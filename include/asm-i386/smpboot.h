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
macro_line|#endif
eof
