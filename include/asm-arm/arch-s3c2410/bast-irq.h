multiline_comment|/* linux/include/asm-arm/arch-s3c2410/bast-irq.h&n; *&n; * (c) 2003,2004 Simtec Electronics&n; *  Ben Dooks &lt;ben@simtec.co.uk&gt;&n; *&n; * Machine BAST - IRQ Number definitions&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * Changelog:&n; *  14-Sep-2004 BJD  Fixed IRQ_USBOC definition&n; *  06-Jan-2003 BJD  Linux 2.6.0 version&n; */
macro_line|#ifndef __ASM_ARCH_BASTIRQ_H
DECL|macro|__ASM_ARCH_BASTIRQ_H
mdefine_line|#define __ASM_ARCH_BASTIRQ_H
multiline_comment|/* irq numbers to onboard peripherals */
DECL|macro|IRQ_USBOC
mdefine_line|#define IRQ_USBOC      IRQ_EINT18
DECL|macro|IRQ_IDE0
mdefine_line|#define IRQ_IDE0       IRQ_EINT16
DECL|macro|IRQ_IDE1
mdefine_line|#define IRQ_IDE1       IRQ_EINT17
DECL|macro|IRQ_PCSERIAL1
mdefine_line|#define IRQ_PCSERIAL1  IRQ_EINT15
DECL|macro|IRQ_PCSERIAL2
mdefine_line|#define IRQ_PCSERIAL2  IRQ_EINT14
DECL|macro|IRQ_PCPARALLEL
mdefine_line|#define IRQ_PCPARALLEL IRQ_EINT13
DECL|macro|IRQ_ASIX
mdefine_line|#define IRQ_ASIX       IRQ_EINT11
DECL|macro|IRQ_DM9000
mdefine_line|#define IRQ_DM9000     IRQ_EINT10
DECL|macro|IRQ_ISA
mdefine_line|#define IRQ_ISA&t;       IRQ_EINT9
DECL|macro|IRQ_SMALERT
mdefine_line|#define IRQ_SMALERT    IRQ_EINT8
macro_line|#endif /* __ASM_ARCH_BASTIRQ_H */
eof
