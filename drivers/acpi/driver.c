multiline_comment|/*&n; *  driver.c - ACPI driver&n; *&n; *  Copyright (C) 2000 Andrew Henroid&n; *  Copyright (C) 2001 Andrew Grover&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
multiline_comment|/*&n; * Changes&n; * David Woodhouse &lt;dwmw2@redhat.com&gt; 2000-12-6&n; * - Fix interruptible_sleep_on() races&n; * Andrew Grover &lt;andrew.grover@intel.com&gt; 2001-2-28&n; * - Major revamping&n; * Peter Breuer &lt;ptb@it.uc3m.es&gt; 2001-5-20&n; * - parse boot time params.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/sysctl.h&gt;
macro_line|#include &lt;linux/pm.h&gt;
macro_line|#include &lt;linux/acpi.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;acpi.h&quot;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT&t;OS_DEPENDENT
id|MODULE_NAME
(paren
l_string|&quot;driver&quot;
)paren
DECL|variable|acpi_fadt
id|FADT_DESCRIPTOR
id|acpi_fadt
suffix:semicolon
DECL|variable|acpi_disabled
r_static
r_int
id|acpi_disabled
op_assign
l_int|0
suffix:semicolon
DECL|enum|acpi_blacklist_predicates
r_enum
id|acpi_blacklist_predicates
(brace
DECL|enumerator|all_versions
id|all_versions
comma
DECL|enumerator|less_than_or_equal
id|less_than_or_equal
comma
DECL|enumerator|equal
id|equal
comma
DECL|enumerator|greater_than_or_equal
id|greater_than_or_equal
comma
)brace
suffix:semicolon
DECL|struct|acpi_blacklist_item
r_struct
id|acpi_blacklist_item
(brace
DECL|member|oem_id
r_char
id|oem_id
(braket
l_int|7
)braket
suffix:semicolon
DECL|member|oem_table_id
r_char
id|oem_table_id
(braket
l_int|9
)braket
suffix:semicolon
DECL|member|oem_revision
id|u32
id|oem_revision
suffix:semicolon
DECL|member|oem_revision_predicate
r_enum
id|acpi_blacklist_predicates
id|oem_revision_predicate
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Currently, this blacklists based on items in the FADT. We may want to&n; * expand this to using other ACPI tables in the future, too.&n; */
DECL|variable|__initdata
r_static
r_struct
id|acpi_blacklist_item
id|acpi_blacklist
(braket
)braket
id|__initdata
op_assign
(brace
(brace
l_string|&quot;TOSHIB&quot;
comma
l_string|&quot;750     &quot;
comma
l_int|0x970814
comma
id|less_than_or_equal
)brace
comma
multiline_comment|/* Portege 7020, BIOS 8.10 */
(brace
l_string|&quot;&quot;
)brace
)brace
suffix:semicolon
r_int
DECL|function|acpi_blacklisted
id|acpi_blacklisted
c_func
(paren
id|FADT_DESCRIPTOR
op_star
id|fadt
)paren
(brace
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|acpi_blacklist
(braket
id|i
)braket
dot
id|oem_id
(braket
l_int|0
)braket
op_ne
l_char|&squot;&bslash;0&squot;
)paren
(brace
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|acpi_blacklist
(braket
id|i
)braket
dot
id|oem_id
comma
id|fadt-&gt;header.oem_id
comma
l_int|6
)paren
)paren
(brace
id|i
op_increment
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|acpi_blacklist
(braket
id|i
)braket
dot
id|oem_table_id
comma
id|fadt-&gt;header.oem_table_id
comma
l_int|8
)paren
)paren
(brace
id|i
op_increment
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|acpi_blacklist
(braket
id|i
)braket
dot
id|oem_revision_predicate
op_eq
id|all_versions
)paren
r_return
id|TRUE
suffix:semicolon
r_if
c_cond
(paren
id|acpi_blacklist
(braket
id|i
)braket
dot
id|oem_revision_predicate
op_eq
id|less_than_or_equal
op_logical_and
id|fadt-&gt;header.oem_revision
op_le
id|acpi_blacklist
(braket
id|i
)braket
dot
id|oem_revision
)paren
r_return
id|TRUE
suffix:semicolon
r_if
c_cond
(paren
id|acpi_blacklist
(braket
id|i
)braket
dot
id|oem_revision_predicate
op_eq
id|greater_than_or_equal
op_logical_and
id|fadt-&gt;header.oem_revision
op_ge
id|acpi_blacklist
(braket
id|i
)braket
dot
id|oem_revision
)paren
r_return
id|TRUE
suffix:semicolon
r_if
c_cond
(paren
id|acpi_blacklist
(braket
id|i
)braket
dot
id|oem_revision_predicate
op_eq
id|equal
op_logical_and
id|fadt-&gt;header.oem_revision
op_eq
id|acpi_blacklist
(braket
id|i
)braket
dot
id|oem_revision
)paren
r_return
id|TRUE
suffix:semicolon
id|i
op_increment
suffix:semicolon
)brace
r_return
id|FALSE
suffix:semicolon
)brace
multiline_comment|/*&n; * Start the interpreter&n; */
r_int
DECL|function|acpi_init
id|acpi_init
c_func
(paren
r_void
)paren
(brace
id|acpi_buffer
id|buffer
suffix:semicolon
id|acpi_system_info
id|sys_info
suffix:semicolon
r_if
c_cond
(paren
id|PM_IS_ACTIVE
c_func
(paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;ACPI: APM is already active, exiting&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_if
c_cond
(paren
id|acpi_disabled
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;ACPI: disabled by cmdline, exiting&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|ACPI_SUCCESS
c_func
(paren
id|acpi_initialize_subsystem
c_func
(paren
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ACPI: Driver initialization failed&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
multiline_comment|/* from this point on, on error we must call acpi_terminate() */
r_if
c_cond
(paren
op_logical_neg
id|ACPI_SUCCESS
c_func
(paren
id|acpi_load_tables
c_func
(paren
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ACPI: System description table load failed&bslash;n&quot;
)paren
suffix:semicolon
id|acpi_terminate
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
multiline_comment|/* get a separate copy of the FADT for use by other drivers */
id|memset
c_func
(paren
op_amp
id|acpi_fadt
comma
l_int|0
comma
r_sizeof
(paren
id|acpi_fadt
)paren
)paren
suffix:semicolon
id|buffer.pointer
op_assign
op_amp
id|acpi_fadt
suffix:semicolon
id|buffer.length
op_assign
r_sizeof
(paren
id|acpi_fadt
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ACPI_SUCCESS
c_func
(paren
id|acpi_get_table
c_func
(paren
id|ACPI_TABLE_FADT
comma
l_int|1
comma
op_amp
id|buffer
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ACPI: Could not get FADT&bslash;n&quot;
)paren
suffix:semicolon
id|acpi_terminate
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_if
c_cond
(paren
id|acpi_blacklisted
c_func
(paren
op_amp
id|acpi_fadt
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ACPI: On blacklist -- BIOS not fully ACPI compliant&bslash;n&quot;
)paren
suffix:semicolon
id|acpi_terminate
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|buffer.length
op_assign
r_sizeof
(paren
id|sys_info
)paren
suffix:semicolon
id|buffer.pointer
op_assign
op_amp
id|sys_info
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ACPI_SUCCESS
(paren
id|acpi_get_system_info
c_func
(paren
op_amp
id|buffer
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ACPI: Could not get system info&bslash;n&quot;
)paren
suffix:semicolon
id|acpi_terminate
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;ACPI: Core Subsystem version [%x]&bslash;n&quot;
comma
id|sys_info.acpi_ca_version
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ACPI_SUCCESS
c_func
(paren
id|acpi_enable_subsystem
c_func
(paren
id|ACPI_FULL_INITIALIZATION
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ACPI: Subsystem enable failed&bslash;n&quot;
)paren
suffix:semicolon
id|acpi_terminate
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;ACPI: Subsystem enabled&bslash;n&quot;
)paren
suffix:semicolon
id|pm_active
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Terminate the interpreter&n; */
r_void
DECL|function|acpi_exit
id|acpi_exit
c_func
(paren
r_void
)paren
(brace
id|acpi_terminate
c_func
(paren
)paren
suffix:semicolon
id|pm_active
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ACPI: Subsystem disabled&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|variable|acpi_init
id|module_init
c_func
(paren
id|acpi_init
)paren
suffix:semicolon
DECL|variable|acpi_exit
id|module_exit
c_func
(paren
id|acpi_exit
)paren
suffix:semicolon
macro_line|#ifndef MODULE
DECL|function|acpi_setup
r_static
r_int
id|__init
id|acpi_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_while
c_loop
(paren
id|str
op_logical_and
op_star
id|str
)paren
(brace
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|str
comma
l_string|&quot;off&quot;
comma
l_int|3
)paren
op_eq
l_int|0
)paren
id|acpi_disabled
op_assign
l_int|1
suffix:semicolon
id|str
op_assign
id|strchr
c_func
(paren
id|str
comma
l_char|&squot;,&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|str
)paren
id|str
op_add_assign
id|strspn
c_func
(paren
id|str
comma
l_string|&quot;, &bslash;t&quot;
)paren
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;acpi=&quot;
comma
id|acpi_setup
)paren
suffix:semicolon
macro_line|#endif
eof
