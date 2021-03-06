multiline_comment|/* Typhoon Radio Card driver for radio support&n; * (c) 1999 Dr. Henrik Seidel &lt;Henrik.Seidel@gmx.de&gt;&n; *&n; * Card manufacturer:&n; * http://194.18.155.92/idc/prod2.idc?nr=50753&amp;lang=e&n; *&n; * Notes on the hardware&n; *&n; * This card has two output sockets, one for speakers and one for line.&n; * The speaker output has volume control, but only in four discrete&n; * steps. The line output has neither volume control nor mute.&n; *&n; * The card has auto-stereo according to its manual, although it all&n; * sounds mono to me (even with the Win/DOS drivers). Maybe it&squot;s my&n; * antenna - I really don&squot;t know for sure.&n; *&n; * Frequency control is done digitally.&n; *&n; * Volume control is done digitally, but there are only four different&n; * possible values. So you should better always turn the volume up and&n; * use line control. I got the best results by connecting line output&n; * to the sound card microphone input. For such a configuration the&n; * volume control has no effect, since volume control only influences&n; * the speaker output.&n; *&n; * There is no explicit mute/unmute. So I set the radio frequency to a&n; * value where I do expect just noise and turn the speaker volume down.&n; * The frequency change is necessary since the card never seems to be&n; * completely silent.&n; */
macro_line|#include &lt;linux/module.h&gt;&t;/* Modules                        */
macro_line|#include &lt;linux/init.h&gt;&t;&t;/* Initdata                       */
macro_line|#include &lt;linux/ioport.h&gt;&t;/* check_region, request_region   */
macro_line|#include &lt;linux/proc_fs.h&gt;&t;/* radio card status report&t;  */
macro_line|#include &lt;asm/io.h&gt;&t;&t;/* outb, outb_p                   */
macro_line|#include &lt;asm/uaccess.h&gt;&t;/* copy to/from user              */
macro_line|#include &lt;linux/videodev.h&gt;&t;/* kernel radio structs           */
macro_line|#include &lt;linux/config.h&gt;&t;/* CONFIG_RADIO_TYPHOON_*         */
DECL|macro|BANNER
mdefine_line|#define BANNER &quot;Typhoon Radio Card driver v0.1&bslash;n&quot;
macro_line|#ifndef CONFIG_RADIO_TYPHOON_PORT
DECL|macro|CONFIG_RADIO_TYPHOON_PORT
mdefine_line|#define CONFIG_RADIO_TYPHOON_PORT -1
macro_line|#endif
macro_line|#ifndef CONFIG_RADIO_TYPHOON_MUTEFREQ
DECL|macro|CONFIG_RADIO_TYPHOON_MUTEFREQ
mdefine_line|#define CONFIG_RADIO_TYPHOON_MUTEFREQ 0
macro_line|#endif
macro_line|#ifndef CONFIG_PROC_FS
DECL|macro|CONFIG_RADIO_TYPHOON_PROC_FS
macro_line|#undef CONFIG_RADIO_TYPHOON_PROC_FS
macro_line|#endif
DECL|struct|typhoon_device
r_struct
id|typhoon_device
(brace
DECL|member|users
r_int
id|users
suffix:semicolon
DECL|member|iobase
r_int
id|iobase
suffix:semicolon
DECL|member|curvol
r_int
id|curvol
suffix:semicolon
DECL|member|muted
r_int
id|muted
suffix:semicolon
DECL|member|curfreq
r_int
r_int
id|curfreq
suffix:semicolon
DECL|member|mutefreq
r_int
r_int
id|mutefreq
suffix:semicolon
DECL|member|lock
r_struct
id|semaphore
id|lock
suffix:semicolon
)brace
suffix:semicolon
r_static
r_void
id|typhoon_setvol_generic
c_func
(paren
r_struct
id|typhoon_device
op_star
id|dev
comma
r_int
id|vol
)paren
suffix:semicolon
r_static
r_int
id|typhoon_setfreq_generic
c_func
(paren
r_struct
id|typhoon_device
op_star
id|dev
comma
r_int
r_int
id|frequency
)paren
suffix:semicolon
r_static
r_int
id|typhoon_setfreq
c_func
(paren
r_struct
id|typhoon_device
op_star
id|dev
comma
r_int
r_int
id|frequency
)paren
suffix:semicolon
r_static
r_void
id|typhoon_mute
c_func
(paren
r_struct
id|typhoon_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_void
id|typhoon_unmute
c_func
(paren
r_struct
id|typhoon_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_int
id|typhoon_setvol
c_func
(paren
r_struct
id|typhoon_device
op_star
id|dev
comma
r_int
id|vol
)paren
suffix:semicolon
r_static
r_int
id|typhoon_ioctl
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
macro_line|#ifdef CONFIG_RADIO_TYPHOON_PROC_FS
r_static
r_int
id|typhoon_get_info
c_func
(paren
r_char
op_star
id|buf
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|len
)paren
suffix:semicolon
macro_line|#endif
DECL|function|typhoon_setvol_generic
r_static
r_void
id|typhoon_setvol_generic
c_func
(paren
r_struct
id|typhoon_device
op_star
id|dev
comma
r_int
id|vol
)paren
(brace
id|down
c_func
(paren
op_amp
id|dev-&gt;lock
)paren
suffix:semicolon
id|vol
op_rshift_assign
l_int|14
suffix:semicolon
multiline_comment|/* Map 16 bit to 2 bit */
id|vol
op_and_assign
l_int|3
suffix:semicolon
id|outb_p
c_func
(paren
id|vol
op_div
l_int|2
comma
id|dev-&gt;iobase
)paren
suffix:semicolon
multiline_comment|/* Set the volume, high bit. */
id|outb_p
c_func
(paren
id|vol
op_mod
l_int|2
comma
id|dev-&gt;iobase
op_plus
l_int|2
)paren
suffix:semicolon
multiline_comment|/* Set the volume, low bit. */
id|up
c_func
(paren
op_amp
id|dev-&gt;lock
)paren
suffix:semicolon
)brace
DECL|function|typhoon_setfreq_generic
r_static
r_int
id|typhoon_setfreq_generic
c_func
(paren
r_struct
id|typhoon_device
op_star
id|dev
comma
r_int
r_int
id|frequency
)paren
(brace
r_int
r_int
id|outval
suffix:semicolon
r_int
r_int
id|x
suffix:semicolon
multiline_comment|/*&n;&t; * The frequency transfer curve is not linear. The best fit I could&n;&t; * get is&n;&t; *&n;&t; * outval = -155 + exp((f + 15.55) * 0.057))&n;&t; *&n;&t; * where frequency f is in MHz. Since we don&squot;t have exp in the kernel,&n;&t; * I approximate this function by a third order polynomial.&n;&t; *&n;&t; */
id|down
c_func
(paren
op_amp
id|dev-&gt;lock
)paren
suffix:semicolon
id|x
op_assign
id|frequency
op_div
l_int|160
suffix:semicolon
id|outval
op_assign
(paren
id|x
op_star
id|x
op_plus
l_int|2500
)paren
op_div
l_int|5000
suffix:semicolon
id|outval
op_assign
(paren
id|outval
op_star
id|x
op_plus
l_int|5000
)paren
op_div
l_int|10000
suffix:semicolon
id|outval
op_sub_assign
(paren
l_int|10
op_star
id|x
op_star
id|x
op_plus
l_int|10433
)paren
op_div
l_int|20866
suffix:semicolon
id|outval
op_add_assign
l_int|4
op_star
id|x
op_minus
l_int|11505
suffix:semicolon
id|outb_p
c_func
(paren
(paren
id|outval
op_rshift
l_int|8
)paren
op_amp
l_int|0x01
comma
id|dev-&gt;iobase
op_plus
l_int|4
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|outval
op_rshift
l_int|9
comma
id|dev-&gt;iobase
op_plus
l_int|6
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|outval
op_amp
l_int|0xff
comma
id|dev-&gt;iobase
op_plus
l_int|8
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
DECL|function|typhoon_setfreq
r_static
r_int
id|typhoon_setfreq
c_func
(paren
r_struct
id|typhoon_device
op_star
id|dev
comma
r_int
r_int
id|frequency
)paren
(brace
id|typhoon_setfreq_generic
c_func
(paren
id|dev
comma
id|frequency
)paren
suffix:semicolon
id|dev-&gt;curfreq
op_assign
id|frequency
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|typhoon_mute
r_static
r_void
id|typhoon_mute
c_func
(paren
r_struct
id|typhoon_device
op_star
id|dev
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;muted
op_eq
l_int|1
)paren
r_return
suffix:semicolon
id|typhoon_setvol_generic
c_func
(paren
id|dev
comma
l_int|0
)paren
suffix:semicolon
id|typhoon_setfreq_generic
c_func
(paren
id|dev
comma
id|dev-&gt;mutefreq
)paren
suffix:semicolon
id|dev-&gt;muted
op_assign
l_int|1
suffix:semicolon
)brace
DECL|function|typhoon_unmute
r_static
r_void
id|typhoon_unmute
c_func
(paren
r_struct
id|typhoon_device
op_star
id|dev
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;muted
op_eq
l_int|0
)paren
r_return
suffix:semicolon
id|typhoon_setfreq_generic
c_func
(paren
id|dev
comma
id|dev-&gt;curfreq
)paren
suffix:semicolon
id|typhoon_setvol_generic
c_func
(paren
id|dev
comma
id|dev-&gt;curvol
)paren
suffix:semicolon
id|dev-&gt;muted
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|typhoon_setvol
r_static
r_int
id|typhoon_setvol
c_func
(paren
r_struct
id|typhoon_device
op_star
id|dev
comma
r_int
id|vol
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;muted
op_logical_and
id|vol
op_ne
l_int|0
)paren
(brace
multiline_comment|/* user is unmuting the card */
id|dev-&gt;curvol
op_assign
id|vol
suffix:semicolon
id|typhoon_unmute
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|vol
op_eq
id|dev-&gt;curvol
)paren
multiline_comment|/* requested volume == current */
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|vol
op_eq
l_int|0
)paren
(brace
multiline_comment|/* volume == 0 means mute the card */
id|typhoon_mute
c_func
(paren
id|dev
)paren
suffix:semicolon
id|dev-&gt;curvol
op_assign
id|vol
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|typhoon_setvol_generic
c_func
(paren
id|dev
comma
id|vol
)paren
suffix:semicolon
id|dev-&gt;curvol
op_assign
id|vol
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|typhoon_do_ioctl
r_static
r_int
id|typhoon_do_ioctl
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
id|typhoon_device
op_star
id|typhoon
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
l_string|&quot;Typhoon Radio&quot;
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
multiline_comment|/* Only 1 tuner */
r_return
op_minus
id|EINVAL
suffix:semicolon
id|v-&gt;rangelow
op_assign
l_int|875
op_star
l_int|1600
suffix:semicolon
id|v-&gt;rangehigh
op_assign
l_int|1080
op_star
l_int|1600
suffix:semicolon
id|v-&gt;flags
op_assign
id|VIDEO_TUNER_LOW
suffix:semicolon
id|v-&gt;mode
op_assign
id|VIDEO_MODE_AUTO
suffix:semicolon
id|v-&gt;signal
op_assign
l_int|0xFFFF
suffix:semicolon
multiline_comment|/* We can&squot;t get the signal strength */
id|strcpy
c_func
(paren
id|v-&gt;name
comma
l_string|&quot;FM&quot;
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
id|typhoon-&gt;curfreq
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
id|typhoon-&gt;curfreq
op_assign
op_star
id|freq
suffix:semicolon
id|typhoon_setfreq
c_func
(paren
id|typhoon
comma
id|typhoon-&gt;curfreq
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
op_or_assign
id|VIDEO_SOUND_MONO
suffix:semicolon
id|v-&gt;volume
op_assign
id|typhoon-&gt;curvol
suffix:semicolon
id|v-&gt;step
op_assign
l_int|1
op_lshift
l_int|14
suffix:semicolon
id|strcpy
c_func
(paren
id|v-&gt;name
comma
l_string|&quot;Typhoon Radio&quot;
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
id|typhoon_mute
c_func
(paren
id|typhoon
)paren
suffix:semicolon
r_else
id|typhoon_unmute
c_func
(paren
id|typhoon
)paren
suffix:semicolon
r_if
c_cond
(paren
id|v-&gt;flags
op_amp
id|VIDEO_AUDIO_VOLUME
)paren
id|typhoon_setvol
c_func
(paren
id|typhoon
comma
id|v-&gt;volume
)paren
suffix:semicolon
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
DECL|function|typhoon_ioctl
r_static
r_int
id|typhoon_ioctl
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
id|typhoon_do_ioctl
)paren
suffix:semicolon
)brace
DECL|variable|typhoon_unit
r_static
r_struct
id|typhoon_device
id|typhoon_unit
op_assign
(brace
dot
id|iobase
op_assign
id|CONFIG_RADIO_TYPHOON_PORT
comma
dot
id|curfreq
op_assign
id|CONFIG_RADIO_TYPHOON_MUTEFREQ
comma
dot
id|mutefreq
op_assign
id|CONFIG_RADIO_TYPHOON_MUTEFREQ
comma
)brace
suffix:semicolon
DECL|variable|typhoon_fops
r_static
r_struct
id|file_operations
id|typhoon_fops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|open
op_assign
id|video_exclusive_open
comma
dot
id|release
op_assign
id|video_exclusive_release
comma
dot
id|ioctl
op_assign
id|typhoon_ioctl
comma
dot
id|llseek
op_assign
id|no_llseek
comma
)brace
suffix:semicolon
DECL|variable|typhoon_radio
r_static
r_struct
id|video_device
id|typhoon_radio
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|name
op_assign
l_string|&quot;Typhoon Radio&quot;
comma
dot
id|type
op_assign
id|VID_TYPE_TUNER
comma
dot
id|hardware
op_assign
id|VID_HARDWARE_TYPHOON
comma
dot
id|fops
op_assign
op_amp
id|typhoon_fops
comma
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_RADIO_TYPHOON_PROC_FS
DECL|function|typhoon_get_info
r_static
r_int
id|typhoon_get_info
c_func
(paren
r_char
op_star
id|buf
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|len
)paren
(brace
r_char
op_star
id|out
op_assign
id|buf
suffix:semicolon
macro_line|#ifdef MODULE
DECL|macro|MODULEPROCSTRING
mdefine_line|#define MODULEPROCSTRING &quot;Driver loaded as a module&quot;
macro_line|#else
mdefine_line|#define MODULEPROCSTRING &quot;Driver compiled into kernel&quot;
macro_line|#endif
multiline_comment|/* output must be kept under PAGE_SIZE */
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
id|BANNER
)paren
suffix:semicolon
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;Load type: &quot;
id|MODULEPROCSTRING
l_string|&quot;&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;frequency = %lu kHz&bslash;n&quot;
comma
id|typhoon_unit.curfreq
op_rshift
l_int|4
)paren
suffix:semicolon
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;volume = %d&bslash;n&quot;
comma
id|typhoon_unit.curvol
)paren
suffix:semicolon
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;mute = %s&bslash;n&quot;
comma
id|typhoon_unit.muted
ques
c_cond
l_string|&quot;on&quot;
suffix:colon
l_string|&quot;off&quot;
)paren
suffix:semicolon
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;iobase = 0x%x&bslash;n&quot;
comma
id|typhoon_unit.iobase
)paren
suffix:semicolon
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;mute frequency = %lu kHz&bslash;n&quot;
comma
id|typhoon_unit.mutefreq
op_rshift
l_int|4
)paren
suffix:semicolon
r_return
id|out
op_minus
id|buf
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_RADIO_TYPHOON_PROC_FS */
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Dr. Henrik Seidel&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;A driver for the Typhoon radio card (a.k.a. EcoRadio).&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|io
r_static
r_int
id|io
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|variable|radio_nr
r_static
r_int
id|radio_nr
op_assign
op_minus
l_int|1
suffix:semicolon
id|module_param
c_func
(paren
id|io
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|io
comma
l_string|&quot;I/O address of the Typhoon card (0x316 or 0x336)&quot;
)paren
suffix:semicolon
id|module_param
c_func
(paren
id|radio_nr
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
macro_line|#ifdef MODULE
DECL|variable|mutefreq
r_static
r_int
r_int
id|mutefreq
op_assign
l_int|0
suffix:semicolon
id|module_param
c_func
(paren
id|mutefreq
comma
id|ulong
comma
l_int|0
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|mutefreq
comma
l_string|&quot;Frequency used when muting the card (in kHz)&quot;
)paren
suffix:semicolon
macro_line|#endif
DECL|function|typhoon_init
r_static
r_int
id|__init
id|typhoon_init
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef MODULE
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
l_string|&quot;radio-typhoon: You must set an I/O address with io=0x316 or io=0x336&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|typhoon_unit.iobase
op_assign
id|io
suffix:semicolon
r_if
c_cond
(paren
id|mutefreq
template_param
l_int|108500
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;radio-typhoon: You must set a frequency (in kHz) used when muting the card,&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;radio-typhoon: e.g. with &bslash;&quot;mutefreq=87500&bslash;&quot; (87000 &lt;= mutefreq &lt;= 108500)&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|typhoon_unit.mutefreq
op_assign
id|mutefreq
suffix:semicolon
macro_line|#endif /* MODULE */
id|printk
c_func
(paren
id|KERN_INFO
id|BANNER
)paren
suffix:semicolon
id|init_MUTEX
c_func
(paren
op_amp
id|typhoon_unit.lock
)paren
suffix:semicolon
id|io
op_assign
id|typhoon_unit.iobase
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
l_int|8
comma
l_string|&quot;typhoon&quot;
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;radio-typhoon: port 0x%x already in use&bslash;n&quot;
comma
id|typhoon_unit.iobase
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|typhoon_radio.priv
op_assign
op_amp
id|typhoon_unit
suffix:semicolon
r_if
c_cond
(paren
id|video_register_device
c_func
(paren
op_amp
id|typhoon_radio
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
l_int|8
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
l_string|&quot;radio-typhoon: port 0x%x.&bslash;n&quot;
comma
id|typhoon_unit.iobase
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;radio-typhoon: mute frequency is %lu kHz.&bslash;n&quot;
comma
id|typhoon_unit.mutefreq
)paren
suffix:semicolon
id|typhoon_unit.mutefreq
op_lshift_assign
l_int|4
suffix:semicolon
multiline_comment|/* mute card - prevents noisy bootups */
id|typhoon_mute
c_func
(paren
op_amp
id|typhoon_unit
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_RADIO_TYPHOON_PROC_FS
r_if
c_cond
(paren
op_logical_neg
id|create_proc_info_entry
c_func
(paren
l_string|&quot;driver/radio-typhoon&quot;
comma
l_int|0
comma
l_int|NULL
comma
id|typhoon_get_info
)paren
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;radio-typhoon: registering /proc/driver/radio-typhoon failed&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|typhoon_cleanup_module
r_static
r_void
id|__exit
id|typhoon_cleanup_module
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_RADIO_TYPHOON_PROC_FS
id|remove_proc_entry
c_func
(paren
l_string|&quot;driver/radio-typhoon&quot;
comma
l_int|NULL
)paren
suffix:semicolon
macro_line|#endif
id|video_unregister_device
c_func
(paren
op_amp
id|typhoon_radio
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|io
comma
l_int|8
)paren
suffix:semicolon
)brace
DECL|variable|typhoon_init
id|module_init
c_func
(paren
id|typhoon_init
)paren
suffix:semicolon
DECL|variable|typhoon_cleanup_module
id|module_exit
c_func
(paren
id|typhoon_cleanup_module
)paren
suffix:semicolon
eof
