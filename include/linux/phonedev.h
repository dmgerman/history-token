macro_line|#ifndef __LINUX_PHONEDEV_H
DECL|macro|__LINUX_PHONEDEV_H
mdefine_line|#define __LINUX_PHONEDEV_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/poll.h&gt;
DECL|struct|phone_device
r_struct
id|phone_device
(brace
DECL|member|next
r_struct
id|phone_device
op_star
id|next
suffix:semicolon
DECL|member|f_op
r_struct
id|file_operations
op_star
id|f_op
suffix:semicolon
DECL|member|open
r_int
(paren
op_star
id|open
)paren
(paren
r_struct
id|phone_device
op_star
comma
r_struct
id|file
op_star
)paren
suffix:semicolon
DECL|member|board
r_int
id|board
suffix:semicolon
multiline_comment|/* Device private index */
DECL|member|minor
r_int
id|minor
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|phonedev_init
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|PHONE_MAJOR
mdefine_line|#define PHONE_MAJOR&t;100
r_extern
r_int
id|phone_register_device
c_func
(paren
r_struct
id|phone_device
op_star
comma
r_int
id|unit
)paren
suffix:semicolon
DECL|macro|PHONE_UNIT_ANY
mdefine_line|#define PHONE_UNIT_ANY&t;-1
r_extern
r_void
id|phone_unregister_device
c_func
(paren
r_struct
id|phone_device
op_star
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
