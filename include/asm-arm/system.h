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
DECL|macro|CPU_ARCH_UNKNOWN
mdefine_line|#define CPU_ARCH_UNKNOWN&t;0
DECL|macro|CPU_ARCH_ARMv3
mdefine_line|#define CPU_ARCH_ARMv3&t;&t;1
DECL|macro|CPU_ARCH_ARMv4
mdefine_line|#define CPU_ARCH_ARMv4&t;&t;2
DECL|macro|CPU_ARCH_ARMv4T
mdefine_line|#define CPU_ARCH_ARMv4T&t;&t;3
DECL|macro|CPU_ARCH_ARMv5
mdefine_line|#define CPU_ARCH_ARMv5&t;&t;4
DECL|macro|CPU_ARCH_ARMv5T
mdefine_line|#define CPU_ARCH_ARMv5T&t;&t;5
DECL|macro|CPU_ARCH_ARMv5TE
mdefine_line|#define CPU_ARCH_ARMv5TE&t;6
DECL|macro|CPU_ARCH_ARMv6
mdefine_line|#define CPU_ARCH_ARMv6&t;&t;7
r_extern
r_int
id|cpu_architecture
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
DECL|macro|read_barrier_depends
mdefine_line|#define read_barrier_depends() do { } while(0)
DECL|macro|set_mb
mdefine_line|#define set_mb(var, value)  do { var = value; mb(); } while (0)
DECL|macro|set_wmb
mdefine_line|#define set_wmb(var, value) do { var = value; wmb(); } while (0)
DECL|macro|nop
mdefine_line|#define nop() __asm__ __volatile__(&quot;mov&bslash;tr0,r0&bslash;t@ nop&bslash;n&bslash;t&quot;);
DECL|macro|prepare_to_switch
mdefine_line|#define prepare_to_switch()    do { } while(0)
multiline_comment|/*&n; * switch_to(prev, next) should switch from task `prev&squot; to `next&squot;&n; * `prev&squot; will never be the same as `next&squot;.&n; * The `mb&squot; is to tell GCC not to cache `current&squot; across this call.&n; */
r_struct
id|thread_info
suffix:semicolon
r_struct
id|task_struct
suffix:semicolon
r_extern
r_struct
id|task_struct
op_star
id|__switch_to
c_func
(paren
r_struct
id|task_struct
op_star
comma
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
mdefine_line|#define switch_to(prev,next,last)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;last = __switch_to(prev,prev-&gt;thread_info,next-&gt;thread_info);&t;&bslash;&n;&t;&t;mb();&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;} while (0)
macro_line|#ifdef CONFIG_SMP
macro_line|#error SMP not supported
DECL|macro|smp_mb
mdefine_line|#define smp_mb()&t;&t;mb()
DECL|macro|smp_rmb
mdefine_line|#define smp_rmb()&t;&t;rmb()
DECL|macro|smp_wmb
mdefine_line|#define smp_wmb()&t;&t;wmb()
DECL|macro|smp_read_barrier_depends
mdefine_line|#define smp_read_barrier_depends()&t;&t;read_barrier_depends()
macro_line|#else
DECL|macro|smp_mb
mdefine_line|#define smp_mb()&t;&t;barrier()
DECL|macro|smp_rmb
mdefine_line|#define smp_rmb()&t;&t;barrier()
DECL|macro|smp_wmb
mdefine_line|#define smp_wmb()&t;&t;barrier()
DECL|macro|smp_read_barrier_depends
mdefine_line|#define smp_read_barrier_depends()&t;&t;do { } while(0)
DECL|macro|clf
mdefine_line|#define clf()&t;&t;&t;__clf()
DECL|macro|stf
mdefine_line|#define stf()&t;&t;&t;__stf()
DECL|macro|irqs_disabled
mdefine_line|#define irqs_disabled()&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long flags;&t;&t;&bslash;&n;&t;local_save_flags(flags);&t;&bslash;&n;&t;flags &amp; PSR_I_BIT;&t;&t;&bslash;&n;})
macro_line|#endif /* CONFIG_SMP */
macro_line|#endif /* __KERNEL__ */
macro_line|#endif
eof
