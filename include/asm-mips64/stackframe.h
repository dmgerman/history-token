multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1994, 1995, 1996, 1999 Ralf Baechle&n; * Copyright (C) 1994, 1995, 1996 Paul M. Antoine.&n; * Copyright (C) 1999 Silicon Graphics, Inc.&n; */
macro_line|#ifndef __ASM_STACKFRAME_H
DECL|macro|__ASM_STACKFRAME_H
mdefine_line|#define __ASM_STACKFRAME_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;asm/asm.h&gt;
macro_line|#include &lt;asm/offset.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#ifndef __ASSEMBLY__
DECL|macro|__str2
mdefine_line|#define __str2(x) #x
DECL|macro|__str
mdefine_line|#define __str(x) __str2(x)
DECL|macro|save_static
mdefine_line|#define save_static(frame)                               &bslash;&n;&t;__asm__ __volatile__(                            &bslash;&n;&t;&t;&quot;sd&bslash;t$16,&quot;__str(PT_R16)&quot;(%0)&bslash;n&bslash;t&quot;        &bslash;&n;&t;&t;&quot;sd&bslash;t$17,&quot;__str(PT_R17)&quot;(%0)&bslash;n&bslash;t&quot;        &bslash;&n;&t;&t;&quot;sd&bslash;t$18,&quot;__str(PT_R18)&quot;(%0)&bslash;n&bslash;t&quot;        &bslash;&n;&t;&t;&quot;sd&bslash;t$19,&quot;__str(PT_R19)&quot;(%0)&bslash;n&bslash;t&quot;        &bslash;&n;&t;&t;&quot;sd&bslash;t$20,&quot;__str(PT_R20)&quot;(%0)&bslash;n&bslash;t&quot;        &bslash;&n;&t;&t;&quot;sd&bslash;t$21,&quot;__str(PT_R21)&quot;(%0)&bslash;n&bslash;t&quot;        &bslash;&n;&t;&t;&quot;sd&bslash;t$22,&quot;__str(PT_R22)&quot;(%0)&bslash;n&bslash;t&quot;        &bslash;&n;&t;&t;&quot;sd&bslash;t$23,&quot;__str(PT_R23)&quot;(%0)&bslash;n&bslash;t&quot;        &bslash;&n;&t;&t;&quot;sd&bslash;t$30,&quot;__str(PT_R30)&quot;(%0)&bslash;n&bslash;t&quot;        &bslash;&n;&t;&t;: /* No outputs */                       &bslash;&n;&t;&t;: &quot;r&quot; (frame))
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#ifdef __ASSEMBLY__
dot
id|macro
id|SAVE_AT
dot
id|set
id|push
dot
id|set
id|noat
id|sd
"$"
l_int|1
comma
id|PT_R1
c_func
(paren
id|sp
)paren
dot
id|set
id|pop
dot
id|endm
dot
id|macro
id|SAVE_TEMP
id|mfhi
id|v1
id|sd
"$"
l_int|8
comma
id|PT_R8
c_func
(paren
id|sp
)paren
id|sd
"$"
l_int|9
comma
id|PT_R9
c_func
(paren
id|sp
)paren
id|sd
id|v1
comma
id|PT_HI
c_func
(paren
id|sp
)paren
id|mflo
id|v1
id|sd
"$"
l_int|10
comma
id|PT_R10
c_func
(paren
id|sp
)paren
id|sd
"$"
l_int|11
comma
id|PT_R11
c_func
(paren
id|sp
)paren
id|sd
id|v1
comma
id|PT_LO
c_func
(paren
id|sp
)paren
id|sd
"$"
l_int|12
comma
id|PT_R12
c_func
(paren
id|sp
)paren
id|sd
"$"
l_int|13
comma
id|PT_R13
c_func
(paren
id|sp
)paren
id|sd
"$"
l_int|14
comma
id|PT_R14
c_func
(paren
id|sp
)paren
id|sd
"$"
l_int|15
comma
id|PT_R15
c_func
(paren
id|sp
)paren
id|sd
"$"
l_int|24
comma
id|PT_R24
c_func
(paren
id|sp
)paren
dot
id|endm
dot
id|macro
id|SAVE_STATIC
id|sd
"$"
l_int|16
comma
id|PT_R16
c_func
(paren
id|sp
)paren
id|sd
"$"
l_int|17
comma
id|PT_R17
c_func
(paren
id|sp
)paren
id|sd
"$"
l_int|18
comma
id|PT_R18
c_func
(paren
id|sp
)paren
id|sd
"$"
l_int|19
comma
id|PT_R19
c_func
(paren
id|sp
)paren
id|sd
"$"
l_int|20
comma
id|PT_R20
c_func
(paren
id|sp
)paren
id|sd
"$"
l_int|21
comma
id|PT_R21
c_func
(paren
id|sp
)paren
id|sd
"$"
l_int|22
comma
id|PT_R22
c_func
(paren
id|sp
)paren
id|sd
"$"
l_int|23
comma
id|PT_R23
c_func
(paren
id|sp
)paren
id|sd
"$"
l_int|30
comma
id|PT_R30
c_func
(paren
id|sp
)paren
dot
id|endm
macro_line|#ifdef CONFIG_SMP
dot
id|macro
id|get_saved_sp
multiline_comment|/* SMP variation */
id|dmfc0
id|k1
comma
id|CP0_CONTEXT
id|dsra
id|k1
comma
l_int|23
id|lui
id|k0
comma
op_mod
id|hi
c_func
(paren
id|pgd_current
)paren
id|daddiu
id|k0
comma
op_mod
id|lo
c_func
(paren
id|pgd_current
)paren
id|dsubu
id|k1
comma
id|k0
id|lui
id|k0
comma
op_mod
id|hi
c_func
(paren
id|kernelsp
)paren
id|daddu
id|k1
comma
id|k0
id|ld
id|k1
comma
op_mod
id|lo
c_func
(paren
id|kernelsp
)paren
(paren
id|k1
)paren
dot
id|endm
dot
id|macro
id|set_saved_sp
id|stackp
id|temp
id|temp2
id|lw
"&bslash;"
id|temp
comma
id|TI_CPU
c_func
(paren
id|gp
)paren
id|dsll
"&bslash;"
id|temp
comma
l_int|3
id|lui
"&bslash;"
id|temp2
comma
op_mod
id|hi
c_func
(paren
id|kernelsp
)paren
id|daddu
"&bslash;"
id|temp
comma
"&bslash;"
id|temp2
id|sd
"&bslash;"
id|stackp
comma
op_mod
id|lo
c_func
(paren
id|kernelsp
)paren
(paren
"&bslash;"
id|temp
)paren
dot
id|endm
macro_line|#else
dot
id|macro
id|get_saved_sp
multiline_comment|/* Uniprocessor variation */
id|lui
id|k1
comma
op_mod
id|hi
c_func
(paren
id|kernelsp
)paren
id|ld
id|k1
comma
op_mod
id|lo
c_func
(paren
id|kernelsp
)paren
(paren
id|k1
)paren
dot
id|endm
dot
id|macro
id|set_saved_sp
id|stackp
id|temp
id|temp2
id|sd
"&bslash;"
id|stackp
comma
id|kernelsp
dot
id|endm
macro_line|#endif
dot
id|macro
id|declare_saved_sp
dot
id|comm
id|kernelsp
comma
id|NR_CPUS
op_star
l_int|8
comma
l_int|8
dot
id|endm
dot
id|macro
id|SAVE_SOME
dot
id|set
id|push
dot
id|set
id|reorder
id|mfc0
id|k0
comma
id|CP0_STATUS
id|sll
id|k0
comma
l_int|3
multiline_comment|/* extract cu0 bit */
dot
id|set
id|noreorder
id|bltz
id|k0
comma
l_float|8f
id|move
id|k1
comma
id|sp
dot
id|set
id|reorder
multiline_comment|/* Called from user mode, new stack. */
id|get_saved_sp
l_int|8
suffix:colon
id|move
id|k0
comma
id|sp
id|dsubu
id|sp
comma
id|k1
comma
id|PT_SIZE
id|sd
id|k0
comma
id|PT_R29
c_func
(paren
id|sp
)paren
id|sd
"$"
l_int|3
comma
id|PT_R3
c_func
(paren
id|sp
)paren
id|sd
"$"
l_int|0
comma
id|PT_R0
c_func
(paren
id|sp
)paren
id|mfc0
id|v1
comma
id|CP0_STATUS
id|sd
"$"
l_int|2
comma
id|PT_R2
c_func
(paren
id|sp
)paren
id|sd
id|v1
comma
id|PT_STATUS
c_func
(paren
id|sp
)paren
id|sd
"$"
l_int|4
comma
id|PT_R4
c_func
(paren
id|sp
)paren
id|mfc0
id|v1
comma
id|CP0_CAUSE
id|sd
"$"
l_int|5
comma
id|PT_R5
c_func
(paren
id|sp
)paren
id|sd
id|v1
comma
id|PT_CAUSE
c_func
(paren
id|sp
)paren
id|sd
"$"
l_int|6
comma
id|PT_R6
c_func
(paren
id|sp
)paren
id|dmfc0
id|v1
comma
id|CP0_EPC
id|sd
"$"
l_int|7
comma
id|PT_R7
c_func
(paren
id|sp
)paren
id|sd
id|v1
comma
id|PT_EPC
c_func
(paren
id|sp
)paren
id|sd
"$"
l_int|25
comma
id|PT_R25
c_func
(paren
id|sp
)paren
id|sd
"$"
l_int|28
comma
id|PT_R28
c_func
(paren
id|sp
)paren
id|sd
"$"
l_int|31
comma
id|PT_R31
c_func
(paren
id|sp
)paren
id|ori
"$"
l_int|28
comma
id|sp
comma
l_int|0x3fff
id|xori
"$"
l_int|28
comma
l_int|0x3fff
dot
id|set
id|pop
dot
id|endm
dot
id|macro
id|SAVE_ALL
id|SAVE_SOME
id|SAVE_AT
id|SAVE_TEMP
id|SAVE_STATIC
dot
id|endm
dot
id|macro
id|RESTORE_AT
dot
id|set
id|push
dot
id|set
id|noat
id|ld
"$"
l_int|1
comma
id|PT_R1
c_func
(paren
id|sp
)paren
dot
id|set
id|pop
dot
id|endm
dot
id|macro
id|RESTORE_SP
id|ld
id|sp
comma
id|PT_R29
c_func
(paren
id|sp
)paren
dot
id|endm
dot
id|macro
id|RESTORE_TEMP
id|ld
"$"
l_int|24
comma
id|PT_LO
c_func
(paren
id|sp
)paren
id|ld
"$"
l_int|8
comma
id|PT_R8
c_func
(paren
id|sp
)paren
id|ld
"$"
l_int|9
comma
id|PT_R9
c_func
(paren
id|sp
)paren
id|mtlo
"$"
l_int|24
id|ld
"$"
l_int|24
comma
id|PT_HI
c_func
(paren
id|sp
)paren
id|ld
"$"
l_int|10
comma
id|PT_R10
c_func
(paren
id|sp
)paren
id|ld
"$"
l_int|11
comma
id|PT_R11
c_func
(paren
id|sp
)paren
id|mthi
"$"
l_int|24
id|ld
"$"
l_int|12
comma
id|PT_R12
c_func
(paren
id|sp
)paren
id|ld
"$"
l_int|13
comma
id|PT_R13
c_func
(paren
id|sp
)paren
id|ld
"$"
l_int|14
comma
id|PT_R14
c_func
(paren
id|sp
)paren
id|ld
"$"
l_int|15
comma
id|PT_R15
c_func
(paren
id|sp
)paren
id|ld
"$"
l_int|24
comma
id|PT_R24
c_func
(paren
id|sp
)paren
dot
id|endm
dot
id|macro
id|RESTORE_STATIC
id|ld
"$"
l_int|16
comma
id|PT_R16
c_func
(paren
id|sp
)paren
id|ld
"$"
l_int|17
comma
id|PT_R17
c_func
(paren
id|sp
)paren
id|ld
"$"
l_int|18
comma
id|PT_R18
c_func
(paren
id|sp
)paren
id|ld
"$"
l_int|19
comma
id|PT_R19
c_func
(paren
id|sp
)paren
id|ld
"$"
l_int|20
comma
id|PT_R20
c_func
(paren
id|sp
)paren
id|ld
"$"
l_int|21
comma
id|PT_R21
c_func
(paren
id|sp
)paren
id|ld
"$"
l_int|22
comma
id|PT_R22
c_func
(paren
id|sp
)paren
id|ld
"$"
l_int|23
comma
id|PT_R23
c_func
(paren
id|sp
)paren
id|ld
"$"
l_int|30
comma
id|PT_R30
c_func
(paren
id|sp
)paren
dot
id|endm
dot
id|macro
id|RESTORE_SOME
dot
id|set
id|push
dot
id|set
id|reorder
id|mfc0
id|t0
comma
id|CP0_STATUS
dot
id|set
id|pop
id|ori
id|t0
comma
l_int|0x1f
id|xori
id|t0
comma
l_int|0x1f
id|mtc0
id|t0
comma
id|CP0_STATUS
id|li
id|v1
comma
l_int|0xff00
op_logical_and
id|t0
comma
id|v1
id|ld
id|v0
comma
id|PT_STATUS
c_func
(paren
id|sp
)paren
id|nor
id|v1
comma
"$"
l_int|0
comma
id|v1
op_logical_and
id|v0
comma
id|v1
op_logical_or
id|v0
comma
id|t0
id|mtc0
id|v0
comma
id|CP0_STATUS
id|ld
id|v1
comma
id|PT_EPC
c_func
(paren
id|sp
)paren
id|dmtc0
id|v1
comma
id|CP0_EPC
id|ld
"$"
l_int|31
comma
id|PT_R31
c_func
(paren
id|sp
)paren
id|ld
"$"
l_int|28
comma
id|PT_R28
c_func
(paren
id|sp
)paren
id|ld
"$"
l_int|25
comma
id|PT_R25
c_func
(paren
id|sp
)paren
id|ld
"$"
l_int|7
comma
id|PT_R7
c_func
(paren
id|sp
)paren
id|ld
"$"
l_int|6
comma
id|PT_R6
c_func
(paren
id|sp
)paren
id|ld
"$"
l_int|5
comma
id|PT_R5
c_func
(paren
id|sp
)paren
id|ld
"$"
l_int|4
comma
id|PT_R4
c_func
(paren
id|sp
)paren
id|ld
"$"
l_int|3
comma
id|PT_R3
c_func
(paren
id|sp
)paren
id|ld
"$"
l_int|2
comma
id|PT_R2
c_func
(paren
id|sp
)paren
dot
id|endm
dot
id|macro
id|RESTORE_ALL
id|RESTORE_SOME
id|RESTORE_AT
id|RESTORE_TEMP
id|RESTORE_STATIC
id|RESTORE_SP
dot
id|endm
multiline_comment|/*&n; * Move to kernel mode and disable interrupts.&n; * Set cp0 enable bit as sign that we&squot;re running on the kernel stack&n; */
dot
id|macro
id|CLI
id|mfc0
id|t0
comma
id|CP0_STATUS
id|li
id|t1
comma
id|ST0_CU0
op_or
l_int|0x1f
op_logical_or
id|t0
comma
id|t1
id|xori
id|t0
comma
l_int|0x1f
id|mtc0
id|t0
comma
id|CP0_STATUS
dot
id|endm
multiline_comment|/*&n; * Move to kernel mode and enable interrupts.&n; * Set cp0 enable bit as sign that we&squot;re running on the kernel stack&n; */
dot
id|macro
id|STI
id|mfc0
id|t0
comma
id|CP0_STATUS
id|li
id|t1
comma
id|ST0_CU0
op_or
l_int|0x1f
op_logical_or
id|t0
comma
id|t1
id|xori
id|t0
comma
l_int|0x1e
id|mtc0
id|t0
comma
id|CP0_STATUS
dot
id|endm
multiline_comment|/*&n; * Just move to kernel mode and leave interrupts as they are.&n; * Set cp0 enable bit as sign that we&squot;re running on the kernel stack&n; */
dot
id|macro
id|KMODE
id|mfc0
id|t0
comma
id|CP0_STATUS
id|li
id|t1
comma
id|ST0_CU0
op_or
l_int|0x1e
op_logical_or
id|t0
comma
id|t1
id|xori
id|t0
comma
l_int|0x1e
id|mtc0
id|t0
comma
id|CP0_STATUS
dot
id|endm
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif /* __ASM_STACKFRAME_H */
eof
