#ifndef LLVM_LIB_TARGET_LAIN_MCTARGETDESC_LAININFO_H
#define LLVM_LIB_TARGET_LAIN_MCTARGETDESC_LAININFO_H

#include "llvm/MC/MCInstrDesc.h"

namespace llvm {
namespace LAINCC {
enum CondCode {
  EQ,
  NE,
  LE,
  GT,
  LEU,
  GTU,
  INVALID,
};

CondCode getOppositeBranchCondition(CondCode);

enum BRCondCode {
  BREQ = 0x0,
};
}

namespace LAINOp {
enum OperandType : unsigned {
  OPERAND_SIMM16 = MCOI::OPERAND_FIRST_TARGET,
  OPERAND_UIMM16
};
} // namespace LAINOp

} // end namespace llvm

#endif