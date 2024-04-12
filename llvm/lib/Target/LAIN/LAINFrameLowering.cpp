#include "LAINFrameLowering.h"
#include "LAINMachineFunctionInfo.h"
#include "LAINSubtarget.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineModuleInfo.h"
#include "llvm/CodeGen/RegisterScavenging.h"
#include "llvm/CodeGen/TargetRegisterInfo.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/ErrorHandling.h"
#include <algorithm>

#define DEBUG_TYPE "LAIN-frame-lowering"

using namespace llvm;

// seems done
void LAINFrameLowering::determineCalleeSaves(MachineFunction &MF,
                                            BitVector &SavedRegs,
                                            RegScavenger *RS) const {
  TargetFrameLowering::determineCalleeSaves(MF, SavedRegs, RS);
  // Unconditionally spill RA and FP only if the function uses a frame
  // pointer.
  if (hasFP(MF)) {
    SavedRegs.set(LAIN::R0);
    SavedRegs.set(LAIN::R2);
  }
}

void LAINFrameLowering::adjustStackToMatchRecords(
    MachineBasicBlock &MBB, MachineBasicBlock::iterator MBBI,
    bool Allocate) const {
  llvm_unreachable("");
}

// TODO: seems ok
void LAINFrameLowering::emitPrologue(MachineFunction &MF,
                                    MachineBasicBlock &MBB) const {
  return;
}

// TODO: seems ok
void LAINFrameLowering::emitEpilogue(MachineFunction &MF,
                                    MachineBasicBlock &MBB) const {
  return;
}

// TODO: seems ok
bool LAINFrameLowering::spillCalleeSavedRegisters(
    MachineBasicBlock &MBB, MachineBasicBlock::iterator MI,
    ArrayRef<CalleeSavedInfo> CSI, const TargetRegisterInfo *TRI) const {
  if (CSI.empty())
    return true;

  MachineFunction *MF = MBB.getParent();
  const TargetInstrInfo &TII = *MF->getSubtarget().getInstrInfo();

  for (auto &CS : CSI) {
    // Insert the spill to the stack frame.
    Register Reg = CS.getReg();
    const TargetRegisterClass *RC = TRI->getMinimalPhysRegClass(Reg);
    TII.storeRegToStackSlot(MBB, MI, Reg, !MBB.isLiveIn(Reg), CS.getFrameIdx(),
                            RC, TRI, 0);
  }

  return true;
}

// TODO: seems ok
bool LAINFrameLowering::restoreCalleeSavedRegisters(
    MachineBasicBlock &MBB, MachineBasicBlock::iterator MI,
    MutableArrayRef<CalleeSavedInfo> CSI, const TargetRegisterInfo *TRI) const {
  if (CSI.empty())
    return true;

  MachineFunction *MF = MBB.getParent();
  const TargetInstrInfo &TII = *MF->getSubtarget().getInstrInfo();

  // Insert in reverse order.
  // loadRegFromStackSlot can insert multiple instructions.
  for (auto &CS : reverse(CSI)) {
    Register Reg = CS.getReg();
    const TargetRegisterClass *RC = TRI->getMinimalPhysRegClass(Reg);
    TII.loadRegFromStackSlot(MBB, MI, Reg, CS.getFrameIdx(), RC, TRI, 0);
    assert(MI != MBB.begin() && "loadRegFromStackSlot didn't insert any code!");
  }

  return true;
}

bool LAINFrameLowering::hasFP(const MachineFunction &MF) const {
  const TargetRegisterInfo *RegInfo = MF.getSubtarget().getRegisterInfo();

  const MachineFrameInfo &MFI = MF.getFrameInfo();
  return MF.getTarget().Options.DisableFramePointerElim(MF) || // -fomit-frame-pointer
         RegInfo->hasStackRealignment(MF) || MFI.hasVarSizedObjects() ||
         MFI.isFrameAddressTaken();
}

// TODO: rewrite!
StackOffset
LAINFrameLowering::getFrameIndexReference(const MachineFunction &MF, int FI,
                                         Register &FrameReg) const {
  const MachineFrameInfo &MFI = MF.getFrameInfo();
  const TargetRegisterInfo *RI = MF.getSubtarget().getRegisterInfo();
  const auto *UFI = MF.getInfo<LAINFunctionInfo>();

  // Callee-saved registers should be referenced relative to the stack
  // pointer (positive offset), otherwise use the frame pointer (negative
  // offset).
  const auto &CSI = MFI.getCalleeSavedInfo();
  int MinCSFI = 0;
  int MaxCSFI = -1;
  int Offset;

  Offset = MFI.getObjectOffset(FI) - getOffsetOfLocalArea() +
           MFI.getOffsetAdjustment();

  if (CSI.size()) {
    MinCSFI = CSI[0].getFrameIdx();
    MaxCSFI = CSI[CSI.size() - 1].getFrameIdx();
  }

  if (FI >= MinCSFI && FI <= MaxCSFI) {
    FrameReg = LAIN::R1;
    Offset += MFI.getStackSize();
  } else if (RI->hasStackRealignment(MF) && !MFI.isFixedObjectIndex(FI)) {
    // TODO: realigned stack
    llvm_unreachable("");
  } else {
    // TODO: what's going on here
    FrameReg = RI->getFrameRegister(MF);
    if (hasFP(MF)) {
      Offset += UFI->getVarArgsSaveSize();
    } else {
      Offset += MFI.getStackSize();
    }
  }

  return StackOffset::getFixed(Offset);
}

// Not preserve stack space within prologue for outgoing variables when the
// function contains variable size objects or there are vector objects accessed
// by the frame pointer.
// Let eliminateCallFramePseudoInstr preserve stack space for it.
bool LAINFrameLowering::hasReservedCallFrame(const MachineFunction &MF) const {
  return !MF.getFrameInfo().hasVarSizedObjects();
}