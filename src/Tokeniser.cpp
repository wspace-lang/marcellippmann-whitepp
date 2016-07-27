/******************************************************************************
 * This file is part of White++.                                              *
 *                                                                            *
 * Written by Marcel Lippmann <marcel.lippmann@tu-dresden.de>.                *
 * Copyright (c) 2016 by Marcel Lippmann.  All rights reserved.               *
 *                                                                            *
 ******************************************************************************/
#include "Tokeniser.h"

using namespace whitepp;


void Tokeniser::tokenise(std::istream& in) {

  while (in.good() && !in.eof()) {
      
    char const c = in.get();
    if (c == ' ') {
      tokens_ += "A";
    } else if (c == '\t') {
      tokens_ += "B";
    } else if (c == '\n') {
      tokens_ += "C";
    }
  }
}
