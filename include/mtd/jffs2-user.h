multiline_comment|/*&n; * $Id: jffs2-user.h,v 1.1 2004/05/05 11:57:54 dwmw2 Exp $&n; *&n; * JFFS2 definitions for use in user space only&n; */
macro_line|#ifndef __JFFS2_USER_H__
DECL|macro|__JFFS2_USER_H__
mdefine_line|#define __JFFS2_USER_H__
multiline_comment|/* This file is blessed for inclusion by userspace */
macro_line|#include &lt;linux/jffs2.h&gt;
macro_line|#include &lt;endian.h&gt;
macro_line|#include &lt;byteswap.h&gt;
DECL|macro|cpu_to_je16
macro_line|#undef cpu_to_je16
DECL|macro|cpu_to_je32
macro_line|#undef cpu_to_je32
DECL|macro|cpu_to_jemode
macro_line|#undef cpu_to_jemode
DECL|macro|je16_to_cpu
macro_line|#undef je16_to_cpu
DECL|macro|je32_to_cpu
macro_line|#undef je32_to_cpu
DECL|macro|jemode_to_cpu
macro_line|#undef jemode_to_cpu
r_extern
r_int
id|target_endian
suffix:semicolon
DECL|macro|t16
mdefine_line|#define t16(x) ({ uint16_t __b = (x); (target_endian==__BYTE_ORDER)?__b:bswap_16(__b); })
DECL|macro|t32
mdefine_line|#define t32(x) ({ uint32_t __b = (x); (target_endian==__BYTE_ORDER)?__b:bswap_32(__b); })
DECL|macro|cpu_to_je16
mdefine_line|#define cpu_to_je16(x) ((jint16_t){t16(x)})
DECL|macro|cpu_to_je32
mdefine_line|#define cpu_to_je32(x) ((jint32_t){t32(x)})
DECL|macro|cpu_to_jemode
mdefine_line|#define cpu_to_jemode(x) ((jmode_t){t32(x)})
DECL|macro|je16_to_cpu
mdefine_line|#define je16_to_cpu(x) (t16((x).v16))
DECL|macro|je32_to_cpu
mdefine_line|#define je32_to_cpu(x) (t32((x).v32))
DECL|macro|jemode_to_cpu
mdefine_line|#define jemode_to_cpu(x) (t32((x).m))
macro_line|#endif /* __JFFS2_USER_H__ */
eof
