multiline_comment|/* &n;   buz - Iomega Buz driver&n;&n;   Copyright (C) 1999 Rainer Johanni &lt;Rainer@Johanni.de&gt;&n;&n;   based on&n;&n;   buz.0.0.3 Copyright (C) 1998 Dave Perks &lt;dperks@ibm.net&gt;&n;&n;   and&n;&n;   bttv - Bt848 frame grabber driver&n;   Copyright (C) 1996,97 Ralph Metzler (rjkm@thp.uni-koeln.de)&n;&n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License as published by&n;   the Free Software Foundation; either version 2 of the License, or&n;   (at your option) any later version.&n;&n;   This program is distributed in the hope that it will be useful,&n;   but WITHOUT ANY WARRANTY; without even the implied warranty of&n;   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;   GNU General Public License for more details.&n;&n;   You should have received a copy of the GNU General Public License&n;   along with this program; if not, write to the Free Software&n;   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef _BUZ_H_
DECL|macro|_BUZ_H_
mdefine_line|#define _BUZ_H_
multiline_comment|/* The Buz only supports a maximum width of 720, but some V4L&n;   applications (e.g. xawtv are more happy with 768).&n;   If XAWTV_HACK is defined, we try to fake a device with bigger width */
DECL|macro|XAWTV_HACK
mdefine_line|#define XAWTV_HACK
macro_line|#ifdef XAWTV_HACK
DECL|macro|BUZ_MAX_WIDTH
mdefine_line|#define   BUZ_MAX_WIDTH   768&t;/* never display more than 768 pixels */
macro_line|#else
DECL|macro|BUZ_MAX_WIDTH
mdefine_line|#define   BUZ_MAX_WIDTH   720&t;/* never display more than 720 pixels */
macro_line|#endif
DECL|macro|BUZ_MAX_HEIGHT
mdefine_line|#define   BUZ_MAX_HEIGHT  576&t;/* never display more than 576 rows */
DECL|macro|BUZ_MIN_WIDTH
mdefine_line|#define   BUZ_MIN_WIDTH    32&t;/* never display less than 32 pixels */
DECL|macro|BUZ_MIN_HEIGHT
mdefine_line|#define   BUZ_MIN_HEIGHT   24&t;/* never display less than 24 rows */
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
multiline_comment|/* decimation of captured video,&n;&t;&t;&t;&t;   enlargement of video played back.&n;&t;&t;&t;&t;   Valid values are 1, 2, 4 or 0.&n;&t;&t;&t;&t;   0 is a special value where the user&n;&t;&t;&t;&t;   has full control over video scaling */
multiline_comment|/* The following parameters only have to be set if decimation==0,&n;&t;   for other values of decimation they provide the data how the image is captured */
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
multiline_comment|/* Temporal decimation: 1 or 2,&n;&t;&t;&t;&t;   if TmpDcm==2 in capture every second frame is dropped,&n;&t;&t;&t;&t;   in playback every frame is played twice */
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
multiline_comment|/* image width BEFORE decimation,&n;&t;&t;&t;&t;   must be a multiple of HorDcm*16 */
DECL|member|img_height
r_int
id|img_height
suffix:semicolon
multiline_comment|/* image height BEFORE decimation,&n;&t;&t;&t;&t;   must be a multiple of VerDcm*8 */
multiline_comment|/* --- End of parameters for decimation==0 only --- */
multiline_comment|/* JPEG control parameters */
DECL|member|quality
r_int
id|quality
suffix:semicolon
multiline_comment|/* Measure for quality of compressed images.&n;&t;&t;&t;&t;   Scales linearly with the size of the compressed images.&n;&t;&t;&t;&t;   Must be beetween 0 and 100, 100 is a compression&n;&t;&t;&t;&t;   ratio of 1:4 */
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
multiline_comment|/* Which markers should go into the JPEG output.&n;&t;&t;&t;&t;&t;   Unless you exactly know what you do, leave them untouched.&n;&t;&t;&t;&t;&t;   Inluding less markers will make the resulting code&n;&t;&t;&t;&t;&t;   smaller, but there will be fewer aplications&n;&t;&t;&t;&t;&t;   which can read it.&n;&t;&t;&t;&t;&t;   The presence of the APP and COM marker is&n;&t;&t;&t;&t;&t;   influenced by APP0_len and COM_len ONLY! */
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
multiline_comment|/* Flag for enabling Video Fifo Feedback.&n;&t;&t;&t;&t;   If this flag is turned on and JPEG decompressing&n;&t;&t;&t;&t;   is going to the screen, the decompress process&n;&t;&t;&t;&t;   is stopped every time the Video Fifo is full.&n;&t;&t;&t;&t;   This enables a smooth decompress to the screen&n;&t;&t;&t;&t;   but the video output signal will get scrambled */
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
multiline_comment|/*&n;   Private IOCTL to set up for displaying MJPEG&n; */
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
DECL|macro|BUZ_NUM_STAT_COM
mdefine_line|#define BUZ_NUM_STAT_COM    4
DECL|macro|BUZ_MASK_STAT_COM
mdefine_line|#define BUZ_MASK_STAT_COM   3
DECL|macro|BUZ_MAX_FRAME
mdefine_line|#define BUZ_MAX_FRAME     256&t;/* Must be a power of 2 */
DECL|macro|BUZ_MASK_FRAME
mdefine_line|#define BUZ_MASK_FRAME    255&t;/* Must be BUZ_MAX_FRAME-1 */
macro_line|#if VIDEO_MAX_FRAME &lt;= 32
DECL|macro|V4L_MAX_FRAME
mdefine_line|#define   V4L_MAX_FRAME   32
macro_line|#elif VIDEO_MAX_FRAME &lt;= 64
DECL|macro|V4L_MAX_FRAME
mdefine_line|#define   V4L_MAX_FRAME   64
macro_line|#else
macro_line|#error   &quot;Too many video frame buffers to handle&quot;
macro_line|#endif
DECL|macro|V4L_MASK_FRAME
mdefine_line|#define   V4L_MASK_FRAME   (V4L_MAX_FRAME - 1)
macro_line|#include &quot;zr36057.h&quot;
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
DECL|struct|zoran_gbuffer
r_struct
id|zoran_gbuffer
(brace
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
DECL|struct|v4l_gbuffer
r_struct
id|v4l_gbuffer
(brace
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
DECL|member|i2c
r_struct
id|i2c_bus
id|i2c
suffix:semicolon
DECL|member|initialized
r_int
id|initialized
suffix:semicolon
multiline_comment|/* flag if zoran has been correctly initalized */
DECL|member|user
r_int
id|user
suffix:semicolon
multiline_comment|/* number of current users (0 or 1) */
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
DECL|member|board
r_int
id|board
suffix:semicolon
multiline_comment|/* Board type */
DECL|macro|BOARD_BUZ
mdefine_line|#define BOARD_BUZ&t;&t;0
DECL|macro|BOARD_LML33
mdefine_line|#define BOARD_LML33&t;&t;1&t;
DECL|member|zr36057_adr
r_int
r_int
id|zr36057_adr
suffix:semicolon
multiline_comment|/* bus address of IO mem returned by PCI BIOS */
DECL|member|zr36057_mem
r_int
r_char
op_star
id|zr36057_mem
suffix:semicolon
multiline_comment|/* pointer to mapped IO memory */
DECL|member|map_mjpeg_buffers
r_int
id|map_mjpeg_buffers
suffix:semicolon
multiline_comment|/* Flag which bufferset will map by next mmap() */
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
multiline_comment|/* Spinlock */
multiline_comment|/* Video for Linux parameters */
DECL|member|picture
r_struct
id|video_picture
id|picture
suffix:semicolon
multiline_comment|/* Current picture params */
DECL|member|buffer
r_struct
id|video_buffer
id|buffer
suffix:semicolon
multiline_comment|/* Current buffer params */
DECL|member|window
r_struct
id|video_window
id|window
suffix:semicolon
multiline_comment|/* Current window params */
DECL|member|buffer_set
DECL|member|window_set
r_int
id|buffer_set
comma
id|window_set
suffix:semicolon
multiline_comment|/* Flags if the above structures are set */
DECL|member|video_interlace
r_int
id|video_interlace
suffix:semicolon
multiline_comment|/* Image on screen is interlaced */
DECL|member|overlay_mask
id|u32
op_star
id|overlay_mask
suffix:semicolon
DECL|member|v4l_capq
id|wait_queue_head_t
id|v4l_capq
suffix:semicolon
multiline_comment|/* wait here for grab to finish */
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
id|v4l_grab_seq
suffix:semicolon
multiline_comment|/* Number of frames grabbed */
DECL|member|gwidth
r_int
id|gwidth
suffix:semicolon
multiline_comment|/* Width of current memory capture */
DECL|member|gheight
r_int
id|gheight
suffix:semicolon
multiline_comment|/* Height of current memory capture */
DECL|member|gformat
r_int
id|gformat
suffix:semicolon
multiline_comment|/* Format of ... */
DECL|member|gbpl
r_int
id|gbpl
suffix:semicolon
multiline_comment|/* byte per line of ... */
multiline_comment|/* V4L grab queue of frames pending */
DECL|member|v4l_pend_head
r_int
id|v4l_pend_head
suffix:semicolon
DECL|member|v4l_pend_tail
r_int
id|v4l_pend_tail
suffix:semicolon
DECL|member|v4l_pend
r_int
id|v4l_pend
(braket
id|V4L_MAX_FRAME
)braket
suffix:semicolon
DECL|member|v4l_gbuf
r_struct
id|v4l_gbuffer
id|v4l_gbuf
(braket
id|VIDEO_MAX_FRAME
)braket
suffix:semicolon
multiline_comment|/* V4L   buffers&squot; info */
multiline_comment|/* Buz MJPEG parameters */
DECL|member|jpg_nbufs
r_int
r_int
id|jpg_nbufs
suffix:semicolon
multiline_comment|/* Number of buffers */
DECL|member|jpg_bufsize
r_int
r_int
id|jpg_bufsize
suffix:semicolon
multiline_comment|/* Size of mjpeg buffers in bytes */
DECL|member|jpg_buffers_allocated
r_int
id|jpg_buffers_allocated
suffix:semicolon
multiline_comment|/* Flag if buffers are allocated  */
DECL|member|need_contiguous
r_int
id|need_contiguous
suffix:semicolon
multiline_comment|/* Flag if contiguous buffers are needed */
DECL|member|codec_mode
r_enum
id|zoran_codec_mode
id|codec_mode
suffix:semicolon
multiline_comment|/* status of codec */
DECL|member|params
r_struct
id|zoran_params
id|params
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
multiline_comment|/* count of frames since grab/play started */
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
DECL|member|jpg_gbuf
r_struct
id|zoran_gbuffer
id|jpg_gbuf
(braket
id|BUZ_MAX_FRAME
)braket
suffix:semicolon
multiline_comment|/* MJPEG buffers&squot; info */
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/*The following should be done in more portable way. It depends on define&n;   of _ALPHA_BUZ in the Makefile. */
macro_line|#ifdef _ALPHA_BUZ
DECL|macro|btwrite
mdefine_line|#define btwrite(dat,adr)    writel((dat),(char *) (zr-&gt;zr36057_adr+(adr)))
DECL|macro|btread
mdefine_line|#define btread(adr)         readl(zr-&gt;zr36057_adr+(adr))
macro_line|#else
DECL|macro|btwrite
mdefine_line|#define btwrite(dat,adr)    writel((dat), (char *) (zr-&gt;zr36057_mem+(adr)))
DECL|macro|btread
mdefine_line|#define btread(adr)         readl(zr-&gt;zr36057_mem+(adr))
macro_line|#endif
DECL|macro|btand
mdefine_line|#define btand(dat,adr)      btwrite((dat) &amp; btread(adr), adr)
DECL|macro|btor
mdefine_line|#define btor(dat,adr)       btwrite((dat) | btread(adr), adr)
DECL|macro|btaor
mdefine_line|#define btaor(dat,mask,adr) btwrite((dat) | ((mask) &amp; btread(adr)), adr)
DECL|macro|I2C_TSA5522
mdefine_line|#define I2C_TSA5522        0xc2
DECL|macro|I2C_TDA9850
mdefine_line|#define I2C_TDA9850        0xb6
DECL|macro|I2C_HAUPEE
mdefine_line|#define I2C_HAUPEE         0xa0
DECL|macro|I2C_STBEE
mdefine_line|#define I2C_STBEE          0xae
DECL|macro|I2C_SAA7111
mdefine_line|#define   I2C_SAA7111        0x48
DECL|macro|I2C_SAA7185
mdefine_line|#define   I2C_SAA7185        0x88
DECL|macro|TDA9850_CON1
mdefine_line|#define TDA9850_CON1       0x04
DECL|macro|TDA9850_CON2
mdefine_line|#define TDA9850_CON2       0x05
DECL|macro|TDA9850_CON3
mdefine_line|#define TDA9850_CON3       0x06
DECL|macro|TDA9850_CON4
mdefine_line|#define TDA9850_CON4       0x07
DECL|macro|TDA9850_ALI1
mdefine_line|#define TDA9850_ALI1       0x08
DECL|macro|TDA9850_ALI2
mdefine_line|#define TDA9850_ALI2       0x09
DECL|macro|TDA9850_ALI3
mdefine_line|#define TDA9850_ALI3       0x0a
macro_line|#endif
eof
