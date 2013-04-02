#!/bin/bash
DSLFILE="input/test02.dsl"
OUTPUT="output/"
JARFILE="ia_gen.jar"

java -jar $JARFILE -i $DSLFILE -o $OUTPUT -s03
