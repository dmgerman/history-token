multiline_comment|/* mb93093-fpga-irqs.h: MB93093 CPU board FPGA IRQs&n; *&n; * Copyright (C) 2004 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _ASM_MB93093_FPGA_IRQS_H
DECL|macro|_ASM_MB93093_FPGA_IRQS_H
mdefine_line|#define _ASM_MB93093_FPGA_IRQS_H
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;asm/irq-routing.h&gt;
DECL|macro|IRQ_BASE_FPGA
mdefine_line|#define IRQ_BASE_FPGA&t;&t;(NR_IRQ_ACTIONS_PER_GROUP * 1)
multiline_comment|/* IRQ IDs presented to drivers */
r_enum
(brace
DECL|enumerator|IRQ_FPGA_PUSH_BUTTON_SW1_5
id|IRQ_FPGA_PUSH_BUTTON_SW1_5
op_assign
id|IRQ_BASE_FPGA
op_plus
l_int|8
comma
DECL|enumerator|IRQ_FPGA_ROCKER_C_SW8
id|IRQ_FPGA_ROCKER_C_SW8
op_assign
id|IRQ_BASE_FPGA
op_plus
l_int|9
comma
DECL|enumerator|IRQ_FPGA_ROCKER_C_SW9
id|IRQ_FPGA_ROCKER_C_SW9
op_assign
id|IRQ_BASE_FPGA
op_plus
l_int|10
comma
)brace
suffix:semicolon
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif /* _ASM_MB93093_FPGA_IRQS_H */
eof
