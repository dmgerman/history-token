macro_line|#ifndef __ASM_CRIS_SYSTEM_H
DECL|macro|__ASM_CRIS_SYSTEM_H
mdefine_line|#define __ASM_CRIS_SYSTEM_H
macro_line|#include &lt;asm/arch/system.h&gt;
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
DECL|macro|barrier
mdefine_line|#define barrier() __asm__ __volatile__(&quot;&quot;: : :&quot;memory&quot;)
DECL|macro|mb
mdefine_line|#define mb() barrier()
DECL|macro|rmb
mdefine_line|#define rmb() mb()
DECL|macro|wmb
mdefine_line|#define wmb() mb()
DECL|macro|read_barrier_depends
mdefine_line|#define read_barrier_depends() do { } while(0)
DECL|macro|set_mb
mdefine_line|#define set_mb(var, value)  do { var = value; mb(); } while (0)
DECL|macro|set_wmb
mdefine_line|#define set_wmb(var, value) do { var = value; wmb(); } while (0)
macro_line|#ifdef CONFIG_SMP
DECL|macro|smp_mb
mdefine_line|#define smp_mb()        mb()
DECL|macro|smp_rmb
mdefine_line|#define smp_rmb()       rmb()
DECL|macro|smp_wmb
mdefine_line|#define smp_wmb()       wmb()
DECL|macro|smp_read_barrier_depends
mdefine_line|#define smp_read_barrier_depends()     read_barrier_depends()
macro_line|#else
DECL|macro|smp_mb
mdefine_line|#define smp_mb()        barrier()
DECL|macro|smp_rmb
mdefine_line|#define smp_rmb()       barrier()
DECL|macro|smp_wmb
mdefine_line|#define smp_wmb()       barrier()
DECL|macro|smp_read_barrier_depends
mdefine_line|#define smp_read_barrier_depends()     do { } while(0)
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
DECL|function|__xchg
r_extern
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
multiline_comment|/* since Etrax doesn&squot;t have any atomic xchg instructions, we need to disable&n;     irq&squot;s (if enabled) and do it with move.d&squot;s */
r_int
r_int
id|flags
comma
id|temp
suffix:semicolon
id|local_save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* save flags, including irq enable bit */
id|local_irq_disable
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
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* restore irq enable bit */
r_return
id|x
suffix:semicolon
)brace
DECL|macro|arch_align_stack
mdefine_line|#define arch_align_stack(x) (x)
macro_line|#endif
eof
