/******************************************************************************
 * This file is part of White++.                                              *
 *                                                                            *
 * Written by Marcel Lippmann <marcel.lippmann@tu-dresden.de>.                *
 * Copyright (c) 2016 by Marcel Lippmann.  All rights reserved.               *
 *                                                                            *
 ******************************************************************************/
#ifndef TOKENISER_H_
#define TOKENISER_H_

#include <istream>
#include <string>


namespace whitepp {

/**
 * This class implements the tokeniser.
 */
class Tokeniser {

private:

  /**
   * The tokens recognised.
   */
  std::string tokens_;


public:

  /**
   * The standard constructor.
   */
  Tokeniser() {}


  /**
   * The destructor.
   */
  ~Tokeniser() {}


  /**
   * This method adds recognised tokens from the input stream to an internal
   * field.
   *
   * @param in The input stream.
   */
  void tokenise(std::istream& in);


  /**
   * @returns The tokens recognised.
   */
  std::string const& get_tokens() const {
    return tokens_;
  }

};

} // namespace whitepp


#endif // TOKENISER_H_
