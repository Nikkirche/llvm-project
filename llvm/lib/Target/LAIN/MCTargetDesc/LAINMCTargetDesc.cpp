#include "MCTargetDesc/LAINInfo.h"
#include "LAIN.h"
#include "TargetInfo/LAINTargetInfo.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/TargetRegistry.h"

using namespace llvm;

#define GET_REGINFO_MC_DESC
#include "LAINGenRegisterInfo.inc"

#define GET_INSTRINFO_MC_DESC
#include "LAINGenInstrInfo.inc"

static MCRegisterInfo *createLAINMCRegisterInfo(const Triple &TT) {
  LAIN_DUMP_MAGENTA
  MCRegisterInfo *X = new MCRegisterInfo();
  InitLAINMCRegisterInfo(X, LAIN::R0);
  return X;
}

static MCInstrInfo *createLAINMCInstrInfo() {
  LAIN_DUMP_MAGENTA
  MCInstrInfo *X = new MCInstrInfo();
  InitLAINMCInstrInfo(X);
  return X;
}

// We need to define this function for linking succeed
extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeLAINTargetMC() {
  LAIN_DUMP_MAGENTA
  Target &TheLAINTarget = getTheLAINTarget();
  // Register the MC register info.
  TargetRegistry::RegisterMCRegInfo(TheLAINTarget, createLAINMCRegisterInfo);
  // Register the MC instruction info.
  TargetRegistry::RegisterMCInstrInfo(TheLAINTarget, createLAINMCInstrInfo);
}