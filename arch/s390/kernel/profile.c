multiline_comment|/*&n; * arch/s390/kernel/profile.c&n; *&n; * Copyright (C) 2003 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; * Author(s): Thomas Spatzier (tspat@de.ibm.com)&n; *&n; */
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/profile.h&gt;
DECL|variable|root_irq_dir
r_static
r_struct
id|proc_dir_entry
op_star
id|root_irq_dir
suffix:semicolon
DECL|function|init_irq_proc
r_void
id|init_irq_proc
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* create /proc/irq */
id|root_irq_dir
op_assign
id|proc_mkdir
c_func
(paren
l_string|&quot;irq&quot;
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* create /proc/irq/prof_cpu_mask */
id|create_prof_cpu_mask
c_func
(paren
id|root_irq_dir
)paren
suffix:semicolon
)brace
eof
