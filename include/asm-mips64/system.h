multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1994, 1995, 1996, 1997, 1998, 1999 by Ralf Baechle&n; * Modified further for R[236]000 by Paul M. Antoine, 1996&n; * Copyright (C) 1999 Silicon Graphics&n; */
macro_line|#ifndef _ASM_SYSTEM_H
DECL|macro|_ASM_SYSTEM_H
mdefine_line|#define _ASM_SYSTEM_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/sgidefs.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
id|__asm__
(paren
l_string|&quot;.macro&bslash;tlocal_irq_enable&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tpush&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;treorder&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tnoat&bslash;n&bslash;t&quot;
l_string|&quot;mfc0&bslash;t$1,$12&bslash;n&bslash;t&quot;
l_string|&quot;ori&bslash;t$1,0x1f&bslash;n&bslash;t&quot;
l_string|&quot;xori&bslash;t$1,0x1e&bslash;n&bslash;t&quot;
l_string|&quot;mtc0&bslash;t$1,$12&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tpop&bslash;n&bslash;t&quot;
l_string|&quot;.endm&quot;
)paren
suffix:semicolon
DECL|function|local_irq_enable
r_extern
r_inline
r_void
id|local_irq_enable
c_func
(paren
r_void
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;local_irq_enable&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
multiline_comment|/* no inputs */
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * For cli() we have to insert nops to make sure that the new value&n; * has actually arrived in the status register before the end of this&n; * macro.&n; * R4000/R4400 need three nops, the R4600 two nops and the R10000 needs&n; * no nops at all.&n; */
id|__asm__
(paren
l_string|&quot;.macro&bslash;tlocal_irq_disable&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tpush&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tnoat&bslash;n&bslash;t&quot;
l_string|&quot;mfc0&bslash;t$1,$12&bslash;n&bslash;t&quot;
l_string|&quot;ori&bslash;t$1,1&bslash;n&bslash;t&quot;
l_string|&quot;xori&bslash;t$1,1&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot;
l_string|&quot;mtc0&bslash;t$1,$12&bslash;n&bslash;t&quot;
l_string|&quot;sll&bslash;t$0, $0, 1&bslash;t&bslash;t&bslash;t# nop&bslash;n&bslash;t&quot;
l_string|&quot;sll&bslash;t$0, $0, 1&bslash;t&bslash;t&bslash;t# nop&bslash;n&bslash;t&quot;
l_string|&quot;sll&bslash;t$0, $0, 1&bslash;t&bslash;t&bslash;t# nop&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tpop&bslash;n&bslash;t&quot;
l_string|&quot;.endm&quot;
)paren
suffix:semicolon
DECL|function|local_irq_disable
r_extern
r_inline
r_void
id|local_irq_disable
c_func
(paren
r_void
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;local_irq_disable&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
multiline_comment|/* no inputs */
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
id|__asm__
(paren
l_string|&quot;.macro&bslash;tlocal_save_flags flags&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tpush&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;treorder&bslash;n&bslash;t&quot;
l_string|&quot;mfc0&bslash;t&bslash;&bslash;flags, $12&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tpop&bslash;n&bslash;t&quot;
l_string|&quot;.endm&quot;
)paren
suffix:semicolon
DECL|macro|local_save_flags
mdefine_line|#define local_save_flags(x)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;local_save_flags %0&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;=r&quot; (x))
id|__asm__
(paren
l_string|&quot;.macro&bslash;tlocal_irq_save result&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tpush&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;treorder&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tnoat&bslash;n&bslash;t&quot;
l_string|&quot;mfc0&bslash;t&bslash;&bslash;result, $12&bslash;n&bslash;t&quot;
l_string|&quot;ori&bslash;t$1, &bslash;&bslash;result, 1&bslash;n&bslash;t&quot;
l_string|&quot;xori&bslash;t$1, 1&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot;
l_string|&quot;mtc0&bslash;t$1, $12&bslash;n&bslash;t&quot;
l_string|&quot;sll&bslash;t$0, $0, 1&bslash;t&bslash;t&bslash;t# nop&bslash;n&bslash;t&quot;
l_string|&quot;sll&bslash;t$0, $0, 1&bslash;t&bslash;t&bslash;t# nop&bslash;n&bslash;t&quot;
l_string|&quot;sll&bslash;t$0, $0, 1&bslash;t&bslash;t&bslash;t# nop&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tpop&bslash;n&bslash;t&quot;
l_string|&quot;.endm&quot;
)paren
suffix:semicolon
DECL|macro|local_irq_save
mdefine_line|#define local_irq_save(x)&t;&t;&t;&t;&t;&t;&bslash;&n;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;local_irq_save&bslash;t%0&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;=r&quot; (x)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: /* no inputs */&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;memory&quot;)
id|__asm__
c_func
(paren
l_string|&quot;.macro&bslash;tlocal_irq_restore flags&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tnoat&bslash;n&bslash;t&quot;
l_string|&quot;mfc0&bslash;t$1, $12&bslash;n&bslash;t&quot;
l_string|&quot;andi&bslash;t&bslash;&bslash;flags, 1&bslash;n&bslash;t&quot;
l_string|&quot;ori&bslash;t$1, 1&bslash;n&bslash;t&quot;
l_string|&quot;xori&bslash;t$1, 1&bslash;n&bslash;t&quot;
l_string|&quot;or&bslash;t&bslash;&bslash;flags, $1&bslash;n&bslash;t&quot;
l_string|&quot;mtc0&bslash;t&bslash;&bslash;flags, $12&bslash;n&bslash;t&quot;
l_string|&quot;sll&bslash;t$0, $0, 1&bslash;t&bslash;t&bslash;t# nop&bslash;n&bslash;t&quot;
l_string|&quot;sll&bslash;t$0, $0, 1&bslash;t&bslash;t&bslash;t# nop&bslash;n&bslash;t&quot;
l_string|&quot;sll&bslash;t$0, $0, 1&bslash;t&bslash;t&bslash;t# nop&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tat&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;treorder&bslash;n&bslash;t&quot;
l_string|&quot;.endm&quot;
)paren
suffix:semicolon
DECL|macro|local_irq_restore
mdefine_line|#define local_irq_restore(flags)&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long __tmp1;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;local_irq_restore&bslash;t%0&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot; (__tmp1)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;0&quot; (flags)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;memory&quot;);&t;&t;&t;&t;&t;&t;&bslash;&n;} while(0)
DECL|macro|irqs_disabled
mdefine_line|#define irqs_disabled()&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long flags;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;local_save_flags(flags);&t;&t;&t;&t;&t;&bslash;&n;&t;!(flags &amp; 1);&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
multiline_comment|/*&n; * read_barrier_depends - Flush all pending reads that subsequents reads&n; * depend on.&n; *&n; * No data-dependent reads from memory-like regions are ever reordered&n; * over this barrier.  All reads preceding this primitive are guaranteed&n; * to access memory (but not necessarily other CPUs&squot; caches) before any&n; * reads following this primitive that depend on the data return by&n; * any of the preceding reads.  This primitive is much lighter weight than&n; * rmb() on most CPUs, and is never heavier weight than is&n; * rmb().&n; *&n; * These ordering constraints are respected by both the local CPU&n; * and the compiler.&n; *&n; * Ordering is not guaranteed by anything other than these primitives,&n; * not even by data dependencies.  See the documentation for&n; * memory_barrier() for examples and URLs to more information.&n; *&n; * For example, the following code would force ordering (the initial&n; * value of &quot;a&quot; is zero, &quot;b&quot; is one, and &quot;p&quot; is &quot;&amp;a&quot;):&n; *&n; * &lt;programlisting&gt;&n; *&t;CPU 0&t;&t;&t;&t;CPU 1&n; *&n; *&t;b = 2;&n; *&t;memory_barrier();&n; *&t;p = &amp;b;&t;&t;&t;&t;q = p;&n; *&t;&t;&t;&t;&t;read_barrier_depends();&n; *&t;&t;&t;&t;&t;d = *q;&n; * &lt;/programlisting&gt;&n; *&n; * because the read of &quot;*q&quot; depends on the read of &quot;p&quot; and these&n; * two reads are separated by a read_barrier_depends().  However,&n; * the following code, with the same initial values for &quot;a&quot; and &quot;b&quot;:&n; *&n; * &lt;programlisting&gt;&n; *&t;CPU 0&t;&t;&t;&t;CPU 1&n; *&n; *&t;a = 2;&n; *&t;memory_barrier();&n; *&t;b = 3;&t;&t;&t;&t;y = b;&n; *&t;&t;&t;&t;&t;read_barrier_depends();&n; *&t;&t;&t;&t;&t;x = a;&n; * &lt;/programlisting&gt;&n; *&n; * does not enforce ordering, since there is no data dependency between&n; * the read of &quot;a&quot; and the read of &quot;b&quot;.  Therefore, on some CPUs, such&n; * as Alpha, &quot;y&quot; could be set to 3 and &quot;x&quot; to 0.  Use rmb()&n; * in cases like thiswhere there are no data dependencies.&n; */
DECL|macro|read_barrier_depends
mdefine_line|#define read_barrier_depends()&t;do { } while(0)
macro_line|#ifdef CONFIG_CPU_HAS_SYNC
DECL|macro|__sync
mdefine_line|#define __sync()&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&bslash;&n;&t;&t;&quot;.set&t;push&bslash;n&bslash;t&quot;&t;&t;&bslash;&n;&t;&t;&quot;.set&t;noreorder&bslash;n&bslash;t&quot;&t;&t;&bslash;&n;&t;&t;&quot;sync&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;.set&t;pop&quot;&t;&t;&t;&bslash;&n;&t;&t;: /* no output */&t;&t;&bslash;&n;&t;&t;: /* no input */&t;&t;&bslash;&n;&t;&t;: &quot;memory&quot;)
macro_line|#else
DECL|macro|__sync
mdefine_line|#define __sync()&t;do { } while(0)
macro_line|#endif
DECL|macro|__fast_iob
mdefine_line|#define __fast_iob()&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&bslash;&n;&t;&t;&quot;.set&t;push&bslash;n&bslash;t&quot;&t;&t;&bslash;&n;&t;&t;&quot;.set&t;noreorder&bslash;n&bslash;t&quot;&t;&t;&bslash;&n;&t;&t;&quot;lw&t;$0,%0&bslash;n&bslash;t&quot;&t;&t;&bslash;&n;&t;&t;&quot;nop&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;.set&t;pop&quot;&t;&t;&t;&bslash;&n;&t;&t;: /* no output */&t;&t;&bslash;&n;&t;&t;: &quot;m&quot; (*(int *)KSEG1)&t;&t;&bslash;&n;&t;&t;: &quot;memory&quot;)
DECL|macro|fast_wmb
mdefine_line|#define fast_wmb()&t;__sync()
DECL|macro|fast_rmb
mdefine_line|#define fast_rmb()&t;__sync()
DECL|macro|fast_mb
mdefine_line|#define fast_mb()&t;__sync()
DECL|macro|fast_iob
mdefine_line|#define fast_iob()&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__sync();&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__(&t;&t;&bslash;&n;&t;&t;&t;&quot;.set&t;push&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&t;&t;&quot;.set&t;noreorder&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&t;&t;&quot;lw&t;$0,%0&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&t;&t;&quot;nop&bslash;n&bslash;t&quot;&t;&t;&bslash;&n;&t;&t;&t;&quot;.set&t;pop&quot;&t;&t;&bslash;&n;&t;&t;&t;: /* no output */&t;&bslash;&n;&t;&t;&t;: &quot;m&quot; (*(int *)KSEG1)&t;&bslash;&n;&t;&t;&t;: &quot;memory&quot;);&t;&t;&bslash;&n;&t;} while (0)
DECL|macro|wmb
mdefine_line|#define wmb()&t;&t;fast_wmb()
DECL|macro|rmb
mdefine_line|#define rmb()&t;&t;fast_rmb()
DECL|macro|mb
mdefine_line|#define mb()&t;&t;fast_mb()
DECL|macro|iob
mdefine_line|#define iob()&t;&t;fast_iob()
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
DECL|function|xchg_u32
r_extern
id|__inline__
r_int
r_int
id|xchg_u32
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
l_string|&quot;.set&bslash;tpush&bslash;t&bslash;t&bslash;t&bslash;t# xchg_u32&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tnomacro&bslash;n&bslash;t&quot;
l_string|&quot;ll&bslash;t%0, %3&bslash;n&quot;
l_string|&quot;1:&bslash;tmove&bslash;t%2, %z4&bslash;n&bslash;t&quot;
l_string|&quot;sc&bslash;t%2, %1&bslash;n&bslash;t&quot;
l_string|&quot;beqzl&bslash;t%2, 1b&bslash;n&bslash;t&quot;
l_string|&quot; ll&bslash;t%0, %3&bslash;n&bslash;t&quot;
l_string|&quot;sync&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tpop&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|val
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
r_return
id|val
suffix:semicolon
)brace
DECL|function|xchg_u64
r_extern
id|__inline__
r_int
r_int
id|xchg_u64
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
l_string|&quot;.set&bslash;tpush&bslash;t&bslash;t&bslash;t&bslash;t# xchg_u64&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tnomacro&bslash;n&bslash;t&quot;
l_string|&quot;lld&bslash;t%0, %3&bslash;n&quot;
l_string|&quot;1:&bslash;tmove&bslash;t%2, %z4&bslash;n&bslash;t&quot;
l_string|&quot;scd&bslash;t%2, %1&bslash;n&bslash;t&quot;
l_string|&quot;beqzl&bslash;t%2, 1b&bslash;n&bslash;t&quot;
l_string|&quot; lld&bslash;t%0, %3&bslash;n&bslash;t&quot;
l_string|&quot;sync&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tpop&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|val
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
r_return
id|val
suffix:semicolon
)brace
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
id|xchg_u32
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
id|xchg_u64
c_func
(paren
id|ptr
comma
id|x
)paren
suffix:semicolon
)brace
r_return
id|x
suffix:semicolon
)brace
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
id|__attribute__
c_func
(paren
(paren
id|noreturn
)paren
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
macro_line|#endif /* _ASM_SYSTEM_H */
eof
