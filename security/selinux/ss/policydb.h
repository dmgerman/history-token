multiline_comment|/*&n; * A policy database (policydb) specifies the&n; * configuration data for the security policy.&n; *&n; * Author : Stephen Smalley, &lt;sds@epoch.ncsc.mil&gt;&n; */
multiline_comment|/* Updated: Frank Mayer &lt;mayerf@tresys.com&gt; and Karl MacMillan &lt;kmacmillan@tresys.com&gt;&n; *&n; * &t;Added conditional policy language extensions&n; *&n; * Copyright (C) 2003 - 2004 Tresys Technology, LLC&n; *&t;This program is free software; you can redistribute it and/or modify&n; *  &t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation, version 2.&n; */
macro_line|#ifndef _SS_POLICYDB_H_
DECL|macro|_SS_POLICYDB_H_
mdefine_line|#define _SS_POLICYDB_H_
macro_line|#include &quot;symtab.h&quot;
macro_line|#include &quot;avtab.h&quot;
macro_line|#include &quot;sidtab.h&quot;
macro_line|#include &quot;context.h&quot;
macro_line|#include &quot;constraint.h&quot;
multiline_comment|/*&n; * A datum type is defined for each kind of symbol&n; * in the configuration data:  individual permissions,&n; * common prefixes for access vectors, classes,&n; * users, roles, types, sensitivities, categories, etc.&n; */
multiline_comment|/* Permission attributes */
DECL|struct|perm_datum
r_struct
id|perm_datum
(brace
DECL|member|value
id|u32
id|value
suffix:semicolon
multiline_comment|/* permission bit + 1 */
macro_line|#ifdef CONFIG_SECURITY_SELINUX_MLS
DECL|macro|MLS_BASE_READ
mdefine_line|#define MLS_BASE_READ    1&t;/* MLS base permission `read&squot; */
DECL|macro|MLS_BASE_WRITE
mdefine_line|#define MLS_BASE_WRITE   2&t;/* MLS base permission `write&squot; */
DECL|macro|MLS_BASE_READBY
mdefine_line|#define MLS_BASE_READBY  4&t;/* MLS base permission `readby&squot; */
DECL|macro|MLS_BASE_WRITEBY
mdefine_line|#define MLS_BASE_WRITEBY 8&t;/* MLS base permission `writeby&squot; */
DECL|member|base_perms
id|u32
id|base_perms
suffix:semicolon
multiline_comment|/* MLS base permission mask */
macro_line|#endif
)brace
suffix:semicolon
multiline_comment|/* Attributes of a common prefix for access vectors */
DECL|struct|common_datum
r_struct
id|common_datum
(brace
DECL|member|value
id|u32
id|value
suffix:semicolon
multiline_comment|/* internal common value */
DECL|member|permissions
r_struct
id|symtab
id|permissions
suffix:semicolon
multiline_comment|/* common permissions */
)brace
suffix:semicolon
multiline_comment|/* Class attributes */
DECL|struct|class_datum
r_struct
id|class_datum
(brace
DECL|member|value
id|u32
id|value
suffix:semicolon
multiline_comment|/* class value */
DECL|member|comkey
r_char
op_star
id|comkey
suffix:semicolon
multiline_comment|/* common name */
DECL|member|comdatum
r_struct
id|common_datum
op_star
id|comdatum
suffix:semicolon
multiline_comment|/* common datum */
DECL|member|permissions
r_struct
id|symtab
id|permissions
suffix:semicolon
multiline_comment|/* class-specific permission symbol table */
DECL|member|constraints
r_struct
id|constraint_node
op_star
id|constraints
suffix:semicolon
multiline_comment|/* constraints on class permissions */
macro_line|#ifdef CONFIG_SECURITY_SELINUX_MLS
DECL|member|mlsperms
r_struct
id|mls_perms
id|mlsperms
suffix:semicolon
multiline_comment|/* MLS base permission masks */
macro_line|#endif
)brace
suffix:semicolon
multiline_comment|/* Role attributes */
DECL|struct|role_datum
r_struct
id|role_datum
(brace
DECL|member|value
id|u32
id|value
suffix:semicolon
multiline_comment|/* internal role value */
DECL|member|dominates
r_struct
id|ebitmap
id|dominates
suffix:semicolon
multiline_comment|/* set of roles dominated by this role */
DECL|member|types
r_struct
id|ebitmap
id|types
suffix:semicolon
multiline_comment|/* set of authorized types for role */
)brace
suffix:semicolon
DECL|struct|role_trans
r_struct
id|role_trans
(brace
DECL|member|role
id|u32
id|role
suffix:semicolon
multiline_comment|/* current role */
DECL|member|type
id|u32
id|type
suffix:semicolon
multiline_comment|/* program executable type */
DECL|member|new_role
id|u32
id|new_role
suffix:semicolon
multiline_comment|/* new role */
DECL|member|next
r_struct
id|role_trans
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|role_allow
r_struct
id|role_allow
(brace
DECL|member|role
id|u32
id|role
suffix:semicolon
multiline_comment|/* current role */
DECL|member|new_role
id|u32
id|new_role
suffix:semicolon
multiline_comment|/* new role */
DECL|member|next
r_struct
id|role_allow
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Type attributes */
DECL|struct|type_datum
r_struct
id|type_datum
(brace
DECL|member|value
id|u32
id|value
suffix:semicolon
multiline_comment|/* internal type value */
DECL|member|primary
r_int
r_char
id|primary
suffix:semicolon
multiline_comment|/* primary name? */
)brace
suffix:semicolon
multiline_comment|/* User attributes */
DECL|struct|user_datum
r_struct
id|user_datum
(brace
DECL|member|value
id|u32
id|value
suffix:semicolon
multiline_comment|/* internal user value */
DECL|member|roles
r_struct
id|ebitmap
id|roles
suffix:semicolon
multiline_comment|/* set of authorized roles for user */
macro_line|#ifdef CONFIG_SECURITY_SELINUX_MLS
DECL|member|ranges
r_struct
id|mls_range_list
op_star
id|ranges
suffix:semicolon
multiline_comment|/* list of authorized MLS ranges for user */
macro_line|#endif
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_SECURITY_SELINUX_MLS
multiline_comment|/* Sensitivity attributes */
DECL|struct|level_datum
r_struct
id|level_datum
(brace
DECL|member|level
r_struct
id|mls_level
op_star
id|level
suffix:semicolon
multiline_comment|/* sensitivity and associated categories */
DECL|member|isalias
r_int
r_char
id|isalias
suffix:semicolon
multiline_comment|/* is this sensitivity an alias for another? */
)brace
suffix:semicolon
multiline_comment|/* Category attributes */
DECL|struct|cat_datum
r_struct
id|cat_datum
(brace
DECL|member|value
id|u32
id|value
suffix:semicolon
multiline_comment|/* internal category bit + 1 */
DECL|member|isalias
r_int
r_char
id|isalias
suffix:semicolon
multiline_comment|/* is this category an alias for another? */
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/* Boolean data type */
DECL|struct|cond_bool_datum
r_struct
id|cond_bool_datum
(brace
DECL|member|value
id|__u32
id|value
suffix:semicolon
multiline_comment|/* internal type value */
DECL|member|state
r_int
id|state
suffix:semicolon
)brace
suffix:semicolon
r_struct
id|cond_node
suffix:semicolon
multiline_comment|/*&n; * The configuration data includes security contexts for&n; * initial SIDs, unlabeled file systems, TCP and UDP port numbers,&n; * network interfaces, and nodes.  This structure stores the&n; * relevant data for one such entry.  Entries of the same kind&n; * (e.g. all initial SIDs) are linked together into a list.&n; */
DECL|struct|ocontext
r_struct
id|ocontext
(brace
r_union
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/* name of initial SID, fs, netif, fstype, path */
r_struct
(brace
DECL|member|protocol
id|u8
id|protocol
suffix:semicolon
DECL|member|low_port
id|u16
id|low_port
suffix:semicolon
DECL|member|high_port
id|u16
id|high_port
suffix:semicolon
DECL|member|port
)brace
id|port
suffix:semicolon
multiline_comment|/* TCP or UDP port information */
r_struct
(brace
DECL|member|addr
id|u32
id|addr
suffix:semicolon
DECL|member|mask
id|u32
id|mask
suffix:semicolon
DECL|member|node
)brace
id|node
suffix:semicolon
multiline_comment|/* node information */
r_struct
(brace
DECL|member|addr
id|u32
id|addr
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|mask
id|u32
id|mask
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|node6
)brace
id|node6
suffix:semicolon
multiline_comment|/* IPv6 node information */
DECL|member|u
)brace
id|u
suffix:semicolon
r_union
(brace
DECL|member|sclass
id|u32
id|sclass
suffix:semicolon
multiline_comment|/* security class for genfs */
DECL|member|behavior
id|u32
id|behavior
suffix:semicolon
multiline_comment|/* labeling behavior for fs_use */
DECL|member|v
)brace
id|v
suffix:semicolon
DECL|member|context
r_struct
id|context
id|context
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* security context(s) */
DECL|member|sid
id|u32
id|sid
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* SID(s) */
DECL|member|next
r_struct
id|ocontext
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|genfs
r_struct
id|genfs
(brace
DECL|member|fstype
r_char
op_star
id|fstype
suffix:semicolon
DECL|member|head
r_struct
id|ocontext
op_star
id|head
suffix:semicolon
DECL|member|next
r_struct
id|genfs
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* symbol table array indices */
DECL|macro|SYM_COMMONS
mdefine_line|#define SYM_COMMONS 0
DECL|macro|SYM_CLASSES
mdefine_line|#define SYM_CLASSES 1
DECL|macro|SYM_ROLES
mdefine_line|#define SYM_ROLES   2
DECL|macro|SYM_TYPES
mdefine_line|#define SYM_TYPES   3
DECL|macro|SYM_USERS
mdefine_line|#define SYM_USERS   4
macro_line|#ifdef CONFIG_SECURITY_SELINUX_MLS
DECL|macro|SYM_LEVELS
mdefine_line|#define SYM_LEVELS  5
DECL|macro|SYM_CATS
mdefine_line|#define SYM_CATS    6
DECL|macro|SYM_BOOLS
mdefine_line|#define SYM_BOOLS   7
DECL|macro|SYM_NUM
mdefine_line|#define SYM_NUM     8
macro_line|#else
DECL|macro|SYM_BOOLS
mdefine_line|#define SYM_BOOLS   5
DECL|macro|SYM_NUM
mdefine_line|#define SYM_NUM     6
macro_line|#endif
multiline_comment|/* object context array indices */
DECL|macro|OCON_ISID
mdefine_line|#define OCON_ISID  0&t;/* initial SIDs */
DECL|macro|OCON_FS
mdefine_line|#define OCON_FS    1&t;/* unlabeled file systems */
DECL|macro|OCON_PORT
mdefine_line|#define OCON_PORT  2&t;/* TCP and UDP port numbers */
DECL|macro|OCON_NETIF
mdefine_line|#define OCON_NETIF 3&t;/* network interfaces */
DECL|macro|OCON_NODE
mdefine_line|#define OCON_NODE  4&t;/* nodes */
DECL|macro|OCON_FSUSE
mdefine_line|#define OCON_FSUSE 5&t;/* fs_use */
DECL|macro|OCON_NODE6
mdefine_line|#define OCON_NODE6 6&t;/* IPv6 nodes */
DECL|macro|OCON_NUM
mdefine_line|#define OCON_NUM   7
multiline_comment|/* The policy database */
DECL|struct|policydb
r_struct
id|policydb
(brace
multiline_comment|/* symbol tables */
DECL|member|symtab
r_struct
id|symtab
id|symtab
(braket
id|SYM_NUM
)braket
suffix:semicolon
DECL|macro|p_commons
mdefine_line|#define p_commons symtab[SYM_COMMONS]
DECL|macro|p_classes
mdefine_line|#define p_classes symtab[SYM_CLASSES]
DECL|macro|p_roles
mdefine_line|#define p_roles symtab[SYM_ROLES]
DECL|macro|p_types
mdefine_line|#define p_types symtab[SYM_TYPES]
DECL|macro|p_users
mdefine_line|#define p_users symtab[SYM_USERS]
DECL|macro|p_levels
mdefine_line|#define p_levels symtab[SYM_LEVELS]
DECL|macro|p_cats
mdefine_line|#define p_cats symtab[SYM_CATS]
DECL|macro|p_bools
mdefine_line|#define p_bools symtab[SYM_BOOLS]
multiline_comment|/* symbol names indexed by (value - 1) */
DECL|member|sym_val_to_name
r_char
op_star
op_star
id|sym_val_to_name
(braket
id|SYM_NUM
)braket
suffix:semicolon
DECL|macro|p_common_val_to_name
mdefine_line|#define p_common_val_to_name sym_val_to_name[SYM_COMMONS]
DECL|macro|p_class_val_to_name
mdefine_line|#define p_class_val_to_name sym_val_to_name[SYM_CLASSES]
DECL|macro|p_role_val_to_name
mdefine_line|#define p_role_val_to_name sym_val_to_name[SYM_ROLES]
DECL|macro|p_type_val_to_name
mdefine_line|#define p_type_val_to_name sym_val_to_name[SYM_TYPES]
DECL|macro|p_user_val_to_name
mdefine_line|#define p_user_val_to_name sym_val_to_name[SYM_USERS]
DECL|macro|p_sens_val_to_name
mdefine_line|#define p_sens_val_to_name sym_val_to_name[SYM_LEVELS]
DECL|macro|p_cat_val_to_name
mdefine_line|#define p_cat_val_to_name sym_val_to_name[SYM_CATS]
DECL|macro|p_bool_val_to_name
mdefine_line|#define p_bool_val_to_name sym_val_to_name[SYM_BOOLS]
multiline_comment|/* class, role, and user attributes indexed by (value - 1) */
DECL|member|class_val_to_struct
r_struct
id|class_datum
op_star
op_star
id|class_val_to_struct
suffix:semicolon
DECL|member|role_val_to_struct
r_struct
id|role_datum
op_star
op_star
id|role_val_to_struct
suffix:semicolon
DECL|member|user_val_to_struct
r_struct
id|user_datum
op_star
op_star
id|user_val_to_struct
suffix:semicolon
multiline_comment|/* type enforcement access vectors and transitions */
DECL|member|te_avtab
r_struct
id|avtab
id|te_avtab
suffix:semicolon
multiline_comment|/* role transitions */
DECL|member|role_tr
r_struct
id|role_trans
op_star
id|role_tr
suffix:semicolon
multiline_comment|/* bools indexed by (value - 1) */
DECL|member|bool_val_to_struct
r_struct
id|cond_bool_datum
op_star
op_star
id|bool_val_to_struct
suffix:semicolon
multiline_comment|/* type enforcement conditional access vectors and transitions */
DECL|member|te_cond_avtab
r_struct
id|avtab
id|te_cond_avtab
suffix:semicolon
multiline_comment|/* linked list indexing te_cond_avtab by conditional */
DECL|member|cond_list
r_struct
id|cond_node
op_star
id|cond_list
suffix:semicolon
multiline_comment|/* role allows */
DECL|member|role_allow
r_struct
id|role_allow
op_star
id|role_allow
suffix:semicolon
multiline_comment|/* security contexts of initial SIDs, unlabeled file systems,&n;&t;   TCP or UDP port numbers, network interfaces and nodes */
DECL|member|ocontexts
r_struct
id|ocontext
op_star
id|ocontexts
(braket
id|OCON_NUM
)braket
suffix:semicolon
multiline_comment|/* security contexts for files in filesystems that cannot support&n;&t;   a persistent label mapping or use another&n;&t;   fixed labeling behavior. */
DECL|member|genfs
r_struct
id|genfs
op_star
id|genfs
suffix:semicolon
macro_line|#ifdef CONFIG_SECURITY_SELINUX_MLS
multiline_comment|/* number of legitimate MLS levels */
DECL|member|nlevels
id|u32
id|nlevels
suffix:semicolon
DECL|member|trustedreaders
r_struct
id|ebitmap
id|trustedreaders
suffix:semicolon
DECL|member|trustedwriters
r_struct
id|ebitmap
id|trustedwriters
suffix:semicolon
DECL|member|trustedobjects
r_struct
id|ebitmap
id|trustedobjects
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
r_extern
r_int
id|policydb_init
c_func
(paren
r_struct
id|policydb
op_star
id|p
)paren
suffix:semicolon
r_extern
r_int
id|policydb_index_classes
c_func
(paren
r_struct
id|policydb
op_star
id|p
)paren
suffix:semicolon
r_extern
r_int
id|policydb_index_others
c_func
(paren
r_struct
id|policydb
op_star
id|p
)paren
suffix:semicolon
r_extern
r_void
id|policydb_destroy
c_func
(paren
r_struct
id|policydb
op_star
id|p
)paren
suffix:semicolon
r_extern
r_int
id|policydb_load_isids
c_func
(paren
r_struct
id|policydb
op_star
id|p
comma
r_struct
id|sidtab
op_star
id|s
)paren
suffix:semicolon
r_extern
r_int
id|policydb_context_isvalid
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
r_extern
r_int
id|policydb_read
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
DECL|macro|PERM_SYMTAB_SIZE
mdefine_line|#define PERM_SYMTAB_SIZE 32
DECL|macro|POLICYDB_CONFIG_MLS
mdefine_line|#define POLICYDB_CONFIG_MLS    1
DECL|macro|OBJECT_R
mdefine_line|#define OBJECT_R &quot;object_r&quot;
DECL|macro|OBJECT_R_VAL
mdefine_line|#define OBJECT_R_VAL 1
DECL|macro|POLICYDB_MAGIC
mdefine_line|#define POLICYDB_MAGIC SELINUX_MAGIC
DECL|macro|POLICYDB_STRING
mdefine_line|#define POLICYDB_STRING &quot;SE Linux&quot;
DECL|struct|policy_file
r_struct
id|policy_file
(brace
DECL|member|data
r_char
op_star
id|data
suffix:semicolon
DECL|member|len
r_int
id|len
suffix:semicolon
)brace
suffix:semicolon
DECL|function|next_entry
r_static
r_inline
r_int
id|next_entry
c_func
(paren
r_void
op_star
id|buf
comma
r_struct
id|policy_file
op_star
id|fp
comma
r_int
id|bytes
)paren
(brace
r_if
c_cond
(paren
id|bytes
OG
id|fp-&gt;len
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|memcpy
c_func
(paren
id|buf
comma
id|fp-&gt;data
comma
id|bytes
)paren
suffix:semicolon
id|fp-&gt;data
op_add_assign
id|bytes
suffix:semicolon
id|fp-&gt;len
op_sub_assign
id|bytes
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif&t;/* _SS_POLICYDB_H_ */
eof
