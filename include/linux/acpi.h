multiline_comment|/*&n; * acpi.h - ACPI Interface&n; *&n; * Copyright (C) 2001 Paul Diefenbaugh &lt;paul.s.diefenbaugh@intel.com&gt;&n; *&n; * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; *&n; * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~&n; */
macro_line|#ifndef _LINUX_ACPI_H
DECL|macro|_LINUX_ACPI_H
mdefine_line|#define _LINUX_ACPI_H
macro_line|#ifndef _LINUX
DECL|macro|_LINUX
mdefine_line|#define _LINUX
macro_line|#endif
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;acpi/acpi.h&gt;
macro_line|#include &lt;acpi/acpi_bus.h&gt;
macro_line|#include &lt;asm/acpi.h&gt;
macro_line|#ifdef CONFIG_ACPI
DECL|enum|acpi_irq_model_id
r_enum
id|acpi_irq_model_id
(brace
DECL|enumerator|ACPI_IRQ_MODEL_PIC
id|ACPI_IRQ_MODEL_PIC
op_assign
l_int|0
comma
DECL|enumerator|ACPI_IRQ_MODEL_IOAPIC
id|ACPI_IRQ_MODEL_IOAPIC
comma
DECL|enumerator|ACPI_IRQ_MODEL_IOSAPIC
id|ACPI_IRQ_MODEL_IOSAPIC
comma
DECL|enumerator|ACPI_IRQ_MODEL_COUNT
id|ACPI_IRQ_MODEL_COUNT
)brace
suffix:semicolon
r_extern
r_enum
id|acpi_irq_model_id
id|acpi_irq_model
suffix:semicolon
multiline_comment|/* Root System Description Pointer (RSDP) */
DECL|struct|acpi_table_rsdp
r_struct
id|acpi_table_rsdp
(brace
DECL|member|signature
r_char
id|signature
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|checksum
id|u8
id|checksum
suffix:semicolon
DECL|member|oem_id
r_char
id|oem_id
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|revision
id|u8
id|revision
suffix:semicolon
DECL|member|rsdt_address
id|u32
id|rsdt_address
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|acpi20_table_rsdp
r_struct
id|acpi20_table_rsdp
(brace
DECL|member|signature
r_char
id|signature
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|checksum
id|u8
id|checksum
suffix:semicolon
DECL|member|oem_id
r_char
id|oem_id
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|revision
id|u8
id|revision
suffix:semicolon
DECL|member|rsdt_address
id|u32
id|rsdt_address
suffix:semicolon
DECL|member|length
id|u32
id|length
suffix:semicolon
DECL|member|xsdt_address
id|u64
id|xsdt_address
suffix:semicolon
DECL|member|ext_checksum
id|u8
id|ext_checksum
suffix:semicolon
DECL|member|reserved
id|u8
id|reserved
(braket
l_int|3
)braket
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|type
id|u8
id|type
suffix:semicolon
DECL|member|length
id|u8
id|length
suffix:semicolon
DECL|typedef|acpi_table_entry_header
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|acpi_table_entry_header
suffix:semicolon
multiline_comment|/* Root System Description Table (RSDT) */
DECL|struct|acpi_table_rsdt
r_struct
id|acpi_table_rsdt
(brace
DECL|member|header
r_struct
id|acpi_table_header
id|header
suffix:semicolon
DECL|member|entry
id|u32
id|entry
(braket
l_int|1
)braket
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* Extended System Description Table (XSDT) */
DECL|struct|acpi_table_xsdt
r_struct
id|acpi_table_xsdt
(brace
DECL|member|header
r_struct
id|acpi_table_header
id|header
suffix:semicolon
DECL|member|entry
id|u64
id|entry
(braket
l_int|1
)braket
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* Fixed ACPI Description Table (FADT) */
DECL|struct|acpi_table_fadt
r_struct
id|acpi_table_fadt
(brace
DECL|member|header
r_struct
id|acpi_table_header
id|header
suffix:semicolon
DECL|member|facs_addr
id|u32
id|facs_addr
suffix:semicolon
DECL|member|dsdt_addr
id|u32
id|dsdt_addr
suffix:semicolon
multiline_comment|/* ... */
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* Multiple APIC Description Table (MADT) */
DECL|struct|acpi_table_madt
r_struct
id|acpi_table_madt
(brace
DECL|member|header
r_struct
id|acpi_table_header
id|header
suffix:semicolon
DECL|member|lapic_address
id|u32
id|lapic_address
suffix:semicolon
r_struct
(brace
DECL|member|pcat_compat
id|u32
id|pcat_compat
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved
id|u32
id|reserved
suffix:colon
l_int|31
suffix:semicolon
DECL|member|flags
)brace
id|flags
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|enum|acpi_madt_entry_id
r_enum
id|acpi_madt_entry_id
(brace
DECL|enumerator|ACPI_MADT_LAPIC
id|ACPI_MADT_LAPIC
op_assign
l_int|0
comma
DECL|enumerator|ACPI_MADT_IOAPIC
id|ACPI_MADT_IOAPIC
comma
DECL|enumerator|ACPI_MADT_INT_SRC_OVR
id|ACPI_MADT_INT_SRC_OVR
comma
DECL|enumerator|ACPI_MADT_NMI_SRC
id|ACPI_MADT_NMI_SRC
comma
DECL|enumerator|ACPI_MADT_LAPIC_NMI
id|ACPI_MADT_LAPIC_NMI
comma
DECL|enumerator|ACPI_MADT_LAPIC_ADDR_OVR
id|ACPI_MADT_LAPIC_ADDR_OVR
comma
DECL|enumerator|ACPI_MADT_IOSAPIC
id|ACPI_MADT_IOSAPIC
comma
DECL|enumerator|ACPI_MADT_LSAPIC
id|ACPI_MADT_LSAPIC
comma
DECL|enumerator|ACPI_MADT_PLAT_INT_SRC
id|ACPI_MADT_PLAT_INT_SRC
comma
DECL|enumerator|ACPI_MADT_ENTRY_COUNT
id|ACPI_MADT_ENTRY_COUNT
)brace
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|polarity
id|u16
id|polarity
suffix:colon
l_int|2
suffix:semicolon
DECL|member|trigger
id|u16
id|trigger
suffix:colon
l_int|2
suffix:semicolon
DECL|member|reserved
id|u16
id|reserved
suffix:colon
l_int|12
suffix:semicolon
DECL|typedef|acpi_interrupt_flags
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|acpi_interrupt_flags
suffix:semicolon
DECL|struct|acpi_table_lapic
r_struct
id|acpi_table_lapic
(brace
DECL|member|header
id|acpi_table_entry_header
id|header
suffix:semicolon
DECL|member|acpi_id
id|u8
id|acpi_id
suffix:semicolon
DECL|member|id
id|u8
id|id
suffix:semicolon
r_struct
(brace
DECL|member|enabled
id|u32
id|enabled
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved
id|u32
id|reserved
suffix:colon
l_int|31
suffix:semicolon
DECL|member|flags
)brace
id|flags
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|acpi_table_ioapic
r_struct
id|acpi_table_ioapic
(brace
DECL|member|header
id|acpi_table_entry_header
id|header
suffix:semicolon
DECL|member|id
id|u8
id|id
suffix:semicolon
DECL|member|reserved
id|u8
id|reserved
suffix:semicolon
DECL|member|address
id|u32
id|address
suffix:semicolon
DECL|member|global_irq_base
id|u32
id|global_irq_base
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|acpi_table_int_src_ovr
r_struct
id|acpi_table_int_src_ovr
(brace
DECL|member|header
id|acpi_table_entry_header
id|header
suffix:semicolon
DECL|member|bus
id|u8
id|bus
suffix:semicolon
DECL|member|bus_irq
id|u8
id|bus_irq
suffix:semicolon
DECL|member|global_irq
id|u32
id|global_irq
suffix:semicolon
DECL|member|flags
id|acpi_interrupt_flags
id|flags
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|acpi_table_nmi_src
r_struct
id|acpi_table_nmi_src
(brace
DECL|member|header
id|acpi_table_entry_header
id|header
suffix:semicolon
DECL|member|flags
id|acpi_interrupt_flags
id|flags
suffix:semicolon
DECL|member|global_irq
id|u32
id|global_irq
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|acpi_table_lapic_nmi
r_struct
id|acpi_table_lapic_nmi
(brace
DECL|member|header
id|acpi_table_entry_header
id|header
suffix:semicolon
DECL|member|acpi_id
id|u8
id|acpi_id
suffix:semicolon
DECL|member|flags
id|acpi_interrupt_flags
id|flags
suffix:semicolon
DECL|member|lint
id|u8
id|lint
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|acpi_table_lapic_addr_ovr
r_struct
id|acpi_table_lapic_addr_ovr
(brace
DECL|member|header
id|acpi_table_entry_header
id|header
suffix:semicolon
DECL|member|reserved
id|u8
id|reserved
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|address
id|u64
id|address
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|acpi_table_iosapic
r_struct
id|acpi_table_iosapic
(brace
DECL|member|header
id|acpi_table_entry_header
id|header
suffix:semicolon
DECL|member|id
id|u8
id|id
suffix:semicolon
DECL|member|reserved
id|u8
id|reserved
suffix:semicolon
DECL|member|global_irq_base
id|u32
id|global_irq_base
suffix:semicolon
DECL|member|address
id|u64
id|address
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|acpi_table_lsapic
r_struct
id|acpi_table_lsapic
(brace
DECL|member|header
id|acpi_table_entry_header
id|header
suffix:semicolon
DECL|member|acpi_id
id|u8
id|acpi_id
suffix:semicolon
DECL|member|id
id|u8
id|id
suffix:semicolon
DECL|member|eid
id|u8
id|eid
suffix:semicolon
DECL|member|reserved
id|u8
id|reserved
(braket
l_int|3
)braket
suffix:semicolon
r_struct
(brace
DECL|member|enabled
id|u32
id|enabled
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved
id|u32
id|reserved
suffix:colon
l_int|31
suffix:semicolon
DECL|member|flags
)brace
id|flags
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|acpi_table_plat_int_src
r_struct
id|acpi_table_plat_int_src
(brace
DECL|member|header
id|acpi_table_entry_header
id|header
suffix:semicolon
DECL|member|flags
id|acpi_interrupt_flags
id|flags
suffix:semicolon
DECL|member|type
id|u8
id|type
suffix:semicolon
multiline_comment|/* See acpi_interrupt_type */
DECL|member|id
id|u8
id|id
suffix:semicolon
DECL|member|eid
id|u8
id|eid
suffix:semicolon
DECL|member|iosapic_vector
id|u8
id|iosapic_vector
suffix:semicolon
DECL|member|global_irq
id|u32
id|global_irq
suffix:semicolon
DECL|member|reserved
id|u32
id|reserved
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|enum|acpi_interrupt_id
r_enum
id|acpi_interrupt_id
(brace
DECL|enumerator|ACPI_INTERRUPT_PMI
id|ACPI_INTERRUPT_PMI
op_assign
l_int|1
comma
DECL|enumerator|ACPI_INTERRUPT_INIT
id|ACPI_INTERRUPT_INIT
comma
DECL|enumerator|ACPI_INTERRUPT_CPEI
id|ACPI_INTERRUPT_CPEI
comma
DECL|enumerator|ACPI_INTERRUPT_COUNT
id|ACPI_INTERRUPT_COUNT
)brace
suffix:semicolon
DECL|macro|ACPI_SPACE_MEM
mdefine_line|#define&t;ACPI_SPACE_MEM&t;&t;0
DECL|struct|acpi_gen_regaddr
r_struct
id|acpi_gen_regaddr
(brace
DECL|member|space_id
id|u8
id|space_id
suffix:semicolon
DECL|member|bit_width
id|u8
id|bit_width
suffix:semicolon
DECL|member|bit_offset
id|u8
id|bit_offset
suffix:semicolon
DECL|member|resv
id|u8
id|resv
suffix:semicolon
DECL|member|addrl
id|u32
id|addrl
suffix:semicolon
DECL|member|addrh
id|u32
id|addrh
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|acpi_table_hpet
r_struct
id|acpi_table_hpet
(brace
DECL|member|header
r_struct
id|acpi_table_header
id|header
suffix:semicolon
DECL|member|id
id|u32
id|id
suffix:semicolon
DECL|member|addr
r_struct
id|acpi_gen_regaddr
id|addr
suffix:semicolon
DECL|member|number
id|u8
id|number
suffix:semicolon
DECL|member|min_tick
id|u16
id|min_tick
suffix:semicolon
DECL|member|page_protect
id|u8
id|page_protect
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/*&n; * System Resource Affinity Table (SRAT)&n; *   see http://www.microsoft.com/hwdev/design/srat.htm&n; */
DECL|struct|acpi_table_srat
r_struct
id|acpi_table_srat
(brace
DECL|member|header
r_struct
id|acpi_table_header
id|header
suffix:semicolon
DECL|member|table_revision
id|u32
id|table_revision
suffix:semicolon
DECL|member|reserved
id|u64
id|reserved
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|enum|acpi_srat_entry_id
r_enum
id|acpi_srat_entry_id
(brace
DECL|enumerator|ACPI_SRAT_PROCESSOR_AFFINITY
id|ACPI_SRAT_PROCESSOR_AFFINITY
op_assign
l_int|0
comma
DECL|enumerator|ACPI_SRAT_MEMORY_AFFINITY
id|ACPI_SRAT_MEMORY_AFFINITY
comma
DECL|enumerator|ACPI_SRAT_ENTRY_COUNT
id|ACPI_SRAT_ENTRY_COUNT
)brace
suffix:semicolon
DECL|struct|acpi_table_processor_affinity
r_struct
id|acpi_table_processor_affinity
(brace
DECL|member|header
id|acpi_table_entry_header
id|header
suffix:semicolon
DECL|member|proximity_domain
id|u8
id|proximity_domain
suffix:semicolon
DECL|member|apic_id
id|u8
id|apic_id
suffix:semicolon
r_struct
(brace
DECL|member|enabled
id|u32
id|enabled
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved
id|u32
id|reserved
suffix:colon
l_int|31
suffix:semicolon
DECL|member|flags
)brace
id|flags
suffix:semicolon
DECL|member|lsapic_eid
id|u8
id|lsapic_eid
suffix:semicolon
DECL|member|reserved
id|u8
id|reserved
(braket
l_int|7
)braket
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|acpi_table_memory_affinity
r_struct
id|acpi_table_memory_affinity
(brace
DECL|member|header
id|acpi_table_entry_header
id|header
suffix:semicolon
DECL|member|proximity_domain
id|u8
id|proximity_domain
suffix:semicolon
DECL|member|reserved1
id|u8
id|reserved1
(braket
l_int|5
)braket
suffix:semicolon
DECL|member|base_addr_lo
id|u32
id|base_addr_lo
suffix:semicolon
DECL|member|base_addr_hi
id|u32
id|base_addr_hi
suffix:semicolon
DECL|member|length_lo
id|u32
id|length_lo
suffix:semicolon
DECL|member|length_hi
id|u32
id|length_hi
suffix:semicolon
DECL|member|memory_type
id|u32
id|memory_type
suffix:semicolon
multiline_comment|/* See acpi_address_range_id */
r_struct
(brace
DECL|member|enabled
id|u32
id|enabled
suffix:colon
l_int|1
suffix:semicolon
DECL|member|hot_pluggable
id|u32
id|hot_pluggable
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved
id|u32
id|reserved
suffix:colon
l_int|30
suffix:semicolon
DECL|member|flags
)brace
id|flags
suffix:semicolon
DECL|member|reserved2
id|u64
id|reserved2
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|enum|acpi_address_range_id
r_enum
id|acpi_address_range_id
(brace
DECL|enumerator|ACPI_ADDRESS_RANGE_MEMORY
id|ACPI_ADDRESS_RANGE_MEMORY
op_assign
l_int|1
comma
DECL|enumerator|ACPI_ADDRESS_RANGE_RESERVED
id|ACPI_ADDRESS_RANGE_RESERVED
op_assign
l_int|2
comma
DECL|enumerator|ACPI_ADDRESS_RANGE_ACPI
id|ACPI_ADDRESS_RANGE_ACPI
op_assign
l_int|3
comma
DECL|enumerator|ACPI_ADDRESS_RANGE_NVS
id|ACPI_ADDRESS_RANGE_NVS
op_assign
l_int|4
comma
DECL|enumerator|ACPI_ADDRESS_RANGE_COUNT
id|ACPI_ADDRESS_RANGE_COUNT
)brace
suffix:semicolon
multiline_comment|/*&n; * System Locality Information Table (SLIT)&n; *   see http://devresource.hp.com/devresource/docs/techpapers/ia64/slit.pdf&n; */
DECL|struct|acpi_table_slit
r_struct
id|acpi_table_slit
(brace
DECL|member|header
r_struct
id|acpi_table_header
id|header
suffix:semicolon
DECL|member|localities
id|u64
id|localities
suffix:semicolon
DECL|member|entry
id|u8
id|entry
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* real size = localities^2 */
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* Smart Battery Description Table (SBST) */
DECL|struct|acpi_table_sbst
r_struct
id|acpi_table_sbst
(brace
DECL|member|header
r_struct
id|acpi_table_header
id|header
suffix:semicolon
DECL|member|warning
id|u32
id|warning
suffix:semicolon
multiline_comment|/* Warn user */
DECL|member|low
id|u32
id|low
suffix:semicolon
multiline_comment|/* Critical sleep */
DECL|member|critical
id|u32
id|critical
suffix:semicolon
multiline_comment|/* Critical shutdown */
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* Embedded Controller Boot Resources Table (ECDT) */
DECL|struct|acpi_table_ecdt
r_struct
id|acpi_table_ecdt
(brace
DECL|member|header
r_struct
id|acpi_table_header
id|header
suffix:semicolon
DECL|member|ec_control
r_struct
id|acpi_generic_address
id|ec_control
suffix:semicolon
DECL|member|ec_data
r_struct
id|acpi_generic_address
id|ec_data
suffix:semicolon
DECL|member|uid
id|u32
id|uid
suffix:semicolon
DECL|member|gpe_bit
id|u8
id|gpe_bit
suffix:semicolon
DECL|member|ec_id
r_char
id|ec_id
(braket
l_int|0
)braket
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* Table Handlers */
DECL|enum|acpi_table_id
r_enum
id|acpi_table_id
(brace
DECL|enumerator|ACPI_TABLE_UNKNOWN
id|ACPI_TABLE_UNKNOWN
op_assign
l_int|0
comma
DECL|enumerator|ACPI_APIC
id|ACPI_APIC
comma
DECL|enumerator|ACPI_BOOT
id|ACPI_BOOT
comma
DECL|enumerator|ACPI_DBGP
id|ACPI_DBGP
comma
DECL|enumerator|ACPI_DSDT
id|ACPI_DSDT
comma
DECL|enumerator|ACPI_ECDT
id|ACPI_ECDT
comma
DECL|enumerator|ACPI_ETDT
id|ACPI_ETDT
comma
DECL|enumerator|ACPI_FADT
id|ACPI_FADT
comma
DECL|enumerator|ACPI_FACS
id|ACPI_FACS
comma
DECL|enumerator|ACPI_OEMX
id|ACPI_OEMX
comma
DECL|enumerator|ACPI_PSDT
id|ACPI_PSDT
comma
DECL|enumerator|ACPI_SBST
id|ACPI_SBST
comma
DECL|enumerator|ACPI_SLIT
id|ACPI_SLIT
comma
DECL|enumerator|ACPI_SPCR
id|ACPI_SPCR
comma
DECL|enumerator|ACPI_SRAT
id|ACPI_SRAT
comma
DECL|enumerator|ACPI_SSDT
id|ACPI_SSDT
comma
DECL|enumerator|ACPI_SPMI
id|ACPI_SPMI
comma
DECL|enumerator|ACPI_HPET
id|ACPI_HPET
comma
DECL|enumerator|ACPI_TABLE_COUNT
id|ACPI_TABLE_COUNT
)brace
suffix:semicolon
DECL|typedef|acpi_table_handler
r_typedef
r_int
(paren
op_star
id|acpi_table_handler
)paren
(paren
r_int
r_int
id|phys_addr
comma
r_int
r_int
id|size
)paren
suffix:semicolon
r_extern
id|acpi_table_handler
id|acpi_table_ops
(braket
id|ACPI_TABLE_COUNT
)braket
suffix:semicolon
DECL|typedef|acpi_madt_entry_handler
r_typedef
r_int
(paren
op_star
id|acpi_madt_entry_handler
)paren
(paren
id|acpi_table_entry_header
op_star
id|header
)paren
suffix:semicolon
r_char
op_star
id|__acpi_map_table
(paren
r_int
r_int
id|phys_addr
comma
r_int
r_int
id|size
)paren
suffix:semicolon
r_int
r_int
id|acpi_find_rsdp
(paren
r_void
)paren
suffix:semicolon
r_int
id|acpi_boot_init
(paren
r_void
)paren
suffix:semicolon
r_int
id|acpi_numa_init
(paren
r_void
)paren
suffix:semicolon
r_int
id|acpi_table_init
(paren
r_void
)paren
suffix:semicolon
r_int
id|acpi_table_parse
(paren
r_enum
id|acpi_table_id
id|id
comma
id|acpi_table_handler
id|handler
)paren
suffix:semicolon
r_int
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
suffix:semicolon
r_int
id|acpi_table_parse_madt
(paren
r_enum
id|acpi_madt_entry_id
id|id
comma
id|acpi_madt_entry_handler
id|handler
)paren
suffix:semicolon
r_int
id|acpi_table_parse_srat
(paren
r_enum
id|acpi_srat_entry_id
id|id
comma
id|acpi_madt_entry_handler
id|handler
)paren
suffix:semicolon
r_void
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
suffix:semicolon
r_void
id|acpi_table_print_madt_entry
(paren
id|acpi_table_entry_header
op_star
id|madt
)paren
suffix:semicolon
r_void
id|acpi_table_print_srat_entry
(paren
id|acpi_table_entry_header
op_star
id|srat
)paren
suffix:semicolon
multiline_comment|/* the following four functions are architecture-dependent */
r_void
id|acpi_numa_slit_init
(paren
r_struct
id|acpi_table_slit
op_star
id|slit
)paren
suffix:semicolon
r_void
id|acpi_numa_processor_affinity_init
(paren
r_struct
id|acpi_table_processor_affinity
op_star
id|pa
)paren
suffix:semicolon
r_void
id|acpi_numa_memory_affinity_init
(paren
r_struct
id|acpi_table_memory_affinity
op_star
id|ma
)paren
suffix:semicolon
r_void
id|acpi_numa_arch_fixup
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|acpi_mp_config
suffix:semicolon
macro_line|#else
DECL|macro|acpi_mp_config
mdefine_line|#define acpi_mp_config&t;0
macro_line|#endif
macro_line|#ifdef CONFIG_ACPI_PCI
DECL|struct|acpi_prt_entry
r_struct
id|acpi_prt_entry
(brace
DECL|member|node
r_struct
id|list_head
id|node
suffix:semicolon
DECL|member|id
r_struct
id|acpi_pci_id
id|id
suffix:semicolon
DECL|member|pin
id|u8
id|pin
suffix:semicolon
r_struct
(brace
DECL|member|handle
id|acpi_handle
id|handle
suffix:semicolon
DECL|member|index
id|u32
id|index
suffix:semicolon
DECL|member|link
)brace
id|link
suffix:semicolon
DECL|member|irq
id|u32
id|irq
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|acpi_prt_list
r_struct
id|acpi_prt_list
(brace
DECL|member|count
r_int
id|count
suffix:semicolon
DECL|member|entries
r_struct
id|list_head
id|entries
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|acpi_prt_list
id|acpi_prt
suffix:semicolon
r_struct
id|pci_dev
suffix:semicolon
r_int
id|acpi_pci_irq_enable
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
suffix:semicolon
r_int
id|acpi_pci_irq_init
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /*CONFIG_ACPI_PCI*/
macro_line|#ifdef CONFIG_ACPI_EC
r_int
id|ec_read
c_func
(paren
id|u8
id|addr
comma
id|u8
op_star
id|val
)paren
suffix:semicolon
r_int
id|ec_write
c_func
(paren
id|u8
id|addr
comma
id|u8
id|val
)paren
suffix:semicolon
macro_line|#endif /*CONFIG_ACPI_EC*/
macro_line|#ifdef CONFIG_ACPI
r_int
id|acpi_blacklisted
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /*CONFIG_ACPI*/
macro_line|#endif /*_LINUX_ACPI_H*/
eof
