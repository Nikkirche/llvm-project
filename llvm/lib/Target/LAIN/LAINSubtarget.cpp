
#include "LAINSubtarget.h"
#include "LAIN.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/ErrorHandling.h"
using namespace llvm;

#define DEBUG_TYPE "lain-subtarget"

#define GET_SUBTARGETINFO_TARGET_DESC
#define GET_SUBTARGETINFO_CTOR
#include "LAINGenSubtargetInfo.inc"

void LAINSubtarget::anchor() {}

LAINSubtarget::LAINSubtarget(const Triple &TT, const std::string &CPU,
                           const std::string &FS, const TargetMachine &TM)
    : LAINGenSubtargetInfo(TT, CPU, /*TuneCPU=*/CPU, FS), InstrInfo(),
      FrameLowering(*this), TLInfo(TM, *this) {}
