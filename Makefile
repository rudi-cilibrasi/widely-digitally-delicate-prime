search: main.cpp miller-rabin/miller-rabin.h
	g++ --std=c++17 main.cpp miller-rabin/miller-rabin.cpp Tester54Bit.cpp  -o $@ -Wall -lgmp -O3

miller-rabin/miller-rabin.h:
	git clone https://github.com/cslarsen/miller-rabin.git

clean:
	rm -rf o search
