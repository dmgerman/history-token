multiline_comment|/*&n; * include/asm-v850/entry.h -- Definitions used by low-level trap handlers&n; *&n; *  Copyright (C) 2001,02,03  NEC Electronics Corporation&n; *  Copyright (C) 2001,02,03  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#ifndef __V850_ENTRY_H__
DECL|macro|__V850_ENTRY_H__
mdefine_line|#define __V850_ENTRY_H__
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
multiline_comment|/* These are special variables using by the kernel trap/interrupt code&n;   to save registers in, at a time when there are no spare registers we&n;   can use to do so, and we can&squot;t depend on the value of the stack&n;   pointer.  This means that they must be within a signed 16-bit&n;   displacement of 0x00000000.  */
DECL|macro|KERNEL_VAR_SPACE_ADDR
mdefine_line|#define KERNEL_VAR_SPACE_ADDR&t;R0_RAM_ADDR
macro_line|#ifdef __ASSEMBLY__
DECL|macro|KERNEL_VAR
mdefine_line|#define KERNEL_VAR(addr)&t;addr[r0]
macro_line|#else
DECL|macro|KERNEL_VAR
mdefine_line|#define KERNEL_VAR(addr)&t;(*(volatile unsigned long *)(addr))
macro_line|#endif
multiline_comment|/* Kernel stack pointer, 4 bytes.  */
DECL|macro|KSP_ADDR
mdefine_line|#define KSP_ADDR&t;&t;(KERNEL_VAR_SPACE_ADDR +  0)
DECL|macro|KSP
mdefine_line|#define KSP&t;&t;&t;KERNEL_VAR (KSP_ADDR)
multiline_comment|/* 1 if in kernel-mode, 0 if in user mode, 1 byte.  */
DECL|macro|KM_ADDR
mdefine_line|#define KM_ADDR &t;&t;(KERNEL_VAR_SPACE_ADDR +  4)
DECL|macro|KM
mdefine_line|#define KM&t;&t;&t;KERNEL_VAR (KM_ADDR)
multiline_comment|/* Temporary storage for interrupt handlers, 4 bytes.  */
DECL|macro|INT_SCRATCH_ADDR
mdefine_line|#define INT_SCRATCH_ADDR&t;(KERNEL_VAR_SPACE_ADDR +  8)
DECL|macro|INT_SCRATCH
mdefine_line|#define INT_SCRATCH&t;&t;KERNEL_VAR (INT_SCRATCH_ADDR)
multiline_comment|/* Where the stack-pointer is saved when jumping to various sorts of&n;   interrupt handlers.  ENTRY_SP is used by everything except NMIs,&n;   which have their own location.  Higher-priority NMIs can clobber the&n;   value written by a lower priority NMI, since they can&squot;t be disabled,&n;   but that&squot;s OK, because only NMI0 (the lowest-priority one) is allowed&n;   to return.  */
DECL|macro|ENTRY_SP_ADDR
mdefine_line|#define ENTRY_SP_ADDR&t;&t;(KERNEL_VAR_SPACE_ADDR + 12)
DECL|macro|ENTRY_SP
mdefine_line|#define ENTRY_SP&t;&t;KERNEL_VAR (ENTRY_SP_ADDR)
DECL|macro|NMI_ENTRY_SP_ADDR
mdefine_line|#define NMI_ENTRY_SP_ADDR&t;(KERNEL_VAR_SPACE_ADDR + 16)
DECL|macro|NMI_ENTRY_SP
mdefine_line|#define NMI_ENTRY_SP&t;&t;KERNEL_VAR (NMI_ENTRY_SP_ADDR)
macro_line|#ifdef CONFIG_RESET_GUARD
multiline_comment|/* Used to detect unexpected resets (since the v850 has no MMU, any call&n;   through a null pointer will jump to the reset vector).  We detect&n;   such resets by checking for a magic value, RESET_GUARD_ACTIVE, in&n;   this location.  Properly resetting the machine stores zero there, so&n;   it shouldn&squot;t trigger the guard; the power-on value is uncertain, but&n;   it&squot;s unlikely to be RESET_GUARD_ACTIVE.  */
DECL|macro|RESET_GUARD_ADDR
mdefine_line|#define RESET_GUARD_ADDR&t;(KERNEL_VAR_SPACE_ADDR + 28)
DECL|macro|RESET_GUARD
mdefine_line|#define RESET_GUARD&t;&t;KERNEL_VAR (RESET_GUARD_ADDR)
DECL|macro|RESET_GUARD_ACTIVE
mdefine_line|#define RESET_GUARD_ACTIVE&t;0xFAB4BEEF
macro_line|#endif /* CONFIG_RESET_GUARD */
macro_line|#ifdef CONFIG_V850E_HIGHRES_TIMER
DECL|macro|HIGHRES_TIMER_SLOW_TICKS_ADDR
mdefine_line|#define HIGHRES_TIMER_SLOW_TICKS_ADDR (KERNEL_VAR_SPACE_ADDR + 32)
DECL|macro|HIGHRES_TIMER_SLOW_TICKS
mdefine_line|#define HIGHRES_TIMER_SLOW_TICKS     KERNEL_VAR (HIGHRES_TIMER_SLOW_TICKS_ADDR)
macro_line|#endif /* CONFIG_V850E_HIGHRES_TIMER */
macro_line|#ifndef __ASSEMBLY__
macro_line|#ifdef CONFIG_RESET_GUARD
multiline_comment|/* Turn off reset guard, so that resetting the machine works normally.&n;   This should be called in the various machine_halt, etc., functions.  */
DECL|function|disable_reset_guard
r_static
r_inline
r_void
id|disable_reset_guard
(paren
r_void
)paren
(brace
id|RESET_GUARD
op_assign
l_int|0
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_RESET_GUARD */
macro_line|#endif /* !__ASSEMBLY__ */
multiline_comment|/* A `state save frame&squot; is a struct pt_regs preceded by some extra space&n;   suitable for a function call stack frame.  */
multiline_comment|/* Amount of room on the stack reserved for arguments and to satisfy the&n;   C calling conventions, in addition to the space used by the struct&n;   pt_regs that actually holds saved values.  */
DECL|macro|STATE_SAVE_ARG_SPACE
mdefine_line|#define STATE_SAVE_ARG_SPACE&t;(6*4) /* Up to six arguments.  */
macro_line|#ifdef __ASSEMBLY__
multiline_comment|/* The size of a state save frame.  */
DECL|macro|STATE_SAVE_SIZE
mdefine_line|#define STATE_SAVE_SIZE&t;&t;(PT_SIZE + STATE_SAVE_ARG_SPACE)
macro_line|#else /* !__ASSEMBLY__ */
multiline_comment|/* The size of a state save frame.  */
DECL|macro|STATE_SAVE_SIZE
mdefine_line|#define STATE_SAVE_SIZE&t;       (sizeof (struct pt_regs) + STATE_SAVE_ARG_SPACE)
macro_line|#endif /* __ASSEMBLY__ */
multiline_comment|/* Offset of the struct pt_regs in a state save frame.  */
DECL|macro|STATE_SAVE_PT_OFFSET
mdefine_line|#define STATE_SAVE_PT_OFFSET&t;STATE_SAVE_ARG_SPACE
macro_line|#endif /* __V850_ENTRY_H__ */
eof
