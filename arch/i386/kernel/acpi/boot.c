multiline_comment|/*&n; *  boot.c - Architecture-Specific Low-Level ACPI Boot Support&n; *&n; *  Copyright (C) 2001, 2002 Paul Diefenbaugh &lt;paul.s.diefenbaugh@intel.com&gt;&n; *  Copyright (C) 2001 Jun Nakajima &lt;jun.nakajima@intel.com&gt;&n; *&n; * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; *&n; * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/acpi.h&gt;
macro_line|#include &lt;linux/efi.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/io_apic.h&gt;
macro_line|#include &lt;asm/apic.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/mpspec.h&gt;
macro_line|#if defined (CONFIG_X86_LOCAL_APIC)
macro_line|#include &lt;mach_apic.h&gt;
macro_line|#include &lt;mach_mpparse.h&gt;
macro_line|#include &lt;asm/io_apic.h&gt;
macro_line|#endif
DECL|macro|PREFIX
mdefine_line|#define PREFIX&t;&t;&t;&quot;ACPI: &quot;
DECL|variable|__initdata
r_int
id|acpi_noirq
id|__initdata
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* skip ACPI IRQ initialization */
DECL|variable|__initdata
r_int
id|acpi_ht
id|__initdata
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* enable HT */
DECL|variable|acpi_lapic
r_int
id|acpi_lapic
suffix:semicolon
DECL|variable|acpi_ioapic
r_int
id|acpi_ioapic
suffix:semicolon
multiline_comment|/* --------------------------------------------------------------------------&n;                              Boot-time Configuration&n;   -------------------------------------------------------------------------- */
DECL|variable|acpi_irq_model
r_enum
id|acpi_irq_model_id
id|acpi_irq_model
suffix:semicolon
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
id|FIX_ACPI_END
comma
id|phys
)paren
suffix:semicolon
id|base
op_assign
id|fix_to_virt
c_func
(paren
id|FIX_ACPI_END
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Most cases can be covered by the below.&n;&t; */
id|idx
op_assign
id|FIX_ACPI_END
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
id|FIX_ACPI_BEGIN
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
id|acpi_madt_oem_check
c_func
(paren
id|madt-&gt;header.oem_id
comma
id|madt-&gt;header.oem_table_id
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
multiline_comment|/* no utility in registering a disabled processor */
r_if
c_cond
(paren
id|processor-&gt;flags.enabled
op_eq
l_int|0
)paren
r_return
l_int|0
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
macro_line|#endif /*CONFIG_X86_LOCAL_APIC*/
macro_line|#if defined(CONFIG_X86_IO_APIC) &amp;&amp; defined(CONFIG_ACPI_INTERPRETER)
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
macro_line|#endif /*CONFIG_X86_IO_APIC*/
macro_line|#ifdef&t;CONFIG_ACPI_BUS
multiline_comment|/*&n; * &quot;acpi_pic_sci=level&quot; (current default)&n; * programs the PIC-mode SCI to Level Trigger.&n; * (NO-OP if the BIOS set Level Trigger already)&n; *&n; * If a PIC-mode SCI is not recogznied or gives spurious IRQ7&squot;s&n; * it may require Edge Trigger -- use &quot;acpi_pic_sci=edge&quot;&n; * (NO-OP if the BIOS set Edge Trigger already)&n; *&n; * Port 0x4d0-4d1 are ECLR1 and ECLR2, the Edge/Level Control Registers&n; * for the 8259 PIC.  bit[n] = 1 means irq[n] is Level, otherwise Edge.&n; * ECLR1 is IRQ&squot;s 0-7 (IRQ 0, 1, 2 must be 0)&n; * ECLR2 is IRQ&squot;s 8-15 (IRQ 8, 13 must be 0)&n; */
DECL|variable|acpi_pic_sci_trigger
r_static
r_int
id|__initdata
id|acpi_pic_sci_trigger
suffix:semicolon
multiline_comment|/* 0: level, 1: edge */
r_void
id|__init
DECL|function|acpi_pic_sci_set_trigger
id|acpi_pic_sci_set_trigger
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_char
id|mask
op_assign
l_int|1
op_lshift
(paren
id|irq
op_amp
l_int|7
)paren
suffix:semicolon
r_int
r_int
id|port
op_assign
l_int|0x4d0
op_plus
(paren
id|irq
op_rshift
l_int|3
)paren
suffix:semicolon
r_int
r_char
id|val
op_assign
id|inb
c_func
(paren
id|port
)paren
suffix:semicolon
id|printk
c_func
(paren
id|PREFIX
l_string|&quot;IRQ%d SCI:&quot;
comma
id|irq
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|val
op_amp
id|mask
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; Edge&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|acpi_pic_sci_trigger
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; set to Level&quot;
)paren
suffix:semicolon
id|outb
c_func
(paren
id|val
op_or
id|mask
comma
id|port
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot; Level&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|acpi_pic_sci_trigger
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; set to Edge&quot;
)paren
suffix:semicolon
id|outb
c_func
(paren
id|val
op_or
id|mask
comma
id|port
)paren
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
l_string|&quot; Trigger.&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_int
id|__init
DECL|function|acpi_pic_sci_setup
id|acpi_pic_sci_setup
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
l_string|&quot;level&quot;
comma
l_int|5
)paren
op_eq
l_int|0
)paren
id|acpi_pic_sci_trigger
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* force level trigger */
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|str
comma
l_string|&quot;edge&quot;
comma
l_int|4
)paren
op_eq
l_int|0
)paren
id|acpi_pic_sci_trigger
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* force edge trigger */
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
l_string|&quot;acpi_pic_sci=&quot;
comma
id|acpi_pic_sci_setup
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_ACPI_BUS */
macro_line|#ifdef CONFIG_X86_IO_APIC
DECL|function|acpi_irq_to_vector
r_int
id|acpi_irq_to_vector
c_func
(paren
id|u32
id|irq
)paren
(brace
r_if
c_cond
(paren
id|use_pci_vector
c_func
(paren
)paren
op_logical_and
op_logical_neg
id|platform_legacy_irq
c_func
(paren
id|irq
)paren
)paren
id|irq
op_assign
id|IO_APIC_VECTOR
c_func
(paren
id|irq
)paren
suffix:semicolon
r_return
id|irq
suffix:semicolon
)brace
macro_line|#endif
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
macro_line|#ifdef CONFIG_HPET_TIMER
r_extern
r_int
r_int
id|hpet_address
suffix:semicolon
DECL|function|acpi_parse_hpet
r_static
r_int
id|__init
id|acpi_parse_hpet
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
r_struct
id|acpi_table_hpet
op_star
id|hpet_tbl
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|phys
op_logical_or
op_logical_neg
id|size
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|hpet_tbl
op_assign
(paren
r_struct
id|acpi_table_hpet
op_star
)paren
id|__acpi_map_table
c_func
(paren
id|phys
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hpet_tbl
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
id|PREFIX
l_string|&quot;Unable to map HPET&bslash;n&quot;
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
id|hpet_tbl-&gt;addr.space_id
op_ne
id|ACPI_SPACE_MEM
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
id|PREFIX
l_string|&quot;HPET timers must be located in &quot;
l_string|&quot;memory.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|hpet_address
op_assign
id|hpet_tbl-&gt;addr.addrl
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
id|PREFIX
l_string|&quot;HPET id: %#x base: %#lx&bslash;n&quot;
comma
id|hpet_tbl-&gt;id
comma
id|hpet_address
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
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
r_if
c_cond
(paren
id|efi_enabled
)paren
(brace
r_if
c_cond
(paren
id|efi.acpi20
)paren
r_return
id|__pa
c_func
(paren
id|efi.acpi20
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|efi.acpi
)paren
r_return
id|__pa
c_func
(paren
id|efi.acpi
)paren
suffix:semicolon
)brace
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
multiline_comment|/*&n; * acpi_boot_init()&n; *  called from setup_arch(), always.&n; *&t;1. maps ACPI tables for later use&n; *&t;2. enumerates lapics&n; *&t;3. enumerates io-apics&n; *&n; * side effects:&n; *&t;acpi_lapic = 1 if LAPIC found&n; *&t;acpi_ioapic = 1 if IOAPIC found&n; *&t;if (acpi_lapic &amp;&amp; acpi_ioapic) smp_found_config = 1;&n; *&t;if acpi_blacklisted() acpi_disabled = 1;&n; *&t;acpi_irq_model=...&n; *&t;...&n; *&n; * return value: (currently ignored)&n; *&t;0: success&n; *&t;!0: failure&n; */
r_int
id|__init
DECL|function|acpi_boot_init
id|acpi_boot_init
(paren
r_void
)paren
(brace
r_int
id|result
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|acpi_disabled
op_logical_and
op_logical_neg
id|acpi_ht
)paren
r_return
l_int|1
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
id|printk
c_func
(paren
id|KERN_WARNING
id|PREFIX
l_string|&quot;BIOS listed in blacklist, disabling ACPI support&bslash;n&quot;
)paren
suffix:semicolon
id|acpi_disabled
op_assign
l_int|1
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
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
comma
l_int|0
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
comma
id|MAX_APICS
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
id|result
op_assign
id|acpi_table_parse_madt
c_func
(paren
id|ACPI_MADT_LAPIC_NMI
comma
id|acpi_parse_lapic_nmi
comma
l_int|0
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
id|acpi_lapic
op_assign
l_int|1
suffix:semicolon
macro_line|#endif /*CONFIG_X86_LOCAL_APIC*/
macro_line|#if defined(CONFIG_X86_IO_APIC) &amp;&amp; defined(CONFIG_ACPI_INTERPRETER)
multiline_comment|/* &n;&t; * I/O APIC &n;&t; * --------&n;&t; */
multiline_comment|/*&n;&t; * ACPI interpreter is required to complete interrupt setup,&n;&t; * so if it is off, don&squot;t enumerate the io-apics with ACPI.&n;&t; * If MPS is present, it will handle them,&n;&t; * otherwise the system will stay in PIC mode&n;&t; */
r_if
c_cond
(paren
id|acpi_disabled
op_logical_or
id|acpi_noirq
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; &t; * if &quot;noapic&quot; boot option, don&squot;t look for IO-APICs&n;&t; */
r_if
c_cond
(paren
id|ioapic_setup_disabled
c_func
(paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
id|PREFIX
l_string|&quot;Skipping IOAPIC probe &quot;
l_string|&quot;due to &squot;noapic&squot; option.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|result
op_assign
id|acpi_table_parse_madt
c_func
(paren
id|ACPI_MADT_IOAPIC
comma
id|acpi_parse_ioapic
comma
id|MAX_IO_APICS
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
comma
id|NR_IRQ_VECTORS
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
comma
id|NR_IRQ_VECTORS
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
id|acpi_irq_balance_set
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
id|acpi_ioapic
op_assign
l_int|1
suffix:semicolon
macro_line|#endif /* CONFIG_X86_IO_APIC &amp;&amp; CONFIG_ACPI_INTERPRETER */
macro_line|#ifdef CONFIG_X86_LOCAL_APIC
r_if
c_cond
(paren
id|acpi_lapic
op_logical_and
id|acpi_ioapic
)paren
(brace
id|smp_found_config
op_assign
l_int|1
suffix:semicolon
id|clustered_apic_check
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_HPET_TIMER
id|acpi_table_parse
c_func
(paren
id|ACPI_HPET
comma
id|acpi_parse_hpet
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
eof
