multiline_comment|/*&n; * VIDEO MOTION CODECs internal API for video devices&n; *&n; * Interface for MJPEG (and maybe later MPEG/WAVELETS) codec&squot;s&n; * bound to a master device.&n; *&n; * (c) 2002 Wolfgang Scherr &lt;scherr@net4you.at&gt;&n; *&n; * $Id: videocodec.h,v 1.1.2.4 2003/01/14 21:15:03 rbultje Exp $&n; *&n; * ------------------------------------------------------------------------&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * ------------------------------------------------------------------------&n; */
multiline_comment|/* =================== */
multiline_comment|/* general description */
multiline_comment|/* =================== */
multiline_comment|/* Should ease the (re-)usage of drivers supporting cards with (different)&n;   video codecs. The codecs register to this module their functionality,&n;   and the processors (masters) can attach to them if they fit.&n;&n;   The codecs are typically have a &quot;strong&quot; binding to their master - so I&n;   don&squot;t think it makes sense to have a full blown interfacing as with e.g.&n;   i2c. If you have an other opinion, let&squot;s discuss &amp; implement it :-)))&n;&n;   Usage:&n;&n;   The slave has just to setup the videocodec structure and use two functions:&n;   videocodec_register(codecdata);&n;   videocodec_unregister(codecdata);&n;   The best is just calling them at module (de-)initialisation.&n;&n;   The master sets up the structure videocodec_master and calls:&n;   codecdata=videocodec_attach(master_codecdata);&n;   videocodec_detach(codecdata);&n;&n;   The slave is called during attach/detach via functions setup previously&n;   during register. At that time, the master_data pointer is set up&n;   and the slave can access any io registers of the master device (in the case&n;   the slave is bound to it). Otherwise it doesn&squot;t need this functions and&n;   therfor they may not be initialized.&n;&n;   The other fuctions are just for convenience, as they are for shure used by&n;   most/all of the codecs. The last ones may be ommited, too. &n;&n;   See the structure declaration below for more information and which data has&n;   to be set up for the master and the slave.&n;&n;   ----------------------------------------------------------------------------&n;   The master should have &quot;knowledge&quot; of the slave and vice versa.  So the data&n;   structures sent to/from slave via set_data/get_data set_image/get_image are&n;   device dependent and vary between MJPEG/MPEG/WAVELET/... devices. (!!!!)&n;   ----------------------------------------------------------------------------&n;*/
"&f;"
multiline_comment|/* ========================================== */
multiline_comment|/* description of the videocodec_io structure */
multiline_comment|/* ========================================== */
multiline_comment|/*&n;   ==== master setup ==== &n;   name -&gt; name of the device structure for reference and debugging&n;   master_data -&gt;  data ref. for the master (e.g. the zr36055,57,67)&n;   readreg -&gt; ref. to read-fn from register (setup by master, used by slave)&n;   writereg -&gt; ref. to write-fn to register (setup by master, used by slave)&n;               this two functions do the lowlevel I/O job&n;&n;   ==== slave functionality setup ==== &n;   slave_data -&gt; data ref. for the slave (e.g. the zr36050,60) &n;   check -&gt; fn-ref. checks availability of an device, returns -EIO on failure or&n;            the type on success&n;            this makes espcecially sense if a driver module supports more than&n;            one codec which may be quite similar to access, nevertheless it&n;            is good for a first functionality check &n;&n;   -- main functions you always need for compression/decompression -- &n;&n;   set_mode -&gt; this fn-ref. resets the entire codec, and sets up the mode&n;               with the last defined norm/size (or device default if not&n;               available) - it returns 0 if the mode is possible &n;   set_size -&gt; this fn-ref. sets the norm and image size for&n;               compression/decompression (returns 0 on success) &n;               the norm param is defined in videodev.h (VIDEO_MODE_*) &n;&n;   additional setup may be available, too - but the codec should work with&n;   some default values even without this &n;&n;   set_data -&gt; sets device-specific data (tables, quality etc.) &n;   get_data -&gt; query device-specific data (tables, quality etc.) &n;&n;   if the device delivers interrupts, they may be setup/handled here &n;   setup_interrupt -&gt; codec irq setup (not needed for 36050/60) &n;   handle_interrupt -&gt; codec irq handling (not needed for 36050/60) &n;&n;   if the device delivers pictures, they may be handled here &n;   put_image -&gt; puts image data to the codec (not needed for 36050/60) &n;   get_image -&gt; gets image data from the codec (not needed for 36050/60) &n;                the calls include frame numbers and flags (even/odd/...) &n;                if needed and a flag which allows blocking until its ready &n;*/
"&f;"
multiline_comment|/* ============== */
multiline_comment|/* user interface */
multiline_comment|/* ============== */
multiline_comment|/* &n;   Currently there is only a information display planned, as the layer&n;   is not visible for the user space at all.&n;&n;   Information is available via procfs. The current entry is &quot;/proc/videocodecs&quot;&n;   but it makes sense to &quot;hide&quot; it in the /proc/video tree of v4l(2) --TODO--.&n;&n;A example for such an output is:&n;&n;&lt;S&gt;lave or attached &lt;M&gt;aster name  type flags    magic    (connected as)&n;S                          zr36050 0002 0000d001 00000000 (TEMPLATE)&n;M                       zr36055[0] 0001 0000c001 00000000 (zr36050[0])&n;M                       zr36055[1] 0001 0000c001 00000000 (zr36050[1])&n;&n;*/
"&f;"
multiline_comment|/* =============================================== */
multiline_comment|/* special defines for the videocodec_io structure */
multiline_comment|/* =============================================== */
macro_line|#ifndef __LINUX_VIDEOCODEC_H
DECL|macro|__LINUX_VIDEOCODEC_H
mdefine_line|#define __LINUX_VIDEOCODEC_H
macro_line|#include &lt;linux/videodev.h&gt;
singleline_comment|//should be in videodev.h ??? (VID_DO_....)
DECL|macro|CODEC_DO_COMPRESSION
mdefine_line|#define CODEC_DO_COMPRESSION 0
DECL|macro|CODEC_DO_EXPANSION
mdefine_line|#define CODEC_DO_EXPANSION   1
multiline_comment|/* this are the current codec flags I think they are needed */
multiline_comment|/*  -&gt; type value in structure */
DECL|macro|CODEC_FLAG_JPEG
mdefine_line|#define CODEC_FLAG_JPEG      0x00000001L&t;
singleline_comment|// JPEG codec
DECL|macro|CODEC_FLAG_MPEG
mdefine_line|#define CODEC_FLAG_MPEG      0x00000002L&t;
singleline_comment|// MPEG1/2/4 codec
DECL|macro|CODEC_FLAG_DIVX
mdefine_line|#define CODEC_FLAG_DIVX      0x00000004L&t;
singleline_comment|// DIVX codec
DECL|macro|CODEC_FLAG_WAVELET
mdefine_line|#define CODEC_FLAG_WAVELET   0x00000008L&t;
singleline_comment|// WAVELET codec
singleline_comment|// room for other types
DECL|macro|CODEC_FLAG_MAGIC
mdefine_line|#define CODEC_FLAG_MAGIC     0x00000800L&t;
singleline_comment|// magic key must match
DECL|macro|CODEC_FLAG_HARDWARE
mdefine_line|#define CODEC_FLAG_HARDWARE  0x00001000L&t;
singleline_comment|// is a hardware codec
DECL|macro|CODEC_FLAG_VFE
mdefine_line|#define CODEC_FLAG_VFE       0x00002000L&t;
singleline_comment|// has direct video frontend
DECL|macro|CODEC_FLAG_ENCODER
mdefine_line|#define CODEC_FLAG_ENCODER   0x00004000L&t;
singleline_comment|// compression capability
DECL|macro|CODEC_FLAG_DECODER
mdefine_line|#define CODEC_FLAG_DECODER   0x00008000L&t;
singleline_comment|// decompression capability
DECL|macro|CODEC_FLAG_NEEDIRQ
mdefine_line|#define CODEC_FLAG_NEEDIRQ   0x00010000L&t;
singleline_comment|// needs irq handling
DECL|macro|CODEC_FLAG_RDWRPIC
mdefine_line|#define CODEC_FLAG_RDWRPIC   0x00020000L&t;
singleline_comment|// handles picture I/O
multiline_comment|/* a list of modes, some are just examples (is there any HW?) */
DECL|macro|CODEC_MODE_BJPG
mdefine_line|#define CODEC_MODE_BJPG      0x0001&t;
singleline_comment|// Baseline JPEG
DECL|macro|CODEC_MODE_LJPG
mdefine_line|#define CODEC_MODE_LJPG      0x0002&t;
singleline_comment|// Lossless JPEG
DECL|macro|CODEC_MODE_MPEG1
mdefine_line|#define CODEC_MODE_MPEG1     0x0003&t;
singleline_comment|// MPEG 1
DECL|macro|CODEC_MODE_MPEG2
mdefine_line|#define CODEC_MODE_MPEG2     0x0004&t;
singleline_comment|// MPEG 2
DECL|macro|CODEC_MODE_MPEG4
mdefine_line|#define CODEC_MODE_MPEG4     0x0005&t;
singleline_comment|// MPEG 4
DECL|macro|CODEC_MODE_MSDIVX
mdefine_line|#define CODEC_MODE_MSDIVX    0x0006&t;
singleline_comment|// MS DivX
DECL|macro|CODEC_MODE_ODIVX
mdefine_line|#define CODEC_MODE_ODIVX     0x0007&t;
singleline_comment|// Open DivX
DECL|macro|CODEC_MODE_WAVELET
mdefine_line|#define CODEC_MODE_WAVELET   0x0008&t;
singleline_comment|// Wavelet
multiline_comment|/* this are the current codec types I want to implement */
multiline_comment|/*  -&gt; type value in structure */
DECL|macro|CODEC_TYPE_NONE
mdefine_line|#define CODEC_TYPE_NONE    0
DECL|macro|CODEC_TYPE_L64702
mdefine_line|#define CODEC_TYPE_L64702  1
DECL|macro|CODEC_TYPE_ZR36050
mdefine_line|#define CODEC_TYPE_ZR36050 2
DECL|macro|CODEC_TYPE_ZR36016
mdefine_line|#define CODEC_TYPE_ZR36016 3
DECL|macro|CODEC_TYPE_ZR36060
mdefine_line|#define CODEC_TYPE_ZR36060 4
multiline_comment|/* the type of data may be enhanced by future implementations (data-fn.&squot;s) */
multiline_comment|/*  -&gt; used in command                                                     */
DECL|macro|CODEC_G_STATUS
mdefine_line|#define CODEC_G_STATUS         0x0000&t;/* codec status (query only) */
DECL|macro|CODEC_S_CODEC_MODE
mdefine_line|#define CODEC_S_CODEC_MODE     0x0001&t;/* codec mode (baseline JPEG, MPEG1,... */
DECL|macro|CODEC_G_CODEC_MODE
mdefine_line|#define CODEC_G_CODEC_MODE     0x8001
DECL|macro|CODEC_S_VFE
mdefine_line|#define CODEC_S_VFE            0x0002&t;/* additional video frontend setup */
DECL|macro|CODEC_G_VFE
mdefine_line|#define CODEC_G_VFE            0x8002
DECL|macro|CODEC_S_MMAP
mdefine_line|#define CODEC_S_MMAP           0x0003&t;/* MMAP setup (if available) */
DECL|macro|CODEC_S_JPEG_TDS_BYTE
mdefine_line|#define CODEC_S_JPEG_TDS_BYTE  0x0010&t;/* target data size in bytes */
DECL|macro|CODEC_G_JPEG_TDS_BYTE
mdefine_line|#define CODEC_G_JPEG_TDS_BYTE  0x8010
DECL|macro|CODEC_S_JPEG_SCALE
mdefine_line|#define CODEC_S_JPEG_SCALE     0x0011&t;/* scaling factor for quant. tables */
DECL|macro|CODEC_G_JPEG_SCALE
mdefine_line|#define CODEC_G_JPEG_SCALE     0x8011
DECL|macro|CODEC_S_JPEG_HDT_DATA
mdefine_line|#define CODEC_S_JPEG_HDT_DATA  0x0018&t;/* huffman-tables */
DECL|macro|CODEC_G_JPEG_HDT_DATA
mdefine_line|#define CODEC_G_JPEG_HDT_DATA  0x8018
DECL|macro|CODEC_S_JPEG_QDT_DATA
mdefine_line|#define CODEC_S_JPEG_QDT_DATA  0x0019&t;/* quantizing-tables */
DECL|macro|CODEC_G_JPEG_QDT_DATA
mdefine_line|#define CODEC_G_JPEG_QDT_DATA  0x8019
DECL|macro|CODEC_S_JPEG_APP_DATA
mdefine_line|#define CODEC_S_JPEG_APP_DATA  0x001A&t;/* APP marker */
DECL|macro|CODEC_G_JPEG_APP_DATA
mdefine_line|#define CODEC_G_JPEG_APP_DATA  0x801A
DECL|macro|CODEC_S_JPEG_COM_DATA
mdefine_line|#define CODEC_S_JPEG_COM_DATA  0x001B&t;/* COM marker */
DECL|macro|CODEC_G_JPEG_COM_DATA
mdefine_line|#define CODEC_G_JPEG_COM_DATA  0x801B
DECL|macro|CODEC_S_PRIVATE
mdefine_line|#define CODEC_S_PRIVATE        0x1000&t;/* &quot;private&quot; commands start here */
DECL|macro|CODEC_G_PRIVATE
mdefine_line|#define CODEC_G_PRIVATE        0x9000
DECL|macro|CODEC_G_FLAG
mdefine_line|#define CODEC_G_FLAG           0x8000&t;/* this is how &squot;get&squot; is detected */
multiline_comment|/* types of transfer, directly user space or a kernel buffer (image-fn.&squot;s) */
multiline_comment|/*  -&gt; used in get_image, put_image                                        */
DECL|macro|CODEC_TRANSFER_KERNEL
mdefine_line|#define CODEC_TRANSFER_KERNEL 0&t;/* use &quot;memcopy&quot; */
DECL|macro|CODEC_TRANSFER_USER
mdefine_line|#define CODEC_TRANSFER_USER   1&t;/* use &quot;to/from_user&quot; */
"&f;"
multiline_comment|/* ========================= */
multiline_comment|/* the structures itself ... */
multiline_comment|/* ========================= */
DECL|struct|vfe_polarity
r_struct
id|vfe_polarity
(brace
DECL|member|vsync_pol
r_int
id|vsync_pol
suffix:colon
l_int|1
suffix:semicolon
DECL|member|hsync_pol
r_int
id|hsync_pol
suffix:colon
l_int|1
suffix:semicolon
DECL|member|field_pol
r_int
id|field_pol
suffix:colon
l_int|1
suffix:semicolon
DECL|member|blank_pol
r_int
id|blank_pol
suffix:colon
l_int|1
suffix:semicolon
DECL|member|subimg_pol
r_int
id|subimg_pol
suffix:colon
l_int|1
suffix:semicolon
DECL|member|poe_pol
r_int
id|poe_pol
suffix:colon
l_int|1
suffix:semicolon
DECL|member|pvalid_pol
r_int
id|pvalid_pol
suffix:colon
l_int|1
suffix:semicolon
DECL|member|vclk_pol
r_int
id|vclk_pol
suffix:colon
l_int|1
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|vfe_settings
r_struct
id|vfe_settings
(brace
DECL|member|x
DECL|member|y
id|__u32
id|x
comma
id|y
suffix:semicolon
multiline_comment|/* Offsets into image */
DECL|member|width
DECL|member|height
id|__u32
id|width
comma
id|height
suffix:semicolon
multiline_comment|/* Area to capture */
DECL|member|decimation
id|__u16
id|decimation
suffix:semicolon
multiline_comment|/* Decimation divider */
DECL|member|flags
id|__u16
id|flags
suffix:semicolon
multiline_comment|/* Flags for capture */
multiline_comment|/* flags are the same as in struct video_capture - see videodev.h:&n;#define VIDEO_CAPTURE_ODD&t;&t;0&n;#define VIDEO_CAPTURE_EVEN&t;&t;1&n;*/
DECL|member|quality
id|__u16
id|quality
suffix:semicolon
multiline_comment|/* quality of the video */
)brace
suffix:semicolon
DECL|struct|tvnorm
r_struct
id|tvnorm
(brace
DECL|member|Wt
DECL|member|Wa
DECL|member|HStart
DECL|member|HSyncStart
DECL|member|Ht
DECL|member|Ha
DECL|member|VStart
id|u16
id|Wt
comma
id|Wa
comma
id|HStart
comma
id|HSyncStart
comma
id|Ht
comma
id|Ha
comma
id|VStart
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|jpeg_com_marker
r_struct
id|jpeg_com_marker
(brace
DECL|member|len
r_int
id|len
suffix:semicolon
multiline_comment|/* number of usable bytes in data */
DECL|member|data
r_char
id|data
(braket
l_int|60
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|jpeg_app_marker
r_struct
id|jpeg_app_marker
(brace
DECL|member|appn
r_int
id|appn
suffix:semicolon
multiline_comment|/* number app segment */
DECL|member|len
r_int
id|len
suffix:semicolon
multiline_comment|/* number of usable bytes in data */
DECL|member|data
r_char
id|data
(braket
l_int|60
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|videocodec
r_struct
id|videocodec
(brace
DECL|member|owner
r_struct
id|module
op_star
id|owner
suffix:semicolon
multiline_comment|/* -- filled in by slave device during register -- */
DECL|member|name
r_char
id|name
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|magic
r_int
r_int
id|magic
suffix:semicolon
multiline_comment|/* may be used for client&lt;-&gt;master attaching */
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* functionality flags */
DECL|member|type
r_int
r_int
id|type
suffix:semicolon
multiline_comment|/* codec type */
multiline_comment|/* -- these is filled in later during master device attach -- */
DECL|member|master_data
r_struct
id|videocodec_master
op_star
id|master_data
suffix:semicolon
multiline_comment|/* -- these are filled in by the slave device during register -- */
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
multiline_comment|/* private slave data */
multiline_comment|/* attach/detach client functions (indirect call) */
DECL|member|setup
r_int
(paren
op_star
id|setup
)paren
(paren
r_struct
id|videocodec
op_star
id|codec
)paren
suffix:semicolon
DECL|member|unset
r_int
(paren
op_star
id|unset
)paren
(paren
r_struct
id|videocodec
op_star
id|codec
)paren
suffix:semicolon
multiline_comment|/* main functions, every client needs them for sure! */
singleline_comment|// set compression or decompression (or freeze, stop, standby, etc)
DECL|member|set_mode
r_int
(paren
op_star
id|set_mode
)paren
(paren
r_struct
id|videocodec
op_star
id|codec
comma
r_int
id|mode
)paren
suffix:semicolon
singleline_comment|// setup picture size and norm (for the codec&squot;s video frontend)
DECL|member|set_video
r_int
(paren
op_star
id|set_video
)paren
(paren
r_struct
id|videocodec
op_star
id|codec
comma
r_struct
id|tvnorm
op_star
id|norm
comma
r_struct
id|vfe_settings
op_star
id|cap
comma
r_struct
id|vfe_polarity
op_star
id|pol
)paren
suffix:semicolon
singleline_comment|// other control commands, also mmap setup etc.
DECL|member|control
r_int
(paren
op_star
id|control
)paren
(paren
r_struct
id|videocodec
op_star
id|codec
comma
r_int
id|type
comma
r_int
id|size
comma
r_void
op_star
id|data
)paren
suffix:semicolon
multiline_comment|/* additional setup/query/processing (may be NULL pointer) */
singleline_comment|// interrupt setup / handling (for irq&squot;s delivered by master)
DECL|member|setup_interrupt
r_int
(paren
op_star
id|setup_interrupt
)paren
(paren
r_struct
id|videocodec
op_star
id|codec
comma
r_int
id|mode
)paren
suffix:semicolon
DECL|member|handle_interrupt
r_int
(paren
op_star
id|handle_interrupt
)paren
(paren
r_struct
id|videocodec
op_star
id|codec
comma
r_int
id|source
comma
r_int
id|flag
)paren
suffix:semicolon
singleline_comment|// picture interface (if any)
DECL|member|put_image
r_int
(paren
op_star
id|put_image
)paren
(paren
r_struct
id|videocodec
op_star
id|codec
comma
r_int
id|tr_type
comma
r_int
id|block
comma
r_int
op_star
id|fr_num
comma
r_int
op_star
id|flag
comma
r_int
id|size
comma
r_void
op_star
id|buf
)paren
suffix:semicolon
DECL|member|get_image
r_int
(paren
op_star
id|get_image
)paren
(paren
r_struct
id|videocodec
op_star
id|codec
comma
r_int
id|tr_type
comma
r_int
id|block
comma
r_int
op_star
id|fr_num
comma
r_int
op_star
id|flag
comma
r_int
id|size
comma
r_void
op_star
id|buf
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|videocodec_master
r_struct
id|videocodec_master
(brace
multiline_comment|/* -- filled in by master device for registration -- */
DECL|member|name
r_char
id|name
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|magic
r_int
r_int
id|magic
suffix:semicolon
multiline_comment|/* may be used for client&lt;-&gt;master attaching */
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* functionality flags */
DECL|member|type
r_int
r_int
id|type
suffix:semicolon
multiline_comment|/* master type */
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
multiline_comment|/* private master data */
DECL|member|readreg
id|__u32
c_func
(paren
op_star
id|readreg
)paren
(paren
r_struct
id|videocodec
op_star
id|codec
comma
id|__u16
id|reg
)paren
suffix:semicolon
DECL|member|writereg
r_void
(paren
op_star
id|writereg
)paren
(paren
r_struct
id|videocodec
op_star
id|codec
comma
id|__u16
id|reg
comma
id|__u32
id|value
)paren
suffix:semicolon
)brace
suffix:semicolon
"&f;"
multiline_comment|/* ================================================= */
multiline_comment|/* function prototypes of the master/slave interface */
multiline_comment|/* ================================================= */
multiline_comment|/* attach and detach commands for the master */
singleline_comment|// * master structure needs to be kmalloc&squot;ed before calling attach
singleline_comment|//   and free&squot;d after calling detach
singleline_comment|// * returns pointer on success, NULL on failure
r_extern
r_struct
id|videocodec
op_star
id|videocodec_attach
c_func
(paren
r_struct
id|videocodec_master
op_star
)paren
suffix:semicolon
singleline_comment|// * 0 on success, &lt;0 (errno) on failure
r_extern
r_int
id|videocodec_detach
c_func
(paren
r_struct
id|videocodec
op_star
)paren
suffix:semicolon
multiline_comment|/* register and unregister commands for the slaves */
singleline_comment|// * 0 on success, &lt;0 (errno) on failure
r_extern
r_int
id|videocodec_register
c_func
(paren
r_const
r_struct
id|videocodec
op_star
)paren
suffix:semicolon
singleline_comment|// * 0 on success, &lt;0 (errno) on failure
r_extern
r_int
id|videocodec_unregister
c_func
(paren
r_const
r_struct
id|videocodec
op_star
)paren
suffix:semicolon
multiline_comment|/* the other calls are directly done via the videocodec structure! */
macro_line|#endif&t;&t;&t;&t;/*ifndef __LINUX_VIDEOCODEC_H */
eof
