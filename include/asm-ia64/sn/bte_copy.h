multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; * &n; * Copyright (c) 2001-2002 Silicon Graphics, Inc.  All rights reserved.&n; */
macro_line|#ifndef _ASM_IA64_SN_BTE_COPY_H
DECL|macro|_ASM_IA64_SN_BTE_COPY_H
mdefine_line|#define _ASM_IA64_SN_BTE_COPY_H
macro_line|#ident &quot;$Revision: $&quot;
macro_line|#include &lt;asm/sn/bte.h&gt;
macro_line|#include &lt;asm/sn/sgi.h&gt;
macro_line|#include &lt;asm/sn/pda.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
multiline_comment|/*&n; * BTE_LOCKING support - Undefining the following line will&n; * adapt the bte_copy code to support one bte per cpu in&n; * synchronous mode.  Even if bte_copy is called with a&n; * notify address, the bte will spin and wait for the transfer&n; * to complete.  By defining the following, spin_locks and&n; * busy checks are placed around the initiation of a BTE&n; * transfer and multiple bte&squot;s per cpu are supported.&n; */
DECL|macro|CONFIG_IA64_SGI_BTE_LOCKING
mdefine_line|#define CONFIG_IA64_SGI_BTE_LOCKING 1
multiline_comment|/*&n; * Some macros to simplify reading.&n; *&n; * Start with macros to locate the BTE control registers.&n; */
DECL|macro|BTEREG_LNSTAT_ADDR
mdefine_line|#define BTEREG_LNSTAT_ADDR (bte-&gt;bte_base_addr)
DECL|macro|BTEREG_SOURCE_ADDR
mdefine_line|#define BTEREG_SOURCE_ADDR (bte-&gt;bte_base_addr + IIO_IBSA0 - IIO_IBLS0)
DECL|macro|BTEREG_DEST_ADDR
mdefine_line|#define BTEREG_DEST_ADDR (bte-&gt;bte_base_addr + IIO_IBDA0 - IIO_IBLS0)
DECL|macro|BTEREG_CTRL_ADDR
mdefine_line|#define BTEREG_CTRL_ADDR (bte-&gt;bte_base_addr + IIO_IBCT0 - IIO_IBLS0)
DECL|macro|BTEREG_NOTIF_ADDR
mdefine_line|#define BTEREG_NOTIF_ADDR (bte-&gt;bte_base_addr + IIO_IBNA0 - IIO_IBLS0)
multiline_comment|/* Some macros to force the IBCT0 value valid. */
DECL|macro|BTE_VALID_MODES
mdefine_line|#define BTE_VALID_MODES BTE_NOTIFY
DECL|macro|BTE_VLD_MODE
mdefine_line|#define BTE_VLD_MODE(x) (x &amp; BTE_VALID_MODES)
singleline_comment|// #define DEBUG_BTE
singleline_comment|// #define DEBUG_BTE_VERBOSE
singleline_comment|// #define DEBUG_TIME_BTE
macro_line|#ifdef DEBUG_BTE
DECL|macro|DPRINTK
macro_line|#  define DPRINTK(x) printk x&t;
singleline_comment|// Terse
macro_line|#  ifdef DEBUG_BTE_VERBOSE
DECL|macro|DPRINTKV
macro_line|#    define DPRINTKV(x) printk x&t;
singleline_comment|// Verbose
macro_line|#  else
DECL|macro|DPRINTKV
macro_line|#    define DPRINTKV(x)
macro_line|#  endif
macro_line|#else
DECL|macro|DPRINTK
macro_line|#  define DPRINTK(x)
DECL|macro|DPRINTKV
macro_line|#  define DPRINTKV(x)
macro_line|#endif
macro_line|#ifdef DEBUG_TIME_BTE
r_extern
id|u64
id|BteSetupTime
suffix:semicolon
r_extern
id|u64
id|BteTransferTime
suffix:semicolon
r_extern
id|u64
id|BteTeardownTime
suffix:semicolon
r_extern
id|u64
id|BteExecuteTime
suffix:semicolon
macro_line|#endif
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
macro_line|#endif
macro_line|#ifdef DEBUG_TIME_BTE
id|u64
id|invokeTime
op_assign
l_int|0
suffix:semicolon
id|u64
id|completeTime
op_assign
l_int|0
suffix:semicolon
id|u64
id|xferStartTime
op_assign
l_int|0
suffix:semicolon
id|u64
id|xferCompleteTime
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
id|u64
id|transferSize
suffix:semicolon
id|bteinfo_t
op_star
id|bte
suffix:semicolon
macro_line|#ifdef DEBUG_TIME_BTE
id|invokeTime
op_assign
id|ia64_get_itc
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|DPRINTK
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
op_star
id|pda.cpubte
(braket
id|bte_to_use
)braket
op_member_access_from_pointer
id|mostRecentNotification
op_amp
id|IBLS_BUSY
)paren
op_logical_and
(paren
op_logical_neg
(paren
id|spin_trylock
(paren
op_amp
(paren
id|pda.cpubte
(braket
id|bte_to_use
)braket
op_member_access_from_pointer
id|spinlock
)paren
)paren
)paren
)paren
op_logical_and
(paren
id|bte_to_use
OL
id|BTES_PER_NODE
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
id|pda.cpubte
(braket
id|bte_to_use
)braket
suffix:semicolon
id|DPRINTKV
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
id|pda.cpubte
(braket
l_int|0
)braket
suffix:semicolon
macro_line|#endif
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
id|bte-&gt;mostRecentNotification
op_assign
op_amp
id|bte-&gt;notify
suffix:semicolon
)brace
r_else
(brace
id|bte-&gt;mostRecentNotification
op_assign
id|notification
suffix:semicolon
)brace
multiline_comment|/* Calculate the number of cache lines to transfer. */
id|transferSize
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
id|DPRINTKV
c_func
(paren
(paren
l_string|&quot;Calculated transfer size of %d cache lines&bslash;n&quot;
comma
id|transferSize
)paren
)paren
suffix:semicolon
multiline_comment|/* Initialize the notification to a known value. */
op_star
id|bte-&gt;mostRecentNotification
op_assign
op_minus
l_int|1L
suffix:semicolon
id|DPRINTKV
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
id|bte-&gt;mostRecentNotification
)paren
)paren
suffix:semicolon
multiline_comment|/* Set the status reg busy bit and transfer length */
id|DPRINTKV
c_func
(paren
(paren
l_string|&quot;IBLS - HUB_S(0x%lx, 0x%lx)&bslash;n&quot;
comma
id|BTEREG_LNSTAT_ADDR
comma
id|IBLS_BUSY
op_or
id|transferSize
)paren
)paren
suffix:semicolon
id|HUB_S
c_func
(paren
id|BTEREG_LNSTAT_ADDR
comma
id|IBLS_BUSY
op_or
id|transferSize
)paren
suffix:semicolon
id|DPRINTKV
c_func
(paren
(paren
l_string|&quot;After setting status, status is 0x%lx and notify is 0x%lx&bslash;n&quot;
comma
id|HUB_L
c_func
(paren
id|BTEREG_LNSTAT_ADDR
)paren
comma
op_star
id|bte-&gt;mostRecentNotification
)paren
)paren
suffix:semicolon
multiline_comment|/* Set the source and destination registers */
id|DPRINTKV
c_func
(paren
(paren
l_string|&quot;IBSA - HUB_S(0x%lx, 0x%lx)&bslash;n&quot;
comma
id|BTEREG_SOURCE_ADDR
comma
id|src
)paren
)paren
suffix:semicolon
id|HUB_S
c_func
(paren
id|BTEREG_SOURCE_ADDR
comma
id|src
)paren
suffix:semicolon
id|DPRINTKV
c_func
(paren
(paren
l_string|&quot;IBDA - HUB_S(0x%lx, 0x%lx)&bslash;n&quot;
comma
id|BTEREG_DEST_ADDR
comma
id|dest
)paren
)paren
suffix:semicolon
id|HUB_S
c_func
(paren
id|BTEREG_DEST_ADDR
comma
id|dest
)paren
suffix:semicolon
multiline_comment|/* Set the notification register */
id|DPRINTKV
c_func
(paren
(paren
l_string|&quot;IBNA - HUB_S(0x%lx, 0x%lx)&bslash;n&quot;
comma
id|BTEREG_NOTIF_ADDR
comma
id|__pa
c_func
(paren
id|bte-&gt;mostRecentNotification
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
id|__pa
c_func
(paren
id|bte-&gt;mostRecentNotification
)paren
)paren
)paren
suffix:semicolon
id|DPRINTKV
c_func
(paren
(paren
l_string|&quot;Set Notify, status is 0x%lx and notify is 0x%lx&bslash;n&quot;
comma
id|HUB_L
c_func
(paren
id|BTEREG_LNSTAT_ADDR
)paren
comma
op_star
id|bte-&gt;mostRecentNotification
)paren
)paren
suffix:semicolon
multiline_comment|/* Initiate the transfer */
id|DPRINTKV
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
macro_line|#ifdef DEBUG_TIME_BTE
id|xferStartTime
op_assign
id|ia64_get_itc
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
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
id|DPRINTKV
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
id|bte-&gt;mostRecentNotification
)paren
)paren
suffix:semicolon
singleline_comment|// &gt;&gt;&gt; Temporarily work around not getting a notification
singleline_comment|// from medusa.
singleline_comment|// *bte-&gt;mostRecentNotification = HUB_L(bte-&gt;bte_base_addr);
r_if
c_cond
(paren
id|notification
op_eq
l_int|NULL
)paren
(brace
multiline_comment|/*&n;&t;&t; * Calculate our timeout&n;&t;&t; *&n;&t;&t; * What are we doing here?  We are trying to determine&n;&t;&t; * the fastest time the BTE could have transfered our&n;&t;&t; * block of data.  By takine the clock frequency (ticks/sec)&n;&t;&t; * divided by the BTE MaxT Transfer Rate (lines/sec)&n;&t;&t; * times the transfer size (lines), we get a tick&n;&t;&t; * offset from current time that the transfer should&n;&t;&t; * complete.&n;&t;&t; *&n;&t;&t; * Why do this?  We are watching for a notification&n;&t;&t; * failure from the BTE.  This behaviour has been&n;&t;&t; * seen in the SN0 and SN1 hardware on rare circumstances&n;&t;&t; * and is expected in SN2.  By checking at the&n;&t;&t; * ideal transfer timeout, we minimize our time&n;&t;&t; * delay from hardware completing our request and&n;&t;&t; * our detecting the failure.&n;&t;&t; */
id|bte-&gt;idealTransferTimeout
op_assign
id|jiffies
op_plus
(paren
id|HZ
op_div
id|BTE_MAXT_LINES_PER_SECOND
op_star
id|transferSize
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|IBLS_BUSY
op_amp
id|bte-&gt;notify
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Notification Workaround: When the max&n;&t;&t;&t; * theoretical time has elapsed, read the hub&n;&t;&t;&t; * status register into the notification area.&n;&t;&t;&t; * This fakes the shub performing the copy.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|jiffies
OG
id|bte-&gt;idealTransferTimeout
)paren
(brace
id|bte-&gt;notify
op_assign
id|HUB_L
c_func
(paren
id|bte-&gt;bte_base_addr
)paren
suffix:semicolon
id|bte-&gt;idealTransferTimeoutReached
op_increment
suffix:semicolon
id|bte-&gt;idealTransferTimeout
op_assign
id|jiffies
op_plus
(paren
id|HZ
op_div
id|BTE_MAXT_LINES_PER_SECOND
op_star
(paren
id|bte-&gt;notify
op_amp
id|BTE_LEN_MASK
)paren
)paren
suffix:semicolon
)brace
)brace
macro_line|#ifdef DEBUG_TIME_BTE
id|xferCompleteTime
op_assign
id|ia64_get_itc
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|bte-&gt;notify
op_amp
id|IBLS_ERROR
)paren
(brace
multiline_comment|/* &gt;&gt;&gt; Need to do real error checking. */
id|transferSize
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
macro_line|#endif
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
macro_line|#endif
macro_line|#ifdef DEBUG_TIME_BTE
id|completeTime
op_assign
id|ia64_get_itc
c_func
(paren
)paren
suffix:semicolon
id|BteSetupTime
op_assign
id|xferStartTime
op_minus
id|invokeTime
suffix:semicolon
id|BteTransferTime
op_assign
id|xferCompleteTime
op_minus
id|xferStartTime
suffix:semicolon
id|BteTeardownTime
op_assign
id|completeTime
op_minus
id|xferCompleteTime
suffix:semicolon
id|BteExecuteTime
op_assign
id|completeTime
op_minus
id|invokeTime
suffix:semicolon
macro_line|#endif
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
comma
r_char
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * The following is the prefered way of calling bte_unaligned_copy&n; * If the copy is fully cache line aligned, then bte_copy is&n; * used instead.  Since bte_copy is inlined, this saves a call&n; * stack.  NOTE: bte_copy is called synchronously and does block&n; * until the transfer is complete.  In order to get the asynch&n; * version of bte_copy, you must perform this check yourself.&n; */
DECL|macro|BTE_UNALIGNED_COPY
mdefine_line|#define BTE_UNALIGNED_COPY(src, dest, len, mode, bteBlock) &bslash;&n;&t;if ((len &amp; L1_CACHE_MASK) || &bslash;&n;&t;    (src &amp; L1_CACHE_MASK) || &bslash;&n;&t;    (dest &amp; L1_CACHE_MASK)) { &bslash;&n;&t;&t;bte_unaligned_copy (src, dest, len, mode, bteBlock); &bslash;&n;&t;} else { &bslash;&n;&t;&t;bte_copy(src, dest, len, mode, NULL); &bslash;&n;&t;}
macro_line|#endif&t;&t;&t;&t;/* _ASM_IA64_SN_BTE_COPY_H */
eof
