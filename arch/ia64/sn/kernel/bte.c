multiline_comment|/*&n; *&n; *&n; * Copyright (c) 2000-2003 Silicon Graphics, Inc.  All Rights Reserved.&n; * &n; * This program is free software; you can redistribute it and/or modify it &n; * under the terms of version 2 of the GNU General Public License &n; * as published by the Free Software Foundation.&n; * &n; * This program is distributed in the hope that it would be useful, but &n; * WITHOUT ANY WARRANTY; without even the implied warranty of &n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. &n; * &n; * Further, this software is distributed without any warranty that it is &n; * free of the rightful claim of any third person regarding infringement &n; * or the like.  Any license provided herein, whether implied or &n; * otherwise, applies only to this software file.  Patent licenses, if &n; * any, provided herein do not apply to combinations of this program with &n; * other software, or any other product whatsoever.&n; * &n; * You should have received a copy of the GNU General Public &n; * License along with this program; if not, write the Free Software &n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; * &n; * Contact information:  Silicon Graphics, Inc., 1600 Amphitheatre Pkwy, &n; * Mountain View, CA  94043, or:&n; * &n; * http://www.sgi.com &n; * &n; * For further information regarding this notice, see: &n; * &n; * http://oss.sgi.com/projects/GenInfo/NoticeExplan&n; */
macro_line|#include &lt;linux/config.h&gt;
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
multiline_comment|/*&n; * The base address of for each set of bte registers.&n; */
DECL|variable|bte_offsets
r_static
r_int
id|bte_offsets
(braket
)braket
op_assign
(brace
id|IIO_IBLS0
comma
id|IIO_IBLS1
)brace
suffix:semicolon
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
r_int
id|bte_to_use
suffix:semicolon
id|u64
id|transfer_size
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
r_do
(brace
id|local_irq_save
c_func
(paren
id|irq_flags
)paren
suffix:semicolon
id|bte_to_use
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Attempt to lock one of the BTE interfaces. */
r_while
c_loop
(paren
(paren
id|bte_to_use
OL
id|BTES_PER_NODE
)paren
op_logical_and
id|BTE_LOCK_IF_AVAIL
c_func
(paren
id|bte_to_use
)paren
)paren
(brace
id|bte_to_use
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|bte_to_use
OL
id|BTES_PER_NODE
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
multiline_comment|/* Wait until a bte is available. */
id|udelay
c_func
(paren
l_int|10
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
l_int|1
)paren
suffix:semicolon
id|bte
op_assign
id|pda-&gt;cpu_bte_if
(braket
id|bte_to_use
)braket
suffix:semicolon
id|BTE_PRINTKV
c_func
(paren
(paren
l_string|&quot;Got a lock on bte %d&bslash;n&quot;
comma
id|bte_to_use
)paren
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
l_string|&quot;IBLS - HUB_S(0x%p, 0x%lx)&bslash;n&quot;
comma
id|BTEREG_LNSTAT_ADDR
comma
id|IBLS_BUSY
op_or
id|transfer_size
)paren
)paren
suffix:semicolon
id|HUB_S
c_func
(paren
id|BTEREG_LNSTAT_ADDR
comma
(paren
id|IBLS_BUSY
op_or
id|transfer_size
)paren
)paren
suffix:semicolon
multiline_comment|/* Set the source and destination registers */
id|BTE_PRINTKV
c_func
(paren
(paren
l_string|&quot;IBSA - HUB_S(0x%p, 0x%lx)&bslash;n&quot;
comma
id|BTEREG_SRC_ADDR
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
id|HUB_S
c_func
(paren
id|BTEREG_SRC_ADDR
comma
(paren
id|TO_PHYS
c_func
(paren
id|src
)paren
)paren
)paren
suffix:semicolon
id|BTE_PRINTKV
c_func
(paren
(paren
l_string|&quot;IBDA - HUB_S(0x%p, 0x%lx)&bslash;n&quot;
comma
id|BTEREG_DEST_ADDR
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
id|HUB_S
c_func
(paren
id|BTEREG_DEST_ADDR
comma
(paren
id|TO_PHYS
c_func
(paren
id|dest
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* Set the notification register */
id|BTE_PRINTKV
c_func
(paren
(paren
l_string|&quot;IBNA - HUB_S(0x%p, 0x%lx)&bslash;n&quot;
comma
id|BTEREG_NOTIF_ADDR
comma
(paren
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
)paren
suffix:semicolon
id|HUB_S
c_func
(paren
id|BTEREG_NOTIF_ADDR
comma
(paren
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
multiline_comment|/* Initiate the transfer */
id|BTE_PRINTK
c_func
(paren
(paren
l_string|&quot;IBCT - HUB_S(0x%p, 0x%lx)&bslash;n&quot;
comma
id|BTEREG_CTRL_ADDR
comma
id|BTE_VALID_MODE
c_func
(paren
id|mode
)paren
)paren
)paren
suffix:semicolon
id|HUB_S
c_func
(paren
id|BTEREG_CTRL_ADDR
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
op_star
id|bte-&gt;most_rcnt_na
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
id|HUB_L
c_func
(paren
id|BTEREG_LNSTAT_ADDR
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
op_star
id|bte-&gt;most_rcnt_na
op_amp
id|IBLS_ERROR
)paren
(brace
id|bte_status
op_assign
op_star
id|bte-&gt;most_rcnt_na
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
id|HUB_L
c_func
(paren
id|BTEREG_LNSTAT_ADDR
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
id|bteBlock
op_assign
id|pda-&gt;cpu_bte_if
(braket
l_int|0
)braket
op_member_access_from_pointer
id|scratch_buf
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
r_return
id|BTE_SUCCESS
suffix:semicolon
)brace
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
multiline_comment|/* &gt;&gt;&gt; Don&squot;t know why the 0x1800000L is here.  Robin */
id|mynodepda-&gt;bte_if
(braket
id|i
)braket
dot
id|bte_base_addr
op_assign
(paren
r_char
op_star
)paren
id|LOCAL_MMR_ADDR
c_func
(paren
id|bte_offsets
(braket
id|i
)braket
op_or
l_int|0x1800000L
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
id|scratch_buf
op_assign
id|alloc_bootmem_node
c_func
(paren
id|NODE_DATA
c_func
(paren
id|cnode
)paren
comma
id|BTE_MAX_XFER
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
multiline_comment|/*&n; * bte_init_cpu()&n; *&n; * Initialize the cpupda structure with pointers to the&n; * nodepda bte blocks.&n; *&n; */
r_void
DECL|function|bte_init_cpu
id|bte_init_cpu
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Called by setup.c as each cpu is being added to the nodepda */
r_if
c_cond
(paren
id|local_node_data-&gt;active_cpu_count
op_amp
l_int|0x1
)paren
(brace
id|pda-&gt;cpu_bte_if
(braket
l_int|0
)braket
op_assign
op_amp
(paren
id|nodepda-&gt;bte_if
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|pda-&gt;cpu_bte_if
(braket
l_int|1
)braket
op_assign
op_amp
(paren
id|nodepda-&gt;bte_if
(braket
l_int|1
)braket
)paren
suffix:semicolon
)brace
r_else
(brace
id|pda-&gt;cpu_bte_if
(braket
l_int|0
)braket
op_assign
op_amp
(paren
id|nodepda-&gt;bte_if
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|pda-&gt;cpu_bte_if
(braket
l_int|1
)braket
op_assign
op_amp
(paren
id|nodepda-&gt;bte_if
(braket
l_int|0
)braket
)paren
suffix:semicolon
)brace
)brace
eof
