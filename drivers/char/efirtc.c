multiline_comment|/*&n; * EFI Time Services Driver for Linux&n; *&n; * Copyright (C) 1999 Hewlett-Packard Co&n; * Copyright (C) 1999 Stephane Eranian &lt;eranian@hpl.hp.com&gt;&n; *&n; * Based on skeleton from the drivers/char/rtc.c driver by P. Gortmaker&n; *&n; * This code provides a architected &amp; portable interface to the real time &n; * clock by using EFI instead of direct bit fiddling. The functionalities are &n; * quite different from the rtc.c driver. The only way to talk to the device &n; * is by using ioctl(). There is a /proc interface which provides the raw &n; * information.&n; *&n; * Please note that we have kept the API as close as possible from the &n; * legacy RTC. The standard /sbin/hwclock program should work normally &n; * when used to get/set the time.&n; *&n; * NOTES:&n; *&t;- Locking is required for safe execution of EFI calls with regards&n; *&t;  to interrrupts and SMP.&n; *&n; * TODO (December 1999):&n; * &t;- provide the API to set/get the WakeUp Alarm (different from the&n; *&t;  rtc.c alarm).&n; *&t;- SMP testing&n; * &t;- Add module support&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/rtc.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;asm/efi.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
DECL|macro|EFI_RTC_VERSION
mdefine_line|#define EFI_RTC_VERSION&t;&t;&quot;0.2&quot;
DECL|macro|EFI_ISDST
mdefine_line|#define EFI_ISDST (EFI_TIME_ADJUST_DAYLIGHT|EFI_TIME_IN_DAYLIGHT)
multiline_comment|/*&n; * EFI Epoch is 1/1/1998&n; */
DECL|macro|EFI_RTC_EPOCH
mdefine_line|#define EFI_RTC_EPOCH&t;&t;1998
DECL|variable|efi_rtc_lock
r_static
id|spinlock_t
id|efi_rtc_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
r_static
r_int
id|efi_rtc_ioctl
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
DECL|macro|is_leap
mdefine_line|#define is_leap(year) &bslash;&n;          ((year) % 4 == 0 &amp;&amp; ((year) % 100 != 0 || (year) % 400 == 0))
DECL|variable|__mon_yday
r_static
r_const
r_int
r_int
r_int
id|__mon_yday
(braket
l_int|2
)braket
(braket
l_int|13
)braket
op_assign
(brace
multiline_comment|/* Normal years.  */
(brace
l_int|0
comma
l_int|31
comma
l_int|59
comma
l_int|90
comma
l_int|120
comma
l_int|151
comma
l_int|181
comma
l_int|212
comma
l_int|243
comma
l_int|273
comma
l_int|304
comma
l_int|334
comma
l_int|365
)brace
comma
multiline_comment|/* Leap years.  */
(brace
l_int|0
comma
l_int|31
comma
l_int|60
comma
l_int|91
comma
l_int|121
comma
l_int|152
comma
l_int|182
comma
l_int|213
comma
l_int|244
comma
l_int|274
comma
l_int|305
comma
l_int|335
comma
l_int|366
)brace
)brace
suffix:semicolon
multiline_comment|/*&n; * returns day of the year [0-365]&n; */
r_static
r_inline
r_int
DECL|function|compute_yday
id|compute_yday
c_func
(paren
id|efi_time_t
op_star
id|eft
)paren
(brace
multiline_comment|/* efi_time_t.month is in the [1-12] so, we need -1 */
r_return
id|__mon_yday
(braket
id|is_leap
c_func
(paren
id|eft-&gt;year
)paren
)braket
(braket
id|eft-&gt;month
op_minus
l_int|1
)braket
op_plus
id|eft-&gt;day
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * returns day of the week [0-6] 0=Sunday&n; *&n; * Don&squot;t try to provide a year that&squot;s before 1998, please !&n; */
r_static
r_int
DECL|function|compute_wday
id|compute_wday
c_func
(paren
id|efi_time_t
op_star
id|eft
)paren
(brace
r_int
id|y
suffix:semicolon
r_int
id|ndays
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|eft-&gt;year
OL
l_int|1998
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;efirtc: EFI year &lt; 1998, invalid date&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_for
c_loop
(paren
id|y
op_assign
id|EFI_RTC_EPOCH
suffix:semicolon
id|y
OL
id|eft-&gt;year
suffix:semicolon
id|y
op_increment
)paren
(brace
id|ndays
op_add_assign
l_int|365
op_plus
(paren
id|is_leap
c_func
(paren
id|y
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
)paren
suffix:semicolon
)brace
id|ndays
op_add_assign
id|compute_yday
c_func
(paren
id|eft
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * 4=1/1/1998 was a Thursday&n;&t; */
r_return
(paren
id|ndays
op_plus
l_int|4
)paren
op_mod
l_int|7
suffix:semicolon
)brace
r_static
r_void
DECL|function|convert_to_efi_time
id|convert_to_efi_time
c_func
(paren
r_struct
id|rtc_time
op_star
id|wtime
comma
id|efi_time_t
op_star
id|eft
)paren
(brace
id|eft-&gt;year
op_assign
id|wtime-&gt;tm_year
op_plus
l_int|1900
suffix:semicolon
id|eft-&gt;month
op_assign
id|wtime-&gt;tm_mon
op_plus
l_int|1
suffix:semicolon
id|eft-&gt;day
op_assign
id|wtime-&gt;tm_mday
suffix:semicolon
id|eft-&gt;hour
op_assign
id|wtime-&gt;tm_hour
suffix:semicolon
id|eft-&gt;minute
op_assign
id|wtime-&gt;tm_min
suffix:semicolon
id|eft-&gt;second
op_assign
id|wtime-&gt;tm_sec
suffix:semicolon
id|eft-&gt;nanosecond
op_assign
l_int|0
suffix:semicolon
id|eft-&gt;daylight
op_assign
id|wtime-&gt;tm_isdst
ques
c_cond
id|EFI_ISDST
suffix:colon
l_int|0
suffix:semicolon
id|eft-&gt;timezone
op_assign
id|EFI_UNSPECIFIED_TIMEZONE
suffix:semicolon
)brace
r_static
r_void
DECL|function|convert_from_efi_time
id|convert_from_efi_time
c_func
(paren
id|efi_time_t
op_star
id|eft
comma
r_struct
id|rtc_time
op_star
id|wtime
)paren
(brace
id|wtime-&gt;tm_sec
op_assign
id|eft-&gt;second
suffix:semicolon
id|wtime-&gt;tm_min
op_assign
id|eft-&gt;minute
suffix:semicolon
id|wtime-&gt;tm_hour
op_assign
id|eft-&gt;hour
suffix:semicolon
id|wtime-&gt;tm_mday
op_assign
id|eft-&gt;day
suffix:semicolon
id|wtime-&gt;tm_mon
op_assign
id|eft-&gt;month
op_minus
l_int|1
suffix:semicolon
id|wtime-&gt;tm_year
op_assign
id|eft-&gt;year
op_minus
l_int|1900
suffix:semicolon
multiline_comment|/* day of the week [0-6], Sunday=0 */
id|wtime-&gt;tm_wday
op_assign
id|compute_wday
c_func
(paren
id|eft
)paren
suffix:semicolon
multiline_comment|/* day in the year [1-365]*/
id|wtime-&gt;tm_yday
op_assign
id|compute_yday
c_func
(paren
id|eft
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|eft-&gt;daylight
op_amp
id|EFI_ISDST
)paren
(brace
r_case
id|EFI_ISDST
suffix:colon
id|wtime-&gt;tm_isdst
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|EFI_TIME_ADJUST_DAYLIGHT
suffix:colon
id|wtime-&gt;tm_isdst
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|wtime-&gt;tm_isdst
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
)brace
r_static
r_int
DECL|function|efi_rtc_ioctl
id|efi_rtc_ioctl
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
id|efi_status_t
id|status
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|efi_time_t
id|eft
suffix:semicolon
id|efi_time_cap_t
id|cap
suffix:semicolon
r_struct
id|rtc_time
id|wtime
suffix:semicolon
r_struct
id|rtc_wkalrm
op_star
id|ewp
suffix:semicolon
r_int
r_char
id|enabled
comma
id|pending
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|RTC_UIE_ON
suffix:colon
r_case
id|RTC_UIE_OFF
suffix:colon
r_case
id|RTC_PIE_ON
suffix:colon
r_case
id|RTC_PIE_OFF
suffix:colon
r_case
id|RTC_AIE_ON
suffix:colon
r_case
id|RTC_AIE_OFF
suffix:colon
r_case
id|RTC_ALM_SET
suffix:colon
r_case
id|RTC_ALM_READ
suffix:colon
r_case
id|RTC_IRQP_READ
suffix:colon
r_case
id|RTC_IRQP_SET
suffix:colon
r_case
id|RTC_EPOCH_READ
suffix:colon
r_case
id|RTC_EPOCH_SET
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
r_case
id|RTC_RD_TIME
suffix:colon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|efi_rtc_lock
comma
id|flags
)paren
suffix:semicolon
id|status
op_assign
id|efi
dot
id|get_time
c_func
(paren
op_amp
id|eft
comma
op_amp
id|cap
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|efi_rtc_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_ne
id|EFI_SUCCESS
)paren
(brace
multiline_comment|/* should never happen */
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;efitime: can&squot;t read time&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|convert_from_efi_time
c_func
(paren
op_amp
id|eft
comma
op_amp
id|wtime
)paren
suffix:semicolon
r_return
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
id|wtime
comma
r_sizeof
(paren
r_struct
id|rtc_time
)paren
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
r_case
id|RTC_SET_TIME
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_TIME
)paren
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|wtime
comma
(paren
r_struct
id|rtc_time
op_star
)paren
id|arg
comma
r_sizeof
(paren
r_struct
id|rtc_time
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|convert_to_efi_time
c_func
(paren
op_amp
id|wtime
comma
op_amp
id|eft
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|efi_rtc_lock
comma
id|flags
)paren
suffix:semicolon
id|status
op_assign
id|efi
dot
id|set_time
c_func
(paren
op_amp
id|eft
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|efi_rtc_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|status
op_eq
id|EFI_SUCCESS
ques
c_cond
l_int|0
suffix:colon
op_minus
id|EINVAL
suffix:semicolon
r_case
id|RTC_WKALM_SET
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_TIME
)paren
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
id|ewp
op_assign
(paren
r_struct
id|rtc_wkalrm
op_star
)paren
id|arg
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|enabled
comma
op_amp
id|ewp-&gt;enabled
)paren
op_logical_or
id|copy_from_user
c_func
(paren
op_amp
id|wtime
comma
op_amp
id|ewp-&gt;time
comma
r_sizeof
(paren
r_struct
id|rtc_time
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|convert_to_efi_time
c_func
(paren
op_amp
id|wtime
comma
op_amp
id|eft
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|efi_rtc_lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * XXX Fixme:&n;&t;&t;&t; * As of EFI 0.92 with the firmware I have on my&n;&t;&t;&t; * machine this call does not seem to work quite &n;&t;&t;&t; * right&n;&t;&t;&t; */
id|status
op_assign
id|efi
dot
id|set_wakeup_time
c_func
(paren
(paren
id|efi_bool_t
)paren
id|enabled
comma
op_amp
id|eft
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|efi_rtc_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|status
op_eq
id|EFI_SUCCESS
ques
c_cond
l_int|0
suffix:colon
op_minus
id|EINVAL
suffix:semicolon
r_case
id|RTC_WKALM_RD
suffix:colon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|efi_rtc_lock
comma
id|flags
)paren
suffix:semicolon
id|status
op_assign
id|efi
dot
id|get_wakeup_time
c_func
(paren
(paren
id|efi_bool_t
op_star
)paren
op_amp
id|enabled
comma
(paren
id|efi_bool_t
op_star
)paren
op_amp
id|pending
comma
op_amp
id|eft
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|efi_rtc_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_ne
id|EFI_SUCCESS
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|ewp
op_assign
(paren
r_struct
id|rtc_wkalrm
op_star
)paren
id|arg
suffix:semicolon
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|enabled
comma
op_amp
id|ewp-&gt;enabled
)paren
op_logical_or
id|put_user
c_func
(paren
id|pending
comma
op_amp
id|ewp-&gt;pending
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|convert_from_efi_time
c_func
(paren
op_amp
id|eft
comma
op_amp
id|wtime
)paren
suffix:semicolon
r_return
id|copy_to_user
c_func
(paren
(paren
r_void
op_star
)paren
op_amp
id|ewp-&gt;time
comma
op_amp
id|wtime
comma
r_sizeof
(paren
r_struct
id|rtc_time
)paren
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;We enforce only one user at a time here with the open/close.&n; *&t;Also clear the previous interrupt data on an open, and clean&n; *&t;up things on a close.&n; */
r_static
r_int
DECL|function|efi_rtc_open
id|efi_rtc_open
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
multiline_comment|/*&n;&t; * nothing special to do here&n;&t; * We do accept multiple open files at the same time as we&n;&t; * synchronize on the per call operation.&n;&t; */
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|efi_rtc_close
id|efi_rtc_close
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
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;The various file operations we support.&n; */
DECL|variable|efi_rtc_fops
r_static
r_struct
id|file_operations
id|efi_rtc_fops
op_assign
(brace
id|owner
suffix:colon
id|THIS_MODULE
comma
id|ioctl
suffix:colon
id|efi_rtc_ioctl
comma
id|open
suffix:colon
id|efi_rtc_open
comma
id|release
suffix:colon
id|efi_rtc_close
comma
)brace
suffix:semicolon
DECL|variable|efi_rtc_dev
r_static
r_struct
id|miscdevice
id|efi_rtc_dev
op_assign
(brace
id|EFI_RTC_MINOR
comma
l_string|&quot;efirtc&quot;
comma
op_amp
id|efi_rtc_fops
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;We export RAW EFI information to /proc/efirtc&n; */
r_static
r_int
DECL|function|efi_rtc_get_status
id|efi_rtc_get_status
c_func
(paren
r_char
op_star
id|buf
)paren
(brace
id|efi_time_t
id|eft
comma
id|alm
suffix:semicolon
id|efi_time_cap_t
id|cap
suffix:semicolon
r_char
op_star
id|p
op_assign
id|buf
suffix:semicolon
id|efi_bool_t
id|enabled
comma
id|pending
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|efi_rtc_lock
comma
id|flags
)paren
suffix:semicolon
id|efi
dot
id|get_time
c_func
(paren
op_amp
id|eft
comma
op_amp
id|cap
)paren
suffix:semicolon
id|efi
dot
id|get_wakeup_time
c_func
(paren
op_amp
id|enabled
comma
op_amp
id|pending
comma
op_amp
id|alm
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|efi_rtc_lock
comma
id|flags
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;Time      :&bslash;n&quot;
l_string|&quot;Year      : %u&bslash;n&quot;
l_string|&quot;Month     : %u&bslash;n&quot;
l_string|&quot;Day       : %u&bslash;n&quot;
l_string|&quot;Hour      : %u&bslash;n&quot;
l_string|&quot;Minute    : %u&bslash;n&quot;
l_string|&quot;Second    : %u&bslash;n&quot;
l_string|&quot;Nanosecond: %u&bslash;n&quot;
l_string|&quot;Daylight  : %u&bslash;n&quot;
comma
id|eft.year
comma
id|eft.month
comma
id|eft.day
comma
id|eft.hour
comma
id|eft.minute
comma
id|eft.second
comma
id|eft.nanosecond
comma
id|eft.daylight
)paren
suffix:semicolon
r_if
c_cond
(paren
id|eft.timezone
op_eq
id|EFI_UNSPECIFIED_TIMEZONE
)paren
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;Timezone  : unspecified&bslash;n&quot;
)paren
suffix:semicolon
r_else
multiline_comment|/* XXX fixme: convert to string? */
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;Timezone  : %u&bslash;n&quot;
comma
id|eft.timezone
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;&bslash;nWakeup Alm:&bslash;n&quot;
l_string|&quot;Enabled   : %s&bslash;n&quot;
l_string|&quot;Pending   : %s&bslash;n&quot;
l_string|&quot;Year      : %u&bslash;n&quot;
l_string|&quot;Month     : %u&bslash;n&quot;
l_string|&quot;Day       : %u&bslash;n&quot;
l_string|&quot;Hour      : %u&bslash;n&quot;
l_string|&quot;Minute    : %u&bslash;n&quot;
l_string|&quot;Second    : %u&bslash;n&quot;
l_string|&quot;Nanosecond: %u&bslash;n&quot;
l_string|&quot;Daylight  : %u&bslash;n&quot;
comma
id|enabled
op_eq
l_int|1
ques
c_cond
l_string|&quot;Yes&quot;
suffix:colon
l_string|&quot;No&quot;
comma
id|pending
op_eq
l_int|1
ques
c_cond
l_string|&quot;Yes&quot;
suffix:colon
l_string|&quot;No&quot;
comma
id|alm.year
comma
id|alm.month
comma
id|alm.day
comma
id|alm.hour
comma
id|alm.minute
comma
id|alm.second
comma
id|alm.nanosecond
comma
id|alm.daylight
)paren
suffix:semicolon
r_if
c_cond
(paren
id|eft.timezone
op_eq
id|EFI_UNSPECIFIED_TIMEZONE
)paren
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;Timezone  : unspecified&bslash;n&quot;
)paren
suffix:semicolon
r_else
multiline_comment|/* XXX fixme: convert to string? */
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;Timezone  : %u&bslash;n&quot;
comma
id|eft.timezone
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * now prints the capabilities&n;&t; */
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;&bslash;nClock Cap :&bslash;n&quot;
l_string|&quot;Resolution: %u&bslash;n&quot;
l_string|&quot;Accuracy  : %u&bslash;n&quot;
l_string|&quot;SetstoZero: %u&bslash;n&quot;
comma
id|cap.resolution
comma
id|cap.accuracy
comma
id|cap.sets_to_zero
)paren
suffix:semicolon
r_return
id|p
op_minus
id|buf
suffix:semicolon
)brace
r_static
r_int
DECL|function|efi_rtc_read_proc
id|efi_rtc_read_proc
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
id|efi_rtc_get_status
c_func
(paren
id|page
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
r_static
r_int
id|__init
DECL|function|efi_rtc_init
id|efi_rtc_init
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;EFI Time Services Driver v%s&bslash;n&quot;
comma
id|EFI_RTC_VERSION
)paren
suffix:semicolon
id|misc_register
c_func
(paren
op_amp
id|efi_rtc_dev
)paren
suffix:semicolon
id|create_proc_read_entry
(paren
l_string|&quot;efirtc&quot;
comma
l_int|0
comma
l_int|NULL
comma
id|efi_rtc_read_proc
comma
l_int|NULL
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
id|__exit
DECL|function|efi_rtc_exit
id|efi_rtc_exit
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* not yet used */
)brace
DECL|variable|efi_rtc_init
id|module_init
c_func
(paren
id|efi_rtc_init
)paren
suffix:semicolon
DECL|variable|efi_rtc_exit
id|module_exit
c_func
(paren
id|efi_rtc_exit
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
