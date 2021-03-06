multiline_comment|/*&n; * $Id: ir-kbd-gpio.c,v 1.12 2005/02/22 12:28:40 kraxel Exp $&n; *&n; * Copyright (c) 2003 Gerd Knorr&n; * Copyright (c) 2003 Pavel Machek&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/input.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;media/ir-common.h&gt;
macro_line|#include &quot;bttv.h&quot;
multiline_comment|/* ---------------------------------------------------------------------- */
DECL|variable|ir_codes_avermedia
r_static
id|IR_KEYTAB_TYPE
id|ir_codes_avermedia
(braket
id|IR_KEYTAB_SIZE
)braket
op_assign
(brace
(braket
l_int|34
)braket
op_assign
id|KEY_KP0
comma
(braket
l_int|40
)braket
op_assign
id|KEY_KP1
comma
(braket
l_int|24
)braket
op_assign
id|KEY_KP2
comma
(braket
l_int|56
)braket
op_assign
id|KEY_KP3
comma
(braket
l_int|36
)braket
op_assign
id|KEY_KP4
comma
(braket
l_int|20
)braket
op_assign
id|KEY_KP5
comma
(braket
l_int|52
)braket
op_assign
id|KEY_KP6
comma
(braket
l_int|44
)braket
op_assign
id|KEY_KP7
comma
(braket
l_int|28
)braket
op_assign
id|KEY_KP8
comma
(braket
l_int|60
)braket
op_assign
id|KEY_KP9
comma
(braket
l_int|48
)braket
op_assign
id|KEY_EJECTCD
comma
singleline_comment|// Unmarked on my controller
(braket
l_int|0
)braket
op_assign
id|KEY_POWER
comma
(braket
l_int|18
)braket
op_assign
id|BTN_LEFT
comma
singleline_comment|// DISPLAY/L
(braket
l_int|50
)braket
op_assign
id|BTN_RIGHT
comma
singleline_comment|// LOOP/R
(braket
l_int|10
)braket
op_assign
id|KEY_MUTE
comma
(braket
l_int|38
)braket
op_assign
id|KEY_RECORD
comma
(braket
l_int|22
)braket
op_assign
id|KEY_PAUSE
comma
(braket
l_int|54
)braket
op_assign
id|KEY_STOP
comma
(braket
l_int|30
)braket
op_assign
id|KEY_VOLUMEDOWN
comma
(braket
l_int|62
)braket
op_assign
id|KEY_VOLUMEUP
comma
(braket
l_int|32
)braket
op_assign
id|KEY_TUNER
comma
singleline_comment|// TV/FM
(braket
l_int|16
)braket
op_assign
id|KEY_CD
comma
(braket
l_int|8
)braket
op_assign
id|KEY_VIDEO
comma
(braket
l_int|4
)braket
op_assign
id|KEY_AUDIO
comma
(braket
l_int|12
)braket
op_assign
id|KEY_ZOOM
comma
singleline_comment|// full screen
(braket
l_int|2
)braket
op_assign
id|KEY_INFO
comma
singleline_comment|// preview
(braket
l_int|42
)braket
op_assign
id|KEY_SEARCH
comma
singleline_comment|// autoscan
(braket
l_int|26
)braket
op_assign
id|KEY_STOP
comma
singleline_comment|// freeze
(braket
l_int|58
)braket
op_assign
id|KEY_RECORD
comma
singleline_comment|// capture
(braket
l_int|6
)braket
op_assign
id|KEY_PLAY
comma
singleline_comment|// unmarked
(braket
l_int|46
)braket
op_assign
id|KEY_RED
comma
singleline_comment|// unmarked
(braket
l_int|14
)braket
op_assign
id|KEY_GREEN
comma
singleline_comment|// unmarked
(braket
l_int|33
)braket
op_assign
id|KEY_YELLOW
comma
singleline_comment|// unmarked
(braket
l_int|17
)braket
op_assign
id|KEY_CHANNELDOWN
comma
(braket
l_int|49
)braket
op_assign
id|KEY_CHANNELUP
comma
(braket
l_int|1
)braket
op_assign
id|KEY_BLUE
comma
singleline_comment|// unmarked
)brace
suffix:semicolon
multiline_comment|/* Matt Jesson &lt;dvb@jesson.eclipse.co.uk */
DECL|variable|ir_codes_avermedia_dvbt
r_static
id|IR_KEYTAB_TYPE
id|ir_codes_avermedia_dvbt
(braket
id|IR_KEYTAB_SIZE
)braket
op_assign
(brace
(braket
l_int|0x28
)braket
op_assign
id|KEY_KP0
comma
singleline_comment|//&squot;0&squot; / &squot;enter&squot;
(braket
l_int|0x22
)braket
op_assign
id|KEY_KP1
comma
singleline_comment|//&squot;1&squot;
(braket
l_int|0x12
)braket
op_assign
id|KEY_KP2
comma
singleline_comment|//&squot;2&squot; / &squot;up arrow&squot;
(braket
l_int|0x32
)braket
op_assign
id|KEY_KP3
comma
singleline_comment|//&squot;3&squot;
(braket
l_int|0x24
)braket
op_assign
id|KEY_KP4
comma
singleline_comment|//&squot;4&squot; / &squot;left arrow&squot;
(braket
l_int|0x14
)braket
op_assign
id|KEY_KP5
comma
singleline_comment|//&squot;5&squot;
(braket
l_int|0x34
)braket
op_assign
id|KEY_KP6
comma
singleline_comment|//&squot;6&squot; / &squot;right arrow&squot;
(braket
l_int|0x26
)braket
op_assign
id|KEY_KP7
comma
singleline_comment|//&squot;7&squot;
(braket
l_int|0x16
)braket
op_assign
id|KEY_KP8
comma
singleline_comment|//&squot;8&squot; / &squot;down arrow&squot;
(braket
l_int|0x36
)braket
op_assign
id|KEY_KP9
comma
singleline_comment|//&squot;9&squot;
(braket
l_int|0x20
)braket
op_assign
id|KEY_LIST
comma
singleline_comment|// &squot;source&squot;
(braket
l_int|0x10
)braket
op_assign
id|KEY_TEXT
comma
singleline_comment|// &squot;teletext&squot;
(braket
l_int|0x00
)braket
op_assign
id|KEY_POWER
comma
singleline_comment|// &squot;power&squot;
(braket
l_int|0x04
)braket
op_assign
id|KEY_AUDIO
comma
singleline_comment|// &squot;audio&squot;
(braket
l_int|0x06
)braket
op_assign
id|KEY_ZOOM
comma
singleline_comment|// &squot;full screen&squot;
(braket
l_int|0x18
)braket
op_assign
id|KEY_VIDEO
comma
singleline_comment|// &squot;display&squot;
(braket
l_int|0x38
)braket
op_assign
id|KEY_SEARCH
comma
singleline_comment|// &squot;loop&squot;
(braket
l_int|0x08
)braket
op_assign
id|KEY_INFO
comma
singleline_comment|// &squot;preview&squot;
(braket
l_int|0x2a
)braket
op_assign
id|KEY_REWIND
comma
singleline_comment|// &squot;backward &lt;&lt;&squot;
(braket
l_int|0x1a
)braket
op_assign
id|KEY_FASTFORWARD
comma
singleline_comment|// &squot;forward &gt;&gt;&squot;
(braket
l_int|0x3a
)braket
op_assign
id|KEY_RECORD
comma
singleline_comment|// &squot;capture&squot;
(braket
l_int|0x0a
)braket
op_assign
id|KEY_MUTE
comma
singleline_comment|// &squot;mute&squot;
(braket
l_int|0x2c
)braket
op_assign
id|KEY_RECORD
comma
singleline_comment|// &squot;record&squot;
(braket
l_int|0x1c
)braket
op_assign
id|KEY_PAUSE
comma
singleline_comment|// &squot;pause&squot;
(braket
l_int|0x3c
)braket
op_assign
id|KEY_STOP
comma
singleline_comment|// &squot;stop&squot;
(braket
l_int|0x0c
)braket
op_assign
id|KEY_PLAY
comma
singleline_comment|// &squot;play&squot;
(braket
l_int|0x2e
)braket
op_assign
id|KEY_RED
comma
singleline_comment|// &squot;red&squot;
(braket
l_int|0x01
)braket
op_assign
id|KEY_BLUE
comma
singleline_comment|// &squot;blue&squot; / &squot;cancel&squot;
(braket
l_int|0x0e
)braket
op_assign
id|KEY_YELLOW
comma
singleline_comment|// &squot;yellow&squot; / &squot;ok&squot;
(braket
l_int|0x21
)braket
op_assign
id|KEY_GREEN
comma
singleline_comment|// &squot;green&squot;
(braket
l_int|0x11
)braket
op_assign
id|KEY_CHANNELDOWN
comma
singleline_comment|// &squot;channel -&squot;
(braket
l_int|0x31
)braket
op_assign
id|KEY_CHANNELUP
comma
singleline_comment|// &squot;channel +&squot;
(braket
l_int|0x1e
)braket
op_assign
id|KEY_VOLUMEDOWN
comma
singleline_comment|// &squot;volume -&squot;
(braket
l_int|0x3e
)braket
op_assign
id|KEY_VOLUMEUP
comma
singleline_comment|// &squot;volume +&squot;
)brace
suffix:semicolon
DECL|variable|ir_codes_pixelview
r_static
id|IR_KEYTAB_TYPE
id|ir_codes_pixelview
(braket
id|IR_KEYTAB_SIZE
)braket
op_assign
(brace
(braket
l_int|2
)braket
op_assign
id|KEY_KP0
comma
(braket
l_int|1
)braket
op_assign
id|KEY_KP1
comma
(braket
l_int|11
)braket
op_assign
id|KEY_KP2
comma
(braket
l_int|27
)braket
op_assign
id|KEY_KP3
comma
(braket
l_int|5
)braket
op_assign
id|KEY_KP4
comma
(braket
l_int|9
)braket
op_assign
id|KEY_KP5
comma
(braket
l_int|21
)braket
op_assign
id|KEY_KP6
comma
(braket
l_int|6
)braket
op_assign
id|KEY_KP7
comma
(braket
l_int|10
)braket
op_assign
id|KEY_KP8
comma
(braket
l_int|18
)braket
op_assign
id|KEY_KP9
comma
(braket
l_int|3
)braket
op_assign
id|KEY_TUNER
comma
singleline_comment|// TV/FM
(braket
l_int|7
)braket
op_assign
id|KEY_SEARCH
comma
singleline_comment|// scan
(braket
l_int|28
)braket
op_assign
id|KEY_ZOOM
comma
singleline_comment|// full screen
(braket
l_int|30
)braket
op_assign
id|KEY_POWER
comma
(braket
l_int|23
)braket
op_assign
id|KEY_VOLUMEDOWN
comma
(braket
l_int|31
)braket
op_assign
id|KEY_VOLUMEUP
comma
(braket
l_int|20
)braket
op_assign
id|KEY_CHANNELDOWN
comma
(braket
l_int|22
)braket
op_assign
id|KEY_CHANNELUP
comma
(braket
l_int|24
)braket
op_assign
id|KEY_MUTE
comma
(braket
l_int|0
)braket
op_assign
id|KEY_LIST
comma
singleline_comment|// source
(braket
l_int|19
)braket
op_assign
id|KEY_INFO
comma
singleline_comment|// loop
(braket
l_int|16
)braket
op_assign
id|KEY_LAST
comma
singleline_comment|// +100
(braket
l_int|13
)braket
op_assign
id|KEY_CLEAR
comma
singleline_comment|// reset
(braket
l_int|12
)braket
op_assign
id|BTN_RIGHT
comma
singleline_comment|// fun++
(braket
l_int|4
)braket
op_assign
id|BTN_LEFT
comma
singleline_comment|// fun--
(braket
l_int|14
)braket
op_assign
id|KEY_GOTO
comma
singleline_comment|// function
(braket
l_int|15
)braket
op_assign
id|KEY_STOP
comma
singleline_comment|// freeze
)brace
suffix:semicolon
multiline_comment|/* Attila Kondoros &lt;attila.kondoros@chello.hu&gt; */
DECL|variable|ir_codes_apac_viewcomp
r_static
id|IR_KEYTAB_TYPE
id|ir_codes_apac_viewcomp
(braket
id|IR_KEYTAB_SIZE
)braket
op_assign
(brace
(braket
l_int|1
)braket
op_assign
id|KEY_KP1
comma
(braket
l_int|2
)braket
op_assign
id|KEY_KP2
comma
(braket
l_int|3
)braket
op_assign
id|KEY_KP3
comma
(braket
l_int|4
)braket
op_assign
id|KEY_KP4
comma
(braket
l_int|5
)braket
op_assign
id|KEY_KP5
comma
(braket
l_int|6
)braket
op_assign
id|KEY_KP6
comma
(braket
l_int|7
)braket
op_assign
id|KEY_KP7
comma
(braket
l_int|8
)braket
op_assign
id|KEY_KP8
comma
(braket
l_int|9
)braket
op_assign
id|KEY_KP9
comma
(braket
l_int|0
)braket
op_assign
id|KEY_KP0
comma
(braket
l_int|23
)braket
op_assign
id|KEY_LAST
comma
singleline_comment|// +100
(braket
l_int|10
)braket
op_assign
id|KEY_LIST
comma
singleline_comment|// recall
(braket
l_int|28
)braket
op_assign
id|KEY_TUNER
comma
singleline_comment|// TV/FM
(braket
l_int|21
)braket
op_assign
id|KEY_SEARCH
comma
singleline_comment|// scan
(braket
l_int|18
)braket
op_assign
id|KEY_POWER
comma
singleline_comment|// power
(braket
l_int|31
)braket
op_assign
id|KEY_VOLUMEDOWN
comma
singleline_comment|// vol up
(braket
l_int|27
)braket
op_assign
id|KEY_VOLUMEUP
comma
singleline_comment|// vol down
(braket
l_int|30
)braket
op_assign
id|KEY_CHANNELDOWN
comma
singleline_comment|// chn up
(braket
l_int|26
)braket
op_assign
id|KEY_CHANNELUP
comma
singleline_comment|// chn down
(braket
l_int|17
)braket
op_assign
id|KEY_VIDEO
comma
singleline_comment|// video
(braket
l_int|15
)braket
op_assign
id|KEY_ZOOM
comma
singleline_comment|// full screen
(braket
l_int|19
)braket
op_assign
id|KEY_MUTE
comma
singleline_comment|// mute/unmute
(braket
l_int|16
)braket
op_assign
id|KEY_TEXT
comma
singleline_comment|// min
(braket
l_int|13
)braket
op_assign
id|KEY_STOP
comma
singleline_comment|// freeze
(braket
l_int|14
)braket
op_assign
id|KEY_RECORD
comma
singleline_comment|// record
(braket
l_int|29
)braket
op_assign
id|KEY_PLAYPAUSE
comma
singleline_comment|// stop
(braket
l_int|25
)braket
op_assign
id|KEY_PLAY
comma
singleline_comment|// play
(braket
l_int|22
)braket
op_assign
id|KEY_GOTO
comma
singleline_comment|// osd
(braket
l_int|20
)braket
op_assign
id|KEY_REFRESH
comma
singleline_comment|// default
(braket
l_int|12
)braket
op_assign
id|KEY_KPPLUS
comma
singleline_comment|// fine tune &gt;&gt;&gt;&gt;
(braket
l_int|24
)braket
op_assign
id|KEY_KPMINUS
singleline_comment|// fine tune &lt;&lt;&lt;&lt;
)brace
suffix:semicolon
multiline_comment|/* ---------------------------------------------------------------------- */
DECL|struct|IR
r_struct
id|IR
(brace
DECL|member|sub
r_struct
id|bttv_sub_device
op_star
id|sub
suffix:semicolon
DECL|member|input
r_struct
id|input_dev
id|input
suffix:semicolon
DECL|member|ir
r_struct
id|ir_input_state
id|ir
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|phys
r_char
id|phys
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|mask_keycode
id|u32
id|mask_keycode
suffix:semicolon
DECL|member|mask_keydown
id|u32
id|mask_keydown
suffix:semicolon
DECL|member|mask_keyup
id|u32
id|mask_keyup
suffix:semicolon
DECL|member|polling
r_int
id|polling
suffix:semicolon
DECL|member|last_gpio
id|u32
id|last_gpio
suffix:semicolon
DECL|member|work
r_struct
id|work_struct
id|work
suffix:semicolon
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|debug
r_static
r_int
id|debug
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
multiline_comment|/* debug level (0,1,2) */
DECL|macro|DEVNAME
mdefine_line|#define DEVNAME &quot;ir-kbd-gpio&quot;
DECL|macro|dprintk
mdefine_line|#define dprintk(fmt, arg...)&t;if (debug) &bslash;&n;&t;printk(KERN_DEBUG DEVNAME &quot;: &quot; fmt , ## arg)
r_static
r_void
id|ir_irq
c_func
(paren
r_struct
id|bttv_sub_device
op_star
id|sub
)paren
suffix:semicolon
r_static
r_int
id|ir_probe
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_int
id|ir_remove
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
DECL|variable|driver
r_static
r_struct
id|bttv_sub_driver
id|driver
op_assign
(brace
dot
id|drv
op_assign
(brace
dot
id|name
op_assign
id|DEVNAME
comma
dot
id|probe
op_assign
id|ir_probe
comma
dot
id|remove
op_assign
id|ir_remove
comma
)brace
comma
dot
id|gpio_irq
op_assign
id|ir_irq
comma
)brace
suffix:semicolon
multiline_comment|/* ---------------------------------------------------------------------- */
DECL|function|ir_handle_key
r_static
r_void
id|ir_handle_key
c_func
(paren
r_struct
id|IR
op_star
id|ir
)paren
(brace
id|u32
id|gpio
comma
id|data
suffix:semicolon
multiline_comment|/* read gpio value */
id|gpio
op_assign
id|bttv_gpio_read
c_func
(paren
id|ir-&gt;sub-&gt;core
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ir-&gt;polling
)paren
(brace
r_if
c_cond
(paren
id|ir-&gt;last_gpio
op_eq
id|gpio
)paren
r_return
suffix:semicolon
id|ir-&gt;last_gpio
op_assign
id|gpio
suffix:semicolon
)brace
multiline_comment|/* extract data */
id|data
op_assign
id|ir_extract_bits
c_func
(paren
id|gpio
comma
id|ir-&gt;mask_keycode
)paren
suffix:semicolon
id|dprintk
c_func
(paren
id|DEVNAME
l_string|&quot;: irq gpio=0x%x code=%d | %s%s%s&bslash;n&quot;
comma
id|gpio
comma
id|data
comma
id|ir-&gt;polling
ques
c_cond
l_string|&quot;poll&quot;
suffix:colon
l_string|&quot;irq&quot;
comma
(paren
id|gpio
op_amp
id|ir-&gt;mask_keydown
)paren
ques
c_cond
l_string|&quot; down&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|gpio
op_amp
id|ir-&gt;mask_keyup
)paren
ques
c_cond
l_string|&quot; up&quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ir-&gt;mask_keydown
)paren
(brace
multiline_comment|/* bit set on keydown */
r_if
c_cond
(paren
id|gpio
op_amp
id|ir-&gt;mask_keydown
)paren
(brace
id|ir_input_keydown
c_func
(paren
op_amp
id|ir-&gt;input
comma
op_amp
id|ir-&gt;ir
comma
id|data
comma
id|data
)paren
suffix:semicolon
)brace
r_else
(brace
id|ir_input_nokey
c_func
(paren
op_amp
id|ir-&gt;input
comma
op_amp
id|ir-&gt;ir
)paren
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|ir-&gt;mask_keyup
)paren
(brace
multiline_comment|/* bit cleared on keydown */
r_if
c_cond
(paren
l_int|0
op_eq
(paren
id|gpio
op_amp
id|ir-&gt;mask_keyup
)paren
)paren
(brace
id|ir_input_keydown
c_func
(paren
op_amp
id|ir-&gt;input
comma
op_amp
id|ir-&gt;ir
comma
id|data
comma
id|data
)paren
suffix:semicolon
)brace
r_else
(brace
id|ir_input_nokey
c_func
(paren
op_amp
id|ir-&gt;input
comma
op_amp
id|ir-&gt;ir
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* can&squot;t disturgissh keydown/up :-/ */
id|ir_input_keydown
c_func
(paren
op_amp
id|ir-&gt;input
comma
op_amp
id|ir-&gt;ir
comma
id|data
comma
id|data
)paren
suffix:semicolon
id|ir_input_nokey
c_func
(paren
op_amp
id|ir-&gt;input
comma
op_amp
id|ir-&gt;ir
)paren
suffix:semicolon
)brace
)brace
DECL|function|ir_irq
r_static
r_void
id|ir_irq
c_func
(paren
r_struct
id|bttv_sub_device
op_star
id|sub
)paren
(brace
r_struct
id|IR
op_star
id|ir
op_assign
id|dev_get_drvdata
c_func
(paren
op_amp
id|sub-&gt;dev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ir-&gt;polling
)paren
id|ir_handle_key
c_func
(paren
id|ir
)paren
suffix:semicolon
)brace
DECL|function|ir_timer
r_static
r_void
id|ir_timer
c_func
(paren
r_int
r_int
id|data
)paren
(brace
r_struct
id|IR
op_star
id|ir
op_assign
(paren
r_struct
id|IR
op_star
)paren
id|data
suffix:semicolon
id|schedule_work
c_func
(paren
op_amp
id|ir-&gt;work
)paren
suffix:semicolon
)brace
DECL|function|ir_work
r_static
r_void
id|ir_work
c_func
(paren
r_void
op_star
id|data
)paren
(brace
r_struct
id|IR
op_star
id|ir
op_assign
id|data
suffix:semicolon
r_int
r_int
id|timeout
suffix:semicolon
id|ir_handle_key
c_func
(paren
id|ir
)paren
suffix:semicolon
id|timeout
op_assign
id|jiffies
op_plus
(paren
id|ir-&gt;polling
op_star
id|HZ
op_div
l_int|1000
)paren
suffix:semicolon
id|mod_timer
c_func
(paren
op_amp
id|ir-&gt;timer
comma
id|timeout
)paren
suffix:semicolon
)brace
multiline_comment|/* ---------------------------------------------------------------------- */
DECL|function|ir_probe
r_static
r_int
id|ir_probe
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|bttv_sub_device
op_star
id|sub
op_assign
id|to_bttv_sub_dev
c_func
(paren
id|dev
)paren
suffix:semicolon
r_struct
id|IR
op_star
id|ir
suffix:semicolon
id|IR_KEYTAB_TYPE
op_star
id|ir_codes
op_assign
l_int|NULL
suffix:semicolon
r_int
id|ir_type
op_assign
id|IR_TYPE_OTHER
suffix:semicolon
id|ir
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|ir
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
id|ir
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|ir
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|ir
)paren
)paren
suffix:semicolon
multiline_comment|/* detect &amp; configure */
r_switch
c_cond
(paren
id|sub-&gt;core-&gt;type
)paren
(brace
r_case
id|BTTV_AVERMEDIA
suffix:colon
r_case
id|BTTV_AVPHONE98
suffix:colon
r_case
id|BTTV_AVERMEDIA98
suffix:colon
id|ir_codes
op_assign
id|ir_codes_avermedia
suffix:semicolon
id|ir-&gt;mask_keycode
op_assign
l_int|0xf88000
suffix:semicolon
id|ir-&gt;mask_keydown
op_assign
l_int|0x010000
suffix:semicolon
id|ir-&gt;polling
op_assign
l_int|50
suffix:semicolon
singleline_comment|// ms
r_break
suffix:semicolon
r_case
id|BTTV_AVDVBT_761
suffix:colon
r_case
id|BTTV_AVDVBT_771
suffix:colon
id|ir_codes
op_assign
id|ir_codes_avermedia_dvbt
suffix:semicolon
id|ir-&gt;mask_keycode
op_assign
l_int|0x0f00c0
suffix:semicolon
id|ir-&gt;mask_keydown
op_assign
l_int|0x000020
suffix:semicolon
id|ir-&gt;polling
op_assign
l_int|50
suffix:semicolon
singleline_comment|// ms
r_break
suffix:semicolon
r_case
id|BTTV_PXELVWPLTVPAK
suffix:colon
id|ir_codes
op_assign
id|ir_codes_pixelview
suffix:semicolon
id|ir-&gt;mask_keycode
op_assign
l_int|0x003e00
suffix:semicolon
id|ir-&gt;mask_keyup
op_assign
l_int|0x010000
suffix:semicolon
id|ir-&gt;polling
op_assign
l_int|50
suffix:semicolon
singleline_comment|// ms
r_break
suffix:semicolon
r_case
id|BTTV_PV_BT878P_9B
suffix:colon
r_case
id|BTTV_PV_BT878P_PLUS
suffix:colon
id|ir_codes
op_assign
id|ir_codes_pixelview
suffix:semicolon
id|ir-&gt;mask_keycode
op_assign
l_int|0x001f00
suffix:semicolon
id|ir-&gt;mask_keyup
op_assign
l_int|0x008000
suffix:semicolon
id|ir-&gt;polling
op_assign
l_int|50
suffix:semicolon
singleline_comment|// ms
r_break
suffix:semicolon
r_case
id|BTTV_WINFAST2000
suffix:colon
id|ir_codes
op_assign
id|ir_codes_winfast
suffix:semicolon
id|ir-&gt;mask_keycode
op_assign
l_int|0x1f8
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BTTV_MAGICTVIEW061
suffix:colon
r_case
id|BTTV_MAGICTVIEW063
suffix:colon
id|ir_codes
op_assign
id|ir_codes_winfast
suffix:semicolon
id|ir-&gt;mask_keycode
op_assign
l_int|0x0008e000
suffix:semicolon
id|ir-&gt;mask_keydown
op_assign
l_int|0x00200000
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BTTV_APAC_VIEWCOMP
suffix:colon
id|ir_codes
op_assign
id|ir_codes_apac_viewcomp
suffix:semicolon
id|ir-&gt;mask_keycode
op_assign
l_int|0x001f00
suffix:semicolon
id|ir-&gt;mask_keyup
op_assign
l_int|0x008000
suffix:semicolon
id|ir-&gt;polling
op_assign
l_int|50
suffix:semicolon
singleline_comment|// ms
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
l_int|NULL
op_eq
id|ir_codes
)paren
(brace
id|kfree
c_func
(paren
id|ir
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
multiline_comment|/* init hardware-specific stuff */
id|bttv_gpio_inout
c_func
(paren
id|sub-&gt;core
comma
id|ir-&gt;mask_keycode
op_or
id|ir-&gt;mask_keydown
comma
l_int|0
)paren
suffix:semicolon
id|ir-&gt;sub
op_assign
id|sub
suffix:semicolon
multiline_comment|/* init input device */
id|snprintf
c_func
(paren
id|ir-&gt;name
comma
r_sizeof
(paren
id|ir-&gt;name
)paren
comma
l_string|&quot;bttv IR (card=%d)&quot;
comma
id|sub-&gt;core-&gt;type
)paren
suffix:semicolon
id|snprintf
c_func
(paren
id|ir-&gt;phys
comma
r_sizeof
(paren
id|ir-&gt;phys
)paren
comma
l_string|&quot;pci-%s/ir0&quot;
comma
id|pci_name
c_func
(paren
id|sub-&gt;core-&gt;pci
)paren
)paren
suffix:semicolon
id|ir_input_init
c_func
(paren
op_amp
id|ir-&gt;input
comma
op_amp
id|ir-&gt;ir
comma
id|ir_type
comma
id|ir_codes
)paren
suffix:semicolon
id|ir-&gt;input.name
op_assign
id|ir-&gt;name
suffix:semicolon
id|ir-&gt;input.phys
op_assign
id|ir-&gt;phys
suffix:semicolon
id|ir-&gt;input.id.bustype
op_assign
id|BUS_PCI
suffix:semicolon
id|ir-&gt;input.id.version
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|sub-&gt;core-&gt;pci-&gt;subsystem_vendor
)paren
(brace
id|ir-&gt;input.id.vendor
op_assign
id|sub-&gt;core-&gt;pci-&gt;subsystem_vendor
suffix:semicolon
id|ir-&gt;input.id.product
op_assign
id|sub-&gt;core-&gt;pci-&gt;subsystem_device
suffix:semicolon
)brace
r_else
(brace
id|ir-&gt;input.id.vendor
op_assign
id|sub-&gt;core-&gt;pci-&gt;vendor
suffix:semicolon
id|ir-&gt;input.id.product
op_assign
id|sub-&gt;core-&gt;pci-&gt;device
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ir-&gt;polling
)paren
(brace
id|INIT_WORK
c_func
(paren
op_amp
id|ir-&gt;work
comma
id|ir_work
comma
id|ir
)paren
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|ir-&gt;timer
)paren
suffix:semicolon
id|ir-&gt;timer.function
op_assign
id|ir_timer
suffix:semicolon
id|ir-&gt;timer.data
op_assign
(paren
r_int
r_int
)paren
id|ir
suffix:semicolon
id|schedule_work
c_func
(paren
op_amp
id|ir-&gt;work
)paren
suffix:semicolon
)brace
multiline_comment|/* all done */
id|dev_set_drvdata
c_func
(paren
id|dev
comma
id|ir
)paren
suffix:semicolon
id|input_register_device
c_func
(paren
op_amp
id|ir-&gt;input
)paren
suffix:semicolon
id|printk
c_func
(paren
id|DEVNAME
l_string|&quot;: %s detected at %s&bslash;n&quot;
comma
id|ir-&gt;input.name
comma
id|ir-&gt;input.phys
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ir_remove
r_static
r_int
id|ir_remove
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|IR
op_star
id|ir
op_assign
id|dev_get_drvdata
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ir-&gt;polling
)paren
(brace
id|del_timer
c_func
(paren
op_amp
id|ir-&gt;timer
)paren
suffix:semicolon
id|flush_scheduled_work
c_func
(paren
)paren
suffix:semicolon
)brace
id|input_unregister_device
c_func
(paren
op_amp
id|ir-&gt;input
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|ir
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* ---------------------------------------------------------------------- */
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Gerd Knorr, Pavel Machek&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;input driver for bt8x8 gpio IR remote controls&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|function|ir_init
r_static
r_int
id|ir_init
c_func
(paren
r_void
)paren
(brace
r_return
id|bttv_sub_register
c_func
(paren
op_amp
id|driver
comma
l_string|&quot;remote&quot;
)paren
suffix:semicolon
)brace
DECL|function|ir_fini
r_static
r_void
id|ir_fini
c_func
(paren
r_void
)paren
(brace
id|bttv_sub_unregister
c_func
(paren
op_amp
id|driver
)paren
suffix:semicolon
)brace
DECL|variable|ir_init
id|module_init
c_func
(paren
id|ir_init
)paren
suffix:semicolon
DECL|variable|ir_fini
id|module_exit
c_func
(paren
id|ir_fini
)paren
suffix:semicolon
multiline_comment|/*&n; * Local variables:&n; * c-basic-offset: 8&n; * End:&n; */
eof
