macro_line|#ifndef __ASM_MPSPEC_H
DECL|macro|__ASM_MPSPEC_H
mdefine_line|#define __ASM_MPSPEC_H
multiline_comment|/*&n; * Structure definitions for SMP machines following the&n; * Intel Multiprocessing Specification 1.1 and 1.4.&n; */
multiline_comment|/*&n; * This tag identifies where the SMP configuration&n; * information is. &n; */
DECL|macro|SMP_MAGIC_IDENT
mdefine_line|#define SMP_MAGIC_IDENT&t;((&squot;_&squot;&lt;&lt;24)|(&squot;P&squot;&lt;&lt;16)|(&squot;M&squot;&lt;&lt;8)|&squot;_&squot;)
multiline_comment|/*&n; * a maximum of 16 APICs with the current APIC ID architecture.&n; */
DECL|macro|MAX_APICS
mdefine_line|#define MAX_APICS 16
DECL|struct|intel_mp_floating
r_struct
id|intel_mp_floating
(brace
DECL|member|mpf_signature
r_char
id|mpf_signature
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* &quot;_MP_&quot; &t;&t;&t;*/
DECL|member|mpf_physptr
r_int
r_int
id|mpf_physptr
suffix:semicolon
multiline_comment|/* Configuration table address&t;*/
DECL|member|mpf_length
r_int
r_char
id|mpf_length
suffix:semicolon
multiline_comment|/* Our length (paragraphs)&t;*/
DECL|member|mpf_specification
r_int
r_char
id|mpf_specification
suffix:semicolon
multiline_comment|/* Specification version&t;*/
DECL|member|mpf_checksum
r_int
r_char
id|mpf_checksum
suffix:semicolon
multiline_comment|/* Checksum (makes sum 0)&t;*/
DECL|member|mpf_feature1
r_int
r_char
id|mpf_feature1
suffix:semicolon
multiline_comment|/* Standard or configuration ? &t;*/
DECL|member|mpf_feature2
r_int
r_char
id|mpf_feature2
suffix:semicolon
multiline_comment|/* Bit7 set for IMCR|PIC&t;*/
DECL|member|mpf_feature3
r_int
r_char
id|mpf_feature3
suffix:semicolon
multiline_comment|/* Unused (0)&t;&t;&t;*/
DECL|member|mpf_feature4
r_int
r_char
id|mpf_feature4
suffix:semicolon
multiline_comment|/* Unused (0)&t;&t;&t;*/
DECL|member|mpf_feature5
r_int
r_char
id|mpf_feature5
suffix:semicolon
multiline_comment|/* Unused (0)&t;&t;&t;*/
)brace
suffix:semicolon
DECL|struct|mp_config_table
r_struct
id|mp_config_table
(brace
DECL|member|mpc_signature
r_char
id|mpc_signature
(braket
l_int|4
)braket
suffix:semicolon
DECL|macro|MPC_SIGNATURE
mdefine_line|#define MPC_SIGNATURE &quot;PCMP&quot;
DECL|member|mpc_length
r_int
r_int
id|mpc_length
suffix:semicolon
multiline_comment|/* Size of table */
DECL|member|mpc_spec
r_char
id|mpc_spec
suffix:semicolon
multiline_comment|/* 0x01 */
DECL|member|mpc_checksum
r_char
id|mpc_checksum
suffix:semicolon
DECL|member|mpc_oem
r_char
id|mpc_oem
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|mpc_productid
r_char
id|mpc_productid
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|mpc_oemptr
r_int
r_int
id|mpc_oemptr
suffix:semicolon
multiline_comment|/* 0 if not present */
DECL|member|mpc_oemsize
r_int
r_int
id|mpc_oemsize
suffix:semicolon
multiline_comment|/* 0 if not present */
DECL|member|mpc_oemcount
r_int
r_int
id|mpc_oemcount
suffix:semicolon
DECL|member|mpc_lapic
r_int
r_int
id|mpc_lapic
suffix:semicolon
multiline_comment|/* APIC address */
DECL|member|reserved
r_int
r_int
id|reserved
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Followed by entries */
DECL|macro|MP_PROCESSOR
mdefine_line|#define&t;MP_PROCESSOR&t;0
DECL|macro|MP_BUS
mdefine_line|#define&t;MP_BUS&t;&t;1
DECL|macro|MP_IOAPIC
mdefine_line|#define&t;MP_IOAPIC&t;2
DECL|macro|MP_INTSRC
mdefine_line|#define&t;MP_INTSRC&t;3
DECL|macro|MP_LINTSRC
mdefine_line|#define&t;MP_LINTSRC&t;4
DECL|struct|mpc_config_processor
r_struct
id|mpc_config_processor
(brace
DECL|member|mpc_type
r_int
r_char
id|mpc_type
suffix:semicolon
DECL|member|mpc_apicid
r_int
r_char
id|mpc_apicid
suffix:semicolon
multiline_comment|/* Local APIC number */
DECL|member|mpc_apicver
r_int
r_char
id|mpc_apicver
suffix:semicolon
multiline_comment|/* Its versions */
DECL|member|mpc_cpuflag
r_int
r_char
id|mpc_cpuflag
suffix:semicolon
DECL|macro|CPU_ENABLED
mdefine_line|#define CPU_ENABLED&t;&t;1&t;/* Processor is available */
DECL|macro|CPU_BOOTPROCESSOR
mdefine_line|#define CPU_BOOTPROCESSOR&t;2&t;/* Processor is the BP */
DECL|member|mpc_cpufeature
r_int
r_int
id|mpc_cpufeature
suffix:semicolon
DECL|macro|CPU_STEPPING_MASK
mdefine_line|#define CPU_STEPPING_MASK 0x0F
DECL|macro|CPU_MODEL_MASK
mdefine_line|#define CPU_MODEL_MASK&t;0xF0
DECL|macro|CPU_FAMILY_MASK
mdefine_line|#define CPU_FAMILY_MASK&t;0xF00
DECL|member|mpc_featureflag
r_int
r_int
id|mpc_featureflag
suffix:semicolon
multiline_comment|/* CPUID feature value */
DECL|member|mpc_reserved
r_int
r_int
id|mpc_reserved
(braket
l_int|2
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|mpc_config_bus
r_struct
id|mpc_config_bus
(brace
DECL|member|mpc_type
r_int
r_char
id|mpc_type
suffix:semicolon
DECL|member|mpc_busid
r_int
r_char
id|mpc_busid
suffix:semicolon
r_int
r_char
id|mpc_bustype
(braket
l_int|6
)braket
id|__attribute
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* List of Bus Type string values, Intel MP Spec. */
DECL|macro|BUSTYPE_EISA
mdefine_line|#define BUSTYPE_EISA&t;&quot;EISA&quot;
DECL|macro|BUSTYPE_ISA
mdefine_line|#define BUSTYPE_ISA&t;&quot;ISA&quot;
DECL|macro|BUSTYPE_INTERN
mdefine_line|#define BUSTYPE_INTERN&t;&quot;INTERN&quot;&t;/* Internal BUS */
DECL|macro|BUSTYPE_MCA
mdefine_line|#define BUSTYPE_MCA&t;&quot;MCA&quot;
DECL|macro|BUSTYPE_VL
mdefine_line|#define BUSTYPE_VL&t;&quot;VL&quot;&t;&t;/* Local bus */
DECL|macro|BUSTYPE_PCI
mdefine_line|#define BUSTYPE_PCI&t;&quot;PCI&quot;
DECL|macro|BUSTYPE_PCMCIA
mdefine_line|#define BUSTYPE_PCMCIA&t;&quot;PCMCIA&quot;
DECL|macro|BUSTYPE_CBUS
mdefine_line|#define BUSTYPE_CBUS&t;&quot;CBUS&quot;
DECL|macro|BUSTYPE_CBUSII
mdefine_line|#define BUSTYPE_CBUSII&t;&quot;CBUSII&quot;
DECL|macro|BUSTYPE_FUTURE
mdefine_line|#define BUSTYPE_FUTURE&t;&quot;FUTURE&quot;
DECL|macro|BUSTYPE_MBI
mdefine_line|#define BUSTYPE_MBI&t;&quot;MBI&quot;
DECL|macro|BUSTYPE_MBII
mdefine_line|#define BUSTYPE_MBII&t;&quot;MBII&quot;
DECL|macro|BUSTYPE_MPI
mdefine_line|#define BUSTYPE_MPI&t;&quot;MPI&quot;
DECL|macro|BUSTYPE_MPSA
mdefine_line|#define BUSTYPE_MPSA&t;&quot;MPSA&quot;
DECL|macro|BUSTYPE_NUBUS
mdefine_line|#define BUSTYPE_NUBUS&t;&quot;NUBUS&quot;
DECL|macro|BUSTYPE_TC
mdefine_line|#define BUSTYPE_TC&t;&quot;TC&quot;
DECL|macro|BUSTYPE_VME
mdefine_line|#define BUSTYPE_VME&t;&quot;VME&quot;
DECL|macro|BUSTYPE_XPRESS
mdefine_line|#define BUSTYPE_XPRESS&t;&quot;XPRESS&quot;
DECL|struct|mpc_config_ioapic
r_struct
id|mpc_config_ioapic
(brace
DECL|member|mpc_type
r_int
r_char
id|mpc_type
suffix:semicolon
DECL|member|mpc_apicid
r_int
r_char
id|mpc_apicid
suffix:semicolon
DECL|member|mpc_apicver
r_int
r_char
id|mpc_apicver
suffix:semicolon
DECL|member|mpc_flags
r_int
r_char
id|mpc_flags
suffix:semicolon
DECL|macro|MPC_APIC_USABLE
mdefine_line|#define MPC_APIC_USABLE&t;&t;0x01
DECL|member|mpc_apicaddr
r_int
r_int
id|mpc_apicaddr
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|mpc_config_intsrc
r_struct
id|mpc_config_intsrc
(brace
DECL|member|mpc_type
r_int
r_char
id|mpc_type
suffix:semicolon
DECL|member|mpc_irqtype
r_int
r_char
id|mpc_irqtype
suffix:semicolon
DECL|member|mpc_irqflag
r_int
r_int
id|mpc_irqflag
suffix:semicolon
DECL|member|mpc_srcbus
r_int
r_char
id|mpc_srcbus
suffix:semicolon
DECL|member|mpc_srcbusirq
r_int
r_char
id|mpc_srcbusirq
suffix:semicolon
DECL|member|mpc_dstapic
r_int
r_char
id|mpc_dstapic
suffix:semicolon
DECL|member|mpc_dstirq
r_int
r_char
id|mpc_dstirq
suffix:semicolon
)brace
suffix:semicolon
DECL|enum|mp_irq_source_types
r_enum
id|mp_irq_source_types
(brace
DECL|enumerator|mp_INT
id|mp_INT
op_assign
l_int|0
comma
DECL|enumerator|mp_NMI
id|mp_NMI
op_assign
l_int|1
comma
DECL|enumerator|mp_SMI
id|mp_SMI
op_assign
l_int|2
comma
DECL|enumerator|mp_ExtINT
id|mp_ExtINT
op_assign
l_int|3
)brace
suffix:semicolon
DECL|macro|MP_IRQDIR_DEFAULT
mdefine_line|#define MP_IRQDIR_DEFAULT&t;0
DECL|macro|MP_IRQDIR_HIGH
mdefine_line|#define MP_IRQDIR_HIGH&t;&t;1
DECL|macro|MP_IRQDIR_LOW
mdefine_line|#define MP_IRQDIR_LOW&t;&t;3
DECL|struct|mpc_config_lintsrc
r_struct
id|mpc_config_lintsrc
(brace
DECL|member|mpc_type
r_int
r_char
id|mpc_type
suffix:semicolon
DECL|member|mpc_irqtype
r_int
r_char
id|mpc_irqtype
suffix:semicolon
DECL|member|mpc_irqflag
r_int
r_int
id|mpc_irqflag
suffix:semicolon
DECL|member|mpc_srcbusid
r_int
r_char
id|mpc_srcbusid
suffix:semicolon
DECL|member|mpc_srcbusirq
r_int
r_char
id|mpc_srcbusirq
suffix:semicolon
DECL|member|mpc_destapic
r_int
r_char
id|mpc_destapic
suffix:semicolon
DECL|macro|MP_APIC_ALL
mdefine_line|#define MP_APIC_ALL&t;0xFF
DECL|member|mpc_destapiclint
r_int
r_char
id|mpc_destapiclint
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;Default configurations&n; *&n; *&t;1&t;2 CPU ISA 82489DX&n; *&t;2&t;2 CPU EISA 82489DX neither IRQ 0 timer nor IRQ 13 DMA chaining&n; *&t;3&t;2 CPU EISA 82489DX&n; *&t;4&t;2 CPU MCA 82489DX&n; *&t;5&t;2 CPU ISA+PCI&n; *&t;6&t;2 CPU EISA+PCI&n; *&t;7&t;2 CPU MCA+PCI&n; */
DECL|macro|MAX_IRQ_SOURCES
mdefine_line|#define MAX_IRQ_SOURCES 256
DECL|macro|MAX_MP_BUSSES
mdefine_line|#define MAX_MP_BUSSES 32
DECL|enum|mp_bustype
r_enum
id|mp_bustype
(brace
DECL|enumerator|MP_BUS_ISA
id|MP_BUS_ISA
op_assign
l_int|1
comma
DECL|enumerator|MP_BUS_EISA
id|MP_BUS_EISA
comma
DECL|enumerator|MP_BUS_PCI
id|MP_BUS_PCI
comma
DECL|enumerator|MP_BUS_MCA
id|MP_BUS_MCA
)brace
suffix:semicolon
r_extern
r_int
id|mp_bus_id_to_type
(braket
id|MAX_MP_BUSSES
)braket
suffix:semicolon
r_extern
r_int
id|mp_bus_id_to_node
(braket
id|MAX_MP_BUSSES
)braket
suffix:semicolon
r_extern
r_int
id|mp_bus_id_to_local
(braket
id|MAX_MP_BUSSES
)braket
suffix:semicolon
r_extern
r_int
id|quad_local_to_mp_bus_id
(braket
id|NR_CPUS
op_div
l_int|4
)braket
(braket
l_int|4
)braket
suffix:semicolon
r_extern
r_int
id|mp_bus_id_to_pci_bus
(braket
id|MAX_MP_BUSSES
)braket
suffix:semicolon
r_extern
r_int
r_int
id|boot_cpu_physical_apicid
suffix:semicolon
r_extern
r_int
r_int
id|phys_cpu_present_map
suffix:semicolon
r_extern
r_int
id|smp_found_config
suffix:semicolon
r_extern
r_void
id|find_smp_config
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|get_smp_config
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|nr_ioapics
suffix:semicolon
r_extern
r_int
id|apic_version
(braket
id|MAX_APICS
)braket
suffix:semicolon
r_extern
r_int
id|mp_bus_id_to_type
(braket
id|MAX_MP_BUSSES
)braket
suffix:semicolon
r_extern
r_int
id|mp_irq_entries
suffix:semicolon
r_extern
r_struct
id|mpc_config_intsrc
id|mp_irqs
(braket
id|MAX_IRQ_SOURCES
)braket
suffix:semicolon
r_extern
r_int
id|mpc_default_type
suffix:semicolon
r_extern
r_int
id|mp_bus_id_to_pci_bus
(braket
id|MAX_MP_BUSSES
)braket
suffix:semicolon
r_extern
r_int
id|mp_current_pci_id
suffix:semicolon
r_extern
r_int
r_int
id|mp_lapic_addr
suffix:semicolon
r_extern
r_int
id|pic_mode
suffix:semicolon
r_extern
r_int
id|using_apic_timer
suffix:semicolon
macro_line|#endif
eof
