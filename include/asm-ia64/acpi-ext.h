macro_line|#ifndef _ASM_IA64_ACPI_EXT_H
DECL|macro|_ASM_IA64_ACPI_EXT_H
mdefine_line|#define _ASM_IA64_ACPI_EXT_H
multiline_comment|/*&n; * Advanced Configuration and Power Infterface&n; * Based on &squot;ACPI Specification 1.0b&squot; Febryary 2, 1999&n; * and &squot;IA-64 Extensions to the ACPI Specification&squot; Rev 0.6&n; *&n; * Copyright (C) 1999 VA Linux Systems&n; * Copyright (C) 1999 Walt Drummond &lt;drummond@valinux.com&gt;&n; * Copyright (C) 2000 Intel Corp.&n; * Copyright (C) 2000,2001 J.I. Lee &lt;jung-ik.lee@intel.com&gt;&n; *&t;ACPI 2.0 specification&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#pragma&t;pack(1)
DECL|macro|ACPI_RSDP_SIG
mdefine_line|#define ACPI_RSDP_SIG &quot;RSD PTR &quot; /* Trailing space required */
DECL|macro|ACPI_RSDP_SIG_LEN
mdefine_line|#define ACPI_RSDP_SIG_LEN 8
r_typedef
r_struct
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
DECL|member|rsdt
id|u32
id|rsdt
suffix:semicolon
DECL|member|length
id|u32
id|length
suffix:semicolon
DECL|member|xsdt
r_struct
id|acpi_xsdt
op_star
id|xsdt
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
DECL|typedef|acpi20_rsdp_t
)brace
id|acpi20_rsdp_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|signature
r_char
id|signature
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|length
id|u32
id|length
suffix:semicolon
DECL|member|revision
id|u8
id|revision
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
DECL|member|oem_table_id
r_char
id|oem_table_id
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|oem_revision
id|u32
id|oem_revision
suffix:semicolon
DECL|member|creator_id
id|u32
id|creator_id
suffix:semicolon
DECL|member|creator_revision
id|u32
id|creator_revision
suffix:semicolon
DECL|typedef|acpi_desc_table_hdr_t
)brace
id|acpi_desc_table_hdr_t
suffix:semicolon
DECL|macro|ACPI_RSDT_SIG
mdefine_line|#define ACPI_RSDT_SIG &quot;RSDT&quot;
DECL|macro|ACPI_RSDT_SIG_LEN
mdefine_line|#define ACPI_RSDT_SIG_LEN 4
r_typedef
r_struct
(brace
DECL|member|header
id|acpi_desc_table_hdr_t
id|header
suffix:semicolon
DECL|member|reserved
id|u8
id|reserved
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|entry_ptrs
id|u32
id|entry_ptrs
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Not really . . . */
DECL|typedef|acpi20_rsdt_t
)brace
id|acpi20_rsdt_t
suffix:semicolon
DECL|macro|ACPI_XSDT_SIG
mdefine_line|#define ACPI_XSDT_SIG &quot;XSDT&quot;
DECL|macro|ACPI_XSDT_SIG_LEN
mdefine_line|#define ACPI_XSDT_SIG_LEN 4
DECL|struct|acpi_xsdt
r_typedef
r_struct
id|acpi_xsdt
(brace
DECL|member|header
id|acpi_desc_table_hdr_t
id|header
suffix:semicolon
DECL|member|entry_ptrs
r_int
r_int
id|entry_ptrs
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Not really . . . */
DECL|typedef|acpi_xsdt_t
)brace
id|acpi_xsdt_t
suffix:semicolon
multiline_comment|/* Common structures for ACPI 2.0 and 0.71 */
DECL|struct|acpi_entry_iosapic
r_typedef
r_struct
id|acpi_entry_iosapic
(brace
DECL|member|type
id|u8
id|type
suffix:semicolon
DECL|member|length
id|u8
id|length
suffix:semicolon
DECL|member|id
id|u8
id|id
suffix:semicolon
DECL|member|reserved
id|u8
id|reserved
suffix:semicolon
DECL|member|irq_base
id|u32
id|irq_base
suffix:semicolon
multiline_comment|/* start of IRQ&squot;s this IOSAPIC is responsible for. */
DECL|member|address
r_int
r_int
id|address
suffix:semicolon
multiline_comment|/* Address of this IOSAPIC */
DECL|typedef|acpi_entry_iosapic_t
)brace
id|acpi_entry_iosapic_t
suffix:semicolon
multiline_comment|/* Local SAPIC flags */
DECL|macro|LSAPIC_ENABLED
mdefine_line|#define LSAPIC_ENABLED                (1&lt;&lt;0)
DECL|macro|LSAPIC_PERFORMANCE_RESTRICTED
mdefine_line|#define LSAPIC_PERFORMANCE_RESTRICTED (1&lt;&lt;1)
DECL|macro|LSAPIC_PRESENT
mdefine_line|#define LSAPIC_PRESENT                (1&lt;&lt;2)
multiline_comment|/* Defines legacy IRQ-&gt;pin mapping */
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
DECL|member|bus
id|u8
id|bus
suffix:semicolon
multiline_comment|/* Constant 0 == ISA */
DECL|member|isa_irq
id|u8
id|isa_irq
suffix:semicolon
multiline_comment|/* ISA IRQ # */
DECL|member|pin
id|u32
id|pin
suffix:semicolon
multiline_comment|/* called vector in spec; really IOSAPIC pin number */
DECL|member|flags
id|u16
id|flags
suffix:semicolon
multiline_comment|/* Edge/Level trigger &amp; High/Low active */
DECL|typedef|acpi_entry_int_override_t
)brace
id|acpi_entry_int_override_t
suffix:semicolon
DECL|macro|INT_OVERRIDE_ACTIVE_LOW
mdefine_line|#define INT_OVERRIDE_ACTIVE_LOW    0x03
DECL|macro|INT_OVERRIDE_LEVEL_TRIGGER
mdefine_line|#define INT_OVERRIDE_LEVEL_TRIGGER 0x0d
multiline_comment|/* IA64 ext 0.71 */
r_typedef
r_struct
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
DECL|member|reserved
r_char
id|reserved
suffix:semicolon
multiline_comment|/* Must be 0 */
DECL|member|rsdt
r_struct
id|acpi_rsdt
op_star
id|rsdt
suffix:semicolon
DECL|typedef|acpi_rsdp_t
)brace
id|acpi_rsdp_t
suffix:semicolon
DECL|struct|acpi_rsdt
r_typedef
r_struct
id|acpi_rsdt
(brace
DECL|member|header
id|acpi_desc_table_hdr_t
id|header
suffix:semicolon
DECL|member|reserved
id|u8
id|reserved
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|entry_ptrs
r_int
r_int
id|entry_ptrs
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Not really . . . */
DECL|typedef|acpi_rsdt_t
)brace
id|acpi_rsdt_t
suffix:semicolon
DECL|macro|ACPI_SAPIC_SIG
mdefine_line|#define ACPI_SAPIC_SIG &quot;SPIC&quot;
DECL|macro|ACPI_SAPIC_SIG_LEN
mdefine_line|#define ACPI_SAPIC_SIG_LEN 4
r_typedef
r_struct
(brace
DECL|member|header
id|acpi_desc_table_hdr_t
id|header
suffix:semicolon
DECL|member|reserved
id|u8
id|reserved
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|interrupt_block
r_int
r_int
id|interrupt_block
suffix:semicolon
DECL|typedef|acpi_sapic_t
)brace
id|acpi_sapic_t
suffix:semicolon
multiline_comment|/* SAPIC structure types */
DECL|macro|ACPI_ENTRY_LOCAL_SAPIC
mdefine_line|#define ACPI_ENTRY_LOCAL_SAPIC         0
DECL|macro|ACPI_ENTRY_IO_SAPIC
mdefine_line|#define ACPI_ENTRY_IO_SAPIC            1
DECL|macro|ACPI_ENTRY_INT_SRC_OVERRIDE
mdefine_line|#define ACPI_ENTRY_INT_SRC_OVERRIDE    2
DECL|macro|ACPI_ENTRY_PLATFORM_INT_SOURCE
mdefine_line|#define ACPI_ENTRY_PLATFORM_INT_SOURCE 3&t;/* Unimplemented */
DECL|struct|acpi_entry_lsapic
r_typedef
r_struct
id|acpi_entry_lsapic
(brace
DECL|member|type
id|u8
id|type
suffix:semicolon
DECL|member|length
id|u8
id|length
suffix:semicolon
DECL|member|acpi_processor_id
id|u16
id|acpi_processor_id
suffix:semicolon
DECL|member|flags
id|u16
id|flags
suffix:semicolon
DECL|member|id
id|u8
id|id
suffix:semicolon
DECL|member|eid
id|u8
id|eid
suffix:semicolon
DECL|typedef|acpi_entry_lsapic_t
)brace
id|acpi_entry_lsapic_t
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
DECL|member|flags
id|u16
id|flags
suffix:semicolon
DECL|member|int_type
id|u8
id|int_type
suffix:semicolon
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
DECL|member|reserved
id|u8
id|reserved
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|global_vector
id|u32
id|global_vector
suffix:semicolon
DECL|typedef|acpi_entry_platform_src_t
)brace
id|acpi_entry_platform_src_t
suffix:semicolon
multiline_comment|/* ACPI 2.0 with 1.3 errata specific structures */
DECL|macro|ACPI_MADT_SIG
mdefine_line|#define ACPI_MADT_SIG &quot;APIC&quot;
DECL|macro|ACPI_MADT_SIG_LEN
mdefine_line|#define ACPI_MADT_SIG_LEN 4
r_typedef
r_struct
(brace
DECL|member|header
id|acpi_desc_table_hdr_t
id|header
suffix:semicolon
DECL|member|lapic_address
id|u32
id|lapic_address
suffix:semicolon
DECL|member|flags
id|u32
id|flags
suffix:semicolon
DECL|typedef|acpi_madt_t
)brace
id|acpi_madt_t
suffix:semicolon
multiline_comment|/* acpi 2.0 MADT flags */
DECL|macro|MADT_PCAT_COMPAT
mdefine_line|#define MADT_PCAT_COMPAT&t;(1&lt;&lt;0)
multiline_comment|/* acpi 2.0 MADT structure types */
DECL|macro|ACPI20_ENTRY_LOCAL_APIC
mdefine_line|#define ACPI20_ENTRY_LOCAL_APIC&t;&t;&t;0
DECL|macro|ACPI20_ENTRY_IO_APIC
mdefine_line|#define ACPI20_ENTRY_IO_APIC&t;&t;&t;1
DECL|macro|ACPI20_ENTRY_INT_SRC_OVERRIDE
mdefine_line|#define ACPI20_ENTRY_INT_SRC_OVERRIDE&t;&t;2
DECL|macro|ACPI20_ENTRY_NMI_SOURCE
mdefine_line|#define ACPI20_ENTRY_NMI_SOURCE&t;&t;&t;3
DECL|macro|ACPI20_ENTRY_LOCAL_APIC_NMI
mdefine_line|#define ACPI20_ENTRY_LOCAL_APIC_NMI&t;&t;4
DECL|macro|ACPI20_ENTRY_LOCAL_APIC_ADDR_OVERRIDE
mdefine_line|#define ACPI20_ENTRY_LOCAL_APIC_ADDR_OVERRIDE&t;5
DECL|macro|ACPI20_ENTRY_IO_SAPIC
mdefine_line|#define ACPI20_ENTRY_IO_SAPIC&t;&t;&t;6
DECL|macro|ACPI20_ENTRY_LOCAL_SAPIC
mdefine_line|#define ACPI20_ENTRY_LOCAL_SAPIC&t;&t;7
DECL|macro|ACPI20_ENTRY_PLATFORM_INT_SOURCE
mdefine_line|#define ACPI20_ENTRY_PLATFORM_INT_SOURCE&t;8
DECL|struct|acpi20_entry_lsapic
r_typedef
r_struct
id|acpi20_entry_lsapic
(brace
DECL|member|type
id|u8
id|type
suffix:semicolon
DECL|member|length
id|u8
id|length
suffix:semicolon
DECL|member|acpi_processor_id
id|u8
id|acpi_processor_id
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
DECL|member|flags
id|u32
id|flags
suffix:semicolon
DECL|typedef|acpi20_entry_lsapic_t
)brace
id|acpi20_entry_lsapic_t
suffix:semicolon
DECL|struct|acpi20_entry_lapic_addr_override
r_typedef
r_struct
id|acpi20_entry_lapic_addr_override
(brace
DECL|member|type
id|u8
id|type
suffix:semicolon
DECL|member|length
id|u8
id|length
suffix:semicolon
DECL|member|reserved
id|u8
id|reserved
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|lapic_address
r_int
r_int
id|lapic_address
suffix:semicolon
DECL|typedef|acpi20_entry_lapic_addr_override_t
)brace
id|acpi20_entry_lapic_addr_override_t
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
DECL|member|flags
id|u16
id|flags
suffix:semicolon
DECL|member|int_type
id|u8
id|int_type
suffix:semicolon
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
DECL|member|global_vector
id|u32
id|global_vector
suffix:semicolon
DECL|typedef|acpi20_entry_platform_src_t
)brace
id|acpi20_entry_platform_src_t
suffix:semicolon
multiline_comment|/* constants for interrupt routing API for device drivers */
DECL|macro|ACPI20_ENTRY_PIS_PMI
mdefine_line|#define ACPI20_ENTRY_PIS_PMI&t;1
DECL|macro|ACPI20_ENTRY_PIS_INIT
mdefine_line|#define ACPI20_ENTRY_PIS_INIT&t;2
DECL|macro|ACPI20_ENTRY_PIS_CPEI
mdefine_line|#define ACPI20_ENTRY_PIS_CPEI&t;3
DECL|macro|ACPI_MAX_PLATFORM_IRQS
mdefine_line|#define ACPI_MAX_PLATFORM_IRQS&t;4
DECL|macro|ACPI_SPCRT_SIG
mdefine_line|#define ACPI_SPCRT_SIG&t;&quot;SPCR&quot;
DECL|macro|ACPI_SPCRT_SIG_LEN
mdefine_line|#define ACPI_SPCRT_SIG_LEN 4
DECL|macro|ACPI_DBGPT_SIG
mdefine_line|#define ACPI_DBGPT_SIG&t;&quot;DBGP&quot;
DECL|macro|ACPI_DBGPT_SIG_LEN
mdefine_line|#define ACPI_DBGPT_SIG_LEN 4
r_extern
r_int
id|acpi20_parse
c_func
(paren
id|acpi20_rsdp_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|acpi20_early_parse
c_func
(paren
id|acpi20_rsdp_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|acpi_parse
c_func
(paren
id|acpi_rsdp_t
op_star
)paren
suffix:semicolon
r_extern
r_const
r_char
op_star
id|acpi_get_sysname
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|acpi_request_vector
c_func
(paren
id|u32
id|int_type
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|acpi_idle
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* power-management idle function, if any */
macro_line|#ifdef CONFIG_NUMA
r_extern
id|cnodeid_t
id|paddr_to_nid
c_func
(paren
r_int
r_int
id|paddr
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * ACPI 2.0 SRAT Table&n; * http://www.microsoft.com/HWDEV/design/SRAT.htm&n; */
DECL|struct|acpi_srat
r_typedef
r_struct
id|acpi_srat
(brace
DECL|member|header
id|acpi_desc_table_hdr_t
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
DECL|typedef|acpi_srat_t
)brace
id|acpi_srat_t
suffix:semicolon
DECL|struct|srat_cpu_affinity
r_typedef
r_struct
id|srat_cpu_affinity
(brace
DECL|member|type
id|u8
id|type
suffix:semicolon
DECL|member|length
id|u8
id|length
suffix:semicolon
DECL|member|proximity_domain
id|u8
id|proximity_domain
suffix:semicolon
DECL|member|apic_id
id|u8
id|apic_id
suffix:semicolon
DECL|member|flags
id|u32
id|flags
suffix:semicolon
DECL|member|local_sapic_eid
id|u8
id|local_sapic_eid
suffix:semicolon
DECL|member|reserved
id|u8
id|reserved
(braket
l_int|7
)braket
suffix:semicolon
DECL|typedef|srat_cpu_affinity_t
)brace
id|srat_cpu_affinity_t
suffix:semicolon
DECL|struct|srat_memory_affinity
r_typedef
r_struct
id|srat_memory_affinity
(brace
DECL|member|type
id|u8
id|type
suffix:semicolon
DECL|member|length
id|u8
id|length
suffix:semicolon
DECL|member|proximity_domain
id|u8
id|proximity_domain
suffix:semicolon
DECL|member|reserved
id|u8
id|reserved
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
DECL|member|flags
id|u32
id|flags
suffix:semicolon
DECL|member|reserved2
id|u64
id|reserved2
suffix:semicolon
DECL|typedef|srat_memory_affinity_t
)brace
id|srat_memory_affinity_t
suffix:semicolon
multiline_comment|/* ACPI 2.0 SRAT structure */
DECL|macro|ACPI_SRAT_SIG
mdefine_line|#define ACPI_SRAT_SIG &quot;SRAT&quot;
DECL|macro|ACPI_SRAT_SIG_LEN
mdefine_line|#define ACPI_SRAT_SIG_LEN 4
DECL|macro|ACPI_SRAT_REVISION
mdefine_line|#define ACPI_SRAT_REVISION 1
DECL|macro|SRAT_CPU_STRUCTURE
mdefine_line|#define SRAT_CPU_STRUCTURE&t;&t;0
DECL|macro|SRAT_MEMORY_STRUCTURE
mdefine_line|#define SRAT_MEMORY_STRUCTURE&t;&t;1
multiline_comment|/* Only 1 flag for cpu affinity structure! */
DECL|macro|SRAT_CPU_FLAGS_ENABLED
mdefine_line|#define SRAT_CPU_FLAGS_ENABLED&t;&t;&t;0x00000001
DECL|macro|SRAT_MEMORY_FLAGS_ENABLED
mdefine_line|#define SRAT_MEMORY_FLAGS_ENABLED&t;&t;0x00000001
DECL|macro|SRAT_MEMORY_FLAGS_HOTREMOVABLE
mdefine_line|#define SRAT_MEMORY_FLAGS_HOTREMOVABLE&t;&t;0x00000002
multiline_comment|/* ACPI 2.0 address range types */
DECL|macro|ACPI_ADDRESS_RANGE_MEMORY
mdefine_line|#define ACPI_ADDRESS_RANGE_MEMORY&t;1
DECL|macro|ACPI_ADDRESS_RANGE_RESERVED
mdefine_line|#define ACPI_ADDRESS_RANGE_RESERVED&t;2
DECL|macro|ACPI_ADDRESS_RANGE_ACPI
mdefine_line|#define ACPI_ADDRESS_RANGE_ACPI&t;&t;3
DECL|macro|ACPI_ADDRESS_RANGE_NVS
mdefine_line|#define ACPI_ADDRESS_RANGE_NVS&t;&t;4
DECL|macro|NODE_ARRAY_INDEX
mdefine_line|#define NODE_ARRAY_INDEX(x)&t;((x) / 8)&t;/* 8 bits/char */
DECL|macro|NODE_ARRAY_OFFSET
mdefine_line|#define NODE_ARRAY_OFFSET(x)&t;((x) % 8)&t;/* 8 bits/char */
DECL|macro|MAX_PXM_DOMAINS
mdefine_line|#define MAX_PXM_DOMAINS&t;&t;(256)
macro_line|#ifdef CONFIG_DISCONTIGMEM
multiline_comment|/*&n; * List of node memory chunks. Filled when parsing SRAT table to&n; * obtain information about memory nodes.&n;*/
DECL|struct|node_memory_chunk_s
r_struct
id|node_memory_chunk_s
(brace
DECL|member|start_paddr
r_int
r_int
id|start_paddr
suffix:semicolon
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
DECL|member|pxm
r_int
id|pxm
suffix:semicolon
singleline_comment|// proximity domain of node
DECL|member|nid
r_int
id|nid
suffix:semicolon
singleline_comment|// which cnode contains this chunk?
DECL|member|bank
r_int
id|bank
suffix:semicolon
singleline_comment|// which mem bank on this node
)brace
suffix:semicolon
r_extern
r_struct
id|node_memory_chunk_s
id|node_memory_chunk
(braket
id|PLAT_MAXCLUMPS
)braket
suffix:semicolon
singleline_comment|// temporary?
DECL|struct|node_cpuid_s
r_struct
id|node_cpuid_s
(brace
DECL|member|phys_id
id|u16
id|phys_id
suffix:semicolon
multiline_comment|/* id &lt;&lt; 8 | eid */
DECL|member|pxm
r_int
id|pxm
suffix:semicolon
singleline_comment|// proximity domain of cpu
DECL|member|nid
r_int
id|nid
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|node_cpuid_s
id|node_cpuid
(braket
id|NR_CPUS
)braket
suffix:semicolon
r_extern
r_int
id|pxm_to_nid_map
(braket
id|MAX_PXM_DOMAINS
)braket
suffix:semicolon
multiline_comment|/* _PXM to logical node ID map */
r_extern
r_int
id|nid_to_pxm_map
(braket
id|PLAT_MAX_COMPACT_NODES
)braket
suffix:semicolon
multiline_comment|/* logical node ID to _PXM map */
r_extern
r_int
id|numnodes
suffix:semicolon
multiline_comment|/* total number of nodes in system */
r_extern
r_int
id|num_memory_chunks
suffix:semicolon
multiline_comment|/* total number of memory chunks */
multiline_comment|/*&n; * ACPI 2.0 SLIT Table&n; * http://devresource.hp.com/devresource/Docs/TechPapers/IA64/slit.pdf&n; */
DECL|struct|acpi_slit
r_typedef
r_struct
id|acpi_slit
(brace
DECL|member|header
id|acpi_desc_table_hdr_t
id|header
suffix:semicolon
DECL|member|localities
id|u64
id|localities
suffix:semicolon
DECL|member|entries
id|u8
id|entries
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* dummy, real size = locality^2 */
DECL|typedef|acpi_slit_t
)brace
id|acpi_slit_t
suffix:semicolon
r_extern
id|u8
id|acpi20_slit
(braket
id|PLAT_MAX_COMPACT_NODES
op_star
id|PLAT_MAX_COMPACT_NODES
)braket
suffix:semicolon
DECL|macro|ACPI_SLIT_SIG
mdefine_line|#define ACPI_SLIT_SIG &quot;SLIT&quot;
DECL|macro|ACPI_SLIT_SIG_LEN
mdefine_line|#define ACPI_SLIT_SIG_LEN 4
DECL|macro|ACPI_SLIT_REVISION
mdefine_line|#define ACPI_SLIT_REVISION 1
DECL|macro|ACPI_SLIT_LOCAL
mdefine_line|#define ACPI_SLIT_LOCAL 10
macro_line|#endif /* CONFIG_DISCONTIGMEM */
macro_line|#pragma&t;pack()
macro_line|#endif /* _ASM_IA64_ACPI_EXT_H */
eof
