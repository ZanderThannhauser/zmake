#!/bin/bash
set -ev
"$1" --test-circular-dependencies
touch "$2"
