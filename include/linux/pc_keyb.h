multiline_comment|/*&n; *&t;include/linux/pc_keyb.h&n; *&n; *&t;PC Keyboard And Keyboard Controller&n; *&n; *&t;(c) 1997 Martin Mares &lt;mj@atrey.karlin.mff.cuni.cz&gt;&n; */
multiline_comment|/*&n; *&t;Configuration Switches&n; */
DECL|macro|KBD_REPORT_ERR
macro_line|#undef KBD_REPORT_ERR&t;&t;&t;/* Report keyboard errors */
DECL|macro|KBD_REPORT_UNKN
mdefine_line|#define KBD_REPORT_UNKN&t;&t;&t;/* Report unknown scan codes */
DECL|macro|KBD_REPORT_TIMEOUTS
mdefine_line|#define KBD_REPORT_TIMEOUTS&t;&t;/* Report keyboard timeouts */
DECL|macro|KBD_IS_FOCUS_9000
macro_line|#undef KBD_IS_FOCUS_9000&t;&t;/* We have the brain-damaged FOCUS-9000 keyboard */
DECL|macro|INITIALIZE_MOUSE
macro_line|#undef INITIALIZE_MOUSE&t;&t;&t;/* Define if your PS/2 mouse needs initialization. */
DECL|macro|KBD_INIT_TIMEOUT
mdefine_line|#define KBD_INIT_TIMEOUT 1000&t;&t;/* Timeout in ms for initializing the keyboard */
DECL|macro|KBC_TIMEOUT
mdefine_line|#define KBC_TIMEOUT 250&t;&t;&t;/* Timeout in ms for sending to keyboard controller */
DECL|macro|KBD_TIMEOUT
mdefine_line|#define KBD_TIMEOUT 1000&t;&t;/* Timeout in ms for keyboard command acknowledge */
multiline_comment|/*&n; *&t;Internal variables of the driver&n; */
r_extern
r_int
r_char
id|pckbd_read_mask
suffix:semicolon
r_extern
r_int
r_char
id|aux_device_present
suffix:semicolon
multiline_comment|/*&n; *&t;Keyboard Controller Registers on normal PCs.&n; */
DECL|macro|KBD_STATUS_REG
mdefine_line|#define KBD_STATUS_REG&t;&t;0x64&t;/* Status register (R) */
DECL|macro|KBD_CNTL_REG
mdefine_line|#define KBD_CNTL_REG&t;&t;0x64&t;/* Controller command register (W) */
DECL|macro|KBD_DATA_REG
mdefine_line|#define KBD_DATA_REG&t;&t;0x60&t;/* Keyboard data register (R/W) */
multiline_comment|/*&n; *&t;Keyboard Controller Commands&n; */
DECL|macro|KBD_CCMD_READ_MODE
mdefine_line|#define KBD_CCMD_READ_MODE&t;0x20&t;/* Read mode bits */
DECL|macro|KBD_CCMD_WRITE_MODE
mdefine_line|#define KBD_CCMD_WRITE_MODE&t;0x60&t;/* Write mode bits */
DECL|macro|KBD_CCMD_GET_VERSION
mdefine_line|#define KBD_CCMD_GET_VERSION&t;0xA1&t;/* Get controller version */
DECL|macro|KBD_CCMD_MOUSE_DISABLE
mdefine_line|#define KBD_CCMD_MOUSE_DISABLE&t;0xA7&t;/* Disable mouse interface */
DECL|macro|KBD_CCMD_MOUSE_ENABLE
mdefine_line|#define KBD_CCMD_MOUSE_ENABLE&t;0xA8&t;/* Enable mouse interface */
DECL|macro|KBD_CCMD_TEST_MOUSE
mdefine_line|#define KBD_CCMD_TEST_MOUSE&t;0xA9&t;/* Mouse interface test */
DECL|macro|KBD_CCMD_SELF_TEST
mdefine_line|#define KBD_CCMD_SELF_TEST&t;0xAA&t;/* Controller self test */
DECL|macro|KBD_CCMD_KBD_TEST
mdefine_line|#define KBD_CCMD_KBD_TEST&t;0xAB&t;/* Keyboard interface test */
DECL|macro|KBD_CCMD_KBD_DISABLE
mdefine_line|#define KBD_CCMD_KBD_DISABLE&t;0xAD&t;/* Keyboard interface disable */
DECL|macro|KBD_CCMD_KBD_ENABLE
mdefine_line|#define KBD_CCMD_KBD_ENABLE&t;0xAE&t;/* Keyboard interface enable */
DECL|macro|KBD_CCMD_WRITE_AUX_OBUF
mdefine_line|#define KBD_CCMD_WRITE_AUX_OBUF&t;0xD3    /* Write to output buffer as if&n;&t;&t;&t;&t;&t;   initiated by the auxiliary device */
DECL|macro|KBD_CCMD_WRITE_MOUSE
mdefine_line|#define KBD_CCMD_WRITE_MOUSE&t;0xD4&t;/* Write the following byte to the mouse */
multiline_comment|/*&n; *&t;Keyboard Commands&n; */
DECL|macro|KBD_CMD_SET_LEDS
mdefine_line|#define KBD_CMD_SET_LEDS&t;0xED&t;/* Set keyboard leds */
DECL|macro|KBD_CMD_SET_RATE
mdefine_line|#define KBD_CMD_SET_RATE&t;0xF3&t;/* Set typematic rate */
DECL|macro|KBD_CMD_ENABLE
mdefine_line|#define KBD_CMD_ENABLE&t;&t;0xF4&t;/* Enable scanning */
DECL|macro|KBD_CMD_DISABLE
mdefine_line|#define KBD_CMD_DISABLE&t;&t;0xF5&t;/* Disable scanning */
DECL|macro|KBD_CMD_RESET
mdefine_line|#define KBD_CMD_RESET&t;&t;0xFF&t;/* Reset */
multiline_comment|/*&n; *&t;Keyboard Replies&n; */
DECL|macro|KBD_REPLY_POR
mdefine_line|#define KBD_REPLY_POR&t;&t;0xAA&t;/* Power on reset */
DECL|macro|KBD_REPLY_ACK
mdefine_line|#define KBD_REPLY_ACK&t;&t;0xFA&t;/* Command ACK */
DECL|macro|KBD_REPLY_RESEND
mdefine_line|#define KBD_REPLY_RESEND&t;0xFE&t;/* Command NACK, send the cmd again */
multiline_comment|/*&n; *&t;Status Register Bits&n; */
DECL|macro|KBD_STAT_OBF
mdefine_line|#define KBD_STAT_OBF &t;&t;0x01&t;/* Keyboard output buffer full */
DECL|macro|KBD_STAT_IBF
mdefine_line|#define KBD_STAT_IBF &t;&t;0x02&t;/* Keyboard input buffer full */
DECL|macro|KBD_STAT_SELFTEST
mdefine_line|#define KBD_STAT_SELFTEST&t;0x04&t;/* Self test successful */
DECL|macro|KBD_STAT_CMD
mdefine_line|#define KBD_STAT_CMD&t;&t;0x08&t;/* Last write was a command write (0=data) */
DECL|macro|KBD_STAT_UNLOCKED
mdefine_line|#define KBD_STAT_UNLOCKED&t;0x10&t;/* Zero if keyboard locked */
DECL|macro|KBD_STAT_MOUSE_OBF
mdefine_line|#define KBD_STAT_MOUSE_OBF&t;0x20&t;/* Mouse output buffer full */
DECL|macro|KBD_STAT_GTO
mdefine_line|#define KBD_STAT_GTO &t;&t;0x40&t;/* General receive/xmit timeout */
DECL|macro|KBD_STAT_PERR
mdefine_line|#define KBD_STAT_PERR &t;&t;0x80&t;/* Parity error */
DECL|macro|AUX_STAT_OBF
mdefine_line|#define AUX_STAT_OBF (KBD_STAT_OBF | KBD_STAT_MOUSE_OBF)
multiline_comment|/*&n; *&t;Controller Mode Register Bits&n; */
DECL|macro|KBD_MODE_KBD_INT
mdefine_line|#define KBD_MODE_KBD_INT&t;0x01&t;/* Keyboard data generate IRQ1 */
DECL|macro|KBD_MODE_MOUSE_INT
mdefine_line|#define KBD_MODE_MOUSE_INT&t;0x02&t;/* Mouse data generate IRQ12 */
DECL|macro|KBD_MODE_SYS
mdefine_line|#define KBD_MODE_SYS &t;&t;0x04&t;/* The system flag (?) */
DECL|macro|KBD_MODE_NO_KEYLOCK
mdefine_line|#define KBD_MODE_NO_KEYLOCK&t;0x08&t;/* The keylock doesn&squot;t affect the keyboard if set */
DECL|macro|KBD_MODE_DISABLE_KBD
mdefine_line|#define KBD_MODE_DISABLE_KBD&t;0x10&t;/* Disable keyboard interface */
DECL|macro|KBD_MODE_DISABLE_MOUSE
mdefine_line|#define KBD_MODE_DISABLE_MOUSE&t;0x20&t;/* Disable mouse interface */
DECL|macro|KBD_MODE_KCC
mdefine_line|#define KBD_MODE_KCC &t;&t;0x40&t;/* Scan code conversion to PC format */
DECL|macro|KBD_MODE_RFU
mdefine_line|#define KBD_MODE_RFU&t;&t;0x80
multiline_comment|/*&n; *&t;Mouse Commands&n; */
DECL|macro|AUX_SET_RES
mdefine_line|#define AUX_SET_RES&t;&t;0xE8&t;/* Set resolution */
DECL|macro|AUX_SET_SCALE11
mdefine_line|#define AUX_SET_SCALE11&t;&t;0xE6&t;/* Set 1:1 scaling */
DECL|macro|AUX_SET_SCALE21
mdefine_line|#define AUX_SET_SCALE21&t;&t;0xE7&t;/* Set 2:1 scaling */
DECL|macro|AUX_GET_SCALE
mdefine_line|#define AUX_GET_SCALE&t;&t;0xE9&t;/* Get scaling factor */
DECL|macro|AUX_SET_STREAM
mdefine_line|#define AUX_SET_STREAM&t;&t;0xEA&t;/* Set stream mode */
DECL|macro|AUX_SET_SAMPLE
mdefine_line|#define AUX_SET_SAMPLE&t;&t;0xF3&t;/* Set sample rate */
DECL|macro|AUX_ENABLE_DEV
mdefine_line|#define AUX_ENABLE_DEV&t;&t;0xF4&t;/* Enable aux device */
DECL|macro|AUX_DISABLE_DEV
mdefine_line|#define AUX_DISABLE_DEV&t;&t;0xF5&t;/* Disable aux device */
DECL|macro|AUX_RESET
mdefine_line|#define AUX_RESET&t;&t;0xFF&t;/* Reset aux device */
DECL|macro|AUX_ACK
mdefine_line|#define AUX_ACK&t;&t;&t;0xFA&t;/* Command byte ACK. */
DECL|macro|AUX_BUF_SIZE
mdefine_line|#define AUX_BUF_SIZE&t;&t;2048&t;/* This might be better divisible by&n;&t;&t;&t;&t;&t;   three to make overruns stay in sync&n;&t;&t;&t;&t;&t;   but then the read function would need&n;&t;&t;&t;&t;&t;   a lock etc - ick */
DECL|struct|aux_queue
r_struct
id|aux_queue
(brace
DECL|member|head
r_int
r_int
id|head
suffix:semicolon
DECL|member|tail
r_int
r_int
id|tail
suffix:semicolon
DECL|member|proc_list
id|wait_queue_head_t
id|proc_list
suffix:semicolon
DECL|member|fasync
r_struct
id|fasync_struct
op_star
id|fasync
suffix:semicolon
DECL|member|buf
r_int
r_char
id|buf
(braket
id|AUX_BUF_SIZE
)braket
suffix:semicolon
)brace
suffix:semicolon
eof
