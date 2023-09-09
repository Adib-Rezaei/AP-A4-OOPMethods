CL =g++ -std=c++11
CC =g++ -std=c++11 -c

all: Goodreads.out

Goodreads.out: Main.o Goodreads.o Authors.o Books.o Users.o Reviews.o Functions.o
	${CL} Main.o Goodreads.o Authors.o Books.o Users.o Reviews.o Functions.o -o Goodreads.out

Main.o: Main.cpp Goodreads.hpp Main.hpp
	${CC} Main.cpp

Goodreads.o: Goodreads.cpp Main.hpp Goodreads.hpp Authors.hpp Books.hpp
	${CC} Goodreads.cpp

Authors.o: Authors.cpp Authors.hpp Main.hpp
	${CC} Authors.cpp

Books.o: Books.cpp Books.hpp
	${CC} Books.cpp

Users.o: Users.cpp Users.hpp Main.hpp
	${CC} Users.cpp

Reviews.o: Reviews.cpp Reviews.hpp 
	${CC} Reviews.cpp

Functions.o: Functions.cpp Main.hpp Goodreads.hpp
	${CC} Functions.cpp

clean:
	rm *.o
	rm Goodreads.out