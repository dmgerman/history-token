multiline_comment|/*&n; * Suspend support specific for i386.&n; *&n; * Distribute under GPLv2&n; *&n; * Copyright (c) 2002 Pavel Machek &lt;pavel@suse.cz&gt;&n; */
DECL|macro|ACPI_C
mdefine_line|#define ACPI_C
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/sysrq.h&gt;
macro_line|#include &lt;linux/compatmac.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/pm.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/suspend.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/acpi.h&gt;
DECL|function|do_suspend_lowlevel
r_void
id|do_suspend_lowlevel
c_func
(paren
r_int
id|resume
)paren
(brace
multiline_comment|/*&n; * FIXME: This function should really be written in assembly. Actually&n; * requirement is that it does not touch stack, because %esp will be&n; * wrong during resume before restore_processor_context(). Check&n; * assembly if you modify this.&n; */
r_if
c_cond
(paren
op_logical_neg
id|resume
)paren
(brace
id|save_processor_context
c_func
(paren
)paren
suffix:semicolon
id|acpi_save_register_state
c_func
(paren
(paren
r_int
r_int
)paren
op_logical_and
id|acpi_sleep_done
)paren
suffix:semicolon
id|acpi_enter_sleep_state
c_func
(paren
l_int|3
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|acpi_sleep_done
suffix:colon
id|acpi_restore_register_state
c_func
(paren
)paren
suffix:semicolon
id|restore_processor_context
c_func
(paren
)paren
suffix:semicolon
)brace
eof
