multiline_comment|/*&n; * MTD partitioning layer definitions&n; *&n; * (C) 2000 Nicolas Pitre &lt;nico@cam.org&gt;&n; *&n; * This code is GPL&n; *&n; * $Id: partitions.h,v 1.6 2001/03/17 17:10:21 dwmw2 Exp $&n; */
macro_line|#ifndef MTD_PARTITIONS_H
DECL|macro|MTD_PARTITIONS_H
mdefine_line|#define MTD_PARTITIONS_H
macro_line|#include &lt;linux/types.h&gt;
multiline_comment|/*&n; * Partition definition structure:&n; * &n; * An array of struct partition is passed along with a MTD object to&n; * add_mtd_partitions() to create them.&n; *&n; * For each partition, these fields are available:&n; * name: string that will be used to label the partition&squot;s MTD device.&n; * size: the partition size; if defined as MTDPART_SIZ_FULL, the partition &n; * &t;will extend to the end of the master MTD device.&n; * offset: absolute starting position within the master MTD device; if &n; * &t;defined as MTDPART_OFS_APPEND, the partition will start where the &n; * &t;previous one ended.&n; * mask_flags: contains flags that have to be masked (removed) from the &n; * &t;master MTD flag set for the corresponding MTD partition.&n; * &t;For example, to force a read-only partition, simply adding &n; * &t;MTD_WRITEABLE to the mask_flags will do the trick.&n; *&n; * Note: writeable partitions require their size and offset be &n; * erasesize aligned.&n; */
DECL|struct|mtd_partition
r_struct
id|mtd_partition
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/* identifier string */
DECL|member|size
id|u_int32_t
id|size
suffix:semicolon
multiline_comment|/* partition size */
DECL|member|offset
id|u_int32_t
id|offset
suffix:semicolon
multiline_comment|/* offset within the master MTD space */
DECL|member|mask_flags
id|u_int32_t
id|mask_flags
suffix:semicolon
multiline_comment|/* master MTD flags to mask out for this partition */
)brace
suffix:semicolon
DECL|macro|MTDPART_OFS_APPEND
mdefine_line|#define MTDPART_OFS_APPEND&t;(-1)
DECL|macro|MTDPART_SIZ_FULL
mdefine_line|#define MTDPART_SIZ_FULL&t;(0)
r_int
id|add_mtd_partitions
c_func
(paren
r_struct
id|mtd_info
op_star
comma
r_struct
id|mtd_partition
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|del_mtd_partitions
c_func
(paren
r_struct
id|mtd_info
op_star
)paren
suffix:semicolon
macro_line|#endif
eof
