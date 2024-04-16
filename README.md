# graphics-dev

This project depends on SDL2.

## Usage

```shell
git clone https://github.com/ethanuppal/graphics-dev.git
cd graphics-dev
make test
make
./main test1
```

## Models

Specification:

```
#VERTICES #FACES
v1.x v1.y v1.z
...
f1.a f1.b f2.c
...
```

Example:

```
3 1
-0.5 -0.5 2
0 0.5 2
0.5 -0.5 2
0 1 2
```

Notes:

- Vertices should be specified by their (zero-based) index and in clockwise order
