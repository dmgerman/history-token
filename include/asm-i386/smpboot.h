macro_line|#ifndef __ASM_SMPBOOT_H
DECL|macro|__ASM_SMPBOOT_H
mdefine_line|#define __ASM_SMPBOOT_H
macro_line|#ifndef clustered_apic_mode
macro_line|#ifdef CONFIG_CLUSTERED_APIC
DECL|macro|clustered_apic_mode
mdefine_line|#define clustered_apic_mode (1)
macro_line|#else /* !CONFIG_CLUSTERED_APIC */
DECL|macro|clustered_apic_mode
mdefine_line|#define clustered_apic_mode (0)
macro_line|#endif /* CONFIG_CLUSTERED_APIC */
macro_line|#endif 
macro_line|#ifdef CONFIG_CLUSTERED_APIC
DECL|macro|TRAMPOLINE_LOW
mdefine_line|#define TRAMPOLINE_LOW phys_to_virt(0x8)
DECL|macro|TRAMPOLINE_HIGH
mdefine_line|#define TRAMPOLINE_HIGH phys_to_virt(0xa)
macro_line|#else /* !CONFIG_CLUSTERED_APIC */
DECL|macro|TRAMPOLINE_LOW
mdefine_line|#define TRAMPOLINE_LOW phys_to_virt(0x467)
DECL|macro|TRAMPOLINE_HIGH
mdefine_line|#define TRAMPOLINE_HIGH phys_to_virt(0x469)
macro_line|#endif /* CONFIG_CLUSTERED_APIC */
macro_line|#ifdef CONFIG_CLUSTERED_APIC
DECL|macro|boot_cpu_apicid
mdefine_line|#define boot_cpu_apicid boot_cpu_logical_apicid
macro_line|#else /* !CONFIG_CLUSTERED_APIC */
DECL|macro|boot_cpu_apicid
mdefine_line|#define boot_cpu_apicid boot_cpu_physical_apicid
macro_line|#endif /* CONFIG_CLUSTERED_APIC */
macro_line|#endif
eof
