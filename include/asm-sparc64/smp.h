multiline_comment|/* smp.h: Sparc64 specific SMP stuff.&n; *&n; * Copyright (C) 1996 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _SPARC64_SMP_H
DECL|macro|_SPARC64_SMP_H
mdefine_line|#define _SPARC64_SMP_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;asm/asi.h&gt;
macro_line|#include &lt;asm/starfire.h&gt;
macro_line|#include &lt;asm/spitfire.h&gt;
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;linux/cpumask.h&gt;
macro_line|#include &lt;linux/cache.h&gt;
macro_line|#endif /* !(__ASSEMBLY__) */
macro_line|#ifdef CONFIG_SMP
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; *&t;Private routines/data&n; */
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
r_extern
r_int
r_char
id|boot_cpu_id
suffix:semicolon
r_extern
id|cpumask_t
id|phys_cpu_present_map
suffix:semicolon
DECL|macro|cpu_possible
mdefine_line|#define cpu_possible(cpu)&t;cpu_isset(cpu, phys_cpu_present_map)
DECL|macro|cpu_online
mdefine_line|#define cpu_online(cpu)&t;&t;cpu_isset(cpu, cpu_online_map)
r_extern
id|atomic_t
id|sparc64_num_cpus_possible
suffix:semicolon
DECL|macro|num_possible_cpus
mdefine_line|#define num_possible_cpus()&t;(atomic_read(&amp;sparc64_num_cpus_possible))
multiline_comment|/*&n; *&t;General functions that each host system must provide.&n; */
DECL|function|hard_smp_processor_id
r_static
id|__inline__
r_int
id|hard_smp_processor_id
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|tlb_type
op_eq
id|cheetah
op_logical_or
id|tlb_type
op_eq
id|cheetah_plus
)paren
(brace
r_int
r_int
id|cfg
comma
id|ver
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;rdpr %%ver, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ver
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ver
op_rshift
l_int|32
)paren
op_eq
l_int|0x003e0016
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;ldxa [%%g0] %1, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|cfg
)paren
suffix:colon
l_string|&quot;i&quot;
(paren
id|ASI_JBUS_CONFIG
)paren
)paren
suffix:semicolon
r_return
(paren
(paren
id|cfg
op_rshift
l_int|17
)paren
op_amp
l_int|0x1f
)paren
suffix:semicolon
)brace
r_else
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;ldxa [%%g0] %1, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|cfg
)paren
suffix:colon
l_string|&quot;i&quot;
(paren
id|ASI_SAFARI_CONFIG
)paren
)paren
suffix:semicolon
r_return
(paren
(paren
id|cfg
op_rshift
l_int|17
)paren
op_amp
l_int|0x3ff
)paren
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|this_is_starfire
op_ne
l_int|0
)paren
(brace
r_return
id|starfire_hard_smp_processor_id
c_func
(paren
)paren
suffix:semicolon
)brace
r_else
(brace
r_int
r_int
id|upaconfig
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;ldxa&t;[%%g0] %1, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|upaconfig
)paren
suffix:colon
l_string|&quot;i&quot;
(paren
id|ASI_UPA_CONFIG
)paren
)paren
suffix:semicolon
r_return
(paren
(paren
id|upaconfig
op_rshift
l_int|17
)paren
op_amp
l_int|0x1f
)paren
suffix:semicolon
)brace
)brace
DECL|macro|smp_processor_id
mdefine_line|#define smp_processor_id() (current_thread_info()-&gt;cpu)
macro_line|#endif /* !(__ASSEMBLY__) */
macro_line|#endif /* !(CONFIG_SMP) */
DECL|macro|NO_PROC_ID
mdefine_line|#define NO_PROC_ID&t;&t;0xFF
macro_line|#endif /* !(_SPARC64_SMP_H) */
eof
