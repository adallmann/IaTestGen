#!/bin/bash
echo -e "\n"
echo "======================================================================"
echo "Run C++ Boost Unit Test Functions:"
g++ cpp_boost_boost.cpp -o cpp_boost_boost -lboost_unit_test_framework
./cpp_boost_boost
rm cpp_boost_boost
echo "======================================================================"
echo -e "\n"
