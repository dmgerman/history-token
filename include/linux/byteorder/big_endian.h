macro_line|#ifndef _LINUX_BYTEORDER_BIG_ENDIAN_H
DECL|macro|_LINUX_BYTEORDER_BIG_ENDIAN_H
mdefine_line|#define _LINUX_BYTEORDER_BIG_ENDIAN_H
macro_line|#ifndef __BIG_ENDIAN
DECL|macro|__BIG_ENDIAN
mdefine_line|#define __BIG_ENDIAN 4321
macro_line|#endif
macro_line|#ifndef __BIG_ENDIAN_BITFIELD
DECL|macro|__BIG_ENDIAN_BITFIELD
mdefine_line|#define __BIG_ENDIAN_BITFIELD
macro_line|#endif
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/byteorder/swab.h&gt;
DECL|macro|__constant_htonl
mdefine_line|#define __constant_htonl(x) ((__force __be32)(__u32)(x))
DECL|macro|__constant_ntohl
mdefine_line|#define __constant_ntohl(x) ((__force __u32)(__be32)(x))
DECL|macro|__constant_htons
mdefine_line|#define __constant_htons(x) ((__force __be16)(__u16)(x))
DECL|macro|__constant_ntohs
mdefine_line|#define __constant_ntohs(x) ((__force __u16)(__be16)(x))
DECL|macro|__constant_cpu_to_le64
mdefine_line|#define __constant_cpu_to_le64(x) ((__force __le64)___constant_swab64((x)))
DECL|macro|__constant_le64_to_cpu
mdefine_line|#define __constant_le64_to_cpu(x) ___constant_swab64((__force __u64)(__le64)(x))
DECL|macro|__constant_cpu_to_le32
mdefine_line|#define __constant_cpu_to_le32(x) ((__force __le32)___constant_swab32((x)))
DECL|macro|__constant_le32_to_cpu
mdefine_line|#define __constant_le32_to_cpu(x) ___constant_swab32((__force __u32)(__le32)(x))
DECL|macro|__constant_cpu_to_le16
mdefine_line|#define __constant_cpu_to_le16(x) ((__force __le16)___constant_swab16((x)))
DECL|macro|__constant_le16_to_cpu
mdefine_line|#define __constant_le16_to_cpu(x) ___constant_swab16((__force __u16)(__le16)(x))
DECL|macro|__constant_cpu_to_be64
mdefine_line|#define __constant_cpu_to_be64(x) ((__force __be64)(__u64)(x))
DECL|macro|__constant_be64_to_cpu
mdefine_line|#define __constant_be64_to_cpu(x) ((__force __u64)(__be64)(x))
DECL|macro|__constant_cpu_to_be32
mdefine_line|#define __constant_cpu_to_be32(x) ((__force __be32)(__u32)(x))
DECL|macro|__constant_be32_to_cpu
mdefine_line|#define __constant_be32_to_cpu(x) ((__force __u32)(__be32)(x))
DECL|macro|__constant_cpu_to_be16
mdefine_line|#define __constant_cpu_to_be16(x) ((__force __be16)(__u16)(x))
DECL|macro|__constant_be16_to_cpu
mdefine_line|#define __constant_be16_to_cpu(x) ((__force __u16)(__be16)(x))
DECL|macro|__cpu_to_le64
mdefine_line|#define __cpu_to_le64(x) ((__force __le64)__swab64((x)))
DECL|macro|__le64_to_cpu
mdefine_line|#define __le64_to_cpu(x) __swab64((__force __u64)(__le64)(x))
DECL|macro|__cpu_to_le32
mdefine_line|#define __cpu_to_le32(x) ((__force __le32)__swab32((x)))
DECL|macro|__le32_to_cpu
mdefine_line|#define __le32_to_cpu(x) __swab32((__force __u32)(__le32)(x))
DECL|macro|__cpu_to_le16
mdefine_line|#define __cpu_to_le16(x) ((__force __le16)__swab16((x)))
DECL|macro|__le16_to_cpu
mdefine_line|#define __le16_to_cpu(x) __swab16((__force __u16)(__le16)(x))
DECL|macro|__cpu_to_be64
mdefine_line|#define __cpu_to_be64(x) ((__force __be64)(__u64)(x))
DECL|macro|__be64_to_cpu
mdefine_line|#define __be64_to_cpu(x) ((__force __u64)(__be64)(x))
DECL|macro|__cpu_to_be32
mdefine_line|#define __cpu_to_be32(x) ((__force __be32)(__u32)(x))
DECL|macro|__be32_to_cpu
mdefine_line|#define __be32_to_cpu(x) ((__force __u32)(__be32)(x))
DECL|macro|__cpu_to_be16
mdefine_line|#define __cpu_to_be16(x) ((__force __be16)(__u16)(x))
DECL|macro|__be16_to_cpu
mdefine_line|#define __be16_to_cpu(x) ((__force __u16)(__be16)(x))
DECL|function|__cpu_to_le64p
r_static
r_inline
id|__le64
id|__cpu_to_le64p
c_func
(paren
r_const
id|__u64
op_star
id|p
)paren
(brace
r_return
(paren
id|__force
id|__le64
)paren
id|__swab64p
c_func
(paren
id|p
)paren
suffix:semicolon
)brace
DECL|function|__le64_to_cpup
r_static
r_inline
id|__u64
id|__le64_to_cpup
c_func
(paren
r_const
id|__le64
op_star
id|p
)paren
(brace
r_return
id|__swab64p
c_func
(paren
(paren
id|__u64
op_star
)paren
id|p
)paren
suffix:semicolon
)brace
DECL|function|__cpu_to_le32p
r_static
r_inline
id|__le32
id|__cpu_to_le32p
c_func
(paren
r_const
id|__u32
op_star
id|p
)paren
(brace
r_return
(paren
id|__force
id|__le32
)paren
id|__swab32p
c_func
(paren
id|p
)paren
suffix:semicolon
)brace
DECL|function|__le32_to_cpup
r_static
r_inline
id|__u32
id|__le32_to_cpup
c_func
(paren
r_const
id|__le32
op_star
id|p
)paren
(brace
r_return
id|__swab32p
c_func
(paren
(paren
id|__u32
op_star
)paren
id|p
)paren
suffix:semicolon
)brace
DECL|function|__cpu_to_le16p
r_static
r_inline
id|__le16
id|__cpu_to_le16p
c_func
(paren
r_const
id|__u16
op_star
id|p
)paren
(brace
r_return
(paren
id|__force
id|__le16
)paren
id|__swab16p
c_func
(paren
id|p
)paren
suffix:semicolon
)brace
DECL|function|__le16_to_cpup
r_static
r_inline
id|__u16
id|__le16_to_cpup
c_func
(paren
r_const
id|__le16
op_star
id|p
)paren
(brace
r_return
id|__swab16p
c_func
(paren
(paren
id|__u16
op_star
)paren
id|p
)paren
suffix:semicolon
)brace
DECL|function|__cpu_to_be64p
r_static
r_inline
id|__be64
id|__cpu_to_be64p
c_func
(paren
r_const
id|__u64
op_star
id|p
)paren
(brace
r_return
(paren
id|__force
id|__be64
)paren
op_star
id|p
suffix:semicolon
)brace
DECL|function|__be64_to_cpup
r_static
r_inline
id|__u64
id|__be64_to_cpup
c_func
(paren
r_const
id|__be64
op_star
id|p
)paren
(brace
r_return
(paren
id|__force
id|__u64
)paren
op_star
id|p
suffix:semicolon
)brace
DECL|function|__cpu_to_be32p
r_static
r_inline
id|__be32
id|__cpu_to_be32p
c_func
(paren
r_const
id|__u32
op_star
id|p
)paren
(brace
r_return
(paren
id|__force
id|__be32
)paren
op_star
id|p
suffix:semicolon
)brace
DECL|function|__be32_to_cpup
r_static
r_inline
id|__u32
id|__be32_to_cpup
c_func
(paren
r_const
id|__be32
op_star
id|p
)paren
(brace
r_return
(paren
id|__force
id|__u32
)paren
op_star
id|p
suffix:semicolon
)brace
DECL|function|__cpu_to_be16p
r_static
r_inline
id|__be16
id|__cpu_to_be16p
c_func
(paren
r_const
id|__u16
op_star
id|p
)paren
(brace
r_return
(paren
id|__force
id|__be16
)paren
op_star
id|p
suffix:semicolon
)brace
DECL|function|__be16_to_cpup
r_static
r_inline
id|__u16
id|__be16_to_cpup
c_func
(paren
r_const
id|__be16
op_star
id|p
)paren
(brace
r_return
(paren
id|__force
id|__u16
)paren
op_star
id|p
suffix:semicolon
)brace
DECL|macro|__cpu_to_le64s
mdefine_line|#define __cpu_to_le64s(x) __swab64s((x))
DECL|macro|__le64_to_cpus
mdefine_line|#define __le64_to_cpus(x) __swab64s((x))
DECL|macro|__cpu_to_le32s
mdefine_line|#define __cpu_to_le32s(x) __swab32s((x))
DECL|macro|__le32_to_cpus
mdefine_line|#define __le32_to_cpus(x) __swab32s((x))
DECL|macro|__cpu_to_le16s
mdefine_line|#define __cpu_to_le16s(x) __swab16s((x))
DECL|macro|__le16_to_cpus
mdefine_line|#define __le16_to_cpus(x) __swab16s((x))
DECL|macro|__cpu_to_be64s
mdefine_line|#define __cpu_to_be64s(x) do {} while (0)
DECL|macro|__be64_to_cpus
mdefine_line|#define __be64_to_cpus(x) do {} while (0)
DECL|macro|__cpu_to_be32s
mdefine_line|#define __cpu_to_be32s(x) do {} while (0)
DECL|macro|__be32_to_cpus
mdefine_line|#define __be32_to_cpus(x) do {} while (0)
DECL|macro|__cpu_to_be16s
mdefine_line|#define __cpu_to_be16s(x) do {} while (0)
DECL|macro|__be16_to_cpus
mdefine_line|#define __be16_to_cpus(x) do {} while (0)
macro_line|#include &lt;linux/byteorder/generic.h&gt;
macro_line|#endif /* _LINUX_BYTEORDER_BIG_ENDIAN_H */
eof
