multiline_comment|/*&n; *  linux/include/asm-arm/imxads/dma.h&n; *&n; *  Copyright (C) 1997,1998 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef __ASM_ARCH_DMA_H
DECL|macro|__ASM_ARCH_DMA_H
mdefine_line|#define __ASM_ARCH_DMA_H
DECL|macro|MAX_DMA_ADDRESS
mdefine_line|#define MAX_DMA_ADDRESS&t;&t;0xffffffff
DECL|macro|MAX_DMA_CHANNELS
mdefine_line|#define MAX_DMA_CHANNELS&t;0
multiline_comment|/*&n; * DMA registration&n; */
r_typedef
r_enum
(brace
DECL|enumerator|DMA_PRIO_HIGH
id|DMA_PRIO_HIGH
op_assign
l_int|0
comma
DECL|enumerator|DMA_PRIO_MEDIUM
id|DMA_PRIO_MEDIUM
op_assign
l_int|3
comma
DECL|enumerator|DMA_PRIO_LOW
id|DMA_PRIO_LOW
op_assign
l_int|6
DECL|typedef|imx_dma_prio
)brace
id|imx_dma_prio
suffix:semicolon
r_int
id|imx_request_dma
c_func
(paren
r_char
op_star
id|name
comma
id|imx_dma_prio
id|prio
comma
r_void
(paren
op_star
id|irq_handler
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
comma
r_void
(paren
op_star
id|err_handler
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
comma
r_void
op_star
id|data
)paren
suffix:semicolon
r_void
id|imx_free_dma
c_func
(paren
r_int
id|dma_ch
)paren
suffix:semicolon
DECL|macro|DMA_REQ_UART3_T
mdefine_line|#define DMA_REQ_UART3_T        2
DECL|macro|DMA_REQ_UART3_R
mdefine_line|#define DMA_REQ_UART3_R        3
DECL|macro|DMA_REQ_SSI2_T
mdefine_line|#define DMA_REQ_SSI2_T         4
DECL|macro|DMA_REQ_SSI2_R
mdefine_line|#define DMA_REQ_SSI2_R         5
DECL|macro|DMA_REQ_CSI_STAT
mdefine_line|#define DMA_REQ_CSI_STAT       6
DECL|macro|DMA_REQ_CSI_R
mdefine_line|#define DMA_REQ_CSI_R          7
DECL|macro|DMA_REQ_MSHC
mdefine_line|#define DMA_REQ_MSHC           8
DECL|macro|DMA_REQ_DSPA_DCT_DOUT
mdefine_line|#define DMA_REQ_DSPA_DCT_DOUT  9
DECL|macro|DMA_REQ_DSPA_DCT_DIN
mdefine_line|#define DMA_REQ_DSPA_DCT_DIN  10
DECL|macro|DMA_REQ_DSPA_MAC
mdefine_line|#define DMA_REQ_DSPA_MAC      11
DECL|macro|DMA_REQ_EXT
mdefine_line|#define DMA_REQ_EXT           12
DECL|macro|DMA_REQ_SDHC
mdefine_line|#define DMA_REQ_SDHC          13
DECL|macro|DMA_REQ_SPI1_R
mdefine_line|#define DMA_REQ_SPI1_R        14
DECL|macro|DMA_REQ_SPI1_T
mdefine_line|#define DMA_REQ_SPI1_T        15
DECL|macro|DMA_REQ_SSI_T
mdefine_line|#define DMA_REQ_SSI_T         16
DECL|macro|DMA_REQ_SSI_R
mdefine_line|#define DMA_REQ_SSI_R         17
DECL|macro|DMA_REQ_ASP_DAC
mdefine_line|#define DMA_REQ_ASP_DAC       18
DECL|macro|DMA_REQ_ASP_ADC
mdefine_line|#define DMA_REQ_ASP_ADC       19
DECL|macro|DMA_REQ_USP_EP
mdefine_line|#define DMA_REQ_USP_EP(x)    (20+(x))
DECL|macro|DMA_REQ_SPI2_R
mdefine_line|#define DMA_REQ_SPI2_R        26
DECL|macro|DMA_REQ_SPI2_T
mdefine_line|#define DMA_REQ_SPI2_T        27
DECL|macro|DMA_REQ_UART2_T
mdefine_line|#define DMA_REQ_UART2_T       28
DECL|macro|DMA_REQ_UART2_R
mdefine_line|#define DMA_REQ_UART2_R       29
DECL|macro|DMA_REQ_UART1_T
mdefine_line|#define DMA_REQ_UART1_T       30
DECL|macro|DMA_REQ_UART1_R
mdefine_line|#define DMA_REQ_UART1_R       31
macro_line|#endif&t;&t;&t;&t;/* _ASM_ARCH_DMA_H */
eof
