macro_line|#ifndef __LINUX_KBIO_H
DECL|macro|__LINUX_KBIO_H
mdefine_line|#define __LINUX_KBIO_H
multiline_comment|/* Return keyboard type */
DECL|macro|KIOCTYPE
mdefine_line|#define KIOCTYPE    _IOR(&squot;k&squot;, 9, int)
multiline_comment|/* Return Keyboard layout */
DECL|macro|KIOCLAYOUT
mdefine_line|#define KIOCLAYOUT  _IOR(&squot;k&squot;, 20, int)
r_enum
(brace
DECL|enumerator|TR_NONE
id|TR_NONE
comma
DECL|enumerator|TR_ASCII
id|TR_ASCII
comma
multiline_comment|/* keyboard is in regular state */
DECL|enumerator|TR_EVENT
id|TR_EVENT
comma
multiline_comment|/* keystrokes sent as firm events */
DECL|enumerator|TR_UNTRANS_EVENT
id|TR_UNTRANS_EVENT
multiline_comment|/* EVENT+up and down+no translation */
)brace
suffix:semicolon
multiline_comment|/* Return the current keyboard translation */
DECL|macro|KIOCGTRANS
mdefine_line|#define KIOCGTRANS  _IOR(&squot;k&squot;, 5, int)
multiline_comment|/* Set the keyboard translation */
DECL|macro|KIOCTRANS
mdefine_line|#define KIOCTRANS   _IOW(&squot;k&squot;, 0, int)
multiline_comment|/* Send a keyboard command */
DECL|macro|KIOCCMD
mdefine_line|#define KIOCCMD     _IOW(&squot;k&squot;, 8, int)
multiline_comment|/* Return if keystrokes are being sent to /dev/kbd */
multiline_comment|/* Set routing of keystrokes to /dev/kbd */
DECL|macro|KIOCSDIRECT
mdefine_line|#define KIOCSDIRECT _IOW(&squot;k&squot;, 10, int)
multiline_comment|/* Set keyboard leds */
DECL|macro|KIOCSLED
mdefine_line|#define KIOCSLED    _IOW(&squot;k&squot;, 14, unsigned char)
multiline_comment|/* Get keyboard leds */
DECL|macro|KIOCGLED
mdefine_line|#define KIOCGLED    _IOR(&squot;k&squot;, 15, unsigned char)
multiline_comment|/* Used by KIOC[GS]RATE */
DECL|struct|kbd_rate
r_struct
id|kbd_rate
(brace
DECL|member|delay
r_int
r_char
id|delay
suffix:semicolon
multiline_comment|/* Delay in Hz before first repeat.&t;*/
DECL|member|rate
r_int
r_char
id|rate
suffix:semicolon
multiline_comment|/* In characters per second (0..50).&t;*/
)brace
suffix:semicolon
multiline_comment|/* Set keyboard rate */
DECL|macro|KIOCSRATE
mdefine_line|#define KIOCSRATE   _IOW(&squot;k&squot;, 40, struct kbd_rate)
multiline_comment|/* Get keyboard rate */
DECL|macro|KIOCGRATE
mdefine_line|#define KIOCGRATE   _IOW(&squot;k&squot;, 41, struct kbd_rate)
multiline_comment|/* Top bit records if the key is up or down */
DECL|macro|KBD_UP
mdefine_line|#define KBD_UP      0x80
multiline_comment|/* Usable information */
DECL|macro|KBD_KEYMASK
mdefine_line|#define KBD_KEYMASK 0x7f
multiline_comment|/* All keys up */
DECL|macro|KBD_IDLE
mdefine_line|#define KBD_IDLE    0x75
macro_line|#endif /* __LINUX_KBIO_H */
eof
