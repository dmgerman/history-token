multiline_comment|/*&n; *  linux/fs/hfs/hfs.h&n; *&n; * Copyright (C) 1995-1997  Paul H. Hargrove&n; * (C) 2003 Ardis Technologies &lt;roman@ardistech.com&gt;&n; * This file may be distributed under the terms of the GNU General Public License.&n; */
macro_line|#ifndef _HFS_H
DECL|macro|_HFS_H
mdefine_line|#define _HFS_H
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
multiline_comment|/* various FIXED size parameters */
DECL|macro|HFS_SECTOR_SIZE
mdefine_line|#define HFS_SECTOR_SIZE&t;&t;512    /* size of an HFS sector */
DECL|macro|HFS_SECTOR_SIZE_BITS
mdefine_line|#define HFS_SECTOR_SIZE_BITS&t;9      /* log_2(HFS_SECTOR_SIZE) */
DECL|macro|HFS_NAMELEN
mdefine_line|#define HFS_NAMELEN&t;&t;31     /* maximum length of an HFS filename */
DECL|macro|HFS_MAX_VALENCE
mdefine_line|#define HFS_MAX_VALENCE&t;&t;32767U
multiline_comment|/* Meanings of the drAtrb field of the MDB,&n; * Reference: _Inside Macintosh: Files_ p. 2-61&n; */
DECL|macro|HFS_SB_ATTRIB_HLOCK
mdefine_line|#define HFS_SB_ATTRIB_HLOCK&t;(1 &lt;&lt; 7)
DECL|macro|HFS_SB_ATTRIB_UNMNT
mdefine_line|#define HFS_SB_ATTRIB_UNMNT&t;(1 &lt;&lt; 8)
DECL|macro|HFS_SB_ATTRIB_SPARED
mdefine_line|#define HFS_SB_ATTRIB_SPARED&t;(1 &lt;&lt; 9)
DECL|macro|HFS_SB_ATTRIB_INCNSTNT
mdefine_line|#define HFS_SB_ATTRIB_INCNSTNT&t;(1 &lt;&lt; 11)
DECL|macro|HFS_SB_ATTRIB_SLOCK
mdefine_line|#define HFS_SB_ATTRIB_SLOCK&t;(1 &lt;&lt; 15)
multiline_comment|/* Some special File ID numbers */
DECL|macro|HFS_POR_CNID
mdefine_line|#define HFS_POR_CNID&t;&t;1&t;/* Parent Of the Root */
DECL|macro|HFS_ROOT_CNID
mdefine_line|#define HFS_ROOT_CNID&t;&t;2&t;/* ROOT directory */
DECL|macro|HFS_EXT_CNID
mdefine_line|#define HFS_EXT_CNID&t;&t;3&t;/* EXTents B-tree */
DECL|macro|HFS_CAT_CNID
mdefine_line|#define HFS_CAT_CNID&t;&t;4&t;/* CATalog B-tree */
DECL|macro|HFS_BAD_CNID
mdefine_line|#define HFS_BAD_CNID&t;&t;5&t;/* BAD blocks file */
DECL|macro|HFS_ALLOC_CNID
mdefine_line|#define HFS_ALLOC_CNID&t;&t;6&t;/* ALLOCation file (HFS+) */
DECL|macro|HFS_START_CNID
mdefine_line|#define HFS_START_CNID&t;&t;7&t;/* STARTup file (HFS+) */
DECL|macro|HFS_ATTR_CNID
mdefine_line|#define HFS_ATTR_CNID&t;&t;8&t;/* ATTRibutes file (HFS+) */
DECL|macro|HFS_EXCH_CNID
mdefine_line|#define HFS_EXCH_CNID&t;&t;15&t;/* ExchangeFiles temp id */
DECL|macro|HFS_FIRSTUSER_CNID
mdefine_line|#define HFS_FIRSTUSER_CNID&t;16
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
multiline_comment|/* bits hfs_finfo.fdFlags */
DECL|macro|HFS_FLG_INITED
mdefine_line|#define HFS_FLG_INITED&t;&t;0x0100
DECL|macro|HFS_FLG_LOCKED
mdefine_line|#define HFS_FLG_LOCKED&t;&t;0x1000
DECL|macro|HFS_FLG_INVISIBLE
mdefine_line|#define HFS_FLG_INVISIBLE&t;0x4000
multiline_comment|/*======== HFS structures as they appear on the disk ========*/
DECL|macro|__packed
mdefine_line|#define __packed __attribute__ ((packed))
multiline_comment|/* Pascal-style string of up to 31 characters */
DECL|struct|hfs_name
r_struct
id|hfs_name
(brace
DECL|member|len
id|u8
id|len
suffix:semicolon
DECL|member|name
id|u8
id|name
(braket
id|HFS_NAMELEN
)braket
suffix:semicolon
DECL|variable|__packed
)brace
id|__packed
suffix:semicolon
DECL|struct|hfs_point
r_struct
id|hfs_point
(brace
DECL|member|v
id|__be16
id|v
suffix:semicolon
DECL|member|h
id|__be16
id|h
suffix:semicolon
DECL|variable|__packed
)brace
id|__packed
suffix:semicolon
DECL|struct|hfs_rect
r_struct
id|hfs_rect
(brace
DECL|member|top
id|__be16
id|top
suffix:semicolon
DECL|member|left
id|__be16
id|left
suffix:semicolon
DECL|member|bottom
id|__be16
id|bottom
suffix:semicolon
DECL|member|right
id|__be16
id|right
suffix:semicolon
DECL|variable|__packed
)brace
id|__packed
suffix:semicolon
DECL|struct|hfs_finfo
r_struct
id|hfs_finfo
(brace
DECL|member|fdType
id|__be32
id|fdType
suffix:semicolon
DECL|member|fdCreator
id|__be32
id|fdCreator
suffix:semicolon
DECL|member|fdFlags
id|__be16
id|fdFlags
suffix:semicolon
DECL|member|fdLocation
r_struct
id|hfs_point
id|fdLocation
suffix:semicolon
DECL|member|fdFldr
id|__be16
id|fdFldr
suffix:semicolon
DECL|variable|__packed
)brace
id|__packed
suffix:semicolon
DECL|struct|hfs_fxinfo
r_struct
id|hfs_fxinfo
(brace
DECL|member|fdIconID
id|__be16
id|fdIconID
suffix:semicolon
DECL|member|fdUnused
id|u8
id|fdUnused
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|fdComment
id|__be16
id|fdComment
suffix:semicolon
DECL|member|fdPutAway
id|__be32
id|fdPutAway
suffix:semicolon
DECL|variable|__packed
)brace
id|__packed
suffix:semicolon
DECL|struct|hfs_dinfo
r_struct
id|hfs_dinfo
(brace
DECL|member|frRect
r_struct
id|hfs_rect
id|frRect
suffix:semicolon
DECL|member|frFlags
id|__be16
id|frFlags
suffix:semicolon
DECL|member|frLocation
r_struct
id|hfs_point
id|frLocation
suffix:semicolon
DECL|member|frView
id|__be16
id|frView
suffix:semicolon
DECL|variable|__packed
)brace
id|__packed
suffix:semicolon
DECL|struct|hfs_dxinfo
r_struct
id|hfs_dxinfo
(brace
DECL|member|frScroll
r_struct
id|hfs_point
id|frScroll
suffix:semicolon
DECL|member|frOpenChain
id|__be32
id|frOpenChain
suffix:semicolon
DECL|member|frUnused
id|__be16
id|frUnused
suffix:semicolon
DECL|member|frComment
id|__be16
id|frComment
suffix:semicolon
DECL|member|frPutAway
id|__be32
id|frPutAway
suffix:semicolon
DECL|variable|__packed
)brace
id|__packed
suffix:semicolon
DECL|union|hfs_finder_info
r_union
id|hfs_finder_info
(brace
r_struct
(brace
DECL|member|finfo
r_struct
id|hfs_finfo
id|finfo
suffix:semicolon
DECL|member|fxinfo
r_struct
id|hfs_fxinfo
id|fxinfo
suffix:semicolon
DECL|member|file
)brace
id|file
suffix:semicolon
r_struct
(brace
DECL|member|dinfo
r_struct
id|hfs_dinfo
id|dinfo
suffix:semicolon
DECL|member|dxinfo
r_struct
id|hfs_dxinfo
id|dxinfo
suffix:semicolon
DECL|member|dir
)brace
id|dir
suffix:semicolon
DECL|variable|__packed
)brace
id|__packed
suffix:semicolon
multiline_comment|/* Cast to a pointer to a generic bkey */
DECL|macro|HFS_BKEY
mdefine_line|#define&t;HFS_BKEY(X)&t;(((void)((X)-&gt;KeyLen)), ((struct hfs_bkey *)(X)))
multiline_comment|/* The key used in the catalog b-tree: */
DECL|struct|hfs_cat_key
r_struct
id|hfs_cat_key
(brace
DECL|member|key_len
id|u8
id|key_len
suffix:semicolon
multiline_comment|/* number of bytes in the key */
DECL|member|reserved
id|u8
id|reserved
suffix:semicolon
multiline_comment|/* padding */
DECL|member|ParID
id|__be32
id|ParID
suffix:semicolon
multiline_comment|/* CNID of the parent dir */
DECL|member|CName
r_struct
id|hfs_name
id|CName
suffix:semicolon
multiline_comment|/* The filename of the entry */
DECL|variable|__packed
)brace
id|__packed
suffix:semicolon
multiline_comment|/* The key used in the extents b-tree: */
DECL|struct|hfs_ext_key
r_struct
id|hfs_ext_key
(brace
DECL|member|key_len
id|u8
id|key_len
suffix:semicolon
multiline_comment|/* number of bytes in the key */
DECL|member|FkType
id|u8
id|FkType
suffix:semicolon
multiline_comment|/* HFS_FK_{DATA,RSRC} */
DECL|member|FNum
id|__be32
id|FNum
suffix:semicolon
multiline_comment|/* The File ID of the file */
DECL|member|FABN
id|__be16
id|FABN
suffix:semicolon
multiline_comment|/* allocation blocks number*/
DECL|variable|__packed
)brace
id|__packed
suffix:semicolon
DECL|union|hfs_btree_key
r_typedef
r_union
id|hfs_btree_key
(brace
DECL|member|key_len
id|u8
id|key_len
suffix:semicolon
multiline_comment|/* number of bytes in the key */
DECL|member|cat
r_struct
id|hfs_cat_key
id|cat
suffix:semicolon
DECL|member|ext
r_struct
id|hfs_ext_key
id|ext
suffix:semicolon
DECL|typedef|hfs_btree_key
)brace
id|hfs_btree_key
suffix:semicolon
DECL|typedef|btree_key
r_typedef
r_union
id|hfs_btree_key
id|btree_key
suffix:semicolon
DECL|struct|hfs_extent
r_struct
id|hfs_extent
(brace
DECL|member|block
id|__be16
id|block
suffix:semicolon
DECL|member|count
id|__be16
id|count
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|hfs_extent_rec
r_typedef
r_struct
id|hfs_extent
id|hfs_extent_rec
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* The catalog record for a file */
DECL|struct|hfs_cat_file
r_struct
id|hfs_cat_file
(brace
DECL|member|type
id|s8
id|type
suffix:semicolon
multiline_comment|/* The type of entry */
DECL|member|reserved
id|u8
id|reserved
suffix:semicolon
DECL|member|Flags
id|u8
id|Flags
suffix:semicolon
multiline_comment|/* Flags such as read-only */
DECL|member|Typ
id|s8
id|Typ
suffix:semicolon
multiline_comment|/* file version number = 0 */
DECL|member|UsrWds
r_struct
id|hfs_finfo
id|UsrWds
suffix:semicolon
multiline_comment|/* data used by the Finder */
DECL|member|FlNum
id|__be32
id|FlNum
suffix:semicolon
multiline_comment|/* The CNID */
DECL|member|StBlk
id|__be16
id|StBlk
suffix:semicolon
multiline_comment|/* obsolete */
DECL|member|LgLen
id|__be32
id|LgLen
suffix:semicolon
multiline_comment|/* The logical EOF of the data fork*/
DECL|member|PyLen
id|__be32
id|PyLen
suffix:semicolon
multiline_comment|/* The physical EOF of the data fork */
DECL|member|RStBlk
id|__be16
id|RStBlk
suffix:semicolon
multiline_comment|/* obsolete */
DECL|member|RLgLen
id|__be32
id|RLgLen
suffix:semicolon
multiline_comment|/* The logical EOF of the rsrc fork */
DECL|member|RPyLen
id|__be32
id|RPyLen
suffix:semicolon
multiline_comment|/* The physical EOF of the rsrc fork */
DECL|member|CrDat
id|__be32
id|CrDat
suffix:semicolon
multiline_comment|/* The creation date */
DECL|member|MdDat
id|__be32
id|MdDat
suffix:semicolon
multiline_comment|/* The modified date */
DECL|member|BkDat
id|__be32
id|BkDat
suffix:semicolon
multiline_comment|/* The last backup date */
DECL|member|FndrInfo
r_struct
id|hfs_fxinfo
id|FndrInfo
suffix:semicolon
multiline_comment|/* more data for the Finder */
DECL|member|ClpSize
id|__be16
id|ClpSize
suffix:semicolon
multiline_comment|/* number of bytes to allocate&n;&t;&t;&t;&t;&t;   when extending files */
DECL|member|ExtRec
id|hfs_extent_rec
id|ExtRec
suffix:semicolon
multiline_comment|/* first extent record&n;&t;&t;&t;&t;&t;   for the data fork */
DECL|member|RExtRec
id|hfs_extent_rec
id|RExtRec
suffix:semicolon
multiline_comment|/* first extent record&n;&t;&t;&t;&t;&t;   for the resource fork */
DECL|member|Resrv
id|u32
id|Resrv
suffix:semicolon
multiline_comment|/* reserved by Apple */
DECL|variable|__packed
)brace
id|__packed
suffix:semicolon
multiline_comment|/* the catalog record for a directory */
DECL|struct|hfs_cat_dir
r_struct
id|hfs_cat_dir
(brace
DECL|member|type
id|s8
id|type
suffix:semicolon
multiline_comment|/* The type of entry */
DECL|member|reserved
id|u8
id|reserved
suffix:semicolon
DECL|member|Flags
id|__be16
id|Flags
suffix:semicolon
multiline_comment|/* flags */
DECL|member|Val
id|__be16
id|Val
suffix:semicolon
multiline_comment|/* Valence: number of files and&n;&t;&t;&t;&t;&t;   dirs in the directory */
DECL|member|DirID
id|__be32
id|DirID
suffix:semicolon
multiline_comment|/* The CNID */
DECL|member|CrDat
id|__be32
id|CrDat
suffix:semicolon
multiline_comment|/* The creation date */
DECL|member|MdDat
id|__be32
id|MdDat
suffix:semicolon
multiline_comment|/* The modification date */
DECL|member|BkDat
id|__be32
id|BkDat
suffix:semicolon
multiline_comment|/* The last backup date */
DECL|member|UsrInfo
r_struct
id|hfs_dinfo
id|UsrInfo
suffix:semicolon
multiline_comment|/* data used by the Finder */
DECL|member|FndrInfo
r_struct
id|hfs_dxinfo
id|FndrInfo
suffix:semicolon
multiline_comment|/* more data used by Finder */
DECL|member|Resrv
id|u8
id|Resrv
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* reserved by Apple */
DECL|variable|__packed
)brace
id|__packed
suffix:semicolon
multiline_comment|/* the catalog record for a thread */
DECL|struct|hfs_cat_thread
r_struct
id|hfs_cat_thread
(brace
DECL|member|type
id|s8
id|type
suffix:semicolon
multiline_comment|/* The type of entry */
DECL|member|reserved
id|u8
id|reserved
(braket
l_int|9
)braket
suffix:semicolon
multiline_comment|/* reserved by Apple */
DECL|member|ParID
id|__be32
id|ParID
suffix:semicolon
multiline_comment|/* CNID of parent directory */
DECL|member|CName
r_struct
id|hfs_name
id|CName
suffix:semicolon
multiline_comment|/* The name of this entry */
DECL|variable|__packed
)brace
id|__packed
suffix:semicolon
multiline_comment|/* A catalog tree record */
DECL|union|hfs_cat_rec
r_typedef
r_union
id|hfs_cat_rec
(brace
DECL|member|type
id|s8
id|type
suffix:semicolon
multiline_comment|/* The type of entry */
DECL|member|file
r_struct
id|hfs_cat_file
id|file
suffix:semicolon
DECL|member|dir
r_struct
id|hfs_cat_dir
id|dir
suffix:semicolon
DECL|member|thread
r_struct
id|hfs_cat_thread
id|thread
suffix:semicolon
DECL|typedef|hfs_cat_rec
)brace
id|hfs_cat_rec
suffix:semicolon
DECL|struct|hfs_mdb
r_struct
id|hfs_mdb
(brace
DECL|member|drSigWord
id|__be16
id|drSigWord
suffix:semicolon
multiline_comment|/* Signature word indicating fs type */
DECL|member|drCrDate
id|__be32
id|drCrDate
suffix:semicolon
multiline_comment|/* fs creation date/time */
DECL|member|drLsMod
id|__be32
id|drLsMod
suffix:semicolon
multiline_comment|/* fs modification date/time */
DECL|member|drAtrb
id|__be16
id|drAtrb
suffix:semicolon
multiline_comment|/* fs attributes */
DECL|member|drNmFls
id|__be16
id|drNmFls
suffix:semicolon
multiline_comment|/* number of files in root directory */
DECL|member|drVBMSt
id|__be16
id|drVBMSt
suffix:semicolon
multiline_comment|/* location (in 512-byte blocks)&n;&t;&t;&t;&t;&t;   of the volume bitmap */
DECL|member|drAllocPtr
id|__be16
id|drAllocPtr
suffix:semicolon
multiline_comment|/* location (in allocation blocks)&n;&t;&t;&t;&t;&t;   to begin next allocation search */
DECL|member|drNmAlBlks
id|__be16
id|drNmAlBlks
suffix:semicolon
multiline_comment|/* number of allocation blocks */
DECL|member|drAlBlkSiz
id|__be32
id|drAlBlkSiz
suffix:semicolon
multiline_comment|/* bytes in an allocation block */
DECL|member|drClpSiz
id|__be32
id|drClpSiz
suffix:semicolon
multiline_comment|/* clumpsize, the number of bytes to&n;&t;&t;&t;&t;&t;   allocate when extending a file */
DECL|member|drAlBlSt
id|__be16
id|drAlBlSt
suffix:semicolon
multiline_comment|/* location (in 512-byte blocks)&n;&t;&t;&t;&t;&t;   of the first allocation block */
DECL|member|drNxtCNID
id|__be32
id|drNxtCNID
suffix:semicolon
multiline_comment|/* CNID to assign to the next&n;&t;&t;&t;&t;&t;   file or directory created */
DECL|member|drFreeBks
id|__be16
id|drFreeBks
suffix:semicolon
multiline_comment|/* number of free allocation blocks */
DECL|member|drVN
id|u8
id|drVN
(braket
l_int|28
)braket
suffix:semicolon
multiline_comment|/* the volume label */
DECL|member|drVolBkUp
id|__be32
id|drVolBkUp
suffix:semicolon
multiline_comment|/* fs backup date/time */
DECL|member|drVSeqNum
id|__be16
id|drVSeqNum
suffix:semicolon
multiline_comment|/* backup sequence number */
DECL|member|drWrCnt
id|__be32
id|drWrCnt
suffix:semicolon
multiline_comment|/* fs write count */
DECL|member|drXTClpSiz
id|__be32
id|drXTClpSiz
suffix:semicolon
multiline_comment|/* clumpsize for the extents B-tree */
DECL|member|drCTClpSiz
id|__be32
id|drCTClpSiz
suffix:semicolon
multiline_comment|/* clumpsize for the catalog B-tree */
DECL|member|drNmRtDirs
id|__be16
id|drNmRtDirs
suffix:semicolon
multiline_comment|/* number of directories in&n;&t;&t;&t;&t;&t;   the root directory */
DECL|member|drFilCnt
id|__be32
id|drFilCnt
suffix:semicolon
multiline_comment|/* number of files in the fs */
DECL|member|drDirCnt
id|__be32
id|drDirCnt
suffix:semicolon
multiline_comment|/* number of directories in the fs */
DECL|member|drFndrInfo
id|u8
id|drFndrInfo
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* data used by the Finder */
DECL|member|drEmbedSigWord
id|__be16
id|drEmbedSigWord
suffix:semicolon
multiline_comment|/* embedded volume signature */
DECL|member|drEmbedExtent
id|__be32
id|drEmbedExtent
suffix:semicolon
multiline_comment|/* starting block number (xdrStABN)&n;&t;&t;&t;&t;&t;   and number of allocation blocks&n;&t;&t;&t;&t;&t;   (xdrNumABlks) occupied by embedded&n;&t;&t;&t;&t;&t;   volume */
DECL|member|drXTFlSize
id|__be32
id|drXTFlSize
suffix:semicolon
multiline_comment|/* bytes in the extents B-tree */
DECL|member|drXTExtRec
id|hfs_extent_rec
id|drXTExtRec
suffix:semicolon
multiline_comment|/* extents B-tree&squot;s first 3 extents */
DECL|member|drCTFlSize
id|__be32
id|drCTFlSize
suffix:semicolon
multiline_comment|/* bytes in the catalog B-tree */
DECL|member|drCTExtRec
id|hfs_extent_rec
id|drCTExtRec
suffix:semicolon
multiline_comment|/* catalog B-tree&squot;s first 3 extents */
DECL|variable|__packed
)brace
id|__packed
suffix:semicolon
multiline_comment|/*======== Data structures kept in memory ========*/
DECL|struct|hfs_readdir_data
r_struct
id|hfs_readdir_data
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|file
r_struct
id|file
op_star
id|file
suffix:semicolon
DECL|member|key
r_struct
id|hfs_cat_key
id|key
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
