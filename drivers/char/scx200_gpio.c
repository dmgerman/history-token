multiline_comment|/* linux/drivers/char/scx200_gpio.c &n;&n;   National Semiconductor SCx200 GPIO driver.  Allows a user space&n;   process to play with the GPIO pins.&n;&n;   Copyright (c) 2001,2002 Christer Weinigel &lt;wingel@nano-system.com&gt; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/scx200_gpio.h&gt;
DECL|macro|NAME
mdefine_line|#define NAME &quot;scx200_gpio&quot;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Christer Weinigel &lt;wingel@nano-system.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;NatSemi SCx200 GPIO Pin Driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|major
r_static
r_int
id|major
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* default to dynamic major */
id|MODULE_PARM
c_func
(paren
id|major
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|major
comma
l_string|&quot;Major device number&quot;
)paren
suffix:semicolon
DECL|function|scx200_gpio_write
r_static
id|ssize_t
id|scx200_gpio_write
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
id|data
comma
r_int
id|len
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_int
id|m
op_assign
id|iminor
c_func
(paren
id|file-&gt;f_dentry-&gt;d_inode
)paren
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|ppos
op_ne
op_amp
id|file-&gt;f_pos
)paren
r_return
op_minus
id|ESPIPE
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
id|len
suffix:semicolon
op_increment
id|i
)paren
(brace
r_char
id|c
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|c
comma
id|data
op_plus
id|i
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_switch
c_cond
(paren
id|c
)paren
(brace
r_case
l_char|&squot;0&squot;
suffix:colon
id|scx200_gpio_set
c_func
(paren
id|m
comma
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;1&squot;
suffix:colon
id|scx200_gpio_set
c_func
(paren
id|m
comma
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;O&squot;
suffix:colon
id|printk
c_func
(paren
id|KERN_INFO
id|NAME
l_string|&quot;: GPIO%d output enabled&bslash;n&quot;
comma
id|m
)paren
suffix:semicolon
id|scx200_gpio_configure
c_func
(paren
id|m
comma
op_complement
l_int|1
comma
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;o&squot;
suffix:colon
id|printk
c_func
(paren
id|KERN_INFO
id|NAME
l_string|&quot;: GPIO%d output disabled&bslash;n&quot;
comma
id|m
)paren
suffix:semicolon
id|scx200_gpio_configure
c_func
(paren
id|m
comma
op_complement
l_int|1
comma
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;T&squot;
suffix:colon
id|printk
c_func
(paren
id|KERN_INFO
id|NAME
l_string|&quot;: GPIO%d output is push pull&bslash;n&quot;
comma
id|m
)paren
suffix:semicolon
id|scx200_gpio_configure
c_func
(paren
id|m
comma
op_complement
l_int|2
comma
l_int|2
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;t&squot;
suffix:colon
id|printk
c_func
(paren
id|KERN_INFO
id|NAME
l_string|&quot;: GPIO%d output is open drain&bslash;n&quot;
comma
id|m
)paren
suffix:semicolon
id|scx200_gpio_configure
c_func
(paren
id|m
comma
op_complement
l_int|2
comma
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;P&squot;
suffix:colon
id|printk
c_func
(paren
id|KERN_INFO
id|NAME
l_string|&quot;: GPIO%d pull up enabled&bslash;n&quot;
comma
id|m
)paren
suffix:semicolon
id|scx200_gpio_configure
c_func
(paren
id|m
comma
op_complement
l_int|4
comma
l_int|4
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;p&squot;
suffix:colon
id|printk
c_func
(paren
id|KERN_INFO
id|NAME
l_string|&quot;: GPIO%d pull up disabled&bslash;n&quot;
comma
id|m
)paren
suffix:semicolon
id|scx200_gpio_configure
c_func
(paren
id|m
comma
op_complement
l_int|4
comma
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_return
id|len
suffix:semicolon
)brace
DECL|function|scx200_gpio_read
r_static
id|ssize_t
id|scx200_gpio_read
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
id|len
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_int
id|m
op_assign
id|iminor
c_func
(paren
id|file-&gt;f_dentry-&gt;d_inode
)paren
suffix:semicolon
r_int
id|value
suffix:semicolon
r_if
c_cond
(paren
id|ppos
op_ne
op_amp
id|file-&gt;f_pos
)paren
r_return
op_minus
id|ESPIPE
suffix:semicolon
id|value
op_assign
id|scx200_gpio_get
c_func
(paren
id|m
)paren
suffix:semicolon
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|value
ques
c_cond
l_char|&squot;1&squot;
suffix:colon
l_char|&squot;0&squot;
comma
id|buf
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
DECL|function|scx200_gpio_open
r_static
r_int
id|scx200_gpio_open
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
r_int
id|m
op_assign
id|iminor
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|m
OG
l_int|63
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|scx200_gpio_release
r_static
r_int
id|scx200_gpio_release
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
DECL|variable|scx200_gpio_fops
r_static
r_struct
id|file_operations
id|scx200_gpio_fops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|write
op_assign
id|scx200_gpio_write
comma
dot
id|read
op_assign
id|scx200_gpio_read
comma
dot
id|open
op_assign
id|scx200_gpio_open
comma
dot
id|release
op_assign
id|scx200_gpio_release
comma
)brace
suffix:semicolon
DECL|function|scx200_gpio_init
r_static
r_int
id|__init
id|scx200_gpio_init
c_func
(paren
r_void
)paren
(brace
r_int
id|r
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
id|NAME
l_string|&quot;: NatSemi SCx200 GPIO Driver&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|scx200_gpio_present
c_func
(paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|NAME
l_string|&quot;: no SCx200 gpio pins available&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|r
op_assign
id|register_chrdev
c_func
(paren
id|major
comma
id|NAME
comma
op_amp
id|scx200_gpio_fops
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|NAME
l_string|&quot;: unable to register character device&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|r
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|major
)paren
(brace
id|major
op_assign
id|r
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
id|NAME
l_string|&quot;: got dynamic major %d&bslash;n&quot;
comma
id|major
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|scx200_gpio_cleanup
r_static
r_void
id|__exit
id|scx200_gpio_cleanup
c_func
(paren
r_void
)paren
(brace
id|unregister_chrdev
c_func
(paren
id|major
comma
id|NAME
)paren
suffix:semicolon
)brace
DECL|variable|scx200_gpio_init
id|module_init
c_func
(paren
id|scx200_gpio_init
)paren
suffix:semicolon
DECL|variable|scx200_gpio_cleanup
id|module_exit
c_func
(paren
id|scx200_gpio_cleanup
)paren
suffix:semicolon
multiline_comment|/*&n;    Local variables:&n;        compile-command: &quot;make -k -C ../.. SUBDIRS=drivers/char modules&quot;&n;        c-basic-offset: 8&n;    End:&n;*/
eof
