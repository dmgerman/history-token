macro_line|#ifndef _ASM_SCATTERLIST_H
DECL|macro|_ASM_SCATTERLIST_H
mdefine_line|#define _ASM_SCATTERLIST_H
multiline_comment|/*&n; * Drivers must set either -&gt;address or (preferred) -&gt;page and -&gt;offset&n; * to indicate where data must be transferred to/from.&n; *&n; * Using -&gt;page is recommended since it handles highmem data as well as&n; * low mem. -&gt;address is restricted to data which has a virtual mapping, and&n; * it will go away in the future. Updating to -&gt;page can be automated very&n; * easily -- something like&n; *&n; * sg-&gt;address = some_ptr;&n; *&n; * can be rewritten as&n; *&n; * sg-&gt;page = virt_to_page(some_ptr);&n; * sg-&gt;offset = (unsigned long) some_ptr &amp; ~PAGE_MASK;&n; *&n; * and that&squot;s it. There&squot;s no excuse for not highmem enabling YOUR driver. /jens&n; */
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
multiline_comment|/* Location for highmem page, if any */
DECL|member|offset
r_int
r_int
id|offset
suffix:semicolon
multiline_comment|/* for highmem, page offset */
DECL|member|dma_address
id|dma_addr_t
id|dma_address
suffix:semicolon
DECL|member|length
r_int
r_int
id|length
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|ISA_DMA_THRESHOLD
mdefine_line|#define ISA_DMA_THRESHOLD (0xffffffffUL)
macro_line|#endif /* !_ASM_SCATTERLIST_H */
eof
