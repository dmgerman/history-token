macro_line|#ifndef __ASM_ARM_SYSTEM_H
DECL|macro|__ASM_ARM_SYSTEM_H
mdefine_line|#define __ASM_ARM_SYSTEM_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/proc-fns.h&gt;
DECL|macro|vectors_base
mdefine_line|#define vectors_base()  (0)
DECL|function|__xchg
r_static
r_inline
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
r_switch
c_cond
(paren
id|size
)paren
(brace
r_case
l_int|1
suffix:colon
r_return
id|cpu_xchg_1
c_func
(paren
id|x
comma
id|ptr
)paren
suffix:semicolon
r_case
l_int|4
suffix:colon
r_return
id|cpu_xchg_4
c_func
(paren
id|x
comma
id|ptr
)paren
suffix:semicolon
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
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * We need to turn the caches off before calling the reset vector - RiscOS&n; * messes up if we don&squot;t&n; */
DECL|macro|proc_hard_reset
mdefine_line|#define proc_hard_reset()       cpu_proc_fin()
multiline_comment|/*&n; * A couple of speedups for the ARM&n; */
multiline_comment|/*&n; * Enable IRQs  (sti)&n; */
DECL|macro|local_irq_enable
mdefine_line|#define local_irq_enable()                                      &bslash;&n;        do {                                    &bslash;&n;          unsigned long temp;                   &bslash;&n;          __asm__ __volatile__(                 &bslash;&n;&quot;       mov     %0, pc          @ sti&bslash;n&quot;        &bslash;&n;&quot;       bic     %0, %0, #0x08000000&bslash;n&quot;          &bslash;&n;&quot;       teqp    %0, #0&bslash;n&quot;                       &bslash;&n;          : &quot;=r&quot; (temp)                         &bslash;&n;          :                                     &bslash;&n;          : &quot;memory&quot;);                          &bslash;&n;        } while(0)
multiline_comment|/*&n; * Disable IRQs (cli)&n; */
DECL|macro|local_irq_disable
mdefine_line|#define local_irq_disable()                                     &bslash;&n;        do {                                    &bslash;&n;          unsigned long temp;                   &bslash;&n;          __asm__ __volatile__(                 &bslash;&n;&quot;       mov     %0, pc          @ cli&bslash;n&quot;        &bslash;&n;&quot;       orr     %0, %0, #0x08000000&bslash;n&quot;          &bslash;&n;&quot;       teqp    %0, #0&bslash;n&quot;                       &bslash;&n;          : &quot;=r&quot; (temp)                         &bslash;&n;          :                                     &bslash;&n;          : &quot;memory&quot;);                          &bslash;&n;        } while(0)
multiline_comment|/* Disable FIQs  (clf) */
DECL|macro|__clf
mdefine_line|#define __clf() do {                            &bslash;&n;        unsigned long temp;                     &bslash;&n;        __asm__ __volatile__(                   &bslash;&n;&quot;       mov     %0, pc          @ clf&bslash;n&quot;        &bslash;&n;&quot;       orr     %0, %0, #0x04000000&bslash;n&quot;          &bslash;&n;&quot;       teqp    %0, #0&bslash;n&quot;                       &bslash;&n;        : &quot;=r&quot; (temp));                         &bslash;&n;    } while(0)
multiline_comment|/* Enable FIQs (stf) */
DECL|macro|__stf
mdefine_line|#define __stf() do {                            &bslash;&n;        unsigned long temp;                     &bslash;&n;        __asm__ __volatile__(                   &bslash;&n;&quot;       mov     %0, pc          @ stf&bslash;n&quot;        &bslash;&n;&quot;       bic     %0, %0, #0x04000000&bslash;n&quot;          &bslash;&n;&quot;       teqp    %0, #0&bslash;n&quot;                       &bslash;&n;        : &quot;=r&quot; (temp));                         &bslash;&n;    } while(0)
multiline_comment|/*&n; * save current IRQ &amp; FIQ state&n; */
DECL|macro|local_save_flags
mdefine_line|#define local_save_flags(x)                             &bslash;&n;        do {                                    &bslash;&n;          __asm__ __volatile__(                 &bslash;&n;&quot;       mov     %0, pc          @ save_flags&bslash;n&quot; &bslash;&n;&quot;       and     %0, %0, #0x0c000000&bslash;n&quot;          &bslash;&n;          : &quot;=r&quot; (x));                          &bslash;&n;        } while (0)
multiline_comment|/*&n; * Save the current interrupt enable state &amp; disable IRQs&n; */
DECL|macro|local_irq_save
mdefine_line|#define local_irq_save(x)                               &bslash;&n;        do {                                            &bslash;&n;          unsigned long temp;                           &bslash;&n;          __asm__ __volatile__(                         &bslash;&n;&quot;       mov     %0, pc          @ save_flags_cli&bslash;n&quot;     &bslash;&n;&quot;       orr     %1, %0, #0x08000000&bslash;n&quot;                  &bslash;&n;&quot;       and     %0, %0, #0x0c000000&bslash;n&quot;                  &bslash;&n;&quot;       teqp    %1, #0&bslash;n&quot;                               &bslash;&n;          : &quot;=r&quot; (x), &quot;=r&quot; (temp)                       &bslash;&n;          :                                             &bslash;&n;          : &quot;memory&quot;);                                  &bslash;&n;        } while (0)
multiline_comment|/*&n; * restore saved IRQ &amp; FIQ state&n; */
DECL|macro|local_irq_restore
mdefine_line|#define local_irq_restore(x)                            &bslash;&n;        do {                                            &bslash;&n;          unsigned long temp;                           &bslash;&n;          __asm__ __volatile__(                         &bslash;&n;&quot;       mov     %0, pc          @ restore_flags&bslash;n&quot;      &bslash;&n;&quot;       bic     %0, %0, #0x0c000000&bslash;n&quot;                  &bslash;&n;&quot;       orr     %0, %0, %1&bslash;n&quot;                           &bslash;&n;&quot;       teqp    %0, #0&bslash;n&quot;                               &bslash;&n;          : &quot;=&amp;r&quot; (temp)                                &bslash;&n;          : &quot;r&quot; (x)                                     &bslash;&n;          : &quot;memory&quot;);                                  &bslash;&n;        } while (0)
r_struct
id|thread_info
suffix:semicolon
multiline_comment|/* information about the system we&squot;re running on */
r_extern
r_int
r_int
id|system_rev
suffix:semicolon
r_extern
r_int
r_int
id|system_serial_low
suffix:semicolon
r_extern
r_int
r_int
id|system_serial_high
suffix:semicolon
r_struct
id|pt_regs
suffix:semicolon
r_void
id|die
c_func
(paren
r_const
r_char
op_star
id|msg
comma
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|err
)paren
id|__attribute__
c_func
(paren
(paren
id|noreturn
)paren
)paren
suffix:semicolon
r_void
id|die_if_kernel
c_func
(paren
r_const
r_char
op_star
id|str
comma
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|err
)paren
suffix:semicolon
r_void
id|hook_fault_code
c_func
(paren
r_int
id|nr
comma
r_int
(paren
op_star
id|fn
)paren
(paren
r_int
r_int
comma
r_int
r_int
comma
r_struct
id|pt_regs
op_star
)paren
comma
r_int
id|sig
comma
r_const
r_char
op_star
id|name
)paren
suffix:semicolon
DECL|macro|xchg
mdefine_line|#define xchg(ptr,x) &bslash;&n;&t;((__typeof__(*(ptr)))__xchg((unsigned long)(x),(ptr),sizeof(*(ptr))))
DECL|macro|tas
mdefine_line|#define tas(ptr) (xchg((ptr),1))
r_extern
id|asmlinkage
r_void
id|__backtrace
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * Include processor dependent parts&n; */
DECL|macro|mb
mdefine_line|#define mb() __asm__ __volatile__ (&quot;&quot; : : : &quot;memory&quot;)
DECL|macro|rmb
mdefine_line|#define rmb() mb()
DECL|macro|wmb
mdefine_line|#define wmb() mb()
DECL|macro|nop
mdefine_line|#define nop() __asm__ __volatile__(&quot;mov&bslash;tr0,r0&bslash;t@ nop&bslash;n&bslash;t&quot;);
DECL|macro|prepare_to_switch
mdefine_line|#define prepare_to_switch()    do { } while(0)
multiline_comment|/*&n; * switch_to(prev, next) should switch from task `prev&squot; to `next&squot;&n; * `prev&squot; will never be the same as `next&squot;.&n; * The `mb&squot; is to tell GCC not to cache `current&squot; across this call.&n; */
r_struct
id|thread_info
suffix:semicolon
r_extern
r_struct
id|task_struct
op_star
id|__switch_to
c_func
(paren
r_struct
id|thread_info
op_star
comma
r_struct
id|thread_info
op_star
)paren
suffix:semicolon
DECL|macro|switch_to
mdefine_line|#define switch_to(prev,next,last)                                       &bslash;&n;        do {                                                            &bslash;&n;                __switch_to(prev-&gt;thread_info,next-&gt;thread_info);       &bslash;&n;                mb();                                                   &bslash;&n;        } while (0)
macro_line|#ifdef CONFIG_SMP
macro_line|#error SMP not supported
macro_line|#endif /* CONFIG_SMP */
DECL|macro|irqs_disabled
mdefine_line|#define irqs_disabled()                 &bslash;&n;({                                      &bslash;&n;        unsigned long flags;            &bslash;&n;        local_save_flags(flags);        &bslash;&n;        flags &amp; PSR_I_BIT;              &bslash;&n;})
DECL|macro|set_mb
mdefine_line|#define set_mb(var, value)  do { var = value; mb(); } while (0)
DECL|macro|smp_mb
mdefine_line|#define smp_mb()&t;&t;barrier()
DECL|macro|smp_rmb
mdefine_line|#define smp_rmb()&t;&t;barrier()
DECL|macro|smp_wmb
mdefine_line|#define smp_wmb()&t;&t;barrier()
DECL|macro|smp_read_barrier_depends
mdefine_line|#define smp_read_barrier_depends()              do { } while(0)
DECL|macro|clf
mdefine_line|#define clf()&t;&t;&t;__clf()
DECL|macro|stf
mdefine_line|#define stf()&t;&t;&t;__stf()
macro_line|#endif /* __KERNEL__ */
macro_line|#endif
eof
