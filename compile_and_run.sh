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

##################################################################
# show infopage of IaTestGen
SHOW_HELP=false
##################################################################
COMPILE_IATESTGEN=false
# recompile dsl-parser. set if DSLParser.jj modified.
COMPILE_JAVACC=false
# generate tests-source for all available specifications
GENERATE_TESTS=true
# compile tests
COMPILE_CPP_TESTS=true
# run tests
RUN_TESTS=true
##################################################################
# flavor settings
FLAVOR_IEEE754=true;
FLAVOR_MPFR=false;
##################################################################
# dir to IaTestGen-project
IATESTGEN_PATH=~/"a/code/iatestgen/IaTestGen"
# output dir for unit-test source-files
OUTPUT_DIR=~/"a/code/iatestgen/IaTestGen/build/output"
##################################################################
# example-files of IaTestGen:
DSL_FILE="$IATESTGEN_PATH""/build/input/specification_example.dsl"
OPTIONAL_FILE="$IATESTGEN_PATH""/build/input/recommended_op.config"
##################################################################
IATESTGEN_JARFILE="ia_gen.jar"
##################################################################


##################################################################
# arguments to compile c++ tests
##################################################################
INCLUDES=~/"a/code/libieeep1788/libieeep1788_branch/"
##################################################################
# file names of generated test-files
TEST_SOURCE_01="cpp_boost_wueieee754"
TEST_SOURCE_02="cpp_boost_wuempfr"
##################################################################

clear

if $COMPILE_IATESTGEN && ! $SHOW_HELP ; then
	cd "$IATESTGEN_PATH" 
	if $COMPILE_JAVACC ; then
		echo -e "COMPILING IATESTGEN WITH JAVACC...........................";
		./generate_parser_and_build.sh
	else
		echo -e "\nCOMPILING IATESTGEN.......................................";
		./build_with_existing_parser.sh
	fi
	echo -e "\n......................................................DONE\n";
fi


if $GENERATE_TESTS || $SHOW_HELP ; then
	cd "$IATESTGEN_PATH""/build/"
	if $SHOW_HELP ; then
		java -jar $IATESTGEN_JARFILE -H 
	else 
		echo -e "\nGENERATE TESTS............................................";
		if $FLAVOR_IEEE754 ; then
			java -jar $IATESTGEN_JARFILE -i $DSL_FILE -o $OUTPUT_DIR -P $OPTIONAL_FILE "--$TEST_SOURCE_01"
		fi
		if $FLAVOR_MPFR ; then
			java -jar $IATESTGEN_JARFILE -i $DSL_FILE -o $OUTPUT_DIR -P $OPTIONAL_FILE "--$TEST_SOURCE_02"
		fi
		echo -e "......................................................DONE\n";
	fi
fi


if $COMPILE_CPP_TESTS && ! $SHOW_HELP ; then
	echo -e "\nCOMPILING CPP UNIT TESTS..................................";
	cd "$OUTPUT_DIR"
	if $FLAVOR_IEEE754 ; then
		[ -f "$TEST_SOURCE_01" ] && rm "$TEST_SOURCE_01"
		g++ -g -I"$INCLUDES" -std=c++11 -Wall -Wextra -Werror -pedantic -DNDEBUG "$TEST_SOURCE_01.cpp" -lboost_unit_test_framework -o "$TEST_SOURCE_01"
	fi
	if $FLAVOR_MPFR ; then
		[ -f "$TEST_SOURCE_02" ] && rm "$TEST_SOURCE_02"
		g++ -g -I"$INCLUDES" -std=c++11 -Wall -Wextra -Werror -pedantic -DNDEBUG "$TEST_SOURCE_02.cpp" -lboost_unit_test_framework -o "$TEST_SOURCE_02"
	fi
	echo -e "......................................................DONE\n";
fi


if $RUN_TESTS && ! $SHOW_HELP ; then
	if $FLAVOR_IEEE754 ; then
		echo -e "\nRUNNING TESTS IEEE754.....................................";
		[ -f "$TEST_SOURCE_01" ] && ./"$TEST_SOURCE_01"
		[ ! -f "$TEST_SOURCE_01" ] && echo "-->no executable found" 
	fi
	if $FLAVOR_MPFR ; then
		echo -e "\nRUNNING TESTS MPFR........................................";
		[ -f "$TEST_SOURCE_02" ] && ./"$TEST_SOURCE_02"
		[ ! -f "$TEST_SOURCE_02" ] && echo "-->no executable found" 
	fi

	echo -e "......................................................DONE\n";
fi
