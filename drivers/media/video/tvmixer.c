macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;linux/videodev.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kdev_t.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &lt;linux/sound.h&gt;
macro_line|#include &lt;linux/soundcard.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|macro|DEV_MAX
mdefine_line|#define DEV_MAX  4
DECL|variable|debug
r_static
r_int
id|debug
op_assign
l_int|0
suffix:semicolon
DECL|variable|devnr
r_static
r_int
id|devnr
op_assign
op_minus
l_int|1
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|debug
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|devnr
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Gerd Knorr&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
multiline_comment|/* ----------------------------------------------------------------------- */
DECL|struct|TVMIXER
r_struct
id|TVMIXER
(brace
DECL|member|dev
r_struct
id|i2c_client
op_star
id|dev
suffix:semicolon
DECL|member|minor
r_int
id|minor
suffix:semicolon
DECL|member|count
r_int
id|count
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|devices
r_static
r_struct
id|TVMIXER
id|devices
(braket
id|DEV_MAX
)braket
suffix:semicolon
r_static
r_int
id|tvmixer_adapters
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adap
)paren
suffix:semicolon
r_static
r_int
id|tvmixer_clients
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
)paren
suffix:semicolon
multiline_comment|/* ----------------------------------------------------------------------- */
DECL|function|mix_to_v4l
r_static
r_int
id|mix_to_v4l
c_func
(paren
r_int
id|i
)paren
(brace
r_int
id|r
suffix:semicolon
id|r
op_assign
(paren
(paren
id|i
op_amp
l_int|0xff
)paren
op_star
l_int|65536
op_plus
l_int|50
)paren
op_div
l_int|100
suffix:semicolon
r_if
c_cond
(paren
id|r
OG
l_int|65535
)paren
id|r
op_assign
l_int|65535
suffix:semicolon
r_if
c_cond
(paren
id|r
OL
l_int|0
)paren
id|r
op_assign
l_int|0
suffix:semicolon
r_return
id|r
suffix:semicolon
)brace
DECL|function|v4l_to_mix
r_static
r_int
id|v4l_to_mix
c_func
(paren
r_int
id|i
)paren
(brace
r_int
id|r
suffix:semicolon
id|r
op_assign
(paren
id|i
op_star
l_int|100
op_plus
l_int|32768
)paren
op_div
l_int|65536
suffix:semicolon
r_if
c_cond
(paren
id|r
OG
l_int|100
)paren
id|r
op_assign
l_int|100
suffix:semicolon
r_if
c_cond
(paren
id|r
OL
l_int|0
)paren
id|r
op_assign
l_int|0
suffix:semicolon
r_return
id|r
op_or
(paren
id|r
op_lshift
l_int|8
)paren
suffix:semicolon
)brace
DECL|function|v4l_to_mix2
r_static
r_int
id|v4l_to_mix2
c_func
(paren
r_int
id|l
comma
r_int
id|r
)paren
(brace
id|r
op_assign
(paren
id|r
op_star
l_int|100
op_plus
l_int|32768
)paren
op_div
l_int|65536
suffix:semicolon
r_if
c_cond
(paren
id|r
OG
l_int|100
)paren
id|r
op_assign
l_int|100
suffix:semicolon
r_if
c_cond
(paren
id|r
OL
l_int|0
)paren
id|r
op_assign
l_int|0
suffix:semicolon
id|l
op_assign
(paren
id|l
op_star
l_int|100
op_plus
l_int|32768
)paren
op_div
l_int|65536
suffix:semicolon
r_if
c_cond
(paren
id|l
OG
l_int|100
)paren
id|l
op_assign
l_int|100
suffix:semicolon
r_if
c_cond
(paren
id|l
OL
l_int|0
)paren
id|l
op_assign
l_int|0
suffix:semicolon
r_return
(paren
id|r
op_lshift
l_int|8
)paren
op_or
id|l
suffix:semicolon
)brace
DECL|function|tvmixer_ioctl
r_static
r_int
id|tvmixer_ioctl
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
r_struct
id|video_audio
id|va
suffix:semicolon
r_int
id|left
comma
id|right
comma
id|ret
comma
id|val
op_assign
l_int|0
suffix:semicolon
r_struct
id|TVMIXER
op_star
id|mix
op_assign
id|file-&gt;private_data
suffix:semicolon
r_struct
id|i2c_client
op_star
id|client
op_assign
id|mix-&gt;dev
suffix:semicolon
r_if
c_cond
(paren
l_int|NULL
op_eq
id|client
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|cmd
op_eq
id|SOUND_MIXER_INFO
)paren
(brace
id|mixer_info
id|info
suffix:semicolon
id|strncpy
c_func
(paren
id|info.id
comma
l_string|&quot;tv card&quot;
comma
r_sizeof
(paren
id|info.id
)paren
)paren
suffix:semicolon
id|strncpy
c_func
(paren
id|info.name
comma
id|client-&gt;dev.name
comma
r_sizeof
(paren
id|info.name
)paren
)paren
suffix:semicolon
id|info.modify_counter
op_assign
l_int|42
multiline_comment|/* FIXME */
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_void
op_star
)paren
id|arg
comma
op_amp
id|info
comma
r_sizeof
(paren
id|info
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cmd
op_eq
id|SOUND_OLD_MIXER_INFO
)paren
(brace
id|_old_mixer_info
id|info
suffix:semicolon
id|strncpy
c_func
(paren
id|info.id
comma
l_string|&quot;tv card&quot;
comma
r_sizeof
(paren
id|info.id
)paren
)paren
suffix:semicolon
id|strncpy
c_func
(paren
id|info.name
comma
id|client-&gt;dev.name
comma
r_sizeof
(paren
id|info.name
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_void
op_star
)paren
id|arg
comma
op_amp
id|info
comma
r_sizeof
(paren
id|info
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cmd
op_eq
id|OSS_GETVERSION
)paren
r_return
id|put_user
c_func
(paren
id|SOUND_VERSION
comma
(paren
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|_SIOC_DIR
c_func
(paren
id|cmd
)paren
op_amp
id|_SIOC_WRITE
)paren
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|val
comma
(paren
r_int
op_star
)paren
id|arg
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
multiline_comment|/* read state */
id|memset
c_func
(paren
op_amp
id|va
comma
l_int|0
comma
r_sizeof
(paren
id|va
)paren
)paren
suffix:semicolon
id|client-&gt;driver
op_member_access_from_pointer
id|command
c_func
(paren
id|client
comma
id|VIDIOCGAUDIO
comma
op_amp
id|va
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|MIXER_READ
c_func
(paren
id|SOUND_MIXER_RECMASK
)paren
suffix:colon
r_case
id|MIXER_READ
c_func
(paren
id|SOUND_MIXER_CAPS
)paren
suffix:colon
r_case
id|MIXER_READ
c_func
(paren
id|SOUND_MIXER_RECSRC
)paren
suffix:colon
r_case
id|MIXER_WRITE
c_func
(paren
id|SOUND_MIXER_RECSRC
)paren
suffix:colon
id|ret
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MIXER_READ
c_func
(paren
id|SOUND_MIXER_STEREODEVS
)paren
suffix:colon
id|ret
op_assign
id|SOUND_MASK_VOLUME
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MIXER_READ
c_func
(paren
id|SOUND_MIXER_DEVMASK
)paren
suffix:colon
id|ret
op_assign
id|SOUND_MASK_VOLUME
suffix:semicolon
r_if
c_cond
(paren
id|va.flags
op_amp
id|VIDEO_AUDIO_BASS
)paren
id|ret
op_or_assign
id|SOUND_MASK_BASS
suffix:semicolon
r_if
c_cond
(paren
id|va.flags
op_amp
id|VIDEO_AUDIO_TREBLE
)paren
id|ret
op_or_assign
id|SOUND_MASK_TREBLE
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MIXER_WRITE
c_func
(paren
id|SOUND_MIXER_VOLUME
)paren
suffix:colon
id|left
op_assign
id|mix_to_v4l
c_func
(paren
id|val
)paren
suffix:semicolon
id|right
op_assign
id|mix_to_v4l
c_func
(paren
id|val
op_rshift
l_int|8
)paren
suffix:semicolon
id|va.volume
op_assign
id|max
c_func
(paren
id|left
comma
id|right
)paren
suffix:semicolon
id|va.balance
op_assign
(paren
l_int|32768
op_star
id|min
c_func
(paren
id|left
comma
id|right
)paren
)paren
op_div
(paren
id|va.volume
ques
c_cond
id|va.volume
suffix:colon
l_int|1
)paren
suffix:semicolon
id|va.balance
op_assign
(paren
id|left
OL
id|right
)paren
ques
c_cond
(paren
l_int|65535
op_minus
id|va.balance
)paren
suffix:colon
id|va.balance
suffix:semicolon
id|client-&gt;driver
op_member_access_from_pointer
id|command
c_func
(paren
id|client
comma
id|VIDIOCSAUDIO
comma
op_amp
id|va
)paren
suffix:semicolon
id|client-&gt;driver
op_member_access_from_pointer
id|command
c_func
(paren
id|client
comma
id|VIDIOCGAUDIO
comma
op_amp
id|va
)paren
suffix:semicolon
multiline_comment|/* fall throuth */
r_case
id|MIXER_READ
c_func
(paren
id|SOUND_MIXER_VOLUME
)paren
suffix:colon
id|left
op_assign
(paren
id|min
c_func
(paren
l_int|65536
op_minus
id|va.balance
comma
l_int|32768
)paren
op_star
id|va.volume
)paren
op_div
l_int|32768
suffix:semicolon
id|right
op_assign
(paren
id|min
c_func
(paren
id|va.balance
comma
l_int|32768
)paren
op_star
id|va.volume
)paren
op_div
l_int|32768
suffix:semicolon
id|ret
op_assign
id|v4l_to_mix2
c_func
(paren
id|left
comma
id|right
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MIXER_WRITE
c_func
(paren
id|SOUND_MIXER_BASS
)paren
suffix:colon
id|va.bass
op_assign
id|mix_to_v4l
c_func
(paren
id|val
)paren
suffix:semicolon
id|client-&gt;driver
op_member_access_from_pointer
id|command
c_func
(paren
id|client
comma
id|VIDIOCSAUDIO
comma
op_amp
id|va
)paren
suffix:semicolon
id|client-&gt;driver
op_member_access_from_pointer
id|command
c_func
(paren
id|client
comma
id|VIDIOCGAUDIO
comma
op_amp
id|va
)paren
suffix:semicolon
multiline_comment|/* fall throuth  */
r_case
id|MIXER_READ
c_func
(paren
id|SOUND_MIXER_BASS
)paren
suffix:colon
id|ret
op_assign
id|v4l_to_mix
c_func
(paren
id|va.bass
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MIXER_WRITE
c_func
(paren
id|SOUND_MIXER_TREBLE
)paren
suffix:colon
id|va.treble
op_assign
id|mix_to_v4l
c_func
(paren
id|val
)paren
suffix:semicolon
id|client-&gt;driver
op_member_access_from_pointer
id|command
c_func
(paren
id|client
comma
id|VIDIOCSAUDIO
comma
op_amp
id|va
)paren
suffix:semicolon
id|client-&gt;driver
op_member_access_from_pointer
id|command
c_func
(paren
id|client
comma
id|VIDIOCGAUDIO
comma
op_amp
id|va
)paren
suffix:semicolon
multiline_comment|/* fall throuth */
r_case
id|MIXER_READ
c_func
(paren
id|SOUND_MIXER_TREBLE
)paren
suffix:colon
id|ret
op_assign
id|v4l_to_mix
c_func
(paren
id|va.treble
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|ret
comma
(paren
r_int
op_star
)paren
id|arg
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|tvmixer_open
r_static
r_int
id|tvmixer_open
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
(brace
r_int
id|i
comma
id|minor
op_assign
id|minor
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
r_struct
id|TVMIXER
op_star
id|mix
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|i2c_client
op_star
id|client
op_assign
l_int|NULL
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
id|DEV_MAX
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|devices
(braket
id|i
)braket
dot
id|minor
op_eq
id|minor
)paren
(brace
id|mix
op_assign
id|devices
op_plus
id|i
suffix:semicolon
id|client
op_assign
id|mix-&gt;dev
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
l_int|NULL
op_eq
id|client
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
multiline_comment|/* lock bttv in memory while the mixer is in use  */
id|file-&gt;private_data
op_assign
id|mix
suffix:semicolon
r_if
c_cond
(paren
id|client-&gt;adapter-&gt;owner
)paren
id|try_module_get
c_func
(paren
id|client-&gt;adapter-&gt;owner
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|tvmixer_release
r_static
r_int
id|tvmixer_release
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
(brace
r_struct
id|TVMIXER
op_star
id|mix
op_assign
id|file-&gt;private_data
suffix:semicolon
r_struct
id|i2c_client
op_star
id|client
suffix:semicolon
id|client
op_assign
id|mix-&gt;dev
suffix:semicolon
r_if
c_cond
(paren
l_int|NULL
op_eq
id|client
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_if
c_cond
(paren
id|client-&gt;adapter-&gt;owner
)paren
id|module_put
c_func
(paren
id|client-&gt;adapter-&gt;owner
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|driver
r_static
r_struct
id|i2c_driver
id|driver
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
l_string|&quot;tv card mixer driver&quot;
comma
dot
id|id
op_assign
id|I2C_DRIVERID_TVMIXER
comma
dot
id|flags
op_assign
id|I2C_DF_DUMMY
comma
dot
id|attach_adapter
op_assign
id|tvmixer_adapters
comma
dot
id|detach_client
op_assign
id|tvmixer_clients
comma
)brace
suffix:semicolon
DECL|variable|tvmixer_fops
r_static
r_struct
id|file_operations
id|tvmixer_fops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|llseek
op_assign
id|no_llseek
comma
dot
id|ioctl
op_assign
id|tvmixer_ioctl
comma
dot
id|open
op_assign
id|tvmixer_open
comma
dot
id|release
op_assign
id|tvmixer_release
comma
)brace
suffix:semicolon
multiline_comment|/* ----------------------------------------------------------------------- */
DECL|function|tvmixer_adapters
r_static
r_int
id|tvmixer_adapters
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adap
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|debug
)paren
id|printk
c_func
(paren
l_string|&quot;tvmixer: adapter %s&bslash;n&quot;
comma
id|adap-&gt;dev.name
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
id|I2C_CLIENT_MAX
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|adap-&gt;clients
(braket
id|i
)braket
)paren
r_continue
suffix:semicolon
id|tvmixer_clients
c_func
(paren
id|adap-&gt;clients
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|tvmixer_clients
r_static
r_int
id|tvmixer_clients
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
)paren
(brace
r_struct
id|video_audio
id|va
suffix:semicolon
r_int
id|i
comma
id|minor
suffix:semicolon
multiline_comment|/* TV card ??? */
r_switch
c_cond
(paren
id|client-&gt;adapter-&gt;id
)paren
(brace
r_case
id|I2C_ALGO_BIT
op_or
id|I2C_HW_B_BT848
suffix:colon
r_case
id|I2C_ALGO_BIT
op_or
id|I2C_HW_B_RIVA
suffix:colon
multiline_comment|/* ok, have a look ... */
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
multiline_comment|/* ignore that one */
r_if
c_cond
(paren
id|debug
)paren
id|printk
c_func
(paren
l_string|&quot;tvmixer: %s is not a tv card&bslash;n&quot;
comma
id|client-&gt;adapter-&gt;dev.name
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;tvmixer: debug: %s&bslash;n&quot;
comma
id|client-&gt;dev.name
)paren
suffix:semicolon
multiline_comment|/* unregister ?? */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|DEV_MAX
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|devices
(braket
id|i
)braket
dot
id|dev
op_eq
id|client
)paren
(brace
multiline_comment|/* unregister */
id|unregister_sound_mixer
c_func
(paren
id|devices
(braket
id|i
)braket
dot
id|minor
)paren
suffix:semicolon
id|devices
(braket
id|i
)braket
dot
id|dev
op_assign
l_int|NULL
suffix:semicolon
id|devices
(braket
id|i
)braket
dot
id|minor
op_assign
op_minus
l_int|1
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;tvmixer: %s unregistered (#1)&bslash;n&quot;
comma
id|client-&gt;dev.name
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
multiline_comment|/* look for a free slot */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|DEV_MAX
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
l_int|NULL
op_eq
id|devices
(braket
id|i
)braket
dot
id|dev
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
id|DEV_MAX
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;tvmixer: DEV_MAX too small&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* audio chip with mixer ??? */
r_if
c_cond
(paren
l_int|NULL
op_eq
id|client-&gt;driver-&gt;command
)paren
(brace
r_if
c_cond
(paren
id|debug
)paren
id|printk
c_func
(paren
l_string|&quot;tvmixer: %s: driver-&gt;command is NULL&bslash;n&quot;
comma
id|client-&gt;driver-&gt;name
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|memset
c_func
(paren
op_amp
id|va
comma
l_int|0
comma
r_sizeof
(paren
id|va
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_ne
id|client-&gt;driver
op_member_access_from_pointer
id|command
c_func
(paren
id|client
comma
id|VIDIOCGAUDIO
comma
op_amp
id|va
)paren
)paren
(brace
r_if
c_cond
(paren
id|debug
)paren
id|printk
c_func
(paren
l_string|&quot;tvmixer: %s: VIDIOCGAUDIO failed&bslash;n&quot;
comma
id|client-&gt;dev.name
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
l_int|0
op_eq
(paren
id|va.flags
op_amp
id|VIDEO_AUDIO_VOLUME
)paren
)paren
(brace
r_if
c_cond
(paren
id|debug
)paren
id|printk
c_func
(paren
l_string|&quot;tvmixer: %s: has no volume control&bslash;n&quot;
comma
id|client-&gt;dev.name
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* everything is fine, register */
r_if
c_cond
(paren
(paren
id|minor
op_assign
id|register_sound_mixer
c_func
(paren
op_amp
id|tvmixer_fops
comma
id|devnr
)paren
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;tvmixer: cannot allocate mixer device&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|devices
(braket
id|i
)braket
dot
id|minor
op_assign
id|minor
suffix:semicolon
id|devices
(braket
id|i
)braket
dot
id|count
op_assign
l_int|0
suffix:semicolon
id|devices
(braket
id|i
)braket
dot
id|dev
op_assign
id|client
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;tvmixer: %s (%s) registered with minor %d&bslash;n&quot;
comma
id|client-&gt;dev.name
comma
id|client-&gt;adapter-&gt;dev.name
comma
id|minor
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* ----------------------------------------------------------------------- */
DECL|function|tvmixer_init_module
r_static
r_int
id|tvmixer_init_module
c_func
(paren
r_void
)paren
(brace
r_int
id|i
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
id|DEV_MAX
suffix:semicolon
id|i
op_increment
)paren
id|devices
(braket
id|i
)braket
dot
id|minor
op_assign
op_minus
l_int|1
suffix:semicolon
id|i2c_add_driver
c_func
(paren
op_amp
id|driver
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|tvmixer_cleanup_module
r_static
r_void
id|tvmixer_cleanup_module
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|i2c_del_driver
c_func
(paren
op_amp
id|driver
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
id|DEV_MAX
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|devices
(braket
id|i
)braket
dot
id|minor
op_ne
op_minus
l_int|1
)paren
(brace
id|unregister_sound_mixer
c_func
(paren
id|devices
(braket
id|i
)braket
dot
id|minor
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;tvmixer: %s unregistered (#2)&bslash;n&quot;
comma
id|devices
(braket
id|i
)braket
dot
id|dev-&gt;dev.name
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|variable|tvmixer_init_module
id|module_init
c_func
(paren
id|tvmixer_init_module
)paren
suffix:semicolon
DECL|variable|tvmixer_cleanup_module
id|module_exit
c_func
(paren
id|tvmixer_cleanup_module
)paren
suffix:semicolon
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-basic-offset: 8&n; * End:&n; */
eof
