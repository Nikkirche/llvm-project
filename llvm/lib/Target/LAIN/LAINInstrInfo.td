//===----------------------------------------------------------------------===//
// LAIN profiles and nodes
//===----------------------------------------------------------------------===//

def lain_ret      : SDNode<"LAINISD::RET", SDTNone,
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
  let EncoderMethod = "getLImm16OpValue";
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

let hasSideEffects = 0, mayLoad = 0, mayStore = 0, isCall = 1, isBranch = 1, isTerminator = 1, r2 = 0, r3_imm = 0 in
def BR : LAINInst<0xBB, (outs), (ins GPR:$r1), "BR $r1",
                  [(brind GPR:$r1)]>;

let isBarrier = 1, isReturn = 1, isTerminator = 1 in
def PseudoRET : LAINPseudoInst<(outs), (ins), "# PseudoRET",
                [(lain_ret)]>,
                PseudoInstExpansion<(BR R0)>;

// movli
let isAsCheapAsAMove = 1, isCodeGenOnly = 1, isReMaterializable = 1, r2 = 0 in
def MOVLI : LAINInst<0xAA, (outs GPR:$r1), (ins limm16:$r3_imm),
                     "MOVli $r1 $r3_imm",
                     [(set GPR:$r1, limm16:$r3_imm)]>;