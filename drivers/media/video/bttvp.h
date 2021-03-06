multiline_comment|/*&n;    $Id: bttvp.h,v 1.17 2005/02/16 12:14:10 kraxel Exp $&n;&n;    bttv - Bt848 frame grabber driver&n;&n;    bttv&squot;s *private* header file  --  nobody other than bttv itself&n;    should ever include this file.&n;&n;    (c) 2000-2002 Gerd Knorr &lt;kraxel@bytesex.org&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
macro_line|#ifndef _BTTVP_H_
DECL|macro|_BTTVP_H_
mdefine_line|#define _BTTVP_H_
macro_line|#include &lt;linux/version.h&gt;
DECL|macro|BTTV_VERSION_CODE
mdefine_line|#define BTTV_VERSION_CODE KERNEL_VERSION(0,9,15)
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;linux/i2c-algo-bit.h&gt;
macro_line|#include &lt;linux/videodev.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/input.h&gt;
macro_line|#include &lt;asm/scatterlist.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;media/video-buf.h&gt;
macro_line|#include &lt;media/audiochip.h&gt;
macro_line|#include &lt;media/tuner.h&gt;
macro_line|#include &lt;media/tveeprom.h&gt;
macro_line|#include &lt;media/ir-common.h&gt;
macro_line|#include &quot;bt848.h&quot;
macro_line|#include &quot;bttv.h&quot;
macro_line|#include &quot;btcx-risc.h&quot;
macro_line|#ifdef __KERNEL__
DECL|macro|FORMAT_FLAGS_DITHER
mdefine_line|#define FORMAT_FLAGS_DITHER       0x01
DECL|macro|FORMAT_FLAGS_PACKED
mdefine_line|#define FORMAT_FLAGS_PACKED       0x02
DECL|macro|FORMAT_FLAGS_PLANAR
mdefine_line|#define FORMAT_FLAGS_PLANAR       0x04
DECL|macro|FORMAT_FLAGS_RAW
mdefine_line|#define FORMAT_FLAGS_RAW          0x08
DECL|macro|FORMAT_FLAGS_CrCb
mdefine_line|#define FORMAT_FLAGS_CrCb         0x10
DECL|macro|RISC_SLOT_O_VBI
mdefine_line|#define RISC_SLOT_O_VBI        4
DECL|macro|RISC_SLOT_O_FIELD
mdefine_line|#define RISC_SLOT_O_FIELD      6
DECL|macro|RISC_SLOT_E_VBI
mdefine_line|#define RISC_SLOT_E_VBI       10
DECL|macro|RISC_SLOT_E_FIELD
mdefine_line|#define RISC_SLOT_E_FIELD     12
DECL|macro|RISC_SLOT_LOOP
mdefine_line|#define RISC_SLOT_LOOP        14
DECL|macro|RESOURCE_OVERLAY
mdefine_line|#define RESOURCE_OVERLAY       1
DECL|macro|RESOURCE_VIDEO
mdefine_line|#define RESOURCE_VIDEO         2
DECL|macro|RESOURCE_VBI
mdefine_line|#define RESOURCE_VBI           4
DECL|macro|RAW_LINES
mdefine_line|#define RAW_LINES            640
DECL|macro|RAW_BPL
mdefine_line|#define RAW_BPL             1024
DECL|macro|UNSET
mdefine_line|#define UNSET (-1U)
multiline_comment|/* ---------------------------------------------------------- */
DECL|struct|bttv_tvnorm
r_struct
id|bttv_tvnorm
(brace
DECL|member|v4l2_id
r_int
id|v4l2_id
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|Fsc
id|u32
id|Fsc
suffix:semicolon
DECL|member|swidth
DECL|member|sheight
id|u16
id|swidth
comma
id|sheight
suffix:semicolon
multiline_comment|/* scaled standard width, height */
DECL|member|totalwidth
id|u16
id|totalwidth
suffix:semicolon
DECL|member|adelay
DECL|member|bdelay
DECL|member|iform
id|u8
id|adelay
comma
id|bdelay
comma
id|iform
suffix:semicolon
DECL|member|scaledtwidth
id|u32
id|scaledtwidth
suffix:semicolon
DECL|member|hdelayx1
DECL|member|hactivex1
id|u16
id|hdelayx1
comma
id|hactivex1
suffix:semicolon
DECL|member|vdelay
id|u16
id|vdelay
suffix:semicolon
DECL|member|vbipack
id|u8
id|vbipack
suffix:semicolon
DECL|member|vtotal
id|u16
id|vtotal
suffix:semicolon
DECL|member|sram
r_int
id|sram
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_const
r_struct
id|bttv_tvnorm
id|bttv_tvnorms
(braket
)braket
suffix:semicolon
DECL|struct|bttv_format
r_struct
id|bttv_format
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|palette
r_int
id|palette
suffix:semicolon
multiline_comment|/* video4linux 1      */
DECL|member|fourcc
r_int
id|fourcc
suffix:semicolon
multiline_comment|/* video4linux 2      */
DECL|member|btformat
r_int
id|btformat
suffix:semicolon
multiline_comment|/* BT848_COLOR_FMT_*  */
DECL|member|btswap
r_int
id|btswap
suffix:semicolon
multiline_comment|/* BT848_COLOR_CTL_*  */
DECL|member|depth
r_int
id|depth
suffix:semicolon
multiline_comment|/* bit/pixel          */
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|member|hshift
DECL|member|vshift
r_int
id|hshift
comma
id|vshift
suffix:semicolon
multiline_comment|/* for planar modes   */
)brace
suffix:semicolon
multiline_comment|/* ---------------------------------------------------------- */
DECL|struct|bttv_geometry
r_struct
id|bttv_geometry
(brace
DECL|member|vtc
DECL|member|crop
DECL|member|comb
id|u8
id|vtc
comma
id|crop
comma
id|comb
suffix:semicolon
DECL|member|width
DECL|member|hscale
DECL|member|hdelay
id|u16
id|width
comma
id|hscale
comma
id|hdelay
suffix:semicolon
DECL|member|sheight
DECL|member|vscale
DECL|member|vdelay
DECL|member|vtotal
id|u16
id|sheight
comma
id|vscale
comma
id|vdelay
comma
id|vtotal
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|bttv_buffer
r_struct
id|bttv_buffer
(brace
multiline_comment|/* common v4l buffer stuff -- must be first */
DECL|member|vb
r_struct
id|videobuf_buffer
id|vb
suffix:semicolon
multiline_comment|/* bttv specific */
DECL|member|fmt
r_const
r_struct
id|bttv_format
op_star
id|fmt
suffix:semicolon
DECL|member|tvnorm
r_int
id|tvnorm
suffix:semicolon
DECL|member|btformat
r_int
id|btformat
suffix:semicolon
DECL|member|btswap
r_int
id|btswap
suffix:semicolon
DECL|member|geo
r_struct
id|bttv_geometry
id|geo
suffix:semicolon
DECL|member|top
r_struct
id|btcx_riscmem
id|top
suffix:semicolon
DECL|member|bottom
r_struct
id|btcx_riscmem
id|bottom
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|bttv_buffer_set
r_struct
id|bttv_buffer_set
(brace
DECL|member|top
r_struct
id|bttv_buffer
op_star
id|top
suffix:semicolon
multiline_comment|/* top field buffer    */
DECL|member|bottom
r_struct
id|bttv_buffer
op_star
id|bottom
suffix:semicolon
multiline_comment|/* bottom field buffer */
DECL|member|top_irq
r_int
r_int
id|top_irq
suffix:semicolon
DECL|member|frame_irq
r_int
r_int
id|frame_irq
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|bttv_overlay
r_struct
id|bttv_overlay
(brace
DECL|member|tvnorm
r_int
id|tvnorm
suffix:semicolon
DECL|member|w
r_struct
id|v4l2_rect
id|w
suffix:semicolon
DECL|member|field
r_enum
id|v4l2_field
id|field
suffix:semicolon
DECL|member|clips
r_struct
id|v4l2_clip
op_star
id|clips
suffix:semicolon
DECL|member|nclips
r_int
id|nclips
suffix:semicolon
DECL|member|setup_ok
r_int
id|setup_ok
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|bttv_fh
r_struct
id|bttv_fh
(brace
DECL|member|btv
r_struct
id|bttv
op_star
id|btv
suffix:semicolon
DECL|member|resources
r_int
id|resources
suffix:semicolon
macro_line|#ifdef VIDIOC_G_PRIORITY
DECL|member|prio
r_enum
id|v4l2_priority
id|prio
suffix:semicolon
macro_line|#endif
DECL|member|type
r_enum
id|v4l2_buf_type
id|type
suffix:semicolon
multiline_comment|/* video capture */
DECL|member|cap
r_struct
id|videobuf_queue
id|cap
suffix:semicolon
DECL|member|fmt
r_const
r_struct
id|bttv_format
op_star
id|fmt
suffix:semicolon
DECL|member|width
r_int
id|width
suffix:semicolon
DECL|member|height
r_int
id|height
suffix:semicolon
multiline_comment|/* current settings */
DECL|member|ovfmt
r_const
r_struct
id|bttv_format
op_star
id|ovfmt
suffix:semicolon
DECL|member|ov
r_struct
id|bttv_overlay
id|ov
suffix:semicolon
multiline_comment|/* video overlay */
DECL|member|vbi
r_struct
id|videobuf_queue
id|vbi
suffix:semicolon
DECL|member|lines
r_int
id|lines
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* ---------------------------------------------------------- */
multiline_comment|/* bttv-risc.c                                                */
multiline_comment|/* risc code generators - capture */
r_int
id|bttv_risc_packed
c_func
(paren
r_struct
id|bttv
op_star
id|btv
comma
r_struct
id|btcx_riscmem
op_star
id|risc
comma
r_struct
id|scatterlist
op_star
id|sglist
comma
r_int
r_int
id|offset
comma
r_int
r_int
id|bpl
comma
r_int
r_int
id|pitch
comma
r_int
r_int
id|lines
)paren
suffix:semicolon
multiline_comment|/* control dma register + risc main loop */
r_void
id|bttv_set_dma
c_func
(paren
r_struct
id|bttv
op_star
id|btv
comma
r_int
id|override
)paren
suffix:semicolon
r_int
id|bttv_risc_init_main
c_func
(paren
r_struct
id|bttv
op_star
id|btv
)paren
suffix:semicolon
r_int
id|bttv_risc_hook
c_func
(paren
r_struct
id|bttv
op_star
id|btv
comma
r_int
id|slot
comma
r_struct
id|btcx_riscmem
op_star
id|risc
comma
r_int
id|irqflags
)paren
suffix:semicolon
multiline_comment|/* capture buffer handling */
r_int
id|bttv_buffer_risc
c_func
(paren
r_struct
id|bttv
op_star
id|btv
comma
r_struct
id|bttv_buffer
op_star
id|buf
)paren
suffix:semicolon
r_int
id|bttv_buffer_activate_video
c_func
(paren
r_struct
id|bttv
op_star
id|btv
comma
r_struct
id|bttv_buffer_set
op_star
id|set
)paren
suffix:semicolon
r_int
id|bttv_buffer_activate_vbi
c_func
(paren
r_struct
id|bttv
op_star
id|btv
comma
r_struct
id|bttv_buffer
op_star
id|vbi
)paren
suffix:semicolon
r_void
id|bttv_dma_free
c_func
(paren
r_struct
id|bttv
op_star
id|btv
comma
r_struct
id|bttv_buffer
op_star
id|buf
)paren
suffix:semicolon
multiline_comment|/* overlay handling */
r_int
id|bttv_overlay_risc
c_func
(paren
r_struct
id|bttv
op_star
id|btv
comma
r_struct
id|bttv_overlay
op_star
id|ov
comma
r_const
r_struct
id|bttv_format
op_star
id|fmt
comma
r_struct
id|bttv_buffer
op_star
id|buf
)paren
suffix:semicolon
multiline_comment|/* ---------------------------------------------------------- */
multiline_comment|/* bttv-vbi.c                                                 */
r_void
id|bttv_vbi_try_fmt
c_func
(paren
r_struct
id|bttv_fh
op_star
id|fh
comma
r_struct
id|v4l2_format
op_star
id|f
)paren
suffix:semicolon
r_void
id|bttv_vbi_get_fmt
c_func
(paren
r_struct
id|bttv_fh
op_star
id|fh
comma
r_struct
id|v4l2_format
op_star
id|f
)paren
suffix:semicolon
r_void
id|bttv_vbi_setlines
c_func
(paren
r_struct
id|bttv_fh
op_star
id|fh
comma
r_struct
id|bttv
op_star
id|btv
comma
r_int
id|lines
)paren
suffix:semicolon
r_extern
r_struct
id|videobuf_queue_ops
id|bttv_vbi_qops
suffix:semicolon
multiline_comment|/* ---------------------------------------------------------- */
multiline_comment|/* bttv-gpio.c */
r_extern
r_struct
id|bus_type
id|bttv_sub_bus_type
suffix:semicolon
r_int
id|bttv_sub_add_device
c_func
(paren
r_struct
id|bttv_core
op_star
id|core
comma
r_char
op_star
id|name
)paren
suffix:semicolon
r_int
id|bttv_sub_del_devices
c_func
(paren
r_struct
id|bttv_core
op_star
id|core
)paren
suffix:semicolon
r_void
id|bttv_gpio_irq
c_func
(paren
r_struct
id|bttv_core
op_star
id|core
)paren
suffix:semicolon
multiline_comment|/* ---------------------------------------------------------- */
multiline_comment|/* bttv-driver.c                                              */
multiline_comment|/* insmod options */
r_extern
r_int
r_int
id|bttv_verbose
suffix:semicolon
r_extern
r_int
r_int
id|bttv_debug
suffix:semicolon
r_extern
r_int
r_int
id|bttv_gpio
suffix:semicolon
r_extern
r_void
id|bttv_gpio_tracking
c_func
(paren
r_struct
id|bttv
op_star
id|btv
comma
r_char
op_star
id|comment
)paren
suffix:semicolon
r_extern
r_int
id|init_bttv_i2c
c_func
(paren
r_struct
id|bttv
op_star
id|btv
)paren
suffix:semicolon
r_extern
r_int
id|fini_bttv_i2c
c_func
(paren
r_struct
id|bttv
op_star
id|btv
)paren
suffix:semicolon
DECL|macro|vprintk
mdefine_line|#define vprintk  if (bttv_verbose) printk
DECL|macro|dprintk
mdefine_line|#define dprintk  if (bttv_debug &gt;= 1) printk
DECL|macro|d2printk
mdefine_line|#define d2printk if (bttv_debug &gt;= 2) printk
multiline_comment|/* our devices */
DECL|macro|BTTV_MAX
mdefine_line|#define BTTV_MAX 16
r_extern
r_int
r_int
id|bttv_num
suffix:semicolon
DECL|macro|BTTV_MAX_FBUF
mdefine_line|#define BTTV_MAX_FBUF   0x208000
DECL|macro|VBIBUF_SIZE
mdefine_line|#define VBIBUF_SIZE     (2048*VBI_MAXLINES*2)
DECL|macro|BTTV_TIMEOUT
mdefine_line|#define BTTV_TIMEOUT    (HZ/2) /* 0.5 seconds */
DECL|macro|BTTV_FREE_IDLE
mdefine_line|#define BTTV_FREE_IDLE  (HZ)   /* one second */
DECL|struct|bttv_pll_info
r_struct
id|bttv_pll_info
(brace
DECL|member|pll_ifreq
r_int
r_int
id|pll_ifreq
suffix:semicolon
multiline_comment|/* PLL input frequency        */
DECL|member|pll_ofreq
r_int
r_int
id|pll_ofreq
suffix:semicolon
multiline_comment|/* PLL output frequency       */
DECL|member|pll_crystal
r_int
r_int
id|pll_crystal
suffix:semicolon
multiline_comment|/* Crystal used for input     */
DECL|member|pll_current
r_int
r_int
id|pll_current
suffix:semicolon
multiline_comment|/* Currently programmed ofreq */
)brace
suffix:semicolon
multiline_comment|/* for gpio-connected remote control */
DECL|struct|bttv_input
r_struct
id|bttv_input
(brace
DECL|member|dev
r_struct
id|input_dev
id|dev
suffix:semicolon
DECL|member|ir
r_struct
id|ir_input_state
id|ir
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|phys
r_char
id|phys
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|mask_keycode
id|u32
id|mask_keycode
suffix:semicolon
DECL|member|mask_keydown
id|u32
id|mask_keydown
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|bttv_suspend_state
r_struct
id|bttv_suspend_state
(brace
DECL|member|gpio_enable
id|u32
id|gpio_enable
suffix:semicolon
DECL|member|gpio_data
id|u32
id|gpio_data
suffix:semicolon
DECL|member|disabled
r_int
id|disabled
suffix:semicolon
DECL|member|loop_irq
r_int
id|loop_irq
suffix:semicolon
DECL|member|video
r_struct
id|bttv_buffer_set
id|video
suffix:semicolon
DECL|member|vbi
r_struct
id|bttv_buffer
op_star
id|vbi
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|bttv
r_struct
id|bttv
(brace
DECL|member|c
r_struct
id|bttv_core
id|c
suffix:semicolon
multiline_comment|/* pci device config */
DECL|member|id
r_int
r_int
id|id
suffix:semicolon
DECL|member|revision
r_int
r_char
id|revision
suffix:semicolon
DECL|member|bt848_mmio
r_int
r_char
id|__iomem
op_star
id|bt848_mmio
suffix:semicolon
multiline_comment|/* pointer to mmio */
multiline_comment|/* card configuration info */
DECL|member|cardid
r_int
r_int
id|cardid
suffix:semicolon
multiline_comment|/* pci subsystem id (bt878 based ones) */
DECL|member|tuner_type
r_int
r_int
id|tuner_type
suffix:semicolon
multiline_comment|/* tuner chip type */
DECL|member|pinnacle_id
r_int
r_int
id|pinnacle_id
suffix:semicolon
DECL|member|svhs
r_int
r_int
id|svhs
suffix:semicolon
DECL|member|pll
r_struct
id|bttv_pll_info
id|pll
suffix:semicolon
DECL|member|triton1
r_int
id|triton1
suffix:semicolon
DECL|member|gpioirq
r_int
id|gpioirq
suffix:semicolon
DECL|member|use_i2c_hw
r_int
id|use_i2c_hw
suffix:semicolon
multiline_comment|/* old gpio interface */
DECL|member|gpioq
id|wait_queue_head_t
id|gpioq
suffix:semicolon
DECL|member|shutdown
r_int
id|shutdown
suffix:semicolon
DECL|member|audio_hook
r_void
(paren
op_star
id|audio_hook
)paren
(paren
r_struct
id|bttv
op_star
id|btv
comma
r_struct
id|video_audio
op_star
id|v
comma
r_int
id|set
)paren
suffix:semicolon
multiline_comment|/* new gpio interface */
DECL|member|gpio_lock
id|spinlock_t
id|gpio_lock
suffix:semicolon
multiline_comment|/* i2c layer */
DECL|member|i2c_algo
r_struct
id|i2c_algo_bit_data
id|i2c_algo
suffix:semicolon
DECL|member|i2c_client
r_struct
id|i2c_client
id|i2c_client
suffix:semicolon
DECL|member|i2c_state
DECL|member|i2c_rc
r_int
id|i2c_state
comma
id|i2c_rc
suffix:semicolon
DECL|member|i2c_done
r_int
id|i2c_done
suffix:semicolon
DECL|member|i2c_queue
id|wait_queue_head_t
id|i2c_queue
suffix:semicolon
multiline_comment|/* video4linux (1) */
DECL|member|video_dev
r_struct
id|video_device
op_star
id|video_dev
suffix:semicolon
DECL|member|radio_dev
r_struct
id|video_device
op_star
id|radio_dev
suffix:semicolon
DECL|member|vbi_dev
r_struct
id|video_device
op_star
id|vbi_dev
suffix:semicolon
multiline_comment|/* infrared remote */
DECL|member|has_remote
r_int
id|has_remote
suffix:semicolon
DECL|member|remote
r_struct
id|bttv_input
op_star
id|remote
suffix:semicolon
multiline_comment|/* locking */
DECL|member|s_lock
id|spinlock_t
id|s_lock
suffix:semicolon
DECL|member|lock
r_struct
id|semaphore
id|lock
suffix:semicolon
DECL|member|resources
r_int
id|resources
suffix:semicolon
DECL|member|reslock
r_struct
id|semaphore
id|reslock
suffix:semicolon
macro_line|#ifdef VIDIOC_G_PRIORITY
DECL|member|prio
r_struct
id|v4l2_prio_state
id|prio
suffix:semicolon
macro_line|#endif
multiline_comment|/* video state */
DECL|member|input
r_int
r_int
id|input
suffix:semicolon
DECL|member|audio
r_int
r_int
id|audio
suffix:semicolon
DECL|member|freq
r_int
r_int
id|freq
suffix:semicolon
DECL|member|tvnorm
DECL|member|hue
DECL|member|contrast
DECL|member|bright
DECL|member|saturation
r_int
id|tvnorm
comma
id|hue
comma
id|contrast
comma
id|bright
comma
id|saturation
suffix:semicolon
DECL|member|fbuf
r_struct
id|v4l2_framebuffer
id|fbuf
suffix:semicolon
DECL|member|field_count
r_int
r_int
id|field_count
suffix:semicolon
multiline_comment|/* various options */
DECL|member|opt_combfilter
r_int
id|opt_combfilter
suffix:semicolon
DECL|member|opt_lumafilter
r_int
id|opt_lumafilter
suffix:semicolon
DECL|member|opt_automute
r_int
id|opt_automute
suffix:semicolon
DECL|member|opt_chroma_agc
r_int
id|opt_chroma_agc
suffix:semicolon
DECL|member|opt_adc_crush
r_int
id|opt_adc_crush
suffix:semicolon
DECL|member|opt_vcr_hack
r_int
id|opt_vcr_hack
suffix:semicolon
DECL|member|opt_whitecrush_upper
r_int
id|opt_whitecrush_upper
suffix:semicolon
DECL|member|opt_whitecrush_lower
r_int
id|opt_whitecrush_lower
suffix:semicolon
multiline_comment|/* radio data/state */
DECL|member|has_radio
r_int
id|has_radio
suffix:semicolon
DECL|member|radio_user
r_int
id|radio_user
suffix:semicolon
multiline_comment|/* miro/pinnacle + Aimslab VHX&n;&t;   philips matchbox (tea5757 radio tuner) support */
DECL|member|has_matchbox
r_int
id|has_matchbox
suffix:semicolon
DECL|member|mbox_we
r_int
id|mbox_we
suffix:semicolon
DECL|member|mbox_data
r_int
id|mbox_data
suffix:semicolon
DECL|member|mbox_clk
r_int
id|mbox_clk
suffix:semicolon
DECL|member|mbox_most
r_int
id|mbox_most
suffix:semicolon
DECL|member|mbox_mask
r_int
id|mbox_mask
suffix:semicolon
multiline_comment|/* ISA stuff (Terratec Active Radio Upgrade) */
DECL|member|mbox_ior
r_int
id|mbox_ior
suffix:semicolon
DECL|member|mbox_iow
r_int
id|mbox_iow
suffix:semicolon
DECL|member|mbox_csel
r_int
id|mbox_csel
suffix:semicolon
multiline_comment|/* risc memory management data&n;&t;   - must aquire s_lock before changing these&n;&t;   - only the irq handler is supported to touch top + bottom + vcurr */
DECL|member|main
r_struct
id|btcx_riscmem
id|main
suffix:semicolon
DECL|member|screen
r_struct
id|bttv_buffer
op_star
id|screen
suffix:semicolon
multiline_comment|/* overlay             */
DECL|member|capture
r_struct
id|list_head
id|capture
suffix:semicolon
multiline_comment|/* video capture queue */
DECL|member|vcapture
r_struct
id|list_head
id|vcapture
suffix:semicolon
multiline_comment|/* vbi capture queue   */
DECL|member|curr
r_struct
id|bttv_buffer_set
id|curr
suffix:semicolon
multiline_comment|/* active buffers      */
DECL|member|cvbi
r_struct
id|bttv_buffer
op_star
id|cvbi
suffix:semicolon
multiline_comment|/* active vbi buffer   */
DECL|member|loop_irq
r_int
id|loop_irq
suffix:semicolon
DECL|member|new_input
r_int
id|new_input
suffix:semicolon
DECL|member|cap_ctl
r_int
r_int
id|cap_ctl
suffix:semicolon
DECL|member|dma_on
r_int
r_int
id|dma_on
suffix:semicolon
DECL|member|timeout
r_struct
id|timer_list
id|timeout
suffix:semicolon
DECL|member|state
r_struct
id|bttv_suspend_state
id|state
suffix:semicolon
multiline_comment|/* stats */
DECL|member|errors
r_int
r_int
id|errors
suffix:semicolon
DECL|member|framedrop
r_int
r_int
id|framedrop
suffix:semicolon
DECL|member|irq_total
r_int
r_int
id|irq_total
suffix:semicolon
DECL|member|irq_me
r_int
r_int
id|irq_me
suffix:semicolon
DECL|member|users
r_int
r_int
id|users
suffix:semicolon
DECL|member|init
r_struct
id|bttv_fh
id|init
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|bttv
id|bttvs
(braket
id|BTTV_MAX
)braket
suffix:semicolon
multiline_comment|/* private ioctls */
DECL|macro|BTTV_VERSION
mdefine_line|#define BTTV_VERSION            _IOR(&squot;v&squot; , BASE_VIDIOCPRIVATE+6, int)
DECL|macro|BTTV_VBISIZE
mdefine_line|#define BTTV_VBISIZE            _IOR(&squot;v&squot; , BASE_VIDIOCPRIVATE+8, int)
macro_line|#endif
DECL|macro|btwrite
mdefine_line|#define btwrite(dat,adr)    writel((dat), btv-&gt;bt848_mmio+(adr))
DECL|macro|btread
mdefine_line|#define btread(adr)         readl(btv-&gt;bt848_mmio+(adr))
DECL|macro|btand
mdefine_line|#define btand(dat,adr)      btwrite((dat) &amp; btread(adr), adr)
DECL|macro|btor
mdefine_line|#define btor(dat,adr)       btwrite((dat) | btread(adr), adr)
DECL|macro|btaor
mdefine_line|#define btaor(dat,mask,adr) btwrite((dat) | ((mask) &amp; btread(adr)), adr)
macro_line|#endif /* _BTTVP_H_ */
multiline_comment|/*&n; * Local variables:&n; * c-basic-offset: 8&n; * End:&n; */
eof
