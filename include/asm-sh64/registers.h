macro_line|#ifndef __ASM_SH64_REGISTERS_H
DECL|macro|__ASM_SH64_REGISTERS_H
mdefine_line|#define __ASM_SH64_REGISTERS_H
multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * include/asm-sh64/registers.h&n; *&n; * Copyright (C) 2000, 2001  Paolo Alberelli&n; * Copyright (C) 2004  Richard Curnow&n; */
macro_line|#ifdef __ASSEMBLY__
multiline_comment|/* =====================================================================&n;**&n;** Section 1: acts on assembly sources pre-processed by GPP ( &lt;source.S&gt;).&n;**&t;      Assigns symbolic names to control &amp; target registers.&n;*/
multiline_comment|/*&n; * Define some useful aliases for control registers.&n; */
DECL|macro|SR
mdefine_line|#define SR&t;cr0
DECL|macro|SSR
mdefine_line|#define SSR&t;cr1
DECL|macro|PSSR
mdefine_line|#define PSSR&t;cr2
multiline_comment|/* cr3 UNDEFINED */
DECL|macro|INTEVT
mdefine_line|#define INTEVT&t;cr4
DECL|macro|EXPEVT
mdefine_line|#define EXPEVT&t;cr5
DECL|macro|PEXPEVT
mdefine_line|#define PEXPEVT&t;cr6
DECL|macro|TRA
mdefine_line|#define TRA&t;cr7
DECL|macro|SPC
mdefine_line|#define SPC&t;cr8
DECL|macro|PSPC
mdefine_line|#define PSPC&t;cr9
DECL|macro|RESVEC
mdefine_line|#define RESVEC&t;cr10
DECL|macro|VBR
mdefine_line|#define VBR&t;cr11
multiline_comment|/* cr12 UNDEFINED */
DECL|macro|TEA
mdefine_line|#define TEA&t;cr13
multiline_comment|/* cr14-cr15 UNDEFINED */
DECL|macro|DCR
mdefine_line|#define DCR&t;cr16
DECL|macro|KCR0
mdefine_line|#define KCR0&t;cr17
DECL|macro|KCR1
mdefine_line|#define KCR1&t;cr18
multiline_comment|/* cr19-cr31 UNDEFINED */
multiline_comment|/* cr32-cr61 RESERVED */
DECL|macro|CTC
mdefine_line|#define CTC&t;cr62
DECL|macro|USR
mdefine_line|#define USR&t;cr63
multiline_comment|/*&n; * ABI dependent registers (general purpose set)&n; */
DECL|macro|RET
mdefine_line|#define RET&t;r2
DECL|macro|ARG1
mdefine_line|#define ARG1&t;r2
DECL|macro|ARG2
mdefine_line|#define ARG2&t;r3
DECL|macro|ARG3
mdefine_line|#define ARG3&t;r4
DECL|macro|ARG4
mdefine_line|#define ARG4&t;r5
DECL|macro|ARG5
mdefine_line|#define ARG5&t;r6
DECL|macro|ARG6
mdefine_line|#define ARG6&t;r7
DECL|macro|SP
mdefine_line|#define SP&t;r15
DECL|macro|LINK
mdefine_line|#define LINK&t;r18
DECL|macro|ZERO
mdefine_line|#define ZERO&t;r63
multiline_comment|/*&n; * Status register defines: used only by assembly sources (and&n; * &t;&t;&t;    syntax independednt)&n; */
DECL|macro|SR_RESET_VAL
mdefine_line|#define SR_RESET_VAL&t;0x0000000050008000
DECL|macro|SR_HARMLESS
mdefine_line|#define SR_HARMLESS&t;0x00000000500080f0&t;/* Write ignores for most */
DECL|macro|SR_ENABLE_FPU
mdefine_line|#define SR_ENABLE_FPU&t;0xffffffffffff7fff&t;/* AND with this */
macro_line|#if defined (CONFIG_SH64_SR_WATCH)
DECL|macro|SR_ENABLE_MMU
mdefine_line|#define SR_ENABLE_MMU&t;0x0000000084000000&t;/* OR with this */
macro_line|#else
DECL|macro|SR_ENABLE_MMU
mdefine_line|#define SR_ENABLE_MMU&t;0x0000000080000000&t;/* OR with this */
macro_line|#endif
DECL|macro|SR_UNBLOCK_EXC
mdefine_line|#define SR_UNBLOCK_EXC&t;0xffffffffefffffff&t;/* AND with this */
DECL|macro|SR_BLOCK_EXC
mdefine_line|#define SR_BLOCK_EXC&t;0x0000000010000000&t;/* OR with this */
macro_line|#else&t;/* Not __ASSEMBLY__ syntax */
multiline_comment|/*&n;** Stringify reg. name&n;*/
DECL|macro|__str
mdefine_line|#define __str(x)  #x
multiline_comment|/* Stringify control register names for use in inline assembly */
DECL|macro|__SR
mdefine_line|#define __SR __str(SR)
DECL|macro|__SSR
mdefine_line|#define __SSR __str(SSR)
DECL|macro|__PSSR
mdefine_line|#define __PSSR __str(PSSR)
DECL|macro|__INTEVT
mdefine_line|#define __INTEVT __str(INTEVT)
DECL|macro|__EXPEVT
mdefine_line|#define __EXPEVT __str(EXPEVT)
DECL|macro|__PEXPEVT
mdefine_line|#define __PEXPEVT __str(PEXPEVT)
DECL|macro|__TRA
mdefine_line|#define __TRA __str(TRA)
DECL|macro|__SPC
mdefine_line|#define __SPC __str(SPC)
DECL|macro|__PSPC
mdefine_line|#define __PSPC __str(PSPC)
DECL|macro|__RESVEC
mdefine_line|#define __RESVEC __str(RESVEC)
DECL|macro|__VBR
mdefine_line|#define __VBR __str(VBR)
DECL|macro|__TEA
mdefine_line|#define __TEA __str(TEA)
DECL|macro|__DCR
mdefine_line|#define __DCR __str(DCR)
DECL|macro|__KCR0
mdefine_line|#define __KCR0 __str(KCR0)
DECL|macro|__KCR1
mdefine_line|#define __KCR1 __str(KCR1)
DECL|macro|__CTC
mdefine_line|#define __CTC __str(CTC)
DECL|macro|__USR
mdefine_line|#define __USR __str(USR)
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif /* __ASM_SH64_REGISTERS_H */
eof
