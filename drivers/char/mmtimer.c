multiline_comment|/*&n; * Intel Multimedia Timer device implementation for SGI SN platforms.&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (c) 2001-2004 Silicon Graphics, Inc.  All rights reserved.&n; *&n; * This driver exports an API that should be supportable by any HPET or IA-PC&n; * multimedia timer.  The code below is currently specific to the SGI Altix&n; * SHub RTC, however.&n; *&n; * 11/01/01 - jbarnes - initial revision&n; * 9/10/04 - Christoph Lameter - remove interrupt support for kernel inclusion&n; * 10/1/04 - Christoph Lameter - provide posix clock CLOCK_SGI_CYCLE&n; * 10/13/04 - Christoph Lameter, Dimitri Sivanich - provide timer interrupt&n; *&t;&t;support via the posix timer interface&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
macro_line|#include &lt;linux/mmtimer.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/posix-timers.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/sn/addrs.h&gt;
macro_line|#include &lt;asm/sn/intr.h&gt;
macro_line|#include &lt;asm/sn/shub_mmr.h&gt;
macro_line|#include &lt;asm/sn/nodepda.h&gt;
macro_line|#include &lt;asm/sn/shubio.h&gt;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Jesse Barnes &lt;jbarnes@sgi.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;SGI Altix RTC Timer&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
multiline_comment|/* name of the device, usually in /dev */
DECL|macro|MMTIMER_NAME
mdefine_line|#define MMTIMER_NAME &quot;mmtimer&quot;
DECL|macro|MMTIMER_DESC
mdefine_line|#define MMTIMER_DESC &quot;SGI Altix RTC Timer&quot;
DECL|macro|MMTIMER_VERSION
mdefine_line|#define MMTIMER_VERSION &quot;2.0&quot;
DECL|macro|RTC_BITS
mdefine_line|#define RTC_BITS 55 /* 55 bits for this implementation */
r_extern
r_int
r_int
id|sn_rtc_cycles_per_second
suffix:semicolon
DECL|macro|RTC_COUNTER_ADDR
mdefine_line|#define RTC_COUNTER_ADDR        ((long *)LOCAL_MMR_ADDR(SH_RTC))
DECL|macro|rtc_time
mdefine_line|#define rtc_time()              (*RTC_COUNTER_ADDR)
r_static
r_int
id|mmtimer_ioctl
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
suffix:semicolon
r_static
r_int
id|mmtimer_mmap
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|vm_area_struct
op_star
id|vma
)paren
suffix:semicolon
multiline_comment|/*&n; * Period in femtoseconds (10^-15 s)&n; */
DECL|variable|mmtimer_femtoperiod
r_static
r_int
r_int
id|mmtimer_femtoperiod
op_assign
l_int|0
suffix:semicolon
DECL|variable|mmtimer_fops
r_static
r_struct
id|file_operations
id|mmtimer_fops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|mmap
op_assign
id|mmtimer_mmap
comma
dot
id|ioctl
op_assign
id|mmtimer_ioctl
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * We only have comparison registers RTC1-4 currently available per&n; * node.  RTC0 is used by SAL.&n; */
DECL|macro|NUM_COMPARATORS
mdefine_line|#define NUM_COMPARATORS 3
multiline_comment|/* Check for an RTC interrupt pending */
DECL|function|mmtimer_int_pending
r_static
r_int
r_inline
id|mmtimer_int_pending
c_func
(paren
r_int
id|comparator
)paren
(brace
r_if
c_cond
(paren
id|HUB_L
c_func
(paren
(paren
r_int
r_int
op_star
)paren
id|LOCAL_MMR_ADDR
c_func
(paren
id|SH_EVENT_OCCURRED
)paren
)paren
op_amp
id|SH_EVENT_OCCURRED_RTC1_INT_MASK
op_lshift
id|comparator
)paren
r_return
l_int|1
suffix:semicolon
r_else
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Clear the RTC interrupt pending bit */
DECL|function|mmtimer_clr_int_pending
r_static
r_void
r_inline
id|mmtimer_clr_int_pending
c_func
(paren
r_int
id|comparator
)paren
(brace
id|HUB_S
c_func
(paren
(paren
id|u64
op_star
)paren
id|LOCAL_MMR_ADDR
c_func
(paren
id|SH_EVENT_OCCURRED_ALIAS
)paren
comma
id|SH_EVENT_OCCURRED_RTC1_INT_MASK
op_lshift
id|comparator
)paren
suffix:semicolon
)brace
multiline_comment|/* Setup timer on comparator RTC1 */
DECL|function|mmtimer_setup_int_0
r_static
r_void
r_inline
id|mmtimer_setup_int_0
c_func
(paren
id|u64
id|expires
)paren
(brace
id|u64
id|val
suffix:semicolon
multiline_comment|/* Disable interrupt */
id|HUB_S
c_func
(paren
(paren
id|u64
op_star
)paren
id|LOCAL_MMR_ADDR
c_func
(paren
id|SH_RTC1_INT_ENABLE
)paren
comma
l_int|0UL
)paren
suffix:semicolon
multiline_comment|/* Initialize comparator value */
id|HUB_S
c_func
(paren
(paren
id|u64
op_star
)paren
id|LOCAL_MMR_ADDR
c_func
(paren
id|SH_INT_CMPB
)paren
comma
op_minus
l_int|1L
)paren
suffix:semicolon
multiline_comment|/* Clear pending bit */
id|mmtimer_clr_int_pending
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|val
op_assign
(paren
(paren
id|u64
)paren
id|SGI_MMTIMER_VECTOR
op_lshift
id|SH_RTC1_INT_CONFIG_IDX_SHFT
)paren
op_or
(paren
(paren
id|u64
)paren
id|cpu_physical_id
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
)paren
op_lshift
id|SH_RTC1_INT_CONFIG_PID_SHFT
)paren
suffix:semicolon
multiline_comment|/* Set configuration */
id|HUB_S
c_func
(paren
(paren
id|u64
op_star
)paren
id|LOCAL_MMR_ADDR
c_func
(paren
id|SH_RTC1_INT_CONFIG
)paren
comma
id|val
)paren
suffix:semicolon
multiline_comment|/* Enable RTC interrupts */
id|HUB_S
c_func
(paren
(paren
id|u64
op_star
)paren
id|LOCAL_MMR_ADDR
c_func
(paren
id|SH_RTC1_INT_ENABLE
)paren
comma
l_int|1UL
)paren
suffix:semicolon
multiline_comment|/* Initialize comparator value */
id|HUB_S
c_func
(paren
(paren
id|u64
op_star
)paren
id|LOCAL_MMR_ADDR
c_func
(paren
id|SH_INT_CMPB
)paren
comma
id|expires
)paren
suffix:semicolon
)brace
multiline_comment|/* Setup timer on comparator RTC2 */
DECL|function|mmtimer_setup_int_1
r_static
r_void
r_inline
id|mmtimer_setup_int_1
c_func
(paren
id|u64
id|expires
)paren
(brace
id|u64
id|val
suffix:semicolon
id|HUB_S
c_func
(paren
(paren
id|u64
op_star
)paren
id|LOCAL_MMR_ADDR
c_func
(paren
id|SH_RTC2_INT_ENABLE
)paren
comma
l_int|0UL
)paren
suffix:semicolon
id|HUB_S
c_func
(paren
(paren
id|u64
op_star
)paren
id|LOCAL_MMR_ADDR
c_func
(paren
id|SH_INT_CMPC
)paren
comma
op_minus
l_int|1L
)paren
suffix:semicolon
id|mmtimer_clr_int_pending
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|val
op_assign
(paren
(paren
id|u64
)paren
id|SGI_MMTIMER_VECTOR
op_lshift
id|SH_RTC2_INT_CONFIG_IDX_SHFT
)paren
op_or
(paren
(paren
id|u64
)paren
id|cpu_physical_id
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
)paren
op_lshift
id|SH_RTC2_INT_CONFIG_PID_SHFT
)paren
suffix:semicolon
id|HUB_S
c_func
(paren
(paren
id|u64
op_star
)paren
id|LOCAL_MMR_ADDR
c_func
(paren
id|SH_RTC2_INT_CONFIG
)paren
comma
id|val
)paren
suffix:semicolon
id|HUB_S
c_func
(paren
(paren
id|u64
op_star
)paren
id|LOCAL_MMR_ADDR
c_func
(paren
id|SH_RTC2_INT_ENABLE
)paren
comma
l_int|1UL
)paren
suffix:semicolon
id|HUB_S
c_func
(paren
(paren
id|u64
op_star
)paren
id|LOCAL_MMR_ADDR
c_func
(paren
id|SH_INT_CMPC
)paren
comma
id|expires
)paren
suffix:semicolon
)brace
multiline_comment|/* Setup timer on comparator RTC3 */
DECL|function|mmtimer_setup_int_2
r_static
r_void
r_inline
id|mmtimer_setup_int_2
c_func
(paren
id|u64
id|expires
)paren
(brace
id|u64
id|val
suffix:semicolon
id|HUB_S
c_func
(paren
(paren
id|u64
op_star
)paren
id|LOCAL_MMR_ADDR
c_func
(paren
id|SH_RTC3_INT_ENABLE
)paren
comma
l_int|0UL
)paren
suffix:semicolon
id|HUB_S
c_func
(paren
(paren
id|u64
op_star
)paren
id|LOCAL_MMR_ADDR
c_func
(paren
id|SH_INT_CMPD
)paren
comma
op_minus
l_int|1L
)paren
suffix:semicolon
id|mmtimer_clr_int_pending
c_func
(paren
l_int|2
)paren
suffix:semicolon
id|val
op_assign
(paren
(paren
id|u64
)paren
id|SGI_MMTIMER_VECTOR
op_lshift
id|SH_RTC3_INT_CONFIG_IDX_SHFT
)paren
op_or
(paren
(paren
id|u64
)paren
id|cpu_physical_id
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
)paren
op_lshift
id|SH_RTC3_INT_CONFIG_PID_SHFT
)paren
suffix:semicolon
id|HUB_S
c_func
(paren
(paren
id|u64
op_star
)paren
id|LOCAL_MMR_ADDR
c_func
(paren
id|SH_RTC3_INT_CONFIG
)paren
comma
id|val
)paren
suffix:semicolon
id|HUB_S
c_func
(paren
(paren
id|u64
op_star
)paren
id|LOCAL_MMR_ADDR
c_func
(paren
id|SH_RTC3_INT_ENABLE
)paren
comma
l_int|1UL
)paren
suffix:semicolon
id|HUB_S
c_func
(paren
(paren
id|u64
op_star
)paren
id|LOCAL_MMR_ADDR
c_func
(paren
id|SH_INT_CMPD
)paren
comma
id|expires
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This function must be called with interrupts disabled and preemption off&n; * in order to insure that the setup succeeds in a deterministic time frame.&n; * It will check if the interrupt setup succeeded.&n; */
DECL|function|mmtimer_setup
r_static
r_int
r_inline
id|mmtimer_setup
c_func
(paren
r_int
id|comparator
comma
r_int
r_int
id|expires
)paren
(brace
r_switch
c_cond
(paren
id|comparator
)paren
(brace
r_case
l_int|0
suffix:colon
id|mmtimer_setup_int_0
c_func
(paren
id|expires
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|mmtimer_setup_int_1
c_func
(paren
id|expires
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|mmtimer_setup_int_2
c_func
(paren
id|expires
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* We might&squot;ve missed our expiration time */
r_if
c_cond
(paren
id|rtc_time
c_func
(paren
)paren
OL
id|expires
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * If an interrupt is already pending then its okay&n;&t; * if not then we failed&n;&t; */
r_return
id|mmtimer_int_pending
c_func
(paren
id|comparator
)paren
suffix:semicolon
)brace
DECL|function|mmtimer_disable_int
r_static
r_int
r_inline
id|mmtimer_disable_int
c_func
(paren
r_int
id|nasid
comma
r_int
id|comparator
)paren
(brace
r_switch
c_cond
(paren
id|comparator
)paren
(brace
r_case
l_int|0
suffix:colon
id|nasid
op_eq
op_minus
l_int|1
ques
c_cond
id|HUB_S
c_func
(paren
(paren
id|u64
op_star
)paren
id|LOCAL_MMR_ADDR
c_func
(paren
id|SH_RTC1_INT_ENABLE
)paren
comma
l_int|0UL
)paren
suffix:colon
id|REMOTE_HUB_S
c_func
(paren
id|nasid
comma
id|SH_RTC1_INT_ENABLE
comma
l_int|0UL
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|nasid
op_eq
op_minus
l_int|1
ques
c_cond
id|HUB_S
c_func
(paren
(paren
id|u64
op_star
)paren
id|LOCAL_MMR_ADDR
c_func
(paren
id|SH_RTC2_INT_ENABLE
)paren
comma
l_int|0UL
)paren
suffix:colon
id|REMOTE_HUB_S
c_func
(paren
id|nasid
comma
id|SH_RTC2_INT_ENABLE
comma
l_int|0UL
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|nasid
op_eq
op_minus
l_int|1
ques
c_cond
id|HUB_S
c_func
(paren
(paren
id|u64
op_star
)paren
id|LOCAL_MMR_ADDR
c_func
(paren
id|SH_RTC3_INT_ENABLE
)paren
comma
l_int|0UL
)paren
suffix:colon
id|REMOTE_HUB_S
c_func
(paren
id|nasid
comma
id|SH_RTC3_INT_ENABLE
comma
l_int|0UL
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|TIMER_OFF
mdefine_line|#define TIMER_OFF 0xbadcabLL
multiline_comment|/* There is one of these for each comparator */
DECL|struct|mmtimer
r_typedef
r_struct
id|mmtimer
(brace
DECL|member|____cacheline_aligned
id|spinlock_t
id|lock
id|____cacheline_aligned
suffix:semicolon
DECL|member|timer
r_struct
id|k_itimer
op_star
id|timer
suffix:semicolon
DECL|member|i
r_int
id|i
suffix:semicolon
DECL|member|cpu
r_int
id|cpu
suffix:semicolon
DECL|member|tasklet
r_struct
id|tasklet_struct
id|tasklet
suffix:semicolon
DECL|typedef|mmtimer_t
)brace
id|mmtimer_t
suffix:semicolon
multiline_comment|/*&n; * Total number of comparators is comparators/node * MAX nodes/running kernel&n; */
DECL|variable|timers
r_static
id|mmtimer_t
id|timers
(braket
id|NUM_COMPARATORS
op_star
id|MAX_COMPACT_NODES
)braket
suffix:semicolon
multiline_comment|/**&n; * mmtimer_ioctl - ioctl interface for /dev/mmtimer&n; * @inode: inode of the device&n; * @file: file structure for the device&n; * @cmd: command to execute&n; * @arg: optional argument to command&n; *&n; * Executes the command specified by @cmd.  Returns 0 for success, &lt; 0 for&n; * failure.&n; *&n; * Valid commands:&n; *&n; * %MMTIMER_GETOFFSET - Should return the offset (relative to the start&n; * of the page where the registers are mapped) for the counter in question.&n; *&n; * %MMTIMER_GETRES - Returns the resolution of the clock in femto (10^-15)&n; * seconds&n; *&n; * %MMTIMER_GETFREQ - Copies the frequency of the clock in Hz to the address&n; * specified by @arg&n; *&n; * %MMTIMER_GETBITS - Returns the number of bits in the clock&squot;s counter&n; *&n; * %MMTIMER_MMAPAVAIL - Returns 1 if the registers can be mmap&squot;d into userspace&n; *&n; * %MMTIMER_GETCOUNTER - Gets the current value in the counter and places it&n; * in the address specified by @arg.&n; */
DECL|function|mmtimer_ioctl
r_static
r_int
id|mmtimer_ioctl
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
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|MMTIMER_GETOFFSET
suffix:colon
multiline_comment|/* offset of the counter */
multiline_comment|/*&n;&t;&t; * SN RTC registers are on their own 64k page&n;&t;&t; */
r_if
c_cond
(paren
id|PAGE_SIZE
op_le
(paren
l_int|1
op_lshift
l_int|16
)paren
)paren
(brace
id|ret
op_assign
(paren
(paren
(paren
r_int
)paren
id|RTC_COUNTER_ADDR
)paren
op_amp
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
)paren
op_div
l_int|8
suffix:semicolon
)brace
r_else
id|ret
op_assign
op_minus
id|ENOSYS
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MMTIMER_GETRES
suffix:colon
multiline_comment|/* resolution of the clock in 10^-15 s */
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_int
r_int
id|__user
op_star
)paren
id|arg
comma
op_amp
id|mmtimer_femtoperiod
comma
r_sizeof
(paren
r_int
r_int
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
id|MMTIMER_GETFREQ
suffix:colon
multiline_comment|/* frequency in Hz */
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_int
r_int
id|__user
op_star
)paren
id|arg
comma
op_amp
id|sn_rtc_cycles_per_second
comma
r_sizeof
(paren
r_int
r_int
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|ret
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MMTIMER_GETBITS
suffix:colon
multiline_comment|/* number of bits in the clock */
id|ret
op_assign
id|RTC_BITS
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MMTIMER_MMAPAVAIL
suffix:colon
multiline_comment|/* can we mmap the clock into userspace? */
id|ret
op_assign
(paren
id|PAGE_SIZE
op_le
(paren
l_int|1
op_lshift
l_int|16
)paren
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MMTIMER_GETCOUNTER
suffix:colon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_int
r_int
id|__user
op_star
)paren
id|arg
comma
id|RTC_COUNTER_ADDR
comma
r_sizeof
(paren
r_int
r_int
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
id|ret
op_assign
op_minus
id|ENOSYS
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/**&n; * mmtimer_mmap - maps the clock&squot;s registers into userspace&n; * @file: file structure for the device&n; * @vma: VMA to map the registers into&n; *&n; * Calls remap_pfn_range() to map the clock&squot;s registers into&n; * the calling process&squot; address space.&n; */
DECL|function|mmtimer_mmap
r_static
r_int
id|mmtimer_mmap
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|vm_area_struct
op_star
id|vma
)paren
(brace
r_int
r_int
id|mmtimer_addr
suffix:semicolon
r_if
c_cond
(paren
id|vma-&gt;vm_end
op_minus
id|vma-&gt;vm_start
op_ne
id|PAGE_SIZE
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_WRITE
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|PAGE_SIZE
OG
(paren
l_int|1
op_lshift
l_int|16
)paren
)paren
r_return
op_minus
id|ENOSYS
suffix:semicolon
id|vma-&gt;vm_flags
op_or_assign
(paren
id|VM_IO
op_or
id|VM_SHM
op_or
id|VM_LOCKED
)paren
suffix:semicolon
id|vma-&gt;vm_page_prot
op_assign
id|pgprot_noncached
c_func
(paren
id|vma-&gt;vm_page_prot
)paren
suffix:semicolon
id|mmtimer_addr
op_assign
id|__pa
c_func
(paren
id|RTC_COUNTER_ADDR
)paren
suffix:semicolon
id|mmtimer_addr
op_and_assign
op_complement
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
id|mmtimer_addr
op_and_assign
l_int|0xfffffffffffffffUL
suffix:semicolon
r_if
c_cond
(paren
id|remap_pfn_range
c_func
(paren
id|vma
comma
id|vma-&gt;vm_start
comma
id|mmtimer_addr
op_rshift
id|PAGE_SHIFT
comma
id|PAGE_SIZE
comma
id|vma-&gt;vm_page_prot
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;remap_pfn_range failed in mmtimer.c&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|mmtimer_miscdev
r_static
r_struct
id|miscdevice
id|mmtimer_miscdev
op_assign
(brace
id|SGI_MMTIMER
comma
id|MMTIMER_NAME
comma
op_amp
id|mmtimer_fops
)brace
suffix:semicolon
DECL|variable|sgi_clock_offset
r_static
r_struct
id|timespec
id|sgi_clock_offset
suffix:semicolon
DECL|variable|sgi_clock_period
r_static
r_int
id|sgi_clock_period
suffix:semicolon
multiline_comment|/*&n; * Posix Timer Interface&n; */
DECL|variable|sgi_clock_offset
r_static
r_struct
id|timespec
id|sgi_clock_offset
suffix:semicolon
DECL|variable|sgi_clock_period
r_static
r_int
id|sgi_clock_period
suffix:semicolon
DECL|function|sgi_clock_get
r_static
r_int
id|sgi_clock_get
c_func
(paren
id|clockid_t
id|clockid
comma
r_struct
id|timespec
op_star
id|tp
)paren
(brace
id|u64
id|nsec
suffix:semicolon
id|nsec
op_assign
id|rtc_time
c_func
(paren
)paren
op_star
id|sgi_clock_period
op_plus
id|sgi_clock_offset.tv_nsec
suffix:semicolon
id|tp-&gt;tv_sec
op_assign
id|div_long_long_rem
c_func
(paren
id|nsec
comma
id|NSEC_PER_SEC
comma
op_amp
id|tp-&gt;tv_nsec
)paren
op_plus
id|sgi_clock_offset.tv_sec
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
suffix:semicolon
DECL|function|sgi_clock_set
r_static
r_int
id|sgi_clock_set
c_func
(paren
id|clockid_t
id|clockid
comma
r_struct
id|timespec
op_star
id|tp
)paren
(brace
id|u64
id|nsec
suffix:semicolon
id|u64
id|rem
suffix:semicolon
id|nsec
op_assign
id|rtc_time
c_func
(paren
)paren
op_star
id|sgi_clock_period
suffix:semicolon
id|sgi_clock_offset.tv_sec
op_assign
id|tp-&gt;tv_sec
op_minus
id|div_long_long_rem
c_func
(paren
id|nsec
comma
id|NSEC_PER_SEC
comma
op_amp
id|rem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rem
op_le
id|tp-&gt;tv_nsec
)paren
id|sgi_clock_offset.tv_nsec
op_assign
id|tp-&gt;tv_sec
op_minus
id|rem
suffix:semicolon
r_else
(brace
id|sgi_clock_offset.tv_nsec
op_assign
id|tp-&gt;tv_sec
op_plus
id|NSEC_PER_SEC
op_minus
id|rem
suffix:semicolon
id|sgi_clock_offset.tv_sec
op_decrement
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Schedule the next periodic interrupt. This function will attempt&n; * to schedule a periodic interrupt later if necessary. If the scheduling&n; * of an interrupt fails then the time to skip is lengthened&n; * exponentially in order to ensure that the next interrupt&n; * can be properly scheduled..&n; */
DECL|function|reschedule_periodic_timer
r_static
r_int
r_inline
id|reschedule_periodic_timer
c_func
(paren
id|mmtimer_t
op_star
id|x
)paren
(brace
r_int
id|n
suffix:semicolon
r_struct
id|k_itimer
op_star
id|t
op_assign
id|x-&gt;timer
suffix:semicolon
id|t-&gt;it.mmtimer.clock
op_assign
id|x-&gt;i
suffix:semicolon
id|t-&gt;it_overrun
op_decrement
suffix:semicolon
id|n
op_assign
l_int|0
suffix:semicolon
r_do
(brace
id|t-&gt;it.mmtimer.expires
op_add_assign
id|t-&gt;it.mmtimer.incr
op_lshift
id|n
suffix:semicolon
id|t-&gt;it_overrun
op_add_assign
l_int|1
op_lshift
id|n
suffix:semicolon
id|n
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|n
OG
l_int|20
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_while
c_loop
(paren
op_logical_neg
id|mmtimer_setup
c_func
(paren
id|x-&gt;i
comma
id|t-&gt;it.mmtimer.expires
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * mmtimer_interrupt - timer interrupt handler&n; * @irq: irq received&n; * @dev_id: device the irq came from&n; * @regs: register state upon receipt of the interrupt&n; *&n; * Called when one of the comarators matches the counter, This&n; * routine will send signals to processes that have requested&n; * them.&n; *&n; * This interrupt is run in an interrupt context&n; * by the SHUB. It is therefore safe to locally access SHub&n; * registers.&n; */
r_static
id|irqreturn_t
DECL|function|mmtimer_interrupt
id|mmtimer_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|i
suffix:semicolon
id|mmtimer_t
op_star
id|base
op_assign
id|timers
op_plus
id|cpuid_to_cnodeid
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
)paren
op_star
id|NUM_COMPARATORS
suffix:semicolon
r_int
r_int
id|expires
op_assign
l_int|0
suffix:semicolon
r_int
id|result
op_assign
id|IRQ_NONE
suffix:semicolon
multiline_comment|/*&n;&t; * Do this once for each comparison register&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NUM_COMPARATORS
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* Make sure this doesn&squot;t get reused before tasklet_sched */
id|spin_lock
c_func
(paren
op_amp
id|base
(braket
id|i
)braket
dot
id|lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|base
(braket
id|i
)braket
dot
id|cpu
op_eq
id|smp_processor_id
c_func
(paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|base
(braket
id|i
)braket
dot
id|timer
)paren
id|expires
op_assign
id|base
(braket
id|i
)braket
dot
id|timer-&gt;it.mmtimer.expires
suffix:semicolon
multiline_comment|/* expires test won&squot;t work with shared irqs */
r_if
c_cond
(paren
(paren
id|mmtimer_int_pending
c_func
(paren
id|i
)paren
OG
l_int|0
)paren
op_logical_or
(paren
id|expires
op_logical_and
(paren
id|expires
OL
id|rtc_time
c_func
(paren
)paren
)paren
)paren
)paren
(brace
id|mmtimer_clr_int_pending
c_func
(paren
id|i
)paren
suffix:semicolon
id|tasklet_schedule
c_func
(paren
op_amp
id|base
(braket
id|i
)braket
dot
id|tasklet
)paren
suffix:semicolon
id|result
op_assign
id|IRQ_HANDLED
suffix:semicolon
)brace
)brace
id|spin_unlock
c_func
(paren
op_amp
id|base
(braket
id|i
)braket
dot
id|lock
)paren
suffix:semicolon
id|expires
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|result
suffix:semicolon
)brace
DECL|function|mmtimer_tasklet
r_void
id|mmtimer_tasklet
c_func
(paren
r_int
r_int
id|data
)paren
(brace
id|mmtimer_t
op_star
id|x
op_assign
(paren
id|mmtimer_t
op_star
)paren
id|data
suffix:semicolon
r_struct
id|k_itimer
op_star
id|t
op_assign
id|x-&gt;timer
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|t
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
multiline_comment|/* Send signal and deal with periodic signals */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|t-&gt;it_lock
comma
id|flags
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|x-&gt;lock
)paren
suffix:semicolon
multiline_comment|/* If timer was deleted between interrupt and here, leave */
r_if
c_cond
(paren
id|t
op_ne
id|x-&gt;timer
)paren
r_goto
id|out
suffix:semicolon
id|t-&gt;it_overrun
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|tasklist_lock.write_lock
op_logical_or
id|posix_timer_event
c_func
(paren
id|t
comma
l_int|0
)paren
op_ne
l_int|0
)paren
(brace
singleline_comment|// printk(KERN_WARNING &quot;mmtimer: cannot deliver signal.&bslash;n&quot;);
id|t-&gt;it_overrun
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|t-&gt;it.mmtimer.incr
)paren
(brace
multiline_comment|/* Periodic timer */
r_if
c_cond
(paren
id|reschedule_periodic_timer
c_func
(paren
id|x
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;mmtimer: unable to reschedule&bslash;n&quot;
)paren
suffix:semicolon
id|x-&gt;timer
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* Ensure we don&squot;t false trigger in mmtimer_interrupt */
id|t-&gt;it.mmtimer.expires
op_assign
l_int|0
suffix:semicolon
)brace
id|t-&gt;it_overrun_last
op_assign
id|t-&gt;it_overrun
suffix:semicolon
id|out
suffix:colon
id|spin_unlock
c_func
(paren
op_amp
id|x-&gt;lock
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|t-&gt;it_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|sgi_timer_create
r_static
r_int
id|sgi_timer_create
c_func
(paren
r_struct
id|k_itimer
op_star
id|timer
)paren
(brace
multiline_comment|/* Insure that a newly created timer is off */
id|timer-&gt;it.mmtimer.clock
op_assign
id|TIMER_OFF
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* This does not really delete a timer. It just insures&n; * that the timer is not active&n; *&n; * Assumption: it_lock is already held with irq&squot;s disabled&n; */
DECL|function|sgi_timer_del
r_static
r_int
id|sgi_timer_del
c_func
(paren
r_struct
id|k_itimer
op_star
id|timr
)paren
(brace
r_int
id|i
op_assign
id|timr-&gt;it.mmtimer.clock
suffix:semicolon
id|cnodeid_t
id|nodeid
op_assign
id|timr-&gt;it.mmtimer.node
suffix:semicolon
id|mmtimer_t
op_star
id|t
op_assign
id|timers
op_plus
id|nodeid
op_star
id|NUM_COMPARATORS
op_plus
id|i
suffix:semicolon
r_int
r_int
id|irqflags
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ne
id|TIMER_OFF
)paren
(brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|t-&gt;lock
comma
id|irqflags
)paren
suffix:semicolon
id|mmtimer_disable_int
c_func
(paren
id|cnodeid_to_nasid
c_func
(paren
id|nodeid
)paren
comma
id|i
)paren
suffix:semicolon
id|t-&gt;timer
op_assign
l_int|NULL
suffix:semicolon
id|timr-&gt;it.mmtimer.clock
op_assign
id|TIMER_OFF
suffix:semicolon
id|timr-&gt;it.mmtimer.expires
op_assign
l_int|0
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|t-&gt;lock
comma
id|irqflags
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|timespec_to_ns
mdefine_line|#define timespec_to_ns(x) ((x).tv_nsec + (x).tv_sec * NSEC_PER_SEC)
DECL|macro|ns_to_timespec
mdefine_line|#define ns_to_timespec(ts, nsec) (ts).tv_sec = div_long_long_rem(nsec, NSEC_PER_SEC, &amp;(ts).tv_nsec)
multiline_comment|/* Assumption: it_lock is already held with irq&squot;s disabled */
DECL|function|sgi_timer_get
r_static
r_void
id|sgi_timer_get
c_func
(paren
r_struct
id|k_itimer
op_star
id|timr
comma
r_struct
id|itimerspec
op_star
id|cur_setting
)paren
(brace
r_if
c_cond
(paren
id|timr-&gt;it.mmtimer.clock
op_eq
id|TIMER_OFF
)paren
(brace
id|cur_setting-&gt;it_interval.tv_nsec
op_assign
l_int|0
suffix:semicolon
id|cur_setting-&gt;it_interval.tv_sec
op_assign
l_int|0
suffix:semicolon
id|cur_setting-&gt;it_value.tv_nsec
op_assign
l_int|0
suffix:semicolon
id|cur_setting-&gt;it_value.tv_sec
op_assign
l_int|0
suffix:semicolon
r_return
suffix:semicolon
)brace
id|ns_to_timespec
c_func
(paren
id|cur_setting-&gt;it_interval
comma
id|timr-&gt;it.mmtimer.incr
op_star
id|sgi_clock_period
)paren
suffix:semicolon
id|ns_to_timespec
c_func
(paren
id|cur_setting-&gt;it_value
comma
(paren
id|timr-&gt;it.mmtimer.expires
op_minus
id|rtc_time
c_func
(paren
)paren
)paren
op_star
id|sgi_clock_period
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|sgi_timer_set
r_static
r_int
id|sgi_timer_set
c_func
(paren
r_struct
id|k_itimer
op_star
id|timr
comma
r_int
id|flags
comma
r_struct
id|itimerspec
op_star
id|new_setting
comma
r_struct
id|itimerspec
op_star
id|old_setting
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_int
id|when
comma
id|period
comma
id|irqflags
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
id|cnodeid_t
id|nodeid
suffix:semicolon
id|mmtimer_t
op_star
id|base
suffix:semicolon
r_if
c_cond
(paren
id|old_setting
)paren
id|sgi_timer_get
c_func
(paren
id|timr
comma
id|old_setting
)paren
suffix:semicolon
id|sgi_timer_del
c_func
(paren
id|timr
)paren
suffix:semicolon
id|when
op_assign
id|timespec_to_ns
c_func
(paren
id|new_setting-&gt;it_value
)paren
suffix:semicolon
id|period
op_assign
id|timespec_to_ns
c_func
(paren
id|new_setting-&gt;it_interval
)paren
suffix:semicolon
r_if
c_cond
(paren
id|when
op_eq
l_int|0
)paren
multiline_comment|/* Clear timer */
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|TIMER_ABSTIME
)paren
(brace
r_struct
id|timespec
id|n
suffix:semicolon
r_int
r_int
id|now
suffix:semicolon
id|getnstimeofday
c_func
(paren
op_amp
id|n
)paren
suffix:semicolon
id|now
op_assign
id|timespec_to_ns
c_func
(paren
id|n
)paren
suffix:semicolon
r_if
c_cond
(paren
id|when
OG
id|now
)paren
id|when
op_sub_assign
id|now
suffix:semicolon
r_else
multiline_comment|/* Fire the timer immediately */
id|when
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Convert to sgi clock period. Need to keep rtc_time() as near as possible&n;&t; * to getnstimeofday() in order to be as faithful as possible to the time&n;&t; * specified.&n;&t; */
id|when
op_assign
(paren
id|when
op_plus
id|sgi_clock_period
op_minus
l_int|1
)paren
op_div
id|sgi_clock_period
op_plus
id|rtc_time
c_func
(paren
)paren
suffix:semicolon
id|period
op_assign
(paren
id|period
op_plus
id|sgi_clock_period
op_minus
l_int|1
)paren
op_div
id|sgi_clock_period
suffix:semicolon
multiline_comment|/*&n;&t; * We are allocating a local SHub comparator. If we would be moved to another&n;&t; * cpu then another SHub may be local to us. Prohibit that by switching off&n;&t; * preemption.&n;&t; */
id|preempt_disable
c_func
(paren
)paren
suffix:semicolon
id|nodeid
op_assign
id|cpuid_to_cnodeid
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
id|base
op_assign
id|timers
op_plus
id|nodeid
op_star
id|NUM_COMPARATORS
suffix:semicolon
id|retry
suffix:colon
multiline_comment|/* Don&squot;t use an allocated timer, or a deleted one that&squot;s pending */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NUM_COMPARATORS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|base
(braket
id|i
)braket
dot
id|timer
op_logical_and
op_logical_neg
id|base
(braket
id|i
)braket
dot
id|tasklet.state
)paren
(brace
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|i
op_eq
id|NUM_COMPARATORS
)paren
(brace
id|preempt_enable
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|base
(braket
id|i
)braket
dot
id|lock
comma
id|irqflags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|base
(braket
id|i
)braket
dot
id|timer
op_logical_or
id|base
(braket
id|i
)braket
dot
id|tasklet.state
op_ne
l_int|0
)paren
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|base
(braket
id|i
)braket
dot
id|lock
comma
id|irqflags
)paren
suffix:semicolon
r_goto
id|retry
suffix:semicolon
)brace
id|base
(braket
id|i
)braket
dot
id|timer
op_assign
id|timr
suffix:semicolon
id|base
(braket
id|i
)braket
dot
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|timr-&gt;it.mmtimer.clock
op_assign
id|i
suffix:semicolon
id|timr-&gt;it.mmtimer.node
op_assign
id|nodeid
suffix:semicolon
id|timr-&gt;it.mmtimer.incr
op_assign
id|period
suffix:semicolon
id|timr-&gt;it.mmtimer.expires
op_assign
id|when
suffix:semicolon
r_if
c_cond
(paren
id|period
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|mmtimer_setup
c_func
(paren
id|i
comma
id|when
)paren
)paren
(brace
id|mmtimer_disable_int
c_func
(paren
op_minus
l_int|1
comma
id|i
)paren
suffix:semicolon
id|posix_timer_event
c_func
(paren
id|timr
comma
l_int|0
)paren
suffix:semicolon
id|timr-&gt;it.mmtimer.expires
op_assign
l_int|0
suffix:semicolon
)brace
)brace
r_else
(brace
id|timr-&gt;it.mmtimer.expires
op_sub_assign
id|period
suffix:semicolon
r_if
c_cond
(paren
id|reschedule_periodic_timer
c_func
(paren
id|base
op_plus
id|i
)paren
)paren
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|base
(braket
id|i
)braket
dot
id|lock
comma
id|irqflags
)paren
suffix:semicolon
id|preempt_enable
c_func
(paren
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|variable|sgi_clock
r_static
r_struct
id|k_clock
id|sgi_clock
op_assign
(brace
dot
id|res
op_assign
l_int|0
comma
dot
id|clock_set
op_assign
id|sgi_clock_set
comma
dot
id|clock_get
op_assign
id|sgi_clock_get
comma
dot
id|timer_create
op_assign
id|sgi_timer_create
comma
dot
id|nsleep
op_assign
id|do_posix_clock_nonanosleep
comma
dot
id|timer_set
op_assign
id|sgi_timer_set
comma
dot
id|timer_del
op_assign
id|sgi_timer_del
comma
dot
id|timer_get
op_assign
id|sgi_timer_get
)brace
suffix:semicolon
multiline_comment|/**&n; * mmtimer_init - device initialization routine&n; *&n; * Does initial setup for the mmtimer device.&n; */
DECL|function|mmtimer_init
r_static
r_int
id|__init
id|mmtimer_init
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
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
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * Sanity check the cycles/sec variable&n;&t; */
r_if
c_cond
(paren
id|sn_rtc_cycles_per_second
OL
l_int|100000
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: unable to determine clock frequency&bslash;n&quot;
comma
id|MMTIMER_NAME
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|mmtimer_femtoperiod
op_assign
(paren
(paren
r_int
r_int
)paren
l_float|1E15
op_plus
id|sn_rtc_cycles_per_second
op_div
l_int|2
)paren
op_div
id|sn_rtc_cycles_per_second
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
id|NUM_COMPARATORS
op_star
id|MAX_COMPACT_NODES
suffix:semicolon
id|i
op_increment
)paren
(brace
id|spin_lock_init
c_func
(paren
op_amp
id|timers
(braket
id|i
)braket
dot
id|lock
)paren
suffix:semicolon
id|timers
(braket
id|i
)braket
dot
id|timer
op_assign
l_int|NULL
suffix:semicolon
id|timers
(braket
id|i
)braket
dot
id|cpu
op_assign
l_int|0
suffix:semicolon
id|timers
(braket
id|i
)braket
dot
id|i
op_assign
id|i
op_mod
id|NUM_COMPARATORS
suffix:semicolon
id|tasklet_init
c_func
(paren
op_amp
id|timers
(braket
id|i
)braket
dot
id|tasklet
comma
id|mmtimer_tasklet
comma
(paren
r_int
r_int
)paren
(paren
id|timers
op_plus
id|i
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|SGI_MMTIMER_VECTOR
comma
id|mmtimer_interrupt
comma
id|SA_PERCPU_IRQ
comma
id|MMTIMER_NAME
comma
l_int|NULL
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: unable to allocate interrupt.&quot;
comma
id|MMTIMER_NAME
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|strcpy
c_func
(paren
id|mmtimer_miscdev.devfs_name
comma
id|MMTIMER_NAME
)paren
suffix:semicolon
r_if
c_cond
(paren
id|misc_register
c_func
(paren
op_amp
id|mmtimer_miscdev
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: failed to register device&bslash;n&quot;
comma
id|MMTIMER_NAME
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|sgi_clock_period
op_assign
id|sgi_clock.res
op_assign
id|NSEC_PER_SEC
op_div
id|sn_rtc_cycles_per_second
suffix:semicolon
id|register_posix_clock
c_func
(paren
id|CLOCK_SGI_CYCLE
comma
op_amp
id|sgi_clock
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: v%s, %ld MHz&bslash;n&quot;
comma
id|MMTIMER_DESC
comma
id|MMTIMER_VERSION
comma
id|sn_rtc_cycles_per_second
op_div
(paren
r_int
r_int
)paren
l_float|1E6
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|mmtimer_init
id|module_init
c_func
(paren
id|mmtimer_init
)paren
suffix:semicolon
eof
