multiline_comment|/*&n; * Copyright (c) 2004 Topspin Communications.  All rights reserved.&n; *&n; * This software is available to you under a choice of one of two&n; * licenses.  You may choose to be licensed under the terms of the GNU&n; * General Public License (GPL) Version 2, available from the file&n; * COPYING in the main directory of this source tree, or the&n; * OpenIB.org BSD license below:&n; *&n; *     Redistribution and use in source and binary forms, with or&n; *     without modification, are permitted provided that the following&n; *     conditions are met:&n; *&n; *      - Redistributions of source code must retain the above&n; *        copyright notice, this list of conditions and the following&n; *        disclaimer.&n; *&n; *      - Redistributions in binary form must reproduce the above&n; *        copyright notice, this list of conditions and the following&n; *        disclaimer in the documentation and/or other materials&n; *        provided with the distribution.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND,&n; * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF&n; * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND&n; * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS&n; * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN&n; * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN&n; * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE&n; * SOFTWARE.&n; *&n; * $Id: core_priv.h 1349 2004-12-16 21:09:43Z roland $&n; */
macro_line|#ifndef _CORE_PRIV_H
DECL|macro|_CORE_PRIV_H
mdefine_line|#define _CORE_PRIV_H
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;ib_verbs.h&gt;
r_int
id|ib_device_register_sysfs
c_func
(paren
r_struct
id|ib_device
op_star
id|device
)paren
suffix:semicolon
r_void
id|ib_device_unregister_sysfs
c_func
(paren
r_struct
id|ib_device
op_star
id|device
)paren
suffix:semicolon
r_int
id|ib_sysfs_setup
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|ib_sysfs_cleanup
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|ib_cache_setup
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|ib_cache_cleanup
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* _CORE_PRIV_H */
eof
