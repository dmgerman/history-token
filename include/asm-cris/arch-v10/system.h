macro_line|#ifndef __ASM_CRIS_ARCH_SYSTEM_H
DECL|macro|__ASM_CRIS_ARCH_SYSTEM_H
mdefine_line|#define __ASM_CRIS_ARCH_SYSTEM_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* read the CPU version register */
DECL|function|rdvr
r_extern
r_inline
r_int
r_int
id|rdvr
c_func
(paren
r_void
)paren
(brace
r_int
r_char
id|vr
suffix:semicolon
id|__asm__
r_volatile
(paren
l_string|&quot;move $vr,%0&quot;
suffix:colon
l_string|&quot;=rm&quot;
(paren
id|vr
)paren
)paren
suffix:semicolon
r_return
id|vr
suffix:semicolon
)brace
multiline_comment|/* read/write the user-mode stackpointer */
DECL|function|rdusp
r_extern
r_inline
r_int
r_int
id|rdusp
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|usp
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;move $usp,%0&quot;
suffix:colon
l_string|&quot;=rm&quot;
(paren
id|usp
)paren
)paren
suffix:semicolon
r_return
id|usp
suffix:semicolon
)brace
DECL|macro|wrusp
mdefine_line|#define wrusp(usp) &bslash;&n;&t;__asm__ __volatile__(&quot;move %0,$usp&quot; : /* no outputs */ : &quot;rm&quot; (usp))
multiline_comment|/* read the current stackpointer */
DECL|function|rdsp
r_extern
r_inline
r_int
r_int
id|rdsp
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|sp
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;move.d $sp,%0&quot;
suffix:colon
l_string|&quot;=rm&quot;
(paren
id|sp
)paren
)paren
suffix:semicolon
r_return
id|sp
suffix:semicolon
)brace
DECL|function|_get_base
r_extern
r_inline
r_int
r_int
id|_get_base
c_func
(paren
r_char
op_star
id|addr
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|nop
mdefine_line|#define nop() __asm__ __volatile__ (&quot;nop&quot;);
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
mdefine_line|#define __xg(x) ((struct __xchg_dummy *)(x))
multiline_comment|/* interrupt control.. */
DECL|macro|local_save_flags
mdefine_line|#define local_save_flags(x)&t;__asm__ __volatile__ (&quot;move $ccr,%0&quot; : &quot;=rm&quot; (x) : : &quot;memory&quot;);
DECL|macro|local_irq_restore
mdefine_line|#define local_irq_restore(x) &t;__asm__ __volatile__ (&quot;move %0,$ccr&quot; : : &quot;rm&quot; (x) : &quot;memory&quot;);
DECL|macro|local_irq_disable
mdefine_line|#define local_irq_disable() &t;__asm__ __volatile__ ( &quot;di&quot; : : :&quot;memory&quot;);
DECL|macro|local_irq_enable
mdefine_line|#define local_irq_enable()&t;__asm__ __volatile__ ( &quot;ei&quot; : : :&quot;memory&quot;);
DECL|macro|irqs_disabled
mdefine_line|#define irqs_disabled()&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long flags;&t;&t;&bslash;&n;&t;local_save_flags(flags);&t;&bslash;&n;&t;!(flags &amp; (1&lt;&lt;5));&t;&t;&bslash;&n;})
multiline_comment|/* For spinlocks etc */
DECL|macro|local_irq_save
mdefine_line|#define local_irq_save(x) __asm__ __volatile__ (&quot;move $ccr,%0&bslash;n&bslash;tdi&quot; : &quot;=rm&quot; (x) : : &quot;memory&quot;);
macro_line|#endif
eof
