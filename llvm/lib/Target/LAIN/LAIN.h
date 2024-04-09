#ifndef LLVM_LIB_TARGET_LAIN_LAIN_H
#define LLVM_LIB_TARGET_LAIN_LAIN_H

#include "MCTargetDesc/LAINMCTargetDesc.h"
#include "llvm/Support/raw_ostream.h"

#define LAIN_DUMP(Color)                                                        \
  {                                                                            \
    llvm::errs().changeColor(Color)                                            \
        << __func__ << "\n\t\t" << __FILE__ << ":" << __LINE__ << "\n";        \
    llvm::errs().changeColor(llvm::raw_ostream::WHITE);                        \
  }

#define LAIN_DUMP_RED LAIN_DUMP(llvm::raw_ostream::RED)
#define LAIN_DUMP_GREEN LAIN_DUMP(llvm::raw_ostream::GREEN)
#define LAIN_DUMP_YELLOW LAIN_DUMP(llvm::raw_ostream::YELLOW)
#define LAIN_DUMP_CYAN LAIN_DUMP(llvm::raw_ostream::CYAN)
#define LAIN_DUMP_MAGENTA LAIN_DUMP(llvm::raw_ostream::MAGENTA)
#define LAIN_DUMP_WHITE LAIN_DUMP(llvm::raw_ostream::WHITE)

#endif // LLVM_LIB_TARGET_Sim_Sim_H