multiline_comment|/*&n; * CMOS/NV-RAM driver for Linux&n; *&n; * Copyright (C) 1997 Roman Hodek &lt;Roman.Hodek@informatik.uni-erlangen.de&gt;&n; * idea by and with help from Richard Jelinek &lt;rj@suse.de&gt;&n; *&n; * This driver allows you to access the contents of the non-volatile memory in&n; * the mc146818rtc.h real-time clock. This chip is built into all PCs and into&n; * many Atari machines. In the former it&squot;s called &quot;CMOS-RAM&quot;, in the latter&n; * &quot;NVRAM&quot; (NV stands for non-volatile).&n; *&n; * The data are supplied as a (seekable) character device, /dev/nvram. The&n; * size of this file is 50, the number of freely available bytes in the memory&n; * (i.e., not used by the RTC itself).&n; * &n; * Checksums over the NVRAM contents are managed by this driver. In case of a&n; * bad checksum, reads and writes return -EIO. The checksum can be initialized&n; * to a sane state either by ioctl(NVRAM_INIT) (clear whole NVRAM) or&n; * ioctl(NVRAM_SETCKS) (doesn&squot;t change contents, just makes checksum valid&n; * again; use with care!)&n; *&n; * This file also provides some functions for other parts of the kernel that&n; * want to access the NVRAM: nvram_{read,write,check_checksum,set_checksum}.&n; * Obviously this can be used only if this driver is always configured into&n; * the kernel and is not a module. Since the functions are used by some Atari&n; * drivers, this is the case on the Atari.&n; *&n; *&n; * &t;1.1&t;Cesar Barros: SMP locking fixes&n; * &t;&t;added changelog&n; */
DECL|macro|NVRAM_VERSION
mdefine_line|#define NVRAM_VERSION&t;&t;&quot;1.1&quot;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
DECL|macro|PC
mdefine_line|#define PC&t;&t;1
DECL|macro|ATARI
mdefine_line|#define ATARI&t;&t;2
multiline_comment|/* select machine configuration */
macro_line|#if defined(CONFIG_ATARI)
DECL|macro|MACH
mdefine_line|#define MACH ATARI
macro_line|#elif defined(__i386__) || defined(__x86_64__) || defined(__arm__)  /* and others?? */
DECL|macro|MACH
mdefine_line|#define MACH PC
macro_line|#else
macro_line|#error Cannot build nvram driver for this machine configuration.
macro_line|#endif
macro_line|#if MACH == PC
multiline_comment|/* RTC in a PC */
DECL|macro|CHECK_DRIVER_INIT
mdefine_line|#define CHECK_DRIVER_INIT()&t;1
multiline_comment|/* On PCs, the checksum is built only over bytes 2..31 */
DECL|macro|PC_CKS_RANGE_START
mdefine_line|#define PC_CKS_RANGE_START&t;2
DECL|macro|PC_CKS_RANGE_END
mdefine_line|#define PC_CKS_RANGE_END&t;31
DECL|macro|PC_CKS_LOC
mdefine_line|#define PC_CKS_LOC&t;&t;32
DECL|macro|mach_check_checksum
mdefine_line|#define&t;mach_check_checksum&t;pc_check_checksum
DECL|macro|mach_set_checksum
mdefine_line|#define&t;mach_set_checksum&t;pc_set_checksum
DECL|macro|mach_proc_infos
mdefine_line|#define&t;mach_proc_infos&t;&t;pc_proc_infos
macro_line|#endif
macro_line|#if MACH == ATARI
multiline_comment|/* Special parameters for RTC in Atari machines */
macro_line|#include &lt;asm/atarihw.h&gt;
macro_line|#include &lt;asm/atariints.h&gt;
DECL|macro|RTC_PORT
mdefine_line|#define RTC_PORT(x)&t;&t;(TT_RTC_BAS + 2*(x))
DECL|macro|CHECK_DRIVER_INIT
mdefine_line|#define CHECK_DRIVER_INIT()&t;(MACH_IS_ATARI &amp;&amp; ATARIHW_PRESENT(TT_CLK))
multiline_comment|/* On Ataris, the checksum is over all bytes except the checksum bytes&n; * themselves; these are at the very end */
DECL|macro|ATARI_CKS_RANGE_START
mdefine_line|#define ATARI_CKS_RANGE_START&t;0
DECL|macro|ATARI_CKS_RANGE_END
mdefine_line|#define ATARI_CKS_RANGE_END&t;47
DECL|macro|ATARI_CKS_LOC
mdefine_line|#define ATARI_CKS_LOC&t;&t;48
DECL|macro|mach_check_checksum
mdefine_line|#define&t;mach_check_checksum&t;atari_check_checksum
DECL|macro|mach_set_checksum
mdefine_line|#define&t;mach_set_checksum&t;atari_set_checksum
DECL|macro|mach_proc_infos
mdefine_line|#define&t;mach_proc_infos&t;&t;atari_proc_infos
macro_line|#endif
multiline_comment|/* Note that *all* calls to CMOS_READ and CMOS_WRITE must be done with&n; * rtc_lock held. Due to the index-port/data-port design of the RTC, we&n; * don&squot;t want two different things trying to get to it at once. (e.g. the&n; * periodic 11 min sync from time.c vs. this driver.)&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/mc146818rtc.h&gt;
macro_line|#include &lt;linux/nvram.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
DECL|variable|nvram_open_cnt
r_static
r_int
id|nvram_open_cnt
suffix:semicolon
multiline_comment|/* #times opened */
DECL|variable|nvram_open_mode
r_static
r_int
id|nvram_open_mode
suffix:semicolon
multiline_comment|/* special open modes */
DECL|variable|nvram_open_lock
r_static
id|spinlock_t
id|nvram_open_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
multiline_comment|/* guards &n;&t;&t;&t;&t;&t;&t;&t; * nvram_open_cnt and&n;&t;&t;&t;&t;&t;&t;&t; * nvram_open_mode */
DECL|macro|NVRAM_WRITE
mdefine_line|#define&t;NVRAM_WRITE&t;&t;1&t;/* opened for writing (exclusive) */
DECL|macro|NVRAM_EXCL
mdefine_line|#define&t;NVRAM_EXCL&t;&t;2&t;/* opened with O_EXCL */
DECL|macro|RTC_FIRST_BYTE
mdefine_line|#define&t;RTC_FIRST_BYTE&t;&t;14&t;/* RTC register number of first&n;&t;&t;&t;&t;&t; * NVRAM byte */
DECL|macro|NVRAM_BYTES
mdefine_line|#define&t;NVRAM_BYTES&t;&t;128-RTC_FIRST_BYTE /* number of NVRAM bytes */
r_static
r_int
id|mach_check_checksum
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
id|mach_set_checksum
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PROC_FS
r_static
r_int
id|mach_proc_infos
c_func
(paren
r_int
r_char
op_star
id|contents
comma
r_char
op_star
id|buffer
comma
r_int
op_star
id|len
comma
id|off_t
op_star
id|begin
comma
id|off_t
id|offset
comma
r_int
id|size
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * These are the internal NVRAM access functions, which do NOT disable&n; * interrupts and do not check the checksum. Both tasks are left to higher&n; * level function, so they need to be done only once per syscall.&n; */
r_static
id|__inline__
r_int
r_char
DECL|function|nvram_read_int
id|nvram_read_int
c_func
(paren
r_int
id|i
)paren
(brace
r_return
(paren
id|CMOS_READ
c_func
(paren
id|RTC_FIRST_BYTE
op_plus
id|i
)paren
)paren
suffix:semicolon
)brace
r_static
id|__inline__
r_void
DECL|function|nvram_write_int
id|nvram_write_int
c_func
(paren
r_int
r_char
id|c
comma
r_int
id|i
)paren
(brace
id|CMOS_WRITE
c_func
(paren
id|c
comma
id|RTC_FIRST_BYTE
op_plus
id|i
)paren
suffix:semicolon
)brace
r_static
id|__inline__
r_int
DECL|function|nvram_check_checksum_int
id|nvram_check_checksum_int
c_func
(paren
r_void
)paren
(brace
r_return
(paren
id|mach_check_checksum
c_func
(paren
)paren
)paren
suffix:semicolon
)brace
r_static
id|__inline__
r_void
DECL|function|nvram_set_checksum_int
id|nvram_set_checksum_int
c_func
(paren
r_void
)paren
(brace
id|mach_set_checksum
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#if MACH == ATARI
multiline_comment|/*&n; * These non-internal functions are provided to be called by other parts of&n; * the kernel. It&squot;s up to the caller to ensure correct checksum before reading&n; * or after writing (needs to be done only once).&n; *&n; * They&squot;re only built if CONFIG_ATARI is defined, because Atari drivers use&n; * them. For other configurations (PC), the rest of the kernel can&squot;t rely on&n; * them being present (this driver may not be configured at all, or as a&n; * module), so they access config information themselves.&n; */
r_int
r_char
DECL|function|nvram_read_byte
id|nvram_read_byte
c_func
(paren
r_int
id|i
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
r_char
id|c
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|rtc_lock
comma
id|flags
)paren
suffix:semicolon
id|c
op_assign
id|nvram_read_int
c_func
(paren
id|i
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|rtc_lock
comma
id|flags
)paren
suffix:semicolon
r_return
(paren
id|c
)paren
suffix:semicolon
)brace
multiline_comment|/* This races nicely with trying to read with checksum checking (nvram_read) */
r_void
DECL|function|nvram_write_byte
id|nvram_write_byte
c_func
(paren
r_int
r_char
id|c
comma
r_int
id|i
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|rtc_lock
comma
id|flags
)paren
suffix:semicolon
id|nvram_write_int
c_func
(paren
id|c
comma
id|i
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|rtc_lock
comma
id|flags
)paren
suffix:semicolon
)brace
r_int
DECL|function|nvram_check_checksum
id|nvram_check_checksum
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|rv
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|rtc_lock
comma
id|flags
)paren
suffix:semicolon
id|rv
op_assign
id|nvram_check_checksum_int
c_func
(paren
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|rtc_lock
comma
id|flags
)paren
suffix:semicolon
r_return
(paren
id|rv
)paren
suffix:semicolon
)brace
r_void
DECL|function|nvram_set_checksum
id|nvram_set_checksum
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|rtc_lock
comma
id|flags
)paren
suffix:semicolon
id|nvram_set_checksum_int
c_func
(paren
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|rtc_lock
comma
id|flags
)paren
suffix:semicolon
)brace
macro_line|#endif /* MACH == ATARI */
multiline_comment|/*&n; * The are the file operation function for user access to /dev/nvram&n; */
r_static
r_int
r_int
DECL|function|nvram_llseek
id|nvram_llseek
c_func
(paren
r_struct
id|file
op_star
id|file
comma
id|loff_t
id|offset
comma
r_int
id|origin
)paren
(brace
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|origin
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/* nothing to do */
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|offset
op_add_assign
id|file-&gt;f_pos
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|offset
op_add_assign
id|NVRAM_BYTES
suffix:semicolon
r_break
suffix:semicolon
)brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
(paren
(paren
id|offset
op_ge
l_int|0
)paren
ques
c_cond
(paren
id|file-&gt;f_pos
op_assign
id|offset
)paren
suffix:colon
op_minus
id|EINVAL
)paren
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|nvram_read
id|nvram_read
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_char
id|contents
(braket
id|NVRAM_BYTES
)braket
suffix:semicolon
r_int
id|i
op_assign
op_star
id|ppos
suffix:semicolon
r_char
op_star
id|tmp
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|rtc_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nvram_check_checksum_int
c_func
(paren
)paren
)paren
r_goto
id|checksum_err
suffix:semicolon
r_for
c_loop
(paren
id|tmp
op_assign
id|contents
suffix:semicolon
id|count
op_decrement
OG
l_int|0
op_logical_and
id|i
OL
id|NVRAM_BYTES
suffix:semicolon
op_increment
id|i
comma
op_increment
id|tmp
)paren
op_star
id|tmp
op_assign
id|nvram_read_int
c_func
(paren
id|i
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|rtc_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buf
comma
id|contents
comma
id|tmp
op_minus
id|contents
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
op_star
id|ppos
op_assign
id|i
suffix:semicolon
r_return
(paren
id|tmp
op_minus
id|contents
)paren
suffix:semicolon
id|checksum_err
suffix:colon
id|spin_unlock_irq
c_func
(paren
op_amp
id|rtc_lock
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|nvram_write
id|nvram_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_char
id|contents
(braket
id|NVRAM_BYTES
)braket
suffix:semicolon
r_int
id|i
op_assign
op_star
id|ppos
suffix:semicolon
r_char
op_star
id|tmp
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|contents
comma
id|buf
comma
(paren
id|NVRAM_BYTES
op_minus
id|i
)paren
OL
id|count
ques
c_cond
(paren
id|NVRAM_BYTES
op_minus
id|i
)paren
suffix:colon
id|count
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|rtc_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nvram_check_checksum_int
c_func
(paren
)paren
)paren
r_goto
id|checksum_err
suffix:semicolon
r_for
c_loop
(paren
id|tmp
op_assign
id|contents
suffix:semicolon
id|count
op_decrement
OG
l_int|0
op_logical_and
id|i
OL
id|NVRAM_BYTES
suffix:semicolon
op_increment
id|i
comma
op_increment
id|tmp
)paren
id|nvram_write_int
c_func
(paren
op_star
id|tmp
comma
id|i
)paren
suffix:semicolon
id|nvram_set_checksum_int
c_func
(paren
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|rtc_lock
)paren
suffix:semicolon
op_star
id|ppos
op_assign
id|i
suffix:semicolon
r_return
(paren
id|tmp
op_minus
id|contents
)paren
suffix:semicolon
id|checksum_err
suffix:colon
id|spin_unlock_irq
c_func
(paren
op_amp
id|rtc_lock
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_static
r_int
DECL|function|nvram_ioctl
id|nvram_ioctl
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
id|i
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|NVRAM_INIT
suffix:colon
multiline_comment|/* initialize NVRAM contents and checksum */
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
r_return
(paren
op_minus
id|EACCES
)paren
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|rtc_lock
)paren
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
id|NVRAM_BYTES
suffix:semicolon
op_increment
id|i
)paren
id|nvram_write_int
c_func
(paren
l_int|0
comma
id|i
)paren
suffix:semicolon
id|nvram_set_checksum_int
c_func
(paren
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|rtc_lock
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
r_case
id|NVRAM_SETCKS
suffix:colon
multiline_comment|/* just set checksum, contents unchanged&n;&t;&t;&t;&t; * (maybe useful after checksum garbaged&n;&t;&t;&t;&t; * somehow...) */
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
r_return
(paren
op_minus
id|EACCES
)paren
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|rtc_lock
)paren
suffix:semicolon
id|nvram_set_checksum_int
c_func
(paren
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|rtc_lock
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
r_default
suffix:colon
r_return
(paren
op_minus
id|ENOTTY
)paren
suffix:semicolon
)brace
)brace
r_static
r_int
DECL|function|nvram_open
id|nvram_open
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
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|nvram_open_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|nvram_open_cnt
op_logical_and
(paren
id|file-&gt;f_flags
op_amp
id|O_EXCL
)paren
)paren
op_logical_or
(paren
id|nvram_open_mode
op_amp
id|NVRAM_EXCL
)paren
op_logical_or
(paren
(paren
id|file-&gt;f_mode
op_amp
l_int|2
)paren
op_logical_and
(paren
id|nvram_open_mode
op_amp
id|NVRAM_WRITE
)paren
)paren
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|nvram_open_lock
)paren
suffix:semicolon
r_return
(paren
op_minus
id|EBUSY
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|file-&gt;f_flags
op_amp
id|O_EXCL
)paren
id|nvram_open_mode
op_or_assign
id|NVRAM_EXCL
suffix:semicolon
r_if
c_cond
(paren
id|file-&gt;f_mode
op_amp
l_int|2
)paren
id|nvram_open_mode
op_or_assign
id|NVRAM_WRITE
suffix:semicolon
id|nvram_open_cnt
op_increment
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|nvram_open_lock
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|nvram_release
id|nvram_release
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
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|nvram_open_lock
)paren
suffix:semicolon
id|nvram_open_cnt
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|file-&gt;f_flags
op_amp
id|O_EXCL
)paren
id|nvram_open_mode
op_and_assign
op_complement
id|NVRAM_EXCL
suffix:semicolon
r_if
c_cond
(paren
id|file-&gt;f_mode
op_amp
l_int|2
)paren
id|nvram_open_mode
op_and_assign
op_complement
id|NVRAM_WRITE
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|nvram_open_lock
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
macro_line|#ifndef CONFIG_PROC_FS
r_static
r_int
DECL|function|nvram_read_proc
id|nvram_read_proc
c_func
(paren
r_char
op_star
id|buffer
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|size
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#else
r_static
r_int
DECL|function|nvram_read_proc
id|nvram_read_proc
c_func
(paren
r_char
op_star
id|buffer
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|size
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
(brace
r_int
r_char
id|contents
(braket
id|NVRAM_BYTES
)braket
suffix:semicolon
r_int
id|i
comma
id|len
op_assign
l_int|0
suffix:semicolon
id|off_t
id|begin
op_assign
l_int|0
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|rtc_lock
)paren
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
id|NVRAM_BYTES
suffix:semicolon
op_increment
id|i
)paren
id|contents
(braket
id|i
)braket
op_assign
id|nvram_read_int
c_func
(paren
id|i
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|rtc_lock
)paren
suffix:semicolon
op_star
id|eof
op_assign
id|mach_proc_infos
c_func
(paren
id|contents
comma
id|buffer
comma
op_amp
id|len
comma
op_amp
id|begin
comma
id|offset
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|offset
op_ge
id|begin
op_plus
id|len
)paren
r_return
(paren
l_int|0
)paren
suffix:semicolon
op_star
id|start
op_assign
id|buffer
op_plus
(paren
id|offset
op_minus
id|begin
)paren
suffix:semicolon
r_return
(paren
id|size
OL
id|begin
op_plus
id|len
op_minus
id|offset
ques
c_cond
id|size
suffix:colon
id|begin
op_plus
id|len
op_minus
id|offset
)paren
suffix:semicolon
)brace
multiline_comment|/* This macro frees the machine specific function from bounds checking and&n; * this like that... */
DECL|macro|PRINT_PROC
mdefine_line|#define&t;PRINT_PROC(fmt,args...)&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;*len += sprintf( buffer+*len, fmt, ##args );&t;&bslash;&n;&t;&t;if (*begin + *len &gt; offset + size)&t;&t;&bslash;&n;&t;&t;&t;return( 0 );&t;&t;&t;&t;&bslash;&n;&t;&t;if (*begin + *len &lt; offset) {&t;&t;&t;&bslash;&n;&t;&t;&t;*begin += *len;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;*len = 0;&t;&t;&t;&t;&bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;&bslash;&n;&t;} while(0)
macro_line|#endif /* CONFIG_PROC_FS */
DECL|variable|nvram_fops
r_static
r_struct
id|file_operations
id|nvram_fops
op_assign
(brace
id|owner
suffix:colon
id|THIS_MODULE
comma
id|llseek
suffix:colon
id|nvram_llseek
comma
id|read
suffix:colon
id|nvram_read
comma
id|write
suffix:colon
id|nvram_write
comma
id|ioctl
suffix:colon
id|nvram_ioctl
comma
id|open
suffix:colon
id|nvram_open
comma
id|release
suffix:colon
id|nvram_release
comma
)brace
suffix:semicolon
DECL|variable|nvram_dev
r_static
r_struct
id|miscdevice
id|nvram_dev
op_assign
(brace
id|NVRAM_MINOR
comma
l_string|&quot;nvram&quot;
comma
op_amp
id|nvram_fops
)brace
suffix:semicolon
r_static
r_int
id|__init
DECL|function|nvram_init
id|nvram_init
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
suffix:semicolon
multiline_comment|/* First test whether the driver should init at all */
r_if
c_cond
(paren
op_logical_neg
id|CHECK_DRIVER_INIT
c_func
(paren
)paren
)paren
r_return
(paren
op_minus
id|ENXIO
)paren
suffix:semicolon
id|ret
op_assign
id|misc_register
c_func
(paren
op_amp
id|nvram_dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;nvram: can&squot;t misc_register on minor=%d&bslash;n&quot;
comma
id|NVRAM_MINOR
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|create_proc_read_entry
c_func
(paren
l_string|&quot;driver/nvram&quot;
comma
l_int|0
comma
l_int|0
comma
id|nvram_read_proc
comma
l_int|NULL
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;nvram: can&squot;t create /proc/driver/nvram&bslash;n&quot;
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|outmisc
suffix:semicolon
)brace
id|ret
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Non-volatile memory driver v&quot;
id|NVRAM_VERSION
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|out
suffix:colon
r_return
(paren
id|ret
)paren
suffix:semicolon
id|outmisc
suffix:colon
id|misc_deregister
c_func
(paren
op_amp
id|nvram_dev
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_static
r_void
id|__exit
DECL|function|nvram_cleanup_module
id|nvram_cleanup_module
c_func
(paren
r_void
)paren
(brace
id|remove_proc_entry
c_func
(paren
l_string|&quot;driver/nvram&quot;
comma
l_int|0
)paren
suffix:semicolon
id|misc_deregister
c_func
(paren
op_amp
id|nvram_dev
)paren
suffix:semicolon
)brace
DECL|variable|nvram_init
id|module_init
c_func
(paren
id|nvram_init
)paren
suffix:semicolon
DECL|variable|nvram_cleanup_module
id|module_exit
c_func
(paren
id|nvram_cleanup_module
)paren
suffix:semicolon
multiline_comment|/*&n; * Machine specific functions&n; */
macro_line|#if MACH == PC
r_static
r_int
DECL|function|pc_check_checksum
id|pc_check_checksum
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_int
id|sum
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|PC_CKS_RANGE_START
suffix:semicolon
id|i
op_le
id|PC_CKS_RANGE_END
suffix:semicolon
op_increment
id|i
)paren
id|sum
op_add_assign
id|nvram_read_int
c_func
(paren
id|i
)paren
suffix:semicolon
r_return
(paren
(paren
id|sum
op_amp
l_int|0xffff
)paren
op_eq
(paren
(paren
id|nvram_read_int
c_func
(paren
id|PC_CKS_LOC
)paren
op_lshift
l_int|8
)paren
op_or
id|nvram_read_int
c_func
(paren
id|PC_CKS_LOC
op_plus
l_int|1
)paren
)paren
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|pc_set_checksum
id|pc_set_checksum
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_int
id|sum
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|PC_CKS_RANGE_START
suffix:semicolon
id|i
op_le
id|PC_CKS_RANGE_END
suffix:semicolon
op_increment
id|i
)paren
id|sum
op_add_assign
id|nvram_read_int
c_func
(paren
id|i
)paren
suffix:semicolon
id|nvram_write_int
c_func
(paren
id|sum
op_rshift
l_int|8
comma
id|PC_CKS_LOC
)paren
suffix:semicolon
id|nvram_write_int
c_func
(paren
id|sum
op_amp
l_int|0xff
comma
id|PC_CKS_LOC
op_plus
l_int|1
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_PROC_FS
DECL|variable|floppy_types
r_static
r_char
op_star
id|floppy_types
(braket
)braket
op_assign
(brace
l_string|&quot;none&quot;
comma
l_string|&quot;5.25&squot;&squot; 360k&quot;
comma
l_string|&quot;5.25&squot;&squot; 1.2M&quot;
comma
l_string|&quot;3.5&squot;&squot; 720k&quot;
comma
l_string|&quot;3.5&squot;&squot; 1.44M&quot;
comma
l_string|&quot;3.5&squot;&squot; 2.88M&quot;
comma
l_string|&quot;3.5&squot;&squot; 2.88M&quot;
)brace
suffix:semicolon
DECL|variable|gfx_types
r_static
r_char
op_star
id|gfx_types
(braket
)braket
op_assign
(brace
l_string|&quot;EGA, VGA, ... (with BIOS)&quot;
comma
l_string|&quot;CGA (40 cols)&quot;
comma
l_string|&quot;CGA (80 cols)&quot;
comma
l_string|&quot;monochrome&quot;
comma
)brace
suffix:semicolon
r_static
r_int
DECL|function|pc_proc_infos
id|pc_proc_infos
c_func
(paren
r_int
r_char
op_star
id|nvram
comma
r_char
op_star
id|buffer
comma
r_int
op_star
id|len
comma
id|off_t
op_star
id|begin
comma
id|off_t
id|offset
comma
r_int
id|size
)paren
(brace
r_int
id|checksum
suffix:semicolon
r_int
id|type
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|rtc_lock
)paren
suffix:semicolon
id|checksum
op_assign
id|nvram_check_checksum_int
c_func
(paren
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|rtc_lock
)paren
suffix:semicolon
id|PRINT_PROC
c_func
(paren
l_string|&quot;Checksum status: %svalid&bslash;n&quot;
comma
id|checksum
ques
c_cond
l_string|&quot;&quot;
suffix:colon
l_string|&quot;not &quot;
)paren
suffix:semicolon
id|PRINT_PROC
c_func
(paren
l_string|&quot;# floppies     : %d&bslash;n&quot;
comma
(paren
id|nvram
(braket
l_int|6
)braket
op_amp
l_int|1
)paren
ques
c_cond
(paren
id|nvram
(braket
l_int|6
)braket
op_rshift
l_int|6
)paren
op_plus
l_int|1
suffix:colon
l_int|0
)paren
suffix:semicolon
id|PRINT_PROC
c_func
(paren
l_string|&quot;Floppy 0 type  : &quot;
)paren
suffix:semicolon
id|type
op_assign
id|nvram
(braket
l_int|2
)braket
op_rshift
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|type
OL
r_sizeof
(paren
id|floppy_types
)paren
op_div
r_sizeof
(paren
op_star
id|floppy_types
)paren
)paren
id|PRINT_PROC
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|floppy_types
(braket
id|type
)braket
)paren
suffix:semicolon
r_else
id|PRINT_PROC
c_func
(paren
l_string|&quot;%d (unknown)&bslash;n&quot;
comma
id|type
)paren
suffix:semicolon
id|PRINT_PROC
c_func
(paren
l_string|&quot;Floppy 1 type  : &quot;
)paren
suffix:semicolon
id|type
op_assign
id|nvram
(braket
l_int|2
)braket
op_amp
l_int|0x0f
suffix:semicolon
r_if
c_cond
(paren
id|type
OL
r_sizeof
(paren
id|floppy_types
)paren
op_div
r_sizeof
(paren
op_star
id|floppy_types
)paren
)paren
id|PRINT_PROC
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|floppy_types
(braket
id|type
)braket
)paren
suffix:semicolon
r_else
id|PRINT_PROC
c_func
(paren
l_string|&quot;%d (unknown)&bslash;n&quot;
comma
id|type
)paren
suffix:semicolon
id|PRINT_PROC
c_func
(paren
l_string|&quot;HD 0 type      : &quot;
)paren
suffix:semicolon
id|type
op_assign
id|nvram
(braket
l_int|4
)braket
op_rshift
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|type
)paren
id|PRINT_PROC
c_func
(paren
l_string|&quot;%02x&bslash;n&quot;
comma
id|type
op_eq
l_int|0x0f
ques
c_cond
id|nvram
(braket
l_int|11
)braket
suffix:colon
id|type
)paren
suffix:semicolon
r_else
id|PRINT_PROC
c_func
(paren
l_string|&quot;none&bslash;n&quot;
)paren
suffix:semicolon
id|PRINT_PROC
c_func
(paren
l_string|&quot;HD 1 type      : &quot;
)paren
suffix:semicolon
id|type
op_assign
id|nvram
(braket
l_int|4
)braket
op_amp
l_int|0x0f
suffix:semicolon
r_if
c_cond
(paren
id|type
)paren
id|PRINT_PROC
c_func
(paren
l_string|&quot;%02x&bslash;n&quot;
comma
id|type
op_eq
l_int|0x0f
ques
c_cond
id|nvram
(braket
l_int|12
)braket
suffix:colon
id|type
)paren
suffix:semicolon
r_else
id|PRINT_PROC
c_func
(paren
l_string|&quot;none&bslash;n&quot;
)paren
suffix:semicolon
id|PRINT_PROC
c_func
(paren
l_string|&quot;HD type 48 data: %d/%d/%d C/H/S, precomp %d, lz %d&bslash;n&quot;
comma
id|nvram
(braket
l_int|18
)braket
op_or
(paren
id|nvram
(braket
l_int|19
)braket
op_lshift
l_int|8
)paren
comma
id|nvram
(braket
l_int|20
)braket
comma
id|nvram
(braket
l_int|25
)braket
comma
id|nvram
(braket
l_int|21
)braket
op_or
(paren
id|nvram
(braket
l_int|22
)braket
op_lshift
l_int|8
)paren
comma
id|nvram
(braket
l_int|23
)braket
op_or
(paren
id|nvram
(braket
l_int|24
)braket
op_lshift
l_int|8
)paren
)paren
suffix:semicolon
id|PRINT_PROC
c_func
(paren
l_string|&quot;HD type 49 data: %d/%d/%d C/H/S, precomp %d, lz %d&bslash;n&quot;
comma
id|nvram
(braket
l_int|39
)braket
op_or
(paren
id|nvram
(braket
l_int|40
)braket
op_lshift
l_int|8
)paren
comma
id|nvram
(braket
l_int|41
)braket
comma
id|nvram
(braket
l_int|46
)braket
comma
id|nvram
(braket
l_int|42
)braket
op_or
(paren
id|nvram
(braket
l_int|43
)braket
op_lshift
l_int|8
)paren
comma
id|nvram
(braket
l_int|44
)braket
op_or
(paren
id|nvram
(braket
l_int|45
)braket
op_lshift
l_int|8
)paren
)paren
suffix:semicolon
id|PRINT_PROC
c_func
(paren
l_string|&quot;DOS base memory: %d kB&bslash;n&quot;
comma
id|nvram
(braket
l_int|7
)braket
op_or
(paren
id|nvram
(braket
l_int|8
)braket
op_lshift
l_int|8
)paren
)paren
suffix:semicolon
id|PRINT_PROC
c_func
(paren
l_string|&quot;Extended memory: %d kB (configured), %d kB (tested)&bslash;n&quot;
comma
id|nvram
(braket
l_int|9
)braket
op_or
(paren
id|nvram
(braket
l_int|10
)braket
op_lshift
l_int|8
)paren
comma
id|nvram
(braket
l_int|34
)braket
op_or
(paren
id|nvram
(braket
l_int|35
)braket
op_lshift
l_int|8
)paren
)paren
suffix:semicolon
id|PRINT_PROC
c_func
(paren
l_string|&quot;Gfx adapter    : %s&bslash;n&quot;
comma
id|gfx_types
(braket
(paren
id|nvram
(braket
l_int|6
)braket
op_rshift
l_int|4
)paren
op_amp
l_int|3
)braket
)paren
suffix:semicolon
id|PRINT_PROC
c_func
(paren
l_string|&quot;FPU            : %sinstalled&bslash;n&quot;
comma
(paren
id|nvram
(braket
l_int|6
)braket
op_amp
l_int|2
)paren
ques
c_cond
l_string|&quot;&quot;
suffix:colon
l_string|&quot;not &quot;
)paren
suffix:semicolon
r_return
(paren
l_int|1
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#endif /* MACH == PC */
macro_line|#if MACH == ATARI
r_static
r_int
DECL|function|atari_check_checksum
id|atari_check_checksum
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_char
id|sum
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|ATARI_CKS_RANGE_START
suffix:semicolon
id|i
op_le
id|ATARI_CKS_RANGE_END
suffix:semicolon
op_increment
id|i
)paren
id|sum
op_add_assign
id|nvram_read_int
c_func
(paren
id|i
)paren
suffix:semicolon
r_return
(paren
id|nvram_read_int
c_func
(paren
id|ATARI_CKS_LOC
)paren
op_eq
(paren
op_complement
id|sum
op_amp
l_int|0xff
)paren
op_logical_and
id|nvram_read_int
c_func
(paren
id|ATARI_CKS_LOC
op_plus
l_int|1
)paren
op_eq
(paren
id|sum
op_amp
l_int|0xff
)paren
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|atari_set_checksum
id|atari_set_checksum
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_char
id|sum
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|ATARI_CKS_RANGE_START
suffix:semicolon
id|i
op_le
id|ATARI_CKS_RANGE_END
suffix:semicolon
op_increment
id|i
)paren
id|sum
op_add_assign
id|nvram_read_int
c_func
(paren
id|i
)paren
suffix:semicolon
id|nvram_write_int
c_func
(paren
op_complement
id|sum
comma
id|ATARI_CKS_LOC
)paren
suffix:semicolon
id|nvram_write_int
c_func
(paren
id|sum
comma
id|ATARI_CKS_LOC
op_plus
l_int|1
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_PROC_FS
r_static
r_struct
(brace
DECL|member|val
r_int
r_char
id|val
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|variable|boot_prefs
)brace
id|boot_prefs
(braket
)braket
op_assign
(brace
(brace
l_int|0x80
comma
l_string|&quot;TOS&quot;
)brace
comma
(brace
l_int|0x40
comma
l_string|&quot;ASV&quot;
)brace
comma
(brace
l_int|0x20
comma
l_string|&quot;NetBSD (?)&quot;
)brace
comma
(brace
l_int|0x10
comma
l_string|&quot;Linux&quot;
)brace
comma
(brace
l_int|0x00
comma
l_string|&quot;unspecified&quot;
)brace
)brace
suffix:semicolon
DECL|variable|languages
r_static
r_char
op_star
id|languages
(braket
)braket
op_assign
(brace
l_string|&quot;English (US)&quot;
comma
l_string|&quot;German&quot;
comma
l_string|&quot;French&quot;
comma
l_string|&quot;English (UK)&quot;
comma
l_string|&quot;Spanish&quot;
comma
l_string|&quot;Italian&quot;
comma
l_string|&quot;6 (undefined)&quot;
comma
l_string|&quot;Swiss (French)&quot;
comma
l_string|&quot;Swiss (German)&quot;
)brace
suffix:semicolon
DECL|variable|dateformat
r_static
r_char
op_star
id|dateformat
(braket
)braket
op_assign
(brace
l_string|&quot;MM%cDD%cYY&quot;
comma
l_string|&quot;DD%cMM%cYY&quot;
comma
l_string|&quot;YY%cMM%cDD&quot;
comma
l_string|&quot;YY%cDD%cMM&quot;
comma
l_string|&quot;4 (undefined)&quot;
comma
l_string|&quot;5 (undefined)&quot;
comma
l_string|&quot;6 (undefined)&quot;
comma
l_string|&quot;7 (undefined)&quot;
)brace
suffix:semicolon
DECL|variable|colors
r_static
r_char
op_star
id|colors
(braket
)braket
op_assign
(brace
l_string|&quot;2&quot;
comma
l_string|&quot;4&quot;
comma
l_string|&quot;16&quot;
comma
l_string|&quot;256&quot;
comma
l_string|&quot;65536&quot;
comma
l_string|&quot;??&quot;
comma
l_string|&quot;??&quot;
comma
l_string|&quot;??&quot;
)brace
suffix:semicolon
DECL|macro|fieldsize
mdefine_line|#define fieldsize(a)&t;(sizeof(a)/sizeof(*a))
r_static
r_int
DECL|function|atari_proc_infos
id|atari_proc_infos
c_func
(paren
r_int
r_char
op_star
id|nvram
comma
r_char
op_star
id|buffer
comma
r_int
op_star
id|len
comma
id|off_t
op_star
id|begin
comma
id|off_t
id|offset
comma
r_int
id|size
)paren
(brace
r_int
id|checksum
op_assign
id|nvram_check_checksum
c_func
(paren
)paren
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|vmode
suffix:semicolon
id|PRINT_PROC
c_func
(paren
l_string|&quot;Checksum status  : %svalid&bslash;n&quot;
comma
id|checksum
ques
c_cond
l_string|&quot;&quot;
suffix:colon
l_string|&quot;not &quot;
)paren
suffix:semicolon
id|PRINT_PROC
c_func
(paren
l_string|&quot;Boot preference  : &quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|fieldsize
c_func
(paren
id|boot_prefs
)paren
op_minus
l_int|1
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
op_decrement
id|i
)paren
(brace
r_if
c_cond
(paren
id|nvram
(braket
l_int|1
)braket
op_eq
id|boot_prefs
(braket
id|i
)braket
dot
id|val
)paren
(brace
id|PRINT_PROC
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|boot_prefs
(braket
id|i
)braket
dot
id|name
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|i
OL
l_int|0
)paren
id|PRINT_PROC
c_func
(paren
l_string|&quot;0x%02x (undefined)&bslash;n&quot;
comma
id|nvram
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|PRINT_PROC
c_func
(paren
l_string|&quot;SCSI arbitration : %s&bslash;n&quot;
comma
(paren
id|nvram
(braket
l_int|16
)braket
op_amp
l_int|0x80
)paren
ques
c_cond
l_string|&quot;on&quot;
suffix:colon
l_string|&quot;off&quot;
)paren
suffix:semicolon
id|PRINT_PROC
c_func
(paren
l_string|&quot;SCSI host ID     : &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nvram
(braket
l_int|16
)braket
op_amp
l_int|0x80
)paren
id|PRINT_PROC
c_func
(paren
l_string|&quot;%d&bslash;n&quot;
comma
id|nvram
(braket
l_int|16
)braket
op_amp
l_int|7
)paren
suffix:semicolon
r_else
id|PRINT_PROC
c_func
(paren
l_string|&quot;n/a&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* the following entries are defined only for the Falcon */
r_if
c_cond
(paren
(paren
id|atari_mch_cookie
op_rshift
l_int|16
)paren
op_ne
id|ATARI_MCH_FALCON
)paren
r_return
l_int|1
suffix:semicolon
id|PRINT_PROC
c_func
(paren
l_string|&quot;OS language      : &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nvram
(braket
l_int|6
)braket
OL
id|fieldsize
c_func
(paren
id|languages
)paren
)paren
id|PRINT_PROC
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|languages
(braket
id|nvram
(braket
l_int|6
)braket
)braket
)paren
suffix:semicolon
r_else
id|PRINT_PROC
c_func
(paren
l_string|&quot;%u (undefined)&bslash;n&quot;
comma
id|nvram
(braket
l_int|6
)braket
)paren
suffix:semicolon
id|PRINT_PROC
c_func
(paren
l_string|&quot;Keyboard language: &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nvram
(braket
l_int|7
)braket
OL
id|fieldsize
c_func
(paren
id|languages
)paren
)paren
id|PRINT_PROC
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|languages
(braket
id|nvram
(braket
l_int|7
)braket
)braket
)paren
suffix:semicolon
r_else
id|PRINT_PROC
c_func
(paren
l_string|&quot;%u (undefined)&bslash;n&quot;
comma
id|nvram
(braket
l_int|7
)braket
)paren
suffix:semicolon
id|PRINT_PROC
c_func
(paren
l_string|&quot;Date format      : &quot;
)paren
suffix:semicolon
id|PRINT_PROC
c_func
(paren
id|dateformat
(braket
id|nvram
(braket
l_int|8
)braket
op_amp
l_int|7
)braket
comma
id|nvram
(braket
l_int|9
)braket
ques
c_cond
id|nvram
(braket
l_int|9
)braket
suffix:colon
l_char|&squot;/&squot;
comma
id|nvram
(braket
l_int|9
)braket
ques
c_cond
id|nvram
(braket
l_int|9
)braket
suffix:colon
l_char|&squot;/&squot;
)paren
suffix:semicolon
id|PRINT_PROC
c_func
(paren
l_string|&quot;, %dh clock&bslash;n&quot;
comma
id|nvram
(braket
l_int|8
)braket
op_amp
l_int|16
ques
c_cond
l_int|24
suffix:colon
l_int|12
)paren
suffix:semicolon
id|PRINT_PROC
c_func
(paren
l_string|&quot;Boot delay       : &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nvram
(braket
l_int|10
)braket
op_eq
l_int|0
)paren
id|PRINT_PROC
c_func
(paren
l_string|&quot;default&quot;
)paren
suffix:semicolon
r_else
id|PRINT_PROC
c_func
(paren
l_string|&quot;%ds%s&bslash;n&quot;
comma
id|nvram
(braket
l_int|10
)braket
comma
id|nvram
(braket
l_int|10
)braket
OL
l_int|8
ques
c_cond
l_string|&quot;, no memory test&quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
id|vmode
op_assign
(paren
id|nvram
(braket
l_int|14
)braket
op_lshift
l_int|8
)paren
op_logical_or
id|nvram
(braket
l_int|15
)braket
suffix:semicolon
id|PRINT_PROC
c_func
(paren
l_string|&quot;Video mode       : %s colors, %d columns, %s %s monitor&bslash;n&quot;
comma
id|colors
(braket
id|vmode
op_amp
l_int|7
)braket
comma
id|vmode
op_amp
l_int|8
ques
c_cond
l_int|80
suffix:colon
l_int|40
comma
id|vmode
op_amp
l_int|16
ques
c_cond
l_string|&quot;VGA&quot;
suffix:colon
l_string|&quot;TV&quot;
comma
id|vmode
op_amp
l_int|32
ques
c_cond
l_string|&quot;PAL&quot;
suffix:colon
l_string|&quot;NTSC&quot;
)paren
suffix:semicolon
id|PRINT_PROC
c_func
(paren
l_string|&quot;                   %soverscan, compat. mode %s%s&bslash;n&quot;
comma
id|vmode
op_amp
l_int|64
ques
c_cond
l_string|&quot;&quot;
suffix:colon
l_string|&quot;no &quot;
comma
id|vmode
op_amp
l_int|128
ques
c_cond
l_string|&quot;on&quot;
suffix:colon
l_string|&quot;off&quot;
comma
id|vmode
op_amp
l_int|256
ques
c_cond
(paren
id|vmode
op_amp
l_int|16
ques
c_cond
l_string|&quot;, line doubling&quot;
suffix:colon
l_string|&quot;, half screen&quot;
)paren
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
r_return
(paren
l_int|1
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#endif /* MACH == ATARI */
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
