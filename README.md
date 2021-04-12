# digitally-delicate-prime
Program to search for Digitally Delicate Prime numbers using libgmp and Docker

It will start at a random 54-bit unsigned integer searching for a
widely digitally delicate prime number.

https://www.popularmechanics.com/science/math/a36014795/mathematicians-discover-new-kind-of-prime-number/


# Building

```
docker build -t wddp .
```

# Running

```
docker run --name wddp --rm wddp
```
