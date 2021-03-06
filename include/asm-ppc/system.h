multiline_comment|/*&n; * Copyright (C) 1999 Cort Dougan &lt;cort@cs.nmt.edu&gt;&n; */
macro_line|#ifndef __PPC_SYSTEM_H
DECL|macro|__PPC_SYSTEM_H
mdefine_line|#define __PPC_SYSTEM_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/hw_irq.h&gt;
multiline_comment|/*&n; * Memory barrier.&n; * The sync instruction guarantees that all memory accesses initiated&n; * by this processor have been performed (with respect to all other&n; * mechanisms that access memory).  The eieio instruction is a barrier&n; * providing an ordering (separately) for (a) cacheable stores and (b)&n; * loads and stores to non-cacheable memory (e.g. I/O devices).&n; *&n; * mb() prevents loads and stores being reordered across this point.&n; * rmb() prevents loads being reordered across this point.&n; * wmb() prevents stores being reordered across this point.&n; * read_barrier_depends() prevents data-dependent loads being reordered&n; *&t;across this point (nop on PPC).&n; *&n; * We can use the eieio instruction for wmb, but since it doesn&squot;t&n; * give any ordering guarantees about loads, we have to use the&n; * stronger but slower sync instruction for mb and rmb.&n; */
DECL|macro|mb
mdefine_line|#define mb()  __asm__ __volatile__ (&quot;sync&quot; : : : &quot;memory&quot;)
DECL|macro|rmb
mdefine_line|#define rmb()  __asm__ __volatile__ (&quot;sync&quot; : : : &quot;memory&quot;)
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
macro_line|#endif /* CONFIG_SMP */
macro_line|#ifdef __KERNEL__
r_struct
id|task_struct
suffix:semicolon
r_struct
id|pt_regs
suffix:semicolon
r_extern
r_void
id|print_backtrace
c_func
(paren
r_int
r_int
op_star
)paren
suffix:semicolon
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
r_void
id|hard_reset_now
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|poweroff_now
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_6xx
r_extern
r_int
id|_get_L2CR
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|_get_L3CR
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|_set_L2CR
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|_set_L3CR
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
macro_line|#else
DECL|macro|_get_L2CR
mdefine_line|#define _get_L2CR()&t;0L
DECL|macro|_get_L3CR
mdefine_line|#define _get_L3CR()&t;0L
DECL|macro|_set_L2CR
mdefine_line|#define _set_L2CR(val)&t;do { } while(0)
DECL|macro|_set_L3CR
mdefine_line|#define _set_L3CR(val)&t;do { } while(0)
macro_line|#endif
r_extern
r_void
id|via_cuda_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|pmac_nvram_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|read_rtc_time
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|pmac_find_display
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
id|enable_kernel_fp
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
id|load_up_altivec
c_func
(paren
r_struct
id|task_struct
op_star
)paren
suffix:semicolon
r_extern
r_void
id|giveup_spe
c_func
(paren
r_struct
id|task_struct
op_star
)paren
suffix:semicolon
r_extern
r_void
id|load_up_spe
c_func
(paren
r_struct
id|task_struct
op_star
)paren
suffix:semicolon
r_extern
r_int
id|fix_alignment
c_func
(paren
r_struct
id|pt_regs
op_star
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
id|call_rtas
c_func
(paren
r_const
r_char
op_star
comma
r_int
comma
r_int
comma
r_int
r_int
op_star
comma
dot
dot
dot
)paren
suffix:semicolon
r_extern
r_void
id|cacheable_memzero
c_func
(paren
r_void
op_star
id|p
comma
r_int
r_int
id|nb
)paren
suffix:semicolon
r_extern
r_int
id|do_page_fault
c_func
(paren
r_struct
id|pt_regs
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|bad_page_fault
c_func
(paren
r_struct
id|pt_regs
op_star
comma
r_int
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|die
c_func
(paren
r_const
r_char
op_star
comma
r_struct
id|pt_regs
op_star
comma
r_int
)paren
suffix:semicolon
r_struct
id|device_node
suffix:semicolon
r_extern
r_void
id|note_scsi_host
c_func
(paren
r_struct
id|device_node
op_star
comma
r_void
op_star
)paren
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
r_extern
r_int
r_int
id|rtas_data
suffix:semicolon
r_static
id|__inline__
r_int
r_int
DECL|function|xchg_u32
id|xchg_u32
c_func
(paren
r_volatile
r_void
op_star
id|p
comma
r_int
r_int
id|val
)paren
(brace
r_int
r_int
id|prev
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;&bslash;n&bslash;&n;1:&t;lwarx&t;%0,0,%2 &bslash;n&quot;
id|PPC405_ERR77
c_func
(paren
l_int|0
comma
op_mod
l_int|2
)paren
l_string|&quot;&t;stwcx.&t;%3,0,%2 &bslash;n&bslash;&n;&t;bne-&t;1b&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|prev
)paren
comma
l_string|&quot;=m&quot;
(paren
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
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
id|val
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
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
multiline_comment|/*&n; * This function doesn&squot;t exist, so you&squot;ll get a linker error&n; * if something tries to do an invalid xchg().&n; */
r_extern
r_void
id|__xchg_called_with_bad_pointer
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|xchg
mdefine_line|#define xchg(ptr,x) ((__typeof__(*(ptr)))__xchg((unsigned long)(x),(ptr),sizeof(*(ptr))))
DECL|macro|tas
mdefine_line|#define tas(ptr) (xchg((ptr),1))
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
(paren
r_int
r_int
)paren
id|xchg_u32
c_func
(paren
id|ptr
comma
id|x
)paren
suffix:semicolon
macro_line|#if 0&t;/* xchg_u64 doesn&squot;t exist on 32-bit PPC */
r_case
l_int|8
suffix:colon
r_return
(paren
r_int
r_int
)paren
id|xchg_u64
c_func
(paren
id|ptr
comma
id|x
)paren
suffix:semicolon
macro_line|#endif /* 0 */
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
DECL|function|xchg_ptr
r_extern
r_inline
r_void
op_star
id|xchg_ptr
c_func
(paren
r_void
op_star
id|m
comma
r_void
op_star
id|val
)paren
(brace
r_return
(paren
r_void
op_star
)paren
id|xchg_u32
c_func
(paren
id|m
comma
(paren
r_int
r_int
)paren
id|val
)paren
suffix:semicolon
)brace
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
l_string|&quot;&bslash;n&bslash;&n;1:&t;lwarx&t;%0,0,%2 &bslash;n&bslash;&n;&t;cmpw&t;0,%0,%3 &bslash;n&bslash;&n;&t;bne&t;2f &bslash;n&quot;
id|PPC405_ERR77
c_func
(paren
l_int|0
comma
op_mod
l_int|2
)paren
l_string|&quot;&t;stwcx.&t;%4,0,%2 &bslash;n&bslash;&n;&t;bne-&t;1b&bslash;n&quot;
macro_line|#ifdef CONFIG_SMP
l_string|&quot;&t;sync&bslash;n&quot;
macro_line|#endif /* CONFIG_SMP */
l_string|&quot;2:&quot;
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
macro_line|#if 0&t;/* we don&squot;t have __cmpxchg_u64 on 32-bit PPC */
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
macro_line|#endif /* 0 */
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
DECL|macro|arch_align_stack
mdefine_line|#define arch_align_stack(x) (x)
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __PPC_SYSTEM_H */
eof
