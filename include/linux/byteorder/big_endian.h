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
macro_line|#include &lt;linux/byteorder/swab.h&gt;
DECL|macro|__constant_htonl
mdefine_line|#define __constant_htonl(x) ((__u32)(x))
DECL|macro|__constant_ntohl
mdefine_line|#define __constant_ntohl(x) ((__u32)(x))
DECL|macro|__constant_htons
mdefine_line|#define __constant_htons(x) ((__u16)(x))
DECL|macro|__constant_ntohs
mdefine_line|#define __constant_ntohs(x) ((__u16)(x))
DECL|macro|__constant_cpu_to_le64
mdefine_line|#define __constant_cpu_to_le64(x) ___constant_swab64((x))
DECL|macro|__constant_le64_to_cpu
mdefine_line|#define __constant_le64_to_cpu(x) ___constant_swab64((x))
DECL|macro|__constant_cpu_to_le32
mdefine_line|#define __constant_cpu_to_le32(x) ___constant_swab32((x))
DECL|macro|__constant_le32_to_cpu
mdefine_line|#define __constant_le32_to_cpu(x) ___constant_swab32((x))
DECL|macro|__constant_cpu_to_le16
mdefine_line|#define __constant_cpu_to_le16(x) ___constant_swab16((x))
DECL|macro|__constant_le16_to_cpu
mdefine_line|#define __constant_le16_to_cpu(x) ___constant_swab16((x))
DECL|macro|__constant_cpu_to_be64
mdefine_line|#define __constant_cpu_to_be64(x) ((__u64)(x))
DECL|macro|__constant_be64_to_cpu
mdefine_line|#define __constant_be64_to_cpu(x) ((__u64)(x))
DECL|macro|__constant_cpu_to_be32
mdefine_line|#define __constant_cpu_to_be32(x) ((__u32)(x))
DECL|macro|__constant_be32_to_cpu
mdefine_line|#define __constant_be32_to_cpu(x) ((__u32)(x))
DECL|macro|__constant_cpu_to_be16
mdefine_line|#define __constant_cpu_to_be16(x) ((__u16)(x))
DECL|macro|__constant_be16_to_cpu
mdefine_line|#define __constant_be16_to_cpu(x) ((__u16)(x))
DECL|macro|__cpu_to_le64
mdefine_line|#define __cpu_to_le64(x) __swab64((x))
DECL|macro|__le64_to_cpu
mdefine_line|#define __le64_to_cpu(x) __swab64((x))
DECL|macro|__cpu_to_le32
mdefine_line|#define __cpu_to_le32(x) __swab32((x))
DECL|macro|__le32_to_cpu
mdefine_line|#define __le32_to_cpu(x) __swab32((x))
DECL|macro|__cpu_to_le16
mdefine_line|#define __cpu_to_le16(x) __swab16((x))
DECL|macro|__le16_to_cpu
mdefine_line|#define __le16_to_cpu(x) __swab16((x))
DECL|macro|__cpu_to_be64
mdefine_line|#define __cpu_to_be64(x) ((__u64)(x))
DECL|macro|__be64_to_cpu
mdefine_line|#define __be64_to_cpu(x) ((__u64)(x))
DECL|macro|__cpu_to_be32
mdefine_line|#define __cpu_to_be32(x) ((__u32)(x))
DECL|macro|__be32_to_cpu
mdefine_line|#define __be32_to_cpu(x) ((__u32)(x))
DECL|macro|__cpu_to_be16
mdefine_line|#define __cpu_to_be16(x) ((__u16)(x))
DECL|macro|__be16_to_cpu
mdefine_line|#define __be16_to_cpu(x) ((__u16)(x))
DECL|macro|__cpu_to_le64p
mdefine_line|#define __cpu_to_le64p(x) __swab64p((x))
DECL|macro|__le64_to_cpup
mdefine_line|#define __le64_to_cpup(x) __swab64p((x))
DECL|macro|__cpu_to_le32p
mdefine_line|#define __cpu_to_le32p(x) __swab32p((x))
DECL|macro|__le32_to_cpup
mdefine_line|#define __le32_to_cpup(x) __swab32p((x))
DECL|macro|__cpu_to_le16p
mdefine_line|#define __cpu_to_le16p(x) __swab16p((x))
DECL|macro|__le16_to_cpup
mdefine_line|#define __le16_to_cpup(x) __swab16p((x))
DECL|macro|__cpu_to_be64p
mdefine_line|#define __cpu_to_be64p(x) (*(__u64*)(x))
DECL|macro|__be64_to_cpup
mdefine_line|#define __be64_to_cpup(x) (*(__u64*)(x))
DECL|macro|__cpu_to_be32p
mdefine_line|#define __cpu_to_be32p(x) (*(__u32*)(x))
DECL|macro|__be32_to_cpup
mdefine_line|#define __be32_to_cpup(x) (*(__u32*)(x))
DECL|macro|__cpu_to_be16p
mdefine_line|#define __cpu_to_be16p(x) (*(__u16*)(x))
DECL|macro|__be16_to_cpup
mdefine_line|#define __be16_to_cpup(x) (*(__u16*)(x))
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
