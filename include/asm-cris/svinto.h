macro_line|#ifndef _ASM_CRIS_SVINTO_H
DECL|macro|_ASM_CRIS_SVINTO_H
mdefine_line|#define _ASM_CRIS_SVINTO_H
macro_line|#include &quot;sv_addr_ag.h&quot;
r_extern
r_int
r_int
id|genconfig_shadow
suffix:semicolon
multiline_comment|/* defined and set in head.S */
multiline_comment|/* dma stuff */
r_enum
(brace
multiline_comment|/* Available in:  */
DECL|enumerator|d_eol
id|d_eol
op_assign
(paren
l_int|1
op_lshift
l_int|0
)paren
comma
multiline_comment|/* flags          */
DECL|enumerator|d_eop
id|d_eop
op_assign
(paren
l_int|1
op_lshift
l_int|1
)paren
comma
multiline_comment|/* flags &amp; status */
DECL|enumerator|d_wait
id|d_wait
op_assign
(paren
l_int|1
op_lshift
l_int|2
)paren
comma
multiline_comment|/* flags          */
DECL|enumerator|d_int
id|d_int
op_assign
(paren
l_int|1
op_lshift
l_int|3
)paren
comma
multiline_comment|/* flags          */
DECL|enumerator|d_txerr
id|d_txerr
op_assign
(paren
l_int|1
op_lshift
l_int|4
)paren
comma
multiline_comment|/* flags          */
DECL|enumerator|d_stop
id|d_stop
op_assign
(paren
l_int|1
op_lshift
l_int|4
)paren
comma
multiline_comment|/*         status */
DECL|enumerator|d_ecp
id|d_ecp
op_assign
(paren
l_int|1
op_lshift
l_int|4
)paren
comma
multiline_comment|/* flags &amp; status */
DECL|enumerator|d_pri
id|d_pri
op_assign
(paren
l_int|1
op_lshift
l_int|5
)paren
comma
multiline_comment|/* flags &amp; status */
DECL|enumerator|d_alignerr
id|d_alignerr
op_assign
(paren
l_int|1
op_lshift
l_int|6
)paren
comma
multiline_comment|/*         status */
DECL|enumerator|d_crcerr
id|d_crcerr
op_assign
(paren
l_int|1
op_lshift
l_int|7
)paren
multiline_comment|/*         status */
)brace
suffix:semicolon
multiline_comment|/* Do remember that DMA does not go through the MMU and needs&n; * a real physical address, not an address virtually mapped or&n; * paged. Therefore the buf/next ptrs below are unsigned long instead&n; * of void * to give a warning if you try to put a pointer directly&n; * to them instead of going through virt_to_phys/phys_to_virt.&n; */
DECL|struct|etrax_dma_descr
r_typedef
r_struct
id|etrax_dma_descr
(brace
DECL|member|sw_len
r_int
r_int
id|sw_len
suffix:semicolon
multiline_comment|/* 0-1 */
DECL|member|ctrl
r_int
r_int
id|ctrl
suffix:semicolon
multiline_comment|/* 2-3 */
DECL|member|next
r_int
r_int
id|next
suffix:semicolon
multiline_comment|/* 4-7 */
DECL|member|buf
r_int
r_int
id|buf
suffix:semicolon
multiline_comment|/* 8-11 */
DECL|member|hw_len
r_int
r_int
id|hw_len
suffix:semicolon
multiline_comment|/* 12-13 */
DECL|member|status
r_int
r_int
id|status
suffix:semicolon
multiline_comment|/* 14-15 */
DECL|typedef|etrax_dma_descr
)brace
id|etrax_dma_descr
suffix:semicolon
DECL|macro|RESET_DMA
mdefine_line|#define RESET_DMA( n ) &bslash;&n;  *R_DMA_CH##n##_CMD = IO_STATE( R_DMA_CH0_CMD, cmd, reset )
DECL|macro|WAIT_DMA
mdefine_line|#define WAIT_DMA( n ) &bslash;&n;  while( (*R_DMA_CH##n##_CMD &amp; IO_MASK( R_DMA_CH0_CMD, cmd )) != &bslash;&n;         IO_STATE( R_DMA_CH0_CMD, cmd, hold ) )
macro_line|#endif
eof
