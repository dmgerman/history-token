multiline_comment|/*&n; *&t;include/asm-mips/dec/kn02ca.h&n; *&n; *&t;Personal DECstation 5000/xx (Maxine or KN02-CA) definitions.&n; *&n; *&t;Copyright (C) 2002, 2003  Maciej W. Rozycki&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef __ASM_MIPS_DEC_KN02CA_H
DECL|macro|__ASM_MIPS_DEC_KN02CA_H
mdefine_line|#define __ASM_MIPS_DEC_KN02CA_H
macro_line|#include &lt;asm/dec/kn02xa.h&gt;&t;&t;/* For common definitions. */
multiline_comment|/*&n; * CPU interrupt bits.&n; */
DECL|macro|KN02CA_CPU_INR_HALT
mdefine_line|#define KN02CA_CPU_INR_HALT&t;6&t;/* HALT from ACCESS.Bus */
DECL|macro|KN02CA_CPU_INR_CASCADE
mdefine_line|#define KN02CA_CPU_INR_CASCADE&t;5&t;/* I/O ASIC cascade */
DECL|macro|KN02CA_CPU_INR_BUS
mdefine_line|#define KN02CA_CPU_INR_BUS&t;4&t;/* memory, I/O bus read/write errors */
DECL|macro|KN02CA_CPU_INR_RTC
mdefine_line|#define KN02CA_CPU_INR_RTC&t;3&t;/* DS1287 RTC */
DECL|macro|KN02CA_CPU_INR_TIMER
mdefine_line|#define KN02CA_CPU_INR_TIMER&t;2&t;/* ARC periodic timer */
multiline_comment|/*&n; * I/O ASIC interrupt bits.  Star marks denote non-IRQ status bits.&n; */
DECL|macro|KN02CA_IO_INR_FLOPPY
mdefine_line|#define KN02CA_IO_INR_FLOPPY&t;15&t;/* 82077 FDC */
DECL|macro|KN02CA_IO_INR_NVRAM
mdefine_line|#define KN02CA_IO_INR_NVRAM&t;14&t;/* (*) NVRAM clear jumper */
DECL|macro|KN02CA_IO_INR_POWERON
mdefine_line|#define KN02CA_IO_INR_POWERON&t;13&t;/* (*) ACCESS.Bus/power-on reset */
DECL|macro|KN02CA_IO_INR_TC0
mdefine_line|#define KN02CA_IO_INR_TC0&t;12&t;/* TURBOchannel slot #0 */
DECL|macro|KN02CA_IO_INR_TIMER
mdefine_line|#define KN02CA_IO_INR_TIMER&t;12&t;/* ARC periodic timer (?) */
DECL|macro|KN02CA_IO_INR_ISDN
mdefine_line|#define KN02CA_IO_INR_ISDN&t;11&t;/* Am79C30A ISDN */
DECL|macro|KN02CA_IO_INR_NRMOD
mdefine_line|#define KN02CA_IO_INR_NRMOD&t;10&t;/* (*) NRMOD manufacturing jumper */
DECL|macro|KN02CA_IO_INR_ASC
mdefine_line|#define KN02CA_IO_INR_ASC&t;9&t;/* ASC (NCR53C94) SCSI */
DECL|macro|KN02CA_IO_INR_LANCE
mdefine_line|#define KN02CA_IO_INR_LANCE&t;8&t;/* LANCE (Am7990) Ethernet */
DECL|macro|KN02CA_IO_INR_HDFLOPPY
mdefine_line|#define KN02CA_IO_INR_HDFLOPPY&t;7&t;/* (*) HD (1.44MB) floppy status */
DECL|macro|KN02CA_IO_INR_SCC0
mdefine_line|#define KN02CA_IO_INR_SCC0&t;6&t;/* SCC (Z85C30) serial #0 */
DECL|macro|KN02CA_IO_INR_TC1
mdefine_line|#define KN02CA_IO_INR_TC1&t;5&t;/* TURBOchannel slot #1 */
DECL|macro|KN02CA_IO_INR_XDFLOPPY
mdefine_line|#define KN02CA_IO_INR_XDFLOPPY&t;4&t;/* (*) XD (2.88MB) floppy status */
DECL|macro|KN02CA_IO_INR_VIDEO
mdefine_line|#define KN02CA_IO_INR_VIDEO&t;3&t;/* framebuffer */
DECL|macro|KN02CA_IO_INR_XVIDEO
mdefine_line|#define KN02CA_IO_INR_XVIDEO&t;2&t;/* ~framebuffer */
DECL|macro|KN02CA_IO_INR_AB_XMIT
mdefine_line|#define KN02CA_IO_INR_AB_XMIT&t;1&t;/* ACCESS.bus transmit */
DECL|macro|KN02CA_IO_INR_AB_RECV
mdefine_line|#define KN02CA_IO_INR_AB_RECV&t;0&t;/* ACCESS.bus receive */
multiline_comment|/*&n; * Memory Error Register bits.&n; */
DECL|macro|KN02CA_MER_INTR
mdefine_line|#define KN02CA_MER_INTR&t;&t;(1&lt;&lt;27)&t;&t;/* ARC IRQ status &amp; ack */
multiline_comment|/*&n; * Memory Size Register bits.&n; */
DECL|macro|KN02CA_MSR_INTREN
mdefine_line|#define KN02CA_MSR_INTREN&t;(1&lt;&lt;26)&t;&t;/* ARC periodic IRQ enable */
DECL|macro|KN02CA_MSR_MS10EN
mdefine_line|#define KN02CA_MSR_MS10EN&t;(1&lt;&lt;25)&t;&t;/* 10/1ms IRQ period select */
DECL|macro|KN02CA_MSR_PFORCE
mdefine_line|#define KN02CA_MSR_PFORCE&t;(0xf&lt;&lt;21)&t;/* byte lane error force */
DECL|macro|KN02CA_MSR_MABEN
mdefine_line|#define KN02CA_MSR_MABEN&t;(1&lt;&lt;20)&t;&t;/* A side VFB address enable */
DECL|macro|KN02CA_MSR_LASTBANK
mdefine_line|#define KN02CA_MSR_LASTBANK&t;(0x7&lt;&lt;17)&t;/* onboard RAM bank # */
multiline_comment|/*&n; * I/O ASIC System Support Register bits.&n; */
DECL|macro|KN03CA_IO_SSR_RES_14
mdefine_line|#define KN03CA_IO_SSR_RES_14&t;(1&lt;&lt;14)&t;&t;/* unused */
DECL|macro|KN03CA_IO_SSR_RES_13
mdefine_line|#define KN03CA_IO_SSR_RES_13&t;(1&lt;&lt;13)&t;&t;/* unused */
DECL|macro|KN03CA_IO_SSR_ISDN_RST
mdefine_line|#define KN03CA_IO_SSR_ISDN_RST&t;(1&lt;&lt;12)&t;&t;/* ~ISDN (Am79C30A) reset */
DECL|macro|KN03CA_IO_SSR_FLOPPY_RST
mdefine_line|#define KN03CA_IO_SSR_FLOPPY_RST (1&lt;&lt;7)&t;&t;/* ~FDC (82077) reset */
DECL|macro|KN03CA_IO_SSR_VIDEO_RST
mdefine_line|#define KN03CA_IO_SSR_VIDEO_RST&t;(1&lt;&lt;6)&t;&t;/* ~framebuffer reset */
DECL|macro|KN03CA_IO_SSR_AB_RST
mdefine_line|#define KN03CA_IO_SSR_AB_RST&t;(1&lt;&lt;5)&t;&t;/* ACCESS.bus reset */
DECL|macro|KN03CA_IO_SSR_RES_4
mdefine_line|#define KN03CA_IO_SSR_RES_4&t;(1&lt;&lt;4)&t;&t;/* unused */
DECL|macro|KN03CA_IO_SSR_RES_3
mdefine_line|#define KN03CA_IO_SSR_RES_3&t;(1&lt;&lt;4)&t;&t;/* unused */
DECL|macro|KN03CA_IO_SSR_RES_2
mdefine_line|#define KN03CA_IO_SSR_RES_2&t;(1&lt;&lt;2)&t;&t;/* unused */
DECL|macro|KN03CA_IO_SSR_RES_1
mdefine_line|#define KN03CA_IO_SSR_RES_1&t;(1&lt;&lt;1)&t;&t;/* unused */
DECL|macro|KN03CA_IO_SSR_LED
mdefine_line|#define KN03CA_IO_SSR_LED&t;(1&lt;&lt;0)&t;&t;/* power LED */
macro_line|#endif /* __ASM_MIPS_DEC_KN02CA_H */
eof
