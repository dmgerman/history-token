multiline_comment|/* inffast.h -- header to use inffast.c&n; * Copyright (C) 1995-1998 Mark Adler&n; * For conditions of distribution and use, see copyright notice in zlib.h &n; */
multiline_comment|/* WARNING: this file should *not* be used by applications. It is&n;   part of the implementation of the compression library and is&n;   subject to change. Applications should only use zlib.h.&n; */
r_extern
r_int
id|cramfs_inflate_fast
id|OF
c_func
(paren
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
id|inflate_blocks_statef
op_star
comma
id|z_streamp
)paren
)paren
suffix:semicolon
eof
