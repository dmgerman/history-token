multiline_comment|/* cache-layout.h: AFS cache layout&n; *&n; * Copyright (C) 2002 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; *&n; *&n; * The cache is stored on a block device and is laid out as:&n; *&n; *  0&t;+------------------------------------------------&n; *&t;|&n; *&t;|  SuperBlock&n; *&t;|&n; *  1&t;+------------------------------------------------&n; *&t;|&n; *&t;|  file-meta-data File: Data block #0&n; *&t;|  - file-meta-data file (volix #0 file #0) : Meta-data block&n; *&t;|    - contains direct pointers to first 64 file data blocks&n; *&t;|  - Cached cell catalogue file (volix #0 file #1) file: Meta-data block&n; *&t;|  - Cached volume location catalogue file (volix #0 file #2): Meta-data block&n; *&t;|  - Vnode catalogue hash bucket #n file: Meta-data block&n; *&t;|&n; *  2&t;+------------------------------------------------&n; *&t;|&n; *&t;|  Bitmap Block Allocation Bitmap&n; *&t;|  - 1 bit per block in the bitmap block&n; *      |  - bit 0 of dword 0 refers to the bitmap block 0&n; *&t;|    - set if the bitmap block is full&n; *      |  - 32768 bits per block, requiring 4 blocks for a 16Tb cache&n; *&t;|  - bitmap bitmap blocks are cleared initially&n; *&t;|  - not present if &lt;4 bitmap blocks&n; *&t;|&n; *&t;+------------------------------------------------&n; *&t;|&n; *&t;|  File Block Allocation Bitmap&n; *&t;|  - 1 bit per block in the cache&n; *      |  - bit 0 of dword 0 refers to the first block of the data cache&n; *&t;|    - set if block is allocated&n; *      |  - 32768 bits per block, requiring 131072 blocks for a 16Tb cache&n; *&t;|  - bitmap blocks are cleared lazily (sb-&gt;bix_bitmap_unready)&n; *&t;|&n; *&t;+------------------------------------------------&n; *&t;|&n; *&t;|  Data Cache&n; *&t;|&n; *  End&t;+------------------------------------------------&n; *&n; * Blocks are indexed by an unsigned 32-bit word, meaning that the cache can hold up to 2^32 pages,&n; * or 16Tb in total.&n; *&n; * Credentials will be cached in memory, since they are subject to change without notice, and are&n; * difficult to derive manually, being constructed from the following information:&n; * - per vnode user ID and mode mask&n; * - parent directory ACL&n; * - directory ACL (dirs only)&n; * - group lists from ptserver&n; */
macro_line|#ifndef _LINUX_AFS_CACHE_LAYOUT_H
DECL|macro|_LINUX_AFS_CACHE_LAYOUT_H
mdefine_line|#define _LINUX_AFS_CACHE_LAYOUT_H
macro_line|#include &quot;types.h&quot;
DECL|typedef|afsc_blockix_t
r_typedef
id|u32
id|afsc_blockix_t
suffix:semicolon
DECL|typedef|afsc_cellix_t
r_typedef
id|u32
id|afsc_cellix_t
suffix:semicolon
multiline_comment|/* Cached volume index&n; * - afsc_volix_t/4 is the index into the volume cache&n; * - afsc_volix_t%4 is 0 for R/W, 1 for R/O and 2 for Bak (3 is not used)&n; * - afsc_volix_t==0-3 refers to a &quot;virtual&quot; volume that stores meta-data about the cache&n; */
r_typedef
r_struct
(brace
DECL|member|index
id|u32
id|index
suffix:semicolon
DECL|typedef|afsc_volix_t
)brace
id|afsc_volix_t
suffix:semicolon
DECL|macro|AFSC_VNCAT_HASH_NBUCKETS
mdefine_line|#define AFSC_VNCAT_HASH_NBUCKETS&t;128
multiline_comment|/* special meta file IDs (all cell 0 vol 0) */
DECL|enum|afsc_meta_fids
r_enum
id|afsc_meta_fids
(brace
DECL|enumerator|AFSC_META_FID_METADATA
id|AFSC_META_FID_METADATA
op_assign
l_int|0
comma
DECL|enumerator|AFSC_META_FID_CELL_CATALOGUE
id|AFSC_META_FID_CELL_CATALOGUE
op_assign
l_int|1
comma
DECL|enumerator|AFSC_META_FID_VLDB_CATALOGUE
id|AFSC_META_FID_VLDB_CATALOGUE
op_assign
l_int|2
comma
DECL|enumerator|AFSC_META_FID_VNODE_CATALOGUE0
id|AFSC_META_FID_VNODE_CATALOGUE0
op_assign
l_int|3
comma
DECL|enumerator|AFSC_META_FID__COUNT
id|AFSC_META_FID__COUNT
op_assign
id|AFSC_VNCAT_HASH_NBUCKETS
op_plus
l_int|3
)brace
suffix:semicolon
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * cache superblock block layout&n; * - the blockdev is prepared for initialisation by &squot;echo &quot;kafsuninit&quot; &gt;/dev/hdaXX&squot; before mounting&n; * - when initialised, the magic number is changed to &quot;kafs-cache&quot;&n; */
DECL|struct|afsc_super_block
r_struct
id|afsc_super_block
(brace
DECL|member|magic
r_char
id|magic
(braket
l_int|10
)braket
suffix:semicolon
multiline_comment|/* magic number */
DECL|macro|AFSC_SUPER_MAGIC
mdefine_line|#define AFSC_SUPER_MAGIC &quot;kafs-cache&quot;
DECL|macro|AFSC_SUPER_MAGIC_NEEDS_INIT
mdefine_line|#define AFSC_SUPER_MAGIC_NEEDS_INIT &quot;kafsuninit&quot;
DECL|macro|AFSC_SUPER_MAGIC_SIZE
mdefine_line|#define AFSC_SUPER_MAGIC_SIZE 10
DECL|member|endian
r_int
r_int
id|endian
suffix:semicolon
multiline_comment|/* 0x1234 stored CPU-normal order */
DECL|macro|AFSC_SUPER_ENDIAN
mdefine_line|#define AFSC_SUPER_ENDIAN 0x1234
DECL|member|version
r_int
id|version
suffix:semicolon
multiline_comment|/* format version */
DECL|macro|AFSC_SUPER_VERSION
mdefine_line|#define AFSC_SUPER_VERSION 1
multiline_comment|/* layout */
DECL|member|bsize
r_int
id|bsize
suffix:semicolon
multiline_comment|/* cache block size */
DECL|member|bix_bitmap_fullmap
id|afsc_blockix_t
id|bix_bitmap_fullmap
suffix:semicolon
multiline_comment|/* block ix of bitmap full bitmap */
DECL|member|bix_bitmap
id|afsc_blockix_t
id|bix_bitmap
suffix:semicolon
multiline_comment|/* block ix of alloc bitmap */
DECL|member|bix_bitmap_unready
id|afsc_blockix_t
id|bix_bitmap_unready
suffix:semicolon
multiline_comment|/* block ix of unready area of bitmap */
DECL|member|bix_cache
id|afsc_blockix_t
id|bix_cache
suffix:semicolon
multiline_comment|/* block ix of data cache */
DECL|member|bix_end
id|afsc_blockix_t
id|bix_end
suffix:semicolon
multiline_comment|/* block ix of end of cache */
)brace
suffix:semicolon
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * vnode (inode) metadata cache record&n; * - padded out to 512 bytes and stored eight to a page&n; * - only the data version is necessary&n; *   - disconnected operation is not supported&n; *   - afs_iget() contacts the server to get the meta-data _anyway_ when an inode is first brought&n; *     into memory&n; * - at least 64 direct block pointers will be available (a directory is max 256Kb)&n; * - any block pointer which is 0 indicates an uncached page&n; */
DECL|struct|afsc_vnode_meta
r_struct
id|afsc_vnode_meta
(brace
multiline_comment|/* file ID */
DECL|member|volume_ix
id|afsc_volix_t
id|volume_ix
suffix:semicolon
multiline_comment|/* volume catalogue index */
DECL|member|vnode
r_int
id|vnode
suffix:semicolon
multiline_comment|/* vnode number */
DECL|member|unique
r_int
id|unique
suffix:semicolon
multiline_comment|/* FID unique */
DECL|member|size
r_int
id|size
suffix:semicolon
multiline_comment|/* size of file */
DECL|member|mtime
id|time_t
id|mtime
suffix:semicolon
multiline_comment|/* last modification time */
multiline_comment|/* file status */
DECL|member|version
id|afs_dataversion_t
id|version
suffix:semicolon
multiline_comment|/* current data version */
multiline_comment|/* file contents */
DECL|member|dbl_indirect
id|afsc_blockix_t
id|dbl_indirect
suffix:semicolon
multiline_comment|/* double indirect block index */
DECL|member|indirect
id|afsc_blockix_t
id|indirect
suffix:semicolon
multiline_comment|/* single indirect block 0 index */
DECL|member|direct
id|afsc_blockix_t
id|direct
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* direct block index (#AFSC_VNODE_META_DIRECT) */
)brace
suffix:semicolon
DECL|macro|AFSC_VNODE_META_RECSIZE
mdefine_line|#define AFSC_VNODE_META_RECSIZE&t;512&t;/* record size */
DECL|macro|AFSC_VNODE_META_DIRECT
mdefine_line|#define AFSC_VNODE_META_DIRECT&t;&bslash;&n;&t;((AFSC_VNODE_META_RECSIZE-sizeof(struct afsc_vnode_meta))/sizeof(afsc_blockix_t))
DECL|macro|AFSC_VNODE_META_PER_PAGE
mdefine_line|#define AFSC_VNODE_META_PER_PAGE&t;(PAGE_SIZE / AFSC_VNODE_META_RECSIZE)
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * entry in the cached cell catalogue&n; */
DECL|struct|afsc_cell_record
r_struct
id|afsc_cell_record
(brace
DECL|member|name
r_char
id|name
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* cell name (padded with NULs) */
DECL|member|servers
r_struct
id|in_addr
id|servers
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* cached cell servers */
)brace
suffix:semicolon
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * entry in the cached volume location catalogue&n; * - indexed by afsc_volix_t/4&n; */
DECL|struct|afsc_vldb_record
r_struct
id|afsc_vldb_record
(brace
DECL|member|name
r_char
id|name
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* volume name (padded with NULs) */
DECL|member|vid
id|afs_volid_t
id|vid
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* volume IDs for R/W, R/O and Bak volumes */
DECL|member|vidmask
r_int
r_char
id|vidmask
suffix:semicolon
multiline_comment|/* voltype mask for vid[] */
DECL|member|_pad
r_int
r_char
id|_pad
(braket
l_int|1
)braket
suffix:semicolon
DECL|member|nservers
r_int
r_int
id|nservers
suffix:semicolon
multiline_comment|/* number of entries used in servers[] */
DECL|member|servers
r_struct
id|in_addr
id|servers
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* fileserver addresses */
DECL|member|srvtmask
r_int
r_char
id|srvtmask
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* voltype masks for servers[] */
DECL|macro|AFSC_VOL_STM_RW
mdefine_line|#define AFSC_VOL_STM_RW&t;0x01 /* server holds a R/W version of the volume */
DECL|macro|AFSC_VOL_STM_RO
mdefine_line|#define AFSC_VOL_STM_RO&t;0x02 /* server holds a R/O version of the volume */
DECL|macro|AFSC_VOL_STM_BAK
mdefine_line|#define AFSC_VOL_STM_BAK&t;0x04 /* server holds a backup version of the volume */
DECL|member|cell_ix
id|afsc_cellix_t
id|cell_ix
suffix:semicolon
multiline_comment|/* cell catalogue index (MAX_UINT if unused) */
DECL|member|ctime
id|time_t
id|ctime
suffix:semicolon
multiline_comment|/* time at which cached */
)brace
suffix:semicolon
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * vnode catalogue entry&n; * - must be 2^x size so that do_generic_file_read doesn&squot;t present them split across pages&n; */
DECL|struct|afsc_vnode_catalogue
r_struct
id|afsc_vnode_catalogue
(brace
DECL|member|volume_ix
id|afsc_volix_t
id|volume_ix
suffix:semicolon
multiline_comment|/* volume catalogue index */
DECL|member|vnode
id|afs_vnodeid_t
id|vnode
suffix:semicolon
multiline_comment|/* vnode ID */
DECL|member|meta_ix
id|u32
id|meta_ix
suffix:semicolon
multiline_comment|/* metadata file index */
DECL|member|atime
id|u32
id|atime
suffix:semicolon
multiline_comment|/* last time entry accessed */
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|macro|AFSC_VNODE_CATALOGUE_PER_BLOCK
mdefine_line|#define AFSC_VNODE_CATALOGUE_PER_BLOCK ((size_t)(PAGE_SIZE/sizeof(struct afsc_vnode_catalogue)))
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * vnode data &quot;page directory&quot; block&n; * - first 1024 pages don&squot;t map through here&n; * - PAGE_SIZE in size&n; */
DECL|struct|afsc_indirect_block
r_struct
id|afsc_indirect_block
(brace
DECL|member|pt_bix
id|afsc_blockix_t
id|pt_bix
(braket
l_int|1024
)braket
suffix:semicolon
multiline_comment|/* &quot;page table&quot; block indices */
)brace
suffix:semicolon
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * vnode data &quot;page table&quot; block&n; * - PAGE_SIZE in size&n; */
DECL|struct|afsc_dbl_indirect_block
r_struct
id|afsc_dbl_indirect_block
(brace
DECL|member|page_bix
id|afsc_blockix_t
id|page_bix
(braket
l_int|1024
)braket
suffix:semicolon
multiline_comment|/* &quot;page&quot; block indices */
)brace
suffix:semicolon
macro_line|#endif /* _LINUX_AFS_CACHE_LAYOUT_H */
eof
