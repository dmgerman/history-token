multiline_comment|/*&n; *  acpi.c - Architecture-Specific Low-Level ACPI Support&n; *&n; *  Copyright (C) 2001, 2002 Paul Diefenbaugh &lt;paul.s.diefenbaugh@intel.com&gt;&n; *  Copyright (C) 2001 Jun Nakajima &lt;jun.nakajima@intel.com&gt;&n; *  Copyright (C) 2001 Patrick Mochel &lt;mochel@osdl.org&gt;&n; *&n; * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; *&n; * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/acpi.h&gt;
macro_line|#include &lt;asm/mpspec.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/apic.h&gt;
macro_line|#include &lt;asm/apicdef.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/io_apic.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
DECL|macro|PREFIX
mdefine_line|#define PREFIX&t;&t;&t;&quot;ACPI: &quot;
r_extern
r_int
id|acpi_disabled
suffix:semicolon
multiline_comment|/* --------------------------------------------------------------------------&n;                              Boot-time Configuration&n;   -------------------------------------------------------------------------- */
DECL|variable|acpi_irq_model
r_enum
id|acpi_irq_model_id
id|acpi_irq_model
suffix:semicolon
macro_line|#ifdef CONFIG_ACPI_BOOT
multiline_comment|/*&n; * Temporarily use the virtual area starting from FIX_IO_APIC_BASE_END,&n; * to map the target physical address. The problem is that set_fixmap()&n; * provides a single page, and it is possible that the page is not&n; * sufficient.&n; * By using this area, we can map up to MAX_IO_APICS pages temporarily,&n; * i.e. until the next __va_range() call.&n; *&n; * Important Safety Note:  The fixed I/O APIC page numbers are *subtracted*&n; * from the fixed base.  That&squot;s why we start at FIX_IO_APIC_BASE_END and&n; * count idx down while incrementing the phys address.&n; */
DECL|function|__acpi_map_table
r_char
op_star
id|__acpi_map_table
c_func
(paren
r_int
r_int
id|phys
comma
r_int
r_int
id|size
)paren
(brace
r_int
r_int
id|base
comma
id|offset
comma
id|mapped_size
suffix:semicolon
r_int
id|idx
suffix:semicolon
r_if
c_cond
(paren
id|phys
op_plus
id|size
OL
l_int|8
op_star
l_int|1024
op_star
l_int|1024
)paren
r_return
id|__va
c_func
(paren
id|phys
)paren
suffix:semicolon
id|offset
op_assign
id|phys
op_amp
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
id|mapped_size
op_assign
id|PAGE_SIZE
op_minus
id|offset
suffix:semicolon
id|set_fixmap
c_func
(paren
id|FIX_IO_APIC_BASE_END
comma
id|phys
)paren
suffix:semicolon
id|base
op_assign
id|fix_to_virt
c_func
(paren
id|FIX_IO_APIC_BASE_END
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Most cases can be covered by the below.&n;&t; */
id|idx
op_assign
id|FIX_IO_APIC_BASE_END
suffix:semicolon
r_while
c_loop
(paren
id|mapped_size
OL
id|size
)paren
(brace
r_if
c_cond
(paren
op_decrement
id|idx
OL
id|FIX_IO_APIC_BASE_0
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* cannot handle this */
id|phys
op_add_assign
id|PAGE_SIZE
suffix:semicolon
id|set_fixmap
c_func
(paren
id|idx
comma
id|phys
)paren
suffix:semicolon
id|mapped_size
op_add_assign
id|PAGE_SIZE
suffix:semicolon
)brace
r_return
(paren
(paren
r_int
r_char
op_star
)paren
id|base
op_plus
id|offset
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_X86_LOCAL_APIC
DECL|variable|acpi_lapic
r_int
id|acpi_lapic
suffix:semicolon
DECL|variable|__initdata
r_static
id|u64
id|acpi_lapic_addr
id|__initdata
op_assign
id|APIC_DEFAULT_PHYS_BASE
suffix:semicolon
r_static
r_int
id|__init
DECL|function|acpi_parse_madt
id|acpi_parse_madt
(paren
r_int
r_int
id|phys_addr
comma
r_int
r_int
id|size
)paren
(brace
r_struct
id|acpi_table_madt
op_star
id|madt
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|phys_addr
op_logical_or
op_logical_neg
id|size
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|madt
op_assign
(paren
r_struct
id|acpi_table_madt
op_star
)paren
id|__acpi_map_table
c_func
(paren
id|phys_addr
comma
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
l_string|&quot;Unable to map MADT&bslash;n&quot;
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
id|madt-&gt;lapic_address
)paren
id|acpi_lapic_addr
op_assign
(paren
id|u64
)paren
id|madt-&gt;lapic_address
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
id|PREFIX
l_string|&quot;Local APIC address 0x%08x&bslash;n&quot;
comma
id|madt-&gt;lapic_address
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
id|__init
DECL|function|acpi_parse_lapic
id|acpi_parse_lapic
(paren
id|acpi_table_entry_header
op_star
id|header
)paren
(brace
r_struct
id|acpi_table_lapic
op_star
id|processor
op_assign
l_int|NULL
suffix:semicolon
id|processor
op_assign
(paren
r_struct
id|acpi_table_lapic
op_star
)paren
id|header
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|processor
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|acpi_table_print_madt_entry
c_func
(paren
id|header
)paren
suffix:semicolon
id|mp_register_lapic
(paren
id|processor-&gt;id
comma
multiline_comment|/* APIC ID */
id|processor-&gt;flags.enabled
)paren
suffix:semicolon
multiline_comment|/* Enabled? */
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
id|__init
DECL|function|acpi_parse_lapic_addr_ovr
id|acpi_parse_lapic_addr_ovr
(paren
id|acpi_table_entry_header
op_star
id|header
)paren
(brace
r_struct
id|acpi_table_lapic_addr_ovr
op_star
id|lapic_addr_ovr
op_assign
l_int|NULL
suffix:semicolon
id|lapic_addr_ovr
op_assign
(paren
r_struct
id|acpi_table_lapic_addr_ovr
op_star
)paren
id|header
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|lapic_addr_ovr
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|acpi_lapic_addr
op_assign
id|lapic_addr_ovr-&gt;address
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifndef CONFIG_ACPI_HT_ONLY
r_static
r_int
id|__init
DECL|function|acpi_parse_lapic_nmi
id|acpi_parse_lapic_nmi
(paren
id|acpi_table_entry_header
op_star
id|header
)paren
(brace
r_struct
id|acpi_table_lapic_nmi
op_star
id|lapic_nmi
op_assign
l_int|NULL
suffix:semicolon
id|lapic_nmi
op_assign
(paren
r_struct
id|acpi_table_lapic_nmi
op_star
)paren
id|header
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|lapic_nmi
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|acpi_table_print_madt_entry
c_func
(paren
id|header
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lapic_nmi-&gt;lint
op_ne
l_int|1
)paren
id|printk
c_func
(paren
id|KERN_WARNING
id|PREFIX
l_string|&quot;NMI not connected to LINT 1!&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif /*CONFIG_ACPI_HT_ONLY*/
macro_line|#endif /*CONFIG_X86_LOCAL_APIC*/
macro_line|#ifdef CONFIG_X86_IO_APIC
DECL|variable|acpi_ioapic
r_int
id|acpi_ioapic
suffix:semicolon
macro_line|#ifndef CONFIG_ACPI_HT_ONLY
r_static
r_int
id|__init
DECL|function|acpi_parse_ioapic
id|acpi_parse_ioapic
(paren
id|acpi_table_entry_header
op_star
id|header
)paren
(brace
r_struct
id|acpi_table_ioapic
op_star
id|ioapic
op_assign
l_int|NULL
suffix:semicolon
id|ioapic
op_assign
(paren
r_struct
id|acpi_table_ioapic
op_star
)paren
id|header
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ioapic
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|acpi_table_print_madt_entry
c_func
(paren
id|header
)paren
suffix:semicolon
id|mp_register_ioapic
(paren
id|ioapic-&gt;id
comma
id|ioapic-&gt;address
comma
id|ioapic-&gt;global_irq_base
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
id|__init
DECL|function|acpi_parse_int_src_ovr
id|acpi_parse_int_src_ovr
(paren
id|acpi_table_entry_header
op_star
id|header
)paren
(brace
r_struct
id|acpi_table_int_src_ovr
op_star
id|intsrc
op_assign
l_int|NULL
suffix:semicolon
id|intsrc
op_assign
(paren
r_struct
id|acpi_table_int_src_ovr
op_star
)paren
id|header
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|intsrc
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|acpi_table_print_madt_entry
c_func
(paren
id|header
)paren
suffix:semicolon
id|mp_override_legacy_irq
(paren
id|intsrc-&gt;bus_irq
comma
id|intsrc-&gt;flags.polarity
comma
id|intsrc-&gt;flags.trigger
comma
id|intsrc-&gt;global_irq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
id|__init
DECL|function|acpi_parse_nmi_src
id|acpi_parse_nmi_src
(paren
id|acpi_table_entry_header
op_star
id|header
)paren
(brace
r_struct
id|acpi_table_nmi_src
op_star
id|nmi_src
op_assign
l_int|NULL
suffix:semicolon
id|nmi_src
op_assign
(paren
r_struct
id|acpi_table_nmi_src
op_star
)paren
id|header
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nmi_src
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|acpi_table_print_madt_entry
c_func
(paren
id|header
)paren
suffix:semicolon
multiline_comment|/* TBD: Support nimsrc entries? */
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif /*!CONFIG_ACPI_HT_ONLY*/ 
macro_line|#endif /*CONFIG_X86_IO_APIC*/
r_static
r_int
r_int
id|__init
DECL|function|acpi_scan_rsdp
id|acpi_scan_rsdp
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|length
)paren
(brace
r_int
r_int
id|offset
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|sig_len
op_assign
r_sizeof
(paren
l_string|&quot;RSD PTR &quot;
)paren
op_minus
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * Scan all 16-byte boundaries of the physical memory region for the&n;&t; * RSDP signature.&n;&t; */
r_for
c_loop
(paren
id|offset
op_assign
l_int|0
suffix:semicolon
id|offset
OL
id|length
suffix:semicolon
id|offset
op_add_assign
l_int|16
)paren
(brace
r_if
c_cond
(paren
id|strncmp
c_func
(paren
(paren
r_char
op_star
)paren
(paren
id|start
op_plus
id|offset
)paren
comma
l_string|&quot;RSD PTR &quot;
comma
id|sig_len
)paren
)paren
r_continue
suffix:semicolon
r_return
(paren
id|start
op_plus
id|offset
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_int
r_int
id|__init
DECL|function|acpi_find_rsdp
id|acpi_find_rsdp
(paren
r_void
)paren
(brace
r_int
r_int
id|rsdp_phys
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * Scan memory looking for the RSDP signature. First search EBDA (low&n;&t; * memory) paragraphs and then search upper memory (E0000-FFFFF).&n;&t; */
id|rsdp_phys
op_assign
id|acpi_scan_rsdp
(paren
l_int|0
comma
l_int|0x400
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rsdp_phys
)paren
id|rsdp_phys
op_assign
id|acpi_scan_rsdp
(paren
l_int|0xE0000
comma
l_int|0xFFFFF
)paren
suffix:semicolon
r_return
id|rsdp_phys
suffix:semicolon
)brace
r_int
id|__init
DECL|function|acpi_boot_init
id|acpi_boot_init
(paren
r_char
op_star
id|cmdline
)paren
(brace
r_int
id|result
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * The default interrupt routing model is PIC (8259).  This gets&n;&t; * overriden if IOAPICs are enumerated (below).&n;&t; */
id|acpi_irq_model
op_assign
id|ACPI_IRQ_MODEL_PIC
suffix:semicolon
multiline_comment|/* &n;&t; * Initialize the ACPI boot-time table parser.&n;&t; */
id|result
op_assign
id|acpi_table_init
c_func
(paren
id|cmdline
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
r_return
id|result
suffix:semicolon
id|result
op_assign
id|acpi_blacklisted
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
(brace
id|acpi_disabled
op_assign
l_int|1
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
id|KERN_NOTICE
id|PREFIX
l_string|&quot;BIOS passes blacklist&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_X86_LOCAL_APIC
multiline_comment|/* &n;&t; * MADT&n;&t; * ----&n;&t; * Parse the Multiple APIC Description Table (MADT), if exists.&n;&t; * Note that this table provides platform SMP configuration &n;&t; * information -- the successor to MPS tables.&n;&t; */
id|result
op_assign
id|acpi_table_parse
c_func
(paren
id|ACPI_APIC
comma
id|acpi_parse_madt
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|result
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
id|PREFIX
l_string|&quot;MADT not present&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PREFIX
l_string|&quot;Error parsing MADT&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|result
OG
l_int|1
)paren
id|printk
c_func
(paren
id|KERN_WARNING
id|PREFIX
l_string|&quot;Multiple MADT tables exist&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* &n;&t; * Local APIC&n;&t; * ----------&n;&t; * Note that the LAPIC address is obtained from the MADT (32-bit value)&n;&t; * and (optionally) overriden by a LAPIC_ADDR_OVR entry (64-bit value).&n;&t; */
id|result
op_assign
id|acpi_table_parse_madt
c_func
(paren
id|ACPI_MADT_LAPIC_ADDR_OVR
comma
id|acpi_parse_lapic_addr_ovr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PREFIX
l_string|&quot;Error parsing LAPIC address override entry&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
id|mp_register_lapic_address
c_func
(paren
id|acpi_lapic_addr
)paren
suffix:semicolon
id|result
op_assign
id|acpi_table_parse_madt
c_func
(paren
id|ACPI_MADT_LAPIC
comma
id|acpi_parse_lapic
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|result
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PREFIX
l_string|&quot;No LAPIC entries present&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* TBD: Cleanup to allow fallback to MPS */
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PREFIX
l_string|&quot;Error parsing LAPIC entry&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* TBD: Cleanup to allow fallback to MPS */
r_return
id|result
suffix:semicolon
)brace
macro_line|#ifndef CONFIG_ACPI_HT_ONLY
id|result
op_assign
id|acpi_table_parse_madt
c_func
(paren
id|ACPI_MADT_LAPIC_NMI
comma
id|acpi_parse_lapic_nmi
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PREFIX
l_string|&quot;Error parsing LAPIC NMI entry&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* TBD: Cleanup to allow fallback to MPS */
r_return
id|result
suffix:semicolon
)brace
macro_line|#endif /*!CONFIG_ACPI_HT_ONLY*/
id|acpi_lapic
op_assign
l_int|1
suffix:semicolon
macro_line|#endif /*CONFIG_X86_LOCAL_APIC*/
macro_line|#ifdef CONFIG_X86_IO_APIC
macro_line|#ifndef CONFIG_ACPI_HT_ONLY
multiline_comment|/* &n;&t; * I/O APIC &n;&t; * --------&n;&t; */
id|result
op_assign
id|acpi_table_parse_madt
c_func
(paren
id|ACPI_MADT_IOAPIC
comma
id|acpi_parse_ioapic
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|result
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PREFIX
l_string|&quot;No IOAPIC entries present&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PREFIX
l_string|&quot;Error parsing IOAPIC entry&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/* Build a default routing table for legacy (ISA) interrupts. */
id|mp_config_acpi_legacy_irqs
c_func
(paren
)paren
suffix:semicolon
id|result
op_assign
id|acpi_table_parse_madt
c_func
(paren
id|ACPI_MADT_INT_SRC_OVR
comma
id|acpi_parse_int_src_ovr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PREFIX
l_string|&quot;Error parsing interrupt source overrides entry&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* TBD: Cleanup to allow fallback to MPS */
r_return
id|result
suffix:semicolon
)brace
id|result
op_assign
id|acpi_table_parse_madt
c_func
(paren
id|ACPI_MADT_NMI_SRC
comma
id|acpi_parse_nmi_src
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PREFIX
l_string|&quot;Error parsing NMI SRC entry&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* TBD: Cleanup to allow fallback to MPS */
r_return
id|result
suffix:semicolon
)brace
id|acpi_irq_model
op_assign
id|ACPI_IRQ_MODEL_IOAPIC
suffix:semicolon
id|acpi_ioapic
op_assign
l_int|1
suffix:semicolon
macro_line|#endif /*!CONFIG_ACPI_HT_ONLY*/
macro_line|#endif /*CONFIG_X86_IO_APIC*/
macro_line|#ifdef CONFIG_X86_LOCAL_APIC
r_if
c_cond
(paren
id|acpi_lapic
op_logical_and
id|acpi_ioapic
)paren
id|smp_found_config
op_assign
l_int|1
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif /*CONFIG_ACPI_BOOT*/
multiline_comment|/* --------------------------------------------------------------------------&n;                              Low-Level Sleep Support&n;   -------------------------------------------------------------------------- */
macro_line|#ifdef CONFIG_ACPI_SLEEP
DECL|macro|DEBUG
mdefine_line|#define DEBUG
macro_line|#ifdef DEBUG
macro_line|#include &lt;linux/serial.h&gt;
macro_line|#endif
multiline_comment|/* address in low memory of the wakeup routine. */
DECL|variable|acpi_wakeup_address
r_int
r_int
id|acpi_wakeup_address
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* new page directory that we will be using */
DECL|variable|pmd
r_static
id|pmd_t
op_star
id|pmd
suffix:semicolon
multiline_comment|/* saved page directory */
DECL|variable|saved_pmd
r_static
id|pmd_t
id|saved_pmd
suffix:semicolon
multiline_comment|/* page which we&squot;ll use for the new page directory */
DECL|variable|ptep
r_static
id|pte_t
op_star
id|ptep
suffix:semicolon
r_extern
r_int
r_int
id|FASTCALL
c_func
(paren
id|acpi_copy_wakeup_routine
c_func
(paren
r_int
r_int
)paren
)paren
suffix:semicolon
multiline_comment|/*&n; * acpi_create_identity_pmd&n; *&n; * Create a new, identity mapped pmd.&n; *&n; * Do this by creating new page directory, and marking all the pages as R/W&n; * Then set it as the new Page Middle Directory.&n; * And, of course, flush the TLB so it takes effect.&n; *&n; * We save the address of the old one, for later restoration.&n; */
DECL|function|acpi_create_identity_pmd
r_static
r_void
id|acpi_create_identity_pmd
(paren
r_void
)paren
(brace
id|pgd_t
op_star
id|pgd
suffix:semicolon
r_int
id|i
suffix:semicolon
id|ptep
op_assign
(paren
id|pte_t
op_star
)paren
id|__get_free_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
multiline_comment|/* fill page with low mapping */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|PTRS_PER_PTE
suffix:semicolon
id|i
op_increment
)paren
id|set_pte
c_func
(paren
id|ptep
op_plus
id|i
comma
id|pfn_pte
c_func
(paren
id|i
comma
id|PAGE_SHARED
)paren
)paren
suffix:semicolon
id|pgd
op_assign
id|pgd_offset
c_func
(paren
id|current-&gt;active_mm
comma
l_int|0
)paren
suffix:semicolon
id|pmd
op_assign
id|pmd_alloc
c_func
(paren
id|current-&gt;mm
comma
id|pgd
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* save the old pmd */
id|saved_pmd
op_assign
op_star
id|pmd
suffix:semicolon
multiline_comment|/* set the new one */
id|set_pmd
c_func
(paren
id|pmd
comma
id|__pmd
c_func
(paren
id|_PAGE_TABLE
op_plus
id|__pa
c_func
(paren
id|ptep
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* flush the TLB */
id|local_flush_tlb
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * acpi_restore_pmd&n; *&n; * Restore the old pmd saved by acpi_create_identity_pmd and&n; * free the page that said function alloc&squot;d&n; */
DECL|function|acpi_restore_pmd
r_static
r_void
id|acpi_restore_pmd
(paren
r_void
)paren
(brace
id|set_pmd
c_func
(paren
id|pmd
comma
id|saved_pmd
)paren
suffix:semicolon
id|local_flush_tlb
c_func
(paren
)paren
suffix:semicolon
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|ptep
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * acpi_save_state_mem - save kernel state&n; *&n; * Create an identity mapped page table and copy the wakeup routine to&n; * low memory.&n; */
DECL|function|acpi_save_state_mem
r_int
id|acpi_save_state_mem
(paren
r_void
)paren
(brace
id|acpi_create_identity_pmd
c_func
(paren
)paren
suffix:semicolon
id|acpi_copy_wakeup_routine
c_func
(paren
id|acpi_wakeup_address
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * acpi_save_state_disk - save kernel state to disk&n; *&n; */
DECL|function|acpi_save_state_disk
r_int
id|acpi_save_state_disk
(paren
r_void
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * acpi_restore_state&n; */
DECL|function|acpi_restore_state_mem
r_void
id|acpi_restore_state_mem
(paren
r_void
)paren
(brace
id|acpi_restore_pmd
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * acpi_reserve_bootmem - do _very_ early ACPI initialisation&n; *&n; * We allocate a page in low memory for the wakeup&n; * routine for when we come back from a sleep state. The&n; * runtime allocator allows specification of &lt;16M pages, but not&n; * &lt;1M pages.&n; */
DECL|function|acpi_reserve_bootmem
r_void
id|__init
id|acpi_reserve_bootmem
c_func
(paren
r_void
)paren
(brace
id|acpi_wakeup_address
op_assign
(paren
r_int
r_int
)paren
id|alloc_bootmem_low
c_func
(paren
id|PAGE_SIZE
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;ACPI: have wakeup address 0x%8.8lx&bslash;n&quot;
comma
id|acpi_wakeup_address
)paren
suffix:semicolon
)brace
macro_line|#endif /*CONFIG_ACPI_SLEEP*/
eof
