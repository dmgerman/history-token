macro_line|#ifndef _LINUX_NVRAM_H
DECL|macro|_LINUX_NVRAM_H
mdefine_line|#define _LINUX_NVRAM_H
macro_line|#include &lt;linux/ioctl.h&gt;
multiline_comment|/* /dev/nvram ioctls */
DECL|macro|NVRAM_INIT
mdefine_line|#define NVRAM_INIT&t;_IO(&squot;p&squot;, 0x40) /* initialize NVRAM and set checksum */
DECL|macro|NVRAM_SETCKS
mdefine_line|#define NVRAM_SETCKS&t;_IO(&squot;p&squot;, 0x41) /* recalculate checksum */
multiline_comment|/* for all current systems, this is where NVRAM starts */
DECL|macro|NVRAM_FIRST_BYTE
mdefine_line|#define NVRAM_FIRST_BYTE    14
multiline_comment|/* all these functions expect an NVRAM offset, not an absolute */
DECL|macro|NVRAM_OFFSET
mdefine_line|#define NVRAM_OFFSET(x)   ((x)-NVRAM_FIRST_BYTE)
macro_line|#ifdef __KERNEL__
multiline_comment|/* __foo is foo without grabbing the rtc_lock - get it yourself */
r_extern
r_int
r_char
id|__nvram_read_byte
c_func
(paren
r_int
id|i
)paren
suffix:semicolon
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
id|__nvram_write_byte
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
id|__nvram_check_checksum
c_func
(paren
r_void
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
id|__nvram_set_checksum
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
