set DSLFILE="input/test01.dsl"
set OUTPUT="output/"
set JARFILE="ia_gen.jar"

java -jar %JARFILE% -i %DSLFILE% -o %OUTPUT%
