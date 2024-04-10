include "llvm/Target/Target.td"
include "LAINRegisterInfo.td"
include "LAINInstrInfo.td"

def LAINInstrInfo : InstrInfo;
def LAIN : Target {
  let InstructionSet = LAINInstrInfo;
}