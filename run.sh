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
# this script is meant for debugging
#
# with it you can:
#   -compile the unit-test-generator programm
#   -generate tests for available specifications
#   -compile generated tests
#   -run generated tests
# 
# besides an installed jdk no further packages are needed
# 
# if you want to compile jinterval-tests with this
# script place jinterval in lib-folder 
# ("JInterval_all_include.jar")
#
# if you want to run jinterval-tests with this
# script place junit4 in lib-folder ("junit-4.0.jar")
##################################################################



##################################################################
# show infopage of IaTestGen
SHOW_HELP=false
##################################################################
COMPILE_IATESTGEN=true
# recompile dsl-parser. set if DSLParser.jj modified.
COMPILE_WITH_JAVACC=false
# generate tests-source for all available specifications
GENERATE_TESTS=false
#######################LANGUAGE SPECS#############################
JAVA_PRECISION_DEFAULT=true # JINTERVAL
JAVA_PRECISION_EXACT=true
CPP_FLAVOR_IEEE754=true
CPP_FLAVOR_MPFR=true
##################################################################
# compile tests
COMPILE_CPP_TESTS=false
COMPILE_JAVA_TESTS=false
# run tests
RUN_CPP_TESTS=false
RUN_JAVA_TESTS=false
##################################################################
# dir to IaTestGen-project
# TODO: ADJUST PATH 
IATESTGEN_PATH=~/"a/code/iatestgen/IaTestGen"
# output dir for unit-test source-files
# TODO: ADJUST PATH 
OUTPUT_DIR=~/"a/code/iatestgen/IaTestGen/build/current/output"
##################################################################
# example-files of IaTestGen:
# TODO: ADJUST PATH 
DSL_FILE="$IATESTGEN_PATH""/build/current/input/\
specification_example.dsl"
# TODO: ADJUST PATH 
OPTIONAL_FILE="$IATESTGEN_PATH""/build/current/input/\
recommended_op.config"
##################################################################
IATESTGEN_JARFILE="ia_gen.jar"
##################################################################

##################################################################
# file names of generated test-files
TEST_SOURCE_CPP_01="cpp_boost_wueieee754"
TEST_SOURCE_CPP_02="cpp_boost_wuempfr"
TEST_SOURCE_JAVA_01="java_junit_jint"
TEST_SOURCE_JAVA_01_CLASS="Jint" #Name of the Java Class
TEST_SOURCE_JAVA_02="java_junit_jint-exact"
TEST_SOURCE_JAVA_02_CLASS="Jintexact" #Name of the Java Class
##################################################################
# arguments to compile c++ tests
##################################################################
# TODO: ADJUST PATH 
INCLUDES_CPP=~/"a/code/libieeep1788/libieeep1788_branch/"
# INCLUDES_CPP=~/"a/code/libieeep1788/libieeep1788_master/"
COMPILE_CPP_OPTIONS="-g -I"$INCLUDES_CPP" -std=c++11 -Wall -Wextra 
	-pedantic -DNDEBUG  -lboost_unit_test_framework"
##################################################################
# arguments to compile java tests
##################################################################
# path to lib-folder of IaTestGen
# TODO: ADJUST PATH 
LIB_FOLDER='/home/mischka/a/code/iatestgen/IaTestGen/lib/'
INCLUDES_JAVA=".:"$LIB_FOLDER"JInterval_all_include.jar:\
"$LIB_FOLDER"junit-4.0.jar"
##################################################################

clear
echo -e "\n"

# compiling iatestgen
if $COMPILE_IATESTGEN && ! $SHOW_HELP ; then
	cd "$IATESTGEN_PATH""/build"
	if $COMPILE_WITH_JAVACC ; then
		echo -e "COMPILING IATESTGEN WITH JAVACC";
		./generate_parser_and_build.sh
	else
		echo -e "\nCOMPILING IATESTGEN";
		./build_with_existing_parser.sh
	fi
	echo -e "\n......................................................DONE\n";
fi

# generating tests
if $GENERATE_TESTS || $SHOW_HELP ; then
	cd "$IATESTGEN_PATH""/build/current/"
	if $SHOW_HELP ; then
		java -jar $IATESTGEN_JARFILE -H 
	else 
		echo -e "\nGENERATE TESTS";
		if $CPP_FLAVOR_IEEE754 ; then
			java -jar $IATESTGEN_JARFILE -i $DSL_FILE -o $OUTPUT_DIR \
			-P $OPTIONAL_FILE "--$TEST_SOURCE_CPP_01"
		fi
		if $CPP_FLAVOR_MPFR ; then
			java -jar $IATESTGEN_JARFILE -i $DSL_FILE -o $OUTPUT_DIR \
			-P $OPTIONAL_FILE "--$TEST_SOURCE_CPP_02"
		fi
		if $JAVA_PRECISION_DEFAULT; then
			java -jar $IATESTGEN_JARFILE -i $DSL_FILE -o $OUTPUT_DIR \
			-P $OPTIONAL_FILE "--$TEST_SOURCE_JAVA_01"
		fi
		if $JAVA_PRECISION_EXACT ; then
			java -jar $IATESTGEN_JARFILE -i $DSL_FILE -o $OUTPUT_DIR \
			-P $OPTIONAL_FILE "--$TEST_SOURCE_JAVA_02"
		fi
		echo -e "......................................................DONE\n";
	fi
fi

# compiling cpp tests
if $COMPILE_CPP_TESTS && ! $SHOW_HELP ; then
	echo -e "\nCOMPILING CPP UNIT TESTS";
	cd "$OUTPUT_DIR"
	if $CPP_FLAVOR_IEEE754 ; then
		[ -f "$TEST_SOURCE_CPP_01" ] && rm "$TEST_SOURCE_CPP_01"
		g++ $COMPILE_CPP_OPTIONS "$TEST_SOURCE_CPP_01.cpp" \
		-o "$TEST_SOURCE_CPP_01"
		[ -f "$TEST_SOURCE_CPP_01" ] && echo "--> C++ IEEE754 Flavor compiled." 
	fi
	if $CPP_FLAVOR_MPFR ; then
		[ -f "$TEST_SOURCE_CPP_02" ] && rm "$TEST_SOURCE_CPP_02"
		g++ $COMPILE_CPP_OPTIONS "$TEST_SOURCE_CPP_02.cpp" \
		-o "$TEST_SOURCE_CPP_02"
		[ -f "$TEST_SOURCE_CPP_02" ] && echo "--> C++ MPFR Flavor compiled." 
	fi
	echo -e "......................................................DONE\n";
fi


# compiling java tests
if $COMPILE_JAVA_TESTS && ! $SHOW_HELP ; then
	echo -e "\nCOMPILING JAVA UNIT TESTS":
	cd "$OUTPUT_DIR"
	if $JAVA_PRECISION_DEFAULT ; then
		[ -f "$TEST_SOURCE_JAVA_01_CLASS" ] && rm "$TEST_SOURCE_JAVA_01_CLASS"
		javac -cp $INCLUDES_JAVA ""$TEST_SOURCE_JAVA_01_CLASS".java"
		echo "--> jInterval Default compiled." 
	fi
	if $JAVA_PRECISION_EXACT ; then
		[ -f "$TEST_SOURCE_JAVA_02_CLASS" ] && rm "$TEST_SOURCE_JAVA_02_CLASS"
		javac -cp $INCLUDES_JAVA ""$TEST_SOURCE_JAVA_02_CLASS".java"
		echo "--> jInterval Exact compiled." 
	fi
	echo -e "......................................................DONE\n";
fi

if $RUN_CPP_TESTS && ! $SHOW_HELP ; then
	if $CPP_FLAVOR_IEEE754 ; then
		echo -e "\nRUNNING TESTS "$TEST_SOURCE_CPP_01"\n";
		[ -f "$TEST_SOURCE_CPP_01" ] && ./"$TEST_SOURCE_CPP_01"
		[ ! -f "$TEST_SOURCE_CPP_01" ] && echo "-->no executable found" 
	fi
	if $CPP_FLAVOR_MPFR ; then
		echo -e "\nRUNNING TESTS "$TEST_SOURCE_CPP_02"\n";
		[ -f "$TEST_SOURCE_CPP_02" ] && ./"$TEST_SOURCE_CPP_02"
		[ ! -f "$TEST_SOURCE_CPP_02" ] && echo "-->no executable found" 
	fi

	echo -e "......................................................DONE\n";
fi


if $RUN_JAVA_TESTS && ! $SHOW_HELP ; then
	if $JAVA_PRECISION_DEFAULT ; then
		echo -e "\nRUNNING TESTS "$TEST_SOURCE_JAVA_01"\n";
		[ -f "$TEST_SOURCE_JAVA_01_CLASS.class" ] && \
 		java -cp $INCLUDES_JAVA org.junit.runner.JUnitCore \
		"$TEST_SOURCE_JAVA_01_CLASS"
		[ ! -f "$TEST_SOURCE_JAVA_01_CLASS.class" ] && echo "-->no executable found" 
	fi
	if $JAVA_PRECISION_EXACT ; then
		echo -e "\nRUNNING TESTS "$TEST_SOURCE_JAVA_02"\n";
		[ -f "$TEST_SOURCE_JAVA_02_CLASS.class" ] && \
 		java -cp $INCLUDES_JAVA org.junit.runner.JUnitCore \
		"$TEST_SOURCE_JAVA_02_CLASS"
		[ ! -f "$TEST_SOURCE_JAVA_02_CLASS.class" ] && echo "-->no executable found" 
		
	fi
	echo -e "......................................................DONE\n";
fi
