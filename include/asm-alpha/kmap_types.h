macro_line|#ifndef _ASM_KMAP_TYPES_H
DECL|macro|_ASM_KMAP_TYPES_H
mdefine_line|#define _ASM_KMAP_TYPES_H
multiline_comment|/* Dummy header just to define km_type. */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#if CONFIG_DEBUG_HIGHMEM
DECL|macro|D
macro_line|# define D(n) __KM_FENCE_##n ,
macro_line|#else
DECL|macro|D
macro_line|# define D(n)
macro_line|#endif
DECL|enum|km_type
r_enum
id|km_type
(brace
DECL|enumerator|D
DECL|enumerator|KM_BOUNCE_READ
id|D
c_func
(paren
l_int|0
)paren
id|KM_BOUNCE_READ
comma
DECL|enumerator|D
DECL|enumerator|KM_SKB_SUNRPC_DATA
id|D
c_func
(paren
l_int|1
)paren
id|KM_SKB_SUNRPC_DATA
comma
DECL|enumerator|D
DECL|enumerator|KM_SKB_DATA_SOFTIRQ
id|D
c_func
(paren
l_int|2
)paren
id|KM_SKB_DATA_SOFTIRQ
comma
DECL|enumerator|D
DECL|enumerator|KM_USER0
id|D
c_func
(paren
l_int|3
)paren
id|KM_USER0
comma
DECL|enumerator|D
DECL|enumerator|KM_USER1
id|D
c_func
(paren
l_int|4
)paren
id|KM_USER1
comma
DECL|enumerator|D
DECL|enumerator|KM_BIO_SRC_IRQ
id|D
c_func
(paren
l_int|5
)paren
id|KM_BIO_SRC_IRQ
comma
DECL|enumerator|D
DECL|enumerator|KM_BIO_DST_IRQ
id|D
c_func
(paren
l_int|6
)paren
id|KM_BIO_DST_IRQ
comma
DECL|enumerator|D
DECL|enumerator|KM_PTE0
id|D
c_func
(paren
l_int|7
)paren
id|KM_PTE0
comma
DECL|enumerator|D
DECL|enumerator|KM_PTE1
id|D
c_func
(paren
l_int|8
)paren
id|KM_PTE1
comma
DECL|enumerator|D
DECL|enumerator|KM_IRQ0
id|D
c_func
(paren
l_int|9
)paren
id|KM_IRQ0
comma
DECL|enumerator|D
DECL|enumerator|KM_IRQ1
id|D
c_func
(paren
l_int|10
)paren
id|KM_IRQ1
comma
DECL|enumerator|D
DECL|enumerator|KM_TYPE_NR
id|D
c_func
(paren
l_int|11
)paren
id|KM_TYPE_NR
)brace
suffix:semicolon
DECL|macro|D
macro_line|#undef D
macro_line|#endif
eof