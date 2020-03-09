/*-
 * kestrelc.c
 * 
 * This implementation is following the theory in the Compiler Construction
 * course given by Douglas W.Jones from The University of Iowa Department of 
 * Computer Science
 * http://homepage.divms.uiowa.edu/~jones/compiler/
 * 
 * Copyright (c) 2019 Fehmi Noyan Isi
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "kestrelc.h"

int sflag;

void usage() {
    printf("usage: kestrelc [source_file] [-s] [-o output_file]\n");
}

static struct option longopts[] = {
    {"outfile",     required_argument,      NULL,   'o'},
    {"asm",         no_argument,            NULL,   's'}
};

int main(int argc, char **argv) {
    FILE *in_fd, *out_fd;
    int ch;
    const char *optstr = "so:";

    /* defaults input and output */
    in_fd = stdin;
    out_fd = stdout;

    while ((ch = getopt_long(argc, argv, optstr, longopts, NULL)) != -1) {
        switch (ch) {
            case 'o':
                if ((out_fd = fopen(optarg, "w")) == NULL) {
                    fprintf(stderr, "Cannot open output file %s.\n", optarg);
                    exit(EXIT_FAILURE);
                }
                break;
            case 's':
                sflag = 1;
                break;
            case '?':
            default:
                usage();
        }
    } 

   if (optind >= argc) {
        fprintf(stderr, "Expected argument after options\n");
        exit(EXIT_FAILURE);
    }

    /* consume the non-opt argument, the input file name */
    if (argv[optind] != NULL) {
        if ((in_fd = fopen(argv[optind], "r")) == NULL) {
                fprintf(stderr, "Cannot read from the input file : %s\n", 
                    argv[optind]);
                exit(EXIT_FAILURE);
        }
    }

    return EXIT_SUCCESS;
}