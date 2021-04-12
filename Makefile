search: main.cpp miller-rabin/miller-rabin.h
	g++ main.cpp miller-rabin/miller-rabin.cpp  -o $@ -Wall -lgmp -O3

clean:
	rm -rf o search
