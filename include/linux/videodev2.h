macro_line|#ifndef __LINUX_VIDEODEV2_H
DECL|macro|__LINUX_VIDEODEV2_H
mdefine_line|#define __LINUX_VIDEODEV2_H
multiline_comment|/*&n; *&t;Video for Linux Two&n; *&n; *&t;Header file for v4l or V4L2 drivers and applications, for&n; *&t;Linux kernels 2.2.x or 2.4.x.&n; *&n; *&t;See http://bytesex.org/v4l/ for API specs and other&n; *&t;v4l2 documentation.&n; *&n; *&t;Author: Bill Dirks &lt;bdirks@pacbell.net&gt;&n; *&t;&t;Justin Schoeman&n; *&t;&t;et al.&n; */
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/time.h&gt; /* need struct timeval */
macro_line|#endif
macro_line|#include &lt;linux/compiler.h&gt; /* need __user */
multiline_comment|/*&n; *&t;M I S C E L L A N E O U S&n; */
multiline_comment|/*  Four-character-code (FOURCC) */
DECL|macro|v4l2_fourcc
mdefine_line|#define v4l2_fourcc(a,b,c,d)&bslash;&n;        (((__u32)(a)&lt;&lt;0)|((__u32)(b)&lt;&lt;8)|((__u32)(c)&lt;&lt;16)|((__u32)(d)&lt;&lt;24))
multiline_comment|/*&n; *&t;E N U M S&n; */
DECL|enum|v4l2_field
r_enum
id|v4l2_field
(brace
DECL|enumerator|V4L2_FIELD_ANY
id|V4L2_FIELD_ANY
op_assign
l_int|0
comma
multiline_comment|/* driver can choose from none,&n;&t;&t;&t;&t;      top, bottom, interlaced&n;&t;&t;&t;&t;      depending on whatever it thinks&n;&t;&t;&t;&t;      is approximate ... */
DECL|enumerator|V4L2_FIELD_NONE
id|V4L2_FIELD_NONE
op_assign
l_int|1
comma
multiline_comment|/* this device has no fields ... */
DECL|enumerator|V4L2_FIELD_TOP
id|V4L2_FIELD_TOP
op_assign
l_int|2
comma
multiline_comment|/* top field only */
DECL|enumerator|V4L2_FIELD_BOTTOM
id|V4L2_FIELD_BOTTOM
op_assign
l_int|3
comma
multiline_comment|/* bottom field only */
DECL|enumerator|V4L2_FIELD_INTERLACED
id|V4L2_FIELD_INTERLACED
op_assign
l_int|4
comma
multiline_comment|/* both fields interlaced */
DECL|enumerator|V4L2_FIELD_SEQ_TB
id|V4L2_FIELD_SEQ_TB
op_assign
l_int|5
comma
multiline_comment|/* both fields sequential into one&n;&t;&t;&t;&t;      buffer, top-bottom order */
DECL|enumerator|V4L2_FIELD_SEQ_BT
id|V4L2_FIELD_SEQ_BT
op_assign
l_int|6
comma
multiline_comment|/* same as above + bottom-top order */
DECL|enumerator|V4L2_FIELD_ALTERNATE
id|V4L2_FIELD_ALTERNATE
op_assign
l_int|7
comma
multiline_comment|/* both fields alternating into&n;&t;&t;&t;&t;      separate buffers */
)brace
suffix:semicolon
DECL|macro|V4L2_FIELD_HAS_TOP
mdefine_line|#define V4L2_FIELD_HAS_TOP(field)&t;&bslash;&n;&t;((field) == V4L2_FIELD_TOP &t;||&bslash;&n;&t; (field) == V4L2_FIELD_INTERLACED ||&bslash;&n;&t; (field) == V4L2_FIELD_SEQ_TB&t;||&bslash;&n;&t; (field) == V4L2_FIELD_SEQ_BT)
DECL|macro|V4L2_FIELD_HAS_BOTTOM
mdefine_line|#define V4L2_FIELD_HAS_BOTTOM(field)&t;&bslash;&n;&t;((field) == V4L2_FIELD_BOTTOM &t;||&bslash;&n;&t; (field) == V4L2_FIELD_INTERLACED ||&bslash;&n;&t; (field) == V4L2_FIELD_SEQ_TB&t;||&bslash;&n;&t; (field) == V4L2_FIELD_SEQ_BT)
DECL|macro|V4L2_FIELD_HAS_BOTH
mdefine_line|#define V4L2_FIELD_HAS_BOTH(field)&t;&bslash;&n;&t;((field) == V4L2_FIELD_INTERLACED ||&bslash;&n;&t; (field) == V4L2_FIELD_SEQ_TB&t;||&bslash;&n;&t; (field) == V4L2_FIELD_SEQ_BT)
DECL|enum|v4l2_buf_type
r_enum
id|v4l2_buf_type
(brace
DECL|enumerator|V4L2_BUF_TYPE_VIDEO_CAPTURE
id|V4L2_BUF_TYPE_VIDEO_CAPTURE
op_assign
l_int|1
comma
DECL|enumerator|V4L2_BUF_TYPE_VIDEO_OUTPUT
id|V4L2_BUF_TYPE_VIDEO_OUTPUT
op_assign
l_int|2
comma
DECL|enumerator|V4L2_BUF_TYPE_VIDEO_OVERLAY
id|V4L2_BUF_TYPE_VIDEO_OVERLAY
op_assign
l_int|3
comma
DECL|enumerator|V4L2_BUF_TYPE_VBI_CAPTURE
id|V4L2_BUF_TYPE_VBI_CAPTURE
op_assign
l_int|4
comma
DECL|enumerator|V4L2_BUF_TYPE_VBI_OUTPUT
id|V4L2_BUF_TYPE_VBI_OUTPUT
op_assign
l_int|5
comma
DECL|enumerator|V4L2_BUF_TYPE_PRIVATE
id|V4L2_BUF_TYPE_PRIVATE
op_assign
l_int|0x80
comma
)brace
suffix:semicolon
DECL|enum|v4l2_ctrl_type
r_enum
id|v4l2_ctrl_type
(brace
DECL|enumerator|V4L2_CTRL_TYPE_INTEGER
id|V4L2_CTRL_TYPE_INTEGER
op_assign
l_int|1
comma
DECL|enumerator|V4L2_CTRL_TYPE_BOOLEAN
id|V4L2_CTRL_TYPE_BOOLEAN
op_assign
l_int|2
comma
DECL|enumerator|V4L2_CTRL_TYPE_MENU
id|V4L2_CTRL_TYPE_MENU
op_assign
l_int|3
comma
DECL|enumerator|V4L2_CTRL_TYPE_BUTTON
id|V4L2_CTRL_TYPE_BUTTON
op_assign
l_int|4
comma
)brace
suffix:semicolon
DECL|enum|v4l2_tuner_type
r_enum
id|v4l2_tuner_type
(brace
DECL|enumerator|V4L2_TUNER_RADIO
id|V4L2_TUNER_RADIO
op_assign
l_int|1
comma
DECL|enumerator|V4L2_TUNER_ANALOG_TV
id|V4L2_TUNER_ANALOG_TV
op_assign
l_int|2
comma
DECL|enumerator|V4L2_TUNER_DIGITAL_TV
id|V4L2_TUNER_DIGITAL_TV
op_assign
l_int|3
comma
)brace
suffix:semicolon
DECL|enum|v4l2_memory
r_enum
id|v4l2_memory
(brace
DECL|enumerator|V4L2_MEMORY_MMAP
id|V4L2_MEMORY_MMAP
op_assign
l_int|1
comma
DECL|enumerator|V4L2_MEMORY_USERPTR
id|V4L2_MEMORY_USERPTR
op_assign
l_int|2
comma
DECL|enumerator|V4L2_MEMORY_OVERLAY
id|V4L2_MEMORY_OVERLAY
op_assign
l_int|3
comma
)brace
suffix:semicolon
multiline_comment|/* see also http://vektor.theorem.ca/graphics/ycbcr/ */
DECL|enum|v4l2_colorspace
r_enum
id|v4l2_colorspace
(brace
multiline_comment|/* ITU-R 601 -- broadcast NTSC/PAL */
DECL|enumerator|V4L2_COLORSPACE_SMPTE170M
id|V4L2_COLORSPACE_SMPTE170M
op_assign
l_int|1
comma
multiline_comment|/* 1125-Line (US) HDTV */
DECL|enumerator|V4L2_COLORSPACE_SMPTE240M
id|V4L2_COLORSPACE_SMPTE240M
op_assign
l_int|2
comma
multiline_comment|/* HD and modern captures. */
DECL|enumerator|V4L2_COLORSPACE_REC709
id|V4L2_COLORSPACE_REC709
op_assign
l_int|3
comma
multiline_comment|/* broken BT878 extents (601, luma range 16-253 instead of 16-235) */
DECL|enumerator|V4L2_COLORSPACE_BT878
id|V4L2_COLORSPACE_BT878
op_assign
l_int|4
comma
multiline_comment|/* These should be useful.  Assume 601 extents. */
DECL|enumerator|V4L2_COLORSPACE_470_SYSTEM_M
id|V4L2_COLORSPACE_470_SYSTEM_M
op_assign
l_int|5
comma
DECL|enumerator|V4L2_COLORSPACE_470_SYSTEM_BG
id|V4L2_COLORSPACE_470_SYSTEM_BG
op_assign
l_int|6
comma
multiline_comment|/* I know there will be cameras that send this.  So, this is&n;&t; * unspecified chromaticities and full 0-255 on each of the&n;&t; * Y&squot;CbCr components&n;&t; */
DECL|enumerator|V4L2_COLORSPACE_JPEG
id|V4L2_COLORSPACE_JPEG
op_assign
l_int|7
comma
multiline_comment|/* For RGB colourspaces, this is probably a good start. */
DECL|enumerator|V4L2_COLORSPACE_SRGB
id|V4L2_COLORSPACE_SRGB
op_assign
l_int|8
comma
)brace
suffix:semicolon
DECL|enum|v4l2_priority
r_enum
id|v4l2_priority
(brace
DECL|enumerator|V4L2_PRIORITY_UNSET
id|V4L2_PRIORITY_UNSET
op_assign
l_int|0
comma
multiline_comment|/* not initialized */
DECL|enumerator|V4L2_PRIORITY_BACKGROUND
id|V4L2_PRIORITY_BACKGROUND
op_assign
l_int|1
comma
DECL|enumerator|V4L2_PRIORITY_INTERACTIVE
id|V4L2_PRIORITY_INTERACTIVE
op_assign
l_int|2
comma
DECL|enumerator|V4L2_PRIORITY_RECORD
id|V4L2_PRIORITY_RECORD
op_assign
l_int|3
comma
DECL|enumerator|V4L2_PRIORITY_DEFAULT
id|V4L2_PRIORITY_DEFAULT
op_assign
id|V4L2_PRIORITY_INTERACTIVE
comma
)brace
suffix:semicolon
DECL|struct|v4l2_rect
r_struct
id|v4l2_rect
(brace
DECL|member|left
id|__s32
id|left
suffix:semicolon
DECL|member|top
id|__s32
id|top
suffix:semicolon
DECL|member|width
id|__s32
id|width
suffix:semicolon
DECL|member|height
id|__s32
id|height
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|v4l2_fract
r_struct
id|v4l2_fract
(brace
DECL|member|numerator
id|__u32
id|numerator
suffix:semicolon
DECL|member|denominator
id|__u32
id|denominator
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;D R I V E R   C A P A B I L I T I E S&n; */
DECL|struct|v4l2_capability
r_struct
id|v4l2_capability
(brace
DECL|member|driver
id|__u8
id|driver
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* i.e. &quot;bttv&quot; */
DECL|member|card
id|__u8
id|card
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* i.e. &quot;Hauppauge WinTV&quot; */
DECL|member|bus_info
id|__u8
id|bus_info
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* &quot;PCI:&quot; + pci_name(pci_dev) */
DECL|member|version
id|__u32
id|version
suffix:semicolon
multiline_comment|/* should use KERNEL_VERSION() */
DECL|member|capabilities
id|__u32
id|capabilities
suffix:semicolon
multiline_comment|/* Device capabilities */
DECL|member|reserved
id|__u32
id|reserved
(braket
l_int|4
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Values for &squot;capabilities&squot; field */
DECL|macro|V4L2_CAP_VIDEO_CAPTURE
mdefine_line|#define V4L2_CAP_VIDEO_CAPTURE&t;0x00000001  /* Is a video capture device */
DECL|macro|V4L2_CAP_VIDEO_OUTPUT
mdefine_line|#define V4L2_CAP_VIDEO_OUTPUT&t;0x00000002  /* Is a video output device */
DECL|macro|V4L2_CAP_VIDEO_OVERLAY
mdefine_line|#define V4L2_CAP_VIDEO_OVERLAY&t;0x00000004  /* Can do video overlay */
DECL|macro|V4L2_CAP_VBI_CAPTURE
mdefine_line|#define V4L2_CAP_VBI_CAPTURE&t;0x00000010  /* Is a VBI capture device */
DECL|macro|V4L2_CAP_VBI_OUTPUT
mdefine_line|#define V4L2_CAP_VBI_OUTPUT&t;0x00000020  /* Is a VBI output device */
DECL|macro|V4L2_CAP_RDS_CAPTURE
mdefine_line|#define V4L2_CAP_RDS_CAPTURE&t;0x00000100  /* RDS data capture */
DECL|macro|V4L2_CAP_TUNER
mdefine_line|#define V4L2_CAP_TUNER&t;&t;0x00010000  /* has a tuner */
DECL|macro|V4L2_CAP_AUDIO
mdefine_line|#define V4L2_CAP_AUDIO&t;&t;0x00020000  /* has audio support */
DECL|macro|V4L2_CAP_RADIO
mdefine_line|#define V4L2_CAP_RADIO&t;&t;0x00040000  /* is a radio device */
DECL|macro|V4L2_CAP_READWRITE
mdefine_line|#define V4L2_CAP_READWRITE      0x01000000  /* read/write systemcalls */
DECL|macro|V4L2_CAP_ASYNCIO
mdefine_line|#define V4L2_CAP_ASYNCIO        0x02000000  /* async I/O */
DECL|macro|V4L2_CAP_STREAMING
mdefine_line|#define V4L2_CAP_STREAMING      0x04000000  /* streaming I/O ioctls */
multiline_comment|/*&n; *&t;V I D E O   I M A G E   F O R M A T&n; */
DECL|struct|v4l2_pix_format
r_struct
id|v4l2_pix_format
(brace
DECL|member|width
id|__u32
id|width
suffix:semicolon
DECL|member|height
id|__u32
id|height
suffix:semicolon
DECL|member|pixelformat
id|__u32
id|pixelformat
suffix:semicolon
DECL|member|field
r_enum
id|v4l2_field
id|field
suffix:semicolon
DECL|member|bytesperline
id|__u32
id|bytesperline
suffix:semicolon
multiline_comment|/* for padding, zero if unused */
DECL|member|sizeimage
id|__u32
id|sizeimage
suffix:semicolon
DECL|member|colorspace
r_enum
id|v4l2_colorspace
id|colorspace
suffix:semicolon
DECL|member|priv
id|__u32
id|priv
suffix:semicolon
multiline_comment|/* private data, depends on pixelformat */
)brace
suffix:semicolon
multiline_comment|/*           Pixel format    FOURCC                  depth  Description   */
DECL|macro|V4L2_PIX_FMT_RGB332
mdefine_line|#define V4L2_PIX_FMT_RGB332  v4l2_fourcc(&squot;R&squot;,&squot;G&squot;,&squot;B&squot;,&squot;1&squot;) /*  8  RGB-3-3-2     */
DECL|macro|V4L2_PIX_FMT_RGB555
mdefine_line|#define V4L2_PIX_FMT_RGB555  v4l2_fourcc(&squot;R&squot;,&squot;G&squot;,&squot;B&squot;,&squot;O&squot;) /* 16  RGB-5-5-5     */
DECL|macro|V4L2_PIX_FMT_RGB565
mdefine_line|#define V4L2_PIX_FMT_RGB565  v4l2_fourcc(&squot;R&squot;,&squot;G&squot;,&squot;B&squot;,&squot;P&squot;) /* 16  RGB-5-6-5     */
DECL|macro|V4L2_PIX_FMT_RGB555X
mdefine_line|#define V4L2_PIX_FMT_RGB555X v4l2_fourcc(&squot;R&squot;,&squot;G&squot;,&squot;B&squot;,&squot;Q&squot;) /* 16  RGB-5-5-5 BE  */
DECL|macro|V4L2_PIX_FMT_RGB565X
mdefine_line|#define V4L2_PIX_FMT_RGB565X v4l2_fourcc(&squot;R&squot;,&squot;G&squot;,&squot;B&squot;,&squot;R&squot;) /* 16  RGB-5-6-5 BE  */
DECL|macro|V4L2_PIX_FMT_BGR24
mdefine_line|#define V4L2_PIX_FMT_BGR24   v4l2_fourcc(&squot;B&squot;,&squot;G&squot;,&squot;R&squot;,&squot;3&squot;) /* 24  BGR-8-8-8     */
DECL|macro|V4L2_PIX_FMT_RGB24
mdefine_line|#define V4L2_PIX_FMT_RGB24   v4l2_fourcc(&squot;R&squot;,&squot;G&squot;,&squot;B&squot;,&squot;3&squot;) /* 24  RGB-8-8-8     */
DECL|macro|V4L2_PIX_FMT_BGR32
mdefine_line|#define V4L2_PIX_FMT_BGR32   v4l2_fourcc(&squot;B&squot;,&squot;G&squot;,&squot;R&squot;,&squot;4&squot;) /* 32  BGR-8-8-8-8   */
DECL|macro|V4L2_PIX_FMT_RGB32
mdefine_line|#define V4L2_PIX_FMT_RGB32   v4l2_fourcc(&squot;R&squot;,&squot;G&squot;,&squot;B&squot;,&squot;4&squot;) /* 32  RGB-8-8-8-8   */
DECL|macro|V4L2_PIX_FMT_GREY
mdefine_line|#define V4L2_PIX_FMT_GREY    v4l2_fourcc(&squot;G&squot;,&squot;R&squot;,&squot;E&squot;,&squot;Y&squot;) /*  8  Greyscale     */
DECL|macro|V4L2_PIX_FMT_YVU410
mdefine_line|#define V4L2_PIX_FMT_YVU410  v4l2_fourcc(&squot;Y&squot;,&squot;V&squot;,&squot;U&squot;,&squot;9&squot;) /*  9  YVU 4:1:0     */
DECL|macro|V4L2_PIX_FMT_YVU420
mdefine_line|#define V4L2_PIX_FMT_YVU420  v4l2_fourcc(&squot;Y&squot;,&squot;V&squot;,&squot;1&squot;,&squot;2&squot;) /* 12  YVU 4:2:0     */
DECL|macro|V4L2_PIX_FMT_YUYV
mdefine_line|#define V4L2_PIX_FMT_YUYV    v4l2_fourcc(&squot;Y&squot;,&squot;U&squot;,&squot;Y&squot;,&squot;V&squot;) /* 16  YUV 4:2:2     */
DECL|macro|V4L2_PIX_FMT_UYVY
mdefine_line|#define V4L2_PIX_FMT_UYVY    v4l2_fourcc(&squot;U&squot;,&squot;Y&squot;,&squot;V&squot;,&squot;Y&squot;) /* 16  YUV 4:2:2     */
DECL|macro|V4L2_PIX_FMT_YUV422P
mdefine_line|#define V4L2_PIX_FMT_YUV422P v4l2_fourcc(&squot;4&squot;,&squot;2&squot;,&squot;2&squot;,&squot;P&squot;) /* 16  YVU422 planar */
DECL|macro|V4L2_PIX_FMT_YUV411P
mdefine_line|#define V4L2_PIX_FMT_YUV411P v4l2_fourcc(&squot;4&squot;,&squot;1&squot;,&squot;1&squot;,&squot;P&squot;) /* 16  YVU411 planar */
DECL|macro|V4L2_PIX_FMT_Y41P
mdefine_line|#define V4L2_PIX_FMT_Y41P    v4l2_fourcc(&squot;Y&squot;,&squot;4&squot;,&squot;1&squot;,&squot;P&squot;) /* 12  YUV 4:1:1     */
multiline_comment|/* two planes -- one Y, one Cr + Cb interleaved  */
DECL|macro|V4L2_PIX_FMT_NV12
mdefine_line|#define V4L2_PIX_FMT_NV12    v4l2_fourcc(&squot;N&squot;,&squot;V&squot;,&squot;1&squot;,&squot;2&squot;) /* 12  Y/CbCr 4:2:0  */
DECL|macro|V4L2_PIX_FMT_NV21
mdefine_line|#define V4L2_PIX_FMT_NV21    v4l2_fourcc(&squot;N&squot;,&squot;V&squot;,&squot;2&squot;,&squot;1&squot;) /* 12  Y/CrCb 4:2:0  */
multiline_comment|/*  The following formats are not defined in the V4L2 specification */
DECL|macro|V4L2_PIX_FMT_YUV410
mdefine_line|#define V4L2_PIX_FMT_YUV410  v4l2_fourcc(&squot;Y&squot;,&squot;U&squot;,&squot;V&squot;,&squot;9&squot;) /*  9  YUV 4:1:0     */
DECL|macro|V4L2_PIX_FMT_YUV420
mdefine_line|#define V4L2_PIX_FMT_YUV420  v4l2_fourcc(&squot;Y&squot;,&squot;U&squot;,&squot;1&squot;,&squot;2&squot;) /* 12  YUV 4:2:0     */
DECL|macro|V4L2_PIX_FMT_YYUV
mdefine_line|#define V4L2_PIX_FMT_YYUV    v4l2_fourcc(&squot;Y&squot;,&squot;Y&squot;,&squot;U&squot;,&squot;V&squot;) /* 16  YUV 4:2:2     */
DECL|macro|V4L2_PIX_FMT_HI240
mdefine_line|#define V4L2_PIX_FMT_HI240   v4l2_fourcc(&squot;H&squot;,&squot;I&squot;,&squot;2&squot;,&squot;4&squot;) /*  8  8-bit color   */
multiline_comment|/* see http://www.siliconimaging.com/RGB%20Bayer.htm */
DECL|macro|V4L2_PIX_FMT_SBGGR8
mdefine_line|#define V4L2_PIX_FMT_SBGGR8  v4l2_fourcc(&squot;B&squot;,&squot;A&squot;,&squot;8&squot;,&squot;1&squot;) /*  8  BGBG.. GRGR.. */
multiline_comment|/* compressed formats */
DECL|macro|V4L2_PIX_FMT_MJPEG
mdefine_line|#define V4L2_PIX_FMT_MJPEG    v4l2_fourcc(&squot;M&squot;,&squot;J&squot;,&squot;P&squot;,&squot;G&squot;) /* Motion-JPEG   */
DECL|macro|V4L2_PIX_FMT_JPEG
mdefine_line|#define V4L2_PIX_FMT_JPEG     v4l2_fourcc(&squot;J&squot;,&squot;P&squot;,&squot;E&squot;,&squot;G&squot;) /* JFIF JPEG     */
DECL|macro|V4L2_PIX_FMT_DV
mdefine_line|#define V4L2_PIX_FMT_DV       v4l2_fourcc(&squot;d&squot;,&squot;v&squot;,&squot;s&squot;,&squot;d&squot;) /* 1394          */
DECL|macro|V4L2_PIX_FMT_MPEG
mdefine_line|#define V4L2_PIX_FMT_MPEG     v4l2_fourcc(&squot;M&squot;,&squot;P&squot;,&squot;E&squot;,&squot;G&squot;) /* MPEG          */
multiline_comment|/*  Vendor-specific formats   */
DECL|macro|V4L2_PIX_FMT_WNVA
mdefine_line|#define V4L2_PIX_FMT_WNVA     v4l2_fourcc(&squot;W&squot;,&squot;N&squot;,&squot;V&squot;,&squot;A&squot;) /* Winnov hw compress */
DECL|macro|V4L2_PIX_FMT_SN9C10X
mdefine_line|#define V4L2_PIX_FMT_SN9C10X  v4l2_fourcc(&squot;S&squot;,&squot;9&squot;,&squot;1&squot;,&squot;0&squot;) /* SN9C10x compression */
multiline_comment|/*&n; *&t;F O R M A T   E N U M E R A T I O N&n; */
DECL|struct|v4l2_fmtdesc
r_struct
id|v4l2_fmtdesc
(brace
DECL|member|index
id|__u32
id|index
suffix:semicolon
multiline_comment|/* Format number      */
DECL|member|type
r_enum
id|v4l2_buf_type
id|type
suffix:semicolon
multiline_comment|/* buffer type        */
DECL|member|flags
id|__u32
id|flags
suffix:semicolon
DECL|member|description
id|__u8
id|description
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* Description string */
DECL|member|pixelformat
id|__u32
id|pixelformat
suffix:semicolon
multiline_comment|/* Format fourcc      */
DECL|member|reserved
id|__u32
id|reserved
(braket
l_int|4
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|V4L2_FMT_FLAG_COMPRESSED
mdefine_line|#define V4L2_FMT_FLAG_COMPRESSED 0x0001
multiline_comment|/*&n; *&t;T I M E C O D E&n; */
DECL|struct|v4l2_timecode
r_struct
id|v4l2_timecode
(brace
DECL|member|type
id|__u32
id|type
suffix:semicolon
DECL|member|flags
id|__u32
id|flags
suffix:semicolon
DECL|member|frames
id|__u8
id|frames
suffix:semicolon
DECL|member|seconds
id|__u8
id|seconds
suffix:semicolon
DECL|member|minutes
id|__u8
id|minutes
suffix:semicolon
DECL|member|hours
id|__u8
id|hours
suffix:semicolon
DECL|member|userbits
id|__u8
id|userbits
(braket
l_int|4
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*  Type  */
DECL|macro|V4L2_TC_TYPE_24FPS
mdefine_line|#define V4L2_TC_TYPE_24FPS&t;&t;1
DECL|macro|V4L2_TC_TYPE_25FPS
mdefine_line|#define V4L2_TC_TYPE_25FPS&t;&t;2
DECL|macro|V4L2_TC_TYPE_30FPS
mdefine_line|#define V4L2_TC_TYPE_30FPS&t;&t;3
DECL|macro|V4L2_TC_TYPE_50FPS
mdefine_line|#define V4L2_TC_TYPE_50FPS&t;&t;4
DECL|macro|V4L2_TC_TYPE_60FPS
mdefine_line|#define V4L2_TC_TYPE_60FPS&t;&t;5
multiline_comment|/*  Flags  */
DECL|macro|V4L2_TC_FLAG_DROPFRAME
mdefine_line|#define V4L2_TC_FLAG_DROPFRAME&t;&t;0x0001 /* &quot;drop-frame&quot; mode */
DECL|macro|V4L2_TC_FLAG_COLORFRAME
mdefine_line|#define V4L2_TC_FLAG_COLORFRAME&t;&t;0x0002
DECL|macro|V4L2_TC_USERBITS_field
mdefine_line|#define V4L2_TC_USERBITS_field&t;&t;0x000C
DECL|macro|V4L2_TC_USERBITS_USERDEFINED
mdefine_line|#define V4L2_TC_USERBITS_USERDEFINED&t;0x0000
DECL|macro|V4L2_TC_USERBITS_8BITCHARS
mdefine_line|#define V4L2_TC_USERBITS_8BITCHARS&t;0x0008
multiline_comment|/* The above is based on SMPTE timecodes */
multiline_comment|/*&n; *&t;C O M P R E S S I O N   P A R A M E T E R S&n; */
macro_line|#if 0
multiline_comment|/* ### generic compression settings don&squot;t work, there is too much&n; * ### codec-specific stuff.  Maybe reuse that for MPEG codec settings&n; * ### later ... */
r_struct
id|v4l2_compression
(brace
id|__u32
id|quality
suffix:semicolon
id|__u32
id|keyframerate
suffix:semicolon
id|__u32
id|pframerate
suffix:semicolon
id|__u32
id|reserved
(braket
l_int|5
)braket
suffix:semicolon
multiline_comment|/*  what we&squot;ll need for MPEG, extracted from some postings on&n;    the v4l list (Gert Vervoort, PlasmaJohn).&n;&n;system stream:&n;  - type: elementary stream(ES), packatised elementary stream(s) (PES)&n;    program stream(PS), transport stream(TS)&n;  - system bitrate&n;  - PS packet size (DVD: 2048 bytes, VCD: 2324 bytes)&n;  - TS video PID&n;  - TS audio PID&n;  - TS PCR PID&n;  - TS system information tables (PAT, PMT, CAT, NIT and SIT)&n;  - (MPEG-1 systems stream vs. MPEG-2 program stream (TS not supported&n;    by MPEG-1 systems)&n;&n;audio:&n;  - type: MPEG (+Layer I,II,III), AC-3, LPCM&n;  - bitrate&n;  - sampling frequency (DVD: 48 Khz, VCD: 44.1 KHz, 32 kHz)&n;  - Trick Modes? (ff, rew)&n;  - Copyright&n;  - Inverse Telecine&n;&n;video:&n;  - picturesize (SIF, 1/2 D1, 2/3 D1, D1) and PAL/NTSC norm can be set&n;    through excisting V4L2 controls&n;  - noise reduction, parameters encoder specific?&n;  - MPEG video version: MPEG-1, MPEG-2&n;  - GOP (Group Of Pictures) definition:&n;    - N: number of frames per GOP&n;    - M: distance between reference (I,P) frames&n;    - open/closed GOP&n;  - quantiser matrix: inter Q matrix (64 bytes) and intra Q matrix (64 bytes)&n;  - quantiser scale: linear or logarithmic&n;  - scanning: alternate or zigzag&n;  - bitrate mode: CBR (constant bitrate) or VBR (variable bitrate).&n;  - target video bitrate for CBR&n;  - target video bitrate for VBR&n;  - maximum video bitrate for VBR - min. quantiser value for VBR&n;  - max. quantiser value for VBR&n;  - adaptive quantisation value&n;  - return the number of bytes per GOP or bitrate for bitrate monitoring&n;&n;*/
)brace
suffix:semicolon
macro_line|#endif
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
multiline_comment|/* Number of APP segment to be written,&n;&t;&t;&t;&t; * must be 0..15 */
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
id|__u32
id|jpeg_markers
suffix:semicolon
multiline_comment|/* Which markers should go into the JPEG&n;&t;&t;&t;&t; * output. Unless you exactly know what&n;&t;&t;&t;&t; * you do, leave them untouched.&n;&t;&t;&t;&t; * Inluding less markers will make the&n;&t;&t;&t;&t; * resulting code smaller, but there will&n;&t;&t;&t;&t; * be fewer aplications which can read it.&n;&t;&t;&t;&t; * The presence of the APP and COM marker&n;&t;&t;&t;&t; * is influenced by APP_len and COM_len&n;&t;&t;&t;&t; * ONLY, not by this property! */
DECL|macro|V4L2_JPEG_MARKER_DHT
mdefine_line|#define V4L2_JPEG_MARKER_DHT (1&lt;&lt;3)    /* Define Huffman Tables */
DECL|macro|V4L2_JPEG_MARKER_DQT
mdefine_line|#define V4L2_JPEG_MARKER_DQT (1&lt;&lt;4)    /* Define Quantization Tables */
DECL|macro|V4L2_JPEG_MARKER_DRI
mdefine_line|#define V4L2_JPEG_MARKER_DRI (1&lt;&lt;5)    /* Define Restart Interval */
DECL|macro|V4L2_JPEG_MARKER_COM
mdefine_line|#define V4L2_JPEG_MARKER_COM (1&lt;&lt;6)    /* Comment segment */
DECL|macro|V4L2_JPEG_MARKER_APP
mdefine_line|#define V4L2_JPEG_MARKER_APP (1&lt;&lt;7)    /* App segment, driver will&n;                                        * allways use APP0 */
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;M E M O R Y - M A P P I N G   B U F F E R S&n; */
DECL|struct|v4l2_requestbuffers
r_struct
id|v4l2_requestbuffers
(brace
DECL|member|count
id|__u32
id|count
suffix:semicolon
DECL|member|type
r_enum
id|v4l2_buf_type
id|type
suffix:semicolon
DECL|member|memory
r_enum
id|v4l2_memory
id|memory
suffix:semicolon
DECL|member|reserved
id|__u32
id|reserved
(braket
l_int|2
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|v4l2_buffer
r_struct
id|v4l2_buffer
(brace
DECL|member|index
id|__u32
id|index
suffix:semicolon
DECL|member|type
r_enum
id|v4l2_buf_type
id|type
suffix:semicolon
DECL|member|bytesused
id|__u32
id|bytesused
suffix:semicolon
DECL|member|flags
id|__u32
id|flags
suffix:semicolon
DECL|member|field
r_enum
id|v4l2_field
id|field
suffix:semicolon
DECL|member|timestamp
r_struct
id|timeval
id|timestamp
suffix:semicolon
DECL|member|timecode
r_struct
id|v4l2_timecode
id|timecode
suffix:semicolon
DECL|member|sequence
id|__u32
id|sequence
suffix:semicolon
multiline_comment|/* memory location */
DECL|member|memory
r_enum
id|v4l2_memory
id|memory
suffix:semicolon
r_union
(brace
DECL|member|offset
id|__u32
id|offset
suffix:semicolon
DECL|member|userptr
r_int
r_int
id|userptr
suffix:semicolon
DECL|member|m
)brace
id|m
suffix:semicolon
DECL|member|length
id|__u32
id|length
suffix:semicolon
DECL|member|input
id|__u32
id|input
suffix:semicolon
DECL|member|reserved
id|__u32
id|reserved
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*  Flags for &squot;flags&squot; field */
DECL|macro|V4L2_BUF_FLAG_MAPPED
mdefine_line|#define V4L2_BUF_FLAG_MAPPED&t;0x0001  /* Buffer is mapped (flag) */
DECL|macro|V4L2_BUF_FLAG_QUEUED
mdefine_line|#define V4L2_BUF_FLAG_QUEUED&t;0x0002&t;/* Buffer is queued for processing */
DECL|macro|V4L2_BUF_FLAG_DONE
mdefine_line|#define V4L2_BUF_FLAG_DONE&t;0x0004&t;/* Buffer is ready */
DECL|macro|V4L2_BUF_FLAG_KEYFRAME
mdefine_line|#define V4L2_BUF_FLAG_KEYFRAME&t;0x0008&t;/* Image is a keyframe (I-frame) */
DECL|macro|V4L2_BUF_FLAG_PFRAME
mdefine_line|#define V4L2_BUF_FLAG_PFRAME&t;0x0010&t;/* Image is a P-frame */
DECL|macro|V4L2_BUF_FLAG_BFRAME
mdefine_line|#define V4L2_BUF_FLAG_BFRAME&t;0x0020&t;/* Image is a B-frame */
DECL|macro|V4L2_BUF_FLAG_TIMECODE
mdefine_line|#define V4L2_BUF_FLAG_TIMECODE&t;0x0100&t;/* timecode field is valid */
DECL|macro|V4L2_BUF_FLAG_INPUT
mdefine_line|#define V4L2_BUF_FLAG_INPUT     0x0200  /* input field is valid */
multiline_comment|/*&n; *&t;O V E R L A Y   P R E V I E W&n; */
DECL|struct|v4l2_framebuffer
r_struct
id|v4l2_framebuffer
(brace
DECL|member|capability
id|__u32
id|capability
suffix:semicolon
DECL|member|flags
id|__u32
id|flags
suffix:semicolon
multiline_comment|/* FIXME: in theory we should pass something like PCI device + memory&n; * region + offset instead of some physical address */
DECL|member|base
r_void
op_star
id|base
suffix:semicolon
DECL|member|fmt
r_struct
id|v4l2_pix_format
id|fmt
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*  Flags for the &squot;capability&squot; field. Read only */
DECL|macro|V4L2_FBUF_CAP_EXTERNOVERLAY
mdefine_line|#define V4L2_FBUF_CAP_EXTERNOVERLAY&t;0x0001
DECL|macro|V4L2_FBUF_CAP_CHROMAKEY
mdefine_line|#define V4L2_FBUF_CAP_CHROMAKEY&t;&t;0x0002
DECL|macro|V4L2_FBUF_CAP_LIST_CLIPPING
mdefine_line|#define V4L2_FBUF_CAP_LIST_CLIPPING     0x0004
DECL|macro|V4L2_FBUF_CAP_BITMAP_CLIPPING
mdefine_line|#define V4L2_FBUF_CAP_BITMAP_CLIPPING&t;0x0008
multiline_comment|/*  Flags for the &squot;flags&squot; field. */
DECL|macro|V4L2_FBUF_FLAG_PRIMARY
mdefine_line|#define V4L2_FBUF_FLAG_PRIMARY&t;&t;0x0001
DECL|macro|V4L2_FBUF_FLAG_OVERLAY
mdefine_line|#define V4L2_FBUF_FLAG_OVERLAY&t;&t;0x0002
DECL|macro|V4L2_FBUF_FLAG_CHROMAKEY
mdefine_line|#define V4L2_FBUF_FLAG_CHROMAKEY&t;0x0004
DECL|struct|v4l2_clip
r_struct
id|v4l2_clip
(brace
DECL|member|c
r_struct
id|v4l2_rect
id|c
suffix:semicolon
DECL|member|next
r_struct
id|v4l2_clip
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|v4l2_window
r_struct
id|v4l2_window
(brace
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
DECL|member|chromakey
id|__u32
id|chromakey
suffix:semicolon
DECL|member|clips
r_struct
id|v4l2_clip
id|__user
op_star
id|clips
suffix:semicolon
DECL|member|clipcount
id|__u32
id|clipcount
suffix:semicolon
DECL|member|bitmap
r_void
id|__user
op_star
id|bitmap
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;C A P T U R E   P A R A M E T E R S&n; */
DECL|struct|v4l2_captureparm
r_struct
id|v4l2_captureparm
(brace
DECL|member|capability
id|__u32
id|capability
suffix:semicolon
multiline_comment|/*  Supported modes */
DECL|member|capturemode
id|__u32
id|capturemode
suffix:semicolon
multiline_comment|/*  Current mode */
DECL|member|timeperframe
r_struct
id|v4l2_fract
id|timeperframe
suffix:semicolon
multiline_comment|/*  Time per frame in .1us units */
DECL|member|extendedmode
id|__u32
id|extendedmode
suffix:semicolon
multiline_comment|/*  Driver-specific extensions */
DECL|member|readbuffers
id|__u32
id|readbuffers
suffix:semicolon
multiline_comment|/*  # of buffers for read */
DECL|member|reserved
id|__u32
id|reserved
(braket
l_int|4
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*  Flags for &squot;capability&squot; and &squot;capturemode&squot; fields */
DECL|macro|V4L2_MODE_HIGHQUALITY
mdefine_line|#define V4L2_MODE_HIGHQUALITY&t;0x0001&t;/*  High quality imaging mode */
DECL|macro|V4L2_CAP_TIMEPERFRAME
mdefine_line|#define V4L2_CAP_TIMEPERFRAME&t;0x1000&t;/*  timeperframe field is supported */
DECL|struct|v4l2_outputparm
r_struct
id|v4l2_outputparm
(brace
DECL|member|capability
id|__u32
id|capability
suffix:semicolon
multiline_comment|/*  Supported modes */
DECL|member|outputmode
id|__u32
id|outputmode
suffix:semicolon
multiline_comment|/*  Current mode */
DECL|member|timeperframe
r_struct
id|v4l2_fract
id|timeperframe
suffix:semicolon
multiline_comment|/*  Time per frame in seconds */
DECL|member|extendedmode
id|__u32
id|extendedmode
suffix:semicolon
multiline_comment|/*  Driver-specific extensions */
DECL|member|writebuffers
id|__u32
id|writebuffers
suffix:semicolon
multiline_comment|/*  # of buffers for write */
DECL|member|reserved
id|__u32
id|reserved
(braket
l_int|4
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;I N P U T   I M A G E   C R O P P I N G&n; */
DECL|struct|v4l2_cropcap
r_struct
id|v4l2_cropcap
(brace
DECL|member|type
r_enum
id|v4l2_buf_type
id|type
suffix:semicolon
DECL|member|bounds
r_struct
id|v4l2_rect
id|bounds
suffix:semicolon
DECL|member|defrect
r_struct
id|v4l2_rect
id|defrect
suffix:semicolon
DECL|member|pixelaspect
r_struct
id|v4l2_fract
id|pixelaspect
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|v4l2_crop
r_struct
id|v4l2_crop
(brace
DECL|member|type
r_enum
id|v4l2_buf_type
id|type
suffix:semicolon
DECL|member|c
r_struct
id|v4l2_rect
id|c
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *      A N A L O G   V I D E O   S T A N D A R D&n; */
DECL|typedef|v4l2_std_id
r_typedef
id|__u64
id|v4l2_std_id
suffix:semicolon
multiline_comment|/* one bit for each */
DECL|macro|V4L2_STD_PAL_B
mdefine_line|#define V4L2_STD_PAL_B          ((v4l2_std_id)0x00000001)
DECL|macro|V4L2_STD_PAL_B1
mdefine_line|#define V4L2_STD_PAL_B1         ((v4l2_std_id)0x00000002)
DECL|macro|V4L2_STD_PAL_G
mdefine_line|#define V4L2_STD_PAL_G          ((v4l2_std_id)0x00000004)
DECL|macro|V4L2_STD_PAL_H
mdefine_line|#define V4L2_STD_PAL_H          ((v4l2_std_id)0x00000008)
DECL|macro|V4L2_STD_PAL_I
mdefine_line|#define V4L2_STD_PAL_I          ((v4l2_std_id)0x00000010)
DECL|macro|V4L2_STD_PAL_D
mdefine_line|#define V4L2_STD_PAL_D          ((v4l2_std_id)0x00000020)
DECL|macro|V4L2_STD_PAL_D1
mdefine_line|#define V4L2_STD_PAL_D1         ((v4l2_std_id)0x00000040)
DECL|macro|V4L2_STD_PAL_K
mdefine_line|#define V4L2_STD_PAL_K          ((v4l2_std_id)0x00000080)
DECL|macro|V4L2_STD_PAL_M
mdefine_line|#define V4L2_STD_PAL_M          ((v4l2_std_id)0x00000100)
DECL|macro|V4L2_STD_PAL_N
mdefine_line|#define V4L2_STD_PAL_N          ((v4l2_std_id)0x00000200)
DECL|macro|V4L2_STD_PAL_Nc
mdefine_line|#define V4L2_STD_PAL_Nc         ((v4l2_std_id)0x00000400)
DECL|macro|V4L2_STD_PAL_60
mdefine_line|#define V4L2_STD_PAL_60         ((v4l2_std_id)0x00000800)
DECL|macro|V4L2_STD_NTSC_M
mdefine_line|#define V4L2_STD_NTSC_M         ((v4l2_std_id)0x00001000)
DECL|macro|V4L2_STD_NTSC_M_JP
mdefine_line|#define V4L2_STD_NTSC_M_JP      ((v4l2_std_id)0x00002000)
DECL|macro|V4L2_STD_SECAM_B
mdefine_line|#define V4L2_STD_SECAM_B        ((v4l2_std_id)0x00010000)
DECL|macro|V4L2_STD_SECAM_D
mdefine_line|#define V4L2_STD_SECAM_D        ((v4l2_std_id)0x00020000)
DECL|macro|V4L2_STD_SECAM_G
mdefine_line|#define V4L2_STD_SECAM_G        ((v4l2_std_id)0x00040000)
DECL|macro|V4L2_STD_SECAM_H
mdefine_line|#define V4L2_STD_SECAM_H        ((v4l2_std_id)0x00080000)
DECL|macro|V4L2_STD_SECAM_K
mdefine_line|#define V4L2_STD_SECAM_K        ((v4l2_std_id)0x00100000)
DECL|macro|V4L2_STD_SECAM_K1
mdefine_line|#define V4L2_STD_SECAM_K1       ((v4l2_std_id)0x00200000)
DECL|macro|V4L2_STD_SECAM_L
mdefine_line|#define V4L2_STD_SECAM_L        ((v4l2_std_id)0x00400000)
multiline_comment|/* ATSC/HDTV */
DECL|macro|V4L2_STD_ATSC_8_VSB
mdefine_line|#define V4L2_STD_ATSC_8_VSB     ((v4l2_std_id)0x01000000)
DECL|macro|V4L2_STD_ATSC_16_VSB
mdefine_line|#define V4L2_STD_ATSC_16_VSB    ((v4l2_std_id)0x02000000)
multiline_comment|/* some common needed stuff */
DECL|macro|V4L2_STD_PAL_BG
mdefine_line|#define V4L2_STD_PAL_BG&t;&t;(V4L2_STD_PAL_B&t;&t;|&bslash;&n;&t;&t;&t;&t; V4L2_STD_PAL_B1&t;|&bslash;&n;&t;&t;&t;&t; V4L2_STD_PAL_G)
DECL|macro|V4L2_STD_PAL_DK
mdefine_line|#define V4L2_STD_PAL_DK&t;&t;(V4L2_STD_PAL_D&t;&t;|&bslash;&n;&t;&t;&t;&t; V4L2_STD_PAL_D1&t;|&bslash;&n;&t;&t;&t;&t; V4L2_STD_PAL_K)
DECL|macro|V4L2_STD_PAL
mdefine_line|#define V4L2_STD_PAL&t;&t;(V4L2_STD_PAL_BG&t;|&bslash;&n;&t;&t;&t;&t; V4L2_STD_PAL_DK&t;|&bslash;&n;&t;&t;&t;&t; V4L2_STD_PAL_H&t;&t;|&bslash;&n;&t;&t;&t;&t; V4L2_STD_PAL_I)
DECL|macro|V4L2_STD_NTSC
mdefine_line|#define V4L2_STD_NTSC           (V4L2_STD_NTSC_M&t;|&bslash;&n;&t;&t;&t;&t; V4L2_STD_NTSC_M_JP)
DECL|macro|V4L2_STD_SECAM_DK
mdefine_line|#define V4L2_STD_SECAM_DK      &t;(V4L2_STD_SECAM_D&t;|&bslash;&n;&t;&t;&t;&t; V4L2_STD_SECAM_K&t;|&bslash;&n;&t;&t;&t;&t; V4L2_STD_SECAM_K1)
DECL|macro|V4L2_STD_SECAM
mdefine_line|#define V4L2_STD_SECAM&t;&t;(V4L2_STD_SECAM_B&t;|&bslash;&n;&t;&t;&t;&t; V4L2_STD_SECAM_G&t;|&bslash;&n;&t;&t;&t;&t; V4L2_STD_SECAM_H&t;|&bslash;&n;&t;&t;&t;&t; V4L2_STD_SECAM_DK&t;|&bslash;&n;&t;&t;&t;&t; V4L2_STD_SECAM_L)
DECL|macro|V4L2_STD_525_60
mdefine_line|#define V4L2_STD_525_60&t;&t;(V4L2_STD_PAL_M&t;&t;|&bslash;&n;&t;&t;&t;&t; V4L2_STD_PAL_60&t;|&bslash;&n;&t;&t;&t;&t; V4L2_STD_NTSC)
DECL|macro|V4L2_STD_625_50
mdefine_line|#define V4L2_STD_625_50&t;&t;(V4L2_STD_PAL&t;&t;|&bslash;&n;&t;&t;&t;&t; V4L2_STD_PAL_N&t;&t;|&bslash;&n;&t;&t;&t;&t; V4L2_STD_PAL_Nc&t;|&bslash;&n;&t;&t;&t;&t; V4L2_STD_SECAM)
DECL|macro|V4L2_STD_ATSC
mdefine_line|#define V4L2_STD_ATSC           (V4L2_STD_ATSC_8_VSB    |&bslash;&n;&t;&t;                 V4L2_STD_ATSC_16_VSB)
DECL|macro|V4L2_STD_UNKNOWN
mdefine_line|#define V4L2_STD_UNKNOWN        0
DECL|macro|V4L2_STD_ALL
mdefine_line|#define V4L2_STD_ALL            (V4L2_STD_525_60&t;|&bslash;&n;&t;&t;&t;&t; V4L2_STD_625_50)
DECL|struct|v4l2_standard
r_struct
id|v4l2_standard
(brace
DECL|member|index
id|__u32
id|index
suffix:semicolon
DECL|member|id
id|v4l2_std_id
id|id
suffix:semicolon
DECL|member|name
id|__u8
id|name
(braket
l_int|24
)braket
suffix:semicolon
DECL|member|frameperiod
r_struct
id|v4l2_fract
id|frameperiod
suffix:semicolon
multiline_comment|/* Frames, not fields */
DECL|member|framelines
id|__u32
id|framelines
suffix:semicolon
DECL|member|reserved
id|__u32
id|reserved
(braket
l_int|4
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;V I D E O   I N P U T S&n; */
DECL|struct|v4l2_input
r_struct
id|v4l2_input
(brace
DECL|member|index
id|__u32
id|index
suffix:semicolon
multiline_comment|/*  Which input */
DECL|member|name
id|__u8
id|name
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/*  Label */
DECL|member|type
id|__u32
id|type
suffix:semicolon
multiline_comment|/*  Type of input */
DECL|member|audioset
id|__u32
id|audioset
suffix:semicolon
multiline_comment|/*  Associated audios (bitfield) */
DECL|member|tuner
id|__u32
id|tuner
suffix:semicolon
multiline_comment|/*  Associated tuner */
DECL|member|std
id|v4l2_std_id
id|std
suffix:semicolon
DECL|member|status
id|__u32
id|status
suffix:semicolon
DECL|member|reserved
id|__u32
id|reserved
(braket
l_int|4
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*  Values for the &squot;type&squot; field */
DECL|macro|V4L2_INPUT_TYPE_TUNER
mdefine_line|#define V4L2_INPUT_TYPE_TUNER&t;&t;1
DECL|macro|V4L2_INPUT_TYPE_CAMERA
mdefine_line|#define V4L2_INPUT_TYPE_CAMERA&t;&t;2
multiline_comment|/* field &squot;status&squot; - general */
DECL|macro|V4L2_IN_ST_NO_POWER
mdefine_line|#define V4L2_IN_ST_NO_POWER    0x00000001  /* Attached device is off */
DECL|macro|V4L2_IN_ST_NO_SIGNAL
mdefine_line|#define V4L2_IN_ST_NO_SIGNAL   0x00000002
DECL|macro|V4L2_IN_ST_NO_COLOR
mdefine_line|#define V4L2_IN_ST_NO_COLOR    0x00000004
multiline_comment|/* field &squot;status&squot; - analog */
DECL|macro|V4L2_IN_ST_NO_H_LOCK
mdefine_line|#define V4L2_IN_ST_NO_H_LOCK   0x00000100  /* No horizontal sync lock */
DECL|macro|V4L2_IN_ST_COLOR_KILL
mdefine_line|#define V4L2_IN_ST_COLOR_KILL  0x00000200  /* Color killer is active */
multiline_comment|/* field &squot;status&squot; - digital */
DECL|macro|V4L2_IN_ST_NO_SYNC
mdefine_line|#define V4L2_IN_ST_NO_SYNC     0x00010000  /* No synchronization lock */
DECL|macro|V4L2_IN_ST_NO_EQU
mdefine_line|#define V4L2_IN_ST_NO_EQU      0x00020000  /* No equalizer lock */
DECL|macro|V4L2_IN_ST_NO_CARRIER
mdefine_line|#define V4L2_IN_ST_NO_CARRIER  0x00040000  /* Carrier recovery failed */
multiline_comment|/* field &squot;status&squot; - VCR and set-top box */
DECL|macro|V4L2_IN_ST_MACROVISION
mdefine_line|#define V4L2_IN_ST_MACROVISION 0x01000000  /* Macrovision detected */
DECL|macro|V4L2_IN_ST_NO_ACCESS
mdefine_line|#define V4L2_IN_ST_NO_ACCESS   0x02000000  /* Conditional access denied */
DECL|macro|V4L2_IN_ST_VTR
mdefine_line|#define V4L2_IN_ST_VTR         0x04000000  /* VTR time constant */
multiline_comment|/*&n; *&t;V I D E O   O U T P U T S&n; */
DECL|struct|v4l2_output
r_struct
id|v4l2_output
(brace
DECL|member|index
id|__u32
id|index
suffix:semicolon
multiline_comment|/*  Which output */
DECL|member|name
id|__u8
id|name
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/*  Label */
DECL|member|type
id|__u32
id|type
suffix:semicolon
multiline_comment|/*  Type of output */
DECL|member|audioset
id|__u32
id|audioset
suffix:semicolon
multiline_comment|/*  Associated audios (bitfield) */
DECL|member|modulator
id|__u32
id|modulator
suffix:semicolon
multiline_comment|/*  Associated modulator */
DECL|member|std
id|v4l2_std_id
id|std
suffix:semicolon
DECL|member|reserved
id|__u32
id|reserved
(braket
l_int|4
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*  Values for the &squot;type&squot; field */
DECL|macro|V4L2_OUTPUT_TYPE_MODULATOR
mdefine_line|#define V4L2_OUTPUT_TYPE_MODULATOR&t;&t;1
DECL|macro|V4L2_OUTPUT_TYPE_ANALOG
mdefine_line|#define V4L2_OUTPUT_TYPE_ANALOG&t;&t;&t;2
DECL|macro|V4L2_OUTPUT_TYPE_ANALOGVGAOVERLAY
mdefine_line|#define V4L2_OUTPUT_TYPE_ANALOGVGAOVERLAY&t;3
multiline_comment|/*&n; *&t;C O N T R O L S&n; */
DECL|struct|v4l2_control
r_struct
id|v4l2_control
(brace
DECL|member|id
id|__u32
id|id
suffix:semicolon
DECL|member|value
id|__s32
id|value
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*  Used in the VIDIOC_QUERYCTRL ioctl for querying controls */
DECL|struct|v4l2_queryctrl
r_struct
id|v4l2_queryctrl
(brace
DECL|member|id
id|__u32
id|id
suffix:semicolon
DECL|member|type
r_enum
id|v4l2_ctrl_type
id|type
suffix:semicolon
DECL|member|name
id|__u8
id|name
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* Whatever */
DECL|member|minimum
id|__s32
id|minimum
suffix:semicolon
multiline_comment|/* Note signedness */
DECL|member|maximum
id|__s32
id|maximum
suffix:semicolon
DECL|member|step
id|__s32
id|step
suffix:semicolon
DECL|member|default_value
id|__s32
id|default_value
suffix:semicolon
DECL|member|flags
id|__u32
id|flags
suffix:semicolon
DECL|member|reserved
id|__u32
id|reserved
(braket
l_int|2
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*  Used in the VIDIOC_QUERYMENU ioctl for querying menu items */
DECL|struct|v4l2_querymenu
r_struct
id|v4l2_querymenu
(brace
DECL|member|id
id|__u32
id|id
suffix:semicolon
DECL|member|index
id|__u32
id|index
suffix:semicolon
DECL|member|name
id|__u8
id|name
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* Whatever */
DECL|member|reserved
id|__u32
id|reserved
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*  Control flags  */
DECL|macro|V4L2_CTRL_FLAG_DISABLED
mdefine_line|#define V4L2_CTRL_FLAG_DISABLED&t;&t;0x0001
DECL|macro|V4L2_CTRL_FLAG_GRABBED
mdefine_line|#define V4L2_CTRL_FLAG_GRABBED&t;&t;0x0002
multiline_comment|/*  Control IDs defined by V4L2 */
DECL|macro|V4L2_CID_BASE
mdefine_line|#define V4L2_CID_BASE&t;&t;&t;0x00980900
multiline_comment|/*  IDs reserved for driver specific controls */
DECL|macro|V4L2_CID_PRIVATE_BASE
mdefine_line|#define V4L2_CID_PRIVATE_BASE&t;&t;0x08000000
DECL|macro|V4L2_CID_BRIGHTNESS
mdefine_line|#define V4L2_CID_BRIGHTNESS&t;&t;(V4L2_CID_BASE+0)
DECL|macro|V4L2_CID_CONTRAST
mdefine_line|#define V4L2_CID_CONTRAST&t;&t;(V4L2_CID_BASE+1)
DECL|macro|V4L2_CID_SATURATION
mdefine_line|#define V4L2_CID_SATURATION&t;&t;(V4L2_CID_BASE+2)
DECL|macro|V4L2_CID_HUE
mdefine_line|#define V4L2_CID_HUE&t;&t;&t;(V4L2_CID_BASE+3)
DECL|macro|V4L2_CID_AUDIO_VOLUME
mdefine_line|#define V4L2_CID_AUDIO_VOLUME&t;&t;(V4L2_CID_BASE+5)
DECL|macro|V4L2_CID_AUDIO_BALANCE
mdefine_line|#define V4L2_CID_AUDIO_BALANCE&t;&t;(V4L2_CID_BASE+6)
DECL|macro|V4L2_CID_AUDIO_BASS
mdefine_line|#define V4L2_CID_AUDIO_BASS&t;&t;(V4L2_CID_BASE+7)
DECL|macro|V4L2_CID_AUDIO_TREBLE
mdefine_line|#define V4L2_CID_AUDIO_TREBLE&t;&t;(V4L2_CID_BASE+8)
DECL|macro|V4L2_CID_AUDIO_MUTE
mdefine_line|#define V4L2_CID_AUDIO_MUTE&t;&t;(V4L2_CID_BASE+9)
DECL|macro|V4L2_CID_AUDIO_LOUDNESS
mdefine_line|#define V4L2_CID_AUDIO_LOUDNESS&t;&t;(V4L2_CID_BASE+10)
DECL|macro|V4L2_CID_BLACK_LEVEL
mdefine_line|#define V4L2_CID_BLACK_LEVEL&t;&t;(V4L2_CID_BASE+11)
DECL|macro|V4L2_CID_AUTO_WHITE_BALANCE
mdefine_line|#define V4L2_CID_AUTO_WHITE_BALANCE&t;(V4L2_CID_BASE+12)
DECL|macro|V4L2_CID_DO_WHITE_BALANCE
mdefine_line|#define V4L2_CID_DO_WHITE_BALANCE&t;(V4L2_CID_BASE+13)
DECL|macro|V4L2_CID_RED_BALANCE
mdefine_line|#define V4L2_CID_RED_BALANCE&t;&t;(V4L2_CID_BASE+14)
DECL|macro|V4L2_CID_BLUE_BALANCE
mdefine_line|#define V4L2_CID_BLUE_BALANCE&t;&t;(V4L2_CID_BASE+15)
DECL|macro|V4L2_CID_GAMMA
mdefine_line|#define V4L2_CID_GAMMA&t;&t;&t;(V4L2_CID_BASE+16)
DECL|macro|V4L2_CID_WHITENESS
mdefine_line|#define V4L2_CID_WHITENESS&t;&t;(V4L2_CID_GAMMA) /* ? Not sure */
DECL|macro|V4L2_CID_EXPOSURE
mdefine_line|#define V4L2_CID_EXPOSURE&t;&t;(V4L2_CID_BASE+17)
DECL|macro|V4L2_CID_AUTOGAIN
mdefine_line|#define V4L2_CID_AUTOGAIN&t;&t;(V4L2_CID_BASE+18)
DECL|macro|V4L2_CID_GAIN
mdefine_line|#define V4L2_CID_GAIN&t;&t;&t;(V4L2_CID_BASE+19)
DECL|macro|V4L2_CID_HFLIP
mdefine_line|#define V4L2_CID_HFLIP&t;&t;&t;(V4L2_CID_BASE+20)
DECL|macro|V4L2_CID_VFLIP
mdefine_line|#define V4L2_CID_VFLIP&t;&t;&t;(V4L2_CID_BASE+21)
DECL|macro|V4L2_CID_HCENTER
mdefine_line|#define V4L2_CID_HCENTER&t;&t;(V4L2_CID_BASE+22)
DECL|macro|V4L2_CID_VCENTER
mdefine_line|#define V4L2_CID_VCENTER&t;&t;(V4L2_CID_BASE+23)
DECL|macro|V4L2_CID_LASTP1
mdefine_line|#define V4L2_CID_LASTP1&t;&t;&t;(V4L2_CID_BASE+24) /* last CID + 1 */
multiline_comment|/*&n; *&t;T U N I N G&n; */
DECL|struct|v4l2_tuner
r_struct
id|v4l2_tuner
(brace
DECL|member|index
id|__u32
id|index
suffix:semicolon
DECL|member|name
id|__u8
id|name
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|type
r_enum
id|v4l2_tuner_type
id|type
suffix:semicolon
DECL|member|capability
id|__u32
id|capability
suffix:semicolon
DECL|member|rangelow
id|__u32
id|rangelow
suffix:semicolon
DECL|member|rangehigh
id|__u32
id|rangehigh
suffix:semicolon
DECL|member|rxsubchans
id|__u32
id|rxsubchans
suffix:semicolon
DECL|member|audmode
id|__u32
id|audmode
suffix:semicolon
DECL|member|signal
id|__s32
id|signal
suffix:semicolon
DECL|member|afc
id|__s32
id|afc
suffix:semicolon
DECL|member|reserved
id|__u32
id|reserved
(braket
l_int|4
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|v4l2_modulator
r_struct
id|v4l2_modulator
(brace
DECL|member|index
id|__u32
id|index
suffix:semicolon
DECL|member|name
id|__u8
id|name
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|capability
id|__u32
id|capability
suffix:semicolon
DECL|member|rangelow
id|__u32
id|rangelow
suffix:semicolon
DECL|member|rangehigh
id|__u32
id|rangehigh
suffix:semicolon
DECL|member|txsubchans
id|__u32
id|txsubchans
suffix:semicolon
DECL|member|reserved
id|__u32
id|reserved
(braket
l_int|4
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*  Flags for the &squot;capability&squot; field */
DECL|macro|V4L2_TUNER_CAP_LOW
mdefine_line|#define V4L2_TUNER_CAP_LOW&t;&t;0x0001
DECL|macro|V4L2_TUNER_CAP_NORM
mdefine_line|#define V4L2_TUNER_CAP_NORM&t;&t;0x0002
DECL|macro|V4L2_TUNER_CAP_STEREO
mdefine_line|#define V4L2_TUNER_CAP_STEREO&t;&t;0x0010
DECL|macro|V4L2_TUNER_CAP_LANG2
mdefine_line|#define V4L2_TUNER_CAP_LANG2&t;&t;0x0020
DECL|macro|V4L2_TUNER_CAP_SAP
mdefine_line|#define V4L2_TUNER_CAP_SAP&t;&t;0x0020
DECL|macro|V4L2_TUNER_CAP_LANG1
mdefine_line|#define V4L2_TUNER_CAP_LANG1&t;&t;0x0040
multiline_comment|/*  Flags for the &squot;rxsubchans&squot; field */
DECL|macro|V4L2_TUNER_SUB_MONO
mdefine_line|#define V4L2_TUNER_SUB_MONO&t;&t;0x0001
DECL|macro|V4L2_TUNER_SUB_STEREO
mdefine_line|#define V4L2_TUNER_SUB_STEREO&t;&t;0x0002
DECL|macro|V4L2_TUNER_SUB_LANG2
mdefine_line|#define V4L2_TUNER_SUB_LANG2&t;&t;0x0004
DECL|macro|V4L2_TUNER_SUB_SAP
mdefine_line|#define V4L2_TUNER_SUB_SAP&t;&t;0x0004
DECL|macro|V4L2_TUNER_SUB_LANG1
mdefine_line|#define V4L2_TUNER_SUB_LANG1&t;&t;0x0008
multiline_comment|/*  Values for the &squot;audmode&squot; field */
DECL|macro|V4L2_TUNER_MODE_MONO
mdefine_line|#define V4L2_TUNER_MODE_MONO&t;&t;0x0000
DECL|macro|V4L2_TUNER_MODE_STEREO
mdefine_line|#define V4L2_TUNER_MODE_STEREO&t;&t;0x0001
DECL|macro|V4L2_TUNER_MODE_LANG2
mdefine_line|#define V4L2_TUNER_MODE_LANG2&t;&t;0x0002
DECL|macro|V4L2_TUNER_MODE_SAP
mdefine_line|#define V4L2_TUNER_MODE_SAP&t;&t;0x0002
DECL|macro|V4L2_TUNER_MODE_LANG1
mdefine_line|#define V4L2_TUNER_MODE_LANG1&t;&t;0x0003
DECL|struct|v4l2_frequency
r_struct
id|v4l2_frequency
(brace
DECL|member|tuner
id|__u32
id|tuner
suffix:semicolon
DECL|member|type
r_enum
id|v4l2_tuner_type
id|type
suffix:semicolon
DECL|member|frequency
id|__u32
id|frequency
suffix:semicolon
DECL|member|reserved
id|__u32
id|reserved
(braket
l_int|8
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;A U D I O&n; */
DECL|struct|v4l2_audio
r_struct
id|v4l2_audio
(brace
DECL|member|index
id|__u32
id|index
suffix:semicolon
DECL|member|name
id|__u8
id|name
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|capability
id|__u32
id|capability
suffix:semicolon
DECL|member|mode
id|__u32
id|mode
suffix:semicolon
DECL|member|reserved
id|__u32
id|reserved
(braket
l_int|2
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*  Flags for the &squot;capability&squot; field */
DECL|macro|V4L2_AUDCAP_STEREO
mdefine_line|#define V4L2_AUDCAP_STEREO&t;&t;0x00001
DECL|macro|V4L2_AUDCAP_AVL
mdefine_line|#define V4L2_AUDCAP_AVL&t;&t;&t;0x00002
multiline_comment|/*  Flags for the &squot;mode&squot; field */
DECL|macro|V4L2_AUDMODE_AVL
mdefine_line|#define V4L2_AUDMODE_AVL&t;&t;0x00001
DECL|struct|v4l2_audioout
r_struct
id|v4l2_audioout
(brace
DECL|member|index
id|__u32
id|index
suffix:semicolon
DECL|member|name
id|__u8
id|name
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|capability
id|__u32
id|capability
suffix:semicolon
DECL|member|mode
id|__u32
id|mode
suffix:semicolon
DECL|member|reserved
id|__u32
id|reserved
(braket
l_int|2
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;D A T A   S E R V I C E S   ( V B I )&n; *&n; *&t;Data services API by Michael Schimek&n; */
DECL|struct|v4l2_vbi_format
r_struct
id|v4l2_vbi_format
(brace
DECL|member|sampling_rate
id|__u32
id|sampling_rate
suffix:semicolon
multiline_comment|/* in 1 Hz */
DECL|member|offset
id|__u32
id|offset
suffix:semicolon
DECL|member|samples_per_line
id|__u32
id|samples_per_line
suffix:semicolon
DECL|member|sample_format
id|__u32
id|sample_format
suffix:semicolon
multiline_comment|/* V4L2_PIX_FMT_* */
DECL|member|start
id|__s32
id|start
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|count
id|__u32
id|count
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|flags
id|__u32
id|flags
suffix:semicolon
multiline_comment|/* V4L2_VBI_* */
DECL|member|reserved
id|__u32
id|reserved
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* must be zero */
)brace
suffix:semicolon
multiline_comment|/*  VBI flags  */
DECL|macro|V4L2_VBI_UNSYNC
mdefine_line|#define V4L2_VBI_UNSYNC&t;&t;(1&lt;&lt; 0)
DECL|macro|V4L2_VBI_INTERLACED
mdefine_line|#define V4L2_VBI_INTERLACED&t;(1&lt;&lt; 1)
multiline_comment|/*&n; *&t;A G G R E G A T E   S T R U C T U R E S&n; */
multiline_comment|/*&t;Stream data format&n; */
DECL|struct|v4l2_format
r_struct
id|v4l2_format
(brace
DECL|member|type
r_enum
id|v4l2_buf_type
id|type
suffix:semicolon
r_union
(brace
DECL|member|pix
r_struct
id|v4l2_pix_format
id|pix
suffix:semicolon
singleline_comment|// V4L2_BUF_TYPE_VIDEO_CAPTURE
DECL|member|win
r_struct
id|v4l2_window
id|win
suffix:semicolon
singleline_comment|// V4L2_BUF_TYPE_VIDEO_OVERLAY
DECL|member|vbi
r_struct
id|v4l2_vbi_format
id|vbi
suffix:semicolon
singleline_comment|// V4L2_BUF_TYPE_VBI_CAPTURE
DECL|member|raw_data
id|__u8
id|raw_data
(braket
l_int|200
)braket
suffix:semicolon
singleline_comment|// user-defined
DECL|member|fmt
)brace
id|fmt
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&t;Stream type-dependent parameters&n; */
DECL|struct|v4l2_streamparm
r_struct
id|v4l2_streamparm
(brace
DECL|member|type
r_enum
id|v4l2_buf_type
id|type
suffix:semicolon
r_union
(brace
DECL|member|capture
r_struct
id|v4l2_captureparm
id|capture
suffix:semicolon
DECL|member|output
r_struct
id|v4l2_outputparm
id|output
suffix:semicolon
DECL|member|raw_data
id|__u8
id|raw_data
(braket
l_int|200
)braket
suffix:semicolon
multiline_comment|/* user-defined */
DECL|member|parm
)brace
id|parm
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;I O C T L   C O D E S   F O R   V I D E O   D E V I C E S&n; *&n; */
DECL|macro|VIDIOC_QUERYCAP
mdefine_line|#define VIDIOC_QUERYCAP&t;&t;_IOR  (&squot;V&squot;,  0, struct v4l2_capability)
DECL|macro|VIDIOC_RESERVED
mdefine_line|#define VIDIOC_RESERVED&t;&t;_IO   (&squot;V&squot;,  1)
DECL|macro|VIDIOC_ENUM_FMT
mdefine_line|#define VIDIOC_ENUM_FMT         _IOWR (&squot;V&squot;,  2, struct v4l2_fmtdesc)
DECL|macro|VIDIOC_G_FMT
mdefine_line|#define VIDIOC_G_FMT&t;&t;_IOWR (&squot;V&squot;,  4, struct v4l2_format)
DECL|macro|VIDIOC_S_FMT
mdefine_line|#define VIDIOC_S_FMT&t;&t;_IOWR (&squot;V&squot;,  5, struct v4l2_format)
macro_line|#if 0
mdefine_line|#define VIDIOC_G_COMP&t;&t;_IOR  (&squot;V&squot;,  6, struct v4l2_compression)
mdefine_line|#define VIDIOC_S_COMP&t;&t;_IOW  (&squot;V&squot;,  7, struct v4l2_compression)
macro_line|#endif
DECL|macro|VIDIOC_REQBUFS
mdefine_line|#define VIDIOC_REQBUFS&t;&t;_IOWR (&squot;V&squot;,  8, struct v4l2_requestbuffers)
DECL|macro|VIDIOC_QUERYBUF
mdefine_line|#define VIDIOC_QUERYBUF&t;&t;_IOWR (&squot;V&squot;,  9, struct v4l2_buffer)
DECL|macro|VIDIOC_G_FBUF
mdefine_line|#define VIDIOC_G_FBUF&t;&t;_IOR  (&squot;V&squot;, 10, struct v4l2_framebuffer)
DECL|macro|VIDIOC_S_FBUF
mdefine_line|#define VIDIOC_S_FBUF&t;&t;_IOW  (&squot;V&squot;, 11, struct v4l2_framebuffer)
DECL|macro|VIDIOC_OVERLAY
mdefine_line|#define VIDIOC_OVERLAY&t;&t;_IOW  (&squot;V&squot;, 14, int)
DECL|macro|VIDIOC_QBUF
mdefine_line|#define VIDIOC_QBUF&t;&t;_IOWR (&squot;V&squot;, 15, struct v4l2_buffer)
DECL|macro|VIDIOC_DQBUF
mdefine_line|#define VIDIOC_DQBUF&t;&t;_IOWR (&squot;V&squot;, 17, struct v4l2_buffer)
DECL|macro|VIDIOC_STREAMON
mdefine_line|#define VIDIOC_STREAMON&t;&t;_IOW  (&squot;V&squot;, 18, int)
DECL|macro|VIDIOC_STREAMOFF
mdefine_line|#define VIDIOC_STREAMOFF&t;_IOW  (&squot;V&squot;, 19, int)
DECL|macro|VIDIOC_G_PARM
mdefine_line|#define VIDIOC_G_PARM&t;&t;_IOWR (&squot;V&squot;, 21, struct v4l2_streamparm)
DECL|macro|VIDIOC_S_PARM
mdefine_line|#define VIDIOC_S_PARM&t;&t;_IOWR (&squot;V&squot;, 22, struct v4l2_streamparm)
DECL|macro|VIDIOC_G_STD
mdefine_line|#define VIDIOC_G_STD&t;&t;_IOR  (&squot;V&squot;, 23, v4l2_std_id)
DECL|macro|VIDIOC_S_STD
mdefine_line|#define VIDIOC_S_STD&t;&t;_IOW  (&squot;V&squot;, 24, v4l2_std_id)
DECL|macro|VIDIOC_ENUMSTD
mdefine_line|#define VIDIOC_ENUMSTD&t;&t;_IOWR (&squot;V&squot;, 25, struct v4l2_standard)
DECL|macro|VIDIOC_ENUMINPUT
mdefine_line|#define VIDIOC_ENUMINPUT&t;_IOWR (&squot;V&squot;, 26, struct v4l2_input)
DECL|macro|VIDIOC_G_CTRL
mdefine_line|#define VIDIOC_G_CTRL&t;&t;_IOWR (&squot;V&squot;, 27, struct v4l2_control)
DECL|macro|VIDIOC_S_CTRL
mdefine_line|#define VIDIOC_S_CTRL&t;&t;_IOWR (&squot;V&squot;, 28, struct v4l2_control)
DECL|macro|VIDIOC_G_TUNER
mdefine_line|#define VIDIOC_G_TUNER&t;&t;_IOWR (&squot;V&squot;, 29, struct v4l2_tuner)
DECL|macro|VIDIOC_S_TUNER
mdefine_line|#define VIDIOC_S_TUNER&t;&t;_IOW  (&squot;V&squot;, 30, struct v4l2_tuner)
DECL|macro|VIDIOC_G_AUDIO
mdefine_line|#define VIDIOC_G_AUDIO&t;&t;_IOR  (&squot;V&squot;, 33, struct v4l2_audio)
DECL|macro|VIDIOC_S_AUDIO
mdefine_line|#define VIDIOC_S_AUDIO&t;&t;_IOW  (&squot;V&squot;, 34, struct v4l2_audio)
DECL|macro|VIDIOC_QUERYCTRL
mdefine_line|#define VIDIOC_QUERYCTRL&t;_IOWR (&squot;V&squot;, 36, struct v4l2_queryctrl)
DECL|macro|VIDIOC_QUERYMENU
mdefine_line|#define VIDIOC_QUERYMENU&t;_IOWR (&squot;V&squot;, 37, struct v4l2_querymenu)
DECL|macro|VIDIOC_G_INPUT
mdefine_line|#define VIDIOC_G_INPUT&t;&t;_IOR  (&squot;V&squot;, 38, int)
DECL|macro|VIDIOC_S_INPUT
mdefine_line|#define VIDIOC_S_INPUT&t;&t;_IOWR (&squot;V&squot;, 39, int)
DECL|macro|VIDIOC_G_OUTPUT
mdefine_line|#define VIDIOC_G_OUTPUT&t;&t;_IOR  (&squot;V&squot;, 46, int)
DECL|macro|VIDIOC_S_OUTPUT
mdefine_line|#define VIDIOC_S_OUTPUT&t;&t;_IOWR (&squot;V&squot;, 47, int)
DECL|macro|VIDIOC_ENUMOUTPUT
mdefine_line|#define VIDIOC_ENUMOUTPUT&t;_IOWR (&squot;V&squot;, 48, struct v4l2_output)
DECL|macro|VIDIOC_G_AUDOUT
mdefine_line|#define VIDIOC_G_AUDOUT&t;&t;_IOR  (&squot;V&squot;, 49, struct v4l2_audioout)
DECL|macro|VIDIOC_S_AUDOUT
mdefine_line|#define VIDIOC_S_AUDOUT&t;&t;_IOW  (&squot;V&squot;, 50, struct v4l2_audioout)
DECL|macro|VIDIOC_G_MODULATOR
mdefine_line|#define VIDIOC_G_MODULATOR&t;_IOWR (&squot;V&squot;, 54, struct v4l2_modulator)
DECL|macro|VIDIOC_S_MODULATOR
mdefine_line|#define VIDIOC_S_MODULATOR&t;_IOW  (&squot;V&squot;, 55, struct v4l2_modulator)
DECL|macro|VIDIOC_G_FREQUENCY
mdefine_line|#define VIDIOC_G_FREQUENCY&t;_IOWR (&squot;V&squot;, 56, struct v4l2_frequency)
DECL|macro|VIDIOC_S_FREQUENCY
mdefine_line|#define VIDIOC_S_FREQUENCY&t;_IOW  (&squot;V&squot;, 57, struct v4l2_frequency)
DECL|macro|VIDIOC_CROPCAP
mdefine_line|#define VIDIOC_CROPCAP&t;&t;_IOWR (&squot;V&squot;, 58, struct v4l2_cropcap)
DECL|macro|VIDIOC_G_CROP
mdefine_line|#define VIDIOC_G_CROP&t;&t;_IOWR (&squot;V&squot;, 59, struct v4l2_crop)
DECL|macro|VIDIOC_S_CROP
mdefine_line|#define VIDIOC_S_CROP&t;&t;_IOW  (&squot;V&squot;, 60, struct v4l2_crop)
DECL|macro|VIDIOC_G_JPEGCOMP
mdefine_line|#define VIDIOC_G_JPEGCOMP&t;_IOR  (&squot;V&squot;, 61, struct v4l2_jpegcompression)
DECL|macro|VIDIOC_S_JPEGCOMP
mdefine_line|#define VIDIOC_S_JPEGCOMP&t;_IOW  (&squot;V&squot;, 62, struct v4l2_jpegcompression)
DECL|macro|VIDIOC_QUERYSTD
mdefine_line|#define VIDIOC_QUERYSTD      &t;_IOR  (&squot;V&squot;, 63, v4l2_std_id)
DECL|macro|VIDIOC_TRY_FMT
mdefine_line|#define VIDIOC_TRY_FMT      &t;_IOWR (&squot;V&squot;, 64, struct v4l2_format)
DECL|macro|VIDIOC_ENUMAUDIO
mdefine_line|#define VIDIOC_ENUMAUDIO&t;_IOWR (&squot;V&squot;, 65, struct v4l2_audio)
DECL|macro|VIDIOC_ENUMAUDOUT
mdefine_line|#define VIDIOC_ENUMAUDOUT&t;_IOWR (&squot;V&squot;, 66, struct v4l2_audioout)
DECL|macro|VIDIOC_G_PRIORITY
mdefine_line|#define VIDIOC_G_PRIORITY       _IOR  (&squot;V&squot;, 67, enum v4l2_priority)
DECL|macro|VIDIOC_S_PRIORITY
mdefine_line|#define VIDIOC_S_PRIORITY       _IOW  (&squot;V&squot;, 68, enum v4l2_priority)
multiline_comment|/* for compatibility, will go away some day */
DECL|macro|VIDIOC_OVERLAY_OLD
mdefine_line|#define VIDIOC_OVERLAY_OLD     &t;_IOWR (&squot;V&squot;, 14, int)
DECL|macro|VIDIOC_S_PARM_OLD
mdefine_line|#define VIDIOC_S_PARM_OLD      &t;_IOW  (&squot;V&squot;, 22, struct v4l2_streamparm)
DECL|macro|VIDIOC_S_CTRL_OLD
mdefine_line|#define VIDIOC_S_CTRL_OLD      &t;_IOW  (&squot;V&squot;, 28, struct v4l2_control)
DECL|macro|VIDIOC_G_AUDIO_OLD
mdefine_line|#define VIDIOC_G_AUDIO_OLD     &t;_IOWR (&squot;V&squot;, 33, struct v4l2_audio)
DECL|macro|VIDIOC_G_AUDOUT_OLD
mdefine_line|#define VIDIOC_G_AUDOUT_OLD    &t;_IOWR (&squot;V&squot;, 49, struct v4l2_audioout)
DECL|macro|VIDIOC_CROPCAP_OLD
mdefine_line|#define VIDIOC_CROPCAP_OLD     &t;_IOR  (&squot;V&squot;, 58, struct v4l2_cropcap)
DECL|macro|BASE_VIDIOC_PRIVATE
mdefine_line|#define BASE_VIDIOC_PRIVATE&t;192&t;&t;/* 192-255 are private */
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; *&n; *&t;V 4 L 2   D R I V E R   H E L P E R   A P I&n; *&n; *&t;Some commonly needed functions for drivers (v4l2-common.o module)&n; */
macro_line|#include &lt;linux/fs.h&gt;
multiline_comment|/*  Video standard functions  */
r_extern
r_int
r_int
id|v4l2_video_std_fps
c_func
(paren
r_struct
id|v4l2_standard
op_star
id|vs
)paren
suffix:semicolon
r_extern
r_int
id|v4l2_video_std_construct
c_func
(paren
r_struct
id|v4l2_standard
op_star
id|vs
comma
r_int
id|id
comma
r_char
op_star
id|name
)paren
suffix:semicolon
multiline_comment|/* prority handling */
DECL|struct|v4l2_prio_state
r_struct
id|v4l2_prio_state
(brace
DECL|member|prios
id|atomic_t
id|prios
(braket
l_int|4
)braket
suffix:semicolon
)brace
suffix:semicolon
r_int
id|v4l2_prio_init
c_func
(paren
r_struct
id|v4l2_prio_state
op_star
id|global
)paren
suffix:semicolon
r_int
id|v4l2_prio_change
c_func
(paren
r_struct
id|v4l2_prio_state
op_star
id|global
comma
r_enum
id|v4l2_priority
op_star
id|local
comma
r_enum
id|v4l2_priority
r_new
)paren
suffix:semicolon
r_int
id|v4l2_prio_open
c_func
(paren
r_struct
id|v4l2_prio_state
op_star
id|global
comma
r_enum
id|v4l2_priority
op_star
id|local
)paren
suffix:semicolon
r_int
id|v4l2_prio_close
c_func
(paren
r_struct
id|v4l2_prio_state
op_star
id|global
comma
r_enum
id|v4l2_priority
op_star
id|local
)paren
suffix:semicolon
r_enum
id|v4l2_priority
id|v4l2_prio_max
c_func
(paren
r_struct
id|v4l2_prio_state
op_star
id|global
)paren
suffix:semicolon
r_int
id|v4l2_prio_check
c_func
(paren
r_struct
id|v4l2_prio_state
op_star
id|global
comma
r_enum
id|v4l2_priority
op_star
id|local
)paren
suffix:semicolon
multiline_comment|/* names for fancy debug output */
r_extern
r_char
op_star
id|v4l2_field_names
(braket
)braket
suffix:semicolon
r_extern
r_char
op_star
id|v4l2_type_names
(braket
)braket
suffix:semicolon
r_extern
r_char
op_star
id|v4l2_ioctl_names
(braket
)braket
suffix:semicolon
multiline_comment|/*  Compatibility layer interface  --  v4l1-compat module */
DECL|typedef|v4l2_kioctl
r_typedef
r_int
(paren
op_star
id|v4l2_kioctl
)paren
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|cmd
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
r_int
id|v4l_compat_translate_ioctl
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
comma
r_int
id|cmd
comma
r_void
op_star
id|arg
comma
id|v4l2_kioctl
id|driver_ioctl
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __LINUX_VIDEODEV2_H */
multiline_comment|/*&n; * Local variables:&n; * c-basic-offset: 8&n; * End:&n; */
eof
