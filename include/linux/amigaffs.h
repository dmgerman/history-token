macro_line|#ifndef AMIGAFFS_H
DECL|macro|AMIGAFFS_H
mdefine_line|#define AMIGAFFS_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
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
DECL|macro|AFFS_ROOT_BMAPS
mdefine_line|#define AFFS_ROOT_BMAPS&t;&t;25
DECL|struct|affs_date
r_struct
id|affs_date
(brace
DECL|member|days
id|__be32
id|days
suffix:semicolon
DECL|member|mins
id|__be32
id|mins
suffix:semicolon
DECL|member|ticks
id|__be32
id|ticks
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|affs_short_date
r_struct
id|affs_short_date
(brace
DECL|member|days
id|__be16
id|days
suffix:semicolon
DECL|member|mins
id|__be16
id|mins
suffix:semicolon
DECL|member|ticks
id|__be16
id|ticks
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|affs_root_head
r_struct
id|affs_root_head
(brace
DECL|member|ptype
id|__be32
id|ptype
suffix:semicolon
DECL|member|spare1
id|__be32
id|spare1
suffix:semicolon
DECL|member|spare2
id|__be32
id|spare2
suffix:semicolon
DECL|member|hash_size
id|__be32
id|hash_size
suffix:semicolon
DECL|member|spare3
id|__be32
id|spare3
suffix:semicolon
DECL|member|checksum
id|__be32
id|checksum
suffix:semicolon
DECL|member|hashtable
id|__be32
id|hashtable
(braket
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|affs_root_tail
r_struct
id|affs_root_tail
(brace
DECL|member|bm_flag
id|__be32
id|bm_flag
suffix:semicolon
DECL|member|bm_blk
id|__be32
id|bm_blk
(braket
id|AFFS_ROOT_BMAPS
)braket
suffix:semicolon
DECL|member|bm_ext
id|__be32
id|bm_ext
suffix:semicolon
DECL|member|root_change
r_struct
id|affs_date
id|root_change
suffix:semicolon
DECL|member|disk_name
id|u8
id|disk_name
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|spare1
id|__be32
id|spare1
suffix:semicolon
DECL|member|spare2
id|__be32
id|spare2
suffix:semicolon
DECL|member|disk_change
r_struct
id|affs_date
id|disk_change
suffix:semicolon
DECL|member|disk_create
r_struct
id|affs_date
id|disk_create
suffix:semicolon
DECL|member|spare3
id|__be32
id|spare3
suffix:semicolon
DECL|member|spare4
id|__be32
id|spare4
suffix:semicolon
DECL|member|dcache
id|__be32
id|dcache
suffix:semicolon
DECL|member|stype
id|__be32
id|stype
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|affs_head
r_struct
id|affs_head
(brace
DECL|member|ptype
id|__be32
id|ptype
suffix:semicolon
DECL|member|key
id|__be32
id|key
suffix:semicolon
DECL|member|block_count
id|__be32
id|block_count
suffix:semicolon
DECL|member|spare1
id|__be32
id|spare1
suffix:semicolon
DECL|member|first_data
id|__be32
id|first_data
suffix:semicolon
DECL|member|checksum
id|__be32
id|checksum
suffix:semicolon
DECL|member|table
id|__be32
id|table
(braket
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|affs_tail
r_struct
id|affs_tail
(brace
DECL|member|spare1
id|__be32
id|spare1
suffix:semicolon
DECL|member|uid
id|__be16
id|uid
suffix:semicolon
DECL|member|gid
id|__be16
id|gid
suffix:semicolon
DECL|member|protect
id|__be32
id|protect
suffix:semicolon
DECL|member|size
id|__be32
id|size
suffix:semicolon
DECL|member|comment
id|u8
id|comment
(braket
l_int|92
)braket
suffix:semicolon
DECL|member|change
r_struct
id|affs_date
id|change
suffix:semicolon
DECL|member|name
id|u8
id|name
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|spare2
id|__be32
id|spare2
suffix:semicolon
DECL|member|original
id|__be32
id|original
suffix:semicolon
DECL|member|link_chain
id|__be32
id|link_chain
suffix:semicolon
DECL|member|spare
id|__be32
id|spare
(braket
l_int|5
)braket
suffix:semicolon
DECL|member|hash_chain
id|__be32
id|hash_chain
suffix:semicolon
DECL|member|parent
id|__be32
id|parent
suffix:semicolon
DECL|member|extension
id|__be32
id|extension
suffix:semicolon
DECL|member|stype
id|__be32
id|stype
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|slink_front
r_struct
id|slink_front
(brace
DECL|member|ptype
id|__be32
id|ptype
suffix:semicolon
DECL|member|key
id|__be32
id|key
suffix:semicolon
DECL|member|spare1
id|__be32
id|spare1
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|checksum
id|__be32
id|checksum
suffix:semicolon
DECL|member|symname
id|u8
id|symname
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* depends on block size */
)brace
suffix:semicolon
DECL|struct|affs_data_head
r_struct
id|affs_data_head
(brace
DECL|member|ptype
id|__be32
id|ptype
suffix:semicolon
DECL|member|key
id|__be32
id|key
suffix:semicolon
DECL|member|sequence
id|__be32
id|sequence
suffix:semicolon
DECL|member|size
id|__be32
id|size
suffix:semicolon
DECL|member|next
id|__be32
id|next
suffix:semicolon
DECL|member|checksum
id|__be32
id|checksum
suffix:semicolon
DECL|member|data
id|u8
id|data
(braket
l_int|1
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
DECL|macro|FIBF_HIDDEN
mdefine_line|#define FIBF_HIDDEN&t;&t;0x0080
DECL|macro|FIBF_SCRIPT
mdefine_line|#define FIBF_SCRIPT&t;&t;0x0040
DECL|macro|FIBF_PURE
mdefine_line|#define FIBF_PURE&t;&t;0x0020&t;&t;/* no use under linux */
DECL|macro|FIBF_ARCHIVED
mdefine_line|#define FIBF_ARCHIVED&t;&t;0x0010&t;&t;/* never set, always cleared on write */
DECL|macro|FIBF_NOREAD
mdefine_line|#define FIBF_NOREAD&t;&t;0x0008&t;&t;/* 0 means allowed */
DECL|macro|FIBF_NOWRITE
mdefine_line|#define FIBF_NOWRITE&t;&t;0x0004&t;&t;/* 0 means allowed */
DECL|macro|FIBF_NOEXECUTE
mdefine_line|#define FIBF_NOEXECUTE&t;&t;0x0002&t;&t;/* 0 means allowed, ignored under linux */
DECL|macro|FIBF_NODELETE
mdefine_line|#define FIBF_NODELETE&t;&t;0x0001&t;&t;/* 0 means allowed */
DECL|macro|FIBF_OWNER
mdefine_line|#define FIBF_OWNER&t;&t;0x000F&t;&t;/* Bits pertaining to owner */
DECL|macro|FIBF_MASK
mdefine_line|#define FIBF_MASK&t;&t;0xEE0E&t;&t;/* Bits modified by Linux */
macro_line|#endif
eof
