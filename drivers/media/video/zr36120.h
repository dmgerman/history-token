multiline_comment|/* &n;    zr36120.h - Zoran 36120/36125 based framegrabbers&n;&n;    Copyright (C) 1998-1999 Pauline Middelink (middelin@polyware.nl)&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
macro_line|#ifndef _ZR36120_H
DECL|macro|_ZR36120_H
mdefine_line|#define _ZR36120_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/i2c-old.h&gt;
macro_line|#include &lt;linux/videodev.h&gt;
macro_line|#include &lt;asm/io.h&gt;
multiline_comment|/*&n; * Debug macro&squot;s, place an x behind the ) for actual debug-compilation&n; * E.g. #define DEBUG(x...)&t;x&n; */
DECL|macro|DEBUG
mdefine_line|#define DEBUG(x...)&t;&t;&t;/* Debug driver */
DECL|macro|IDEBUG
mdefine_line|#define IDEBUG(x...)&t;&t;&t;/* Debug interrupt handler */
DECL|macro|PDEBUG
mdefine_line|#define PDEBUG&t;&t;0&t;&t;/* Debug PCI writes */
multiline_comment|/* defined in zr36120_i2c */
r_extern
r_struct
id|i2c_bus
id|zoran_i2c_bus_template
suffix:semicolon
DECL|macro|ZORAN_MAX_FBUFFERS
mdefine_line|#define&t;ZORAN_MAX_FBUFFERS&t;2
DECL|macro|ZORAN_MAX_FBUFFER
mdefine_line|#define&t;ZORAN_MAX_FBUFFER&t;(768*576*2)
DECL|macro|ZORAN_MAX_FBUFSIZE
mdefine_line|#define&t;ZORAN_MAX_FBUFSIZE&t;(ZORAN_MAX_FBUFFERS*ZORAN_MAX_FBUFFER)
DECL|macro|ZORAN_VBI_BUFFERS
mdefine_line|#define&t;ZORAN_VBI_BUFFERS&t;2
DECL|macro|ZORAN_VBI_BUFSIZE
mdefine_line|#define&t;ZORAN_VBI_BUFSIZE&t;(22*1024*2)
DECL|struct|tvcard
r_struct
id|tvcard
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/* name of the cardtype */
DECL|member|video_inputs
r_int
id|video_inputs
suffix:semicolon
multiline_comment|/* number of channels defined in video_mux */
DECL|member|audio_inputs
r_int
id|audio_inputs
suffix:semicolon
multiline_comment|/* number of channels defined in audio_mux */
DECL|member|swapi2c
id|__u32
id|swapi2c
suffix:colon
l_int|1
comma
multiline_comment|/* need to swap i2c wires SDA/SCL? */
DECL|member|usegirq1
id|usegirq1
suffix:colon
l_int|1
comma
multiline_comment|/* VSYNC at GIRQ1 instead of GIRQ0? */
DECL|member|vsync_pos
id|vsync_pos
suffix:colon
l_int|1
comma
multiline_comment|/* positive VSYNC signal? */
DECL|member|hsync_pos
id|hsync_pos
suffix:colon
l_int|1
comma
multiline_comment|/* positive HSYNC signal? */
DECL|member|gpdir
id|gpdir
suffix:colon
l_int|8
comma
multiline_comment|/* General Purpose Direction register */
DECL|member|gpval
id|gpval
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* General Purpose Value register */
DECL|member|video_mux
r_int
id|video_mux
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* mapping channel number to physical input */
DECL|macro|IS_TUNER
mdefine_line|#define&t;&t;IS_TUNER&t;0x80
DECL|macro|IS_SVHS
mdefine_line|#define&t;&t;IS_SVHS&t;&t;0x40
DECL|macro|CHANNEL_MASK
mdefine_line|#define&t;&t;CHANNEL_MASK&t;0x3F
DECL|member|audio_mux
r_int
id|audio_mux
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* mapping channel number to physical input */
)brace
suffix:semicolon
DECL|macro|TUNER
mdefine_line|#define&t;TUNER(x)&t;((x)|IS_TUNER)
DECL|macro|SVHS
mdefine_line|#define&t;SVHS(x)&t;&t;((x)|IS_SVHS)
DECL|struct|vidinfo
r_struct
id|vidinfo
(brace
DECL|member|next
r_struct
id|vidinfo
op_star
id|next
suffix:semicolon
multiline_comment|/* next active buffer&t;&t;&t;*/
DECL|member|kindof
id|uint
id|kindof
suffix:semicolon
DECL|macro|FBUFFER_OVERLAY
mdefine_line|#define&t;FBUFFER_OVERLAY&t;&t;0
DECL|macro|FBUFFER_GRAB
mdefine_line|#define&t;FBUFFER_GRAB&t;&t;1
DECL|macro|FBUFFER_VBI
mdefine_line|#define&t;FBUFFER_VBI&t;&t;2
DECL|member|status
id|uint
id|status
suffix:semicolon
DECL|macro|FBUFFER_FREE
mdefine_line|#define FBUFFER_FREE&t;&t;0
DECL|macro|FBUFFER_BUSY
mdefine_line|#define FBUFFER_BUSY&t;&t;1
DECL|macro|FBUFFER_DONE
mdefine_line|#define FBUFFER_DONE&t;&t;2
DECL|member|fieldnr
id|ulong
id|fieldnr
suffix:semicolon
multiline_comment|/* # of field, not framer!&t;&t;*/
DECL|member|x
DECL|member|y
id|uint
id|x
comma
id|y
suffix:semicolon
DECL|member|w
DECL|member|h
r_int
id|w
comma
id|h
suffix:semicolon
multiline_comment|/* w,h can be negative!&t;&t;&t;*/
DECL|member|format
id|uint
id|format
suffix:semicolon
multiline_comment|/* index in palette2fmt[]&t;&t;*/
DECL|member|bpp
id|uint
id|bpp
suffix:semicolon
multiline_comment|/* lookup from palette2fmt[]&t;&t;*/
DECL|member|bpl
id|uint
id|bpl
suffix:semicolon
multiline_comment|/* calc: width * bpp&t;&t;&t;*/
DECL|member|busadr
id|ulong
id|busadr
suffix:semicolon
multiline_comment|/* bus addr for DMA engine&t;&t;*/
DECL|member|memadr
r_char
op_star
id|memadr
suffix:semicolon
multiline_comment|/* kernel addr for making copies&t;*/
DECL|member|overlay
id|ulong
op_star
id|overlay
suffix:semicolon
multiline_comment|/* kernel addr of overlay mask&t;&t;*/
)brace
suffix:semicolon
DECL|struct|zoran
r_struct
id|zoran
(brace
DECL|member|video_dev
r_struct
id|video_device
id|video_dev
suffix:semicolon
DECL|macro|CARD_DEBUG
mdefine_line|#define CARD_DEBUG&t;KERN_DEBUG &quot;%s(%lu): &quot;
DECL|macro|CARD_INFO
mdefine_line|#define CARD_INFO&t;KERN_INFO &quot;%s(%lu): &quot;
DECL|macro|CARD_ERR
mdefine_line|#define CARD_ERR&t;KERN_ERR &quot;%s(%lu): &quot;
DECL|macro|CARD
mdefine_line|#define CARD&t;&t;ztv-&gt;video_dev.name,ztv-&gt;fieldnr
multiline_comment|/* zoran chip specific details */
DECL|member|i2c
r_struct
id|i2c_bus
id|i2c
suffix:semicolon
multiline_comment|/* i2c registration data&t;*/
DECL|member|dev
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
multiline_comment|/* ptr to PCI device&t;&t;*/
DECL|member|zoran_adr
id|ulong
id|zoran_adr
suffix:semicolon
multiline_comment|/* bus address of IO memory&t;*/
DECL|member|zoran_mem
r_char
op_star
id|zoran_mem
suffix:semicolon
multiline_comment|/* kernel address of IO memory&t;*/
DECL|member|card
r_struct
id|tvcard
op_star
id|card
suffix:semicolon
multiline_comment|/* the cardtype&t;&t;&t;*/
DECL|member|norm
id|uint
id|norm
suffix:semicolon
multiline_comment|/* 0=PAL, 1=NTSC, 2=SECAM&t;*/
DECL|member|tuner_freq
id|uint
id|tuner_freq
suffix:semicolon
multiline_comment|/* Current freq in kHz&t;&t;*/
DECL|member|picture
r_struct
id|video_picture
id|picture
suffix:semicolon
multiline_comment|/* Current picture params&t;*/
multiline_comment|/* videocard details */
DECL|member|swidth
id|uint
id|swidth
suffix:semicolon
multiline_comment|/* screen width&t;&t;&t;*/
DECL|member|sheight
id|uint
id|sheight
suffix:semicolon
multiline_comment|/* screen height&t;&t;*/
DECL|member|depth
id|uint
id|depth
suffix:semicolon
multiline_comment|/* depth in bits&t;&t;*/
multiline_comment|/* State details */
DECL|member|fbuffer
r_char
op_star
id|fbuffer
suffix:semicolon
multiline_comment|/* framebuffers for mmap&t;*/
DECL|member|overinfo
r_struct
id|vidinfo
id|overinfo
suffix:semicolon
multiline_comment|/* overlay data&t;&t;&t;*/
DECL|member|grabinfo
r_struct
id|vidinfo
id|grabinfo
(braket
id|ZORAN_MAX_FBUFFERS
)braket
suffix:semicolon
multiline_comment|/* grabbing data*/
DECL|member|grabq
id|wait_queue_head_t
id|grabq
suffix:semicolon
multiline_comment|/* grabbers queue&t;&t;*/
multiline_comment|/* VBI details */
DECL|member|vbi_dev
r_struct
id|video_device
id|vbi_dev
suffix:semicolon
DECL|member|readinfo
r_struct
id|vidinfo
id|readinfo
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* VBI data - flip buffers&t;*/
DECL|member|vbiq
id|wait_queue_head_t
id|vbiq
suffix:semicolon
multiline_comment|/* vbi queue&t;&t;&t;*/
multiline_comment|/* maintenance data */
DECL|member|have_decoder
r_int
id|have_decoder
suffix:semicolon
multiline_comment|/* did we detect a mux?&t;&t;*/
DECL|member|have_tuner
r_int
id|have_tuner
suffix:semicolon
multiline_comment|/* did we detect a tuner?&t;*/
DECL|member|users
r_int
id|users
suffix:semicolon
multiline_comment|/* howmany video/vbi open?&t;*/
DECL|member|tuner_type
r_int
id|tuner_type
suffix:semicolon
multiline_comment|/* tuner type, when found&t;*/
DECL|member|running
r_int
id|running
suffix:semicolon
multiline_comment|/* are we rolling?&t;&t;*/
DECL|member|lock
id|rwlock_t
id|lock
suffix:semicolon
DECL|member|state
r_int
id|state
suffix:semicolon
multiline_comment|/* what is requested of us?&t;*/
DECL|macro|STATE_OVERLAY
mdefine_line|#define STATE_OVERLAY&t;0
DECL|macro|STATE_VBI
mdefine_line|#define STATE_VBI&t;1
DECL|member|workqueue
r_struct
id|vidinfo
op_star
id|workqueue
suffix:semicolon
multiline_comment|/* buffers to grab, head is active */
DECL|member|fieldnr
id|ulong
id|fieldnr
suffix:semicolon
multiline_comment|/* #field, ticked every VSYNC&t;*/
DECL|member|lastfieldnr
id|ulong
id|lastfieldnr
suffix:semicolon
multiline_comment|/* #field, ticked every GRAB&t;*/
DECL|member|vidInterlace
r_int
id|vidInterlace
suffix:semicolon
multiline_comment|/* calculated */
DECL|member|vidXshift
r_int
id|vidXshift
suffix:semicolon
multiline_comment|/* calculated */
DECL|member|vidWidth
id|uint
id|vidWidth
suffix:semicolon
multiline_comment|/* calculated */
DECL|member|vidHeight
id|uint
id|vidHeight
suffix:semicolon
multiline_comment|/* calculated */
)brace
suffix:semicolon
DECL|macro|zrwrite
mdefine_line|#define zrwrite(dat,adr)    writel((dat),(char *) (ztv-&gt;zoran_mem+(adr)))
DECL|macro|zrread
mdefine_line|#define zrread(adr)         readl(ztv-&gt;zoran_mem+(adr))
macro_line|#if PDEBUG == 0
DECL|macro|zrand
mdefine_line|#define zrand(dat,adr)      zrwrite((dat) &amp; zrread(adr), adr)
DECL|macro|zror
mdefine_line|#define zror(dat,adr)       zrwrite((dat) | zrread(adr), adr)
DECL|macro|zraor
mdefine_line|#define zraor(dat,mask,adr) zrwrite( ((dat)&amp;~(mask)) | ((mask)&amp;zrread(adr)), adr)
macro_line|#else
DECL|macro|zrand
mdefine_line|#define zrand(dat, adr) &bslash;&n;do { &bslash;&n;&t;ulong data = (dat) &amp; zrread((adr)); &bslash;&n;&t;zrwrite(data, (adr)); &bslash;&n;&t;if (0 != (~(dat) &amp; zrread((adr)))) &bslash;&n;&t;&t;printk(KERN_DEBUG &quot;zoran: zrand at %d(%d) detected set bits(%x)&bslash;n&quot;, __LINE__, (adr), (dat)); &bslash;&n;} while(0)
DECL|macro|zror
mdefine_line|#define zror(dat, adr) &bslash;&n;do { &bslash;&n;&t;ulong data = (dat) | zrread((adr)); &bslash;&n;&t;zrwrite(data, (adr)); &bslash;&n;&t;if ((dat) != ((dat) &amp; zrread(adr))) &bslash;&n;&t;&t;printk(KERN_DEBUG &quot;zoran: zror at %d(%d) detected unset bits(%x)&bslash;n&quot;, __LINE__, (adr), (dat)); &bslash;&n;} while(0)
DECL|macro|zraor
mdefine_line|#define zraor(dat, mask, adr) &bslash;&n;do { &bslash;&n;&t;ulong data; &bslash;&n;&t;if ((dat) &amp; (mask)) &bslash;&n;&t;&t;printk(KERN_DEBUG &quot;zoran: zraor at %d(%d) detected bits(%x:%x)&bslash;n&quot;, __LINE__, (adr), (dat), (mask)); &bslash;&n;&t;data = ((dat)&amp;~(mask)) | ((mask) &amp; zrread((adr))); &bslash;&n;&t;zrwrite(data,(adr)); &bslash;&n;&t;if ( (dat) != (~(mask) &amp; zrread((adr))) ) &bslash;&n;&t;&t;printk(KERN_DEBUG &quot;zoran: zraor at %d(%d) could not set all bits(%x:%x)&bslash;n&quot;, __LINE__, (adr), (dat), (mask)); &bslash;&n;} while(0)
macro_line|#endif
macro_line|#endif
multiline_comment|/* zoran PCI address space */
DECL|macro|ZORAN_VFEH
mdefine_line|#define ZORAN_VFEH&t;&t;0x000&t;/* Video Front End Horizontal Conf. */
DECL|macro|ZORAN_VFEH_HSPOL
mdefine_line|#define&t;ZORAN_VFEH_HSPOL&t;(1&lt;&lt;30)
DECL|macro|ZORAN_VFEH_HSTART
mdefine_line|#define&t;ZORAN_VFEH_HSTART&t;(0x3FF&lt;&lt;10)
DECL|macro|ZORAN_VFEH_HEND
mdefine_line|#define&t;ZORAN_VFEH_HEND&t;&t;(0x3FF&lt;&lt;0)
DECL|macro|ZORAN_VFEV
mdefine_line|#define ZORAN_VFEV&t;&t;0x004&t;/* Video Front End Vertical Conf. */
DECL|macro|ZORAN_VFEV_VSPOL
mdefine_line|#define&t;ZORAN_VFEV_VSPOL&t;(1&lt;&lt;30)
DECL|macro|ZORAN_VFEV_VSTART
mdefine_line|#define&t;ZORAN_VFEV_VSTART&t;(0x3FF&lt;&lt;10)
DECL|macro|ZORAN_VFEV_VEND
mdefine_line|#define&t;ZORAN_VFEV_VEND&t;&t;(0x3FF&lt;&lt;0)
DECL|macro|ZORAN_VFEC
mdefine_line|#define&t;ZORAN_VFEC&t;&t;0x008&t;/* Video Front End Scaler and Pixel */
DECL|macro|ZORAN_VFEC_EXTFL
mdefine_line|#define ZORAN_VFEC_EXTFL&t;(1&lt;&lt;26)
DECL|macro|ZORAN_VFEC_TOPFIELD
mdefine_line|#define&t;ZORAN_VFEC_TOPFIELD&t;(1&lt;&lt;25)
DECL|macro|ZORAN_VFEC_VCLKPOL
mdefine_line|#define&t;ZORAN_VFEC_VCLKPOL&t;(1&lt;&lt;24)
DECL|macro|ZORAN_VFEC_HFILTER
mdefine_line|#define&t;ZORAN_VFEC_HFILTER&t;(7&lt;&lt;21)
DECL|macro|ZORAN_VFEC_HFILTER_1
mdefine_line|#define&t;ZORAN_VFEC_HFILTER_1&t;(0&lt;&lt;21)&t;/* no lumi,    3-tap chromo */
DECL|macro|ZORAN_VFEC_HFILTER_2
mdefine_line|#define&t;ZORAN_VFEC_HFILTER_2&t;(1&lt;&lt;21)&t;/* 3-tap lumi, 3-tap chromo */
DECL|macro|ZORAN_VFEC_HFILTER_3
mdefine_line|#define&t;ZORAN_VFEC_HFILTER_3&t;(2&lt;&lt;21)&t;/* 4-tap lumi, 4-tap chromo */
DECL|macro|ZORAN_VFEC_HFILTER_4
mdefine_line|#define&t;ZORAN_VFEC_HFILTER_4&t;(3&lt;&lt;21)&t;/* 5-tap lumi, 4-tap chromo */
DECL|macro|ZORAN_VFEC_HFILTER_5
mdefine_line|#define&t;ZORAN_VFEC_HFILTER_5&t;(4&lt;&lt;21)&t;/* 4-tap lumi, 4-tap chromo */
DECL|macro|ZORAN_VFEC_DUPFLD
mdefine_line|#define&t;ZORAN_VFEC_DUPFLD&t;(1&lt;&lt;20)
DECL|macro|ZORAN_VFEC_HORDCM
mdefine_line|#define&t;ZORAN_VFEC_HORDCM&t;(63&lt;&lt;14)
DECL|macro|ZORAN_VFEC_VERDCM
mdefine_line|#define&t;ZORAN_VFEC_VERDCM&t;(63&lt;&lt;8)
DECL|macro|ZORAN_VFEC_DISPMOD
mdefine_line|#define&t;ZORAN_VFEC_DISPMOD&t;(1&lt;&lt;6)
DECL|macro|ZORAN_VFEC_RGB
mdefine_line|#define&t;ZORAN_VFEC_RGB&t;&t;(3&lt;&lt;3)
DECL|macro|ZORAN_VFEC_RGB_YUV422
mdefine_line|#define&t;ZORAN_VFEC_RGB_YUV422&t;(0&lt;&lt;3)
DECL|macro|ZORAN_VFEC_RGB_RGB888
mdefine_line|#define&t;ZORAN_VFEC_RGB_RGB888&t;(1&lt;&lt;3)
DECL|macro|ZORAN_VFEC_RGB_RGB565
mdefine_line|#define&t;ZORAN_VFEC_RGB_RGB565&t;(2&lt;&lt;3)
DECL|macro|ZORAN_VFEC_RGB_RGB555
mdefine_line|#define&t;ZORAN_VFEC_RGB_RGB555&t;(3&lt;&lt;3)
DECL|macro|ZORAN_VFEC_ERRDIF
mdefine_line|#define&t;ZORAN_VFEC_ERRDIF&t;(1&lt;&lt;2)
DECL|macro|ZORAN_VFEC_PACK24
mdefine_line|#define&t;ZORAN_VFEC_PACK24&t;(1&lt;&lt;1)
DECL|macro|ZORAN_VFEC_LE
mdefine_line|#define&t;ZORAN_VFEC_LE&t;&t;(1&lt;&lt;0)
DECL|macro|ZORAN_VTOP
mdefine_line|#define&t;ZORAN_VTOP&t;&t;0x00C&t;/* Video Display &quot;Top&quot; */
DECL|macro|ZORAN_VBOT
mdefine_line|#define&t;ZORAN_VBOT&t;&t;0x010&t;/* Video Display &quot;Bottom&quot; */
DECL|macro|ZORAN_VSTR
mdefine_line|#define&t;ZORAN_VSTR&t;&t;0x014&t;/* Video Display Stride */
DECL|macro|ZORAN_VSTR_DISPSTRIDE
mdefine_line|#define&t;ZORAN_VSTR_DISPSTRIDE&t;(0xFFFF&lt;&lt;16)
DECL|macro|ZORAN_VSTR_VIDOVF
mdefine_line|#define&t;ZORAN_VSTR_VIDOVF&t;(1&lt;&lt;8)
DECL|macro|ZORAN_VSTR_SNAPSHOT
mdefine_line|#define&t;ZORAN_VSTR_SNAPSHOT&t;(1&lt;&lt;1)
DECL|macro|ZORAN_VSTR_GRAB
mdefine_line|#define&t;ZORAN_VSTR_GRAB&t;&t;(1&lt;&lt;0)
DECL|macro|ZORAN_VDC
mdefine_line|#define&t;ZORAN_VDC&t;&t;0x018&t;/* Video Display Conf. */
DECL|macro|ZORAN_VDC_VIDEN
mdefine_line|#define&t;ZORAN_VDC_VIDEN&t;&t;(1&lt;&lt;31)
DECL|macro|ZORAN_VDC_MINPIX
mdefine_line|#define&t;ZORAN_VDC_MINPIX&t;(0x1F&lt;&lt;25)
DECL|macro|ZORAN_VDC_TRICOM
mdefine_line|#define&t;ZORAN_VDC_TRICOM&t;(1&lt;&lt;24)
DECL|macro|ZORAN_VDC_VIDWINHT
mdefine_line|#define&t;ZORAN_VDC_VIDWINHT&t;(0x3FF&lt;&lt;12)
DECL|macro|ZORAN_VDC_VIDWINWID
mdefine_line|#define&t;ZORAN_VDC_VIDWINWID&t;(0x3FF&lt;&lt;0)
DECL|macro|ZORAN_MTOP
mdefine_line|#define&t;ZORAN_MTOP&t;&t;0x01C&t;/* Masking Map &quot;Top&quot; */
DECL|macro|ZORAN_MBOT
mdefine_line|#define&t;ZORAN_MBOT&t;&t;0x020&t;/* Masking Map &quot;Bottom&quot; */
DECL|macro|ZORAN_OCR
mdefine_line|#define&t;ZORAN_OCR&t;&t;0x024&t;/* Overlay Control */
DECL|macro|ZORAN_OCR_OVLEN
mdefine_line|#define&t;ZORAN_OCR_OVLEN&t;&t;(1&lt;&lt;15)
DECL|macro|ZORAN_OCR_MASKSTRIDE
mdefine_line|#define&t;ZORAN_OCR_MASKSTRIDE&t;(0xFF&lt;&lt;0)
DECL|macro|ZORAN_PCI
mdefine_line|#define&t;ZORAN_PCI&t;&t;0x028&t;/* System, PCI and GPP Control */
DECL|macro|ZORAN_PCI_SOFTRESET
mdefine_line|#define&t;ZORAN_PCI_SOFTRESET&t;(1&lt;&lt;24)
DECL|macro|ZORAN_PCI_WAITSTATE
mdefine_line|#define&t;ZORAN_PCI_WAITSTATE&t;(3&lt;&lt;16)
DECL|macro|ZORAN_PCI_GENPURDIR
mdefine_line|#define&t;ZORAN_PCI_GENPURDIR&t;(0xFF&lt;&lt;0)
DECL|macro|ZORAN_GUEST
mdefine_line|#define&t;ZORAN_GUEST&t;&t;0x02C&t;/* GuestBus Control */
DECL|macro|ZORAN_CSOURCE
mdefine_line|#define&t;ZORAN_CSOURCE&t;&t;0x030&t;/* Code Source Address */
DECL|macro|ZORAN_CTRANS
mdefine_line|#define&t;ZORAN_CTRANS&t;&t;0x034&t;/* Code Transfer Control */
DECL|macro|ZORAN_CMEM
mdefine_line|#define&t;ZORAN_CMEM&t;&t;0x038&t;/* Code Memory Pointer */
DECL|macro|ZORAN_ISR
mdefine_line|#define&t;ZORAN_ISR&t;&t;0x03C&t;/* Interrupt Status Register */
DECL|macro|ZORAN_ISR_CODE
mdefine_line|#define&t;ZORAN_ISR_CODE&t;&t;(1&lt;&lt;28)
DECL|macro|ZORAN_ISR_GIRQ0
mdefine_line|#define&t;ZORAN_ISR_GIRQ0&t;&t;(1&lt;&lt;29)
DECL|macro|ZORAN_ISR_GIRQ1
mdefine_line|#define&t;ZORAN_ISR_GIRQ1&t;&t;(1&lt;&lt;30)
DECL|macro|ZORAN_ICR
mdefine_line|#define&t;ZORAN_ICR&t;&t;0x040&t;/* Interrupt Control Register */
DECL|macro|ZORAN_ICR_EN
mdefine_line|#define&t;ZORAN_ICR_EN&t;&t;(1&lt;&lt;24)
DECL|macro|ZORAN_ICR_CODE
mdefine_line|#define&t;ZORAN_ICR_CODE&t;&t;(1&lt;&lt;28)
DECL|macro|ZORAN_ICR_GIRQ0
mdefine_line|#define&t;ZORAN_ICR_GIRQ0&t;&t;(1&lt;&lt;29)
DECL|macro|ZORAN_ICR_GIRQ1
mdefine_line|#define&t;ZORAN_ICR_GIRQ1&t;&t;(1&lt;&lt;30)
DECL|macro|ZORAN_I2C
mdefine_line|#define&t;ZORAN_I2C&t;&t;0x044&t;/* I2C-Bus */
DECL|macro|ZORAN_I2C_SCL
mdefine_line|#define ZORAN_I2C_SCL&t;&t;(1&lt;&lt;1)
DECL|macro|ZORAN_I2C_SDA
mdefine_line|#define ZORAN_I2C_SDA&t;&t;(1&lt;&lt;0)
DECL|macro|ZORAN_POST
mdefine_line|#define&t;ZORAN_POST&t;&t;0x48&t;/* PostOffice */
DECL|macro|ZORAN_POST_PEN
mdefine_line|#define&t;ZORAN_POST_PEN&t;&t;(1&lt;&lt;25)
DECL|macro|ZORAN_POST_TIME
mdefine_line|#define&t;ZORAN_POST_TIME&t;&t;(1&lt;&lt;24)
DECL|macro|ZORAN_POST_DIR
mdefine_line|#define&t;ZORAN_POST_DIR&t;&t;(1&lt;&lt;23)
DECL|macro|ZORAN_POST_GUESTID
mdefine_line|#define&t;ZORAN_POST_GUESTID&t;(3&lt;&lt;20)
DECL|macro|ZORAN_POST_GUEST
mdefine_line|#define&t;ZORAN_POST_GUEST&t;(7&lt;&lt;16)
DECL|macro|ZORAN_POST_DATA
mdefine_line|#define&t;ZORAN_POST_DATA&t;&t;(0xFF&lt;&lt;0)
macro_line|#endif
eof
