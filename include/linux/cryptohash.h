macro_line|#ifndef __CRYPTOHASH_H
DECL|macro|__CRYPTOHASH_H
mdefine_line|#define __CRYPTOHASH_H
DECL|macro|SHA_DIGEST_WORDS
mdefine_line|#define SHA_DIGEST_WORDS 5
DECL|macro|SHA_WORKSPACE_WORDS
mdefine_line|#define SHA_WORKSPACE_WORDS 80
r_void
id|sha_init
c_func
(paren
id|__u32
op_star
id|buf
)paren
suffix:semicolon
r_void
id|sha_transform
c_func
(paren
id|__u32
op_star
id|digest
comma
r_const
r_char
op_star
id|data
comma
id|__u32
op_star
id|W
)paren
suffix:semicolon
macro_line|#endif
eof
