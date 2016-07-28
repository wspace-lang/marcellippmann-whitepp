/******************************************************************************
 * This file is part of White++.                                              *
 *                                                                            *
 * Written by Marcel Lippmann <marcel.lippmann@tu-dresden.de>.                *
 * Copyright (c) 2016 by Marcel Lippmann.  All rights reserved.               *
 *                                                                            *
 ******************************************************************************/
#ifndef VIRTUALMACHINE_H_
#define VIRTUALMACHINE_H_

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "Parser.h"


namespace whitepp {

/**
 * This class represents a virtual machine.
 */
class VirtualMachine : public InstructionVisitor {

private:

  /**
   * The set of instructions, i.e. the program.
   */
  instructions_t instructions_;


  /**
   * A map where to find labels in the instructions vector.
   */
  std::map<std::string, int> labels_;


  //
  // The VM state.
  //

  /**
   * The heap.
   */
  std::map<int, int> heap_;


  /**
   * The stack.
   */
  std::vector<int> stack_;


  /**
   * The call stack.
   */
  std::vector<int> call_stack_;


  /**
   * The program counter.
   */
  unsigned int program_counter_;


  /**
   * Once run() was called, it cannot be called again.
   */
  bool finished_;


  //
  // Abstract methods inherited from InstructionVisitor.
  //

  virtual void visit(Push& instr) override;
  virtual void visit(Dupl& instr) override;
  virtual void visit(Swap& instr) override;
  virtual void visit(Discard& instr) override;
  virtual void visit(Add& instr) override;
  virtual void visit(Sub& instr) override;
  virtual void visit(Mul& instr) override;
  virtual void visit(Div& instr) override;
  virtual void visit(Mod& instr) override;
  virtual void visit(Store& instr) override;
  virtual void visit(Retrieve& instr) override;
  virtual void visit(SetLbl& instr) override;
  virtual void visit(CallLbl& instr) override;
  virtual void visit(Jump& instr) override;
  virtual void visit(JumpZero& instr) override;
  virtual void visit(JumpNeg& instr) override;
  virtual void visit(Ret& instr) override;
  virtual void visit(End& instr) override;
  virtual void visit(PrintChar& instr) override;
  virtual void visit(PrintInt& instr) override;
  virtual void visit(ReadChar& instr) override;
  virtual void visit(ReadInt& instr) override;


public:

  /**
   * The standard constructor.
   */
  VirtualMachine(instructions_t const& instructions,
                 std::map<std::string, int> const& labels) :
      instructions_(instructions), labels_(labels), program_counter_(0), finished_(false) {}


  /**
   * The destructor.
   */
  ~VirtualMachine() {}


  /**
   * Run the virtual machine.
   */
  void run();


  /**
   * Reset the virtual machine.
   */
  void reset();

};

} // namespace whitepp


#endif // VIRTUALMACHINE_H_
