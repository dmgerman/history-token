multiline_comment|/* $Id: gdb-stub.h,v 1.3 1998/07/20 17:52:19 ralf Exp $&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1995 Andreas Busse&n; */
macro_line|#ifndef __ASM_MIPS_GDB_STUB_H
DECL|macro|__ASM_MIPS_GDB_STUB_H
mdefine_line|#define __ASM_MIPS_GDB_STUB_H
multiline_comment|/*&n; * important register numbers&n; */
DECL|macro|REG_EPC
mdefine_line|#define REG_EPC&t;&t;&t;37
DECL|macro|REG_FP
mdefine_line|#define REG_FP&t;&t;&t;72
DECL|macro|REG_SP
mdefine_line|#define REG_SP&t;&t;&t;29
multiline_comment|/*&n; * Stack layout for the GDB exception handler&n; * Derived from the stack layout described in asm-mips/stackframe.h&n; *&n; * The first PTRSIZE*5 bytes are argument save space for C subroutines.&n; */
DECL|macro|NUMREGS
mdefine_line|#define NUMREGS&t;&t;&t;90
DECL|macro|GDB_FR_REG0
mdefine_line|#define GDB_FR_REG0&t;&t;(PTRSIZE*5)&t;&t;&t;/* 0 */
DECL|macro|GDB_FR_REG1
mdefine_line|#define GDB_FR_REG1&t;&t;((GDB_FR_REG0) + 4)&t;&t;/* 1 */
DECL|macro|GDB_FR_REG2
mdefine_line|#define GDB_FR_REG2&t;&t;((GDB_FR_REG1) + 4)&t;&t;/* 2 */
DECL|macro|GDB_FR_REG3
mdefine_line|#define GDB_FR_REG3&t;&t;((GDB_FR_REG2) + 4)&t;&t;/* 3 */
DECL|macro|GDB_FR_REG4
mdefine_line|#define GDB_FR_REG4&t;&t;((GDB_FR_REG3) + 4)&t;&t;/* 4 */
DECL|macro|GDB_FR_REG5
mdefine_line|#define GDB_FR_REG5&t;&t;((GDB_FR_REG4) + 4)&t;&t;/* 5 */
DECL|macro|GDB_FR_REG6
mdefine_line|#define GDB_FR_REG6&t;&t;((GDB_FR_REG5) + 4)&t;&t;/* 6 */
DECL|macro|GDB_FR_REG7
mdefine_line|#define GDB_FR_REG7&t;&t;((GDB_FR_REG6) + 4)&t;&t;/* 7 */
DECL|macro|GDB_FR_REG8
mdefine_line|#define GDB_FR_REG8&t;&t;((GDB_FR_REG7) + 4)&t;&t;/* 8 */
DECL|macro|GDB_FR_REG9
mdefine_line|#define GDB_FR_REG9&t;        ((GDB_FR_REG8) + 4)&t;&t;/* 9 */
DECL|macro|GDB_FR_REG10
mdefine_line|#define GDB_FR_REG10&t;&t;((GDB_FR_REG9) + 4)&t;&t;/* 10 */
DECL|macro|GDB_FR_REG11
mdefine_line|#define GDB_FR_REG11&t;&t;((GDB_FR_REG10) + 4)&t;&t;/* 11 */
DECL|macro|GDB_FR_REG12
mdefine_line|#define GDB_FR_REG12&t;&t;((GDB_FR_REG11) + 4)&t;&t;/* 12 */
DECL|macro|GDB_FR_REG13
mdefine_line|#define GDB_FR_REG13&t;&t;((GDB_FR_REG12) + 4)&t;&t;/* 13 */
DECL|macro|GDB_FR_REG14
mdefine_line|#define GDB_FR_REG14&t;&t;((GDB_FR_REG13) + 4)&t;&t;/* 14 */
DECL|macro|GDB_FR_REG15
mdefine_line|#define GDB_FR_REG15&t;&t;((GDB_FR_REG14) + 4)&t;&t;/* 15 */
DECL|macro|GDB_FR_REG16
mdefine_line|#define GDB_FR_REG16&t;&t;((GDB_FR_REG15) + 4)&t;&t;/* 16 */
DECL|macro|GDB_FR_REG17
mdefine_line|#define GDB_FR_REG17&t;&t;((GDB_FR_REG16) + 4)&t;&t;/* 17 */
DECL|macro|GDB_FR_REG18
mdefine_line|#define GDB_FR_REG18&t;&t;((GDB_FR_REG17) + 4)&t;&t;/* 18 */
DECL|macro|GDB_FR_REG19
mdefine_line|#define GDB_FR_REG19&t;&t;((GDB_FR_REG18) + 4)&t;&t;/* 19 */
DECL|macro|GDB_FR_REG20
mdefine_line|#define GDB_FR_REG20&t;&t;((GDB_FR_REG19) + 4)&t;&t;/* 20 */
DECL|macro|GDB_FR_REG21
mdefine_line|#define GDB_FR_REG21&t;&t;((GDB_FR_REG20) + 4)&t;&t;/* 21 */
DECL|macro|GDB_FR_REG22
mdefine_line|#define GDB_FR_REG22&t;&t;((GDB_FR_REG21) + 4)&t;&t;/* 22 */
DECL|macro|GDB_FR_REG23
mdefine_line|#define GDB_FR_REG23&t;&t;((GDB_FR_REG22) + 4)&t;&t;/* 23 */
DECL|macro|GDB_FR_REG24
mdefine_line|#define GDB_FR_REG24&t;&t;((GDB_FR_REG23) + 4)&t;&t;/* 24 */
DECL|macro|GDB_FR_REG25
mdefine_line|#define GDB_FR_REG25&t;&t;((GDB_FR_REG24) + 4)&t;&t;/* 25 */
DECL|macro|GDB_FR_REG26
mdefine_line|#define GDB_FR_REG26&t;&t;((GDB_FR_REG25) + 4)&t;&t;/* 26 */
DECL|macro|GDB_FR_REG27
mdefine_line|#define GDB_FR_REG27&t;&t;((GDB_FR_REG26) + 4)&t;&t;/* 27 */
DECL|macro|GDB_FR_REG28
mdefine_line|#define GDB_FR_REG28&t;&t;((GDB_FR_REG27) + 4)&t;&t;/* 28 */
DECL|macro|GDB_FR_REG29
mdefine_line|#define GDB_FR_REG29&t;&t;((GDB_FR_REG28) + 4)&t;&t;/* 29 */
DECL|macro|GDB_FR_REG30
mdefine_line|#define GDB_FR_REG30&t;&t;((GDB_FR_REG29) + 4)&t;&t;/* 30 */
DECL|macro|GDB_FR_REG31
mdefine_line|#define GDB_FR_REG31&t;&t;((GDB_FR_REG30) + 4)&t;&t;/* 31 */
multiline_comment|/*&n; * Saved special registers&n; */
DECL|macro|GDB_FR_STATUS
mdefine_line|#define GDB_FR_STATUS&t;&t;((GDB_FR_REG31) + 4)&t;&t;/* 32 */
DECL|macro|GDB_FR_LO
mdefine_line|#define GDB_FR_LO&t;&t;((GDB_FR_STATUS) + 4)&t;&t;/* 33 */
DECL|macro|GDB_FR_HI
mdefine_line|#define GDB_FR_HI&t;&t;((GDB_FR_LO) + 4)&t;&t;/* 34 */
DECL|macro|GDB_FR_BADVADDR
mdefine_line|#define GDB_FR_BADVADDR&t;&t;((GDB_FR_HI) + 4)&t;&t;/* 35 */
DECL|macro|GDB_FR_CAUSE
mdefine_line|#define GDB_FR_CAUSE&t;&t;((GDB_FR_BADVADDR) + 4)&t;&t;/* 36 */
DECL|macro|GDB_FR_EPC
mdefine_line|#define GDB_FR_EPC&t;&t;((GDB_FR_CAUSE) + 4)&t;&t;/* 37 */
multiline_comment|/*&n; * Saved floating point registers&n; */
DECL|macro|GDB_FR_FPR0
mdefine_line|#define GDB_FR_FPR0&t;&t;((GDB_FR_EPC) + 4)&t;&t;/* 38 */
DECL|macro|GDB_FR_FPR1
mdefine_line|#define GDB_FR_FPR1&t;&t;((GDB_FR_FPR0) + 4)&t;&t;/* 39 */
DECL|macro|GDB_FR_FPR2
mdefine_line|#define GDB_FR_FPR2&t;&t;((GDB_FR_FPR1) + 4)&t;&t;/* 40 */
DECL|macro|GDB_FR_FPR3
mdefine_line|#define GDB_FR_FPR3&t;&t;((GDB_FR_FPR2) + 4)&t;&t;/* 41 */
DECL|macro|GDB_FR_FPR4
mdefine_line|#define GDB_FR_FPR4&t;&t;((GDB_FR_FPR3) + 4)&t;&t;/* 42 */
DECL|macro|GDB_FR_FPR5
mdefine_line|#define GDB_FR_FPR5&t;&t;((GDB_FR_FPR4) + 4)&t;&t;/* 43 */
DECL|macro|GDB_FR_FPR6
mdefine_line|#define GDB_FR_FPR6&t;&t;((GDB_FR_FPR5) + 4)&t;&t;/* 44 */
DECL|macro|GDB_FR_FPR7
mdefine_line|#define GDB_FR_FPR7&t;&t;((GDB_FR_FPR6) + 4)&t;&t;/* 45 */
DECL|macro|GDB_FR_FPR8
mdefine_line|#define GDB_FR_FPR8&t;&t;((GDB_FR_FPR7) + 4)&t;&t;/* 46 */
DECL|macro|GDB_FR_FPR9
mdefine_line|#define GDB_FR_FPR9&t;&t;((GDB_FR_FPR8) + 4)&t;&t;/* 47 */
DECL|macro|GDB_FR_FPR10
mdefine_line|#define GDB_FR_FPR10&t;&t;((GDB_FR_FPR9) + 4)&t;&t;/* 48 */
DECL|macro|GDB_FR_FPR11
mdefine_line|#define GDB_FR_FPR11&t;&t;((GDB_FR_FPR10) + 4)&t;&t;/* 49 */
DECL|macro|GDB_FR_FPR12
mdefine_line|#define GDB_FR_FPR12&t;&t;((GDB_FR_FPR11) + 4)&t;&t;/* 50 */
DECL|macro|GDB_FR_FPR13
mdefine_line|#define GDB_FR_FPR13&t;&t;((GDB_FR_FPR12) + 4)&t;&t;/* 51 */
DECL|macro|GDB_FR_FPR14
mdefine_line|#define GDB_FR_FPR14&t;&t;((GDB_FR_FPR13) + 4)&t;&t;/* 52 */
DECL|macro|GDB_FR_FPR15
mdefine_line|#define GDB_FR_FPR15&t;&t;((GDB_FR_FPR14) + 4)&t;&t;/* 53 */
DECL|macro|GDB_FR_FPR16
mdefine_line|#define GDB_FR_FPR16&t;&t;((GDB_FR_FPR15) + 4)&t;&t;/* 54 */
DECL|macro|GDB_FR_FPR17
mdefine_line|#define GDB_FR_FPR17&t;&t;((GDB_FR_FPR16) + 4)&t;&t;/* 55 */
DECL|macro|GDB_FR_FPR18
mdefine_line|#define GDB_FR_FPR18&t;&t;((GDB_FR_FPR17) + 4)&t;&t;/* 56 */
DECL|macro|GDB_FR_FPR19
mdefine_line|#define GDB_FR_FPR19&t;&t;((GDB_FR_FPR18) + 4)&t;&t;/* 57 */
DECL|macro|GDB_FR_FPR20
mdefine_line|#define GDB_FR_FPR20&t;&t;((GDB_FR_FPR19) + 4)&t;&t;/* 58 */
DECL|macro|GDB_FR_FPR21
mdefine_line|#define GDB_FR_FPR21&t;&t;((GDB_FR_FPR20) + 4)&t;&t;/* 59 */
DECL|macro|GDB_FR_FPR22
mdefine_line|#define GDB_FR_FPR22&t;&t;((GDB_FR_FPR21) + 4)&t;&t;/* 60 */
DECL|macro|GDB_FR_FPR23
mdefine_line|#define GDB_FR_FPR23&t;&t;((GDB_FR_FPR22) + 4)&t;&t;/* 61 */
DECL|macro|GDB_FR_FPR24
mdefine_line|#define GDB_FR_FPR24&t;&t;((GDB_FR_FPR23) + 4)&t;&t;/* 62 */
DECL|macro|GDB_FR_FPR25
mdefine_line|#define GDB_FR_FPR25&t;&t;((GDB_FR_FPR24) + 4)&t;&t;/* 63 */
DECL|macro|GDB_FR_FPR26
mdefine_line|#define GDB_FR_FPR26&t;&t;((GDB_FR_FPR25) + 4)&t;&t;/* 64 */
DECL|macro|GDB_FR_FPR27
mdefine_line|#define GDB_FR_FPR27&t;&t;((GDB_FR_FPR26) + 4)&t;&t;/* 65 */
DECL|macro|GDB_FR_FPR28
mdefine_line|#define GDB_FR_FPR28&t;&t;((GDB_FR_FPR27) + 4)&t;&t;/* 66 */
DECL|macro|GDB_FR_FPR29
mdefine_line|#define GDB_FR_FPR29&t;&t;((GDB_FR_FPR28) + 4)&t;&t;/* 67 */
DECL|macro|GDB_FR_FPR30
mdefine_line|#define GDB_FR_FPR30&t;&t;((GDB_FR_FPR29) + 4)&t;&t;/* 68 */
DECL|macro|GDB_FR_FPR31
mdefine_line|#define GDB_FR_FPR31&t;&t;((GDB_FR_FPR30) + 4)&t;&t;/* 69 */
DECL|macro|GDB_FR_FSR
mdefine_line|#define GDB_FR_FSR&t;&t;((GDB_FR_FPR31) + 4)&t;&t;/* 70 */
DECL|macro|GDB_FR_FIR
mdefine_line|#define GDB_FR_FIR&t;&t;((GDB_FR_FSR) + 4)&t;&t;/* 71 */
DECL|macro|GDB_FR_FRP
mdefine_line|#define GDB_FR_FRP&t;&t;((GDB_FR_FIR) + 4)&t;&t;/* 72 */
DECL|macro|GDB_FR_DUMMY
mdefine_line|#define GDB_FR_DUMMY&t;&t;((GDB_FR_FRP) + 4)&t;&t;/* 73, unused ??? */
multiline_comment|/*&n; * Again, CP0 registers&n; */
DECL|macro|GDB_FR_CP0_INDEX
mdefine_line|#define GDB_FR_CP0_INDEX&t;((GDB_FR_DUMMY) + 4)&t;&t;/* 74 */
DECL|macro|GDB_FR_CP0_RANDOM
mdefine_line|#define GDB_FR_CP0_RANDOM&t;((GDB_FR_CP0_INDEX) + 4)&t;/* 75 */
DECL|macro|GDB_FR_CP0_ENTRYLO0
mdefine_line|#define GDB_FR_CP0_ENTRYLO0&t;((GDB_FR_CP0_RANDOM) + 4)&t;/* 76 */
DECL|macro|GDB_FR_CP0_ENTRYLO1
mdefine_line|#define GDB_FR_CP0_ENTRYLO1&t;((GDB_FR_CP0_ENTRYLO0) + 4)&t;/* 77 */
DECL|macro|GDB_FR_CP0_CONTEXT
mdefine_line|#define GDB_FR_CP0_CONTEXT&t;((GDB_FR_CP0_ENTRYLO1) + 4)&t;/* 78 */
DECL|macro|GDB_FR_CP0_PAGEMASK
mdefine_line|#define GDB_FR_CP0_PAGEMASK&t;((GDB_FR_CP0_CONTEXT) + 4)&t;/* 79 */
DECL|macro|GDB_FR_CP0_WIRED
mdefine_line|#define GDB_FR_CP0_WIRED&t;((GDB_FR_CP0_PAGEMASK) + 4)&t;/* 80 */
DECL|macro|GDB_FR_CP0_REG7
mdefine_line|#define GDB_FR_CP0_REG7&t;&t;((GDB_FR_CP0_WIRED) + 4)&t;/* 81 */
DECL|macro|GDB_FR_CP0_REG8
mdefine_line|#define GDB_FR_CP0_REG8&t;&t;((GDB_FR_CP0_REG7) + 4)&t;&t;/* 82 */
DECL|macro|GDB_FR_CP0_REG9
mdefine_line|#define GDB_FR_CP0_REG9&t;&t;((GDB_FR_CP0_REG8) + 4)&t;&t;/* 83 */
DECL|macro|GDB_FR_CP0_ENTRYHI
mdefine_line|#define GDB_FR_CP0_ENTRYHI&t;((GDB_FR_CP0_REG9) + 4)&t;&t;/* 84 */
DECL|macro|GDB_FR_CP0_REG11
mdefine_line|#define GDB_FR_CP0_REG11&t;((GDB_FR_CP0_ENTRYHI) + 4)&t;/* 85 */
DECL|macro|GDB_FR_CP0_REG12
mdefine_line|#define GDB_FR_CP0_REG12&t;((GDB_FR_CP0_REG11) + 4)&t;/* 86 */
DECL|macro|GDB_FR_CP0_REG13
mdefine_line|#define GDB_FR_CP0_REG13&t;((GDB_FR_CP0_REG12) + 4)&t;/* 87 */
DECL|macro|GDB_FR_CP0_REG14
mdefine_line|#define GDB_FR_CP0_REG14&t;((GDB_FR_CP0_REG13) + 4)&t;/* 88 */
DECL|macro|GDB_FR_CP0_PRID
mdefine_line|#define GDB_FR_CP0_PRID&t;&t;((GDB_FR_CP0_REG14) + 4)&t;/* 89 */
DECL|macro|GDB_FR_SIZE
mdefine_line|#define GDB_FR_SIZE&t;&t;((((GDB_FR_CP0_PRID) + 4) + (PTRSIZE-1)) &amp; ~(PTRSIZE-1))
macro_line|#ifndef _LANGUAGE_ASSEMBLY
multiline_comment|/*&n; * This is the same as above, but for the high-level&n; * part of the GDB stub.&n; */
DECL|struct|gdb_regs
r_struct
id|gdb_regs
(brace
multiline_comment|/*&n;&t; * Pad bytes for argument save space on the stack&n;&t; * 20/40 Bytes for 32/64 bit code&n;&t; */
DECL|member|pad0
r_int
r_int
id|pad0
(braket
l_int|5
)braket
suffix:semicolon
multiline_comment|/*&n;&t; * saved main processor registers&n;&t; */
DECL|member|reg0
DECL|member|reg1
DECL|member|reg2
DECL|member|reg3
DECL|member|reg4
DECL|member|reg5
DECL|member|reg6
DECL|member|reg7
r_int
id|reg0
comma
id|reg1
comma
id|reg2
comma
id|reg3
comma
id|reg4
comma
id|reg5
comma
id|reg6
comma
id|reg7
suffix:semicolon
DECL|member|reg8
DECL|member|reg9
DECL|member|reg10
DECL|member|reg11
DECL|member|reg12
DECL|member|reg13
DECL|member|reg14
DECL|member|reg15
r_int
id|reg8
comma
id|reg9
comma
id|reg10
comma
id|reg11
comma
id|reg12
comma
id|reg13
comma
id|reg14
comma
id|reg15
suffix:semicolon
DECL|member|reg16
DECL|member|reg17
DECL|member|reg18
DECL|member|reg19
DECL|member|reg20
DECL|member|reg21
DECL|member|reg22
DECL|member|reg23
r_int
id|reg16
comma
id|reg17
comma
id|reg18
comma
id|reg19
comma
id|reg20
comma
id|reg21
comma
id|reg22
comma
id|reg23
suffix:semicolon
DECL|member|reg24
DECL|member|reg25
DECL|member|reg26
DECL|member|reg27
DECL|member|reg28
DECL|member|reg29
DECL|member|reg30
DECL|member|reg31
r_int
id|reg24
comma
id|reg25
comma
id|reg26
comma
id|reg27
comma
id|reg28
comma
id|reg29
comma
id|reg30
comma
id|reg31
suffix:semicolon
multiline_comment|/*&n;&t; * Saved special registers&n;&t; */
DECL|member|cp0_status
r_int
id|cp0_status
suffix:semicolon
DECL|member|lo
r_int
id|lo
suffix:semicolon
DECL|member|hi
r_int
id|hi
suffix:semicolon
DECL|member|cp0_badvaddr
r_int
id|cp0_badvaddr
suffix:semicolon
DECL|member|cp0_cause
r_int
id|cp0_cause
suffix:semicolon
DECL|member|cp0_epc
r_int
id|cp0_epc
suffix:semicolon
multiline_comment|/*&n;&t; * Saved floating point registers&n;&t; */
DECL|member|fpr0
DECL|member|fpr1
DECL|member|fpr2
DECL|member|fpr3
DECL|member|fpr4
DECL|member|fpr5
DECL|member|fpr6
DECL|member|fpr7
r_int
id|fpr0
comma
id|fpr1
comma
id|fpr2
comma
id|fpr3
comma
id|fpr4
comma
id|fpr5
comma
id|fpr6
comma
id|fpr7
suffix:semicolon
DECL|member|fpr8
DECL|member|fpr9
DECL|member|fpr10
DECL|member|fpr11
DECL|member|fpr12
DECL|member|fpr13
DECL|member|fpr14
DECL|member|fpr15
r_int
id|fpr8
comma
id|fpr9
comma
id|fpr10
comma
id|fpr11
comma
id|fpr12
comma
id|fpr13
comma
id|fpr14
comma
id|fpr15
suffix:semicolon
DECL|member|fpr16
DECL|member|fpr17
DECL|member|fpr18
DECL|member|fpr19
DECL|member|fpr20
DECL|member|fpr21
DECL|member|fpr22
DECL|member|fpr23
r_int
id|fpr16
comma
id|fpr17
comma
id|fpr18
comma
id|fpr19
comma
id|fpr20
comma
id|fpr21
comma
id|fpr22
comma
id|fpr23
suffix:semicolon
DECL|member|fpr24
DECL|member|fpr25
DECL|member|fpr26
DECL|member|fpr27
DECL|member|fpr28
DECL|member|fpr29
DECL|member|fpr30
DECL|member|fpr31
r_int
id|fpr24
comma
id|fpr25
comma
id|fpr26
comma
id|fpr27
comma
id|fpr28
comma
id|fpr29
comma
id|fpr30
comma
id|fpr31
suffix:semicolon
DECL|member|cp1_fsr
r_int
id|cp1_fsr
suffix:semicolon
DECL|member|cp1_fir
r_int
id|cp1_fir
suffix:semicolon
multiline_comment|/*&n;&t; * Frame pointer&n;&t; */
DECL|member|frame_ptr
r_int
id|frame_ptr
suffix:semicolon
DECL|member|dummy
r_int
id|dummy
suffix:semicolon
multiline_comment|/* unused */
multiline_comment|/*&n;&t; * saved cp0 registers&n;&t; */
DECL|member|cp0_index
r_int
id|cp0_index
suffix:semicolon
DECL|member|cp0_random
r_int
id|cp0_random
suffix:semicolon
DECL|member|cp0_entrylo0
r_int
id|cp0_entrylo0
suffix:semicolon
DECL|member|cp0_entrylo1
r_int
id|cp0_entrylo1
suffix:semicolon
DECL|member|cp0_context
r_int
id|cp0_context
suffix:semicolon
DECL|member|cp0_pagemask
r_int
id|cp0_pagemask
suffix:semicolon
DECL|member|cp0_wired
r_int
id|cp0_wired
suffix:semicolon
DECL|member|cp0_reg7
r_int
id|cp0_reg7
suffix:semicolon
DECL|member|cp0_reg8
r_int
id|cp0_reg8
suffix:semicolon
DECL|member|cp0_reg9
r_int
id|cp0_reg9
suffix:semicolon
DECL|member|cp0_entryhi
r_int
id|cp0_entryhi
suffix:semicolon
DECL|member|cp0_reg11
r_int
id|cp0_reg11
suffix:semicolon
DECL|member|cp0_reg12
r_int
id|cp0_reg12
suffix:semicolon
DECL|member|cp0_reg13
r_int
id|cp0_reg13
suffix:semicolon
DECL|member|cp0_reg14
r_int
id|cp0_reg14
suffix:semicolon
DECL|member|cp0_prid
r_int
id|cp0_prid
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Prototypes&n; */
r_void
id|set_debug_traps
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* _LANGUAGE_ASSEMBLY */
macro_line|#endif /* __ASM_MIPS_GDB_STUB_H */
eof
