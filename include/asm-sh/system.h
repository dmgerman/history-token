macro_line|#ifndef __ASM_SH_SYSTEM_H
DECL|macro|__ASM_SH_SYSTEM_H
mdefine_line|#define __ASM_SH_SYSTEM_H
multiline_comment|/*&n; * Copyright (C) 1999, 2000  Niibe Yutaka  &amp;  Kaz Kojima&n; * Copyright (C) 2002 Paul Mundt&n; */
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; *&t;switch_to() should switch tasks to task nr n, first&n; */
DECL|macro|switch_to
mdefine_line|#define switch_to(prev, next, last) do {&t;&t;&t;&t;&bslash;&n; task_t *__last;&t;&t;&t;&t;&t;&t;&t;&bslash;&n; register unsigned long *__ts1 __asm__ (&quot;r1&quot;) = &amp;prev-&gt;thread.sp;&t;&bslash;&n; register unsigned long *__ts2 __asm__ (&quot;r2&quot;) = &amp;prev-&gt;thread.pc;&t;&bslash;&n; register unsigned long *__ts4 __asm__ (&quot;r4&quot;) = (unsigned long *)prev;&t;&bslash;&n; register unsigned long *__ts5 __asm__ (&quot;r5&quot;) = (unsigned long *)next;&t;&bslash;&n; register unsigned long *__ts6 __asm__ (&quot;r6&quot;) = &amp;next-&gt;thread.sp;&t;&bslash;&n; register unsigned long __ts7 __asm__ (&quot;r7&quot;) = next-&gt;thread.pc;&t;&t;&bslash;&n; __asm__ __volatile__ (&quot;.balign 4&bslash;n&bslash;t&quot; &t;&t;&t;&t;&t;&bslash;&n;&t;&t;       &quot;stc.l&t;gbr, @-r15&bslash;n&bslash;t&quot; &t;&t;&t;&bslash;&n;&t;&t;       &quot;sts.l&t;pr, @-r15&bslash;n&bslash;t&quot; &t;&t;&t;&t;&bslash;&n;&t;&t;       &quot;mov.l&t;r8, @-r15&bslash;n&bslash;t&quot; &t;&t;&t;&t;&bslash;&n;&t;&t;       &quot;mov.l&t;r9, @-r15&bslash;n&bslash;t&quot; &t;&t;&t;&t;&bslash;&n;&t;&t;       &quot;mov.l&t;r10, @-r15&bslash;n&bslash;t&quot; &t;&t;&t;&bslash;&n;&t;&t;       &quot;mov.l&t;r11, @-r15&bslash;n&bslash;t&quot; &t;&t;&t;&bslash;&n;&t;&t;       &quot;mov.l&t;r12, @-r15&bslash;n&bslash;t&quot; &t;&t;&t;&bslash;&n;&t;&t;       &quot;mov.l&t;r13, @-r15&bslash;n&bslash;t&quot; &t;&t;&t;&bslash;&n;&t;&t;       &quot;mov.l&t;r14, @-r15&bslash;n&bslash;t&quot; &t;&t;&t;&bslash;&n;&t;&t;       &quot;mov.l&t;r15, @r1&t;! save SP&bslash;n&bslash;t&quot;&t;&t;&bslash;&n;&t;&t;       &quot;mov.l&t;@r6, r15&t;! change to new stack&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;       &quot;mova&t;1f, %0&bslash;n&bslash;t&quot; &t;&t;&t;&t;&bslash;&n;&t;&t;       &quot;mov.l&t;%0, @r2&t;&t;! save PC&bslash;n&bslash;t&quot; &t;&t;&bslash;&n;&t;&t;       &quot;mov.l&t;2f, %0&bslash;n&bslash;t&quot; &t;&t;&t;&t;&bslash;&n;&t;&t;       &quot;jmp&t;@%0&t;&t;! call __switch_to&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;       &quot; lds&t;r7, pr&t;&t;!  with return to new PC&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;       &quot;.balign&t;4&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;       &quot;2:&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;       &quot;.long&t;__switch_to&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;       &quot;1:&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;       &quot;mov.l&t;@r15+, r14&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;       &quot;mov.l&t;@r15+, r13&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;       &quot;mov.l&t;@r15+, r12&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;       &quot;mov.l&t;@r15+, r11&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;       &quot;mov.l&t;@r15+, r10&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;       &quot;mov.l&t;@r15+, r9&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;       &quot;mov.l&t;@r15+, r8&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;       &quot;lds.l&t;@r15+, pr&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;       &quot;ldc.l&t;@r15+, gbr&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;       : &quot;=z&quot; (__last)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;       : &quot;r&quot; (__ts1), &quot;r&quot; (__ts2), &quot;r&quot; (__ts4), &t;&bslash;&n;&t;&t;&t; &quot;r&quot; (__ts5), &quot;r&quot; (__ts6), &quot;r&quot; (__ts7) &t;&t;&bslash;&n;&t;&t;       : &quot;r3&quot;, &quot;t&quot;);&t;&t;&t;&t;&t;&bslash;&n;&t;last = __last;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|nop
mdefine_line|#define nop() __asm__ __volatile__ (&quot;nop&quot;)
DECL|macro|xchg
mdefine_line|#define xchg(ptr,x) ((__typeof__(*(ptr)))__xchg((unsigned long)(x),(ptr),sizeof(*(ptr))))
DECL|function|tas
r_static
id|__inline__
r_int
r_int
id|tas
c_func
(paren
r_volatile
r_int
op_star
id|m
)paren
(brace
multiline_comment|/* #define tas(ptr) (xchg((ptr),1)) */
r_int
r_int
id|retval
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;tas.b&t;@%1&bslash;n&bslash;t&quot;
l_string|&quot;movt&t;%0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|retval
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|m
)paren
suffix:colon
l_string|&quot;t&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
r_extern
r_void
id|__xchg_called_with_bad_pointer
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|mb
mdefine_line|#define mb()&t;__asm__ __volatile__ (&quot;&quot;: : :&quot;memory&quot;)
DECL|macro|rmb
mdefine_line|#define rmb()&t;mb()
DECL|macro|wmb
mdefine_line|#define wmb()&t;__asm__ __volatile__ (&quot;&quot;: : :&quot;memory&quot;)
DECL|macro|read_barrier_depends
mdefine_line|#define read_barrier_depends()&t;do { } while(0)
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
mdefine_line|#define smp_read_barrier_depends()&t;do { } while(0)
macro_line|#endif
DECL|macro|set_mb
mdefine_line|#define set_mb(var, value) do { xchg(&amp;var, value); } while (0)
DECL|macro|set_wmb
mdefine_line|#define set_wmb(var, value) do { var = value; wmb(); } while (0)
multiline_comment|/* Interrupt Control */
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
r_int
r_int
id|__dummy0
comma
id|__dummy1
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;stc&t;sr, %0&bslash;n&bslash;t&quot;
l_string|&quot;and&t;%1, %0&bslash;n&bslash;t&quot;
l_string|&quot;stc&t;r6_bank, %1&bslash;n&bslash;t&quot;
l_string|&quot;or&t;%1, %0&bslash;n&bslash;t&quot;
l_string|&quot;ldc&t;%0, sr&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|__dummy0
)paren
comma
l_string|&quot;=r&quot;
(paren
id|__dummy1
)paren
suffix:colon
l_string|&quot;1&quot;
(paren
op_complement
l_int|0x000000f0
)paren
suffix:colon
l_string|&quot;memory&quot;
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
r_int
r_int
id|__dummy
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;stc&t;sr, %0&bslash;n&bslash;t&quot;
l_string|&quot;or&t;#0xf0, %0&bslash;n&bslash;t&quot;
l_string|&quot;ldc&t;%0, sr&quot;
suffix:colon
l_string|&quot;=&amp;z&quot;
(paren
id|__dummy
)paren
suffix:colon
multiline_comment|/* no inputs */
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
DECL|macro|local_save_flags
mdefine_line|#define local_save_flags(x) &bslash;&n;&t;__asm__(&quot;stc sr, %0; and #0xf0, %0&quot; : &quot;=&amp;z&quot; (x) :/**/: &quot;memory&quot; )
DECL|macro|irqs_disabled
mdefine_line|#define irqs_disabled()&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long flags;&t;&t;&bslash;&n;&t;local_save_flags(flags);&t;&bslash;&n;&t;(flags != 0);&t;&t;&t;&bslash;&n;})
DECL|function|local_irq_save
r_static
id|__inline__
r_int
r_int
id|local_irq_save
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|flags
comma
id|__dummy
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;stc&t;sr, %1&bslash;n&bslash;t&quot;
l_string|&quot;mov&t;%1, %0&bslash;n&bslash;t&quot;
l_string|&quot;or&t;#0xf0, %0&bslash;n&bslash;t&quot;
l_string|&quot;ldc&t;%0, sr&bslash;n&bslash;t&quot;
l_string|&quot;mov&t;%1, %0&bslash;n&bslash;t&quot;
l_string|&quot;and&t;#0xf0, %0&quot;
suffix:colon
l_string|&quot;=&amp;z&quot;
(paren
id|flags
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|__dummy
)paren
suffix:colon
multiline_comment|/**/
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|flags
suffix:semicolon
)brace
macro_line|#ifdef DEBUG_CLI_STI
DECL|function|local_irq_restore
r_static
id|__inline__
r_void
id|local_irq_restore
c_func
(paren
r_int
r_int
id|x
)paren
(brace
r_if
c_cond
(paren
(paren
id|x
op_amp
l_int|0x000000f0
)paren
op_ne
l_int|0x000000f0
)paren
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
r_else
(brace
r_int
r_int
id|flags
suffix:semicolon
id|local_save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_eq
l_int|0
)paren
(brace
r_extern
r_void
id|dump_stack
c_func
(paren
r_void
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;BUG!&bslash;n&quot;
)paren
suffix:semicolon
id|dump_stack
c_func
(paren
)paren
suffix:semicolon
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
)brace
macro_line|#else
DECL|macro|local_irq_restore
mdefine_line|#define local_irq_restore(x) do { &t;&t;&t;&bslash;&n;&t;if ((x &amp; 0x000000f0) != 0x000000f0)&t;&t;&bslash;&n;&t;&t;local_irq_enable();&t;&t;&t;&t;&bslash;&n;} while (0)
macro_line|#endif
DECL|macro|really_restore_flags
mdefine_line|#define really_restore_flags(x) do { &t;&t;&t;&bslash;&n;&t;if ((x &amp; 0x000000f0) != 0x000000f0)&t;&t;&bslash;&n;&t;&t;local_irq_enable();&t;&t;&t;&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;local_irq_disable();&t;&t;&t;&t;&bslash;&n;} while (0)
multiline_comment|/*&n; * Jump to P2 area.&n; * When handling TLB or caches, we need to do it from P2 area.&n; */
DECL|macro|jump_to_P2
mdefine_line|#define jump_to_P2()&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long __dummy;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&bslash;&n;&t;&t;&quot;mov.l&t;1f, %0&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&t;&quot;or&t;%1, %0&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&t;&quot;jmp&t;@%0&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&t;&quot; nop&bslash;n&bslash;t&quot; &t;&t;&bslash;&n;&t;&t;&quot;.balign 4&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;1:&t;.long 2f&bslash;n&quot;&t;&bslash;&n;&t;&t;&quot;2:&quot;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=&amp;r&quot; (__dummy)&t;&bslash;&n;&t;&t;: &quot;r&quot; (0x20000000));&t;&bslash;&n;} while (0)
multiline_comment|/*&n; * Back to P1 area.&n; */
DECL|macro|back_to_P1
mdefine_line|#define back_to_P1()&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long __dummy;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;nop;nop;nop;nop;nop;nop;nop&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&t;&quot;mov.l&t;1f, %0&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;jmp&t;@%0&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot; nop&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.balign 4&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;1:&t;.long 2f&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;2:&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=&amp;r&quot; (__dummy));&t;&t;&t;&bslash;&n;} while (0)
multiline_comment|/* For spinlocks etc */
DECL|macro|local_irq_save
mdefine_line|#define local_irq_save(x)&t;x = local_irq_save()
DECL|function|xchg_u32
r_static
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
r_static
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
DECL|macro|arch_align_stack
mdefine_line|#define arch_align_stack(x) (x)
macro_line|#endif
eof
