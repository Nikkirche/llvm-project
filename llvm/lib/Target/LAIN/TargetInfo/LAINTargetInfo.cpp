#include "TargetInfo/LAINTargetInfo.h"
#include "llvm/MC/TargetRegistry.h"
using namespace llvm;

Target &llvm::getTheLAINTarget() {
  static Target TheLAINTarget;
  return TheLAINTarget;
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeLAINTargetInfo() {
  RegisterTarget<Triple::lain> X(getTheLAINTarget(), "LAIN", "LAIN 32",
                                   "lain");
}