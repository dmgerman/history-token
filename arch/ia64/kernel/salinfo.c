multiline_comment|/*&n; * salinfo.c&n; *&n; * Creates entries in /proc/sal for various system features.&n; *&n; * Copyright (c) 2003 Silicon Graphics, Inc.  All rights reserved.&n; * Copyright (c) 2003 Hewlett-Packard Co&n; *&t;Bjorn Helgaas &lt;bjorn.helgaas@hp.com&gt;&n; *&n; * 10/30/2001&t;jbarnes@sgi.com&t;&t;copied much of Stephane&squot;s palinfo&n; *&t;&t;&t;&t;&t;code to create this file&n; * Oct 23 2003&t;kaos@sgi.com&n; *   Replace IPI with set_cpus_allowed() to read a record from the required cpu.&n; *   Redesign salinfo log processing to separate interrupt and user space&n; *   contexts.&n; *   Cache the record across multi-block reads from user space.&n; *   Support &gt; 64 cpus.&n; *   Delete module_exit and MOD_INC/DEC_COUNT, salinfo cannot be a module.&n; *&n; * Jan 28 2004&t;kaos@sgi.com&n; *   Periodically check for outstanding MCA or INIT records.&n; *&n; * Dec  5 2004&t;kaos@sgi.com&n; *   Standardize which records are cleared automatically.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &lt;asm/sal.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Jesse Barnes &lt;jbarnes@sgi.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;/proc interface to IA-64 SAL features&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
r_static
r_int
id|salinfo_read
c_func
(paren
r_char
op_star
id|page
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|off
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/* name of the proc entry */
DECL|member|feature
r_int
r_int
id|feature
suffix:semicolon
multiline_comment|/* feature bit */
DECL|member|entry
r_struct
id|proc_dir_entry
op_star
id|entry
suffix:semicolon
multiline_comment|/* registered entry (removal) */
DECL|typedef|salinfo_entry_t
)brace
id|salinfo_entry_t
suffix:semicolon
multiline_comment|/*&n; * List {name,feature} pairs for every entry in /proc/sal/&lt;feature&gt;&n; * that this module exports&n; */
DECL|variable|salinfo_entries
r_static
id|salinfo_entry_t
id|salinfo_entries
(braket
)braket
op_assign
initialization_block
suffix:semicolon
DECL|macro|NR_SALINFO_ENTRIES
mdefine_line|#define NR_SALINFO_ENTRIES ARRAY_SIZE(salinfo_entries)
DECL|variable|salinfo_log_name
r_static
r_char
op_star
id|salinfo_log_name
(braket
)braket
op_assign
(brace
l_string|&quot;mca&quot;
comma
l_string|&quot;init&quot;
comma
l_string|&quot;cmc&quot;
comma
l_string|&quot;cpe&quot;
comma
)brace
suffix:semicolon
DECL|variable|salinfo_proc_entries
r_static
r_struct
id|proc_dir_entry
op_star
id|salinfo_proc_entries
(braket
id|ARRAY_SIZE
c_func
(paren
id|salinfo_entries
)paren
op_plus
multiline_comment|/* /proc/sal/bus_lock */
id|ARRAY_SIZE
c_func
(paren
id|salinfo_log_name
)paren
op_plus
multiline_comment|/* /proc/sal/{mca,...} */
(paren
l_int|2
op_star
id|ARRAY_SIZE
c_func
(paren
id|salinfo_log_name
)paren
)paren
op_plus
multiline_comment|/* /proc/sal/mca/{event,data} */
l_int|1
)braket
suffix:semicolon
multiline_comment|/* /proc/sal */
multiline_comment|/* Some records we get ourselves, some are accessed as saved data in buffers&n; * that are owned by mca.c.&n; */
DECL|struct|salinfo_data_saved
r_struct
id|salinfo_data_saved
(brace
DECL|member|buffer
id|u8
op_star
id|buffer
suffix:semicolon
DECL|member|size
id|u64
id|size
suffix:semicolon
DECL|member|id
id|u64
id|id
suffix:semicolon
DECL|member|cpu
r_int
id|cpu
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* State transitions.  Actions are :-&n; *   Write &quot;read &lt;cpunum&gt;&quot; to the data file.&n; *   Write &quot;clear &lt;cpunum&gt;&quot; to the data file.&n; *   Write &quot;oemdata &lt;cpunum&gt; &lt;offset&gt; to the data file.&n; *   Read from the data file.&n; *   Close the data file.&n; *&n; * Start state is NO_DATA.&n; *&n; * NO_DATA&n; *    write &quot;read &lt;cpunum&gt;&quot; -&gt; NO_DATA or LOG_RECORD.&n; *    write &quot;clear &lt;cpunum&gt;&quot; -&gt; NO_DATA or LOG_RECORD.&n; *    write &quot;oemdata &lt;cpunum&gt; &lt;offset&gt; -&gt; return -EINVAL.&n; *    read data -&gt; return EOF.&n; *    close -&gt; unchanged.  Free record areas.&n; *&n; * LOG_RECORD&n; *    write &quot;read &lt;cpunum&gt;&quot; -&gt; NO_DATA or LOG_RECORD.&n; *    write &quot;clear &lt;cpunum&gt;&quot; -&gt; NO_DATA or LOG_RECORD.&n; *    write &quot;oemdata &lt;cpunum&gt; &lt;offset&gt; -&gt; format the oem data, goto OEMDATA.&n; *    read data -&gt; return the INIT/MCA/CMC/CPE record.&n; *    close -&gt; unchanged.  Keep record areas.&n; *&n; * OEMDATA&n; *    write &quot;read &lt;cpunum&gt;&quot; -&gt; NO_DATA or LOG_RECORD.&n; *    write &quot;clear &lt;cpunum&gt;&quot; -&gt; NO_DATA or LOG_RECORD.&n; *    write &quot;oemdata &lt;cpunum&gt; &lt;offset&gt; -&gt; format the oem data, goto OEMDATA.&n; *    read data -&gt; return the formatted oemdata.&n; *    close -&gt; unchanged.  Keep record areas.&n; *&n; * Closing the data file does not change the state.  This allows shell scripts&n; * to manipulate salinfo data, each shell redirection opens the file, does one&n; * action then closes it again.  The record areas are only freed at close when&n; * the state is NO_DATA.&n; */
DECL|enum|salinfo_state
r_enum
id|salinfo_state
(brace
DECL|enumerator|STATE_NO_DATA
id|STATE_NO_DATA
comma
DECL|enumerator|STATE_LOG_RECORD
id|STATE_LOG_RECORD
comma
DECL|enumerator|STATE_OEMDATA
id|STATE_OEMDATA
comma
)brace
suffix:semicolon
DECL|struct|salinfo_data
r_struct
id|salinfo_data
(brace
DECL|member|cpu_event
r_volatile
id|cpumask_t
id|cpu_event
suffix:semicolon
multiline_comment|/* which cpus have outstanding events */
DECL|member|sem
r_struct
id|semaphore
id|sem
suffix:semicolon
multiline_comment|/* count of cpus with outstanding events (bits set in cpu_event) */
DECL|member|log_buffer
id|u8
op_star
id|log_buffer
suffix:semicolon
DECL|member|log_size
id|u64
id|log_size
suffix:semicolon
DECL|member|oemdata
id|u8
op_star
id|oemdata
suffix:semicolon
multiline_comment|/* decoded oem data */
DECL|member|oemdata_size
id|u64
id|oemdata_size
suffix:semicolon
DECL|member|open
r_int
id|open
suffix:semicolon
multiline_comment|/* single-open to prevent races */
DECL|member|type
id|u8
id|type
suffix:semicolon
DECL|member|saved_num
id|u8
id|saved_num
suffix:semicolon
multiline_comment|/* using a saved record? */
DECL|member|state
r_enum
id|salinfo_state
id|state
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* processing state */
DECL|member|padding
id|u8
id|padding
suffix:semicolon
DECL|member|cpu_check
r_int
id|cpu_check
suffix:semicolon
multiline_comment|/* next CPU to check */
DECL|member|data_saved
r_struct
id|salinfo_data_saved
id|data_saved
(braket
l_int|5
)braket
suffix:semicolon
multiline_comment|/* save last 5 records from mca.c, must be &lt; 255 */
)brace
suffix:semicolon
DECL|variable|salinfo_data
r_static
r_struct
id|salinfo_data
id|salinfo_data
(braket
id|ARRAY_SIZE
c_func
(paren
id|salinfo_log_name
)paren
)braket
suffix:semicolon
DECL|variable|data_lock
DECL|variable|data_saved_lock
r_static
id|spinlock_t
id|data_lock
comma
id|data_saved_lock
suffix:semicolon
multiline_comment|/** salinfo_platform_oemdata - optional callback to decode oemdata from an error&n; * record.&n; * @sect_header: pointer to the start of the section to decode.&n; * @oemdata: returns vmalloc area containing the decded output.&n; * @oemdata_size: returns length of decoded output (strlen).&n; *&n; * Description: If user space asks for oem data to be decoded by the kernel&n; * and/or prom and the platform has set salinfo_platform_oemdata to the address&n; * of a platform specific routine then call that routine.  salinfo_platform_oemdata&n; * vmalloc&squot;s and formats its output area, returning the address of the text&n; * and its strlen.  Returns 0 for success, -ve for error.  The callback is&n; * invoked on the cpu that generated the error record.&n; */
DECL|variable|salinfo_platform_oemdata
r_int
(paren
op_star
id|salinfo_platform_oemdata
)paren
(paren
r_const
id|u8
op_star
id|sect_header
comma
id|u8
op_star
op_star
id|oemdata
comma
id|u64
op_star
id|oemdata_size
)paren
suffix:semicolon
DECL|struct|salinfo_platform_oemdata_parms
r_struct
id|salinfo_platform_oemdata_parms
(brace
DECL|member|efi_guid
r_const
id|u8
op_star
id|efi_guid
suffix:semicolon
DECL|member|oemdata
id|u8
op_star
op_star
id|oemdata
suffix:semicolon
DECL|member|oemdata_size
id|u64
op_star
id|oemdata_size
suffix:semicolon
DECL|member|ret
r_int
id|ret
suffix:semicolon
)brace
suffix:semicolon
r_static
r_void
DECL|function|salinfo_platform_oemdata_cpu
id|salinfo_platform_oemdata_cpu
c_func
(paren
r_void
op_star
id|context
)paren
(brace
r_struct
id|salinfo_platform_oemdata_parms
op_star
id|parms
op_assign
id|context
suffix:semicolon
id|parms-&gt;ret
op_assign
id|salinfo_platform_oemdata
c_func
(paren
id|parms-&gt;efi_guid
comma
id|parms-&gt;oemdata
comma
id|parms-&gt;oemdata_size
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|shift1_data_saved
id|shift1_data_saved
(paren
r_struct
id|salinfo_data
op_star
id|data
comma
r_int
id|shift
)paren
(brace
id|memcpy
c_func
(paren
id|data-&gt;data_saved
op_plus
id|shift
comma
id|data-&gt;data_saved
op_plus
id|shift
op_plus
l_int|1
comma
(paren
id|ARRAY_SIZE
c_func
(paren
id|data-&gt;data_saved
)paren
op_minus
(paren
id|shift
op_plus
l_int|1
)paren
)paren
op_star
r_sizeof
(paren
id|data-&gt;data_saved
(braket
l_int|0
)braket
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
id|data-&gt;data_saved
op_plus
id|ARRAY_SIZE
c_func
(paren
id|data-&gt;data_saved
)paren
op_minus
l_int|1
comma
l_int|0
comma
r_sizeof
(paren
id|data-&gt;data_saved
(braket
l_int|0
)braket
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* This routine is invoked in interrupt context.  Note: mca.c enables&n; * interrupts before calling this code for CMC/CPE.  MCA and INIT events are&n; * not irq safe, do not call any routines that use spinlocks, they may deadlock.&n; * MCA and INIT records are recorded, a timer event will look for any&n; * outstanding events and wake up the user space code.&n; *&n; * The buffer passed from mca.c points to the output from ia64_log_get. This is&n; * a persistent buffer but its contents can change between the interrupt and&n; * when user space processes the record.  Save the record id to identify&n; * changes.&n; */
r_void
DECL|function|salinfo_log_wakeup
id|salinfo_log_wakeup
c_func
(paren
r_int
id|type
comma
id|u8
op_star
id|buffer
comma
id|u64
id|size
comma
r_int
id|irqsafe
)paren
(brace
r_struct
id|salinfo_data
op_star
id|data
op_assign
id|salinfo_data
op_plus
id|type
suffix:semicolon
r_struct
id|salinfo_data_saved
op_star
id|data_saved
suffix:semicolon
r_int
r_int
id|flags
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|saved_size
op_assign
id|ARRAY_SIZE
c_func
(paren
id|data-&gt;data_saved
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|type
op_ge
id|ARRAY_SIZE
c_func
(paren
id|salinfo_log_name
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irqsafe
)paren
id|spin_lock_irqsave
c_func
(paren
op_amp
id|data_saved_lock
comma
id|flags
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|data_saved
op_assign
id|data-&gt;data_saved
suffix:semicolon
id|i
OL
id|saved_size
suffix:semicolon
op_increment
id|i
comma
op_increment
id|data_saved
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|data_saved-&gt;buffer
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_eq
id|saved_size
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|data-&gt;saved_num
)paren
(brace
id|shift1_data_saved
c_func
(paren
id|data
comma
l_int|0
)paren
suffix:semicolon
id|data_saved
op_assign
id|data-&gt;data_saved
op_plus
id|saved_size
op_minus
l_int|1
suffix:semicolon
)brace
r_else
id|data_saved
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|data_saved
)paren
(brace
id|data_saved-&gt;cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|data_saved-&gt;id
op_assign
(paren
(paren
id|sal_log_record_header_t
op_star
)paren
id|buffer
)paren
op_member_access_from_pointer
id|id
suffix:semicolon
id|data_saved-&gt;size
op_assign
id|size
suffix:semicolon
id|data_saved-&gt;buffer
op_assign
id|buffer
suffix:semicolon
)brace
r_if
c_cond
(paren
id|irqsafe
)paren
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|data_saved_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_and_set_bit
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
op_amp
id|data-&gt;cpu_event
)paren
)paren
(brace
r_if
c_cond
(paren
id|irqsafe
)paren
id|up
c_func
(paren
op_amp
id|data-&gt;sem
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Check for outstanding MCA/INIT records every 5 minutes (arbitrary) */
DECL|macro|SALINFO_TIMER_DELAY
mdefine_line|#define SALINFO_TIMER_DELAY (5*60*HZ)
DECL|variable|salinfo_timer
r_static
r_struct
id|timer_list
id|salinfo_timer
suffix:semicolon
r_static
r_void
DECL|function|salinfo_timeout_check
id|salinfo_timeout_check
c_func
(paren
r_struct
id|salinfo_data
op_star
id|data
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|data-&gt;open
)paren
r_return
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
id|NR_CPUS
suffix:semicolon
op_increment
id|i
)paren
(brace
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|i
comma
op_amp
id|data-&gt;cpu_event
)paren
)paren
(brace
multiline_comment|/* double up() is not a problem, user space will see no&n;&t;&t;&t; * records for the additional &quot;events&quot;.&n;&t;&t;&t; */
id|up
c_func
(paren
op_amp
id|data-&gt;sem
)paren
suffix:semicolon
)brace
)brace
)brace
r_static
r_void
DECL|function|salinfo_timeout
id|salinfo_timeout
(paren
r_int
r_int
id|arg
)paren
(brace
id|salinfo_timeout_check
c_func
(paren
id|salinfo_data
op_plus
id|SAL_INFO_TYPE_MCA
)paren
suffix:semicolon
id|salinfo_timeout_check
c_func
(paren
id|salinfo_data
op_plus
id|SAL_INFO_TYPE_INIT
)paren
suffix:semicolon
id|salinfo_timer.expires
op_assign
id|jiffies
op_plus
id|SALINFO_TIMER_DELAY
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|salinfo_timer
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|salinfo_event_open
id|salinfo_event_open
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
op_minus
id|EPERM
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|salinfo_event_read
id|salinfo_event_read
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
id|__user
op_star
id|buffer
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|file-&gt;f_dentry-&gt;d_inode
suffix:semicolon
r_struct
id|proc_dir_entry
op_star
id|entry
op_assign
id|PDE
c_func
(paren
id|inode
)paren
suffix:semicolon
r_struct
id|salinfo_data
op_star
id|data
op_assign
id|entry-&gt;data
suffix:semicolon
r_char
id|cmd
(braket
l_int|32
)braket
suffix:semicolon
r_int
id|size
suffix:semicolon
r_int
id|i
comma
id|n
comma
id|cpu
op_assign
op_minus
l_int|1
suffix:semicolon
id|retry
suffix:colon
r_if
c_cond
(paren
id|down_trylock
c_func
(paren
op_amp
id|data-&gt;sem
)paren
)paren
(brace
r_if
c_cond
(paren
id|file-&gt;f_flags
op_amp
id|O_NONBLOCK
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
r_if
c_cond
(paren
id|down_interruptible
c_func
(paren
op_amp
id|data-&gt;sem
)paren
)paren
r_return
op_minus
id|ERESTARTSYS
suffix:semicolon
)brace
id|n
op_assign
id|data-&gt;cpu_check
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
id|NR_CPUS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|n
comma
op_amp
id|data-&gt;cpu_event
)paren
)paren
(brace
id|cpu
op_assign
id|n
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_increment
id|n
op_eq
id|NR_CPUS
)paren
id|n
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cpu
op_eq
op_minus
l_int|1
)paren
r_goto
id|retry
suffix:semicolon
multiline_comment|/* events are sticky until the user says &quot;clear&quot; */
id|up
c_func
(paren
op_amp
id|data-&gt;sem
)paren
suffix:semicolon
multiline_comment|/* for next read, start checking at next CPU */
id|data-&gt;cpu_check
op_assign
id|cpu
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|data-&gt;cpu_check
op_eq
id|NR_CPUS
)paren
id|data-&gt;cpu_check
op_assign
l_int|0
suffix:semicolon
id|snprintf
c_func
(paren
id|cmd
comma
r_sizeof
(paren
id|cmd
)paren
comma
l_string|&quot;read %d&bslash;n&quot;
comma
id|cpu
)paren
suffix:semicolon
id|size
op_assign
id|strlen
c_func
(paren
id|cmd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|size
OG
id|count
)paren
id|size
op_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buffer
comma
id|cmd
comma
id|size
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
id|size
suffix:semicolon
)brace
DECL|variable|salinfo_event_fops
r_static
r_struct
id|file_operations
id|salinfo_event_fops
op_assign
(brace
dot
id|open
op_assign
id|salinfo_event_open
comma
dot
id|read
op_assign
id|salinfo_event_read
comma
)brace
suffix:semicolon
r_static
r_int
DECL|function|salinfo_log_open
id|salinfo_log_open
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
r_struct
id|proc_dir_entry
op_star
id|entry
op_assign
id|PDE
c_func
(paren
id|inode
)paren
suffix:semicolon
r_struct
id|salinfo_data
op_star
id|data
op_assign
id|entry-&gt;data
suffix:semicolon
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
op_minus
id|EPERM
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|data_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|data-&gt;open
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|data_lock
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|data-&gt;open
op_assign
l_int|1
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|data_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|data-&gt;state
op_eq
id|STATE_NO_DATA
op_logical_and
op_logical_neg
(paren
id|data-&gt;log_buffer
op_assign
id|vmalloc
c_func
(paren
id|ia64_sal_get_state_info_size
c_func
(paren
id|data-&gt;type
)paren
)paren
)paren
)paren
(brace
id|data-&gt;open
op_assign
l_int|0
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|salinfo_log_release
id|salinfo_log_release
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
r_struct
id|proc_dir_entry
op_star
id|entry
op_assign
id|PDE
c_func
(paren
id|inode
)paren
suffix:semicolon
r_struct
id|salinfo_data
op_star
id|data
op_assign
id|entry-&gt;data
suffix:semicolon
r_if
c_cond
(paren
id|data-&gt;state
op_eq
id|STATE_NO_DATA
)paren
(brace
id|vfree
c_func
(paren
id|data-&gt;log_buffer
)paren
suffix:semicolon
id|vfree
c_func
(paren
id|data-&gt;oemdata
)paren
suffix:semicolon
id|data-&gt;log_buffer
op_assign
l_int|NULL
suffix:semicolon
id|data-&gt;oemdata
op_assign
l_int|NULL
suffix:semicolon
)brace
id|spin_lock
c_func
(paren
op_amp
id|data_lock
)paren
suffix:semicolon
id|data-&gt;open
op_assign
l_int|0
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|data_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
DECL|function|call_on_cpu
id|call_on_cpu
c_func
(paren
r_int
id|cpu
comma
r_void
(paren
op_star
id|fn
)paren
(paren
r_void
op_star
)paren
comma
r_void
op_star
id|arg
)paren
(brace
id|cpumask_t
id|save_cpus_allowed
comma
id|new_cpus_allowed
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|save_cpus_allowed
comma
op_amp
id|current-&gt;cpus_allowed
comma
r_sizeof
(paren
id|save_cpus_allowed
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|new_cpus_allowed
comma
l_int|0
comma
r_sizeof
(paren
id|new_cpus_allowed
)paren
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|cpu
comma
op_amp
id|new_cpus_allowed
)paren
suffix:semicolon
id|set_cpus_allowed
c_func
(paren
id|current
comma
id|new_cpus_allowed
)paren
suffix:semicolon
(paren
op_star
id|fn
)paren
(paren
id|arg
)paren
suffix:semicolon
id|set_cpus_allowed
c_func
(paren
id|current
comma
id|save_cpus_allowed
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|salinfo_log_read_cpu
id|salinfo_log_read_cpu
c_func
(paren
r_void
op_star
id|context
)paren
(brace
r_struct
id|salinfo_data
op_star
id|data
op_assign
id|context
suffix:semicolon
id|sal_log_record_header_t
op_star
id|rh
suffix:semicolon
id|data-&gt;log_size
op_assign
id|ia64_sal_get_state_info
c_func
(paren
id|data-&gt;type
comma
(paren
id|u64
op_star
)paren
id|data-&gt;log_buffer
)paren
suffix:semicolon
id|rh
op_assign
(paren
id|sal_log_record_header_t
op_star
)paren
(paren
id|data-&gt;log_buffer
)paren
suffix:semicolon
multiline_comment|/* Clear corrected errors as they are read from SAL */
r_if
c_cond
(paren
id|rh-&gt;severity
op_eq
id|sal_log_severity_corrected
)paren
id|ia64_sal_clear_state_info
c_func
(paren
id|data-&gt;type
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|salinfo_log_new_read
id|salinfo_log_new_read
c_func
(paren
r_int
id|cpu
comma
r_struct
id|salinfo_data
op_star
id|data
)paren
(brace
r_struct
id|salinfo_data_saved
op_star
id|data_saved
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|saved_size
op_assign
id|ARRAY_SIZE
c_func
(paren
id|data-&gt;data_saved
)paren
suffix:semicolon
id|data-&gt;saved_num
op_assign
l_int|0
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|data_saved_lock
comma
id|flags
)paren
suffix:semicolon
id|retry
suffix:colon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|data_saved
op_assign
id|data-&gt;data_saved
suffix:semicolon
id|i
OL
id|saved_size
suffix:semicolon
op_increment
id|i
comma
op_increment
id|data_saved
)paren
(brace
r_if
c_cond
(paren
id|data_saved-&gt;buffer
op_logical_and
id|data_saved-&gt;cpu
op_eq
id|cpu
)paren
(brace
id|sal_log_record_header_t
op_star
id|rh
op_assign
(paren
id|sal_log_record_header_t
op_star
)paren
(paren
id|data_saved-&gt;buffer
)paren
suffix:semicolon
id|data-&gt;log_size
op_assign
id|data_saved-&gt;size
suffix:semicolon
id|memcpy
c_func
(paren
id|data-&gt;log_buffer
comma
id|rh
comma
id|data-&gt;log_size
)paren
suffix:semicolon
id|barrier
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* id check must not be moved */
r_if
c_cond
(paren
id|rh-&gt;id
op_eq
id|data_saved-&gt;id
)paren
(brace
id|data-&gt;saved_num
op_assign
id|i
op_plus
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* saved record changed by mca.c since interrupt, discard it */
id|shift1_data_saved
c_func
(paren
id|data
comma
id|i
)paren
suffix:semicolon
r_goto
id|retry
suffix:semicolon
)brace
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|data_saved_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|data-&gt;saved_num
)paren
id|call_on_cpu
c_func
(paren
id|cpu
comma
id|salinfo_log_read_cpu
comma
id|data
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|data-&gt;log_size
)paren
(brace
id|data-&gt;state
op_assign
id|STATE_NO_DATA
suffix:semicolon
id|clear_bit
c_func
(paren
id|cpu
comma
op_amp
id|data-&gt;cpu_event
)paren
suffix:semicolon
)brace
r_else
(brace
id|data-&gt;state
op_assign
id|STATE_LOG_RECORD
suffix:semicolon
)brace
)brace
r_static
id|ssize_t
DECL|function|salinfo_log_read
id|salinfo_log_read
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
id|__user
op_star
id|buffer
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|file-&gt;f_dentry-&gt;d_inode
suffix:semicolon
r_struct
id|proc_dir_entry
op_star
id|entry
op_assign
id|PDE
c_func
(paren
id|inode
)paren
suffix:semicolon
r_struct
id|salinfo_data
op_star
id|data
op_assign
id|entry-&gt;data
suffix:semicolon
id|u8
op_star
id|buf
suffix:semicolon
id|u64
id|bufsize
suffix:semicolon
r_if
c_cond
(paren
id|data-&gt;state
op_eq
id|STATE_LOG_RECORD
)paren
(brace
id|buf
op_assign
id|data-&gt;log_buffer
suffix:semicolon
id|bufsize
op_assign
id|data-&gt;log_size
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|data-&gt;state
op_eq
id|STATE_OEMDATA
)paren
(brace
id|buf
op_assign
id|data-&gt;oemdata
suffix:semicolon
id|bufsize
op_assign
id|data-&gt;oemdata_size
suffix:semicolon
)brace
r_else
(brace
id|buf
op_assign
l_int|NULL
suffix:semicolon
id|bufsize
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|simple_read_from_buffer
c_func
(paren
id|buffer
comma
id|count
comma
id|ppos
comma
id|buf
comma
id|bufsize
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|salinfo_log_clear_cpu
id|salinfo_log_clear_cpu
c_func
(paren
r_void
op_star
id|context
)paren
(brace
r_struct
id|salinfo_data
op_star
id|data
op_assign
id|context
suffix:semicolon
id|ia64_sal_clear_state_info
c_func
(paren
id|data-&gt;type
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|salinfo_log_clear
id|salinfo_log_clear
c_func
(paren
r_struct
id|salinfo_data
op_star
id|data
comma
r_int
id|cpu
)paren
(brace
id|sal_log_record_header_t
op_star
id|rh
suffix:semicolon
id|data-&gt;state
op_assign
id|STATE_NO_DATA
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|cpu
comma
op_amp
id|data-&gt;cpu_event
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|down
c_func
(paren
op_amp
id|data-&gt;sem
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|cpu
comma
op_amp
id|data-&gt;cpu_event
)paren
suffix:semicolon
r_if
c_cond
(paren
id|data-&gt;saved_num
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
id|data_saved_lock
comma
id|flags
)paren
suffix:semicolon
id|shift1_data_saved
c_func
(paren
id|data
comma
id|data-&gt;saved_num
op_minus
l_int|1
)paren
suffix:semicolon
id|data-&gt;saved_num
op_assign
l_int|0
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|data_saved_lock
comma
id|flags
)paren
suffix:semicolon
)brace
id|rh
op_assign
(paren
id|sal_log_record_header_t
op_star
)paren
(paren
id|data-&gt;log_buffer
)paren
suffix:semicolon
multiline_comment|/* Corrected errors have already been cleared from SAL */
r_if
c_cond
(paren
id|rh-&gt;severity
op_ne
id|sal_log_severity_corrected
)paren
id|call_on_cpu
c_func
(paren
id|cpu
comma
id|salinfo_log_clear_cpu
comma
id|data
)paren
suffix:semicolon
multiline_comment|/* clearing a record may make a new record visible */
id|salinfo_log_new_read
c_func
(paren
id|cpu
comma
id|data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|data-&gt;state
op_eq
id|STATE_LOG_RECORD
op_logical_and
op_logical_neg
id|test_and_set_bit
c_func
(paren
id|cpu
comma
op_amp
id|data-&gt;cpu_event
)paren
)paren
id|up
c_func
(paren
op_amp
id|data-&gt;sem
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|salinfo_log_write
id|salinfo_log_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
id|__user
op_star
id|buffer
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|file-&gt;f_dentry-&gt;d_inode
suffix:semicolon
r_struct
id|proc_dir_entry
op_star
id|entry
op_assign
id|PDE
c_func
(paren
id|inode
)paren
suffix:semicolon
r_struct
id|salinfo_data
op_star
id|data
op_assign
id|entry-&gt;data
suffix:semicolon
r_char
id|cmd
(braket
l_int|32
)braket
suffix:semicolon
r_int
id|size
suffix:semicolon
id|u32
id|offset
suffix:semicolon
r_int
id|cpu
suffix:semicolon
id|size
op_assign
r_sizeof
(paren
id|cmd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
OL
id|size
)paren
id|size
op_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|cmd
comma
id|buffer
comma
id|size
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|sscanf
c_func
(paren
id|cmd
comma
l_string|&quot;read %d&quot;
comma
op_amp
id|cpu
)paren
op_eq
l_int|1
)paren
(brace
id|salinfo_log_new_read
c_func
(paren
id|cpu
comma
id|data
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|sscanf
c_func
(paren
id|cmd
comma
l_string|&quot;clear %d&quot;
comma
op_amp
id|cpu
)paren
op_eq
l_int|1
)paren
(brace
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|salinfo_log_clear
c_func
(paren
id|data
comma
id|cpu
)paren
)paren
)paren
id|count
op_assign
id|ret
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|sscanf
c_func
(paren
id|cmd
comma
l_string|&quot;oemdata %d %d&quot;
comma
op_amp
id|cpu
comma
op_amp
id|offset
)paren
op_eq
l_int|2
)paren
(brace
r_if
c_cond
(paren
id|data-&gt;state
op_ne
id|STATE_LOG_RECORD
op_logical_and
id|data-&gt;state
op_ne
id|STATE_OEMDATA
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|offset
OG
id|data-&gt;log_size
op_minus
r_sizeof
(paren
id|efi_guid_t
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|data-&gt;state
op_assign
id|STATE_OEMDATA
suffix:semicolon
r_if
c_cond
(paren
id|salinfo_platform_oemdata
)paren
(brace
r_struct
id|salinfo_platform_oemdata_parms
id|parms
op_assign
(brace
dot
id|efi_guid
op_assign
id|data-&gt;log_buffer
op_plus
id|offset
comma
dot
id|oemdata
op_assign
op_amp
id|data-&gt;oemdata
comma
dot
id|oemdata_size
op_assign
op_amp
id|data-&gt;oemdata_size
)brace
suffix:semicolon
id|call_on_cpu
c_func
(paren
id|cpu
comma
id|salinfo_platform_oemdata_cpu
comma
op_amp
id|parms
)paren
suffix:semicolon
r_if
c_cond
(paren
id|parms.ret
)paren
id|count
op_assign
id|parms.ret
suffix:semicolon
)brace
r_else
id|data-&gt;oemdata_size
op_assign
l_int|0
suffix:semicolon
)brace
r_else
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
DECL|variable|salinfo_data_fops
r_static
r_struct
id|file_operations
id|salinfo_data_fops
op_assign
(brace
dot
id|open
op_assign
id|salinfo_log_open
comma
dot
id|release
op_assign
id|salinfo_log_release
comma
dot
id|read
op_assign
id|salinfo_log_read
comma
dot
id|write
op_assign
id|salinfo_log_write
comma
)brace
suffix:semicolon
r_static
r_int
id|__init
DECL|function|salinfo_init
id|salinfo_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|salinfo_dir
suffix:semicolon
multiline_comment|/* /proc/sal dir entry */
r_struct
id|proc_dir_entry
op_star
op_star
id|sdir
op_assign
id|salinfo_proc_entries
suffix:semicolon
multiline_comment|/* keeps track of every entry */
r_struct
id|proc_dir_entry
op_star
id|dir
comma
op_star
id|entry
suffix:semicolon
r_struct
id|salinfo_data
op_star
id|data
suffix:semicolon
r_int
id|i
comma
id|j
comma
id|online
suffix:semicolon
id|salinfo_dir
op_assign
id|proc_mkdir
c_func
(paren
l_string|&quot;sal&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|salinfo_dir
)paren
r_return
l_int|0
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
id|NR_SALINFO_ENTRIES
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* pass the feature bit in question as misc data */
op_star
id|sdir
op_increment
op_assign
id|create_proc_read_entry
(paren
id|salinfo_entries
(braket
id|i
)braket
dot
id|name
comma
l_int|0
comma
id|salinfo_dir
comma
id|salinfo_read
comma
(paren
r_void
op_star
)paren
id|salinfo_entries
(braket
id|i
)braket
dot
id|feature
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|ARRAY_SIZE
c_func
(paren
id|salinfo_log_name
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|data
op_assign
id|salinfo_data
op_plus
id|i
suffix:semicolon
id|data-&gt;type
op_assign
id|i
suffix:semicolon
id|sema_init
c_func
(paren
op_amp
id|data-&gt;sem
comma
l_int|0
)paren
suffix:semicolon
id|dir
op_assign
id|proc_mkdir
c_func
(paren
id|salinfo_log_name
(braket
id|i
)braket
comma
id|salinfo_dir
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dir
)paren
r_continue
suffix:semicolon
id|entry
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;event&quot;
comma
id|S_IRUSR
comma
id|dir
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|entry
)paren
r_continue
suffix:semicolon
id|entry-&gt;data
op_assign
id|data
suffix:semicolon
id|entry-&gt;proc_fops
op_assign
op_amp
id|salinfo_event_fops
suffix:semicolon
op_star
id|sdir
op_increment
op_assign
id|entry
suffix:semicolon
id|entry
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;data&quot;
comma
id|S_IRUSR
op_or
id|S_IWUSR
comma
id|dir
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|entry
)paren
r_continue
suffix:semicolon
id|entry-&gt;data
op_assign
id|data
suffix:semicolon
id|entry-&gt;proc_fops
op_assign
op_amp
id|salinfo_data_fops
suffix:semicolon
op_star
id|sdir
op_increment
op_assign
id|entry
suffix:semicolon
multiline_comment|/* we missed any events before now */
id|online
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|NR_CPUS
suffix:semicolon
id|j
op_increment
)paren
r_if
c_cond
(paren
id|cpu_online
c_func
(paren
id|j
)paren
)paren
(brace
id|set_bit
c_func
(paren
id|j
comma
op_amp
id|data-&gt;cpu_event
)paren
suffix:semicolon
op_increment
id|online
suffix:semicolon
)brace
id|sema_init
c_func
(paren
op_amp
id|data-&gt;sem
comma
id|online
)paren
suffix:semicolon
op_star
id|sdir
op_increment
op_assign
id|dir
suffix:semicolon
)brace
op_star
id|sdir
op_increment
op_assign
id|salinfo_dir
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|salinfo_timer
)paren
suffix:semicolon
id|salinfo_timer.expires
op_assign
id|jiffies
op_plus
id|SALINFO_TIMER_DELAY
suffix:semicolon
id|salinfo_timer.function
op_assign
op_amp
id|salinfo_timeout
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|salinfo_timer
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * &squot;data&squot; contains an integer that corresponds to the feature we&squot;re&n; * testing&n; */
r_static
r_int
DECL|function|salinfo_read
id|salinfo_read
c_func
(paren
r_char
op_star
id|page
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|off
comma
r_int
id|count
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
id|len
op_assign
l_int|0
suffix:semicolon
id|len
op_assign
id|sprintf
c_func
(paren
id|page
comma
(paren
id|sal_platform_features
op_amp
(paren
r_int
r_int
)paren
id|data
)paren
ques
c_cond
l_string|&quot;1&bslash;n&quot;
suffix:colon
l_string|&quot;0&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_le
id|off
op_plus
id|count
)paren
op_star
id|eof
op_assign
l_int|1
suffix:semicolon
op_star
id|start
op_assign
id|page
op_plus
id|off
suffix:semicolon
id|len
op_sub_assign
id|off
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|count
)paren
id|len
op_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|0
)paren
id|len
op_assign
l_int|0
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|variable|salinfo_init
id|module_init
c_func
(paren
id|salinfo_init
)paren
suffix:semicolon
eof
