multiline_comment|/*&n; * BK Id: SCCS/s.amigahw.h 1.5 05/17/01 18:14:24 cort&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASMPPC_AMIGAHW_H
DECL|macro|__ASMPPC_AMIGAHW_H
mdefine_line|#define __ASMPPC_AMIGAHW_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm-m68k/amigahw.h&gt;
DECL|macro|CHIP_PHYSADDR
macro_line|#undef CHIP_PHYSADDR
macro_line|#ifdef CONFIG_APUS_FAST_EXCEPT
DECL|macro|CHIP_PHYSADDR
mdefine_line|#define CHIP_PHYSADDR      (0x000000)
macro_line|#else
DECL|macro|CHIP_PHYSADDR
mdefine_line|#define CHIP_PHYSADDR      (0x004000)
macro_line|#endif
macro_line|#endif /* __ASMPPC_AMIGAHW_H */
macro_line|#endif /* __KERNEL__ */
eof
