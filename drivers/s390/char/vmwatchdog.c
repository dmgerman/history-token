multiline_comment|/*&n; * Watchdog implementation based on z/VM Watchdog Timer API&n; *&n; * The user space watchdog daemon can use this driver as&n; * /dev/vmwatchdog to have z/VM execute the specified CP&n; * command when the timeout expires. The default command is&n; * &quot;IPL&quot;, which which cause an immediate reboot.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;linux/watchdog.h&gt;
macro_line|#include &lt;asm/ebcdic.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|macro|MAX_CMDLEN
mdefine_line|#define MAX_CMDLEN 240
DECL|macro|MIN_INTERVAL
mdefine_line|#define MIN_INTERVAL 15
DECL|variable|vmwdt_cmd
r_static
r_char
id|vmwdt_cmd
(braket
id|MAX_CMDLEN
)braket
op_assign
l_string|&quot;IPL&quot;
suffix:semicolon
DECL|variable|vmwdt_conceal
r_static
r_int
id|vmwdt_conceal
suffix:semicolon
macro_line|#ifdef CONFIG_WATCHDOG_NOWAYOUT
DECL|variable|vmwdt_nowayout
r_static
r_int
id|vmwdt_nowayout
op_assign
l_int|1
suffix:semicolon
macro_line|#else
DECL|variable|vmwdt_nowayout
r_static
r_int
id|vmwdt_nowayout
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Arnd Bergmann &lt;arndb@de.ibm.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;z/VM Watchdog Timer&quot;
)paren
suffix:semicolon
id|module_param_string
c_func
(paren
id|cmd
comma
id|vmwdt_cmd
comma
id|MAX_CMDLEN
comma
l_int|0644
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|cmd
comma
l_string|&quot;CP command that is run when the watchdog triggers&quot;
)paren
suffix:semicolon
id|module_param_named
c_func
(paren
id|conceal
comma
id|vmwdt_conceal
comma
r_bool
comma
l_int|0644
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|conceal
comma
l_string|&quot;Enable the CONCEAL CP option while the watchdog &quot;
l_string|&quot; is active&quot;
)paren
suffix:semicolon
id|module_param_named
c_func
(paren
id|nowayout
comma
id|vmwdt_nowayout
comma
r_bool
comma
l_int|0
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|nowayout
comma
l_string|&quot;Watchdog cannot be stopped once started&quot;
l_string|&quot; (default=CONFIG_WATCHDOG_NOWAYOUT)&quot;
)paren
suffix:semicolon
DECL|variable|WATCHDOG_MINOR
id|MODULE_ALIAS_MISCDEV
c_func
(paren
id|WATCHDOG_MINOR
)paren
suffix:semicolon
DECL|variable|vmwdt_interval
r_static
r_int
r_int
id|vmwdt_interval
op_assign
l_int|60
suffix:semicolon
DECL|variable|vmwdt_is_open
r_static
r_int
r_int
id|vmwdt_is_open
suffix:semicolon
DECL|variable|vmwdt_expect_close
r_static
r_int
id|vmwdt_expect_close
suffix:semicolon
DECL|enum|vmwdt_func
r_enum
id|vmwdt_func
(brace
multiline_comment|/* function codes */
DECL|enumerator|wdt_init
id|wdt_init
op_assign
l_int|0
comma
DECL|enumerator|wdt_change
id|wdt_change
op_assign
l_int|1
comma
DECL|enumerator|wdt_cancel
id|wdt_cancel
op_assign
l_int|2
comma
multiline_comment|/* flags */
DECL|enumerator|wdt_conceal
id|wdt_conceal
op_assign
l_int|0x80000000
comma
)brace
suffix:semicolon
DECL|function|__diag288
r_static
r_int
id|__diag288
c_func
(paren
r_enum
id|vmwdt_func
id|func
comma
r_int
r_int
id|timeout
comma
r_char
op_star
id|cmd
comma
r_int
id|len
)paren
(brace
r_register
r_int
r_int
id|__func
id|asm
c_func
(paren
l_string|&quot;2&quot;
)paren
suffix:semicolon
r_register
r_int
r_int
id|__timeout
id|asm
c_func
(paren
l_string|&quot;3&quot;
)paren
suffix:semicolon
r_register
r_int
r_int
id|__cmdp
id|asm
c_func
(paren
l_string|&quot;4&quot;
)paren
suffix:semicolon
r_register
r_int
r_int
id|__cmdl
id|asm
c_func
(paren
l_string|&quot;5&quot;
)paren
suffix:semicolon
r_int
id|err
suffix:semicolon
id|__func
op_assign
id|func
suffix:semicolon
id|__timeout
op_assign
id|timeout
suffix:semicolon
id|__cmdp
op_assign
id|virt_to_phys
c_func
(paren
id|cmd
)paren
suffix:semicolon
id|__cmdl
op_assign
id|len
suffix:semicolon
id|err
op_assign
l_int|0
suffix:semicolon
id|asm
r_volatile
(paren
macro_line|#ifdef __s390x__
l_string|&quot;diag %2,%4,0x288&bslash;n&quot;
l_string|&quot;1:&t;&bslash;n&quot;
l_string|&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;2:&t;lghi %0,%1&bslash;n&quot;
l_string|&quot;&t;jg 1b&bslash;n&quot;
l_string|&quot;.previous&bslash;n&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;&t;.align 8&bslash;n&quot;
l_string|&quot;&t;.quad 1b,2b&bslash;n&quot;
l_string|&quot;.previous&bslash;n&quot;
macro_line|#else
l_string|&quot;diag %2,%4,0x288&bslash;n&quot;
l_string|&quot;1:&t;&bslash;n&quot;
l_string|&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;2:&t;lhi %0,%1&bslash;n&quot;
l_string|&quot;&t;bras 1,3f&bslash;n&quot;
l_string|&quot;&t;.long 1b&bslash;n&quot;
l_string|&quot;3:&t;l 1,0(1)&bslash;n&quot;
l_string|&quot;&t;br 1&bslash;n&quot;
l_string|&quot;.previous&bslash;n&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;&t;.align 4&bslash;n&quot;
l_string|&quot;&t;.long 1b,2b&bslash;n&quot;
l_string|&quot;.previous&bslash;n&quot;
macro_line|#endif
suffix:colon
l_string|&quot;+&amp;d&quot;
(paren
id|err
)paren
suffix:colon
l_string|&quot;i&quot;
(paren
op_minus
id|EINVAL
)paren
comma
l_string|&quot;d&quot;
(paren
id|__func
)paren
comma
l_string|&quot;d&quot;
(paren
id|__timeout
)paren
comma
l_string|&quot;d&quot;
(paren
id|__cmdp
)paren
comma
l_string|&quot;d&quot;
(paren
id|__cmdl
)paren
suffix:colon
l_string|&quot;1&quot;
comma
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|vmwdt_keepalive
r_static
r_int
id|vmwdt_keepalive
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* we allocate new memory every time to avoid having&n;&t; * to track the state. static allocation is not an&n;&t; * option since that might not be contiguous in real&n;&t; * storage in case of a modular build */
r_static
r_char
op_star
id|ebc_cmd
suffix:semicolon
r_int
id|len
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_int
r_int
id|func
suffix:semicolon
id|ebc_cmd
op_assign
id|kmalloc
c_func
(paren
id|MAX_CMDLEN
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ebc_cmd
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|len
op_assign
id|strlcpy
c_func
(paren
id|ebc_cmd
comma
id|vmwdt_cmd
comma
id|MAX_CMDLEN
)paren
suffix:semicolon
id|ASCEBC
c_func
(paren
id|ebc_cmd
comma
id|MAX_CMDLEN
)paren
suffix:semicolon
id|EBC_TOUPPER
c_func
(paren
id|ebc_cmd
comma
id|MAX_CMDLEN
)paren
suffix:semicolon
id|func
op_assign
id|vmwdt_conceal
ques
c_cond
(paren
id|wdt_init
op_or
id|wdt_conceal
)paren
suffix:colon
id|wdt_init
suffix:semicolon
id|ret
op_assign
id|__diag288
c_func
(paren
id|func
comma
id|vmwdt_interval
comma
id|ebc_cmd
comma
id|len
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|ebc_cmd
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
id|KERN_WARNING
l_string|&quot;%s: problem setting interval %d, &quot;
l_string|&quot;cmd %s&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|vmwdt_interval
comma
id|vmwdt_cmd
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|vmwdt_disable
r_static
r_int
id|vmwdt_disable
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
op_assign
id|__diag288
c_func
(paren
id|wdt_cancel
comma
l_int|0
comma
l_string|&quot;&quot;
comma
l_int|0
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
id|KERN_WARNING
l_string|&quot;%s: problem disabling watchdog&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|vmwdt_probe
r_static
r_int
id|__init
id|vmwdt_probe
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* there is no real way to see if the watchdog is supported,&n;&t; * so we try initializing it with a NOP command (&quot;BEGIN&quot;)&n;&t; * that won&squot;t cause any harm even if the following disable&n;&t; * fails for some reason */
r_static
r_char
id|__initdata
id|ebc_begin
(braket
)braket
op_assign
(brace
l_int|194
comma
l_int|197
comma
l_int|199
comma
l_int|201
comma
l_int|213
)brace
suffix:semicolon
r_if
c_cond
(paren
id|__diag288
c_func
(paren
id|wdt_init
comma
l_int|15
comma
id|ebc_begin
comma
r_sizeof
(paren
id|ebc_begin
)paren
)paren
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;z/VM watchdog not available&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
id|vmwdt_disable
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|vmwdt_open
r_static
r_int
id|vmwdt_open
c_func
(paren
r_struct
id|inode
op_star
id|i
comma
r_struct
id|file
op_star
id|f
)paren
(brace
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|test_and_set_bit
c_func
(paren
l_int|0
comma
op_amp
id|vmwdt_is_open
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|ret
op_assign
id|vmwdt_keepalive
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
id|clear_bit
c_func
(paren
l_int|0
comma
op_amp
id|vmwdt_is_open
)paren
suffix:semicolon
r_return
id|ret
ques
c_cond
id|ret
suffix:colon
id|nonseekable_open
c_func
(paren
id|i
comma
id|f
)paren
suffix:semicolon
)brace
DECL|function|vmwdt_close
r_static
r_int
id|vmwdt_close
c_func
(paren
r_struct
id|inode
op_star
id|i
comma
r_struct
id|file
op_star
id|f
)paren
(brace
r_if
c_cond
(paren
id|vmwdt_expect_close
op_eq
l_int|42
)paren
id|vmwdt_disable
c_func
(paren
)paren
suffix:semicolon
id|vmwdt_expect_close
op_assign
l_int|0
suffix:semicolon
id|clear_bit
c_func
(paren
l_int|0
comma
op_amp
id|vmwdt_is_open
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|vmwdt_info
r_static
r_struct
id|watchdog_info
id|vmwdt_info
op_assign
(brace
dot
id|options
op_assign
id|WDIOF_SETTIMEOUT
op_or
id|WDIOF_KEEPALIVEPING
op_or
id|WDIOF_MAGICCLOSE
comma
dot
id|firmware_version
op_assign
l_int|0
comma
dot
id|identity
op_assign
l_string|&quot;z/VM Watchdog Timer&quot;
comma
)brace
suffix:semicolon
DECL|function|vmwdt_ioctl
r_static
r_int
id|vmwdt_ioctl
c_func
(paren
r_struct
id|inode
op_star
id|i
comma
r_struct
id|file
op_star
id|f
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
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|WDIOC_GETSUPPORT
suffix:colon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_void
id|__user
op_star
)paren
id|arg
comma
op_amp
id|vmwdt_info
comma
r_sizeof
(paren
id|vmwdt_info
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|WDIOC_GETSTATUS
suffix:colon
r_case
id|WDIOC_GETBOOTSTATUS
suffix:colon
r_return
id|put_user
c_func
(paren
l_int|0
comma
(paren
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
r_case
id|WDIOC_GETTEMP
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
r_case
id|WDIOC_SETOPTIONS
suffix:colon
(brace
r_int
id|options
comma
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|options
comma
(paren
r_int
id|__user
op_star
)paren
id|arg
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|options
op_amp
id|WDIOS_DISABLECARD
)paren
(brace
id|ret
op_assign
id|vmwdt_disable
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
)brace
r_if
c_cond
(paren
id|options
op_amp
id|WDIOS_ENABLECARD
)paren
(brace
id|ret
op_assign
id|vmwdt_keepalive
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
r_case
id|WDIOC_GETTIMEOUT
suffix:colon
r_return
id|put_user
c_func
(paren
id|vmwdt_interval
comma
(paren
r_int
id|__user
op_star
)paren
id|arg
)paren
suffix:semicolon
r_case
id|WDIOC_SETTIMEOUT
suffix:colon
(brace
r_int
id|interval
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|interval
comma
(paren
r_int
id|__user
op_star
)paren
id|arg
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|interval
OL
id|MIN_INTERVAL
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|vmwdt_interval
op_assign
id|interval
suffix:semicolon
)brace
r_return
id|vmwdt_keepalive
c_func
(paren
)paren
suffix:semicolon
r_case
id|WDIOC_KEEPALIVE
suffix:colon
r_return
id|vmwdt_keepalive
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|vmwdt_write
r_static
id|ssize_t
id|vmwdt_write
c_func
(paren
r_struct
id|file
op_star
id|f
comma
r_const
r_char
id|__user
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
r_if
c_cond
(paren
id|count
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|vmwdt_nowayout
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* note: just in case someone wrote the magic character&n;&t;&t;&t; * five months ago... */
id|vmwdt_expect_close
op_assign
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
op_ne
id|count
suffix:semicolon
id|i
op_increment
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
id|buf
op_plus
id|i
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;V&squot;
)paren
id|vmwdt_expect_close
op_assign
l_int|42
suffix:semicolon
)brace
)brace
multiline_comment|/* someone wrote to us, we should restart timer */
id|vmwdt_keepalive
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
id|count
suffix:semicolon
)brace
DECL|variable|vmwdt_fops
r_static
r_struct
id|file_operations
id|vmwdt_fops
op_assign
(brace
dot
id|open
op_assign
op_amp
id|vmwdt_open
comma
dot
id|release
op_assign
op_amp
id|vmwdt_close
comma
dot
id|ioctl
op_assign
op_amp
id|vmwdt_ioctl
comma
dot
id|write
op_assign
op_amp
id|vmwdt_write
comma
dot
id|owner
op_assign
id|THIS_MODULE
comma
)brace
suffix:semicolon
DECL|variable|vmwdt_dev
r_static
r_struct
id|miscdevice
id|vmwdt_dev
op_assign
(brace
dot
id|minor
op_assign
id|WATCHDOG_MINOR
comma
dot
id|name
op_assign
l_string|&quot;watchdog&quot;
comma
dot
id|fops
op_assign
op_amp
id|vmwdt_fops
comma
)brace
suffix:semicolon
DECL|function|vmwdt_init
r_static
r_int
id|__init
id|vmwdt_init
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
suffix:semicolon
id|ret
op_assign
id|vmwdt_probe
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
r_return
id|misc_register
c_func
(paren
op_amp
id|vmwdt_dev
)paren
suffix:semicolon
)brace
DECL|variable|vmwdt_init
id|module_init
c_func
(paren
id|vmwdt_init
)paren
suffix:semicolon
DECL|function|vmwdt_exit
r_static
r_void
id|__exit
id|vmwdt_exit
c_func
(paren
r_void
)paren
(brace
id|WARN_ON
c_func
(paren
id|misc_deregister
c_func
(paren
op_amp
id|vmwdt_dev
)paren
op_ne
l_int|0
)paren
suffix:semicolon
)brace
DECL|variable|vmwdt_exit
id|module_exit
c_func
(paren
id|vmwdt_exit
)paren
suffix:semicolon
eof
