macro_line|#ifndef __ASM_SH_DMA_H
DECL|macro|__ASM_SH_DMA_H
mdefine_line|#define __ASM_SH_DMA_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/io.h&gt;&t;&t;/* need byte IO */
DECL|macro|MAX_DMA_CHANNELS
mdefine_line|#define MAX_DMA_CHANNELS 8
DECL|macro|SH_MAX_DMA_CHANNELS
mdefine_line|#define SH_MAX_DMA_CHANNELS 4
multiline_comment|/* The maximum address that we can perform a DMA transfer to on this platform */
multiline_comment|/* Don&squot;t define MAX_DMA_ADDRESS; it&squot;s useless on the SuperH and any&n;   occurrence should be flagged as an error.  */
multiline_comment|/* But... */
multiline_comment|/* XXX: This is not applicable to SuperH, just needed for alloc_bootmem */
DECL|macro|MAX_DMA_ADDRESS
mdefine_line|#define MAX_DMA_ADDRESS      (PAGE_OFFSET+0x10000000)
macro_line|#if defined(__sh3__)
DECL|macro|SAR
mdefine_line|#define SAR ((unsigned long[]){0xa4000020,0xa4000030,0xa4000040,0xa4000050})
DECL|macro|DAR
mdefine_line|#define DAR ((unsigned long[]){0xa4000024,0xa4000034,0xa4000044,0xa4000054})
DECL|macro|DMATCR
mdefine_line|#define DMATCR ((unsigned long[]){0xa4000028,0xa4000038,0xa4000048,0xa4000058})
DECL|macro|CHCR
mdefine_line|#define CHCR ((unsigned long[]){0xa400002c,0xa400003c,0xa400004c,0xa400005c})
DECL|macro|DMAOR
mdefine_line|#define DMAOR 0xa4000060UL
macro_line|#elif defined(__SH4__)
DECL|macro|SAR
mdefine_line|#define SAR ((unsigned long[]){0xbfa00000,0xbfa00010,0xbfa00020,0xbfa00030})
DECL|macro|DAR
mdefine_line|#define DAR ((unsigned long[]){0xbfa00004,0xbfa00014,0xbfa00024,0xbfa00034})
DECL|macro|DMATCR
mdefine_line|#define DMATCR ((unsigned long[]){0xbfa00008,0xbfa00018,0xbfa00028,0xbfa00038})
DECL|macro|CHCR
mdefine_line|#define CHCR ((unsigned long[]){0xbfa0000c,0xbfa0001c,0xbfa0002c,0xbfa0003c})
DECL|macro|DMAOR
mdefine_line|#define DMAOR 0xbfa00040UL
macro_line|#endif
DECL|macro|DMTE_IRQ
mdefine_line|#define DMTE_IRQ ((int[]){DMTE0_IRQ,DMTE1_IRQ,DMTE2_IRQ,DMTE3_IRQ})
DECL|macro|DMA_MODE_READ
mdefine_line|#define DMA_MODE_READ&t;0x00&t;/* I/O to memory, no autoinit, increment, single mode */
DECL|macro|DMA_MODE_WRITE
mdefine_line|#define DMA_MODE_WRITE&t;0x01&t;/* memory to I/O, no autoinit, increment, single mode */
DECL|macro|DMA_AUTOINIT
mdefine_line|#define DMA_AUTOINIT&t;0x10
DECL|macro|REQ_L
mdefine_line|#define REQ_L&t;0x00000000
DECL|macro|REQ_E
mdefine_line|#define REQ_E&t;0x00080000
DECL|macro|RACK_H
mdefine_line|#define RACK_H&t;0x00000000
DECL|macro|RACK_L
mdefine_line|#define RACK_L&t;0x00040000
DECL|macro|ACK_R
mdefine_line|#define ACK_R&t;0x00000000
DECL|macro|ACK_W
mdefine_line|#define ACK_W&t;0x00020000
DECL|macro|ACK_H
mdefine_line|#define ACK_H&t;0x00000000
DECL|macro|ACK_L
mdefine_line|#define ACK_L&t;0x00010000
DECL|macro|DM_INC
mdefine_line|#define DM_INC&t;0x00004000
DECL|macro|DM_DEC
mdefine_line|#define DM_DEC&t;0x00008000
DECL|macro|SM_INC
mdefine_line|#define SM_INC&t;0x00001000
DECL|macro|SM_DEC
mdefine_line|#define SM_DEC&t;0x00002000
DECL|macro|RS_DUAL
mdefine_line|#define RS_DUAL&t;0x00000000
DECL|macro|RS_IN
mdefine_line|#define RS_IN&t;0x00000200
DECL|macro|RS_OUT
mdefine_line|#define RS_OUT&t;0x00000300
DECL|macro|TM_BURST
mdefine_line|#define TM_BURST 0x0000080
DECL|macro|TS_8
mdefine_line|#define TS_8&t;0x00000010
DECL|macro|TS_16
mdefine_line|#define TS_16&t;0x00000020
DECL|macro|TS_32
mdefine_line|#define TS_32&t;0x00000030
DECL|macro|TS_64
mdefine_line|#define TS_64&t;0x00000000
DECL|macro|TS_BLK
mdefine_line|#define TS_BLK&t;0x00000040
DECL|macro|CHCR_DE
mdefine_line|#define CHCR_DE 0x00000001
DECL|macro|CHCR_TE
mdefine_line|#define CHCR_TE 0x00000002
DECL|macro|CHCR_IE
mdefine_line|#define CHCR_IE 0x00000004
DECL|macro|DMAOR_COD
mdefine_line|#define DMAOR_COD&t;0x00000008
DECL|macro|DMAOR_AE
mdefine_line|#define DMAOR_AE&t;0x00000004
DECL|macro|DMAOR_NMIF
mdefine_line|#define DMAOR_NMIF&t;0x00000002
DECL|macro|DMAOR_DME
mdefine_line|#define DMAOR_DME&t;0x00000001
DECL|struct|dma_info_t
r_struct
id|dma_info_t
(brace
DECL|member|chan
r_int
r_int
id|chan
suffix:semicolon
DECL|member|mode_read
r_int
r_int
id|mode_read
suffix:semicolon
DECL|member|mode_write
r_int
r_int
id|mode_write
suffix:semicolon
DECL|member|dev_addr
r_int
r_int
id|dev_addr
suffix:semicolon
DECL|member|mode
r_int
r_int
id|mode
suffix:semicolon
DECL|member|mem_addr
r_int
r_int
id|mem_addr
suffix:semicolon
DECL|member|count
r_int
r_int
id|count
suffix:semicolon
)brace
suffix:semicolon
DECL|function|clear_dma_ff
r_static
id|__inline__
r_void
multiline_comment|/* These are in arch/sh/kernel/dma.c: */
r_extern
r_int
r_int
id|claim_dma_lock
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|release_dma_lock
c_func
(paren
r_int
r_int
id|flags
)paren
suffix:semicolon
r_extern
r_void
id|setup_dma
c_func
(paren
r_int
r_int
id|dmanr
comma
r_struct
id|dma_info_t
op_star
id|info
)paren
suffix:semicolon
r_extern
r_void
id|enable_dma
c_func
(paren
r_int
r_int
id|dmanr
)paren
suffix:semicolon
r_extern
r_void
id|disable_dma
c_func
(paren
r_int
r_int
id|dmanr
)paren
suffix:semicolon
r_extern
r_void
id|set_dma_mode
c_func
(paren
r_int
r_int
id|dmanr
comma
r_char
id|mode
)paren
suffix:semicolon
r_extern
r_void
id|set_dma_addr
c_func
(paren
r_int
r_int
id|dmanr
comma
r_int
r_int
id|a
)paren
suffix:semicolon
r_extern
r_void
id|set_dma_count
c_func
(paren
r_int
r_int
id|dmanr
comma
r_int
r_int
id|count
)paren
suffix:semicolon
r_extern
r_int
id|get_dma_residue
c_func
(paren
r_int
r_int
id|dmanr
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PCI
r_extern
r_int
id|isa_dma_bridge_buggy
suffix:semicolon
macro_line|#else
DECL|macro|isa_dma_bridge_buggy
mdefine_line|#define isa_dma_bridge_buggy &t;(0)
macro_line|#endif
macro_line|#endif /* __ASM_SH_DMA_H */
eof
