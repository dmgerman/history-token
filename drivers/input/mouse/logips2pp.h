multiline_comment|/*&n; * Logitech PS/2++ mouse driver header&n; *&n; * Copyright (c) 2003 Vojtech Pavlik &lt;vojtech@suse.cz&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License version 2 as published by&n; * the Free Software Foundation.&n; */
macro_line|#ifndef _LOGIPS2PP_H
DECL|macro|_LOGIPS2PP_H
mdefine_line|#define _LOGIPS2PP_H
DECL|macro|PS2PP_4BTN
mdefine_line|#define PS2PP_4BTN&t;0x01
DECL|macro|PS2PP_WHEEL
mdefine_line|#define PS2PP_WHEEL&t;0x02
DECL|macro|PS2PP_MX
mdefine_line|#define PS2PP_MX&t;0x04
DECL|macro|PS2PP_MX310
mdefine_line|#define PS2PP_MX310&t;0x08
r_struct
id|psmouse
suffix:semicolon
r_void
id|ps2pp_process_packet
c_func
(paren
r_struct
id|psmouse
op_star
id|psmouse
)paren
suffix:semicolon
r_void
id|ps2pp_set_800dpi
c_func
(paren
r_struct
id|psmouse
op_star
id|psmouse
)paren
suffix:semicolon
r_int
id|ps2pp_detect
c_func
(paren
r_struct
id|psmouse
op_star
id|psmouse
)paren
suffix:semicolon
macro_line|#endif
eof
