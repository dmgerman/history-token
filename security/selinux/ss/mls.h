multiline_comment|/*&n; * Multi-level security (MLS) policy operations.&n; *&n; * Author : Stephen Smalley, &lt;sds@epoch.ncsc.mil&gt;&n; */
macro_line|#ifndef _SS_MLS_H_
DECL|macro|_SS_MLS_H_
mdefine_line|#define _SS_MLS_H_
macro_line|#include &quot;context.h&quot;
macro_line|#include &quot;policydb.h&quot;
macro_line|#ifdef CONFIG_SECURITY_SELINUX_MLS
r_void
id|mls_compute_av
c_func
(paren
r_struct
id|context
op_star
id|scontext
comma
r_struct
id|context
op_star
id|tcontext
comma
r_struct
id|class_datum
op_star
id|tclass
comma
id|u32
op_star
id|allowed
)paren
suffix:semicolon
r_int
id|mls_compute_context_len
c_func
(paren
r_struct
id|context
op_star
id|context
)paren
suffix:semicolon
r_int
id|mls_sid_to_context
c_func
(paren
r_struct
id|context
op_star
id|context
comma
r_char
op_star
op_star
id|scontext
)paren
suffix:semicolon
r_int
id|mls_context_isvalid
c_func
(paren
r_struct
id|policydb
op_star
id|p
comma
r_struct
id|context
op_star
id|c
)paren
suffix:semicolon
r_int
id|mls_context_to_sid
c_func
(paren
r_char
id|oldc
comma
r_char
op_star
op_star
id|scontext
comma
r_struct
id|context
op_star
id|context
)paren
suffix:semicolon
r_int
id|mls_convert_context
c_func
(paren
r_struct
id|policydb
op_star
id|oldp
comma
r_struct
id|policydb
op_star
id|newp
comma
r_struct
id|context
op_star
id|context
)paren
suffix:semicolon
r_int
id|mls_compute_sid
c_func
(paren
r_struct
id|context
op_star
id|scontext
comma
r_struct
id|context
op_star
id|tcontext
comma
id|u16
id|tclass
comma
id|u32
id|specified
comma
r_struct
id|context
op_star
id|newcontext
)paren
suffix:semicolon
r_int
id|sens_index
c_func
(paren
r_void
op_star
id|key
comma
r_void
op_star
id|datum
comma
r_void
op_star
id|datap
)paren
suffix:semicolon
r_int
id|cat_index
c_func
(paren
r_void
op_star
id|key
comma
r_void
op_star
id|datum
comma
r_void
op_star
id|datap
)paren
suffix:semicolon
r_int
id|sens_destroy
c_func
(paren
r_void
op_star
id|key
comma
r_void
op_star
id|datum
comma
r_void
op_star
id|p
)paren
suffix:semicolon
r_int
id|cat_destroy
c_func
(paren
r_void
op_star
id|key
comma
r_void
op_star
id|datum
comma
r_void
op_star
id|p
)paren
suffix:semicolon
r_int
id|sens_read
c_func
(paren
r_struct
id|policydb
op_star
id|p
comma
r_struct
id|hashtab
op_star
id|h
comma
r_void
op_star
id|fp
)paren
suffix:semicolon
r_int
id|cat_read
c_func
(paren
r_struct
id|policydb
op_star
id|p
comma
r_struct
id|hashtab
op_star
id|h
comma
r_void
op_star
id|fp
)paren
suffix:semicolon
DECL|macro|mls_for_user_ranges
mdefine_line|#define mls_for_user_ranges(user, usercon) { &bslash;&n;struct mls_range_list *__ranges; &bslash;&n;for (__ranges = user-&gt;ranges; __ranges; __ranges = __ranges-&gt;next) { &bslash;&n;usercon.range = __ranges-&gt;range;
DECL|macro|mls_end_user_ranges
mdefine_line|#define mls_end_user_ranges } }
DECL|macro|mls_symtab_names
mdefine_line|#define mls_symtab_names , &quot;levels&quot;, &quot;categories&quot;
DECL|macro|mls_symtab_sizes
mdefine_line|#define mls_symtab_sizes , 16, 16
DECL|macro|mls_index_f
mdefine_line|#define mls_index_f ,sens_index, cat_index
DECL|macro|mls_destroy_f
mdefine_line|#define mls_destroy_f ,sens_destroy, cat_destroy
DECL|macro|mls_read_f
mdefine_line|#define mls_read_f ,sens_read, cat_read
DECL|macro|mls_write_f
mdefine_line|#define mls_write_f ,sens_write, cat_write
DECL|macro|mls_policydb_index_others
mdefine_line|#define mls_policydb_index_others(p) printk(&quot;, %d levels&quot;, p-&gt;nlevels);
DECL|macro|mls_set_config
mdefine_line|#define mls_set_config(config) config |= POLICYDB_CONFIG_MLS
r_void
id|mls_user_destroy
c_func
(paren
r_struct
id|user_datum
op_star
id|usrdatum
)paren
suffix:semicolon
r_int
id|mls_read_range
c_func
(paren
r_struct
id|context
op_star
id|c
comma
r_void
op_star
id|fp
)paren
suffix:semicolon
r_int
id|mls_read_perm
c_func
(paren
r_struct
id|perm_datum
op_star
id|perdatum
comma
r_void
op_star
id|fp
)paren
suffix:semicolon
r_int
id|mls_read_class
c_func
(paren
r_struct
id|class_datum
op_star
id|cladatum
comma
r_void
op_star
id|fp
)paren
suffix:semicolon
r_int
id|mls_read_user
c_func
(paren
r_struct
id|user_datum
op_star
id|usrdatum
comma
r_void
op_star
id|fp
)paren
suffix:semicolon
r_int
id|mls_read_nlevels
c_func
(paren
r_struct
id|policydb
op_star
id|p
comma
r_void
op_star
id|fp
)paren
suffix:semicolon
r_int
id|mls_read_trusted
c_func
(paren
r_struct
id|policydb
op_star
id|p
comma
r_void
op_star
id|fp
)paren
suffix:semicolon
macro_line|#else
DECL|macro|mls_compute_av
mdefine_line|#define&t;mls_compute_av(scontext, tcontext, tclass_datum, allowed)
DECL|macro|mls_compute_context_len
mdefine_line|#define mls_compute_context_len(context) 0
DECL|macro|mls_sid_to_context
mdefine_line|#define&t;mls_sid_to_context(context, scontextpp)
DECL|macro|mls_context_isvalid
mdefine_line|#define mls_context_isvalid(p, c) 1
DECL|macro|mls_context_to_sid
mdefine_line|#define&t;mls_context_to_sid(oldc, context_str, context) 0
DECL|macro|mls_convert_context
mdefine_line|#define mls_convert_context(oldp, newp, c) 0
DECL|macro|mls_compute_sid
mdefine_line|#define mls_compute_sid(scontext, tcontext, tclass, specified, newcontextp) 0
DECL|macro|mls_for_user_ranges
mdefine_line|#define mls_for_user_ranges(user, usercon)
DECL|macro|mls_end_user_ranges
mdefine_line|#define mls_end_user_ranges
DECL|macro|mls_symtab_names
mdefine_line|#define mls_symtab_names
DECL|macro|mls_symtab_sizes
mdefine_line|#define mls_symtab_sizes
DECL|macro|mls_index_f
mdefine_line|#define mls_index_f
DECL|macro|mls_destroy_f
mdefine_line|#define mls_destroy_f
DECL|macro|mls_read_f
mdefine_line|#define mls_read_f
DECL|macro|mls_write_f
mdefine_line|#define mls_write_f
DECL|macro|mls_policydb_index_others
mdefine_line|#define mls_policydb_index_others(p)
DECL|macro|mls_set_config
mdefine_line|#define mls_set_config(config)
DECL|macro|mls_user_destroy
mdefine_line|#define mls_user_destroy(usrdatum)
DECL|macro|mls_read_range
mdefine_line|#define mls_read_range(c, fp) 0
DECL|macro|mls_read_perm
mdefine_line|#define mls_read_perm(p, fp) 0
DECL|macro|mls_read_class
mdefine_line|#define mls_read_class(c, fp) 0
DECL|macro|mls_read_user
mdefine_line|#define mls_read_user(u, fp) 0
DECL|macro|mls_read_nlevels
mdefine_line|#define mls_read_nlevels(p, fp) 0
DECL|macro|mls_read_trusted
mdefine_line|#define mls_read_trusted(p, fp) 0
macro_line|#endif
macro_line|#endif&t;/* _SS_MLS_H */
eof
