macro_line|#ifndef _NAMESPACE_H_
DECL|macro|_NAMESPACE_H_
mdefine_line|#define _NAMESPACE_H_
macro_line|#ifdef __KERNEL__
DECL|struct|namespace
r_struct
r_namespace
(brace
DECL|member|count
id|atomic_t
id|count
suffix:semicolon
DECL|member|root
r_struct
id|vfsmount
op_star
id|root
suffix:semicolon
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|sem
r_struct
id|rw_semaphore
id|sem
suffix:semicolon
)brace
suffix:semicolon
DECL|function|put_namespace
r_static
r_inline
r_void
id|put_namespace
c_func
(paren
r_struct
r_namespace
op_star
r_namespace
)paren
(brace
r_if
c_cond
(paren
id|atomic_dec_and_test
c_func
(paren
op_amp
r_namespace
op_member_access_from_pointer
id|count
)paren
)paren
(brace
id|down_write
c_func
(paren
op_amp
r_namespace
op_member_access_from_pointer
id|sem
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|dcache_lock
)paren
suffix:semicolon
id|umount_tree
c_func
(paren
r_namespace
op_member_access_from_pointer
id|root
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|dcache_lock
)paren
suffix:semicolon
id|up_write
c_func
(paren
op_amp
r_namespace
op_member_access_from_pointer
id|sem
)paren
suffix:semicolon
id|kfree
c_func
(paren
r_namespace
)paren
suffix:semicolon
)brace
)brace
DECL|function|exit_namespace
r_static
r_inline
r_void
id|exit_namespace
c_func
(paren
r_struct
id|task_struct
op_star
id|p
)paren
(brace
r_struct
r_namespace
op_star
r_namespace
op_assign
id|p
op_member_access_from_pointer
r_namespace
suffix:semicolon
r_if
c_cond
(paren
r_namespace
)paren
(brace
id|task_lock
c_func
(paren
id|p
)paren
suffix:semicolon
id|p
op_member_access_from_pointer
r_namespace
op_assign
l_int|NULL
suffix:semicolon
id|task_unlock
c_func
(paren
id|p
)paren
suffix:semicolon
id|put_namespace
c_func
(paren
r_namespace
)paren
suffix:semicolon
)brace
)brace
r_extern
r_int
id|copy_namespace
c_func
(paren
r_int
comma
r_struct
id|task_struct
op_star
)paren
suffix:semicolon
DECL|function|get_namespace
r_static
r_inline
r_void
id|get_namespace
c_func
(paren
r_struct
r_namespace
op_star
r_namespace
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
r_namespace
op_member_access_from_pointer
id|count
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#endif
eof
