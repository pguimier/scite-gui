#!/bin/sh
version=$(svnversion -n|sed -e 's/.*:\([0-9]*\).*/\1/')
echo "Revision: $version"
svn export ./ ../_sg_
cd ../_sg_
7za u -tzip $(dirname $0)/scite-gui_r$version.zip *
cd ..
rm -rf _sg_

read _wait_