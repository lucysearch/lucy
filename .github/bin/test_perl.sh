#!/bin/sh

git clone --depth=1 https://github.com/lucysearch/lucy-clownfish.git

cd lucy-clownfish/compiler/perl
perl Build.PL
./Build
./Build install

cd ../../runtime/perl
perl Build.PL
./Build
./Build install

cd ../../../perl
perl Build.PL
./Build
./Build test
