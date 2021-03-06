macro_line|#ifndef _LINUX_FIRMWARE_H
DECL|macro|_LINUX_FIRMWARE_H
mdefine_line|#define _LINUX_FIRMWARE_H
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
DECL|macro|FIRMWARE_NAME_MAX
mdefine_line|#define FIRMWARE_NAME_MAX 30 
DECL|struct|firmware
r_struct
id|firmware
(brace
DECL|member|size
r_int
id|size
suffix:semicolon
DECL|member|data
id|u8
op_star
id|data
suffix:semicolon
)brace
suffix:semicolon
r_struct
id|device
suffix:semicolon
r_int
id|request_firmware
c_func
(paren
r_const
r_struct
id|firmware
op_star
op_star
id|fw
comma
r_const
r_char
op_star
id|name
comma
r_struct
id|device
op_star
id|device
)paren
suffix:semicolon
r_int
id|request_firmware_nowait
c_func
(paren
r_struct
id|module
op_star
id|module
comma
r_const
r_char
op_star
id|name
comma
r_struct
id|device
op_star
id|device
comma
r_void
op_star
id|context
comma
r_void
(paren
op_star
id|cont
)paren
(paren
r_const
r_struct
id|firmware
op_star
id|fw
comma
r_void
op_star
id|context
)paren
)paren
suffix:semicolon
r_void
id|release_firmware
c_func
(paren
r_const
r_struct
id|firmware
op_star
id|fw
)paren
suffix:semicolon
r_void
id|register_firmware
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_const
id|u8
op_star
id|data
comma
r_int
id|size
)paren
suffix:semicolon
macro_line|#endif
eof
