
cc = "gcc"

cflags = ["-Wall", "-Werror"]

srcs = []

/tmp/srclist.md:
	$ find -name '*.c' | sed 's/^/srcs += ["/g;s/$/"]/g' > /tmp/srclist.md

include /tmp/srclist.md

objs = []
deps = []
for src in srcs:
	objdir = "/tmp/bin/" + dir(src); obj = "/tmp/bin/" + basename(src) + '.o'
	depdir = "/tmp/dep/" + dir(src); dep = "/tmp/dep/" + basename(src) + '.d'
	(objdir): $ mkdir -p (objdir)
	(depdir): $ mkdir -p (depdir)
	(obj) (dep): (src) | (objdir) (depdir)
		$ (cc) -c (cppflags) (cflags) (src) -MMD -MF (dep) -o (obj)
	objs += [obj]; deps += [dep]
endfor

default: /tmp/zmake

/tmp/zmake: (objs)
	$ (cc) (objs) -o /tmp/zmake

include (deps)













