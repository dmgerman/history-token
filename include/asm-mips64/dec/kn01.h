multiline_comment|/*&n; * Hardware info about DECstation DS2100/3100 systems (otherwise known as&n; * pmin/pmax or KN01).&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1995,1996 by Paul M. Antoine, some code and definitions&n; * are by courtesy of Chris Fraser.&n; * Copyright (C) 2002, 2003  Maciej W. Rozycki&n; */
macro_line|#ifndef __ASM_MIPS_DEC_KN01_H
DECL|macro|__ASM_MIPS_DEC_KN01_H
mdefine_line|#define __ASM_MIPS_DEC_KN01_H
macro_line|#include &lt;asm/addrspace.h&gt;
DECL|macro|KN01_SLOT_BASE
mdefine_line|#define KN01_SLOT_BASE&t;KSEG1ADDR(0x10000000)
DECL|macro|KN01_SLOT_SIZE
mdefine_line|#define KN01_SLOT_SIZE&t;0x01000000
multiline_comment|/*&n; * Address ranges for devices.&n; */
DECL|macro|KN01_PMASK
mdefine_line|#define KN01_PMASK&t;(0*KN01_SLOT_SIZE)&t;/* color plane mask */
DECL|macro|KN01_PCC
mdefine_line|#define KN01_PCC&t;(1*KN01_SLOT_SIZE)&t;/* PCC (DC503) cursor */
DECL|macro|KN01_VDAC
mdefine_line|#define KN01_VDAC&t;(2*KN01_SLOT_SIZE)&t;/* color map */
DECL|macro|KN01_RES_3
mdefine_line|#define KN01_RES_3&t;(3*KN01_SLOT_SIZE)&t;/* unused */
DECL|macro|KN01_RES_4
mdefine_line|#define KN01_RES_4&t;(4*KN01_SLOT_SIZE)&t;/* unused */
DECL|macro|KN01_RES_5
mdefine_line|#define KN01_RES_5&t;(5*KN01_SLOT_SIZE)&t;/* unused */
DECL|macro|KN01_RES_6
mdefine_line|#define KN01_RES_6&t;(6*KN01_SLOT_SIZE)&t;/* unused */
DECL|macro|KN01_ERRADDR
mdefine_line|#define KN01_ERRADDR&t;(7*KN01_SLOT_SIZE)&t;/* write error address */
DECL|macro|KN01_LANCE
mdefine_line|#define KN01_LANCE&t;(8*KN01_SLOT_SIZE)&t;/* LANCE (Am7990) Ethernet */
DECL|macro|KN01_LANCE_MEM
mdefine_line|#define KN01_LANCE_MEM&t;(9*KN01_SLOT_SIZE)&t;/* LANCE buffer memory */
DECL|macro|KN01_SII
mdefine_line|#define KN01_SII&t;(10*KN01_SLOT_SIZE)&t;/* SII (DC7061) SCSI */
DECL|macro|KN01_SII_MEM
mdefine_line|#define KN01_SII_MEM&t;(11*KN01_SLOT_SIZE)&t;/* SII buffer memory */
DECL|macro|KN01_DZ11
mdefine_line|#define KN01_DZ11&t;(12*KN01_SLOT_SIZE)&t;/* DZ11 (DC7085) serial */
DECL|macro|KN01_RTC
mdefine_line|#define KN01_RTC&t;(13*KN01_SLOT_SIZE)&t;/* DS1287 RTC (bytes #0) */
DECL|macro|KN01_ESAR
mdefine_line|#define KN01_ESAR&t;(13*KN01_SLOT_SIZE)&t;/* MAC address (bytes #1) */
DECL|macro|KN01_CSR
mdefine_line|#define KN01_CSR&t;(14*KN01_SLOT_SIZE)&t;/* system ctrl &amp; status reg */
DECL|macro|KN01_SYS_ROM
mdefine_line|#define KN01_SYS_ROM&t;(15*KN01_SLOT_SIZE)&t;/* system board ROM */
multiline_comment|/*&n; * Some port addresses...&n; */
DECL|macro|KN01_LANCE_BASE
mdefine_line|#define KN01_LANCE_BASE (KN01_SLOT_BASE + KN01_LANCE)&t;/* 0xB8000000 */
DECL|macro|KN01_DZ11_BASE
mdefine_line|#define KN01_DZ11_BASE&t;(KN01_SLOT_BASE + KN01_DZ11)&t;/* 0xBC000000 */
DECL|macro|KN01_RTC_BASE
mdefine_line|#define KN01_RTC_BASE&t;(KN01_SLOT_BASE + KN01_RTC)&t;/* 0xBD000000 */
multiline_comment|/*&n; * Frame buffer memory address.&n; */
DECL|macro|KN01_VFB_MEM
mdefine_line|#define KN01_VFB_MEM&t;KSEG1ADDR(0x0fc00000)
multiline_comment|/*&n; * CPU interrupt bits.&n; */
DECL|macro|KN01_CPU_INR_BUS
mdefine_line|#define KN01_CPU_INR_BUS&t;6&t;/* memory, I/O bus read/write errors */
DECL|macro|KN01_CPU_INR_VIDEO
mdefine_line|#define KN01_CPU_INR_VIDEO&t;6&t;/* PCC area detect #2 */
DECL|macro|KN01_CPU_INR_RTC
mdefine_line|#define KN01_CPU_INR_RTC&t;5&t;/* DS1287 RTC */
DECL|macro|KN01_CPU_INR_DZ11
mdefine_line|#define KN01_CPU_INR_DZ11&t;4&t;/* DZ11 (DC7085) serial */
DECL|macro|KN01_CPU_INR_LANCE
mdefine_line|#define KN01_CPU_INR_LANCE&t;3&t;/* LANCE (Am7990) Ethernet */
DECL|macro|KN01_CPU_INR_SII
mdefine_line|#define KN01_CPU_INR_SII&t;2&t;/* SII (DC7061) SCSI */
multiline_comment|/*&n; * System Control &amp; Status Register bits.&n; */
DECL|macro|KN01_CSR_MNFMOD
mdefine_line|#define KN01_CSR_MNFMOD&t;&t;(1&lt;&lt;15)&t;/* MNFMOD manufacturing jumper */
DECL|macro|KN01_CSR_STATUS
mdefine_line|#define KN01_CSR_STATUS&t;&t;(1&lt;&lt;14)&t;/* self-test result status output */
DECL|macro|KN01_CSR_PARDIS
mdefine_line|#define KN01_CSR_PARDIS&t;&t;(1&lt;&lt;13)&t;/* parity error disable */
DECL|macro|KN01_CSR_CRSRTST
mdefine_line|#define KN01_CSR_CRSRTST&t;(1&lt;&lt;12)&t;/* PCC test output */
DECL|macro|KN01_CSR_MONO
mdefine_line|#define KN01_CSR_MONO&t;&t;(1&lt;&lt;11)&t;/* mono/color fb SIMM installed */
DECL|macro|KN01_CSR_MEMERR
mdefine_line|#define KN01_CSR_MEMERR&t;&t;(1&lt;&lt;10)&t;/* write timeout error status &amp; ack*/
DECL|macro|KN01_CSR_VINT
mdefine_line|#define KN01_CSR_VINT&t;&t;(1&lt;&lt;9)&t;/* PCC area detect #2 status &amp; ack */
DECL|macro|KN01_CSR_TXDIS
mdefine_line|#define KN01_CSR_TXDIS&t;&t;(1&lt;&lt;8)&t;/* DZ11 transmit disable */
DECL|macro|KN01_CSR_VBGTRG
mdefine_line|#define KN01_CSR_VBGTRG&t;&t;(1&lt;&lt;2)&t;/* blue DAC voltage over green (r/o) */
DECL|macro|KN01_CSR_VRGTRG
mdefine_line|#define KN01_CSR_VRGTRG&t;&t;(1&lt;&lt;1)&t;/* red DAC voltage over green (r/o) */
DECL|macro|KN01_CSR_VRGTRB
mdefine_line|#define KN01_CSR_VRGTRB&t;&t;(1&lt;&lt;0)&t;/* red DAC voltage over blue (r/o) */
DECL|macro|KN01_CSR_LEDS
mdefine_line|#define KN01_CSR_LEDS&t;&t;(0xff&lt;&lt;0) /* ~diagnostic LEDs (w/o) */
macro_line|#endif /* __ASM_MIPS_DEC_KN01_H */
eof
