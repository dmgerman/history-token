multiline_comment|/*&n; * Hardware info about DECstation 5000/200 systems (otherwise known as&n; * 3max or KN02).&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1995,1996 by Paul M. Antoine, some code and definitions&n; * are by courtesy of Chris Fraser.&n; * Copyright (C) 2002, 2003  Maciej W. Rozycki&n; */
macro_line|#ifndef __ASM_MIPS_DEC_KN02_H
DECL|macro|__ASM_MIPS_DEC_KN02_H
mdefine_line|#define __ASM_MIPS_DEC_KN02_H
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#endif
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &lt;asm/dec/ecc.h&gt;
DECL|macro|KN02_SLOT_BASE
mdefine_line|#define KN02_SLOT_BASE&t;KSEG1ADDR(0x1fc00000)
DECL|macro|KN02_SLOT_SIZE
mdefine_line|#define KN02_SLOT_SIZE&t;0x00080000
multiline_comment|/*&n; * Address ranges decoded by the &quot;system slot&quot; logic for onboard devices.&n; */
DECL|macro|KN02_SYS_ROM
mdefine_line|#define KN02_SYS_ROM&t;(0*KN02_SLOT_SIZE)&t;/* system board ROM */
DECL|macro|KN02_RES_1
mdefine_line|#define KN02_RES_1&t;(1*KN02_SLOT_SIZE)&t;/* unused */
DECL|macro|KN02_CHKSYN
mdefine_line|#define KN02_CHKSYN&t;(2*KN02_SLOT_SIZE)&t;/* ECC syndrome */
DECL|macro|KN02_ERRADDR
mdefine_line|#define KN02_ERRADDR&t;(3*KN02_SLOT_SIZE)&t;/* bus error address */
DECL|macro|KN02_DZ11
mdefine_line|#define KN02_DZ11&t;(4*KN02_SLOT_SIZE)&t;/* DZ11 (DC7085) serial */
DECL|macro|KN02_RTC
mdefine_line|#define KN02_RTC&t;(5*KN02_SLOT_SIZE)&t;/* DS1287 RTC */
DECL|macro|KN02_CSR
mdefine_line|#define KN02_CSR&t;(6*KN02_SLOT_SIZE)&t;/* system ctrl &amp; status reg */
DECL|macro|KN02_SYS_ROM_7
mdefine_line|#define KN02_SYS_ROM_7&t;(7*KN02_SLOT_SIZE)&t;/* system board ROM (alias) */
multiline_comment|/*&n; * Some port addresses...&n; */
DECL|macro|KN02_DZ11_BASE
mdefine_line|#define KN02_DZ11_BASE&t;(KN02_SLOT_BASE + KN02_DZ11)&t;/* DZ11 */
DECL|macro|KN02_RTC_BASE
mdefine_line|#define KN02_RTC_BASE&t;(KN02_SLOT_BASE + KN02_RTC)&t;/* RTC */
DECL|macro|KN02_CSR_BASE
mdefine_line|#define KN02_CSR_BASE&t;(KN02_SLOT_BASE + KN02_CSR)&t;/* CSR */
multiline_comment|/*&n; * System Control &amp; Status Register bits.&n; */
DECL|macro|KN02_CSR_RES_28
mdefine_line|#define KN02_CSR_RES_28&t;&t;(0xf&lt;&lt;28)&t;/* unused */
DECL|macro|KN02_CSR_PSU
mdefine_line|#define KN02_CSR_PSU&t;&t;(1&lt;&lt;27)&t;&t;/* power supply unit warning */
DECL|macro|KN02_CSR_NVRAM
mdefine_line|#define KN02_CSR_NVRAM&t;&t;(1&lt;&lt;26)&t;&t;/* ~NVRAM clear jumper */
DECL|macro|KN02_CSR_REFEVEN
mdefine_line|#define KN02_CSR_REFEVEN&t;(1&lt;&lt;25)&t;&t;/* mem refresh bank toggle */
DECL|macro|KN03_CSR_NRMOD
mdefine_line|#define KN03_CSR_NRMOD&t;&t;(1&lt;&lt;24)&t;&t;/* ~NRMOD manufact. jumper */
DECL|macro|KN03_CSR_IOINTEN
mdefine_line|#define KN03_CSR_IOINTEN&t;(0xff&lt;&lt;16)&t;/* IRQ mask bits */
DECL|macro|KN02_CSR_DIAGCHK
mdefine_line|#define KN02_CSR_DIAGCHK&t;(1&lt;&lt;15)&t;&t;/* diagn/norml ECC reads */
DECL|macro|KN02_CSR_DIAGGEN
mdefine_line|#define KN02_CSR_DIAGGEN&t;(1&lt;&lt;14)&t;&t;/* diagn/norml ECC writes */
DECL|macro|KN02_CSR_CORRECT
mdefine_line|#define KN02_CSR_CORRECT&t;(1&lt;&lt;13)&t;&t;/* ECC correct/check */
DECL|macro|KN02_CSR_LEDIAG
mdefine_line|#define KN02_CSR_LEDIAG&t;&t;(1&lt;&lt;12)&t;&t;/* ECC diagn. latch strobe */
DECL|macro|KN02_CSR_TXDIS
mdefine_line|#define KN02_CSR_TXDIS&t;&t;(1&lt;&lt;11)&t;&t;/* DZ11 transmit disable */
DECL|macro|KN02_CSR_BNK32M
mdefine_line|#define KN02_CSR_BNK32M&t;&t;(1&lt;&lt;10)&t;&t;/* 32M/8M stride */
DECL|macro|KN02_CSR_DIAGDN
mdefine_line|#define KN02_CSR_DIAGDN&t;&t;(1&lt;&lt;9)&t;&t;/* DIAGDN manufact. jumper */
DECL|macro|KN02_CSR_BAUD38
mdefine_line|#define KN02_CSR_BAUD38&t;&t;(1&lt;&lt;8)&t;&t;/* DZ11 38/19kbps ext. rate */
DECL|macro|KN03_CSR_IOINT
mdefine_line|#define KN03_CSR_IOINT&t;&t;(0xff&lt;&lt;0)&t;/* IRQ status bits (r/o) */
DECL|macro|KN03_CSR_LEDS
mdefine_line|#define KN03_CSR_LEDS&t;&t;(0xff&lt;&lt;0)&t;/* ~diagnostic LEDs (w/o) */
multiline_comment|/*&n; * CPU interrupt bits.&n; */
DECL|macro|KN02_CPU_INR_RES_6
mdefine_line|#define KN02_CPU_INR_RES_6&t;6&t;/* unused */
DECL|macro|KN02_CPU_INR_BUS
mdefine_line|#define KN02_CPU_INR_BUS&t;5&t;/* memory, I/O bus read/write errors */
DECL|macro|KN02_CPU_INR_RES_4
mdefine_line|#define KN02_CPU_INR_RES_4&t;4&t;/* unused */
DECL|macro|KN02_CPU_INR_RTC
mdefine_line|#define KN02_CPU_INR_RTC&t;3&t;/* DS1287 RTC */
DECL|macro|KN02_CPU_INR_CASCADE
mdefine_line|#define KN02_CPU_INR_CASCADE&t;2&t;/* CSR cascade */
multiline_comment|/*&n; * CSR interrupt bits.&n; */
DECL|macro|KN02_CSR_INR_DZ11
mdefine_line|#define KN02_CSR_INR_DZ11&t;7&t;/* DZ11 (DC7085) serial */
DECL|macro|KN02_CSR_INR_LANCE
mdefine_line|#define KN02_CSR_INR_LANCE&t;6&t;/* LANCE (Am7990) Ethernet */
DECL|macro|KN02_CSR_INR_ASC
mdefine_line|#define KN02_CSR_INR_ASC&t;5&t;/* ASC (NCR53C94) SCSI */
DECL|macro|KN02_CSR_INR_RES_4
mdefine_line|#define KN02_CSR_INR_RES_4&t;4&t;/* unused */
DECL|macro|KN02_CSR_INR_RES_3
mdefine_line|#define KN02_CSR_INR_RES_3&t;3&t;/* unused */
DECL|macro|KN02_CSR_INR_TC2
mdefine_line|#define KN02_CSR_INR_TC2&t;2&t;/* TURBOchannel slot #2 */
DECL|macro|KN02_CSR_INR_TC1
mdefine_line|#define KN02_CSR_INR_TC1&t;1&t;/* TURBOchannel slot #1 */
DECL|macro|KN02_CSR_INR_TC0
mdefine_line|#define KN02_CSR_INR_TC0&t;0&t;/* TURBOchannel slot #0 */
DECL|macro|KN02_IRQ_BASE
mdefine_line|#define KN02_IRQ_BASE&t;&t;8&t;/* first IRQ assigned to CSR */
DECL|macro|KN02_IRQ_LINES
mdefine_line|#define KN02_IRQ_LINES&t;&t;8&t;/* number of CSR interrupts */
DECL|macro|KN02_IRQ_NR
mdefine_line|#define KN02_IRQ_NR(n)&t;&t;((n) + KN02_IRQ_BASE)
DECL|macro|KN02_IRQ_MASK
mdefine_line|#define KN02_IRQ_MASK(n)&t;(1 &lt;&lt; (n))
DECL|macro|KN02_IRQ_ALL
mdefine_line|#define KN02_IRQ_ALL&t;&t;0xff
macro_line|#ifndef __ASSEMBLY__
r_extern
id|u32
id|cached_kn02_csr
suffix:semicolon
r_extern
id|spinlock_t
id|kn02_lock
suffix:semicolon
r_extern
r_void
id|init_kn02_irqs
c_func
(paren
r_int
id|base
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif /* __ASM_MIPS_DEC_KN02_H */
eof
