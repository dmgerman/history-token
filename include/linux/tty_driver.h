macro_line|#ifndef _LINUX_TTY_DRIVER_H
DECL|macro|_LINUX_TTY_DRIVER_H
mdefine_line|#define _LINUX_TTY_DRIVER_H
multiline_comment|/*&n; * This structure defines the interface between the low-level tty&n; * driver and the tty routines.  The following routines can be&n; * defined; unless noted otherwise, they are optional, and can be&n; * filled in with a null pointer.&n; *&n; * int  (*open)(struct tty_struct * tty, struct file * filp);&n; *&n; * &t;This routine is called when a particular tty device is opened.&n; * &t;This routine is mandatory; if this routine is not filled in,&n; * &t;the attempted open will fail with ENODEV.&n; *     &n; * void (*close)(struct tty_struct * tty, struct file * filp);&n; *&n; * &t;This routine is called when a particular tty device is closed.&n; *&n; * int (*write)(struct tty_struct * tty, int from_user,&n; * &t;&t; const unsigned char *buf, int count);&n; *&n; * &t;This routine is called by the kernel to write a series of&n; * &t;characters to the tty device.  The characters may come from&n; * &t;user space or kernel space.  This routine will return the&n; *&t;number of characters actually accepted for writing.  This&n; *&t;routine is mandatory.&n; *&n; * void (*put_char)(struct tty_struct *tty, unsigned char ch);&n; *&n; * &t;This routine is called by the kernel to write a single&n; * &t;character to the tty device.  If the kernel uses this routine,&n; * &t;it must call the flush_chars() routine (if defined) when it is&n; * &t;done stuffing characters into the driver.  If there is no room&n; * &t;in the queue, the character is ignored.&n; *&n; * void (*flush_chars)(struct tty_struct *tty);&n; *&n; * &t;This routine is called by the kernel after it has written a&n; * &t;series of characters to the tty device using put_char().  &n; * &n; * int  (*write_room)(struct tty_struct *tty);&n; *&n; * &t;This routine returns the numbers of characters the tty driver&n; * &t;will accept for queuing to be written.  This number is subject&n; * &t;to change as output buffers get emptied, or if the output flow&n; *&t;control is acted.&n; * &n; * int  (*ioctl)(struct tty_struct *tty, struct file * file,&n; * &t;    unsigned int cmd, unsigned long arg);&n; *&n; * &t;This routine allows the tty driver to implement&n; *&t;device-specific ioctl&squot;s.  If the ioctl number passed in cmd&n; * &t;is not recognized by the driver, it should return ENOIOCTLCMD.&n; * &n; * void (*set_termios)(struct tty_struct *tty, struct termios * old);&n; *&n; * &t;This routine allows the tty driver to be notified when&n; * &t;device&squot;s termios settings have changed.  Note that a&n; * &t;well-designed tty driver should be prepared to accept the case&n; * &t;where old == NULL, and try to do something rational.&n; *&n; * void (*set_ldisc)(struct tty_struct *tty);&n; *&n; * &t;This routine allows the tty driver to be notified when the&n; * &t;device&squot;s termios settings have changed.&n; * &n; * void (*throttle)(struct tty_struct * tty);&n; *&n; * &t;This routine notifies the tty driver that input buffers for&n; * &t;the line discipline are close to full, and it should somehow&n; * &t;signal that no more characters should be sent to the tty.&n; * &n; * void (*unthrottle)(struct tty_struct * tty);&n; *&n; * &t;This routine notifies the tty drivers that it should signals&n; * &t;that characters can now be sent to the tty without fear of&n; * &t;overrunning the input buffers of the line disciplines.&n; * &n; * void (*stop)(struct tty_struct *tty);&n; *&n; * &t;This routine notifies the tty driver that it should stop&n; * &t;outputting characters to the tty device.  &n; * &n; * void (*start)(struct tty_struct *tty);&n; *&n; * &t;This routine notifies the tty driver that it resume sending&n; *&t;characters to the tty device.&n; * &n; * void (*hangup)(struct tty_struct *tty);&n; *&n; * &t;This routine notifies the tty driver that it should hangup the&n; * &t;tty device.&n; *&n; * void (*break_ctl)(struct tty_stuct *tty, int state);&n; *&n; * &t;This optional routine requests the tty driver to turn on or&n; * &t;off BREAK status on the RS-232 port.  If state is -1,&n; * &t;then the BREAK status should be turned on; if state is 0, then&n; * &t;BREAK should be turned off.&n; *&n; * &t;If this routine is implemented, the high-level tty driver will&n; * &t;handle the following ioctls: TCSBRK, TCSBRKP, TIOCSBRK,&n; * &t;TIOCCBRK.  Otherwise, these ioctls will be passed down to the&n; * &t;driver to handle.&n; *&n; * void (*wait_until_sent)(struct tty_struct *tty, int timeout);&n; * &n; * &t;This routine waits until the device has written out all of the&n; * &t;characters in its transmitter FIFO.&n; *&n; * void (*send_xchar)(struct tty_struct *tty, char ch);&n; *&n; * &t;This routine is used to send a high-priority XON/XOFF&n; * &t;character to the device.&n; */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/cdev.h&gt;
DECL|struct|tty_driver
r_struct
id|tty_driver
(brace
DECL|member|magic
r_int
id|magic
suffix:semicolon
multiline_comment|/* magic number for this structure */
DECL|member|cdev
r_struct
id|cdev
id|cdev
suffix:semicolon
DECL|member|owner
r_struct
id|module
op_star
id|owner
suffix:semicolon
DECL|member|driver_name
r_const
r_char
op_star
id|driver_name
suffix:semicolon
DECL|member|devfs_name
r_const
r_char
op_star
id|devfs_name
suffix:semicolon
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|name_base
r_int
id|name_base
suffix:semicolon
multiline_comment|/* offset of printed name */
DECL|member|major
r_int
id|major
suffix:semicolon
multiline_comment|/* major device number */
DECL|member|minor_start
r_int
id|minor_start
suffix:semicolon
multiline_comment|/* start of minor device number*/
DECL|member|num
r_int
id|num
suffix:semicolon
multiline_comment|/* number of devices */
DECL|member|type
r_int
id|type
suffix:semicolon
multiline_comment|/* type of tty driver */
DECL|member|subtype
r_int
id|subtype
suffix:semicolon
multiline_comment|/* subtype of tty driver */
DECL|member|init_termios
r_struct
id|termios
id|init_termios
suffix:semicolon
multiline_comment|/* Initial termios */
DECL|member|flags
r_int
id|flags
suffix:semicolon
multiline_comment|/* tty driver flags */
DECL|member|refcount
r_int
id|refcount
suffix:semicolon
multiline_comment|/* for loadable tty drivers */
DECL|member|proc_entry
r_struct
id|proc_dir_entry
op_star
id|proc_entry
suffix:semicolon
multiline_comment|/* /proc fs entry */
DECL|member|other
r_struct
id|tty_driver
op_star
id|other
suffix:semicolon
multiline_comment|/* only used for the PTY driver */
multiline_comment|/*&n;&t; * Pointer to the tty data structures&n;&t; */
DECL|member|ttys
r_struct
id|tty_struct
op_star
op_star
id|ttys
suffix:semicolon
DECL|member|termios
r_struct
id|termios
op_star
op_star
id|termios
suffix:semicolon
DECL|member|termios_locked
r_struct
id|termios
op_star
op_star
id|termios_locked
suffix:semicolon
DECL|member|driver_state
r_void
op_star
id|driver_state
suffix:semicolon
multiline_comment|/* only used for the PTY driver */
multiline_comment|/*&n;&t; * Interface routines from the upper tty layer to the tty&n;&t; * driver.&n;&t; */
DECL|member|open
r_int
(paren
op_star
id|open
)paren
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_struct
id|file
op_star
id|filp
)paren
suffix:semicolon
DECL|member|close
r_void
(paren
op_star
id|close
)paren
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_struct
id|file
op_star
id|filp
)paren
suffix:semicolon
DECL|member|write
r_int
(paren
op_star
id|write
)paren
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_int
id|from_user
comma
r_const
r_int
r_char
op_star
id|buf
comma
r_int
id|count
)paren
suffix:semicolon
DECL|member|put_char
r_void
(paren
op_star
id|put_char
)paren
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_int
r_char
id|ch
)paren
suffix:semicolon
DECL|member|flush_chars
r_void
(paren
op_star
id|flush_chars
)paren
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
suffix:semicolon
DECL|member|write_room
r_int
(paren
op_star
id|write_room
)paren
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
suffix:semicolon
DECL|member|chars_in_buffer
r_int
(paren
op_star
id|chars_in_buffer
)paren
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
suffix:semicolon
DECL|member|ioctl
r_int
(paren
op_star
id|ioctl
)paren
(paren
r_struct
id|tty_struct
op_star
id|tty
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
DECL|member|set_termios
r_void
(paren
op_star
id|set_termios
)paren
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_struct
id|termios
op_star
id|old
)paren
suffix:semicolon
DECL|member|throttle
r_void
(paren
op_star
id|throttle
)paren
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
suffix:semicolon
DECL|member|unthrottle
r_void
(paren
op_star
id|unthrottle
)paren
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
suffix:semicolon
DECL|member|stop
r_void
(paren
op_star
id|stop
)paren
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
suffix:semicolon
DECL|member|start
r_void
(paren
op_star
id|start
)paren
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
suffix:semicolon
DECL|member|hangup
r_void
(paren
op_star
id|hangup
)paren
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
suffix:semicolon
DECL|member|break_ctl
r_void
(paren
op_star
id|break_ctl
)paren
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_int
id|state
)paren
suffix:semicolon
DECL|member|flush_buffer
r_void
(paren
op_star
id|flush_buffer
)paren
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
suffix:semicolon
DECL|member|set_ldisc
r_void
(paren
op_star
id|set_ldisc
)paren
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
suffix:semicolon
DECL|member|wait_until_sent
r_void
(paren
op_star
id|wait_until_sent
)paren
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_int
id|timeout
)paren
suffix:semicolon
DECL|member|send_xchar
r_void
(paren
op_star
id|send_xchar
)paren
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_char
id|ch
)paren
suffix:semicolon
DECL|member|read_proc
r_int
(paren
op_star
id|read_proc
)paren
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
DECL|member|write_proc
r_int
(paren
op_star
id|write_proc
)paren
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
op_star
id|buffer
comma
r_int
r_int
id|count
comma
r_void
op_star
id|data
)paren
suffix:semicolon
DECL|member|tiocmget
r_int
(paren
op_star
id|tiocmget
)paren
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_struct
id|file
op_star
id|file
)paren
suffix:semicolon
DECL|member|tiocmset
r_int
(paren
op_star
id|tiocmset
)paren
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|set
comma
r_int
r_int
id|clear
)paren
suffix:semicolon
DECL|member|tty_drivers
r_struct
id|list_head
id|tty_drivers
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|list_head
id|tty_drivers
suffix:semicolon
multiline_comment|/* tty driver magic number */
DECL|macro|TTY_DRIVER_MAGIC
mdefine_line|#define TTY_DRIVER_MAGIC&t;&t;0x5402
multiline_comment|/*&n; * tty driver flags&n; * &n; * TTY_DRIVER_RESET_TERMIOS --- requests the tty layer to reset the&n; * &t;termios setting when the last process has closed the device.&n; * &t;Used for PTY&squot;s, in particular.&n; * &n; * TTY_DRIVER_REAL_RAW --- if set, indicates that the driver will&n; * &t;guarantee never not to set any special character handling&n; * &t;flags if ((IGNBRK || (!BRKINT &amp;&amp; !PARMRK)) &amp;&amp; (IGNPAR ||&n; * &t;!INPCK)).  That is, if there is no reason for the driver to&n; * &t;send notifications of parity and break characters up to the&n; * &t;line driver, it won&squot;t do so.  This allows the line driver to&n; *&t;optimize for this case if this flag is set.  (Note that there&n; * &t;is also a promise, if the above case is true, not to signal&n; * &t;overruns, either.)&n; *&n; * TTY_DRIVER_NO_DEVFS --- if set, do not create devfs entries. This&n; *&t;is only used by tty_register_driver().&n; *&n; */
DECL|macro|TTY_DRIVER_INSTALLED
mdefine_line|#define TTY_DRIVER_INSTALLED&t;&t;0x0001
DECL|macro|TTY_DRIVER_RESET_TERMIOS
mdefine_line|#define TTY_DRIVER_RESET_TERMIOS&t;0x0002
DECL|macro|TTY_DRIVER_REAL_RAW
mdefine_line|#define TTY_DRIVER_REAL_RAW&t;&t;0x0004
DECL|macro|TTY_DRIVER_NO_DEVFS
mdefine_line|#define TTY_DRIVER_NO_DEVFS&t;&t;0x0008
multiline_comment|/* tty driver types */
DECL|macro|TTY_DRIVER_TYPE_SYSTEM
mdefine_line|#define TTY_DRIVER_TYPE_SYSTEM&t;&t;0x0001
DECL|macro|TTY_DRIVER_TYPE_CONSOLE
mdefine_line|#define TTY_DRIVER_TYPE_CONSOLE&t;&t;0x0002
DECL|macro|TTY_DRIVER_TYPE_SERIAL
mdefine_line|#define TTY_DRIVER_TYPE_SERIAL&t;&t;0x0003
DECL|macro|TTY_DRIVER_TYPE_PTY
mdefine_line|#define TTY_DRIVER_TYPE_PTY&t;&t;0x0004
DECL|macro|TTY_DRIVER_TYPE_SCC
mdefine_line|#define TTY_DRIVER_TYPE_SCC&t;&t;0x0005&t;/* scc driver */
DECL|macro|TTY_DRIVER_TYPE_SYSCONS
mdefine_line|#define TTY_DRIVER_TYPE_SYSCONS&t;&t;0x0006
multiline_comment|/* system subtypes (magic, used by tty_io.c) */
DECL|macro|SYSTEM_TYPE_TTY
mdefine_line|#define SYSTEM_TYPE_TTY&t;&t;&t;0x0001
DECL|macro|SYSTEM_TYPE_CONSOLE
mdefine_line|#define SYSTEM_TYPE_CONSOLE&t;&t;0x0002
DECL|macro|SYSTEM_TYPE_SYSCONS
mdefine_line|#define SYSTEM_TYPE_SYSCONS&t;&t;0x0003
DECL|macro|SYSTEM_TYPE_SYSPTMX
mdefine_line|#define SYSTEM_TYPE_SYSPTMX&t;&t;0x0004
multiline_comment|/* pty subtypes (magic, used by tty_io.c) */
DECL|macro|PTY_TYPE_MASTER
mdefine_line|#define PTY_TYPE_MASTER&t;&t;&t;0x0001
DECL|macro|PTY_TYPE_SLAVE
mdefine_line|#define PTY_TYPE_SLAVE&t;&t;&t;0x0002
multiline_comment|/* serial subtype definitions */
DECL|macro|SERIAL_TYPE_NORMAL
mdefine_line|#define SERIAL_TYPE_NORMAL&t;1
DECL|macro|SERIAL_TYPE_CALLOUT
mdefine_line|#define SERIAL_TYPE_CALLOUT&t;2
macro_line|#endif /* #ifdef _LINUX_TTY_DRIVER_H */
eof
