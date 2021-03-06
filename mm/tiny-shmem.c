multiline_comment|/*&n; * tiny-shmem.c: simple shmemfs and tmpfs using ramfs code&n; *&n; * Matt Mackall &lt;mpm@selenic.com&gt; January, 2004&n; * derived from mm/shmem.c and fs/ramfs/inode.c&n; *&n; * This is intended for small system where the benefits of the full&n; * shmem code (swap-backed and resource-limited) are outweighed by&n; * their complexity. On systems without swap this code should be&n; * effectively equivalent, but much lighter weight.&n; */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
macro_line|#include &lt;linux/vfs.h&gt;
macro_line|#include &lt;linux/mount.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;linux/ramfs.h&gt;
DECL|variable|tmpfs_fs_type
r_static
r_struct
id|file_system_type
id|tmpfs_fs_type
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;tmpfs&quot;
comma
dot
id|get_sb
op_assign
id|ramfs_get_sb
comma
dot
id|kill_sb
op_assign
id|kill_litter_super
comma
)brace
suffix:semicolon
DECL|variable|shm_mnt
r_static
r_struct
id|vfsmount
op_star
id|shm_mnt
suffix:semicolon
DECL|function|init_tmpfs
r_static
r_int
id|__init
id|init_tmpfs
c_func
(paren
r_void
)paren
(brace
id|register_filesystem
c_func
(paren
op_amp
id|tmpfs_fs_type
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_TMPFS
id|devfs_mk_dir
c_func
(paren
l_string|&quot;shm&quot;
)paren
suffix:semicolon
macro_line|#endif
id|shm_mnt
op_assign
id|kern_mount
c_func
(paren
op_amp
id|tmpfs_fs_type
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|module_init
id|module_init
c_func
(paren
id|init_tmpfs
)paren
multiline_comment|/*&n; * shmem_file_setup - get an unlinked file living in tmpfs&n; *&n; * @name: name for dentry (to be seen in /proc/&lt;pid&gt;/maps&n; * @size: size to be set for the file&n; *&n; */
r_struct
id|file
op_star
id|shmem_file_setup
c_func
(paren
r_char
op_star
id|name
comma
id|loff_t
id|size
comma
r_int
r_int
id|flags
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
id|inode
op_star
id|inode
suffix:semicolon
r_struct
id|dentry
op_star
id|dentry
comma
op_star
id|root
suffix:semicolon
r_struct
id|qstr
id|this
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|shm_mnt
)paren
)paren
r_return
(paren
r_void
op_star
)paren
id|shm_mnt
suffix:semicolon
id|error
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|this.name
op_assign
id|name
suffix:semicolon
id|this.len
op_assign
id|strlen
c_func
(paren
id|name
)paren
suffix:semicolon
id|this.hash
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* will go */
id|root
op_assign
id|shm_mnt-&gt;mnt_root
suffix:semicolon
id|dentry
op_assign
id|d_alloc
c_func
(paren
id|root
comma
op_amp
id|this
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dentry
)paren
r_goto
id|put_memory
suffix:semicolon
id|error
op_assign
op_minus
id|ENFILE
suffix:semicolon
id|file
op_assign
id|get_empty_filp
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|file
)paren
r_goto
id|put_dentry
suffix:semicolon
id|error
op_assign
op_minus
id|ENOSPC
suffix:semicolon
id|inode
op_assign
id|ramfs_get_inode
c_func
(paren
id|root-&gt;d_sb
comma
id|S_IFREG
op_or
id|S_IRWXUGO
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
r_goto
id|close_file
suffix:semicolon
id|d_instantiate
c_func
(paren
id|dentry
comma
id|inode
)paren
suffix:semicolon
id|inode-&gt;i_size
op_assign
id|size
suffix:semicolon
id|inode-&gt;i_nlink
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* It is unlinked */
id|file-&gt;f_vfsmnt
op_assign
id|mntget
c_func
(paren
id|shm_mnt
)paren
suffix:semicolon
id|file-&gt;f_dentry
op_assign
id|dentry
suffix:semicolon
id|file-&gt;f_mapping
op_assign
id|inode-&gt;i_mapping
suffix:semicolon
id|file-&gt;f_op
op_assign
op_amp
id|ramfs_file_operations
suffix:semicolon
id|file-&gt;f_mode
op_assign
id|FMODE_WRITE
op_or
id|FMODE_READ
suffix:semicolon
r_return
id|file
suffix:semicolon
id|close_file
suffix:colon
id|put_filp
c_func
(paren
id|file
)paren
suffix:semicolon
id|put_dentry
suffix:colon
id|dput
c_func
(paren
id|dentry
)paren
suffix:semicolon
id|put_memory
suffix:colon
r_return
id|ERR_PTR
c_func
(paren
id|error
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * shmem_zero_setup - setup a shared anonymous mapping&n; *&n; * @vma: the vma to be mmapped is prepared by do_mmap_pgoff&n; */
DECL|function|shmem_zero_setup
r_int
id|shmem_zero_setup
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
)paren
(brace
r_struct
id|file
op_star
id|file
suffix:semicolon
id|loff_t
id|size
op_assign
id|vma-&gt;vm_end
op_minus
id|vma-&gt;vm_start
suffix:semicolon
id|file
op_assign
id|shmem_file_setup
c_func
(paren
l_string|&quot;dev/zero&quot;
comma
id|size
comma
id|vma-&gt;vm_flags
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
r_return
id|PTR_ERR
c_func
(paren
id|file
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vma-&gt;vm_file
)paren
id|fput
c_func
(paren
id|vma-&gt;vm_file
)paren
suffix:semicolon
id|vma-&gt;vm_file
op_assign
id|file
suffix:semicolon
id|vma-&gt;vm_ops
op_assign
op_amp
id|generic_file_vm_ops
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|shmem_unuse
r_int
id|shmem_unuse
c_func
(paren
id|swp_entry_t
id|entry
comma
r_struct
id|page
op_star
id|page
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
eof
