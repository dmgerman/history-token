multiline_comment|/*&n; * linux/include/asm-arm/arch-tbox/irqs.h&n; *&n; * Copyright (C) 1998, 2000 Philip Blundell&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
DECL|macro|IRQ_MPEGDMA
mdefine_line|#define IRQ_MPEGDMA&t;&t;0
DECL|macro|IRQ_ASHTX
mdefine_line|#define IRQ_ASHTX&t;&t;1
DECL|macro|IRQ_ASHRX
mdefine_line|#define IRQ_ASHRX&t;&t;2
DECL|macro|IRQ_VSYNC
mdefine_line|#define IRQ_VSYNC&t;&t;3
DECL|macro|IRQ_HSYNC
mdefine_line|#define IRQ_HSYNC&t;&t;4
DECL|macro|IRQ_MPEG
mdefine_line|#define IRQ_MPEG&t;&t;5
DECL|macro|IRQ_UART2
mdefine_line|#define IRQ_UART2&t;&t;6
DECL|macro|IRQ_UART1
mdefine_line|#define IRQ_UART1&t;&t;7
DECL|macro|IRQ_ETHERNET
mdefine_line|#define IRQ_ETHERNET&t;&t;8
DECL|macro|IRQ_TIMER
mdefine_line|#define IRQ_TIMER&t;&t;9
DECL|macro|IRQ_AUDIODMA
mdefine_line|#define IRQ_AUDIODMA&t;&t;10
multiline_comment|/* bit 11 used for video field ident */
DECL|macro|IRQ_EXPMODCS0
mdefine_line|#define IRQ_EXPMODCS0&t;&t;12
DECL|macro|IRQ_EXPMODCS1
mdefine_line|#define IRQ_EXPMODCS1&t;&t;13
DECL|macro|irq_cannonicalize
mdefine_line|#define irq_cannonicalize(i)&t;(i)
eof
