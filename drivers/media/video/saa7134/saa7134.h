multiline_comment|/*&n; * v4l2 device driver for philips saa7134 based TV cards&n; *&n; * (c) 2001,02 Gerd Knorr &lt;kraxel@bytesex.org&gt;&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;linux/videodev.h&gt;
macro_line|#include &lt;linux/kdev_t.h&gt;
macro_line|#include &lt;media/video-buf.h&gt;
macro_line|#include &lt;media/tuner.h&gt;
macro_line|#include &lt;media/audiochip.h&gt;
macro_line|#include &lt;media/id.h&gt;
DECL|macro|SAA7134_VERSION_CODE
mdefine_line|#define SAA7134_VERSION_CODE KERNEL_VERSION(0,2,2)
macro_line|#ifndef TRUE
DECL|macro|TRUE
macro_line|# define TRUE (1==1)
macro_line|#endif
macro_line|#ifndef FALSE
DECL|macro|FALSE
macro_line|# define FALSE (1==0)
macro_line|#endif
multiline_comment|/* 2.4 / 2.5 driver compatibility stuff */
multiline_comment|/* ----------------------------------------------------------- */
multiline_comment|/* enums                                                       */
DECL|enum|saa7134_tvaudio_mode
r_enum
id|saa7134_tvaudio_mode
(brace
DECL|enumerator|TVAUDIO_FM_MONO
id|TVAUDIO_FM_MONO
op_assign
l_int|1
comma
DECL|enumerator|TVAUDIO_FM_BG_STEREO
id|TVAUDIO_FM_BG_STEREO
op_assign
l_int|2
comma
DECL|enumerator|TVAUDIO_FM_SAT_STEREO
id|TVAUDIO_FM_SAT_STEREO
op_assign
l_int|3
comma
DECL|enumerator|TVAUDIO_FM_K_STEREO
id|TVAUDIO_FM_K_STEREO
op_assign
l_int|4
comma
DECL|enumerator|TVAUDIO_NICAM_AM
id|TVAUDIO_NICAM_AM
op_assign
l_int|5
comma
DECL|enumerator|TVAUDIO_NICAM_FM
id|TVAUDIO_NICAM_FM
op_assign
l_int|6
comma
)brace
suffix:semicolon
DECL|enum|saa7134_audio_in
r_enum
id|saa7134_audio_in
(brace
DECL|enumerator|TV
id|TV
op_assign
l_int|1
comma
DECL|enumerator|LINE1
id|LINE1
op_assign
l_int|2
comma
DECL|enumerator|LINE2
id|LINE2
op_assign
l_int|3
comma
)brace
suffix:semicolon
DECL|enum|saa7134_video_out
r_enum
id|saa7134_video_out
(brace
DECL|enumerator|CCIR656
id|CCIR656
op_assign
l_int|1
comma
)brace
suffix:semicolon
multiline_comment|/* ----------------------------------------------------------- */
multiline_comment|/* static data                                                 */
DECL|struct|saa7134_tvnorm
r_struct
id|saa7134_tvnorm
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|id
id|v4l2_std_id
id|id
suffix:semicolon
DECL|member|width
r_int
id|width
suffix:semicolon
DECL|member|height
r_int
id|height
suffix:semicolon
multiline_comment|/* video decoder */
DECL|member|sync_control
r_int
id|sync_control
suffix:semicolon
DECL|member|luma_control
r_int
id|luma_control
suffix:semicolon
DECL|member|chroma_ctrl1
r_int
id|chroma_ctrl1
suffix:semicolon
DECL|member|chroma_gain
r_int
id|chroma_gain
suffix:semicolon
DECL|member|chroma_ctrl2
r_int
id|chroma_ctrl2
suffix:semicolon
multiline_comment|/* video scaler */
DECL|member|h_start
r_int
id|h_start
suffix:semicolon
DECL|member|h_stop
r_int
id|h_stop
suffix:semicolon
DECL|member|video_v_start
r_int
id|video_v_start
suffix:semicolon
DECL|member|video_v_stop
r_int
id|video_v_stop
suffix:semicolon
DECL|member|vbi_v_start
r_int
id|vbi_v_start
suffix:semicolon
DECL|member|vbi_v_stop
r_int
id|vbi_v_stop
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|saa7134_tvaudio
r_struct
id|saa7134_tvaudio
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|std
r_int
id|std
suffix:semicolon
DECL|member|mode
r_enum
id|saa7134_tvaudio_mode
id|mode
suffix:semicolon
DECL|member|carr1
r_int
id|carr1
suffix:semicolon
DECL|member|carr2
r_int
id|carr2
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|saa7134_format
r_struct
id|saa7134_format
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|fourcc
r_int
id|fourcc
suffix:semicolon
DECL|member|depth
r_int
id|depth
suffix:semicolon
DECL|member|pm
r_int
id|pm
suffix:semicolon
DECL|member|vshift
r_int
id|vshift
suffix:semicolon
multiline_comment|/* vertical downsampling (for planar yuv) */
DECL|member|hshift
r_int
id|hshift
suffix:semicolon
multiline_comment|/* horizontal downsampling (for planar yuv) */
DECL|member|bswap
r_int
id|bswap
suffix:colon
l_int|1
suffix:semicolon
DECL|member|wswap
r_int
id|wswap
suffix:colon
l_int|1
suffix:semicolon
DECL|member|yuv
r_int
id|yuv
suffix:colon
l_int|1
suffix:semicolon
DECL|member|planar
r_int
id|planar
suffix:colon
l_int|1
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* ----------------------------------------------------------- */
multiline_comment|/* card configuration                                          */
DECL|macro|SAA7134_BOARD_NOAUTO
mdefine_line|#define SAA7134_BOARD_NOAUTO           -1
DECL|macro|SAA7134_BOARD_UNKNOWN
mdefine_line|#define SAA7134_BOARD_UNKNOWN           0
DECL|macro|SAA7134_BOARD_PROTEUS_PRO
mdefine_line|#define SAA7134_BOARD_PROTEUS_PRO       1
DECL|macro|SAA7134_BOARD_FLYVIDEO3000
mdefine_line|#define SAA7134_BOARD_FLYVIDEO3000      2
DECL|macro|SAA7134_BOARD_FLYVIDEO2000
mdefine_line|#define SAA7134_BOARD_FLYVIDEO2000      3
DECL|macro|SAA7134_BOARD_EMPRESS
mdefine_line|#define SAA7134_BOARD_EMPRESS           4
DECL|macro|SAA7134_BOARD_MONSTERTV
mdefine_line|#define SAA7134_BOARD_MONSTERTV         5
DECL|macro|SAA7134_BOARD_MD9717
mdefine_line|#define SAA7134_BOARD_MD9717            6
DECL|macro|SAA7134_BOARD_TVSTATION_RDS
mdefine_line|#define SAA7134_BOARD_TVSTATION_RDS     7
DECL|macro|SAA7134_BOARD_CINERGY400
mdefine_line|#define SAA7134_BOARD_CINERGY400&t;8
DECL|macro|SAA7134_BOARD_MD5044
mdefine_line|#define SAA7134_BOARD_MD5044&t;&t;9
DECL|macro|SAA7134_BOARD_KWORLD
mdefine_line|#define SAA7134_BOARD_KWORLD           10
DECL|macro|SAA7134_BOARD_CINERGY600
mdefine_line|#define SAA7134_BOARD_CINERGY600       11
DECL|macro|SAA7134_BOARD_MD7134
mdefine_line|#define SAA7134_BOARD_MD7134           12
DECL|macro|SAA7134_INPUT_MAX
mdefine_line|#define SAA7134_INPUT_MAX 8
DECL|struct|saa7134_input
r_struct
id|saa7134_input
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|vmux
r_int
id|vmux
suffix:semicolon
DECL|member|amux
r_enum
id|saa7134_audio_in
id|amux
suffix:semicolon
DECL|member|gpio
r_int
id|gpio
suffix:semicolon
DECL|member|tv
r_int
id|tv
suffix:colon
l_int|1
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|saa7134_board
r_struct
id|saa7134_board
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|audio_clock
r_int
id|audio_clock
suffix:semicolon
multiline_comment|/* input switching */
DECL|member|gpiomask
r_int
id|gpiomask
suffix:semicolon
DECL|member|inputs
r_struct
id|saa7134_input
id|inputs
(braket
id|SAA7134_INPUT_MAX
)braket
suffix:semicolon
DECL|member|radio
r_struct
id|saa7134_input
id|radio
suffix:semicolon
DECL|member|mute
r_struct
id|saa7134_input
id|mute
suffix:semicolon
multiline_comment|/* peripheral I/O */
DECL|member|i2s_rate
r_int
id|i2s_rate
suffix:semicolon
DECL|member|has_ts
r_int
id|has_ts
suffix:semicolon
DECL|member|video_out
r_enum
id|saa7134_video_out
id|video_out
suffix:semicolon
multiline_comment|/* i2c chip info */
DECL|member|tuner_type
r_int
id|tuner_type
suffix:semicolon
DECL|member|need_tda9887
r_int
id|need_tda9887
suffix:colon
l_int|1
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|card_has_audio
mdefine_line|#define card_has_audio(dev)   (dev-&gt;pci-&gt;device == PCI_DEVICE_ID_PHILIPS_SAA7134)
DECL|macro|card_has_radio
mdefine_line|#define card_has_radio(dev)   (NULL != saa7134_boards[dev-&gt;board].radio.name)
DECL|macro|card_has_ts
mdefine_line|#define card_has_ts(dev)      (saa7134_boards[dev-&gt;board].has_ts)
DECL|macro|card
mdefine_line|#define card(dev)             (saa7134_boards[dev-&gt;board])
DECL|macro|card_in
mdefine_line|#define card_in(dev,n)        (saa7134_boards[dev-&gt;board].inputs[n])
multiline_comment|/* ----------------------------------------------------------- */
multiline_comment|/* device / file handle status                                 */
DECL|macro|RESOURCE_OVERLAY
mdefine_line|#define RESOURCE_OVERLAY       1
DECL|macro|RESOURCE_VIDEO
mdefine_line|#define RESOURCE_VIDEO         2
DECL|macro|RESOURCE_VBI
mdefine_line|#define RESOURCE_VBI           4
DECL|macro|INTERLACE_AUTO
mdefine_line|#define INTERLACE_AUTO         0
DECL|macro|INTERLACE_ON
mdefine_line|#define INTERLACE_ON           1
DECL|macro|INTERLACE_OFF
mdefine_line|#define INTERLACE_OFF          2
DECL|macro|BUFFER_TIMEOUT
mdefine_line|#define BUFFER_TIMEOUT     (HZ/2)  /* 0.5 seconds */
r_struct
id|saa7134_dev
suffix:semicolon
r_struct
id|saa7134_dma
suffix:semicolon
multiline_comment|/* saa7134 page table */
DECL|struct|saa7134_pgtable
r_struct
id|saa7134_pgtable
(brace
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
DECL|member|cpu
id|u32
op_star
id|cpu
suffix:semicolon
DECL|member|dma
id|dma_addr_t
id|dma
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* tvaudio thread status */
DECL|struct|saa7134_thread
r_struct
id|saa7134_thread
(brace
DECL|member|task
r_struct
id|task_struct
op_star
id|task
suffix:semicolon
DECL|member|wq
id|wait_queue_head_t
id|wq
suffix:semicolon
DECL|member|notify
r_struct
id|semaphore
op_star
id|notify
suffix:semicolon
DECL|member|exit
r_int
m_exit
suffix:semicolon
DECL|member|scan1
r_int
id|scan1
suffix:semicolon
DECL|member|scan2
r_int
id|scan2
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* buffer for one video/vbi/ts frame */
DECL|struct|saa7134_buf
r_struct
id|saa7134_buf
(brace
multiline_comment|/* common v4l buffer stuff -- must be first */
DECL|member|vb
r_struct
id|videobuf_buffer
id|vb
suffix:semicolon
multiline_comment|/* saa7134 specific */
DECL|member|fmt
r_struct
id|saa7134_format
op_star
id|fmt
suffix:semicolon
DECL|member|top_seen
r_int
id|top_seen
suffix:semicolon
DECL|member|activate
r_int
(paren
op_star
id|activate
)paren
(paren
r_struct
id|saa7134_dev
op_star
id|dev
comma
r_struct
id|saa7134_buf
op_star
id|buf
comma
r_struct
id|saa7134_buf
op_star
id|next
)paren
suffix:semicolon
multiline_comment|/* page tables */
DECL|member|pt
r_struct
id|saa7134_pgtable
op_star
id|pt
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|saa7134_dmaqueue
r_struct
id|saa7134_dmaqueue
(brace
DECL|member|dev
r_struct
id|saa7134_dev
op_star
id|dev
suffix:semicolon
DECL|member|curr
r_struct
id|saa7134_buf
op_star
id|curr
suffix:semicolon
DECL|member|queue
r_struct
id|list_head
id|queue
suffix:semicolon
DECL|member|timeout
r_struct
id|timer_list
id|timeout
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* video filehandle status */
DECL|struct|saa7134_fh
r_struct
id|saa7134_fh
(brace
DECL|member|dev
r_struct
id|saa7134_dev
op_star
id|dev
suffix:semicolon
DECL|member|radio
r_int
id|radio
suffix:semicolon
DECL|member|type
r_enum
id|v4l2_buf_type
id|type
suffix:semicolon
DECL|member|win
r_struct
id|v4l2_window
id|win
suffix:semicolon
DECL|member|clips
r_struct
id|v4l2_clip
id|clips
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|nclips
r_int
id|nclips
suffix:semicolon
DECL|member|resources
r_int
id|resources
suffix:semicolon
multiline_comment|/* video capture */
DECL|member|fmt
r_struct
id|saa7134_format
op_star
id|fmt
suffix:semicolon
DECL|member|width
DECL|member|height
r_int
id|width
comma
id|height
suffix:semicolon
DECL|member|cap
r_struct
id|videobuf_queue
id|cap
suffix:semicolon
DECL|member|pt_cap
r_struct
id|saa7134_pgtable
id|pt_cap
suffix:semicolon
multiline_comment|/* vbi capture */
DECL|member|vbi
r_struct
id|videobuf_queue
id|vbi
suffix:semicolon
DECL|member|pt_vbi
r_struct
id|saa7134_pgtable
id|pt_vbi
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* TS status */
DECL|struct|saa7134_ts
r_struct
id|saa7134_ts
(brace
DECL|member|users
r_int
id|users
suffix:semicolon
multiline_comment|/* TS capture */
DECL|member|ts
r_struct
id|videobuf_queue
id|ts
suffix:semicolon
DECL|member|pt_ts
r_struct
id|saa7134_pgtable
id|pt_ts
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* oss dsp status */
DECL|struct|saa7134_oss
r_struct
id|saa7134_oss
(brace
DECL|member|lock
r_struct
id|semaphore
id|lock
suffix:semicolon
DECL|member|minor_mixer
r_int
id|minor_mixer
suffix:semicolon
DECL|member|minor_dsp
r_int
id|minor_dsp
suffix:semicolon
DECL|member|users_dsp
r_int
id|users_dsp
suffix:semicolon
multiline_comment|/* mixer */
DECL|member|input
r_enum
id|saa7134_audio_in
id|input
suffix:semicolon
DECL|member|count
r_int
id|count
suffix:semicolon
DECL|member|line1
r_int
id|line1
suffix:semicolon
DECL|member|line2
r_int
id|line2
suffix:semicolon
multiline_comment|/* dsp */
DECL|member|afmt
r_int
id|afmt
suffix:semicolon
DECL|member|rate
r_int
id|rate
suffix:semicolon
DECL|member|channels
r_int
id|channels
suffix:semicolon
DECL|member|recording
r_int
id|recording
suffix:semicolon
DECL|member|blocks
r_int
id|blocks
suffix:semicolon
DECL|member|blksize
r_int
id|blksize
suffix:semicolon
DECL|member|bufsize
r_int
id|bufsize
suffix:semicolon
DECL|member|pt
r_struct
id|saa7134_pgtable
id|pt
suffix:semicolon
DECL|member|dma
r_struct
id|videobuf_dmabuf
id|dma
suffix:semicolon
DECL|member|wq
id|wait_queue_head_t
id|wq
suffix:semicolon
DECL|member|dma_blk
r_int
id|dma_blk
suffix:semicolon
DECL|member|read_offset
r_int
id|read_offset
suffix:semicolon
DECL|member|read_count
r_int
id|read_count
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* global device status */
DECL|struct|saa7134_dev
r_struct
id|saa7134_dev
(brace
DECL|member|devlist
r_struct
id|list_head
id|devlist
suffix:semicolon
DECL|member|lock
r_struct
id|semaphore
id|lock
suffix:semicolon
DECL|member|slock
id|spinlock_t
id|slock
suffix:semicolon
multiline_comment|/* various device info */
DECL|member|resources
r_int
id|resources
suffix:semicolon
DECL|member|video_dev
r_struct
id|video_device
id|video_dev
suffix:semicolon
DECL|member|ts_dev
r_struct
id|video_device
id|ts_dev
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
DECL|member|oss
r_struct
id|saa7134_oss
id|oss
suffix:semicolon
DECL|member|ts
r_struct
id|saa7134_ts
id|ts
suffix:semicolon
multiline_comment|/* pci i/o */
DECL|member|name
r_char
id|name
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|pci
r_struct
id|pci_dev
op_star
id|pci
suffix:semicolon
DECL|member|pci_rev
DECL|member|pci_lat
r_int
r_char
id|pci_rev
comma
id|pci_lat
suffix:semicolon
DECL|member|lmmio
id|__u32
op_star
id|lmmio
suffix:semicolon
DECL|member|bmmio
id|__u8
op_star
id|bmmio
suffix:semicolon
multiline_comment|/* config info */
DECL|member|board
r_int
id|board
suffix:semicolon
DECL|member|tuner_type
r_int
id|tuner_type
suffix:semicolon
multiline_comment|/* i2c i/o */
DECL|member|i2c_adap
r_struct
id|i2c_adapter
id|i2c_adap
suffix:semicolon
DECL|member|i2c_client
r_struct
id|i2c_client
id|i2c_client
suffix:semicolon
DECL|member|eedata
r_int
r_char
id|eedata
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* video overlay */
DECL|member|ovbuf
r_struct
id|v4l2_framebuffer
id|ovbuf
suffix:semicolon
DECL|member|ovfmt
r_struct
id|saa7134_format
op_star
id|ovfmt
suffix:semicolon
DECL|member|ovenable
r_int
id|ovenable
suffix:semicolon
DECL|member|ovfield
r_enum
id|v4l2_field
id|ovfield
suffix:semicolon
multiline_comment|/* video+ts+vbi capture */
DECL|member|video_q
r_struct
id|saa7134_dmaqueue
id|video_q
suffix:semicolon
DECL|member|ts_q
r_struct
id|saa7134_dmaqueue
id|ts_q
suffix:semicolon
DECL|member|vbi_q
r_struct
id|saa7134_dmaqueue
id|vbi_q
suffix:semicolon
DECL|member|vbi_fieldcount
r_int
id|vbi_fieldcount
suffix:semicolon
multiline_comment|/* various v4l controls */
DECL|member|tvnorm
r_struct
id|saa7134_tvnorm
op_star
id|tvnorm
suffix:semicolon
multiline_comment|/* video */
DECL|member|tvaudio
r_struct
id|saa7134_tvaudio
op_star
id|tvaudio
suffix:semicolon
DECL|member|ctl_input
r_int
id|ctl_input
suffix:semicolon
DECL|member|ctl_bright
r_int
id|ctl_bright
suffix:semicolon
DECL|member|ctl_contrast
r_int
id|ctl_contrast
suffix:semicolon
DECL|member|ctl_hue
r_int
id|ctl_hue
suffix:semicolon
DECL|member|ctl_saturation
r_int
id|ctl_saturation
suffix:semicolon
DECL|member|ctl_freq
r_int
id|ctl_freq
suffix:semicolon
DECL|member|ctl_mute
r_int
id|ctl_mute
suffix:semicolon
multiline_comment|/* audio */
DECL|member|ctl_volume
r_int
id|ctl_volume
suffix:semicolon
DECL|member|ctl_invert
r_int
id|ctl_invert
suffix:semicolon
multiline_comment|/* private */
DECL|member|ctl_mirror
r_int
id|ctl_mirror
suffix:semicolon
DECL|member|ctl_y_odd
r_int
id|ctl_y_odd
suffix:semicolon
DECL|member|ctl_y_even
r_int
id|ctl_y_even
suffix:semicolon
multiline_comment|/* other global state info */
DECL|member|automute
r_int
id|automute
suffix:semicolon
DECL|member|thread
r_struct
id|saa7134_thread
id|thread
suffix:semicolon
DECL|member|input
r_struct
id|saa7134_input
op_star
id|input
suffix:semicolon
DECL|member|hw_input
r_struct
id|saa7134_input
op_star
id|hw_input
suffix:semicolon
DECL|member|hw_mute
r_int
id|hw_mute
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* ----------------------------------------------------------- */
DECL|macro|saa_readl
mdefine_line|#define saa_readl(reg)             readl(dev-&gt;lmmio + (reg))
DECL|macro|saa_writel
mdefine_line|#define saa_writel(reg,value)      writel((value), dev-&gt;lmmio + (reg));
DECL|macro|saa_andorl
mdefine_line|#define saa_andorl(reg,mask,value) &bslash;&n;  writel((readl(dev-&gt;lmmio+(reg)) &amp; ~(mask)) |&bslash;&n;  ((value) &amp; (mask)), dev-&gt;lmmio+(reg))
DECL|macro|saa_setl
mdefine_line|#define saa_setl(reg,bit)          saa_andorl((reg),(bit),(bit))
DECL|macro|saa_clearl
mdefine_line|#define saa_clearl(reg,bit)        saa_andorl((reg),(bit),0)
DECL|macro|saa_readb
mdefine_line|#define saa_readb(reg)             readb(dev-&gt;bmmio + (reg))
DECL|macro|saa_writeb
mdefine_line|#define saa_writeb(reg,value)      writeb((value), dev-&gt;bmmio + (reg));
DECL|macro|saa_andorb
mdefine_line|#define saa_andorb(reg,mask,value) &bslash;&n;  writeb((readb(dev-&gt;bmmio+(reg)) &amp; ~(mask)) |&bslash;&n;  ((value) &amp; (mask)), dev-&gt;bmmio+(reg))
DECL|macro|saa_setb
mdefine_line|#define saa_setb(reg,bit)          saa_andorb((reg),(bit),(bit))
DECL|macro|saa_clearb
mdefine_line|#define saa_clearb(reg,bit)        saa_andorb((reg),(bit),0)
multiline_comment|/* ----------------------------------------------------------- */
multiline_comment|/* saa7134-core.c                                              */
r_extern
r_struct
id|list_head
id|saa7134_devlist
suffix:semicolon
r_extern
r_int
id|saa7134_devcount
suffix:semicolon
r_void
id|saa7134_print_ioctl
c_func
(paren
r_char
op_star
id|name
comma
r_int
r_int
id|cmd
)paren
suffix:semicolon
r_void
id|saa7134_track_gpio
c_func
(paren
r_struct
id|saa7134_dev
op_star
id|dev
comma
r_char
op_star
id|msg
)paren
suffix:semicolon
DECL|macro|SAA7134_PGTABLE_SIZE
mdefine_line|#define SAA7134_PGTABLE_SIZE 4096
r_int
id|saa7134_pgtable_alloc
c_func
(paren
r_struct
id|pci_dev
op_star
id|pci
comma
r_struct
id|saa7134_pgtable
op_star
id|pt
)paren
suffix:semicolon
r_int
id|saa7134_pgtable_build
c_func
(paren
r_struct
id|pci_dev
op_star
id|pci
comma
r_struct
id|saa7134_pgtable
op_star
id|pt
comma
r_struct
id|scatterlist
op_star
id|list
comma
r_int
id|length
comma
r_int
id|startpage
)paren
suffix:semicolon
r_void
id|saa7134_pgtable_free
c_func
(paren
r_struct
id|pci_dev
op_star
id|pci
comma
r_struct
id|saa7134_pgtable
op_star
id|pt
)paren
suffix:semicolon
r_int
id|saa7134_buffer_count
c_func
(paren
r_int
id|size
comma
r_int
id|count
)paren
suffix:semicolon
r_int
id|saa7134_buffer_startpage
c_func
(paren
r_struct
id|saa7134_buf
op_star
id|buf
)paren
suffix:semicolon
r_int
r_int
id|saa7134_buffer_base
c_func
(paren
r_struct
id|saa7134_buf
op_star
id|buf
)paren
suffix:semicolon
r_int
id|saa7134_buffer_queue
c_func
(paren
r_struct
id|saa7134_dev
op_star
id|dev
comma
r_struct
id|saa7134_dmaqueue
op_star
id|q
comma
r_struct
id|saa7134_buf
op_star
id|buf
)paren
suffix:semicolon
r_void
id|saa7134_buffer_finish
c_func
(paren
r_struct
id|saa7134_dev
op_star
id|dev
comma
r_struct
id|saa7134_dmaqueue
op_star
id|q
comma
r_int
id|state
)paren
suffix:semicolon
r_void
id|saa7134_buffer_next
c_func
(paren
r_struct
id|saa7134_dev
op_star
id|dev
comma
r_struct
id|saa7134_dmaqueue
op_star
id|q
)paren
suffix:semicolon
r_void
id|saa7134_buffer_timeout
c_func
(paren
r_int
r_int
id|data
)paren
suffix:semicolon
r_void
id|saa7134_dma_free
c_func
(paren
r_struct
id|saa7134_dev
op_star
id|dev
comma
r_struct
id|saa7134_buf
op_star
id|buf
)paren
suffix:semicolon
r_int
id|saa7134_set_dmabits
c_func
(paren
r_struct
id|saa7134_dev
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/* ----------------------------------------------------------- */
multiline_comment|/* saa7134-cards.c                                             */
r_extern
r_struct
id|saa7134_board
id|saa7134_boards
(braket
)braket
suffix:semicolon
r_extern
r_const
r_int
id|saa7134_bcount
suffix:semicolon
r_extern
r_struct
id|pci_device_id
id|__devinitdata
id|saa7134_pci_tbl
(braket
)braket
suffix:semicolon
multiline_comment|/* ----------------------------------------------------------- */
multiline_comment|/* saa7134-i2c.c                                               */
r_int
id|saa7134_i2c_register
c_func
(paren
r_struct
id|saa7134_dev
op_star
id|dev
)paren
suffix:semicolon
r_int
id|saa7134_i2c_unregister
c_func
(paren
r_struct
id|saa7134_dev
op_star
id|dev
)paren
suffix:semicolon
r_void
id|saa7134_i2c_call_clients
c_func
(paren
r_struct
id|saa7134_dev
op_star
id|dev
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
multiline_comment|/* ----------------------------------------------------------- */
multiline_comment|/* saa7134-video.c                                             */
r_extern
r_struct
id|video_device
id|saa7134_video_template
suffix:semicolon
r_extern
r_struct
id|video_device
id|saa7134_radio_template
suffix:semicolon
r_int
id|saa7134_common_ioctl
c_func
(paren
r_struct
id|saa7134_dev
op_star
id|dev
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
id|saa7134_video_init
c_func
(paren
r_struct
id|saa7134_dev
op_star
id|dev
)paren
suffix:semicolon
r_int
id|saa7134_video_fini
c_func
(paren
r_struct
id|saa7134_dev
op_star
id|dev
)paren
suffix:semicolon
r_void
id|saa7134_irq_video_intl
c_func
(paren
r_struct
id|saa7134_dev
op_star
id|dev
)paren
suffix:semicolon
r_void
id|saa7134_irq_video_done
c_func
(paren
r_struct
id|saa7134_dev
op_star
id|dev
comma
r_int
r_int
id|status
)paren
suffix:semicolon
multiline_comment|/* ----------------------------------------------------------- */
multiline_comment|/* saa7134-ts.c                                                */
r_extern
r_struct
id|video_device
id|saa7134_ts_template
suffix:semicolon
r_int
id|saa7134_ts_init
c_func
(paren
r_struct
id|saa7134_dev
op_star
id|dev
)paren
suffix:semicolon
r_int
id|saa7134_ts_fini
c_func
(paren
r_struct
id|saa7134_dev
op_star
id|dev
)paren
suffix:semicolon
r_void
id|saa7134_irq_ts_done
c_func
(paren
r_struct
id|saa7134_dev
op_star
id|dev
comma
r_int
r_int
id|status
)paren
suffix:semicolon
multiline_comment|/* ----------------------------------------------------------- */
multiline_comment|/* saa7134-vbi.c                                               */
r_extern
r_struct
id|videobuf_queue_ops
id|saa7134_vbi_qops
suffix:semicolon
r_extern
r_struct
id|video_device
id|saa7134_vbi_template
suffix:semicolon
r_int
id|saa7134_vbi_init
c_func
(paren
r_struct
id|saa7134_dev
op_star
id|dev
)paren
suffix:semicolon
r_int
id|saa7134_vbi_fini
c_func
(paren
r_struct
id|saa7134_dev
op_star
id|dev
)paren
suffix:semicolon
r_void
id|saa7134_irq_vbi_done
c_func
(paren
r_struct
id|saa7134_dev
op_star
id|dev
comma
r_int
r_int
id|status
)paren
suffix:semicolon
multiline_comment|/* ----------------------------------------------------------- */
multiline_comment|/* saa7134-tvaudio.c                                           */
r_void
id|saa7134_tvaudio_setmute
c_func
(paren
r_struct
id|saa7134_dev
op_star
id|dev
)paren
suffix:semicolon
r_void
id|saa7134_tvaudio_setinput
c_func
(paren
r_struct
id|saa7134_dev
op_star
id|dev
comma
r_struct
id|saa7134_input
op_star
id|in
)paren
suffix:semicolon
r_void
id|saa7134_tvaudio_setvolume
c_func
(paren
r_struct
id|saa7134_dev
op_star
id|dev
comma
r_int
id|level
)paren
suffix:semicolon
r_int
id|saa7134_tvaudio_getstereo
c_func
(paren
r_struct
id|saa7134_dev
op_star
id|dev
comma
r_struct
id|saa7134_tvaudio
op_star
id|audio
)paren
suffix:semicolon
r_int
id|saa7134_tvaudio_init
c_func
(paren
r_struct
id|saa7134_dev
op_star
id|dev
)paren
suffix:semicolon
r_int
id|saa7134_tvaudio_fini
c_func
(paren
r_struct
id|saa7134_dev
op_star
id|dev
)paren
suffix:semicolon
r_int
id|saa7134_tvaudio_do_scan
c_func
(paren
r_struct
id|saa7134_dev
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/* ----------------------------------------------------------- */
multiline_comment|/* saa7134-oss.c                                               */
r_extern
r_struct
id|file_operations
id|saa7134_dsp_fops
suffix:semicolon
r_extern
r_struct
id|file_operations
id|saa7134_mixer_fops
suffix:semicolon
r_int
id|saa7134_oss_init
c_func
(paren
r_struct
id|saa7134_dev
op_star
id|dev
)paren
suffix:semicolon
r_int
id|saa7134_oss_fini
c_func
(paren
r_struct
id|saa7134_dev
op_star
id|dev
)paren
suffix:semicolon
r_void
id|saa7134_irq_oss_done
c_func
(paren
r_struct
id|saa7134_dev
op_star
id|dev
comma
r_int
r_int
id|status
)paren
suffix:semicolon
multiline_comment|/*&n; * Local variables:&n; * c-basic-offset: 8&n; * End:&n; */
eof
