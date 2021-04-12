FROM debian:stretch

RUN apt update -y && apt install -y libgmp-dev build-essential g++ git

WORKDIR /usr/src/myapp

RUN git clone https://github.com/cslarsen/miller-rabin.git

COPY Makefile main.cpp /usr/src/myapp/

RUN make

CMD /usr/src/myapp/search

