multiline_comment|/*&n; *  Routines for control of the CS8427 via i2c bus&n; *  IEC958 (S/PDIF) receiver &amp; transmitter by Cirrus Logic&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/control.h&gt;
macro_line|#include &lt;sound/pcm.h&gt;
macro_line|#include &lt;sound/cs8427.h&gt;
macro_line|#include &lt;sound/asoundef.h&gt;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Jaroslav Kysela &lt;perex@suse.cz&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;IEC958 (S/PDIF) receiver &amp; transmitter by Cirrus Logic&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|macro|chip_t
mdefine_line|#define chip_t snd_i2c_device_t
DECL|macro|CS8427_ADDR
mdefine_line|#define CS8427_ADDR&t;&t;&t;(0x20&gt;&gt;1) /* fixed address */
r_typedef
r_struct
(brace
DECL|member|substream
id|snd_pcm_substream_t
op_star
id|substream
suffix:semicolon
DECL|member|hw_status
r_char
id|hw_status
(braket
l_int|24
)braket
suffix:semicolon
multiline_comment|/* hardware status */
DECL|member|def_status
r_char
id|def_status
(braket
l_int|24
)braket
suffix:semicolon
multiline_comment|/* default status */
DECL|member|pcm_status
r_char
id|pcm_status
(braket
l_int|24
)braket
suffix:semicolon
multiline_comment|/* PCM private status */
DECL|member|hw_udata
r_char
id|hw_udata
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|pcm_ctl
id|snd_kcontrol_t
op_star
id|pcm_ctl
suffix:semicolon
DECL|typedef|cs8427_stream_t
)brace
id|cs8427_stream_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|regmap
r_int
r_char
id|regmap
(braket
l_int|0x14
)braket
suffix:semicolon
multiline_comment|/* map of first 1 + 13 registers */
DECL|member|playback
id|cs8427_stream_t
id|playback
suffix:semicolon
DECL|member|capture
id|cs8427_stream_t
id|capture
suffix:semicolon
DECL|typedef|cs8427_t
)brace
id|cs8427_t
suffix:semicolon
DECL|function|swapbits
r_static
r_int
r_char
id|swapbits
c_func
(paren
r_int
r_char
id|val
)paren
(brace
r_int
id|bit
suffix:semicolon
r_int
r_char
id|res
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|bit
op_assign
l_int|0
suffix:semicolon
id|bit
OL
l_int|8
suffix:semicolon
id|bit
op_increment
)paren
(brace
id|res
op_or_assign
id|val
op_amp
l_int|1
suffix:semicolon
id|res
op_lshift_assign
l_int|1
suffix:semicolon
id|val
op_rshift_assign
l_int|1
suffix:semicolon
)brace
r_return
id|res
suffix:semicolon
)brace
DECL|function|snd_cs8427_detect
r_int
id|snd_cs8427_detect
c_func
(paren
id|snd_i2c_bus_t
op_star
id|bus
comma
r_int
r_char
id|addr
)paren
(brace
r_int
id|res
suffix:semicolon
id|snd_i2c_lock
c_func
(paren
id|bus
)paren
suffix:semicolon
id|res
op_assign
id|snd_i2c_probeaddr
c_func
(paren
id|bus
comma
id|CS8427_ADDR
op_or
(paren
id|addr
op_amp
l_int|7
)paren
)paren
suffix:semicolon
id|snd_i2c_unlock
c_func
(paren
id|bus
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
DECL|function|snd_cs8427_reg_write
r_static
r_int
id|snd_cs8427_reg_write
c_func
(paren
id|snd_i2c_device_t
op_star
id|device
comma
r_int
r_char
id|reg
comma
r_int
r_char
id|val
)paren
(brace
r_int
id|err
suffix:semicolon
r_int
r_char
id|buf
(braket
l_int|2
)braket
suffix:semicolon
id|buf
(braket
l_int|0
)braket
op_assign
id|reg
op_amp
l_int|0x7f
suffix:semicolon
id|buf
(braket
l_int|1
)braket
op_assign
id|val
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_i2c_sendbytes
c_func
(paren
id|device
comma
id|buf
comma
l_int|2
)paren
)paren
op_ne
l_int|2
)paren
(brace
id|snd_printk
c_func
(paren
l_string|&quot;unable to send bytes 0x%02x:0x%02x to CS8427 (%i)&bslash;n&quot;
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
id|err
)paren
suffix:semicolon
r_return
id|err
OL
l_int|0
ques
c_cond
id|err
suffix:colon
op_minus
id|EIO
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_cs8427_reg_read
r_static
r_int
id|snd_cs8427_reg_read
c_func
(paren
id|snd_i2c_device_t
op_star
id|device
comma
r_int
r_char
id|reg
)paren
(brace
r_int
id|err
suffix:semicolon
r_int
r_char
id|buf
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_i2c_sendbytes
c_func
(paren
id|device
comma
op_amp
id|reg
comma
l_int|1
)paren
)paren
op_ne
l_int|1
)paren
(brace
id|snd_printk
c_func
(paren
l_string|&quot;unable to send register 0x%x byte to CS8427&bslash;n&quot;
comma
id|reg
)paren
suffix:semicolon
r_return
id|err
OL
l_int|0
ques
c_cond
id|err
suffix:colon
op_minus
id|EIO
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_i2c_readbytes
c_func
(paren
id|device
comma
op_amp
id|buf
comma
l_int|1
)paren
)paren
op_ne
l_int|1
)paren
(brace
id|snd_printk
c_func
(paren
l_string|&quot;unable to read register 0x%x byte from CS8427&bslash;n&quot;
comma
id|reg
)paren
suffix:semicolon
r_return
id|err
OL
l_int|0
ques
c_cond
id|err
suffix:colon
op_minus
id|EIO
suffix:semicolon
)brace
r_return
id|buf
suffix:semicolon
)brace
DECL|function|snd_cs8427_select_corudata
r_static
r_int
id|snd_cs8427_select_corudata
c_func
(paren
id|snd_i2c_device_t
op_star
id|device
comma
r_int
id|udata
)paren
(brace
id|cs8427_t
op_star
id|chip
op_assign
id|snd_magic_cast
c_func
(paren
id|cs8427_t
comma
id|device-&gt;private_data
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
r_int
id|err
suffix:semicolon
id|udata
op_assign
id|udata
ques
c_cond
id|CS8427_BSEL
suffix:colon
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|udata
op_ne
(paren
id|chip-&gt;regmap
(braket
id|CS8427_REG_CSDATABUF
)braket
op_amp
id|udata
)paren
)paren
(brace
id|chip-&gt;regmap
(braket
id|CS8427_REG_CSDATABUF
)braket
op_and_assign
op_complement
id|CS8427_BSEL
suffix:semicolon
id|chip-&gt;regmap
(braket
id|CS8427_REG_CSDATABUF
)braket
op_or_assign
id|udata
suffix:semicolon
id|err
op_assign
id|snd_cs8427_reg_write
c_func
(paren
id|device
comma
id|CS8427_REG_CSDATABUF
comma
id|chip-&gt;regmap
(braket
id|CS8427_REG_CSDATABUF
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_cs8427_send_corudata
r_static
r_int
id|snd_cs8427_send_corudata
c_func
(paren
id|snd_i2c_device_t
op_star
id|device
comma
r_int
id|udata
comma
r_int
r_char
op_star
id|ndata
comma
r_int
id|count
)paren
(brace
id|cs8427_t
op_star
id|chip
op_assign
id|snd_magic_cast
c_func
(paren
id|cs8427_t
comma
id|device-&gt;private_data
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
r_char
op_star
id|hw_data
op_assign
id|udata
ques
c_cond
id|chip-&gt;playback.hw_udata
suffix:colon
id|chip-&gt;playback.hw_status
suffix:semicolon
r_char
id|data
(braket
l_int|32
)braket
suffix:semicolon
r_int
id|err
comma
id|idx
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|hw_data
comma
id|ndata
comma
id|count
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_cs8427_select_corudata
c_func
(paren
id|device
comma
id|udata
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
id|memcpy
c_func
(paren
id|hw_data
comma
id|data
comma
id|count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|udata
)paren
(brace
id|memset
c_func
(paren
id|data
comma
l_int|0
comma
r_sizeof
(paren
id|data
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|hw_data
comma
id|data
comma
l_int|32
)paren
op_eq
l_int|0
)paren
(brace
id|chip-&gt;regmap
(braket
id|CS8427_REG_UDATABUF
)braket
op_and_assign
op_complement
id|CS8427_UBMMASK
suffix:semicolon
id|chip-&gt;regmap
(braket
id|CS8427_REG_UDATABUF
)braket
op_or_assign
id|CS8427_UBMZEROS
op_or
id|CS8427_EFTUI
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_cs8427_reg_write
c_func
(paren
id|device
comma
id|CS8427_REG_UDATABUF
comma
id|chip-&gt;regmap
(braket
id|CS8427_REG_UDATABUF
)braket
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
id|data
(braket
l_int|0
)braket
op_assign
id|CS8427_REG_AUTOINC
op_or
id|CS8427_REG_CORU_DATABUF
suffix:semicolon
r_for
c_loop
(paren
id|idx
op_assign
l_int|0
suffix:semicolon
id|idx
OL
id|count
suffix:semicolon
id|idx
op_increment
)paren
id|data
(braket
id|idx
op_plus
l_int|1
)braket
op_assign
id|swapbits
c_func
(paren
id|ndata
(braket
id|idx
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|snd_i2c_sendbytes
c_func
(paren
id|device
comma
id|data
comma
id|count
)paren
op_ne
id|count
)paren
r_return
op_minus
id|EIO
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|snd_cs8427_free
r_static
r_void
id|snd_cs8427_free
c_func
(paren
id|snd_i2c_device_t
op_star
id|device
)paren
(brace
r_if
c_cond
(paren
id|device-&gt;private_data
)paren
id|snd_magic_kfree
c_func
(paren
id|device-&gt;private_data
)paren
suffix:semicolon
)brace
DECL|function|snd_cs8427_create
r_int
id|snd_cs8427_create
c_func
(paren
id|snd_i2c_bus_t
op_star
id|bus
comma
r_int
r_char
id|addr
comma
id|snd_i2c_device_t
op_star
op_star
id|r_cs8427
)paren
(brace
r_static
r_int
r_char
id|initvals1
(braket
)braket
op_assign
(brace
id|CS8427_REG_CONTROL1
op_or
id|CS8427_REG_AUTOINC
comma
multiline_comment|/* CS8427_REG_CLOCKSOURCE: RMCK to OMCK, no validity, disable mutes, TCBL=output */
id|CS8427_SWCLK
comma
multiline_comment|/* CS8427_REG_CONTROL2: hold last valid audio sample, RMCK=256*Fs, normal stereo operation */
l_int|0x00
comma
multiline_comment|/* CS8427_REG_DATAFLOW: output drivers normal operation, Tx&lt;=serial, Rx=&gt;serial */
id|CS8427_TXDSERIAL
op_or
id|CS8427_SPDAES3RECEIVER
comma
multiline_comment|/* CS8427_REG_CLOCKSOURCE: Run off, CMCK=256*Fs, output time base = OMCK, input time base =&n;&t;     covered input clock, recovered input clock source is Envy24 */
id|CS8427_INC
comma
multiline_comment|/* CS8427_REG_SERIALINPUT: Serial audio input port data format = I2S, 24-bit, 64*Fsi */
id|CS8427_SIDEL
op_or
id|CS8427_SILRPOL
comma
multiline_comment|/* CS8427_REG_SERIALOUTPUT: Serial audio output port data format = I2S, 24-bit, 64*Fsi */
id|CS8427_SODEL
op_or
id|CS8427_SOLRPOL
comma
)brace
suffix:semicolon
r_static
r_int
r_char
id|initvals2
(braket
)braket
op_assign
(brace
id|CS8427_REG_RECVERRMASK
op_or
id|CS8427_REG_AUTOINC
comma
multiline_comment|/* CS8427_REG_RECVERRMASK: unmask the input PLL clock, V, confidence, biphase, parity status bits */
multiline_comment|/* CS8427_UNLOCK | CS8427_V | CS8427_CONF | CS8427_BIP | CS8427_PAR,&n;&t;  Why setting CS8427_V causes clicks and glitches? */
id|CS8427_UNLOCK
op_or
id|CS8427_CONF
op_or
id|CS8427_BIP
op_or
id|CS8427_PAR
comma
multiline_comment|/* CS8427_REG_CSDATABUF:&n;&t;     Registers 32-55 window to CS buffer&n;&t;     Inhibit D-&gt;E transfers from overwriting first 5 bytes of CS data.&n;&t;     Inhibit D-&gt;E transfers (all) of CS data.&n;&t;     Allow E-&gt;F transfer of CS data.&n;&t;     One byte mode; both A/B channels get same written CB data.&n;&t;     A channel info is output to chip&squot;s EMPH* pin. */
id|CS8427_CBMR
op_or
id|CS8427_DETCI
comma
multiline_comment|/* CS8427_REG_UDATABUF:&n;&t;     Use internal buffer to transmit User (U) data.&n;&t;     Chip&squot;s U pin is an output.&n;&t;     Transmit all O&squot;s for user data.&n;&t;     Inhibit D-&gt;E transfers.&n;&t;     Inhibit E-&gt;F transfers. */
id|CS8427_UD
op_or
id|CS8427_EFTUI
op_or
id|CS8427_DETUI
comma
)brace
suffix:semicolon
r_int
id|err
suffix:semicolon
id|cs8427_t
op_star
id|chip
suffix:semicolon
id|snd_i2c_device_t
op_star
id|device
suffix:semicolon
r_int
r_char
id|buf
(braket
l_int|32
op_plus
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_i2c_device_create
c_func
(paren
id|bus
comma
l_string|&quot;CS8427&quot;
comma
id|CS8427_ADDR
op_or
(paren
id|addr
op_amp
l_int|7
)paren
comma
op_amp
id|device
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
id|chip
op_assign
id|device-&gt;private_data
op_assign
id|snd_magic_kcalloc
c_func
(paren
id|cs8427_t
comma
l_int|0
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|chip
op_eq
l_int|NULL
)paren
(brace
id|snd_i2c_device_free
c_func
(paren
id|device
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|device-&gt;private_free
op_assign
id|snd_cs8427_free
suffix:semicolon
id|snd_i2c_lock
c_func
(paren
id|bus
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_cs8427_reg_read
c_func
(paren
id|device
comma
id|CS8427_REG_ID_AND_VER
)paren
)paren
op_ne
id|CS8427_VER8427A
)paren
(brace
id|snd_i2c_unlock
c_func
(paren
id|bus
)paren
suffix:semicolon
id|snd_printk
c_func
(paren
l_string|&quot;unable to find CS8427 signature (expected 0x%x, read 0x%x), initialization is not completed&bslash;n&quot;
comma
id|CS8427_VER8427A
comma
id|err
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
multiline_comment|/* turn off run bit while making changes to configuration */
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_cs8427_reg_write
c_func
(paren
id|device
comma
id|CS8427_REG_CLOCKSOURCE
comma
l_int|0x00
)paren
)paren
OL
l_int|0
)paren
r_goto
id|__fail
suffix:semicolon
multiline_comment|/* send initial values */
id|memcpy
c_func
(paren
id|chip-&gt;regmap
op_plus
(paren
id|initvals1
(braket
l_int|0
)braket
op_amp
l_int|0x7f
)paren
comma
id|initvals1
op_plus
l_int|1
comma
l_int|6
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_i2c_sendbytes
c_func
(paren
id|device
comma
id|initvals1
comma
l_int|7
)paren
)paren
op_ne
l_int|7
)paren
(brace
id|err
op_assign
id|err
OL
l_int|0
ques
c_cond
id|err
suffix:colon
op_minus
id|EIO
suffix:semicolon
r_goto
id|__fail
suffix:semicolon
)brace
multiline_comment|/* Turn off CS8427 interrupt stuff that is not used in hardware */
id|memset
c_func
(paren
id|buf
comma
l_int|0
comma
l_int|7
)paren
suffix:semicolon
multiline_comment|/* from address 9 to 15 */
id|buf
(braket
l_int|0
)braket
op_assign
l_int|9
suffix:semicolon
multiline_comment|/* register */
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_i2c_sendbytes
c_func
(paren
id|device
comma
id|buf
comma
l_int|7
)paren
)paren
op_ne
l_int|7
)paren
r_goto
id|__fail
suffix:semicolon
multiline_comment|/* send transfer initialization sequence */
id|memcpy
c_func
(paren
id|chip-&gt;regmap
op_plus
(paren
id|initvals2
(braket
l_int|0
)braket
op_amp
l_int|0x7f
)paren
comma
id|initvals2
op_plus
l_int|1
comma
l_int|3
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_i2c_sendbytes
c_func
(paren
id|device
comma
id|initvals2
comma
l_int|4
)paren
)paren
op_ne
l_int|4
)paren
(brace
id|err
op_assign
id|err
OL
l_int|0
ques
c_cond
id|err
suffix:colon
op_minus
id|EIO
suffix:semicolon
r_goto
id|__fail
suffix:semicolon
)brace
multiline_comment|/* write default channel status bytes */
id|buf
(braket
l_int|0
)braket
op_assign
id|CS8427_REG_AUTOINC
op_or
id|CS8427_REG_CORU_DATABUF
suffix:semicolon
id|buf
(braket
l_int|1
)braket
op_assign
id|swapbits
c_func
(paren
(paren
r_int
r_char
)paren
(paren
id|SNDRV_PCM_DEFAULT_CON_SPDIF
op_rshift
l_int|0
)paren
)paren
suffix:semicolon
id|buf
(braket
l_int|2
)braket
op_assign
id|swapbits
c_func
(paren
(paren
r_int
r_char
)paren
(paren
id|SNDRV_PCM_DEFAULT_CON_SPDIF
op_rshift
l_int|8
)paren
)paren
suffix:semicolon
id|buf
(braket
l_int|3
)braket
op_assign
id|swapbits
c_func
(paren
(paren
r_int
r_char
)paren
(paren
id|SNDRV_PCM_DEFAULT_CON_SPDIF
op_rshift
l_int|16
)paren
)paren
suffix:semicolon
id|buf
(braket
l_int|4
)braket
op_assign
id|swapbits
c_func
(paren
(paren
r_int
r_char
)paren
(paren
id|SNDRV_PCM_DEFAULT_CON_SPDIF
op_rshift
l_int|24
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
id|buf
op_plus
l_int|5
comma
l_int|0
comma
r_sizeof
(paren
id|buf
)paren
op_minus
l_int|5
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|chip-&gt;playback.def_status
comma
id|buf
op_plus
l_int|1
comma
l_int|24
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|chip-&gt;playback.pcm_status
comma
id|buf
op_plus
l_int|1
comma
l_int|24
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_i2c_sendbytes
c_func
(paren
id|device
comma
id|buf
comma
l_int|33
)paren
)paren
op_ne
l_int|33
)paren
r_goto
id|__fail
suffix:semicolon
multiline_comment|/* turn on run bit and rock&squot;n&squot;roll */
id|chip-&gt;regmap
(braket
id|CS8427_REG_CLOCKSOURCE
)braket
op_assign
id|initvals1
(braket
l_int|4
)braket
op_or
id|CS8427_RUN
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_cs8427_reg_write
c_func
(paren
id|device
comma
id|CS8427_REG_CLOCKSOURCE
comma
id|chip-&gt;regmap
(braket
id|CS8427_REG_CLOCKSOURCE
)braket
)paren
)paren
OL
l_int|0
)paren
r_goto
id|__fail
suffix:semicolon
macro_line|#if 0&t;
singleline_comment|// it&squot;s nice for read tests
(brace
r_char
id|buf
(braket
l_int|128
)braket
suffix:semicolon
id|buf
(braket
l_int|0
)braket
op_assign
l_int|0x81
suffix:semicolon
id|snd_i2c_sendbytes
c_func
(paren
id|device
comma
id|buf
comma
l_int|1
)paren
suffix:semicolon
id|snd_i2c_readbytes
c_func
(paren
id|device
comma
id|buf
comma
l_int|127
)paren
suffix:semicolon
)brace
macro_line|#endif
id|snd_i2c_unlock
c_func
(paren
id|bus
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r_cs8427
)paren
op_star
id|r_cs8427
op_assign
id|device
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|__fail
suffix:colon
id|snd_i2c_unlock
c_func
(paren
id|bus
)paren
suffix:semicolon
id|snd_i2c_device_free
c_func
(paren
id|device
)paren
suffix:semicolon
r_return
id|err
OL
l_int|0
ques
c_cond
id|err
suffix:colon
op_minus
id|EIO
suffix:semicolon
)brace
DECL|function|snd_cs8427_in_status_info
r_static
r_int
id|snd_cs8427_in_status_info
c_func
(paren
id|snd_kcontrol_t
op_star
id|kcontrol
comma
id|snd_ctl_elem_info_t
op_star
id|uinfo
)paren
(brace
id|uinfo-&gt;type
op_assign
id|SNDRV_CTL_ELEM_TYPE_INTEGER
suffix:semicolon
id|uinfo-&gt;count
op_assign
l_int|1
suffix:semicolon
id|uinfo-&gt;value.integer.min
op_assign
l_int|0
suffix:semicolon
id|uinfo-&gt;value.integer.max
op_assign
l_int|255
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_cs8427_in_status_get
r_static
r_int
id|snd_cs8427_in_status_get
c_func
(paren
id|snd_kcontrol_t
op_star
id|kcontrol
comma
id|snd_ctl_elem_value_t
op_star
id|ucontrol
)paren
(brace
id|snd_i2c_device_t
op_star
id|device
op_assign
id|snd_kcontrol_chip
c_func
(paren
id|kcontrol
)paren
suffix:semicolon
r_int
id|data
suffix:semicolon
id|snd_i2c_lock
c_func
(paren
id|device-&gt;bus
)paren
suffix:semicolon
id|data
op_assign
id|snd_cs8427_reg_read
c_func
(paren
id|device
comma
l_int|15
)paren
suffix:semicolon
id|snd_i2c_unlock
c_func
(paren
id|device-&gt;bus
)paren
suffix:semicolon
r_if
c_cond
(paren
id|data
OL
l_int|0
)paren
r_return
id|data
suffix:semicolon
id|ucontrol-&gt;value.integer.value
(braket
l_int|0
)braket
op_assign
id|data
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_cs8427_spdif_info
r_static
r_int
id|snd_cs8427_spdif_info
c_func
(paren
id|snd_kcontrol_t
op_star
id|kcontrol
comma
id|snd_ctl_elem_info_t
op_star
id|uinfo
)paren
(brace
id|uinfo-&gt;type
op_assign
id|SNDRV_CTL_ELEM_TYPE_IEC958
suffix:semicolon
id|uinfo-&gt;count
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_cs8427_spdif_get
r_static
r_int
id|snd_cs8427_spdif_get
c_func
(paren
id|snd_kcontrol_t
op_star
id|kcontrol
comma
id|snd_ctl_elem_value_t
op_star
id|ucontrol
)paren
(brace
id|snd_i2c_device_t
op_star
id|device
op_assign
id|snd_kcontrol_chip
c_func
(paren
id|kcontrol
)paren
suffix:semicolon
id|cs8427_t
op_star
id|chip
op_assign
id|snd_magic_cast
c_func
(paren
id|cs8427_t
comma
id|device-&gt;private_data
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
id|snd_i2c_lock
c_func
(paren
id|device-&gt;bus
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|ucontrol-&gt;value.iec958.status
comma
id|chip-&gt;playback.def_status
comma
l_int|23
)paren
suffix:semicolon
id|snd_i2c_unlock
c_func
(paren
id|device-&gt;bus
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_cs8427_spdif_put
r_static
r_int
id|snd_cs8427_spdif_put
c_func
(paren
id|snd_kcontrol_t
op_star
id|kcontrol
comma
id|snd_ctl_elem_value_t
op_star
id|ucontrol
)paren
(brace
id|snd_i2c_device_t
op_star
id|device
op_assign
id|snd_kcontrol_chip
c_func
(paren
id|kcontrol
)paren
suffix:semicolon
id|cs8427_t
op_star
id|chip
op_assign
id|snd_magic_cast
c_func
(paren
id|cs8427_t
comma
id|device-&gt;private_data
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
r_int
r_char
op_star
id|status
op_assign
id|kcontrol-&gt;private_value
ques
c_cond
id|chip-&gt;playback.pcm_status
suffix:colon
id|chip-&gt;playback.def_status
suffix:semicolon
r_int
id|err
comma
id|change
suffix:semicolon
id|snd_i2c_lock
c_func
(paren
id|device-&gt;bus
)paren
suffix:semicolon
id|change
op_assign
id|memcmp
c_func
(paren
id|ucontrol-&gt;value.iec958.status
comma
id|status
comma
l_int|23
)paren
op_ne
l_int|0
suffix:semicolon
id|memcpy
c_func
(paren
id|status
comma
id|ucontrol-&gt;value.iec958.status
comma
l_int|23
)paren
suffix:semicolon
r_if
c_cond
(paren
id|change
op_logical_and
(paren
id|kcontrol-&gt;private_value
ques
c_cond
id|chip-&gt;playback.substream
op_ne
l_int|NULL
suffix:colon
id|chip-&gt;playback.substream
op_eq
l_int|NULL
)paren
)paren
(brace
id|err
op_assign
id|snd_cs8427_send_corudata
c_func
(paren
id|device
comma
l_int|0
comma
id|status
comma
l_int|23
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
id|change
op_assign
id|err
suffix:semicolon
)brace
id|snd_i2c_unlock
c_func
(paren
id|device-&gt;bus
)paren
suffix:semicolon
r_return
id|change
suffix:semicolon
)brace
DECL|function|snd_cs8427_spdif_mask_info
r_static
r_int
id|snd_cs8427_spdif_mask_info
c_func
(paren
id|snd_kcontrol_t
op_star
id|kcontrol
comma
id|snd_ctl_elem_info_t
op_star
id|uinfo
)paren
(brace
id|uinfo-&gt;type
op_assign
id|SNDRV_CTL_ELEM_TYPE_IEC958
suffix:semicolon
id|uinfo-&gt;count
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_cs8427_spdif_mask_get
r_static
r_int
id|snd_cs8427_spdif_mask_get
c_func
(paren
id|snd_kcontrol_t
op_star
id|kcontrol
comma
id|snd_ctl_elem_value_t
op_star
id|ucontrol
)paren
(brace
id|memset
c_func
(paren
id|ucontrol-&gt;value.iec958.status
comma
l_int|0xff
comma
l_int|23
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|CONTROLS
mdefine_line|#define CONTROLS (sizeof(snd_cs8427_iec958_controls)/sizeof(snd_kcontrol_new_t))
DECL|variable|snd_cs8427_iec958_controls
r_static
id|snd_kcontrol_new_t
id|snd_cs8427_iec958_controls
(braket
)braket
op_assign
(brace
(brace
dot
id|iface
op_assign
id|SNDRV_CTL_ELEM_IFACE_PCM
comma
dot
id|info
op_assign
id|snd_cs8427_in_status_info
comma
dot
id|name
op_assign
l_string|&quot;IEC958 CS8427 Input Status&quot;
comma
dot
id|access
op_assign
id|SNDRV_CTL_ELEM_ACCESS_READ
op_or
id|SNDRV_CTL_ELEM_ACCESS_VOLATILE
comma
dot
id|get
op_assign
id|snd_cs8427_in_status_get
comma
)brace
comma
(brace
dot
id|access
op_assign
id|SNDRV_CTL_ELEM_ACCESS_READ
comma
dot
id|iface
op_assign
id|SNDRV_CTL_ELEM_IFACE_PCM
comma
dot
id|name
op_assign
id|SNDRV_CTL_NAME_IEC958
c_func
(paren
l_string|&quot;&quot;
comma
id|PLAYBACK
comma
id|MASK
)paren
comma
dot
id|info
op_assign
id|snd_cs8427_spdif_mask_info
comma
dot
id|get
op_assign
id|snd_cs8427_spdif_mask_get
comma
)brace
comma
(brace
dot
id|iface
op_assign
id|SNDRV_CTL_ELEM_IFACE_PCM
comma
dot
id|name
op_assign
id|SNDRV_CTL_NAME_IEC958
c_func
(paren
l_string|&quot;&quot;
comma
id|PLAYBACK
comma
id|DEFAULT
)paren
comma
dot
id|info
op_assign
id|snd_cs8427_spdif_info
comma
dot
id|get
op_assign
id|snd_cs8427_spdif_get
comma
dot
id|put
op_assign
id|snd_cs8427_spdif_put
comma
dot
id|private_value
op_assign
l_int|0
)brace
comma
(brace
dot
id|access
op_assign
id|SNDRV_CTL_ELEM_ACCESS_READWRITE
op_or
id|SNDRV_CTL_ELEM_ACCESS_INACTIVE
comma
dot
id|iface
op_assign
id|SNDRV_CTL_ELEM_IFACE_PCM
comma
dot
id|name
op_assign
id|SNDRV_CTL_NAME_IEC958
c_func
(paren
l_string|&quot;&quot;
comma
id|PLAYBACK
comma
id|PCM_STREAM
)paren
comma
dot
id|info
op_assign
id|snd_cs8427_spdif_info
comma
dot
id|get
op_assign
id|snd_cs8427_spdif_get
comma
dot
id|put
op_assign
id|snd_cs8427_spdif_put
comma
dot
id|private_value
op_assign
l_int|1
)brace
)brace
suffix:semicolon
DECL|function|snd_cs8427_iec958_build
r_int
id|snd_cs8427_iec958_build
c_func
(paren
id|snd_i2c_device_t
op_star
id|cs8427
comma
id|snd_pcm_substream_t
op_star
id|play_substream
comma
id|snd_pcm_substream_t
op_star
id|cap_substream
)paren
(brace
id|cs8427_t
op_star
id|chip
op_assign
id|snd_magic_cast
c_func
(paren
id|cs8427_t
comma
id|cs8427-&gt;private_data
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
id|snd_kcontrol_t
op_star
id|kctl
suffix:semicolon
r_int
id|idx
comma
id|err
suffix:semicolon
id|snd_assert
c_func
(paren
id|play_substream
op_logical_and
id|cap_substream
comma
r_return
op_minus
id|EINVAL
)paren
suffix:semicolon
r_for
c_loop
(paren
id|idx
op_assign
l_int|0
suffix:semicolon
id|idx
OL
id|CONTROLS
suffix:semicolon
id|idx
op_increment
)paren
(brace
id|kctl
op_assign
id|snd_ctl_new1
c_func
(paren
op_amp
id|snd_cs8427_iec958_controls
(braket
id|idx
)braket
comma
id|cs8427
)paren
suffix:semicolon
r_if
c_cond
(paren
id|kctl
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|kctl-&gt;id.device
op_assign
id|play_substream-&gt;pcm-&gt;device
suffix:semicolon
id|kctl-&gt;id.subdevice
op_assign
id|play_substream-&gt;number
suffix:semicolon
id|err
op_assign
id|snd_ctl_add
c_func
(paren
id|cs8427-&gt;bus-&gt;card
comma
id|kctl
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|kctl-&gt;id.name
comma
id|SNDRV_CTL_NAME_IEC958
c_func
(paren
l_string|&quot;&quot;
comma
id|PLAYBACK
comma
id|PCM_STREAM
)paren
)paren
)paren
id|chip-&gt;playback.pcm_ctl
op_assign
id|kctl
suffix:semicolon
)brace
id|snd_assert
c_func
(paren
id|chip-&gt;playback.pcm_ctl
comma
r_return
op_minus
id|EIO
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_cs8427_iec958_active
r_int
id|snd_cs8427_iec958_active
c_func
(paren
id|snd_i2c_device_t
op_star
id|cs8427
comma
r_int
id|active
)paren
(brace
id|cs8427_t
op_star
id|chip
suffix:semicolon
id|snd_assert
c_func
(paren
id|cs8427
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
id|chip
op_assign
id|snd_magic_cast
c_func
(paren
id|cs8427_t
comma
id|cs8427-&gt;private_data
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
r_if
c_cond
(paren
id|active
)paren
id|memcpy
c_func
(paren
id|chip-&gt;playback.pcm_status
comma
id|chip-&gt;playback.def_status
comma
l_int|24
)paren
suffix:semicolon
id|chip-&gt;playback.pcm_ctl-&gt;access
op_and_assign
op_complement
id|SNDRV_CTL_ELEM_ACCESS_INACTIVE
suffix:semicolon
id|snd_ctl_notify
c_func
(paren
id|cs8427-&gt;bus-&gt;card
comma
id|SNDRV_CTL_EVENT_MASK_VALUE
op_or
id|SNDRV_CTL_EVENT_MASK_INFO
comma
op_amp
id|chip-&gt;playback.pcm_ctl-&gt;id
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_cs8427_iec958_pcm
r_int
id|snd_cs8427_iec958_pcm
c_func
(paren
id|snd_i2c_device_t
op_star
id|cs8427
comma
r_int
r_int
id|rate
)paren
(brace
id|cs8427_t
op_star
id|chip
suffix:semicolon
r_char
op_star
id|status
suffix:semicolon
r_int
id|err
suffix:semicolon
id|snd_assert
c_func
(paren
id|cs8427
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
id|chip
op_assign
id|snd_magic_cast
c_func
(paren
id|cs8427_t
comma
id|cs8427-&gt;private_data
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
id|status
op_assign
id|chip-&gt;playback.pcm_status
suffix:semicolon
id|snd_i2c_lock
c_func
(paren
id|cs8427-&gt;bus
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
(braket
l_int|0
)braket
op_amp
id|IEC958_AES0_PROFESSIONAL
)paren
(brace
id|status
(braket
l_int|0
)braket
op_and_assign
op_complement
id|IEC958_AES0_PRO_FS
suffix:semicolon
r_switch
c_cond
(paren
id|rate
)paren
(brace
r_case
l_int|32000
suffix:colon
id|status
(braket
l_int|0
)braket
op_or_assign
id|IEC958_AES0_PRO_FS_32000
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|44100
suffix:colon
id|status
(braket
l_int|0
)braket
op_or_assign
id|IEC958_AES0_PRO_FS_44100
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|48000
suffix:colon
id|status
(braket
l_int|0
)braket
op_or_assign
id|IEC958_AES0_PRO_FS_48000
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|status
(braket
l_int|0
)braket
op_or_assign
id|IEC958_AES0_PRO_FS_NOTID
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_else
(brace
id|status
(braket
l_int|3
)braket
op_and_assign
op_complement
id|IEC958_AES3_CON_FS
suffix:semicolon
r_switch
c_cond
(paren
id|rate
)paren
(brace
r_case
l_int|32000
suffix:colon
id|status
(braket
l_int|3
)braket
op_or_assign
id|IEC958_AES3_CON_FS_32000
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|44100
suffix:colon
id|status
(braket
l_int|3
)braket
op_or_assign
id|IEC958_AES3_CON_FS_44100
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|48000
suffix:colon
id|status
(braket
l_int|3
)braket
op_or_assign
id|IEC958_AES3_CON_FS_48000
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|err
op_assign
id|snd_cs8427_send_corudata
c_func
(paren
id|cs8427
comma
l_int|0
comma
id|status
comma
l_int|23
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OG
l_int|0
)paren
id|snd_ctl_notify
c_func
(paren
id|cs8427-&gt;bus-&gt;card
comma
id|SNDRV_CTL_EVENT_MASK_VALUE
comma
op_amp
id|chip-&gt;playback.pcm_ctl-&gt;id
)paren
suffix:semicolon
id|snd_i2c_unlock
c_func
(paren
id|cs8427-&gt;bus
)paren
suffix:semicolon
r_return
id|err
OL
l_int|0
ques
c_cond
id|err
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|variable|snd_cs8427_detect
id|EXPORT_SYMBOL
c_func
(paren
id|snd_cs8427_detect
)paren
suffix:semicolon
DECL|variable|snd_cs8427_create
id|EXPORT_SYMBOL
c_func
(paren
id|snd_cs8427_create
)paren
suffix:semicolon
DECL|variable|snd_cs8427_iec958_build
id|EXPORT_SYMBOL
c_func
(paren
id|snd_cs8427_iec958_build
)paren
suffix:semicolon
DECL|variable|snd_cs8427_iec958_active
id|EXPORT_SYMBOL
c_func
(paren
id|snd_cs8427_iec958_active
)paren
suffix:semicolon
DECL|variable|snd_cs8427_iec958_pcm
id|EXPORT_SYMBOL
c_func
(paren
id|snd_cs8427_iec958_pcm
)paren
suffix:semicolon
eof
