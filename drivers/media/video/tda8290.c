multiline_comment|/*&n; * $Id: tda8290.c,v 1.7 2005/03/07 12:01:51 kraxel Exp $&n; *&n; * i2c tv tuner chip device driver&n; * controls the philips tda8290+75 tuner chip combo.&n; */
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;linux/videodev.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;media/tuner.h&gt;
multiline_comment|/* ---------------------------------------------------------------------- */
DECL|struct|freq_entry
r_struct
id|freq_entry
(brace
DECL|member|freq
id|u16
id|freq
suffix:semicolon
DECL|member|value
id|u8
id|value
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|band_table
r_static
r_struct
id|freq_entry
id|band_table
(braket
)braket
op_assign
(brace
(brace
l_int|0x2DF4
comma
l_int|0x1C
)brace
comma
(brace
l_int|0x2574
comma
l_int|0x14
)brace
comma
(brace
l_int|0x22B4
comma
l_int|0x0C
)brace
comma
(brace
l_int|0x20D4
comma
l_int|0x0B
)brace
comma
(brace
l_int|0x1E74
comma
l_int|0x3B
)brace
comma
(brace
l_int|0x1C34
comma
l_int|0x33
)brace
comma
(brace
l_int|0x16F4
comma
l_int|0x5B
)brace
comma
(brace
l_int|0x1454
comma
l_int|0x53
)brace
comma
(brace
l_int|0x12D4
comma
l_int|0x52
)brace
comma
(brace
l_int|0x1034
comma
l_int|0x4A
)brace
comma
(brace
l_int|0x0EE4
comma
l_int|0x7A
)brace
comma
(brace
l_int|0x0D34
comma
l_int|0x72
)brace
comma
(brace
l_int|0x0B54
comma
l_int|0x9A
)brace
comma
(brace
l_int|0x0914
comma
l_int|0x91
)brace
comma
(brace
l_int|0x07F4
comma
l_int|0x89
)brace
comma
(brace
l_int|0x0774
comma
l_int|0xB9
)brace
comma
(brace
l_int|0x067B
comma
l_int|0xB1
)brace
comma
(brace
l_int|0x0634
comma
l_int|0xD9
)brace
comma
(brace
l_int|0x05A4
comma
l_int|0xD8
)brace
comma
singleline_comment|// FM radio
(brace
l_int|0x0494
comma
l_int|0xD0
)brace
comma
(brace
l_int|0x03BC
comma
l_int|0xC8
)brace
comma
(brace
l_int|0x0394
comma
l_int|0xF8
)brace
comma
singleline_comment|// 57250000 Hz
(brace
l_int|0x0000
comma
l_int|0xF0
)brace
comma
singleline_comment|// 0
)brace
suffix:semicolon
DECL|variable|div_table
r_static
r_struct
id|freq_entry
id|div_table
(braket
)braket
op_assign
(brace
(brace
l_int|0x1C34
comma
l_int|3
)brace
comma
(brace
l_int|0x0D34
comma
l_int|2
)brace
comma
(brace
l_int|0x067B
comma
l_int|1
)brace
comma
(brace
l_int|0x0000
comma
l_int|0
)brace
comma
)brace
suffix:semicolon
DECL|variable|agc_table
r_static
r_struct
id|freq_entry
id|agc_table
(braket
)braket
op_assign
(brace
(brace
l_int|0x22B4
comma
l_int|0x8F
)brace
comma
(brace
l_int|0x0B54
comma
l_int|0x9F
)brace
comma
(brace
l_int|0x09A4
comma
l_int|0x8F
)brace
comma
(brace
l_int|0x0554
comma
l_int|0x9F
)brace
comma
(brace
l_int|0x0000
comma
l_int|0xBF
)brace
comma
)brace
suffix:semicolon
DECL|function|get_freq_entry
r_static
id|__u8
id|get_freq_entry
c_func
(paren
r_struct
id|freq_entry
op_star
id|table
comma
id|__u16
id|freq
)paren
(brace
r_while
c_loop
(paren
id|table-&gt;freq
op_logical_and
id|table-&gt;freq
OG
id|freq
)paren
(brace
id|table
op_increment
suffix:semicolon
)brace
r_return
id|table-&gt;value
suffix:semicolon
)brace
multiline_comment|/* ---------------------------------------------------------------------- */
DECL|variable|i2c_enable_bridge
r_static
r_int
r_char
id|i2c_enable_bridge
(braket
l_int|2
)braket
op_assign
(brace
l_int|0x21
comma
l_int|0xC0
)brace
suffix:semicolon
DECL|variable|i2c_disable_bridge
r_static
r_int
r_char
id|i2c_disable_bridge
(braket
l_int|2
)braket
op_assign
(brace
l_int|0x21
comma
l_int|0x80
)brace
suffix:semicolon
DECL|variable|i2c_init_tda8275
r_static
r_int
r_char
id|i2c_init_tda8275
(braket
l_int|14
)braket
op_assign
(brace
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x7C
comma
l_int|0x04
comma
l_int|0xA3
comma
l_int|0x3F
comma
l_int|0x2A
comma
l_int|0x04
comma
l_int|0xFF
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x40
)brace
suffix:semicolon
DECL|variable|i2c_set_VS
r_static
r_int
r_char
id|i2c_set_VS
(braket
l_int|2
)braket
op_assign
(brace
l_int|0x30
comma
l_int|0x6F
)brace
suffix:semicolon
DECL|variable|i2c_set_GP01_CF
r_static
r_int
r_char
id|i2c_set_GP01_CF
(braket
l_int|2
)braket
op_assign
(brace
l_int|0x20
comma
l_int|0x0B
)brace
suffix:semicolon
DECL|variable|i2c_tda8290_reset
r_static
r_int
r_char
id|i2c_tda8290_reset
(braket
l_int|2
)braket
op_assign
(brace
l_int|0x00
comma
l_int|0x00
)brace
suffix:semicolon
DECL|variable|i2c_gainset_off
r_static
r_int
r_char
id|i2c_gainset_off
(braket
l_int|2
)braket
op_assign
(brace
l_int|0x28
comma
l_int|0x14
)brace
suffix:semicolon
DECL|variable|i2c_gainset_on
r_static
r_int
r_char
id|i2c_gainset_on
(braket
l_int|2
)braket
op_assign
(brace
l_int|0x28
comma
l_int|0x54
)brace
suffix:semicolon
DECL|variable|i2c_agc3_00
r_static
r_int
r_char
id|i2c_agc3_00
(braket
l_int|2
)braket
op_assign
(brace
l_int|0x80
comma
l_int|0x00
)brace
suffix:semicolon
DECL|variable|i2c_agc2_BF
r_static
r_int
r_char
id|i2c_agc2_BF
(braket
l_int|2
)braket
op_assign
(brace
l_int|0x60
comma
l_int|0xBF
)brace
suffix:semicolon
DECL|variable|i2c_cb1_D2
r_static
r_int
r_char
id|i2c_cb1_D2
(braket
l_int|2
)braket
op_assign
(brace
l_int|0x30
comma
l_int|0xD2
)brace
suffix:semicolon
DECL|variable|i2c_cb1_56
r_static
r_int
r_char
id|i2c_cb1_56
(braket
l_int|2
)braket
op_assign
(brace
l_int|0x30
comma
l_int|0x56
)brace
suffix:semicolon
DECL|variable|i2c_cb1_52
r_static
r_int
r_char
id|i2c_cb1_52
(braket
l_int|2
)braket
op_assign
(brace
l_int|0x30
comma
l_int|0x52
)brace
suffix:semicolon
DECL|variable|i2c_cb1_50
r_static
r_int
r_char
id|i2c_cb1_50
(braket
l_int|2
)braket
op_assign
(brace
l_int|0x30
comma
l_int|0x50
)brace
suffix:semicolon
DECL|variable|i2c_agc2_7F
r_static
r_int
r_char
id|i2c_agc2_7F
(braket
l_int|2
)braket
op_assign
(brace
l_int|0x60
comma
l_int|0x7F
)brace
suffix:semicolon
DECL|variable|i2c_agc3_08
r_static
r_int
r_char
id|i2c_agc3_08
(braket
l_int|2
)braket
op_assign
(brace
l_int|0x80
comma
l_int|0x08
)brace
suffix:semicolon
DECL|variable|i2c_msg_init
r_static
r_struct
id|i2c_msg
id|i2c_msg_init
(braket
)braket
op_assign
(brace
(brace
id|I2C_ADDR_TDA8275
comma
l_int|0
comma
id|ARRAY_SIZE
c_func
(paren
id|i2c_init_tda8275
)paren
comma
id|i2c_init_tda8275
)brace
comma
(brace
id|I2C_ADDR_TDA8290
comma
l_int|0
comma
id|ARRAY_SIZE
c_func
(paren
id|i2c_disable_bridge
)paren
comma
id|i2c_disable_bridge
)brace
comma
(brace
id|I2C_ADDR_TDA8290
comma
l_int|0
comma
id|ARRAY_SIZE
c_func
(paren
id|i2c_set_VS
)paren
comma
id|i2c_set_VS
)brace
comma
(brace
id|I2C_ADDR_TDA8290
comma
l_int|0
comma
id|ARRAY_SIZE
c_func
(paren
id|i2c_set_GP01_CF
)paren
comma
id|i2c_set_GP01_CF
)brace
comma
)brace
suffix:semicolon
DECL|variable|i2c_msg_prolog
r_static
r_struct
id|i2c_msg
id|i2c_msg_prolog
(braket
)braket
op_assign
(brace
singleline_comment|//&t;{ I2C_ADDR_TDA8290, 0, ARRAY_SIZE(i2c_easy_mode), i2c_easy_mode },
(brace
id|I2C_ADDR_TDA8290
comma
l_int|0
comma
id|ARRAY_SIZE
c_func
(paren
id|i2c_gainset_off
)paren
comma
id|i2c_gainset_off
)brace
comma
(brace
id|I2C_ADDR_TDA8290
comma
l_int|0
comma
id|ARRAY_SIZE
c_func
(paren
id|i2c_tda8290_reset
)paren
comma
id|i2c_tda8290_reset
)brace
comma
(brace
id|I2C_ADDR_TDA8290
comma
l_int|0
comma
id|ARRAY_SIZE
c_func
(paren
id|i2c_enable_bridge
)paren
comma
id|i2c_enable_bridge
)brace
comma
)brace
suffix:semicolon
DECL|variable|i2c_msg_config
r_static
r_struct
id|i2c_msg
id|i2c_msg_config
(braket
)braket
op_assign
(brace
singleline_comment|//&t;{ I2C_ADDR_TDA8275, 0, ARRAY_SIZE(i2c_set_freq), i2c_set_freq },
(brace
id|I2C_ADDR_TDA8275
comma
l_int|0
comma
id|ARRAY_SIZE
c_func
(paren
id|i2c_agc3_00
)paren
comma
id|i2c_agc3_00
)brace
comma
(brace
id|I2C_ADDR_TDA8275
comma
l_int|0
comma
id|ARRAY_SIZE
c_func
(paren
id|i2c_agc2_BF
)paren
comma
id|i2c_agc2_BF
)brace
comma
(brace
id|I2C_ADDR_TDA8275
comma
l_int|0
comma
id|ARRAY_SIZE
c_func
(paren
id|i2c_cb1_D2
)paren
comma
id|i2c_cb1_D2
)brace
comma
(brace
id|I2C_ADDR_TDA8275
comma
l_int|0
comma
id|ARRAY_SIZE
c_func
(paren
id|i2c_cb1_56
)paren
comma
id|i2c_cb1_56
)brace
comma
(brace
id|I2C_ADDR_TDA8275
comma
l_int|0
comma
id|ARRAY_SIZE
c_func
(paren
id|i2c_cb1_52
)paren
comma
id|i2c_cb1_52
)brace
comma
)brace
suffix:semicolon
DECL|variable|i2c_msg_epilog
r_static
r_struct
id|i2c_msg
id|i2c_msg_epilog
(braket
)braket
op_assign
(brace
(brace
id|I2C_ADDR_TDA8275
comma
l_int|0
comma
id|ARRAY_SIZE
c_func
(paren
id|i2c_cb1_50
)paren
comma
id|i2c_cb1_50
)brace
comma
(brace
id|I2C_ADDR_TDA8275
comma
l_int|0
comma
id|ARRAY_SIZE
c_func
(paren
id|i2c_agc2_7F
)paren
comma
id|i2c_agc2_7F
)brace
comma
(brace
id|I2C_ADDR_TDA8275
comma
l_int|0
comma
id|ARRAY_SIZE
c_func
(paren
id|i2c_agc3_08
)paren
comma
id|i2c_agc3_08
)brace
comma
(brace
id|I2C_ADDR_TDA8290
comma
l_int|0
comma
id|ARRAY_SIZE
c_func
(paren
id|i2c_disable_bridge
)paren
comma
id|i2c_disable_bridge
)brace
comma
(brace
id|I2C_ADDR_TDA8290
comma
l_int|0
comma
id|ARRAY_SIZE
c_func
(paren
id|i2c_gainset_on
)paren
comma
id|i2c_gainset_on
)brace
comma
)brace
suffix:semicolon
DECL|function|tda8290_tune
r_static
r_int
id|tda8290_tune
c_func
(paren
r_struct
id|i2c_client
op_star
id|c
)paren
(brace
r_struct
id|tuner
op_star
id|t
op_assign
id|i2c_get_clientdata
c_func
(paren
id|c
)paren
suffix:semicolon
r_struct
id|i2c_msg
id|easy_mode
op_assign
(brace
id|I2C_ADDR_TDA8290
comma
l_int|0
comma
l_int|2
comma
id|t-&gt;i2c_easy_mode
)brace
suffix:semicolon
r_struct
id|i2c_msg
id|set_freq
op_assign
(brace
id|I2C_ADDR_TDA8275
comma
l_int|0
comma
l_int|8
comma
id|t-&gt;i2c_set_freq
)brace
suffix:semicolon
id|i2c_transfer
c_func
(paren
id|c-&gt;adapter
comma
op_amp
id|easy_mode
comma
l_int|1
)paren
suffix:semicolon
id|i2c_transfer
c_func
(paren
id|c-&gt;adapter
comma
id|i2c_msg_prolog
comma
id|ARRAY_SIZE
c_func
(paren
id|i2c_msg_prolog
)paren
)paren
suffix:semicolon
id|i2c_transfer
c_func
(paren
id|c-&gt;adapter
comma
op_amp
id|set_freq
comma
l_int|1
)paren
suffix:semicolon
id|i2c_transfer
c_func
(paren
id|c-&gt;adapter
comma
id|i2c_msg_config
comma
id|ARRAY_SIZE
c_func
(paren
id|i2c_msg_config
)paren
)paren
suffix:semicolon
id|msleep
c_func
(paren
l_int|550
)paren
suffix:semicolon
id|i2c_transfer
c_func
(paren
id|c-&gt;adapter
comma
id|i2c_msg_epilog
comma
id|ARRAY_SIZE
c_func
(paren
id|i2c_msg_epilog
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|set_frequency
r_static
r_void
id|set_frequency
c_func
(paren
r_struct
id|tuner
op_star
id|t
comma
id|u16
id|ifc
)paren
(brace
id|u32
id|N
op_assign
(paren
(paren
(paren
id|t-&gt;freq
op_lshift
l_int|3
)paren
op_plus
id|ifc
)paren
op_amp
l_int|0x3fffc
)paren
suffix:semicolon
id|N
op_assign
id|N
op_rshift
id|get_freq_entry
c_func
(paren
id|div_table
comma
id|t-&gt;freq
)paren
suffix:semicolon
id|t-&gt;i2c_set_freq
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
id|t-&gt;i2c_set_freq
(braket
l_int|1
)braket
op_assign
(paren
r_int
r_char
)paren
(paren
id|N
op_rshift
l_int|8
)paren
suffix:semicolon
id|t-&gt;i2c_set_freq
(braket
l_int|2
)braket
op_assign
(paren
r_int
r_char
)paren
id|N
suffix:semicolon
id|t-&gt;i2c_set_freq
(braket
l_int|3
)braket
op_assign
l_int|0x40
suffix:semicolon
id|t-&gt;i2c_set_freq
(braket
l_int|4
)braket
op_assign
l_int|0x52
suffix:semicolon
id|t-&gt;i2c_set_freq
(braket
l_int|5
)braket
op_assign
id|get_freq_entry
c_func
(paren
id|band_table
comma
id|t-&gt;freq
)paren
suffix:semicolon
id|t-&gt;i2c_set_freq
(braket
l_int|6
)braket
op_assign
id|get_freq_entry
c_func
(paren
id|agc_table
comma
id|t-&gt;freq
)paren
suffix:semicolon
id|t-&gt;i2c_set_freq
(braket
l_int|7
)braket
op_assign
l_int|0x8f
suffix:semicolon
)brace
DECL|macro|V4L2_STD_MN
mdefine_line|#define V4L2_STD_MN&t;(V4L2_STD_PAL_M|V4L2_STD_PAL_N|V4L2_STD_PAL_Nc|V4L2_STD_NTSC)
DECL|macro|V4L2_STD_B
mdefine_line|#define V4L2_STD_B&t;(V4L2_STD_PAL_B|V4L2_STD_PAL_B1|V4L2_STD_SECAM_B)
DECL|macro|V4L2_STD_GH
mdefine_line|#define V4L2_STD_GH&t;(V4L2_STD_PAL_G|V4L2_STD_PAL_H|V4L2_STD_SECAM_G|V4L2_STD_SECAM_H)
DECL|macro|V4L2_STD_DK
mdefine_line|#define V4L2_STD_DK&t;(V4L2_STD_PAL_DK|V4L2_STD_SECAM_DK)
DECL|function|set_audio
r_static
r_void
id|set_audio
c_func
(paren
r_struct
id|tuner
op_star
id|t
)paren
(brace
id|t-&gt;i2c_easy_mode
(braket
l_int|0
)braket
op_assign
l_int|0x01
suffix:semicolon
r_if
c_cond
(paren
id|t-&gt;std
op_amp
id|V4L2_STD_MN
)paren
id|t-&gt;i2c_easy_mode
(braket
l_int|1
)braket
op_assign
l_int|0x01
suffix:semicolon
r_else
r_if
c_cond
(paren
id|t-&gt;std
op_amp
id|V4L2_STD_B
)paren
id|t-&gt;i2c_easy_mode
(braket
l_int|1
)braket
op_assign
l_int|0x02
suffix:semicolon
r_else
r_if
c_cond
(paren
id|t-&gt;std
op_amp
id|V4L2_STD_GH
)paren
id|t-&gt;i2c_easy_mode
(braket
l_int|1
)braket
op_assign
l_int|0x04
suffix:semicolon
r_else
r_if
c_cond
(paren
id|t-&gt;std
op_amp
id|V4L2_STD_PAL_I
)paren
id|t-&gt;i2c_easy_mode
(braket
l_int|1
)braket
op_assign
l_int|0x08
suffix:semicolon
r_else
r_if
c_cond
(paren
id|t-&gt;std
op_amp
id|V4L2_STD_DK
)paren
id|t-&gt;i2c_easy_mode
(braket
l_int|1
)braket
op_assign
l_int|0x10
suffix:semicolon
r_else
r_if
c_cond
(paren
id|t-&gt;std
op_amp
id|V4L2_STD_SECAM_L
)paren
id|t-&gt;i2c_easy_mode
(braket
l_int|1
)braket
op_assign
l_int|0x20
suffix:semicolon
)brace
DECL|function|set_tv_freq
r_static
r_void
id|set_tv_freq
c_func
(paren
r_struct
id|i2c_client
op_star
id|c
comma
r_int
r_int
id|freq
)paren
(brace
r_struct
id|tuner
op_star
id|t
op_assign
id|i2c_get_clientdata
c_func
(paren
id|c
)paren
suffix:semicolon
id|set_audio
c_func
(paren
id|t
)paren
suffix:semicolon
id|set_frequency
c_func
(paren
id|t
comma
l_int|864
)paren
suffix:semicolon
id|tda8290_tune
c_func
(paren
id|c
)paren
suffix:semicolon
)brace
DECL|function|set_radio_freq
r_static
r_void
id|set_radio_freq
c_func
(paren
r_struct
id|i2c_client
op_star
id|c
comma
r_int
r_int
id|freq
)paren
(brace
r_struct
id|tuner
op_star
id|t
op_assign
id|i2c_get_clientdata
c_func
(paren
id|c
)paren
suffix:semicolon
id|set_frequency
c_func
(paren
id|t
comma
l_int|704
)paren
suffix:semicolon
id|tda8290_tune
c_func
(paren
id|c
)paren
suffix:semicolon
)brace
DECL|function|has_signal
r_static
r_int
id|has_signal
c_func
(paren
r_struct
id|i2c_client
op_star
id|c
)paren
(brace
r_int
r_char
id|i2c_get_afc
(braket
l_int|1
)braket
op_assign
(brace
l_int|0x1B
)brace
suffix:semicolon
r_int
r_char
id|afc
op_assign
l_int|0
suffix:semicolon
id|i2c_master_send
c_func
(paren
id|c
comma
id|i2c_get_afc
comma
id|ARRAY_SIZE
c_func
(paren
id|i2c_get_afc
)paren
)paren
suffix:semicolon
id|i2c_master_recv
c_func
(paren
id|c
comma
op_amp
id|afc
comma
l_int|1
)paren
suffix:semicolon
r_return
(paren
id|afc
op_amp
l_int|0x80
)paren
ques
c_cond
l_int|65535
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|function|tda8290_init
r_int
id|tda8290_init
c_func
(paren
r_struct
id|i2c_client
op_star
id|c
)paren
(brace
r_struct
id|tuner
op_star
id|t
op_assign
id|i2c_get_clientdata
c_func
(paren
id|c
)paren
suffix:semicolon
id|strlcpy
c_func
(paren
id|c-&gt;name
comma
l_string|&quot;tda8290+75&quot;
comma
r_sizeof
(paren
id|c-&gt;name
)paren
)paren
suffix:semicolon
id|tuner_info
c_func
(paren
l_string|&quot;tuner: type set to %s&bslash;n&quot;
comma
id|c-&gt;name
)paren
suffix:semicolon
id|t-&gt;tv_freq
op_assign
id|set_tv_freq
suffix:semicolon
id|t-&gt;radio_freq
op_assign
id|set_radio_freq
suffix:semicolon
id|t-&gt;has_signal
op_assign
id|has_signal
suffix:semicolon
id|i2c_master_send
c_func
(paren
id|c
comma
id|i2c_enable_bridge
comma
id|ARRAY_SIZE
c_func
(paren
id|i2c_enable_bridge
)paren
)paren
suffix:semicolon
id|i2c_transfer
c_func
(paren
id|c-&gt;adapter
comma
id|i2c_msg_init
comma
id|ARRAY_SIZE
c_func
(paren
id|i2c_msg_init
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-basic-offset: 8&n; * End:&n; */
eof
