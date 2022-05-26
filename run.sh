#!/bin/bash

set -e

clear

echo "--> compiling sw"
arm-linux-gcc -static -Wall -O3 rsa.c -o rsa


echo "--> run gplatform"
gplatform rsa.fdl 2>/dev/null

echo "--> done"
