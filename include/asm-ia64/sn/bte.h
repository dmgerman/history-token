multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; * &n; * Copyright (c) 2001-2002 Silicon Graphics, Inc.  All rights reserved.&n; */
macro_line|#ifndef _ASM_IA64_SN_BTE_H
DECL|macro|_ASM_IA64_SN_BTE_H
mdefine_line|#define _ASM_IA64_SN_BTE_H
macro_line|#ident &quot;$Revision: $&quot;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/cache.h&gt;
macro_line|#include &lt;asm/sn/io.h&gt;
DECL|macro|L1_CACHE_MASK
mdefine_line|#define L1_CACHE_MASK (L1_CACHE_BYTES - 1)&t;/* Mask to retrieve&n;&t;&t;&t;&t;&t;&t; * the offset into this&n;&t;&t;&t;&t;&t;&t; * cache line.*/
multiline_comment|/* BTE status register only supports 16 bits for length field */
DECL|macro|BTE_LEN_MASK
mdefine_line|#define BTE_LEN_MASK ((1 &lt;&lt; 16) - 1)
multiline_comment|/*&n; * Constants used in determining the best and worst case transfer&n; * times. To help explain the two, the following graph of transfer&n; * status vs time may help.&n; *&n; *     active +------------------:-+  :&n; *  status    |                  : |  :&n; *       idle +__________________:_+=======&n; *            0 Time           MaxT  MinT&n; *&n; *  Therefore, MaxT is the maximum thoeretical rate for transfering&n; *  the request block (assuming ideal circumstances)&n; *&n; *  MinT is the minimum theoretical rate for transferring the&n; *  requested block (assuming maximum link distance and contention)&n; *&n; *  The following defines are the inverse of the above.  They are&n; *  used for calculating the MaxT time and MinT time given the &n; *  number of lines in the transfer.&n; */
DECL|macro|BTE_MAXT_LINES_PER_SECOND
mdefine_line|#define BTE_MAXT_LINES_PER_SECOND 800
DECL|macro|BTE_MINT_LINES_PER_SECOND
mdefine_line|#define BTE_MINT_LINES_PER_SECOND 600
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
multiline_comment|/*&n; * Structure defining a bte.  An instance of this&n; * structure is created in the nodepda for each&n; * bte on that node (as defined by BTES_PER_NODE)&n; * This structure contains everything necessary&n; * to work with a BTE.&n; */
DECL|struct|bteinfo_s
r_typedef
r_struct
id|bteinfo_s
(brace
DECL|member|____cacheline_aligned
id|u64
r_volatile
id|notify
id|____cacheline_aligned
suffix:semicolon
DECL|member|____cacheline_aligned
r_char
op_star
id|bte_base_addr
id|____cacheline_aligned
suffix:semicolon
DECL|member|spinlock
id|spinlock_t
id|spinlock
suffix:semicolon
DECL|member|idealTransferTimeout
id|u64
id|idealTransferTimeout
suffix:semicolon
DECL|member|idealTransferTimeoutReached
id|u64
id|idealTransferTimeoutReached
suffix:semicolon
DECL|member|mostRecentSrc
id|u64
id|mostRecentSrc
suffix:semicolon
DECL|member|mostRecentDest
id|u64
id|mostRecentDest
suffix:semicolon
DECL|member|mostRecentLen
id|u64
id|mostRecentLen
suffix:semicolon
DECL|member|mostRecentMode
id|u64
id|mostRecentMode
suffix:semicolon
DECL|member|mostRecentNotification
id|u64
r_volatile
op_star
id|mostRecentNotification
suffix:semicolon
DECL|typedef|bteinfo_t
)brace
id|bteinfo_t
suffix:semicolon
multiline_comment|/* Possible results from bte_copy and bte_unaligned_copy */
r_typedef
r_enum
(brace
DECL|enumerator|BTE_SUCCESS
id|BTE_SUCCESS
comma
multiline_comment|/* 0 is success */
DECL|enumerator|BTEFAIL_NOTAVAIL
id|BTEFAIL_NOTAVAIL
comma
multiline_comment|/* BTE not available */
DECL|enumerator|BTEFAIL_ERROR
id|BTEFAIL_ERROR
comma
multiline_comment|/* Generic error */
DECL|enumerator|BTEFAIL_DIR
id|BTEFAIL_DIR
multiline_comment|/* Diretory error */
DECL|typedef|bte_result_t
)brace
id|bte_result_t
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* _ASM_IA64_SN_BTE_H */
eof
