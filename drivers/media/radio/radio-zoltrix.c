multiline_comment|/* zoltrix radio plus driver for Linux radio support&n; * (c) 1998 C. van Schaik &lt;carl@leg.uct.ac.za&gt;&n; *&n; * BUGS  &n; *  Due to the inconsistancy in reading from the signal flags&n; *  it is difficult to get an accurate tuned signal.&n; *&n; *  It seems that the card is not linear to 0 volume. It cuts off&n; *  at a low volume, and it is not possible (at least I have not found)&n; *  to get fine volume control over the low volume range.&n; *&n; *  Some code derived from code by Romolo Manfredini&n; *&t;&t;&t;&t;   romolo@bicnet.it&n; *&n; * 1999-05-06 - (C. van Schaik)&n; *&t;      - Make signal strength and stereo scans&n; *&t;        kinder to cpu while in delay&n; * 1999-01-05 - (C. van Schaik)&n; *&t;      - Changed tuning to 1/160Mhz accuracy&n; *&t;      - Added stereo support&n; *&t;&t;(card defaults to stereo)&n; *&t;&t;(can explicitly force mono on the card)&n; *&t;&t;(can detect if station is in stereo)&n; *&t;      - Added unmute function&n; *&t;      - Reworked ioctl functions&n; */
macro_line|#include &lt;linux/module.h&gt;&t;/* Modules                        */
macro_line|#include &lt;linux/init.h&gt;&t;&t;/* Initdata                       */
macro_line|#include &lt;linux/ioport.h&gt;&t;/* check_region, request_region   */
macro_line|#include &lt;linux/delay.h&gt;&t;/* udelay                 */
macro_line|#include &lt;asm/io.h&gt;&t;&t;/* outb, outb_p                   */
macro_line|#include &lt;asm/uaccess.h&gt;&t;/* copy to/from user              */
macro_line|#include &lt;linux/videodev.h&gt;&t;/* kernel radio structs           */
macro_line|#include &lt;linux/config.h&gt;&t;/* CONFIG_RADIO_ZOLTRIX_PORT      */
macro_line|#ifndef CONFIG_RADIO_ZOLTRIX_PORT
DECL|macro|CONFIG_RADIO_ZOLTRIX_PORT
mdefine_line|#define CONFIG_RADIO_ZOLTRIX_PORT -1
macro_line|#endif
DECL|variable|io
r_static
r_int
id|io
op_assign
id|CONFIG_RADIO_ZOLTRIX_PORT
suffix:semicolon
DECL|variable|radio_nr
r_static
r_int
id|radio_nr
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|struct|zol_device
r_struct
id|zol_device
(brace
DECL|member|port
r_int
id|port
suffix:semicolon
DECL|member|curvol
r_int
id|curvol
suffix:semicolon
DECL|member|curfreq
r_int
r_int
id|curfreq
suffix:semicolon
DECL|member|muted
r_int
id|muted
suffix:semicolon
DECL|member|stereo
r_int
r_int
id|stereo
suffix:semicolon
DECL|member|lock
r_struct
id|semaphore
id|lock
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* local things */
DECL|function|sleep_delay
r_static
r_void
id|sleep_delay
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Sleep nicely for +/- 10 mS */
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|zol_setvol
r_static
r_int
id|zol_setvol
c_func
(paren
r_struct
id|zol_device
op_star
id|dev
comma
r_int
id|vol
)paren
(brace
id|dev-&gt;curvol
op_assign
id|vol
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;muted
)paren
r_return
l_int|0
suffix:semicolon
id|down
c_func
(paren
op_amp
id|dev-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vol
op_eq
l_int|0
)paren
(brace
id|outb
c_func
(paren
l_int|0
comma
id|io
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0
comma
id|io
)paren
suffix:semicolon
id|inb
c_func
(paren
id|io
op_plus
l_int|3
)paren
suffix:semicolon
multiline_comment|/* Zoltrix needs to be read to confirm */
id|up
c_func
(paren
op_amp
id|dev-&gt;lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|outb
c_func
(paren
id|dev-&gt;curvol
op_minus
l_int|1
comma
id|io
)paren
suffix:semicolon
id|sleep_delay
c_func
(paren
)paren
suffix:semicolon
id|inb
c_func
(paren
id|io
op_plus
l_int|2
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|dev-&gt;lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|zol_mute
r_static
r_void
id|zol_mute
c_func
(paren
r_struct
id|zol_device
op_star
id|dev
)paren
(brace
id|dev-&gt;muted
op_assign
l_int|1
suffix:semicolon
id|down
c_func
(paren
op_amp
id|dev-&gt;lock
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0
comma
id|io
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0
comma
id|io
)paren
suffix:semicolon
id|inb
c_func
(paren
id|io
op_plus
l_int|3
)paren
suffix:semicolon
multiline_comment|/* Zoltrix needs to be read to confirm */
id|up
c_func
(paren
op_amp
id|dev-&gt;lock
)paren
suffix:semicolon
)brace
DECL|function|zol_unmute
r_static
r_void
id|zol_unmute
c_func
(paren
r_struct
id|zol_device
op_star
id|dev
)paren
(brace
id|dev-&gt;muted
op_assign
l_int|0
suffix:semicolon
id|zol_setvol
c_func
(paren
id|dev
comma
id|dev-&gt;curvol
)paren
suffix:semicolon
)brace
DECL|function|zol_setfreq
r_static
r_int
id|zol_setfreq
c_func
(paren
r_struct
id|zol_device
op_star
id|dev
comma
r_int
r_int
id|freq
)paren
(brace
multiline_comment|/* tunes the radio to the desired frequency */
r_int
r_int
r_int
id|bitmask
comma
id|f
comma
id|m
suffix:semicolon
r_int
r_int
id|stereo
op_assign
id|dev-&gt;stereo
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|freq
op_eq
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
id|m
op_assign
(paren
id|freq
op_div
l_int|160
op_minus
l_int|8800
)paren
op_star
l_int|2
suffix:semicolon
id|f
op_assign
(paren
r_int
r_int
r_int
)paren
id|m
op_plus
l_int|0x4d1c
suffix:semicolon
id|bitmask
op_assign
l_int|0xc480402c10080000ull
suffix:semicolon
id|i
op_assign
l_int|45
suffix:semicolon
id|down
c_func
(paren
op_amp
id|dev-&gt;lock
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0
comma
id|io
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0
comma
id|io
)paren
suffix:semicolon
id|inb
c_func
(paren
id|io
op_plus
l_int|3
)paren
suffix:semicolon
multiline_comment|/* Zoltrix needs to be read to confirm */
id|outb
c_func
(paren
l_int|0x40
comma
id|io
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0xc0
comma
id|io
)paren
suffix:semicolon
id|bitmask
op_assign
(paren
id|bitmask
op_xor
(paren
(paren
id|f
op_amp
l_int|0xff
)paren
op_lshift
l_int|47
)paren
op_xor
(paren
(paren
id|f
op_amp
l_int|0xff00
)paren
op_lshift
l_int|30
)paren
op_xor
(paren
id|stereo
op_lshift
l_int|31
)paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|i
op_decrement
)paren
(brace
r_if
c_cond
(paren
(paren
id|bitmask
op_amp
l_int|0x8000000000000000ull
)paren
op_ne
l_int|0
)paren
(brace
id|outb
c_func
(paren
l_int|0x80
comma
id|io
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|50
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x00
comma
id|io
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|50
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x80
comma
id|io
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|50
)paren
suffix:semicolon
)brace
r_else
(brace
id|outb
c_func
(paren
l_int|0xc0
comma
id|io
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|50
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x40
comma
id|io
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|50
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0xc0
comma
id|io
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|50
)paren
suffix:semicolon
)brace
id|bitmask
op_mul_assign
l_int|2
suffix:semicolon
)brace
multiline_comment|/* termination sequence */
id|outb
c_func
(paren
l_int|0x80
comma
id|io
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0xc0
comma
id|io
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x40
comma
id|io
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|1000
)paren
suffix:semicolon
id|inb
c_func
(paren
id|io
op_plus
l_int|2
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|1000
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;muted
)paren
(brace
id|outb
c_func
(paren
l_int|0
comma
id|io
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0
comma
id|io
)paren
suffix:semicolon
id|inb
c_func
(paren
id|io
op_plus
l_int|3
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|1000
)paren
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|dev-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;muted
)paren
(brace
id|zol_setvol
c_func
(paren
id|dev
comma
id|dev-&gt;curvol
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Get signal strength */
DECL|function|zol_getsigstr
r_int
id|zol_getsigstr
c_func
(paren
r_struct
id|zol_device
op_star
id|dev
)paren
(brace
r_int
id|a
comma
id|b
suffix:semicolon
id|down
c_func
(paren
op_amp
id|dev-&gt;lock
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x00
comma
id|io
)paren
suffix:semicolon
multiline_comment|/* This stuff I found to do nothing */
id|outb
c_func
(paren
id|dev-&gt;curvol
comma
id|io
)paren
suffix:semicolon
id|sleep_delay
c_func
(paren
)paren
suffix:semicolon
id|sleep_delay
c_func
(paren
)paren
suffix:semicolon
id|a
op_assign
id|inb
c_func
(paren
id|io
)paren
suffix:semicolon
id|sleep_delay
c_func
(paren
)paren
suffix:semicolon
id|b
op_assign
id|inb
c_func
(paren
id|io
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|dev-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|a
op_ne
id|b
)paren
r_return
(paren
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|a
op_eq
l_int|0xcf
)paren
op_logical_or
(paren
id|a
op_eq
l_int|0xdf
)paren
multiline_comment|/* I found this out by playing */
op_logical_or
(paren
id|a
op_eq
l_int|0xef
)paren
)paren
multiline_comment|/* with a binary scanner on the card io */
r_return
(paren
l_int|1
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|zol_is_stereo
r_int
id|zol_is_stereo
(paren
r_struct
id|zol_device
op_star
id|dev
)paren
(brace
r_int
id|x1
comma
id|x2
suffix:semicolon
id|down
c_func
(paren
op_amp
id|dev-&gt;lock
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x00
comma
id|io
)paren
suffix:semicolon
id|outb
c_func
(paren
id|dev-&gt;curvol
comma
id|io
)paren
suffix:semicolon
id|sleep_delay
c_func
(paren
)paren
suffix:semicolon
id|sleep_delay
c_func
(paren
)paren
suffix:semicolon
id|x1
op_assign
id|inb
c_func
(paren
id|io
)paren
suffix:semicolon
id|sleep_delay
c_func
(paren
)paren
suffix:semicolon
id|x2
op_assign
id|inb
c_func
(paren
id|io
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|dev-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|x1
op_eq
id|x2
)paren
op_logical_and
(paren
id|x1
op_eq
l_int|0xcf
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|zol_do_ioctl
r_static
r_int
id|zol_do_ioctl
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
r_void
op_star
id|arg
)paren
(brace
r_struct
id|video_device
op_star
id|dev
op_assign
id|video_devdata
c_func
(paren
id|file
)paren
suffix:semicolon
r_struct
id|zol_device
op_star
id|zol
op_assign
id|dev-&gt;priv
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|VIDIOCGCAP
suffix:colon
(brace
r_struct
id|video_capability
op_star
id|v
op_assign
id|arg
suffix:semicolon
id|memset
c_func
(paren
id|v
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|v
)paren
)paren
suffix:semicolon
id|v-&gt;type
op_assign
id|VID_TYPE_TUNER
suffix:semicolon
id|v-&gt;channels
op_assign
l_int|1
op_plus
id|zol-&gt;stereo
suffix:semicolon
id|v-&gt;audios
op_assign
l_int|1
suffix:semicolon
id|strcpy
c_func
(paren
id|v-&gt;name
comma
l_string|&quot;Zoltrix Radio&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|VIDIOCGTUNER
suffix:colon
(brace
r_struct
id|video_tuner
op_star
id|v
op_assign
id|arg
suffix:semicolon
r_if
c_cond
(paren
id|v-&gt;tuner
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|strcpy
c_func
(paren
id|v-&gt;name
comma
l_string|&quot;FM&quot;
)paren
suffix:semicolon
id|v-&gt;rangelow
op_assign
(paren
r_int
)paren
(paren
l_float|88.0
op_star
l_int|16000
)paren
suffix:semicolon
id|v-&gt;rangehigh
op_assign
(paren
r_int
)paren
(paren
l_float|108.0
op_star
l_int|16000
)paren
suffix:semicolon
id|v-&gt;flags
op_assign
id|zol_is_stereo
c_func
(paren
id|zol
)paren
ques
c_cond
id|VIDEO_TUNER_STEREO_ON
suffix:colon
l_int|0
suffix:semicolon
id|v-&gt;flags
op_or_assign
id|VIDEO_TUNER_LOW
suffix:semicolon
id|v-&gt;mode
op_assign
id|VIDEO_MODE_AUTO
suffix:semicolon
id|v-&gt;signal
op_assign
l_int|0xFFFF
op_star
id|zol_getsigstr
c_func
(paren
id|zol
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|VIDIOCSTUNER
suffix:colon
(brace
r_struct
id|video_tuner
op_star
id|v
op_assign
id|arg
suffix:semicolon
r_if
c_cond
(paren
id|v-&gt;tuner
op_ne
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* Only 1 tuner so no setting needed ! */
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|VIDIOCGFREQ
suffix:colon
(brace
r_int
r_int
op_star
id|freq
op_assign
id|arg
suffix:semicolon
op_star
id|freq
op_assign
id|zol-&gt;curfreq
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|VIDIOCSFREQ
suffix:colon
(brace
r_int
r_int
op_star
id|freq
op_assign
id|arg
suffix:semicolon
id|zol-&gt;curfreq
op_assign
op_star
id|freq
suffix:semicolon
id|zol_setfreq
c_func
(paren
id|zol
comma
id|zol-&gt;curfreq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|VIDIOCGAUDIO
suffix:colon
(brace
r_struct
id|video_audio
op_star
id|v
op_assign
id|arg
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|v
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|v
)paren
)paren
suffix:semicolon
id|v-&gt;flags
op_or_assign
id|VIDEO_AUDIO_MUTABLE
op_or
id|VIDEO_AUDIO_VOLUME
suffix:semicolon
id|v-&gt;mode
op_ne
id|zol_is_stereo
c_func
(paren
id|zol
)paren
ques
c_cond
id|VIDEO_SOUND_STEREO
suffix:colon
id|VIDEO_SOUND_MONO
suffix:semicolon
id|v-&gt;volume
op_assign
id|zol-&gt;curvol
op_star
l_int|4096
suffix:semicolon
id|v-&gt;step
op_assign
l_int|4096
suffix:semicolon
id|strcpy
c_func
(paren
id|v-&gt;name
comma
l_string|&quot;Zoltrix Radio&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|VIDIOCSAUDIO
suffix:colon
(brace
r_struct
id|video_audio
op_star
id|v
op_assign
id|arg
suffix:semicolon
r_if
c_cond
(paren
id|v-&gt;audio
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|v-&gt;flags
op_amp
id|VIDEO_AUDIO_MUTE
)paren
id|zol_mute
c_func
(paren
id|zol
)paren
suffix:semicolon
r_else
(brace
id|zol_unmute
c_func
(paren
id|zol
)paren
suffix:semicolon
id|zol_setvol
c_func
(paren
id|zol
comma
id|v-&gt;volume
op_div
l_int|4096
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|v-&gt;mode
op_amp
id|VIDEO_SOUND_STEREO
)paren
(brace
id|zol-&gt;stereo
op_assign
l_int|1
suffix:semicolon
id|zol_setfreq
c_func
(paren
id|zol
comma
id|zol-&gt;curfreq
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|v-&gt;mode
op_amp
id|VIDEO_SOUND_MONO
)paren
(brace
id|zol-&gt;stereo
op_assign
l_int|0
suffix:semicolon
id|zol_setfreq
c_func
(paren
id|zol
comma
id|zol-&gt;curfreq
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_default
suffix:colon
r_return
op_minus
id|ENOIOCTLCMD
suffix:semicolon
)brace
)brace
DECL|function|zol_ioctl
r_static
r_int
id|zol_ioctl
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
(brace
r_return
id|video_usercopy
c_func
(paren
id|inode
comma
id|file
comma
id|cmd
comma
id|arg
comma
id|zol_do_ioctl
)paren
suffix:semicolon
)brace
DECL|variable|zoltrix_unit
r_static
r_struct
id|zol_device
id|zoltrix_unit
suffix:semicolon
DECL|variable|zoltrix_fops
r_static
r_struct
id|file_operations
id|zoltrix_fops
op_assign
(brace
id|owner
suffix:colon
id|THIS_MODULE
comma
id|open
suffix:colon
id|video_exclusive_open
comma
id|release
suffix:colon
id|video_exclusive_release
comma
id|ioctl
suffix:colon
id|zol_ioctl
comma
id|llseek
suffix:colon
id|no_llseek
comma
)brace
suffix:semicolon
DECL|variable|zoltrix_radio
r_static
r_struct
id|video_device
id|zoltrix_radio
op_assign
(brace
id|owner
suffix:colon
id|THIS_MODULE
comma
id|name
suffix:colon
l_string|&quot;Zoltrix Radio Plus&quot;
comma
id|type
suffix:colon
id|VID_TYPE_TUNER
comma
id|hardware
suffix:colon
id|VID_HARDWARE_ZOLTRIX
comma
id|fops
suffix:colon
op_amp
id|zoltrix_fops
comma
)brace
suffix:semicolon
DECL|function|zoltrix_init
r_static
r_int
id|__init
id|zoltrix_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|io
op_eq
op_minus
l_int|1
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;You must set an I/O address with io=0x???&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|io
op_ne
l_int|0x20c
)paren
op_logical_and
(paren
id|io
op_ne
l_int|0x30c
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;zoltrix: invalid port, try 0x20c or 0x30c&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
id|zoltrix_radio.priv
op_assign
op_amp
id|zoltrix_unit
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|io
comma
l_int|2
comma
l_string|&quot;zoltrix&quot;
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;zoltrix: port 0x%x already in use&bslash;n&quot;
comma
id|io
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
r_if
c_cond
(paren
id|video_register_device
c_func
(paren
op_amp
id|zoltrix_radio
comma
id|VFL_TYPE_RADIO
comma
id|radio_nr
)paren
op_eq
op_minus
l_int|1
)paren
(brace
id|release_region
c_func
(paren
id|io
comma
l_int|2
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Zoltrix Radio Plus card driver.&bslash;n&quot;
)paren
suffix:semicolon
id|init_MUTEX
c_func
(paren
op_amp
id|zoltrix_unit.lock
)paren
suffix:semicolon
multiline_comment|/* mute card - prevents noisy bootups */
multiline_comment|/* this ensures that the volume is all the way down  */
id|outb
c_func
(paren
l_int|0
comma
id|io
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0
comma
id|io
)paren
suffix:semicolon
id|sleep_delay
c_func
(paren
)paren
suffix:semicolon
id|sleep_delay
c_func
(paren
)paren
suffix:semicolon
id|inb
c_func
(paren
id|io
op_plus
l_int|3
)paren
suffix:semicolon
id|zoltrix_unit.curvol
op_assign
l_int|0
suffix:semicolon
id|zoltrix_unit.stereo
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;C.van Schaik&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;A driver for the Zoltrix Radio Plus.&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|io
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|io
comma
l_string|&quot;I/O address of the Zoltrix Radio Plus (0x20c or 0x30c)&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|radio_nr
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
DECL|function|zoltrix_cleanup_module
r_static
r_void
id|__exit
id|zoltrix_cleanup_module
c_func
(paren
r_void
)paren
(brace
id|video_unregister_device
c_func
(paren
op_amp
id|zoltrix_radio
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|io
comma
l_int|2
)paren
suffix:semicolon
)brace
DECL|variable|zoltrix_init
id|module_init
c_func
(paren
id|zoltrix_init
)paren
suffix:semicolon
DECL|variable|zoltrix_cleanup_module
id|module_exit
c_func
(paren
id|zoltrix_cleanup_module
)paren
suffix:semicolon
eof
