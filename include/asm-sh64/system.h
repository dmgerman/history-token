macro_line|#ifndef __ASM_SH64_SYSTEM_H
DECL|macro|__ASM_SH64_SYSTEM_H
mdefine_line|#define __ASM_SH64_SYSTEM_H
multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * include/asm-sh64/system.h&n; *&n; * Copyright (C) 2000, 2001  Paolo Alberelli&n; * Copyright (C) 2003  Paul Mundt&n; * Copyright (C) 2004  Richard Curnow&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/registers.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
multiline_comment|/*&n; *&t;switch_to() should switch tasks to task nr n, first&n; */
r_typedef
r_struct
(brace
DECL|member|seg
r_int
r_int
id|seg
suffix:semicolon
DECL|typedef|mm_segment_t
)brace
id|mm_segment_t
suffix:semicolon
r_extern
r_struct
id|task_struct
op_star
id|sh64_switch_to
c_func
(paren
r_struct
id|task_struct
op_star
id|prev
comma
r_struct
id|thread_struct
op_star
id|prev_thread
comma
r_struct
id|task_struct
op_star
id|next
comma
r_struct
id|thread_struct
op_star
id|next_thread
)paren
suffix:semicolon
DECL|macro|switch_to
mdefine_line|#define switch_to(prev,next,last) &bslash;&n;&t;do {&bslash;&n;&t;&t;if (last_task_used_math != next) {&bslash;&n;&t;&t;&t;struct pt_regs *regs = next-&gt;thread.uregs;&bslash;&n;&t;&t;&t;if (regs) regs-&gt;sr |= SR_FD;&bslash;&n;&t;&t;}&bslash;&n;&t;&t;last = sh64_switch_to(prev, &amp;prev-&gt;thread, next, &amp;next-&gt;thread);&bslash;&n;&t;} while(0)
DECL|macro|nop
mdefine_line|#define nop() __asm__ __volatile__ (&quot;nop&quot;)
DECL|macro|xchg
mdefine_line|#define xchg(ptr,x) ((__typeof__(*(ptr)))__xchg((unsigned long)(x),(ptr),sizeof(*(ptr))))
DECL|macro|tas
mdefine_line|#define tas(ptr) (xchg((ptr), 1))
r_extern
r_void
id|__xchg_called_with_bad_pointer
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|mb
mdefine_line|#define mb()&t;__asm__ __volatile__ (&quot;synco&quot;: : :&quot;memory&quot;)
DECL|macro|rmb
mdefine_line|#define rmb()&t;mb()
DECL|macro|wmb
mdefine_line|#define wmb()&t;__asm__ __volatile__ (&quot;synco&quot;: : :&quot;memory&quot;)
DECL|macro|read_barrier_depends
mdefine_line|#define read_barrier_depends()&t;do { } while (0)
macro_line|#ifdef CONFIG_SMP
DECL|macro|smp_mb
mdefine_line|#define smp_mb()&t;mb()
DECL|macro|smp_rmb
mdefine_line|#define smp_rmb()&t;rmb()
DECL|macro|smp_wmb
mdefine_line|#define smp_wmb()&t;wmb()
DECL|macro|smp_read_barrier_depends
mdefine_line|#define smp_read_barrier_depends()&t;read_barrier_depends()
macro_line|#else
DECL|macro|smp_mb
mdefine_line|#define smp_mb()&t;barrier()
DECL|macro|smp_rmb
mdefine_line|#define smp_rmb()&t;barrier()
DECL|macro|smp_wmb
mdefine_line|#define smp_wmb()&t;barrier()
DECL|macro|smp_read_barrier_depends
mdefine_line|#define smp_read_barrier_depends()&t;do { } while (0)
macro_line|#endif /* CONFIG_SMP */
DECL|macro|set_rmb
mdefine_line|#define set_rmb(var, value) do { xchg(&amp;var, value); } while (0)
DECL|macro|set_mb
mdefine_line|#define set_mb(var, value) set_rmb(var, value)
DECL|macro|set_wmb
mdefine_line|#define set_wmb(var, value) do { var = value; wmb(); } while (0)
multiline_comment|/* Interrupt Control */
macro_line|#ifndef HARD_CLI
DECL|macro|SR_MASK_L
mdefine_line|#define SR_MASK_L 0x000000f0L
DECL|macro|SR_MASK_LL
mdefine_line|#define SR_MASK_LL 0x00000000000000f0LL
macro_line|#else
DECL|macro|SR_MASK_L
mdefine_line|#define SR_MASK_L 0x10000000L
DECL|macro|SR_MASK_LL
mdefine_line|#define SR_MASK_LL 0x0000000010000000LL
macro_line|#endif
DECL|function|local_irq_enable
r_static
id|__inline__
r_void
id|local_irq_enable
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* cli/sti based on SR.BL */
r_int
r_int
r_int
id|__dummy0
comma
id|__dummy1
op_assign
op_complement
id|SR_MASK_LL
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;getcon&t;&quot;
id|__SR
l_string|&quot;, %0&bslash;n&bslash;t&quot;
l_string|&quot;and&t;%0, %1, %0&bslash;n&bslash;t&quot;
l_string|&quot;putcon&t;%0, &quot;
id|__SR
l_string|&quot;&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|__dummy0
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|__dummy1
)paren
)paren
suffix:semicolon
)brace
DECL|function|local_irq_disable
r_static
id|__inline__
r_void
id|local_irq_disable
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* cli/sti based on SR.BL */
r_int
r_int
r_int
id|__dummy0
comma
id|__dummy1
op_assign
id|SR_MASK_LL
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;getcon&t;&quot;
id|__SR
l_string|&quot;, %0&bslash;n&bslash;t&quot;
l_string|&quot;or&t;%0, %1, %0&bslash;n&bslash;t&quot;
l_string|&quot;putcon&t;%0, &quot;
id|__SR
l_string|&quot;&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|__dummy0
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|__dummy1
)paren
)paren
suffix:semicolon
)brace
DECL|macro|local_save_flags
mdefine_line|#define local_save_flags(x) &t;&t;&t;&t;&t;&t;&bslash;&n;(__extension__ ({&t;unsigned long long __dummy=SR_MASK_LL;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;getcon&t;&quot; __SR &quot;, %0&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;and&t;%0, %1, %0&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=&amp;r&quot; (x)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;r&quot; (__dummy));}))
DECL|macro|local_irq_save
mdefine_line|#define local_irq_save(x)&t;&t;&t;&t;&t;&t;&bslash;&n;(__extension__ ({&t;unsigned long long __d2=SR_MASK_LL, __d1;&t;&bslash;&n;&t;__asm__ __volatile__(          &t;         &t;&t;&t;&bslash;&n;&t;&t;&quot;getcon&t;&quot; __SR &quot;, %1&bslash;n&bslash;t&quot; &t;&t;&t;&t;&bslash;&n;&t;&t;&quot;or&t;%1, r63, %0&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;or&t;%1, %2, %1&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;putcon&t;%1, &quot; __SR &quot;&bslash;n&bslash;t&quot;    &t;&t;&t;&t;&bslash;&n;&t;&t;&quot;and&t;%0, %2, %0&quot;    &t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=&amp;r&quot; (x), &quot;=&amp;r&quot; (__d1)&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;r&quot; (__d2));}));
DECL|macro|local_irq_restore
mdefine_line|#define local_irq_restore(x) do { &t;&t;&t;&t;&t;&bslash;&n;&t;if ( ((x) &amp; SR_MASK_L) == 0 )&t;&t;/* dropping to 0 ? */&t;&bslash;&n;&t;&t;local_irq_enable();&t;&t;/* yes...re-enable */&t;&bslash;&n;} while (0)
DECL|macro|irqs_disabled
mdefine_line|#define irqs_disabled()&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long flags;&t;&t;&bslash;&n;&t;local_save_flags(flags);&t;&bslash;&n;&t;(flags != 0);&t;&t;&t;&bslash;&n;})
DECL|function|xchg_u32
r_extern
id|__inline__
r_int
r_int
id|xchg_u32
c_func
(paren
r_volatile
r_int
op_star
id|m
comma
r_int
r_int
id|val
)paren
(brace
r_int
r_int
id|flags
comma
id|retval
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|retval
op_assign
op_star
id|m
suffix:semicolon
op_star
id|m
op_assign
id|val
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|xchg_u8
r_extern
id|__inline__
r_int
r_int
id|xchg_u8
c_func
(paren
r_volatile
r_int
r_char
op_star
id|m
comma
r_int
r_int
id|val
)paren
(brace
r_int
r_int
id|flags
comma
id|retval
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|retval
op_assign
op_star
id|m
suffix:semicolon
op_star
id|m
op_assign
id|val
op_amp
l_int|0xff
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|__xchg
r_static
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
r_switch
c_cond
(paren
id|size
)paren
(brace
r_case
l_int|4
suffix:colon
r_return
id|xchg_u32
c_func
(paren
id|ptr
comma
id|x
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
r_return
id|xchg_u8
c_func
(paren
id|ptr
comma
id|x
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|__xchg_called_with_bad_pointer
c_func
(paren
)paren
suffix:semicolon
r_return
id|x
suffix:semicolon
)brace
multiline_comment|/* XXX&n; * disable hlt during certain critical i/o operations&n; */
DECL|macro|HAVE_DISABLE_HLT
mdefine_line|#define HAVE_DISABLE_HLT
r_void
id|disable_hlt
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|enable_hlt
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|smp_mb
mdefine_line|#define smp_mb()        barrier()
DECL|macro|smp_rmb
mdefine_line|#define smp_rmb()       barrier()
DECL|macro|smp_wmb
mdefine_line|#define smp_wmb()       barrier()
macro_line|#ifdef CONFIG_SH_ALPHANUMERIC
multiline_comment|/* This is only used for debugging. */
r_extern
r_void
id|print_seg
c_func
(paren
r_char
op_star
id|file
comma
r_int
id|line
)paren
suffix:semicolon
DECL|macro|PLS
mdefine_line|#define PLS() print_seg(__FILE__,__LINE__)
macro_line|#else&t;/* CONFIG_SH_ALPHANUMERIC */
DECL|macro|PLS
mdefine_line|#define PLS()
macro_line|#endif&t;/* CONFIG_SH_ALPHANUMERIC */
DECL|macro|PL
mdefine_line|#define PL() printk(&quot;@ &lt;%s,%s:%d&gt;&bslash;n&quot;,__FILE__,__FUNCTION__,__LINE__)
DECL|macro|arch_align_stack
mdefine_line|#define arch_align_stack(x) (x)
macro_line|#endif /* __ASM_SH64_SYSTEM_H */
eof
