#!/bin/sh

echo ---- Running aclocal
aclocal
echo ---- Running autoconf
autoconf
echo ---- Running libtoolize
libtoolize
echo ---- Running automake
automake -a
echo ---- Now run "./configure" followed by "make"

