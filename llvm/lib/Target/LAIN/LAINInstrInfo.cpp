#include "LAINInstrInfo.h"
#include "LAIN.h"
#include "MCTargetDesc/LAINInfo.h"
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

LAINInstrInfo::LAINInstrInfo()
    : LAINGenInstrInfo(LAIN::ADJCALLSTACKDOWN, LAIN::ADJCALLSTACKUP) {
  LAIN_DUMP_GREEN
}

unsigned LAINInstrInfo::isLoadFromStackSlot(const MachineInstr &MI,
                                            int &FrameIndex) const {
  switch (MI.getOpcode()) {
  default:
    return 0;
    // TODO: load opcodes
    break;
  }

  if (MI.getOperand(1).isFI() && MI.getOperand(2).isImm() &&
      MI.getOperand(2).getImm() == 0) {
    FrameIndex = MI.getOperand(1).getIndex();
    return MI.getOperand(0).getReg();
  }
  return 0;
}

unsigned LAINInstrInfo::isStoreToStackSlot(const MachineInstr &MI,
                                           int &FrameIndex) const {
  llvm_unreachable("");
  return 0;
}

static LAINCC::CondCode getCondFromBranchOpc(unsigned Opc) {
  switch (Opc) {
  default:
    return LAINCC::INVALID;
  case LAIN::BEQ:
    return LAINCC::EQ;
  case LAIN::BNE:
    return LAINCC::NE;
  case LAIN::BLE:
    return LAINCC::LE;
  case LAIN::BGT:
    return LAINCC::GT;
  case LAIN::BLEU:
    return LAINCC::LEU;
  case LAIN::BGTU:
    return LAINCC::GTU;
  }
}

static void parseCondBranch(MachineInstr &LastInst, MachineBasicBlock *&Target,
                            SmallVectorImpl<MachineOperand> &Cond) {
  // Block ends with fall-through condbranch.
  assert(LastInst.getDesc().isConditionalBranch() &&
         "Unknown conditional branch");
  Target = LastInst.getOperand(2).getMBB();
  unsigned CC = getCondFromBranchOpc(LastInst.getOpcode());
  Cond.push_back(MachineOperand::CreateImm(CC));
  Cond.push_back(LastInst.getOperand(0));
  Cond.push_back(LastInst.getOperand(1));
}

const MCInstrDesc &LAINInstrInfo::getBrCond(LAINCC::CondCode CC) const {
  switch (CC) {
  default:
    llvm_unreachable("Unknown condition code!");
  case LAINCC::EQ:
    return get(LAIN::BEQ);
  case LAINCC::NE:
    return get(LAIN::BNE);
  case LAINCC::LE:
    return get(LAIN::BLE);
  case LAINCC::GT:
    return get(LAIN::BGT);
  case LAINCC::LEU:
    return get(LAIN::BLEU);
  case LAINCC::GTU:
    return get(LAIN::BGTU);
  }
}

LAINCC::CondCode LAINCC::getOppositeBranchCondition(LAINCC::CondCode CC) {
  switch (CC) {
  default:
    llvm_unreachable("Unrecognized conditional branch");
  case LAINCC::EQ:
    return LAINCC::NE;
  case LAINCC::NE:
    return LAINCC::EQ;
  case LAINCC::LE:
    return LAINCC::GT;
  case LAINCC::GT:
    return LAINCC::LE;
  case LAINCC::LEU:
    return LAINCC::GTU;
  case LAINCC::GTU:
    return LAINCC::LEU;
  }
}

// TODO: inherited from riscv
bool LAINInstrInfo::analyzeBranch(MachineBasicBlock &MBB,
                                  MachineBasicBlock *&TBB,
                                  MachineBasicBlock *&FBB,
                                  SmallVectorImpl<MachineOperand> &Cond,
                                  bool AllowModify) const {
  TBB = FBB = nullptr;
  Cond.clear();

  // If the block has no terminators, it just falls into the block after it.
  MachineBasicBlock::iterator I = MBB.getLastNonDebugInstr();
  if (I == MBB.end() || !isUnpredicatedTerminator(*I))
    return false;

  // Count the number of terminators and find the first unconditional or
  // indirect branch.
  MachineBasicBlock::iterator FirstUncondOrIndirectBr = MBB.end();
  int NumTerminators = 0;
  for (auto J = I.getReverse(); J != MBB.rend() && isUnpredicatedTerminator(*J);
       J++) {
    NumTerminators++;
    if (J->getDesc().isUnconditionalBranch() ||
        J->getDesc().isIndirectBranch()) {
      FirstUncondOrIndirectBr = J.getReverse();
    }
  }

  // If AllowModify is true, we can erase any terminators after
  // FirstUncondOrIndirectBR.
  if (AllowModify && FirstUncondOrIndirectBr != MBB.end()) {
    while (std::next(FirstUncondOrIndirectBr) != MBB.end()) {
      std::next(FirstUncondOrIndirectBr)->eraseFromParent();
      NumTerminators--;
    }
    I = FirstUncondOrIndirectBr;
  }

  // We can't handle blocks that end in an indirect branch.
  if (I->getDesc().isIndirectBranch())
    return true;

  // We can't handle blocks with more than 2 terminators.
  if (NumTerminators > 2)
    return true;

  // Handle a single unconditional branch.
  if (NumTerminators == 1 && I->getDesc().isUnconditionalBranch()) {
    TBB = getBranchDestBlock(*I);
    return false;
  }

  // Handle a single conditional branch.
  if (NumTerminators == 1 && I->getDesc().isConditionalBranch()) {
    parseCondBranch(*I, TBB, Cond);
    return false;
  }

  // Handle a conditional branch followed by an unconditional branch.
  if (NumTerminators == 2 && std::prev(I)->getDesc().isConditionalBranch() &&
      I->getDesc().isUnconditionalBranch()) {
    parseCondBranch(*std::prev(I), TBB, Cond);
    FBB = getBranchDestBlock(*I);
    return false;
  }

  // Otherwise, we can't handle this.
  return true;
}

// TODO: explore
unsigned LAINInstrInfo::removeBranch(MachineBasicBlock &MBB,
                                     int *BytesRemoved) const {
  if (BytesRemoved)
    *BytesRemoved = 0;
  MachineBasicBlock::iterator I = MBB.getLastNonDebugInstr();
  if (I == MBB.end())
    return 0;

  if (!I->getDesc().isUnconditionalBranch() &&
      !I->getDesc().isConditionalBranch())
    return 0;

  // Remove the branch.
  if (BytesRemoved)
    *BytesRemoved += getInstSizeInBytes(*I);
  I->eraseFromParent();

  I = MBB.end();

  if (I == MBB.begin())
    return 1;
  --I;
  if (!I->getDesc().isConditionalBranch())
    return 1;

  // Remove the branch.
  if (BytesRemoved)
    *BytesRemoved += getInstSizeInBytes(*I);
  I->eraseFromParent();
  return 2;
}

MachineBasicBlock *
LAINInstrInfo::getBranchDestBlock(const MachineInstr &MI) const {
  assert(MI.getDesc().isBranch() && "Unexpected opcode!");
  return MI.getOperand(MI.getNumExplicitOperands() - 1).getMBB();
}

void LAINInstrInfo::copyPhysReg(MachineBasicBlock &MBB,
                                MachineBasicBlock::iterator MBBI,
                                const DebugLoc &DL, MCRegister DstReg,
                                MCRegister SrcReg, bool KillSrc) const {
  if (LAIN::GPRRegClass.contains(DstReg, SrcReg)) {
    BuildMI(MBB, MBBI, DL, get(LAIN::ADDI), DstReg)
        .addReg(SrcReg, getKillRegState(KillSrc))
        .addImm(0);
    return;
  }
  llvm_unreachable("can't copyPhysReg");
}

void LAINInstrInfo::storeRegToStackSlot(MachineBasicBlock &MBB,
                                        MachineBasicBlock::iterator I,
                                        Register SrcReg, bool IsKill, int FI,
                                        const TargetRegisterClass *RC,
                                        const TargetRegisterInfo *TRI,
                                        Register VReg) const {
  DebugLoc DL;
  if (I != MBB.end())
    DL = I->getDebugLoc();

  MachineFunction *MF = MBB.getParent();
  MachineFrameInfo &MFI = MF->getFrameInfo();

  MachineMemOperand *MMO = MF->getMachineMemOperand(
      MachinePointerInfo::getFixedStack(*MF, FI), MachineMemOperand::MOStore,
      MFI.getObjectSize(FI), MFI.getObjectAlign(FI));

  BuildMI(MBB, I, DL, get(LAIN::STI_))
      .addReg(SrcReg, getKillRegState(IsKill))
      .addFrameIndex(FI)
      .addImm(0)
      .addMemOperand(MMO);
}

void LAINInstrInfo::loadRegFromStackSlot(MachineBasicBlock &MBB,
                                         MachineBasicBlock::iterator I,
                                         Register DstReg, int FI,
                                         const TargetRegisterClass *RC,
                                         const TargetRegisterInfo *TRI,
                                         Register VReg) const {
  DebugLoc DL;
  if (I != MBB.end())
    DL = I->getDebugLoc();

  MachineFunction *MF = MBB.getParent();
  MachineFrameInfo &MFI = MF->getFrameInfo();

  MachineMemOperand *MMO = MF->getMachineMemOperand(
      MachinePointerInfo::getFixedStack(*MF, FI), MachineMemOperand::MOLoad,
      MFI.getObjectSize(FI), MFI.getObjectAlign(FI));

  BuildMI(MBB, I, DL, get(LAIN::LDI), DstReg)
      .addFrameIndex(FI)
      .addImm(0)
      .addMemOperand(MMO);
}

bool LAINInstrInfo::reverseBranchCondition(
    SmallVectorImpl<MachineOperand> &Cond) const {
  assert((Cond.size() == 3) && "Invalid branch condition!");
  auto CC = static_cast<LAINCC::CondCode>(Cond[0].getImm());
  Cond[0].setImm(getOppositeBranchCondition(CC));
  return false;
}

// TODO: explore
unsigned LAINInstrInfo::insertBranch(
    MachineBasicBlock &MBB, MachineBasicBlock *TBB, MachineBasicBlock *FBB,
    ArrayRef<MachineOperand> Cond, const DebugLoc &DL, int *BytesAdded) const {
  if (BytesAdded)
    *BytesAdded = 0;

  // Shouldn't be a fall through.
  assert(TBB && "insertBranch must not be told to insert a fallthrough");
  assert((Cond.size() == 3 || Cond.size() == 0) &&
         "Wrong number of components");

  // Unconditional branch.
  if (Cond.empty()) {
    MachineInstr &MI = *BuildMI(&MBB, DL, get(LAIN::B)).addMBB(TBB);
    if (BytesAdded)
      *BytesAdded += getInstSizeInBytes(MI);
    return 1;
  }

  // Either a one or two-way conditional branch.
  auto CC = static_cast<LAINCC::CondCode>(Cond[0].getImm());
  MachineInstr &CondMI =
      *BuildMI(&MBB, DL, getBrCond(CC)).add(Cond[1]).add(Cond[2]).addMBB(TBB);
  if (BytesAdded)
    *BytesAdded += getInstSizeInBytes(CondMI);

  // One-way conditional branch.
  if (!FBB)
    return 1;

  // Two-way conditional branch.
  MachineInstr &MI = *BuildMI(&MBB, DL, get(LAIN::B)).addMBB(FBB);
  if (BytesAdded)
    *BytesAdded += getInstSizeInBytes(MI);
  return 2;
}

unsigned LAINInstrInfo::getInstSizeInBytes(const MachineInstr &MI) const {
  llvm_unreachable("");
}

bool LAINInstrInfo::getBaseAndOffsetPosition(const MachineInstr &MI,
                                             unsigned &BasePos,
                                             unsigned &OffsetPos) const {
  llvm_unreachable("");
}
