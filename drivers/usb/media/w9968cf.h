multiline_comment|/***************************************************************************&n; * Video4Linux driver for W996[87]CF JPEG USB Dual Mode Camera Chip.       *&n; *                                                                         *&n; * Copyright (C) 2002-2004 by Luca Risolia &lt;luca.risolia@studio.unibo.it&gt;  *&n; *                                                                         *&n; * This program is free software; you can redistribute it and/or modify    *&n; * it under the terms of the GNU General Public License as published by    *&n; * the Free Software Foundation; either version 2 of the License, or       *&n; * (at your option) any later version.                                     *&n; *                                                                         *&n; * This program is distributed in the hope that it will be useful,         *&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of          *&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *&n; * GNU General Public License for more details.                            *&n; *                                                                         *&n; * You should have received a copy of the GNU General Public License       *&n; * along with this program; if not, write to the Free Software             *&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.               *&n; ***************************************************************************/
macro_line|#ifndef _W9968CF_H_
DECL|macro|_W9968CF_H_
mdefine_line|#define _W9968CF_H_
macro_line|#include &lt;linux/videodev.h&gt;
macro_line|#include &lt;linux/usb.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/rwsem.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &lt;media/ovcamchip.h&gt;
macro_line|#include &quot;w9968cf_vpp.h&quot;
multiline_comment|/****************************************************************************&n; * Default values                                                           *&n; ****************************************************************************/
DECL|macro|W9968CF_OVMOD_LOAD
mdefine_line|#define W9968CF_OVMOD_LOAD      1  /* automatic &squot;ovcamchip&squot; module loading */
DECL|macro|W9968CF_VPPMOD_LOAD
mdefine_line|#define W9968CF_VPPMOD_LOAD     1  /* automatic &squot;w9968cf-vpp&squot; module loading */
multiline_comment|/* Comment/uncomment the following line to enable/disable debugging messages */
DECL|macro|W9968CF_DEBUG
mdefine_line|#define W9968CF_DEBUG
multiline_comment|/* These have effect only if W9968CF_DEBUG is defined */
DECL|macro|W9968CF_DEBUG_LEVEL
mdefine_line|#define W9968CF_DEBUG_LEVEL    2 /* from 0 to 6. 0 for no debug informations */
DECL|macro|W9968CF_SPECIFIC_DEBUG
mdefine_line|#define W9968CF_SPECIFIC_DEBUG 0 /* 0 or 1 */
DECL|macro|W9968CF_MAX_DEVICES
mdefine_line|#define W9968CF_MAX_DEVICES    32
DECL|macro|W9968CF_SIMCAMS
mdefine_line|#define W9968CF_SIMCAMS        W9968CF_MAX_DEVICES /* simultaneous cameras */
DECL|macro|W9968CF_MAX_BUFFERS
mdefine_line|#define W9968CF_MAX_BUFFERS   32
DECL|macro|W9968CF_BUFFERS
mdefine_line|#define W9968CF_BUFFERS       2 /* n. of frame buffers from 2 to MAX_BUFFERS */
multiline_comment|/* Maximum data payload sizes in bytes for alternate settings */
DECL|variable|wMaxPacketSize
r_static
r_const
id|u16
id|wMaxPacketSize
(braket
)braket
op_assign
(brace
l_int|1023
comma
l_int|959
comma
l_int|895
comma
l_int|831
comma
l_int|767
comma
l_int|703
comma
l_int|639
comma
l_int|575
comma
l_int|511
comma
l_int|447
comma
l_int|383
comma
l_int|319
comma
l_int|255
comma
l_int|191
comma
l_int|127
comma
l_int|63
)brace
suffix:semicolon
DECL|macro|W9968CF_PACKET_SIZE
mdefine_line|#define W9968CF_PACKET_SIZE      1023 /* according to wMaxPacketSizes[] */
DECL|macro|W9968CF_MIN_PACKET_SIZE
mdefine_line|#define W9968CF_MIN_PACKET_SIZE  63 /* minimum value */
DECL|macro|W9968CF_ISO_PACKETS
mdefine_line|#define W9968CF_ISO_PACKETS      5 /* n.of packets for isochronous transfers */
DECL|macro|W9968CF_USB_CTRL_TIMEOUT
mdefine_line|#define W9968CF_USB_CTRL_TIMEOUT HZ /* timeout for usb control commands */
DECL|macro|W9968CF_URBS
mdefine_line|#define W9968CF_URBS             2 /* n. of scheduled URBs for ISO transfer */
DECL|macro|W9968CF_I2C_BUS_DELAY
mdefine_line|#define W9968CF_I2C_BUS_DELAY    4 /* delay in us for I2C bit r/w operations */
DECL|macro|W9968CF_I2C_RW_RETRIES
mdefine_line|#define W9968CF_I2C_RW_RETRIES   15 /* number of max I2C r/w retries */
multiline_comment|/* Available video formats */
DECL|struct|w9968cf_format
r_struct
id|w9968cf_format
(brace
DECL|member|palette
r_const
id|u16
id|palette
suffix:semicolon
DECL|member|depth
r_const
id|u16
id|depth
suffix:semicolon
DECL|member|compression
r_const
id|u8
id|compression
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|w9968cf_formatlist
r_static
r_const
r_struct
id|w9968cf_format
id|w9968cf_formatlist
(braket
)braket
op_assign
(brace
(brace
id|VIDEO_PALETTE_UYVY
comma
l_int|16
comma
l_int|0
)brace
comma
multiline_comment|/* original video */
(brace
id|VIDEO_PALETTE_YUV422P
comma
l_int|16
comma
l_int|1
)brace
comma
multiline_comment|/* with JPEG compression */
(brace
id|VIDEO_PALETTE_YUV420P
comma
l_int|12
comma
l_int|1
)brace
comma
multiline_comment|/* with JPEG compression */
(brace
id|VIDEO_PALETTE_YUV420
comma
l_int|12
comma
l_int|1
)brace
comma
multiline_comment|/* same as YUV420P */
(brace
id|VIDEO_PALETTE_YUYV
comma
l_int|16
comma
l_int|0
)brace
comma
multiline_comment|/* software conversion */
(brace
id|VIDEO_PALETTE_YUV422
comma
l_int|16
comma
l_int|0
)brace
comma
multiline_comment|/* software conversion */
(brace
id|VIDEO_PALETTE_GREY
comma
l_int|8
comma
l_int|0
)brace
comma
multiline_comment|/* software conversion */
(brace
id|VIDEO_PALETTE_RGB555
comma
l_int|16
comma
l_int|0
)brace
comma
multiline_comment|/* software conversion */
(brace
id|VIDEO_PALETTE_RGB565
comma
l_int|16
comma
l_int|0
)brace
comma
multiline_comment|/* software conversion */
(brace
id|VIDEO_PALETTE_RGB24
comma
l_int|24
comma
l_int|0
)brace
comma
multiline_comment|/* software conversion */
(brace
id|VIDEO_PALETTE_RGB32
comma
l_int|32
comma
l_int|0
)brace
comma
multiline_comment|/* software conversion */
(brace
l_int|0
comma
l_int|0
comma
l_int|0
)brace
multiline_comment|/* 0 is a terminating entry */
)brace
suffix:semicolon
DECL|macro|W9968CF_DECOMPRESSION
mdefine_line|#define W9968CF_DECOMPRESSION    2 /* decomp:0=disable,1=force,2=any formats */
DECL|macro|W9968CF_PALETTE_DECOMP_OFF
mdefine_line|#define W9968CF_PALETTE_DECOMP_OFF   VIDEO_PALETTE_UYVY    /* when decomp=0 */
DECL|macro|W9968CF_PALETTE_DECOMP_FORCE
mdefine_line|#define W9968CF_PALETTE_DECOMP_FORCE VIDEO_PALETTE_YUV420P /* when decomp=1 */
DECL|macro|W9968CF_PALETTE_DECOMP_ON
mdefine_line|#define W9968CF_PALETTE_DECOMP_ON    VIDEO_PALETTE_UYVY    /* when decomp=2 */
DECL|macro|W9968CF_FORCE_RGB
mdefine_line|#define W9968CF_FORCE_RGB        0  /* read RGB instead of BGR, yes=1/no=0 */
DECL|macro|W9968CF_MAX_WIDTH
mdefine_line|#define W9968CF_MAX_WIDTH      800 /* Has effect if up-scaling is on */
DECL|macro|W9968CF_MAX_HEIGHT
mdefine_line|#define W9968CF_MAX_HEIGHT     600 /* Has effect if up-scaling is on */
DECL|macro|W9968CF_WIDTH
mdefine_line|#define W9968CF_WIDTH          320 /* from 128 to 352, multiple of 16 */
DECL|macro|W9968CF_HEIGHT
mdefine_line|#define W9968CF_HEIGHT         240 /* from  96 to 288, multiple of 16 */
DECL|macro|W9968CF_CLAMPING
mdefine_line|#define W9968CF_CLAMPING       0 /* 0 disable, 1 enable video data clamping */
DECL|macro|W9968CF_FILTER_TYPE
mdefine_line|#define W9968CF_FILTER_TYPE    0 /* 0 disable  1 (1-2-1), 2 (2-3-6-3-2) */
DECL|macro|W9968CF_DOUBLE_BUFFER
mdefine_line|#define W9968CF_DOUBLE_BUFFER  1 /* 0 disable, 1 enable double buffer */
DECL|macro|W9968CF_LARGEVIEW
mdefine_line|#define W9968CF_LARGEVIEW      1 /* 0 disable, 1 enable */
DECL|macro|W9968CF_UPSCALING
mdefine_line|#define W9968CF_UPSCALING      0 /* 0 disable, 1 enable */
DECL|macro|W9968CF_MONOCHROME
mdefine_line|#define W9968CF_MONOCHROME     0 /* 0 not monochrome, 1 monochrome sensor */
DECL|macro|W9968CF_BRIGHTNESS
mdefine_line|#define W9968CF_BRIGHTNESS     31000 /* from 0 to 65535 */
DECL|macro|W9968CF_HUE
mdefine_line|#define W9968CF_HUE            32768 /* from 0 to 65535 */
DECL|macro|W9968CF_COLOUR
mdefine_line|#define W9968CF_COLOUR         32768 /* from 0 to 65535 */
DECL|macro|W9968CF_CONTRAST
mdefine_line|#define W9968CF_CONTRAST       50000 /* from 0 to 65535 */
DECL|macro|W9968CF_WHITENESS
mdefine_line|#define W9968CF_WHITENESS      32768 /* from 0 to 65535 */
DECL|macro|W9968CF_AUTOBRIGHT
mdefine_line|#define W9968CF_AUTOBRIGHT     0 /* 0 disable, 1 enable automatic brightness */
DECL|macro|W9968CF_AUTOEXP
mdefine_line|#define W9968CF_AUTOEXP        1 /* 0 disable, 1 enable automatic exposure */
DECL|macro|W9968CF_LIGHTFREQ
mdefine_line|#define W9968CF_LIGHTFREQ      50 /* light frequency. 50Hz (Europe) or 60Hz */
DECL|macro|W9968CF_BANDINGFILTER
mdefine_line|#define W9968CF_BANDINGFILTER  0 /* 0 disable, 1 enable banding filter */
DECL|macro|W9968CF_BACKLIGHT
mdefine_line|#define W9968CF_BACKLIGHT      0 /* 0 or 1, 1=object is lit from behind */
DECL|macro|W9968CF_MIRROR
mdefine_line|#define W9968CF_MIRROR         0 /* 0 or 1 [don&squot;t] reverse image horizontally*/
DECL|macro|W9968CF_CLOCKDIV
mdefine_line|#define W9968CF_CLOCKDIV         -1 /* -1 = automatic clock divisor */
DECL|macro|W9968CF_DEF_CLOCKDIVISOR
mdefine_line|#define W9968CF_DEF_CLOCKDIVISOR  0 /* default sensor clock divisor value */
multiline_comment|/****************************************************************************&n; * Globals                                                                  *&n; ****************************************************************************/
DECL|macro|W9968CF_MODULE_NAME
mdefine_line|#define W9968CF_MODULE_NAME     &quot;V4L driver for W996[87]CF JPEG USB &quot; &bslash;&n;                                &quot;Dual Mode Camera Chip&quot;
DECL|macro|W9968CF_MODULE_VERSION
mdefine_line|#define W9968CF_MODULE_VERSION  &quot;1:1.33-basic&quot;
DECL|macro|W9968CF_MODULE_AUTHOR
mdefine_line|#define W9968CF_MODULE_AUTHOR   &quot;(C) 2002-2004 Luca Risolia&quot;
DECL|macro|W9968CF_AUTHOR_EMAIL
mdefine_line|#define W9968CF_AUTHOR_EMAIL    &quot;&lt;luca.risolia@studio.unibo.it&gt;&quot;
DECL|macro|W9968CF_MODULE_LICENSE
mdefine_line|#define W9968CF_MODULE_LICENSE  &quot;GPL&quot;
DECL|variable|winbond_id_table
r_static
r_const
r_struct
id|usb_device_id
id|winbond_id_table
(braket
)braket
op_assign
(brace
(brace
multiline_comment|/* Creative Labs Video Blaster WebCam Go Plus */
id|USB_DEVICE
c_func
(paren
l_int|0x041e
comma
l_int|0x4003
)paren
comma
dot
id|driver_info
op_assign
(paren
r_int
r_int
)paren
l_string|&quot;w9968cf&quot;
comma
)brace
comma
(brace
multiline_comment|/* Generic W996[87]CF JPEG USB Dual Mode Camera */
id|USB_DEVICE
c_func
(paren
l_int|0x1046
comma
l_int|0x9967
)paren
comma
dot
id|driver_info
op_assign
(paren
r_int
r_int
)paren
l_string|&quot;w9968cf&quot;
comma
)brace
comma
(brace
)brace
multiline_comment|/* terminating entry */
)brace
suffix:semicolon
multiline_comment|/* W996[87]CF camera models, internal ids: */
DECL|enum|w9968cf_model_id
r_enum
id|w9968cf_model_id
(brace
DECL|enumerator|W9968CF_MOD_GENERIC
id|W9968CF_MOD_GENERIC
op_assign
l_int|1
comma
multiline_comment|/* Generic W996[87]CF based device */
DECL|enumerator|W9968CF_MOD_CLVBWGP
id|W9968CF_MOD_CLVBWGP
op_assign
l_int|11
comma
multiline_comment|/*Creative Labs Video Blaster WebCam Go Plus*/
DECL|enumerator|W9968CF_MOD_ADPVDMA
id|W9968CF_MOD_ADPVDMA
op_assign
l_int|21
comma
multiline_comment|/* Aroma Digi Pen VGA Dual Mode ADG-5000 */
DECL|enumerator|W9986CF_MOD_AAU
id|W9986CF_MOD_AAU
op_assign
l_int|31
comma
multiline_comment|/* AVerMedia AVerTV USB */
DECL|enumerator|W9968CF_MOD_CLVBWG
id|W9968CF_MOD_CLVBWG
op_assign
l_int|34
comma
multiline_comment|/* Creative Labs Video Blaster WebCam Go */
DECL|enumerator|W9968CF_MOD_LL
id|W9968CF_MOD_LL
op_assign
l_int|37
comma
multiline_comment|/* Lebon LDC-035A */
DECL|enumerator|W9968CF_MOD_EEEMC
id|W9968CF_MOD_EEEMC
op_assign
l_int|40
comma
multiline_comment|/* Ezonics EZ-802 EZMega Cam */
DECL|enumerator|W9968CF_MOD_OOE
id|W9968CF_MOD_OOE
op_assign
l_int|42
comma
multiline_comment|/* OmniVision OV8610-EDE */
DECL|enumerator|W9968CF_MOD_ODPVDMPC
id|W9968CF_MOD_ODPVDMPC
op_assign
l_int|43
comma
multiline_comment|/* OPCOM Digi Pen VGA Dual Mode Pen Camera */
DECL|enumerator|W9968CF_MOD_PDPII
id|W9968CF_MOD_PDPII
op_assign
l_int|46
comma
multiline_comment|/* Pretec Digi Pen-II */
DECL|enumerator|W9968CF_MOD_PDP480
id|W9968CF_MOD_PDP480
op_assign
l_int|49
comma
multiline_comment|/* Pretec DigiPen-480 */
)brace
suffix:semicolon
DECL|enum|w9968cf_frame_status
r_enum
id|w9968cf_frame_status
(brace
DECL|enumerator|F_READY
id|F_READY
comma
multiline_comment|/* finished grabbing &amp; ready to be read/synced */
DECL|enumerator|F_GRABBING
id|F_GRABBING
comma
multiline_comment|/* in the process of being grabbed into */
DECL|enumerator|F_ERROR
id|F_ERROR
comma
multiline_comment|/* something bad happened while processing */
DECL|enumerator|F_UNUSED
id|F_UNUSED
multiline_comment|/* unused (no VIDIOCMCAPTURE) */
)brace
suffix:semicolon
DECL|struct|w9968cf_frame_t
r_struct
id|w9968cf_frame_t
(brace
DECL|member|buffer
r_void
op_star
id|buffer
suffix:semicolon
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
DECL|member|length
id|u32
id|length
suffix:semicolon
DECL|member|number
r_int
id|number
suffix:semicolon
DECL|member|status
r_enum
id|w9968cf_frame_status
id|status
suffix:semicolon
DECL|member|next
r_struct
id|w9968cf_frame_t
op_star
id|next
suffix:semicolon
DECL|member|queued
id|u8
id|queued
suffix:semicolon
)brace
suffix:semicolon
DECL|enum|w9968cf_vpp_flag
r_enum
id|w9968cf_vpp_flag
(brace
DECL|enumerator|VPP_NONE
id|VPP_NONE
op_assign
l_int|0x00
comma
DECL|enumerator|VPP_UPSCALE
id|VPP_UPSCALE
op_assign
l_int|0x01
comma
DECL|enumerator|VPP_SWAP_YUV_BYTES
id|VPP_SWAP_YUV_BYTES
op_assign
l_int|0x02
comma
DECL|enumerator|VPP_DECOMPRESSION
id|VPP_DECOMPRESSION
op_assign
l_int|0x04
comma
DECL|enumerator|VPP_UYVY_TO_RGBX
id|VPP_UYVY_TO_RGBX
op_assign
l_int|0x08
comma
)brace
suffix:semicolon
DECL|variable|w9968cf_vpp
r_static
r_struct
id|w9968cf_vpp_t
op_star
id|w9968cf_vpp
suffix:semicolon
r_static
id|DECLARE_MUTEX
c_func
(paren
id|w9968cf_vppmod_lock
)paren
suffix:semicolon
r_static
id|DECLARE_WAIT_QUEUE_HEAD
c_func
(paren
id|w9968cf_vppmod_wait
)paren
suffix:semicolon
r_static
id|LIST_HEAD
c_func
(paren
id|w9968cf_dev_list
)paren
suffix:semicolon
multiline_comment|/* head of V4L registered cameras list */
r_static
id|DECLARE_MUTEX
c_func
(paren
id|w9968cf_devlist_sem
)paren
suffix:semicolon
multiline_comment|/* semaphore for list traversal */
r_static
id|DECLARE_RWSEM
c_func
(paren
id|w9968cf_disconnect
)paren
suffix:semicolon
multiline_comment|/* prevent races with open() */
multiline_comment|/* Main device driver structure */
DECL|struct|w9968cf_device
r_struct
id|w9968cf_device
(brace
DECL|member|dev
r_struct
id|device
id|dev
suffix:semicolon
multiline_comment|/* device structure */
DECL|member|id
r_enum
id|w9968cf_model_id
id|id
suffix:semicolon
multiline_comment|/* private device identifier */
DECL|member|v4ldev
r_struct
id|video_device
op_star
id|v4ldev
suffix:semicolon
multiline_comment|/* -&gt; V4L structure */
DECL|member|v4llist
r_struct
id|list_head
id|v4llist
suffix:semicolon
multiline_comment|/* entry of the list of V4L cameras */
DECL|member|usbdev
r_struct
id|usb_device
op_star
id|usbdev
suffix:semicolon
multiline_comment|/* -&gt; main USB structure */
DECL|member|urb
r_struct
id|urb
op_star
id|urb
(braket
id|W9968CF_URBS
)braket
suffix:semicolon
multiline_comment|/* -&gt; USB request block structs */
DECL|member|transfer_buffer
r_void
op_star
id|transfer_buffer
(braket
id|W9968CF_URBS
)braket
suffix:semicolon
multiline_comment|/* -&gt; ISO transfer buffers */
DECL|member|control_buffer
id|u16
op_star
id|control_buffer
suffix:semicolon
multiline_comment|/* -&gt; buffer for control req.*/
DECL|member|data_buffer
id|u16
op_star
id|data_buffer
suffix:semicolon
multiline_comment|/* -&gt; data to send to the FSB */
DECL|member|frame
r_struct
id|w9968cf_frame_t
id|frame
(braket
id|W9968CF_MAX_BUFFERS
)braket
suffix:semicolon
DECL|member|frame_tmp
r_struct
id|w9968cf_frame_t
id|frame_tmp
suffix:semicolon
multiline_comment|/* temporary frame */
DECL|member|frame_vpp
r_struct
id|w9968cf_frame_t
id|frame_vpp
suffix:semicolon
multiline_comment|/* helper frame.*/
DECL|member|frame_current
r_struct
id|w9968cf_frame_t
op_star
id|frame_current
suffix:semicolon
multiline_comment|/* -&gt; frame being grabbed */
DECL|member|requested_frame
r_struct
id|w9968cf_frame_t
op_star
id|requested_frame
(braket
id|W9968CF_MAX_BUFFERS
)braket
suffix:semicolon
DECL|member|max_buffers
id|u8
id|max_buffers
comma
multiline_comment|/* number of requested buffers */
DECL|member|force_palette
id|force_palette
comma
multiline_comment|/* yes=1/no=0 */
DECL|member|force_rgb
id|force_rgb
comma
multiline_comment|/* read RGB instead of BGR, yes=1, no=0 */
DECL|member|double_buffer
id|double_buffer
comma
multiline_comment|/* hardware double buffering yes=1/no=0 */
DECL|member|clamping
id|clamping
comma
multiline_comment|/* video data clamping yes=1/no=0 */
DECL|member|filter_type
id|filter_type
comma
multiline_comment|/* 0=disabled, 1=3 tap, 2=5 tap filter */
DECL|member|capture
id|capture
comma
multiline_comment|/* 0=disabled, 1=enabled */
DECL|member|largeview
id|largeview
comma
multiline_comment|/* 0=disabled, 1=enabled */
DECL|member|decompression
id|decompression
comma
multiline_comment|/* 0=disabled, 1=forced, 2=allowed */
DECL|member|upscaling
id|upscaling
suffix:semicolon
multiline_comment|/* software image scaling, 0=enabled, 1=disabled */
DECL|member|picture
r_struct
id|video_picture
id|picture
suffix:semicolon
multiline_comment|/* current picture settings */
DECL|member|window
r_struct
id|video_window
id|window
suffix:semicolon
multiline_comment|/* current window settings */
DECL|member|hw_depth
id|u16
id|hw_depth
comma
multiline_comment|/* depth (used by the chip) */
DECL|member|hw_palette
id|hw_palette
comma
multiline_comment|/* palette (used by the chip) */
DECL|member|hw_width
id|hw_width
comma
multiline_comment|/* width (used by the chip) */
DECL|member|hw_height
id|hw_height
comma
multiline_comment|/* height (used by the chip) */
DECL|member|hs_polarity
id|hs_polarity
comma
multiline_comment|/* 0=negative sync pulse, 1=positive sync pulse */
DECL|member|vs_polarity
id|vs_polarity
comma
multiline_comment|/* 0=negative sync pulse, 1=positive sync pulse */
DECL|member|start_cropx
id|start_cropx
comma
multiline_comment|/* pixels from HS inactive edge to 1st cropped pixel*/
DECL|member|start_cropy
id|start_cropy
suffix:semicolon
multiline_comment|/* pixels from VS inactive edge to 1st cropped pixel*/
DECL|member|vpp_flag
r_enum
id|w9968cf_vpp_flag
id|vpp_flag
suffix:semicolon
multiline_comment|/* post-processing routines in use */
DECL|member|nbuffers
id|u8
id|nbuffers
comma
multiline_comment|/* number of allocated frame buffers */
DECL|member|altsetting
id|altsetting
comma
multiline_comment|/* camera alternate setting */
DECL|member|disconnected
id|disconnected
comma
multiline_comment|/* flag: yes=1, no=0 */
DECL|member|misconfigured
id|misconfigured
comma
multiline_comment|/* flag: yes=1, no=0 */
DECL|member|users
id|users
comma
multiline_comment|/* flag: number of users holding the device */
DECL|member|streaming
id|streaming
suffix:semicolon
multiline_comment|/* flag: yes=1, no=0 */
DECL|member|sensor_initialized
id|u8
id|sensor_initialized
suffix:semicolon
multiline_comment|/* flag: yes=1, no=0 */
multiline_comment|/* Determined by the image sensor type: */
DECL|member|sensor
r_int
id|sensor
comma
multiline_comment|/* type of image sensor chip (CC_*) */
DECL|member|monochrome
id|monochrome
suffix:semicolon
multiline_comment|/* image sensor is (probably) monochrome */
DECL|member|maxwidth
id|u16
id|maxwidth
comma
multiline_comment|/* maximum width supported by the image sensor */
DECL|member|maxheight
id|maxheight
comma
multiline_comment|/* maximum height supported by the image sensor */
DECL|member|minwidth
id|minwidth
comma
multiline_comment|/* minimum width supported by the image sensor */
DECL|member|minheight
id|minheight
suffix:semicolon
multiline_comment|/* minimum height supported by the image sensor */
DECL|member|auto_brt
id|u8
id|auto_brt
comma
multiline_comment|/* auto brightness enabled flag */
DECL|member|auto_exp
id|auto_exp
comma
multiline_comment|/* auto exposure enabled flag */
DECL|member|backlight
id|backlight
comma
multiline_comment|/* backlight exposure algorithm flag */
DECL|member|mirror
id|mirror
comma
multiline_comment|/* image is reversed horizontally */
DECL|member|lightfreq
id|lightfreq
comma
multiline_comment|/* power (lighting) frequency */
DECL|member|bandfilt
id|bandfilt
suffix:semicolon
multiline_comment|/* banding filter enabled flag */
DECL|member|clockdiv
id|s8
id|clockdiv
suffix:semicolon
multiline_comment|/* clock divisor */
multiline_comment|/* I2C interface to kernel */
DECL|member|i2c_adapter
r_struct
id|i2c_adapter
id|i2c_adapter
suffix:semicolon
DECL|member|sensor_client
r_struct
id|i2c_client
op_star
id|sensor_client
suffix:semicolon
multiline_comment|/* Locks */
DECL|member|dev_sem
r_struct
id|semaphore
id|dev_sem
comma
multiline_comment|/* for probe, disconnect,open and close */
DECL|member|fileop_sem
id|fileop_sem
suffix:semicolon
multiline_comment|/* for read and ioctl */
DECL|member|urb_lock
id|spinlock_t
id|urb_lock
comma
multiline_comment|/* for submit_urb() and unlink_urb() */
DECL|member|flist_lock
id|flist_lock
suffix:semicolon
multiline_comment|/* for requested frame list accesses */
DECL|member|open
DECL|member|wait_queue
id|wait_queue_head_t
id|open
comma
id|wait_queue
suffix:semicolon
DECL|member|command
r_char
id|command
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* name of the program holding the device */
)brace
suffix:semicolon
multiline_comment|/****************************************************************************&n; * Macros for debugging                                                     *&n; ****************************************************************************/
DECL|macro|DBG
macro_line|#undef DBG
DECL|macro|KDBG
macro_line|#undef KDBG
macro_line|#ifdef W9968CF_DEBUG
multiline_comment|/* For device specific debugging messages */
DECL|macro|DBG
macro_line|#&t;define DBG(level, fmt, args...)                                       &bslash;&n;{                                                                             &bslash;&n;&t;if ( ((specific_debug) &amp;&amp; (debug == (level))) ||                      &bslash;&n;&t;     ((!specific_debug) &amp;&amp; (debug &gt;= (level))) ) {                    &bslash;&n;&t;&t;if ((level) == 1)                                             &bslash;&n;&t;&t;&t;dev_err(&amp;cam-&gt;dev, fmt &quot;&bslash;n&quot;, ## args);                &bslash;&n;&t;&t;else if ((level) == 2 || (level) == 3)                        &bslash;&n;&t;&t;&t;dev_info(&amp;cam-&gt;dev, fmt &quot;&bslash;n&quot;, ## args);               &bslash;&n;&t;&t;else if ((level) == 4)                                        &bslash;&n;&t;&t;&t;dev_warn(&amp;cam-&gt;dev, fmt &quot;&bslash;n&quot;, ## args);               &bslash;&n;&t;&t;else if ((level) &gt;= 5)                                        &bslash;&n;&t;&t;&t;dev_info(&amp;cam-&gt;dev, &quot;[%s:%d] &quot; fmt &quot;&bslash;n&quot;,              &bslash;&n;&t;&t;&t;         __FUNCTION__, __LINE__ , ## args);           &bslash;&n;&t;}                                                                     &bslash;&n;}
multiline_comment|/* For generic kernel (not device specific) messages */
DECL|macro|KDBG
macro_line|#&t;define KDBG(level, fmt, args...)                                      &bslash;&n;{                                                                             &bslash;&n;&t;if ( ((specific_debug) &amp;&amp; (debug == (level))) ||                      &bslash;&n;&t;     ((!specific_debug) &amp;&amp; (debug &gt;= (level))) ) {                    &bslash;&n;&t;&t;if ((level) &gt;= 1 &amp;&amp; (level) &lt;= 4)                             &bslash;&n;&t;&t;&t;pr_info(&quot;w9968cf: &quot; fmt &quot;&bslash;n&quot;, ## args);               &bslash;&n;&t;&t;else if ((level) &gt;= 5)                                        &bslash;&n;&t;&t;&t;pr_debug(&quot;w9968cf: [%s:%d] &quot; fmt &quot;&bslash;n&quot;, __FUNCTION__,  &bslash;&n;&t;&t;&t;         __LINE__ , ## args);                         &bslash;&n;&t;}                                                                     &bslash;&n;}
macro_line|#else
multiline_comment|/* Not debugging: nothing */
DECL|macro|DBG
macro_line|#&t;define DBG(level, fmt, args...) do {;} while(0);
DECL|macro|KDBG
macro_line|#&t;define KDBG(level, fmt, args...) do {;} while(0);
macro_line|#endif
DECL|macro|PDBG
macro_line|#undef PDBG
DECL|macro|PDBG
mdefine_line|#define PDBG(fmt, args...)                                                    &bslash;&n;dev_info(&amp;cam-&gt;dev, &quot;[%s:%d] &quot; fmt &quot;&bslash;n&quot;, __FUNCTION__, __LINE__ , ## args);
DECL|macro|PDBGG
macro_line|#undef PDBGG
DECL|macro|PDBGG
mdefine_line|#define PDBGG(fmt, args...) do {;} while(0); /* nothing: it&squot;s a placeholder */
macro_line|#endif /* _W9968CF_H_ */
eof
