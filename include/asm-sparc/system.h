multiline_comment|/* $Id: system.h,v 1.86 2001/10/30 04:57:10 davem Exp $ */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifndef __SPARC_SYSTEM_H
DECL|macro|__SPARC_SYSTEM_H
mdefine_line|#define __SPARC_SYSTEM_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/threads.h&gt;&t;/* NR_CPUS */
macro_line|#include &lt;linux/thread_info.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/psr.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/btfixup.h&gt;
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
multiline_comment|/* Really, userland should not be looking at any of this... */
macro_line|#ifdef __KERNEL__
r_extern
r_enum
id|sparc_cpu
id|sparc_cpu_model
suffix:semicolon
macro_line|#ifndef CONFIG_SUN4
DECL|macro|ARCH_SUN4C_SUN4
mdefine_line|#define ARCH_SUN4C_SUN4 (sparc_cpu_model==sun4c)
DECL|macro|ARCH_SUN4
mdefine_line|#define ARCH_SUN4 0
macro_line|#else
DECL|macro|ARCH_SUN4C_SUN4
mdefine_line|#define ARCH_SUN4C_SUN4 1
DECL|macro|ARCH_SUN4
mdefine_line|#define ARCH_SUN4 1
macro_line|#endif
DECL|macro|SUN4M_NCPUS
mdefine_line|#define SUN4M_NCPUS            4              /* Architectural limit of sun4m. */
r_extern
r_struct
id|thread_info
op_star
id|current_set
(braket
id|NR_CPUS
)braket
suffix:semicolon
r_extern
r_int
r_int
id|empty_bad_page
suffix:semicolon
r_extern
r_int
r_int
id|empty_bad_page_table
suffix:semicolon
r_extern
r_int
r_int
id|empty_zero_page
suffix:semicolon
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
multiline_comment|/* When a context switch happens we must flush all user windows so that&n; * the windows of the current process are flushed onto its stack. This&n; * way the windows are all clean for the next process and the stack&n; * frames are up to date.&n; */
r_extern
r_void
id|flush_user_windows
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|kill_user_windows
c_func
(paren
r_void
)paren
suffix:semicolon
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
id|fpsave
c_func
(paren
r_int
r_int
op_star
id|fpregs
comma
r_int
r_int
op_star
id|fsr
comma
r_void
op_star
id|fpqueue
comma
r_int
r_int
op_star
id|fpqdepth
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
DECL|macro|SWITCH_ENTER
mdefine_line|#define SWITCH_ENTER(prv) &bslash;&n;&t;do {&t;&t;&t;&bslash;&n;&t;if (test_tsk_thread_flag(prv, TIF_USEDFPU)) { &bslash;&n;&t;&t;put_psr(get_psr() | PSR_EF); &bslash;&n;&t;&t;fpsave(&amp;(prv)-&gt;thread.float_regs[0], &amp;(prv)-&gt;thread.fsr, &bslash;&n;&t;&t;       &amp;(prv)-&gt;thread.fpqueue[0], &amp;(prv)-&gt;thread.fpqdepth); &bslash;&n;&t;&t;clear_tsk_thread_flag(prv, TIF_USEDFPU); &bslash;&n;&t;&t;(prv)-&gt;thread.kregs-&gt;psr &amp;= ~PSR_EF; &bslash;&n;&t;} &bslash;&n;&t;} while(0)
DECL|macro|SWITCH_DO_LAZY_FPU
mdefine_line|#define SWITCH_DO_LAZY_FPU(next)&t;/* */
macro_line|#else
DECL|macro|SWITCH_ENTER
mdefine_line|#define SWITCH_ENTER(prv)&t;&t;/* */
DECL|macro|SWITCH_DO_LAZY_FPU
mdefine_line|#define SWITCH_DO_LAZY_FPU(nxt)&t;&bslash;&n;&t;do {&t;&t;&t;&bslash;&n;&t;if (last_task_used_math != (nxt))&t;&t;&bslash;&n;&t;&t;(nxt)-&gt;thread.kregs-&gt;psr&amp;=~PSR_EF;&t;&bslash;&n;&t;} while(0)
macro_line|#endif
multiline_comment|/*&n; * Flush windows so that the VM switch which follows&n; * would not pull the stack from under us.&n; *&n; * SWITCH_ENTER and SWITH_DO_LAZY_FPU do not work yet (e.g. SMP does not work)&n; * XXX WTF is the above comment? Found in late teen 2.4.x.&n; */
DECL|macro|prepare_arch_switch
mdefine_line|#define prepare_arch_switch(rq, next) do { &bslash;&n;&t;__asm__ __volatile__( &bslash;&n;&t;&quot;.globl&bslash;tflush_patch_switch&bslash;nflush_patch_switch:&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;save %sp, -0x40, %sp; save %sp, -0x40, %sp; save %sp, -0x40, %sp&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;save %sp, -0x40, %sp; save %sp, -0x40, %sp; save %sp, -0x40, %sp&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;save %sp, -0x40, %sp&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;restore; restore; restore; restore; restore; restore; restore&quot;); &bslash;&n;} while(0)
DECL|macro|finish_arch_switch
mdefine_line|#define finish_arch_switch(rq, next)&t;spin_unlock_irq(&amp;(rq)-&gt;lock)
DECL|macro|task_running
mdefine_line|#define task_running(rq, p)&t;&t;((rq)-&gt;curr == (p))
multiline_comment|/* Much care has gone into this code, do not touch it.&n;&t; *&n;&t; * We need to loadup regs l0/l1 for the newly forked child&n;&t; * case because the trap return path relies on those registers&n;&t; * holding certain values, gcc is told that they are clobbered.&n;&t; * Gcc needs registers for 3 values in and 1 value out, so we&n;&t; * clobber every non-fixed-usage register besides l2/l3/o4/o5.  -DaveM&n;&t; *&n;&t; * Hey Dave, that do not touch sign is too much of an incentive&n;&t; * - Anton &amp; Pete&n;&t; */
DECL|macro|switch_to
mdefine_line|#define switch_to(prev, next, last) do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;SWITCH_ENTER(prev);&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;SWITCH_DO_LAZY_FPU(next);&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;cpu_set(smp_processor_id(), next-&gt;active_mm-&gt;cpu_vm_mask);&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;sethi&t;%%hi(here - 0x8), %%o7&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;mov&t;%%g6, %%g3&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;or&t;%%o7, %%lo(here - 0x8), %%o7&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;rd&t;%%psr, %%g4&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;std&t;%%sp, [%%g6 + %4]&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;rd&t;%%wim, %%g5&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;wr&t;%%g4, 0x20, %%psr&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;nop&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;std&t;%%g4, [%%g6 + %3]&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;ldd&t;[%2 + %3], %%g4&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;mov&t;%2, %%g6&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.globl&t;patchme_store_new_current&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&quot;patchme_store_new_current:&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;st&t;%2, [%1]&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;wr&t;%%g4, 0x20, %%psr&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;nop&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;nop&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;nop&bslash;n&bslash;t&quot;&t;/* LEON needs all 3 nops: load to %sp depends on CWP. */&t;&t;&bslash;&n;&t;&quot;ldd&t;[%%g6 + %4], %%sp&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;wr&t;%%g5, 0x0, %%wim&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;ldd&t;[%%sp + 0x00], %%l0&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;ldd&t;[%%sp + 0x38], %%i6&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;wr&t;%%g4, 0x0, %%psr&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;nop&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;nop&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;jmpl&t;%%o7 + 0x8, %%g0&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot; ld&t;[%%g3 + %5], %0&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;here:&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;        : &quot;=&amp;r&quot; (last)&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;        : &quot;r&quot; (&amp;(current_set[hard_smp_processor_id()])),&t;&bslash;&n;&t;  &quot;r&quot; ((next)-&gt;thread_info),&t;&t;&t;&t;&bslash;&n;&t;  &quot;i&quot; (TI_KPSR),&t;&t;&t;&t;&t;&bslash;&n;&t;  &quot;i&quot; (TI_KSP),&t;&t;&t;&t;&t;&t;&bslash;&n;&t;  &quot;i&quot; (TI_TASK)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;:       &quot;g1&quot;, &quot;g2&quot;, &quot;g3&quot;, &quot;g4&quot;, &quot;g5&quot;,       &quot;g7&quot;,&t;&bslash;&n;&t;  &quot;l0&quot;, &quot;l1&quot;,       &quot;l3&quot;, &quot;l4&quot;, &quot;l5&quot;, &quot;l6&quot;, &quot;l7&quot;,&t;&bslash;&n;&t;  &quot;i0&quot;, &quot;i1&quot;, &quot;i2&quot;, &quot;i3&quot;, &quot;i4&quot;, &quot;i5&quot;,&t;&t;&t;&bslash;&n;&t;  &quot;o0&quot;, &quot;o1&quot;, &quot;o2&quot;, &quot;o3&quot;,                   &quot;o7&quot;);&t;&bslash;&n;&t;} while(0)
multiline_comment|/*&n; * Changing the IRQ level on the Sparc.&n; */
r_extern
r_void
id|local_irq_restore
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
r_int
id|__local_irq_save
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|local_irq_enable
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|getipl
r_static
r_inline
r_int
r_int
id|getipl
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|retval
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;rd&t;%%psr, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|retval
)paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|macro|local_save_flags
mdefine_line|#define local_save_flags(flags)&t;((flags) = getipl())
DECL|macro|local_irq_save
mdefine_line|#define local_irq_save(flags)&t;((flags) = __local_irq_save())
DECL|macro|local_irq_disable
mdefine_line|#define local_irq_disable()&t;((void) __local_irq_save())
DECL|macro|irqs_disabled
mdefine_line|#define irqs_disabled()&t;&t;((getipl() &amp; PSR_PIL) != 0)
multiline_comment|/* XXX Change this if we ever use a PSO mode kernel. */
DECL|macro|mb
mdefine_line|#define mb()&t;__asm__ __volatile__ (&quot;&quot; : : : &quot;memory&quot;)
DECL|macro|rmb
mdefine_line|#define rmb()&t;mb()
DECL|macro|wmb
mdefine_line|#define wmb()&t;mb()
DECL|macro|read_barrier_depends
mdefine_line|#define read_barrier_depends()&t;do { } while(0)
DECL|macro|set_mb
mdefine_line|#define set_mb(__var, __value)  do { __var = __value; mb(); } while(0)
DECL|macro|set_wmb
mdefine_line|#define set_wmb(__var, __value) set_mb(__var, __value)
DECL|macro|smp_mb
mdefine_line|#define smp_mb()&t;__asm__ __volatile__(&quot;&quot;:::&quot;memory&quot;)
DECL|macro|smp_rmb
mdefine_line|#define smp_rmb()&t;__asm__ __volatile__(&quot;&quot;:::&quot;memory&quot;)
DECL|macro|smp_wmb
mdefine_line|#define smp_wmb()&t;__asm__ __volatile__(&quot;&quot;:::&quot;memory&quot;)
DECL|macro|smp_read_barrier_depends
mdefine_line|#define smp_read_barrier_depends()&t;do { } while(0)
DECL|macro|nop
mdefine_line|#define nop() __asm__ __volatile__ (&quot;nop&quot;)
multiline_comment|/* This has special calling conventions */
macro_line|#ifndef CONFIG_SMP
id|BTFIXUPDEF_CALL
c_func
(paren
r_void
comma
id|___xchg32
comma
r_void
)paren
macro_line|#endif
DECL|function|xchg_u32
r_extern
id|__inline__
r_int
r_int
id|xchg_u32
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
macro_line|#ifdef CONFIG_SMP
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;swap [%2], %0&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|val
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
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
macro_line|#else
r_register
r_int
r_int
op_star
id|ptr
id|asm
c_func
(paren
l_string|&quot;g1&quot;
)paren
suffix:semicolon
r_register
r_int
r_int
id|ret
id|asm
c_func
(paren
l_string|&quot;g2&quot;
)paren
suffix:semicolon
id|ptr
op_assign
(paren
r_int
r_int
op_star
)paren
id|m
suffix:semicolon
id|ret
op_assign
id|val
suffix:semicolon
multiline_comment|/* Note: this is magic and the nop there is&n;&t;   really needed. */
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;mov&t;%%o7, %%g4&bslash;n&bslash;t&quot;
l_string|&quot;call&t;___f____xchg32&bslash;n&bslash;t&quot;
l_string|&quot; nop&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|ret
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|ret
)paren
comma
l_string|&quot;r&quot;
(paren
id|ptr
)paren
suffix:colon
l_string|&quot;g3&quot;
comma
l_string|&quot;g4&quot;
comma
l_string|&quot;g7&quot;
comma
l_string|&quot;memory&quot;
comma
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
macro_line|#endif
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
id|xchg_u32
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
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif /* !(__SPARC_SYSTEM_H) */
eof
