multiline_comment|/* &n; * APIC driver for &quot;bigsmp&quot; XAPIC machines with more than 8 virtual CPUs.&n; * Drives the local APIC in &quot;clustered mode&quot;.&n; */
DECL|macro|APIC_DEFINITION
mdefine_line|#define APIC_DEFINITION 1
macro_line|#include &lt;asm/genapic.h&gt;
macro_line|#include &lt;asm/fixmap.h&gt;
macro_line|#include &lt;asm/apicdef.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/mach-bigsmp/mach_apic.h&gt;
macro_line|#include &lt;asm/mach-bigsmp/mach_apicdef.h&gt;
macro_line|#include &lt;asm/mach-bigsmp/mach_ipi.h&gt;
macro_line|#include &lt;asm/mach-default/mach_mpparse.h&gt;
DECL|variable|dmi_bigsmp
r_int
id|dmi_bigsmp
suffix:semicolon
multiline_comment|/* can be set by dmi scanners */
DECL|function|probe_bigsmp
r_static
id|__init
r_int
id|probe_bigsmp
c_func
(paren
r_void
)paren
(brace
r_return
id|dmi_bigsmp
suffix:semicolon
)brace
DECL|variable|apic_bigsmp
r_struct
id|genapic
id|apic_bigsmp
op_assign
id|APIC_INIT
c_func
(paren
l_string|&quot;bigsmp&quot;
comma
id|probe_bigsmp
)paren
suffix:semicolon
eof
