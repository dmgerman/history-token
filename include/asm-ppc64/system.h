macro_line|#ifndef __PPC64_SYSTEM_H
DECL|macro|__PPC64_SYSTEM_H
mdefine_line|#define __PPC64_SYSTEM_H
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/compiler.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/hw_irq.h&gt;
macro_line|#include &lt;asm/memory.h&gt;
multiline_comment|/*&n; * Memory barrier.&n; * The sync instruction guarantees that all memory accesses initiated&n; * by this processor have been performed (with respect to all other&n; * mechanisms that access memory).  The eieio instruction is a barrier&n; * providing an ordering (separately) for (a) cacheable stores and (b)&n; * loads and stores to non-cacheable memory (e.g. I/O devices).&n; *&n; * mb() prevents loads and stores being reordered across this point.&n; * rmb() prevents loads being reordered across this point.&n; * wmb() prevents stores being reordered across this point.&n; * read_barrier_depends() prevents data-dependent loads being reordered&n; *&t;across this point (nop on PPC).&n; *&n; * We can use the eieio instruction for wmb, but since it doesn&squot;t&n; * give any ordering guarantees about loads, we have to use the&n; * stronger but slower sync instruction for mb and rmb.&n; */
DECL|macro|mb
mdefine_line|#define mb()   __asm__ __volatile__ (&quot;sync&quot; : : : &quot;memory&quot;)
DECL|macro|rmb
mdefine_line|#define rmb()  __asm__ __volatile__ (&quot;lwsync&quot; : : : &quot;memory&quot;)
DECL|macro|wmb
mdefine_line|#define wmb()  __asm__ __volatile__ (&quot;eieio&quot; : : : &quot;memory&quot;)
DECL|macro|read_barrier_depends
mdefine_line|#define read_barrier_depends()  do { } while(0)
DECL|macro|set_mb
mdefine_line|#define set_mb(var, value)&t;do { var = value; mb(); } while (0)
DECL|macro|set_wmb
mdefine_line|#define set_wmb(var, value)&t;do { var = value; wmb(); } while (0)
macro_line|#ifdef CONFIG_SMP
DECL|macro|smp_mb
mdefine_line|#define smp_mb()&t;mb()
DECL|macro|smp_rmb
mdefine_line|#define smp_rmb()&t;rmb()
DECL|macro|smp_wmb
mdefine_line|#define smp_wmb()&t;wmb()
DECL|macro|smp_read_barrier_depends
mdefine_line|#define smp_read_barrier_depends()  read_barrier_depends()
macro_line|#else
DECL|macro|smp_mb
mdefine_line|#define smp_mb()&t;__asm__ __volatile__(&quot;&quot;: : :&quot;memory&quot;)
DECL|macro|smp_rmb
mdefine_line|#define smp_rmb()&t;__asm__ __volatile__(&quot;&quot;: : :&quot;memory&quot;)
DECL|macro|smp_wmb
mdefine_line|#define smp_wmb()&t;__asm__ __volatile__(&quot;&quot;: : :&quot;memory&quot;)
DECL|macro|smp_read_barrier_depends
mdefine_line|#define smp_read_barrier_depends()  do { } while(0)
macro_line|#endif /* CONFIG_SMP */
macro_line|#ifdef CONFIG_DEBUGGER
r_extern
r_int
(paren
op_star
id|__debugger
)paren
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_int
(paren
op_star
id|__debugger_bpt
)paren
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_int
(paren
op_star
id|__debugger_sstep
)paren
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_int
(paren
op_star
id|__debugger_iabr_match
)paren
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_int
(paren
op_star
id|__debugger_dabr_match
)paren
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_int
(paren
op_star
id|__debugger_fault_handler
)paren
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
DECL|macro|DEBUGGER_BOILERPLATE
mdefine_line|#define DEBUGGER_BOILERPLATE(__NAME) &bslash;&n;static inline int __NAME(struct pt_regs *regs) &bslash;&n;{ &bslash;&n;&t;if (unlikely(__ ## __NAME)) &bslash;&n;&t;&t;return __ ## __NAME(regs); &bslash;&n;&t;return 0; &bslash;&n;}
id|DEBUGGER_BOILERPLATE
c_func
(paren
id|debugger
)paren
id|DEBUGGER_BOILERPLATE
c_func
(paren
id|debugger_bpt
)paren
id|DEBUGGER_BOILERPLATE
c_func
(paren
id|debugger_sstep
)paren
id|DEBUGGER_BOILERPLATE
c_func
(paren
id|debugger_iabr_match
)paren
id|DEBUGGER_BOILERPLATE
c_func
(paren
id|debugger_dabr_match
)paren
id|DEBUGGER_BOILERPLATE
c_func
(paren
id|debugger_fault_handler
)paren
macro_line|#ifdef CONFIG_XMON
r_extern
r_void
id|xmon_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#else
DECL|macro|debugger
mdefine_line|#define debugger(regs)&t;&t;&t;0
DECL|macro|debugger_bpt
mdefine_line|#define debugger_bpt(regs)&t;&t;0
DECL|macro|debugger_sstep
mdefine_line|#define debugger_sstep(regs)&t;&t;0
DECL|macro|debugger_iabr_match
mdefine_line|#define debugger_iabr_match(regs)&t;0
DECL|macro|debugger_dabr_match
mdefine_line|#define debugger_dabr_match(regs)&t;0
DECL|macro|debugger_fault_handler
mdefine_line|#define debugger_fault_handler(regs)&t;0
macro_line|#endif
r_extern
r_void
id|show_regs
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_void
id|flush_instruction_cache
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|_get_PVR
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|giveup_fpu
c_func
(paren
r_struct
id|task_struct
op_star
)paren
suffix:semicolon
r_extern
r_void
id|disable_kernel_fp
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|enable_kernel_fp
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|giveup_altivec
c_func
(paren
r_struct
id|task_struct
op_star
)paren
suffix:semicolon
r_extern
r_void
id|disable_kernel_altivec
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|enable_kernel_altivec
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|cvt_fd
c_func
(paren
r_float
op_star
id|from
comma
r_float
op_star
id|to
comma
r_int
r_int
op_star
id|fpscr
)paren
suffix:semicolon
r_extern
r_void
id|cvt_df
c_func
(paren
r_float
op_star
id|from
comma
r_float
op_star
id|to
comma
r_int
r_int
op_star
id|fpscr
)paren
suffix:semicolon
r_extern
r_int
id|abs
c_func
(paren
r_int
)paren
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
id|task_struct
op_star
)paren
suffix:semicolon
DECL|macro|switch_to
mdefine_line|#define switch_to(prev, next, last)&t;((last) = __switch_to((prev), (next)))
r_struct
id|thread_struct
suffix:semicolon
r_extern
r_struct
id|task_struct
op_star
id|_switch
c_func
(paren
r_struct
id|thread_struct
op_star
id|prev
comma
r_struct
id|thread_struct
op_star
id|next
)paren
suffix:semicolon
r_struct
id|pt_regs
suffix:semicolon
r_extern
r_void
id|dump_regs
c_func
(paren
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
DECL|function|__is_processor
r_static
r_inline
r_int
id|__is_processor
c_func
(paren
r_int
r_int
id|pv
)paren
(brace
r_int
r_int
id|pvr
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;mfspr %0, 0x11F&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|pvr
)paren
)paren
suffix:semicolon
r_return
id|PVR_VER
c_func
(paren
id|pvr
)paren
op_eq
id|pv
suffix:semicolon
)brace
multiline_comment|/*&n; * Atomic exchange&n; *&n; * Changes the memory location &squot;*ptr&squot; to be val and returns&n; * the previous value stored there.&n; *&n; * Inline asm pulled from arch/ppc/kernel/misc.S so ppc64&n; * is more like most of the other architectures.&n; */
r_static
id|__inline__
r_int
r_int
DECL|function|__xchg_u32
id|__xchg_u32
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
id|dummy
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
id|EIEIO_ON_SMP
l_string|&quot;1:&t;lwarx %0,0,%3&t;&t;# __xchg_u32&bslash;n&bslash;&n;&t;stwcx. %2,0,%3&bslash;n&bslash;&n;2:&t;bne- 1b&quot;
id|ISYNC_ON_SMP
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|dummy
)paren
comma
l_string|&quot;=m&quot;
(paren
op_star
id|m
)paren
suffix:colon
l_string|&quot;r&quot;
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
(paren
id|dummy
)paren
suffix:semicolon
)brace
r_static
id|__inline__
r_int
r_int
DECL|function|__xchg_u64
id|__xchg_u64
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
id|dummy
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
id|EIEIO_ON_SMP
l_string|&quot;1:&t;ldarx %0,0,%3&t;&t;# __xchg_u64&bslash;n&bslash;&n;&t;stdcx. %2,0,%3&bslash;n&bslash;&n;2:&t;bne- 1b&quot;
id|ISYNC_ON_SMP
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|dummy
)paren
comma
l_string|&quot;=m&quot;
(paren
op_star
id|m
)paren
suffix:colon
l_string|&quot;r&quot;
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
(paren
id|dummy
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This function doesn&squot;t exist, so you&squot;ll get a linker error&n; * if something tries to do an invalid xchg().&n; */
r_extern
r_void
id|__xchg_called_with_bad_pointer
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
id|__inline__
r_int
r_int
DECL|function|__xchg
id|__xchg
c_func
(paren
r_volatile
r_void
op_star
id|ptr
comma
r_int
r_int
id|x
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
id|__xchg_u32
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
id|__xchg_u64
c_func
(paren
id|ptr
comma
id|x
)paren
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
DECL|macro|xchg
mdefine_line|#define xchg(ptr,x)&t;&t;&t;&t;&t;&t;&t;     &bslash;&n;  ({&t;&t;&t;&t;&t;&t;&t;&t;&t;     &bslash;&n;     __typeof__(*(ptr)) _x_ = (x);&t;&t;&t;&t;&t;     &bslash;&n;     (__typeof__(*(ptr))) __xchg((ptr), (unsigned long)_x_, sizeof(*(ptr))); &bslash;&n;  })
DECL|macro|tas
mdefine_line|#define tas(ptr) (xchg((ptr),1))
DECL|macro|__HAVE_ARCH_CMPXCHG
mdefine_line|#define __HAVE_ARCH_CMPXCHG&t;1
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
id|p
comma
r_int
id|old
comma
r_int
r_new
)paren
(brace
r_int
r_int
id|prev
suffix:semicolon
id|__asm__
id|__volatile__
(paren
id|EIEIO_ON_SMP
l_string|&quot;1:&t;lwarx&t;%0,0,%2&t;&t;# __cmpxchg_u32&bslash;n&bslash;&n;&t;cmpw&t;0,%0,%3&bslash;n&bslash;&n;&t;bne-&t;2f&bslash;n&bslash;&n;&t;stwcx.&t;%4,0,%2&bslash;n&bslash;&n;&t;bne-&t;1b&quot;
id|ISYNC_ON_SMP
l_string|&quot;&bslash;n&bslash;&n;2:&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|prev
)paren
comma
l_string|&quot;=m&quot;
(paren
op_star
id|p
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|p
)paren
comma
l_string|&quot;r&quot;
(paren
id|old
)paren
comma
l_string|&quot;r&quot;
(paren
r_new
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|p
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|prev
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
id|p
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
r_int
r_int
id|prev
suffix:semicolon
id|__asm__
id|__volatile__
(paren
id|EIEIO_ON_SMP
l_string|&quot;1:&t;ldarx&t;%0,0,%2&t;&t;# __cmpxchg_u64&bslash;n&bslash;&n;&t;cmpd&t;0,%0,%3&bslash;n&bslash;&n;&t;bne-&t;2f&bslash;n&bslash;&n;&t;stdcx.&t;%4,0,%2&bslash;n&bslash;&n;&t;bne-&t;1b&quot;
id|ISYNC_ON_SMP
l_string|&quot;&bslash;n&bslash;&n;2:&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|prev
)paren
comma
l_string|&quot;=m&quot;
(paren
op_star
id|p
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|p
)paren
comma
l_string|&quot;r&quot;
(paren
id|old
)paren
comma
l_string|&quot;r&quot;
(paren
r_new
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|p
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|prev
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
macro_line|#endif
eof
