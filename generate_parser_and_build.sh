#!/bin/bash

#  
#     IaTestGen - Interval arithmetic test generator
#     Copyright 2013
#
#     Marco Nehmeier (nehmeier@informatik.uni-wuerzburg.de)
#     Institute of Computer Science,
#     University of Wuerzburg, Germany
#     
#     Michael Jedich (m.jedich@gmail.com)
#     University of Wuerzburg, Germany
#     
#     
#     Licensed under the Apache License, Version 2.0 (the "License");
#     you may not use this file except in compliance with the License.
#     You may obtain a copy of the License at
#     
#     http://www.apache.org/licenses/LICENSE-2.0
#     
#     Unless required by applicable law or agreed to in writing, software
#     distributed under the License is distributed on an "AS IS" BASIS,
#     WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#     See the License for the specific language governing permissions and
#     limitations under the License.
#  

if ! [ -x files/apache_ant_1.8.3/bin/ant ]
  then
    echo -e "you have no permission to use ant-tool \nmake ant executable:"
    sudo chmod ugo+x files/apache_ant_1.8.3/bin/ant
fi

for file in $(find . -name "*.sh");
do
  if ! [ -x $file ]
     then
        echo -e "you have no permission to use for some scripts \nplease make them executable:"
        sudo chmod ugo+x $file
  fi
done

if [ -x files/apache_ant_1.8.3/bin/ant ]
  then
    files/apache_ant_1.8.3/bin/ant -q -buildfile generate_parser_and_build.xml
  else
    echo "something went wrong. you have no permission to use ant-tool."
fi

