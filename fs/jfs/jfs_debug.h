multiline_comment|/*&n; *   Copyright (c) International Business Machines Corp., 2000-2002&n; *   Portions Copyright (c) Christoph Hellwig, 2001-2002&n; *&n; *   This program is free software;  you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY;  without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See&n; *   the GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program;  if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; */
macro_line|#ifndef _H_JFS_DEBUG
DECL|macro|_H_JFS_DEBUG
mdefine_line|#define _H_JFS_DEBUG
multiline_comment|/*&n; *&t;jfs_debug.h&n; *&n; * global debug message, data structure/macro definitions&n; * under control of CONFIG_JFS_DEBUG, CONFIG_JFS_STATISTICS;&n; */
multiline_comment|/*&n; *&t;assert with traditional printf/panic&n; */
macro_line|#ifdef CONFIG_KERNEL_ASSERTS
multiline_comment|/* kgdb stuff */
DECL|macro|assert
mdefine_line|#define assert(p) KERNEL_ASSERT(#p, p)
macro_line|#else
DECL|macro|assert
mdefine_line|#define assert(p) {&bslash;&n;if (!(p))&bslash;&n;&t;{&bslash;&n;&t;&t;printk(&quot;assert(%s)&bslash;n&quot;,#p);&bslash;&n;&t;&t;BUG();&bslash;&n;&t;}&bslash;&n;}
macro_line|#endif
multiline_comment|/*&n; *&t;debug ON&n; *&t;--------&n; */
macro_line|#ifdef CONFIG_JFS_DEBUG
DECL|macro|ASSERT
mdefine_line|#define ASSERT(p) assert(p)
multiline_comment|/* dump memory contents */
r_extern
r_void
id|dump_mem
c_func
(paren
r_char
op_star
id|label
comma
r_void
op_star
id|data
comma
r_int
id|length
)paren
suffix:semicolon
r_extern
r_int
id|jfsloglevel
suffix:semicolon
multiline_comment|/* information message: e.g., configuration, major event */
DECL|macro|jFYI
mdefine_line|#define jFYI(button, prspec) &bslash;&n;&t;do { if (button &amp;&amp; jfsloglevel &gt; 1) printk prspec; } while (0)
multiline_comment|/* error event message: e.g., i/o error */
r_extern
r_int
id|jfsERROR
suffix:semicolon
DECL|macro|jERROR
mdefine_line|#define jERROR(button, prspec) &bslash;&n;&t;do { if (button &amp;&amp; jfsloglevel &gt; 0) { printk prspec; } } while (0)
multiline_comment|/* debug event message: */
DECL|macro|jEVENT
mdefine_line|#define jEVENT(button,prspec) &bslash;&n;&t;do { if (button) printk prspec; } while (0)
multiline_comment|/*&n; *&t;debug OFF&n; *&t;---------&n; */
macro_line|#else&t;&t;&t;&t;/* CONFIG_JFS_DEBUG */
DECL|macro|dump_mem
mdefine_line|#define dump_mem(label,data,length)
DECL|macro|ASSERT
mdefine_line|#define ASSERT(p)
DECL|macro|jEVENT
mdefine_line|#define jEVENT(button,prspec)
DECL|macro|jERROR
mdefine_line|#define jERROR(button,prspec)
DECL|macro|jFYI
mdefine_line|#define jFYI(button,prspec)
macro_line|#endif&t;&t;&t;&t;/* CONFIG_JFS_DEBUG */
multiline_comment|/*&n; *&t;statistics&n; *&t;----------&n; */
macro_line|#ifdef&t;CONFIG_JFS_STATISTICS
DECL|macro|INCREMENT
mdefine_line|#define&t;INCREMENT(x)&t;&t;((x)++)
DECL|macro|DECREMENT
mdefine_line|#define&t;DECREMENT(x)&t;&t;((x)--)
DECL|macro|HIGHWATERMARK
mdefine_line|#define&t;HIGHWATERMARK(x,y)&t;((x) = max((x), (y)))
macro_line|#else
DECL|macro|INCREMENT
mdefine_line|#define&t;INCREMENT(x)
DECL|macro|DECREMENT
mdefine_line|#define&t;DECREMENT(x)
DECL|macro|HIGHWATERMARK
mdefine_line|#define&t;HIGHWATERMARK(x,y)
macro_line|#endif&t;&t;&t;&t;/* CONFIG_JFS_STATISTICS */
macro_line|#endif&t;&t;&t;&t;/* _H_JFS_DEBUG */
eof
