multiline_comment|/*&n; *  acpi_tables.c - ACPI Boot-Time Table Parsing&n; *&n; *  Copyright (C) 2001 Paul Diefenbaugh &lt;paul.s.diefenbaugh@intel.com&gt;&n; *&n; * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; *&n; * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/acpi.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
DECL|macro|PREFIX
mdefine_line|#define PREFIX&t;&t;&t;&quot;ACPI: &quot;
DECL|macro|ACPI_MAX_TABLES
mdefine_line|#define ACPI_MAX_TABLES&t;&t;256
DECL|variable|acpi_table_signatures
r_static
r_char
op_star
id|acpi_table_signatures
(braket
id|ACPI_TABLE_COUNT
)braket
op_assign
(brace
(braket
id|ACPI_TABLE_UNKNOWN
)braket
op_assign
l_string|&quot;????&quot;
comma
(braket
id|ACPI_APIC
)braket
op_assign
l_string|&quot;APIC&quot;
comma
(braket
id|ACPI_BOOT
)braket
op_assign
l_string|&quot;BOOT&quot;
comma
(braket
id|ACPI_DBGP
)braket
op_assign
l_string|&quot;DBGP&quot;
comma
(braket
id|ACPI_DSDT
)braket
op_assign
l_string|&quot;DSDT&quot;
comma
(braket
id|ACPI_ECDT
)braket
op_assign
l_string|&quot;ECDT&quot;
comma
(braket
id|ACPI_ETDT
)braket
op_assign
l_string|&quot;ETDT&quot;
comma
(braket
id|ACPI_FADT
)braket
op_assign
l_string|&quot;FACP&quot;
comma
(braket
id|ACPI_FACS
)braket
op_assign
l_string|&quot;FACS&quot;
comma
(braket
id|ACPI_OEMX
)braket
op_assign
l_string|&quot;OEM&quot;
comma
(braket
id|ACPI_PSDT
)braket
op_assign
l_string|&quot;PSDT&quot;
comma
(braket
id|ACPI_SBST
)braket
op_assign
l_string|&quot;SBST&quot;
comma
(braket
id|ACPI_SLIT
)braket
op_assign
l_string|&quot;SLIT&quot;
comma
(braket
id|ACPI_SPCR
)braket
op_assign
l_string|&quot;SPCR&quot;
comma
(braket
id|ACPI_SRAT
)braket
op_assign
l_string|&quot;SRAT&quot;
comma
(braket
id|ACPI_SSDT
)braket
op_assign
l_string|&quot;SSDT&quot;
comma
(braket
id|ACPI_SPMI
)braket
op_assign
l_string|&quot;SPMI&quot;
comma
(braket
id|ACPI_HPET
)braket
op_assign
l_string|&quot;HPET&quot;
comma
(braket
id|ACPI_MCFG
)braket
op_assign
l_string|&quot;MCFG&quot;
comma
)brace
suffix:semicolon
DECL|variable|mps_inti_flags_polarity
r_static
r_char
op_star
id|mps_inti_flags_polarity
(braket
)braket
op_assign
(brace
l_string|&quot;dfl&quot;
comma
l_string|&quot;high&quot;
comma
l_string|&quot;res&quot;
comma
l_string|&quot;low&quot;
)brace
suffix:semicolon
DECL|variable|mps_inti_flags_trigger
r_static
r_char
op_star
id|mps_inti_flags_trigger
(braket
)braket
op_assign
(brace
l_string|&quot;dfl&quot;
comma
l_string|&quot;edge&quot;
comma
l_string|&quot;res&quot;
comma
l_string|&quot;level&quot;
)brace
suffix:semicolon
multiline_comment|/* System Description Table (RSDT/XSDT) */
DECL|struct|acpi_table_sdt
r_struct
id|acpi_table_sdt
(brace
DECL|member|pa
r_int
r_int
id|pa
suffix:semicolon
DECL|member|id
r_enum
id|acpi_table_id
id|id
suffix:semicolon
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|variable|sdt_pa
r_static
r_int
r_int
id|sdt_pa
suffix:semicolon
multiline_comment|/* Physical Address */
DECL|variable|sdt_count
r_static
r_int
r_int
id|sdt_count
suffix:semicolon
multiline_comment|/* Table count */
DECL|variable|sdt_entry
r_static
r_struct
id|acpi_table_sdt
id|sdt_entry
(braket
id|ACPI_MAX_TABLES
)braket
suffix:semicolon
r_void
DECL|function|acpi_table_print
id|acpi_table_print
(paren
r_struct
id|acpi_table_header
op_star
id|header
comma
r_int
r_int
id|phys_addr
)paren
(brace
r_char
op_star
id|name
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|header
)paren
r_return
suffix:semicolon
multiline_comment|/* Some table signatures aren&squot;t good table names */
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
id|acpi_table_signatures
(braket
id|ACPI_APIC
)braket
comma
r_sizeof
(paren
id|header-&gt;signature
)paren
)paren
)paren
(brace
id|name
op_assign
l_string|&quot;MADT&quot;
suffix:semicolon
)brace
r_else
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
id|acpi_table_signatures
(braket
id|ACPI_FADT
)braket
comma
r_sizeof
(paren
id|header-&gt;signature
)paren
)paren
)paren
(brace
id|name
op_assign
l_string|&quot;FADT&quot;
suffix:semicolon
)brace
r_else
id|name
op_assign
id|header-&gt;signature
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
id|PREFIX
l_string|&quot;%.4s (v%3.3d %6.6s %8.8s 0x%08x %.4s 0x%08x) @ 0x%p&bslash;n&quot;
comma
id|name
comma
id|header-&gt;revision
comma
id|header-&gt;oem_id
comma
id|header-&gt;oem_table_id
comma
id|header-&gt;oem_revision
comma
id|header-&gt;asl_compiler_id
comma
id|header-&gt;asl_compiler_revision
comma
(paren
r_void
op_star
)paren
id|phys_addr
)paren
suffix:semicolon
)brace
r_void
DECL|function|acpi_table_print_madt_entry
id|acpi_table_print_madt_entry
(paren
id|acpi_table_entry_header
op_star
id|header
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|header
)paren
r_return
suffix:semicolon
r_switch
c_cond
(paren
id|header-&gt;type
)paren
(brace
r_case
id|ACPI_MADT_LAPIC
suffix:colon
(brace
r_struct
id|acpi_table_lapic
op_star
id|p
op_assign
(paren
r_struct
id|acpi_table_lapic
op_star
)paren
id|header
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
id|PREFIX
l_string|&quot;LAPIC (acpi_id[0x%02x] lapic_id[0x%02x] %s)&bslash;n&quot;
comma
id|p-&gt;acpi_id
comma
id|p-&gt;id
comma
id|p-&gt;flags.enabled
ques
c_cond
l_string|&quot;enabled&quot;
suffix:colon
l_string|&quot;disabled&quot;
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ACPI_MADT_IOAPIC
suffix:colon
(brace
r_struct
id|acpi_table_ioapic
op_star
id|p
op_assign
(paren
r_struct
id|acpi_table_ioapic
op_star
)paren
id|header
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
id|PREFIX
l_string|&quot;IOAPIC (id[0x%02x] address[0x%08x] gsi_base[%d])&bslash;n&quot;
comma
id|p-&gt;id
comma
id|p-&gt;address
comma
id|p-&gt;global_irq_base
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ACPI_MADT_INT_SRC_OVR
suffix:colon
(brace
r_struct
id|acpi_table_int_src_ovr
op_star
id|p
op_assign
(paren
r_struct
id|acpi_table_int_src_ovr
op_star
)paren
id|header
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
id|PREFIX
l_string|&quot;INT_SRC_OVR (bus %d bus_irq %d global_irq %d %s %s)&bslash;n&quot;
comma
id|p-&gt;bus
comma
id|p-&gt;bus_irq
comma
id|p-&gt;global_irq
comma
id|mps_inti_flags_polarity
(braket
id|p-&gt;flags.polarity
)braket
comma
id|mps_inti_flags_trigger
(braket
id|p-&gt;flags.trigger
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;flags.reserved
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
id|PREFIX
l_string|&quot;INT_SRC_OVR unexpected reserved flags: 0x%x&bslash;n&quot;
comma
id|p-&gt;flags.reserved
)paren
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
r_case
id|ACPI_MADT_NMI_SRC
suffix:colon
(brace
r_struct
id|acpi_table_nmi_src
op_star
id|p
op_assign
(paren
r_struct
id|acpi_table_nmi_src
op_star
)paren
id|header
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
id|PREFIX
l_string|&quot;NMI_SRC (%s %s global_irq %d)&bslash;n&quot;
comma
id|mps_inti_flags_polarity
(braket
id|p-&gt;flags.polarity
)braket
comma
id|mps_inti_flags_trigger
(braket
id|p-&gt;flags.trigger
)braket
comma
id|p-&gt;global_irq
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ACPI_MADT_LAPIC_NMI
suffix:colon
(brace
r_struct
id|acpi_table_lapic_nmi
op_star
id|p
op_assign
(paren
r_struct
id|acpi_table_lapic_nmi
op_star
)paren
id|header
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
id|PREFIX
l_string|&quot;LAPIC_NMI (acpi_id[0x%02x] %s %s lint[0x%x])&bslash;n&quot;
comma
id|p-&gt;acpi_id
comma
id|mps_inti_flags_polarity
(braket
id|p-&gt;flags.polarity
)braket
comma
id|mps_inti_flags_trigger
(braket
id|p-&gt;flags.trigger
)braket
comma
id|p-&gt;lint
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ACPI_MADT_LAPIC_ADDR_OVR
suffix:colon
(brace
r_struct
id|acpi_table_lapic_addr_ovr
op_star
id|p
op_assign
(paren
r_struct
id|acpi_table_lapic_addr_ovr
op_star
)paren
id|header
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
id|PREFIX
l_string|&quot;LAPIC_ADDR_OVR (address[%p])&bslash;n&quot;
comma
(paren
r_void
op_star
)paren
(paren
r_int
r_int
)paren
id|p-&gt;address
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ACPI_MADT_IOSAPIC
suffix:colon
(brace
r_struct
id|acpi_table_iosapic
op_star
id|p
op_assign
(paren
r_struct
id|acpi_table_iosapic
op_star
)paren
id|header
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
id|PREFIX
l_string|&quot;IOSAPIC (id[0x%x] address[%p] gsi_base[%d])&bslash;n&quot;
comma
id|p-&gt;id
comma
(paren
r_void
op_star
)paren
(paren
r_int
r_int
)paren
id|p-&gt;address
comma
id|p-&gt;global_irq_base
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ACPI_MADT_LSAPIC
suffix:colon
(brace
r_struct
id|acpi_table_lsapic
op_star
id|p
op_assign
(paren
r_struct
id|acpi_table_lsapic
op_star
)paren
id|header
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
id|PREFIX
l_string|&quot;LSAPIC (acpi_id[0x%02x] lsapic_id[0x%02x] lsapic_eid[0x%02x] %s)&bslash;n&quot;
comma
id|p-&gt;acpi_id
comma
id|p-&gt;id
comma
id|p-&gt;eid
comma
id|p-&gt;flags.enabled
ques
c_cond
l_string|&quot;enabled&quot;
suffix:colon
l_string|&quot;disabled&quot;
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ACPI_MADT_PLAT_INT_SRC
suffix:colon
(brace
r_struct
id|acpi_table_plat_int_src
op_star
id|p
op_assign
(paren
r_struct
id|acpi_table_plat_int_src
op_star
)paren
id|header
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
id|PREFIX
l_string|&quot;PLAT_INT_SRC (%s %s type[0x%x] id[0x%04x] eid[0x%x] iosapic_vector[0x%x] global_irq[0x%x]&bslash;n&quot;
comma
id|mps_inti_flags_polarity
(braket
id|p-&gt;flags.polarity
)braket
comma
id|mps_inti_flags_trigger
(braket
id|p-&gt;flags.trigger
)braket
comma
id|p-&gt;type
comma
id|p-&gt;id
comma
id|p-&gt;eid
comma
id|p-&gt;iosapic_vector
comma
id|p-&gt;global_irq
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_WARNING
id|PREFIX
l_string|&quot;Found unsupported MADT entry (type = 0x%x)&bslash;n&quot;
comma
id|header-&gt;type
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_static
r_int
DECL|function|acpi_table_compute_checksum
id|acpi_table_compute_checksum
(paren
r_void
op_star
id|table_pointer
comma
r_int
r_int
id|length
)paren
(brace
id|u8
op_star
id|p
op_assign
(paren
id|u8
op_star
)paren
id|table_pointer
suffix:semicolon
r_int
r_int
id|remains
op_assign
id|length
suffix:semicolon
r_int
r_int
id|sum
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
op_logical_or
op_logical_neg
id|length
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_while
c_loop
(paren
id|remains
op_decrement
)paren
id|sum
op_add_assign
op_star
id|p
op_increment
suffix:semicolon
r_return
(paren
id|sum
op_amp
l_int|0xFF
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * acpi_get_table_header_early()&n; * for acpi_blacklisted(), acpi_table_get_sdt()&n; */
r_int
id|__init
DECL|function|acpi_get_table_header_early
id|acpi_get_table_header_early
(paren
r_enum
id|acpi_table_id
id|id
comma
r_struct
id|acpi_table_header
op_star
op_star
id|header
)paren
(brace
r_int
r_int
id|i
suffix:semicolon
r_enum
id|acpi_table_id
id|temp_id
suffix:semicolon
multiline_comment|/* DSDT is different from the rest */
r_if
c_cond
(paren
id|id
op_eq
id|ACPI_DSDT
)paren
id|temp_id
op_assign
id|ACPI_FADT
suffix:semicolon
r_else
id|temp_id
op_assign
id|id
suffix:semicolon
multiline_comment|/* Locate the table. */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|sdt_count
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|sdt_entry
(braket
id|i
)braket
dot
id|id
op_ne
id|temp_id
)paren
r_continue
suffix:semicolon
op_star
id|header
op_assign
(paren
r_void
op_star
)paren
id|__acpi_map_table
c_func
(paren
id|sdt_entry
(braket
id|i
)braket
dot
id|pa
comma
id|sdt_entry
(braket
id|i
)braket
dot
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|header
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
id|PREFIX
l_string|&quot;Unable to map %s&bslash;n&quot;
comma
id|acpi_table_signatures
(braket
id|temp_id
)braket
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
op_star
id|header
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
id|PREFIX
l_string|&quot;%s not present&bslash;n&quot;
comma
id|acpi_table_signatures
(braket
id|id
)braket
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
multiline_comment|/* Map the DSDT header via the pointer in the FADT */
r_if
c_cond
(paren
id|id
op_eq
id|ACPI_DSDT
)paren
(brace
r_struct
id|fadt_descriptor_rev2
op_star
id|fadt
op_assign
(paren
r_struct
id|fadt_descriptor_rev2
op_star
)paren
op_star
id|header
suffix:semicolon
r_if
c_cond
(paren
id|fadt-&gt;revision
op_eq
l_int|3
op_logical_and
id|fadt-&gt;Xdsdt
)paren
(brace
op_star
id|header
op_assign
(paren
r_void
op_star
)paren
id|__acpi_map_table
c_func
(paren
id|fadt-&gt;Xdsdt
comma
r_sizeof
(paren
r_struct
id|acpi_table_header
)paren
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|fadt-&gt;V1_dsdt
)paren
(brace
op_star
id|header
op_assign
(paren
r_void
op_star
)paren
id|__acpi_map_table
c_func
(paren
id|fadt-&gt;V1_dsdt
comma
r_sizeof
(paren
r_struct
id|acpi_table_header
)paren
)paren
suffix:semicolon
)brace
r_else
op_star
id|header
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|header
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
id|PREFIX
l_string|&quot;Unable to map DSDT&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_int
id|__init
DECL|function|acpi_table_parse_madt_family
id|acpi_table_parse_madt_family
(paren
r_enum
id|acpi_table_id
id|id
comma
r_int
r_int
id|madt_size
comma
r_int
id|entry_id
comma
id|acpi_madt_entry_handler
id|handler
comma
r_int
r_int
id|max_entries
)paren
(brace
r_void
op_star
id|madt
op_assign
l_int|NULL
suffix:semicolon
id|acpi_table_entry_header
op_star
id|entry
suffix:semicolon
r_int
r_int
id|count
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|madt_end
suffix:semicolon
r_int
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|handler
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* Locate the MADT (if exists). There should only be one. */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|sdt_count
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|sdt_entry
(braket
id|i
)braket
dot
id|id
op_ne
id|id
)paren
r_continue
suffix:semicolon
id|madt
op_assign
(paren
r_void
op_star
)paren
id|__acpi_map_table
c_func
(paren
id|sdt_entry
(braket
id|i
)braket
dot
id|pa
comma
id|sdt_entry
(braket
id|i
)braket
dot
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|madt
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
id|PREFIX
l_string|&quot;Unable to map %s&bslash;n&quot;
comma
id|acpi_table_signatures
(braket
id|id
)braket
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|madt
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
id|PREFIX
l_string|&quot;%s not present&bslash;n&quot;
comma
id|acpi_table_signatures
(braket
id|id
)braket
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|madt_end
op_assign
(paren
r_int
r_int
)paren
id|madt
op_plus
id|sdt_entry
(braket
id|i
)braket
dot
id|size
suffix:semicolon
multiline_comment|/* Parse all entries looking for a match. */
id|entry
op_assign
(paren
id|acpi_table_entry_header
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|madt
op_plus
id|madt_size
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
(paren
r_int
r_int
)paren
id|entry
)paren
op_plus
r_sizeof
(paren
id|acpi_table_entry_header
)paren
OL
id|madt_end
)paren
(brace
r_if
c_cond
(paren
id|entry-&gt;type
op_eq
id|entry_id
op_logical_and
(paren
op_logical_neg
id|max_entries
op_logical_or
id|count
op_increment
OL
id|max_entries
)paren
)paren
r_if
c_cond
(paren
id|handler
c_func
(paren
id|entry
comma
id|madt_end
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|entry
op_assign
(paren
id|acpi_table_entry_header
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|entry
op_plus
id|entry-&gt;length
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|max_entries
op_logical_and
id|count
OG
id|max_entries
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
id|PREFIX
l_string|&quot;[%s:0x%02x] ignored %i entries of &quot;
l_string|&quot;%i found&bslash;n&quot;
comma
id|acpi_table_signatures
(braket
id|id
)braket
comma
id|entry_id
comma
id|count
op_minus
id|max_entries
comma
id|count
)paren
suffix:semicolon
)brace
r_return
id|count
suffix:semicolon
)brace
r_int
id|__init
DECL|function|acpi_table_parse_madt
id|acpi_table_parse_madt
(paren
r_enum
id|acpi_madt_entry_id
id|id
comma
id|acpi_madt_entry_handler
id|handler
comma
r_int
r_int
id|max_entries
)paren
(brace
r_return
id|acpi_table_parse_madt_family
c_func
(paren
id|ACPI_APIC
comma
r_sizeof
(paren
r_struct
id|acpi_table_madt
)paren
comma
id|id
comma
id|handler
comma
id|max_entries
)paren
suffix:semicolon
)brace
r_int
id|__init
DECL|function|acpi_table_parse
id|acpi_table_parse
(paren
r_enum
id|acpi_table_id
id|id
comma
id|acpi_table_handler
id|handler
)paren
(brace
r_int
id|count
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|handler
)paren
r_return
op_minus
id|EINVAL
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
id|sdt_count
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|sdt_entry
(braket
id|i
)braket
dot
id|id
op_ne
id|id
)paren
r_continue
suffix:semicolon
id|count
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|count
op_eq
l_int|1
)paren
id|handler
c_func
(paren
id|sdt_entry
(braket
id|i
)braket
dot
id|pa
comma
id|sdt_entry
(braket
id|i
)braket
dot
id|size
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
id|KERN_WARNING
id|PREFIX
l_string|&quot;%d duplicate %s table ignored.&bslash;n&quot;
comma
id|count
comma
id|acpi_table_signatures
(braket
id|id
)braket
)paren
suffix:semicolon
)brace
r_return
id|count
suffix:semicolon
)brace
r_static
r_int
id|__init
DECL|function|acpi_table_get_sdt
id|acpi_table_get_sdt
(paren
r_struct
id|acpi_table_rsdp
op_star
id|rsdp
)paren
(brace
r_struct
id|acpi_table_header
op_star
id|header
op_assign
l_int|NULL
suffix:semicolon
r_int
r_int
id|i
comma
id|id
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rsdp
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* First check XSDT (but only on ACPI 2.0-compatible systems) */
r_if
c_cond
(paren
(paren
id|rsdp-&gt;revision
op_ge
l_int|2
)paren
op_logical_and
(paren
(paren
(paren
r_struct
id|acpi20_table_rsdp
op_star
)paren
id|rsdp
)paren
op_member_access_from_pointer
id|xsdt_address
)paren
)paren
(brace
r_struct
id|acpi_table_xsdt
op_star
id|mapped_xsdt
op_assign
l_int|NULL
suffix:semicolon
id|sdt_pa
op_assign
(paren
(paren
r_struct
id|acpi20_table_rsdp
op_star
)paren
id|rsdp
)paren
op_member_access_from_pointer
id|xsdt_address
suffix:semicolon
multiline_comment|/* map in just the header */
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
id|sdt_pa
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
(brace
id|printk
c_func
(paren
id|KERN_WARNING
id|PREFIX
l_string|&quot;Unable to map XSDT header&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
multiline_comment|/* remap in the entire table before processing */
id|mapped_xsdt
op_assign
(paren
r_struct
id|acpi_table_xsdt
op_star
)paren
id|__acpi_map_table
c_func
(paren
id|sdt_pa
comma
id|header-&gt;length
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mapped_xsdt
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
id|PREFIX
l_string|&quot;Unable to map XSDT&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|header
op_assign
op_amp
id|mapped_xsdt-&gt;header
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|header-&gt;signature
comma
l_string|&quot;XSDT&quot;
comma
l_int|4
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
id|PREFIX
l_string|&quot;XSDT signature incorrect&bslash;n&quot;
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
id|acpi_table_compute_checksum
c_func
(paren
id|header
comma
id|header-&gt;length
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
id|PREFIX
l_string|&quot;Invalid XSDT checksum&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|sdt_count
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
r_if
c_cond
(paren
id|sdt_count
OG
id|ACPI_MAX_TABLES
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
id|PREFIX
l_string|&quot;Truncated %lu XSDT entries&bslash;n&quot;
comma
(paren
id|sdt_count
op_minus
id|ACPI_MAX_TABLES
)paren
)paren
suffix:semicolon
id|sdt_count
op_assign
id|ACPI_MAX_TABLES
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|sdt_count
suffix:semicolon
id|i
op_increment
)paren
id|sdt_entry
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
id|mapped_xsdt-&gt;entry
(braket
id|i
)braket
suffix:semicolon
)brace
multiline_comment|/* Then check RSDT */
r_else
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
id|sdt_pa
op_assign
id|rsdp-&gt;rsdt_address
suffix:semicolon
multiline_comment|/* map in just the header */
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
id|sdt_pa
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
(brace
id|printk
c_func
(paren
id|KERN_WARNING
id|PREFIX
l_string|&quot;Unable to map RSDT header&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
multiline_comment|/* remap in the entire table before processing */
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
id|sdt_pa
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
(brace
id|printk
c_func
(paren
id|KERN_WARNING
id|PREFIX
l_string|&quot;Unable to map RSDT&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|header
op_assign
op_amp
id|mapped_rsdt-&gt;header
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|header-&gt;signature
comma
l_string|&quot;RSDT&quot;
comma
l_int|4
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
id|PREFIX
l_string|&quot;RSDT signature incorrect&bslash;n&quot;
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
id|acpi_table_compute_checksum
c_func
(paren
id|header
comma
id|header-&gt;length
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
id|PREFIX
l_string|&quot;Invalid RSDT checksum&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|sdt_count
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
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|sdt_count
OG
id|ACPI_MAX_TABLES
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
id|PREFIX
l_string|&quot;Truncated %lu RSDT entries&bslash;n&quot;
comma
(paren
id|sdt_count
op_minus
id|ACPI_MAX_TABLES
)paren
)paren
suffix:semicolon
id|sdt_count
op_assign
id|ACPI_MAX_TABLES
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|sdt_count
suffix:semicolon
id|i
op_increment
)paren
id|sdt_entry
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
r_else
(brace
id|printk
c_func
(paren
id|KERN_WARNING
id|PREFIX
l_string|&quot;No System Description Table (RSDT/XSDT) specified in RSDP&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|acpi_table_print
c_func
(paren
id|header
comma
id|sdt_pa
)paren
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
id|sdt_count
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* map in just the header */
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
id|sdt_entry
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
multiline_comment|/* remap in the entire table before processing */
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
id|sdt_entry
(braket
id|i
)braket
dot
id|pa
comma
id|header-&gt;length
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
id|acpi_table_print
c_func
(paren
id|header
comma
id|sdt_entry
(braket
id|i
)braket
dot
id|pa
)paren
suffix:semicolon
r_if
c_cond
(paren
id|acpi_table_compute_checksum
c_func
(paren
id|header
comma
id|header-&gt;length
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;  &gt;&gt;&gt; ERROR: Invalid checksum&bslash;n&quot;
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|sdt_entry
(braket
id|i
)braket
dot
id|size
op_assign
id|header-&gt;length
suffix:semicolon
r_for
c_loop
(paren
id|id
op_assign
l_int|0
suffix:semicolon
id|id
OL
id|ACPI_TABLE_COUNT
suffix:semicolon
id|id
op_increment
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
id|header-&gt;signature
comma
id|acpi_table_signatures
(braket
id|id
)braket
comma
r_sizeof
(paren
id|header-&gt;signature
)paren
)paren
)paren
(brace
id|sdt_entry
(braket
id|i
)braket
dot
id|id
op_assign
id|id
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* &n;&t; * The DSDT is *not* in the RSDT (why not? no idea.) but we want&n;&t; * to print its info, because this is what people usually blacklist&n;&t; * against. Unfortunately, we don&squot;t know the phys_addr, so just&n;&t; * print 0. Maybe no one will notice.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|acpi_get_table_header_early
c_func
(paren
id|ACPI_DSDT
comma
op_amp
id|header
)paren
)paren
(brace
id|acpi_table_print
c_func
(paren
id|header
comma
l_int|0
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * acpi_table_init()&n; *&n; * find RSDP, find and checksum SDT/XSDT.&n; * checksum all tables, print SDT/XSDT&n; * &n; * result: sdt_entry[] is initialized&n; */
r_int
id|__init
DECL|function|acpi_table_init
id|acpi_table_init
(paren
r_void
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
r_int
id|result
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Locate and map the Root System Description Table (RSDP) */
id|rsdp_phys
op_assign
id|acpi_find_rsdp
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rsdp_phys
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PREFIX
l_string|&quot;Unable to locate RSDP&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|rsdp
op_assign
(paren
r_struct
id|acpi_table_rsdp
op_star
)paren
id|__va
c_func
(paren
id|rsdp_phys
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rsdp
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
id|PREFIX
l_string|&quot;Unable to map RSDP&bslash;n&quot;
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
id|KERN_DEBUG
id|PREFIX
l_string|&quot;RSDP (v%3.3d %6.6s                                ) @ 0x%p&bslash;n&quot;
comma
id|rsdp-&gt;revision
comma
id|rsdp-&gt;oem_id
comma
(paren
r_void
op_star
)paren
id|rsdp_phys
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rsdp-&gt;revision
OL
l_int|2
)paren
id|result
op_assign
id|acpi_table_compute_checksum
c_func
(paren
id|rsdp
comma
r_sizeof
(paren
r_struct
id|acpi_table_rsdp
)paren
)paren
suffix:semicolon
r_else
id|result
op_assign
id|acpi_table_compute_checksum
c_func
(paren
id|rsdp
comma
(paren
(paren
r_struct
id|acpi20_table_rsdp
op_star
)paren
id|rsdp
)paren
op_member_access_from_pointer
id|length
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;  &gt;&gt;&gt; ERROR: Invalid checksum&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
multiline_comment|/* Locate and map the System Description table (RSDT/XSDT) */
r_if
c_cond
(paren
id|acpi_table_get_sdt
c_func
(paren
id|rsdp
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
