multiline_comment|/*&n; *  include/asm-s390/system.h&n; *&n; *  S390 version&n; *    Copyright (C) 1999 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Martin Schwidefsky (schwidefsky@de.ibm.com),&n; *&n; *  Derived from &quot;include/asm-i386/system.h&quot;&n; */
macro_line|#ifndef __ASM_SYSTEM_H
DECL|macro|__ASM_SYSTEM_H
mdefine_line|#define __ASM_SYSTEM_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#ifdef __KERNEL__
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
r_void
op_star
comma
r_void
op_star
)paren
suffix:semicolon
macro_line|#ifdef __s390x__
DECL|macro|__FLAG_SHIFT
mdefine_line|#define __FLAG_SHIFT 56
macro_line|#else /* ! __s390x__ */
DECL|macro|__FLAG_SHIFT
mdefine_line|#define __FLAG_SHIFT 24
macro_line|#endif /* ! __s390x__ */
DECL|function|save_fp_regs
r_static
r_inline
r_void
id|save_fp_regs
c_func
(paren
id|s390_fp_regs
op_star
id|fpregs
)paren
(brace
id|asm
r_volatile
(paren
l_string|&quot;   std   0,8(%1)&bslash;n&quot;
l_string|&quot;   std   2,24(%1)&bslash;n&quot;
l_string|&quot;   std   4,40(%1)&bslash;n&quot;
l_string|&quot;   std   6,56(%1)&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
id|fpregs
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|fpregs
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|fpregs
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|MACHINE_HAS_IEEE
)paren
r_return
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;   stfpc 0(%1)&bslash;n&quot;
l_string|&quot;   std   1,16(%1)&bslash;n&quot;
l_string|&quot;   std   3,32(%1)&bslash;n&quot;
l_string|&quot;   std   5,48(%1)&bslash;n&quot;
l_string|&quot;   std   7,64(%1)&bslash;n&quot;
l_string|&quot;   std   8,72(%1)&bslash;n&quot;
l_string|&quot;   std   9,80(%1)&bslash;n&quot;
l_string|&quot;   std   10,88(%1)&bslash;n&quot;
l_string|&quot;   std   11,96(%1)&bslash;n&quot;
l_string|&quot;   std   12,104(%1)&bslash;n&quot;
l_string|&quot;   std   13,112(%1)&bslash;n&quot;
l_string|&quot;   std   14,120(%1)&bslash;n&quot;
l_string|&quot;   std   15,128(%1)&bslash;n&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
id|fpregs
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|fpregs
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|fpregs
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
DECL|function|restore_fp_regs
r_static
r_inline
r_void
id|restore_fp_regs
c_func
(paren
id|s390_fp_regs
op_star
id|fpregs
)paren
(brace
id|asm
r_volatile
(paren
l_string|&quot;   ld    0,8(%0)&bslash;n&quot;
l_string|&quot;   ld    2,24(%0)&bslash;n&quot;
l_string|&quot;   ld    4,40(%0)&bslash;n&quot;
l_string|&quot;   ld    6,56(%0)&quot;
suffix:colon
suffix:colon
l_string|&quot;a&quot;
(paren
id|fpregs
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|fpregs
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|MACHINE_HAS_IEEE
)paren
r_return
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;   lfpc  0(%0)&bslash;n&quot;
l_string|&quot;   ld    1,16(%0)&bslash;n&quot;
l_string|&quot;   ld    3,32(%0)&bslash;n&quot;
l_string|&quot;   ld    5,48(%0)&bslash;n&quot;
l_string|&quot;   ld    7,64(%0)&bslash;n&quot;
l_string|&quot;   ld    8,72(%0)&bslash;n&quot;
l_string|&quot;   ld    9,80(%0)&bslash;n&quot;
l_string|&quot;   ld    10,88(%0)&bslash;n&quot;
l_string|&quot;   ld    11,96(%0)&bslash;n&quot;
l_string|&quot;   ld    12,104(%0)&bslash;n&quot;
l_string|&quot;   ld    13,112(%0)&bslash;n&quot;
l_string|&quot;   ld    14,120(%0)&bslash;n&quot;
l_string|&quot;   ld    15,128(%0)&bslash;n&quot;
suffix:colon
suffix:colon
l_string|&quot;a&quot;
(paren
id|fpregs
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|fpregs
)paren
)paren
suffix:semicolon
)brace
DECL|function|save_access_regs
r_static
r_inline
r_void
id|save_access_regs
c_func
(paren
r_int
r_int
op_star
id|acrs
)paren
(brace
id|asm
r_volatile
(paren
l_string|&quot;stam 0,15,0(%0)&quot;
suffix:colon
suffix:colon
l_string|&quot;a&quot;
(paren
id|acrs
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
DECL|function|restore_access_regs
r_static
r_inline
r_void
id|restore_access_regs
c_func
(paren
r_int
r_int
op_star
id|acrs
)paren
(brace
id|asm
r_volatile
(paren
l_string|&quot;lam 0,15,0(%0)&quot;
suffix:colon
suffix:colon
l_string|&quot;a&quot;
(paren
id|acrs
)paren
)paren
suffix:semicolon
)brace
DECL|macro|switch_to
mdefine_line|#define switch_to(prev,next,last) do {&t;&t;&t;&t;&t;     &bslash;&n;&t;if (prev == next)&t;&t;&t;&t;&t;&t;     &bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;     &bslash;&n;&t;save_fp_regs(&amp;prev-&gt;thread.fp_regs);&t;&t;&t;&t;     &bslash;&n;&t;restore_fp_regs(&amp;next-&gt;thread.fp_regs);&t;&t;&t;&t;     &bslash;&n;&t;save_access_regs(&amp;prev-&gt;thread.acrs[0]);&t;&t;&t;     &bslash;&n;&t;restore_access_regs(&amp;next-&gt;thread.acrs[0]);&t;&t;&t;     &bslash;&n;&t;prev = __switch_to(prev,next);&t;&t;&t;&t;&t;     &bslash;&n;} while (0)
DECL|macro|prepare_arch_switch
mdefine_line|#define prepare_arch_switch(rq, next)&t;do { } while(0)
DECL|macro|task_running
mdefine_line|#define task_running(rq, p)&t;&t;((rq)-&gt;curr == (p))
macro_line|#ifdef CONFIG_VIRT_CPU_ACCOUNTING
r_extern
r_void
id|account_user_vtime
c_func
(paren
r_struct
id|task_struct
op_star
)paren
suffix:semicolon
r_extern
r_void
id|account_system_vtime
c_func
(paren
r_struct
id|task_struct
op_star
)paren
suffix:semicolon
DECL|macro|finish_arch_switch
mdefine_line|#define finish_arch_switch(rq, prev) do {&t;&t;&t;&t;     &bslash;&n;&t;set_fs(current-&gt;thread.mm_segment);&t;&t;&t;&t;     &bslash;&n;&t;spin_unlock(&amp;(rq)-&gt;lock);&t;&t;&t;&t;&t;     &bslash;&n;&t;account_system_vtime(prev);&t;&t;&t;&t;&t;     &bslash;&n;&t;local_irq_enable();&t;&t;&t;&t;&t;&t;     &bslash;&n;} while (0)
macro_line|#else
DECL|macro|account_system_vtime
mdefine_line|#define account_system_vtime(prev)
DECL|macro|finish_arch_switch
mdefine_line|#define finish_arch_switch(rq, prev) do {&t;&t;&t;&t;     &bslash;&n;&t;set_fs(current-&gt;thread.mm_segment);&t;&t;&t;&t;     &bslash;&n;&t;spin_unlock_irq(&amp;(rq)-&gt;lock);&t;&t;&t;&t;&t;     &bslash;&n;} while (0)
macro_line|#endif
DECL|macro|nop
mdefine_line|#define nop() __asm__ __volatile__ (&quot;nop&quot;)
DECL|macro|xchg
mdefine_line|#define xchg(ptr,x) &bslash;&n;  ((__typeof__(*(ptr)))__xchg((unsigned long)(x),(void *)(ptr),sizeof(*(ptr))))
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
r_void
op_star
id|ptr
comma
r_int
id|size
)paren
(brace
r_int
r_int
id|addr
comma
id|old
suffix:semicolon
r_int
id|shift
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
id|addr
op_assign
(paren
r_int
r_int
)paren
id|ptr
suffix:semicolon
id|shift
op_assign
(paren
l_int|3
op_xor
(paren
id|addr
op_amp
l_int|3
)paren
)paren
op_lshift
l_int|3
suffix:semicolon
id|addr
op_xor_assign
id|addr
op_amp
l_int|3
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;    l   %0,0(%4)&bslash;n&quot;
l_string|&quot;0:  lr  0,%0&bslash;n&quot;
l_string|&quot;    nr  0,%3&bslash;n&quot;
l_string|&quot;    or  0,%2&bslash;n&quot;
l_string|&quot;    cs  %0,0,0(%4)&bslash;n&quot;
l_string|&quot;    jl  0b&bslash;n&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|old
)paren
comma
l_string|&quot;=m&quot;
(paren
op_star
(paren
r_int
op_star
)paren
id|addr
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|x
op_lshift
id|shift
)paren
comma
l_string|&quot;d&quot;
(paren
op_complement
(paren
l_int|255
op_lshift
id|shift
)paren
)paren
comma
l_string|&quot;a&quot;
(paren
id|addr
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
(paren
r_int
op_star
)paren
id|addr
)paren
suffix:colon
l_string|&quot;memory&quot;
comma
l_string|&quot;cc&quot;
comma
l_string|&quot;0&quot;
)paren
suffix:semicolon
id|x
op_assign
id|old
op_rshift
id|shift
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|addr
op_assign
(paren
r_int
r_int
)paren
id|ptr
suffix:semicolon
id|shift
op_assign
(paren
l_int|2
op_xor
(paren
id|addr
op_amp
l_int|2
)paren
)paren
op_lshift
l_int|3
suffix:semicolon
id|addr
op_xor_assign
id|addr
op_amp
l_int|2
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;    l   %0,0(%4)&bslash;n&quot;
l_string|&quot;0:  lr  0,%0&bslash;n&quot;
l_string|&quot;    nr  0,%3&bslash;n&quot;
l_string|&quot;    or  0,%2&bslash;n&quot;
l_string|&quot;    cs  %0,0,0(%4)&bslash;n&quot;
l_string|&quot;    jl  0b&bslash;n&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|old
)paren
comma
l_string|&quot;=m&quot;
(paren
op_star
(paren
r_int
op_star
)paren
id|addr
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|x
op_lshift
id|shift
)paren
comma
l_string|&quot;d&quot;
(paren
op_complement
(paren
l_int|65535
op_lshift
id|shift
)paren
)paren
comma
l_string|&quot;a&quot;
(paren
id|addr
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
(paren
r_int
op_star
)paren
id|addr
)paren
suffix:colon
l_string|&quot;memory&quot;
comma
l_string|&quot;cc&quot;
comma
l_string|&quot;0&quot;
)paren
suffix:semicolon
id|x
op_assign
id|old
op_rshift
id|shift
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|asm
r_volatile
(paren
l_string|&quot;    l   %0,0(%3)&bslash;n&quot;
l_string|&quot;0:  cs  %0,%2,0(%3)&bslash;n&quot;
l_string|&quot;    jl  0b&bslash;n&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|old
)paren
comma
l_string|&quot;=m&quot;
(paren
op_star
(paren
r_int
op_star
)paren
id|ptr
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|x
)paren
comma
l_string|&quot;a&quot;
(paren
id|ptr
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
(paren
r_int
op_star
)paren
id|ptr
)paren
suffix:colon
l_string|&quot;memory&quot;
comma
l_string|&quot;cc&quot;
)paren
suffix:semicolon
id|x
op_assign
id|old
suffix:semicolon
r_break
suffix:semicolon
macro_line|#ifdef __s390x__
r_case
l_int|8
suffix:colon
id|asm
r_volatile
(paren
l_string|&quot;    lg  %0,0(%3)&bslash;n&quot;
l_string|&quot;0:  csg %0,%2,0(%3)&bslash;n&quot;
l_string|&quot;    jl  0b&bslash;n&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|old
)paren
comma
l_string|&quot;=m&quot;
(paren
op_star
(paren
r_int
op_star
)paren
id|ptr
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|x
)paren
comma
l_string|&quot;a&quot;
(paren
id|ptr
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
(paren
r_int
op_star
)paren
id|ptr
)paren
suffix:colon
l_string|&quot;memory&quot;
comma
l_string|&quot;cc&quot;
)paren
suffix:semicolon
id|x
op_assign
id|old
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif /* __s390x__ */
)brace
r_return
id|x
suffix:semicolon
)brace
multiline_comment|/*&n; * Atomic compare and exchange.  Compare OLD with MEM, if identical,&n; * store NEW in MEM.  Return the initial value in MEM.  Success is&n; * indicated by comparing RETURN with OLD.&n; */
DECL|macro|__HAVE_ARCH_CMPXCHG
mdefine_line|#define __HAVE_ARCH_CMPXCHG 1
DECL|macro|cmpxchg
mdefine_line|#define cmpxchg(ptr,o,n)&bslash;&n;&t;((__typeof__(*(ptr)))__cmpxchg((ptr),(unsigned long)(o),&bslash;&n;&t;&t;&t;&t;&t;(unsigned long)(n),sizeof(*(ptr))))
r_static
r_inline
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
r_int
r_int
id|addr
comma
id|prev
comma
id|tmp
suffix:semicolon
r_int
id|shift
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
id|addr
op_assign
(paren
r_int
r_int
)paren
id|ptr
suffix:semicolon
id|shift
op_assign
(paren
l_int|3
op_xor
(paren
id|addr
op_amp
l_int|3
)paren
)paren
op_lshift
l_int|3
suffix:semicolon
id|addr
op_xor_assign
id|addr
op_amp
l_int|3
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;    l   %0,0(%4)&bslash;n&quot;
l_string|&quot;0:  nr  %0,%5&bslash;n&quot;
l_string|&quot;    lr  %1,%0&bslash;n&quot;
l_string|&quot;    or  %0,%2&bslash;n&quot;
l_string|&quot;    or  %1,%3&bslash;n&quot;
l_string|&quot;    cs  %0,%1,0(%4)&bslash;n&quot;
l_string|&quot;    jnl 1f&bslash;n&quot;
l_string|&quot;    xr  %1,%0&bslash;n&quot;
l_string|&quot;    nr  %1,%5&bslash;n&quot;
l_string|&quot;    jnz 0b&bslash;n&quot;
l_string|&quot;1:&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|prev
)paren
comma
l_string|&quot;=&amp;d&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|old
op_lshift
id|shift
)paren
comma
l_string|&quot;d&quot;
(paren
r_new
op_lshift
id|shift
)paren
comma
l_string|&quot;a&quot;
(paren
id|ptr
)paren
comma
l_string|&quot;d&quot;
(paren
op_complement
(paren
l_int|255
op_lshift
id|shift
)paren
)paren
suffix:colon
l_string|&quot;memory&quot;
comma
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
id|prev
op_rshift
id|shift
suffix:semicolon
r_case
l_int|2
suffix:colon
id|addr
op_assign
(paren
r_int
r_int
)paren
id|ptr
suffix:semicolon
id|shift
op_assign
(paren
l_int|2
op_xor
(paren
id|addr
op_amp
l_int|2
)paren
)paren
op_lshift
l_int|3
suffix:semicolon
id|addr
op_xor_assign
id|addr
op_amp
l_int|2
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;    l   %0,0(%4)&bslash;n&quot;
l_string|&quot;0:  nr  %0,%5&bslash;n&quot;
l_string|&quot;    lr  %1,%0&bslash;n&quot;
l_string|&quot;    or  %0,%2&bslash;n&quot;
l_string|&quot;    or  %1,%3&bslash;n&quot;
l_string|&quot;    cs  %0,%1,0(%4)&bslash;n&quot;
l_string|&quot;    jnl 1f&bslash;n&quot;
l_string|&quot;    xr  %1,%0&bslash;n&quot;
l_string|&quot;    nr  %1,%5&bslash;n&quot;
l_string|&quot;    jnz 0b&bslash;n&quot;
l_string|&quot;1:&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|prev
)paren
comma
l_string|&quot;=&amp;d&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|old
op_lshift
id|shift
)paren
comma
l_string|&quot;d&quot;
(paren
r_new
op_lshift
id|shift
)paren
comma
l_string|&quot;a&quot;
(paren
id|ptr
)paren
comma
l_string|&quot;d&quot;
(paren
op_complement
(paren
l_int|65535
op_lshift
id|shift
)paren
)paren
suffix:colon
l_string|&quot;memory&quot;
comma
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
id|prev
op_rshift
id|shift
suffix:semicolon
r_case
l_int|4
suffix:colon
id|asm
r_volatile
(paren
l_string|&quot;    cs  %0,%2,0(%3)&bslash;n&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|prev
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|old
)paren
comma
l_string|&quot;d&quot;
(paren
r_new
)paren
comma
l_string|&quot;a&quot;
(paren
id|ptr
)paren
suffix:colon
l_string|&quot;memory&quot;
comma
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
id|prev
suffix:semicolon
macro_line|#ifdef __s390x__
r_case
l_int|8
suffix:colon
id|asm
r_volatile
(paren
l_string|&quot;    csg %0,%2,0(%3)&bslash;n&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|prev
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|old
)paren
comma
l_string|&quot;d&quot;
(paren
r_new
)paren
comma
l_string|&quot;a&quot;
(paren
id|ptr
)paren
suffix:colon
l_string|&quot;memory&quot;
comma
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
id|prev
suffix:semicolon
macro_line|#endif /* __s390x__ */
)brace
r_return
id|old
suffix:semicolon
)brace
multiline_comment|/*&n; * Force strict CPU ordering.&n; * And yes, this is required on UP too when we&squot;re talking&n; * to devices.&n; *&n; * This is very similar to the ppc eieio/sync instruction in that is&n; * does a checkpoint syncronisation &amp; makes sure that &n; * all memory ops have completed wrt other CPU&squot;s ( see 7-15 POP  DJB ).&n; */
DECL|macro|eieio
mdefine_line|#define eieio()  __asm__ __volatile__ ( &quot;bcr 15,0&quot; : : : &quot;memory&quot; ) 
DECL|macro|SYNC_OTHER_CORES
macro_line|# define SYNC_OTHER_CORES(x)   eieio() 
DECL|macro|mb
mdefine_line|#define mb()    eieio()
DECL|macro|rmb
mdefine_line|#define rmb()   eieio()
DECL|macro|wmb
mdefine_line|#define wmb()   eieio()
DECL|macro|read_barrier_depends
mdefine_line|#define read_barrier_depends() do { } while(0)
DECL|macro|smp_mb
mdefine_line|#define smp_mb()       mb()
DECL|macro|smp_rmb
mdefine_line|#define smp_rmb()      rmb()
DECL|macro|smp_wmb
mdefine_line|#define smp_wmb()      wmb()
DECL|macro|smp_read_barrier_depends
mdefine_line|#define smp_read_barrier_depends()    read_barrier_depends()
DECL|macro|smp_mb__before_clear_bit
mdefine_line|#define smp_mb__before_clear_bit()     smp_mb()
DECL|macro|smp_mb__after_clear_bit
mdefine_line|#define smp_mb__after_clear_bit()      smp_mb()
DECL|macro|set_mb
mdefine_line|#define set_mb(var, value)      do { var = value; mb(); } while (0)
DECL|macro|set_wmb
mdefine_line|#define set_wmb(var, value)     do { var = value; wmb(); } while (0)
multiline_comment|/* interrupt control.. */
DECL|macro|local_irq_enable
mdefine_line|#define local_irq_enable() ({ &bslash;&n;        unsigned long  __dummy; &bslash;&n;        __asm__ __volatile__ ( &bslash;&n;                &quot;stosm 0(%1),0x03&quot; &bslash;&n;&t;&t;: &quot;=m&quot; (__dummy) : &quot;a&quot; (&amp;__dummy) : &quot;memory&quot; ); &bslash;&n;        })
DECL|macro|local_irq_disable
mdefine_line|#define local_irq_disable() ({ &bslash;&n;        unsigned long __flags; &bslash;&n;        __asm__ __volatile__ ( &bslash;&n;                &quot;stnsm 0(%1),0xfc&quot; : &quot;=m&quot; (__flags) : &quot;a&quot; (&amp;__flags) ); &bslash;&n;        __flags; &bslash;&n;        })
DECL|macro|local_save_flags
mdefine_line|#define local_save_flags(x) &bslash;&n;        __asm__ __volatile__(&quot;stosm 0(%1),0&quot; : &quot;=m&quot; (x) : &quot;a&quot; (&amp;x), &quot;m&quot; (x) )
DECL|macro|local_irq_restore
mdefine_line|#define local_irq_restore(x) &bslash;&n;        __asm__ __volatile__(&quot;ssm   0(%0)&quot; : : &quot;a&quot; (&amp;x), &quot;m&quot; (x) : &quot;memory&quot;)
DECL|macro|irqs_disabled
mdefine_line|#define irqs_disabled()&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long flags;&t;&t;&bslash;&n;&t;local_save_flags(flags);&t;&bslash;&n;        !((flags &gt;&gt; __FLAG_SHIFT) &amp; 3);&t;&bslash;&n;})
macro_line|#ifdef __s390x__
DECL|macro|__load_psw
mdefine_line|#define __load_psw(psw) &bslash;&n;        __asm__ __volatile__(&quot;lpswe 0(%0)&quot; : : &quot;a&quot; (&amp;psw), &quot;m&quot; (psw) : &quot;cc&quot; );
DECL|macro|__ctl_load
mdefine_line|#define __ctl_load(array, low, high) ({ &bslash;&n;&t;__asm__ __volatile__ ( &bslash;&n;&t;&t;&quot;   bras  1,0f&bslash;n&quot; &bslash;&n;                &quot;   lctlg 0,0,0(%0)&bslash;n&quot; &bslash;&n;&t;&t;&quot;0: ex    %1,0(1)&quot; &bslash;&n;&t;&t;: : &quot;a&quot; (&amp;array), &quot;a&quot; (((low)&lt;&lt;4)+(high)) : &quot;1&quot; ); &bslash;&n;&t;})
DECL|macro|__ctl_store
mdefine_line|#define __ctl_store(array, low, high) ({ &bslash;&n;&t;__asm__ __volatile__ ( &bslash;&n;&t;&t;&quot;   bras  1,0f&bslash;n&quot; &bslash;&n;&t;&t;&quot;   stctg 0,0,0(%1)&bslash;n&quot; &bslash;&n;&t;&t;&quot;0: ex    %2,0(1)&quot; &bslash;&n;&t;&t;: &quot;=m&quot; (array) : &quot;a&quot; (&amp;array), &quot;a&quot; (((low)&lt;&lt;4)+(high)) : &quot;1&quot; ); &bslash;&n;&t;})
DECL|macro|__ctl_set_bit
mdefine_line|#define __ctl_set_bit(cr, bit) ({ &bslash;&n;        __u8 __dummy[24]; &bslash;&n;        __asm__ __volatile__ ( &bslash;&n;                &quot;    bras  1,0f&bslash;n&quot;       /* skip indirect insns */ &bslash;&n;                &quot;    stctg 0,0,0(%1)&bslash;n&quot; &bslash;&n;                &quot;    lctlg 0,0,0(%1)&bslash;n&quot; &bslash;&n;                &quot;0:  ex    %2,0(1)&bslash;n&quot;    /* execute stctl */ &bslash;&n;                &quot;    lg    0,0(%1)&bslash;n&quot; &bslash;&n;                &quot;    ogr   0,%3&bslash;n&quot;       /* set the bit */ &bslash;&n;                &quot;    stg   0,0(%1)&bslash;n&quot; &bslash;&n;                &quot;1:  ex    %2,6(1)&quot;      /* execute lctl */ &bslash;&n;                : &quot;=m&quot; (__dummy) &bslash;&n;&t;&t;: &quot;a&quot; ((((unsigned long) &amp;__dummy) + 7) &amp; ~7UL), &bslash;&n;&t;&t;  &quot;a&quot; (cr*17), &quot;a&quot; (1L&lt;&lt;(bit)) &bslash;&n;                : &quot;cc&quot;, &quot;0&quot;, &quot;1&quot; ); &bslash;&n;        })
DECL|macro|__ctl_clear_bit
mdefine_line|#define __ctl_clear_bit(cr, bit) ({ &bslash;&n;        __u8 __dummy[16]; &bslash;&n;        __asm__ __volatile__ ( &bslash;&n;                &quot;    bras  1,0f&bslash;n&quot;       /* skip indirect insns */ &bslash;&n;                &quot;    stctg 0,0,0(%1)&bslash;n&quot; &bslash;&n;                &quot;    lctlg 0,0,0(%1)&bslash;n&quot; &bslash;&n;                &quot;0:  ex    %2,0(1)&bslash;n&quot;    /* execute stctl */ &bslash;&n;                &quot;    lg    0,0(%1)&bslash;n&quot; &bslash;&n;                &quot;    ngr   0,%3&bslash;n&quot;       /* set the bit */ &bslash;&n;                &quot;    stg   0,0(%1)&bslash;n&quot; &bslash;&n;                &quot;1:  ex    %2,6(1)&quot;      /* execute lctl */ &bslash;&n;                : &quot;=m&quot; (__dummy) &bslash;&n;&t;&t;: &quot;a&quot; ((((unsigned long) &amp;__dummy) + 7) &amp; ~7UL), &bslash;&n;&t;&t;  &quot;a&quot; (cr*17), &quot;a&quot; (~(1L&lt;&lt;(bit))) &bslash;&n;                : &quot;cc&quot;, &quot;0&quot;, &quot;1&quot; ); &bslash;&n;        })
macro_line|#else /* __s390x__ */
DECL|macro|__load_psw
mdefine_line|#define __load_psw(psw) &bslash;&n;&t;__asm__ __volatile__(&quot;lpsw 0(%0)&quot; : : &quot;a&quot; (&amp;psw) : &quot;cc&quot; );
DECL|macro|__ctl_load
mdefine_line|#define __ctl_load(array, low, high) ({ &bslash;&n;&t;__asm__ __volatile__ ( &bslash;&n;&t;&t;&quot;   bras  1,0f&bslash;n&quot; &bslash;&n;                &quot;   lctl 0,0,0(%0)&bslash;n&quot; &bslash;&n;&t;&t;&quot;0: ex    %1,0(1)&quot; &bslash;&n;&t;&t;: : &quot;a&quot; (&amp;array), &quot;a&quot; (((low)&lt;&lt;4)+(high)) : &quot;1&quot; ); &bslash;&n;&t;})
DECL|macro|__ctl_store
mdefine_line|#define __ctl_store(array, low, high) ({ &bslash;&n;&t;__asm__ __volatile__ ( &bslash;&n;&t;&t;&quot;   bras  1,0f&bslash;n&quot; &bslash;&n;&t;&t;&quot;   stctl 0,0,0(%1)&bslash;n&quot; &bslash;&n;&t;&t;&quot;0: ex    %2,0(1)&quot; &bslash;&n;&t;&t;: &quot;=m&quot; (array) : &quot;a&quot; (&amp;array), &quot;a&quot; (((low)&lt;&lt;4)+(high)): &quot;1&quot; ); &bslash;&n;&t;})
DECL|macro|__ctl_set_bit
mdefine_line|#define __ctl_set_bit(cr, bit) ({ &bslash;&n;        __u8 __dummy[16]; &bslash;&n;        __asm__ __volatile__ ( &bslash;&n;                &quot;    bras  1,0f&bslash;n&quot;       /* skip indirect insns */ &bslash;&n;                &quot;    stctl 0,0,0(%1)&bslash;n&quot; &bslash;&n;                &quot;    lctl  0,0,0(%1)&bslash;n&quot; &bslash;&n;                &quot;0:  ex    %2,0(1)&bslash;n&quot;    /* execute stctl */ &bslash;&n;                &quot;    l     0,0(%1)&bslash;n&quot; &bslash;&n;                &quot;    or    0,%3&bslash;n&quot;       /* set the bit */ &bslash;&n;                &quot;    st    0,0(%1)&bslash;n&quot; &bslash;&n;                &quot;1:  ex    %2,4(1)&quot;      /* execute lctl */ &bslash;&n;                : &quot;=m&quot; (__dummy) &bslash;&n;&t;&t;: &quot;a&quot; ((((unsigned long) &amp;__dummy) + 7) &amp; ~7UL), &bslash;&n;&t;&t;  &quot;a&quot; (cr*17), &quot;a&quot; (1&lt;&lt;(bit)) &bslash;&n;                : &quot;cc&quot;, &quot;0&quot;, &quot;1&quot; ); &bslash;&n;        })
DECL|macro|__ctl_clear_bit
mdefine_line|#define __ctl_clear_bit(cr, bit) ({ &bslash;&n;        __u8 __dummy[16]; &bslash;&n;        __asm__ __volatile__ ( &bslash;&n;                &quot;    bras  1,0f&bslash;n&quot;       /* skip indirect insns */ &bslash;&n;                &quot;    stctl 0,0,0(%1)&bslash;n&quot; &bslash;&n;                &quot;    lctl  0,0,0(%1)&bslash;n&quot; &bslash;&n;                &quot;0:  ex    %2,0(1)&bslash;n&quot;    /* execute stctl */ &bslash;&n;                &quot;    l     0,0(%1)&bslash;n&quot; &bslash;&n;                &quot;    nr    0,%3&bslash;n&quot;       /* set the bit */ &bslash;&n;                &quot;    st    0,0(%1)&bslash;n&quot; &bslash;&n;                &quot;1:  ex    %2,4(1)&quot;      /* execute lctl */ &bslash;&n;                : &quot;=m&quot; (__dummy) &bslash;&n;&t;&t;: &quot;a&quot; ((((unsigned long) &amp;__dummy) + 7) &amp; ~7UL), &bslash;&n;&t;&t;  &quot;a&quot; (cr*17), &quot;a&quot; (~(1&lt;&lt;(bit))) &bslash;&n;                : &quot;cc&quot;, &quot;0&quot;, &quot;1&quot; ); &bslash;&n;        })
macro_line|#endif /* __s390x__ */
multiline_comment|/* For spinlocks etc */
DECL|macro|local_irq_save
mdefine_line|#define local_irq_save(x)&t;((x) = local_irq_disable())
macro_line|#ifdef CONFIG_SMP
r_extern
r_void
id|smp_ctl_set_bit
c_func
(paren
r_int
id|cr
comma
r_int
id|bit
)paren
suffix:semicolon
r_extern
r_void
id|smp_ctl_clear_bit
c_func
(paren
r_int
id|cr
comma
r_int
id|bit
)paren
suffix:semicolon
DECL|macro|ctl_set_bit
mdefine_line|#define ctl_set_bit(cr, bit) smp_ctl_set_bit(cr, bit)
DECL|macro|ctl_clear_bit
mdefine_line|#define ctl_clear_bit(cr, bit) smp_ctl_clear_bit(cr, bit)
macro_line|#else
DECL|macro|ctl_set_bit
mdefine_line|#define ctl_set_bit(cr, bit) __ctl_set_bit(cr, bit)
DECL|macro|ctl_clear_bit
mdefine_line|#define ctl_clear_bit(cr, bit) __ctl_clear_bit(cr, bit)
macro_line|#endif /* CONFIG_SMP */
r_extern
r_void
(paren
op_star
id|_machine_restart
)paren
(paren
r_char
op_star
id|command
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|_machine_halt
)paren
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|_machine_power_off
)paren
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif
eof
