#bin/sh

# shellcheck disable=SC2164
cd cmake-build-debug
cmake ..
make
./StarGame

