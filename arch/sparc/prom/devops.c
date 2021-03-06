multiline_comment|/* $Id: devops.c,v 1.13 2000/08/26 02:38:03 anton Exp $&n; * devops.c:  Device operations using the PROM.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/openprom.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
r_extern
r_void
id|restore_current
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Open the device described by the string &squot;dstr&squot;.  Returns the handle&n; * to that device used for subsequent operations on that device.&n; * Returns -1 on failure.&n; */
r_int
DECL|function|prom_devopen
id|prom_devopen
c_func
(paren
r_char
op_star
id|dstr
)paren
(brace
r_int
id|handle
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|prom_lock
comma
id|flags
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|prom_vers
)paren
(brace
r_case
id|PROM_V0
suffix:colon
id|handle
op_assign
(paren
op_star
(paren
id|romvec-&gt;pv_v0devops.v0_devopen
)paren
)paren
(paren
id|dstr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|handle
op_eq
l_int|0
)paren
(brace
id|handle
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|PROM_V2
suffix:colon
r_case
id|PROM_V3
suffix:colon
id|handle
op_assign
(paren
op_star
(paren
id|romvec-&gt;pv_v2devops.v2_dev_open
)paren
)paren
(paren
id|dstr
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|handle
op_assign
op_minus
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
suffix:semicolon
id|restore_current
c_func
(paren
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|prom_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|handle
suffix:semicolon
)brace
multiline_comment|/* Close the device described by device handle &squot;dhandle&squot;. */
r_int
DECL|function|prom_devclose
id|prom_devclose
c_func
(paren
r_int
id|dhandle
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|prom_lock
comma
id|flags
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|prom_vers
)paren
(brace
r_case
id|PROM_V0
suffix:colon
(paren
op_star
(paren
id|romvec-&gt;pv_v0devops.v0_devclose
)paren
)paren
(paren
id|dhandle
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PROM_V2
suffix:colon
r_case
id|PROM_V3
suffix:colon
(paren
op_star
(paren
id|romvec-&gt;pv_v2devops.v2_dev_close
)paren
)paren
(paren
id|dhandle
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
suffix:semicolon
id|restore_current
c_func
(paren
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|prom_lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Seek to specified location described by &squot;seekhi&squot; and &squot;seeklo&squot;&n; * for device &squot;dhandle&squot;.&n; */
r_void
DECL|function|prom_seek
id|prom_seek
c_func
(paren
r_int
id|dhandle
comma
r_int
r_int
id|seekhi
comma
r_int
r_int
id|seeklo
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|prom_lock
comma
id|flags
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|prom_vers
)paren
(brace
r_case
id|PROM_V0
suffix:colon
(paren
op_star
(paren
id|romvec-&gt;pv_v0devops.v0_seekdev
)paren
)paren
(paren
id|dhandle
comma
id|seekhi
comma
id|seeklo
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PROM_V2
suffix:colon
r_case
id|PROM_V3
suffix:colon
(paren
op_star
(paren
id|romvec-&gt;pv_v2devops.v2_dev_seek
)paren
)paren
(paren
id|dhandle
comma
id|seekhi
comma
id|seeklo
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
suffix:semicolon
id|restore_current
c_func
(paren
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|prom_lock
comma
id|flags
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
eof
