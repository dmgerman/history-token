macro_line|#ifndef __LINUX_VIDEODEV_H
DECL|macro|__LINUX_VIDEODEV_H
mdefine_line|#define __LINUX_VIDEODEV_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#if 0
multiline_comment|/*&n; * v4l2 is still work-in-progress, integration planed for 2.5.x&n; *   v4l2 project homepage:   http://www.thedirks.org/v4l2/&n; *   patches available from:  http://bytesex.org/patches/&n; */
macro_line|# define HAVE_V4L2 1
macro_line|# include &lt;linux/videodev2.h&gt;
macro_line|#else
DECL|macro|HAVE_V4L2
macro_line|# undef HAVE_V4L2
macro_line|#endif
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
DECL|struct|video_device
r_struct
id|video_device
(brace
DECL|member|owner
r_struct
id|module
op_star
id|owner
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|type
r_int
id|type
suffix:semicolon
multiline_comment|/* v4l1 */
DECL|member|type2
r_int
id|type2
suffix:semicolon
multiline_comment|/* v4l2 */
DECL|member|hardware
r_int
id|hardware
suffix:semicolon
DECL|member|minor
r_int
id|minor
suffix:semicolon
multiline_comment|/* new interface -- we will use file_operations directly&n; &t; * like soundcore does.&n; &t; * kernel_ioctl() will be called by video_generic_ioctl.&n; &t; * video_generic_ioctl() does the userspace copying of the&n; &t; * ioctl arguments */
DECL|member|fops
r_struct
id|file_operations
op_star
id|fops
suffix:semicolon
DECL|member|kernel_ioctl
r_int
(paren
op_star
id|kernel_ioctl
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
DECL|member|priv
r_void
op_star
id|priv
suffix:semicolon
multiline_comment|/* Used to be &squot;private&squot; but that upsets C++ */
multiline_comment|/* for videodev.c intenal usage -- don&squot;t touch */
DECL|member|users
r_int
id|users
suffix:semicolon
DECL|member|lock
r_struct
id|semaphore
id|lock
suffix:semicolon
DECL|member|devfs_handle
id|devfs_handle_t
id|devfs_handle
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|VIDEO_MAJOR
mdefine_line|#define VIDEO_MAJOR&t;81
r_extern
r_int
id|video_register_device
c_func
(paren
r_struct
id|video_device
op_star
comma
r_int
id|type
comma
r_int
id|nr
)paren
suffix:semicolon
DECL|macro|VFL_TYPE_GRABBER
mdefine_line|#define VFL_TYPE_GRABBER&t;0
DECL|macro|VFL_TYPE_VBI
mdefine_line|#define VFL_TYPE_VBI&t;&t;1
DECL|macro|VFL_TYPE_RADIO
mdefine_line|#define VFL_TYPE_RADIO&t;&t;2
DECL|macro|VFL_TYPE_VTX
mdefine_line|#define VFL_TYPE_VTX&t;&t;3
r_extern
r_void
id|video_unregister_device
c_func
(paren
r_struct
id|video_device
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|video_device
op_star
id|video_devdata
c_func
(paren
r_struct
id|file
op_star
)paren
suffix:semicolon
r_extern
r_int
id|video_exclusive_open
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
)paren
suffix:semicolon
r_extern
r_int
id|video_exclusive_release
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
)paren
suffix:semicolon
r_extern
r_int
id|video_generic_ioctl
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
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
DECL|macro|VID_TYPE_CAPTURE
mdefine_line|#define VID_TYPE_CAPTURE&t;1&t;/* Can capture */
DECL|macro|VID_TYPE_TUNER
mdefine_line|#define VID_TYPE_TUNER&t;&t;2&t;/* Can tune */
DECL|macro|VID_TYPE_TELETEXT
mdefine_line|#define VID_TYPE_TELETEXT&t;4&t;/* Does teletext */
DECL|macro|VID_TYPE_OVERLAY
mdefine_line|#define VID_TYPE_OVERLAY&t;8&t;/* Overlay onto frame buffer */
DECL|macro|VID_TYPE_CHROMAKEY
mdefine_line|#define VID_TYPE_CHROMAKEY&t;16&t;/* Overlay by chromakey */
DECL|macro|VID_TYPE_CLIPPING
mdefine_line|#define VID_TYPE_CLIPPING&t;32&t;/* Can clip */
DECL|macro|VID_TYPE_FRAMERAM
mdefine_line|#define VID_TYPE_FRAMERAM&t;64&t;/* Uses the frame buffer memory */
DECL|macro|VID_TYPE_SCALES
mdefine_line|#define VID_TYPE_SCALES&t;&t;128&t;/* Scalable */
DECL|macro|VID_TYPE_MONOCHROME
mdefine_line|#define VID_TYPE_MONOCHROME&t;256&t;/* Monochrome only */
DECL|macro|VID_TYPE_SUBCAPTURE
mdefine_line|#define VID_TYPE_SUBCAPTURE&t;512&t;/* Can capture subareas of the image */
DECL|macro|VID_TYPE_MPEG_DECODER
mdefine_line|#define VID_TYPE_MPEG_DECODER&t;1024&t;/* Can decode MPEG streams */
DECL|macro|VID_TYPE_MPEG_ENCODER
mdefine_line|#define VID_TYPE_MPEG_ENCODER&t;2048&t;/* Can encode MPEG streams */
DECL|macro|VID_TYPE_MJPEG_DECODER
mdefine_line|#define VID_TYPE_MJPEG_DECODER&t;4096&t;/* Can decode MJPEG streams */
DECL|macro|VID_TYPE_MJPEG_ENCODER
mdefine_line|#define VID_TYPE_MJPEG_ENCODER&t;8192&t;/* Can encode MJPEG streams */
DECL|struct|video_capability
r_struct
id|video_capability
(brace
DECL|member|name
r_char
id|name
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|type
r_int
id|type
suffix:semicolon
DECL|member|channels
r_int
id|channels
suffix:semicolon
multiline_comment|/* Num channels */
DECL|member|audios
r_int
id|audios
suffix:semicolon
multiline_comment|/* Num audio devices */
DECL|member|maxwidth
r_int
id|maxwidth
suffix:semicolon
multiline_comment|/* Supported width */
DECL|member|maxheight
r_int
id|maxheight
suffix:semicolon
multiline_comment|/* And height */
DECL|member|minwidth
r_int
id|minwidth
suffix:semicolon
multiline_comment|/* Supported width */
DECL|member|minheight
r_int
id|minheight
suffix:semicolon
multiline_comment|/* And height */
)brace
suffix:semicolon
DECL|struct|video_channel
r_struct
id|video_channel
(brace
DECL|member|channel
r_int
id|channel
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|tuners
r_int
id|tuners
suffix:semicolon
DECL|member|flags
id|__u32
id|flags
suffix:semicolon
DECL|macro|VIDEO_VC_TUNER
mdefine_line|#define VIDEO_VC_TUNER&t;&t;1&t;/* Channel has a tuner */
DECL|macro|VIDEO_VC_AUDIO
mdefine_line|#define VIDEO_VC_AUDIO&t;&t;2&t;/* Channel has audio */
DECL|member|type
id|__u16
id|type
suffix:semicolon
DECL|macro|VIDEO_TYPE_TV
mdefine_line|#define VIDEO_TYPE_TV&t;&t;1
DECL|macro|VIDEO_TYPE_CAMERA
mdefine_line|#define VIDEO_TYPE_CAMERA&t;2&t;
DECL|member|norm
id|__u16
id|norm
suffix:semicolon
multiline_comment|/* Norm set by channel */
)brace
suffix:semicolon
DECL|struct|video_tuner
r_struct
id|video_tuner
(brace
DECL|member|tuner
r_int
id|tuner
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|rangelow
DECL|member|rangehigh
r_int
r_int
id|rangelow
comma
id|rangehigh
suffix:semicolon
multiline_comment|/* Tuner range */
DECL|member|flags
id|__u32
id|flags
suffix:semicolon
DECL|macro|VIDEO_TUNER_PAL
mdefine_line|#define VIDEO_TUNER_PAL&t;&t;1
DECL|macro|VIDEO_TUNER_NTSC
mdefine_line|#define VIDEO_TUNER_NTSC&t;2
DECL|macro|VIDEO_TUNER_SECAM
mdefine_line|#define VIDEO_TUNER_SECAM&t;4
DECL|macro|VIDEO_TUNER_LOW
mdefine_line|#define VIDEO_TUNER_LOW&t;&t;8&t;/* Uses KHz not MHz */
DECL|macro|VIDEO_TUNER_NORM
mdefine_line|#define VIDEO_TUNER_NORM&t;16&t;/* Tuner can set norm */
DECL|macro|VIDEO_TUNER_STEREO_ON
mdefine_line|#define VIDEO_TUNER_STEREO_ON&t;128&t;/* Tuner is seeing stereo */
DECL|macro|VIDEO_TUNER_RDS_ON
mdefine_line|#define VIDEO_TUNER_RDS_ON      256     /* Tuner is seeing an RDS datastream */
DECL|macro|VIDEO_TUNER_MBS_ON
mdefine_line|#define VIDEO_TUNER_MBS_ON      512     /* Tuner is seeing an MBS datastream */
DECL|member|mode
id|__u16
id|mode
suffix:semicolon
multiline_comment|/* PAL/NTSC/SECAM/OTHER */
DECL|macro|VIDEO_MODE_PAL
mdefine_line|#define VIDEO_MODE_PAL&t;&t;0
DECL|macro|VIDEO_MODE_NTSC
mdefine_line|#define VIDEO_MODE_NTSC&t;&t;1
DECL|macro|VIDEO_MODE_SECAM
mdefine_line|#define VIDEO_MODE_SECAM&t;2
DECL|macro|VIDEO_MODE_AUTO
mdefine_line|#define VIDEO_MODE_AUTO&t;&t;3
DECL|member|signal
id|__u16
id|signal
suffix:semicolon
multiline_comment|/* Signal strength 16bit scale */
)brace
suffix:semicolon
DECL|struct|video_picture
r_struct
id|video_picture
(brace
DECL|member|brightness
id|__u16
id|brightness
suffix:semicolon
DECL|member|hue
id|__u16
id|hue
suffix:semicolon
DECL|member|colour
id|__u16
id|colour
suffix:semicolon
DECL|member|contrast
id|__u16
id|contrast
suffix:semicolon
DECL|member|whiteness
id|__u16
id|whiteness
suffix:semicolon
multiline_comment|/* Black and white only */
DECL|member|depth
id|__u16
id|depth
suffix:semicolon
multiline_comment|/* Capture depth */
DECL|member|palette
id|__u16
id|palette
suffix:semicolon
multiline_comment|/* Palette in use */
DECL|macro|VIDEO_PALETTE_GREY
mdefine_line|#define VIDEO_PALETTE_GREY&t;1&t;/* Linear greyscale */
DECL|macro|VIDEO_PALETTE_HI240
mdefine_line|#define VIDEO_PALETTE_HI240&t;2&t;/* High 240 cube (BT848) */
DECL|macro|VIDEO_PALETTE_RGB565
mdefine_line|#define VIDEO_PALETTE_RGB565&t;3&t;/* 565 16 bit RGB */
DECL|macro|VIDEO_PALETTE_RGB24
mdefine_line|#define VIDEO_PALETTE_RGB24&t;4&t;/* 24bit RGB */
DECL|macro|VIDEO_PALETTE_RGB32
mdefine_line|#define VIDEO_PALETTE_RGB32&t;5&t;/* 32bit RGB */&t;
DECL|macro|VIDEO_PALETTE_RGB555
mdefine_line|#define VIDEO_PALETTE_RGB555&t;6&t;/* 555 15bit RGB */
DECL|macro|VIDEO_PALETTE_YUV422
mdefine_line|#define VIDEO_PALETTE_YUV422&t;7&t;/* YUV422 capture */
DECL|macro|VIDEO_PALETTE_YUYV
mdefine_line|#define VIDEO_PALETTE_YUYV&t;8
DECL|macro|VIDEO_PALETTE_UYVY
mdefine_line|#define VIDEO_PALETTE_UYVY&t;9&t;/* The great thing about standards is ... */
DECL|macro|VIDEO_PALETTE_YUV420
mdefine_line|#define VIDEO_PALETTE_YUV420&t;10
DECL|macro|VIDEO_PALETTE_YUV411
mdefine_line|#define VIDEO_PALETTE_YUV411&t;11&t;/* YUV411 capture */
DECL|macro|VIDEO_PALETTE_RAW
mdefine_line|#define VIDEO_PALETTE_RAW&t;12&t;/* RAW capture (BT848) */
DECL|macro|VIDEO_PALETTE_YUV422P
mdefine_line|#define VIDEO_PALETTE_YUV422P&t;13&t;/* YUV 4:2:2 Planar */
DECL|macro|VIDEO_PALETTE_YUV411P
mdefine_line|#define VIDEO_PALETTE_YUV411P&t;14&t;/* YUV 4:1:1 Planar */
DECL|macro|VIDEO_PALETTE_YUV420P
mdefine_line|#define VIDEO_PALETTE_YUV420P&t;15&t;/* YUV 4:2:0 Planar */
DECL|macro|VIDEO_PALETTE_YUV410P
mdefine_line|#define VIDEO_PALETTE_YUV410P&t;16&t;/* YUV 4:1:0 Planar */
DECL|macro|VIDEO_PALETTE_PLANAR
mdefine_line|#define VIDEO_PALETTE_PLANAR&t;13&t;/* start of planar entries */
DECL|macro|VIDEO_PALETTE_COMPONENT
mdefine_line|#define VIDEO_PALETTE_COMPONENT 7&t;/* start of component entries */
)brace
suffix:semicolon
DECL|struct|video_audio
r_struct
id|video_audio
(brace
DECL|member|audio
r_int
id|audio
suffix:semicolon
multiline_comment|/* Audio channel */
DECL|member|volume
id|__u16
id|volume
suffix:semicolon
multiline_comment|/* If settable */
DECL|member|bass
DECL|member|treble
id|__u16
id|bass
comma
id|treble
suffix:semicolon
DECL|member|flags
id|__u32
id|flags
suffix:semicolon
DECL|macro|VIDEO_AUDIO_MUTE
mdefine_line|#define VIDEO_AUDIO_MUTE&t;1
DECL|macro|VIDEO_AUDIO_MUTABLE
mdefine_line|#define VIDEO_AUDIO_MUTABLE&t;2
DECL|macro|VIDEO_AUDIO_VOLUME
mdefine_line|#define VIDEO_AUDIO_VOLUME&t;4
DECL|macro|VIDEO_AUDIO_BASS
mdefine_line|#define VIDEO_AUDIO_BASS&t;8
DECL|macro|VIDEO_AUDIO_TREBLE
mdefine_line|#define VIDEO_AUDIO_TREBLE&t;16&t;
DECL|macro|VIDEO_AUDIO_BALANCE
mdefine_line|#define VIDEO_AUDIO_BALANCE&t;32
DECL|member|name
r_char
id|name
(braket
l_int|16
)braket
suffix:semicolon
DECL|macro|VIDEO_SOUND_MONO
mdefine_line|#define VIDEO_SOUND_MONO&t;1
DECL|macro|VIDEO_SOUND_STEREO
mdefine_line|#define VIDEO_SOUND_STEREO&t;2
DECL|macro|VIDEO_SOUND_LANG1
mdefine_line|#define VIDEO_SOUND_LANG1&t;4
DECL|macro|VIDEO_SOUND_LANG2
mdefine_line|#define VIDEO_SOUND_LANG2&t;8
DECL|member|mode
id|__u16
id|mode
suffix:semicolon
DECL|member|balance
id|__u16
id|balance
suffix:semicolon
multiline_comment|/* Stereo balance */
DECL|member|step
id|__u16
id|step
suffix:semicolon
multiline_comment|/* Step actual volume uses */
)brace
suffix:semicolon
DECL|struct|video_clip
r_struct
id|video_clip
(brace
DECL|member|x
DECL|member|y
id|__s32
id|x
comma
id|y
suffix:semicolon
DECL|member|width
DECL|member|height
id|__s32
id|width
comma
id|height
suffix:semicolon
DECL|member|next
r_struct
id|video_clip
op_star
id|next
suffix:semicolon
multiline_comment|/* For user use/driver use only */
)brace
suffix:semicolon
DECL|struct|video_window
r_struct
id|video_window
(brace
DECL|member|x
DECL|member|y
id|__u32
id|x
comma
id|y
suffix:semicolon
multiline_comment|/* Position of window */
DECL|member|width
DECL|member|height
id|__u32
id|width
comma
id|height
suffix:semicolon
multiline_comment|/* Its size */
DECL|member|chromakey
id|__u32
id|chromakey
suffix:semicolon
DECL|member|flags
id|__u32
id|flags
suffix:semicolon
DECL|member|clips
r_struct
id|video_clip
op_star
id|clips
suffix:semicolon
multiline_comment|/* Set only */
DECL|member|clipcount
r_int
id|clipcount
suffix:semicolon
DECL|macro|VIDEO_WINDOW_INTERLACE
mdefine_line|#define VIDEO_WINDOW_INTERLACE&t;1
DECL|macro|VIDEO_WINDOW_CHROMAKEY
mdefine_line|#define VIDEO_WINDOW_CHROMAKEY&t;16&t;/* Overlay by chromakey */
DECL|macro|VIDEO_CLIP_BITMAP
mdefine_line|#define VIDEO_CLIP_BITMAP&t;-1
multiline_comment|/* bitmap is 1024x625, a &squot;1&squot; bit represents a clipped pixel */
DECL|macro|VIDEO_CLIPMAP_SIZE
mdefine_line|#define VIDEO_CLIPMAP_SIZE&t;(128 * 625)
)brace
suffix:semicolon
DECL|struct|video_capture
r_struct
id|video_capture
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
DECL|macro|VIDEO_CAPTURE_ODD
mdefine_line|#define VIDEO_CAPTURE_ODD&t;&t;0&t;/* Temporal */
DECL|macro|VIDEO_CAPTURE_EVEN
mdefine_line|#define VIDEO_CAPTURE_EVEN&t;&t;1
)brace
suffix:semicolon
DECL|struct|video_buffer
r_struct
id|video_buffer
(brace
DECL|member|base
r_void
op_star
id|base
suffix:semicolon
DECL|member|height
DECL|member|width
r_int
id|height
comma
id|width
suffix:semicolon
DECL|member|depth
r_int
id|depth
suffix:semicolon
DECL|member|bytesperline
r_int
id|bytesperline
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|video_mmap
r_struct
id|video_mmap
(brace
DECL|member|frame
r_int
r_int
id|frame
suffix:semicolon
multiline_comment|/* Frame (0 - n) for double buffer */
DECL|member|height
DECL|member|width
r_int
id|height
comma
id|width
suffix:semicolon
DECL|member|format
r_int
r_int
id|format
suffix:semicolon
multiline_comment|/* should be VIDEO_PALETTE_* */
)brace
suffix:semicolon
DECL|struct|video_key
r_struct
id|video_key
(brace
DECL|member|key
id|__u8
id|key
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|flags
id|__u32
id|flags
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|VIDEO_MAX_FRAME
mdefine_line|#define VIDEO_MAX_FRAME&t;&t;32
DECL|struct|video_mbuf
r_struct
id|video_mbuf
(brace
DECL|member|size
r_int
id|size
suffix:semicolon
multiline_comment|/* Total memory to map */
DECL|member|frames
r_int
id|frames
suffix:semicolon
multiline_comment|/* Frames */
DECL|member|offsets
r_int
id|offsets
(braket
id|VIDEO_MAX_FRAME
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|VIDEO_NO_UNIT
mdefine_line|#define &t;VIDEO_NO_UNIT&t;(-1)
DECL|struct|video_unit
r_struct
id|video_unit
(brace
DECL|member|video
r_int
id|video
suffix:semicolon
multiline_comment|/* Video minor */
DECL|member|vbi
r_int
id|vbi
suffix:semicolon
multiline_comment|/* VBI minor */
DECL|member|radio
r_int
id|radio
suffix:semicolon
multiline_comment|/* Radio minor */
DECL|member|audio
r_int
id|audio
suffix:semicolon
multiline_comment|/* Audio minor */
DECL|member|teletext
r_int
id|teletext
suffix:semicolon
multiline_comment|/* Teletext minor */
)brace
suffix:semicolon
DECL|struct|vbi_format
r_struct
id|vbi_format
(brace
DECL|member|sampling_rate
id|__u32
id|sampling_rate
suffix:semicolon
multiline_comment|/* in Hz */
DECL|member|samples_per_line
id|__u32
id|samples_per_line
suffix:semicolon
DECL|member|sample_format
id|__u32
id|sample_format
suffix:semicolon
multiline_comment|/* VIDEO_PALETTE_RAW only (1 byte) */
DECL|member|start
id|__s32
id|start
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* starting line for each frame */
DECL|member|count
id|__u32
id|count
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* count of lines for each frame */
DECL|member|flags
id|__u32
id|flags
suffix:semicolon
DECL|macro|VBI_UNSYNC
mdefine_line|#define&t;VBI_UNSYNC&t;1&t;/* can distingues between top/bottom field */
DECL|macro|VBI_INTERLACED
mdefine_line|#define&t;VBI_INTERLACED&t;2&t;/* lines are interlaced */
)brace
suffix:semicolon
multiline_comment|/* video_info is biased towards hardware mpeg encode/decode */
multiline_comment|/* but it could apply generically to any hardware compressor/decompressor */
DECL|struct|video_info
r_struct
id|video_info
(brace
DECL|member|frame_count
id|__u32
id|frame_count
suffix:semicolon
multiline_comment|/* frames output since decode/encode began */
DECL|member|h_size
id|__u32
id|h_size
suffix:semicolon
multiline_comment|/* current unscaled horizontal size */
DECL|member|v_size
id|__u32
id|v_size
suffix:semicolon
multiline_comment|/* current unscaled veritcal size */
DECL|member|smpte_timecode
id|__u32
id|smpte_timecode
suffix:semicolon
multiline_comment|/* current SMPTE timecode (for current GOP) */
DECL|member|picture_type
id|__u32
id|picture_type
suffix:semicolon
multiline_comment|/* current picture type */
DECL|member|temporal_reference
id|__u32
id|temporal_reference
suffix:semicolon
multiline_comment|/* current temporal reference */
DECL|member|user_data
id|__u8
id|user_data
(braket
l_int|256
)braket
suffix:semicolon
multiline_comment|/* user data last found in compressed stream */
multiline_comment|/* user_data[0] contains user data flags, user_data[1] has count */
)brace
suffix:semicolon
multiline_comment|/* generic structure for setting playback modes */
DECL|struct|video_play_mode
r_struct
id|video_play_mode
(brace
DECL|member|mode
r_int
id|mode
suffix:semicolon
DECL|member|p1
r_int
id|p1
suffix:semicolon
DECL|member|p2
r_int
id|p2
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* for loading microcode / fpga programming */
DECL|struct|video_code
r_struct
id|video_code
(brace
DECL|member|loadwhat
r_char
id|loadwhat
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* name or tag of file being passed */
DECL|member|datasize
r_int
id|datasize
suffix:semicolon
DECL|member|data
id|__u8
op_star
id|data
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|VIDIOCGCAP
mdefine_line|#define VIDIOCGCAP&t;&t;_IOR(&squot;v&squot;,1,struct video_capability)&t;/* Get capabilities */
DECL|macro|VIDIOCGCHAN
mdefine_line|#define VIDIOCGCHAN&t;&t;_IOWR(&squot;v&squot;,2,struct video_channel)&t;/* Get channel info (sources) */
DECL|macro|VIDIOCSCHAN
mdefine_line|#define VIDIOCSCHAN&t;&t;_IOW(&squot;v&squot;,3,struct video_channel)&t;/* Set channel &t;*/
DECL|macro|VIDIOCGTUNER
mdefine_line|#define VIDIOCGTUNER&t;&t;_IOWR(&squot;v&squot;,4,struct video_tuner)&t;&t;/* Get tuner abilities */
DECL|macro|VIDIOCSTUNER
mdefine_line|#define VIDIOCSTUNER&t;&t;_IOW(&squot;v&squot;,5,struct video_tuner)&t;&t;/* Tune the tuner for the current channel */
DECL|macro|VIDIOCGPICT
mdefine_line|#define VIDIOCGPICT&t;&t;_IOR(&squot;v&squot;,6,struct video_picture)&t;/* Get picture properties */
DECL|macro|VIDIOCSPICT
mdefine_line|#define VIDIOCSPICT&t;&t;_IOW(&squot;v&squot;,7,struct video_picture)&t;/* Set picture properties */
DECL|macro|VIDIOCCAPTURE
mdefine_line|#define VIDIOCCAPTURE&t;&t;_IOW(&squot;v&squot;,8,int)&t;&t;&t;&t;/* Start, end capture */
DECL|macro|VIDIOCGWIN
mdefine_line|#define VIDIOCGWIN&t;&t;_IOR(&squot;v&squot;,9, struct video_window)&t;/* Get the video overlay window */
DECL|macro|VIDIOCSWIN
mdefine_line|#define VIDIOCSWIN&t;&t;_IOW(&squot;v&squot;,10, struct video_window)&t;/* Set the video overlay window - passes clip list for hardware smarts , chromakey etc */
DECL|macro|VIDIOCGFBUF
mdefine_line|#define VIDIOCGFBUF&t;&t;_IOR(&squot;v&squot;,11, struct video_buffer)&t;/* Get frame buffer */
DECL|macro|VIDIOCSFBUF
mdefine_line|#define VIDIOCSFBUF&t;&t;_IOW(&squot;v&squot;,12, struct video_buffer)&t;/* Set frame buffer - root only */
DECL|macro|VIDIOCKEY
mdefine_line|#define VIDIOCKEY&t;&t;_IOR(&squot;v&squot;,13, struct video_key)&t;&t;/* Video key event - to dev 255 is to all - cuts capture on all DMA windows with this key (0xFFFFFFFF == all) */
DECL|macro|VIDIOCGFREQ
mdefine_line|#define VIDIOCGFREQ&t;&t;_IOR(&squot;v&squot;,14, unsigned long)&t;&t;/* Set tuner */
DECL|macro|VIDIOCSFREQ
mdefine_line|#define VIDIOCSFREQ&t;&t;_IOW(&squot;v&squot;,15, unsigned long)&t;&t;/* Set tuner */
DECL|macro|VIDIOCGAUDIO
mdefine_line|#define VIDIOCGAUDIO&t;&t;_IOR(&squot;v&squot;,16, struct video_audio)&t;/* Get audio info */
DECL|macro|VIDIOCSAUDIO
mdefine_line|#define VIDIOCSAUDIO&t;&t;_IOW(&squot;v&squot;,17, struct video_audio)&t;/* Audio source, mute etc */
DECL|macro|VIDIOCSYNC
mdefine_line|#define VIDIOCSYNC&t;&t;_IOW(&squot;v&squot;,18, int)&t;&t;&t;/* Sync with mmap grabbing */
DECL|macro|VIDIOCMCAPTURE
mdefine_line|#define VIDIOCMCAPTURE&t;&t;_IOW(&squot;v&squot;,19, struct video_mmap)&t;&t;/* Grab frames */
DECL|macro|VIDIOCGMBUF
mdefine_line|#define VIDIOCGMBUF&t;&t;_IOR(&squot;v&squot;,20, struct video_mbuf)&t;&t;/* Memory map buffer info */
DECL|macro|VIDIOCGUNIT
mdefine_line|#define VIDIOCGUNIT&t;&t;_IOR(&squot;v&squot;,21, struct video_unit)&t;&t;/* Get attached units */
DECL|macro|VIDIOCGCAPTURE
mdefine_line|#define VIDIOCGCAPTURE&t;&t;_IOR(&squot;v&squot;,22, struct video_capture)&t;/* Get subcapture */
DECL|macro|VIDIOCSCAPTURE
mdefine_line|#define VIDIOCSCAPTURE&t;&t;_IOW(&squot;v&squot;,23, struct video_capture)&t;/* Set subcapture */
DECL|macro|VIDIOCSPLAYMODE
mdefine_line|#define VIDIOCSPLAYMODE&t;&t;_IOW(&squot;v&squot;,24, struct video_play_mode)&t;/* Set output video mode/feature */
DECL|macro|VIDIOCSWRITEMODE
mdefine_line|#define VIDIOCSWRITEMODE&t;_IOW(&squot;v&squot;,25, int)&t;&t;&t;/* Set write mode */
DECL|macro|VIDIOCGPLAYINFO
mdefine_line|#define VIDIOCGPLAYINFO&t;&t;_IOR(&squot;v&squot;,26, struct video_info)&t;&t;/* Get current playback info from hardware */
DECL|macro|VIDIOCSMICROCODE
mdefine_line|#define VIDIOCSMICROCODE&t;_IOW(&squot;v&squot;,27, struct video_code)&t;&t;/* Load microcode into hardware */
DECL|macro|VIDIOCGVBIFMT
mdefine_line|#define&t;VIDIOCGVBIFMT&t;&t;_IOR(&squot;v&squot;,28, struct vbi_format)&t;&t;/* Get VBI information */
DECL|macro|VIDIOCSVBIFMT
mdefine_line|#define&t;VIDIOCSVBIFMT&t;&t;_IOW(&squot;v&squot;,29, struct vbi_format)&t;&t;/* Set VBI information */
DECL|macro|BASE_VIDIOCPRIVATE
mdefine_line|#define BASE_VIDIOCPRIVATE&t;192&t;&t;/* 192-255 are private */
multiline_comment|/* VIDIOCSWRITEMODE */
DECL|macro|VID_WRITE_MPEG_AUD
mdefine_line|#define VID_WRITE_MPEG_AUD&t;&t;0
DECL|macro|VID_WRITE_MPEG_VID
mdefine_line|#define VID_WRITE_MPEG_VID&t;&t;1
DECL|macro|VID_WRITE_OSD
mdefine_line|#define VID_WRITE_OSD&t;&t;&t;2
DECL|macro|VID_WRITE_TTX
mdefine_line|#define VID_WRITE_TTX&t;&t;&t;3
DECL|macro|VID_WRITE_CC
mdefine_line|#define VID_WRITE_CC&t;&t;&t;4
DECL|macro|VID_WRITE_MJPEG
mdefine_line|#define VID_WRITE_MJPEG&t;&t;&t;5
multiline_comment|/* VIDIOCSPLAYMODE */
DECL|macro|VID_PLAY_VID_OUT_MODE
mdefine_line|#define VID_PLAY_VID_OUT_MODE&t;&t;0
multiline_comment|/* p1: = VIDEO_MODE_PAL, VIDEO_MODE_NTSC, etc ... */
DECL|macro|VID_PLAY_GENLOCK
mdefine_line|#define VID_PLAY_GENLOCK&t;&t;1
multiline_comment|/* p1: 0 = OFF, 1 = ON */
multiline_comment|/* p2: GENLOCK FINE DELAY value */
DECL|macro|VID_PLAY_NORMAL
mdefine_line|#define VID_PLAY_NORMAL&t;&t;&t;2
DECL|macro|VID_PLAY_PAUSE
mdefine_line|#define VID_PLAY_PAUSE&t;&t;&t;3
DECL|macro|VID_PLAY_SINGLE_FRAME
mdefine_line|#define VID_PLAY_SINGLE_FRAME&t;&t;4
DECL|macro|VID_PLAY_FAST_FORWARD
mdefine_line|#define VID_PLAY_FAST_FORWARD&t;&t;5
DECL|macro|VID_PLAY_SLOW_MOTION
mdefine_line|#define VID_PLAY_SLOW_MOTION&t;&t;6
DECL|macro|VID_PLAY_IMMEDIATE_NORMAL
mdefine_line|#define VID_PLAY_IMMEDIATE_NORMAL&t;7
DECL|macro|VID_PLAY_SWITCH_CHANNELS
mdefine_line|#define VID_PLAY_SWITCH_CHANNELS&t;8
DECL|macro|VID_PLAY_FREEZE_FRAME
mdefine_line|#define VID_PLAY_FREEZE_FRAME&t;&t;9
DECL|macro|VID_PLAY_STILL_MODE
mdefine_line|#define VID_PLAY_STILL_MODE&t;&t;10
DECL|macro|VID_PLAY_MASTER_MODE
mdefine_line|#define VID_PLAY_MASTER_MODE&t;&t;11
multiline_comment|/* p1: see below */
DECL|macro|VID_PLAY_MASTER_NONE
mdefine_line|#define&t;&t;VID_PLAY_MASTER_NONE&t;1
DECL|macro|VID_PLAY_MASTER_VIDEO
mdefine_line|#define&t;&t;VID_PLAY_MASTER_VIDEO&t;2
DECL|macro|VID_PLAY_MASTER_AUDIO
mdefine_line|#define&t;&t;VID_PLAY_MASTER_AUDIO&t;3
DECL|macro|VID_PLAY_ACTIVE_SCANLINES
mdefine_line|#define VID_PLAY_ACTIVE_SCANLINES&t;12
multiline_comment|/* p1 = first active; p2 = last active */
DECL|macro|VID_PLAY_RESET
mdefine_line|#define VID_PLAY_RESET&t;&t;&t;13
DECL|macro|VID_PLAY_END_MARK
mdefine_line|#define VID_PLAY_END_MARK&t;&t;14
DECL|macro|VID_HARDWARE_BT848
mdefine_line|#define VID_HARDWARE_BT848&t;1
DECL|macro|VID_HARDWARE_QCAM_BW
mdefine_line|#define VID_HARDWARE_QCAM_BW&t;2
DECL|macro|VID_HARDWARE_PMS
mdefine_line|#define VID_HARDWARE_PMS&t;3
DECL|macro|VID_HARDWARE_QCAM_C
mdefine_line|#define VID_HARDWARE_QCAM_C&t;4
DECL|macro|VID_HARDWARE_PSEUDO
mdefine_line|#define VID_HARDWARE_PSEUDO&t;5
DECL|macro|VID_HARDWARE_SAA5249
mdefine_line|#define VID_HARDWARE_SAA5249&t;6
DECL|macro|VID_HARDWARE_AZTECH
mdefine_line|#define VID_HARDWARE_AZTECH&t;7
DECL|macro|VID_HARDWARE_SF16MI
mdefine_line|#define VID_HARDWARE_SF16MI&t;8
DECL|macro|VID_HARDWARE_RTRACK
mdefine_line|#define VID_HARDWARE_RTRACK&t;9
DECL|macro|VID_HARDWARE_ZOLTRIX
mdefine_line|#define VID_HARDWARE_ZOLTRIX&t;10
DECL|macro|VID_HARDWARE_SAA7146
mdefine_line|#define VID_HARDWARE_SAA7146    11
DECL|macro|VID_HARDWARE_VIDEUM
mdefine_line|#define VID_HARDWARE_VIDEUM&t;12&t;/* Reserved for Winnov videum */
DECL|macro|VID_HARDWARE_RTRACK2
mdefine_line|#define VID_HARDWARE_RTRACK2&t;13
DECL|macro|VID_HARDWARE_PERMEDIA2
mdefine_line|#define VID_HARDWARE_PERMEDIA2&t;14&t;/* Reserved for Permedia2 */
DECL|macro|VID_HARDWARE_RIVA128
mdefine_line|#define VID_HARDWARE_RIVA128&t;15&t;/* Reserved for RIVA 128 */
DECL|macro|VID_HARDWARE_PLANB
mdefine_line|#define VID_HARDWARE_PLANB&t;16&t;/* PowerMac motherboard video-in */
DECL|macro|VID_HARDWARE_BROADWAY
mdefine_line|#define VID_HARDWARE_BROADWAY&t;17&t;/* Broadway project */
DECL|macro|VID_HARDWARE_GEMTEK
mdefine_line|#define VID_HARDWARE_GEMTEK&t;18
DECL|macro|VID_HARDWARE_TYPHOON
mdefine_line|#define VID_HARDWARE_TYPHOON&t;19
DECL|macro|VID_HARDWARE_VINO
mdefine_line|#define VID_HARDWARE_VINO&t;20&t;/* SGI Indy Vino */
DECL|macro|VID_HARDWARE_CADET
mdefine_line|#define VID_HARDWARE_CADET&t;21&t;/* Cadet radio */
DECL|macro|VID_HARDWARE_TRUST
mdefine_line|#define VID_HARDWARE_TRUST&t;22&t;/* Trust FM Radio */
DECL|macro|VID_HARDWARE_TERRATEC
mdefine_line|#define VID_HARDWARE_TERRATEC&t;23&t;/* TerraTec ActiveRadio */
DECL|macro|VID_HARDWARE_CPIA
mdefine_line|#define VID_HARDWARE_CPIA&t;24
DECL|macro|VID_HARDWARE_ZR36120
mdefine_line|#define VID_HARDWARE_ZR36120&t;25&t;/* Zoran ZR36120/ZR36125 */
DECL|macro|VID_HARDWARE_ZR36067
mdefine_line|#define VID_HARDWARE_ZR36067&t;26&t;/* Zoran ZR36067/36060 */
DECL|macro|VID_HARDWARE_OV511
mdefine_line|#define VID_HARDWARE_OV511&t;27&t;
DECL|macro|VID_HARDWARE_ZR356700
mdefine_line|#define VID_HARDWARE_ZR356700&t;28&t;/* Zoran 36700 series */
DECL|macro|VID_HARDWARE_W9966
mdefine_line|#define VID_HARDWARE_W9966&t;29
DECL|macro|VID_HARDWARE_SE401
mdefine_line|#define VID_HARDWARE_SE401&t;30&t;/* SE401 USB webcams */
DECL|macro|VID_HARDWARE_PWC
mdefine_line|#define VID_HARDWARE_PWC&t;31&t;/* Philips webcams */
DECL|macro|VID_HARDWARE_MEYE
mdefine_line|#define VID_HARDWARE_MEYE&t;32&t;/* Sony Vaio MotionEye cameras */
DECL|macro|VID_HARDWARE_CPIA2
mdefine_line|#define VID_HARDWARE_CPIA2&t;33
macro_line|#endif /* __LINUX_VIDEODEV_H */
multiline_comment|/*&n; * Local variables:&n; * c-basic-offset: 8&n; * End:&n; */
eof
