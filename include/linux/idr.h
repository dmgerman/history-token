multiline_comment|/*&n; * include/linux/id.h&n; * &n; * 2002-10-18  written by Jim Houston jim.houston@ccur.com&n; *&t;Copyright (C) 2002 by Concurrent Computer Corporation&n; *&t;Distributed under the GNU GPL license version 2.&n; *&n; * Small id to pointer translation service avoiding fixed sized&n; * tables.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
DECL|macro|RESERVED_ID_BITS
mdefine_line|#define RESERVED_ID_BITS 8
macro_line|#if     BITS_PER_LONG == 32
DECL|macro|IDR_BITS
mdefine_line|#define IDR_BITS 5
DECL|macro|IDR_FULL
mdefine_line|#define IDR_FULL 0xffffffff
macro_line|#elif BITS_PER_LONG == 64
DECL|macro|IDR_BITS
mdefine_line|#define IDR_BITS 6
DECL|macro|IDR_FULL
mdefine_line|#define IDR_FULL 0xffffffffffffffff
macro_line|#else
macro_line|#error &quot;BITS_PER_LONG is not 32 or 64&quot;
macro_line|#endif
DECL|macro|IDR_MASK
mdefine_line|#define IDR_MASK ((1 &lt;&lt; IDR_BITS)-1)
multiline_comment|/* Leave the possibility of an incomplete final layer */
DECL|macro|MAX_LEVEL
mdefine_line|#define MAX_LEVEL (BITS_PER_LONG - RESERVED_ID_BITS + IDR_BITS - 1) / IDR_BITS
DECL|macro|MAX_ID_SHIFT
mdefine_line|#define MAX_ID_SHIFT (BITS_PER_LONG - RESERVED_ID_BITS)
DECL|macro|MAX_ID_BIT
mdefine_line|#define MAX_ID_BIT (1L &lt;&lt; MAX_ID_SHIFT)
DECL|macro|MAX_ID_MASK
mdefine_line|#define MAX_ID_MASK (MAX_ID_BIT - 1)
multiline_comment|/* Number of id_layer structs to leave in free list */
DECL|macro|IDR_FREE_MAX
mdefine_line|#define IDR_FREE_MAX MAX_LEVEL + MAX_LEVEL
DECL|struct|idr_layer
r_struct
id|idr_layer
(brace
DECL|member|bitmap
r_int
r_int
id|bitmap
suffix:semicolon
singleline_comment|// A zero bit means &quot;space here&quot;
DECL|member|count
r_int
id|count
suffix:semicolon
singleline_comment|// When zero, we can release it
DECL|member|ary
r_struct
id|idr_layer
op_star
id|ary
(braket
l_int|1
op_lshift
id|IDR_BITS
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|idr
r_struct
id|idr
(brace
DECL|member|top
r_struct
id|idr_layer
op_star
id|top
suffix:semicolon
DECL|member|layers
r_int
id|layers
suffix:semicolon
DECL|member|count
r_int
id|count
suffix:semicolon
DECL|member|id_free
r_struct
id|idr_layer
op_star
id|id_free
suffix:semicolon
DECL|member|id_free_cnt
r_int
id|id_free_cnt
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * This is what we export.&n; */
r_void
op_star
id|idr_find
c_func
(paren
r_struct
id|idr
op_star
id|idp
comma
r_int
id|id
)paren
suffix:semicolon
r_int
id|idr_pre_get
c_func
(paren
r_struct
id|idr
op_star
id|idp
)paren
suffix:semicolon
r_int
id|idr_get_new
c_func
(paren
r_struct
id|idr
op_star
id|idp
comma
r_void
op_star
id|ptr
)paren
suffix:semicolon
r_void
id|idr_remove
c_func
(paren
r_struct
id|idr
op_star
id|idp
comma
r_int
id|id
)paren
suffix:semicolon
r_void
id|idr_init
c_func
(paren
r_struct
id|idr
op_star
id|idp
)paren
suffix:semicolon
r_extern
id|kmem_cache_t
op_star
id|idr_layer_cache
suffix:semicolon
eof
