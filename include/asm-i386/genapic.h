macro_line|#ifndef _ASM_GENAPIC_H
DECL|macro|_ASM_GENAPIC_H
mdefine_line|#define _ASM_GENAPIC_H 1
multiline_comment|/*&n; * Generic APIC driver interface.&n; *&n; * An straight forward mapping of the APIC related parts of the&n; * x86 subarchitecture interface to a dynamic object.&n; *&n; * This is used by the &quot;generic&quot; x86 subarchitecture.&n; *&n; * Copyright 2003 Andi Kleen, SuSE Labs.&n; */
r_struct
id|mpc_config_translation
suffix:semicolon
r_struct
id|mpc_config_bus
suffix:semicolon
r_struct
id|mp_config_table
suffix:semicolon
r_struct
id|mpc_config_processor
suffix:semicolon
DECL|struct|genapic
r_struct
id|genapic
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|probe
r_int
(paren
op_star
id|probe
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|apic_id_registered
r_int
(paren
op_star
id|apic_id_registered
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|target_cpus
id|cpumask_t
(paren
op_star
id|target_cpus
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|int_delivery_mode
r_int
id|int_delivery_mode
suffix:semicolon
DECL|member|int_dest_mode
r_int
id|int_dest_mode
suffix:semicolon
DECL|member|apic_broadcast_id
r_int
id|apic_broadcast_id
suffix:semicolon
DECL|member|esr_disable
r_int
id|esr_disable
suffix:semicolon
DECL|member|check_apicid_used
r_int
r_int
(paren
op_star
id|check_apicid_used
)paren
(paren
id|physid_mask_t
id|bitmap
comma
r_int
id|apicid
)paren
suffix:semicolon
DECL|member|check_apicid_present
r_int
r_int
(paren
op_star
id|check_apicid_present
)paren
(paren
r_int
id|apicid
)paren
suffix:semicolon
DECL|member|no_balance_irq
r_int
id|no_balance_irq
suffix:semicolon
DECL|member|no_ioapic_check
r_int
id|no_ioapic_check
suffix:semicolon
DECL|member|init_apic_ldr
r_void
(paren
op_star
id|init_apic_ldr
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|ioapic_phys_id_map
id|physid_mask_t
(paren
op_star
id|ioapic_phys_id_map
)paren
(paren
id|physid_mask_t
id|map
)paren
suffix:semicolon
DECL|member|clustered_apic_check
r_void
(paren
op_star
id|clustered_apic_check
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|multi_timer_check
r_int
(paren
op_star
id|multi_timer_check
)paren
(paren
r_int
id|apic
comma
r_int
id|irq
)paren
suffix:semicolon
DECL|member|apicid_to_node
r_int
(paren
op_star
id|apicid_to_node
)paren
(paren
r_int
id|logical_apicid
)paren
suffix:semicolon
DECL|member|cpu_to_logical_apicid
r_int
(paren
op_star
id|cpu_to_logical_apicid
)paren
(paren
r_int
id|cpu
)paren
suffix:semicolon
DECL|member|cpu_present_to_apicid
r_int
(paren
op_star
id|cpu_present_to_apicid
)paren
(paren
r_int
id|mps_cpu
)paren
suffix:semicolon
DECL|member|apicid_to_cpu_present
id|physid_mask_t
(paren
op_star
id|apicid_to_cpu_present
)paren
(paren
r_int
id|phys_apicid
)paren
suffix:semicolon
DECL|member|mpc_apic_id
r_int
(paren
op_star
id|mpc_apic_id
)paren
(paren
r_struct
id|mpc_config_processor
op_star
id|m
comma
r_struct
id|mpc_config_translation
op_star
id|t
)paren
suffix:semicolon
DECL|member|setup_portio_remap
r_void
(paren
op_star
id|setup_portio_remap
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|check_phys_apicid_present
r_int
(paren
op_star
id|check_phys_apicid_present
)paren
(paren
r_int
id|boot_cpu_physical_apicid
)paren
suffix:semicolon
DECL|member|enable_apic_mode
r_void
(paren
op_star
id|enable_apic_mode
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|phys_pkg_id
id|u32
(paren
op_star
id|phys_pkg_id
)paren
(paren
id|u32
id|cpuid_apic
comma
r_int
id|index_msb
)paren
suffix:semicolon
multiline_comment|/* mpparse */
DECL|member|mpc_oem_bus_info
r_void
(paren
op_star
id|mpc_oem_bus_info
)paren
(paren
r_struct
id|mpc_config_bus
op_star
comma
r_char
op_star
comma
r_struct
id|mpc_config_translation
op_star
)paren
suffix:semicolon
DECL|member|mpc_oem_pci_bus
r_void
(paren
op_star
id|mpc_oem_pci_bus
)paren
(paren
r_struct
id|mpc_config_bus
op_star
comma
r_struct
id|mpc_config_translation
op_star
)paren
suffix:semicolon
multiline_comment|/* When one of the next two hooks returns 1 the genapic&n;&t;   is switched to this. Essentially they are additional probe &n;&t;   functions. */
DECL|member|mps_oem_check
r_int
(paren
op_star
id|mps_oem_check
)paren
(paren
r_struct
id|mp_config_table
op_star
id|mpc
comma
r_char
op_star
id|oem
comma
r_char
op_star
id|productid
)paren
suffix:semicolon
DECL|member|acpi_madt_oem_check
r_int
(paren
op_star
id|acpi_madt_oem_check
)paren
(paren
r_char
op_star
id|oem_id
comma
r_char
op_star
id|oem_table_id
)paren
suffix:semicolon
DECL|member|get_apic_id
r_int
(paren
op_star
id|get_apic_id
)paren
(paren
r_int
r_int
id|x
)paren
suffix:semicolon
DECL|member|apic_id_mask
r_int
r_int
id|apic_id_mask
suffix:semicolon
DECL|member|cpu_mask_to_apicid
r_int
r_int
(paren
op_star
id|cpu_mask_to_apicid
)paren
(paren
id|cpumask_const_t
id|cpumask
)paren
suffix:semicolon
multiline_comment|/* ipi */
DECL|member|send_IPI_mask
r_void
(paren
op_star
id|send_IPI_mask
)paren
(paren
id|cpumask_t
id|mask
comma
r_int
id|vector
)paren
suffix:semicolon
DECL|member|send_IPI_allbutself
r_void
(paren
op_star
id|send_IPI_allbutself
)paren
(paren
r_int
id|vector
)paren
suffix:semicolon
DECL|member|send_IPI_all
r_void
(paren
op_star
id|send_IPI_all
)paren
(paren
r_int
id|vector
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|APICFUNC
mdefine_line|#define APICFUNC(x) .x = x
DECL|macro|APIC_INIT
mdefine_line|#define APIC_INIT(aname, aprobe) { &bslash;&n;&t;.name = aname, &bslash;&n;&t;.probe = aprobe, &bslash;&n;&t;.int_delivery_mode = INT_DELIVERY_MODE, &bslash;&n;&t;.int_dest_mode = INT_DEST_MODE, &bslash;&n;&t;.apic_broadcast_id = APIC_BROADCAST_ID, &bslash;&n;&t;.no_balance_irq = NO_BALANCE_IRQ, &bslash;&n;&t;.no_ioapic_check = NO_IOAPIC_CHECK, &bslash;&n;&t;APICFUNC(apic_id_registered), &bslash;&n;&t;APICFUNC(target_cpus), &bslash;&n;&t;APICFUNC(check_apicid_used), &bslash;&n;&t;APICFUNC(check_apicid_present), &bslash;&n;&t;APICFUNC(init_apic_ldr), &bslash;&n;&t;APICFUNC(ioapic_phys_id_map), &bslash;&n;&t;APICFUNC(clustered_apic_check), &bslash;&n;&t;APICFUNC(multi_timer_check), &bslash;&n;&t;APICFUNC(apicid_to_node), &bslash;&n;&t;APICFUNC(cpu_to_logical_apicid), &bslash;&n;&t;APICFUNC(cpu_present_to_apicid), &bslash;&n;&t;APICFUNC(apicid_to_cpu_present), &bslash;&n;&t;APICFUNC(mpc_apic_id), &bslash;&n;&t;APICFUNC(setup_portio_remap), &bslash;&n;&t;APICFUNC(check_phys_apicid_present), &bslash;&n;&t;APICFUNC(mpc_oem_bus_info), &bslash;&n;&t;APICFUNC(mpc_oem_pci_bus), &bslash;&n;&t;APICFUNC(mps_oem_check), &bslash;&n;&t;APICFUNC(get_apic_id), &bslash;&n;&t;.apic_id_mask = APIC_ID_MASK, &bslash;&n;&t;APICFUNC(cpu_mask_to_apicid), &bslash;&n;&t;APICFUNC(acpi_madt_oem_check), &bslash;&n;&t;APICFUNC(send_IPI_mask), &bslash;&n;&t;APICFUNC(send_IPI_allbutself), &bslash;&n;&t;APICFUNC(send_IPI_all), &bslash;&n;&t;APICFUNC(enable_apic_mode), &bslash;&n;&t;APICFUNC(phys_pkg_id), &bslash;&n;&t;}
r_extern
r_struct
id|genapic
op_star
id|genapic
suffix:semicolon
macro_line|#endif
eof
