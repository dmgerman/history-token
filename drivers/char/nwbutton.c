multiline_comment|/*&n; * &t;NetWinder Button Driver-&n; *&t;Copyright (C) Alex Holden &lt;alex@linuxhacker.org&gt; 1998, 1999.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
DECL|macro|__NWBUTTON_C
mdefine_line|#define __NWBUTTON_C&t;&t;/* Tell the header file who we are */
macro_line|#include &quot;nwbutton.h&quot;
DECL|variable|button_press_count
r_static
r_int
id|button_press_count
suffix:semicolon
multiline_comment|/* The count of button presses */
DECL|variable|button_timer
r_static
r_struct
id|timer_list
id|button_timer
suffix:semicolon
multiline_comment|/* Times for the end of a sequence */
r_static
id|DECLARE_WAIT_QUEUE_HEAD
c_func
(paren
id|button_wait_queue
)paren
suffix:semicolon
multiline_comment|/* Used for blocking read */
DECL|variable|button_output_buffer
r_static
r_char
id|button_output_buffer
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* Stores data to write out of device */
DECL|variable|bcount
r_static
r_int
id|bcount
suffix:semicolon
multiline_comment|/* The number of bytes in the buffer */
DECL|variable|bdelay
r_static
r_int
id|bdelay
op_assign
id|BUTTON_DELAY
suffix:semicolon
multiline_comment|/* The delay, in jiffies */
DECL|variable|button_callback_list
r_static
r_struct
id|button_callback
id|button_callback_list
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* The callback list */
DECL|variable|callback_count
r_static
r_int
id|callback_count
suffix:semicolon
multiline_comment|/* The number of callbacks registered */
DECL|variable|reboot_count
r_static
r_int
id|reboot_count
op_assign
id|NUM_PRESSES_REBOOT
suffix:semicolon
multiline_comment|/* Number of presses to reboot */
multiline_comment|/*&n; * This function is called by other drivers to register a callback function&n; * to be called when a particular number of button presses occurs.&n; * The callback list is a static array of 32 entries (I somehow doubt many&n; * people are ever going to want to register more than 32 different actions&n; * to be performed by the kernel on different numbers of button presses ;).&n; * However, if an attempt to register a 33rd entry (perhaps a stuck loop&n; * somewhere registering the same entry over and over?) it will fail to&n; * do so and return -ENOMEM. If an attempt is made to register a null pointer,&n; * it will fail to do so and return -EINVAL.&n; * Because callbacks can be unregistered at random the list can become&n; * fragmented, so we need to search through the list until we find the first&n; * free entry.&n; *&n; * FIXME: Has anyone spotted any locking functions int his code recently ??&n; */
DECL|function|button_add_callback
r_int
id|button_add_callback
(paren
r_void
(paren
op_star
id|callback
)paren
(paren
r_void
)paren
comma
r_int
id|count
)paren
(brace
r_int
id|lp
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|callback_count
op_eq
l_int|32
)paren
(brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|callback
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|callback_count
op_increment
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
(paren
id|button_callback_list
(braket
id|lp
)braket
dot
id|callback
)paren
suffix:semicolon
id|lp
op_increment
)paren
suffix:semicolon
id|button_callback_list
(braket
id|lp
)braket
dot
id|callback
op_assign
id|callback
suffix:semicolon
id|button_callback_list
(braket
id|lp
)braket
dot
id|count
op_assign
id|count
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * This function is called by other drivers to deregister a callback function.&n; * If you attempt to unregister a callback which does not exist, it will fail&n; * with -EINVAL. If there is more than one entry with the same address,&n; * because it searches the list from end to beginning, it will unregister the&n; * last one to be registered first (FILO- First In Last Out).&n; * Note that this is not neccessarily true if the entries are not submitted&n; * at the same time, because another driver could have unregistered a callback&n; * between the submissions creating a gap earlier in the list, which would&n; * be filled first at submission time.&n; */
DECL|function|button_del_callback
r_int
id|button_del_callback
(paren
r_void
(paren
op_star
id|callback
)paren
(paren
r_void
)paren
)paren
(brace
r_int
id|lp
op_assign
l_int|31
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|callback
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_while
c_loop
(paren
id|lp
op_ge
l_int|0
)paren
(brace
r_if
c_cond
(paren
(paren
id|button_callback_list
(braket
id|lp
)braket
dot
id|callback
)paren
op_eq
id|callback
)paren
(brace
id|button_callback_list
(braket
id|lp
)braket
dot
id|callback
op_assign
l_int|NULL
suffix:semicolon
id|button_callback_list
(braket
id|lp
)braket
dot
id|count
op_assign
l_int|0
suffix:semicolon
id|callback_count
op_decrement
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
suffix:semicolon
id|lp
op_decrement
suffix:semicolon
)brace
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/*&n; * This function is called by button_sequence_finished to search through the&n; * list of callback functions, and call any of them whose count argument&n; * matches the current count of button presses. It starts at the beginning&n; * of the list and works up to the end. It will refuse to follow a null&n; * pointer (which should never happen anyway).&n; */
DECL|function|button_consume_callbacks
r_static
r_void
id|button_consume_callbacks
(paren
r_int
id|bpcount
)paren
(brace
r_int
id|lp
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|lp
op_le
l_int|31
suffix:semicolon
id|lp
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|button_callback_list
(braket
id|lp
)braket
dot
id|count
)paren
op_eq
id|bpcount
)paren
(brace
r_if
c_cond
(paren
id|button_callback_list
(braket
id|lp
)braket
dot
id|callback
)paren
(brace
id|button_callback_list
(braket
id|lp
)braket
dot
id|callback
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
)brace
)brace
multiline_comment|/* &n; * This function is called when the button_timer times out.&n; * ie. When you don&squot;t press the button for bdelay jiffies, this is taken to&n; * mean you have ended the sequence of key presses, and this function is&n; * called to wind things up (write the press_count out to /dev/button, call&n; * any matching registered function callbacks, initiate reboot, etc.).&n; */
DECL|function|button_sequence_finished
r_static
r_void
id|button_sequence_finished
(paren
r_int
r_int
id|parameters
)paren
(brace
macro_line|#ifdef CONFIG_NWBUTTON_REBOOT&t;&t;/* Reboot using button is enabled */
r_if
c_cond
(paren
id|button_press_count
op_eq
id|reboot_count
)paren
(brace
id|kill_proc
(paren
l_int|1
comma
id|SIGINT
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Ask init to reboot us */
)brace
macro_line|#endif /* CONFIG_NWBUTTON_REBOOT */
id|button_consume_callbacks
(paren
id|button_press_count
)paren
suffix:semicolon
id|bcount
op_assign
id|sprintf
(paren
id|button_output_buffer
comma
l_string|&quot;%d&bslash;n&quot;
comma
id|button_press_count
)paren
suffix:semicolon
id|button_press_count
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Reset the button press counter */
id|wake_up_interruptible
(paren
op_amp
id|button_wait_queue
)paren
suffix:semicolon
)brace
multiline_comment|/* &n; *  This handler is called when the orange button is pressed (GPIO 10 of the&n; *  SuperIO chip, which maps to logical IRQ 26). If the press_count is 0,&n; *  this is the first press, so it starts a timer and increments the counter.&n; *  If it is higher than 0, it deletes the old timer, starts a new one, and&n; *  increments the counter.&n; */
DECL|function|button_handler
r_static
id|irqreturn_t
id|button_handler
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
r_if
c_cond
(paren
id|button_press_count
)paren
(brace
id|del_timer
(paren
op_amp
id|button_timer
)paren
suffix:semicolon
)brace
id|button_press_count
op_increment
suffix:semicolon
id|init_timer
(paren
op_amp
id|button_timer
)paren
suffix:semicolon
id|button_timer.function
op_assign
id|button_sequence_finished
suffix:semicolon
id|button_timer.expires
op_assign
(paren
id|jiffies
op_plus
id|bdelay
)paren
suffix:semicolon
id|add_timer
(paren
op_amp
id|button_timer
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
multiline_comment|/*&n; * This function is called when a user space program attempts to read&n; * /dev/nwbutton. It puts the device to sleep on the wait queue until&n; * button_sequence_finished writes some data to the buffer and flushes&n; * the queue, at which point it writes the data out to the device and&n; * returns the number of characters it has written. This function is&n; * reentrant, so that many processes can be attempting to read from the&n; * device at any one time.&n; */
DECL|function|button_read
r_static
r_int
id|button_read
(paren
r_struct
id|file
op_star
id|filp
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
id|interruptible_sleep_on
(paren
op_amp
id|button_wait_queue
)paren
suffix:semicolon
r_return
(paren
id|copy_to_user
(paren
id|buffer
comma
op_amp
id|button_output_buffer
comma
id|bcount
)paren
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
id|bcount
suffix:semicolon
)brace
multiline_comment|/* &n; * This structure is the file operations structure, which specifies what&n; * callbacks functions the kernel should call when a user mode process&n; * attempts to perform these operations on the device.&n; */
DECL|variable|button_fops
r_static
r_struct
id|file_operations
id|button_fops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|read
op_assign
id|button_read
comma
)brace
suffix:semicolon
multiline_comment|/* &n; * This structure is the misc device structure, which specifies the minor&n; * device number (158 in this case), the name of the device (for /proc/misc),&n; * and the address of the above file operations structure.&n; */
DECL|variable|button_misc_device
r_static
r_struct
id|miscdevice
id|button_misc_device
op_assign
(brace
id|BUTTON_MINOR
comma
l_string|&quot;nwbutton&quot;
comma
op_amp
id|button_fops
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * This function is called to initialise the driver, either from misc.c at&n; * bootup if the driver is compiled into the kernel, or from init_module&n; * below at module insert time. It attempts to register the device node&n; * and the IRQ and fails with a warning message if either fails, though&n; * neither ever should because the device number and IRQ are unique to&n; * this driver.&n; */
DECL|function|nwbutton_init
r_static
r_int
id|__init
id|nwbutton_init
c_func
(paren
r_void
)paren
(brace
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
id|printk
(paren
id|KERN_INFO
l_string|&quot;NetWinder Button Driver Version %s (C) Alex Holden &quot;
l_string|&quot;&lt;alex@linuxhacker.org&gt; 1998.&bslash;n&quot;
comma
id|VERSION
)paren
suffix:semicolon
r_if
c_cond
(paren
id|misc_register
(paren
op_amp
id|button_misc_device
)paren
)paren
(brace
id|printk
(paren
id|KERN_WARNING
l_string|&quot;nwbutton: Couldn&squot;t register device 10, &quot;
l_string|&quot;%d.&bslash;n&quot;
comma
id|BUTTON_MINOR
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
r_if
c_cond
(paren
id|request_irq
(paren
id|IRQ_NETWINDER_BUTTON
comma
id|button_handler
comma
id|SA_INTERRUPT
comma
l_string|&quot;nwbutton&quot;
comma
l_int|NULL
)paren
)paren
(brace
id|printk
(paren
id|KERN_WARNING
l_string|&quot;nwbutton: IRQ %d is not free.&bslash;n&quot;
comma
id|IRQ_NETWINDER_BUTTON
)paren
suffix:semicolon
id|misc_deregister
(paren
op_amp
id|button_misc_device
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|nwbutton_exit
r_static
r_void
id|__exit
id|nwbutton_exit
(paren
r_void
)paren
(brace
id|free_irq
(paren
id|IRQ_NETWINDER_BUTTON
comma
l_int|NULL
)paren
suffix:semicolon
id|misc_deregister
(paren
op_amp
id|button_misc_device
)paren
suffix:semicolon
)brace
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Alex Holden&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|nwbutton_init
id|module_init
c_func
(paren
id|nwbutton_init
)paren
suffix:semicolon
DECL|variable|nwbutton_exit
id|module_exit
c_func
(paren
id|nwbutton_exit
)paren
suffix:semicolon
eof
