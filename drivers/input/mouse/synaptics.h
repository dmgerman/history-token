multiline_comment|/*&n; * Synaptics TouchPad PS/2 mouse driver&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License version 2 as published by&n; * the Free Software Foundation.&n; */
macro_line|#ifndef _SYNAPTICS_H
DECL|macro|_SYNAPTICS_H
mdefine_line|#define _SYNAPTICS_H
r_extern
r_int
id|synaptics_detect
c_func
(paren
r_struct
id|psmouse
op_star
id|psmouse
comma
r_int
id|set_properties
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
id|synaptics_reset
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
DECL|macro|SYN_QUE_EXT_CAPAB
mdefine_line|#define SYN_QUE_EXT_CAPAB&t;&t;0x09
multiline_comment|/* synatics modes */
DECL|macro|SYN_BIT_ABSOLUTE_MODE
mdefine_line|#define SYN_BIT_ABSOLUTE_MODE&t;&t;(1 &lt;&lt; 7)
DECL|macro|SYN_BIT_HIGH_RATE
mdefine_line|#define SYN_BIT_HIGH_RATE&t;&t;(1 &lt;&lt; 6)
DECL|macro|SYN_BIT_SLEEP_MODE
mdefine_line|#define SYN_BIT_SLEEP_MODE&t;&t;(1 &lt;&lt; 3)
DECL|macro|SYN_BIT_DISABLE_GESTURE
mdefine_line|#define SYN_BIT_DISABLE_GESTURE&t;&t;(1 &lt;&lt; 2)
DECL|macro|SYN_BIT_FOUR_BYTE_CLIENT
mdefine_line|#define SYN_BIT_FOUR_BYTE_CLIENT&t;(1 &lt;&lt; 1)
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
DECL|macro|SYN_CAP_MIDDLE_BUTTON
mdefine_line|#define SYN_CAP_MIDDLE_BUTTON(c)&t;((c) &amp; (1 &lt;&lt; 18))
DECL|macro|SYN_CAP_PASS_THROUGH
mdefine_line|#define SYN_CAP_PASS_THROUGH(c)&t;&t;((c) &amp; (1 &lt;&lt; 7))
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
DECL|macro|SYN_EXT_CAP_REQUESTS
mdefine_line|#define SYN_EXT_CAP_REQUESTS(c)&t;&t;(((c) &amp; 0x700000) &gt;&gt; 20)
DECL|macro|SYN_CAP_MULTI_BUTTON_NO
mdefine_line|#define SYN_CAP_MULTI_BUTTON_NO(ec)&t;(((ec) &amp; 0x00f000) &gt;&gt; 12)
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
multiline_comment|/* synaptics special commands */
DECL|macro|SYN_PS_SET_MODE2
mdefine_line|#define SYN_PS_SET_MODE2&t;&t;0x14
DECL|macro|SYN_PS_CLIENT_CMD
mdefine_line|#define SYN_PS_CLIENT_CMD&t;&t;0x28
multiline_comment|/* synaptics packet types */
DECL|macro|SYN_NEWABS
mdefine_line|#define SYN_NEWABS&t;&t;&t;0
DECL|macro|SYN_NEWABS_STRICT
mdefine_line|#define SYN_NEWABS_STRICT&t;&t;1
DECL|macro|SYN_NEWABS_RELAXED
mdefine_line|#define SYN_NEWABS_RELAXED&t;&t;2
DECL|macro|SYN_OLDABS
mdefine_line|#define SYN_OLDABS&t;&t;&t;3
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
r_int
id|left
suffix:colon
l_int|1
suffix:semicolon
DECL|member|right
r_int
r_int
id|right
suffix:colon
l_int|1
suffix:semicolon
DECL|member|middle
r_int
r_int
id|middle
suffix:colon
l_int|1
suffix:semicolon
DECL|member|up
r_int
r_int
id|up
suffix:colon
l_int|1
suffix:semicolon
DECL|member|down
r_int
r_int
id|down
suffix:colon
l_int|1
suffix:semicolon
DECL|member|ext_buttons
r_int
r_char
id|ext_buttons
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
DECL|member|ext_cap
r_int
r_int
r_int
id|ext_cap
suffix:semicolon
multiline_comment|/* Extended Capabilities */
DECL|member|identity
r_int
r_int
r_int
id|identity
suffix:semicolon
multiline_comment|/* Identification */
DECL|member|pkt_type
r_int
r_char
id|pkt_type
suffix:semicolon
multiline_comment|/* packet type - old, new, etc */
DECL|member|mode
r_int
r_char
id|mode
suffix:semicolon
multiline_comment|/* current mode byte */
)brace
suffix:semicolon
macro_line|#endif /* _SYNAPTICS_H */
eof
