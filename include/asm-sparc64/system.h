multiline_comment|/* $Id: system.h,v 1.69 2002/02/09 19:49:31 davem Exp $ */
macro_line|#ifndef __SPARC64_SYSTEM_H
DECL|macro|__SPARC64_SYSTEM_H
mdefine_line|#define __SPARC64_SYSTEM_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/visasm.h&gt;
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * Sparc (general) CPU types&n; */
DECL|enum|sparc_cpu
r_enum
id|sparc_cpu
(brace
DECL|enumerator|sun4
id|sun4
op_assign
l_int|0x00
comma
DECL|enumerator|sun4c
id|sun4c
op_assign
l_int|0x01
comma
DECL|enumerator|sun4m
id|sun4m
op_assign
l_int|0x02
comma
DECL|enumerator|sun4d
id|sun4d
op_assign
l_int|0x03
comma
DECL|enumerator|sun4e
id|sun4e
op_assign
l_int|0x04
comma
DECL|enumerator|sun4u
id|sun4u
op_assign
l_int|0x05
comma
multiline_comment|/* V8 ploos ploos */
DECL|enumerator|sun_unknown
id|sun_unknown
op_assign
l_int|0x06
comma
DECL|enumerator|ap1000
id|ap1000
op_assign
l_int|0x07
comma
multiline_comment|/* almost a sun4m */
)brace
suffix:semicolon
DECL|macro|sparc_cpu_model
mdefine_line|#define sparc_cpu_model sun4u
multiline_comment|/* This cannot ever be a sun4c nor sun4 :) That&squot;s just history. */
DECL|macro|ARCH_SUN4C_SUN4
mdefine_line|#define ARCH_SUN4C_SUN4 0
DECL|macro|ARCH_SUN4
mdefine_line|#define ARCH_SUN4 0
macro_line|#endif
DECL|macro|setipl
mdefine_line|#define setipl(__new_ipl) &bslash;&n;&t;__asm__ __volatile__(&quot;wrpr&t;%0, %%pil&quot;  : : &quot;r&quot; (__new_ipl) : &quot;memory&quot;)
DECL|macro|local_irq_disable
mdefine_line|#define local_irq_disable() &bslash;&n;&t;__asm__ __volatile__(&quot;wrpr&t;15, %%pil&quot; : : : &quot;memory&quot;)
DECL|macro|local_irq_enable
mdefine_line|#define local_irq_enable() &bslash;&n;&t;__asm__ __volatile__(&quot;wrpr&t;0, %%pil&quot; : : : &quot;memory&quot;)
DECL|macro|getipl
mdefine_line|#define getipl() &bslash;&n;({ unsigned long retval; __asm__ __volatile__(&quot;rdpr&t;%%pil, %0&quot; : &quot;=r&quot; (retval)); retval; })
DECL|macro|swap_pil
mdefine_line|#define swap_pil(__new_pil) &bslash;&n;({&t;unsigned long retval; &bslash;&n;&t;__asm__ __volatile__(&quot;rdpr&t;%%pil, %0&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&t;     &quot;wrpr&t;%1, %%pil&quot; &bslash;&n;&t;&t;&t;     : &quot;=&amp;r&quot; (retval) &bslash;&n;&t;&t;&t;     : &quot;r&quot; (__new_pil) &bslash;&n;&t;&t;&t;     : &quot;memory&quot;); &bslash;&n;&t;retval; &bslash;&n;})
DECL|macro|read_pil_and_cli
mdefine_line|#define read_pil_and_cli() &bslash;&n;({&t;unsigned long retval; &bslash;&n;&t;__asm__ __volatile__(&quot;rdpr&t;%%pil, %0&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&t;     &quot;wrpr&t;15, %%pil&quot; &bslash;&n;&t;&t;&t;     : &quot;=r&quot; (retval) &bslash;&n;&t;&t;&t;     : : &quot;memory&quot;); &bslash;&n;&t;retval; &bslash;&n;})
DECL|macro|local_save_flags
mdefine_line|#define local_save_flags(flags)&t;&t;((flags) = getipl())
DECL|macro|local_irq_save
mdefine_line|#define local_irq_save(flags)&t;&t;((flags) = read_pil_and_cli())
DECL|macro|local_irq_restore
mdefine_line|#define local_irq_restore(flags)&t;&t;setipl((flags))
multiline_comment|/* On sparc64 IRQ flags are the PIL register.  A value of zero&n; * means all interrupt levels are enabled, any other value means&n; * only IRQ levels greater than that value will be received.&n; * Consequently this means that the lowest IRQ level is one.&n; */
DECL|macro|irqs_disabled
mdefine_line|#define irqs_disabled()&t;&t;&bslash;&n;({&t;unsigned long flags;&t;&bslash;&n;&t;local_save_flags(flags);&bslash;&n;&t;(flags &gt; 0);&t;&t;&bslash;&n;})
DECL|macro|nop
mdefine_line|#define nop() &t;&t;__asm__ __volatile__ (&quot;nop&quot;)
DECL|macro|membar
mdefine_line|#define membar(type)&t;__asm__ __volatile__ (&quot;membar &quot; type : : : &quot;memory&quot;)
DECL|macro|mb
mdefine_line|#define mb()&t;&t;&bslash;&n;&t;membar(&quot;#LoadLoad | #LoadStore | #StoreStore | #StoreLoad&quot;)
DECL|macro|rmb
mdefine_line|#define rmb()&t;&t;membar(&quot;#LoadLoad&quot;)
DECL|macro|wmb
mdefine_line|#define wmb()&t;&t;membar(&quot;#StoreStore&quot;)
DECL|macro|read_barrier_depends
mdefine_line|#define read_barrier_depends()&t;&t;do { } while(0)
DECL|macro|set_mb
mdefine_line|#define set_mb(__var, __value) &bslash;&n;&t;do { __var = __value; membar(&quot;#StoreLoad | #StoreStore&quot;); } while(0)
DECL|macro|set_wmb
mdefine_line|#define set_wmb(__var, __value) &bslash;&n;&t;do { __var = __value; membar(&quot;#StoreStore&quot;); } while(0)
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
mdefine_line|#define smp_mb()&t;__asm__ __volatile__(&quot;&quot;:::&quot;memory&quot;)
DECL|macro|smp_rmb
mdefine_line|#define smp_rmb()&t;__asm__ __volatile__(&quot;&quot;:::&quot;memory&quot;)
DECL|macro|smp_wmb
mdefine_line|#define smp_wmb()&t;__asm__ __volatile__(&quot;&quot;:::&quot;memory&quot;)
DECL|macro|smp_read_barrier_depends
mdefine_line|#define smp_read_barrier_depends()&t;do { } while(0)
macro_line|#endif
DECL|macro|flushi
mdefine_line|#define flushi(addr)&t;__asm__ __volatile__ (&quot;flush %0&quot; : : &quot;r&quot; (addr) : &quot;memory&quot;)
DECL|macro|flushw_all
mdefine_line|#define flushw_all()&t;__asm__ __volatile__(&quot;flushw&quot;)
multiline_comment|/* Performance counter register access. */
DECL|macro|read_pcr
mdefine_line|#define read_pcr(__p)  __asm__ __volatile__(&quot;rd&t;%%pcr, %0&quot; : &quot;=r&quot; (__p))
DECL|macro|write_pcr
mdefine_line|#define write_pcr(__p) __asm__ __volatile__(&quot;wr&t;%0, 0x0, %%pcr&quot; : : &quot;r&quot; (__p))
DECL|macro|read_pic
mdefine_line|#define read_pic(__p)  __asm__ __volatile__(&quot;rd %%pic, %0&quot; : &quot;=r&quot; (__p))
multiline_comment|/* Blackbird errata workaround.  See commentary in&n; * arch/sparc64/kernel/smp.c:smp_percpu_timer_interrupt()&n; * for more information.&n; */
DECL|macro|reset_pic
mdefine_line|#define reset_pic()    &t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&quot;ba,pt&t;%xcc, 99f&bslash;n&bslash;t&quot;&t;&t;&bslash;&n;&t;&t;&t;     &quot;.align&t;64&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;  &quot;99:wr&t;%g0, 0x0, %pic&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&t;&t;     &quot;rd&t;%pic, %g0&quot;)
macro_line|#ifndef __ASSEMBLY__
r_extern
r_void
id|sun_do_break
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|serial_console
suffix:semicolon
r_extern
r_int
id|stop_a_enabled
suffix:semicolon
DECL|function|con_is_present
r_static
id|__inline__
r_int
id|con_is_present
c_func
(paren
r_void
)paren
(brace
r_return
id|serial_console
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
)brace
r_extern
r_void
id|synchronize_user_stack
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__flushw_user
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|flushw_user
mdefine_line|#define flushw_user() __flushw_user()
DECL|macro|flush_user_windows
mdefine_line|#define flush_user_windows flushw_user
DECL|macro|flush_register_windows
mdefine_line|#define flush_register_windows flushw_all
DECL|macro|prepare_arch_switch
mdefine_line|#define prepare_arch_switch(rq, next)&t;&t;&bslash;&n;do {&t;spin_lock(&amp;(next)-&gt;switch_lock);&t;&bslash;&n;&t;spin_unlock(&amp;(rq)-&gt;lock);&t;&t;&bslash;&n;&t;flushw_all();&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|finish_arch_switch
mdefine_line|#define finish_arch_switch(rq, prev)&t;&t;&bslash;&n;do {&t;spin_unlock_irq(&amp;(prev)-&gt;switch_lock);&t;&bslash;&n;} while (0)
DECL|macro|task_running
mdefine_line|#define task_running(rq, p) &bslash;&n;&t;((rq)-&gt;curr == (p) || spin_is_locked(&amp;(p)-&gt;switch_lock))
multiline_comment|/* See what happens when you design the chip correctly?&n;&t; *&n;&t; * We tell gcc we clobber all non-fixed-usage registers except&n;&t; * for l0/l1.  It will use one for &squot;next&squot; and the other to hold&n;&t; * the output value of &squot;last&squot;.  &squot;next&squot; is not referenced again&n;&t; * past the invocation of switch_to in the scheduler, so we need&n;&t; * not preserve it&squot;s value.  Hairy, but it lets us remove 2 loads&n;&t; * and 2 stores in this critical code path.  -DaveM&n;&t; */
macro_line|#if __GNUC__ &gt;= 3
DECL|macro|EXTRA_CLOBBER
mdefine_line|#define EXTRA_CLOBBER ,&quot;%l1&quot;
macro_line|#else
DECL|macro|EXTRA_CLOBBER
mdefine_line|#define EXTRA_CLOBBER
macro_line|#endif
DECL|macro|switch_to
mdefine_line|#define switch_to(prev, next, last)&t;&t;&t;&t;&t;&bslash;&n;do {&t;if (test_thread_flag(TIF_PERFCTR)) {&t;&t;&t;&t;&bslash;&n;&t;&t;unsigned long __tmp;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;read_pcr(__tmp);&t;&t;&t;&t;&t;&bslash;&n;&t;&t;current_thread_info()-&gt;pcr_reg = __tmp;&t;&t;&t;&bslash;&n;&t;&t;read_pic(__tmp);&t;&t;&t;&t;&t;&bslash;&n;&t;&t;current_thread_info()-&gt;kernel_cntd0 += (unsigned int)(__tmp);&bslash;&n;&t;&t;current_thread_info()-&gt;kernel_cntd1 += ((__tmp) &gt;&gt; 32);&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;flush_tlb_pending();&t;&t;&t;&t;&t;&t;&bslash;&n;&t;save_and_clear_fpu();&t;&t;&t;&t;&t;&t;&bslash;&n;&t;/* If you are tempted to conditionalize the following */&t;&bslash;&n;&t;/* so that ASI is only written if it changes, think again. */&t;&bslash;&n;&t;__asm__ __volatile__(&quot;wr %%g0, %0, %%asi&quot;&t;&t;&t;&bslash;&n;&t;: : &quot;r&quot; (__thread_flag_byte_ptr(next-&gt;thread_info)[TI_FLAG_BYTE_CURRENT_DS]));&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;mov&t;%%g4, %%g7&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;wrpr&t;%%g0, 0x95, %%pstate&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;stx&t;%%i6, [%%sp + 2047 + 0x70]&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;stx&t;%%i7, [%%sp + 2047 + 0x78]&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;rdpr&t;%%wstate, %%o5&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;stx&t;%%o6, [%%g6 + %3]&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;stb&t;%%o5, [%%g6 + %2]&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;rdpr&t;%%cwp, %%o5&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;stb&t;%%o5, [%%g6 + %5]&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;mov&t;%1, %%g6&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;ldub&t;[%1 + %5], %%g1&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;wrpr&t;%%g1, %%cwp&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;ldx&t;[%%g6 + %3], %%o6&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;ldub&t;[%%g6 + %2], %%o5&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;ldx&t;[%%g6 + %4], %%o7&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;mov&t;%%g6, %%l2&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;wrpr&t;%%o5, 0x0, %%wstate&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;ldx&t;[%%sp + 2047 + 0x70], %%i6&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;ldx&t;[%%sp + 2047 + 0x78], %%i7&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;wrpr&t;%%g0, 0x94, %%pstate&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;mov&t;%%l2, %%g6&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;ldx&t;[%%g6 + %7], %%g4&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;wrpr&t;%%g0, 0x96, %%pstate&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;andcc&t;%%o7, %6, %%g0&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;beq,pt %%icc, 1f&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot; mov&t;%%g7, %0&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;b,a ret_from_syscall&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;1:&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;=&amp;r&quot; (last)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;0&quot; (next-&gt;thread_info),&t;&t;&t;&t;&t;&bslash;&n;&t;  &quot;i&quot; (TI_WSTATE), &quot;i&quot; (TI_KSP), &quot;i&quot; (TI_FLAGS), &quot;i&quot; (TI_CWP),&t;&bslash;&n;&t;  &quot;i&quot; (_TIF_NEWCHILD), &quot;i&quot; (TI_TASK)&t;&t;&t;&t;&bslash;&n;&t;: &quot;cc&quot;,&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;        &quot;g1&quot;, &quot;g2&quot;, &quot;g3&quot;,                   &quot;g7&quot;,&t;&t;&bslash;&n;&t;              &quot;l2&quot;, &quot;l3&quot;, &quot;l4&quot;, &quot;l5&quot;, &quot;l6&quot;, &quot;l7&quot;,&t;&t;&bslash;&n;&t;  &quot;i0&quot;, &quot;i1&quot;, &quot;i2&quot;, &quot;i3&quot;, &quot;i4&quot;, &quot;i5&quot;,&t;&t;&t;&t;&bslash;&n;&t;  &quot;o0&quot;, &quot;o1&quot;, &quot;o2&quot;, &quot;o3&quot;, &quot;o4&quot;, &quot;o5&quot;,       &quot;o7&quot; EXTRA_CLOBBER);&bslash;&n;&t;/* If you fuck with this, update ret_from_syscall code too. */&t;&bslash;&n;&t;if (test_thread_flag(TIF_PERFCTR)) {&t;&t;&t;&t;&bslash;&n;&t;&t;write_pcr(current_thread_info()-&gt;pcr_reg);&t;&t;&bslash;&n;&t;&t;reset_pic();&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while(0)
DECL|function|xchg32
r_static
r_inline
r_int
r_int
id|xchg32
c_func
(paren
id|__volatile__
r_int
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
id|tmp1
comma
id|tmp2
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&t;membar&t;&t;#StoreLoad | #LoadLoad&bslash;n&quot;
l_string|&quot;&t;mov&t;&t;%0, %1&bslash;n&quot;
l_string|&quot;1:&t;lduw&t;&t;[%4], %2&bslash;n&quot;
l_string|&quot;&t;cas&t;&t;[%4], %2, %0&bslash;n&quot;
l_string|&quot;&t;cmp&t;&t;%2, %0&bslash;n&quot;
l_string|&quot;&t;bne,a,pn&t;%%icc, 1b&bslash;n&quot;
l_string|&quot;&t; mov&t;&t;%1, %0&bslash;n&quot;
l_string|&quot;&t;membar&t;&t;#StoreLoad | #StoreStore&bslash;n&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|val
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|tmp1
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|tmp2
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|val
)paren
comma
l_string|&quot;r&quot;
(paren
id|m
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
DECL|function|xchg64
r_static
r_inline
r_int
r_int
id|xchg64
c_func
(paren
id|__volatile__
r_int
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
id|tmp1
comma
id|tmp2
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&t;membar&t;&t;#StoreLoad | #LoadLoad&bslash;n&quot;
l_string|&quot;&t;mov&t;&t;%0, %1&bslash;n&quot;
l_string|&quot;1:&t;ldx&t;&t;[%4], %2&bslash;n&quot;
l_string|&quot;&t;casx&t;&t;[%4], %2, %0&bslash;n&quot;
l_string|&quot;&t;cmp&t;&t;%2, %0&bslash;n&quot;
l_string|&quot;&t;bne,a,pn&t;%%xcc, 1b&bslash;n&quot;
l_string|&quot;&t; mov&t;&t;%1, %0&bslash;n&quot;
l_string|&quot;&t;membar&t;&t;#StoreLoad | #StoreStore&bslash;n&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|val
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|tmp1
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|tmp2
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|val
)paren
comma
l_string|&quot;r&quot;
(paren
id|m
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
DECL|macro|xchg
mdefine_line|#define xchg(ptr,x) ((__typeof__(*(ptr)))__xchg((unsigned long)(x),(ptr),sizeof(*(ptr))))
DECL|macro|tas
mdefine_line|#define tas(ptr) (xchg((ptr),1))
r_extern
r_void
id|__xchg_called_with_bad_pointer
c_func
(paren
r_void
)paren
suffix:semicolon
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
id|__volatile__
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
id|xchg32
c_func
(paren
id|ptr
comma
id|x
)paren
suffix:semicolon
r_case
l_int|8
suffix:colon
r_return
id|xchg64
c_func
(paren
id|ptr
comma
id|x
)paren
suffix:semicolon
)brace
suffix:semicolon
id|__xchg_called_with_bad_pointer
c_func
(paren
)paren
suffix:semicolon
r_return
id|x
suffix:semicolon
)brace
r_extern
r_void
id|die_if_kernel
c_func
(paren
r_char
op_star
id|str
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
id|__attribute__
(paren
(paren
id|noreturn
)paren
)paren
suffix:semicolon
multiline_comment|/* &n; * Atomic compare and exchange.  Compare OLD with MEM, if identical,&n; * store NEW in MEM.  Return the initial value in MEM.  Success is&n; * indicated by comparing RETURN with OLD.&n; */
DECL|macro|__HAVE_ARCH_CMPXCHG
mdefine_line|#define __HAVE_ARCH_CMPXCHG 1
r_static
id|__inline__
r_int
r_int
DECL|function|__cmpxchg_u32
id|__cmpxchg_u32
c_func
(paren
r_volatile
r_int
op_star
id|m
comma
r_int
id|old
comma
r_int
r_new
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;membar #StoreLoad | #LoadLoad&bslash;n&quot;
l_string|&quot;cas [%2], %3, %0&bslash;n&bslash;t&quot;
l_string|&quot;membar #StoreLoad | #StoreStore&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
r_new
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
r_new
)paren
comma
l_string|&quot;r&quot;
(paren
id|m
)paren
comma
l_string|&quot;r&quot;
(paren
id|old
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
r_new
suffix:semicolon
)brace
r_static
id|__inline__
r_int
r_int
DECL|function|__cmpxchg_u64
id|__cmpxchg_u64
c_func
(paren
r_volatile
r_int
op_star
id|m
comma
r_int
r_int
id|old
comma
r_int
r_int
r_new
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;membar #StoreLoad | #LoadLoad&bslash;n&quot;
l_string|&quot;casx [%2], %3, %0&bslash;n&bslash;t&quot;
l_string|&quot;membar #StoreLoad | #StoreStore&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
r_new
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
r_new
)paren
comma
l_string|&quot;r&quot;
(paren
id|m
)paren
comma
l_string|&quot;r&quot;
(paren
id|old
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
r_new
suffix:semicolon
)brace
multiline_comment|/* This function doesn&squot;t exist, so you&squot;ll get a linker error&n;   if something tries to do an invalid cmpxchg().  */
r_extern
r_void
id|__cmpxchg_called_with_bad_pointer
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
id|__inline__
r_int
r_int
DECL|function|__cmpxchg
id|__cmpxchg
c_func
(paren
r_volatile
r_void
op_star
id|ptr
comma
r_int
r_int
id|old
comma
r_int
r_int
r_new
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
id|__cmpxchg_u32
c_func
(paren
id|ptr
comma
id|old
comma
r_new
)paren
suffix:semicolon
r_case
l_int|8
suffix:colon
r_return
id|__cmpxchg_u64
c_func
(paren
id|ptr
comma
id|old
comma
r_new
)paren
suffix:semicolon
)brace
id|__cmpxchg_called_with_bad_pointer
c_func
(paren
)paren
suffix:semicolon
r_return
id|old
suffix:semicolon
)brace
DECL|macro|cmpxchg
mdefine_line|#define cmpxchg(ptr,o,n)&t;&t;&t;&t;&t;&t; &bslash;&n;  ({&t;&t;&t;&t;&t;&t;&t;&t;&t; &bslash;&n;     __typeof__(*(ptr)) _o_ = (o);&t;&t;&t;&t;&t; &bslash;&n;     __typeof__(*(ptr)) _n_ = (n);&t;&t;&t;&t;&t; &bslash;&n;     (__typeof__(*(ptr))) __cmpxchg((ptr), (unsigned long)_o_,&t;&t; &bslash;&n;&t;&t;&t;&t;    (unsigned long)_n_, sizeof(*(ptr))); &bslash;&n;  })
macro_line|#endif /* !(__ASSEMBLY__) */
DECL|macro|arch_align_stack
mdefine_line|#define arch_align_stack(x) (x)
macro_line|#endif /* !(__SPARC64_SYSTEM_H) */
eof
