
//===----------------------------------------------------------------------===//
//  Describe LAIN instructions format
//
//  CPU INSTRUCTION FORMATS
//
//  FF FF FF FF
//        ^^ ^^ - r3_imm - third reg or imm
//      ^       - r2     - second reg
//     ^        - r1     - first reg
//  ^^          - opcode - operation code
//
//===----------------------------------------------------------------------===//

// Generic LAIN Format
class LAINInst<bits<8> op, dag outs, dag ins, string asmstr, list<dag> pattern>: Instruction
{
  // Inst and Size: for tablegen(... -gen-emitter) and
  // tablegen(... -gen-disassembler) in CMakeLists.txt
  let Namespace = "LAIN";
  let DecoderNamespace = "LAIN";
  let Size = 4;

  field bits<32> Inst;

  bits<8> Opcode = op;
  bits<4>  r1;
  bits<4>  r2;
  bits<16> r3_imm;

  let Inst{31-24} = Opcode;
  let Inst{23-20} = r1;
  let Inst{19-16} = r2;
  let Inst{15-0}  = r3_imm;

  let OutOperandList = outs;
  let InOperandList  = ins;
  let AsmString   = asmstr;
  let Pattern     = pattern;

}

// Pseudo instructions format
class LAINPseudoInst<dag outs, dag ins, string asmstr, list<dag> pattern>
   : LAINInst<0, outs, ins, asmstr, pattern> {
  let isPseudo = 1;
  let isCodeGenOnly = 1;
}

//intrinsics

def PUTPIXEL : LAINInst<0xF0, (outs), (ins GPR:$r1, GPR:$r2, GPR:$r3_imm),
                      "PUTPIXEL $r1 $r2 $r3_imm", [(int_lain_putpixel GPR:$r1, GPR:$r2, GPR:$r3_imm)]>;

let r1 = 0, r2 = 0, r3_imm = 0 in
def FLUSH : LAINInst<0xF1, (outs), (ins), "FLUSH", [(int_lain_flush)]>;

let r2 = 0, r3_imm = 0 in
def RAND : LAINInst<0xF2, (outs GPR:$r1), (ins), "RAND $r1", [(set GPR:$r1, (int_lain_rand))]>;

let r3_imm = 0 in
def ABS : LAINInst<0xF3, (outs GPR:$r1), (ins GPR:$r2), "ABS $r1 $r2", [(set GPR:$r1, (int_lain_abs GPR:$r2))]>;

let r1 = 0, r2 = 0, r3_imm = 0 in
def INIT  : LAINInst<0xF4, (outs), (ins), "INIT", [(int_lain_init)]>;