multiline_comment|/*&n; *  fs/partitions/mac.h&n; */
DECL|macro|MAC_PARTITION_MAGIC
mdefine_line|#define MAC_PARTITION_MAGIC&t;0x504d
multiline_comment|/* type field value for A/UX or other Unix partitions */
DECL|macro|APPLE_AUX_TYPE
mdefine_line|#define APPLE_AUX_TYPE&t;&quot;Apple_UNIX_SVR2&quot;
DECL|struct|mac_partition
r_struct
id|mac_partition
(brace
DECL|member|signature
id|__u16
id|signature
suffix:semicolon
multiline_comment|/* expected to be MAC_PARTITION_MAGIC */
DECL|member|res1
id|__u16
id|res1
suffix:semicolon
DECL|member|map_count
id|__u32
id|map_count
suffix:semicolon
multiline_comment|/* # blocks in partition map */
DECL|member|start_block
id|__u32
id|start_block
suffix:semicolon
multiline_comment|/* absolute starting block # of partition */
DECL|member|block_count
id|__u32
id|block_count
suffix:semicolon
multiline_comment|/* number of blocks in partition */
DECL|member|name
r_char
id|name
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* partition name */
DECL|member|type
r_char
id|type
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* string type description */
DECL|member|data_start
id|__u32
id|data_start
suffix:semicolon
multiline_comment|/* rel block # of first data block */
DECL|member|data_count
id|__u32
id|data_count
suffix:semicolon
multiline_comment|/* number of data blocks */
DECL|member|status
id|__u32
id|status
suffix:semicolon
multiline_comment|/* partition status bits */
DECL|member|boot_start
id|__u32
id|boot_start
suffix:semicolon
DECL|member|boot_size
id|__u32
id|boot_size
suffix:semicolon
DECL|member|boot_load
id|__u32
id|boot_load
suffix:semicolon
DECL|member|boot_load2
id|__u32
id|boot_load2
suffix:semicolon
DECL|member|boot_entry
id|__u32
id|boot_entry
suffix:semicolon
DECL|member|boot_entry2
id|__u32
id|boot_entry2
suffix:semicolon
DECL|member|boot_cksum
id|__u32
id|boot_cksum
suffix:semicolon
DECL|member|processor
r_char
id|processor
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* identifies ISA of boot */
multiline_comment|/* there is more stuff after this that we don&squot;t need */
)brace
suffix:semicolon
DECL|macro|MAC_STATUS_BOOTABLE
mdefine_line|#define MAC_STATUS_BOOTABLE&t;8&t;/* partition is bootable */
DECL|macro|MAC_DRIVER_MAGIC
mdefine_line|#define MAC_DRIVER_MAGIC&t;0x4552
multiline_comment|/* Driver descriptor structure, in block 0 */
DECL|struct|mac_driver_desc
r_struct
id|mac_driver_desc
(brace
DECL|member|signature
id|__u16
id|signature
suffix:semicolon
multiline_comment|/* expected to be MAC_DRIVER_MAGIC */
DECL|member|block_size
id|__u16
id|block_size
suffix:semicolon
DECL|member|block_count
id|__u32
id|block_count
suffix:semicolon
multiline_comment|/* ... more stuff */
)brace
suffix:semicolon
r_int
id|mac_partition
c_func
(paren
r_struct
id|gendisk
op_star
id|hd
comma
id|kdev_t
id|dev
comma
r_int
r_int
id|fsec
comma
r_int
id|first_part_minor
)paren
suffix:semicolon
eof
