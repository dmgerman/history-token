multiline_comment|/*&n; * linux/include/asm-arm/arch-iop3xx/dma.h&n; *&n; *  Copyright (C) 2004 Intel Corp.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#ifndef _IOP3XX_DMA_H_P
DECL|macro|_IOP3XX_DMA_H_P
mdefine_line|#define _IOP3XX_DMA_H_P
multiline_comment|/* 80310 not supported */
DECL|macro|MAX_IOP3XX_DMA_CHANNEL
mdefine_line|#define MAX_IOP3XX_DMA_CHANNEL   2
DECL|macro|MAX_DMA_DESC
mdefine_line|#define MAX_DMA_DESC        &t;64&t;/*128 */
DECL|macro|DMA_FREE
mdefine_line|#define DMA_FREE         0x0
DECL|macro|DMA_ACTIVE
mdefine_line|#define DMA_ACTIVE       0x1
DECL|macro|DMA_COMPLETE
mdefine_line|#define DMA_COMPLETE     0x2
DECL|macro|DMA_ERROR
mdefine_line|#define DMA_ERROR        0x4
multiline_comment|/*&n; * Make the generic DMA bits go away since we don&squot;t use it&n; */
DECL|macro|MAX_DMA_CHANNELS
mdefine_line|#define MAX_DMA_CHANNELS&t;0
DECL|macro|MAX_DMA_ADDRESS
mdefine_line|#define MAX_DMA_ADDRESS&t;&t;0xffffffff
DECL|macro|DMA_POLL
mdefine_line|#define DMA_POLL         0x0
DECL|macro|DMA_INTERRUPT
mdefine_line|#define DMA_INTERRUPT    0x1
DECL|macro|DMA_DCR_MTM
mdefine_line|#define DMA_DCR_MTM     0x00000040  /* memory to memory transfer */
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
singleline_comment|//extern iop3xx_dma_t dma_chan[2];
multiline_comment|/* function prototypes */
macro_line|#ifdef CONFIG_IOP3XX_DMACOPY
r_extern
r_int
id|iop_memcpy
suffix:semicolon
r_void
op_star
id|dma_memcpy
c_func
(paren
r_void
op_star
id|to
comma
r_const
r_void
op_star
id|from
comma
id|__kernel_size_t
id|n
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif /* _ASM_ARCH_DMA_H_P */
eof
