macro_line|#ifndef __PARISC_SYSTEM_H
DECL|macro|__PARISC_SYSTEM_H
mdefine_line|#define __PARISC_SYSTEM_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/psw.h&gt;
multiline_comment|/* The program status word as bitfields.  */
DECL|struct|pa_psw
r_struct
id|pa_psw
(brace
DECL|member|y
r_int
r_int
id|y
suffix:colon
l_int|1
suffix:semicolon
DECL|member|z
r_int
r_int
id|z
suffix:colon
l_int|1
suffix:semicolon
DECL|member|rv
r_int
r_int
id|rv
suffix:colon
l_int|2
suffix:semicolon
DECL|member|w
r_int
r_int
id|w
suffix:colon
l_int|1
suffix:semicolon
DECL|member|e
r_int
r_int
id|e
suffix:colon
l_int|1
suffix:semicolon
DECL|member|s
r_int
r_int
id|s
suffix:colon
l_int|1
suffix:semicolon
DECL|member|t
r_int
r_int
id|t
suffix:colon
l_int|1
suffix:semicolon
DECL|member|h
r_int
r_int
id|h
suffix:colon
l_int|1
suffix:semicolon
DECL|member|l
r_int
r_int
id|l
suffix:colon
l_int|1
suffix:semicolon
DECL|member|n
r_int
r_int
id|n
suffix:colon
l_int|1
suffix:semicolon
DECL|member|x
r_int
r_int
id|x
suffix:colon
l_int|1
suffix:semicolon
DECL|member|b
r_int
r_int
id|b
suffix:colon
l_int|1
suffix:semicolon
DECL|member|c
r_int
r_int
id|c
suffix:colon
l_int|1
suffix:semicolon
DECL|member|v
r_int
r_int
id|v
suffix:colon
l_int|1
suffix:semicolon
DECL|member|m
r_int
r_int
id|m
suffix:colon
l_int|1
suffix:semicolon
DECL|member|cb
r_int
r_int
id|cb
suffix:colon
l_int|8
suffix:semicolon
DECL|member|o
r_int
r_int
id|o
suffix:colon
l_int|1
suffix:semicolon
DECL|member|g
r_int
r_int
id|g
suffix:colon
l_int|1
suffix:semicolon
DECL|member|f
r_int
r_int
id|f
suffix:colon
l_int|1
suffix:semicolon
DECL|member|r
r_int
r_int
id|r
suffix:colon
l_int|1
suffix:semicolon
DECL|member|q
r_int
r_int
id|q
suffix:colon
l_int|1
suffix:semicolon
DECL|member|p
r_int
r_int
id|p
suffix:colon
l_int|1
suffix:semicolon
DECL|member|d
r_int
r_int
id|d
suffix:colon
l_int|1
suffix:semicolon
DECL|member|i
r_int
r_int
id|i
suffix:colon
l_int|1
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef __LP64__
DECL|macro|pa_psw
mdefine_line|#define pa_psw(task) ((struct pa_psw *) ((char *) (task) + TASK_PT_PSW + 4))
macro_line|#else
DECL|macro|pa_psw
mdefine_line|#define pa_psw(task) ((struct pa_psw *) ((char *) (task) + TASK_PT_PSW))
macro_line|#endif
r_struct
id|task_struct
suffix:semicolon
r_extern
r_struct
id|task_struct
op_star
id|_switch_to
c_func
(paren
r_struct
id|task_struct
op_star
comma
r_struct
id|task_struct
op_star
)paren
suffix:semicolon
DECL|macro|switch_to
mdefine_line|#define switch_to(prev, next, last) do {&t;&t;&t;&bslash;&n;&t;(last) = _switch_to(prev, next);&t;&t;&t;&bslash;&n;} while(0)
multiline_comment|/* interrupt control */
DECL|macro|local_save_flags
mdefine_line|#define local_save_flags(x)&t;__asm__ __volatile__(&quot;ssm 0, %0&quot; : &quot;=r&quot; (x) : : &quot;memory&quot;)
DECL|macro|local_irq_disable
mdefine_line|#define local_irq_disable()&t;__asm__ __volatile__(&quot;rsm %0,%%r0&bslash;n&quot; : : &quot;i&quot; (PSW_I) : &quot;memory&quot; )
DECL|macro|local_irq_enable
mdefine_line|#define local_irq_enable()&t;__asm__ __volatile__(&quot;ssm %0,%%r0&bslash;n&quot; : : &quot;i&quot; (PSW_I) : &quot;memory&quot; )
DECL|macro|local_irq_save
mdefine_line|#define local_irq_save(x) &bslash;&n;&t;__asm__ __volatile__(&quot;rsm %1,%0&quot; : &quot;=r&quot; (x) :&quot;i&quot; (PSW_I) : &quot;memory&quot; )
DECL|macro|local_irq_restore
mdefine_line|#define local_irq_restore(x) &bslash;&n;&t;__asm__ __volatile__(&quot;mtsm %0&quot; : : &quot;r&quot; (x) : &quot;memory&quot; )
DECL|macro|irqs_disabled
mdefine_line|#define irqs_disabled()&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long flags;&t;&t;&bslash;&n;&t;local_save_flags(flags);&t;&bslash;&n;&t;(flags &amp; PSW_I) == 0;&t;&t;&bslash;&n;})
DECL|macro|mfctl
mdefine_line|#define mfctl(reg)&t;({&t;&t;&bslash;&n;&t;unsigned long cr;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&bslash;&n;&t;&t;&quot;mfctl &quot; #reg &quot;,%0&quot; :&t;&bslash;&n;&t;&t; &quot;=r&quot; (cr)&t;&t;&bslash;&n;&t;);&t;&t;&t;&t;&bslash;&n;&t;cr;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|mtctl
mdefine_line|#define mtctl(gr, cr) &bslash;&n;&t;__asm__ __volatile__(&quot;mtctl %0,%1&quot; &bslash;&n;&t;&t;: /* no outputs */ &bslash;&n;&t;&t;: &quot;r&quot; (gr), &quot;i&quot; (cr))
multiline_comment|/* these are here to de-mystefy the calling code, and to provide hooks */
multiline_comment|/* which I needed for debugging EIEM problems -PB */
DECL|macro|get_eiem
mdefine_line|#define get_eiem() mfctl(15)
DECL|function|set_eiem
r_static
r_inline
r_void
id|set_eiem
c_func
(paren
r_int
r_int
id|val
)paren
(brace
id|mtctl
c_func
(paren
id|val
comma
l_int|15
)paren
suffix:semicolon
)brace
DECL|macro|mfsp
mdefine_line|#define mfsp(reg)&t;({&t;&t;&bslash;&n;&t;unsigned long cr;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&bslash;&n;&t;&t;&quot;mfsp &quot; #reg &quot;,%0&quot; :&t;&bslash;&n;&t;&t; &quot;=r&quot; (cr)&t;&t;&bslash;&n;&t;);&t;&t;&t;&t;&bslash;&n;&t;cr;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|mtsp
mdefine_line|#define mtsp(gr, cr) &bslash;&n;&t;__asm__ __volatile__(&quot;mtsp %0,%1&quot; &bslash;&n;&t;&t;: /* no outputs */ &bslash;&n;&t;&t;: &quot;r&quot; (gr), &quot;i&quot; (cr))
multiline_comment|/*&n;** This is simply the barrier() macro from linux/kernel.h but when serial.c&n;** uses tqueue.h uses smp_mb() defined using barrier(), linux/kernel.h&n;** hasn&squot;t yet been included yet so it fails, thus repeating the macro here.&n;**&n;** PA-RISC architecture allows for weakly ordered memory accesses although&n;** none of the processors use it. There is a strong ordered bit that is&n;** set in the O-bit of the page directory entry. Operating systems that&n;** can not tolerate out of order accesses should set this bit when mapping&n;** pages. The O-bit of the PSW should also be set to 1 (I don&squot;t believe any&n;** of the processor implemented the PSW O-bit). The PCX-W ERS states that&n;** the TLB O-bit is not implemented so the page directory does not need to&n;** have the O-bit set when mapping pages (section 3.1). This section also&n;** states that the PSW Y, Z, G, and O bits are not implemented.&n;** So it looks like nothing needs to be done for parisc-linux (yet).&n;** (thanks to chada for the above comment -ggg)&n;**&n;** The __asm__ op below simple prevents gcc/ld from reordering&n;** instructions across the mb() &quot;call&quot;.&n;*/
DECL|macro|mb
mdefine_line|#define mb()&t;&t;__asm__ __volatile__(&quot;&quot;:::&quot;memory&quot;);&t;/* barrier() */
DECL|macro|rmb
mdefine_line|#define rmb()&t;&t;mb()
DECL|macro|wmb
mdefine_line|#define wmb()&t;&t;mb()
DECL|macro|smp_mb
mdefine_line|#define smp_mb()&t;mb()
DECL|macro|smp_rmb
mdefine_line|#define smp_rmb()&t;mb()
DECL|macro|smp_wmb
mdefine_line|#define smp_wmb()&t;mb()
DECL|macro|smp_read_barrier_depends
mdefine_line|#define smp_read_barrier_depends()&t;do { } while(0)
DECL|macro|read_barrier_depends
mdefine_line|#define read_barrier_depends()&t;&t;do { } while(0)
DECL|macro|set_mb
mdefine_line|#define set_mb(var, value)&t;&t;do { var = value; mb(); } while (0)
DECL|macro|set_wmb
mdefine_line|#define set_wmb(var, value)&t;&t;do { var = value; wmb(); } while (0)
multiline_comment|/* LDCW, the only atomic read-write operation PA-RISC has. *sigh*.  */
DECL|macro|__ldcw
mdefine_line|#define __ldcw(a) ({ &bslash;&n;&t;unsigned __ret; &bslash;&n;&t;__asm__ __volatile__(&quot;ldcw 0(%1),%0&quot; : &quot;=r&quot; (__ret) : &quot;r&quot; (a)); &bslash;&n;&t;__ret; &bslash;&n;})
macro_line|#ifdef CONFIG_SMP
multiline_comment|/*&n; * Your basic SMP spinlocks, allowing only a single CPU anywhere&n; */
r_typedef
r_struct
(brace
DECL|member|lock
r_volatile
r_int
r_int
id|__attribute__
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|16
)paren
)paren
)paren
id|lock
suffix:semicolon
DECL|typedef|spinlock_t
)brace
id|spinlock_t
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
