# Questions

## What's `stdint.h`?

Declaration of integer types

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

Defining integer types with a specific width

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

8, 32, 32, 16

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

4D

## What's the difference between `bfSize` and `biSize`?

bfSize=biSize + 54 (Header)

## What does it mean if `biHeight` is negative?

Topdown image

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

Permission issues, file does not exist

## Why is the third argument to `fread` always `1` in our code?

Reading file in blocks

## What value does line 63 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

3

## What does `fseek` do?

Set file position to a given offset

## What is `SEEK_CUR`?

Position from where is offset added, i.e. current position of file pointer
