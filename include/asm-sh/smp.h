multiline_comment|/*&n; * Copyright (C) 2002 Paul Mundt&n; */
macro_line|#ifndef __ASM_SH_SMP_H
DECL|macro|__ASM_SH_SMP_H
mdefine_line|#define __ASM_SH_SMP_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#ifdef CONFIG_SMP
macro_line|#include &lt;asm/spinlock.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/current.h&gt;
r_extern
r_int
r_int
id|cpu_online_map
suffix:semicolon
DECL|macro|cpu_online
mdefine_line|#define cpu_online(cpu)&t;&t;(cpu_online_map &amp; (1 &lt;&lt; (cpu)))
DECL|macro|cpu_possible
mdefine_line|#define cpu_possible(cpu)&t;(cpu_online(cpu))
DECL|macro|smp_processor_id
mdefine_line|#define smp_processor_id()&t;(current_thread_info()-&gt;cpu)
DECL|function|num_online_cpus
r_extern
r_inline
r_int
r_int
id|num_online_cpus
c_func
(paren
r_void
)paren
(brace
r_return
id|hweight32
c_func
(paren
id|cpu_online_map
)paren
suffix:semicolon
)brace
multiline_comment|/* I&squot;ve no idea what the real meaning of this is */
DECL|macro|PROC_CHANGE_PENALTY
mdefine_line|#define PROC_CHANGE_PENALTY&t;20
DECL|macro|NO_PROC_ID
mdefine_line|#define NO_PROC_ID&t;(-1)
DECL|struct|smp_fn_call_struct
r_struct
id|smp_fn_call_struct
(brace
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|finished
id|atomic_t
id|finished
suffix:semicolon
DECL|member|fn
r_void
(paren
op_star
id|fn
)paren
(paren
r_void
op_star
)paren
suffix:semicolon
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|smp_fn_call_struct
id|smp_fn_call
suffix:semicolon
DECL|macro|SMP_MSG_RESCHEDULE
mdefine_line|#define SMP_MSG_RESCHEDULE&t;0x0001
macro_line|#endif /* CONFIG_SMP */
macro_line|#endif /* __ASM_SH_SMP_H */
eof
