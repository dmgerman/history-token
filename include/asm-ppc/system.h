multiline_comment|/*&n; * $Id: system.h,v 1.49 1999/09/11 18:37:54 cort Exp $&n; *&n; * Copyright (C) 1999 Cort Dougan &lt;cort@cs.nmt.edu&gt;&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __PPC_SYSTEM_H
DECL|macro|__PPC_SYSTEM_H
mdefine_line|#define __PPC_SYSTEM_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kdev_t.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/hw_irq.h&gt;
multiline_comment|/*&n; * Memory barrier.&n; * The sync instruction guarantees that all memory accesses initiated&n; * by this processor have been performed (with respect to all other&n; * mechanisms that access memory).  The eieio instruction is a barrier&n; * providing an ordering (separately) for (a) cacheable stores and (b)&n; * loads and stores to non-cacheable memory (e.g. I/O devices).&n; *&n; * mb() prevents loads and stores being reordered across this point.&n; * rmb() prevents loads being reordered across this point.&n; * wmb() prevents stores being reordered across this point.&n; *&n; * We can use the eieio instruction for wmb, but since it doesn&squot;t&n; * give any ordering guarantees about loads, we have to use the&n; * stronger but slower sync instruction for mb and rmb.&n; */
DECL|macro|mb
mdefine_line|#define mb()  __asm__ __volatile__ (&quot;sync&quot; : : : &quot;memory&quot;)
DECL|macro|rmb
mdefine_line|#define rmb()  __asm__ __volatile__ (&quot;sync&quot; : : : &quot;memory&quot;)
DECL|macro|wmb
mdefine_line|#define wmb()  __asm__ __volatile__ (&quot;eieio&quot; : : : &quot;memory&quot;)
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
macro_line|#else
DECL|macro|smp_mb
mdefine_line|#define smp_mb()&t;__asm__ __volatile__(&quot;&quot;: : :&quot;memory&quot;)
DECL|macro|smp_rmb
mdefine_line|#define smp_rmb()&t;__asm__ __volatile__(&quot;&quot;: : :&quot;memory&quot;)
DECL|macro|smp_wmb
mdefine_line|#define smp_wmb()&t;__asm__ __volatile__(&quot;&quot;: : :&quot;memory&quot;)
macro_line|#endif /* CONFIG_SMP */
r_extern
r_void
id|xmon_irq
c_func
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_extern
r_void
id|xmon
c_func
(paren
r_struct
id|pt_regs
op_star
id|excp
)paren
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
r_extern
r_int
id|_get_PVR
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|_get_L2CR
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
r_int
id|abs
c_func
(paren
r_int
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
r_struct
id|task_struct
suffix:semicolon
DECL|macro|prepare_to_switch
mdefine_line|#define prepare_to_switch()&t;do { } while(0)
DECL|macro|switch_to
mdefine_line|#define switch_to(prev,next,last) _switch_to((prev),(next),&amp;(last))
r_extern
r_void
id|_switch_to
c_func
(paren
r_struct
id|task_struct
op_star
comma
r_struct
id|task_struct
op_star
comma
r_struct
id|task_struct
op_star
op_star
)paren
suffix:semicolon
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
macro_line|#ifndef CONFIG_SMP
DECL|macro|cli
mdefine_line|#define cli()&t;__cli()
DECL|macro|sti
mdefine_line|#define sti()&t;__sti()
DECL|macro|save_flags
mdefine_line|#define save_flags(flags)&t;__save_flags(flags)
DECL|macro|restore_flags
mdefine_line|#define restore_flags(flags)&t;__restore_flags(flags)
DECL|macro|save_and_cli
mdefine_line|#define save_and_cli(flags)&t;__save_and_cli(flags)
macro_line|#else /* CONFIG_SMP */
r_extern
r_void
id|__global_cli
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__global_sti
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|__global_save_flags
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__global_restore_flags
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
DECL|macro|cli
mdefine_line|#define cli() __global_cli()
DECL|macro|sti
mdefine_line|#define sti() __global_sti()
DECL|macro|save_flags
mdefine_line|#define save_flags(x) ((x)=__global_save_flags())
DECL|macro|restore_flags
mdefine_line|#define restore_flags(x) __global_restore_flags(x)
macro_line|#endif /* !CONFIG_SMP */
DECL|macro|local_irq_disable
mdefine_line|#define local_irq_disable()&t;&t;__cli()
DECL|macro|local_irq_enable
mdefine_line|#define local_irq_enable()&t;&t;__sti()
DECL|macro|local_irq_save
mdefine_line|#define local_irq_save(flags)&t;&t;__save_and_cli(flags)
DECL|macro|local_irq_restore
mdefine_line|#define local_irq_restore(flags)&t;__restore_flags(flags)
DECL|macro|xchg
mdefine_line|#define xchg(ptr,x) ((__typeof__(*(ptr)))__xchg((unsigned long)(x),(ptr),sizeof(*(ptr))))
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
"&quot;"
l_int|1
suffix:colon
id|lwarx
op_mod
l_int|0
comma
l_int|0
comma
op_mod
l_int|2
id|stwcx
dot
op_mod
l_int|3
comma
l_int|0
comma
op_mod
l_int|2
id|bne
op_minus
l_int|1
id|b
"&quot;"
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
id|prev
suffix:semicolon
id|__asm__
id|__volatile__
(paren
"&quot;"
l_int|1
suffix:colon
id|lwarx
op_mod
l_int|0
comma
l_int|0
comma
op_mod
l_int|2
id|cmpw
l_int|0
comma
op_mod
l_int|0
comma
op_mod
l_int|3
id|bne
l_float|2f
id|stwcx
dot
op_mod
l_int|4
comma
l_int|0
comma
op_mod
l_int|2
id|bne
op_minus
l_int|1
id|b
"&bslash;"
id|n
"&quot;"
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
macro_line|#endif /* __PPC_SYSTEM_H */
macro_line|#endif /* __KERNEL__ */
eof
