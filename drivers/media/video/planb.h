multiline_comment|/* &n;    planb - PlanB frame grabber driver&n;&n;    PlanB is used in the 7x00/8x00 series of PowerMacintosh&n;    Computers as video input DMA controller.&n;&n;    Copyright (C) 1998 Michel Lanners (mlan@cpu.lu)&n;&n;    Based largely on the bttv driver by Ralph Metzler (rjkm@thp.uni-koeln.de)&n;&n;    Additional debugging and coding by Takashi Oe (toe@unlserve.unl.edu)&n;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
multiline_comment|/* $Id: planb.h,v 1.13 1999/05/03 19:28:56 mlan Exp $ */
macro_line|#ifndef _PLANB_H_
DECL|macro|_PLANB_H_
mdefine_line|#define _PLANB_H_
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;asm/dbdma.h&gt;
macro_line|#include &quot;saa7196.h&quot;
macro_line|#endif /* __KERNEL__ */
DECL|macro|PLANB_DEVICE_NAME
mdefine_line|#define PLANB_DEVICE_NAME&t;&quot;Apple PlanB Video-In&quot;
DECL|macro|PLANB_REV
mdefine_line|#define PLANB_REV&t;&t;&quot;1.0&quot;
macro_line|#ifdef __KERNEL__
singleline_comment|//#define PLANB_GSCANLINE&t;/* use this if apps have the notion of */
multiline_comment|/* grab buffer scanline */
multiline_comment|/* This should be safe for both PAL and NTSC */
DECL|macro|PLANB_MAXPIXELS
mdefine_line|#define PLANB_MAXPIXELS 768
DECL|macro|PLANB_MAXLINES
mdefine_line|#define PLANB_MAXLINES 576
DECL|macro|PLANB_NTSC_MAXLINES
mdefine_line|#define PLANB_NTSC_MAXLINES 480
multiline_comment|/* Uncomment your preferred norm ;-) */
DECL|macro|PLANB_DEF_NORM
mdefine_line|#define PLANB_DEF_NORM VIDEO_MODE_PAL
singleline_comment|//#define PLANB_DEF_NORM VIDEO_MODE_NTSC
singleline_comment|//#define PLANB_DEF_NORM VIDEO_MODE_SECAM
multiline_comment|/* fields settings */
DECL|macro|PLANB_GRAY
mdefine_line|#define PLANB_GRAY&t;0x1&t;/*  8-bit mono? */
DECL|macro|PLANB_COLOUR15
mdefine_line|#define PLANB_COLOUR15&t;0x2&t;/* 16-bit mode */
DECL|macro|PLANB_COLOUR32
mdefine_line|#define PLANB_COLOUR32&t;0x4&t;/* 32-bit mode */
DECL|macro|PLANB_CLIPMASK
mdefine_line|#define PLANB_CLIPMASK&t;0x8&t;/* hardware clipmasking */
multiline_comment|/* misc. flags for PlanB DMA operation */
DECL|macro|CH_SYNC
mdefine_line|#define&t;CH_SYNC&t;&t;0x1&t;/* synchronize channels (set by ch1;&n;&t;&t;&t;&t;   cleared by ch2) */
DECL|macro|FIELD_SYNC
mdefine_line|#define FIELD_SYNC&t;0x2     /* used for the start of each field&n;&t;&t;&t;&t;   (0 -&gt; 1 -&gt; 0 for ch1; 0 -&gt; 1 for ch2) */
DECL|macro|EVEN_FIELD
mdefine_line|#define EVEN_FIELD&t;0x0&t;/* even field is detected if unset */
DECL|macro|DMA_ABORT
mdefine_line|#define DMA_ABORT&t;0x2&t;/* error or just out of sync if set */
DECL|macro|ODD_FIELD
mdefine_line|#define ODD_FIELD&t;0x4&t;/* odd field is detected if set */
multiline_comment|/* for capture operations */
DECL|macro|MAX_GBUFFERS
mdefine_line|#define MAX_GBUFFERS&t;2
multiline_comment|/* note PLANB_MAX_FBUF must be divisible by PAGE_SIZE */
macro_line|#ifdef PLANB_GSCANLINE
DECL|macro|PLANB_MAX_FBUF
mdefine_line|#define PLANB_MAX_FBUF&t;0x240000&t;/* 576 * 1024 * 4 */
DECL|macro|TAB_FACTOR
mdefine_line|#define TAB_FACTOR&t;(1)
macro_line|#else
DECL|macro|PLANB_MAX_FBUF
mdefine_line|#define PLANB_MAX_FBUF&t;0x1b0000&t;/* 576 * 768 * 4 */
DECL|macro|TAB_FACTOR
mdefine_line|#define TAB_FACTOR&t;(2)
macro_line|#endif
macro_line|#endif /* __KERNEL__ */
DECL|struct|planb_saa_regs
r_struct
id|planb_saa_regs
(brace
DECL|member|addr
r_int
r_char
id|addr
suffix:semicolon
DECL|member|val
r_int
r_char
id|val
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|planb_stat_regs
r_struct
id|planb_stat_regs
(brace
DECL|member|ch1_stat
r_int
r_int
id|ch1_stat
suffix:semicolon
DECL|member|ch2_stat
r_int
r_int
id|ch2_stat
suffix:semicolon
DECL|member|saa_stat0
r_int
r_char
id|saa_stat0
suffix:semicolon
DECL|member|saa_stat1
r_int
r_char
id|saa_stat1
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|planb_any_regs
r_struct
id|planb_any_regs
(brace
DECL|member|offset
r_int
r_int
id|offset
suffix:semicolon
DECL|member|bytes
r_int
r_int
id|bytes
suffix:semicolon
DECL|member|data
r_int
r_char
id|data
(braket
l_int|128
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* planb private ioctls */
DECL|macro|PLANBIOCGSAAREGS
mdefine_line|#define PLANBIOCGSAAREGS&t;_IOWR(&squot;v&squot;, BASE_VIDIOCPRIVATE, struct planb_saa_regs)&t;/* Read a saa7196 reg value */
DECL|macro|PLANBIOCSSAAREGS
mdefine_line|#define PLANBIOCSSAAREGS&t;_IOW(&squot;v&squot;, BASE_VIDIOCPRIVATE + 1, struct planb_saa_regs)&t;/* Set a saa7196 reg value */
DECL|macro|PLANBIOCGSTAT
mdefine_line|#define PLANBIOCGSTAT&t;&t;_IOR(&squot;v&squot;, BASE_VIDIOCPRIVATE + 2, struct planb_stat_regs)&t;/* Read planb status */
DECL|macro|PLANB_TV_MODE
mdefine_line|#define PLANB_TV_MODE&t;&t;1
DECL|macro|PLANB_VTR_MODE
mdefine_line|#define PLANB_VTR_MODE&t;&t;2
DECL|macro|PLANBIOCGMODE
mdefine_line|#define PLANBIOCGMODE&t;&t;_IOR(&squot;v&squot;, BASE_VIDIOCPRIVATE + 3, int)&t;/* Get TV/VTR mode */
DECL|macro|PLANBIOCSMODE
mdefine_line|#define PLANBIOCSMODE&t;&t;_IOW(&squot;v&squot;, BASE_VIDIOCPRIVATE + 4, int)&t;/* Set TV/VTR mode */
macro_line|#ifdef PLANB_GSCANLINE
DECL|macro|PLANBG_GRAB_BPL
mdefine_line|#define PLANBG_GRAB_BPL&t;&t;_IOR(&squot;v&squot;, BASE_VIDIOCPRIVATE + 5, int)&t;/* # of bytes per scanline in grab buffer */
macro_line|#endif
multiline_comment|/* call wake_up_interruptible() with appropriate actions */
DECL|macro|PLANB_INTR_DEBUG
mdefine_line|#define PLANB_INTR_DEBUG&t;_IOW(&squot;v&squot;, BASE_VIDIOCPRIVATE + 20, int)
multiline_comment|/* investigate which reg does what */
DECL|macro|PLANB_INV_REGS
mdefine_line|#define PLANB_INV_REGS&t;&t;_IOWR(&squot;v&squot;, BASE_VIDIOCPRIVATE + 21, struct planb_any_regs)
macro_line|#ifdef __KERNEL__
multiline_comment|/* Potentially useful macros */
DECL|macro|PLANB_SET
mdefine_line|#define PLANB_SET(x)&t;((x) &lt;&lt; 16 | (x))
DECL|macro|PLANB_CLR
mdefine_line|#define PLANB_CLR(x)&t;((x) &lt;&lt; 16)
multiline_comment|/* This represents the physical register layout */
DECL|struct|planb_registers
r_struct
id|planb_registers
(brace
DECL|member|ch1
r_volatile
r_struct
id|dbdma_regs
id|ch1
suffix:semicolon
multiline_comment|/* 0x00: video in */
DECL|member|even
r_volatile
r_int
r_int
id|even
suffix:semicolon
multiline_comment|/* 0x40: even field setting */
DECL|member|odd
r_volatile
r_int
r_int
id|odd
suffix:semicolon
multiline_comment|/* 0x44; odd field setting */
DECL|member|pad1
r_int
r_int
id|pad1
(braket
l_int|14
)braket
suffix:semicolon
multiline_comment|/* empty? */
DECL|member|ch2
r_volatile
r_struct
id|dbdma_regs
id|ch2
suffix:semicolon
multiline_comment|/* 0x80: clipmask out */
DECL|member|pad2
r_int
r_int
id|pad2
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* 0xc0: empty? */
DECL|member|reg3
r_volatile
r_int
r_int
id|reg3
suffix:semicolon
multiline_comment|/* 0x100: ???? */
DECL|member|intr_stat
r_volatile
r_int
r_int
id|intr_stat
suffix:semicolon
multiline_comment|/* 0x104: irq status */
DECL|macro|PLANB_CLR_IRQ
mdefine_line|#define PLANB_CLR_IRQ&t;&t;0x00&t;&t;/* clear Plan B interrupt */
DECL|macro|PLANB_GEN_IRQ
mdefine_line|#define PLANB_GEN_IRQ&t;&t;0x01&t;&t;/* assert Plan B interrupt */
DECL|macro|PLANB_FRM_IRQ
mdefine_line|#define PLANB_FRM_IRQ&t;&t;0x0100&t;&t;/* end of frame */
DECL|member|pad3
r_int
r_int
id|pad3
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* empty? */
DECL|member|reg5
r_volatile
r_int
r_int
id|reg5
suffix:semicolon
multiline_comment|/* 0x10c: ??? */
DECL|member|pad4
r_int
r_int
id|pad4
(braket
l_int|60
)braket
suffix:semicolon
multiline_comment|/* empty? */
DECL|member|saa_addr
r_volatile
r_int
r_char
id|saa_addr
suffix:semicolon
multiline_comment|/* 0x200: SAA subadr */
DECL|member|pad5
r_char
id|pad5
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|saa_regval
r_volatile
r_int
r_char
id|saa_regval
suffix:semicolon
multiline_comment|/* SAA7196 write reg. val */
DECL|member|pad6
r_char
id|pad6
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|saa_status
r_volatile
r_int
r_char
id|saa_status
suffix:semicolon
multiline_comment|/* SAA7196 status byte */
multiline_comment|/* There is more unused stuff here */
)brace
suffix:semicolon
DECL|struct|planb_window
r_struct
id|planb_window
(brace
DECL|member|x
DECL|member|y
r_int
id|x
comma
id|y
suffix:semicolon
DECL|member|width
DECL|member|height
id|ushort
id|width
comma
id|height
suffix:semicolon
DECL|member|bpp
DECL|member|bpl
DECL|member|depth
DECL|member|pad
id|ushort
id|bpp
comma
id|bpl
comma
id|depth
comma
id|pad
suffix:semicolon
DECL|member|swidth
DECL|member|sheight
id|ushort
id|swidth
comma
id|sheight
suffix:semicolon
DECL|member|norm
r_int
id|norm
suffix:semicolon
DECL|member|interlace
r_int
id|interlace
suffix:semicolon
DECL|member|color_fmt
id|u32
id|color_fmt
suffix:semicolon
DECL|member|chromakey
r_int
id|chromakey
suffix:semicolon
DECL|member|mode
r_int
id|mode
suffix:semicolon
multiline_comment|/* used to switch between TV/VTR modes */
)brace
suffix:semicolon
DECL|struct|planb_suspend
r_struct
id|planb_suspend
(brace
DECL|member|overlay
r_int
id|overlay
suffix:semicolon
DECL|member|frame
r_int
id|frame
suffix:semicolon
DECL|member|cmd
r_struct
id|dbdma_cmd
id|cmd
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|planb
r_struct
id|planb
(brace
DECL|member|video_dev
r_struct
id|video_device
id|video_dev
suffix:semicolon
DECL|member|picture
r_struct
id|video_picture
id|picture
suffix:semicolon
multiline_comment|/* Current picture params */
DECL|member|audio_dev
r_struct
id|video_audio
id|audio_dev
suffix:semicolon
multiline_comment|/* Current audio params */
DECL|member|planb_base
r_volatile
r_struct
id|planb_registers
op_star
id|planb_base
suffix:semicolon
multiline_comment|/* virt base of planb */
DECL|member|planb_base_phys
r_struct
id|planb_registers
op_star
id|planb_base_phys
suffix:semicolon
multiline_comment|/* phys base of planb */
DECL|member|priv_space
r_void
op_star
id|priv_space
suffix:semicolon
multiline_comment|/* Org. alloc. mem for kfree */
DECL|member|user
r_int
id|user
suffix:semicolon
DECL|member|tab_size
r_int
r_int
id|tab_size
suffix:semicolon
DECL|member|maxlines
r_int
id|maxlines
suffix:semicolon
DECL|member|lock
r_struct
id|semaphore
id|lock
suffix:semicolon
DECL|member|irq
r_int
r_int
id|irq
suffix:semicolon
multiline_comment|/* interrupt number */
DECL|member|intr_mask
r_volatile
r_int
r_int
id|intr_mask
suffix:semicolon
DECL|member|overlay
r_int
id|overlay
suffix:semicolon
multiline_comment|/* overlay running? */
DECL|member|win
r_struct
id|planb_window
id|win
suffix:semicolon
DECL|member|frame_buffer_phys
r_int
r_int
id|frame_buffer_phys
suffix:semicolon
multiline_comment|/* We need phys for DMA */
DECL|member|offset
r_int
id|offset
suffix:semicolon
multiline_comment|/* offset of pixel 1 */
DECL|member|ch1_cmd
r_volatile
r_struct
id|dbdma_cmd
op_star
id|ch1_cmd
suffix:semicolon
multiline_comment|/* Video In DMA cmd buffer */
DECL|member|ch2_cmd
r_volatile
r_struct
id|dbdma_cmd
op_star
id|ch2_cmd
suffix:semicolon
multiline_comment|/* Clip Out DMA cmd buffer */
DECL|member|overlay_last1
r_volatile
r_struct
id|dbdma_cmd
op_star
id|overlay_last1
suffix:semicolon
DECL|member|overlay_last2
r_volatile
r_struct
id|dbdma_cmd
op_star
id|overlay_last2
suffix:semicolon
DECL|member|ch1_cmd_phys
r_int
r_int
id|ch1_cmd_phys
suffix:semicolon
DECL|member|mask
r_volatile
r_int
r_char
op_star
id|mask
suffix:semicolon
multiline_comment|/* Clipmask buffer */
DECL|member|suspend
r_int
id|suspend
suffix:semicolon
DECL|member|suspendq
id|wait_queue_head_t
id|suspendq
suffix:semicolon
DECL|member|suspended
r_struct
id|planb_suspend
id|suspended
suffix:semicolon
DECL|member|cmd_buff_inited
r_int
id|cmd_buff_inited
suffix:semicolon
multiline_comment|/* cmd buffer inited? */
DECL|member|grabbing
r_int
id|grabbing
suffix:semicolon
DECL|member|gcount
r_int
r_int
id|gcount
suffix:semicolon
DECL|member|capq
id|wait_queue_head_t
id|capq
suffix:semicolon
DECL|member|last_fr
r_int
id|last_fr
suffix:semicolon
DECL|member|prev_last_fr
r_int
id|prev_last_fr
suffix:semicolon
DECL|member|rawbuf
r_int
r_char
op_star
op_star
id|rawbuf
suffix:semicolon
DECL|member|rawbuf_size
r_int
id|rawbuf_size
suffix:semicolon
DECL|member|gbuf_idx
r_int
id|gbuf_idx
(braket
id|MAX_GBUFFERS
)braket
suffix:semicolon
DECL|member|cap_cmd
r_volatile
r_struct
id|dbdma_cmd
op_star
id|cap_cmd
(braket
id|MAX_GBUFFERS
)braket
suffix:semicolon
DECL|member|last_cmd
r_volatile
r_struct
id|dbdma_cmd
op_star
id|last_cmd
(braket
id|MAX_GBUFFERS
)braket
suffix:semicolon
DECL|member|pre_cmd
r_volatile
r_struct
id|dbdma_cmd
op_star
id|pre_cmd
(braket
id|MAX_GBUFFERS
)braket
suffix:semicolon
DECL|member|need_pre_capture
r_int
id|need_pre_capture
(braket
id|MAX_GBUFFERS
)braket
suffix:semicolon
DECL|macro|PLANB_DUMMY
mdefine_line|#define PLANB_DUMMY 40&t;/* # of command buf&squot;s allocated for pre-capture seq. */
DECL|member|gwidth
DECL|member|gheight
r_int
id|gwidth
(braket
id|MAX_GBUFFERS
)braket
comma
id|gheight
(braket
id|MAX_GBUFFERS
)braket
suffix:semicolon
DECL|member|gfmt
r_int
r_int
id|gfmt
(braket
id|MAX_GBUFFERS
)braket
suffix:semicolon
DECL|member|gnorm_switch
r_int
id|gnorm_switch
(braket
id|MAX_GBUFFERS
)braket
suffix:semicolon
DECL|member|frame_stat
r_volatile
r_int
r_int
op_star
id|frame_stat
suffix:semicolon
DECL|macro|GBUFFER_UNUSED
mdefine_line|#define GBUFFER_UNUSED       0x00U
DECL|macro|GBUFFER_GRABBING
mdefine_line|#define GBUFFER_GRABBING     0x01U
DECL|macro|GBUFFER_DONE
mdefine_line|#define GBUFFER_DONE         0x02U
macro_line|#ifdef PLANB_GSCANLINE
DECL|member|gbytes_per_line
r_int
id|gbytes_per_line
suffix:semicolon
macro_line|#else
DECL|macro|MAX_LNUM
mdefine_line|#define MAX_LNUM 431&t;/* change this if PLANB_MAXLINES or */
multiline_comment|/* PLANB_MAXPIXELS changes */
DECL|member|l_fr_addr_idx
r_int
id|l_fr_addr_idx
(braket
id|MAX_GBUFFERS
)braket
suffix:semicolon
DECL|member|l_to_addr
r_int
r_char
op_star
id|l_to_addr
(braket
id|MAX_GBUFFERS
)braket
(braket
id|MAX_LNUM
)braket
suffix:semicolon
DECL|member|l_to_next_idx
r_int
id|l_to_next_idx
(braket
id|MAX_GBUFFERS
)braket
(braket
id|MAX_LNUM
)braket
suffix:semicolon
DECL|member|l_to_next_size
r_int
id|l_to_next_size
(braket
id|MAX_GBUFFERS
)braket
(braket
id|MAX_LNUM
)braket
suffix:semicolon
DECL|member|lsize
DECL|member|lnum
r_int
id|lsize
(braket
id|MAX_GBUFFERS
)braket
comma
id|lnum
(braket
id|MAX_GBUFFERS
)braket
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _PLANB_H_ */
eof
