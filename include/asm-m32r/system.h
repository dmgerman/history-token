macro_line|#ifndef _ASM_M32R_SYSTEM_H
DECL|macro|_ASM_M32R_SYSTEM_H
mdefine_line|#define _ASM_M32R_SYSTEM_H
multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2001  by Hiroyuki Kondo, Hirokazu Takata, and Hitoshi Yamamoto&n; * Copyright (C) 2004  Hirokazu Takata &lt;takata at linux-m32r.org&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * switch_to(prev, next) should switch from task `prev&squot; to `next&squot;&n; * `prev&squot; will never be the same as `next&squot;.&n; *&n; * `next&squot; and `prev&squot; should be struct task_struct, but it isn&squot;t always defined&n; */
macro_line|#ifndef CONFIG_SMP
DECL|macro|prepare_to_switch
mdefine_line|#define prepare_to_switch()  do { } while(0)
macro_line|#endif&t;/* not CONFIG_SMP */
DECL|macro|switch_to
mdefine_line|#define switch_to(prev, next, last)  do { &bslash;&n;&t;register unsigned long  arg0 __asm__ (&quot;r0&quot;) = (unsigned long)prev; &bslash;&n;&t;register unsigned long  arg1 __asm__ (&quot;r1&quot;) = (unsigned long)next; &bslash;&n;&t;register unsigned long  *oldsp __asm__ (&quot;r2&quot;) = &amp;(prev-&gt;thread.sp); &bslash;&n;&t;register unsigned long  *newsp __asm__ (&quot;r3&quot;) = &amp;(next-&gt;thread.sp); &bslash;&n;&t;register unsigned long  *oldlr __asm__ (&quot;r4&quot;) = &amp;(prev-&gt;thread.lr); &bslash;&n;&t;register unsigned long  *newlr __asm__ (&quot;r5&quot;) = &amp;(next-&gt;thread.lr); &bslash;&n;&t;register struct task_struct  *__last __asm__ (&quot;r6&quot;); &bslash;&n;&t;__asm__ __volatile__ ( &bslash;&n;&t;&t;&quot;st     r8, @-r15                                 &bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&quot;st     r9, @-r15                                 &bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&quot;st    r10, @-r15                                 &bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&quot;st    r11, @-r15                                 &bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&quot;st    r12, @-r15                                 &bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&quot;st    r13, @-r15                                 &bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&quot;st    r14, @-r15                                 &bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&quot;seth  r14, #high(1f)                             &bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&quot;or3   r14, r14, #low(1f)                         &bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&quot;st    r14, @r4    ; store old LR                 &bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&quot;st    r15, @r2    ; store old SP                 &bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&quot;ld    r15, @r3    ; load new SP                  &bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&quot;st     r0, @-r15  ; store &squot;prev&squot; onto new stack  &bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&quot;ld    r14, @r5    ; load new LR                  &bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&quot;jmp   r14                                        &bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&quot;.fillinsn                                        &bslash;n  &quot; &bslash;&n;&t;&t;&quot;1:                                               &bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&quot;ld     r6, @r15+  ; load &squot;prev&squot; from new stack   &bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&quot;ld    r14, @r15+                                 &bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&quot;ld    r13, @r15+                                 &bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&quot;ld    r12, @r15+                                 &bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&quot;ld    r11, @r15+                                 &bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&quot;ld    r10, @r15+                                 &bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&quot;ld     r9, @r15+                                 &bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&quot;ld     r8, @r15+                                 &bslash;n&bslash;t&quot; &bslash;&n;&t;&t;: &quot;=&amp;r&quot; (__last) &bslash;&n;&t;&t;: &quot;r&quot; (arg0), &quot;r&quot; (arg1), &quot;r&quot; (oldsp), &quot;r&quot; (newsp), &bslash;&n;&t;&t;  &quot;r&quot; (oldlr), &quot;r&quot; (newlr) &bslash;&n;&t;&t;: &quot;memory&quot; &bslash;&n;&t;); &bslash;&n;&t;last = __last; &bslash;&n;} while(0)
multiline_comment|/* Interrupt Control */
macro_line|#if !defined(CONFIG_CHIP_M32102)
DECL|macro|local_irq_enable
mdefine_line|#define local_irq_enable() &bslash;&n;&t;__asm__ __volatile__ (&quot;setpsw #0x40 -&gt; nop&quot;: : :&quot;memory&quot;)
DECL|macro|local_irq_disable
mdefine_line|#define local_irq_disable() &bslash;&n;&t;__asm__ __volatile__ (&quot;clrpsw #0x40 -&gt; nop&quot;: : :&quot;memory&quot;)
macro_line|#else&t;/* CONFIG_CHIP_M32102 */
DECL|function|local_irq_enable
r_static
r_inline
r_void
id|local_irq_enable
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|tmpreg
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;mvfc&t;%0, psw;&t;&t;&bslash;n&bslash;t&quot;
l_string|&quot;or3&t;%0, %0, #0x0040;&t;&bslash;n&bslash;t&quot;
l_string|&quot;mvtc&t;%0, psw;&t;&t;&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|tmpreg
)paren
suffix:colon
suffix:colon
l_string|&quot;cbit&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
DECL|function|local_irq_disable
r_static
r_inline
r_void
id|local_irq_disable
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|tmpreg0
comma
id|tmpreg1
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;ld24&t;%0, #0&t;; Use 32-bit insn. &bslash;n&bslash;t&quot;
l_string|&quot;mvfc&t;%1, psw&t;; No interrupt can be accepted here. &bslash;n&bslash;t&quot;
l_string|&quot;mvtc&t;%0, psw&t;&bslash;n&bslash;t&quot;
l_string|&quot;and3&t;%0, %1, #0xffbf&t;&bslash;n&bslash;t&quot;
l_string|&quot;mvtc&t;%0, psw&t;&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|tmpreg0
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|tmpreg1
)paren
suffix:colon
suffix:colon
l_string|&quot;cbit&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif&t;/* CONFIG_CHIP_M32102 */
DECL|macro|local_save_flags
mdefine_line|#define local_save_flags(x) &bslash;&n;&t;__asm__ __volatile__(&quot;mvfc %0,psw&quot; : &quot;=r&quot;(x) : /* no input */)
DECL|macro|local_irq_restore
mdefine_line|#define local_irq_restore(x) &bslash;&n;&t;__asm__ __volatile__(&quot;mvtc %0,psw&quot; : /* no outputs */ &bslash;&n;&t;&t;: &quot;r&quot; (x) : &quot;cbit&quot;, &quot;memory&quot;)
macro_line|#if !defined(CONFIG_CHIP_M32102)
DECL|macro|local_irq_save
mdefine_line|#define local_irq_save(x)&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&bslash;&n;  &t;&t;&quot;mvfc&t;%0, psw;&t;&t;&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;  &t;&quot;clrpsw&t;#0x40 -&gt; nop;&t;&t;&bslash;n&bslash;t&quot;&t;&bslash;&n;  &t;&t;: &quot;=r&quot; (x) : /* no input */ : &quot;memory&quot;)
macro_line|#else&t;/* CONFIG_CHIP_M32102 */
DECL|macro|local_irq_save
mdefine_line|#define local_irq_save(x) &t;&t;&t;&t;&bslash;&n;&t;({&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;unsigned long tmpreg;&t;&t;&t;&bslash;&n;&t;&t;__asm__ __volatile__( &t;&t;&t;&bslash;&n;&t;&t;&t;&quot;ld24&t;%1, #0 &bslash;n&bslash;t&quot; &t;&t;&bslash;&n;&t;&t;&t;&quot;mvfc&t;%0, psw &bslash;n&bslash;t&quot;&t;&t;&bslash;&n;&t;&t;&t;&quot;mvtc&t;%1, psw &bslash;n&bslash;t&quot;&t;&t;&bslash;&n;&t;&t;&t;&quot;and3&t;%1, %0, #0xffbf &bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&t;&t;&quot;mvtc&t;%1, psw &bslash;n&bslash;t&quot; &t;&t;&bslash;&n;&t;&t;&t;: &quot;=r&quot; (x), &quot;=&amp;r&quot; (tmpreg)&t;&bslash;&n;&t;&t;&t;: : &quot;cbit&quot;, &quot;memory&quot;);&t;&t;&bslash;&n;&t;})
macro_line|#endif&t;/* CONFIG_CHIP_M32102 */
DECL|macro|irqs_disabled
mdefine_line|#define irqs_disabled()&t;&t;&t;&t;&t;&bslash;&n;&t;({&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;unsigned long flags;&t;&t;&t;&bslash;&n;&t;&t;local_save_flags(flags);&t;&t;&bslash;&n;&t;&t;!(flags &amp; 0x40);&t;&t;&t;&bslash;&n;&t;})
macro_line|#endif  /* __KERNEL__ */
DECL|macro|nop
mdefine_line|#define nop()&t;__asm__ __volatile__ (&quot;nop&quot; : : )
DECL|macro|xchg
mdefine_line|#define xchg(ptr,x) &bslash;&n;&t;((__typeof__(*(ptr)))__xchg((unsigned long)(x),(ptr),sizeof(*(ptr))))
DECL|macro|tas
mdefine_line|#define tas(ptr)&t;(xchg((ptr),1))
macro_line|#ifdef CONFIG_SMP
r_extern
r_void
id|__xchg_called_with_bad_pointer
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_CHIP_M32700_TS1
DECL|macro|DCACHE_CLEAR
mdefine_line|#define DCACHE_CLEAR(reg0, reg1, addr)&t;&t;&t;&t;&bslash;&n;&t;&quot;seth&t;&quot;reg1&quot;, #high(dcache_dummy);&t;&t;&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&quot;or3&t;&quot;reg1&quot;, &quot;reg1&quot;, #low(dcache_dummy);&t;&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&quot;lock&t;&quot;reg0&quot;, @&quot;reg1&quot;;&t;&t;&t;&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&quot;add3&t;&quot;reg0&quot;, &quot;addr&quot;, #0x1000;&t;&t;&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&quot;ld&t;&quot;reg0&quot;, @&quot;reg0&quot;;&t;&t;&t;&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&quot;add3&t;&quot;reg0&quot;, &quot;addr&quot;, #0x2000;&t;&t;&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&quot;ld&t;&quot;reg0&quot;, @&quot;reg0&quot;;&t;&t;&t;&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&quot;unlock&t;&quot;reg0&quot;, @&quot;reg1&quot;;&t;&t;&t;&bslash;n&bslash;t&quot;
multiline_comment|/* FIXME: This workaround code cannot handle kenrel modules&n;&t; * correctly under SMP environment.&n;&t; */
macro_line|#else&t;/* CONFIG_CHIP_M32700_TS1 */
DECL|macro|DCACHE_CLEAR
mdefine_line|#define DCACHE_CLEAR(reg0, reg1, addr)
macro_line|#endif&t;/* CONFIG_CHIP_M32700_TS1 */
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
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|tmp
op_assign
l_int|0
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
macro_line|#ifndef CONFIG_SMP
r_case
l_int|1
suffix:colon
id|__asm__
id|__volatile__
(paren
l_string|&quot;ldb&t;%0, @%2 &bslash;n&bslash;t&quot;
l_string|&quot;stb&t;%1, @%2 &bslash;n&bslash;t&quot;
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
l_string|&quot;r&quot;
(paren
id|ptr
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
l_string|&quot;ldh&t;%0, @%2 &bslash;n&bslash;t&quot;
l_string|&quot;sth&t;%1, @%2 &bslash;n&bslash;t&quot;
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
l_string|&quot;r&quot;
(paren
id|ptr
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
l_string|&quot;ld&t;%0, @%2 &bslash;n&bslash;t&quot;
l_string|&quot;st&t;%1, @%2 &bslash;n&bslash;t&quot;
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
l_string|&quot;r&quot;
(paren
id|ptr
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#else  /* CONFIG_SMP */
r_case
l_int|4
suffix:colon
id|__asm__
id|__volatile__
(paren
id|DCACHE_CLEAR
c_func
(paren
l_string|&quot;%0&quot;
comma
l_string|&quot;r4&quot;
comma
l_string|&quot;%2&quot;
)paren
l_string|&quot;lock&t;%0, @%2;&t;&bslash;n&bslash;t&quot;
l_string|&quot;unlock&t;%1, @%2;&t;&bslash;n&bslash;t&quot;
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
l_string|&quot;r&quot;
(paren
id|ptr
)paren
suffix:colon
l_string|&quot;memory&quot;
macro_line|#ifdef CONFIG_CHIP_M32700_TS1
comma
l_string|&quot;r4&quot;
macro_line|#endif&t;/* CONFIG_CHIP_M32700_TS1 */
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|__xchg_called_with_bad_pointer
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif  /* CONFIG_SMP */
)brace
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
(paren
id|tmp
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Memory barrier.&n; *&n; * mb() prevents loads and stores being reordered across this point.&n; * rmb() prevents loads being reordered across this point.&n; * wmb() prevents stores being reordered across this point.&n; */
DECL|macro|mb
mdefine_line|#define mb()   barrier()
DECL|macro|rmb
mdefine_line|#define rmb()  mb()
DECL|macro|wmb
mdefine_line|#define wmb()  mb()
multiline_comment|/**&n; * read_barrier_depends - Flush all pending reads that subsequents reads&n; * depend on.&n; *&n; * No data-dependent reads from memory-like regions are ever reordered&n; * over this barrier.  All reads preceding this primitive are guaranteed&n; * to access memory (but not necessarily other CPUs&squot; caches) before any&n; * reads following this primitive that depend on the data return by&n; * any of the preceding reads.  This primitive is much lighter weight than&n; * rmb() on most CPUs, and is never heavier weight than is&n; * rmb().&n; *&n; * These ordering constraints are respected by both the local CPU&n; * and the compiler.&n; *&n; * Ordering is not guaranteed by anything other than these primitives,&n; * not even by data dependencies.  See the documentation for&n; * memory_barrier() for examples and URLs to more information.&n; *&n; * For example, the following code would force ordering (the initial&n; * value of &quot;a&quot; is zero, &quot;b&quot; is one, and &quot;p&quot; is &quot;&amp;a&quot;):&n; *&n; * &lt;programlisting&gt;&n; *      CPU 0                           CPU 1&n; *&n; *      b = 2;&n; *      memory_barrier();&n; *      p = &amp;b;                         q = p;&n; *                                      read_barrier_depends();&n; *                                      d = *q;&n; * &lt;/programlisting&gt;&n; *&n; *&n; * because the read of &quot;*q&quot; depends on the read of &quot;p&quot; and these&n; * two reads are separated by a read_barrier_depends().  However,&n; * the following code, with the same initial values for &quot;a&quot; and &quot;b&quot;:&n; *&n; * &lt;programlisting&gt;&n; *      CPU 0                           CPU 1&n; *&n; *      a = 2;&n; *      memory_barrier();&n; *      b = 3;                          y = b;&n; *                                      read_barrier_depends();&n; *                                      x = a;&n; * &lt;/programlisting&gt;&n; *&n; * does not enforce ordering, since there is no data dependency between&n; * the read of &quot;a&quot; and the read of &quot;b&quot;.  Therefore, on some CPUs, such&n; * as Alpha, &quot;y&quot; could be set to 3 and &quot;x&quot; to 0.  Use rmb()&n; * in cases like thiswhere there are no data dependencies.&n; **/
DECL|macro|read_barrier_depends
mdefine_line|#define read_barrier_depends()&t;do { } while (0)
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
mdefine_line|#define smp_read_barrier_depends()&t;do { } while (0)
macro_line|#endif
DECL|macro|set_mb
mdefine_line|#define set_mb(var, value) do { xchg(&amp;var, value); } while (0)
DECL|macro|set_wmb
mdefine_line|#define set_wmb(var, value) do { var = value; wmb(); } while (0)
DECL|macro|arch_align_stack
mdefine_line|#define arch_align_stack(x) (x)
macro_line|#endif  /* _ASM_M32R_SYSTEM_H */
eof
