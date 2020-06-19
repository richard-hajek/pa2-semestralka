#!/usr/bin/env bash

[[ -d hajekric ]] && rm -r hajekric
mkdir hajekric
cp -r src hajekric
cp -r doxygen hajekric
cp -r examples hajekric
cp Makefile hajekric
cp zadani.txt hajekric
cp prohlaseni.txt hajekric
cp polymorfismus.txt hajekric
zip -r hajekric.zip hajekric
