multiline_comment|/*&n; * include/linux/node.h - generic node definition&n; *&n; * This is mainly for topological representation. We define the &n; * basic &squot;struct node&squot; here, which can be embedded in per-arch &n; * definitions of processors.&n; *&n; * Basic handling of the devices is done in drivers/base/node.c&n; * and system devices are handled in drivers/base/sys.c. &n; *&n; * Nodes are exported via driverfs in the class/node/devices/&n; * directory. &n; *&n; * Per-node interfaces can be implemented using a struct device_interface. &n; * See the following for how to do this: &n; * - drivers/base/intf.c &n; * - Documentation/driver-model/interface.txt&n; */
macro_line|#ifndef _LINUX_NODE_H_
DECL|macro|_LINUX_NODE_H_
mdefine_line|#define _LINUX_NODE_H_
macro_line|#include &lt;linux/sysdev.h&gt;
DECL|struct|node
r_struct
id|node
(brace
DECL|member|cpumap
r_int
r_int
id|cpumap
suffix:semicolon
multiline_comment|/* Bitmap of CPUs on the Node */
DECL|member|sysdev
r_struct
id|sys_device
id|sysdev
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|register_node
c_func
(paren
r_struct
id|node
op_star
comma
r_int
comma
r_struct
id|node
op_star
)paren
suffix:semicolon
DECL|macro|to_node
mdefine_line|#define to_node(_root) container_of(_root, struct node, sysroot)
DECL|macro|to_root
mdefine_line|#define to_root(_dev) container_of(_dev, struct sys_root, dev)
macro_line|#endif /* _LINUX_NODE_H_ */
eof
