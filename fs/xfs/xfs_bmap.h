multiline_comment|/*&n; * Copyright (c) 2000 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
macro_line|#ifndef __XFS_BMAP_H__
DECL|macro|__XFS_BMAP_H__
mdefine_line|#define __XFS_BMAP_H__
r_struct
id|getbmap
suffix:semicolon
r_struct
id|xfs_bmbt_irec
suffix:semicolon
r_struct
id|xfs_inode
suffix:semicolon
r_struct
id|xfs_mount
suffix:semicolon
r_struct
id|xfs_trans
suffix:semicolon
multiline_comment|/*&n; * List of extents to be free &quot;later&quot;.&n; * The list is kept sorted on xbf_startblock.&n; */
DECL|struct|xfs_bmap_free_item
r_typedef
r_struct
id|xfs_bmap_free_item
(brace
DECL|member|xbfi_startblock
id|xfs_fsblock_t
id|xbfi_startblock
suffix:semicolon
multiline_comment|/* starting fs block number */
DECL|member|xbfi_blockcount
id|xfs_extlen_t
id|xbfi_blockcount
suffix:semicolon
multiline_comment|/* number of blocks in extent */
DECL|member|xbfi_next
r_struct
id|xfs_bmap_free_item
op_star
id|xbfi_next
suffix:semicolon
multiline_comment|/* link to next entry */
DECL|typedef|xfs_bmap_free_item_t
)brace
id|xfs_bmap_free_item_t
suffix:semicolon
multiline_comment|/*&n; * Header for free extent list.&n; */
DECL|struct|xfs_bmap_free
r_typedef
r_struct
id|xfs_bmap_free
(brace
DECL|member|xbf_first
id|xfs_bmap_free_item_t
op_star
id|xbf_first
suffix:semicolon
multiline_comment|/* list of to-be-free extents */
DECL|member|xbf_count
r_int
id|xbf_count
suffix:semicolon
multiline_comment|/* count of items on list */
DECL|member|xbf_low
r_int
id|xbf_low
suffix:semicolon
multiline_comment|/* kludge: alloc in low mode */
DECL|typedef|xfs_bmap_free_t
)brace
id|xfs_bmap_free_t
suffix:semicolon
DECL|macro|XFS_BMAP_MAX_NMAP
mdefine_line|#define XFS_BMAP_MAX_NMAP&t;4
multiline_comment|/*&n; * Flags for xfs_bmapi&n; */
DECL|macro|XFS_BMAPI_WRITE
mdefine_line|#define XFS_BMAPI_WRITE&t;&t;0x001&t;/* write operation: allocate space */
DECL|macro|XFS_BMAPI_DELAY
mdefine_line|#define XFS_BMAPI_DELAY&t;&t;0x002&t;/* delayed write operation */
DECL|macro|XFS_BMAPI_ENTIRE
mdefine_line|#define XFS_BMAPI_ENTIRE&t;0x004&t;/* return entire extent, not trimmed */
DECL|macro|XFS_BMAPI_METADATA
mdefine_line|#define XFS_BMAPI_METADATA&t;0x008&t;/* mapping metadata not user data */
DECL|macro|XFS_BMAPI_EXACT
mdefine_line|#define XFS_BMAPI_EXACT&t;&t;0x010&t;/* allocate only to spec&squot;d bounds */
DECL|macro|XFS_BMAPI_ATTRFORK
mdefine_line|#define XFS_BMAPI_ATTRFORK&t;0x020&t;/* use attribute fork not data */
DECL|macro|XFS_BMAPI_ASYNC
mdefine_line|#define XFS_BMAPI_ASYNC&t;&t;0x040&t;/* bunmapi xactions can be async */
DECL|macro|XFS_BMAPI_RSVBLOCKS
mdefine_line|#define XFS_BMAPI_RSVBLOCKS&t;0x080&t;/* OK to alloc. reserved data blocks */
DECL|macro|XFS_BMAPI_PREALLOC
mdefine_line|#define XFS_BMAPI_PREALLOC&t;0x100&t;/* preallocation op: unwritten space */
DECL|macro|XFS_BMAPI_IGSTATE
mdefine_line|#define XFS_BMAPI_IGSTATE&t;0x200&t;/* Ignore state - */
multiline_comment|/* combine contig. space */
DECL|macro|XFS_BMAPI_CONTIG
mdefine_line|#define XFS_BMAPI_CONTIG&t;0x400&t;/* must allocate only one extent */
DECL|macro|XFS_BMAPI_DIRECT_IO
mdefine_line|#define XFS_BMAPI_DIRECT_IO&t;0x800&t;/* Flag from cxfs client, not used&n;&t;&t;&t;&t;&t; * by xfs directly. Indicates alloc&n;&t;&t;&t;&t;&t; * request is for direct I/O not&n;&t;&t;&t;&t;&t; * extent conversion by server */
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_BMAPI_AFLAG)
r_int
id|xfs_bmapi_aflag
c_func
(paren
r_int
id|w
)paren
suffix:semicolon
DECL|macro|XFS_BMAPI_AFLAG
mdefine_line|#define XFS_BMAPI_AFLAG(w)&t;xfs_bmapi_aflag(w)
macro_line|#else
DECL|macro|XFS_BMAPI_AFLAG
mdefine_line|#define XFS_BMAPI_AFLAG(w)&t;((w) == XFS_ATTR_FORK ? XFS_BMAPI_ATTRFORK : 0)
macro_line|#endif
multiline_comment|/*&n; * Special values for xfs_bmbt_irec_t br_startblock field.&n; */
DECL|macro|DELAYSTARTBLOCK
mdefine_line|#define DELAYSTARTBLOCK&t;&t;((xfs_fsblock_t)-1LL)
DECL|macro|HOLESTARTBLOCK
mdefine_line|#define HOLESTARTBLOCK&t;&t;((xfs_fsblock_t)-2LL)
multiline_comment|/*&n; * Trace operations for bmap extent tracing&n; */
DECL|macro|XFS_BMAP_KTRACE_DELETE
mdefine_line|#define XFS_BMAP_KTRACE_DELETE&t;1
DECL|macro|XFS_BMAP_KTRACE_INSERT
mdefine_line|#define XFS_BMAP_KTRACE_INSERT&t;2
DECL|macro|XFS_BMAP_KTRACE_PRE_UP
mdefine_line|#define XFS_BMAP_KTRACE_PRE_UP&t;3
DECL|macro|XFS_BMAP_KTRACE_POST_UP
mdefine_line|#define XFS_BMAP_KTRACE_POST_UP 4
DECL|macro|XFS_BMAP_TRACE_SIZE
mdefine_line|#define XFS_BMAP_TRACE_SIZE&t;4096&t;/* size of global trace buffer */
DECL|macro|XFS_BMAP_KTRACE_SIZE
mdefine_line|#define XFS_BMAP_KTRACE_SIZE&t;32&t;/* size of per-inode trace buffer */
macro_line|#if defined(XFS_ALL_TRACE)
DECL|macro|XFS_BMAP_TRACE
mdefine_line|#define XFS_BMAP_TRACE
macro_line|#endif
macro_line|#if !defined(DEBUG)
DECL|macro|XFS_BMAP_TRACE
macro_line|#undef&t;XFS_BMAP_TRACE
macro_line|#endif
macro_line|#if XFS_WANT_FUNCS || (XFS_WANT_SPACE &amp;&amp; XFSSO_XFS_BMAP_INIT)
r_void
id|xfs_bmap_init
c_func
(paren
id|xfs_bmap_free_t
op_star
id|flp
comma
id|xfs_fsblock_t
op_star
id|fbp
)paren
suffix:semicolon
DECL|macro|XFS_BMAP_INIT
mdefine_line|#define XFS_BMAP_INIT(flp,fbp)&t;xfs_bmap_init(flp,fbp)
macro_line|#else
DECL|macro|XFS_BMAP_INIT
mdefine_line|#define XFS_BMAP_INIT(flp,fbp)&t;&bslash;&n;&t;((flp)-&gt;xbf_first = NULL, (flp)-&gt;xbf_count = 0, &bslash;&n;&t; (flp)-&gt;xbf_low = 0, *(fbp) = NULLFSBLOCK)
macro_line|#endif
multiline_comment|/*&n; * Argument structure for xfs_bmap_alloc.&n; */
DECL|struct|xfs_bmalloca
r_typedef
r_struct
id|xfs_bmalloca
(brace
DECL|member|firstblock
id|xfs_fsblock_t
id|firstblock
suffix:semicolon
multiline_comment|/* i/o first block allocated */
DECL|member|rval
id|xfs_fsblock_t
id|rval
suffix:semicolon
multiline_comment|/* starting block of new extent */
DECL|member|off
id|xfs_fileoff_t
id|off
suffix:semicolon
multiline_comment|/* offset in file filling in */
DECL|member|tp
r_struct
id|xfs_trans
op_star
id|tp
suffix:semicolon
multiline_comment|/* transaction pointer */
DECL|member|ip
r_struct
id|xfs_inode
op_star
id|ip
suffix:semicolon
multiline_comment|/* incore inode pointer */
DECL|member|prevp
r_struct
id|xfs_bmbt_irec
op_star
id|prevp
suffix:semicolon
multiline_comment|/* extent before the new one */
DECL|member|gotp
r_struct
id|xfs_bmbt_irec
op_star
id|gotp
suffix:semicolon
multiline_comment|/* extent after, or delayed */
DECL|member|alen
id|xfs_extlen_t
id|alen
suffix:semicolon
multiline_comment|/* i/o length asked/allocated */
DECL|member|total
id|xfs_extlen_t
id|total
suffix:semicolon
multiline_comment|/* total blocks needed for xaction */
DECL|member|minlen
id|xfs_extlen_t
id|minlen
suffix:semicolon
multiline_comment|/* mininum allocation size (blocks) */
DECL|member|minleft
id|xfs_extlen_t
id|minleft
suffix:semicolon
multiline_comment|/* amount must be left after alloc */
DECL|member|eof
r_char
id|eof
suffix:semicolon
multiline_comment|/* set if allocating past last extent */
DECL|member|wasdel
r_char
id|wasdel
suffix:semicolon
multiline_comment|/* replacing a delayed allocation */
DECL|member|userdata
r_char
id|userdata
suffix:semicolon
multiline_comment|/* set if is user data */
DECL|member|low
r_char
id|low
suffix:semicolon
multiline_comment|/* low on space, using seq&squot;l ags */
DECL|member|aeof
r_char
id|aeof
suffix:semicolon
multiline_comment|/* allocated space at eof */
DECL|typedef|xfs_bmalloca_t
)brace
id|xfs_bmalloca_t
suffix:semicolon
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * Convert inode from non-attributed to attributed.&n; * Must not be in a transaction, ip must not be locked.&n; */
r_int
multiline_comment|/* error code */
id|xfs_bmap_add_attrfork
c_func
(paren
r_struct
id|xfs_inode
op_star
id|ip
comma
multiline_comment|/* incore inode pointer */
r_int
id|rsvd
)paren
suffix:semicolon
multiline_comment|/* flag for reserved block allocation */
multiline_comment|/*&n; * Add the extent to the list of extents to be free at transaction end.&n; * The list is maintained sorted (by block number).&n; */
r_void
id|xfs_bmap_add_free
c_func
(paren
id|xfs_fsblock_t
id|bno
comma
multiline_comment|/* fs block number of extent */
id|xfs_filblks_t
id|len
comma
multiline_comment|/* length of extent */
id|xfs_bmap_free_t
op_star
id|flist
comma
multiline_comment|/* list of extents */
r_struct
id|xfs_mount
op_star
id|mp
)paren
suffix:semicolon
multiline_comment|/* mount point structure */
multiline_comment|/*&n; * Routine to clean up the free list data structure when&n; * an error occurs during a transaction.&n; */
r_void
id|xfs_bmap_cancel
c_func
(paren
id|xfs_bmap_free_t
op_star
id|flist
)paren
suffix:semicolon
multiline_comment|/* free list to clean up */
multiline_comment|/*&n; * Routine to check if a specified inode is swap capable.&n; */
r_int
id|xfs_bmap_check_swappable
c_func
(paren
r_struct
id|xfs_inode
op_star
id|ip
)paren
suffix:semicolon
multiline_comment|/* incore inode */
multiline_comment|/*&n; * Compute and fill in the value of the maximum depth of a bmap btree&n; * in this filesystem.&t;Done once, during mount.&n; */
r_void
id|xfs_bmap_compute_maxlevels
c_func
(paren
r_struct
id|xfs_mount
op_star
id|mp
comma
multiline_comment|/* file system mount structure */
r_int
id|whichfork
)paren
suffix:semicolon
multiline_comment|/* data or attr fork */
multiline_comment|/*&n; * Routine to be called at transaction&squot;s end by xfs_bmapi, xfs_bunmapi&n; * caller.  Frees all the extents that need freeing, which must be done&n; * last due to locking considerations.&n; *&n; * Return 1 if the given transaction was committed and a new one allocated,&n; * and 0 otherwise.&n; */
r_int
multiline_comment|/* error */
id|xfs_bmap_finish
c_func
(paren
r_struct
id|xfs_trans
op_star
op_star
id|tp
comma
multiline_comment|/* transaction pointer addr */
id|xfs_bmap_free_t
op_star
id|flist
comma
multiline_comment|/* i/o: list extents to free */
id|xfs_fsblock_t
id|firstblock
comma
multiline_comment|/* controlled a.g. for allocs */
r_int
op_star
id|committed
)paren
suffix:semicolon
multiline_comment|/* xact committed or not */
multiline_comment|/*&n; * Returns the file-relative block number of the first unused block in the file.&n; * This is the lowest-address hole if the file has holes, else the first block&n; * past the end of file.&n; */
r_int
multiline_comment|/* error */
id|xfs_bmap_first_unused
c_func
(paren
r_struct
id|xfs_trans
op_star
id|tp
comma
multiline_comment|/* transaction pointer */
r_struct
id|xfs_inode
op_star
id|ip
comma
multiline_comment|/* incore inode */
id|xfs_extlen_t
id|len
comma
multiline_comment|/* size of hole to find */
id|xfs_fileoff_t
op_star
id|unused
comma
multiline_comment|/* unused block num */
r_int
id|whichfork
)paren
suffix:semicolon
multiline_comment|/* data or attr fork */
multiline_comment|/*&n; * Returns the file-relative block number of the last block + 1 before&n; * last_block (input value) in the file.&n; * This is not based on i_size, it is based on the extent list.&n; * Returns 0 for local files, as they do not have an extent list.&n; */
r_int
multiline_comment|/* error */
id|xfs_bmap_last_before
c_func
(paren
r_struct
id|xfs_trans
op_star
id|tp
comma
multiline_comment|/* transaction pointer */
r_struct
id|xfs_inode
op_star
id|ip
comma
multiline_comment|/* incore inode */
id|xfs_fileoff_t
op_star
id|last_block
comma
multiline_comment|/* last block */
r_int
id|whichfork
)paren
suffix:semicolon
multiline_comment|/* data or attr fork */
multiline_comment|/*&n; * Returns the file-relative block number of the first block past eof in&n; * the file.  This is not based on i_size, it is based on the extent list.&n; * Returns 0 for local files, as they do not have an extent list.&n; */
r_int
multiline_comment|/* error */
id|xfs_bmap_last_offset
c_func
(paren
r_struct
id|xfs_trans
op_star
id|tp
comma
multiline_comment|/* transaction pointer */
r_struct
id|xfs_inode
op_star
id|ip
comma
multiline_comment|/* incore inode */
id|xfs_fileoff_t
op_star
id|unused
comma
multiline_comment|/* last block num */
r_int
id|whichfork
)paren
suffix:semicolon
multiline_comment|/* data or attr fork */
multiline_comment|/*&n; * Returns whether the selected fork of the inode has exactly one&n; * block or not.  For the data fork we check this matches di_size,&n; * implying the file&squot;s range is 0..bsize-1.&n; */
r_int
id|xfs_bmap_one_block
c_func
(paren
r_struct
id|xfs_inode
op_star
id|ip
comma
multiline_comment|/* incore inode */
r_int
id|whichfork
)paren
suffix:semicolon
multiline_comment|/* data or attr fork */
multiline_comment|/*&n; * Read in the extents to iu_extents.&n; * All inode fields are set up by caller, we just traverse the btree&n; * and copy the records in.&n; */
r_int
multiline_comment|/* error */
id|xfs_bmap_read_extents
c_func
(paren
r_struct
id|xfs_trans
op_star
id|tp
comma
multiline_comment|/* transaction pointer */
r_struct
id|xfs_inode
op_star
id|ip
comma
multiline_comment|/* incore inode */
r_int
id|whichfork
)paren
suffix:semicolon
multiline_comment|/* data or attr fork */
macro_line|#if defined(XFS_BMAP_TRACE)
multiline_comment|/*&n; * Add bmap trace insert entries for all the contents of the extent list.&n; */
r_void
id|xfs_bmap_trace_exlist
c_func
(paren
r_char
op_star
id|fname
comma
multiline_comment|/* function name */
r_struct
id|xfs_inode
op_star
id|ip
comma
multiline_comment|/* incore inode pointer */
id|xfs_extnum_t
id|cnt
comma
multiline_comment|/* count of entries in list */
r_int
id|whichfork
)paren
suffix:semicolon
multiline_comment|/* data or attr fork */
macro_line|#else
DECL|macro|xfs_bmap_trace_exlist
mdefine_line|#define xfs_bmap_trace_exlist(f,ip,c,w)
macro_line|#endif
multiline_comment|/*&n; * Map file blocks to filesystem blocks.&n; * File range is given by the bno/len pair.&n; * Adds blocks to file if a write (&quot;flags &amp; XFS_BMAPI_WRITE&quot; set)&n; * into a hole or past eof.&n; * Only allocates blocks from a single allocation group,&n; * to avoid locking problems.&n; * The returned value in &quot;firstblock&quot; from the first call in a transaction&n; * must be remembered and presented to subsequent calls in &quot;firstblock&quot;.&n; * An upper bound for the number of blocks to be allocated is supplied to&n; * the first call in &quot;total&quot;; if no allocation group has that many free&n; * blocks then the call will fail (return NULLFSBLOCK in &quot;firstblock&quot;).&n; */
r_int
multiline_comment|/* error */
id|xfs_bmapi
c_func
(paren
r_struct
id|xfs_trans
op_star
id|tp
comma
multiline_comment|/* transaction pointer */
r_struct
id|xfs_inode
op_star
id|ip
comma
multiline_comment|/* incore inode */
id|xfs_fileoff_t
id|bno
comma
multiline_comment|/* starting file offs. mapped */
id|xfs_filblks_t
id|len
comma
multiline_comment|/* length to map in file */
r_int
id|flags
comma
multiline_comment|/* XFS_BMAPI_... */
id|xfs_fsblock_t
op_star
id|firstblock
comma
multiline_comment|/* first allocated block&n;&t;&t;&t;&t;&t;&t;   controls a.g. for allocs */
id|xfs_extlen_t
id|total
comma
multiline_comment|/* total blocks needed */
r_struct
id|xfs_bmbt_irec
op_star
id|mval
comma
multiline_comment|/* output: map values */
r_int
op_star
id|nmap
comma
multiline_comment|/* i/o: mval size/count */
id|xfs_bmap_free_t
op_star
id|flist
)paren
suffix:semicolon
multiline_comment|/* i/o: list extents to free */
multiline_comment|/*&n; * Map file blocks to filesystem blocks, simple version.&n; * One block only, read-only.&n; * For flags, only the XFS_BMAPI_ATTRFORK flag is examined.&n; * For the other flag values, the effect is as if XFS_BMAPI_METADATA&n; * was set and all the others were clear.&n; */
r_int
multiline_comment|/* error */
id|xfs_bmapi_single
c_func
(paren
r_struct
id|xfs_trans
op_star
id|tp
comma
multiline_comment|/* transaction pointer */
r_struct
id|xfs_inode
op_star
id|ip
comma
multiline_comment|/* incore inode */
r_int
id|whichfork
comma
multiline_comment|/* data or attr fork */
id|xfs_fsblock_t
op_star
id|fsb
comma
multiline_comment|/* output: mapped block */
id|xfs_fileoff_t
id|bno
)paren
suffix:semicolon
multiline_comment|/* starting file offs. mapped */
multiline_comment|/*&n; * Unmap (remove) blocks from a file.&n; * If nexts is nonzero then the number of extents to remove is limited to&n; * that value.&t;If not all extents in the block range can be removed then&n; * *done is set.&n; */
r_int
multiline_comment|/* error */
id|xfs_bunmapi
c_func
(paren
r_struct
id|xfs_trans
op_star
id|tp
comma
multiline_comment|/* transaction pointer */
r_struct
id|xfs_inode
op_star
id|ip
comma
multiline_comment|/* incore inode */
id|xfs_fileoff_t
id|bno
comma
multiline_comment|/* starting offset to unmap */
id|xfs_filblks_t
id|len
comma
multiline_comment|/* length to unmap in file */
r_int
id|flags
comma
multiline_comment|/* XFS_BMAPI_... */
id|xfs_extnum_t
id|nexts
comma
multiline_comment|/* number of extents max */
id|xfs_fsblock_t
op_star
id|firstblock
comma
multiline_comment|/* first allocated block&n;&t;&t;&t;&t;&t;&t;   controls a.g. for allocs */
id|xfs_bmap_free_t
op_star
id|flist
comma
multiline_comment|/* i/o: list extents to free */
r_int
op_star
id|done
)paren
suffix:semicolon
multiline_comment|/* set if not done yet */
multiline_comment|/*&n; * Fcntl interface to xfs_bmapi.&n; */
r_int
multiline_comment|/* error code */
id|xfs_getbmap
c_func
(paren
id|bhv_desc_t
op_star
id|bdp
comma
multiline_comment|/* XFS behavior descriptor*/
r_struct
id|getbmap
op_star
id|bmv
comma
multiline_comment|/* user bmap structure */
r_void
op_star
id|ap
comma
multiline_comment|/* pointer to user&squot;s array */
r_int
id|iflags
)paren
suffix:semicolon
multiline_comment|/* interface flags */
multiline_comment|/*&n; * Check the last inode extent to determine whether this allocation will result&n; * in blocks being allocated at the end of the file. When we allocate new data&n; * blocks at the end of the file which do not start at the previous data block,&n; * we will try to align the new blocks at stripe unit boundaries.&n; */
r_int
id|xfs_bmap_isaeof
c_func
(paren
r_struct
id|xfs_inode
op_star
id|ip
comma
id|xfs_fileoff_t
id|off
comma
r_int
id|whichfork
comma
r_char
op_star
id|aeof
)paren
suffix:semicolon
multiline_comment|/*&n; * Check if the endoff is outside the last extent. If so the caller will grow&n; * the allocation to a stripe unit boundary&n; */
r_int
id|xfs_bmap_eof
c_func
(paren
r_struct
id|xfs_inode
op_star
id|ip
comma
id|xfs_fileoff_t
id|endoff
comma
r_int
id|whichfork
comma
r_int
op_star
id|eof
)paren
suffix:semicolon
multiline_comment|/*&n; * Count fsblocks of the given fork.&n; */
r_int
id|xfs_bmap_count_blocks
c_func
(paren
id|xfs_trans_t
op_star
id|tp
comma
id|xfs_inode_t
op_star
id|ip
comma
r_int
id|whichfork
comma
r_int
op_star
id|count
)paren
suffix:semicolon
multiline_comment|/*&n; * Check an extent list, which has just been read, for&n; * any bit in the extent flag field.&n; */
r_int
id|xfs_check_nostate_extents
c_func
(paren
id|xfs_bmbt_rec_t
op_star
id|ep
comma
id|xfs_extnum_t
id|num
)paren
suffix:semicolon
macro_line|#endif&t;/* __KERNEL__ */
macro_line|#endif&t;/* __XFS_BMAP_H__ */
eof
