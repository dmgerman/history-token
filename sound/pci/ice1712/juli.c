multiline_comment|/*&n; *   ALSA driver for ICEnsemble VT1724 (Envy24HT)&n; *&n; *   Lowlevel functions for ESI Juli@ cards&n; *&n; *&t;Copyright (c) 2004 Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &quot;ice1712.h&quot;
macro_line|#include &quot;envy24ht.h&quot;
macro_line|#include &quot;juli.h&quot;
multiline_comment|/*&n; * chip addresses on I2C bus&n; */
DECL|macro|AK4114_ADDR
mdefine_line|#define AK4114_ADDR&t;&t;0x20&t;&t;/* S/PDIF receiver */
DECL|macro|AK4358_ADDR
mdefine_line|#define AK4358_ADDR&t;&t;0x22&t;&t;/* DAC */
multiline_comment|/*&n; * GPIO pins&n; */
DECL|macro|GPIO_FREQ_MASK
mdefine_line|#define GPIO_FREQ_MASK&t;&t;(3&lt;&lt;0)
DECL|macro|GPIO_FREQ_32KHZ
mdefine_line|#define GPIO_FREQ_32KHZ&t;&t;(0&lt;&lt;0)
DECL|macro|GPIO_FREQ_44KHZ
mdefine_line|#define GPIO_FREQ_44KHZ&t;&t;(1&lt;&lt;0)
DECL|macro|GPIO_FREQ_48KHZ
mdefine_line|#define GPIO_FREQ_48KHZ&t;&t;(2&lt;&lt;0)
DECL|macro|GPIO_MULTI_MASK
mdefine_line|#define GPIO_MULTI_MASK&t;&t;(3&lt;&lt;2)
DECL|macro|GPIO_MULTI_4X
mdefine_line|#define GPIO_MULTI_4X&t;&t;(0&lt;&lt;2)
DECL|macro|GPIO_MULTI_2X
mdefine_line|#define GPIO_MULTI_2X&t;&t;(1&lt;&lt;2)
DECL|macro|GPIO_MULTI_1X
mdefine_line|#define GPIO_MULTI_1X&t;&t;(2&lt;&lt;2)&t;&t;/* also external */
DECL|macro|GPIO_MULTI_HALF
mdefine_line|#define GPIO_MULTI_HALF&t;&t;(3&lt;&lt;2)
DECL|macro|GPIO_INTERNAL_CLOCK
mdefine_line|#define GPIO_INTERNAL_CLOCK&t;(1&lt;&lt;4)
DECL|macro|GPIO_ANALOG_PRESENT
mdefine_line|#define GPIO_ANALOG_PRESENT&t;(1&lt;&lt;5)&t;&t;/* RO only: 0 = present */
DECL|macro|GPIO_RXMCLK_SEL
mdefine_line|#define GPIO_RXMCLK_SEL&t;&t;(1&lt;&lt;7)&t;&t;/* must be 0 */
DECL|macro|GPIO_AK5385A_CKS0
mdefine_line|#define GPIO_AK5385A_CKS0&t;(1&lt;&lt;8)
DECL|macro|GPIO_AK5385A_DFS0
mdefine_line|#define GPIO_AK5385A_DFS0&t;(1&lt;&lt;9)&t;&t;/* swapped with DFS1 according doc? */
DECL|macro|GPIO_AK5385A_DFS1
mdefine_line|#define GPIO_AK5385A_DFS1&t;(1&lt;&lt;10)
DECL|macro|GPIO_DIGOUT_MONITOR
mdefine_line|#define GPIO_DIGOUT_MONITOR&t;(1&lt;&lt;11)&t;&t;/* 1 = active */
DECL|macro|GPIO_DIGIN_MONITOR
mdefine_line|#define GPIO_DIGIN_MONITOR&t;(1&lt;&lt;12)&t;&t;/* 1 = active */
DECL|macro|GPIO_ANAIN_MONITOR
mdefine_line|#define GPIO_ANAIN_MONITOR&t;(1&lt;&lt;13)&t;&t;/* 1 = active */
DECL|macro|GPIO_AK5385A_MCLK
mdefine_line|#define GPIO_AK5385A_MCLK&t;(1&lt;&lt;14)&t;&t;/* must be 0 */
DECL|macro|GPIO_MUTE_CONTROL
mdefine_line|#define GPIO_MUTE_CONTROL&t;(1&lt;&lt;15)&t;&t;/* 0 = off, 1 = on */
DECL|function|juli_ak4114_write
r_static
r_void
id|juli_ak4114_write
c_func
(paren
r_void
op_star
id|private_data
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
id|snd_vt1724_write_i2c
c_func
(paren
(paren
id|ice1712_t
op_star
)paren
id|private_data
comma
id|AK4114_ADDR
comma
id|reg
comma
id|val
)paren
suffix:semicolon
)brace
DECL|function|juli_ak4114_read
r_static
r_int
r_char
id|juli_ak4114_read
c_func
(paren
r_void
op_star
id|private_data
comma
r_int
r_char
id|reg
)paren
(brace
r_return
id|snd_vt1724_read_i2c
c_func
(paren
(paren
id|ice1712_t
op_star
)paren
id|private_data
comma
id|AK4114_ADDR
comma
id|reg
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * AK4358 section&n; */
DECL|function|juli_akm_lock
r_static
r_void
id|juli_akm_lock
c_func
(paren
id|akm4xxx_t
op_star
id|ak
comma
r_int
id|chip
)paren
(brace
)brace
DECL|function|juli_akm_unlock
r_static
r_void
id|juli_akm_unlock
c_func
(paren
id|akm4xxx_t
op_star
id|ak
comma
r_int
id|chip
)paren
(brace
)brace
DECL|function|juli_akm_write
r_static
r_void
id|juli_akm_write
c_func
(paren
id|akm4xxx_t
op_star
id|ak
comma
r_int
id|chip
comma
r_int
r_char
id|addr
comma
r_int
r_char
id|data
)paren
(brace
id|ice1712_t
op_star
id|ice
op_assign
id|ak-&gt;private_data
(braket
l_int|0
)braket
suffix:semicolon
id|snd_assert
c_func
(paren
id|chip
op_eq
l_int|0
comma
r_return
)paren
suffix:semicolon
id|snd_vt1724_write_i2c
c_func
(paren
id|ice
comma
id|AK4358_ADDR
comma
id|addr
comma
id|data
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * change the rate of envy24HT, AK4358&n; */
DECL|function|juli_akm_set_rate_val
r_static
r_void
id|juli_akm_set_rate_val
c_func
(paren
id|akm4xxx_t
op_star
id|ak
comma
r_int
r_int
id|rate
)paren
(brace
r_int
r_char
id|old
comma
id|tmp
comma
id|dfs
suffix:semicolon
r_if
c_cond
(paren
id|rate
op_eq
l_int|0
)paren
multiline_comment|/* no hint - S/PDIF input is master, simply return */
r_return
suffix:semicolon
multiline_comment|/* adjust DFS on codecs */
r_if
c_cond
(paren
id|rate
OG
l_int|96000
)paren
id|dfs
op_assign
l_int|2
suffix:semicolon
r_else
r_if
c_cond
(paren
id|rate
OG
l_int|48000
)paren
id|dfs
op_assign
l_int|1
suffix:semicolon
r_else
id|dfs
op_assign
l_int|0
suffix:semicolon
id|tmp
op_assign
id|snd_akm4xxx_get
c_func
(paren
id|ak
comma
l_int|0
comma
l_int|2
)paren
suffix:semicolon
id|old
op_assign
(paren
id|tmp
op_rshift
l_int|4
)paren
op_amp
l_int|0x03
suffix:semicolon
r_if
c_cond
(paren
id|old
op_eq
id|dfs
)paren
r_return
suffix:semicolon
multiline_comment|/* reset DFS */
id|snd_akm4xxx_reset
c_func
(paren
id|ak
comma
l_int|1
)paren
suffix:semicolon
id|tmp
op_assign
id|snd_akm4xxx_get
c_func
(paren
id|ak
comma
l_int|0
comma
l_int|2
)paren
suffix:semicolon
id|tmp
op_and_assign
op_complement
(paren
l_int|0x03
op_lshift
l_int|4
)paren
suffix:semicolon
id|tmp
op_or_assign
id|dfs
op_lshift
l_int|4
suffix:semicolon
id|snd_akm4xxx_set
c_func
(paren
id|ak
comma
l_int|0
comma
l_int|2
comma
id|tmp
)paren
suffix:semicolon
id|snd_akm4xxx_reset
c_func
(paren
id|ak
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|variable|__devinitdata
r_static
id|akm4xxx_t
id|akm_juli_dac
id|__devinitdata
op_assign
(brace
dot
id|type
op_assign
id|SND_AK4358
comma
dot
id|num_dacs
op_assign
l_int|2
comma
dot
id|ops
op_assign
(brace
dot
id|lock
op_assign
id|juli_akm_lock
comma
dot
id|unlock
op_assign
id|juli_akm_unlock
comma
dot
id|write
op_assign
id|juli_akm_write
comma
dot
id|set_rate_val
op_assign
id|juli_akm_set_rate_val
)brace
)brace
suffix:semicolon
DECL|function|juli_add_controls
r_static
r_int
id|__devinit
id|juli_add_controls
c_func
(paren
id|ice1712_t
op_star
id|ice
)paren
(brace
r_return
id|snd_ice1712_akm4xxx_build_controls
c_func
(paren
id|ice
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * initialize the chip&n; */
DECL|function|juli_init
r_static
r_int
id|__devinit
id|juli_init
c_func
(paren
id|ice1712_t
op_star
id|ice
)paren
(brace
r_static
r_int
r_char
id|ak4114_init_vals
(braket
)braket
op_assign
(brace
multiline_comment|/* AK4117_REG_PWRDN */
id|AK4114_RST
op_or
id|AK4114_PWN
op_or
id|AK4114_OCKS0
op_or
id|AK4114_OCKS1
comma
multiline_comment|/* AK4114_REQ_FORMAT */
id|AK4114_DIF_I24I2S
comma
multiline_comment|/* AK4114_REG_IO0 */
id|AK4114_TX1E
comma
multiline_comment|/* AK4114_REG_IO1 */
id|AK4114_EFH_1024
op_or
id|AK4114_DIT
op_or
id|AK4114_IPS
c_func
(paren
l_int|1
)paren
comma
multiline_comment|/* AK4114_REG_INT0_MASK */
l_int|0
comma
multiline_comment|/* AK4114_REG_INT1_MASK */
l_int|0
)brace
suffix:semicolon
r_static
r_int
r_char
id|ak4114_init_txcsb
(braket
)braket
op_assign
(brace
l_int|0x41
comma
l_int|0x02
comma
l_int|0x2c
comma
l_int|0x00
comma
l_int|0x00
)brace
suffix:semicolon
r_int
id|err
suffix:semicolon
id|akm4xxx_t
op_star
id|ak
suffix:semicolon
macro_line|#if 0
r_for
c_loop
(paren
id|err
op_assign
l_int|0
suffix:semicolon
id|err
OL
l_int|0x20
suffix:semicolon
id|err
op_increment
)paren
id|juli_ak4114_read
c_func
(paren
id|ice
comma
id|err
)paren
suffix:semicolon
id|juli_ak4114_write
c_func
(paren
id|ice
comma
l_int|0
comma
l_int|0x0f
)paren
suffix:semicolon
id|juli_ak4114_read
c_func
(paren
id|ice
comma
l_int|0
)paren
suffix:semicolon
id|juli_ak4114_read
c_func
(paren
id|ice
comma
l_int|1
)paren
suffix:semicolon
macro_line|#endif
id|err
op_assign
id|snd_ak4114_create
c_func
(paren
id|ice-&gt;card
comma
id|juli_ak4114_read
comma
id|juli_ak4114_write
comma
id|ak4114_init_vals
comma
id|ak4114_init_txcsb
comma
id|ice
comma
op_amp
id|ice-&gt;spec.juli.ak4114
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
id|ice-&gt;spec.juli.analog
op_assign
id|ice-&gt;gpio
dot
id|get_data
c_func
(paren
id|ice
)paren
op_amp
id|GPIO_ANALOG_PRESENT
suffix:semicolon
r_if
c_cond
(paren
id|ice-&gt;spec.juli.analog
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;juli@: analog I/O detected&bslash;n&quot;
)paren
suffix:semicolon
id|ice-&gt;num_total_dacs
op_assign
l_int|2
suffix:semicolon
id|ice-&gt;num_total_adcs
op_assign
l_int|2
suffix:semicolon
id|ak
op_assign
id|ice-&gt;akm
op_assign
id|kcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
id|akm4xxx_t
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ak
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|ice-&gt;akm_codecs
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_ice1712_akm4xxx_init
c_func
(paren
id|ak
comma
op_amp
id|akm_juli_dac
comma
l_int|NULL
comma
id|ice
)paren
)paren
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
multiline_comment|/*&n; * Juli@ boards don&squot;t provide the EEPROM data except for the vendor IDs.&n; * hence the driver needs to sets up it properly.&n; */
DECL|variable|__devinitdata
r_static
r_int
r_char
id|juli_eeprom
(braket
)braket
id|__devinitdata
op_assign
(brace
l_int|0x20
comma
multiline_comment|/* SYSCONF: clock 512, mpu401, 1xADC, 1xDACs */
l_int|0x80
comma
multiline_comment|/* ACLINK: I2S */
l_int|0xf8
comma
multiline_comment|/* I2S: vol, 96k, 24bit, 192k */
l_int|0xc3
comma
multiline_comment|/* SPDIF: out-en, out-int, spdif-in */
l_int|0x9f
comma
multiline_comment|/* GPIO_DIR */
l_int|0xff
comma
multiline_comment|/* GPIO_DIR1 */
l_int|0x7f
comma
multiline_comment|/* GPIO_DIR2 */
l_int|0x9f
comma
multiline_comment|/* GPIO_MASK */
l_int|0xff
comma
multiline_comment|/* GPIO_MASK1 */
l_int|0x7f
comma
multiline_comment|/* GPIO_MASK2 */
l_int|0x16
comma
multiline_comment|/* GPIO_STATE: internal clock, multiple 1x, 48kHz */
l_int|0x80
comma
multiline_comment|/* GPIO_STATE1: mute */
l_int|0x00
comma
multiline_comment|/* GPIO_STATE2 */
)brace
suffix:semicolon
multiline_comment|/* entry point */
DECL|variable|__devinitdata
r_struct
id|snd_ice1712_card_info
id|snd_vt1724_juli_cards
(braket
)braket
id|__devinitdata
op_assign
(brace
(brace
dot
id|subvendor
op_assign
id|VT1724_SUBDEVICE_JULI
comma
dot
id|name
op_assign
l_string|&quot;ESI Juli@&quot;
comma
dot
id|model
op_assign
l_string|&quot;juli&quot;
comma
dot
id|chip_init
op_assign
id|juli_init
comma
dot
id|build_controls
op_assign
id|juli_add_controls
comma
dot
id|eeprom_size
op_assign
r_sizeof
(paren
id|juli_eeprom
)paren
comma
dot
id|eeprom_data
op_assign
id|juli_eeprom
comma
)brace
comma
(brace
)brace
multiline_comment|/* terminator */
)brace
suffix:semicolon
eof
