multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1994, 95, 96, 97, 98, 99, 2003 by Ralf Baechle&n; * Copyright (C) 1996 by Paul M. Antoine&n; * Copyright (C) 1999 Silicon Graphics&n; * Kevin D. Kissell, kevink@mips.org and Carsten Langgaard, carstenl@mips.com&n; * Copyright (C) 2000 MIPS Technologies, Inc.&n; */
macro_line|#ifndef _ASM_SYSTEM_H
DECL|macro|_ASM_SYSTEM_H
mdefine_line|#define _ASM_SYSTEM_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &lt;asm/cpu-features.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/war.h&gt;
macro_line|#include &lt;asm/interrupt.h&gt;
multiline_comment|/*&n; * read_barrier_depends - Flush all pending reads that subsequents reads&n; * depend on.&n; *&n; * No data-dependent reads from memory-like regions are ever reordered&n; * over this barrier.  All reads preceding this primitive are guaranteed&n; * to access memory (but not necessarily other CPUs&squot; caches) before any&n; * reads following this primitive that depend on the data return by&n; * any of the preceding reads.  This primitive is much lighter weight than&n; * rmb() on most CPUs, and is never heavier weight than is&n; * rmb().&n; *&n; * These ordering constraints are respected by both the local CPU&n; * and the compiler.&n; *&n; * Ordering is not guaranteed by anything other than these primitives,&n; * not even by data dependencies.  See the documentation for&n; * memory_barrier() for examples and URLs to more information.&n; *&n; * For example, the following code would force ordering (the initial&n; * value of &quot;a&quot; is zero, &quot;b&quot; is one, and &quot;p&quot; is &quot;&amp;a&quot;):&n; *&n; * &lt;programlisting&gt;&n; *&t;CPU 0&t;&t;&t;&t;CPU 1&n; *&n; *&t;b = 2;&n; *&t;memory_barrier();&n; *&t;p = &amp;b;&t;&t;&t;&t;q = p;&n; *&t;&t;&t;&t;&t;read_barrier_depends();&n; *&t;&t;&t;&t;&t;d = *q;&n; * &lt;/programlisting&gt;&n; *&n; * because the read of &quot;*q&quot; depends on the read of &quot;p&quot; and these&n; * two reads are separated by a read_barrier_depends().  However,&n; * the following code, with the same initial values for &quot;a&quot; and &quot;b&quot;:&n; *&n; * &lt;programlisting&gt;&n; *&t;CPU 0&t;&t;&t;&t;CPU 1&n; *&n; *&t;a = 2;&n; *&t;memory_barrier();&n; *&t;b = 3;&t;&t;&t;&t;y = b;&n; *&t;&t;&t;&t;&t;read_barrier_depends();&n; *&t;&t;&t;&t;&t;x = a;&n; * &lt;/programlisting&gt;&n; *&n; * does not enforce ordering, since there is no data dependency between&n; * the read of &quot;a&quot; and the read of &quot;b&quot;.  Therefore, on some CPUs, such&n; * as Alpha, &quot;y&quot; could be set to 3 and &quot;x&quot; to 0.  Use rmb()&n; * in cases like thiswhere there are no data dependencies.&n; */
DECL|macro|read_barrier_depends
mdefine_line|#define read_barrier_depends()&t;do { } while(0)
macro_line|#ifdef CONFIG_CPU_HAS_SYNC
DECL|macro|__sync
mdefine_line|#define __sync()&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&bslash;&n;&t;&t;&quot;.set&t;push&bslash;n&bslash;t&quot;&t;&t;&bslash;&n;&t;&t;&quot;.set&t;noreorder&bslash;n&bslash;t&quot;&t;&t;&bslash;&n;&t;&t;&quot;.set&t;mips2&bslash;n&bslash;t&quot;&t;&t;&bslash;&n;&t;&t;&quot;sync&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;.set&t;pop&quot;&t;&t;&t;&bslash;&n;&t;&t;: /* no output */&t;&t;&bslash;&n;&t;&t;: /* no input */&t;&t;&bslash;&n;&t;&t;: &quot;memory&quot;)
macro_line|#else
DECL|macro|__sync
mdefine_line|#define __sync()&t;do { } while(0)
macro_line|#endif
DECL|macro|__fast_iob
mdefine_line|#define __fast_iob()&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&bslash;&n;&t;&t;&quot;.set&t;push&bslash;n&bslash;t&quot;&t;&t;&bslash;&n;&t;&t;&quot;.set&t;noreorder&bslash;n&bslash;t&quot;&t;&t;&bslash;&n;&t;&t;&quot;lw&t;$0,%0&bslash;n&bslash;t&quot;&t;&t;&bslash;&n;&t;&t;&quot;nop&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;.set&t;pop&quot;&t;&t;&t;&bslash;&n;&t;&t;: /* no output */&t;&t;&bslash;&n;&t;&t;: &quot;m&quot; (*(int *)CKSEG1)&t;&t;&bslash;&n;&t;&t;: &quot;memory&quot;)
DECL|macro|fast_wmb
mdefine_line|#define fast_wmb()&t;__sync()
DECL|macro|fast_rmb
mdefine_line|#define fast_rmb()&t;__sync()
DECL|macro|fast_mb
mdefine_line|#define fast_mb()&t;__sync()
DECL|macro|fast_iob
mdefine_line|#define fast_iob()&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__sync();&t;&t;&t;&bslash;&n;&t;&t;__fast_iob();&t;&t;&t;&bslash;&n;&t;} while (0)
macro_line|#ifdef CONFIG_CPU_HAS_WB
macro_line|#include &lt;asm/wbflush.h&gt;
DECL|macro|wmb
mdefine_line|#define wmb()&t;&t;fast_wmb()
DECL|macro|rmb
mdefine_line|#define rmb()&t;&t;fast_rmb()
DECL|macro|mb
mdefine_line|#define mb()&t;&t;wbflush()
DECL|macro|iob
mdefine_line|#define iob()&t;&t;wbflush()
macro_line|#else /* !CONFIG_CPU_HAS_WB */
DECL|macro|wmb
mdefine_line|#define wmb()&t;&t;fast_wmb()
DECL|macro|rmb
mdefine_line|#define rmb()&t;&t;fast_rmb()
DECL|macro|mb
mdefine_line|#define mb()&t;&t;fast_mb()
DECL|macro|iob
mdefine_line|#define iob()&t;&t;fast_iob()
macro_line|#endif /* !CONFIG_CPU_HAS_WB */
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
macro_line|#endif
DECL|macro|set_mb
mdefine_line|#define set_mb(var, value) &bslash;&n;do { var = value; mb(); } while (0)
DECL|macro|set_wmb
mdefine_line|#define set_wmb(var, value) &bslash;&n;do { var = value; wmb(); } while (0)
multiline_comment|/*&n; * switch_to(n) should switch tasks to task nr n, first&n; * checking that n isn&squot;t the current task, in which case it does nothing.&n; */
r_extern
id|asmlinkage
r_void
op_star
id|resume
c_func
(paren
r_void
op_star
id|last
comma
r_void
op_star
id|next
comma
r_void
op_star
id|next_ti
)paren
suffix:semicolon
r_struct
id|task_struct
suffix:semicolon
DECL|macro|switch_to
mdefine_line|#define switch_to(prev,next,last) &bslash;&n;do { &bslash;&n;&t;(last) = resume(prev, next, next-&gt;thread_info); &bslash;&n;} while(0)
DECL|macro|ROT_IN_PIECES
mdefine_line|#define ROT_IN_PIECES&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.set&t;noreorder&t;&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;&t;.set&t;reorder&t;&t;&bslash;n&quot;
DECL|function|__xchg_u32
r_static
r_inline
r_int
r_int
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
id|__u32
id|retval
suffix:semicolon
r_if
c_cond
(paren
id|cpu_has_llsc
op_logical_and
id|R10000_LLSC_WAR
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
l_string|&quot;1:&t;ll&t;%0, %3&t;&t;&t;# xchg_u32&t;&bslash;n&quot;
l_string|&quot;&t;move&t;%2, %z4&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;sc&t;%2, %1&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;beqzl&t;%2, 1b&t;&t;&t;&t;&t;&bslash;n&quot;
id|ROT_IN_PIECES
macro_line|#ifdef CONFIG_SMP
l_string|&quot;&t;sync&t;&t;&t;&t;&t;&t;&bslash;n&quot;
macro_line|#endif
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|retval
)paren
comma
l_string|&quot;=m&quot;
(paren
op_star
id|m
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|dummy
)paren
suffix:colon
l_string|&quot;R&quot;
(paren
op_star
id|m
)paren
comma
l_string|&quot;Jr&quot;
(paren
id|val
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|cpu_has_llsc
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
l_string|&quot;1:&t;ll&t;%0, %3&t;&t;&t;# xchg_u32&t;&bslash;n&quot;
l_string|&quot;&t;move&t;%2, %z4&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;sc&t;%2, %1&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;beqz&t;%2, 1b&t;&t;&t;&t;&t;&bslash;n&quot;
macro_line|#ifdef CONFIG_SMP
l_string|&quot;&t;sync&t;&t;&t;&t;&t;&t;&bslash;n&quot;
macro_line|#endif
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|retval
)paren
comma
l_string|&quot;=m&quot;
(paren
op_star
id|m
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|dummy
)paren
suffix:colon
l_string|&quot;R&quot;
(paren
op_star
id|m
)paren
comma
l_string|&quot;Jr&quot;
(paren
id|val
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
r_int
r_int
id|flags
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|retval
op_assign
op_star
id|m
suffix:semicolon
op_star
id|m
op_assign
id|val
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* implies memory barrier  */
)brace
r_return
id|retval
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_MIPS64
DECL|function|__xchg_u64
r_static
r_inline
id|__u64
id|__xchg_u64
c_func
(paren
r_volatile
id|__u64
op_star
id|m
comma
id|__u64
id|val
)paren
(brace
id|__u64
id|retval
suffix:semicolon
r_if
c_cond
(paren
id|cpu_has_llsc
op_logical_and
id|R10000_LLSC_WAR
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
l_string|&quot;1:&t;lld&t;%0, %3&t;&t;&t;# xchg_u64&t;&bslash;n&quot;
l_string|&quot;&t;move&t;%2, %z4&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;scd&t;%2, %1&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;beqzl&t;%2, 1b&t;&t;&t;&t;&t;&bslash;n&quot;
id|ROT_IN_PIECES
macro_line|#ifdef CONFIG_SMP
l_string|&quot;&t;sync&t;&t;&t;&t;&t;&t;&bslash;n&quot;
macro_line|#endif
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|retval
)paren
comma
l_string|&quot;=m&quot;
(paren
op_star
id|m
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|dummy
)paren
suffix:colon
l_string|&quot;R&quot;
(paren
op_star
id|m
)paren
comma
l_string|&quot;Jr&quot;
(paren
id|val
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|cpu_has_llsc
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
l_string|&quot;1:&t;lld&t;%0, %3&t;&t;&t;# xchg_u64&t;&bslash;n&quot;
l_string|&quot;&t;move&t;%2, %z4&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;scd&t;%2, %1&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;beqz&t;%2, 1b&t;&t;&t;&t;&t;&bslash;n&quot;
macro_line|#ifdef CONFIG_SMP
l_string|&quot;&t;sync&t;&t;&t;&t;&t;&t;&bslash;n&quot;
macro_line|#endif
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|retval
)paren
comma
l_string|&quot;=m&quot;
(paren
op_star
id|m
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|dummy
)paren
suffix:colon
l_string|&quot;R&quot;
(paren
op_star
id|m
)paren
comma
l_string|&quot;Jr&quot;
(paren
id|val
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
r_int
r_int
id|flags
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|retval
op_assign
op_star
id|m
suffix:semicolon
op_star
id|m
op_assign
id|val
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* implies memory barrier  */
)brace
r_return
id|retval
suffix:semicolon
)brace
macro_line|#else
r_extern
id|__u64
id|__xchg_u64_unsupported_on_32bit_kernels
c_func
(paren
r_volatile
id|__u64
op_star
id|m
comma
id|__u64
id|val
)paren
suffix:semicolon
DECL|macro|__xchg_u64
mdefine_line|#define __xchg_u64 __xchg_u64_unsupported_on_32bit_kernels
macro_line|#endif
multiline_comment|/* This function doesn&squot;t exist, so you&squot;ll get a linker error&n;   if something tries to do an invalid xchg().  */
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
mdefine_line|#define xchg(ptr,x) ((__typeof__(*(ptr)))__xchg((unsigned long)(x),(ptr),sizeof(*(ptr))))
DECL|macro|tas
mdefine_line|#define tas(ptr) (xchg((ptr),1))
DECL|macro|__HAVE_ARCH_CMPXCHG
mdefine_line|#define __HAVE_ARCH_CMPXCHG 1
DECL|function|__cmpxchg_u32
r_static
r_inline
r_int
r_int
id|__cmpxchg_u32
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
id|__u32
id|retval
suffix:semicolon
r_if
c_cond
(paren
id|cpu_has_llsc
op_logical_and
id|R10000_LLSC_WAR
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&t;.set&t;noat&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;1:&t;ll&t;%0, %2&t;&t;&t;# __cmpxchg_u32&t;&bslash;n&quot;
l_string|&quot;&t;bne&t;%0, %z3, 2f&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;move&t;$1, %z4&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;sc&t;$1, %1&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;beqzl&t;$1, 1b&t;&t;&t;&t;&t;&bslash;n&quot;
id|ROT_IN_PIECES
macro_line|#ifdef CONFIG_SMP
l_string|&quot;&t;sync&t;&t;&t;&t;&t;&t;&bslash;n&quot;
macro_line|#endif
l_string|&quot;2:&t;&t;&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;.set&t;at&t;&t;&t;&t;&t;&bslash;n&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|retval
)paren
comma
l_string|&quot;=m&quot;
(paren
op_star
id|m
)paren
suffix:colon
l_string|&quot;R&quot;
(paren
op_star
id|m
)paren
comma
l_string|&quot;Jr&quot;
(paren
id|old
)paren
comma
l_string|&quot;Jr&quot;
(paren
r_new
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|cpu_has_llsc
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&t;.set&t;noat&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;1:&t;ll&t;%0, %2&t;&t;&t;# __cmpxchg_u32&t;&bslash;n&quot;
l_string|&quot;&t;bne&t;%0, %z3, 2f&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;move&t;$1, %z4&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;sc&t;$1, %1&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;beqz&t;$1, 1b&t;&t;&t;&t;&t;&bslash;n&quot;
macro_line|#ifdef CONFIG_SMP
l_string|&quot;&t;sync&t;&t;&t;&t;&t;&t;&bslash;n&quot;
macro_line|#endif
l_string|&quot;2:&t;&t;&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;.set&t;at&t;&t;&t;&t;&t;&bslash;n&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|retval
)paren
comma
l_string|&quot;=m&quot;
(paren
op_star
id|m
)paren
suffix:colon
l_string|&quot;R&quot;
(paren
op_star
id|m
)paren
comma
l_string|&quot;Jr&quot;
(paren
id|old
)paren
comma
l_string|&quot;Jr&quot;
(paren
r_new
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
r_int
r_int
id|flags
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|retval
op_assign
op_star
id|m
suffix:semicolon
r_if
c_cond
(paren
id|retval
op_eq
id|old
)paren
op_star
id|m
op_assign
r_new
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* implies memory barrier  */
)brace
r_return
id|retval
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_MIPS64
DECL|function|__cmpxchg_u64
r_static
r_inline
r_int
r_int
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
id|__u64
id|retval
suffix:semicolon
r_if
c_cond
(paren
id|cpu_has_llsc
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&t;.set&t;noat&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;1:&t;lld&t;%0, %2&t;&t;&t;# __cmpxchg_u64&t;&bslash;n&quot;
l_string|&quot;&t;bne&t;%0, %z3, 2f&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;move&t;$1, %z4&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;scd&t;$1, %1&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;beqzl&t;$1, 1b&t;&t;&t;&t;&t;&bslash;n&quot;
id|ROT_IN_PIECES
macro_line|#ifdef CONFIG_SMP
l_string|&quot;&t;sync&t;&t;&t;&t;&t;&t;&bslash;n&quot;
macro_line|#endif
l_string|&quot;2:&t;&t;&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;.set&t;at&t;&t;&t;&t;&t;&bslash;n&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|retval
)paren
comma
l_string|&quot;=m&quot;
(paren
op_star
id|m
)paren
suffix:colon
l_string|&quot;R&quot;
(paren
op_star
id|m
)paren
comma
l_string|&quot;Jr&quot;
(paren
id|old
)paren
comma
l_string|&quot;Jr&quot;
(paren
r_new
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|cpu_has_llsc
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&t;.set&t;noat&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;1:&t;lld&t;%0, %2&t;&t;&t;# __cmpxchg_u64&t;&bslash;n&quot;
l_string|&quot;&t;bne&t;%0, %z3, 2f&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;move&t;$1, %z4&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;scd&t;$1, %1&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;beqz&t;$1, 1b&t;&t;&t;&t;&t;&bslash;n&quot;
macro_line|#ifdef CONFIG_SMP
l_string|&quot;&t;sync&t;&t;&t;&t;&t;&t;&bslash;n&quot;
macro_line|#endif
l_string|&quot;2:&t;&t;&t;&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;.set&t;at&t;&t;&t;&t;&t;&bslash;n&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|retval
)paren
comma
l_string|&quot;=m&quot;
(paren
op_star
id|m
)paren
suffix:colon
l_string|&quot;R&quot;
(paren
op_star
id|m
)paren
comma
l_string|&quot;Jr&quot;
(paren
id|old
)paren
comma
l_string|&quot;Jr&quot;
(paren
r_new
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
r_int
r_int
id|flags
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|retval
op_assign
op_star
id|m
suffix:semicolon
r_if
c_cond
(paren
id|retval
op_eq
id|old
)paren
op_star
id|m
op_assign
r_new
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* implies memory barrier  */
)brace
r_return
id|retval
suffix:semicolon
)brace
macro_line|#else
r_extern
r_int
r_int
id|__cmpxchg_u64_unsupported_on_32bit_kernels
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
suffix:semicolon
DECL|macro|__cmpxchg_u64
mdefine_line|#define __cmpxchg_u64 __cmpxchg_u64_unsupported_on_32bit_kernels
macro_line|#endif
multiline_comment|/* This function doesn&squot;t exist, so you&squot;ll get a linker error&n;   if something tries to do an invalid cmpxchg().  */
r_extern
r_void
id|__cmpxchg_called_with_bad_pointer
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|__cmpxchg
r_static
r_inline
r_int
r_int
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
mdefine_line|#define cmpxchg(ptr,old,new) ((__typeof__(*(ptr)))__cmpxchg((ptr), (unsigned long)(old), (unsigned long)(new),sizeof(*(ptr))))
r_extern
r_void
op_star
id|set_except_vector
c_func
(paren
r_int
id|n
comma
r_void
op_star
id|addr
)paren
suffix:semicolon
r_extern
r_void
id|per_cpu_trap_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|NORET_TYPE
r_void
id|__die
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
r_const
r_char
op_star
id|file
comma
r_const
r_char
op_star
id|func
comma
r_int
r_int
id|line
)paren
suffix:semicolon
r_extern
r_void
id|__die_if_kernel
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
r_const
r_char
op_star
id|file
comma
r_const
r_char
op_star
id|func
comma
r_int
r_int
id|line
)paren
suffix:semicolon
DECL|macro|die
mdefine_line|#define die(msg, regs)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__die(msg, regs, __FILE__ &quot;:&quot;, __FUNCTION__, __LINE__)
DECL|macro|die_if_kernel
mdefine_line|#define die_if_kernel(msg, regs)&t;&t;&t;&t;&t;&bslash;&n;&t;__die_if_kernel(msg, regs, __FILE__ &quot;:&quot;, __FUNCTION__, __LINE__)
r_extern
r_int
id|stop_a_enabled
suffix:semicolon
multiline_comment|/*&n; * Taken from include/asm-ia64/system.h; prevents deadlock on SMP&n; * systems.&n; */
DECL|macro|prepare_arch_switch
mdefine_line|#define prepare_arch_switch(rq, next)&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;spin_lock(&amp;(next)-&gt;switch_lock);&t;&bslash;&n;&t;spin_unlock(&amp;(rq)-&gt;lock);&t;&t;&bslash;&n;} while (0)
DECL|macro|finish_arch_switch
mdefine_line|#define finish_arch_switch(rq, prev)&t;spin_unlock_irq(&amp;(prev)-&gt;switch_lock)
DECL|macro|task_running
mdefine_line|#define task_running(rq, p) &t;&t;((rq)-&gt;curr == (p) || spin_is_locked(&amp;(p)-&gt;switch_lock))
macro_line|#endif /* _ASM_SYSTEM_H */
eof
