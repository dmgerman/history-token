macro_line|#ifndef __ASM_ARM_SYSTEM_H
DECL|macro|__ASM_ARM_SYSTEM_H
mdefine_line|#define __ASM_ARM_SYSTEM_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
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
r_extern
r_int
r_int
id|mem_fclk_21285
suffix:semicolon
multiline_comment|/*&n; * This tells us if we have an ISA bridge&n; * present in a PCI system.&n; */
macro_line|#ifdef CONFIG_PCI
r_extern
r_int
id|have_isa_bridge
suffix:semicolon
macro_line|#else
DECL|macro|have_isa_bridge
mdefine_line|#define have_isa_bridge&t;&t;(0)
macro_line|#endif
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
macro_line|#include &lt;asm/proc-fns.h&gt;
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
macro_line|#include &lt;asm/proc/system.h&gt;
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
DECL|macro|prepare_arch_schedule
mdefine_line|#define prepare_arch_schedule(prev)&t;&t;do { } while(0)
DECL|macro|finish_arch_schedule
mdefine_line|#define finish_arch_schedule(prev)&t;&t;do { } while(0)
DECL|macro|prepare_arch_switch
mdefine_line|#define prepare_arch_switch(rq)&t;&t;&t;do { } while(0)
DECL|macro|finish_arch_switch
mdefine_line|#define finish_arch_switch(rq)&t;&t;&t;spin_unlock_irq(&amp;(rq)-&gt;lock)
DECL|macro|switch_to
mdefine_line|#define switch_to(prev,next,last)&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t; &t;&t;&t;&t;&t;&bslash;&n;&t;&t;__switch_to(prev-&gt;thread_info,next-&gt;thread_info);&t;&bslash;&n;&t;&t;mb();&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;} while (0)
multiline_comment|/* For spinlocks etc */
DECL|macro|local_irq_save
mdefine_line|#define local_irq_save(x)&t;__save_flags_cli(x)
DECL|macro|local_irq_restore
mdefine_line|#define local_irq_restore(x)&t;__restore_flags(x)
DECL|macro|local_irq_disable
mdefine_line|#define local_irq_disable()&t;__cli()
DECL|macro|local_irq_enable
mdefine_line|#define local_irq_enable()&t;__sti()
macro_line|#ifdef CONFIG_SMP
macro_line|#error SMP not supported
DECL|macro|smp_mb
mdefine_line|#define smp_mb()&t;&t;mb()
DECL|macro|smp_rmb
mdefine_line|#define smp_rmb()&t;&t;rmb()
DECL|macro|smp_wmb
mdefine_line|#define smp_wmb()&t;&t;wmb()
macro_line|#else
DECL|macro|smp_mb
mdefine_line|#define smp_mb()&t;&t;barrier()
DECL|macro|smp_rmb
mdefine_line|#define smp_rmb()&t;&t;barrier()
DECL|macro|smp_wmb
mdefine_line|#define smp_wmb()&t;&t;barrier()
DECL|macro|cli
mdefine_line|#define cli()&t;&t;&t;__cli()
DECL|macro|sti
mdefine_line|#define sti()&t;&t;&t;__sti()
DECL|macro|clf
mdefine_line|#define clf()&t;&t;&t;__clf()
DECL|macro|stf
mdefine_line|#define stf()&t;&t;&t;__stf()
DECL|macro|save_flags
mdefine_line|#define save_flags(x)&t;&t;__save_flags(x)
DECL|macro|restore_flags
mdefine_line|#define restore_flags(x)&t;__restore_flags(x)
macro_line|#endif /* CONFIG_SMP */
macro_line|#endif /* __KERNEL__ */
macro_line|#endif
eof
