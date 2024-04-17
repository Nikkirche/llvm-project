#include "TargetInfo/LAINTargetInfo.h"
#include "LAIN.h"
#include "llvm/MC/TargetRegistry.h"
using namespace llvm;

Target &llvm::getTheLAINTarget() {
  LAIN_DUMP_YELLOW
  static Target TheLAINTarget;
  return TheLAINTarget;
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeLAINTargetInfo() {
  LAIN_DUMP_YELLOW
  RegisterTarget<Triple::lain> X(getTheLAINTarget(), "lain","Simple learning architecture",
                                   "LAIN");
}