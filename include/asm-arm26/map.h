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
