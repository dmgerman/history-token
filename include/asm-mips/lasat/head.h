multiline_comment|/*&n; * Image header stuff&n; */
macro_line|#ifndef _HEAD_H
DECL|macro|_HEAD_H
mdefine_line|#define _HEAD_H
DECL|macro|LASAT_K_MAGIC0_VAL
mdefine_line|#define LASAT_K_MAGIC0_VAL&t;0xfedeabba
DECL|macro|LASAT_K_MAGIC1_VAL
mdefine_line|#define LASAT_K_MAGIC1_VAL&t;0x00bedead
macro_line|#ifndef _LANGUAGE_ASSEMBLY
macro_line|#include &lt;linux/types.h&gt;
DECL|struct|bootloader_header
r_struct
id|bootloader_header
(brace
DECL|member|magic
id|u32
id|magic
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|version
id|u32
id|version
suffix:semicolon
DECL|member|image_start
id|u32
id|image_start
suffix:semicolon
DECL|member|image_size
id|u32
id|image_size
suffix:semicolon
DECL|member|kernel_start
id|u32
id|kernel_start
suffix:semicolon
DECL|member|kernel_entry
id|u32
id|kernel_entry
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
macro_line|#endif /* _HEAD_H */
eof
