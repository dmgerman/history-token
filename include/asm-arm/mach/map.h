multiline_comment|/*&n; *  linux/include/asm-arm/map.h&n; *&n; *  Copyright (C) 1999-2000 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Page table mapping constructs and function prototypes&n; */
DECL|struct|map_desc
r_struct
id|map_desc
(brace
DECL|member|virtual
r_int
r_int
r_virtual
suffix:semicolon
DECL|member|physical
r_int
r_int
id|physical
suffix:semicolon
DECL|member|length
r_int
r_int
id|length
suffix:semicolon
DECL|member|type
r_int
r_int
id|type
suffix:semicolon
)brace
suffix:semicolon
r_struct
id|meminfo
suffix:semicolon
DECL|macro|MT_DEVICE
mdefine_line|#define MT_DEVICE&t;&t;0
DECL|macro|MT_CACHECLEAN
mdefine_line|#define MT_CACHECLEAN&t;&t;1
DECL|macro|MT_MINICLEAN
mdefine_line|#define MT_MINICLEAN&t;&t;2
DECL|macro|MT_LOW_VECTORS
mdefine_line|#define MT_LOW_VECTORS&t;&t;3
DECL|macro|MT_HIGH_VECTORS
mdefine_line|#define MT_HIGH_VECTORS&t;&t;4
DECL|macro|MT_MEMORY
mdefine_line|#define MT_MEMORY&t;&t;5
DECL|macro|MT_ROM
mdefine_line|#define MT_ROM&t;&t;&t;6
DECL|macro|MT_IXP2000_DEVICE
mdefine_line|#define MT_IXP2000_DEVICE&t;7
r_extern
r_void
id|create_memmap_holes
c_func
(paren
r_struct
id|meminfo
op_star
)paren
suffix:semicolon
r_extern
r_void
id|memtable_init
c_func
(paren
r_struct
id|meminfo
op_star
)paren
suffix:semicolon
r_extern
r_void
id|iotable_init
c_func
(paren
r_struct
id|map_desc
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|setup_io_desc
c_func
(paren
r_void
)paren
suffix:semicolon
eof
