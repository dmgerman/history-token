multiline_comment|/* mb93493-irqs.h: MB93493 companion chip IRQs&n; *&n; * Copyright (C) 2004 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _ASM_MB93493_IRQS_H
DECL|macro|_ASM_MB93493_IRQS_H
mdefine_line|#define _ASM_MB93493_IRQS_H
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;asm/irq-routing.h&gt;
DECL|macro|IRQ_BASE_MB93493
mdefine_line|#define IRQ_BASE_MB93493&t;(NR_IRQ_ACTIONS_PER_GROUP * 2)
multiline_comment|/* IRQ IDs presented to drivers */
r_enum
(brace
DECL|enumerator|IRQ_MB93493_VDC
id|IRQ_MB93493_VDC
op_assign
id|IRQ_BASE_MB93493
op_plus
l_int|0
comma
DECL|enumerator|IRQ_MB93493_VCC
id|IRQ_MB93493_VCC
op_assign
id|IRQ_BASE_MB93493
op_plus
l_int|1
comma
DECL|enumerator|IRQ_MB93493_AUDIO_OUT
id|IRQ_MB93493_AUDIO_OUT
op_assign
id|IRQ_BASE_MB93493
op_plus
l_int|2
comma
DECL|enumerator|IRQ_MB93493_I2C_0
id|IRQ_MB93493_I2C_0
op_assign
id|IRQ_BASE_MB93493
op_plus
l_int|3
comma
DECL|enumerator|IRQ_MB93493_I2C_1
id|IRQ_MB93493_I2C_1
op_assign
id|IRQ_BASE_MB93493
op_plus
l_int|4
comma
DECL|enumerator|IRQ_MB93493_USB
id|IRQ_MB93493_USB
op_assign
id|IRQ_BASE_MB93493
op_plus
l_int|5
comma
DECL|enumerator|IRQ_MB93493_LOCAL_BUS
id|IRQ_MB93493_LOCAL_BUS
op_assign
id|IRQ_BASE_MB93493
op_plus
l_int|7
comma
DECL|enumerator|IRQ_MB93493_PCMCIA
id|IRQ_MB93493_PCMCIA
op_assign
id|IRQ_BASE_MB93493
op_plus
l_int|8
comma
DECL|enumerator|IRQ_MB93493_GPIO
id|IRQ_MB93493_GPIO
op_assign
id|IRQ_BASE_MB93493
op_plus
l_int|9
comma
DECL|enumerator|IRQ_MB93493_AUDIO_IN
id|IRQ_MB93493_AUDIO_IN
op_assign
id|IRQ_BASE_MB93493
op_plus
l_int|10
comma
)brace
suffix:semicolon
multiline_comment|/* IRQ multiplexor mappings */
DECL|macro|ROUTE_VIA_IRQ0
mdefine_line|#define ROUTE_VIA_IRQ0&t;0&t;/* route IRQ by way of CPU external IRQ 0 */
DECL|macro|ROUTE_VIA_IRQ1
mdefine_line|#define ROUTE_VIA_IRQ1&t;1&t;/* route IRQ by way of CPU external IRQ 1 */
DECL|macro|IRQ_MB93493_VDC_ROUTE
mdefine_line|#define IRQ_MB93493_VDC_ROUTE&t;&t;ROUTE_VIA_IRQ0
DECL|macro|IRQ_MB93493_VCC_ROUTE
mdefine_line|#define IRQ_MB93493_VCC_ROUTE&t;&t;ROUTE_VIA_IRQ1
DECL|macro|IRQ_MB93493_AUDIO_OUT_ROUTE
mdefine_line|#define IRQ_MB93493_AUDIO_OUT_ROUTE&t;ROUTE_VIA_IRQ1
DECL|macro|IRQ_MB93493_I2C_0_ROUTE
mdefine_line|#define IRQ_MB93493_I2C_0_ROUTE&t;&t;ROUTE_VIA_IRQ1
DECL|macro|IRQ_MB93493_I2C_1_ROUTE
mdefine_line|#define IRQ_MB93493_I2C_1_ROUTE&t;&t;ROUTE_VIA_IRQ1
DECL|macro|IRQ_MB93493_USB_ROUTE
mdefine_line|#define IRQ_MB93493_USB_ROUTE&t;&t;ROUTE_VIA_IRQ1
DECL|macro|IRQ_MB93493_LOCAL_BUS_ROUTE
mdefine_line|#define IRQ_MB93493_LOCAL_BUS_ROUTE&t;ROUTE_VIA_IRQ1
DECL|macro|IRQ_MB93493_PCMCIA_ROUTE
mdefine_line|#define IRQ_MB93493_PCMCIA_ROUTE&t;ROUTE_VIA_IRQ1
DECL|macro|IRQ_MB93493_GPIO_ROUTE
mdefine_line|#define IRQ_MB93493_GPIO_ROUTE&t;&t;ROUTE_VIA_IRQ1
DECL|macro|IRQ_MB93493_AUDIO_IN_ROUTE
mdefine_line|#define IRQ_MB93493_AUDIO_IN_ROUTE&t;ROUTE_VIA_IRQ1
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif /* _ASM_MB93493_IRQS_H */
eof
