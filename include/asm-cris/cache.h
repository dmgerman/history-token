macro_line|#ifndef _ASM_CACHE_H
DECL|macro|_ASM_CACHE_H
mdefine_line|#define _ASM_CACHE_H
multiline_comment|/* Etrax 100LX have 32-byte cache-lines. When we add support for future chips&n; * here should be a check for CPU type.&n; */
DECL|macro|L1_CACHE_BYTES
mdefine_line|#define L1_CACHE_BYTES 32
DECL|macro|L1_CACHE_SHIFT_MAX
mdefine_line|#define L1_CACHE_SHIFT_MAX 5&t;/* largest L1 which this arch supports */
macro_line|#endif /* _ASM_CACHE_H */
eof
