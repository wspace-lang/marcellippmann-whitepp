/******************************************************************************
 * This file is part of White++.                                              *
 *                                                                            *
 * Written by Marcel Lippmann <marcel.lippmann@tu-dresden.de>.                *
 * Copyright (c) 2016 by Marcel Lippmann.  All rights reserved.               *
 *                                                                            *
 ******************************************************************************/
#include "VirtualMachine.h"

#include <iostream>

using namespace whitepp;


void VirtualMachine::visit(Push& instr) {

  stack_.emplace_back(instr.get_num());
  ++program_counter_;
}


void VirtualMachine::visit(Dupl& instr) {

  stack_.emplace_back(stack_.back());
  ++program_counter_;
}


void VirtualMachine::visit(Swap& instr) {

  auto const e1 = stack_.back();
  stack_.pop_back();

  auto const e2 = stack_.back();
  stack_.pop_back();

  stack_.emplace_back(e1);
  stack_.emplace_back(e2);

  ++program_counter_;
}


void VirtualMachine::visit(Discard& instr) {

  stack_.pop_back();
  ++program_counter_;
}


void VirtualMachine::visit(Add& instr) {

  auto const y = stack_.back();
  stack_.pop_back();

  auto const x = stack_.back();
  stack_.pop_back();

  stack_.emplace_back(x + y);

  ++program_counter_;
}


void VirtualMachine::visit(Sub& instr) {

  auto const y = stack_.back();
  stack_.pop_back();

  auto const x = stack_.back();
  stack_.pop_back();

  stack_.emplace_back(x - y);

  ++program_counter_;
}


void VirtualMachine::visit(Mul& instr) {

  auto const y = stack_.back();
  stack_.pop_back();

  auto const x = stack_.back();
  stack_.pop_back();

  stack_.emplace_back(x * y);

  ++program_counter_;
}


void VirtualMachine::visit(Div& instr) {

  auto const y = stack_.back();
  stack_.pop_back();

  auto const x = stack_.back();
  stack_.pop_back();

  stack_.emplace_back(x / y);

  ++program_counter_;
}


void VirtualMachine::visit(Mod& instr) {

  auto const y = stack_.back();
  stack_.pop_back();

  auto const x = stack_.back();
  stack_.pop_back();

  stack_.emplace_back(x % y);

  ++program_counter_;
}


void VirtualMachine::visit(Store& instr) {

  auto const x = stack_.back();
  stack_.pop_back();

  auto const l = stack_.back();
  stack_.pop_back();

  heap_[l] = x;

  ++program_counter_;
}


void VirtualMachine::visit(Retrieve& instr) {

  auto const l = stack_.back();
  stack_.pop_back();

  stack_.emplace_back(heap_[l]);

  ++program_counter_;
}


void VirtualMachine::visit(SetLbl& instr) {
  ++program_counter_;
}


void VirtualMachine::visit(CallLbl& instr) {

  call_stack_.emplace_back(program_counter_);

  program_counter_ = labels_[instr.get_label()];
}


void VirtualMachine::visit(Jump& instr) {

  program_counter_ = labels_[instr.get_label()];
}


void VirtualMachine::visit(JumpZero& instr) {

  if (stack_.back() == 0) {
    program_counter_ = labels_[instr.get_label()];
  } else {
    ++program_counter_;
  }

  stack_.pop_back();
}


void VirtualMachine::visit(JumpNeg& instr) {

  if (stack_.back() < 0) {

    program_counter_ = labels_[instr.get_label()];

  } else {

    ++program_counter_;
  }

  stack_.pop_back();
}


void VirtualMachine::visit(Ret& instr) {

  program_counter_ = call_stack_.back() + 1;
  call_stack_.pop_back();
}


void VirtualMachine::visit(End& instr) {

  // End by setting program counter to invalid position.
  program_counter_ = instructions_.size();
}


void VirtualMachine::visit(PrintChar& instr) {

  std::cout << static_cast<char>(stack_.back());
  stack_.pop_back();

  ++program_counter_;
}


void VirtualMachine::visit(PrintInt& instr) {

  std::cout << stack_.back();
  stack_.pop_back();

  ++program_counter_;
}


void VirtualMachine::visit(ReadChar& instr) {

  char c;
  std::cin.get(c);

  heap_[stack_.back()] = static_cast<int>(c);
  stack_.pop_back();

  ++program_counter_;
}


void VirtualMachine::visit(ReadInt& instr) {

  int i;
  std::cin >> i;

  heap_[stack_.back()] = i;
  stack_.pop_back();

  ++program_counter_;
}


void VirtualMachine::run() {

  if (finished_) {
    return;
  }

  // Perform the instructions.
  while (program_counter_ < instructions_.size()) {
    instructions_[program_counter_]->accept(*this);
  }

  finished_ = true;
}


void VirtualMachine::reset() {

  heap_.clear();
  stack_.clear();
  call_stack_.clear();

  program_counter_ = 0;

  finished_ = false;
}
