#ifndef LLVM_LIB_TARGET_LAIN_MCTARGETDESC_LAININFO_H
#define LLVM_LIB_TARGET_LAIN_MCTARGETDESC_LAININFO_H

#include "llvm/MC/MCInstrDesc.h"

namespace llvm {

namespace LAINOp {
enum OperandType : unsigned {
  OPERAND_LAINM16 = MCOI::OPERAND_FIRST_TARGET,
};
} // namespace LAINOp

} // end namespace llvm

#endif