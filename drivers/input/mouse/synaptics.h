multiline_comment|/*&n; * Synaptics TouchPad PS/2 mouse driver&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License version 2 as published by&n; * the Free Software Foundation.&n; */
macro_line|#ifndef _SYNAPTICS_H
DECL|macro|_SYNAPTICS_H
mdefine_line|#define _SYNAPTICS_H
r_extern
r_void
id|synaptics_process_byte
c_func
(paren
r_struct
id|psmouse
op_star
id|psmouse
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_int
id|synaptics_init
c_func
(paren
r_struct
id|psmouse
op_star
id|psmouse
)paren
suffix:semicolon
r_extern
r_void
id|synaptics_disconnect
c_func
(paren
r_struct
id|psmouse
op_star
id|psmouse
)paren
suffix:semicolon
multiline_comment|/* synaptics queries */
DECL|macro|SYN_QUE_IDENTIFY
mdefine_line|#define SYN_QUE_IDENTIFY&t;&t;0x00
DECL|macro|SYN_QUE_MODES
mdefine_line|#define SYN_QUE_MODES&t;&t;&t;0x01
DECL|macro|SYN_QUE_CAPABILITIES
mdefine_line|#define SYN_QUE_CAPABILITIES&t;&t;0x02
DECL|macro|SYN_QUE_MODEL
mdefine_line|#define SYN_QUE_MODEL&t;&t;&t;0x03
DECL|macro|SYN_QUE_SERIAL_NUMBER_PREFIX
mdefine_line|#define SYN_QUE_SERIAL_NUMBER_PREFIX&t;0x06
DECL|macro|SYN_QUE_SERIAL_NUMBER_SUFFIX
mdefine_line|#define SYN_QUE_SERIAL_NUMBER_SUFFIX&t;0x07
DECL|macro|SYN_QUE_RESOLUTION
mdefine_line|#define SYN_QUE_RESOLUTION&t;&t;0x08
multiline_comment|/* synatics modes */
DECL|macro|SYN_BIT_ABSOLUTE_MODE
mdefine_line|#define SYN_BIT_ABSOLUTE_MODE&t;&t;(1 &lt;&lt; 7)
DECL|macro|SYN_BIT_HIGH_RATE
mdefine_line|#define SYN_BIT_HIGH_RATE&t;&t;(1 &lt;&lt; 6)
DECL|macro|SYN_BIT_SLEEP_MODE
mdefine_line|#define SYN_BIT_SLEEP_MODE&t;&t;(1 &lt;&lt; 3)
DECL|macro|SYN_BIT_DISABLE_GESTURE
mdefine_line|#define SYN_BIT_DISABLE_GESTURE&t;&t;(1 &lt;&lt; 2)
DECL|macro|SYN_BIT_W_MODE
mdefine_line|#define SYN_BIT_W_MODE&t;&t;&t;(1 &lt;&lt; 0)
multiline_comment|/* synaptics model ID bits */
DECL|macro|SYN_MODEL_ROT180
mdefine_line|#define SYN_MODEL_ROT180(m)&t;&t;((m) &amp; (1 &lt;&lt; 23))
DECL|macro|SYN_MODEL_PORTRAIT
mdefine_line|#define SYN_MODEL_PORTRAIT(m)&t;&t;((m) &amp; (1 &lt;&lt; 22))
DECL|macro|SYN_MODEL_SENSOR
mdefine_line|#define SYN_MODEL_SENSOR(m)&t;&t;(((m) &gt;&gt; 16) &amp; 0x3f)
DECL|macro|SYN_MODEL_HARDWARE
mdefine_line|#define SYN_MODEL_HARDWARE(m)&t;&t;(((m) &gt;&gt; 9) &amp; 0x7f)
DECL|macro|SYN_MODEL_NEWABS
mdefine_line|#define SYN_MODEL_NEWABS(m)&t;&t;((m) &amp; (1 &lt;&lt; 7))
DECL|macro|SYN_MODEL_PEN
mdefine_line|#define SYN_MODEL_PEN(m)&t;&t;((m) &amp; (1 &lt;&lt; 6))
DECL|macro|SYN_MODEL_SIMPLIC
mdefine_line|#define SYN_MODEL_SIMPLIC(m)&t;&t;((m) &amp; (1 &lt;&lt; 5))
DECL|macro|SYN_MODEL_GEOMETRY
mdefine_line|#define SYN_MODEL_GEOMETRY(m)&t;&t;((m) &amp; 0x0f)
multiline_comment|/* synaptics capability bits */
DECL|macro|SYN_CAP_EXTENDED
mdefine_line|#define SYN_CAP_EXTENDED(c)&t;&t;((c) &amp; (1 &lt;&lt; 23))
DECL|macro|SYN_CAP_SLEEP
mdefine_line|#define SYN_CAP_SLEEP(c)&t;&t;((c) &amp; (1 &lt;&lt; 4))
DECL|macro|SYN_CAP_FOUR_BUTTON
mdefine_line|#define SYN_CAP_FOUR_BUTTON(c)&t;&t;((c) &amp; (1 &lt;&lt; 3))
DECL|macro|SYN_CAP_MULTIFINGER
mdefine_line|#define SYN_CAP_MULTIFINGER(c)&t;&t;((c) &amp; (1 &lt;&lt; 1))
DECL|macro|SYN_CAP_PALMDETECT
mdefine_line|#define SYN_CAP_PALMDETECT(c)&t;&t;((c) &amp; (1 &lt;&lt; 0))
DECL|macro|SYN_CAP_VALID
mdefine_line|#define SYN_CAP_VALID(c)&t;&t;((((c) &amp; 0x00ff00) &gt;&gt; 8) == 0x47)
multiline_comment|/* synaptics modes query bits */
DECL|macro|SYN_MODE_ABSOLUTE
mdefine_line|#define SYN_MODE_ABSOLUTE(m)&t;&t;((m) &amp; (1 &lt;&lt; 7))
DECL|macro|SYN_MODE_RATE
mdefine_line|#define SYN_MODE_RATE(m)&t;&t;((m) &amp; (1 &lt;&lt; 6))
DECL|macro|SYN_MODE_BAUD_SLEEP
mdefine_line|#define SYN_MODE_BAUD_SLEEP(m)&t;&t;((m) &amp; (1 &lt;&lt; 3))
DECL|macro|SYN_MODE_DISABLE_GESTURE
mdefine_line|#define SYN_MODE_DISABLE_GESTURE(m)&t;((m) &amp; (1 &lt;&lt; 2))
DECL|macro|SYN_MODE_PACKSIZE
mdefine_line|#define SYN_MODE_PACKSIZE(m)&t;&t;((m) &amp; (1 &lt;&lt; 1))
DECL|macro|SYN_MODE_WMODE
mdefine_line|#define SYN_MODE_WMODE(m)&t;&t;((m) &amp; (1 &lt;&lt; 0))
multiline_comment|/* synaptics identify query bits */
DECL|macro|SYN_ID_MODEL
mdefine_line|#define SYN_ID_MODEL(i) &t;&t;(((i) &gt;&gt; 4) &amp; 0x0f)
DECL|macro|SYN_ID_MAJOR
mdefine_line|#define SYN_ID_MAJOR(i) &t;&t;((i) &amp; 0x0f)
DECL|macro|SYN_ID_MINOR
mdefine_line|#define SYN_ID_MINOR(i) &t;&t;(((i) &gt;&gt; 16) &amp; 0xff)
DECL|macro|SYN_ID_IS_SYNAPTICS
mdefine_line|#define SYN_ID_IS_SYNAPTICS(i)&t;&t;((((i) &gt;&gt; 8) &amp; 0xff) == 0x47)
multiline_comment|/*&n; * A structure to describe the state of the touchpad hardware (buttons and pad)&n; */
DECL|struct|synaptics_hw_state
r_struct
id|synaptics_hw_state
(brace
DECL|member|x
r_int
id|x
suffix:semicolon
DECL|member|y
r_int
id|y
suffix:semicolon
DECL|member|z
r_int
id|z
suffix:semicolon
DECL|member|w
r_int
id|w
suffix:semicolon
DECL|member|left
r_int
id|left
suffix:semicolon
DECL|member|right
r_int
id|right
suffix:semicolon
DECL|member|up
r_int
id|up
suffix:semicolon
DECL|member|down
r_int
id|down
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|synaptics_data
r_struct
id|synaptics_data
(brace
multiline_comment|/* Data read from the touchpad */
DECL|member|model_id
r_int
r_int
r_int
id|model_id
suffix:semicolon
multiline_comment|/* Model-ID */
DECL|member|capabilities
r_int
r_int
r_int
id|capabilities
suffix:semicolon
multiline_comment|/* Capabilities */
DECL|member|identity
r_int
r_int
r_int
id|identity
suffix:semicolon
multiline_comment|/* Identification */
multiline_comment|/* Data for normal processing */
DECL|member|proto_buf
r_int
r_char
id|proto_buf
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* Buffer for Packet */
DECL|member|last_byte
r_int
r_char
id|last_byte
suffix:semicolon
multiline_comment|/* last received byte */
DECL|member|inSync
r_int
id|inSync
suffix:semicolon
multiline_comment|/* Packets in sync */
DECL|member|proto_buf_tail
r_int
id|proto_buf_tail
suffix:semicolon
DECL|member|old_w
r_int
id|old_w
suffix:semicolon
multiline_comment|/* Previous w value */
)brace
suffix:semicolon
macro_line|#endif /* _SYNAPTICS_H */
eof
