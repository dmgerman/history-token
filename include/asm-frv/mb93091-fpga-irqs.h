multiline_comment|/* mb93091-fpga-irqs.h: MB93091 CPU board FPGA IRQs&n; *&n; * Copyright (C) 2004 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _ASM_MB93091_FPGA_IRQS_H
DECL|macro|_ASM_MB93091_FPGA_IRQS_H
mdefine_line|#define _ASM_MB93091_FPGA_IRQS_H
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;asm/irq-routing.h&gt;
DECL|macro|IRQ_BASE_FPGA
mdefine_line|#define IRQ_BASE_FPGA&t;&t;(NR_IRQ_ACTIONS_PER_GROUP * 1)
multiline_comment|/* IRQ IDs presented to drivers */
r_enum
(brace
DECL|enumerator|IRQ_FPGA__UNUSED
id|IRQ_FPGA__UNUSED
op_assign
id|IRQ_BASE_FPGA
comma
DECL|enumerator|IRQ_FPGA_SYSINT_BUS_EXPANSION_1
id|IRQ_FPGA_SYSINT_BUS_EXPANSION_1
comma
DECL|enumerator|IRQ_FPGA_SL_BUS_EXPANSION_2
id|IRQ_FPGA_SL_BUS_EXPANSION_2
comma
DECL|enumerator|IRQ_FPGA_PCI_INTD
id|IRQ_FPGA_PCI_INTD
comma
DECL|enumerator|IRQ_FPGA_PCI_INTC
id|IRQ_FPGA_PCI_INTC
comma
DECL|enumerator|IRQ_FPGA_PCI_INTB
id|IRQ_FPGA_PCI_INTB
comma
DECL|enumerator|IRQ_FPGA_PCI_INTA
id|IRQ_FPGA_PCI_INTA
comma
DECL|enumerator|IRQ_FPGA_SL_BUS_EXPANSION_7
id|IRQ_FPGA_SL_BUS_EXPANSION_7
comma
DECL|enumerator|IRQ_FPGA_SYSINT_BUS_EXPANSION_8
id|IRQ_FPGA_SYSINT_BUS_EXPANSION_8
comma
DECL|enumerator|IRQ_FPGA_SL_BUS_EXPANSION_9
id|IRQ_FPGA_SL_BUS_EXPANSION_9
comma
DECL|enumerator|IRQ_FPGA_MB86943_PCI_INTA
id|IRQ_FPGA_MB86943_PCI_INTA
comma
DECL|enumerator|IRQ_FPGA_MB86943_SLBUS_SIDE
id|IRQ_FPGA_MB86943_SLBUS_SIDE
comma
DECL|enumerator|IRQ_FPGA_RTL8029_INTA
id|IRQ_FPGA_RTL8029_INTA
comma
DECL|enumerator|IRQ_FPGA_SYSINT_BUS_EXPANSION_13
id|IRQ_FPGA_SYSINT_BUS_EXPANSION_13
comma
DECL|enumerator|IRQ_FPGA_SL_BUS_EXPANSION_14
id|IRQ_FPGA_SL_BUS_EXPANSION_14
comma
DECL|enumerator|IRQ_FPGA_NMI
id|IRQ_FPGA_NMI
comma
)brace
suffix:semicolon
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif /* _ASM_MB93091_FPGA_IRQS_H */
eof
