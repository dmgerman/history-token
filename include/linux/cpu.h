multiline_comment|/*&n; * cpu.h - generic cpu defition&n; *&n; * This is mainly for topological representation. We define the &n; * basic &squot;struct cpu&squot; here, which can be embedded in per-arch &n; * definitions of processors.&n; *&n; * Basic handling of the devices is done in drivers/base/cpu.c&n; * and system devices are handled in drivers/base/sys.c. &n; *&n; * CPUs are exported via driverfs in the class/cpu/devices/&n; * directory. &n; *&n; * Per-cpu interfaces can be implemented using a struct device_interface. &n; * See the following for how to do this: &n; * - drivers/base/intf.c &n; * - Documentation/driver-model/interface.txt&n; *&n; */
macro_line|#include &lt;linux/device.h&gt;
r_extern
r_struct
id|device_class
id|cpu_devclass
suffix:semicolon
DECL|struct|cpu
r_struct
id|cpu
(brace
DECL|member|sysdev
r_struct
id|sys_device
id|sysdev
suffix:semicolon
)brace
suffix:semicolon
eof
