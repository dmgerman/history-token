multiline_comment|/* infblock.h -- header to use infblock.c&n; * Copyright (C) 1995-1998 Mark Adler&n; * For conditions of distribution and use, see copyright notice in zlib.h &n; */
multiline_comment|/* WARNING: this file should *not* be used by applications. It is&n;   part of the implementation of the compression library and is&n;   subject to change. Applications should only use zlib.h.&n; */
macro_line|#ifndef _INFBLOCK_H
DECL|macro|_INFBLOCK_H
mdefine_line|#define _INFBLOCK_H
r_struct
id|inflate_blocks_state
suffix:semicolon
DECL|typedef|inflate_blocks_statef
r_typedef
r_struct
id|inflate_blocks_state
id|inflate_blocks_statef
suffix:semicolon
r_extern
id|inflate_blocks_statef
op_star
id|zlib_inflate_blocks_new
(paren
id|z_streamp
id|z
comma
id|check_func
id|c
comma
multiline_comment|/* check function */
id|uInt
id|w
)paren
suffix:semicolon
multiline_comment|/* window size */
r_extern
r_int
id|zlib_inflate_blocks
(paren
id|inflate_blocks_statef
op_star
comma
id|z_streamp
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* initial return code */
r_extern
r_void
id|zlib_inflate_blocks_reset
(paren
id|inflate_blocks_statef
op_star
comma
id|z_streamp
comma
id|uLong
op_star
)paren
suffix:semicolon
multiline_comment|/* check value on output */
r_extern
r_int
id|zlib_inflate_blocks_free
(paren
id|inflate_blocks_statef
op_star
comma
id|z_streamp
)paren
suffix:semicolon
r_extern
r_void
id|zlib_inflate_set_dictionary
(paren
id|inflate_blocks_statef
op_star
id|s
comma
r_const
id|Byte
op_star
id|d
comma
multiline_comment|/* dictionary */
id|uInt
id|n
)paren
suffix:semicolon
multiline_comment|/* dictionary length */
r_extern
r_int
id|zlib_inflate_blocks_sync_point
(paren
id|inflate_blocks_statef
op_star
id|s
)paren
suffix:semicolon
macro_line|#endif /* _INFBLOCK_H */
eof
