# Compression Library (CompLib)

This is a library that aims to provide simple wrappers around a few compression algorithms, currently just [LZO](https://www.oberhumer.com/opensource/lzo/)

## Compiling

### Shared Library

Simply run cmake and make (or ninja or whatever you want to use)

First make a build directory in the project root directory and enter that, then:

```bash
cmake ..
make
```

### Static Library

Simply run cmake (but setting the option COMPLIB_STATIC to ON) and make (or ninja or whatever you want to use)

First make a build directory in the project root directory and enter that, then:

```bash
cmake -DCOMPLIB_STATIC=ON ..
make
```
