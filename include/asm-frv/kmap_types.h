macro_line|#ifndef _ASM_KMAP_TYPES_H
DECL|macro|_ASM_KMAP_TYPES_H
mdefine_line|#define _ASM_KMAP_TYPES_H
DECL|enum|km_type
r_enum
id|km_type
(brace
multiline_comment|/* arch specific kmaps - change the numbers attached to these at your peril */
DECL|enumerator|__KM_CACHE
id|__KM_CACHE
comma
multiline_comment|/* cache flush page attachment point */
DECL|enumerator|__KM_PGD
id|__KM_PGD
comma
multiline_comment|/* current page directory */
DECL|enumerator|__KM_ITLB_PTD
id|__KM_ITLB_PTD
comma
multiline_comment|/* current instruction TLB miss page table lookup */
DECL|enumerator|__KM_DTLB_PTD
id|__KM_DTLB_PTD
comma
multiline_comment|/* current data TLB miss page table lookup */
multiline_comment|/* general kmaps */
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
DECL|enumerator|KM_SOFTIRQ0
id|KM_SOFTIRQ0
comma
DECL|enumerator|KM_SOFTIRQ1
id|KM_SOFTIRQ1
comma
DECL|enumerator|KM_TYPE_NR
id|KM_TYPE_NR
)brace
suffix:semicolon
macro_line|#endif
eof
