multiline_comment|/*&n; *  drivers/s390/cio/requestirq.c&n; *   S/390 common I/O routines -- enabling and disabling of devices&n; *   $Revision: 1.46 $&n; *&n; *    Copyright (C) 1999-2002 IBM Deutschland Entwicklung GmbH,&n; *&t;&t;&t;      IBM Corporation&n; *    Author(s): Ingo Adlung (adlung@de.ibm.com)&n; *&t;&t; Cornelia Huck (cohuck@de.ibm.com)&n; *&t;&t; Arnd Bergmann (arndb@de.ibm.com)&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/lowcore.h&gt;
macro_line|#include &quot;css.h&quot;
DECL|variable|global_pgid
r_struct
id|pgid
id|global_pgid
suffix:semicolon
DECL|variable|global_pgid
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|global_pgid
)paren
suffix:semicolon
multiline_comment|/*&n; * init_IRQ is now only used to set the pgid as early as possible&n; */
r_void
id|__init
DECL|function|init_IRQ
id|init_IRQ
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n;&t; * Let&squot;s build our path group ID here.&n;&t; */
r_if
c_cond
(paren
id|MACHINE_NEW_STIDP
)paren
id|global_pgid.cpu_addr
op_assign
l_int|0x8000
suffix:semicolon
r_else
(brace
macro_line|#ifdef CONFIG_SMP
id|global_pgid.cpu_addr
op_assign
id|hard_smp_processor_id
c_func
(paren
)paren
suffix:semicolon
macro_line|#else
id|global_pgid.cpu_addr
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
)brace
id|global_pgid.cpu_id
op_assign
(paren
(paren
id|cpuid_t
op_star
)paren
id|__LC_CPUID
)paren
op_member_access_from_pointer
id|ident
suffix:semicolon
id|global_pgid.cpu_model
op_assign
(paren
(paren
id|cpuid_t
op_star
)paren
id|__LC_CPUID
)paren
op_member_access_from_pointer
id|machine
suffix:semicolon
id|global_pgid.tod_high
op_assign
(paren
id|__u32
)paren
(paren
id|get_clock
c_func
(paren
)paren
op_rshift
l_int|32
)paren
suffix:semicolon
)brace
eof
