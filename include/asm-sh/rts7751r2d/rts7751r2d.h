macro_line|#ifndef __ASM_SH_RENESAS_RTS7751R2D_H
DECL|macro|__ASM_SH_RENESAS_RTS7751R2D_H
mdefine_line|#define __ASM_SH_RENESAS_RTS7751R2D_H
multiline_comment|/*&n; * linux/include/asm-sh/renesas_rts7751r2d.h&n; *&n; * Copyright (C) 2000  Atom Create Engineering Co., Ltd.&n; *&n; * Renesas Technology Sales RTS7751R2D support&n; */
multiline_comment|/* Box specific addresses.  */
DECL|macro|PA_BCR
mdefine_line|#define PA_BCR&t;&t;0xa4000000&t;/* FPGA */
DECL|macro|PA_IRLMON
mdefine_line|#define PA_IRLMON&t;0xa4000002&t;/* Interrupt Status control */
DECL|macro|PA_CFCTL
mdefine_line|#define PA_CFCTL&t;0xa4000004&t;/* CF Timing control */
DECL|macro|PA_CFPOW
mdefine_line|#define PA_CFPOW&t;0xa4000006&t;/* CF Power control */
DECL|macro|PA_DISPCTL
mdefine_line|#define PA_DISPCTL&t;0xa4000008&t;/* Display Timing control */
DECL|macro|PA_SDMPOW
mdefine_line|#define PA_SDMPOW&t;0xa400000a&t;/* SD Power control */
DECL|macro|PA_RTCCE
mdefine_line|#define PA_RTCCE&t;0xa400000c&t;/* RTC(9701) Enable control */
DECL|macro|PA_PCICD
mdefine_line|#define PA_PCICD&t;0xa400000e&t;/* PCI Extention detect control */
DECL|macro|PA_VOYAGERRTS
mdefine_line|#define PA_VOYAGERRTS&t;0xa4000020&t;/* VOYAGER Reset control */
macro_line|#if defined(CONFIG_RTS7751R2D_REV11)
DECL|macro|PA_AXRST
mdefine_line|#define PA_AXRST&t;0xa4000022&t;/* AX_LAN Reset control */
DECL|macro|PA_CFRST
mdefine_line|#define PA_CFRST&t;0xa4000024&t;/* CF Reset control */
DECL|macro|PA_ADMRTS
mdefine_line|#define&t;PA_ADMRTS&t;0xa4000026&t;/* SD Reset control */
DECL|macro|PA_EXTRST
mdefine_line|#define PA_EXTRST&t;0xa4000028&t;/* Extention Reset control */
DECL|macro|PA_CFCDINTCLR
mdefine_line|#define PA_CFCDINTCLR&t;0xa400002a&t;/* CF Insert Interrupt clear */
macro_line|#else
DECL|macro|PA_CFRST
mdefine_line|#define PA_CFRST&t;0xa4000022&t;/* CF Reset control */
DECL|macro|PA_ADMRTS
mdefine_line|#define&t;PA_ADMRTS&t;0xa4000024&t;/* SD Reset control */
DECL|macro|PA_EXTRST
mdefine_line|#define PA_EXTRST&t;0xa4000026&t;/* Extention Reset control */
DECL|macro|PA_CFCDINTCLR
mdefine_line|#define PA_CFCDINTCLR&t;0xa4000028&t;/* CF Insert Interrupt clear */
DECL|macro|PA_KEYCTLCLR
mdefine_line|#define&t;PA_KEYCTLCLR&t;0xa400002a&t;/* Key Interrupt clear */
macro_line|#endif
DECL|macro|PA_POWOFF
mdefine_line|#define PA_POWOFF&t;0xa4000030&t;/* Board Power OFF control */
DECL|macro|PA_VERREG
mdefine_line|#define PA_VERREG&t;0xa4000032&t;/* FPGA Version Register */
DECL|macro|PA_INPORT
mdefine_line|#define PA_INPORT&t;0xa4000034&t;/* KEY Input Port control */
DECL|macro|PA_OUTPORT
mdefine_line|#define PA_OUTPORT&t;0xa4000036&t;/* LED control */
DECL|macro|PA_DMPORT
mdefine_line|#define PA_DMPORT&t;0xa4000038&t;/* DM270 Output Port control */
DECL|macro|PA_AX88796L
mdefine_line|#define PA_AX88796L&t;0xaa000400&t;/* AX88796L Area */
DECL|macro|PA_VOYAGER
mdefine_line|#define PA_VOYAGER&t;0xab000000&t;/* VOYAGER GX Area */
DECL|macro|PA_AREA5_IO
mdefine_line|#define PA_AREA5_IO&t;0xb4000000&t;/* Area 5 IO Memory */
DECL|macro|PA_AREA6_IO
mdefine_line|#define PA_AREA6_IO&t;0xb8000000&t;/* Area 6 IO Memory */
DECL|macro|PA_IDE_OFFSET
mdefine_line|#define PA_IDE_OFFSET&t;0x1f0&t;&t;/* CF IDE Offset */
DECL|macro|AX88796L_IO_BASE
mdefine_line|#define AX88796L_IO_BASE&t;0x1000&t;/* AX88796L IO Base Address */
DECL|macro|IRLCNTR1
mdefine_line|#define IRLCNTR1&t;(PA_BCR + 0)&t;/* Interrupt Control Register1 */
macro_line|#if defined(CONFIG_RTS7751R2D_REV11)
DECL|macro|IRQ_PCIETH
mdefine_line|#define IRQ_PCIETH&t;0&t;&t;/* PCI Ethernet IRQ */
DECL|macro|IRQ_CFCARD
mdefine_line|#define IRQ_CFCARD&t;1&t;&t;/* CF Card IRQ */
DECL|macro|IRQ_CFINST
mdefine_line|#define IRQ_CFINST&t;2&t;&t;/* CF Card Insert IRQ */
DECL|macro|IRQ_PCMCIA
mdefine_line|#define IRQ_PCMCIA&t;3&t;&t;/* PCMCIA IRQ */
DECL|macro|IRQ_VOYAGER
mdefine_line|#define IRQ_VOYAGER&t;4&t;&t;/* VOYAGER IRQ */
DECL|macro|IRQ_ONETH
mdefine_line|#define IRQ_ONETH&t;5&t;&t;/* On board Ethernet IRQ */
macro_line|#else
DECL|macro|IRQ_KEYIN
mdefine_line|#define IRQ_KEYIN&t;0&t;&t;/* Key Input IRQ */
DECL|macro|IRQ_PCIETH
mdefine_line|#define IRQ_PCIETH&t;1&t;&t;/* PCI Ethernet IRQ */
DECL|macro|IRQ_CFCARD
mdefine_line|#define IRQ_CFCARD&t;2&t;&t;/* CF Card IRQ */
DECL|macro|IRQ_CFINST
mdefine_line|#define IRQ_CFINST&t;3&t;&t;/* CF Card Insert IRQ */
DECL|macro|IRQ_PCMCIA
mdefine_line|#define IRQ_PCMCIA&t;4&t;&t;/* PCMCIA IRQ */
DECL|macro|IRQ_VOYAGER
mdefine_line|#define IRQ_VOYAGER&t;5&t;&t;/* VOYAGER IRQ */
macro_line|#endif
DECL|macro|IRQ_RTCALM
mdefine_line|#define IRQ_RTCALM&t;6&t;&t;/* RTC Alarm IRQ */
DECL|macro|IRQ_RTCTIME
mdefine_line|#define IRQ_RTCTIME&t;7&t;&t;/* RTC Timer IRQ */
DECL|macro|IRQ_SDCARD
mdefine_line|#define IRQ_SDCARD&t;8&t;&t;/* SD Card IRQ */
DECL|macro|IRQ_PCISLOT1
mdefine_line|#define IRQ_PCISLOT1&t;9&t;&t;/* PCI Slot #1 IRQ */
DECL|macro|IRQ_PCISLOT2
mdefine_line|#define IRQ_PCISLOT2&t;10&t;&t;/* PCI Slot #2 IRQ */
DECL|macro|IRQ_EXTENTION
mdefine_line|#define&t;IRQ_EXTENTION&t;11&t;&t;/* EXTn IRQ */
macro_line|#endif  /* __ASM_SH_RENESAS_RTS7751R2D */
eof
