multiline_comment|/*&n; * Hardware info common to DECstation 5000/1xx systems (otherwise&n; * known as 3min or kn02ba) and Personal DECstations 5000/xx ones&n; * (otherwise known as maxine or kn02ca).&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1995,1996 by Paul M. Antoine, some code and definitions&n; * are by courtesy of Chris Fraser.&n; * Copyright (C) 2000, 2002, 2003  Maciej W. Rozycki&n; *&n; * These are addresses which have to be known early in the boot process.&n; * For other addresses refer to tc.h, ioasic_addrs.h and friends.&n; */
macro_line|#ifndef __ASM_MIPS_DEC_KN02XA_H
DECL|macro|__ASM_MIPS_DEC_KN02XA_H
mdefine_line|#define __ASM_MIPS_DEC_KN02XA_H
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &lt;asm/dec/ioasic_addrs.h&gt;
DECL|macro|KN02XA_SLOT_BASE
mdefine_line|#define KN02XA_SLOT_BASE&t;KSEG1ADDR(0x1c000000)
multiline_comment|/*&n; * Some port addresses...&n; */
DECL|macro|KN02XA_IOASIC_BASE
mdefine_line|#define KN02XA_IOASIC_BASE    (KN02XA_SLOT_BASE + IOASIC_IOCTL)&t;/* I/O ASIC */
DECL|macro|KN02XA_RTC_BASE
mdefine_line|#define KN02XA_RTC_BASE&t;&t;(KN02XA_SLOT_BASE + IOASIC_TOY)&t;/* RTC */
multiline_comment|/*&n; * Memory control ASIC registers.&n; */
DECL|macro|KN02XA_MER
mdefine_line|#define KN02XA_MER&t;KSEG1ADDR(0x0c400000)&t;/* memory error register */
DECL|macro|KN02XA_MSR
mdefine_line|#define KN02XA_MSR&t;KSEG1ADDR(0x0c800000)&t;/* memory size register */
multiline_comment|/*&n; * CPU control ASIC registers.&n; */
DECL|macro|KN02XA_MEM_CONF
mdefine_line|#define KN02XA_MEM_CONF&t;KSEG1ADDR(0x0e000000)&t;/* write timeout config */
DECL|macro|KN02XA_EAR
mdefine_line|#define KN02XA_EAR&t;KSEG1ADDR(0x0e000004)&t;/* error address register */
DECL|macro|KN02XA_BOOT0
mdefine_line|#define KN02XA_BOOT0&t;KSEG1ADDR(0x0e000008)&t;/* boot 0 register */
DECL|macro|KN02XA_MEM_INTR
mdefine_line|#define KN02XA_MEM_INTR&t;KSEG1ADDR(0x0e00000c)&t;/* write err IRQ stat &amp; ack */
multiline_comment|/*&n; * Memory Error Register bits, common definitions.&n; * The rest is defined in system-specific headers.&n; */
DECL|macro|KN02XA_MER_RES_28
mdefine_line|#define KN02XA_MER_RES_28&t;(0xf&lt;&lt;28)&t;/* unused */
DECL|macro|KN02XA_MER_RES_17
mdefine_line|#define KN02XA_MER_RES_17&t;(0x3ff&lt;&lt;17)&t;/* unused */
DECL|macro|KN02XA_MER_PAGERR
mdefine_line|#define KN02XA_MER_PAGERR&t;(1&lt;&lt;16)&t;&t;/* 2k page boundary error */
DECL|macro|KN02XA_MER_TRANSERR
mdefine_line|#define KN02XA_MER_TRANSERR&t;(1&lt;&lt;15)&t;&t;/* transfer length error */
DECL|macro|KN02XA_MER_PARDIS
mdefine_line|#define KN02XA_MER_PARDIS&t;(1&lt;&lt;14)&t;&t;/* parity error disable */
DECL|macro|KN02XA_MER_RES_12
mdefine_line|#define KN02XA_MER_RES_12&t;(0x3&lt;&lt;12)&t;/* unused */
DECL|macro|KN02XA_MER_BYTERR
mdefine_line|#define KN02XA_MER_BYTERR&t;(0xf&lt;&lt;8)&t;/* byte lane error bitmask */
DECL|macro|KN02XA_MER_RES_0
mdefine_line|#define KN02XA_MER_RES_0&t;(0xff&lt;&lt;0)&t;/* unused */
multiline_comment|/*&n; * Memory Size Register bits, common definitions.&n; * The rest is defined in system-specific headers.&n; */
DECL|macro|KN02XA_MSR_RES_27
mdefine_line|#define KN02XA_MSR_RES_27&t;(0x1f&lt;&lt;27)&t;/* unused */
DECL|macro|KN02XA_MSR_RES_14
mdefine_line|#define KN02XA_MSR_RES_14&t;(0x7&lt;&lt;14)&t;/* unused */
DECL|macro|KN02XA_MSR_SIZE
mdefine_line|#define KN02XA_MSR_SIZE&t;&t;(1&lt;&lt;13)&t;&t;/* 16M/4M stride */
DECL|macro|KN02XA_MSR_RES_0
mdefine_line|#define KN02XA_MSR_RES_0&t;(0x1fff&lt;&lt;0)&t;/* unused */
multiline_comment|/*&n; * Error Address Register bits.&n; */
DECL|macro|KN02XA_EAR_RES_29
mdefine_line|#define KN02XA_EAR_RES_29&t;(0x7&lt;&lt;29)&t;/* unused */
DECL|macro|KN02XA_EAR_ADDRESS
mdefine_line|#define KN02XA_EAR_ADDRESS&t;(0x7ffffff&lt;&lt;2)&t;/* address involved */
DECL|macro|KN02XA_EAR_RES_0
mdefine_line|#define KN02XA_EAR_RES_0&t;(0x3&lt;&lt;0)&t;/* unused */
macro_line|#endif /* __ASM_MIPS_DEC_KN02XA_H */
eof
