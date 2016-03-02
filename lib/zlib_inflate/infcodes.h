multiline_comment|/* infcodes.h -- header to use infcodes.c&n; * Copyright (C) 1995-1998 Mark Adler&n; * For conditions of distribution and use, see copyright notice in zlib.h &n; */
multiline_comment|/* WARNING: this file should *not* be used by applications. It is&n;   part of the implementation of the compression library and is&n;   subject to change. Applications should only use zlib.h.&n; */
macro_line|#ifndef _INFCODES_H
DECL|macro|_INFCODES_H
mdefine_line|#define _INFCODES_H
macro_line|#include &quot;infblock.h&quot;
r_struct
id|inflate_codes_state
suffix:semicolon
DECL|typedef|inflate_codes_statef
r_typedef
r_struct
id|inflate_codes_state
id|inflate_codes_statef
suffix:semicolon
r_extern
id|inflate_codes_statef
op_star
id|zlib_inflate_codes_new
(paren
id|uInt
comma
id|uInt
comma
id|inflate_huft
op_star
comma
id|inflate_huft
op_star
comma
id|z_streamp
)paren
suffix:semicolon
r_extern
r_int
id|zlib_inflate_codes
(paren
id|inflate_blocks_statef
op_star
comma
id|z_streamp
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|zlib_inflate_codes_free
(paren
id|inflate_codes_statef
op_star
comma
id|z_streamp
)paren
suffix:semicolon
macro_line|#endif /* _INFCODES_H */
eof
