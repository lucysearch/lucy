#!/bin/sh

export INSTALL_DIR="$(pwd)/install"
export PATH="$INSTALL_DIR/bin:$PATH"
export CLOWNFISH_INCLUDE="$INSTALL_DIR/share/clownfish/include"
export LIBRARY_PATH="$INSTALL_DIR/lib"
export LD_LIBRARY_PATH="$INSTALL_DIR/lib"

git clone --depth=1 https://github.com/lucysearch/lucy-clownfish.git

cd lucy-clownfish/compiler/c
./configure --prefix=$INSTALL_DIR
make
make install

cd ../../runtime/c
./configure --prefix=$INSTALL_DIR
make
make install

cd ../../../c
./configure
make
make test
