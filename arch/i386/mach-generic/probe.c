multiline_comment|/* Copyright 2003 Andi Kleen, SuSE Labs. &n; * Subject to the GNU Public License, v.2 &n; * &n; * Generic x86 APIC driver probe layer.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/cpumask.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/fixmap.h&gt;
macro_line|#include &lt;asm/mpspec.h&gt;
macro_line|#include &lt;asm/apicdef.h&gt;
macro_line|#include &lt;asm/genapic.h&gt;
r_extern
r_struct
id|genapic
id|apic_summit
suffix:semicolon
r_extern
r_struct
id|genapic
id|apic_bigsmp
suffix:semicolon
r_extern
r_struct
id|genapic
id|apic_default
suffix:semicolon
DECL|variable|genapic
r_struct
id|genapic
op_star
id|genapic
op_assign
op_amp
id|apic_default
suffix:semicolon
DECL|variable|__initdata
r_struct
id|genapic
op_star
id|apic_probe
(braket
)braket
id|__initdata
op_assign
(brace
op_amp
id|apic_summit
comma
op_amp
id|apic_bigsmp
comma
op_amp
id|apic_default
comma
multiline_comment|/* must be last */
l_int|NULL
comma
)brace
suffix:semicolon
DECL|function|generic_apic_probe
r_void
id|__init
id|generic_apic_probe
c_func
(paren
r_char
op_star
id|command_line
)paren
(brace
r_char
op_star
id|s
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|changed
op_assign
l_int|0
suffix:semicolon
id|s
op_assign
id|strstr
c_func
(paren
id|command_line
comma
l_string|&quot;apic=&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|s
op_logical_and
(paren
id|s
op_eq
id|command_line
op_logical_or
id|isspace
c_func
(paren
id|s
(braket
op_minus
l_int|1
)braket
)paren
)paren
)paren
(brace
r_char
op_star
id|p
op_assign
id|strchr
c_func
(paren
id|s
comma
l_char|&squot; &squot;
)paren
comma
id|old
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
id|p
op_assign
id|strchr
c_func
(paren
id|s
comma
l_char|&squot;&bslash;0&squot;
)paren
suffix:semicolon
id|old
op_assign
op_star
id|p
suffix:semicolon
op_star
id|p
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
op_logical_neg
id|changed
op_logical_and
id|apic_probe
(braket
id|i
)braket
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|apic_probe
(braket
id|i
)braket
op_member_access_from_pointer
id|name
comma
id|s
op_plus
l_int|5
)paren
)paren
(brace
id|changed
op_assign
l_int|1
suffix:semicolon
id|genapic
op_assign
id|apic_probe
(braket
id|i
)braket
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|changed
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Unknown genapic `%s&squot; specified.&bslash;n&quot;
comma
id|s
)paren
suffix:semicolon
op_star
id|p
op_assign
id|old
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
op_logical_neg
id|changed
op_logical_and
id|apic_probe
(braket
id|i
)braket
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|apic_probe
(braket
id|i
)braket
op_member_access_from_pointer
id|probe
c_func
(paren
)paren
)paren
(brace
id|changed
op_assign
l_int|1
suffix:semicolon
id|genapic
op_assign
id|apic_probe
(braket
id|i
)braket
suffix:semicolon
)brace
)brace
multiline_comment|/* Not visible without early console */
r_if
c_cond
(paren
op_logical_neg
id|changed
)paren
id|panic
c_func
(paren
l_string|&quot;Didn&squot;t find an APIC driver&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Using APIC driver %s&bslash;n&quot;
comma
id|genapic-&gt;name
)paren
suffix:semicolon
)brace
multiline_comment|/* These functions can switch the APIC even after the initial -&gt;probe() */
DECL|function|mps_oem_check
r_int
id|__init
id|mps_oem_check
c_func
(paren
r_struct
id|mp_config_table
op_star
id|mpc
comma
r_char
op_star
id|oem
comma
r_char
op_star
id|productid
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|apic_probe
(braket
id|i
)braket
suffix:semicolon
op_increment
id|i
)paren
(brace
r_if
c_cond
(paren
id|apic_probe
(braket
id|i
)braket
op_member_access_from_pointer
id|mps_oem_check
c_func
(paren
id|mpc
comma
id|oem
comma
id|productid
)paren
)paren
(brace
id|genapic
op_assign
id|apic_probe
(braket
id|i
)braket
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Switched to APIC driver `%s&squot;.&bslash;n&quot;
comma
id|genapic-&gt;name
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|acpi_madt_oem_check
r_int
id|__init
id|acpi_madt_oem_check
c_func
(paren
r_char
op_star
id|oem_id
comma
r_char
op_star
id|oem_table_id
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|apic_probe
(braket
id|i
)braket
suffix:semicolon
op_increment
id|i
)paren
(brace
r_if
c_cond
(paren
id|apic_probe
(braket
id|i
)braket
op_member_access_from_pointer
id|acpi_madt_oem_check
c_func
(paren
id|oem_id
comma
id|oem_table_id
)paren
)paren
(brace
id|genapic
op_assign
id|apic_probe
(braket
id|i
)braket
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Switched to APIC driver `%s&squot;.&bslash;n&quot;
comma
id|genapic-&gt;name
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hard_smp_processor_id
r_int
id|hard_smp_processor_id
c_func
(paren
r_void
)paren
(brace
r_return
id|genapic
op_member_access_from_pointer
id|get_apic_id
c_func
(paren
op_star
(paren
r_int
r_int
op_star
)paren
(paren
id|APIC_BASE
op_plus
id|APIC_ID
)paren
)paren
suffix:semicolon
)brace
eof
