multiline_comment|/* smp.h: PPC specific SMP stuff.&n; *&n; * Original was a copy of sparc smp.h.  Now heavily modified&n; * for PPC.&n; *&n; * Copyright (C) 1996 David S. Miller (davem@caip.rutgers.edu)&n; * Copyright (C) 1996-2001 Cort Dougan &lt;cort@fsmlabs.com&gt;&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef _PPC_SMP_H
DECL|macro|_PPC_SMP_H
mdefine_line|#define _PPC_SMP_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#ifdef CONFIG_SMP
macro_line|#ifndef __ASSEMBLY__
DECL|struct|cpuinfo_PPC
r_struct
id|cpuinfo_PPC
(brace
DECL|member|loops_per_jiffy
r_int
r_int
id|loops_per_jiffy
suffix:semicolon
DECL|member|pvr
r_int
r_int
id|pvr
suffix:semicolon
DECL|member|pgd_cache
r_int
r_int
op_star
id|pgd_cache
suffix:semicolon
DECL|member|pte_cache
r_int
r_int
op_star
id|pte_cache
suffix:semicolon
DECL|member|pgtable_cache_sz
r_int
r_int
id|pgtable_cache_sz
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|cpuinfo_PPC
id|cpu_data
(braket
id|NR_CPUS
)braket
suffix:semicolon
r_extern
r_int
r_int
id|cpu_online_map
suffix:semicolon
r_extern
r_int
r_int
id|smp_proc_in_lock
(braket
id|NR_CPUS
)braket
suffix:semicolon
r_extern
r_volatile
r_int
r_int
id|cpu_callin_map
(braket
id|NR_CPUS
)braket
suffix:semicolon
r_extern
r_void
id|smp_store_cpu_info
c_func
(paren
r_int
id|id
)paren
suffix:semicolon
r_extern
r_void
id|smp_send_tlb_invalidate
c_func
(paren
r_int
)paren
suffix:semicolon
r_extern
r_void
id|smp_send_xmon_break
c_func
(paren
r_int
id|cpu
)paren
suffix:semicolon
r_struct
id|pt_regs
suffix:semicolon
r_extern
r_void
id|smp_message_recv
c_func
(paren
r_int
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
DECL|macro|NO_PROC_ID
mdefine_line|#define NO_PROC_ID&t;&t;0xFF            /* No processor magic marker */
DECL|macro|PROC_CHANGE_PENALTY
mdefine_line|#define PROC_CHANGE_PENALTY&t;20
multiline_comment|/* 1 to 1 mapping on PPC -- Cort */
DECL|macro|cpu_logical_map
mdefine_line|#define cpu_logical_map(cpu) (cpu)
DECL|macro|cpu_number_map
mdefine_line|#define cpu_number_map(x) (x)
DECL|macro|smp_processor_id
mdefine_line|#define smp_processor_id() (current-&gt;processor)
r_extern
r_int
id|smp_hw_index
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|macro|hard_smp_processor_id
mdefine_line|#define hard_smp_processor_id() (smp_hw_index[smp_processor_id()])
DECL|struct|klock_info_struct
r_struct
id|klock_info_struct
(brace
DECL|member|kernel_flag
r_int
r_int
id|kernel_flag
suffix:semicolon
DECL|member|akp
r_int
r_char
id|akp
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|klock_info_struct
id|klock_info
suffix:semicolon
DECL|macro|KLOCK_HELD
mdefine_line|#define KLOCK_HELD       0xffffffff
DECL|macro|KLOCK_CLEAR
mdefine_line|#define KLOCK_CLEAR      0x0
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#else /* !(CONFIG_SMP) */
macro_line|#endif /* !(CONFIG_SMP) */
macro_line|#endif /* !(_PPC_SMP_H) */
macro_line|#endif /* __KERNEL__ */
eof
