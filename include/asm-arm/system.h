macro_line|#ifndef __ASM_ARM_SYSTEM_H
DECL|macro|__ASM_ARM_SYSTEM_H
mdefine_line|#define __ASM_ARM_SYSTEM_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
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
DECL|macro|CPU_ARCH_ARMv5TEJ
mdefine_line|#define CPU_ARCH_ARMv5TEJ&t;7
DECL|macro|CPU_ARCH_ARMv6
mdefine_line|#define CPU_ARCH_ARMv6&t;&t;8
multiline_comment|/*&n; * CR1 bits (CP#15 CR1)&n; */
DECL|macro|CR_M
mdefine_line|#define CR_M&t;(1 &lt;&lt; 0)&t;/* MMU enable&t;&t;&t;&t;*/
DECL|macro|CR_A
mdefine_line|#define CR_A&t;(1 &lt;&lt; 1)&t;/* Alignment abort enable&t;&t;*/
DECL|macro|CR_C
mdefine_line|#define CR_C&t;(1 &lt;&lt; 2)&t;/* Dcache enable&t;&t;&t;*/
DECL|macro|CR_W
mdefine_line|#define CR_W&t;(1 &lt;&lt; 3)&t;/* Write buffer enable&t;&t;&t;*/
DECL|macro|CR_P
mdefine_line|#define CR_P&t;(1 &lt;&lt; 4)&t;/* 32-bit exception handler&t;&t;*/
DECL|macro|CR_D
mdefine_line|#define CR_D&t;(1 &lt;&lt; 5)&t;/* 32-bit data address range&t;&t;*/
DECL|macro|CR_L
mdefine_line|#define CR_L&t;(1 &lt;&lt; 6)&t;/* Implementation defined&t;&t;*/
DECL|macro|CR_B
mdefine_line|#define CR_B&t;(1 &lt;&lt; 7)&t;/* Big endian&t;&t;&t;&t;*/
DECL|macro|CR_S
mdefine_line|#define CR_S&t;(1 &lt;&lt; 8)&t;/* System MMU protection&t;&t;*/
DECL|macro|CR_R
mdefine_line|#define CR_R&t;(1 &lt;&lt; 9)&t;/* ROM MMU protection&t;&t;&t;*/
DECL|macro|CR_F
mdefine_line|#define CR_F&t;(1 &lt;&lt; 10)&t;/* Implementation defined&t;&t;*/
DECL|macro|CR_Z
mdefine_line|#define CR_Z&t;(1 &lt;&lt; 11)&t;/* Implementation defined&t;&t;*/
DECL|macro|CR_I
mdefine_line|#define CR_I&t;(1 &lt;&lt; 12)&t;/* Icache enable&t;&t;&t;*/
DECL|macro|CR_V
mdefine_line|#define CR_V&t;(1 &lt;&lt; 13)&t;/* Vectors relocated to 0xffff0000&t;*/
DECL|macro|CR_RR
mdefine_line|#define CR_RR&t;(1 &lt;&lt; 14)&t;/* Round Robin cache replacement&t;*/
DECL|macro|CR_L4
mdefine_line|#define CR_L4&t;(1 &lt;&lt; 15)&t;/* LDR pc can set T bit&t;&t;&t;*/
DECL|macro|CR_DT
mdefine_line|#define CR_DT&t;(1 &lt;&lt; 16)
DECL|macro|CR_IT
mdefine_line|#define CR_IT&t;(1 &lt;&lt; 18)
DECL|macro|CR_ST
mdefine_line|#define CR_ST&t;(1 &lt;&lt; 19)
DECL|macro|CR_FI
mdefine_line|#define CR_FI&t;(1 &lt;&lt; 21)&t;/* Fast interrupt (lower latency mode)&t;*/
DECL|macro|CR_U
mdefine_line|#define CR_U&t;(1 &lt;&lt; 22)&t;/* Unaligned access operation&t;&t;*/
DECL|macro|CR_XP
mdefine_line|#define CR_XP&t;(1 &lt;&lt; 23)&t;/* Extended page tables&t;&t;&t;*/
DECL|macro|CR_VE
mdefine_line|#define CR_VE&t;(1 &lt;&lt; 24)&t;/* Vectored interrupts&t;&t;&t;*/
DECL|macro|CPUID_ID
mdefine_line|#define CPUID_ID&t;0
DECL|macro|CPUID_CACHETYPE
mdefine_line|#define CPUID_CACHETYPE&t;1
DECL|macro|CPUID_TCM
mdefine_line|#define CPUID_TCM&t;2
DECL|macro|CPUID_TLBTYPE
mdefine_line|#define CPUID_TLBTYPE&t;3
DECL|macro|read_cpuid
mdefine_line|#define read_cpuid(reg)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;unsigned int __val;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;asm(&quot;mrc&t;p15, 0, %0, c0, c0, &quot; __stringify(reg)&t;&bslash;&n;&t;&t;    : &quot;=r&quot; (__val)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;    :&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;    : &quot;cc&quot;);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__val;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;})
multiline_comment|/*&n; * This is used to ensure the compiler did actually allocate the register we&n; * asked it for some inline assembly sequences.  Apparently we can&squot;t trust&n; * the compiler from one version to another so a bit of paranoia won&squot;t hurt.&n; * This string is meant to be concatenated with the inline asm string and&n; * will cause compilation to stop on mismatch.&n; * (for details, see gcc PR 15089)&n; */
DECL|macro|__asmeq
mdefine_line|#define __asmeq(x, y)  &quot;.ifnc &quot; x &quot;,&quot; y &quot; ; .err ; .endif&bslash;n&bslash;t&quot;
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;linux/linkage.h&gt;
r_struct
id|thread_info
suffix:semicolon
r_struct
id|task_struct
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
r_extern
r_int
id|cpu_architecture
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|set_cr
mdefine_line|#define set_cr(x)&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&bslash;&n;&t;&quot;mcr&t;p15, 0, %0, c1, c0, 0&t;@ set CR&quot;&t;&bslash;&n;&t;: : &quot;r&quot; (x) : &quot;cc&quot;)
DECL|macro|get_cr
mdefine_line|#define get_cr()&t;&t;&t;&t;&t;&bslash;&n;&t;({&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned int __val;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&bslash;&n;&t;&quot;mrc&t;p15, 0, %0, c1, c0, 0&t;@ get CR&quot;&t;&bslash;&n;&t;: &quot;=r&quot; (__val) : : &quot;cc&quot;);&t;&t;&t;&bslash;&n;&t;__val;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;})
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
DECL|macro|UDBG_UNDEFINED
mdefine_line|#define UDBG_UNDEFINED&t;(1 &lt;&lt; 0)
DECL|macro|UDBG_SYSCALL
mdefine_line|#define UDBG_SYSCALL&t;(1 &lt;&lt; 1)
DECL|macro|UDBG_BADABORT
mdefine_line|#define UDBG_BADABORT&t;(1 &lt;&lt; 2)
DECL|macro|UDBG_SEGV
mdefine_line|#define UDBG_SEGV&t;(1 &lt;&lt; 3)
DECL|macro|UDBG_BUS
mdefine_line|#define UDBG_BUS&t;(1 &lt;&lt; 4)
r_extern
r_int
r_int
id|user_debug
suffix:semicolon
macro_line|#if __LINUX_ARM_ARCH__ &gt;= 4
DECL|macro|vectors_high
mdefine_line|#define vectors_high()&t;(cr_alignment &amp; CR_V)
macro_line|#else
DECL|macro|vectors_high
mdefine_line|#define vectors_high()&t;(0)
macro_line|#endif
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
macro_line|#ifdef CONFIG_SMP
multiline_comment|/*&n; * Define our own context switch locking.  This allows us to enable&n; * interrupts over the context switch, otherwise we end up with high&n; * interrupt latency.  The real problem area is switch_mm() which may&n; * do a full cache flush.&n; */
DECL|macro|prepare_arch_switch
mdefine_line|#define prepare_arch_switch(rq,next)&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;spin_lock(&amp;(next)-&gt;switch_lock);&t;&t;&t;&t;&bslash;&n;&t;spin_unlock_irq(&amp;(rq)-&gt;lock);&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|finish_arch_switch
mdefine_line|#define finish_arch_switch(rq,prev)&t;&t;&t;&t;&t;&bslash;&n;&t;spin_unlock(&amp;(prev)-&gt;switch_lock)
DECL|macro|task_running
mdefine_line|#define task_running(rq,p)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;((rq)-&gt;curr == (p) || spin_is_locked(&amp;(p)-&gt;switch_lock))
macro_line|#else
multiline_comment|/*&n; * Our UP-case is more simple, but we assume knowledge of how&n; * spin_unlock_irq() and friends are implemented.  This avoids&n; * us needlessly decrementing and incrementing the preempt count.&n; */
DECL|macro|prepare_arch_switch
mdefine_line|#define prepare_arch_switch(rq,next)&t;local_irq_enable()
DECL|macro|finish_arch_switch
mdefine_line|#define finish_arch_switch(rq,prev)&t;spin_unlock(&amp;(rq)-&gt;lock)
DECL|macro|task_running
mdefine_line|#define task_running(rq,p)&t;&t;((rq)-&gt;curr == (p))
macro_line|#endif
multiline_comment|/*&n; * switch_to(prev, next) should switch from task `prev&squot; to `next&squot;&n; * `prev&squot; will never be the same as `next&squot;.  schedule() itself&n; * contains the memory barrier to tell GCC not to cache `current&squot;.&n; */
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
mdefine_line|#define switch_to(prev,next,last)&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;last = __switch_to(prev,prev-&gt;thread_info,next-&gt;thread_info);&t;&bslash;&n;} while (0)
multiline_comment|/*&n; * CPU interrupt mask handling.&n; */
macro_line|#if __LINUX_ARM_ARCH__ &gt;= 6
DECL|macro|local_irq_save
mdefine_line|#define local_irq_save(x)&t;&t;&t;&t;&t;&bslash;&n;&t;({&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;mrs&t;%0, cpsr&t;&t;@ local_irq_save&bslash;n&quot;&t;&bslash;&n;&t;&quot;cpsid&t;i&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;=r&quot; (x) : : &quot;memory&quot;, &quot;cc&quot;);&t;&t;&t;&t;&bslash;&n;&t;})
DECL|macro|local_irq_enable
mdefine_line|#define local_irq_enable()  __asm__(&quot;cpsie i&t;@ __sti&quot; : : : &quot;memory&quot;, &quot;cc&quot;)
DECL|macro|local_irq_disable
mdefine_line|#define local_irq_disable() __asm__(&quot;cpsid i&t;@ __cli&quot; : : : &quot;memory&quot;, &quot;cc&quot;)
DECL|macro|local_fiq_enable
mdefine_line|#define local_fiq_enable()  __asm__(&quot;cpsie f&t;@ __stf&quot; : : : &quot;memory&quot;, &quot;cc&quot;)
DECL|macro|local_fiq_disable
mdefine_line|#define local_fiq_disable() __asm__(&quot;cpsid f&t;@ __clf&quot; : : : &quot;memory&quot;, &quot;cc&quot;)
macro_line|#else
multiline_comment|/*&n; * Save the current interrupt enable state &amp; disable IRQs&n; */
DECL|macro|local_irq_save
mdefine_line|#define local_irq_save(x)&t;&t;&t;&t;&t;&bslash;&n;&t;({&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;unsigned long temp;&t;&t;&t;&t;&bslash;&n;&t;&t;(void) (&amp;temp == &amp;x);&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;mrs&t;%0, cpsr&t;&t;@ local_irq_save&bslash;n&quot;&t;&bslash;&n;&quot;&t;orr&t;%1, %0, #128&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&quot;&t;msr&t;cpsr_c, %1&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;=r&quot; (x), &quot;=r&quot; (temp)&t;&t;&t;&t;&t;&bslash;&n;&t;:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;memory&quot;, &quot;cc&quot;);&t;&t;&t;&t;&t;&bslash;&n;&t;})
multiline_comment|/*&n; * Enable IRQs&n; */
DECL|macro|local_irq_enable
mdefine_line|#define local_irq_enable()&t;&t;&t;&t;&t;&bslash;&n;&t;({&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;unsigned long temp;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;mrs&t;%0, cpsr&t;&t;@ local_irq_enable&bslash;n&quot;&t;&bslash;&n;&quot;&t;bic&t;%0, %0, #128&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&quot;&t;msr&t;cpsr_c, %0&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;=r&quot; (temp)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;memory&quot;, &quot;cc&quot;);&t;&t;&t;&t;&t;&bslash;&n;&t;})
multiline_comment|/*&n; * Disable IRQs&n; */
DECL|macro|local_irq_disable
mdefine_line|#define local_irq_disable()&t;&t;&t;&t;&t;&bslash;&n;&t;({&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;unsigned long temp;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;mrs&t;%0, cpsr&t;&t;@ local_irq_disable&bslash;n&quot;&t;&bslash;&n;&quot;&t;orr&t;%0, %0, #128&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&quot;&t;msr&t;cpsr_c, %0&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;=r&quot; (temp)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;memory&quot;, &quot;cc&quot;);&t;&t;&t;&t;&t;&bslash;&n;&t;})
multiline_comment|/*&n; * Enable FIQs&n; */
DECL|macro|local_fiq_enable
mdefine_line|#define local_fiq_enable()&t;&t;&t;&t;&t;&bslash;&n;&t;({&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;unsigned long temp;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;mrs&t;%0, cpsr&t;&t;@ stf&bslash;n&quot;&t;&t;&bslash;&n;&quot;&t;bic&t;%0, %0, #64&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&quot;&t;msr&t;cpsr_c, %0&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;=r&quot; (temp)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;memory&quot;, &quot;cc&quot;);&t;&t;&t;&t;&t;&bslash;&n;&t;})
multiline_comment|/*&n; * Disable FIQs&n; */
DECL|macro|local_fiq_disable
mdefine_line|#define local_fiq_disable()&t;&t;&t;&t;&t;&bslash;&n;&t;({&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;unsigned long temp;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;mrs&t;%0, cpsr&t;&t;@ clf&bslash;n&quot;&t;&t;&bslash;&n;&quot;&t;orr&t;%0, %0, #64&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&quot;&t;msr&t;cpsr_c, %0&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;=r&quot; (temp)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;memory&quot;, &quot;cc&quot;);&t;&t;&t;&t;&t;&bslash;&n;&t;})
macro_line|#endif
multiline_comment|/*&n; * Save the current interrupt enable state.&n; */
DECL|macro|local_save_flags
mdefine_line|#define local_save_flags(x)&t;&t;&t;&t;&t;&bslash;&n;&t;({&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;mrs&t;%0, cpsr&t;&t;@ local_save_flags&quot;&t;&bslash;&n;&t;: &quot;=r&quot; (x) : : &quot;memory&quot;, &quot;cc&quot;);&t;&t;&t;&t;&bslash;&n;&t;})
multiline_comment|/*&n; * restore saved IRQ &amp; FIQ state&n; */
DECL|macro|local_irq_restore
mdefine_line|#define local_irq_restore(x)&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;msr&t;cpsr_c, %0&t;&t;@ local_irq_restore&bslash;n&quot;&t;&bslash;&n;&t;:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;r&quot; (x)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;memory&quot;, &quot;cc&quot;)
DECL|macro|irqs_disabled
mdefine_line|#define irqs_disabled()&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long flags;&t;&t;&bslash;&n;&t;local_save_flags(flags);&t;&bslash;&n;&t;flags &amp; PSR_I_BIT;&t;&t;&bslash;&n;})
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
macro_line|#if defined(CONFIG_CPU_SA1100) || defined(CONFIG_CPU_SA110)
multiline_comment|/*&n; * On the StrongARM, &quot;swp&quot; is terminally broken since it bypasses the&n; * cache totally.  This means that the cache becomes inconsistent, and,&n; * since we use normal loads/stores as well, this is really bad.&n; * Typically, this causes oopsen in filp_close, but could have other,&n; * more disasterous effects.  There are two work-arounds:&n; *  1. Disable interrupts and emulate the atomic swap&n; *  2. Clean the cache, perform atomic swap, flush the cache&n; *&n; * We choose (1) since its the &quot;easiest&quot; to achieve here and is not&n; * dependent on the processor type.&n; */
DECL|macro|swp_is_buggy
mdefine_line|#define swp_is_buggy
macro_line|#endif
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
id|local_irq_save
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
id|local_irq_restore
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
id|local_irq_save
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
id|local_irq_restore
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
l_string|&quot;=&amp;r&quot;
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
comma
l_string|&quot;cc&quot;
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
l_string|&quot;=&amp;r&quot;
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
comma
l_string|&quot;cc&quot;
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
comma
id|ret
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_SMP */
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif /* __KERNEL__ */
macro_line|#endif
eof
