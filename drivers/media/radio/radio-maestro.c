multiline_comment|/* Maestro PCI sound card radio driver for Linux support&n; * (c) 2000 A. Tlalka, atlka@pg.gda.pl&n; * Notes on the hardware&n; *&n; *  + Frequency control is done digitally &n; *  + No volume control - only mute/unmute - you have to use Aux line volume&n; *  control on Maestro card to set the volume&n; *  + Radio status (tuned/not_tuned and stereo/mono) is valid some time after&n; *  frequency setting (&gt;100ms) and only when the radio is unmuted.&n; *  version 0.02&n; *  + io port is automatically detected - only the first radio is used&n; *  version 0.03&n; *  + thread access locking additions&n; *  version 0.04&n; * + code improvements&n; * + VIDEO_TUNER_LOW is permanent&n; */
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
DECL|macro|DRIVER_VERSION
mdefine_line|#define DRIVER_VERSION&t;&quot;0.04&quot;
DECL|macro|PCI_VENDOR_ESS
mdefine_line|#define PCI_VENDOR_ESS                  0x125D
DECL|macro|PCI_DEVICE_ID_ESS_ESS1968
mdefine_line|#define PCI_DEVICE_ID_ESS_ESS1968       0x1968          /* Maestro 2    */
DECL|macro|PCI_DEVICE_ID_ESS_ESS1978
mdefine_line|#define PCI_DEVICE_ID_ESS_ESS1978       0x1978          /* Maestro 2E   */
DECL|macro|GPIO_DATA
mdefine_line|#define GPIO_DATA       0x60   /* port offset from ESS_IO_BASE */
DECL|macro|IO_MASK
mdefine_line|#define IO_MASK&t;&t;4      /* mask      register offset from GPIO_DATA&n;&t;&t;&t;&t;bits 1=unmask write to given bit */
DECL|macro|IO_DIR
mdefine_line|#define IO_DIR&t;&t;8      /* direction register offset from GPIO_DATA&n;&t;&t;&t;&t;bits 0/1=read/write direction */
DECL|macro|GPIO6
mdefine_line|#define GPIO6           0x0040 /* mask bits for GPIO lines */
DECL|macro|GPIO7
mdefine_line|#define GPIO7           0x0080
DECL|macro|GPIO8
mdefine_line|#define GPIO8           0x0100
DECL|macro|GPIO9
mdefine_line|#define GPIO9           0x0200
DECL|macro|STR_DATA
mdefine_line|#define STR_DATA        GPIO6  /* radio TEA5757 pins and GPIO bits */
DECL|macro|STR_CLK
mdefine_line|#define STR_CLK         GPIO7
DECL|macro|STR_WREN
mdefine_line|#define STR_WREN        GPIO8
DECL|macro|STR_MOST
mdefine_line|#define STR_MOST        GPIO9
DECL|macro|FREQ_LO
mdefine_line|#define FREQ_LO&t;&t; 50*16000
DECL|macro|FREQ_HI
mdefine_line|#define FREQ_HI&t;&t;150*16000
DECL|macro|FREQ_IF
mdefine_line|#define FREQ_IF         171200 /* 10.7*16000   */
DECL|macro|FREQ_STEP
mdefine_line|#define FREQ_STEP       200    /* 12.5*16      */
DECL|macro|FREQ2BITS
mdefine_line|#define FREQ2BITS(x)&t;((((unsigned int)(x)+FREQ_IF+(FREQ_STEP&lt;&lt;1))&bslash;&n;&t;&t;&t;/(FREQ_STEP&lt;&lt;2))&lt;&lt;2) /* (x==fmhz*16*1000) -&gt; bits */
DECL|macro|BITS2FREQ
mdefine_line|#define BITS2FREQ(x)&t;((x) * FREQ_STEP - FREQ_IF)
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
r_static
r_int
id|radio_open
c_func
(paren
r_struct
id|video_device
op_star
comma
r_int
)paren
suffix:semicolon
r_static
r_int
id|radio_ioctl
c_func
(paren
r_struct
id|video_device
op_star
comma
r_int
r_int
comma
r_void
op_star
)paren
suffix:semicolon
r_static
r_void
id|radio_close
c_func
(paren
r_struct
id|video_device
op_star
)paren
suffix:semicolon
DECL|variable|maestro_radio
r_static
r_struct
id|video_device
id|maestro_radio
op_assign
(brace
id|owner
suffix:colon
id|THIS_MODULE
comma
id|name
suffix:colon
l_string|&quot;Maestro radio&quot;
comma
id|type
suffix:colon
id|VID_TYPE_TUNER
comma
id|hardware
suffix:colon
id|VID_HARDWARE_SF16MI
comma
id|open
suffix:colon
id|radio_open
comma
id|close
suffix:colon
id|radio_close
comma
id|ioctl
suffix:colon
id|radio_ioctl
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
multiline_comment|/* base of Maestro card radio io (GPIO_DATA)*/
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
DECL|variable|users
r_static
r_int
id|users
op_assign
l_int|0
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
DECL|function|udelay2
r_static
r_void
id|udelay2
c_func
(paren
r_void
)paren
(brace
id|udelay
c_func
(paren
l_int|2
)paren
suffix:semicolon
)brace
DECL|function|udelay4
r_static
r_void
id|udelay4
c_func
(paren
r_void
)paren
(brace
id|udelay
c_func
(paren
l_int|4
)paren
suffix:semicolon
)brace
DECL|function|udelay16
r_static
r_void
id|udelay16
c_func
(paren
r_void
)paren
(brace
id|udelay
c_func
(paren
l_int|16
)paren
suffix:semicolon
)brace
DECL|function|radio_bits_get
r_static
id|__u32
id|radio_bits_get
c_func
(paren
r_struct
id|radio_device
op_star
id|dev
)paren
(brace
r_register
id|__u16
id|io
op_assign
id|dev-&gt;io
comma
id|l
comma
id|rdata
suffix:semicolon
r_register
id|__u32
id|data
op_assign
l_int|0
suffix:semicolon
id|__u16
id|omask
suffix:semicolon
id|omask
op_assign
id|inw
c_func
(paren
id|io
op_plus
id|IO_MASK
)paren
suffix:semicolon
id|outw
c_func
(paren
op_complement
(paren
id|STR_CLK
op_or
id|STR_WREN
)paren
comma
id|io
op_plus
id|IO_MASK
)paren
suffix:semicolon
id|outw
c_func
(paren
l_int|0
comma
id|io
)paren
suffix:semicolon
id|udelay16
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|l
op_assign
l_int|24
suffix:semicolon
id|l
op_decrement
suffix:semicolon
)paren
(brace
id|outw
c_func
(paren
id|STR_CLK
comma
id|io
)paren
suffix:semicolon
multiline_comment|/* HI state */
id|udelay2
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|l
)paren
(brace
id|dev-&gt;tuned
op_assign
id|inw
c_func
(paren
id|io
)paren
op_amp
id|STR_MOST
ques
c_cond
l_int|0
suffix:colon
l_int|0xffff
suffix:semicolon
)brace
id|outw
c_func
(paren
l_int|0
comma
id|io
)paren
suffix:semicolon
multiline_comment|/* LO state */
id|udelay2
c_func
(paren
)paren
suffix:semicolon
id|data
op_lshift_assign
l_int|1
suffix:semicolon
multiline_comment|/* shift data */
id|rdata
op_assign
id|inw
c_func
(paren
id|io
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|l
)paren
(brace
id|dev-&gt;stereo
op_assign
id|rdata
op_amp
id|STR_MOST
ques
c_cond
l_int|0
suffix:colon
id|VIDEO_TUNER_STEREO_ON
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|rdata
op_amp
id|STR_DATA
)paren
(brace
id|data
op_increment
suffix:semicolon
)brace
id|udelay2
c_func
(paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dev-&gt;muted
)paren
(brace
id|outw
c_func
(paren
id|STR_WREN
comma
id|io
)paren
suffix:semicolon
)brace
id|udelay4
c_func
(paren
)paren
suffix:semicolon
id|outw
c_func
(paren
id|omask
comma
id|io
op_plus
id|IO_MASK
)paren
suffix:semicolon
r_return
id|data
op_amp
l_int|0x3ffe
suffix:semicolon
)brace
DECL|function|radio_bits_set
r_static
r_void
id|radio_bits_set
c_func
(paren
r_struct
id|radio_device
op_star
id|dev
comma
id|__u32
id|data
)paren
(brace
r_register
id|__u16
id|io
op_assign
id|dev-&gt;io
comma
id|l
comma
id|bits
suffix:semicolon
id|__u16
id|omask
comma
id|odir
suffix:semicolon
id|omask
op_assign
id|inw
c_func
(paren
id|io
op_plus
id|IO_MASK
)paren
suffix:semicolon
id|odir
op_assign
(paren
id|inw
c_func
(paren
id|io
op_plus
id|IO_DIR
)paren
op_amp
op_complement
id|STR_DATA
)paren
op_or
(paren
id|STR_CLK
op_or
id|STR_WREN
)paren
suffix:semicolon
id|outw
c_func
(paren
id|odir
op_or
id|STR_DATA
comma
id|io
op_plus
id|IO_DIR
)paren
suffix:semicolon
id|outw
c_func
(paren
op_complement
(paren
id|STR_DATA
op_or
id|STR_CLK
op_or
id|STR_WREN
)paren
comma
id|io
op_plus
id|IO_MASK
)paren
suffix:semicolon
id|udelay16
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|l
op_assign
l_int|25
suffix:semicolon
id|l
suffix:semicolon
id|l
op_decrement
)paren
(brace
id|bits
op_assign
(paren
(paren
id|data
op_rshift
l_int|18
)paren
op_amp
id|STR_DATA
)paren
op_or
id|STR_WREN
suffix:semicolon
id|data
op_lshift_assign
l_int|1
suffix:semicolon
multiline_comment|/* shift data */
id|outw
c_func
(paren
id|bits
comma
id|io
)paren
suffix:semicolon
multiline_comment|/* start strobe */
id|udelay2
c_func
(paren
)paren
suffix:semicolon
id|outw
c_func
(paren
id|bits
op_or
id|STR_CLK
comma
id|io
)paren
suffix:semicolon
multiline_comment|/* HI level */
id|udelay2
c_func
(paren
)paren
suffix:semicolon
id|outw
c_func
(paren
id|bits
comma
id|io
)paren
suffix:semicolon
multiline_comment|/* LO level */
id|udelay4
c_func
(paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;muted
)paren
(brace
id|outw
c_func
(paren
l_int|0
comma
id|io
)paren
suffix:semicolon
)brace
id|udelay4
c_func
(paren
)paren
suffix:semicolon
id|outw
c_func
(paren
id|omask
comma
id|io
op_plus
id|IO_MASK
)paren
suffix:semicolon
id|outw
c_func
(paren
id|odir
comma
id|io
op_plus
id|IO_DIR
)paren
suffix:semicolon
id|sleep_125ms
c_func
(paren
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
id|v
suffix:semicolon
id|strcpy
c_func
(paren
id|v.name
comma
l_string|&quot;Maestro radio&quot;
)paren
suffix:semicolon
id|v.type
op_assign
id|VID_TYPE_TUNER
suffix:semicolon
id|v.channels
op_assign
id|v.audios
op_assign
l_int|1
suffix:semicolon
id|v.maxwidth
op_assign
id|v.maxheight
op_assign
id|v.minwidth
op_assign
id|v.minheight
op_assign
l_int|0
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
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
(paren
r_void
)paren
id|radio_bits_get
c_func
(paren
id|card
)paren
suffix:semicolon
id|v.flags
op_assign
id|VIDEO_TUNER_LOW
op_or
id|card-&gt;stereo
suffix:semicolon
id|v.signal
op_assign
id|card-&gt;tuned
suffix:semicolon
id|strcpy
c_func
(paren
id|v.name
comma
l_string|&quot;FM&quot;
)paren
suffix:semicolon
id|v.rangelow
op_assign
id|FREQ_LO
suffix:semicolon
id|v.rangehigh
op_assign
id|FREQ_HI
suffix:semicolon
id|v.mode
op_assign
id|VIDEO_MODE_AUTO
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
id|tmp
op_assign
id|BITS2FREQ
c_func
(paren
id|radio_bits_get
c_func
(paren
id|card
)paren
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
id|tmp
comma
r_sizeof
(paren
id|tmp
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
id|VIDIOCSFREQ
suffix:colon
(brace
r_int
r_int
id|tmp
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|tmp
comma
id|arg
comma
r_sizeof
(paren
id|tmp
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
id|tmp
id|FREQ_HI
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|radio_bits_set
c_func
(paren
id|card
comma
id|FREQ2BITS
c_func
(paren
id|tmp
)paren
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
id|v
suffix:semicolon
id|strcpy
c_func
(paren
id|v.name
comma
l_string|&quot;Radio&quot;
)paren
suffix:semicolon
id|v.audio
op_assign
id|v.volume
op_assign
id|v.bass
op_assign
id|v.treble
op_assign
id|v.balance
op_assign
id|v.step
op_assign
l_int|0
suffix:semicolon
id|v.flags
op_assign
id|VIDEO_AUDIO_MUTABLE
op_or
id|card-&gt;muted
suffix:semicolon
id|v.mode
op_assign
id|VIDEO_SOUND_STEREO
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
(brace
r_register
id|__u16
id|io
op_assign
id|card-&gt;io
suffix:semicolon
r_register
id|__u16
id|omask
op_assign
id|inw
c_func
(paren
id|io
op_plus
id|IO_MASK
)paren
suffix:semicolon
id|outw
c_func
(paren
op_complement
id|STR_WREN
comma
id|io
op_plus
id|IO_MASK
)paren
suffix:semicolon
id|outw
c_func
(paren
(paren
id|card-&gt;muted
op_assign
id|v.flags
op_amp
id|VIDEO_AUDIO_MUTE
)paren
ques
c_cond
id|STR_WREN
suffix:colon
l_int|0
comma
id|io
)paren
suffix:semicolon
id|udelay4
c_func
(paren
)paren
suffix:semicolon
id|outw
c_func
(paren
id|omask
comma
id|io
op_plus
id|IO_MASK
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
)brace
r_case
id|VIDIOCGUNIT
suffix:colon
(brace
r_struct
id|video_unit
id|v
suffix:semicolon
id|v.video
op_assign
id|VIDEO_NO_UNIT
suffix:semicolon
id|v.vbi
op_assign
id|VIDEO_NO_UNIT
suffix:semicolon
id|v.radio
op_assign
id|dev-&gt;minor
suffix:semicolon
id|v.audio
op_assign
l_int|0
suffix:semicolon
id|v.teletext
op_assign
id|VIDEO_NO_UNIT
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
id|radio_function
c_func
(paren
id|dev
comma
id|cmd
comma
id|arg
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
DECL|function|radio_open
r_static
r_int
id|radio_open
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
DECL|function|radio_close
r_static
r_void
id|radio_close
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
r_inline
r_static
id|__u16
id|radio_install
c_func
(paren
r_struct
id|pci_dev
op_star
id|pcidev
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Adam Tlalka, atlka@pg.gda.pl&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Radio driver for the Maestro PCI sound card radio.&quot;
)paren
suffix:semicolon
id|EXPORT_NO_SYMBOLS
suffix:semicolon
DECL|function|maestro_radio_exit
r_void
id|__exit
id|maestro_radio_exit
c_func
(paren
r_void
)paren
(brace
id|video_unregister_device
c_func
(paren
op_amp
id|maestro_radio
)paren
suffix:semicolon
)brace
DECL|function|maestro_radio_init
r_int
id|__init
id|maestro_radio_init
c_func
(paren
r_void
)paren
(brace
r_register
id|__u16
id|found
op_assign
l_int|0
suffix:semicolon
r_struct
id|pci_dev
op_star
id|pcidev
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pci_present
c_func
(paren
)paren
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_while
c_loop
(paren
op_logical_neg
id|found
op_logical_and
(paren
id|pcidev
op_assign
id|pci_find_device
c_func
(paren
id|PCI_VENDOR_ESS
comma
id|PCI_DEVICE_ID_ESS_ESS1968
comma
id|pcidev
)paren
)paren
)paren
(brace
id|found
op_or_assign
id|radio_install
c_func
(paren
id|pcidev
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
op_logical_neg
id|found
op_logical_and
(paren
id|pcidev
op_assign
id|pci_find_device
c_func
(paren
id|PCI_VENDOR_ESS
comma
id|PCI_DEVICE_ID_ESS_ESS1978
comma
id|pcidev
)paren
)paren
)paren
(brace
id|found
op_or_assign
id|radio_install
c_func
(paren
id|pcidev
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|found
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;radio-maestro: no devices found.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|maestro_radio_init
id|module_init
c_func
(paren
id|maestro_radio_init
)paren
suffix:semicolon
DECL|variable|maestro_radio_exit
id|module_exit
c_func
(paren
id|maestro_radio_exit
)paren
suffix:semicolon
DECL|function|radio_power_on
r_inline
r_static
id|__u16
id|radio_power_on
c_func
(paren
r_struct
id|radio_device
op_star
id|dev
)paren
(brace
r_register
id|__u16
id|io
op_assign
id|dev-&gt;io
suffix:semicolon
r_register
id|__u32
id|ofreq
suffix:semicolon
id|__u16
id|omask
comma
id|odir
suffix:semicolon
id|omask
op_assign
id|inw
c_func
(paren
id|io
op_plus
id|IO_MASK
)paren
suffix:semicolon
id|odir
op_assign
(paren
id|inw
c_func
(paren
id|io
op_plus
id|IO_DIR
)paren
op_amp
op_complement
id|STR_DATA
)paren
op_or
(paren
id|STR_CLK
op_or
id|STR_WREN
)paren
suffix:semicolon
id|outw
c_func
(paren
id|odir
op_amp
op_complement
id|STR_WREN
comma
id|io
op_plus
id|IO_DIR
)paren
suffix:semicolon
id|dev-&gt;muted
op_assign
id|inw
c_func
(paren
id|io
)paren
op_amp
id|STR_WREN
ques
c_cond
l_int|0
suffix:colon
id|VIDEO_AUDIO_MUTE
suffix:semicolon
id|outw
c_func
(paren
id|odir
comma
id|io
op_plus
id|IO_DIR
)paren
suffix:semicolon
id|outw
c_func
(paren
op_complement
(paren
id|STR_WREN
op_or
id|STR_CLK
)paren
comma
id|io
op_plus
id|IO_MASK
)paren
suffix:semicolon
id|outw
c_func
(paren
id|dev-&gt;muted
ques
c_cond
l_int|0
suffix:colon
id|STR_WREN
comma
id|io
)paren
suffix:semicolon
id|udelay16
c_func
(paren
)paren
suffix:semicolon
id|outw
c_func
(paren
id|omask
comma
id|io
op_plus
id|IO_MASK
)paren
suffix:semicolon
id|ofreq
op_assign
id|radio_bits_get
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ofreq
OL
id|FREQ2BITS
c_func
(paren
id|FREQ_LO
)paren
)paren
op_logical_or
(paren
id|ofreq
OG
id|FREQ2BITS
c_func
(paren
id|FREQ_HI
)paren
)paren
)paren
(brace
id|ofreq
op_assign
id|FREQ2BITS
c_func
(paren
id|FREQ_LO
)paren
suffix:semicolon
)brace
id|radio_bits_set
c_func
(paren
id|dev
comma
id|ofreq
)paren
suffix:semicolon
r_return
(paren
id|ofreq
op_eq
id|radio_bits_get
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
)brace
DECL|function|radio_install
r_inline
r_static
id|__u16
id|radio_install
c_func
(paren
r_struct
id|pci_dev
op_star
id|pcidev
)paren
(brace
r_if
c_cond
(paren
(paren
(paren
id|pcidev
op_member_access_from_pointer
r_class
op_rshift
l_int|8
)paren
op_amp
l_int|0xffff
)paren
op_ne
id|PCI_CLASS_MULTIMEDIA_AUDIO
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
id|radio_unit.io
op_assign
id|pcidev-&gt;resource
(braket
l_int|0
)braket
dot
id|start
op_plus
id|GPIO_DATA
suffix:semicolon
id|maestro_radio.priv
op_assign
op_amp
id|radio_unit
suffix:semicolon
id|init_MUTEX
c_func
(paren
op_amp
id|radio_unit.lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|radio_power_on
c_func
(paren
op_amp
id|radio_unit
)paren
)paren
(brace
r_if
c_cond
(paren
id|video_register_device
c_func
(paren
op_amp
id|maestro_radio
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
l_string|&quot;radio-maestro: can&squot;t register device!&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;radio-maestro: version &quot;
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
l_string|&quot;radio-maestro: radio chip initialized&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_else
r_return
l_int|0
suffix:semicolon
)brace
eof
