macro_line|#ifndef _LINUX_BYTEORDER_PDP_ENDIAN_H
DECL|macro|_LINUX_BYTEORDER_PDP_ENDIAN_H
mdefine_line|#define _LINUX_BYTEORDER_PDP_ENDIAN_H
multiline_comment|/*&n; * Could have been named NUXI-endian, but we use the same name as in glibc.&n; * hopefully only the PDP and its evolutions (old VAXen in compatibility mode)&n; * should ever use this braindead byteorder.&n; * This file *should* work, but has not been tested.&n; *&n; * little-endian is 1234; big-endian is 4321; nuxi/pdp-endian is 3412&n; *&n; * I thought vaxen were NUXI-endian, but was told they were correct-endian&n; * (little-endian), though indeed there existed NUXI-endian machines&n; * (DEC PDP-11 and old VAXen in compatibility mode).&n; * This makes this file a bit useless, but as a proof-of-concept.&n; *&n; * But what does a __u64 look like: is it 34127856 or 78563412 ???&n; * I don&squot;t dare imagine! Hence, no 64-bit byteorder support yet.&n; * Hopefully, there 64-bit pdp-endian support shouldn&squot;t ever be required.&n; *&n; */
macro_line|#ifndef __PDP_ENDIAN
DECL|macro|__PDP_ENDIAN
mdefine_line|#define __PDP_ENDIAN 3412
macro_line|#endif
macro_line|#ifndef __PDP_ENDIAN_BITFIELD
DECL|macro|__PDP_ENDIAN_BITFIELD
mdefine_line|#define __PDP_ENDIAN_BITFIELD
macro_line|#endif
macro_line|#include &lt;linux/byteorder/swab.h&gt;
macro_line|#include &lt;linux/byteorder/swabb.h&gt;
DECL|macro|__constant_htonl
mdefine_line|#define __constant_htonl(x) ___constant_swahb32((x))
DECL|macro|__constant_ntohl
mdefine_line|#define __constant_ntohl(x) ___constant_swahb32((x))
DECL|macro|__constant_htons
mdefine_line|#define __constant_htons(x) ___constant_swab16((x))
DECL|macro|__constant_ntohs
mdefine_line|#define __constant_ntohs(x) ___constant_swab16((x))
DECL|macro|__constant_cpu_to_le64
mdefine_line|#define __constant_cpu_to_le64(x) I DON&squot;T KNOW
DECL|macro|__constant_le64_to_cpu
mdefine_line|#define __constant_le64_to_cpu(x) I DON&squot;T KNOW
DECL|macro|__constant_cpu_to_le32
mdefine_line|#define __constant_cpu_to_le32(x) ___constant_swahw32((x))
DECL|macro|__constant_le32_to_cpu
mdefine_line|#define __constant_le32_to_cpu(x) ___constant_swahw32((x))
DECL|macro|__constant_cpu_to_le16
mdefine_line|#define __constant_cpu_to_le16(x) ((__u16)(x)
DECL|macro|__constant_le16_to_cpu
mdefine_line|#define __constant_le16_to_cpu(x) ((__u16)(x)
DECL|macro|__constant_cpu_to_be64
mdefine_line|#define __constant_cpu_to_be64(x) I DON&squot;T KNOW
DECL|macro|__constant_be64_to_cpu
mdefine_line|#define __constant_be64_to_cpu(x) I DON&squot;T KNOW
DECL|macro|__constant_cpu_to_be32
mdefine_line|#define __constant_cpu_to_be32(x) ___constant_swahb32((x))
DECL|macro|__constant_be32_to_cpu
mdefine_line|#define __constant_be32_to_cpu(x) ___constant_swahb32((x))
DECL|macro|__constant_cpu_to_be16
mdefine_line|#define __constant_cpu_to_be16(x) ___constant_swab16((x))
DECL|macro|__constant_be16_to_cpu
mdefine_line|#define __constant_be16_to_cpu(x) ___constant_swab16((x))
DECL|macro|__cpu_to_le64
mdefine_line|#define __cpu_to_le64(x) I DON&squot;T KNOW
DECL|macro|__le64_to_cpu
mdefine_line|#define __le64_to_cpu(x) I DON&squot;T KNOW
DECL|macro|__cpu_to_le32
mdefine_line|#define __cpu_to_le32(x) ___swahw32((x))
DECL|macro|__le32_to_cpu
mdefine_line|#define __le32_to_cpu(x) ___swahw32((x))
DECL|macro|__cpu_to_le16
mdefine_line|#define __cpu_to_le16(x) ((__u16)(x)
DECL|macro|__le16_to_cpu
mdefine_line|#define __le16_to_cpu(x) ((__u16)(x)
DECL|macro|__cpu_to_be64
mdefine_line|#define __cpu_to_be64(x) I DON&squot;T KNOW
DECL|macro|__be64_to_cpu
mdefine_line|#define __be64_to_cpu(x) I DON&squot;T KNOW
DECL|macro|__cpu_to_be32
mdefine_line|#define __cpu_to_be32(x) __swahb32((x))
DECL|macro|__be32_to_cpu
mdefine_line|#define __be32_to_cpu(x) __swahb32((x))
DECL|macro|__cpu_to_be16
mdefine_line|#define __cpu_to_be16(x) __swab16((x))
DECL|macro|__be16_to_cpu
mdefine_line|#define __be16_to_cpu(x) __swab16((x))
DECL|macro|__cpu_to_le64p
mdefine_line|#define __cpu_to_le64p(x) I DON&squot;T KNOW
DECL|macro|__le64_to_cpup
mdefine_line|#define __le64_to_cpup(x) I DON&squot;T KNOW
DECL|macro|__cpu_to_le32p
mdefine_line|#define __cpu_to_le32p(x) ___swahw32p((x))
DECL|macro|__le32_to_cpup
mdefine_line|#define __le32_to_cpup(x) ___swahw32p((x))
DECL|macro|__cpu_to_le16p
mdefine_line|#define __cpu_to_le16p(x) (*(__u16*)(x))
DECL|macro|__le16_to_cpup
mdefine_line|#define __le16_to_cpup(x) (*(__u16*)(x))
DECL|macro|__cpu_to_be64p
mdefine_line|#define __cpu_to_be64p(x) I DON&squot;T KNOW
DECL|macro|__be64_to_cpup
mdefine_line|#define __be64_to_cpup(x) I DON&squot;T KNOW
DECL|macro|__cpu_to_be32p
mdefine_line|#define __cpu_to_be32p(x) __swahb32p((x))
DECL|macro|__be32_to_cpup
mdefine_line|#define __be32_to_cpup(x) __swahb32p((x))
DECL|macro|__cpu_to_be16p
mdefine_line|#define __cpu_to_be16p(x) __swab16p((x))
DECL|macro|__be16_to_cpup
mdefine_line|#define __be16_to_cpup(x) __swab16p((x))
DECL|macro|__cpu_to_le64s
mdefine_line|#define __cpu_to_le64s(x) I DON&squot;T KNOW
DECL|macro|__le64_to_cpus
mdefine_line|#define __le64_to_cpus(x) I DON&squot;T KNOW
DECL|macro|__cpu_to_le32s
mdefine_line|#define __cpu_to_le32s(x) ___swahw32s((x))
DECL|macro|__le32_to_cpus
mdefine_line|#define __le32_to_cpus(x) ___swahw32s((x))
DECL|macro|__cpu_to_le16s
mdefine_line|#define __cpu_to_le16s(x) do {} while (0)
DECL|macro|__le16_to_cpus
mdefine_line|#define __le16_to_cpus(x) do {} while (0)
DECL|macro|__cpu_to_be64s
mdefine_line|#define __cpu_to_be64s(x) I DON&squot;T KNOW
DECL|macro|__be64_to_cpus
mdefine_line|#define __be64_to_cpus(x) I DON&squot;T KNOW
DECL|macro|__cpu_to_be32s
mdefine_line|#define __cpu_to_be32s(x) __swahb32s((x))
DECL|macro|__be32_to_cpus
mdefine_line|#define __be32_to_cpus(x) __swahb32s((x))
DECL|macro|__cpu_to_be16s
mdefine_line|#define __cpu_to_be16s(x) __swab16s((x))
DECL|macro|__be16_to_cpus
mdefine_line|#define __be16_to_cpus(x) __swab16s((x))
macro_line|#include &lt;linux/byteorder/generic.h&gt;
macro_line|#endif /* _LINUX_BYTEORDER_PDP_ENDIAN_H */
eof
