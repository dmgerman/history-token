macro_line|#ifndef __ASM_MACH_APIC_H
DECL|macro|__ASM_MACH_APIC_H
mdefine_line|#define __ASM_MACH_APIC_H
macro_line|#include &lt;asm/genapic.h&gt;
DECL|macro|esr_disable
mdefine_line|#define esr_disable (genapic-&gt;esr_disable)
DECL|macro|NO_BALANCE_IRQ
mdefine_line|#define NO_BALANCE_IRQ (genapic-&gt;no_balance_irq)
DECL|macro|APIC_BROADCAST_ID
mdefine_line|#define APIC_BROADCAST_ID (genapic-&gt;apic_broadcast_id)
DECL|macro|INT_DELIVERY_MODE
mdefine_line|#define INT_DELIVERY_MODE (genapic-&gt;int_delivery_mode)
DECL|macro|INT_DEST_MODE
mdefine_line|#define INT_DEST_MODE (genapic-&gt;int_dest_mode)
DECL|macro|TARGET_CPUS
mdefine_line|#define TARGET_CPUS&t;  (genapic-&gt;target_cpus())
DECL|macro|apic_id_registered
mdefine_line|#define apic_id_registered (genapic-&gt;apic_id_registered)
DECL|macro|apic_id_registered
mdefine_line|#define apic_id_registered (genapic-&gt;apic_id_registered)
DECL|macro|init_apic_ldr
mdefine_line|#define init_apic_ldr (genapic-&gt;init_apic_ldr)
DECL|macro|ioapic_phys_id_map
mdefine_line|#define ioapic_phys_id_map (genapic-&gt;ioapic_phys_id_map)
DECL|macro|clustered_apic_check
mdefine_line|#define clustered_apic_check (genapic-&gt;clustered_apic_check) 
DECL|macro|multi_timer_check
mdefine_line|#define multi_timer_check (genapic-&gt;multi_timer_check)
DECL|macro|apicid_to_node
mdefine_line|#define apicid_to_node (genapic-&gt;apicid_to_node)
DECL|macro|cpu_to_logical_apicid
mdefine_line|#define cpu_to_logical_apicid (genapic-&gt;cpu_to_logical_apicid) 
DECL|macro|cpu_present_to_apicid
mdefine_line|#define cpu_present_to_apicid (genapic-&gt;cpu_present_to_apicid)
DECL|macro|apicid_to_cpu_present
mdefine_line|#define apicid_to_cpu_present (genapic-&gt;apicid_to_cpu_present)
DECL|macro|mpc_apic_id
mdefine_line|#define mpc_apic_id (genapic-&gt;mpc_apic_id) 
DECL|macro|setup_portio_remap
mdefine_line|#define setup_portio_remap (genapic-&gt;setup_portio_remap)
DECL|macro|check_apicid_present
mdefine_line|#define check_apicid_present (genapic-&gt;check_apicid_present)
DECL|macro|check_phys_apicid_present
mdefine_line|#define check_phys_apicid_present (genapic-&gt;check_phys_apicid_present)
DECL|macro|check_apicid_used
mdefine_line|#define check_apicid_used (genapic-&gt;check_apicid_used)
DECL|macro|cpu_mask_to_apicid
mdefine_line|#define cpu_mask_to_apicid (genapic-&gt;cpu_mask_to_apicid)
macro_line|#endif /* __ASM_MACH_APIC_H */
eof
