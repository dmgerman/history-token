macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;linux/suspend.h&gt;
macro_line|#include &lt;linux/bcd.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;acpi/acpi_bus.h&gt;
macro_line|#include &lt;acpi/acpi_drivers.h&gt;
macro_line|#ifdef CONFIG_X86
macro_line|#include &lt;linux/mc146818rtc.h&gt;
macro_line|#endif
macro_line|#include &quot;sleep.h&quot;
DECL|macro|ACPI_SYSTEM_FILE_SLEEP
mdefine_line|#define ACPI_SYSTEM_FILE_SLEEP&t;&t;&quot;sleep&quot;
DECL|macro|ACPI_SYSTEM_FILE_ALARM
mdefine_line|#define ACPI_SYSTEM_FILE_ALARM&t;&t;&quot;alarm&quot;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT&t;&t;ACPI_SYSTEM_COMPONENT
id|ACPI_MODULE_NAME
(paren
l_string|&quot;sleep&quot;
)paren
DECL|function|acpi_system_sleep_seq_show
r_static
r_int
id|acpi_system_sleep_seq_show
c_func
(paren
r_struct
id|seq_file
op_star
id|seq
comma
r_void
op_star
id|offset
)paren
(brace
r_int
id|i
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_system_sleep_seq_show&quot;
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
op_le
id|ACPI_STATE_S5
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|sleep_states
(braket
id|i
)braket
)paren
(brace
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;S%d &quot;
comma
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
id|ACPI_STATE_S4
op_logical_and
id|acpi_gbl_FACS-&gt;S4bios_f
)paren
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;S4bios &quot;
)paren
suffix:semicolon
)brace
)brace
id|seq_puts
c_func
(paren
id|seq
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|acpi_system_sleep_open_fs
r_static
r_int
id|acpi_system_sleep_open_fs
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
id|single_open
c_func
(paren
id|file
comma
id|acpi_system_sleep_seq_show
comma
id|PDE
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|data
)paren
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|acpi_system_write_sleep
id|acpi_system_write_sleep
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
r_char
id|str
(braket
l_int|12
)braket
suffix:semicolon
id|u32
id|state
op_assign
l_int|0
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
r_sizeof
(paren
id|str
)paren
op_minus
l_int|1
)paren
r_goto
id|Done
suffix:semicolon
id|memset
c_func
(paren
id|str
comma
l_int|0
comma
r_sizeof
(paren
id|str
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|str
comma
id|buffer
comma
id|count
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
multiline_comment|/* Check for S4 bios request */
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|str
comma
l_string|&quot;4b&quot;
)paren
)paren
(brace
id|error
op_assign
id|acpi_suspend
c_func
(paren
l_int|4
)paren
suffix:semicolon
r_goto
id|Done
suffix:semicolon
)brace
id|state
op_assign
id|simple_strtoul
c_func
(paren
id|str
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SOFTWARE_SUSPEND
r_if
c_cond
(paren
id|state
op_eq
l_int|4
)paren
(brace
id|software_suspend
c_func
(paren
)paren
suffix:semicolon
r_goto
id|Done
suffix:semicolon
)brace
macro_line|#endif
id|error
op_assign
id|acpi_suspend
c_func
(paren
id|state
)paren
suffix:semicolon
id|Done
suffix:colon
r_return
id|error
ques
c_cond
id|error
suffix:colon
id|count
suffix:semicolon
)brace
DECL|function|acpi_system_alarm_seq_show
r_static
r_int
id|acpi_system_alarm_seq_show
c_func
(paren
r_struct
id|seq_file
op_star
id|seq
comma
r_void
op_star
id|offset
)paren
(brace
id|u32
id|sec
comma
id|min
comma
id|hr
suffix:semicolon
id|u32
id|day
comma
id|mo
comma
id|yr
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_system_alarm_seq_show&quot;
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|rtc_lock
)paren
suffix:semicolon
id|sec
op_assign
id|CMOS_READ
c_func
(paren
id|RTC_SECONDS_ALARM
)paren
suffix:semicolon
id|min
op_assign
id|CMOS_READ
c_func
(paren
id|RTC_MINUTES_ALARM
)paren
suffix:semicolon
id|hr
op_assign
id|CMOS_READ
c_func
(paren
id|RTC_HOURS_ALARM
)paren
suffix:semicolon
macro_line|#if 0&t;/* If we ever get an FACP with proper values... */
r_if
c_cond
(paren
id|acpi_gbl_FADT-&gt;day_alrm
)paren
id|day
op_assign
id|CMOS_READ
c_func
(paren
id|acpi_gbl_FADT-&gt;day_alrm
)paren
suffix:semicolon
r_else
id|day
op_assign
id|CMOS_READ
c_func
(paren
id|RTC_DAY_OF_MONTH
)paren
suffix:semicolon
r_if
c_cond
(paren
id|acpi_gbl_FADT-&gt;mon_alrm
)paren
id|mo
op_assign
id|CMOS_READ
c_func
(paren
id|acpi_gbl_FADT-&gt;mon_alrm
)paren
suffix:semicolon
r_else
id|mo
op_assign
id|CMOS_READ
c_func
(paren
id|RTC_MONTH
)paren
suffix:semicolon
suffix:semicolon
r_if
c_cond
(paren
id|acpi_gbl_FADT-&gt;century
)paren
id|yr
op_assign
id|CMOS_READ
c_func
(paren
id|acpi_gbl_FADT-&gt;century
)paren
op_star
l_int|100
op_plus
id|CMOS_READ
c_func
(paren
id|RTC_YEAR
)paren
suffix:semicolon
r_else
id|yr
op_assign
id|CMOS_READ
c_func
(paren
id|RTC_YEAR
)paren
suffix:semicolon
macro_line|#else
id|day
op_assign
id|CMOS_READ
c_func
(paren
id|RTC_DAY_OF_MONTH
)paren
suffix:semicolon
id|mo
op_assign
id|CMOS_READ
c_func
(paren
id|RTC_MONTH
)paren
suffix:semicolon
id|yr
op_assign
id|CMOS_READ
c_func
(paren
id|RTC_YEAR
)paren
suffix:semicolon
macro_line|#endif
id|spin_unlock
c_func
(paren
op_amp
id|rtc_lock
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|sec
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|min
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|hr
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|day
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|mo
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|yr
)paren
suffix:semicolon
macro_line|#if 0
multiline_comment|/* we&squot;re trusting the FADT (see above)*/
macro_line|#else
multiline_comment|/* If we&squot;re not trusting the FADT, we should at least make it&n;&t; * right for _this_ century... ehm, what is _this_ century?&n;&t; *&n;&t; * TBD:&n;&t; *  ASAP: find piece of code in the kernel, e.g. star tracker driver,&n;&t; *        which we can trust to determine the century correctly. Atom&n;&t; *        watch driver would be nice, too...&n;&t; *&n;&t; *  if that has not happened, change for first release in 2050:&n; &t; *        if (yr&lt;50)&n;&t; *                yr += 2100;&n;&t; *        else&n;&t; *                yr += 2000;   // current line of code&n;&t; *&n;&t; *  if that has not happened either, please do on 2099/12/31:23:59:59&n;&t; *        s/2000/2100&n;&t; *&n;&t; */
id|yr
op_add_assign
l_int|2000
suffix:semicolon
macro_line|#endif
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;%4.4u-&quot;
comma
id|yr
)paren
suffix:semicolon
(paren
id|mo
OG
l_int|12
)paren
ques
c_cond
id|seq_puts
c_func
(paren
id|seq
comma
l_string|&quot;**-&quot;
)paren
suffix:colon
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;%2.2u-&quot;
comma
id|mo
)paren
suffix:semicolon
(paren
id|day
OG
l_int|31
)paren
ques
c_cond
id|seq_puts
c_func
(paren
id|seq
comma
l_string|&quot;** &quot;
)paren
suffix:colon
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;%2.2u &quot;
comma
id|day
)paren
suffix:semicolon
(paren
id|hr
OG
l_int|23
)paren
ques
c_cond
id|seq_puts
c_func
(paren
id|seq
comma
l_string|&quot;**:&quot;
)paren
suffix:colon
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;%2.2u:&quot;
comma
id|hr
)paren
suffix:semicolon
(paren
id|min
OG
l_int|59
)paren
ques
c_cond
id|seq_puts
c_func
(paren
id|seq
comma
l_string|&quot;**:&quot;
)paren
suffix:colon
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;%2.2u:&quot;
comma
id|min
)paren
suffix:semicolon
(paren
id|sec
OG
l_int|59
)paren
ques
c_cond
id|seq_puts
c_func
(paren
id|seq
comma
l_string|&quot;**&bslash;n&quot;
)paren
suffix:colon
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;%2.2u&bslash;n&quot;
comma
id|sec
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|acpi_system_alarm_open_fs
r_static
r_int
id|acpi_system_alarm_open_fs
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
id|single_open
c_func
(paren
id|file
comma
id|acpi_system_alarm_seq_show
comma
id|PDE
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|data
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|get_date_field
id|get_date_field
(paren
r_char
op_star
op_star
id|p
comma
id|u32
op_star
id|value
)paren
(brace
r_char
op_star
id|next
op_assign
l_int|NULL
suffix:semicolon
r_char
op_star
id|string_end
op_assign
l_int|NULL
suffix:semicolon
r_int
id|result
op_assign
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/*&n;&t; * Try to find delimeter, only to insert null.  The end of the&n;&t; * string won&squot;t have one, but is still valid.&n;&t; */
id|next
op_assign
id|strpbrk
c_func
(paren
op_star
id|p
comma
l_string|&quot;- :&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|next
)paren
op_star
id|next
op_increment
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
op_star
id|value
op_assign
id|simple_strtoul
c_func
(paren
op_star
id|p
comma
op_amp
id|string_end
comma
l_int|10
)paren
suffix:semicolon
multiline_comment|/* Signal success if we got a good digit */
r_if
c_cond
(paren
id|string_end
op_ne
op_star
id|p
)paren
id|result
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|next
)paren
op_star
id|p
op_assign
id|next
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|acpi_system_write_alarm
id|acpi_system_write_alarm
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
r_int
id|result
op_assign
l_int|0
suffix:semicolon
r_char
id|alarm_string
(braket
l_int|30
)braket
op_assign
(brace
l_char|&squot;&bslash;0&squot;
)brace
suffix:semicolon
r_char
op_star
id|p
op_assign
id|alarm_string
suffix:semicolon
id|u32
id|sec
comma
id|min
comma
id|hr
comma
id|day
comma
id|mo
comma
id|yr
suffix:semicolon
r_int
id|adjust
op_assign
l_int|0
suffix:semicolon
r_int
r_char
id|rtc_control
op_assign
l_int|0
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_system_write_alarm&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
r_sizeof
(paren
id|alarm_string
)paren
op_minus
l_int|1
)paren
id|return_VALUE
c_func
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|alarm_string
comma
id|buffer
comma
id|count
)paren
)paren
id|return_VALUE
c_func
(paren
op_minus
id|EFAULT
)paren
suffix:semicolon
id|alarm_string
(braket
id|count
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
multiline_comment|/* check for time adjustment */
r_if
c_cond
(paren
id|alarm_string
(braket
l_int|0
)braket
op_eq
l_char|&squot;+&squot;
)paren
(brace
id|p
op_increment
suffix:semicolon
id|adjust
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|result
op_assign
id|get_date_field
c_func
(paren
op_amp
id|p
comma
op_amp
id|yr
)paren
)paren
)paren
r_goto
id|end
suffix:semicolon
r_if
c_cond
(paren
(paren
id|result
op_assign
id|get_date_field
c_func
(paren
op_amp
id|p
comma
op_amp
id|mo
)paren
)paren
)paren
r_goto
id|end
suffix:semicolon
r_if
c_cond
(paren
(paren
id|result
op_assign
id|get_date_field
c_func
(paren
op_amp
id|p
comma
op_amp
id|day
)paren
)paren
)paren
r_goto
id|end
suffix:semicolon
r_if
c_cond
(paren
(paren
id|result
op_assign
id|get_date_field
c_func
(paren
op_amp
id|p
comma
op_amp
id|hr
)paren
)paren
)paren
r_goto
id|end
suffix:semicolon
r_if
c_cond
(paren
(paren
id|result
op_assign
id|get_date_field
c_func
(paren
op_amp
id|p
comma
op_amp
id|min
)paren
)paren
)paren
r_goto
id|end
suffix:semicolon
r_if
c_cond
(paren
(paren
id|result
op_assign
id|get_date_field
c_func
(paren
op_amp
id|p
comma
op_amp
id|sec
)paren
)paren
)paren
r_goto
id|end
suffix:semicolon
r_if
c_cond
(paren
id|sec
OG
l_int|59
)paren
(brace
id|min
op_add_assign
l_int|1
suffix:semicolon
id|sec
op_sub_assign
l_int|60
suffix:semicolon
)brace
r_if
c_cond
(paren
id|min
OG
l_int|59
)paren
(brace
id|hr
op_add_assign
l_int|1
suffix:semicolon
id|min
op_sub_assign
l_int|60
suffix:semicolon
)brace
r_if
c_cond
(paren
id|hr
OG
l_int|23
)paren
(brace
id|day
op_add_assign
l_int|1
suffix:semicolon
id|hr
op_sub_assign
l_int|24
suffix:semicolon
)brace
r_if
c_cond
(paren
id|day
OG
l_int|31
)paren
(brace
id|mo
op_add_assign
l_int|1
suffix:semicolon
id|day
op_sub_assign
l_int|31
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mo
OG
l_int|12
)paren
(brace
id|yr
op_add_assign
l_int|1
suffix:semicolon
id|mo
op_sub_assign
l_int|12
suffix:semicolon
)brace
id|spin_lock_irq
c_func
(paren
op_amp
id|rtc_lock
)paren
suffix:semicolon
id|rtc_control
op_assign
id|CMOS_READ
c_func
(paren
id|RTC_CONTROL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|rtc_control
op_amp
id|RTC_DM_BINARY
)paren
op_logical_or
id|RTC_ALWAYS_BCD
)paren
(brace
id|BIN_TO_BCD
c_func
(paren
id|yr
)paren
suffix:semicolon
id|BIN_TO_BCD
c_func
(paren
id|mo
)paren
suffix:semicolon
id|BIN_TO_BCD
c_func
(paren
id|day
)paren
suffix:semicolon
id|BIN_TO_BCD
c_func
(paren
id|hr
)paren
suffix:semicolon
id|BIN_TO_BCD
c_func
(paren
id|min
)paren
suffix:semicolon
id|BIN_TO_BCD
c_func
(paren
id|sec
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|adjust
)paren
(brace
id|yr
op_add_assign
id|CMOS_READ
c_func
(paren
id|RTC_YEAR
)paren
suffix:semicolon
id|mo
op_add_assign
id|CMOS_READ
c_func
(paren
id|RTC_MONTH
)paren
suffix:semicolon
id|day
op_add_assign
id|CMOS_READ
c_func
(paren
id|RTC_DAY_OF_MONTH
)paren
suffix:semicolon
id|hr
op_add_assign
id|CMOS_READ
c_func
(paren
id|RTC_HOURS
)paren
suffix:semicolon
id|min
op_add_assign
id|CMOS_READ
c_func
(paren
id|RTC_MINUTES
)paren
suffix:semicolon
id|sec
op_add_assign
id|CMOS_READ
c_func
(paren
id|RTC_SECONDS
)paren
suffix:semicolon
)brace
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
op_logical_neg
(paren
id|rtc_control
op_amp
id|RTC_DM_BINARY
)paren
op_logical_or
id|RTC_ALWAYS_BCD
)paren
(brace
id|BCD_TO_BIN
c_func
(paren
id|yr
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|mo
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|day
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|hr
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|min
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|sec
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sec
OG
l_int|59
)paren
(brace
id|min
op_increment
suffix:semicolon
id|sec
op_sub_assign
l_int|60
suffix:semicolon
)brace
r_if
c_cond
(paren
id|min
OG
l_int|59
)paren
(brace
id|hr
op_increment
suffix:semicolon
id|min
op_sub_assign
l_int|60
suffix:semicolon
)brace
r_if
c_cond
(paren
id|hr
OG
l_int|23
)paren
(brace
id|day
op_increment
suffix:semicolon
id|hr
op_sub_assign
l_int|24
suffix:semicolon
)brace
r_if
c_cond
(paren
id|day
OG
l_int|31
)paren
(brace
id|mo
op_increment
suffix:semicolon
id|day
op_sub_assign
l_int|31
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mo
OG
l_int|12
)paren
(brace
id|yr
op_increment
suffix:semicolon
id|mo
op_sub_assign
l_int|12
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|rtc_control
op_amp
id|RTC_DM_BINARY
)paren
op_logical_or
id|RTC_ALWAYS_BCD
)paren
(brace
id|BIN_TO_BCD
c_func
(paren
id|yr
)paren
suffix:semicolon
id|BIN_TO_BCD
c_func
(paren
id|mo
)paren
suffix:semicolon
id|BIN_TO_BCD
c_func
(paren
id|day
)paren
suffix:semicolon
id|BIN_TO_BCD
c_func
(paren
id|hr
)paren
suffix:semicolon
id|BIN_TO_BCD
c_func
(paren
id|min
)paren
suffix:semicolon
id|BIN_TO_BCD
c_func
(paren
id|sec
)paren
suffix:semicolon
)brace
id|spin_lock_irq
c_func
(paren
op_amp
id|rtc_lock
)paren
suffix:semicolon
multiline_comment|/* write the fields the rtc knows about */
id|CMOS_WRITE
c_func
(paren
id|hr
comma
id|RTC_HOURS_ALARM
)paren
suffix:semicolon
id|CMOS_WRITE
c_func
(paren
id|min
comma
id|RTC_MINUTES_ALARM
)paren
suffix:semicolon
id|CMOS_WRITE
c_func
(paren
id|sec
comma
id|RTC_SECONDS_ALARM
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * If the system supports an enhanced alarm it will have non-zero&n;&t; * offsets into the CMOS RAM here -- which for some reason are pointing&n;&t; * to the RTC area of memory.&n;&t; */
macro_line|#if 0
r_if
c_cond
(paren
id|acpi_gbl_FADT-&gt;day_alrm
)paren
id|CMOS_WRITE
c_func
(paren
id|day
comma
id|acpi_gbl_FADT-&gt;day_alrm
)paren
suffix:semicolon
r_if
c_cond
(paren
id|acpi_gbl_FADT-&gt;mon_alrm
)paren
id|CMOS_WRITE
c_func
(paren
id|mo
comma
id|acpi_gbl_FADT-&gt;mon_alrm
)paren
suffix:semicolon
r_if
c_cond
(paren
id|acpi_gbl_FADT-&gt;century
)paren
id|CMOS_WRITE
c_func
(paren
id|yr
op_div
l_int|100
comma
id|acpi_gbl_FADT-&gt;century
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* enable the rtc alarm interrupt */
r_if
c_cond
(paren
op_logical_neg
(paren
id|rtc_control
op_amp
id|RTC_AIE
)paren
)paren
(brace
id|rtc_control
op_or_assign
id|RTC_AIE
suffix:semicolon
id|CMOS_WRITE
c_func
(paren
id|rtc_control
comma
id|RTC_CONTROL
)paren
suffix:semicolon
id|CMOS_READ
c_func
(paren
id|RTC_INTR_FLAGS
)paren
suffix:semicolon
)brace
id|spin_unlock_irq
c_func
(paren
op_amp
id|rtc_lock
)paren
suffix:semicolon
id|acpi_set_register
c_func
(paren
id|ACPI_BITREG_RT_CLOCK_ENABLE
comma
l_int|1
comma
id|ACPI_MTX_LOCK
)paren
suffix:semicolon
id|file-&gt;f_pos
op_add_assign
id|count
suffix:semicolon
id|result
op_assign
l_int|0
suffix:semicolon
id|end
suffix:colon
id|return_VALUE
c_func
(paren
id|result
ques
c_cond
id|result
suffix:colon
id|count
)paren
suffix:semicolon
)brace
DECL|variable|acpi_system_sleep_fops
r_static
r_struct
id|file_operations
id|acpi_system_sleep_fops
op_assign
(brace
dot
id|open
op_assign
id|acpi_system_sleep_open_fs
comma
dot
id|read
op_assign
id|seq_read
comma
dot
id|write
op_assign
id|acpi_system_write_sleep
comma
dot
id|llseek
op_assign
id|seq_lseek
comma
dot
id|release
op_assign
id|single_release
comma
)brace
suffix:semicolon
DECL|variable|acpi_system_alarm_fops
r_static
r_struct
id|file_operations
id|acpi_system_alarm_fops
op_assign
(brace
dot
id|open
op_assign
id|acpi_system_alarm_open_fs
comma
dot
id|read
op_assign
id|seq_read
comma
dot
id|write
op_assign
id|acpi_system_write_alarm
comma
dot
id|llseek
op_assign
id|seq_lseek
comma
dot
id|release
op_assign
id|single_release
comma
)brace
suffix:semicolon
DECL|function|acpi_sleep_proc_init
r_static
r_int
id|acpi_sleep_proc_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|entry
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|acpi_disabled
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* &squot;sleep&squot; [R/W]*/
id|entry
op_assign
id|create_proc_entry
c_func
(paren
id|ACPI_SYSTEM_FILE_SLEEP
comma
id|S_IFREG
op_or
id|S_IRUGO
op_or
id|S_IWUSR
comma
id|acpi_root_dir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|entry
)paren
id|entry-&gt;proc_fops
op_assign
op_amp
id|acpi_system_sleep_fops
suffix:semicolon
multiline_comment|/* &squot;alarm&squot; [R/W] */
id|entry
op_assign
id|create_proc_entry
c_func
(paren
id|ACPI_SYSTEM_FILE_ALARM
comma
id|S_IFREG
op_or
id|S_IRUGO
op_or
id|S_IWUSR
comma
id|acpi_root_dir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|entry
)paren
id|entry-&gt;proc_fops
op_assign
op_amp
id|acpi_system_alarm_fops
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|acpi_sleep_proc_init
id|late_initcall
c_func
(paren
id|acpi_sleep_proc_init
)paren
suffix:semicolon
eof
