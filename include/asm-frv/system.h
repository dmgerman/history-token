multiline_comment|/* system.h: FR-V CPU control definitions&n; *&n; * Copyright (C) 2003 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _ASM_SYSTEM_H
DECL|macro|_ASM_SYSTEM_H
mdefine_line|#define _ASM_SYSTEM_H
macro_line|#include &lt;linux/config.h&gt; /* get configuration macros */
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
r_struct
id|thread_struct
suffix:semicolon
DECL|macro|prepare_to_switch
mdefine_line|#define prepare_to_switch()    do { } while(0)
multiline_comment|/*&n; * switch_to(prev, next) should switch from task `prev&squot; to `next&squot;&n; * `prev&squot; will never be the same as `next&squot;.&n; * The `mb&squot; is to tell GCC not to cache `current&squot; across this call.&n; */
r_extern
id|asmlinkage
r_struct
id|task_struct
op_star
id|__switch_to
c_func
(paren
r_struct
id|thread_struct
op_star
id|prev_thread
comma
r_struct
id|thread_struct
op_star
id|next_thread
comma
r_struct
id|task_struct
op_star
id|prev
)paren
suffix:semicolon
DECL|macro|switch_to
mdefine_line|#define switch_to(prev, next, last)&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(prev)-&gt;thread.sched_lr =&t;&t;&t;&t;&t;&bslash;&n;&t;&t;(unsigned long) __builtin_return_address(0);&t;&t;&bslash;&n;&t;(last) = __switch_to(&amp;(prev)-&gt;thread, &amp;(next)-&gt;thread, (prev));&t;&bslash;&n;&t;mb();&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while(0)
multiline_comment|/*&n; * interrupt flag manipulation&n; */
DECL|macro|local_irq_disable
mdefine_line|#define local_irq_disable()&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long psr;&t;&t;&t;&t;&bslash;&n;&t;asm volatile(&quot;&t;movsg&t;psr,%0&t;&t;&bslash;n&quot;&t;&bslash;&n;&t;&t;     &quot;&t;andi&t;%0,%2,%0&t;&bslash;n&quot;&t;&bslash;&n;&t;&t;     &quot;&t;ori&t;%0,%1,%0&t;&bslash;n&quot;&t;&bslash;&n;&t;&t;     &quot;&t;movgs&t;%0,psr&t;&t;&bslash;n&quot;&t;&bslash;&n;&t;&t;     : &quot;=r&quot;(psr)&t;&t;&t;&bslash;&n;&t;&t;     : &quot;i&quot; (PSR_PIL_14), &quot;i&quot; (~PSR_PIL)&t;&bslash;&n;&t;&t;     : &quot;memory&quot;);&t;&t;&t;&bslash;&n;} while(0)
DECL|macro|local_irq_enable
mdefine_line|#define local_irq_enable()&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long psr;&t;&t;&t;&t;&bslash;&n;&t;asm volatile(&quot;&t;movsg&t;psr,%0&t;&t;&bslash;n&quot;&t;&bslash;&n;&t;&t;     &quot;&t;andi&t;%0,%1,%0&t;&bslash;n&quot;&t;&bslash;&n;&t;&t;     &quot;&t;movgs&t;%0,psr&t;&t;&bslash;n&quot;&t;&bslash;&n;&t;&t;     : &quot;=r&quot;(psr)&t;&t;&t;&bslash;&n;&t;&t;     : &quot;i&quot; (~PSR_PIL)&t;&t;&t;&bslash;&n;&t;&t;     : &quot;memory&quot;);&t;&t;&t;&bslash;&n;} while(0)
DECL|macro|local_save_flags
mdefine_line|#define local_save_flags(flags)&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;typecheck(unsigned long, flags);&t;&bslash;&n;&t;asm(&quot;movsg psr,%0&quot;&t;&t;&t;&bslash;&n;&t;    : &quot;=r&quot;(flags)&t;&t;&t;&bslash;&n;&t;    :&t;&t;&t;&t;&t;&bslash;&n;&t;    : &quot;memory&quot;);&t;&t;&t;&bslash;&n;} while(0)
DECL|macro|local_irq_save
mdefine_line|#define&t;local_irq_save(flags)&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long npsr;&t;&t;&t;&t;&bslash;&n;&t;typecheck(unsigned long, flags);&t;&t;&bslash;&n;&t;asm volatile(&quot;&t;movsg&t;psr,%0&t;&t;&bslash;n&quot;&t;&bslash;&n;&t;&t;     &quot;&t;andi&t;%0,%3,%1&t;&bslash;n&quot;&t;&bslash;&n;&t;&t;     &quot;&t;ori&t;%1,%2,%1&t;&bslash;n&quot;&t;&bslash;&n;&t;&t;     &quot;&t;movgs&t;%1,psr&t;&t;&bslash;n&quot;&t;&bslash;&n;&t;&t;     : &quot;=r&quot;(flags), &quot;=r&quot;(npsr)&t;&t;&bslash;&n;&t;&t;     : &quot;i&quot; (PSR_PIL_14), &quot;i&quot; (~PSR_PIL)&t;&bslash;&n;&t;&t;     : &quot;memory&quot;);&t;&t;&t;&bslash;&n;} while(0)
DECL|macro|local_irq_restore
mdefine_line|#define&t;local_irq_restore(flags)&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;typecheck(unsigned long, flags);&t;&t;&bslash;&n;&t;asm volatile(&quot;&t;movgs&t;%0,psr&t;&t;&bslash;n&quot;&t;&bslash;&n;&t;&t;     :&t;&t;&t;&t;&t;&bslash;&n;&t;&t;     : &quot;r&quot; (flags)&t;&t;&t;&bslash;&n;&t;&t;     : &quot;memory&quot;);&t;&t;&t;&bslash;&n;} while(0)
DECL|macro|irqs_disabled
mdefine_line|#define irqs_disabled() &bslash;&n;&t;((__get_PSR() &amp; PSR_PIL) &gt;= PSR_PIL_14)
multiline_comment|/*&n; * Force strict CPU ordering.&n; */
DECL|macro|nop
mdefine_line|#define nop()&t;&t;&t;asm volatile (&quot;nop&quot;::)
DECL|macro|mb
mdefine_line|#define mb()&t;&t;&t;asm volatile (&quot;membar&quot; : : :&quot;memory&quot;)
DECL|macro|rmb
mdefine_line|#define rmb()&t;&t;&t;asm volatile (&quot;membar&quot; : : :&quot;memory&quot;)
DECL|macro|wmb
mdefine_line|#define wmb()&t;&t;&t;asm volatile (&quot;membar&quot; : : :&quot;memory&quot;)
DECL|macro|set_mb
mdefine_line|#define set_mb(var, value)&t;do { var = value; mb(); } while (0)
DECL|macro|set_wmb
mdefine_line|#define set_wmb(var, value)&t;do { var = value; wmb(); } while (0)
DECL|macro|smp_mb
mdefine_line|#define smp_mb()&t;&t;mb()
DECL|macro|smp_rmb
mdefine_line|#define smp_rmb()&t;&t;rmb()
DECL|macro|smp_wmb
mdefine_line|#define smp_wmb()&t;&t;wmb()
DECL|macro|read_barrier_depends
mdefine_line|#define read_barrier_depends()&t;&t;do {} while(0)
DECL|macro|smp_read_barrier_depends
mdefine_line|#define smp_read_barrier_depends()&t;read_barrier_depends()
DECL|macro|HARD_RESET_NOW
mdefine_line|#define HARD_RESET_NOW()&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;cli();&t;&t;&t;&t;&t;&bslash;&n;} while(1)
r_extern
r_void
id|die_if_kernel
c_func
(paren
r_const
r_char
op_star
comma
dot
dot
dot
)paren
id|__attribute__
c_func
(paren
(paren
id|format
c_func
(paren
id|printf
comma
l_int|1
comma
l_int|2
)paren
)paren
)paren
suffix:semicolon
r_extern
r_void
id|free_initmem
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|arch_align_stack
mdefine_line|#define arch_align_stack(x) (x)
macro_line|#endif /* _ASM_SYSTEM_H */
eof
