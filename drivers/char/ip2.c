singleline_comment|// ip2.c
singleline_comment|// This is a dummy module to make the firmware available when needed
singleline_comment|// and allows it to be unloaded when not. Rumor is the __initdata 
singleline_comment|// macro doesn&squot;t always works on all platforms so we use this kludge.
singleline_comment|// If not compiled as a module it just makes fip_firm avaliable then
singleline_comment|//  __initdata should work as advertized
singleline_comment|//
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#ifndef __init
DECL|macro|__init
mdefine_line|#define __init
macro_line|#endif
macro_line|#ifndef __initfunc
DECL|macro|__initfunc
mdefine_line|#define __initfunc(a) a
macro_line|#endif
macro_line|#ifndef __initdata
DECL|macro|__initdata
mdefine_line|#define __initdata
macro_line|#endif
macro_line|#include &quot;./ip2/ip2types.h&quot;&t;&t;
macro_line|#include &quot;./ip2/fip_firm.h&quot;&t;&t;
singleline_comment|// the meat
r_int
id|ip2_loadmain
c_func
(paren
r_int
op_star
comma
r_int
op_star
comma
r_int
r_char
op_star
comma
r_int
)paren
suffix:semicolon
singleline_comment|// ref into ip2main.c
macro_line|#ifdef MODULE
DECL|variable|io
r_static
r_int
id|io
(braket
id|IP2_MAX_BOARDS
)braket
op_assign
(brace
l_int|0
comma
)brace
suffix:semicolon
DECL|variable|irq
r_static
r_int
id|irq
(braket
id|IP2_MAX_BOARDS
)braket
op_assign
(brace
l_int|0
comma
)brace
suffix:semicolon
macro_line|#&t;if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,1,0)
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Doug McNash&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Computone IntelliPort Plus Driver&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|irq
comma
l_string|&quot;1-&quot;
id|__MODULE_STRING
c_func
(paren
id|IP2_MAX_BOARDS
)paren
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|irq
comma
l_string|&quot;Interrupts for IntelliPort Cards&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|io
comma
l_string|&quot;1-&quot;
id|__MODULE_STRING
c_func
(paren
id|IP2_MAX_BOARDS
)paren
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|io
comma
l_string|&quot;I/O ports for IntelliPort Cards&quot;
)paren
suffix:semicolon
macro_line|#&t;endif&t;/* LINUX_VERSION */
singleline_comment|//======================================================================
r_int
DECL|function|init_module
id|init_module
c_func
(paren
r_void
)paren
(brace
r_int
id|rc
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
singleline_comment|// hold till done 
id|rc
op_assign
id|ip2_loadmain
c_func
(paren
id|io
comma
id|irq
comma
(paren
r_int
r_char
op_star
)paren
id|fip_firm
comma
r_sizeof
(paren
id|fip_firm
)paren
)paren
suffix:semicolon
singleline_comment|// The call to lock and load main, create dep 
id|MOD_DEC_USE_COUNT
suffix:semicolon
singleline_comment|//done - kerneld now can unload us
r_return
id|rc
suffix:semicolon
)brace
singleline_comment|//======================================================================
r_int
DECL|function|ip2_init
id|ip2_init
c_func
(paren
r_void
)paren
(brace
singleline_comment|// call to this is int tty_io.c so we need this
r_return
l_int|0
suffix:semicolon
)brace
singleline_comment|//======================================================================
r_void
DECL|function|cleanup_module
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
)brace
macro_line|#else&t;
singleline_comment|// !MODULE 
macro_line|#ifndef NULL
DECL|macro|NULL
macro_line|# define NULL&t;&t;((void *) 0)
macro_line|#endif
r_int
DECL|function|ip2_init
id|ip2_init
c_func
(paren
r_void
)paren
(brace
r_return
id|ip2_loadmain
c_func
(paren
l_int|NULL
comma
l_int|NULL
comma
(paren
r_int
r_char
op_star
)paren
id|fip_firm
comma
r_sizeof
(paren
id|fip_firm
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif /* !MODULE */
eof
