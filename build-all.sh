set -ev
unset on_error
make buildtype=debug   -j8
make buildtype=test    -j8
make buildtype=release -j8
