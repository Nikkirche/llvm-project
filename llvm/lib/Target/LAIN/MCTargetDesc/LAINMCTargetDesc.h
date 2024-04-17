#ifndef LLVM_LIB_TARGET_LAIN_MCTARGETDESC_LAINMCTARGETDESC_H
#define LLVM_LIB_TARGET_LAIN_MCTARGETDESC_LAINMCTARGETDESC_H

#define GET_REGINFO_ENUM
#include "LAINGenRegisterInfo.inc"
#define GET_INSTRINFO_ENUM
#include "LAINGenInstrInfo.inc"
#endif

#include <memory>

namespace llvm {
class MCAsmBackend;
class MCCodeEmitter;
class MCContext;
class MCInstrInfo;
class MCObjectTargetWriter;
class MCRegisterInfo;
class MCSubtargetInfo;
class MCTargetOptions;
class Target;

MCCodeEmitter *createLAINMCCodeEmitter(const MCInstrInfo &MCII, MCContext &Ctx);
MCAsmBackend *createLAINAsmBackend(const Target &T, const MCSubtargetInfo &STI,
                                  const MCRegisterInfo &MRI,
                                  const MCTargetOptions &Options);
std::unique_ptr<MCObjectTargetWriter> createLAINELFObjectWriter(bool Is64Bit,
                                                               uint8_t OSABI);
} // namespace llvm
