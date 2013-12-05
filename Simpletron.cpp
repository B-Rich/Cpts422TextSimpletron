// Author: Andrew S. O'Fallon

#include "Simpletron.h"

Simpletron::Simpletron (int newProgramSize, int newDataSize)
{
	mProgramMemoryPtr = new SmlInstruction[newProgramSize];
	mDataMemoryPtr = new int[newDataSize];
	for (int i = 0; i < newDataSize; i++)
	{
		mDataMemoryPtr[i] = 0;
	}
	mAccumulator = 0;
	mInstructionCounter = 0;
	mProgramSize = newProgramSize;
	mDataSize = newDataSize;
	mOperand = 0;
	mOpcode = (OpcodeType) 0;
}

Simpletron::~Simpletron ()
{
	delete [] mProgramMemoryPtr;
	delete [] mDataMemoryPtr;
}

Simpletron & Simpletron::operator= (const Simpletron &rhs)
{
	if (this != &rhs)
	{
		mProgramMemoryPtr = rhs.getProgramMemoryPtr ();
		mAccumulator = rhs.getAccumulator ();
		mInstructionCounter = rhs.getInstructionCounter ();
		mInstructionRegister = rhs.getInstructionRegister ();
		mProgramSize = rhs.getProgramSize ();
		mOpcode = rhs.getOpcode ();
		mOperand = rhs.getOperand ();
	}

	return *this;
}

// getters / accessors
SmlInstruction * Simpletron::getProgramMemoryPtr () const
{
	return mProgramMemoryPtr;
}

int * Simpletron::getDataMemoryPtr () const
{
	return mDataMemoryPtr;
}

int Simpletron::getAccumulator () const
{
	return mAccumulator;
}

int Simpletron::getInstructionCounter () const
{
	return mInstructionCounter;
}

SmlInstruction Simpletron::getInstructionRegister () const
{
	return mInstructionRegister;
}

int Simpletron::getProgramSize () const
{
	return mProgramSize;
}

int Simpletron::getDataSize () const
{
	return mDataSize;
}

OpcodeType Simpletron::getOpcode () const
{
	return mOpcode;
}

int Simpletron::getOperand () const
{
	return mOperand;
}

// setters / mutators
void Simpletron::setProgramMemoryPtr (SmlInstruction *newProgramMemoryPtr)
{
	mProgramMemoryPtr = newProgramMemoryPtr;
}

void Simpletron::setDataMemoryPtr (int *newDataMemoryPtr)
{
	mDataMemoryPtr = newDataMemoryPtr;
}

void Simpletron::setAccumulator (int newAccumulator)
{
	mAccumulator = newAccumulator;
}

void Simpletron::setInstructionCounter (int newInstructionCounter)
{
	mInstructionCounter = newInstructionCounter;
}

void Simpletron::setInstructionRegister (SmlInstruction newInstructionRegister)
{
	mInstructionRegister = newInstructionRegister;
}

void Simpletron::setProgramSize (int newProgramSize)
{
	mProgramSize = newProgramSize;
}

void Simpletron::setDataSize (int newDataSize)
{
	mDataSize = newDataSize;
}

void Simpletron::setOpcode (OpcodeType newOpcode)
{
	mOpcode = newOpcode;
}

void Simpletron::setOperand (int newOperand)
{
	mOperand = newOperand;
}

// Get the instruction from program memory
// Increment the instruction counter
void Simpletron::fetch ()
{
	mInstructionRegister = mProgramMemoryPtr[mInstructionCounter];
	mInstructionCounter++;
}

// Split the SML instruction into the opcode and operand
void Simpletron::decode ()
{
	mOpcode = mInstructionRegister.getOpcode ();
	mOperand = mInstructionRegister.getOperand ();
	mInstructionCounter++;
}

// Carry out the appropriate operation based on the opcode
void Simpletron::execute ()
{
	switch (mOpcode)
	{
		case READ: cout << ">> ";
				   cin >> mDataMemoryPtr[mOperand];
				   break;
		case WRITE: cout << "<< " << mDataMemoryPtr[mOperand] << endl;
			        break;
		case LOAD: mAccumulator = mDataMemoryPtr[mOperand];
			       break;
		case STORE: mDataMemoryPtr[mOperand] = mAccumulator;
			        break;
		case ADD: mAccumulator += mDataMemoryPtr[mOperand];
			      break;
		case SUBTRACT: mAccumulator -= mDataMemoryPtr[mOperand];
			           break;
		case DIVIDE: mAccumulator /= mDataMemoryPtr[mOperand];
			         break;
		case MULTIPLY: mAccumulator *= mDataMemoryPtr[mOperand];
			           break;
		case MOD: mAccumulator %= mDataMemoryPtr[mOperand];
			      break;
		case EXP: mAccumulator = (int) pow ((double) mDataMemoryPtr[mOperand], (double) mAccumulator);
			      break;
		case BRANCH: mInstructionCounter = mAccumulator;
			         break;
		case BRANCHNEG: if (mAccumulator < 0)
						{
							mInstructionCounter = mOperand;
						}
			            break;
		case BRANCHZERO: if (mAccumulator == 0)
						 {
							 mInstructionCounter = mOperand;
						 }
			             break;
		case HALT: // done
			       exit (0);
			       break;
		default: cout << "ERROR: Invalid instruction. Exiting program!" << endl;
				 exit (1);
			     break;
	}

	system ("pause");
	dumpMemory ();
}

void Simpletron::dumpMemory ()
{
	int index = 0;
	SmlInstruction *tempPtr = this->getProgramMemoryPtr ();
	
	system ("cls");

	cout << "REGISTERS:" << endl;
	printf ("%-20s%+20.5d\n", "Accumulator", mAccumulator);
	if (mInstructionCounter != 0)
	{
		printf ("%-20s%+20.5d\n", "InstructionCounter", mInstructionCounter - 1);
	}
	else
	{
		printf ("%-20s%+20.5d\n", "InstructionCounter", mInstructionCounter);

	}
	printf ("%-20s%+17.2d%.3d\n", "InstructionRegister", mOpcode, mOperand);
	printf ("%-20s%+20.5d\n", "OperationCode", mOpcode);
	printf ("%-20s%+20.5d\n", "Operand", mOperand);
	cout << endl;


	cout << "PROGRAM MEMORY:" << endl;
	while ((index < (this->getProgramSize ())) && (tempPtr[index].getOpcode () != NO_OP))
	{
		cout << tempPtr[index++] << " ";
		if ((index % 10) == 0)
		{
			cout << endl;
		}
	}
	cout << endl;
	index = 0;
	int *dataPtr = this->getDataMemoryPtr ();

	cout << "DATA MEMORY:" << endl;
	while (index < 100)
	{
		printf ("%+5.4d ", dataPtr[index++]);
		if ((index % 10) == 0)
		{
			cout << endl;
		}
	}
	cout << endl;
}