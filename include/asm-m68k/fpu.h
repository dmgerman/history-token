macro_line|#ifndef __M68K_FPU_H
DECL|macro|__M68K_FPU_H
mdefine_line|#define __M68K_FPU_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * MAX floating point unit state size (FSAVE/FRESTORE)&n; */
macro_line|#if defined(CONFIG_M68020) || defined(CONFIG_M68030)
DECL|macro|FPSTATESIZE
mdefine_line|#define FPSTATESIZE (216/sizeof(unsigned char))
macro_line|#elif defined(CONFIG_M68040)
DECL|macro|FPSTATESIZE
mdefine_line|#define FPSTATESIZE (96/sizeof(unsigned char))
macro_line|#elif defined(CONFIG_M68KFPU_EMU)
DECL|macro|FPSTATESIZE
mdefine_line|#define FPSTATESIZE (28/sizeof(unsigned char))
macro_line|#elif defined(CONFIG_M68060)
DECL|macro|FPSTATESIZE
mdefine_line|#define FPSTATESIZE (12/sizeof(unsigned char))
macro_line|#else
DECL|macro|FPSTATESIZE
mdefine_line|#define FPSTATESIZE error no_cpu_type_configured
macro_line|#endif
macro_line|#endif /* __M68K_FPU_H */
eof
