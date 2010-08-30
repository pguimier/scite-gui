#!/bin/sh
svn -R propset svn:ignore -F svn_ignore .

echo press any key to close window...
read _wait_
