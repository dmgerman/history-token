macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* This handles the memory map.. */
macro_line|#ifndef CONFIG_SUN3
DECL|macro|PAGE_OFFSET_RAW
mdefine_line|#define PAGE_OFFSET_RAW&t;&t;0x00000000
macro_line|#else
DECL|macro|PAGE_OFFSET_RAW
mdefine_line|#define PAGE_OFFSET_RAW&t;&t;0x0E000000 
macro_line|#endif
eof
