set DSLFILE="input/specification_example.dsl"
set OUTPUT="output/"
set JARFILE="ia_gen.jar"

java -jar %JARFILE% -i %DSLFILE% -o %OUTPUT%
