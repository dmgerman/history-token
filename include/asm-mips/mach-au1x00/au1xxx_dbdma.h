multiline_comment|/*&n; *&n; * BRIEF MODULE DESCRIPTION&n; *&t;Include file for Alchemy Semiconductor&squot;s Au1550 Descriptor&n; *&t;Based DMA Controller.&n; *&n; * Copyright 2004 Embedded Edge, LLC&n; *&t;dan@embeddededge.com&n; *&n; *  This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR IMPLIED&n; *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; */
multiline_comment|/* Specifics for the Au1xxx Descriptor-Based DMA Controllers, first&n; * seen in the AU1550 part.&n; */
macro_line|#ifndef _AU1000_DBDMA_H_
DECL|macro|_AU1000_DBDMA_H_
mdefine_line|#define _AU1000_DBDMA_H_
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifndef _LANGUAGE_ASSEMBLY
multiline_comment|/* The DMA base addresses.&n; * The Channels are every 256 bytes (0x0100) from the channel 0 base.&n; * Interrupt status/enable is bits 15:0 for channels 15 to zero.&n; */
DECL|macro|DDMA_GLOBAL_BASE
mdefine_line|#define DDMA_GLOBAL_BASE&t;0xb4003000
DECL|macro|DDMA_CHANNEL_BASE
mdefine_line|#define DDMA_CHANNEL_BASE&t;0xb4002000
DECL|struct|dbdma_global
r_typedef
r_struct
id|dbdma_global
(brace
DECL|member|ddma_config
id|u32
id|ddma_config
suffix:semicolon
DECL|member|ddma_intstat
id|u32
id|ddma_intstat
suffix:semicolon
DECL|member|ddma_throttle
id|u32
id|ddma_throttle
suffix:semicolon
DECL|member|ddma_inten
id|u32
id|ddma_inten
suffix:semicolon
DECL|typedef|dbdma_global_t
)brace
id|dbdma_global_t
suffix:semicolon
multiline_comment|/* General Configuration.&n;*/
DECL|macro|DDMA_CONFIG_AF
mdefine_line|#define DDMA_CONFIG_AF&t;&t;(1 &lt;&lt; 2)
DECL|macro|DDMA_CONFIG_AH
mdefine_line|#define DDMA_CONFIG_AH&t;&t;(1 &lt;&lt; 1)
DECL|macro|DDMA_CONFIG_AL
mdefine_line|#define DDMA_CONFIG_AL&t;&t;(1 &lt;&lt; 0)
DECL|macro|DDMA_THROTTLE_EN
mdefine_line|#define DDMA_THROTTLE_EN&t;(1 &lt;&lt; 31)
multiline_comment|/* The structure of a DMA Channel.&n;*/
DECL|struct|au1xxx_dma_channel
r_typedef
r_struct
id|au1xxx_dma_channel
(brace
DECL|member|ddma_cfg
id|u32
id|ddma_cfg
suffix:semicolon
multiline_comment|/* See below */
DECL|member|ddma_desptr
id|u32
id|ddma_desptr
suffix:semicolon
multiline_comment|/* 32-byte aligned pointer to descriptor */
DECL|member|ddma_statptr
id|u32
id|ddma_statptr
suffix:semicolon
multiline_comment|/* word aligned pointer to status word */
DECL|member|ddma_dbell
id|u32
id|ddma_dbell
suffix:semicolon
multiline_comment|/* A write activates channel operation */
DECL|member|ddma_irq
id|u32
id|ddma_irq
suffix:semicolon
multiline_comment|/* If bit 0 set, interrupt pending */
DECL|member|ddma_stat
id|u32
id|ddma_stat
suffix:semicolon
multiline_comment|/* See below */
DECL|member|ddma_bytecnt
id|u32
id|ddma_bytecnt
suffix:semicolon
multiline_comment|/* Byte count, valid only when chan idle */
multiline_comment|/* Remainder, up to the 256 byte boundary, is reserved.&n;&t;*/
DECL|typedef|au1x_dma_chan_t
)brace
id|au1x_dma_chan_t
suffix:semicolon
DECL|macro|DDMA_CFG_SED
mdefine_line|#define DDMA_CFG_SED&t;(1 &lt;&lt; 9)&t;/* source DMA level/edge detect */
DECL|macro|DDMA_CFG_SP
mdefine_line|#define DDMA_CFG_SP&t;(1 &lt;&lt; 8)&t;/* source DMA polarity */
DECL|macro|DDMA_CFG_DED
mdefine_line|#define DDMA_CFG_DED&t;(1 &lt;&lt; 7)&t;/* destination DMA level/edge detect */
DECL|macro|DDMA_CFG_DP
mdefine_line|#define DDMA_CFG_DP&t;(1 &lt;&lt; 6)&t;/* destination DMA polarity */
DECL|macro|DDMA_CFG_SYNC
mdefine_line|#define DDMA_CFG_SYNC&t;(1 &lt;&lt; 5)&t;/* Sync static bus controller */
DECL|macro|DDMA_CFG_PPR
mdefine_line|#define DDMA_CFG_PPR&t;(1 &lt;&lt; 4)&t;/* PCI posted read/write control */
DECL|macro|DDMA_CFG_DFN
mdefine_line|#define DDMA_CFG_DFN&t;(1 &lt;&lt; 3)&t;/* Descriptor fetch non-coherent */
DECL|macro|DDMA_CFG_SBE
mdefine_line|#define DDMA_CFG_SBE&t;(1 &lt;&lt; 2)&t;/* Source big endian */
DECL|macro|DDMA_CFG_DBE
mdefine_line|#define DDMA_CFG_DBE&t;(1 &lt;&lt; 1)&t;/* Destination big endian */
DECL|macro|DDMA_CFG_EN
mdefine_line|#define DDMA_CFG_EN&t;(1 &lt;&lt; 0)&t;/* Channel enable */
multiline_comment|/* Always set when descriptor processing done, regardless of&n; * interrupt enable state.  Reflected in global intstat, don&squot;t&n; * clear this until global intstat is read/used.&n; */
DECL|macro|DDMA_IRQ_IN
mdefine_line|#define DDMA_IRQ_IN&t;(1 &lt;&lt; 0)
DECL|macro|DDMA_STAT_DB
mdefine_line|#define DDMA_STAT_DB&t;(1 &lt;&lt; 2)&t;/* Doorbell pushed */
DECL|macro|DDMA_STAT_V
mdefine_line|#define DDMA_STAT_V&t;(1 &lt;&lt; 1)&t;/* Descriptor valid */
DECL|macro|DDMA_STAT_H
mdefine_line|#define DDMA_STAT_H&t;(1 &lt;&lt; 0)&t;/* Channel Halted */
multiline_comment|/* &quot;Standard&quot; DDMA Descriptor.&n; * Must be 32-byte aligned.&n; */
DECL|struct|au1xxx_ddma_desc
r_typedef
r_struct
id|au1xxx_ddma_desc
(brace
DECL|member|dscr_cmd0
id|u32
id|dscr_cmd0
suffix:semicolon
multiline_comment|/* See below */
DECL|member|dscr_cmd1
id|u32
id|dscr_cmd1
suffix:semicolon
multiline_comment|/* See below */
DECL|member|dscr_source0
id|u32
id|dscr_source0
suffix:semicolon
multiline_comment|/* source phys address */
DECL|member|dscr_source1
id|u32
id|dscr_source1
suffix:semicolon
multiline_comment|/* See below */
DECL|member|dscr_dest0
id|u32
id|dscr_dest0
suffix:semicolon
multiline_comment|/* Destination address */
DECL|member|dscr_dest1
id|u32
id|dscr_dest1
suffix:semicolon
multiline_comment|/* See below */
DECL|member|dscr_stat
id|u32
id|dscr_stat
suffix:semicolon
multiline_comment|/* completion status */
DECL|member|dscr_nxtptr
id|u32
id|dscr_nxtptr
suffix:semicolon
multiline_comment|/* Next descriptor pointer (mostly) */
DECL|typedef|au1x_ddma_desc_t
)brace
id|au1x_ddma_desc_t
suffix:semicolon
DECL|macro|DSCR_CMD0_V
mdefine_line|#define DSCR_CMD0_V&t;&t;(1 &lt;&lt; 31)&t;/* Descriptor valid */
DECL|macro|DSCR_CMD0_MEM
mdefine_line|#define DSCR_CMD0_MEM&t;&t;(1 &lt;&lt; 30)&t;/* mem-mem transfer */
DECL|macro|DSCR_CMD0_SID_MASK
mdefine_line|#define DSCR_CMD0_SID_MASK&t;(0x1f &lt;&lt; 25)&t;/* Source ID */
DECL|macro|DSCR_CMD0_DID_MASK
mdefine_line|#define DSCR_CMD0_DID_MASK&t;(0x1f &lt;&lt; 20)&t;/* Destination ID */
DECL|macro|DSCR_CMD0_SW_MASK
mdefine_line|#define DSCR_CMD0_SW_MASK&t;(0x3 &lt;&lt; 18)&t;/* Source Width */
DECL|macro|DSCR_CMD0_DW_MASK
mdefine_line|#define DSCR_CMD0_DW_MASK&t;(0x3 &lt;&lt; 16)&t;/* Destination Width */
DECL|macro|DSCR_CMD0_ARB
mdefine_line|#define DSCR_CMD0_ARB&t;&t;(0x1 &lt;&lt; 15)&t;/* Set for Hi Pri */
DECL|macro|DSCR_CMD0_DT_MASK
mdefine_line|#define DSCR_CMD0_DT_MASK&t;(0x3 &lt;&lt; 13)&t;/* Descriptor Type */
DECL|macro|DSCR_CMD0_SN
mdefine_line|#define DSCR_CMD0_SN&t;&t;(0x1 &lt;&lt; 12)&t;/* Source non-coherent */
DECL|macro|DSCR_CMD0_DN
mdefine_line|#define DSCR_CMD0_DN&t;&t;(0x1 &lt;&lt; 11)&t;/* Destination non-coherent */
DECL|macro|DSCR_CMD0_SM
mdefine_line|#define DSCR_CMD0_SM&t;&t;(0x1 &lt;&lt; 10)&t;/* Stride mode */
DECL|macro|DSCR_CMD0_IE
mdefine_line|#define DSCR_CMD0_IE&t;&t;(0x1 &lt;&lt; 8)&t;/* Interrupt Enable */
DECL|macro|DSCR_CMD0_SP
mdefine_line|#define DSCR_CMD0_SP&t;&t;(0x1 &lt;&lt; 4)&t;/* Status pointer select */
DECL|macro|DSCR_CMD0_CV
mdefine_line|#define DSCR_CMD0_CV&t;&t;(0x1 &lt;&lt; 2)&t;/* Clear Valid when done */
DECL|macro|DSCR_CMD0_ST_MASK
mdefine_line|#define DSCR_CMD0_ST_MASK&t;(0x3 &lt;&lt; 0)&t;/* Status instruction */
multiline_comment|/* Command 0 device IDs.&n;*/
DECL|macro|DSCR_CMD0_UART0_TX
mdefine_line|#define DSCR_CMD0_UART0_TX&t;0
DECL|macro|DSCR_CMD0_UART0_RX
mdefine_line|#define DSCR_CMD0_UART0_RX&t;1
DECL|macro|DSCR_CMD0_UART3_TX
mdefine_line|#define DSCR_CMD0_UART3_TX&t;2
DECL|macro|DSCR_CMD0_UART3_RX
mdefine_line|#define DSCR_CMD0_UART3_RX&t;3
DECL|macro|DSCR_CMD0_DMA_REQ0
mdefine_line|#define DSCR_CMD0_DMA_REQ0&t;4
DECL|macro|DSCR_CMD0_DMA_REQ1
mdefine_line|#define DSCR_CMD0_DMA_REQ1&t;5
DECL|macro|DSCR_CMD0_DMA_REQ2
mdefine_line|#define DSCR_CMD0_DMA_REQ2&t;6
DECL|macro|DSCR_CMD0_DMA_REQ3
mdefine_line|#define DSCR_CMD0_DMA_REQ3&t;7
DECL|macro|DSCR_CMD0_USBDEV_RX0
mdefine_line|#define DSCR_CMD0_USBDEV_RX0&t;8
DECL|macro|DSCR_CMD0_USBDEV_TX0
mdefine_line|#define DSCR_CMD0_USBDEV_TX0&t;9
DECL|macro|DSCR_CMD0_USBDEV_TX1
mdefine_line|#define DSCR_CMD0_USBDEV_TX1&t;10
DECL|macro|DSCR_CMD0_USBDEV_TX2
mdefine_line|#define DSCR_CMD0_USBDEV_TX2&t;11
DECL|macro|DSCR_CMD0_USBDEV_RX3
mdefine_line|#define DSCR_CMD0_USBDEV_RX3&t;12
DECL|macro|DSCR_CMD0_USBDEV_RX4
mdefine_line|#define DSCR_CMD0_USBDEV_RX4&t;13
DECL|macro|DSCR_CMD0_PSC0_TX
mdefine_line|#define DSCR_CMD0_PSC0_TX&t;14
DECL|macro|DSCR_CMD0_PSC0_RX
mdefine_line|#define DSCR_CMD0_PSC0_RX&t;15
DECL|macro|DSCR_CMD0_PSC1_TX
mdefine_line|#define DSCR_CMD0_PSC1_TX&t;16
DECL|macro|DSCR_CMD0_PSC1_RX
mdefine_line|#define DSCR_CMD0_PSC1_RX&t;17
DECL|macro|DSCR_CMD0_PSC2_TX
mdefine_line|#define DSCR_CMD0_PSC2_TX&t;18
DECL|macro|DSCR_CMD0_PSC2_RX
mdefine_line|#define DSCR_CMD0_PSC2_RX&t;19
DECL|macro|DSCR_CMD0_PSC3_TX
mdefine_line|#define DSCR_CMD0_PSC3_TX&t;20
DECL|macro|DSCR_CMD0_PSC3_RX
mdefine_line|#define DSCR_CMD0_PSC3_RX&t;21
DECL|macro|DSCR_CMD0_PCI_WRITE
mdefine_line|#define DSCR_CMD0_PCI_WRITE&t;22
DECL|macro|DSCR_CMD0_NAND_FLASH
mdefine_line|#define DSCR_CMD0_NAND_FLASH&t;23
DECL|macro|DSCR_CMD0_MAC0_RX
mdefine_line|#define DSCR_CMD0_MAC0_RX&t;24
DECL|macro|DSCR_CMD0_MAC0_TX
mdefine_line|#define DSCR_CMD0_MAC0_TX&t;25
DECL|macro|DSCR_CMD0_MAC1_RX
mdefine_line|#define DSCR_CMD0_MAC1_RX&t;26
DECL|macro|DSCR_CMD0_MAC1_TX
mdefine_line|#define DSCR_CMD0_MAC1_TX&t;27
DECL|macro|DSCR_CMD0_THROTTLE
mdefine_line|#define DSCR_CMD0_THROTTLE&t;30
DECL|macro|DSCR_CMD0_ALWAYS
mdefine_line|#define DSCR_CMD0_ALWAYS&t;31
DECL|macro|DSCR_NDEV_IDS
mdefine_line|#define DSCR_NDEV_IDS&t;&t;32
DECL|macro|DSCR_CMD0_SID
mdefine_line|#define DSCR_CMD0_SID(x)&t;(((x) &amp; 0x1f) &lt;&lt; 25)
DECL|macro|DSCR_CMD0_DID
mdefine_line|#define DSCR_CMD0_DID(x)&t;(((x) &amp; 0x1f) &lt;&lt; 20)
multiline_comment|/* Source/Destination transfer width.&n;*/
DECL|macro|DSCR_CMD0_BYTE
mdefine_line|#define DSCR_CMD0_BYTE&t;&t;0
DECL|macro|DSCR_CMD0_HALFWORD
mdefine_line|#define DSCR_CMD0_HALFWORD&t;1
DECL|macro|DSCR_CMD0_WORD
mdefine_line|#define DSCR_CMD0_WORD&t;&t;2
DECL|macro|DSCR_CMD0_SW
mdefine_line|#define DSCR_CMD0_SW(x)&t;&t;(((x) &amp; 0x3) &lt;&lt; 18)
DECL|macro|DSCR_CMD0_DW
mdefine_line|#define DSCR_CMD0_DW(x)&t;&t;(((x) &amp; 0x3) &lt;&lt; 16)
multiline_comment|/* DDMA Descriptor Type.&n;*/
DECL|macro|DSCR_CMD0_STANDARD
mdefine_line|#define DSCR_CMD0_STANDARD&t;0
DECL|macro|DSCR_CMD0_LITERAL
mdefine_line|#define DSCR_CMD0_LITERAL&t;1
DECL|macro|DSCR_CMD0_CMP_BRANCH
mdefine_line|#define DSCR_CMD0_CMP_BRANCH&t;2
DECL|macro|DSCR_CMD0_DT
mdefine_line|#define DSCR_CMD0_DT(x)&t;&t;(((x) &amp; 0x3) &lt;&lt; 13)
multiline_comment|/* Status Instruction.&n;*/
DECL|macro|DSCR_CMD0_ST_NOCHANGE
mdefine_line|#define DSCR_CMD0_ST_NOCHANGE&t;0&t;/* Don&squot;t change */
DECL|macro|DSCR_CMD0_ST_CURRENT
mdefine_line|#define DSCR_CMD0_ST_CURRENT&t;1&t;/* Write current status */
DECL|macro|DSCR_CMD0_ST_CMD0
mdefine_line|#define DSCR_CMD0_ST_CMD0&t;2&t;/* Write cmd0 with V cleared */
DECL|macro|DSCR_CMD0_ST_BYTECNT
mdefine_line|#define DSCR_CMD0_ST_BYTECNT&t;3&t;/* Write remaining byte count */
DECL|macro|DSCR_CMD0_ST
mdefine_line|#define DSCR_CMD0_ST(x)&t;&t;(((x) &amp; 0x3) &lt;&lt; 0)
multiline_comment|/* Descriptor Command 1&n;*/
DECL|macro|DSCR_CMD1_SUPTR_MASK
mdefine_line|#define DSCR_CMD1_SUPTR_MASK&t;(0xf &lt;&lt; 28)&t;/* upper 4 bits of src addr */
DECL|macro|DSCR_CMD1_DUPTR_MASK
mdefine_line|#define DSCR_CMD1_DUPTR_MASK&t;(0xf &lt;&lt; 24)&t;/* upper 4 bits of dest addr */
DECL|macro|DSCR_CMD1_FL_MASK
mdefine_line|#define DSCR_CMD1_FL_MASK&t;(0x3 &lt;&lt; 22)&t;/* Flag bits */
DECL|macro|DSCR_CMD1_BC_MASK
mdefine_line|#define DSCR_CMD1_BC_MASK&t;(0x3fffff)&t;/* Byte count */
multiline_comment|/* Flag description.&n;*/
DECL|macro|DSCR_CMD1_FL_MEM_STRIDE0
mdefine_line|#define DSCR_CMD1_FL_MEM_STRIDE0&t;0
DECL|macro|DSCR_CMD1_FL_MEM_STRIDE1
mdefine_line|#define DSCR_CMD1_FL_MEM_STRIDE1&t;1
DECL|macro|DSCR_CMD1_FL_MEM_STRIDE2
mdefine_line|#define DSCR_CMD1_FL_MEM_STRIDE2&t;2
DECL|macro|DSCR_CMD1_FL
mdefine_line|#define DSCR_CMD1_FL(x)&t;&t;(((x) &amp; 0x3) &lt;&lt; 22)
multiline_comment|/* Source1, 1-dimensional stride.&n;*/
DECL|macro|DSCR_SRC1_STS_MASK
mdefine_line|#define DSCR_SRC1_STS_MASK&t;(3 &lt;&lt; 30)&t;/* Src xfer size */
DECL|macro|DSCR_SRC1_SAM_MASK
mdefine_line|#define DSCR_SRC1_SAM_MASK&t;(3 &lt;&lt; 28)&t;/* Src xfer movement */
DECL|macro|DSCR_SRC1_SB_MASK
mdefine_line|#define DSCR_SRC1_SB_MASK&t;(0x3fff &lt;&lt; 14)&t;/* Block size */
DECL|macro|DSCR_SRC1_SB
mdefine_line|#define DSCR_SRC1_SB(x)&t;&t;(((x) &amp; 0x3fff) &lt;&lt; 14)
DECL|macro|DSCR_SRC1_SS_MASK
mdefine_line|#define DSCR_SRC1_SS_MASK&t;(0x3fff &lt;&lt; 0)&t;/* Stride */
DECL|macro|DSCR_SRC1_SS
mdefine_line|#define DSCR_SRC1_SS(x)&t;&t;(((x) &amp; 0x3fff) &lt;&lt; 0)
multiline_comment|/* Dest1, 1-dimensional stride.&n;*/
DECL|macro|DSCR_DEST1_DTS_MASK
mdefine_line|#define DSCR_DEST1_DTS_MASK&t;(3 &lt;&lt; 30)&t;/* Dest xfer size */
DECL|macro|DSCR_DEST1_DAM_MASK
mdefine_line|#define DSCR_DEST1_DAM_MASK&t;(3 &lt;&lt; 28)&t;/* Dest xfer movement */
DECL|macro|DSCR_DEST1_DB_MASK
mdefine_line|#define DSCR_DEST1_DB_MASK&t;(0x3fff &lt;&lt; 14)&t;/* Block size */
DECL|macro|DSCR_DEST1_DB
mdefine_line|#define DSCR_DEST1_DB(x)&t;(((x) &amp; 0x3fff) &lt;&lt; 14)
DECL|macro|DSCR_DEST1_DS_MASK
mdefine_line|#define DSCR_DEST1_DS_MASK&t;(0x3fff &lt;&lt; 0)&t;/* Stride */
DECL|macro|DSCR_DEST1_DS
mdefine_line|#define DSCR_DEST1_DS(x)&t;(((x) &amp; 0x3fff) &lt;&lt; 0)
DECL|macro|DSCR_xTS_SIZE1
mdefine_line|#define DSCR_xTS_SIZE1&t;&t;0
DECL|macro|DSCR_xTS_SIZE2
mdefine_line|#define DSCR_xTS_SIZE2&t;&t;1
DECL|macro|DSCR_xTS_SIZE4
mdefine_line|#define DSCR_xTS_SIZE4&t;&t;2
DECL|macro|DSCR_xTS_SIZE8
mdefine_line|#define DSCR_xTS_SIZE8&t;&t;3
DECL|macro|DSCR_SRC1_STS
mdefine_line|#define DSCR_SRC1_STS(x)&t;(((x) &amp; 3) &lt;&lt; 30)
DECL|macro|DSCR_DEST1_DTS
mdefine_line|#define DSCR_DEST1_DTS(x)&t;(((x) &amp; 3) &lt;&lt; 30)
DECL|macro|DSCR_xAM_INCREMENT
mdefine_line|#define DSCR_xAM_INCREMENT&t;0
DECL|macro|DSCR_xAM_DECREMENT
mdefine_line|#define DSCR_xAM_DECREMENT&t;1
DECL|macro|DSCR_xAM_STATIC
mdefine_line|#define DSCR_xAM_STATIC&t;&t;2
DECL|macro|DSCR_xAM_BURST
mdefine_line|#define DSCR_xAM_BURST&t;&t;3
DECL|macro|DSCR_SRC1_SAM
mdefine_line|#define DSCR_SRC1_SAM(x)&t;(((x) &amp; 3) &lt;&lt; 28)
DECL|macro|DSCR_DEST1_DAM
mdefine_line|#define DSCR_DEST1_DAM(x)&t;(((x) &amp; 3) &lt;&lt; 28)
multiline_comment|/* The next descriptor pointer.&n;*/
DECL|macro|DSCR_NXTPTR_MASK
mdefine_line|#define DSCR_NXTPTR_MASK&t;(0x07ffffff)
DECL|macro|DSCR_NXTPTR
mdefine_line|#define DSCR_NXTPTR(x)&t;&t;((x) &gt;&gt; 5)
DECL|macro|DSCR_GET_NXTPTR
mdefine_line|#define DSCR_GET_NXTPTR(x)&t;((x) &lt;&lt; 5)
DECL|macro|DSCR_NXTPTR_MS
mdefine_line|#define DSCR_NXTPTR_MS&t;&t;(1 &lt;&lt; 27)
multiline_comment|/* The number of DBDMA channels.&n;*/
DECL|macro|NUM_DBDMA_CHANS
mdefine_line|#define NUM_DBDMA_CHANS&t;16
multiline_comment|/* External functions for drivers to use.&n;*/
multiline_comment|/* Use this to allocate a dbdma channel.  The device ids are one of the&n; * DSCR_CMD0 devices IDs, which is usually redefined to a more&n; * meaningful name.  The &squot;callback&squot; is called during dma completion&n; * interrupt.&n; */
id|u32
id|au1xxx_dbdma_chan_alloc
c_func
(paren
id|u32
id|srcid
comma
id|u32
id|destid
comma
r_void
(paren
op_star
id|callback
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
id|callparam
)paren
suffix:semicolon
DECL|macro|DBDMA_MEM_CHAN
mdefine_line|#define DBDMA_MEM_CHAN&t;DSCR_CMD0_ALWAYS
multiline_comment|/* ACK!  These should be in a board specific description file.&n;*/
macro_line|#ifdef CONFIG_MIPS_PB1550
DECL|macro|DBDMA_AC97_TX_CHAN
mdefine_line|#define DBDMA_AC97_TX_CHAN DSCR_CMD0_PSC1_TX
DECL|macro|DBDMA_AC97_RX_CHAN
mdefine_line|#define DBDMA_AC97_RX_CHAN DSCR_CMD0_PSC1_RX
macro_line|#endif
macro_line|#ifdef CONFIG_MIPS_DB1550
DECL|macro|DBDMA_AC97_TX_CHAN
mdefine_line|#define DBDMA_AC97_TX_CHAN DSCR_CMD0_PSC1_TX
DECL|macro|DBDMA_AC97_RX_CHAN
mdefine_line|#define DBDMA_AC97_RX_CHAN DSCR_CMD0_PSC1_RX
macro_line|#endif
multiline_comment|/* Set the device width of a in/out fifo.&n;*/
id|u32
id|au1xxx_dbdma_set_devwidth
c_func
(paren
id|u32
id|chanid
comma
r_int
id|bits
)paren
suffix:semicolon
multiline_comment|/* Allocate a ring of descriptors for dbdma.&n;*/
id|u32
id|au1xxx_dbdma_ring_alloc
c_func
(paren
id|u32
id|chanid
comma
r_int
id|entries
)paren
suffix:semicolon
multiline_comment|/* Put buffers on source/destination descriptors.&n;*/
id|u32
id|au1xxx_dbdma_put_source
c_func
(paren
id|u32
id|chanid
comma
r_void
op_star
id|buf
comma
r_int
id|nbytes
)paren
suffix:semicolon
id|u32
id|au1xxx_dbdma_put_dest
c_func
(paren
id|u32
id|chanid
comma
r_void
op_star
id|buf
comma
r_int
id|nbytes
)paren
suffix:semicolon
multiline_comment|/* Get a buffer from the destination descriptor.&n;*/
id|u32
id|au1xxx_dbdma_get_dest
c_func
(paren
id|u32
id|chanid
comma
r_void
op_star
op_star
id|buf
comma
r_int
op_star
id|nbytes
)paren
suffix:semicolon
r_void
id|au1xxx_dbdma_stop
c_func
(paren
id|u32
id|chanid
)paren
suffix:semicolon
r_void
id|au1xxx_dbdma_start
c_func
(paren
id|u32
id|chanid
)paren
suffix:semicolon
r_void
id|au1xxx_dbdma_reset
c_func
(paren
id|u32
id|chanid
)paren
suffix:semicolon
id|u32
id|au1xxx_get_dma_residue
c_func
(paren
id|u32
id|chanid
)paren
suffix:semicolon
r_void
id|au1xxx_dbdma_chan_free
c_func
(paren
id|u32
id|chanid
)paren
suffix:semicolon
r_void
id|au1xxx_dbdma_dump
c_func
(paren
id|u32
id|chanid
)paren
suffix:semicolon
macro_line|#endif /* _LANGUAGE_ASSEMBLY */
macro_line|#endif /* _AU1000_DBDMA_H_ */
eof
