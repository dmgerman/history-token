multiline_comment|/*&n; *    Support for OR51211 (pcHDTV HD-2000) - VSB&n; *&n; *    Copyright (C) 2005 Kirk Lapray &lt;kirk_lapray@bigfoot.com&gt;&n; *&n; *    Based on code from Jack Kelliher (kelliher@xmission.com)&n; *                           Copyright (C) 2002 &amp; pcHDTV, inc.&n; *&n; *    This program is free software; you can redistribute it and/or modify&n; *    it under the terms of the GNU General Public License as published by&n; *    the Free Software Foundation; either version 2 of the License, or&n; *    (at your option) any later version.&n; *&n; *    This program is distributed in the hope that it will be useful,&n; *    but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *    GNU General Public License for more details.&n; *&n; *    You should have received a copy of the GNU General Public License&n; *    along with this program; if not, write to the Free Software&n; *    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n;*/
multiline_comment|/*&n; * This driver needs external firmware. Please use the command&n; * &quot;&lt;kerneldir&gt;/Documentation/dvb/get_dvb_firmware or51211&quot; to&n; * download/extract it, and then copy it to /usr/lib/hotplug/firmware.&n; */
DECL|macro|OR51211_DEFAULT_FIRMWARE
mdefine_line|#define OR51211_DEFAULT_FIRMWARE &quot;dvb-fe-or51211.fw&quot;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/firmware.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &quot;dvb_frontend.h&quot;
macro_line|#include &quot;or51211.h&quot;
DECL|variable|debug
r_static
r_int
id|debug
suffix:semicolon
DECL|macro|dprintk
mdefine_line|#define dprintk(args...) &bslash;&n;&t;do { &bslash;&n;&t;&t;if (debug) printk(KERN_DEBUG &quot;or51211: &quot; args); &bslash;&n;&t;} while (0)
DECL|variable|run_buf
r_static
id|u8
id|run_buf
(braket
)braket
op_assign
(brace
l_int|0x7f
comma
l_int|0x01
)brace
suffix:semicolon
DECL|variable|cmd_buf
r_static
id|u8
id|cmd_buf
(braket
)braket
op_assign
(brace
l_int|0x04
comma
l_int|0x01
comma
l_int|0x50
comma
l_int|0x80
comma
l_int|0x06
)brace
suffix:semicolon
singleline_comment|// ATSC
DECL|struct|or51211_state
r_struct
id|or51211_state
(brace
DECL|member|i2c
r_struct
id|i2c_adapter
op_star
id|i2c
suffix:semicolon
DECL|member|ops
r_struct
id|dvb_frontend_ops
id|ops
suffix:semicolon
multiline_comment|/* Configuration settings */
DECL|member|config
r_const
r_struct
id|or51211_config
op_star
id|config
suffix:semicolon
DECL|member|frontend
r_struct
id|dvb_frontend
id|frontend
suffix:semicolon
DECL|member|bt
r_struct
id|bt878
op_star
id|bt
suffix:semicolon
multiline_comment|/* Demodulator private data */
DECL|member|initialized
id|u8
id|initialized
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Tuner private data */
DECL|member|current_frequency
id|u32
id|current_frequency
suffix:semicolon
)brace
suffix:semicolon
DECL|function|i2c_writebytes
r_static
r_int
id|i2c_writebytes
(paren
r_struct
id|or51211_state
op_star
id|state
comma
id|u8
id|reg
comma
id|u8
op_star
id|buf
comma
r_int
id|len
)paren
(brace
r_int
id|err
suffix:semicolon
r_struct
id|i2c_msg
id|msg
suffix:semicolon
id|msg.addr
op_assign
id|reg
suffix:semicolon
id|msg.flags
op_assign
l_int|0
suffix:semicolon
id|msg.len
op_assign
id|len
suffix:semicolon
id|msg.buf
op_assign
id|buf
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|i2c_transfer
(paren
id|state-&gt;i2c
comma
op_amp
id|msg
comma
l_int|1
)paren
)paren
op_ne
l_int|1
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;or51211: i2c_writebytes error &quot;
l_string|&quot;(addr %02x, err == %i)&bslash;n&quot;
comma
id|reg
comma
id|err
)paren
suffix:semicolon
r_return
op_minus
id|EREMOTEIO
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|i2c_readbytes
r_static
id|u8
id|i2c_readbytes
(paren
r_struct
id|or51211_state
op_star
id|state
comma
id|u8
id|reg
comma
id|u8
op_star
id|buf
comma
r_int
id|len
)paren
(brace
r_int
id|err
suffix:semicolon
r_struct
id|i2c_msg
id|msg
suffix:semicolon
id|msg.addr
op_assign
id|reg
suffix:semicolon
id|msg.flags
op_assign
id|I2C_M_RD
suffix:semicolon
id|msg.len
op_assign
id|len
suffix:semicolon
id|msg.buf
op_assign
id|buf
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|i2c_transfer
(paren
id|state-&gt;i2c
comma
op_amp
id|msg
comma
l_int|1
)paren
)paren
op_ne
l_int|1
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;or51211: i2c_readbytes error &quot;
l_string|&quot;(addr %02x, err == %i)&bslash;n&quot;
comma
id|reg
comma
id|err
)paren
suffix:semicolon
r_return
op_minus
id|EREMOTEIO
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|or51211_load_firmware
r_static
r_int
id|or51211_load_firmware
(paren
r_struct
id|dvb_frontend
op_star
id|fe
comma
r_const
r_struct
id|firmware
op_star
id|fw
)paren
(brace
r_struct
id|or51211_state
op_star
id|state
op_assign
id|fe-&gt;demodulator_priv
suffix:semicolon
id|u8
id|tudata
(braket
l_int|585
)braket
suffix:semicolon
r_int
id|i
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;Firmware is %d bytes&bslash;n&quot;
comma
id|fw-&gt;size
)paren
suffix:semicolon
multiline_comment|/* Get eprom data */
id|tudata
(braket
l_int|0
)braket
op_assign
l_int|17
suffix:semicolon
r_if
c_cond
(paren
id|i2c_writebytes
c_func
(paren
id|state
comma
l_int|0x50
comma
id|tudata
comma
l_int|1
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;or51211:load_firmware error eprom addr&bslash;n&quot;
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
id|i2c_readbytes
c_func
(paren
id|state
comma
l_int|0x50
comma
op_amp
id|tudata
(braket
l_int|145
)braket
comma
l_int|192
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;or51211: load_firmware error eprom&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Create firmware buffer */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|145
suffix:semicolon
id|i
op_increment
)paren
id|tudata
(braket
id|i
)braket
op_assign
id|fw-&gt;data
(braket
id|i
)braket
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
l_int|248
suffix:semicolon
id|i
op_increment
)paren
id|tudata
(braket
id|i
op_plus
l_int|337
)braket
op_assign
id|fw-&gt;data
(braket
l_int|145
op_plus
id|i
)braket
suffix:semicolon
id|state-&gt;config
op_member_access_from_pointer
id|reset
c_func
(paren
id|fe
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i2c_writebytes
c_func
(paren
id|state
comma
id|state-&gt;config-&gt;demod_address
comma
id|tudata
comma
l_int|585
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;or51211: load_firmware error 1&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|msleep
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i2c_writebytes
c_func
(paren
id|state
comma
id|state-&gt;config-&gt;demod_address
comma
op_amp
id|fw-&gt;data
(braket
l_int|393
)braket
comma
l_int|8125
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;or51211: load_firmware error 2&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|msleep
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i2c_writebytes
c_func
(paren
id|state
comma
id|state-&gt;config-&gt;demod_address
comma
id|run_buf
comma
l_int|2
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;or51211: load_firmware error 3&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Wait at least 5 msec */
id|msleep
c_func
(paren
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i2c_writebytes
c_func
(paren
id|state
comma
id|state-&gt;config-&gt;demod_address
comma
id|run_buf
comma
l_int|2
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;or51211: load_firmware error 4&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|msleep
c_func
(paren
l_int|10
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;or51211: Done.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
suffix:semicolon
DECL|function|or51211_setmode
r_static
r_int
id|or51211_setmode
c_func
(paren
r_struct
id|dvb_frontend
op_star
id|fe
comma
r_int
id|mode
)paren
(brace
r_struct
id|or51211_state
op_star
id|state
op_assign
id|fe-&gt;demodulator_priv
suffix:semicolon
id|u8
id|rec_buf
(braket
l_int|14
)braket
suffix:semicolon
id|state-&gt;config
op_member_access_from_pointer
id|setmode
c_func
(paren
id|fe
comma
id|mode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i2c_writebytes
c_func
(paren
id|state
comma
id|state-&gt;config-&gt;demod_address
comma
id|run_buf
comma
l_int|2
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;or51211: setmode error 1&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Wait at least 5 msec */
id|msleep
c_func
(paren
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i2c_writebytes
c_func
(paren
id|state
comma
id|state-&gt;config-&gt;demod_address
comma
id|run_buf
comma
l_int|2
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;or51211: setmode error 2&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|msleep
c_func
(paren
l_int|10
)paren
suffix:semicolon
multiline_comment|/* Set operation mode in Receiver 1 register;&n;&t; * type 1:&n;&t; * data 0x50h  Automatic sets receiver channel conditions&n;&t; *             Automatic NTSC rejection filter&n;&t; *             Enable  MPEG serial data output&n;&t; *             MPEG2tr&n;&t; *             High tuner phase noise&n;&t; *             normal +/-150kHz Carrier acquisition range&n;&t; */
r_if
c_cond
(paren
id|i2c_writebytes
c_func
(paren
id|state
comma
id|state-&gt;config-&gt;demod_address
comma
id|cmd_buf
comma
l_int|3
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;or51211: setmode error 3&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|rec_buf
(braket
l_int|0
)braket
op_assign
l_int|0x04
suffix:semicolon
id|rec_buf
(braket
l_int|1
)braket
op_assign
l_int|0x00
suffix:semicolon
id|rec_buf
(braket
l_int|2
)braket
op_assign
l_int|0x03
suffix:semicolon
id|rec_buf
(braket
l_int|3
)braket
op_assign
l_int|0x00
suffix:semicolon
id|msleep
c_func
(paren
l_int|20
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i2c_writebytes
c_func
(paren
id|state
comma
id|state-&gt;config-&gt;demod_address
comma
id|rec_buf
comma
l_int|3
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;or51211: setmode error 5&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|msleep
c_func
(paren
l_int|3
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i2c_readbytes
c_func
(paren
id|state
comma
id|state-&gt;config-&gt;demod_address
comma
op_amp
id|rec_buf
(braket
l_int|10
)braket
comma
l_int|2
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;or51211: setmode error 6&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|dprintk
c_func
(paren
l_string|&quot;setmode rec status %02x %02x&bslash;n&quot;
comma
id|rec_buf
(braket
l_int|10
)braket
comma
id|rec_buf
(braket
l_int|11
)braket
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|or51211_set_parameters
r_static
r_int
id|or51211_set_parameters
c_func
(paren
r_struct
id|dvb_frontend
op_star
id|fe
comma
r_struct
id|dvb_frontend_parameters
op_star
id|param
)paren
(brace
r_struct
id|or51211_state
op_star
id|state
op_assign
id|fe-&gt;demodulator_priv
suffix:semicolon
id|u32
id|freq
op_assign
l_int|0
suffix:semicolon
id|u16
id|tunerfreq
op_assign
l_int|0
suffix:semicolon
id|u8
id|buf
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Change only if we are actually changing the channel */
r_if
c_cond
(paren
id|state-&gt;current_frequency
op_ne
id|param-&gt;frequency
)paren
(brace
id|freq
op_assign
l_int|44000
op_plus
(paren
id|param-&gt;frequency
op_div
l_int|1000
)paren
suffix:semicolon
id|tunerfreq
op_assign
id|freq
op_star
l_int|16
op_div
l_int|1000
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;set_parameters frequency = %d (tunerfreq = %d)&bslash;n&quot;
comma
id|param-&gt;frequency
comma
id|tunerfreq
)paren
suffix:semicolon
id|buf
(braket
l_int|0
)braket
op_assign
(paren
id|tunerfreq
op_rshift
l_int|8
)paren
op_amp
l_int|0x7F
suffix:semicolon
id|buf
(braket
l_int|1
)braket
op_assign
(paren
id|tunerfreq
op_amp
l_int|0xFF
)paren
suffix:semicolon
id|buf
(braket
l_int|2
)braket
op_assign
l_int|0x8E
suffix:semicolon
r_if
c_cond
(paren
id|param-&gt;frequency
OL
l_int|157250000
)paren
(brace
id|buf
(braket
l_int|3
)braket
op_assign
l_int|0xA0
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;set_parameters VHF low range&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|param-&gt;frequency
OL
l_int|454000000
)paren
(brace
id|buf
(braket
l_int|3
)braket
op_assign
l_int|0x90
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;set_parameters VHF high range&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|buf
(braket
l_int|3
)braket
op_assign
l_int|0x30
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;set_parameters UHF range&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|dprintk
c_func
(paren
l_string|&quot;set_parameters tuner bytes: 0x%02x 0x%02x &quot;
l_string|&quot;0x%02x 0x%02x&bslash;n&quot;
comma
id|buf
(braket
l_int|0
)braket
comma
id|buf
(braket
l_int|1
)braket
comma
id|buf
(braket
l_int|2
)braket
comma
id|buf
(braket
l_int|3
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i2c_writebytes
c_func
(paren
id|state
comma
l_int|0xC2
op_rshift
l_int|1
comma
id|buf
comma
l_int|4
)paren
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;or51211:set_parameters error &quot;
l_string|&quot;writing to tuner&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Set to ATSC mode */
id|or51211_setmode
c_func
(paren
id|fe
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Update current frequency */
id|state-&gt;current_frequency
op_assign
id|param-&gt;frequency
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|or51211_read_status
r_static
r_int
id|or51211_read_status
c_func
(paren
r_struct
id|dvb_frontend
op_star
id|fe
comma
id|fe_status_t
op_star
id|status
)paren
(brace
r_struct
id|or51211_state
op_star
id|state
op_assign
id|fe-&gt;demodulator_priv
suffix:semicolon
r_int
r_char
id|rec_buf
(braket
l_int|2
)braket
suffix:semicolon
r_int
r_char
id|snd_buf
(braket
)braket
op_assign
(brace
l_int|0x04
comma
l_int|0x00
comma
l_int|0x03
comma
l_int|0x00
)brace
suffix:semicolon
op_star
id|status
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Receiver Status */
r_if
c_cond
(paren
id|i2c_writebytes
c_func
(paren
id|state
comma
id|state-&gt;config-&gt;demod_address
comma
id|snd_buf
comma
l_int|3
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;or51132: read_status write error&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|msleep
c_func
(paren
l_int|3
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i2c_readbytes
c_func
(paren
id|state
comma
id|state-&gt;config-&gt;demod_address
comma
id|rec_buf
comma
l_int|2
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;or51132: read_status read error&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|dprintk
c_func
(paren
l_string|&quot;read_status %x %x&bslash;n&quot;
comma
id|rec_buf
(braket
l_int|0
)braket
comma
id|rec_buf
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rec_buf
(braket
l_int|0
)braket
op_amp
l_int|0x01
)paren
(brace
multiline_comment|/* Receiver Lock */
op_star
id|status
op_or_assign
id|FE_HAS_SIGNAL
suffix:semicolon
op_star
id|status
op_or_assign
id|FE_HAS_CARRIER
suffix:semicolon
op_star
id|status
op_or_assign
id|FE_HAS_VITERBI
suffix:semicolon
op_star
id|status
op_or_assign
id|FE_HAS_SYNC
suffix:semicolon
op_star
id|status
op_or_assign
id|FE_HAS_LOCK
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* log10-1 table at .5 increments from 1 to 100.5 */
DECL|variable|i100x20log10
r_static
r_int
r_int
id|i100x20log10
(braket
)braket
op_assign
(brace
l_int|0
comma
l_int|352
comma
l_int|602
comma
l_int|795
comma
l_int|954
comma
l_int|1088
comma
l_int|1204
comma
l_int|1306
comma
l_int|1397
comma
l_int|1480
comma
l_int|1556
comma
l_int|1625
comma
l_int|1690
comma
l_int|1750
comma
l_int|1806
comma
l_int|1858
comma
l_int|1908
comma
l_int|1955
comma
l_int|2000
comma
l_int|2042
comma
l_int|2082
comma
l_int|2121
comma
l_int|2158
comma
l_int|2193
comma
l_int|2227
comma
l_int|2260
comma
l_int|2292
comma
l_int|2322
comma
l_int|2352
comma
l_int|2380
comma
l_int|2408
comma
l_int|2434
comma
l_int|2460
comma
l_int|2486
comma
l_int|2510
comma
l_int|2534
comma
l_int|2557
comma
l_int|2580
comma
l_int|2602
comma
l_int|2623
comma
l_int|2644
comma
l_int|2664
comma
l_int|2684
comma
l_int|2704
comma
l_int|2723
comma
l_int|2742
comma
l_int|2760
comma
l_int|2778
comma
l_int|2795
comma
l_int|2813
comma
l_int|2829
comma
l_int|2846
comma
l_int|2862
comma
l_int|2878
comma
l_int|2894
comma
l_int|2909
comma
l_int|2924
comma
l_int|2939
comma
l_int|2954
comma
l_int|2968
comma
l_int|2982
comma
l_int|2996
comma
l_int|3010
comma
l_int|3023
comma
l_int|3037
comma
l_int|3050
comma
l_int|3062
comma
l_int|3075
comma
l_int|3088
comma
l_int|3100
comma
l_int|3112
comma
l_int|3124
comma
l_int|3136
comma
l_int|3148
comma
l_int|3159
comma
l_int|3170
comma
l_int|3182
comma
l_int|3193
comma
l_int|3204
comma
l_int|3214
comma
l_int|3225
comma
l_int|3236
comma
l_int|3246
comma
l_int|3256
comma
l_int|3266
comma
l_int|3276
comma
l_int|3286
comma
l_int|3296
comma
l_int|3306
comma
l_int|3316
comma
l_int|3325
comma
l_int|3334
comma
l_int|3344
comma
l_int|3353
comma
l_int|3362
comma
l_int|3371
comma
l_int|3380
comma
l_int|3389
comma
l_int|3397
comma
l_int|3406
comma
l_int|3415
comma
l_int|3423
comma
l_int|3432
comma
l_int|3440
comma
l_int|3448
comma
l_int|3456
comma
l_int|3464
comma
l_int|3472
comma
l_int|3480
comma
l_int|3488
comma
l_int|3496
comma
l_int|3504
comma
l_int|3511
comma
l_int|3519
comma
l_int|3526
comma
l_int|3534
comma
l_int|3541
comma
l_int|3549
comma
l_int|3556
comma
l_int|3563
comma
l_int|3570
comma
l_int|3577
comma
l_int|3584
comma
l_int|3591
comma
l_int|3598
comma
l_int|3605
comma
l_int|3612
comma
l_int|3619
comma
l_int|3625
comma
l_int|3632
comma
l_int|3639
comma
l_int|3645
comma
l_int|3652
comma
l_int|3658
comma
l_int|3665
comma
l_int|3671
comma
l_int|3677
comma
l_int|3683
comma
l_int|3690
comma
l_int|3696
comma
l_int|3702
comma
l_int|3708
comma
l_int|3714
comma
l_int|3720
comma
l_int|3726
comma
l_int|3732
comma
l_int|3738
comma
l_int|3744
comma
l_int|3750
comma
l_int|3755
comma
l_int|3761
comma
l_int|3767
comma
l_int|3772
comma
l_int|3778
comma
l_int|3784
comma
l_int|3789
comma
l_int|3795
comma
l_int|3800
comma
l_int|3806
comma
l_int|3811
comma
l_int|3816
comma
l_int|3822
comma
l_int|3827
comma
l_int|3832
comma
l_int|3838
comma
l_int|3843
comma
l_int|3848
comma
l_int|3853
comma
l_int|3858
comma
l_int|3863
comma
l_int|3868
comma
l_int|3874
comma
l_int|3879
comma
l_int|3884
comma
l_int|3888
comma
l_int|3893
comma
l_int|3898
comma
l_int|3903
comma
l_int|3908
comma
l_int|3913
comma
l_int|3918
comma
l_int|3922
comma
l_int|3927
comma
l_int|3932
comma
l_int|3936
comma
l_int|3941
comma
l_int|3946
comma
l_int|3950
comma
l_int|3955
comma
l_int|3960
comma
l_int|3964
comma
l_int|3969
comma
l_int|3973
comma
l_int|3978
comma
l_int|3982
comma
l_int|3986
comma
l_int|3991
comma
l_int|3995
comma
l_int|4000
comma
l_int|4004
comma
)brace
suffix:semicolon
DECL|variable|denom
r_static
r_int
r_int
id|denom
(braket
)braket
op_assign
(brace
l_int|1
comma
l_int|1
comma
l_int|100
comma
l_int|1000
comma
l_int|10000
comma
l_int|100000
comma
l_int|1000000
comma
l_int|10000000
comma
l_int|100000000
)brace
suffix:semicolon
DECL|function|i20Log10
r_static
r_int
r_int
id|i20Log10
c_func
(paren
r_int
r_int
id|val
)paren
(brace
r_int
r_int
id|rntval
op_assign
l_int|100
suffix:semicolon
r_int
r_int
id|tmp
op_assign
id|val
suffix:semicolon
r_int
r_int
id|exp
op_assign
l_int|1
suffix:semicolon
r_while
c_loop
(paren
id|tmp
OG
l_int|100
)paren
(brace
id|tmp
op_div_assign
l_int|100
suffix:semicolon
id|exp
op_increment
suffix:semicolon
)brace
id|val
op_assign
(paren
l_int|2
op_star
id|val
)paren
op_div
id|denom
(braket
id|exp
)braket
suffix:semicolon
r_if
c_cond
(paren
id|exp
OG
l_int|1
)paren
id|rntval
op_assign
l_int|2000
op_star
id|exp
suffix:semicolon
id|rntval
op_add_assign
id|i100x20log10
(braket
id|val
)braket
suffix:semicolon
r_return
id|rntval
suffix:semicolon
)brace
DECL|function|or51211_read_signal_strength
r_static
r_int
id|or51211_read_signal_strength
c_func
(paren
r_struct
id|dvb_frontend
op_star
id|fe
comma
id|u16
op_star
id|strength
)paren
(brace
r_struct
id|or51211_state
op_star
id|state
op_assign
id|fe-&gt;demodulator_priv
suffix:semicolon
id|u8
id|rec_buf
(braket
l_int|2
)braket
suffix:semicolon
id|u8
id|snd_buf
(braket
l_int|4
)braket
suffix:semicolon
id|u8
id|snr_equ
suffix:semicolon
multiline_comment|/* SNR after Equalizer */
id|snd_buf
(braket
l_int|0
)braket
op_assign
l_int|0x04
suffix:semicolon
id|snd_buf
(braket
l_int|1
)braket
op_assign
l_int|0x00
suffix:semicolon
id|snd_buf
(braket
l_int|2
)braket
op_assign
l_int|0x04
suffix:semicolon
id|snd_buf
(braket
l_int|3
)braket
op_assign
l_int|0x00
suffix:semicolon
r_if
c_cond
(paren
id|i2c_writebytes
c_func
(paren
id|state
comma
id|state-&gt;config-&gt;demod_address
comma
id|snd_buf
comma
l_int|3
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;or51211: read_status write error&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|msleep
c_func
(paren
l_int|3
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i2c_readbytes
c_func
(paren
id|state
comma
id|state-&gt;config-&gt;demod_address
comma
id|rec_buf
comma
l_int|2
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;or51211: read_status read error&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|snr_equ
op_assign
id|rec_buf
(braket
l_int|0
)braket
op_amp
l_int|0xff
suffix:semicolon
multiline_comment|/* The value reported back from the frontend will be FFFF=100% 0000=0% */
op_star
id|strength
op_assign
(paren
(paren
(paren
l_int|5334
op_minus
id|i20Log10
c_func
(paren
id|snr_equ
)paren
)paren
op_div
l_int|3
op_plus
l_int|5
)paren
op_star
l_int|65535
)paren
op_div
l_int|1000
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;read_signal_strength %i&bslash;n&quot;
comma
op_star
id|strength
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|or51211_read_snr
r_static
r_int
id|or51211_read_snr
c_func
(paren
r_struct
id|dvb_frontend
op_star
id|fe
comma
id|u16
op_star
id|snr
)paren
(brace
r_struct
id|or51211_state
op_star
id|state
op_assign
id|fe-&gt;demodulator_priv
suffix:semicolon
id|u8
id|rec_buf
(braket
l_int|2
)braket
suffix:semicolon
id|u8
id|snd_buf
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* SNR after Equalizer */
id|snd_buf
(braket
l_int|0
)braket
op_assign
l_int|0x04
suffix:semicolon
id|snd_buf
(braket
l_int|1
)braket
op_assign
l_int|0x00
suffix:semicolon
id|snd_buf
(braket
l_int|2
)braket
op_assign
l_int|0x04
suffix:semicolon
id|snd_buf
(braket
l_int|3
)braket
op_assign
l_int|0x00
suffix:semicolon
r_if
c_cond
(paren
id|i2c_writebytes
c_func
(paren
id|state
comma
id|state-&gt;config-&gt;demod_address
comma
id|snd_buf
comma
l_int|3
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;or51211: read_status write error&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|msleep
c_func
(paren
l_int|3
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i2c_readbytes
c_func
(paren
id|state
comma
id|state-&gt;config-&gt;demod_address
comma
id|rec_buf
comma
l_int|2
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;or51211: read_status read error&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
op_star
id|snr
op_assign
id|rec_buf
(braket
l_int|0
)braket
op_amp
l_int|0xff
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;read_snr %i&bslash;n&quot;
comma
op_star
id|snr
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|or51211_read_ber
r_static
r_int
id|or51211_read_ber
c_func
(paren
r_struct
id|dvb_frontend
op_star
id|fe
comma
id|u32
op_star
id|ber
)paren
(brace
op_star
id|ber
op_assign
op_minus
id|ENOSYS
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|or51211_read_ucblocks
r_static
r_int
id|or51211_read_ucblocks
c_func
(paren
r_struct
id|dvb_frontend
op_star
id|fe
comma
id|u32
op_star
id|ucblocks
)paren
(brace
op_star
id|ucblocks
op_assign
op_minus
id|ENOSYS
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|or51211_sleep
r_static
r_int
id|or51211_sleep
c_func
(paren
r_struct
id|dvb_frontend
op_star
id|fe
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|or51211_init
r_static
r_int
id|or51211_init
c_func
(paren
r_struct
id|dvb_frontend
op_star
id|fe
)paren
(brace
r_struct
id|or51211_state
op_star
id|state
op_assign
id|fe-&gt;demodulator_priv
suffix:semicolon
r_const
r_struct
id|or51211_config
op_star
id|config
op_assign
id|state-&gt;config
suffix:semicolon
r_const
r_struct
id|firmware
op_star
id|fw
suffix:semicolon
r_int
r_char
id|get_ver_buf
(braket
)braket
op_assign
(brace
l_int|0x04
comma
l_int|0x00
comma
l_int|0x30
comma
l_int|0x00
comma
l_int|0x00
)brace
suffix:semicolon
r_int
r_char
id|rec_buf
(braket
l_int|14
)braket
suffix:semicolon
r_int
id|ret
comma
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|state-&gt;initialized
)paren
(brace
multiline_comment|/* Request the firmware, this will block until it uploads */
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;or51211: Waiting for firmware upload &quot;
l_string|&quot;(%s)...&bslash;n&quot;
comma
id|OR51211_DEFAULT_FIRMWARE
)paren
suffix:semicolon
id|ret
op_assign
id|config
op_member_access_from_pointer
id|request_firmware
c_func
(paren
id|fe
comma
op_amp
id|fw
comma
id|OR51211_DEFAULT_FIRMWARE
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;or51211:Got Hotplug firmware&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;or51211: No firmware uploaded &quot;
l_string|&quot;(timeout or file not found?)&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
id|ret
op_assign
id|or51211_load_firmware
c_func
(paren
id|fe
comma
id|fw
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;or51211: Writing firmware to &quot;
l_string|&quot;device failed!&bslash;n&quot;
)paren
suffix:semicolon
id|release_firmware
c_func
(paren
id|fw
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;or51211: Firmware upload complete.&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Set operation mode in Receiver 1 register;&n;&t;&t; * type 1:&n;&t;&t; * data 0x50h  Automatic sets receiver channel conditions&n;&t;&t; *             Automatic NTSC rejection filter&n;&t;&t; *             Enable  MPEG serial data output&n;&t;&t; *             MPEG2tr&n;&t;&t; *             High tuner phase noise&n;&t;&t; *             normal +/-150kHz Carrier acquisition range&n;&t;&t; */
r_if
c_cond
(paren
id|i2c_writebytes
c_func
(paren
id|state
comma
id|state-&gt;config-&gt;demod_address
comma
id|cmd_buf
comma
l_int|3
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;or51211: Load DVR Error 5&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Read back ucode version to besure we loaded correctly */
multiline_comment|/* and are really up and running */
id|rec_buf
(braket
l_int|0
)braket
op_assign
l_int|0x04
suffix:semicolon
id|rec_buf
(braket
l_int|1
)braket
op_assign
l_int|0x00
suffix:semicolon
id|rec_buf
(braket
l_int|2
)braket
op_assign
l_int|0x03
suffix:semicolon
id|rec_buf
(braket
l_int|3
)braket
op_assign
l_int|0x00
suffix:semicolon
id|msleep
c_func
(paren
l_int|30
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i2c_writebytes
c_func
(paren
id|state
comma
id|state-&gt;config-&gt;demod_address
comma
id|rec_buf
comma
l_int|3
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;or51211: Load DVR Error A&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|msleep
c_func
(paren
l_int|3
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i2c_readbytes
c_func
(paren
id|state
comma
id|state-&gt;config-&gt;demod_address
comma
op_amp
id|rec_buf
(braket
l_int|10
)braket
comma
l_int|2
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;or51211: Load DVR Error B&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|rec_buf
(braket
l_int|0
)braket
op_assign
l_int|0x04
suffix:semicolon
id|rec_buf
(braket
l_int|1
)braket
op_assign
l_int|0x00
suffix:semicolon
id|rec_buf
(braket
l_int|2
)braket
op_assign
l_int|0x01
suffix:semicolon
id|rec_buf
(braket
l_int|3
)braket
op_assign
l_int|0x00
suffix:semicolon
id|msleep
c_func
(paren
l_int|20
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i2c_writebytes
c_func
(paren
id|state
comma
id|state-&gt;config-&gt;demod_address
comma
id|rec_buf
comma
l_int|3
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;or51211: Load DVR Error C&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|msleep
c_func
(paren
l_int|3
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i2c_readbytes
c_func
(paren
id|state
comma
id|state-&gt;config-&gt;demod_address
comma
op_amp
id|rec_buf
(braket
l_int|12
)braket
comma
l_int|2
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;or51211: Load DVR Error D&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|8
suffix:semicolon
id|i
op_increment
)paren
id|rec_buf
(braket
id|i
)braket
op_assign
l_int|0xed
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
l_int|5
suffix:semicolon
id|i
op_increment
)paren
(brace
id|msleep
c_func
(paren
l_int|30
)paren
suffix:semicolon
id|get_ver_buf
(braket
l_int|4
)braket
op_assign
id|i
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|i2c_writebytes
c_func
(paren
id|state
comma
id|state-&gt;config-&gt;demod_address
comma
id|get_ver_buf
comma
l_int|5
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;or51211:Load DVR Error 6&quot;
l_string|&quot; - %d&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|msleep
c_func
(paren
l_int|3
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i2c_readbytes
c_func
(paren
id|state
comma
id|state-&gt;config-&gt;demod_address
comma
op_amp
id|rec_buf
(braket
id|i
op_star
l_int|2
)braket
comma
l_int|2
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;or51211:Load DVR Error 7&quot;
l_string|&quot; - %d&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* If we didn&squot;t receive the right index, try again */
r_if
c_cond
(paren
(paren
r_int
)paren
id|rec_buf
(braket
id|i
op_star
l_int|2
op_plus
l_int|1
)braket
op_ne
id|i
op_plus
l_int|1
)paren
(brace
id|i
op_decrement
suffix:semicolon
)brace
)brace
id|dprintk
c_func
(paren
l_string|&quot;read_fwbits %x %x %x %x %x %x %x %x %x %x&bslash;n&quot;
comma
id|rec_buf
(braket
l_int|0
)braket
comma
id|rec_buf
(braket
l_int|1
)braket
comma
id|rec_buf
(braket
l_int|2
)braket
comma
id|rec_buf
(braket
l_int|3
)braket
comma
id|rec_buf
(braket
l_int|4
)braket
comma
id|rec_buf
(braket
l_int|5
)braket
comma
id|rec_buf
(braket
l_int|6
)braket
comma
id|rec_buf
(braket
l_int|7
)braket
comma
id|rec_buf
(braket
l_int|8
)braket
comma
id|rec_buf
(braket
l_int|9
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;or51211: ver TU%02x%02x%02x VSB mode %02x&quot;
l_string|&quot; Status %02x&bslash;n&quot;
comma
id|rec_buf
(braket
l_int|2
)braket
comma
id|rec_buf
(braket
l_int|4
)braket
comma
id|rec_buf
(braket
l_int|6
)braket
comma
id|rec_buf
(braket
l_int|12
)braket
comma
id|rec_buf
(braket
l_int|10
)braket
)paren
suffix:semicolon
id|rec_buf
(braket
l_int|0
)braket
op_assign
l_int|0x04
suffix:semicolon
id|rec_buf
(braket
l_int|1
)braket
op_assign
l_int|0x00
suffix:semicolon
id|rec_buf
(braket
l_int|2
)braket
op_assign
l_int|0x03
suffix:semicolon
id|rec_buf
(braket
l_int|3
)braket
op_assign
l_int|0x00
suffix:semicolon
id|msleep
c_func
(paren
l_int|20
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i2c_writebytes
c_func
(paren
id|state
comma
id|state-&gt;config-&gt;demod_address
comma
id|rec_buf
comma
l_int|3
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;or51211: Load DVR Error 8&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|msleep
c_func
(paren
l_int|20
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i2c_readbytes
c_func
(paren
id|state
comma
id|state-&gt;config-&gt;demod_address
comma
op_amp
id|rec_buf
(braket
l_int|8
)braket
comma
l_int|2
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;or51211: Load DVR Error 9&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|state-&gt;initialized
op_assign
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|or51211_get_tune_settings
r_static
r_int
id|or51211_get_tune_settings
c_func
(paren
r_struct
id|dvb_frontend
op_star
id|fe
comma
r_struct
id|dvb_frontend_tune_settings
op_star
id|fesettings
)paren
(brace
id|fesettings-&gt;min_delay_ms
op_assign
l_int|500
suffix:semicolon
id|fesettings-&gt;step_size
op_assign
l_int|0
suffix:semicolon
id|fesettings-&gt;max_drift
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|or51211_release
r_static
r_void
id|or51211_release
c_func
(paren
r_struct
id|dvb_frontend
op_star
id|fe
)paren
(brace
r_struct
id|or51211_state
op_star
id|state
op_assign
id|fe-&gt;demodulator_priv
suffix:semicolon
id|state-&gt;config
op_member_access_from_pointer
id|sleep
c_func
(paren
id|fe
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|state
)paren
suffix:semicolon
)brace
DECL|variable|or51211_ops
r_static
r_struct
id|dvb_frontend_ops
id|or51211_ops
suffix:semicolon
DECL|function|or51211_attach
r_struct
id|dvb_frontend
op_star
id|or51211_attach
c_func
(paren
r_const
r_struct
id|or51211_config
op_star
id|config
comma
r_struct
id|i2c_adapter
op_star
id|i2c
)paren
(brace
r_struct
id|or51211_state
op_star
id|state
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Allocate memory for the internal state */
id|state
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|or51211_state
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|state
op_eq
l_int|NULL
)paren
r_goto
id|error
suffix:semicolon
multiline_comment|/* Setup the state */
id|state-&gt;config
op_assign
id|config
suffix:semicolon
id|state-&gt;i2c
op_assign
id|i2c
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|state-&gt;ops
comma
op_amp
id|or51211_ops
comma
r_sizeof
(paren
r_struct
id|dvb_frontend_ops
)paren
)paren
suffix:semicolon
id|state-&gt;initialized
op_assign
l_int|0
suffix:semicolon
id|state-&gt;current_frequency
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Create dvb_frontend */
id|state-&gt;frontend.ops
op_assign
op_amp
id|state-&gt;ops
suffix:semicolon
id|state-&gt;frontend.demodulator_priv
op_assign
id|state
suffix:semicolon
r_return
op_amp
id|state-&gt;frontend
suffix:semicolon
id|error
suffix:colon
r_if
c_cond
(paren
id|state
)paren
id|kfree
c_func
(paren
id|state
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|variable|or51211_ops
r_static
r_struct
id|dvb_frontend_ops
id|or51211_ops
op_assign
(brace
dot
id|info
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;Oren OR51211 VSB Frontend&quot;
comma
dot
id|type
op_assign
id|FE_ATSC
comma
dot
id|frequency_min
op_assign
l_int|44000000
comma
dot
id|frequency_max
op_assign
l_int|958000000
comma
dot
id|frequency_stepsize
op_assign
l_int|166666
comma
dot
id|caps
op_assign
id|FE_CAN_FEC_1_2
op_or
id|FE_CAN_FEC_2_3
op_or
id|FE_CAN_FEC_3_4
op_or
id|FE_CAN_FEC_5_6
op_or
id|FE_CAN_FEC_7_8
op_or
id|FE_CAN_FEC_AUTO
op_or
id|FE_CAN_8VSB
)brace
comma
dot
id|release
op_assign
id|or51211_release
comma
dot
id|init
op_assign
id|or51211_init
comma
dot
id|sleep
op_assign
id|or51211_sleep
comma
dot
id|set_frontend
op_assign
id|or51211_set_parameters
comma
dot
id|get_tune_settings
op_assign
id|or51211_get_tune_settings
comma
dot
id|read_status
op_assign
id|or51211_read_status
comma
dot
id|read_ber
op_assign
id|or51211_read_ber
comma
dot
id|read_signal_strength
op_assign
id|or51211_read_signal_strength
comma
dot
id|read_snr
op_assign
id|or51211_read_snr
comma
dot
id|read_ucblocks
op_assign
id|or51211_read_ucblocks
comma
)brace
suffix:semicolon
id|module_param
c_func
(paren
id|debug
comma
r_int
comma
l_int|0644
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|debug
comma
l_string|&quot;Turn on/off frontend debugging (default:off).&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Oren OR51211 VSB [pcHDTV HD-2000] Demodulator Driver&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Kirk Lapray&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|or51211_attach
id|EXPORT_SYMBOL
c_func
(paren
id|or51211_attach
)paren
suffix:semicolon
eof
