multiline_comment|/*&n; *  include/asm-s390/system.h&n; *&n; *  S390 version&n; *    Copyright (C) 1999 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Martin Schwidefsky (schwidefsky@de.ibm.com),&n; *&n; *  Derived from &quot;include/asm-i386/system.h&quot;&n; */
macro_line|#ifndef __ASM_SYSTEM_H
DECL|macro|__ASM_SYSTEM_H
mdefine_line|#define __ASM_SYSTEM_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/types.h&gt;
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;asm/lowcore.h&gt;
macro_line|#endif
macro_line|#include &lt;linux/kernel.h&gt;
DECL|macro|switch_to
mdefine_line|#define switch_to(prev,next,last) do {&t;&t;&t;&t;&t;     &bslash;&n;&t;if (prev == next)&t;&t;&t;&t;&t;&t;     &bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;     &bslash;&n;&t;save_fp_regs(&amp;prev-&gt;thread.fp_regs);&t;&t;&t;&t;     &bslash;&n;&t;restore_fp_regs(&amp;next-&gt;thread.fp_regs);&t;&t;&t;&t;     &bslash;&n;&t;resume(prev,next);&t;&t;&t;&t;&t;&t;     &bslash;&n;} while (0)
r_struct
id|task_struct
suffix:semicolon
DECL|macro|nop
mdefine_line|#define nop() __asm__ __volatile__ (&quot;nop&quot;)
DECL|macro|xchg
mdefine_line|#define xchg(ptr,x) &bslash;&n;  ((__typeof__(*(ptr)))__xchg((unsigned long)(x),(void *)(ptr),sizeof(*(ptr))))
r_extern
r_void
id|__misaligned_u16
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__misaligned_u32
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__misaligned_u64
c_func
(paren
r_void
)paren
suffix:semicolon
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
r_int
r_int
id|addr
comma
id|old
suffix:semicolon
r_int
id|shift
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
id|addr
op_assign
(paren
r_int
r_int
)paren
id|ptr
suffix:semicolon
id|shift
op_assign
(paren
l_int|3
op_xor
(paren
id|addr
op_amp
l_int|3
)paren
)paren
op_lshift
l_int|3
suffix:semicolon
id|addr
op_xor_assign
id|addr
op_amp
l_int|3
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;    l   %0,0(%3)&bslash;n&quot;
l_string|&quot;0:  lr  0,%0&bslash;n&quot;
l_string|&quot;    nr  0,%2&bslash;n&quot;
l_string|&quot;    or  0,%1&bslash;n&quot;
l_string|&quot;    cs  %0,0,0(%3)&bslash;n&quot;
l_string|&quot;    jl  0b&bslash;n&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|old
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|x
op_lshift
id|shift
)paren
comma
l_string|&quot;d&quot;
(paren
op_complement
(paren
l_int|255
op_lshift
id|shift
)paren
)paren
comma
l_string|&quot;a&quot;
(paren
id|addr
)paren
suffix:colon
l_string|&quot;memory&quot;
comma
l_string|&quot;cc&quot;
comma
l_string|&quot;0&quot;
)paren
suffix:semicolon
id|x
op_assign
id|old
op_rshift
id|shift
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|addr
op_assign
(paren
r_int
r_int
)paren
id|ptr
suffix:semicolon
id|shift
op_assign
(paren
l_int|2
op_xor
(paren
id|addr
op_amp
l_int|2
)paren
)paren
op_lshift
l_int|3
suffix:semicolon
id|addr
op_xor_assign
id|addr
op_amp
l_int|2
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;    l   %0,0(%3)&bslash;n&quot;
l_string|&quot;0:  lr  0,%0&bslash;n&quot;
l_string|&quot;    nr  0,%2&bslash;n&quot;
l_string|&quot;    or  0,%1&bslash;n&quot;
l_string|&quot;    cs  %0,0,0(%3)&bslash;n&quot;
l_string|&quot;    jl  0b&bslash;n&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|old
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|x
op_lshift
id|shift
)paren
comma
l_string|&quot;d&quot;
(paren
op_complement
(paren
l_int|65535
op_lshift
id|shift
)paren
)paren
comma
l_string|&quot;a&quot;
(paren
id|addr
)paren
suffix:colon
l_string|&quot;memory&quot;
comma
l_string|&quot;cc&quot;
comma
l_string|&quot;0&quot;
)paren
suffix:semicolon
id|x
op_assign
id|old
op_rshift
id|shift
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|asm
r_volatile
(paren
l_string|&quot;    l   %0,0(%2)&bslash;n&quot;
l_string|&quot;0:  cs  %0,%1,0(%2)&bslash;n&quot;
l_string|&quot;    jl  0b&bslash;n&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|old
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|x
)paren
comma
l_string|&quot;a&quot;
(paren
id|ptr
)paren
suffix:colon
l_string|&quot;memory&quot;
comma
l_string|&quot;cc&quot;
comma
l_string|&quot;0&quot;
)paren
suffix:semicolon
id|x
op_assign
id|old
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|8
suffix:colon
id|asm
r_volatile
(paren
l_string|&quot;    lg  %0,0(%2)&bslash;n&quot;
l_string|&quot;0:  csg %0,%1,0(%2)&bslash;n&quot;
l_string|&quot;    jl  0b&bslash;n&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|old
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|x
)paren
comma
l_string|&quot;a&quot;
(paren
id|ptr
)paren
suffix:colon
l_string|&quot;memory&quot;
comma
l_string|&quot;cc&quot;
comma
l_string|&quot;0&quot;
)paren
suffix:semicolon
id|x
op_assign
id|old
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|x
suffix:semicolon
)brace
multiline_comment|/*&n; * Atomic compare and exchange.  Compare OLD with MEM, if identical,&n; * store NEW in MEM.  Return the initial value in MEM.  Success is&n; * indicated by comparing RETURN with OLD.&n; */
DECL|macro|__HAVE_ARCH_CMPXCHG
mdefine_line|#define __HAVE_ARCH_CMPXCHG 1
DECL|macro|cmpxchg
mdefine_line|#define cmpxchg(ptr,o,n)&bslash;&n;&t;((__typeof__(*(ptr)))__cmpxchg((ptr),(unsigned long)(o),&bslash;&n;&t;&t;&t;&t;&t;(unsigned long)(n),sizeof(*(ptr))))
r_static
r_inline
r_int
r_int
DECL|function|__cmpxchg
id|__cmpxchg
c_func
(paren
r_volatile
r_void
op_star
id|ptr
comma
r_int
r_int
id|old
comma
r_int
r_int
r_new
comma
r_int
id|size
)paren
(brace
r_int
r_int
id|addr
comma
id|prev
comma
id|tmp
suffix:semicolon
r_int
id|shift
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
id|addr
op_assign
(paren
r_int
r_int
)paren
id|ptr
suffix:semicolon
id|shift
op_assign
(paren
l_int|3
op_xor
(paren
id|addr
op_amp
l_int|3
)paren
)paren
op_lshift
l_int|3
suffix:semicolon
id|addr
op_xor_assign
id|addr
op_amp
l_int|3
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;    l   %0,0(%4)&bslash;n&quot;
l_string|&quot;0:  nr  %0,%5&bslash;n&quot;
l_string|&quot;    lr  %1,%0&bslash;n&quot;
l_string|&quot;    or  %0,%2&bslash;n&quot;
l_string|&quot;    or  %1,%3&bslash;n&quot;
l_string|&quot;    cs  %0,%1,0(%4)&bslash;n&quot;
l_string|&quot;    jnl 1f&bslash;n&quot;
l_string|&quot;    xr  %1,%0&bslash;n&quot;
l_string|&quot;    nr  %1,%5&bslash;n&quot;
l_string|&quot;    jnz 0b&bslash;n&quot;
l_string|&quot;1:&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|prev
)paren
comma
l_string|&quot;=&amp;d&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|old
op_lshift
id|shift
)paren
comma
l_string|&quot;d&quot;
(paren
r_new
op_lshift
id|shift
)paren
comma
l_string|&quot;a&quot;
(paren
id|ptr
)paren
comma
l_string|&quot;d&quot;
(paren
op_complement
(paren
l_int|255
op_lshift
id|shift
)paren
)paren
suffix:colon
l_string|&quot;memory&quot;
comma
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
id|prev
op_rshift
id|shift
suffix:semicolon
r_case
l_int|2
suffix:colon
id|addr
op_assign
(paren
r_int
r_int
)paren
id|ptr
suffix:semicolon
id|shift
op_assign
(paren
l_int|2
op_xor
(paren
id|addr
op_amp
l_int|2
)paren
)paren
op_lshift
l_int|3
suffix:semicolon
id|addr
op_xor_assign
id|addr
op_amp
l_int|2
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;    l   %0,0(%4)&bslash;n&quot;
l_string|&quot;0:  nr  %0,%5&bslash;n&quot;
l_string|&quot;    lr  %1,%0&bslash;n&quot;
l_string|&quot;    or  %0,%2&bslash;n&quot;
l_string|&quot;    or  %1,%3&bslash;n&quot;
l_string|&quot;    cs  %0,%1,0(%4)&bslash;n&quot;
l_string|&quot;    jnl 1f&bslash;n&quot;
l_string|&quot;    xr  %1,%0&bslash;n&quot;
l_string|&quot;    nr  %1,%5&bslash;n&quot;
l_string|&quot;    jnz 0b&bslash;n&quot;
l_string|&quot;1:&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|prev
)paren
comma
l_string|&quot;=&amp;d&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|old
op_lshift
id|shift
)paren
comma
l_string|&quot;d&quot;
(paren
r_new
op_lshift
id|shift
)paren
comma
l_string|&quot;a&quot;
(paren
id|ptr
)paren
comma
l_string|&quot;d&quot;
(paren
op_complement
(paren
l_int|65535
op_lshift
id|shift
)paren
)paren
suffix:colon
l_string|&quot;memory&quot;
comma
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
id|prev
op_rshift
id|shift
suffix:semicolon
r_case
l_int|4
suffix:colon
id|asm
r_volatile
(paren
l_string|&quot;    cs  %0,%2,0(%3)&bslash;n&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|prev
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|old
)paren
comma
l_string|&quot;d&quot;
(paren
r_new
)paren
comma
l_string|&quot;a&quot;
(paren
id|ptr
)paren
suffix:colon
l_string|&quot;memory&quot;
comma
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
id|prev
suffix:semicolon
r_case
l_int|8
suffix:colon
id|asm
r_volatile
(paren
l_string|&quot;    csg %0,%2,0(%3)&bslash;n&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|prev
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|old
)paren
comma
l_string|&quot;d&quot;
(paren
r_new
)paren
comma
l_string|&quot;a&quot;
(paren
id|ptr
)paren
suffix:colon
l_string|&quot;memory&quot;
comma
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
id|prev
suffix:semicolon
)brace
r_return
id|old
suffix:semicolon
)brace
multiline_comment|/*&n; * Force strict CPU ordering.&n; * And yes, this is required on UP too when we&squot;re talking&n; * to devices.&n; *&n; * This is very similar to the ppc eieio/sync instruction in that is&n; * does a checkpoint syncronisation &amp; makes sure that &n; * all memory ops have completed wrt other CPU&squot;s ( see 7-15 POP  DJB ).&n; */
DECL|macro|eieio
mdefine_line|#define eieio()  __asm__ __volatile__ (&quot;BCR 15,0&quot;) 
DECL|macro|SYNC_OTHER_CORES
macro_line|# define SYNC_OTHER_CORES(x)   eieio() 
DECL|macro|mb
mdefine_line|#define mb()    eieio()
DECL|macro|rmb
mdefine_line|#define rmb()   eieio()
DECL|macro|wmb
mdefine_line|#define wmb()   eieio()
DECL|macro|smp_mb
mdefine_line|#define smp_mb()       mb()
DECL|macro|smp_rmb
mdefine_line|#define smp_rmb()      rmb()
DECL|macro|smp_wmb
mdefine_line|#define smp_wmb()      wmb()
DECL|macro|smp_mb__before_clear_bit
mdefine_line|#define smp_mb__before_clear_bit()     smp_mb()
DECL|macro|smp_mb__after_clear_bit
mdefine_line|#define smp_mb__after_clear_bit()      smp_mb()
DECL|macro|set_mb
mdefine_line|#define set_mb(var, value)      do { var = value; mb(); } while (0)
DECL|macro|set_wmb
mdefine_line|#define set_wmb(var, value)     do { var = value; wmb(); } while (0)
multiline_comment|/* interrupt control.. */
DECL|macro|local_irq_enable
mdefine_line|#define local_irq_enable() ({ &bslash;&n;        unsigned long __dummy; &bslash;&n;        __asm__ __volatile__ ( &bslash;&n;                &quot;stosm 0(%0),0x03&quot; : : &quot;a&quot; (&amp;__dummy) : &quot;memory&quot;); &bslash;&n;        })
DECL|macro|local_irq_disable
mdefine_line|#define local_irq_disable() ({ &bslash;&n;        unsigned long __flags; &bslash;&n;        __asm__ __volatile__ ( &bslash;&n;                &quot;stnsm 0(%0),0xFC&quot; : : &quot;a&quot; (&amp;__flags) : &quot;memory&quot;); &bslash;&n;        __flags; &bslash;&n;        })
DECL|macro|local_save_flags
mdefine_line|#define local_save_flags(x) &bslash;&n;        __asm__ __volatile__(&quot;stosm 0(%0),0&quot; : : &quot;a&quot; (&amp;x) : &quot;memory&quot;)
DECL|macro|local_irq_restore
mdefine_line|#define local_irq_restore(x) &bslash;&n;        __asm__ __volatile__(&quot;ssm   0(%0)&quot; : : &quot;a&quot; (&amp;x) : &quot;memory&quot;)
DECL|macro|irqs_disabled
mdefine_line|#define irqs_disabled()&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long flags;&t;&t;&bslash;&n;&t;local_save_flags(flags);&t;&bslash;&n;        !((flags &gt;&gt; 56) &amp; 3);&t;&t;&bslash;&n;})
DECL|macro|__load_psw
mdefine_line|#define __load_psw(psw) &bslash;&n;        __asm__ __volatile__(&quot;lpswe 0(%0)&quot; : : &quot;a&quot; (&amp;psw) : &quot;cc&quot; );
DECL|macro|__ctl_load
mdefine_line|#define __ctl_load(array, low, high) ({ &bslash;&n;&t;__asm__ __volatile__ ( &bslash;&n;&t;&t;&quot;   la    1,%0&bslash;n&quot; &bslash;&n;&t;&t;&quot;   bras  2,0f&bslash;n&quot; &bslash;&n;                &quot;   lctlg 0,0,0(1)&bslash;n&quot; &bslash;&n;&t;&t;&quot;0: ex    %1,0(2)&quot; &bslash;&n;&t;&t;: : &quot;m&quot; (array), &quot;a&quot; (((low)&lt;&lt;4)+(high)) : &quot;1&quot;, &quot;2&quot; ); &bslash;&n;&t;})
DECL|macro|__ctl_store
mdefine_line|#define __ctl_store(array, low, high) ({ &bslash;&n;&t;__asm__ __volatile__ ( &bslash;&n;&t;&t;&quot;   la    1,%0&bslash;n&quot; &bslash;&n;&t;&t;&quot;   bras  2,0f&bslash;n&quot; &bslash;&n;&t;&t;&quot;   stctg 0,0,0(1)&bslash;n&quot; &bslash;&n;&t;&t;&quot;0: ex    %1,0(2)&quot; &bslash;&n;&t;&t;: &quot;=m&quot; (array) : &quot;a&quot; (((low)&lt;&lt;4)+(high)): &quot;1&quot;, &quot;2&quot; ); &bslash;&n;&t;})
DECL|macro|__ctl_set_bit
mdefine_line|#define __ctl_set_bit(cr, bit) ({ &bslash;&n;        __u8 __dummy[24]; &bslash;&n;        __asm__ __volatile__ ( &bslash;&n;                &quot;    la    1,%0&bslash;n&quot;       /* align to 8 byte */ &bslash;&n;                &quot;    aghi  1,7&bslash;n&quot; &bslash;&n;                &quot;    nill  1,0xfff8&bslash;n&quot; &bslash;&n;                &quot;    bras  2,0f&bslash;n&quot;       /* skip indirect insns */ &bslash;&n;                &quot;    stctg 0,0,0(1)&bslash;n&quot; &bslash;&n;                &quot;    lctlg 0,0,0(1)&bslash;n&quot; &bslash;&n;                &quot;0:  ex    %1,0(2)&bslash;n&quot;    /* execute stctl */ &bslash;&n;                &quot;    lg    0,0(1)&bslash;n&quot; &bslash;&n;                &quot;    ogr   0,%2&bslash;n&quot;       /* set the bit */ &bslash;&n;                &quot;    stg   0,0(1)&bslash;n&quot; &bslash;&n;                &quot;1:  ex    %1,6(2)&quot;      /* execute lctl */ &bslash;&n;                : &quot;=m&quot; (__dummy) : &quot;a&quot; (cr*17), &quot;a&quot; (1L&lt;&lt;(bit)) &bslash;&n;                : &quot;cc&quot;, &quot;0&quot;, &quot;1&quot;, &quot;2&quot;); &bslash;&n;        })
DECL|macro|__ctl_clear_bit
mdefine_line|#define __ctl_clear_bit(cr, bit) ({ &bslash;&n;        __u8 __dummy[24]; &bslash;&n;        __asm__ __volatile__ ( &bslash;&n;                &quot;    la    1,%0&bslash;n&quot;       /* align to 8 byte */ &bslash;&n;                &quot;    aghi  1,7&bslash;n&quot; &bslash;&n;                &quot;    nill  1,0xfff8&bslash;n&quot; &bslash;&n;                &quot;    bras  2,0f&bslash;n&quot;       /* skip indirect insns */ &bslash;&n;                &quot;    stctg 0,0,0(1)&bslash;n&quot; &bslash;&n;                &quot;    lctlg 0,0,0(1)&bslash;n&quot; &bslash;&n;                &quot;0:  ex    %1,0(2)&bslash;n&quot;    /* execute stctl */ &bslash;&n;                &quot;    lg    0,0(1)&bslash;n&quot; &bslash;&n;                &quot;    ngr   0,%2&bslash;n&quot;       /* set the bit */ &bslash;&n;                &quot;    stg   0,0(1)&bslash;n&quot; &bslash;&n;                &quot;1:  ex    %1,6(2)&quot;      /* execute lctl */ &bslash;&n;                : &quot;=m&quot; (__dummy) : &quot;a&quot; (cr*17), &quot;a&quot; (~(1L&lt;&lt;(bit))) &bslash;&n;                : &quot;cc&quot;, &quot;0&quot;, &quot;1&quot;, &quot;2&quot;); &bslash;&n;        })
multiline_comment|/* For spinlocks etc */
DECL|macro|local_irq_save
mdefine_line|#define local_irq_save(x)&t;((x) = local_irq_disable())
macro_line|#ifdef CONFIG_SMP
r_extern
r_void
id|smp_ctl_set_bit
c_func
(paren
r_int
id|cr
comma
r_int
id|bit
)paren
suffix:semicolon
r_extern
r_void
id|smp_ctl_clear_bit
c_func
(paren
r_int
id|cr
comma
r_int
id|bit
)paren
suffix:semicolon
DECL|macro|ctl_set_bit
mdefine_line|#define ctl_set_bit(cr, bit) smp_ctl_set_bit(cr, bit)
DECL|macro|ctl_clear_bit
mdefine_line|#define ctl_clear_bit(cr, bit) smp_ctl_clear_bit(cr, bit)
macro_line|#else
DECL|macro|ctl_set_bit
mdefine_line|#define ctl_set_bit(cr, bit) __ctl_set_bit(cr, bit)
DECL|macro|ctl_clear_bit
mdefine_line|#define ctl_clear_bit(cr, bit) __ctl_clear_bit(cr, bit)
macro_line|#endif
macro_line|#ifdef __KERNEL__
r_extern
r_struct
id|task_struct
op_star
id|resume
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
r_int
id|save_fp_regs1
c_func
(paren
id|s390_fp_regs
op_star
id|fpregs
)paren
suffix:semicolon
r_extern
r_void
id|save_fp_regs
c_func
(paren
id|s390_fp_regs
op_star
id|fpregs
)paren
suffix:semicolon
r_extern
r_int
id|restore_fp_regs1
c_func
(paren
id|s390_fp_regs
op_star
id|fpregs
)paren
suffix:semicolon
r_extern
r_void
id|restore_fp_regs
c_func
(paren
id|s390_fp_regs
op_star
id|fpregs
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|_machine_restart
)paren
(paren
r_char
op_star
id|command
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|_machine_halt
)paren
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|_machine_power_off
)paren
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
