multiline_comment|/*&n; * ioctl32.c: Conversion between 32bit and 64bit native ioctls.&n; *&n; * Copyright (C) 2000 Silicon Graphics, Inc.&n; * Written by Ulf Carlsson (ulfc@engr.sgi.com)&n; * Copyright (C) 2000, 2004 Ralf Baechle&n; * Copyright (C) 2002, 2003  Maciej W. Rozycki&n; */
DECL|macro|INCLUDES
mdefine_line|#define INCLUDES
macro_line|#include &quot;compat_ioctl.c&quot;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/compat.h&gt;
macro_line|#include &lt;linux/ioctl32.h&gt;
macro_line|#include &lt;linux/syscalls.h&gt;
macro_line|#ifdef CONFIG_SIBYTE_TBPROF
macro_line|#include &lt;asm/sibyte/trace_prof.h&gt;
macro_line|#endif
DECL|macro|A
mdefine_line|#define A(__x) ((unsigned long)(__x))
r_int
id|sys_ioctl
c_func
(paren
r_int
r_int
id|fd
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
DECL|macro|CODE
mdefine_line|#define CODE
macro_line|#include &quot;compat_ioctl.c&quot;
DECL|typedef|ioctl32_handler_t
r_typedef
r_int
(paren
op_star
id|ioctl32_handler_t
)paren
(paren
r_int
r_int
comma
r_int
r_int
comma
r_int
r_int
comma
r_struct
id|file
op_star
)paren
suffix:semicolon
DECL|macro|COMPATIBLE_IOCTL
mdefine_line|#define COMPATIBLE_IOCTL(cmd)&t;&t;HANDLE_IOCTL((cmd),sys_ioctl)
DECL|macro|HANDLE_IOCTL
mdefine_line|#define HANDLE_IOCTL(cmd,handler)&t;{ (cmd), (ioctl32_handler_t)(handler), NULL },
DECL|macro|IOCTL_TABLE_START
mdefine_line|#define IOCTL_TABLE_START &bslash;&n;&t;struct ioctl_trans ioctl_start[] = {
DECL|macro|IOCTL_TABLE_END
mdefine_line|#define IOCTL_TABLE_END &bslash;&n;&t;};
id|IOCTL_TABLE_START
macro_line|#include &lt;linux/compat_ioctl.h&gt;
DECL|macro|DECLARES
mdefine_line|#define DECLARES
macro_line|#include &quot;compat_ioctl.c&quot;
macro_line|#ifdef CONFIG_SIBYTE_TBPROF
id|COMPATIBLE_IOCTL
c_func
(paren
id|SBPROF_ZBSTART
)paren
id|COMPATIBLE_IOCTL
c_func
(paren
id|SBPROF_ZBSTOP
)paren
id|COMPATIBLE_IOCTL
c_func
(paren
id|SBPROF_ZBWAITFULL
)paren
macro_line|#endif /* CONFIG_SIBYTE_TBPROF */
multiline_comment|/*HANDLE_IOCTL(RTC_IRQP_READ, w_long)&n;COMPATIBLE_IOCTL(RTC_IRQP_SET)&n;HANDLE_IOCTL(RTC_EPOCH_READ, w_long)&n;COMPATIBLE_IOCTL(RTC_EPOCH_SET)&n;*/
id|IOCTL_TABLE_END
r_int
id|ioctl_table_size
op_assign
id|ARRAY_SIZE
c_func
(paren
id|ioctl_start
)paren
suffix:semicolon
eof
