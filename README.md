# widely digitally-delicate-prime
Program to search for Widely Digitally Delicate Prime numbers
using libgmp and Docker

It will start at a random 54-bit unsigned integer searching for a
widely digitally delicate prime number.

https://www.popularmechanics.com/science/math/a36014795/mathematicians-discover-new-kind-of-prime-number/

https://arxiv.org/pdf/2101.08898.pdf

# Building

```
docker build -t wddp .
```

# Running

```
docker run --name wddp --rm wddp
```
