#ifndef LLVM_LIB_TARGET_LAIN_LAINTARGETMACHINE_H
#define LLVM_LIB_TARGET_LAIN_LAINTARGETMACHINE_H

#include "LAINInstrInfo.h"
#include "LAINSubtarget.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {

class LAINTargetMachine : public LLVMTargetMachine {
  std::unique_ptr<TargetLoweringObjectFile> TLOF;
  LAINSubtarget Subtarget;

public:
  LAINTargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                     StringRef FS, const TargetOptions &Options,
                     std::optional<Reloc::Model> RM,
                     std::optional<CodeModel::Model> CM, CodeGenOptLevel OL,
                     bool JIT);
  ~LAINTargetMachine() override;

  const LAINSubtarget *getSubtargetImpl(const Function &) const override {
    return &Subtarget;
  }

  // Pass Pipeline Configuration
  TargetPassConfig *createPassConfig(PassManagerBase &PM) override;
  TargetLoweringObjectFile *getObjFileLowering() const override {
    return TLOF.get();
  }
};
} // end namespace llvm

#endif