multiline_comment|/*&n; * include/linux/idr.h&n; * &n; * 2002-10-18  written by Jim Houston jim.houston@ccur.com&n; *&t;Copyright (C) 2002 by Concurrent Computer Corporation&n; *&t;Distributed under the GNU GPL license version 2.&n; *&n; * Small id to pointer translation service avoiding fixed sized&n; * tables.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#if BITS_PER_LONG == 32
DECL|macro|IDR_BITS
macro_line|# define IDR_BITS 5
DECL|macro|IDR_FULL
macro_line|# define IDR_FULL 0xfffffffful
multiline_comment|/* We can only use two of the bits in the top level because there is&n;   only one possible bit in the top level (5 bits * 7 levels = 35&n;   bits, but you only use 31 bits in the id). */
DECL|macro|TOP_LEVEL_FULL
macro_line|# define TOP_LEVEL_FULL (IDR_FULL &gt;&gt; 30)
macro_line|#elif BITS_PER_LONG == 64
DECL|macro|IDR_BITS
macro_line|# define IDR_BITS 6
DECL|macro|IDR_FULL
macro_line|# define IDR_FULL 0xfffffffffffffffful
multiline_comment|/* We can only use two of the bits in the top level because there is&n;   only one possible bit in the top level (6 bits * 6 levels = 36&n;   bits, but you only use 31 bits in the id). */
DECL|macro|TOP_LEVEL_FULL
macro_line|# define TOP_LEVEL_FULL (IDR_FULL &gt;&gt; 62)
macro_line|#else
macro_line|# error &quot;BITS_PER_LONG is not 32 or 64&quot;
macro_line|#endif
DECL|macro|IDR_SIZE
mdefine_line|#define IDR_SIZE (1 &lt;&lt; IDR_BITS)
DECL|macro|IDR_MASK
mdefine_line|#define IDR_MASK ((1 &lt;&lt; IDR_BITS)-1)
DECL|macro|MAX_ID_SHIFT
mdefine_line|#define MAX_ID_SHIFT (sizeof(int)*8 - 1)
DECL|macro|MAX_ID_BIT
mdefine_line|#define MAX_ID_BIT (1U &lt;&lt; MAX_ID_SHIFT)
DECL|macro|MAX_ID_MASK
mdefine_line|#define MAX_ID_MASK (MAX_ID_BIT - 1)
multiline_comment|/* Leave the possibility of an incomplete final layer */
DECL|macro|MAX_LEVEL
mdefine_line|#define MAX_LEVEL (MAX_ID_SHIFT + IDR_BITS - 1) / IDR_BITS
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
multiline_comment|/* A zero bit means &quot;space here&quot; */
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
DECL|member|count
r_int
id|count
suffix:semicolon
multiline_comment|/* When zero, we can release it */
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
DECL|member|id_free
r_struct
id|idr_layer
op_star
id|id_free
suffix:semicolon
DECL|member|layers
r_int
id|layers
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
DECL|macro|IDR_INIT
mdefine_line|#define IDR_INIT(name)&t;&t;&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;.top&t;&t;= NULL,&t;&t;&t;&t;&t;&bslash;&n;&t;.id_free&t;= NULL,&t;&t;&t;&t;&t;&bslash;&n;&t;.layers &t;= 0,&t;&t;&t;&t;&t;&bslash;&n;&t;.id_free_cnt&t;= 0,&t;&t;&t;&t;&t;&bslash;&n;&t;.lock&t;&t;= SPIN_LOCK_UNLOCKED,&t;&t;&t;&bslash;&n;}
DECL|macro|DEFINE_IDR
mdefine_line|#define DEFINE_IDR(name)&t;struct idr name = IDR_INIT(name)
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
comma
r_int
id|gfp_mask
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
comma
r_int
op_star
id|id
)paren
suffix:semicolon
r_int
id|idr_get_new_above
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
comma
r_int
id|starting_id
comma
r_int
op_star
id|id
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
eof
