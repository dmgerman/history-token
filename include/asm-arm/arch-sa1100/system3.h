multiline_comment|/*&n; * linux/include/asm-arm/arch-sa1100/system3.h&n; *&n; * Copyright (C) 2001 Stefan Eletzhofer &lt;stefan.eletzhofer@eletztrick.de&gt;&n; *&n; * $Id: system3.h,v 1.2.4.2 2001/12/04 14:58:50 seletz Exp $&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * $Log: system3.h,v $&n; * Revision 1.2.4.2  2001/12/04 14:58:50  seletz&n; * - removed neponset hack&n; * - removed irq definitions (now in irqs.h)&n; *&n; * Revision 1.2.4.1  2001/12/04 12:51:18  seletz&n; * - re-added from linux_2_4_8_ac12_rmk1_np1_pt1&n; *&n; * Revision 1.2.2.2  2001/11/16 13:58:43  seletz&n; * - simplified cpld register access&n; *&n; * Revision 1.2.2.1  2001/10/15 16:17:20  seletz&n; * - first revision&n; *&n; *&n; */
macro_line|#ifndef __ASM_ARCH_HARDWARE_H
macro_line|#error &quot;include &lt;asm/hardware.h&gt; instead&quot;
macro_line|#endif
multiline_comment|/* System 3 LCD */
DECL|macro|SYS3LCD
mdefine_line|#define SYS3LCD&t;&t;&t;SKPEN0
DECL|macro|SYS3LCDBACKL
mdefine_line|#define SYS3LCDBACKL&t;SKPEN1
DECL|macro|SYS3LCDBRIGHT
mdefine_line|#define SYS3LCDBRIGHT&t;SKPWM0
DECL|macro|SYS3LCDCONTR
mdefine_line|#define SYS3LCDCONTR&t;SKPWM1
DECL|macro|PT_CPLD_BASE
mdefine_line|#define PT_CPLD_BASE&t;&t;(0x10000000)
DECL|macro|PT_SMC_BASE
mdefine_line|#define PT_SMC_BASE&t;&t;&t;(0x18000000)
DECL|macro|PT_SA1111_BASE
mdefine_line|#define PT_SA1111_BASE&t;&t;(0x40000000)
DECL|macro|SA1111_BASE
mdefine_line|#define SA1111_BASE&t;&t;&t;PT_SA1111_BASE
DECL|macro|Ptcpld_p2v
mdefine_line|#define Ptcpld_p2v( x )&t;((x) - PT_CPLD_BASE + 0xf3000000)
DECL|macro|Ptcpld_v2p
mdefine_line|#define Ptcpld_v2p( x )&t;((x) - 0xf3000000 + PT_CPLD_BASE)
DECL|macro|_PT_SYSID
mdefine_line|#define _PT_SYSID&t;( PT_CPLD_BASE + 0x00 )
DECL|macro|_PT_IRQSR
mdefine_line|#define _PT_IRQSR&t;( PT_CPLD_BASE + 0x24 )
DECL|macro|_PT_CTRL0
mdefine_line|#define _PT_CTRL0&t;( PT_CPLD_BASE + 0x90 )
DECL|macro|_PT_CTRL1
mdefine_line|#define _PT_CTRL1&t;( PT_CPLD_BASE + 0xA0 )
DECL|macro|_PT_CTRL2
mdefine_line|#define _PT_CTRL2&t;( PT_CPLD_BASE + 0xB0 )
DECL|macro|PT_SYSID
mdefine_line|#define PT_SYSID&t;(*((volatile u_char *)Ptcpld_p2v( _PT_SYSID )))
DECL|macro|PT_IRQSR
mdefine_line|#define PT_IRQSR&t;(*((volatile u_char *)Ptcpld_p2v( _PT_IRQSR )))
DECL|macro|PT_CTRL0
mdefine_line|#define PT_CTRL0&t;(*((volatile u_char *)Ptcpld_p2v( _PT_CTRL0 )))
DECL|macro|PT_CTRL1
mdefine_line|#define PT_CTRL1&t;(*((volatile u_char *)Ptcpld_p2v( _PT_CTRL1 )))
DECL|macro|PT_CTRL2
mdefine_line|#define PT_CTRL2&t;(*((volatile u_char *)Ptcpld_p2v( _PT_CTRL2 )))
DECL|macro|PTCTRL0_set
mdefine_line|#define PTCTRL0_set( x )&t;PT_CTRL0 |= (x)
DECL|macro|PTCTRL1_set
mdefine_line|#define PTCTRL1_set( x )&t;PT_CTRL1 |= (x)
DECL|macro|PTCTRL2_set
mdefine_line|#define PTCTRL2_set( x )&t;PT_CTRL2 |= (x)
DECL|macro|PTCTRL0_clear
mdefine_line|#define PTCTRL0_clear( x )&t;PT_CTRL0 &amp;= ~(x)
DECL|macro|PTCTRL1_clear
mdefine_line|#define PTCTRL1_clear( x )&t;PT_CTRL1 &amp;= ~(x)
DECL|macro|PTCTRL2_clear
mdefine_line|#define PTCTRL2_clear( x )&t;PT_CTRL2 &amp;= ~(x)
multiline_comment|/* System ID register */
multiline_comment|/* IRQ Source Register */
DECL|macro|PT_IRQ_LAN
mdefine_line|#define PT_IRQ_LAN&t;&t;( 1&lt;&lt;0 )
DECL|macro|PT_IRQ_X
mdefine_line|#define PT_IRQ_X&t;&t;( 1&lt;&lt;1 )
DECL|macro|PT_IRQ_SA1111
mdefine_line|#define PT_IRQ_SA1111&t;( 1&lt;&lt;2 )
DECL|macro|PT_IRQ_RS1
mdefine_line|#define PT_IRQ_RS1&t;&t;( 1&lt;&lt;3 )
DECL|macro|PT_IRQ_RS1_RING
mdefine_line|#define PT_IRQ_RS1_RING&t;( 1&lt;&lt;4 )
DECL|macro|PT_IRQ_RS1_DCD
mdefine_line|#define PT_IRQ_RS1_DCD&t;( 1&lt;&lt;5 )
DECL|macro|PT_IRQ_RS1_DSR
mdefine_line|#define PT_IRQ_RS1_DSR&t;( 1&lt;&lt;6 )
DECL|macro|PT_IRQ_RS2
mdefine_line|#define PT_IRQ_RS2&t;&t;( 1&lt;&lt;7 )
multiline_comment|/* FIXME */
DECL|macro|PT_IRQ_USAR
mdefine_line|#define PT_IRQ_USAR&t;&t;( 1&lt;&lt;1 )
multiline_comment|/* CTRL 0 */
DECL|macro|PT_CTRL0_USBSLAVE
mdefine_line|#define PT_CTRL0_USBSLAVE&t;( 1&lt;&lt;0 )
DECL|macro|PT_CTRL0_USBHOST
mdefine_line|#define PT_CTRL0_USBHOST&t;( 1&lt;&lt;1 )
DECL|macro|PT_CTRL0_LCD_BL
mdefine_line|#define PT_CTRL0_LCD_BL&t;&t;( 1&lt;&lt;2 )
DECL|macro|PT_CTRL0_LAN_EN
mdefine_line|#define PT_CTRL0_LAN_EN&t;&t;( 1&lt;&lt;3 )&t;/* active low */
DECL|macro|PT_CTRL0_IRDA_M
mdefine_line|#define PT_CTRL0_IRDA_M(x)&t;( (((u_char)x)&amp;0x03)&lt;&lt;4 )
DECL|macro|PT_CTRL0_IRDA_M0
mdefine_line|#define PT_CTRL0_IRDA_M0&t;( 1&lt;&lt;4 )
DECL|macro|PT_CTRL0_IRDA_M1
mdefine_line|#define PT_CTRL0_IRDA_M1&t;( 1&lt;&lt;5 )
DECL|macro|PT_CTRL0_IRDA_FSEL
mdefine_line|#define PT_CTRL0_IRDA_FSEL&t;( 1&lt;&lt;6 )
DECL|macro|PT_CTRL0_LCD_EN
mdefine_line|#define PT_CTRL0_LCD_EN&t;&t;( 1&lt;&lt;7 )
DECL|macro|PT_CTRL0_INIT
mdefine_line|#define PT_CTRL0_INIT&t;( PT_CTRL0_USBSLAVE | PT_CTRL0_USBHOST | &bslash;&n;&t;&t;&t;&t;&t;&t;PT_CTRL0_LCD_BL | PT_CTRL0_LAN_EN | PT_CTRL0_LCD_EN )
multiline_comment|/* CTRL 1 */
DECL|macro|PT_CTRL1_RS3_MUX
mdefine_line|#define PT_CTRL1_RS3_MUX(x) ( (((u_char)x)&amp;0x03)&lt;&lt;0 )
DECL|macro|PT_CTRL1_RS3_MUX0
mdefine_line|#define PT_CTRL1_RS3_MUX0&t;( 1&lt;&lt;0 )
DECL|macro|PT_CTRL1_RS3_MUX1
mdefine_line|#define PT_CTRL1_RS3_MUX1&t;( 1&lt;&lt;1 )
DECL|macro|PT_CTRL1_RS3_RST
mdefine_line|#define PT_CTRL1_RS3_RST&t;( 1&lt;&lt;2 )
DECL|macro|PT_CTRL1_RS3_RS485_TERM
mdefine_line|#define PT_CTRL1_RS3_RS485_TERM&t;( 1&lt;&lt;4 )
DECL|macro|PT_CTRL1_X
mdefine_line|#define PT_CTRL1_X&t;&t;&t;( 1&lt;&lt;4 )
DECL|macro|PT_CTRL1_PCMCIA_A0VPP
mdefine_line|#define PT_CTRL1_PCMCIA_A0VPP&t;( 1&lt;&lt;6 )
DECL|macro|PT_CTRL1_PCMCIA_A1VPP
mdefine_line|#define PT_CTRL1_PCMCIA_A1VPP&t;( 1&lt;&lt;7 )
DECL|macro|PT_RS3_MUX_ALIRS
mdefine_line|#define PT_RS3_MUX_ALIRS&t;( 0 )
DECL|macro|PT_RS3_MUX_IDATA
mdefine_line|#define PT_RS3_MUX_IDATA&t;( 1 )
DECL|macro|PT_RS3_MUX_RADIO
mdefine_line|#define PT_RS3_MUX_RADIO&t;( 2 )
DECL|macro|PT_RS3_MUX_RS485
mdefine_line|#define PT_RS3_MUX_RS485&t;( 3 )
multiline_comment|/* CTRL 2 */
DECL|macro|PT_CTRL2_RS1_RTS
mdefine_line|#define PT_CTRL2_RS1_RTS&t;( 1&lt;&lt;0 )
DECL|macro|PT_CTRL2_RS1_DTR
mdefine_line|#define PT_CTRL2_RS1_DTR&t;( 1&lt;&lt;1 )
eof
