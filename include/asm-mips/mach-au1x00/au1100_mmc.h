multiline_comment|/*&n; * BRIEF MODULE DESCRIPTION&n; *&t;Defines for using the MMC/SD controllers on the&n; *      Alchemy Au1100 mips processor.&n; *&n; * Copyright (c) 2003 Embedded Edge, LLC.&n; * Author: Embedded Edge, LLC.&n; *         &t;dan@embeddededge.com or tim@embeddededge.com&n; *&n; *  This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR IMPLIED&n; *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
multiline_comment|/*&n; * AU1100 MMC/SD definitions.&n; *&n; * From &quot;AMD Alchemy Solutions Au1100 Processor Data Book - Preliminary&quot;&n; *    June, 2003&n; */
macro_line|#ifndef __ASM_AU1100_MMC_H
DECL|macro|__ASM_AU1100_MMC_H
mdefine_line|#define __ASM_AU1100_MMC_H
DECL|macro|NUM_AU1100_MMC_CONTROLLERS
mdefine_line|#define NUM_AU1100_MMC_CONTROLLERS&t;2
DECL|macro|AU1100_SD_IRQ
mdefine_line|#define AU1100_SD_IRQ&t;2
DECL|macro|SD0_BASE
mdefine_line|#define SD0_BASE&t;0xB0600000
DECL|macro|SD1_BASE
mdefine_line|#define SD1_BASE&t;0xB0680000
multiline_comment|/*&n; *  Register offsets.&n; */
DECL|macro|SD_TXPORT
mdefine_line|#define SD_TXPORT&t;(0x0000)
DECL|macro|SD_RXPORT
mdefine_line|#define SD_RXPORT&t;(0x0004)
DECL|macro|SD_CONFIG
mdefine_line|#define SD_CONFIG&t;(0x0008)
DECL|macro|SD_ENABLE
mdefine_line|#define SD_ENABLE&t;(0x000C)
DECL|macro|SD_CONFIG2
mdefine_line|#define SD_CONFIG2&t;(0x0010)
DECL|macro|SD_BLKSIZE
mdefine_line|#define SD_BLKSIZE&t;(0x0014)
DECL|macro|SD_STATUS
mdefine_line|#define SD_STATUS&t;(0x0018)
DECL|macro|SD_DEBUG
mdefine_line|#define SD_DEBUG&t;(0x001C)
DECL|macro|SD_CMD
mdefine_line|#define SD_CMD&t;&t;(0x0020)
DECL|macro|SD_CMDARG
mdefine_line|#define SD_CMDARG&t;(0x0024)
DECL|macro|SD_RESP3
mdefine_line|#define SD_RESP3&t;(0x0028)
DECL|macro|SD_RESP2
mdefine_line|#define SD_RESP2&t;(0x002C)
DECL|macro|SD_RESP1
mdefine_line|#define SD_RESP1&t;(0x0030)
DECL|macro|SD_RESP0
mdefine_line|#define SD_RESP0&t;(0x0034)
DECL|macro|SD_TIMEOUT
mdefine_line|#define SD_TIMEOUT&t;(0x0038)
multiline_comment|/*&n; *  SD_TXPORT bit definitions.&n; */
DECL|macro|SD_TXPORT_TXD
mdefine_line|#define SD_TXPORT_TXD&t;(0x000000ff)
multiline_comment|/*&n; *  SD_RXPORT bit definitions.&n; */
DECL|macro|SD_RXPORT_RXD
mdefine_line|#define SD_RXPORT_RXD&t;(0x000000ff)
multiline_comment|/*&n; *  SD_CONFIG bit definitions.&n; */
DECL|macro|SD_CONFIG_DIV
mdefine_line|#define SD_CONFIG_DIV&t;(0x000001ff)
DECL|macro|SD_CONFIG_DE
mdefine_line|#define SD_CONFIG_DE&t;(0x00000200)
DECL|macro|SD_CONFIG_NE
mdefine_line|#define SD_CONFIG_NE&t;(0x00000400)
DECL|macro|SD_CONFIG_TU
mdefine_line|#define SD_CONFIG_TU&t;(0x00000800)
DECL|macro|SD_CONFIG_TO
mdefine_line|#define SD_CONFIG_TO&t;(0x00001000)
DECL|macro|SD_CONFIG_RU
mdefine_line|#define SD_CONFIG_RU&t;(0x00002000)
DECL|macro|SD_CONFIG_RO
mdefine_line|#define SD_CONFIG_RO&t;(0x00004000)
DECL|macro|SD_CONFIG_I
mdefine_line|#define SD_CONFIG_I&t;(0x00008000)
DECL|macro|SD_CONFIG_CR
mdefine_line|#define SD_CONFIG_CR&t;(0x00010000)
DECL|macro|SD_CONFIG_RAT
mdefine_line|#define SD_CONFIG_RAT&t;(0x00020000)
DECL|macro|SD_CONFIG_DD
mdefine_line|#define SD_CONFIG_DD&t;(0x00040000)
DECL|macro|SD_CONFIG_DT
mdefine_line|#define SD_CONFIG_DT&t;(0x00080000)
DECL|macro|SD_CONFIG_SC
mdefine_line|#define SD_CONFIG_SC&t;(0x00100000)
DECL|macro|SD_CONFIG_RC
mdefine_line|#define SD_CONFIG_RC&t;(0x00200000)
DECL|macro|SD_CONFIG_WC
mdefine_line|#define SD_CONFIG_WC&t;(0x00400000)
DECL|macro|SD_CONFIG_xxx
mdefine_line|#define SD_CONFIG_xxx&t;(0x00800000)
DECL|macro|SD_CONFIG_TH
mdefine_line|#define SD_CONFIG_TH&t;(0x01000000)
DECL|macro|SD_CONFIG_TE
mdefine_line|#define SD_CONFIG_TE&t;(0x02000000)
DECL|macro|SD_CONFIG_TA
mdefine_line|#define SD_CONFIG_TA&t;(0x04000000)
DECL|macro|SD_CONFIG_RH
mdefine_line|#define SD_CONFIG_RH&t;(0x08000000)
DECL|macro|SD_CONFIG_RA
mdefine_line|#define SD_CONFIG_RA&t;(0x10000000)
DECL|macro|SD_CONFIG_RF
mdefine_line|#define SD_CONFIG_RF&t;(0x20000000)
DECL|macro|SD_CONFIG_CD
mdefine_line|#define SD_CONFIG_CD&t;(0x40000000)
DECL|macro|SD_CONFIG_SI
mdefine_line|#define SD_CONFIG_SI&t;(0x80000000)
multiline_comment|/*&n; *  SD_ENABLE bit definitions.&n; */
DECL|macro|SD_ENABLE_CE
mdefine_line|#define SD_ENABLE_CE&t;(0x00000001)
DECL|macro|SD_ENABLE_R
mdefine_line|#define SD_ENABLE_R&t;(0x00000002)
multiline_comment|/*&n; *  SD_CONFIG2 bit definitions.&n; */
DECL|macro|SD_CONFIG2_EN
mdefine_line|#define SD_CONFIG2_EN&t;(0x00000001)
DECL|macro|SD_CONFIG2_FF
mdefine_line|#define SD_CONFIG2_FF&t;(0x00000002)
DECL|macro|SD_CONFIG2_xx1
mdefine_line|#define SD_CONFIG2_xx1&t;(0x00000004)
DECL|macro|SD_CONFIG2_DF
mdefine_line|#define SD_CONFIG2_DF&t;(0x00000008)
DECL|macro|SD_CONFIG2_DC
mdefine_line|#define SD_CONFIG2_DC&t;(0x00000010)
DECL|macro|SD_CONFIG2_xx2
mdefine_line|#define SD_CONFIG2_xx2&t;(0x000000e0)
DECL|macro|SD_CONFIG2_WB
mdefine_line|#define SD_CONFIG2_WB&t;(0x00000100)
DECL|macro|SD_CONFIG2_RW
mdefine_line|#define SD_CONFIG2_RW&t;(0x00000200)
multiline_comment|/*&n; *  SD_BLKSIZE bit definitions.&n; */
DECL|macro|SD_BLKSIZE_BS
mdefine_line|#define SD_BLKSIZE_BS&t;(0x000007ff)
DECL|macro|SD_BLKSIZE_BS_SHIFT
mdefine_line|#define SD_BLKSIZE_BS_SHIFT&t; (0)
DECL|macro|SD_BLKSIZE_BC
mdefine_line|#define SD_BLKSIZE_BC&t;(0x01ff0000)
DECL|macro|SD_BLKSIZE_BC_SHIFT
mdefine_line|#define SD_BLKSIZE_BC_SHIFT&t;(16)
multiline_comment|/*&n; *  SD_STATUS bit definitions.&n; */
DECL|macro|SD_STATUS_DCRCW
mdefine_line|#define SD_STATUS_DCRCW&t;(0x00000007)
DECL|macro|SD_STATUS_xx1
mdefine_line|#define SD_STATUS_xx1&t;(0x00000008)
DECL|macro|SD_STATUS_CB
mdefine_line|#define SD_STATUS_CB&t;(0x00000010)
DECL|macro|SD_STATUS_DB
mdefine_line|#define SD_STATUS_DB&t;(0x00000020)
DECL|macro|SD_STATUS_CF
mdefine_line|#define SD_STATUS_CF&t;(0x00000040)
DECL|macro|SD_STATUS_D3
mdefine_line|#define SD_STATUS_D3&t;(0x00000080)
DECL|macro|SD_STATUS_xx2
mdefine_line|#define SD_STATUS_xx2&t;(0x00000300)
DECL|macro|SD_STATUS_NE
mdefine_line|#define SD_STATUS_NE&t;(0x00000400)
DECL|macro|SD_STATUS_TU
mdefine_line|#define SD_STATUS_TU&t;(0x00000800)
DECL|macro|SD_STATUS_TO
mdefine_line|#define SD_STATUS_TO&t;(0x00001000)
DECL|macro|SD_STATUS_RU
mdefine_line|#define SD_STATUS_RU&t;(0x00002000)
DECL|macro|SD_STATUS_RO
mdefine_line|#define SD_STATUS_RO&t;(0x00004000)
DECL|macro|SD_STATUS_I
mdefine_line|#define SD_STATUS_I&t;(0x00008000)
DECL|macro|SD_STATUS_CR
mdefine_line|#define SD_STATUS_CR&t;(0x00010000)
DECL|macro|SD_STATUS_RAT
mdefine_line|#define SD_STATUS_RAT&t;(0x00020000)
DECL|macro|SD_STATUS_DD
mdefine_line|#define SD_STATUS_DD&t;(0x00040000)
DECL|macro|SD_STATUS_DT
mdefine_line|#define SD_STATUS_DT&t;(0x00080000)
DECL|macro|SD_STATUS_SC
mdefine_line|#define SD_STATUS_SC&t;(0x00100000)
DECL|macro|SD_STATUS_RC
mdefine_line|#define SD_STATUS_RC&t;(0x00200000)
DECL|macro|SD_STATUS_WC
mdefine_line|#define SD_STATUS_WC&t;(0x00400000)
DECL|macro|SD_STATUS_xx3
mdefine_line|#define SD_STATUS_xx3&t;(0x00800000)
DECL|macro|SD_STATUS_TH
mdefine_line|#define SD_STATUS_TH&t;(0x01000000)
DECL|macro|SD_STATUS_TE
mdefine_line|#define SD_STATUS_TE&t;(0x02000000)
DECL|macro|SD_STATUS_TA
mdefine_line|#define SD_STATUS_TA&t;(0x04000000)
DECL|macro|SD_STATUS_RH
mdefine_line|#define SD_STATUS_RH&t;(0x08000000)
DECL|macro|SD_STATUS_RA
mdefine_line|#define SD_STATUS_RA&t;(0x10000000)
DECL|macro|SD_STATUS_RF
mdefine_line|#define SD_STATUS_RF&t;(0x20000000)
DECL|macro|SD_STATUS_CD
mdefine_line|#define SD_STATUS_CD&t;(0x40000000)
DECL|macro|SD_STATUS_SI
mdefine_line|#define SD_STATUS_SI&t;(0x80000000)
multiline_comment|/*&n; *  SD_CMD bit definitions.&n; */
DECL|macro|SD_CMD_GO
mdefine_line|#define SD_CMD_GO&t;(0x00000001)
DECL|macro|SD_CMD_RY
mdefine_line|#define SD_CMD_RY&t;(0x00000002)
DECL|macro|SD_CMD_xx1
mdefine_line|#define SD_CMD_xx1&t;(0x0000000c)
DECL|macro|SD_CMD_CT_MASK
mdefine_line|#define SD_CMD_CT_MASK&t;(0x000000f0)
DECL|macro|SD_CMD_CT_0
mdefine_line|#define SD_CMD_CT_0&t;(0x00000000)
DECL|macro|SD_CMD_CT_1
mdefine_line|#define SD_CMD_CT_1&t;(0x00000010)
DECL|macro|SD_CMD_CT_2
mdefine_line|#define SD_CMD_CT_2&t;(0x00000020)
DECL|macro|SD_CMD_CT_3
mdefine_line|#define SD_CMD_CT_3&t;(0x00000030)
DECL|macro|SD_CMD_CT_4
mdefine_line|#define SD_CMD_CT_4&t;(0x00000040)
DECL|macro|SD_CMD_CT_5
mdefine_line|#define SD_CMD_CT_5&t;(0x00000050)
DECL|macro|SD_CMD_CT_6
mdefine_line|#define SD_CMD_CT_6&t;(0x00000060)
DECL|macro|SD_CMD_CT_7
mdefine_line|#define SD_CMD_CT_7&t;(0x00000070)
DECL|macro|SD_CMD_CI
mdefine_line|#define SD_CMD_CI&t;(0x0000ff00)
DECL|macro|SD_CMD_CI_SHIFT
mdefine_line|#define SD_CMD_CI_SHIFT&t;&t;(8)
DECL|macro|SD_CMD_RT_MASK
mdefine_line|#define SD_CMD_RT_MASK&t;(0x00ff0000)
DECL|macro|SD_CMD_RT_0
mdefine_line|#define SD_CMD_RT_0&t;(0x00000000)
DECL|macro|SD_CMD_RT_1
mdefine_line|#define SD_CMD_RT_1&t;(0x00010000)
DECL|macro|SD_CMD_RT_2
mdefine_line|#define SD_CMD_RT_2&t;(0x00020000)
DECL|macro|SD_CMD_RT_3
mdefine_line|#define SD_CMD_RT_3&t;(0x00030000)
DECL|macro|SD_CMD_RT_4
mdefine_line|#define SD_CMD_RT_4&t;(0x00040000)
DECL|macro|SD_CMD_RT_5
mdefine_line|#define SD_CMD_RT_5&t;(0x00050000)
DECL|macro|SD_CMD_RT_6
mdefine_line|#define SD_CMD_RT_6&t;(0x00060000)
DECL|macro|SD_CMD_RT_1B
mdefine_line|#define SD_CMD_RT_1B&t;(0x00810000)
macro_line|#endif /* __ASM_AU1100_MMC_H */
eof
