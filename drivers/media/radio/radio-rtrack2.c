multiline_comment|/* RadioTrack II driver for Linux radio support (C) 1998 Ben Pfaff&n; * &n; * Based on RadioTrack I/RadioReveal (C) 1997 M. Kirkwood&n; * Converted to new API by Alan Cox &lt;Alan.Cox@linux.org&gt;&n; * Various bugfixes and enhancements by Russell Kroll &lt;rkroll@exploits.org&gt;&n; *&n; * TODO: Allow for more than one of these foolish entities :-)&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;&t;/* Modules &t;&t;&t;*/
macro_line|#include &lt;linux/init.h&gt;&t;&t;/* Initdata&t;&t;&t;*/
macro_line|#include &lt;linux/ioport.h&gt;&t;/* check_region, request_region&t;*/
macro_line|#include &lt;linux/delay.h&gt;&t;/* udelay&t;&t;&t;*/
macro_line|#include &lt;asm/io.h&gt;&t;&t;/* outb, outb_p&t;&t;&t;*/
macro_line|#include &lt;asm/uaccess.h&gt;&t;/* copy to/from user&t;&t;*/
macro_line|#include &lt;linux/videodev.h&gt;&t;/* kernel radio structs&t;&t;*/
macro_line|#include &lt;linux/config.h&gt;&t;/* CONFIG_RADIO_RTRACK2_PORT &t;*/
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#ifndef CONFIG_RADIO_RTRACK2_PORT
DECL|macro|CONFIG_RADIO_RTRACK2_PORT
mdefine_line|#define CONFIG_RADIO_RTRACK2_PORT -1
macro_line|#endif
DECL|variable|io
r_static
r_int
id|io
op_assign
id|CONFIG_RADIO_RTRACK2_PORT
suffix:semicolon
DECL|variable|radio_nr
r_static
r_int
id|radio_nr
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|variable|lock
r_static
id|spinlock_t
id|lock
suffix:semicolon
DECL|struct|rt_device
r_struct
id|rt_device
(brace
DECL|member|port
r_int
id|port
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
)brace
suffix:semicolon
multiline_comment|/* local things */
DECL|function|rt_mute
r_static
r_void
id|rt_mute
c_func
(paren
r_struct
id|rt_device
op_star
id|dev
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;muted
)paren
(brace
r_return
suffix:semicolon
)brace
id|spin_lock
c_func
(paren
op_amp
id|lock
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|1
comma
id|io
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|lock
)paren
suffix:semicolon
id|dev-&gt;muted
op_assign
l_int|1
suffix:semicolon
)brace
DECL|function|rt_unmute
r_static
r_void
id|rt_unmute
c_func
(paren
r_struct
id|rt_device
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
(brace
r_return
suffix:semicolon
)brace
id|spin_lock
c_func
(paren
op_amp
id|lock
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
id|spin_unlock
c_func
(paren
op_amp
id|lock
)paren
suffix:semicolon
id|dev-&gt;muted
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|zero
r_static
r_void
id|zero
c_func
(paren
r_void
)paren
(brace
id|outb_p
c_func
(paren
l_int|1
comma
id|io
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|3
comma
id|io
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|1
comma
id|io
)paren
suffix:semicolon
)brace
DECL|function|one
r_static
r_void
id|one
c_func
(paren
r_void
)paren
(brace
id|outb_p
c_func
(paren
l_int|5
comma
id|io
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|7
comma
id|io
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|5
comma
id|io
)paren
suffix:semicolon
)brace
DECL|function|rt_setfreq
r_static
r_int
id|rt_setfreq
c_func
(paren
r_struct
id|rt_device
op_star
id|dev
comma
r_int
r_int
id|freq
)paren
(brace
r_int
id|i
suffix:semicolon
id|freq
op_assign
id|freq
op_div
l_int|200
op_plus
l_int|856
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|lock
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0xc8
comma
id|io
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0xc9
comma
id|io
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0xc9
comma
id|io
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|10
suffix:semicolon
id|i
op_increment
)paren
id|zero
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|14
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
r_if
c_cond
(paren
id|freq
op_amp
(paren
l_int|1
op_lshift
id|i
)paren
)paren
id|one
(paren
)paren
suffix:semicolon
r_else
id|zero
(paren
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0xc8
comma
id|io
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;muted
)paren
id|outb_p
c_func
(paren
l_int|0
comma
id|io
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|rt_getsigstr
r_static
r_int
id|rt_getsigstr
c_func
(paren
r_struct
id|rt_device
op_star
id|dev
)paren
(brace
r_if
c_cond
(paren
id|inb
c_func
(paren
id|io
)paren
op_amp
l_int|2
)paren
multiline_comment|/* bit set = no signal present&t;*/
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
multiline_comment|/* signal present&t;&t;*/
)brace
DECL|function|rt_do_ioctl
r_static
r_int
id|rt_do_ioctl
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
id|rt_device
op_star
id|rt
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
l_string|&quot;RadioTrack II&quot;
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
(brace
multiline_comment|/* Only 1 tuner */
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|v-&gt;rangelow
op_assign
l_int|88
op_star
l_int|16000
suffix:semicolon
id|v-&gt;rangehigh
op_assign
l_int|108
op_star
l_int|16000
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
op_star
id|rt_getsigstr
c_func
(paren
id|rt
)paren
suffix:semicolon
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
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
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
id|rt-&gt;curfreq
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
id|rt-&gt;curfreq
op_assign
op_star
id|freq
suffix:semicolon
id|rt_setfreq
c_func
(paren
id|rt
comma
id|rt-&gt;curfreq
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
suffix:semicolon
id|v-&gt;volume
op_assign
l_int|1
suffix:semicolon
id|v-&gt;step
op_assign
l_int|65535
suffix:semicolon
id|strcpy
c_func
(paren
id|v-&gt;name
comma
l_string|&quot;Radio&quot;
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
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|v-&gt;flags
op_amp
id|VIDEO_AUDIO_MUTE
)paren
(brace
id|rt_mute
c_func
(paren
id|rt
)paren
suffix:semicolon
)brace
r_else
id|rt_unmute
c_func
(paren
id|rt
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
DECL|function|rt_ioctl
r_static
r_int
id|rt_ioctl
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
id|rt_do_ioctl
)paren
suffix:semicolon
)brace
DECL|variable|rtrack2_unit
r_static
r_struct
id|rt_device
id|rtrack2_unit
suffix:semicolon
DECL|variable|rtrack2_fops
r_static
r_struct
id|file_operations
id|rtrack2_fops
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
id|rt_ioctl
comma
dot
id|llseek
op_assign
id|no_llseek
comma
)brace
suffix:semicolon
DECL|variable|rtrack2_radio
r_static
r_struct
id|video_device
id|rtrack2_radio
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
l_string|&quot;RadioTrack II radio&quot;
comma
dot
id|type
op_assign
id|VID_TYPE_TUNER
comma
dot
id|hardware
op_assign
id|VID_HARDWARE_RTRACK2
comma
dot
id|fops
op_assign
op_amp
id|rtrack2_fops
comma
)brace
suffix:semicolon
DECL|function|rtrack2_init
r_static
r_int
id|__init
id|rtrack2_init
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
l_string|&quot;You must set an I/O address with io=0x20c or io=0x30c&bslash;n&quot;
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
op_logical_neg
id|request_region
c_func
(paren
id|io
comma
l_int|4
comma
l_string|&quot;rtrack2&quot;
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;rtrack2: port 0x%x already in use&bslash;n&quot;
comma
id|io
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|rtrack2_radio.priv
op_assign
op_amp
id|rtrack2_unit
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|video_register_device
c_func
(paren
op_amp
id|rtrack2_radio
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
l_int|4
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
l_string|&quot;AIMSlab Radiotrack II card driver.&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* mute card - prevents noisy bootups */
id|outb
c_func
(paren
l_int|1
comma
id|io
)paren
suffix:semicolon
id|rtrack2_unit.muted
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
l_string|&quot;Ben Pfaff&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;A driver for the RadioTrack II radio card.&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
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
l_string|&quot;I/O address of the RadioTrack card (0x20c or 0x30c)&quot;
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
DECL|function|rtrack2_cleanup_module
r_static
r_void
id|__exit
id|rtrack2_cleanup_module
c_func
(paren
r_void
)paren
(brace
id|video_unregister_device
c_func
(paren
op_amp
id|rtrack2_radio
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|io
comma
l_int|4
)paren
suffix:semicolon
)brace
DECL|variable|rtrack2_init
id|module_init
c_func
(paren
id|rtrack2_init
)paren
suffix:semicolon
DECL|variable|rtrack2_cleanup_module
id|module_exit
c_func
(paren
id|rtrack2_cleanup_module
)paren
suffix:semicolon
multiline_comment|/*&n;  Local variables:&n;  compile-command: &quot;mmake&quot;&n;  End:&n;*/
eof
