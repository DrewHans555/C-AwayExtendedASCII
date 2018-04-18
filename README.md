# C-AwayExtendedASCII
This repository contains code written in C for Blackburn College's Spring 2018 Horizons In Computer Science class CS372.

C-AwayExtendedASCII is a C program for compressing ANSI text files to 7-bit ASCII. C-Away simply removes the leftmost bit from each char in the original file and outputs a new compressed file. 

If the size of the original file is (X) bits then the compressed file size will be (X*(7/8) + Xmod8) bits.

### Prerequisites
* GCC (or similar compiler)
* GNU Make (or you can compile yourself using: gcc main.c -o cawayextendedascii)

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details
