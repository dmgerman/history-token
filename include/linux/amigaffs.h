macro_line|#ifndef AMIGAFFS_H
DECL|macro|AMIGAFFS_H
mdefine_line|#define AMIGAFFS_H
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;linux/types.h&gt;
multiline_comment|/* AmigaOS allows file names with up to 30 characters length.&n; * Names longer than that will be silently truncated. If you&n; * want to disallow this, comment out the following #define.&n; * Creating filesystem objects with longer names will then&n; * result in an error (ENAMETOOLONG).&n; */
multiline_comment|/*#define AFFS_NO_TRUNCATE */
multiline_comment|/* Ugly macros make the code more pretty. */
DECL|macro|GET_END_PTR
mdefine_line|#define GET_END_PTR(st,p,sz)&t;&t; ((st *)((char *)(p)+((sz)-sizeof(st))))
DECL|macro|AFFS_GET_HASHENTRY
mdefine_line|#define AFFS_GET_HASHENTRY(data,hashkey) be32_to_cpu(((struct dir_front *)data)-&gt;hashtable[hashkey])
DECL|macro|AFFS_BLOCK
mdefine_line|#define AFFS_BLOCK(data,ino,blk)&t; ((struct file_front *)data)-&gt;blocks[AFFS_I2HSIZE(ino)-1-(blk)]
DECL|macro|FILE_END
mdefine_line|#define FILE_END(p,i)&t;GET_END_PTR(struct file_end,p,AFFS_I2BSIZE(i))
DECL|macro|ROOT_END
mdefine_line|#define ROOT_END(p,i)&t;GET_END_PTR(struct root_end,p,AFFS_I2BSIZE(i))
DECL|macro|DIR_END
mdefine_line|#define DIR_END(p,i)&t;GET_END_PTR(struct dir_end,p,AFFS_I2BSIZE(i))
DECL|macro|LINK_END
mdefine_line|#define LINK_END(p,i)&t;GET_END_PTR(struct hlink_end,p,AFFS_I2BSIZE(i))
DECL|macro|ROOT_END_S
mdefine_line|#define ROOT_END_S(p,s)&t;GET_END_PTR(struct root_end,p,(s)-&gt;s_blocksize)
DECL|macro|DATA_FRONT
mdefine_line|#define DATA_FRONT(bh)&t;((struct data_front *)(bh)-&gt;b_data)
DECL|macro|DIR_FRONT
mdefine_line|#define DIR_FRONT(bh)&t;((struct dir_front *)(bh)-&gt;b_data)
multiline_comment|/* Only for easier debugging if need be */
DECL|macro|affs_bread
mdefine_line|#define affs_bread&t;bread
DECL|macro|affs_brelse
mdefine_line|#define affs_brelse&t;brelse
macro_line|#ifdef __LITTLE_ENDIAN
DECL|macro|BO_EXBITS
mdefine_line|#define BO_EXBITS&t;0x18UL
macro_line|#elif defined(__BIG_ENDIAN)
DECL|macro|BO_EXBITS
mdefine_line|#define BO_EXBITS&t;0x00UL
macro_line|#else
macro_line|#error Endianness must be known for affs to work.
macro_line|#endif
DECL|macro|FS_OFS
mdefine_line|#define FS_OFS&t;&t;0x444F5300
DECL|macro|FS_FFS
mdefine_line|#define FS_FFS&t;&t;0x444F5301
DECL|macro|FS_INTLOFS
mdefine_line|#define FS_INTLOFS&t;0x444F5302
DECL|macro|FS_INTLFFS
mdefine_line|#define FS_INTLFFS&t;0x444F5303
DECL|macro|FS_DCOFS
mdefine_line|#define FS_DCOFS&t;0x444F5304
DECL|macro|FS_DCFFS
mdefine_line|#define FS_DCFFS&t;0x444F5305
DECL|macro|MUFS_FS
mdefine_line|#define MUFS_FS&t;&t;0x6d754653   /* &squot;muFS&squot; */
DECL|macro|MUFS_OFS
mdefine_line|#define MUFS_OFS&t;0x6d754600   /* &squot;muF&bslash;0&squot; */
DECL|macro|MUFS_FFS
mdefine_line|#define MUFS_FFS&t;0x6d754601   /* &squot;muF&bslash;1&squot; */
DECL|macro|MUFS_INTLOFS
mdefine_line|#define MUFS_INTLOFS&t;0x6d754602   /* &squot;muF&bslash;2&squot; */
DECL|macro|MUFS_INTLFFS
mdefine_line|#define MUFS_INTLFFS&t;0x6d754603   /* &squot;muF&bslash;3&squot; */
DECL|macro|MUFS_DCOFS
mdefine_line|#define MUFS_DCOFS&t;0x6d754604   /* &squot;muF&bslash;4&squot; */
DECL|macro|MUFS_DCFFS
mdefine_line|#define MUFS_DCFFS&t;0x6d754605   /* &squot;muF&bslash;5&squot; */
DECL|macro|T_SHORT
mdefine_line|#define T_SHORT&t;&t;2
DECL|macro|T_LIST
mdefine_line|#define T_LIST&t;&t;16
DECL|macro|T_DATA
mdefine_line|#define T_DATA&t;&t;8
DECL|macro|ST_LINKFILE
mdefine_line|#define ST_LINKFILE&t;-4
DECL|macro|ST_FILE
mdefine_line|#define ST_FILE&t;&t;-3
DECL|macro|ST_ROOT
mdefine_line|#define ST_ROOT&t;&t;1
DECL|macro|ST_USERDIR
mdefine_line|#define ST_USERDIR&t;2
DECL|macro|ST_SOFTLINK
mdefine_line|#define ST_SOFTLINK&t;3
DECL|macro|ST_LINKDIR
mdefine_line|#define ST_LINKDIR&t;4
DECL|struct|root_front
r_struct
id|root_front
(brace
DECL|member|primary_type
id|s32
id|primary_type
suffix:semicolon
DECL|member|spare1
id|s32
id|spare1
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|hash_size
id|s32
id|hash_size
suffix:semicolon
DECL|member|spare2
id|s32
id|spare2
suffix:semicolon
DECL|member|checksum
id|u32
id|checksum
suffix:semicolon
DECL|member|hashtable
id|s32
id|hashtable
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|root_end
r_struct
id|root_end
(brace
DECL|member|bm_flag
id|s32
id|bm_flag
suffix:semicolon
DECL|member|bm_keys
id|s32
id|bm_keys
(braket
l_int|25
)braket
suffix:semicolon
DECL|member|bm_extend
id|s32
id|bm_extend
suffix:semicolon
DECL|member|dir_altered
r_struct
id|DateStamp
id|dir_altered
suffix:semicolon
DECL|member|disk_name
id|u8
id|disk_name
(braket
l_int|40
)braket
suffix:semicolon
DECL|member|disk_altered
r_struct
id|DateStamp
id|disk_altered
suffix:semicolon
DECL|member|disk_made
r_struct
id|DateStamp
id|disk_made
suffix:semicolon
DECL|member|spare1
id|s32
id|spare1
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|secondary_type
id|s32
id|secondary_type
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|dir_front
r_struct
id|dir_front
(brace
DECL|member|primary_type
id|s32
id|primary_type
suffix:semicolon
DECL|member|own_key
id|s32
id|own_key
suffix:semicolon
DECL|member|spare1
id|s32
id|spare1
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|checksum
id|u32
id|checksum
suffix:semicolon
DECL|member|hashtable
id|s32
id|hashtable
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|dir_end
r_struct
id|dir_end
(brace
DECL|member|spare1
id|s32
id|spare1
suffix:semicolon
DECL|member|owner_uid
id|s16
id|owner_uid
suffix:semicolon
DECL|member|owner_gid
id|s16
id|owner_gid
suffix:semicolon
DECL|member|protect
id|u32
id|protect
suffix:semicolon
DECL|member|spare2
id|s32
id|spare2
suffix:semicolon
DECL|member|comment
id|u8
id|comment
(braket
l_int|92
)braket
suffix:semicolon
DECL|member|created
r_struct
id|DateStamp
id|created
suffix:semicolon
DECL|member|dir_name
id|u8
id|dir_name
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|spare3
id|s32
id|spare3
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|link_chain
id|s32
id|link_chain
suffix:semicolon
DECL|member|spare4
id|s32
id|spare4
(braket
l_int|5
)braket
suffix:semicolon
DECL|member|hash_chain
id|s32
id|hash_chain
suffix:semicolon
DECL|member|parent
id|s32
id|parent
suffix:semicolon
DECL|member|spare5
id|s32
id|spare5
suffix:semicolon
DECL|member|secondary_type
id|s32
id|secondary_type
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|file_front
r_struct
id|file_front
(brace
DECL|member|primary_type
id|s32
id|primary_type
suffix:semicolon
DECL|member|own_key
id|s32
id|own_key
suffix:semicolon
DECL|member|block_count
id|s32
id|block_count
suffix:semicolon
DECL|member|unknown1
id|s32
id|unknown1
suffix:semicolon
DECL|member|first_data
id|s32
id|first_data
suffix:semicolon
DECL|member|checksum
id|u32
id|checksum
suffix:semicolon
DECL|member|blocks
id|s32
id|blocks
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|file_end
r_struct
id|file_end
(brace
DECL|member|spare1
id|s32
id|spare1
suffix:semicolon
DECL|member|owner_uid
id|s16
id|owner_uid
suffix:semicolon
DECL|member|owner_gid
id|s16
id|owner_gid
suffix:semicolon
DECL|member|protect
id|u32
id|protect
suffix:semicolon
DECL|member|byte_size
id|s32
id|byte_size
suffix:semicolon
DECL|member|comment
id|u8
id|comment
(braket
l_int|92
)braket
suffix:semicolon
DECL|member|created
r_struct
id|DateStamp
id|created
suffix:semicolon
DECL|member|file_name
id|u8
id|file_name
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|spare2
id|s32
id|spare2
suffix:semicolon
DECL|member|original
id|s32
id|original
suffix:semicolon
multiline_comment|/* not really in file_end */
DECL|member|link_chain
id|s32
id|link_chain
suffix:semicolon
DECL|member|spare3
id|s32
id|spare3
(braket
l_int|5
)braket
suffix:semicolon
DECL|member|hash_chain
id|s32
id|hash_chain
suffix:semicolon
DECL|member|parent
id|s32
id|parent
suffix:semicolon
DECL|member|extension
id|s32
id|extension
suffix:semicolon
DECL|member|secondary_type
id|s32
id|secondary_type
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|hlink_front
r_struct
id|hlink_front
(brace
DECL|member|primary_type
id|s32
id|primary_type
suffix:semicolon
DECL|member|own_key
id|s32
id|own_key
suffix:semicolon
DECL|member|spare1
id|s32
id|spare1
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|checksum
id|u32
id|checksum
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|hlink_end
r_struct
id|hlink_end
(brace
DECL|member|spare1
id|s32
id|spare1
suffix:semicolon
DECL|member|owner_uid
id|s16
id|owner_uid
suffix:semicolon
DECL|member|owner_gid
id|s16
id|owner_gid
suffix:semicolon
DECL|member|protect
id|u32
id|protect
suffix:semicolon
DECL|member|comment
id|u8
id|comment
(braket
l_int|92
)braket
suffix:semicolon
DECL|member|created
r_struct
id|DateStamp
id|created
suffix:semicolon
DECL|member|link_name
id|u8
id|link_name
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|spare2
id|s32
id|spare2
suffix:semicolon
DECL|member|original
id|s32
id|original
suffix:semicolon
DECL|member|link_chain
id|s32
id|link_chain
suffix:semicolon
DECL|member|spare3
id|s32
id|spare3
(braket
l_int|5
)braket
suffix:semicolon
DECL|member|hash_chain
id|s32
id|hash_chain
suffix:semicolon
DECL|member|parent
id|s32
id|parent
suffix:semicolon
DECL|member|spare4
id|s32
id|spare4
suffix:semicolon
DECL|member|secondary_type
id|s32
id|secondary_type
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|slink_front
r_struct
id|slink_front
(brace
DECL|member|primary_type
id|s32
id|primary_type
suffix:semicolon
DECL|member|own_key
id|s32
id|own_key
suffix:semicolon
DECL|member|spare1
id|s32
id|spare1
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|checksum
id|s32
id|checksum
suffix:semicolon
DECL|member|symname
id|u8
id|symname
(braket
l_int|288
)braket
suffix:semicolon
multiline_comment|/* depends on block size */
)brace
suffix:semicolon
DECL|struct|data_front
r_struct
id|data_front
(brace
DECL|member|primary_type
id|s32
id|primary_type
suffix:semicolon
DECL|member|header_key
id|s32
id|header_key
suffix:semicolon
DECL|member|sequence_number
id|s32
id|sequence_number
suffix:semicolon
DECL|member|data_size
id|s32
id|data_size
suffix:semicolon
DECL|member|next_data
id|s32
id|next_data
suffix:semicolon
DECL|member|checksum
id|s32
id|checksum
suffix:semicolon
DECL|member|data
id|u8
id|data
(braket
l_int|488
)braket
suffix:semicolon
multiline_comment|/* depends on block size */
)brace
suffix:semicolon
multiline_comment|/* Permission bits */
DECL|macro|FIBF_OTR_READ
mdefine_line|#define FIBF_OTR_READ&t;&t;0x8000
DECL|macro|FIBF_OTR_WRITE
mdefine_line|#define FIBF_OTR_WRITE&t;&t;0x4000
DECL|macro|FIBF_OTR_EXECUTE
mdefine_line|#define FIBF_OTR_EXECUTE&t;0x2000
DECL|macro|FIBF_OTR_DELETE
mdefine_line|#define FIBF_OTR_DELETE&t;&t;0x1000
DECL|macro|FIBF_GRP_READ
mdefine_line|#define FIBF_GRP_READ&t;&t;0x0800
DECL|macro|FIBF_GRP_WRITE
mdefine_line|#define FIBF_GRP_WRITE&t;&t;0x0400
DECL|macro|FIBF_GRP_EXECUTE
mdefine_line|#define FIBF_GRP_EXECUTE&t;0x0200
DECL|macro|FIBF_GRP_DELETE
mdefine_line|#define FIBF_GRP_DELETE&t;&t;0x0100
DECL|macro|FIBF_SCRIPT
mdefine_line|#define FIBF_SCRIPT&t;&t;0x0040
DECL|macro|FIBF_PURE
mdefine_line|#define FIBF_PURE&t;&t;0x0020&t;&t;/* no use under linux */
DECL|macro|FIBF_ARCHIVE
mdefine_line|#define FIBF_ARCHIVE&t;&t;0x0010&t;&t;/* never set, always cleared on write */
DECL|macro|FIBF_READ
mdefine_line|#define FIBF_READ&t;&t;0x0008&t;&t;/* 0 means allowed */
DECL|macro|FIBF_WRITE
mdefine_line|#define FIBF_WRITE&t;&t;0x0004&t;&t;/* 0 means allowed */
DECL|macro|FIBF_EXECUTE
mdefine_line|#define FIBF_EXECUTE&t;&t;0x0002&t;&t;/* 0 means allowed, ignored under linux */
DECL|macro|FIBF_DELETE
mdefine_line|#define FIBF_DELETE&t;&t;0x0001&t;&t;/* 0 means allowed */
DECL|macro|FIBF_OWNER
mdefine_line|#define FIBF_OWNER&t;&t;0x000F&t;&t;/* Bits pertaining to owner */
DECL|macro|AFFS_UMAYWRITE
mdefine_line|#define AFFS_UMAYWRITE(prot)&t;(((prot) &amp; (FIBF_WRITE|FIBF_DELETE)) == (FIBF_WRITE|FIBF_DELETE))
DECL|macro|AFFS_UMAYREAD
mdefine_line|#define AFFS_UMAYREAD(prot)&t;((prot) &amp; FIBF_READ)
DECL|macro|AFFS_UMAYEXECUTE
mdefine_line|#define AFFS_UMAYEXECUTE(prot)&t;((prot) &amp; FIBF_EXECUTE)
DECL|macro|AFFS_GMAYWRITE
mdefine_line|#define AFFS_GMAYWRITE(prot)&t;(((prot)&amp;(FIBF_GRP_WRITE|FIBF_GRP_DELETE))==&bslash;&n;&t;&t;&t;&t;&t;&t;&t;(FIBF_GRP_WRITE|FIBF_GRP_DELETE))
DECL|macro|AFFS_GMAYREAD
mdefine_line|#define AFFS_GMAYREAD(prot)&t;((prot) &amp; FIBF_GRP_READ)
DECL|macro|AFFS_GMAYEXECUTE
mdefine_line|#define AFFS_GMAYEXECUTE(prot)&t;((prot) &amp; FIBF_EXECUTE)
DECL|macro|AFFS_OMAYWRITE
mdefine_line|#define AFFS_OMAYWRITE(prot)&t;(((prot)&amp;(FIBF_OTR_WRITE|FIBF_OTR_DELETE))==&bslash;&n;&t;&t;&t;&t;&t;&t;&t;(FIBF_OTR_WRITE|FIBF_OTR_DELETE))
DECL|macro|AFFS_OMAYREAD
mdefine_line|#define AFFS_OMAYREAD(prot)&t;((prot) &amp; FIBF_OTR_READ)
DECL|macro|AFFS_OMAYEXECUTE
mdefine_line|#define AFFS_OMAYEXECUTE(prot)&t;((prot) &amp; FIBF_EXECUTE)
macro_line|#endif
eof
