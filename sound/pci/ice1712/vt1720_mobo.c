multiline_comment|/*&n; *   ALSA driver for VT1720/VT1724 (Envy24PT/Envy24HT)&n; *&n; *   Lowlevel functions for VT1720-based motherboards&n; *&n; *&t;Copyright (c) 2004 Takashi Iwai &lt;tiwai@suse.de&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &quot;ice1712.h&quot;
macro_line|#include &quot;vt1720_mobo.h&quot;
DECL|function|k8x800_init
r_static
r_int
id|__devinit
id|k8x800_init
c_func
(paren
id|ice1712_t
op_star
id|ice
)paren
(brace
id|ice-&gt;vt1720
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* VT1616 codec */
id|ice-&gt;num_total_dacs
op_assign
l_int|6
suffix:semicolon
id|ice-&gt;num_total_adcs
op_assign
l_int|2
suffix:semicolon
multiline_comment|/* WM8728 codec */
multiline_comment|/* FIXME: TODO */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|k8x800_add_controls
r_static
r_int
id|__devinit
id|k8x800_add_controls
c_func
(paren
id|ice1712_t
op_star
id|ice
)paren
(brace
multiline_comment|/* FIXME: needs some quirks for VT1616? */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* EEPROM image */
DECL|variable|__devinitdata
r_static
r_int
r_char
id|k8x800_eeprom
(braket
)braket
id|__devinitdata
op_assign
(brace
l_int|0x01
comma
multiline_comment|/* SYSCONF: clock 256, 1ADC, 2DACs */
l_int|0x02
comma
multiline_comment|/* ACLINK: ACLINK, packed */
l_int|0x00
comma
multiline_comment|/* I2S: - */
l_int|0x00
comma
multiline_comment|/* SPDIF: - */
l_int|0xff
comma
multiline_comment|/* GPIO_DIR */
l_int|0xff
comma
multiline_comment|/* GPIO_DIR1 */
l_int|0x00
comma
multiline_comment|/* - */
l_int|0xff
comma
multiline_comment|/* GPIO_MASK */
l_int|0xff
comma
multiline_comment|/* GPIO_MASK1 */
l_int|0x00
comma
multiline_comment|/* - */
l_int|0x00
comma
multiline_comment|/* GPIO_STATE */
l_int|0x00
comma
multiline_comment|/* GPIO_STATE1 */
l_int|0x00
comma
multiline_comment|/* - */
)brace
suffix:semicolon
multiline_comment|/* entry point */
DECL|variable|__devinitdata
r_struct
id|snd_ice1712_card_info
id|snd_vt1720_mobo_cards
(braket
)braket
id|__devinitdata
op_assign
(brace
(brace
dot
id|subvendor
op_assign
id|VT1720_SUBDEVICE_K8X800
comma
dot
id|name
op_assign
l_string|&quot;Albatron K8X800 Pro II&quot;
comma
dot
id|model
op_assign
l_string|&quot;k8x800&quot;
comma
dot
id|chip_init
op_assign
id|k8x800_init
comma
dot
id|build_controls
op_assign
id|k8x800_add_controls
comma
dot
id|eeprom_size
op_assign
r_sizeof
(paren
id|k8x800_eeprom
)paren
comma
dot
id|eeprom_data
op_assign
id|k8x800_eeprom
comma
)brace
comma
(brace
dot
id|subvendor
op_assign
id|VT1720_SUBDEVICE_ZNF3_150
comma
dot
id|name
op_assign
l_string|&quot;Chaintech ZNF3-150&quot;
comma
multiline_comment|/* identical with k8x800 */
dot
id|chip_init
op_assign
id|k8x800_init
comma
dot
id|build_controls
op_assign
id|k8x800_add_controls
comma
dot
id|eeprom_size
op_assign
r_sizeof
(paren
id|k8x800_eeprom
)paren
comma
dot
id|eeprom_data
op_assign
id|k8x800_eeprom
comma
)brace
comma
(brace
dot
id|subvendor
op_assign
id|VT1720_SUBDEVICE_ZNF3_250
comma
dot
id|name
op_assign
l_string|&quot;Chaintech ZNF3-250&quot;
comma
multiline_comment|/* identical with k8x800 */
dot
id|chip_init
op_assign
id|k8x800_init
comma
dot
id|build_controls
op_assign
id|k8x800_add_controls
comma
dot
id|eeprom_size
op_assign
r_sizeof
(paren
id|k8x800_eeprom
)paren
comma
dot
id|eeprom_data
op_assign
id|k8x800_eeprom
comma
)brace
comma
(brace
dot
id|subvendor
op_assign
id|VT1720_SUBDEVICE_9CJS
comma
dot
id|name
op_assign
l_string|&quot;Chaintech 9CJS&quot;
comma
multiline_comment|/* identical with k8x800 */
dot
id|chip_init
op_assign
id|k8x800_init
comma
dot
id|build_controls
op_assign
id|k8x800_add_controls
comma
dot
id|eeprom_size
op_assign
r_sizeof
(paren
id|k8x800_eeprom
)paren
comma
dot
id|eeprom_data
op_assign
id|k8x800_eeprom
comma
)brace
comma
(brace
)brace
multiline_comment|/* terminator */
)brace
suffix:semicolon
eof
