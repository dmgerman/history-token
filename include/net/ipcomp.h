macro_line|#ifndef _NET_IPCOMP_H
DECL|macro|_NET_IPCOMP_H
mdefine_line|#define _NET_IPCOMP_H
DECL|macro|IPCOMP_SCRATCH_SIZE
mdefine_line|#define IPCOMP_SCRATCH_SIZE     65400
DECL|struct|ipcomp_data
r_struct
id|ipcomp_data
(brace
DECL|member|threshold
id|u16
id|threshold
suffix:semicolon
DECL|member|scratch
id|u8
op_star
id|scratch
suffix:semicolon
DECL|member|tfm
r_struct
id|crypto_tfm
op_star
id|tfm
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
