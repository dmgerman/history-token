macro_line|#ifdef __KERNEL__
macro_line|#ifndef _ASM_KMAP_TYPES_H
DECL|macro|_ASM_KMAP_TYPES_H
mdefine_line|#define _ASM_KMAP_TYPES_H
DECL|enum|km_type
r_enum
id|km_type
(brace
DECL|enumerator|KM_BOUNCE_READ
id|KM_BOUNCE_READ
comma
DECL|enumerator|KM_BOUNCE_WRITE
id|KM_BOUNCE_WRITE
comma
DECL|enumerator|KM_SKB_DATA
id|KM_SKB_DATA
comma
DECL|enumerator|KM_SKB_DATA_SOFTIRQ
id|KM_SKB_DATA_SOFTIRQ
comma
DECL|enumerator|KM_TYPE_NR
id|KM_TYPE_NR
)brace
suffix:semicolon
macro_line|#endif
macro_line|#endif /* __KERNEL__ */
eof
