multiline_comment|/* &n; * Guillemot Maxi Radio FM 2000 PCI radio card driver for Linux &n; * (C) 2001 Dimitromanolakis Apostolos &lt;apdim@grecian.net&gt;&n; *&n; * Based in the radio Maestro PCI driver. Actually it uses the same chip&n; * for radio but different pci controller.&n; *&n; * I didn&squot;t have any specs I reversed engineered the protocol from&n; * the windows driver (radio.dll). &n; *&n; * The card uses the TEA5757 chip that includes a search function but it&n; * is useless as I haven&squot;t found any way to read back the frequency. If &n; * anybody does please mail me.&n; *&n; * For the pdf file see:&n; * http://www.semiconductors.philips.com/pip/TEA5757H/V1&n; *&n; *&n; * CHANGES:&n; *   0.75b&n; *     - better pci interface thanks to Francois Romieu &lt;romieu@cogenit.fr&gt;&n; *&n; *   0.75&n; *     - tiding up&n; *     - removed support for multiple devices as it didn&squot;t work anyway&n; *&n; * BUGS: &n; *   - card unmutes if you change frequency&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/videodev.h&gt;
multiline_comment|/* version 0.75      Sun Feb  4 22:51:27 EET 2001 */
DECL|macro|DRIVER_VERSION
mdefine_line|#define DRIVER_VERSION&t;&quot;0.75&quot;
macro_line|#ifndef PCI_VENDOR_ID_GUILLEMOT
DECL|macro|PCI_VENDOR_ID_GUILLEMOT
mdefine_line|#define PCI_VENDOR_ID_GUILLEMOT 0x5046
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_GUILLEMOT
DECL|macro|PCI_DEVICE_ID_GUILLEMOT_MAXIRADIO
mdefine_line|#define PCI_DEVICE_ID_GUILLEMOT_MAXIRADIO 0x1001
macro_line|#endif
multiline_comment|/* TEA5757 pin mappings */
DECL|variable|clk
DECL|variable|data
DECL|variable|wren
DECL|variable|mo_st
DECL|variable|power
r_static
r_const
r_int
id|clk
op_assign
l_int|1
comma
id|data
op_assign
l_int|2
comma
id|wren
op_assign
l_int|4
comma
id|mo_st
op_assign
l_int|8
comma
id|power
op_assign
l_int|16
suffix:semicolon
DECL|variable|radio_nr
r_static
r_int
id|radio_nr
op_assign
op_minus
l_int|1
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|radio_nr
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
DECL|macro|FREQ_LO
mdefine_line|#define FREQ_LO&t;&t; 50*16000
DECL|macro|FREQ_HI
mdefine_line|#define FREQ_HI&t;&t;150*16000
DECL|macro|FREQ_IF
mdefine_line|#define FREQ_IF         171200 /* 10.7*16000   */
DECL|macro|FREQ_STEP
mdefine_line|#define FREQ_STEP       200    /* 12.5*16      */
DECL|macro|FREQ2BITS
mdefine_line|#define FREQ2BITS(x)&t;((( (unsigned int)(x)+FREQ_IF+(FREQ_STEP&lt;&lt;1))&bslash;&n;&t;&t;&t;/(FREQ_STEP&lt;&lt;2))&lt;&lt;2) /* (x==fmhz*16*1000) -&gt; bits */
DECL|macro|BITS2FREQ
mdefine_line|#define BITS2FREQ(x)&t;((x) * FREQ_STEP - FREQ_IF)
r_static
r_int
id|radio_ioctl
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
DECL|variable|maxiradio_fops
r_static
r_struct
id|file_operations
id|maxiradio_fops
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
id|radio_ioctl
comma
dot
id|llseek
op_assign
id|no_llseek
comma
)brace
suffix:semicolon
DECL|variable|maxiradio_radio
r_static
r_struct
id|video_device
id|maxiradio_radio
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
l_string|&quot;Maxi Radio FM2000 radio&quot;
comma
dot
id|type
op_assign
id|VID_TYPE_TUNER
comma
dot
id|hardware
op_assign
id|VID_HARDWARE_SF16MI
comma
dot
id|fops
op_assign
op_amp
id|maxiradio_fops
comma
)brace
suffix:semicolon
DECL|struct|radio_device
r_static
r_struct
id|radio_device
(brace
DECL|member|io
id|__u16
id|io
comma
multiline_comment|/* base of radio io */
DECL|member|muted
id|muted
comma
multiline_comment|/* VIDEO_AUDIO_MUTE */
DECL|member|stereo
id|stereo
comma
multiline_comment|/* VIDEO_TUNER_STEREO_ON */
DECL|member|tuned
id|tuned
suffix:semicolon
multiline_comment|/* signal strength (0 or 0xffff) */
DECL|member|freq
r_int
r_int
id|freq
suffix:semicolon
DECL|member|lock
r_struct
id|semaphore
id|lock
suffix:semicolon
DECL|variable|radio_unit
)brace
id|radio_unit
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
)brace
suffix:semicolon
DECL|function|sleep_125ms
r_static
r_void
id|sleep_125ms
c_func
(paren
r_void
)paren
(brace
id|current-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
suffix:semicolon
id|schedule_timeout
c_func
(paren
id|HZ
op_rshift
l_int|3
)paren
suffix:semicolon
)brace
DECL|function|outbit
r_static
r_void
id|outbit
c_func
(paren
r_int
r_int
id|bit
comma
id|__u16
id|io
)paren
(brace
r_if
c_cond
(paren
id|bit
op_ne
l_int|0
)paren
(brace
id|outb
c_func
(paren
id|power
op_or
id|wren
op_or
id|data
comma
id|io
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|4
)paren
suffix:semicolon
id|outb
c_func
(paren
id|power
op_or
id|wren
op_or
id|data
op_or
id|clk
comma
id|io
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|4
)paren
suffix:semicolon
id|outb
c_func
(paren
id|power
op_or
id|wren
op_or
id|data
comma
id|io
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|4
)paren
suffix:semicolon
)brace
r_else
(brace
id|outb
c_func
(paren
id|power
op_or
id|wren
comma
id|io
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|4
)paren
suffix:semicolon
id|outb
c_func
(paren
id|power
op_or
id|wren
op_or
id|clk
comma
id|io
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|4
)paren
suffix:semicolon
id|outb
c_func
(paren
id|power
op_or
id|wren
comma
id|io
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|4
)paren
suffix:semicolon
)brace
)brace
DECL|function|turn_power
r_static
r_void
id|turn_power
c_func
(paren
id|__u16
id|io
comma
r_int
id|p
)paren
(brace
r_if
c_cond
(paren
id|p
op_ne
l_int|0
)paren
(brace
id|outb
c_func
(paren
id|power
comma
id|io
)paren
suffix:semicolon
)brace
r_else
id|outb
c_func
(paren
l_int|0
comma
id|io
)paren
suffix:semicolon
)brace
DECL|function|set_freq
r_static
r_void
id|set_freq
c_func
(paren
id|__u16
id|io
comma
id|__u32
id|data
)paren
(brace
r_int
r_int
r_int
id|si
suffix:semicolon
r_int
id|bl
suffix:semicolon
multiline_comment|/* TEA5757 shift register bits (see pdf) */
id|outbit
c_func
(paren
l_int|0
comma
id|io
)paren
suffix:semicolon
singleline_comment|// 24  search 
id|outbit
c_func
(paren
l_int|1
comma
id|io
)paren
suffix:semicolon
singleline_comment|// 23  search up/down
id|outbit
c_func
(paren
l_int|0
comma
id|io
)paren
suffix:semicolon
singleline_comment|// 22  stereo/mono
id|outbit
c_func
(paren
l_int|0
comma
id|io
)paren
suffix:semicolon
singleline_comment|// 21  band
id|outbit
c_func
(paren
l_int|0
comma
id|io
)paren
suffix:semicolon
singleline_comment|// 20  band (only 00=FM works I think)
id|outbit
c_func
(paren
l_int|0
comma
id|io
)paren
suffix:semicolon
singleline_comment|// 19  port ?
id|outbit
c_func
(paren
l_int|0
comma
id|io
)paren
suffix:semicolon
singleline_comment|// 18  port ?
id|outbit
c_func
(paren
l_int|0
comma
id|io
)paren
suffix:semicolon
singleline_comment|// 17  search level
id|outbit
c_func
(paren
l_int|0
comma
id|io
)paren
suffix:semicolon
singleline_comment|// 16  search level
id|si
op_assign
l_int|0x8000
suffix:semicolon
r_for
c_loop
(paren
id|bl
op_assign
l_int|1
suffix:semicolon
id|bl
op_le
l_int|16
suffix:semicolon
id|bl
op_increment
)paren
(brace
id|outbit
c_func
(paren
id|data
op_amp
id|si
comma
id|io
)paren
suffix:semicolon
id|si
op_rshift_assign
l_int|1
suffix:semicolon
)brace
id|outb
c_func
(paren
id|power
comma
id|io
)paren
suffix:semicolon
)brace
DECL|function|get_stereo
r_static
r_int
id|get_stereo
c_func
(paren
id|__u16
id|io
)paren
(brace
id|outb
c_func
(paren
id|power
comma
id|io
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|4
)paren
suffix:semicolon
r_return
op_logical_neg
(paren
id|inb
c_func
(paren
id|io
)paren
op_amp
id|mo_st
)paren
suffix:semicolon
)brace
DECL|function|get_tune
r_static
r_int
id|get_tune
c_func
(paren
id|__u16
id|io
)paren
(brace
id|outb
c_func
(paren
id|power
op_plus
id|clk
comma
id|io
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|4
)paren
suffix:semicolon
r_return
op_logical_neg
(paren
id|inb
c_func
(paren
id|io
)paren
op_amp
id|mo_st
)paren
suffix:semicolon
)brace
DECL|function|radio_function
r_inline
r_static
r_int
id|radio_function
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
id|radio_device
op_star
id|card
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
id|strcpy
c_func
(paren
id|v-&gt;name
comma
l_string|&quot;Maxi Radio FM2000 radio&quot;
)paren
suffix:semicolon
id|v-&gt;type
op_assign
id|VID_TYPE_TUNER
suffix:semicolon
id|v-&gt;channels
op_assign
id|v-&gt;audios
op_assign
l_int|1
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
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|card-&gt;stereo
op_assign
l_int|0xffff
op_star
id|get_stereo
c_func
(paren
id|card-&gt;io
)paren
suffix:semicolon
id|card-&gt;tuned
op_assign
l_int|0xffff
op_star
id|get_tune
c_func
(paren
id|card-&gt;io
)paren
suffix:semicolon
id|v-&gt;flags
op_assign
id|VIDEO_TUNER_LOW
op_or
id|card-&gt;stereo
suffix:semicolon
id|v-&gt;signal
op_assign
id|card-&gt;tuned
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
id|FREQ_LO
suffix:semicolon
id|v-&gt;rangehigh
op_assign
id|FREQ_HI
suffix:semicolon
id|v-&gt;mode
op_assign
id|VIDEO_MODE_AUTO
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
id|card-&gt;freq
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
r_if
c_cond
(paren
op_star
id|freq
template_param
id|FREQ_HI
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|card-&gt;freq
op_assign
op_star
id|freq
suffix:semicolon
id|set_freq
c_func
(paren
id|card-&gt;io
comma
id|FREQ2BITS
c_func
(paren
id|card-&gt;freq
)paren
)paren
suffix:semicolon
id|sleep_125ms
c_func
(paren
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
id|strcpy
c_func
(paren
id|v-&gt;name
comma
l_string|&quot;Radio&quot;
)paren
suffix:semicolon
id|v-&gt;flags
op_assign
id|VIDEO_AUDIO_MUTABLE
op_or
id|card-&gt;muted
suffix:semicolon
id|v-&gt;mode
op_assign
id|VIDEO_SOUND_STEREO
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
id|card-&gt;muted
op_assign
id|v-&gt;flags
op_amp
id|VIDEO_AUDIO_MUTE
suffix:semicolon
r_if
c_cond
(paren
id|card-&gt;muted
)paren
(brace
id|turn_power
c_func
(paren
id|card-&gt;io
comma
l_int|0
)paren
suffix:semicolon
)brace
r_else
id|set_freq
c_func
(paren
id|card-&gt;io
comma
id|FREQ2BITS
c_func
(paren
id|card-&gt;freq
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|VIDIOCGUNIT
suffix:colon
(brace
r_struct
id|video_unit
op_star
id|v
op_assign
id|arg
suffix:semicolon
id|v-&gt;video
op_assign
id|VIDEO_NO_UNIT
suffix:semicolon
id|v-&gt;vbi
op_assign
id|VIDEO_NO_UNIT
suffix:semicolon
id|v-&gt;radio
op_assign
id|dev-&gt;minor
suffix:semicolon
id|v-&gt;audio
op_assign
l_int|0
suffix:semicolon
id|v-&gt;teletext
op_assign
id|VIDEO_NO_UNIT
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
DECL|function|radio_ioctl
r_static
r_int
id|radio_ioctl
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
id|radio_device
op_star
id|card
op_assign
id|dev-&gt;priv
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|down
c_func
(paren
op_amp
id|card-&gt;lock
)paren
suffix:semicolon
id|ret
op_assign
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
id|radio_function
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|card-&gt;lock
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Dimitromanolakis Apostolos, apdim@grecian.net&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Radio driver for the Guillemot Maxi Radio FM2000 radio.&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|function|maxiradio_init_one
r_static
r_int
id|__devinit
id|maxiradio_init_one
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
r_const
r_struct
id|pci_device_id
op_star
id|ent
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|pci_resource_start
c_func
(paren
id|pdev
comma
l_int|0
)paren
comma
id|pci_resource_len
c_func
(paren
id|pdev
comma
l_int|0
)paren
comma
l_string|&quot;Maxi Radio FM 2000&quot;
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;radio-maxiradio: can&squot;t reserve I/O ports&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|err_out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pci_enable_device
c_func
(paren
id|pdev
)paren
)paren
r_goto
id|err_out_free_region
suffix:semicolon
id|radio_unit.io
op_assign
id|pci_resource_start
c_func
(paren
id|pdev
comma
l_int|0
)paren
suffix:semicolon
id|init_MUTEX
c_func
(paren
op_amp
id|radio_unit.lock
)paren
suffix:semicolon
id|maxiradio_radio.priv
op_assign
op_amp
id|radio_unit
suffix:semicolon
r_if
c_cond
(paren
id|video_register_device
c_func
(paren
op_amp
id|maxiradio_radio
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
id|printk
c_func
(paren
l_string|&quot;radio-maxiradio: can&squot;t register device!&quot;
)paren
suffix:semicolon
r_goto
id|err_out_free_region
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;radio-maxiradio: version &quot;
id|DRIVER_VERSION
l_string|&quot; time &quot;
id|__TIME__
l_string|&quot;  &quot;
id|__DATE__
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;radio-maxiradio: found Guillemot MAXI Radio device (io = 0x%x)&bslash;n&quot;
comma
id|radio_unit.io
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|err_out_free_region
suffix:colon
id|release_region
c_func
(paren
id|pci_resource_start
c_func
(paren
id|pdev
comma
l_int|0
)paren
comma
id|pci_resource_len
c_func
(paren
id|pdev
comma
l_int|0
)paren
)paren
suffix:semicolon
id|err_out
suffix:colon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|maxiradio_remove_one
r_static
r_void
id|__devexit
id|maxiradio_remove_one
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
)paren
(brace
id|video_unregister_device
c_func
(paren
op_amp
id|maxiradio_radio
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|pci_resource_start
c_func
(paren
id|pdev
comma
l_int|0
)paren
comma
id|pci_resource_len
c_func
(paren
id|pdev
comma
l_int|0
)paren
)paren
suffix:semicolon
)brace
DECL|variable|maxiradio_pci_tbl
r_static
r_struct
id|pci_device_id
id|maxiradio_pci_tbl
(braket
)braket
op_assign
(brace
(brace
id|PCI_VENDOR_ID_GUILLEMOT
comma
id|PCI_DEVICE_ID_GUILLEMOT_MAXIRADIO
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
)brace
comma
(brace
l_int|0
comma
)brace
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
c_func
(paren
id|pci
comma
id|maxiradio_pci_tbl
)paren
suffix:semicolon
DECL|variable|maxiradio_driver
r_static
r_struct
id|pci_driver
id|maxiradio_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;radio-maxiradio&quot;
comma
dot
id|id_table
op_assign
id|maxiradio_pci_tbl
comma
dot
id|probe
op_assign
id|maxiradio_init_one
comma
dot
id|remove
op_assign
id|__devexit_p
c_func
(paren
id|maxiradio_remove_one
)paren
comma
)brace
suffix:semicolon
DECL|function|maxiradio_radio_init
r_int
id|__init
id|maxiradio_radio_init
c_func
(paren
r_void
)paren
(brace
r_return
id|pci_module_init
c_func
(paren
op_amp
id|maxiradio_driver
)paren
suffix:semicolon
)brace
DECL|function|maxiradio_radio_exit
r_void
id|__exit
id|maxiradio_radio_exit
c_func
(paren
r_void
)paren
(brace
id|pci_unregister_driver
c_func
(paren
op_amp
id|maxiradio_driver
)paren
suffix:semicolon
)brace
DECL|variable|maxiradio_radio_init
id|module_init
c_func
(paren
id|maxiradio_radio_init
)paren
suffix:semicolon
DECL|variable|maxiradio_radio_exit
id|module_exit
c_func
(paren
id|maxiradio_radio_exit
)paren
suffix:semicolon
eof
