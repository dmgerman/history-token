multiline_comment|/*  &n;    saa7146.h - definitions philips saa7146 based cards&n;    Copyright (C) 1999 Nathan Laredo (laredo@gnu.org)&n;    &n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
macro_line|#ifndef __SAA7146__
DECL|macro|__SAA7146__
mdefine_line|#define __SAA7146__
DECL|macro|SAA7146_VERSION_CODE
mdefine_line|#define SAA7146_VERSION_CODE 0x000101
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/videodev.h&gt;
macro_line|#ifndef O_NONCAP  
DECL|macro|O_NONCAP
mdefine_line|#define O_NONCAP&t;O_TRUNC
macro_line|#endif
DECL|macro|MAX_GBUFFERS
mdefine_line|#define MAX_GBUFFERS&t;2
DECL|macro|FBUF_SIZE
mdefine_line|#define FBUF_SIZE&t;0x190000
macro_line|#ifdef __KERNEL__
DECL|struct|saa7146_window
r_struct
id|saa7146_window
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
DECL|member|cropx
DECL|member|cropy
r_int
id|cropx
comma
id|cropy
suffix:semicolon
DECL|member|cropwidth
DECL|member|cropheight
id|ushort
id|cropwidth
comma
id|cropheight
suffix:semicolon
DECL|member|vidadr
r_int
r_int
id|vidadr
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
multiline_comment|/*  Per-open data for handling multiple opens on one device */
DECL|struct|device_open
r_struct
id|device_open
(brace
DECL|member|isopen
r_int
id|isopen
suffix:semicolon
DECL|member|noncapturing
r_int
id|noncapturing
suffix:semicolon
DECL|member|dev
r_struct
id|saa7146
op_star
id|dev
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|MAX_OPENS
mdefine_line|#define MAX_OPENS 3
DECL|struct|saa7146
r_struct
id|saa7146
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
DECL|member|audio_dev
r_struct
id|video_audio
id|audio_dev
suffix:semicolon
DECL|member|vidinfo
r_struct
id|video_info
id|vidinfo
suffix:semicolon
DECL|member|user
r_int
id|user
suffix:semicolon
DECL|member|cap
r_int
id|cap
suffix:semicolon
DECL|member|capuser
r_int
id|capuser
suffix:semicolon
DECL|member|irqstate
r_int
id|irqstate
suffix:semicolon
multiline_comment|/* irq routine is state driven */
DECL|member|writemode
r_int
id|writemode
suffix:semicolon
DECL|member|playmode
r_int
id|playmode
suffix:semicolon
DECL|member|nr
r_int
r_int
id|nr
suffix:semicolon
DECL|member|irq
r_int
r_int
id|irq
suffix:semicolon
multiline_comment|/* IRQ used by SAA7146 card */
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
DECL|member|revision
r_int
r_char
id|revision
suffix:semicolon
DECL|member|boardcfg
r_int
r_char
id|boardcfg
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* 64 bytes of config from eeprom */
DECL|member|saa7146_adr
r_int
r_int
id|saa7146_adr
suffix:semicolon
multiline_comment|/* bus address of IO mem from PCI BIOS */
DECL|member|win
r_struct
id|saa7146_window
id|win
suffix:semicolon
DECL|member|saa7146_mem
r_int
r_char
id|__iomem
op_star
id|saa7146_mem
suffix:semicolon
multiline_comment|/* pointer to mapped IO memory */
DECL|member|open_data
r_struct
id|device_open
id|open_data
(braket
id|MAX_OPENS
)braket
suffix:semicolon
DECL|macro|MAX_MARKS
mdefine_line|#define MAX_MARKS 16
multiline_comment|/* for a/v sync */
DECL|member|endmark
DECL|member|endmarkhead
DECL|member|endmarktail
r_int
id|endmark
(braket
id|MAX_MARKS
)braket
comma
id|endmarkhead
comma
id|endmarktail
suffix:semicolon
DECL|member|dmaRPS1
DECL|member|pageRPS1
DECL|member|dmaRPS2
DECL|member|pageRPS2
DECL|member|dmavid1
DECL|member|dmavid2
id|u32
op_star
id|dmaRPS1
comma
op_star
id|pageRPS1
comma
op_star
id|dmaRPS2
comma
op_star
id|pageRPS2
comma
op_star
id|dmavid1
comma
op_star
id|dmavid2
comma
DECL|member|dmavid3
DECL|member|dmaa1in
DECL|member|dmaa1out
DECL|member|dmaa2in
DECL|member|dmaa2out
op_star
id|dmavid3
comma
op_star
id|dmaa1in
comma
op_star
id|dmaa1out
comma
op_star
id|dmaa2in
comma
op_star
id|dmaa2out
comma
DECL|member|pagedebi
DECL|member|pagevid1
DECL|member|pagevid2
DECL|member|pagevid3
DECL|member|pagea1in
op_star
id|pagedebi
comma
op_star
id|pagevid1
comma
op_star
id|pagevid2
comma
op_star
id|pagevid3
comma
op_star
id|pagea1in
comma
DECL|member|pagea1out
DECL|member|pagea2in
DECL|member|pagea2out
op_star
id|pagea1out
comma
op_star
id|pagea2in
comma
op_star
id|pagea2out
suffix:semicolon
DECL|member|i2cq
DECL|member|debiq
DECL|member|audq
DECL|member|vidq
id|wait_queue_head_t
id|i2cq
comma
id|debiq
comma
id|audq
comma
id|vidq
suffix:semicolon
DECL|member|vidbuf
DECL|member|audbuf
DECL|member|osdbuf
DECL|member|dmadebi
id|u8
op_star
id|vidbuf
comma
op_star
id|audbuf
comma
op_star
id|osdbuf
comma
op_star
id|dmadebi
suffix:semicolon
DECL|member|audhead
DECL|member|vidhead
DECL|member|osdhead
DECL|member|audtail
DECL|member|vidtail
DECL|member|osdtail
r_int
id|audhead
comma
id|vidhead
comma
id|osdhead
comma
id|audtail
comma
id|vidtail
comma
id|osdtail
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
multiline_comment|/* the device lock */
)brace
suffix:semicolon
macro_line|#endif
macro_line|#ifdef _ALPHA_SAA7146
DECL|macro|saawrite
mdefine_line|#define saawrite(dat,adr)    writel((dat), saa-&gt;saa7146_adr+(adr))
DECL|macro|saaread
mdefine_line|#define saaread(adr)         readl(saa-&gt;saa7146_adr+(adr))
macro_line|#else
DECL|macro|saawrite
mdefine_line|#define saawrite(dat,adr)    writel((dat), saa-&gt;saa7146_mem+(adr))
DECL|macro|saaread
mdefine_line|#define saaread(adr)         readl(saa-&gt;saa7146_mem+(adr))
macro_line|#endif
DECL|macro|saaand
mdefine_line|#define saaand(dat,adr)      saawrite((dat) &amp; saaread(adr), adr)
DECL|macro|saaor
mdefine_line|#define saaor(dat,adr)       saawrite((dat) | saaread(adr), adr)
DECL|macro|saaaor
mdefine_line|#define saaaor(dat,mask,adr) saawrite((dat) | ((mask) &amp; saaread(adr)), adr)
multiline_comment|/* bitmask of attached hardware found */
DECL|macro|SAA7146_UNKNOWN
mdefine_line|#define SAA7146_UNKNOWN&t;&t;0x00000000
DECL|macro|SAA7146_SAA7111
mdefine_line|#define SAA7146_SAA7111&t;&t;0x00000001
DECL|macro|SAA7146_SAA7121
mdefine_line|#define SAA7146_SAA7121&t;&t;0x00000002
DECL|macro|SAA7146_IBMMPEG
mdefine_line|#define SAA7146_IBMMPEG&t;&t;0x00000004
macro_line|#endif
eof
