multiline_comment|/*&n; * BK Id: SCCS/s.byteorder.h 1.8 10/11/01 13:02:49 trini&n; */
macro_line|#ifndef _PPC_BYTEORDER_H
DECL|macro|_PPC_BYTEORDER_H
mdefine_line|#define _PPC_BYTEORDER_H
macro_line|#include &lt;asm/types.h&gt;
macro_line|#ifdef __GNUC__
macro_line|#ifdef __KERNEL__
DECL|function|ld_le16
r_extern
id|__inline__
r_int
id|ld_le16
c_func
(paren
r_const
r_volatile
r_int
r_int
op_star
id|addr
)paren
(brace
r_int
id|val
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;lhbrx %0,0,%1&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|val
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|addr
)paren
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
DECL|function|st_le16
r_extern
id|__inline__
r_void
id|st_le16
c_func
(paren
r_volatile
r_int
r_int
op_star
id|addr
comma
r_const
r_int
id|val
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;sthbrx %1,0,%2&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
id|addr
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|val
)paren
comma
l_string|&quot;r&quot;
(paren
id|addr
)paren
)paren
suffix:semicolon
)brace
DECL|function|ld_le32
r_extern
id|__inline__
r_int
id|ld_le32
c_func
(paren
r_const
r_volatile
r_int
op_star
id|addr
)paren
(brace
r_int
id|val
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;lwbrx %0,0,%1&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|val
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|addr
)paren
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
DECL|function|st_le32
r_extern
id|__inline__
r_void
id|st_le32
c_func
(paren
r_volatile
r_int
op_star
id|addr
comma
r_const
r_int
id|val
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;stwbrx %1,0,%2&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
id|addr
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|val
)paren
comma
l_string|&quot;r&quot;
(paren
id|addr
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* alas, egcs sounds like it has a bug in this code that doesn&squot;t use the&n;   inline asm correctly, and can cause file corruption. Until I hear that&n;   it&squot;s fixed, I can live without the extra speed. I hope. */
macro_line|#if 0
r_static
id|__inline__
id|__const__
id|__u16
id|___arch__swab16
c_func
(paren
id|__u16
id|value
)paren
(brace
id|__u16
id|result
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;rlwimi %0,%1,8,16,23&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|result
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|value
)paren
comma
l_string|&quot;0&quot;
(paren
id|value
op_rshift
l_int|8
)paren
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
r_static
id|__inline__
id|__const__
id|__u32
id|___arch__swab32
c_func
(paren
id|__u32
id|value
)paren
(brace
id|__u32
id|result
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;rlwimi %0,%1,24,16,23&bslash;n&bslash;t&quot;
l_string|&quot;rlwimi %0,%1,8,8,15&bslash;n&bslash;t&quot;
l_string|&quot;rlwimi %0,%1,24,0,7&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|result
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|value
)paren
comma
l_string|&quot;0&quot;
(paren
id|value
op_rshift
l_int|24
)paren
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
mdefine_line|#define __arch__swab32(x) ___arch__swab32(x)
mdefine_line|#define __arch__swab16(x) ___arch__swab16(x)
macro_line|#endif /* 0 */
multiline_comment|/* The same, but returns converted value from the location pointer by addr. */
DECL|macro|__arch__swab16p
mdefine_line|#define __arch__swab16p(addr) ld_le16(addr)
DECL|macro|__arch__swab32p
mdefine_line|#define __arch__swab32p(addr) ld_le32(addr)
multiline_comment|/* The same, but do the conversion in situ, ie. put the value back to addr. */
DECL|macro|__arch__swab16s
mdefine_line|#define __arch__swab16s(addr) st_le16(addr,*addr)
DECL|macro|__arch__swab32s
mdefine_line|#define __arch__swab32s(addr) st_le32(addr,*addr)
macro_line|#endif /* __KERNEL__ */
macro_line|#if !defined(__STRICT_ANSI__) || defined(__KERNEL__)
DECL|macro|__BYTEORDER_HAS_U64__
macro_line|#  define __BYTEORDER_HAS_U64__
DECL|macro|__SWAB_64_THRU_32__
macro_line|#  define __SWAB_64_THRU_32__
macro_line|#endif
macro_line|#endif /* __GNUC__ */
macro_line|#include &lt;linux/byteorder/big_endian.h&gt;
macro_line|#endif /* _PPC_BYTEORDER_H */
eof
