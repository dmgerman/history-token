multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992-1997, 2000-2003 Silicon Graphics, Inc.  All Rights Reserved.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/hw_irq.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/sn/sgi.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/sn/iograph.h&gt;
macro_line|#include &lt;asm/sn/hcl.h&gt;
macro_line|#include &lt;asm/sn/labelcl.h&gt;
macro_line|#include &lt;asm/sn/io.h&gt;
macro_line|#include &lt;asm/sn/sn_private.h&gt;
macro_line|#include &lt;asm/sn/klconfig.h&gt;
macro_line|#include &lt;asm/sn/sn_cpuid.h&gt;
macro_line|#include &lt;asm/sn/pci/pciio.h&gt;
macro_line|#include &lt;asm/sn/pci/pcibr.h&gt;
macro_line|#include &lt;asm/sn/xtalk/xtalk.h&gt;
macro_line|#include &lt;asm/sn/pci/pcibr_private.h&gt;
macro_line|#include &lt;asm/sn/intr.h&gt;
macro_line|#include &lt;asm/sn/sn2/shub_mmr.h&gt;
macro_line|#include &lt;asm/sn/sn2/shub_mmr_t.h&gt;
macro_line|#include &lt;asm/sal.h&gt;
macro_line|#include &lt;asm/sn/sn_sal.h&gt;
macro_line|#include &lt;asm/sn/sndrv.h&gt;
macro_line|#include &lt;asm/sn/sn2/shubio.h&gt;
DECL|macro|SHUB_NUM_ECF_REGISTERS
mdefine_line|#define SHUB_NUM_ECF_REGISTERS 8
DECL|variable|shub_perf_counts
r_static
r_uint32
id|shub_perf_counts
(braket
id|SHUB_NUM_ECF_REGISTERS
)braket
suffix:semicolon
DECL|variable|shub_perf_counts_regs
r_static
id|shubreg_t
id|shub_perf_counts_regs
(braket
id|SHUB_NUM_ECF_REGISTERS
)braket
op_assign
(brace
id|SH_PERFORMANCE_COUNTER0
comma
id|SH_PERFORMANCE_COUNTER1
comma
id|SH_PERFORMANCE_COUNTER2
comma
id|SH_PERFORMANCE_COUNTER3
comma
id|SH_PERFORMANCE_COUNTER4
comma
id|SH_PERFORMANCE_COUNTER5
comma
id|SH_PERFORMANCE_COUNTER6
comma
id|SH_PERFORMANCE_COUNTER7
)brace
suffix:semicolon
r_static
r_inline
r_void
DECL|function|shub_mmr_write
id|shub_mmr_write
c_func
(paren
id|cnodeid_t
id|cnode
comma
id|shubreg_t
id|reg
comma
r_uint64
id|val
)paren
(brace
r_int
id|nasid
op_assign
id|cnodeid_to_nasid
c_func
(paren
id|cnode
)paren
suffix:semicolon
r_volatile
r_uint64
op_star
id|addr
op_assign
(paren
r_uint64
op_star
)paren
(paren
id|GLOBAL_MMR_ADDR
c_func
(paren
id|nasid
comma
id|reg
)paren
)paren
suffix:semicolon
op_star
id|addr
op_assign
id|val
suffix:semicolon
id|__ia64_mf_a
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|shub_mmr_write_iospace
id|shub_mmr_write_iospace
c_func
(paren
id|cnodeid_t
id|cnode
comma
id|shubreg_t
id|reg
comma
r_uint64
id|val
)paren
(brace
r_int
id|nasid
op_assign
id|cnodeid_to_nasid
c_func
(paren
id|cnode
)paren
suffix:semicolon
id|REMOTE_HUB_S
c_func
(paren
id|nasid
comma
id|reg
comma
id|val
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|shub_mmr_write32
id|shub_mmr_write32
c_func
(paren
id|cnodeid_t
id|cnode
comma
id|shubreg_t
id|reg
comma
r_uint32
id|val
)paren
(brace
r_int
id|nasid
op_assign
id|cnodeid_to_nasid
c_func
(paren
id|cnode
)paren
suffix:semicolon
r_volatile
r_uint32
op_star
id|addr
op_assign
(paren
r_uint32
op_star
)paren
(paren
id|GLOBAL_MMR_ADDR
c_func
(paren
id|nasid
comma
id|reg
)paren
)paren
suffix:semicolon
op_star
id|addr
op_assign
id|val
suffix:semicolon
id|__ia64_mf_a
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
r_inline
r_uint64
DECL|function|shub_mmr_read
id|shub_mmr_read
c_func
(paren
id|cnodeid_t
id|cnode
comma
id|shubreg_t
id|reg
)paren
(brace
r_int
id|nasid
op_assign
id|cnodeid_to_nasid
c_func
(paren
id|cnode
)paren
suffix:semicolon
r_volatile
r_uint64
id|val
suffix:semicolon
id|val
op_assign
op_star
(paren
r_uint64
op_star
)paren
(paren
id|GLOBAL_MMR_ADDR
c_func
(paren
id|nasid
comma
id|reg
)paren
)paren
suffix:semicolon
id|__ia64_mf_a
c_func
(paren
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
r_static
r_inline
r_uint64
DECL|function|shub_mmr_read_iospace
id|shub_mmr_read_iospace
c_func
(paren
id|cnodeid_t
id|cnode
comma
id|shubreg_t
id|reg
)paren
(brace
r_int
id|nasid
op_assign
id|cnodeid_to_nasid
c_func
(paren
id|cnode
)paren
suffix:semicolon
r_return
id|REMOTE_HUB_L
c_func
(paren
id|nasid
comma
id|reg
)paren
suffix:semicolon
)brace
r_static
r_inline
r_uint32
DECL|function|shub_mmr_read32
id|shub_mmr_read32
c_func
(paren
id|cnodeid_t
id|cnode
comma
id|shubreg_t
id|reg
)paren
(brace
r_int
id|nasid
op_assign
id|cnodeid_to_nasid
c_func
(paren
id|cnode
)paren
suffix:semicolon
r_volatile
r_uint32
id|val
suffix:semicolon
id|val
op_assign
op_star
(paren
r_uint32
op_star
)paren
(paren
id|GLOBAL_MMR_ADDR
c_func
(paren
id|nasid
comma
id|reg
)paren
)paren
suffix:semicolon
id|__ia64_mf_a
c_func
(paren
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
r_static
r_int
DECL|function|reset_shub_stats
id|reset_shub_stats
c_func
(paren
id|cnodeid_t
id|cnode
)paren
(brace
r_int
id|i
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
id|SHUB_NUM_ECF_REGISTERS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|shub_perf_counts
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
id|shub_mmr_write32
c_func
(paren
id|cnode
comma
id|shub_perf_counts_regs
(braket
id|i
)braket
comma
l_int|0
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|configure_shub_stats
id|configure_shub_stats
c_func
(paren
id|cnodeid_t
id|cnode
comma
r_int
r_int
id|arg
)paren
(brace
r_uint64
op_star
id|p
op_assign
(paren
r_uint64
op_star
)paren
id|arg
suffix:semicolon
r_uint64
id|i
suffix:semicolon
r_uint64
id|regcnt
suffix:semicolon
r_uint64
id|regval
(braket
l_int|2
)braket
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
(paren
r_void
op_star
)paren
op_amp
id|regcnt
comma
id|p
comma
r_sizeof
(paren
id|regcnt
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_for
c_loop
(paren
id|p
op_increment
comma
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|regcnt
suffix:semicolon
id|i
op_increment
comma
id|p
op_add_assign
l_int|2
)paren
(brace
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
(paren
r_void
op_star
)paren
id|regval
comma
(paren
r_void
op_star
)paren
id|p
comma
r_sizeof
(paren
id|regval
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|regval
(braket
l_int|0
)braket
op_amp
l_int|0x7
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Error: configure_shub_stats: unaligned address 0x%016lx&bslash;n&quot;
comma
id|regval
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|shub_mmr_write
c_func
(paren
id|cnode
comma
(paren
id|shubreg_t
)paren
id|regval
(braket
l_int|0
)braket
comma
id|regval
(braket
l_int|1
)braket
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|capture_shub_stats
id|capture_shub_stats
c_func
(paren
id|cnodeid_t
id|cnode
comma
r_uint32
op_star
id|counts
)paren
(brace
r_int
id|i
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
id|SHUB_NUM_ECF_REGISTERS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|counts
(braket
id|i
)braket
op_assign
id|shub_mmr_read32
c_func
(paren
id|cnode
comma
id|shub_perf_counts_regs
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|shubstats_ioctl
id|shubstats_ioctl
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
id|cnodeid_t
id|cnode
suffix:semicolon
r_uint64
id|longarg
suffix:semicolon
r_int
id|nasid
suffix:semicolon
id|cnode
op_assign
(paren
id|cnodeid_t
)paren
id|file-&gt;f_dentry-&gt;d_fsdata
suffix:semicolon
r_if
c_cond
(paren
id|cnode
OL
l_int|0
op_logical_or
id|cnode
op_ge
id|numnodes
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|SNDRV_SHUB_CONFIGURE
suffix:colon
r_return
id|configure_shub_stats
c_func
(paren
id|cnode
comma
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SNDRV_SHUB_RESETSTATS
suffix:colon
id|reset_shub_stats
c_func
(paren
id|cnode
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SNDRV_SHUB_INFOSIZE
suffix:colon
id|longarg
op_assign
r_sizeof
(paren
id|shub_perf_counts
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_void
op_star
)paren
id|arg
comma
op_amp
id|longarg
comma
r_sizeof
(paren
id|longarg
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|SNDRV_SHUB_GETSTATS
suffix:colon
id|capture_shub_stats
c_func
(paren
id|cnode
comma
id|shub_perf_counts
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_void
op_star
)paren
id|arg
comma
id|shub_perf_counts
comma
r_sizeof
(paren
id|shub_perf_counts
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|SNDRV_SHUB_GETNASID
suffix:colon
id|nasid
op_assign
id|cnodeid_to_nasid
c_func
(paren
id|cnode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_void
op_star
)paren
id|arg
comma
op_amp
id|nasid
comma
r_sizeof
(paren
id|nasid
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|shub_mon_fops
r_struct
id|file_operations
id|shub_mon_fops
op_assign
(brace
dot
id|ioctl
op_assign
id|shubstats_ioctl
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * &quot;linkstatd&quot; kernel thread to export SGI Numalink&n; * stats via /proc/sgi_sn/linkstats&n; */
DECL|struct|s_linkstats
r_static
r_struct
id|s_linkstats
(brace
DECL|member|hs_ni_sn_errors
r_uint64
id|hs_ni_sn_errors
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|hs_ni_cb_errors
r_uint64
id|hs_ni_cb_errors
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|hs_ni_retry_errors
r_uint64
id|hs_ni_retry_errors
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|hs_ii_up
r_int
id|hs_ii_up
suffix:semicolon
DECL|member|hs_ii_sn_errors
r_uint64
id|hs_ii_sn_errors
suffix:semicolon
DECL|member|hs_ii_cb_errors
r_uint64
id|hs_ii_cb_errors
suffix:semicolon
DECL|member|hs_ii_retry_errors
r_uint64
id|hs_ii_retry_errors
suffix:semicolon
DECL|variable|sn_linkstats
)brace
op_star
id|sn_linkstats
suffix:semicolon
DECL|variable|sn_linkstats_lock
r_static
id|spinlock_t
id|sn_linkstats_lock
suffix:semicolon
DECL|variable|sn_linkstats_starttime
r_static
r_int
r_int
id|sn_linkstats_starttime
suffix:semicolon
DECL|variable|sn_linkstats_samples
r_static
r_int
r_int
id|sn_linkstats_samples
suffix:semicolon
DECL|variable|sn_linkstats_overflows
r_static
r_int
r_int
id|sn_linkstats_overflows
suffix:semicolon
DECL|variable|sn_linkstats_update_msecs
r_static
r_int
r_int
id|sn_linkstats_update_msecs
suffix:semicolon
r_void
DECL|function|sn_linkstats_reset
id|sn_linkstats_reset
c_func
(paren
r_int
r_int
id|msecs
)paren
(brace
r_int
id|cnode
suffix:semicolon
r_uint64
id|iio_wstat
suffix:semicolon
r_uint64
id|llp_csr_reg
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|sn_linkstats_lock
)paren
suffix:semicolon
id|memset
c_func
(paren
id|sn_linkstats
comma
l_int|0
comma
id|numnodes
op_star
r_sizeof
(paren
r_struct
id|s_linkstats
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|cnode
op_assign
l_int|0
suffix:semicolon
id|cnode
OL
id|numnodes
suffix:semicolon
id|cnode
op_increment
)paren
(brace
id|shub_mmr_write
c_func
(paren
id|cnode
comma
id|SH_NI0_LLP_ERR
comma
l_int|0L
)paren
suffix:semicolon
id|shub_mmr_write
c_func
(paren
id|cnode
comma
id|SH_NI1_LLP_ERR
comma
l_int|0L
)paren
suffix:semicolon
id|shub_mmr_write_iospace
c_func
(paren
id|cnode
comma
id|IIO_LLP_LOG
comma
l_int|0L
)paren
suffix:semicolon
multiline_comment|/* zero the II retry counter */
id|iio_wstat
op_assign
id|shub_mmr_read_iospace
c_func
(paren
id|cnode
comma
id|IIO_WSTAT
)paren
suffix:semicolon
id|iio_wstat
op_and_assign
l_int|0xffffffffff00ffff
suffix:semicolon
multiline_comment|/* bits 23:16 */
id|shub_mmr_write_iospace
c_func
(paren
id|cnode
comma
id|IIO_WSTAT
comma
id|iio_wstat
)paren
suffix:semicolon
multiline_comment|/* Check if the II xtalk link is working */
id|llp_csr_reg
op_assign
id|shub_mmr_read_iospace
c_func
(paren
id|cnode
comma
id|IIO_LLP_CSR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|llp_csr_reg
op_amp
id|IIO_LLP_CSR_IS_UP
)paren
id|sn_linkstats
(braket
id|cnode
)braket
dot
id|hs_ii_up
op_assign
l_int|1
suffix:semicolon
)brace
id|sn_linkstats_update_msecs
op_assign
id|msecs
suffix:semicolon
id|sn_linkstats_samples
op_assign
l_int|0
suffix:semicolon
id|sn_linkstats_overflows
op_assign
l_int|0
suffix:semicolon
id|sn_linkstats_starttime
op_assign
id|jiffies
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|sn_linkstats_lock
)paren
suffix:semicolon
)brace
r_int
DECL|function|linkstatd_thread
id|linkstatd_thread
c_func
(paren
r_void
op_star
id|unused
)paren
(brace
r_int
id|cnode
suffix:semicolon
r_int
id|overflows
suffix:semicolon
r_uint64
id|reg
(braket
l_int|2
)braket
suffix:semicolon
r_uint64
id|iio_wstat
op_assign
l_int|0L
suffix:semicolon
id|ii_illr_u_t
id|illr
suffix:semicolon
r_struct
id|s_linkstats
op_star
id|lsp
suffix:semicolon
r_struct
id|task_struct
op_star
id|tsk
op_assign
id|current
suffix:semicolon
id|daemonize
c_func
(paren
l_string|&quot;linkstatd&quot;
)paren
suffix:semicolon
id|set_user_nice
c_func
(paren
id|tsk
comma
l_int|19
)paren
suffix:semicolon
id|sigfillset
c_func
(paren
op_amp
id|tsk-&gt;blocked
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|tsk-&gt;comm
comma
l_string|&quot;linkstatd&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
id|schedule_timeout
c_func
(paren
id|sn_linkstats_update_msecs
op_star
id|HZ
op_div
l_int|1000
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|sn_linkstats_lock
)paren
suffix:semicolon
id|overflows
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|lsp
op_assign
id|sn_linkstats
comma
id|cnode
op_assign
l_int|0
suffix:semicolon
id|cnode
OL
id|numnodes
suffix:semicolon
id|cnode
op_increment
comma
id|lsp
op_increment
)paren
(brace
id|reg
(braket
l_int|0
)braket
op_assign
id|shub_mmr_read
c_func
(paren
id|cnode
comma
id|SH_NI0_LLP_ERR
)paren
suffix:semicolon
id|reg
(braket
l_int|1
)braket
op_assign
id|shub_mmr_read
c_func
(paren
id|cnode
comma
id|SH_NI1_LLP_ERR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lsp-&gt;hs_ii_up
)paren
(brace
id|illr
op_assign
(paren
id|ii_illr_u_t
)paren
id|shub_mmr_read_iospace
c_func
(paren
id|cnode
comma
id|IIO_LLP_LOG
)paren
suffix:semicolon
id|iio_wstat
op_assign
id|shub_mmr_read_iospace
c_func
(paren
id|cnode
comma
id|IIO_WSTAT
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|overflows
op_logical_and
(paren
(paren
id|reg
(braket
l_int|0
)braket
op_amp
id|SH_NI0_LLP_ERR_RX_SN_ERR_COUNT_MASK
)paren
op_eq
id|SH_NI0_LLP_ERR_RX_SN_ERR_COUNT_MASK
op_logical_or
(paren
id|reg
(braket
l_int|0
)braket
op_amp
id|SH_NI0_LLP_ERR_RX_CB_ERR_COUNT_MASK
)paren
op_eq
id|SH_NI0_LLP_ERR_RX_CB_ERR_COUNT_MASK
op_logical_or
(paren
id|reg
(braket
l_int|1
)braket
op_amp
id|SH_NI1_LLP_ERR_RX_SN_ERR_COUNT_MASK
)paren
op_eq
id|SH_NI1_LLP_ERR_RX_SN_ERR_COUNT_MASK
op_logical_or
(paren
id|reg
(braket
l_int|1
)braket
op_amp
id|SH_NI1_LLP_ERR_RX_CB_ERR_COUNT_MASK
)paren
op_eq
id|SH_NI1_LLP_ERR_RX_CB_ERR_COUNT_MASK
op_logical_or
(paren
id|lsp-&gt;hs_ii_up
op_logical_and
id|illr.ii_illr_fld_s.i_sn_cnt
op_eq
id|IIO_LLP_SN_MAX
)paren
op_logical_or
(paren
id|lsp-&gt;hs_ii_up
op_logical_and
id|illr.ii_illr_fld_s.i_cb_cnt
op_eq
id|IIO_LLP_CB_MAX
)paren
)paren
)paren
(brace
id|overflows
op_assign
l_int|1
suffix:semicolon
)brace
DECL|macro|LINKSTAT_UPDATE
mdefine_line|#define LINKSTAT_UPDATE(reg, cnt, mask, shift) cnt += (reg &amp; mask) &gt;&gt; shift
id|LINKSTAT_UPDATE
c_func
(paren
id|reg
(braket
l_int|0
)braket
comma
id|lsp-&gt;hs_ni_sn_errors
(braket
l_int|0
)braket
comma
id|SH_NI0_LLP_ERR_RX_SN_ERR_COUNT_MASK
comma
id|SH_NI0_LLP_ERR_RX_SN_ERR_COUNT_SHFT
)paren
suffix:semicolon
id|LINKSTAT_UPDATE
c_func
(paren
id|reg
(braket
l_int|1
)braket
comma
id|lsp-&gt;hs_ni_sn_errors
(braket
l_int|1
)braket
comma
id|SH_NI1_LLP_ERR_RX_SN_ERR_COUNT_MASK
comma
id|SH_NI1_LLP_ERR_RX_SN_ERR_COUNT_SHFT
)paren
suffix:semicolon
id|LINKSTAT_UPDATE
c_func
(paren
id|reg
(braket
l_int|0
)braket
comma
id|lsp-&gt;hs_ni_cb_errors
(braket
l_int|0
)braket
comma
id|SH_NI0_LLP_ERR_RX_CB_ERR_COUNT_MASK
comma
id|SH_NI0_LLP_ERR_RX_CB_ERR_COUNT_SHFT
)paren
suffix:semicolon
id|LINKSTAT_UPDATE
c_func
(paren
id|reg
(braket
l_int|1
)braket
comma
id|lsp-&gt;hs_ni_cb_errors
(braket
l_int|1
)braket
comma
id|SH_NI1_LLP_ERR_RX_CB_ERR_COUNT_MASK
comma
id|SH_NI1_LLP_ERR_RX_CB_ERR_COUNT_SHFT
)paren
suffix:semicolon
id|LINKSTAT_UPDATE
c_func
(paren
id|reg
(braket
l_int|0
)braket
comma
id|lsp-&gt;hs_ni_retry_errors
(braket
l_int|0
)braket
comma
id|SH_NI0_LLP_ERR_RETRY_COUNT_MASK
comma
id|SH_NI0_LLP_ERR_RETRY_COUNT_SHFT
)paren
suffix:semicolon
id|LINKSTAT_UPDATE
c_func
(paren
id|reg
(braket
l_int|1
)braket
comma
id|lsp-&gt;hs_ni_retry_errors
(braket
l_int|1
)braket
comma
id|SH_NI1_LLP_ERR_RETRY_COUNT_MASK
comma
id|SH_NI1_LLP_ERR_RETRY_COUNT_SHFT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lsp-&gt;hs_ii_up
)paren
(brace
multiline_comment|/* II sn and cb errors */
id|lsp-&gt;hs_ii_sn_errors
op_add_assign
id|illr.ii_illr_fld_s.i_sn_cnt
suffix:semicolon
id|lsp-&gt;hs_ii_cb_errors
op_add_assign
id|illr.ii_illr_fld_s.i_cb_cnt
suffix:semicolon
id|lsp-&gt;hs_ii_retry_errors
op_add_assign
(paren
id|iio_wstat
op_amp
l_int|0x0000000000ff0000
)paren
op_rshift
l_int|16
suffix:semicolon
id|shub_mmr_write
c_func
(paren
id|cnode
comma
id|SH_NI0_LLP_ERR
comma
l_int|0L
)paren
suffix:semicolon
id|shub_mmr_write
c_func
(paren
id|cnode
comma
id|SH_NI1_LLP_ERR
comma
l_int|0L
)paren
suffix:semicolon
id|shub_mmr_write_iospace
c_func
(paren
id|cnode
comma
id|IIO_LLP_LOG
comma
l_int|0L
)paren
suffix:semicolon
multiline_comment|/* zero the II retry counter */
id|iio_wstat
op_assign
id|shub_mmr_read_iospace
c_func
(paren
id|cnode
comma
id|IIO_WSTAT
)paren
suffix:semicolon
id|iio_wstat
op_and_assign
l_int|0xffffffffff00ffff
suffix:semicolon
multiline_comment|/* bits 23:16 */
id|shub_mmr_write_iospace
c_func
(paren
id|cnode
comma
id|IIO_WSTAT
comma
id|iio_wstat
)paren
suffix:semicolon
)brace
)brace
id|sn_linkstats_samples
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|overflows
)paren
id|sn_linkstats_overflows
op_increment
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|sn_linkstats_lock
)paren
suffix:semicolon
)brace
)brace
r_static
r_char
op_star
DECL|function|rate_per_minute
id|rate_per_minute
c_func
(paren
r_uint64
id|val
comma
r_uint64
id|secs
)paren
(brace
r_static
r_char
id|buf
(braket
l_int|16
)braket
suffix:semicolon
r_uint64
id|a
op_assign
l_int|0
comma
id|b
op_assign
l_int|0
comma
id|c
op_assign
l_int|0
comma
id|d
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|secs
)paren
(brace
id|a
op_assign
l_int|60
op_star
id|val
op_div
id|secs
suffix:semicolon
id|b
op_assign
l_int|60
op_star
l_int|10
op_star
id|val
op_div
id|secs
op_minus
(paren
l_int|10
op_star
id|a
)paren
suffix:semicolon
id|c
op_assign
l_int|60
op_star
l_int|100
op_star
id|val
op_div
id|secs
op_minus
(paren
l_int|100
op_star
id|a
)paren
op_minus
(paren
l_int|10
op_star
id|b
)paren
suffix:semicolon
id|d
op_assign
l_int|60
op_star
l_int|1000
op_star
id|val
op_div
id|secs
op_minus
(paren
l_int|1000
op_star
id|a
)paren
op_minus
(paren
l_int|100
op_star
id|b
)paren
op_minus
(paren
l_int|10
op_star
id|c
)paren
suffix:semicolon
)brace
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%4lu.%lu%lu%lu&quot;
comma
id|a
comma
id|b
comma
id|c
comma
id|d
)paren
suffix:semicolon
r_return
id|buf
suffix:semicolon
)brace
r_int
DECL|function|sn_linkstats_get
id|sn_linkstats_get
c_func
(paren
r_char
op_star
id|page
)paren
(brace
r_int
id|n
op_assign
l_int|0
suffix:semicolon
r_int
id|cnode
suffix:semicolon
r_int
id|nlport
suffix:semicolon
r_struct
id|s_linkstats
op_star
id|lsp
suffix:semicolon
id|nodepda_t
op_star
id|npda
suffix:semicolon
r_uint64
id|snsum
op_assign
l_int|0
suffix:semicolon
r_uint64
id|cbsum
op_assign
l_int|0
suffix:semicolon
r_uint64
id|retrysum
op_assign
l_int|0
suffix:semicolon
r_uint64
id|snsum_ii
op_assign
l_int|0
suffix:semicolon
r_uint64
id|cbsum_ii
op_assign
l_int|0
suffix:semicolon
r_uint64
id|retrysum_ii
op_assign
l_int|0
suffix:semicolon
r_uint64
id|secs
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|sn_linkstats_lock
)paren
suffix:semicolon
id|secs
op_assign
(paren
id|jiffies
op_minus
id|sn_linkstats_starttime
)paren
op_div
id|HZ
suffix:semicolon
id|n
op_add_assign
id|sprintf
c_func
(paren
id|page
comma
l_string|&quot;# SGI Numalink stats v1 : %lu samples, %lu o/flows, update %lu msecs&bslash;n&quot;
comma
id|sn_linkstats_samples
comma
id|sn_linkstats_overflows
comma
id|sn_linkstats_update_msecs
)paren
suffix:semicolon
id|n
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|n
comma
l_string|&quot;%-37s %8s %8s %8s %8s&bslash;n&quot;
comma
l_string|&quot;# Numalink&quot;
comma
l_string|&quot;sn errs&quot;
comma
l_string|&quot;cb errs&quot;
comma
l_string|&quot;cb/min&quot;
comma
l_string|&quot;retries&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|lsp
op_assign
id|sn_linkstats
comma
id|cnode
op_assign
l_int|0
suffix:semicolon
id|cnode
OL
id|numnodes
suffix:semicolon
id|cnode
op_increment
comma
id|lsp
op_increment
)paren
(brace
id|npda
op_assign
id|NODEPDA
c_func
(paren
id|cnode
)paren
suffix:semicolon
multiline_comment|/* two NL links on each SHub */
r_for
c_loop
(paren
id|nlport
op_assign
l_int|0
suffix:semicolon
id|nlport
OL
l_int|2
suffix:semicolon
id|nlport
op_increment
)paren
(brace
id|cbsum
op_add_assign
id|lsp-&gt;hs_ni_cb_errors
(braket
id|nlport
)braket
suffix:semicolon
id|snsum
op_add_assign
id|lsp-&gt;hs_ni_sn_errors
(braket
id|nlport
)braket
suffix:semicolon
id|retrysum
op_add_assign
id|lsp-&gt;hs_ni_retry_errors
(braket
id|nlport
)braket
suffix:semicolon
multiline_comment|/* avoid buffer overrun (should be using seq_read API) */
r_if
c_cond
(paren
id|numnodes
OG
l_int|64
)paren
r_continue
suffix:semicolon
id|n
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|n
comma
l_string|&quot;/%s/link/%d  %8lu %8lu %8s %8lu&bslash;n&quot;
comma
id|npda-&gt;hwg_node_name
comma
id|nlport
op_plus
l_int|1
comma
id|lsp-&gt;hs_ni_sn_errors
(braket
id|nlport
)braket
comma
id|lsp-&gt;hs_ni_cb_errors
(braket
id|nlport
)braket
comma
id|rate_per_minute
c_func
(paren
id|lsp-&gt;hs_ni_cb_errors
(braket
id|nlport
)braket
comma
id|secs
)paren
comma
id|lsp-&gt;hs_ni_retry_errors
(braket
id|nlport
)braket
)paren
suffix:semicolon
)brace
multiline_comment|/* one II port on each SHub (may not be connected) */
r_if
c_cond
(paren
id|lsp-&gt;hs_ii_up
)paren
(brace
id|n
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|n
comma
l_string|&quot;/%s/xtalk   %8lu %8lu %8s %8lu&bslash;n&quot;
comma
id|npda-&gt;hwg_node_name
comma
id|lsp-&gt;hs_ii_sn_errors
comma
id|lsp-&gt;hs_ii_cb_errors
comma
id|rate_per_minute
c_func
(paren
id|lsp-&gt;hs_ii_cb_errors
comma
id|secs
)paren
comma
id|lsp-&gt;hs_ii_retry_errors
)paren
suffix:semicolon
id|snsum_ii
op_add_assign
id|lsp-&gt;hs_ii_sn_errors
suffix:semicolon
id|cbsum_ii
op_add_assign
id|lsp-&gt;hs_ii_cb_errors
suffix:semicolon
id|retrysum_ii
op_add_assign
id|lsp-&gt;hs_ii_retry_errors
suffix:semicolon
)brace
)brace
id|n
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|n
comma
l_string|&quot;%-37s %8lu %8lu %8s %8lu&bslash;n&quot;
comma
l_string|&quot;System wide NL totals&quot;
comma
id|snsum
comma
id|cbsum
comma
id|rate_per_minute
c_func
(paren
id|cbsum
comma
id|secs
)paren
comma
id|retrysum
)paren
suffix:semicolon
id|n
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|n
comma
l_string|&quot;%-37s %8lu %8lu %8s %8lu&bslash;n&quot;
comma
l_string|&quot;System wide II totals&quot;
comma
id|snsum_ii
comma
id|cbsum_ii
comma
id|rate_per_minute
c_func
(paren
id|cbsum_ii
comma
id|secs
)paren
comma
id|retrysum_ii
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|sn_linkstats_lock
)paren
suffix:semicolon
r_return
id|n
suffix:semicolon
)brace
r_static
r_int
id|__init
DECL|function|linkstatd_init
id|linkstatd_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|ia64_platform_is
c_func
(paren
l_string|&quot;sn2&quot;
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|sn_linkstats_lock
)paren
suffix:semicolon
id|sn_linkstats
op_assign
id|kmalloc
c_func
(paren
id|numnodes
op_star
r_sizeof
(paren
r_struct
id|s_linkstats
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|sn_linkstats_reset
c_func
(paren
l_int|60000UL
)paren
suffix:semicolon
multiline_comment|/* default 60 second update interval */
id|kernel_thread
c_func
(paren
id|linkstatd_thread
comma
l_int|NULL
comma
id|CLONE_KERNEL
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|linkstatd_init
id|__initcall
c_func
(paren
id|linkstatd_init
)paren
suffix:semicolon
eof
