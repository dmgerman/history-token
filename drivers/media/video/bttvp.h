multiline_comment|/*&n;    bttv - Bt848 frame grabber driver&n;&n;    bttv&squot;s *private* header file  --  nobody else than bttv itself&n;    should ever include this file.&n;&n;    Copyright (C) 1996,97 Ralph Metzler (rjkm@thp.uni-koeln.de)&n;    (c) 1999,2000 Gerd Knorr &lt;kraxel@goldbach.in-berlin.de&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
macro_line|#ifndef _BTTVP_H_
DECL|macro|_BTTVP_H_
mdefine_line|#define _BTTVP_H_
DECL|macro|BTTV_VERSION_CODE
mdefine_line|#define BTTV_VERSION_CODE KERNEL_VERSION(0,7,83)
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;linux/i2c-algo-bit.h&gt;
macro_line|#include &quot;bt848.h&quot;
macro_line|#include &quot;bttv.h&quot;
macro_line|#include &quot;audiochip.h&quot;
macro_line|#ifdef __KERNEL__
multiline_comment|/* ---------------------------------------------------------- */
multiline_comment|/* bttv-driver.c                                              */
multiline_comment|/* insmod options / kernel args */
r_extern
r_int
id|no_overlay
suffix:semicolon
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
DECL|macro|dprintk
mdefine_line|#define dprintk&t;&t;if (bttv_debug) printk
multiline_comment|/* Anybody who uses more than four? */
DECL|macro|BTTV_MAX
mdefine_line|#define BTTV_MAX 4
r_extern
r_int
id|bttv_num
suffix:semicolon
multiline_comment|/* number of Bt848s in use */
r_extern
r_struct
id|bttv
id|bttvs
(braket
id|BTTV_MAX
)braket
suffix:semicolon
macro_line|#ifndef O_NONCAP  
DECL|macro|O_NONCAP
mdefine_line|#define O_NONCAP&t;O_TRUNC
macro_line|#endif
macro_line|#ifdef VIDEODAT_HACK
DECL|macro|VBI_MAXLINES
macro_line|# define VBI_MAXLINES   19
macro_line|#else
DECL|macro|VBI_MAXLINES
macro_line|# define VBI_MAXLINES   16
macro_line|#endif
DECL|macro|VBIBUF_SIZE
mdefine_line|#define VBIBUF_SIZE     (2048*VBI_MAXLINES*2)
DECL|macro|MAX_GBUFFERS
mdefine_line|#define MAX_GBUFFERS&t;64
DECL|macro|RISCMEM_LEN
mdefine_line|#define RISCMEM_LEN&t;(32744*2)
DECL|macro|BTTV_MAX_FBUF
mdefine_line|#define BTTV_MAX_FBUF&t;0x208000
DECL|struct|bttv_window
r_struct
id|bttv_window
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
id|ushort
id|bpp
comma
id|bpl
suffix:semicolon
DECL|member|swidth
DECL|member|sheight
id|ushort
id|swidth
comma
id|sheight
suffix:semicolon
DECL|member|vidadr
r_int
r_int
id|vidadr
suffix:semicolon
DECL|member|freq
id|ushort
id|freq
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
r_int
id|color_fmt
suffix:semicolon
DECL|member|depth
id|ushort
id|depth
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|bttv_pll_info
r_struct
id|bttv_pll_info
(brace
DECL|member|pll_ifreq
r_int
r_int
id|pll_ifreq
suffix:semicolon
multiline_comment|/* PLL input frequency &t; */
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
DECL|struct|bttv_gbuf
r_struct
id|bttv_gbuf
(brace
DECL|member|stat
r_int
id|stat
suffix:semicolon
DECL|macro|GBUFFER_UNUSED
mdefine_line|#define GBUFFER_UNUSED       0
DECL|macro|GBUFFER_GRABBING
mdefine_line|#define GBUFFER_GRABBING     1
DECL|macro|GBUFFER_DONE
mdefine_line|#define GBUFFER_DONE         2
DECL|macro|GBUFFER_ERROR
mdefine_line|#define GBUFFER_ERROR        3
DECL|member|tv
r_struct
id|timeval
id|tv
suffix:semicolon
DECL|member|width
id|u16
id|width
suffix:semicolon
DECL|member|height
id|u16
id|height
suffix:semicolon
DECL|member|fmt
id|u16
id|fmt
suffix:semicolon
DECL|member|risc
id|u32
op_star
id|risc
suffix:semicolon
DECL|member|ro
r_int
r_int
id|ro
suffix:semicolon
DECL|member|re
r_int
r_int
id|re
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|bttv
r_struct
id|bttv
(brace
DECL|member|video_dev
r_struct
id|video_device
id|video_dev
suffix:semicolon
DECL|member|radio_dev
r_struct
id|video_device
id|radio_dev
suffix:semicolon
DECL|member|vbi_dev
r_struct
id|video_device
id|vbi_dev
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
DECL|member|s_lock
id|spinlock_t
id|s_lock
suffix:semicolon
DECL|member|lock
r_struct
id|semaphore
id|lock
suffix:semicolon
DECL|member|user
r_int
id|user
suffix:semicolon
DECL|member|capuser
r_int
id|capuser
suffix:semicolon
multiline_comment|/* i2c */
DECL|member|i2c_adap
r_struct
id|i2c_adapter
id|i2c_adap
suffix:semicolon
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
DECL|member|i2c_clients
r_struct
id|i2c_client
op_star
id|i2c_clients
(braket
id|I2C_CLIENTS_MAX
)braket
suffix:semicolon
DECL|member|tuner_type
r_int
id|tuner_type
suffix:semicolon
DECL|member|channel
r_int
id|channel
suffix:semicolon
DECL|member|nr
r_int
r_int
id|nr
suffix:semicolon
DECL|member|id
r_int
r_int
id|id
suffix:semicolon
DECL|member|dev
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
DECL|member|irq
r_int
r_int
id|irq
suffix:semicolon
multiline_comment|/* IRQ used by Bt848 card */
DECL|member|revision
r_int
r_char
id|revision
suffix:semicolon
DECL|member|bt848_adr
r_int
r_int
id|bt848_adr
suffix:semicolon
multiline_comment|/* bus address of IO mem returned by PCI BIOS */
DECL|member|bt848_mem
r_int
r_char
op_star
id|bt848_mem
suffix:semicolon
multiline_comment|/* pointer to mapped IO memory */
DECL|member|busriscmem
r_int
r_int
id|busriscmem
suffix:semicolon
DECL|member|riscmem
id|u32
op_star
id|riscmem
suffix:semicolon
DECL|member|vbibuf
r_int
r_char
op_star
id|vbibuf
suffix:semicolon
DECL|member|win
r_struct
id|bttv_window
id|win
suffix:semicolon
DECL|member|fb_color_ctl
r_int
id|fb_color_ctl
suffix:semicolon
DECL|member|type
r_int
id|type
suffix:semicolon
multiline_comment|/* card type  */
DECL|member|cardid
r_int
id|cardid
suffix:semicolon
DECL|member|audio
r_int
id|audio
suffix:semicolon
multiline_comment|/* audio mode */
DECL|member|audio_chip
r_int
id|audio_chip
suffix:semicolon
multiline_comment|/* set to one of the chips supported by bttv.c */
DECL|member|radio
r_int
id|radio
suffix:semicolon
DECL|member|has_radio
r_int
id|has_radio
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
DECL|member|risc_jmp
id|u32
op_star
id|risc_jmp
suffix:semicolon
DECL|member|vbi_odd
id|u32
op_star
id|vbi_odd
suffix:semicolon
DECL|member|vbi_even
id|u32
op_star
id|vbi_even
suffix:semicolon
DECL|member|bus_vbi_even
id|u32
id|bus_vbi_even
suffix:semicolon
DECL|member|bus_vbi_odd
id|u32
id|bus_vbi_odd
suffix:semicolon
DECL|member|vbiq
id|wait_queue_head_t
id|vbiq
suffix:semicolon
DECL|member|capq
id|wait_queue_head_t
id|capq
suffix:semicolon
DECL|member|vbip
r_int
id|vbip
suffix:semicolon
DECL|member|risc_scr_odd
id|u32
op_star
id|risc_scr_odd
suffix:semicolon
DECL|member|risc_scr_even
id|u32
op_star
id|risc_scr_even
suffix:semicolon
DECL|member|risc_cap_odd
id|u32
id|risc_cap_odd
suffix:semicolon
DECL|member|risc_cap_even
id|u32
id|risc_cap_even
suffix:semicolon
DECL|member|scr_on
r_int
id|scr_on
suffix:semicolon
DECL|member|vbi_on
r_int
id|vbi_on
suffix:semicolon
DECL|member|cliprecs
r_struct
id|video_clip
op_star
id|cliprecs
suffix:semicolon
DECL|member|gbuf
r_struct
id|bttv_gbuf
op_star
id|gbuf
suffix:semicolon
DECL|member|gqueue
r_int
id|gqueue
(braket
id|MAX_GBUFFERS
)braket
suffix:semicolon
DECL|member|gq_in
DECL|member|gq_out
DECL|member|gq_grab
DECL|member|gq_start
r_int
id|gq_in
comma
id|gq_out
comma
id|gq_grab
comma
id|gq_start
suffix:semicolon
DECL|member|fbuffer
r_char
op_star
id|fbuffer
suffix:semicolon
DECL|member|pll
r_struct
id|bttv_pll_info
id|pll
suffix:semicolon
DECL|member|Fsc
r_int
r_int
id|Fsc
suffix:semicolon
DECL|member|field
r_int
r_int
id|field
suffix:semicolon
DECL|member|last_field
r_int
r_int
id|last_field
suffix:semicolon
multiline_comment|/* number of last grabbed field */
DECL|member|i2c_command
r_int
id|i2c_command
suffix:semicolon
DECL|member|triton1
r_int
id|triton1
suffix:semicolon
DECL|member|errors
r_int
id|errors
suffix:semicolon
DECL|member|needs_restart
r_int
id|needs_restart
suffix:semicolon
DECL|member|gpioq
id|wait_queue_head_t
id|gpioq
suffix:semicolon
DECL|member|shutdown
r_int
id|shutdown
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
DECL|macro|btwrite
mdefine_line|#define btwrite(dat,adr)    writel((dat), (char *) (btv-&gt;bt848_mem+(adr)))
DECL|macro|btread
mdefine_line|#define btread(adr)         readl(btv-&gt;bt848_mem+(adr))
DECL|macro|btand
mdefine_line|#define btand(dat,adr)      btwrite((dat) &amp; btread(adr), adr)
DECL|macro|btor
mdefine_line|#define btor(dat,adr)       btwrite((dat) | btread(adr), adr)
DECL|macro|btaor
mdefine_line|#define btaor(dat,mask,adr) btwrite((dat) | ((mask) &amp; btread(adr)), adr)
multiline_comment|/* bttv ioctls */
DECL|macro|BTTV_READEE
mdefine_line|#define BTTV_READEE&t;&t;_IOW(&squot;v&squot;,  BASE_VIDIOCPRIVATE+0, char [256])
DECL|macro|BTTV_WRITEE
mdefine_line|#define BTTV_WRITEE&t;&t;_IOR(&squot;v&squot;,  BASE_VIDIOCPRIVATE+1, char [256])
DECL|macro|BTTV_FIELDNR
mdefine_line|#define BTTV_FIELDNR&t;&t;_IOR(&squot;v&squot; , BASE_VIDIOCPRIVATE+2, unsigned int)
DECL|macro|BTTV_PLLSET
mdefine_line|#define BTTV_PLLSET&t;&t;_IOW(&squot;v&squot; , BASE_VIDIOCPRIVATE+3, struct bttv_pll_info)
DECL|macro|BTTV_BURST_ON
mdefine_line|#define BTTV_BURST_ON      &t;_IOR(&squot;v&squot; , BASE_VIDIOCPRIVATE+4, int)
DECL|macro|BTTV_BURST_OFF
mdefine_line|#define BTTV_BURST_OFF     &t;_IOR(&squot;v&squot; , BASE_VIDIOCPRIVATE+5, int)
DECL|macro|BTTV_VERSION
mdefine_line|#define BTTV_VERSION  &t;        _IOR(&squot;v&squot; , BASE_VIDIOCPRIVATE+6, int)
DECL|macro|BTTV_PICNR
mdefine_line|#define BTTV_PICNR&t;&t;_IOR(&squot;v&squot; , BASE_VIDIOCPRIVATE+7, int)
DECL|macro|BTTV_VBISIZE
mdefine_line|#define BTTV_VBISIZE            _IOR(&squot;v&squot; , BASE_VIDIOCPRIVATE+8, int)
DECL|macro|TDA9850
mdefine_line|#define TDA9850            0x01
DECL|macro|TDA9840
mdefine_line|#define TDA9840            0x02
DECL|macro|TDA8425
mdefine_line|#define TDA8425            0x03
DECL|macro|TEA6300
mdefine_line|#define TEA6300            0x04
macro_line|#endif /* _BTTVP_H_ */
multiline_comment|/*&n; * Local variables:&n; * c-basic-offset: 8&n; * End:&n; */
eof
