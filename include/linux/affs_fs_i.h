macro_line|#ifndef _AFFS_FS_I
DECL|macro|_AFFS_FS_I
mdefine_line|#define _AFFS_FS_I
macro_line|#include &lt;linux/a.out.h&gt;
macro_line|#include &lt;linux/time.h&gt;
DECL|macro|AFFS_MAX_PREALLOC
mdefine_line|#define AFFS_MAX_PREALLOC&t;16&t;/* MUST be a power of 2 */
DECL|macro|AFFS_KCSIZE
mdefine_line|#define AFFS_KCSIZE&t;&t;73&t;/* Allows for 1 extension block at 512 byte-blocks */
DECL|struct|key_cache
r_struct
id|key_cache
(brace
DECL|member|kc_lru_time
r_struct
id|timeval
id|kc_lru_time
suffix:semicolon
multiline_comment|/* Last time this cache was used */
DECL|member|kc_first
id|s32
id|kc_first
suffix:semicolon
multiline_comment|/* First cached key */
DECL|member|kc_last
id|s32
id|kc_last
suffix:semicolon
multiline_comment|/* Last cached key */
DECL|member|kc_this_key
id|s32
id|kc_this_key
suffix:semicolon
multiline_comment|/* Key of extension block this data block keys are from */
DECL|member|kc_this_seq
r_int
id|kc_this_seq
suffix:semicolon
multiline_comment|/* Sequence number of this extension block */
DECL|member|kc_next_key
id|s32
id|kc_next_key
suffix:semicolon
multiline_comment|/* Key of next extension block */
DECL|member|kc_keys
id|s32
id|kc_keys
(braket
id|AFFS_KCSIZE
)braket
suffix:semicolon
multiline_comment|/* Key cache */
)brace
suffix:semicolon
DECL|macro|EC_SIZE
mdefine_line|#define EC_SIZE&t;(PAGE_SIZE - 4 * sizeof(struct key_cache) - 4) / 4
DECL|struct|ext_cache
r_struct
id|ext_cache
(brace
DECL|member|kc
r_struct
id|key_cache
id|kc
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* The 4 key caches */
DECL|member|ec
id|s32
id|ec
(braket
id|EC_SIZE
)braket
suffix:semicolon
multiline_comment|/* Keys of assorted extension blocks */
DECL|member|max_ext
r_int
id|max_ext
suffix:semicolon
multiline_comment|/* Index of last known extension block */
)brace
suffix:semicolon
multiline_comment|/*&n; * affs fs inode data in memory&n; */
DECL|struct|affs_inode_info
r_struct
id|affs_inode_info
(brace
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
DECL|member|i_parent
id|s32
id|i_parent
suffix:semicolon
multiline_comment|/* parent ino */
DECL|member|i_original
id|s32
id|i_original
suffix:semicolon
multiline_comment|/* if != 0, this is the key of the original */
DECL|member|i_data
id|s32
id|i_data
(braket
id|AFFS_MAX_PREALLOC
)braket
suffix:semicolon
multiline_comment|/* preallocated blocks */
DECL|member|i_ec
r_struct
id|ext_cache
op_star
id|i_ec
suffix:semicolon
multiline_comment|/* Cache gets allocated dynamically */
DECL|member|i_cache_users
r_int
id|i_cache_users
suffix:semicolon
multiline_comment|/* Cache cannot be freed while &gt; 0 */
DECL|member|i_lastblock
r_int
id|i_lastblock
suffix:semicolon
multiline_comment|/* last allocated block */
DECL|member|i_pa_cnt
r_int
id|i_pa_cnt
suffix:semicolon
multiline_comment|/* number of preallocated blocks */
DECL|member|i_pa_next
r_int
id|i_pa_next
suffix:semicolon
multiline_comment|/* Index of next block in i_data[] */
DECL|member|i_pa_last
r_int
id|i_pa_last
suffix:semicolon
multiline_comment|/* Index of next free slot in i_data[] */
DECL|member|i_zone
r_int
id|i_zone
suffix:semicolon
multiline_comment|/* write zone */
DECL|member|i_hlink
r_int
r_char
id|i_hlink
suffix:semicolon
multiline_comment|/* This is a fake */
DECL|member|i_pad
r_int
r_char
id|i_pad
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
