// Author: Andrew S. O'Fallon
//
// Description: This program implements a simulator which is capable of interpreting 
// Simpletron Machine Language (SML) instructions. These instructions consist of the
// following: no operation, read, write, load, store, add, subtract, divide, multiply, 
// modulus, exponentiation, branch, branch if result is negative, branch if result is zero, 
// and halt.
//
// The simulator performs fetch/decode/execute instruction cycle on
// each instruction encountered in program memory. An instruction
// fetch is performed by accessing program memory based on
// where the instruction counter refers, and placing the instruction
// obtained into the instruction register. Decode splits
// the instruction register into two parts: operation code (opcode)
// and operand(s). Execute carries out the operation specified by the opcode.
//
// The simulator ends when a "halt" instruction is encountered.
//

#include "SimApp.h"

int main (void)
{
	SimApp simulator;

	simulator.runApp ();
		
	return 0;
}