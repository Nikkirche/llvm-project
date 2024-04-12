//===----------------------------------------------------------------------===//
//
// Implements the info about LAIN target spec.
//
//===----------------------------------------------------------------------===//

#include "LAINTargetMachine.h"
#include "LAIN.h"
#include "TargetInfo/LAINTargetInfo.h"
#include "llvm/CodeGen/Passes.h"
#include "llvm/CodeGen/TargetLoweringObjectFileImpl.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/IR/Attributes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/CodeGen.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Target/TargetOptions.h"

#define DEBUG_TYPE "LAIN"

using namespace llvm;

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeLAINTarget() {
  // Register the target.
  LAIN_DUMP_CYAN
  RegisterTargetMachine<LAINTargetMachine> A(getTheLAINTarget());
}

LAINTargetMachine::LAINTargetMachine(const Target &T, const Triple &TT,
                                   StringRef CPU, StringRef FS,
                                   const TargetOptions &Options,
                                   std::optional<Reloc::Model> RM,
                                   std::optional<CodeModel::Model> CM,
                                   CodeGenOptLevel OL, bool JIT)
    : LLVMTargetMachine(T, "e-m:e-p:32:32-i8:8:32-i16:16:32-i64:64-n32", TT,
                        CPU, FS, Options, Reloc::Static,
                        getEffectiveCodeModel(CM, CodeModel::Small), OL),
      TLOF(std::make_unique<TargetLoweringObjectFileELF>()),
      Subtarget(TT, std::string(CPU), std::string(FS), *this) {
  initAsmInfo();
}

LAINTargetMachine::~LAINTargetMachine() = default;

namespace {

/// LAIN Code Generator Pass Configuration Options.
class LAINPassConfig : public TargetPassConfig {
public:
  LAINPassConfig(LAINTargetMachine &TM, PassManagerBase &PM)
      : TargetPassConfig(TM, PM) {}

  LAINTargetMachine &getLAINTargetMachine() const {
    return getTM<LAINTargetMachine>();
  }

  bool addInstSelector() override;
};

} // end anonymous namespace

TargetPassConfig *LAINTargetMachine::createPassConfig(PassManagerBase &PM) {
  return new LAINPassConfig(*this, PM);
}

bool LAINPassConfig::addInstSelector() {
  addPass(createLAINISelDag(getLAINTargetMachine()));
  return false;
}