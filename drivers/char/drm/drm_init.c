multiline_comment|/**&n; * &bslash;file drm_init.h &n; * Setup/Cleanup for DRM&n; *&n; * &bslash;author Rickard E. (Rik) Faith &lt;faith@valinux.com&gt;&n; * &bslash;author Gareth Hughes &lt;gareth@valinux.com&gt;&n; */
multiline_comment|/*&n; * Created: Mon Jan  4 08:58:31 1999 by faith@valinux.com&n; *&n; * Copyright 1999 Precision Insight, Inc., Cedar Park, Texas.&n; * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, California.&n; * All Rights Reserved.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; *&n; * The above copyright notice and this permission notice (including the next&n; * paragraph) shall be included in all copies or substantial portions of the&n; * Software.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR&n; * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * VA LINUX SYSTEMS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR&n; * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,&n; * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR&n; * OTHER DEALINGS IN THE SOFTWARE.&n; */
macro_line|#include &quot;drmP.h&quot;
multiline_comment|/**&n; * Check whether DRI will run on this CPU.&n; *&n; * &bslash;return non-zero if the DRI will run on this CPU, or zero otherwise.&n; */
DECL|function|drm_cpu_valid
r_int
id|drm_cpu_valid
c_func
(paren
r_void
)paren
(brace
macro_line|#if defined(__i386__)
r_if
c_cond
(paren
id|boot_cpu_data.x86
op_eq
l_int|3
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* No cmpxchg on a 386 */
macro_line|#endif
macro_line|#if defined(__sparc__) &amp;&amp; !defined(__sparc_v9__)
r_return
l_int|0
suffix:semicolon
multiline_comment|/* No cmpxchg before v9 sparc. */
macro_line|#endif
r_return
l_int|1
suffix:semicolon
)brace
eof
