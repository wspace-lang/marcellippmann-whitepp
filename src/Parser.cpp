/******************************************************************************
 * This file is part of White++.                                              *
 *                                                                            *
 * Written by Marcel Lippmann <marcel.lippmann@tu-dresden.de>.                *
 * Copyright (c) 2016 by Marcel Lippmann.  All rights reserved.               *
 *                                                                            *
 ******************************************************************************/
#include "Parser.h"

using namespace whitepp;


/**
 * This helper function checks whether string1 starts with string2.  If yes,
 * string1 is chopped.
 *
 * @param string1 A string.
 * @param string2 A string.
 * @returns true iff string1 starts with string2.
 */
bool starts_with(std::string& string1, std::string const& string2) {

  if (std::equal(std::cbegin(string2), std::cend(string2), std::cbegin(string1))) {

    string1.erase(0, string2.length());
    return true;

  } else {

    return false;
  }
}


/**
 * This helper function reads an integer value.
 *
 * In this process, the string is chopped.
 *
 * @param string A string.
 * @returns The read integer.
 * @throws std::runtime_error if no number can be read.
 */
int read_int(std::string& string) {

  try {

    if (string.at(0) == 'C') {
      throw std::runtime_error("Parsing error");
    }

    int sign = (string.at(0) == 'A') ? 1 : -1;
    int num = 0;

    int i;
    for (i = 1; string.at(i) != 'C'; ++i) {

      num *= 2;

      if (string.at(i) == 'B') {
        ++num;
      }
    }

    string.erase(0, i + 1);
    
    return sign * num;

  } catch (std::out_of_range const& e) {

    // No number can be read.
    throw std::runtime_error("Parsing error");
  }
}


std::string read_str(std::string& string) {

  try {

    if (string.at(0) == 'C') {
      throw std::runtime_error("Parsing error");
    }

    auto index = string.find('C');
    if (index != std::string::npos) {

      auto str = string.substr(0, index);
      string.erase(0, index + 1);

      return str;

    } else {

      throw std::runtime_error("Parsing error");
    }

  } catch (std::out_of_range const& e) {

    // No string can be read.
    throw std::runtime_error("Parsing error");
  }
}


void Parser::parse(std::string& tokens) {

  while (!tokens.empty()) {

    if (starts_with(tokens, "AA")) {

      // Push Integer
      int num = read_int(tokens);
      instructions_.emplace_back(std::make_shared<Push>(num));

    } else if (starts_with(tokens, "ACA")) {

      // Duplicate last
      instructions_.emplace_back(std::make_shared<Dupl>());

    } else if (starts_with(tokens, "ACB")) {

      // Swap last
      instructions_.emplace_back(std::make_shared<Swap>());
      
    } else if (starts_with(tokens, "ACC")) {

      // Discard
      instructions_.emplace_back(std::make_shared<Discard>());

    } else if (starts_with(tokens, "BAAA")) {

      // Add
      instructions_.emplace_back(std::make_shared<Add>());

    } else if (starts_with(tokens, "BAAB")) {

      // Substract
      instructions_.emplace_back(std::make_shared<Sub>());

    } else if (starts_with(tokens, "BAAC")) {

      // Multiply
      instructions_.emplace_back(std::make_shared<Mul>());

    } else if (starts_with(tokens, "BABA")) {

      // Divide
      instructions_.emplace_back(std::make_shared<Div>());

    } else if (starts_with(tokens, "BABB")) {

      // Modulo
      instructions_.emplace_back(std::make_shared<Mod>());

    } else if (starts_with(tokens, "BBA")) {

      // Store in heap
      instructions_.emplace_back(std::make_shared<Store>());

    } else if (starts_with(tokens, "BBB")) {

      // Retrieve from heap
      instructions_.emplace_back(std::make_shared<Retrieve>());

    } else if (starts_with(tokens, "BCAA")) {

      // Print Char
      instructions_.emplace_back(std::make_shared<PrintChar>());

    } else if (starts_with(tokens, "BCAB")) {

      // Print Integer
      instructions_.emplace_back(std::make_shared<PrintInt>());

    } else if (starts_with(tokens, "BCBA")) {

      // Read Char
      instructions_.emplace_back(std::make_shared<ReadChar>());

    } else if (starts_with(tokens, "BCBB")) {

      // Read Integer
      instructions_.emplace_back(std::make_shared<ReadInt>());

    } else if (starts_with(tokens, "CAA")) {

      // Set label
      std::string str = read_str(tokens); 

      auto ret = labels_.emplace(str, instructions_.size());
      if (!ret.second) {

        // Label already defined!
        throw std::runtime_error("Parsing error: Label already defined!");
      }

      instructions_.emplace_back(std::make_shared<SetLbl>(str));

    } else if (starts_with(tokens, "CAB")) {

      // Call label
      std::string str = read_str(tokens); 
      instructions_.emplace_back(std::make_shared<CallLbl>(str));

    } else if (starts_with(tokens, "CAC")) {

      // Jump to label
      std::string str = read_str(tokens); 
      instructions_.emplace_back(std::make_shared<Jump>(str));

    } else if (starts_with(tokens, "CBA")) {

      // Jump to label if zero
      std::string str = read_str(tokens); 
      instructions_.emplace_back(std::make_shared<JumpZero>(str));

    } else if (starts_with(tokens, "CBB")) {

      // Jump to label if negative
      std::string str = read_str(tokens); 
      instructions_.emplace_back(std::make_shared<JumpNeg>(str));

    } else if (starts_with(tokens, "CBC")) {

      // Return
      instructions_.emplace_back(std::make_shared<Ret>());

    } else if (starts_with(tokens, "CCC")) {

      // End
      instructions_.emplace_back(std::make_shared<End>());

    } else {

      // No valid command.
      throw std::runtime_error("Parsing error");
    }
  }
}


std::ostream& whitepp::operator<<(std::ostream& os, Instruction const& instr) {

  os << instr.to_str();
  return os;
}


void Push::accept(InstructionVisitor& visitor) {
  visitor.visit(*this);
}


void Dupl::accept(InstructionVisitor& visitor) {
  visitor.visit(*this);
}


void Swap::accept(InstructionVisitor& visitor) {
  visitor.visit(*this);
}


void Discard::accept(InstructionVisitor& visitor) {
  visitor.visit(*this);
}


void Add::accept(InstructionVisitor& visitor) {
  visitor.visit(*this);
}


void Sub::accept(InstructionVisitor& visitor) {
  visitor.visit(*this);
}


void Mul::accept(InstructionVisitor& visitor) {
  visitor.visit(*this);
}


void Div::accept(InstructionVisitor& visitor) {
  visitor.visit(*this);
}


void Mod::accept(InstructionVisitor& visitor) {
  visitor.visit(*this);
}


void Store::accept(InstructionVisitor& visitor) {
  visitor.visit(*this);
}


void Retrieve::accept(InstructionVisitor& visitor) {
  visitor.visit(*this);
}


void SetLbl::accept(InstructionVisitor& visitor) {
  visitor.visit(*this);
}


void CallLbl::accept(InstructionVisitor& visitor) {
  visitor.visit(*this);
}


void Jump::accept(InstructionVisitor& visitor) {
  visitor.visit(*this);
}


void JumpZero::accept(InstructionVisitor& visitor) {
  visitor.visit(*this);
}


void JumpNeg::accept(InstructionVisitor& visitor) {
  visitor.visit(*this);
}


void Ret::accept(InstructionVisitor& visitor) {
  visitor.visit(*this);
}


void End::accept(InstructionVisitor& visitor) {
  visitor.visit(*this);
}


void PrintChar::accept(InstructionVisitor& visitor) {
  visitor.visit(*this);
}


void PrintInt::accept(InstructionVisitor& visitor) {
  visitor.visit(*this);
}


void ReadChar::accept(InstructionVisitor& visitor) {
  visitor.visit(*this);
}


void ReadInt::accept(InstructionVisitor& visitor) {
  visitor.visit(*this);
}
