multiline_comment|/*&n; *&t;Commands to the keyboard processor&n; */
DECL|macro|LK_PARAM
mdefine_line|#define&t;LK_PARAM&t;&t;0x80&t;/* start/end parameter list */
DECL|macro|LK_CMD_RESUME
mdefine_line|#define&t;LK_CMD_RESUME&t;&t;0x8b
DECL|macro|LK_CMD_INHIBIT
mdefine_line|#define&t;LK_CMD_INHIBIT&t;&t;0xb9
DECL|macro|LK_CMD_LEDS_ON
mdefine_line|#define&t;LK_CMD_LEDS_ON&t;&t;0x13&t;/* 1 param: led bitmask */
DECL|macro|LK_CMD_LEDS_OFF
mdefine_line|#define&t;LK_CMD_LEDS_OFF&t;&t;0x11&t;/* 1 param: led bitmask */
DECL|macro|LK_CMD_DIS_KEYCLK
mdefine_line|#define&t;LK_CMD_DIS_KEYCLK&t;0x99
DECL|macro|LK_CMD_ENB_KEYCLK
mdefine_line|#define&t;LK_CMD_ENB_KEYCLK&t;0x1b&t;/* 1 param: volume */
DECL|macro|LK_CMD_DIS_CTLCLK
mdefine_line|#define&t;LK_CMD_DIS_CTLCLK&t;0xb9
DECL|macro|LK_CMD_ENB_CTLCLK
mdefine_line|#define&t;LK_CMD_ENB_CTLCLK&t;0xbb
DECL|macro|LK_CMD_SOUND_CLK
mdefine_line|#define&t;LK_CMD_SOUND_CLK&t;0x9f
DECL|macro|LK_CMD_DIS_BELL
mdefine_line|#define&t;LK_CMD_DIS_BELL&t;&t;0xa1
DECL|macro|LK_CMD_ENB_BELL
mdefine_line|#define&t;LK_CMD_ENB_BELL&t;&t;0x23&t;/* 1 param: volume */
DECL|macro|LK_CMD_BELL
mdefine_line|#define&t;LK_CMD_BELL&t;&t;0xa7
DECL|macro|LK_CMD_TMP_NORPT
mdefine_line|#define&t;LK_CMD_TMP_NORPT&t;0xc1
DECL|macro|LK_CMD_ENB_RPT
mdefine_line|#define&t;LK_CMD_ENB_RPT&t;&t;0xe3
DECL|macro|LK_CMD_DIS_RPT
mdefine_line|#define&t;LK_CMD_DIS_RPT&t;&t;0xe1
DECL|macro|LK_CMD_RPT_TO_DOWN
mdefine_line|#define&t;LK_CMD_RPT_TO_DOWN&t;0xd9
DECL|macro|LK_CMD_REQ_ID
mdefine_line|#define&t;LK_CMD_REQ_ID&t;&t;0xab
DECL|macro|LK_CMD_POWER_UP
mdefine_line|#define&t;LK_CMD_POWER_UP&t;&t;0xfd
DECL|macro|LK_CMD_TEST_MODE
mdefine_line|#define&t;LK_CMD_TEST_MODE&t;0xcb
DECL|macro|LK_CMD_SET_DEFAULTS
mdefine_line|#define&t;LK_CMD_SET_DEFAULTS&t;0xd3
multiline_comment|/* there are 4 leds, represent them in the low 4 bits of a byte */
DECL|macro|LK_PARAM_LED_MASK
mdefine_line|#define&t;LK_PARAM_LED_MASK(ledbmap)&t;(LK_PARAM|(ledbmap))
multiline_comment|/* max volume is 0, lowest is 0x7 */
DECL|macro|LK_PARAM_VOLUME
mdefine_line|#define&t;LK_PARAM_VOLUME(v)&t;&t;(LK_PARAM|((v)&amp;0x7))
multiline_comment|/* mode set command(s) details */
DECL|macro|LK_MODE_DOWN
mdefine_line|#define&t;LK_MODE_DOWN&t;&t;0x0
DECL|macro|LK_MODE_RPT_DOWN
mdefine_line|#define&t;LK_MODE_RPT_DOWN&t;0x2
DECL|macro|LK_MODE_DOWN_UP
mdefine_line|#define&t;LK_MODE_DOWN_UP&t;&t;0x6
DECL|macro|LK_CMD_MODE
mdefine_line|#define&t;LK_CMD_MODE(m,div)&t;(LK_PARAM|(div&lt;&lt;3)|m)
DECL|macro|LK_SHIFT
mdefine_line|#define LK_SHIFT 1&lt;&lt;0
DECL|macro|LK_CTRL
mdefine_line|#define LK_CTRL 1&lt;&lt;1
DECL|macro|LK_LOCK
mdefine_line|#define LK_LOCK 1&lt;&lt;2
DECL|macro|LK_COMP
mdefine_line|#define LK_COMP 1&lt;&lt;3
DECL|macro|LK_KEY_SHIFT
mdefine_line|#define LK_KEY_SHIFT 174
DECL|macro|LK_KEY_CTRL
mdefine_line|#define LK_KEY_CTRL 175
DECL|macro|LK_KEY_LOCK
mdefine_line|#define LK_KEY_LOCK 176
DECL|macro|LK_KEY_COMP
mdefine_line|#define LK_KEY_COMP 177
DECL|macro|LK_KEY_RELEASE
mdefine_line|#define LK_KEY_RELEASE 179
DECL|macro|LK_KEY_REPEAT
mdefine_line|#define LK_KEY_REPEAT 180
DECL|macro|LK_KEY_ACK
mdefine_line|#define LK_KEY_ACK 186
r_extern
r_int
r_char
id|scancodeRemap
(braket
l_int|256
)braket
suffix:semicolon
eof
