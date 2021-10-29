#!/bin/bash

kaf_nblen_test()
{
	nb=$1
	testable=$2
	answer=$3
	echo "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
	echo "+++++++++<-YOUR OUTPUT +++++++++++++++ TEST $nb +++++++++++++++ -> TEST OUTPUT++++++++++"

	if diff -y <(./tester $testable | cat -e) <(echo "$answer");
	then
		echo -e "OK\n"
	else
		echo -e "KO\n"
	fi
}

kaf_swap_test()
{
	nb=$1
	testable1=$2
	testable2=$3
	answer=$4
	echo "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
	echo "+++++++++<-YOUR OUTPUT +++++++++++++++ TEST $nb +++++++++++++++ -> TEST OUTPUT++++++++++"

	if diff -y <(./tester $testable1 $testable2 | cat -e) <(echo "$answer");
	then
		echo -e "OK\n"
	else
		echo -e "KO\n"
	fi
}

kaf_uv_test()
{
	nb=$1
	u0=$2
	v0=$3
	answer=$5
	echo "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
	echo "+++++++++<-YOUR OUTPUT +++++++++++++++ TEST $nb +++++++++++++++ -> TEST OUTPUT++++++++++"

	if diff -y <(./tester $u0 $v0 | cat -e) answers/uv;
	then
		echo -e "OK\n"
	else
		echo -e "KO\n"
	fi
}

kaf_vec3_test()
{
	nb=$1
	x0=$2
	y0=$3
	z0=$4
	answer=$5
	echo "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
	echo "+++++++++<-YOUR OUTPUT +++++++++++++++ TEST $nb +++++++++++++++ -> TEST OUTPUT++++++++++"

	if diff -y <(./tester $x0 $y0 $z0 | cat -e) answers/vec3;
	then
		echo -e "OK\n"
	else
		echo -e "KO\n"
	fi
}

kaf_tri_test()
{
	nb=$1
	params=$2
	answer=$3
	echo "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
	echo "+++++++++<-YOUR OUTPUT +++++++++++++++ TEST $nb +++++++++++++++ -> TEST OUTPUT++++++++++"

	if diff -y <(./tester $params | cat -e) answers/triangle;
	then
		echo -e "OK\n"
	else
		echo -e "KO\n"
	fi
}

kaf_object_test()
{
	nb=$1
	object=$2
	answer=$3
	echo "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
	echo "+++++++++<-YOUR OUTPUT +++++++++++++++ TEST $nb +++++++++++++++ -> TEST OUTPUT++++++++++"

	if diff -y <(./tester $object | cat -e) $answer;
	then
		echo -e "OK\n"
	else
		echo -e "KO\n"
	fi
}

g++ -o tester -Wall -Wextra -Werror -g kaf_nblen_main.cpp -I.. -L.. -lkaf
kaf_nblen_test '1' '100' '3$'
kaf_nblen_test '2' '1000' '4$'
kaf_nblen_test '3' '10000' '5$'
kaf_nblen_test '4' '100000' '6$'
kaf_nblen_test '5' '1000000' '7$'
kaf_nblen_test '6' '10000000' '8$'
g++ -o tester -Wall -Wextra -Werror -g kaf_swap_main.cpp -I.. -L.. -lkaf
kaf_swap_test '1' '100' '1' '1 100$'
g++ -o tester -Wall -Wextra -Werror -g kaf_vectors_main.cpp -I.. -L.. -lkaf
kaf_vec3_test '1' '1' '2' '3' 'x: 1 y: 2 z: 3 w: 1$'
g++ -o tester -Wall -Wextra -Werror -g kaf_uv_main.cpp -I.. -L.. -lkaf
kaf_uv_test '1' '1' '2'
g++ -o tester -Wall -Wextra -Werror -g kaf_triangles_main.cpp -I.. -L.. -lkaf
kaf_tri_test '1' '1 2 3 4 5 6 7 8 9'
g++ -o tester -Wall -Wextra -Werror -g kaf_object_main.cpp -I.. -L.. -lkaf
kaf_object_test '1' 'empty' 'answers/invalid_obj_file'
kaf_object_test '2' '../object_files/naanna.obj' 'answers/object_error'
kaf_object_test '3' '../object_files/square.obj' 'answers/square'
kaf_object_test '4' '../object_files/cube.obj' 'answers/cube'
