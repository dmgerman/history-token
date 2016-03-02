multiline_comment|/*&n; *  linux/include/asm-arm/assembler.h&n; *&n; *  Copyright (C) 1996-2000 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  This file contains arm architecture specific defines&n; *  for the different processors.&n; *&n; *  Do not include any C declarations in this file - it is included by&n; *  assembler source.&n; */
macro_line|#ifndef __ASSEMBLY__
macro_line|#error &quot;Only include this from assembly code&quot;
macro_line|#endif
macro_line|#include &lt;asm/ptrace.h&gt;
multiline_comment|/*&n; * Endian independent macros for shifting bytes within registers.&n; */
macro_line|#ifndef __ARMEB__
DECL|macro|pull
mdefine_line|#define pull            lsr
DECL|macro|push
mdefine_line|#define push            lsl
DECL|macro|get_byte_0
mdefine_line|#define get_byte_0      lsl #0
DECL|macro|get_byte_1
mdefine_line|#define get_byte_1&t;lsr #8
DECL|macro|get_byte_2
mdefine_line|#define get_byte_2&t;lsr #16
DECL|macro|get_byte_3
mdefine_line|#define get_byte_3&t;lsr #24
DECL|macro|put_byte_0
mdefine_line|#define put_byte_0      lsl #0
DECL|macro|put_byte_1
mdefine_line|#define put_byte_1&t;lsl #8
DECL|macro|put_byte_2
mdefine_line|#define put_byte_2&t;lsl #16
DECL|macro|put_byte_3
mdefine_line|#define put_byte_3&t;lsl #24
macro_line|#else
DECL|macro|pull
mdefine_line|#define pull            lsl
DECL|macro|push
mdefine_line|#define push            lsr
DECL|macro|get_byte_0
mdefine_line|#define get_byte_0&t;lsr #24
DECL|macro|get_byte_1
mdefine_line|#define get_byte_1&t;lsr #16
DECL|macro|get_byte_2
mdefine_line|#define get_byte_2&t;lsr #8
DECL|macro|get_byte_3
mdefine_line|#define get_byte_3      lsl #0
DECL|macro|put_byte_0
mdefine_line|#define put_byte_0&t;lsl #24
DECL|macro|put_byte_1
mdefine_line|#define put_byte_1&t;lsl #16
DECL|macro|put_byte_2
mdefine_line|#define put_byte_2&t;lsl #8
DECL|macro|put_byte_3
mdefine_line|#define put_byte_3      lsl #0
macro_line|#endif
multiline_comment|/*&n; * Data preload for architectures that support it&n; */
macro_line|#if __LINUX_ARM_ARCH__ &gt;= 5
DECL|macro|PLD
mdefine_line|#define PLD(code...)&t;code
macro_line|#else
DECL|macro|PLD
mdefine_line|#define PLD(code...)
macro_line|#endif
DECL|macro|MODE_USR
mdefine_line|#define MODE_USR&t;USR_MODE
DECL|macro|MODE_FIQ
mdefine_line|#define MODE_FIQ&t;FIQ_MODE
DECL|macro|MODE_IRQ
mdefine_line|#define MODE_IRQ&t;IRQ_MODE
DECL|macro|MODE_SVC
mdefine_line|#define MODE_SVC&t;SVC_MODE
DECL|macro|DEFAULT_FIQ
mdefine_line|#define DEFAULT_FIQ&t;MODE_FIQ
multiline_comment|/*&n; * LOADREGS - ldm with PC in register list (eg, ldmfd sp!, {pc})&n; */
macro_line|#ifdef __STDC__
DECL|macro|LOADREGS
mdefine_line|#define LOADREGS(cond, base, reglist...)&bslash;&n;&t;ldm##cond&t;base,reglist
macro_line|#else
DECL|macro|LOADREGS
mdefine_line|#define LOADREGS(cond, base, reglist...)&bslash;&n;&t;ldm/**/cond&t;base,reglist
macro_line|#endif
multiline_comment|/*&n; * Build a return instruction for this processor type.&n; */
DECL|macro|RETINSTR
mdefine_line|#define RETINSTR(instr, regs...)&bslash;&n;&t;instr&t;regs
multiline_comment|/*&n; * Save the current IRQ state and disable IRQs.  Note that this macro&n; * assumes FIQs are enabled, and that the processor is in SVC mode.&n; */
DECL|variable|oldcpsr
dot
id|macro
id|save_and_disable_irqs
comma
id|oldcpsr
comma
id|temp
DECL|variable|oldcpsr
id|mrs
"&bslash;"
id|oldcpsr
comma
id|cpsr
DECL|variable|temp
id|mov
"&bslash;"
id|temp
comma
macro_line|#PSR_I_BIT | MODE_SVC
DECL|variable|cpsr_c
id|msr
id|cpsr_c
comma
"&bslash;"
id|temp
dot
id|endm
multiline_comment|/*&n; * Restore interrupt state previously stored in a register.  We don&squot;t&n; * guarantee that this will preserve the flags.&n; */
dot
id|macro
id|restore_irqs
comma
id|oldcpsr
DECL|variable|cpsr_c
id|msr
id|cpsr_c
comma
"&bslash;"
id|oldcpsr
dot
id|endm
multiline_comment|/*&n; * These two are used to save LR/restore PC over a user-based access.&n; * The old 26-bit architecture requires that we do.  On 32-bit&n; * architecture, we can safely ignore this requirement.&n; */
dot
id|macro
id|save_lr
dot
id|endm
dot
id|macro
id|restore_pc
id|mov
id|pc
comma
id|lr
dot
id|endm
DECL|macro|USER
mdefine_line|#define USER(x...)&t;&t;&t;&t;&bslash;&n;9999:&t;x;&t;&t;&t;&t;&t;&bslash;&n;&t;.section __ex_table,&quot;a&quot;;&t;&t;&bslash;&n;&t;.align&t;3;&t;&t;&t;&t;&bslash;&n;&t;.long&t;9999b,9001f;&t;&t;&t;&bslash;&n;&t;.previous
eof
