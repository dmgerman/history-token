multiline_comment|/*&n; * APIC driver for the Unisys ES7000 chipset.&n; */
DECL|macro|APIC_DEFINITION
mdefine_line|#define APIC_DEFINITION 1
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/cpumask.h&gt;
macro_line|#include &lt;asm/mpspec.h&gt;
macro_line|#include &lt;asm/genapic.h&gt;
macro_line|#include &lt;asm/fixmap.h&gt;
macro_line|#include &lt;asm/apicdef.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/mach-es7000/mach_apicdef.h&gt;
macro_line|#include &lt;asm/mach-es7000/mach_apic.h&gt;
macro_line|#include &lt;asm/mach-es7000/mach_ipi.h&gt;
macro_line|#include &lt;asm/mach-es7000/mach_mpparse.h&gt;
macro_line|#include &lt;asm/mach-es7000/mach_wakecpu.h&gt;
DECL|function|probe_es7000
r_static
id|__init
r_int
id|probe_es7000
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* probed later in mptable/ACPI hooks */
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|apic_es7000
r_struct
id|genapic
id|apic_es7000
op_assign
id|APIC_INIT
c_func
(paren
l_string|&quot;es7000&quot;
comma
id|probe_es7000
)paren
suffix:semicolon
eof
