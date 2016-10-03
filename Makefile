test_setport: setport test_setport.cpp
	g++-5 -std=c++11 -o test_setport test_setport.cpp
	
setport: portsetter.cpp
	g++-5 -std=c++11 -o setport portsetter.cpp

execute_test: test_setport
	test_setport
