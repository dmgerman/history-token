multiline_comment|/*&n; * linux/include/asm-arm/arch-80200fcc/irqs.h&n; *&n; * Author:&t;Deepak Saxena &lt;dsaxena@mvista.com&gt;&n; * Copyright:&t;(C) 2001 MontaVista Software Inc.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
DECL|macro|IRQ_XS80200_BCU
mdefine_line|#define IRQ_XS80200_BCU&t;&t;0&t;/* Bus Control Unit */
DECL|macro|IRQ_XS80200_PMU
mdefine_line|#define IRQ_XS80200_PMU&t;&t;1&t;/* Performance Monitoring Unit */
DECL|macro|IRQ_XS80200_EXTIRQ
mdefine_line|#define IRQ_XS80200_EXTIRQ&t;2&t;/* external IRQ signal */
DECL|macro|IRQ_XS80200_EXTFIQ
mdefine_line|#define IRQ_XS80200_EXTFIQ&t;3&t;/* external IRQ signal */
DECL|macro|NR_XS80200_IRQS
mdefine_line|#define NR_XS80200_IRQS&t;&t;4
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS&t;&t;&t;NR_XS80200_IRQS
DECL|macro|IRQ_XSCALE_PMU
mdefine_line|#define&t;IRQ_XSCALE_PMU&t;&t;IRQ_XS80200_PMU
eof
