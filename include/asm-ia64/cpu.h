macro_line|#ifndef _ASM_IA64_CPU_H_
DECL|macro|_ASM_IA64_CPU_H_
mdefine_line|#define _ASM_IA64_CPU_H_
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/cpu.h&gt;
macro_line|#include &lt;linux/topology.h&gt;
macro_line|#include &lt;linux/percpu.h&gt;
DECL|struct|ia64_cpu
r_struct
id|ia64_cpu
(brace
DECL|member|cpu
r_struct
id|cpu
id|cpu
suffix:semicolon
)brace
suffix:semicolon
id|DECLARE_PER_CPU
c_func
(paren
r_struct
id|ia64_cpu
comma
id|cpu_devices
)paren
suffix:semicolon
id|DECLARE_PER_CPU
c_func
(paren
r_int
comma
id|cpu_state
)paren
suffix:semicolon
macro_line|#endif /* _ASM_IA64_CPU_H_ */
eof
