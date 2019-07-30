a.out : main.c draw.c vec.c model.c util.c *.h
	gcc main.c draw.c vec.c model.c util.c -o a.out -lminifb -lX11 -lm -O3
