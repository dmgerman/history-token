multiline_comment|/*&n; * linux/ipc/shm.c&n; * Copyright (C) 1992, 1993 Krishna Balasubramanian&n; *&t; Many improvements/fixes by Bruno Haible.&n; * Replaced `struct shm_desc&squot; by `struct vm_area_struct&squot;, July 1994.&n; * Fixed the shm swap deallocation (shm_unuse()), August 1998 Andrea Arcangeli.&n; *&n; * /proc/sysvipc/shm support (c) 1999 Dragos Acostachioaie &lt;dragos@iname.com&gt;&n; * BIGMEM support, Andrea Arcangeli &lt;andrea@suse.de&gt;&n; * SMP thread shm, Jean-Luc Boyard &lt;jean-luc.boyard@siemens.fr&gt;&n; * HIGHMEM support, Ingo Molnar &lt;mingo@redhat.com&gt;&n; * Make shmmax, shmall, shmmni sysctl&squot;able, Christoph Rohland &lt;cr@sap.com&gt;&n; * Shared /dev/zero support, Kanoj Sarcar &lt;kanoj@sgi.com&gt;&n; * Move the mm functionality over to mm/shmem.c, Christoph Rohland &lt;cr@sap.com&gt;&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/shm.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/shmem_fs.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;util.h&quot;
DECL|macro|shm_flags
mdefine_line|#define shm_flags&t;shm_perm.mode
DECL|variable|shm_file_operations
r_static
r_struct
id|file_operations
id|shm_file_operations
suffix:semicolon
DECL|variable|shm_vm_ops
r_static
r_struct
id|vm_operations_struct
id|shm_vm_ops
suffix:semicolon
DECL|variable|shm_ids
r_static
r_struct
id|ipc_ids
id|shm_ids
suffix:semicolon
DECL|macro|shm_lock
mdefine_line|#define shm_lock(id)&t;((struct shmid_kernel*)ipc_lock(&amp;shm_ids,id))
DECL|macro|shm_unlock
mdefine_line|#define shm_unlock(id)&t;ipc_unlock(&amp;shm_ids,id)
DECL|macro|shm_lockall
mdefine_line|#define shm_lockall()&t;ipc_lockall(&amp;shm_ids)
DECL|macro|shm_unlockall
mdefine_line|#define shm_unlockall()&t;ipc_unlockall(&amp;shm_ids)
DECL|macro|shm_get
mdefine_line|#define shm_get(id)&t;((struct shmid_kernel*)ipc_get(&amp;shm_ids,id))
DECL|macro|shm_buildid
mdefine_line|#define shm_buildid(id, seq) &bslash;&n;&t;ipc_buildid(&amp;shm_ids, id, seq)
r_static
r_int
id|newseg
(paren
id|key_t
id|key
comma
r_int
id|shmflg
comma
r_int
id|size
)paren
suffix:semicolon
r_static
r_void
id|shm_open
(paren
r_struct
id|vm_area_struct
op_star
id|shmd
)paren
suffix:semicolon
r_static
r_void
id|shm_close
(paren
r_struct
id|vm_area_struct
op_star
id|shmd
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PROC_FS
r_static
r_int
id|sysvipc_shm_read_proc
c_func
(paren
r_char
op_star
id|buffer
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|length
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|shm_ctlmax
r_int
id|shm_ctlmax
op_assign
id|SHMMAX
suffix:semicolon
DECL|variable|shm_ctlall
r_int
id|shm_ctlall
op_assign
id|SHMALL
suffix:semicolon
DECL|variable|shm_ctlmni
r_int
id|shm_ctlmni
op_assign
id|SHMMNI
suffix:semicolon
DECL|variable|shm_tot
r_static
r_int
id|shm_tot
suffix:semicolon
multiline_comment|/* total number of shared memory pages */
DECL|function|shm_init
r_void
id|__init
id|shm_init
(paren
r_void
)paren
(brace
id|ipc_init_ids
c_func
(paren
op_amp
id|shm_ids
comma
l_int|1
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PROC_FS
id|create_proc_read_entry
c_func
(paren
l_string|&quot;sysvipc/shm&quot;
comma
l_int|0
comma
l_int|0
comma
id|sysvipc_shm_read_proc
comma
l_int|NULL
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|shm_checkid
r_static
r_inline
r_int
id|shm_checkid
c_func
(paren
r_struct
id|shmid_kernel
op_star
id|s
comma
r_int
id|id
)paren
(brace
r_if
c_cond
(paren
id|ipc_checkid
c_func
(paren
op_amp
id|shm_ids
comma
op_amp
id|s-&gt;shm_perm
comma
id|id
)paren
)paren
r_return
op_minus
id|EIDRM
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|shm_rmid
r_static
r_inline
r_struct
id|shmid_kernel
op_star
id|shm_rmid
c_func
(paren
r_int
id|id
)paren
(brace
r_return
(paren
r_struct
id|shmid_kernel
op_star
)paren
id|ipc_rmid
c_func
(paren
op_amp
id|shm_ids
comma
id|id
)paren
suffix:semicolon
)brace
DECL|function|shm_addid
r_static
r_inline
r_int
id|shm_addid
c_func
(paren
r_struct
id|shmid_kernel
op_star
id|shp
)paren
(brace
r_return
id|ipc_addid
c_func
(paren
op_amp
id|shm_ids
comma
op_amp
id|shp-&gt;shm_perm
comma
id|shm_ctlmni
op_plus
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|shm_inc
r_static
r_inline
r_void
id|shm_inc
(paren
r_int
id|id
)paren
(brace
r_struct
id|shmid_kernel
op_star
id|shp
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|shp
op_assign
id|shm_lock
c_func
(paren
id|id
)paren
)paren
)paren
(brace
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
id|shp-&gt;shm_atim
op_assign
id|CURRENT_TIME
suffix:semicolon
id|shp-&gt;shm_lprid
op_assign
id|current-&gt;pid
suffix:semicolon
id|shp-&gt;shm_nattch
op_increment
suffix:semicolon
id|shm_unlock
c_func
(paren
id|id
)paren
suffix:semicolon
)brace
multiline_comment|/* This is called by fork, once for every shm attach. */
DECL|function|shm_open
r_static
r_void
id|shm_open
(paren
r_struct
id|vm_area_struct
op_star
id|shmd
)paren
(brace
id|shm_inc
(paren
id|shmd-&gt;vm_file-&gt;f_dentry-&gt;d_inode-&gt;i_ino
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * shm_destroy - free the struct shmid_kernel&n; *&n; * @shp: struct to free&n; *&n; * It has to be called with shp and shm_ids.sem locked,&n; * but returns with shp unlocked and freed.&n; */
DECL|function|shm_destroy
r_static
r_void
id|shm_destroy
(paren
r_struct
id|shmid_kernel
op_star
id|shp
)paren
(brace
id|shm_tot
op_sub_assign
(paren
id|shp-&gt;shm_segsz
op_plus
id|PAGE_SIZE
op_minus
l_int|1
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|shm_rmid
(paren
id|shp-&gt;id
)paren
suffix:semicolon
id|shm_unlock
c_func
(paren
id|shp-&gt;id
)paren
suffix:semicolon
id|shmem_lock
c_func
(paren
id|shp-&gt;shm_file
comma
l_int|0
)paren
suffix:semicolon
id|fput
(paren
id|shp-&gt;shm_file
)paren
suffix:semicolon
id|kfree
(paren
id|shp
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * remove the attach descriptor shmd.&n; * free memory for segment if it is marked destroyed.&n; * The descriptor has already been removed from the current-&gt;mm-&gt;mmap list&n; * and will later be kfree()d.&n; */
DECL|function|shm_close
r_static
r_void
id|shm_close
(paren
r_struct
id|vm_area_struct
op_star
id|shmd
)paren
(brace
r_struct
id|file
op_star
id|file
op_assign
id|shmd-&gt;vm_file
suffix:semicolon
r_int
id|id
op_assign
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_ino
suffix:semicolon
r_struct
id|shmid_kernel
op_star
id|shp
suffix:semicolon
id|down
(paren
op_amp
id|shm_ids.sem
)paren
suffix:semicolon
multiline_comment|/* remove from the list of attaches of the shm segment */
r_if
c_cond
(paren
op_logical_neg
(paren
id|shp
op_assign
id|shm_lock
c_func
(paren
id|id
)paren
)paren
)paren
(brace
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
id|shp-&gt;shm_lprid
op_assign
id|current-&gt;pid
suffix:semicolon
id|shp-&gt;shm_dtim
op_assign
id|CURRENT_TIME
suffix:semicolon
id|shp-&gt;shm_nattch
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|shp-&gt;shm_nattch
op_eq
l_int|0
op_logical_and
id|shp-&gt;shm_flags
op_amp
id|SHM_DEST
)paren
(brace
id|shm_destroy
(paren
id|shp
)paren
suffix:semicolon
)brace
r_else
id|shm_unlock
c_func
(paren
id|id
)paren
suffix:semicolon
id|up
(paren
op_amp
id|shm_ids.sem
)paren
suffix:semicolon
)brace
DECL|function|shm_mmap
r_static
r_int
id|shm_mmap
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|vm_area_struct
op_star
id|vma
)paren
(brace
id|UPDATE_ATIME
c_func
(paren
id|file-&gt;f_dentry-&gt;d_inode
)paren
suffix:semicolon
id|vma-&gt;vm_ops
op_assign
op_amp
id|shm_vm_ops
suffix:semicolon
id|shm_inc
c_func
(paren
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_ino
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|shm_file_operations
r_static
r_struct
id|file_operations
id|shm_file_operations
op_assign
(brace
dot
id|mmap
op_assign
id|shm_mmap
)brace
suffix:semicolon
DECL|variable|shm_vm_ops
r_static
r_struct
id|vm_operations_struct
id|shm_vm_ops
op_assign
(brace
dot
id|open
op_assign
id|shm_open
comma
multiline_comment|/* callback for a new vm-area open */
dot
id|close
op_assign
id|shm_close
comma
multiline_comment|/* callback for when the vm-area is released */
dot
id|nopage
op_assign
id|shmem_nopage
comma
)brace
suffix:semicolon
DECL|function|newseg
r_static
r_int
id|newseg
(paren
id|key_t
id|key
comma
r_int
id|shmflg
comma
r_int
id|size
)paren
(brace
r_int
id|error
suffix:semicolon
r_struct
id|shmid_kernel
op_star
id|shp
suffix:semicolon
r_int
id|numpages
op_assign
(paren
id|size
op_plus
id|PAGE_SIZE
op_minus
l_int|1
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
r_struct
id|file
op_star
id|file
suffix:semicolon
r_char
id|name
(braket
l_int|13
)braket
suffix:semicolon
r_int
id|id
suffix:semicolon
r_if
c_cond
(paren
id|size
template_param
id|shm_ctlmax
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|shm_tot
op_plus
id|numpages
op_ge
id|shm_ctlall
)paren
r_return
op_minus
id|ENOSPC
suffix:semicolon
id|shp
op_assign
(paren
r_struct
id|shmid_kernel
op_star
)paren
id|kmalloc
(paren
r_sizeof
(paren
op_star
id|shp
)paren
comma
id|GFP_USER
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|shp
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|shp-&gt;shm_perm.key
op_assign
id|key
suffix:semicolon
id|shp-&gt;shm_flags
op_assign
(paren
id|shmflg
op_amp
id|S_IRWXUGO
)paren
suffix:semicolon
id|sprintf
(paren
id|name
comma
l_string|&quot;SYSV%08x&quot;
comma
id|key
)paren
suffix:semicolon
id|file
op_assign
id|shmem_file_setup
c_func
(paren
id|name
comma
id|size
comma
id|VM_ACCOUNT
)paren
suffix:semicolon
id|error
op_assign
id|PTR_ERR
c_func
(paren
id|file
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|file
)paren
)paren
r_goto
id|no_file
suffix:semicolon
id|error
op_assign
op_minus
id|ENOSPC
suffix:semicolon
id|id
op_assign
id|shm_addid
c_func
(paren
id|shp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|id
op_eq
op_minus
l_int|1
)paren
(brace
r_goto
id|no_id
suffix:semicolon
)brace
id|shp-&gt;shm_cprid
op_assign
id|current-&gt;pid
suffix:semicolon
id|shp-&gt;shm_lprid
op_assign
l_int|0
suffix:semicolon
id|shp-&gt;shm_atim
op_assign
id|shp-&gt;shm_dtim
op_assign
l_int|0
suffix:semicolon
id|shp-&gt;shm_ctim
op_assign
id|CURRENT_TIME
suffix:semicolon
id|shp-&gt;shm_segsz
op_assign
id|size
suffix:semicolon
id|shp-&gt;shm_nattch
op_assign
l_int|0
suffix:semicolon
id|shp-&gt;id
op_assign
id|shm_buildid
c_func
(paren
id|id
comma
id|shp-&gt;shm_perm.seq
)paren
suffix:semicolon
id|shp-&gt;shm_file
op_assign
id|file
suffix:semicolon
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_ino
op_assign
id|shp-&gt;id
suffix:semicolon
id|file-&gt;f_op
op_assign
op_amp
id|shm_file_operations
suffix:semicolon
id|shm_tot
op_add_assign
id|numpages
suffix:semicolon
id|shm_unlock
(paren
id|id
)paren
suffix:semicolon
r_return
id|shp-&gt;id
suffix:semicolon
id|no_id
suffix:colon
id|fput
c_func
(paren
id|file
)paren
suffix:semicolon
id|no_file
suffix:colon
id|kfree
c_func
(paren
id|shp
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|sys_shmget
id|asmlinkage
r_int
id|sys_shmget
(paren
id|key_t
id|key
comma
r_int
id|size
comma
r_int
id|shmflg
)paren
(brace
r_struct
id|shmid_kernel
op_star
id|shp
suffix:semicolon
r_int
id|err
comma
id|id
op_assign
l_int|0
suffix:semicolon
id|down
c_func
(paren
op_amp
id|shm_ids.sem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|key
op_eq
id|IPC_PRIVATE
)paren
(brace
id|err
op_assign
id|newseg
c_func
(paren
id|key
comma
id|shmflg
comma
id|size
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|id
op_assign
id|ipc_findkey
c_func
(paren
op_amp
id|shm_ids
comma
id|key
)paren
)paren
op_eq
op_minus
l_int|1
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|shmflg
op_amp
id|IPC_CREAT
)paren
)paren
id|err
op_assign
op_minus
id|ENOENT
suffix:semicolon
r_else
id|err
op_assign
id|newseg
c_func
(paren
id|key
comma
id|shmflg
comma
id|size
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|shmflg
op_amp
id|IPC_CREAT
)paren
op_logical_and
(paren
id|shmflg
op_amp
id|IPC_EXCL
)paren
)paren
(brace
id|err
op_assign
op_minus
id|EEXIST
suffix:semicolon
)brace
r_else
(brace
id|shp
op_assign
id|shm_lock
c_func
(paren
id|id
)paren
suffix:semicolon
r_if
c_cond
(paren
id|shp
op_eq
l_int|NULL
)paren
(brace
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|shp-&gt;shm_segsz
OL
id|size
)paren
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_else
r_if
c_cond
(paren
id|ipcperms
c_func
(paren
op_amp
id|shp-&gt;shm_perm
comma
id|shmflg
)paren
)paren
id|err
op_assign
op_minus
id|EACCES
suffix:semicolon
r_else
id|err
op_assign
id|shm_buildid
c_func
(paren
id|id
comma
id|shp-&gt;shm_perm.seq
)paren
suffix:semicolon
id|shm_unlock
c_func
(paren
id|id
)paren
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|shm_ids.sem
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|copy_shmid_to_user
r_static
r_inline
r_int
r_int
id|copy_shmid_to_user
c_func
(paren
r_void
op_star
id|buf
comma
r_struct
id|shmid64_ds
op_star
id|in
comma
r_int
id|version
)paren
(brace
r_switch
c_cond
(paren
id|version
)paren
(brace
r_case
id|IPC_64
suffix:colon
r_return
id|copy_to_user
c_func
(paren
id|buf
comma
id|in
comma
r_sizeof
(paren
op_star
id|in
)paren
)paren
suffix:semicolon
r_case
id|IPC_OLD
suffix:colon
(brace
r_struct
id|shmid_ds
id|out
suffix:semicolon
id|ipc64_perm_to_ipc_perm
c_func
(paren
op_amp
id|in-&gt;shm_perm
comma
op_amp
id|out.shm_perm
)paren
suffix:semicolon
id|out.shm_segsz
op_assign
id|in-&gt;shm_segsz
suffix:semicolon
id|out.shm_atime
op_assign
id|in-&gt;shm_atime
suffix:semicolon
id|out.shm_dtime
op_assign
id|in-&gt;shm_dtime
suffix:semicolon
id|out.shm_ctime
op_assign
id|in-&gt;shm_ctime
suffix:semicolon
id|out.shm_cpid
op_assign
id|in-&gt;shm_cpid
suffix:semicolon
id|out.shm_lpid
op_assign
id|in-&gt;shm_lpid
suffix:semicolon
id|out.shm_nattch
op_assign
id|in-&gt;shm_nattch
suffix:semicolon
r_return
id|copy_to_user
c_func
(paren
id|buf
comma
op_amp
id|out
comma
r_sizeof
(paren
id|out
)paren
)paren
suffix:semicolon
)brace
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
DECL|struct|shm_setbuf
r_struct
id|shm_setbuf
(brace
DECL|member|uid
id|uid_t
id|uid
suffix:semicolon
DECL|member|gid
id|gid_t
id|gid
suffix:semicolon
DECL|member|mode
id|mode_t
id|mode
suffix:semicolon
)brace
suffix:semicolon
DECL|function|copy_shmid_from_user
r_static
r_inline
r_int
r_int
id|copy_shmid_from_user
c_func
(paren
r_struct
id|shm_setbuf
op_star
id|out
comma
r_void
op_star
id|buf
comma
r_int
id|version
)paren
(brace
r_switch
c_cond
(paren
id|version
)paren
(brace
r_case
id|IPC_64
suffix:colon
(brace
r_struct
id|shmid64_ds
id|tbuf
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|tbuf
comma
id|buf
comma
r_sizeof
(paren
id|tbuf
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|out-&gt;uid
op_assign
id|tbuf.shm_perm.uid
suffix:semicolon
id|out-&gt;gid
op_assign
id|tbuf.shm_perm.gid
suffix:semicolon
id|out-&gt;mode
op_assign
id|tbuf.shm_flags
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|IPC_OLD
suffix:colon
(brace
r_struct
id|shmid_ds
id|tbuf_old
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|tbuf_old
comma
id|buf
comma
r_sizeof
(paren
id|tbuf_old
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|out-&gt;uid
op_assign
id|tbuf_old.shm_perm.uid
suffix:semicolon
id|out-&gt;gid
op_assign
id|tbuf_old.shm_perm.gid
suffix:semicolon
id|out-&gt;mode
op_assign
id|tbuf_old.shm_flags
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
DECL|function|copy_shminfo_to_user
r_static
r_inline
r_int
r_int
id|copy_shminfo_to_user
c_func
(paren
r_void
op_star
id|buf
comma
r_struct
id|shminfo64
op_star
id|in
comma
r_int
id|version
)paren
(brace
r_switch
c_cond
(paren
id|version
)paren
(brace
r_case
id|IPC_64
suffix:colon
r_return
id|copy_to_user
c_func
(paren
id|buf
comma
id|in
comma
r_sizeof
(paren
op_star
id|in
)paren
)paren
suffix:semicolon
r_case
id|IPC_OLD
suffix:colon
(brace
r_struct
id|shminfo
id|out
suffix:semicolon
r_if
c_cond
(paren
id|in-&gt;shmmax
OG
id|INT_MAX
)paren
(brace
id|out.shmmax
op_assign
id|INT_MAX
suffix:semicolon
)brace
r_else
id|out.shmmax
op_assign
(paren
r_int
)paren
id|in-&gt;shmmax
suffix:semicolon
id|out.shmmin
op_assign
id|in-&gt;shmmin
suffix:semicolon
id|out.shmmni
op_assign
id|in-&gt;shmmni
suffix:semicolon
id|out.shmseg
op_assign
id|in-&gt;shmseg
suffix:semicolon
id|out.shmall
op_assign
id|in-&gt;shmall
suffix:semicolon
r_return
id|copy_to_user
c_func
(paren
id|buf
comma
op_amp
id|out
comma
r_sizeof
(paren
id|out
)paren
)paren
suffix:semicolon
)brace
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
DECL|function|shm_get_stat
r_static
r_void
id|shm_get_stat
(paren
r_int
r_int
op_star
id|rss
comma
r_int
r_int
op_star
id|swp
)paren
(brace
r_struct
id|shmem_inode_info
op_star
id|info
suffix:semicolon
r_int
id|i
suffix:semicolon
op_star
id|rss
op_assign
l_int|0
suffix:semicolon
op_star
id|swp
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
op_le
id|shm_ids.max_id
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|shmid_kernel
op_star
id|shp
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
id|shp
op_assign
id|shm_get
c_func
(paren
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
id|shp
op_eq
l_int|NULL
)paren
(brace
r_continue
suffix:semicolon
)brace
id|inode
op_assign
id|shp-&gt;shm_file-&gt;f_dentry-&gt;d_inode
suffix:semicolon
id|info
op_assign
id|SHMEM_I
c_func
(paren
id|inode
)paren
suffix:semicolon
id|spin_lock
(paren
op_amp
id|info-&gt;lock
)paren
suffix:semicolon
op_star
id|rss
op_add_assign
id|inode-&gt;i_mapping-&gt;nrpages
suffix:semicolon
op_star
id|swp
op_add_assign
id|info-&gt;swapped
suffix:semicolon
id|spin_unlock
(paren
op_amp
id|info-&gt;lock
)paren
suffix:semicolon
)brace
)brace
DECL|function|sys_shmctl
id|asmlinkage
r_int
id|sys_shmctl
(paren
r_int
id|shmid
comma
r_int
id|cmd
comma
r_struct
id|shmid_ds
op_star
id|buf
)paren
(brace
r_struct
id|shm_setbuf
id|setbuf
suffix:semicolon
r_struct
id|shmid_kernel
op_star
id|shp
suffix:semicolon
r_int
id|err
comma
id|version
suffix:semicolon
r_if
c_cond
(paren
id|cmd
OL
l_int|0
op_logical_or
id|shmid
OL
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|version
op_assign
id|ipc_parse_version
c_func
(paren
op_amp
id|cmd
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
multiline_comment|/* replace with proc interface ? */
r_case
id|IPC_INFO
suffix:colon
(brace
r_struct
id|shminfo64
id|shminfo
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|shminfo
comma
l_int|0
comma
r_sizeof
(paren
id|shminfo
)paren
)paren
suffix:semicolon
id|shminfo.shmmni
op_assign
id|shminfo.shmseg
op_assign
id|shm_ctlmni
suffix:semicolon
id|shminfo.shmmax
op_assign
id|shm_ctlmax
suffix:semicolon
id|shminfo.shmall
op_assign
id|shm_ctlall
suffix:semicolon
id|shminfo.shmmin
op_assign
id|SHMMIN
suffix:semicolon
r_if
c_cond
(paren
id|copy_shminfo_to_user
(paren
id|buf
comma
op_amp
id|shminfo
comma
id|version
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
multiline_comment|/* reading a integer is always atomic */
id|err
op_assign
id|shm_ids.max_id
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
id|err
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
r_case
id|SHM_INFO
suffix:colon
(brace
r_struct
id|shm_info
id|shm_info
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|shm_info
comma
l_int|0
comma
r_sizeof
(paren
id|shm_info
)paren
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|shm_ids.sem
)paren
suffix:semicolon
id|shm_lockall
c_func
(paren
)paren
suffix:semicolon
id|shm_info.used_ids
op_assign
id|shm_ids.in_use
suffix:semicolon
id|shm_get_stat
(paren
op_amp
id|shm_info.shm_rss
comma
op_amp
id|shm_info.shm_swp
)paren
suffix:semicolon
id|shm_info.shm_tot
op_assign
id|shm_tot
suffix:semicolon
id|shm_info.swap_attempts
op_assign
l_int|0
suffix:semicolon
id|shm_info.swap_successes
op_assign
l_int|0
suffix:semicolon
id|err
op_assign
id|shm_ids.max_id
suffix:semicolon
id|shm_unlockall
c_func
(paren
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|shm_ids.sem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
(paren
id|buf
comma
op_amp
id|shm_info
comma
r_sizeof
(paren
id|shm_info
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
id|err
OL
l_int|0
ques
c_cond
l_int|0
suffix:colon
id|err
suffix:semicolon
)brace
r_case
id|SHM_STAT
suffix:colon
r_case
id|IPC_STAT
suffix:colon
(brace
r_struct
id|shmid64_ds
id|tbuf
suffix:semicolon
r_int
id|result
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|tbuf
comma
l_int|0
comma
r_sizeof
(paren
id|tbuf
)paren
)paren
suffix:semicolon
id|shp
op_assign
id|shm_lock
c_func
(paren
id|shmid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|shp
op_eq
l_int|NULL
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cmd
op_eq
id|SHM_STAT
)paren
(brace
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|shmid
OG
id|shm_ids.max_id
)paren
r_goto
id|out_unlock
suffix:semicolon
id|result
op_assign
id|shm_buildid
c_func
(paren
id|shmid
comma
id|shp-&gt;shm_perm.seq
)paren
suffix:semicolon
)brace
r_else
(brace
id|err
op_assign
id|shm_checkid
c_func
(paren
id|shp
comma
id|shmid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
r_goto
id|out_unlock
suffix:semicolon
)brace
id|result
op_assign
l_int|0
suffix:semicolon
)brace
id|err
op_assign
op_minus
id|EACCES
suffix:semicolon
r_if
c_cond
(paren
id|ipcperms
(paren
op_amp
id|shp-&gt;shm_perm
comma
id|S_IRUGO
)paren
)paren
r_goto
id|out_unlock
suffix:semicolon
id|kernel_to_ipc64_perm
c_func
(paren
op_amp
id|shp-&gt;shm_perm
comma
op_amp
id|tbuf.shm_perm
)paren
suffix:semicolon
id|tbuf.shm_segsz
op_assign
id|shp-&gt;shm_segsz
suffix:semicolon
id|tbuf.shm_atime
op_assign
id|shp-&gt;shm_atim
suffix:semicolon
id|tbuf.shm_dtime
op_assign
id|shp-&gt;shm_dtim
suffix:semicolon
id|tbuf.shm_ctime
op_assign
id|shp-&gt;shm_ctim
suffix:semicolon
id|tbuf.shm_cpid
op_assign
id|shp-&gt;shm_cprid
suffix:semicolon
id|tbuf.shm_lpid
op_assign
id|shp-&gt;shm_lprid
suffix:semicolon
id|tbuf.shm_nattch
op_assign
id|shp-&gt;shm_nattch
suffix:semicolon
id|shm_unlock
c_func
(paren
id|shmid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_shmid_to_user
(paren
id|buf
comma
op_amp
id|tbuf
comma
id|version
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
id|result
suffix:semicolon
)brace
r_case
id|SHM_LOCK
suffix:colon
r_case
id|SHM_UNLOCK
suffix:colon
(brace
multiline_comment|/* Allow superuser to lock segment in memory */
multiline_comment|/* Should the pages be faulted in here or leave it to user? */
multiline_comment|/* need to determine interaction with current-&gt;swappable */
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_IPC_LOCK
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
id|shp
op_assign
id|shm_lock
c_func
(paren
id|shmid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|shp
op_eq
l_int|NULL
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|err
op_assign
id|shm_checkid
c_func
(paren
id|shp
comma
id|shmid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
r_goto
id|out_unlock
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cmd
op_eq
id|SHM_LOCK
)paren
(brace
id|shmem_lock
c_func
(paren
id|shp-&gt;shm_file
comma
l_int|1
)paren
suffix:semicolon
id|shp-&gt;shm_flags
op_or_assign
id|SHM_LOCKED
suffix:semicolon
)brace
r_else
(brace
id|shmem_lock
c_func
(paren
id|shp-&gt;shm_file
comma
l_int|0
)paren
suffix:semicolon
id|shp-&gt;shm_flags
op_and_assign
op_complement
id|SHM_LOCKED
suffix:semicolon
)brace
id|shm_unlock
c_func
(paren
id|shmid
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
r_case
id|IPC_RMID
suffix:colon
(brace
multiline_comment|/*&n;&t;&t; *&t;We cannot simply remove the file. The SVID states&n;&t;&t; *&t;that the block remains until the last person&n;&t;&t; *&t;detaches from it, then is deleted. A shmat() on&n;&t;&t; *&t;an RMID segment is legal in older Linux and if &n;&t;&t; *&t;we change it apps break...&n;&t;&t; *&n;&t;&t; *&t;Instead we set a destroyed flag, and then blow&n;&t;&t; *&t;the name away when the usage hits zero.&n;&t;&t; */
id|down
c_func
(paren
op_amp
id|shm_ids.sem
)paren
suffix:semicolon
id|shp
op_assign
id|shm_lock
c_func
(paren
id|shmid
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|shp
op_eq
l_int|NULL
)paren
r_goto
id|out_up
suffix:semicolon
id|err
op_assign
id|shm_checkid
c_func
(paren
id|shp
comma
id|shmid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
r_goto
id|out_unlock_up
suffix:semicolon
)brace
r_if
c_cond
(paren
id|current-&gt;euid
op_ne
id|shp-&gt;shm_perm.uid
op_logical_and
id|current-&gt;euid
op_ne
id|shp-&gt;shm_perm.cuid
op_logical_and
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
(brace
id|err
op_assign
op_minus
id|EPERM
suffix:semicolon
r_goto
id|out_unlock_up
suffix:semicolon
)brace
r_if
c_cond
(paren
id|shp-&gt;shm_nattch
)paren
(brace
id|shp-&gt;shm_flags
op_or_assign
id|SHM_DEST
suffix:semicolon
multiline_comment|/* Do not find it any more */
id|shp-&gt;shm_perm.key
op_assign
id|IPC_PRIVATE
suffix:semicolon
id|shm_unlock
c_func
(paren
id|shmid
)paren
suffix:semicolon
)brace
r_else
id|shm_destroy
(paren
id|shp
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|shm_ids.sem
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
r_case
id|IPC_SET
suffix:colon
(brace
r_if
c_cond
(paren
id|copy_shmid_from_user
(paren
op_amp
id|setbuf
comma
id|buf
comma
id|version
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|down
c_func
(paren
op_amp
id|shm_ids.sem
)paren
suffix:semicolon
id|shp
op_assign
id|shm_lock
c_func
(paren
id|shmid
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|shp
op_eq
l_int|NULL
)paren
(brace
r_goto
id|out_up
suffix:semicolon
)brace
id|err
op_assign
id|shm_checkid
c_func
(paren
id|shp
comma
id|shmid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
r_goto
id|out_unlock_up
suffix:semicolon
)brace
id|err
op_assign
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;euid
op_ne
id|shp-&gt;shm_perm.uid
op_logical_and
id|current-&gt;euid
op_ne
id|shp-&gt;shm_perm.cuid
op_logical_and
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
(brace
r_goto
id|out_unlock_up
suffix:semicolon
)brace
id|shp-&gt;shm_perm.uid
op_assign
id|setbuf.uid
suffix:semicolon
id|shp-&gt;shm_perm.gid
op_assign
id|setbuf.gid
suffix:semicolon
id|shp-&gt;shm_flags
op_assign
(paren
id|shp-&gt;shm_flags
op_amp
op_complement
id|S_IRWXUGO
)paren
op_or
(paren
id|setbuf.mode
op_amp
id|S_IRWXUGO
)paren
suffix:semicolon
id|shp-&gt;shm_ctim
op_assign
id|CURRENT_TIME
suffix:semicolon
r_break
suffix:semicolon
)brace
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|err
op_assign
l_int|0
suffix:semicolon
id|out_unlock_up
suffix:colon
id|shm_unlock
c_func
(paren
id|shmid
)paren
suffix:semicolon
id|out_up
suffix:colon
id|up
c_func
(paren
op_amp
id|shm_ids.sem
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
id|out_unlock
suffix:colon
id|shm_unlock
c_func
(paren
id|shmid
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*&n; * Fix shmaddr, allocate descriptor, map shm, add attach descriptor to lists.&n; */
DECL|function|sys_shmat
id|asmlinkage
r_int
id|sys_shmat
(paren
r_int
id|shmid
comma
r_char
op_star
id|shmaddr
comma
r_int
id|shmflg
comma
id|ulong
op_star
id|raddr
)paren
(brace
r_struct
id|shmid_kernel
op_star
id|shp
suffix:semicolon
r_int
r_int
id|addr
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
r_struct
id|file
op_star
id|file
suffix:semicolon
r_int
id|err
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|prot
suffix:semicolon
r_int
r_int
id|o_flags
suffix:semicolon
r_int
id|acc_mode
suffix:semicolon
r_void
op_star
id|user_addr
suffix:semicolon
r_if
c_cond
(paren
id|shmid
OL
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|addr
op_assign
(paren
id|ulong
)paren
id|shmaddr
)paren
)paren
(brace
r_if
c_cond
(paren
id|addr
op_amp
(paren
id|SHMLBA
op_minus
l_int|1
)paren
)paren
(brace
r_if
c_cond
(paren
id|shmflg
op_amp
id|SHM_RND
)paren
id|addr
op_and_assign
op_complement
(paren
id|SHMLBA
op_minus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* round down */
r_else
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|flags
op_assign
id|MAP_SHARED
op_or
id|MAP_FIXED
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
(paren
id|shmflg
op_amp
id|SHM_REMAP
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|flags
op_assign
id|MAP_SHARED
suffix:semicolon
)brace
r_if
c_cond
(paren
id|shmflg
op_amp
id|SHM_RDONLY
)paren
(brace
id|prot
op_assign
id|PROT_READ
suffix:semicolon
id|o_flags
op_assign
id|O_RDONLY
suffix:semicolon
id|acc_mode
op_assign
id|S_IRUGO
suffix:semicolon
)brace
r_else
(brace
id|prot
op_assign
id|PROT_READ
op_or
id|PROT_WRITE
suffix:semicolon
id|o_flags
op_assign
id|O_RDWR
suffix:semicolon
id|acc_mode
op_assign
id|S_IRUGO
op_or
id|S_IWUGO
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * We cannot rely on the fs check since SYSV IPC does have an&n;&t; * additional creator id...&n;&t; */
id|shp
op_assign
id|shm_lock
c_func
(paren
id|shmid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|shp
op_eq
l_int|NULL
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|err
op_assign
id|shm_checkid
c_func
(paren
id|shp
comma
id|shmid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|shm_unlock
c_func
(paren
id|shmid
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ipcperms
c_func
(paren
op_amp
id|shp-&gt;shm_perm
comma
id|acc_mode
)paren
)paren
(brace
id|shm_unlock
c_func
(paren
id|shmid
)paren
suffix:semicolon
r_return
op_minus
id|EACCES
suffix:semicolon
)brace
id|file
op_assign
id|shp-&gt;shm_file
suffix:semicolon
id|size
op_assign
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_size
suffix:semicolon
id|shp-&gt;shm_nattch
op_increment
suffix:semicolon
id|shm_unlock
c_func
(paren
id|shmid
)paren
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|addr
op_logical_and
op_logical_neg
(paren
id|shmflg
op_amp
id|SHM_REMAP
)paren
)paren
(brace
id|user_addr
op_assign
id|ERR_PTR
c_func
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|find_vma_intersection
c_func
(paren
id|current-&gt;mm
comma
id|addr
comma
id|addr
op_plus
id|size
)paren
)paren
r_goto
id|invalid
suffix:semicolon
multiline_comment|/*&n;&t;&t; * If shm segment goes below stack, make sure there is some&n;&t;&t; * space left for the stack to grow (at least 4 pages).&n;&t;&t; */
r_if
c_cond
(paren
id|addr
template_param
id|current-&gt;mm-&gt;start_stack
op_minus
id|size
op_minus
id|PAGE_SIZE
op_star
l_int|5
)paren
r_goto
id|invalid
suffix:semicolon
)brace
id|user_addr
op_assign
(paren
r_void
op_star
)paren
id|do_mmap
(paren
id|file
comma
id|addr
comma
id|size
comma
id|prot
comma
id|flags
comma
l_int|0
)paren
suffix:semicolon
id|invalid
suffix:colon
id|up_write
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
id|down
(paren
op_amp
id|shm_ids.sem
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|shp
op_assign
id|shm_lock
c_func
(paren
id|shmid
)paren
)paren
)paren
(brace
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
id|shp-&gt;shm_nattch
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|shp-&gt;shm_nattch
op_eq
l_int|0
op_logical_and
id|shp-&gt;shm_flags
op_amp
id|SHM_DEST
)paren
(brace
id|shm_destroy
(paren
id|shp
)paren
suffix:semicolon
)brace
r_else
id|shm_unlock
c_func
(paren
id|shmid
)paren
suffix:semicolon
id|up
(paren
op_amp
id|shm_ids.sem
)paren
suffix:semicolon
op_star
id|raddr
op_assign
(paren
r_int
r_int
)paren
id|user_addr
suffix:semicolon
id|err
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|user_addr
)paren
)paren
id|err
op_assign
id|PTR_ERR
c_func
(paren
id|user_addr
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*&n; * detach and kill segment if marked destroyed.&n; * The work is done in shm_close.&n; */
DECL|function|sys_shmdt
id|asmlinkage
r_int
id|sys_shmdt
(paren
r_char
op_star
id|shmaddr
)paren
(brace
r_struct
id|mm_struct
op_star
id|mm
op_assign
id|current-&gt;mm
suffix:semicolon
r_struct
id|vm_area_struct
op_star
id|shmd
comma
op_star
id|shmdnext
suffix:semicolon
r_int
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
suffix:semicolon
r_for
c_loop
(paren
id|shmd
op_assign
id|mm-&gt;mmap
suffix:semicolon
id|shmd
suffix:semicolon
id|shmd
op_assign
id|shmdnext
)paren
(brace
id|shmdnext
op_assign
id|shmd-&gt;vm_next
suffix:semicolon
r_if
c_cond
(paren
id|shmd-&gt;vm_ops
op_eq
op_amp
id|shm_vm_ops
op_logical_and
id|shmd-&gt;vm_start
op_minus
(paren
id|shmd-&gt;vm_pgoff
op_lshift
id|PAGE_SHIFT
)paren
op_eq
(paren
id|ulong
)paren
id|shmaddr
)paren
(brace
id|do_munmap
c_func
(paren
id|mm
comma
id|shmd-&gt;vm_start
comma
id|shmd-&gt;vm_end
op_minus
id|shmd-&gt;vm_start
)paren
suffix:semicolon
id|retval
op_assign
l_int|0
suffix:semicolon
)brace
)brace
id|up_write
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_PROC_FS
DECL|function|sysvipc_shm_read_proc
r_static
r_int
id|sysvipc_shm_read_proc
c_func
(paren
r_char
op_star
id|buffer
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|length
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
(brace
id|off_t
id|pos
op_assign
l_int|0
suffix:semicolon
id|off_t
id|begin
op_assign
l_int|0
suffix:semicolon
r_int
id|i
comma
id|len
op_assign
l_int|0
suffix:semicolon
id|down
c_func
(paren
op_amp
id|shm_ids.sem
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;       key      shmid perms       size  cpid  lpid nattch   uid   gid  cuid  cgid      atime      dtime      ctime&bslash;n&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
op_le
id|shm_ids.max_id
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|shmid_kernel
op_star
id|shp
suffix:semicolon
id|shp
op_assign
id|shm_lock
c_func
(paren
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
id|shp
op_ne
l_int|NULL
)paren
(brace
DECL|macro|SMALL_STRING
mdefine_line|#define SMALL_STRING &quot;%10d %10d  %4o %10u %5u %5u  %5d %5u %5u %5u %5u %10lu %10lu %10lu&bslash;n&quot;
DECL|macro|BIG_STRING
mdefine_line|#define BIG_STRING   &quot;%10d %10d  %4o %21u %5u %5u  %5d %5u %5u %5u %5u %10lu %10lu %10lu&bslash;n&quot;
r_char
op_star
id|format
suffix:semicolon
r_if
c_cond
(paren
r_sizeof
(paren
r_int
)paren
op_le
r_sizeof
(paren
r_int
)paren
)paren
id|format
op_assign
id|SMALL_STRING
suffix:semicolon
r_else
id|format
op_assign
id|BIG_STRING
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
id|format
comma
id|shp-&gt;shm_perm.key
comma
id|shm_buildid
c_func
(paren
id|i
comma
id|shp-&gt;shm_perm.seq
)paren
comma
id|shp-&gt;shm_flags
comma
id|shp-&gt;shm_segsz
comma
id|shp-&gt;shm_cprid
comma
id|shp-&gt;shm_lprid
comma
id|shp-&gt;shm_nattch
comma
id|shp-&gt;shm_perm.uid
comma
id|shp-&gt;shm_perm.gid
comma
id|shp-&gt;shm_perm.cuid
comma
id|shp-&gt;shm_perm.cgid
comma
id|shp-&gt;shm_atim
comma
id|shp-&gt;shm_dtim
comma
id|shp-&gt;shm_ctim
)paren
suffix:semicolon
id|shm_unlock
c_func
(paren
id|i
)paren
suffix:semicolon
id|pos
op_add_assign
id|len
suffix:semicolon
r_if
c_cond
(paren
id|pos
OL
id|offset
)paren
(brace
id|len
op_assign
l_int|0
suffix:semicolon
id|begin
op_assign
id|pos
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pos
OG
id|offset
op_plus
id|length
)paren
(brace
r_goto
id|done
suffix:semicolon
)brace
)brace
)brace
op_star
id|eof
op_assign
l_int|1
suffix:semicolon
id|done
suffix:colon
id|up
c_func
(paren
op_amp
id|shm_ids.sem
)paren
suffix:semicolon
op_star
id|start
op_assign
id|buffer
op_plus
(paren
id|offset
op_minus
id|begin
)paren
suffix:semicolon
id|len
op_sub_assign
(paren
id|offset
op_minus
id|begin
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|length
)paren
(brace
id|len
op_assign
id|length
suffix:semicolon
)brace
r_if
c_cond
(paren
id|len
OL
l_int|0
)paren
(brace
id|len
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|len
suffix:semicolon
)brace
macro_line|#endif
eof
