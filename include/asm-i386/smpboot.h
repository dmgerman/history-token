macro_line|#ifndef __ASM_SMPBOOT_H
DECL|macro|__ASM_SMPBOOT_H
mdefine_line|#define __ASM_SMPBOOT_H
macro_line|#ifndef clustered_apic_mode
macro_line|#ifdef CONFIG_MULTIQUAD
DECL|macro|clustered_apic_mode
mdefine_line|#define clustered_apic_mode (1)
macro_line|#else /* !CONFIG_MULTIQUAD */
DECL|macro|clustered_apic_mode
mdefine_line|#define clustered_apic_mode (0)
macro_line|#endif /* CONFIG_MULTIQUAD */
macro_line|#endif 
macro_line|#ifdef CONFIG_MULTIQUAD
DECL|macro|TRAMPOLINE_LOW
mdefine_line|#define TRAMPOLINE_LOW phys_to_virt(0x8)
DECL|macro|TRAMPOLINE_HIGH
mdefine_line|#define TRAMPOLINE_HIGH phys_to_virt(0xa)
macro_line|#else /* !CONFIG_MULTIQUAD */
DECL|macro|TRAMPOLINE_LOW
mdefine_line|#define TRAMPOLINE_LOW phys_to_virt(0x467)
DECL|macro|TRAMPOLINE_HIGH
mdefine_line|#define TRAMPOLINE_HIGH phys_to_virt(0x469)
macro_line|#endif /* CONFIG_MULTIQUAD */
macro_line|#ifdef CONFIG_MULTIQUAD
DECL|macro|boot_cpu_apicid
mdefine_line|#define boot_cpu_apicid boot_cpu_logical_apicid
macro_line|#else /* !CONFIG_MULTIQUAD */
DECL|macro|boot_cpu_apicid
mdefine_line|#define boot_cpu_apicid boot_cpu_physical_apicid
macro_line|#endif /* CONFIG_MULTIQUAD */
multiline_comment|/*&n; * How to map from the cpu_present_map&n; */
macro_line|#ifdef CONFIG_MULTIQUAD
DECL|macro|cpu_present_to_apicid
mdefine_line|#define cpu_present_to_apicid(mps_cpu) ( ((mps_cpu/4)*16) + (1&lt;&lt;(mps_cpu%4)) )
macro_line|#else /* !CONFIG_MULTIQUAD */
DECL|macro|cpu_present_to_apicid
mdefine_line|#define cpu_present_to_apicid(apicid) (apicid)
macro_line|#endif /* CONFIG_MULTIQUAD */
multiline_comment|/*&n; * Mappings between logical cpu number and logical / physical apicid&n; * The first four macros are trivial, but it keeps the abstraction consistent&n; */
r_extern
r_volatile
r_int
id|logical_apicid_2_cpu
(braket
)braket
suffix:semicolon
r_extern
r_volatile
r_int
id|cpu_2_logical_apicid
(braket
)braket
suffix:semicolon
r_extern
r_volatile
r_int
id|physical_apicid_2_cpu
(braket
)braket
suffix:semicolon
r_extern
r_volatile
r_int
id|cpu_2_physical_apicid
(braket
)braket
suffix:semicolon
DECL|macro|logical_apicid_to_cpu
mdefine_line|#define logical_apicid_to_cpu(apicid) logical_apicid_2_cpu[apicid]
DECL|macro|cpu_to_logical_apicid
mdefine_line|#define cpu_to_logical_apicid(cpu) cpu_2_logical_apicid[cpu]
DECL|macro|physical_apicid_to_cpu
mdefine_line|#define physical_apicid_to_cpu(apicid) physical_apicid_2_cpu[apicid]
DECL|macro|cpu_to_physical_apicid
mdefine_line|#define cpu_to_physical_apicid(cpu) cpu_2_physical_apicid[cpu]
macro_line|#ifdef CONFIG_MULTIQUAD&t;&t;&t;/* use logical IDs to bootstrap */
DECL|macro|boot_apicid_to_cpu
mdefine_line|#define boot_apicid_to_cpu(apicid) logical_apicid_2_cpu[apicid]
DECL|macro|cpu_to_boot_apicid
mdefine_line|#define cpu_to_boot_apicid(cpu) cpu_2_logical_apicid[cpu]
macro_line|#else /* !CONFIG_MULTIQUAD */&t;&t;/* use physical IDs to bootstrap */
DECL|macro|boot_apicid_to_cpu
mdefine_line|#define boot_apicid_to_cpu(apicid) physical_apicid_2_cpu[apicid]
DECL|macro|cpu_to_boot_apicid
mdefine_line|#define cpu_to_boot_apicid(cpu) cpu_2_physical_apicid[cpu]
macro_line|#endif /* CONFIG_MULTIQUAD */
macro_line|#ifdef CONFIG_MULTIQUAD
macro_line|#else /* !CONFIG_MULTIQUAD */
macro_line|#endif /* CONFIG_MULTIQUAD */
macro_line|#endif
eof
