#include "LAINInstrInfo.h"
#include "LAIN.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineMemOperand.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/ErrorHandling.h"

using namespace llvm;

#define GET_INSTRINFO_CTOR_DTOR
#include "LAINGenInstrInfo.inc"

#define DEBUG_TYPE "LAIN-inst-info"

LAINInstrInfo::LAINInstrInfo() : LAINGenInstrInfo() { LAIN_DUMP_GREEN }