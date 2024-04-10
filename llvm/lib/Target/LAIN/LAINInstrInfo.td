//===----------------------------------------------------------------------===//
// LAIN profiles and nodes
//===----------------------------------------------------------------------===//

def sim_ret      : SDNode<"LAINISD::RET", SDTNone,
                            [SDNPHasChain, SDNPOptInGlue, SDNPVariadic]>;

//===----------------------------------------------------------------------===//
// Instruction format superclass
//===----------------------------------------------------------------------===//

include "LAINInstrFormats.td"

//===----------------------------------------------------------------------===//
// LAIN Operand, Complex Patterns and Transformations Definitions.
//===----------------------------------------------------------------------===//

class LImmAsmOperand<int width> : AsmOperandClass {
  let Name = "LImm" # width;
  let RenderMethod = "addImmOperands";
  let DiagnosticType = !strconcat("Invalid", Name);
}

def limm16 : Operand<i32>, ImmLeaf<i32, [{return isInt<16>(Imm);}]> {
  let ParserMatchClass = LImmAsmOperand<16>;
  let EncoderMethod = "getImmOpValue";
  let DecoderMethod = "decodeLImmOperand<16>";
  let MCOperandPredicate = [{
    int64_t Imm;
    if (MCOp.evaluateAsConstantImm(Imm))
      return isInt<16>(Imm);
    return MCOp.isBareSymbolRef();
  }];
  let OperandType = "OPERAND_LAINM16";
  let OperandNamespace = "LAINOp";
}

//===----------------------------------------------------------------------===//
// LAIN Instructions
//===----------------------------------------------------------------------===//

let hasSideEffects = 0, mayLoad = 0, mayStore = 0, isCall = 1, isBranch = 1, isTerminator = 1 in
def BR : LAINInst<0x0, (outs), (ins GPR:$rs1), "BR $rs1",
                  [(brind GPR:$rs1)]>;

let isBarrier = 1, isReturn = 1, isTerminator = 1 in
def PseudoRET : LAINPseudoInst<(outs), (ins), "# PseudoRET",
                [(sim_ret)]>,
                PseudoInstExpansion<(BR R0)>;

// movli
let isAsCheapAsAMove = 1, isCodeGenOnly = 1, isReMaterializable = 1 in
def MOVLI : LAINInst<0x0, (outs GPR:$rd), (ins limm16:$imm),
                     "MOVli $rd $imm",
                     [(set GPR:$rd, limm16:$imm)]>;