macro_line|#ifndef __SHMEM_FS_H
DECL|macro|__SHMEM_FS_H
mdefine_line|#define __SHMEM_FS_H
macro_line|#include &lt;linux/swap.h&gt;
multiline_comment|/* inode in-kernel data */
DECL|macro|SHMEM_NR_DIRECT
mdefine_line|#define SHMEM_NR_DIRECT 16
r_extern
id|atomic_t
id|shmem_nrpages
suffix:semicolon
DECL|struct|shmem_inode_info
r_struct
id|shmem_inode_info
(brace
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|sem
r_struct
id|semaphore
id|sem
suffix:semicolon
DECL|member|next_index
r_int
r_int
id|next_index
suffix:semicolon
DECL|member|i_direct
id|swp_entry_t
id|i_direct
(braket
id|SHMEM_NR_DIRECT
)braket
suffix:semicolon
multiline_comment|/* for the first blocks */
DECL|member|i_indirect
r_void
op_star
op_star
id|i_indirect
suffix:semicolon
multiline_comment|/* indirect blocks */
DECL|member|swapped
r_int
r_int
id|swapped
suffix:semicolon
DECL|member|locked
r_int
id|locked
suffix:semicolon
multiline_comment|/* into memory */
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|vfs_inode
r_struct
id|inode
id|vfs_inode
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|shmem_sb_info
r_struct
id|shmem_sb_info
(brace
DECL|member|max_blocks
r_int
r_int
id|max_blocks
suffix:semicolon
multiline_comment|/* How many blocks are allowed */
DECL|member|free_blocks
r_int
r_int
id|free_blocks
suffix:semicolon
multiline_comment|/* How many are left for allocation */
DECL|member|max_inodes
r_int
r_int
id|max_inodes
suffix:semicolon
multiline_comment|/* How many inodes are allowed */
DECL|member|free_inodes
r_int
r_int
id|free_inodes
suffix:semicolon
multiline_comment|/* How many are left for allocation */
DECL|member|stat_lock
id|spinlock_t
id|stat_lock
suffix:semicolon
)brace
suffix:semicolon
DECL|function|SHMEM_I
r_static
r_inline
r_struct
id|shmem_inode_info
op_star
id|SHMEM_I
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_return
id|list_entry
c_func
(paren
id|inode
comma
r_struct
id|shmem_inode_info
comma
id|vfs_inode
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
