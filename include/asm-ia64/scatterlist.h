macro_line|#ifndef _ASM_IA64_SCATTERLIST_H
DECL|macro|_ASM_IA64_SCATTERLIST_H
mdefine_line|#define _ASM_IA64_SCATTERLIST_H
multiline_comment|/*&n; * Modified 1998-1999, 2001-2002, 2004&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;, Hewlett-Packard Co&n; */
DECL|struct|scatterlist
r_struct
id|scatterlist
(brace
DECL|member|page
r_struct
id|page
op_star
id|page
suffix:semicolon
DECL|member|offset
r_int
r_int
id|offset
suffix:semicolon
DECL|member|length
r_int
r_int
id|length
suffix:semicolon
multiline_comment|/* buffer length */
DECL|member|dma_address
id|dma_addr_t
id|dma_address
suffix:semicolon
DECL|member|dma_length
r_int
r_int
id|dma_length
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * It used to be that ISA_DMA_THRESHOLD had something to do with the&n; * DMA-limits of ISA-devices.  Nowadays, its only remaining use (apart&n; * from the aha1542.c driver, which isn&squot;t 64-bit clean anyhow) is to&n; * tell the block-layer (via BLK_BOUNCE_ISA) what the max. physical&n; * address of a page is that is allocated with GFP_DMA.  On IA-64,&n; * that&squot;s 4GB - 1.&n; */
DECL|macro|ISA_DMA_THRESHOLD
mdefine_line|#define ISA_DMA_THRESHOLD&t;0xffffffff
macro_line|#endif /* _ASM_IA64_SCATTERLIST_H */
eof
