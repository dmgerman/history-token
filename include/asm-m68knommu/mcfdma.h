multiline_comment|/****************************************************************************/
multiline_comment|/*&n; *&t;mcfdma.h -- Coldfire internal DMA support defines.&n; *&n; *&t;(C) Copyright 1999, Rob Scott (rscott@mtrob.ml.org)&n; */
multiline_comment|/****************************************************************************/
macro_line|#ifndef&t;mcfdma_h
DECL|macro|mcfdma_h
mdefine_line|#define&t;mcfdma_h
multiline_comment|/****************************************************************************/
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; *&t;Get address specific defines for this Coldfire member.&n; */
macro_line|#if defined(CONFIG_M5206) || defined(CONFIG_M5206e)
DECL|macro|MCFDMA_BASE0
mdefine_line|#define&t;MCFDMA_BASE0&t;&t;0x200&t;&t;/* Base address of DMA 0 */
DECL|macro|MCFDMA_BASE1
mdefine_line|#define&t;MCFDMA_BASE1&t;&t;0x240&t;&t;/* Base address of DMA 1 */
macro_line|#elif defined(CONFIG_M5272)
DECL|macro|MCFDMA_BASE0
mdefine_line|#define&t;MCFDMA_BASE0&t;&t;0x0e0&t;&t;/* Base address of DMA 0 */
macro_line|#elif defined(CONFIG_M527x) || defined(CONFIG_M528x)
multiline_comment|/* These are relative to the IPSBAR, not MBAR */
DECL|macro|MCFDMA_BASE0
mdefine_line|#define&t;MCFDMA_BASE0&t;&t;0x100&t;&t;/* Base address of DMA 0 */
DECL|macro|MCFDMA_BASE1
mdefine_line|#define&t;MCFDMA_BASE1&t;&t;0x140&t;&t;/* Base address of DMA 1 */
DECL|macro|MCFDMA_BASE2
mdefine_line|#define&t;MCFDMA_BASE2&t;&t;0x180&t;&t;/* Base address of DMA 2 */
DECL|macro|MCFDMA_BASE3
mdefine_line|#define&t;MCFDMA_BASE3&t;&t;0x1C0&t;&t;/* Base address of DMA 3 */
macro_line|#elif defined(CONFIG_M5249) || defined(CONFIG_M5307) || defined(CONFIG_M5407)
DECL|macro|MCFDMA_BASE0
mdefine_line|#define&t;MCFDMA_BASE0&t;&t;0x300&t;&t;/* Base address of DMA 0 */
DECL|macro|MCFDMA_BASE1
mdefine_line|#define&t;MCFDMA_BASE1&t;&t;0x340&t;&t;/* Base address of DMA 1 */
DECL|macro|MCFDMA_BASE2
mdefine_line|#define&t;MCFDMA_BASE2&t;&t;0x380&t;&t;/* Base address of DMA 2 */
DECL|macro|MCFDMA_BASE3
mdefine_line|#define&t;MCFDMA_BASE3&t;&t;0x3C0&t;&t;/* Base address of DMA 3 */
macro_line|#endif
macro_line|#if !defined(CONFIG_M5272)
multiline_comment|/*&n; *&t;Define the DMA register set addresses.&n; *      Note: these are longword registers, use unsigned long as data type&n; */
DECL|macro|MCFDMA_SAR
mdefine_line|#define&t;MCFDMA_SAR&t;&t;0x00&t;&t;/* DMA source address (r/w) */
DECL|macro|MCFDMA_DAR
mdefine_line|#define&t;MCFDMA_DAR&t;&t;0x01&t;&t;/* DMA destination adr (r/w) */
multiline_comment|/* these are word registers, use unsigned short data type */
DECL|macro|MCFDMA_DCR
mdefine_line|#define&t;MCFDMA_DCR&t;&t;0x04&t;&t;/* DMA control reg (r/w) */
DECL|macro|MCFDMA_BCR
mdefine_line|#define&t;MCFDMA_BCR&t;&t;0x06&t;&t;/* DMA byte count reg (r/w) */
multiline_comment|/* these are byte registers, use unsiged char data type */
DECL|macro|MCFDMA_DSR
mdefine_line|#define&t;MCFDMA_DSR&t;&t;0x10&t;&t;/* DMA status reg (r/w) */
DECL|macro|MCFDMA_DIVR
mdefine_line|#define&t;MCFDMA_DIVR&t;&t;0x14&t;&t;/* DMA interrupt vec (r/w) */
multiline_comment|/*&n; *&t;Bit definitions for the DMA Control Register (DCR).&n; */
DECL|macro|MCFDMA_DCR_INT
mdefine_line|#define&t;MCFDMA_DCR_INT&t;        0x8000&t;&t;/* Enable completion irq */
DECL|macro|MCFDMA_DCR_EEXT
mdefine_line|#define&t;MCFDMA_DCR_EEXT&t;        0x4000&t;&t;/* Enable external DMA req */
DECL|macro|MCFDMA_DCR_CS
mdefine_line|#define&t;MCFDMA_DCR_CS &t;        0x2000&t;&t;/* Enable cycle steal */
DECL|macro|MCFDMA_DCR_AA
mdefine_line|#define&t;MCFDMA_DCR_AA   &t;0x1000&t;&t;/* Enable auto alignment */
DECL|macro|MCFDMA_DCR_BWC_MASK
mdefine_line|#define&t;MCFDMA_DCR_BWC_MASK  &t;0x0E00&t;&t;/* Bandwidth ctl mask */
DECL|macro|MCFDMA_DCR_BWC_512
mdefine_line|#define MCFDMA_DCR_BWC_512      0x0200          /* Bandwidth:   512 Bytes */
DECL|macro|MCFDMA_DCR_BWC_1024
mdefine_line|#define MCFDMA_DCR_BWC_1024     0x0400          /* Bandwidth:  1024 Bytes */
DECL|macro|MCFDMA_DCR_BWC_2048
mdefine_line|#define MCFDMA_DCR_BWC_2048     0x0600          /* Bandwidth:  2048 Bytes */
DECL|macro|MCFDMA_DCR_BWC_4096
mdefine_line|#define MCFDMA_DCR_BWC_4096     0x0800          /* Bandwidth:  4096 Bytes */
DECL|macro|MCFDMA_DCR_BWC_8192
mdefine_line|#define MCFDMA_DCR_BWC_8192     0x0a00          /* Bandwidth:  8192 Bytes */
DECL|macro|MCFDMA_DCR_BWC_16384
mdefine_line|#define MCFDMA_DCR_BWC_16384    0x0c00          /* Bandwidth: 16384 Bytes */
DECL|macro|MCFDMA_DCR_BWC_32768
mdefine_line|#define MCFDMA_DCR_BWC_32768    0x0e00          /* Bandwidth: 32768 Bytes */
DECL|macro|MCFDMA_DCR_SAA
mdefine_line|#define&t;MCFDMA_DCR_SAA         &t;0x0100&t;&t;/* Single Address Access */
DECL|macro|MCFDMA_DCR_S_RW
mdefine_line|#define&t;MCFDMA_DCR_S_RW        &t;0x0080&t;&t;/* SAA read/write value */
DECL|macro|MCFDMA_DCR_SINC
mdefine_line|#define&t;MCFDMA_DCR_SINC        &t;0x0040&t;&t;/* Source addr inc enable */
DECL|macro|MCFDMA_DCR_SSIZE_MASK
mdefine_line|#define&t;MCFDMA_DCR_SSIZE_MASK  &t;0x0030&t;&t;/* Src xfer size */
DECL|macro|MCFDMA_DCR_SSIZE_LONG
mdefine_line|#define&t;MCFDMA_DCR_SSIZE_LONG  &t;0x0000&t;&t;/* Src xfer size, 00 = longw */
DECL|macro|MCFDMA_DCR_SSIZE_BYTE
mdefine_line|#define&t;MCFDMA_DCR_SSIZE_BYTE  &t;0x0010&t;&t;/* Src xfer size, 01 = byte */
DECL|macro|MCFDMA_DCR_SSIZE_WORD
mdefine_line|#define&t;MCFDMA_DCR_SSIZE_WORD  &t;0x0020&t;&t;/* Src xfer size, 10 = word */
DECL|macro|MCFDMA_DCR_SSIZE_LINE
mdefine_line|#define&t;MCFDMA_DCR_SSIZE_LINE  &t;0x0030&t;&t;/* Src xfer size, 11 = line */
DECL|macro|MCFDMA_DCR_DINC
mdefine_line|#define&t;MCFDMA_DCR_DINC        &t;0x0008&t;&t;/* Dest addr inc enable */
DECL|macro|MCFDMA_DCR_DSIZE_MASK
mdefine_line|#define&t;MCFDMA_DCR_DSIZE_MASK  &t;0x0006&t;&t;/* Dest xfer size */
DECL|macro|MCFDMA_DCR_DSIZE_LONG
mdefine_line|#define&t;MCFDMA_DCR_DSIZE_LONG  &t;0x0000&t;&t;/* Dest xfer size, 00 = long */
DECL|macro|MCFDMA_DCR_DSIZE_BYTE
mdefine_line|#define&t;MCFDMA_DCR_DSIZE_BYTE  &t;0x0002&t;&t;/* Dest xfer size, 01 = byte */
DECL|macro|MCFDMA_DCR_DSIZE_WORD
mdefine_line|#define&t;MCFDMA_DCR_DSIZE_WORD  &t;0x0004&t;&t;/* Dest xfer size, 10 = word */
DECL|macro|MCFDMA_DCR_DSIZE_LINE
mdefine_line|#define&t;MCFDMA_DCR_DSIZE_LINE  &t;0x0006&t;&t;/* Dest xfer size, 11 = line */
DECL|macro|MCFDMA_DCR_START
mdefine_line|#define&t;MCFDMA_DCR_START       &t;0x0001&t;&t;/* Start transfer */
multiline_comment|/*&n; *&t;Bit definitions for the DMA Status Register (DSR).&n; */
DECL|macro|MCFDMA_DSR_CE
mdefine_line|#define&t;MCFDMA_DSR_CE&t;        0x40&t;&t;/* Config error */
DECL|macro|MCFDMA_DSR_BES
mdefine_line|#define&t;MCFDMA_DSR_BES&t;        0x20&t;&t;/* Bus Error on source */
DECL|macro|MCFDMA_DSR_BED
mdefine_line|#define&t;MCFDMA_DSR_BED &t;        0x10&t;&t;/* Bus Error on dest */
DECL|macro|MCFDMA_DSR_REQ
mdefine_line|#define&t;MCFDMA_DSR_REQ   &t;0x04&t;&t;/* Requests remaining */
DECL|macro|MCFDMA_DSR_BSY
mdefine_line|#define&t;MCFDMA_DSR_BSY  &t;0x02&t;&t;/* Busy */
DECL|macro|MCFDMA_DSR_DONE
mdefine_line|#define&t;MCFDMA_DSR_DONE        &t;0x01&t;&t;/* DMA transfer complete */
macro_line|#else /* This is an MCF5272 */
DECL|macro|MCFDMA_DMR
mdefine_line|#define MCFDMA_DMR        0x00    /* Mode Register (r/w) */
DECL|macro|MCFDMA_DIR
mdefine_line|#define MCFDMA_DIR        0x03    /* Interrupt trigger register (r/w) */
DECL|macro|MCFDMA_DSAR
mdefine_line|#define MCFDMA_DSAR       0x03    /* Source Address register (r/w) */
DECL|macro|MCFDMA_DDAR
mdefine_line|#define MCFDMA_DDAR       0x04    /* Destination Address register (r/w) */
DECL|macro|MCFDMA_DBCR
mdefine_line|#define MCFDMA_DBCR       0x02    /* Byte Count Register (r/w) */
multiline_comment|/* Bit definitions for the DMA Mode Register (DMR) */
DECL|macro|MCFDMA_DMR_RESET
mdefine_line|#define MCFDMA_DMR_RESET     0x80000000L /* Reset bit */
DECL|macro|MCFDMA_DMR_EN
mdefine_line|#define MCFDMA_DMR_EN        0x40000000L /* DMA enable */
DECL|macro|MCFDMA_DMR_RQM
mdefine_line|#define MCFDMA_DMR_RQM       0x000C0000L /* Request Mode Mask */
DECL|macro|MCFDMA_DMR_RQM_DUAL
mdefine_line|#define MCFDMA_DMR_RQM_DUAL  0x000C0000L /* Dual address mode, the only valid mode */
DECL|macro|MCFDMA_DMR_DSTM
mdefine_line|#define MCFDMA_DMR_DSTM      0x00002000L /* Destination addressing mask */
DECL|macro|MCFDMA_DMR_DSTM_SA
mdefine_line|#define MCFDMA_DMR_DSTM_SA   0x00000000L /* Destination uses static addressing */
DECL|macro|MCFDMA_DMR_DSTM_IA
mdefine_line|#define MCFDMA_DMR_DSTM_IA   0x00002000L /* Destination uses incremental addressing */
DECL|macro|MCFDMA_DMR_DSTT_UD
mdefine_line|#define MCFDMA_DMR_DSTT_UD   0x00000400L /* Destination is user data */
DECL|macro|MCFDMA_DMR_DSTT_UC
mdefine_line|#define MCFDMA_DMR_DSTT_UC   0x00000800L /* Destination is user code */
DECL|macro|MCFDMA_DMR_DSTT_SD
mdefine_line|#define MCFDMA_DMR_DSTT_SD   0x00001400L /* Destination is supervisor data */
DECL|macro|MCFDMA_DMR_DSTT_SC
mdefine_line|#define MCFDMA_DMR_DSTT_SC   0x00001800L /* Destination is supervisor code */
DECL|macro|MCFDMA_DMR_DSTS_OFF
mdefine_line|#define MCFDMA_DMR_DSTS_OFF  0x8         /* offset to the destination size bits */
DECL|macro|MCFDMA_DMR_DSTS_LONG
mdefine_line|#define MCFDMA_DMR_DSTS_LONG 0x00000000L /* Long destination size */
DECL|macro|MCFDMA_DMR_DSTS_BYTE
mdefine_line|#define MCFDMA_DMR_DSTS_BYTE 0x00000100L /* Byte destination size */
DECL|macro|MCFDMA_DMR_DSTS_WORD
mdefine_line|#define MCFDMA_DMR_DSTS_WORD 0x00000200L /* Word destination size */
DECL|macro|MCFDMA_DMR_DSTS_LINE
mdefine_line|#define MCFDMA_DMR_DSTS_LINE 0x00000300L /* Line destination size */
DECL|macro|MCFDMA_DMR_SRCM
mdefine_line|#define MCFDMA_DMR_SRCM      0x00000020L /* Source addressing mask */
DECL|macro|MCFDMA_DMR_SRCM_SA
mdefine_line|#define MCFDMA_DMR_SRCM_SA   0x00000000L /* Source uses static addressing */
DECL|macro|MCFDMA_DMR_SRCM_IA
mdefine_line|#define MCFDMA_DMR_SRCM_IA   0x00000020L /* Source uses incremental addressing */
DECL|macro|MCFDMA_DMR_SRCT_UD
mdefine_line|#define MCFDMA_DMR_SRCT_UD   0x00000004L /* Source is user data */
DECL|macro|MCFDMA_DMR_SRCT_UC
mdefine_line|#define MCFDMA_DMR_SRCT_UC   0x00000008L /* Source is user code */
DECL|macro|MCFDMA_DMR_SRCT_SD
mdefine_line|#define MCFDMA_DMR_SRCT_SD   0x00000014L /* Source is supervisor data */
DECL|macro|MCFDMA_DMR_SRCT_SC
mdefine_line|#define MCFDMA_DMR_SRCT_SC   0x00000018L /* Source is supervisor code */
DECL|macro|MCFDMA_DMR_SRCS_OFF
mdefine_line|#define MCFDMA_DMR_SRCS_OFF  0x0         /* Offset to the source size bits */
DECL|macro|MCFDMA_DMR_SRCS_LONG
mdefine_line|#define MCFDMA_DMR_SRCS_LONG 0x00000000L /* Long source size */
DECL|macro|MCFDMA_DMR_SRCS_BYTE
mdefine_line|#define MCFDMA_DMR_SRCS_BYTE 0x00000001L /* Byte source size */
DECL|macro|MCFDMA_DMR_SRCS_WORD
mdefine_line|#define MCFDMA_DMR_SRCS_WORD 0x00000002L /* Word source size */
DECL|macro|MCFDMA_DMR_SRCS_LINE
mdefine_line|#define MCFDMA_DMR_SRCS_LINE 0x00000003L /* Line source size */
multiline_comment|/* Bit definitions for the DMA interrupt register (DIR) */
DECL|macro|MCFDMA_DIR_INVEN
mdefine_line|#define MCFDMA_DIR_INVEN     0x1000 /* Invalid Combination interrupt enable */
DECL|macro|MCFDMA_DIR_ASCEN
mdefine_line|#define MCFDMA_DIR_ASCEN     0x0800 /* Address Sequence Complete (Completion) interrupt enable */
DECL|macro|MCFDMA_DIR_TEEN
mdefine_line|#define MCFDMA_DIR_TEEN      0x0200 /* Transfer Error interrupt enable */
DECL|macro|MCFDMA_DIR_TCEN
mdefine_line|#define MCFDMA_DIR_TCEN      0x0100 /* Transfer Complete (a bus transfer, that is) interrupt enable */
DECL|macro|MCFDMA_DIR_INV
mdefine_line|#define MCFDMA_DIR_INV       0x1000 /* Invalid Combination */
DECL|macro|MCFDMA_DIR_ASC
mdefine_line|#define MCFDMA_DIR_ASC       0x0008 /* Address Sequence Complete (DMA Completion) */
DECL|macro|MCFDMA_DIR_TE
mdefine_line|#define MCFDMA_DIR_TE        0x0002 /* Transfer Error */
DECL|macro|MCFDMA_DIR_TC
mdefine_line|#define MCFDMA_DIR_TC        0x0001 /* Transfer Complete */
macro_line|#endif /* !defined(CONFIG_M5272) */ 
multiline_comment|/****************************************************************************/
macro_line|#endif&t;/* mcfdma_h */
eof
