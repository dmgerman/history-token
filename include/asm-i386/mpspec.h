macro_line|#ifndef __ASM_MPSPEC_H
DECL|macro|__ASM_MPSPEC_H
mdefine_line|#define __ASM_MPSPEC_H
macro_line|#include &lt;linux/cpumask.h&gt;
macro_line|#include &lt;asm/mpspec_def.h&gt;
macro_line|#include &lt;mach_mpspec.h&gt;
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
macro_line|#ifdef CONFIG_X86_SUMMIT
r_extern
r_void
id|setup_summit
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ACPI_BOOT
r_extern
r_void
id|mp_register_lapic
(paren
id|u8
id|id
comma
id|u8
id|enabled
)paren
suffix:semicolon
r_extern
r_void
id|mp_register_lapic_address
(paren
id|u64
id|address
)paren
suffix:semicolon
r_extern
r_void
id|mp_register_ioapic
(paren
id|u8
id|id
comma
id|u32
id|address
comma
id|u32
id|irq_base
)paren
suffix:semicolon
r_extern
r_void
id|mp_override_legacy_irq
(paren
id|u8
id|bus_irq
comma
id|u8
id|polarity
comma
id|u8
id|trigger
comma
id|u32
id|global_irq
)paren
suffix:semicolon
r_extern
r_void
id|mp_config_acpi_legacy_irqs
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|mp_config_ioapic_for_sci
c_func
(paren
r_int
id|irq
)paren
suffix:semicolon
r_extern
r_void
id|mp_parse_prt
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /*CONFIG_ACPI_BOOT*/
DECL|macro|PHYSID_ARRAY_SIZE
mdefine_line|#define PHYSID_ARRAY_SIZE&t;BITS_TO_LONGS(MAX_APICS)
DECL|struct|physid_mask
r_struct
id|physid_mask
(brace
DECL|member|mask
r_int
r_int
id|mask
(braket
id|PHYSID_ARRAY_SIZE
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|physid_mask_t
r_typedef
r_struct
id|physid_mask
id|physid_mask_t
suffix:semicolon
DECL|macro|physid_set
mdefine_line|#define physid_set(physid, map)&t;&t;&t;set_bit(physid, (map).mask)
DECL|macro|physid_clear
mdefine_line|#define physid_clear(physid, map)&t;&t;clear_bit(physid, (map).mask)
DECL|macro|physid_isset
mdefine_line|#define physid_isset(physid, map)&t;&t;test_bit(physid, (map).mask)
DECL|macro|physid_test_and_set
mdefine_line|#define physid_test_and_set(physid, map)&t;test_and_set_bit(physid, (map).mask)
DECL|macro|physids_and
mdefine_line|#define physids_and(dst, src1, src2)&t;&t;bitmap_and((dst).mask, (src1).mask, (src2).mask, MAX_APICS)
DECL|macro|physids_or
mdefine_line|#define physids_or(dst, src1, src2)&t;&t;bitmap_or((dst).mask, (src1).mask, (src2).mask, MAX_APICS)
DECL|macro|physids_clear
mdefine_line|#define physids_clear(map)&t;&t;&t;bitmap_clear((map).mask, MAX_APICS)
DECL|macro|physids_complement
mdefine_line|#define physids_complement(map)&t;&t;&t;bitmap_complement((map).mask, MAX_APICS)
DECL|macro|physids_empty
mdefine_line|#define physids_empty(map)&t;&t;&t;bitmap_empty((map).mask, MAX_APICS)
DECL|macro|physids_equal
mdefine_line|#define physids_equal(map1, map2)&t;&t;bitmap_equal((map1).mask, (map2).mask, MAX_APICS)
DECL|macro|physids_weight
mdefine_line|#define physids_weight(map)&t;&t;&t;bitmap_weight((map).mask, MAX_APICS)
DECL|macro|physids_shift_right
mdefine_line|#define physids_shift_right(d, s, n)&t;&t;bitmap_shift_right((d).mask, (s).mask, n, MAX_APICS)
DECL|macro|physids_shift_left
mdefine_line|#define physids_shift_left(d, s, n)&t;&t;bitmap_shift_left((d).mask, (s).mask, n, MAX_APICS)
DECL|macro|physids_coerce
mdefine_line|#define physids_coerce(map)&t;&t;&t;((map).mask[0])
DECL|macro|physids_promote
mdefine_line|#define physids_promote(physids)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;physid_mask_t __physid_mask = PHYSID_MASK_NONE;&t;&t;&t;&bslash;&n;&t;&t;__physid_mask.mask[0] = physids;&t;&t;&t;&t;&bslash;&n;&t;&t;__physid_mask;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;})
DECL|macro|physid_mask_of_physid
mdefine_line|#define physid_mask_of_physid(physid)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;physid_mask_t __physid_mask = PHYSID_MASK_NONE;&t;&t;&t;&bslash;&n;&t;&t;physid_set(physid, __physid_mask);&t;&t;&t;&t;&bslash;&n;&t;&t;__physid_mask;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;})
DECL|macro|PHYSID_MASK_ALL
mdefine_line|#define PHYSID_MASK_ALL&t;&t;{ {[0 ... PHYSID_ARRAY_SIZE-1] = ~0UL} }
DECL|macro|PHYSID_MASK_NONE
mdefine_line|#define PHYSID_MASK_NONE&t;{ {[0 ... PHYSID_ARRAY_SIZE-1] = 0UL} }
r_extern
id|physid_mask_t
id|phys_cpu_present_map
suffix:semicolon
macro_line|#endif
eof
