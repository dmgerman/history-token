multiline_comment|/*&n; * crc32.h&n; * See linux/lib/crc32.c for license and changes&n; */
macro_line|#ifndef _LINUX_CRC32_H
DECL|macro|_LINUX_CRC32_H
mdefine_line|#define _LINUX_CRC32_H
macro_line|#include &lt;linux/types.h&gt;
r_extern
id|u32
id|crc32_le
c_func
(paren
id|u32
id|crc
comma
r_int
r_char
r_const
op_star
id|p
comma
r_int
id|len
)paren
suffix:semicolon
r_extern
id|u32
id|crc32_be
c_func
(paren
id|u32
id|crc
comma
r_int
r_char
r_const
op_star
id|p
comma
r_int
id|len
)paren
suffix:semicolon
DECL|macro|crc32
mdefine_line|#define crc32(seed, data, length)  crc32_le(seed, (unsigned char const *)data, length)
DECL|macro|ether_crc_le
mdefine_line|#define ether_crc_le(length, data) crc32_le(~0, data, length)
DECL|macro|ether_crc
mdefine_line|#define ether_crc(length, data)    crc32_be(~0, data, length)
macro_line|#endif /* _LINUX_CRC32_H */
eof
