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
macro_line|#include &quot;driver.h&quot;
macro_line|#ifdef CONFIG_ACPI_KERNEL_CONFIG
macro_line|#include &lt;asm/efi.h&gt;
DECL|macro|ACPI_USE_EFI
mdefine_line|#define ACPI_USE_EFI
macro_line|#endif
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
multiline_comment|/*&n; * Start the interpreter&n; */
r_int
DECL|function|acpi_init
id|acpi_init
c_func
(paren
r_void
)paren
(brace
id|ACPI_PHYSICAL_ADDRESS
id|rsdp_phys
suffix:semicolon
id|ACPI_BUFFER
id|buffer
suffix:semicolon
id|ACPI_SYSTEM_INFO
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
macro_line|#ifndef ACPI_USE_EFI
r_if
c_cond
(paren
op_logical_neg
id|ACPI_SUCCESS
c_func
(paren
id|acpi_find_root_pointer
c_func
(paren
op_amp
id|rsdp_phys
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ACPI: System description tables not found&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
macro_line|#else
id|rsdp_phys
op_assign
id|efi.acpi
suffix:semicolon
macro_line|#endif
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
id|rsdp_phys
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
