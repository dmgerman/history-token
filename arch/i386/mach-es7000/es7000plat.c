multiline_comment|/*&n; * Written by: Garry Forsgren, Unisys Corporation&n; *             Natalie Protasevich, Unisys Corporation&n; * This file contains the code to configure and interface&n; * with Unisys ES7000 series hardware system manager.&n; *&n; * Copyright (c) 2003 Unisys Corporation.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Unisys Corporation, Township Line &amp; Union Meeting&n; * Roads-A, Unisys Way, Blue Bell, Pennsylvania, 19424, or:&n; *&n; * http://www.unisys.com&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/notifier.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/acpi.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/nmi.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/apicdef.h&gt;
macro_line|#include &quot;es7000.h&quot;
multiline_comment|/*&n; * ES7000 Globals&n; */
DECL|variable|psai
r_volatile
r_int
r_int
op_star
id|psai
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|mip_reg
r_struct
id|mip_reg
op_star
id|mip_reg
suffix:semicolon
DECL|variable|host_reg
r_struct
id|mip_reg
op_star
id|host_reg
suffix:semicolon
DECL|variable|mip_port
r_int
id|mip_port
suffix:semicolon
DECL|variable|mip_addr
DECL|variable|host_addr
r_int
r_int
id|mip_addr
comma
id|host_addr
suffix:semicolon
macro_line|#if defined(CONFIG_X86_IO_APIC) &amp;&amp; (defined(CONFIG_ACPI_INTERPRETER) || defined(CONFIG_ACPI_BOOT))
multiline_comment|/*&n; * GSI override for ES7000 platforms.&n; */
DECL|variable|base
r_static
r_int
r_int
id|base
suffix:semicolon
r_static
r_int
DECL|function|es7000_rename_gsi
id|es7000_rename_gsi
c_func
(paren
r_int
id|ioapic
comma
r_int
id|gsi
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|base
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
id|i
OL
id|nr_ioapics
suffix:semicolon
id|i
op_increment
)paren
id|base
op_add_assign
id|nr_ioapic_registers
(braket
id|i
)braket
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|ioapic
op_logical_and
(paren
id|gsi
OL
l_int|16
)paren
)paren
id|gsi
op_add_assign
id|base
suffix:semicolon
r_return
id|gsi
suffix:semicolon
)brace
macro_line|#endif 
singleline_comment|// (CONFIG_X86_IO_APIC) &amp;&amp; (CONFIG_ACPI_INTERPRETER || CONFIG_ACPI_BOOT)
multiline_comment|/*&n; * Parse the OEM Table&n; */
r_int
id|__init
DECL|function|parse_unisys_oem
id|parse_unisys_oem
(paren
r_char
op_star
id|oemptr
comma
r_int
id|oem_entries
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|success
op_assign
l_int|0
suffix:semicolon
r_int
r_char
id|type
comma
id|size
suffix:semicolon
r_int
r_int
id|val
suffix:semicolon
r_char
op_star
id|tp
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|psai
op_star
id|psaip
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|mip_reg_info
op_star
id|mi
suffix:semicolon
r_struct
id|mip_reg
op_star
id|host
comma
op_star
id|mip
suffix:semicolon
id|tp
op_assign
id|oemptr
suffix:semicolon
id|tp
op_add_assign
l_int|8
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
op_le
id|oem_entries
suffix:semicolon
id|i
op_increment
)paren
(brace
id|type
op_assign
op_star
id|tp
op_increment
suffix:semicolon
id|size
op_assign
op_star
id|tp
op_increment
suffix:semicolon
id|tp
op_sub_assign
l_int|2
suffix:semicolon
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
id|MIP_REG
suffix:colon
id|mi
op_assign
(paren
r_struct
id|mip_reg_info
op_star
)paren
id|tp
suffix:semicolon
id|val
op_assign
id|MIP_RD_LO
c_func
(paren
id|mi-&gt;host_reg
)paren
suffix:semicolon
id|host_addr
op_assign
id|val
suffix:semicolon
id|host
op_assign
(paren
r_struct
id|mip_reg
op_star
)paren
id|val
suffix:semicolon
id|host_reg
op_assign
id|__va
c_func
(paren
id|host
)paren
suffix:semicolon
id|val
op_assign
id|MIP_RD_LO
c_func
(paren
id|mi-&gt;mip_reg
)paren
suffix:semicolon
id|mip_port
op_assign
id|MIP_PORT
c_func
(paren
id|mi-&gt;mip_info
)paren
suffix:semicolon
id|mip_addr
op_assign
id|val
suffix:semicolon
id|mip
op_assign
(paren
r_struct
id|mip_reg
op_star
)paren
id|val
suffix:semicolon
id|mip_reg
op_assign
id|__va
c_func
(paren
id|mip
)paren
suffix:semicolon
id|Dprintk
c_func
(paren
l_string|&quot;es7000_mipcfg: host_reg = 0x%lx &bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|host_reg
)paren
suffix:semicolon
id|Dprintk
c_func
(paren
l_string|&quot;es7000_mipcfg: mip_reg = 0x%lx &bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|mip_reg
)paren
suffix:semicolon
id|success
op_increment
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MIP_PSAI_REG
suffix:colon
id|psaip
op_assign
(paren
r_struct
id|psai
op_star
)paren
id|tp
suffix:semicolon
r_if
c_cond
(paren
id|tp
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|psaip-&gt;addr
)paren
id|psai
op_assign
id|__va
c_func
(paren
id|psaip-&gt;addr
)paren
suffix:semicolon
r_else
id|psai
op_assign
l_int|NULL
suffix:semicolon
id|success
op_increment
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_eq
l_int|6
)paren
r_break
suffix:semicolon
id|tp
op_add_assign
id|size
suffix:semicolon
)brace
r_if
c_cond
(paren
id|success
OL
l_int|2
)paren
(brace
id|es7000_plat
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;&bslash;nEnabling ES7000 specific features...&bslash;n&quot;
)paren
suffix:semicolon
id|es7000_plat
op_assign
l_int|1
suffix:semicolon
id|ioapic_renumber_irq
op_assign
id|es7000_rename_gsi
suffix:semicolon
)brace
r_return
id|es7000_plat
suffix:semicolon
)brace
r_int
id|__init
DECL|function|find_unisys_acpi_oem_table
id|find_unisys_acpi_oem_table
c_func
(paren
r_int
r_int
op_star
id|oem_addr
comma
r_int
op_star
id|length
)paren
(brace
r_struct
id|acpi_table_rsdp
op_star
id|rsdp
op_assign
l_int|NULL
suffix:semicolon
r_int
r_int
id|rsdp_phys
op_assign
l_int|0
suffix:semicolon
r_struct
id|acpi_table_header
op_star
id|header
op_assign
l_int|NULL
suffix:semicolon
r_int
id|i
suffix:semicolon
r_struct
id|acpi_table_sdt
id|sdt
suffix:semicolon
id|rsdp_phys
op_assign
id|acpi_find_rsdp
c_func
(paren
)paren
suffix:semicolon
id|rsdp
op_assign
id|__va
c_func
(paren
id|rsdp_phys
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rsdp-&gt;rsdt_address
)paren
(brace
r_struct
id|acpi_table_rsdt
op_star
id|mapped_rsdt
op_assign
l_int|NULL
suffix:semicolon
id|sdt.pa
op_assign
id|rsdp-&gt;rsdt_address
suffix:semicolon
id|header
op_assign
(paren
r_struct
id|acpi_table_header
op_star
)paren
id|__acpi_map_table
c_func
(paren
id|sdt.pa
comma
r_sizeof
(paren
r_struct
id|acpi_table_header
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|header
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|sdt.count
op_assign
(paren
id|header-&gt;length
op_minus
r_sizeof
(paren
r_struct
id|acpi_table_header
)paren
)paren
op_rshift
l_int|3
suffix:semicolon
id|mapped_rsdt
op_assign
(paren
r_struct
id|acpi_table_rsdt
op_star
)paren
id|__acpi_map_table
c_func
(paren
id|sdt.pa
comma
id|header-&gt;length
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mapped_rsdt
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|header
op_assign
op_amp
id|mapped_rsdt-&gt;header
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|sdt.count
suffix:semicolon
id|i
op_increment
)paren
id|sdt.entry
(braket
id|i
)braket
dot
id|pa
op_assign
(paren
r_int
r_int
)paren
id|mapped_rsdt-&gt;entry
(braket
id|i
)braket
suffix:semicolon
)brace
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|sdt.count
suffix:semicolon
id|i
op_increment
)paren
(brace
id|header
op_assign
(paren
r_struct
id|acpi_table_header
op_star
)paren
id|__acpi_map_table
c_func
(paren
id|sdt.entry
(braket
id|i
)braket
dot
id|pa
comma
r_sizeof
(paren
r_struct
id|acpi_table_header
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|header
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
(paren
r_char
op_star
)paren
op_amp
id|header-&gt;signature
comma
l_string|&quot;OEM1&quot;
comma
l_int|4
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
(paren
r_char
op_star
)paren
op_amp
id|header-&gt;oem_id
comma
l_string|&quot;UNISYS&quot;
comma
l_int|6
)paren
)paren
(brace
r_void
op_star
id|addr
suffix:semicolon
r_struct
id|oem_table
op_star
id|t
suffix:semicolon
id|acpi_table_print
c_func
(paren
id|header
comma
id|sdt.entry
(braket
id|i
)braket
dot
id|pa
)paren
suffix:semicolon
id|t
op_assign
(paren
r_struct
id|oem_table
op_star
)paren
id|__acpi_map_table
c_func
(paren
id|sdt.entry
(braket
id|i
)braket
dot
id|pa
comma
id|header-&gt;length
)paren
suffix:semicolon
id|addr
op_assign
(paren
r_void
op_star
)paren
id|__acpi_map_table
c_func
(paren
id|t-&gt;OEMTableAddr
comma
id|t-&gt;OEMTableSize
)paren
suffix:semicolon
op_star
id|length
op_assign
id|header-&gt;length
suffix:semicolon
op_star
id|oem_addr
op_assign
(paren
r_int
r_int
)paren
id|addr
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
)brace
id|Dprintk
c_func
(paren
l_string|&quot;ES7000: did not find Unisys ACPI OEM table!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_static
r_void
DECL|function|es7000_spin
id|es7000_spin
c_func
(paren
r_int
id|n
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
id|i
op_increment
OL
id|n
)paren
id|rep_nop
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
r_int
id|__init
DECL|function|es7000_mip_write
id|es7000_mip_write
c_func
(paren
r_struct
id|mip_reg
op_star
id|mip_reg
)paren
(brace
r_int
id|status
op_assign
l_int|0
suffix:semicolon
r_int
id|spin
suffix:semicolon
id|spin
op_assign
id|MIP_SPIN
suffix:semicolon
r_while
c_loop
(paren
(paren
(paren
r_int
r_int
r_int
)paren
id|host_reg-&gt;off_38
op_amp
(paren
r_int
r_int
r_int
)paren
id|MIP_VALID
)paren
op_ne
l_int|0
)paren
(brace
r_if
c_cond
(paren
op_decrement
id|spin
op_le
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;es7000_mip_write: Timeout waiting for Host Valid Flag&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|es7000_spin
c_func
(paren
id|MIP_SPIN
)paren
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|host_reg
comma
id|mip_reg
comma
r_sizeof
(paren
r_struct
id|mip_reg
)paren
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|1
comma
id|mip_port
)paren
suffix:semicolon
id|spin
op_assign
id|MIP_SPIN
suffix:semicolon
r_while
c_loop
(paren
(paren
(paren
r_int
r_int
r_int
)paren
id|mip_reg-&gt;off_38
op_amp
(paren
r_int
r_int
r_int
)paren
id|MIP_VALID
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
op_decrement
id|spin
op_le
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;es7000_mip_write: Timeout waiting for MIP Valid Flag&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|es7000_spin
c_func
(paren
id|MIP_SPIN
)paren
suffix:semicolon
)brace
id|status
op_assign
(paren
(paren
r_int
r_int
r_int
)paren
id|mip_reg-&gt;off_0
op_amp
(paren
r_int
r_int
r_int
)paren
l_int|0xffff0000000000ULL
)paren
op_rshift
l_int|48
suffix:semicolon
id|mip_reg-&gt;off_38
op_assign
(paren
(paren
r_int
r_int
r_int
)paren
id|mip_reg-&gt;off_38
op_amp
(paren
r_int
r_int
r_int
)paren
op_complement
id|MIP_VALID
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
r_int
DECL|function|es7000_start_cpu
id|es7000_start_cpu
c_func
(paren
r_int
id|cpu
comma
r_int
r_int
id|eip
)paren
(brace
r_int
r_int
id|vect
op_assign
l_int|0
comma
id|psaival
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|psai
op_eq
l_int|NULL
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|vect
op_assign
(paren
(paren
r_int
r_int
)paren
id|__pa
c_func
(paren
id|eip
)paren
op_div
l_int|0x1000
)paren
op_lshift
l_int|16
suffix:semicolon
id|psaival
op_assign
(paren
l_int|0x1000000
op_or
id|vect
op_or
id|cpu
)paren
suffix:semicolon
r_while
c_loop
(paren
op_star
id|psai
op_amp
l_int|0x1000000
)paren
suffix:semicolon
op_star
id|psai
op_assign
id|psaival
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_int
DECL|function|es7000_stop_cpu
id|es7000_stop_cpu
c_func
(paren
r_int
id|cpu
)paren
(brace
r_int
id|startup
suffix:semicolon
r_if
c_cond
(paren
id|psai
op_eq
l_int|NULL
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|startup
op_assign
(paren
l_int|0x1000000
op_or
id|cpu
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
op_star
id|psai
op_amp
l_int|0xff00ffff
)paren
op_ne
id|startup
)paren
suffix:semicolon
id|startup
op_assign
(paren
op_star
id|psai
op_amp
l_int|0xff0000
)paren
op_rshift
l_int|16
suffix:semicolon
op_star
id|psai
op_and_assign
l_int|0xffffff
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_void
id|__init
DECL|function|es7000_sw_apic
id|es7000_sw_apic
c_func
(paren
)paren
(brace
r_if
c_cond
(paren
id|es7000_plat
)paren
(brace
r_int
id|mip_status
suffix:semicolon
r_struct
id|mip_reg
id|es7000_mip_reg
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;ES7000: Enabling APIC mode.&bslash;n&quot;
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|es7000_mip_reg
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|mip_reg
)paren
)paren
suffix:semicolon
id|es7000_mip_reg.off_0
op_assign
id|MIP_SW_APIC
suffix:semicolon
id|es7000_mip_reg.off_38
op_assign
(paren
id|MIP_VALID
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|mip_status
op_assign
id|es7000_mip_write
c_func
(paren
op_amp
id|es7000_mip_reg
)paren
)paren
op_ne
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;es7000_sw_apic: command failed, status = %x&bslash;n&quot;
comma
id|mip_status
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
eof
