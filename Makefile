a.out : main.c draw.c vec.c *.h
	gcc main.c draw.c vec.c -o a.out -lminifb -lX11 -lm
