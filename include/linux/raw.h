macro_line|#ifndef __LINUX_RAW_H
DECL|macro|__LINUX_RAW_H
mdefine_line|#define __LINUX_RAW_H
macro_line|#include &lt;linux/types.h&gt;
DECL|macro|RAW_SETBIND
mdefine_line|#define RAW_SETBIND&t;_IO( 0xac, 0 )
DECL|macro|RAW_GETBIND
mdefine_line|#define RAW_GETBIND&t;_IO( 0xac, 1 )
DECL|struct|raw_config_request
r_struct
id|raw_config_request
(brace
DECL|member|raw_minor
r_int
id|raw_minor
suffix:semicolon
DECL|member|block_major
id|__u64
id|block_major
suffix:semicolon
DECL|member|block_minor
id|__u64
id|block_minor
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* __LINUX_RAW_H */
eof
