macro_line|#ifndef _M68KNOMMU_SYSTEM_H
DECL|macro|_M68KNOMMU_SYSTEM_H
mdefine_line|#define _M68KNOMMU_SYSTEM_H
macro_line|#include &lt;linux/config.h&gt; /* get configuration macros */
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/entry.h&gt;
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
mdefine_line|#define switch_to(prev,next,last)&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  void *_last;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  __asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;  &t;&quot;movel&t;%1, %%a0&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;movel&t;%2, %%a1&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;jbsr resume&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;movel&t;%%d1, %0&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;       : &quot;=d&quot; (_last)&t;&t;&t;&t;&t;&t;&bslash;&n;       : &quot;d&quot; (prev), &quot;d&quot; (next)&t;&t;&t;&t;&t;&bslash;&n;       : &quot;cc&quot;, &quot;d0&quot;, &quot;d1&quot;, &quot;d2&quot;, &quot;d3&quot;, &quot;d4&quot;, &quot;d5&quot;, &quot;a0&quot;, &quot;a1&quot;);&t;&bslash;&n;  (last) = _last;&t;&t;&t;&t;&t;&t;&bslash;&n;}
macro_line|#ifdef CONFIG_COLDFIRE
DECL|macro|local_irq_enable
mdefine_line|#define local_irq_enable() __asm__ __volatile__ (&t;&t;&bslash;&n;&t;&quot;move %/sr,%%d0&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;andi.l #0xf8ff,%%d0&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;move %%d0,%/sr&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;: /* no outputs */&t;&t;&t;&t;&t;&bslash;&n;&t;:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;        : &quot;cc&quot;, &quot;%d0&quot;, &quot;memory&quot;)
DECL|macro|local_irq_disable
mdefine_line|#define local_irq_disable() __asm__ __volatile__ (&t;&t;&bslash;&n;&t;&quot;move %/sr,%%d0&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;ori.l  #0x0700,%%d0&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;move %%d0,%/sr&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;: /* no inputs */&t;&t;&t;&t;&t;&bslash;&n;&t;:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;cc&quot;, &quot;%d0&quot;, &quot;memory&quot;)
macro_line|#else
multiline_comment|/* portable version */
multiline_comment|/* FIXME - see entry.h*/
DECL|macro|ALLOWINT
mdefine_line|#define ALLOWINT 0xf8ff
DECL|macro|local_irq_enable
mdefine_line|#define local_irq_enable() asm volatile (&quot;andiw %0,%%sr&quot;: : &quot;i&quot; (ALLOWINT) : &quot;memory&quot;)
DECL|macro|local_irq_disable
mdefine_line|#define local_irq_disable() asm volatile (&quot;oriw  #0x0700,%%sr&quot;: : : &quot;memory&quot;)
macro_line|#endif
DECL|macro|local_save_flags
mdefine_line|#define local_save_flags(x) asm volatile (&quot;movew %%sr,%0&quot;:&quot;=d&quot; (x) : : &quot;memory&quot;)
DECL|macro|local_irq_restore
mdefine_line|#define local_irq_restore(x) asm volatile (&quot;movew %0,%%sr&quot;: :&quot;d&quot; (x) : &quot;memory&quot;)
multiline_comment|/* For spinlocks etc */
DECL|macro|local_irq_save
mdefine_line|#define local_irq_save(x) do { local_save_flags(x); local_irq_disable(); } while (0)
DECL|macro|irqs_disabled
mdefine_line|#define&t;irqs_disabled()&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long flags;&t;&t;&bslash;&n;&t;local_save_flags(flags);&t;&bslash;&n;&t;((flags &amp; 0x0700) == 0x0700);&t;&bslash;&n;})
DECL|macro|iret
mdefine_line|#define iret() __asm__ __volatile__ (&quot;rte&quot;: : :&quot;memory&quot;, &quot;sp&quot;, &quot;cc&quot;)
multiline_comment|/*&n; * Force strict CPU ordering.&n; * Not really required on m68k...&n; */
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
multiline_comment|/*&n; * Atomic compare and exchange.  Compare OLD with MEM, if identical,&n; * store NEW in MEM.  Return the initial value in MEM.  Success is&n; * indicated by comparing RETURN with OLD.&n; */
DECL|macro|__HAVE_ARCH_CMPXCHG
mdefine_line|#define __HAVE_ARCH_CMPXCHG&t;1
r_static
id|__inline__
r_int
r_int
DECL|function|cmpxchg
id|cmpxchg
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
r_int
id|flags
suffix:semicolon
r_int
id|prev
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|prev
op_assign
op_star
id|p
)paren
op_eq
id|old
)paren
op_star
id|p
op_assign
r_new
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|prev
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_M68332
DECL|macro|HARD_RESET_NOW
mdefine_line|#define HARD_RESET_NOW() ({&t;&t;&bslash;&n;        local_irq_disable();&t;&t;&bslash;&n;        asm(&quot;&t;&t;&t;&t;&bslash;&n;&t;movew   #0x0000, 0xfffa6a;&t;&bslash;&n;        reset;&t;&t;&t;&t;&bslash;&n;        /*movew #0x1557, 0xfffa44;*/&t;&bslash;&n;        /*movew #0x0155, 0xfffa46;*/&t;&bslash;&n;        moveal #0, %a0;&t;&t;&t;&bslash;&n;        movec %a0, %vbr;&t;&t;&bslash;&n;        moveal 0, %sp;&t;&t;&t;&bslash;&n;        moveal 4, %a0;&t;&t;&t;&bslash;&n;        jmp (%a0);&t;&t;&t;&bslash;&n;        &quot;);&t;&t;&t;&t;&bslash;&n;})
macro_line|#endif
macro_line|#if defined( CONFIG_M68328 ) || defined( CONFIG_M68EZ328 ) || &bslash;&n;&t;defined (CONFIG_M68360) || defined( CONFIG_M68VZ328 )
DECL|macro|HARD_RESET_NOW
mdefine_line|#define HARD_RESET_NOW() ({&t;&t;&bslash;&n;        local_irq_disable();&t;&t;&bslash;&n;        asm(&quot;&t;&t;&t;&t;&bslash;&n;        moveal #0x10c00000, %a0;&t;&bslash;&n;        moveb #0, 0xFFFFF300;&t;&t;&bslash;&n;        moveal 0(%a0), %sp;&t;&t;&bslash;&n;        moveal 4(%a0), %a0;&t;&t;&bslash;&n;        jmp (%a0);&t;&t;&t;&bslash;&n;        &quot;);&t;&t;&t;&t;&bslash;&n;})
macro_line|#endif
macro_line|#ifdef CONFIG_COLDFIRE
macro_line|#if defined(CONFIG_M5272) &amp;&amp; defined(CONFIG_NETtel)
multiline_comment|/*&n; *&t;Need to account for broken early mask of 5272 silicon. So don&squot;t&n; *&t;jump through the original start address. Jump strait into the&n; *&t;known start of the FLASH code.&n; */
DECL|macro|HARD_RESET_NOW
mdefine_line|#define HARD_RESET_NOW() ({&t;&t;&bslash;&n;        asm(&quot;&t;&t;&t;&t;&bslash;&n;&t;movew #0x2700, %sr;&t;&t;&bslash;&n;        jmp 0xf0000400;&t;&t;&t;&bslash;&n;        &quot;);&t;&t;&t;&t;&bslash;&n;})
macro_line|#elif defined(CONFIG_NETtel) || defined(CONFIG_eLIA) || defined(CONFIG_DISKtel) || defined(CONFIG_SECUREEDGEMP3) || defined(CONFIG_CLEOPATRA)
DECL|macro|HARD_RESET_NOW
mdefine_line|#define HARD_RESET_NOW() ({&t;&t;&bslash;&n;        asm(&quot;&t;&t;&t;&t;&bslash;&n;&t;movew #0x2700, %sr;&t;&t;&bslash;&n;&t;moveal #0x10000044, %a0;&t;&bslash;&n;&t;movel #0xffffffff, (%a0);&t;&bslash;&n;&t;moveal #0x10000001, %a0;&t;&bslash;&n;&t;moveb #0x00, (%a0);&t;&t;&bslash;&n;        moveal #0xf0000004, %a0;&t;&bslash;&n;        moveal (%a0), %a0;&t;&t;&bslash;&n;        jmp (%a0);&t;&t;&t;&bslash;&n;        &quot;);&t;&t;&t;&t;&bslash;&n;})
macro_line|#elif defined(CONFIG_M528x)
multiline_comment|/*&n; * The MCF528x has a bit (SOFTRST) in memory (Reset Control Register RCR),&n; * that when set, resets the MCF528x.&n; */
DECL|macro|HARD_RESET_NOW
mdefine_line|#define HARD_RESET_NOW() &bslash;&n;({&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned char volatile *reset;&t;&t;&bslash;&n;&t;asm(&quot;move.w&t;#0x2700, %sr&quot;);&t;&t;&bslash;&n;&t;reset = ((volatile unsigned short *)(MCF_IPSBAR + 0x110000));&t;&bslash;&n;&t;while(1)&t;&t;&t;&t;&bslash;&n;&t;*reset |= (0x01 &lt;&lt; 7);&bslash;&n;})
macro_line|#else
DECL|macro|HARD_RESET_NOW
mdefine_line|#define HARD_RESET_NOW() ({&t;&t;&bslash;&n;        asm(&quot;&t;&t;&t;&t;&bslash;&n;&t;movew #0x2700, %sr;&t;&t;&bslash;&n;        moveal #0x4, %a0;&t;&t;&bslash;&n;        moveal (%a0), %a0;&t;&t;&bslash;&n;        jmp (%a0);&t;&t;&t;&bslash;&n;        &quot;);&t;&t;&t;&t;&bslash;&n;})
macro_line|#endif
macro_line|#endif
DECL|macro|arch_align_stack
mdefine_line|#define arch_align_stack(x) (x)
macro_line|#endif /* _M68KNOMMU_SYSTEM_H */
eof
