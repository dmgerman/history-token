macro_line|#ifndef __ASM_MACH_APIC_H
DECL|macro|__ASM_MACH_APIC_H
mdefine_line|#define __ASM_MACH_APIC_H
macro_line|#include &lt;mach_apicdef.h&gt;
DECL|macro|APIC_DFR_VALUE
mdefine_line|#define APIC_DFR_VALUE&t;(APIC_DFR_FLAT)
DECL|macro|no_balance_irq
mdefine_line|#define no_balance_irq (0)
DECL|macro|esr_disable
mdefine_line|#define esr_disable (0)
DECL|macro|NO_IOAPIC_CHECK
mdefine_line|#define NO_IOAPIC_CHECK (0)
DECL|macro|INT_DELIVERY_MODE
mdefine_line|#define INT_DELIVERY_MODE dest_LowestPrio
DECL|macro|INT_DEST_MODE
mdefine_line|#define INT_DEST_MODE 1     /* logical delivery broadcast to all procs */
macro_line|#ifdef CONFIG_SMP
DECL|macro|TARGET_CPUS
mdefine_line|#define TARGET_CPUS cpu_online_map
macro_line|#else
DECL|macro|TARGET_CPUS
mdefine_line|#define TARGET_CPUS cpumask_of_cpu(0)
macro_line|#endif
DECL|macro|check_apicid_used
mdefine_line|#define check_apicid_used(bitmap, apicid)&t;physid_isset(apicid, bitmap)
DECL|macro|check_apicid_present
mdefine_line|#define check_apicid_present(bit)&t;&t;physid_isset(bit, phys_cpu_present_map)
DECL|function|apic_id_registered
r_static
r_inline
r_int
id|apic_id_registered
c_func
(paren
r_void
)paren
(brace
r_return
id|physid_isset
c_func
(paren
id|GET_APIC_ID
c_func
(paren
id|apic_read
c_func
(paren
id|APIC_ID
)paren
)paren
comma
id|phys_cpu_present_map
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Set up the logical destination ID.&n; *&n; * Intel recommends to set DFR, LDR and TPR before enabling&n; * an APIC.  See e.g. &quot;AP-388 82489DX User&squot;s Manual&quot; (Intel&n; * document number 292116).  So here it goes...&n; */
DECL|function|init_apic_ldr
r_static
r_inline
r_void
id|init_apic_ldr
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|val
suffix:semicolon
id|apic_write_around
c_func
(paren
id|APIC_DFR
comma
id|APIC_DFR_VALUE
)paren
suffix:semicolon
id|val
op_assign
id|apic_read
c_func
(paren
id|APIC_LDR
)paren
op_amp
op_complement
id|APIC_LDR_MASK
suffix:semicolon
id|val
op_or_assign
id|SET_APIC_LOGICAL_ID
c_func
(paren
l_int|1UL
op_lshift
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
id|apic_write_around
c_func
(paren
id|APIC_LDR
comma
id|val
)paren
suffix:semicolon
)brace
DECL|function|summit_check
r_static
r_inline
r_void
id|summit_check
c_func
(paren
r_char
op_star
id|oem
comma
r_char
op_star
id|productid
)paren
(brace
)brace
DECL|function|clustered_apic_check
r_static
r_inline
r_void
id|clustered_apic_check
c_func
(paren
r_void
)paren
(brace
)brace
multiline_comment|/* Mapping from cpu number to logical apicid */
DECL|function|cpu_to_logical_apicid
r_static
r_inline
r_int
id|cpu_to_logical_apicid
c_func
(paren
r_int
id|cpu
)paren
(brace
r_return
l_int|1
op_lshift
id|cpu
suffix:semicolon
)brace
DECL|function|cpu_present_to_apicid
r_static
r_inline
r_int
id|cpu_present_to_apicid
c_func
(paren
r_int
id|mps_cpu
)paren
(brace
r_if
c_cond
(paren
id|mps_cpu
OL
id|get_physical_broadcast
c_func
(paren
)paren
)paren
r_return
id|mps_cpu
suffix:semicolon
r_else
r_return
id|BAD_APICID
suffix:semicolon
)brace
DECL|function|apicid_to_cpu_present
r_static
r_inline
id|physid_mask_t
id|apicid_to_cpu_present
c_func
(paren
r_int
id|apicid
)paren
(brace
r_return
id|physid_mask_of_physid
c_func
(paren
id|apicid
)paren
suffix:semicolon
)brace
DECL|macro|WAKE_SECONDARY_VIA_INIT
mdefine_line|#define WAKE_SECONDARY_VIA_INIT
DECL|function|setup_portio_remap
r_static
r_inline
r_void
id|setup_portio_remap
c_func
(paren
r_void
)paren
(brace
)brace
DECL|function|enable_apic_mode
r_static
r_inline
r_void
id|enable_apic_mode
c_func
(paren
r_void
)paren
(brace
)brace
DECL|function|check_phys_apicid_present
r_static
r_inline
r_int
id|check_phys_apicid_present
c_func
(paren
r_int
id|boot_cpu_physical_apicid
)paren
(brace
r_return
id|physid_isset
c_func
(paren
id|boot_cpu_physical_apicid
comma
id|phys_cpu_present_map
)paren
suffix:semicolon
)brace
DECL|function|cpu_mask_to_apicid
r_static
r_inline
r_int
r_int
id|cpu_mask_to_apicid
c_func
(paren
id|cpumask_t
id|cpumask
)paren
(brace
r_return
id|cpus_addr
c_func
(paren
id|cpumask
)paren
(braket
l_int|0
)braket
suffix:semicolon
)brace
DECL|function|phys_pkg_id
r_static
r_inline
id|u32
id|phys_pkg_id
c_func
(paren
id|u32
id|cpuid_apic
comma
r_int
id|index_msb
)paren
(brace
r_return
id|cpuid_apic
op_rshift
id|index_msb
suffix:semicolon
)brace
macro_line|#endif /* __ASM_MACH_APIC_H */
eof
