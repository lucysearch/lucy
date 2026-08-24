#!/bin/sh

set -e

INSTALL_DIR="$(pwd)/ci_install"
export CLOWNFISH_INCLUDE="$INSTALL_DIR/share/clownfish/include"
export LD_LIBRARY_PATH="$INSTALL_DIR/lib"

export CC=clang
export LSAN_OPTIONS=suppressions=../devel/conf/LSan.supp
export UBSAN_OPTIONS=print_stacktrace=1

git clone --depth=1 https://github.com/lucysearch/lucy-clownfish.git

cd lucy-clownfish/compiler/c
./configure --prefix=$INSTALL_DIR
make
make install

# charmonizer doesn't allow to specify linker flags, so we patch the
# Makefile manually.

cd ../../runtime/c
./configure \
    --prefix=$INSTALL_DIR \
    -- \
    -fsanitize=address,undefined \
    -fno-sanitize=function \
    -fno-sanitize-recover=all \
    -fno-omit-frame-pointer
sed -i -e 's/LDFLAGS = /&-fsanitize=address,undefined /' Makefile
make
make install

cd ../../../c
./configure \
    --clownfish-prefix=$INSTALL_DIR \
    -- \
    -D LUCY_UBSAN \
    -fsanitize=address,undefined \
    -fno-sanitize=function \
    -fno-sanitize-recover=all \
    -fno-omit-frame-pointer
sed -i -e '/LEMON/! s/LDFLAGS = /&-fsanitize=address,undefined /' Makefile
make
make test
