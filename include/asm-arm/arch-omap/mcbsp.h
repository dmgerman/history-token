multiline_comment|/*&n; * linux/include/asm-arm/arch-omap/gpio.h&n; *&n; * Defines for Multi-Channel Buffered Serial Port&n; *&n; * Copyright (C) 2002 RidgeRun, Inc.&n; * Author: Steve Johnson&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; *&n; */
macro_line|#ifndef __ASM_ARCH_OMAP_MCBSP_H
DECL|macro|__ASM_ARCH_OMAP_MCBSP_H
mdefine_line|#define __ASM_ARCH_OMAP_MCBSP_H
macro_line|#include &lt;asm/arch/hardware.h&gt;
DECL|macro|OMAP730_MCBSP1_BASE
mdefine_line|#define OMAP730_MCBSP1_BASE&t;0xfffb1000
DECL|macro|OMAP730_MCBSP2_BASE
mdefine_line|#define OMAP730_MCBSP2_BASE&t;0xfffb1800
DECL|macro|OMAP1510_MCBSP1_BASE
mdefine_line|#define OMAP1510_MCBSP1_BASE&t;0xe1011800
DECL|macro|OMAP1510_MCBSP2_BASE
mdefine_line|#define OMAP1510_MCBSP2_BASE&t;0xfffb1000
DECL|macro|OMAP1510_MCBSP3_BASE
mdefine_line|#define OMAP1510_MCBSP3_BASE&t;0xe1017000
DECL|macro|OMAP1610_MCBSP1_BASE
mdefine_line|#define OMAP1610_MCBSP1_BASE&t;0xe1011800
DECL|macro|OMAP1610_MCBSP2_BASE
mdefine_line|#define OMAP1610_MCBSP2_BASE&t;0xfffb1000
DECL|macro|OMAP1610_MCBSP3_BASE
mdefine_line|#define OMAP1610_MCBSP3_BASE&t;0xe1017000
DECL|macro|OMAP_MCBSP_REG_DRR2
mdefine_line|#define OMAP_MCBSP_REG_DRR2&t;0x00
DECL|macro|OMAP_MCBSP_REG_DRR1
mdefine_line|#define OMAP_MCBSP_REG_DRR1&t;0x02
DECL|macro|OMAP_MCBSP_REG_DXR2
mdefine_line|#define OMAP_MCBSP_REG_DXR2&t;0x04
DECL|macro|OMAP_MCBSP_REG_DXR1
mdefine_line|#define OMAP_MCBSP_REG_DXR1&t;0x06
DECL|macro|OMAP_MCBSP_REG_SPCR2
mdefine_line|#define OMAP_MCBSP_REG_SPCR2&t;0x08
DECL|macro|OMAP_MCBSP_REG_SPCR1
mdefine_line|#define OMAP_MCBSP_REG_SPCR1&t;0x0a
DECL|macro|OMAP_MCBSP_REG_RCR2
mdefine_line|#define OMAP_MCBSP_REG_RCR2&t;0x0c
DECL|macro|OMAP_MCBSP_REG_RCR1
mdefine_line|#define OMAP_MCBSP_REG_RCR1&t;0x0e
DECL|macro|OMAP_MCBSP_REG_XCR2
mdefine_line|#define OMAP_MCBSP_REG_XCR2&t;0x10
DECL|macro|OMAP_MCBSP_REG_XCR1
mdefine_line|#define OMAP_MCBSP_REG_XCR1&t;0x12
DECL|macro|OMAP_MCBSP_REG_SRGR2
mdefine_line|#define OMAP_MCBSP_REG_SRGR2&t;0x14
DECL|macro|OMAP_MCBSP_REG_SRGR1
mdefine_line|#define OMAP_MCBSP_REG_SRGR1&t;0x16
DECL|macro|OMAP_MCBSP_REG_MCR2
mdefine_line|#define OMAP_MCBSP_REG_MCR2&t;0x18
DECL|macro|OMAP_MCBSP_REG_MCR1
mdefine_line|#define OMAP_MCBSP_REG_MCR1&t;0x1a
DECL|macro|OMAP_MCBSP_REG_RCERA
mdefine_line|#define OMAP_MCBSP_REG_RCERA&t;0x1c
DECL|macro|OMAP_MCBSP_REG_RCERB
mdefine_line|#define OMAP_MCBSP_REG_RCERB&t;0x1e
DECL|macro|OMAP_MCBSP_REG_XCERA
mdefine_line|#define OMAP_MCBSP_REG_XCERA&t;0x20
DECL|macro|OMAP_MCBSP_REG_XCERB
mdefine_line|#define OMAP_MCBSP_REG_XCERB&t;0x22
DECL|macro|OMAP_MCBSP_REG_PCR0
mdefine_line|#define OMAP_MCBSP_REG_PCR0&t;0x24
DECL|macro|OMAP_MCBSP_REG_RCERC
mdefine_line|#define OMAP_MCBSP_REG_RCERC&t;0x26
DECL|macro|OMAP_MCBSP_REG_RCERD
mdefine_line|#define OMAP_MCBSP_REG_RCERD&t;0x28
DECL|macro|OMAP_MCBSP_REG_XCERC
mdefine_line|#define OMAP_MCBSP_REG_XCERC&t;0x2A
DECL|macro|OMAP_MCBSP_REG_XCERD
mdefine_line|#define OMAP_MCBSP_REG_XCERD&t;0x2C
DECL|macro|OMAP_MCBSP_REG_RCERE
mdefine_line|#define OMAP_MCBSP_REG_RCERE&t;0x2E
DECL|macro|OMAP_MCBSP_REG_RCERF
mdefine_line|#define OMAP_MCBSP_REG_RCERF&t;0x30
DECL|macro|OMAP_MCBSP_REG_XCERE
mdefine_line|#define OMAP_MCBSP_REG_XCERE&t;0x32
DECL|macro|OMAP_MCBSP_REG_XCERF
mdefine_line|#define OMAP_MCBSP_REG_XCERF&t;0x34
DECL|macro|OMAP_MCBSP_REG_RCERG
mdefine_line|#define OMAP_MCBSP_REG_RCERG&t;0x36
DECL|macro|OMAP_MCBSP_REG_RCERH
mdefine_line|#define OMAP_MCBSP_REG_RCERH&t;0x38
DECL|macro|OMAP_MCBSP_REG_XCERG
mdefine_line|#define OMAP_MCBSP_REG_XCERG&t;0x3A
DECL|macro|OMAP_MCBSP_REG_XCERH
mdefine_line|#define OMAP_MCBSP_REG_XCERH&t;0x3C
DECL|macro|OMAP_MAX_MCBSP_COUNT
mdefine_line|#define OMAP_MAX_MCBSP_COUNT 3
DECL|macro|OMAP_MCBSP_READ
mdefine_line|#define OMAP_MCBSP_READ(base, reg)&t;&t;__raw_readw((base) + OMAP_MCBSP_REG_##reg)
DECL|macro|OMAP_MCBSP_WRITE
mdefine_line|#define OMAP_MCBSP_WRITE(base, reg, val)&t;__raw_writew((val), (base) + OMAP_MCBSP_REG_##reg)
multiline_comment|/************************** McBSP SPCR1 bit definitions ***********************/
DECL|macro|RRST
mdefine_line|#define RRST&t;&t;&t;0x0001
DECL|macro|RRDY
mdefine_line|#define RRDY&t;&t;&t;0x0002
DECL|macro|RFULL
mdefine_line|#define RFULL&t;&t;&t;0x0004
DECL|macro|RSYNC_ERR
mdefine_line|#define RSYNC_ERR&t;&t;0x0008
DECL|macro|RINTM
mdefine_line|#define RINTM(value)&t;&t;((value)&lt;&lt;4)&t;/* bits 4:5 */
DECL|macro|ABIS
mdefine_line|#define ABIS&t;&t;&t;0x0040
DECL|macro|DXENA
mdefine_line|#define DXENA&t;&t;&t;0x0080
DECL|macro|CLKSTP
mdefine_line|#define CLKSTP(value)&t;&t;((value)&lt;&lt;11)&t;/* bits 11:12 */
DECL|macro|RJUST
mdefine_line|#define RJUST(value)&t;&t;((value)&lt;&lt;13)&t;/* bits 13:14 */
DECL|macro|DLB
mdefine_line|#define DLB&t;&t;&t;0x8000
multiline_comment|/************************** McBSP SPCR2 bit definitions ***********************/
DECL|macro|XRST
mdefine_line|#define XRST&t;&t;0x0001
DECL|macro|XRDY
mdefine_line|#define XRDY&t;&t;0x0002
DECL|macro|XEMPTY
mdefine_line|#define XEMPTY&t;&t;0x0004
DECL|macro|XSYNC_ERR
mdefine_line|#define XSYNC_ERR&t;0x0008
DECL|macro|XINTM
mdefine_line|#define XINTM(value)&t;((value)&lt;&lt;4)&t;&t;/* bits 4:5 */
DECL|macro|GRST
mdefine_line|#define GRST&t;&t;0x0040
DECL|macro|FRST
mdefine_line|#define FRST&t;&t;0x0080
DECL|macro|SOFT
mdefine_line|#define SOFT&t;&t;0x0100
DECL|macro|FREE
mdefine_line|#define FREE&t;&t;0x0200
multiline_comment|/************************** McBSP PCR bit definitions *************************/
DECL|macro|CLKRP
mdefine_line|#define CLKRP&t;&t;0x0001
DECL|macro|CLKXP
mdefine_line|#define CLKXP&t;&t;0x0002
DECL|macro|FSRP
mdefine_line|#define FSRP&t;&t;0x0004
DECL|macro|FSXP
mdefine_line|#define FSXP&t;&t;0x0008
DECL|macro|DR_STAT
mdefine_line|#define DR_STAT&t;&t;0x0010
DECL|macro|DX_STAT
mdefine_line|#define DX_STAT&t;&t;0x0020
DECL|macro|CLKS_STAT
mdefine_line|#define CLKS_STAT&t;0x0040
DECL|macro|SCLKME
mdefine_line|#define SCLKME&t;&t;0x0080
DECL|macro|CLKRM
mdefine_line|#define CLKRM&t;&t;0x0100
DECL|macro|CLKXM
mdefine_line|#define CLKXM&t;&t;0x0200
DECL|macro|FSRM
mdefine_line|#define FSRM&t;&t;0x0400
DECL|macro|FSXM
mdefine_line|#define FSXM&t;&t;0x0800
DECL|macro|RIOEN
mdefine_line|#define RIOEN&t;&t;0x1000
DECL|macro|XIOEN
mdefine_line|#define XIOEN&t;&t;0x2000
DECL|macro|IDLE_EN
mdefine_line|#define IDLE_EN&t;&t;0x4000
multiline_comment|/************************** McBSP RCR1 bit definitions ************************/
DECL|macro|RWDLEN1
mdefine_line|#define RWDLEN1(value)&t;&t;((value)&lt;&lt;5)&t;/* Bits 5:7 */
DECL|macro|RFRLEN1
mdefine_line|#define RFRLEN1(value)&t;&t;((value)&lt;&lt;8)&t;/* Bits 8:14 */
multiline_comment|/************************** McBSP XCR1 bit definitions ************************/
DECL|macro|XWDLEN1
mdefine_line|#define XWDLEN1(value)&t;&t;((value)&lt;&lt;5)&t;/* Bits 5:7 */
DECL|macro|XFRLEN1
mdefine_line|#define XFRLEN1(value)&t;&t;((value)&lt;&lt;8)&t;/* Bits 8:14 */
multiline_comment|/*************************** McBSP RCR2 bit definitions ***********************/
DECL|macro|RDATDLY
mdefine_line|#define RDATDLY(value)&t;&t;(value)&t;&t;/* Bits 0:1 */
DECL|macro|RFIG
mdefine_line|#define RFIG&t;&t;&t;0x0004
DECL|macro|RCOMPAND
mdefine_line|#define RCOMPAND(value)&t;&t;((value)&lt;&lt;3)&t;/* Bits 3:4 */
DECL|macro|RWDLEN2
mdefine_line|#define RWDLEN2(value)&t;&t;((value)&lt;&lt;5)&t;/* Bits 5:7 */
DECL|macro|RFRLEN2
mdefine_line|#define RFRLEN2(value)&t;&t;((value)&lt;&lt;8)&t;/* Bits 8:14 */
DECL|macro|RPHASE
mdefine_line|#define RPHASE&t;&t;&t;0x8000
multiline_comment|/*************************** McBSP XCR2 bit definitions ***********************/
DECL|macro|XDATDLY
mdefine_line|#define XDATDLY(value)&t;&t;(value)&t;&t;/* Bits 0:1 */
DECL|macro|XFIG
mdefine_line|#define XFIG&t;&t;&t;0x0004
DECL|macro|XCOMPAND
mdefine_line|#define XCOMPAND(value)&t;&t;((value)&lt;&lt;3)&t;/* Bits 3:4 */
DECL|macro|XWDLEN2
mdefine_line|#define XWDLEN2(value)&t;&t;((value)&lt;&lt;5)&t;/* Bits 5:7 */
DECL|macro|XFRLEN2
mdefine_line|#define XFRLEN2(value)&t;&t;((value)&lt;&lt;8)&t;/* Bits 8:14 */
DECL|macro|XPHASE
mdefine_line|#define XPHASE&t;&t;&t;0x8000
multiline_comment|/************************* McBSP SRGR1 bit definitions ************************/
DECL|macro|CLKGDV
mdefine_line|#define CLKGDV(value)&t;&t;(value)&t;&t;/* Bits 0:7 */
DECL|macro|FWID
mdefine_line|#define FWID(value)&t;&t;((value)&lt;&lt;8)&t;/* Bits 8:15 */
multiline_comment|/************************* McBSP SRGR2 bit definitions ************************/
DECL|macro|FPER
mdefine_line|#define FPER(value)&t;&t;(value)&t;&t;/* Bits 0:11 */
DECL|macro|FSGM
mdefine_line|#define FSGM&t;&t;&t;0x1000
DECL|macro|CLKSM
mdefine_line|#define CLKSM&t;&t;&t;0x2000
DECL|macro|CLKSP
mdefine_line|#define CLKSP&t;&t;&t;0x4000
DECL|macro|GSYNC
mdefine_line|#define GSYNC&t;&t;&t;0x8000
multiline_comment|/************************* McBSP MCR1 bit definitions *************************/
DECL|macro|RMCM
mdefine_line|#define RMCM&t;&t;&t;0x0001
DECL|macro|RCBLK
mdefine_line|#define RCBLK(value)&t;&t;((value)&lt;&lt;2)&t;/* Bits 2:4 */
DECL|macro|RPABLK
mdefine_line|#define RPABLK(value)&t;&t;((value)&lt;&lt;5)&t;/* Bits 5:6 */
DECL|macro|RPBBLK
mdefine_line|#define RPBBLK(value)&t;&t;((value)&lt;&lt;7)&t;/* Bits 7:8 */
multiline_comment|/************************* McBSP MCR2 bit definitions *************************/
DECL|macro|XMCM
mdefine_line|#define XMCM(value)&t;&t;(value)&t;&t;/* Bits 0:1 */
DECL|macro|XCBLK
mdefine_line|#define XCBLK(value)&t;&t;((value)&lt;&lt;2)&t;/* Bits 2:4 */
DECL|macro|XPABLK
mdefine_line|#define XPABLK(value)&t;&t;((value)&lt;&lt;5)&t;/* Bits 5:6 */
DECL|macro|XPBBLK
mdefine_line|#define XPBBLK(value)&t;&t;((value)&lt;&lt;7)&t;/* Bits 7:8 */
multiline_comment|/* we don&squot;t do multichannel for now */
DECL|struct|omap_mcbsp_reg_cfg
r_struct
id|omap_mcbsp_reg_cfg
(brace
DECL|member|spcr2
id|u16
id|spcr2
suffix:semicolon
DECL|member|spcr1
id|u16
id|spcr1
suffix:semicolon
DECL|member|rcr2
id|u16
id|rcr2
suffix:semicolon
DECL|member|rcr1
id|u16
id|rcr1
suffix:semicolon
DECL|member|xcr2
id|u16
id|xcr2
suffix:semicolon
DECL|member|xcr1
id|u16
id|xcr1
suffix:semicolon
DECL|member|srgr2
id|u16
id|srgr2
suffix:semicolon
DECL|member|srgr1
id|u16
id|srgr1
suffix:semicolon
DECL|member|mcr2
id|u16
id|mcr2
suffix:semicolon
DECL|member|mcr1
id|u16
id|mcr1
suffix:semicolon
DECL|member|pcr0
id|u16
id|pcr0
suffix:semicolon
DECL|member|rcerc
id|u16
id|rcerc
suffix:semicolon
DECL|member|rcerd
id|u16
id|rcerd
suffix:semicolon
DECL|member|xcerc
id|u16
id|xcerc
suffix:semicolon
DECL|member|xcerd
id|u16
id|xcerd
suffix:semicolon
DECL|member|rcere
id|u16
id|rcere
suffix:semicolon
DECL|member|rcerf
id|u16
id|rcerf
suffix:semicolon
DECL|member|xcere
id|u16
id|xcere
suffix:semicolon
DECL|member|xcerf
id|u16
id|xcerf
suffix:semicolon
DECL|member|rcerg
id|u16
id|rcerg
suffix:semicolon
DECL|member|rcerh
id|u16
id|rcerh
suffix:semicolon
DECL|member|xcerg
id|u16
id|xcerg
suffix:semicolon
DECL|member|xcerh
id|u16
id|xcerh
suffix:semicolon
)brace
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|OMAP_MCBSP1
id|OMAP_MCBSP1
op_assign
l_int|0
comma
DECL|enumerator|OMAP_MCBSP2
id|OMAP_MCBSP2
comma
DECL|enumerator|OMAP_MCBSP3
id|OMAP_MCBSP3
comma
DECL|typedef|omap_mcbsp_id
)brace
id|omap_mcbsp_id
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|OMAP_MCBSP_WORD_8
id|OMAP_MCBSP_WORD_8
op_assign
l_int|0
comma
DECL|enumerator|OMAP_MCBSP_WORD_12
id|OMAP_MCBSP_WORD_12
comma
DECL|enumerator|OMAP_MCBSP_WORD_16
id|OMAP_MCBSP_WORD_16
comma
DECL|enumerator|OMAP_MCBSP_WORD_20
id|OMAP_MCBSP_WORD_20
comma
DECL|enumerator|OMAP_MCBSP_WORD_24
id|OMAP_MCBSP_WORD_24
comma
DECL|enumerator|OMAP_MCBSP_WORD_32
id|OMAP_MCBSP_WORD_32
comma
DECL|typedef|omap_mcbsp_word_length
)brace
id|omap_mcbsp_word_length
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|OMAP_MCBSP_CLK_RISING
id|OMAP_MCBSP_CLK_RISING
op_assign
l_int|0
comma
DECL|enumerator|OMAP_MCBSP_CLK_FALLING
id|OMAP_MCBSP_CLK_FALLING
comma
DECL|typedef|omap_mcbsp_clk_polarity
)brace
id|omap_mcbsp_clk_polarity
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|OMAP_MCBSP_FS_ACTIVE_HIGH
id|OMAP_MCBSP_FS_ACTIVE_HIGH
op_assign
l_int|0
comma
DECL|enumerator|OMAP_MCBSP_FS_ACTIVE_LOW
id|OMAP_MCBSP_FS_ACTIVE_LOW
comma
DECL|typedef|omap_mcbsp_fs_polarity
)brace
id|omap_mcbsp_fs_polarity
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|OMAP_MCBSP_CLK_STP_MODE_NO_DELAY
id|OMAP_MCBSP_CLK_STP_MODE_NO_DELAY
op_assign
l_int|0
comma
DECL|enumerator|OMAP_MCBSP_CLK_STP_MODE_DELAY
id|OMAP_MCBSP_CLK_STP_MODE_DELAY
comma
DECL|typedef|omap_mcbsp_clk_stp_mode
)brace
id|omap_mcbsp_clk_stp_mode
suffix:semicolon
multiline_comment|/******* SPI specific mode **********/
r_typedef
r_enum
(brace
DECL|enumerator|OMAP_MCBSP_SPI_MASTER
id|OMAP_MCBSP_SPI_MASTER
op_assign
l_int|0
comma
DECL|enumerator|OMAP_MCBSP_SPI_SLAVE
id|OMAP_MCBSP_SPI_SLAVE
comma
DECL|typedef|omap_mcbsp_spi_mode
)brace
id|omap_mcbsp_spi_mode
suffix:semicolon
DECL|struct|omap_mcbsp_spi_cfg
r_struct
id|omap_mcbsp_spi_cfg
(brace
DECL|member|spi_mode
id|omap_mcbsp_spi_mode
id|spi_mode
suffix:semicolon
DECL|member|rx_clock_polarity
id|omap_mcbsp_clk_polarity
id|rx_clock_polarity
suffix:semicolon
DECL|member|tx_clock_polarity
id|omap_mcbsp_clk_polarity
id|tx_clock_polarity
suffix:semicolon
DECL|member|fsx_polarity
id|omap_mcbsp_fs_polarity
id|fsx_polarity
suffix:semicolon
DECL|member|clk_div
id|u8
id|clk_div
suffix:semicolon
DECL|member|clk_stp_mode
id|omap_mcbsp_clk_stp_mode
id|clk_stp_mode
suffix:semicolon
DECL|member|word_length
id|omap_mcbsp_word_length
id|word_length
suffix:semicolon
)brace
suffix:semicolon
r_void
id|omap_mcbsp_config
c_func
(paren
r_int
r_int
id|id
comma
r_const
r_struct
id|omap_mcbsp_reg_cfg
op_star
id|config
)paren
suffix:semicolon
r_int
id|omap_mcbsp_request
c_func
(paren
r_int
r_int
id|id
)paren
suffix:semicolon
r_void
id|omap_mcbsp_free
c_func
(paren
r_int
r_int
id|id
)paren
suffix:semicolon
r_void
id|omap_mcbsp_start
c_func
(paren
r_int
r_int
id|id
)paren
suffix:semicolon
r_void
id|omap_mcbsp_stop
c_func
(paren
r_int
r_int
id|id
)paren
suffix:semicolon
r_void
id|omap_mcbsp_xmit_word
c_func
(paren
r_int
r_int
id|id
comma
id|u32
id|word
)paren
suffix:semicolon
id|u32
id|omap_mcbsp_recv_word
c_func
(paren
r_int
r_int
id|id
)paren
suffix:semicolon
r_int
id|omap_mcbsp_xmit_buffer
c_func
(paren
r_int
r_int
id|id
comma
id|dma_addr_t
id|buffer
comma
r_int
r_int
id|length
)paren
suffix:semicolon
r_int
id|omap_mcbsp_recv_buffer
c_func
(paren
r_int
r_int
id|id
comma
id|dma_addr_t
id|buffer
comma
r_int
r_int
id|length
)paren
suffix:semicolon
multiline_comment|/* SPI specific API */
r_void
id|omap_mcbsp_set_spi_mode
c_func
(paren
r_int
r_int
id|id
comma
r_const
r_struct
id|omap_mcbsp_spi_cfg
op_star
id|spi_cfg
)paren
suffix:semicolon
macro_line|#endif
eof
