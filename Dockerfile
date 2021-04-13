#FROM debian:stretch
FROM alpine:3.13.4

RUN apk add gmp-dev git make g++

WORKDIR /usr/src/myapp

COPY . /usr/src/myapp

RUN make

CMD /usr/src/myapp/search

