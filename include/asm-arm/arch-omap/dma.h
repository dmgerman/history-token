multiline_comment|/*&n; *  linux/include/asm-arm/arch-omap/dma.h&n; *&n; *  Copyright (C) 2003 Nokia Corporation&n; *  Author: Juha Yrj&#xfffd;l&#xfffd; &lt;juha.yrjola@nokia.com&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; */
macro_line|#ifndef __ASM_ARCH_DMA_H
DECL|macro|__ASM_ARCH_DMA_H
mdefine_line|#define __ASM_ARCH_DMA_H
DECL|macro|MAX_DMA_ADDRESS
mdefine_line|#define MAX_DMA_ADDRESS&t;&t;&t;0xffffffff
DECL|macro|OMAP_LOGICAL_DMA_CH_COUNT
mdefine_line|#define OMAP_LOGICAL_DMA_CH_COUNT&t;17
DECL|macro|OMAP_DMA_NO_DEVICE
mdefine_line|#define OMAP_DMA_NO_DEVICE&t;&t;0
DECL|macro|OMAP_DMA_MCSI1_TX
mdefine_line|#define OMAP_DMA_MCSI1_TX&t;&t;1
DECL|macro|OMAP_DMA_MCSI1_RX
mdefine_line|#define OMAP_DMA_MCSI1_RX&t;&t;2
DECL|macro|OMAP_DMA_I2C_RX
mdefine_line|#define OMAP_DMA_I2C_RX&t;&t;&t;3
DECL|macro|OMAP_DMA_I2C_TX
mdefine_line|#define OMAP_DMA_I2C_TX&t;&t;&t;4
DECL|macro|OMAP_DMA_EXT_NDMA_REQ
mdefine_line|#define OMAP_DMA_EXT_NDMA_REQ&t;&t;5
DECL|macro|OMAP_DMA_EXT_NDMA_REQ2
mdefine_line|#define OMAP_DMA_EXT_NDMA_REQ2&t;&t;6
DECL|macro|OMAP_DMA_UWIRE_TX
mdefine_line|#define OMAP_DMA_UWIRE_TX&t;&t;7
DECL|macro|OMAP_DMA_MCBSP1_DMA_TX
mdefine_line|#define OMAP_DMA_MCBSP1_DMA_TX&t;&t;8
DECL|macro|OMAP_DMA_MCBSP1_DMA_RX
mdefine_line|#define OMAP_DMA_MCBSP1_DMA_RX&t;&t;9
DECL|macro|OMAP_DMA_MCBSP3_DMA_TX
mdefine_line|#define OMAP_DMA_MCBSP3_DMA_TX&t;&t;10
DECL|macro|OMAP_DMA_MCBSP3_DMA_RX
mdefine_line|#define OMAP_DMA_MCBSP3_DMA_RX&t;&t;11
DECL|macro|OMAP_DMA_UART1_TX
mdefine_line|#define OMAP_DMA_UART1_TX&t;&t;12
DECL|macro|OMAP_DMA_UART1_RX
mdefine_line|#define OMAP_DMA_UART1_RX&t;&t;13
DECL|macro|OMAP_DMA_UART2_TX
mdefine_line|#define OMAP_DMA_UART2_TX&t;&t;14
DECL|macro|OMAP_DMA_UART2_RX
mdefine_line|#define OMAP_DMA_UART2_RX&t;&t;15
DECL|macro|OMAP_DMA_MCBSP2_TX
mdefine_line|#define OMAP_DMA_MCBSP2_TX&t;&t;16
DECL|macro|OMAP_DMA_MCBSP2_RX
mdefine_line|#define OMAP_DMA_MCBSP2_RX&t;&t;17
DECL|macro|OMAP_DMA_UART3_TX
mdefine_line|#define OMAP_DMA_UART3_TX&t;&t;18
DECL|macro|OMAP_DMA_UART3_RX
mdefine_line|#define OMAP_DMA_UART3_RX&t;&t;19
DECL|macro|OMAP_DMA_CAMERA_IF_RX
mdefine_line|#define OMAP_DMA_CAMERA_IF_RX&t;&t;20
DECL|macro|OMAP_DMA_MMC_TX
mdefine_line|#define OMAP_DMA_MMC_TX&t;&t;&t;21
DECL|macro|OMAP_DMA_MMC_RX
mdefine_line|#define OMAP_DMA_MMC_RX&t;&t;&t;22
DECL|macro|OMAP_DMA_NAND
mdefine_line|#define OMAP_DMA_NAND&t;&t;&t;23
DECL|macro|OMAP_DMA_IRQ_LCD_LINE
mdefine_line|#define OMAP_DMA_IRQ_LCD_LINE&t;&t;24
DECL|macro|OMAP_DMA_MEMORY_STICK
mdefine_line|#define OMAP_DMA_MEMORY_STICK&t;&t;25
DECL|macro|OMAP_DMA_USB_W2FC_RX0
mdefine_line|#define OMAP_DMA_USB_W2FC_RX0&t;&t;26
DECL|macro|OMAP_DMA_USB_W2FC_RX1
mdefine_line|#define OMAP_DMA_USB_W2FC_RX1&t;&t;27
DECL|macro|OMAP_DMA_USB_W2FC_RX2
mdefine_line|#define OMAP_DMA_USB_W2FC_RX2&t;&t;28
DECL|macro|OMAP_DMA_USB_W2FC_TX0
mdefine_line|#define OMAP_DMA_USB_W2FC_TX0&t;&t;29
DECL|macro|OMAP_DMA_USB_W2FC_TX1
mdefine_line|#define OMAP_DMA_USB_W2FC_TX1&t;&t;30
DECL|macro|OMAP_DMA_USB_W2FC_TX2
mdefine_line|#define OMAP_DMA_USB_W2FC_TX2&t;&t;31
multiline_comment|/* These are only for 1610 */
DECL|macro|OMAP_DMA_CRYPTO_DES_IN
mdefine_line|#define OMAP_DMA_CRYPTO_DES_IN&t;&t;32
DECL|macro|OMAP_DMA_SPI_TX
mdefine_line|#define OMAP_DMA_SPI_TX&t;&t;&t;33
DECL|macro|OMAP_DMA_SPI_RX
mdefine_line|#define OMAP_DMA_SPI_RX&t;&t;&t;34
DECL|macro|OMAP_DMA_CRYPTO_HASH
mdefine_line|#define OMAP_DMA_CRYPTO_HASH&t;&t;35
DECL|macro|OMAP_DMA_CCP_ATTN
mdefine_line|#define OMAP_DMA_CCP_ATTN&t;&t;36
DECL|macro|OMAP_DMA_CCP_FIFO_NOT_EMPTY
mdefine_line|#define OMAP_DMA_CCP_FIFO_NOT_EMPTY&t;37
DECL|macro|OMAP_DMA_CMT_APE_TX_CHAN_0
mdefine_line|#define OMAP_DMA_CMT_APE_TX_CHAN_0&t;38
DECL|macro|OMAP_DMA_CMT_APE_RV_CHAN_0
mdefine_line|#define OMAP_DMA_CMT_APE_RV_CHAN_0&t;39
DECL|macro|OMAP_DMA_CMT_APE_TX_CHAN_1
mdefine_line|#define OMAP_DMA_CMT_APE_TX_CHAN_1&t;40
DECL|macro|OMAP_DMA_CMT_APE_RV_CHAN_1
mdefine_line|#define OMAP_DMA_CMT_APE_RV_CHAN_1&t;41
DECL|macro|OMAP_DMA_CMT_APE_TX_CHAN_2
mdefine_line|#define OMAP_DMA_CMT_APE_TX_CHAN_2&t;42
DECL|macro|OMAP_DMA_CMT_APE_RV_CHAN_2
mdefine_line|#define OMAP_DMA_CMT_APE_RV_CHAN_2&t;43
DECL|macro|OMAP_DMA_CMT_APE_TX_CHAN_3
mdefine_line|#define OMAP_DMA_CMT_APE_TX_CHAN_3&t;44
DECL|macro|OMAP_DMA_CMT_APE_RV_CHAN_3
mdefine_line|#define OMAP_DMA_CMT_APE_RV_CHAN_3&t;45
DECL|macro|OMAP_DMA_CMT_APE_TX_CHAN_4
mdefine_line|#define OMAP_DMA_CMT_APE_TX_CHAN_4&t;46
DECL|macro|OMAP_DMA_CMT_APE_RV_CHAN_4
mdefine_line|#define OMAP_DMA_CMT_APE_RV_CHAN_4&t;47
DECL|macro|OMAP_DMA_CMT_APE_TX_CHAN_5
mdefine_line|#define OMAP_DMA_CMT_APE_TX_CHAN_5&t;48
DECL|macro|OMAP_DMA_CMT_APE_RV_CHAN_5
mdefine_line|#define OMAP_DMA_CMT_APE_RV_CHAN_5&t;49
DECL|macro|OMAP_DMA_CMT_APE_TX_CHAN_6
mdefine_line|#define OMAP_DMA_CMT_APE_TX_CHAN_6&t;50
DECL|macro|OMAP_DMA_CMT_APE_RV_CHAN_6
mdefine_line|#define OMAP_DMA_CMT_APE_RV_CHAN_6&t;51
DECL|macro|OMAP_DMA_CMT_APE_TX_CHAN_7
mdefine_line|#define OMAP_DMA_CMT_APE_TX_CHAN_7&t;52
DECL|macro|OMAP_DMA_CMT_APE_RV_CHAN_7
mdefine_line|#define OMAP_DMA_CMT_APE_RV_CHAN_7&t;53
DECL|macro|OMAP_DMA_MMC2_TX
mdefine_line|#define OMAP_DMA_MMC2_TX&t;&t;54
DECL|macro|OMAP_DMA_MMC2_RX
mdefine_line|#define OMAP_DMA_MMC2_RX&t;&t;55
DECL|macro|OMAP_DMA_CRYPTO_DES_OUT
mdefine_line|#define OMAP_DMA_CRYPTO_DES_OUT&t;&t;56
DECL|macro|OMAP_DMA_BASE
mdefine_line|#define OMAP_DMA_BASE&t;&t;&t;0xfffed800
DECL|macro|OMAP_DMA_GCR_REG
mdefine_line|#define OMAP_DMA_GCR_REG&t;&t;(OMAP_DMA_BASE + 0x400)
DECL|macro|OMAP_DMA_GSCR_REG
mdefine_line|#define OMAP_DMA_GSCR_REG&t;&t;(OMAP_DMA_BASE + 0x404)
DECL|macro|OMAP_DMA_GRST_REG
mdefine_line|#define OMAP_DMA_GRST_REG&t;&t;(OMAP_DMA_BASE + 0x408)
DECL|macro|OMAP_DMA_HW_ID_REG
mdefine_line|#define OMAP_DMA_HW_ID_REG&t;&t;(OMAP_DMA_BASE + 0x442)
DECL|macro|OMAP_DMA_PCH2_ID_REG
mdefine_line|#define OMAP_DMA_PCH2_ID_REG&t;&t;(OMAP_DMA_BASE + 0x444)
DECL|macro|OMAP_DMA_PCH0_ID
mdefine_line|#define OMAP_DMA_PCH0_ID&t;&t;(OMAP_DMA_BASE + 0x446)
DECL|macro|OMAP_DMA_PCH1_ID
mdefine_line|#define OMAP_DMA_PCH1_ID&t;&t;(OMAP_DMA_BASE + 0x448)
DECL|macro|OMAP_DMA_PCHG_ID
mdefine_line|#define OMAP_DMA_PCHG_ID&t;&t;(OMAP_DMA_BASE + 0x44a)
DECL|macro|OMAP_DMA_PCHD_ID
mdefine_line|#define OMAP_DMA_PCHD_ID&t;&t;(OMAP_DMA_BASE + 0x44c)
DECL|macro|OMAP_DMA_CAPS_0_U_REG
mdefine_line|#define OMAP_DMA_CAPS_0_U_REG&t;&t;(OMAP_DMA_BASE + 0x44e)
DECL|macro|OMAP_DMA_CAPS_0_L_REG
mdefine_line|#define OMAP_DMA_CAPS_0_L_REG&t;&t;(OMAP_DMA_BASE + 0x450)
DECL|macro|OMAP_DMA_CAPS_1_U_REG
mdefine_line|#define OMAP_DMA_CAPS_1_U_REG&t;&t;(OMAP_DMA_BASE + 0x452)
DECL|macro|OMAP_DMA_CAPS_1_L_REG
mdefine_line|#define OMAP_DMA_CAPS_1_L_REG&t;&t;(OMAP_DMA_BASE + 0x454)
DECL|macro|OMAP_DMA_CAPS_2_REG
mdefine_line|#define OMAP_DMA_CAPS_2_REG&t;&t;(OMAP_DMA_BASE + 0x456)
DECL|macro|OMAP_DMA_CAPS_3_REG
mdefine_line|#define OMAP_DMA_CAPS_3_REG&t;&t;(OMAP_DMA_BASE + 0x458)
DECL|macro|OMAP_DMA_CAPS_4_REG
mdefine_line|#define OMAP_DMA_CAPS_4_REG&t;&t;(OMAP_DMA_BASE + 0x45a)
DECL|macro|OMAP_DMA_PCH2_SR_REG
mdefine_line|#define OMAP_DMA_PCH2_SR_REG&t;&t;(OMAP_DMA_BASE + 0x460)
DECL|macro|OMAP_DMA_PCH0_SR_REG
mdefine_line|#define OMAP_DMA_PCH0_SR_REG&t;&t;(OMAP_DMA_BASE + 0x480)
DECL|macro|OMAP_DMA_PCH1_SR_REG
mdefine_line|#define OMAP_DMA_PCH1_SR_REG&t;&t;(OMAP_DMA_BASE + 0x482)
DECL|macro|OMAP_DMA_PCHD_SR_REG
mdefine_line|#define OMAP_DMA_PCHD_SR_REG&t;&t;(OMAP_DMA_BASE + 0x4c0)
DECL|macro|OMAP1510_DMA_LCD_CTRL
mdefine_line|#define OMAP1510_DMA_LCD_CTRL&t;&t;0xfffedb00
DECL|macro|OMAP1510_DMA_LCD_TOP_F1_L
mdefine_line|#define OMAP1510_DMA_LCD_TOP_F1_L&t;0xfffedb02
DECL|macro|OMAP1510_DMA_LCD_TOP_F1_U
mdefine_line|#define OMAP1510_DMA_LCD_TOP_F1_U&t;0xfffedb04
DECL|macro|OMAP1510_DMA_LCD_BOT_F1_L
mdefine_line|#define OMAP1510_DMA_LCD_BOT_F1_L&t;0xfffedb06
DECL|macro|OMAP1510_DMA_LCD_BOT_F1_U
mdefine_line|#define OMAP1510_DMA_LCD_BOT_F1_U&t;0xfffedb08
DECL|macro|OMAP1610_DMA_LCD_CSDP
mdefine_line|#define OMAP1610_DMA_LCD_CSDP&t;&t;0xfffee3c0
DECL|macro|OMAP1610_DMA_LCD_CCR
mdefine_line|#define OMAP1610_DMA_LCD_CCR&t;&t;0xfffee3c2
DECL|macro|OMAP1610_DMA_LCD_CTRL
mdefine_line|#define OMAP1610_DMA_LCD_CTRL&t;&t;0xfffee3c4
DECL|macro|OMAP1610_DMA_LCD_TOP_B1_L
mdefine_line|#define OMAP1610_DMA_LCD_TOP_B1_L&t;0xfffee3c8
DECL|macro|OMAP1610_DMA_LCD_TOP_B1_U
mdefine_line|#define OMAP1610_DMA_LCD_TOP_B1_U&t;0xfffee3ca
DECL|macro|OMAP1610_DMA_LCD_BOT_B1_L
mdefine_line|#define OMAP1610_DMA_LCD_BOT_B1_L&t;0xfffee3cc
DECL|macro|OMAP1610_DMA_LCD_BOT_B1_U
mdefine_line|#define OMAP1610_DMA_LCD_BOT_B1_U&t;0xfffee3ce
DECL|macro|OMAP1610_DMA_LCD_TOP_B2_L
mdefine_line|#define OMAP1610_DMA_LCD_TOP_B2_L&t;0xfffee3d0
DECL|macro|OMAP1610_DMA_LCD_TOP_B2_U
mdefine_line|#define OMAP1610_DMA_LCD_TOP_B2_U&t;0xfffee3d2
DECL|macro|OMAP1610_DMA_LCD_BOT_B2_L
mdefine_line|#define OMAP1610_DMA_LCD_BOT_B2_L&t;0xfffee3d4
DECL|macro|OMAP1610_DMA_LCD_BOT_B2_U
mdefine_line|#define OMAP1610_DMA_LCD_BOT_B2_U&t;0xfffee3d6
DECL|macro|OMAP1610_DMA_LCD_SRC_EI_B1
mdefine_line|#define OMAP1610_DMA_LCD_SRC_EI_B1&t;0xfffee3d8
DECL|macro|OMAP1610_DMA_LCD_SRC_FI_B1_L
mdefine_line|#define OMAP1610_DMA_LCD_SRC_FI_B1_L&t;0xfffee3da
DECL|macro|OMAP1610_DMA_LCD_SRC_EN_B1
mdefine_line|#define OMAP1610_DMA_LCD_SRC_EN_B1&t;0xfffee3e0
DECL|macro|OMAP1610_DMA_LCD_SRC_FN_B1
mdefine_line|#define OMAP1610_DMA_LCD_SRC_FN_B1&t;0xfffee3e4
DECL|macro|OMAP1610_DMA_LCD_LCH_CTRL
mdefine_line|#define OMAP1610_DMA_LCD_LCH_CTRL&t;0xfffee3ea
DECL|macro|OMAP1610_DMA_LCD_SRC_FI_B1_U
mdefine_line|#define OMAP1610_DMA_LCD_SRC_FI_B1_U&t;0xfffee3f4
multiline_comment|/* Every LCh has its own set of the registers below */
DECL|macro|OMAP_DMA_CSDP_REG
mdefine_line|#define OMAP_DMA_CSDP_REG(n)&t;&t;(OMAP_DMA_BASE + 0x40 * (n) + 0x00)
DECL|macro|OMAP_DMA_CCR_REG
mdefine_line|#define OMAP_DMA_CCR_REG(n)&t;&t;(OMAP_DMA_BASE + 0x40 * (n) + 0x02)
DECL|macro|OMAP_DMA_CICR_REG
mdefine_line|#define OMAP_DMA_CICR_REG(n)&t;&t;(OMAP_DMA_BASE + 0x40 * (n) + 0x04)
DECL|macro|OMAP_DMA_CSR_REG
mdefine_line|#define OMAP_DMA_CSR_REG(n)&t;&t;(OMAP_DMA_BASE + 0x40 * (n) + 0x06)
DECL|macro|OMAP_DMA_CSSA_L_REG
mdefine_line|#define OMAP_DMA_CSSA_L_REG(n)&t;&t;(OMAP_DMA_BASE + 0x40 * (n) + 0x08)
DECL|macro|OMAP_DMA_CSSA_U_REG
mdefine_line|#define OMAP_DMA_CSSA_U_REG(n)&t;&t;(OMAP_DMA_BASE + 0x40 * (n) + 0x0a)
DECL|macro|OMAP_DMA_CDSA_L_REG
mdefine_line|#define OMAP_DMA_CDSA_L_REG(n)&t;&t;(OMAP_DMA_BASE + 0x40 * (n) + 0x0c)
DECL|macro|OMAP_DMA_CDSA_U_REG
mdefine_line|#define OMAP_DMA_CDSA_U_REG(n)&t;&t;(OMAP_DMA_BASE + 0x40 * (n) + 0x0e)
DECL|macro|OMAP_DMA_CEN_REG
mdefine_line|#define OMAP_DMA_CEN_REG(n)&t;&t;(OMAP_DMA_BASE + 0x40 * (n) + 0x10)
DECL|macro|OMAP_DMA_CFN_REG
mdefine_line|#define OMAP_DMA_CFN_REG(n)&t;&t;(OMAP_DMA_BASE + 0x40 * (n) + 0x12)
DECL|macro|OMAP_DMA_CSFI_REG
mdefine_line|#define OMAP_DMA_CSFI_REG(n)&t;&t;(OMAP_DMA_BASE + 0x40 * (n) + 0x14)
DECL|macro|OMAP_DMA_CSEI_REG
mdefine_line|#define OMAP_DMA_CSEI_REG(n)&t;&t;(OMAP_DMA_BASE + 0x40 * (n) + 0x16)
DECL|macro|OMAP_DMA_CSAC_REG
mdefine_line|#define OMAP_DMA_CSAC_REG(n)&t;&t;(OMAP_DMA_BASE + 0x40 * (n) + 0x18)
DECL|macro|OMAP_DMA_CDAC_REG
mdefine_line|#define OMAP_DMA_CDAC_REG(n)&t;&t;(OMAP_DMA_BASE + 0x40 * (n) + 0x1a)
DECL|macro|OMAP_DMA_CDEI_REG
mdefine_line|#define OMAP_DMA_CDEI_REG(n)&t;&t;(OMAP_DMA_BASE + 0x40 * (n) + 0x1c)
DECL|macro|OMAP_DMA_CDFI_REG
mdefine_line|#define OMAP_DMA_CDFI_REG(n)&t;&t;(OMAP_DMA_BASE + 0x40 * (n) + 0x1e)
DECL|macro|OMAP_DMA_COLOR_L_REG
mdefine_line|#define OMAP_DMA_COLOR_L_REG(n)&t;&t;(OMAP_DMA_BASE + 0x40 * (n) + 0x20)
DECL|macro|OMAP_DMA_COLOR_U_REG
mdefine_line|#define OMAP_DMA_COLOR_U_REG(n)&t;&t;(OMAP_DMA_BASE + 0x40 * (n) + 0x22)
DECL|macro|OMAP_DMA_CCR2_REG
mdefine_line|#define OMAP_DMA_CCR2_REG(n)&t;&t;(OMAP_DMA_BASE + 0x40 * (n) + 0x24)
DECL|macro|OMAP_DMA_CLNK_CTRL_REG
mdefine_line|#define OMAP_DMA_CLNK_CTRL_REG(n)&t;(OMAP_DMA_BASE + 0x40 * (n) + 0x28)
DECL|macro|OMAP_DMA_LCH_CTRL_REG
mdefine_line|#define OMAP_DMA_LCH_CTRL_REG(n)&t;(OMAP_DMA_BASE + 0x40 * (n) + 0x2a)
DECL|macro|OMAP_DMA_TOUT_IRQ
mdefine_line|#define OMAP_DMA_TOUT_IRQ&t;&t;(1 &lt;&lt; 0)
DECL|macro|OMAP_DMA_DROP_IRQ
mdefine_line|#define OMAP_DMA_DROP_IRQ&t;&t;(1 &lt;&lt; 1)
DECL|macro|OMAP_DMA_HALF_IRQ
mdefine_line|#define OMAP_DMA_HALF_IRQ&t;&t;(1 &lt;&lt; 2)
DECL|macro|OMAP_DMA_FRAME_IRQ
mdefine_line|#define OMAP_DMA_FRAME_IRQ&t;&t;(1 &lt;&lt; 3)
DECL|macro|OMAP_DMA_LAST_IRQ
mdefine_line|#define OMAP_DMA_LAST_IRQ&t;&t;(1 &lt;&lt; 4)
DECL|macro|OMAP_DMA_BLOCK_IRQ
mdefine_line|#define OMAP_DMA_BLOCK_IRQ&t;&t;(1 &lt;&lt; 5)
DECL|macro|OMAP_DMA_SYNC_IRQ
mdefine_line|#define OMAP_DMA_SYNC_IRQ&t;&t;(1 &lt;&lt; 6)
DECL|macro|OMAP_DMA_DATA_TYPE_S8
mdefine_line|#define OMAP_DMA_DATA_TYPE_S8&t;&t;0x00
DECL|macro|OMAP_DMA_DATA_TYPE_S16
mdefine_line|#define OMAP_DMA_DATA_TYPE_S16&t;&t;0x01
DECL|macro|OMAP_DMA_DATA_TYPE_S32
mdefine_line|#define OMAP_DMA_DATA_TYPE_S32&t;&t;0x02
DECL|macro|OMAP_DMA_SYNC_ELEMENT
mdefine_line|#define OMAP_DMA_SYNC_ELEMENT&t;&t;0x00
DECL|macro|OMAP_DMA_SYNC_FRAME
mdefine_line|#define OMAP_DMA_SYNC_FRAME&t;&t;0x01
DECL|macro|OMAP_DMA_SYNC_BLOCK
mdefine_line|#define OMAP_DMA_SYNC_BLOCK&t;&t;0x02
DECL|macro|OMAP_DMA_PORT_EMIFF
mdefine_line|#define OMAP_DMA_PORT_EMIFF&t;&t;0x00
DECL|macro|OMAP_DMA_PORT_EMIFS
mdefine_line|#define OMAP_DMA_PORT_EMIFS&t;&t;0x01
DECL|macro|OMAP_DMA_PORT_OCP_T1
mdefine_line|#define OMAP_DMA_PORT_OCP_T1&t;&t;0x02
DECL|macro|OMAP_DMA_PORT_TIPB
mdefine_line|#define OMAP_DMA_PORT_TIPB&t;&t;0x03
DECL|macro|OMAP_DMA_PORT_OCP_T2
mdefine_line|#define OMAP_DMA_PORT_OCP_T2&t;&t;0x04
DECL|macro|OMAP_DMA_PORT_MPUI
mdefine_line|#define OMAP_DMA_PORT_MPUI&t;&t;0x05
DECL|macro|OMAP_DMA_AMODE_CONSTANT
mdefine_line|#define OMAP_DMA_AMODE_CONSTANT&t;&t;0x00
DECL|macro|OMAP_DMA_AMODE_POST_INC
mdefine_line|#define OMAP_DMA_AMODE_POST_INC&t;&t;0x01
DECL|macro|OMAP_DMA_AMODE_SINGLE_IDX
mdefine_line|#define OMAP_DMA_AMODE_SINGLE_IDX&t;0x02
DECL|macro|OMAP_DMA_AMODE_DOUBLE_IDX
mdefine_line|#define OMAP_DMA_AMODE_DOUBLE_IDX&t;0x03
multiline_comment|/* LCD DMA block numbers */
r_enum
(brace
DECL|enumerator|OMAP_LCD_DMA_B1_TOP
id|OMAP_LCD_DMA_B1_TOP
comma
DECL|enumerator|OMAP_LCD_DMA_B1_BOTTOM
id|OMAP_LCD_DMA_B1_BOTTOM
comma
DECL|enumerator|OMAP_LCD_DMA_B2_TOP
id|OMAP_LCD_DMA_B2_TOP
comma
DECL|enumerator|OMAP_LCD_DMA_B2_BOTTOM
id|OMAP_LCD_DMA_B2_BOTTOM
)brace
suffix:semicolon
r_extern
r_int
id|omap_request_dma
c_func
(paren
r_int
id|dev_id
comma
r_const
r_char
op_star
id|dev_name
comma
r_void
(paren
op_star
id|callback
)paren
(paren
r_int
id|lch
comma
id|u16
id|ch_status
comma
r_void
op_star
id|data
)paren
comma
r_void
op_star
id|data
comma
r_int
op_star
id|dma_ch
)paren
suffix:semicolon
r_extern
r_void
id|omap_enable_dma_irq
c_func
(paren
r_int
id|ch
comma
id|u16
id|irq_bits
)paren
suffix:semicolon
r_extern
r_void
id|omap_disable_dma_irq
c_func
(paren
r_int
id|ch
comma
id|u16
id|irq_bits
)paren
suffix:semicolon
r_extern
r_void
id|omap_free_dma
c_func
(paren
r_int
id|ch
)paren
suffix:semicolon
r_extern
r_void
id|omap_start_dma
c_func
(paren
r_int
id|lch
)paren
suffix:semicolon
r_extern
r_void
id|omap_stop_dma
c_func
(paren
r_int
id|lch
)paren
suffix:semicolon
r_extern
r_void
id|omap_set_dma_transfer_params
c_func
(paren
r_int
id|lch
comma
r_int
id|data_type
comma
r_int
id|elem_count
comma
r_int
id|frame_count
comma
r_int
id|sync_mode
)paren
suffix:semicolon
r_extern
r_void
id|omap_set_dma_src_params
c_func
(paren
r_int
id|lch
comma
r_int
id|src_port
comma
r_int
id|src_amode
comma
r_int
r_int
id|src_start
)paren
suffix:semicolon
r_extern
r_void
id|omap_set_dma_dest_params
c_func
(paren
r_int
id|lch
comma
r_int
id|dest_port
comma
r_int
id|dest_amode
comma
r_int
r_int
id|dest_start
)paren
suffix:semicolon
r_extern
r_void
id|omap_dma_link_lch
(paren
r_int
id|lch_head
comma
r_int
id|lch_queue
)paren
suffix:semicolon
r_extern
r_void
id|omap_dma_unlink_lch
(paren
r_int
id|lch_head
comma
r_int
id|lch_queue
)paren
suffix:semicolon
multiline_comment|/* Returns 1 if the DMA module is in OMAP1510-compatible mode, 0 otherwise */
r_extern
r_int
id|omap_dma_in_1510_mode
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* LCD DMA functions */
r_extern
r_int
id|omap_request_lcd_dma
c_func
(paren
r_void
(paren
op_star
id|callback
)paren
(paren
id|u16
id|status
comma
r_void
op_star
id|data
)paren
comma
r_void
op_star
id|data
)paren
suffix:semicolon
r_extern
r_void
id|omap_free_lcd_dma
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|omap_start_lcd_dma
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|omap_stop_lcd_dma
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|omap_set_lcd_dma_b1
c_func
(paren
r_int
r_int
id|addr
comma
id|u16
id|fb_xres
comma
id|u16
id|fb_yres
comma
r_int
id|data_type
)paren
suffix:semicolon
r_extern
r_void
id|omap_set_lcd_dma_b1_rotation
c_func
(paren
r_int
id|rotate
)paren
suffix:semicolon
macro_line|#endif /* __ASM_ARCH_DMA_H */
eof
