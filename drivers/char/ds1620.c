multiline_comment|/*&n; * linux/drivers/char/ds1620.c: Dallas Semiconductors DS1620&n; *   thermometer driver (as used in the Rebel.com NetWinder)&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/capability.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/therm.h&gt;
macro_line|#ifdef CONFIG_PROC_FS
multiline_comment|/* define for /proc interface */
DECL|macro|THERM_USE_PROC
mdefine_line|#define THERM_USE_PROC
macro_line|#endif
multiline_comment|/* Definitions for DS1620 chip */
DECL|macro|THERM_START_CONVERT
mdefine_line|#define THERM_START_CONVERT&t;0xee
DECL|macro|THERM_RESET
mdefine_line|#define THERM_RESET&t;&t;0xaf
DECL|macro|THERM_READ_CONFIG
mdefine_line|#define THERM_READ_CONFIG&t;0xac
DECL|macro|THERM_READ_TEMP
mdefine_line|#define THERM_READ_TEMP&t;&t;0xaa
DECL|macro|THERM_READ_TL
mdefine_line|#define THERM_READ_TL&t;&t;0xa2
DECL|macro|THERM_READ_TH
mdefine_line|#define THERM_READ_TH&t;&t;0xa1
DECL|macro|THERM_WRITE_CONFIG
mdefine_line|#define THERM_WRITE_CONFIG&t;0x0c
DECL|macro|THERM_WRITE_TL
mdefine_line|#define THERM_WRITE_TL&t;&t;0x02
DECL|macro|THERM_WRITE_TH
mdefine_line|#define THERM_WRITE_TH&t;&t;0x01
DECL|macro|CFG_CPU
mdefine_line|#define CFG_CPU&t;&t;&t;2
DECL|macro|CFG_1SHOT
mdefine_line|#define CFG_1SHOT&t;&t;1
DECL|variable|fan_state
r_static
r_const
r_char
op_star
id|fan_state
(braket
)braket
op_assign
(brace
l_string|&quot;off&quot;
comma
l_string|&quot;on&quot;
comma
l_string|&quot;on (hardwired)&quot;
)brace
suffix:semicolon
multiline_comment|/*&n; * Start of NetWinder specifics&n; *  Note!  We have to hold the gpio lock with IRQs disabled over the&n; *  whole of our transaction to the Dallas chip, since there is a&n; *  chance that the WaveArtist driver could touch these bits to&n; *  enable or disable the speaker.&n; */
r_extern
id|spinlock_t
id|gpio_lock
suffix:semicolon
r_extern
r_int
r_int
id|system_rev
suffix:semicolon
DECL|function|netwinder_ds1620_set_clk
r_static
r_inline
r_void
id|netwinder_ds1620_set_clk
c_func
(paren
r_int
id|clk
)paren
(brace
id|gpio_modify_op
c_func
(paren
id|GPIO_DSCLK
comma
id|clk
ques
c_cond
id|GPIO_DSCLK
suffix:colon
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|netwinder_ds1620_set_data
r_static
r_inline
r_void
id|netwinder_ds1620_set_data
c_func
(paren
r_int
id|dat
)paren
(brace
id|gpio_modify_op
c_func
(paren
id|GPIO_DATA
comma
id|dat
ques
c_cond
id|GPIO_DATA
suffix:colon
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|netwinder_ds1620_get_data
r_static
r_inline
r_int
id|netwinder_ds1620_get_data
c_func
(paren
r_void
)paren
(brace
r_return
id|gpio_read
c_func
(paren
)paren
op_amp
id|GPIO_DATA
suffix:semicolon
)brace
DECL|function|netwinder_ds1620_set_data_dir
r_static
r_inline
r_void
id|netwinder_ds1620_set_data_dir
c_func
(paren
r_int
id|dir
)paren
(brace
id|gpio_modify_io
c_func
(paren
id|GPIO_DATA
comma
id|dir
ques
c_cond
id|GPIO_DATA
suffix:colon
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|netwinder_ds1620_reset
r_static
r_inline
r_void
id|netwinder_ds1620_reset
c_func
(paren
r_void
)paren
(brace
id|cpld_modify
c_func
(paren
id|CPLD_DS_ENABLE
comma
l_int|0
)paren
suffix:semicolon
id|cpld_modify
c_func
(paren
id|CPLD_DS_ENABLE
comma
id|CPLD_DS_ENABLE
)paren
suffix:semicolon
)brace
DECL|function|netwinder_lock
r_static
r_inline
r_void
id|netwinder_lock
c_func
(paren
r_int
r_int
op_star
id|flags
)paren
(brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|gpio_lock
comma
op_star
id|flags
)paren
suffix:semicolon
)brace
DECL|function|netwinder_unlock
r_static
r_inline
r_void
id|netwinder_unlock
c_func
(paren
r_int
r_int
op_star
id|flags
)paren
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|gpio_lock
comma
op_star
id|flags
)paren
suffix:semicolon
)brace
DECL|function|netwinder_set_fan
r_static
r_inline
r_void
id|netwinder_set_fan
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
id|spin_lock_irqsave
c_func
(paren
op_amp
id|gpio_lock
comma
id|flags
)paren
suffix:semicolon
id|gpio_modify_op
c_func
(paren
id|GPIO_FAN
comma
id|i
ques
c_cond
id|GPIO_FAN
suffix:colon
l_int|0
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|gpio_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|netwinder_get_fan
r_static
r_inline
r_int
id|netwinder_get_fan
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
(paren
id|system_rev
op_amp
l_int|0xf000
)paren
op_eq
l_int|0x4000
)paren
r_return
id|FAN_ALWAYS_ON
suffix:semicolon
r_return
(paren
id|gpio_read
c_func
(paren
)paren
op_amp
id|GPIO_FAN
)paren
ques
c_cond
id|FAN_ON
suffix:colon
id|FAN_OFF
suffix:semicolon
)brace
multiline_comment|/*&n; * End of NetWinder specifics&n; */
DECL|function|ds1620_send_bits
r_static
r_void
id|ds1620_send_bits
c_func
(paren
r_int
id|nr
comma
r_int
id|value
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
id|nr
suffix:semicolon
id|i
op_increment
)paren
(brace
id|netwinder_ds1620_set_data
c_func
(paren
id|value
op_amp
l_int|1
)paren
suffix:semicolon
id|netwinder_ds1620_set_clk
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|netwinder_ds1620_set_clk
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|value
op_rshift_assign
l_int|1
suffix:semicolon
)brace
)brace
DECL|function|ds1620_recv_bits
r_static
r_int
r_int
id|ds1620_recv_bits
c_func
(paren
r_int
id|nr
)paren
(brace
r_int
r_int
id|value
op_assign
l_int|0
comma
id|mask
op_assign
l_int|1
suffix:semicolon
r_int
id|i
suffix:semicolon
id|netwinder_ds1620_set_data
c_func
(paren
l_int|0
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
id|nr
suffix:semicolon
id|i
op_increment
)paren
(brace
id|netwinder_ds1620_set_clk
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|netwinder_ds1620_get_data
c_func
(paren
)paren
)paren
id|value
op_or_assign
id|mask
suffix:semicolon
id|mask
op_lshift_assign
l_int|1
suffix:semicolon
id|netwinder_ds1620_set_clk
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_return
id|value
suffix:semicolon
)brace
DECL|function|ds1620_out
r_static
r_void
id|ds1620_out
c_func
(paren
r_int
id|cmd
comma
r_int
id|bits
comma
r_int
id|value
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|netwinder_lock
c_func
(paren
op_amp
id|flags
)paren
suffix:semicolon
id|netwinder_ds1620_set_clk
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|netwinder_ds1620_set_data_dir
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|netwinder_ds1620_reset
c_func
(paren
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|ds1620_send_bits
c_func
(paren
l_int|8
comma
id|cmd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bits
)paren
id|ds1620_send_bits
c_func
(paren
id|bits
comma
id|value
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|netwinder_ds1620_reset
c_func
(paren
)paren
suffix:semicolon
id|netwinder_unlock
c_func
(paren
op_amp
id|flags
)paren
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
id|schedule_timeout
c_func
(paren
l_int|2
)paren
suffix:semicolon
)brace
DECL|function|ds1620_in
r_static
r_int
r_int
id|ds1620_in
c_func
(paren
r_int
id|cmd
comma
r_int
id|bits
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|value
suffix:semicolon
id|netwinder_lock
c_func
(paren
op_amp
id|flags
)paren
suffix:semicolon
id|netwinder_ds1620_set_clk
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|netwinder_ds1620_set_data_dir
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|netwinder_ds1620_reset
c_func
(paren
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|ds1620_send_bits
c_func
(paren
l_int|8
comma
id|cmd
)paren
suffix:semicolon
id|netwinder_ds1620_set_data_dir
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|value
op_assign
id|ds1620_recv_bits
c_func
(paren
id|bits
)paren
suffix:semicolon
id|netwinder_ds1620_reset
c_func
(paren
)paren
suffix:semicolon
id|netwinder_unlock
c_func
(paren
op_amp
id|flags
)paren
suffix:semicolon
r_return
id|value
suffix:semicolon
)brace
DECL|function|cvt_9_to_int
r_static
r_int
id|cvt_9_to_int
c_func
(paren
r_int
r_int
id|val
)paren
(brace
r_if
c_cond
(paren
id|val
op_amp
l_int|0x100
)paren
id|val
op_or_assign
l_int|0xfffffe00
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
DECL|function|ds1620_write_state
r_static
r_void
id|ds1620_write_state
c_func
(paren
r_struct
id|therm
op_star
id|therm
)paren
(brace
id|ds1620_out
c_func
(paren
id|THERM_WRITE_CONFIG
comma
l_int|8
comma
id|CFG_CPU
)paren
suffix:semicolon
id|ds1620_out
c_func
(paren
id|THERM_WRITE_TL
comma
l_int|9
comma
id|therm-&gt;lo
)paren
suffix:semicolon
id|ds1620_out
c_func
(paren
id|THERM_WRITE_TH
comma
l_int|9
comma
id|therm-&gt;hi
)paren
suffix:semicolon
id|ds1620_out
c_func
(paren
id|THERM_START_CONVERT
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|ds1620_read_state
r_static
r_void
id|ds1620_read_state
c_func
(paren
r_struct
id|therm
op_star
id|therm
)paren
(brace
id|therm-&gt;lo
op_assign
id|cvt_9_to_int
c_func
(paren
id|ds1620_in
c_func
(paren
id|THERM_READ_TL
comma
l_int|9
)paren
)paren
suffix:semicolon
id|therm-&gt;hi
op_assign
id|cvt_9_to_int
c_func
(paren
id|ds1620_in
c_func
(paren
id|THERM_READ_TH
comma
l_int|9
)paren
)paren
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|ds1620_read
id|ds1620_read
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
id|ptr
)paren
(brace
r_int
r_int
id|cur_temp
suffix:semicolon
r_int
r_char
id|cur_temp_degF
suffix:semicolon
multiline_comment|/* Can&squot;t seek (pread) on this device */
r_if
c_cond
(paren
id|ptr
op_ne
op_amp
id|file-&gt;f_pos
)paren
r_return
op_minus
id|ESPIPE
suffix:semicolon
id|cur_temp
op_assign
id|cvt_9_to_int
c_func
(paren
id|ds1620_in
c_func
(paren
id|THERM_READ_TEMP
comma
l_int|9
)paren
)paren
op_rshift
l_int|1
suffix:semicolon
multiline_comment|/* convert to Fahrenheit, as per wdt.c */
id|cur_temp_degF
op_assign
(paren
id|cur_temp
op_star
l_int|9
)paren
op_div
l_int|5
op_plus
l_int|32
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buf
comma
op_amp
id|cur_temp_degF
comma
l_int|1
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_static
r_int
DECL|function|ds1620_ioctl
id|ds1620_ioctl
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
r_struct
id|therm
id|therm
suffix:semicolon
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
id|CMD_SET_THERMOSTATE
suffix:colon
r_case
id|CMD_SET_THERMOSTATE2
suffix:colon
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
r_if
c_cond
(paren
id|cmd
op_eq
id|CMD_SET_THERMOSTATE
)paren
(brace
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|therm.hi
comma
(paren
r_int
op_star
)paren
id|arg
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|therm.lo
op_assign
id|therm.hi
op_minus
l_int|3
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|therm
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|therm
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|therm.lo
op_lshift_assign
l_int|1
suffix:semicolon
id|therm.hi
op_lshift_assign
l_int|1
suffix:semicolon
id|ds1620_write_state
c_func
(paren
op_amp
id|therm
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CMD_GET_THERMOSTATE
suffix:colon
r_case
id|CMD_GET_THERMOSTATE2
suffix:colon
id|ds1620_read_state
c_func
(paren
op_amp
id|therm
)paren
suffix:semicolon
id|therm.lo
op_rshift_assign
l_int|1
suffix:semicolon
id|therm.hi
op_rshift_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|cmd
op_eq
id|CMD_GET_THERMOSTATE
)paren
(brace
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|therm.hi
comma
(paren
r_int
op_star
)paren
id|arg
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_else
(brace
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
id|therm
comma
r_sizeof
(paren
id|therm
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|CMD_GET_TEMPERATURE
suffix:colon
r_case
id|CMD_GET_TEMPERATURE2
suffix:colon
id|i
op_assign
id|cvt_9_to_int
c_func
(paren
id|ds1620_in
c_func
(paren
id|THERM_READ_TEMP
comma
l_int|9
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cmd
op_eq
id|CMD_GET_TEMPERATURE
)paren
id|i
op_rshift_assign
l_int|1
suffix:semicolon
r_return
id|put_user
c_func
(paren
id|i
comma
(paren
r_int
op_star
)paren
id|arg
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
r_case
id|CMD_GET_STATUS
suffix:colon
id|i
op_assign
id|ds1620_in
c_func
(paren
id|THERM_READ_CONFIG
comma
l_int|8
)paren
op_amp
l_int|0xe3
suffix:semicolon
r_return
id|put_user
c_func
(paren
id|i
comma
(paren
r_int
op_star
)paren
id|arg
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
r_case
id|CMD_GET_FAN
suffix:colon
id|i
op_assign
id|netwinder_get_fan
c_func
(paren
)paren
suffix:semicolon
r_return
id|put_user
c_func
(paren
id|i
comma
(paren
r_int
op_star
)paren
id|arg
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
r_case
id|CMD_SET_FAN
suffix:colon
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
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|i
comma
(paren
r_int
op_star
)paren
id|arg
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|netwinder_set_fan
c_func
(paren
id|i
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|ENOIOCTLCMD
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef THERM_USE_PROC
r_static
r_int
DECL|function|proc_therm_ds1620_read
id|proc_therm_ds1620_read
c_func
(paren
r_char
op_star
id|buf
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
id|len
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|unused
)paren
(brace
r_struct
id|therm
id|th
suffix:semicolon
r_int
id|temp
suffix:semicolon
id|ds1620_read_state
c_func
(paren
op_amp
id|th
)paren
suffix:semicolon
id|temp
op_assign
id|cvt_9_to_int
c_func
(paren
id|ds1620_in
c_func
(paren
id|THERM_READ_TEMP
comma
l_int|9
)paren
)paren
suffix:semicolon
id|len
op_assign
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;Thermostat: HI %i.%i, LOW %i.%i; &quot;
l_string|&quot;temperature: %i.%i C, fan %s&bslash;n&quot;
comma
id|th.hi
op_rshift
l_int|1
comma
id|th.hi
op_amp
l_int|1
ques
c_cond
l_int|5
suffix:colon
l_int|0
comma
id|th.lo
op_rshift
l_int|1
comma
id|th.lo
op_amp
l_int|1
ques
c_cond
l_int|5
suffix:colon
l_int|0
comma
id|temp
op_rshift
l_int|1
comma
id|temp
op_amp
l_int|1
ques
c_cond
l_int|5
suffix:colon
l_int|0
comma
id|fan_state
(braket
id|netwinder_get_fan
c_func
(paren
)paren
)braket
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|variable|proc_therm_ds1620
r_static
r_struct
id|proc_dir_entry
op_star
id|proc_therm_ds1620
suffix:semicolon
macro_line|#endif
DECL|variable|ds1620_fops
r_static
r_struct
id|file_operations
id|ds1620_fops
op_assign
(brace
id|owner
suffix:colon
id|THIS_MODULE
comma
id|read
suffix:colon
id|ds1620_read
comma
id|ioctl
suffix:colon
id|ds1620_ioctl
comma
)brace
suffix:semicolon
DECL|variable|ds1620_miscdev
r_static
r_struct
id|miscdevice
id|ds1620_miscdev
op_assign
(brace
id|TEMP_MINOR
comma
l_string|&quot;temp&quot;
comma
op_amp
id|ds1620_fops
)brace
suffix:semicolon
DECL|function|ds1620_init
r_static
r_int
id|__init
id|ds1620_init
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
suffix:semicolon
r_struct
id|therm
id|th
comma
id|th_start
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|machine_is_netwinder
c_func
(paren
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|ds1620_out
c_func
(paren
id|THERM_RESET
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|ds1620_out
c_func
(paren
id|THERM_WRITE_CONFIG
comma
l_int|8
comma
id|CFG_CPU
)paren
suffix:semicolon
id|ds1620_out
c_func
(paren
id|THERM_START_CONVERT
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Trigger the fan to start by setting&n;&t; * temperature high point low.  This kicks&n;&t; * the fan into action.&n;&t; */
id|ds1620_read_state
c_func
(paren
op_amp
id|th
)paren
suffix:semicolon
id|th_start.lo
op_assign
l_int|0
suffix:semicolon
id|th_start.hi
op_assign
l_int|1
suffix:semicolon
id|ds1620_write_state
c_func
(paren
op_amp
id|th_start
)paren
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
id|schedule_timeout
c_func
(paren
l_int|2
op_star
id|HZ
)paren
suffix:semicolon
id|ds1620_write_state
c_func
(paren
op_amp
id|th
)paren
suffix:semicolon
id|ret
op_assign
id|misc_register
c_func
(paren
op_amp
id|ds1620_miscdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
macro_line|#ifdef THERM_USE_PROC
id|proc_therm_ds1620
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;therm&quot;
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|proc_therm_ds1620
)paren
id|proc_therm_ds1620-&gt;read_proc
op_assign
id|proc_therm_ds1620_read
suffix:semicolon
r_else
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;therm: unable to register /proc/therm&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|ds1620_read_state
c_func
(paren
op_amp
id|th
)paren
suffix:semicolon
id|ret
op_assign
id|cvt_9_to_int
c_func
(paren
id|ds1620_in
c_func
(paren
id|THERM_READ_TEMP
comma
l_int|9
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Thermostat: high %i.%i, low %i.%i, &quot;
l_string|&quot;current %i.%i C, fan %s.&bslash;n&quot;
comma
id|th.hi
op_rshift
l_int|1
comma
id|th.hi
op_amp
l_int|1
ques
c_cond
l_int|5
suffix:colon
l_int|0
comma
id|th.lo
op_rshift
l_int|1
comma
id|th.lo
op_amp
l_int|1
ques
c_cond
l_int|5
suffix:colon
l_int|0
comma
id|ret
op_rshift
l_int|1
comma
id|ret
op_amp
l_int|1
ques
c_cond
l_int|5
suffix:colon
l_int|0
comma
id|fan_state
(braket
id|netwinder_get_fan
c_func
(paren
)paren
)braket
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ds1620_exit
r_static
r_void
id|__exit
id|ds1620_exit
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef THERM_USE_PROC
id|remove_proc_entry
c_func
(paren
l_string|&quot;therm&quot;
comma
l_int|NULL
)paren
suffix:semicolon
macro_line|#endif
id|misc_deregister
c_func
(paren
op_amp
id|ds1620_miscdev
)paren
suffix:semicolon
)brace
DECL|variable|ds1620_init
id|module_init
c_func
(paren
id|ds1620_init
)paren
suffix:semicolon
DECL|variable|ds1620_exit
id|module_exit
c_func
(paren
id|ds1620_exit
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
