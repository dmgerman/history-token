macro_line|#ifndef _ASM_I386_CPU_H_
DECL|macro|_ASM_I386_CPU_H_
mdefine_line|#define _ASM_I386_CPU_H_
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/cpu.h&gt;
macro_line|#include &lt;linux/topology.h&gt;
macro_line|#include &lt;asm/node.h&gt;
DECL|struct|i386_cpu
r_struct
id|i386_cpu
(brace
DECL|member|cpu
r_struct
id|cpu
id|cpu
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|i386_cpu
id|cpu_devices
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|function|arch_register_cpu
r_static
r_inline
r_int
(def_block
id|arch_register_cpu
c_func
(paren
r_int
id|num
)paren
(brace
r_struct
id|node
op_star
id|parent
op_assign
l_int|NULL
suffix:semicolon
macro_line|#ifdef CONFIG_NUMA
id|parent
op_assign
op_amp
id|node_devices
(braket
id|cpu_to_node
c_func
(paren
id|num
)paren
)braket
dot
id|node
suffix:semicolon
macro_line|#endif /* CONFIG_NUMA */
r_return
id|register_cpu
c_func
(paren
op_amp
id|cpu_devices
(braket
id|num
)braket
dot
id|cpu
comma
id|num
comma
id|parent
)paren
suffix:semicolon
)brace
)def_block
macro_line|#endif /* _ASM_I386_CPU_H_ */
eof
