macro_line|#ifndef _ASM_I386_CPU_H_
DECL|macro|_ASM_I386_CPU_H_
mdefine_line|#define _ASM_I386_CPU_H_
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/cpu.h&gt;
macro_line|#include &lt;asm/topology.h&gt;
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
macro_line|#ifdef CONFIG_NUMA
DECL|function|arch_register_cpu
r_static
r_inline
r_void
(def_block
id|arch_register_cpu
c_func
(paren
r_int
id|num
)paren
(brace
r_int
id|p_node
op_assign
id|__cpu_to_node
c_func
(paren
id|num
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p_node
op_ge
l_int|0
op_logical_and
id|p_node
OL
id|NR_CPUS
)paren
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
op_amp
id|node_devices
(braket
id|p_node
)braket
dot
id|node
)paren
suffix:semicolon
)brace
)def_block
macro_line|#else /* !CONFIG_NUMA */
DECL|function|arch_register_cpu
r_static
r_inline
r_void
(def_block
id|arch_register_cpu
c_func
(paren
r_int
id|num
)paren
(brace
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
(paren
r_struct
id|node
op_star
)paren
l_int|NULL
)paren
suffix:semicolon
)brace
)def_block
macro_line|#endif /* CONFIG_NUMA */
macro_line|#endif /* _ASM_I386_CPU_H_ */
eof
