macro_line|#ifndef __ASM_MIPS_SMP_H
DECL|macro|__ASM_MIPS_SMP_H
mdefine_line|#define __ASM_MIPS_SMP_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_SMP
macro_line|#include &lt;asm/spinlock.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/current.h&gt;
multiline_comment|/* Mappings are straight across.  If we want&n;   to add support for disabling cpus and such,&n;   we&squot;ll have to do what the mips64 port does here */
DECL|macro|cpu_logical_map
mdefine_line|#define cpu_logical_map(cpu)&t;(cpu)
DECL|macro|cpu_number_map
mdefine_line|#define cpu_number_map(cpu)     (cpu)
DECL|macro|smp_processor_id
mdefine_line|#define smp_processor_id()  (current-&gt;processor)
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
macro_line|#endif /* CONFIG_SMP */
macro_line|#endif /* __ASM_MIPS_SMP_H */
eof
