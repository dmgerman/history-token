macro_line|#ifndef __SOUND_VT1724_H
DECL|macro|__SOUND_VT1724_H
mdefine_line|#define __SOUND_VT1724_H
multiline_comment|/*&n; *   ALSA driver for ICEnsemble VT1724 (Envy24)&n; *&n; *&t;Copyright (c) 2000 Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &lt;sound/control.h&gt;
macro_line|#include &lt;sound/ac97_codec.h&gt;
macro_line|#include &lt;sound/rawmidi.h&gt;
macro_line|#include &lt;sound/i2c.h&gt;
macro_line|#include &lt;sound/pcm.h&gt;
macro_line|#include &quot;ice1712.h&quot;
r_enum
(brace
DECL|enumerator|ICE_EEP2_SYSCONF
id|ICE_EEP2_SYSCONF
op_assign
l_int|0
comma
multiline_comment|/* 06 */
DECL|enumerator|ICE_EEP2_ACLINK
id|ICE_EEP2_ACLINK
comma
multiline_comment|/* 07 */
DECL|enumerator|ICE_EEP2_I2S
id|ICE_EEP2_I2S
comma
multiline_comment|/* 08 */
DECL|enumerator|ICE_EEP2_SPDIF
id|ICE_EEP2_SPDIF
comma
multiline_comment|/* 09 */
DECL|enumerator|ICE_EEP2_GPIO_DIR
id|ICE_EEP2_GPIO_DIR
comma
multiline_comment|/* 0a */
DECL|enumerator|ICE_EEP2_GPIO_DIR1
id|ICE_EEP2_GPIO_DIR1
comma
multiline_comment|/* 0b */
DECL|enumerator|ICE_EEP2_GPIO_DIR2
id|ICE_EEP2_GPIO_DIR2
comma
multiline_comment|/* 0c */
DECL|enumerator|ICE_EEP2_GPIO_MASK
id|ICE_EEP2_GPIO_MASK
comma
multiline_comment|/* 0d */
DECL|enumerator|ICE_EEP2_GPIO_MASK1
id|ICE_EEP2_GPIO_MASK1
comma
multiline_comment|/* 0e */
DECL|enumerator|ICE_EEP2_GPIO_MASK2
id|ICE_EEP2_GPIO_MASK2
comma
multiline_comment|/* 0f */
DECL|enumerator|ICE_EEP2_GPIO_STATE
id|ICE_EEP2_GPIO_STATE
comma
multiline_comment|/* 10 */
DECL|enumerator|ICE_EEP2_GPIO_STATE1
id|ICE_EEP2_GPIO_STATE1
comma
multiline_comment|/* 11 */
DECL|enumerator|ICE_EEP2_GPIO_STATE2
id|ICE_EEP2_GPIO_STATE2
multiline_comment|/* 12 */
)brace
suffix:semicolon
multiline_comment|/*&n; *  Direct registers&n; */
DECL|macro|ICEREG1724
mdefine_line|#define ICEREG1724(ice, x) ((ice)-&gt;port + VT1724_REG_##x)
DECL|macro|VT1724_REG_CONTROL
mdefine_line|#define VT1724_REG_CONTROL&t;&t;0x00&t;/* byte */
DECL|macro|VT1724_RESET
mdefine_line|#define   VT1724_RESET&t;&t;&t;0x80&t;/* reset whole chip */
DECL|macro|VT1724_REG_IRQMASK
mdefine_line|#define VT1724_REG_IRQMASK&t;&t;0x01&t;/* byte */
DECL|macro|VT1724_IRQ_MPU_RX
mdefine_line|#define   VT1724_IRQ_MPU_RX&t;&t;0x80
DECL|macro|VT1724_IRQ_MPU_TX
mdefine_line|#define   VT1724_IRQ_MPU_TX&t;&t;0x20
DECL|macro|VT1724_IRQ_MTPCM
mdefine_line|#define   VT1724_IRQ_MTPCM&t;&t;0x10
DECL|macro|VT1724_REG_IRQSTAT
mdefine_line|#define VT1724_REG_IRQSTAT&t;&t;0x02&t;/* byte */
multiline_comment|/* look to VT1724_IRQ_* */
DECL|macro|VT1724_REG_SYS_CFG
mdefine_line|#define VT1724_REG_SYS_CFG&t;&t;0x04&t;/* byte - system configuration PCI60 on Envy24*/
DECL|macro|VT1724_CFG_CLOCK
mdefine_line|#define   VT1724_CFG_CLOCK&t;0xc0
DECL|macro|VT1724_CFG_CLOCK512
mdefine_line|#define     VT1724_CFG_CLOCK512&t;0x00&t;/* 22.5692Mhz, 44.1kHz*512 */
DECL|macro|VT1724_CFG_CLOCK384
mdefine_line|#define     VT1724_CFG_CLOCK384  0x40&t;/* 16.9344Mhz, 44.1kHz*384 */
DECL|macro|VT1724_CFG_MPU401
mdefine_line|#define   VT1724_CFG_MPU401&t;0x20&t;&t;/* MPU401 UARTs */
DECL|macro|VT1724_CFG_ADC_MASK
mdefine_line|#define   VT1724_CFG_ADC_MASK&t;0x0c&t;/* one, two or one and S/PDIF, stereo ADCs */
DECL|macro|VT1724_CFG_DAC_MASK
mdefine_line|#define   VT1724_CFG_DAC_MASK&t;0x03&t;/* one, two, three, four stereo DACs */
DECL|macro|VT1724_REG_AC97_CFG
mdefine_line|#define VT1724_REG_AC97_CFG&t;&t;0x05&t;/* byte */
DECL|macro|VT1724_CFG_PRO_I2S
mdefine_line|#define   VT1724_CFG_PRO_I2S&t;0x80&t;/* multitrack converter: I2S or AC&squot;97 */
DECL|macro|VT1724_CFG_AC97_PACKED
mdefine_line|#define   VT1724_CFG_AC97_PACKED&t;0x01&t;/* split or packed mode - AC&squot;97 */
DECL|macro|VT1724_REG_I2S_FEATURES
mdefine_line|#define VT1724_REG_I2S_FEATURES&t;&t;0x06&t;/* byte */
DECL|macro|VT1724_CFG_I2S_VOLUME
mdefine_line|#define   VT1724_CFG_I2S_VOLUME&t;0x80&t;/* volume/mute capability */
DECL|macro|VT1724_CFG_I2S_96KHZ
mdefine_line|#define   VT1724_CFG_I2S_96KHZ&t;0x40&t;/* supports 96kHz sampling */
DECL|macro|VT1724_CFG_I2S_RESMASK
mdefine_line|#define   VT1724_CFG_I2S_RESMASK&t;0x30&t;/* resolution mask, 16,18,20,24-bit */
DECL|macro|VT1724_CFG_I2S_192KHZ
mdefine_line|#define   VT1724_CFG_I2S_192KHZ&t;0x08&t;/* supports 192kHz sampling */
DECL|macro|VT1724_CFG_I2S_OTHER
mdefine_line|#define   VT1724_CFG_I2S_OTHER&t;0x07&t;/* other I2S IDs */
DECL|macro|VT1724_REG_SPDIF_CFG
mdefine_line|#define VT1724_REG_SPDIF_CFG&t;&t;0x07&t;/* byte */
DECL|macro|VT1724_CFG_SPDIF_OUT_EN
mdefine_line|#define   VT1724_CFG_SPDIF_OUT_EN&t;0x80&t;/*Internal S/PDIF output is enabled*/
DECL|macro|VT1724_CFG_SPDIF_OUT_INT
mdefine_line|#define   VT1724_CFG_SPDIF_OUT_INT&t;0x40&t;/*Internal S/PDIF output is implemented*/
DECL|macro|VT1724_CFG_I2S_CHIPID
mdefine_line|#define   VT1724_CFG_I2S_CHIPID&t;0x3c&t;/* I2S chip ID */
DECL|macro|VT1724_CFG_SPDIF_IN
mdefine_line|#define   VT1724_CFG_SPDIF_IN&t;0x02&t;/* S/PDIF input is present */
DECL|macro|VT1724_CFG_SPDIF_OUT
mdefine_line|#define   VT1724_CFG_SPDIF_OUT&t;0x01&t;/* External S/PDIF output is present */
multiline_comment|/*there is no consumer AC97 codec with the VT1724*/
singleline_comment|//#define VT1724_REG_AC97_INDEX&t;&t;0x08&t;/* byte */
singleline_comment|//#define VT1724_REG_AC97_CMD&t;&t;0x09&t;/* byte */
DECL|macro|VT1724_REG_MPU_TXFIFO
mdefine_line|#define VT1724_REG_MPU_TXFIFO&t;&t;0x0a&t;/*byte ro. number of bytes in TX fifo*/
DECL|macro|VT1724_REG_MPU_RXFIFO
mdefine_line|#define VT1724_REG_MPU_RXFIFO&t;&t;0x0b&t;/*byte ro. number of bytes in RX fifo*/
singleline_comment|//are these 2 the wrong way around? they don&squot;t seem to be used yet anyway
DECL|macro|VT1724_REG_MPU_CTRL
mdefine_line|#define VT1724_REG_MPU_CTRL&t;&t;0x0c&t;/* byte */
DECL|macro|VT1724_REG_MPU_DATA
mdefine_line|#define VT1724_REG_MPU_DATA&t;&t;0x0d&t;/* byte */
DECL|macro|VT1724_REG_MPU_FIFO_WM
mdefine_line|#define VT1724_REG_MPU_FIFO_WM&t;0x0e&t;/*byte set the high/low watermarks for RX/TX fifos*/
DECL|macro|VT1724_MPU_RX_FIFO
mdefine_line|#define   VT1724_MPU_RX_FIFO&t;0x20&t;
singleline_comment|//1=rx fifo watermark 0=tx fifo watermark
DECL|macro|VT1724_MPU_FIFO_MASK
mdefine_line|#define   VT1724_MPU_FIFO_MASK&t;0x1f&t;
DECL|macro|VT1724_REG_I2C_DEV_ADDR
mdefine_line|#define VT1724_REG_I2C_DEV_ADDR&t;0x10&t;/* byte */
DECL|macro|VT1724_I2C_WRITE
mdefine_line|#define   VT1724_I2C_WRITE&t;&t;0x01&t;/* write direction */
DECL|macro|VT1724_REG_I2C_BYTE_ADDR
mdefine_line|#define VT1724_REG_I2C_BYTE_ADDR&t;0x11&t;/* byte */
DECL|macro|VT1724_REG_I2C_DATA
mdefine_line|#define VT1724_REG_I2C_DATA&t;&t;0x12&t;/* byte */
DECL|macro|VT1724_REG_I2C_CTRL
mdefine_line|#define VT1724_REG_I2C_CTRL&t;&t;0x13&t;/* byte */
DECL|macro|VT1724_I2C_EEPROM
mdefine_line|#define   VT1724_I2C_EEPROM&t;&t;0x80&t;/* EEPROM exists */
DECL|macro|VT1724_I2C_BUSY
mdefine_line|#define   VT1724_I2C_BUSY&t;&t;0x01&t;/* busy bit */
DECL|macro|VT1724_REG_GPIO_DATA
mdefine_line|#define VT1724_REG_GPIO_DATA&t;0x14&t;/* word */
DECL|macro|VT1724_REG_GPIO_WRITE_MASK
mdefine_line|#define VT1724_REG_GPIO_WRITE_MASK&t;0x16 /* word */
DECL|macro|VT1724_REG_GPIO_DIRECTION
mdefine_line|#define VT1724_REG_GPIO_DIRECTION&t;0x18 /* dword? (3 bytes) 0=input 1=output. &n;&t;&t;&t;&t;&t;&t;bit3 - during reset used for Eeprom power-on strapping&n;&t;&t;&t;&t;&t;&t;if TESTEN# pin active, bit 2 always input*/
DECL|macro|VT1724_REG_POWERDOWN
mdefine_line|#define VT1724_REG_POWERDOWN&t;0x1c
DECL|macro|VT1724_REG_GPIO_DATA_22
mdefine_line|#define VT1724_REG_GPIO_DATA_22&t;0x1e /* byte direction for GPIO 16:22 */
DECL|macro|VT1724_REG_GPIO_WRITE_MASK_22
mdefine_line|#define VT1724_REG_GPIO_WRITE_MASK_22&t;0x1f /* byte write mask for GPIO 16:22 */
multiline_comment|/* &n; *  Professional multi-track direct control registers&n; */
DECL|macro|ICEMT1724
mdefine_line|#define ICEMT1724(ice, x) ((ice)-&gt;profi_port + VT1724_MT_##x)
DECL|macro|VT1724_MT_IRQ
mdefine_line|#define VT1724_MT_IRQ&t;&t;&t;0x00&t;/* byte - interrupt mask */
DECL|macro|VT1724_MULTI_PDMA4
mdefine_line|#define   VT1724_MULTI_PDMA4&t;0x80&t;/* SPDIF Out / PDMA4 */
DECL|macro|VT1724_MULTI_PDMA3
mdefine_line|#define&t;  VT1724_MULTI_PDMA3&t;0x40&t;/* PDMA3 */
DECL|macro|VT1724_MULTI_PDMA2
mdefine_line|#define   VT1724_MULTI_PDMA2&t;0x20&t;/* PDMA2 */
DECL|macro|VT1724_MULTI_PDMA1
mdefine_line|#define   VT1724_MULTI_PDMA1&t;0x10&t;/* PDMA1 */
DECL|macro|VT1724_MULTI_FIFO_ERR
mdefine_line|#define   VT1724_MULTI_FIFO_ERR 0x08&t;/* DMA FIFO underrun/overrun. */
DECL|macro|VT1724_MULTI_RDMA1
mdefine_line|#define   VT1724_MULTI_RDMA1&t;0x04&t;/* RDMA1 (S/PDIF input) */
DECL|macro|VT1724_MULTI_RDMA0
mdefine_line|#define   VT1724_MULTI_RDMA0&t;0x02&t;/* RMDA0 */
DECL|macro|VT1724_MULTI_PDMA0
mdefine_line|#define   VT1724_MULTI_PDMA0&t;0x01&t;/* MC Interleave/PDMA0 */
DECL|macro|VT1724_MT_RATE
mdefine_line|#define VT1724_MT_RATE&t;&t;&t;0x01&t;/* byte - sampling rate select */
DECL|macro|VT1724_SPDIF_MASTER
mdefine_line|#define   VT1724_SPDIF_MASTER&t;&t;0x10&t;/* S/PDIF input is master clock */
DECL|macro|VT1724_MT_I2S_FORMAT
mdefine_line|#define VT1724_MT_I2S_FORMAT&t;&t;0x02&t;/* byte - I2S data format */
DECL|macro|VT1724_MT_I2S_MCLK_128X
mdefine_line|#define   VT1724_MT_I2S_MCLK_128X&t;0x08
DECL|macro|VT1724_MT_I2S_FORMAT_MASK
mdefine_line|#define   VT1724_MT_I2S_FORMAT_MASK&t;0x03
DECL|macro|VT1724_MT_I2S_FORMAT_I2S
mdefine_line|#define   VT1724_MT_I2S_FORMAT_I2S&t;0x00
DECL|macro|VT1724_MT_DMA_INT_MASK
mdefine_line|#define VT1724_MT_DMA_INT_MASK&t;&t;0x03&t;/* byte -DMA Interrupt Mask */
multiline_comment|/* lool to VT1724_MULTI_* */
DECL|macro|VT1724_MT_AC97_INDEX
mdefine_line|#define VT1724_MT_AC97_INDEX&t;&t;0x04&t;/* byte - AC&squot;97 index */
DECL|macro|VT1724_MT_AC97_CMD
mdefine_line|#define VT1724_MT_AC97_CMD&t;&t;0x05&t;/* byte - AC&squot;97 command &amp; status */
DECL|macro|VT1724_AC97_COLD
mdefine_line|#define   VT1724_AC97_COLD&t;0x80&t;/* cold reset */
DECL|macro|VT1724_AC97_WARM
mdefine_line|#define   VT1724_AC97_WARM&t;0x40&t;/* warm reset */
DECL|macro|VT1724_AC97_WRITE
mdefine_line|#define   VT1724_AC97_WRITE&t;0x20&t;/* W: write, R: write in progress */
DECL|macro|VT1724_AC97_READ
mdefine_line|#define   VT1724_AC97_READ&t;0x10&t;/* W: read, R: read in progress */
DECL|macro|VT1724_AC97_READY
mdefine_line|#define   VT1724_AC97_READY&t;0x08&t;/* codec ready status bit */
DECL|macro|VT1724_AC97_ID_MASK
mdefine_line|#define   VT1724_AC97_ID_MASK&t;0x03&t;/* codec id mask */
DECL|macro|VT1724_MT_AC97_DATA
mdefine_line|#define VT1724_MT_AC97_DATA&t;&t;0x06&t;/* word - AC&squot;97 data */
DECL|macro|VT1724_MT_PLAYBACK_ADDR
mdefine_line|#define VT1724_MT_PLAYBACK_ADDR&t;&t;0x10&t;/* dword - playback address */
DECL|macro|VT1724_MT_PLAYBACK_SIZE
mdefine_line|#define VT1724_MT_PLAYBACK_SIZE&t;&t;0x14&t;/* dword - playback size */
DECL|macro|VT1724_MT_DMA_CONTROL
mdefine_line|#define VT1724_MT_DMA_CONTROL&t;&t;0x18&t;/* byte - control */
DECL|macro|VT1724_PDMA4_START
mdefine_line|#define   VT1724_PDMA4_START&t;0x80&t;/* SPDIF out / PDMA4 start */
DECL|macro|VT1724_PDMA3_START
mdefine_line|#define   VT1724_PDMA3_START&t;0x40&t;/* PDMA3 start */
DECL|macro|VT1724_PDMA2_START
mdefine_line|#define   VT1724_PDMA2_START&t;0x20&t;/* PDMA2 start */
DECL|macro|VT1724_PDMA1_START
mdefine_line|#define   VT1724_PDMA1_START&t;0x10&t;/* PDMA1 start */
DECL|macro|VT1724_RDMA1_START
mdefine_line|#define   VT1724_RDMA1_START&t;0x04&t;/* RDMA1 start */
DECL|macro|VT1724_RDMA0_START
mdefine_line|#define   VT1724_RDMA0_START&t;0x02&t;/* RMDA0 start */
DECL|macro|VT1724_PDMA0_START
mdefine_line|#define   VT1724_PDMA0_START&t;0x01&t;/* MC Interleave / PDMA0 start */
DECL|macro|VT1724_MT_BURST
mdefine_line|#define VT1724_MT_BURST&t;&t;&t;0x19&t;/* Interleaved playback DMA Active streams / PCI burst size */
DECL|macro|VT1724_MT_DMA_FIFO_ERR
mdefine_line|#define VT1724_MT_DMA_FIFO_ERR&t;&t;0x1a&t;/*Global playback and record DMA FIFO Underrun/Overrun */
DECL|macro|VT1724_PDMA4_UNDERRUN
mdefine_line|#define   VT1724_PDMA4_UNDERRUN&t;&t;0x80
DECL|macro|VT1724_PDMA2_UNDERRUN
mdefine_line|#define   VT1724_PDMA2_UNDERRUN&t;&t;0x40
DECL|macro|VT1724_PDMA3_UNDERRUN
mdefine_line|#define   VT1724_PDMA3_UNDERRUN&t;&t;0x20
DECL|macro|VT1724_PDMA1_UNDERRUN
mdefine_line|#define   VT1724_PDMA1_UNDERRUN&t;&t;0x10
DECL|macro|VT1724_RDMA1_UNDERRUN
mdefine_line|#define   VT1724_RDMA1_UNDERRUN&t;&t;0x04
DECL|macro|VT1724_RDMA0_UNDERRUN
mdefine_line|#define   VT1724_RDMA0_UNDERRUN&t;&t;0x02
DECL|macro|VT1724_PDMA0_UNDERRUN
mdefine_line|#define   VT1724_PDMA0_UNDERRUN&t;&t;0x01
DECL|macro|VT1724_MT_DMA_PAUSE
mdefine_line|#define VT1724_MT_DMA_PAUSE&t;&t;0x1b&t;/*Global playback and record DMA FIFO pause/resume */
DECL|macro|VT1724_PDMA4_PAUSE
mdefine_line|#define&t;  VT1724_PDMA4_PAUSE&t;0x80
DECL|macro|VT1724_PDMA3_PAUSE
mdefine_line|#define&t;  VT1724_PDMA3_PAUSE&t;0x40
DECL|macro|VT1724_PDMA2_PAUSE
mdefine_line|#define&t;  VT1724_PDMA2_PAUSE&t;0x20
DECL|macro|VT1724_PDMA1_PAUSE
mdefine_line|#define&t;  VT1724_PDMA1_PAUSE&t;0x10
DECL|macro|VT1724_RDMA1_PAUSE
mdefine_line|#define&t;  VT1724_RDMA1_PAUSE&t;0x04
DECL|macro|VT1724_RDMA0_PAUSE
mdefine_line|#define&t;  VT1724_RDMA0_PAUSE&t;0x02
DECL|macro|VT1724_PDMA0_PAUSE
mdefine_line|#define&t;  VT1724_PDMA0_PAUSE&t;0x01
DECL|macro|VT1724_MT_PLAYBACK_COUNT
mdefine_line|#define VT1724_MT_PLAYBACK_COUNT&t;0x1c&t;/* word - playback count */
DECL|macro|VT1724_MT_CAPTURE_ADDR
mdefine_line|#define VT1724_MT_CAPTURE_ADDR&t;&t;0x20&t;/* dword - capture address */
DECL|macro|VT1724_MT_CAPTURE_SIZE
mdefine_line|#define VT1724_MT_CAPTURE_SIZE&t;&t;0x24&t;/* word - capture size */
DECL|macro|VT1724_MT_CAPTURE_COUNT
mdefine_line|#define VT1724_MT_CAPTURE_COUNT&t;&t;0x26&t;/* word - capture count */
DECL|macro|VT1724_MT_ROUTE_PLAYBACK
mdefine_line|#define VT1724_MT_ROUTE_PLAYBACK&t;0x2c&t;/* word */
DECL|macro|VT1724_MT_RDMA1_ADDR
mdefine_line|#define VT1724_MT_RDMA1_ADDR&t;&t;0x30&t;/* dword - RDMA1 capture address */
DECL|macro|VT1724_MT_RDMA1_SIZE
mdefine_line|#define VT1724_MT_RDMA1_SIZE&t;&t;0x34&t;/* word - RDMA1 capture size */
DECL|macro|VT1724_MT_RDMA1_COUNT
mdefine_line|#define VT1724_MT_RDMA1_COUNT&t;&t;0x36&t;/* word - RDMA1 capture count */
DECL|macro|VT1724_MT_SPDIF_CTRL
mdefine_line|#define VT1724_MT_SPDIF_CTRL&t;&t;0x3c&t;/* word */
DECL|macro|VT1724_MT_MONITOR_PEAKINDEX
mdefine_line|#define VT1724_MT_MONITOR_PEAKINDEX&t;0x3e&t;/* byte */
DECL|macro|VT1724_MT_MONITOR_PEAKDATA
mdefine_line|#define VT1724_MT_MONITOR_PEAKDATA&t;0x3f&t;/* byte */
multiline_comment|/* concurrent stereo channels */
DECL|macro|VT1724_MT_PDMA4_ADDR
mdefine_line|#define VT1724_MT_PDMA4_ADDR&t;&t;0x40&t;/* dword */
DECL|macro|VT1724_MT_PDMA4_SIZE
mdefine_line|#define VT1724_MT_PDMA4_SIZE&t;&t;0x44&t;/* word */
DECL|macro|VT1724_MT_PDMA4_COUNT
mdefine_line|#define VT1724_MT_PDMA4_COUNT&t;&t;0x46&t;/* word */
DECL|macro|VT1724_MT_PDMA3_ADDR
mdefine_line|#define VT1724_MT_PDMA3_ADDR&t;&t;0x50&t;/* dword */
DECL|macro|VT1724_MT_PDMA3_SIZE
mdefine_line|#define VT1724_MT_PDMA3_SIZE&t;&t;0x54&t;/* word */
DECL|macro|VT1724_MT_PDMA3_COUNT
mdefine_line|#define VT1724_MT_PDMA3_COUNT&t;&t;0x56&t;/* word */
DECL|macro|VT1724_MT_PDMA2_ADDR
mdefine_line|#define VT1724_MT_PDMA2_ADDR&t;&t;0x60&t;/* dword */
DECL|macro|VT1724_MT_PDMA2_SIZE
mdefine_line|#define VT1724_MT_PDMA2_SIZE&t;&t;0x64&t;/* word */
DECL|macro|VT1724_MT_PDMA2_COUNT
mdefine_line|#define VT1724_MT_PDMA2_COUNT&t;&t;0x66&t;/* word */
DECL|macro|VT1724_MT_PDMA1_ADDR
mdefine_line|#define VT1724_MT_PDMA1_ADDR&t;&t;0x70&t;/* dword */
DECL|macro|VT1724_MT_PDMA1_SIZE
mdefine_line|#define VT1724_MT_PDMA1_SIZE&t;&t;0x74&t;/* word */
DECL|macro|VT1724_MT_PDMA1_COUNT
mdefine_line|#define VT1724_MT_PDMA1_COUNT&t;&t;0x76&t;/* word */
macro_line|#endif /* __SOUND_VT1724_H */
eof
