macro_line|#ifndef _H8300_SYSTEM_H
DECL|macro|_H8300_SYSTEM_H
mdefine_line|#define _H8300_SYSTEM_H
macro_line|#include &lt;linux/config.h&gt; /* get configuration macros */
macro_line|#include &lt;linux/linkage.h&gt;
DECL|macro|prepare_to_switch
mdefine_line|#define prepare_to_switch()&t;do { } while(0)
multiline_comment|/*&n; * switch_to(n) should switch tasks to task ptr, first checking that&n; * ptr isn&squot;t the current task, in which case it does nothing.  This&n; * also clears the TS-flag if the task we switched to has used the&n; * math co-processor latest.&n; */
multiline_comment|/*&n; * switch_to() saves the extra registers, that are not saved&n; * automatically by SAVE_SWITCH_STACK in resume(), ie. d0-d5 and&n; * a0-a1. Some of these are used by schedule() and its predecessors&n; * and so we might get see unexpected behaviors when a task returns&n; * with unexpected register values.&n; *&n; * syscall stores these registers itself and none of them are used&n; * by syscall after the function in the syscall has been called.&n; *&n; * Beware that resume now expects *next to be in d1 and the offset of&n; * tss to be in a1. This saves a few instructions as we no longer have&n; * to push them onto the stack and read them back right after.&n; *&n; * 02/17/96 - Jes Sorensen (jds@kom.auc.dk)&n; *&n; * Changed 96/09/19 by Andreas Schwab&n; * pass prev in a0, next in a1, offset of tss in d1, and whether&n; * the mm structures are shared in d2 (to avoid atc flushing).&n; *&n; * H8/300 Porting 2002/09/04 Yoshinori Sato&n; */
id|asmlinkage
r_void
id|resume
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|switch_to
mdefine_line|#define switch_to(prev,next,last) {                         &bslash;&n;  void *_last;&t;&t;&t;&t;&t;&t;    &bslash;&n;  __asm__ __volatile__(&t;&t;&t;&t;&t;    &bslash;&n;  &t;&t;&t;&quot;mov.l&t;%1, er0&bslash;n&bslash;t&quot;&t;&t;    &bslash;&n;&t;&t;&t;&quot;mov.l&t;%2, er1&bslash;n&bslash;t&quot;&t;&t;    &bslash;&n;                        &quot;mov.l  %3, er2&bslash;n&bslash;t&quot;                &bslash;&n;&t;&t;&t;&quot;jsr @_resume&bslash;n&bslash;t&quot;                  &bslash;&n;                        &quot;mov.l  er2,%0&bslash;n&bslash;t&quot;                 &bslash;&n;&t;&t;       : &quot;=r&quot; (_last)&t;&t;&t;    &bslash;&n;&t;&t;       : &quot;r&quot; (&amp;(prev-&gt;thread)),&t;&t;    &bslash;&n;&t;&t;&t; &quot;r&quot; (&amp;(next-&gt;thread)),&t;&t;    &bslash;&n;                         &quot;g&quot; (prev)                         &bslash;&n;&t;&t;       : &quot;cc&quot;, &quot;er0&quot;, &quot;er1&quot;, &quot;er2&quot;, &quot;er3&quot;); &bslash;&n;  (last) = _last; &t;&t;&t;&t;&t;    &bslash;&n;}
DECL|macro|__sti
mdefine_line|#define __sti() asm volatile (&quot;andc #0x7f,ccr&quot;)
DECL|macro|__cli
mdefine_line|#define __cli() asm volatile (&quot;orc  #0x80,ccr&quot;)
DECL|macro|__save_flags
mdefine_line|#define __save_flags(x) &bslash;&n;       asm volatile (&quot;stc ccr,%w0&quot;:&quot;=r&quot; (x))
DECL|macro|__restore_flags
mdefine_line|#define __restore_flags(x) &bslash;&n;       asm volatile (&quot;ldc %w0,ccr&quot;: :&quot;r&quot; (x))
DECL|macro|irqs_disabled
mdefine_line|#define&t;irqs_disabled()&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned char flags;&t;&t;&bslash;&n;&t;__save_flags(flags);&t;        &bslash;&n;&t;((flags &amp; 0x80) == 0x80);&t;&bslash;&n;})
DECL|macro|iret
mdefine_line|#define iret() __asm__ __volatile__ (&quot;rte&quot;: : :&quot;memory&quot;, &quot;sp&quot;, &quot;cc&quot;)
multiline_comment|/* For spinlocks etc */
DECL|macro|local_irq_disable
mdefine_line|#define local_irq_disable()&t;__cli()
DECL|macro|local_irq_enable
mdefine_line|#define local_irq_enable()      __sti()
DECL|macro|local_irq_save
mdefine_line|#define local_irq_save(x)&t;({ __save_flags(x); local_irq_disable(); })
DECL|macro|local_irq_restore
mdefine_line|#define local_irq_restore(x)&t;__restore_flags(x)
DECL|macro|local_save_flags
mdefine_line|#define local_save_flags(x)     __save_flags(x)
multiline_comment|/*&n; * Force strict CPU ordering.&n; * Not really required on H8...&n; */
DECL|macro|nop
mdefine_line|#define nop()  asm volatile (&quot;nop&quot;::)
DECL|macro|mb
mdefine_line|#define mb()   asm volatile (&quot;&quot;   : : :&quot;memory&quot;)
DECL|macro|rmb
mdefine_line|#define rmb()  asm volatile (&quot;&quot;   : : :&quot;memory&quot;)
DECL|macro|wmb
mdefine_line|#define wmb()  asm volatile (&quot;&quot;   : : :&quot;memory&quot;)
DECL|macro|set_rmb
mdefine_line|#define set_rmb(var, value)    do { xchg(&amp;var, value); } while (0)
DECL|macro|set_mb
mdefine_line|#define set_mb(var, value)     set_rmb(var, value)
DECL|macro|set_wmb
mdefine_line|#define set_wmb(var, value)    do { var = value; wmb(); } while (0)
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
id|local_irq_save
c_func
(paren
id|flags
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
l_string|&quot;mov.b %2,%0&bslash;n&bslash;t&quot;
l_string|&quot;mov.b %1,%2&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;r&quot;
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
l_string|&quot;mov.w %2,%0&bslash;n&bslash;t&quot;
l_string|&quot;mov.w %1,%2&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;r&quot;
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
l_string|&quot;mov.l %2,%0&bslash;n&bslash;t&quot;
l_string|&quot;mov.l %1,%2&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;r&quot;
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
r_default
suffix:colon
id|tmp
op_assign
l_int|0
suffix:semicolon
)brace
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|tmp
suffix:semicolon
)brace
DECL|macro|HARD_RESET_NOW
mdefine_line|#define HARD_RESET_NOW() ({&t;&t;&bslash;&n;        local_irq_disable();&t;&t;&bslash;&n;        asm(&quot;jmp @@0&quot;);&t;&t;&t;&bslash;&n;})
DECL|macro|arch_align_stack
mdefine_line|#define arch_align_stack(x) (x)
macro_line|#endif /* _H8300_SYSTEM_H */
eof
