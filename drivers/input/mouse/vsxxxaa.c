multiline_comment|/*&n; * DEC VSXXX-AA and VSXXX-GA mouse driver.&n; *&n; * Copyright (C) 2003-2004 by Jan-Benedict Glaw &lt;jbglaw@lug-owl.de&gt;&n; *&n; * The packet format was taken from a patch to GPM which is (C) 2001&n; * by&t;Karsten Merker &lt;merker@linuxtag.org&gt;&n; * and&t;Maciej W. Rozycki &lt;macro@ds2.pg.gda.pl&gt;&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; */
multiline_comment|/*&n; * Building an adaptor to DB9 / DB25 RS232&n; * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~&n; *&n; * DISCLAIMER: Use this description AT YOUR OWN RISK! I&squot;ll not pay for&n; * anything if you break your mouse, your computer or whatever!&n; *&n; * In theory, this mouse is a simple RS232 device. In practice, it has got&n; * a quite uncommon plug and the requirement to additionally get a power&n; * supply at +5V and -12V.&n; *&n; * If you look at the socket/jack (_not_ at the plug), we use this pin&n; * numbering:&n; *    _______&n; *   / 7 6 5 &bslash;&n; *  | 4 --- 3 |&n; *   &bslash;  2 1  /&n; *    -------&n; * &n; *&t;DEC socket&t;DB9&t;DB25&t;Note&n; *&t;1 (GND)&t;&t;5&t;7&t;-&n; *&t;2 (RxD)&t;&t;2&t;3&t;-&n; *&t;3 (TxD)&t;&t;3&t;2&t;-&n; *&t;4 (-12V)&t;-&t;-&t;Somewhere from the PSU. At ATX, it&squot;s&n; *&t;&t;&t;&t;&t;the thin blue wire at pin 12 of the&n; *&t;&t;&t;&t;&t;ATX power connector. Only required for&n; *&t;&t;&t;&t;&t;VSXXX-AA/-GA mice.&n; *&t;5 (+5V)&t;&t;-&t;-&t;PSU (red wires of ATX power connector&n; *&t;&t;&t;&t;&t;on pin 4, 6, 19 or 20) or HDD power&n; *&t;&t;&t;&t;&t;connector (also red wire).&n; *&t;6 (+12V)&t;-&t;-&t;HDD power connector, yellow wire. Only&n; *&t;&t;&t;&t;&t;required for VSXXX-AB digitizer.&n; *&t;7 (dev. avail.)&t;-&t;-&t;The mouse shorts this one to pin 1.&n; *&t;&t;&t;&t;&t;This way, the host computer can detect&n; *&t;&t;&t;&t;&t;the mouse. To use it with the adaptor,&n; *&t;&t;&t;&t;&t;simply don&squot;t connect this pin.&n; *&n; * So to get a working adaptor, you need to connect the mouse with three&n; * wires to a RS232 port and two or three additional wires for +5V, +12V and&n; * -12V to the PSU.&n; *&n; * Flow specification for the link is 4800, 8o1.&n; *&n; * The mice and tablet are described in &quot;VCB02 Video Subsystem - Technical&n; * Manual&quot;, DEC EK-104AA-TM-001. You&squot;ll find it at MANX, a search engine&n; * specific for DEC documentation. Try&n; * http://www.vt100.net/manx/details?pn=EK-104AA-TM-001;id=21;cp=1&n; */
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/input.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/serio.h&gt;
macro_line|#include &lt;linux/init.h&gt;
DECL|macro|DRIVER_DESC
mdefine_line|#define DRIVER_DESC&t;&quot;Serial DEC VSXXX-AA/GA mouse / DEC tablet driver&quot;
id|MODULE_AUTHOR
(paren
l_string|&quot;Jan-Benedict Glaw &lt;jbglaw@lug-owl.de&gt;&quot;
)paren
suffix:semicolon
DECL|variable|DRIVER_DESC
id|MODULE_DESCRIPTION
(paren
id|DRIVER_DESC
)paren
suffix:semicolon
id|MODULE_LICENSE
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|macro|VSXXXAA_DEBUG
macro_line|#undef VSXXXAA_DEBUG
macro_line|#ifdef VSXXXAA_DEBUG
DECL|macro|DBG
mdefine_line|#define DBG(x...) printk (x)
macro_line|#else
DECL|macro|DBG
mdefine_line|#define DBG(x...) do {} while (0)
macro_line|#endif
DECL|macro|VSXXXAA_INTRO_MASK
mdefine_line|#define VSXXXAA_INTRO_MASK&t;0x80
DECL|macro|VSXXXAA_INTRO_HEAD
mdefine_line|#define VSXXXAA_INTRO_HEAD&t;0x80
DECL|macro|IS_HDR_BYTE
mdefine_line|#define IS_HDR_BYTE(x)&t;&t;(((x) &amp; VSXXXAA_INTRO_MASK)&t;&bslash;&n;&t;&t;&t;&t;&t;== VSXXXAA_INTRO_HEAD)
DECL|macro|VSXXXAA_PACKET_MASK
mdefine_line|#define VSXXXAA_PACKET_MASK&t;0xe0
DECL|macro|VSXXXAA_PACKET_REL
mdefine_line|#define VSXXXAA_PACKET_REL&t;0x80
DECL|macro|VSXXXAA_PACKET_ABS
mdefine_line|#define VSXXXAA_PACKET_ABS&t;0xc0
DECL|macro|VSXXXAA_PACKET_POR
mdefine_line|#define VSXXXAA_PACKET_POR&t;0xa0
DECL|macro|MATCH_PACKET_TYPE
mdefine_line|#define MATCH_PACKET_TYPE(data, type)&t;(((data) &amp; VSXXXAA_PACKET_MASK) == type)
DECL|struct|vsxxxaa
r_struct
id|vsxxxaa
(brace
DECL|member|dev
r_struct
id|input_dev
id|dev
suffix:semicolon
DECL|member|serio
r_struct
id|serio
op_star
id|serio
suffix:semicolon
DECL|macro|BUFLEN
mdefine_line|#define BUFLEN 15 /* At least 5 is needed for a full tablet packet */
DECL|member|buf
r_int
r_char
id|buf
(braket
id|BUFLEN
)braket
suffix:semicolon
DECL|member|count
r_int
r_char
id|count
suffix:semicolon
DECL|member|version
r_int
r_char
id|version
suffix:semicolon
DECL|member|country
r_int
r_char
id|country
suffix:semicolon
DECL|member|type
r_int
r_char
id|type
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|64
)braket
suffix:semicolon
DECL|member|phys
r_char
id|phys
(braket
l_int|32
)braket
suffix:semicolon
)brace
suffix:semicolon
r_static
r_void
DECL|function|vsxxxaa_drop_bytes
id|vsxxxaa_drop_bytes
(paren
r_struct
id|vsxxxaa
op_star
id|mouse
comma
r_int
id|num
)paren
(brace
r_if
c_cond
(paren
id|num
op_ge
id|mouse-&gt;count
)paren
id|mouse-&gt;count
op_assign
l_int|0
suffix:semicolon
r_else
(brace
id|memmove
(paren
id|mouse-&gt;buf
comma
id|mouse-&gt;buf
op_plus
id|num
op_minus
l_int|1
comma
id|BUFLEN
op_minus
id|num
)paren
suffix:semicolon
id|mouse-&gt;count
op_sub_assign
id|num
suffix:semicolon
)brace
)brace
r_static
r_void
DECL|function|vsxxxaa_queue_byte
id|vsxxxaa_queue_byte
(paren
r_struct
id|vsxxxaa
op_star
id|mouse
comma
r_int
r_char
id|byte
)paren
(brace
r_if
c_cond
(paren
id|mouse-&gt;count
op_eq
id|BUFLEN
)paren
(brace
id|printk
(paren
id|KERN_ERR
l_string|&quot;%s on %s: Dropping a byte of full buffer.&bslash;n&quot;
comma
id|mouse-&gt;name
comma
id|mouse-&gt;phys
)paren
suffix:semicolon
id|vsxxxaa_drop_bytes
(paren
id|mouse
comma
l_int|1
)paren
suffix:semicolon
)brace
id|DBG
(paren
id|KERN_INFO
l_string|&quot;Queueing byte 0x%02x&bslash;n&quot;
comma
id|byte
)paren
suffix:semicolon
id|mouse-&gt;buf
(braket
id|mouse-&gt;count
op_increment
)braket
op_assign
id|byte
suffix:semicolon
)brace
r_static
r_void
DECL|function|vsxxxaa_detection_done
id|vsxxxaa_detection_done
(paren
r_struct
id|vsxxxaa
op_star
id|mouse
)paren
(brace
r_switch
c_cond
(paren
id|mouse-&gt;type
)paren
(brace
r_case
l_int|0x02
suffix:colon
id|sprintf
(paren
id|mouse-&gt;name
comma
l_string|&quot;DEC VSXXX-AA/GA mouse&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x04
suffix:colon
id|sprintf
(paren
id|mouse-&gt;name
comma
l_string|&quot;DEC VSXXX-AB digitizer&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|sprintf
(paren
id|mouse-&gt;name
comma
l_string|&quot;unknown DEC pointer device&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|printk
(paren
id|KERN_INFO
l_string|&quot;Found %s version 0x%02x from country 0x%02x &quot;
l_string|&quot;on port %s&bslash;n&quot;
comma
id|mouse-&gt;name
comma
id|mouse-&gt;version
comma
id|mouse-&gt;country
comma
id|mouse-&gt;phys
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Returns number of bytes to be dropped, 0 if packet is okay.&n; */
r_static
r_int
DECL|function|vsxxxaa_check_packet
id|vsxxxaa_check_packet
(paren
r_struct
id|vsxxxaa
op_star
id|mouse
comma
r_int
id|packet_len
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* First byte must be a header byte */
r_if
c_cond
(paren
op_logical_neg
id|IS_HDR_BYTE
(paren
id|mouse-&gt;buf
(braket
l_int|0
)braket
)paren
)paren
(brace
id|DBG
(paren
l_string|&quot;vsck: len=%d, 1st=0x%02x&bslash;n&quot;
comma
id|packet_len
comma
id|mouse-&gt;buf
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Check all following bytes */
r_if
c_cond
(paren
id|packet_len
OG
l_int|1
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|packet_len
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|IS_HDR_BYTE
(paren
id|mouse-&gt;buf
(braket
id|i
)braket
)paren
)paren
(brace
id|printk
(paren
id|KERN_ERR
l_string|&quot;Need to drop %d bytes &quot;
l_string|&quot;of a broken packet.&bslash;n&quot;
comma
id|i
op_minus
l_int|1
)paren
suffix:semicolon
id|DBG
(paren
id|KERN_INFO
l_string|&quot;check: len=%d, b[%d]=0x%02x&bslash;n&quot;
comma
id|packet_len
comma
id|i
comma
id|mouse-&gt;buf
(braket
id|i
)braket
)paren
suffix:semicolon
r_return
id|i
op_minus
l_int|1
suffix:semicolon
)brace
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
id|__inline__
r_int
DECL|function|vsxxxaa_smells_like_packet
id|vsxxxaa_smells_like_packet
(paren
r_struct
id|vsxxxaa
op_star
id|mouse
comma
r_int
r_char
id|type
comma
r_int
id|len
)paren
(brace
r_return
(paren
id|mouse-&gt;count
op_ge
id|len
)paren
op_logical_and
id|MATCH_PACKET_TYPE
(paren
id|mouse-&gt;buf
(braket
l_int|0
)braket
comma
id|type
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|vsxxxaa_handle_REL_packet
id|vsxxxaa_handle_REL_packet
(paren
r_struct
id|vsxxxaa
op_star
id|mouse
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|input_dev
op_star
id|dev
op_assign
op_amp
id|mouse-&gt;dev
suffix:semicolon
r_int
r_char
op_star
id|buf
op_assign
id|mouse-&gt;buf
suffix:semicolon
r_int
id|left
comma
id|middle
comma
id|right
suffix:semicolon
r_int
id|dx
comma
id|dy
suffix:semicolon
multiline_comment|/*&n;&t; * Check for normal stream packets. This is three bytes,&n;&t; * with the first byte&squot;s 3 MSB set to 100.&n;&t; *&n;&t; * [0]:&t;1&t;0&t;0&t;SignX&t;SignY&t;Left&t;Middle&t;Right&n;&t; * [1]: 0&t;dx&t;dx&t;dx&t;dx&t;dx&t;dx&t;dx&n;&t; * [2]:&t;0&t;dy&t;dy&t;dy&t;dy&t;dy&t;dy&t;dy&n;&t; */
multiline_comment|/*&n;&t; * Low 7 bit of byte 1 are abs(dx), bit 7 is&n;&t; * 0, bit 4 of byte 0 is direction.&n;&t; */
id|dx
op_assign
id|buf
(braket
l_int|1
)braket
op_amp
l_int|0x7f
suffix:semicolon
id|dx
op_mul_assign
(paren
(paren
id|buf
(braket
l_int|0
)braket
op_rshift
l_int|4
)paren
op_amp
l_int|0x01
)paren
ques
c_cond
l_int|1
suffix:colon
op_minus
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * Low 7 bit of byte 2 are abs(dy), bit 7 is&n;&t; * 0, bit 3 of byte 0 is direction.&n;&t; */
id|dy
op_assign
id|buf
(braket
l_int|2
)braket
op_amp
l_int|0x7f
suffix:semicolon
id|dy
op_mul_assign
(paren
(paren
id|buf
(braket
l_int|0
)braket
op_rshift
l_int|3
)paren
op_amp
l_int|0x01
)paren
ques
c_cond
op_minus
l_int|1
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * Get button state. It&squot;s the low three bits&n;&t; * (for three buttons) of byte 0.&n;&t; */
id|left
op_assign
(paren
id|buf
(braket
l_int|0
)braket
op_amp
l_int|0x04
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|middle
op_assign
(paren
id|buf
(braket
l_int|0
)braket
op_amp
l_int|0x02
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|right
op_assign
(paren
id|buf
(braket
l_int|0
)braket
op_amp
l_int|0x01
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|vsxxxaa_drop_bytes
(paren
id|mouse
comma
l_int|3
)paren
suffix:semicolon
id|DBG
(paren
id|KERN_INFO
l_string|&quot;%s on %s: dx=%d, dy=%d, buttons=%s%s%s&bslash;n&quot;
comma
id|mouse-&gt;name
comma
id|mouse-&gt;phys
comma
id|dx
comma
id|dy
comma
id|left
ques
c_cond
l_string|&quot;L&quot;
suffix:colon
l_string|&quot;l&quot;
comma
id|middle
ques
c_cond
l_string|&quot;M&quot;
suffix:colon
l_string|&quot;m&quot;
comma
id|right
ques
c_cond
l_string|&quot;R&quot;
suffix:colon
l_string|&quot;r&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Report what we&squot;ve found so far...&n;&t; */
id|input_regs
(paren
id|dev
comma
id|regs
)paren
suffix:semicolon
id|input_report_key
(paren
id|dev
comma
id|BTN_LEFT
comma
id|left
)paren
suffix:semicolon
id|input_report_key
(paren
id|dev
comma
id|BTN_MIDDLE
comma
id|middle
)paren
suffix:semicolon
id|input_report_key
(paren
id|dev
comma
id|BTN_RIGHT
comma
id|right
)paren
suffix:semicolon
id|input_report_key
(paren
id|dev
comma
id|BTN_TOUCH
comma
l_int|0
)paren
suffix:semicolon
id|input_report_rel
(paren
id|dev
comma
id|REL_X
comma
id|dx
)paren
suffix:semicolon
id|input_report_rel
(paren
id|dev
comma
id|REL_Y
comma
id|dy
)paren
suffix:semicolon
id|input_sync
(paren
id|dev
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|vsxxxaa_handle_ABS_packet
id|vsxxxaa_handle_ABS_packet
(paren
r_struct
id|vsxxxaa
op_star
id|mouse
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|input_dev
op_star
id|dev
op_assign
op_amp
id|mouse-&gt;dev
suffix:semicolon
r_int
r_char
op_star
id|buf
op_assign
id|mouse-&gt;buf
suffix:semicolon
r_int
id|left
comma
id|middle
comma
id|right
comma
id|touch
suffix:semicolon
r_int
id|x
comma
id|y
suffix:semicolon
multiline_comment|/*&n;&t; * Tablet position / button packet&n;&t; *&n;&t; * [0]:&t;1&t;1&t;0&t;B4&t;B3&t;B2&t;B1&t;Pr&n;&t; * [1]:&t;0&t;0&t;X5&t;X4&t;X3&t;X2&t;X1&t;X0&n;&t; * [2]:&t;0&t;0&t;X11&t;X10&t;X9&t;X8&t;X7&t;X6&n;&t; * [3]:&t;0&t;0&t;Y5&t;Y4&t;Y3&t;Y2&t;Y1&t;Y0&n;&t; * [4]:&t;0&t;0&t;Y11&t;Y10&t;Y9&t;Y8&t;Y7&t;Y6&n;&t; */
multiline_comment|/*&n;&t; * Get X/Y position. Y axis needs to be inverted since VSXXX-AB&n;&t; * counts down-&gt;top while monitor counts top-&gt;bottom.&n;&t; */
id|x
op_assign
(paren
(paren
id|buf
(braket
l_int|2
)braket
op_amp
l_int|0x3f
)paren
op_lshift
l_int|6
)paren
op_or
(paren
id|buf
(braket
l_int|1
)braket
op_amp
l_int|0x3f
)paren
suffix:semicolon
id|y
op_assign
(paren
(paren
id|buf
(braket
l_int|4
)braket
op_amp
l_int|0x3f
)paren
op_lshift
l_int|6
)paren
op_or
(paren
id|buf
(braket
l_int|3
)braket
op_amp
l_int|0x3f
)paren
suffix:semicolon
id|y
op_assign
l_int|1023
op_minus
id|y
suffix:semicolon
multiline_comment|/*&n;&t; * Get button state. It&squot;s bits &lt;4..1&gt; of byte 0.&n;&t; */
id|left
op_assign
(paren
id|buf
(braket
l_int|0
)braket
op_amp
l_int|0x02
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|middle
op_assign
(paren
id|buf
(braket
l_int|0
)braket
op_amp
l_int|0x04
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|right
op_assign
(paren
id|buf
(braket
l_int|0
)braket
op_amp
l_int|0x08
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|touch
op_assign
(paren
id|buf
(braket
l_int|0
)braket
op_amp
l_int|0x10
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|vsxxxaa_drop_bytes
(paren
id|mouse
comma
l_int|5
)paren
suffix:semicolon
id|DBG
(paren
id|KERN_INFO
l_string|&quot;%s on %s: x=%d, y=%d, buttons=%s%s%s%s&bslash;n&quot;
comma
id|mouse-&gt;name
comma
id|mouse-&gt;phys
comma
id|x
comma
id|y
comma
id|left
ques
c_cond
l_string|&quot;L&quot;
suffix:colon
l_string|&quot;l&quot;
comma
id|middle
ques
c_cond
l_string|&quot;M&quot;
suffix:colon
l_string|&quot;m&quot;
comma
id|right
ques
c_cond
l_string|&quot;R&quot;
suffix:colon
l_string|&quot;r&quot;
comma
id|touch
ques
c_cond
l_string|&quot;T&quot;
suffix:colon
l_string|&quot;t&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Report what we&squot;ve found so far...&n;&t; */
id|input_regs
(paren
id|dev
comma
id|regs
)paren
suffix:semicolon
id|input_report_key
(paren
id|dev
comma
id|BTN_LEFT
comma
id|left
)paren
suffix:semicolon
id|input_report_key
(paren
id|dev
comma
id|BTN_MIDDLE
comma
id|middle
)paren
suffix:semicolon
id|input_report_key
(paren
id|dev
comma
id|BTN_RIGHT
comma
id|right
)paren
suffix:semicolon
id|input_report_key
(paren
id|dev
comma
id|BTN_TOUCH
comma
id|touch
)paren
suffix:semicolon
id|input_report_abs
(paren
id|dev
comma
id|ABS_X
comma
id|x
)paren
suffix:semicolon
id|input_report_abs
(paren
id|dev
comma
id|ABS_Y
comma
id|y
)paren
suffix:semicolon
id|input_sync
(paren
id|dev
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|vsxxxaa_handle_POR_packet
id|vsxxxaa_handle_POR_packet
(paren
r_struct
id|vsxxxaa
op_star
id|mouse
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|input_dev
op_star
id|dev
op_assign
op_amp
id|mouse-&gt;dev
suffix:semicolon
r_int
r_char
op_star
id|buf
op_assign
id|mouse-&gt;buf
suffix:semicolon
r_int
id|left
comma
id|middle
comma
id|right
suffix:semicolon
r_int
r_char
id|error
suffix:semicolon
multiline_comment|/*&n;&t; * Check for Power-On-Reset packets. These are sent out&n;&t; * after plugging the mouse in, or when explicitely&n;&t; * requested by sending &squot;T&squot;.&n;&t; *&n;&t; * [0]:&t;1&t;0&t;1&t;0&t;R3&t;R2&t;R1&t;R0&n;&t; * [1]:&t;0&t;M2&t;M1&t;M0&t;D3&t;D2&t;D1&t;D0&n;&t; * [2]:&t;0&t;E6&t;E5&t;E4&t;E3&t;E2&t;E1&t;E0&n;&t; * [3]:&t;0&t;0&t;0&t;0&t;0&t;Left&t;Middle&t;Right&n;&t; *&n;&t; * M: manufacturer location code&n;&t; * R: revision code&n;&t; * E: Error code. I&squot;m not sure about these, but gpm&squot;s sources,&n;&t; *    which support this mouse, too, tell about them:&n;&t; *&t;E = [0x00 .. 0x1f]: no error, byte #3 is button state&n;&t; *&t;E = 0x3d: button error, byte #3 tells which one.&n;&t; *&t;E = &lt;else&gt;: other error&n;&t; * D: &lt;0010&gt; == mouse, &lt;0100&gt; == tablet&n;&t; *&n;&t; */
id|mouse-&gt;version
op_assign
id|buf
(braket
l_int|0
)braket
op_amp
l_int|0x0f
suffix:semicolon
id|mouse-&gt;country
op_assign
(paren
id|buf
(braket
l_int|1
)braket
op_rshift
l_int|4
)paren
op_amp
l_int|0x07
suffix:semicolon
id|mouse-&gt;type
op_assign
id|buf
(braket
l_int|1
)braket
op_amp
l_int|0x0f
suffix:semicolon
id|error
op_assign
id|buf
(braket
l_int|2
)braket
op_amp
l_int|0x7f
suffix:semicolon
multiline_comment|/*&n;&t; * Get button state. It&squot;s the low three bits&n;&t; * (for three buttons) of byte 0. Maybe even the bit &lt;3&gt;&n;&t; * has some meaning if a tablet is attached.&n;&t; */
id|left
op_assign
(paren
id|buf
(braket
l_int|0
)braket
op_amp
l_int|0x04
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|middle
op_assign
(paren
id|buf
(braket
l_int|0
)braket
op_amp
l_int|0x02
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|right
op_assign
(paren
id|buf
(braket
l_int|0
)braket
op_amp
l_int|0x01
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|vsxxxaa_drop_bytes
(paren
id|mouse
comma
l_int|4
)paren
suffix:semicolon
id|vsxxxaa_detection_done
(paren
id|mouse
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
op_le
l_int|0x1f
)paren
(brace
multiline_comment|/* No error. Report buttons */
id|input_regs
(paren
id|dev
comma
id|regs
)paren
suffix:semicolon
id|input_report_key
(paren
id|dev
comma
id|BTN_LEFT
comma
id|left
)paren
suffix:semicolon
id|input_report_key
(paren
id|dev
comma
id|BTN_MIDDLE
comma
id|middle
)paren
suffix:semicolon
id|input_report_key
(paren
id|dev
comma
id|BTN_RIGHT
comma
id|right
)paren
suffix:semicolon
id|input_report_key
(paren
id|dev
comma
id|BTN_TOUCH
comma
l_int|0
)paren
suffix:semicolon
id|input_sync
(paren
id|dev
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
(paren
id|KERN_ERR
l_string|&quot;Your %s on %s reports an undefined error, &quot;
l_string|&quot;please check it...&bslash;n&quot;
comma
id|mouse-&gt;name
comma
id|mouse-&gt;phys
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * If the mouse was hot-plugged, we need to force differential mode&n;&t; * now... However, give it a second to recover from it&squot;s reset.&n;&t; */
id|printk
(paren
id|KERN_NOTICE
l_string|&quot;%s on %s: Forceing standard packet format and &quot;
l_string|&quot;streaming mode&bslash;n&quot;
comma
id|mouse-&gt;name
comma
id|mouse-&gt;phys
)paren
suffix:semicolon
id|mouse-&gt;serio-&gt;write
(paren
id|mouse-&gt;serio
comma
l_char|&squot;S&squot;
)paren
suffix:semicolon
id|mdelay
(paren
l_int|50
)paren
suffix:semicolon
id|mouse-&gt;serio-&gt;write
(paren
id|mouse-&gt;serio
comma
l_char|&squot;R&squot;
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|vsxxxaa_parse_buffer
id|vsxxxaa_parse_buffer
(paren
r_struct
id|vsxxxaa
op_star
id|mouse
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_char
op_star
id|buf
op_assign
id|mouse-&gt;buf
suffix:semicolon
r_int
id|stray_bytes
suffix:semicolon
multiline_comment|/*&n;&t; * Parse buffer to death...&n;&t; */
r_do
(brace
multiline_comment|/*&n;&t;&t; * Out of sync? Throw away what we don&squot;t understand. Each&n;&t;&t; * packet starts with a byte whose bit 7 is set. Unhandled&n;&t;&t; * packets (ie. which we don&squot;t know about or simply b0rk3d&n;&t;&t; * data...) will get shifted out of the buffer after some&n;&t;&t; * activity on the mouse.&n;&t;&t; */
r_while
c_loop
(paren
id|mouse-&gt;count
OG
l_int|0
op_logical_and
op_logical_neg
id|IS_HDR_BYTE
c_func
(paren
id|buf
(braket
l_int|0
)braket
)paren
)paren
(brace
id|printk
(paren
id|KERN_ERR
l_string|&quot;%s on %s: Dropping a byte to regain &quot;
l_string|&quot;sync with mouse data stream...&bslash;n&quot;
comma
id|mouse-&gt;name
comma
id|mouse-&gt;phys
)paren
suffix:semicolon
id|vsxxxaa_drop_bytes
(paren
id|mouse
comma
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Check for packets we know about.&n;&t;&t; */
r_if
c_cond
(paren
id|vsxxxaa_smells_like_packet
(paren
id|mouse
comma
id|VSXXXAA_PACKET_REL
comma
l_int|3
)paren
)paren
(brace
multiline_comment|/* Check for broken packet */
id|stray_bytes
op_assign
id|vsxxxaa_check_packet
(paren
id|mouse
comma
l_int|3
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stray_bytes
OG
l_int|0
)paren
(brace
id|printk
(paren
id|KERN_ERR
l_string|&quot;Dropping %d bytes now...&bslash;n&quot;
comma
id|stray_bytes
)paren
suffix:semicolon
id|vsxxxaa_drop_bytes
(paren
id|mouse
comma
id|stray_bytes
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|vsxxxaa_handle_REL_packet
(paren
id|mouse
comma
id|regs
)paren
suffix:semicolon
r_continue
suffix:semicolon
multiline_comment|/* More to parse? */
)brace
r_if
c_cond
(paren
id|vsxxxaa_smells_like_packet
(paren
id|mouse
comma
id|VSXXXAA_PACKET_ABS
comma
l_int|5
)paren
)paren
(brace
multiline_comment|/* Check for broken packet */
id|stray_bytes
op_assign
id|vsxxxaa_check_packet
(paren
id|mouse
comma
l_int|5
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stray_bytes
OG
l_int|0
)paren
(brace
id|printk
(paren
id|KERN_ERR
l_string|&quot;Dropping %d bytes now...&bslash;n&quot;
comma
id|stray_bytes
)paren
suffix:semicolon
id|vsxxxaa_drop_bytes
(paren
id|mouse
comma
id|stray_bytes
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|vsxxxaa_handle_ABS_packet
(paren
id|mouse
comma
id|regs
)paren
suffix:semicolon
r_continue
suffix:semicolon
multiline_comment|/* More to parse? */
)brace
r_if
c_cond
(paren
id|vsxxxaa_smells_like_packet
(paren
id|mouse
comma
id|VSXXXAA_PACKET_POR
comma
l_int|4
)paren
)paren
(brace
multiline_comment|/* Check for broken packet */
id|stray_bytes
op_assign
id|vsxxxaa_check_packet
(paren
id|mouse
comma
l_int|4
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stray_bytes
OG
l_int|0
)paren
(brace
id|printk
(paren
id|KERN_ERR
l_string|&quot;Dropping %d bytes now...&bslash;n&quot;
comma
id|stray_bytes
)paren
suffix:semicolon
id|vsxxxaa_drop_bytes
(paren
id|mouse
comma
id|stray_bytes
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|vsxxxaa_handle_POR_packet
(paren
id|mouse
comma
id|regs
)paren
suffix:semicolon
r_continue
suffix:semicolon
multiline_comment|/* More to parse? */
)brace
r_break
suffix:semicolon
multiline_comment|/* No REL, ABS or POR packet found */
)brace
r_while
c_loop
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_static
id|irqreturn_t
DECL|function|vsxxxaa_interrupt
id|vsxxxaa_interrupt
(paren
r_struct
id|serio
op_star
id|serio
comma
r_int
r_char
id|data
comma
r_int
r_int
id|flags
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|vsxxxaa
op_star
id|mouse
op_assign
id|serio
op_member_access_from_pointer
r_private
suffix:semicolon
id|vsxxxaa_queue_byte
(paren
id|mouse
comma
id|data
)paren
suffix:semicolon
id|vsxxxaa_parse_buffer
(paren
id|mouse
comma
id|regs
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
r_static
r_void
DECL|function|vsxxxaa_disconnect
id|vsxxxaa_disconnect
(paren
r_struct
id|serio
op_star
id|serio
)paren
(brace
r_struct
id|vsxxxaa
op_star
id|mouse
op_assign
id|serio
op_member_access_from_pointer
r_private
suffix:semicolon
id|input_unregister_device
(paren
op_amp
id|mouse-&gt;dev
)paren
suffix:semicolon
id|serio_close
(paren
id|serio
)paren
suffix:semicolon
id|kfree
(paren
id|mouse
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|vsxxxaa_connect
id|vsxxxaa_connect
(paren
r_struct
id|serio
op_star
id|serio
comma
r_struct
id|serio_driver
op_star
id|drv
)paren
(brace
r_struct
id|vsxxxaa
op_star
id|mouse
suffix:semicolon
r_if
c_cond
(paren
(paren
id|serio-&gt;type
op_amp
id|SERIO_TYPE
)paren
op_ne
id|SERIO_RS232
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
(paren
id|serio-&gt;type
op_amp
id|SERIO_PROTO
)paren
op_ne
id|SERIO_VSXXXAA
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|mouse
op_assign
id|kmalloc
(paren
r_sizeof
(paren
r_struct
id|vsxxxaa
)paren
comma
id|GFP_KERNEL
)paren
)paren
)paren
r_return
suffix:semicolon
id|memset
(paren
id|mouse
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|vsxxxaa
)paren
)paren
suffix:semicolon
id|init_input_dev
(paren
op_amp
id|mouse-&gt;dev
)paren
suffix:semicolon
id|set_bit
(paren
id|EV_KEY
comma
id|mouse-&gt;dev.evbit
)paren
suffix:semicolon
multiline_comment|/* We have buttons */
id|set_bit
(paren
id|EV_REL
comma
id|mouse-&gt;dev.evbit
)paren
suffix:semicolon
id|set_bit
(paren
id|EV_ABS
comma
id|mouse-&gt;dev.evbit
)paren
suffix:semicolon
id|set_bit
(paren
id|BTN_LEFT
comma
id|mouse-&gt;dev.keybit
)paren
suffix:semicolon
multiline_comment|/* We have 3 buttons */
id|set_bit
(paren
id|BTN_MIDDLE
comma
id|mouse-&gt;dev.keybit
)paren
suffix:semicolon
id|set_bit
(paren
id|BTN_RIGHT
comma
id|mouse-&gt;dev.keybit
)paren
suffix:semicolon
id|set_bit
(paren
id|BTN_TOUCH
comma
id|mouse-&gt;dev.keybit
)paren
suffix:semicolon
multiline_comment|/* ...and Tablet */
id|set_bit
(paren
id|REL_X
comma
id|mouse-&gt;dev.relbit
)paren
suffix:semicolon
id|set_bit
(paren
id|REL_Y
comma
id|mouse-&gt;dev.relbit
)paren
suffix:semicolon
id|set_bit
(paren
id|ABS_X
comma
id|mouse-&gt;dev.absbit
)paren
suffix:semicolon
id|set_bit
(paren
id|ABS_Y
comma
id|mouse-&gt;dev.absbit
)paren
suffix:semicolon
id|mouse-&gt;dev.absmin
(braket
id|ABS_X
)braket
op_assign
l_int|0
suffix:semicolon
id|mouse-&gt;dev.absmax
(braket
id|ABS_X
)braket
op_assign
l_int|1023
suffix:semicolon
id|mouse-&gt;dev.absmin
(braket
id|ABS_Y
)braket
op_assign
l_int|0
suffix:semicolon
id|mouse-&gt;dev.absmax
(braket
id|ABS_Y
)braket
op_assign
l_int|1023
suffix:semicolon
id|mouse-&gt;dev
dot
r_private
op_assign
id|mouse
suffix:semicolon
id|serio
op_member_access_from_pointer
r_private
op_assign
id|mouse
suffix:semicolon
id|sprintf
(paren
id|mouse-&gt;name
comma
l_string|&quot;DEC VSXXX-AA/GA mouse or VSXXX-AB digitizer&quot;
)paren
suffix:semicolon
id|sprintf
(paren
id|mouse-&gt;phys
comma
l_string|&quot;%s/input0&quot;
comma
id|serio-&gt;phys
)paren
suffix:semicolon
id|mouse-&gt;dev.name
op_assign
id|mouse-&gt;name
suffix:semicolon
id|mouse-&gt;dev.phys
op_assign
id|mouse-&gt;phys
suffix:semicolon
id|mouse-&gt;dev.id.bustype
op_assign
id|BUS_RS232
suffix:semicolon
id|mouse-&gt;serio
op_assign
id|serio
suffix:semicolon
r_if
c_cond
(paren
id|serio_open
(paren
id|serio
comma
id|drv
)paren
)paren
(brace
id|kfree
(paren
id|mouse
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Request selftest. Standard packet format and differential&n;&t; * mode will be requested after the device ID&squot;ed successfully.&n;&t; */
id|mouse-&gt;serio-&gt;write
(paren
id|mouse-&gt;serio
comma
l_char|&squot;T&squot;
)paren
suffix:semicolon
multiline_comment|/* Test */
id|input_register_device
(paren
op_amp
id|mouse-&gt;dev
)paren
suffix:semicolon
id|printk
(paren
id|KERN_INFO
l_string|&quot;input: %s on %s&bslash;n&quot;
comma
id|mouse-&gt;name
comma
id|mouse-&gt;phys
)paren
suffix:semicolon
)brace
DECL|variable|vsxxxaa_drv
r_static
r_struct
id|serio_driver
id|vsxxxaa_drv
op_assign
(brace
dot
id|driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;vsxxxaa&quot;
comma
)brace
comma
dot
id|description
op_assign
id|DRIVER_DESC
comma
dot
id|connect
op_assign
id|vsxxxaa_connect
comma
dot
id|interrupt
op_assign
id|vsxxxaa_interrupt
comma
dot
id|disconnect
op_assign
id|vsxxxaa_disconnect
comma
)brace
suffix:semicolon
r_int
id|__init
DECL|function|vsxxxaa_init
id|vsxxxaa_init
(paren
r_void
)paren
(brace
id|serio_register_driver
c_func
(paren
op_amp
id|vsxxxaa_drv
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_void
id|__exit
DECL|function|vsxxxaa_exit
id|vsxxxaa_exit
(paren
r_void
)paren
(brace
id|serio_unregister_driver
c_func
(paren
op_amp
id|vsxxxaa_drv
)paren
suffix:semicolon
)brace
DECL|variable|vsxxxaa_init
id|module_init
(paren
id|vsxxxaa_init
)paren
suffix:semicolon
DECL|variable|vsxxxaa_exit
id|module_exit
(paren
id|vsxxxaa_exit
)paren
suffix:semicolon
eof
