#!/bin/sh
#add all new files
svn status | grep "^?" | cut -d ? -f 2 | xargs svn add 2>/dev/null
echo -n "Log-Message: "
read Message

svn ci ./ --message "$Message" --username frank.wunderlich
read _wait_