#!/bin/bash

# kaf_nblen_test()
# {
# 	nb=$1
# 	option=$2
# 	answer=$3
# 	echo "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
# 	echo "++ TEST $nb ++"

# 	if diff <(./tester $option | cat -e) <(echo "$answer");
# 	then
# 		echo -e "OK\n"
# 	else
# 		echo -e "KO\n"
# 	fi
# }

kaf_nblen_test()
{
	nb=$1
	testable=$2
	answer=$3
	echo "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
	echo "++ TEST $nb ++"

	if diff <(./tester $testable | cat -e) <(echo "$answer");
	then
		echo -e "OK\n"
	else
		echo -e "KO\n"
	fi
}

g++ -Wall -Wextra -Werror -g kaf_nblen.cpp kaf_nblen_main.cpp -o tester
kaf_nblen_test '1' '100' '3$'
kaf_nblen_test '2' '1000' '4$'
kaf_nblen_test '3' '10000' '5$'
kaf_nblen_test '4' '100000' '6$'
kaf_nblen_test '5' '1000000' '7$'
kaf_nblen_test '6' '10000000' '8$'
kaf_nblen_test '7' '-3' '1$'
kaf_nblen_test '7' '-20' '2$'
