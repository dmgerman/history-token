multiline_comment|/* key.h: authentication token and access key management&n; *&n; * Copyright (C) 2004 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; *&n; *&n; * See Documentation/keys.txt for information on keys/keyrings.&n; */
macro_line|#ifndef _LINUX_KEY_H
DECL|macro|_LINUX_KEY_H
mdefine_line|#define _LINUX_KEY_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/rbtree.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#ifdef __KERNEL__
multiline_comment|/* key handle serial number */
DECL|typedef|key_serial_t
r_typedef
r_int32
id|key_serial_t
suffix:semicolon
multiline_comment|/* key handle permissions mask */
DECL|typedef|key_perm_t
r_typedef
r_uint32
id|key_perm_t
suffix:semicolon
r_struct
id|key
suffix:semicolon
macro_line|#ifdef CONFIG_KEYS
DECL|macro|KEY_DEBUGGING
macro_line|#undef KEY_DEBUGGING
DECL|macro|KEY_USR_VIEW
mdefine_line|#define KEY_USR_VIEW&t;0x00010000&t;/* user can view a key&squot;s attributes */
DECL|macro|KEY_USR_READ
mdefine_line|#define KEY_USR_READ&t;0x00020000&t;/* user can read key payload / view keyring */
DECL|macro|KEY_USR_WRITE
mdefine_line|#define KEY_USR_WRITE&t;0x00040000&t;/* user can update key payload / add link to keyring */
DECL|macro|KEY_USR_SEARCH
mdefine_line|#define KEY_USR_SEARCH&t;0x00080000&t;/* user can find a key in search / search a keyring */
DECL|macro|KEY_USR_LINK
mdefine_line|#define KEY_USR_LINK&t;0x00100000&t;/* user can create a link to a key/keyring */
DECL|macro|KEY_USR_ALL
mdefine_line|#define KEY_USR_ALL&t;0x001f0000
DECL|macro|KEY_GRP_VIEW
mdefine_line|#define KEY_GRP_VIEW&t;0x00000100&t;/* group permissions... */
DECL|macro|KEY_GRP_READ
mdefine_line|#define KEY_GRP_READ&t;0x00000200
DECL|macro|KEY_GRP_WRITE
mdefine_line|#define KEY_GRP_WRITE&t;0x00000400
DECL|macro|KEY_GRP_SEARCH
mdefine_line|#define KEY_GRP_SEARCH&t;0x00000800
DECL|macro|KEY_GRP_LINK
mdefine_line|#define KEY_GRP_LINK&t;0x00001000
DECL|macro|KEY_GRP_ALL
mdefine_line|#define KEY_GRP_ALL&t;0x00001f00
DECL|macro|KEY_OTH_VIEW
mdefine_line|#define KEY_OTH_VIEW&t;0x00000001&t;/* third party permissions... */
DECL|macro|KEY_OTH_READ
mdefine_line|#define KEY_OTH_READ&t;0x00000002
DECL|macro|KEY_OTH_WRITE
mdefine_line|#define KEY_OTH_WRITE&t;0x00000004
DECL|macro|KEY_OTH_SEARCH
mdefine_line|#define KEY_OTH_SEARCH&t;0x00000008
DECL|macro|KEY_OTH_LINK
mdefine_line|#define KEY_OTH_LINK&t;0x00000010
DECL|macro|KEY_OTH_ALL
mdefine_line|#define KEY_OTH_ALL&t;0x0000001f
r_struct
id|seq_file
suffix:semicolon
r_struct
id|user_struct
suffix:semicolon
r_struct
id|signal_struct
suffix:semicolon
r_struct
id|key_type
suffix:semicolon
r_struct
id|key_owner
suffix:semicolon
r_struct
id|keyring_list
suffix:semicolon
r_struct
id|keyring_name
suffix:semicolon
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * authentication token / access credential / keyring&n; * - types of key include:&n; *   - keyrings&n; *   - disk encryption IDs&n; *   - Kerberos TGTs and tickets&n; */
DECL|struct|key
r_struct
id|key
(brace
DECL|member|usage
id|atomic_t
id|usage
suffix:semicolon
multiline_comment|/* number of references */
DECL|member|serial
id|key_serial_t
id|serial
suffix:semicolon
multiline_comment|/* key serial number */
DECL|member|serial_node
r_struct
id|rb_node
id|serial_node
suffix:semicolon
DECL|member|type
r_struct
id|key_type
op_star
id|type
suffix:semicolon
multiline_comment|/* type of key */
DECL|member|lock
id|rwlock_t
id|lock
suffix:semicolon
multiline_comment|/* examination vs change lock */
DECL|member|sem
r_struct
id|rw_semaphore
id|sem
suffix:semicolon
multiline_comment|/* change vs change sem */
DECL|member|user
r_struct
id|key_user
op_star
id|user
suffix:semicolon
multiline_comment|/* owner of this key */
DECL|member|expiry
id|time_t
id|expiry
suffix:semicolon
multiline_comment|/* time at which key expires (or 0) */
DECL|member|uid
id|uid_t
id|uid
suffix:semicolon
DECL|member|gid
id|gid_t
id|gid
suffix:semicolon
DECL|member|perm
id|key_perm_t
id|perm
suffix:semicolon
multiline_comment|/* access permissions */
DECL|member|quotalen
r_int
r_int
id|quotalen
suffix:semicolon
multiline_comment|/* length added to quota */
DECL|member|datalen
r_int
r_int
id|datalen
suffix:semicolon
multiline_comment|/* payload data length */
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* status flags (change with lock writelocked) */
DECL|macro|KEY_FLAG_INSTANTIATED
mdefine_line|#define KEY_FLAG_INSTANTIATED&t;0x00000001&t;/* set if key has been instantiated */
DECL|macro|KEY_FLAG_DEAD
mdefine_line|#define KEY_FLAG_DEAD&t;&t;0x00000002&t;/* set if key type has been deleted */
DECL|macro|KEY_FLAG_REVOKED
mdefine_line|#define KEY_FLAG_REVOKED&t;0x00000004&t;/* set if key had been revoked */
DECL|macro|KEY_FLAG_IN_QUOTA
mdefine_line|#define KEY_FLAG_IN_QUOTA&t;0x00000008&t;/* set if key consumes quota */
DECL|macro|KEY_FLAG_USER_CONSTRUCT
mdefine_line|#define KEY_FLAG_USER_CONSTRUCT&t;0x00000010&t;/* set if key is being constructed in userspace */
DECL|macro|KEY_FLAG_NEGATIVE
mdefine_line|#define KEY_FLAG_NEGATIVE&t;0x00000020&t;/* set if key is negative */
macro_line|#ifdef KEY_DEBUGGING
DECL|member|magic
r_int
id|magic
suffix:semicolon
DECL|macro|KEY_DEBUG_MAGIC
mdefine_line|#define KEY_DEBUG_MAGIC&t;&t;0x18273645u
DECL|macro|KEY_DEBUG_MAGIC_X
mdefine_line|#define KEY_DEBUG_MAGIC_X&t;0xf8e9dacbu
macro_line|#endif
multiline_comment|/* the description string&n;&t; * - this is used to match a key against search criteria&n;&t; * - this should be a printable string&n;&t; * - eg: for krb5 AFS, this might be &quot;afs@REDHAT.COM&quot;&n;&t; */
DECL|member|description
r_char
op_star
id|description
suffix:semicolon
multiline_comment|/* type specific data&n;&t; * - this is used by the keyring type to index the name&n;&t; */
r_union
(brace
DECL|member|link
r_struct
id|list_head
id|link
suffix:semicolon
DECL|member|type_data
)brace
id|type_data
suffix:semicolon
multiline_comment|/* key data&n;&t; * - this is used to hold the data actually used in cryptography or&n;&t; *   whatever&n;&t; */
r_union
(brace
DECL|member|value
r_int
r_int
id|value
suffix:semicolon
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
DECL|member|subscriptions
r_struct
id|keyring_list
op_star
id|subscriptions
suffix:semicolon
DECL|member|payload
)brace
id|payload
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * kernel managed key type definition&n; */
DECL|struct|key_type
r_struct
id|key_type
(brace
multiline_comment|/* name of the type */
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/* default payload length for quota precalculation (optional)&n;&t; * - this can be used instead of calling key_payload_reserve(), that&n;&t; *   function only needs to be called if the real datalen is different&n;&t; */
DECL|member|def_datalen
r_int
id|def_datalen
suffix:semicolon
multiline_comment|/* instantiate a key of this type&n;&t; * - this method should call key_payload_reserve() to determine if the&n;&t; *   user&squot;s quota will hold the payload&n;&t; */
DECL|member|instantiate
r_int
(paren
op_star
id|instantiate
)paren
(paren
r_struct
id|key
op_star
id|key
comma
r_const
r_void
op_star
id|data
comma
r_int
id|datalen
)paren
suffix:semicolon
multiline_comment|/* duplicate a key of this type (optional)&n;&t; * - the source key will be locked against change&n;&t; * - the new description will be attached&n;&t; * - the quota will have been adjusted automatically from&n;&t; *   source-&gt;quotalen&n;&t; */
DECL|member|duplicate
r_int
(paren
op_star
id|duplicate
)paren
(paren
r_struct
id|key
op_star
id|key
comma
r_const
r_struct
id|key
op_star
id|source
)paren
suffix:semicolon
multiline_comment|/* update a key of this type (optional)&n;&t; * - this method should call key_payload_reserve() to recalculate the&n;&t; *   quota consumption&n;&t; * - the key must be locked against read when modifying&n;&t; */
DECL|member|update
r_int
(paren
op_star
id|update
)paren
(paren
r_struct
id|key
op_star
id|key
comma
r_const
r_void
op_star
id|data
comma
r_int
id|datalen
)paren
suffix:semicolon
multiline_comment|/* match a key against a description */
DECL|member|match
r_int
(paren
op_star
id|match
)paren
(paren
r_const
r_struct
id|key
op_star
id|key
comma
r_const
r_void
op_star
id|desc
)paren
suffix:semicolon
multiline_comment|/* clear the data from a key (optional) */
DECL|member|destroy
r_void
(paren
op_star
id|destroy
)paren
(paren
r_struct
id|key
op_star
id|key
)paren
suffix:semicolon
multiline_comment|/* describe a key */
DECL|member|describe
r_void
(paren
op_star
id|describe
)paren
(paren
r_const
r_struct
id|key
op_star
id|key
comma
r_struct
id|seq_file
op_star
id|p
)paren
suffix:semicolon
multiline_comment|/* read a key&squot;s data (optional)&n;&t; * - permission checks will be done by the caller&n;&t; * - the key&squot;s semaphore will be readlocked by the caller&n;&t; * - should return the amount of data that could be read, no matter how&n;&t; *   much is copied into the buffer&n;&t; * - shouldn&squot;t do the copy if the buffer is NULL&n;&t; */
DECL|member|read
r_int
(paren
op_star
id|read
)paren
(paren
r_const
r_struct
id|key
op_star
id|key
comma
r_char
id|__user
op_star
id|buffer
comma
r_int
id|buflen
)paren
suffix:semicolon
multiline_comment|/* internal fields */
DECL|member|link
r_struct
id|list_head
id|link
suffix:semicolon
multiline_comment|/* link in types list */
)brace
suffix:semicolon
r_extern
r_struct
id|key_type
id|key_type_keyring
suffix:semicolon
r_extern
r_int
id|register_key_type
c_func
(paren
r_struct
id|key_type
op_star
id|ktype
)paren
suffix:semicolon
r_extern
r_void
id|unregister_key_type
c_func
(paren
r_struct
id|key_type
op_star
id|ktype
)paren
suffix:semicolon
r_extern
r_struct
id|key
op_star
id|key_alloc
c_func
(paren
r_struct
id|key_type
op_star
id|type
comma
r_const
r_char
op_star
id|desc
comma
id|uid_t
id|uid
comma
id|gid_t
id|gid
comma
id|key_perm_t
id|perm
comma
r_int
id|not_in_quota
)paren
suffix:semicolon
r_extern
r_int
id|key_payload_reserve
c_func
(paren
r_struct
id|key
op_star
id|key
comma
r_int
id|datalen
)paren
suffix:semicolon
r_extern
r_int
id|key_instantiate_and_link
c_func
(paren
r_struct
id|key
op_star
id|key
comma
r_const
r_void
op_star
id|data
comma
r_int
id|datalen
comma
r_struct
id|key
op_star
id|keyring
)paren
suffix:semicolon
r_extern
r_int
id|key_negate_and_link
c_func
(paren
r_struct
id|key
op_star
id|key
comma
r_int
id|timeout
comma
r_struct
id|key
op_star
id|keyring
)paren
suffix:semicolon
r_extern
r_void
id|key_revoke
c_func
(paren
r_struct
id|key
op_star
id|key
)paren
suffix:semicolon
r_extern
r_void
id|key_put
c_func
(paren
r_struct
id|key
op_star
id|key
)paren
suffix:semicolon
DECL|function|key_get
r_static
r_inline
r_struct
id|key
op_star
id|key_get
c_func
(paren
r_struct
id|key
op_star
id|key
)paren
(brace
r_if
c_cond
(paren
id|key
)paren
id|atomic_inc
c_func
(paren
op_amp
id|key-&gt;usage
)paren
suffix:semicolon
r_return
id|key
suffix:semicolon
)brace
r_extern
r_struct
id|key
op_star
id|request_key
c_func
(paren
r_struct
id|key_type
op_star
id|type
comma
r_const
r_char
op_star
id|description
comma
r_const
r_char
op_star
id|callout_info
)paren
suffix:semicolon
r_extern
r_int
id|key_validate
c_func
(paren
r_struct
id|key
op_star
id|key
)paren
suffix:semicolon
r_extern
r_struct
id|key
op_star
id|key_create_or_update
c_func
(paren
r_struct
id|key
op_star
id|keyring
comma
r_const
r_char
op_star
id|type
comma
r_const
r_char
op_star
id|description
comma
r_const
r_void
op_star
id|payload
comma
r_int
id|plen
comma
r_int
id|not_in_quota
)paren
suffix:semicolon
r_extern
r_int
id|key_update
c_func
(paren
r_struct
id|key
op_star
id|key
comma
r_const
r_void
op_star
id|payload
comma
r_int
id|plen
)paren
suffix:semicolon
r_extern
r_int
id|key_link
c_func
(paren
r_struct
id|key
op_star
id|keyring
comma
r_struct
id|key
op_star
id|key
)paren
suffix:semicolon
r_extern
r_int
id|key_unlink
c_func
(paren
r_struct
id|key
op_star
id|keyring
comma
r_struct
id|key
op_star
id|key
)paren
suffix:semicolon
r_extern
r_struct
id|key
op_star
id|keyring_alloc
c_func
(paren
r_const
r_char
op_star
id|description
comma
id|uid_t
id|uid
comma
id|gid_t
id|gid
comma
r_int
id|not_in_quota
comma
r_struct
id|key
op_star
id|dest
)paren
suffix:semicolon
r_extern
r_int
id|keyring_clear
c_func
(paren
r_struct
id|key
op_star
id|keyring
)paren
suffix:semicolon
r_extern
r_struct
id|key
op_star
id|keyring_search
c_func
(paren
r_struct
id|key
op_star
id|keyring
comma
r_struct
id|key_type
op_star
id|type
comma
r_const
r_char
op_star
id|description
)paren
suffix:semicolon
r_extern
r_struct
id|key
op_star
id|search_process_keyrings
c_func
(paren
r_struct
id|key_type
op_star
id|type
comma
r_const
r_char
op_star
id|description
)paren
suffix:semicolon
r_extern
r_int
id|keyring_add_key
c_func
(paren
r_struct
id|key
op_star
id|keyring
comma
r_struct
id|key
op_star
id|key
)paren
suffix:semicolon
r_extern
r_struct
id|key
op_star
id|key_lookup
c_func
(paren
id|key_serial_t
id|id
)paren
suffix:semicolon
DECL|macro|key_serial
mdefine_line|#define key_serial(key) ((key) ? (key)-&gt;serial : 0)
multiline_comment|/*&n; * the userspace interface&n; */
r_extern
r_struct
id|key
id|root_user_keyring
comma
id|root_session_keyring
suffix:semicolon
r_extern
r_int
id|alloc_uid_keyring
c_func
(paren
r_struct
id|user_struct
op_star
id|user
)paren
suffix:semicolon
r_extern
r_void
id|switch_uid_keyring
c_func
(paren
r_struct
id|user_struct
op_star
id|new_user
)paren
suffix:semicolon
r_extern
r_int
id|copy_keys
c_func
(paren
r_int
r_int
id|clone_flags
comma
r_struct
id|task_struct
op_star
id|tsk
)paren
suffix:semicolon
r_extern
r_int
id|copy_thread_group_keys
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
)paren
suffix:semicolon
r_extern
r_void
id|exit_keys
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
)paren
suffix:semicolon
r_extern
r_void
id|exit_thread_group_keys
c_func
(paren
r_struct
id|signal_struct
op_star
id|tg
)paren
suffix:semicolon
r_extern
r_int
id|suid_keys
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
)paren
suffix:semicolon
r_extern
r_int
id|exec_keys
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
)paren
suffix:semicolon
r_extern
r_void
id|key_fsuid_changed
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
)paren
suffix:semicolon
r_extern
r_void
id|key_fsgid_changed
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
)paren
suffix:semicolon
r_extern
r_void
id|key_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#else /* CONFIG_KEYS */
DECL|macro|key_validate
mdefine_line|#define key_validate(k)&t;&t;&t;0
DECL|macro|key_serial
mdefine_line|#define key_serial(k)&t;&t;&t;0
DECL|macro|key_get
mdefine_line|#define key_get(k) &t;&t;&t;NULL
DECL|macro|key_put
mdefine_line|#define key_put(k)&t;&t;&t;do { } while(0)
DECL|macro|alloc_uid_keyring
mdefine_line|#define alloc_uid_keyring(u)&t;&t;0
DECL|macro|switch_uid_keyring
mdefine_line|#define switch_uid_keyring(u)&t;&t;do { } while(0)
DECL|macro|copy_keys
mdefine_line|#define copy_keys(f,t)&t;&t;&t;0
DECL|macro|copy_thread_group_keys
mdefine_line|#define copy_thread_group_keys(t)&t;0
DECL|macro|exit_keys
mdefine_line|#define exit_keys(t)&t;&t;&t;do { } while(0)
DECL|macro|exit_thread_group_keys
mdefine_line|#define exit_thread_group_keys(tg)&t;do { } while(0)
DECL|macro|suid_keys
mdefine_line|#define suid_keys(t)&t;&t;&t;do { } while(0)
DECL|macro|exec_keys
mdefine_line|#define exec_keys(t)&t;&t;&t;do { } while(0)
DECL|macro|key_fsuid_changed
mdefine_line|#define key_fsuid_changed(t)&t;&t;do { } while(0)
DECL|macro|key_fsgid_changed
mdefine_line|#define key_fsgid_changed(t)&t;&t;do { } while(0)
DECL|macro|key_init
mdefine_line|#define key_init()&t;&t;&t;do { } while(0)
macro_line|#endif /* CONFIG_KEYS */
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _LINUX_KEY_H */
eof
