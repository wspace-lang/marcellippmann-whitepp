/******************************************************************************
 * This file is part of White++.                                              *
 *                                                                            *
 * Written by Marcel Lippmann <marcel.lippmann@tu-dresden.de>.                *
 * Copyright (c) 2016 by Marcel Lippmann.  All rights reserved.               *
 *                                                                            *
 ******************************************************************************/
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

#include "Parser.h"
#include "Tokeniser.h"
#include "VirtualMachine.h"


using namespace whitepp;


void print_usage(std::string const& prgName, std::string const& errorMsg) {

  std::cout << "Usage: "   << prgName  << "FILE" << std::endl
            << "This program is a whitespace interpreter." << std::endl
            << "FILE is a whitespace program." << std::endl
            << "  Error: " << errorMsg << std::endl;
}


int main(int argc, char const* argv[]) {

  std::string prgName = argv[0];

  if (argc != 2) {
    print_usage(prgName, "Please specify one argument.");
    return EXIT_FAILURE;
  }

  //
  // Get tokens.
  //

  Tokeniser tokeniser;

  std::ifstream filestream(argv[1]);
  tokeniser.tokenise(filestream);
  filestream.close();

  auto tokens = tokeniser.get_tokens();

  //
  // Parse tokens.
  //

  Parser parser;

  try {

    parser.parse(tokens);

  } catch (std::runtime_error const& e) {

    print_usage(prgName, e.what());
    return EXIT_FAILURE;
  }

  //
  // Run virtual machine.
  //

  VirtualMachine vm(parser.get_instructions(), parser.get_labels());

  vm.run();

  return EXIT_SUCCESS;
}
