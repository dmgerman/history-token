macro_line|#ifndef __LINUX_se401_H
DECL|macro|__LINUX_se401_H
mdefine_line|#define __LINUX_se401_H
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/videodev.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
DECL|macro|se401_DEBUG
mdefine_line|#define se401_DEBUG&t;/* Turn on debug messages */
macro_line|#ifdef se401_DEBUG
DECL|macro|PDEBUG
macro_line|#  define PDEBUG(level, fmt, args...) &bslash;&n;if (debug &gt;= level) info(&quot;[&quot; __PRETTY_FUNCTION__ &quot;:%d] &quot; fmt, __LINE__ , ## args)
macro_line|#else
DECL|macro|PDEBUG
macro_line|#  define PDEBUG(level, fmt, args...) do {} while(0)
macro_line|#endif
multiline_comment|/* An almost drop-in replacement for sleep_on_interruptible */
DECL|macro|wait_interruptible
mdefine_line|#define wait_interruptible(test, queue, wait) &bslash;&n;{ &bslash;&n;&t;add_wait_queue(queue, wait); &bslash;&n;&t;set_current_state(TASK_INTERRUPTIBLE); &bslash;&n;&t;if (test) &bslash;&n;&t;&t;schedule(); &bslash;&n;&t;remove_wait_queue(queue, wait); &bslash;&n;&t;set_current_state(TASK_RUNNING); &bslash;&n;&t;if (signal_pending(current)) &bslash;&n;&t;&t;break; &bslash;&n;}
DECL|macro|SE401_REQ_GET_CAMERA_DESCRIPTOR
mdefine_line|#define SE401_REQ_GET_CAMERA_DESCRIPTOR&t;&t;0x06
DECL|macro|SE401_REQ_START_CONTINUOUS_CAPTURE
mdefine_line|#define SE401_REQ_START_CONTINUOUS_CAPTURE&t;0x41
DECL|macro|SE401_REQ_STOP_CONTINUOUS_CAPTURE
mdefine_line|#define SE401_REQ_STOP_CONTINUOUS_CAPTURE&t;0x42
DECL|macro|SE401_REQ_CAPTURE_FRAME
mdefine_line|#define SE401_REQ_CAPTURE_FRAME&t;&t;&t;0x43
DECL|macro|SE401_REQ_GET_BRT
mdefine_line|#define SE401_REQ_GET_BRT&t;&t;&t;0x44
DECL|macro|SE401_REQ_SET_BRT
mdefine_line|#define SE401_REQ_SET_BRT&t;&t;&t;0x45
DECL|macro|SE401_REQ_GET_WIDTH
mdefine_line|#define SE401_REQ_GET_WIDTH&t;&t;&t;0x4c
DECL|macro|SE401_REQ_SET_WIDTH
mdefine_line|#define SE401_REQ_SET_WIDTH&t;&t;&t;0x4d
DECL|macro|SE401_REQ_GET_HEIGHT
mdefine_line|#define SE401_REQ_GET_HEIGHT&t;&t;&t;0x4e
DECL|macro|SE401_REQ_SET_HEIGHT
mdefine_line|#define SE401_REQ_SET_HEIGHT&t;&t;&t;0x4f
DECL|macro|SE401_REQ_GET_OUTPUT_MODE
mdefine_line|#define SE401_REQ_GET_OUTPUT_MODE&t;&t;0x50
DECL|macro|SE401_REQ_SET_OUTPUT_MODE
mdefine_line|#define SE401_REQ_SET_OUTPUT_MODE&t;&t;0x51
DECL|macro|SE401_REQ_GET_EXT_FEATURE
mdefine_line|#define SE401_REQ_GET_EXT_FEATURE&t;&t;0x52
DECL|macro|SE401_REQ_SET_EXT_FEATURE
mdefine_line|#define SE401_REQ_SET_EXT_FEATURE&t;&t;0x53
DECL|macro|SE401_REQ_CAMERA_POWER
mdefine_line|#define SE401_REQ_CAMERA_POWER&t;&t;&t;0x56
DECL|macro|SE401_REQ_LED_CONTROL
mdefine_line|#define SE401_REQ_LED_CONTROL&t;&t;&t;0x57
DECL|macro|SE401_REQ_BIOS
mdefine_line|#define SE401_REQ_BIOS&t;&t;&t;&t;0xff
DECL|macro|SE401_BIOS_READ
mdefine_line|#define SE401_BIOS_READ&t;&t;&t;&t;0x07
DECL|macro|SE401_FORMAT_BAYER
mdefine_line|#define SE401_FORMAT_BAYER&t;0x40
multiline_comment|/* Hyundai hv7131b registers&n;   7121 and 7141 should be the same (haven&squot;t really checked...) */
multiline_comment|/* Mode registers: */
DECL|macro|HV7131_REG_MODE_A
mdefine_line|#define HV7131_REG_MODE_A&t;&t;0x00
DECL|macro|HV7131_REG_MODE_B
mdefine_line|#define HV7131_REG_MODE_B&t;&t;0x01
DECL|macro|HV7131_REG_MODE_C
mdefine_line|#define HV7131_REG_MODE_C&t;&t;0x02
multiline_comment|/* Frame registers: */
DECL|macro|HV7131_REG_FRSU
mdefine_line|#define HV7131_REG_FRSU&t;&t;0x10
DECL|macro|HV7131_REG_FRSL
mdefine_line|#define HV7131_REG_FRSL&t;&t;0x11
DECL|macro|HV7131_REG_FCSU
mdefine_line|#define HV7131_REG_FCSU&t;&t;0x12
DECL|macro|HV7131_REG_FCSL
mdefine_line|#define HV7131_REG_FCSL&t;&t;0x13
DECL|macro|HV7131_REG_FWHU
mdefine_line|#define HV7131_REG_FWHU&t;&t;0x14
DECL|macro|HV7131_REG_FWHL
mdefine_line|#define HV7131_REG_FWHL&t;&t;0x15
DECL|macro|HV7131_REG_FWWU
mdefine_line|#define HV7131_REG_FWWU&t;&t;0x16
DECL|macro|HV7131_REG_FWWL
mdefine_line|#define HV7131_REG_FWWL&t;&t;0x17
multiline_comment|/* Timing registers: */
DECL|macro|HV7131_REG_THBU
mdefine_line|#define HV7131_REG_THBU&t;&t;0x20
DECL|macro|HV7131_REG_THBL
mdefine_line|#define HV7131_REG_THBL&t;&t;0x21
DECL|macro|HV7131_REG_TVBU
mdefine_line|#define HV7131_REG_TVBU&t;&t;0x22
DECL|macro|HV7131_REG_TVBL
mdefine_line|#define HV7131_REG_TVBL&t;&t;0x23
DECL|macro|HV7131_REG_TITU
mdefine_line|#define HV7131_REG_TITU&t;&t;0x25
DECL|macro|HV7131_REG_TITM
mdefine_line|#define HV7131_REG_TITM&t;&t;0x26
DECL|macro|HV7131_REG_TITL
mdefine_line|#define HV7131_REG_TITL&t;&t;0x27
DECL|macro|HV7131_REG_TMCD
mdefine_line|#define HV7131_REG_TMCD&t;&t;0x28
multiline_comment|/* Adjust Registers: */
DECL|macro|HV7131_REG_ARLV
mdefine_line|#define HV7131_REG_ARLV&t;&t;0x30
DECL|macro|HV7131_REG_ARCG
mdefine_line|#define HV7131_REG_ARCG&t;&t;0x31
DECL|macro|HV7131_REG_AGCG
mdefine_line|#define HV7131_REG_AGCG&t;&t;0x32
DECL|macro|HV7131_REG_ABCG
mdefine_line|#define HV7131_REG_ABCG&t;&t;0x33
DECL|macro|HV7131_REG_APBV
mdefine_line|#define HV7131_REG_APBV&t;&t;0x34
DECL|macro|HV7131_REG_ASLP
mdefine_line|#define HV7131_REG_ASLP&t;&t;0x54
multiline_comment|/* Offset Registers: */
DECL|macro|HV7131_REG_OFSR
mdefine_line|#define HV7131_REG_OFSR&t;&t;0x50
DECL|macro|HV7131_REG_OFSG
mdefine_line|#define HV7131_REG_OFSG&t;&t;0x51
DECL|macro|HV7131_REG_OFSB
mdefine_line|#define HV7131_REG_OFSB&t;&t;0x52
multiline_comment|/* REset level statistics registers: */
DECL|macro|HV7131_REG_LOREFNOH
mdefine_line|#define HV7131_REG_LOREFNOH&t;0x57
DECL|macro|HV7131_REG_LOREFNOL
mdefine_line|#define HV7131_REG_LOREFNOL&t;0x58
DECL|macro|HV7131_REG_HIREFNOH
mdefine_line|#define HV7131_REG_HIREFNOH&t;0x59
DECL|macro|HV7131_REG_HIREFNOL
mdefine_line|#define HV7131_REG_HIREFNOL&t;0x5a
multiline_comment|/* se401 registers */
DECL|macro|SE401_OPERATINGMODE
mdefine_line|#define SE401_OPERATINGMODE&t;0x2000
multiline_comment|/* size of usb transfers */
DECL|macro|SE401_PACKETSIZE
mdefine_line|#define SE401_PACKETSIZE&t;4096
multiline_comment|/* number of queued bulk transfers to use, should be about 8 */
DECL|macro|SE401_NUMSBUF
mdefine_line|#define SE401_NUMSBUF&t;&t;1
multiline_comment|/* read the usb specs for this one :) */
DECL|macro|SE401_VIDEO_ENDPOINT
mdefine_line|#define SE401_VIDEO_ENDPOINT&t;1
DECL|macro|SE401_BUTTON_ENDPOINT
mdefine_line|#define SE401_BUTTON_ENDPOINT&t;2
multiline_comment|/* number of frames supported by the v4l part */
DECL|macro|SE401_NUMFRAMES
mdefine_line|#define SE401_NUMFRAMES&t;&t;2
multiline_comment|/* scratch buffers for passing data to the decoders */
DECL|macro|SE401_NUMSCRATCH
mdefine_line|#define SE401_NUMSCRATCH&t;32
multiline_comment|/* maximum amount of data in a JangGu packet */
DECL|macro|SE401_VLCDATALEN
mdefine_line|#define SE401_VLCDATALEN&t;1024
multiline_comment|/* number of nul sized packets to receive before kicking the camera */
DECL|macro|SE401_MAX_NULLPACKETS
mdefine_line|#define SE401_MAX_NULLPACKETS&t;4000
multiline_comment|/* number of decoding errors before kicking the camera */
DECL|macro|SE401_MAX_ERRORS
mdefine_line|#define SE401_MAX_ERRORS&t;200
r_struct
id|usb_device
suffix:semicolon
DECL|struct|se401_sbuf
r_struct
id|se401_sbuf
(brace
DECL|member|data
r_int
r_char
op_star
id|data
suffix:semicolon
)brace
suffix:semicolon
r_enum
(brace
DECL|enumerator|FRAME_UNUSED
id|FRAME_UNUSED
comma
multiline_comment|/* Unused (no MCAPTURE) */
DECL|enumerator|FRAME_READY
id|FRAME_READY
comma
multiline_comment|/* Ready to start grabbing */
DECL|enumerator|FRAME_GRABBING
id|FRAME_GRABBING
comma
multiline_comment|/* In the process of being grabbed into */
DECL|enumerator|FRAME_DONE
id|FRAME_DONE
comma
multiline_comment|/* Finished grabbing, but not been synced yet */
DECL|enumerator|FRAME_ERROR
id|FRAME_ERROR
comma
multiline_comment|/* Something bad happened while processing */
)brace
suffix:semicolon
r_enum
(brace
DECL|enumerator|FMT_BAYER
id|FMT_BAYER
comma
DECL|enumerator|FMT_JANGGU
id|FMT_JANGGU
comma
)brace
suffix:semicolon
r_enum
(brace
DECL|enumerator|BUFFER_UNUSED
id|BUFFER_UNUSED
comma
DECL|enumerator|BUFFER_READY
id|BUFFER_READY
comma
DECL|enumerator|BUFFER_BUSY
id|BUFFER_BUSY
comma
DECL|enumerator|BUFFER_DONE
id|BUFFER_DONE
comma
)brace
suffix:semicolon
DECL|struct|se401_scratch
r_struct
id|se401_scratch
(brace
DECL|member|data
r_int
r_char
op_star
id|data
suffix:semicolon
DECL|member|state
r_volatile
r_int
id|state
suffix:semicolon
DECL|member|offset
r_int
id|offset
suffix:semicolon
DECL|member|length
r_int
id|length
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|se401_frame
r_struct
id|se401_frame
(brace
DECL|member|data
r_int
r_char
op_star
id|data
suffix:semicolon
multiline_comment|/* Frame buffer */
DECL|member|grabstate
r_volatile
r_int
id|grabstate
suffix:semicolon
multiline_comment|/* State of grabbing */
DECL|member|curline
r_int
r_char
op_star
id|curline
suffix:semicolon
DECL|member|curlinepix
r_int
id|curlinepix
suffix:semicolon
DECL|member|curpix
r_int
id|curpix
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|usb_se401
r_struct
id|usb_se401
(brace
DECL|member|vdev
r_struct
id|video_device
id|vdev
suffix:semicolon
multiline_comment|/* Device structure */
DECL|member|dev
r_struct
id|usb_device
op_star
id|dev
suffix:semicolon
DECL|member|iface
r_int
r_char
id|iface
suffix:semicolon
DECL|member|camera_name
r_char
op_star
id|camera_name
suffix:semicolon
DECL|member|change
r_int
id|change
suffix:semicolon
DECL|member|brightness
r_int
id|brightness
suffix:semicolon
DECL|member|hue
r_int
id|hue
suffix:semicolon
DECL|member|rgain
r_int
id|rgain
suffix:semicolon
DECL|member|ggain
r_int
id|ggain
suffix:semicolon
DECL|member|bgain
r_int
id|bgain
suffix:semicolon
DECL|member|expose_h
r_int
id|expose_h
suffix:semicolon
DECL|member|expose_m
r_int
id|expose_m
suffix:semicolon
DECL|member|expose_l
r_int
id|expose_l
suffix:semicolon
DECL|member|resetlevel
r_int
id|resetlevel
suffix:semicolon
DECL|member|enhance
r_int
id|enhance
suffix:semicolon
DECL|member|format
r_int
id|format
suffix:semicolon
DECL|member|sizes
r_int
id|sizes
suffix:semicolon
DECL|member|width
r_int
op_star
id|width
suffix:semicolon
DECL|member|height
r_int
op_star
id|height
suffix:semicolon
DECL|member|cwidth
r_int
id|cwidth
suffix:semicolon
multiline_comment|/* current width */
DECL|member|cheight
r_int
id|cheight
suffix:semicolon
multiline_comment|/* current height */
DECL|member|palette
r_int
id|palette
suffix:semicolon
DECL|member|maxframesize
r_int
id|maxframesize
suffix:semicolon
DECL|member|cframesize
r_int
id|cframesize
suffix:semicolon
multiline_comment|/* current framesize */
DECL|member|lock
r_struct
id|semaphore
id|lock
suffix:semicolon
DECL|member|user
r_int
id|user
suffix:semicolon
multiline_comment|/* user count for exclusive use */
DECL|member|removed
r_int
id|removed
suffix:semicolon
multiline_comment|/* device disconnected */
DECL|member|streaming
r_int
id|streaming
suffix:semicolon
multiline_comment|/* Are we streaming video? */
DECL|member|fbuf
r_char
op_star
id|fbuf
suffix:semicolon
multiline_comment|/* Videodev buffer area */
DECL|member|urb
id|urb_t
op_star
id|urb
(braket
id|SE401_NUMSBUF
)braket
suffix:semicolon
DECL|member|inturb
id|urb_t
op_star
id|inturb
suffix:semicolon
DECL|member|button
r_int
id|button
suffix:semicolon
DECL|member|buttonpressed
r_int
id|buttonpressed
suffix:semicolon
DECL|member|curframe
r_int
id|curframe
suffix:semicolon
multiline_comment|/* Current receiving frame */
DECL|member|frame
r_struct
id|se401_frame
id|frame
(braket
id|SE401_NUMFRAMES
)braket
suffix:semicolon
DECL|member|readcount
r_int
id|readcount
suffix:semicolon
DECL|member|framecount
r_int
id|framecount
suffix:semicolon
DECL|member|error
r_int
id|error
suffix:semicolon
DECL|member|dropped
r_int
id|dropped
suffix:semicolon
DECL|member|scratch_next
r_int
id|scratch_next
suffix:semicolon
DECL|member|scratch_use
r_int
id|scratch_use
suffix:semicolon
DECL|member|scratch_overflow
r_int
id|scratch_overflow
suffix:semicolon
DECL|member|scratch
r_struct
id|se401_scratch
id|scratch
(braket
id|SE401_NUMSCRATCH
)braket
suffix:semicolon
multiline_comment|/* Decoder specific data: */
DECL|member|vlcdata
r_int
r_char
id|vlcdata
(braket
id|SE401_VLCDATALEN
)braket
suffix:semicolon
DECL|member|vlcdatapos
r_int
id|vlcdatapos
suffix:semicolon
DECL|member|bayeroffset
r_int
id|bayeroffset
suffix:semicolon
DECL|member|sbuf
r_struct
id|se401_sbuf
id|sbuf
(braket
id|SE401_NUMSBUF
)braket
suffix:semicolon
DECL|member|wq
id|wait_queue_head_t
id|wq
suffix:semicolon
multiline_comment|/* Processes waiting */
multiline_comment|/* proc interface */
DECL|member|proc_entry
r_struct
id|proc_dir_entry
op_star
id|proc_entry
suffix:semicolon
multiline_comment|/* /proc/se401/videoX */
DECL|member|nullpackets
r_int
id|nullpackets
suffix:semicolon
)brace
suffix:semicolon
r_static
r_inline
r_void
id|usb_se401_remove_disconnected
(paren
r_struct
id|usb_se401
op_star
id|se401
)paren
suffix:semicolon
macro_line|#endif
eof
