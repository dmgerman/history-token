multiline_comment|/*&n; *  linux/fs/readdir.c&n; *&n; *  Copyright (C) 1995  Linus Torvalds&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|function|vfs_readdir
r_int
id|vfs_readdir
c_func
(paren
r_struct
id|file
op_star
id|file
comma
id|filldir_t
id|filler
comma
r_void
op_star
id|buf
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|file-&gt;f_dentry-&gt;d_inode
suffix:semicolon
r_int
id|res
op_assign
op_minus
id|ENOTDIR
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|file-&gt;f_op
op_logical_or
op_logical_neg
id|file-&gt;f_op-&gt;readdir
)paren
r_goto
id|out
suffix:semicolon
id|down
c_func
(paren
op_amp
id|inode-&gt;i_sem
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|inode-&gt;i_zombie
)paren
suffix:semicolon
id|res
op_assign
op_minus
id|ENOENT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IS_DEADDIR
c_func
(paren
id|inode
)paren
)paren
(brace
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|res
op_assign
id|file-&gt;f_op
op_member_access_from_pointer
id|readdir
c_func
(paren
id|file
comma
id|buf
comma
id|filler
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|inode-&gt;i_zombie
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|inode-&gt;i_sem
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|res
suffix:semicolon
)brace
multiline_comment|/*&n; * Directory is locked and all positive dentries in it are safe, since&n; * for ramfs-type trees they can&squot;t go away without unlink() or rmdir(),&n; * both impossible due to the lock on directory.&n; */
DECL|function|dcache_readdir
r_int
id|dcache_readdir
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_void
op_star
id|dirent
comma
id|filldir_t
id|filldir
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|dentry
op_star
id|dentry
op_assign
id|filp-&gt;f_dentry
suffix:semicolon
id|i
op_assign
id|filp-&gt;f_pos
suffix:semicolon
r_switch
c_cond
(paren
id|i
)paren
(brace
r_case
l_int|0
suffix:colon
r_if
c_cond
(paren
id|filldir
c_func
(paren
id|dirent
comma
l_string|&quot;.&quot;
comma
l_int|1
comma
id|i
comma
id|dentry-&gt;d_inode-&gt;i_ino
comma
id|DT_DIR
)paren
OL
l_int|0
)paren
r_break
suffix:semicolon
id|i
op_increment
suffix:semicolon
id|filp-&gt;f_pos
op_increment
suffix:semicolon
multiline_comment|/* fallthrough */
r_case
l_int|1
suffix:colon
r_if
c_cond
(paren
id|filldir
c_func
(paren
id|dirent
comma
l_string|&quot;..&quot;
comma
l_int|2
comma
id|i
comma
id|dentry-&gt;d_parent-&gt;d_inode-&gt;i_ino
comma
id|DT_DIR
)paren
OL
l_int|0
)paren
r_break
suffix:semicolon
id|i
op_increment
suffix:semicolon
id|filp-&gt;f_pos
op_increment
suffix:semicolon
multiline_comment|/* fallthrough */
r_default
suffix:colon
(brace
)brace
(brace
r_struct
id|list_head
op_star
id|list
suffix:semicolon
r_int
id|j
op_assign
id|i
op_minus
l_int|2
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|dcache_lock
)paren
suffix:semicolon
id|list
op_assign
id|dentry-&gt;d_subdirs.next
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
id|list
op_eq
op_amp
id|dentry-&gt;d_subdirs
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|dcache_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|j
)paren
r_break
suffix:semicolon
id|j
op_decrement
suffix:semicolon
id|list
op_assign
id|list-&gt;next
suffix:semicolon
)brace
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_struct
id|dentry
op_star
id|de
op_assign
id|list_entry
c_func
(paren
id|list
comma
r_struct
id|dentry
comma
id|d_child
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|de-&gt;d_hash
)paren
op_logical_and
id|de-&gt;d_inode
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|dcache_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|filldir
c_func
(paren
id|dirent
comma
id|de-&gt;d_name.name
comma
id|de-&gt;d_name.len
comma
id|filp-&gt;f_pos
comma
id|de-&gt;d_inode-&gt;i_ino
comma
id|DT_UNKNOWN
)paren
OL
l_int|0
)paren
r_break
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|dcache_lock
)paren
suffix:semicolon
)brace
id|filp-&gt;f_pos
op_increment
suffix:semicolon
id|list
op_assign
id|list-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|list
op_ne
op_amp
id|dentry-&gt;d_subdirs
)paren
r_continue
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|dcache_lock
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Traditional linux readdir() handling..&n; *&n; * &quot;count=1&quot; is a special case, meaning that the buffer is one&n; * dirent-structure in size and that the code can&squot;t handle more&n; * anyway. Thus the special &quot;fillonedir()&quot; function for that&n; * case (the low-level handlers don&squot;t need to care about this).&n; */
DECL|macro|NAME_OFFSET
mdefine_line|#define NAME_OFFSET(de) ((int) ((de)-&gt;d_name - (char *) (de)))
DECL|macro|ROUND_UP
mdefine_line|#define ROUND_UP(x) (((x)+sizeof(long)-1) &amp; ~(sizeof(long)-1))
macro_line|#ifndef __ia64__
DECL|struct|old_linux_dirent
r_struct
id|old_linux_dirent
(brace
DECL|member|d_ino
r_int
r_int
id|d_ino
suffix:semicolon
DECL|member|d_offset
r_int
r_int
id|d_offset
suffix:semicolon
DECL|member|d_namlen
r_int
r_int
id|d_namlen
suffix:semicolon
DECL|member|d_name
r_char
id|d_name
(braket
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|readdir_callback
r_struct
id|readdir_callback
(brace
DECL|member|dirent
r_struct
id|old_linux_dirent
op_star
id|dirent
suffix:semicolon
DECL|member|count
r_int
id|count
suffix:semicolon
)brace
suffix:semicolon
DECL|function|fillonedir
r_static
r_int
id|fillonedir
c_func
(paren
r_void
op_star
id|__buf
comma
r_const
r_char
op_star
id|name
comma
r_int
id|namlen
comma
id|loff_t
id|offset
comma
id|ino_t
id|ino
comma
r_int
r_int
id|d_type
)paren
(brace
r_struct
id|readdir_callback
op_star
id|buf
op_assign
(paren
r_struct
id|readdir_callback
op_star
)paren
id|__buf
suffix:semicolon
r_struct
id|old_linux_dirent
op_star
id|dirent
suffix:semicolon
r_if
c_cond
(paren
id|buf-&gt;count
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|buf-&gt;count
op_increment
suffix:semicolon
id|dirent
op_assign
id|buf-&gt;dirent
suffix:semicolon
id|put_user
c_func
(paren
id|ino
comma
op_amp
id|dirent-&gt;d_ino
)paren
suffix:semicolon
id|put_user
c_func
(paren
id|offset
comma
op_amp
id|dirent-&gt;d_offset
)paren
suffix:semicolon
id|put_user
c_func
(paren
id|namlen
comma
op_amp
id|dirent-&gt;d_namlen
)paren
suffix:semicolon
id|copy_to_user
c_func
(paren
id|dirent-&gt;d_name
comma
id|name
comma
id|namlen
)paren
suffix:semicolon
id|put_user
c_func
(paren
l_int|0
comma
id|dirent-&gt;d_name
op_plus
id|namlen
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|old_readdir
id|asmlinkage
r_int
id|old_readdir
c_func
(paren
r_int
r_int
id|fd
comma
r_void
op_star
id|dirent
comma
r_int
r_int
id|count
)paren
(brace
r_int
id|error
suffix:semicolon
r_struct
id|file
op_star
id|file
suffix:semicolon
r_struct
id|readdir_callback
id|buf
suffix:semicolon
id|error
op_assign
op_minus
id|EBADF
suffix:semicolon
id|file
op_assign
id|fget
c_func
(paren
id|fd
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|file
)paren
r_goto
id|out
suffix:semicolon
id|buf.count
op_assign
l_int|0
suffix:semicolon
id|buf.dirent
op_assign
id|dirent
suffix:semicolon
id|error
op_assign
id|vfs_readdir
c_func
(paren
id|file
comma
id|fillonedir
comma
op_amp
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
op_ge
l_int|0
)paren
id|error
op_assign
id|buf.count
suffix:semicolon
id|fput
c_func
(paren
id|file
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|error
suffix:semicolon
)brace
macro_line|#endif /* !__ia64__ */
multiline_comment|/*&n; * New, all-improved, singing, dancing, iBCS2-compliant getdents()&n; * interface. &n; */
DECL|struct|linux_dirent
r_struct
id|linux_dirent
(brace
DECL|member|d_ino
r_int
r_int
id|d_ino
suffix:semicolon
DECL|member|d_off
r_int
r_int
id|d_off
suffix:semicolon
DECL|member|d_reclen
r_int
r_int
id|d_reclen
suffix:semicolon
DECL|member|d_name
r_char
id|d_name
(braket
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|getdents_callback
r_struct
id|getdents_callback
(brace
DECL|member|current_dir
r_struct
id|linux_dirent
op_star
id|current_dir
suffix:semicolon
DECL|member|previous
r_struct
id|linux_dirent
op_star
id|previous
suffix:semicolon
DECL|member|count
r_int
id|count
suffix:semicolon
DECL|member|error
r_int
id|error
suffix:semicolon
)brace
suffix:semicolon
DECL|function|filldir
r_static
r_int
id|filldir
c_func
(paren
r_void
op_star
id|__buf
comma
r_const
r_char
op_star
id|name
comma
r_int
id|namlen
comma
id|loff_t
id|offset
comma
id|ino_t
id|ino
comma
r_int
r_int
id|d_type
)paren
(brace
r_struct
id|linux_dirent
op_star
id|dirent
suffix:semicolon
r_struct
id|getdents_callback
op_star
id|buf
op_assign
(paren
r_struct
id|getdents_callback
op_star
)paren
id|__buf
suffix:semicolon
r_int
id|reclen
op_assign
id|ROUND_UP
c_func
(paren
id|NAME_OFFSET
c_func
(paren
id|dirent
)paren
op_plus
id|namlen
op_plus
l_int|1
)paren
suffix:semicolon
id|buf-&gt;error
op_assign
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* only used if we fail.. */
r_if
c_cond
(paren
id|reclen
OG
id|buf-&gt;count
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|dirent
op_assign
id|buf-&gt;previous
suffix:semicolon
r_if
c_cond
(paren
id|dirent
)paren
id|put_user
c_func
(paren
id|offset
comma
op_amp
id|dirent-&gt;d_off
)paren
suffix:semicolon
id|dirent
op_assign
id|buf-&gt;current_dir
suffix:semicolon
id|buf-&gt;previous
op_assign
id|dirent
suffix:semicolon
id|put_user
c_func
(paren
id|ino
comma
op_amp
id|dirent-&gt;d_ino
)paren
suffix:semicolon
id|put_user
c_func
(paren
id|reclen
comma
op_amp
id|dirent-&gt;d_reclen
)paren
suffix:semicolon
id|copy_to_user
c_func
(paren
id|dirent-&gt;d_name
comma
id|name
comma
id|namlen
)paren
suffix:semicolon
id|put_user
c_func
(paren
l_int|0
comma
id|dirent-&gt;d_name
op_plus
id|namlen
)paren
suffix:semicolon
(paren
(paren
r_char
op_star
)paren
id|dirent
)paren
op_add_assign
id|reclen
suffix:semicolon
id|buf-&gt;current_dir
op_assign
id|dirent
suffix:semicolon
id|buf-&gt;count
op_sub_assign
id|reclen
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sys_getdents
id|asmlinkage
r_int
id|sys_getdents
c_func
(paren
r_int
r_int
id|fd
comma
r_void
op_star
id|dirent
comma
r_int
r_int
id|count
)paren
(brace
r_struct
id|file
op_star
id|file
suffix:semicolon
r_struct
id|linux_dirent
op_star
id|lastdirent
suffix:semicolon
r_struct
id|getdents_callback
id|buf
suffix:semicolon
r_int
id|error
suffix:semicolon
id|error
op_assign
op_minus
id|EBADF
suffix:semicolon
id|file
op_assign
id|fget
c_func
(paren
id|fd
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|file
)paren
r_goto
id|out
suffix:semicolon
id|buf.current_dir
op_assign
(paren
r_struct
id|linux_dirent
op_star
)paren
id|dirent
suffix:semicolon
id|buf.previous
op_assign
l_int|NULL
suffix:semicolon
id|buf.count
op_assign
id|count
suffix:semicolon
id|buf.error
op_assign
l_int|0
suffix:semicolon
id|error
op_assign
id|vfs_readdir
c_func
(paren
id|file
comma
id|filldir
comma
op_amp
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
OL
l_int|0
)paren
r_goto
id|out_putf
suffix:semicolon
id|error
op_assign
id|buf.error
suffix:semicolon
id|lastdirent
op_assign
id|buf.previous
suffix:semicolon
r_if
c_cond
(paren
id|lastdirent
)paren
(brace
id|put_user
c_func
(paren
id|file-&gt;f_pos
comma
op_amp
id|lastdirent-&gt;d_off
)paren
suffix:semicolon
id|error
op_assign
id|count
op_minus
id|buf.count
suffix:semicolon
)brace
id|out_putf
suffix:colon
id|fput
c_func
(paren
id|file
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/*&n; * And even better one including d_type field and 64bit d_ino and d_off.&n; */
DECL|struct|linux_dirent64
r_struct
id|linux_dirent64
(brace
DECL|member|d_ino
id|u64
id|d_ino
suffix:semicolon
DECL|member|d_off
id|s64
id|d_off
suffix:semicolon
DECL|member|d_reclen
r_int
r_int
id|d_reclen
suffix:semicolon
DECL|member|d_type
r_int
r_char
id|d_type
suffix:semicolon
DECL|member|d_name
r_char
id|d_name
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|ROUND_UP64
mdefine_line|#define ROUND_UP64(x) (((x)+sizeof(u64)-1) &amp; ~(sizeof(u64)-1))
DECL|struct|getdents_callback64
r_struct
id|getdents_callback64
(brace
DECL|member|current_dir
r_struct
id|linux_dirent64
op_star
id|current_dir
suffix:semicolon
DECL|member|previous
r_struct
id|linux_dirent64
op_star
id|previous
suffix:semicolon
DECL|member|count
r_int
id|count
suffix:semicolon
DECL|member|error
r_int
id|error
suffix:semicolon
)brace
suffix:semicolon
DECL|function|filldir64
r_static
r_int
id|filldir64
c_func
(paren
r_void
op_star
id|__buf
comma
r_const
r_char
op_star
id|name
comma
r_int
id|namlen
comma
id|loff_t
id|offset
comma
id|ino_t
id|ino
comma
r_int
r_int
id|d_type
)paren
(brace
r_struct
id|linux_dirent64
op_star
id|dirent
comma
id|d
suffix:semicolon
r_struct
id|getdents_callback64
op_star
id|buf
op_assign
(paren
r_struct
id|getdents_callback64
op_star
)paren
id|__buf
suffix:semicolon
r_int
id|reclen
op_assign
id|ROUND_UP64
c_func
(paren
id|NAME_OFFSET
c_func
(paren
id|dirent
)paren
op_plus
id|namlen
op_plus
l_int|1
)paren
suffix:semicolon
id|buf-&gt;error
op_assign
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* only used if we fail.. */
r_if
c_cond
(paren
id|reclen
OG
id|buf-&gt;count
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|dirent
op_assign
id|buf-&gt;previous
suffix:semicolon
r_if
c_cond
(paren
id|dirent
)paren
(brace
id|d.d_off
op_assign
id|offset
suffix:semicolon
id|copy_to_user
c_func
(paren
op_amp
id|dirent-&gt;d_off
comma
op_amp
id|d.d_off
comma
r_sizeof
(paren
id|d.d_off
)paren
)paren
suffix:semicolon
)brace
id|dirent
op_assign
id|buf-&gt;current_dir
suffix:semicolon
id|buf-&gt;previous
op_assign
id|dirent
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|d
comma
l_int|0
comma
id|NAME_OFFSET
c_func
(paren
op_amp
id|d
)paren
)paren
suffix:semicolon
id|d.d_ino
op_assign
id|ino
suffix:semicolon
id|d.d_reclen
op_assign
id|reclen
suffix:semicolon
id|d.d_type
op_assign
id|d_type
suffix:semicolon
id|copy_to_user
c_func
(paren
id|dirent
comma
op_amp
id|d
comma
id|NAME_OFFSET
c_func
(paren
op_amp
id|d
)paren
)paren
suffix:semicolon
id|copy_to_user
c_func
(paren
id|dirent-&gt;d_name
comma
id|name
comma
id|namlen
)paren
suffix:semicolon
id|put_user
c_func
(paren
l_int|0
comma
id|dirent-&gt;d_name
op_plus
id|namlen
)paren
suffix:semicolon
(paren
(paren
r_char
op_star
)paren
id|dirent
)paren
op_add_assign
id|reclen
suffix:semicolon
id|buf-&gt;current_dir
op_assign
id|dirent
suffix:semicolon
id|buf-&gt;count
op_sub_assign
id|reclen
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sys_getdents64
id|asmlinkage
r_int
id|sys_getdents64
c_func
(paren
r_int
r_int
id|fd
comma
r_void
op_star
id|dirent
comma
r_int
r_int
id|count
)paren
(brace
r_struct
id|file
op_star
id|file
suffix:semicolon
r_struct
id|linux_dirent64
op_star
id|lastdirent
suffix:semicolon
r_struct
id|getdents_callback64
id|buf
suffix:semicolon
r_int
id|error
suffix:semicolon
id|error
op_assign
op_minus
id|EBADF
suffix:semicolon
id|file
op_assign
id|fget
c_func
(paren
id|fd
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|file
)paren
r_goto
id|out
suffix:semicolon
id|buf.current_dir
op_assign
(paren
r_struct
id|linux_dirent64
op_star
)paren
id|dirent
suffix:semicolon
id|buf.previous
op_assign
l_int|NULL
suffix:semicolon
id|buf.count
op_assign
id|count
suffix:semicolon
id|buf.error
op_assign
l_int|0
suffix:semicolon
id|error
op_assign
id|vfs_readdir
c_func
(paren
id|file
comma
id|filldir64
comma
op_amp
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
OL
l_int|0
)paren
r_goto
id|out_putf
suffix:semicolon
id|error
op_assign
id|buf.error
suffix:semicolon
id|lastdirent
op_assign
id|buf.previous
suffix:semicolon
r_if
c_cond
(paren
id|lastdirent
)paren
(brace
r_struct
id|linux_dirent64
id|d
suffix:semicolon
id|d.d_off
op_assign
id|file-&gt;f_pos
suffix:semicolon
id|copy_to_user
c_func
(paren
op_amp
id|lastdirent-&gt;d_off
comma
op_amp
id|d.d_off
comma
r_sizeof
(paren
id|d.d_off
)paren
)paren
suffix:semicolon
id|error
op_assign
id|count
op_minus
id|buf.count
suffix:semicolon
)brace
id|out_putf
suffix:colon
id|fput
c_func
(paren
id|file
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|error
suffix:semicolon
)brace
eof
