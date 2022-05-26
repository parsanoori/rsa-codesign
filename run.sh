#!/bin/bash

set -e

echo "--> compiling sw..."
arm-linux-gcc -static -Wall -O3 rsa.c -o rsa
echo "--> run gplatform..."
gplatform rsa.fdl
echo "--> done"
