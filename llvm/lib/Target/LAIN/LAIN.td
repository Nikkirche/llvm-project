include "llvm/Target/Target.td"
include "LAINRegisterInfo.td"
include "LAINInstrInfo.td"

class Proc<string Name, list<SubtargetFeature> Features>
 : Processor<Name, NoItineraries, Features>;

def : Proc<"generic", []>;

def LAINInstrInfo : InstrInfo;
def LAIN : Target {
  let InstructionSet = LAINInstrInfo;
}