#include "LAINRegisterInfo.h"
#include "LAIN.h"
#include "LAINFrameLowering.h"
#include "llvm/CodeGen/TargetInstrInfo.h"

using namespace llvm;

#define GET_REGINFO_TARGET_DESC
#include "LAINGenRegisterInfo.inc"

LAINRegisterInfo::LAINRegisterInfo() : LAINGenRegisterInfo(LAIN::R0) {
  LAIN_DUMP_GREEN
}