multiline_comment|/* ----------------------------------------------------------------------- *&n; *   &n; *   Copyright 2001 H. Peter Anvin - All Rights Reserved&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation, Inc., 675 Mass Ave, Cambridge MA 02139,&n; *   USA; either version 2 of the License, or (at your option) any later&n; *   version; incorporated herein by reference.&n; *&n; * ----------------------------------------------------------------------- */
multiline_comment|/*&n; * Prototypes for functions exported from the compressed isofs subsystem&n; */
macro_line|#ifdef CONFIG_ZISOFS
r_extern
r_struct
id|address_space_operations
id|zisofs_aops
suffix:semicolon
r_extern
r_int
id|__init
id|zisofs_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__exit
id|zisofs_cleanup
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
eof
