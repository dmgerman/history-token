macro_line|#ifndef __ASM_IO_APIC_H
DECL|macro|__ASM_IO_APIC_H
mdefine_line|#define __ASM_IO_APIC_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/mpspec.h&gt;
multiline_comment|/*&n; * Intel IO-APIC support for SMP and UP systems.&n; *&n; * Copyright (C) 1997, 1998, 1999, 2000 Ingo Molnar&n; */
macro_line|#ifdef CONFIG_X86_IO_APIC
macro_line|#ifdef CONFIG_PCI_MSI
DECL|function|use_pci_vector
r_static
r_inline
r_int
id|use_pci_vector
c_func
(paren
r_void
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|disable_edge_ioapic_vector
r_static
r_inline
r_void
id|disable_edge_ioapic_vector
c_func
(paren
r_int
r_int
id|vector
)paren
(brace
)brace
DECL|function|mask_and_ack_level_ioapic_vector
r_static
r_inline
r_void
id|mask_and_ack_level_ioapic_vector
c_func
(paren
r_int
r_int
id|vector
)paren
(brace
)brace
DECL|function|end_edge_ioapic_vector
r_static
r_inline
r_void
id|end_edge_ioapic_vector
(paren
r_int
r_int
id|vector
)paren
(brace
)brace
DECL|macro|startup_level_ioapic
mdefine_line|#define startup_level_ioapic&t;startup_level_ioapic_vector
DECL|macro|shutdown_level_ioapic
mdefine_line|#define shutdown_level_ioapic&t;mask_IO_APIC_vector
DECL|macro|enable_level_ioapic
mdefine_line|#define enable_level_ioapic&t;unmask_IO_APIC_vector
DECL|macro|disable_level_ioapic
mdefine_line|#define disable_level_ioapic&t;mask_IO_APIC_vector
DECL|macro|mask_and_ack_level_ioapic
mdefine_line|#define mask_and_ack_level_ioapic mask_and_ack_level_ioapic_vector
DECL|macro|end_level_ioapic
mdefine_line|#define end_level_ioapic&t;end_level_ioapic_vector
DECL|macro|set_ioapic_affinity
mdefine_line|#define set_ioapic_affinity&t;set_ioapic_affinity_vector
DECL|macro|startup_edge_ioapic
mdefine_line|#define startup_edge_ioapic &t;startup_edge_ioapic_vector
DECL|macro|shutdown_edge_ioapic
mdefine_line|#define shutdown_edge_ioapic &t;disable_edge_ioapic_vector
DECL|macro|enable_edge_ioapic
mdefine_line|#define enable_edge_ioapic &t;unmask_IO_APIC_vector
DECL|macro|disable_edge_ioapic
mdefine_line|#define disable_edge_ioapic &t;disable_edge_ioapic_vector
DECL|macro|ack_edge_ioapic
mdefine_line|#define ack_edge_ioapic &t;ack_edge_ioapic_vector
DECL|macro|end_edge_ioapic
mdefine_line|#define end_edge_ioapic &t;end_edge_ioapic_vector
macro_line|#else
DECL|function|use_pci_vector
r_static
r_inline
r_int
id|use_pci_vector
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|disable_edge_ioapic_irq
r_static
r_inline
r_void
id|disable_edge_ioapic_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
)brace
DECL|function|mask_and_ack_level_ioapic_irq
r_static
r_inline
r_void
id|mask_and_ack_level_ioapic_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
)brace
DECL|function|end_edge_ioapic_irq
r_static
r_inline
r_void
id|end_edge_ioapic_irq
(paren
r_int
r_int
id|irq
)paren
(brace
)brace
DECL|macro|startup_level_ioapic
mdefine_line|#define startup_level_ioapic&t;startup_level_ioapic_irq
DECL|macro|shutdown_level_ioapic
mdefine_line|#define shutdown_level_ioapic&t;mask_IO_APIC_irq
DECL|macro|enable_level_ioapic
mdefine_line|#define enable_level_ioapic&t;unmask_IO_APIC_irq
DECL|macro|disable_level_ioapic
mdefine_line|#define disable_level_ioapic&t;mask_IO_APIC_irq
DECL|macro|mask_and_ack_level_ioapic
mdefine_line|#define mask_and_ack_level_ioapic mask_and_ack_level_ioapic_irq
DECL|macro|end_level_ioapic
mdefine_line|#define end_level_ioapic&t;end_level_ioapic_irq
DECL|macro|set_ioapic_affinity
mdefine_line|#define set_ioapic_affinity&t;set_ioapic_affinity_irq
DECL|macro|startup_edge_ioapic
mdefine_line|#define startup_edge_ioapic &t;startup_edge_ioapic_irq
DECL|macro|shutdown_edge_ioapic
mdefine_line|#define shutdown_edge_ioapic &t;disable_edge_ioapic_irq
DECL|macro|enable_edge_ioapic
mdefine_line|#define enable_edge_ioapic &t;unmask_IO_APIC_irq
DECL|macro|disable_edge_ioapic
mdefine_line|#define disable_edge_ioapic &t;disable_edge_ioapic_irq
DECL|macro|ack_edge_ioapic
mdefine_line|#define ack_edge_ioapic &t;ack_edge_ioapic_irq
DECL|macro|end_edge_ioapic
mdefine_line|#define end_edge_ioapic &t;end_edge_ioapic_irq
macro_line|#endif
DECL|macro|IO_APIC_BASE
mdefine_line|#define IO_APIC_BASE(idx) &bslash;&n;&t;&t;((volatile int *)(__fix_to_virt(FIX_IO_APIC_BASE_0 + idx) &bslash;&n;&t;&t;+ (mp_ioapics[idx].mpc_apicaddr &amp; ~PAGE_MASK)))
multiline_comment|/*&n; * The structure of the IO-APIC:&n; */
DECL|union|IO_APIC_reg_00
r_union
id|IO_APIC_reg_00
(brace
DECL|member|raw
id|u32
id|raw
suffix:semicolon
r_struct
(brace
DECL|member|__reserved_2
id|u32
id|__reserved_2
suffix:colon
l_int|14
comma
DECL|member|LTS
id|LTS
suffix:colon
l_int|1
comma
DECL|member|delivery_type
id|delivery_type
suffix:colon
l_int|1
comma
DECL|member|__reserved_1
id|__reserved_1
suffix:colon
l_int|8
comma
DECL|member|ID
id|ID
suffix:colon
l_int|8
suffix:semicolon
DECL|member|bits
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|bits
suffix:semicolon
)brace
suffix:semicolon
DECL|union|IO_APIC_reg_01
r_union
id|IO_APIC_reg_01
(brace
DECL|member|raw
id|u32
id|raw
suffix:semicolon
r_struct
(brace
DECL|member|version
id|u32
id|version
suffix:colon
l_int|8
comma
DECL|member|__reserved_2
id|__reserved_2
suffix:colon
l_int|7
comma
DECL|member|PRQ
id|PRQ
suffix:colon
l_int|1
comma
DECL|member|entries
id|entries
suffix:colon
l_int|8
comma
DECL|member|__reserved_1
id|__reserved_1
suffix:colon
l_int|8
suffix:semicolon
DECL|member|bits
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|bits
suffix:semicolon
)brace
suffix:semicolon
DECL|union|IO_APIC_reg_02
r_union
id|IO_APIC_reg_02
(brace
DECL|member|raw
id|u32
id|raw
suffix:semicolon
r_struct
(brace
DECL|member|__reserved_2
id|u32
id|__reserved_2
suffix:colon
l_int|24
comma
DECL|member|arbitration
id|arbitration
suffix:colon
l_int|4
comma
DECL|member|__reserved_1
id|__reserved_1
suffix:colon
l_int|4
suffix:semicolon
DECL|member|bits
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|bits
suffix:semicolon
)brace
suffix:semicolon
DECL|union|IO_APIC_reg_03
r_union
id|IO_APIC_reg_03
(brace
DECL|member|raw
id|u32
id|raw
suffix:semicolon
r_struct
(brace
DECL|member|boot_DT
id|u32
id|boot_DT
suffix:colon
l_int|1
comma
DECL|member|__reserved_1
id|__reserved_1
suffix:colon
l_int|31
suffix:semicolon
DECL|member|bits
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|bits
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * # of IO-APICs and # of IRQ routing registers&n; */
r_extern
r_int
id|nr_ioapics
suffix:semicolon
r_extern
r_int
id|nr_ioapic_registers
(braket
id|MAX_IO_APICS
)braket
suffix:semicolon
DECL|enum|ioapic_irq_destination_types
r_enum
id|ioapic_irq_destination_types
(brace
DECL|enumerator|dest_Fixed
id|dest_Fixed
op_assign
l_int|0
comma
DECL|enumerator|dest_LowestPrio
id|dest_LowestPrio
op_assign
l_int|1
comma
DECL|enumerator|dest_SMI
id|dest_SMI
op_assign
l_int|2
comma
DECL|enumerator|dest__reserved_1
id|dest__reserved_1
op_assign
l_int|3
comma
DECL|enumerator|dest_NMI
id|dest_NMI
op_assign
l_int|4
comma
DECL|enumerator|dest_INIT
id|dest_INIT
op_assign
l_int|5
comma
DECL|enumerator|dest__reserved_2
id|dest__reserved_2
op_assign
l_int|6
comma
DECL|enumerator|dest_ExtINT
id|dest_ExtINT
op_assign
l_int|7
)brace
suffix:semicolon
DECL|struct|IO_APIC_route_entry
r_struct
id|IO_APIC_route_entry
(brace
DECL|member|vector
id|__u32
id|vector
suffix:colon
l_int|8
comma
DECL|member|delivery_mode
id|delivery_mode
suffix:colon
l_int|3
comma
multiline_comment|/* 000: FIXED&n;&t;&t;&t;&t;&t; * 001: lowest prio&n;&t;&t;&t;&t;&t; * 111: ExtINT&n;&t;&t;&t;&t;&t; */
DECL|member|dest_mode
id|dest_mode
suffix:colon
l_int|1
comma
multiline_comment|/* 0: physical, 1: logical */
DECL|member|delivery_status
id|delivery_status
suffix:colon
l_int|1
comma
DECL|member|polarity
id|polarity
suffix:colon
l_int|1
comma
DECL|member|irr
id|irr
suffix:colon
l_int|1
comma
DECL|member|trigger
id|trigger
suffix:colon
l_int|1
comma
multiline_comment|/* 0: edge, 1: level */
DECL|member|mask
id|mask
suffix:colon
l_int|1
comma
multiline_comment|/* 0: enabled, 1: disabled */
DECL|member|__reserved_2
id|__reserved_2
suffix:colon
l_int|15
suffix:semicolon
r_union
(brace
r_struct
(brace
id|__u32
DECL|member|__reserved_1
id|__reserved_1
suffix:colon
l_int|24
comma
DECL|member|physical_dest
id|physical_dest
suffix:colon
l_int|4
comma
DECL|member|__reserved_2
id|__reserved_2
suffix:colon
l_int|4
suffix:semicolon
DECL|member|physical
)brace
id|physical
suffix:semicolon
r_struct
(brace
id|__u32
DECL|member|__reserved_1
id|__reserved_1
suffix:colon
l_int|24
comma
DECL|member|logical_dest
id|logical_dest
suffix:colon
l_int|8
suffix:semicolon
DECL|member|logical
)brace
id|logical
suffix:semicolon
DECL|member|dest
)brace
id|dest
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/*&n; * MP-BIOS irq configuration table structures:&n; */
multiline_comment|/* I/O APIC entries */
r_extern
r_struct
id|mpc_config_ioapic
id|mp_ioapics
(braket
id|MAX_IO_APICS
)braket
suffix:semicolon
multiline_comment|/* # of MP IRQ source entries */
r_extern
r_int
id|mp_irq_entries
suffix:semicolon
multiline_comment|/* MP IRQ source entries */
r_extern
r_struct
id|mpc_config_intsrc
id|mp_irqs
(braket
id|MAX_IRQ_SOURCES
)braket
suffix:semicolon
multiline_comment|/* non-0 if default (table-less) MP configuration */
r_extern
r_int
id|mpc_default_type
suffix:semicolon
DECL|function|io_apic_read
r_static
r_inline
r_int
r_int
id|io_apic_read
c_func
(paren
r_int
r_int
id|apic
comma
r_int
r_int
id|reg
)paren
(brace
op_star
id|IO_APIC_BASE
c_func
(paren
id|apic
)paren
op_assign
id|reg
suffix:semicolon
r_return
op_star
(paren
id|IO_APIC_BASE
c_func
(paren
id|apic
)paren
op_plus
l_int|4
)paren
suffix:semicolon
)brace
DECL|function|io_apic_write
r_static
r_inline
r_void
id|io_apic_write
c_func
(paren
r_int
r_int
id|apic
comma
r_int
r_int
id|reg
comma
r_int
r_int
id|value
)paren
(brace
op_star
id|IO_APIC_BASE
c_func
(paren
id|apic
)paren
op_assign
id|reg
suffix:semicolon
op_star
(paren
id|IO_APIC_BASE
c_func
(paren
id|apic
)paren
op_plus
l_int|4
)paren
op_assign
id|value
suffix:semicolon
)brace
multiline_comment|/*&n; * Re-write a value: to be used for read-modify-write&n; * cycles where the read already set up the index register.&n; *&n; * Older SiS APIC requires we rewrite the index regiser&n; */
r_extern
r_int
id|sis_apic_bug
suffix:semicolon
DECL|function|io_apic_modify
r_static
r_inline
r_void
id|io_apic_modify
c_func
(paren
r_int
r_int
id|apic
comma
r_int
r_int
id|reg
comma
r_int
r_int
id|value
)paren
(brace
r_if
c_cond
(paren
id|sis_apic_bug
)paren
op_star
id|IO_APIC_BASE
c_func
(paren
id|apic
)paren
op_assign
id|reg
suffix:semicolon
op_star
(paren
id|IO_APIC_BASE
c_func
(paren
id|apic
)paren
op_plus
l_int|4
)paren
op_assign
id|value
suffix:semicolon
)brace
multiline_comment|/* 1 if &quot;noapic&quot; boot option passed */
r_extern
r_int
id|skip_ioapic_setup
suffix:semicolon
multiline_comment|/*&n; * If we use the IO-APIC for IRQ routing, disable automatic&n; * assignment of PCI IRQ&squot;s.&n; */
DECL|macro|io_apic_assign_pci_irqs
mdefine_line|#define io_apic_assign_pci_irqs (mp_irq_entries &amp;&amp; !skip_ioapic_setup)
macro_line|#ifdef CONFIG_ACPI_BOOT
r_extern
r_int
id|io_apic_get_unique_id
(paren
r_int
id|ioapic
comma
r_int
id|apic_id
)paren
suffix:semicolon
r_extern
r_int
id|io_apic_get_version
(paren
r_int
id|ioapic
)paren
suffix:semicolon
r_extern
r_int
id|io_apic_get_redir_entries
(paren
r_int
id|ioapic
)paren
suffix:semicolon
r_extern
r_int
id|io_apic_set_pci_routing
(paren
r_int
id|ioapic
comma
r_int
id|pin
comma
r_int
id|irq
comma
r_int
id|edge_level
comma
r_int
id|active_high_low
)paren
suffix:semicolon
macro_line|#endif /*CONFIG_ACPI_BOOT*/
macro_line|#else  /* !CONFIG_X86_IO_APIC */
DECL|macro|io_apic_assign_pci_irqs
mdefine_line|#define io_apic_assign_pci_irqs 0
macro_line|#endif
r_extern
r_int
id|assign_irq_vector
c_func
(paren
r_int
id|irq
)paren
suffix:semicolon
macro_line|#endif
eof
