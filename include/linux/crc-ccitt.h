macro_line|#ifndef _LINUX_CRC_CCITT_H
DECL|macro|_LINUX_CRC_CCITT_H
mdefine_line|#define _LINUX_CRC_CCITT_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/types.h&gt;
r_extern
id|u16
r_const
id|crc_ccitt_table
(braket
l_int|256
)braket
suffix:semicolon
r_extern
id|u16
id|crc_ccitt
c_func
(paren
id|u16
id|crc
comma
r_const
id|u8
op_star
id|buffer
comma
r_int
id|len
)paren
suffix:semicolon
DECL|function|crc_ccitt_byte
r_static
r_inline
id|u16
id|crc_ccitt_byte
c_func
(paren
id|u16
id|crc
comma
r_const
id|u8
id|c
)paren
(brace
r_return
(paren
id|crc
op_rshift
l_int|8
)paren
op_xor
id|crc_ccitt_table
(braket
(paren
id|crc
op_xor
id|c
)paren
op_amp
l_int|0xff
)braket
suffix:semicolon
)brace
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _LINUX_CRC_CCITT_H */
eof
