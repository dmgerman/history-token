multiline_comment|/*&n; * bulkmem.h -- Definitions for bulk memory services&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * The initial developer of the original code is David A. Hinds&n; * &lt;dahinds@users.sourceforge.net&gt;.  Portions created by David A. Hinds&n; * are Copyright (C) 1999 David A. Hinds.  All Rights Reserved.&n; *&n; * (C) 1999&t;&t;David A. Hinds&n; */
macro_line|#ifndef _LINUX_BULKMEM_H
DECL|macro|_LINUX_BULKMEM_H
mdefine_line|#define _LINUX_BULKMEM_H
multiline_comment|/* For GetFirstRegion and GetNextRegion */
DECL|struct|region_info_t
r_typedef
r_struct
id|region_info_t
(brace
DECL|member|Attributes
id|u_int
id|Attributes
suffix:semicolon
DECL|member|CardOffset
id|u_int
id|CardOffset
suffix:semicolon
DECL|member|RegionSize
id|u_int
id|RegionSize
suffix:semicolon
DECL|member|AccessSpeed
id|u_int
id|AccessSpeed
suffix:semicolon
DECL|member|BlockSize
id|u_int
id|BlockSize
suffix:semicolon
DECL|member|PartMultiple
id|u_int
id|PartMultiple
suffix:semicolon
DECL|member|JedecMfr
DECL|member|JedecInfo
id|u_char
id|JedecMfr
comma
id|JedecInfo
suffix:semicolon
DECL|member|next
id|memory_handle_t
id|next
suffix:semicolon
DECL|typedef|region_info_t
)brace
id|region_info_t
suffix:semicolon
DECL|macro|REGION_TYPE
mdefine_line|#define REGION_TYPE&t;&t;0x0001
DECL|macro|REGION_TYPE_CM
mdefine_line|#define REGION_TYPE_CM&t;&t;0x0000
DECL|macro|REGION_TYPE_AM
mdefine_line|#define REGION_TYPE_AM&t;&t;0x0001
DECL|macro|REGION_PREFETCH
mdefine_line|#define REGION_PREFETCH&t;&t;0x0008
DECL|macro|REGION_CACHEABLE
mdefine_line|#define REGION_CACHEABLE&t;0x0010
DECL|macro|REGION_BAR_MASK
mdefine_line|#define REGION_BAR_MASK&t;&t;0xe000
DECL|macro|REGION_BAR_SHIFT
mdefine_line|#define REGION_BAR_SHIFT&t;13
r_int
id|pcmcia_get_first_region
c_func
(paren
id|client_handle_t
id|handle
comma
id|region_info_t
op_star
id|rgn
)paren
suffix:semicolon
r_int
id|pcmcia_get_next_region
c_func
(paren
id|client_handle_t
id|handle
comma
id|region_info_t
op_star
id|rgn
)paren
suffix:semicolon
macro_line|#endif /* _LINUX_BULKMEM_H */
eof
