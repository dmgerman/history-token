multiline_comment|/* $Id: system.h,v 1.20 1999/12/06 23:13:21 ralf Exp $&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1994 - 1999 by Ralf Baechle&n; * Copyright (C) 1996 by Paul M. Antoine&n; * Copyright (C) 1994 - 1999 by Ralf Baechle&n; */
macro_line|#ifndef _ASM_SYSTEM_H
DECL|macro|_ASM_SYSTEM_H
mdefine_line|#define _ASM_SYSTEM_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/sgidefs.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
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
l_string|&quot;.set&bslash;tpush&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;treorder&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tnoat&bslash;n&bslash;t&quot;
l_string|&quot;mfc0&bslash;t$1,$12&bslash;n&bslash;t&quot;
l_string|&quot;ori&bslash;t$1,0x1f&bslash;n&bslash;t&quot;
l_string|&quot;xori&bslash;t$1,0x1e&bslash;n&bslash;t&quot;
l_string|&quot;mtc0&bslash;t$1,$12&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tpop&bslash;n&bslash;t&quot;
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
l_string|&quot;.set&bslash;tpush&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;treorder&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tnoat&bslash;n&bslash;t&quot;
l_string|&quot;mfc0&bslash;t$1,$12&bslash;n&bslash;t&quot;
l_string|&quot;ori&bslash;t$1,1&bslash;n&bslash;t&quot;
l_string|&quot;xori&bslash;t$1,1&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot;
l_string|&quot;mtc0&bslash;t$1,$12&bslash;n&bslash;t&quot;
l_string|&quot;nop&bslash;n&bslash;t&quot;
l_string|&quot;nop&bslash;n&bslash;t&quot;
l_string|&quot;nop&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tpop&bslash;n&bslash;t&quot;
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
mdefine_line|#define __save_flags(x)                  &bslash;&n;__asm__ __volatile__(                    &bslash;&n;&t;&quot;.set&bslash;tpush&bslash;n&bslash;t&quot;&t;&t; &bslash;&n;&t;&quot;.set&bslash;treorder&bslash;n&bslash;t&quot;              &bslash;&n;&t;&quot;mfc0&bslash;t%0,$12&bslash;n&bslash;t&quot;               &bslash;&n;&t;&quot;.set&bslash;tpop&bslash;n&bslash;t&quot;                      &bslash;&n;&t;: &quot;=r&quot; (x)                       &bslash;&n;&t;: /* no inputs */                &bslash;&n;&t;: &quot;memory&quot;)
DECL|macro|__save_and_cli
mdefine_line|#define __save_and_cli(x)                &bslash;&n;__asm__ __volatile__(                    &bslash;&n;&t;&quot;.set&bslash;tpush&bslash;n&bslash;t&quot;&t;&t; &bslash;&n;&t;&quot;.set&bslash;treorder&bslash;n&bslash;t&quot;              &bslash;&n;&t;&quot;.set&bslash;tnoat&bslash;n&bslash;t&quot;                 &bslash;&n;&t;&quot;mfc0&bslash;t%0,$12&bslash;n&bslash;t&quot;               &bslash;&n;&t;&quot;ori&bslash;t$1,%0,1&bslash;n&bslash;t&quot;               &bslash;&n;&t;&quot;xori&bslash;t$1,1&bslash;n&bslash;t&quot;                 &bslash;&n;&t;&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot;&t;&t; &bslash;&n;&t;&quot;mtc0&bslash;t$1,$12&bslash;n&bslash;t&quot;               &bslash;&n;&t;&quot;nop&bslash;n&bslash;t&quot;                        &bslash;&n;&t;&quot;nop&bslash;n&bslash;t&quot;                        &bslash;&n;&t;&quot;nop&bslash;n&bslash;t&quot;                        &bslash;&n;&t;&quot;.set&bslash;tpop&bslash;n&bslash;t&quot;                  &bslash;&n;&t;: &quot;=r&quot; (x)                       &bslash;&n;&t;: /* no inputs */                &bslash;&n;&t;: &quot;$1&quot;, &quot;memory&quot;)
r_extern
r_void
id|__inline__
DECL|function|__restore_flags
id|__restore_flags
c_func
(paren
r_int
id|flags
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.set&bslash;tpush&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;treorder&bslash;n&bslash;t&quot;
l_string|&quot;mfc0&bslash;t$8,$12&bslash;n&bslash;t&quot;
l_string|&quot;li&bslash;t$9,0xff00&bslash;n&bslash;t&quot;
l_string|&quot;and&bslash;t$8,$9&bslash;n&bslash;t&quot;
l_string|&quot;nor&bslash;t$9,$0,$9&bslash;n&bslash;t&quot;
l_string|&quot;and&bslash;t%0,$9&bslash;n&bslash;t&quot;
l_string|&quot;or&bslash;t%0,$8&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot;
l_string|&quot;mtc0&bslash;t%0,$12&bslash;n&bslash;t&quot;
l_string|&quot;nop&bslash;n&bslash;t&quot;
l_string|&quot;nop&bslash;n&bslash;t&quot;
l_string|&quot;nop&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tpop&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|flags
)paren
suffix:colon
l_string|&quot;$8&quot;
comma
l_string|&quot;$9&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Non-SMP versions ...&n; */
DECL|macro|sti
mdefine_line|#define sti() __sti()
DECL|macro|cli
mdefine_line|#define cli() __cli()
DECL|macro|save_flags
mdefine_line|#define save_flags(x) __save_flags(x)
DECL|macro|save_and_cli
mdefine_line|#define save_and_cli(x) __save_and_cli(x)
DECL|macro|restore_flags
mdefine_line|#define restore_flags(x) __restore_flags(x)
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
macro_line|#ifdef CONFIG_CPU_HAS_WB
macro_line|#include &lt;asm/wbflush.h&gt;
DECL|macro|rmb
mdefine_line|#define rmb()
DECL|macro|wmb
mdefine_line|#define wmb() wbflush()
DECL|macro|mb
mdefine_line|#define mb() wbflush()
macro_line|#else
DECL|macro|mb
mdefine_line|#define mb()&t;&t;&t;&t;&t;&t;&bslash;&n;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;# prevent instructions being moved around&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;# 8 nops to fool the R4400 pipeline&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&quot;nop;nop;nop;nop;nop;nop;nop;nop&bslash;n&bslash;t&quot;&t;&t;&bslash;&n;&t;&quot;.set&bslash;treorder&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;: /* no output */&t;&t;&t;&t;&bslash;&n;&t;: /* no input */&t;&t;&t;&t;&bslash;&n;&t;: &quot;memory&quot;)
DECL|macro|rmb
mdefine_line|#define rmb() mb()
DECL|macro|wmb
mdefine_line|#define wmb() mb()
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
DECL|macro|switch_to
mdefine_line|#define switch_to(prev,next,last) &bslash;&n;do { &bslash;&n;&t;(last) = resume(prev, next); &bslash;&n;} while(0)
multiline_comment|/*&n; * For 32 and 64 bit operands we can take advantage of ll and sc.&n; * FIXME: This doesn&squot;t work for R3000 machines.&n; */
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
macro_line|#if defined(CONFIG_CPU_HAS_LLSC)
r_int
r_int
id|dummy
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tnoat&bslash;n&bslash;t&quot;
l_string|&quot;ll&bslash;t%0,(%1)&bslash;n&quot;
l_string|&quot;1:&bslash;tmove&bslash;t$1,%2&bslash;n&bslash;t&quot;
l_string|&quot;sc&bslash;t$1,(%1)&bslash;n&bslash;t&quot;
l_string|&quot;beqzl&bslash;t$1,1b&bslash;n&bslash;t&quot;
l_string|&quot;ll&bslash;t%0,(%1)&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tat&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;treorder&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|val
)paren
comma
l_string|&quot;=r&quot;
(paren
id|m
)paren
comma
l_string|&quot;=r&quot;
(paren
id|dummy
)paren
suffix:colon
l_string|&quot;1&quot;
(paren
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
macro_line|#else
r_int
r_int
id|flags
comma
id|retval
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
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
macro_line|#endif /* Processor-dependent optimization */
)brace
multiline_comment|/*&n; * Only used for 64 bit kernel.&n; */
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
l_string|&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tnoat&bslash;n&bslash;t&quot;
l_string|&quot;lld&bslash;t%0,(%1)&bslash;n&quot;
l_string|&quot;1:&bslash;tmove&bslash;t$1,%2&bslash;n&bslash;t&quot;
l_string|&quot;scd&bslash;t$1,(%1)&bslash;n&bslash;t&quot;
l_string|&quot;beqzl&bslash;t$1,1b&bslash;n&bslash;t&quot;
l_string|&quot;lld&bslash;t%0,(%1)&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tat&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;treorder&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|val
)paren
comma
l_string|&quot;=r&quot;
(paren
id|m
)paren
comma
l_string|&quot;=r&quot;
(paren
id|dummy
)paren
suffix:colon
l_string|&quot;1&quot;
(paren
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
multiline_comment|/*&n; * This function doesn&squot;t exist, so you&squot;ll get a linker error&n; * if something tries to do an invalid xchg().&n; *&n; * This only works if the compiler isn&squot;t horribly bad at optimizing.&n; * gcc-2.5.8 reportedly can&squot;t handle this, but I define that one to&n; * be dead anyway.&n; */
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
id|__inline__
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
macro_line|#if defined(__mips64)
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
macro_line|#endif
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
id|where
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
id|where
comma
r_int
r_int
id|line
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
DECL|macro|die
mdefine_line|#define die(msg, regs)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__die(msg, regs, __FILE__ &quot;:&quot;__FUNCTION__, __LINE__)
DECL|macro|die_if_kernel
mdefine_line|#define die_if_kernel(msg, regs)&t;&t;&t;&t;&t;&bslash;&n;&t;__die_if_kernel(msg, regs, __FILE__ &quot;:&quot;__FUNCTION__, __LINE__)
macro_line|#endif /* _ASM_SYSTEM_H */
eof
