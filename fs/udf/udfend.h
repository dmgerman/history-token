macro_line|#ifndef __UDF_ENDIAN_H
DECL|macro|__UDF_ENDIAN_H
mdefine_line|#define __UDF_ENDIAN_H
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;linux/string.h&gt;
DECL|function|lelb_to_cpu
r_static
r_inline
id|kernel_lb_addr
id|lelb_to_cpu
c_func
(paren
id|lb_addr
id|in
)paren
(brace
id|kernel_lb_addr
id|out
suffix:semicolon
id|out.logicalBlockNum
op_assign
id|le32_to_cpu
c_func
(paren
id|in.logicalBlockNum
)paren
suffix:semicolon
id|out.partitionReferenceNum
op_assign
id|le16_to_cpu
c_func
(paren
id|in.partitionReferenceNum
)paren
suffix:semicolon
r_return
id|out
suffix:semicolon
)brace
DECL|function|cpu_to_lelb
r_static
r_inline
id|lb_addr
id|cpu_to_lelb
c_func
(paren
id|kernel_lb_addr
id|in
)paren
(brace
id|lb_addr
id|out
suffix:semicolon
id|out.logicalBlockNum
op_assign
id|cpu_to_le32
c_func
(paren
id|in.logicalBlockNum
)paren
suffix:semicolon
id|out.partitionReferenceNum
op_assign
id|cpu_to_le16
c_func
(paren
id|in.partitionReferenceNum
)paren
suffix:semicolon
r_return
id|out
suffix:semicolon
)brace
DECL|function|lets_to_cpu
r_static
r_inline
id|kernel_timestamp
id|lets_to_cpu
c_func
(paren
id|timestamp
id|in
)paren
(brace
id|kernel_timestamp
id|out
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|out
comma
op_amp
id|in
comma
r_sizeof
(paren
id|timestamp
)paren
)paren
suffix:semicolon
id|out.typeAndTimezone
op_assign
id|le16_to_cpu
c_func
(paren
id|in.typeAndTimezone
)paren
suffix:semicolon
id|out.year
op_assign
id|le16_to_cpu
c_func
(paren
id|in.year
)paren
suffix:semicolon
r_return
id|out
suffix:semicolon
)brace
DECL|function|lesa_to_cpu
r_static
r_inline
id|short_ad
id|lesa_to_cpu
c_func
(paren
id|short_ad
id|in
)paren
(brace
id|short_ad
id|out
suffix:semicolon
id|out.extLength
op_assign
id|le32_to_cpu
c_func
(paren
id|in.extLength
)paren
suffix:semicolon
id|out.extPosition
op_assign
id|le32_to_cpu
c_func
(paren
id|in.extPosition
)paren
suffix:semicolon
r_return
id|out
suffix:semicolon
)brace
DECL|function|cpu_to_lesa
r_static
r_inline
id|short_ad
id|cpu_to_lesa
c_func
(paren
id|short_ad
id|in
)paren
(brace
id|short_ad
id|out
suffix:semicolon
id|out.extLength
op_assign
id|cpu_to_le32
c_func
(paren
id|in.extLength
)paren
suffix:semicolon
id|out.extPosition
op_assign
id|cpu_to_le32
c_func
(paren
id|in.extPosition
)paren
suffix:semicolon
r_return
id|out
suffix:semicolon
)brace
DECL|function|lela_to_cpu
r_static
r_inline
id|kernel_long_ad
id|lela_to_cpu
c_func
(paren
id|long_ad
id|in
)paren
(brace
id|kernel_long_ad
id|out
suffix:semicolon
id|out.extLength
op_assign
id|le32_to_cpu
c_func
(paren
id|in.extLength
)paren
suffix:semicolon
id|out.extLocation
op_assign
id|lelb_to_cpu
c_func
(paren
id|in.extLocation
)paren
suffix:semicolon
r_return
id|out
suffix:semicolon
)brace
DECL|function|cpu_to_lela
r_static
r_inline
id|long_ad
id|cpu_to_lela
c_func
(paren
id|kernel_long_ad
id|in
)paren
(brace
id|long_ad
id|out
suffix:semicolon
id|out.extLength
op_assign
id|cpu_to_le32
c_func
(paren
id|in.extLength
)paren
suffix:semicolon
id|out.extLocation
op_assign
id|cpu_to_lelb
c_func
(paren
id|in.extLocation
)paren
suffix:semicolon
r_return
id|out
suffix:semicolon
)brace
DECL|function|leea_to_cpu
r_static
r_inline
id|kernel_extent_ad
id|leea_to_cpu
c_func
(paren
id|extent_ad
id|in
)paren
(brace
id|kernel_extent_ad
id|out
suffix:semicolon
id|out.extLength
op_assign
id|le32_to_cpu
c_func
(paren
id|in.extLength
)paren
suffix:semicolon
id|out.extLocation
op_assign
id|le32_to_cpu
c_func
(paren
id|in.extLocation
)paren
suffix:semicolon
r_return
id|out
suffix:semicolon
)brace
DECL|function|cpu_to_lets
r_static
r_inline
id|timestamp
id|cpu_to_lets
c_func
(paren
id|kernel_timestamp
id|in
)paren
(brace
id|timestamp
id|out
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|out
comma
op_amp
id|in
comma
r_sizeof
(paren
id|timestamp
)paren
)paren
suffix:semicolon
id|out.typeAndTimezone
op_assign
id|cpu_to_le16
c_func
(paren
id|in.typeAndTimezone
)paren
suffix:semicolon
id|out.year
op_assign
id|cpu_to_le16
c_func
(paren
id|in.year
)paren
suffix:semicolon
r_return
id|out
suffix:semicolon
)brace
macro_line|#endif /* __UDF_ENDIAN_H */
eof
