macro_line|#ifndef __LINUX_ROMFS_FS_H
DECL|macro|__LINUX_ROMFS_FS_H
mdefine_line|#define __LINUX_ROMFS_FS_H
multiline_comment|/* The basic structures of the romfs filesystem */
DECL|macro|ROMBSIZE
mdefine_line|#define ROMBSIZE BLOCK_SIZE
DECL|macro|ROMBSBITS
mdefine_line|#define ROMBSBITS BLOCK_SIZE_BITS
DECL|macro|ROMBMASK
mdefine_line|#define ROMBMASK (ROMBSIZE-1)
DECL|macro|ROMFS_MAGIC
mdefine_line|#define ROMFS_MAGIC 0x7275
DECL|macro|ROMFS_MAXFN
mdefine_line|#define ROMFS_MAXFN 128
DECL|macro|__mkw
mdefine_line|#define __mkw(h,l) (((h)&amp;0x00ff)&lt;&lt; 8|((l)&amp;0x00ff))
DECL|macro|__mkl
mdefine_line|#define __mkl(h,l) (((h)&amp;0xffff)&lt;&lt;16|((l)&amp;0xffff))
DECL|macro|__mk4
mdefine_line|#define __mk4(a,b,c,d) htonl(__mkl(__mkw(a,b),__mkw(c,d)))
DECL|macro|ROMSB_WORD0
mdefine_line|#define ROMSB_WORD0 __mk4(&squot;-&squot;,&squot;r&squot;,&squot;o&squot;,&squot;m&squot;)
DECL|macro|ROMSB_WORD1
mdefine_line|#define ROMSB_WORD1 __mk4(&squot;1&squot;,&squot;f&squot;,&squot;s&squot;,&squot;-&squot;)
multiline_comment|/* On-disk &quot;super block&quot; */
DECL|struct|romfs_super_block
r_struct
id|romfs_super_block
(brace
DECL|member|word0
id|__u32
id|word0
suffix:semicolon
DECL|member|word1
id|__u32
id|word1
suffix:semicolon
DECL|member|size
id|__u32
id|size
suffix:semicolon
DECL|member|checksum
id|__u32
id|checksum
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* volume name */
)brace
suffix:semicolon
multiline_comment|/* On disk inode */
DECL|struct|romfs_inode
r_struct
id|romfs_inode
(brace
DECL|member|next
id|__u32
id|next
suffix:semicolon
multiline_comment|/* low 4 bits see ROMFH_ */
DECL|member|spec
id|__u32
id|spec
suffix:semicolon
DECL|member|size
id|__u32
id|size
suffix:semicolon
DECL|member|checksum
id|__u32
id|checksum
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|ROMFH_TYPE
mdefine_line|#define ROMFH_TYPE 7
DECL|macro|ROMFH_HRD
mdefine_line|#define ROMFH_HRD 0
DECL|macro|ROMFH_DIR
mdefine_line|#define ROMFH_DIR 1
DECL|macro|ROMFH_REG
mdefine_line|#define ROMFH_REG 2
DECL|macro|ROMFH_SYM
mdefine_line|#define ROMFH_SYM 3
DECL|macro|ROMFH_BLK
mdefine_line|#define ROMFH_BLK 4
DECL|macro|ROMFH_CHR
mdefine_line|#define ROMFH_CHR 5
DECL|macro|ROMFH_SCK
mdefine_line|#define ROMFH_SCK 6
DECL|macro|ROMFH_FIF
mdefine_line|#define ROMFH_FIF 7
DECL|macro|ROMFH_EXEC
mdefine_line|#define ROMFH_EXEC 8
multiline_comment|/* Alignment */
DECL|macro|ROMFH_SIZE
mdefine_line|#define ROMFH_SIZE 16
DECL|macro|ROMFH_PAD
mdefine_line|#define ROMFH_PAD (ROMFH_SIZE-1)
DECL|macro|ROMFH_MASK
mdefine_line|#define ROMFH_MASK (~ROMFH_PAD)
macro_line|#ifdef __KERNEL__
multiline_comment|/* Not much now */
macro_line|#endif /* __KERNEL__ */
macro_line|#endif
eof
