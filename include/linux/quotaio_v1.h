macro_line|#ifndef _LINUX_QUOTAIO_V1_H
DECL|macro|_LINUX_QUOTAIO_V1_H
mdefine_line|#define _LINUX_QUOTAIO_V1_H
macro_line|#include &lt;linux/types.h&gt;
multiline_comment|/*&n; * The following constants define the amount of time given a user&n; * before the soft limits are treated as hard limits (usually resulting&n; * in an allocation failure). The timer is started when the user crosses&n; * their soft limit, it is reset when they go below their soft limit.&n; */
DECL|macro|MAX_IQ_TIME
mdefine_line|#define MAX_IQ_TIME  604800&t;/* (7*24*60*60) 1 week */
DECL|macro|MAX_DQ_TIME
mdefine_line|#define MAX_DQ_TIME  604800&t;/* (7*24*60*60) 1 week */
multiline_comment|/*&n; * The following structure defines the format of the disk quota file&n; * (as it appears on disk) - the file is an array of these structures&n; * indexed by user or group number.&n; */
DECL|struct|v1_disk_dqblk
r_struct
id|v1_disk_dqblk
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
multiline_comment|/* absolute limit on allocated inodes */
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
multiline_comment|/* time limit for excessive inode use */
)brace
suffix:semicolon
DECL|macro|v1_dqoff
mdefine_line|#define v1_dqoff(UID)      ((loff_t)((UID) * sizeof (struct v1_disk_dqblk)))
macro_line|#endif&t;/* _LINUX_QUOTAIO_V1_H */
eof
