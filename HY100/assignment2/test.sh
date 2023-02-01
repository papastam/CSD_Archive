#!/bin/sh

##########################################################################
# The MIT License (MIT)                                                  #
#                                                                        #
# Copyright (c) 2015 Foivos S. Zakkak <foivos@zakkak.net>                #
#                                                                        #
# Permission is hereby granted, free of charge, to any person obtaining  #
# a copy of this software and associated documentation files (the        #
# "Software"), to deal in the Software without restriction, including    #
# without limitation the rights to use, copy, modify, merge, publish,    #
# distribute, sublicense, and/or sell copies of the Software, and to     #
# permit persons to whom the Software is furnished to do so, subject to  #
# the following conditions:                                              #
#                                                                        #
# The above copyright notice and this permission notice shall be         #
# included in all copies or substantial portions of the Software.        #
#                                                                        #
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,        #
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF     #
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND                  #
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE #
# LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION #
# OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION  #
# WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.        #
##########################################################################


# Check if there are two arguments
if [ $# -eq 2 ]; then
   if ! [ -d "$2" ]; then
     /bin/echo "$2 is not a directory."
     exit 1
   fi
else
   /bin/echo "Usage: $0 <executable> <folder with tests>"
   exit 1
fi

# who am I?
LOGIN=`whoami`
# create a temporary directory to store the results
mkdir -p /tmp/${LOGIN}/$2/
for i in `ls $2/*.in`; do
    # remove previous results
    rm -f /tmp/${LOGIN}/${i%in}out;
    # run the executable to produce the result
    ./$1 < $i > /tmp/${LOGIN}/${i%in}out;
    # Diff ignoring empty lines (-B)
    diff -B ${i%in}out /tmp/${LOGIN}/${i%in}out;
    ans=$?
    # Print the test filename
    /bin/echo -n $i' :';
    # Check if there where any diffs or not
    if [ $ans -eq 0 ]; then
        /bin/echo -e '\e[30G \e[32;1mPASS\e[0m';
    else
        /bin/echo -e '\e[30G \e[31;1mFAIL\e[0m';
    fi
done
rm -rf /tmp/${LOGIN}/$2/
