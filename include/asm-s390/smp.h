multiline_comment|/*&n; *  include/asm-s390/smp.h&n; *&n; *  S390 version&n; *    Copyright (C) 1999 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Denis Joseph Barrow (djbarrow@de.ibm.com,barrow_dj@yahoo.com),&n; *               Martin Schwidefsky (schwidefsky@de.ibm.com)&n; */
macro_line|#ifndef __ASM_SMP_H
DECL|macro|__ASM_SMP_H
mdefine_line|#define __ASM_SMP_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#if defined(__KERNEL__) &amp;&amp; defined(CONFIG_SMP) &amp;&amp; !defined(__ASSEMBLY__)
macro_line|#include &lt;asm/lowcore.h&gt;
multiline_comment|/*&n;  s390 specific smp.c headers&n; */
r_typedef
r_struct
(brace
DECL|member|intresting
r_int
id|intresting
suffix:semicolon
DECL|member|ccode
id|sigp_ccode
id|ccode
suffix:semicolon
DECL|member|status
id|__u32
id|status
suffix:semicolon
DECL|member|cpu
id|__u16
id|cpu
suffix:semicolon
DECL|typedef|sigp_info
)brace
id|sigp_info
suffix:semicolon
r_extern
r_volatile
r_int
r_int
id|cpu_online_map
suffix:semicolon
r_extern
r_volatile
r_int
r_int
id|cpu_possible_map
suffix:semicolon
DECL|macro|NO_PROC_ID
mdefine_line|#define NO_PROC_ID&t;&t;0xFF&t;&t;/* No processor magic marker */
multiline_comment|/*&n; *&t;This magic constant controls our willingness to transfer&n; *&t;a process across CPUs. Such a transfer incurs misses on the L1&n; *&t;cache, and on a P6 or P5 with multiple L2 caches L2 hits. My&n; *&t;gut feeling is this will vary by board in value. For a board&n; *&t;with separate L2 cache it probably depends also on the RSS, and&n; *&t;for a board with shared L2 cache it ought to decay fast as other&n; *&t;processes are run.&n; */
DECL|macro|PROC_CHANGE_PENALTY
mdefine_line|#define PROC_CHANGE_PENALTY&t;20&t;&t;/* Schedule penalty */
DECL|macro|smp_processor_id
mdefine_line|#define smp_processor_id() (current_thread_info()-&gt;cpu)
DECL|macro|cpu_online
mdefine_line|#define cpu_online(cpu) (cpu_online_map &amp; (1&lt;&lt;(cpu)))
DECL|macro|cpu_possible
mdefine_line|#define cpu_possible(cpu) (cpu_possible_map &amp; (1&lt;&lt;(cpu)))
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
macro_line|#ifndef __s390x__
r_return
id|hweight32
c_func
(paren
id|cpu_online_map
)paren
suffix:semicolon
macro_line|#else /* __s390x__ */
r_return
id|hweight64
c_func
(paren
id|cpu_online_map
)paren
suffix:semicolon
macro_line|#endif /* __s390x__ */
)brace
DECL|function|any_online_cpu
r_extern
r_inline
r_int
r_int
id|any_online_cpu
c_func
(paren
r_int
r_int
id|mask
)paren
(brace
r_if
c_cond
(paren
id|mask
op_amp
id|cpu_online_map
)paren
r_return
id|__ffs
c_func
(paren
id|mask
op_amp
id|cpu_online_map
)paren
suffix:semicolon
r_return
id|NR_CPUS
suffix:semicolon
)brace
DECL|function|hard_smp_processor_id
r_extern
id|__inline__
id|__u16
id|hard_smp_processor_id
c_func
(paren
r_void
)paren
(brace
id|__u16
id|cpu_address
suffix:semicolon
id|__asm__
(paren
l_string|&quot;stap %0&bslash;n&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|cpu_address
)paren
)paren
suffix:semicolon
r_return
id|cpu_address
suffix:semicolon
)brace
DECL|macro|cpu_logical_map
mdefine_line|#define cpu_logical_map(cpu) (cpu)
macro_line|#endif
macro_line|#endif
eof
