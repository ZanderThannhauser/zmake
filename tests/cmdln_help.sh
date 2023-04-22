#!/bin/bash
set -ev
"$1" --help
touch "$2"
