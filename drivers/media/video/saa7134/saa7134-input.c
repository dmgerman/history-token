multiline_comment|/*&n; * $Id: saa7134-input.c,v 1.16 2004/12/10 12:33:39 kraxel Exp $&n; *&n; * handle saa7134 IR remotes via linux kernel input layer.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/input.h&gt;
macro_line|#include &quot;saa7134-reg.h&quot;
macro_line|#include &quot;saa7134.h&quot;
DECL|variable|disable_ir
r_static
r_int
r_int
id|disable_ir
op_assign
l_int|0
suffix:semicolon
id|module_param
c_func
(paren
id|disable_ir
comma
r_int
comma
l_int|0444
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|disable_ir
comma
l_string|&quot;disable infrared remote support&quot;
)paren
suffix:semicolon
DECL|variable|ir_debug
r_static
r_int
r_int
id|ir_debug
op_assign
l_int|0
suffix:semicolon
id|module_param
c_func
(paren
id|ir_debug
comma
r_int
comma
l_int|0644
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|ir_debug
comma
l_string|&quot;enable debug messages [IR]&quot;
)paren
suffix:semicolon
DECL|macro|dprintk
mdefine_line|#define dprintk(fmt, arg...)&t;if (ir_debug) &bslash;&n;&t;printk(KERN_DEBUG &quot;%s/ir: &quot; fmt, dev-&gt;name , ## arg)
multiline_comment|/* ---------------------------------------------------------------------- */
DECL|variable|flyvideo_codes
r_static
id|IR_KEYTAB_TYPE
id|flyvideo_codes
(braket
id|IR_KEYTAB_SIZE
)braket
op_assign
(brace
(braket
l_int|15
)braket
op_assign
id|KEY_KP0
comma
(braket
l_int|3
)braket
op_assign
id|KEY_KP1
comma
(braket
l_int|4
)braket
op_assign
id|KEY_KP2
comma
(braket
l_int|5
)braket
op_assign
id|KEY_KP3
comma
(braket
l_int|7
)braket
op_assign
id|KEY_KP4
comma
(braket
l_int|8
)braket
op_assign
id|KEY_KP5
comma
(braket
l_int|9
)braket
op_assign
id|KEY_KP6
comma
(braket
l_int|11
)braket
op_assign
id|KEY_KP7
comma
(braket
l_int|12
)braket
op_assign
id|KEY_KP8
comma
(braket
l_int|13
)braket
op_assign
id|KEY_KP9
comma
(braket
l_int|14
)braket
op_assign
id|KEY_TUNER
comma
singleline_comment|// Air/Cable
(braket
l_int|17
)braket
op_assign
id|KEY_VIDEO
comma
singleline_comment|// Video
(braket
l_int|21
)braket
op_assign
id|KEY_AUDIO
comma
singleline_comment|// Audio
(braket
l_int|0
)braket
op_assign
id|KEY_POWER
comma
singleline_comment|// Pover
(braket
l_int|2
)braket
op_assign
id|KEY_ZOOM
comma
singleline_comment|// Fullscreen
(braket
l_int|27
)braket
op_assign
id|KEY_MUTE
comma
singleline_comment|// Mute
(braket
l_int|20
)braket
op_assign
id|KEY_VOLUMEUP
comma
(braket
l_int|23
)braket
op_assign
id|KEY_VOLUMEDOWN
comma
(braket
l_int|18
)braket
op_assign
id|KEY_CHANNELUP
comma
singleline_comment|// Channel +
(braket
l_int|19
)braket
op_assign
id|KEY_CHANNELDOWN
comma
singleline_comment|// Channel -
(braket
l_int|6
)braket
op_assign
id|KEY_AGAIN
comma
singleline_comment|// Recal
(braket
l_int|16
)braket
op_assign
id|KEY_KPENTER
comma
singleline_comment|// Enter
macro_line|#if 1 /* FIXME */
(braket
l_int|26
)braket
op_assign
id|KEY_F22
comma
singleline_comment|// Stereo
(braket
l_int|24
)braket
op_assign
id|KEY_EDIT
comma
singleline_comment|// AV Source
macro_line|#endif
)brace
suffix:semicolon
DECL|variable|cinergy_codes
r_static
id|IR_KEYTAB_TYPE
id|cinergy_codes
(braket
id|IR_KEYTAB_SIZE
)braket
op_assign
(brace
(braket
l_int|0
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
l_int|0x0a
)braket
op_assign
id|KEY_POWER
comma
(braket
l_int|0x0b
)braket
op_assign
id|KEY_PROG1
comma
singleline_comment|// app
(braket
l_int|0x0c
)braket
op_assign
id|KEY_ZOOM
comma
singleline_comment|// zoom/fullscreen
(braket
l_int|0x0d
)braket
op_assign
id|KEY_CHANNELUP
comma
singleline_comment|// channel
(braket
l_int|0x0e
)braket
op_assign
id|KEY_CHANNELDOWN
comma
singleline_comment|// channel-
(braket
l_int|0x0f
)braket
op_assign
id|KEY_VOLUMEUP
comma
(braket
l_int|0x10
)braket
op_assign
id|KEY_VOLUMEDOWN
comma
(braket
l_int|0x11
)braket
op_assign
id|KEY_TUNER
comma
singleline_comment|// AV
(braket
l_int|0x12
)braket
op_assign
id|KEY_NUMLOCK
comma
singleline_comment|// -/--
(braket
l_int|0x13
)braket
op_assign
id|KEY_AUDIO
comma
singleline_comment|// audio
(braket
l_int|0x14
)braket
op_assign
id|KEY_MUTE
comma
(braket
l_int|0x15
)braket
op_assign
id|KEY_UP
comma
(braket
l_int|0x16
)braket
op_assign
id|KEY_DOWN
comma
(braket
l_int|0x17
)braket
op_assign
id|KEY_LEFT
comma
(braket
l_int|0x18
)braket
op_assign
id|KEY_RIGHT
comma
(braket
l_int|0x19
)braket
op_assign
id|BTN_LEFT
comma
(braket
l_int|0x1a
)braket
op_assign
id|BTN_RIGHT
comma
(braket
l_int|0x1b
)braket
op_assign
id|KEY_WWW
comma
singleline_comment|// text
(braket
l_int|0x1c
)braket
op_assign
id|KEY_REWIND
comma
(braket
l_int|0x1d
)braket
op_assign
id|KEY_FORWARD
comma
(braket
l_int|0x1e
)braket
op_assign
id|KEY_RECORD
comma
(braket
l_int|0x1f
)braket
op_assign
id|KEY_PLAY
comma
(braket
l_int|0x20
)braket
op_assign
id|KEY_PREVIOUSSONG
comma
(braket
l_int|0x21
)braket
op_assign
id|KEY_NEXTSONG
comma
(braket
l_int|0x22
)braket
op_assign
id|KEY_PAUSE
comma
(braket
l_int|0x23
)braket
op_assign
id|KEY_STOP
comma
)brace
suffix:semicolon
multiline_comment|/* Alfons Geser &lt;a.geser@cox.net&gt;&n; * updates from Job D. R. Borges &lt;jobdrb@ig.com.br&gt; */
DECL|variable|eztv_codes
r_static
id|IR_KEYTAB_TYPE
id|eztv_codes
(braket
id|IR_KEYTAB_SIZE
)braket
op_assign
(brace
(braket
l_int|18
)braket
op_assign
id|KEY_POWER
comma
(braket
l_int|1
)braket
op_assign
id|KEY_TV
comma
singleline_comment|// DVR
(braket
l_int|21
)braket
op_assign
id|KEY_DVD
comma
singleline_comment|// DVD
(braket
l_int|23
)braket
op_assign
id|KEY_AUDIO
comma
singleline_comment|// music
singleline_comment|// DVR mode / DVD mode / music mode
(braket
l_int|27
)braket
op_assign
id|KEY_MUTE
comma
singleline_comment|// mute
(braket
l_int|2
)braket
op_assign
id|KEY_LANGUAGE
comma
singleline_comment|// MTS/SAP / audio / autoseek
(braket
l_int|30
)braket
op_assign
id|KEY_SUBTITLE
comma
singleline_comment|// closed captioning / subtitle / seek
(braket
l_int|22
)braket
op_assign
id|KEY_ZOOM
comma
singleline_comment|// full screen
(braket
l_int|28
)braket
op_assign
id|KEY_VIDEO
comma
singleline_comment|// video source / eject / delall
(braket
l_int|29
)braket
op_assign
id|KEY_RESTART
comma
singleline_comment|// playback / angle / del
(braket
l_int|47
)braket
op_assign
id|KEY_SEARCH
comma
singleline_comment|// scan / menu / playlist
(braket
l_int|48
)braket
op_assign
id|KEY_CHANNEL
comma
singleline_comment|// CH surfing / bookmark / memo
(braket
l_int|49
)braket
op_assign
id|KEY_HELP
comma
singleline_comment|// help
(braket
l_int|50
)braket
op_assign
id|KEY_MODE
comma
singleline_comment|// num/memo
(braket
l_int|51
)braket
op_assign
id|KEY_ESC
comma
singleline_comment|// cancel
(braket
l_int|12
)braket
op_assign
id|KEY_UP
comma
singleline_comment|// up
(braket
l_int|16
)braket
op_assign
id|KEY_DOWN
comma
singleline_comment|// down
(braket
l_int|8
)braket
op_assign
id|KEY_LEFT
comma
singleline_comment|// left
(braket
l_int|4
)braket
op_assign
id|KEY_RIGHT
comma
singleline_comment|// right
(braket
l_int|3
)braket
op_assign
id|KEY_SELECT
comma
singleline_comment|// select
(braket
l_int|31
)braket
op_assign
id|KEY_REWIND
comma
singleline_comment|// rewind
(braket
l_int|32
)braket
op_assign
id|KEY_PLAYPAUSE
comma
singleline_comment|// play/pause
(braket
l_int|41
)braket
op_assign
id|KEY_FORWARD
comma
singleline_comment|// forward
(braket
l_int|20
)braket
op_assign
id|KEY_AGAIN
comma
singleline_comment|// repeat
(braket
l_int|43
)braket
op_assign
id|KEY_RECORD
comma
singleline_comment|// recording
(braket
l_int|44
)braket
op_assign
id|KEY_STOP
comma
singleline_comment|// stop
(braket
l_int|45
)braket
op_assign
id|KEY_PLAY
comma
singleline_comment|// play
(braket
l_int|46
)braket
op_assign
id|KEY_SHUFFLE
comma
singleline_comment|// snapshot / shuffle
(braket
l_int|0
)braket
op_assign
id|KEY_KP0
comma
(braket
l_int|5
)braket
op_assign
id|KEY_KP1
comma
(braket
l_int|6
)braket
op_assign
id|KEY_KP2
comma
(braket
l_int|7
)braket
op_assign
id|KEY_KP3
comma
(braket
l_int|9
)braket
op_assign
id|KEY_KP4
comma
(braket
l_int|10
)braket
op_assign
id|KEY_KP5
comma
(braket
l_int|11
)braket
op_assign
id|KEY_KP6
comma
(braket
l_int|13
)braket
op_assign
id|KEY_KP7
comma
(braket
l_int|14
)braket
op_assign
id|KEY_KP8
comma
(braket
l_int|15
)braket
op_assign
id|KEY_KP9
comma
(braket
l_int|42
)braket
op_assign
id|KEY_VOLUMEUP
comma
(braket
l_int|17
)braket
op_assign
id|KEY_VOLUMEDOWN
comma
(braket
l_int|24
)braket
op_assign
id|KEY_CHANNELUP
comma
singleline_comment|// CH.tracking up
(braket
l_int|25
)braket
op_assign
id|KEY_CHANNELDOWN
comma
singleline_comment|// CH.tracking down
(braket
l_int|19
)braket
op_assign
id|KEY_KPENTER
comma
singleline_comment|// enter
(braket
l_int|33
)braket
op_assign
id|KEY_KPDOT
comma
singleline_comment|// . (decimal dot)
)brace
suffix:semicolon
DECL|variable|avacssmart_codes
r_static
id|IR_KEYTAB_TYPE
id|avacssmart_codes
(braket
id|IR_KEYTAB_SIZE
)braket
op_assign
(brace
(braket
l_int|30
)braket
op_assign
id|KEY_POWER
comma
singleline_comment|// power
(braket
l_int|28
)braket
op_assign
id|KEY_SEARCH
comma
singleline_comment|// scan
(braket
l_int|7
)braket
op_assign
id|KEY_SELECT
comma
singleline_comment|// source
(braket
l_int|22
)braket
op_assign
id|KEY_VOLUMEUP
comma
(braket
l_int|20
)braket
op_assign
id|KEY_VOLUMEDOWN
comma
(braket
l_int|31
)braket
op_assign
id|KEY_CHANNELUP
comma
(braket
l_int|23
)braket
op_assign
id|KEY_CHANNELDOWN
comma
(braket
l_int|24
)braket
op_assign
id|KEY_MUTE
comma
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
l_int|16
)braket
op_assign
id|KEY_KPDOT
comma
(braket
l_int|3
)braket
op_assign
id|KEY_TUNER
comma
singleline_comment|// tv/fm
(braket
l_int|4
)braket
op_assign
id|KEY_REWIND
comma
singleline_comment|// fm tuning left or function left
(braket
l_int|12
)braket
op_assign
id|KEY_FORWARD
comma
singleline_comment|// fm tuning right or function right
(braket
l_int|0
)braket
op_assign
id|KEY_RECORD
comma
(braket
l_int|8
)braket
op_assign
id|KEY_STOP
comma
(braket
l_int|17
)braket
op_assign
id|KEY_PLAY
comma
(braket
l_int|25
)braket
op_assign
id|KEY_ZOOM
comma
(braket
l_int|14
)braket
op_assign
id|KEY_MENU
comma
singleline_comment|// function
(braket
l_int|19
)braket
op_assign
id|KEY_AGAIN
comma
singleline_comment|// recall
(braket
l_int|29
)braket
op_assign
id|KEY_RESTART
comma
singleline_comment|// reset
singleline_comment|// FIXME
(braket
l_int|13
)braket
op_assign
id|KEY_F21
comma
singleline_comment|// mts
(braket
l_int|15
)braket
op_assign
id|KEY_F22
comma
singleline_comment|// min
(braket
l_int|26
)braket
op_assign
id|KEY_F23
comma
singleline_comment|// freeze
)brace
suffix:semicolon
multiline_comment|/* Alex Hermann &lt;gaaf@gmx.net&gt; */
DECL|variable|md2819_codes
r_static
id|IR_KEYTAB_TYPE
id|md2819_codes
(braket
id|IR_KEYTAB_SIZE
)braket
op_assign
(brace
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
l_int|34
)braket
op_assign
id|KEY_KP0
comma
(braket
l_int|32
)braket
op_assign
id|KEY_TV
comma
singleline_comment|// TV/FM
(braket
l_int|16
)braket
op_assign
id|KEY_CD
comma
singleline_comment|// CD
(braket
l_int|48
)braket
op_assign
id|KEY_TEXT
comma
singleline_comment|// TELETEXT
(braket
l_int|0
)braket
op_assign
id|KEY_POWER
comma
singleline_comment|// POWER
(braket
l_int|8
)braket
op_assign
id|KEY_VIDEO
comma
singleline_comment|// VIDEO
(braket
l_int|4
)braket
op_assign
id|KEY_AUDIO
comma
singleline_comment|// AUDIO
(braket
l_int|12
)braket
op_assign
id|KEY_ZOOM
comma
singleline_comment|// FULL SCREEN
(braket
l_int|18
)braket
op_assign
id|KEY_SUBTITLE
comma
singleline_comment|// DISPLAY&t;- ???
(braket
l_int|50
)braket
op_assign
id|KEY_REWIND
comma
singleline_comment|// LOOP&t;&t;- ???
(braket
l_int|2
)braket
op_assign
id|KEY_PRINT
comma
singleline_comment|// PREVIEW&t;- ???
(braket
l_int|42
)braket
op_assign
id|KEY_SEARCH
comma
singleline_comment|// AUTOSCAN
(braket
l_int|26
)braket
op_assign
id|KEY_SLEEP
comma
singleline_comment|// FREEZE&t;- ???
(braket
l_int|58
)braket
op_assign
id|KEY_SHUFFLE
comma
singleline_comment|// SNAPSHOT&t;- ???
(braket
l_int|10
)braket
op_assign
id|KEY_MUTE
comma
singleline_comment|// MUTE
(braket
l_int|38
)braket
op_assign
id|KEY_RECORD
comma
singleline_comment|// RECORD
(braket
l_int|22
)braket
op_assign
id|KEY_PAUSE
comma
singleline_comment|// PAUSE
(braket
l_int|54
)braket
op_assign
id|KEY_STOP
comma
singleline_comment|// STOP
(braket
l_int|6
)braket
op_assign
id|KEY_PLAY
comma
singleline_comment|// PLAY
(braket
l_int|46
)braket
op_assign
id|KEY_RED
comma
singleline_comment|// &lt;RED&gt;
(braket
l_int|33
)braket
op_assign
id|KEY_GREEN
comma
singleline_comment|// &lt;GREEN&gt;
(braket
l_int|14
)braket
op_assign
id|KEY_YELLOW
comma
singleline_comment|// &lt;YELLOW&gt;
(braket
l_int|1
)braket
op_assign
id|KEY_BLUE
comma
singleline_comment|// &lt;BLUE&gt;
(braket
l_int|30
)braket
op_assign
id|KEY_VOLUMEDOWN
comma
singleline_comment|// VOLUME-
(braket
l_int|62
)braket
op_assign
id|KEY_VOLUMEUP
comma
singleline_comment|// VOLUME+
(braket
l_int|17
)braket
op_assign
id|KEY_CHANNELDOWN
comma
singleline_comment|// CHANNEL/PAGE-
(braket
l_int|49
)braket
op_assign
id|KEY_CHANNELUP
singleline_comment|// CHANNEL/PAGE+
)brace
suffix:semicolon
DECL|variable|videomate_tv_pvr_codes
r_static
id|IR_KEYTAB_TYPE
id|videomate_tv_pvr_codes
(braket
id|IR_KEYTAB_SIZE
)braket
op_assign
(brace
(braket
l_int|20
)braket
op_assign
id|KEY_MUTE
comma
(braket
l_int|36
)braket
op_assign
id|KEY_ZOOM
comma
(braket
l_int|1
)braket
op_assign
id|KEY_DVD
comma
(braket
l_int|35
)braket
op_assign
id|KEY_RADIO
comma
(braket
l_int|0
)braket
op_assign
id|KEY_TV
comma
(braket
l_int|10
)braket
op_assign
id|KEY_REWIND
comma
(braket
l_int|8
)braket
op_assign
id|KEY_PLAYPAUSE
comma
(braket
l_int|15
)braket
op_assign
id|KEY_FORWARD
comma
(braket
l_int|2
)braket
op_assign
id|KEY_PREVIOUS
comma
(braket
l_int|7
)braket
op_assign
id|KEY_STOP
comma
(braket
l_int|6
)braket
op_assign
id|KEY_NEXT
comma
(braket
l_int|12
)braket
op_assign
id|KEY_UP
comma
(braket
l_int|14
)braket
op_assign
id|KEY_DOWN
comma
(braket
l_int|11
)braket
op_assign
id|KEY_LEFT
comma
(braket
l_int|13
)braket
op_assign
id|KEY_RIGHT
comma
(braket
l_int|17
)braket
op_assign
id|KEY_OK
comma
(braket
l_int|3
)braket
op_assign
id|KEY_MENU
comma
(braket
l_int|9
)braket
op_assign
id|KEY_SETUP
comma
(braket
l_int|5
)braket
op_assign
id|KEY_VIDEO
comma
(braket
l_int|34
)braket
op_assign
id|KEY_CHANNEL
comma
(braket
l_int|18
)braket
op_assign
id|KEY_VOLUMEUP
comma
(braket
l_int|21
)braket
op_assign
id|KEY_VOLUMEDOWN
comma
(braket
l_int|16
)braket
op_assign
id|KEY_CHANNELUP
comma
(braket
l_int|19
)braket
op_assign
id|KEY_CHANNELDOWN
comma
(braket
l_int|4
)braket
op_assign
id|KEY_RECORD
comma
(braket
l_int|22
)braket
op_assign
id|KEY_KP1
comma
(braket
l_int|23
)braket
op_assign
id|KEY_KP2
comma
(braket
l_int|24
)braket
op_assign
id|KEY_KP3
comma
(braket
l_int|25
)braket
op_assign
id|KEY_KP4
comma
(braket
l_int|26
)braket
op_assign
id|KEY_KP5
comma
(braket
l_int|27
)braket
op_assign
id|KEY_KP6
comma
(braket
l_int|28
)braket
op_assign
id|KEY_KP7
comma
(braket
l_int|29
)braket
op_assign
id|KEY_KP8
comma
(braket
l_int|30
)braket
op_assign
id|KEY_KP9
comma
(braket
l_int|31
)braket
op_assign
id|KEY_KP0
comma
(braket
l_int|32
)braket
op_assign
id|KEY_LANGUAGE
comma
(braket
l_int|33
)braket
op_assign
id|KEY_SLEEP
comma
)brace
suffix:semicolon
multiline_comment|/* ---------------------------------------------------------------------- */
DECL|function|build_key
r_static
r_int
id|build_key
c_func
(paren
r_struct
id|saa7134_dev
op_star
id|dev
)paren
(brace
r_struct
id|saa7134_ir
op_star
id|ir
op_assign
id|dev-&gt;remote
suffix:semicolon
id|u32
id|gpio
comma
id|data
suffix:semicolon
multiline_comment|/* rising SAA7134_GPIO_GPRESCAN reads the status */
id|saa_clearb
c_func
(paren
id|SAA7134_GPIO_GPMODE3
comma
id|SAA7134_GPIO_GPRESCAN
)paren
suffix:semicolon
id|saa_setb
c_func
(paren
id|SAA7134_GPIO_GPMODE3
comma
id|SAA7134_GPIO_GPRESCAN
)paren
suffix:semicolon
id|gpio
op_assign
id|saa_readl
c_func
(paren
id|SAA7134_GPIO_GPSTATUS0
op_rshift
l_int|2
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
l_int|0
suffix:semicolon
id|ir-&gt;last_gpio
op_assign
id|gpio
suffix:semicolon
)brace
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
l_string|&quot;build_key gpio=0x%x mask=0x%x data=%d&bslash;n&quot;
comma
id|gpio
comma
id|ir-&gt;mask_keycode
comma
id|data
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ir-&gt;mask_keydown
op_logical_and
(paren
l_int|0
op_ne
(paren
id|gpio
op_amp
id|ir-&gt;mask_keydown
)paren
)paren
)paren
op_logical_or
(paren
id|ir-&gt;mask_keyup
op_logical_and
(paren
l_int|0
op_eq
(paren
id|gpio
op_amp
id|ir-&gt;mask_keyup
)paren
)paren
)paren
)paren
(brace
id|ir_input_keydown
c_func
(paren
op_amp
id|ir-&gt;dev
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
id|ir-&gt;dev
comma
op_amp
id|ir-&gt;ir
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* ---------------------------------------------------------------------- */
DECL|function|saa7134_input_irq
r_void
id|saa7134_input_irq
c_func
(paren
r_struct
id|saa7134_dev
op_star
id|dev
)paren
(brace
r_struct
id|saa7134_ir
op_star
id|ir
op_assign
id|dev-&gt;remote
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ir-&gt;polling
)paren
id|build_key
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
DECL|function|saa7134_input_timer
r_static
r_void
id|saa7134_input_timer
c_func
(paren
r_int
r_int
id|data
)paren
(brace
r_struct
id|saa7134_dev
op_star
id|dev
op_assign
(paren
r_struct
id|saa7134_dev
op_star
)paren
id|data
suffix:semicolon
r_struct
id|saa7134_ir
op_star
id|ir
op_assign
id|dev-&gt;remote
suffix:semicolon
r_int
r_int
id|timeout
suffix:semicolon
id|build_key
c_func
(paren
id|dev
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
DECL|function|saa7134_input_init1
r_int
id|saa7134_input_init1
c_func
(paren
r_struct
id|saa7134_dev
op_star
id|dev
)paren
(brace
r_struct
id|saa7134_ir
op_star
id|ir
suffix:semicolon
id|IR_KEYTAB_TYPE
op_star
id|ir_codes
op_assign
l_int|NULL
suffix:semicolon
id|u32
id|mask_keycode
op_assign
l_int|0
suffix:semicolon
id|u32
id|mask_keydown
op_assign
l_int|0
suffix:semicolon
id|u32
id|mask_keyup
op_assign
l_int|0
suffix:semicolon
r_int
id|polling
op_assign
l_int|0
suffix:semicolon
r_int
id|ir_type
op_assign
id|IR_TYPE_OTHER
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;has_remote
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|disable_ir
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
multiline_comment|/* detect &amp; configure */
r_switch
c_cond
(paren
id|dev-&gt;board
)paren
(brace
r_case
id|SAA7134_BOARD_FLYVIDEO2000
suffix:colon
r_case
id|SAA7134_BOARD_FLYVIDEO3000
suffix:colon
id|ir_codes
op_assign
id|flyvideo_codes
suffix:semicolon
id|mask_keycode
op_assign
l_int|0xEC00000
suffix:semicolon
id|mask_keydown
op_assign
l_int|0x0040000
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SAA7134_BOARD_CINERGY400
suffix:colon
r_case
id|SAA7134_BOARD_CINERGY600
suffix:colon
r_case
id|SAA7134_BOARD_CINERGY600_MK3
suffix:colon
id|ir_codes
op_assign
id|cinergy_codes
suffix:semicolon
id|mask_keycode
op_assign
l_int|0x00003f
suffix:semicolon
id|mask_keyup
op_assign
l_int|0x040000
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SAA7134_BOARD_ECS_TVP3XP
suffix:colon
r_case
id|SAA7134_BOARD_ECS_TVP3XP_4CB5
suffix:colon
id|ir_codes
op_assign
id|eztv_codes
suffix:semicolon
id|mask_keycode
op_assign
l_int|0x00017c
suffix:semicolon
id|mask_keyup
op_assign
l_int|0x000002
suffix:semicolon
id|polling
op_assign
l_int|50
suffix:semicolon
singleline_comment|// ms
r_break
suffix:semicolon
r_case
id|SAA7134_BOARD_AVACSSMARTTV
suffix:colon
id|ir_codes
op_assign
id|avacssmart_codes
suffix:semicolon
id|mask_keycode
op_assign
l_int|0x00001F
suffix:semicolon
id|mask_keyup
op_assign
l_int|0x000020
suffix:semicolon
id|polling
op_assign
l_int|50
suffix:semicolon
singleline_comment|// ms
r_break
suffix:semicolon
r_case
id|SAA7134_BOARD_MD2819
suffix:colon
r_case
id|SAA7134_BOARD_AVERMEDIA_305
suffix:colon
r_case
id|SAA7134_BOARD_AVERMEDIA_307
suffix:colon
id|ir_codes
op_assign
id|md2819_codes
suffix:semicolon
id|mask_keycode
op_assign
l_int|0x0007C8
suffix:semicolon
id|mask_keydown
op_assign
l_int|0x000010
suffix:semicolon
id|polling
op_assign
l_int|50
suffix:semicolon
singleline_comment|// ms
multiline_comment|/* Set GPIO pin2 to high to enable the IR controller */
id|saa_setb
c_func
(paren
id|SAA7134_GPIO_GPMODE0
comma
l_int|0x4
)paren
suffix:semicolon
id|saa_setb
c_func
(paren
id|SAA7134_GPIO_GPSTATUS0
comma
l_int|0x4
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SAA7134_BOARD_VIDEOMATE_TV_PVR
suffix:colon
id|ir_codes
op_assign
id|videomate_tv_pvr_codes
suffix:semicolon
id|mask_keycode
op_assign
l_int|0x00003F
suffix:semicolon
id|mask_keyup
op_assign
l_int|0x400000
suffix:semicolon
id|polling
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
id|printk
c_func
(paren
l_string|&quot;%s: Oops: IR config error [card=%d]&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|dev-&gt;board
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
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
multiline_comment|/* init hardware-specific stuff */
id|ir-&gt;mask_keycode
op_assign
id|mask_keycode
suffix:semicolon
id|ir-&gt;mask_keydown
op_assign
id|mask_keydown
suffix:semicolon
id|ir-&gt;mask_keyup
op_assign
id|mask_keyup
suffix:semicolon
id|ir-&gt;polling
op_assign
id|polling
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
l_string|&quot;saa7134 IR (%s)&quot;
comma
id|saa7134_boards
(braket
id|dev-&gt;board
)braket
dot
id|name
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
id|dev-&gt;pci
)paren
)paren
suffix:semicolon
id|ir_input_init
c_func
(paren
op_amp
id|ir-&gt;dev
comma
op_amp
id|ir-&gt;ir
comma
id|ir_type
comma
id|ir_codes
)paren
suffix:semicolon
id|ir-&gt;dev.name
op_assign
id|ir-&gt;name
suffix:semicolon
id|ir-&gt;dev.phys
op_assign
id|ir-&gt;phys
suffix:semicolon
id|ir-&gt;dev.id.bustype
op_assign
id|BUS_PCI
suffix:semicolon
id|ir-&gt;dev.id.version
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;pci-&gt;subsystem_vendor
)paren
(brace
id|ir-&gt;dev.id.vendor
op_assign
id|dev-&gt;pci-&gt;subsystem_vendor
suffix:semicolon
id|ir-&gt;dev.id.product
op_assign
id|dev-&gt;pci-&gt;subsystem_device
suffix:semicolon
)brace
r_else
(brace
id|ir-&gt;dev.id.vendor
op_assign
id|dev-&gt;pci-&gt;vendor
suffix:semicolon
id|ir-&gt;dev.id.product
op_assign
id|dev-&gt;pci-&gt;device
suffix:semicolon
)brace
multiline_comment|/* all done */
id|dev-&gt;remote
op_assign
id|ir
suffix:semicolon
r_if
c_cond
(paren
id|ir-&gt;polling
)paren
(brace
id|init_timer
c_func
(paren
op_amp
id|ir-&gt;timer
)paren
suffix:semicolon
id|ir-&gt;timer.function
op_assign
id|saa7134_input_timer
suffix:semicolon
id|ir-&gt;timer.data
op_assign
(paren
r_int
r_int
)paren
id|dev
suffix:semicolon
id|ir-&gt;timer.expires
op_assign
id|jiffies
op_plus
id|HZ
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|ir-&gt;timer
)paren
suffix:semicolon
)brace
id|input_register_device
c_func
(paren
op_amp
id|dev-&gt;remote-&gt;dev
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: registered input device for IR&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|saa7134_input_fini
r_void
id|saa7134_input_fini
c_func
(paren
r_struct
id|saa7134_dev
op_star
id|dev
)paren
(brace
r_if
c_cond
(paren
l_int|NULL
op_eq
id|dev-&gt;remote
)paren
r_return
suffix:semicolon
id|input_unregister_device
c_func
(paren
op_amp
id|dev-&gt;remote-&gt;dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;remote-&gt;polling
)paren
id|del_timer_sync
c_func
(paren
op_amp
id|dev-&gt;remote-&gt;timer
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|dev-&gt;remote
)paren
suffix:semicolon
id|dev-&gt;remote
op_assign
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* ----------------------------------------------------------------------&n; * Local variables:&n; * c-basic-offset: 8&n; * End:&n; */
eof
