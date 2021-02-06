/*-
 * kestrelc.cpp
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

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>

#include "kestrelc.hpp"
#include "parseargs.hpp"

bool sflag;

void 
usage() {
    std::cerr << "usage: kestrelc -i source_file [-s] -o output_file";
    std::cerr << std::endl;
}

int 
main(int argc, char **argv) {
    std::ifstream in_file;
    std::ofstream out_file;
    std::string in_file_name, out_file_name;
    std::map<char, std::string> args;

    if (argc < 3){
        usage();
        exit(1);
    }
    
    try {
        args = parse_args(argc, argv, "i:o:s");
    } catch (std::invalid_argument& e) {
        std:: cerr << e.what() << std::endl;
        usage();
        exit(EXIT_FAILURE);
    }

    if (args.find('s') != args.end())
        sflag = true;

    in_file_name = args.at('i');
    out_file_name = args.at('o');

    in_file.open(in_file_name);
    if (in_file.is_open() == false) {
        std::cerr << "Unable to open file for reading: " + in_file_name;
        std::cerr << std::endl;
        exit(EXIT_FAILURE);
    }

    out_file.open(out_file_name);
    if (out_file.is_open() == false) {
        std::cerr << "Unable to open file for writing: " + in_file_name;
        std::cerr << std::endl;
        exit(EXIT_FAILURE);
    }

    in_file.close();
    out_file.close();

    return(EXIT_SUCCESS);
}
