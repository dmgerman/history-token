multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Definitions for the interrupt related bits in the I/O ASIC&n; * interrupt status register (and the interrupt mask register, of course)&n; *&n; * Created with Information from:&n; *&n; * &quot;DEC 3000 300/400/500/600/700/800/900 AXP Models System Programmer&squot;s Manual&quot;&n; *&n; * and the Mach Sources&n; *&n; * Copyright (C) 199x  the Anonymous&n; * Copyright (C) 2002  Maciej W. Rozycki&n; */
macro_line|#ifndef __ASM_DEC_IOASIC_INTS_H
DECL|macro|__ASM_DEC_IOASIC_INTS_H
mdefine_line|#define __ASM_DEC_IOASIC_INTS_H
multiline_comment|/*&n; * The upper 16 bits are a part of the I/O ASIC&squot;s internal DMA engine&n; * and thus are common to all I/O ASIC machines.  The exception is&n; * the Maxine, which makes use of the FLOPPY and ISDN bits (otherwise&n; * unused) and has a different SCC wiring.&n; */
multiline_comment|/* all systems */
DECL|macro|IO_INR_SCC0A_TXDMA
mdefine_line|#define IO_INR_SCC0A_TXDMA&t;31&t;/* SCC0A transmit page end */
DECL|macro|IO_INR_SCC0A_TXERR
mdefine_line|#define IO_INR_SCC0A_TXERR&t;30&t;/* SCC0A transmit memory read error */
DECL|macro|IO_INR_SCC0A_RXDMA
mdefine_line|#define IO_INR_SCC0A_RXDMA&t;29&t;/* SCC0A receive half page */
DECL|macro|IO_INR_SCC0A_RXERR
mdefine_line|#define IO_INR_SCC0A_RXERR&t;28&t;/* SCC0A receive overrun */
DECL|macro|IO_INR_ASC_DMA
mdefine_line|#define IO_INR_ASC_DMA&t;&t;19&t;/* ASC buffer pointer loaded */
DECL|macro|IO_INR_ASC_ERR
mdefine_line|#define IO_INR_ASC_ERR&t;&t;18&t;/* ASC page overrun */
DECL|macro|IO_INR_ASC_MERR
mdefine_line|#define IO_INR_ASC_MERR&t;&t;17&t;/* ASC memory read error */
DECL|macro|IO_INR_LANCE_MERR
mdefine_line|#define IO_INR_LANCE_MERR&t;16&t;/* LANCE memory read error */
multiline_comment|/* except Maxine */
DECL|macro|IO_INR_SCC1A_TXDMA
mdefine_line|#define IO_INR_SCC1A_TXDMA&t;27&t;/* SCC1A transmit page end */
DECL|macro|IO_INR_SCC1A_TXERR
mdefine_line|#define IO_INR_SCC1A_TXERR&t;26&t;/* SCC1A transmit memory read error */
DECL|macro|IO_INR_SCC1A_RXDMA
mdefine_line|#define IO_INR_SCC1A_RXDMA&t;25&t;/* SCC1A receive half page */
DECL|macro|IO_INR_SCC1A_RXERR
mdefine_line|#define IO_INR_SCC1A_RXERR&t;24&t;/* SCC1A receive overrun */
DECL|macro|IO_INR_RES_23
mdefine_line|#define IO_INR_RES_23&t;&t;23&t;/* unused */
DECL|macro|IO_INR_RES_22
mdefine_line|#define IO_INR_RES_22&t;&t;22&t;/* unused */
DECL|macro|IO_INR_RES_21
mdefine_line|#define IO_INR_RES_21&t;&t;21&t;/* unused */
DECL|macro|IO_INR_RES_20
mdefine_line|#define IO_INR_RES_20&t;&t;20&t;/* unused */
multiline_comment|/* Maxine */
DECL|macro|IO_INR_AB_TXDMA
mdefine_line|#define IO_INR_AB_TXDMA&t;&t;27&t;/* ACCESS.bus transmit page end */
DECL|macro|IO_INR_AB_TXERR
mdefine_line|#define IO_INR_AB_TXERR&t;&t;26&t;/* ACCESS.bus xmit memory read error */
DECL|macro|IO_INR_AB_RXDMA
mdefine_line|#define IO_INR_AB_RXDMA&t;&t;25&t;/* ACCESS.bus receive half page */
DECL|macro|IO_INR_AB_RXERR
mdefine_line|#define IO_INR_AB_RXERR&t;&t;24&t;/* ACCESS.bus receive overrun */
DECL|macro|IO_INR_FLOPPY_ERR
mdefine_line|#define IO_INR_FLOPPY_ERR&t;23&t;/* FDC error */
DECL|macro|IO_INR_ISDN_TXDMA
mdefine_line|#define IO_INR_ISDN_TXDMA&t;22&t;/* ISDN xmit buffer pointer loaded */
DECL|macro|IO_INR_ISDN_RXDMA
mdefine_line|#define IO_INR_ISDN_RXDMA&t;21&t;/* ISDN recv buffer pointer loaded */
DECL|macro|IO_INR_ISDN_ERR
mdefine_line|#define IO_INR_ISDN_ERR&t;&t;20&t;/* ISDN memory read/overrun error */
DECL|macro|IO_INR_DMA
mdefine_line|#define IO_INR_DMA&t;&t;16&t;/* first DMA IRQ */
multiline_comment|/*&n; * The lower 16 bits are system-specific and thus defined in&n; * system-specific headers.&n; */
DECL|macro|IO_IRQ_BASE
mdefine_line|#define IO_IRQ_BASE&t;&t;8&t;/* first IRQ assigned to I/O ASIC */
DECL|macro|IO_IRQ_LINES
mdefine_line|#define IO_IRQ_LINES&t;&t;32&t;/* number of I/O ASIC interrupts */
DECL|macro|IO_IRQ_NR
mdefine_line|#define IO_IRQ_NR(n)&t;&t;((n) + IO_IRQ_BASE)
DECL|macro|IO_IRQ_MASK
mdefine_line|#define IO_IRQ_MASK(n)&t;&t;(1 &lt;&lt; (n))
DECL|macro|IO_IRQ_ALL
mdefine_line|#define IO_IRQ_ALL&t;&t;0x0000ffff
DECL|macro|IO_IRQ_DMA
mdefine_line|#define IO_IRQ_DMA&t;&t;0xffff0000
macro_line|#endif /* __ASM_DEC_IOASIC_INTS_H */
eof
