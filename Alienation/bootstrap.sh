#!/bin/sh

aclocal
autoconf
automake -a
echo Now run "./configure" followed by "make"

