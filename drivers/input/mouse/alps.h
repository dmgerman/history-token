multiline_comment|/*&n; * ALPS touchpad PS/2 mouse driver&n; *&n; * Copyright (c) 2003 Peter Osterlund &lt;petero2@telia.com&gt;&n; * Copyright (c) 2005 Vojtech Pavlik &lt;vojtech@suse.cz&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License version 2 as published by&n; * the Free Software Foundation.&n; */
macro_line|#ifndef _ALPS_H
DECL|macro|_ALPS_H
mdefine_line|#define _ALPS_H
r_int
id|alps_detect
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
r_int
id|alps_init
c_func
(paren
r_struct
id|psmouse
op_star
id|psmouse
)paren
suffix:semicolon
DECL|struct|alps_model_info
r_struct
id|alps_model_info
(brace
DECL|member|signature
r_int
r_char
id|signature
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|byte0
DECL|member|mask0
r_int
r_char
id|byte0
comma
id|mask0
suffix:semicolon
DECL|member|flags
r_int
r_char
id|flags
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|alps_data
r_struct
id|alps_data
(brace
DECL|member|dev2
r_struct
id|input_dev
id|dev2
suffix:semicolon
multiline_comment|/* Relative device */
DECL|member|name
r_char
id|name
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* Name */
DECL|member|phys
r_char
id|phys
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* Phys */
DECL|member|i
r_struct
id|alps_model_info
op_star
id|i
suffix:semicolon
multiline_comment|/* Info */
DECL|member|prev_fin
r_int
id|prev_fin
suffix:semicolon
multiline_comment|/* Finger bit from previous packet */
)brace
suffix:semicolon
macro_line|#endif
eof
