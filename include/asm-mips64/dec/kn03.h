multiline_comment|/*&n; * Hardware info about DECstation 5000/2x0 systems (otherwise known as&n; * 3max+) and DECsystem 5900 systems (otherwise known as bigmax) which&n; * differ mechanically but are otherwise identical (both are known as&n; * KN03).&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1995,1996 by Paul M. Antoine, some code and definitions&n; * are by courtesy of Chris Fraser.&n; * Copyright (C) 2000, 2002, 2003  Maciej W. Rozycki&n; */
macro_line|#ifndef __ASM_MIPS_DEC_KN03_H
DECL|macro|__ASM_MIPS_DEC_KN03_H
mdefine_line|#define __ASM_MIPS_DEC_KN03_H
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &lt;asm/dec/ecc.h&gt;
macro_line|#include &lt;asm/dec/ioasic_addrs.h&gt;
DECL|macro|KN03_SLOT_BASE
mdefine_line|#define KN03_SLOT_BASE&t;KSEG1ADDR(0x1f800000)
multiline_comment|/*&n; * Some port addresses...&n; */
DECL|macro|KN03_IOASIC_BASE
mdefine_line|#define KN03_IOASIC_BASE&t;(KN03_SLOT_BASE + IOASIC_IOCTL)&t;/* I/O ASIC */
DECL|macro|KN03_RTC_BASE
mdefine_line|#define KN03_RTC_BASE&t;&t;(KN03_SLOT_BASE + IOASIC_TOY)&t;/* RTC */
DECL|macro|KN03_MCR_BASE
mdefine_line|#define KN03_MCR_BASE&t;&t;(KN03_SLOT_BASE + IOASIC_MCR)&t;/* MCR */
multiline_comment|/*&n; * CPU interrupt bits.&n; */
DECL|macro|KN03_CPU_INR_HALT
mdefine_line|#define KN03_CPU_INR_HALT&t;6&t;/* HALT button */
DECL|macro|KN03_CPU_INR_BUS
mdefine_line|#define KN03_CPU_INR_BUS&t;5&t;/* memory, I/O bus read/write errors */
DECL|macro|KN03_CPU_INR_RES_4
mdefine_line|#define KN03_CPU_INR_RES_4&t;4&t;/* unused */
DECL|macro|KN03_CPU_INR_RTC
mdefine_line|#define KN03_CPU_INR_RTC&t;3&t;/* DS1287 RTC */
DECL|macro|KN03_CPU_INR_CASCADE
mdefine_line|#define KN03_CPU_INR_CASCADE&t;2&t;/* I/O ASIC cascade */
multiline_comment|/*&n; * I/O ASIC interrupt bits.  Star marks denote non-IRQ status bits.&n; */
DECL|macro|KN03_IO_INR_3MAXP
mdefine_line|#define KN03_IO_INR_3MAXP&t;15&t;/* (*) 3max+/bigmax ID */
DECL|macro|KN03_IO_INR_NVRAM
mdefine_line|#define KN03_IO_INR_NVRAM&t;14&t;/* (*) NVRAM clear jumper */
DECL|macro|KN03_IO_INR_TC2
mdefine_line|#define KN03_IO_INR_TC2&t;&t;13&t;/* TURBOchannel slot #2 */
DECL|macro|KN03_IO_INR_TC1
mdefine_line|#define KN03_IO_INR_TC1&t;&t;12&t;/* TURBOchannel slot #1 */
DECL|macro|KN03_IO_INR_TC0
mdefine_line|#define KN03_IO_INR_TC0&t;&t;11&t;/* TURBOchannel slot #0 */
DECL|macro|KN03_IO_INR_NRMOD
mdefine_line|#define KN03_IO_INR_NRMOD&t;10&t;/* (*) NRMOD manufacturing jumper */
DECL|macro|KN03_IO_INR_ASC
mdefine_line|#define KN03_IO_INR_ASC&t;&t;9&t;/* ASC (NCR53C94) SCSI */
DECL|macro|KN03_IO_INR_LANCE
mdefine_line|#define KN03_IO_INR_LANCE&t;8&t;/* LANCE (Am7990) Ethernet */
DECL|macro|KN03_IO_INR_SCC1
mdefine_line|#define KN03_IO_INR_SCC1&t;7&t;/* SCC (Z85C30) serial #1 */
DECL|macro|KN03_IO_INR_SCC0
mdefine_line|#define KN03_IO_INR_SCC0&t;6&t;/* SCC (Z85C30) serial #0 */
DECL|macro|KN03_IO_INR_RTC
mdefine_line|#define KN03_IO_INR_RTC&t;&t;5&t;/* DS1287 RTC */
DECL|macro|KN03_IO_INR_PSU
mdefine_line|#define KN03_IO_INR_PSU&t;&t;4&t;/* power supply unit warning */
DECL|macro|KN03_IO_INR_RES_3
mdefine_line|#define KN03_IO_INR_RES_3&t;3&t;/* unused */
DECL|macro|KN03_IO_INR_ASC_DATA
mdefine_line|#define KN03_IO_INR_ASC_DATA&t;2&t;/* SCSI data ready (for PIO) */
DECL|macro|KN03_IO_INR_PBNC
mdefine_line|#define KN03_IO_INR_PBNC&t;1&t;/* ~HALT button debouncer */
DECL|macro|KN03_IO_INR_PBNO
mdefine_line|#define KN03_IO_INR_PBNO&t;0&t;/* HALT button debouncer */
multiline_comment|/*&n; * Memory Control Register bits.&n; */
DECL|macro|KN03_MCR_RES_16
mdefine_line|#define KN03_MCR_RES_16&t;&t;(0xffff&lt;&lt;16)&t;/* unused */
DECL|macro|KN03_MCR_DIAGCHK
mdefine_line|#define KN03_MCR_DIAGCHK&t;(1&lt;&lt;15)&t;&t;/* diagn/norml ECC reads */
DECL|macro|KN03_MCR_DIAGGEN
mdefine_line|#define KN03_MCR_DIAGGEN&t;(1&lt;&lt;14)&t;&t;/* diagn/norml ECC writes */
DECL|macro|KN03_MCR_CORRECT
mdefine_line|#define KN03_MCR_CORRECT&t;(1&lt;&lt;13)&t;&t;/* ECC correct/check */
DECL|macro|KN03_MCR_RES_11
mdefine_line|#define KN03_MCR_RES_11&t;&t;(0x3&lt;&lt;12)&t;/* unused */
DECL|macro|KN03_MCR_BNK32M
mdefine_line|#define KN03_MCR_BNK32M&t;&t;(1&lt;&lt;10)&t;&t;/* 32M/8M stride */
DECL|macro|KN03_MCR_RES_7
mdefine_line|#define KN03_MCR_RES_7&t;&t;(0x7&lt;&lt;7)&t;/* unused */
DECL|macro|KN03_MCR_CHECK
mdefine_line|#define KN03_MCR_CHECK&t;&t;(0x7f&lt;&lt;0)&t;/* diagnostic check bits */
multiline_comment|/*&n; * I/O ASIC System Support Register bits.&n; */
DECL|macro|KN03_IO_SSR_TXDIS1
mdefine_line|#define KN03_IO_SSR_TXDIS1&t;(1&lt;&lt;14)&t;&t;/* SCC1 transmit disable */
DECL|macro|KN03_IO_SSR_TXDIS0
mdefine_line|#define KN03_IO_SSR_TXDIS0&t;(1&lt;&lt;13)&t;&t;/* SCC0 transmit disable */
DECL|macro|KN03_IO_SSR_RES_12
mdefine_line|#define KN03_IO_SSR_RES_12&t;(1&lt;&lt;12)&t;&t;/* unused */
DECL|macro|KN03_IO_SSR_LEDS
mdefine_line|#define KN03_IO_SSR_LEDS&t;(0xff&lt;&lt;0)&t;/* ~diagnostic LEDs */
macro_line|#endif /* __ASM_MIPS_DEC_KN03_H */
eof
