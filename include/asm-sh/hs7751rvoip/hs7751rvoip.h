macro_line|#ifndef __ASM_SH_RENESAS_HS7751RVOIP_H
DECL|macro|__ASM_SH_RENESAS_HS7751RVOIP_H
mdefine_line|#define __ASM_SH_RENESAS_HS7751RVOIP_H
multiline_comment|/*&n; * linux/include/asm-sh/hs7751rvoip/hs7751rvoip.h&n; *&n; * Copyright (C) 2000  Atom Create Engineering Co., Ltd.&n; *&n; * Renesas Technology Sales HS7751RVoIP support&n; */
multiline_comment|/* Box specific addresses.  */
DECL|macro|PA_BCR
mdefine_line|#define PA_BCR&t;&t;0xa4000000&t;/* FPGA */
DECL|macro|PA_SLICCNTR1
mdefine_line|#define PA_SLICCNTR1&t;0xa4000006&t;/* SLIC PIO Control 1 */
DECL|macro|PA_SLICCNTR2
mdefine_line|#define PA_SLICCNTR2&t;0xa4000008&t;/* SLIC PIO Control 2 */
DECL|macro|PA_DMACNTR
mdefine_line|#define PA_DMACNTR&t;0xa400000a&t;/* USB DMA Control */
DECL|macro|PA_INPORTR
mdefine_line|#define PA_INPORTR&t;0xa400000c&t;/* Input Port Register */
DECL|macro|PA_OUTPORTR
mdefine_line|#define PA_OUTPORTR&t;0xa400000e&t;/* Output Port Reguster */
DECL|macro|PA_VERREG
mdefine_line|#define PA_VERREG&t;0xa4000014&t;/* FPGA Version Register */
DECL|macro|PA_AREA5_IO
mdefine_line|#define PA_AREA5_IO&t;0xb4000000&t;/* Area 5 IO Memory */
DECL|macro|PA_AREA6_IO
mdefine_line|#define PA_AREA6_IO&t;0xb8000000&t;/* Area 6 IO Memory */
DECL|macro|PA_IDE_OFFSET
mdefine_line|#define PA_IDE_OFFSET&t;0x1f0&t;&t;/* CF IDE Offset */
DECL|macro|IRLCNTR1
mdefine_line|#define IRLCNTR1&t;(PA_BCR + 0)&t;/* Interrupt Control Register1 */
DECL|macro|IRLCNTR2
mdefine_line|#define IRLCNTR2&t;(PA_BCR + 2)&t;/* Interrupt Control Register2 */
DECL|macro|IRLCNTR3
mdefine_line|#define IRLCNTR3&t;(PA_BCR + 4)&t;/* Interrupt Control Register3 */
DECL|macro|IRLCNTR4
mdefine_line|#define IRLCNTR4&t;(PA_BCR + 16)&t;/* Interrupt Control Register4 */
DECL|macro|IRLCNTR5
mdefine_line|#define IRLCNTR5&t;(PA_BCR + 18)&t;/* Interrupt Control Register5 */
DECL|macro|IRQ_PCIETH
mdefine_line|#define IRQ_PCIETH&t;6&t;&t;/* PCI Ethernet IRQ */
DECL|macro|IRQ_PCIHUB
mdefine_line|#define IRQ_PCIHUB&t;7&t;&t;/* PCI Ethernet Hub IRQ */
DECL|macro|IRQ_USBCOM
mdefine_line|#define IRQ_USBCOM&t;8&t;&t;/* USB Comunication IRQ */
DECL|macro|IRQ_USBCON
mdefine_line|#define IRQ_USBCON&t;9&t;&t;/* USB Connect IRQ */
DECL|macro|IRQ_USBDMA
mdefine_line|#define IRQ_USBDMA&t;10&t;&t;/* USB DMA IRQ */
DECL|macro|IRQ_CFCARD
mdefine_line|#define IRQ_CFCARD&t;11&t;&t;/* CF Card IRQ */
DECL|macro|IRQ_PCMCIA
mdefine_line|#define IRQ_PCMCIA&t;12&t;&t;/* PCMCIA IRQ */
DECL|macro|IRQ_PCISLOT
mdefine_line|#define IRQ_PCISLOT&t;13&t;&t;/* PCI Slot #1 IRQ */
DECL|macro|IRQ_ONHOOK1
mdefine_line|#define IRQ_ONHOOK1&t;0&t;&t;/* ON HOOK1 IRQ */
DECL|macro|IRQ_OFFHOOK1
mdefine_line|#define IRQ_OFFHOOK1&t;1&t;&t;/* OFF HOOK1 IRQ */
DECL|macro|IRQ_ONHOOK2
mdefine_line|#define IRQ_ONHOOK2&t;2&t;&t;/* ON HOOK2 IRQ */
DECL|macro|IRQ_OFFHOOK2
mdefine_line|#define IRQ_OFFHOOK2&t;3&t;&t;/* OFF HOOK2 IRQ */
DECL|macro|IRQ_RINGING
mdefine_line|#define&t;IRQ_RINGING&t;4&t;&t;/* Ringing IRQ */
DECL|macro|IRQ_CODEC
mdefine_line|#define&t;IRQ_CODEC&t;5&t;&t;/* CODEC IRQ */
macro_line|#endif  /* __ASM_SH_RENESAS_HS7751RVOIP */
eof
