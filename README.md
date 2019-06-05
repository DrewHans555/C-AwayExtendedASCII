# C-AwayExtendedASCII

C-AwayExtendedASCII is a simple C program for compressing ANSI text files to 7-bit ASCII.

If the size of the original file is (X) bits then the compressed file size will be (X*(7/8) + (X mod 8)) bits.

### Prerequisites
* GCC
* GNU Make

### Getting Started
The recommended way to build C-AwayExtendedASCII is with the included [makefile](./makefile).

Typing ```make``` will compile all code in /src into a single executable in /build.

Typing ```make test``` will compile all testable modules with the unity testing framework in /unity, run all tests in /test, and then print the test results.

Typing ```make clean``` will remove all .o, .out, .exe, and .txt files in /build.

Typing ```make usage``` will display all available options.

After building, feel free to test it out on the included txt copy of Alice's Adventures in Wonderland by Lewis Carroll:
* On Linux: ```cawayextendedascii.out -f "./Alice's Adventures in Wonderland by Lewis Carroll.txt"```
* On Windows: ```cawayextendedascii.exe -f "./Alice's Adventures in Wonderland by Lewis Carroll.txt"```

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

Unity, which this project uses for testing, is also licensed under the MIT License - see the [unity/LICENSE.txt](./unity/LICENSE.txt) file for details.
