multiline_comment|/*&n; *&n; *&n; * Copyright (c) 2000-2002 Silicon Graphics, Inc.  All Rights Reserved.&n; * &n; * This program is free software; you can redistribute it and/or modify it &n; * under the terms of version 2 of the GNU General Public License &n; * as published by the Free Software Foundation.&n; * &n; * This program is distributed in the hope that it would be useful, but &n; * WITHOUT ANY WARRANTY; without even the implied warranty of &n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. &n; * &n; * Further, this software is distributed without any warranty that it is &n; * free of the rightful claim of any third person regarding infringement &n; * or the like.  Any license provided herein, whether implied or &n; * otherwise, applies only to this software file.  Patent licenses, if &n; * any, provided herein do not apply to combinations of this program with &n; * other software, or any other product whatsoever.&n; * &n; * You should have received a copy of the GNU General Public &n; * License along with this program; if not, write the Free Software &n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; * &n; * Contact information:  Silicon Graphics, Inc., 1600 Amphitheatre Pkwy, &n; * Mountain View, CA  94043, or:&n; * &n; * http://www.sgi.com &n; * &n; * For further information regarding this notice, see: &n; * &n; * http://oss.sgi.com/projects/GenInfo/NoticeExplan&n; */
macro_line|#ifndef _ASM_IA64_SN_BTE_H
DECL|macro|_ASM_IA64_SN_BTE_H
mdefine_line|#define _ASM_IA64_SN_BTE_H
macro_line|#ident &quot;$Revision: 1.1 $&quot;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/cache.h&gt;
macro_line|#include &lt;asm/sn/io.h&gt;
multiline_comment|/* BTE status register only supports 16 bits for length field */
DECL|macro|BTE_LEN_BITS
mdefine_line|#define BTE_LEN_BITS (16)
DECL|macro|BTE_LEN_MASK
mdefine_line|#define BTE_LEN_MASK ((1 &lt;&lt; BTE_LEN_BITS) - 1)
DECL|macro|BTE_MAX_XFER
mdefine_line|#define BTE_MAX_XFER ((1 &lt;&lt; BTE_LEN_BITS) * L1_CACHE_BYTES)
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
DECL|member|ideal_xfr_tmo
id|u64
id|ideal_xfr_tmo
suffix:semicolon
multiline_comment|/* Time out */
DECL|member|ideal_xfr_tmo_cnt
id|u64
id|ideal_xfr_tmo_cnt
suffix:semicolon
multiline_comment|/* u64 most_recent_src;&n;&t; * u64 most_recent_dest;&n;&t; * u64 most_recent_len;&n;&t; * u64 most_recent_mode; */
DECL|member|most_rcnt_na
id|u64
r_volatile
op_star
id|most_rcnt_na
suffix:semicolon
DECL|member|bte_test_buf
r_void
op_star
id|bte_test_buf
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
r_void
id|bte_reset_nasid
c_func
(paren
id|nasid_t
)paren
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* _ASM_IA64_SN_BTE_H */
eof
