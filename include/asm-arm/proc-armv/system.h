multiline_comment|/*&n; *  linux/include/asm-arm/proc-armv/system.h&n; *&n; *  Copyright (C) 1996 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#ifndef __ASM_PROC_SYSTEM_H
DECL|macro|__ASM_PROC_SYSTEM_H
mdefine_line|#define __ASM_PROC_SYSTEM_H
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|set_cr
mdefine_line|#define set_cr(x)&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&bslash;&n;&t;&quot;mcr&t;p15, 0, %0, c1, c0&t;@ set CR&quot;&t;&bslash;&n;&t;: : &quot;r&quot; (x))
r_extern
r_int
r_int
id|cr_no_alignment
suffix:semicolon
multiline_comment|/* defined in entry-armv.S */
r_extern
r_int
r_int
id|cr_alignment
suffix:semicolon
multiline_comment|/* defined in entry-armv.S */
multiline_comment|/*&n; * A couple of speedups for the ARM&n; */
multiline_comment|/*&n; * Save the current interrupt enable state &amp; disable IRQs&n; */
DECL|macro|__save_flags_cli
mdefine_line|#define __save_flags_cli(x)&t;&t;&t;&t;&t;&bslash;&n;&t;({&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;unsigned long temp;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;mrs&t;%0, cpsr&t;&t;@ save_flags_cli&bslash;n&quot;&t;&bslash;&n;&quot;&t;orr&t;%1, %0, #128&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&quot;&t;msr&t;cpsr_c, %1&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;=r&quot; (x), &quot;=r&quot; (temp)&t;&t;&t;&t;&t;&bslash;&n;&t;:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;memory&quot;);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;})
multiline_comment|/*&n; * Enable IRQs&n; */
DECL|macro|__sti
mdefine_line|#define __sti()&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;({&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;unsigned long temp;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;mrs&t;%0, cpsr&t;&t;@ sti&bslash;n&quot;&t;&t;&bslash;&n;&quot;&t;bic&t;%0, %0, #128&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&quot;&t;msr&t;cpsr_c, %0&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;=r&quot; (temp)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;memory&quot;);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;})
multiline_comment|/*&n; * Disable IRQs&n; */
DECL|macro|__cli
mdefine_line|#define __cli()&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;({&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;unsigned long temp;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;mrs&t;%0, cpsr&t;&t;@ cli&bslash;n&quot;&t;&t;&bslash;&n;&quot;&t;orr&t;%0, %0, #128&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&quot;&t;msr&t;cpsr_c, %0&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;=r&quot; (temp)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;memory&quot;);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;})
multiline_comment|/*&n; * Enable FIQs&n; */
DECL|macro|__stf
mdefine_line|#define __stf()&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;({&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;unsigned long temp;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;mrs&t;%0, cpsr&t;&t;@ stf&bslash;n&quot;&t;&t;&bslash;&n;&quot;&t;bic&t;%0, %0, #64&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&quot;&t;msr&t;cpsr_c, %0&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;=r&quot; (temp)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;memory&quot;);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;})
multiline_comment|/*&n; * Disable FIQs&n; */
DECL|macro|__clf
mdefine_line|#define __clf()&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;({&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;unsigned long temp;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;mrs&t;%0, cpsr&t;&t;@ clf&bslash;n&quot;&t;&t;&bslash;&n;&quot;&t;orr&t;%0, %0, #64&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&quot;&t;msr&t;cpsr_c, %0&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;=r&quot; (temp)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;memory&quot;);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;})
multiline_comment|/*&n; * save current IRQ &amp; FIQ state&n; */
DECL|macro|__save_flags
mdefine_line|#define __save_flags(x)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;mrs&t;%0, cpsr&t;&t;@ save_flags&bslash;n&quot;&t;&t;&bslash;&n;&t;  : &quot;=r&quot; (x)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;  :&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;  : &quot;memory&quot;)
multiline_comment|/*&n; * restore saved IRQ &amp; FIQ state&n; */
DECL|macro|__restore_flags
mdefine_line|#define __restore_flags(x)&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;msr&t;cpsr_c, %0&t;&t;@ restore_flags&bslash;n&quot;&t;&bslash;&n;&t;:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;r&quot; (x)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;memory&quot;)
macro_line|#if defined(CONFIG_CPU_SA1100) || defined(CONFIG_CPU_SA110)
multiline_comment|/*&n; * On the StrongARM, &quot;swp&quot; is terminally broken since it bypasses the&n; * cache totally.  This means that the cache becomes inconsistent, and,&n; * since we use normal loads/stores as well, this is really bad.&n; * Typically, this causes oopsen in filp_close, but could have other,&n; * more disasterous effects.  There are two work-arounds:&n; *  1. Disable interrupts and emulate the atomic swap&n; *  2. Clean the cache, perform atomic swap, flush the cache&n; *&n; * We choose (1) since its the &quot;easiest&quot; to achieve here and is not&n; * dependent on the processor type.&n; */
DECL|macro|swp_is_buggy
mdefine_line|#define swp_is_buggy
macro_line|#endif
DECL|function|__xchg
r_extern
id|__inline__
r_int
r_int
id|__xchg
c_func
(paren
r_int
r_int
id|x
comma
r_volatile
r_void
op_star
id|ptr
comma
r_int
id|size
)paren
(brace
r_extern
r_void
id|__bad_xchg
c_func
(paren
r_volatile
r_void
op_star
comma
r_int
)paren
suffix:semicolon
r_int
r_int
id|ret
suffix:semicolon
macro_line|#ifdef swp_is_buggy
r_int
r_int
id|flags
suffix:semicolon
macro_line|#endif
r_switch
c_cond
(paren
id|size
)paren
(brace
macro_line|#ifdef swp_is_buggy
r_case
l_int|1
suffix:colon
id|__save_flags_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
id|ret
op_assign
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
id|ptr
suffix:semicolon
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
id|ptr
op_assign
id|x
suffix:semicolon
id|__restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|__save_flags_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
id|ret
op_assign
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|ptr
suffix:semicolon
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|ptr
op_assign
id|x
suffix:semicolon
id|__restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#else
r_case
l_int|1
suffix:colon
id|__asm__
id|__volatile__
(paren
l_string|&quot;swpb %0, %1, [%2]&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ret
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|x
)paren
comma
l_string|&quot;r&quot;
(paren
id|ptr
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|__asm__
id|__volatile__
(paren
l_string|&quot;swp %0, %1, [%2]&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ret
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|x
)paren
comma
l_string|&quot;r&quot;
(paren
id|ptr
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
r_default
suffix:colon
id|__bad_xchg
c_func
(paren
id|ptr
comma
id|size
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
macro_line|#endif
eof
