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
DECL|enumerator|KM_SKB_SUNRPC_DATA
id|KM_SKB_SUNRPC_DATA
comma
DECL|enumerator|KM_SKB_DATA_SOFTIRQ
id|KM_SKB_DATA_SOFTIRQ
comma
DECL|enumerator|KM_USER0
id|KM_USER0
comma
DECL|enumerator|KM_USER1
id|KM_USER1
comma
DECL|enumerator|KM_BIO_SRC_IRQ
id|KM_BIO_SRC_IRQ
comma
DECL|enumerator|KM_BIO_DST_IRQ
id|KM_BIO_DST_IRQ
comma
DECL|enumerator|KM_PTE0
id|KM_PTE0
comma
DECL|enumerator|KM_PTE1
id|KM_PTE1
comma
DECL|enumerator|KM_IRQ0
id|KM_IRQ0
comma
DECL|enumerator|KM_IRQ1
id|KM_IRQ1
comma
DECL|enumerator|KM_TYPE_NR
id|KM_TYPE_NR
)brace
suffix:semicolon
macro_line|#endif
macro_line|#endif /* __KERNEL__ */
eof