multiline_comment|/*&n; *&n; *&n; * Copyright (c) 2000-2003 Silicon Graphics, Inc.  All Rights Reserved.&n; * &n; * This program is free software; you can redistribute it and/or modify it &n; * under the terms of version 2 of the GNU General Public License &n; * as published by the Free Software Foundation.&n; * &n; * This program is distributed in the hope that it would be useful, but &n; * WITHOUT ANY WARRANTY; without even the implied warranty of &n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. &n; * &n; * Further, this software is distributed without any warranty that it is &n; * free of the rightful claim of any third person regarding infringement &n; * or the like.  Any license provided herein, whether implied or &n; * otherwise, applies only to this software file.  Patent licenses, if &n; * any, provided herein do not apply to combinations of this program with &n; * other software, or any other product whatsoever.&n; * &n; * You should have received a copy of the GNU General Public &n; * License along with this program; if not, write the Free Software &n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; * &n; * Contact information:  Silicon Graphics, Inc., 1600 Amphitheatre Pkwy, &n; * Mountain View, CA  94043, or:&n; * &n; * http://www.sgi.com &n; * &n; * For further information regarding this notice, see: &n; * &n; * http://oss.sgi.com/projects/GenInfo/NoticeExplan&n; */
macro_line|#ifndef _ASM_IA64_SN_BTE_H
DECL|macro|_ASM_IA64_SN_BTE_H
mdefine_line|#define _ASM_IA64_SN_BTE_H
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/cache.h&gt;
macro_line|#include &lt;asm/sn/io.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
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
multiline_comment|/* macro to force the IBCT0 value valid */
DECL|macro|BTE_VALID_MODE
mdefine_line|#define BTE_VALID_MODE(x) ((x) &amp; (IBCT_NOTIFY | IBCT_ZFIL_MODE))
multiline_comment|/*&n; * Handle locking of the bte interfaces.&n; *&n; * All transfers spinlock the interface before setting up the SHUB&n; * registers.  Sync transfers hold the lock until all processing is&n; * complete.  Async transfers release the lock as soon as the transfer&n; * is initiated.&n; *&n; * To determine if an interface is available, we must check both the&n; * busy bit and the spinlock for that interface.&n; */
DECL|macro|BTE_LOCK_IF_AVAIL
mdefine_line|#define BTE_LOCK_IF_AVAIL(_x) (&bslash;&n;&t;(*pda-&gt;cpu_bte_if[_x]-&gt;most_rcnt_na &amp; (IBLS_BUSY | IBLS_ERROR)) &amp;&amp; &bslash;&n;&t;(!(spin_trylock(&amp;(pda-&gt;cpu_bte_if[_x]-&gt;spinlock)))) &bslash;&n;&t;)
multiline_comment|/*&n; * Some macros to simplify reading.&n; * Start with macros to locate the BTE control registers.&n; */
DECL|macro|BTEREG_LNSTAT_ADDR
mdefine_line|#define BTEREG_LNSTAT_ADDR ((u64 *)(bte-&gt;bte_base_addr))
DECL|macro|BTEREG_SRC_ADDR
mdefine_line|#define BTEREG_SRC_ADDR ((u64 *)(bte-&gt;bte_base_addr + BTEOFF_SRC))
DECL|macro|BTEREG_DEST_ADDR
mdefine_line|#define BTEREG_DEST_ADDR ((u64 *)(bte-&gt;bte_base_addr + BTEOFF_DEST))
DECL|macro|BTEREG_CTRL_ADDR
mdefine_line|#define BTEREG_CTRL_ADDR ((u64 *)(bte-&gt;bte_base_addr + BTEOFF_CTRL))
DECL|macro|BTEREG_NOTIF_ADDR
mdefine_line|#define BTEREG_NOTIF_ADDR ((u64 *)(bte-&gt;bte_base_addr + BTEOFF_NOTIFY))
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
DECL|enumerator|BTEFAIL_POISON
id|BTEFAIL_POISON
comma
multiline_comment|/* poison page */
DECL|enumerator|BTEFAIL_PROT
id|BTEFAIL_PROT
comma
multiline_comment|/* Protection violation */
DECL|enumerator|BTEFAIL_ACCESS
id|BTEFAIL_ACCESS
comma
multiline_comment|/* access error */
DECL|enumerator|BTEFAIL_TOUT
id|BTEFAIL_TOUT
comma
multiline_comment|/* Time out */
DECL|enumerator|BTEFAIL_XTERR
id|BTEFAIL_XTERR
comma
multiline_comment|/* Diretory error */
DECL|enumerator|BTEFAIL_DIR
id|BTEFAIL_DIR
comma
multiline_comment|/* Diretory error */
DECL|enumerator|BTEFAIL_ERROR
id|BTEFAIL_ERROR
comma
multiline_comment|/* Generic error */
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
id|u64
r_volatile
op_star
id|most_rcnt_na
suffix:semicolon
DECL|member|scratch_buf
r_void
op_star
id|scratch_buf
suffix:semicolon
multiline_comment|/* Node local scratch buffer        */
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
multiline_comment|/*&n; * The following is the prefered way of calling bte_unaligned_copy&n; * If the copy is fully cache line aligned, then bte_copy is&n; * used instead.  Since bte_copy is inlined, this saves a call&n; * stack.  NOTE: bte_copy is called synchronously and does block&n; * until the transfer is complete.  In order to get the asynch&n; * version of bte_copy, you must perform this check yourself.&n; */
DECL|macro|BTE_UNALIGNED_COPY
mdefine_line|#define BTE_UNALIGNED_COPY(src, dest, len, mode)                        &bslash;&n;&t;(((len &amp; L1_CACHE_MASK) || (src &amp; L1_CACHE_MASK) ||             &bslash;&n;&t;  (dest &amp; L1_CACHE_MASK)) ?                                     &bslash;&n;&t; bte_unaligned_copy(src, dest, len, mode) :              &t;&bslash;&n;&t; bte_copy(src, dest, len, mode, NULL))
macro_line|#endif&t;/* _ASM_IA64_SN_BTE_H */
eof
