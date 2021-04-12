#FROM debian:stretch
FROM alpine:3.13.4

RUN apk add gmp-dev git make g++

WORKDIR /usr/src/myapp

RUN git clone https://github.com/cslarsen/miller-rabin.git

COPY Makefile main.cpp /usr/src/myapp/

RUN make

CMD /usr/src/myapp/search

