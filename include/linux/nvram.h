macro_line|#ifndef _LINUX_NVRAM_H
DECL|macro|_LINUX_NVRAM_H
mdefine_line|#define _LINUX_NVRAM_H
macro_line|#include &lt;linux/ioctl.h&gt;
multiline_comment|/* /dev/nvram ioctls */
DECL|macro|NVRAM_INIT
mdefine_line|#define NVRAM_INIT&t;&t;_IO(&squot;p&squot;, 0x40) /* initialize NVRAM and set checksum */
DECL|macro|NVRAM_SETCKS
mdefine_line|#define&t;NVRAM_SETCKS&t;_IO(&squot;p&squot;, 0x41) /* recalculate checksum */
macro_line|#ifdef __KERNEL__
r_extern
r_int
r_char
id|nvram_read_byte
c_func
(paren
r_int
id|i
)paren
suffix:semicolon
r_extern
r_void
id|nvram_write_byte
c_func
(paren
r_int
r_char
id|c
comma
r_int
id|i
)paren
suffix:semicolon
r_extern
r_int
id|nvram_check_checksum
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|nvram_set_checksum
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif  /* _LINUX_NVRAM_H */
eof
