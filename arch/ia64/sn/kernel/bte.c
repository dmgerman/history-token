multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (c) 2000-2003 Silicon Graphics, Inc.  All Rights Reserved.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/sn/sgi.h&gt;
macro_line|#include &lt;asm/sn/nodepda.h&gt;
macro_line|#include &lt;asm/sn/addrs.h&gt;
macro_line|#include &lt;asm/sn/arch.h&gt;
macro_line|#include &lt;asm/sn/sn_cpuid.h&gt;
macro_line|#include &lt;asm/sn/pda.h&gt;
macro_line|#include &lt;asm/sn/sn2/shubio.h&gt;
macro_line|#include &lt;asm/nodedata.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/sn/bte.h&gt;
macro_line|#ifndef L1_CACHE_MASK
DECL|macro|L1_CACHE_MASK
mdefine_line|#define L1_CACHE_MASK (L1_CACHE_BYTES - 1)
macro_line|#endif
multiline_comment|/* two interfaces on two btes */
DECL|macro|MAX_INTERFACES_TO_TRY
mdefine_line|#define MAX_INTERFACES_TO_TRY&t;&t;4
r_static
r_struct
id|bteinfo_s
op_star
DECL|function|bte_if_on_node
id|bte_if_on_node
c_func
(paren
id|nasid_t
id|nasid
comma
r_int
id|interface
)paren
(brace
id|nodepda_t
op_star
id|tmp_nodepda
suffix:semicolon
id|tmp_nodepda
op_assign
id|NODEPDA
c_func
(paren
id|nasid_to_cnodeid
c_func
(paren
id|nasid
)paren
)paren
suffix:semicolon
r_return
op_amp
id|tmp_nodepda-&gt;bte_if
(braket
id|interface
)braket
suffix:semicolon
)brace
multiline_comment|/************************************************************************&n; * Block Transfer Engine copy related functions.&n; *&n; ***********************************************************************/
multiline_comment|/*&n; * bte_copy(src, dest, len, mode, notification)&n; *&n; * Use the block transfer engine to move kernel memory from src to dest&n; * using the assigned mode.&n; *&n; * Paramaters:&n; *   src - physical address of the transfer source.&n; *   dest - physical address of the transfer destination.&n; *   len - number of bytes to transfer from source to dest.&n; *   mode - hardware defined.  See reference information&n; *          for IBCT0/1 in the SHUB Programmers Reference&n; *   notification - kernel virtual address of the notification cache&n; *                  line.  If NULL, the default is used and&n; *                  the bte_copy is synchronous.&n; *&n; * NOTE:  This function requires src, dest, and len to&n; * be cacheline aligned.&n; */
id|bte_result_t
DECL|function|bte_copy
id|bte_copy
c_func
(paren
id|u64
id|src
comma
id|u64
id|dest
comma
id|u64
id|len
comma
id|u64
id|mode
comma
r_void
op_star
id|notification
)paren
(brace
id|u64
id|transfer_size
suffix:semicolon
id|u64
id|transfer_stat
suffix:semicolon
r_struct
id|bteinfo_s
op_star
id|bte
suffix:semicolon
id|bte_result_t
id|bte_status
suffix:semicolon
r_int
r_int
id|irq_flags
suffix:semicolon
r_struct
id|bteinfo_s
op_star
id|btes_to_try
(braket
id|MAX_INTERFACES_TO_TRY
)braket
suffix:semicolon
r_int
id|bte_if_index
suffix:semicolon
id|BTE_PRINTK
c_func
(paren
(paren
l_string|&quot;bte_copy(0x%lx, 0x%lx, 0x%lx, 0x%lx, 0x%p)&bslash;n&quot;
comma
id|src
comma
id|dest
comma
id|len
comma
id|mode
comma
id|notification
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_eq
l_int|0
)paren
(brace
r_return
id|BTE_SUCCESS
suffix:semicolon
)brace
id|ASSERT
c_func
(paren
op_logical_neg
(paren
(paren
id|len
op_amp
id|L1_CACHE_MASK
)paren
op_logical_or
(paren
id|src
op_amp
id|L1_CACHE_MASK
)paren
op_logical_or
(paren
id|dest
op_amp
id|L1_CACHE_MASK
)paren
)paren
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|len
OL
(paren
(paren
id|BTE_LEN_MASK
op_plus
l_int|1
)paren
op_lshift
id|L1_CACHE_SHIFT
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mode
op_amp
id|BTE_USE_DEST
)paren
(brace
multiline_comment|/* try remote then local */
id|btes_to_try
(braket
l_int|0
)braket
op_assign
id|bte_if_on_node
c_func
(paren
id|NASID_GET
c_func
(paren
id|dest
)paren
comma
l_int|0
)paren
suffix:semicolon
id|btes_to_try
(braket
l_int|1
)braket
op_assign
id|bte_if_on_node
c_func
(paren
id|NASID_GET
c_func
(paren
id|dest
)paren
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mode
op_amp
id|BTE_USE_ANY
)paren
(brace
id|btes_to_try
(braket
l_int|2
)braket
op_assign
id|bte_if_on_node
c_func
(paren
id|get_nasid
c_func
(paren
)paren
comma
l_int|0
)paren
suffix:semicolon
id|btes_to_try
(braket
l_int|3
)braket
op_assign
id|bte_if_on_node
c_func
(paren
id|get_nasid
c_func
(paren
)paren
comma
l_int|1
)paren
suffix:semicolon
)brace
r_else
(brace
id|btes_to_try
(braket
l_int|2
)braket
op_assign
l_int|NULL
suffix:semicolon
id|btes_to_try
(braket
l_int|3
)braket
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* try local then remote */
id|btes_to_try
(braket
l_int|0
)braket
op_assign
id|bte_if_on_node
c_func
(paren
id|get_nasid
c_func
(paren
)paren
comma
l_int|0
)paren
suffix:semicolon
id|btes_to_try
(braket
l_int|1
)braket
op_assign
id|bte_if_on_node
c_func
(paren
id|get_nasid
c_func
(paren
)paren
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mode
op_amp
id|BTE_USE_ANY
)paren
(brace
id|btes_to_try
(braket
l_int|2
)braket
op_assign
id|bte_if_on_node
c_func
(paren
id|NASID_GET
c_func
(paren
id|dest
)paren
comma
l_int|0
)paren
suffix:semicolon
id|btes_to_try
(braket
l_int|3
)braket
op_assign
id|bte_if_on_node
c_func
(paren
id|NASID_GET
c_func
(paren
id|dest
)paren
comma
l_int|1
)paren
suffix:semicolon
)brace
r_else
(brace
id|btes_to_try
(braket
l_int|2
)braket
op_assign
l_int|NULL
suffix:semicolon
id|btes_to_try
(braket
l_int|3
)braket
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
r_do
(brace
id|local_irq_save
c_func
(paren
id|irq_flags
)paren
suffix:semicolon
id|bte_if_index
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Attempt to lock one of the BTE interfaces. */
r_while
c_loop
(paren
id|bte_if_index
OL
id|MAX_INTERFACES_TO_TRY
)paren
(brace
id|bte
op_assign
id|btes_to_try
(braket
id|bte_if_index
op_increment
)braket
suffix:semicolon
r_if
c_cond
(paren
id|bte
op_eq
l_int|NULL
)paren
(brace
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|spin_trylock
c_func
(paren
op_amp
id|bte-&gt;spinlock
)paren
)paren
(brace
r_if
c_cond
(paren
(paren
op_star
id|bte-&gt;most_rcnt_na
op_amp
id|BTE_ACTIVE
)paren
op_logical_or
(paren
id|BTE_LNSTAT_LOAD
c_func
(paren
id|bte
)paren
op_amp
id|BTE_ACTIVE
)paren
)paren
(brace
multiline_comment|/* Got the lock but BTE still busy */
id|spin_unlock
c_func
(paren
op_amp
id|bte-&gt;spinlock
)paren
suffix:semicolon
id|bte
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* we got the lock and it&squot;s not busy */
r_break
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
id|bte
op_ne
l_int|NULL
)paren
(brace
r_break
suffix:semicolon
)brace
id|local_irq_restore
c_func
(paren
id|irq_flags
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|mode
op_amp
id|BTE_WACQUIRE
)paren
)paren
(brace
r_return
id|BTEFAIL_NOTAVAIL
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|notification
op_eq
l_int|NULL
)paren
(brace
multiline_comment|/* User does not want to be notified. */
id|bte-&gt;most_rcnt_na
op_assign
op_amp
id|bte-&gt;notify
suffix:semicolon
)brace
r_else
(brace
id|bte-&gt;most_rcnt_na
op_assign
id|notification
suffix:semicolon
)brace
multiline_comment|/* Calculate the number of cache lines to transfer. */
id|transfer_size
op_assign
(paren
(paren
id|len
op_rshift
id|L1_CACHE_SHIFT
)paren
op_amp
id|BTE_LEN_MASK
)paren
suffix:semicolon
multiline_comment|/* Initialize the notification to a known value. */
op_star
id|bte-&gt;most_rcnt_na
op_assign
op_minus
l_int|1L
suffix:semicolon
multiline_comment|/* Set the status reg busy bit and transfer length */
id|BTE_PRINTKV
c_func
(paren
(paren
l_string|&quot;IBLS = 0x%lx&bslash;n&quot;
comma
id|IBLS_BUSY
op_or
id|transfer_size
)paren
)paren
suffix:semicolon
id|BTE_LNSTAT_STORE
c_func
(paren
id|bte
comma
id|IBLS_BUSY
op_or
id|transfer_size
)paren
suffix:semicolon
multiline_comment|/* Set the source and destination registers */
id|BTE_PRINTKV
c_func
(paren
(paren
l_string|&quot;IBSA = 0x%lx)&bslash;n&quot;
comma
(paren
id|TO_PHYS
c_func
(paren
id|src
)paren
)paren
)paren
)paren
suffix:semicolon
id|BTE_SRC_STORE
c_func
(paren
id|bte
comma
id|TO_PHYS
c_func
(paren
id|src
)paren
)paren
suffix:semicolon
id|BTE_PRINTKV
c_func
(paren
(paren
l_string|&quot;IBDA = 0x%lx)&bslash;n&quot;
comma
(paren
id|TO_PHYS
c_func
(paren
id|dest
)paren
)paren
)paren
)paren
suffix:semicolon
id|BTE_DEST_STORE
c_func
(paren
id|bte
comma
id|TO_PHYS
c_func
(paren
id|dest
)paren
)paren
suffix:semicolon
multiline_comment|/* Set the notification register */
id|BTE_PRINTKV
c_func
(paren
(paren
l_string|&quot;IBNA = 0x%lx)&bslash;n&quot;
comma
id|TO_PHYS
c_func
(paren
id|ia64_tpa
c_func
(paren
(paren
r_int
r_int
)paren
id|bte-&gt;most_rcnt_na
)paren
)paren
)paren
)paren
suffix:semicolon
id|BTE_NOTIF_STORE
c_func
(paren
id|bte
comma
id|TO_PHYS
c_func
(paren
id|ia64_tpa
c_func
(paren
(paren
r_int
r_int
)paren
id|bte-&gt;most_rcnt_na
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* Initiate the transfer */
id|BTE_PRINTK
c_func
(paren
(paren
l_string|&quot;IBCT = 0x%lx)&bslash;n&quot;
comma
id|BTE_VALID_MODE
c_func
(paren
id|mode
)paren
)paren
)paren
suffix:semicolon
id|BTE_CTRL_STORE
c_func
(paren
id|bte
comma
id|BTE_VALID_MODE
c_func
(paren
id|mode
)paren
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|bte-&gt;spinlock
comma
id|irq_flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|notification
op_ne
l_int|NULL
)paren
(brace
r_return
id|BTE_SUCCESS
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|transfer_stat
op_assign
op_star
id|bte-&gt;most_rcnt_na
)paren
op_eq
op_minus
l_int|1UL
)paren
(brace
)brace
id|BTE_PRINTKV
c_func
(paren
(paren
l_string|&quot; Delay Done.  IBLS = 0x%lx, most_rcnt_na = 0x%lx&bslash;n&quot;
comma
id|BTE_LNSTAT_LOAD
c_func
(paren
id|bte
)paren
comma
op_star
id|bte-&gt;most_rcnt_na
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|transfer_stat
op_amp
id|IBLS_ERROR
)paren
(brace
id|bte_status
op_assign
id|transfer_stat
op_amp
op_complement
id|IBLS_ERROR
suffix:semicolon
op_star
id|bte-&gt;most_rcnt_na
op_assign
l_int|0L
suffix:semicolon
)brace
r_else
(brace
id|bte_status
op_assign
id|BTE_SUCCESS
suffix:semicolon
)brace
id|BTE_PRINTK
c_func
(paren
(paren
l_string|&quot;Returning status is 0x%lx and most_rcnt_na is 0x%lx&bslash;n&quot;
comma
id|BTE_LNSTAT_LOAD
c_func
(paren
id|bte
)paren
comma
op_star
id|bte-&gt;most_rcnt_na
)paren
)paren
suffix:semicolon
r_return
id|bte_status
suffix:semicolon
)brace
DECL|variable|bte_copy
id|EXPORT_SYMBOL
c_func
(paren
id|bte_copy
)paren
suffix:semicolon
multiline_comment|/*&n; * bte_unaligned_copy(src, dest, len, mode)&n; *&n; * use the block transfer engine to move kernel&n; * memory from src to dest using the assigned mode.&n; *&n; * Paramaters:&n; *   src - physical address of the transfer source.&n; *   dest - physical address of the transfer destination.&n; *   len - number of bytes to transfer from source to dest.&n; *   mode - hardware defined.  See reference information&n; *          for IBCT0/1 in the SGI documentation.&n; *&n; * NOTE: If the source, dest, and len are all cache line aligned,&n; * then it would be _FAR_ preferrable to use bte_copy instead.&n; */
id|bte_result_t
DECL|function|bte_unaligned_copy
id|bte_unaligned_copy
c_func
(paren
id|u64
id|src
comma
id|u64
id|dest
comma
id|u64
id|len
comma
id|u64
id|mode
)paren
(brace
r_int
id|destFirstCacheOffset
suffix:semicolon
id|u64
id|headBteSource
suffix:semicolon
id|u64
id|headBteLen
suffix:semicolon
id|u64
id|headBcopySrcOffset
suffix:semicolon
id|u64
id|headBcopyDest
suffix:semicolon
id|u64
id|headBcopyLen
suffix:semicolon
id|u64
id|footBteSource
suffix:semicolon
id|u64
id|footBteLen
suffix:semicolon
id|u64
id|footBcopyDest
suffix:semicolon
id|u64
id|footBcopyLen
suffix:semicolon
id|bte_result_t
id|rv
suffix:semicolon
r_char
op_star
id|bteBlock
comma
op_star
id|bteBlock_unaligned
suffix:semicolon
r_if
c_cond
(paren
id|len
op_eq
l_int|0
)paren
(brace
r_return
id|BTE_SUCCESS
suffix:semicolon
)brace
multiline_comment|/* temporary buffer used during unaligned transfers */
id|bteBlock_unaligned
op_assign
id|kmalloc
c_func
(paren
id|len
op_plus
l_int|3
op_star
id|L1_CACHE_BYTES
comma
id|GFP_KERNEL
op_or
id|GFP_DMA
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bteBlock_unaligned
op_eq
l_int|NULL
)paren
(brace
r_return
id|BTEFAIL_NOTAVAIL
suffix:semicolon
)brace
id|bteBlock
op_assign
(paren
r_char
op_star
)paren
id|L1_CACHE_ALIGN
c_func
(paren
(paren
id|u64
)paren
id|bteBlock_unaligned
)paren
suffix:semicolon
id|headBcopySrcOffset
op_assign
id|src
op_amp
id|L1_CACHE_MASK
suffix:semicolon
id|destFirstCacheOffset
op_assign
id|dest
op_amp
id|L1_CACHE_MASK
suffix:semicolon
multiline_comment|/*&n;&t; * At this point, the transfer is broken into&n;&t; * (up to) three sections.  The first section is&n;&t; * from the start address to the first physical&n;&t; * cache line, the second is from the first physical&n;&t; * cache line to the last complete cache line,&n;&t; * and the third is from the last cache line to the&n;&t; * end of the buffer.  The first and third sections&n;&t; * are handled by bte copying into a temporary buffer&n;&t; * and then bcopy&squot;ing the necessary section into the&n;&t; * final location.  The middle section is handled with&n;&t; * a standard bte copy.&n;&t; *&n;&t; * One nasty exception to the above rule is when the&n;&t; * source and destination are not symetrically&n;&t; * mis-aligned.  If the source offset from the first&n;&t; * cache line is different from the destination offset,&n;&t; * we make the first section be the entire transfer&n;&t; * and the bcopy the entire block into place.&n;&t; */
r_if
c_cond
(paren
id|headBcopySrcOffset
op_eq
id|destFirstCacheOffset
)paren
(brace
multiline_comment|/*&n;&t;&t; * Both the source and destination are the same&n;&t;&t; * distance from a cache line boundary so we can&n;&t;&t; * use the bte to transfer the bulk of the&n;&t;&t; * data.&n;&t;&t; */
id|headBteSource
op_assign
id|src
op_amp
op_complement
id|L1_CACHE_MASK
suffix:semicolon
id|headBcopyDest
op_assign
id|dest
suffix:semicolon
r_if
c_cond
(paren
id|headBcopySrcOffset
)paren
(brace
id|headBcopyLen
op_assign
(paren
id|len
OG
(paren
id|L1_CACHE_BYTES
op_minus
id|headBcopySrcOffset
)paren
ques
c_cond
id|L1_CACHE_BYTES
op_minus
id|headBcopySrcOffset
suffix:colon
id|len
)paren
suffix:semicolon
id|headBteLen
op_assign
id|L1_CACHE_BYTES
suffix:semicolon
)brace
r_else
(brace
id|headBcopyLen
op_assign
l_int|0
suffix:semicolon
id|headBteLen
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|len
OG
id|headBcopyLen
)paren
(brace
id|footBcopyLen
op_assign
(paren
id|len
op_minus
id|headBcopyLen
)paren
op_amp
id|L1_CACHE_MASK
suffix:semicolon
id|footBteLen
op_assign
id|L1_CACHE_BYTES
suffix:semicolon
id|footBteSource
op_assign
id|src
op_plus
id|len
op_minus
id|footBcopyLen
suffix:semicolon
id|footBcopyDest
op_assign
id|dest
op_plus
id|len
op_minus
id|footBcopyLen
suffix:semicolon
r_if
c_cond
(paren
id|footBcopyDest
op_eq
(paren
id|headBcopyDest
op_plus
id|headBcopyLen
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * We have two contigous bcopy&n;&t;&t;&t;&t; * blocks.  Merge them.&n;&t;&t;&t;&t; */
id|headBcopyLen
op_add_assign
id|footBcopyLen
suffix:semicolon
id|headBteLen
op_add_assign
id|footBteLen
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|footBcopyLen
OG
l_int|0
)paren
(brace
id|rv
op_assign
id|bte_copy
c_func
(paren
id|footBteSource
comma
id|ia64_tpa
c_func
(paren
(paren
r_int
r_int
)paren
id|bteBlock
)paren
comma
id|footBteLen
comma
id|mode
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rv
op_ne
id|BTE_SUCCESS
)paren
(brace
id|kfree
c_func
(paren
id|bteBlock_unaligned
)paren
suffix:semicolon
r_return
id|rv
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|__va
c_func
(paren
id|footBcopyDest
)paren
comma
(paren
r_char
op_star
)paren
id|bteBlock
comma
id|footBcopyLen
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|footBcopyLen
op_assign
l_int|0
suffix:semicolon
id|footBteLen
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|len
OG
(paren
id|headBcopyLen
op_plus
id|footBcopyLen
)paren
)paren
(brace
multiline_comment|/* now transfer the middle. */
id|rv
op_assign
id|bte_copy
c_func
(paren
(paren
id|src
op_plus
id|headBcopyLen
)paren
comma
(paren
id|dest
op_plus
id|headBcopyLen
)paren
comma
(paren
id|len
op_minus
id|headBcopyLen
op_minus
id|footBcopyLen
)paren
comma
id|mode
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rv
op_ne
id|BTE_SUCCESS
)paren
(brace
id|kfree
c_func
(paren
id|bteBlock_unaligned
)paren
suffix:semicolon
r_return
id|rv
suffix:semicolon
)brace
)brace
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t; * The transfer is not symetric, we will&n;&t;&t; * allocate a buffer large enough for all the&n;&t;&t; * data, bte_copy into that buffer and then&n;&t;&t; * bcopy to the destination.&n;&t;&t; */
multiline_comment|/* Add the leader from source */
id|headBteLen
op_assign
id|len
op_plus
(paren
id|src
op_amp
id|L1_CACHE_MASK
)paren
suffix:semicolon
multiline_comment|/* Add the trailing bytes from footer. */
id|headBteLen
op_add_assign
id|L1_CACHE_BYTES
op_minus
(paren
id|headBteLen
op_amp
id|L1_CACHE_MASK
)paren
suffix:semicolon
id|headBteSource
op_assign
id|src
op_amp
op_complement
id|L1_CACHE_MASK
suffix:semicolon
id|headBcopySrcOffset
op_assign
id|src
op_amp
id|L1_CACHE_MASK
suffix:semicolon
id|headBcopyDest
op_assign
id|dest
suffix:semicolon
id|headBcopyLen
op_assign
id|len
suffix:semicolon
)brace
r_if
c_cond
(paren
id|headBcopyLen
OG
l_int|0
)paren
(brace
id|rv
op_assign
id|bte_copy
c_func
(paren
id|headBteSource
comma
id|ia64_tpa
c_func
(paren
(paren
r_int
r_int
)paren
id|bteBlock
)paren
comma
id|headBteLen
comma
id|mode
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rv
op_ne
id|BTE_SUCCESS
)paren
(brace
id|kfree
c_func
(paren
id|bteBlock_unaligned
)paren
suffix:semicolon
r_return
id|rv
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|__va
c_func
(paren
id|headBcopyDest
)paren
comma
(paren
(paren
r_char
op_star
)paren
id|bteBlock
op_plus
id|headBcopySrcOffset
)paren
comma
id|headBcopyLen
)paren
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|bteBlock_unaligned
)paren
suffix:semicolon
r_return
id|BTE_SUCCESS
suffix:semicolon
)brace
DECL|variable|bte_unaligned_copy
id|EXPORT_SYMBOL
c_func
(paren
id|bte_unaligned_copy
)paren
suffix:semicolon
multiline_comment|/************************************************************************&n; * Block Transfer Engine initialization functions.&n; *&n; ***********************************************************************/
multiline_comment|/*&n; * bte_init_node(nodepda, cnode)&n; *&n; * Initialize the nodepda structure with BTE base addresses and&n; * spinlocks.&n; */
r_void
DECL|function|bte_init_node
id|bte_init_node
c_func
(paren
id|nodepda_t
op_star
id|mynodepda
comma
id|cnodeid_t
id|cnode
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/*&n;&t; * Indicate that all the block transfer engines on this node&n;&t; * are available.&n;&t; */
multiline_comment|/*&n;&t; * Allocate one bte_recover_t structure per node.  It holds&n;&t; * the recovery lock for node.  All the bte interface structures&n;&t; * will point at this one bte_recover structure to get the lock.&n;&t; */
id|spin_lock_init
c_func
(paren
op_amp
id|mynodepda-&gt;bte_recovery_lock
)paren
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|mynodepda-&gt;bte_recovery_timer
)paren
suffix:semicolon
id|mynodepda-&gt;bte_recovery_timer.function
op_assign
id|bte_error_handler
suffix:semicolon
id|mynodepda-&gt;bte_recovery_timer.data
op_assign
(paren
r_int
r_int
)paren
id|mynodepda
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|BTES_PER_NODE
suffix:semicolon
id|i
op_increment
)paren
(brace
(paren
id|u64
)paren
id|mynodepda-&gt;bte_if
(braket
id|i
)braket
dot
id|bte_base_addr
op_assign
id|REMOTE_HUB_ADDR
c_func
(paren
id|cnodeid_to_nasid
c_func
(paren
id|cnode
)paren
comma
(paren
id|i
op_eq
l_int|0
ques
c_cond
id|IIO_IBLS0
suffix:colon
id|IIO_IBLS1
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Initialize the notification and spinlock&n;&t;&t; * so the first transfer can occur.&n;&t;&t; */
id|mynodepda-&gt;bte_if
(braket
id|i
)braket
dot
id|most_rcnt_na
op_assign
op_amp
(paren
id|mynodepda-&gt;bte_if
(braket
id|i
)braket
dot
id|notify
)paren
suffix:semicolon
id|mynodepda-&gt;bte_if
(braket
id|i
)braket
dot
id|notify
op_assign
l_int|0L
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|mynodepda-&gt;bte_if
(braket
id|i
)braket
dot
id|spinlock
)paren
suffix:semicolon
id|mynodepda-&gt;bte_if
(braket
id|i
)braket
dot
id|bte_cnode
op_assign
id|cnode
suffix:semicolon
id|mynodepda-&gt;bte_if
(braket
id|i
)braket
dot
id|bte_error_count
op_assign
l_int|0
suffix:semicolon
id|mynodepda-&gt;bte_if
(braket
id|i
)braket
dot
id|bte_num
op_assign
id|i
suffix:semicolon
id|mynodepda-&gt;bte_if
(braket
id|i
)braket
dot
id|cleanup_active
op_assign
l_int|0
suffix:semicolon
id|mynodepda-&gt;bte_if
(braket
id|i
)braket
dot
id|bh_error
op_assign
l_int|0
suffix:semicolon
)brace
)brace
eof
