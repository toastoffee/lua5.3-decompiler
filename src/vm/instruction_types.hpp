/**
  ******************************************************************************
  * @file           : instruction_types.hpp
  * @author         : toastoffee
  * @brief          : None
  * @attention      : None
  * @date           : 2024/7/13
  ******************************************************************************
  */



#ifndef LUA5_3_DECOMPILER_INSTRUCTION_TYPES_HPP
#define LUA5_3_DECOMPILER_INSTRUCTION_TYPES_HPP

#include "../binChunk/chunk_types.hpp"


typedef uint32_t Instruction;

const int IABC = 0,     // x stands for (extended), s stands for (signed)
          IABx = 1,     // A usually used for target register index, B\C can be register index or constant pool index
          IAsBx = 2,
          IAx = 3;

const int OP_MOVE = 0,        OP_LOADK = 1,       OP_LOADKX = 2,      OP_LOADBOOL = 3,
          OP_LOADNIL = 4,     OP_GETUPVAL = 5,    OP_GETTABUP = 6,    OP_GETTABLE = 7,
          OP_SETTABUP = 8,    OP_SETUPVAL = 9,    OP_SETTABLE = 10,   OP_NEWTABLE = 11,
          OP_SELF = 12,       OP_ADD = 13,        OP_SUB = 14,        OP_MUL = 15,
          OP_MOD = 16,        OP_POW = 17,        OP_DIV = 18,        OP_IDIV = 19,
          OP_BAND = 20,       OP_BOR = 21,        OP_BXOR = 22,       OP_SHL = 23,
          OP_SHR = 24,        OP_UNM = 25,        OP_BNOT = 26,       OP_NOT = 27,
          OP_LEN = 28,        OP_CONCAT = 29,     OP_JMP = 30,        OP_EQ = 31,
          OP_LT = 32,         OP_LE = 33,         OP_TEST = 34,       OP_TESTSET = 35,
          OP_CALL = 36,       OP_TAILCALL = 37,   OP_RETURN = 38,     OP_FORLOOP = 39,
          OP_FORPREP = 40,    OP_TFORCALL = 41,   OP_TFORLOOP = 42,   OP_SETLIST = 43,
          OP_CLOSURE = 44,    OP_VARARG = 45,     OP_EXTRAARG = 46;

const int OpArgN = 0, // argument is not used
          OpArgU = 1, // argument is used
          OpArgR = 2, // argument is a register or a jump offset
          OpArgK = 3; // argument is a constant or register/constant



#endif //LUA5_3_DECOMPILER_INSTRUCTION_TYPES_HPP
