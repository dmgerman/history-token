multiline_comment|/* GemTek radio card driver for Linux (C) 1998 Jonas Munsin &lt;jmunsin@iki.fi&gt;&n; *&n; * GemTek hasn&squot;t released any specs on the card, so the protocol had to&n; * be reverse engineered with dosemu.&n; *&n; * Besides the protocol changes, this is mostly a copy of:&n; *&n; *    RadioTrack II driver for Linux radio support (C) 1998 Ben Pfaff&n; * &n; *    Based on RadioTrack I/RadioReveal (C) 1997 M. Kirkwood&n; *    Coverted to new API by Alan Cox &lt;Alan.Cox@linux.org&gt;&n; *    Various bugfixes and enhancements by Russell Kroll &lt;rkroll@exploits.org&gt;&n; *&n; * TODO: Allow for more than one of these foolish entities :-)&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;&t;/* Modules &t;&t;&t;*/
macro_line|#include &lt;linux/init.h&gt;&t;&t;/* Initdata&t;&t;&t;*/
macro_line|#include &lt;linux/ioport.h&gt;&t;/* check_region, request_region&t;*/
macro_line|#include &lt;linux/delay.h&gt;&t;/* udelay&t;&t;&t;*/
macro_line|#include &lt;asm/io.h&gt;&t;&t;/* outb, outb_p&t;&t;&t;*/
macro_line|#include &lt;asm/uaccess.h&gt;&t;/* copy to/from user&t;&t;*/
macro_line|#include &lt;linux/videodev.h&gt;&t;/* kernel radio structs&t;&t;*/
macro_line|#include &lt;linux/config.h&gt;&t;/* CONFIG_RADIO_GEMTEK_PORT &t;*/
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#ifndef CONFIG_RADIO_GEMTEK_PORT
DECL|macro|CONFIG_RADIO_GEMTEK_PORT
mdefine_line|#define CONFIG_RADIO_GEMTEK_PORT -1
macro_line|#endif
DECL|variable|io
r_static
r_int
id|io
op_assign
id|CONFIG_RADIO_GEMTEK_PORT
suffix:semicolon
DECL|variable|radio_nr
r_static
r_int
id|radio_nr
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|variable|users
r_static
r_int
id|users
op_assign
l_int|0
suffix:semicolon
DECL|variable|lock
r_static
id|spinlock_t
id|lock
suffix:semicolon
DECL|struct|gemtek_device
r_struct
id|gemtek_device
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
multiline_comment|/* the correct way to mute the gemtek may be to write the last written&n; * frequency || 0x10, but just writing 0x10 once seems to do it as well&n; */
DECL|function|gemtek_mute
r_static
r_void
id|gemtek_mute
c_func
(paren
r_struct
id|gemtek_device
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
l_int|0x10
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
DECL|function|gemtek_unmute
r_static
r_void
id|gemtek_unmute
c_func
(paren
r_struct
id|gemtek_device
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
l_int|0x20
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
l_int|0x04
comma
id|io
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|5
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x05
comma
id|io
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|5
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
l_int|0x06
comma
id|io
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|5
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x07
comma
id|io
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|5
)paren
suffix:semicolon
)brace
DECL|function|gemtek_setfreq
r_static
r_int
id|gemtek_setfreq
c_func
(paren
r_struct
id|gemtek_device
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
multiline_comment|/*        freq = 78.25*((float)freq/16000.0 + 10.52); */
id|freq
op_div_assign
l_int|16
suffix:semicolon
id|freq
op_add_assign
l_int|10520
suffix:semicolon
id|freq
op_mul_assign
l_int|7825
suffix:semicolon
id|freq
op_div_assign
l_int|100000
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|lock
)paren
suffix:semicolon
multiline_comment|/* 2 start bits */
id|outb_p
c_func
(paren
l_int|0x03
comma
id|io
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|5
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x07
comma
id|io
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|5
)paren
suffix:semicolon
multiline_comment|/* 28 frequency bits (lsb first) */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|14
suffix:semicolon
id|i
op_increment
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
c_func
(paren
)paren
suffix:semicolon
r_else
id|zero
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* 36 unknown bits */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|11
suffix:semicolon
id|i
op_increment
)paren
id|zero
c_func
(paren
)paren
suffix:semicolon
id|one
c_func
(paren
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
l_int|4
suffix:semicolon
id|i
op_increment
)paren
id|zero
c_func
(paren
)paren
suffix:semicolon
id|one
c_func
(paren
)paren
suffix:semicolon
id|zero
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* 2 end bits */
id|outb_p
c_func
(paren
l_int|0x03
comma
id|io
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|5
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x07
comma
id|io
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|5
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
DECL|function|gemtek_getsigstr
r_int
id|gemtek_getsigstr
c_func
(paren
r_struct
id|gemtek_device
op_star
id|dev
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|lock
)paren
suffix:semicolon
id|inb
c_func
(paren
id|io
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|5
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inb
c_func
(paren
id|io
)paren
op_amp
l_int|8
)paren
multiline_comment|/* bit set = no signal present */
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
multiline_comment|/* signal present */
)brace
DECL|function|gemtek_ioctl
r_static
r_int
id|gemtek_ioctl
c_func
(paren
r_struct
id|video_device
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
(brace
r_struct
id|gemtek_device
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
id|v
suffix:semicolon
id|v.type
op_assign
id|VID_TYPE_TUNER
suffix:semicolon
id|v.channels
op_assign
l_int|1
suffix:semicolon
id|v.audios
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* No we don&squot;t do pictures */
id|v.maxwidth
op_assign
l_int|0
suffix:semicolon
id|v.maxheight
op_assign
l_int|0
suffix:semicolon
id|v.minwidth
op_assign
l_int|0
suffix:semicolon
id|v.minheight
op_assign
l_int|0
suffix:semicolon
id|strcpy
c_func
(paren
id|v.name
comma
l_string|&quot;GemTek&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|arg
comma
op_amp
id|v
comma
r_sizeof
(paren
id|v
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
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
id|v
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|v
comma
id|arg
comma
r_sizeof
(paren
id|v
)paren
)paren
op_ne
l_int|0
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|v.tuner
)paren
(brace
multiline_comment|/* Only 1 tuner */
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|v.rangelow
op_assign
l_int|87
op_star
l_int|16000
suffix:semicolon
id|v.rangehigh
op_assign
l_int|108
op_star
l_int|16000
suffix:semicolon
id|v.flags
op_assign
id|VIDEO_TUNER_LOW
suffix:semicolon
id|v.mode
op_assign
id|VIDEO_MODE_AUTO
suffix:semicolon
id|v.signal
op_assign
l_int|0xFFFF
op_star
id|gemtek_getsigstr
c_func
(paren
id|rt
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|v.name
comma
l_string|&quot;FM&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|arg
comma
op_amp
id|v
comma
r_sizeof
(paren
id|v
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
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
id|v
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|v
comma
id|arg
comma
r_sizeof
(paren
id|v
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|v.tuner
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
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|arg
comma
op_amp
id|rt-&gt;curfreq
comma
r_sizeof
(paren
id|rt-&gt;curfreq
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
r_case
id|VIDIOCSFREQ
suffix:colon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|rt-&gt;curfreq
comma
id|arg
comma
r_sizeof
(paren
id|rt-&gt;curfreq
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
multiline_comment|/* needs to be called twice in order for getsigstr to work */
id|gemtek_setfreq
c_func
(paren
id|rt
comma
id|rt-&gt;curfreq
)paren
suffix:semicolon
id|gemtek_setfreq
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
r_case
id|VIDIOCGAUDIO
suffix:colon
(brace
r_struct
id|video_audio
id|v
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
id|v
)paren
)paren
suffix:semicolon
id|v.flags
op_or_assign
id|VIDEO_AUDIO_MUTABLE
suffix:semicolon
id|v.volume
op_assign
l_int|1
suffix:semicolon
id|v.step
op_assign
l_int|65535
suffix:semicolon
id|strcpy
c_func
(paren
id|v.name
comma
l_string|&quot;Radio&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|arg
comma
op_amp
id|v
comma
r_sizeof
(paren
id|v
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
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
id|v
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|v
comma
id|arg
comma
r_sizeof
(paren
id|v
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|v.audio
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
id|v.flags
op_amp
id|VIDEO_AUDIO_MUTE
)paren
(brace
id|gemtek_mute
c_func
(paren
id|rt
)paren
suffix:semicolon
)brace
r_else
id|gemtek_unmute
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
DECL|function|gemtek_open
r_static
r_int
id|gemtek_open
c_func
(paren
r_struct
id|video_device
op_star
id|dev
comma
r_int
id|flags
)paren
(brace
r_if
c_cond
(paren
id|users
)paren
(brace
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|users
op_increment
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|gemtek_close
r_static
r_void
id|gemtek_close
c_func
(paren
r_struct
id|video_device
op_star
id|dev
)paren
(brace
id|users
op_decrement
suffix:semicolon
)brace
DECL|variable|gemtek_unit
r_static
r_struct
id|gemtek_device
id|gemtek_unit
suffix:semicolon
DECL|variable|gemtek_radio
r_static
r_struct
id|video_device
id|gemtek_radio
op_assign
(brace
id|owner
suffix:colon
id|THIS_MODULE
comma
id|name
suffix:colon
l_string|&quot;GemTek radio&quot;
comma
id|type
suffix:colon
id|VID_TYPE_TUNER
comma
id|hardware
suffix:colon
id|VID_HARDWARE_GEMTEK
comma
id|open
suffix:colon
id|gemtek_open
comma
id|close
suffix:colon
id|gemtek_close
comma
id|ioctl
suffix:colon
id|gemtek_ioctl
comma
)brace
suffix:semicolon
DECL|function|gemtek_init
r_static
r_int
id|__init
id|gemtek_init
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
l_string|&quot;You must set an I/O address with io=0x20c, io=0x30c, io=0x24c or io=0x34c (io=0x020c or io=0x248 for the combined sound/radiocard)&bslash;n&quot;
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
l_string|&quot;gemtek&quot;
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;gemtek: port 0x%x already in use&bslash;n&quot;
comma
id|io
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|gemtek_radio.priv
op_assign
op_amp
id|gemtek_unit
suffix:semicolon
r_if
c_cond
(paren
id|video_register_device
c_func
(paren
op_amp
id|gemtek_radio
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
l_string|&quot;GemTek Radio Card driver.&bslash;n&quot;
)paren
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|lock
)paren
suffix:semicolon
multiline_comment|/* mute card - prevents noisy bootups */
id|outb
c_func
(paren
l_int|0x10
comma
id|io
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|5
)paren
suffix:semicolon
id|gemtek_unit.muted
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* this is _maybe_ unnecessary */
id|outb
c_func
(paren
l_int|0x01
comma
id|io
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Jonas Munsin&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;A driver for the GemTek Radio Card&quot;
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
l_string|&quot;I/O address of the GemTek card (0x20c, 0x30c, 0x24c or 0x34c (0x20c or 0x248 have been reported to work for the combined sound/radiocard)).&quot;
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
id|EXPORT_NO_SYMBOLS
suffix:semicolon
DECL|function|gemtek_cleanup
r_static
r_void
id|__exit
id|gemtek_cleanup
c_func
(paren
r_void
)paren
(brace
id|video_unregister_device
c_func
(paren
op_amp
id|gemtek_radio
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
DECL|variable|gemtek_init
id|module_init
c_func
(paren
id|gemtek_init
)paren
suffix:semicolon
DECL|variable|gemtek_cleanup
id|module_exit
c_func
(paren
id|gemtek_cleanup
)paren
suffix:semicolon
multiline_comment|/*&n;  Local variables:&n;  compile-command: &quot;gcc -c -DMODVERSIONS -D__KERNEL__ -DMODULE -O6 -Wall -Wstrict-prototypes -I /home/blp/tmp/linux-2.1.111-rtrack/include radio-rtrack2.c&quot;&n;  End:&n;*/
eof
