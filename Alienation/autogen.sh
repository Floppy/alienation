#!/bin/sh

aclocal
autoconf
automake -a

echo "Now do ./configure to start the build process"
