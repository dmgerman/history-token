macro_line|#ifndef _AFFS_FS_I
DECL|macro|_AFFS_FS_I
mdefine_line|#define _AFFS_FS_I
macro_line|#include &lt;linux/a.out.h&gt;
singleline_comment|// move this to linux/coda.h!!!
macro_line|#include &lt;linux/time.h&gt;
DECL|macro|AFFS_CACHE_SIZE
mdefine_line|#define AFFS_CACHE_SIZE&t;&t;PAGE_SIZE
singleline_comment|//#define AFFS_CACHE_SIZE&t;&t;(4*4)
DECL|macro|AFFS_MAX_PREALLOC
mdefine_line|#define AFFS_MAX_PREALLOC&t;32
DECL|macro|AFFS_LC_SIZE
mdefine_line|#define AFFS_LC_SIZE&t;&t;(AFFS_CACHE_SIZE/sizeof(u32)/2)
DECL|macro|AFFS_AC_SIZE
mdefine_line|#define AFFS_AC_SIZE&t;&t;(AFFS_CACHE_SIZE/sizeof(struct affs_ext_key)/2)
DECL|macro|AFFS_AC_MASK
mdefine_line|#define AFFS_AC_MASK&t;&t;(AFFS_AC_SIZE-1)
DECL|struct|affs_ext_key
r_struct
id|affs_ext_key
(brace
DECL|member|ext
id|u32
id|ext
suffix:semicolon
multiline_comment|/* idx of the extended block */
DECL|member|key
id|u32
id|key
suffix:semicolon
multiline_comment|/* block number */
)brace
suffix:semicolon
multiline_comment|/*&n; * affs fs inode data in memory&n; */
DECL|struct|affs_inode_info
r_struct
id|affs_inode_info
(brace
DECL|member|i_opencnt
id|u32
id|i_opencnt
suffix:semicolon
DECL|member|i_link_lock
r_struct
id|semaphore
id|i_link_lock
suffix:semicolon
multiline_comment|/* Protects internal inode access. */
DECL|member|i_ext_lock
r_struct
id|semaphore
id|i_ext_lock
suffix:semicolon
multiline_comment|/* Protects internal inode access. */
DECL|macro|i_hash_lock
mdefine_line|#define i_hash_lock i_ext_lock
DECL|member|i_blkcnt
id|u32
id|i_blkcnt
suffix:semicolon
multiline_comment|/* block count */
DECL|member|i_extcnt
id|u32
id|i_extcnt
suffix:semicolon
multiline_comment|/* extended block count */
DECL|member|i_lc
id|u32
op_star
id|i_lc
suffix:semicolon
multiline_comment|/* linear cache of extended blocks */
DECL|member|i_lc_size
id|u32
id|i_lc_size
suffix:semicolon
DECL|member|i_lc_shift
id|u32
id|i_lc_shift
suffix:semicolon
DECL|member|i_lc_mask
id|u32
id|i_lc_mask
suffix:semicolon
DECL|member|i_ac
r_struct
id|affs_ext_key
op_star
id|i_ac
suffix:semicolon
multiline_comment|/* associative cache of extended blocks */
DECL|member|i_ext_last
id|u32
id|i_ext_last
suffix:semicolon
multiline_comment|/* last accessed extended block */
DECL|member|i_ext_bh
r_struct
id|buffer_head
op_star
id|i_ext_bh
suffix:semicolon
multiline_comment|/* bh of last extended block */
DECL|member|mmu_private
r_int
r_int
id|mmu_private
suffix:semicolon
DECL|member|i_protect
id|u32
id|i_protect
suffix:semicolon
multiline_comment|/* unused attribute bits */
DECL|member|i_lastalloc
id|u32
id|i_lastalloc
suffix:semicolon
multiline_comment|/* last allocated block */
DECL|member|i_pa_cnt
r_int
id|i_pa_cnt
suffix:semicolon
multiline_comment|/* number of preallocated blocks */
macro_line|#if 0
id|s32
id|i_original
suffix:semicolon
multiline_comment|/* if != 0, this is the key of the original */
id|u32
id|i_data
(braket
id|AFFS_MAX_PREALLOC
)braket
suffix:semicolon
multiline_comment|/* preallocated blocks */
r_int
id|i_cache_users
suffix:semicolon
multiline_comment|/* Cache cannot be freed while &gt; 0 */
r_int
r_char
id|i_hlink
suffix:semicolon
multiline_comment|/* This is a fake */
r_int
r_char
id|i_pad
suffix:semicolon
id|s32
id|i_parent
suffix:semicolon
multiline_comment|/* parent ino */
macro_line|#endif
)brace
suffix:semicolon
multiline_comment|/* short cut to get to the affs specific inode data */
DECL|macro|AFFS_INODE
mdefine_line|#define AFFS_INODE&t;(&amp;inode-&gt;u.affs_i)
DECL|macro|AFFS_DIR
mdefine_line|#define AFFS_DIR&t;(&amp;dir-&gt;u.affs_i)
macro_line|#endif
eof
