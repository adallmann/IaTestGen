#!/bin/bash
DSLFILE="input/specification_example.dsl"
OUTPUT="output/"
JARFILE="ia_gen.jar"

java -jar $JARFILE -i $DSLFILE -o $OUTPUT
