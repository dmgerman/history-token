multiline_comment|/*&n; * $Id: h3600_ts_input.c,v 1.4 2002/01/23 06:39:37 jsimmons Exp $&n; *&n; *  Copyright (c) 2001 &quot;Crazy&quot; James Simmons jsimmons@transvirtual.com&n; *&n; *  Sponsored by Transvirtual Technology.&n; *&n; *  Derived from the code in h3600_ts.[ch] by Charles Flynn&n; */
multiline_comment|/*&n; * Driver for the h3600 Touch Screen and other Atmel controlled devices.&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; *&n; * Should you need to contact me, the author, you can do so by&n; * e-mail - mail your message to &lt;jsimmons@transvirtual.com&gt;.&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/input.h&gt;
macro_line|#include &lt;linux/serio.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/pm.h&gt;
multiline_comment|/* SA1100 serial defines */
macro_line|#include &lt;asm/arch/hardware.h&gt;
macro_line|#include &lt;asm/arch/irqs.h&gt;
DECL|macro|DRIVER_DESC
mdefine_line|#define DRIVER_DESC&t;&quot;H3600 touchscreen driver&quot;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;James Simmons &lt;jsimmons@transvirtual.com&gt;&quot;
)paren
suffix:semicolon
DECL|variable|DRIVER_DESC
id|MODULE_DESCRIPTION
c_func
(paren
id|DRIVER_DESC
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
multiline_comment|/*&n; * Definitions &amp; global arrays.&n; */
multiline_comment|/* The start and end of frame characters SOF and EOF */
DECL|macro|CHAR_SOF
mdefine_line|#define CHAR_SOF                0x02
DECL|macro|CHAR_EOF
mdefine_line|#define CHAR_EOF                0x03
DECL|macro|FRAME_OVERHEAD
mdefine_line|#define FRAME_OVERHEAD          3       /* CHAR_SOF,CHAR_EOF,LENGTH = 3 */
multiline_comment|/*&n;        Atmel events and response IDs contained in frame.&n;        Programmer has no control over these numbers.&n;        TODO there are holes - specifically  1,7,0x0a&n;*/
DECL|macro|VERSION_ID
mdefine_line|#define VERSION_ID              0       /* Get Version (request/respose) */
DECL|macro|KEYBD_ID
mdefine_line|#define KEYBD_ID                2       /* Keyboard (event) */
DECL|macro|TOUCHS_ID
mdefine_line|#define TOUCHS_ID               3       /* Touch Screen (event)*/
DECL|macro|EEPROM_READ_ID
mdefine_line|#define EEPROM_READ_ID          4       /* (request/response) */
DECL|macro|EEPROM_WRITE_ID
mdefine_line|#define EEPROM_WRITE_ID         5       /* (request/response) */
DECL|macro|THERMAL_ID
mdefine_line|#define THERMAL_ID              6       /* (request/response) */
DECL|macro|NOTIFY_LED_ID
mdefine_line|#define NOTIFY_LED_ID           8       /* (request/response) */
DECL|macro|BATTERY_ID
mdefine_line|#define BATTERY_ID              9       /* (request/response) */
DECL|macro|SPI_READ_ID
mdefine_line|#define SPI_READ_ID             0x0b    /* ( request/response) */
DECL|macro|SPI_WRITE_ID
mdefine_line|#define SPI_WRITE_ID            0x0c    /* ( request/response) */
DECL|macro|FLITE_ID
mdefine_line|#define FLITE_ID                0x0d    /* backlight ( request/response) */
DECL|macro|STX_ID
mdefine_line|#define STX_ID                  0xa1    /* extension pack status (req/resp) */
DECL|macro|MAX_ID
mdefine_line|#define MAX_ID                  14
DECL|macro|H3600_MAX_LENGTH
mdefine_line|#define H3600_MAX_LENGTH 16
DECL|macro|H3600_KEY
mdefine_line|#define H3600_KEY 0xf
DECL|macro|H3600_SCANCODE_RECORD
mdefine_line|#define H3600_SCANCODE_RECORD&t;1&t; /* 1 -&gt; record button */
DECL|macro|H3600_SCANCODE_CALENDAR
mdefine_line|#define H3600_SCANCODE_CALENDAR 2&t; /* 2 -&gt; calendar */
DECL|macro|H3600_SCANCODE_CONTACTS
mdefine_line|#define H3600_SCANCODE_CONTACTS 3&t; /* 3 -&gt; contact */
DECL|macro|H3600_SCANCODE_Q
mdefine_line|#define H3600_SCANCODE_Q&t;4&t; /* 4 -&gt; Q button */
DECL|macro|H3600_SCANCODE_START
mdefine_line|#define&t;H3600_SCANCODE_START&t;5&t; /* 5 -&gt; start menu */
DECL|macro|H3600_SCANCODE_UP
mdefine_line|#define&t;H3600_SCANCODE_UP&t;6&t; /* 6 -&gt; up */
DECL|macro|H3600_SCANCODE_RIGHT
mdefine_line|#define H3600_SCANCODE_RIGHT&t;7 &t; /* 7 -&gt; right */
DECL|macro|H3600_SCANCODE_LEFT
mdefine_line|#define H3600_SCANCODE_LEFT &t;8&t; /* 8 -&gt; left */
DECL|macro|H3600_SCANCODE_DOWN
mdefine_line|#define H3600_SCANCODE_DOWN &t;9&t; /* 9 -&gt; down */
DECL|variable|h3600_name
r_static
r_char
op_star
id|h3600_name
op_assign
l_string|&quot;H3600 TouchScreen&quot;
suffix:semicolon
multiline_comment|/*&n; * Per-touchscreen data.&n; */
DECL|struct|h3600_dev
r_struct
id|h3600_dev
(brace
DECL|member|dev
r_struct
id|input_dev
id|dev
suffix:semicolon
DECL|member|pm_dev
r_struct
id|pm_dev
op_star
id|pm_dev
suffix:semicolon
DECL|member|serio
r_struct
id|serio
op_star
id|serio
suffix:semicolon
DECL|member|pm_dev
r_struct
id|pm_dev
op_star
id|pm_dev
suffix:semicolon
DECL|member|event
r_int
r_char
id|event
suffix:semicolon
multiline_comment|/* event ID from packet */
DECL|member|chksum
r_int
r_char
id|chksum
suffix:semicolon
DECL|member|len
r_int
r_char
id|len
suffix:semicolon
DECL|member|idx
r_int
r_char
id|idx
suffix:semicolon
DECL|member|buf
r_int
r_char
id|buf
(braket
id|H3600_MAX_LENGTH
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
DECL|function|action_button_handler
r_static
id|irqreturn_t
id|action_button_handler
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|down
op_assign
(paren
id|GPLR
op_amp
id|GPIO_BITSY_ACTION_BUTTON
)paren
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
r_struct
id|input_dev
op_star
id|dev
op_assign
(paren
r_struct
id|input_dev
op_star
)paren
id|dev_id
suffix:semicolon
id|input_regs
c_func
(paren
id|dev
comma
id|regs
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|KEY_ENTER
comma
id|down
)paren
suffix:semicolon
id|input_sync
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
DECL|function|npower_button_handler
r_static
id|irqreturn_t
id|npower_button_handler
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|down
op_assign
(paren
id|GPLR
op_amp
id|GPIO_BITSY_NPOWER_BUTTON
)paren
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
r_struct
id|input_dev
op_star
id|dev
op_assign
(paren
r_struct
id|input_dev
op_star
)paren
id|dev_id
suffix:semicolon
multiline_comment|/*&n;&t; * This interrupt is only called when we release the key. So we have&n;&t; * to fake a key press.&n;&t; */
id|input_regs
c_func
(paren
id|dev
comma
id|regs
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|KEY_SUSPEND
comma
l_int|1
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|KEY_SUSPEND
comma
id|down
)paren
suffix:semicolon
id|input_sync
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_PM
DECL|variable|flite_brightness
r_static
r_int
id|flite_brightness
op_assign
l_int|25
suffix:semicolon
DECL|enum|flite_pwr
r_enum
id|flite_pwr
(brace
DECL|enumerator|FLITE_PWR_OFF
id|FLITE_PWR_OFF
op_assign
l_int|0
comma
DECL|enumerator|FLITE_PWR_ON
id|FLITE_PWR_ON
op_assign
l_int|1
)brace
suffix:semicolon
multiline_comment|/*&n; * h3600_flite_power: enables or disables power to frontlight, using last bright */
DECL|function|h3600_flite_power
r_int
r_int
id|h3600_flite_power
c_func
(paren
r_struct
id|input_dev
op_star
id|dev
comma
r_enum
id|flite_pwr
id|pwr
)paren
(brace
r_int
r_char
id|brightness
op_assign
(paren
id|pwr
op_eq
id|FLITE_PWR_OFF
)paren
ques
c_cond
l_int|0
suffix:colon
id|flite_brightness
suffix:semicolon
r_struct
id|h3600_dev
op_star
id|ts
op_assign
id|dev
op_member_access_from_pointer
r_private
suffix:semicolon
multiline_comment|/* Must be in this order */
id|ts-&gt;serio
op_member_access_from_pointer
id|write
c_func
(paren
id|ts-&gt;serio
comma
l_int|1
)paren
suffix:semicolon
id|ts-&gt;serio
op_member_access_from_pointer
id|write
c_func
(paren
id|ts-&gt;serio
comma
id|pwr
)paren
suffix:semicolon
id|ts-&gt;serio
op_member_access_from_pointer
id|write
c_func
(paren
id|ts-&gt;serio
comma
id|brightness
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|suspended
r_static
r_int
id|suspended
op_assign
l_int|0
suffix:semicolon
DECL|function|h3600ts_pm_callback
r_static
r_int
id|h3600ts_pm_callback
c_func
(paren
r_struct
id|pm_dev
op_star
id|pm_dev
comma
id|pm_request_t
id|req
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|input_dev
op_star
id|dev
op_assign
(paren
r_struct
id|input_dev
op_star
)paren
id|data
suffix:semicolon
r_switch
c_cond
(paren
id|req
)paren
(brace
r_case
id|PM_SUSPEND
suffix:colon
multiline_comment|/* enter D1-D3 */
id|suspended
op_assign
l_int|1
suffix:semicolon
id|h3600_flite_power
c_func
(paren
id|dev
comma
id|FLITE_PWR_OFF
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PM_BLANK
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|suspended
)paren
id|h3600_flite_power
c_func
(paren
id|dev
comma
id|FLITE_PWR_OFF
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PM_RESUME
suffix:colon
multiline_comment|/* enter D0 */
multiline_comment|/* same as unblank */
r_case
id|PM_UNBLANK
suffix:colon
r_if
c_cond
(paren
id|suspended
)paren
(brace
singleline_comment|//initSerial();
id|suspended
op_assign
l_int|0
suffix:semicolon
)brace
id|h3600_flite_power
c_func
(paren
id|dev
comma
id|FLITE_PWR_ON
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * This function translates the native event packets to linux input event&n; * packets. Some packets coming from serial are not touchscreen related. In&n; * this case we send them off to be processed elsewhere.&n; */
DECL|function|h3600ts_process_packet
r_static
r_void
id|h3600ts_process_packet
c_func
(paren
r_struct
id|h3600_dev
op_star
id|ts
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
id|ts-&gt;dev
suffix:semicolon
r_static
r_int
id|touched
op_assign
l_int|0
suffix:semicolon
r_int
id|key
comma
id|down
op_assign
l_int|0
suffix:semicolon
id|input_regs
c_func
(paren
id|dev
comma
id|regs
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|ts-&gt;event
)paren
(brace
multiline_comment|/*&n;                   Buttons - returned as a single byte&n;                        7 6 5 4 3 2 1 0&n;                        S x x x N N N N&n;&n;                   S       switch state ( 0=pressed 1=released)&n;                   x       Unused.&n;                   NNNN    switch number 0-15&n;&n;                Note: This is true for non interrupt generated key events.&n;                */
r_case
id|KEYBD_ID
suffix:colon
id|down
op_assign
(paren
id|ts-&gt;buf
(braket
l_int|0
)braket
op_amp
l_int|0x80
)paren
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
r_switch
c_cond
(paren
id|ts-&gt;buf
(braket
l_int|0
)braket
op_amp
l_int|0x7f
)paren
(brace
r_case
id|H3600_SCANCODE_RECORD
suffix:colon
id|key
op_assign
id|KEY_RECORD
suffix:semicolon
r_break
suffix:semicolon
r_case
id|H3600_SCANCODE_CALENDAR
suffix:colon
id|key
op_assign
id|KEY_PROG1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|H3600_SCANCODE_CONTACTS
suffix:colon
id|key
op_assign
id|KEY_PROG2
suffix:semicolon
r_break
suffix:semicolon
r_case
id|H3600_SCANCODE_Q
suffix:colon
id|key
op_assign
id|KEY_Q
suffix:semicolon
r_break
suffix:semicolon
r_case
id|H3600_SCANCODE_START
suffix:colon
id|key
op_assign
id|KEY_PROG3
suffix:semicolon
r_break
suffix:semicolon
r_case
id|H3600_SCANCODE_UP
suffix:colon
id|key
op_assign
id|KEY_UP
suffix:semicolon
r_break
suffix:semicolon
r_case
id|H3600_SCANCODE_RIGHT
suffix:colon
id|key
op_assign
id|KEY_RIGHT
suffix:semicolon
r_break
suffix:semicolon
r_case
id|H3600_SCANCODE_LEFT
suffix:colon
id|key
op_assign
id|KEY_LEFT
suffix:semicolon
r_break
suffix:semicolon
r_case
id|H3600_SCANCODE_DOWN
suffix:colon
id|key
op_assign
id|KEY_DOWN
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|key
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|key
)paren
id|input_report_key
c_func
(paren
id|dev
comma
id|key
comma
id|down
)paren
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/*&n;                 * Native touchscreen event data is formatted as shown below:-&n;                 *&n;                 *      +-------+-------+-------+-------+&n;                 *      | Xmsb  | Xlsb  | Ymsb  | Ylsb  |&n;                 *      +-------+-------+-------+-------+&n;                 *       byte 0    1       2       3&n;                 */
r_case
id|TOUCHS_ID
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|touched
)paren
(brace
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_TOUCH
comma
l_int|1
)paren
suffix:semicolon
id|touched
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ts-&gt;len
)paren
(brace
r_int
r_int
id|x
comma
id|y
suffix:semicolon
id|x
op_assign
id|ts-&gt;buf
(braket
l_int|0
)braket
suffix:semicolon
id|x
op_lshift_assign
l_int|8
suffix:semicolon
id|x
op_add_assign
id|ts-&gt;buf
(braket
l_int|1
)braket
suffix:semicolon
id|y
op_assign
id|ts-&gt;buf
(braket
l_int|2
)braket
suffix:semicolon
id|y
op_lshift_assign
l_int|8
suffix:semicolon
id|y
op_add_assign
id|ts-&gt;buf
(braket
l_int|3
)braket
suffix:semicolon
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_X
comma
id|x
)paren
suffix:semicolon
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_Y
comma
id|y
)paren
suffix:semicolon
)brace
r_else
(brace
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_TOUCH
comma
l_int|0
)paren
suffix:semicolon
id|touched
op_assign
l_int|0
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* Send a non input event elsewhere */
r_break
suffix:semicolon
)brace
id|input_sync
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * h3600ts_event() handles events from the input module.&n; */
DECL|function|h3600ts_event
r_static
r_int
id|h3600ts_event
c_func
(paren
r_struct
id|input_dev
op_star
id|dev
comma
r_int
r_int
id|type
comma
r_int
r_int
id|code
comma
r_int
id|value
)paren
(brace
r_struct
id|h3600_dev
op_star
id|ts
op_assign
id|dev
op_member_access_from_pointer
r_private
suffix:semicolon
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
id|EV_LED
suffix:colon
(brace
singleline_comment|//&t;ts-&gt;serio-&gt;write(ts-&gt;serio, SOME_CMD);
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n;        Frame format&n;  byte    1       2               3              len + 4&n;        +-------+---------------+---------------+--=------------+&n;        |SOF    |id     |len    | len bytes     | Chksum        |&n;        +-------+---------------+---------------+--=------------+&n;  bit   0     7  8    11 12   15 16&n;&n;        +-------+---------------+-------+&n;        |SOF    |id     |0      |Chksum | - Note Chksum does not include SOF&n;        +-------+---------------+-------+&n;  bit   0     7  8    11 12   15 16&n;&n;*/
DECL|variable|state
r_static
r_int
id|state
suffix:semicolon
multiline_comment|/* decode States  */
DECL|macro|STATE_SOF
mdefine_line|#define STATE_SOF       0       /* start of FRAME */
DECL|macro|STATE_ID
mdefine_line|#define STATE_ID        1       /* state where we decode the ID &amp; len */
DECL|macro|STATE_DATA
mdefine_line|#define STATE_DATA      2       /* state where we decode data */
DECL|macro|STATE_EOF
mdefine_line|#define STATE_EOF       3       /* state where we decode checksum or EOF */
DECL|function|h3600ts_interrupt
r_static
id|irqreturn_t
id|h3600ts_interrupt
c_func
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
id|h3600_dev
op_star
id|ts
op_assign
id|serio_get_drvdata
c_func
(paren
id|serio
)paren
suffix:semicolon
multiline_comment|/*&n;         * We have a new frame coming in.&n;         */
r_switch
c_cond
(paren
id|state
)paren
(brace
r_case
id|STATE_SOF
suffix:colon
r_if
c_cond
(paren
id|data
op_eq
id|CHAR_SOF
)paren
id|state
op_assign
id|STATE_ID
suffix:semicolon
r_break
suffix:semicolon
r_case
id|STATE_ID
suffix:colon
id|ts-&gt;event
op_assign
(paren
id|data
op_amp
l_int|0xf0
)paren
op_rshift
l_int|4
suffix:semicolon
id|ts-&gt;len
op_assign
(paren
id|data
op_amp
l_int|0xf
)paren
suffix:semicolon
id|ts-&gt;idx
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|ts-&gt;event
op_ge
id|MAX_ID
)paren
(brace
id|state
op_assign
id|STATE_SOF
suffix:semicolon
r_break
suffix:semicolon
)brace
id|ts-&gt;chksum
op_assign
id|data
suffix:semicolon
id|state
op_assign
(paren
id|ts-&gt;len
OG
l_int|0
)paren
ques
c_cond
id|STATE_DATA
suffix:colon
id|STATE_EOF
suffix:semicolon
r_break
suffix:semicolon
r_case
id|STATE_DATA
suffix:colon
id|ts-&gt;chksum
op_add_assign
id|data
suffix:semicolon
id|ts-&gt;buf
(braket
id|ts-&gt;idx
)braket
op_assign
id|data
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|ts-&gt;idx
op_eq
id|ts-&gt;len
)paren
(brace
id|state
op_assign
id|STATE_EOF
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|STATE_EOF
suffix:colon
id|state
op_assign
id|STATE_SOF
suffix:semicolon
r_if
c_cond
(paren
id|data
op_eq
id|CHAR_EOF
op_logical_or
id|data
op_eq
id|ts-&gt;chksum
)paren
id|h3600ts_process_packet
c_func
(paren
id|ts
comma
id|regs
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;Error3&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
multiline_comment|/*&n; * h3600ts_connect() is the routine that is called when someone adds a&n; * new serio device that supports H3600 protocol and registers it as&n; * an input device.&n; */
DECL|function|h3600ts_connect
r_static
r_void
id|h3600ts_connect
c_func
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
id|h3600_dev
op_star
id|ts
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|ts
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|h3600_dev
)paren
comma
id|GFP_KERNEL
)paren
)paren
)paren
r_return
suffix:semicolon
id|memset
c_func
(paren
id|ts
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|h3600_dev
)paren
)paren
suffix:semicolon
id|init_input_dev
c_func
(paren
op_amp
id|ts-&gt;dev
)paren
suffix:semicolon
multiline_comment|/* Device specific stuff */
id|set_GPIO_IRQ_edge
c_func
(paren
id|GPIO_BITSY_ACTION_BUTTON
comma
id|GPIO_BOTH_EDGES
)paren
suffix:semicolon
id|set_GPIO_IRQ_edge
c_func
(paren
id|GPIO_BITSY_NPOWER_BUTTON
comma
id|GPIO_RISING_EDGE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|IRQ_GPIO_BITSY_ACTION_BUTTON
comma
id|action_button_handler
comma
id|SA_SHIRQ
op_or
id|SA_INTERRUPT
op_or
id|SA_SAMPLE_RANDOM
comma
l_string|&quot;h3600_action&quot;
comma
op_amp
id|ts-&gt;dev
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;h3600ts.c: Could not allocate Action Button IRQ!&bslash;n&quot;
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|ts
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|IRQ_GPIO_BITSY_NPOWER_BUTTON
comma
id|npower_button_handler
comma
id|SA_SHIRQ
op_or
id|SA_INTERRUPT
op_or
id|SA_SAMPLE_RANDOM
comma
l_string|&quot;h3600_suspend&quot;
comma
op_amp
id|ts-&gt;dev
)paren
)paren
(brace
id|free_irq
c_func
(paren
id|IRQ_GPIO_BITSY_ACTION_BUTTON
comma
op_amp
id|ts-&gt;dev
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;h3600ts.c: Could not allocate Power Button IRQ!&bslash;n&quot;
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|ts
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Now we have things going we setup our input device */
id|ts-&gt;dev.evbit
(braket
l_int|0
)braket
op_assign
id|BIT
c_func
(paren
id|EV_KEY
)paren
op_or
id|BIT
c_func
(paren
id|EV_ABS
)paren
op_or
id|BIT
c_func
(paren
id|EV_LED
)paren
op_or
id|BIT
c_func
(paren
id|EV_PWR
)paren
suffix:semicolon
id|ts-&gt;dev.ledbit
(braket
l_int|0
)braket
op_assign
id|BIT
c_func
(paren
id|LED_SLEEP
)paren
suffix:semicolon
id|input_set_abs_params
c_func
(paren
op_amp
id|ts-&gt;dev
comma
id|ABS_X
comma
l_int|60
comma
l_int|985
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|input_set_abs_params
c_func
(paren
op_amp
id|ts-&gt;dev
comma
id|ABS_Y
comma
l_int|35
comma
l_int|1024
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|KEY_RECORD
comma
id|ts-&gt;dev.keybit
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|KEY_Q
comma
id|ts-&gt;dev.keybit
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|KEY_PROG1
comma
id|ts-&gt;dev.keybit
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|KEY_PROG2
comma
id|ts-&gt;dev.keybit
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|KEY_PROG3
comma
id|ts-&gt;dev.keybit
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|KEY_UP
comma
id|ts-&gt;dev.keybit
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|KEY_RIGHT
comma
id|ts-&gt;dev.keybit
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|KEY_LEFT
comma
id|ts-&gt;dev.keybit
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|KEY_DOWN
comma
id|ts-&gt;dev.keybit
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|KEY_ENTER
comma
id|ts-&gt;dev.keybit
)paren
suffix:semicolon
id|ts-&gt;dev.keybit
(braket
id|LONG
c_func
(paren
id|BTN_TOUCH
)paren
)braket
op_or_assign
id|BIT
c_func
(paren
id|BTN_TOUCH
)paren
suffix:semicolon
id|ts-&gt;dev.keybit
(braket
id|LONG
c_func
(paren
id|KEY_SUSPEND
)paren
)braket
op_or_assign
id|BIT
c_func
(paren
id|KEY_SUSPEND
)paren
suffix:semicolon
id|ts-&gt;serio
op_assign
id|serio
suffix:semicolon
id|sprintf
c_func
(paren
id|ts-&gt;phys
comma
l_string|&quot;%s/input0&quot;
comma
id|serio-&gt;phys
)paren
suffix:semicolon
id|ts-&gt;dev.event
op_assign
id|h3600ts_event
suffix:semicolon
id|ts-&gt;dev
dot
r_private
op_assign
id|ts
suffix:semicolon
id|ts-&gt;dev.name
op_assign
id|h3600_name
suffix:semicolon
id|ts-&gt;dev.phys
op_assign
id|ts-&gt;phys
suffix:semicolon
id|ts-&gt;dev.id.bustype
op_assign
id|BUS_RS232
suffix:semicolon
id|ts-&gt;dev.id.vendor
op_assign
id|SERIO_H3600
suffix:semicolon
id|ts-&gt;dev.id.product
op_assign
l_int|0x0666
suffix:semicolon
multiline_comment|/* FIXME !!! We can ask the hardware */
id|ts-&gt;dev.id.version
op_assign
l_int|0x0100
suffix:semicolon
id|serio_set_drvdata
c_func
(paren
id|serio
comma
id|ts
)paren
suffix:semicolon
r_if
c_cond
(paren
id|serio_open
c_func
(paren
id|serio
comma
id|drv
)paren
)paren
(brace
id|free_irq
c_func
(paren
id|IRQ_GPIO_BITSY_ACTION_BUTTON
comma
id|ts
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|IRQ_GPIO_BITSY_NPOWER_BUTTON
comma
id|ts
)paren
suffix:semicolon
id|serio_set_drvdata
c_func
(paren
id|serio
comma
l_int|NULL
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|ts
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
singleline_comment|//h3600_flite_control(1, 25);     /* default brightness */
macro_line|#ifdef CONFIG_PM
id|ts-&gt;pm_dev
op_assign
id|pm_register
c_func
(paren
id|PM_ILLUMINATION_DEV
comma
id|PM_SYS_LIGHT
comma
id|h3600ts_pm_callback
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;registered pm callback&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|input_register_device
c_func
(paren
op_amp
id|ts-&gt;dev
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;input: %s on %s&bslash;n&quot;
comma
id|h3600_name
comma
id|serio-&gt;phys
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * h3600ts_disconnect() is the opposite of h3600ts_connect()&n; */
DECL|function|h3600ts_disconnect
r_static
r_void
id|h3600ts_disconnect
c_func
(paren
r_struct
id|serio
op_star
id|serio
)paren
(brace
r_struct
id|h3600_dev
op_star
id|ts
op_assign
id|serio_get_drvdata
c_func
(paren
id|serio
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|IRQ_GPIO_BITSY_ACTION_BUTTON
comma
op_amp
id|ts-&gt;dev
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|IRQ_GPIO_BITSY_NPOWER_BUTTON
comma
op_amp
id|ts-&gt;dev
)paren
suffix:semicolon
id|input_unregister_device
c_func
(paren
op_amp
id|ts-&gt;dev
)paren
suffix:semicolon
id|serio_close
c_func
(paren
id|serio
)paren
suffix:semicolon
id|serio_set_drvdata
c_func
(paren
id|serio
comma
l_int|NULL
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|ts
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The serio driver structure.&n; */
DECL|variable|h3600ts_serio_ids
r_static
r_struct
id|serio_device_id
id|h3600ts_serio_ids
(braket
)braket
op_assign
(brace
(brace
dot
id|type
op_assign
id|SERIO_RS232
comma
dot
id|proto
op_assign
id|SERIO_H3600
comma
dot
id|id
op_assign
id|SERIO_ANY
comma
dot
id|extra
op_assign
id|SERIO_ANY
comma
)brace
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
c_func
(paren
id|serio
comma
id|h3600ts_serio_ids
)paren
suffix:semicolon
DECL|variable|h3600ts_drv
r_static
r_struct
id|serio_driver
id|h3600ts_drv
op_assign
(brace
dot
id|driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;h3600ts&quot;
comma
)brace
comma
dot
id|description
op_assign
id|DRIVER_DESC
comma
dot
id|id_table
op_assign
id|h3600ts_serio_ids
comma
dot
id|interrupt
op_assign
id|h3600ts_interrupt
comma
dot
id|connect
op_assign
id|h3600ts_connect
comma
dot
id|disconnect
op_assign
id|h3600ts_disconnect
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * The functions for inserting/removing us as a module.&n; */
DECL|function|h3600ts_init
r_static
r_int
id|__init
id|h3600ts_init
c_func
(paren
r_void
)paren
(brace
id|serio_register_driver
c_func
(paren
op_amp
id|h3600ts_drv
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|h3600ts_exit
r_static
r_void
id|__exit
id|h3600ts_exit
c_func
(paren
r_void
)paren
(brace
id|serio_unregister_driver
c_func
(paren
op_amp
id|h3600ts_drv
)paren
suffix:semicolon
)brace
DECL|variable|h3600ts_init
id|module_init
c_func
(paren
id|h3600ts_init
)paren
suffix:semicolon
DECL|variable|h3600ts_exit
id|module_exit
c_func
(paren
id|h3600ts_exit
)paren
suffix:semicolon
eof
