multiline_comment|/*&n; * linux/asm/assembler.h&n; *&n; * This file contains arm architecture specific defines&n; * for the different processors.&n; *&n; * Do not include any C declarations in this file - it is included by&n; * assembler source.&n; */
macro_line|#ifndef __ASSEMBLY__
macro_line|#error &quot;Only include this from assembly code&quot;
macro_line|#endif
multiline_comment|/*&n; * Endian independent macros for shifting bytes within registers.&n; */
DECL|macro|pull
mdefine_line|#define pull            lsr
DECL|macro|push
mdefine_line|#define push            lsl
DECL|macro|byte
mdefine_line|#define byte(x)         (x*8)
macro_line|#ifdef __STDC__
DECL|macro|LOADREGS
mdefine_line|#define LOADREGS(cond, base, reglist...)&bslash;&n;&t;ldm##cond&t;base,reglist^
DECL|macro|RETINSTR
mdefine_line|#define RETINSTR(instr, regs...)&bslash;&n;&t;instr##s&t;regs
macro_line|#else
DECL|macro|LOADREGS
mdefine_line|#define LOADREGS(cond, base, reglist...)&bslash;&n;&t;ldm/**/cond&t;base,reglist^
DECL|macro|RETINSTR
mdefine_line|#define RETINSTR(instr, regs...)&bslash;&n;&t;instr/**/s&t;regs
macro_line|#endif
DECL|macro|MODENOP
mdefine_line|#define MODENOP&bslash;&n;&t;mov&t;r0, r0
DECL|macro|MODE
mdefine_line|#define MODE(savereg,tmpreg,mode) &bslash;&n;&t;mov&t;savereg, pc; &bslash;&n;&t;bic&t;tmpreg, savereg, $0x0c000003; &bslash;&n;&t;orr&t;tmpreg, tmpreg, $mode; &bslash;&n;&t;teqp&t;tmpreg, $0
DECL|macro|RESTOREMODE
mdefine_line|#define RESTOREMODE(savereg) &bslash;&n;&t;teqp&t;savereg, $0
DECL|macro|SAVEIRQS
mdefine_line|#define SAVEIRQS(tmpreg)
DECL|macro|RESTOREIRQS
mdefine_line|#define RESTOREIRQS(tmpreg)
DECL|macro|DISABLEIRQS
mdefine_line|#define DISABLEIRQS(tmpreg)&bslash;&n;&t;teqp&t;pc, $0x08000003
DECL|macro|ENABLEIRQS
mdefine_line|#define ENABLEIRQS(tmpreg)&bslash;&n;&t;teqp&t;pc, $0x00000003
DECL|macro|USERMODE
mdefine_line|#define USERMODE(tmpreg)&bslash;&n;&t;teqp&t;pc, $0x00000000;&bslash;&n;&t;mov&t;r0, r0
DECL|macro|SVCMODE
mdefine_line|#define SVCMODE(tmpreg)&bslash;&n;&t;teqp&t;pc, $0x00000003;&bslash;&n;&t;mov&t;r0, r0
multiline_comment|/*&n; * Save the current IRQ state and disable IRQs&n; * Note that this macro assumes FIQs are enabled, and&n; * that the processor is in SVC mode.&n; */
DECL|variable|oldcpsr
dot
id|macro
id|save_and_disable_irqs
comma
id|oldcpsr
comma
id|temp
DECL|variable|oldcpsr
id|mov
"&bslash;"
id|oldcpsr
comma
id|pc
DECL|variable|temp
DECL|variable|oldcpsr
id|orr
"&bslash;"
id|temp
comma
"&bslash;"
id|oldcpsr
comma
macro_line|#0x08000000
DECL|variable|temp
id|teqp
"&bslash;"
id|temp
comma
macro_line|#0
dot
id|endm
multiline_comment|/*&n; * Restore interrupt state previously stored in&n; * a register&n; * ** Actually do nothing on Arc - hope that the caller uses a MOVS PC soon&n; * after!&n; */
dot
id|macro
id|restore_irqs
comma
id|oldcpsr
"@"
id|This
id|be
id|restore_irqs
dot
id|endm
multiline_comment|/*&n; * These two are used to save LR/restore PC over a user-based access.&n; * The old 26-bit architecture requires that we save lr (R14)&n; */
dot
id|macro
id|save_lr
id|str
id|lr
comma
(braket
id|sp
comma
macro_line|#-4]!
dot
id|endm
dot
id|macro
id|restore_pc
id|ldmfd
id|sp
op_logical_neg
comma
(brace
id|pc
)brace
op_xor
dot
id|endm
DECL|macro|USER
mdefine_line|#define USER(x...)&t;&t;&t;&t;&bslash;&n;9999:&t;x;&t;&t;&t;&t;&t;&bslash;&n;&t;.section __ex_table,&quot;a&quot;;&t;&t;&bslash;&n;&t;.align&t;3;&t;&t;&t;&t;&bslash;&n;&t;.long&t;9999b,9001f;&t;&t;&t;&bslash;&n;&t;.previous
eof
