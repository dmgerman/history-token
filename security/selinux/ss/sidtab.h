multiline_comment|/*&n; * A security identifier table (sidtab) is a hash table&n; * of security context structures indexed by SID value.&n; *&n; * Author : Stephen Smalley, &lt;sds@epoch.ncsc.mil&gt;&n; */
macro_line|#ifndef _SS_SIDTAB_H_
DECL|macro|_SS_SIDTAB_H_
mdefine_line|#define _SS_SIDTAB_H_
macro_line|#include &quot;context.h&quot;
DECL|struct|sidtab_node
r_struct
id|sidtab_node
(brace
DECL|member|sid
id|u32
id|sid
suffix:semicolon
multiline_comment|/* security identifier */
DECL|member|context
r_struct
id|context
id|context
suffix:semicolon
multiline_comment|/* security context structure */
DECL|member|next
r_struct
id|sidtab_node
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SIDTAB_HASH_BITS
mdefine_line|#define SIDTAB_HASH_BITS 7
DECL|macro|SIDTAB_HASH_BUCKETS
mdefine_line|#define SIDTAB_HASH_BUCKETS (1 &lt;&lt; SIDTAB_HASH_BITS)
DECL|macro|SIDTAB_HASH_MASK
mdefine_line|#define SIDTAB_HASH_MASK (SIDTAB_HASH_BUCKETS-1)
DECL|macro|SIDTAB_SIZE
mdefine_line|#define SIDTAB_SIZE SIDTAB_HASH_BUCKETS
DECL|struct|sidtab
r_struct
id|sidtab
(brace
DECL|member|htable
r_struct
id|sidtab_node
op_star
op_star
id|htable
suffix:semicolon
DECL|member|nel
r_int
r_int
id|nel
suffix:semicolon
multiline_comment|/* number of elements */
DECL|member|next_sid
r_int
r_int
id|next_sid
suffix:semicolon
multiline_comment|/* next SID to allocate */
DECL|member|shutdown
r_int
r_char
id|shutdown
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
)brace
suffix:semicolon
r_int
id|sidtab_init
c_func
(paren
r_struct
id|sidtab
op_star
id|s
)paren
suffix:semicolon
r_int
id|sidtab_insert
c_func
(paren
r_struct
id|sidtab
op_star
id|s
comma
id|u32
id|sid
comma
r_struct
id|context
op_star
id|context
)paren
suffix:semicolon
r_struct
id|context
op_star
id|sidtab_search
c_func
(paren
r_struct
id|sidtab
op_star
id|s
comma
id|u32
id|sid
)paren
suffix:semicolon
r_int
id|sidtab_map
c_func
(paren
r_struct
id|sidtab
op_star
id|s
comma
r_int
(paren
op_star
id|apply
)paren
(paren
id|u32
id|sid
comma
r_struct
id|context
op_star
id|context
comma
r_void
op_star
id|args
)paren
comma
r_void
op_star
id|args
)paren
suffix:semicolon
r_void
id|sidtab_map_remove_on_error
c_func
(paren
r_struct
id|sidtab
op_star
id|s
comma
r_int
(paren
op_star
id|apply
)paren
(paren
id|u32
id|sid
comma
r_struct
id|context
op_star
id|context
comma
r_void
op_star
id|args
)paren
comma
r_void
op_star
id|args
)paren
suffix:semicolon
r_int
id|sidtab_context_to_sid
c_func
(paren
r_struct
id|sidtab
op_star
id|s
comma
r_struct
id|context
op_star
id|context
comma
id|u32
op_star
id|sid
)paren
suffix:semicolon
r_void
id|sidtab_hash_eval
c_func
(paren
r_struct
id|sidtab
op_star
id|h
comma
r_char
op_star
id|tag
)paren
suffix:semicolon
r_void
id|sidtab_destroy
c_func
(paren
r_struct
id|sidtab
op_star
id|s
)paren
suffix:semicolon
r_void
id|sidtab_set
c_func
(paren
r_struct
id|sidtab
op_star
id|dst
comma
r_struct
id|sidtab
op_star
id|src
)paren
suffix:semicolon
r_void
id|sidtab_shutdown
c_func
(paren
r_struct
id|sidtab
op_star
id|s
)paren
suffix:semicolon
macro_line|#endif&t;/* _SS_SIDTAB_H_ */
eof
