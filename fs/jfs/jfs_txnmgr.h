multiline_comment|/*&n; *   Copyright (c) International Business Machines  Corp., 2000&n; *&n; *   This program is free software;  you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or &n; *   (at your option) any later version.&n; * &n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY;  without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See&n; *   the GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program;  if not, write to the Free Software &n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; */
multiline_comment|/*&n; * Change History :&n; *&n; */
macro_line|#ifndef _H_JFS_TXNMGR
DECL|macro|_H_JFS_TXNMGR
mdefine_line|#define _H_JFS_TXNMGR
multiline_comment|/*&n; *&t;jfs_txnmgr.h: transaction manager&n; */
macro_line|#include &quot;jfs_logmgr.h&quot;
multiline_comment|/*&n; * Hide implementation of TxBlock and TxLock&n; */
DECL|macro|tid_to_tblock
mdefine_line|#define tid_to_tblock(tid) (&amp;TxBlock[tid])
DECL|macro|lid_to_tlock
mdefine_line|#define lid_to_tlock(lid) (&amp;TxLock[lid])
multiline_comment|/*&n; *&t;transaction block&n; */
DECL|struct|tblock
r_typedef
r_struct
id|tblock
(brace
multiline_comment|/*&n;&t; * tblock_t and jbuf_t common area: struct logsyncblk&n;&t; *&n;&t; * the following 5 fields are the same as struct logsyncblk&n;&t; * which is common to tblock and jbuf to form logsynclist&n;&t; */
DECL|member|xflag
id|u16
id|xflag
suffix:semicolon
multiline_comment|/* tx commit type */
DECL|member|flag
id|u16
id|flag
suffix:semicolon
multiline_comment|/* tx commit state */
DECL|member|dummy
id|lid_t
id|dummy
suffix:semicolon
multiline_comment|/* Must keep structures common */
DECL|member|lsn
id|s32
id|lsn
suffix:semicolon
multiline_comment|/* recovery lsn */
DECL|member|synclist
r_struct
id|list_head
id|synclist
suffix:semicolon
multiline_comment|/* logsynclist link */
multiline_comment|/* lock management */
DECL|member|sb
r_struct
id|super_block
op_star
id|sb
suffix:semicolon
multiline_comment|/* 4: super block */
DECL|member|next
id|lid_t
id|next
suffix:semicolon
multiline_comment|/* 2: index of first tlock of tid */
DECL|member|last
id|lid_t
id|last
suffix:semicolon
multiline_comment|/* 2: index of last tlock of tid */
DECL|member|waitor
id|wait_queue_head_t
id|waitor
suffix:semicolon
multiline_comment|/* 4: tids waiting on this tid */
multiline_comment|/* log management */
DECL|member|logtid
id|u32
id|logtid
suffix:semicolon
multiline_comment|/* 4: log transaction id */
multiline_comment|/* (32) */
multiline_comment|/* commit management */
DECL|member|cqnext
r_struct
id|tblock
op_star
id|cqnext
suffix:semicolon
multiline_comment|/* 4: commit queue link */
DECL|member|clsn
id|s32
id|clsn
suffix:semicolon
multiline_comment|/* 4: commit lsn */
DECL|member|bp
r_struct
id|lbuf
op_star
id|bp
suffix:semicolon
multiline_comment|/* 4: */
DECL|member|pn
id|s32
id|pn
suffix:semicolon
multiline_comment|/* 4: commit record log page number */
DECL|member|eor
id|s32
id|eor
suffix:semicolon
multiline_comment|/* 4: commit record eor */
DECL|member|gcwait
id|wait_queue_head_t
id|gcwait
suffix:semicolon
multiline_comment|/* 4: group commit event list:&n;&t;&t;&t;&t;&t; *    ready transactions wait on this&n;&t;&t;&t;&t;&t; *    event for group commit completion.&n;&t;&t;&t;&t;&t; */
DECL|member|ip
r_struct
id|inode
op_star
id|ip
suffix:semicolon
multiline_comment|/* 4: inode being created or deleted */
DECL|member|rsrvd
id|s32
id|rsrvd
suffix:semicolon
multiline_comment|/* 4: */
DECL|typedef|tblock_t
)brace
id|tblock_t
suffix:semicolon
multiline_comment|/* (64) */
r_extern
r_struct
id|tblock
op_star
id|TxBlock
suffix:semicolon
multiline_comment|/* transaction block table */
multiline_comment|/* commit flags: tblk-&gt;xflag */
DECL|macro|COMMIT_SYNC
mdefine_line|#define&t;COMMIT_SYNC&t;0x0001&t;/* synchronous commit */
DECL|macro|COMMIT_FORCE
mdefine_line|#define&t;COMMIT_FORCE&t;0x0002&t;/* force pageout at end of commit */
DECL|macro|COMMIT_FLUSH
mdefine_line|#define&t;COMMIT_FLUSH&t;0x0004&t;/* init flush at end of commit */
DECL|macro|COMMIT_MAP
mdefine_line|#define COMMIT_MAP&t;0x00f0
DECL|macro|COMMIT_PMAP
mdefine_line|#define&t;COMMIT_PMAP&t;0x0010&t;/* update pmap */
DECL|macro|COMMIT_WMAP
mdefine_line|#define&t;COMMIT_WMAP&t;0x0020&t;/* update wmap */
DECL|macro|COMMIT_PWMAP
mdefine_line|#define&t;COMMIT_PWMAP&t;0x0040&t;/* update pwmap */
DECL|macro|COMMIT_FREE
mdefine_line|#define&t;COMMIT_FREE&t;0x0f00
DECL|macro|COMMIT_DELETE
mdefine_line|#define&t;COMMIT_DELETE&t;0x0100&t;/* inode delete */
DECL|macro|COMMIT_TRUNCATE
mdefine_line|#define&t;COMMIT_TRUNCATE&t;0x0200&t;/* file truncation */
DECL|macro|COMMIT_CREATE
mdefine_line|#define&t;COMMIT_CREATE&t;0x0400&t;/* inode create */
DECL|macro|COMMIT_LAZY
mdefine_line|#define&t;COMMIT_LAZY&t;0x0800&t;/* lazy commit */
DECL|macro|COMMIT_PAGE
mdefine_line|#define COMMIT_PAGE&t;0x1000&t;/* Identifies element as metapage */
DECL|macro|COMMIT_INODE
mdefine_line|#define COMMIT_INODE&t;0x2000&t;/* Identifies element as inode */
multiline_comment|/* group commit flags tblk-&gt;flag: see jfs_logmgr.h */
multiline_comment|/*&n; *&t;transaction lock&n; */
DECL|struct|tlock
r_typedef
r_struct
id|tlock
(brace
DECL|member|next
id|lid_t
id|next
suffix:semicolon
multiline_comment|/* index next lockword on tid locklist&n;&t;&t;&t;&t; *          next lockword on freelist&n;&t;&t;&t;&t; */
DECL|member|tid
id|tid_t
id|tid
suffix:semicolon
multiline_comment|/* transaction id holding lock */
DECL|member|flag
id|u16
id|flag
suffix:semicolon
multiline_comment|/* 2: lock control */
DECL|member|type
id|u16
id|type
suffix:semicolon
multiline_comment|/* 2: log type */
DECL|member|mp
r_struct
id|metapage
op_star
id|mp
suffix:semicolon
multiline_comment|/* 4: object page buffer locked */
DECL|member|ip
r_struct
id|inode
op_star
id|ip
suffix:semicolon
multiline_comment|/* 4: object */
multiline_comment|/* (16) */
DECL|member|lock
id|s16
id|lock
(braket
l_int|24
)braket
suffix:semicolon
multiline_comment|/* 48: overlay area */
DECL|typedef|tlock_t
)brace
id|tlock_t
suffix:semicolon
multiline_comment|/* (64) */
r_extern
r_struct
id|tlock
op_star
id|TxLock
suffix:semicolon
multiline_comment|/* transaction lock table */
multiline_comment|/*&n; * tlock flag&n; */
multiline_comment|/* txLock state */
DECL|macro|tlckPAGELOCK
mdefine_line|#define tlckPAGELOCK&t;&t;0x8000
DECL|macro|tlckINODELOCK
mdefine_line|#define tlckINODELOCK&t;&t;0x4000
DECL|macro|tlckLINELOCK
mdefine_line|#define tlckLINELOCK&t;&t;0x2000
DECL|macro|tlckINLINELOCK
mdefine_line|#define tlckINLINELOCK&t;&t;0x1000
multiline_comment|/* lmLog state */
DECL|macro|tlckLOG
mdefine_line|#define tlckLOG&t;&t;&t;0x0800
multiline_comment|/* updateMap state */
DECL|macro|tlckUPDATEMAP
mdefine_line|#define&t;tlckUPDATEMAP&t;&t;0x0080
multiline_comment|/* freeLock state */
DECL|macro|tlckFREELOCK
mdefine_line|#define tlckFREELOCK&t;&t;0x0008
DECL|macro|tlckWRITEPAGE
mdefine_line|#define tlckWRITEPAGE&t;&t;0x0004
DECL|macro|tlckFREEPAGE
mdefine_line|#define tlckFREEPAGE&t;&t;0x0002
multiline_comment|/*&n; * tlock type&n; */
DECL|macro|tlckTYPE
mdefine_line|#define&t;tlckTYPE&t;&t;0xfe00
DECL|macro|tlckINODE
mdefine_line|#define&t;tlckINODE&t;&t;0x8000
DECL|macro|tlckXTREE
mdefine_line|#define&t;tlckXTREE&t;&t;0x4000
DECL|macro|tlckDTREE
mdefine_line|#define&t;tlckDTREE&t;&t;0x2000
DECL|macro|tlckMAP
mdefine_line|#define&t;tlckMAP&t;&t;&t;0x1000
DECL|macro|tlckEA
mdefine_line|#define&t;tlckEA&t;&t;&t;0x0800
DECL|macro|tlckACL
mdefine_line|#define&t;tlckACL&t;&t;&t;0x0400
DECL|macro|tlckDATA
mdefine_line|#define&t;tlckDATA&t;&t;0x0200
DECL|macro|tlckBTROOT
mdefine_line|#define&t;tlckBTROOT&t;&t;0x0100
DECL|macro|tlckOPERATION
mdefine_line|#define&t;tlckOPERATION&t;&t;0x00ff
DECL|macro|tlckGROW
mdefine_line|#define tlckGROW&t;&t;0x0001&t;/* file grow */
DECL|macro|tlckREMOVE
mdefine_line|#define tlckREMOVE&t;&t;0x0002&t;/* file delete */
DECL|macro|tlckTRUNCATE
mdefine_line|#define tlckTRUNCATE&t;&t;0x0004&t;/* file truncate */
DECL|macro|tlckRELOCATE
mdefine_line|#define tlckRELOCATE&t;&t;0x0008&t;/* file/directory relocate */
DECL|macro|tlckENTRY
mdefine_line|#define tlckENTRY&t;&t;0x0001&t;/* directory insert/delete */
DECL|macro|tlckEXTEND
mdefine_line|#define tlckEXTEND&t;&t;0x0002&t;/* directory extend in-line */
DECL|macro|tlckSPLIT
mdefine_line|#define tlckSPLIT&t;&t;0x0010&t;/* splited page */
DECL|macro|tlckNEW
mdefine_line|#define tlckNEW&t;&t;&t;0x0020&t;/* new page from split */
DECL|macro|tlckFREE
mdefine_line|#define tlckFREE&t;&t;0x0040&t;/* free page */
DECL|macro|tlckRELINK
mdefine_line|#define tlckRELINK&t;&t;0x0080&t;/* update sibling pointer */
multiline_comment|/*&n; *&t;linelock for lmLog()&n; *&n; * note: linelock_t and its variations are overlaid&n; * at tlock.lock: watch for alignment;&n; */
r_typedef
r_struct
(brace
DECL|member|offset
id|u8
id|offset
suffix:semicolon
multiline_comment|/* 1: */
DECL|member|length
id|u8
id|length
suffix:semicolon
multiline_comment|/* 1: */
DECL|typedef|lv_t
)brace
id|lv_t
suffix:semicolon
multiline_comment|/* (2) */
DECL|macro|TLOCKSHORT
mdefine_line|#define&t;TLOCKSHORT&t;20
DECL|macro|TLOCKLONG
mdefine_line|#define&t;TLOCKLONG&t;28
r_typedef
r_struct
(brace
DECL|member|next
id|u16
id|next
suffix:semicolon
multiline_comment|/* 2: next linelock */
DECL|member|maxcnt
id|s8
id|maxcnt
suffix:semicolon
multiline_comment|/* 1: */
DECL|member|index
id|s8
id|index
suffix:semicolon
multiline_comment|/* 1: */
DECL|member|flag
id|u16
id|flag
suffix:semicolon
multiline_comment|/* 2: */
DECL|member|type
id|u8
id|type
suffix:semicolon
multiline_comment|/* 1: */
DECL|member|l2linesize
id|u8
id|l2linesize
suffix:semicolon
multiline_comment|/* 1: log2 of linesize */
multiline_comment|/* (8) */
DECL|member|lv
id|lv_t
id|lv
(braket
l_int|20
)braket
suffix:semicolon
multiline_comment|/* 40: */
DECL|typedef|linelock_t
)brace
id|linelock_t
suffix:semicolon
multiline_comment|/* (48) */
DECL|macro|dtlock_t
mdefine_line|#define dtlock_t&t;linelock_t
DECL|macro|itlock_t
mdefine_line|#define itlock_t&t;linelock_t
r_typedef
r_struct
(brace
DECL|member|next
id|u16
id|next
suffix:semicolon
multiline_comment|/* 2: */
DECL|member|maxcnt
id|s8
id|maxcnt
suffix:semicolon
multiline_comment|/* 1: */
DECL|member|index
id|s8
id|index
suffix:semicolon
multiline_comment|/* 1: */
DECL|member|flag
id|u16
id|flag
suffix:semicolon
multiline_comment|/* 2: */
DECL|member|type
id|u8
id|type
suffix:semicolon
multiline_comment|/* 1: */
DECL|member|l2linesize
id|u8
id|l2linesize
suffix:semicolon
multiline_comment|/* 1: log2 of linesize */
multiline_comment|/* (8) */
DECL|member|header
id|lv_t
id|header
suffix:semicolon
multiline_comment|/* 2: */
DECL|member|lwm
id|lv_t
id|lwm
suffix:semicolon
multiline_comment|/* 2: low water mark */
DECL|member|hwm
id|lv_t
id|hwm
suffix:semicolon
multiline_comment|/* 2: high water mark */
DECL|member|twm
id|lv_t
id|twm
suffix:semicolon
multiline_comment|/* 2: */
multiline_comment|/* (16) */
DECL|member|pxdlock
id|s32
id|pxdlock
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* 32: */
DECL|typedef|xtlock_t
)brace
id|xtlock_t
suffix:semicolon
multiline_comment|/* (48) */
multiline_comment|/*&n; *&t;maplock for txUpdateMap()&n; *&n; * note: maplock_t and its variations are overlaid&n; * at tlock.lock/linelock: watch for alignment;&n; * N.B. next field may be set by linelock, and should not&n; * be modified by maplock;&n; * N.B. index of the first pxdlock specifies index of next &n; * free maplock (i.e., number of maplock) in the tlock; &n; */
r_typedef
r_struct
(brace
DECL|member|next
id|u16
id|next
suffix:semicolon
multiline_comment|/* 2: */
DECL|member|maxcnt
id|u8
id|maxcnt
suffix:semicolon
multiline_comment|/* 2: */
DECL|member|index
id|u8
id|index
suffix:semicolon
multiline_comment|/* 2: next free maplock index */
DECL|member|flag
id|u16
id|flag
suffix:semicolon
multiline_comment|/* 2: */
DECL|member|type
id|u8
id|type
suffix:semicolon
multiline_comment|/* 1: */
DECL|member|count
id|u8
id|count
suffix:semicolon
multiline_comment|/* 1: number of pxd/xad */
multiline_comment|/* (8) */
DECL|member|pxd
id|pxd_t
id|pxd
suffix:semicolon
multiline_comment|/* 8: */
DECL|typedef|maplock_t
)brace
id|maplock_t
suffix:semicolon
multiline_comment|/* (16): */
multiline_comment|/* maplock flag */
DECL|macro|mlckALLOC
mdefine_line|#define&t;mlckALLOC&t;&t;0x00f0
DECL|macro|mlckALLOCXADLIST
mdefine_line|#define&t;mlckALLOCXADLIST&t;0x0080
DECL|macro|mlckALLOCPXDLIST
mdefine_line|#define&t;mlckALLOCPXDLIST&t;0x0040
DECL|macro|mlckALLOCXAD
mdefine_line|#define&t;mlckALLOCXAD&t;&t;0x0020
DECL|macro|mlckALLOCPXD
mdefine_line|#define&t;mlckALLOCPXD&t;&t;0x0010
DECL|macro|mlckFREE
mdefine_line|#define&t;mlckFREE&t;&t;0x000f
DECL|macro|mlckFREEXADLIST
mdefine_line|#define&t;mlckFREEXADLIST&t;&t;0x0008
DECL|macro|mlckFREEPXDLIST
mdefine_line|#define&t;mlckFREEPXDLIST&t;&t;0x0004
DECL|macro|mlckFREEXAD
mdefine_line|#define&t;mlckFREEXAD&t;&t;0x0002
DECL|macro|mlckFREEPXD
mdefine_line|#define&t;mlckFREEPXD&t;&t;0x0001
DECL|macro|pxdlock_t
mdefine_line|#define&t;pxdlock_t&t;maplock_t
r_typedef
r_struct
(brace
DECL|member|next
id|u16
id|next
suffix:semicolon
multiline_comment|/* 2: */
DECL|member|maxcnt
id|u8
id|maxcnt
suffix:semicolon
multiline_comment|/* 2: */
DECL|member|index
id|u8
id|index
suffix:semicolon
multiline_comment|/* 2: */
DECL|member|flag
id|u16
id|flag
suffix:semicolon
multiline_comment|/* 2: */
DECL|member|type
id|u8
id|type
suffix:semicolon
multiline_comment|/* 1: */
DECL|member|count
id|u8
id|count
suffix:semicolon
multiline_comment|/* 1: number of pxd/xad */
multiline_comment|/* (8) */
DECL|member|xdlist
r_void
op_star
id|xdlist
suffix:semicolon
multiline_comment|/* 4: pxd/xad list */
DECL|member|rsrvd
id|s32
id|rsrvd
suffix:semicolon
multiline_comment|/* 4: */
DECL|typedef|xdlistlock_t
)brace
id|xdlistlock_t
suffix:semicolon
multiline_comment|/* (16): */
multiline_comment|/*&n; *&t;commit&n; *&n; * parameter to the commit manager routines&n; */
DECL|struct|commit
r_typedef
r_struct
id|commit
(brace
DECL|member|tid
id|tid_t
id|tid
suffix:semicolon
multiline_comment|/* 4: tid = index of tblock */
DECL|member|flag
r_int
id|flag
suffix:semicolon
multiline_comment|/* 4: flags */
DECL|member|log
id|log_t
op_star
id|log
suffix:semicolon
multiline_comment|/* 4: log */
DECL|member|sb
r_struct
id|super_block
op_star
id|sb
suffix:semicolon
multiline_comment|/* 4: superblock */
DECL|member|nip
r_int
id|nip
suffix:semicolon
multiline_comment|/* 4: number of entries in iplist */
DECL|member|iplist
r_struct
id|inode
op_star
op_star
id|iplist
suffix:semicolon
multiline_comment|/* 4: list of pointers to inodes */
multiline_comment|/* (32) */
multiline_comment|/* log record descriptor on 64-bit boundary */
DECL|member|lrd
id|lrd_t
id|lrd
suffix:semicolon
multiline_comment|/* : log record descriptor */
DECL|typedef|commit_t
)brace
id|commit_t
suffix:semicolon
multiline_comment|/*&n; * external declarations&n; */
r_extern
id|tlock_t
op_star
id|txLock
c_func
(paren
id|tid_t
id|tid
comma
r_struct
id|inode
op_star
id|ip
comma
r_struct
id|metapage
op_star
id|mp
comma
r_int
id|flag
)paren
suffix:semicolon
r_extern
id|tlock_t
op_star
id|txMaplock
c_func
(paren
id|tid_t
id|tid
comma
r_struct
id|inode
op_star
id|ip
comma
r_int
id|flag
)paren
suffix:semicolon
r_extern
r_int
id|txCommit
c_func
(paren
id|tid_t
id|tid
comma
r_int
id|nip
comma
r_struct
id|inode
op_star
op_star
id|iplist
comma
r_int
id|flag
)paren
suffix:semicolon
r_extern
id|tid_t
id|txBegin
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|flag
)paren
suffix:semicolon
r_extern
r_void
id|txBeginAnon
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
suffix:semicolon
r_extern
r_void
id|txEnd
c_func
(paren
id|tid_t
id|tid
)paren
suffix:semicolon
r_extern
r_void
id|txAbort
c_func
(paren
id|tid_t
id|tid
comma
r_int
id|dirty
)paren
suffix:semicolon
r_extern
id|linelock_t
op_star
id|txLinelock
c_func
(paren
id|linelock_t
op_star
id|tlock
)paren
suffix:semicolon
r_extern
r_void
id|txFreeMap
c_func
(paren
r_struct
id|inode
op_star
id|ip
comma
id|maplock_t
op_star
id|maplock
comma
id|tblock_t
op_star
id|tblk
comma
r_int
id|maptype
)paren
suffix:semicolon
r_extern
r_void
id|txEA
c_func
(paren
id|tid_t
id|tid
comma
r_struct
id|inode
op_star
id|ip
comma
id|dxd_t
op_star
id|oldea
comma
id|dxd_t
op_star
id|newea
)paren
suffix:semicolon
r_extern
r_void
id|txFreelock
c_func
(paren
r_struct
id|inode
op_star
id|ip
)paren
suffix:semicolon
r_extern
r_int
id|lmLog
c_func
(paren
id|log_t
op_star
id|log
comma
id|tblock_t
op_star
id|tblk
comma
id|lrd_t
op_star
id|lrd
comma
id|tlock_t
op_star
id|tlck
)paren
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* _H_JFS_TXNMGR */
eof
