multiline_comment|/*&n; * arch/v850/kernel/mach.h -- Machine-dependent functions used by v850 port&n; *&n; *  Copyright (C) 2001,02,03  NEC Electronics Corporation&n; *  Copyright (C) 2001,02,03  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#ifndef __V850_MACH_H__
DECL|macro|__V850_MACH_H__
mdefine_line|#define __V850_MACH_H__
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/entry.h&gt;
macro_line|#include &lt;asm/clinkage.h&gt;
r_void
id|mach_setup
(paren
r_char
op_star
op_star
id|cmdline
)paren
suffix:semicolon
r_void
id|mach_gettimeofday
(paren
r_struct
id|timespec
op_star
id|tv
)paren
suffix:semicolon
r_void
id|mach_sched_init
(paren
r_struct
id|irqaction
op_star
id|timer_action
)paren
suffix:semicolon
r_void
id|mach_get_physical_ram
(paren
r_int
r_int
op_star
id|ram_start
comma
r_int
r_int
op_star
id|ram_len
)paren
suffix:semicolon
r_void
id|mach_init_irqs
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* If defined, is called very early in the kernel initialization.  The&n;   stack pointer is valid, but very little has been initialized (e.g.,&n;   bss is not zeroed yet) when this is called, so care must taken.  */
r_void
id|mach_early_init
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* If defined, called after the bootmem allocator has been initialized,&n;   to allow the platform-dependent code to reserve any areas of RAM that&n;   the kernel shouldn&squot;t touch.  */
r_void
id|mach_reserve_bootmem
(paren
r_void
)paren
id|__attribute__
(paren
(paren
id|__weak__
)paren
)paren
suffix:semicolon
multiline_comment|/* Called with each timer tick, if non-zero.  */
r_extern
r_void
(paren
op_star
id|mach_tick
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* The following establishes aliases for various mach_ functions to the&n;   name by which the rest of the kernel calls them.  These statements&n;   should only have an effect in the file that defines the actual functions. */
DECL|macro|MACH_ALIAS
mdefine_line|#define MACH_ALIAS(to, from)&t;&t;&t;&t;&t;&t;      &bslash;&n;   asm (&quot;.global &quot; macrology_stringify (C_SYMBOL_NAME (to)) &quot;;&quot;&t;&t;      &bslash;&n;&t;macrology_stringify (C_SYMBOL_NAME (to))&t;&t;&t;      &bslash;&n;&t;&quot; = &quot; macrology_stringify (C_SYMBOL_NAME (from)))
multiline_comment|/* e.g.: MACH_ALIAS (kernel_name,&t;arch_spec_name);  */
macro_line|#endif /* __V850_MACH_H__ */
eof
