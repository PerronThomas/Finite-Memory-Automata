all : Automate algo.dot Algo.jpg input.txt automate.txt 

Automate : main.cpp etat.cpp etat.h token.cpp token.h transition.cpp transition.h
	rm -f output.txt
	g++ $^ -o $@

algo.dot : Automate
	./$^

Algo.jpg : algo.dot
	dot -Tjpg $^ -o $@

clean:
	rm -f Automate algo.dot output.txt Algo.jpg
