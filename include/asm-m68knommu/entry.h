macro_line|#ifndef __M68KNOMMU_ENTRY_H
DECL|macro|__M68KNOMMU_ENTRY_H
mdefine_line|#define __M68KNOMMU_ENTRY_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/page.h&gt;
multiline_comment|/*&n; * Stack layout in &squot;ret_from_exception&squot;:&n; *&n; * This allows access to the syscall arguments in registers d1-d5&n; *&n; *&t; 0(sp) - d1&n; *&t; 4(sp) - d2&n; *&t; 8(sp) - d3&n; *&t; C(sp) - d4&n; *&t;10(sp) - d5&n; *&t;14(sp) - a0&n; *&t;18(sp) - a1&n; *&t;1C(sp) - a2&n; *&t;20(sp) - d0&n; *&t;24(sp) - orig_d0&n; *&t;28(sp) - stack adjustment&n; *&t;2C(sp) - [ sr              ] [ format &amp; vector ]&n; *&t;2E(sp) - [ pc              ] [ sr              ]&n; *&t;30(sp) - [ format &amp; vector ] [ pc              ]&n; *&t;&t;  ^^^^^^^^^^^^^^^^^   ^^^^^^^^^^^^^^^^^&n; *&t;&t;&t;M68K&t;&t;  COLDFIRE&n; */
DECL|macro|ALLOWINT
mdefine_line|#define ALLOWINT 0xf8ff
macro_line|#ifdef __ASSEMBLY__
multiline_comment|/* process bits for task_struct.flags */
id|PF_TRACESYS_OFF
op_assign
l_int|3
id|PF_TRACESYS_BIT
op_assign
l_int|5
id|PF_PTRACED_OFF
op_assign
l_int|3
id|PF_PTRACED_BIT
op_assign
l_int|4
id|PF_DTRACE_OFF
op_assign
l_int|1
id|PF_DTRACE_BIT
op_assign
l_int|5
id|LENOSYS
op_assign
l_int|38
id|LD0
op_assign
l_int|0x20
id|LORIG_D0
op_assign
l_int|0x24
id|LFORMATVEC
op_assign
l_int|0x2c
id|LSR
op_assign
l_int|0x2e
id|LPC
op_assign
l_int|0x30
DECL|macro|SWITCH_STACK_SIZE
mdefine_line|#define SWITCH_STACK_SIZE (6*4+4)&t;/* Includes return address */
multiline_comment|/*&n; * This defines the normal kernel pt-regs layout.&n; *&n; * regs are a2-a6 and d6-d7 preserved by C code&n; * the kernel doesn&squot;t mess with usp unless it needs to&n; */
macro_line|#ifdef CONFIG_COLDFIRE
multiline_comment|/*&n; * This is made a little more tricky on the ColdFire. There is no&n; * separate kernel and user stack pointers. Need to artificially&n; * construct a usp in software... When doing this we need to disable&n; * interrupts, otherwise bad things could happen.&n; */
dot
id|macro
id|SAVE_ALL
id|move
macro_line|#0x2700,%sr&t;&t;/* disable intrs */
DECL|variable|btst
id|btst
macro_line|#5,%sp@(2)&t;&t;/* from user? */
id|bnes
l_float|6f
multiline_comment|/* no, skip */
DECL|variable|sp
id|movel
op_mod
id|sp
comma
id|sw_usp
multiline_comment|/* save user sp */
DECL|variable|addql
id|addql
macro_line|#8,sw_usp&t;&t;/* remove exception */
DECL|variable|sw_ksp
id|movel
id|sw_ksp
comma
op_mod
id|sp
multiline_comment|/* kernel sp */
DECL|variable|subql
id|subql
macro_line|#8,%sp&t;&t;&t;/* room for exception */
id|clrl
op_mod
id|sp
"@"
op_minus
multiline_comment|/* stk_adj */
id|movel
op_mod
id|d0
comma
op_mod
id|sp
"@"
op_minus
multiline_comment|/* orig d0 */
id|movel
op_mod
id|d0
comma
op_mod
id|sp
"@"
op_minus
multiline_comment|/* d0 */
id|subl
macro_line|#32,%sp&t;&t;&t;/* space for 8 regs */
id|moveml
op_mod
id|d1
op_minus
op_mod
id|d5
op_div
op_mod
id|a0
op_minus
op_mod
id|a2
comma
op_mod
id|sp
"@"
DECL|variable|sw_usp
id|movel
id|sw_usp
comma
op_mod
id|a0
multiline_comment|/* get usp */
id|moveml
op_mod
id|a0
"@"
(paren
op_minus
l_int|8
)paren
comma
op_mod
id|d1
op_minus
op_mod
id|d2
multiline_comment|/* get exception */
id|moveml
op_mod
id|d1
op_minus
op_mod
id|d2
comma
op_mod
id|sp
"@"
(paren
id|LFORMATVEC
)paren
multiline_comment|/* copy exception */
id|bra
l_float|7f
l_int|6
suffix:colon
id|clrl
op_mod
id|sp
"@"
op_minus
multiline_comment|/* stk_adj */
id|movel
op_mod
id|d0
comma
op_mod
id|sp
"@"
op_minus
multiline_comment|/* orig d0 */
id|movel
op_mod
id|d0
comma
op_mod
id|sp
"@"
op_minus
multiline_comment|/* d0 */
id|subl
macro_line|#32,%sp&t;&t;&t;/* space for 7 regs */
id|moveml
op_mod
id|d1
op_minus
op_mod
id|d5
op_div
op_mod
id|a0
op_minus
op_mod
id|a2
comma
op_mod
id|sp
"@"
l_int|7
suffix:colon
dot
id|endm
dot
id|macro
id|RESTORE_ALL
id|btst
macro_line|#5,%sp@(LSR)&t;&t;/* going user? */
id|bnes
l_float|8f
multiline_comment|/* no, skip */
id|move
macro_line|#0x2700,%sr&t;&t;/* disable intrs */
id|movel
id|sw_usp
comma
op_mod
id|a0
multiline_comment|/* get usp */
id|moveml
op_mod
id|sp
"@"
(paren
id|LFORMATVEC
)paren
comma
op_mod
id|d1
op_minus
op_mod
id|d2
multiline_comment|/* copy exception */
id|moveml
op_mod
id|d1
op_minus
op_mod
id|d2
comma
op_mod
id|a0
"@"
(paren
op_minus
l_int|8
)paren
id|moveml
op_mod
id|sp
"@"
comma
op_mod
id|d1
op_minus
op_mod
id|d5
op_div
op_mod
id|a0
op_minus
op_mod
id|a2
id|addl
macro_line|#32,%sp&t;&t;&t;/* space for 8 regs */
id|movel
op_mod
id|sp
"@"
op_plus
comma
op_mod
id|d0
id|addql
macro_line|#4,%sp&t;&t;&t;/* orig d0 */
id|addl
op_mod
id|sp
"@"
op_plus
comma
op_mod
id|sp
multiline_comment|/* stk adj */
id|addql
macro_line|#8,%sp&t;&t;&t;/* remove exception */
id|movel
op_mod
id|sp
comma
id|sw_ksp
multiline_comment|/* save ksp */
id|subql
macro_line|#8,sw_usp&t;&t;/* set exception */
id|movel
id|sw_usp
comma
op_mod
id|sp
multiline_comment|/* restore usp */
id|rte
l_int|8
suffix:colon
id|moveml
op_mod
id|sp
"@"
comma
op_mod
id|d1
op_minus
op_mod
id|d5
op_div
op_mod
id|a0
op_minus
op_mod
id|a2
id|addl
macro_line|#32,%sp&t;&t;&t;/* space for 8 regs */
id|movel
op_mod
id|sp
"@"
op_plus
comma
op_mod
id|d0
id|addql
macro_line|#4,%sp&t;&t;&t;/* orig d0 */
id|addl
op_mod
id|sp
"@"
op_plus
comma
op_mod
id|sp
multiline_comment|/* stk adj */
id|rte
dot
id|endm
multiline_comment|/*&n; * Quick exception save, use current stack only.&n; */
dot
id|macro
id|SAVE_LOCAL
id|move
macro_line|#0x2700,%sr&t;&t;/* disable intrs */
id|clrl
op_mod
id|sp
"@"
op_minus
multiline_comment|/* stk_adj */
id|movel
op_mod
id|d0
comma
op_mod
id|sp
"@"
op_minus
multiline_comment|/* orig d0 */
id|movel
op_mod
id|d0
comma
op_mod
id|sp
"@"
op_minus
multiline_comment|/* d0 */
id|subl
macro_line|#32,%sp&t;&t;&t;/* space for 8 regs */
id|moveml
op_mod
id|d1
op_minus
op_mod
id|d5
op_div
op_mod
id|a0
op_minus
op_mod
id|a2
comma
op_mod
id|sp
"@"
dot
id|endm
dot
id|macro
id|RESTORE_LOCAL
id|moveml
op_mod
id|sp
"@"
comma
op_mod
id|d1
op_minus
op_mod
id|d5
op_div
op_mod
id|a0
op_minus
op_mod
id|a2
id|addl
macro_line|#32,%sp&t;&t;&t;/* space for 8 regs */
id|movel
op_mod
id|sp
"@"
op_plus
comma
op_mod
id|d0
id|addql
macro_line|#4,%sp&t;&t;&t;/* orig d0 */
id|addl
op_mod
id|sp
"@"
op_plus
comma
op_mod
id|sp
multiline_comment|/* stk adj */
id|rte
dot
id|endm
dot
id|macro
id|SAVE_SWITCH_STACK
id|subl
macro_line|#24,%sp&t;&t;&t;/* 6 regs */
id|moveml
op_mod
id|a3
op_minus
op_mod
id|a6
op_div
op_mod
id|d6
op_minus
op_mod
id|d7
comma
op_mod
id|sp
"@"
dot
id|endm
dot
id|macro
id|RESTORE_SWITCH_STACK
id|moveml
op_mod
id|sp
"@"
comma
op_mod
id|a3
op_minus
op_mod
id|a6
op_div
op_mod
id|d6
op_minus
op_mod
id|d7
id|addl
macro_line|#24,%sp&t;&t;&t;/* 6 regs */
dot
id|endm
multiline_comment|/*&n; * Software copy of the user and kernel stack pointers... Ugh...&n; * Need these to get around ColdFire not having separate kernel&n; * and user stack pointers.&n; */
dot
id|globl
id|sw_usp
dot
id|globl
id|sw_ksp
macro_line|#else /* !CONFIG_COLDFIRE */
multiline_comment|/*&n; * Standard 68k interrupt entry and exit macros.&n; */
dot
id|macro
id|SAVE_ALL
id|clrl
op_mod
id|sp
"@"
op_minus
multiline_comment|/* stk_adj */
id|movel
op_mod
id|d0
comma
op_mod
id|sp
"@"
op_minus
multiline_comment|/* orig d0 */
id|movel
op_mod
id|d0
comma
op_mod
id|sp
"@"
op_minus
multiline_comment|/* d0 */
id|moveml
op_mod
id|d1
op_minus
op_mod
id|d5
op_div
op_mod
id|a0
op_minus
op_mod
id|a2
comma
op_mod
id|sp
"@"
op_minus
dot
id|endm
dot
id|macro
id|RESTORE_ALL
id|moveml
op_mod
id|sp
"@"
op_plus
comma
op_mod
id|a0
op_minus
op_mod
id|a2
op_div
op_mod
id|d1
op_minus
op_mod
id|d5
id|movel
op_mod
id|sp
"@"
op_plus
comma
op_mod
id|d0
id|addql
macro_line|#4,%sp&t;&t;&t;/* orig d0 */
id|addl
op_mod
id|sp
"@"
op_plus
comma
op_mod
id|sp
multiline_comment|/* stk adj */
id|rte
dot
id|endm
dot
id|macro
id|SAVE_SWITCH_STACK
id|moveml
op_mod
id|a3
op_minus
op_mod
id|a6
op_div
op_mod
id|d6
op_minus
op_mod
id|d7
comma
op_mod
id|sp
"@"
op_minus
dot
id|endm
dot
id|macro
id|RESTORE_SWITCH_STACK
id|moveml
op_mod
id|sp
"@"
op_plus
comma
op_mod
id|a3
op_minus
op_mod
id|a6
op_div
op_mod
id|d6
op_minus
op_mod
id|d7
dot
id|endm
macro_line|#endif /* !CONFIG_COLDFIRE */
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif /* __M68KNOMMU_ENTRY_H */
eof
