multiline_comment|/* &n; * Default generic APIC driver. This handles upto 8 CPUs.&n; */
DECL|macro|APIC_DEFINITION
mdefine_line|#define APIC_DEFINITION 1
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/cpumask.h&gt;
macro_line|#include &lt;asm/mpspec.h&gt;
macro_line|#include &lt;asm/mach-default/mach_apicdef.h&gt;
macro_line|#include &lt;asm/genapic.h&gt;
macro_line|#include &lt;asm/fixmap.h&gt;
macro_line|#include &lt;asm/apicdef.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/mach-default/mach_apic.h&gt;
macro_line|#include &lt;asm/mach-default/mach_ipi.h&gt;
macro_line|#include &lt;asm/mach-default/mach_mpparse.h&gt;
multiline_comment|/* should be called last. */
DECL|function|probe_default
r_static
id|__init
r_int
id|probe_default
c_func
(paren
r_void
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|apic_default
r_struct
id|genapic
id|apic_default
op_assign
id|APIC_INIT
c_func
(paren
l_string|&quot;default&quot;
comma
id|probe_default
)paren
suffix:semicolon
eof
