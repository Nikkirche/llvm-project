#include "LAINMCTargetDesc.h"
#include "LAIN.h"
#include "LAINInfo.h"
#include "LAINInstPrinter.h"
#include "LAINMCAsmInfo.h"
#include "LAINTargetStreamer.h"
#include "TargetInfo/LAINTargetInfo.h"
#include "TargetInfo/LAINTargetInfo.h"
#include "llvm/MC/MCDwarf.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/FormattedStream.h"

using namespace llvm;

#define GET_REGINFO_MC_DESC
#include "LAINGenRegisterInfo.inc"

#define GET_INSTRINFO_MC_DESC
#include "LAINGenInstrInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "LAINGenSubtargetInfo.inc"

static MCRegisterInfo *createLAINMCRegisterInfo(const Triple &TT) {
  LAIN_DUMP_MAGENTA
  MCRegisterInfo *X = new MCRegisterInfo();
  InitLAINMCRegisterInfo(X, LAIN::R0);
  return X;
}

static MCSubtargetInfo *createLAINMCSubtargetInfo(const Triple &TT,
                                                 StringRef CPU, StringRef FS) {
  LAIN_DUMP_MAGENTA
  return createLAINMCSubtargetInfoImpl(TT, CPU, /*TuneCPU*/ CPU, FS);
}


static MCAsmInfo *createLAINMCAsmInfo(const MCRegisterInfo &MRI,
                                     const Triple &TT,
                                     const MCTargetOptions &Options) {
  LAIN_DUMP_MAGENTA
  MCAsmInfo *MAI = new LAINELFMCAsmInfo(TT);
  unsigned SP = MRI.getDwarfRegNum(LAIN::R1, true);
  MCCFIInstruction Inst = MCCFIInstruction::cfiDefCfa(nullptr, SP, 0);
  MAI->addInitialFrameState(Inst);
  return MAI;
}

static MCInstPrinter *createLAINMCInstPrinter(const Triple &T,
                                             unsigned SyntaxVariant,
                                             const MCAsmInfo &MAI,
                                             const MCInstrInfo &MII,
                                             const MCRegisterInfo &MRI) {
  return new LAINInstPrinter(MAI, MII, MRI);
}

LAINTargetStreamer::LAINTargetStreamer(MCStreamer &S) : MCTargetStreamer(S) {}
LAINTargetStreamer::~LAINTargetStreamer() = default;

static MCTargetStreamer *createTargetAsmStreamer(MCStreamer &S,
                                                 formatted_raw_ostream &OS,
                                                 MCInstPrinter *InstPrint,
                                                 bool isVerboseAsm) {
  return new LAINTargetStreamer(S);
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
  RegisterMCAsmInfoFn X(TheLAINTarget, createLAINMCAsmInfo);
  // Register the MC register info.
  TargetRegistry::RegisterMCRegInfo(TheLAINTarget, createLAINMCRegisterInfo);
  // Register the MC instruction info.
  TargetRegistry::RegisterMCInstrInfo(TheLAINTarget, createLAINMCInstrInfo);
  // Register the MC subtarget info.
  TargetRegistry::RegisterMCSubtargetInfo(TheLAINTarget,
                                          createLAINMCSubtargetInfo);
  TargetRegistry::RegisterMCInstPrinter(TheLAINTarget, createLAINMCInstPrinter);
  TargetRegistry::RegisterAsmTargetStreamer(TheLAINTarget,
                                            createTargetAsmStreamer);
  // Register the MC Code Emitter.
  TargetRegistry::RegisterMCCodeEmitter(TheLAINTarget, createLAINMCCodeEmitter);
  // Register the asm backend.
  TargetRegistry::RegisterMCAsmBackend(TheLAINTarget, createLAINAsmBackend);
}