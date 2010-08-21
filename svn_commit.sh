#!/bin/sh
echo -n "Log-Message: "
read Message
#add all new files
svn status | grep "^?" | cut -d ? -f 2 | xargs svn add

svn ci ./ --message "$Message"
read _wait_
