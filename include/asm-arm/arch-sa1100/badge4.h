multiline_comment|/*&n; * linux/include/asm-arm/arch-sa1100/badge4.h&n; *&n; *   Tim Connors &lt;connors@hpl.hp.com&gt;&n; *   Christopher Hoover &lt;ch@hpl.hp.com&gt;&n; *&n; * Copyright (C) 2002 Hewlett-Packard Company&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; */
macro_line|#ifndef __ASM_ARCH_HARDWARE_H
macro_line|#error &quot;include &lt;asm/hardware.h&gt; instead&quot;
macro_line|#endif
DECL|macro|BADGE4_SA1111_BASE
mdefine_line|#define BADGE4_SA1111_BASE&t;&t;(0x48000000)
multiline_comment|/* GPIOs on the BadgePAD 4 */
DECL|macro|BADGE4_GPIO_INT_1111
mdefine_line|#define BADGE4_GPIO_INT_1111&t;&t;GPIO_GPIO0   /* SA-1111 IRQ */
DECL|macro|BADGE4_GPIO_INT_VID
mdefine_line|#define BADGE4_GPIO_INT_VID&t;&t;GPIO_GPIO1   /* Video expansion */
DECL|macro|BADGE4_GPIO_LGP2
mdefine_line|#define BADGE4_GPIO_LGP2&t;&t;GPIO_GPIO2   /* GPIO_LDD8 */
DECL|macro|BADGE4_GPIO_LGP3
mdefine_line|#define BADGE4_GPIO_LGP3&t;&t;GPIO_GPIO3   /* GPIO_LDD9 */
DECL|macro|BADGE4_GPIO_LGP4
mdefine_line|#define BADGE4_GPIO_LGP4&t;&t;GPIO_GPIO4   /* GPIO_LDD10 */
DECL|macro|BADGE4_GPIO_LGP5
mdefine_line|#define BADGE4_GPIO_LGP5&t;&t;GPIO_GPIO5   /* GPIO_LDD11 */
DECL|macro|BADGE4_GPIO_LGP6
mdefine_line|#define BADGE4_GPIO_LGP6&t;&t;GPIO_GPIO6   /* GPIO_LDD12 */
DECL|macro|BADGE4_GPIO_LGP7
mdefine_line|#define BADGE4_GPIO_LGP7&t;&t;GPIO_GPIO7   /* GPIO_LDD13 */
DECL|macro|BADGE4_GPIO_LGP8
mdefine_line|#define BADGE4_GPIO_LGP8&t;&t;GPIO_GPIO8   /* GPIO_LDD14 */
DECL|macro|BADGE4_GPIO_LGP9
mdefine_line|#define BADGE4_GPIO_LGP9&t;&t;GPIO_GPIO9   /* GPIO_LDD15 */
DECL|macro|BADGE4_GPIO_GPA_VID
mdefine_line|#define BADGE4_GPIO_GPA_VID&t;&t;GPIO_GPIO10  /* Video expansion */
DECL|macro|BADGE4_GPIO_GPB_VID
mdefine_line|#define BADGE4_GPIO_GPB_VID&t;&t;GPIO_GPIO11  /* Video expansion */
DECL|macro|BADGE4_GPIO_GPC_VID
mdefine_line|#define BADGE4_GPIO_GPC_VID&t;&t;GPIO_GPIO12  /* Video expansion */
DECL|macro|BADGE4_GPIO_UART_HS1
mdefine_line|#define BADGE4_GPIO_UART_HS1&t;&t;GPIO_GPIO13
DECL|macro|BADGE4_GPIO_UART_HS2
mdefine_line|#define BADGE4_GPIO_UART_HS2&t;&t;GPIO_GPIO14
DECL|macro|BADGE4_GPIO_MUXSEL0
mdefine_line|#define BADGE4_GPIO_MUXSEL0&t;&t;GPIO_GPIO15
DECL|macro|BADGE4_GPIO_TESTPT_J7
mdefine_line|#define BADGE4_GPIO_TESTPT_J7&t;&t;GPIO_GPIO16
DECL|macro|BADGE4_GPIO_SDSDA
mdefine_line|#define BADGE4_GPIO_SDSDA&t;&t;GPIO_GPIO17  /* SDRAM SPD Data */
DECL|macro|BADGE4_GPIO_SDSCL
mdefine_line|#define BADGE4_GPIO_SDSCL&t;&t;GPIO_GPIO18  /* SDRAM SPD Clock */
DECL|macro|BADGE4_GPIO_SDTYP0
mdefine_line|#define BADGE4_GPIO_SDTYP0&t;&t;GPIO_GPIO19  /* SDRAM Type Control */
DECL|macro|BADGE4_GPIO_SDTYP1
mdefine_line|#define BADGE4_GPIO_SDTYP1&t;&t;GPIO_GPIO20  /* SDRAM Type Control */
DECL|macro|BADGE4_GPIO_BGNT_1111
mdefine_line|#define BADGE4_GPIO_BGNT_1111&t;&t;GPIO_GPIO21  /* GPIO_MBGNT */
DECL|macro|BADGE4_GPIO_BREQ_1111
mdefine_line|#define BADGE4_GPIO_BREQ_1111&t;&t;GPIO_GPIO22  /* GPIO_TREQA */
DECL|macro|BADGE4_GPIO_TESTPT_J6
mdefine_line|#define BADGE4_GPIO_TESTPT_J6&t;&t;GPIO_GPIO23
DECL|macro|BADGE4_GPIO_PCMEN5V
mdefine_line|#define BADGE4_GPIO_PCMEN5V&t;&t;GPIO_GPIO24  /* 5V power */
DECL|macro|BADGE4_GPIO_SA1111_NRST
mdefine_line|#define BADGE4_GPIO_SA1111_NRST&t;&t;GPIO_GPIO25  /* SA-1111 nRESET */
DECL|macro|BADGE4_GPIO_TESTPT_J5
mdefine_line|#define BADGE4_GPIO_TESTPT_J5&t;&t;GPIO_GPIO26
DECL|macro|BADGE4_GPIO_CLK_1111
mdefine_line|#define BADGE4_GPIO_CLK_1111&t;&t;GPIO_GPIO27  /* GPIO_32_768kHz */
multiline_comment|/* Interrupts on the BadgePAD 4 */
DECL|macro|BADGE4_IRQ_GPIO_SA1111
mdefine_line|#define BADGE4_IRQ_GPIO_SA1111&t;&t;IRQ_GPIO0    /* SA-1111 interrupt */
multiline_comment|/* PCM5ENV Usage tracking */
DECL|macro|BADGE4_5V_PCMCIA_SOCK0
mdefine_line|#define BADGE4_5V_PCMCIA_SOCK0&t;&t;(1&lt;&lt;0)
DECL|macro|BADGE4_5V_PCMCIA_SOCK1
mdefine_line|#define BADGE4_5V_PCMCIA_SOCK1&t;&t;(1&lt;&lt;1)
DECL|macro|BADGE4_5V_PCMCIA_SOCK
mdefine_line|#define BADGE4_5V_PCMCIA_SOCK(n)&t;(1&lt;&lt;(n))
DECL|macro|BADGE4_5V_USB
mdefine_line|#define BADGE4_5V_USB&t;&t;&t;(1&lt;&lt;2)
macro_line|#ifndef __ASSEMBLY__
r_extern
r_void
id|badge4_set_5V
c_func
(paren
r_int
id|subsystem
comma
r_int
id|on
)paren
suffix:semicolon
macro_line|#endif
eof
