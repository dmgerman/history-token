multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1994, 1995, 1996, 1997, 1998, 1999 by Ralf Baechle&n; * Modified further for R[236]000 by Paul M. Antoine, 1996&n; * Copyright (C) 1999 Silicon Graphics&n; */
macro_line|#ifndef _ASM_SYSTEM_H
DECL|macro|_ASM_SYSTEM_H
mdefine_line|#define _ASM_SYSTEM_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/sgidefs.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
r_extern
id|__inline__
r_void
DECL|function|__sti
id|__sti
c_func
(paren
r_void
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tnoat&bslash;n&bslash;t&quot;
l_string|&quot;mfc0&bslash;t$1,$12&bslash;n&bslash;t&quot;
l_string|&quot;ori&bslash;t$1,0x1f&bslash;n&bslash;t&quot;
l_string|&quot;xori&bslash;t$1,0x1e&bslash;n&bslash;t&quot;
l_string|&quot;mtc0&bslash;t$1,$12&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tat&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;treorder&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
multiline_comment|/* no inputs */
suffix:colon
l_string|&quot;$1&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * For cli() we have to insert nops to make shure that the new value&n; * has actually arrived in the status register before the end of this&n; * macro.&n; * R4000/R4400 need three nops, the R4600 two nops and the R10000 needs&n; * no nops at all.&n; */
r_extern
id|__inline__
r_void
DECL|function|__cli
id|__cli
c_func
(paren
r_void
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tnoat&bslash;n&bslash;t&quot;
l_string|&quot;mfc0&bslash;t$1,$12&bslash;n&bslash;t&quot;
l_string|&quot;ori&bslash;t$1,1&bslash;n&bslash;t&quot;
l_string|&quot;xori&bslash;t$1,1&bslash;n&bslash;t&quot;
l_string|&quot;mtc0&bslash;t$1,$12&bslash;n&bslash;t&quot;
l_string|&quot;nop&bslash;n&bslash;t&quot;
l_string|&quot;nop&bslash;n&bslash;t&quot;
l_string|&quot;nop&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tat&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;treorder&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
multiline_comment|/* no inputs */
suffix:colon
l_string|&quot;$1&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
DECL|macro|__save_flags
mdefine_line|#define __save_flags(x)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;mfc0&bslash;t%0,$12&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.set&bslash;treorder&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;=r&quot; (x))
DECL|macro|__save_and_cli
mdefine_line|#define __save_and_cli(x)&t;&t;&t;&t;&t;&t;&bslash;&n;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.set&bslash;tnoat&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;mfc0&bslash;t%0,$12&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;ori&bslash;t$1,%0,1&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;xori&bslash;t$1,1&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;mtc0&bslash;t$1,$12&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;nop&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;nop&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;nop&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.set&bslash;tat&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.set&bslash;treorder&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;=r&quot; (x)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: /* no inputs */&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;$1&quot;, &quot;memory&quot;)
DECL|macro|__restore_flags
mdefine_line|#define __restore_flags(flags)&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long __tmp1;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.set&bslash;tnoreorder&bslash;t&bslash;t&bslash;t# __restore_flags&bslash;n&bslash;t&quot;&t;&t;&bslash;&n;&t;&t;&quot;.set&bslash;tnoat&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;mfc0&bslash;t$1, $12&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;andi&bslash;t%0, 1&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;ori&bslash;t$1, 1&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;xori&bslash;t$1, 1&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;or&bslash;t%0, $1&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;mtc0&bslash;t%0, $12&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;nop&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;nop&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;nop&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.set&bslash;tat&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.set&bslash;treorder&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot; (__tmp1)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;0&quot; (flags)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;$1&quot;, &quot;memory&quot;);&t;&t;&t;&t;&t;&bslash;&n;} while(0)
macro_line|#ifdef CONFIG_SMP
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
DECL|macro|save_and_cli
mdefine_line|#define save_and_cli(x) do { save_flags(x); cli(); } while(0)
macro_line|#else
DECL|macro|cli
mdefine_line|#define cli() __cli()
DECL|macro|sti
mdefine_line|#define sti() __sti()
DECL|macro|save_flags
mdefine_line|#define save_flags(x) __save_flags(x)
DECL|macro|restore_flags
mdefine_line|#define restore_flags(x) __restore_flags(x)
DECL|macro|save_and_cli
mdefine_line|#define save_and_cli(x) __save_and_cli(x)
macro_line|#endif /* CONFIG_SMP */
multiline_comment|/* For spinlocks etc */
DECL|macro|local_irq_save
mdefine_line|#define local_irq_save(x)&t;__save_and_cli(x);
DECL|macro|local_irq_restore
mdefine_line|#define local_irq_restore(x)&t;__restore_flags(x);
DECL|macro|local_irq_disable
mdefine_line|#define local_irq_disable()&t;__cli();
DECL|macro|local_irq_enable
mdefine_line|#define local_irq_enable()&t;__sti();
multiline_comment|/*&n; * These are probably defined overly paranoid ...&n; */
DECL|macro|mb
mdefine_line|#define mb()&t;&t;&t;&t;&t;&t;&bslash;&n;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;# prevent instructions being moved around&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;sync&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.set&bslash;treorder&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;: /* no output */&t;&t;&t;&t;&bslash;&n;&t;: /* no input */&t;&t;&t;&t;&bslash;&n;&t;: &quot;memory&quot;)
DECL|macro|rmb
mdefine_line|#define rmb() mb()
DECL|macro|wmb
mdefine_line|#define wmb() mb()
macro_line|#ifdef CONFIG_SMP
DECL|macro|smp_mb
mdefine_line|#define smp_mb()&t;mb()
DECL|macro|smp_rmb
mdefine_line|#define smp_rmb()&t;rmb()
DECL|macro|smp_wmb
mdefine_line|#define smp_wmb()&t;wmb()
macro_line|#else
DECL|macro|smp_mb
mdefine_line|#define smp_mb()&t;barrier()
DECL|macro|smp_rmb
mdefine_line|#define smp_rmb()&t;barrier()
DECL|macro|smp_wmb
mdefine_line|#define smp_wmb()&t;barrier()
macro_line|#endif
DECL|macro|set_mb
mdefine_line|#define set_mb(var, value) &bslash;&n;do { var = value; mb(); } while (0)
DECL|macro|set_wmb
mdefine_line|#define set_wmb(var, value) &bslash;&n;do { var = value; wmb(); } while (0)
macro_line|#if !defined (_LANGUAGE_ASSEMBLY)
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
)paren
suffix:semicolon
macro_line|#endif /* !defined (_LANGUAGE_ASSEMBLY) */
DECL|macro|prepare_to_switch
mdefine_line|#define prepare_to_switch()&t;do { } while(0)
r_extern
id|asmlinkage
r_void
id|lazy_fpu_switch
c_func
(paren
r_void
op_star
comma
r_void
op_star
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|init_fpu
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|save_fp
c_func
(paren
r_void
op_star
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
DECL|macro|SWITCH_DO_LAZY_FPU
mdefine_line|#define SWITCH_DO_LAZY_FPU &bslash;&n;&t;if (prev-&gt;flags &amp; PF_USEDFPU) { &bslash;&n;&t;&t;lazy_fpu_switch(prev, 0); &bslash;&n;&t;&t;set_cp0_status(ST0_CU1, ~ST0_CU1); &bslash;&n;&t;&t;prev-&gt;flags &amp;= ~PF_USEDFPU; &bslash;&n;&t;}
macro_line|#else /* CONFIG_SMP */
DECL|macro|SWITCH_DO_LAZY_FPU
mdefine_line|#define SWITCH_DO_LAZY_FPU&t;do { } while(0)
macro_line|#endif /* CONFIG_SMP */
DECL|macro|switch_to
mdefine_line|#define switch_to(prev,next,last) &bslash;&n;do { &bslash;&n;&t;SWITCH_DO_LAZY_FPU; &bslash;&n;&t;(last) = resume(prev, next); &bslash;&n;} while(0)
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
l_string|&quot;.set&bslash;tnoreorder&bslash;t&bslash;t&bslash;t# xchg_u32&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tnoat&bslash;n&bslash;t&quot;
l_string|&quot;ll&bslash;t%0, %3&bslash;n&quot;
l_string|&quot;1:&bslash;tmove&bslash;t$1, %2&bslash;n&bslash;t&quot;
l_string|&quot;sc&bslash;t$1, %1&bslash;n&bslash;t&quot;
l_string|&quot;beqzl&bslash;t$1, 1b&bslash;n&bslash;t&quot;
l_string|&quot; ll&bslash;t%0, %3&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tat&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;treorder&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|val
)paren
comma
l_string|&quot;=o&quot;
(paren
op_star
id|m
)paren
comma
l_string|&quot;=r&quot;
(paren
id|dummy
)paren
suffix:colon
l_string|&quot;o&quot;
(paren
op_star
id|m
)paren
comma
l_string|&quot;2&quot;
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
l_string|&quot;.set&bslash;tnoreorder&bslash;t&bslash;t&bslash;t# xchg_u64&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tnoat&bslash;n&bslash;t&quot;
l_string|&quot;lld&bslash;t%0, %3&bslash;n&quot;
l_string|&quot;1:&bslash;tmove&bslash;t$1, %2&bslash;n&bslash;t&quot;
l_string|&quot;scd&bslash;t$1, %1&bslash;n&bslash;t&quot;
l_string|&quot;beqzl&bslash;t$1, 1b&bslash;n&bslash;t&quot;
l_string|&quot; lld&bslash;t%0, %3&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tat&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;treorder&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|val
)paren
comma
l_string|&quot;=o&quot;
(paren
op_star
id|m
)paren
comma
l_string|&quot;=r&quot;
(paren
id|dummy
)paren
suffix:colon
l_string|&quot;o&quot;
(paren
op_star
id|m
)paren
comma
l_string|&quot;2&quot;
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
r_static
id|__inline__
r_int
r_int
DECL|function|__xchg
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
macro_line|#endif /* _ASM_SYSTEM_H */
eof
