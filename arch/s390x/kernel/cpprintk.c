macro_line|#include &quot;cpcmd.h&quot;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/tty_driver.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|variable|buf
r_static
r_char
id|buf
(braket
l_int|1024
)braket
suffix:semicolon
DECL|function|s390printk
id|asmlinkage
r_int
id|s390printk
c_func
(paren
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
(brace
id|va_list
id|args
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|console_lock
comma
id|flags
)paren
suffix:semicolon
id|va_start
c_func
(paren
id|args
comma
id|fmt
)paren
suffix:semicolon
id|i
op_assign
id|vsprintf
c_func
(paren
op_amp
id|buf
(braket
l_int|0
)braket
comma
l_string|&quot;MSG * &quot;
comma
id|args
)paren
suffix:semicolon
id|i
op_assign
id|vsprintf
c_func
(paren
op_amp
id|buf
(braket
id|i
)braket
comma
id|fmt
comma
id|args
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|args
)paren
suffix:semicolon
id|cpcmd
c_func
(paren
id|buf
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|console_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
eof
