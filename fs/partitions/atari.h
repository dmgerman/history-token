multiline_comment|/*&n; *  fs/partitions/atari.h&n; *  Moved by Russell King from:&n; *&n; * linux/include/linux/atari_rootsec.h&n; * definitions for Atari Rootsector layout&n; * by Andreas Schwab (schwab@ls5.informatik.uni-dortmund.de)&n; *&n; * modified for ICD/Supra partitioning scheme restricted to at most 12&n; * partitions&n; * by Guenther Kelleter (guenther@pool.informatik.rwth-aachen.de)&n; */
DECL|struct|partition_info
r_struct
id|partition_info
(brace
DECL|member|flg
id|u8
id|flg
suffix:semicolon
multiline_comment|/* bit 0: active; bit 7: bootable */
DECL|member|id
r_char
id|id
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* &quot;GEM&quot;, &quot;BGM&quot;, &quot;XGM&quot;, or other */
DECL|member|st
id|u32
id|st
suffix:semicolon
multiline_comment|/* start of partition */
DECL|member|siz
id|u32
id|siz
suffix:semicolon
multiline_comment|/* length of partition */
)brace
suffix:semicolon
DECL|struct|rootsector
r_struct
id|rootsector
(brace
DECL|member|unused
r_char
id|unused
(braket
l_int|0x156
)braket
suffix:semicolon
multiline_comment|/* room for boot code */
DECL|member|icdpart
r_struct
id|partition_info
id|icdpart
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* info for ICD-partitions 5..12 */
DECL|member|unused2
r_char
id|unused2
(braket
l_int|0xc
)braket
suffix:semicolon
DECL|member|hd_siz
id|u32
id|hd_siz
suffix:semicolon
multiline_comment|/* size of disk in blocks */
DECL|member|part
r_struct
id|partition_info
id|part
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|bsl_st
id|u32
id|bsl_st
suffix:semicolon
multiline_comment|/* start of bad sector list */
DECL|member|bsl_cnt
id|u32
id|bsl_cnt
suffix:semicolon
multiline_comment|/* length of bad sector list */
DECL|member|checksum
id|u16
id|checksum
suffix:semicolon
multiline_comment|/* checksum for bootable disks */
)brace
id|__attribute__
c_func
(paren
(paren
id|__packed__
)paren
)paren
suffix:semicolon
r_int
id|atari_partition
(paren
r_struct
id|gendisk
op_star
id|hd
comma
r_struct
id|block_device
op_star
id|bdev
comma
r_int
r_int
id|first_sector
comma
r_int
id|first_part_minor
)paren
suffix:semicolon
eof
