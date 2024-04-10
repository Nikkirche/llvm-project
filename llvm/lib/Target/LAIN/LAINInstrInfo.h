#ifndef LLVM_LIB_TARGET_LAIN_LAININSTRINFO_H
#define LLVM_LIB_TARGET_LAIN_LAININSTRINFO_H

#include "LAINRegisterInfo.h"
#include "MCTargetDesc/LAINInfo.h"
#include "llvm/CodeGen/TargetInstrInfo.h"

#define GET_INSTRINFO_HEADER
#include "LAINGenInstrInfo.inc"

namespace llvm {

class LAINSubtarget;

class LAINInstrInfo : public LAINGenInstrInfo {
public:
  LAINInstrInfo();

};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_LAIN_LAININSTRINFO_H