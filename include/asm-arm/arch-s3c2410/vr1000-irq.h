multiline_comment|/* linux/include/asm-arm/arch-s3c2410/vr1000-irq.h&n; *&n; * (c) 2003,2004 Simtec Electronics&n; *  Ben Dooks &lt;ben@simtec.co.uk&gt;&n; *&n; * Machine VR1000 - IRQ Number definitions&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * Changelog:&n; *  06-Jan-2003 BJD  Linux 2.6.0 version&n; *  19-Mar-2004 BJD  Updates for VR1000&n; */
macro_line|#ifndef __ASM_ARCH_VR1000IRQ_H
DECL|macro|__ASM_ARCH_VR1000IRQ_H
mdefine_line|#define __ASM_ARCH_VR1000IRQ_H
multiline_comment|/* irq numbers to onboard peripherals */
DECL|macro|IRQ_USBOC
mdefine_line|#define IRQ_USBOC&t;     IRQ_EINT19
DECL|macro|IRQ_IDE0
mdefine_line|#define IRQ_IDE0&t;     IRQ_EINT16
DECL|macro|IRQ_IDE1
mdefine_line|#define IRQ_IDE1&t;     IRQ_EINT17
DECL|macro|IRQ_VR1000_SERIAL
mdefine_line|#define IRQ_VR1000_SERIAL    IRQ_EINT12
DECL|macro|IRQ_VR1000_DM9000A
mdefine_line|#define IRQ_VR1000_DM9000A   IRQ_EINT10
DECL|macro|IRQ_VR1000_DM9000N
mdefine_line|#define IRQ_VR1000_DM9000N   IRQ_EINT9
DECL|macro|IRQ_SMALERT
mdefine_line|#define IRQ_SMALERT&t;     IRQ_EINT8
macro_line|#endif /* __ASM_ARCH_VR1000IRQ_H */
eof
