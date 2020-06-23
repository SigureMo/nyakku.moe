mkdir tmp/
echo 'Compiling...'
g++ -std=c++11 -c arithmetic_unit.cpp -o tmp/arithmetic_unit.o
g++ -std=c++11 -c calculator.cpp -o tmp/calculator.o
g++ -std=c++11 -c operand.cpp -o tmp/operand.o
g++ -std=c++11 -c operator.cpp -o tmp/operator.o
g++ -std=c++11 -c compute.cpp -o tmp/compute.o
g++ -std=c++11 tmp/calculator.o tmp/arithmetic_unit.o tmp/operand.o tmp/operator.o tmp/compute.o -o tmp/calculator
rm tmp/arithmetic_unit.o tmp/calculator.o tmp/operand.o tmp/operator.o tmp/compute.o
echo 'Running...'
tmp/calculator
echo 'Exit'
rm -r tmp/
