multiline_comment|/*&n; *&t;include/asm-mips/dec/kn02ba.h&n; *&n; *&t;DECstation 5000/1xx (3min or KN02-BA) definitions.&n; *&n; *&t;Copyright (C) 2002, 2003  Maciej W. Rozycki&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef __ASM_MIPS_DEC_KN02BA_H
DECL|macro|__ASM_MIPS_DEC_KN02BA_H
mdefine_line|#define __ASM_MIPS_DEC_KN02BA_H
macro_line|#include &lt;asm/dec/kn02xa.h&gt;&t;&t;/* For common definitions. */
multiline_comment|/*&n; * CPU interrupt bits.&n; */
DECL|macro|KN02BA_CPU_INR_HALT
mdefine_line|#define KN02BA_CPU_INR_HALT&t;6&t;/* HALT button */
DECL|macro|KN02BA_CPU_INR_CASCADE
mdefine_line|#define KN02BA_CPU_INR_CASCADE&t;5&t;/* I/O ASIC cascade */
DECL|macro|KN02BA_CPU_INR_TC2
mdefine_line|#define KN02BA_CPU_INR_TC2&t;4&t;/* TURBOchannel slot #2 */
DECL|macro|KN02BA_CPU_INR_TC1
mdefine_line|#define KN02BA_CPU_INR_TC1&t;3&t;/* TURBOchannel slot #1 */
DECL|macro|KN02BA_CPU_INR_TC0
mdefine_line|#define KN02BA_CPU_INR_TC0&t;2&t;/* TURBOchannel slot #0 */
multiline_comment|/*&n; * I/O ASIC interrupt bits.  Star marks denote non-IRQ status bits.&n; */
DECL|macro|KN02BA_IO_INR_RES_15
mdefine_line|#define KN02BA_IO_INR_RES_15&t;15&t;/* unused */
DECL|macro|KN02BA_IO_INR_NVRAM
mdefine_line|#define KN02BA_IO_INR_NVRAM&t;14&t;/* (*) NVRAM clear jumper */
DECL|macro|KN02BA_IO_INR_RES_13
mdefine_line|#define KN02BA_IO_INR_RES_13&t;13&t;/* unused */
DECL|macro|KN02BA_IO_INR_BUS
mdefine_line|#define KN02BA_IO_INR_BUS&t;12&t;/* memory, I/O bus read/write errors */
DECL|macro|KN02BA_IO_INR_RES_11
mdefine_line|#define KN02BA_IO_INR_RES_11&t;11&t;/* unused */
DECL|macro|KN02BA_IO_INR_NRMOD
mdefine_line|#define KN02BA_IO_INR_NRMOD&t;10&t;/* (*) NRMOD manufacturing jumper */
DECL|macro|KN02BA_IO_INR_ASC
mdefine_line|#define KN02BA_IO_INR_ASC&t;9&t;/* ASC (NCR53C94) SCSI */
DECL|macro|KN02BA_IO_INR_LANCE
mdefine_line|#define KN02BA_IO_INR_LANCE&t;8&t;/* LANCE (Am7990) Ethernet */
DECL|macro|KN02BA_IO_INR_SCC1
mdefine_line|#define KN02BA_IO_INR_SCC1&t;7&t;/* SCC (Z85C30) serial #1 */
DECL|macro|KN02BA_IO_INR_SCC0
mdefine_line|#define KN02BA_IO_INR_SCC0&t;6&t;/* SCC (Z85C30) serial #0 */
DECL|macro|KN02BA_IO_INR_RTC
mdefine_line|#define KN02BA_IO_INR_RTC&t;5&t;/* DS1287 RTC */
DECL|macro|KN02BA_IO_INR_PSU
mdefine_line|#define KN02BA_IO_INR_PSU&t;4&t;/* power supply unit warning */
DECL|macro|KN02BA_IO_INR_RES_3
mdefine_line|#define KN02BA_IO_INR_RES_3&t;3&t;/* unused */
DECL|macro|KN02BA_IO_INR_ASC_DATA
mdefine_line|#define KN02BA_IO_INR_ASC_DATA&t;2&t;/* SCSI data ready (for PIO) */
DECL|macro|KN02BA_IO_INR_PBNC
mdefine_line|#define KN02BA_IO_INR_PBNC&t;1&t;/* ~HALT button debouncer */
DECL|macro|KN02BA_IO_INR_PBNO
mdefine_line|#define KN02BA_IO_INR_PBNO&t;0&t;/* HALT button debouncer */
multiline_comment|/*&n; * Memory Error Register bits.&n; */
DECL|macro|KN02BA_MER_RES_27
mdefine_line|#define KN02BA_MER_RES_27&t;(1&lt;&lt;27)&t;&t;/* unused */
multiline_comment|/*&n; * Memory Size Register bits.&n; */
DECL|macro|KN02BA_MSR_RES_17
mdefine_line|#define KN02BA_MSR_RES_17&t;(0x3ff&lt;&lt;17)&t;/* unused */
multiline_comment|/*&n; * I/O ASIC System Support Register bits.&n; */
DECL|macro|KN02BA_IO_SSR_TXDIS1
mdefine_line|#define KN02BA_IO_SSR_TXDIS1&t;(1&lt;&lt;14)&t;&t;/* SCC1 transmit disable */
DECL|macro|KN02BA_IO_SSR_TXDIS0
mdefine_line|#define KN02BA_IO_SSR_TXDIS0&t;(1&lt;&lt;13)&t;&t;/* SCC0 transmit disable */
DECL|macro|KN02BA_IO_SSR_RES_12
mdefine_line|#define KN02BA_IO_SSR_RES_12&t;(1&lt;&lt;12)&t;&t;/* unused */
DECL|macro|KN02BA_IO_SSR_LEDS
mdefine_line|#define KN02BA_IO_SSR_LEDS&t;(0xff&lt;&lt;0)&t;/* ~diagnostic LEDs */
macro_line|#endif /* __ASM_MIPS_DEC_KN02BA_H */
eof
