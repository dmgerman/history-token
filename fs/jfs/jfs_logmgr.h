multiline_comment|/*&n; *   Copyright (c) International Business Machines Corp., 2000-2002&n; *&n; *   This program is free software;  you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or &n; *   (at your option) any later version.&n; * &n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY;  without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See&n; *   the GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program;  if not, write to the Free Software &n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; */
macro_line|#ifndef&t;_H_JFS_LOGMGR
DECL|macro|_H_JFS_LOGMGR
mdefine_line|#define _H_JFS_LOGMGR
macro_line|#include &quot;jfs_filsys.h&quot;
macro_line|#include &quot;jfs_lock.h&quot;
multiline_comment|/*&n; *&t;log manager configuration parameters&n; */
multiline_comment|/* log page size */
DECL|macro|LOGPSIZE
mdefine_line|#define&t;LOGPSIZE&t;4096
DECL|macro|L2LOGPSIZE
mdefine_line|#define&t;L2LOGPSIZE&t;12
DECL|macro|LOGPAGES
mdefine_line|#define LOGPAGES&t;16&t;/* Log pages per mounted file system */
multiline_comment|/*&n; *&t;log logical volume&n; *&n; * a log is used to make the commit operation on journalled &n; * files within the same logical volume group atomic.&n; * a log is implemented with a logical volume.&n; * there is one log per logical volume group. &n; *&n; * block 0 of the log logical volume is not used (ipl etc).&n; * block 1 contains a log &quot;superblock&quot; and is used by logFormat(),&n; * lmLogInit(), lmLogShutdown(), and logRedo() to record status &n; * of the log but is not otherwise used during normal processing. &n; * blocks 2 - (N-1) are used to contain log records.&n; *&n; * when a volume group is varied-on-line, logRedo() must have &n; * been executed before the file systems (logical volumes) in &n; * the volume group can be mounted.&n; */
multiline_comment|/*&n; *&t;log superblock (block 1 of logical volume)&n; */
DECL|macro|LOGSUPER_B
mdefine_line|#define&t;LOGSUPER_B&t;1
DECL|macro|LOGSTART_B
mdefine_line|#define&t;LOGSTART_B&t;2
DECL|macro|LOGMAGIC
mdefine_line|#define&t;LOGMAGIC&t;0x87654321
DECL|macro|LOGVERSION
mdefine_line|#define&t;LOGVERSION&t;1
DECL|macro|MAX_ACTIVE
mdefine_line|#define MAX_ACTIVE&t;128&t;/* Max active file systems sharing log */
r_typedef
r_struct
(brace
DECL|member|magic
id|u32
id|magic
suffix:semicolon
multiline_comment|/* 4: log lv identifier */
DECL|member|version
id|s32
id|version
suffix:semicolon
multiline_comment|/* 4: version number */
DECL|member|serial
id|s32
id|serial
suffix:semicolon
multiline_comment|/* 4: log open/mount counter */
DECL|member|size
id|s32
id|size
suffix:semicolon
multiline_comment|/* 4: size in number of LOGPSIZE blocks */
DECL|member|bsize
id|s32
id|bsize
suffix:semicolon
multiline_comment|/* 4: logical block size in byte */
DECL|member|l2bsize
id|s32
id|l2bsize
suffix:semicolon
multiline_comment|/* 4: log2 of bsize */
DECL|member|flag
id|u32
id|flag
suffix:semicolon
multiline_comment|/* 4: option */
DECL|member|state
id|u32
id|state
suffix:semicolon
multiline_comment|/* 4: state - see below */
DECL|member|end
id|s32
id|end
suffix:semicolon
multiline_comment|/* 4: addr of last log record set by logredo */
DECL|member|uuid
r_char
id|uuid
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* 16: 128-bit journal uuid */
DECL|member|label
r_char
id|label
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* 16: journal label */
r_struct
(brace
DECL|member|uuid
r_char
id|uuid
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|active
)brace
id|active
(braket
id|MAX_ACTIVE
)braket
suffix:semicolon
multiline_comment|/* 2048: active file systems list */
DECL|typedef|logsuper_t
)brace
id|logsuper_t
suffix:semicolon
DECL|macro|NULL_UUID
mdefine_line|#define NULL_UUID &quot;&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&quot;
multiline_comment|/* log flag: commit option (see jfs_filsys.h) */
multiline_comment|/* log state */
DECL|macro|LOGMOUNT
mdefine_line|#define&t;LOGMOUNT&t;0&t;/* log mounted by lmLogInit() */
DECL|macro|LOGREDONE
mdefine_line|#define LOGREDONE&t;1&t;/* log shutdown by lmLogShutdown().&n;&t;&t;&t;&t; * log redo completed by logredo().&n;&t;&t;&t;&t; */
DECL|macro|LOGWRAP
mdefine_line|#define LOGWRAP&t;&t;2&t;/* log wrapped */
DECL|macro|LOGREADERR
mdefine_line|#define LOGREADERR&t;3&t;/* log read error detected in logredo() */
multiline_comment|/*&n; *&t;log logical page&n; *&n; * (this comment should be rewritten !)&n; * the header and trailer structures (h,t) will normally have &n; * the same page and eor value.&n; * An exception to this occurs when a complete page write is not &n; * accomplished on a power failure. Since the hardware may &quot;split write&quot;&n; * sectors in the page, any out of order sequence may occur during powerfail &n; * and needs to be recognized during log replay.  The xor value is&n; * an &quot;exclusive or&quot; of all log words in the page up to eor.  This&n; * 32 bit eor is stored with the top 16 bits in the header and the&n; * bottom 16 bits in the trailer.  logredo can easily recognize pages&n; * that were not completed by reconstructing this eor and checking &n; * the log page.&n; *&n; * Previous versions of the operating system did not allow split &n; * writes and detected partially written records in logredo by &n; * ordering the updates to the header, trailer, and the move of data &n; * into the logdata area.  The order: (1) data is moved (2) header &n; * is updated (3) trailer is updated.  In logredo, when the header &n; * differed from the trailer, the header and trailer were reconciled &n; * as follows: if h.page != t.page they were set to the smaller of &n; * the two and h.eor and t.eor set to 8 (i.e. empty page). if (only) &n; * h.eor != t.eor they were set to the smaller of their two values.&n; */
r_typedef
r_struct
(brace
r_struct
(brace
multiline_comment|/* header */
DECL|member|page
id|s32
id|page
suffix:semicolon
multiline_comment|/* 4: log sequence page number */
DECL|member|rsrvd
id|s16
id|rsrvd
suffix:semicolon
multiline_comment|/* 2: */
DECL|member|eor
id|s16
id|eor
suffix:semicolon
multiline_comment|/* 2: end-of-log offset of lasrt record write */
DECL|member|h
)brace
id|h
suffix:semicolon
DECL|member|data
id|s32
id|data
(braket
id|LOGPSIZE
op_div
l_int|4
op_minus
l_int|4
)braket
suffix:semicolon
multiline_comment|/* log record area */
r_struct
(brace
multiline_comment|/* trailer */
DECL|member|page
id|s32
id|page
suffix:semicolon
multiline_comment|/* 4: normally the same as h.page */
DECL|member|rsrvd
id|s16
id|rsrvd
suffix:semicolon
multiline_comment|/* 2: */
DECL|member|eor
id|s16
id|eor
suffix:semicolon
multiline_comment|/* 2: normally the same as h.eor */
DECL|member|t
)brace
id|t
suffix:semicolon
DECL|typedef|logpage_t
)brace
id|logpage_t
suffix:semicolon
DECL|macro|LOGPHDRSIZE
mdefine_line|#define LOGPHDRSIZE&t;8&t;/* log page header size */
DECL|macro|LOGPTLRSIZE
mdefine_line|#define LOGPTLRSIZE&t;8&t;/* log page trailer size */
multiline_comment|/*&n; *&t;log record&n; *&n; * (this comment should be rewritten !)&n; * jfs uses only &quot;after&quot; log records (only a single writer is allowed&n; * in a  page, pages are written to temporary paging space if&n; * if they must be written to disk before commit, and i/o is&n; * scheduled for modified pages to their home location after&n; * the log records containing the after values and the commit &n; * record is written to the log on disk, undo discards the copy&n; * in main-memory.)&n; *&n; * a log record consists of a data area of variable length followed by &n; * a descriptor of fixed size LOGRDSIZE bytes.&n; * the  data area is rounded up to an integral number of 4-bytes and &n; * must be no longer than LOGPSIZE.&n; * the descriptor is of size of multiple of 4-bytes and aligned on a &n; * 4-byte boundary. &n; * records are packed one after the other in the data area of log pages.&n; * (sometimes a DUMMY record is inserted so that at least one record ends &n; * on every page or the longest record is placed on at most two pages).&n; * the field eor in page header/trailer points to the byte following &n; * the last record on a page.&n; */
multiline_comment|/* log record types */
DECL|macro|LOG_COMMIT
mdefine_line|#define LOG_COMMIT&t;&t;0x8000
DECL|macro|LOG_SYNCPT
mdefine_line|#define LOG_SYNCPT&t;&t;0x4000
DECL|macro|LOG_MOUNT
mdefine_line|#define LOG_MOUNT&t;&t;0x2000
DECL|macro|LOG_REDOPAGE
mdefine_line|#define LOG_REDOPAGE&t;&t;0x0800
DECL|macro|LOG_NOREDOPAGE
mdefine_line|#define LOG_NOREDOPAGE&t;&t;0x0080
DECL|macro|LOG_NOREDOINOEXT
mdefine_line|#define LOG_NOREDOINOEXT&t;0x0040
DECL|macro|LOG_UPDATEMAP
mdefine_line|#define LOG_UPDATEMAP&t;&t;0x0008
DECL|macro|LOG_NOREDOFILE
mdefine_line|#define LOG_NOREDOFILE&t;&t;0x0001
multiline_comment|/* REDOPAGE/NOREDOPAGE log record data type */
DECL|macro|LOG_INODE
mdefine_line|#define&t;LOG_INODE&t;&t;0x0001
DECL|macro|LOG_XTREE
mdefine_line|#define&t;LOG_XTREE&t;&t;0x0002
DECL|macro|LOG_DTREE
mdefine_line|#define&t;LOG_DTREE&t;&t;0x0004
DECL|macro|LOG_BTROOT
mdefine_line|#define&t;LOG_BTROOT&t;&t;0x0010
DECL|macro|LOG_EA
mdefine_line|#define&t;LOG_EA&t;&t;&t;0x0020
DECL|macro|LOG_ACL
mdefine_line|#define&t;LOG_ACL&t;&t;&t;0x0040
DECL|macro|LOG_DATA
mdefine_line|#define&t;LOG_DATA&t;&t;0x0080
DECL|macro|LOG_NEW
mdefine_line|#define&t;LOG_NEW&t;&t;&t;0x0100
DECL|macro|LOG_EXTEND
mdefine_line|#define&t;LOG_EXTEND&t;&t;0x0200
DECL|macro|LOG_RELOCATE
mdefine_line|#define LOG_RELOCATE&t;&t;0x0400
DECL|macro|LOG_DIR_XTREE
mdefine_line|#define LOG_DIR_XTREE&t;&t;0x0800&t;/* Xtree is in directory inode */
multiline_comment|/* UPDATEMAP log record descriptor type */
DECL|macro|LOG_ALLOCXADLIST
mdefine_line|#define&t;LOG_ALLOCXADLIST&t;0x0080
DECL|macro|LOG_ALLOCPXDLIST
mdefine_line|#define&t;LOG_ALLOCPXDLIST&t;0x0040
DECL|macro|LOG_ALLOCXAD
mdefine_line|#define&t;LOG_ALLOCXAD&t;&t;0x0020
DECL|macro|LOG_ALLOCPXD
mdefine_line|#define&t;LOG_ALLOCPXD&t;&t;0x0010
DECL|macro|LOG_FREEXADLIST
mdefine_line|#define&t;LOG_FREEXADLIST&t;&t;0x0008
DECL|macro|LOG_FREEPXDLIST
mdefine_line|#define&t;LOG_FREEPXDLIST&t;&t;0x0004
DECL|macro|LOG_FREEXAD
mdefine_line|#define&t;LOG_FREEXAD&t;&t;0x0002
DECL|macro|LOG_FREEPXD
mdefine_line|#define&t;LOG_FREEPXD&t;&t;0x0001
DECL|struct|lrd
r_typedef
r_struct
id|lrd
(brace
multiline_comment|/*&n;&t; * type independent area&n;&t; */
DECL|member|logtid
id|s32
id|logtid
suffix:semicolon
multiline_comment|/* 4: log transaction identifier */
DECL|member|backchain
id|s32
id|backchain
suffix:semicolon
multiline_comment|/* 4: ptr to prev record of same transaction */
DECL|member|type
id|u16
id|type
suffix:semicolon
multiline_comment|/* 2: record type */
DECL|member|length
id|s16
id|length
suffix:semicolon
multiline_comment|/* 2: length of data in record (in byte) */
DECL|member|aggregate
id|u32
id|aggregate
suffix:semicolon
multiline_comment|/* 4: file system lv/aggregate */
multiline_comment|/* (16) */
multiline_comment|/*&n;&t; * type dependent area (20)&n;&t; */
r_union
(brace
multiline_comment|/*&n;&t;&t; *      COMMIT: commit&n;&t;&t; *&n;&t;&t; * transaction commit: no type-dependent information;&n;&t;&t; */
multiline_comment|/*&n;&t;&t; *      REDOPAGE: after-image&n;&t;&t; *&n;&t;&t; * apply after-image;&n;&t;&t; *&n;&t;&t; * N.B. REDOPAGE, NOREDOPAGE, and UPDATEMAP must be same format;&n;&t;&t; */
r_struct
(brace
DECL|member|fileset
id|u32
id|fileset
suffix:semicolon
multiline_comment|/* 4: fileset number */
DECL|member|inode
id|u32
id|inode
suffix:semicolon
multiline_comment|/* 4: inode number */
DECL|member|type
id|u16
id|type
suffix:semicolon
multiline_comment|/* 2: REDOPAGE record type */
DECL|member|l2linesize
id|s16
id|l2linesize
suffix:semicolon
multiline_comment|/* 2: log2 of line size */
DECL|member|pxd
id|pxd_t
id|pxd
suffix:semicolon
multiline_comment|/* 8: on-disk page pxd */
DECL|member|redopage
)brace
id|redopage
suffix:semicolon
multiline_comment|/* (20) */
multiline_comment|/*&n;&t;&t; *      NOREDOPAGE: the page is freed&n;&t;&t; *&n;&t;&t; * do not apply after-image records which precede this record&n;&t;&t; * in the log with the same page block number to this page.&n;&t;&t; *&n;&t;&t; * N.B. REDOPAGE, NOREDOPAGE, and UPDATEMAP must be same format;&n;&t;&t; */
r_struct
(brace
DECL|member|fileset
id|s32
id|fileset
suffix:semicolon
multiline_comment|/* 4: fileset number */
DECL|member|inode
id|u32
id|inode
suffix:semicolon
multiline_comment|/* 4: inode number */
DECL|member|type
id|u16
id|type
suffix:semicolon
multiline_comment|/* 2: NOREDOPAGE record type */
DECL|member|rsrvd
id|s16
id|rsrvd
suffix:semicolon
multiline_comment|/* 2: reserved */
DECL|member|pxd
id|pxd_t
id|pxd
suffix:semicolon
multiline_comment|/* 8: on-disk page pxd */
DECL|member|noredopage
)brace
id|noredopage
suffix:semicolon
multiline_comment|/* (20) */
multiline_comment|/*&n;&t;&t; *      UPDATEMAP: update block allocation map&n;&t;&t; *&n;&t;&t; * either in-line PXD,&n;&t;&t; * or     out-of-line  XADLIST;&n;&t;&t; *&n;&t;&t; * N.B. REDOPAGE, NOREDOPAGE, and UPDATEMAP must be same format;&n;&t;&t; */
r_struct
(brace
DECL|member|fileset
id|u32
id|fileset
suffix:semicolon
multiline_comment|/* 4: fileset number */
DECL|member|inode
id|u32
id|inode
suffix:semicolon
multiline_comment|/* 4: inode number */
DECL|member|type
id|u16
id|type
suffix:semicolon
multiline_comment|/* 2: UPDATEMAP record type */
DECL|member|nxd
id|s16
id|nxd
suffix:semicolon
multiline_comment|/* 2: number of extents */
DECL|member|pxd
id|pxd_t
id|pxd
suffix:semicolon
multiline_comment|/* 8: pxd */
DECL|member|updatemap
)brace
id|updatemap
suffix:semicolon
multiline_comment|/* (20) */
multiline_comment|/*&n;&t;&t; *      NOREDOINOEXT: the inode extent is freed&n;&t;&t; *&n;&t;&t; * do not apply after-image records which precede this &n;&t;&t; * record in the log with the any of the 4 page block &n;&t;&t; * numbers in this inode extent. &n;&t;&t; * &n;&t;&t; * NOTE: The fileset and pxd fields MUST remain in &n;&t;&t; *       the same fields in the REDOPAGE record format.&n;&t;&t; *&n;&t;&t; */
r_struct
(brace
DECL|member|fileset
id|s32
id|fileset
suffix:semicolon
multiline_comment|/* 4: fileset number */
DECL|member|iagnum
id|s32
id|iagnum
suffix:semicolon
multiline_comment|/* 4: IAG number     */
DECL|member|inoext_idx
id|s32
id|inoext_idx
suffix:semicolon
multiline_comment|/* 4: inode extent index */
DECL|member|pxd
id|pxd_t
id|pxd
suffix:semicolon
multiline_comment|/* 8: on-disk page pxd */
DECL|member|noredoinoext
)brace
id|noredoinoext
suffix:semicolon
multiline_comment|/* (20) */
multiline_comment|/*&n;&t;&t; *      SYNCPT: log sync point&n;&t;&t; *&n;&t;&t; * replay log upto syncpt address specified;&n;&t;&t; */
r_struct
(brace
DECL|member|sync
id|s32
id|sync
suffix:semicolon
multiline_comment|/* 4: syncpt address (0 = here) */
DECL|member|syncpt
)brace
id|syncpt
suffix:semicolon
multiline_comment|/*&n;&t;&t; *      MOUNT: file system mount&n;&t;&t; *&n;&t;&t; * file system mount: no type-dependent information;&n;&t;&t; */
multiline_comment|/*&n;&t;&t; *      ? FREEXTENT: free specified extent(s)&n;&t;&t; *&n;&t;&t; * free specified extent(s) from block allocation map&n;&t;&t; * N.B.: nextents should be length of data/sizeof(xad_t)&n;&t;&t; */
r_struct
(brace
DECL|member|type
id|s32
id|type
suffix:semicolon
multiline_comment|/* 4: FREEXTENT record type */
DECL|member|nextent
id|s32
id|nextent
suffix:semicolon
multiline_comment|/* 4: number of extents */
multiline_comment|/* data: PXD or XAD list */
DECL|member|freextent
)brace
id|freextent
suffix:semicolon
multiline_comment|/*&n;&t;&t; *      ? NOREDOFILE: this file is freed&n;&t;&t; *&n;&t;&t; * do not apply records which precede this record in the log&n;&t;&t; * with the same inode number.&n;&t;&t; *&n;&t;&t; * NOREDILE must be the first to be written at commit&n;&t;&t; * (last to be read in logredo()) - it prevents&n;&t;&t; * replay of preceding updates of all preceding generations&n;&t;&t; * of the inumber esp. the on-disk inode itself, &n;&t;&t; * but does NOT prevent&n;&t;&t; * replay of the &n;&t;&t; */
r_struct
(brace
DECL|member|fileset
id|s32
id|fileset
suffix:semicolon
multiline_comment|/* 4: fileset number */
DECL|member|inode
id|u32
id|inode
suffix:semicolon
multiline_comment|/* 4: inode number */
DECL|member|noredofile
)brace
id|noredofile
suffix:semicolon
multiline_comment|/*&n;&t;&t; *      ? NEWPAGE: &n;&t;&t; *&n;&t;&t; * metadata type dependent&n;&t;&t; */
r_struct
(brace
DECL|member|fileset
id|s32
id|fileset
suffix:semicolon
multiline_comment|/* 4: fileset number */
DECL|member|inode
id|u32
id|inode
suffix:semicolon
multiline_comment|/* 4: inode number */
DECL|member|type
id|s32
id|type
suffix:semicolon
multiline_comment|/* 4: NEWPAGE record type */
DECL|member|pxd
id|pxd_t
id|pxd
suffix:semicolon
multiline_comment|/* 8: on-disk page pxd */
DECL|member|newpage
)brace
id|newpage
suffix:semicolon
multiline_comment|/*&n;&t;&t; *      ? DUMMY: filler&n;&t;&t; *&n;&t;&t; * no type-dependent information&n;&t;&t; */
DECL|member|log
)brace
id|log
suffix:semicolon
DECL|typedef|lrd_t
)brace
id|lrd_t
suffix:semicolon
multiline_comment|/* (36) */
DECL|macro|LOGRDSIZE
mdefine_line|#define&t;LOGRDSIZE&t;(sizeof(struct lrd))
multiline_comment|/*&n; *&t;line vector descriptor&n; */
r_typedef
r_struct
(brace
DECL|member|offset
id|s16
id|offset
suffix:semicolon
DECL|member|length
id|s16
id|length
suffix:semicolon
DECL|typedef|lvd_t
)brace
id|lvd_t
suffix:semicolon
multiline_comment|/*&n; *&t;log logical volume&n; */
DECL|struct|jfs_log
r_typedef
r_struct
id|jfs_log
(brace
DECL|member|sb
r_struct
id|super_block
op_star
id|sb
suffix:semicolon
multiline_comment|/* 4: This is used to sync metadata&n;&t;&t;&t;&t; *    before writing syncpt.  Will&n;&t;&t;&t;&t; *    need to be a list if we share&n;&t;&t;&t;&t; *    the log between fs&squot;s&n;&t;&t;&t;&t; */
DECL|member|bdev
r_struct
id|block_device
op_star
id|bdev
suffix:semicolon
multiline_comment|/* 4: log lv pointer */
DECL|member|serial
id|s32
id|serial
suffix:semicolon
multiline_comment|/* 4: log mount serial number */
DECL|member|base
id|s64
id|base
suffix:semicolon
multiline_comment|/* @8: log extent address (inline log ) */
DECL|member|size
r_int
id|size
suffix:semicolon
multiline_comment|/* 4: log size in log page (in page) */
DECL|member|l2bsize
r_int
id|l2bsize
suffix:semicolon
multiline_comment|/* 4: log2 of bsize */
DECL|member|flag
id|uint
id|flag
suffix:semicolon
multiline_comment|/* 4: flag */
DECL|member|state
id|uint
id|state
suffix:semicolon
multiline_comment|/* 4: state */
DECL|member|lbuf_free
r_struct
id|lbuf
op_star
id|lbuf_free
suffix:semicolon
multiline_comment|/* 4: free lbufs */
DECL|member|free_wait
id|wait_queue_head_t
id|free_wait
suffix:semicolon
multiline_comment|/* 4: */
multiline_comment|/* log write */
DECL|member|logtid
r_int
id|logtid
suffix:semicolon
multiline_comment|/* 4: log tid */
DECL|member|page
r_int
id|page
suffix:semicolon
multiline_comment|/* 4: page number of eol page */
DECL|member|eor
r_int
id|eor
suffix:semicolon
multiline_comment|/* 4: eor of last record in eol page */
DECL|member|bp
r_struct
id|lbuf
op_star
id|bp
suffix:semicolon
multiline_comment|/* 4: current log page buffer */
DECL|member|loglock
r_struct
id|semaphore
id|loglock
suffix:semicolon
multiline_comment|/* 4: log write serialization lock */
multiline_comment|/* syncpt */
DECL|member|nextsync
r_int
id|nextsync
suffix:semicolon
multiline_comment|/* 4: bytes to write before next syncpt */
DECL|member|active
r_int
id|active
suffix:semicolon
multiline_comment|/* 4: */
DECL|member|syncbarrier
r_int
id|syncbarrier
suffix:semicolon
multiline_comment|/* 4: */
DECL|member|syncwait
id|wait_queue_head_t
id|syncwait
suffix:semicolon
multiline_comment|/* 4: */
multiline_comment|/* commit */
DECL|member|cflag
id|uint
id|cflag
suffix:semicolon
multiline_comment|/* 4: */
r_struct
(brace
multiline_comment|/* 8: FIFO commit queue header */
DECL|member|head
r_struct
id|tblock
op_star
id|head
suffix:semicolon
DECL|member|tail
r_struct
id|tblock
op_star
id|tail
suffix:semicolon
DECL|member|cqueue
)brace
id|cqueue
suffix:semicolon
DECL|member|gcrtc
r_int
id|gcrtc
suffix:semicolon
multiline_comment|/* 4: GC_READY transaction count */
DECL|member|gclrt
r_struct
id|tblock
op_star
id|gclrt
suffix:semicolon
multiline_comment|/* 4: latest GC_READY transaction */
DECL|member|gclock
id|spinlock_t
id|gclock
suffix:semicolon
multiline_comment|/* 4: group commit lock */
DECL|member|logsize
r_int
id|logsize
suffix:semicolon
multiline_comment|/* 4: log data area size in byte */
DECL|member|lsn
r_int
id|lsn
suffix:semicolon
multiline_comment|/* 4: end-of-log */
DECL|member|clsn
r_int
id|clsn
suffix:semicolon
multiline_comment|/* 4: clsn */
DECL|member|syncpt
r_int
id|syncpt
suffix:semicolon
multiline_comment|/* 4: addr of last syncpt record */
DECL|member|sync
r_int
id|sync
suffix:semicolon
multiline_comment|/* 4: addr from last logsync() */
DECL|member|synclist
r_struct
id|list_head
id|synclist
suffix:semicolon
multiline_comment|/* 8: logsynclist anchor */
DECL|member|synclock
id|spinlock_t
id|synclock
suffix:semicolon
multiline_comment|/* 4: synclist lock */
DECL|member|wqueue
r_struct
id|lbuf
op_star
id|wqueue
suffix:semicolon
multiline_comment|/* 4: log pageout queue */
DECL|member|count
r_int
id|count
suffix:semicolon
multiline_comment|/* 4: count */
DECL|member|uuid
r_char
id|uuid
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* 16: 128-bit uuid of log device */
DECL|typedef|log_t
)brace
id|log_t
suffix:semicolon
multiline_comment|/*&n; * group commit flag&n; */
multiline_comment|/* log_t */
DECL|macro|logGC_PAGEOUT
mdefine_line|#define logGC_PAGEOUT&t;0x00000001
multiline_comment|/* tblock_t/lbuf_t */
DECL|macro|tblkGC_QUEUE
mdefine_line|#define tblkGC_QUEUE&t;&t;0x0001
DECL|macro|tblkGC_READY
mdefine_line|#define tblkGC_READY&t;&t;0x0002
DECL|macro|tblkGC_COMMIT
mdefine_line|#define tblkGC_COMMIT&t;&t;0x0004
DECL|macro|tblkGC_COMMITTED
mdefine_line|#define tblkGC_COMMITTED&t;0x0008
DECL|macro|tblkGC_EOP
mdefine_line|#define tblkGC_EOP&t;&t;0x0010
DECL|macro|tblkGC_FREE
mdefine_line|#define tblkGC_FREE&t;&t;0x0020
DECL|macro|tblkGC_LEADER
mdefine_line|#define tblkGC_LEADER&t;&t;0x0040
DECL|macro|tblkGC_ERROR
mdefine_line|#define tblkGC_ERROR&t;&t;0x0080
DECL|macro|tblkGC_LAZY
mdefine_line|#define tblkGC_LAZY&t;&t;0x0100&t;
singleline_comment|// D230860
DECL|macro|tblkGC_UNLOCKED
mdefine_line|#define tblkGC_UNLOCKED&t;&t;0x0200&t;
singleline_comment|// D230860
multiline_comment|/*&n; *&t;&t;log cache buffer header&n; */
DECL|struct|lbuf
r_typedef
r_struct
id|lbuf
(brace
DECL|member|l_log
id|log_t
op_star
id|l_log
suffix:semicolon
multiline_comment|/* 4: log associated with buffer */
multiline_comment|/*&n;&t; * data buffer base area&n;&t; */
DECL|member|l_flag
id|uint
id|l_flag
suffix:semicolon
multiline_comment|/* 4: pageout control flags */
DECL|member|l_wqnext
r_struct
id|lbuf
op_star
id|l_wqnext
suffix:semicolon
multiline_comment|/* 4: write queue link */
DECL|member|l_freelist
r_struct
id|lbuf
op_star
id|l_freelist
suffix:semicolon
multiline_comment|/* 4: freelistlink */
DECL|member|l_pn
r_int
id|l_pn
suffix:semicolon
multiline_comment|/* 4: log page number */
DECL|member|l_eor
r_int
id|l_eor
suffix:semicolon
multiline_comment|/* 4: log record eor */
DECL|member|l_ceor
r_int
id|l_ceor
suffix:semicolon
multiline_comment|/* 4: committed log record eor */
DECL|member|l_blkno
id|s64
id|l_blkno
suffix:semicolon
multiline_comment|/* 8: log page block number */
DECL|member|l_ldata
id|caddr_t
id|l_ldata
suffix:semicolon
multiline_comment|/* 4: data page */
DECL|member|l_ioevent
id|wait_queue_head_t
id|l_ioevent
suffix:semicolon
multiline_comment|/* 4: i/o done event */
DECL|member|l_page
r_struct
id|page
op_star
id|l_page
suffix:semicolon
multiline_comment|/* The page itself */
DECL|typedef|lbuf_t
)brace
id|lbuf_t
suffix:semicolon
multiline_comment|/* Reuse l_freelist for redrive list */
DECL|macro|l_redrive_next
mdefine_line|#define l_redrive_next l_freelist
multiline_comment|/*&n; *&t;logsynclist block&n; *&n; * common logsyncblk prefix for jbuf_t and tblock_t&n; */
DECL|struct|logsyncblk
r_typedef
r_struct
id|logsyncblk
(brace
DECL|member|xflag
id|u16
id|xflag
suffix:semicolon
multiline_comment|/* flags */
DECL|member|flag
id|u16
id|flag
suffix:semicolon
multiline_comment|/* only meaninful in tblock_t */
DECL|member|lid
id|lid_t
id|lid
suffix:semicolon
multiline_comment|/* lock id */
DECL|member|lsn
id|s32
id|lsn
suffix:semicolon
multiline_comment|/* log sequence number */
DECL|member|synclist
r_struct
id|list_head
id|synclist
suffix:semicolon
multiline_comment|/* log sync list link */
DECL|typedef|logsyncblk_t
)brace
id|logsyncblk_t
suffix:semicolon
multiline_comment|/*&n; *&t;logsynclist serialization (per log)&n; */
DECL|macro|LOGSYNC_LOCK_INIT
mdefine_line|#define LOGSYNC_LOCK_INIT(log) spin_lock_init(&amp;(log)-&gt;synclock)
DECL|macro|LOGSYNC_LOCK
mdefine_line|#define LOGSYNC_LOCK(log) spin_lock(&amp;(log)-&gt;synclock)
DECL|macro|LOGSYNC_UNLOCK
mdefine_line|#define LOGSYNC_UNLOCK(log) spin_unlock(&amp;(log)-&gt;synclock)
multiline_comment|/* compute the difference in bytes of lsn from sync point */
DECL|macro|logdiff
mdefine_line|#define logdiff(diff, lsn, log)&bslash;&n;{&bslash;&n;&t;diff = (lsn) - (log)-&gt;syncpt;&bslash;&n;&t;if (diff &lt; 0)&bslash;&n;&t;&t;diff += (log)-&gt;logsize;&bslash;&n;}
r_extern
r_int
id|lmLogOpen
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
id|log_t
op_star
op_star
id|log
)paren
suffix:semicolon
r_extern
r_void
id|lmLogWait
c_func
(paren
id|log_t
op_star
id|log
)paren
suffix:semicolon
r_extern
r_int
id|lmLogClose
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
id|log_t
op_star
id|log
)paren
suffix:semicolon
r_extern
r_int
id|lmLogSync
c_func
(paren
id|log_t
op_star
id|log
comma
r_int
id|nosyncwait
)paren
suffix:semicolon
r_extern
r_int
id|lmLogQuiesce
c_func
(paren
id|log_t
op_star
id|log
)paren
suffix:semicolon
r_extern
r_int
id|lmLogResume
c_func
(paren
id|log_t
op_star
id|log
comma
r_struct
id|super_block
op_star
id|sb
)paren
suffix:semicolon
r_extern
r_int
id|lmLogFormat
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
id|s64
id|logAddress
comma
r_int
id|logSize
)paren
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* _H_JFS_LOGMGR */
eof
