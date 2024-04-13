let TargetPrefix = "lain" in {  // All intrinsics start with "llvm.lain.".

def int_lain_putpixel: ClangBuiltin<"simPutPixel">,
  Intrinsic<[], [llvm_i32_ty, llvm_i32_ty, llvm_i32_ty], [IntrNoMem, IntrHasSideEffects]>;

def int_lain_flush: ClangBuiltin<"simFlush">,
  Intrinsic<[], [], [IntrNoMem, IntrHasSideEffects]>;

def int_lain_rand: ClangBuiltin<"simRand">,
  Intrinsic<[llvm_i32_ty], [], [IntrNoMem, IntrHasSideEffects]>;

def int_lain_abs: ClangBuiltin<"simAbs">,
  Intrinsic<[llvm_i32_ty], [llvm_i32_ty], [IntrNoMem, IntrHasSideEffects]>;

def int_lain_init: ClangBuiltin<"simInit">,
  Intrinsic<[], [], [IntrNoMem, IntrHasSideEffects]>;

} // TargetPrefix = "lain"