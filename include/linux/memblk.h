multiline_comment|/*&n; * include/linux/memblk.h - generic memblk definition&n; *&n; * This is mainly for topological representation. We define the &n; * basic &squot;struct memblk&squot; here, which can be embedded in per-arch &n; * definitions of memory blocks.&n; *&n; * Basic handling of the devices is done in drivers/base/memblk.c&n; * and system devices are handled in drivers/base/sys.c. &n; *&n; * MemBlks are exported via driverfs in the class/memblk/devices/&n; * directory. &n; *&n; * Per-memblk interfaces can be implemented using a struct device_interface. &n; * See the following for how to do this: &n; * - drivers/base/intf.c &n; * - Documentation/driver-model/interface.txt&n; */
macro_line|#ifndef _LINUX_MEMBLK_H_
DECL|macro|_LINUX_MEMBLK_H_
mdefine_line|#define _LINUX_MEMBLK_H_
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/node.h&gt;
DECL|struct|memblk
r_struct
id|memblk
(brace
DECL|member|node_id
r_int
id|node_id
suffix:semicolon
multiline_comment|/* The node which contains the MemBlk */
DECL|member|sysdev
r_struct
id|sys_device
id|sysdev
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|register_memblk
c_func
(paren
r_struct
id|memblk
op_star
comma
r_int
comma
r_struct
id|node
op_star
)paren
suffix:semicolon
macro_line|#endif /* _LINUX_MEMBLK_H_ */
eof
