macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/videodev.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;media/id.h&gt;
macro_line|#include &lt;media/saa6752hs.h&gt;
multiline_comment|/* Addresses to scan */
DECL|variable|normal_i2c
r_static
r_int
r_int
id|normal_i2c
(braket
)braket
op_assign
(brace
l_int|0x20
comma
id|I2C_CLIENT_END
)brace
suffix:semicolon
DECL|variable|normal_i2c_range
r_static
r_int
r_int
id|normal_i2c_range
(braket
)braket
op_assign
(brace
id|I2C_CLIENT_END
)brace
suffix:semicolon
id|I2C_CLIENT_INSMOD
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;device driver for saa6752hs MPEG2 encoder&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Andrew de Quincey&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|driver
r_static
r_struct
id|i2c_driver
id|driver
suffix:semicolon
DECL|variable|client_template
r_static
r_struct
id|i2c_client
id|client_template
suffix:semicolon
DECL|enum|saa6752hs_command
r_enum
id|saa6752hs_command
(brace
DECL|enumerator|SAA6752HS_COMMAND_RESET
id|SAA6752HS_COMMAND_RESET
op_assign
l_int|0
comma
DECL|enumerator|SAA6752HS_COMMAND_STOP
id|SAA6752HS_COMMAND_STOP
op_assign
l_int|1
comma
DECL|enumerator|SAA6752HS_COMMAND_START
id|SAA6752HS_COMMAND_START
op_assign
l_int|2
comma
DECL|enumerator|SAA6752HS_COMMAND_PAUSE
id|SAA6752HS_COMMAND_PAUSE
op_assign
l_int|3
comma
DECL|enumerator|SAA6752HS_COMMAND_RECONFIGURE
id|SAA6752HS_COMMAND_RECONFIGURE
op_assign
l_int|4
comma
DECL|enumerator|SAA6752HS_COMMAND_SLEEP
id|SAA6752HS_COMMAND_SLEEP
op_assign
l_int|5
comma
DECL|enumerator|SAA6752HS_COMMAND_RECONFIGURE_FORCE
id|SAA6752HS_COMMAND_RECONFIGURE_FORCE
op_assign
l_int|6
comma
DECL|enumerator|SAA6752HS_COMMAND_MAX
id|SAA6752HS_COMMAND_MAX
)brace
suffix:semicolon
multiline_comment|/* ---------------------------------------------------------------------- */
DECL|variable|PAT
r_static
id|u8
id|PAT
(braket
)braket
op_assign
(brace
l_int|0xc2
comma
singleline_comment|// i2c register
l_int|0x00
comma
singleline_comment|// table number for encoder
l_int|0x47
comma
singleline_comment|// sync
l_int|0x40
comma
l_int|0x00
comma
singleline_comment|// transport_error_indicator(0), payload_unit_start(1), transport_priority(0), pid(0)
l_int|0x10
comma
singleline_comment|// transport_scrambling_control(00), adaptation_field_control(01), continuity_counter(0)
l_int|0x00
comma
singleline_comment|// PSI pointer to start of table
l_int|0x00
comma
singleline_comment|// tid(0)
l_int|0xb0
comma
l_int|0x0d
comma
singleline_comment|// section_syntax_indicator(1), section_length(13)
l_int|0x00
comma
l_int|0x01
comma
singleline_comment|// transport_stream_id(1)
l_int|0xc1
comma
singleline_comment|// version_number(0), current_next_indicator(1)
l_int|0x00
comma
l_int|0x00
comma
singleline_comment|// section_number(0), last_section_number(0)
l_int|0x00
comma
l_int|0x01
comma
singleline_comment|// program_number(1)
l_int|0xe0
comma
l_int|0x10
comma
singleline_comment|// PMT PID(0x10)
l_int|0x76
comma
l_int|0xf1
comma
l_int|0x44
comma
l_int|0xd1
singleline_comment|// CRC32
)brace
suffix:semicolon
DECL|variable|PMT
r_static
id|u8
id|PMT
(braket
)braket
op_assign
(brace
l_int|0xc2
comma
singleline_comment|// i2c register
l_int|0x01
comma
singleline_comment|// table number for encoder
l_int|0x47
comma
singleline_comment|// sync
l_int|0x40
comma
l_int|0x10
comma
singleline_comment|// transport_error_indicator(0), payload_unit_start(1), transport_priority(0), pid(0x10)
l_int|0x10
comma
singleline_comment|// transport_scrambling_control(00), adaptation_field_control(01), continuity_counter(0)
l_int|0x00
comma
singleline_comment|// PSI pointer to start of table
l_int|0x02
comma
singleline_comment|// tid(2)
l_int|0xb0
comma
l_int|0x17
comma
singleline_comment|// section_syntax_indicator(1), section_length(23)
l_int|0x00
comma
l_int|0x01
comma
singleline_comment|// program_number(1)
l_int|0xc1
comma
singleline_comment|// version_number(0), current_next_indicator(1)
l_int|0x00
comma
l_int|0x00
comma
singleline_comment|// section_number(0), last_section_number(0)
l_int|0xe1
comma
l_int|0x04
comma
singleline_comment|// PCR_PID (0x104)
l_int|0xf0
comma
l_int|0x00
comma
singleline_comment|// program_info_length(0)
l_int|0x02
comma
l_int|0xe1
comma
l_int|0x00
comma
l_int|0xf0
comma
l_int|0x00
comma
singleline_comment|// video stream type(2), pid(0x100)
l_int|0x04
comma
l_int|0xe1
comma
l_int|0x03
comma
l_int|0xf0
comma
l_int|0x00
comma
singleline_comment|// audio stream type(4), pid(0x103)
l_int|0xa1
comma
l_int|0xca
comma
l_int|0x0f
comma
l_int|0x82
singleline_comment|// CRC32
)brace
suffix:semicolon
DECL|variable|mpeg_params_template
r_static
r_struct
id|mpeg_params
id|mpeg_params_template
op_assign
(brace
dot
id|bitrate_mode
op_assign
id|MPEG_BITRATE_MODE_CBR
comma
dot
id|video_target_bitrate
op_assign
l_int|5000
comma
dot
id|audio_bitrate
op_assign
id|MPEG_AUDIO_BITRATE_256
comma
dot
id|total_bitrate
op_assign
l_int|6000
comma
)brace
suffix:semicolon
multiline_comment|/* ---------------------------------------------------------------------- */
DECL|function|saa6752hs_chip_command
r_static
r_int
id|saa6752hs_chip_command
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
comma
r_enum
id|saa6752hs_command
id|command
)paren
(brace
r_int
r_char
id|buf
(braket
l_int|3
)braket
suffix:semicolon
r_int
r_int
id|timeout
suffix:semicolon
r_int
id|status
op_assign
l_int|0
suffix:semicolon
singleline_comment|// execute the command
r_switch
c_cond
(paren
id|command
)paren
(brace
r_case
id|SAA6752HS_COMMAND_RESET
suffix:colon
id|buf
(braket
l_int|0
)braket
op_assign
l_int|0x00
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SAA6752HS_COMMAND_STOP
suffix:colon
id|buf
(braket
l_int|0
)braket
op_assign
l_int|0x03
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SAA6752HS_COMMAND_START
suffix:colon
id|buf
(braket
l_int|0
)braket
op_assign
l_int|0x02
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SAA6752HS_COMMAND_PAUSE
suffix:colon
id|buf
(braket
l_int|0
)braket
op_assign
l_int|0x04
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SAA6752HS_COMMAND_RECONFIGURE
suffix:colon
id|buf
(braket
l_int|0
)braket
op_assign
l_int|0x05
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SAA6752HS_COMMAND_SLEEP
suffix:colon
id|buf
(braket
l_int|0
)braket
op_assign
l_int|0x06
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SAA6752HS_COMMAND_RECONFIGURE_FORCE
suffix:colon
id|buf
(braket
l_int|0
)braket
op_assign
l_int|0x07
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
singleline_comment|// set it and wait for it to be so
id|i2c_master_send
c_func
(paren
id|client
comma
id|buf
comma
l_int|1
)paren
suffix:semicolon
id|timeout
op_assign
id|jiffies
op_plus
id|HZ
op_star
l_int|3
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
singleline_comment|// get the current status
id|buf
(braket
l_int|0
)braket
op_assign
l_int|0x10
suffix:semicolon
id|i2c_master_send
c_func
(paren
id|client
comma
id|buf
comma
l_int|1
)paren
suffix:semicolon
id|i2c_master_recv
c_func
(paren
id|client
comma
id|buf
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|buf
(braket
l_int|0
)braket
op_amp
l_int|0x20
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|time_after
c_func
(paren
id|jiffies
comma
id|timeout
)paren
)paren
(brace
id|status
op_assign
op_minus
id|ETIMEDOUT
suffix:semicolon
r_break
suffix:semicolon
)brace
singleline_comment|// wait a bit
id|msleep
c_func
(paren
l_int|10
)paren
suffix:semicolon
)brace
singleline_comment|// delay a bit to let encoder settle
id|msleep
c_func
(paren
l_int|50
)paren
suffix:semicolon
singleline_comment|// done
r_return
id|status
suffix:semicolon
)brace
DECL|function|saa6752hs_set_bitrate
r_static
r_int
id|saa6752hs_set_bitrate
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
comma
r_struct
id|mpeg_params
op_star
id|params
)paren
(brace
id|u8
id|buf
(braket
l_int|3
)braket
suffix:semicolon
singleline_comment|// set the bitrate mode
id|buf
(braket
l_int|0
)braket
op_assign
l_int|0x71
suffix:semicolon
id|buf
(braket
l_int|1
)braket
op_assign
id|params-&gt;bitrate_mode
suffix:semicolon
id|i2c_master_send
c_func
(paren
id|client
comma
id|buf
comma
l_int|2
)paren
suffix:semicolon
singleline_comment|// set the video bitrate
r_if
c_cond
(paren
id|params-&gt;bitrate_mode
op_eq
id|MPEG_BITRATE_MODE_VBR
)paren
(brace
singleline_comment|// set the target bitrate
id|buf
(braket
l_int|0
)braket
op_assign
l_int|0x80
suffix:semicolon
id|buf
(braket
l_int|1
)braket
op_assign
id|params-&gt;video_target_bitrate
op_rshift
l_int|8
suffix:semicolon
id|buf
(braket
l_int|2
)braket
op_assign
id|params-&gt;video_target_bitrate
op_amp
l_int|0xff
suffix:semicolon
id|i2c_master_send
c_func
(paren
id|client
comma
id|buf
comma
l_int|3
)paren
suffix:semicolon
singleline_comment|// set the max bitrate
id|buf
(braket
l_int|0
)braket
op_assign
l_int|0x81
suffix:semicolon
id|buf
(braket
l_int|1
)braket
op_assign
id|params-&gt;video_max_bitrate
op_rshift
l_int|8
suffix:semicolon
id|buf
(braket
l_int|2
)braket
op_assign
id|params-&gt;video_max_bitrate
op_amp
l_int|0xff
suffix:semicolon
id|i2c_master_send
c_func
(paren
id|client
comma
id|buf
comma
l_int|3
)paren
suffix:semicolon
)brace
r_else
(brace
singleline_comment|// set the target bitrate (no max bitrate for CBR)
id|buf
(braket
l_int|0
)braket
op_assign
l_int|0x81
suffix:semicolon
id|buf
(braket
l_int|1
)braket
op_assign
id|params-&gt;video_target_bitrate
op_rshift
l_int|8
suffix:semicolon
id|buf
(braket
l_int|2
)braket
op_assign
id|params-&gt;video_target_bitrate
op_amp
l_int|0xff
suffix:semicolon
id|i2c_master_send
c_func
(paren
id|client
comma
id|buf
comma
l_int|3
)paren
suffix:semicolon
)brace
singleline_comment|// set the audio bitrate
id|buf
(braket
l_int|0
)braket
op_assign
l_int|0x94
suffix:semicolon
id|buf
(braket
l_int|1
)braket
op_assign
id|params-&gt;audio_bitrate
suffix:semicolon
id|i2c_master_send
c_func
(paren
id|client
comma
id|buf
comma
l_int|2
)paren
suffix:semicolon
singleline_comment|// set the total bitrate
id|buf
(braket
l_int|0
)braket
op_assign
l_int|0xb1
suffix:semicolon
id|buf
(braket
l_int|1
)braket
op_assign
id|params-&gt;total_bitrate
op_rshift
l_int|8
suffix:semicolon
id|buf
(braket
l_int|2
)braket
op_assign
id|params-&gt;total_bitrate
op_amp
l_int|0xff
suffix:semicolon
id|i2c_master_send
c_func
(paren
id|client
comma
id|buf
comma
l_int|3
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|saa6752hs_init
r_static
r_int
id|saa6752hs_init
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
comma
r_struct
id|mpeg_params
op_star
id|params
)paren
(brace
r_int
r_char
id|buf
(braket
l_int|3
)braket
suffix:semicolon
r_void
op_star
id|data
suffix:semicolon
singleline_comment|// check the bitrate parameters first
r_if
c_cond
(paren
id|params
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|params-&gt;bitrate_mode
op_ge
id|MPEG_BITRATE_MODE_MAX
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|params-&gt;video_target_bitrate
op_ge
id|MPEG_VIDEO_TARGET_BITRATE_MAX
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|params-&gt;video_max_bitrate
op_ge
id|MPEG_VIDEO_MAX_BITRATE_MAX
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|params-&gt;audio_bitrate
op_ge
id|MPEG_AUDIO_BITRATE_MAX
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|params-&gt;total_bitrate
op_ge
id|MPEG_TOTAL_BITRATE_MAX
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|params-&gt;bitrate_mode
op_eq
id|MPEG_BITRATE_MODE_MAX
op_logical_and
id|params-&gt;video_target_bitrate
op_le
id|params-&gt;video_max_bitrate
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
singleline_comment|// Set GOP structure {3, 13}
id|buf
(braket
l_int|0
)braket
op_assign
l_int|0x72
suffix:semicolon
id|buf
(braket
l_int|1
)braket
op_assign
l_int|0x03
suffix:semicolon
id|buf
(braket
l_int|2
)braket
op_assign
l_int|0x0D
suffix:semicolon
id|i2c_master_send
c_func
(paren
id|client
comma
id|buf
comma
l_int|3
)paren
suffix:semicolon
singleline_comment|// Set minimum Q-scale {4}
id|buf
(braket
l_int|0
)braket
op_assign
l_int|0x82
suffix:semicolon
id|buf
(braket
l_int|1
)braket
op_assign
l_int|0x04
suffix:semicolon
id|i2c_master_send
c_func
(paren
id|client
comma
id|buf
comma
l_int|2
)paren
suffix:semicolon
singleline_comment|// Set maximum Q-scale {12}
id|buf
(braket
l_int|0
)braket
op_assign
l_int|0x83
suffix:semicolon
id|buf
(braket
l_int|1
)braket
op_assign
l_int|0x0C
suffix:semicolon
id|i2c_master_send
c_func
(paren
id|client
comma
id|buf
comma
l_int|2
)paren
suffix:semicolon
singleline_comment|// Set Output Protocol
id|buf
(braket
l_int|0
)braket
op_assign
l_int|0xD0
suffix:semicolon
id|buf
(braket
l_int|1
)braket
op_assign
l_int|0x01
suffix:semicolon
id|i2c_master_send
c_func
(paren
id|client
comma
id|buf
comma
l_int|2
)paren
suffix:semicolon
singleline_comment|// Set video output stream format {TS}
id|buf
(braket
l_int|0
)braket
op_assign
l_int|0xB0
suffix:semicolon
id|buf
(braket
l_int|1
)braket
op_assign
l_int|0x05
suffix:semicolon
id|i2c_master_send
c_func
(paren
id|client
comma
id|buf
comma
l_int|2
)paren
suffix:semicolon
singleline_comment|// Set Audio PID {0x103}
id|buf
(braket
l_int|0
)braket
op_assign
l_int|0xC1
suffix:semicolon
id|buf
(braket
l_int|1
)braket
op_assign
l_int|0x01
suffix:semicolon
id|buf
(braket
l_int|2
)braket
op_assign
l_int|0x03
suffix:semicolon
id|i2c_master_send
c_func
(paren
id|client
comma
id|buf
comma
l_int|3
)paren
suffix:semicolon
singleline_comment|// setup bitrate settings
id|data
op_assign
id|i2c_get_clientdata
c_func
(paren
id|client
)paren
suffix:semicolon
r_if
c_cond
(paren
id|params
)paren
(brace
id|saa6752hs_set_bitrate
c_func
(paren
id|client
comma
id|params
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|data
comma
id|params
comma
r_sizeof
(paren
r_struct
id|mpeg_params
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
singleline_comment|// parameters were not supplied. use the previous set
id|saa6752hs_set_bitrate
c_func
(paren
id|client
comma
(paren
r_struct
id|mpeg_params
op_star
)paren
id|data
)paren
suffix:semicolon
)brace
singleline_comment|// Send SI tables
id|i2c_master_send
c_func
(paren
id|client
comma
id|PAT
comma
r_sizeof
(paren
id|PAT
)paren
)paren
suffix:semicolon
id|i2c_master_send
c_func
(paren
id|client
comma
id|PMT
comma
r_sizeof
(paren
id|PMT
)paren
)paren
suffix:semicolon
singleline_comment|// mute then unmute audio. This removes buzzing artefacts
id|buf
(braket
l_int|0
)braket
op_assign
l_int|0xa4
suffix:semicolon
id|buf
(braket
l_int|1
)braket
op_assign
l_int|1
suffix:semicolon
id|i2c_master_send
c_func
(paren
id|client
comma
id|buf
comma
l_int|2
)paren
suffix:semicolon
id|buf
(braket
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
id|i2c_master_send
c_func
(paren
id|client
comma
id|buf
comma
l_int|2
)paren
suffix:semicolon
singleline_comment|// start it going
id|saa6752hs_chip_command
c_func
(paren
id|client
comma
id|SAA6752HS_COMMAND_START
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|saa6752hs_attach
r_static
r_int
id|saa6752hs_attach
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adap
comma
r_int
id|addr
comma
r_int
id|kind
)paren
(brace
r_struct
id|i2c_client
op_star
id|client
suffix:semicolon
r_struct
id|mpeg_params
op_star
id|params
suffix:semicolon
id|client_template.adapter
op_assign
id|adap
suffix:semicolon
id|client_template.addr
op_assign
id|addr
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;saa6752hs: chip found @ 0x%x&bslash;n&quot;
comma
id|addr
op_lshift
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|NULL
op_eq
(paren
id|client
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|i2c_client
)paren
comma
id|GFP_KERNEL
)paren
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memcpy
c_func
(paren
id|client
comma
op_amp
id|client_template
comma
r_sizeof
(paren
r_struct
id|i2c_client
)paren
)paren
suffix:semicolon
id|strlcpy
c_func
(paren
id|client-&gt;name
comma
l_string|&quot;saa6752hs&quot;
comma
r_sizeof
(paren
id|client-&gt;name
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|NULL
op_eq
(paren
id|params
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|mpeg_params
)paren
comma
id|GFP_KERNEL
)paren
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memcpy
c_func
(paren
id|params
comma
op_amp
id|mpeg_params_template
comma
r_sizeof
(paren
r_struct
id|mpeg_params
)paren
)paren
suffix:semicolon
id|i2c_set_clientdata
c_func
(paren
id|client
comma
id|params
)paren
suffix:semicolon
id|i2c_attach_client
c_func
(paren
id|client
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|saa6752hs_probe
r_static
r_int
id|saa6752hs_probe
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adap
)paren
(brace
r_if
c_cond
(paren
id|adap
op_member_access_from_pointer
r_class
op_amp
id|I2C_CLASS_TV_ANALOG
)paren
r_return
id|i2c_probe
c_func
(paren
id|adap
comma
op_amp
id|addr_data
comma
id|saa6752hs_attach
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|saa6752hs_detach
r_static
r_int
id|saa6752hs_detach
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
)paren
(brace
r_void
op_star
id|data
suffix:semicolon
id|data
op_assign
id|i2c_get_clientdata
c_func
(paren
id|client
)paren
suffix:semicolon
id|i2c_detach_client
c_func
(paren
id|client
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|data
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|client
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|saa6752hs_command
id|saa6752hs_command
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
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
id|mpeg_params
op_star
id|init_arg
op_assign
id|arg
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|MPEG_SETPARAMS
suffix:colon
r_return
id|saa6752hs_init
c_func
(paren
id|client
comma
id|init_arg
)paren
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* nothing */
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* ----------------------------------------------------------------------- */
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
l_string|&quot;i2c saa6752hs MPEG encoder&quot;
comma
dot
id|id
op_assign
id|I2C_DRIVERID_SAA6752HS
comma
dot
id|flags
op_assign
id|I2C_DF_NOTIFY
comma
dot
id|attach_adapter
op_assign
id|saa6752hs_probe
comma
dot
id|detach_client
op_assign
id|saa6752hs_detach
comma
dot
id|command
op_assign
id|saa6752hs_command
comma
)brace
suffix:semicolon
DECL|variable|client_template
r_static
r_struct
id|i2c_client
id|client_template
op_assign
(brace
id|I2C_DEVNAME
c_func
(paren
l_string|&quot;(saa6752hs unset)&quot;
)paren
comma
dot
id|flags
op_assign
id|I2C_CLIENT_ALLOW_USE
comma
dot
id|driver
op_assign
op_amp
id|driver
comma
)brace
suffix:semicolon
DECL|function|saa6752hs_init_module
r_static
r_int
id|__init
id|saa6752hs_init_module
c_func
(paren
r_void
)paren
(brace
r_return
id|i2c_add_driver
c_func
(paren
op_amp
id|driver
)paren
suffix:semicolon
)brace
DECL|function|saa6752hs_cleanup_module
r_static
r_void
id|__exit
id|saa6752hs_cleanup_module
c_func
(paren
r_void
)paren
(brace
id|i2c_del_driver
c_func
(paren
op_amp
id|driver
)paren
suffix:semicolon
)brace
DECL|variable|saa6752hs_init_module
id|module_init
c_func
(paren
id|saa6752hs_init_module
)paren
suffix:semicolon
DECL|variable|saa6752hs_cleanup_module
id|module_exit
c_func
(paren
id|saa6752hs_cleanup_module
)paren
suffix:semicolon
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-basic-offset: 8&n; * End:&n; */
eof
