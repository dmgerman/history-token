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
macro_line|#include &quot;tuner.h&quot;
macro_line|#include &quot;audiochip.h&quot;
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
l_int|0x60
comma
l_int|0x6f
comma
id|I2C_CLIENT_END
)brace
suffix:semicolon
DECL|variable|probe
r_static
r_int
r_int
id|probe
(braket
l_int|2
)braket
op_assign
(brace
id|I2C_CLIENT_END
comma
id|I2C_CLIENT_END
)brace
suffix:semicolon
DECL|variable|probe_range
r_static
r_int
r_int
id|probe_range
(braket
l_int|2
)braket
op_assign
(brace
id|I2C_CLIENT_END
comma
id|I2C_CLIENT_END
)brace
suffix:semicolon
DECL|variable|ignore
r_static
r_int
r_int
id|ignore
(braket
l_int|2
)braket
op_assign
(brace
id|I2C_CLIENT_END
comma
id|I2C_CLIENT_END
)brace
suffix:semicolon
DECL|variable|ignore_range
r_static
r_int
r_int
id|ignore_range
(braket
l_int|2
)braket
op_assign
(brace
id|I2C_CLIENT_END
comma
id|I2C_CLIENT_END
)brace
suffix:semicolon
DECL|variable|force
r_static
r_int
r_int
id|force
(braket
l_int|2
)braket
op_assign
(brace
id|I2C_CLIENT_END
comma
id|I2C_CLIENT_END
)brace
suffix:semicolon
DECL|variable|addr_data
r_static
r_struct
id|i2c_client_address_data
id|addr_data
op_assign
(brace
id|normal_i2c
comma
id|normal_i2c_range
comma
id|probe
comma
id|probe_range
comma
id|ignore
comma
id|ignore_range
comma
id|force
)brace
suffix:semicolon
DECL|variable|debug
r_static
r_int
id|debug
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* insmod parameter */
DECL|variable|type
r_static
r_int
id|type
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* insmod parameter */
DECL|variable|addr
r_static
r_int
id|addr
op_assign
l_int|0
suffix:semicolon
DECL|variable|pal
r_static
r_char
op_star
id|pal
op_assign
l_string|&quot;b&quot;
suffix:semicolon
DECL|variable|this_adap
r_static
r_int
id|this_adap
suffix:semicolon
DECL|variable|tv_range
r_static
r_int
id|tv_range
(braket
l_int|2
)braket
op_assign
(brace
l_int|44
comma
l_int|958
)brace
suffix:semicolon
DECL|variable|radio_range
r_static
r_int
id|radio_range
(braket
l_int|2
)braket
op_assign
(brace
l_int|65
comma
l_int|108
)brace
suffix:semicolon
DECL|macro|dprintk
mdefine_line|#define dprintk     if (debug) printk
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
id|type
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|addr
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|tv_range
comma
l_string|&quot;2i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|radio_range
comma
l_string|&quot;2i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|pal
comma
l_string|&quot;s&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|struct|tuner
r_struct
id|tuner
(brace
DECL|member|type
r_int
id|type
suffix:semicolon
multiline_comment|/* chip type */
DECL|member|freq
r_int
id|freq
suffix:semicolon
multiline_comment|/* keep track of the current settings */
DECL|member|std
r_int
id|std
suffix:semicolon
DECL|member|radio
r_int
id|radio
suffix:semicolon
DECL|member|mode
r_int
id|mode
suffix:semicolon
multiline_comment|/* PAL(0)/SECAM(1) mode (PHILIPS_SECAM only) */
)brace
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
multiline_comment|/* tv standard selection for Temic 4046 FM5&n;   this value takes the low bits of control byte 2&n;   from datasheet Rev.01, Feb.00 &n;     standard     BG      I       L       L2      D&n;     picture IF   38.9    38.9    38.9    33.95   38.9&n;     sound 1      33.4    32.9    32.4    40.45   32.4&n;     sound 2      33.16   &n;     NICAM        33.05   32.348  33.05           33.05&n; */
DECL|macro|TEMIC_SET_PAL_I
mdefine_line|#define TEMIC_SET_PAL_I         0x05
DECL|macro|TEMIC_SET_PAL_DK
mdefine_line|#define TEMIC_SET_PAL_DK        0x09
DECL|macro|TEMIC_SET_PAL_L
mdefine_line|#define TEMIC_SET_PAL_L         0x0a 
singleline_comment|// SECAM ?
DECL|macro|TEMIC_SET_PAL_L2
mdefine_line|#define TEMIC_SET_PAL_L2        0x0b 
singleline_comment|// change IF !
DECL|macro|TEMIC_SET_PAL_BG
mdefine_line|#define TEMIC_SET_PAL_BG        0x0c
multiline_comment|/* tv tuner system standard selection for Philips FQ1216ME&n;   this value takes the low bits of control byte 2&n;   from datasheet &quot;1999 Nov 16&quot; (supersedes &quot;1999 Mar 23&quot;)&n;     standard &t;&t;BG&t;DK&t;I&t;L&t;L`&n;     picture carrier&t;38.90&t;38.90&t;38.90&t;38.90&t;33.95&n;     colour&t;&t;34.47&t;34.47&t;34.47&t;34.47&t;38.38&n;     sound 1&t;&t;33.40&t;32.40&t;32.90&t;32.40&t;40.45&n;     sound 2&t;&t;33.16&t;-&t;-&t;-&t;-&n;     NICAM&t;&t;33.05&t;33.05&t;32.35&t;33.05&t;39.80&n; */
DECL|macro|PHILIPS_SET_PAL_I
mdefine_line|#define PHILIPS_SET_PAL_I&t;0x01 /* Bit 2 always zero !*/
DECL|macro|PHILIPS_SET_PAL_BGDK
mdefine_line|#define PHILIPS_SET_PAL_BGDK&t;0x09
DECL|macro|PHILIPS_SET_PAL_L2
mdefine_line|#define PHILIPS_SET_PAL_L2&t;0x0a
DECL|macro|PHILIPS_SET_PAL_L
mdefine_line|#define PHILIPS_SET_PAL_L&t;0x0b&t;
multiline_comment|/* system switching for Philips FI1216MF MK2&n;   from datasheet &quot;1996 Jul 09&quot;,&n; */
DECL|macro|PHILIPS_MF_SET_BG
mdefine_line|#define PHILIPS_MF_SET_BG&t;0x01 /* Bit 2 must be zero, Bit 3 is system output */
DECL|macro|PHILIPS_MF_SET_PAL_L
mdefine_line|#define PHILIPS_MF_SET_PAL_L&t;0x03
DECL|macro|PHILIPS_MF_SET_PAL_L2
mdefine_line|#define PHILIPS_MF_SET_PAL_L2&t;0x02
multiline_comment|/* ---------------------------------------------------------------------- */
DECL|struct|tunertype
r_struct
id|tunertype
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|Vendor
r_int
r_char
id|Vendor
suffix:semicolon
DECL|member|Type
r_int
r_char
id|Type
suffix:semicolon
DECL|member|thresh1
r_int
r_int
id|thresh1
suffix:semicolon
multiline_comment|/*  band switch VHF_LO &lt;=&gt; VHF_HI  */
DECL|member|thresh2
r_int
r_int
id|thresh2
suffix:semicolon
multiline_comment|/*  band switch VHF_HI &lt;=&gt; UHF     */
DECL|member|VHF_L
r_int
r_char
id|VHF_L
suffix:semicolon
DECL|member|VHF_H
r_int
r_char
id|VHF_H
suffix:semicolon
DECL|member|UHF
r_int
r_char
id|UHF
suffix:semicolon
DECL|member|config
r_int
r_char
id|config
suffix:semicolon
DECL|member|IFPCoff
r_int
r_int
id|IFPCoff
suffix:semicolon
multiline_comment|/* 622.4=16*38.90 MHz PAL, 732=16*45.75 NTSC */
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;The floats in the tuner struct are computed at compile time&n; *&t;by gcc and cast back to integers. Thus we don&squot;t violate the&n; *&t;&quot;no float in kernel&quot; rule.&n; */
DECL|variable|tuners
r_static
r_struct
id|tunertype
id|tuners
(braket
)braket
op_assign
(brace
(brace
l_string|&quot;Temic PAL (4002 FH5)&quot;
comma
id|TEMIC
comma
id|PAL
comma
l_int|16
op_star
l_float|140.25
comma
l_int|16
op_star
l_float|463.25
comma
l_int|0x02
comma
l_int|0x04
comma
l_int|0x01
comma
l_int|0x8e
comma
l_int|623
)brace
comma
(brace
l_string|&quot;Philips PAL_I&quot;
comma
id|Philips
comma
id|PAL_I
comma
l_int|16
op_star
l_float|140.25
comma
l_int|16
op_star
l_float|463.25
comma
l_int|0xa0
comma
l_int|0x90
comma
l_int|0x30
comma
l_int|0x8e
comma
l_int|623
)brace
comma
(brace
l_string|&quot;Philips NTSC&quot;
comma
id|Philips
comma
id|NTSC
comma
l_int|16
op_star
l_float|157.25
comma
l_int|16
op_star
l_float|451.25
comma
l_int|0xA0
comma
l_int|0x90
comma
l_int|0x30
comma
l_int|0x8e
comma
l_int|732
)brace
comma
(brace
l_string|&quot;Philips SECAM&quot;
comma
id|Philips
comma
id|SECAM
comma
l_int|16
op_star
l_float|168.25
comma
l_int|16
op_star
l_float|447.25
comma
l_int|0xA7
comma
l_int|0x97
comma
l_int|0x37
comma
l_int|0x8e
comma
l_int|623
)brace
comma
(brace
l_string|&quot;NoTuner&quot;
comma
id|NoTuner
comma
id|NOTUNER
comma
l_int|0
comma
l_int|0
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
)brace
comma
(brace
l_string|&quot;Philips PAL&quot;
comma
id|Philips
comma
id|PAL
comma
l_int|16
op_star
l_float|168.25
comma
l_int|16
op_star
l_float|447.25
comma
l_int|0xA0
comma
l_int|0x90
comma
l_int|0x30
comma
l_int|0x8e
comma
l_int|623
)brace
comma
(brace
l_string|&quot;Temic NTSC (4032 FY5)&quot;
comma
id|TEMIC
comma
id|NTSC
comma
l_int|16
op_star
l_float|157.25
comma
l_int|16
op_star
l_float|463.25
comma
l_int|0x02
comma
l_int|0x04
comma
l_int|0x01
comma
l_int|0x8e
comma
l_int|732
)brace
comma
(brace
l_string|&quot;Temic PAL_I (4062 FY5)&quot;
comma
id|TEMIC
comma
id|PAL_I
comma
l_int|16
op_star
l_float|170.00
comma
l_int|16
op_star
l_float|450.00
comma
l_int|0x02
comma
l_int|0x04
comma
l_int|0x01
comma
l_int|0x8e
comma
l_int|623
)brace
comma
(brace
l_string|&quot;Temic NTSC (4036 FY5)&quot;
comma
id|TEMIC
comma
id|NTSC
comma
l_int|16
op_star
l_float|157.25
comma
l_int|16
op_star
l_float|463.25
comma
l_int|0xa0
comma
l_int|0x90
comma
l_int|0x30
comma
l_int|0x8e
comma
l_int|732
)brace
comma
(brace
l_string|&quot;Alps HSBH1&quot;
comma
id|TEMIC
comma
id|NTSC
comma
l_int|16
op_star
l_float|137.25
comma
l_int|16
op_star
l_float|385.25
comma
l_int|0x01
comma
l_int|0x02
comma
l_int|0x08
comma
l_int|0x8e
comma
l_int|732
)brace
comma
(brace
l_string|&quot;Alps TSBE1&quot;
comma
id|TEMIC
comma
id|PAL
comma
l_int|16
op_star
l_float|137.25
comma
l_int|16
op_star
l_float|385.25
comma
l_int|0x01
comma
l_int|0x02
comma
l_int|0x08
comma
l_int|0x8e
comma
l_int|732
)brace
comma
(brace
l_string|&quot;Alps TSBB5&quot;
comma
id|Alps
comma
id|PAL_I
comma
multiline_comment|/* tested (UK UHF) with Modtec MM205 */
l_int|16
op_star
l_float|133.25
comma
l_int|16
op_star
l_float|351.25
comma
l_int|0x01
comma
l_int|0x02
comma
l_int|0x08
comma
l_int|0x8e
comma
l_int|632
)brace
comma
(brace
l_string|&quot;Alps TSBE5&quot;
comma
id|Alps
comma
id|PAL
comma
multiline_comment|/* untested - data sheet guess. Only IF differs. */
l_int|16
op_star
l_float|133.25
comma
l_int|16
op_star
l_float|351.25
comma
l_int|0x01
comma
l_int|0x02
comma
l_int|0x08
comma
l_int|0x8e
comma
l_int|622
)brace
comma
(brace
l_string|&quot;Alps TSBC5&quot;
comma
id|Alps
comma
id|PAL
comma
multiline_comment|/* untested - data sheet guess. Only IF differs. */
l_int|16
op_star
l_float|133.25
comma
l_int|16
op_star
l_float|351.25
comma
l_int|0x01
comma
l_int|0x02
comma
l_int|0x08
comma
l_int|0x8e
comma
l_int|608
)brace
comma
(brace
l_string|&quot;Temic PAL_I (4006FH5)&quot;
comma
id|TEMIC
comma
id|PAL_I
comma
l_int|16
op_star
l_float|170.00
comma
l_int|16
op_star
l_float|450.00
comma
l_int|0xa0
comma
l_int|0x90
comma
l_int|0x30
comma
l_int|0x8e
comma
l_int|623
)brace
comma
(brace
l_string|&quot;Alps TSCH6&quot;
comma
id|Alps
comma
id|NTSC
comma
l_int|16
op_star
l_float|137.25
comma
l_int|16
op_star
l_float|385.25
comma
l_int|0x14
comma
l_int|0x12
comma
l_int|0x11
comma
l_int|0x8e
comma
l_int|732
)brace
comma
(brace
l_string|&quot;Temic PAL_DK (4016 FY5)&quot;
comma
id|TEMIC
comma
id|PAL
comma
l_int|16
op_star
l_float|136.25
comma
l_int|16
op_star
l_float|456.25
comma
l_int|0xa0
comma
l_int|0x90
comma
l_int|0x30
comma
l_int|0x8e
comma
l_int|623
)brace
comma
(brace
l_string|&quot;Philips NTSC_M (MK2)&quot;
comma
id|Philips
comma
id|NTSC
comma
l_int|16
op_star
l_float|160.00
comma
l_int|16
op_star
l_float|454.00
comma
l_int|0xa0
comma
l_int|0x90
comma
l_int|0x30
comma
l_int|0x8e
comma
l_int|732
)brace
comma
(brace
l_string|&quot;Temic PAL_I (4066 FY5)&quot;
comma
id|TEMIC
comma
id|PAL_I
comma
l_int|16
op_star
l_float|169.00
comma
l_int|16
op_star
l_float|454.00
comma
l_int|0xa0
comma
l_int|0x90
comma
l_int|0x30
comma
l_int|0x8e
comma
l_int|623
)brace
comma
(brace
l_string|&quot;Temic PAL* auto (4006 FN5)&quot;
comma
id|TEMIC
comma
id|PAL
comma
l_int|16
op_star
l_float|169.00
comma
l_int|16
op_star
l_float|454.00
comma
l_int|0xa0
comma
l_int|0x90
comma
l_int|0x30
comma
l_int|0x8e
comma
l_int|623
)brace
comma
(brace
l_string|&quot;Temic PAL (4009 FR5)&quot;
comma
id|TEMIC
comma
id|PAL
comma
l_int|16
op_star
l_float|141.00
comma
l_int|16
op_star
l_float|464.00
comma
l_int|0xa0
comma
l_int|0x90
comma
l_int|0x30
comma
l_int|0x8e
comma
l_int|623
)brace
comma
(brace
l_string|&quot;Temic NTSC (4039 FR5)&quot;
comma
id|TEMIC
comma
id|NTSC
comma
l_int|16
op_star
l_float|158.00
comma
l_int|16
op_star
l_float|453.00
comma
l_int|0xa0
comma
l_int|0x90
comma
l_int|0x30
comma
l_int|0x8e
comma
l_int|732
)brace
comma
(brace
l_string|&quot;Temic PAL/SECAM multi (4046 FM5)&quot;
comma
id|TEMIC
comma
id|PAL
comma
l_int|16
op_star
l_float|169.00
comma
l_int|16
op_star
l_float|454.00
comma
l_int|0xa0
comma
l_int|0x90
comma
l_int|0x30
comma
l_int|0x8e
comma
l_int|623
)brace
comma
(brace
l_string|&quot;Philips PAL_DK&quot;
comma
id|Philips
comma
id|PAL
comma
l_int|16
op_star
l_float|170.00
comma
l_int|16
op_star
l_float|450.00
comma
l_int|0xa0
comma
l_int|0x90
comma
l_int|0x30
comma
l_int|0x8e
comma
l_int|623
)brace
comma
(brace
l_string|&quot;Philips PAL/SECAM multi (FQ1216ME)&quot;
comma
id|Philips
comma
id|PAL
comma
l_int|16
op_star
l_float|170.00
comma
l_int|16
op_star
l_float|450.00
comma
l_int|0xa0
comma
l_int|0x90
comma
l_int|0x30
comma
l_int|0x8e
comma
l_int|623
)brace
comma
(brace
l_string|&quot;LG PAL_I+FM (TAPC-I001D)&quot;
comma
id|LGINNOTEK
comma
id|PAL_I
comma
l_int|16
op_star
l_float|170.00
comma
l_int|16
op_star
l_float|450.00
comma
l_int|0xa0
comma
l_int|0x90
comma
l_int|0x30
comma
l_int|0x8e
comma
l_int|623
)brace
comma
(brace
l_string|&quot;LG PAL_I (TAPC-I701D)&quot;
comma
id|LGINNOTEK
comma
id|PAL_I
comma
l_int|16
op_star
l_float|170.00
comma
l_int|16
op_star
l_float|450.00
comma
l_int|0xa0
comma
l_int|0x90
comma
l_int|0x30
comma
l_int|0x8e
comma
l_int|623
)brace
comma
(brace
l_string|&quot;LG NTSC+FM (TPI8NSR01F)&quot;
comma
id|LGINNOTEK
comma
id|NTSC
comma
l_int|16
op_star
l_float|210.00
comma
l_int|16
op_star
l_float|497.00
comma
l_int|0xa0
comma
l_int|0x90
comma
l_int|0x30
comma
l_int|0x8e
comma
l_int|732
)brace
comma
(brace
l_string|&quot;LG PAL_BG+FM (TPI8PSB01D)&quot;
comma
id|LGINNOTEK
comma
id|PAL
comma
l_int|16
op_star
l_float|170.00
comma
l_int|16
op_star
l_float|450.00
comma
l_int|0xa0
comma
l_int|0x90
comma
l_int|0x30
comma
l_int|0x8e
comma
l_int|623
)brace
comma
(brace
l_string|&quot;LG PAL_BG (TPI8PSB11D)&quot;
comma
id|LGINNOTEK
comma
id|PAL
comma
l_int|16
op_star
l_float|170.00
comma
l_int|16
op_star
l_float|450.00
comma
l_int|0xa0
comma
l_int|0x90
comma
l_int|0x30
comma
l_int|0x8e
comma
l_int|623
)brace
comma
(brace
l_string|&quot;Temic PAL* auto + FM (4009 FN5)&quot;
comma
id|TEMIC
comma
id|PAL
comma
l_int|16
op_star
l_float|141.00
comma
l_int|16
op_star
l_float|464.00
comma
l_int|0xa0
comma
l_int|0x90
comma
l_int|0x30
comma
l_int|0x8e
comma
l_int|623
)brace
)brace
suffix:semicolon
DECL|macro|TUNERS
mdefine_line|#define TUNERS (sizeof(tuners)/sizeof(struct tunertype))
multiline_comment|/* ---------------------------------------------------------------------- */
DECL|function|tuner_getstatus
r_static
r_int
id|tuner_getstatus
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
id|byte
suffix:semicolon
r_if
c_cond
(paren
l_int|1
op_ne
id|i2c_master_recv
c_func
(paren
id|c
comma
op_amp
id|byte
comma
l_int|1
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|byte
suffix:semicolon
)brace
DECL|macro|TUNER_POR
mdefine_line|#define TUNER_POR       0x80
DECL|macro|TUNER_FL
mdefine_line|#define TUNER_FL        0x40
DECL|macro|TUNER_MODE
mdefine_line|#define TUNER_MODE      0x38
DECL|macro|TUNER_AFC
mdefine_line|#define TUNER_AFC       0x07
DECL|macro|TUNER_STEREO
mdefine_line|#define TUNER_STEREO    0x10 /* radio mode */
DECL|macro|TUNER_SIGNAL
mdefine_line|#define TUNER_SIGNAL    0x07 /* radio mode */
DECL|function|tuner_signal
r_static
r_int
id|tuner_signal
c_func
(paren
r_struct
id|i2c_client
op_star
id|c
)paren
(brace
r_return
(paren
id|tuner_getstatus
c_func
(paren
id|c
)paren
op_amp
id|TUNER_SIGNAL
)paren
op_lshift
l_int|13
suffix:semicolon
)brace
DECL|function|tuner_stereo
r_static
r_int
id|tuner_stereo
c_func
(paren
r_struct
id|i2c_client
op_star
id|c
)paren
(brace
r_return
(paren
id|tuner_getstatus
(paren
id|c
)paren
op_amp
id|TUNER_STEREO
)paren
suffix:semicolon
)brace
DECL|function|tuner_islocked
r_static
r_int
id|tuner_islocked
(paren
r_struct
id|i2c_client
op_star
id|c
)paren
(brace
r_return
(paren
id|tuner_getstatus
(paren
id|c
)paren
op_amp
id|TUNER_FL
)paren
suffix:semicolon
)brace
DECL|function|tuner_afcstatus
r_static
r_int
id|tuner_afcstatus
(paren
r_struct
id|i2c_client
op_star
id|c
)paren
(brace
r_return
(paren
id|tuner_getstatus
(paren
id|c
)paren
op_amp
id|TUNER_AFC
)paren
op_minus
l_int|2
suffix:semicolon
)brace
macro_line|#if 0 /* unused */
r_static
r_int
id|tuner_mode
(paren
r_struct
id|i2c_client
op_star
id|c
)paren
(brace
r_return
(paren
id|tuner_getstatus
(paren
id|c
)paren
op_amp
id|TUNER_MODE
)paren
op_rshift
l_int|3
suffix:semicolon
)brace
macro_line|#endif
singleline_comment|// Set tuner frequency,  freq in Units of 62.5kHz = 1/16MHz
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
id|freq
)paren
(brace
id|u8
id|config
suffix:semicolon
id|u16
id|div
suffix:semicolon
r_struct
id|tunertype
op_star
id|tun
suffix:semicolon
r_struct
id|tuner
op_star
id|t
op_assign
id|c-&gt;data
suffix:semicolon
r_int
r_char
id|buffer
(braket
l_int|4
)braket
suffix:semicolon
r_int
id|rc
suffix:semicolon
r_if
c_cond
(paren
id|freq
template_param
id|tv_range
(braket
l_int|1
)braket
op_star
l_int|16
)paren
(brace
multiline_comment|/* FIXME: better do that chip-specific, but&n;&t;&t;   right now we don&squot;t have that in the config&n;&t;&t;   struct and this way is still better than no&n;&t;&t;   check at all */
id|printk
c_func
(paren
l_string|&quot;tuner: TV freq (%d.%02d) out of range (%d-%d)&bslash;n&quot;
comma
id|freq
op_div
l_int|16
comma
id|freq
op_mod
l_int|16
op_star
l_int|100
op_div
l_int|16
comma
id|tv_range
(braket
l_int|0
)braket
comma
id|tv_range
(braket
l_int|1
)braket
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|t-&gt;type
op_eq
op_minus
l_int|1
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;tuner: tuner type not set&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|tun
op_assign
op_amp
id|tuners
(braket
id|t-&gt;type
)braket
suffix:semicolon
r_if
c_cond
(paren
id|freq
OL
id|tun-&gt;thresh1
)paren
id|config
op_assign
id|tun-&gt;VHF_L
suffix:semicolon
r_else
r_if
c_cond
(paren
id|freq
OL
id|tun-&gt;thresh2
)paren
id|config
op_assign
id|tun-&gt;VHF_H
suffix:semicolon
r_else
id|config
op_assign
id|tun-&gt;UHF
suffix:semicolon
multiline_comment|/* tv norm specific stuff for multi-norm tuners */
r_switch
c_cond
(paren
id|t-&gt;type
)paren
(brace
r_case
id|TUNER_PHILIPS_SECAM
suffix:colon
multiline_comment|/* 0x01 -&gt; ??? no change ??? */
multiline_comment|/* 0x02 -&gt; PAL BDGHI / SECAM L */
multiline_comment|/* 0x04 -&gt; ??? PAL others / SECAM others ??? */
id|config
op_and_assign
op_complement
l_int|0x02
suffix:semicolon
r_if
c_cond
(paren
id|t-&gt;mode
)paren
id|config
op_or_assign
l_int|0x02
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TUNER_TEMIC_4046FM5
suffix:colon
id|config
op_and_assign
op_complement
l_int|0x0f
suffix:semicolon
r_switch
c_cond
(paren
id|pal
(braket
l_int|0
)braket
)paren
(brace
r_case
l_char|&squot;i&squot;
suffix:colon
r_case
l_char|&squot;I&squot;
suffix:colon
id|config
op_or_assign
id|TEMIC_SET_PAL_I
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;d&squot;
suffix:colon
r_case
l_char|&squot;D&squot;
suffix:colon
id|config
op_or_assign
id|TEMIC_SET_PAL_DK
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;l&squot;
suffix:colon
r_case
l_char|&squot;L&squot;
suffix:colon
id|config
op_or_assign
id|TEMIC_SET_PAL_L
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;b&squot;
suffix:colon
r_case
l_char|&squot;B&squot;
suffix:colon
r_case
l_char|&squot;g&squot;
suffix:colon
r_case
l_char|&squot;G&squot;
suffix:colon
r_default
suffix:colon
id|config
op_or_assign
id|TEMIC_SET_PAL_BG
suffix:semicolon
r_break
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|TUNER_PHILIPS_FQ1216ME
suffix:colon
id|config
op_and_assign
op_complement
l_int|0x0f
suffix:semicolon
r_switch
c_cond
(paren
id|pal
(braket
l_int|0
)braket
)paren
(brace
r_case
l_char|&squot;i&squot;
suffix:colon
r_case
l_char|&squot;I&squot;
suffix:colon
id|config
op_or_assign
id|PHILIPS_SET_PAL_I
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;l&squot;
suffix:colon
r_case
l_char|&squot;L&squot;
suffix:colon
id|config
op_or_assign
id|PHILIPS_SET_PAL_L
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;d&squot;
suffix:colon
r_case
l_char|&squot;D&squot;
suffix:colon
r_case
l_char|&squot;b&squot;
suffix:colon
r_case
l_char|&squot;B&squot;
suffix:colon
r_case
l_char|&squot;g&squot;
suffix:colon
r_case
l_char|&squot;G&squot;
suffix:colon
id|config
op_or_assign
id|PHILIPS_SET_PAL_BGDK
suffix:semicolon
r_break
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * Philips FI1216MK2 remark from specification :&n;&t; * for channel selection involving band switching, and to ensure&n;&t; * smooth tuning to the desired channel without causing&n;&t; * unnecessary charge pump action, it is recommended to consider&n;&t; * the difference between wanted channel frequency and the&n;&t; * current channel frequency.  Unnecessary charge pump action&n;&t; * will result in very low tuning voltage which may drive the&n;&t; * oscillator to extreme conditions.&n;&t; *&n;&t; * Progfou: specification says to send config data before&n;&t; * frequency in case (wanted frequency &lt; current frequency).&n;&t; */
id|div
op_assign
id|freq
op_plus
id|tun-&gt;IFPCoff
suffix:semicolon
r_if
c_cond
(paren
id|t-&gt;type
op_eq
id|TUNER_PHILIPS_SECAM
op_logical_and
id|freq
OL
id|t-&gt;freq
)paren
(brace
id|buffer
(braket
l_int|0
)braket
op_assign
id|tun-&gt;config
suffix:semicolon
id|buffer
(braket
l_int|1
)braket
op_assign
id|config
suffix:semicolon
id|buffer
(braket
l_int|2
)braket
op_assign
(paren
id|div
op_rshift
l_int|8
)paren
op_amp
l_int|0x7f
suffix:semicolon
id|buffer
(braket
l_int|3
)braket
op_assign
id|div
op_amp
l_int|0xff
suffix:semicolon
)brace
r_else
(brace
id|buffer
(braket
l_int|0
)braket
op_assign
(paren
id|div
op_rshift
l_int|8
)paren
op_amp
l_int|0x7f
suffix:semicolon
id|buffer
(braket
l_int|1
)braket
op_assign
id|div
op_amp
l_int|0xff
suffix:semicolon
id|buffer
(braket
l_int|2
)braket
op_assign
id|tun-&gt;config
suffix:semicolon
id|buffer
(braket
l_int|3
)braket
op_assign
id|config
suffix:semicolon
)brace
r_if
c_cond
(paren
l_int|4
op_ne
(paren
id|rc
op_assign
id|i2c_master_send
c_func
(paren
id|c
comma
id|buffer
comma
l_int|4
)paren
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;tuner: i2c i/o error: rc == %d (should be 4)&bslash;n&quot;
comma
id|rc
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
id|freq
)paren
(brace
id|u8
id|config
suffix:semicolon
id|u16
id|div
suffix:semicolon
r_struct
id|tunertype
op_star
id|tun
suffix:semicolon
r_struct
id|tuner
op_star
id|t
op_assign
(paren
r_struct
id|tuner
op_star
)paren
id|c-&gt;data
suffix:semicolon
r_int
r_char
id|buffer
(braket
l_int|4
)braket
suffix:semicolon
r_int
id|rc
suffix:semicolon
r_if
c_cond
(paren
id|freq
template_param
id|radio_range
(braket
l_int|1
)braket
op_star
l_int|16
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;tuner: radio freq (%d.%02d) out of range (%d-%d)&bslash;n&quot;
comma
id|freq
op_div
l_int|16
comma
id|freq
op_mod
l_int|16
op_star
l_int|100
op_div
l_int|16
comma
id|radio_range
(braket
l_int|0
)braket
comma
id|radio_range
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|t-&gt;type
op_eq
op_minus
l_int|1
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;tuner: tuner type not set&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|tun
op_assign
op_amp
id|tuners
(braket
id|t-&gt;type
)braket
suffix:semicolon
id|config
op_assign
l_int|0xa4
multiline_comment|/* 0xa5 */
suffix:semicolon
multiline_comment|/* bit 0 is AFC (set) vs. RF-Signal (clear) */
id|div
op_assign
id|freq
op_plus
(paren
r_int
)paren
(paren
l_int|16
op_star
l_float|10.7
)paren
suffix:semicolon
id|div
op_and_assign
l_int|0x7fff
suffix:semicolon
id|buffer
(braket
l_int|0
)braket
op_assign
(paren
id|div
op_rshift
l_int|8
)paren
op_amp
l_int|0x7f
suffix:semicolon
id|buffer
(braket
l_int|1
)braket
op_assign
id|div
op_amp
l_int|0xff
suffix:semicolon
id|buffer
(braket
l_int|2
)braket
op_assign
id|tun-&gt;config
suffix:semicolon
id|buffer
(braket
l_int|3
)braket
op_assign
id|config
suffix:semicolon
r_if
c_cond
(paren
l_int|4
op_ne
(paren
id|rc
op_assign
id|i2c_master_send
c_func
(paren
id|c
comma
id|buffer
comma
l_int|4
)paren
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;tuner: i2c i/o error: rc == %d (should be 4)&bslash;n&quot;
comma
id|rc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|debug
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
op_div
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tuner_islocked
(paren
id|c
)paren
)paren
id|printk
(paren
l_string|&quot;tuner: PLL locked&bslash;n&quot;
)paren
suffix:semicolon
r_else
id|printk
(paren
l_string|&quot;tuner: PLL not locked&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|config
op_amp
l_int|1
)paren
(brace
id|printk
(paren
l_string|&quot;tuner: AFC: %d&bslash;n&quot;
comma
id|tuner_afcstatus
c_func
(paren
id|c
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
(paren
l_string|&quot;tuner: Signal: %d&bslash;n&quot;
comma
id|tuner_signal
c_func
(paren
id|c
)paren
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* ---------------------------------------------------------------------- */
DECL|function|tuner_attach
r_static
r_int
id|tuner_attach
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
r_int
id|flags
comma
r_int
id|kind
)paren
(brace
r_struct
id|tuner
op_star
id|t
suffix:semicolon
r_struct
id|i2c_client
op_star
id|client
suffix:semicolon
r_if
c_cond
(paren
id|this_adap
OG
l_int|0
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|this_adap
op_increment
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
l_string|&quot;tuner: chip found @ 0x%x&bslash;n&quot;
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
id|client-&gt;data
op_assign
id|t
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|tuner
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|NULL
op_eq
id|t
)paren
(brace
id|kfree
c_func
(paren
id|client
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memset
c_func
(paren
id|t
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|tuner
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|type
op_ge
l_int|0
op_logical_and
id|type
OL
id|TUNERS
)paren
(brace
id|t-&gt;type
op_assign
id|type
suffix:semicolon
id|strncpy
c_func
(paren
id|client-&gt;name
comma
id|tuners
(braket
id|t-&gt;type
)braket
dot
id|name
comma
r_sizeof
(paren
id|client-&gt;name
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|t-&gt;type
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
id|i2c_attach_client
c_func
(paren
id|client
)paren
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|tuner_probe
r_static
r_int
id|tuner_probe
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
l_int|0
op_ne
id|addr
)paren
(brace
id|normal_i2c_range
(braket
l_int|0
)braket
op_assign
id|addr
suffix:semicolon
id|normal_i2c_range
(braket
l_int|1
)braket
op_assign
id|addr
suffix:semicolon
)brace
id|this_adap
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|adap-&gt;id
op_eq
(paren
id|I2C_ALGO_BIT
op_or
id|I2C_HW_B_BT848
)paren
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
id|tuner_attach
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|tuner_detach
r_static
r_int
id|tuner_detach
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
)paren
(brace
r_struct
id|tuner
op_star
id|t
op_assign
(paren
r_struct
id|tuner
op_star
)paren
id|client-&gt;data
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
id|t
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|client
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|tuner_command
id|tuner_command
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
id|tuner
op_star
id|t
op_assign
(paren
r_struct
id|tuner
op_star
)paren
id|client-&gt;data
suffix:semicolon
r_int
op_star
id|iarg
op_assign
(paren
r_int
op_star
)paren
id|arg
suffix:semicolon
macro_line|#if 0
id|__u16
op_star
id|sarg
op_assign
(paren
id|__u16
op_star
)paren
id|arg
suffix:semicolon
macro_line|#endif
r_switch
c_cond
(paren
id|cmd
)paren
(brace
multiline_comment|/* --- configuration --- */
r_case
id|TUNER_SET_TYPE
suffix:colon
r_if
c_cond
(paren
id|t-&gt;type
op_ne
op_minus
l_int|1
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_star
id|iarg
OL
l_int|0
op_logical_or
op_star
id|iarg
op_ge
id|TUNERS
)paren
r_return
l_int|0
suffix:semicolon
id|t-&gt;type
op_assign
op_star
id|iarg
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;tuner: type set to %d (%s)&bslash;n&quot;
comma
id|t-&gt;type
comma
id|tuners
(braket
id|t-&gt;type
)braket
dot
id|name
)paren
suffix:semicolon
id|strncpy
c_func
(paren
id|client-&gt;name
comma
id|tuners
(braket
id|t-&gt;type
)braket
dot
id|name
comma
r_sizeof
(paren
id|client-&gt;name
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AUDC_SET_RADIO
suffix:colon
id|t-&gt;radio
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* --- v4l ioctls --- */
multiline_comment|/* take care: bttv does userspace copying, we&squot;ll get a&n;&t;   kernel pointer here... */
r_case
id|VIDIOCSCHAN
suffix:colon
(brace
r_struct
id|video_channel
op_star
id|vc
op_assign
id|arg
suffix:semicolon
id|t-&gt;radio
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|t-&gt;type
op_eq
id|TUNER_PHILIPS_SECAM
)paren
(brace
id|t-&gt;mode
op_assign
(paren
id|vc-&gt;norm
op_eq
id|VIDEO_MODE_SECAM
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|set_tv_freq
c_func
(paren
id|client
comma
id|t-&gt;freq
)paren
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
op_star
id|v
op_assign
id|arg
suffix:semicolon
r_if
c_cond
(paren
id|t-&gt;radio
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;tuner: radio freq set to %d.%02d&bslash;n&quot;
comma
(paren
op_star
id|iarg
)paren
op_div
l_int|16
comma
(paren
op_star
id|iarg
)paren
op_mod
l_int|16
op_star
l_int|100
op_div
l_int|16
)paren
suffix:semicolon
id|set_radio_freq
c_func
(paren
id|client
comma
op_star
id|v
)paren
suffix:semicolon
)brace
r_else
(brace
id|dprintk
c_func
(paren
l_string|&quot;tuner: tv freq set to %d.%02d&bslash;n&quot;
comma
(paren
op_star
id|iarg
)paren
op_div
l_int|16
comma
(paren
op_star
id|iarg
)paren
op_mod
l_int|16
op_star
l_int|100
op_div
l_int|16
)paren
suffix:semicolon
id|set_tv_freq
c_func
(paren
id|client
comma
op_star
id|v
)paren
suffix:semicolon
)brace
id|t-&gt;freq
op_assign
op_star
id|v
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
id|vt
op_assign
id|arg
suffix:semicolon
r_if
c_cond
(paren
id|t-&gt;radio
)paren
id|vt-&gt;signal
op_assign
id|tuner_signal
c_func
(paren
id|client
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
id|va
op_assign
id|arg
suffix:semicolon
r_if
c_cond
(paren
id|t-&gt;radio
)paren
id|va-&gt;mode
op_assign
(paren
id|tuner_stereo
c_func
(paren
id|client
)paren
ques
c_cond
id|VIDEO_SOUND_STEREO
suffix:colon
id|VIDEO_SOUND_MONO
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#if 0
multiline_comment|/* --- old, obsolete interface --- */
r_case
id|TUNER_SET_TVFREQ
suffix:colon
id|dprintk
c_func
(paren
l_string|&quot;tuner: tv freq set to %d.%02d&bslash;n&quot;
comma
(paren
op_star
id|iarg
)paren
op_div
l_int|16
comma
(paren
op_star
id|iarg
)paren
op_mod
l_int|16
op_star
l_int|100
op_div
l_int|16
)paren
suffix:semicolon
id|set_tv_freq
c_func
(paren
id|client
comma
op_star
id|iarg
)paren
suffix:semicolon
id|t-&gt;radio
op_assign
l_int|0
suffix:semicolon
id|t-&gt;freq
op_assign
op_star
id|iarg
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TUNER_SET_RADIOFREQ
suffix:colon
id|dprintk
c_func
(paren
l_string|&quot;tuner: radio freq set to %d.%02d&bslash;n&quot;
comma
(paren
op_star
id|iarg
)paren
op_div
l_int|16
comma
(paren
op_star
id|iarg
)paren
op_mod
l_int|16
op_star
l_int|100
op_div
l_int|16
)paren
suffix:semicolon
id|set_radio_freq
c_func
(paren
id|client
comma
op_star
id|iarg
)paren
suffix:semicolon
id|t-&gt;radio
op_assign
l_int|1
suffix:semicolon
id|t-&gt;freq
op_assign
op_star
id|iarg
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TUNER_SET_MODE
suffix:colon
r_if
c_cond
(paren
id|t-&gt;type
op_ne
id|TUNER_PHILIPS_SECAM
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;tuner: trying to change mode for other than TUNER_PHILIPS_SECAM&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
r_int
id|mode
op_assign
(paren
op_star
id|sarg
op_eq
id|VIDEO_MODE_SECAM
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;tuner: mode set to %d&bslash;n&quot;
comma
op_star
id|sarg
)paren
suffix:semicolon
id|t-&gt;mode
op_assign
id|mode
suffix:semicolon
id|set_tv_freq
c_func
(paren
id|client
comma
id|t-&gt;freq
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
macro_line|#endif
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
l_string|&quot;i2c TV tuner driver&quot;
comma
id|I2C_DRIVERID_TUNER
comma
id|I2C_DF_NOTIFY
comma
id|tuner_probe
comma
id|tuner_detach
comma
id|tuner_command
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
l_string|&quot;(unset)&quot;
comma
multiline_comment|/* name       */
op_minus
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
comma
op_amp
id|driver
)brace
suffix:semicolon
id|EXPORT_NO_SYMBOLS
suffix:semicolon
DECL|function|tuner_init_module
r_int
id|tuner_init_module
c_func
(paren
r_void
)paren
(brace
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
DECL|function|tuner_cleanup_module
r_void
id|tuner_cleanup_module
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
DECL|variable|tuner_init_module
id|module_init
c_func
(paren
id|tuner_init_module
)paren
suffix:semicolon
DECL|variable|tuner_cleanup_module
id|module_exit
c_func
(paren
id|tuner_cleanup_module
)paren
suffix:semicolon
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-basic-offset: 8&n; * End:&n; */
eof
