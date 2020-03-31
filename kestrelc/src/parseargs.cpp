/*-
 * parseargs.cpp
 * 
 * Copyright (c) 2020 Fehmi Noyan Isi
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
#include <stdexcept>
#include <utility>

#include "parseargs.hpp"

#define PROG_NAME_KEY  '%'

std::string extract_file_name(char *str) {
    char sep = '/';
    std::string s(str);

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && \
    !defined(__CYGWIN__)
    sep = '\\';
#endif

    auto i = s.find_last_of(sep);

    if (i == std::string::npos) 
        return s;   
   else
        return(s.substr(i+1, s.length() - i));
}

// returns a std::map with key set to command line options and values 
// set to corresponding option argument.
// for options without a following argument, an empty std::string is
// used as the option argument
// optarg() style formatting string is used as the last parameter to
// distinguish parameters with and without an argument
// the key for the program name (i.e. argv[0]) is PROG_NAME_KEY
std::map<char, std::string> parse_args(int argc, char **argv, std::string l) {
    std::map<char, std::string> args;

    std::string prog_name = extract_file_name(argv[0]);
    args.insert(std::pair<char, std::string>(PROG_NAME_KEY, prog_name));

    // rest of the command line arguments
    for (int i=1; i<argc; i++){
        std::string argv_i(argv[i]);
        char ch = argv_i.at(0);

        if (ch == '-') {
            if (argv_i.size() != 2)
                throw std::invalid_argument("Invalid argumet: " + argv_i);

            // fetch the next arg
            if (i < argc) {
                char opt = argv_i.at(1);
                size_t pos = l.find(opt);
                bool has_valarg;
                std::string val;

                if (pos == std::string::npos) 
                    throw std::invalid_argument("Invalid argumet: " + argv_i);

                if (pos+1 < l.size())                    
                    has_valarg = (l.at(pos+1) == ':');
                else
                    has_valarg = false;

                if (has_valarg) {
                    std::string arg_n(argv[++i]);

                    if (arg_n.at(0) == '-' || arg_n.size() == 0)
                        throw std::invalid_argument("Option must be followed "
                            "by a value");                 

                    val = arg_n;                
                } else {
                    val = "";
                }
                auto p = std::make_pair(opt, val);
                args.insert(p);
            } 
        } else
            throw std::invalid_argument("Invalid argumet: " + argv_i);
    }
    return args;
}