multiline_comment|/*&n; * linux/include/asm-arm/arch-nexuspci/irqs.h&n; *&n; * Copyright (C) 1997, 1998, 2000 Philip Blundell&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
multiline_comment|/*&n; * The hardware is capable of routing any interrupt source (except the&n; * DUART) to either IRQ or FIQ.  We ignore FIQ and use IRQ exclusively&n; * for simplicity.  &n; */
DECL|macro|IRQ_DUART
mdefine_line|#define IRQ_DUART&t;&t;0
DECL|macro|IRQ_PLX
mdefine_line|#define IRQ_PLX &t;&t;1
DECL|macro|IRQ_PCI_D
mdefine_line|#define IRQ_PCI_D&t;&t;2
DECL|macro|IRQ_PCI_C
mdefine_line|#define IRQ_PCI_C&t;&t;3
DECL|macro|IRQ_PCI_B
mdefine_line|#define IRQ_PCI_B&t;&t;4
DECL|macro|IRQ_PCI_A
mdefine_line|#define IRQ_PCI_A&t;        5
DECL|macro|IRQ_SYSERR
mdefine_line|#define IRQ_SYSERR&t;&t;6&t;/* only from IOSLAVE rev B */
DECL|macro|FIRST_IRQ
mdefine_line|#define FIRST_IRQ&t;&t;IRQ_DUART
DECL|macro|LAST_IRQ
mdefine_line|#define LAST_IRQ&t;&t;IRQ_SYSERR
multiline_comment|/* timer is part of the DUART */
DECL|macro|IRQ_TIMER
mdefine_line|#define IRQ_TIMER&t;&t;IRQ_DUART
DECL|macro|irq_cannonicalize
mdefine_line|#define irq_cannonicalize(i)&t;(i)
eof
