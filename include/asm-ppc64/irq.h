macro_line|#ifdef __KERNEL__
macro_line|#ifndef _ASM_IRQ_H
DECL|macro|_ASM_IRQ_H
mdefine_line|#define _ASM_IRQ_H
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;asm/atomic.h&gt;
r_extern
r_void
id|disable_irq
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|disable_irq_nosync
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|enable_irq
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * this is the maximum number of virtual irqs we will use.&n; */
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS&t;&t;&t;512
DECL|macro|NUM_8259_INTERRUPTS
mdefine_line|#define NUM_8259_INTERRUPTS&t;16
multiline_comment|/* Interrupt numbers are virtual in case they are sparsely&n; * distributed by the hardware.&n; */
DECL|macro|NR_HW_IRQS
mdefine_line|#define NR_HW_IRQS&t;&t;8192
r_extern
r_int
r_int
id|real_irq_to_virt_map
(braket
id|NR_HW_IRQS
)braket
suffix:semicolon
r_extern
r_int
r_int
id|virt_irq_to_real_map
(braket
id|NR_IRQS
)braket
suffix:semicolon
multiline_comment|/* Create a mapping for a real_irq if it doesn&squot;t already exist.&n; * Return the virtual irq as a convenience.&n; */
r_int
r_int
id|virt_irq_create_mapping
c_func
(paren
r_int
r_int
id|real_irq
)paren
suffix:semicolon
multiline_comment|/* These funcs map irqs between real and virtual */
DECL|function|real_irq_to_virt
r_static
r_inline
r_int
r_int
id|real_irq_to_virt
c_func
(paren
r_int
r_int
id|real_irq
)paren
(brace
r_return
id|real_irq_to_virt_map
(braket
id|real_irq
)braket
suffix:semicolon
)brace
DECL|function|virt_irq_to_real
r_static
r_inline
r_int
r_int
id|virt_irq_to_real
c_func
(paren
r_int
r_int
id|virt_irq
)paren
(brace
r_return
id|virt_irq_to_real_map
(braket
id|virt_irq
)braket
suffix:semicolon
)brace
multiline_comment|/*&n; * This gets called from serial.c, which is now used on&n; * powermacs as well as prep/chrp boxes.&n; * Prep and chrp both have cascaded 8259 PICs.&n; */
DECL|function|irq_cannonicalize
r_static
id|__inline__
r_int
id|irq_cannonicalize
c_func
(paren
r_int
id|irq
)paren
(brace
r_return
id|irq
suffix:semicolon
)brace
macro_line|#endif /* _ASM_IRQ_H */
macro_line|#endif /* __KERNEL__ */
eof
