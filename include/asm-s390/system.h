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
DECL|macro|prepare_arch_schedule
mdefine_line|#define prepare_arch_schedule(prev)&t;&t;do { } while (0)
DECL|macro|finish_arch_schedule
mdefine_line|#define finish_arch_schedule(prev)&t;&t;do { } while (0)
DECL|macro|prepare_arch_switch
mdefine_line|#define prepare_arch_switch(rq)&t;&t;&t;do { } while (0)
DECL|macro|finish_arch_switch
mdefine_line|#define finish_arch_switch(rq)&t;&t;&t;spin_unlock_irq(&amp;(rq)-&gt;lock)
DECL|macro|switch_to
mdefine_line|#define switch_to(prev,next,last) do {&t;&t;&t;&t;&t;     &bslash;&n;&t;if (prev == next)&t;&t;&t;&t;&t;&t;     &bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;     &bslash;&n;&t;save_fp_regs1(&amp;prev-&gt;thread.fp_regs);&t;&t;&t;&t;     &bslash;&n;&t;restore_fp_regs1(&amp;next-&gt;thread.fp_regs);&t;&t;&t;     &bslash;&n;&t;resume(prev,next);&t;&t;&t;&t;&t;&t;     &bslash;&n;} while (0)
r_struct
id|task_struct
suffix:semicolon
DECL|macro|nop
mdefine_line|#define nop() __asm__ __volatile__ (&quot;nop&quot;)
DECL|macro|xchg
mdefine_line|#define xchg(ptr,x) ((__typeof__(*(ptr)))__xchg((unsigned long)(x),(ptr),sizeof(*(ptr))))
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
r_switch
c_cond
(paren
id|size
)paren
(brace
r_case
l_int|1
suffix:colon
id|asm
r_volatile
(paren
l_string|&quot;   lhi   1,3&bslash;n&quot;
l_string|&quot;   nr    1,%0&bslash;n&quot;
multiline_comment|/* isolate last 2 bits */
l_string|&quot;   xr    %0,1&bslash;n&quot;
multiline_comment|/* align ptr */
l_string|&quot;   bras  2,0f&bslash;n&quot;
l_string|&quot;   icm   1,8,3(%1)&bslash;n&quot;
multiline_comment|/* for ptr&amp;3 == 0 */
l_string|&quot;   stcm  0,8,3(%1)&bslash;n&quot;
l_string|&quot;   icm   1,4,3(%1)&bslash;n&quot;
multiline_comment|/* for ptr&amp;3 == 1 */
l_string|&quot;   stcm  0,4,3(%1)&bslash;n&quot;
l_string|&quot;   icm   1,2,3(%1)&bslash;n&quot;
multiline_comment|/* for ptr&amp;3 == 2 */
l_string|&quot;   stcm  0,2,3(%1)&bslash;n&quot;
l_string|&quot;   icm   1,1,3(%1)&bslash;n&quot;
multiline_comment|/* for ptr&amp;3 == 3 */
l_string|&quot;   stcm  0,1,3(%1)&bslash;n&quot;
l_string|&quot;0: sll   1,3&bslash;n&quot;
l_string|&quot;   la    2,0(1,2)&bslash;n&quot;
multiline_comment|/* r2 points to an icm */
l_string|&quot;   l     0,0(%0)&bslash;n&quot;
multiline_comment|/* get fullword */
l_string|&quot;1: lr    1,0&bslash;n&quot;
multiline_comment|/* cs loop */
l_string|&quot;   ex    0,0(2)&bslash;n&quot;
multiline_comment|/* insert x */
l_string|&quot;   cs    0,1,0(%0)&bslash;n&quot;
l_string|&quot;   jl    1b&bslash;n&quot;
l_string|&quot;   ex    0,4(2)&quot;
multiline_comment|/* store *ptr to x */
suffix:colon
l_string|&quot;+a&amp;&quot;
(paren
id|ptr
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
op_amp
id|x
)paren
suffix:colon
l_string|&quot;memory&quot;
comma
l_string|&quot;cc&quot;
comma
l_string|&quot;0&quot;
comma
l_string|&quot;1&quot;
comma
l_string|&quot;2&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
r_if
c_cond
(paren
(paren
(paren
id|__u32
)paren
id|ptr
)paren
op_amp
l_int|1
)paren
(brace
id|__misaligned_u16
c_func
(paren
)paren
suffix:semicolon
)brace
id|asm
r_volatile
(paren
l_string|&quot;   lhi   1,2&bslash;n&quot;
l_string|&quot;   nr    1,%0&bslash;n&quot;
multiline_comment|/* isolate bit 2^1 */
l_string|&quot;   xr    %0,1&bslash;n&quot;
multiline_comment|/* align ptr */
l_string|&quot;   bras  2,0f&bslash;n&quot;
l_string|&quot;   icm   1,12,2(%1)&bslash;n&quot;
multiline_comment|/* for ptr&amp;2 == 0 */
l_string|&quot;   stcm  0,12,2(%1)&bslash;n&quot;
l_string|&quot;   icm   1,3,2(%1)&bslash;n&quot;
multiline_comment|/* for ptr&amp;2 == 1 */
l_string|&quot;   stcm  0,3,2(%1)&bslash;n&quot;
l_string|&quot;0: sll   1,2&bslash;n&quot;
l_string|&quot;   la    2,0(1,2)&bslash;n&quot;
multiline_comment|/* r2 points to an icm */
l_string|&quot;   l     0,0(%0)&bslash;n&quot;
multiline_comment|/* get fullword */
l_string|&quot;1: lr    1,0&bslash;n&quot;
multiline_comment|/* cs loop */
l_string|&quot;   ex    0,0(2)&bslash;n&quot;
multiline_comment|/* insert x */
l_string|&quot;   cs    0,1,0(%0)&bslash;n&quot;
l_string|&quot;   jl    1b&bslash;n&quot;
l_string|&quot;   ex    0,4(2)&quot;
multiline_comment|/* store *ptr to x */
suffix:colon
l_string|&quot;+a&amp;&quot;
(paren
id|ptr
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
op_amp
id|x
)paren
suffix:colon
l_string|&quot;memory&quot;
comma
l_string|&quot;cc&quot;
comma
l_string|&quot;0&quot;
comma
l_string|&quot;1&quot;
comma
l_string|&quot;2&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
r_if
c_cond
(paren
(paren
(paren
id|__u32
)paren
id|ptr
)paren
op_amp
l_int|3
)paren
(brace
id|__misaligned_u32
c_func
(paren
)paren
suffix:semicolon
)brace
id|asm
r_volatile
(paren
l_string|&quot;    l   0,0(%1)&bslash;n&quot;
l_string|&quot;0:  cs  0,%0,0(%1)&bslash;n&quot;
l_string|&quot;    jl  0b&bslash;n&quot;
l_string|&quot;    lr  %0,0&bslash;n&quot;
suffix:colon
l_string|&quot;+d&amp;&quot;
(paren
id|x
)paren
suffix:colon
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
r_break
suffix:semicolon
)brace
r_return
id|x
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
mdefine_line|#define local_irq_enable() ({ &bslash;&n;        __u8 __dummy; &bslash;&n;        __asm__ __volatile__ ( &bslash;&n;                &quot;stosm 0(%0),0x03&quot; : : &quot;a&quot; (&amp;__dummy) : &quot;memory&quot;); &bslash;&n;        })
DECL|macro|local_irq_disable
mdefine_line|#define local_irq_disable() ({ &bslash;&n;        __u32 __flags; &bslash;&n;        __asm__ __volatile__ ( &bslash;&n;                &quot;stnsm 0(%0),0xFC&quot; : : &quot;a&quot; (&amp;__flags) : &quot;memory&quot;); &bslash;&n;        __flags; &bslash;&n;        })
DECL|macro|local_save_flags
mdefine_line|#define local_save_flags(x) &bslash;&n;        __asm__ __volatile__(&quot;stosm 0(%0),0&quot; : : &quot;a&quot; (&amp;x) : &quot;memory&quot;)
DECL|macro|local_irq_restore
mdefine_line|#define local_irq_restore(x) &bslash;&n;        __asm__ __volatile__(&quot;ssm   0(%0)&quot; : : &quot;a&quot; (&amp;x) : &quot;memory&quot;)
DECL|macro|__load_psw
mdefine_line|#define __load_psw(psw) &bslash;&n;&t;__asm__ __volatile__(&quot;lpsw 0(%0)&quot; : : &quot;a&quot; (&amp;psw) : &quot;cc&quot; );
DECL|macro|__ctl_load
mdefine_line|#define __ctl_load(array, low, high) ({ &bslash;&n;&t;__asm__ __volatile__ ( &bslash;&n;&t;&t;&quot;   la    1,%0&bslash;n&quot; &bslash;&n;&t;&t;&quot;   bras  2,0f&bslash;n&quot; &bslash;&n;                &quot;   lctl  0,0,0(1)&bslash;n&quot; &bslash;&n;&t;&t;&quot;0: ex    %1,0(2)&quot; &bslash;&n;&t;&t;: : &quot;m&quot; (array), &quot;a&quot; (((low)&lt;&lt;4)+(high)) : &quot;1&quot;, &quot;2&quot; ); &bslash;&n;&t;})
DECL|macro|__ctl_store
mdefine_line|#define __ctl_store(array, low, high) ({ &bslash;&n;&t;__asm__ __volatile__ ( &bslash;&n;&t;&t;&quot;   la    1,%0&bslash;n&quot; &bslash;&n;&t;&t;&quot;   bras  2,0f&bslash;n&quot; &bslash;&n;&t;&t;&quot;   stctl 0,0,0(1)&bslash;n&quot; &bslash;&n;&t;&t;&quot;0: ex    %1,0(2)&quot; &bslash;&n;&t;&t;: &quot;=m&quot; (array) : &quot;a&quot; (((low)&lt;&lt;4)+(high)): &quot;1&quot;, &quot;2&quot; ); &bslash;&n;&t;})
DECL|macro|__ctl_set_bit
mdefine_line|#define __ctl_set_bit(cr, bit) ({ &bslash;&n;        __u8 __dummy[16]; &bslash;&n;        __asm__ __volatile__ ( &bslash;&n;                &quot;    la    1,%0&bslash;n&quot;       /* align to 8 byte */ &bslash;&n;                &quot;    ahi   1,7&bslash;n&quot; &bslash;&n;                &quot;    srl   1,3&bslash;n&quot; &bslash;&n;                &quot;    sll   1,3&bslash;n&quot; &bslash;&n;                &quot;    bras  2,0f&bslash;n&quot;       /* skip indirect insns */ &bslash;&n;                &quot;    stctl 0,0,0(1)&bslash;n&quot; &bslash;&n;                &quot;    lctl  0,0,0(1)&bslash;n&quot; &bslash;&n;                &quot;0:  ex    %1,0(2)&bslash;n&quot;    /* execute stctl */ &bslash;&n;                &quot;    l     0,0(1)&bslash;n&quot; &bslash;&n;                &quot;    or    0,%2&bslash;n&quot;       /* set the bit */ &bslash;&n;                &quot;    st    0,0(1)&bslash;n&quot; &bslash;&n;                &quot;1:  ex    %1,4(2)&quot;      /* execute lctl */ &bslash;&n;                : &quot;=m&quot; (__dummy) : &quot;a&quot; (cr*17), &quot;a&quot; (1&lt;&lt;(bit)) &bslash;&n;                : &quot;cc&quot;, &quot;0&quot;, &quot;1&quot;, &quot;2&quot;); &bslash;&n;        })
DECL|macro|__ctl_clear_bit
mdefine_line|#define __ctl_clear_bit(cr, bit) ({ &bslash;&n;        __u8 __dummy[16]; &bslash;&n;        __asm__ __volatile__ ( &bslash;&n;                &quot;    la    1,%0&bslash;n&quot;       /* align to 8 byte */ &bslash;&n;                &quot;    ahi   1,7&bslash;n&quot; &bslash;&n;                &quot;    srl   1,3&bslash;n&quot; &bslash;&n;                &quot;    sll   1,3&bslash;n&quot; &bslash;&n;                &quot;    bras  2,0f&bslash;n&quot;       /* skip indirect insns */ &bslash;&n;                &quot;    stctl 0,0,0(1)&bslash;n&quot; &bslash;&n;                &quot;    lctl  0,0,0(1)&bslash;n&quot; &bslash;&n;                &quot;0:  ex    %1,0(2)&bslash;n&quot;    /* execute stctl */ &bslash;&n;                &quot;    l     0,0(1)&bslash;n&quot; &bslash;&n;                &quot;    nr    0,%2&bslash;n&quot;       /* set the bit */ &bslash;&n;                &quot;    st    0,0(1)&bslash;n&quot; &bslash;&n;                &quot;1:  ex    %1,4(2)&quot;      /* execute lctl */ &bslash;&n;                : &quot;=m&quot; (__dummy) : &quot;a&quot; (cr*17), &quot;a&quot; (~(1&lt;&lt;(bit))) &bslash;&n;                : &quot;cc&quot;, &quot;0&quot;, &quot;1&quot;, &quot;2&quot;); &bslash;&n;        })
multiline_comment|/* For spinlocks etc */
DECL|macro|local_irq_save
mdefine_line|#define local_irq_save(x)&t;((x) = local_irq_disable())
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
DECL|macro|cli
mdefine_line|#define cli() local_irq_disable()
DECL|macro|sti
mdefine_line|#define sti() local_irq_enable()
DECL|macro|save_flags
mdefine_line|#define save_flags(x) local_save_flags(x)
DECL|macro|restore_flags
mdefine_line|#define restore_flags(x) local_irq_restore(x)
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
