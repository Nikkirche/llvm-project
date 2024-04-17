#ifndef LLVM_LIB_TARGET_LAIN_LAINTARGETSTREAMER_H
#define LLVM_LIB_TARGET_LAIN_LAINTARGETSTREAMER_H

#include "llvm/MC/MCStreamer.h"

namespace llvm {

class LAINTargetStreamer : public MCTargetStreamer {
public:
  LAINTargetStreamer(MCStreamer &S);
  ~LAINTargetStreamer() override;
};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_LAIN_LAINTARGETSTREAMER_H