multiline_comment|/* asmmacro.h: Assembler macros.&n; *&n; * Copyright (C) 1996 David S. Miller (davem@caipfs.rutgers.edu)&n; */
macro_line|#ifndef _SPARC_ASMMACRO_H
DECL|macro|_SPARC_ASMMACRO_H
mdefine_line|#define _SPARC_ASMMACRO_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/btfixup.h&gt;
macro_line|#include &lt;asm/asi.h&gt;
DECL|macro|GET_PROCESSOR4M_ID
mdefine_line|#define GET_PROCESSOR4M_ID(reg) &bslash;&n;&t;rd&t;%tbr, %reg; &bslash;&n;&t;srl&t;%reg, 12, %reg; &bslash;&n;&t;and&t;%reg, 3, %reg;
DECL|macro|GET_PROCESSOR4D_ID
mdefine_line|#define GET_PROCESSOR4D_ID(reg) &bslash;&n;&t;lda&t;[%g0] ASI_M_VIKING_TMP1, %reg;
multiline_comment|/* Blackbox */
DECL|macro|GET_PROCESSOR_ID
mdefine_line|#define GET_PROCESSOR_ID(reg) &bslash;&n;&t;sethi&t;%hi(___b_smp_processor_id), %reg; &bslash;&n;&t;sethi&t;%hi(boot_cpu_id), %reg; &bslash;&n;&t;ldub&t;[%reg + %lo(boot_cpu_id)], %reg;
DECL|macro|GET_PROCESSOR_MID
mdefine_line|#define GET_PROCESSOR_MID(reg, tmp) &bslash;&n;&t;rd&t;%tbr, %reg; &bslash;&n;&t;sethi&t;%hi(C_LABEL(mid_xlate)), %tmp; &bslash;&n;&t;srl&t;%reg, 12, %reg; &bslash;&n;&t;or&t;%tmp, %lo(C_LABEL(mid_xlate)), %tmp; &bslash;&n;&t;and&t;%reg, 3, %reg; &bslash;&n;&t;ldub&t;[%tmp + %reg], %reg;
DECL|macro|GET_PROCESSOR_OFFSET
mdefine_line|#define GET_PROCESSOR_OFFSET(reg, tmp) &bslash;&n;&t;GET_PROCESSOR_ID(reg) &bslash;&n;&t;sethi&t;%hi(C_LABEL(cpu_offset)), %tmp; &bslash;&n;&t;sll&t;%reg, 2, %reg; &bslash;&n;&t;or&t;%tmp, %lo(C_LABEL(cpu_offset)), %tmp; &bslash;&n;&t;ld&t;[%tmp + %reg], %reg;
multiline_comment|/* All trap entry points _must_ begin with this macro or else you&n; * lose.  It makes sure the kernel has a proper window so that&n; * c-code can be called.&n; */
DECL|macro|SAVE_ALL_HEAD
mdefine_line|#define SAVE_ALL_HEAD &bslash;&n;&t;sethi&t;%hi(trap_setup), %l4; &bslash;&n;&t;jmpl&t;%l4 + %lo(trap_setup), %l6;
DECL|macro|SAVE_ALL
mdefine_line|#define SAVE_ALL &bslash;&n;&t;SAVE_ALL_HEAD &bslash;&n;&t; nop;
multiline_comment|/* All traps low-level code here must end with this macro. */
DECL|macro|RESTORE_ALL
mdefine_line|#define RESTORE_ALL b ret_trap_entry; clr %l6;
multiline_comment|/* sun4 probably wants half word accesses to ASI_SEGMAP, while sun4c+&n;   likes byte accesses. These are to avoid ifdef mania. */
macro_line|#ifdef CONFIG_SUN4
DECL|macro|lduXa
mdefine_line|#define lduXa&t;lduha
DECL|macro|stXa
mdefine_line|#define stXa&t;stha
macro_line|#else
DECL|macro|lduXa
mdefine_line|#define lduXa&t;lduba
DECL|macro|stXa
mdefine_line|#define stXa&t;stba
macro_line|#endif
macro_line|#endif /* !(_SPARC_ASMMACRO_H) */
eof
