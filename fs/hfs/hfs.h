multiline_comment|/* &n; * linux/fs/hfs/hfs.h&n; *&n; * Copyright (C) 1995-1997  Paul H. Hargrove&n; * This file may be distributed under the terms of the GNU General Public License.&n; *&n; * &quot;XXX&quot; in a comment is a note to myself to consider changing something.&n; */
macro_line|#ifndef _HFS_H
DECL|macro|_HFS_H
mdefine_line|#define _HFS_H
macro_line|#include &lt;linux/hfs_sysdep.h&gt;
DECL|macro|HFS_NEW
mdefine_line|#define HFS_NEW(X)&t;((X) = hfs_malloc(sizeof(*(X))))
DECL|macro|HFS_DELETE
mdefine_line|#define HFS_DELETE(X)&t;do { hfs_free((X), sizeof(*(X))); (X) = NULL; } &bslash;&n;                        while (0)
multiline_comment|/* offsets to various blocks */
DECL|macro|HFS_DD_BLK
mdefine_line|#define HFS_DD_BLK&t;&t;0 /* Driver Descriptor block */
DECL|macro|HFS_PMAP_BLK
mdefine_line|#define HFS_PMAP_BLK&t;&t;1 /* First block of partition map */
DECL|macro|HFS_MDB_BLK
mdefine_line|#define HFS_MDB_BLK&t;&t;2 /* Block (w/i partition) of MDB */
multiline_comment|/* magic numbers for various disk blocks */
DECL|macro|HFS_DRVR_DESC_MAGIC
mdefine_line|#define HFS_DRVR_DESC_MAGIC&t;0x4552 /* &quot;ER&quot;: driver descriptor map */
DECL|macro|HFS_OLD_PMAP_MAGIC
mdefine_line|#define HFS_OLD_PMAP_MAGIC&t;0x5453 /* &quot;TS&quot;: old-type partition map */
DECL|macro|HFS_NEW_PMAP_MAGIC
mdefine_line|#define HFS_NEW_PMAP_MAGIC&t;0x504D /* &quot;PM&quot;: new-type partition map */
DECL|macro|HFS_SUPER_MAGIC
mdefine_line|#define HFS_SUPER_MAGIC&t;&t;0x4244 /* &quot;BD&quot;: HFS MDB (super block) */
DECL|macro|HFS_MFS_SUPER_MAGIC
mdefine_line|#define HFS_MFS_SUPER_MAGIC&t;0xD2D7 /* MFS MDB (super block) */
multiline_comment|/* magic numbers for various internal structures */
DECL|macro|HFS_FILE_MAGIC
mdefine_line|#define HFS_FILE_MAGIC&t;&t;0x4801
DECL|macro|HFS_DIR_MAGIC
mdefine_line|#define HFS_DIR_MAGIC&t;&t;0x4802
DECL|macro|HFS_MDB_MAGIC
mdefine_line|#define HFS_MDB_MAGIC&t;&t;0x4803
DECL|macro|HFS_EXT_MAGIC
mdefine_line|#define HFS_EXT_MAGIC&t;&t;0x4804 /* XXX currently unused */
DECL|macro|HFS_BREC_MAGIC
mdefine_line|#define HFS_BREC_MAGIC&t;&t;0x4811 /* XXX currently unused */
DECL|macro|HFS_BTREE_MAGIC
mdefine_line|#define HFS_BTREE_MAGIC&t;&t;0x4812
DECL|macro|HFS_BNODE_MAGIC
mdefine_line|#define HFS_BNODE_MAGIC&t;&t;0x4813
multiline_comment|/* various FIXED size parameters */
DECL|macro|HFS_SECTOR_SIZE
mdefine_line|#define HFS_SECTOR_SIZE&t;&t;512    /* size of an HFS sector */
DECL|macro|HFS_SECTOR_SIZE_BITS
mdefine_line|#define HFS_SECTOR_SIZE_BITS&t;9      /* log_2(HFS_SECTOR_SIZE) */
DECL|macro|HFS_NAMELEN
mdefine_line|#define HFS_NAMELEN&t;&t;31     /* maximum length of an HFS filename */
DECL|macro|HFS_NAMEMAX
mdefine_line|#define HFS_NAMEMAX&t;&t;(3*31) /* max size of ENCODED filename */
DECL|macro|HFS_BM_MAXBLOCKS
mdefine_line|#define HFS_BM_MAXBLOCKS&t;(16)   /* max number of bitmap blocks */
DECL|macro|HFS_BM_BPB
mdefine_line|#define HFS_BM_BPB (8*HFS_SECTOR_SIZE) /* number of bits per bitmap block */
DECL|macro|HFS_MAX_VALENCE
mdefine_line|#define HFS_MAX_VALENCE&t;&t;32767U
DECL|macro|HFS_FORK_MAX
mdefine_line|#define HFS_FORK_MAX&t;&t;(0x7FFFFFFF)
multiline_comment|/* Meanings of the drAtrb field of the MDB,&n; * Reference: _Inside Macintosh: Files_ p. 2-61&n; */
DECL|macro|HFS_SB_ATTRIB_HLOCK
mdefine_line|#define HFS_SB_ATTRIB_HLOCK 0x0080
DECL|macro|HFS_SB_ATTRIB_CLEAN
mdefine_line|#define HFS_SB_ATTRIB_CLEAN 0x0100
DECL|macro|HFS_SB_ATTRIB_SPARED
mdefine_line|#define HFS_SB_ATTRIB_SPARED 0x0200
DECL|macro|HFS_SB_ATTRIB_SLOCK
mdefine_line|#define HFS_SB_ATTRIB_SLOCK 0x8000
multiline_comment|/* 2**16 - 1 */
DECL|macro|HFS_USHRT_MAX
mdefine_line|#define HFS_USHRT_MAX&t;65535
multiline_comment|/* Some special File ID numbers */
DECL|macro|HFS_POR_CNID
mdefine_line|#define HFS_POR_CNID&t;1&t;/* Parent Of the Root */
DECL|macro|HFS_ROOT_CNID
mdefine_line|#define HFS_ROOT_CNID&t;2&t;/* ROOT directory */
DECL|macro|HFS_EXT_CNID
mdefine_line|#define HFS_EXT_CNID&t;3&t;/* EXTents B-tree */
DECL|macro|HFS_CAT_CNID
mdefine_line|#define HFS_CAT_CNID&t;4&t;/* CATalog B-tree */
DECL|macro|HFS_BAD_CNID
mdefine_line|#define HFS_BAD_CNID&t;5&t;/* BAD blocks file */
DECL|macro|HFS_ALLOC_CNID
mdefine_line|#define HFS_ALLOC_CNID  6       /* ALLOCation file (HFS+) */
DECL|macro|HFS_START_CNID
mdefine_line|#define HFS_START_CNID  7       /* STARTup file (HFS+) */
DECL|macro|HFS_ATTR_CNID
mdefine_line|#define HFS_ATTR_CNID   8       /* ATTRibutes file (HFS+) */
DECL|macro|HFS_EXCH_CNID
mdefine_line|#define HFS_EXCH_CNID  15       /* ExchangeFiles temp id */
multiline_comment|/* values for hfs_cat_rec.cdrType */
DECL|macro|HFS_CDR_DIR
mdefine_line|#define HFS_CDR_DIR    0x01    /* folder (directory) */
DECL|macro|HFS_CDR_FIL
mdefine_line|#define HFS_CDR_FIL    0x02    /* file */
DECL|macro|HFS_CDR_THD
mdefine_line|#define HFS_CDR_THD    0x03    /* folder (directory) thread */
DECL|macro|HFS_CDR_FTH
mdefine_line|#define HFS_CDR_FTH    0x04    /* file thread */
multiline_comment|/* legal values for hfs_ext_key.FkType and hfs_file.fork */
DECL|macro|HFS_FK_DATA
mdefine_line|#define HFS_FK_DATA&t;0x00
DECL|macro|HFS_FK_RSRC
mdefine_line|#define HFS_FK_RSRC&t;0xFF
multiline_comment|/* bits in hfs_fil_entry.Flags */
DECL|macro|HFS_FIL_LOCK
mdefine_line|#define HFS_FIL_LOCK&t;0x01  /* locked */
DECL|macro|HFS_FIL_THD
mdefine_line|#define HFS_FIL_THD&t;0x02  /* file thread */
DECL|macro|HFS_FIL_DOPEN
mdefine_line|#define HFS_FIL_DOPEN   0x04  /* data fork open */
DECL|macro|HFS_FIL_ROPEN
mdefine_line|#define HFS_FIL_ROPEN   0x08  /* resource fork open */
DECL|macro|HFS_FIL_DIR
mdefine_line|#define HFS_FIL_DIR     0x10  /* directory (always clear) */
DECL|macro|HFS_FIL_RSRV1
mdefine_line|#define HFS_FIL_RSRV1   0x20  /* reserved */
DECL|macro|HFS_FIL_NOCOPY
mdefine_line|#define HFS_FIL_NOCOPY  0x40  /* copy-protected file */
DECL|macro|HFS_FIL_USED
mdefine_line|#define HFS_FIL_USED&t;0x80  /* open */
multiline_comment|/* bits in hfs_dir_entry.Flags. dirflags is 16 bits. */
DECL|macro|HFS_DIR_LOCK
mdefine_line|#define HFS_DIR_LOCK        0x01  /* locked */
DECL|macro|HFS_DIR_THD
mdefine_line|#define HFS_DIR_THD         0x02  /* directory thread */
DECL|macro|HFS_DIR_INEXPFOLDER
mdefine_line|#define HFS_DIR_INEXPFOLDER 0x04  /* in a shared area */
DECL|macro|HFS_DIR_MOUNTED
mdefine_line|#define HFS_DIR_MOUNTED     0x08  /* mounted */
DECL|macro|HFS_DIR_DIR
mdefine_line|#define HFS_DIR_DIR         0x10  /* directory (always set) */
DECL|macro|HFS_DIR_EXPFOLDER
mdefine_line|#define HFS_DIR_EXPFOLDER   0x20  /* share point */
DECL|macro|HFS_DIR_RSRV1
mdefine_line|#define HFS_DIR_RSRV1       0x40  /* reserved */
DECL|macro|HFS_DIR_RSRV2
mdefine_line|#define HFS_DIR_RSRV2       0x80  /* reserved */
multiline_comment|/* Access types used when requesting access to a B-node */
DECL|macro|HFS_LOCK_NONE
mdefine_line|#define HFS_LOCK_NONE&t;0x0000&t;/* Illegal */
DECL|macro|HFS_LOCK_READ
mdefine_line|#define HFS_LOCK_READ&t;0x0001&t;/* read-only access */
DECL|macro|HFS_LOCK_RESRV
mdefine_line|#define HFS_LOCK_RESRV&t;0x0002&t;/* might potentially modify */
DECL|macro|HFS_LOCK_WRITE
mdefine_line|#define HFS_LOCK_WRITE&t;0x0003&t;/* will modify now (exclusive access) */
DECL|macro|HFS_LOCK_MASK
mdefine_line|#define HFS_LOCK_MASK&t;0x000f
multiline_comment|/* Flags field of the hfs_path_elem */
DECL|macro|HFS_BPATH_FIRST
mdefine_line|#define HFS_BPATH_FIRST&t;&t;0x0100
DECL|macro|HFS_BPATH_OVERFLOW
mdefine_line|#define HFS_BPATH_OVERFLOW&t;0x0200
DECL|macro|HFS_BPATH_UNDERFLOW
mdefine_line|#define HFS_BPATH_UNDERFLOW&t;0x0400
DECL|macro|HFS_BPATH_MASK
mdefine_line|#define HFS_BPATH_MASK&t;&t;0x0f00
multiline_comment|/* Flags for hfs_bfind() */
DECL|macro|HFS_BFIND_EXACT
mdefine_line|#define HFS_BFIND_EXACT&t;&t;0x0010
DECL|macro|HFS_BFIND_LOCK
mdefine_line|#define HFS_BFIND_LOCK&t;&t;0x0020
multiline_comment|/* Modes for hfs_bfind() */
DECL|macro|HFS_BFIND_WRITE
mdefine_line|#define HFS_BFIND_WRITE   (HFS_LOCK_RESRV|HFS_BFIND_EXACT|HFS_BFIND_LOCK)
DECL|macro|HFS_BFIND_READ_EQ
mdefine_line|#define HFS_BFIND_READ_EQ (HFS_LOCK_READ|HFS_BFIND_EXACT)
DECL|macro|HFS_BFIND_READ_LE
mdefine_line|#define HFS_BFIND_READ_LE (HFS_LOCK_READ)
DECL|macro|HFS_BFIND_INSERT
mdefine_line|#define HFS_BFIND_INSERT  (HFS_LOCK_RESRV|HFS_BPATH_FIRST|HFS_BPATH_OVERFLOW)
DECL|macro|HFS_BFIND_DELETE
mdefine_line|#define HFS_BFIND_DELETE &bslash;&n;&t; (HFS_LOCK_RESRV|HFS_BFIND_EXACT|HFS_BPATH_FIRST|HFS_BPATH_UNDERFLOW)
multiline_comment|/*======== HFS structures as they appear on the disk ========*/
multiline_comment|/* Pascal-style string of up to 31 characters */
DECL|struct|hfs_name
r_struct
id|hfs_name
(brace
DECL|member|Len
id|hfs_byte_t
id|Len
suffix:semicolon
DECL|member|Name
id|hfs_byte_t
id|Name
(braket
l_int|31
)braket
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|v
id|hfs_word_t
id|v
suffix:semicolon
DECL|member|h
id|hfs_word_t
id|h
suffix:semicolon
DECL|typedef|hfs_point_t
)brace
id|hfs_point_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|top
id|hfs_word_t
id|top
suffix:semicolon
DECL|member|left
id|hfs_word_t
id|left
suffix:semicolon
DECL|member|bottom
id|hfs_word_t
id|bottom
suffix:semicolon
DECL|member|right
id|hfs_word_t
id|right
suffix:semicolon
DECL|typedef|hfs_rect_t
)brace
id|hfs_rect_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|fdType
id|hfs_lword_t
id|fdType
suffix:semicolon
DECL|member|fdCreator
id|hfs_lword_t
id|fdCreator
suffix:semicolon
DECL|member|fdFlags
id|hfs_word_t
id|fdFlags
suffix:semicolon
DECL|member|fdLocation
id|hfs_point_t
id|fdLocation
suffix:semicolon
DECL|member|fdFldr
id|hfs_word_t
id|fdFldr
suffix:semicolon
DECL|typedef|hfs_finfo_t
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
id|hfs_finfo_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|fdIconID
id|hfs_word_t
id|fdIconID
suffix:semicolon
DECL|member|fdUnused
id|hfs_byte_t
id|fdUnused
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|fdComment
id|hfs_word_t
id|fdComment
suffix:semicolon
DECL|member|fdPutAway
id|hfs_lword_t
id|fdPutAway
suffix:semicolon
DECL|typedef|hfs_fxinfo_t
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
id|hfs_fxinfo_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|frRect
id|hfs_rect_t
id|frRect
suffix:semicolon
DECL|member|frFlags
id|hfs_word_t
id|frFlags
suffix:semicolon
DECL|member|frLocation
id|hfs_point_t
id|frLocation
suffix:semicolon
DECL|member|frView
id|hfs_word_t
id|frView
suffix:semicolon
DECL|typedef|hfs_dinfo_t
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
id|hfs_dinfo_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|frScroll
id|hfs_point_t
id|frScroll
suffix:semicolon
DECL|member|frOpenChain
id|hfs_lword_t
id|frOpenChain
suffix:semicolon
DECL|member|frUnused
id|hfs_word_t
id|frUnused
suffix:semicolon
DECL|member|frComment
id|hfs_word_t
id|frComment
suffix:semicolon
DECL|member|frPutAway
id|hfs_lword_t
id|frPutAway
suffix:semicolon
DECL|typedef|hfs_dxinfo_t
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
id|hfs_dxinfo_t
suffix:semicolon
DECL|union|hfs_finder_info
r_union
id|hfs_finder_info
(brace
r_struct
(brace
DECL|member|finfo
id|hfs_finfo_t
id|finfo
suffix:semicolon
DECL|member|fxinfo
id|hfs_fxinfo_t
id|fxinfo
suffix:semicolon
DECL|member|file
)brace
id|file
suffix:semicolon
r_struct
(brace
DECL|member|dinfo
id|hfs_dinfo_t
id|dinfo
suffix:semicolon
DECL|member|dxinfo
id|hfs_dxinfo_t
id|dxinfo
suffix:semicolon
DECL|member|dir
)brace
id|dir
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* A btree record key on disk */
DECL|struct|hfs_bkey
r_struct
id|hfs_bkey
(brace
DECL|member|KeyLen
id|hfs_byte_t
id|KeyLen
suffix:semicolon
multiline_comment|/* number of bytes in the key */
DECL|member|value
id|hfs_byte_t
id|value
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* (KeyLen) bytes of key */
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* Cast to a pointer to a generic bkey */
DECL|macro|HFS_BKEY
mdefine_line|#define&t;HFS_BKEY(X)&t;(((void)((X)-&gt;KeyLen)), ((struct hfs_bkey *)(X)))
multiline_comment|/* The key used in the catalog b-tree: */
DECL|struct|hfs_cat_key
r_struct
id|hfs_cat_key
(brace
DECL|member|KeyLen
id|hfs_byte_t
id|KeyLen
suffix:semicolon
multiline_comment|/* number of bytes in the key */
DECL|member|Resrv1
id|hfs_byte_t
id|Resrv1
suffix:semicolon
multiline_comment|/* padding */
DECL|member|ParID
id|hfs_lword_t
id|ParID
suffix:semicolon
multiline_comment|/* CNID of the parent dir */
DECL|member|CName
r_struct
id|hfs_name
id|CName
suffix:semicolon
multiline_comment|/* The filename of the entry */
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* The key used in the extents b-tree: */
DECL|struct|hfs_ext_key
r_struct
id|hfs_ext_key
(brace
DECL|member|KeyLen
id|hfs_byte_t
id|KeyLen
suffix:semicolon
multiline_comment|/* number of bytes in the key */
DECL|member|FkType
id|hfs_byte_t
id|FkType
suffix:semicolon
multiline_comment|/* HFS_FK_{DATA,RSRC} */
DECL|member|FNum
id|hfs_lword_t
id|FNum
suffix:semicolon
multiline_comment|/* The File ID of the file */
DECL|member|FABN
id|hfs_word_t
id|FABN
suffix:semicolon
multiline_comment|/* allocation blocks number*/
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/*======== Data structures kept in memory ========*/
multiline_comment|/*&n; * struct hfs_mdb&n; *&n; * The fields from the MDB of an HFS filesystem&n; */
DECL|struct|hfs_mdb
r_struct
id|hfs_mdb
(brace
DECL|member|magic
r_int
id|magic
suffix:semicolon
multiline_comment|/* A magic number */
DECL|member|vname
r_int
r_char
id|vname
(braket
l_int|28
)braket
suffix:semicolon
multiline_comment|/* The volume name */
DECL|member|sys_mdb
id|hfs_sysmdb
id|sys_mdb
suffix:semicolon
multiline_comment|/* superblock */
DECL|member|buf
id|hfs_buffer
id|buf
suffix:semicolon
multiline_comment|/* The hfs_buffer&n;&t;&t;&t;&t;&t;&t;   holding the real&n;&t;&t;&t;&t;&t;&t;   superblock (aka VIB&n;&t;&t;&t;&t;&t;&t;   or MDB) */
DECL|member|alt_buf
id|hfs_buffer
id|alt_buf
suffix:semicolon
multiline_comment|/* The hfs_buffer holding&n;&t;&t;&t;&t;&t;&t;   the alternate superblock */
DECL|member|bitmap
id|hfs_buffer
id|bitmap
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* The hfs_buffer holding the&n;&t;&t;&t;&t;&t;&t;   allocation bitmap */
DECL|member|ext_tree
r_struct
id|hfs_btree
op_star
id|ext_tree
suffix:semicolon
multiline_comment|/* Information about&n;&t;&t;&t;&t;&t;&t;   the extents b-tree */
DECL|member|cat_tree
r_struct
id|hfs_btree
op_star
id|cat_tree
suffix:semicolon
multiline_comment|/* Information about&n;&t;&t;&t;&t;&t;&t;   the catalog b-tree */
DECL|member|file_count
id|hfs_u32
id|file_count
suffix:semicolon
multiline_comment|/* The number of&n;&t;&t;&t;&t;&t;&t;   regular files in&n;&t;&t;&t;&t;&t;&t;   the filesystem */
DECL|member|dir_count
id|hfs_u32
id|dir_count
suffix:semicolon
multiline_comment|/* The number of&n;&t;&t;&t;&t;&t;&t;   directories in the&n;&t;&t;&t;&t;&t;&t;   filesystem */
DECL|member|next_id
id|hfs_u32
id|next_id
suffix:semicolon
multiline_comment|/* The next available&n;&t;&t;&t;&t;&t;&t;   file id number */
DECL|member|clumpablks
id|hfs_u32
id|clumpablks
suffix:semicolon
multiline_comment|/* The number of allocation&n;&t;&t;&t;&t;&t;&t;   blocks to try to add when&n;&t;&t;&t;&t;&t;&t;   extending a file */
DECL|member|write_count
id|hfs_u32
id|write_count
suffix:semicolon
multiline_comment|/* The number of MDB&n;&t;&t;&t;&t;&t;&t;   writes (a sort of&n;&t;&t;&t;&t;&t;&t;   version number) */
DECL|member|fs_start
id|hfs_u32
id|fs_start
suffix:semicolon
multiline_comment|/* The first 512-byte&n;&t;&t;&t;&t;&t;&t;   block represented&n;&t;&t;&t;&t;&t;&t;   in the bitmap */
DECL|member|create_date
id|hfs_u32
id|create_date
suffix:semicolon
multiline_comment|/* In network byte-order */
DECL|member|modify_date
id|hfs_u32
id|modify_date
suffix:semicolon
multiline_comment|/* In network byte-order */
DECL|member|backup_date
id|hfs_u32
id|backup_date
suffix:semicolon
multiline_comment|/* In network byte-order */
DECL|member|root_files
id|hfs_u16
id|root_files
suffix:semicolon
multiline_comment|/* The number of&n;&t;&t;&t;&t;&t;&t;   regular&n;&t;&t;&t;&t;&t;&t;   (non-directory)&n;&t;&t;&t;&t;&t;&t;   files in the root&n;&t;&t;&t;&t;&t;&t;   directory */
DECL|member|root_dirs
id|hfs_u16
id|root_dirs
suffix:semicolon
multiline_comment|/* The number of&n;&t;&t;&t;&t;&t;&t;   directories in the&n;&t;&t;&t;&t;&t;&t;   root directory */
DECL|member|fs_ablocks
id|hfs_u16
id|fs_ablocks
suffix:semicolon
multiline_comment|/* The number of&n;&t;&t;&t;&t;&t;&t;   allocation blocks&n;&t;&t;&t;&t;&t;&t;   in the filesystem */
DECL|member|free_ablocks
id|hfs_u16
id|free_ablocks
suffix:semicolon
multiline_comment|/* The number of unused&n;&t;&t;&t;&t;&t;&t;   allocation blocks&n;&t;&t;&t;&t;&t;&t;   in the filesystem */
DECL|member|alloc_blksz
id|hfs_u32
id|alloc_blksz
suffix:semicolon
multiline_comment|/* The number of&n;&t;&t;&t;&t;&t;&t;   512-byte blocks per&n;&t;&t;&t;&t;&t;&t;   &quot;allocation block&quot; */
DECL|member|attrib
id|hfs_u16
id|attrib
suffix:semicolon
multiline_comment|/* Attribute word */
DECL|member|bitmap_sem
r_struct
id|semaphore
id|bitmap_sem
suffix:semicolon
DECL|member|entry_dirty
r_struct
id|list_head
id|entry_dirty
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * struct hfs_extent&n; *&n; * The offset to allocation block mapping for a given file is&n; * contained in a series of these structures.  Each (struct&n; * hfs_extent) records up to three runs of contiguous allocation&n; * blocks.  An allocation block is a contiguous group of physical&n; * blocks.&n; */
DECL|struct|hfs_extent
r_struct
id|hfs_extent
(brace
DECL|member|magic
r_int
id|magic
suffix:semicolon
multiline_comment|/* A magic number */
DECL|member|start
r_int
r_int
id|start
suffix:semicolon
multiline_comment|/* Where in the file this record&n;&t;&t;&t;&t;&t; begins (in allocation blocks) */
DECL|member|end
r_int
r_int
id|end
suffix:semicolon
multiline_comment|/* Where in the file this record&n;&t;&t;&t;&t;&t; ends (in allocation blocks) */
DECL|member|block
r_int
r_int
id|block
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* The allocation block on disk which&n;&t;&t;&t;&t;&t; begins this extent */
DECL|member|length
r_int
r_int
id|length
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* The number of allocation blocks&n;&t;&t;&t;&t;&t; in this extent */
DECL|member|next
r_struct
id|hfs_extent
op_star
id|next
suffix:semicolon
multiline_comment|/* Next extent record for this file */
DECL|member|prev
r_struct
id|hfs_extent
op_star
id|prev
suffix:semicolon
multiline_comment|/* Previous extent record for this file */
DECL|member|count
r_int
id|count
suffix:semicolon
multiline_comment|/* Number of times it is used */
)brace
suffix:semicolon
multiline_comment|/*&n; * struct hfs_dir &n; *&n; * This structure holds information specific&n; * to a directory in an HFS filesystem.&n; */
DECL|struct|hfs_dir
r_struct
id|hfs_dir
(brace
DECL|member|magic
r_int
id|magic
suffix:semicolon
multiline_comment|/* A magic number */
DECL|member|flags
id|hfs_u16
id|flags
suffix:semicolon
DECL|member|dirs
id|hfs_u16
id|dirs
suffix:semicolon
multiline_comment|/* Number of directories in this one */
DECL|member|files
id|hfs_u16
id|files
suffix:semicolon
multiline_comment|/* Number of files in this directory */
DECL|member|readers
r_int
id|readers
suffix:semicolon
DECL|member|read_wait
id|hfs_wait_queue
id|read_wait
suffix:semicolon
DECL|member|writers
r_int
id|writers
suffix:semicolon
DECL|member|write_wait
id|hfs_wait_queue
id|write_wait
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * struct hfs_fork&n; *&n; * This structure holds the information&n; * specific to a single fork of a file.&n; */
DECL|struct|hfs_fork
r_struct
id|hfs_fork
(brace
DECL|member|entry
r_struct
id|hfs_cat_entry
op_star
id|entry
suffix:semicolon
multiline_comment|/* The file this fork is part of */
DECL|member|first
r_struct
id|hfs_extent
id|first
suffix:semicolon
multiline_comment|/* The first extent record for&n;&t;&t;&t;&t;&t;&t; this fork */
DECL|member|cache
r_struct
id|hfs_extent
op_star
id|cache
suffix:semicolon
multiline_comment|/* The most-recently accessed&n;&t;&t;&t;&t;&t;&t; extent record for this fork */
DECL|member|lsize
id|hfs_u32
id|lsize
suffix:semicolon
multiline_comment|/* The logical size in bytes */
DECL|member|psize
id|hfs_u32
id|psize
suffix:semicolon
multiline_comment|/* The phys size (512-byte blocks) */
DECL|member|fork
id|hfs_u8
id|fork
suffix:semicolon
multiline_comment|/* Which fork is this? */
)brace
suffix:semicolon
multiline_comment|/*&n; * struct hfs_file &n; *&n; * This structure holds information specific&n; * to a file in an HFS filesystem.&n; */
DECL|struct|hfs_file
r_struct
id|hfs_file
(brace
DECL|member|magic
r_int
id|magic
suffix:semicolon
DECL|member|data_fork
r_struct
id|hfs_fork
id|data_fork
suffix:semicolon
DECL|member|rsrc_fork
r_struct
id|hfs_fork
id|rsrc_fork
suffix:semicolon
DECL|member|clumpablks
id|hfs_u16
id|clumpablks
suffix:semicolon
DECL|member|flags
id|hfs_u8
id|flags
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * struct hfs_file &n; *&n; * This structure holds information about a&n; * file or directory in an HFS filesystem.&n; *&n; * &squot;wait&squot; must remain 1st and &squot;hash&squot; 2nd since we do some pointer arithmetic.&n; */
DECL|struct|hfs_cat_entry
r_struct
id|hfs_cat_entry
(brace
DECL|member|wait
id|hfs_wait_queue
id|wait
suffix:semicolon
DECL|member|hash
r_struct
id|list_head
id|hash
suffix:semicolon
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|mdb
r_struct
id|hfs_mdb
op_star
id|mdb
suffix:semicolon
DECL|member|sys_entry
id|hfs_sysentry
id|sys_entry
suffix:semicolon
DECL|member|key
r_struct
id|hfs_cat_key
id|key
suffix:semicolon
DECL|member|info
r_union
id|hfs_finder_info
id|info
suffix:semicolon
DECL|member|cnid
id|hfs_u32
id|cnid
suffix:semicolon
multiline_comment|/* In network byte-order */
DECL|member|create_date
id|hfs_u32
id|create_date
suffix:semicolon
multiline_comment|/* In network byte-order */
DECL|member|modify_date
id|hfs_u32
id|modify_date
suffix:semicolon
multiline_comment|/* In network byte-order */
DECL|member|backup_date
id|hfs_u32
id|backup_date
suffix:semicolon
multiline_comment|/* In network byte-order */
DECL|member|count
r_int
r_int
id|count
suffix:semicolon
DECL|member|state
r_int
r_int
id|state
suffix:semicolon
DECL|member|type
id|hfs_u8
id|type
suffix:semicolon
r_union
(brace
DECL|member|dir
r_struct
id|hfs_dir
id|dir
suffix:semicolon
DECL|member|file
r_struct
id|hfs_file
id|file
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* hfs entry state bits */
DECL|macro|HFS_DIRTY
mdefine_line|#define HFS_DIRTY        1
DECL|macro|HFS_KEYDIRTY
mdefine_line|#define HFS_KEYDIRTY     2
DECL|macro|HFS_LOCK
mdefine_line|#define HFS_LOCK         4
DECL|macro|HFS_DELETED
mdefine_line|#define HFS_DELETED      8
multiline_comment|/* &n; * struct hfs_bnode_ref&n; *&n; * A pointer to a (struct hfs_bnode) and the type of lock held on it.&n; */
DECL|struct|hfs_bnode_ref
r_struct
id|hfs_bnode_ref
(brace
DECL|member|bn
r_struct
id|hfs_bnode
op_star
id|bn
suffix:semicolon
DECL|member|lock_type
r_int
id|lock_type
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * struct hfs_belem&n; *&n; * An element of the path from the root of a B-tree to a leaf.&n; * Includes the reference to a (struct hfs_bnode), the index of&n; * the appropriate record in that node, and some flags.&n; */
DECL|struct|hfs_belem
r_struct
id|hfs_belem
(brace
DECL|member|bnr
r_struct
id|hfs_bnode_ref
id|bnr
suffix:semicolon
DECL|member|record
r_int
id|record
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * struct hfs_brec&n; *&n; * The structure returned by hfs_bfind() to describe the requested record.&n; */
DECL|struct|hfs_brec
r_struct
id|hfs_brec
(brace
DECL|member|keep_flags
r_int
id|keep_flags
suffix:semicolon
DECL|member|tree
r_struct
id|hfs_btree
op_star
id|tree
suffix:semicolon
DECL|member|top
r_struct
id|hfs_belem
op_star
id|top
suffix:semicolon
DECL|member|bottom
r_struct
id|hfs_belem
op_star
id|bottom
suffix:semicolon
DECL|member|elem
r_struct
id|hfs_belem
id|elem
(braket
l_int|9
)braket
suffix:semicolon
DECL|member|key
r_struct
id|hfs_bkey
op_star
id|key
suffix:semicolon
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
multiline_comment|/* The actual data */
)brace
suffix:semicolon
multiline_comment|/*================ Function prototypes ================*/
multiline_comment|/* bdelete.c */
r_extern
r_int
id|hfs_bdelete
c_func
(paren
r_struct
id|hfs_btree
op_star
comma
r_const
r_struct
id|hfs_bkey
op_star
)paren
suffix:semicolon
multiline_comment|/* bfind.c */
r_extern
r_void
id|hfs_brec_relse
c_func
(paren
r_struct
id|hfs_brec
op_star
comma
r_struct
id|hfs_belem
op_star
)paren
suffix:semicolon
r_extern
r_int
id|hfs_bsucc
c_func
(paren
r_struct
id|hfs_brec
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|hfs_bfind
c_func
(paren
r_struct
id|hfs_brec
op_star
comma
r_struct
id|hfs_btree
op_star
comma
r_const
r_struct
id|hfs_bkey
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* binsert.c */
r_extern
r_int
id|hfs_binsert
c_func
(paren
r_struct
id|hfs_btree
op_star
comma
r_const
r_struct
id|hfs_bkey
op_star
comma
r_const
r_void
op_star
comma
id|hfs_u16
)paren
suffix:semicolon
multiline_comment|/* bitmap.c */
r_extern
id|hfs_u16
id|hfs_vbm_count_free
c_func
(paren
r_const
r_struct
id|hfs_mdb
op_star
comma
id|hfs_u16
)paren
suffix:semicolon
r_extern
id|hfs_u16
id|hfs_vbm_search_free
c_func
(paren
r_const
r_struct
id|hfs_mdb
op_star
comma
id|hfs_u16
op_star
)paren
suffix:semicolon
r_extern
r_int
id|hfs_set_vbm_bits
c_func
(paren
r_struct
id|hfs_mdb
op_star
comma
id|hfs_u16
comma
id|hfs_u16
)paren
suffix:semicolon
r_extern
r_int
id|hfs_clear_vbm_bits
c_func
(paren
r_struct
id|hfs_mdb
op_star
comma
id|hfs_u16
comma
id|hfs_u16
)paren
suffix:semicolon
multiline_comment|/* bitops.c */
r_extern
id|hfs_u32
id|hfs_find_zero_bit
c_func
(paren
r_const
id|hfs_u32
op_star
comma
id|hfs_u32
comma
id|hfs_u32
)paren
suffix:semicolon
r_extern
id|hfs_u32
id|hfs_count_zero_bits
c_func
(paren
r_const
id|hfs_u32
op_star
comma
id|hfs_u32
comma
id|hfs_u32
)paren
suffix:semicolon
multiline_comment|/* btree.c */
r_extern
r_struct
id|hfs_btree
op_star
id|hfs_btree_init
c_func
(paren
r_struct
id|hfs_mdb
op_star
comma
id|ino_t
comma
id|hfs_byte_t
op_star
comma
id|hfs_u32
comma
id|hfs_u32
)paren
suffix:semicolon
r_extern
r_void
id|hfs_btree_free
c_func
(paren
r_struct
id|hfs_btree
op_star
)paren
suffix:semicolon
r_extern
r_void
id|hfs_btree_commit
c_func
(paren
r_struct
id|hfs_btree
op_star
comma
id|hfs_byte_t
op_star
comma
id|hfs_lword_t
)paren
suffix:semicolon
multiline_comment|/* catalog.c */
r_extern
r_void
id|hfs_cat_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|hfs_cat_put
c_func
(paren
r_struct
id|hfs_cat_entry
op_star
)paren
suffix:semicolon
r_extern
r_void
id|hfs_cat_mark_dirty
c_func
(paren
r_struct
id|hfs_cat_entry
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|hfs_cat_entry
op_star
id|hfs_cat_get
c_func
(paren
r_struct
id|hfs_mdb
op_star
comma
r_const
r_struct
id|hfs_cat_key
op_star
)paren
suffix:semicolon
r_extern
r_void
id|hfs_cat_invalidate
c_func
(paren
r_struct
id|hfs_mdb
op_star
)paren
suffix:semicolon
r_extern
r_void
id|hfs_cat_commit
c_func
(paren
r_struct
id|hfs_mdb
op_star
)paren
suffix:semicolon
r_extern
r_void
id|hfs_cat_free
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|hfs_cat_compare
c_func
(paren
r_const
r_struct
id|hfs_cat_key
op_star
comma
r_const
r_struct
id|hfs_cat_key
op_star
)paren
suffix:semicolon
r_extern
r_void
id|hfs_cat_build_key
c_func
(paren
id|hfs_u32
comma
r_const
r_struct
id|hfs_name
op_star
comma
r_struct
id|hfs_cat_key
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|hfs_cat_entry
op_star
id|hfs_cat_parent
c_func
(paren
r_struct
id|hfs_cat_entry
op_star
)paren
suffix:semicolon
r_extern
r_int
id|hfs_cat_open
c_func
(paren
r_struct
id|hfs_cat_entry
op_star
comma
r_struct
id|hfs_brec
op_star
)paren
suffix:semicolon
r_extern
r_int
id|hfs_cat_next
c_func
(paren
r_struct
id|hfs_cat_entry
op_star
comma
r_struct
id|hfs_brec
op_star
comma
id|hfs_u16
comma
id|hfs_u32
op_star
comma
id|hfs_u8
op_star
)paren
suffix:semicolon
r_extern
r_void
id|hfs_cat_close
c_func
(paren
r_struct
id|hfs_cat_entry
op_star
comma
r_struct
id|hfs_brec
op_star
)paren
suffix:semicolon
r_extern
r_int
id|hfs_cat_create
c_func
(paren
r_struct
id|hfs_cat_entry
op_star
comma
r_struct
id|hfs_cat_key
op_star
comma
id|hfs_u8
comma
id|hfs_u32
comma
id|hfs_u32
comma
r_struct
id|hfs_cat_entry
op_star
op_star
)paren
suffix:semicolon
r_extern
r_int
id|hfs_cat_mkdir
c_func
(paren
r_struct
id|hfs_cat_entry
op_star
comma
r_struct
id|hfs_cat_key
op_star
comma
r_struct
id|hfs_cat_entry
op_star
op_star
)paren
suffix:semicolon
r_extern
r_int
id|hfs_cat_delete
c_func
(paren
r_struct
id|hfs_cat_entry
op_star
comma
r_struct
id|hfs_cat_entry
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|hfs_cat_move
c_func
(paren
r_struct
id|hfs_cat_entry
op_star
comma
r_struct
id|hfs_cat_entry
op_star
comma
r_struct
id|hfs_cat_entry
op_star
comma
r_struct
id|hfs_cat_key
op_star
comma
r_struct
id|hfs_cat_entry
op_star
op_star
)paren
suffix:semicolon
multiline_comment|/* extent.c */
r_extern
r_int
id|hfs_ext_compare
c_func
(paren
r_const
r_struct
id|hfs_ext_key
op_star
comma
r_const
r_struct
id|hfs_ext_key
op_star
)paren
suffix:semicolon
r_extern
r_void
id|hfs_extent_in
c_func
(paren
r_struct
id|hfs_fork
op_star
comma
r_const
id|hfs_byte_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|hfs_extent_out
c_func
(paren
r_const
r_struct
id|hfs_fork
op_star
comma
id|hfs_byte_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|hfs_extent_map
c_func
(paren
r_struct
id|hfs_fork
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|hfs_extent_adj
c_func
(paren
r_struct
id|hfs_fork
op_star
)paren
suffix:semicolon
r_extern
r_void
id|hfs_extent_free
c_func
(paren
r_struct
id|hfs_fork
op_star
)paren
suffix:semicolon
multiline_comment|/* file.c */
r_extern
r_int
id|hfs_get_block
c_func
(paren
r_struct
id|inode
op_star
comma
id|sector_t
comma
r_struct
id|buffer_head
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* mdb.c */
r_extern
r_struct
id|hfs_mdb
op_star
id|hfs_mdb_get
c_func
(paren
id|hfs_sysmdb
comma
r_int
comma
id|hfs_s32
)paren
suffix:semicolon
r_extern
r_void
id|hfs_mdb_commit
c_func
(paren
r_struct
id|hfs_mdb
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|hfs_mdb_put
c_func
(paren
r_struct
id|hfs_mdb
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* part_tbl.c */
r_extern
r_int
id|hfs_part_find
c_func
(paren
id|hfs_sysmdb
comma
r_int
comma
r_int
comma
id|hfs_s32
op_star
comma
id|hfs_s32
op_star
)paren
suffix:semicolon
multiline_comment|/* string.c */
r_extern
r_int
r_int
id|hfs_strhash
c_func
(paren
r_const
r_int
r_char
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
id|hfs_strcmp
c_func
(paren
r_const
r_int
r_char
op_star
comma
r_int
r_int
comma
r_const
r_int
r_char
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
id|hfs_streq
c_func
(paren
r_const
r_int
r_char
op_star
comma
r_int
r_int
comma
r_const
r_int
r_char
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|hfs_tolower
c_func
(paren
r_int
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_static
id|__inline__
r_struct
id|dentry
DECL|function|hfs_lookup_dentry
op_star
id|hfs_lookup_dentry
c_func
(paren
r_struct
id|dentry
op_star
id|base
comma
r_const
r_char
op_star
id|name
comma
r_const
r_int
id|len
)paren
(brace
r_struct
id|qstr
id|this
suffix:semicolon
id|this.name
op_assign
id|name
suffix:semicolon
id|this.len
op_assign
id|len
suffix:semicolon
id|this.hash
op_assign
id|hfs_strhash
c_func
(paren
id|name
comma
id|len
)paren
suffix:semicolon
r_return
id|d_lookup
c_func
(paren
id|base
comma
op_amp
id|this
)paren
suffix:semicolon
)brace
multiline_comment|/* drop a dentry for one of the special directories.&n; * it&squot;s in the form of base/name/dentry. */
DECL|function|hfs_drop_special
r_static
id|__inline__
r_void
id|hfs_drop_special
c_func
(paren
r_struct
id|dentry
op_star
id|base
comma
r_const
r_struct
id|hfs_name
op_star
id|name
comma
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
r_struct
id|dentry
op_star
id|dparent
comma
op_star
id|de
suffix:semicolon
id|dparent
op_assign
id|hfs_lookup_dentry
c_func
(paren
id|base
comma
id|name-&gt;Name
comma
id|name-&gt;Len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dparent
)paren
(brace
id|de
op_assign
id|hfs_lookup_dentry
c_func
(paren
id|dparent
comma
id|dentry-&gt;d_name.name
comma
id|dentry-&gt;d_name.len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|de
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|de-&gt;d_inode
)paren
id|d_drop
c_func
(paren
id|de
)paren
suffix:semicolon
id|dput
c_func
(paren
id|de
)paren
suffix:semicolon
)brace
id|dput
c_func
(paren
id|dparent
)paren
suffix:semicolon
)brace
)brace
r_extern
r_struct
id|dentry_operations
id|hfs_dentry_operations
suffix:semicolon
macro_line|#endif
eof
