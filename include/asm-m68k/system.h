macro_line|#ifndef _M68K_SYSTEM_H
DECL|macro|_M68K_SYSTEM_H
mdefine_line|#define _M68K_SYSTEM_H
macro_line|#include &lt;linux/config.h&gt; /* get configuration macros */
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/entry.h&gt;
DECL|macro|prepare_to_switch
mdefine_line|#define prepare_to_switch()&t;do { } while(0)
multiline_comment|/*&n; * switch_to(n) should switch tasks to task ptr, first checking that&n; * ptr isn&squot;t the current task, in which case it does nothing.  This&n; * also clears the TS-flag if the task we switched to has used the&n; * math co-processor latest.&n; */
multiline_comment|/*&n; * switch_to() saves the extra registers, that are not saved&n; * automatically by SAVE_SWITCH_STACK in resume(), ie. d0-d5 and&n; * a0-a1. Some of these are used by schedule() and its predecessors&n; * and so we might get see unexpected behaviors when a task returns&n; * with unexpected register values.&n; *&n; * syscall stores these registers itself and none of them are used&n; * by syscall after the function in the syscall has been called.&n; *&n; * Beware that resume now expects *next to be in d1 and the offset of&n; * tss to be in a1. This saves a few instructions as we no longer have&n; * to push them onto the stack and read them back right after.&n; *&n; * 02/17/96 - Jes Sorensen (jds@kom.auc.dk)&n; *&n; * Changed 96/09/19 by Andreas Schwab&n; * pass prev in a0, next in a1, offset of tss in d1, and whether&n; * the mm structures are shared in d2 (to avoid atc flushing).&n; */
id|asmlinkage
r_void
id|resume
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|switch_to
mdefine_line|#define switch_to(prev,next,last) { &bslash;&n;  register void *_prev __asm__ (&quot;a0&quot;) = (prev); &bslash;&n;  register void *_next __asm__ (&quot;a1&quot;) = (next); &bslash;&n;  register void *_last __asm__ (&quot;d1&quot;); &bslash;&n;  __asm__ __volatile__(&quot;jbsr &quot; SYMBOL_NAME_STR(resume) &bslash;&n;&t;&t;       : &quot;=d&quot; (_last) : &quot;a&quot; (_prev), &quot;a&quot; (_next) &bslash;&n;&t;&t;       : &quot;d0&quot;, /* &quot;d1&quot;, */ &quot;d2&quot;, &quot;d3&quot;, &quot;d4&quot;, &quot;d5&quot;, &quot;a0&quot;, &quot;a1&quot;); &bslash;&n;  (last) = _last; &bslash;&n;}
multiline_comment|/* interrupt control.. */
macro_line|#if 0
mdefine_line|#define __sti() asm volatile (&quot;andiw %0,%%sr&quot;: : &quot;i&quot; (ALLOWINT) : &quot;memory&quot;)
macro_line|#else
macro_line|#include &lt;asm/hardirq.h&gt;
DECL|macro|__sti
mdefine_line|#define __sti() ({&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;&t;if (MACH_IS_Q40 || !local_irq_count(smp_processor_id()))              &bslash;&n;&t;&t;asm volatile (&quot;andiw %0,%%sr&quot;: : &quot;i&quot; (ALLOWINT) : &quot;memory&quot;);  &bslash;&n;})
macro_line|#endif
DECL|macro|__cli
mdefine_line|#define __cli() asm volatile (&quot;oriw  #0x0700,%%sr&quot;: : : &quot;memory&quot;)
DECL|macro|__save_flags
mdefine_line|#define __save_flags(x) asm volatile (&quot;movew %%sr,%0&quot;:&quot;=d&quot; (x) : : &quot;memory&quot;)
DECL|macro|__restore_flags
mdefine_line|#define __restore_flags(x) asm volatile (&quot;movew %0,%%sr&quot;: :&quot;d&quot; (x) : &quot;memory&quot;)
multiline_comment|/* For spinlocks etc */
DECL|macro|local_irq_save
mdefine_line|#define local_irq_save(x)&t;({ __save_flags(x); __cli(); })
DECL|macro|local_irq_restore
mdefine_line|#define local_irq_restore(x)&t;__restore_flags(x)
DECL|macro|local_irq_disable
mdefine_line|#define local_irq_disable()&t;__cli()
DECL|macro|local_irq_enable
mdefine_line|#define local_irq_enable()&t;__sti()
DECL|macro|cli
mdefine_line|#define cli()&t;&t;&t;__cli()
DECL|macro|sti
mdefine_line|#define sti()&t;&t;&t;__sti()
DECL|macro|save_flags
mdefine_line|#define save_flags(x)&t;&t;__save_flags(x)
DECL|macro|restore_flags
mdefine_line|#define restore_flags(x)&t;__restore_flags(x)
DECL|macro|save_and_cli
mdefine_line|#define save_and_cli(flags)   do { save_flags(flags); cli(); } while(0)
multiline_comment|/*&n; * Force strict CPU ordering.&n; * Not really required on m68k...&n; */
DECL|macro|nop
mdefine_line|#define nop()&t;&t;do { asm volatile (&quot;nop&quot;); barrier(); } while (0)
DECL|macro|mb
mdefine_line|#define mb()&t;&t;barrier()
DECL|macro|rmb
mdefine_line|#define rmb()&t;&t;barrier()
DECL|macro|wmb
mdefine_line|#define wmb()&t;&t;barrier()
DECL|macro|set_mb
mdefine_line|#define set_mb(var, value)    do { xchg(&amp;var, value); } while (0)
DECL|macro|set_wmb
mdefine_line|#define set_wmb(var, value)    do { var = value; wmb(); } while (0)
DECL|macro|smp_mb
mdefine_line|#define smp_mb()&t;barrier()
DECL|macro|smp_rmb
mdefine_line|#define smp_rmb()&t;barrier()
DECL|macro|smp_wmb
mdefine_line|#define smp_wmb()&t;barrier()
DECL|macro|xchg
mdefine_line|#define xchg(ptr,x) ((__typeof__(*(ptr)))__xchg((unsigned long)(x),(ptr),sizeof(*(ptr))))
DECL|macro|tas
mdefine_line|#define tas(ptr) (xchg((ptr),1))
DECL|struct|__xchg_dummy
DECL|member|a
r_struct
id|__xchg_dummy
(brace
r_int
r_int
id|a
(braket
l_int|100
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|__xg
mdefine_line|#define __xg(x) ((volatile struct __xchg_dummy *)(x))
macro_line|#ifndef CONFIG_RMW_INSNS
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
r_int
r_int
id|tmp
comma
id|flags
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
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
id|__asm__
id|__volatile__
(paren
l_string|&quot;moveb %2,%0&bslash;n&bslash;t&quot;
l_string|&quot;moveb %1,%2&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|x
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|__xg
c_func
(paren
id|ptr
)paren
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|__asm__
id|__volatile__
(paren
l_string|&quot;movew %2,%0&bslash;n&bslash;t&quot;
l_string|&quot;movew %1,%2&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|x
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|__xg
c_func
(paren
id|ptr
)paren
)paren
suffix:colon
l_string|&quot;memory&quot;
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
l_string|&quot;movel %2,%0&bslash;n&bslash;t&quot;
l_string|&quot;movel %1,%2&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|x
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|__xg
c_func
(paren
id|ptr
)paren
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|tmp
suffix:semicolon
)brace
macro_line|#else
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
l_int|1
suffix:colon
id|__asm__
id|__volatile__
(paren
l_string|&quot;moveb %2,%0&bslash;n&bslash;t&quot;
l_string|&quot;1:&bslash;n&bslash;t&quot;
l_string|&quot;casb %0,%1,%2&bslash;n&bslash;t&quot;
l_string|&quot;jne 1b&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|x
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|x
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|__xg
c_func
(paren
id|ptr
)paren
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|__asm__
id|__volatile__
(paren
l_string|&quot;movew %2,%0&bslash;n&bslash;t&quot;
l_string|&quot;1:&bslash;n&bslash;t&quot;
l_string|&quot;casw %0,%1,%2&bslash;n&bslash;t&quot;
l_string|&quot;jne 1b&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|x
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|x
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|__xg
c_func
(paren
id|ptr
)paren
)paren
suffix:colon
l_string|&quot;memory&quot;
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
l_string|&quot;movel %2,%0&bslash;n&bslash;t&quot;
l_string|&quot;1:&bslash;n&bslash;t&quot;
l_string|&quot;casl %0,%1,%2&bslash;n&bslash;t&quot;
l_string|&quot;jne 1b&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|x
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|x
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|__xg
c_func
(paren
id|ptr
)paren
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|x
suffix:semicolon
)brace
macro_line|#endif
macro_line|#endif /* _M68K_SYSTEM_H */
eof
