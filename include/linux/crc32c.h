macro_line|#ifndef _LINUX_CRC32C_H
DECL|macro|_LINUX_CRC32C_H
mdefine_line|#define _LINUX_CRC32C_H
macro_line|#include &lt;linux/types.h&gt;
r_extern
id|u32
id|crc32c_le
c_func
(paren
id|u32
id|crc
comma
r_int
r_char
r_const
op_star
id|address
comma
r_int
id|length
)paren
suffix:semicolon
r_extern
id|u32
id|crc32c_be
c_func
(paren
id|u32
id|crc
comma
r_int
r_char
r_const
op_star
id|address
comma
r_int
id|length
)paren
suffix:semicolon
DECL|macro|crc32c
mdefine_line|#define crc32c(seed, data, length)  crc32c_le(seed, (unsigned char const *)data, length)
macro_line|#endif&t;/* _LINUX_CRC32C_H */
eof
