#!/usr/bin/python3

import sys;
import subprocess;
import pickle;
import atexit;

from time import time;
from glob import glob;
from os import environ;
from os.path import exists, getmtime;

from heapq import heappush;
from heapq import heappop;

database = dict();

database_file = ".make.py.db";
if exists(database_file):
	with open(database_file, "rb") as stream:
		database = pickle.load(stream);

if "fail-times" not in database:
	database["fail-times"] = dict();

if "prev-commands" not in database:
	database["prev-commands"] = dict();

def flush_database():
	with open(database_file, "wb") as stream:
		pickle.dump(database, stream);

atexit.register(flush_database);

class recipe_object:
	def __init__(self, target):
		self.target = target;
		self.command = None;
		self.ordered_only = set();
		self.dep_on = set();
		self.dep_of = set();
		self.ftime = database["fail-times"].setdefault(target, time());
		self.waiting = 0;
	
	def add_dep(self, other, order_only = False):
		if order_only:
			self.ordered_only.add(other);
		else:
			self.dep_on.add(other);
		other.dep_of.add(self);
	
	def should_rebuild(self):
		if not exists(self.target):
			return True;
		
		if self.command != database["prev-commands"].get(self.target):
			return True;
		
		mtime = getmtime(self.target);
		return any(getmtime(dep.target) > mtime for dep in self.dep_on);
		
	def __lt__(self, other):
		return (self.ftime, self.target) > (other.ftime, other.target);
	
all_recipes = dict();

def recipe(name):
	if name not in all_recipes:
		x = recipe_object(name);
		all_recipes[name] = x;
	return all_recipes[name];

def make(start_targets):
	# update priorities:
	todo = set(all_recipes.values());
	while len(todo):
		element = todo.pop();
		for dep in element.dep_on:
			if dep.ftime < element.ftime:
				dep.ftime = element.ftime;
				todo.add(dep);
	
	needed = set();
	
	# figure out which recipes are needed:
	todo = set([recipe(target) for target in start_targets])
	while len(todo):
		element = todo.pop();
		if element not in needed:
			needed.add(element);
			for dep in element.dep_on:
				todo.add(dep);
			for dep in element.ordered_only:
				todo.add(dep);
	
	todo = list();
	
	# add initial recipes to todo
	for element in needed:
		element.waiting = len(element.dep_on) + len(element.ordered_only);
		if element.waiting == 0:
			heappush(todo, element);
	
	# run commands, add more recipes to todo list, repeat as necessary:
	while len(todo):
		element = heappop(todo);
		
		if not exists(element.target) and element.command is None:
			print(f"no command to build '{element.target}'!");
			print(f"(needed by {', '.join(d.target for d in element.dep_of)})");
			exit(1);
		elif element.should_rebuild():
			assert(element.command);
			print("\033[33m" f"$ {' '.join(element.command)}" "\033[0m");
			result = subprocess.run(element.command);
			if result.returncode:
				print("subcommand failed!");
				database["fail-times"][element.target] = time();
				exit(1);
			else:
				database["prev-commands"][element.target] = element.command;
		
		for dep in element.dep_of:
			dep.waiting -= 1;
			if dep.waiting == 0:
				heappush(todo, dep);
	

cc = "gcc";
cppflags = ["-D", "_GNU_SOURCE", "-I", "."];
cflags = ["-Wall", "-Werror", "-Wfatal-errors"];
ldflags = [];
ldlibs = ["-lgmp", "-lgdbm"];

buildtype = environ.get("buildtype", "release");

if buildtype == "debug":
	cppflags += ["-D", "DEBUGGING"];
	cflags += ["-g"];
	cflags += ["-Wno-unused-variable"];
	cflags += ["-Wno-unused-but-set-variable"];
elif buildtype == "test":
	cppflags += ["-D", "TESTING"];
elif buildtype == "release":
	cppflags += ["-D", "RELEASE"];
else:
	print("! UNKNOWN BUILD !");
	exit(1);

buildprefix = f"build/{buildtype}-type";

directories = set();
dependency_files = list();
objects = list();

for src in glob("**/*.c", recursive = True):
	obj = buildprefix + "/" + src[:-2] + ".o";
	recipe(obj).add_dep(recipe(src));
	recipe(obj).command = [cc, "-c", *cppflags, *cflags, src, "-o", obj];
	objects.append(obj);
	
	dep = buildprefix + "/" + src[:-2] + ".d";
	recipe(dep).add_dep(recipe(src));
	recipe(dep).command = [cc, "-MM", *cppflags, src, "-MT", obj, "-MF", dep];
	dependency_files.append(dep);
	
	directory = obj[:obj.rindex("/")];
	recipe(obj).add_dep(recipe(directory), order_only = True);
	recipe(dep).add_dep(recipe(directory), order_only = True);
	directories.add(directory);
	
for directory in directories:
	recipe(directory).command = ["mkdir", directory, "-p"];

executable = buildprefix + "/" + "main";
for obj in objects: recipe(executable).add_dep(recipe(obj));
recipe(executable).command = [cc, *ldflags, *objects, *ldlibs, "-o", executable];

args = ["-j1", "-f", "makefile"];
#args = ["--help"];

recipe("run").add_dep(recipe(executable));
recipe("run").command = [executable, *args];

recipe("valrun").add_dep(recipe(executable));
recipe("valrun").command = ["valgrind", executable, *args];

# build and read the dependency files before considering the executable:
make(dependency_files);
for dependency_file in dependency_files:
	with open(dependency_file) as stream:
		target, *deps = stream.read().replace("\\\n", " ").split();
		for dep in deps:
			recipe(target[:-1]).add_dep(recipe(dep));

# build whatever the user asked for, default to building the executable:
if len(sys.argv) > 1:
	make(sys.argv[1:]);
else:
	make([executable]);






















