/******************************************************************************
 * This file is part of White++.                                              *
 *                                                                            *
 * Written by Marcel Lippmann <marcel.lippmann@tu-dresden.de>.                *
 * Copyright (c) 2016 by Marcel Lippmann.  All rights reserved.               *
 *                                                                            *
 ******************************************************************************/
#ifndef PARSER_H_
#define PARSER_H_

#include <map>
#include <memory>
#include <stdexcept>
#include <ostream>
#include <vector>

#include "Tokeniser.h"


namespace whitepp {

/**
 * Forward declaration for the visitor.
 */
class InstructionVisitor;


/**
 * This class specifies the valid instructions.
 */
class Instruction {

protected:

  /**
   * The standard constructor.
   */
  Instruction() {}


public:

  /**
   * The destructor.
   */
  virtual ~Instruction() {}


  /**
   * @param The visitor.
   */
  virtual void accept(InstructionVisitor& visitor) = 0;


  /**
   * @returns A string representation of the instruction.
   */
  virtual std::string to_str() const = 0;

};


/**
 * Override the << operator for Instruction.
 */
std::ostream& operator<<(std::ostream& os, Instruction const& instr);

  
/**
 * Push Integer
 */
class Push : public Instruction {

private:

  int num_;


public:

	/**
	 * The default constructor.
	 */
  Push(int const num) : num_(num) {}


	/**
	 * The destructor.
	 */
  virtual ~Push() {}


  /**
   * @returns The stored integer.
   */
  int get_num() const {
    return num_;
  }


  virtual void accept(InstructionVisitor& visitor) override;


  virtual std::string to_str() const override {
    return "Push " + std::to_string(num_);
  }

};


/**
 * Duplicate last
 */
class Dupl : public Instruction {

public:

	/**
	 * The default constructor.
	 */
	Dupl() {}


	/**
	 * The destructor.
	 */
	virtual ~Dupl() {}


  virtual void accept(InstructionVisitor& visitor) override;


  virtual std::string to_str() const override {
    return "Dupl";
  }

};
  

/**
 * Swap last
 */
class Swap : public Instruction {

public:

	/**
	 * The default constructor.
	 */
	Swap() {}


	/**
	 * The destructor.
	 */
	virtual ~Swap() {}


  virtual void accept(InstructionVisitor& visitor) override;


  virtual std::string to_str() const override {
    return "Swap";
  }

};


/**
 * Discard
 */
class Discard : public Instruction {

public:

	/**
	 * The default constructor.
	 */
	Discard() {}


	/**
	 * The destructor.
	 */
	virtual ~Discard() {}


  virtual void accept(InstructionVisitor& visitor) override;


  virtual std::string to_str() const override {
    return "Discard";
  }

};


/**
 * Add
 */
class Add : public Instruction {

public:

	/**
	 * The default constructor.
	 */
	Add() {}


	/**
	 * The destructor.
	 */
	virtual ~Add() {}


  virtual void accept(InstructionVisitor& visitor) override;


  virtual std::string to_str() const override {
    return "Add";
  }

};


/**
 * Substract
 */
class Sub : public Instruction {

public:

	/**
	 * The default constructor.
	 */
	Sub() {}


	/**
	 * The destructor.
	 */
	virtual ~Sub() {}


  virtual void accept(InstructionVisitor& visitor) override;


  virtual std::string to_str() const override {
    return "Sub";
  }

};


/**
 * Multiply
 */
class Mul : public Instruction {

public:

	/**
	 * The default constructor.
	 */
	Mul() {}


	/**
	 * The destructor.
	 */
	virtual ~Mul() {}


  virtual void accept(InstructionVisitor& visitor) override;


  virtual std::string to_str() const override {
    return "Mul";
  }

};


/**
 * Divide
 */
class Div : public Instruction {

public:

	/**
	 * The default constructor.
	 */
	Div() {}


	/**
	 * The destructor.
	 */
	virtual ~Div() {}


  virtual void accept(InstructionVisitor& visitor) override;


  virtual std::string to_str() const override {
    return "Div";
  }

};


/**
 * Modulo
 */
class Mod : public Instruction {

public:

	/**
	 * The default constructor.
	 */
	Mod() {}


	/**
	 * The destructor.
	 */
	virtual ~Mod() {}


  virtual void accept(InstructionVisitor& visitor) override;


  virtual std::string to_str() const override {
    return "Mod";
  }

};


/**
 * Store in heap
 */
class Store : public Instruction {

public:

	/**
	 * The default constructor.
	 */
	Store() {}


	/**
	 * The destructor.
	 */
	virtual ~Store() {}


  virtual void accept(InstructionVisitor& visitor) override;


  virtual std::string to_str() const override {
    return "Store";
  }

};


/**
 * Retrieve from heap
 */
class Retrieve : public Instruction {

public:

	/**
	 * The default constructor.
	 */
	Retrieve() {}


	/**
	 * The destructor.
	 */
	virtual ~Retrieve() {}


  virtual void accept(InstructionVisitor& visitor) override;


  virtual std::string to_str() const override {
    return "Retrieve";
  }

};

/**
 * Set label
 */
class SetLbl : public Instruction {

private:

  std::string label_;


public:

	/**
	 * The default constructor.
	 */
	SetLbl(std::string const& label) : label_(label) {}


	/**
	 * The destructor.
	 */
	virtual ~SetLbl() {}


  virtual void accept(InstructionVisitor& visitor) override;


  virtual std::string to_str() const override {
    return "SetLbl " + label_;
  }

};


/**
 * Call label
 */
class CallLbl : public Instruction {

private:

  std::string label_;


public:

	/**
	 * The default constructor.
	 */
	CallLbl(std::string const& label) : label_(label) {}


	/**
	 * The destructor.
	 */
	virtual ~CallLbl() {}


  /**
   * @returns The label.
   */
  std::string const& get_label() const {
    return label_;
  }


  virtual void accept(InstructionVisitor& visitor) override;


  virtual std::string to_str() const override {
    return "CallLbl " + label_;
  }

};


/**
 * Jump to label
 */
class Jump : public Instruction {

private:

  std::string label_;


public:

	/**
	 * The default constructor.
	 */
	Jump(std::string const& label) : label_(label) {}


	/**
	 * The destructor.
	 */
	virtual ~Jump() {}


  /**
   * @returns The label.
   */
  std::string const& get_label() const {
    return label_;
  }


  virtual void accept(InstructionVisitor& visitor) override;


  virtual std::string to_str() const override {
    return "Jump " + label_;
  }

};


/**
 * Jump to label if zero
 */
class JumpZero : public Instruction {

private:

  std::string label_;


public:

	/**
	 * The default constructor.
	 */
	JumpZero(std::string const& label) : label_(label) {}


	/**
	 * The destructor.
	 */
	virtual ~JumpZero() {}


  /**
   * @returns The label.
   */
  std::string const& get_label() const {
    return label_;
  }


  virtual void accept(InstructionVisitor& visitor) override;


  virtual std::string to_str() const override {
    return "JumpZero " + label_;
  }

};


/**
 * Jump to label if negative
 */
class JumpNeg : public Instruction {

private:

  std::string label_;


public:

	/**
	 * The default constructor.
	 */
	JumpNeg(std::string const& label) : label_(label) {}


	/**
	 * The destructor.
	 */
	virtual ~JumpNeg() {}


  /**
   * @returns The label.
   */
  std::string const& get_label() const {
    return label_;
  }


  virtual void accept(InstructionVisitor& visitor) override;


  virtual std::string to_str() const override {
    return "JumpNeg " + label_;
  }

};


/**
 * Return
 */
class Ret : public Instruction {

public:

	/**
	 * The default constructor.
	 */
	Ret() {}


	/**
	 * The destructor.
	 */
	virtual ~Ret() {}


  virtual void accept(InstructionVisitor& visitor) override;


  virtual std::string to_str() const override {
    return "Ret";
  }

};


/**
 * End
 */
class End : public Instruction {

public:

	/**
	 * The default constructor.
	 */
	End() {}


	/**
	 * The destructor.
	 */
	virtual ~End() {}


  virtual void accept(InstructionVisitor& visitor) override;


  virtual std::string to_str() const override {
    return "End";
  }

};


/**
 * Print char
 */
class PrintChar : public Instruction {

public:

	/**
	 * The default constructor.
	 */
	PrintChar() {}


	/**
	 * The destructor.
	 */
	virtual ~PrintChar() {}


  virtual void accept(InstructionVisitor& visitor) override;


  virtual std::string to_str() const override {
    return "PrintChar";
  }

};


/**
 * Print int
 */
class PrintInt : public Instruction {

public:

	/**
	 * The default constructor.
	 */
	PrintInt() {}


	/**
	 * The destructor.
	 */
	virtual ~PrintInt() {}


  virtual void accept(InstructionVisitor& visitor) override;


  virtual std::string to_str() const override {
    return "PrintInt";
  }

};


/**
 * Read char
 */
class ReadChar : public Instruction {

public:

	/**
	 * The default constructor.
	 */
	ReadChar() {}


	/**
	 * The destructor.
	 */
	virtual ~ReadChar() {}


  virtual void accept(InstructionVisitor& visitor) override;


  virtual std::string to_str() const override {
    return "ReadChar";
  }

};


/**
 * Read int
 */
class ReadInt : public Instruction {

public:

	/**
	 * The default constructor.
	 */
	ReadInt() {}


	/**
	 * The destructor.
	 */
	virtual ~ReadInt() {}


  virtual void accept(InstructionVisitor& visitor) override;


  virtual std::string to_str() const override {
    return "ReadInt";
  }

};


/**
 * This class is an abstract interface for visiting instructions.
 */
class InstructionVisitor {

public:

  virtual void visit(Push& instr) = 0;
  virtual void visit(Dupl& instr) = 0;
  virtual void visit(Swap& instr) = 0;
  virtual void visit(Discard& instr) = 0;
  virtual void visit(Add& instr) = 0;
  virtual void visit(Sub& instr) = 0;
  virtual void visit(Mul& instr) = 0;
  virtual void visit(Div& instr) = 0;
  virtual void visit(Mod& instr) = 0;
  virtual void visit(Store& instr) = 0;
  virtual void visit(Retrieve& instr) = 0;
  virtual void visit(SetLbl& instr) = 0;
  virtual void visit(CallLbl& instr) = 0;
  virtual void visit(Jump& instr) = 0;
  virtual void visit(JumpZero& instr) = 0;
  virtual void visit(JumpNeg& instr) = 0;
  virtual void visit(Ret& instr) = 0;
  virtual void visit(End& instr) = 0;
  virtual void visit(PrintChar& instr) = 0;
  virtual void visit(PrintInt& instr) = 0;
  virtual void visit(ReadChar& instr) = 0;
  virtual void visit(ReadInt& instr) = 0;

};


/**
 * This type defines a sequence of instructions.
 */
typedef std::vector<std::shared_ptr<Instruction>> instructions_t;


/**
 * This class implements the parser.
 */
class Parser {

private:

  /**
   * The instructions parsed.
   */
  instructions_t instructions_;


  /**
   * A map where to find labels in the instructions vector.
   */
  std::map<std::string, int> labels_;


public:

  /**
   * The standard constructor.
   */
  Parser() {}


  /**
   * The destructor.
   */
  ~Parser() {}


  /**
   * This method parses the given tokens and stores the instructions in a
   * field.
   *
   * @param tokens The tokens to parse.
   * @throws std::runtime_error if tokens cannot be parsed successfully.
   */
  void parse(std::string& tokens);


  /**
   * @returns The instructions parsed.
   */
  instructions_t const& get_instructions() const {
    return instructions_;
  }


  /**
   * @returns The labels parsed.
   */
  std::map<std::string, int> const& get_labels() const {
    return labels_;
  }
};

} // namespace whitepp


#endif // PARSER_H_
