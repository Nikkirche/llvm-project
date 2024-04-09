#ifndef LLVM_LIB_TARGET_LAIN_LAINREGISTERINFO_H
#define LLVM_LIB_TARGET_LAIN_LAINREGISTERINFO_H

#define GET_REGINFO_HEADER
#include "LAINGenRegisterInfo.inc"

namespace llvm {

struct LAINRegisterInfo : public LAINGenRegisterInfo {
public:
  LAINRegisterInfo();
};

} // end namespace llvm

#endif