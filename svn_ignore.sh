#!/bin/sh
svn -R propset svn:ignore -F .svnignore .

echo press any key to close window...
read _wait_
