macro_line|#ifndef _LINUX_TTY_LDISC_H
DECL|macro|_LINUX_TTY_LDISC_H
mdefine_line|#define _LINUX_TTY_LDISC_H
multiline_comment|/*&n; * This structure defines the interface between the tty line discipline&n; * implementation and the tty routines.  The following routines can be&n; * defined; unless noted otherwise, they are optional, and can be&n; * filled in with a null pointer.&n; *&n; * int&t;(*open)(struct tty_struct *);&n; *&n; * &t;This function is called when the line discipline is associated&n; * &t;with the tty.  The line discipline can use this as an&n; * &t;opportunity to initialize any state needed by the ldisc routines.&n; * &n; * void&t;(*close)(struct tty_struct *);&n; *&n; *&t;This function is called when the line discipline is being&n; * &t;shutdown, either because the tty is being closed or because&n; * &t;the tty is being changed to use a new line discipline&n; * &n; * void&t;(*flush_buffer)(struct tty_struct *tty);&n; *&n; * &t;This function instructs the line discipline to clear its&n; * &t;buffers of any input characters it may have queued to be&n; * &t;delivered to the user mode process.&n; * &n; * ssize_t (*chars_in_buffer)(struct tty_struct *tty);&n; *&n; * &t;This function returns the number of input characters the line&n; *&t;discipline may have queued up to be delivered to the user mode&n; *&t;process.&n; * &n; * ssize_t (*read)(struct tty_struct * tty, struct file * file,&n; *&t;&t;   unsigned char * buf, size_t nr);&n; *&n; * &t;This function is called when the user requests to read from&n; * &t;the tty.  The line discipline will return whatever characters&n; * &t;it has buffered up for the user.  If this function is not&n; * &t;defined, the user will receive an EIO error.&n; * &n; * ssize_t (*write)(struct tty_struct * tty, struct file * file,&n; * &t;&t;    const unsigned char * buf, size_t nr);&n; *&n; * &t;This function is called when the user requests to write to the&n; * &t;tty.  The line discipline will deliver the characters to the&n; * &t;low-level tty device for transmission, optionally performing&n; * &t;some processing on the characters first.  If this function is&n; * &t;not defined, the user will receive an EIO error.&n; * &n; * int&t;(*ioctl)(struct tty_struct * tty, struct file * file,&n; * &t;&t; unsigned int cmd, unsigned long arg);&n; *&n; *&t;This function is called when the user requests an ioctl which&n; * &t;is not handled by the tty layer or the low-level tty driver.&n; * &t;It is intended for ioctls which affect line discpline&n; * &t;operation.  Note that the search order for ioctls is (1) tty&n; * &t;layer, (2) tty low-level driver, (3) line discpline.  So a&n; * &t;low-level driver can &quot;grab&quot; an ioctl request before the line&n; * &t;discpline has a chance to see it.&n; * &n; * void&t;(*set_termios)(struct tty_struct *tty, struct termios * old);&n; *&n; * &t;This function notifies the line discpline that a change has&n; * &t;been made to the termios structure.&n; * &n; * int&t;(*poll)(struct tty_struct * tty, struct file * file,&n; * &t;&t;  poll_table *wait);&n; *&n; * &t;This function is called when a user attempts to select/poll on a&n; * &t;tty device.  It is solely the responsibility of the line&n; * &t;discipline to handle poll requests.&n; *&n; * void&t;(*receive_buf)(struct tty_struct *, const unsigned char *cp,&n; * &t;&t;       char *fp, int count);&n; *&n; * &t;This function is called by the low-level tty driver to send&n; * &t;characters received by the hardware to the line discpline for&n; * &t;processing.  &lt;cp&gt; is a pointer to the buffer of input&n; * &t;character received by the device.  &lt;fp&gt; is a pointer to a&n; * &t;pointer of flag bytes which indicate whether a character was&n; * &t;received with a parity error, etc.&n; * &n; * int&t;(*receive_room)(struct tty_struct *);&n; *&n; * &t;This function is called by the low-level tty driver to&n; * &t;determine how many characters the line discpline can accept.&n; * &t;The low-level driver must not send more characters than was&n; * &t;indicated by receive_room, or the line discpline may drop&n; * &t;those characters.&n; * &n; * void&t;(*write_wakeup)(struct tty_struct *);&n; *&n; * &t;This function is called by the low-level tty driver to signal&n; * &t;that line discpline should try to send more characters to the&n; * &t;low-level driver for transmission.  If the line discpline does&n; * &t;not have any more data to send, it can just return.&n; */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
DECL|struct|tty_ldisc
r_struct
id|tty_ldisc
(brace
DECL|member|magic
r_int
id|magic
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|num
r_int
id|num
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
multiline_comment|/*&n;&t; * The following routines are called from above.&n;&t; */
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
DECL|member|chars_in_buffer
id|ssize_t
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
DECL|member|read
id|ssize_t
(paren
op_star
id|read
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
r_char
id|__user
op_star
id|buf
comma
r_int
id|nr
)paren
suffix:semicolon
DECL|member|write
id|ssize_t
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
r_struct
id|file
op_star
id|file
comma
r_const
r_int
r_char
id|__user
op_star
id|buf
comma
r_int
id|nr
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
DECL|member|poll
r_int
r_int
(paren
op_star
id|poll
)paren
(paren
r_struct
id|tty_struct
op_star
comma
r_struct
id|file
op_star
comma
r_struct
id|poll_table_struct
op_star
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * The following routines are called from below.&n;&t; */
DECL|member|receive_buf
r_void
(paren
op_star
id|receive_buf
)paren
(paren
r_struct
id|tty_struct
op_star
comma
r_const
r_int
r_char
op_star
id|cp
comma
r_char
op_star
id|fp
comma
r_int
id|count
)paren
suffix:semicolon
DECL|member|receive_room
r_int
(paren
op_star
id|receive_room
)paren
(paren
r_struct
id|tty_struct
op_star
)paren
suffix:semicolon
DECL|member|write_wakeup
r_void
(paren
op_star
id|write_wakeup
)paren
(paren
r_struct
id|tty_struct
op_star
)paren
suffix:semicolon
DECL|member|owner
r_struct
id|module
op_star
id|owner
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|TTY_LDISC_MAGIC
mdefine_line|#define TTY_LDISC_MAGIC&t;0x5403
DECL|macro|LDISC_FLAG_DEFINED
mdefine_line|#define LDISC_FLAG_DEFINED&t;0x00000001
DECL|macro|MODULE_ALIAS_LDISC
mdefine_line|#define MODULE_ALIAS_LDISC(ldisc) &bslash;&n;&t;MODULE_ALIAS(&quot;tty-ldisc-&quot; __stringify(ldisc))
macro_line|#endif /* _LINUX_TTY_LDISC_H */
eof
