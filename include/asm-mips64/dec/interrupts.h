multiline_comment|/*&n; * Miscellaneous definitions used to initialise the interrupt vector table&n; * with the machine-specific interrupt routines.&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1997 by Paul M. Antoine.&n; * reworked 1998 by Harald Koerfgen.&n; * Copyright (C) 2001, 2002, 2003  Maciej W. Rozycki&n; */
macro_line|#ifndef __ASM_DEC_INTERRUPTS_H
DECL|macro|__ASM_DEC_INTERRUPTS_H
mdefine_line|#define __ASM_DEC_INTERRUPTS_H
macro_line|#include &lt;asm/mipsregs.h&gt;
multiline_comment|/*&n; * The list of possible system devices which provide an&n; * interrupt.  Not all devices exist on a given system.&n; */
DECL|macro|DEC_IRQ_CASCADE
mdefine_line|#define DEC_IRQ_CASCADE&t;&t;0&t;/* cascade from CSR or I/O ASIC */
multiline_comment|/* Ordinary interrupts */
DECL|macro|DEC_IRQ_AB_RECV
mdefine_line|#define DEC_IRQ_AB_RECV&t;&t;1&t;/* ACCESS.bus receive */
DECL|macro|DEC_IRQ_AB_XMIT
mdefine_line|#define DEC_IRQ_AB_XMIT&t;&t;2&t;/* ACCESS.bus transmit */
DECL|macro|DEC_IRQ_DZ11
mdefine_line|#define DEC_IRQ_DZ11&t;&t;3&t;/* DZ11 (DC7085) serial */
DECL|macro|DEC_IRQ_ASC
mdefine_line|#define DEC_IRQ_ASC&t;&t;4&t;/* ASC (NCR53C94) SCSI */
DECL|macro|DEC_IRQ_FLOPPY
mdefine_line|#define DEC_IRQ_FLOPPY&t;&t;5&t;/* 82077 FDC */
DECL|macro|DEC_IRQ_FPU
mdefine_line|#define DEC_IRQ_FPU&t;&t;6&t;/* R3k FPU */
DECL|macro|DEC_IRQ_HALT
mdefine_line|#define DEC_IRQ_HALT&t;&t;7&t;/* HALT button or from ACCESS.Bus */
DECL|macro|DEC_IRQ_ISDN
mdefine_line|#define DEC_IRQ_ISDN&t;&t;8&t;/* Am79C30A ISDN */
DECL|macro|DEC_IRQ_LANCE
mdefine_line|#define DEC_IRQ_LANCE&t;&t;9&t;/* LANCE (Am7990) Ethernet */
DECL|macro|DEC_IRQ_BUS
mdefine_line|#define DEC_IRQ_BUS&t;&t;10&t;/* memory, I/O bus read/write errors */
DECL|macro|DEC_IRQ_PSU
mdefine_line|#define DEC_IRQ_PSU&t;&t;11&t;/* power supply unit warning */
DECL|macro|DEC_IRQ_RTC
mdefine_line|#define DEC_IRQ_RTC&t;&t;12&t;/* DS1287 RTC */
DECL|macro|DEC_IRQ_SCC0
mdefine_line|#define DEC_IRQ_SCC0&t;&t;13&t;/* SCC (Z85C30) serial #0 */
DECL|macro|DEC_IRQ_SCC1
mdefine_line|#define DEC_IRQ_SCC1&t;&t;14&t;/* SCC (Z85C30) serial #1 */
DECL|macro|DEC_IRQ_SII
mdefine_line|#define DEC_IRQ_SII&t;&t;15&t;/* SII (DC7061) SCSI */
DECL|macro|DEC_IRQ_TC0
mdefine_line|#define DEC_IRQ_TC0&t;&t;16&t;/* TURBOchannel slot #0 */
DECL|macro|DEC_IRQ_TC1
mdefine_line|#define DEC_IRQ_TC1&t;&t;17&t;/* TURBOchannel slot #1 */
DECL|macro|DEC_IRQ_TC2
mdefine_line|#define DEC_IRQ_TC2&t;&t;18&t;/* TURBOchannel slot #2 */
DECL|macro|DEC_IRQ_TIMER
mdefine_line|#define DEC_IRQ_TIMER&t;&t;19&t;/* ARC periodic timer */
DECL|macro|DEC_IRQ_VIDEO
mdefine_line|#define DEC_IRQ_VIDEO&t;&t;20&t;/* framebuffer */
multiline_comment|/* I/O ASIC DMA interrupts */
DECL|macro|DEC_IRQ_ASC_MERR
mdefine_line|#define DEC_IRQ_ASC_MERR&t;21&t;/* ASC memory read error */
DECL|macro|DEC_IRQ_ASC_ERR
mdefine_line|#define DEC_IRQ_ASC_ERR&t;&t;22&t;/* ASC page overrun */
DECL|macro|DEC_IRQ_ASC_DMA
mdefine_line|#define DEC_IRQ_ASC_DMA&t;&t;23&t;/* ASC buffer pointer loaded */
DECL|macro|DEC_IRQ_FLOPPY_ERR
mdefine_line|#define DEC_IRQ_FLOPPY_ERR&t;24&t;/* FDC error */
DECL|macro|DEC_IRQ_ISDN_ERR
mdefine_line|#define DEC_IRQ_ISDN_ERR&t;25&t;/* ISDN memory read/overrun error */
DECL|macro|DEC_IRQ_ISDN_RXDMA
mdefine_line|#define DEC_IRQ_ISDN_RXDMA&t;26&t;/* ISDN recv buffer pointer loaded */
DECL|macro|DEC_IRQ_ISDN_TXDMA
mdefine_line|#define DEC_IRQ_ISDN_TXDMA&t;27&t;/* ISDN xmit buffer pointer loaded */
DECL|macro|DEC_IRQ_LANCE_MERR
mdefine_line|#define DEC_IRQ_LANCE_MERR&t;28&t;/* LANCE memory read error */
DECL|macro|DEC_IRQ_SCC0A_RXERR
mdefine_line|#define DEC_IRQ_SCC0A_RXERR&t;29&t;/* SCC0A (printer) receive overrun */
DECL|macro|DEC_IRQ_SCC0A_RXDMA
mdefine_line|#define DEC_IRQ_SCC0A_RXDMA&t;30&t;/* SCC0A receive half page */
DECL|macro|DEC_IRQ_SCC0A_TXERR
mdefine_line|#define DEC_IRQ_SCC0A_TXERR&t;31&t;/* SCC0A xmit memory read/overrun */
DECL|macro|DEC_IRQ_SCC0A_TXDMA
mdefine_line|#define DEC_IRQ_SCC0A_TXDMA&t;32&t;/* SCC0A transmit page end */
DECL|macro|DEC_IRQ_AB_RXERR
mdefine_line|#define DEC_IRQ_AB_RXERR&t;33&t;/* ACCESS.bus receive overrun */
DECL|macro|DEC_IRQ_AB_RXDMA
mdefine_line|#define DEC_IRQ_AB_RXDMA&t;34&t;/* ACCESS.bus receive half page */
DECL|macro|DEC_IRQ_AB_TXERR
mdefine_line|#define DEC_IRQ_AB_TXERR&t;35&t;/* ACCESS.bus xmit memory read/ovrn */
DECL|macro|DEC_IRQ_AB_TXDMA
mdefine_line|#define DEC_IRQ_AB_TXDMA&t;36&t;/* ACCESS.bus transmit page end */
DECL|macro|DEC_IRQ_SCC1A_RXERR
mdefine_line|#define DEC_IRQ_SCC1A_RXERR&t;37&t;/* SCC1A (modem) receive overrun */
DECL|macro|DEC_IRQ_SCC1A_RXDMA
mdefine_line|#define DEC_IRQ_SCC1A_RXDMA&t;38&t;/* SCC1A receive half page */
DECL|macro|DEC_IRQ_SCC1A_TXERR
mdefine_line|#define DEC_IRQ_SCC1A_TXERR&t;39&t;/* SCC1A xmit memory read/overrun */
DECL|macro|DEC_IRQ_SCC1A_TXDMA
mdefine_line|#define DEC_IRQ_SCC1A_TXDMA&t;40&t;/* SCC1A transmit page end */
multiline_comment|/* TC5 &amp; TC6 are virtual slots for KN02&squot;s onboard devices */
DECL|macro|DEC_IRQ_TC5
mdefine_line|#define DEC_IRQ_TC5&t;&t;DEC_IRQ_ASC&t;/* virtual PMAZ-AA */
DECL|macro|DEC_IRQ_TC6
mdefine_line|#define DEC_IRQ_TC6&t;&t;DEC_IRQ_LANCE&t;/* virtual PMAD-AA */
DECL|macro|DEC_NR_INTS
mdefine_line|#define DEC_NR_INTS&t;&t;41
multiline_comment|/* Largest of cpu mask_nr tables. */
DECL|macro|DEC_MAX_CPU_INTS
mdefine_line|#define DEC_MAX_CPU_INTS&t;6
multiline_comment|/* Largest of asic mask_nr tables. */
DECL|macro|DEC_MAX_ASIC_INTS
mdefine_line|#define DEC_MAX_ASIC_INTS&t;9
multiline_comment|/*&n; * CPU interrupt bits common to all systems.&n; */
DECL|macro|DEC_CPU_INR_FPU
mdefine_line|#define DEC_CPU_INR_FPU&t;&t;7&t;/* R3k FPU */
DECL|macro|DEC_CPU_INR_SW1
mdefine_line|#define DEC_CPU_INR_SW1&t;&t;1&t;/* software #1 */
DECL|macro|DEC_CPU_INR_SW0
mdefine_line|#define DEC_CPU_INR_SW0&t;&t;0&t;/* software #0 */
DECL|macro|DEC_CPU_IRQ_BASE
mdefine_line|#define DEC_CPU_IRQ_BASE&t;0&t;/* first IRQ assigned to CPU */
DECL|macro|DEC_CPU_IRQ_NR
mdefine_line|#define DEC_CPU_IRQ_NR(n)&t;((n) + DEC_CPU_IRQ_BASE)
DECL|macro|DEC_CPU_IRQ_MASK
mdefine_line|#define DEC_CPU_IRQ_MASK(n)&t;(1 &lt;&lt; ((n) + CAUSEB_IP))
DECL|macro|DEC_CPU_IRQ_ALL
mdefine_line|#define DEC_CPU_IRQ_ALL&t;&t;(0xff &lt;&lt; CAUSEB_IP)
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * Interrupt table structures to hide differences between systems.&n; */
DECL|member|i
DECL|member|p
DECL|typedef|int_ptr
r_typedef
r_union
(brace
r_int
id|i
suffix:semicolon
r_void
op_star
id|p
suffix:semicolon
)brace
id|int_ptr
suffix:semicolon
r_extern
r_int
id|dec_interrupt
(braket
id|DEC_NR_INTS
)braket
suffix:semicolon
r_extern
id|int_ptr
id|cpu_mask_nr_tbl
(braket
id|DEC_MAX_CPU_INTS
)braket
(braket
l_int|2
)braket
suffix:semicolon
r_extern
id|int_ptr
id|asic_mask_nr_tbl
(braket
id|DEC_MAX_ASIC_INTS
)braket
(braket
l_int|2
)braket
suffix:semicolon
r_extern
r_int
id|cpu_fpu_mask
suffix:semicolon
multiline_comment|/*&n; * Common interrupt routine prototypes for all DECStations&n; */
r_extern
r_void
id|kn02_io_int
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|kn02xa_io_int
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|kn03_io_int
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|asic_dma_int
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|asic_all_int
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|kn02_all_int
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|cpu_all_int
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|dec_intr_unimplemented
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|asic_intr_unimplemented
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif
eof
