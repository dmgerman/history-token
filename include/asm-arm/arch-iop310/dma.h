multiline_comment|/*&n; * linux/include/asm-arm/arch-iop80310/dma.h&n; *&n; *  Copyright (C) 2001 MontaVista Software, Inc.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#ifndef _IOP310_DMA_H_
DECL|macro|_IOP310_DMA_H_
mdefine_line|#define _IOP310_DMA_H_
multiline_comment|/* 2 DMA on primary PCI and 1 on secondary for 80310 */
DECL|macro|MAX_IOP310_DMA_CHANNEL
mdefine_line|#define MAX_IOP310_DMA_CHANNEL   3
DECL|macro|MAX_DMA_DESC
mdefine_line|#define MAX_DMA_DESC        &t;64&t;/*128 */
multiline_comment|/*&n; * Make the generic DMA bits go away since we don&squot;t use it&n; */
DECL|macro|MAX_DMA_CHANNELS
mdefine_line|#define MAX_DMA_CHANNELS&t;0
DECL|macro|MAX_DMA_ADDRESS
mdefine_line|#define MAX_DMA_ADDRESS&t;&t;0xffffffff
DECL|macro|IOP310_DMA_P0
mdefine_line|#define IOP310_DMA_P0      &t;0
DECL|macro|IOP310_DMA_P1
mdefine_line|#define IOP310_DMA_P1&t;&t;1
DECL|macro|IOP310_DMA_S0
mdefine_line|#define IOP310_DMA_S0      &t;2
DECL|macro|DMA_MOD_READ
mdefine_line|#define DMA_MOD_READ        &t;0x0001
DECL|macro|DMA_MOD_WRITE
mdefine_line|#define DMA_MOD_WRITE&t;&t;0x0002
DECL|macro|DMA_MOD_CACHED
mdefine_line|#define DMA_MOD_CACHED&t;&t;0x0004
DECL|macro|DMA_MOD_NONCACHED
mdefine_line|#define DMA_MOD_NONCACHED&t;0x0008
DECL|macro|DMA_DESC_DONE
mdefine_line|#define DMA_DESC_DONE   &t;0x0010
DECL|macro|DMA_INCOMPLETE
mdefine_line|#define DMA_INCOMPLETE  &t;0x0020
DECL|macro|DMA_HOLD
mdefine_line|#define DMA_HOLD&t;&t;0x0040
DECL|macro|DMA_END_CHAIN
mdefine_line|#define DMA_END_CHAIN&t;&t;0x0080
DECL|macro|DMA_COMPLETE
mdefine_line|#define DMA_COMPLETE&t;&t;0x0100
DECL|macro|DMA_NOTIFY
mdefine_line|#define DMA_NOTIFY&t;&t;0x0200
DECL|macro|DMA_NEW_HEAD
mdefine_line|#define DMA_NEW_HEAD&t;&t;0x0400
DECL|macro|DMA_USER_MASK
mdefine_line|#define DMA_USER_MASK&t;(DMA_NOTIFY | DMA_INCOMPLETE | &bslash;&n;&t;&t;&t;&t;&t;&t; DMA_HOLD | DMA_COMPLETE)
DECL|macro|DMA_DCR_DAC
mdefine_line|#define DMA_DCR_DAC&t;&t;0x00000020&t;/* Dual Addr Cycle Enab */
DECL|macro|DMA_DCR_IE
mdefine_line|#define DMA_DCR_IE&t;&t;0x00000010&t;/* Interrupt Enable */
DECL|macro|DMA_DCR_PCI_IOR
mdefine_line|#define DMA_DCR_PCI_IOR&t;&t;0x00000002&t;/* I/O Read */
DECL|macro|DMA_DCR_PCI_IOW
mdefine_line|#define DMA_DCR_PCI_IOW&t;&t;0x00000003&t;/* I/O Write */
DECL|macro|DMA_DCR_PCI_MR
mdefine_line|#define DMA_DCR_PCI_MR&t;&t;0x00000006&t;/* Memory Read */
DECL|macro|DMA_DCR_PCI_MW
mdefine_line|#define DMA_DCR_PCI_MW&t;&t;0x00000007&t;/* Memory Write */
DECL|macro|DMA_DCR_PCI_CR
mdefine_line|#define DMA_DCR_PCI_CR&t;&t;0x0000000A&t;/* Configuration Read */
DECL|macro|DMA_DCR_PCI_CW
mdefine_line|#define DMA_DCR_PCI_CW&t;&t;0x0000000B&t;/* Configuration Write */
DECL|macro|DMA_DCR_PCI_MRM
mdefine_line|#define DMA_DCR_PCI_MRM&t;&t;0x0000000C&t;/* Memory Read Multiple */
DECL|macro|DMA_DCR_PCI_MRL
mdefine_line|#define DMA_DCR_PCI_MRL&t;&t;0x0000000E&t;/* Memory Read Line */
DECL|macro|DMA_DCR_PCI_MWI
mdefine_line|#define DMA_DCR_PCI_MWI&t;&t;0x0000000F&t;/* Mem Write and Inval */
DECL|macro|DMA_USER_CMD_IE
mdefine_line|#define DMA_USER_CMD_IE&t;&t;0x00000001&t;/* user request int */
DECL|macro|DMA_USER_END_CHAIN
mdefine_line|#define DMA_USER_END_CHAIN&t;0x00000002&t;/* end of sgl chain flag */
multiline_comment|/* ATU defines */
DECL|macro|IOP310_ATUCR_PRIM_OUT_ENAB
mdefine_line|#define     IOP310_ATUCR_PRIM_OUT_ENAB  /* Configuration   */      0x00000002
DECL|macro|IOP310_ATUCR_DIR_ADDR_ENAB
mdefine_line|#define     IOP310_ATUCR_DIR_ADDR_ENAB  /* Configuration   */      0x00000080
DECL|typedef|dma_callback_t
r_typedef
r_void
(paren
op_star
id|dma_callback_t
)paren
(paren
r_void
op_star
id|buf_context
)paren
suffix:semicolon
multiline_comment|/*&n; * DMA Descriptor&n; */
DECL|struct|_dma_desc
r_typedef
r_struct
id|_dma_desc
(brace
DECL|member|NDAR
id|u32
id|NDAR
suffix:semicolon
multiline_comment|/* next descriptor adress */
DECL|member|PDAR
id|u32
id|PDAR
suffix:semicolon
multiline_comment|/* PCI address */
DECL|member|PUADR
id|u32
id|PUADR
suffix:semicolon
multiline_comment|/* upper PCI address */
DECL|member|LADR
id|u32
id|LADR
suffix:semicolon
multiline_comment|/* local address */
DECL|member|BC
id|u32
id|BC
suffix:semicolon
multiline_comment|/* byte count */
DECL|member|DC
id|u32
id|DC
suffix:semicolon
multiline_comment|/* descriptor control */
DECL|typedef|dma_desc_t
)brace
id|dma_desc_t
suffix:semicolon
DECL|struct|_dma_sgl
r_typedef
r_struct
id|_dma_sgl
(brace
DECL|member|dma_desc
id|dma_desc_t
id|dma_desc
suffix:semicolon
multiline_comment|/* DMA descriptor pointer */
DECL|member|status
id|u32
id|status
suffix:semicolon
multiline_comment|/* descriptor status */
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
multiline_comment|/* local virt */
DECL|member|next
r_struct
id|_dma_sgl
op_star
id|next
suffix:semicolon
multiline_comment|/* next descriptor */
DECL|typedef|dma_sgl_t
)brace
id|dma_sgl_t
suffix:semicolon
multiline_comment|/* dma sgl head */
DECL|struct|_dma_head
r_typedef
r_struct
id|_dma_head
(brace
DECL|member|total
id|u32
id|total
suffix:semicolon
multiline_comment|/* total elements in SGL */
DECL|member|status
id|u32
id|status
suffix:semicolon
multiline_comment|/* status of sgl */
DECL|member|mode
id|u32
id|mode
suffix:semicolon
multiline_comment|/* read or write mode */
DECL|member|list
id|dma_sgl_t
op_star
id|list
suffix:semicolon
multiline_comment|/* pointer to list */
DECL|member|callback
id|dma_callback_t
id|callback
suffix:semicolon
multiline_comment|/* callback function */
DECL|typedef|dma_head_t
)brace
id|dma_head_t
suffix:semicolon
multiline_comment|/* function prototypes */
r_int
id|dma_request
c_func
(paren
id|dmach_t
comma
r_const
r_char
op_star
)paren
suffix:semicolon
r_int
id|dma_queue_buffer
c_func
(paren
id|dmach_t
comma
id|dma_head_t
op_star
)paren
suffix:semicolon
r_int
id|dma_suspend
c_func
(paren
id|dmach_t
)paren
suffix:semicolon
r_int
id|dma_resume
c_func
(paren
id|dmach_t
)paren
suffix:semicolon
r_int
id|dma_flush_all
c_func
(paren
id|dmach_t
)paren
suffix:semicolon
r_void
id|dma_free
c_func
(paren
id|dmach_t
)paren
suffix:semicolon
r_void
id|dma_set_irq_threshold
c_func
(paren
id|dmach_t
comma
r_int
)paren
suffix:semicolon
id|dma_sgl_t
op_star
id|dma_get_buffer
c_func
(paren
id|dmach_t
comma
r_int
)paren
suffix:semicolon
r_void
id|dma_return_buffer
c_func
(paren
id|dmach_t
comma
id|dma_sgl_t
op_star
)paren
suffix:semicolon
macro_line|#endif /* _ASM_ARCH_DMA_H */
eof
