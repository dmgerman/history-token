multiline_comment|/*&n; * Copyright (C) 2003-2004 Intel&n; * Copyright (C) Tom Long Nguyen (tom.l.nguyen@intel.com)&n; */
macro_line|#ifndef ASM_MSI_H
DECL|macro|ASM_MSI_H
mdefine_line|#define ASM_MSI_H
DECL|macro|NR_VECTORS
mdefine_line|#define NR_VECTORS&t;&t;NR_IRQS
DECL|macro|FIRST_DEVICE_VECTOR
mdefine_line|#define FIRST_DEVICE_VECTOR &t;IA64_FIRST_DEVICE_VECTOR
DECL|macro|LAST_DEVICE_VECTOR
mdefine_line|#define LAST_DEVICE_VECTOR&t;IA64_LAST_DEVICE_VECTOR
DECL|function|set_intr_gate
r_static
r_inline
r_void
id|set_intr_gate
(paren
r_int
id|nr
comma
r_void
op_star
id|func
)paren
(brace
)brace
DECL|macro|IO_APIC_VECTOR
mdefine_line|#define IO_APIC_VECTOR(irq)&t;(irq)
DECL|macro|ack_APIC_irq
mdefine_line|#define ack_APIC_irq&t;&t;ia64_eoi
DECL|macro|cpu_mask_to_apicid
mdefine_line|#define cpu_mask_to_apicid(mask) cpu_physical_id(first_cpu(mask))
DECL|macro|MSI_DEST_MODE
mdefine_line|#define MSI_DEST_MODE&t;&t;MSI_PHYSICAL_MODE
DECL|macro|MSI_TARGET_CPU
mdefine_line|#define MSI_TARGET_CPU&t;((ia64_getreg(_IA64_REG_CR_LID) &gt;&gt; 16) &amp; 0xffff)
DECL|macro|MSI_TARGET_CPU_SHIFT
mdefine_line|#define MSI_TARGET_CPU_SHIFT&t;4
macro_line|#endif /* ASM_MSI_H */
eof
