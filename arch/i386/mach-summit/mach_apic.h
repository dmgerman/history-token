macro_line|#ifndef __ASM_MACH_APIC_H
DECL|macro|__ASM_MACH_APIC_H
mdefine_line|#define __ASM_MACH_APIC_H
r_extern
r_int
id|x86_summit
suffix:semicolon
DECL|macro|XAPIC_DEST_CPUS_MASK
mdefine_line|#define XAPIC_DEST_CPUS_MASK    0x0Fu
DECL|macro|XAPIC_DEST_CLUSTER_MASK
mdefine_line|#define XAPIC_DEST_CLUSTER_MASK 0xF0u
DECL|macro|xapic_phys_to_log_apicid
mdefine_line|#define xapic_phys_to_log_apicid(phys_apic) ( (1ul &lt;&lt; ((phys_apic) &amp; 0x3)) |&bslash;&n;&t;&t;((phys_apic) &amp; XAPIC_DEST_CLUSTER_MASK) )
DECL|function|calculate_ldr
r_static
r_inline
r_int
r_int
id|calculate_ldr
c_func
(paren
r_int
r_int
id|old
)paren
(brace
r_int
r_int
id|id
suffix:semicolon
r_if
c_cond
(paren
id|x86_summit
)paren
id|id
op_assign
id|xapic_phys_to_log_apicid
c_func
(paren
id|hard_smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
r_else
id|id
op_assign
l_int|1UL
op_lshift
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
r_return
(paren
(paren
id|old
op_amp
op_complement
id|APIC_LDR_MASK
)paren
op_or
id|SET_APIC_LOGICAL_ID
c_func
(paren
id|id
)paren
)paren
suffix:semicolon
)brace
DECL|macro|APIC_DFR_VALUE
mdefine_line|#define APIC_DFR_VALUE&t;(x86_summit ? APIC_DFR_CLUSTER : APIC_DFR_FLAT)
DECL|macro|TARGET_CPUS
mdefine_line|#define TARGET_CPUS&t;(x86_summit ? XAPIC_DEST_CPUS_MASK : cpu_online_map)
DECL|macro|APIC_BROADCAST_ID
mdefine_line|#define APIC_BROADCAST_ID     (x86_summit ? 0xFF : 0x0F)
DECL|macro|check_apicid_used
mdefine_line|#define check_apicid_used(bitmap, apicid) (0)
macro_line|#endif /* __ASM_MACH_APIC_H */
eof
