macro_line|#ifndef _LINUX_DEVFS_FS_KERNEL_H
DECL|macro|_LINUX_DEVFS_FS_KERNEL_H
mdefine_line|#define _LINUX_DEVFS_FS_KERNEL_H
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/kdev_t.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
DECL|macro|DEVFS_SUPER_MAGIC
mdefine_line|#define DEVFS_SUPER_MAGIC                0x1373
DECL|macro|DEVFS_FL_NONE
mdefine_line|#define DEVFS_FL_NONE           0x000 /* This helps to make code more readable&n;&t;&t;&t;&t;       */
DECL|macro|DEVFS_FL_AUTO_DEVNUM
mdefine_line|#define DEVFS_FL_AUTO_DEVNUM    0x002 /* Automatically generate device number&n;&t;&t;&t;&t;       */
DECL|macro|DEVFS_FL_REMOVABLE
mdefine_line|#define DEVFS_FL_REMOVABLE      0x008 /* This is a removable media device    */
DECL|macro|DEVFS_FL_WAIT
mdefine_line|#define DEVFS_FL_WAIT           0x010 /* Wait for devfsd to finish           */
DECL|macro|DEVFS_FL_CURRENT_OWNER
mdefine_line|#define DEVFS_FL_CURRENT_OWNER  0x020 /* Set initial ownership to current    */
DECL|macro|DEVFS_FL_DEFAULT
mdefine_line|#define DEVFS_FL_DEFAULT        DEVFS_FL_NONE
DECL|macro|DEVFS_SPECIAL_CHR
mdefine_line|#define DEVFS_SPECIAL_CHR     0
DECL|macro|DEVFS_SPECIAL_BLK
mdefine_line|#define DEVFS_SPECIAL_BLK     1
DECL|typedef|devfs_handle_t
r_typedef
r_struct
id|devfs_entry
op_star
id|devfs_handle_t
suffix:semicolon
macro_line|#ifdef CONFIG_DEVFS_FS
r_extern
r_void
id|devfs_remove
c_func
(paren
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
id|__attribute__
c_func
(paren
(paren
id|format
(paren
id|printf
comma
l_int|1
comma
l_int|2
)paren
)paren
)paren
suffix:semicolon
DECL|struct|unique_numspace
r_struct
id|unique_numspace
(brace
DECL|member|init_lock
id|spinlock_t
id|init_lock
suffix:semicolon
DECL|member|sem_initialised
r_int
r_char
id|sem_initialised
suffix:semicolon
DECL|member|num_free
r_int
r_int
id|num_free
suffix:semicolon
multiline_comment|/*  Num free in bits       */
DECL|member|length
r_int
r_int
id|length
suffix:semicolon
multiline_comment|/*  Array length in bytes  */
DECL|member|bits
r_int
r_int
op_star
id|bits
suffix:semicolon
DECL|member|semaphore
r_struct
id|semaphore
id|semaphore
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|UNIQUE_NUMBERSPACE_INITIALISER
mdefine_line|#define UNIQUE_NUMBERSPACE_INITIALISER {SPIN_LOCK_UNLOCKED, 0, 0, 0, NULL}
r_extern
r_void
id|devfs_put
(paren
id|devfs_handle_t
id|de
)paren
suffix:semicolon
r_extern
id|devfs_handle_t
id|devfs_register
(paren
id|devfs_handle_t
id|dir
comma
r_const
r_char
op_star
id|name
comma
r_int
r_int
id|flags
comma
r_int
r_int
id|major
comma
r_int
r_int
id|minor
comma
id|umode_t
id|mode
comma
r_void
op_star
id|ops
comma
r_void
op_star
id|info
)paren
suffix:semicolon
r_extern
r_void
id|devfs_unregister
(paren
id|devfs_handle_t
id|de
)paren
suffix:semicolon
r_extern
r_int
id|devfs_mk_symlink
(paren
id|devfs_handle_t
id|dir
comma
r_const
r_char
op_star
id|name
comma
r_int
r_int
id|flags
comma
r_const
r_char
op_star
id|link
comma
id|devfs_handle_t
op_star
id|handle
comma
r_void
op_star
id|info
)paren
suffix:semicolon
r_extern
id|devfs_handle_t
id|devfs_mk_dir
(paren
id|devfs_handle_t
id|dir
comma
r_const
r_char
op_star
id|name
comma
r_void
op_star
id|info
)paren
suffix:semicolon
r_extern
id|devfs_handle_t
id|devfs_get_handle
(paren
id|devfs_handle_t
id|dir
comma
r_const
r_char
op_star
id|name
comma
r_int
id|traverse_symlinks
)paren
suffix:semicolon
r_extern
id|devfs_handle_t
id|devfs_get_handle_from_inode
(paren
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
r_extern
r_int
id|devfs_generate_path
(paren
id|devfs_handle_t
id|de
comma
r_char
op_star
id|path
comma
r_int
id|buflen
)paren
suffix:semicolon
r_extern
r_int
id|devfs_set_file_size
(paren
id|devfs_handle_t
id|de
comma
r_int
r_int
id|size
)paren
suffix:semicolon
r_extern
r_void
op_star
id|devfs_get_info
(paren
id|devfs_handle_t
id|de
)paren
suffix:semicolon
r_extern
r_int
id|devfs_set_info
(paren
id|devfs_handle_t
id|de
comma
r_void
op_star
id|info
)paren
suffix:semicolon
r_extern
id|devfs_handle_t
id|devfs_get_parent
(paren
id|devfs_handle_t
id|de
)paren
suffix:semicolon
r_extern
id|devfs_handle_t
id|devfs_get_first_child
(paren
id|devfs_handle_t
id|de
)paren
suffix:semicolon
r_extern
id|devfs_handle_t
id|devfs_get_next_sibling
(paren
id|devfs_handle_t
id|de
)paren
suffix:semicolon
r_extern
r_const
r_char
op_star
id|devfs_get_name
(paren
id|devfs_handle_t
id|de
comma
r_int
r_int
op_star
id|namelen
)paren
suffix:semicolon
r_extern
r_int
id|devfs_only
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|devfs_register_tape
(paren
id|devfs_handle_t
id|de
)paren
suffix:semicolon
r_extern
r_void
id|devfs_unregister_tape
c_func
(paren
r_int
id|num
)paren
suffix:semicolon
r_extern
r_void
id|devfs_register_series
(paren
id|devfs_handle_t
id|dir
comma
r_const
r_char
op_star
id|format
comma
r_int
r_int
id|num_entries
comma
r_int
r_int
id|flags
comma
r_int
r_int
id|major
comma
r_int
r_int
id|minor_start
comma
id|umode_t
id|mode
comma
r_void
op_star
id|ops
comma
r_void
op_star
id|info
)paren
suffix:semicolon
r_extern
r_int
id|devfs_alloc_major
(paren
r_char
id|type
)paren
suffix:semicolon
r_extern
r_void
id|devfs_dealloc_major
(paren
r_char
id|type
comma
r_int
id|major
)paren
suffix:semicolon
r_extern
id|kdev_t
id|devfs_alloc_devnum
(paren
r_char
id|type
)paren
suffix:semicolon
r_extern
r_void
id|devfs_dealloc_devnum
(paren
r_char
id|type
comma
id|kdev_t
id|devnum
)paren
suffix:semicolon
r_extern
r_int
id|devfs_alloc_unique_number
(paren
r_struct
id|unique_numspace
op_star
id|space
)paren
suffix:semicolon
r_extern
r_void
id|devfs_dealloc_unique_number
(paren
r_struct
id|unique_numspace
op_star
id|space
comma
r_int
id|number
)paren
suffix:semicolon
r_extern
r_void
id|mount_devfs_fs
(paren
r_void
)paren
suffix:semicolon
macro_line|#else  /*  CONFIG_DEVFS_FS  */
DECL|struct|unique_numspace
r_struct
id|unique_numspace
(brace
DECL|member|dummy
r_char
id|dummy
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|UNIQUE_NUMBERSPACE_INITIALISER
mdefine_line|#define UNIQUE_NUMBERSPACE_INITIALISER {0}
DECL|function|devfs_put
r_static
r_inline
r_void
id|devfs_put
(paren
id|devfs_handle_t
id|de
)paren
(brace
r_return
suffix:semicolon
)brace
DECL|function|devfs_register
r_static
r_inline
id|devfs_handle_t
id|devfs_register
(paren
id|devfs_handle_t
id|dir
comma
r_const
r_char
op_star
id|name
comma
r_int
r_int
id|flags
comma
r_int
r_int
id|major
comma
r_int
r_int
id|minor
comma
id|umode_t
id|mode
comma
r_void
op_star
id|ops
comma
r_void
op_star
id|info
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|devfs_unregister
r_static
r_inline
r_void
id|devfs_unregister
(paren
id|devfs_handle_t
id|de
)paren
(brace
r_return
suffix:semicolon
)brace
DECL|function|devfs_mk_symlink
r_static
r_inline
r_int
id|devfs_mk_symlink
(paren
id|devfs_handle_t
id|dir
comma
r_const
r_char
op_star
id|name
comma
r_int
r_int
id|flags
comma
r_const
r_char
op_star
id|link
comma
id|devfs_handle_t
op_star
id|handle
comma
r_void
op_star
id|info
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|devfs_mk_dir
r_static
r_inline
id|devfs_handle_t
id|devfs_mk_dir
(paren
id|devfs_handle_t
id|dir
comma
r_const
r_char
op_star
id|name
comma
r_void
op_star
id|info
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|devfs_get_handle
r_static
r_inline
id|devfs_handle_t
id|devfs_get_handle
(paren
id|devfs_handle_t
id|dir
comma
r_const
r_char
op_star
id|name
comma
r_int
id|traverse_symlinks
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|devfs_remove
r_static
r_inline
r_void
id|devfs_remove
c_func
(paren
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
(brace
)brace
DECL|function|devfs_get_handle_from_inode
r_static
r_inline
id|devfs_handle_t
id|devfs_get_handle_from_inode
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|devfs_generate_path
r_static
r_inline
r_int
id|devfs_generate_path
(paren
id|devfs_handle_t
id|de
comma
r_char
op_star
id|path
comma
r_int
id|buflen
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
DECL|function|devfs_set_file_size
r_static
r_inline
r_int
id|devfs_set_file_size
(paren
id|devfs_handle_t
id|de
comma
r_int
r_int
id|size
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
DECL|function|devfs_get_info
r_static
r_inline
r_void
op_star
id|devfs_get_info
(paren
id|devfs_handle_t
id|de
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|devfs_set_info
r_static
r_inline
r_int
id|devfs_set_info
(paren
id|devfs_handle_t
id|de
comma
r_void
op_star
id|info
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|devfs_get_parent
r_static
r_inline
id|devfs_handle_t
id|devfs_get_parent
(paren
id|devfs_handle_t
id|de
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|devfs_get_first_child
r_static
r_inline
id|devfs_handle_t
id|devfs_get_first_child
(paren
id|devfs_handle_t
id|de
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|devfs_get_next_sibling
r_static
r_inline
id|devfs_handle_t
id|devfs_get_next_sibling
(paren
id|devfs_handle_t
id|de
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|devfs_get_name
r_static
r_inline
r_const
r_char
op_star
id|devfs_get_name
(paren
id|devfs_handle_t
id|de
comma
r_int
r_int
op_star
id|namelen
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|devfs_only
r_static
r_inline
r_int
id|devfs_only
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|devfs_register_tape
r_static
r_inline
r_int
id|devfs_register_tape
(paren
id|devfs_handle_t
id|de
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|devfs_unregister_tape
r_static
r_inline
r_void
id|devfs_unregister_tape
c_func
(paren
r_int
id|num
)paren
(brace
)brace
DECL|function|devfs_register_series
r_static
r_inline
r_void
id|devfs_register_series
(paren
id|devfs_handle_t
id|dir
comma
r_const
r_char
op_star
id|format
comma
r_int
r_int
id|num_entries
comma
r_int
r_int
id|flags
comma
r_int
r_int
id|major
comma
r_int
r_int
id|minor_start
comma
id|umode_t
id|mode
comma
r_void
op_star
id|ops
comma
r_void
op_star
id|info
)paren
(brace
r_return
suffix:semicolon
)brace
DECL|function|devfs_alloc_major
r_static
r_inline
r_int
id|devfs_alloc_major
(paren
r_char
id|type
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|devfs_dealloc_major
r_static
r_inline
r_void
id|devfs_dealloc_major
(paren
r_char
id|type
comma
r_int
id|major
)paren
(brace
r_return
suffix:semicolon
)brace
DECL|function|devfs_alloc_devnum
r_static
r_inline
id|kdev_t
id|devfs_alloc_devnum
(paren
r_char
id|type
)paren
(brace
r_return
id|NODEV
suffix:semicolon
)brace
DECL|function|devfs_dealloc_devnum
r_static
r_inline
r_void
id|devfs_dealloc_devnum
(paren
r_char
id|type
comma
id|kdev_t
id|devnum
)paren
(brace
r_return
suffix:semicolon
)brace
DECL|function|devfs_alloc_unique_number
r_static
r_inline
r_int
id|devfs_alloc_unique_number
(paren
r_struct
id|unique_numspace
op_star
id|space
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|devfs_dealloc_unique_number
r_static
r_inline
r_void
id|devfs_dealloc_unique_number
(paren
r_struct
id|unique_numspace
op_star
id|space
comma
r_int
id|number
)paren
(brace
r_return
suffix:semicolon
)brace
DECL|function|mount_devfs_fs
r_static
r_inline
r_void
id|mount_devfs_fs
(paren
r_void
)paren
(brace
r_return
suffix:semicolon
)brace
macro_line|#endif  /*  CONFIG_DEVFS_FS  */
macro_line|#endif  /*  _LINUX_DEVFS_FS_KERNEL_H  */
eof
