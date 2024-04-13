#ifndef LLVM_LIB_TARGET_LAIN_MCTARGETDESC_LAINFIXUPKINDS_H
#define LLVM_LIB_TARGET_LAIN_MCTARGETDESC_LAINFIXUPKINDS_H

#include "llvm/MC/MCFixup.h"

namespace llvm {
namespace LAIN {
// Although most of the current fixup types reflect a unique relocation
// one can have multiple fixup types for a given relocation and thus need
// to be uniquely named.
//
// This table *must* be in the same order of
// MCFixupKindInfo Infos[LAIN::NumTargetFixupKinds]
// in LAINAsmBackend.cpp.
//
enum Fixups {
  fixup_LAIN_PC16 = FirstTargetFixupKind,
  // Marker
  LastTargetFixupKind,
  NumTargetFixupKinds = LastTargetFixupKind - FirstTargetFixupKind
};
} // namespace LAIN
} // namespace llvm


#endif