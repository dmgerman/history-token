multiline_comment|/*&n; * Copyright 1996, 1997, 1998 Hans Reiser, see reiserfs/README for licensing and copyright details&n; */
multiline_comment|/* this file has an amazingly stupid&n;                                   name, yura please fix it to be&n;                                   reiserfs.h, and merge all the rest&n;                                   of our .h files that are in this&n;                                   directory into it.  */
macro_line|#ifndef _LINUX_REISER_FS_H
DECL|macro|_LINUX_REISER_FS_H
mdefine_line|#define _LINUX_REISER_FS_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/tqueue.h&gt;
macro_line|#include &lt;asm/unaligned.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/reiserfs_fs_i.h&gt;
macro_line|#endif
multiline_comment|/*&n; *  include/linux/reiser_fs.h&n; *&n; *  Reiser File System constants and structures&n; *&n; */
multiline_comment|/* in reading the #defines, it may help to understand that they employ&n;   the following abbreviations:&n;&n;   B = Buffer&n;   I = Item header&n;   H = Height within the tree (should be changed to LEV)&n;   N = Number of the item in the node&n;   STAT = stat data&n;   DEH = Directory Entry Header&n;   EC = Entry Count&n;   E = Entry number&n;   UL = Unsigned Long&n;   BLKH = BLocK Header&n;   UNFM = UNForMatted node&n;   DC = Disk Child&n;   P = Path&n;&n;   These #defines are named by concatenating these abbreviations,&n;   where first comes the arguments, and last comes the return value,&n;   of the macro.&n;&n;*/
DECL|macro|USE_INODE_GENERATION_COUNTER
mdefine_line|#define USE_INODE_GENERATION_COUNTER
DECL|macro|REISERFS_PREALLOCATE
mdefine_line|#define REISERFS_PREALLOCATE
DECL|macro|PREALLOCATION_SIZE
mdefine_line|#define PREALLOCATION_SIZE 8
multiline_comment|/* n must be power of 2 */
DECL|macro|_ROUND_UP
mdefine_line|#define _ROUND_UP(x,n) (((x)+(n)-1u) &amp; ~((n)-1u))
singleline_comment|// to be ok for alpha and others we have to align structures to 8 byte
singleline_comment|// boundary.
singleline_comment|// FIXME: do not change 4 by anything else: there is code which relies on that
DECL|macro|ROUND_UP
mdefine_line|#define ROUND_UP(x) _ROUND_UP(x,8LL)
multiline_comment|/* debug levels.  Right now, CONFIG_REISERFS_CHECK means print all debug&n;** messages.&n;*/
DECL|macro|REISERFS_DEBUG_CODE
mdefine_line|#define REISERFS_DEBUG_CODE 5 /* extra messages to help find/debug errors */ 
multiline_comment|/* assertions handling */
multiline_comment|/** always check a condition and panic if it&squot;s false. */
DECL|macro|RASSERT
mdefine_line|#define RASSERT( cond, format, args... )&t;&t;&t;&t;&t;&bslash;&n;if( !( cond ) ) &t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  reiserfs_panic( 0, &quot;reiserfs[%i]: assertion &quot; #cond &quot; failed at &quot;&t;&t;&bslash;&n;&t;&t;  __FILE__ &quot;:%i:&quot; __FUNCTION__ &quot;: &quot; format &quot;&bslash;n&quot;,&t;&t;&bslash;&n;&t;&t;  in_interrupt() ? -1 : current -&gt; pid, __LINE__ , ##args )
macro_line|#if defined( CONFIG_REISERFS_CHECK )
DECL|macro|RFALSE
mdefine_line|#define RFALSE( cond, format, args... ) RASSERT( !( cond ), format, ##args )
macro_line|#else
DECL|macro|RFALSE
mdefine_line|#define RFALSE( cond, format, args... ) do {;} while( 0 )
macro_line|#endif
DECL|macro|CONSTF
mdefine_line|#define CONSTF __attribute__( ( const ) )
multiline_comment|/*&n; * Disk Data Structures&n; */
multiline_comment|/***************************************************************************/
multiline_comment|/*                             SUPER BLOCK                                 */
multiline_comment|/***************************************************************************/
multiline_comment|/*&n; * Structure of super block on disk, a version of which in RAM is often accessed as s-&gt;u.reiserfs_sb.s_rs&n; * the version in RAM is part of a larger structure containing fields never written to disk.&n; */
DECL|macro|UNSET_HASH
mdefine_line|#define UNSET_HASH 0 
singleline_comment|// read_super will guess about, what hash names
singleline_comment|// in directories were sorted with
DECL|macro|TEA_HASH
mdefine_line|#define TEA_HASH  1
DECL|macro|YURA_HASH
mdefine_line|#define YURA_HASH 2
DECL|macro|R5_HASH
mdefine_line|#define R5_HASH   3
DECL|macro|DEFAULT_HASH
mdefine_line|#define DEFAULT_HASH R5_HASH
DECL|struct|journal_params
r_struct
id|journal_params
(brace
DECL|member|jp_journal_1st_block
id|__u32
id|jp_journal_1st_block
suffix:semicolon
multiline_comment|/* where does journal start from on its&n;&t;&t;&t;&t;       * device */
DECL|member|jp_journal_dev
id|__u32
id|jp_journal_dev
suffix:semicolon
multiline_comment|/* journal device st_rdev */
DECL|member|jp_journal_size
id|__u32
id|jp_journal_size
suffix:semicolon
multiline_comment|/* size of the journal */
DECL|member|jp_journal_trans_max
id|__u32
id|jp_journal_trans_max
suffix:semicolon
multiline_comment|/* max number of blocks in a transaction. */
DECL|member|jp_journal_magic
id|__u32
id|jp_journal_magic
suffix:semicolon
multiline_comment|/* random value made on fs creation (this&n;&t;&t;&t;&t;       * was sb_journal_block_count) */
DECL|member|jp_journal_max_batch
id|__u32
id|jp_journal_max_batch
suffix:semicolon
multiline_comment|/* max number of blocks to batch into a&n;&t;&t;&t;&t;       * trans */
DECL|member|jp_journal_max_commit_age
id|__u32
id|jp_journal_max_commit_age
suffix:semicolon
multiline_comment|/* in seconds, how old can an async&n;&t;&t;&t;&t;       * commit be */
DECL|member|jp_journal_max_trans_age
id|__u32
id|jp_journal_max_trans_age
suffix:semicolon
multiline_comment|/* in seconds, how old can a transaction&n;&t;&t;&t;&t;       * be */
)brace
suffix:semicolon
multiline_comment|/* this is the super from 3.5.X, where X &gt;= 10 */
DECL|struct|reiserfs_super_block_v1
r_struct
id|reiserfs_super_block_v1
(brace
DECL|member|s_block_count
id|__u32
id|s_block_count
suffix:semicolon
multiline_comment|/* blocks count         */
DECL|member|s_free_blocks
id|__u32
id|s_free_blocks
suffix:semicolon
multiline_comment|/* free blocks count    */
DECL|member|s_root_block
id|__u32
id|s_root_block
suffix:semicolon
multiline_comment|/* root block number    */
DECL|member|s_journal
r_struct
id|journal_params
id|s_journal
suffix:semicolon
DECL|member|s_blocksize
id|__u16
id|s_blocksize
suffix:semicolon
multiline_comment|/* block size */
DECL|member|s_oid_maxsize
id|__u16
id|s_oid_maxsize
suffix:semicolon
multiline_comment|/* max size of object id array, see&n;&t;&t;&t;&t;    * get_objectid() commentary  */
DECL|member|s_oid_cursize
id|__u16
id|s_oid_cursize
suffix:semicolon
multiline_comment|/* current size of object id array */
DECL|member|s_umount_state
id|__u16
id|s_umount_state
suffix:semicolon
multiline_comment|/* this is set to 1 when filesystem was&n;&t;&t;&t;&t;    * umounted, to 2 - when not */
DECL|member|s_magic
r_char
id|s_magic
(braket
l_int|10
)braket
suffix:semicolon
multiline_comment|/* reiserfs magic string indicates that&n;&t;&t;&t;&t;    * file system is reiserfs:&n;&t;&t;&t;&t;    * &quot;ReIsErFs&quot; or &quot;ReIsEr2Fs&quot; or &quot;ReIsEr3Fs&quot; */
DECL|member|s_fs_state
id|__u16
id|s_fs_state
suffix:semicolon
multiline_comment|/* it is set to used by fsck to mark which&n;&t;&t;&t;&t;    * phase of rebuilding is done */
DECL|member|s_hash_function_code
id|__u32
id|s_hash_function_code
suffix:semicolon
multiline_comment|/* indicate, what hash function is being use&n;&t;&t;&t;&t;    * to sort names in a directory*/
DECL|member|s_tree_height
id|__u16
id|s_tree_height
suffix:semicolon
multiline_comment|/* height of disk tree */
DECL|member|s_bmap_nr
id|__u16
id|s_bmap_nr
suffix:semicolon
multiline_comment|/* amount of bitmap blocks needed to address&n;&t;&t;&t;&t;    * each block of file system */
DECL|member|s_version
id|__u16
id|s_version
suffix:semicolon
multiline_comment|/* this field is only reliable on filesystem&n;&t;&t;&t;&t;    * with non-standard journal */
DECL|member|s_reserved_for_journal
id|__u16
id|s_reserved_for_journal
suffix:semicolon
multiline_comment|/* size in blocks of journal area on main&n;&t;&t;&t;&t;    * device, we need to keep after&n;&t;&t;&t;&t;    * making fs with non-standard journal */
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
suffix:semicolon
DECL|macro|SB_SIZE_V1
mdefine_line|#define SB_SIZE_V1 (sizeof(struct reiserfs_super_block_v1))
multiline_comment|/* this is the on disk super block */
DECL|struct|reiserfs_super_block
r_struct
id|reiserfs_super_block
(brace
DECL|member|s_v1
r_struct
id|reiserfs_super_block_v1
id|s_v1
suffix:semicolon
DECL|member|s_inode_generation
id|__u32
id|s_inode_generation
suffix:semicolon
DECL|member|s_flags
id|__u32
id|s_flags
suffix:semicolon
multiline_comment|/* Right now used only by inode-attributes, if enabled */
DECL|member|s_uuid
r_int
r_char
id|s_uuid
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* filesystem unique identifier */
DECL|member|s_label
r_int
r_char
id|s_label
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* filesystem volume label */
DECL|member|s_unused
r_char
id|s_unused
(braket
l_int|88
)braket
suffix:semicolon
multiline_comment|/* zero filled by mkreiserfs and&n;&t;&t;&t;&t;     * reiserfs_convert_objectid_map_v1()&n;&t;&t;&t;&t;     * so any additions must be updated&n;&t;&t;&t;&t;     * there as well. */
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
suffix:semicolon
DECL|macro|SB_SIZE
mdefine_line|#define SB_SIZE (sizeof(struct reiserfs_super_block))
DECL|macro|REISERFS_VERSION_1
mdefine_line|#define REISERFS_VERSION_1 0
DECL|macro|REISERFS_VERSION_2
mdefine_line|#define REISERFS_VERSION_2 2
singleline_comment|// on-disk super block fields converted to cpu form
DECL|macro|SB_DISK_SUPER_BLOCK
mdefine_line|#define SB_DISK_SUPER_BLOCK(s) ((s)-&gt;u.reiserfs_sb.s_rs)
DECL|macro|SB_V1_DISK_SUPER_BLOCK
mdefine_line|#define SB_V1_DISK_SUPER_BLOCK(s) (&amp;(SB_DISK_SUPER_BLOCK(s)-&gt;s_v1))
DECL|macro|SB_BLOCKSIZE
mdefine_line|#define SB_BLOCKSIZE(s) &bslash;&n;        le32_to_cpu ((SB_V1_DISK_SUPER_BLOCK(s)-&gt;s_blocksize))
DECL|macro|SB_BLOCK_COUNT
mdefine_line|#define SB_BLOCK_COUNT(s) &bslash;&n;        le32_to_cpu ((SB_V1_DISK_SUPER_BLOCK(s)-&gt;s_block_count))
DECL|macro|SB_FREE_BLOCKS
mdefine_line|#define SB_FREE_BLOCKS(s) &bslash;&n;        le32_to_cpu ((SB_V1_DISK_SUPER_BLOCK(s)-&gt;s_free_blocks))
DECL|macro|SB_REISERFS_MAGIC
mdefine_line|#define SB_REISERFS_MAGIC(s) &bslash;&n;        (SB_V1_DISK_SUPER_BLOCK(s)-&gt;s_magic)
DECL|macro|SB_ROOT_BLOCK
mdefine_line|#define SB_ROOT_BLOCK(s) &bslash;&n;        le32_to_cpu ((SB_V1_DISK_SUPER_BLOCK(s)-&gt;s_root_block))
DECL|macro|SB_TREE_HEIGHT
mdefine_line|#define SB_TREE_HEIGHT(s) &bslash;&n;        le16_to_cpu ((SB_V1_DISK_SUPER_BLOCK(s)-&gt;s_tree_height))
DECL|macro|SB_REISERFS_STATE
mdefine_line|#define SB_REISERFS_STATE(s) &bslash;&n;        le16_to_cpu ((SB_V1_DISK_SUPER_BLOCK(s)-&gt;s_umount_state))
DECL|macro|SB_VERSION
mdefine_line|#define SB_VERSION(s) le16_to_cpu ((SB_V1_DISK_SUPER_BLOCK(s)-&gt;s_version))
DECL|macro|SB_BMAP_NR
mdefine_line|#define SB_BMAP_NR(s) le16_to_cpu ((SB_V1_DISK_SUPER_BLOCK(s)-&gt;s_bmap_nr))
DECL|macro|PUT_SB_BLOCK_COUNT
mdefine_line|#define PUT_SB_BLOCK_COUNT(s, val) &bslash;&n;   do { SB_V1_DISK_SUPER_BLOCK(s)-&gt;s_block_count = cpu_to_le32(val); } while (0)
DECL|macro|PUT_SB_FREE_BLOCKS
mdefine_line|#define PUT_SB_FREE_BLOCKS(s, val) &bslash;&n;   do { SB_V1_DISK_SUPER_BLOCK(s)-&gt;s_free_blocks = cpu_to_le32(val); } while (0)
DECL|macro|PUT_SB_ROOT_BLOCK
mdefine_line|#define PUT_SB_ROOT_BLOCK(s, val) &bslash;&n;   do { SB_V1_DISK_SUPER_BLOCK(s)-&gt;s_root_block = cpu_to_le32(val); } while (0)
DECL|macro|PUT_SB_TREE_HEIGHT
mdefine_line|#define PUT_SB_TREE_HEIGHT(s, val) &bslash;&n;   do { SB_V1_DISK_SUPER_BLOCK(s)-&gt;s_tree_height = cpu_to_le16(val); } while (0)
DECL|macro|PUT_SB_REISERFS_STATE
mdefine_line|#define PUT_SB_REISERFS_STATE(s, val) &bslash;&n;   do { SB_V1_DISK_SUPER_BLOCK(s)-&gt;s_umount_state = cpu_to_le16(val); } while (0) 
DECL|macro|PUT_SB_VERSION
mdefine_line|#define PUT_SB_VERSION(s, val) &bslash;&n;   do { SB_V1_DISK_SUPER_BLOCK(s)-&gt;s_version = cpu_to_le16(val); } while (0)
DECL|macro|PUT_SB_BMAP_NR
mdefine_line|#define PUT_SB_BMAP_NR(s, val) &bslash;&n;   do { SB_V1_DISK_SUPER_BLOCK(s)-&gt;s_bmap_nr = cpu_to_le16 (val); } while (0)
DECL|macro|SB_ONDISK_JP
mdefine_line|#define SB_ONDISK_JP(s) (&amp;SB_V1_DISK_SUPER_BLOCK(s)-&gt;s_journal)
DECL|macro|SB_ONDISK_JOURNAL_SIZE
mdefine_line|#define SB_ONDISK_JOURNAL_SIZE(s) &bslash;&n;         le32_to_cpu ((SB_ONDISK_JP(s)-&gt;jp_journal_size))
DECL|macro|SB_ONDISK_JOURNAL_1st_BLOCK
mdefine_line|#define SB_ONDISK_JOURNAL_1st_BLOCK(s) &bslash;&n;         le32_to_cpu ((SB_ONDISK_JP(s)-&gt;jp_journal_1st_block))
DECL|macro|SB_ONDISK_JOURNAL_DEVICE
mdefine_line|#define SB_ONDISK_JOURNAL_DEVICE(s) &bslash;&n;         le32_to_cpu ((SB_ONDISK_JP(s)-&gt;jp_journal_dev))
DECL|macro|SB_ONDISK_RESERVED_FOR_JOURNAL
mdefine_line|#define SB_ONDISK_RESERVED_FOR_JOURNAL(s) &bslash;&n;         le32_to_cpu ((SB_V1_DISK_SUPER_BLOCK(s)-&gt;s_reserved_for_journal))
DECL|macro|is_block_in_log_or_reserved_area
mdefine_line|#define is_block_in_log_or_reserved_area(s, block) &bslash;&n;         block &gt;= SB_JOURNAL_1st_RESERVED_BLOCK(s) &bslash;&n;         &amp;&amp; block &lt; SB_JOURNAL_1st_RESERVED_BLOCK(s) +  &bslash;&n;         ((!is_reiserfs_jr(SB_DISK_SUPER_BLOCK(s)) ? &bslash;&n;         SB_ONDISK_JOURNAL_SIZE(s) + 1 : SB_ONDISK_RESERVED_FOR_JOURNAL(s))) 
multiline_comment|/* used by gcc */
DECL|macro|REISERFS_SUPER_MAGIC
mdefine_line|#define REISERFS_SUPER_MAGIC 0x52654973
multiline_comment|/* used by file system utilities that&n;                                   look at the superblock, etc. */
DECL|macro|REISERFS_SUPER_MAGIC_STRING
mdefine_line|#define REISERFS_SUPER_MAGIC_STRING &quot;ReIsErFs&quot;
DECL|macro|REISER2FS_SUPER_MAGIC_STRING
mdefine_line|#define REISER2FS_SUPER_MAGIC_STRING &quot;ReIsEr2Fs&quot;
DECL|macro|REISER2FS_JR_SUPER_MAGIC_STRING
mdefine_line|#define REISER2FS_JR_SUPER_MAGIC_STRING &quot;ReIsEr3Fs&quot;
r_extern
r_const
r_char
id|reiserfs_3_5_magic_string
(braket
)braket
suffix:semicolon
r_extern
r_const
r_char
id|reiserfs_3_6_magic_string
(braket
)braket
suffix:semicolon
r_extern
r_const
r_char
id|reiserfs_jr_magic_string
(braket
)braket
suffix:semicolon
r_int
id|is_reiserfs_3_5
(paren
r_struct
id|reiserfs_super_block
op_star
id|rs
)paren
suffix:semicolon
r_int
id|is_reiserfs_3_6
(paren
r_struct
id|reiserfs_super_block
op_star
id|rs
)paren
suffix:semicolon
r_int
id|is_reiserfs_jr
(paren
r_struct
id|reiserfs_super_block
op_star
id|rs
)paren
suffix:semicolon
multiline_comment|/* ReiserFS leaves the first 64k unused, so that partition labels have&n;   enough space.  If someone wants to write a fancy bootloader that&n;   needs more than 64k, let us know, and this will be increased in size.&n;   This number must be larger than than the largest block size on any&n;   platform, or code will break.  -Hans */
DECL|macro|REISERFS_DISK_OFFSET_IN_BYTES
mdefine_line|#define REISERFS_DISK_OFFSET_IN_BYTES (64 * 1024)
DECL|macro|REISERFS_FIRST_BLOCK
mdefine_line|#define REISERFS_FIRST_BLOCK unused_define
DECL|macro|REISERFS_JOURNAL_OFFSET_IN_BYTES
mdefine_line|#define REISERFS_JOURNAL_OFFSET_IN_BYTES REISERFS_DISK_OFFSET_IN_BYTES
multiline_comment|/* the spot for the super in versions 3.5 - 3.5.10 (inclusive) */
DECL|macro|REISERFS_OLD_DISK_OFFSET_IN_BYTES
mdefine_line|#define REISERFS_OLD_DISK_OFFSET_IN_BYTES (8 * 1024)
singleline_comment|// reiserfs internal error code (used by search_by_key adn fix_nodes))
DECL|macro|CARRY_ON
mdefine_line|#define CARRY_ON      0
DECL|macro|REPEAT_SEARCH
mdefine_line|#define REPEAT_SEARCH -1
DECL|macro|IO_ERROR
mdefine_line|#define IO_ERROR      -2
DECL|macro|NO_DISK_SPACE
mdefine_line|#define NO_DISK_SPACE -3
DECL|macro|NO_BALANCING_NEEDED
mdefine_line|#define NO_BALANCING_NEEDED  (-4)
DECL|macro|NO_MORE_UNUSED_CONTIGUOUS_BLOCKS
mdefine_line|#define NO_MORE_UNUSED_CONTIGUOUS_BLOCKS (-5)
DECL|typedef|b_blocknr_t
r_typedef
r_int
r_int
id|b_blocknr_t
suffix:semicolon
DECL|typedef|unp_t
r_typedef
id|__u32
id|unp_t
suffix:semicolon
DECL|struct|unfm_nodeinfo
r_struct
id|unfm_nodeinfo
(brace
DECL|member|unfm_nodenum
id|unp_t
id|unfm_nodenum
suffix:semicolon
DECL|member|unfm_freespace
r_int
r_int
id|unfm_freespace
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* there are two formats of keys: 3.5 and 3.6&n; */
DECL|macro|KEY_FORMAT_3_5
mdefine_line|#define KEY_FORMAT_3_5 0
DECL|macro|KEY_FORMAT_3_6
mdefine_line|#define KEY_FORMAT_3_6 1
multiline_comment|/* there are two stat datas */
DECL|macro|STAT_DATA_V1
mdefine_line|#define STAT_DATA_V1 0
DECL|macro|STAT_DATA_V2
mdefine_line|#define STAT_DATA_V2 1
DECL|function|REISERFS_I
r_static
r_inline
r_struct
id|reiserfs_inode_info
op_star
id|REISERFS_I
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
id|reiserfs_inode_info
comma
id|vfs_inode
)paren
suffix:semicolon
)brace
multiline_comment|/** this says about version of key of all items (but stat data) the&n;    object consists of */
DECL|macro|get_inode_item_key_version
mdefine_line|#define get_inode_item_key_version( inode )                                    &bslash;&n;    ((REISERFS_I(inode)-&gt;i_flags &amp; i_item_key_version_mask) ? KEY_FORMAT_3_6 : KEY_FORMAT_3_5)
DECL|macro|set_inode_item_key_version
mdefine_line|#define set_inode_item_key_version( inode, version )                           &bslash;&n;         ({ if((version)==KEY_FORMAT_3_6)                                      &bslash;&n;                REISERFS_I(inode)-&gt;i_flags |= i_item_key_version_mask;      &bslash;&n;            else                                                               &bslash;&n;                REISERFS_I(inode)-&gt;i_flags &amp;= ~i_item_key_version_mask; })
DECL|macro|get_inode_sd_version
mdefine_line|#define get_inode_sd_version(inode)                                            &bslash;&n;    ((REISERFS_I(inode)-&gt;i_flags &amp; i_stat_data_version_mask) ? STAT_DATA_V2 : STAT_DATA_V1)
DECL|macro|set_inode_sd_version
mdefine_line|#define set_inode_sd_version(inode, version)                                   &bslash;&n;         ({ if((version)==STAT_DATA_V2)                                        &bslash;&n;                REISERFS_I(inode)-&gt;i_flags |= i_stat_data_version_mask;     &bslash;&n;            else                                                               &bslash;&n;                REISERFS_I(inode)-&gt;i_flags &amp;= ~i_stat_data_version_mask; })
multiline_comment|/* This is an aggressive tail suppression policy, I am hoping it&n;   improves our benchmarks. The principle behind it is that percentage&n;   space saving is what matters, not absolute space saving.  This is&n;   non-intuitive, but it helps to understand it if you consider that the&n;   cost to access 4 blocks is not much more than the cost to access 1&n;   block, if you have to do a seek and rotate.  A tail risks a&n;   non-linear disk access that is significant as a percentage of total&n;   time cost for a 4 block file and saves an amount of space that is&n;   less significant as a percentage of space, or so goes the hypothesis.&n;   -Hans */
DECL|macro|STORE_TAIL_IN_UNFM
mdefine_line|#define STORE_TAIL_IN_UNFM(n_file_size,n_tail_size,n_block_size) &bslash;&n;(&bslash;&n;  (!(n_tail_size)) || &bslash;&n;  (((n_tail_size) &gt; MAX_DIRECT_ITEM_LEN(n_block_size)) || &bslash;&n;   ( (n_file_size) &gt;= (n_block_size) * 4 ) || &bslash;&n;   ( ( (n_file_size) &gt;= (n_block_size) * 3 ) &amp;&amp; &bslash;&n;     ( (n_tail_size) &gt;=   (MAX_DIRECT_ITEM_LEN(n_block_size))/4) ) || &bslash;&n;   ( ( (n_file_size) &gt;= (n_block_size) * 2 ) &amp;&amp; &bslash;&n;     ( (n_tail_size) &gt;=   (MAX_DIRECT_ITEM_LEN(n_block_size))/2) ) || &bslash;&n;   ( ( (n_file_size) &gt;= (n_block_size) ) &amp;&amp; &bslash;&n;     ( (n_tail_size) &gt;=   (MAX_DIRECT_ITEM_LEN(n_block_size) * 3)/4) ) ) &bslash;&n;)
multiline_comment|/*&n; * values for s_umount_state field&n; */
DECL|macro|REISERFS_VALID_FS
mdefine_line|#define REISERFS_VALID_FS    1
DECL|macro|REISERFS_ERROR_FS
mdefine_line|#define REISERFS_ERROR_FS    2
singleline_comment|//
singleline_comment|// there are 5 item types currently
singleline_comment|//
DECL|macro|TYPE_STAT_DATA
mdefine_line|#define TYPE_STAT_DATA 0
DECL|macro|TYPE_INDIRECT
mdefine_line|#define TYPE_INDIRECT 1
DECL|macro|TYPE_DIRECT
mdefine_line|#define TYPE_DIRECT 2
DECL|macro|TYPE_DIRENTRY
mdefine_line|#define TYPE_DIRENTRY 3 
DECL|macro|TYPE_MAXTYPE
mdefine_line|#define TYPE_MAXTYPE 3 
DECL|macro|TYPE_ANY
mdefine_line|#define TYPE_ANY 15 
singleline_comment|// FIXME: comment is required
multiline_comment|/***************************************************************************/
multiline_comment|/*                       KEY &amp; ITEM HEAD                                   */
multiline_comment|/***************************************************************************/
singleline_comment|//
singleline_comment|// directories use this key as well as old files
singleline_comment|//
DECL|struct|offset_v1
r_struct
id|offset_v1
(brace
DECL|member|k_offset
id|__u32
id|k_offset
suffix:semicolon
DECL|member|k_uniqueness
id|__u32
id|k_uniqueness
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
suffix:semicolon
DECL|struct|offset_v2
r_struct
id|offset_v2
(brace
macro_line|#ifdef __LITTLE_ENDIAN
multiline_comment|/* little endian version */
DECL|member|k_offset
id|__u64
id|k_offset
suffix:colon
l_int|60
suffix:semicolon
DECL|member|k_type
id|__u64
id|k_type
suffix:colon
l_int|4
suffix:semicolon
macro_line|#else
multiline_comment|/* big endian version */
id|__u64
id|k_type
suffix:colon
l_int|4
suffix:semicolon
id|__u64
id|k_offset
suffix:colon
l_int|60
suffix:semicolon
macro_line|#endif
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
suffix:semicolon
macro_line|#ifndef __LITTLE_ENDIAN
r_typedef
r_union
(brace
DECL|member|offset_v2
r_struct
id|offset_v2
id|offset_v2
suffix:semicolon
DECL|member|linear
id|__u64
id|linear
suffix:semicolon
DECL|typedef|offset_v2_esafe_overlay
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
id|offset_v2_esafe_overlay
suffix:semicolon
DECL|function|offset_v2_k_type
r_static
r_inline
id|__u16
id|offset_v2_k_type
c_func
(paren
r_const
r_struct
id|offset_v2
op_star
id|v2
)paren
(brace
id|offset_v2_esafe_overlay
id|tmp
op_assign
op_star
(paren
r_const
id|offset_v2_esafe_overlay
op_star
)paren
id|v2
suffix:semicolon
id|tmp.linear
op_assign
id|le64_to_cpu
c_func
(paren
id|tmp.linear
)paren
suffix:semicolon
r_return
(paren
id|tmp.offset_v2.k_type
op_le
id|TYPE_MAXTYPE
)paren
ques
c_cond
id|tmp.offset_v2.k_type
suffix:colon
id|TYPE_ANY
suffix:semicolon
)brace
DECL|function|set_offset_v2_k_type
r_static
r_inline
r_void
id|set_offset_v2_k_type
c_func
(paren
r_struct
id|offset_v2
op_star
id|v2
comma
r_int
id|type
)paren
(brace
id|offset_v2_esafe_overlay
op_star
id|tmp
op_assign
(paren
id|offset_v2_esafe_overlay
op_star
)paren
id|v2
suffix:semicolon
id|tmp-&gt;linear
op_assign
id|le64_to_cpu
c_func
(paren
id|tmp-&gt;linear
)paren
suffix:semicolon
id|tmp-&gt;offset_v2.k_type
op_assign
id|type
suffix:semicolon
id|tmp-&gt;linear
op_assign
id|cpu_to_le64
c_func
(paren
id|tmp-&gt;linear
)paren
suffix:semicolon
)brace
DECL|function|offset_v2_k_offset
r_static
r_inline
id|loff_t
id|offset_v2_k_offset
c_func
(paren
r_const
r_struct
id|offset_v2
op_star
id|v2
)paren
(brace
id|offset_v2_esafe_overlay
id|tmp
op_assign
op_star
(paren
r_const
id|offset_v2_esafe_overlay
op_star
)paren
id|v2
suffix:semicolon
id|tmp.linear
op_assign
id|le64_to_cpu
c_func
(paren
id|tmp.linear
)paren
suffix:semicolon
r_return
id|tmp.offset_v2.k_offset
suffix:semicolon
)brace
DECL|function|set_offset_v2_k_offset
r_static
r_inline
r_void
(def_block
id|set_offset_v2_k_offset
c_func
(paren
r_struct
id|offset_v2
op_star
id|v2
comma
id|loff_t
id|offset
)paren
(brace
id|offset_v2_esafe_overlay
op_star
id|tmp
op_assign
(paren
id|offset_v2_esafe_overlay
op_star
)paren
id|v2
suffix:semicolon
id|tmp-&gt;linear
op_assign
id|le64_to_cpu
c_func
(paren
id|tmp-&gt;linear
)paren
suffix:semicolon
id|tmp-&gt;offset_v2.k_offset
op_assign
id|offset
suffix:semicolon
id|tmp-&gt;linear
op_assign
id|cpu_to_le64
c_func
(paren
id|tmp-&gt;linear
)paren
suffix:semicolon
)brace
)def_block
macro_line|#else
DECL|macro|offset_v2_k_type
macro_line|# define offset_v2_k_type(v2)           ((v2)-&gt;k_type)
DECL|macro|set_offset_v2_k_type
macro_line|# define set_offset_v2_k_type(v2,val)   (offset_v2_k_type(v2) = (val))
DECL|macro|offset_v2_k_offset
macro_line|# define offset_v2_k_offset(v2)         ((v2)-&gt;k_offset)
DECL|macro|set_offset_v2_k_offset
macro_line|# define set_offset_v2_k_offset(v2,val) (offset_v2_k_offset(v2) = (val))
macro_line|#endif
multiline_comment|/* Key of an item determines its location in the S+tree, and&n;   is composed of 4 components */
DECL|struct|key
r_struct
id|key
(brace
DECL|member|k_dir_id
id|__u32
id|k_dir_id
suffix:semicolon
multiline_comment|/* packing locality: by default parent&n;&t;&t;&t;  directory object id */
DECL|member|k_objectid
id|__u32
id|k_objectid
suffix:semicolon
multiline_comment|/* object identifier */
r_union
(brace
DECL|member|k_offset_v1
r_struct
id|offset_v1
id|k_offset_v1
suffix:semicolon
DECL|member|k_offset_v2
r_struct
id|offset_v2
id|k_offset_v2
suffix:semicolon
DECL|member|u
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
id|u
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
suffix:semicolon
DECL|struct|cpu_key
r_struct
id|cpu_key
(brace
DECL|member|on_disk_key
r_struct
id|key
id|on_disk_key
suffix:semicolon
DECL|member|version
r_int
id|version
suffix:semicolon
DECL|member|key_length
r_int
id|key_length
suffix:semicolon
multiline_comment|/* 3 in all cases but direct2indirect and&n;&t;&t;       indirect2direct conversion */
)brace
suffix:semicolon
multiline_comment|/* Our function for comparing keys can compare keys of different&n;   lengths.  It takes as a parameter the length of the keys it is to&n;   compare.  These defines are used in determining what is to be passed&n;   to it as that parameter. */
DECL|macro|REISERFS_FULL_KEY_LEN
mdefine_line|#define REISERFS_FULL_KEY_LEN     4
DECL|macro|REISERFS_SHORT_KEY_LEN
mdefine_line|#define REISERFS_SHORT_KEY_LEN    2
multiline_comment|/* The result of the key compare */
DECL|macro|FIRST_GREATER
mdefine_line|#define FIRST_GREATER 1
DECL|macro|SECOND_GREATER
mdefine_line|#define SECOND_GREATER -1
DECL|macro|KEYS_IDENTICAL
mdefine_line|#define KEYS_IDENTICAL 0
DECL|macro|KEY_FOUND
mdefine_line|#define KEY_FOUND 1
DECL|macro|KEY_NOT_FOUND
mdefine_line|#define KEY_NOT_FOUND 0
DECL|macro|KEY_SIZE
mdefine_line|#define KEY_SIZE (sizeof(struct key))
DECL|macro|SHORT_KEY_SIZE
mdefine_line|#define SHORT_KEY_SIZE (sizeof (__u32) + sizeof (__u32))
multiline_comment|/* return values for search_by_key and clones */
DECL|macro|ITEM_FOUND
mdefine_line|#define ITEM_FOUND 1
DECL|macro|ITEM_NOT_FOUND
mdefine_line|#define ITEM_NOT_FOUND 0
DECL|macro|ENTRY_FOUND
mdefine_line|#define ENTRY_FOUND 1
DECL|macro|ENTRY_NOT_FOUND
mdefine_line|#define ENTRY_NOT_FOUND 0
DECL|macro|DIRECTORY_NOT_FOUND
mdefine_line|#define DIRECTORY_NOT_FOUND -1
DECL|macro|REGULAR_FILE_FOUND
mdefine_line|#define REGULAR_FILE_FOUND -2
DECL|macro|DIRECTORY_FOUND
mdefine_line|#define DIRECTORY_FOUND -3
DECL|macro|BYTE_FOUND
mdefine_line|#define BYTE_FOUND 1
DECL|macro|BYTE_NOT_FOUND
mdefine_line|#define BYTE_NOT_FOUND 0
DECL|macro|FILE_NOT_FOUND
mdefine_line|#define FILE_NOT_FOUND -1
DECL|macro|POSITION_FOUND
mdefine_line|#define POSITION_FOUND 1
DECL|macro|POSITION_NOT_FOUND
mdefine_line|#define POSITION_NOT_FOUND 0
singleline_comment|// return values for reiserfs_find_entry and search_by_entry_key
DECL|macro|NAME_FOUND
mdefine_line|#define NAME_FOUND 1
DECL|macro|NAME_NOT_FOUND
mdefine_line|#define NAME_NOT_FOUND 0
DECL|macro|GOTO_PREVIOUS_ITEM
mdefine_line|#define GOTO_PREVIOUS_ITEM 2
DECL|macro|NAME_FOUND_INVISIBLE
mdefine_line|#define NAME_FOUND_INVISIBLE 3
multiline_comment|/*  Everything in the filesystem is stored as a set of items.  The&n;    item head contains the key of the item, its free space (for&n;    indirect items) and specifies the location of the item itself&n;    within the block.  */
DECL|struct|item_head
r_struct
id|item_head
(brace
multiline_comment|/* Everything in the tree is found by searching for it based on&n;&t; * its key.*/
DECL|member|ih_key
r_struct
id|key
id|ih_key
suffix:semicolon
r_union
(brace
multiline_comment|/* The free space in the last unformatted node of an&n;&t;&t;   indirect item if this is an indirect item.  This&n;&t;&t;   equals 0xFFFF iff this is a direct item or stat data&n;&t;&t;   item. Note that the key, not this field, is used to&n;&t;&t;   determine the item type, and thus which field this&n;&t;&t;   union contains. */
DECL|member|ih_free_space_reserved
id|__u16
id|ih_free_space_reserved
suffix:semicolon
multiline_comment|/* Iff this is a directory item, this field equals the&n;&t;&t;   number of directory entries in the directory item. */
DECL|member|ih_entry_count
id|__u16
id|ih_entry_count
suffix:semicolon
DECL|member|u
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
id|u
suffix:semicolon
DECL|member|ih_item_len
id|__u16
id|ih_item_len
suffix:semicolon
multiline_comment|/* total size of the item body */
DECL|member|ih_item_location
id|__u16
id|ih_item_location
suffix:semicolon
multiline_comment|/* an offset to the item body&n;&t;&t;&t;&t;      * within the block */
DECL|member|ih_version
id|__u16
id|ih_version
suffix:semicolon
multiline_comment|/* 0 for all old items, 2 for new&n;&t;&t;&t;&t;&t;ones. Highest bit is set by fsck&n;&t;&t;&t;&t;&t;temporary, cleaned after all&n;&t;&t;&t;&t;&t;done */
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
suffix:semicolon
multiline_comment|/* size of item header     */
DECL|macro|IH_SIZE
mdefine_line|#define IH_SIZE (sizeof(struct item_head))
DECL|macro|ih_free_space
mdefine_line|#define ih_free_space(ih)            le16_to_cpu((ih)-&gt;u.ih_free_space_reserved)
DECL|macro|ih_version
mdefine_line|#define ih_version(ih)               le16_to_cpu((ih)-&gt;ih_version)
DECL|macro|ih_entry_count
mdefine_line|#define ih_entry_count(ih)           le16_to_cpu((ih)-&gt;u.ih_entry_count)
DECL|macro|ih_location
mdefine_line|#define ih_location(ih)              le16_to_cpu((ih)-&gt;ih_item_location)
DECL|macro|ih_item_len
mdefine_line|#define ih_item_len(ih)              le16_to_cpu((ih)-&gt;ih_item_len)
DECL|macro|put_ih_free_space
mdefine_line|#define put_ih_free_space(ih, val)   do { (ih)-&gt;u.ih_free_space_reserved = cpu_to_le16(val); } while(0)
DECL|macro|put_ih_version
mdefine_line|#define put_ih_version(ih, val)      do { (ih)-&gt;ih_version = cpu_to_le16(val); } while (0)
DECL|macro|put_ih_entry_count
mdefine_line|#define put_ih_entry_count(ih, val)  do { (ih)-&gt;u.ih_entry_count = cpu_to_le16(val); } while (0)
DECL|macro|put_ih_location
mdefine_line|#define put_ih_location(ih, val)     do { (ih)-&gt;ih_item_location = cpu_to_le16(val); } while (0)
DECL|macro|put_ih_item_len
mdefine_line|#define put_ih_item_len(ih, val)     do { (ih)-&gt;ih_item_len = cpu_to_le16(val); } while (0)
DECL|macro|unreachable_item
mdefine_line|#define unreachable_item(ih) (ih_version(ih) &amp; (1 &lt;&lt; 15))
DECL|macro|get_ih_free_space
mdefine_line|#define get_ih_free_space(ih) (ih_version (ih) == KEY_FORMAT_3_6 ? 0 : ih_free_space (ih))
DECL|macro|set_ih_free_space
mdefine_line|#define set_ih_free_space(ih,val) put_ih_free_space((ih), ((ih_version(ih) == KEY_FORMAT_3_6) ? 0 : (val)))
multiline_comment|/* these operate on indirect items, where you&squot;ve got an array of ints&n;** at a possibly unaligned location.  These are a noop on ia32&n;** &n;** p is the array of __u32, i is the index into the array, v is the value&n;** to store there.&n;*/
DECL|macro|get_block_num
mdefine_line|#define get_block_num(p, i) le32_to_cpu(get_unaligned((p) + (i)))
DECL|macro|put_block_num
mdefine_line|#define put_block_num(p, i, v) put_unaligned(cpu_to_le32(v), (p) + (i))
singleline_comment|//
singleline_comment|// in old version uniqueness field shows key type
singleline_comment|//
DECL|macro|V1_SD_UNIQUENESS
mdefine_line|#define V1_SD_UNIQUENESS 0
DECL|macro|V1_INDIRECT_UNIQUENESS
mdefine_line|#define V1_INDIRECT_UNIQUENESS 0xfffffffe
DECL|macro|V1_DIRECT_UNIQUENESS
mdefine_line|#define V1_DIRECT_UNIQUENESS 0xffffffff
DECL|macro|V1_DIRENTRY_UNIQUENESS
mdefine_line|#define V1_DIRENTRY_UNIQUENESS 500
DECL|macro|V1_ANY_UNIQUENESS
mdefine_line|#define V1_ANY_UNIQUENESS 555 
singleline_comment|// FIXME: comment is required
r_extern
r_void
id|reiserfs_warning
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
suffix:semicolon
multiline_comment|/* __attribute__( ( format ( printf, 1, 2 ) ) ); */
singleline_comment|//
singleline_comment|// here are conversion routines
singleline_comment|//
r_static
r_inline
r_int
id|uniqueness2type
(paren
id|__u32
id|uniqueness
)paren
id|CONSTF
suffix:semicolon
DECL|function|uniqueness2type
r_static
r_inline
r_int
id|uniqueness2type
(paren
id|__u32
id|uniqueness
)paren
(brace
r_switch
c_cond
(paren
id|uniqueness
)paren
(brace
r_case
id|V1_SD_UNIQUENESS
suffix:colon
r_return
id|TYPE_STAT_DATA
suffix:semicolon
r_case
id|V1_INDIRECT_UNIQUENESS
suffix:colon
r_return
id|TYPE_INDIRECT
suffix:semicolon
r_case
id|V1_DIRECT_UNIQUENESS
suffix:colon
r_return
id|TYPE_DIRECT
suffix:semicolon
r_case
id|V1_DIRENTRY_UNIQUENESS
suffix:colon
r_return
id|TYPE_DIRENTRY
suffix:semicolon
r_default
suffix:colon
id|reiserfs_warning
c_func
(paren
l_string|&quot;vs-500: unknown uniqueness %d&bslash;n&quot;
comma
id|uniqueness
)paren
suffix:semicolon
r_case
id|V1_ANY_UNIQUENESS
suffix:colon
r_return
id|TYPE_ANY
suffix:semicolon
)brace
)brace
r_static
r_inline
id|__u32
id|type2uniqueness
(paren
r_int
id|type
)paren
id|CONSTF
suffix:semicolon
DECL|function|type2uniqueness
r_static
r_inline
id|__u32
id|type2uniqueness
(paren
r_int
id|type
)paren
(brace
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
id|TYPE_STAT_DATA
suffix:colon
r_return
id|V1_SD_UNIQUENESS
suffix:semicolon
r_case
id|TYPE_INDIRECT
suffix:colon
r_return
id|V1_INDIRECT_UNIQUENESS
suffix:semicolon
r_case
id|TYPE_DIRECT
suffix:colon
r_return
id|V1_DIRECT_UNIQUENESS
suffix:semicolon
r_case
id|TYPE_DIRENTRY
suffix:colon
r_return
id|V1_DIRENTRY_UNIQUENESS
suffix:semicolon
r_default
suffix:colon
id|reiserfs_warning
c_func
(paren
l_string|&quot;vs-501: unknown type %d&bslash;n&quot;
comma
id|type
)paren
suffix:semicolon
r_case
id|TYPE_ANY
suffix:colon
r_return
id|V1_ANY_UNIQUENESS
suffix:semicolon
)brace
)brace
singleline_comment|//
singleline_comment|// key is pointer to on disk key which is stored in le, result is cpu,
singleline_comment|// there is no way to get version of object from key, so, provide
singleline_comment|// version to these defines
singleline_comment|//
DECL|function|le_key_k_offset
r_static
r_inline
id|loff_t
id|le_key_k_offset
(paren
r_int
id|version
comma
r_const
r_struct
id|key
op_star
id|key
)paren
(brace
r_return
(paren
id|version
op_eq
id|KEY_FORMAT_3_5
)paren
ques
c_cond
id|le32_to_cpu
c_func
(paren
id|key-&gt;u.k_offset_v1.k_offset
)paren
suffix:colon
id|offset_v2_k_offset
c_func
(paren
op_amp
(paren
id|key-&gt;u.k_offset_v2
)paren
)paren
suffix:semicolon
)brace
DECL|function|le_ih_k_offset
r_static
r_inline
id|loff_t
id|le_ih_k_offset
(paren
r_const
r_struct
id|item_head
op_star
id|ih
)paren
(brace
r_return
id|le_key_k_offset
(paren
id|ih_version
(paren
id|ih
)paren
comma
op_amp
(paren
id|ih-&gt;ih_key
)paren
)paren
suffix:semicolon
)brace
DECL|function|le_key_k_type
r_static
r_inline
id|loff_t
id|le_key_k_type
(paren
r_int
id|version
comma
r_const
r_struct
id|key
op_star
id|key
)paren
(brace
r_return
(paren
id|version
op_eq
id|KEY_FORMAT_3_5
)paren
ques
c_cond
id|uniqueness2type
c_func
(paren
id|le32_to_cpu
c_func
(paren
id|key-&gt;u.k_offset_v1.k_uniqueness
)paren
)paren
suffix:colon
id|offset_v2_k_type
c_func
(paren
op_amp
(paren
id|key-&gt;u.k_offset_v2
)paren
)paren
suffix:semicolon
)brace
DECL|function|le_ih_k_type
r_static
r_inline
id|loff_t
id|le_ih_k_type
(paren
r_const
r_struct
id|item_head
op_star
id|ih
)paren
(brace
r_return
id|le_key_k_type
(paren
id|ih_version
(paren
id|ih
)paren
comma
op_amp
(paren
id|ih-&gt;ih_key
)paren
)paren
suffix:semicolon
)brace
DECL|function|set_le_key_k_offset
r_static
r_inline
r_void
id|set_le_key_k_offset
(paren
r_int
id|version
comma
r_struct
id|key
op_star
id|key
comma
id|loff_t
id|offset
)paren
(brace
(paren
id|version
op_eq
id|KEY_FORMAT_3_5
)paren
ques
c_cond
(paren
id|key-&gt;u.k_offset_v1.k_offset
op_assign
id|cpu_to_le32
(paren
id|offset
)paren
)paren
suffix:colon
multiline_comment|/* jdm check */
(paren
id|set_offset_v2_k_offset
c_func
(paren
op_amp
(paren
id|key-&gt;u.k_offset_v2
)paren
comma
id|offset
)paren
)paren
suffix:semicolon
)brace
DECL|function|set_le_ih_k_offset
r_static
r_inline
r_void
id|set_le_ih_k_offset
(paren
r_struct
id|item_head
op_star
id|ih
comma
id|loff_t
id|offset
)paren
(brace
id|set_le_key_k_offset
(paren
id|ih_version
(paren
id|ih
)paren
comma
op_amp
(paren
id|ih-&gt;ih_key
)paren
comma
id|offset
)paren
suffix:semicolon
)brace
DECL|function|set_le_key_k_type
r_static
r_inline
r_void
id|set_le_key_k_type
(paren
r_int
id|version
comma
r_struct
id|key
op_star
id|key
comma
r_int
id|type
)paren
(brace
(paren
id|version
op_eq
id|KEY_FORMAT_3_5
)paren
ques
c_cond
(paren
id|key-&gt;u.k_offset_v1.k_uniqueness
op_assign
id|cpu_to_le32
c_func
(paren
id|type2uniqueness
c_func
(paren
id|type
)paren
)paren
)paren
suffix:colon
(paren
id|set_offset_v2_k_type
c_func
(paren
op_amp
(paren
id|key-&gt;u.k_offset_v2
)paren
comma
id|type
)paren
)paren
suffix:semicolon
)brace
DECL|function|set_le_ih_k_type
r_static
r_inline
r_void
id|set_le_ih_k_type
(paren
r_struct
id|item_head
op_star
id|ih
comma
r_int
id|type
)paren
(brace
id|set_le_key_k_type
(paren
id|ih_version
(paren
id|ih
)paren
comma
op_amp
(paren
id|ih-&gt;ih_key
)paren
comma
id|type
)paren
suffix:semicolon
)brace
DECL|macro|is_direntry_le_key
mdefine_line|#define is_direntry_le_key(version,key) (le_key_k_type (version, key) == TYPE_DIRENTRY)
DECL|macro|is_direct_le_key
mdefine_line|#define is_direct_le_key(version,key) (le_key_k_type (version, key) == TYPE_DIRECT)
DECL|macro|is_indirect_le_key
mdefine_line|#define is_indirect_le_key(version,key) (le_key_k_type (version, key) == TYPE_INDIRECT)
DECL|macro|is_statdata_le_key
mdefine_line|#define is_statdata_le_key(version,key) (le_key_k_type (version, key) == TYPE_STAT_DATA)
singleline_comment|//
singleline_comment|// item header has version.
singleline_comment|//
DECL|macro|is_direntry_le_ih
mdefine_line|#define is_direntry_le_ih(ih) is_direntry_le_key (ih_version (ih), &amp;((ih)-&gt;ih_key))
DECL|macro|is_direct_le_ih
mdefine_line|#define is_direct_le_ih(ih) is_direct_le_key (ih_version (ih), &amp;((ih)-&gt;ih_key))
DECL|macro|is_indirect_le_ih
mdefine_line|#define is_indirect_le_ih(ih) is_indirect_le_key (ih_version(ih), &amp;((ih)-&gt;ih_key))
DECL|macro|is_statdata_le_ih
mdefine_line|#define is_statdata_le_ih(ih) is_statdata_le_key (ih_version (ih), &amp;((ih)-&gt;ih_key))
singleline_comment|//
singleline_comment|// key is pointer to cpu key, result is cpu
singleline_comment|//
DECL|function|cpu_key_k_offset
r_static
r_inline
id|loff_t
id|cpu_key_k_offset
(paren
r_const
r_struct
id|cpu_key
op_star
id|key
)paren
(brace
r_return
(paren
id|key-&gt;version
op_eq
id|KEY_FORMAT_3_5
)paren
ques
c_cond
id|key-&gt;on_disk_key.u.k_offset_v1.k_offset
suffix:colon
id|key-&gt;on_disk_key.u.k_offset_v2.k_offset
suffix:semicolon
)brace
DECL|function|cpu_key_k_type
r_static
r_inline
id|loff_t
id|cpu_key_k_type
(paren
r_const
r_struct
id|cpu_key
op_star
id|key
)paren
(brace
r_return
(paren
id|key-&gt;version
op_eq
id|KEY_FORMAT_3_5
)paren
ques
c_cond
id|uniqueness2type
(paren
id|key-&gt;on_disk_key.u.k_offset_v1.k_uniqueness
)paren
suffix:colon
id|key-&gt;on_disk_key.u.k_offset_v2.k_type
suffix:semicolon
)brace
DECL|function|set_cpu_key_k_offset
r_static
r_inline
r_void
id|set_cpu_key_k_offset
(paren
r_struct
id|cpu_key
op_star
id|key
comma
id|loff_t
id|offset
)paren
(brace
(paren
id|key-&gt;version
op_eq
id|KEY_FORMAT_3_5
)paren
ques
c_cond
(paren
id|key-&gt;on_disk_key.u.k_offset_v1.k_offset
op_assign
id|offset
)paren
suffix:colon
(paren
id|key-&gt;on_disk_key.u.k_offset_v2.k_offset
op_assign
id|offset
)paren
suffix:semicolon
)brace
DECL|function|set_cpu_key_k_type
r_static
r_inline
r_void
id|set_cpu_key_k_type
(paren
r_struct
id|cpu_key
op_star
id|key
comma
r_int
id|type
)paren
(brace
(paren
id|key-&gt;version
op_eq
id|KEY_FORMAT_3_5
)paren
ques
c_cond
(paren
id|key-&gt;on_disk_key.u.k_offset_v1.k_uniqueness
op_assign
id|type2uniqueness
(paren
id|type
)paren
)paren
suffix:colon
(paren
id|key-&gt;on_disk_key.u.k_offset_v2.k_type
op_assign
id|type
)paren
suffix:semicolon
)brace
DECL|function|cpu_key_k_offset_dec
r_static
r_inline
r_void
id|cpu_key_k_offset_dec
(paren
r_struct
id|cpu_key
op_star
id|key
)paren
(brace
r_if
c_cond
(paren
id|key-&gt;version
op_eq
id|KEY_FORMAT_3_5
)paren
id|key-&gt;on_disk_key.u.k_offset_v1.k_offset
op_decrement
suffix:semicolon
r_else
id|key-&gt;on_disk_key.u.k_offset_v2.k_offset
op_decrement
suffix:semicolon
)brace
DECL|macro|is_direntry_cpu_key
mdefine_line|#define is_direntry_cpu_key(key) (cpu_key_k_type (key) == TYPE_DIRENTRY)
DECL|macro|is_direct_cpu_key
mdefine_line|#define is_direct_cpu_key(key) (cpu_key_k_type (key) == TYPE_DIRECT)
DECL|macro|is_indirect_cpu_key
mdefine_line|#define is_indirect_cpu_key(key) (cpu_key_k_type (key) == TYPE_INDIRECT)
DECL|macro|is_statdata_cpu_key
mdefine_line|#define is_statdata_cpu_key(key) (cpu_key_k_type (key) == TYPE_STAT_DATA)
multiline_comment|/* are these used ? */
DECL|macro|is_direntry_cpu_ih
mdefine_line|#define is_direntry_cpu_ih(ih) (is_direntry_cpu_key (&amp;((ih)-&gt;ih_key)))
DECL|macro|is_direct_cpu_ih
mdefine_line|#define is_direct_cpu_ih(ih) (is_direct_cpu_key (&amp;((ih)-&gt;ih_key)))
DECL|macro|is_indirect_cpu_ih
mdefine_line|#define is_indirect_cpu_ih(ih) (is_indirect_cpu_key (&amp;((ih)-&gt;ih_key)))
DECL|macro|is_statdata_cpu_ih
mdefine_line|#define is_statdata_cpu_ih(ih) (is_statdata_cpu_key (&amp;((ih)-&gt;ih_key)))
DECL|macro|I_K_KEY_IN_ITEM
mdefine_line|#define I_K_KEY_IN_ITEM(p_s_ih, p_s_key, n_blocksize) &bslash;&n;    ( ! COMP_SHORT_KEYS(p_s_ih, p_s_key) &amp;&amp; &bslash;&n;          I_OFF_BYTE_IN_ITEM(p_s_ih, k_offset (p_s_key), n_blocksize) )
multiline_comment|/* maximal length of item */
DECL|macro|MAX_ITEM_LEN
mdefine_line|#define MAX_ITEM_LEN(block_size) (block_size - BLKH_SIZE - IH_SIZE)
DECL|macro|MIN_ITEM_LEN
mdefine_line|#define MIN_ITEM_LEN 1
multiline_comment|/* object identifier for root dir */
DECL|macro|REISERFS_ROOT_OBJECTID
mdefine_line|#define REISERFS_ROOT_OBJECTID 2
DECL|macro|REISERFS_ROOT_PARENT_OBJECTID
mdefine_line|#define REISERFS_ROOT_PARENT_OBJECTID 1
r_extern
r_struct
id|key
id|root_key
suffix:semicolon
multiline_comment|/* &n; * Picture represents a leaf of the S+tree&n; *  ______________________________________________________&n; * |      |  Array of     |                   |           |&n; * |Block |  Object-Item  |      F r e e      |  Objects- |&n; * | head |  Headers      |     S p a c e     |   Items   |&n; * |______|_______________|___________________|___________|&n; */
multiline_comment|/* Header of a disk block.  More precisely, header of a formatted leaf&n;   or internal node, and not the header of an unformatted node. */
DECL|struct|block_head
r_struct
id|block_head
(brace
DECL|member|blk_level
id|__u16
id|blk_level
suffix:semicolon
multiline_comment|/* Level of a block in the tree. */
DECL|member|blk_nr_item
id|__u16
id|blk_nr_item
suffix:semicolon
multiline_comment|/* Number of keys/items in a block. */
DECL|member|blk_free_space
id|__u16
id|blk_free_space
suffix:semicolon
multiline_comment|/* Block free space in bytes. */
DECL|member|blk_reserved
id|__u16
id|blk_reserved
suffix:semicolon
multiline_comment|/* dump this in v4/planA */
DECL|member|blk_right_delim_key
r_struct
id|key
id|blk_right_delim_key
suffix:semicolon
multiline_comment|/* kept only for compatibility */
)brace
suffix:semicolon
DECL|macro|BLKH_SIZE
mdefine_line|#define BLKH_SIZE                     (sizeof(struct block_head))
DECL|macro|blkh_level
mdefine_line|#define blkh_level(p_blkh)            (le16_to_cpu((p_blkh)-&gt;blk_level))
DECL|macro|blkh_nr_item
mdefine_line|#define blkh_nr_item(p_blkh)          (le16_to_cpu((p_blkh)-&gt;blk_nr_item))
DECL|macro|blkh_free_space
mdefine_line|#define blkh_free_space(p_blkh)       (le16_to_cpu((p_blkh)-&gt;blk_free_space))
DECL|macro|blkh_reserved
mdefine_line|#define blkh_reserved(p_blkh)         (le16_to_cpu((p_blkh)-&gt;blk_reserved))
DECL|macro|set_blkh_level
mdefine_line|#define set_blkh_level(p_blkh,val)    ((p_blkh)-&gt;blk_level = cpu_to_le16(val))
DECL|macro|set_blkh_nr_item
mdefine_line|#define set_blkh_nr_item(p_blkh,val)  ((p_blkh)-&gt;blk_nr_item = cpu_to_le16(val))
DECL|macro|set_blkh_free_space
mdefine_line|#define set_blkh_free_space(p_blkh,val) ((p_blkh)-&gt;blk_free_space = cpu_to_le16(val))
DECL|macro|set_blkh_reserved
mdefine_line|#define set_blkh_reserved(p_blkh,val) ((p_blkh)-&gt;blk_reserved = cpu_to_le16(val))
DECL|macro|blkh_right_delim_key
mdefine_line|#define blkh_right_delim_key(p_blkh)  ((p_blkh)-&gt;blk_right_delim_key)
DECL|macro|set_blkh_right_delim_key
mdefine_line|#define set_blkh_right_delim_key(p_blkh,val)  ((p_blkh)-&gt;blk_right_delim_key = val)
multiline_comment|/*&n; * values for blk_level field of the struct block_head&n; */
DECL|macro|FREE_LEVEL
mdefine_line|#define FREE_LEVEL 0 /* when node gets removed from the tree its&n;&t;&t;&t;blk_level is set to FREE_LEVEL. It is then&n;&t;&t;&t;used to see whether the node is still in the&n;&t;&t;&t;tree */
DECL|macro|DISK_LEAF_NODE_LEVEL
mdefine_line|#define DISK_LEAF_NODE_LEVEL  1 /* Leaf node level.*/
multiline_comment|/* Given the buffer head of a formatted node, resolve to the block head of that node. */
DECL|macro|B_BLK_HEAD
mdefine_line|#define B_BLK_HEAD(p_s_bh)            ((struct block_head *)((p_s_bh)-&gt;b_data))
multiline_comment|/* Number of items that are in buffer. */
DECL|macro|B_NR_ITEMS
mdefine_line|#define B_NR_ITEMS(p_s_bh)            (blkh_nr_item(B_BLK_HEAD(p_s_bh)))
DECL|macro|B_LEVEL
mdefine_line|#define B_LEVEL(p_s_bh)               (blkh_level(B_BLK_HEAD(p_s_bh)))
DECL|macro|B_FREE_SPACE
mdefine_line|#define B_FREE_SPACE(p_s_bh)          (blkh_free_space(B_BLK_HEAD(p_s_bh)))
DECL|macro|PUT_B_NR_ITEMS
mdefine_line|#define PUT_B_NR_ITEMS(p_s_bh,val)    do { set_blkh_nr_item(B_BLK_HEAD(p_s_bh),val); } while (0)
DECL|macro|PUT_B_LEVEL
mdefine_line|#define PUT_B_LEVEL(p_s_bh,val)       do { set_blkh_level(B_BLK_HEAD(p_s_bh),val); } while (0)
DECL|macro|PUT_B_FREE_SPACE
mdefine_line|#define PUT_B_FREE_SPACE(p_s_bh,val)  do { set_blkh_free_space(B_BLK_HEAD(p_s_bh),val); } while (0)
multiline_comment|/* Get right delimiting key. -- little endian */
DECL|macro|B_PRIGHT_DELIM_KEY
mdefine_line|#define B_PRIGHT_DELIM_KEY(p_s_bh)   (&amp;(blk_right_delim_key(B_BLK_HEAD(p_s_bh))
multiline_comment|/* Does the buffer contain a disk leaf. */
DECL|macro|B_IS_ITEMS_LEVEL
mdefine_line|#define B_IS_ITEMS_LEVEL(p_s_bh)     (B_LEVEL(p_s_bh) == DISK_LEAF_NODE_LEVEL)
multiline_comment|/* Does the buffer contain a disk internal node */
DECL|macro|B_IS_KEYS_LEVEL
mdefine_line|#define B_IS_KEYS_LEVEL(p_s_bh)      (B_LEVEL(p_s_bh) &gt; DISK_LEAF_NODE_LEVEL &bslash;&n;                                            &amp;&amp; B_LEVEL(p_s_bh) &lt;= MAX_HEIGHT)
multiline_comment|/***************************************************************************/
multiline_comment|/*                             STAT DATA                                   */
multiline_comment|/***************************************************************************/
singleline_comment|//
singleline_comment|// old stat data is 32 bytes long. We are going to distinguish new one by
singleline_comment|// different size
singleline_comment|//
DECL|struct|stat_data_v1
r_struct
id|stat_data_v1
(brace
DECL|member|sd_mode
id|__u16
id|sd_mode
suffix:semicolon
multiline_comment|/* file type, permissions */
DECL|member|sd_nlink
id|__u16
id|sd_nlink
suffix:semicolon
multiline_comment|/* number of hard links */
DECL|member|sd_uid
id|__u16
id|sd_uid
suffix:semicolon
multiline_comment|/* owner */
DECL|member|sd_gid
id|__u16
id|sd_gid
suffix:semicolon
multiline_comment|/* group */
DECL|member|sd_size
id|__u32
id|sd_size
suffix:semicolon
multiline_comment|/* file size */
DECL|member|sd_atime
id|__u32
id|sd_atime
suffix:semicolon
multiline_comment|/* time of last access */
DECL|member|sd_mtime
id|__u32
id|sd_mtime
suffix:semicolon
multiline_comment|/* time file was last modified  */
DECL|member|sd_ctime
id|__u32
id|sd_ctime
suffix:semicolon
multiline_comment|/* time inode (stat data) was last changed (except changes to sd_atime and sd_mtime) */
r_union
(brace
DECL|member|sd_rdev
id|__u32
id|sd_rdev
suffix:semicolon
DECL|member|sd_blocks
id|__u32
id|sd_blocks
suffix:semicolon
multiline_comment|/* number of blocks file uses */
DECL|member|u
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
id|u
suffix:semicolon
DECL|member|sd_first_direct_byte
id|__u32
id|sd_first_direct_byte
suffix:semicolon
multiline_comment|/* first byte of file which is stored&n;&t;&t;&t;&t;   in a direct item: except that if it&n;&t;&t;&t;&t;   equals 1 it is a symlink and if it&n;&t;&t;&t;&t;   equals ~(__u32)0 there is no&n;&t;&t;&t;&t;   direct item.  The existence of this&n;&t;&t;&t;&t;   field really grates on me. Let&squot;s&n;&t;&t;&t;&t;   replace it with a macro based on&n;&t;&t;&t;&t;   sd_size and our tail suppression&n;&t;&t;&t;&t;   policy.  Someday.  -Hans */
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
suffix:semicolon
DECL|macro|SD_V1_SIZE
mdefine_line|#define SD_V1_SIZE              (sizeof(struct stat_data_v1))
DECL|macro|stat_data_v1
mdefine_line|#define stat_data_v1(ih)        (ih_version (ih) == KEY_FORMAT_3_5)
DECL|macro|sd_v1_mode
mdefine_line|#define sd_v1_mode(sdp)         (le16_to_cpu((sdp)-&gt;sd_mode))
DECL|macro|set_sd_v1_mode
mdefine_line|#define set_sd_v1_mode(sdp,v)   ((sdp)-&gt;sd_mode = cpu_to_le16(v))
DECL|macro|sd_v1_nlink
mdefine_line|#define sd_v1_nlink(sdp)        (le16_to_cpu((sdp)-&gt;sd_nlink))
DECL|macro|set_sd_v1_nlink
mdefine_line|#define set_sd_v1_nlink(sdp,v)  ((sdp)-&gt;sd_nlink = cpu_to_le16(v))
DECL|macro|sd_v1_uid
mdefine_line|#define sd_v1_uid(sdp)          (le16_to_cpu((sdp)-&gt;sd_uid))
DECL|macro|set_sd_v1_uid
mdefine_line|#define set_sd_v1_uid(sdp,v)    ((sdp)-&gt;sd_uid = cpu_to_le16(v))
DECL|macro|sd_v1_gid
mdefine_line|#define sd_v1_gid(sdp)          (le16_to_cpu((sdp)-&gt;sd_gid))
DECL|macro|set_sd_v1_gid
mdefine_line|#define set_sd_v1_gid(sdp,v)    ((sdp)-&gt;sd_gid = cpu_to_le16(v))
DECL|macro|sd_v1_size
mdefine_line|#define sd_v1_size(sdp)         (le32_to_cpu((sdp)-&gt;sd_size))
DECL|macro|set_sd_v1_size
mdefine_line|#define set_sd_v1_size(sdp,v)   ((sdp)-&gt;sd_size = cpu_to_le32(v))
DECL|macro|sd_v1_atime
mdefine_line|#define sd_v1_atime(sdp)        (le32_to_cpu((sdp)-&gt;sd_atime))
DECL|macro|set_sd_v1_atime
mdefine_line|#define set_sd_v1_atime(sdp,v)  ((sdp)-&gt;sd_atime = cpu_to_le32(v))
DECL|macro|sd_v1_mtime
mdefine_line|#define sd_v1_mtime(sdp)        (le32_to_cpu((sdp)-&gt;sd_mtime))
DECL|macro|set_sd_v1_mtime
mdefine_line|#define set_sd_v1_mtime(sdp,v)  ((sdp)-&gt;sd_mtime = cpu_to_le32(v))
DECL|macro|sd_v1_ctime
mdefine_line|#define sd_v1_ctime(sdp)        (le32_to_cpu((sdp)-&gt;sd_ctime))
DECL|macro|set_sd_v1_ctime
mdefine_line|#define set_sd_v1_ctime(sdp,v)  ((sdp)-&gt;sd_ctime = cpu_to_le32(v))
DECL|macro|sd_v1_rdev
mdefine_line|#define sd_v1_rdev(sdp)         (le32_to_cpu((sdp)-&gt;u.sd_rdev))
DECL|macro|set_sd_v1_rdev
mdefine_line|#define set_sd_v1_rdev(sdp,v)   ((sdp)-&gt;u.sd_rdev = cpu_to_le32(v))
DECL|macro|sd_v1_blocks
mdefine_line|#define sd_v1_blocks(sdp)       (le32_to_cpu((sdp)-&gt;u.sd_blocks))
DECL|macro|set_sd_v1_blocks
mdefine_line|#define set_sd_v1_blocks(sdp,v) ((sdp)-&gt;u.sd_blocks = cpu_to_le32(v))
DECL|macro|sd_v1_first_direct_byte
mdefine_line|#define sd_v1_first_direct_byte(sdp) &bslash;&n;                                (le32_to_cpu((sdp)-&gt;sd_first_direct_byte))
DECL|macro|set_sd_v1_first_direct_byte
mdefine_line|#define set_sd_v1_first_direct_byte(sdp,v) &bslash;&n;                                ((sdp)-&gt;sd_first_direct_byte = cpu_to_le32(v))
multiline_comment|/* Stat Data on disk (reiserfs version of UFS disk inode minus the&n;   address blocks) */
DECL|struct|stat_data
r_struct
id|stat_data
(brace
DECL|member|sd_mode
id|__u16
id|sd_mode
suffix:semicolon
multiline_comment|/* file type, permissions */
DECL|member|sd_reserved
id|__u16
id|sd_reserved
suffix:semicolon
DECL|member|sd_nlink
id|__u32
id|sd_nlink
suffix:semicolon
multiline_comment|/* number of hard links */
DECL|member|sd_size
id|__u64
id|sd_size
suffix:semicolon
multiline_comment|/* file size */
DECL|member|sd_uid
id|__u32
id|sd_uid
suffix:semicolon
multiline_comment|/* owner */
DECL|member|sd_gid
id|__u32
id|sd_gid
suffix:semicolon
multiline_comment|/* group */
DECL|member|sd_atime
id|__u32
id|sd_atime
suffix:semicolon
multiline_comment|/* time of last access */
DECL|member|sd_mtime
id|__u32
id|sd_mtime
suffix:semicolon
multiline_comment|/* time file was last modified  */
DECL|member|sd_ctime
id|__u32
id|sd_ctime
suffix:semicolon
multiline_comment|/* time inode (stat data) was last changed (except changes to sd_atime and sd_mtime) */
DECL|member|sd_blocks
id|__u32
id|sd_blocks
suffix:semicolon
r_union
(brace
DECL|member|sd_rdev
id|__u32
id|sd_rdev
suffix:semicolon
DECL|member|sd_generation
id|__u32
id|sd_generation
suffix:semicolon
singleline_comment|//__u32 sd_first_direct_byte; 
multiline_comment|/* first byte of file which is stored in a&n;&t;&t;&t;&t;       direct item: except that if it equals 1&n;&t;&t;&t;&t;       it is a symlink and if it equals&n;&t;&t;&t;&t;       ~(__u32)0 there is no direct item.  The&n;&t;&t;&t;&t;       existence of this field really grates&n;&t;&t;&t;&t;       on me. Let&squot;s replace it with a macro&n;&t;&t;&t;&t;       based on sd_size and our tail&n;&t;&t;&t;&t;       suppression policy? */
DECL|member|u
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
id|u
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
suffix:semicolon
singleline_comment|//
singleline_comment|// this is 44 bytes long
singleline_comment|//
DECL|macro|SD_SIZE
mdefine_line|#define SD_SIZE (sizeof(struct stat_data))
DECL|macro|SD_V2_SIZE
mdefine_line|#define SD_V2_SIZE              SD_SIZE
DECL|macro|stat_data_v2
mdefine_line|#define stat_data_v2(ih)        (ih_version (ih) == KEY_FORMAT_3_6)
DECL|macro|sd_v2_mode
mdefine_line|#define sd_v2_mode(sdp)         (le16_to_cpu((sdp)-&gt;sd_mode))
DECL|macro|set_sd_v2_mode
mdefine_line|#define set_sd_v2_mode(sdp,v)   ((sdp)-&gt;sd_mode = cpu_to_le16(v))
multiline_comment|/* sd_reserved */
multiline_comment|/* set_sd_reserved */
DECL|macro|sd_v2_nlink
mdefine_line|#define sd_v2_nlink(sdp)        (le32_to_cpu((sdp)-&gt;sd_nlink))
DECL|macro|set_sd_v2_nlink
mdefine_line|#define set_sd_v2_nlink(sdp,v)  ((sdp)-&gt;sd_nlink = cpu_to_le32(v))
DECL|macro|sd_v2_size
mdefine_line|#define sd_v2_size(sdp)         (le64_to_cpu((sdp)-&gt;sd_size))
DECL|macro|set_sd_v2_size
mdefine_line|#define set_sd_v2_size(sdp,v)   ((sdp)-&gt;sd_size = cpu_to_le64(v))
DECL|macro|sd_v2_uid
mdefine_line|#define sd_v2_uid(sdp)          (le32_to_cpu((sdp)-&gt;sd_uid))
DECL|macro|set_sd_v2_uid
mdefine_line|#define set_sd_v2_uid(sdp,v)    ((sdp)-&gt;sd_uid = cpu_to_le32(v))
DECL|macro|sd_v2_gid
mdefine_line|#define sd_v2_gid(sdp)          (le32_to_cpu((sdp)-&gt;sd_gid))
DECL|macro|set_sd_v2_gid
mdefine_line|#define set_sd_v2_gid(sdp,v)    ((sdp)-&gt;sd_gid = cpu_to_le32(v))
DECL|macro|sd_v2_atime
mdefine_line|#define sd_v2_atime(sdp)        (le32_to_cpu((sdp)-&gt;sd_atime))
DECL|macro|set_sd_v2_atime
mdefine_line|#define set_sd_v2_atime(sdp,v)  ((sdp)-&gt;sd_atime = cpu_to_le32(v))
DECL|macro|sd_v2_mtime
mdefine_line|#define sd_v2_mtime(sdp)        (le32_to_cpu((sdp)-&gt;sd_mtime))
DECL|macro|set_sd_v2_mtime
mdefine_line|#define set_sd_v2_mtime(sdp,v)  ((sdp)-&gt;sd_mtime = cpu_to_le32(v))
DECL|macro|sd_v2_ctime
mdefine_line|#define sd_v2_ctime(sdp)        (le32_to_cpu((sdp)-&gt;sd_ctime))
DECL|macro|set_sd_v2_ctime
mdefine_line|#define set_sd_v2_ctime(sdp,v)  ((sdp)-&gt;sd_ctime = cpu_to_le32(v))
DECL|macro|sd_v2_blocks
mdefine_line|#define sd_v2_blocks(sdp)       (le32_to_cpu((sdp)-&gt;sd_blocks))
DECL|macro|set_sd_v2_blocks
mdefine_line|#define set_sd_v2_blocks(sdp,v) ((sdp)-&gt;sd_blocks = cpu_to_le32(v))
DECL|macro|sd_v2_rdev
mdefine_line|#define sd_v2_rdev(sdp)         (le32_to_cpu((sdp)-&gt;u.sd_rdev))
DECL|macro|set_sd_v2_rdev
mdefine_line|#define set_sd_v2_rdev(sdp,v)   ((sdp)-&gt;u.sd_rdev = cpu_to_le32(v))
DECL|macro|sd_v2_generation
mdefine_line|#define sd_v2_generation(sdp)   (le32_to_cpu((sdp)-&gt;u.sd_generation))
DECL|macro|set_sd_v2_generation
mdefine_line|#define set_sd_v2_generation(sdp,v) ((sdp)-&gt;u.sd_generation = cpu_to_le32(v))
multiline_comment|/***************************************************************************/
multiline_comment|/*                      DIRECTORY STRUCTURE                                */
multiline_comment|/***************************************************************************/
multiline_comment|/* &n;   Picture represents the structure of directory items&n;   ________________________________________________&n;   |  Array of     |   |     |        |       |   |&n;   | directory     |N-1| N-2 | ....   |   1st |0th|&n;   | entry headers |   |     |        |       |   |&n;   |_______________|___|_____|________|_______|___|&n;                    &lt;----   directory entries         ------&gt;&n;&n; First directory item has k_offset component 1. We store &quot;.&quot; and &quot;..&quot;&n; in one item, always, we never split &quot;.&quot; and &quot;..&quot; into differing&n; items.  This makes, among other things, the code for removing&n; directories simpler. */
DECL|macro|SD_OFFSET
mdefine_line|#define SD_OFFSET  0
DECL|macro|SD_UNIQUENESS
mdefine_line|#define SD_UNIQUENESS 0
DECL|macro|DOT_OFFSET
mdefine_line|#define DOT_OFFSET 1
DECL|macro|DOT_DOT_OFFSET
mdefine_line|#define DOT_DOT_OFFSET 2
DECL|macro|DIRENTRY_UNIQUENESS
mdefine_line|#define DIRENTRY_UNIQUENESS 500
multiline_comment|/* */
DECL|macro|FIRST_ITEM_OFFSET
mdefine_line|#define FIRST_ITEM_OFFSET 1
multiline_comment|/*&n;   Q: How to get key of object pointed to by entry from entry?  &n;&n;   A: Each directory entry has its header. This header has deh_dir_id and deh_objectid fields, those are key&n;      of object, entry points to */
multiline_comment|/* NOT IMPLEMENTED:   &n;   Directory will someday contain stat data of object */
DECL|struct|reiserfs_de_head
r_struct
id|reiserfs_de_head
(brace
DECL|member|deh_offset
id|__u32
id|deh_offset
suffix:semicolon
multiline_comment|/* third component of the directory entry key */
DECL|member|deh_dir_id
id|__u32
id|deh_dir_id
suffix:semicolon
multiline_comment|/* objectid of the parent directory of the object, that is referenced&n;&t;&t;&t;&t;&t;   by directory entry */
DECL|member|deh_objectid
id|__u32
id|deh_objectid
suffix:semicolon
multiline_comment|/* objectid of the object, that is referenced by directory entry */
DECL|member|deh_location
id|__u16
id|deh_location
suffix:semicolon
multiline_comment|/* offset of name in the whole item */
DECL|member|deh_state
id|__u16
id|deh_state
suffix:semicolon
multiline_comment|/* whether 1) entry contains stat data (for future), and 2) whether&n;&t;&t;&t;&t;&t;   entry is hidden (unlinked) */
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
suffix:semicolon
DECL|macro|DEH_SIZE
mdefine_line|#define DEH_SIZE                  sizeof(struct reiserfs_de_head)
DECL|macro|deh_offset
mdefine_line|#define deh_offset(p_deh)         (le32_to_cpu((p_deh)-&gt;deh_offset))
DECL|macro|deh_dir_id
mdefine_line|#define deh_dir_id(p_deh)         (le32_to_cpu((p_deh)-&gt;deh_dir_id))
DECL|macro|deh_objectid
mdefine_line|#define deh_objectid(p_deh)       (le32_to_cpu((p_deh)-&gt;deh_objectid))
DECL|macro|deh_location
mdefine_line|#define deh_location(p_deh)       (le16_to_cpu((p_deh)-&gt;deh_location))
DECL|macro|deh_state
mdefine_line|#define deh_state(p_deh)          (le16_to_cpu((p_deh)-&gt;deh_state))
DECL|macro|put_deh_offset
mdefine_line|#define put_deh_offset(p_deh,v)   ((p_deh)-&gt;deh_offset = cpu_to_le32((v)))
DECL|macro|put_deh_dir_id
mdefine_line|#define put_deh_dir_id(p_deh,v)   ((p_deh)-&gt;deh_dir_id = cpu_to_le32((v)))
DECL|macro|put_deh_objectid
mdefine_line|#define put_deh_objectid(p_deh,v) ((p_deh)-&gt;deh_objectid = cpu_to_le32((v)))
DECL|macro|put_deh_location
mdefine_line|#define put_deh_location(p_deh,v) ((p_deh)-&gt;deh_location = cpu_to_le16((v)))
DECL|macro|put_deh_state
mdefine_line|#define put_deh_state(p_deh,v)    ((p_deh)-&gt;deh_state = cpu_to_le16((v)))
multiline_comment|/* empty directory contains two entries &quot;.&quot; and &quot;..&quot; and their headers */
DECL|macro|EMPTY_DIR_SIZE
mdefine_line|#define EMPTY_DIR_SIZE &bslash;&n;(DEH_SIZE * 2 + ROUND_UP (strlen (&quot;.&quot;)) + ROUND_UP (strlen (&quot;..&quot;)))
multiline_comment|/* old format directories have this size when empty */
DECL|macro|EMPTY_DIR_SIZE_V1
mdefine_line|#define EMPTY_DIR_SIZE_V1 (DEH_SIZE * 2 + 3)
DECL|macro|DEH_Statdata
mdefine_line|#define DEH_Statdata 0&t;&t;&t;/* not used now */
DECL|macro|DEH_Visible
mdefine_line|#define DEH_Visible 2
multiline_comment|/* 64 bit systems (and the S/390) need to be aligned explicitly -jdm */
macro_line|#if BITS_PER_LONG == 64 || defined(__s390__) || defined(__hppa__)
DECL|macro|ADDR_UNALIGNED_BITS
macro_line|#   define ADDR_UNALIGNED_BITS  (3)
macro_line|#endif
multiline_comment|/* These are only used to manipulate deh_state.&n; * Because of this, we&squot;ll use the ext2_ bit routines,&n; * since they are little endian */
macro_line|#ifdef ADDR_UNALIGNED_BITS
DECL|macro|aligned_address
macro_line|#   define aligned_address(addr)           ((void *)((long)(addr) &amp; ~((1UL &lt;&lt; ADDR_UNALIGNED_BITS) - 1)))
DECL|macro|unaligned_offset
macro_line|#   define unaligned_offset(addr)          (((int)((long)(addr) &amp; ((1 &lt;&lt; ADDR_UNALIGNED_BITS) - 1))) &lt;&lt; 3)
DECL|macro|set_bit_unaligned
macro_line|#   define set_bit_unaligned(nr, addr)     ext2_set_bit((nr) + unaligned_offset(addr), aligned_address(addr))
DECL|macro|clear_bit_unaligned
macro_line|#   define clear_bit_unaligned(nr, addr)   ext2_clear_bit((nr) + unaligned_offset(addr), aligned_address(addr))
DECL|macro|test_bit_unaligned
macro_line|#   define test_bit_unaligned(nr, addr)    ext2_test_bit((nr) + unaligned_offset(addr), aligned_address(addr))
macro_line|#else
DECL|macro|set_bit_unaligned
macro_line|#   define set_bit_unaligned(nr, addr)     ext2_set_bit(nr, addr)
DECL|macro|clear_bit_unaligned
macro_line|#   define clear_bit_unaligned(nr, addr)   ext2_clear_bit(nr, addr)
DECL|macro|test_bit_unaligned
macro_line|#   define test_bit_unaligned(nr, addr)    ext2_test_bit(nr, addr)
macro_line|#endif
DECL|macro|mark_de_with_sd
mdefine_line|#define mark_de_with_sd(deh)        set_bit_unaligned (DEH_Statdata, &amp;((deh)-&gt;deh_state))
DECL|macro|mark_de_without_sd
mdefine_line|#define mark_de_without_sd(deh)     clear_bit_unaligned (DEH_Statdata, &amp;((deh)-&gt;deh_state))
DECL|macro|mark_de_visible
mdefine_line|#define mark_de_visible(deh)&t;    set_bit_unaligned (DEH_Visible, &amp;((deh)-&gt;deh_state))
DECL|macro|mark_de_hidden
mdefine_line|#define mark_de_hidden(deh)&t;    clear_bit_unaligned (DEH_Visible, &amp;((deh)-&gt;deh_state))
DECL|macro|de_with_sd
mdefine_line|#define de_with_sd(deh)&t;&t;    test_bit_unaligned (DEH_Statdata, &amp;((deh)-&gt;deh_state))
DECL|macro|de_visible
mdefine_line|#define de_visible(deh)&t;    &t;    test_bit_unaligned (DEH_Visible, &amp;((deh)-&gt;deh_state))
DECL|macro|de_hidden
mdefine_line|#define de_hidden(deh)&t;    &t;    !test_bit_unaligned (DEH_Visible, &amp;((deh)-&gt;deh_state))
r_extern
r_void
id|make_empty_dir_item_v1
(paren
r_char
op_star
id|body
comma
id|__u32
id|dirid
comma
id|__u32
id|objid
comma
id|__u32
id|par_dirid
comma
id|__u32
id|par_objid
)paren
suffix:semicolon
r_extern
r_void
id|make_empty_dir_item
(paren
r_char
op_star
id|body
comma
id|__u32
id|dirid
comma
id|__u32
id|objid
comma
id|__u32
id|par_dirid
comma
id|__u32
id|par_objid
)paren
suffix:semicolon
multiline_comment|/* array of the entry headers */
multiline_comment|/* get item body */
DECL|macro|B_I_PITEM
mdefine_line|#define B_I_PITEM(bh,ih) ( (bh)-&gt;b_data + ih_location(ih) )
DECL|macro|B_I_DEH
mdefine_line|#define B_I_DEH(bh,ih) ((struct reiserfs_de_head *)(B_I_PITEM(bh,ih)))
multiline_comment|/* length of the directory entry in directory item. This define&n;   calculates length of i-th directory entry using directory entry&n;   locations from dir entry head. When it calculates length of 0-th&n;   directory entry, it uses length of whole item in place of entry&n;   location of the non-existent following entry in the calculation.&n;   See picture above.*/
multiline_comment|/*&n;#define I_DEH_N_ENTRY_LENGTH(ih,deh,i) &bslash;&n;((i) ? (deh_location((deh)-1) - deh_location((deh))) : (ih_item_len((ih)) - deh_location((deh))))&n;*/
DECL|function|entry_length
r_static
r_inline
r_int
id|entry_length
(paren
r_const
r_struct
id|buffer_head
op_star
id|bh
comma
r_const
r_struct
id|item_head
op_star
id|ih
comma
r_int
id|pos_in_item
)paren
(brace
r_struct
id|reiserfs_de_head
op_star
id|deh
suffix:semicolon
id|deh
op_assign
id|B_I_DEH
(paren
id|bh
comma
id|ih
)paren
op_plus
id|pos_in_item
suffix:semicolon
r_if
c_cond
(paren
id|pos_in_item
)paren
r_return
id|deh_location
c_func
(paren
id|deh
op_minus
l_int|1
)paren
op_minus
id|deh_location
c_func
(paren
id|deh
)paren
suffix:semicolon
r_return
id|ih_item_len
c_func
(paren
id|ih
)paren
op_minus
id|deh_location
c_func
(paren
id|deh
)paren
suffix:semicolon
)brace
multiline_comment|/* number of entries in the directory item, depends on ENTRY_COUNT being at the start of directory dynamic data. */
DECL|macro|I_ENTRY_COUNT
mdefine_line|#define I_ENTRY_COUNT(ih) (ih_entry_count((ih)))
multiline_comment|/* name by bh, ih and entry_num */
DECL|macro|B_I_E_NAME
mdefine_line|#define B_I_E_NAME(bh,ih,entry_num) ((char *)(bh-&gt;b_data + ih_location(ih) + deh_location(B_I_DEH(bh,ih)+(entry_num))))
singleline_comment|// two entries per block (at least)
singleline_comment|//#define REISERFS_MAX_NAME_LEN(block_size) 
singleline_comment|//((block_size - BLKH_SIZE - IH_SIZE - DEH_SIZE * 2) / 2)
DECL|macro|REISERFS_MAX_NAME_LEN
mdefine_line|#define REISERFS_MAX_NAME_LEN(block_size) 255
multiline_comment|/* this structure is used for operations on directory entries. It is&n;   not a disk structure. */
multiline_comment|/* When reiserfs_find_entry or search_by_entry_key find directory&n;   entry, they return filled reiserfs_dir_entry structure */
DECL|struct|reiserfs_dir_entry
r_struct
id|reiserfs_dir_entry
(brace
DECL|member|de_bh
r_struct
id|buffer_head
op_star
id|de_bh
suffix:semicolon
DECL|member|de_item_num
r_int
id|de_item_num
suffix:semicolon
DECL|member|de_ih
r_struct
id|item_head
op_star
id|de_ih
suffix:semicolon
DECL|member|de_entry_num
r_int
id|de_entry_num
suffix:semicolon
DECL|member|de_deh
r_struct
id|reiserfs_de_head
op_star
id|de_deh
suffix:semicolon
DECL|member|de_entrylen
r_int
id|de_entrylen
suffix:semicolon
DECL|member|de_namelen
r_int
id|de_namelen
suffix:semicolon
DECL|member|de_name
r_char
op_star
id|de_name
suffix:semicolon
DECL|member|de_gen_number_bit_string
r_char
op_star
id|de_gen_number_bit_string
suffix:semicolon
DECL|member|de_dir_id
id|__u32
id|de_dir_id
suffix:semicolon
DECL|member|de_objectid
id|__u32
id|de_objectid
suffix:semicolon
DECL|member|de_entry_key
r_struct
id|cpu_key
id|de_entry_key
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* these defines are useful when a particular member of a reiserfs_dir_entry is needed */
multiline_comment|/* pointer to file name, stored in entry */
DECL|macro|B_I_DEH_ENTRY_FILE_NAME
mdefine_line|#define B_I_DEH_ENTRY_FILE_NAME(bh,ih,deh) (B_I_PITEM (bh, ih) + deh_location(deh))
multiline_comment|/* length of name */
DECL|macro|I_DEH_N_ENTRY_FILE_NAME_LENGTH
mdefine_line|#define I_DEH_N_ENTRY_FILE_NAME_LENGTH(ih,deh,entry_num) &bslash;&n;(I_DEH_N_ENTRY_LENGTH (ih, deh, entry_num) - (de_with_sd (deh) ? SD_SIZE : 0))
multiline_comment|/* hash value occupies bits from 7 up to 30 */
DECL|macro|GET_HASH_VALUE
mdefine_line|#define GET_HASH_VALUE(offset) ((offset) &amp; 0x7fffff80LL)
multiline_comment|/* generation number occupies 7 bits starting from 0 up to 6 */
DECL|macro|GET_GENERATION_NUMBER
mdefine_line|#define GET_GENERATION_NUMBER(offset) ((offset) &amp; 0x7fLL)
DECL|macro|MAX_GENERATION_NUMBER
mdefine_line|#define MAX_GENERATION_NUMBER  127
DECL|macro|SET_GENERATION_NUMBER
mdefine_line|#define SET_GENERATION_NUMBER(offset,gen_number) (GET_HASH_VALUE(offset)|(gen_number))
multiline_comment|/*&n; * Picture represents an internal node of the reiserfs tree&n; *  ______________________________________________________&n; * |      |  Array of     |  Array of         |  Free     |&n; * |block |    keys       |  pointers         | space     |&n; * | head |      N        |      N+1          |           |&n; * |______|_______________|___________________|___________|&n; */
multiline_comment|/***************************************************************************/
multiline_comment|/*                      DISK CHILD                                         */
multiline_comment|/***************************************************************************/
multiline_comment|/* Disk child pointer: The pointer from an internal node of the tree&n;   to a node that is on disk. */
DECL|struct|disk_child
r_struct
id|disk_child
(brace
DECL|member|dc_block_number
id|__u32
id|dc_block_number
suffix:semicolon
multiline_comment|/* Disk child&squot;s block number. */
DECL|member|dc_size
id|__u16
id|dc_size
suffix:semicolon
multiline_comment|/* Disk child&squot;s used space.   */
DECL|member|dc_reserved
id|__u16
id|dc_reserved
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|DC_SIZE
mdefine_line|#define DC_SIZE (sizeof(struct disk_child))
DECL|macro|dc_block_number
mdefine_line|#define dc_block_number(dc_p)&t;(le32_to_cpu((dc_p)-&gt;dc_block_number))
DECL|macro|dc_size
mdefine_line|#define dc_size(dc_p)&t;&t;(le16_to_cpu((dc_p)-&gt;dc_size))
DECL|macro|put_dc_block_number
mdefine_line|#define put_dc_block_number(dc_p, val)   do { (dc_p)-&gt;dc_block_number = cpu_to_le32(val); } while(0)
DECL|macro|put_dc_size
mdefine_line|#define put_dc_size(dc_p, val)   do { (dc_p)-&gt;dc_size = cpu_to_le16(val); } while(0)
multiline_comment|/* Get disk child by buffer header and position in the tree node. */
DECL|macro|B_N_CHILD
mdefine_line|#define B_N_CHILD(p_s_bh,n_pos)  ((struct disk_child *)&bslash;&n;((p_s_bh)-&gt;b_data+BLKH_SIZE+B_NR_ITEMS(p_s_bh)*KEY_SIZE+DC_SIZE*(n_pos)))
multiline_comment|/* Get disk child number by buffer header and position in the tree node. */
DECL|macro|B_N_CHILD_NUM
mdefine_line|#define B_N_CHILD_NUM(p_s_bh,n_pos) (dc_block_number(B_N_CHILD(p_s_bh,n_pos)))
DECL|macro|PUT_B_N_CHILD_NUM
mdefine_line|#define PUT_B_N_CHILD_NUM(p_s_bh,n_pos, val) (put_dc_block_number(B_N_CHILD(p_s_bh,n_pos), val ))
multiline_comment|/* maximal value of field child_size in structure disk_child */
multiline_comment|/* child size is the combined size of all items and their headers */
DECL|macro|MAX_CHILD_SIZE
mdefine_line|#define MAX_CHILD_SIZE(bh) ((int)( (bh)-&gt;b_size - BLKH_SIZE ))
multiline_comment|/* amount of used space in buffer (not including block head) */
DECL|macro|B_CHILD_SIZE
mdefine_line|#define B_CHILD_SIZE(cur) (MAX_CHILD_SIZE(cur)-(B_FREE_SPACE(cur)))
multiline_comment|/* max and min number of keys in internal node */
DECL|macro|MAX_NR_KEY
mdefine_line|#define MAX_NR_KEY(bh) ( (MAX_CHILD_SIZE(bh)-DC_SIZE)/(KEY_SIZE+DC_SIZE) )
DECL|macro|MIN_NR_KEY
mdefine_line|#define MIN_NR_KEY(bh)    (MAX_NR_KEY(bh)/2)
multiline_comment|/***************************************************************************/
multiline_comment|/*                      PATH STRUCTURES AND DEFINES                        */
multiline_comment|/***************************************************************************/
multiline_comment|/* Search_by_key fills up the path from the root to the leaf as it descends the tree looking for the&n;   key.  It uses reiserfs_bread to try to find buffers in the cache given their block number.  If it&n;   does not find them in the cache it reads them from disk.  For each node search_by_key finds using&n;   reiserfs_bread it then uses bin_search to look through that node.  bin_search will find the&n;   position of the block_number of the next node if it is looking through an internal node.  If it&n;   is looking through a leaf node bin_search will find the position of the item which has key either&n;   equal to given key, or which is the maximal key less than the given key. */
DECL|struct|path_element
r_struct
id|path_element
(brace
DECL|member|pe_buffer
r_struct
id|buffer_head
op_star
id|pe_buffer
suffix:semicolon
multiline_comment|/* Pointer to the buffer at the path in the tree. */
DECL|member|pe_position
r_int
id|pe_position
suffix:semicolon
multiline_comment|/* Position in the tree node which is placed in the */
multiline_comment|/* buffer above.                                  */
)brace
suffix:semicolon
DECL|macro|MAX_HEIGHT
mdefine_line|#define MAX_HEIGHT 5 /* maximal height of a tree. don&squot;t change this without changing JOURNAL_PER_BALANCE_CNT */
DECL|macro|EXTENDED_MAX_HEIGHT
mdefine_line|#define EXTENDED_MAX_HEIGHT         7 /* Must be equals MAX_HEIGHT + FIRST_PATH_ELEMENT_OFFSET */
DECL|macro|FIRST_PATH_ELEMENT_OFFSET
mdefine_line|#define FIRST_PATH_ELEMENT_OFFSET   2 /* Must be equal to at least 2. */
DECL|macro|ILLEGAL_PATH_ELEMENT_OFFSET
mdefine_line|#define ILLEGAL_PATH_ELEMENT_OFFSET 1 /* Must be equal to FIRST_PATH_ELEMENT_OFFSET - 1 */
DECL|macro|MAX_FEB_SIZE
mdefine_line|#define MAX_FEB_SIZE 6   /* this MUST be MAX_HEIGHT + 1. See about FEB below */
multiline_comment|/* We need to keep track of who the ancestors of nodes are.  When we&n;   perform a search we record which nodes were visited while&n;   descending the tree looking for the node we searched for. This list&n;   of nodes is called the path.  This information is used while&n;   performing balancing.  Note that this path information may become&n;   invalid, and this means we must check it when using it to see if it&n;   is still valid. You&squot;ll need to read search_by_key and the comments&n;   in it, especially about decrement_counters_in_path(), to understand&n;   this structure.  &n;&n;Paths make the code so much harder to work with and debug.... An&n;enormous number of bugs are due to them, and trying to write or modify&n;code that uses them just makes my head hurt.  They are based on an&n;excessive effort to avoid disturbing the precious VFS code.:-( The&n;gods only know how we are going to SMP the code that uses them.&n;znodes are the way! */
DECL|struct|path
r_struct
id|path
(brace
DECL|member|path_length
r_int
id|path_length
suffix:semicolon
multiline_comment|/* Length of the array above.   */
DECL|member|path_elements
r_struct
id|path_element
id|path_elements
(braket
id|EXTENDED_MAX_HEIGHT
)braket
suffix:semicolon
multiline_comment|/* Array of the path elements.  */
DECL|member|pos_in_item
r_int
id|pos_in_item
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|pos_in_item
mdefine_line|#define pos_in_item(path) ((path)-&gt;pos_in_item)
DECL|macro|INITIALIZE_PATH
mdefine_line|#define INITIALIZE_PATH(var) &bslash;&n;struct path var = {ILLEGAL_PATH_ELEMENT_OFFSET, }
multiline_comment|/* Get path element by path and path position. */
DECL|macro|PATH_OFFSET_PELEMENT
mdefine_line|#define PATH_OFFSET_PELEMENT(p_s_path,n_offset)  ((p_s_path)-&gt;path_elements +(n_offset))
multiline_comment|/* Get buffer header at the path by path and path position. */
DECL|macro|PATH_OFFSET_PBUFFER
mdefine_line|#define PATH_OFFSET_PBUFFER(p_s_path,n_offset)   (PATH_OFFSET_PELEMENT(p_s_path,n_offset)-&gt;pe_buffer)
multiline_comment|/* Get position in the element at the path by path and path position. */
DECL|macro|PATH_OFFSET_POSITION
mdefine_line|#define PATH_OFFSET_POSITION(p_s_path,n_offset) (PATH_OFFSET_PELEMENT(p_s_path,n_offset)-&gt;pe_position)
DECL|macro|PATH_PLAST_BUFFER
mdefine_line|#define PATH_PLAST_BUFFER(p_s_path) (PATH_OFFSET_PBUFFER((p_s_path), (p_s_path)-&gt;path_length))
multiline_comment|/* you know, to the person who didn&squot;t&n;                                   write this the macro name does not&n;                                   at first suggest what it does.&n;                                   Maybe POSITION_FROM_PATH_END? Or&n;                                   maybe we should just focus on&n;                                   dumping paths... -Hans */
DECL|macro|PATH_LAST_POSITION
mdefine_line|#define PATH_LAST_POSITION(p_s_path) (PATH_OFFSET_POSITION((p_s_path), (p_s_path)-&gt;path_length))
DECL|macro|PATH_PITEM_HEAD
mdefine_line|#define PATH_PITEM_HEAD(p_s_path)    B_N_PITEM_HEAD(PATH_PLAST_BUFFER(p_s_path),PATH_LAST_POSITION(p_s_path))
multiline_comment|/* in do_balance leaf has h == 0 in contrast with path structure,&n;   where root has level == 0. That is why we need these defines */
DECL|macro|PATH_H_PBUFFER
mdefine_line|#define PATH_H_PBUFFER(p_s_path, h) PATH_OFFSET_PBUFFER (p_s_path, p_s_path-&gt;path_length - (h))&t;/* tb-&gt;S[h] */
DECL|macro|PATH_H_PPARENT
mdefine_line|#define PATH_H_PPARENT(path, h) PATH_H_PBUFFER (path, (h) + 1)&t;&t;&t;/* tb-&gt;F[h] or tb-&gt;S[0]-&gt;b_parent */
DECL|macro|PATH_H_POSITION
mdefine_line|#define PATH_H_POSITION(path, h) PATH_OFFSET_POSITION (path, path-&gt;path_length - (h))&t;
DECL|macro|PATH_H_B_ITEM_ORDER
mdefine_line|#define PATH_H_B_ITEM_ORDER(path, h) PATH_H_POSITION(path, h + 1)&t;&t;/* tb-&gt;S[h]-&gt;b_item_order */
DECL|macro|PATH_H_PATH_OFFSET
mdefine_line|#define PATH_H_PATH_OFFSET(p_s_path, n_h) ((p_s_path)-&gt;path_length - (n_h))
DECL|macro|get_last_bh
mdefine_line|#define get_last_bh(path) PATH_PLAST_BUFFER(path)
DECL|macro|get_ih
mdefine_line|#define get_ih(path) PATH_PITEM_HEAD(path)
DECL|macro|get_item_pos
mdefine_line|#define get_item_pos(path) PATH_LAST_POSITION(path)
DECL|macro|get_item
mdefine_line|#define get_item(path) ((void *)B_N_PITEM(PATH_PLAST_BUFFER(path), PATH_LAST_POSITION (path)))
DECL|macro|item_moved
mdefine_line|#define item_moved(ih,path) comp_items(ih, path)
DECL|macro|path_changed
mdefine_line|#define path_changed(ih,path) comp_items (ih, path)
multiline_comment|/***************************************************************************/
multiline_comment|/*                       MISC                                              */
multiline_comment|/***************************************************************************/
multiline_comment|/* Size of pointer to the unformatted node. */
DECL|macro|UNFM_P_SIZE
mdefine_line|#define UNFM_P_SIZE (sizeof(unp_t))
singleline_comment|// in in-core inode key is stored on le form
DECL|macro|INODE_PKEY
mdefine_line|#define INODE_PKEY(inode) ((struct key *)(REISERFS_I(inode)-&gt;i_key))
DECL|macro|MAX_UL_INT
mdefine_line|#define MAX_UL_INT 0xffffffff
DECL|macro|MAX_INT
mdefine_line|#define MAX_INT    0x7ffffff
DECL|macro|MAX_US_INT
mdefine_line|#define MAX_US_INT 0xffff
singleline_comment|// reiserfs version 2 has max offset 60 bits. Version 1 - 32 bit offset
DECL|macro|U32_MAX
mdefine_line|#define U32_MAX (~(__u32)0)
DECL|function|max_reiserfs_offset
r_static
r_inline
id|loff_t
id|max_reiserfs_offset
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_if
c_cond
(paren
id|get_inode_item_key_version
c_func
(paren
id|inode
)paren
op_eq
id|KEY_FORMAT_3_5
)paren
r_return
(paren
id|loff_t
)paren
id|U32_MAX
suffix:semicolon
r_return
(paren
id|loff_t
)paren
(paren
(paren
op_complement
(paren
id|__u64
)paren
l_int|0
)paren
op_rshift
l_int|4
)paren
suffix:semicolon
)brace
multiline_comment|/*#define MAX_KEY_UNIQUENESS&t;MAX_UL_INT*/
DECL|macro|MAX_KEY_OBJECTID
mdefine_line|#define MAX_KEY_OBJECTID&t;MAX_UL_INT
DECL|macro|MAX_B_NUM
mdefine_line|#define MAX_B_NUM  MAX_UL_INT
DECL|macro|MAX_FC_NUM
mdefine_line|#define MAX_FC_NUM MAX_US_INT
multiline_comment|/* the purpose is to detect overflow of an unsigned short */
DECL|macro|REISERFS_LINK_MAX
mdefine_line|#define REISERFS_LINK_MAX (MAX_US_INT - 1000)
multiline_comment|/* The following defines are used in reiserfs_insert_item and reiserfs_append_item  */
DECL|macro|REISERFS_KERNEL_MEM
mdefine_line|#define REISERFS_KERNEL_MEM&t;&t;0&t;/* reiserfs kernel memory mode&t;*/
DECL|macro|REISERFS_USER_MEM
mdefine_line|#define REISERFS_USER_MEM&t;&t;1&t;/* reiserfs user memory mode&t;&t;*/
DECL|macro|fs_generation
mdefine_line|#define fs_generation(s) ((s)-&gt;u.reiserfs_sb.s_generation_counter)
DECL|macro|get_generation
mdefine_line|#define get_generation(s) atomic_read (&amp;fs_generation(s))
DECL|macro|FILESYSTEM_CHANGED_TB
mdefine_line|#define FILESYSTEM_CHANGED_TB(tb)  (get_generation((tb)-&gt;tb_sb) != (tb)-&gt;fs_gen)
DECL|macro|fs_changed
mdefine_line|#define fs_changed(gen,s) (gen != get_generation (s))
multiline_comment|/***************************************************************************/
multiline_comment|/*                  FIXATE NODES                                           */
multiline_comment|/***************************************************************************/
DECL|macro|VI_TYPE_LEFT_MERGEABLE
mdefine_line|#define VI_TYPE_LEFT_MERGEABLE 1
DECL|macro|VI_TYPE_RIGHT_MERGEABLE
mdefine_line|#define VI_TYPE_RIGHT_MERGEABLE 2
multiline_comment|/* To make any changes in the tree we always first find node, that&n;   contains item to be changed/deleted or place to insert a new&n;   item. We call this node S. To do balancing we need to decide what&n;   we will shift to left/right neighbor, or to a new node, where new&n;   item will be etc. To make this analysis simpler we build virtual&n;   node. Virtual node is an array of items, that will replace items of&n;   node S. (For instance if we are going to delete an item, virtual&n;   node does not contain it). Virtual node keeps information about&n;   item sizes and types, mergeability of first and last items, sizes&n;   of all entries in directory item. We use this array of items when&n;   calculating what we can shift to neighbors and how many nodes we&n;   have to have if we do not any shiftings, if we shift to left/right&n;   neighbor or to both. */
DECL|struct|virtual_item
r_struct
id|virtual_item
(brace
DECL|member|vi_index
r_int
id|vi_index
suffix:semicolon
singleline_comment|// index in the array of item operations
DECL|member|vi_type
r_int
r_int
id|vi_type
suffix:semicolon
singleline_comment|// left/right mergeability
DECL|member|vi_item_len
r_int
r_int
id|vi_item_len
suffix:semicolon
multiline_comment|/* length of item that it will have after balancing */
DECL|member|vi_ih
r_struct
id|item_head
op_star
id|vi_ih
suffix:semicolon
DECL|member|vi_item
r_const
r_char
op_star
id|vi_item
suffix:semicolon
singleline_comment|// body of item (old or new)
DECL|member|vi_new_data
r_const
r_void
op_star
id|vi_new_data
suffix:semicolon
singleline_comment|// 0 always but paste mode
DECL|member|vi_uarea
r_void
op_star
id|vi_uarea
suffix:semicolon
singleline_comment|// item specific area
)brace
suffix:semicolon
DECL|struct|virtual_node
r_struct
id|virtual_node
(brace
DECL|member|vn_free_ptr
r_char
op_star
id|vn_free_ptr
suffix:semicolon
multiline_comment|/* this is a pointer to the free space in the buffer */
DECL|member|vn_nr_item
r_int
r_int
id|vn_nr_item
suffix:semicolon
multiline_comment|/* number of items in virtual node */
DECL|member|vn_size
r_int
id|vn_size
suffix:semicolon
multiline_comment|/* size of node , that node would have if it has unlimited size and no balancing is performed */
DECL|member|vn_mode
r_int
id|vn_mode
suffix:semicolon
multiline_comment|/* mode of balancing (paste, insert, delete, cut) */
DECL|member|vn_affected_item_num
r_int
id|vn_affected_item_num
suffix:semicolon
DECL|member|vn_pos_in_item
r_int
id|vn_pos_in_item
suffix:semicolon
DECL|member|vn_ins_ih
r_struct
id|item_head
op_star
id|vn_ins_ih
suffix:semicolon
multiline_comment|/* item header of inserted item, 0 for other modes */
DECL|member|vn_data
r_const
r_void
op_star
id|vn_data
suffix:semicolon
DECL|member|vn_vi
r_struct
id|virtual_item
op_star
id|vn_vi
suffix:semicolon
multiline_comment|/* array of items (including a new one, excluding item to be deleted) */
)brace
suffix:semicolon
multiline_comment|/***************************************************************************/
multiline_comment|/*                  TREE BALANCE                                           */
multiline_comment|/***************************************************************************/
multiline_comment|/* This temporary structure is used in tree balance algorithms, and&n;   constructed as we go to the extent that its various parts are&n;   needed.  It contains arrays of nodes that can potentially be&n;   involved in the balancing of node S, and parameters that define how&n;   each of the nodes must be balanced.  Note that in these algorithms&n;   for balancing the worst case is to need to balance the current node&n;   S and the left and right neighbors and all of their parents plus&n;   create a new node.  We implement S1 balancing for the leaf nodes&n;   and S0 balancing for the internal nodes (S1 and S0 are defined in&n;   our papers.)*/
DECL|macro|MAX_FREE_BLOCK
mdefine_line|#define MAX_FREE_BLOCK 7&t;/* size of the array of buffers to free at end of do_balance */
multiline_comment|/* maximum number of FEB blocknrs on a single level */
DECL|macro|MAX_AMOUNT_NEEDED
mdefine_line|#define MAX_AMOUNT_NEEDED 2
multiline_comment|/* someday somebody will prefix every field in this struct with tb_ */
DECL|struct|tree_balance
r_struct
id|tree_balance
(brace
DECL|member|tb_mode
r_int
id|tb_mode
suffix:semicolon
DECL|member|need_balance_dirty
r_int
id|need_balance_dirty
suffix:semicolon
DECL|member|tb_sb
r_struct
id|super_block
op_star
id|tb_sb
suffix:semicolon
DECL|member|transaction_handle
r_struct
id|reiserfs_transaction_handle
op_star
id|transaction_handle
suffix:semicolon
DECL|member|tb_path
r_struct
id|path
op_star
id|tb_path
suffix:semicolon
DECL|member|L
r_struct
id|buffer_head
op_star
id|L
(braket
id|MAX_HEIGHT
)braket
suffix:semicolon
multiline_comment|/* array of left neighbors of nodes in the path */
DECL|member|R
r_struct
id|buffer_head
op_star
id|R
(braket
id|MAX_HEIGHT
)braket
suffix:semicolon
multiline_comment|/* array of right neighbors of nodes in the path*/
DECL|member|FL
r_struct
id|buffer_head
op_star
id|FL
(braket
id|MAX_HEIGHT
)braket
suffix:semicolon
multiline_comment|/* array of fathers of the left  neighbors      */
DECL|member|FR
r_struct
id|buffer_head
op_star
id|FR
(braket
id|MAX_HEIGHT
)braket
suffix:semicolon
multiline_comment|/* array of fathers of the right neighbors      */
DECL|member|CFL
r_struct
id|buffer_head
op_star
id|CFL
(braket
id|MAX_HEIGHT
)braket
suffix:semicolon
multiline_comment|/* array of common parents of center node and its left neighbor  */
DECL|member|CFR
r_struct
id|buffer_head
op_star
id|CFR
(braket
id|MAX_HEIGHT
)braket
suffix:semicolon
multiline_comment|/* array of common parents of center node and its right neighbor */
DECL|member|FEB
r_struct
id|buffer_head
op_star
id|FEB
(braket
id|MAX_FEB_SIZE
)braket
suffix:semicolon
multiline_comment|/* array of empty buffers. Number of buffers in array equals&n;&t;&t;&t;&t;&t;     cur_blknum. */
DECL|member|used
r_struct
id|buffer_head
op_star
id|used
(braket
id|MAX_FEB_SIZE
)braket
suffix:semicolon
DECL|member|thrown
r_struct
id|buffer_head
op_star
id|thrown
(braket
id|MAX_FEB_SIZE
)braket
suffix:semicolon
DECL|member|lnum
r_int
id|lnum
(braket
id|MAX_HEIGHT
)braket
suffix:semicolon
multiline_comment|/* array of number of items which must be&n;&t;&t;&t;   shifted to the left in order to balance the&n;&t;&t;&t;   current node; for leaves includes item that&n;&t;&t;&t;   will be partially shifted; for internal&n;&t;&t;&t;   nodes, it is the number of child pointers&n;&t;&t;&t;   rather than items. It includes the new item&n;&t;&t;&t;   being created. The code sometimes subtracts&n;&t;&t;&t;   one to get the number of wholly shifted&n;&t;&t;&t;   items for other purposes. */
DECL|member|rnum
r_int
id|rnum
(braket
id|MAX_HEIGHT
)braket
suffix:semicolon
multiline_comment|/* substitute right for left in comment above */
DECL|member|lkey
r_int
id|lkey
(braket
id|MAX_HEIGHT
)braket
suffix:semicolon
multiline_comment|/* array indexed by height h mapping the key delimiting L[h] and&n;&t;&t;&t;&t;&t;       S[h] to its item number within the node CFL[h] */
DECL|member|rkey
r_int
id|rkey
(braket
id|MAX_HEIGHT
)braket
suffix:semicolon
multiline_comment|/* substitute r for l in comment above */
DECL|member|insert_size
r_int
id|insert_size
(braket
id|MAX_HEIGHT
)braket
suffix:semicolon
multiline_comment|/* the number of bytes by we are trying to add or remove from&n;&t;&t;&t;&t;&t;       S[h]. A negative value means removing.  */
DECL|member|blknum
r_int
id|blknum
(braket
id|MAX_HEIGHT
)braket
suffix:semicolon
multiline_comment|/* number of nodes that will replace node S[h] after&n;&t;&t;&t;&t;&t;       balancing on the level h of the tree.  If 0 then S is&n;&t;&t;&t;&t;&t;       being deleted, if 1 then S is remaining and no new nodes&n;&t;&t;&t;&t;&t;       are being created, if 2 or 3 then 1 or 2 new nodes is&n;&t;&t;&t;&t;&t;       being created */
multiline_comment|/* fields that are used only for balancing leaves of the tree */
DECL|member|cur_blknum
r_int
id|cur_blknum
suffix:semicolon
multiline_comment|/* number of empty blocks having been already allocated&t;&t;&t;*/
DECL|member|s0num
r_int
id|s0num
suffix:semicolon
multiline_comment|/* number of items that fall into left most  node when S[0] splits&t;*/
DECL|member|s1num
r_int
id|s1num
suffix:semicolon
multiline_comment|/* number of items that fall into first  new node when S[0] splits&t;*/
DECL|member|s2num
r_int
id|s2num
suffix:semicolon
multiline_comment|/* number of items that fall into second new node when S[0] splits&t;*/
DECL|member|lbytes
r_int
id|lbytes
suffix:semicolon
multiline_comment|/* number of bytes which can flow to the left neighbor from the&t;left&t;*/
multiline_comment|/* most liquid item that cannot be shifted from S[0] entirely&t;&t;*/
multiline_comment|/* if -1 then nothing will be partially shifted */
DECL|member|rbytes
r_int
id|rbytes
suffix:semicolon
multiline_comment|/* number of bytes which will flow to the right neighbor from the right&t;*/
multiline_comment|/* most liquid item that cannot be shifted from S[0] entirely&t;&t;*/
multiline_comment|/* if -1 then nothing will be partially shifted                           */
DECL|member|s1bytes
r_int
id|s1bytes
suffix:semicolon
multiline_comment|/* number of bytes which flow to the first  new node when S[0] splits&t;*/
multiline_comment|/* note: if S[0] splits into 3 nodes, then items do not need to be cut&t;*/
DECL|member|s2bytes
r_int
id|s2bytes
suffix:semicolon
DECL|member|buf_to_free
r_struct
id|buffer_head
op_star
id|buf_to_free
(braket
id|MAX_FREE_BLOCK
)braket
suffix:semicolon
multiline_comment|/* buffers which are to be freed after do_balance finishes by unfix_nodes */
DECL|member|vn_buf
r_char
op_star
id|vn_buf
suffix:semicolon
multiline_comment|/* kmalloced memory. Used to create&n;&t;&t;&t;&t;   virtual node and keep map of&n;&t;&t;&t;&t;   dirtied bitmap blocks */
DECL|member|vn_buf_size
r_int
id|vn_buf_size
suffix:semicolon
multiline_comment|/* size of the vn_buf */
DECL|member|tb_vn
r_struct
id|virtual_node
op_star
id|tb_vn
suffix:semicolon
multiline_comment|/* VN starts after bitmap of bitmap blocks */
DECL|member|fs_gen
r_int
id|fs_gen
suffix:semicolon
multiline_comment|/* saved value of `reiserfs_generation&squot; counter&n;&t;&t;&t;          see FILESYSTEM_CHANGED() macro in reiserfs_fs.h */
)brace
suffix:semicolon
multiline_comment|/* These are modes of balancing */
multiline_comment|/* When inserting an item. */
DECL|macro|M_INSERT
mdefine_line|#define M_INSERT&t;&squot;i&squot;
multiline_comment|/* When inserting into (directories only) or appending onto an already&n;   existant item. */
DECL|macro|M_PASTE
mdefine_line|#define M_PASTE&t;&t;&squot;p&squot;
multiline_comment|/* When deleting an item. */
DECL|macro|M_DELETE
mdefine_line|#define M_DELETE&t;&squot;d&squot;
multiline_comment|/* When truncating an item or removing an entry from a (directory) item. */
DECL|macro|M_CUT
mdefine_line|#define M_CUT &t;&t;&squot;c&squot;
multiline_comment|/* used when balancing on leaf level skipped (in reiserfsck) */
DECL|macro|M_INTERNAL
mdefine_line|#define M_INTERNAL&t;&squot;n&squot;
multiline_comment|/* When further balancing is not needed, then do_balance does not need&n;   to be called. */
DECL|macro|M_SKIP_BALANCING
mdefine_line|#define M_SKIP_BALANCING &t;&t;&squot;s&squot;
DECL|macro|M_CONVERT
mdefine_line|#define M_CONVERT&t;&squot;v&squot;
multiline_comment|/* modes of leaf_move_items */
DECL|macro|LEAF_FROM_S_TO_L
mdefine_line|#define LEAF_FROM_S_TO_L 0
DECL|macro|LEAF_FROM_S_TO_R
mdefine_line|#define LEAF_FROM_S_TO_R 1
DECL|macro|LEAF_FROM_R_TO_L
mdefine_line|#define LEAF_FROM_R_TO_L 2
DECL|macro|LEAF_FROM_L_TO_R
mdefine_line|#define LEAF_FROM_L_TO_R 3
DECL|macro|LEAF_FROM_S_TO_SNEW
mdefine_line|#define LEAF_FROM_S_TO_SNEW 4
DECL|macro|FIRST_TO_LAST
mdefine_line|#define FIRST_TO_LAST 0
DECL|macro|LAST_TO_FIRST
mdefine_line|#define LAST_TO_FIRST 1
multiline_comment|/* used in do_balance for passing parent of node information that has&n;   been gotten from tb struct */
DECL|struct|buffer_info
r_struct
id|buffer_info
(brace
DECL|member|tb
r_struct
id|tree_balance
op_star
id|tb
suffix:semicolon
DECL|member|bi_bh
r_struct
id|buffer_head
op_star
id|bi_bh
suffix:semicolon
DECL|member|bi_parent
r_struct
id|buffer_head
op_star
id|bi_parent
suffix:semicolon
DECL|member|bi_position
r_int
id|bi_position
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* there are 4 types of items: stat data, directory item, indirect, direct.&n;+-------------------+------------+--------------+------------+&n;|&t;            |  k_offset  | k_uniqueness | mergeable? |&n;+-------------------+------------+--------------+------------+&n;|     stat data     |&t;0        |      0       |   no       |&n;+-------------------+------------+--------------+------------+&n;| 1st directory item| DOT_OFFSET |DIRENTRY_UNIQUENESS|   no       | &n;| non 1st directory | hash value |              |   yes      |&n;|     item          |            |              |            |&n;+-------------------+------------+--------------+------------+&n;| indirect item     | offset + 1 |TYPE_INDIRECT |   if this is not the first indirect item of the object&n;+-------------------+------------+--------------+------------+&n;| direct item       | offset + 1 |TYPE_DIRECT   | if not this is not the first direct item of the object&n;+-------------------+------------+--------------+------------+&n;*/
DECL|struct|item_operations
r_struct
id|item_operations
(brace
DECL|member|bytes_number
r_int
(paren
op_star
id|bytes_number
)paren
(paren
r_struct
id|item_head
op_star
id|ih
comma
r_int
id|block_size
)paren
suffix:semicolon
DECL|member|decrement_key
r_void
(paren
op_star
id|decrement_key
)paren
(paren
r_struct
id|cpu_key
op_star
)paren
suffix:semicolon
DECL|member|is_left_mergeable
r_int
(paren
op_star
id|is_left_mergeable
)paren
(paren
r_struct
id|key
op_star
id|ih
comma
r_int
r_int
id|bsize
)paren
suffix:semicolon
DECL|member|print_item
r_void
(paren
op_star
id|print_item
)paren
(paren
r_struct
id|item_head
op_star
comma
r_char
op_star
id|item
)paren
suffix:semicolon
DECL|member|check_item
r_void
(paren
op_star
id|check_item
)paren
(paren
r_struct
id|item_head
op_star
comma
r_char
op_star
id|item
)paren
suffix:semicolon
DECL|member|create_vi
r_int
(paren
op_star
id|create_vi
)paren
(paren
r_struct
id|virtual_node
op_star
id|vn
comma
r_struct
id|virtual_item
op_star
id|vi
comma
r_int
id|is_affected
comma
r_int
id|insert_size
)paren
suffix:semicolon
DECL|member|check_left
r_int
(paren
op_star
id|check_left
)paren
(paren
r_struct
id|virtual_item
op_star
id|vi
comma
r_int
id|free
comma
r_int
id|start_skip
comma
r_int
id|end_skip
)paren
suffix:semicolon
DECL|member|check_right
r_int
(paren
op_star
id|check_right
)paren
(paren
r_struct
id|virtual_item
op_star
id|vi
comma
r_int
id|free
)paren
suffix:semicolon
DECL|member|part_size
r_int
(paren
op_star
id|part_size
)paren
(paren
r_struct
id|virtual_item
op_star
id|vi
comma
r_int
id|from
comma
r_int
id|to
)paren
suffix:semicolon
DECL|member|unit_num
r_int
(paren
op_star
id|unit_num
)paren
(paren
r_struct
id|virtual_item
op_star
id|vi
)paren
suffix:semicolon
DECL|member|print_vi
r_void
(paren
op_star
id|print_vi
)paren
(paren
r_struct
id|virtual_item
op_star
id|vi
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|item_operations
id|stat_data_ops
comma
id|indirect_ops
comma
id|direct_ops
comma
id|direntry_ops
suffix:semicolon
r_extern
r_struct
id|item_operations
op_star
id|item_ops
(braket
id|TYPE_ANY
op_plus
l_int|1
)braket
suffix:semicolon
DECL|macro|op_bytes_number
mdefine_line|#define op_bytes_number(ih,bsize)                    item_ops[le_ih_k_type (ih)]-&gt;bytes_number (ih, bsize)
DECL|macro|op_is_left_mergeable
mdefine_line|#define op_is_left_mergeable(key,bsize)              item_ops[le_key_k_type (le_key_version (key), key)]-&gt;is_left_mergeable (key, bsize)
DECL|macro|op_print_item
mdefine_line|#define op_print_item(ih,item)                       item_ops[le_ih_k_type (ih)]-&gt;print_item (ih, item)
DECL|macro|op_check_item
mdefine_line|#define op_check_item(ih,item)                       item_ops[le_ih_k_type (ih)]-&gt;check_item (ih, item)
DECL|macro|op_create_vi
mdefine_line|#define op_create_vi(vn,vi,is_affected,insert_size)  item_ops[le_ih_k_type ((vi)-&gt;vi_ih)]-&gt;create_vi (vn,vi,is_affected,insert_size)
DECL|macro|op_check_left
mdefine_line|#define op_check_left(vi,free,start_skip,end_skip) item_ops[(vi)-&gt;vi_index]-&gt;check_left (vi, free, start_skip, end_skip)
DECL|macro|op_check_right
mdefine_line|#define op_check_right(vi,free)                      item_ops[(vi)-&gt;vi_index]-&gt;check_right (vi, free)
DECL|macro|op_part_size
mdefine_line|#define op_part_size(vi,from,to)                     item_ops[(vi)-&gt;vi_index]-&gt;part_size (vi, from, to)
DECL|macro|op_unit_num
mdefine_line|#define op_unit_num(vi)&t;&t;&t;&t;     item_ops[(vi)-&gt;vi_index]-&gt;unit_num (vi)
DECL|macro|op_print_vi
mdefine_line|#define op_print_vi(vi)                              item_ops[(vi)-&gt;vi_index]-&gt;print_vi (vi)
DECL|macro|COMP_KEYS
mdefine_line|#define COMP_KEYS comp_keys
DECL|macro|COMP_SHORT_KEYS
mdefine_line|#define COMP_SHORT_KEYS comp_short_keys
multiline_comment|/*#define keys_of_same_object comp_short_keys*/
multiline_comment|/* number of blocks pointed to by the indirect item */
DECL|macro|I_UNFM_NUM
mdefine_line|#define I_UNFM_NUM(p_s_ih)&t;( ih_item_len(p_s_ih) / UNFM_P_SIZE )
multiline_comment|/* the used space within the unformatted node corresponding to pos within the item pointed to by ih */
DECL|macro|I_POS_UNFM_SIZE
mdefine_line|#define I_POS_UNFM_SIZE(ih,pos,size) (((pos) == I_UNFM_NUM(ih) - 1 ) ? (size) - ih_free_space(ih) : (size))
multiline_comment|/* number of bytes contained by the direct item or the unformatted nodes the indirect item points to */
multiline_comment|/* get the item header */
DECL|macro|B_N_PITEM_HEAD
mdefine_line|#define B_N_PITEM_HEAD(bh,item_num) ( (struct item_head * )((bh)-&gt;b_data + BLKH_SIZE) + (item_num) )
multiline_comment|/* get key */
DECL|macro|B_N_PDELIM_KEY
mdefine_line|#define B_N_PDELIM_KEY(bh,item_num) ( (struct key * )((bh)-&gt;b_data + BLKH_SIZE) + (item_num) )
multiline_comment|/* get the key */
DECL|macro|B_N_PKEY
mdefine_line|#define B_N_PKEY(bh,item_num) ( &amp;(B_N_PITEM_HEAD(bh,item_num)-&gt;ih_key) )
multiline_comment|/* get item body */
DECL|macro|B_N_PITEM
mdefine_line|#define B_N_PITEM(bh,item_num) ( (bh)-&gt;b_data + ih_location(B_N_PITEM_HEAD((bh),(item_num))))
multiline_comment|/* get the stat data by the buffer header and the item order */
DECL|macro|B_N_STAT_DATA
mdefine_line|#define B_N_STAT_DATA(bh,nr) &bslash;&n;( (struct stat_data *)((bh)-&gt;b_data + ih_location(B_N_PITEM_HEAD((bh),(nr))) ) )
multiline_comment|/* following defines use reiserfs buffer header and item header */
multiline_comment|/* get stat-data */
DECL|macro|B_I_STAT_DATA
mdefine_line|#define B_I_STAT_DATA(bh, ih) ( (struct stat_data * )((bh)-&gt;b_data + ih_location(ih)) )
singleline_comment|// this is 3976 for size==4096
DECL|macro|MAX_DIRECT_ITEM_LEN
mdefine_line|#define MAX_DIRECT_ITEM_LEN(size) ((size) - BLKH_SIZE - 2*IH_SIZE - SD_SIZE - UNFM_P_SIZE)
multiline_comment|/* indirect items consist of entries which contain blocknrs, pos&n;   indicates which entry, and B_I_POS_UNFM_POINTER resolves to the&n;   blocknr contained by the entry pos points to */
DECL|macro|B_I_POS_UNFM_POINTER
mdefine_line|#define B_I_POS_UNFM_POINTER(bh,ih,pos) le32_to_cpu(*(((unp_t *)B_I_PITEM(bh,ih)) + (pos)))
DECL|macro|PUT_B_I_POS_UNFM_POINTER
mdefine_line|#define PUT_B_I_POS_UNFM_POINTER(bh,ih,pos, val) do {*(((unp_t *)B_I_PITEM(bh,ih)) + (pos)) = cpu_to_le32(val); } while (0)
DECL|struct|reiserfs_iget4_args
r_struct
id|reiserfs_iget4_args
(brace
DECL|member|objectid
id|__u32
id|objectid
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/***************************************************************************/
multiline_comment|/*                    FUNCTION DECLARATIONS                                */
multiline_comment|/***************************************************************************/
multiline_comment|/*#ifdef __KERNEL__*/
multiline_comment|/* journal.c see journal.c for all the comments here */
DECL|macro|JOURNAL_TRANS_HALF
mdefine_line|#define JOURNAL_TRANS_HALF 1018   /* must be correct to keep the desc and commit structs at 4k */
multiline_comment|/* first block written in a commit.  */
DECL|struct|reiserfs_journal_desc
r_struct
id|reiserfs_journal_desc
(brace
DECL|member|j_trans_id
id|__u32
id|j_trans_id
suffix:semicolon
multiline_comment|/* id of commit */
DECL|member|j_len
id|__u32
id|j_len
suffix:semicolon
multiline_comment|/* length of commit. len +1 is the commit block */
DECL|member|j_mount_id
id|__u32
id|j_mount_id
suffix:semicolon
multiline_comment|/* mount id of this trans*/
DECL|member|j_realblock
id|__u32
id|j_realblock
(braket
id|JOURNAL_TRANS_HALF
)braket
suffix:semicolon
multiline_comment|/* real locations for each block */
DECL|member|j_magic
r_char
id|j_magic
(braket
l_int|12
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* last block written in a commit */
DECL|struct|reiserfs_journal_commit
r_struct
id|reiserfs_journal_commit
(brace
DECL|member|j_trans_id
id|__u32
id|j_trans_id
suffix:semicolon
multiline_comment|/* must match j_trans_id from the desc block */
DECL|member|j_len
id|__u32
id|j_len
suffix:semicolon
multiline_comment|/* ditto */
DECL|member|j_realblock
id|__u32
id|j_realblock
(braket
id|JOURNAL_TRANS_HALF
)braket
suffix:semicolon
multiline_comment|/* real locations for each block */
DECL|member|j_digest
r_char
id|j_digest
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* md5 sum of all the blocks involved, including desc and commit. not used, kill it */
)brace
suffix:semicolon
multiline_comment|/* this header block gets written whenever a transaction is considered fully flushed, and is more recent than the&n;** last fully flushed transaction.  fully flushed means all the log blocks and all the real blocks are on disk,&n;** and this transaction does not need to be replayed.&n;*/
DECL|struct|reiserfs_journal_header
r_struct
id|reiserfs_journal_header
(brace
DECL|member|j_last_flush_trans_id
id|__u32
id|j_last_flush_trans_id
suffix:semicolon
multiline_comment|/* id of last fully flushed transaction */
DECL|member|j_first_unflushed_offset
id|__u32
id|j_first_unflushed_offset
suffix:semicolon
multiline_comment|/* offset in the log of where to start replay after a crash */
DECL|member|j_mount_id
id|__u32
id|j_mount_id
suffix:semicolon
DECL|member|jh_journal
multiline_comment|/* 12 */
r_struct
id|journal_params
id|jh_journal
suffix:semicolon
)brace
suffix:semicolon
r_extern
id|task_queue
id|reiserfs_commit_thread_tq
suffix:semicolon
r_extern
id|wait_queue_head_t
id|reiserfs_commit_thread_wait
suffix:semicolon
multiline_comment|/* biggest tunable defines are right here */
DECL|macro|JOURNAL_BLOCK_COUNT
mdefine_line|#define JOURNAL_BLOCK_COUNT 8192 /* number of blocks in the journal */
DECL|macro|JOURNAL_TRANS_MAX_DEFAULT
mdefine_line|#define JOURNAL_TRANS_MAX_DEFAULT 1024   /* biggest possible single transaction, don&squot;t change for now (8/3/99) */
DECL|macro|JOURNAL_TRANS_MIN_DEFAULT
mdefine_line|#define JOURNAL_TRANS_MIN_DEFAULT 256
DECL|macro|JOURNAL_MAX_BATCH_DEFAULT
mdefine_line|#define JOURNAL_MAX_BATCH_DEFAULT   900 /* max blocks to batch into one transaction, don&squot;t make this any bigger than 900 */
DECL|macro|JOURNAL_MIN_RATIO
mdefine_line|#define JOURNAL_MIN_RATIO 2
DECL|macro|JOURNAL_MAX_COMMIT_AGE
mdefine_line|#define JOURNAL_MAX_COMMIT_AGE 30 
DECL|macro|JOURNAL_MAX_TRANS_AGE
mdefine_line|#define JOURNAL_MAX_TRANS_AGE 30
DECL|macro|JOURNAL_PER_BALANCE_CNT
mdefine_line|#define JOURNAL_PER_BALANCE_CNT (3 * (MAX_HEIGHT-2) + 9)
multiline_comment|/* both of these can be as low as 1, or as high as you want.  The min is the&n;** number of 4k bitmap nodes preallocated on mount. New nodes are allocated&n;** as needed, and released when transactions are committed.  On release, if &n;** the current number of nodes is &gt; max, the node is freed, otherwise, &n;** it is put on a free list for faster use later.&n;*/
DECL|macro|REISERFS_MIN_BITMAP_NODES
mdefine_line|#define REISERFS_MIN_BITMAP_NODES 10 
DECL|macro|REISERFS_MAX_BITMAP_NODES
mdefine_line|#define REISERFS_MAX_BITMAP_NODES 100 
DECL|macro|JBH_HASH_SHIFT
mdefine_line|#define JBH_HASH_SHIFT 13 /* these are based on journal hash size of 8192 */
DECL|macro|JBH_HASH_MASK
mdefine_line|#define JBH_HASH_MASK 8191
multiline_comment|/* After several hours of tedious analysis, the following hash&n; * function won.  Do not mess with it... -DaveM&n; */
DECL|macro|_jhashfn
mdefine_line|#define _jhashfn(dev,block)&t;&bslash;&n;&t;((((dev)&lt;&lt;(JBH_HASH_SHIFT - 6)) ^ ((dev)&lt;&lt;(JBH_HASH_SHIFT - 9))) ^ &bslash;&n;&t; (((block)&lt;&lt;(JBH_HASH_SHIFT - 6)) ^ ((block) &gt;&gt; 13) ^ ((block) &lt;&lt; (JBH_HASH_SHIFT - 12))))
DECL|macro|journal_hash
mdefine_line|#define journal_hash(t,sb,block) ((t)[_jhashfn((kdev_t_to_nr(sb-&gt;s_dev)),(block)) &amp; JBH_HASH_MASK])
multiline_comment|/* finds n&squot;th buffer with 0 being the start of this commit.  Needs to go away, j_ap_blocks has changed&n;** since I created this.  One chunk of code in journal.c needs changing before deleting it&n;*/
DECL|macro|JOURNAL_BUFFER
mdefine_line|#define JOURNAL_BUFFER(j,n) ((j)-&gt;j_ap_blocks[((j)-&gt;j_start + (n)) % JOURNAL_BLOCK_COUNT])
r_void
id|reiserfs_commit_for_inode
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_void
id|reiserfs_update_inode_transaction
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_void
id|reiserfs_wait_on_write_block
c_func
(paren
r_struct
id|super_block
op_star
id|s
)paren
suffix:semicolon
r_void
id|reiserfs_block_writes
c_func
(paren
r_struct
id|reiserfs_transaction_handle
op_star
id|th
)paren
suffix:semicolon
r_void
id|reiserfs_allow_writes
c_func
(paren
r_struct
id|super_block
op_star
id|s
)paren
suffix:semicolon
r_void
id|reiserfs_check_lock_depth
c_func
(paren
r_char
op_star
id|caller
)paren
suffix:semicolon
r_void
id|reiserfs_prepare_for_journal
c_func
(paren
r_struct
id|super_block
op_star
comma
r_struct
id|buffer_head
op_star
id|bh
comma
r_int
id|wait
)paren
suffix:semicolon
r_void
id|reiserfs_restore_prepared_buffer
c_func
(paren
r_struct
id|super_block
op_star
comma
r_struct
id|buffer_head
op_star
id|bh
)paren
suffix:semicolon
r_int
id|journal_init
c_func
(paren
r_struct
id|super_block
op_star
comma
r_const
r_char
op_star
id|j_dev_name
comma
r_int
id|old_format
)paren
suffix:semicolon
r_int
id|journal_release
c_func
(paren
r_struct
id|reiserfs_transaction_handle
op_star
comma
r_struct
id|super_block
op_star
)paren
suffix:semicolon
r_int
id|journal_release_error
c_func
(paren
r_struct
id|reiserfs_transaction_handle
op_star
comma
r_struct
id|super_block
op_star
)paren
suffix:semicolon
r_int
id|journal_end
c_func
(paren
r_struct
id|reiserfs_transaction_handle
op_star
comma
r_struct
id|super_block
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_int
id|journal_end_sync
c_func
(paren
r_struct
id|reiserfs_transaction_handle
op_star
comma
r_struct
id|super_block
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_int
id|journal_mark_dirty_nolog
c_func
(paren
r_struct
id|reiserfs_transaction_handle
op_star
comma
r_struct
id|super_block
op_star
comma
r_struct
id|buffer_head
op_star
id|bh
)paren
suffix:semicolon
r_int
id|journal_mark_freed
c_func
(paren
r_struct
id|reiserfs_transaction_handle
op_star
comma
r_struct
id|super_block
op_star
comma
r_int
r_int
id|blocknr
)paren
suffix:semicolon
r_int
id|push_journal_writer
c_func
(paren
r_char
op_star
id|w
)paren
suffix:semicolon
r_int
id|pop_journal_writer
c_func
(paren
r_int
id|windex
)paren
suffix:semicolon
r_int
id|journal_transaction_should_end
c_func
(paren
r_struct
id|reiserfs_transaction_handle
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|reiserfs_in_journal
c_func
(paren
r_struct
id|super_block
op_star
id|p_s_sb
comma
r_int
r_int
id|bl
comma
r_int
id|searchall
comma
r_int
r_int
op_star
id|next
)paren
suffix:semicolon
r_int
id|journal_begin
c_func
(paren
r_struct
id|reiserfs_transaction_handle
op_star
comma
r_struct
id|super_block
op_star
id|p_s_sb
comma
r_int
r_int
)paren
suffix:semicolon
r_struct
id|super_block
op_star
id|reiserfs_get_super
c_func
(paren
id|kdev_t
id|dev
)paren
suffix:semicolon
r_void
id|flush_async_commits
c_func
(paren
r_struct
id|super_block
op_star
id|p_s_sb
)paren
suffix:semicolon
r_int
id|buffer_journaled
c_func
(paren
r_const
r_struct
id|buffer_head
op_star
id|bh
)paren
suffix:semicolon
r_int
id|mark_buffer_journal_new
c_func
(paren
r_struct
id|buffer_head
op_star
id|bh
)paren
suffix:semicolon
r_int
id|reiserfs_sync_all_buffers
c_func
(paren
id|kdev_t
id|dev
comma
r_int
id|wait
)paren
suffix:semicolon
r_int
id|reiserfs_sync_buffers
c_func
(paren
id|kdev_t
id|dev
comma
r_int
id|wait
)paren
suffix:semicolon
r_int
id|reiserfs_add_page_to_flush_list
c_func
(paren
r_struct
id|reiserfs_transaction_handle
op_star
comma
r_struct
id|inode
op_star
comma
r_struct
id|buffer_head
op_star
)paren
suffix:semicolon
r_int
id|reiserfs_remove_page_from_flush_list
c_func
(paren
r_struct
id|reiserfs_transaction_handle
op_star
comma
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_int
id|reiserfs_allocate_list_bitmaps
c_func
(paren
r_struct
id|super_block
op_star
id|s
comma
r_struct
id|reiserfs_list_bitmap
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* why is this kerplunked right here? */
DECL|function|reiserfs_buffer_prepared
r_static
r_inline
r_int
id|reiserfs_buffer_prepared
c_func
(paren
r_const
r_struct
id|buffer_head
op_star
id|bh
)paren
(brace
r_if
c_cond
(paren
id|bh
op_logical_and
id|test_bit
c_func
(paren
id|BH_JPrepared
comma
(paren
r_struct
id|buffer_head
op_star
)paren
op_amp
id|bh-&gt;b_state
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_else
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* buffer was journaled, waiting to get to disk */
DECL|function|buffer_journal_dirty
r_static
r_inline
r_int
id|buffer_journal_dirty
c_func
(paren
r_const
r_struct
id|buffer_head
op_star
id|bh
)paren
(brace
r_if
c_cond
(paren
id|bh
)paren
r_return
id|test_bit
c_func
(paren
id|BH_JDirty_wait
comma
(paren
r_struct
id|buffer_head
op_star
)paren
op_amp
id|bh-&gt;b_state
)paren
suffix:semicolon
r_else
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mark_buffer_notjournal_dirty
r_static
r_inline
r_int
id|mark_buffer_notjournal_dirty
c_func
(paren
r_struct
id|buffer_head
op_star
id|bh
)paren
(brace
r_if
c_cond
(paren
id|bh
)paren
id|clear_bit
c_func
(paren
id|BH_JDirty_wait
comma
op_amp
id|bh-&gt;b_state
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mark_buffer_notjournal_new
r_static
r_inline
r_int
id|mark_buffer_notjournal_new
c_func
(paren
r_struct
id|buffer_head
op_star
id|bh
)paren
(brace
r_if
c_cond
(paren
id|bh
)paren
(brace
id|clear_bit
c_func
(paren
id|BH_JNew
comma
op_amp
id|bh-&gt;b_state
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_void
id|add_save_link
(paren
r_struct
id|reiserfs_transaction_handle
op_star
id|th
comma
r_struct
id|inode
op_star
id|inode
comma
r_int
id|truncate
)paren
suffix:semicolon
r_void
id|remove_save_link
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|truncate
)paren
suffix:semicolon
multiline_comment|/* objectid.c */
id|__u32
id|reiserfs_get_unused_objectid
(paren
r_struct
id|reiserfs_transaction_handle
op_star
id|th
)paren
suffix:semicolon
r_void
id|reiserfs_release_objectid
(paren
r_struct
id|reiserfs_transaction_handle
op_star
id|th
comma
id|__u32
id|objectid_to_release
)paren
suffix:semicolon
r_int
id|reiserfs_convert_objectid_map_v1
c_func
(paren
r_struct
id|super_block
op_star
)paren
suffix:semicolon
multiline_comment|/* stree.c */
r_int
id|B_IS_IN_TREE
c_func
(paren
r_const
r_struct
id|buffer_head
op_star
)paren
suffix:semicolon
r_extern
r_inline
r_void
id|copy_short_key
(paren
r_void
op_star
id|to
comma
r_const
r_void
op_star
id|from
)paren
suffix:semicolon
r_extern
r_inline
r_void
id|copy_item_head
c_func
(paren
r_struct
id|item_head
op_star
id|p_v_to
comma
r_const
r_struct
id|item_head
op_star
id|p_v_from
)paren
suffix:semicolon
singleline_comment|// first key is in cpu form, second - le
r_extern
r_inline
r_int
id|comp_keys
(paren
r_const
r_struct
id|key
op_star
id|le_key
comma
r_const
r_struct
id|cpu_key
op_star
id|cpu_key
)paren
suffix:semicolon
r_extern
r_inline
r_int
id|comp_short_keys
(paren
r_const
r_struct
id|key
op_star
id|le_key
comma
r_const
r_struct
id|cpu_key
op_star
id|cpu_key
)paren
suffix:semicolon
r_extern
r_inline
r_void
id|le_key2cpu_key
(paren
r_struct
id|cpu_key
op_star
id|to
comma
r_const
r_struct
id|key
op_star
id|from
)paren
suffix:semicolon
singleline_comment|// both are cpu keys
r_extern
r_inline
r_int
id|comp_cpu_keys
(paren
r_const
r_struct
id|cpu_key
op_star
comma
r_const
r_struct
id|cpu_key
op_star
)paren
suffix:semicolon
r_extern
r_inline
r_int
id|comp_short_cpu_keys
(paren
r_const
r_struct
id|cpu_key
op_star
comma
r_const
r_struct
id|cpu_key
op_star
)paren
suffix:semicolon
r_extern
r_inline
r_void
id|cpu_key2cpu_key
(paren
r_struct
id|cpu_key
op_star
comma
r_const
r_struct
id|cpu_key
op_star
)paren
suffix:semicolon
singleline_comment|// both are in le form
r_extern
r_inline
r_int
id|comp_le_keys
(paren
r_const
r_struct
id|key
op_star
comma
r_const
r_struct
id|key
op_star
)paren
suffix:semicolon
r_extern
r_inline
r_int
id|comp_short_le_keys
(paren
r_const
r_struct
id|key
op_star
comma
r_const
r_struct
id|key
op_star
)paren
suffix:semicolon
singleline_comment|//
singleline_comment|// get key version from on disk key - kludge
singleline_comment|//
DECL|function|le_key_version
r_static
r_inline
r_int
id|le_key_version
(paren
r_const
r_struct
id|key
op_star
id|key
)paren
(brace
r_int
id|type
suffix:semicolon
id|type
op_assign
id|offset_v2_k_type
c_func
(paren
op_amp
(paren
id|key-&gt;u.k_offset_v2
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|type
op_ne
id|TYPE_DIRECT
op_logical_and
id|type
op_ne
id|TYPE_INDIRECT
op_logical_and
id|type
op_ne
id|TYPE_DIRENTRY
)paren
r_return
id|KEY_FORMAT_3_5
suffix:semicolon
r_return
id|KEY_FORMAT_3_6
suffix:semicolon
)brace
DECL|function|copy_key
r_static
r_inline
r_void
id|copy_key
(paren
r_struct
id|key
op_star
id|to
comma
r_const
r_struct
id|key
op_star
id|from
)paren
(brace
id|memcpy
(paren
id|to
comma
id|from
comma
id|KEY_SIZE
)paren
suffix:semicolon
)brace
r_int
id|comp_items
(paren
r_const
r_struct
id|item_head
op_star
id|stored_ih
comma
r_const
r_struct
id|path
op_star
id|p_s_path
)paren
suffix:semicolon
r_const
r_struct
id|key
op_star
id|get_rkey
(paren
r_const
r_struct
id|path
op_star
id|p_s_chk_path
comma
r_const
r_struct
id|super_block
op_star
id|p_s_sb
)paren
suffix:semicolon
r_inline
r_int
id|bin_search
(paren
r_const
r_void
op_star
id|p_v_key
comma
r_const
r_void
op_star
id|p_v_base
comma
r_int
id|p_n_num
comma
r_int
id|p_n_width
comma
r_int
op_star
id|p_n_pos
)paren
suffix:semicolon
r_int
id|search_by_key
(paren
r_struct
id|super_block
op_star
comma
r_const
r_struct
id|cpu_key
op_star
comma
r_struct
id|path
op_star
comma
r_int
)paren
suffix:semicolon
DECL|macro|search_item
mdefine_line|#define search_item(s,key,path) search_by_key (s, key, path, DISK_LEAF_NODE_LEVEL)
r_int
id|search_for_position_by_key
(paren
r_struct
id|super_block
op_star
id|p_s_sb
comma
r_const
r_struct
id|cpu_key
op_star
id|p_s_cpu_key
comma
r_struct
id|path
op_star
id|p_s_search_path
)paren
suffix:semicolon
r_extern
r_inline
r_void
id|decrement_bcount
(paren
r_struct
id|buffer_head
op_star
id|p_s_bh
)paren
suffix:semicolon
r_void
id|decrement_counters_in_path
(paren
r_struct
id|path
op_star
id|p_s_search_path
)paren
suffix:semicolon
r_void
id|pathrelse
(paren
r_struct
id|path
op_star
id|p_s_search_path
)paren
suffix:semicolon
r_int
id|reiserfs_check_path
c_func
(paren
r_struct
id|path
op_star
id|p
)paren
suffix:semicolon
r_void
id|pathrelse_and_restore
(paren
r_struct
id|super_block
op_star
id|s
comma
r_struct
id|path
op_star
id|p_s_search_path
)paren
suffix:semicolon
r_int
id|reiserfs_insert_item
(paren
r_struct
id|reiserfs_transaction_handle
op_star
id|th
comma
r_struct
id|path
op_star
id|path
comma
r_const
r_struct
id|cpu_key
op_star
id|key
comma
r_struct
id|item_head
op_star
id|ih
comma
r_const
r_char
op_star
id|body
)paren
suffix:semicolon
r_int
id|reiserfs_paste_into_item
(paren
r_struct
id|reiserfs_transaction_handle
op_star
id|th
comma
r_struct
id|path
op_star
id|path
comma
r_const
r_struct
id|cpu_key
op_star
id|key
comma
r_const
r_char
op_star
id|body
comma
r_int
id|paste_size
)paren
suffix:semicolon
r_int
id|reiserfs_cut_from_item
(paren
r_struct
id|reiserfs_transaction_handle
op_star
id|th
comma
r_struct
id|path
op_star
id|path
comma
r_struct
id|cpu_key
op_star
id|key
comma
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|page
op_star
id|page
comma
id|loff_t
id|new_file_size
)paren
suffix:semicolon
r_int
id|reiserfs_delete_item
(paren
r_struct
id|reiserfs_transaction_handle
op_star
id|th
comma
r_struct
id|path
op_star
id|path
comma
r_const
r_struct
id|cpu_key
op_star
id|key
comma
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|buffer_head
op_star
id|p_s_un_bh
)paren
suffix:semicolon
r_void
id|reiserfs_delete_solid_item
(paren
r_struct
id|reiserfs_transaction_handle
op_star
id|th
comma
r_struct
id|key
op_star
id|key
)paren
suffix:semicolon
r_void
id|reiserfs_delete_object
(paren
r_struct
id|reiserfs_transaction_handle
op_star
id|th
comma
r_struct
id|inode
op_star
id|p_s_inode
)paren
suffix:semicolon
r_void
id|reiserfs_do_truncate
(paren
r_struct
id|reiserfs_transaction_handle
op_star
id|th
comma
r_struct
id|inode
op_star
id|p_s_inode
comma
r_struct
id|page
op_star
comma
r_int
id|update_timestamps
)paren
suffix:semicolon
DECL|macro|i_block_size
mdefine_line|#define i_block_size(inode) ((inode)-&gt;i_sb-&gt;s_blocksize)
DECL|macro|file_size
mdefine_line|#define file_size(inode) ((inode)-&gt;i_size)
DECL|macro|tail_size
mdefine_line|#define tail_size(inode) (file_size (inode) &amp; (i_block_size (inode) - 1))
DECL|macro|tail_has_to_be_packed
mdefine_line|#define tail_has_to_be_packed(inode) (!dont_have_tails ((inode)-&gt;i_sb) &amp;&amp;&bslash;&n;!STORE_TAIL_IN_UNFM(file_size (inode), tail_size(inode), i_block_size (inode)))
r_void
id|padd_item
(paren
r_char
op_star
id|item
comma
r_int
id|total_length
comma
r_int
id|length
)paren
suffix:semicolon
multiline_comment|/* inode.c */
r_void
id|reiserfs_read_inode
(paren
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
r_void
id|reiserfs_read_inode2
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_void
op_star
id|p
)paren
suffix:semicolon
r_void
id|reiserfs_delete_inode
(paren
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
r_void
id|reiserfs_write_inode
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
)paren
suffix:semicolon
r_struct
id|dentry
op_star
id|reiserfs_fh_to_dentry
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
id|__u32
op_star
id|data
comma
r_int
id|len
comma
r_int
id|fhtype
comma
r_int
id|parent
)paren
suffix:semicolon
r_int
id|reiserfs_dentry_to_fh
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
id|__u32
op_star
id|data
comma
r_int
op_star
id|lenp
comma
r_int
id|need_parent
)paren
suffix:semicolon
r_int
id|reiserfs_prepare_write
c_func
(paren
r_struct
id|file
op_star
comma
r_struct
id|page
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_void
id|reiserfs_truncate_file
c_func
(paren
r_struct
id|inode
op_star
comma
r_int
id|update_timestamps
)paren
suffix:semicolon
r_void
id|make_cpu_key
(paren
r_struct
id|cpu_key
op_star
id|cpu_key
comma
r_struct
id|inode
op_star
id|inode
comma
id|loff_t
id|offset
comma
r_int
id|type
comma
r_int
id|key_length
)paren
suffix:semicolon
r_void
id|make_le_item_head
(paren
r_struct
id|item_head
op_star
id|ih
comma
r_const
r_struct
id|cpu_key
op_star
id|key
comma
r_int
id|version
comma
id|loff_t
id|offset
comma
r_int
id|type
comma
r_int
id|length
comma
r_int
id|entry_count
)paren
suffix:semicolon
r_struct
id|inode
op_star
id|reiserfs_iget
(paren
r_struct
id|super_block
op_star
id|s
comma
r_const
r_struct
id|cpu_key
op_star
id|key
)paren
suffix:semicolon
r_struct
id|inode
op_star
id|reiserfs_new_inode
(paren
r_struct
id|reiserfs_transaction_handle
op_star
id|th
comma
r_struct
id|inode
op_star
id|dir
comma
r_int
id|mode
comma
r_const
r_char
op_star
id|symname
comma
r_int
id|item_len
comma
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|inode
op_star
id|inode
comma
r_int
op_star
id|err
)paren
suffix:semicolon
r_int
id|reiserfs_sync_inode
(paren
r_struct
id|reiserfs_transaction_handle
op_star
id|th
comma
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
r_void
id|reiserfs_update_sd
(paren
r_struct
id|reiserfs_transaction_handle
op_star
id|th
comma
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
multiline_comment|/* namei.c */
r_inline
r_void
id|set_de_name_and_namelen
(paren
r_struct
id|reiserfs_dir_entry
op_star
id|de
)paren
suffix:semicolon
r_int
id|search_by_entry_key
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_const
r_struct
id|cpu_key
op_star
id|key
comma
r_struct
id|path
op_star
id|path
comma
r_struct
id|reiserfs_dir_entry
op_star
id|de
)paren
suffix:semicolon
multiline_comment|/* procfs.c */
macro_line|#if defined( CONFIG_PROC_FS ) &amp;&amp; defined( CONFIG_REISERFS_PROC_INFO )
DECL|macro|REISERFS_PROC_INFO
mdefine_line|#define REISERFS_PROC_INFO
macro_line|#else
DECL|macro|REISERFS_PROC_INFO
macro_line|#undef REISERFS_PROC_INFO
macro_line|#endif
r_int
id|reiserfs_proc_info_init
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
suffix:semicolon
r_int
id|reiserfs_proc_info_done
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
suffix:semicolon
r_struct
id|proc_dir_entry
op_star
id|reiserfs_proc_register
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_char
op_star
id|name
comma
id|read_proc_t
op_star
id|func
)paren
suffix:semicolon
r_void
id|reiserfs_proc_unregister
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_const
r_char
op_star
id|name
)paren
suffix:semicolon
r_struct
id|proc_dir_entry
op_star
id|reiserfs_proc_register_global
c_func
(paren
r_char
op_star
id|name
comma
id|read_proc_t
op_star
id|func
)paren
suffix:semicolon
r_void
id|reiserfs_proc_unregister_global
c_func
(paren
r_const
r_char
op_star
id|name
)paren
suffix:semicolon
r_int
id|reiserfs_proc_info_global_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|reiserfs_proc_info_global_done
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|reiserfs_proc_tail
c_func
(paren
r_int
id|len
comma
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
id|count
comma
r_int
op_star
id|eof
)paren
suffix:semicolon
r_int
id|reiserfs_global_version_in_proc
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
id|count
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
r_int
id|reiserfs_version_in_proc
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
id|count
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
r_int
id|reiserfs_super_in_proc
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
id|count
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
r_int
id|reiserfs_per_level_in_proc
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
id|count
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
r_int
id|reiserfs_bitmap_in_proc
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
id|count
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
r_int
id|reiserfs_on_disk_super_in_proc
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
id|count
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
r_int
id|reiserfs_oidmap_in_proc
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
id|count
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
r_int
id|reiserfs_journal_in_proc
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
id|count
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
macro_line|#if defined( REISERFS_PROC_INFO )
DECL|macro|PROC_EXP
mdefine_line|#define PROC_EXP( e )   e
DECL|macro|MAX
mdefine_line|#define MAX( a, b ) ( ( ( a ) &gt; ( b ) ) ? ( a ) : ( b ) )
DECL|macro|__PINFO
mdefine_line|#define __PINFO( sb ) ( sb ) -&gt; u.reiserfs_sb.s_proc_info_data
DECL|macro|PROC_INFO_MAX
mdefine_line|#define PROC_INFO_MAX( sb, field, value )&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    __PINFO( sb ).field =&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;        MAX( ( sb ) -&gt; u.reiserfs_sb.s_proc_info_data.field, value )
DECL|macro|PROC_INFO_INC
mdefine_line|#define PROC_INFO_INC( sb, field ) ( ++ ( __PINFO( sb ).field ) )
DECL|macro|PROC_INFO_ADD
mdefine_line|#define PROC_INFO_ADD( sb, field, val ) ( __PINFO( sb ).field += ( val ) )
DECL|macro|PROC_INFO_BH_STAT
mdefine_line|#define PROC_INFO_BH_STAT( sb, bh, level )&t;&t;&t;&t;&t;&t;&t;&bslash;&n;    PROC_INFO_INC( sb, sbk_read_at[ ( level ) ] );&t;&t;&t;&t;&t;&t;&bslash;&n;    PROC_INFO_ADD( sb, free_at[ ( level ) ], B_FREE_SPACE( bh ) );&t;&bslash;&n;    PROC_INFO_ADD( sb, items_at[ ( level ) ], B_NR_ITEMS( bh ) )
macro_line|#else
DECL|macro|PROC_EXP
mdefine_line|#define PROC_EXP( e )
DECL|macro|VOID_V
mdefine_line|#define VOID_V ( ( void ) 0 )
DECL|macro|PROC_INFO_MAX
mdefine_line|#define PROC_INFO_MAX( sb, field, value ) VOID_V
DECL|macro|PROC_INFO_INC
mdefine_line|#define PROC_INFO_INC( sb, field ) VOID_V
DECL|macro|PROC_INFO_ADD
mdefine_line|#define PROC_INFO_ADD( sb, field, val ) VOID_V
DECL|macro|PROC_INFO_BH_STAT
mdefine_line|#define PROC_INFO_BH_STAT( p_s_sb, p_s_bh, n_node_level ) VOID_V
macro_line|#endif
multiline_comment|/* dir.c */
r_extern
r_struct
id|inode_operations
id|reiserfs_dir_inode_operations
suffix:semicolon
r_extern
r_struct
id|file_operations
id|reiserfs_dir_operations
suffix:semicolon
multiline_comment|/* tail_conversion.c */
r_int
id|direct2indirect
(paren
r_struct
id|reiserfs_transaction_handle
op_star
comma
r_struct
id|inode
op_star
comma
r_struct
id|path
op_star
comma
r_struct
id|buffer_head
op_star
comma
id|loff_t
)paren
suffix:semicolon
r_int
id|indirect2direct
(paren
r_struct
id|reiserfs_transaction_handle
op_star
comma
r_struct
id|inode
op_star
comma
r_struct
id|page
op_star
comma
r_struct
id|path
op_star
comma
r_const
r_struct
id|cpu_key
op_star
comma
id|loff_t
comma
r_char
op_star
)paren
suffix:semicolon
r_void
id|reiserfs_unmap_buffer
c_func
(paren
r_struct
id|buffer_head
op_star
)paren
suffix:semicolon
multiline_comment|/* file.c */
r_extern
r_struct
id|inode_operations
id|reiserfs_file_inode_operations
suffix:semicolon
r_extern
r_struct
id|file_operations
id|reiserfs_file_operations
suffix:semicolon
r_extern
r_struct
id|address_space_operations
id|reiserfs_address_space_operations
suffix:semicolon
r_int
id|get_new_buffer
(paren
r_struct
id|reiserfs_transaction_handle
op_star
id|th
comma
r_struct
id|buffer_head
op_star
comma
r_struct
id|buffer_head
op_star
op_star
comma
r_struct
id|path
op_star
)paren
suffix:semicolon
multiline_comment|/* buffer2.c */
r_struct
id|buffer_head
op_star
id|reiserfs_getblk
(paren
r_struct
id|super_block
op_star
id|super
comma
r_int
id|n_block
)paren
suffix:semicolon
r_void
id|wait_buffer_until_released
(paren
r_const
r_struct
id|buffer_head
op_star
id|bh
)paren
suffix:semicolon
r_struct
id|buffer_head
op_star
id|reiserfs_bread
(paren
r_struct
id|super_block
op_star
id|super
comma
r_int
id|n_block
)paren
suffix:semicolon
multiline_comment|/* fix_nodes.c */
macro_line|#ifdef CONFIG_REISERFS_CHECK
r_void
op_star
id|reiserfs_kmalloc
(paren
r_int
id|size
comma
r_int
id|flags
comma
r_struct
id|super_block
op_star
id|s
)paren
suffix:semicolon
r_void
id|reiserfs_kfree
(paren
r_const
r_void
op_star
id|vp
comma
r_int
id|size
comma
r_struct
id|super_block
op_star
id|s
)paren
suffix:semicolon
macro_line|#else
DECL|macro|reiserfs_kmalloc
mdefine_line|#define reiserfs_kmalloc(x, y, z) kmalloc(x, y)
DECL|macro|reiserfs_kfree
mdefine_line|#define reiserfs_kfree(x, y, z) kfree(x)
macro_line|#endif
r_int
id|fix_nodes
(paren
r_int
id|n_op_mode
comma
r_struct
id|tree_balance
op_star
id|p_s_tb
comma
r_struct
id|item_head
op_star
id|p_s_ins_ih
comma
r_const
r_void
op_star
)paren
suffix:semicolon
r_void
id|unfix_nodes
(paren
r_struct
id|tree_balance
op_star
)paren
suffix:semicolon
r_void
id|free_buffers_in_tb
(paren
r_struct
id|tree_balance
op_star
id|p_s_tb
)paren
suffix:semicolon
multiline_comment|/* prints.c */
r_void
id|reiserfs_panic
(paren
r_struct
id|super_block
op_star
id|s
comma
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
(paren
(paren
id|noreturn
)paren
)paren
suffix:semicolon
multiline_comment|/* __attribute__( ( format ( printf, 2, 3 ) ) ) */
r_void
id|reiserfs_debug
(paren
r_struct
id|super_block
op_star
id|s
comma
r_int
id|level
comma
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
suffix:semicolon
multiline_comment|/* __attribute__( ( format ( printf, 3, 4 ) ) ); */
r_void
id|print_virtual_node
(paren
r_struct
id|virtual_node
op_star
id|vn
)paren
suffix:semicolon
r_void
id|print_indirect_item
(paren
r_struct
id|buffer_head
op_star
id|bh
comma
r_int
id|item_num
)paren
suffix:semicolon
r_void
id|store_print_tb
(paren
r_struct
id|tree_balance
op_star
id|tb
)paren
suffix:semicolon
r_void
id|print_cur_tb
(paren
r_char
op_star
id|mes
)paren
suffix:semicolon
r_void
id|print_de
(paren
r_struct
id|reiserfs_dir_entry
op_star
id|de
)paren
suffix:semicolon
r_void
id|print_bi
(paren
r_struct
id|buffer_info
op_star
id|bi
comma
r_char
op_star
id|mes
)paren
suffix:semicolon
DECL|macro|PRINT_LEAF_ITEMS
mdefine_line|#define PRINT_LEAF_ITEMS 1   /* print all items */
DECL|macro|PRINT_DIRECTORY_ITEMS
mdefine_line|#define PRINT_DIRECTORY_ITEMS 2 /* print directory items */
DECL|macro|PRINT_DIRECT_ITEMS
mdefine_line|#define PRINT_DIRECT_ITEMS 4 /* print contents of direct items */
r_void
id|print_block
(paren
r_struct
id|buffer_head
op_star
id|bh
comma
dot
dot
dot
)paren
suffix:semicolon
r_void
id|print_path
(paren
r_struct
id|tree_balance
op_star
id|tb
comma
r_struct
id|path
op_star
id|path
)paren
suffix:semicolon
r_void
id|print_bmap
(paren
r_struct
id|super_block
op_star
id|s
comma
r_int
id|silent
)paren
suffix:semicolon
r_void
id|print_bmap_block
(paren
r_int
id|i
comma
r_char
op_star
id|data
comma
r_int
id|size
comma
r_int
id|silent
)paren
suffix:semicolon
multiline_comment|/*void print_super_block (struct super_block * s, char * mes);*/
r_void
id|print_objectid_map
(paren
r_struct
id|super_block
op_star
id|s
)paren
suffix:semicolon
r_void
id|print_block_head
(paren
r_struct
id|buffer_head
op_star
id|bh
comma
r_char
op_star
id|mes
)paren
suffix:semicolon
r_void
id|check_leaf
(paren
r_struct
id|buffer_head
op_star
id|bh
)paren
suffix:semicolon
r_void
id|check_internal
(paren
r_struct
id|buffer_head
op_star
id|bh
)paren
suffix:semicolon
r_void
id|print_statistics
(paren
r_struct
id|super_block
op_star
id|s
)paren
suffix:semicolon
r_char
op_star
id|reiserfs_hashname
c_func
(paren
r_int
id|code
)paren
suffix:semicolon
multiline_comment|/* lbalance.c */
r_int
id|leaf_move_items
(paren
r_int
id|shift_mode
comma
r_struct
id|tree_balance
op_star
id|tb
comma
r_int
id|mov_num
comma
r_int
id|mov_bytes
comma
r_struct
id|buffer_head
op_star
id|Snew
)paren
suffix:semicolon
r_int
id|leaf_shift_left
(paren
r_struct
id|tree_balance
op_star
id|tb
comma
r_int
id|shift_num
comma
r_int
id|shift_bytes
)paren
suffix:semicolon
r_int
id|leaf_shift_right
(paren
r_struct
id|tree_balance
op_star
id|tb
comma
r_int
id|shift_num
comma
r_int
id|shift_bytes
)paren
suffix:semicolon
r_void
id|leaf_delete_items
(paren
r_struct
id|buffer_info
op_star
id|cur_bi
comma
r_int
id|last_first
comma
r_int
id|first
comma
r_int
id|del_num
comma
r_int
id|del_bytes
)paren
suffix:semicolon
r_void
id|leaf_insert_into_buf
(paren
r_struct
id|buffer_info
op_star
id|bi
comma
r_int
id|before
comma
r_struct
id|item_head
op_star
id|inserted_item_ih
comma
r_const
r_char
op_star
id|inserted_item_body
comma
r_int
id|zeros_number
)paren
suffix:semicolon
r_void
id|leaf_paste_in_buffer
(paren
r_struct
id|buffer_info
op_star
id|bi
comma
r_int
id|pasted_item_num
comma
r_int
id|pos_in_item
comma
r_int
id|paste_size
comma
r_const
r_char
op_star
id|body
comma
r_int
id|zeros_number
)paren
suffix:semicolon
r_void
id|leaf_cut_from_buffer
(paren
r_struct
id|buffer_info
op_star
id|bi
comma
r_int
id|cut_item_num
comma
r_int
id|pos_in_item
comma
r_int
id|cut_size
)paren
suffix:semicolon
r_void
id|leaf_paste_entries
(paren
r_struct
id|buffer_head
op_star
id|bh
comma
r_int
id|item_num
comma
r_int
id|before
comma
r_int
id|new_entry_count
comma
r_struct
id|reiserfs_de_head
op_star
id|new_dehs
comma
r_const
r_char
op_star
id|records
comma
r_int
id|paste_size
)paren
suffix:semicolon
multiline_comment|/* ibalance.c */
r_int
id|balance_internal
(paren
r_struct
id|tree_balance
op_star
comma
r_int
comma
r_int
comma
r_struct
id|item_head
op_star
comma
r_struct
id|buffer_head
op_star
op_star
)paren
suffix:semicolon
multiline_comment|/* do_balance.c */
r_inline
r_void
id|do_balance_mark_leaf_dirty
(paren
r_struct
id|tree_balance
op_star
id|tb
comma
r_struct
id|buffer_head
op_star
id|bh
comma
r_int
id|flag
)paren
suffix:semicolon
DECL|macro|do_balance_mark_internal_dirty
mdefine_line|#define do_balance_mark_internal_dirty do_balance_mark_leaf_dirty
DECL|macro|do_balance_mark_sb_dirty
mdefine_line|#define do_balance_mark_sb_dirty do_balance_mark_leaf_dirty
r_void
id|do_balance
(paren
r_struct
id|tree_balance
op_star
id|tb
comma
r_struct
id|item_head
op_star
id|ih
comma
r_const
r_char
op_star
id|body
comma
r_int
id|flag
)paren
suffix:semicolon
r_void
id|reiserfs_invalidate_buffer
(paren
r_struct
id|tree_balance
op_star
id|tb
comma
r_struct
id|buffer_head
op_star
id|bh
)paren
suffix:semicolon
r_int
id|get_left_neighbor_position
(paren
r_struct
id|tree_balance
op_star
id|tb
comma
r_int
id|h
)paren
suffix:semicolon
r_int
id|get_right_neighbor_position
(paren
r_struct
id|tree_balance
op_star
id|tb
comma
r_int
id|h
)paren
suffix:semicolon
r_void
id|replace_key
(paren
r_struct
id|tree_balance
op_star
id|tb
comma
r_struct
id|buffer_head
op_star
comma
r_int
comma
r_struct
id|buffer_head
op_star
comma
r_int
)paren
suffix:semicolon
r_void
id|replace_lkey
(paren
r_struct
id|tree_balance
op_star
comma
r_int
comma
r_struct
id|item_head
op_star
)paren
suffix:semicolon
r_void
id|replace_rkey
(paren
r_struct
id|tree_balance
op_star
comma
r_int
comma
r_struct
id|item_head
op_star
)paren
suffix:semicolon
r_void
id|make_empty_node
(paren
r_struct
id|buffer_info
op_star
)paren
suffix:semicolon
r_struct
id|buffer_head
op_star
id|get_FEB
(paren
r_struct
id|tree_balance
op_star
)paren
suffix:semicolon
multiline_comment|/* bitmap.c */
r_int
id|is_reusable
(paren
r_struct
id|super_block
op_star
id|s
comma
r_int
r_int
id|block
comma
r_int
id|bit_value
)paren
suffix:semicolon
r_void
id|reiserfs_free_block
(paren
r_struct
id|reiserfs_transaction_handle
op_star
id|th
comma
r_int
r_int
)paren
suffix:semicolon
r_int
id|reiserfs_new_blocknrs
(paren
r_struct
id|reiserfs_transaction_handle
op_star
id|th
comma
r_int
r_int
op_star
id|pblocknrs
comma
r_int
r_int
id|start_from
comma
r_int
id|amount_needed
)paren
suffix:semicolon
r_int
id|reiserfs_new_unf_blocknrs
(paren
r_struct
id|reiserfs_transaction_handle
op_star
id|th
comma
r_int
r_int
op_star
id|pblocknr
comma
r_int
r_int
id|start_from
)paren
suffix:semicolon
macro_line|#ifdef REISERFS_PREALLOCATE
r_int
id|reiserfs_new_unf_blocknrs2
(paren
r_struct
id|reiserfs_transaction_handle
op_star
id|th
comma
r_struct
id|inode
op_star
id|inode
comma
r_int
r_int
op_star
id|pblocknr
comma
r_int
r_int
id|start_from
)paren
suffix:semicolon
r_void
id|reiserfs_discard_prealloc
(paren
r_struct
id|reiserfs_transaction_handle
op_star
id|th
comma
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
r_void
id|reiserfs_discard_all_prealloc
(paren
r_struct
id|reiserfs_transaction_handle
op_star
id|th
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* hashes.c */
id|__u32
id|keyed_hash
(paren
r_const
r_int
r_char
op_star
id|msg
comma
r_int
id|len
)paren
suffix:semicolon
id|__u32
id|yura_hash
(paren
r_const
r_int
r_char
op_star
id|msg
comma
r_int
id|len
)paren
suffix:semicolon
id|__u32
id|r5_hash
(paren
r_const
r_int
r_char
op_star
id|msg
comma
r_int
id|len
)paren
suffix:semicolon
multiline_comment|/* the ext2 bit routines adjust for big or little endian as&n;** appropriate for the arch, so in our laziness we use them rather&n;** than using the bit routines they call more directly.  These&n;** routines must be used when changing on disk bitmaps.  */
DECL|macro|reiserfs_test_and_set_le_bit
mdefine_line|#define reiserfs_test_and_set_le_bit   ext2_set_bit
DECL|macro|reiserfs_test_and_clear_le_bit
mdefine_line|#define reiserfs_test_and_clear_le_bit ext2_clear_bit
DECL|macro|reiserfs_test_le_bit
mdefine_line|#define reiserfs_test_le_bit           ext2_test_bit
DECL|macro|reiserfs_find_next_zero_le_bit
mdefine_line|#define reiserfs_find_next_zero_le_bit ext2_find_next_zero_bit
multiline_comment|/* sometimes reiserfs_truncate may require to allocate few new blocks&n;   to perform indirect2direct conversion. People probably used to&n;   think, that truncate should work without problems on a filesystem&n;   without free disk space. They may complain that they can not&n;   truncate due to lack of free disk space. This spare space allows us&n;   to not worry about it. 500 is probably too much, but it should be&n;   absolutely safe */
DECL|macro|SPARE_SPACE
mdefine_line|#define SPARE_SPACE 500
multiline_comment|/* prototypes from ioctl.c */
r_int
id|reiserfs_ioctl
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
r_int
id|reiserfs_unpack
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
)paren
suffix:semicolon
multiline_comment|/* ioctl&squot;s command */
DECL|macro|REISERFS_IOC_UNPACK
mdefine_line|#define REISERFS_IOC_UNPACK&t;&t;_IOW(0xCD,1,long)
macro_line|#endif /* _LINUX_REISER_FS_H */
eof
