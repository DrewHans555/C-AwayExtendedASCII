#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include "CAwayExtendedASCII.h"

int main(int argc, char **argv)
{
    extern char *optarg;
    extern int optind;
    int c;
    int err = 0;
    static char usage[] = "usage: %s -f filename\n";
    int required_args = 1;
    int fflag=0;
    char *filename;

    while ((c = getopt(argc, argv, "f:")) != -1)
    {
        switch (c)
        {
            case 'f':
                fflag = 1;
                filename = optarg;
                break;
            case '?':
                err = 1;
                break;
        }
    }

    if (fflag == 0)
    {
        fprintf(stderr, "%s: missing -f option\n", argv[0]);
        fprintf(stderr, usage, argv[0]);
        exit(1);
    }
    else if (err)
    {
        fprintf(stderr, usage, argv[0]);
        exit(1);
    }

    int status = CAwayExtendedASCII(filename);

    exit(status);
}
