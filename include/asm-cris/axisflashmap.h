macro_line|#ifndef __ASM_AXISFLASHMAP_H
DECL|macro|__ASM_AXISFLASHMAP_H
mdefine_line|#define __ASM_AXISFLASHMAP_H
multiline_comment|/* Bootblock parameters are stored at 0xc000 and has the FLASH_BOOT_MAGIC &n; * as start, it ends with 0xFFFFFFFF */
DECL|macro|FLASH_BOOT_MAGIC
mdefine_line|#define FLASH_BOOT_MAGIC 0xbeefcace
DECL|macro|BOOTPARAM_OFFSET
mdefine_line|#define BOOTPARAM_OFFSET 0xc000
multiline_comment|/* apps/bootblocktool is used to read and write the parameters,&n; * and it has nothing to do with the partition table. &n; */
multiline_comment|/* the partitiontable consists of some &quot;jump over&quot; code, a head and&n; * then the actual entries.&n; * tools/mkptable is used to generate the ptable. &n; */
multiline_comment|/* The partition table starts with code to &quot;jump over&quot; it: */
DECL|macro|PARTITIONTABLE_CODE_START
mdefine_line|#define PARTITIONTABLE_CODE_START { &bslash;&n; 0x0f, 0x05, /* nop 0 */&bslash;&n; 0x25, 0xf0, /* di  2 */&bslash;&n; 0xed, 0xff  /* ba  4 */ }
multiline_comment|/* The actual offset depend on the number of entries */
DECL|macro|PARTITIONTABLE_CODE_END
mdefine_line|#define PARTITIONTABLE_CODE_END { &bslash;&n; 0x00, 0x00, /* ba offset 6 */&bslash;&n; 0x0f, 0x05  /* nop 8 */}
DECL|macro|PARTITION_TABLE_OFFSET
mdefine_line|#define PARTITION_TABLE_OFFSET 10
DECL|macro|PARTITION_TABLE_MAGIC
mdefine_line|#define PARTITION_TABLE_MAGIC 0xbeef /* Not a good magic */
multiline_comment|/* The partitiontable_head is located at offset +10: */
DECL|struct|partitiontable_head
r_struct
id|partitiontable_head
(brace
DECL|member|magic
id|__u16
id|magic
suffix:semicolon
multiline_comment|/* PARTITION_TABLE_MAGIC */
DECL|member|size
id|__u16
id|size
suffix:semicolon
multiline_comment|/* Length of ptable block (not header) */
DECL|member|checksum
id|__u32
id|checksum
suffix:semicolon
multiline_comment|/* simple longword sum */
)brace
suffix:semicolon
multiline_comment|/* And followed by partition table entries */
DECL|struct|partitiontable_entry
r_struct
id|partitiontable_entry
(brace
DECL|member|offset
id|__u32
id|offset
suffix:semicolon
multiline_comment|/* Offset is relative to the sector the ptable is in */
DECL|member|size
id|__u32
id|size
suffix:semicolon
DECL|member|checksum
id|__u32
id|checksum
suffix:semicolon
multiline_comment|/* simple longword sum */
DECL|member|type
id|__u16
id|type
suffix:semicolon
DECL|member|flags
id|__u16
id|flags
suffix:semicolon
multiline_comment|/* bit 0: ro/rw = 1/0 */
DECL|member|future0
id|__u32
id|future0
suffix:semicolon
multiline_comment|/* 16 bytes reserved for future use */
DECL|member|future1
id|__u32
id|future1
suffix:semicolon
DECL|member|future2
id|__u32
id|future2
suffix:semicolon
DECL|member|future3
id|__u32
id|future3
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* ended by an end marker: */
DECL|macro|PARTITIONTABLE_END_MARKER
mdefine_line|#define PARTITIONTABLE_END_MARKER 0xFFFFFFFF
DECL|macro|PARTITIONTABLE_END_MARKER_SIZE
mdefine_line|#define PARTITIONTABLE_END_MARKER_SIZE 4
multiline_comment|/*#define PARTITION_TYPE_RESCUE 0x0000?*/
multiline_comment|/* Not used, maybe it should? */
DECL|macro|PARTITION_TYPE_PARAM
mdefine_line|#define PARTITION_TYPE_PARAM  0x0001 /* Hmm.. */
DECL|macro|PARTITION_TYPE_KERNEL
mdefine_line|#define PARTITION_TYPE_KERNEL 0x0002
DECL|macro|PARTITION_TYPE_JFFS
mdefine_line|#define PARTITION_TYPE_JFFS   0x0003
macro_line|#endif
eof
