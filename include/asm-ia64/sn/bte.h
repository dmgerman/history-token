multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (c) 2000-2004 Silicon Graphics, Inc.  All Rights Reserved.&n; */
macro_line|#ifndef _ASM_IA64_SN_BTE_H
DECL|macro|_ASM_IA64_SN_BTE_H
mdefine_line|#define _ASM_IA64_SN_BTE_H
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/cache.h&gt;
macro_line|#include &lt;asm/sn/types.h&gt;
multiline_comment|/* #define BTE_DEBUG */
multiline_comment|/* #define BTE_DEBUG_VERBOSE */
macro_line|#ifdef BTE_DEBUG
DECL|macro|BTE_PRINTK
macro_line|#  define BTE_PRINTK(x) printk x&t;/* Terse */
macro_line|#  ifdef BTE_DEBUG_VERBOSE
DECL|macro|BTE_PRINTKV
macro_line|#    define BTE_PRINTKV(x) printk x&t;/* Verbose */
macro_line|#  else
DECL|macro|BTE_PRINTKV
macro_line|#    define BTE_PRINTKV(x)
macro_line|#  endif /* BTE_DEBUG_VERBOSE */
macro_line|#else
DECL|macro|BTE_PRINTK
macro_line|#  define BTE_PRINTK(x)
DECL|macro|BTE_PRINTKV
macro_line|#  define BTE_PRINTKV(x)
macro_line|#endif&t;/* BTE_DEBUG */
multiline_comment|/* BTE status register only supports 16 bits for length field */
DECL|macro|BTE_LEN_BITS
mdefine_line|#define BTE_LEN_BITS (16)
DECL|macro|BTE_LEN_MASK
mdefine_line|#define BTE_LEN_MASK ((1 &lt;&lt; BTE_LEN_BITS) - 1)
DECL|macro|BTE_MAX_XFER
mdefine_line|#define BTE_MAX_XFER ((1 &lt;&lt; BTE_LEN_BITS) * L1_CACHE_BYTES)
multiline_comment|/* Define hardware */
DECL|macro|BTES_PER_NODE
mdefine_line|#define BTES_PER_NODE 2
multiline_comment|/* Define hardware modes */
DECL|macro|BTE_NOTIFY
mdefine_line|#define BTE_NOTIFY (IBCT_NOTIFY)
DECL|macro|BTE_NORMAL
mdefine_line|#define BTE_NORMAL BTE_NOTIFY
DECL|macro|BTE_ZERO_FILL
mdefine_line|#define BTE_ZERO_FILL (BTE_NOTIFY | IBCT_ZFIL_MODE)
multiline_comment|/* Use a reserved bit to let the caller specify a wait for any BTE */
DECL|macro|BTE_WACQUIRE
mdefine_line|#define BTE_WACQUIRE (0x4000)
multiline_comment|/* Use the BTE on the node with the destination memory */
DECL|macro|BTE_USE_DEST
mdefine_line|#define BTE_USE_DEST (BTE_WACQUIRE &lt;&lt; 1)
multiline_comment|/* Use any available BTE interface on any node for the transfer */
DECL|macro|BTE_USE_ANY
mdefine_line|#define BTE_USE_ANY (BTE_USE_DEST &lt;&lt; 1)
multiline_comment|/* macro to force the IBCT0 value valid */
DECL|macro|BTE_VALID_MODE
mdefine_line|#define BTE_VALID_MODE(x) ((x) &amp; (IBCT_NOTIFY | IBCT_ZFIL_MODE))
DECL|macro|BTE_ACTIVE
mdefine_line|#define BTE_ACTIVE&t;&t;(IBLS_BUSY | IBLS_ERROR)
DECL|macro|BTE_WORD_AVAILABLE
mdefine_line|#define BTE_WORD_AVAILABLE&t;(IBLS_BUSY &lt;&lt; 1)
DECL|macro|BTE_WORD_BUSY
mdefine_line|#define BTE_WORD_BUSY&t;&t;(~BTE_WORD_AVAILABLE)
multiline_comment|/*&n; * Some macros to simplify reading.&n; * Start with macros to locate the BTE control registers.&n; */
DECL|macro|BTE_LNSTAT_LOAD
mdefine_line|#define BTE_LNSTAT_LOAD(_bte)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;HUB_L(_bte-&gt;bte_base_addr)
DECL|macro|BTE_LNSTAT_STORE
mdefine_line|#define BTE_LNSTAT_STORE(_bte, _x)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;HUB_S(_bte-&gt;bte_base_addr, (_x))
DECL|macro|BTE_SRC_STORE
mdefine_line|#define BTE_SRC_STORE(_bte, _x)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;HUB_S(_bte-&gt;bte_base_addr + (BTEOFF_SRC/8), (_x))
DECL|macro|BTE_DEST_STORE
mdefine_line|#define BTE_DEST_STORE(_bte, _x)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;HUB_S(_bte-&gt;bte_base_addr + (BTEOFF_DEST/8), (_x))
DECL|macro|BTE_CTRL_STORE
mdefine_line|#define BTE_CTRL_STORE(_bte, _x)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;HUB_S(_bte-&gt;bte_base_addr + (BTEOFF_CTRL/8), (_x))
DECL|macro|BTE_NOTIF_STORE
mdefine_line|#define BTE_NOTIF_STORE(_bte, _x)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;HUB_S(_bte-&gt;bte_base_addr + (BTEOFF_NOTIFY/8), (_x))
multiline_comment|/* Possible results from bte_copy and bte_unaligned_copy */
multiline_comment|/* The following error codes map into the BTE hardware codes&n; * IIO_ICRB_ECODE_* (in shubio.h). The hardware uses&n; * an error code of 0 (IIO_ICRB_ECODE_DERR), but we want zero&n; * to mean BTE_SUCCESS, so add one (BTEFAIL_OFFSET) to the error&n; * codes to give the following error codes.&n; */
DECL|macro|BTEFAIL_OFFSET
mdefine_line|#define BTEFAIL_OFFSET&t;1
r_typedef
r_enum
(brace
DECL|enumerator|BTE_SUCCESS
id|BTE_SUCCESS
comma
multiline_comment|/* 0 is success */
DECL|enumerator|BTEFAIL_DIR
id|BTEFAIL_DIR
comma
multiline_comment|/* Directory error due to IIO access*/
DECL|enumerator|BTEFAIL_POISON
id|BTEFAIL_POISON
comma
multiline_comment|/* poison error on IO access (write to poison page) */
DECL|enumerator|BTEFAIL_WERR
id|BTEFAIL_WERR
comma
multiline_comment|/* Write error (ie WINV to a Read only line) */
DECL|enumerator|BTEFAIL_ACCESS
id|BTEFAIL_ACCESS
comma
multiline_comment|/* access error (protection violation) */
DECL|enumerator|BTEFAIL_PWERR
id|BTEFAIL_PWERR
comma
multiline_comment|/* Partial Write Error */
DECL|enumerator|BTEFAIL_PRERR
id|BTEFAIL_PRERR
comma
multiline_comment|/* Partial Read Error */
DECL|enumerator|BTEFAIL_TOUT
id|BTEFAIL_TOUT
comma
multiline_comment|/* CRB Time out */
DECL|enumerator|BTEFAIL_XTERR
id|BTEFAIL_XTERR
comma
multiline_comment|/* Incoming xtalk pkt had error bit */
DECL|enumerator|BTEFAIL_NOTAVAIL
id|BTEFAIL_NOTAVAIL
comma
multiline_comment|/* BTE not available */
DECL|typedef|bte_result_t
)brace
id|bte_result_t
suffix:semicolon
multiline_comment|/*&n; * Structure defining a bte.  An instance of this&n; * structure is created in the nodepda for each&n; * bte on that node (as defined by BTES_PER_NODE)&n; * This structure contains everything necessary&n; * to work with a BTE.&n; */
DECL|struct|bteinfo_s
r_struct
id|bteinfo_s
(brace
DECL|member|____cacheline_aligned
r_volatile
id|u64
id|notify
id|____cacheline_aligned
suffix:semicolon
DECL|member|____cacheline_aligned
id|u64
op_star
id|bte_base_addr
id|____cacheline_aligned
suffix:semicolon
DECL|member|spinlock
id|spinlock_t
id|spinlock
suffix:semicolon
DECL|member|bte_cnode
id|cnodeid_t
id|bte_cnode
suffix:semicolon
multiline_comment|/* cnode                            */
DECL|member|bte_error_count
r_int
id|bte_error_count
suffix:semicolon
multiline_comment|/* Number of errors encountered     */
DECL|member|bte_num
r_int
id|bte_num
suffix:semicolon
multiline_comment|/* 0 --&gt; BTE0, 1 --&gt; BTE1           */
DECL|member|cleanup_active
r_int
id|cleanup_active
suffix:semicolon
multiline_comment|/* Interface is locked for cleanup  */
DECL|member|bh_error
r_volatile
id|bte_result_t
id|bh_error
suffix:semicolon
multiline_comment|/* error while processing   */
DECL|member|most_rcnt_na
r_volatile
id|u64
op_star
id|most_rcnt_na
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Function prototypes (functions defined in bte.c, used elsewhere)&n; */
r_extern
id|bte_result_t
id|bte_copy
c_func
(paren
id|u64
comma
id|u64
comma
id|u64
comma
id|u64
comma
r_void
op_star
)paren
suffix:semicolon
r_extern
id|bte_result_t
id|bte_unaligned_copy
c_func
(paren
id|u64
comma
id|u64
comma
id|u64
comma
id|u64
)paren
suffix:semicolon
r_extern
r_void
id|bte_error_handler
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
DECL|macro|bte_zero
mdefine_line|#define bte_zero(dest, len, mode, notification) &bslash;&n;&t;bte_copy(0, dest, len, ((mode) | BTE_ZERO_FILL), notification)
multiline_comment|/*&n; * The following is the prefered way of calling bte_unaligned_copy&n; * If the copy is fully cache line aligned, then bte_copy is&n; * used instead.  Since bte_copy is inlined, this saves a call&n; * stack.  NOTE: bte_copy is called synchronously and does block&n; * until the transfer is complete.  In order to get the asynch&n; * version of bte_copy, you must perform this check yourself.&n; */
DECL|macro|BTE_UNALIGNED_COPY
mdefine_line|#define BTE_UNALIGNED_COPY(src, dest, len, mode)                        &bslash;&n;&t;(((len &amp; L1_CACHE_MASK) || (src &amp; L1_CACHE_MASK) ||             &bslash;&n;&t;  (dest &amp; L1_CACHE_MASK)) ?                                     &bslash;&n;&t; bte_unaligned_copy(src, dest, len, mode) :              &t;&bslash;&n;&t; bte_copy(src, dest, len, mode, NULL))
macro_line|#endif&t;/* _ASM_IA64_SN_BTE_H */
eof
