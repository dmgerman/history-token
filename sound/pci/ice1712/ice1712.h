macro_line|#ifndef __SOUND_ICE1712_H
DECL|macro|__SOUND_ICE1712_H
mdefine_line|#define __SOUND_ICE1712_H
multiline_comment|/*&n; *   ALSA driver for ICEnsemble ICE1712 (Envy24)&n; *&n; *&t;Copyright (c) 2000 Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &lt;sound/control.h&gt;
macro_line|#include &lt;sound/ac97_codec.h&gt;
macro_line|#include &lt;sound/rawmidi.h&gt;
macro_line|#include &lt;sound/i2c.h&gt;
macro_line|#include &lt;sound/ak4xxx-adda.h&gt;
macro_line|#include &lt;sound/pcm.h&gt;
multiline_comment|/*&n; *  Direct registers&n; */
DECL|macro|ICEREG
mdefine_line|#define ICEREG(ice, x) ((ice)-&gt;port + ICE1712_REG_##x)
DECL|macro|ICE1712_REG_CONTROL
mdefine_line|#define ICE1712_REG_CONTROL&t;&t;0x00&t;/* byte */
DECL|macro|ICE1712_RESET
mdefine_line|#define   ICE1712_RESET&t;&t;&t;0x80&t;/* reset whole chip */
DECL|macro|ICE1712_SERR_LEVEL
mdefine_line|#define   ICE1712_SERR_LEVEL&t;&t;0x04&t;/* SERR# level otherwise edge */
DECL|macro|ICE1712_NATIVE
mdefine_line|#define   ICE1712_NATIVE&t;&t;0x01&t;/* native mode otherwise SB */
DECL|macro|ICE1712_REG_IRQMASK
mdefine_line|#define ICE1712_REG_IRQMASK&t;&t;0x01&t;/* byte */
DECL|macro|ICE1712_IRQ_MPU1
mdefine_line|#define   ICE1712_IRQ_MPU1&t;&t;0x80
DECL|macro|ICE1712_IRQ_TIMER
mdefine_line|#define   ICE1712_IRQ_TIMER&t;&t;0x40
DECL|macro|ICE1712_IRQ_MPU2
mdefine_line|#define   ICE1712_IRQ_MPU2&t;&t;0x20
DECL|macro|ICE1712_IRQ_PROPCM
mdefine_line|#define   ICE1712_IRQ_PROPCM&t;&t;0x10
DECL|macro|ICE1712_IRQ_FM
mdefine_line|#define   ICE1712_IRQ_FM&t;&t;0x08&t;/* FM/MIDI - legacy */
DECL|macro|ICE1712_IRQ_PBKDS
mdefine_line|#define   ICE1712_IRQ_PBKDS&t;&t;0x04&t;/* playback DS channels */
DECL|macro|ICE1712_IRQ_CONCAP
mdefine_line|#define   ICE1712_IRQ_CONCAP&t;&t;0x02&t;/* consumer capture */
DECL|macro|ICE1712_IRQ_CONPBK
mdefine_line|#define   ICE1712_IRQ_CONPBK&t;&t;0x01&t;/* consumer playback */
DECL|macro|ICE1712_REG_IRQSTAT
mdefine_line|#define ICE1712_REG_IRQSTAT&t;&t;0x02&t;/* byte */
multiline_comment|/* look to ICE1712_IRQ_* */
DECL|macro|ICE1712_REG_INDEX
mdefine_line|#define ICE1712_REG_INDEX&t;&t;0x03&t;/* byte - indirect CCIxx regs */
DECL|macro|ICE1712_REG_DATA
mdefine_line|#define ICE1712_REG_DATA&t;&t;0x04&t;/* byte - indirect CCIxx regs */
DECL|macro|ICE1712_REG_NMI_STAT1
mdefine_line|#define ICE1712_REG_NMI_STAT1&t;&t;0x05&t;/* byte */
DECL|macro|ICE1712_REG_NMI_DATA
mdefine_line|#define ICE1712_REG_NMI_DATA&t;&t;0x06&t;/* byte */
DECL|macro|ICE1712_REG_NMI_INDEX
mdefine_line|#define ICE1712_REG_NMI_INDEX&t;&t;0x07&t;/* byte */
DECL|macro|ICE1712_REG_AC97_INDEX
mdefine_line|#define ICE1712_REG_AC97_INDEX&t;&t;0x08&t;/* byte */
DECL|macro|ICE1712_REG_AC97_CMD
mdefine_line|#define ICE1712_REG_AC97_CMD&t;&t;0x09&t;/* byte */
DECL|macro|ICE1712_AC97_COLD
mdefine_line|#define   ICE1712_AC97_COLD&t;&t;0x80&t;/* cold reset */
DECL|macro|ICE1712_AC97_WARM
mdefine_line|#define   ICE1712_AC97_WARM&t;&t;0x40&t;/* warm reset */
DECL|macro|ICE1712_AC97_WRITE
mdefine_line|#define   ICE1712_AC97_WRITE&t;&t;0x20&t;/* W: write, R: write in progress */
DECL|macro|ICE1712_AC97_READ
mdefine_line|#define   ICE1712_AC97_READ&t;&t;0x10&t;/* W: read, R: read in progress */
DECL|macro|ICE1712_AC97_READY
mdefine_line|#define   ICE1712_AC97_READY&t;&t;0x08&t;/* codec ready status bit */
DECL|macro|ICE1712_AC97_PBK_VSR
mdefine_line|#define   ICE1712_AC97_PBK_VSR&t;&t;0x02&t;/* playback VSR */
DECL|macro|ICE1712_AC97_CAP_VSR
mdefine_line|#define   ICE1712_AC97_CAP_VSR&t;&t;0x01&t;/* capture VSR */
DECL|macro|ICE1712_REG_AC97_DATA
mdefine_line|#define ICE1712_REG_AC97_DATA&t;&t;0x0a&t;/* word (little endian) */
DECL|macro|ICE1712_REG_MPU1_CTRL
mdefine_line|#define ICE1712_REG_MPU1_CTRL&t;&t;0x0c&t;/* byte */
DECL|macro|ICE1712_REG_MPU1_DATA
mdefine_line|#define ICE1712_REG_MPU1_DATA&t;&t;0x0d&t;/* byte */
DECL|macro|ICE1712_REG_I2C_DEV_ADDR
mdefine_line|#define ICE1712_REG_I2C_DEV_ADDR&t;0x10&t;/* byte */
DECL|macro|ICE1712_I2C_WRITE
mdefine_line|#define   ICE1712_I2C_WRITE&t;&t;0x01&t;/* write direction */
DECL|macro|ICE1712_REG_I2C_BYTE_ADDR
mdefine_line|#define ICE1712_REG_I2C_BYTE_ADDR&t;0x11&t;/* byte */
DECL|macro|ICE1712_REG_I2C_DATA
mdefine_line|#define ICE1712_REG_I2C_DATA&t;&t;0x12&t;/* byte */
DECL|macro|ICE1712_REG_I2C_CTRL
mdefine_line|#define ICE1712_REG_I2C_CTRL&t;&t;0x13&t;/* byte */
DECL|macro|ICE1712_I2C_EEPROM
mdefine_line|#define   ICE1712_I2C_EEPROM&t;&t;0x80&t;/* EEPROM exists */
DECL|macro|ICE1712_I2C_BUSY
mdefine_line|#define   ICE1712_I2C_BUSY&t;&t;0x01&t;/* busy bit */
DECL|macro|ICE1712_REG_CONCAP_ADDR
mdefine_line|#define ICE1712_REG_CONCAP_ADDR&t;&t;0x14&t;/* dword - consumer capture */
DECL|macro|ICE1712_REG_CONCAP_COUNT
mdefine_line|#define ICE1712_REG_CONCAP_COUNT&t;0x18&t;/* word - current/base count */
DECL|macro|ICE1712_REG_SERR_SHADOW
mdefine_line|#define ICE1712_REG_SERR_SHADOW&t;&t;0x1b&t;/* byte */
DECL|macro|ICE1712_REG_MPU2_CTRL
mdefine_line|#define ICE1712_REG_MPU2_CTRL&t;&t;0x1c&t;/* byte */
DECL|macro|ICE1712_REG_MPU2_DATA
mdefine_line|#define ICE1712_REG_MPU2_DATA&t;&t;0x1d&t;/* byte */
DECL|macro|ICE1712_REG_TIMER
mdefine_line|#define ICE1712_REG_TIMER&t;&t;0x1e&t;/* word */
multiline_comment|/*&n; *  Indirect registers&n; */
DECL|macro|ICE1712_IREG_PBK_COUNT_LO
mdefine_line|#define ICE1712_IREG_PBK_COUNT_LO&t;0x00
DECL|macro|ICE1712_IREG_PBK_COUNT_HI
mdefine_line|#define ICE1712_IREG_PBK_COUNT_HI&t;0x01
DECL|macro|ICE1712_IREG_PBK_CTRL
mdefine_line|#define ICE1712_IREG_PBK_CTRL&t;&t;0x02
DECL|macro|ICE1712_IREG_PBK_LEFT
mdefine_line|#define ICE1712_IREG_PBK_LEFT&t;&t;0x03&t;/* left volume */
DECL|macro|ICE1712_IREG_PBK_RIGHT
mdefine_line|#define ICE1712_IREG_PBK_RIGHT&t;&t;0x04&t;/* right volume */
DECL|macro|ICE1712_IREG_PBK_SOFT
mdefine_line|#define ICE1712_IREG_PBK_SOFT&t;&t;0x05&t;/* soft volume */
DECL|macro|ICE1712_IREG_PBK_RATE_LO
mdefine_line|#define ICE1712_IREG_PBK_RATE_LO&t;0x06
DECL|macro|ICE1712_IREG_PBK_RATE_MID
mdefine_line|#define ICE1712_IREG_PBK_RATE_MID&t;0x07
DECL|macro|ICE1712_IREG_PBK_RATE_HI
mdefine_line|#define ICE1712_IREG_PBK_RATE_HI&t;0x08
DECL|macro|ICE1712_IREG_CAP_COUNT_LO
mdefine_line|#define ICE1712_IREG_CAP_COUNT_LO&t;0x10
DECL|macro|ICE1712_IREG_CAP_COUNT_HI
mdefine_line|#define ICE1712_IREG_CAP_COUNT_HI&t;0x11
DECL|macro|ICE1712_IREG_CAP_CTRL
mdefine_line|#define ICE1712_IREG_CAP_CTRL&t;&t;0x12
DECL|macro|ICE1712_IREG_GPIO_DATA
mdefine_line|#define ICE1712_IREG_GPIO_DATA&t;&t;0x20
DECL|macro|ICE1712_IREG_GPIO_WRITE_MASK
mdefine_line|#define ICE1712_IREG_GPIO_WRITE_MASK&t;0x21
DECL|macro|ICE1712_IREG_GPIO_DIRECTION
mdefine_line|#define ICE1712_IREG_GPIO_DIRECTION&t;0x22
DECL|macro|ICE1712_IREG_CONSUMER_POWERDOWN
mdefine_line|#define ICE1712_IREG_CONSUMER_POWERDOWN&t;0x30
DECL|macro|ICE1712_IREG_PRO_POWERDOWN
mdefine_line|#define ICE1712_IREG_PRO_POWERDOWN&t;0x31
multiline_comment|/*&n; *  Consumer section direct DMA registers&n; */
DECL|macro|ICEDS
mdefine_line|#define ICEDS(ice, x) ((ice)-&gt;dmapath_port + ICE1712_DS_##x)
DECL|macro|ICE1712_DS_INTMASK
mdefine_line|#define ICE1712_DS_INTMASK&t;&t;0x00&t;/* word - interrupt mask */
DECL|macro|ICE1712_DS_INTSTAT
mdefine_line|#define ICE1712_DS_INTSTAT&t;&t;0x02&t;/* word - interrupt status */
DECL|macro|ICE1712_DS_DATA
mdefine_line|#define ICE1712_DS_DATA&t;&t;&t;0x04&t;/* dword - channel data */
DECL|macro|ICE1712_DS_INDEX
mdefine_line|#define ICE1712_DS_INDEX&t;&t;0x08&t;/* dword - channel index */
multiline_comment|/*&n; *  Consumer section channel registers&n; */
DECL|macro|ICE1712_DSC_ADDR0
mdefine_line|#define ICE1712_DSC_ADDR0&t;&t;0x00&t;/* dword - base address 0 */
DECL|macro|ICE1712_DSC_COUNT0
mdefine_line|#define ICE1712_DSC_COUNT0&t;&t;0x01&t;/* word - count 0 */
DECL|macro|ICE1712_DSC_ADDR1
mdefine_line|#define ICE1712_DSC_ADDR1&t;&t;0x02&t;/* dword - base address 1 */
DECL|macro|ICE1712_DSC_COUNT1
mdefine_line|#define ICE1712_DSC_COUNT1&t;&t;0x03&t;/* word - count 1 */
DECL|macro|ICE1712_DSC_CONTROL
mdefine_line|#define ICE1712_DSC_CONTROL&t;&t;0x04&t;/* byte - control &amp; status */
DECL|macro|ICE1712_BUFFER1
mdefine_line|#define   ICE1712_BUFFER1&t;&t;0x80&t;/* buffer1 is active */
DECL|macro|ICE1712_BUFFER1_AUTO
mdefine_line|#define   ICE1712_BUFFER1_AUTO&t;&t;0x40&t;/* buffer1 auto init */
DECL|macro|ICE1712_BUFFER0_AUTO
mdefine_line|#define   ICE1712_BUFFER0_AUTO&t;&t;0x20&t;/* buffer0 auto init */
DECL|macro|ICE1712_FLUSH
mdefine_line|#define   ICE1712_FLUSH&t;&t;&t;0x10&t;/* flush FIFO */
DECL|macro|ICE1712_STEREO
mdefine_line|#define   ICE1712_STEREO&t;&t;0x08&t;/* stereo */
DECL|macro|ICE1712_16BIT
mdefine_line|#define   ICE1712_16BIT&t;&t;&t;0x04&t;/* 16-bit data */
DECL|macro|ICE1712_PAUSE
mdefine_line|#define   ICE1712_PAUSE&t;&t;&t;0x02&t;/* pause */
DECL|macro|ICE1712_START
mdefine_line|#define   ICE1712_START&t;&t;&t;0x01&t;/* start */
DECL|macro|ICE1712_DSC_RATE
mdefine_line|#define ICE1712_DSC_RATE&t;&t;0x05&t;/* dword - rate */
DECL|macro|ICE1712_DSC_VOLUME
mdefine_line|#define ICE1712_DSC_VOLUME&t;&t;0x06&t;/* word - volume control */
multiline_comment|/* &n; *  Professional multi-track direct control registers&n; */
DECL|macro|ICEMT
mdefine_line|#define ICEMT(ice, x) ((ice)-&gt;profi_port + ICE1712_MT_##x)
DECL|macro|ICE1712_MT_IRQ
mdefine_line|#define ICE1712_MT_IRQ&t;&t;&t;0x00&t;/* byte - interrupt mask */
DECL|macro|ICE1712_MULTI_CAPTURE
mdefine_line|#define   ICE1712_MULTI_CAPTURE&t;&t;0x80&t;/* capture IRQ */
DECL|macro|ICE1712_MULTI_PLAYBACK
mdefine_line|#define   ICE1712_MULTI_PLAYBACK&t;0x40&t;/* playback IRQ */
DECL|macro|ICE1712_MULTI_CAPSTATUS
mdefine_line|#define   ICE1712_MULTI_CAPSTATUS&t;0x02&t;/* capture IRQ status */
DECL|macro|ICE1712_MULTI_PBKSTATUS
mdefine_line|#define   ICE1712_MULTI_PBKSTATUS&t;0x01&t;/* playback IRQ status */
DECL|macro|ICE1712_MT_RATE
mdefine_line|#define ICE1712_MT_RATE&t;&t;&t;0x01&t;/* byte - sampling rate select */
DECL|macro|ICE1712_SPDIF_MASTER
mdefine_line|#define   ICE1712_SPDIF_MASTER&t;&t;0x10&t;/* S/PDIF input is master clock */
DECL|macro|ICE1712_MT_I2S_FORMAT
mdefine_line|#define ICE1712_MT_I2S_FORMAT&t;&t;0x02&t;/* byte - I2S data format */
DECL|macro|ICE1712_MT_AC97_INDEX
mdefine_line|#define ICE1712_MT_AC97_INDEX&t;&t;0x04&t;/* byte - AC&squot;97 index */
DECL|macro|ICE1712_MT_AC97_CMD
mdefine_line|#define ICE1712_MT_AC97_CMD&t;&t;0x05&t;/* byte - AC&squot;97 command &amp; status */
multiline_comment|/* look to ICE1712_AC97_* */
DECL|macro|ICE1712_MT_AC97_DATA
mdefine_line|#define ICE1712_MT_AC97_DATA&t;&t;0x06&t;/* word - AC&squot;97 data */
DECL|macro|ICE1712_MT_PLAYBACK_ADDR
mdefine_line|#define ICE1712_MT_PLAYBACK_ADDR&t;0x10&t;/* dword - playback address */
DECL|macro|ICE1712_MT_PLAYBACK_SIZE
mdefine_line|#define ICE1712_MT_PLAYBACK_SIZE&t;0x14&t;/* word - playback size */
DECL|macro|ICE1712_MT_PLAYBACK_COUNT
mdefine_line|#define ICE1712_MT_PLAYBACK_COUNT&t;0x16&t;/* word - playback count */
DECL|macro|ICE1712_MT_PLAYBACK_CONTROL
mdefine_line|#define ICE1712_MT_PLAYBACK_CONTROL&t;0x18&t;/* byte - control */
DECL|macro|ICE1712_CAPTURE_START_SHADOW
mdefine_line|#define   ICE1712_CAPTURE_START_SHADOW&t;0x04&t;/* capture start */
DECL|macro|ICE1712_PLAYBACK_PAUSE
mdefine_line|#define   ICE1712_PLAYBACK_PAUSE&t;0x02&t;/* playback pause */
DECL|macro|ICE1712_PLAYBACK_START
mdefine_line|#define   ICE1712_PLAYBACK_START&t;0x01&t;/* playback start */
DECL|macro|ICE1712_MT_CAPTURE_ADDR
mdefine_line|#define ICE1712_MT_CAPTURE_ADDR&t;&t;0x20&t;/* dword - capture address */
DECL|macro|ICE1712_MT_CAPTURE_SIZE
mdefine_line|#define ICE1712_MT_CAPTURE_SIZE&t;&t;0x24&t;/* word - capture size */
DECL|macro|ICE1712_MT_CAPTURE_COUNT
mdefine_line|#define ICE1712_MT_CAPTURE_COUNT&t;0x26&t;/* word - capture count */
DECL|macro|ICE1712_MT_CAPTURE_CONTROL
mdefine_line|#define ICE1712_MT_CAPTURE_CONTROL&t;0x28&t;/* byte - control */
DECL|macro|ICE1712_CAPTURE_START
mdefine_line|#define   ICE1712_CAPTURE_START&t;&t;0x01&t;/* capture start */
DECL|macro|ICE1712_MT_ROUTE_PSDOUT03
mdefine_line|#define ICE1712_MT_ROUTE_PSDOUT03&t;0x30&t;/* word */
DECL|macro|ICE1712_MT_ROUTE_SPDOUT
mdefine_line|#define ICE1712_MT_ROUTE_SPDOUT&t;&t;0x32&t;/* word */
DECL|macro|ICE1712_MT_ROUTE_CAPTURE
mdefine_line|#define ICE1712_MT_ROUTE_CAPTURE&t;0x34&t;/* dword */
DECL|macro|ICE1712_MT_MONITOR_VOLUME
mdefine_line|#define ICE1712_MT_MONITOR_VOLUME&t;0x38&t;/* word */
DECL|macro|ICE1712_MT_MONITOR_INDEX
mdefine_line|#define ICE1712_MT_MONITOR_INDEX&t;0x3a&t;/* byte */
DECL|macro|ICE1712_MT_MONITOR_RATE
mdefine_line|#define ICE1712_MT_MONITOR_RATE&t;&t;0x3b&t;/* byte */
DECL|macro|ICE1712_MT_MONITOR_ROUTECTRL
mdefine_line|#define ICE1712_MT_MONITOR_ROUTECTRL&t;0x3c&t;/* byte */
DECL|macro|ICE1712_ROUTE_AC97
mdefine_line|#define   ICE1712_ROUTE_AC97&t;&t;0x01&t;/* route digital mixer output to AC&squot;97 */
DECL|macro|ICE1712_MT_MONITOR_PEAKINDEX
mdefine_line|#define ICE1712_MT_MONITOR_PEAKINDEX&t;0x3e&t;/* byte */
DECL|macro|ICE1712_MT_MONITOR_PEAKDATA
mdefine_line|#define ICE1712_MT_MONITOR_PEAKDATA&t;0x3f&t;/* byte */
multiline_comment|/*&n; *  Codec configuration bits&n; */
multiline_comment|/* PCI[60] System Configuration */
DECL|macro|ICE1712_CFG_CLOCK
mdefine_line|#define ICE1712_CFG_CLOCK&t;0xc0
DECL|macro|ICE1712_CFG_CLOCK512
mdefine_line|#define   ICE1712_CFG_CLOCK512&t;0x00&t;/* 22.5692Mhz, 44.1kHz*512 */
DECL|macro|ICE1712_CFG_CLOCK384
mdefine_line|#define   ICE1712_CFG_CLOCK384  0x40&t;/* 16.9344Mhz, 44.1kHz*384 */
DECL|macro|ICE1712_CFG_EXT
mdefine_line|#define   ICE1712_CFG_EXT&t;0x80&t;/* external clock */
DECL|macro|ICE1712_CFG_2xMPU401
mdefine_line|#define ICE1712_CFG_2xMPU401&t;0x20&t;/* two MPU401 UARTs */
DECL|macro|ICE1712_CFG_NO_CON_AC97
mdefine_line|#define ICE1712_CFG_NO_CON_AC97 0x10&t;/* consumer AC&squot;97 codec is not present */
DECL|macro|ICE1712_CFG_ADC_MASK
mdefine_line|#define ICE1712_CFG_ADC_MASK&t;0x0c&t;/* one, two, three, four stereo ADCs */
DECL|macro|ICE1712_CFG_DAC_MASK
mdefine_line|#define ICE1712_CFG_DAC_MASK&t;0x03&t;/* one, two, three, four stereo DACs */
multiline_comment|/* PCI[61] AC-Link Configuration */
DECL|macro|ICE1712_CFG_PRO_I2S
mdefine_line|#define ICE1712_CFG_PRO_I2S&t;0x80&t;/* multitrack converter: I2S or AC&squot;97 */
DECL|macro|ICE1712_CFG_AC97_PACKED
mdefine_line|#define ICE1712_CFG_AC97_PACKED&t;0x01&t;/* split or packed mode - AC&squot;97 */
multiline_comment|/* PCI[62] I2S Features */
DECL|macro|ICE1712_CFG_I2S_VOLUME
mdefine_line|#define ICE1712_CFG_I2S_VOLUME&t;0x80&t;/* volume/mute capability */
DECL|macro|ICE1712_CFG_I2S_96KHZ
mdefine_line|#define ICE1712_CFG_I2S_96KHZ&t;0x40&t;/* supports 96kHz sampling */
DECL|macro|ICE1712_CFG_I2S_RESMASK
mdefine_line|#define ICE1712_CFG_I2S_RESMASK&t;0x30&t;/* resolution mask, 16,18,20,24-bit */
DECL|macro|ICE1712_CFG_I2S_OTHER
mdefine_line|#define ICE1712_CFG_I2S_OTHER&t;0x0f&t;/* other I2S IDs */
multiline_comment|/* PCI[63] S/PDIF Configuration */
DECL|macro|ICE1712_CFG_I2S_CHIPID
mdefine_line|#define ICE1712_CFG_I2S_CHIPID&t;0xfc&t;/* I2S chip ID */
DECL|macro|ICE1712_CFG_SPDIF_IN
mdefine_line|#define ICE1712_CFG_SPDIF_IN&t;0x02&t;/* S/PDIF input is present */
DECL|macro|ICE1712_CFG_SPDIF_OUT
mdefine_line|#define ICE1712_CFG_SPDIF_OUT&t;0x01&t;/* S/PDIF output is present */
multiline_comment|/*&n; * DMA mode values&n; * identical with DMA_XXX on i386 architecture.&n; */
DECL|macro|ICE1712_DMA_MODE_WRITE
mdefine_line|#define ICE1712_DMA_MODE_WRITE&t;&t;0x48
DECL|macro|ICE1712_DMA_AUTOINIT
mdefine_line|#define ICE1712_DMA_AUTOINIT&t;&t;0x10
multiline_comment|/*&n; *  &n; */
DECL|typedef|ice1712_t
r_typedef
r_struct
id|_snd_ice1712
id|ice1712_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|subvendor
r_int
r_int
id|subvendor
suffix:semicolon
multiline_comment|/* PCI[2c-2f] */
DECL|member|size
r_int
r_char
id|size
suffix:semicolon
multiline_comment|/* size of EEPROM image in bytes */
DECL|member|version
r_int
r_char
id|version
suffix:semicolon
multiline_comment|/* must be 1 (or 2 for vt1724) */
DECL|member|data
r_int
r_char
id|data
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|gpiomask
r_int
r_int
id|gpiomask
suffix:semicolon
DECL|member|gpiostate
r_int
r_int
id|gpiostate
suffix:semicolon
DECL|member|gpiodir
r_int
r_int
id|gpiodir
suffix:semicolon
DECL|typedef|ice1712_eeprom_t
)brace
id|ice1712_eeprom_t
suffix:semicolon
r_enum
(brace
DECL|enumerator|ICE_EEP1_CODEC
id|ICE_EEP1_CODEC
op_assign
l_int|0
comma
multiline_comment|/* 06 */
DECL|enumerator|ICE_EEP1_ACLINK
id|ICE_EEP1_ACLINK
comma
multiline_comment|/* 07 */
DECL|enumerator|ICE_EEP1_I2SID
id|ICE_EEP1_I2SID
comma
multiline_comment|/* 08 */
DECL|enumerator|ICE_EEP1_SPDIF
id|ICE_EEP1_SPDIF
comma
multiline_comment|/* 09 */
DECL|enumerator|ICE_EEP1_GPIO_MASK
id|ICE_EEP1_GPIO_MASK
comma
multiline_comment|/* 0a */
DECL|enumerator|ICE_EEP1_GPIO_STATE
id|ICE_EEP1_GPIO_STATE
comma
multiline_comment|/* 0b */
DECL|enumerator|ICE_EEP1_GPIO_DIR
id|ICE_EEP1_GPIO_DIR
comma
multiline_comment|/* 0c */
DECL|enumerator|ICE_EEP1_AC97_MAIN_LO
id|ICE_EEP1_AC97_MAIN_LO
comma
multiline_comment|/* 0d */
DECL|enumerator|ICE_EEP1_AC97_MAIN_HI
id|ICE_EEP1_AC97_MAIN_HI
comma
multiline_comment|/* 0e */
DECL|enumerator|ICE_EEP1_AC97_PCM_LO
id|ICE_EEP1_AC97_PCM_LO
comma
multiline_comment|/* 0f */
DECL|enumerator|ICE_EEP1_AC97_PCM_HI
id|ICE_EEP1_AC97_PCM_HI
comma
multiline_comment|/* 10 */
DECL|enumerator|ICE_EEP1_AC97_REC_LO
id|ICE_EEP1_AC97_REC_LO
comma
multiline_comment|/* 11 */
DECL|enumerator|ICE_EEP1_AC97_REC_HI
id|ICE_EEP1_AC97_REC_HI
comma
multiline_comment|/* 12 */
DECL|enumerator|ICE_EEP1_AC97_RECSRC
id|ICE_EEP1_AC97_RECSRC
comma
multiline_comment|/* 13 */
DECL|enumerator|ICE_EEP1_DAC_ID
id|ICE_EEP1_DAC_ID
comma
multiline_comment|/* 14 */
DECL|enumerator|ICE_EEP1_DAC_ID1
id|ICE_EEP1_DAC_ID1
comma
DECL|enumerator|ICE_EEP1_DAC_ID2
id|ICE_EEP1_DAC_ID2
comma
DECL|enumerator|ICE_EEP1_DAC_ID3
id|ICE_EEP1_DAC_ID3
comma
DECL|enumerator|ICE_EEP1_ADC_ID
id|ICE_EEP1_ADC_ID
comma
multiline_comment|/* 18 */
DECL|enumerator|ICE_EEP1_ADC_ID1
id|ICE_EEP1_ADC_ID1
comma
DECL|enumerator|ICE_EEP1_ADC_ID2
id|ICE_EEP1_ADC_ID2
comma
DECL|enumerator|ICE_EEP1_ADC_ID3
id|ICE_EEP1_ADC_ID3
)brace
suffix:semicolon
DECL|macro|ice_has_con_ac97
mdefine_line|#define ice_has_con_ac97(ice)&t;(!((ice)-&gt;eeprom.data[ICE_EEP1_CODEC] &amp; ICE1712_CFG_NO_CON_AC97))
DECL|struct|snd_ak4xxx_private
r_struct
id|snd_ak4xxx_private
(brace
DECL|member|cif
r_int
r_int
id|cif
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* CIF mode */
DECL|member|caddr
r_int
r_char
id|caddr
suffix:semicolon
multiline_comment|/* C0 and C1 bits */
DECL|member|data_mask
r_int
r_int
id|data_mask
suffix:semicolon
multiline_comment|/* DATA gpio bit */
DECL|member|clk_mask
r_int
r_int
id|clk_mask
suffix:semicolon
multiline_comment|/* CLK gpio bit */
DECL|member|cs_mask
r_int
r_int
id|cs_mask
suffix:semicolon
multiline_comment|/* bit mask for select/deselect address */
DECL|member|cs_addr
r_int
r_int
id|cs_addr
suffix:semicolon
multiline_comment|/* bits to select address */
DECL|member|cs_none
r_int
r_int
id|cs_none
suffix:semicolon
multiline_comment|/* bits to deselect address */
DECL|member|add_flags
r_int
r_int
id|add_flags
suffix:semicolon
multiline_comment|/* additional bits at init */
DECL|member|mask_flags
r_int
r_int
id|mask_flags
suffix:semicolon
multiline_comment|/* total mask bits */
DECL|struct|snd_akm4xxx_ops
r_struct
id|snd_akm4xxx_ops
(brace
DECL|member|set_rate_val
r_void
(paren
op_star
id|set_rate_val
)paren
(paren
id|akm4xxx_t
op_star
id|ak
comma
r_int
r_int
id|rate
)paren
suffix:semicolon
DECL|member|ops
)brace
id|ops
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|snd_ice1712_spdif
r_struct
id|snd_ice1712_spdif
(brace
DECL|member|cs8403_bits
r_int
r_char
id|cs8403_bits
suffix:semicolon
DECL|member|cs8403_stream_bits
r_int
r_char
id|cs8403_stream_bits
suffix:semicolon
DECL|member|stream_ctl
id|snd_kcontrol_t
op_star
id|stream_ctl
suffix:semicolon
DECL|struct|snd_ice1712_spdif_ops
r_struct
id|snd_ice1712_spdif_ops
(brace
DECL|member|open
r_void
(paren
op_star
id|open
)paren
(paren
id|ice1712_t
op_star
comma
id|snd_pcm_substream_t
op_star
)paren
suffix:semicolon
DECL|member|setup_rate
r_void
(paren
op_star
id|setup_rate
)paren
(paren
id|ice1712_t
op_star
comma
r_int
id|rate
)paren
suffix:semicolon
DECL|member|close
r_void
(paren
op_star
id|close
)paren
(paren
id|ice1712_t
op_star
comma
id|snd_pcm_substream_t
op_star
)paren
suffix:semicolon
DECL|member|default_get
r_void
(paren
op_star
id|default_get
)paren
(paren
id|ice1712_t
op_star
comma
id|snd_ctl_elem_value_t
op_star
id|ucontrol
)paren
suffix:semicolon
DECL|member|default_put
r_int
(paren
op_star
id|default_put
)paren
(paren
id|ice1712_t
op_star
comma
id|snd_ctl_elem_value_t
op_star
id|ucontrol
)paren
suffix:semicolon
DECL|member|stream_get
r_void
(paren
op_star
id|stream_get
)paren
(paren
id|ice1712_t
op_star
comma
id|snd_ctl_elem_value_t
op_star
id|ucontrol
)paren
suffix:semicolon
DECL|member|stream_put
r_int
(paren
op_star
id|stream_put
)paren
(paren
id|ice1712_t
op_star
comma
id|snd_ctl_elem_value_t
op_star
id|ucontrol
)paren
suffix:semicolon
DECL|member|ops
)brace
id|ops
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|_snd_ice1712
r_struct
id|_snd_ice1712
(brace
DECL|member|conp_dma_size
r_int
r_int
id|conp_dma_size
suffix:semicolon
DECL|member|conc_dma_size
r_int
r_int
id|conc_dma_size
suffix:semicolon
DECL|member|prop_dma_size
r_int
r_int
id|prop_dma_size
suffix:semicolon
DECL|member|proc_dma_size
r_int
r_int
id|proc_dma_size
suffix:semicolon
DECL|member|irq
r_int
id|irq
suffix:semicolon
DECL|member|port
r_int
r_int
id|port
suffix:semicolon
DECL|member|ddma_port
r_int
r_int
id|ddma_port
suffix:semicolon
DECL|member|dmapath_port
r_int
r_int
id|dmapath_port
suffix:semicolon
DECL|member|profi_port
r_int
r_int
id|profi_port
suffix:semicolon
DECL|member|pci
r_struct
id|pci_dev
op_star
id|pci
suffix:semicolon
DECL|member|card
id|snd_card_t
op_star
id|card
suffix:semicolon
DECL|member|pcm
id|snd_pcm_t
op_star
id|pcm
suffix:semicolon
DECL|member|pcm_ds
id|snd_pcm_t
op_star
id|pcm_ds
suffix:semicolon
DECL|member|pcm_pro
id|snd_pcm_t
op_star
id|pcm_pro
suffix:semicolon
DECL|member|playback_con_substream
id|snd_pcm_substream_t
op_star
id|playback_con_substream
suffix:semicolon
DECL|member|playback_con_substream_ds
id|snd_pcm_substream_t
op_star
id|playback_con_substream_ds
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|capture_con_substream
id|snd_pcm_substream_t
op_star
id|capture_con_substream
suffix:semicolon
DECL|member|playback_pro_substream
id|snd_pcm_substream_t
op_star
id|playback_pro_substream
suffix:semicolon
DECL|member|capture_pro_substream
id|snd_pcm_substream_t
op_star
id|capture_pro_substream
suffix:semicolon
DECL|member|playback_pro_size
r_int
r_int
id|playback_pro_size
suffix:semicolon
DECL|member|capture_pro_size
r_int
r_int
id|capture_pro_size
suffix:semicolon
DECL|member|playback_con_virt_addr
r_int
r_int
id|playback_con_virt_addr
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|playback_con_active_buf
r_int
r_int
id|playback_con_active_buf
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|capture_con_virt_addr
r_int
r_int
id|capture_con_virt_addr
suffix:semicolon
DECL|member|ac97_ext_id
r_int
r_int
id|ac97_ext_id
suffix:semicolon
DECL|member|ac97
id|ac97_t
op_star
id|ac97
suffix:semicolon
DECL|member|rmidi
id|snd_rawmidi_t
op_star
id|rmidi
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|reg_lock
id|spinlock_t
id|reg_lock
suffix:semicolon
DECL|member|proc_entry
id|snd_info_entry_t
op_star
id|proc_entry
suffix:semicolon
DECL|member|eeprom
id|ice1712_eeprom_t
id|eeprom
suffix:semicolon
DECL|member|pro_volumes
r_int
r_int
id|pro_volumes
(braket
l_int|20
)braket
suffix:semicolon
DECL|member|omni
r_int
r_int
id|omni
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Delta Omni I/O */
DECL|member|vt1724
r_int
r_int
id|vt1724
suffix:colon
l_int|1
suffix:semicolon
DECL|member|vt1720
r_int
r_int
id|vt1720
suffix:colon
l_int|1
suffix:semicolon
DECL|member|has_spdif
r_int
r_int
id|has_spdif
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* VT1720/4 - has SPDIF I/O */
DECL|member|force_pdma4
r_int
r_int
id|force_pdma4
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* VT1720/4 - PDMA4 as non-spdif */
DECL|member|force_rdma1
r_int
r_int
id|force_rdma1
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* VT1720/4 - RDMA1 as non-spdif */
DECL|member|num_total_dacs
r_int
r_int
id|num_total_dacs
suffix:semicolon
multiline_comment|/* total DACs */
DECL|member|num_total_adcs
r_int
r_int
id|num_total_adcs
suffix:semicolon
multiline_comment|/* total ADCs */
DECL|member|cur_rate
r_int
r_int
id|cur_rate
suffix:semicolon
multiline_comment|/* current rate */
DECL|member|open_mutex
r_struct
id|semaphore
id|open_mutex
suffix:semicolon
DECL|member|pcm_reserved
id|snd_pcm_substream_t
op_star
id|pcm_reserved
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|akm_codecs
r_int
r_int
id|akm_codecs
suffix:semicolon
DECL|member|akm
id|akm4xxx_t
op_star
id|akm
suffix:semicolon
DECL|member|spdif
r_struct
id|snd_ice1712_spdif
id|spdif
suffix:semicolon
DECL|member|i2c
id|snd_i2c_bus_t
op_star
id|i2c
suffix:semicolon
multiline_comment|/* I2C bus */
DECL|member|cs8427
id|snd_i2c_device_t
op_star
id|cs8427
suffix:semicolon
multiline_comment|/* CS8427 I2C device */
DECL|member|cs8427_timeout
r_int
r_int
id|cs8427_timeout
suffix:semicolon
multiline_comment|/* CS8427 reset timeout in HZ/100 */
DECL|struct|ice1712_gpio
r_struct
id|ice1712_gpio
(brace
DECL|member|direction
r_int
r_int
id|direction
suffix:semicolon
multiline_comment|/* current direction bits */
DECL|member|write_mask
r_int
r_int
id|write_mask
suffix:semicolon
multiline_comment|/* current mask bits */
DECL|member|saved
r_int
r_int
id|saved
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* for ewx_i2c */
multiline_comment|/* operators */
DECL|member|set_mask
r_void
(paren
op_star
id|set_mask
)paren
(paren
id|ice1712_t
op_star
id|ice
comma
r_int
r_int
id|data
)paren
suffix:semicolon
DECL|member|set_dir
r_void
(paren
op_star
id|set_dir
)paren
(paren
id|ice1712_t
op_star
id|ice
comma
r_int
r_int
id|data
)paren
suffix:semicolon
DECL|member|set_data
r_void
(paren
op_star
id|set_data
)paren
(paren
id|ice1712_t
op_star
id|ice
comma
r_int
r_int
id|data
)paren
suffix:semicolon
DECL|member|get_data
r_int
r_int
(paren
op_star
id|get_data
)paren
(paren
id|ice1712_t
op_star
id|ice
)paren
suffix:semicolon
multiline_comment|/* misc operators - move to another place? */
DECL|member|set_pro_rate
r_void
(paren
op_star
id|set_pro_rate
)paren
(paren
id|ice1712_t
op_star
id|ice
comma
r_int
r_int
id|rate
)paren
suffix:semicolon
DECL|member|gpio
)brace
id|gpio
suffix:semicolon
DECL|member|gpio_mutex
r_struct
id|semaphore
id|gpio_mutex
suffix:semicolon
multiline_comment|/* other board-specific data */
r_union
(brace
multiline_comment|/* additional i2c devices for EWS boards*/
DECL|member|i2cdevs
id|snd_i2c_device_t
op_star
id|i2cdevs
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* AC97 register cache for Aureon */
DECL|struct|aureon_spec
r_struct
id|aureon_spec
(brace
DECL|member|stac9744
r_int
r_int
id|stac9744
(braket
l_int|64
)braket
suffix:semicolon
DECL|member|cs8415_mux
r_int
r_int
id|cs8415_mux
suffix:semicolon
DECL|member|master
r_int
r_int
id|master
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|vol
r_int
r_int
id|vol
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|aureon
)brace
id|aureon
suffix:semicolon
multiline_comment|/* Hoontech-specific setting */
DECL|struct|hoontech_spec
r_struct
id|hoontech_spec
(brace
DECL|member|boxbits
r_int
r_char
id|boxbits
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|config
r_int
r_int
id|config
suffix:semicolon
DECL|member|boxconfig
r_int
r_int
id|boxconfig
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|hoontech
)brace
id|hoontech
suffix:semicolon
DECL|member|spec
)brace
id|spec
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * gpio access functions&n; */
DECL|function|snd_ice1712_gpio_set_dir
r_static
r_inline
r_void
id|snd_ice1712_gpio_set_dir
c_func
(paren
id|ice1712_t
op_star
id|ice
comma
r_int
r_int
id|bits
)paren
(brace
id|ice-&gt;gpio
dot
id|set_dir
c_func
(paren
id|ice
comma
id|bits
)paren
suffix:semicolon
)brace
DECL|function|snd_ice1712_gpio_set_mask
r_static
r_inline
r_void
id|snd_ice1712_gpio_set_mask
c_func
(paren
id|ice1712_t
op_star
id|ice
comma
r_int
r_int
id|bits
)paren
(brace
id|ice-&gt;gpio
dot
id|set_mask
c_func
(paren
id|ice
comma
id|bits
)paren
suffix:semicolon
)brace
DECL|function|snd_ice1712_gpio_write
r_static
r_inline
r_void
id|snd_ice1712_gpio_write
c_func
(paren
id|ice1712_t
op_star
id|ice
comma
r_int
r_int
id|val
)paren
(brace
id|ice-&gt;gpio
dot
id|set_data
c_func
(paren
id|ice
comma
id|val
)paren
suffix:semicolon
)brace
DECL|function|snd_ice1712_gpio_read
r_static
r_inline
r_int
r_int
id|snd_ice1712_gpio_read
c_func
(paren
id|ice1712_t
op_star
id|ice
)paren
(brace
r_return
id|ice-&gt;gpio
dot
id|get_data
c_func
(paren
id|ice
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * save and restore gpio status&n; * The access to gpio will be protected by mutex, so don&squot;t forget to&n; * restore!&n; */
DECL|function|snd_ice1712_save_gpio_status
r_static
r_inline
r_void
id|snd_ice1712_save_gpio_status
c_func
(paren
id|ice1712_t
op_star
id|ice
)paren
(brace
id|down
c_func
(paren
op_amp
id|ice-&gt;gpio_mutex
)paren
suffix:semicolon
id|ice-&gt;gpio.saved
(braket
l_int|0
)braket
op_assign
id|ice-&gt;gpio.direction
suffix:semicolon
id|ice-&gt;gpio.saved
(braket
l_int|1
)braket
op_assign
id|ice-&gt;gpio.write_mask
suffix:semicolon
)brace
DECL|function|snd_ice1712_restore_gpio_status
r_static
r_inline
r_void
id|snd_ice1712_restore_gpio_status
c_func
(paren
id|ice1712_t
op_star
id|ice
)paren
(brace
id|ice-&gt;gpio
dot
id|set_dir
c_func
(paren
id|ice
comma
id|ice-&gt;gpio.saved
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|ice-&gt;gpio
dot
id|set_mask
c_func
(paren
id|ice
comma
id|ice-&gt;gpio.saved
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|ice-&gt;gpio.direction
op_assign
id|ice-&gt;gpio.saved
(braket
l_int|0
)braket
suffix:semicolon
id|ice-&gt;gpio.write_mask
op_assign
id|ice-&gt;gpio.saved
(braket
l_int|1
)braket
suffix:semicolon
id|up
c_func
(paren
op_amp
id|ice-&gt;gpio_mutex
)paren
suffix:semicolon
)brace
multiline_comment|/* for bit controls */
DECL|macro|ICE1712_GPIO
mdefine_line|#define ICE1712_GPIO(xiface, xname, xindex, mask, invert, xaccess) &bslash;&n;{ .iface = xiface, .name = xname, .access = xaccess, .info = snd_ice1712_gpio_info, &bslash;&n;  .get = snd_ice1712_gpio_get, .put = snd_ice1712_gpio_put, &bslash;&n;  .private_value = mask | (invert &lt;&lt; 24) }
r_int
id|snd_ice1712_gpio_info
c_func
(paren
id|snd_kcontrol_t
op_star
id|kcontrol
comma
id|snd_ctl_elem_info_t
op_star
id|uinfo
)paren
suffix:semicolon
r_int
id|snd_ice1712_gpio_get
c_func
(paren
id|snd_kcontrol_t
op_star
id|kcontrol
comma
id|snd_ctl_elem_value_t
op_star
id|ucontrol
)paren
suffix:semicolon
r_int
id|snd_ice1712_gpio_put
c_func
(paren
id|snd_kcontrol_t
op_star
id|kcontrol
comma
id|snd_ctl_elem_value_t
op_star
id|ucontrol
)paren
suffix:semicolon
multiline_comment|/*&n; * set gpio direction, write mask and data&n; */
DECL|function|snd_ice1712_gpio_write_bits
r_static
r_inline
r_void
id|snd_ice1712_gpio_write_bits
c_func
(paren
id|ice1712_t
op_star
id|ice
comma
r_int
r_int
id|mask
comma
r_int
r_int
id|bits
)paren
(brace
id|ice-&gt;gpio.direction
op_or_assign
id|mask
suffix:semicolon
id|snd_ice1712_gpio_set_dir
c_func
(paren
id|ice
comma
id|ice-&gt;gpio.direction
)paren
suffix:semicolon
id|snd_ice1712_gpio_set_mask
c_func
(paren
id|ice
comma
op_complement
id|mask
)paren
suffix:semicolon
id|snd_ice1712_gpio_write
c_func
(paren
id|ice
comma
id|mask
op_amp
id|bits
)paren
suffix:semicolon
)brace
r_int
id|snd_ice1712_spdif_build_controls
c_func
(paren
id|ice1712_t
op_star
id|ice
)paren
suffix:semicolon
r_int
id|snd_ice1712_akm4xxx_init
c_func
(paren
id|akm4xxx_t
op_star
id|ak
comma
r_const
id|akm4xxx_t
op_star
r_template
comma
r_const
r_struct
id|snd_ak4xxx_private
op_star
id|priv
comma
id|ice1712_t
op_star
id|ice
)paren
suffix:semicolon
r_void
id|snd_ice1712_akm4xxx_free
c_func
(paren
id|ice1712_t
op_star
id|ice
)paren
suffix:semicolon
r_int
id|snd_ice1712_akm4xxx_build_controls
c_func
(paren
id|ice1712_t
op_star
id|ice
)paren
suffix:semicolon
r_int
id|snd_ice1712_init_cs8427
c_func
(paren
id|ice1712_t
op_star
id|ice
comma
r_int
id|addr
)paren
suffix:semicolon
DECL|function|snd_ice1712_write
r_static
r_inline
r_void
id|snd_ice1712_write
c_func
(paren
id|ice1712_t
op_star
id|ice
comma
id|u8
id|addr
comma
id|u8
id|data
)paren
(brace
id|outb
c_func
(paren
id|addr
comma
id|ICEREG
c_func
(paren
id|ice
comma
id|INDEX
)paren
)paren
suffix:semicolon
id|outb
c_func
(paren
id|data
comma
id|ICEREG
c_func
(paren
id|ice
comma
id|DATA
)paren
)paren
suffix:semicolon
)brace
DECL|function|snd_ice1712_read
r_static
r_inline
id|u8
id|snd_ice1712_read
c_func
(paren
id|ice1712_t
op_star
id|ice
comma
id|u8
id|addr
)paren
(brace
id|outb
c_func
(paren
id|addr
comma
id|ICEREG
c_func
(paren
id|ice
comma
id|INDEX
)paren
)paren
suffix:semicolon
r_return
id|inb
c_func
(paren
id|ICEREG
c_func
(paren
id|ice
comma
id|DATA
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * entry pointer&n; */
DECL|struct|snd_ice1712_card_info
r_struct
id|snd_ice1712_card_info
(brace
DECL|member|subvendor
r_int
r_int
id|subvendor
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|model
r_char
op_star
id|model
suffix:semicolon
DECL|member|driver
r_char
op_star
id|driver
suffix:semicolon
DECL|member|chip_init
r_int
(paren
op_star
id|chip_init
)paren
(paren
id|ice1712_t
op_star
)paren
suffix:semicolon
DECL|member|build_controls
r_int
(paren
op_star
id|build_controls
)paren
(paren
id|ice1712_t
op_star
)paren
suffix:semicolon
DECL|member|no_mpu401
r_int
id|no_mpu401
suffix:colon
l_int|1
suffix:semicolon
DECL|member|eeprom_size
r_int
r_int
id|eeprom_size
suffix:semicolon
DECL|member|eeprom_data
r_int
r_char
op_star
id|eeprom_data
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* __SOUND_ICE1712_H */
eof
