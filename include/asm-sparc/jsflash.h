multiline_comment|/*&n; * jsflash.h: OS Flash SIMM support for JavaStations.&n; *&n; * Copyright (C) 1999  Pete Zaitcev&n; */
macro_line|#ifndef _SPARC_JSFLASH_H
DECL|macro|_SPARC_JSFLASH_H
mdefine_line|#define _SPARC_JSFLASH_H
macro_line|#ifndef _SPARC_TYPES_H
macro_line|#include &lt;asm/types.h&gt;
macro_line|#endif
multiline_comment|/*&n; * Semantics of the offset is a full address.&n; * Hardcode it or get it from probe ioctl.&n; *&n; * We use full bus address, so that we would be&n; * automatically compatible with possible future systems.&n; */
DECL|macro|JSFLASH_IDENT
mdefine_line|#define JSFLASH_IDENT   ((&squot;F&squot;&lt;&lt;8)|54)
DECL|struct|jsflash_ident_arg
r_struct
id|jsflash_ident_arg
(brace
DECL|member|off
id|__u64
id|off
suffix:semicolon
multiline_comment|/* 0x20000000 is included */
DECL|member|size
id|__u32
id|size
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* With trailing zero */
)brace
suffix:semicolon
DECL|macro|JSFLASH_ERASE
mdefine_line|#define JSFLASH_ERASE   ((&squot;F&squot;&lt;&lt;8)|55)
multiline_comment|/* Put 0 as argument, may be flags or sector number... */
DECL|macro|JSFLASH_PROGRAM
mdefine_line|#define JSFLASH_PROGRAM ((&squot;F&squot;&lt;&lt;8)|56)
DECL|struct|jsflash_program_arg
r_struct
id|jsflash_program_arg
(brace
DECL|member|data
id|__u64
id|data
suffix:semicolon
multiline_comment|/* char* for sparc and sparc64 */
DECL|member|off
id|__u64
id|off
suffix:semicolon
DECL|member|size
id|__u32
id|size
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* _SPARC_JSFLASH_H */
eof
