multiline_comment|/*&n; * An access vector table (avtab) is a hash table&n; * of access vectors and transition types indexed&n; * by a type pair and a class.  An access vector&n; * table is used to represent the type enforcement&n; * tables.&n; *&n; *  Author : Stephen Smalley, &lt;sds@epoch.ncsc.mil&gt;&n; */
multiline_comment|/* Updated: Frank Mayer &lt;mayerf@tresys.com&gt; and Karl MacMillan &lt;kmacmillan@tresys.com&gt;&n; *&n; * &t;Added conditional policy language extensions&n; *&n; * Copyright (C) 2003 Tresys Technology, LLC&n; *&t;This program is free software; you can redistribute it and/or modify&n; *  &t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation, version 2.&n; */
macro_line|#ifndef _SS_AVTAB_H_
DECL|macro|_SS_AVTAB_H_
mdefine_line|#define _SS_AVTAB_H_
DECL|struct|avtab_key
r_struct
id|avtab_key
(brace
DECL|member|source_type
id|u32
id|source_type
suffix:semicolon
multiline_comment|/* source type */
DECL|member|target_type
id|u32
id|target_type
suffix:semicolon
multiline_comment|/* target type */
DECL|member|target_class
id|u32
id|target_class
suffix:semicolon
multiline_comment|/* target object class */
)brace
suffix:semicolon
DECL|struct|avtab_datum
r_struct
id|avtab_datum
(brace
DECL|macro|AVTAB_ALLOWED
mdefine_line|#define AVTAB_ALLOWED     1
DECL|macro|AVTAB_AUDITALLOW
mdefine_line|#define AVTAB_AUDITALLOW  2
DECL|macro|AVTAB_AUDITDENY
mdefine_line|#define AVTAB_AUDITDENY   4
DECL|macro|AVTAB_AV
mdefine_line|#define AVTAB_AV         (AVTAB_ALLOWED | AVTAB_AUDITALLOW | AVTAB_AUDITDENY)
DECL|macro|AVTAB_TRANSITION
mdefine_line|#define AVTAB_TRANSITION 16
DECL|macro|AVTAB_MEMBER
mdefine_line|#define AVTAB_MEMBER     32
DECL|macro|AVTAB_CHANGE
mdefine_line|#define AVTAB_CHANGE     64
DECL|macro|AVTAB_TYPE
mdefine_line|#define AVTAB_TYPE       (AVTAB_TRANSITION | AVTAB_MEMBER | AVTAB_CHANGE)
DECL|macro|AVTAB_ENABLED
mdefine_line|#define AVTAB_ENABLED    0x80000000 /* reserved for used in cond_avtab */
DECL|member|specified
id|u32
id|specified
suffix:semicolon
multiline_comment|/* what fields are specified */
DECL|member|data
id|u32
id|data
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* access vectors or types */
DECL|macro|avtab_allowed
mdefine_line|#define avtab_allowed(x) (x)-&gt;data[0]
DECL|macro|avtab_auditdeny
mdefine_line|#define avtab_auditdeny(x) (x)-&gt;data[1]
DECL|macro|avtab_auditallow
mdefine_line|#define avtab_auditallow(x) (x)-&gt;data[2]
DECL|macro|avtab_transition
mdefine_line|#define avtab_transition(x) (x)-&gt;data[0]
DECL|macro|avtab_change
mdefine_line|#define avtab_change(x) (x)-&gt;data[1]
DECL|macro|avtab_member
mdefine_line|#define avtab_member(x) (x)-&gt;data[2]
)brace
suffix:semicolon
DECL|struct|avtab_node
r_struct
id|avtab_node
(brace
DECL|member|key
r_struct
id|avtab_key
id|key
suffix:semicolon
DECL|member|datum
r_struct
id|avtab_datum
id|datum
suffix:semicolon
DECL|member|next
r_struct
id|avtab_node
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|avtab
r_struct
id|avtab
(brace
DECL|member|htable
r_struct
id|avtab_node
op_star
op_star
id|htable
suffix:semicolon
DECL|member|nel
id|u32
id|nel
suffix:semicolon
multiline_comment|/* number of elements */
)brace
suffix:semicolon
r_int
id|avtab_init
c_func
(paren
r_struct
id|avtab
op_star
)paren
suffix:semicolon
r_struct
id|avtab_datum
op_star
id|avtab_search
c_func
(paren
r_struct
id|avtab
op_star
id|h
comma
r_struct
id|avtab_key
op_star
id|k
comma
r_int
id|specified
)paren
suffix:semicolon
r_void
id|avtab_destroy
c_func
(paren
r_struct
id|avtab
op_star
id|h
)paren
suffix:semicolon
r_void
id|avtab_hash_eval
c_func
(paren
r_struct
id|avtab
op_star
id|h
comma
r_char
op_star
id|tag
)paren
suffix:semicolon
r_int
id|avtab_read_item
c_func
(paren
r_void
op_star
id|fp
comma
r_struct
id|avtab_datum
op_star
id|avdatum
comma
r_struct
id|avtab_key
op_star
id|avkey
)paren
suffix:semicolon
r_int
id|avtab_read
c_func
(paren
r_struct
id|avtab
op_star
id|a
comma
r_void
op_star
id|fp
comma
id|u32
id|config
)paren
suffix:semicolon
r_struct
id|avtab_node
op_star
id|avtab_insert_nonunique
c_func
(paren
r_struct
id|avtab
op_star
id|h
comma
r_struct
id|avtab_key
op_star
id|key
comma
r_struct
id|avtab_datum
op_star
id|datum
)paren
suffix:semicolon
r_struct
id|avtab_node
op_star
id|avtab_search_node
c_func
(paren
r_struct
id|avtab
op_star
id|h
comma
r_struct
id|avtab_key
op_star
id|key
comma
r_int
id|specified
)paren
suffix:semicolon
r_struct
id|avtab_node
op_star
id|avtab_search_node_next
c_func
(paren
r_struct
id|avtab_node
op_star
id|node
comma
r_int
id|specified
)paren
suffix:semicolon
r_void
id|avtab_cache_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|avtab_cache_destroy
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|AVTAB_HASH_BITS
mdefine_line|#define AVTAB_HASH_BITS 15
DECL|macro|AVTAB_HASH_BUCKETS
mdefine_line|#define AVTAB_HASH_BUCKETS (1 &lt;&lt; AVTAB_HASH_BITS)
DECL|macro|AVTAB_HASH_MASK
mdefine_line|#define AVTAB_HASH_MASK (AVTAB_HASH_BUCKETS-1)
DECL|macro|AVTAB_SIZE
mdefine_line|#define AVTAB_SIZE AVTAB_HASH_BUCKETS
macro_line|#endif&t;/* _SS_AVTAB_H_ */
eof
