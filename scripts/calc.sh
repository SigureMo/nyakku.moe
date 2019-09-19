g++ -std=c++11 -c Codes/VB/05_calc/calculate/arithmetic_unit.cpp -o tmp/arithmetic_unit.o
g++ -std=c++11 -c Codes/VB/05_calc/calculate/calculate.cpp -o tmp/calculate.o
g++ -std=c++11 -c Codes/VB/05_calc/calculate/operand.cpp -o tmp/operand.o
g++ -std=c++11 -c Codes/VB/05_calc/calculate/operator.cpp -o tmp/operator.o
g++ -std=c++11 -c Codes/VB/05_calc/calculate/compute.cpp -o tmp/compute.o
g++ -std=c++11 tmp/calculate.o tmp/arithmetic_unit.o tmp/operand.o tmp/operator.o tmp/compute.o -o tmp/calculate
tmp/calculate
yarn clear
