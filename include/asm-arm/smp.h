multiline_comment|/*&n; *  linux/include/asm-arm/smp.h&n; *&n; *  Copyright (C) 2004-2005 ARM Ltd.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#ifndef __ASM_ARM_SMP_H
DECL|macro|__ASM_ARM_SMP_H
mdefine_line|#define __ASM_ARM_SMP_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/cpumask.h&gt;
macro_line|#include &lt;linux/thread_info.h&gt;
macro_line|#include &lt;asm/arch/smp.h&gt;
macro_line|#ifndef CONFIG_SMP
macro_line|# error &quot;&lt;asm-arm/smp.h&gt; included in non-SMP build&quot;
macro_line|#endif
DECL|macro|smp_processor_id
mdefine_line|#define smp_processor_id()&t;(current_thread_info()-&gt;cpu)
r_extern
id|cpumask_t
id|cpu_present_mask
suffix:semicolon
DECL|macro|cpu_possible_map
mdefine_line|#define cpu_possible_map cpu_present_mask
multiline_comment|/*&n; * at the moment, there&squot;s not a big penalty for changing CPUs&n; * (the &gt;big&lt; penalty is running SMP in the first place)&n; */
DECL|macro|PROC_CHANGE_PENALTY
mdefine_line|#define PROC_CHANGE_PENALTY&t;&t;15
multiline_comment|/*&n; * Move global data into per-processor storage.&n; */
r_extern
r_void
id|smp_store_cpu_info
c_func
(paren
r_int
r_int
id|cpuid
)paren
suffix:semicolon
multiline_comment|/*&n; * Raise an IPI cross call on CPUs in callmap.&n; */
r_extern
r_void
id|smp_cross_call
c_func
(paren
id|cpumask_t
id|callmap
)paren
suffix:semicolon
multiline_comment|/*&n; * Boot a secondary CPU, and assign it the specified idle task.&n; * This also gives us the initial stack to use for this CPU.&n; */
r_extern
r_int
id|__init
id|boot_secondary
c_func
(paren
r_int
r_int
id|cpu
comma
r_struct
id|task_struct
op_star
)paren
suffix:semicolon
macro_line|#endif /* ifndef __ASM_ARM_SMP_H */
eof
