multiline_comment|/*&n; *&n; *&n; * Copyright (c) 2000-2002 Silicon Graphics, Inc.  All Rights Reserved.&n; * &n; * This program is free software; you can redistribute it and/or modify it &n; * under the terms of version 2 of the GNU General Public License &n; * as published by the Free Software Foundation.&n; * &n; * This program is distributed in the hope that it would be useful, but &n; * WITHOUT ANY WARRANTY; without even the implied warranty of &n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. &n; * &n; * Further, this software is distributed without any warranty that it is &n; * free of the rightful claim of any third person regarding infringement &n; * or the like.  Any license provided herein, whether implied or &n; * otherwise, applies only to this software file.  Patent licenses, if &n; * any, provided herein do not apply to combinations of this program with &n; * other software, or any other product whatsoever.&n; * &n; * You should have received a copy of the GNU General Public &n; * License along with this program; if not, write the Free Software &n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; * &n; * Contact information:  Silicon Graphics, Inc., 1600 Amphitheatre Pkwy, &n; * Mountain View, CA  94043, or:&n; * &n; * http://www.sgi.com &n; * &n; * For further information regarding this notice, see: &n; * &n; * http://oss.sgi.com/projects/GenInfo/NoticeExplan&n; */
macro_line|#ifndef _ASM_IA64_SN_BTE_COPY_H
DECL|macro|_ASM_IA64_SN_BTE_COPY_H
mdefine_line|#define _ASM_IA64_SN_BTE_COPY_H
macro_line|#ident &quot;$Revision: 1.1 $&quot;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/cache.h&gt;
macro_line|#include &lt;asm/sn/bte.h&gt;
macro_line|#include &lt;asm/sn/sgi.h&gt;
macro_line|#include &lt;asm/sn/pda.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
DECL|macro|L1_CACHE_MASK
mdefine_line|#define L1_CACHE_MASK (L1_CACHE_BYTES - 1)
multiline_comment|/*&n; * BTE_LOCKING support - When CONFIG_IA64_SGI_BTE_LOCKING is&n; * not defined, the bte_copy code supports one bte per cpu in&n; * synchronous mode.  Even if bte_copy is called with a&n; * notify address, the bte will spin and wait for the transfer&n; * to complete.  By defining the following, spin_locks and&n; * busy checks are placed around the initiation of a BTE&n; * transfer and multiple bte&squot;s per cpu are supported.&n; */
macro_line|#if 0
mdefine_line|#define CONFIG_IA64_SGI_BTE_LOCKING 1
macro_line|#endif
multiline_comment|/*&n; * Handle locking of the bte interfaces.&n; *&n; * All transfers spinlock the interface before setting up the SHUB&n; * registers.  Sync transfers hold the lock until all processing is&n; * complete.  Async transfers release the lock as soon as the transfer&n; * is initiated.&n; *&n; * To determine if an interface is available, we must check both the&n; * busy bit and the spinlock for that interface.&n; */
DECL|macro|BTE_LOCK_IF_AVAIL
mdefine_line|#define BTE_LOCK_IF_AVAIL(_x) (&bslash;&n;&t;(*pda.cpu_bte_if[_x]-&gt;most_rcnt_na &amp; IBLS_BUSY) &amp;&amp; &bslash;&n;&t;(!(spin_trylock(&amp;(pda.cpu_bte_if[_x]-&gt;spinlock)))) &bslash;&n;&t;)
multiline_comment|/*&n; * Some macros to simplify reading.&n; *&n; * Start with macros to locate the BTE control registers.&n; */
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
multiline_comment|/* Some macros to force the IBCT0 value valid. */
DECL|macro|BTE_VALID_MODES
mdefine_line|#define BTE_VALID_MODES BTE_NOTIFY
DECL|macro|BTE_VLD_MODE
mdefine_line|#define BTE_VLD_MODE(x) (x &amp; BTE_VALID_MODES)
singleline_comment|// #define BTE_DEBUG
singleline_comment|// #define BTE_DEBUG_VERBOSE
singleline_comment|// #define BTE_TIME
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
macro_line|#endif /* BTE_DEBUG */
DECL|macro|BTE_IDEAL_TMO
mdefine_line|#define BTE_IDEAL_TMO(x) (jiffies + &bslash;&n;&t;(HZ / BTE_MAXT_LINES_PER_SECOND * x))
macro_line|#ifdef BTE_TIME
r_volatile
r_extern
id|u64
id|bte_setup_time
suffix:semicolon
r_volatile
r_extern
id|u64
id|bte_transfer_time
suffix:semicolon
r_volatile
r_extern
id|u64
id|bte_tear_down_time
suffix:semicolon
r_volatile
r_extern
id|u64
id|bte_execute_time
suffix:semicolon
DECL|macro|BTE_TIME_DECLARE
mdefine_line|#define BTE_TIME_DECLARE() &bslash;&n;&t;u64 btcp_strt_tm = 0; &bslash;&n;&t;u64 btcp_cplt_tm = 0; &bslash;&n;&t;u64 xfr_strt_tm = 0; &bslash;&n;&t;u64 xfr_cplt_tm = 0; &bslash;&n;
DECL|macro|BTE_TIME_START
mdefine_line|#define BTE_TIME_START() &bslash;&n;&t;btcp_strt_tm = xfr_strt_tm = xfr_cplt_tm = ia64_get_itc();
DECL|macro|BTE_TIME_XFR_START
mdefine_line|#define BTE_TIME_XFR_START() &bslash;&n;&t;xfr_strt_tm = ia64_get_itc();
DECL|macro|BTE_TIME_XFR_STOP
mdefine_line|#define BTE_TIME_XFR_STOP() &bslash;&n;&t;xfr_cplt_tm = ia64_get_itc();
DECL|macro|BTE_TIME_STOP
mdefine_line|#define BTE_TIME_STOP() &bslash;&n;&t;btcp_cplt_tm = ia64_get_itc(); &bslash;&n;&t;bte_setup_time = xfr_strt_tm - btcp_strt_tm; &bslash;&n;&t;bte_transfer_time = xfr_cplt_tm - xfr_strt_tm; &bslash;&n;&t;bte_tear_down_time = btcp_cplt_tm - xfr_cplt_tm; &bslash;&n;&t;bte_execute_time = btcp_cplt_tm - btcp_strt_tm; &bslash;&n;
macro_line|#else /* BTE_TIME */
DECL|macro|BTE_TIME_DECLARE
mdefine_line|#define BTE_TIME_DECLARE()
DECL|macro|BTE_TIME_START
mdefine_line|#define BTE_TIME_START()
DECL|macro|BTE_TIME_XFR_START
mdefine_line|#define BTE_TIME_XFR_START()
DECL|macro|BTE_TIME_XFR_STOP
mdefine_line|#define BTE_TIME_XFR_STOP()
DECL|macro|BTE_TIME_STOP
mdefine_line|#define BTE_TIME_STOP()
macro_line|#endif /* BTE_TIME */
multiline_comment|/*&n; * bte_copy(src, dest, len, mode, notification)&n; *&n; * use the block transfer engine to move kernel&n; * memory from src to dest using the assigned mode.&n; *&n; * Paramaters:&n; *   src - physical address of the transfer source.&n; *   dest - physical address of the transfer destination.&n; *   len - number of bytes to transfer from source to dest.&n; *   mode - hardware defined.  See reference information&n; *          for IBCT0/1 in the SHUB Programmers Reference&n; *   notification - kernel virtual address of the notification cache&n; *                  line.  If NULL, the default is used and&n; *                  the bte_copy is synchronous.&n; *&n; * NOTE:  This function requires src, dest, and len to&n; * be cache line aligned.&n; */
r_extern
id|__inline__
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
macro_line|#ifdef CONFIG_IA64_SGI_BTE_LOCKING
r_int
id|bte_to_use
suffix:semicolon
macro_line|#endif /* CONFIG_IA64_SGI_BTE_LOCKING */
id|u64
id|transfer_size
suffix:semicolon
id|u64
id|lines_remaining
suffix:semicolon
id|bteinfo_t
op_star
id|bte
suffix:semicolon
id|BTE_TIME_DECLARE
c_func
(paren
)paren
suffix:semicolon
id|BTE_TIME_START
c_func
(paren
)paren
suffix:semicolon
id|BTE_PRINTK
c_func
(paren
(paren
l_string|&quot;bte_copy (0x%lx, 0x%lx, 0x%lx, 0x%lx, 0x%lx)&bslash;n&quot;
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
id|BTE_TIME_STOP
c_func
(paren
)paren
suffix:semicolon
r_return
(paren
id|BTE_SUCCESS
)paren
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
macro_line|#ifdef CONFIG_IA64_SGI_BTE_LOCKING
(brace
id|bte_to_use
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Attempt to lock one of the BTE interfaces */
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
(paren
id|bte_to_use
op_ge
id|BTES_PER_NODE
)paren
op_logical_and
op_logical_neg
(paren
id|mode
op_amp
id|BTE_WACQUIRE
)paren
)paren
(brace
id|BTE_TIME_STOP
c_func
(paren
)paren
suffix:semicolon
r_return
(paren
id|BTEFAIL_NOTAVAIL
)paren
suffix:semicolon
)brace
multiline_comment|/* Wait until a bte is available. */
)brace
r_while
c_loop
(paren
id|bte_to_use
op_ge
id|BTES_PER_NODE
)paren
suffix:semicolon
id|bte
op_assign
id|pda.cpu_bte_if
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
macro_line|#else
multiline_comment|/* Assuming one BTE per CPU. */
id|bte
op_assign
id|pda-&gt;cpu_bte_if
(braket
l_int|0
)braket
suffix:semicolon
macro_line|#endif /* CONFIG_IA64_SGI_BTE_LOCKING */
multiline_comment|/*&n;&t; * The following are removed for optimization but is&n;&t; * available in the event that the SHUB exhibits&n;&t; * notification problems similar to the hub, bedrock et al.&n;&t; *&n;&t; * bte-&gt;mostRecentSrc = src;&n;&t; * bte-&gt;mostRecentDest = dest;&n;&t; * bte-&gt;mostRecentLen = len;&n;&t; * bte-&gt;mostRecentMode = mode;&n;&t; */
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
id|BTE_PRINTKV
c_func
(paren
(paren
l_string|&quot;Calculated transfer size of %d cache lines&bslash;n&quot;
comma
id|transfer_size
)paren
)paren
suffix:semicolon
multiline_comment|/* Initialize the notification to a known value. */
op_star
id|bte-&gt;most_rcnt_na
op_assign
op_minus
l_int|1L
suffix:semicolon
id|BTE_PRINTKV
c_func
(paren
(paren
l_string|&quot;Before, status is 0x%lx and notify is 0x%lx&bslash;n&quot;
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
multiline_comment|/* Set the status reg busy bit and transfer length */
id|BTE_PRINTKV
c_func
(paren
(paren
l_string|&quot;IBLS - HUB_S(0x%lx, 0x%lx)&bslash;n&quot;
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
l_string|&quot;IBSA - HUB_S(0x%lx, 0x%lx)&bslash;n&quot;
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
l_string|&quot;IBDA - HUB_S(0x%lx, 0x%lx)&bslash;n&quot;
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
l_string|&quot;IBNA - HUB_S(0x%lx, 0x%lx)&bslash;n&quot;
comma
id|BTEREG_NOTIF_ADDR
comma
(paren
id|TO_PHYS
c_func
(paren
id|__pa
c_func
(paren
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
id|__pa
c_func
(paren
id|bte-&gt;most_rcnt_na
)paren
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* Initiate the transfer */
id|BTE_PRINTKV
c_func
(paren
(paren
l_string|&quot;IBCT - HUB_S(0x%lx, 0x%lx)&bslash;n&quot;
comma
id|BTEREG_CTRL_ADDR
comma
id|mode
)paren
)paren
suffix:semicolon
id|BTE_TIME_XFR_START
c_func
(paren
)paren
suffix:semicolon
id|HUB_S
c_func
(paren
id|BTEREG_CTRL_ADDR
comma
id|BTE_VLD_MODE
c_func
(paren
id|mode
)paren
)paren
suffix:semicolon
id|BTE_PRINTKV
c_func
(paren
(paren
l_string|&quot;Initiated, status is 0x%lx and notify is 0x%lx&bslash;n&quot;
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
id|notification
op_eq
l_int|NULL
)paren
(brace
multiline_comment|/*&n;&t;&t; * Calculate our timeout&n;&t;&t; *&n;&t;&t; * What are we doing here?  We are trying to determine&n;&t;&t; * the fastest time the BTE could have transfered our&n;&t;&t; * block of data.  By takine the clock frequency (ticks/sec)&n;&t;&t; * divided by the BTE MaxT Transfer Rate (lines/sec)&n;&t;&t; * times the transfer size (lines), we get a tick&n;&t;&t; * offset from current time that the transfer should&n;&t;&t; * complete.&n;&t;&t; *&n;&t;&t; * Why do this?  We are watching for a notification&n;&t;&t; * failure from the BTE.  This behaviour has been&n;&t;&t; * seen in the SN0 and SN1 hardware on rare circumstances&n;&t;&t; * and is expected in SN2.  By checking at the&n;&t;&t; * ideal transfer timeout, we minimize our time&n;&t;&t; * delay from hardware completing our request and&n;&t;&t; * our detecting the failure.&n;&t;&t; */
id|bte-&gt;ideal_xfr_tmo
op_assign
id|BTE_IDEAL_TMO
c_func
(paren
id|transfer_size
)paren
suffix:semicolon
r_while
c_loop
(paren
id|bte-&gt;notify
op_eq
op_minus
l_int|1UL
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Notification Workaround: When the max&n;&t;&t;&t; * theoretical time has elapsed, read the hub&n;&t;&t;&t; * status register into the notification area.&n;&t;&t;&t; * This fakes the shub performing the copy.&n;&t;&t;&t; */
id|BTE_PRINTKV
c_func
(paren
(paren
l_string|&quot;  Timing.  IBLS = 0x%lx, &quot;
l_string|&quot;notify= 0x%lx&bslash;n&quot;
comma
id|HUB_L
c_func
(paren
id|BTEREG_LNSTAT_ADDR
)paren
comma
id|bte-&gt;notify
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|time_after
c_func
(paren
id|jiffies
comma
id|bte-&gt;ideal_xfr_tmo
)paren
)paren
(brace
id|lines_remaining
op_assign
id|HUB_L
c_func
(paren
id|BTEREG_LNSTAT_ADDR
)paren
op_amp
id|BTE_LEN_MASK
suffix:semicolon
id|bte-&gt;ideal_xfr_tmo_cnt
op_increment
suffix:semicolon
id|bte-&gt;ideal_xfr_tmo
op_assign
id|BTE_IDEAL_TMO
c_func
(paren
id|lines_remaining
)paren
suffix:semicolon
id|BTE_PRINTKV
c_func
(paren
(paren
l_string|&quot;  Timeout.  cpu %d &quot;
l_string|&quot;IBLS = 0x%lx, &quot;
l_string|&quot;notify= 0x%lx, &quot;
l_string|&quot;Lines remaining = %d. &quot;
l_string|&quot;New timeout = %d.&bslash;n&quot;
comma
id|smp_processor_id
c_func
(paren
)paren
comma
id|HUB_L
c_func
(paren
id|BTEREG_LNSTAT_ADDR
)paren
comma
id|bte-&gt;notify
comma
id|lines_remaining
comma
id|bte-&gt;ideal_xfr_tmo
)paren
)paren
suffix:semicolon
)brace
)brace
id|BTE_PRINTKV
c_func
(paren
(paren
l_string|&quot; Delay Done.  IBLS = 0x%lx, notify= 0x%lx&bslash;n&quot;
comma
id|HUB_L
c_func
(paren
id|BTEREG_LNSTAT_ADDR
)paren
comma
id|bte-&gt;notify
)paren
)paren
suffix:semicolon
id|BTE_TIME_XFR_STOP
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bte-&gt;notify
op_amp
id|IBLS_ERROR
)paren
(brace
multiline_comment|/* &gt;&gt;&gt; Need to do real error checking. */
id|transfer_size
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef CONFIG_IA64_SGI_BTE_LOCKING
id|spin_unlock
c_func
(paren
op_amp
(paren
id|bte-&gt;spinlock
)paren
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_IA64_SGI_BTE_LOCKING */
id|BTE_PRINTKV
c_func
(paren
(paren
l_string|&quot;Erroring status is 0x%lx and &quot;
l_string|&quot;notify is 0x%lx&bslash;n&quot;
comma
id|HUB_L
c_func
(paren
id|BTEREG_LNSTAT_ADDR
)paren
comma
id|bte-&gt;notify
)paren
)paren
suffix:semicolon
id|BTE_TIME_STOP
c_func
(paren
)paren
suffix:semicolon
id|bte-&gt;notify
op_assign
l_int|0L
suffix:semicolon
r_return
(paren
id|BTEFAIL_ERROR
)paren
suffix:semicolon
)brace
)brace
macro_line|#ifdef CONFIG_IA64_SGI_BTE_LOCKING
id|spin_unlock
c_func
(paren
op_amp
(paren
id|bte-&gt;spinlock
)paren
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_IA64_SGI_BTE_LOCKING */
id|BTE_TIME_STOP
c_func
(paren
)paren
suffix:semicolon
id|BTE_PRINTKV
c_func
(paren
(paren
l_string|&quot;Returning status is 0x%lx and notify is 0x%lx&bslash;n&quot;
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
(paren
id|BTE_SUCCESS
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Define the bte_unaligned_copy as an extern.&n; */
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
multiline_comment|/*&n; * The following is the prefered way of calling bte_unaligned_copy&n; * If the copy is fully cache line aligned, then bte_copy is&n; * used instead.  Since bte_copy is inlined, this saves a call&n; * stack.  NOTE: bte_copy is called synchronously and does block&n; * until the transfer is complete.  In order to get the asynch&n; * version of bte_copy, you must perform this check yourself.&n; */
DECL|macro|BTE_UNALIGNED_COPY
mdefine_line|#define BTE_UNALIGNED_COPY(src, dest, len, mode)&t;&t;&t;&bslash;&n;&t;(((len &amp; L1_CACHE_MASK) || (src &amp; L1_CACHE_MASK) ||&t;&t;&bslash;&n;&t;  (dest &amp; L1_CACHE_MASK)) ?&t;&t;&t;&t;&t;&bslash;&n;&t;&t;bte_unaligned_copy(src, dest, len, mode) :&t;&t;&bslash;&n;&t;&t;bte_copy(src, dest, len, mode, NULL))
macro_line|#endif /* _ASM_IA64_SN_BTE_COPY_H */
eof
