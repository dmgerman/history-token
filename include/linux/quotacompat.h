multiline_comment|/*&n; *&t;Definition of symbols used for backward compatible interface&n; */
macro_line|#ifndef _LINUX_QUOTACOMPAT_
DECL|macro|_LINUX_QUOTACOMPAT_
mdefine_line|#define _LINUX_QUOTACOMPAT_
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/quota.h&gt;
DECL|struct|v1c_mem_dqblk
r_struct
id|v1c_mem_dqblk
(brace
DECL|member|dqb_bhardlimit
id|__u32
id|dqb_bhardlimit
suffix:semicolon
multiline_comment|/* absolute limit on disk blks alloc */
DECL|member|dqb_bsoftlimit
id|__u32
id|dqb_bsoftlimit
suffix:semicolon
multiline_comment|/* preferred limit on disk blks */
DECL|member|dqb_curblocks
id|__u32
id|dqb_curblocks
suffix:semicolon
multiline_comment|/* current block count */
DECL|member|dqb_ihardlimit
id|__u32
id|dqb_ihardlimit
suffix:semicolon
multiline_comment|/* maximum # allocated inodes */
DECL|member|dqb_isoftlimit
id|__u32
id|dqb_isoftlimit
suffix:semicolon
multiline_comment|/* preferred inode limit */
DECL|member|dqb_curinodes
id|__u32
id|dqb_curinodes
suffix:semicolon
multiline_comment|/* current # allocated inodes */
DECL|member|dqb_btime
id|time_t
id|dqb_btime
suffix:semicolon
multiline_comment|/* time limit for excessive disk use */
DECL|member|dqb_itime
id|time_t
id|dqb_itime
suffix:semicolon
multiline_comment|/* time limit for excessive files */
)brace
suffix:semicolon
DECL|struct|v1c_dqstats
r_struct
id|v1c_dqstats
(brace
DECL|member|lookups
id|__u32
id|lookups
suffix:semicolon
DECL|member|drops
id|__u32
id|drops
suffix:semicolon
DECL|member|reads
id|__u32
id|reads
suffix:semicolon
DECL|member|writes
id|__u32
id|writes
suffix:semicolon
DECL|member|cache_hits
id|__u32
id|cache_hits
suffix:semicolon
DECL|member|allocated_dquots
id|__u32
id|allocated_dquots
suffix:semicolon
DECL|member|free_dquots
id|__u32
id|free_dquots
suffix:semicolon
DECL|member|syncs
id|__u32
id|syncs
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|v2c_mem_dqblk
r_struct
id|v2c_mem_dqblk
(brace
DECL|member|dqb_ihardlimit
r_int
r_int
id|dqb_ihardlimit
suffix:semicolon
DECL|member|dqb_isoftlimit
r_int
r_int
id|dqb_isoftlimit
suffix:semicolon
DECL|member|dqb_curinodes
r_int
r_int
id|dqb_curinodes
suffix:semicolon
DECL|member|dqb_bhardlimit
r_int
r_int
id|dqb_bhardlimit
suffix:semicolon
DECL|member|dqb_bsoftlimit
r_int
r_int
id|dqb_bsoftlimit
suffix:semicolon
DECL|member|dqb_curspace
id|qsize_t
id|dqb_curspace
suffix:semicolon
DECL|member|dqb_btime
id|__kernel_time_t
id|dqb_btime
suffix:semicolon
DECL|member|dqb_itime
id|__kernel_time_t
id|dqb_itime
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|v2c_mem_dqinfo
r_struct
id|v2c_mem_dqinfo
(brace
DECL|member|dqi_bgrace
r_int
r_int
id|dqi_bgrace
suffix:semicolon
DECL|member|dqi_igrace
r_int
r_int
id|dqi_igrace
suffix:semicolon
DECL|member|dqi_flags
r_int
r_int
id|dqi_flags
suffix:semicolon
DECL|member|dqi_blocks
r_int
r_int
id|dqi_blocks
suffix:semicolon
DECL|member|dqi_free_blk
r_int
r_int
id|dqi_free_blk
suffix:semicolon
DECL|member|dqi_free_entry
r_int
r_int
id|dqi_free_entry
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|v2c_dqstats
r_struct
id|v2c_dqstats
(brace
DECL|member|lookups
id|__u32
id|lookups
suffix:semicolon
DECL|member|drops
id|__u32
id|drops
suffix:semicolon
DECL|member|reads
id|__u32
id|reads
suffix:semicolon
DECL|member|writes
id|__u32
id|writes
suffix:semicolon
DECL|member|cache_hits
id|__u32
id|cache_hits
suffix:semicolon
DECL|member|allocated_dquots
id|__u32
id|allocated_dquots
suffix:semicolon
DECL|member|free_dquots
id|__u32
id|free_dquots
suffix:semicolon
DECL|member|syncs
id|__u32
id|syncs
suffix:semicolon
DECL|member|version
id|__u32
id|version
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|Q_COMP_QUOTAON
mdefine_line|#define Q_COMP_QUOTAON  0x0100&t;/* enable quotas */
DECL|macro|Q_COMP_QUOTAOFF
mdefine_line|#define Q_COMP_QUOTAOFF 0x0200&t;/* disable quotas */
DECL|macro|Q_COMP_SYNC
mdefine_line|#define Q_COMP_SYNC     0x0600&t;/* sync disk copy of a filesystems quotas */
DECL|macro|Q_V1_GETQUOTA
mdefine_line|#define Q_V1_GETQUOTA 0x0300&t;/* get limits and usage */
DECL|macro|Q_V1_SETQUOTA
mdefine_line|#define Q_V1_SETQUOTA 0x0400&t;/* set limits and usage */
DECL|macro|Q_V1_SETUSE
mdefine_line|#define Q_V1_SETUSE   0x0500&t;/* set usage */
DECL|macro|Q_V1_SETQLIM
mdefine_line|#define Q_V1_SETQLIM  0x0700&t;/* set limits */
DECL|macro|Q_V1_GETSTATS
mdefine_line|#define Q_V1_GETSTATS 0x0800&t;/* get collected stats */
DECL|macro|Q_V1_RSQUASH
mdefine_line|#define Q_V1_RSQUASH  0x1000&t;/* set root_squash option */
DECL|macro|Q_V2_SETQLIM
mdefine_line|#define Q_V2_SETQLIM  0x0700&t;/* set limits */
DECL|macro|Q_V2_GETINFO
mdefine_line|#define Q_V2_GETINFO  0x0900&t;/* get info about quotas - graces, flags... */
DECL|macro|Q_V2_SETINFO
mdefine_line|#define Q_V2_SETINFO  0x0A00&t;/* set info about quotas */
DECL|macro|Q_V2_SETGRACE
mdefine_line|#define Q_V2_SETGRACE 0x0B00&t;/* set inode and block grace */
DECL|macro|Q_V2_SETFLAGS
mdefine_line|#define Q_V2_SETFLAGS 0x0C00&t;/* set flags for quota */
DECL|macro|Q_V2_GETQUOTA
mdefine_line|#define Q_V2_GETQUOTA 0x0D00&t;/* get limits and usage */
DECL|macro|Q_V2_SETQUOTA
mdefine_line|#define Q_V2_SETQUOTA 0x0E00&t;/* set limits and usage */
DECL|macro|Q_V2_SETUSE
mdefine_line|#define Q_V2_SETUSE   0x0F00&t;/* set usage */
DECL|macro|Q_V2_GETSTATS
mdefine_line|#define Q_V2_GETSTATS 0x1100&t;/* get collected stats */
macro_line|#endif
eof
