multiline_comment|/*&n; * include/linux/cpu.h - generic cpu definition&n; *&n; * This is mainly for topological representation. We define the &n; * basic &squot;struct cpu&squot; here, which can be embedded in per-arch &n; * definitions of processors.&n; *&n; * Basic handling of the devices is done in drivers/base/cpu.c&n; * and system devices are handled in drivers/base/sys.c. &n; *&n; * CPUs are exported via driverfs in the class/cpu/devices/&n; * directory. &n; *&n; * Per-cpu interfaces can be implemented using a struct device_interface. &n; * See the following for how to do this: &n; * - drivers/base/intf.c &n; * - Documentation/driver-model/interface.txt&n; */
macro_line|#ifndef _LINUX_CPU_H_
DECL|macro|_LINUX_CPU_H_
mdefine_line|#define _LINUX_CPU_H_
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/node.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
DECL|struct|cpu
r_struct
id|cpu
(brace
DECL|member|node_id
r_int
id|node_id
suffix:semicolon
multiline_comment|/* The node which contains the CPU */
DECL|member|sysdev
r_struct
id|sys_device
id|sysdev
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|register_cpu
c_func
(paren
r_struct
id|cpu
op_star
comma
r_int
comma
r_struct
id|node
op_star
)paren
suffix:semicolon
r_extern
r_struct
r_class
id|cpu_class
suffix:semicolon
r_struct
id|notifier_block
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
multiline_comment|/* Need to know about CPUs going up/down? */
r_extern
r_int
id|register_cpu_notifier
c_func
(paren
r_struct
id|notifier_block
op_star
id|nb
)paren
suffix:semicolon
r_extern
r_void
id|unregister_cpu_notifier
c_func
(paren
r_struct
id|notifier_block
op_star
id|nb
)paren
suffix:semicolon
r_int
id|cpu_up
c_func
(paren
r_int
r_int
id|cpu
)paren
suffix:semicolon
macro_line|#else
DECL|function|register_cpu_notifier
r_static
r_inline
r_int
id|register_cpu_notifier
c_func
(paren
r_struct
id|notifier_block
op_star
id|nb
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|unregister_cpu_notifier
r_static
r_inline
r_void
id|unregister_cpu_notifier
c_func
(paren
r_struct
id|notifier_block
op_star
id|nb
)paren
(brace
)brace
macro_line|#endif /* CONFIG_SMP */
multiline_comment|/* Stop CPUs going up and down. */
r_extern
r_struct
id|semaphore
id|cpucontrol
suffix:semicolon
macro_line|#endif /* _LINUX_CPU_H_ */
eof
