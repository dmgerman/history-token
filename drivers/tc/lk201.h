multiline_comment|/*&n; *&t;Commands to the keyboard processor&n; */
DECL|macro|LK_PARAM
mdefine_line|#define LK_PARAM&t;&t;0x80&t;/* start/end parameter list */
DECL|macro|LK_CMD_RESUME
mdefine_line|#define LK_CMD_RESUME&t;&t;0x8b&t;/* resume transmission to the host */
DECL|macro|LK_CMD_INHIBIT
mdefine_line|#define LK_CMD_INHIBIT&t;&t;0x89&t;/* stop transmission to the host */
DECL|macro|LK_CMD_LEDS_ON
mdefine_line|#define LK_CMD_LEDS_ON&t;&t;0x13&t;/* light LEDs */
multiline_comment|/* 1st param: led bitmask */
DECL|macro|LK_CMD_LEDS_OFF
mdefine_line|#define LK_CMD_LEDS_OFF&t;&t;0x11&t;/* turn off LEDs */
multiline_comment|/* 1st param: led bitmask */
DECL|macro|LK_CMD_DIS_KEYCLK
mdefine_line|#define LK_CMD_DIS_KEYCLK&t;0x99&t;/* disable the keyclick */
DECL|macro|LK_CMD_ENB_KEYCLK
mdefine_line|#define LK_CMD_ENB_KEYCLK&t;0x1b&t;/* enable the keyclick */
multiline_comment|/* 1st param: volume */
DECL|macro|LK_CMD_DIS_CTLCLK
mdefine_line|#define LK_CMD_DIS_CTLCLK&t;0xb9&t;/* disable the Ctrl keyclick */
DECL|macro|LK_CMD_ENB_CTLCLK
mdefine_line|#define LK_CMD_ENB_CTLCLK&t;0xbb&t;/* enable the Ctrl keyclick */
DECL|macro|LK_CMD_SOUND_CLK
mdefine_line|#define LK_CMD_SOUND_CLK&t;0x9f&t;/* emit a keyclick */
DECL|macro|LK_CMD_DIS_BELL
mdefine_line|#define LK_CMD_DIS_BELL&t;&t;0xa1&t;/* disable the bell */
DECL|macro|LK_CMD_ENB_BELL
mdefine_line|#define LK_CMD_ENB_BELL&t;&t;0x23&t;/* enable the bell */
multiline_comment|/* 1st param: volume */
DECL|macro|LK_CMD_BELL
mdefine_line|#define LK_CMD_BELL&t;&t;0xa7&t;/* emit a bell */
DECL|macro|LK_CMD_TMP_NORPT
mdefine_line|#define LK_CMD_TMP_NORPT&t;0xd1&t;/* disable typematic */
multiline_comment|/* for the currently pressed key */
DECL|macro|LK_CMD_ENB_RPT
mdefine_line|#define LK_CMD_ENB_RPT&t;&t;0xe3&t;/* enable typematic */
multiline_comment|/* for RPT_DOWN groups */
DECL|macro|LK_CMD_DIS_RPT
mdefine_line|#define LK_CMD_DIS_RPT&t;&t;0xe1&t;/* disable typematic */
multiline_comment|/* for RPT_DOWN groups */
DECL|macro|LK_CMD_RPT_TO_DOWN
mdefine_line|#define LK_CMD_RPT_TO_DOWN&t;0xd9&t;/* set RPT_DOWN groups to DOWN */
DECL|macro|LK_CMD_REQ_ID
mdefine_line|#define LK_CMD_REQ_ID&t;&t;0xab&t;/* request the keyboard ID */
DECL|macro|LK_CMD_POWER_UP
mdefine_line|#define LK_CMD_POWER_UP&t;&t;0xfd&t;/* init power-up sequence */
DECL|macro|LK_CMD_TEST_MODE
mdefine_line|#define LK_CMD_TEST_MODE&t;0xcb&t;/* enter the factory test mode */
DECL|macro|LK_CMD_TEST_EXIT
mdefine_line|#define LK_CMD_TEST_EXIT&t;0x80&t;/* exit the factory test mode */
DECL|macro|LK_CMD_SET_DEFAULTS
mdefine_line|#define LK_CMD_SET_DEFAULTS&t;0xd3&t;/* set power-up defaults */
DECL|macro|LK_CMD_MODE
mdefine_line|#define LK_CMD_MODE(m,div)&t;(LK_PARAM|(((div)&amp;0xf)&lt;&lt;3)|(((m)&amp;0x3)&lt;&lt;1))
multiline_comment|/* select the repeat mode */
multiline_comment|/* for the selected key group */
DECL|macro|LK_CMD_MODE_AR
mdefine_line|#define LK_CMD_MODE_AR(m,div)&t;((((div)&amp;0xf)&lt;&lt;3)|(((m)&amp;0x3)&lt;&lt;1))
multiline_comment|/* select the repeat mode */
multiline_comment|/* and the repeat register */
multiline_comment|/* for the selected key group */
multiline_comment|/* 1st param: register number */
DECL|macro|LK_CMD_RPT_RATE
mdefine_line|#define LK_CMD_RPT_RATE(r)&t;(0x78|(((r)&amp;0x3)&lt;&lt;1))
multiline_comment|/* set the delay and repeat rate */
multiline_comment|/* for the selected repeat register */
multiline_comment|/* 1st param: initial delay */
multiline_comment|/* 2nd param: repeat rate */
multiline_comment|/* there are 4 leds, represent them in the low 4 bits of a byte */
DECL|macro|LK_PARAM_LED_MASK
mdefine_line|#define LK_PARAM_LED_MASK(ledbmap)&t;(LK_PARAM|((ledbmap)&amp;0xf))
DECL|macro|LK_LED_WAIT
mdefine_line|#define LK_LED_WAIT&t;&t;0x1&t;/* Wait LED */
DECL|macro|LK_LED_COMP
mdefine_line|#define LK_LED_COMP&t;&t;0x2&t;/* Compose LED */
DECL|macro|LK_LED_LOCK
mdefine_line|#define LK_LED_LOCK&t;&t;0x4&t;/* Lock LED */
DECL|macro|LK_LED_HOLD
mdefine_line|#define LK_LED_HOLD&t;&t;0x8&t;/* Hold Screen LED */
multiline_comment|/* max volume is 0, lowest is 0x7 */
DECL|macro|LK_PARAM_VOLUME
mdefine_line|#define LK_PARAM_VOLUME(v)&t;&t;(LK_PARAM|((v)&amp;0x7))
multiline_comment|/* mode set command details, div is a key group number */
DECL|macro|LK_MODE_DOWN
mdefine_line|#define LK_MODE_DOWN&t;&t;0x0&t;/* make only */
DECL|macro|LK_MODE_RPT_DOWN
mdefine_line|#define LK_MODE_RPT_DOWN&t;0x1&t;/* make and typematic */
DECL|macro|LK_MODE_DOWN_UP
mdefine_line|#define LK_MODE_DOWN_UP&t;&t;0x3&t;/* make and release */
multiline_comment|/* there are 4 repeat registers */
DECL|macro|LK_PARAM_AR
mdefine_line|#define LK_PARAM_AR(r)&t;&t;(LK_PARAM|((v)&amp;0x3))
multiline_comment|/*&n; * Mappings between key groups and keycodes are as follows:&n; *&n; *  1: 0xbf - 0xff -- alphanumeric,&n; *  2: 0x91 - 0xa5 -- numeric keypad,&n; *  3: 0xbc        -- Backspace,&n; *  4: 0xbd - 0xbe -- Tab, Return,&n; *  5: 0xb0 - 0xb2 -- Lock, Compose Character,&n; *  6: 0xad - 0xaf -- Ctrl, Shift,&n; *  7: 0xa6 - 0xa8 -- Left Arrow, Right Arrow,&n; *  8: 0xa9 - 0xac -- Up Arrow, Down Arrow, Right Shift,&n; *  9: 0x88 - 0x90 -- editor keypad,&n; * 10: 0x56 - 0x62 -- F1 - F5,&n; * 11: 0x63 - 0x6e -- F6 - F10,&n; * 12: 0x6f - 0x7a -- F11 - F14,&n; * 13: 0x7b - 0x7d -- Help, Do,&n; * 14: 0x7e - 0x87 -- F17 - F20.&n; *&n; * Notes:&n; * 1. Codes in the 0x00 - 0x40 range are reserved.&n; * 2. The assignment of the 0x41 - 0x55 range is undiscovered, probably 10.&n; */
multiline_comment|/* delay is 5 - 630 ms; 0x00 and 0x7f are reserved */
DECL|macro|LK_PARAM_DELAY
mdefine_line|#define LK_PARAM_DELAY(t)&t;((t)&amp;0x7f)
multiline_comment|/* rate is 12 - 127 Hz; 0x00 - 0x0b and 0x7d (power-up!) are reserved */
DECL|macro|LK_PARAM_RATE
mdefine_line|#define LK_PARAM_RATE(r)&t;(LK_PARAM|((r)&amp;0x7f))
DECL|macro|LK_SHIFT
mdefine_line|#define LK_SHIFT 1&lt;&lt;0
DECL|macro|LK_CTRL
mdefine_line|#define LK_CTRL 1&lt;&lt;1
DECL|macro|LK_LOCK
mdefine_line|#define LK_LOCK 1&lt;&lt;2
DECL|macro|LK_COMP
mdefine_line|#define LK_COMP 1&lt;&lt;3
DECL|macro|LK_KEY_SHIFT
mdefine_line|#define LK_KEY_SHIFT&t;&t;0xae
DECL|macro|LK_KEY_CTRL
mdefine_line|#define LK_KEY_CTRL&t;&t;0xaf
DECL|macro|LK_KEY_LOCK
mdefine_line|#define LK_KEY_LOCK&t;&t;0xb0
DECL|macro|LK_KEY_COMP
mdefine_line|#define LK_KEY_COMP&t;&t;0xb1
DECL|macro|LK_KEY_RELEASE
mdefine_line|#define LK_KEY_RELEASE&t;&t;0xb3&t;/* all keys released */
DECL|macro|LK_KEY_REPEAT
mdefine_line|#define LK_KEY_REPEAT&t;&t;0xb4&t;/* repeat the last key */
multiline_comment|/* status responses */
DECL|macro|LK_STAT_RESUME_ERR
mdefine_line|#define LK_STAT_RESUME_ERR&t;0xb5&t;/* keystrokes lost while inhibited */
DECL|macro|LK_STAT_ERROR
mdefine_line|#define LK_STAT_ERROR&t;&t;0xb6&t;/* an invalid command received */
DECL|macro|LK_STAT_INHIBIT_ACK
mdefine_line|#define LK_STAT_INHIBIT_ACK&t;0xb7&t;/* transmission inhibited */
DECL|macro|LK_STAT_TEST_ACK
mdefine_line|#define LK_STAT_TEST_ACK&t;0xb8&t;/* the factory test mode entered */
DECL|macro|LK_STAT_MODE_KEYDOWN
mdefine_line|#define LK_STAT_MODE_KEYDOWN&t;0xb9&t;/* a key is down on a change */
multiline_comment|/* to the DOWN_UP mode; */
multiline_comment|/* the keycode follows */
DECL|macro|LK_STAT_MODE_ACK
mdefine_line|#define LK_STAT_MODE_ACK&t;0xba&t;/* the mode command succeeded */
DECL|macro|LK_STAT_PWRUP_ID
mdefine_line|#define LK_STAT_PWRUP_ID&t;0x01&t;/* the power-up response start mark */
DECL|macro|LK_STAT_PWRUP_OK
mdefine_line|#define LK_STAT_PWRUP_OK&t;0x00&t;/* the power-up self test OK */
DECL|macro|LK_STAT_PWRUP_KDOWN
mdefine_line|#define LK_STAT_PWRUP_KDOWN&t;0x3d&t;/* a key was down during the test */
DECL|macro|LK_STAT_PWRUP_ERROR
mdefine_line|#define LK_STAT_PWRUP_ERROR&t;0x3e&t;/* keyboard self test failure */
r_extern
r_int
r_char
id|scancodeRemap
(braket
l_int|256
)braket
suffix:semicolon
eof
