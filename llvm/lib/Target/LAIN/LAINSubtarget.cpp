
#include "LAINSubtarget.h"
#include "LAIN.h"
#include "llvm/Target/TargetMachine.h"

using namespace llvm;

#define DEBUG_TYPE "lain-subtarget"

#define GET_SUBTARGETINFO_TARGET_DESC
#define GET_SUBTARGETINFO_CTOR
#include "LAINGenSubtargetInfo.inc"

LAINSubtarget::LAINSubtarget(const StringRef &CPU, const StringRef &TuneCPU,
                           const StringRef &FS, const TargetMachine &TM)
    : LAINGenSubtargetInfo(TM.getTargetTriple(), CPU, TuneCPU, FS) {
  LAIN_DUMP_CYAN
}