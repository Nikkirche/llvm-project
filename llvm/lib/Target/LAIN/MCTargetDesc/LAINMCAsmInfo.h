#ifndef LLVM_LIB_TARGET_LAIN_MCTARGETDESC_LAINMCASMINFO_H
#define LLVM_LIB_TARGET_LAIN_MCTARGETDESC_LAINMCASMINFO_H

#include "llvm/MC/MCAsmInfoELF.h"

namespace llvm {

class Triple;

class LAINELFMCAsmInfo : public MCAsmInfoELF {
public:
  explicit LAINELFMCAsmInfo(const Triple &TheTriple);
};

} // end namespace llvm


#endif