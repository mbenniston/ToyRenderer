a.out : ./src/*.c ./src/*.h
	gcc ./src/*.c  -o ./bin/ToyRenderer -lminifb -lX11 -lm -O3 -Wall
