multiline_comment|/*&n; * include/asm-v850/system.h -- Low-level interrupt/thread ops&n; *&n; *  Copyright (C) 2001,02,03  NEC Electronics Corporation&n; *  Copyright (C) 2001,02,03  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#ifndef __V850_SYSTEM_H__
DECL|macro|__V850_SYSTEM_H__
mdefine_line|#define __V850_SYSTEM_H__
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
DECL|macro|prepare_to_switch
mdefine_line|#define prepare_to_switch()&t;do { } while (0)
multiline_comment|/*&n; * switch_to(n) should switch tasks to task ptr, first checking that&n; * ptr isn&squot;t the current task, in which case it does nothing.&n; */
r_struct
id|thread_struct
suffix:semicolon
r_extern
r_void
op_star
id|switch_thread
(paren
r_struct
id|thread_struct
op_star
id|last
comma
r_struct
id|thread_struct
op_star
id|next
)paren
suffix:semicolon
DECL|macro|switch_to
mdefine_line|#define switch_to(prev,next,last)&t;&t;&t;&t;&t;      &bslash;&n;  do {&t;&t;&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;        if (prev != next) {&t;&t;&t;&t;&t;&t;      &bslash;&n; &t;&t;(last) = switch_thread (&amp;prev-&gt;thread, &amp;next-&gt;thread);&t;      &bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;      &bslash;&n;  } while (0)
multiline_comment|/* Enable/disable interrupts.  */
DECL|macro|local_irq_enable
mdefine_line|#define local_irq_enable()&t;__asm__ __volatile__ (&quot;ei&quot;)
DECL|macro|local_irq_disable
mdefine_line|#define local_irq_disable()&t;__asm__ __volatile__ (&quot;di&quot;)
DECL|macro|local_save_flags
mdefine_line|#define local_save_flags(flags) &bslash;&n;  __asm__ __volatile__ (&quot;stsr %1, %0&quot; : &quot;=r&quot; (flags) : &quot;i&quot; (SR_PSW))
DECL|macro|local_restore_flags
mdefine_line|#define local_restore_flags(flags) &bslash;&n;  __asm__ __volatile__ (&quot;ldsr %0, %1&quot; :: &quot;r&quot; (flags), &quot;i&quot; (SR_PSW))
multiline_comment|/* For spinlocks etc */
DECL|macro|local_irq_save
mdefine_line|#define&t;local_irq_save(flags) &bslash;&n;  do { local_save_flags (flags); local_irq_disable (); } while (0) 
DECL|macro|local_irq_restore
mdefine_line|#define local_irq_restore(flags) &bslash;&n;  local_restore_flags (flags);
DECL|function|irqs_disabled
r_static
r_inline
r_int
id|irqs_disabled
(paren
r_void
)paren
(brace
r_int
id|flags
suffix:semicolon
id|local_save_flags
(paren
id|flags
)paren
suffix:semicolon
r_return
op_logical_neg
op_logical_neg
(paren
id|flags
op_amp
l_int|0x20
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Force strict CPU ordering.&n; * Not really required on v850...&n; */
DECL|macro|nop
mdefine_line|#define nop()&t;&t;&t;__asm__ __volatile__ (&quot;nop&quot;)
DECL|macro|mb
mdefine_line|#define mb()&t;&t;&t;__asm__ __volatile__ (&quot;&quot; ::: &quot;memory&quot;)
DECL|macro|rmb
mdefine_line|#define rmb()&t;&t;&t;mb ()
DECL|macro|wmb
mdefine_line|#define wmb()&t;&t;&t;mb ()
DECL|macro|read_barrier_depends
mdefine_line|#define read_barrier_depends()&t;((void)0)
DECL|macro|set_rmb
mdefine_line|#define set_rmb(var, value)&t;do { xchg (&amp;var, value); } while (0)
DECL|macro|set_mb
mdefine_line|#define set_mb(var, value)&t;set_rmb (var, value)
DECL|macro|set_wmb
mdefine_line|#define set_wmb(var, value)&t;do { var = value; wmb (); } while (0)
DECL|macro|smp_mb
mdefine_line|#define smp_mb()&t;mb ()
DECL|macro|smp_rmb
mdefine_line|#define smp_rmb()&t;rmb ()
DECL|macro|smp_wmb
mdefine_line|#define smp_wmb()&t;wmb ()
DECL|macro|smp_read_barrier_depends
mdefine_line|#define smp_read_barrier_depends()&t;read_barrier_depends()
DECL|macro|xchg
mdefine_line|#define xchg(ptr, with) &bslash;&n;  ((__typeof__ (*(ptr)))__xchg ((unsigned long)(with), (ptr), sizeof (*(ptr))))
DECL|macro|tas
mdefine_line|#define tas(ptr) (xchg ((ptr), 1))
DECL|function|__xchg
r_extern
r_inline
r_int
r_int
id|__xchg
(paren
r_int
r_int
id|with
comma
id|__volatile__
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
id|tmp
op_assign
op_star
(paren
r_int
r_char
op_star
)paren
id|ptr
suffix:semicolon
op_star
(paren
r_int
r_char
op_star
)paren
id|ptr
op_assign
id|with
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|tmp
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
id|ptr
suffix:semicolon
op_star
(paren
r_int
r_int
op_star
)paren
id|ptr
op_assign
id|with
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|tmp
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
id|ptr
suffix:semicolon
op_star
(paren
r_int
r_int
op_star
)paren
id|ptr
op_assign
id|with
suffix:semicolon
r_break
suffix:semicolon
)brace
id|local_irq_restore
(paren
id|flags
)paren
suffix:semicolon
r_return
id|tmp
suffix:semicolon
)brace
DECL|macro|arch_align_stack
mdefine_line|#define arch_align_stack(x) (x)
macro_line|#endif /* __V850_SYSTEM_H__ */
eof
