multiline_comment|/*&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU Library General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.&n; */
macro_line|#ifndef __SOUND_AU88X0_H
DECL|macro|__SOUND_AU88X0_H
mdefine_line|#define __SOUND_AU88X0_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/pcm.h&gt;
macro_line|#include &lt;sound/rawmidi.h&gt;
macro_line|#include &lt;sound/mpu401.h&gt;
macro_line|#include &lt;sound/hwdep.h&gt;
macro_line|#include &lt;sound/ac97_codec.h&gt;
macro_line|#endif
macro_line|#ifndef CHIP_AU8820
macro_line|#include &quot;au88x0_eq.h&quot;
macro_line|#include &quot;au88x0_a3d.h&quot;
macro_line|#endif
macro_line|#ifndef CHIP_AU8810
macro_line|#include &quot;au88x0_wt.h&quot;
macro_line|#endif
DECL|macro|VORTEX_DMA_MASK
mdefine_line|#define&t;VORTEX_DMA_MASK&t;0xffffffff
DECL|macro|hwread
mdefine_line|#define&t;hwread(x,y) readl((x)+((y)&gt;&gt;2))
DECL|macro|hwwrite
mdefine_line|#define&t;hwwrite(x,y,z) writel((z),(x)+((y)&gt;&gt;2))
multiline_comment|/* Vortex MPU401 defines. */
DECL|macro|MIDI_CLOCK_DIV
mdefine_line|#define&t;MIDI_CLOCK_DIV&t;&t;0x61
multiline_comment|/* Standart MPU401 defines. */
DECL|macro|MPU401_RESET
mdefine_line|#define&t;MPU401_RESET&t;&t;0xff
DECL|macro|MPU401_ENTER_UART
mdefine_line|#define&t;MPU401_ENTER_UART&t;0x3f
DECL|macro|MPU401_ACK
mdefine_line|#define&t;MPU401_ACK&t;&t;0xfe
singleline_comment|// Get src register value to convert from x to y.
DECL|macro|SRC_RATIO
mdefine_line|#define&t;SRC_RATIO(x,y)&t;&t;((((x&lt;&lt;15)/y) + 1)/2)
multiline_comment|/* FIFO software state constants. */
DECL|macro|FIFO_STOP
mdefine_line|#define FIFO_STOP 0
DECL|macro|FIFO_START
mdefine_line|#define FIFO_START 1
DECL|macro|FIFO_PAUSE
mdefine_line|#define FIFO_PAUSE 2
multiline_comment|/* IRQ flags */
DECL|macro|IRQ_ERR_MASK
mdefine_line|#define IRQ_ERR_MASK&t;0x00ff
DECL|macro|IRQ_FATAL
mdefine_line|#define IRQ_FATAL&t;0x0001
DECL|macro|IRQ_PARITY
mdefine_line|#define IRQ_PARITY&t;0x0002
DECL|macro|IRQ_REG
mdefine_line|#define IRQ_REG&t;&t;0x0004
DECL|macro|IRQ_FIFO
mdefine_line|#define IRQ_FIFO&t;0x0008
DECL|macro|IRQ_DMA
mdefine_line|#define IRQ_DMA&t;&t;0x0010
DECL|macro|IRQ_PCMOUT
mdefine_line|#define IRQ_PCMOUT&t;0x0020&t;/* PCM OUT page crossing */
DECL|macro|IRQ_TIMER
mdefine_line|#define IRQ_TIMER&t;0x1000
DECL|macro|IRQ_MIDI
mdefine_line|#define IRQ_MIDI&t;0x2000
DECL|macro|IRQ_MODEM
mdefine_line|#define IRQ_MODEM&t;0x4000
multiline_comment|/* ADB Resource */
DECL|macro|VORTEX_RESOURCE_DMA
mdefine_line|#define VORTEX_RESOURCE_DMA&t;0x00000000
DECL|macro|VORTEX_RESOURCE_SRC
mdefine_line|#define VORTEX_RESOURCE_SRC&t;0x00000001
DECL|macro|VORTEX_RESOURCE_MIXIN
mdefine_line|#define VORTEX_RESOURCE_MIXIN&t;0x00000002
DECL|macro|VORTEX_RESOURCE_MIXOUT
mdefine_line|#define VORTEX_RESOURCE_MIXOUT&t;0x00000003
DECL|macro|VORTEX_RESOURCE_A3D
mdefine_line|#define VORTEX_RESOURCE_A3D&t;0x00000004
DECL|macro|VORTEX_RESOURCE_LAST
mdefine_line|#define VORTEX_RESOURCE_LAST&t;0x00000005
multiline_comment|/* Check for SDAC bit in &quot;Extended audio ID&quot; AC97 register */
DECL|macro|VORTEX_IS_QUAD
mdefine_line|#define VORTEX_IS_QUAD(x) ((x-&gt;codec == NULL) ?  0 : (x-&gt;codec-&gt;ext_id&amp;0x80))
multiline_comment|/* Check if chip has bug. */
DECL|macro|IS_BAD_CHIP
mdefine_line|#define IS_BAD_CHIP(x) (&bslash;&n;&t;(x-&gt;rev == 0xfe &amp;&amp; x-&gt;device == PCI_DEVICE_ID_AUREAL_VORTEX_2) || &bslash;&n;&t;(x-&gt;rev == 0xfe &amp;&amp; x-&gt;device == PCI_DEVICE_ID_AUREAL_ADVANTAGE))
multiline_comment|/* PCM devices */
DECL|macro|VORTEX_PCM_ADB
mdefine_line|#define VORTEX_PCM_ADB&t;&t;0
DECL|macro|VORTEX_PCM_SPDIF
mdefine_line|#define VORTEX_PCM_SPDIF&t;1
DECL|macro|VORTEX_PCM_A3D
mdefine_line|#define VORTEX_PCM_A3D&t;&t;2
DECL|macro|VORTEX_PCM_WT
mdefine_line|#define VORTEX_PCM_WT&t;&t;3
DECL|macro|VORTEX_PCM_I2S
mdefine_line|#define VORTEX_PCM_I2S&t;&t;4
DECL|macro|VORTEX_PCM_LAST
mdefine_line|#define VORTEX_PCM_LAST&t;&t;5
DECL|macro|MIX_CAPT
mdefine_line|#define MIX_CAPT(x) (vortex-&gt;mixcapt[x])
DECL|macro|MIX_PLAYB
mdefine_line|#define MIX_PLAYB(x) (vortex-&gt;mixplayb[x])
DECL|macro|MIX_SPDIF
mdefine_line|#define MIX_SPDIF(x) (vortex-&gt;mixspdif[x])
DECL|macro|NR_WTPB
mdefine_line|#define NR_WTPB 0x20&t;&t;/* WT channels per eahc bank. */
multiline_comment|/* Structs */
r_typedef
r_struct
(brace
singleline_comment|//int this_08;          /* Still unknown */
DECL|member|fifo_enabled
r_int
id|fifo_enabled
suffix:semicolon
multiline_comment|/* this_24 */
DECL|member|fifo_status
r_int
id|fifo_status
suffix:semicolon
multiline_comment|/* this_1c */
DECL|member|dma_ctrl
r_int
id|dma_ctrl
suffix:semicolon
multiline_comment|/* this_78 (ADB), this_7c (WT) */
DECL|member|dma_unknown
r_int
id|dma_unknown
suffix:semicolon
multiline_comment|/* this_74 (ADB), this_78 (WT). WDM: +8 */
DECL|member|cfg0
r_int
id|cfg0
suffix:semicolon
DECL|member|cfg1
r_int
id|cfg1
suffix:semicolon
DECL|member|nr_ch
r_int
id|nr_ch
suffix:semicolon
multiline_comment|/* Nr of PCM channels in use */
DECL|member|type
r_int
id|type
suffix:semicolon
multiline_comment|/* Output type (ac97, a3d, spdif, i2s, dsp) */
DECL|member|dma
r_int
id|dma
suffix:semicolon
multiline_comment|/* Hardware DMA index. */
DECL|member|dir
r_int
id|dir
suffix:semicolon
multiline_comment|/* Stream Direction. */
DECL|member|resources
id|u32
id|resources
(braket
l_int|5
)braket
suffix:semicolon
multiline_comment|/* Virtual page extender stuff */
DECL|member|nr_periods
r_int
id|nr_periods
suffix:semicolon
DECL|member|period_bytes
r_int
id|period_bytes
suffix:semicolon
DECL|member|sgbuf
id|snd_pcm_sgbuf_t
op_star
id|sgbuf
suffix:semicolon
multiline_comment|/* DMA Scatter Gather struct */
DECL|member|period_real
r_int
id|period_real
suffix:semicolon
DECL|member|period_virt
r_int
id|period_virt
suffix:semicolon
DECL|member|substream
id|snd_pcm_substream_t
op_star
id|substream
suffix:semicolon
DECL|typedef|stream_t
)brace
id|stream_t
suffix:semicolon
DECL|typedef|vortex_t
r_typedef
r_struct
id|snd_vortex
id|vortex_t
suffix:semicolon
DECL|struct|snd_vortex
r_struct
id|snd_vortex
(brace
multiline_comment|/* ALSA structs. */
DECL|member|card
id|snd_card_t
op_star
id|card
suffix:semicolon
DECL|member|pcm
id|snd_pcm_t
op_star
id|pcm
(braket
id|VORTEX_PCM_LAST
)braket
suffix:semicolon
DECL|member|rmidi
id|snd_rawmidi_t
op_star
id|rmidi
suffix:semicolon
multiline_comment|/* Legacy Midi interface. */
DECL|member|codec
id|ac97_t
op_star
id|codec
suffix:semicolon
multiline_comment|/* Stream structs. */
DECL|member|dma_adb
id|stream_t
id|dma_adb
(braket
id|NR_ADB
)braket
suffix:semicolon
DECL|member|spdif_sr
r_int
id|spdif_sr
suffix:semicolon
macro_line|#ifndef CHIP_AU8810
DECL|member|dma_wt
id|stream_t
id|dma_wt
(braket
id|NR_WT
)braket
suffix:semicolon
DECL|member|wt_voice
id|wt_voice_t
id|wt_voice
(braket
id|NR_WT
)braket
suffix:semicolon
multiline_comment|/* WT register cache. */
DECL|member|mixwt
r_char
id|mixwt
(braket
(paren
id|NR_WT
op_div
id|NR_WTPB
)paren
op_star
l_int|6
)braket
suffix:semicolon
multiline_comment|/* WT mixin objects */
macro_line|#endif
multiline_comment|/* Global resources */
DECL|member|mixcapt
id|s8
id|mixcapt
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|mixplayb
id|s8
id|mixplayb
(braket
l_int|4
)braket
suffix:semicolon
macro_line|#ifndef CHIP_AU8820
DECL|member|mixspdif
id|s8
id|mixspdif
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|mixa3d
id|s8
id|mixa3d
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* mixers which collect all a3d streams. */
DECL|member|mixxtlk
id|s8
id|mixxtlk
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* crosstalk canceler mixer inputs. */
macro_line|#endif
DECL|member|fixed_res
id|u32
id|fixed_res
(braket
l_int|5
)braket
suffix:semicolon
macro_line|#ifndef CHIP_AU8820
multiline_comment|/* Hardware equalizer structs */
DECL|member|eq
id|eqlzr_t
id|eq
suffix:semicolon
multiline_comment|/* A3D structs */
DECL|member|a3d
id|a3dsrc_t
id|a3d
(braket
id|NR_A3D
)braket
suffix:semicolon
multiline_comment|/* Xtalk canceler */
DECL|member|xt_mode
r_int
id|xt_mode
suffix:semicolon
multiline_comment|/* 1: speakers, 0:headphones. */
macro_line|#endif
multiline_comment|/* Gameport stuff. */
DECL|member|gameport
r_struct
id|gameport
op_star
id|gameport
suffix:semicolon
multiline_comment|/* PCI hardware resources */
DECL|member|io
r_int
r_int
id|io
suffix:semicolon
DECL|member|mmio
r_int
r_int
op_star
id|mmio
suffix:semicolon
DECL|member|irq
r_int
r_int
id|irq
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
multiline_comment|/* PCI device */
DECL|member|pci_dev
r_struct
id|pci_dev
op_star
id|pci_dev
suffix:semicolon
DECL|member|vendor
id|u16
id|vendor
suffix:semicolon
DECL|member|device
id|u16
id|device
suffix:semicolon
DECL|member|rev
id|u8
id|rev
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Functions. */
multiline_comment|/* SRC */
r_static
r_void
id|vortex_adb_setsrc
c_func
(paren
id|vortex_t
op_star
id|vortex
comma
r_int
id|adbdma
comma
r_int
r_int
id|cvrt
comma
r_int
id|dir
)paren
suffix:semicolon
multiline_comment|/* DMA Engines. */
r_static
r_void
id|vortex_adbdma_setbuffers
c_func
(paren
id|vortex_t
op_star
id|vortex
comma
r_int
id|adbdma
comma
id|snd_pcm_sgbuf_t
op_star
id|sgbuf
comma
r_int
id|size
comma
r_int
id|count
)paren
suffix:semicolon
r_static
r_void
id|vortex_adbdma_setmode
c_func
(paren
id|vortex_t
op_star
id|vortex
comma
r_int
id|adbdma
comma
r_int
id|ie
comma
r_int
id|dir
comma
r_int
id|fmt
comma
r_int
id|d
comma
r_int
r_int
id|offset
)paren
suffix:semicolon
r_static
r_void
id|vortex_adbdma_setstartbuffer
c_func
(paren
id|vortex_t
op_star
id|vortex
comma
r_int
id|adbdma
comma
r_int
id|sb
)paren
suffix:semicolon
macro_line|#ifndef CHIP_AU8810
r_static
r_void
id|vortex_wtdma_setbuffers
c_func
(paren
id|vortex_t
op_star
id|vortex
comma
r_int
id|wtdma
comma
id|snd_pcm_sgbuf_t
op_star
id|sgbuf
comma
r_int
id|size
comma
r_int
id|count
)paren
suffix:semicolon
r_static
r_void
id|vortex_wtdma_setmode
c_func
(paren
id|vortex_t
op_star
id|vortex
comma
r_int
id|wtdma
comma
r_int
id|ie
comma
r_int
id|fmt
comma
r_int
id|d
comma
multiline_comment|/*int e, */
r_int
r_int
id|offset
)paren
suffix:semicolon
r_static
r_void
id|vortex_wtdma_setstartbuffer
c_func
(paren
id|vortex_t
op_star
id|vortex
comma
r_int
id|wtdma
comma
r_int
id|sb
)paren
suffix:semicolon
macro_line|#endif
r_static
r_void
id|vortex_adbdma_startfifo
c_func
(paren
id|vortex_t
op_star
id|vortex
comma
r_int
id|adbdma
)paren
suffix:semicolon
singleline_comment|//static void vortex_adbdma_stopfifo(vortex_t *vortex, int adbdma);
r_static
r_void
id|vortex_adbdma_pausefifo
c_func
(paren
id|vortex_t
op_star
id|vortex
comma
r_int
id|adbdma
)paren
suffix:semicolon
r_static
r_void
id|vortex_adbdma_resumefifo
c_func
(paren
id|vortex_t
op_star
id|vortex
comma
r_int
id|adbdma
)paren
suffix:semicolon
r_static
r_int
r_inline
id|vortex_adbdma_getlinearpos
c_func
(paren
id|vortex_t
op_star
id|vortex
comma
r_int
id|adbdma
)paren
suffix:semicolon
macro_line|#ifndef CHIP_AU8810
r_static
r_void
id|vortex_wtdma_startfifo
c_func
(paren
id|vortex_t
op_star
id|vortex
comma
r_int
id|wtdma
)paren
suffix:semicolon
r_static
r_void
id|vortex_wtdma_stopfifo
c_func
(paren
id|vortex_t
op_star
id|vortex
comma
r_int
id|wtdma
)paren
suffix:semicolon
r_static
r_void
id|vortex_wtdma_pausefifo
c_func
(paren
id|vortex_t
op_star
id|vortex
comma
r_int
id|wtdma
)paren
suffix:semicolon
r_static
r_void
id|vortex_wtdma_resumefifo
c_func
(paren
id|vortex_t
op_star
id|vortex
comma
r_int
id|wtdma
)paren
suffix:semicolon
r_static
r_int
r_inline
id|vortex_wtdma_getlinearpos
c_func
(paren
id|vortex_t
op_star
id|vortex
comma
r_int
id|wtdma
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* global stuff. */
r_static
r_void
id|vortex_codec_init
c_func
(paren
id|vortex_t
op_star
id|vortex
)paren
suffix:semicolon
r_static
r_void
id|vortex_codec_write
c_func
(paren
id|ac97_t
op_star
id|codec
comma
r_int
r_int
id|addr
comma
r_int
r_int
id|data
)paren
suffix:semicolon
r_static
r_int
r_int
id|vortex_codec_read
c_func
(paren
id|ac97_t
op_star
id|codec
comma
r_int
r_int
id|addr
)paren
suffix:semicolon
r_static
r_void
id|vortex_spdif_init
c_func
(paren
id|vortex_t
op_star
id|vortex
comma
r_int
id|spdif_sr
comma
r_int
id|spdif_mode
)paren
suffix:semicolon
r_static
r_int
id|vortex_core_init
c_func
(paren
id|vortex_t
op_star
id|card
)paren
suffix:semicolon
r_static
r_int
id|vortex_core_shutdown
c_func
(paren
id|vortex_t
op_star
id|card
)paren
suffix:semicolon
r_static
r_void
id|vortex_enable_int
c_func
(paren
id|vortex_t
op_star
id|card
)paren
suffix:semicolon
r_static
id|irqreturn_t
id|vortex_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_static
r_int
id|vortex_alsafmt_aspfmt
c_func
(paren
r_int
id|alsafmt
)paren
suffix:semicolon
multiline_comment|/* Connection  stuff. */
r_static
r_void
id|vortex_connect_default
c_func
(paren
id|vortex_t
op_star
id|vortex
comma
r_int
id|en
)paren
suffix:semicolon
r_static
r_int
id|vortex_adb_allocroute
c_func
(paren
id|vortex_t
op_star
id|vortex
comma
r_int
id|dma
comma
r_int
id|nr_ch
comma
r_int
id|dir
comma
r_int
id|type
)paren
suffix:semicolon
r_static
r_char
id|vortex_adb_checkinout
c_func
(paren
id|vortex_t
op_star
id|vortex
comma
r_int
id|resmap
(braket
)braket
comma
r_int
id|out
comma
r_int
id|restype
)paren
suffix:semicolon
macro_line|#ifndef CHIP_AU8810
r_static
r_int
id|vortex_wt_allocroute
c_func
(paren
id|vortex_t
op_star
id|vortex
comma
r_int
id|dma
comma
r_int
id|nr_ch
)paren
suffix:semicolon
r_static
r_void
id|vortex_wt_connect
c_func
(paren
id|vortex_t
op_star
id|vortex
comma
r_int
id|en
)paren
suffix:semicolon
r_static
r_void
id|vortex_wt_init
c_func
(paren
id|vortex_t
op_star
id|vortex
)paren
suffix:semicolon
macro_line|#endif
r_static
r_void
id|vortex_route
c_func
(paren
id|vortex_t
op_star
id|vortex
comma
r_int
id|en
comma
r_int
r_char
id|channel
comma
r_int
r_char
id|source
comma
r_int
r_char
id|dest
)paren
suffix:semicolon
macro_line|#if 0
r_static
r_void
id|vortex_routes
c_func
(paren
id|vortex_t
op_star
id|vortex
comma
r_int
id|en
comma
r_int
r_char
id|channel
comma
r_int
r_char
id|source
comma
r_int
r_char
id|dest0
comma
r_int
r_char
id|dest1
)paren
suffix:semicolon
macro_line|#endif
r_static
r_void
id|vortex_connection_mixin_mix
c_func
(paren
id|vortex_t
op_star
id|vortex
comma
r_int
id|en
comma
r_int
r_char
id|mixin
comma
r_int
r_char
id|mix
comma
r_int
id|a
)paren
suffix:semicolon
r_static
r_void
id|vortex_mix_setinputvolumebyte
c_func
(paren
id|vortex_t
op_star
id|vortex
comma
r_int
r_char
id|mix
comma
r_int
id|mixin
comma
r_int
r_char
id|vol
)paren
suffix:semicolon
r_static
r_void
id|vortex_mix_setvolumebyte
c_func
(paren
id|vortex_t
op_star
id|vortex
comma
r_int
r_char
id|mix
comma
r_int
r_char
id|vol
)paren
suffix:semicolon
multiline_comment|/* A3D functions. */
macro_line|#ifndef CHIP_AU8820
r_static
r_void
id|vortex_Vort3D
c_func
(paren
id|vortex_t
op_star
id|v
comma
r_int
id|en
)paren
suffix:semicolon
r_static
r_void
id|vortex_Vort3D_connect
c_func
(paren
id|vortex_t
op_star
id|vortex
comma
r_int
id|en
)paren
suffix:semicolon
r_static
r_void
id|vortex_Vort3D_InitializeSource
c_func
(paren
id|a3dsrc_t
op_star
id|a
comma
r_int
id|en
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Driver stuff. */
r_static
r_int
id|__devinit
id|vortex_gameport_register
c_func
(paren
id|vortex_t
op_star
id|card
)paren
suffix:semicolon
r_static
r_int
id|__devexit
id|vortex_gameport_unregister
c_func
(paren
id|vortex_t
op_star
id|card
)paren
suffix:semicolon
macro_line|#ifndef CHIP_AU8820
r_static
r_int
id|__devinit
id|vortex_eq_init
c_func
(paren
id|vortex_t
op_star
id|vortex
)paren
suffix:semicolon
r_static
r_int
id|__devexit
id|vortex_eq_free
c_func
(paren
id|vortex_t
op_star
id|vortex
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* ALSA stuff. */
r_static
r_int
id|__devinit
id|snd_vortex_new_pcm
c_func
(paren
id|vortex_t
op_star
id|vortex
comma
r_int
id|idx
comma
r_int
id|nr
)paren
suffix:semicolon
r_static
r_int
id|__devinit
id|snd_vortex_mixer
c_func
(paren
id|vortex_t
op_star
id|vortex
)paren
suffix:semicolon
r_static
r_int
id|__devinit
id|snd_vortex_midi
c_func
(paren
id|vortex_t
op_star
id|vortex
)paren
suffix:semicolon
macro_line|#endif
eof
