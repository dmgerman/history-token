multiline_comment|/*&n; * ALPS touchpad PS/2 mouse driver&n; *&n; * Copyright (c) 2003 Peter Osterlund &lt;petero2@telia.com&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License version 2 as published by&n; * the Free Software Foundation.&n; */
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
macro_line|#endif
eof
