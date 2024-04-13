#include "LAINRegisterInfo.h"
#include "LAIN.h"
#include "LAINInstrInfo.h"
#include "LAINSubtarget.h"
#include "llvm/ADT/BitVector.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineModuleInfo.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/CodeGen/RegisterScavenging.h"
#include "llvm/CodeGen/TargetFrameLowering.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetOptions.h"

using namespace llvm;

#define DEBUG_TYPE "LAIN-reg-info"

#define GET_REGINFO_TARGET_DESC
#include "LAINGenRegisterInfo.inc"

LAINRegisterInfo::LAINRegisterInfo() : LAINGenRegisterInfo(LAIN::RA) {}

const MCPhysReg *
LAINRegisterInfo::getCalleeSavedRegs(const MachineFunction *MF) const {
  return CSR_LAIN_SaveList;
}

// TODO: check cconv
BitVector LAINRegisterInfo::getReservedRegs(const MachineFunction &MF) const {
  LAINFrameLowering const *TFI = getFrameLowering(MF);

  BitVector Reserved(getNumRegs());
  Reserved.set(LAIN::GP);
  Reserved.set(LAIN::SP);

  if (TFI->hasFP(MF)) {
    Reserved.set(LAIN::FP);
  }
  if (TFI->hasBP(MF)) {
    Reserved.set(LAIN::BP);
  }
  return Reserved;
}

bool LAINRegisterInfo::requiresRegisterScavenging(
    const MachineFunction &MF) const {
  return false; // TODO: what for?
}

// TODO: rewrite!
bool LAINRegisterInfo::eliminateFrameIndex(MachineBasicBlock::iterator II,
                                          int SPAdj, unsigned FIOperandNum,
                                          RegScavenger *RS) const {
  assert(SPAdj == 0 && "Unexpected non-zero SPAdj value");

  MachineInstr &MI = *II;
  MachineFunction &MF = *MI.getParent()->getParent();
  DebugLoc DL = MI.getDebugLoc();

  int FrameIndex = MI.getOperand(FIOperandNum).getIndex();
  Register FrameReg;
  int Offset = getFrameLowering(MF)
                   ->getFrameIndexReference(MF, FrameIndex, FrameReg)
                   .getFixed();
  Offset += MI.getOperand(FIOperandNum + 1).getImm();

  if (!isInt<16>(Offset)) {
    llvm_unreachable("");
  }

  MI.getOperand(FIOperandNum).ChangeToRegister(FrameReg, false, false, false);
  MI.getOperand(FIOperandNum + 1).ChangeToImmediate(Offset);
  return false;
}

Register LAINRegisterInfo::getFrameRegister(const MachineFunction &MF) const {
  const TargetFrameLowering *TFI = getFrameLowering(MF);
  return TFI->hasFP(MF) ? LAIN::FP : LAIN::SP;;
}

const uint32_t *
LAINRegisterInfo::getCallPreservedMask(const MachineFunction &MF,
                                      CallingConv::ID CC) const {
  return CSR_LAIN_RegMask;
}