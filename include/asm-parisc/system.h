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
DECL|macro|pa_psw
mdefine_line|#define pa_psw(task) ((struct pa_psw *) ((char *) (task) + TASK_PT_PSW))
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
DECL|macro|prepare_to_switch
mdefine_line|#define prepare_to_switch()&t;do { } while(0)
DECL|macro|switch_to
mdefine_line|#define switch_to(prev, next, last) do {&t;&t;&t;&bslash;&n;&t;(last) = _switch_to(prev, next);&t;&t;&t;&bslash;&n;} while(0)
multiline_comment|/* borrowed this from sparc64 -- probably the SMP case is hosed for us */
macro_line|#ifdef CONFIG_SMP
DECL|macro|smp_mb
mdefine_line|#define smp_mb()&t;mb()
DECL|macro|smp_rmb
mdefine_line|#define smp_rmb()&t;rmb()
DECL|macro|smp_wmb
mdefine_line|#define smp_wmb()&t;wmb()
macro_line|#else
multiline_comment|/* This is simply the barrier() macro from linux/kernel.h but when serial.c&n; * uses tqueue.h uses smp_mb() defined using barrier(), linux/kernel.h&n; * hasn&squot;t yet been included yet so it fails, thus repeating the macro here.&n; */
DECL|macro|smp_mb
mdefine_line|#define smp_mb()&t;__asm__ __volatile__(&quot;&quot;:::&quot;memory&quot;);
DECL|macro|smp_rmb
mdefine_line|#define smp_rmb()&t;__asm__ __volatile__(&quot;&quot;:::&quot;memory&quot;);
DECL|macro|smp_wmb
mdefine_line|#define smp_wmb()&t;__asm__ __volatile__(&quot;&quot;:::&quot;memory&quot;);
macro_line|#endif
multiline_comment|/* interrupt control */
DECL|macro|__save_flags
mdefine_line|#define __save_flags(x)&t;__asm__ __volatile__(&quot;ssm 0, %0&quot; : &quot;=r&quot; (x) : : &quot;memory&quot;)
DECL|macro|__restore_flags
mdefine_line|#define __restore_flags(x) __asm__ __volatile__(&quot;mtsm %0&quot; : : &quot;r&quot; (x) : &quot;memory&quot;)
DECL|macro|__cli
mdefine_line|#define __cli()&t;__asm__ __volatile__(&quot;rsm %0,%%r0&bslash;n&quot; : : &quot;i&quot; (PSW_I) : &quot;memory&quot; )
DECL|macro|__sti
mdefine_line|#define __sti()&t;__asm__ __volatile__(&quot;ssm %0,%%r0&bslash;n&quot; : : &quot;i&quot; (PSW_I) : &quot;memory&quot; )
DECL|macro|local_irq_save
mdefine_line|#define local_irq_save(x) &bslash;&n;&t;__asm__ __volatile__(&quot;rsm %1,%0&quot; : &quot;=r&quot; (x) :&quot;i&quot; (PSW_I) : &quot;memory&quot; )
DECL|macro|local_irq_restore
mdefine_line|#define local_irq_restore(x) &bslash;&n;&t;__asm__ __volatile__(&quot;mtsm %0&quot; : : &quot;r&quot; (x) : &quot;memory&quot; )
DECL|macro|local_irq_disable
mdefine_line|#define local_irq_disable() __cli()
DECL|macro|local_irq_enable
mdefine_line|#define local_irq_enable()  __sti()
macro_line|#ifdef CONFIG_SMP
macro_line|#else
DECL|macro|cli
mdefine_line|#define cli() __cli()
DECL|macro|sti
mdefine_line|#define sti() __sti()
DECL|macro|save_flags
mdefine_line|#define save_flags(x) __save_flags(x)
DECL|macro|restore_flags
mdefine_line|#define restore_flags(x) __restore_flags(x)
macro_line|#endif
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
DECL|macro|mb
mdefine_line|#define mb()  __asm__ __volatile__ (&quot;sync&quot; : : :&quot;memory&quot;)
DECL|macro|wmb
mdefine_line|#define wmb() mb()
r_extern
r_int
r_int
id|__xchg
c_func
(paren
r_int
r_int
comma
r_int
r_int
op_star
comma
r_int
)paren
suffix:semicolon
DECL|macro|xchg
mdefine_line|#define xchg(ptr,x) &bslash;&n; (__typeof__(*(ptr)))__xchg((unsigned long)(x),(unsigned long*)(ptr),sizeof(*(ptr)))
multiline_comment|/* LDCW, the only atomic read-write operation PA-RISC has.  Sigh. */
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
