multiline_comment|/* $Id: system.h,v 1.4 2001/03/20 19:46:00 bjornw Exp $ */
macro_line|#ifndef __ASM_CRIS_SYSTEM_H
DECL|macro|__ASM_CRIS_SYSTEM_H
mdefine_line|#define __ASM_CRIS_SYSTEM_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
multiline_comment|/* the switch_to macro calls resume, an asm function in entry.S which does the actual&n; * task switching.&n; */
r_extern
r_struct
id|task_struct
op_star
id|resume
c_func
(paren
r_struct
id|task_struct
op_star
id|prev
comma
r_struct
id|task_struct
op_star
id|next
comma
r_int
)paren
suffix:semicolon
DECL|macro|prepare_to_switch
mdefine_line|#define prepare_to_switch()     do { } while(0)
DECL|macro|switch_to
mdefine_line|#define switch_to(prev,next,last) last = resume(prev,next, &bslash;&n;&t;&t;&t;&t;&t; (int)&amp;((struct task_struct *)0)-&gt;thread)
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
l_string|&quot;move usp,%0&quot;
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
mdefine_line|#define wrusp(usp) &bslash;&n;&t;__asm__ __volatile__(&quot;move %0,usp&quot; : /* no outputs */ : &quot;rm&quot; (usp))
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
l_string|&quot;move.d sp,%0&quot;
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
r_static
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
macro_line|#if 0
multiline_comment|/* use these and an oscilloscope to see the fraction of time we&squot;re running with IRQ&squot;s disabled */
multiline_comment|/* it assumes the LED&squot;s are on port 0x90000000 of course. */
mdefine_line|#define sti() __asm__ __volatile__ ( &quot;ei&bslash;n&bslash;tpush r0&bslash;n&bslash;tmoveq 0,r0&bslash;n&bslash;tmove.d r0,[0x90000000]&bslash;n&bslash;tpop r0&quot; );
mdefine_line|#define cli() __asm__ __volatile__ ( &quot;di&bslash;n&bslash;tpush r0&bslash;n&bslash;tmove.d 0x40000,r0&bslash;n&bslash;tmove.d r0,[0x90000000]&bslash;n&bslash;tpop r0&quot;);
mdefine_line|#define save_flags(x) __asm__ __volatile__ (&quot;move ccr,%0&quot; : &quot;=rm&quot; (x) : : &quot;memory&quot;);
mdefine_line|#define restore_flags(x) __asm__ __volatile__ (&quot;move %0,ccr&bslash;n&bslash;tbtstq 5,%0&bslash;n&bslash;tbpl 1f&bslash;n&bslash;tnop&bslash;n&bslash;tpush r0&bslash;n&bslash;tmoveq 0,r0&bslash;n&bslash;tmove.d r0,[0x90000000]&bslash;n&bslash;tpop r0&bslash;n1:&bslash;n&quot; : : &quot;r&quot; (x) : &quot;memory&quot;);
macro_line|#else
DECL|macro|__cli
mdefine_line|#define __cli() __asm__ __volatile__ ( &quot;di&quot;);
DECL|macro|__sti
mdefine_line|#define __sti() __asm__ __volatile__ ( &quot;ei&quot; );
DECL|macro|__save_flags
mdefine_line|#define __save_flags(x) __asm__ __volatile__ (&quot;move ccr,%0&quot; : &quot;=rm&quot; (x) : : &quot;memory&quot;);
DECL|macro|__restore_flags
mdefine_line|#define __restore_flags(x) __asm__ __volatile__ (&quot;move %0,ccr&quot; : : &quot;rm&quot; (x) : &quot;memory&quot;);
multiline_comment|/* For spinlocks etc */
DECL|macro|local_irq_save
mdefine_line|#define local_irq_save(x) __asm__ __volatile__ (&quot;move ccr,%0&bslash;n&bslash;tdi&quot; : &quot;=rm&quot; (x) : : &quot;memory&quot;); 
DECL|macro|local_irq_restore
mdefine_line|#define local_irq_restore(x) restore_flags(x)
DECL|macro|local_irq_disable
mdefine_line|#define local_irq_disable()  cli()
DECL|macro|local_irq_enable
mdefine_line|#define local_irq_enable()   sti()
macro_line|#endif
DECL|macro|cli
mdefine_line|#define cli() __cli()
DECL|macro|sti
mdefine_line|#define sti() __sti()
DECL|macro|save_flags
mdefine_line|#define save_flags(x) __save_flags(x)
DECL|macro|restore_flags
mdefine_line|#define restore_flags(x) __restore_flags(x)
DECL|macro|save_and_cli
mdefine_line|#define save_and_cli(x) do { __save_flags(x); cli(); } while(0)
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
r_void
op_star
id|ptr
comma
r_int
id|size
)paren
(brace
multiline_comment|/* since Etrax doesn&squot;t have any atomic xchg instructions, we need to disable&n;     irq&squot;s (if enabled) and do it with move.d&squot;s */
macro_line|#if 0
r_int
r_int
id|flags
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* save flags, including irq enable bit */
id|cli
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* shut off irq&squot;s */
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
l_string|&quot;move.b %0,r0&bslash;n&bslash;t&quot;
l_string|&quot;move.b %1,%0&bslash;n&bslash;t&quot;
l_string|&quot;move.b r0,%1&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|x
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
op_star
id|__xg
c_func
(paren
id|ptr
)paren
)paren
comma
l_string|&quot;r&quot;
(paren
id|x
)paren
suffix:colon
l_string|&quot;memory&quot;
comma
l_string|&quot;r0&quot;
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
l_string|&quot;move.w %0,r0&bslash;n&bslash;t&quot;
l_string|&quot;move.w %1,%0&bslash;n&bslash;t&quot;
l_string|&quot;move.w r0,%1&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|x
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
op_star
id|__xg
c_func
(paren
id|ptr
)paren
)paren
comma
l_string|&quot;r&quot;
(paren
id|x
)paren
suffix:colon
l_string|&quot;memory&quot;
comma
l_string|&quot;r0&quot;
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
l_string|&quot;move.d %0,r0&bslash;n&bslash;t&quot;
l_string|&quot;move.d %1,%0&bslash;n&bslash;t&quot;
l_string|&quot;move.d r0,%1&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|x
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
op_star
id|__xg
c_func
(paren
id|ptr
)paren
)paren
comma
l_string|&quot;r&quot;
(paren
id|x
)paren
suffix:colon
l_string|&quot;memory&quot;
comma
l_string|&quot;r0&quot;
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
multiline_comment|/* restore irq enable bit */
r_return
id|x
suffix:semicolon
macro_line|#else
r_int
r_int
id|flags
comma
id|temp
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* save flags, including irq enable bit */
id|cli
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* shut off irq&squot;s */
r_switch
c_cond
(paren
id|size
)paren
(brace
r_case
l_int|1
suffix:colon
op_star
(paren
(paren
r_int
r_char
op_star
)paren
op_amp
id|temp
)paren
op_assign
id|x
suffix:semicolon
id|x
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
op_star
(paren
(paren
r_int
r_char
op_star
)paren
op_amp
id|temp
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
op_star
(paren
(paren
r_int
r_int
op_star
)paren
op_amp
id|temp
)paren
op_assign
id|x
suffix:semicolon
id|x
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
op_star
(paren
(paren
r_int
r_int
op_star
)paren
op_amp
id|temp
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|temp
op_assign
id|x
suffix:semicolon
id|x
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
id|temp
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
multiline_comment|/* restore irq enable bit */
r_return
id|x
suffix:semicolon
macro_line|#endif
)brace
DECL|macro|mb
mdefine_line|#define mb() __asm__ __volatile__ (&quot;&quot; : : : &quot;memory&quot;)
DECL|macro|rmb
mdefine_line|#define rmb() mb()
DECL|macro|wmb
mdefine_line|#define wmb() mb()
macro_line|#ifdef CONFIG_SMP
DECL|macro|smp_mb
mdefine_line|#define smp_mb()        mb()
DECL|macro|smp_rmb
mdefine_line|#define smp_rmb()       rmb()
DECL|macro|smp_wmb
mdefine_line|#define smp_wmb()       wmb()
macro_line|#else
DECL|macro|smp_mb
mdefine_line|#define smp_mb()        barrier()
DECL|macro|smp_rmb
mdefine_line|#define smp_rmb()       barrier()
DECL|macro|smp_wmb
mdefine_line|#define smp_wmb()       barrier()
macro_line|#endif
DECL|macro|iret
mdefine_line|#define iret()
multiline_comment|/*&n; * disable hlt during certain critical i/o operations&n; */
DECL|macro|HAVE_DISABLE_HLT
mdefine_line|#define HAVE_DISABLE_HLT
r_void
id|disable_hlt
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|enable_hlt
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
eof
