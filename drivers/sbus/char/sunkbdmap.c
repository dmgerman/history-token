multiline_comment|/* $Id: sunkbdmap.c,v 1.1 1997/09/07 15:40:27 ecd Exp $&n; * sunkbdmap.c: Wrapper around sunkeymap.c to change table names.&n; *&n; * Copyright (C) 1997  Eddie C. Dost  (ecd@skynet.be)&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_PCI
DECL|macro|func_buf
mdefine_line|#define func_buf&t;&t;&t;sun_func_buf
DECL|macro|func_table
mdefine_line|#define func_table&t;&t;&t;sun_func_table
DECL|macro|funcbufsize
mdefine_line|#define funcbufsize&t;&t;&t;sun_funcbufsize
DECL|macro|funcbufleft
mdefine_line|#define funcbufleft&t;&t;&t;sun_funcbufleft
DECL|macro|funcbufptr
mdefine_line|#define funcbufptr&t;&t;&t;sun_funcbufptr
DECL|macro|accent_table
mdefine_line|#define accent_table&t;&t;&t;sun_accent_table
DECL|macro|accent_table_size
mdefine_line|#define accent_table_size&t;&t;sun_accent_table_size
DECL|macro|key_maps
mdefine_line|#define key_maps&t;&t;&t;sun_key_maps
DECL|macro|keymap_count
mdefine_line|#define keymap_count&t;&t;&t;sun_keymap_count
DECL|macro|plain_map
mdefine_line|#define plain_map&t;&t;&t;sun_plain_map
DECL|macro|shift_map
mdefine_line|#define shift_map&t;&t;&t;sun_shift_map
DECL|macro|ctrl_map
mdefine_line|#define ctrl_map&t;&t;&t;sun_ctrl_map
DECL|macro|alt_map
mdefine_line|#define alt_map&t;&t;&t;&t;sun_alt_map
DECL|macro|altgr_map
mdefine_line|#define altgr_map&t;&t;&t;sun_altgr_map
DECL|macro|shift_ctrl_map
mdefine_line|#define shift_ctrl_map&t;&t;&t;sun_shift_ctrl_map
DECL|macro|ctrl_alt_map
mdefine_line|#define ctrl_alt_map&t;&t;&t;sun_ctrl_alt_map
macro_line|#endif /* CONFIG_PCI */
macro_line|#include &quot;sunkeymap.c&quot;
eof
