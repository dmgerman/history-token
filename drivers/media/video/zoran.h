multiline_comment|/* &n; * zoran - Iomega Buz driver&n; *&n; * Copyright (C) 1999 Rainer Johanni &lt;Rainer@Johanni.de&gt;&n; *&n; * based on&n; *&n; * zoran.0.0.3 Copyright (C) 1998 Dave Perks &lt;dperks@ibm.net&gt;&n; *&n; * and&n; *&n; * bttv - Bt848 frame grabber driver&n; * Copyright (C) 1996,97,98 Ralph  Metzler (rjkm@thp.uni-koeln.de)&n; *                        &amp; Marcus Metzler (mocm@thp.uni-koeln.de)&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef _BUZ_H_
DECL|macro|_BUZ_H_
mdefine_line|#define _BUZ_H_
DECL|struct|zoran_requestbuffers
r_struct
id|zoran_requestbuffers
(brace
DECL|member|count
r_int
r_int
id|count
suffix:semicolon
multiline_comment|/* Number of buffers for MJPEG grabbing */
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
multiline_comment|/* Size PER BUFFER in bytes */
)brace
suffix:semicolon
DECL|struct|zoran_sync
r_struct
id|zoran_sync
(brace
DECL|member|frame
r_int
r_int
id|frame
suffix:semicolon
multiline_comment|/* number of buffer that has been free&squot;d */
DECL|member|length
r_int
r_int
id|length
suffix:semicolon
multiline_comment|/* number of code bytes in buffer (capture only) */
DECL|member|seq
r_int
r_int
id|seq
suffix:semicolon
multiline_comment|/* frame sequence number */
DECL|member|timestamp
r_struct
id|timeval
id|timestamp
suffix:semicolon
multiline_comment|/* timestamp */
)brace
suffix:semicolon
DECL|struct|zoran_status
r_struct
id|zoran_status
(brace
DECL|member|input
r_int
id|input
suffix:semicolon
multiline_comment|/* Input channel, has to be set prior to BUZIOC_G_STATUS */
DECL|member|signal
r_int
id|signal
suffix:semicolon
multiline_comment|/* Returned: 1 if valid video signal detected */
DECL|member|norm
r_int
id|norm
suffix:semicolon
multiline_comment|/* Returned: VIDEO_MODE_PAL or VIDEO_MODE_NTSC */
DECL|member|color
r_int
id|color
suffix:semicolon
multiline_comment|/* Returned: 1 if color signal detected */
)brace
suffix:semicolon
DECL|struct|zoran_params
r_struct
id|zoran_params
(brace
multiline_comment|/* The following parameters can only be queried */
DECL|member|major_version
r_int
id|major_version
suffix:semicolon
multiline_comment|/* Major version number of driver */
DECL|member|minor_version
r_int
id|minor_version
suffix:semicolon
multiline_comment|/* Minor version number of driver */
multiline_comment|/* Main control parameters */
DECL|member|input
r_int
id|input
suffix:semicolon
multiline_comment|/* Input channel: 0 = Composite, 1 = S-VHS */
DECL|member|norm
r_int
id|norm
suffix:semicolon
multiline_comment|/* Norm: VIDEO_MODE_PAL or VIDEO_MODE_NTSC */
DECL|member|decimation
r_int
id|decimation
suffix:semicolon
multiline_comment|/* decimation of captured video,&n;&t;&t;&t;&t; * enlargement of video played back.&n;&t;&t;&t;&t; * Valid values are 1, 2, 4 or 0.&n;&t;&t;&t;&t; * 0 is a special value where the user&n;&t;&t;&t;&t; * has full control over video scaling */
multiline_comment|/* The following parameters only have to be set if decimation==0,&n;&t; * for other values of decimation they provide the data how the image is captured */
DECL|member|HorDcm
r_int
id|HorDcm
suffix:semicolon
multiline_comment|/* Horizontal decimation: 1, 2 or 4 */
DECL|member|VerDcm
r_int
id|VerDcm
suffix:semicolon
multiline_comment|/* Vertical decimation: 1 or 2 */
DECL|member|TmpDcm
r_int
id|TmpDcm
suffix:semicolon
multiline_comment|/* Temporal decimation: 1 or 2,&n;&t;&t;&t;&t; * if TmpDcm==2 in capture every second frame is dropped,&n;&t;&t;&t;&t; * in playback every frame is played twice */
DECL|member|field_per_buff
r_int
id|field_per_buff
suffix:semicolon
multiline_comment|/* Number of fields per buffer: 1 or 2 */
DECL|member|img_x
r_int
id|img_x
suffix:semicolon
multiline_comment|/* start of image in x direction */
DECL|member|img_y
r_int
id|img_y
suffix:semicolon
multiline_comment|/* start of image in y direction */
DECL|member|img_width
r_int
id|img_width
suffix:semicolon
multiline_comment|/* image width BEFORE decimation,&n;&t;&t;&t;&t; * must be a multiple of HorDcm*16 */
DECL|member|img_height
r_int
id|img_height
suffix:semicolon
multiline_comment|/* image height BEFORE decimation,&n;&t;&t;&t;&t; * must be a multiple of VerDcm*8 */
multiline_comment|/* --- End of parameters for decimation==0 only --- */
multiline_comment|/* JPEG control parameters */
DECL|member|quality
r_int
id|quality
suffix:semicolon
multiline_comment|/* Measure for quality of compressed images.&n;&t;&t;&t;&t; * Scales linearly with the size of the compressed images.&n;&t;&t;&t;&t; * Must be beetween 0 and 100, 100 is a compression&n;&t;&t;&t;&t; * ratio of 1:4 */
DECL|member|odd_even
r_int
id|odd_even
suffix:semicolon
multiline_comment|/* Which field should come first ??? */
DECL|member|APPn
r_int
id|APPn
suffix:semicolon
multiline_comment|/* Number of APP segment to be written, must be 0..15 */
DECL|member|APP_len
r_int
id|APP_len
suffix:semicolon
multiline_comment|/* Length of data in JPEG APPn segment */
DECL|member|APP_data
r_char
id|APP_data
(braket
l_int|60
)braket
suffix:semicolon
multiline_comment|/* Data in the JPEG APPn segment. */
DECL|member|COM_len
r_int
id|COM_len
suffix:semicolon
multiline_comment|/* Length of data in JPEG COM segment */
DECL|member|COM_data
r_char
id|COM_data
(braket
l_int|60
)braket
suffix:semicolon
multiline_comment|/* Data in JPEG COM segment */
DECL|member|jpeg_markers
r_int
r_int
id|jpeg_markers
suffix:semicolon
multiline_comment|/* Which markers should go into the JPEG output.&n;&t;&t;&t;&t;&t; * Unless you exactly know what you do, leave them untouched.&n;&t;&t;&t;&t;&t; * Inluding less markers will make the resulting code&n;&t;&t;&t;&t;&t; * smaller, but there will be fewer aplications&n;&t;&t;&t;&t;&t; * which can read it.&n;&t;&t;&t;&t;&t; * The presence of the APP and COM marker is&n;&t;&t;&t;&t;&t; * influenced by APP0_len and COM_len ONLY! */
DECL|macro|JPEG_MARKER_DHT
mdefine_line|#define JPEG_MARKER_DHT (1&lt;&lt;3)&t;/* Define Huffman Tables */
DECL|macro|JPEG_MARKER_DQT
mdefine_line|#define JPEG_MARKER_DQT (1&lt;&lt;4)&t;/* Define Quantization Tables */
DECL|macro|JPEG_MARKER_DRI
mdefine_line|#define JPEG_MARKER_DRI (1&lt;&lt;5)&t;/* Define Restart Interval */
DECL|macro|JPEG_MARKER_COM
mdefine_line|#define JPEG_MARKER_COM (1&lt;&lt;6)&t;/* Comment segment */
DECL|macro|JPEG_MARKER_APP
mdefine_line|#define JPEG_MARKER_APP (1&lt;&lt;7)&t;/* App segment, driver will allways use APP0 */
DECL|member|VFIFO_FB
r_int
id|VFIFO_FB
suffix:semicolon
multiline_comment|/* Flag for enabling Video Fifo Feedback.&n;&t;&t;&t;&t; * If this flag is turned on and JPEG decompressing&n;&t;&t;&t;&t; * is going to the screen, the decompress process&n;&t;&t;&t;&t; * is stopped every time the Video Fifo is full.&n;&t;&t;&t;&t; * This enables a smooth decompress to the screen&n;&t;&t;&t;&t; * but the video output signal will get scrambled */
multiline_comment|/* Misc */
DECL|member|reserved
r_char
id|reserved
(braket
l_int|312
)braket
suffix:semicolon
multiline_comment|/* Makes 512 bytes for this structure */
)brace
suffix:semicolon
multiline_comment|/*&n;Private IOCTL to set up for displaying MJPEG&n;*/
DECL|macro|BUZIOC_G_PARAMS
mdefine_line|#define BUZIOC_G_PARAMS       _IOR (&squot;v&squot;, BASE_VIDIOCPRIVATE+0,  struct zoran_params)
DECL|macro|BUZIOC_S_PARAMS
mdefine_line|#define BUZIOC_S_PARAMS       _IOWR(&squot;v&squot;, BASE_VIDIOCPRIVATE+1,  struct zoran_params)
DECL|macro|BUZIOC_REQBUFS
mdefine_line|#define BUZIOC_REQBUFS        _IOWR(&squot;v&squot;, BASE_VIDIOCPRIVATE+2,  struct zoran_requestbuffers)
DECL|macro|BUZIOC_QBUF_CAPT
mdefine_line|#define BUZIOC_QBUF_CAPT      _IOW (&squot;v&squot;, BASE_VIDIOCPRIVATE+3,  int)
DECL|macro|BUZIOC_QBUF_PLAY
mdefine_line|#define BUZIOC_QBUF_PLAY      _IOW (&squot;v&squot;, BASE_VIDIOCPRIVATE+4,  int)
DECL|macro|BUZIOC_SYNC
mdefine_line|#define BUZIOC_SYNC           _IOR (&squot;v&squot;, BASE_VIDIOCPRIVATE+5,  struct zoran_sync)
DECL|macro|BUZIOC_G_STATUS
mdefine_line|#define BUZIOC_G_STATUS       _IOWR(&squot;v&squot;, BASE_VIDIOCPRIVATE+6,  struct zoran_status)
macro_line|#ifdef __KERNEL__
DECL|macro|MAJOR_VERSION
mdefine_line|#define MAJOR_VERSION 0&t;&t;/* driver major version */
DECL|macro|MINOR_VERSION
mdefine_line|#define MINOR_VERSION 9&t;&t;/* driver minor version */
DECL|macro|RELEASE_VERSION
mdefine_line|#define RELEASE_VERSION 5&t;/* release version */
DECL|macro|ZORAN_NAME
mdefine_line|#define ZORAN_NAME    &quot;ZORAN&quot;&t;/* name of the device */
DECL|macro|ZR_DEVNAME
mdefine_line|#define ZR_DEVNAME(zr) ((zr)-&gt;name)
DECL|macro|BUZ_MAX_WIDTH
mdefine_line|#define   BUZ_MAX_WIDTH   (zr-&gt;timing-&gt;Wa)
DECL|macro|BUZ_MAX_HEIGHT
mdefine_line|#define   BUZ_MAX_HEIGHT  (zr-&gt;timing-&gt;Ha)
DECL|macro|BUZ_MIN_WIDTH
mdefine_line|#define   BUZ_MIN_WIDTH    32&t;/* never display less than 32 pixels */
DECL|macro|BUZ_MIN_HEIGHT
mdefine_line|#define   BUZ_MIN_HEIGHT   24&t;/* never display less than 24 rows */
DECL|macro|BUZ_NUM_STAT_COM
mdefine_line|#define BUZ_NUM_STAT_COM    4
DECL|macro|BUZ_MASK_STAT_COM
mdefine_line|#define BUZ_MASK_STAT_COM   3
DECL|macro|BUZ_MAX_FRAME
mdefine_line|#define BUZ_MAX_FRAME     256&t;/* Must be a power of 2 */
DECL|macro|BUZ_MASK_FRAME
mdefine_line|#define BUZ_MASK_FRAME    255&t;/* Must be BUZ_MAX_FRAME-1 */
DECL|macro|BUZ_MAX_INPUT
mdefine_line|#define BUZ_MAX_INPUT       8
macro_line|#if VIDEO_MAX_FRAME &lt;= 32
DECL|macro|V4L_MAX_FRAME
macro_line|#   define   V4L_MAX_FRAME   32
macro_line|#elif VIDEO_MAX_FRAME &lt;= 64
DECL|macro|V4L_MAX_FRAME
macro_line|#   define   V4L_MAX_FRAME   64
macro_line|#else
macro_line|#   error   &quot;Too many video frame buffers to handle&quot;
macro_line|#endif
DECL|macro|V4L_MASK_FRAME
mdefine_line|#define   V4L_MASK_FRAME   (V4L_MAX_FRAME - 1)
DECL|macro|MAX_KMALLOC_MEM
mdefine_line|#define MAX_KMALLOC_MEM (128*1024)
macro_line|#include &quot;zr36057.h&quot;
DECL|enum|card_type
r_enum
id|card_type
(brace
DECL|enumerator|UNKNOWN
id|UNKNOWN
op_assign
op_minus
l_int|1
comma
multiline_comment|/* Pinnacle/Miro */
DECL|enumerator|DC10_old
id|DC10_old
comma
multiline_comment|/* DC30 like */
DECL|enumerator|DC10_new
id|DC10_new
comma
multiline_comment|/* DC10plus like */
DECL|enumerator|DC10plus
id|DC10plus
comma
DECL|enumerator|DC30
id|DC30
comma
DECL|enumerator|DC30plus
id|DC30plus
comma
multiline_comment|/* Linux Media Labs */
DECL|enumerator|LML33
id|LML33
comma
DECL|enumerator|LML33R10
id|LML33R10
comma
multiline_comment|/* Iomega */
DECL|enumerator|BUZ
id|BUZ
comma
multiline_comment|/* total number of cards */
DECL|enumerator|NUM_CARDS
id|NUM_CARDS
)brace
suffix:semicolon
DECL|enum|zoran_codec_mode
r_enum
id|zoran_codec_mode
(brace
DECL|enumerator|BUZ_MODE_IDLE
id|BUZ_MODE_IDLE
comma
multiline_comment|/* nothing going on */
DECL|enumerator|BUZ_MODE_MOTION_COMPRESS
id|BUZ_MODE_MOTION_COMPRESS
comma
multiline_comment|/* grabbing frames */
DECL|enumerator|BUZ_MODE_MOTION_DECOMPRESS
id|BUZ_MODE_MOTION_DECOMPRESS
comma
multiline_comment|/* playing frames */
DECL|enumerator|BUZ_MODE_STILL_COMPRESS
id|BUZ_MODE_STILL_COMPRESS
comma
multiline_comment|/* still frame conversion */
DECL|enumerator|BUZ_MODE_STILL_DECOMPRESS
id|BUZ_MODE_STILL_DECOMPRESS
multiline_comment|/* still frame conversion */
)brace
suffix:semicolon
DECL|enum|zoran_buffer_state
r_enum
id|zoran_buffer_state
(brace
DECL|enumerator|BUZ_STATE_USER
id|BUZ_STATE_USER
comma
multiline_comment|/* buffer is owned by application */
DECL|enumerator|BUZ_STATE_PEND
id|BUZ_STATE_PEND
comma
multiline_comment|/* buffer is queued in pend[] ready to feed to I/O */
DECL|enumerator|BUZ_STATE_DMA
id|BUZ_STATE_DMA
comma
multiline_comment|/* buffer is queued in dma[] for I/O */
DECL|enumerator|BUZ_STATE_DONE
id|BUZ_STATE_DONE
multiline_comment|/* buffer is ready to return to application */
)brace
suffix:semicolon
DECL|enum|zoran_map_mode
r_enum
id|zoran_map_mode
(brace
DECL|enumerator|ZORAN_MAP_MODE_RAW
id|ZORAN_MAP_MODE_RAW
comma
DECL|enumerator|ZORAN_MAP_MODE_JPG_REC
id|ZORAN_MAP_MODE_JPG_REC
comma
DECL|macro|ZORAN_MAP_MODE_JPG
mdefine_line|#define ZORAN_MAP_MODE_JPG ZORAN_MAP_MODE_JPG_REC
DECL|enumerator|ZORAN_MAP_MODE_JPG_PLAY
id|ZORAN_MAP_MODE_JPG_PLAY
comma
)brace
suffix:semicolon
DECL|enum|gpio_type
r_enum
id|gpio_type
(brace
DECL|enumerator|GPIO_JPEG_SLEEP
id|GPIO_JPEG_SLEEP
op_assign
l_int|0
comma
DECL|enumerator|GPIO_JPEG_RESET
id|GPIO_JPEG_RESET
comma
DECL|enumerator|GPIO_JPEG_FRAME
id|GPIO_JPEG_FRAME
comma
DECL|enumerator|GPIO_VID_DIR
id|GPIO_VID_DIR
comma
DECL|enumerator|GPIO_VID_EN
id|GPIO_VID_EN
comma
DECL|enumerator|GPIO_VID_RESET
id|GPIO_VID_RESET
comma
DECL|enumerator|GPIO_CLK_SEL1
id|GPIO_CLK_SEL1
comma
DECL|enumerator|GPIO_CLK_SEL2
id|GPIO_CLK_SEL2
comma
DECL|enumerator|GPIO_MAX
id|GPIO_MAX
comma
)brace
suffix:semicolon
DECL|enum|gpcs_type
r_enum
id|gpcs_type
(brace
DECL|enumerator|GPCS_JPEG_RESET
id|GPCS_JPEG_RESET
op_assign
l_int|0
comma
DECL|enumerator|GPCS_JPEG_START
id|GPCS_JPEG_START
comma
DECL|enumerator|GPCS_MAX
id|GPCS_MAX
comma
)brace
suffix:semicolon
DECL|struct|zoran_format
r_struct
id|zoran_format
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
DECL|member|fourcc
id|__u32
id|fourcc
suffix:semicolon
DECL|member|colorspace
r_int
id|colorspace
suffix:semicolon
DECL|member|depth
r_int
id|depth
suffix:semicolon
DECL|member|flags
id|__u32
id|flags
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* flags */
DECL|macro|ZORAN_FORMAT_COMPRESSED
mdefine_line|#define ZORAN_FORMAT_COMPRESSED 1&lt;&lt;0
DECL|macro|ZORAN_FORMAT_OVERLAY
mdefine_line|#define ZORAN_FORMAT_OVERLAY    1&lt;&lt;1
DECL|macro|ZORAN_FORMAT_CAPTURE
mdefine_line|#define ZORAN_FORMAT_CAPTURE&t;1&lt;&lt;2
DECL|macro|ZORAN_FORMAT_PLAYBACK
mdefine_line|#define ZORAN_FORMAT_PLAYBACK&t;1&lt;&lt;3
multiline_comment|/* overlay-settings */
DECL|struct|zoran_overlay_settings
r_struct
id|zoran_overlay_settings
(brace
DECL|member|is_set
r_int
id|is_set
suffix:semicolon
DECL|member|x
DECL|member|y
DECL|member|width
DECL|member|height
r_int
id|x
comma
id|y
comma
id|width
comma
id|height
suffix:semicolon
multiline_comment|/* position */
DECL|member|clipcount
r_int
id|clipcount
suffix:semicolon
multiline_comment|/* position and number of clips */
DECL|member|format
r_const
r_struct
id|zoran_format
op_star
id|format
suffix:semicolon
multiline_comment|/* overlay format */
)brace
suffix:semicolon
multiline_comment|/* v4l-capture settings */
DECL|struct|zoran_v4l_settings
r_struct
id|zoran_v4l_settings
(brace
DECL|member|width
DECL|member|height
DECL|member|bytesperline
r_int
id|width
comma
id|height
comma
id|bytesperline
suffix:semicolon
multiline_comment|/* capture size */
DECL|member|format
r_const
r_struct
id|zoran_format
op_star
id|format
suffix:semicolon
multiline_comment|/* capture format */
)brace
suffix:semicolon
multiline_comment|/* whoops, this one is undeclared if !v4l2 */
macro_line|#ifndef HAVE_V4L2
DECL|struct|v4l2_jpegcompression
r_struct
id|v4l2_jpegcompression
(brace
DECL|member|quality
r_int
id|quality
suffix:semicolon
DECL|member|APPn
r_int
id|APPn
suffix:semicolon
DECL|member|APP_len
r_int
id|APP_len
suffix:semicolon
DECL|member|APP_data
r_char
id|APP_data
(braket
l_int|60
)braket
suffix:semicolon
DECL|member|COM_len
r_int
id|COM_len
suffix:semicolon
DECL|member|COM_data
r_char
id|COM_data
(braket
l_int|60
)braket
suffix:semicolon
DECL|member|jpeg_markers
id|__u32
id|jpeg_markers
suffix:semicolon
DECL|member|reserved
id|__u8
id|reserved
(braket
l_int|116
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/* jpg-capture/-playback settings */
DECL|struct|zoran_jpg_settings
r_struct
id|zoran_jpg_settings
(brace
DECL|member|decimation
r_int
id|decimation
suffix:semicolon
multiline_comment|/* this bit is used to set everything to default */
DECL|member|HorDcm
DECL|member|VerDcm
DECL|member|TmpDcm
r_int
id|HorDcm
comma
id|VerDcm
comma
id|TmpDcm
suffix:semicolon
multiline_comment|/* capture decimation settings (TmpDcm=1 means both fields) */
DECL|member|field_per_buff
DECL|member|odd_even
r_int
id|field_per_buff
comma
id|odd_even
suffix:semicolon
multiline_comment|/* field-settings (odd_even=1 (+TmpDcm=1) means top-field-first) */
DECL|member|img_x
DECL|member|img_y
DECL|member|img_width
DECL|member|img_height
r_int
id|img_x
comma
id|img_y
comma
id|img_width
comma
id|img_height
suffix:semicolon
multiline_comment|/* crop settings (subframe capture) */
DECL|member|jpg_comp
r_struct
id|v4l2_jpegcompression
id|jpg_comp
suffix:semicolon
multiline_comment|/* JPEG-specific capture settings */
)brace
suffix:semicolon
DECL|struct|zoran_mapping
r_struct
id|zoran_mapping
(brace
DECL|member|file
r_struct
id|file
op_star
id|file
suffix:semicolon
DECL|member|count
r_int
id|count
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|zoran_jpg_buffer
r_struct
id|zoran_jpg_buffer
(brace
DECL|member|map
r_struct
id|zoran_mapping
op_star
id|map
suffix:semicolon
DECL|member|frag_tab
id|u32
op_star
id|frag_tab
suffix:semicolon
multiline_comment|/* addresses of frag table */
DECL|member|frag_tab_bus
id|u32
id|frag_tab_bus
suffix:semicolon
multiline_comment|/* same value cached to save time in ISR */
DECL|member|state
r_enum
id|zoran_buffer_state
id|state
suffix:semicolon
multiline_comment|/* non-zero if corresponding buffer is in use in grab queue */
DECL|member|bs
r_struct
id|zoran_sync
id|bs
suffix:semicolon
multiline_comment|/* DONE: info to return to application */
)brace
suffix:semicolon
DECL|struct|zoran_v4l_buffer
r_struct
id|zoran_v4l_buffer
(brace
DECL|member|map
r_struct
id|zoran_mapping
op_star
id|map
suffix:semicolon
DECL|member|fbuffer
r_char
op_star
id|fbuffer
suffix:semicolon
multiline_comment|/* virtual  address of frame buffer */
DECL|member|fbuffer_phys
r_int
r_int
id|fbuffer_phys
suffix:semicolon
multiline_comment|/* physical address of frame buffer */
DECL|member|fbuffer_bus
r_int
r_int
id|fbuffer_bus
suffix:semicolon
multiline_comment|/* bus      address of frame buffer */
DECL|member|state
r_enum
id|zoran_buffer_state
id|state
suffix:semicolon
multiline_comment|/* state: unused/pending/done */
DECL|member|bs
r_struct
id|zoran_sync
id|bs
suffix:semicolon
multiline_comment|/* DONE: info to return to application */
)brace
suffix:semicolon
DECL|enum|zoran_lock_activity
r_enum
id|zoran_lock_activity
(brace
DECL|enumerator|ZORAN_FREE
id|ZORAN_FREE
comma
multiline_comment|/* free for use */
DECL|enumerator|ZORAN_ACTIVE
id|ZORAN_ACTIVE
comma
multiline_comment|/* active but unlocked */
DECL|enumerator|ZORAN_LOCKED
id|ZORAN_LOCKED
comma
multiline_comment|/* locked */
)brace
suffix:semicolon
multiline_comment|/* buffer collections */
DECL|struct|zoran_jpg_struct
r_struct
id|zoran_jpg_struct
(brace
DECL|member|active
r_enum
id|zoran_lock_activity
id|active
suffix:semicolon
multiline_comment|/* feature currently in use? */
DECL|member|buffer
r_struct
id|zoran_jpg_buffer
id|buffer
(braket
id|BUZ_MAX_FRAME
)braket
suffix:semicolon
multiline_comment|/* buffers */
DECL|member|num_buffers
DECL|member|buffer_size
r_int
id|num_buffers
comma
id|buffer_size
suffix:semicolon
DECL|member|allocated
id|u8
id|allocated
suffix:semicolon
multiline_comment|/* Flag if buffers are allocated  */
DECL|member|ready_to_be_freed
id|u8
id|ready_to_be_freed
suffix:semicolon
multiline_comment|/* hack - see zoran_driver.c */
DECL|member|need_contiguous
id|u8
id|need_contiguous
suffix:semicolon
multiline_comment|/* Flag if contiguous buffers are needed */
)brace
suffix:semicolon
DECL|struct|zoran_v4l_struct
r_struct
id|zoran_v4l_struct
(brace
DECL|member|active
r_enum
id|zoran_lock_activity
id|active
suffix:semicolon
multiline_comment|/* feature currently in use? */
DECL|member|buffer
r_struct
id|zoran_v4l_buffer
id|buffer
(braket
id|VIDEO_MAX_FRAME
)braket
suffix:semicolon
multiline_comment|/* buffers */
DECL|member|num_buffers
DECL|member|buffer_size
r_int
id|num_buffers
comma
id|buffer_size
suffix:semicolon
DECL|member|allocated
id|u8
id|allocated
suffix:semicolon
multiline_comment|/* Flag if buffers are allocated  */
DECL|member|ready_to_be_freed
id|u8
id|ready_to_be_freed
suffix:semicolon
multiline_comment|/* hack - see zoran_driver.c */
)brace
suffix:semicolon
r_struct
id|zoran
suffix:semicolon
multiline_comment|/* zoran_fh contains per-open() settings */
DECL|struct|zoran_fh
r_struct
id|zoran_fh
(brace
DECL|member|zr
r_struct
id|zoran
op_star
id|zr
suffix:semicolon
DECL|member|map_mode
r_enum
id|zoran_map_mode
id|map_mode
suffix:semicolon
multiline_comment|/* Flag which bufferset will map by next mmap() */
DECL|member|overlay_settings
r_struct
id|zoran_overlay_settings
id|overlay_settings
suffix:semicolon
DECL|member|overlay_mask
id|u32
op_star
id|overlay_mask
suffix:semicolon
multiline_comment|/* overlay mask */
DECL|member|overlay_active
r_enum
id|zoran_lock_activity
id|overlay_active
suffix:semicolon
multiline_comment|/* feature currently in use? */
DECL|member|v4l_settings
r_struct
id|zoran_v4l_settings
id|v4l_settings
suffix:semicolon
multiline_comment|/* structure with a lot of things to play with */
DECL|member|v4l_buffers
r_struct
id|zoran_v4l_struct
id|v4l_buffers
suffix:semicolon
multiline_comment|/* V4L buffers&squot; info */
DECL|member|jpg_settings
r_struct
id|zoran_jpg_settings
id|jpg_settings
suffix:semicolon
multiline_comment|/* structure with a lot of things to play with */
DECL|member|jpg_buffers
r_struct
id|zoran_jpg_struct
id|jpg_buffers
suffix:semicolon
multiline_comment|/* MJPEG buffers&squot; info */
)brace
suffix:semicolon
DECL|struct|card_info
r_struct
id|card_info
(brace
DECL|member|type
r_enum
id|card_type
id|type
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|i2c_decoder
DECL|member|i2c_encoder
id|u16
id|i2c_decoder
comma
id|i2c_encoder
suffix:semicolon
multiline_comment|/* I2C types */
DECL|member|video_vfe
DECL|member|video_codec
id|u16
id|video_vfe
comma
id|video_codec
suffix:semicolon
multiline_comment|/* videocodec types */
DECL|member|audio_chip
id|u16
id|audio_chip
suffix:semicolon
multiline_comment|/* audio type */
DECL|member|vendor_id
DECL|member|device_id
id|u16
id|vendor_id
comma
id|device_id
suffix:semicolon
multiline_comment|/* subsystem vendor/device ID */
DECL|member|inputs
r_int
id|inputs
suffix:semicolon
multiline_comment|/* number of video inputs */
DECL|struct|input
r_struct
id|input
(brace
DECL|member|muxsel
r_int
id|muxsel
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|input
)brace
id|input
(braket
id|BUZ_MAX_INPUT
)braket
suffix:semicolon
DECL|member|norms
r_int
id|norms
suffix:semicolon
DECL|member|tvn
r_struct
id|tvnorm
op_star
id|tvn
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* supported TV norms */
DECL|member|jpeg_int
id|u32
id|jpeg_int
suffix:semicolon
multiline_comment|/* JPEG interrupt */
DECL|member|vsync_int
id|u32
id|vsync_int
suffix:semicolon
multiline_comment|/* VSYNC interrupt */
DECL|member|gpio
id|s8
id|gpio
(braket
id|GPIO_MAX
)braket
suffix:semicolon
DECL|member|gpcs
id|u8
id|gpcs
(braket
id|GPCS_MAX
)braket
suffix:semicolon
DECL|member|vfe_pol
r_struct
id|vfe_polarity
id|vfe_pol
suffix:semicolon
DECL|member|gpio_pol
id|u8
id|gpio_pol
(braket
id|GPIO_MAX
)braket
suffix:semicolon
multiline_comment|/* is the /GWS line conected? */
DECL|member|gws_not_connected
id|u8
id|gws_not_connected
suffix:semicolon
DECL|member|init
r_void
(paren
op_star
id|init
)paren
(paren
r_struct
id|zoran
op_star
id|zr
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|zoran
r_struct
id|zoran
(brace
DECL|member|video_dev
r_struct
id|video_device
op_star
id|video_dev
suffix:semicolon
DECL|member|i2c_adapter
r_struct
id|i2c_adapter
id|i2c_adapter
suffix:semicolon
multiline_comment|/* */
DECL|member|i2c_algo
r_struct
id|i2c_algo_bit_data
id|i2c_algo
suffix:semicolon
multiline_comment|/* */
DECL|member|i2cbr
id|u32
id|i2cbr
suffix:semicolon
DECL|member|decoder
r_struct
id|i2c_client
op_star
id|decoder
suffix:semicolon
multiline_comment|/* video decoder i2c client */
DECL|member|encoder
r_struct
id|i2c_client
op_star
id|encoder
suffix:semicolon
multiline_comment|/* video encoder i2c client */
DECL|member|codec
r_struct
id|videocodec
op_star
id|codec
suffix:semicolon
multiline_comment|/* video codec */
DECL|member|vfe
r_struct
id|videocodec
op_star
id|vfe
suffix:semicolon
multiline_comment|/* video front end */
DECL|member|resource_lock
r_struct
id|semaphore
id|resource_lock
suffix:semicolon
multiline_comment|/* prevent evil stuff */
DECL|member|initialized
id|u8
id|initialized
suffix:semicolon
multiline_comment|/* flag if zoran has been correctly initalized */
DECL|member|user
r_int
id|user
suffix:semicolon
multiline_comment|/* number of current users */
DECL|member|card
r_struct
id|card_info
id|card
suffix:semicolon
DECL|member|timing
r_struct
id|tvnorm
op_star
id|timing
suffix:semicolon
DECL|member|id
r_int
r_int
id|id
suffix:semicolon
multiline_comment|/* number of this device */
DECL|member|name
r_char
id|name
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* name of this device */
DECL|member|pci_dev
r_struct
id|pci_dev
op_star
id|pci_dev
suffix:semicolon
multiline_comment|/* PCI device */
DECL|member|revision
r_int
r_char
id|revision
suffix:semicolon
multiline_comment|/* revision of zr36057 */
DECL|member|zr36057_adr
r_int
r_int
id|zr36057_adr
suffix:semicolon
multiline_comment|/* bus address of IO mem returned by PCI BIOS */
DECL|member|zr36057_mem
r_int
r_char
id|__iomem
op_star
id|zr36057_mem
suffix:semicolon
multiline_comment|/* pointer to mapped IO memory */
DECL|member|spinlock
id|spinlock_t
id|spinlock
suffix:semicolon
multiline_comment|/* Spinlock */
multiline_comment|/* Video for Linux parameters */
DECL|member|input
DECL|member|norm
r_int
id|input
comma
id|norm
suffix:semicolon
multiline_comment|/* card&squot;s norm and input - norm=VIDEO_MODE_* */
DECL|member|hue
DECL|member|saturation
DECL|member|contrast
DECL|member|brightness
r_int
id|hue
comma
id|saturation
comma
id|contrast
comma
id|brightness
suffix:semicolon
multiline_comment|/* Current picture params */
DECL|member|buffer
r_struct
id|video_buffer
id|buffer
suffix:semicolon
multiline_comment|/* Current buffer params */
DECL|member|overlay_settings
r_struct
id|zoran_overlay_settings
id|overlay_settings
suffix:semicolon
DECL|member|overlay_mask
id|u32
op_star
id|overlay_mask
suffix:semicolon
multiline_comment|/* overlay mask */
DECL|member|overlay_active
r_enum
id|zoran_lock_activity
id|overlay_active
suffix:semicolon
multiline_comment|/* feature currently in use? */
DECL|member|v4l_capq
id|wait_queue_head_t
id|v4l_capq
suffix:semicolon
DECL|member|v4l_overlay_active
r_int
id|v4l_overlay_active
suffix:semicolon
multiline_comment|/* Overlay grab is activated */
DECL|member|v4l_memgrab_active
r_int
id|v4l_memgrab_active
suffix:semicolon
multiline_comment|/* Memory grab is activated */
DECL|member|v4l_grab_frame
r_int
id|v4l_grab_frame
suffix:semicolon
multiline_comment|/* Frame number being currently grabbed */
DECL|macro|NO_GRAB_ACTIVE
mdefine_line|#define NO_GRAB_ACTIVE (-1)
DECL|member|v4l_grab_seq
r_int
r_int
id|v4l_grab_seq
suffix:semicolon
multiline_comment|/* Number of frames grabbed */
DECL|member|v4l_settings
r_struct
id|zoran_v4l_settings
id|v4l_settings
suffix:semicolon
multiline_comment|/* structure with a lot of things to play with */
multiline_comment|/* V4L grab queue of frames pending */
DECL|member|v4l_pend_head
r_int
r_int
id|v4l_pend_head
suffix:semicolon
DECL|member|v4l_pend_tail
r_int
r_int
id|v4l_pend_tail
suffix:semicolon
DECL|member|v4l_sync_tail
r_int
r_int
id|v4l_sync_tail
suffix:semicolon
DECL|member|v4l_pend
r_int
id|v4l_pend
(braket
id|V4L_MAX_FRAME
)braket
suffix:semicolon
DECL|member|v4l_buffers
r_struct
id|zoran_v4l_struct
id|v4l_buffers
suffix:semicolon
multiline_comment|/* V4L buffers&squot; info */
multiline_comment|/* Buz MJPEG parameters */
DECL|member|codec_mode
r_enum
id|zoran_codec_mode
id|codec_mode
suffix:semicolon
multiline_comment|/* status of codec */
DECL|member|jpg_settings
r_struct
id|zoran_jpg_settings
id|jpg_settings
suffix:semicolon
multiline_comment|/* structure with a lot of things to play with */
DECL|member|jpg_capq
id|wait_queue_head_t
id|jpg_capq
suffix:semicolon
multiline_comment|/* wait here for grab to finish */
multiline_comment|/* grab queue counts/indices, mask with BUZ_MASK_STAT_COM before using as index */
multiline_comment|/* (dma_head - dma_tail) is number active in DMA, must be &lt;= BUZ_NUM_STAT_COM */
multiline_comment|/* (value &amp; BUZ_MASK_STAT_COM) corresponds to index in stat_com table */
DECL|member|jpg_que_head
r_int
r_int
id|jpg_que_head
suffix:semicolon
multiline_comment|/* Index where to put next buffer which is queued */
DECL|member|jpg_dma_head
r_int
r_int
id|jpg_dma_head
suffix:semicolon
multiline_comment|/* Index of next buffer which goes into stat_com  */
DECL|member|jpg_dma_tail
r_int
r_int
id|jpg_dma_tail
suffix:semicolon
multiline_comment|/* Index of last buffer in stat_com               */
DECL|member|jpg_que_tail
r_int
r_int
id|jpg_que_tail
suffix:semicolon
multiline_comment|/* Index of last buffer in queue                  */
DECL|member|jpg_seq_num
r_int
r_int
id|jpg_seq_num
suffix:semicolon
multiline_comment|/* count of frames since grab/play started        */
DECL|member|jpg_err_seq
r_int
r_int
id|jpg_err_seq
suffix:semicolon
multiline_comment|/* last seq_num before error                      */
DECL|member|jpg_err_shift
r_int
r_int
id|jpg_err_shift
suffix:semicolon
DECL|member|jpg_queued_num
r_int
r_int
id|jpg_queued_num
suffix:semicolon
multiline_comment|/* count of frames queued since grab/play started */
multiline_comment|/* zr36057&squot;s code buffer table */
DECL|member|stat_com
id|u32
op_star
id|stat_com
suffix:semicolon
multiline_comment|/* stat_com[i] is indexed by dma_head/tail &amp; BUZ_MASK_STAT_COM */
multiline_comment|/* (value &amp; BUZ_MASK_FRAME) corresponds to index in pend[] queue */
DECL|member|jpg_pend
r_int
id|jpg_pend
(braket
id|BUZ_MAX_FRAME
)braket
suffix:semicolon
multiline_comment|/* array indexed by frame number */
DECL|member|jpg_buffers
r_struct
id|zoran_jpg_struct
id|jpg_buffers
suffix:semicolon
multiline_comment|/* MJPEG buffers&squot; info */
multiline_comment|/* Additional stuff for testing */
macro_line|#ifdef CONFIG_PROC_FS
DECL|member|zoran_proc
r_struct
id|proc_dir_entry
op_star
id|zoran_proc
suffix:semicolon
macro_line|#else
DECL|member|zoran_proc
r_void
op_star
id|zoran_proc
suffix:semicolon
macro_line|#endif
DECL|member|testing
r_int
id|testing
suffix:semicolon
DECL|member|jpeg_error
r_int
id|jpeg_error
suffix:semicolon
DECL|member|intr_counter_GIRQ1
r_int
id|intr_counter_GIRQ1
suffix:semicolon
DECL|member|intr_counter_GIRQ0
r_int
id|intr_counter_GIRQ0
suffix:semicolon
DECL|member|intr_counter_CodRepIRQ
r_int
id|intr_counter_CodRepIRQ
suffix:semicolon
DECL|member|intr_counter_JPEGRepIRQ
r_int
id|intr_counter_JPEGRepIRQ
suffix:semicolon
DECL|member|field_counter
r_int
id|field_counter
suffix:semicolon
DECL|member|IRQ1_in
r_int
id|IRQ1_in
suffix:semicolon
DECL|member|IRQ1_out
r_int
id|IRQ1_out
suffix:semicolon
DECL|member|JPEG_in
r_int
id|JPEG_in
suffix:semicolon
DECL|member|JPEG_out
r_int
id|JPEG_out
suffix:semicolon
DECL|member|JPEG_0
r_int
id|JPEG_0
suffix:semicolon
DECL|member|JPEG_1
r_int
id|JPEG_1
suffix:semicolon
DECL|member|END_event_missed
r_int
id|END_event_missed
suffix:semicolon
DECL|member|JPEG_missed
r_int
id|JPEG_missed
suffix:semicolon
DECL|member|JPEG_error
r_int
id|JPEG_error
suffix:semicolon
DECL|member|num_errors
r_int
id|num_errors
suffix:semicolon
DECL|member|JPEG_max_missed
r_int
id|JPEG_max_missed
suffix:semicolon
DECL|member|JPEG_min_missed
r_int
id|JPEG_min_missed
suffix:semicolon
DECL|member|last_isr
id|u32
id|last_isr
suffix:semicolon
DECL|member|frame_num
r_int
r_int
id|frame_num
suffix:semicolon
DECL|member|test_q
id|wait_queue_head_t
id|test_q
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*The following should be done in more portable way. It depends on define&n;  of _ALPHA_BUZ in the Makefile.*/
macro_line|#ifdef _ALPHA_BUZ
DECL|macro|btwrite
mdefine_line|#define btwrite(dat,adr)    writel((dat), zr-&gt;zr36057_adr+(adr))
DECL|macro|btread
mdefine_line|#define btread(adr)         readl(zr-&gt;zr36057_adr+(adr))
macro_line|#else
DECL|macro|btwrite
mdefine_line|#define btwrite(dat,adr)    writel((dat), zr-&gt;zr36057_mem+(adr))
DECL|macro|btread
mdefine_line|#define btread(adr)         readl(zr-&gt;zr36057_mem+(adr))
macro_line|#endif
DECL|macro|btand
mdefine_line|#define btand(dat,adr)      btwrite((dat) &amp; btread(adr), adr)
DECL|macro|btor
mdefine_line|#define btor(dat,adr)       btwrite((dat) | btread(adr), adr)
DECL|macro|btaor
mdefine_line|#define btaor(dat,mask,adr) btwrite((dat) | ((mask) &amp; btread(adr)), adr)
macro_line|#endif&t;&t;&t;&t;/* __kernel__ */
macro_line|#endif
eof
