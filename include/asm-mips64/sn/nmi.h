multiline_comment|/* &n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997 Silicon Graphics, Inc.&n; */
macro_line|#ifndef __ASM_SN_NMI_H
DECL|macro|__ASM_SN_NMI_H
mdefine_line|#define __ASM_SN_NMI_H
macro_line|#ident &quot;$Revision: 1.2 $&quot;
macro_line|#include &lt;asm/sn/addrs.h&gt;
multiline_comment|/*&n; * The launch data structure resides at a fixed place in each node&squot;s memory&n; * and is used to communicate between the master processor and the slave&n; * processors.&n; *&n; * The master stores launch parameters in the launch structure&n; * corresponding to a target processor that is in a slave loop, then sends&n; * an interrupt to the slave processor.  The slave calls the desired&n; * function, followed by an optional rendezvous function, then returns to&n; * the slave loop.  The master does not wait for the slaves before&n; * returning.&n; *&n; * There is an array of launch structures, one per CPU on the node.  One&n; * interrupt level is used per CPU.&n; */
DECL|macro|NMI_MAGIC
mdefine_line|#define NMI_MAGIC&t;&t;0x48414d4d455201
DECL|macro|NMI_SIZEOF
mdefine_line|#define NMI_SIZEOF&t;&t;0x40
DECL|macro|NMI_OFF_MAGIC
mdefine_line|#define NMI_OFF_MAGIC&t;&t;0x00&t;/* Struct offsets for assembly      */
DECL|macro|NMI_OFF_FLAGS
mdefine_line|#define NMI_OFF_FLAGS&t;&t;0x08
DECL|macro|NMI_OFF_CALL
mdefine_line|#define NMI_OFF_CALL&t;&t;0x10
DECL|macro|NMI_OFF_CALLC
mdefine_line|#define NMI_OFF_CALLC&t;&t;0x18
DECL|macro|NMI_OFF_CALLPARM
mdefine_line|#define NMI_OFF_CALLPARM&t;0x20
DECL|macro|NMI_OFF_GMASTER
mdefine_line|#define NMI_OFF_GMASTER&t;&t;0x28
multiline_comment|/*&n; * The NMI routine is called only if the complement address is&n; * correct.&n; *&n; * Before control is transferred to a routine, the compliment address&n; * is zeroed (invalidated) to prevent an accidental call from a spurious&n; * interrupt.&n; *&n; */
macro_line|#ifdef _LANGUAGE_C
DECL|struct|nmi_s
r_typedef
r_struct
id|nmi_s
(brace
DECL|member|magic
r_volatile
r_int
r_int
id|magic
suffix:semicolon
multiline_comment|/* Magic number */
DECL|member|flags
r_volatile
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* Combination of flags above */
DECL|member|call_addr
r_volatile
r_void
op_star
id|call_addr
suffix:semicolon
multiline_comment|/* Routine for slave to call        */
DECL|member|call_addr_c
r_volatile
r_void
op_star
id|call_addr_c
suffix:semicolon
multiline_comment|/* 1&squot;s complement of address        */
DECL|member|call_parm
r_volatile
r_void
op_star
id|call_parm
suffix:semicolon
multiline_comment|/* Single parm passed to call&t;    */
DECL|member|gmaster
r_volatile
r_int
r_int
id|gmaster
suffix:semicolon
multiline_comment|/* Flag true only on global master*/
DECL|typedef|nmi_t
)brace
id|nmi_t
suffix:semicolon
macro_line|#endif /* _LANGUAGE_C */
multiline_comment|/* Following definitions are needed both in the prom &amp; the kernel&n; * to identify the format of the nmi cpu register save area in the&n; * low memory on each node.&n; */
macro_line|#ifdef _LANGUAGE_C
DECL|struct|reg_struct
r_struct
id|reg_struct
(brace
DECL|member|gpr
r_int
r_int
id|gpr
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|sr
r_int
r_int
id|sr
suffix:semicolon
DECL|member|cause
r_int
r_int
id|cause
suffix:semicolon
DECL|member|epc
r_int
r_int
id|epc
suffix:semicolon
DECL|member|badva
r_int
r_int
id|badva
suffix:semicolon
DECL|member|error_epc
r_int
r_int
id|error_epc
suffix:semicolon
DECL|member|cache_err
r_int
r_int
id|cache_err
suffix:semicolon
DECL|member|nmi_sr
r_int
r_int
id|nmi_sr
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* _LANGUAGE_C */
multiline_comment|/* These are the assembly language offsets into the reg_struct structure */
DECL|macro|R0_OFF
mdefine_line|#define R0_OFF&t;&t;0x0
DECL|macro|R1_OFF
mdefine_line|#define R1_OFF&t;&t;0x8
DECL|macro|R2_OFF
mdefine_line|#define R2_OFF&t;&t;0x10
DECL|macro|R3_OFF
mdefine_line|#define R3_OFF&t;&t;0x18
DECL|macro|R4_OFF
mdefine_line|#define R4_OFF&t;&t;0x20
DECL|macro|R5_OFF
mdefine_line|#define R5_OFF&t;&t;0x28
DECL|macro|R6_OFF
mdefine_line|#define R6_OFF&t;&t;0x30
DECL|macro|R7_OFF
mdefine_line|#define R7_OFF&t;&t;0x38
DECL|macro|R8_OFF
mdefine_line|#define R8_OFF&t;&t;0x40
DECL|macro|R9_OFF
mdefine_line|#define R9_OFF&t;&t;0x48
DECL|macro|R10_OFF
mdefine_line|#define R10_OFF&t;&t;0x50
DECL|macro|R11_OFF
mdefine_line|#define R11_OFF&t;&t;0x58
DECL|macro|R12_OFF
mdefine_line|#define R12_OFF&t;&t;0x60
DECL|macro|R13_OFF
mdefine_line|#define R13_OFF&t;&t;0x68
DECL|macro|R14_OFF
mdefine_line|#define R14_OFF&t;&t;0x70
DECL|macro|R15_OFF
mdefine_line|#define R15_OFF&t;&t;0x78
DECL|macro|R16_OFF
mdefine_line|#define R16_OFF&t;&t;0x80
DECL|macro|R17_OFF
mdefine_line|#define R17_OFF&t;&t;0x88
DECL|macro|R18_OFF
mdefine_line|#define R18_OFF&t;&t;0x90
DECL|macro|R19_OFF
mdefine_line|#define R19_OFF&t;&t;0x98
DECL|macro|R20_OFF
mdefine_line|#define R20_OFF&t;&t;0xa0
DECL|macro|R21_OFF
mdefine_line|#define R21_OFF&t;&t;0xa8
DECL|macro|R22_OFF
mdefine_line|#define R22_OFF&t;&t;0xb0
DECL|macro|R23_OFF
mdefine_line|#define R23_OFF&t;&t;0xb8
DECL|macro|R24_OFF
mdefine_line|#define R24_OFF&t;&t;0xc0
DECL|macro|R25_OFF
mdefine_line|#define R25_OFF&t;&t;0xc8
DECL|macro|R26_OFF
mdefine_line|#define R26_OFF&t;&t;0xd0
DECL|macro|R27_OFF
mdefine_line|#define R27_OFF&t;&t;0xd8
DECL|macro|R28_OFF
mdefine_line|#define R28_OFF&t;&t;0xe0
DECL|macro|R29_OFF
mdefine_line|#define R29_OFF&t;&t;0xe8
DECL|macro|R30_OFF
mdefine_line|#define R30_OFF&t;&t;0xf0
DECL|macro|R31_OFF
mdefine_line|#define R31_OFF&t;&t;0xf8
DECL|macro|SR_OFF
mdefine_line|#define SR_OFF&t;&t;0x100
DECL|macro|CAUSE_OFF
mdefine_line|#define CAUSE_OFF&t;0x108
DECL|macro|EPC_OFF
mdefine_line|#define EPC_OFF&t;&t;0x110
DECL|macro|BADVA_OFF
mdefine_line|#define BADVA_OFF&t;0x118
DECL|macro|ERROR_EPC_OFF
mdefine_line|#define ERROR_EPC_OFF&t;0x120
DECL|macro|CACHE_ERR_OFF
mdefine_line|#define CACHE_ERR_OFF&t;0x128
DECL|macro|NMISR_OFF
mdefine_line|#define NMISR_OFF&t;0x130
macro_line|#endif /* __ASM_SN_NMI_H */
eof
