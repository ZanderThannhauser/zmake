set -ev
buildtype=debug   ./make.py
buildtype=dev     ./make.py
buildtype=test    ./make.py
buildtype=release ./make.py
