multiline_comment|/* &n; * APIC driver for &quot;bigsmp&quot; XAPIC machines with more than 8 virtual CPUs.&n; * Drives the local APIC in &quot;clustered mode&quot;.&n; */
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
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/dmi.h&gt;
macro_line|#include &lt;asm/mach-bigsmp/mach_apic.h&gt;
macro_line|#include &lt;asm/mach-bigsmp/mach_apicdef.h&gt;
macro_line|#include &lt;asm/mach-bigsmp/mach_ipi.h&gt;
macro_line|#include &lt;asm/mach-default/mach_mpparse.h&gt;
DECL|variable|dmi_bigsmp
r_static
r_int
id|dmi_bigsmp
suffix:semicolon
multiline_comment|/* can be set by dmi scanners */
DECL|function|hp_ht_bigsmp
r_static
id|__init
r_int
id|hp_ht_bigsmp
c_func
(paren
r_struct
id|dmi_system_id
op_star
id|d
)paren
(brace
macro_line|#ifdef CONFIG_X86_GENERICARCH
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;%s detected: force use of apic=bigsmp&bslash;n&quot;
comma
id|d-&gt;ident
)paren
suffix:semicolon
id|dmi_bigsmp
op_assign
l_int|1
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|bigsmp_dmi_table
r_static
r_struct
id|dmi_system_id
id|__initdata
id|bigsmp_dmi_table
(braket
)braket
op_assign
(brace
(brace
id|hp_ht_bigsmp
comma
l_string|&quot;HP ProLiant DL760 G2&quot;
comma
(brace
id|DMI_MATCH
c_func
(paren
id|DMI_BIOS_VENDOR
comma
l_string|&quot;HP&quot;
)paren
comma
id|DMI_MATCH
c_func
(paren
id|DMI_BIOS_VERSION
comma
l_string|&quot;P44-&quot;
)paren
comma
)brace
)brace
comma
(brace
id|hp_ht_bigsmp
comma
l_string|&quot;HP ProLiant DL740&quot;
comma
(brace
id|DMI_MATCH
c_func
(paren
id|DMI_BIOS_VENDOR
comma
l_string|&quot;HP&quot;
)paren
comma
id|DMI_MATCH
c_func
(paren
id|DMI_BIOS_VERSION
comma
l_string|&quot;P47-&quot;
)paren
comma
)brace
)brace
comma
(brace
)brace
)brace
suffix:semicolon
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
id|dmi_check_system
c_func
(paren
id|bigsmp_dmi_table
)paren
suffix:semicolon
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
