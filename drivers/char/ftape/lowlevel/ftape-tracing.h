macro_line|#ifndef _FTAPE_TRACING_H
DECL|macro|_FTAPE_TRACING_H
mdefine_line|#define _FTAPE_TRACING_H
multiline_comment|/*&n; * Copyright (C) 1994-1996 Bas Laarhoven,&n; *           (C) 1996-1997 Claus-Justus Heine.&n;&n; This program is free software; you can redistribute it and/or modify&n; it under the terms of the GNU General Public License as published by&n; the Free Software Foundation; either version 2, or (at your option)&n; any later version.&n;&n; This program is distributed in the hope that it will be useful,&n; but WITHOUT ANY WARRANTY; without even the implied warranty of&n; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; GNU General Public License for more details.&n;&n; You should have received a copy of the GNU General Public License&n; along with this program; see the file COPYING.  If not, write to&n; the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n; *&n; * $Source: /homes/cvs/ftape-stacked/ftape/lowlevel/ftape-tracing.h,v $&n; * $Revision: 1.2 $&n; * $Date: 1997/10/05 19:18:28 $&n; *&n; *      This file contains definitions that eases the debugging of the&n; *      QIC-40/80/3010/3020 floppy-tape driver &quot;ftape&quot; for Linux.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
multiline_comment|/*&n; *  Be very careful with TRACE_EXIT and TRACE_ABORT.&n; *&n; *  if (something) TRACE_EXIT error;&n; *&n; *  will NOT work. Use&n; *&n; *  if (something) {&n; *    TRACE_EXIT error;&n; *  }&n; *&n; *  instead. Maybe a bit dangerous, but save lots of lines of code.&n; */
DECL|macro|LL_X
mdefine_line|#define LL_X &quot;%d/%d KB&quot;
DECL|macro|LL
mdefine_line|#define LL(x) (unsigned int)((__u64)(x)&gt;&gt;10), (unsigned int)((x)&amp;1023)
r_typedef
r_enum
(brace
DECL|enumerator|ft_t_nil
id|ft_t_nil
op_assign
op_minus
l_int|1
comma
DECL|enumerator|ft_t_bug
id|ft_t_bug
comma
DECL|enumerator|ft_t_err
id|ft_t_err
comma
DECL|enumerator|ft_t_warn
id|ft_t_warn
comma
DECL|enumerator|ft_t_info
id|ft_t_info
comma
DECL|enumerator|ft_t_noise
id|ft_t_noise
comma
DECL|enumerator|ft_t_flow
id|ft_t_flow
comma
DECL|enumerator|ft_t_fdc_dma
id|ft_t_fdc_dma
comma
DECL|enumerator|ft_t_data_flow
id|ft_t_data_flow
comma
DECL|enumerator|ft_t_any
id|ft_t_any
DECL|typedef|ft_trace_t
)brace
id|ft_trace_t
suffix:semicolon
macro_line|#ifdef  CONFIG_FT_NO_TRACE_AT_ALL
multiline_comment|/*  the compiler will optimize away most TRACE() macros&n; */
DECL|macro|FT_TRACE_TOP_LEVEL
mdefine_line|#define FT_TRACE_TOP_LEVEL&t;ft_t_bug
DECL|macro|TRACE_FUN
mdefine_line|#define TRACE_FUN(level)&t;do {} while(0)
DECL|macro|TRACE_EXIT
mdefine_line|#define TRACE_EXIT&t;&t;return
DECL|macro|TRACE
mdefine_line|#define TRACE(l, m, i...)&t;&t;&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if ((ft_trace_t)(l) == FT_TRACE_TOP_LEVEL) {&t;&t;&t;&bslash;&n;&t;&t;printk(KERN_INFO&quot;ftape&quot;__FILE__&quot;(&quot;__FUNCTION__&quot;):&bslash;n&quot;&t;&bslash;&n;&t;&t;       KERN_INFO m&quot;.&bslash;n&quot; ,##i);&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;}
DECL|macro|SET_TRACE_LEVEL
mdefine_line|#define SET_TRACE_LEVEL(l)      if ((l) == (l)) do {} while(0)
DECL|macro|TRACE_LEVEL
mdefine_line|#define TRACE_LEVEL&t;&t;FT_TRACE_TOP_LEVEL
macro_line|#else
macro_line|#ifdef CONFIG_FT_NO_TRACE
multiline_comment|/*  the compiler will optimize away many TRACE() macros&n; *  the ftape_simple_trace_call() function simply increments &n; *  the function nest level.&n; */
DECL|macro|FT_TRACE_TOP_LEVEL
mdefine_line|#define FT_TRACE_TOP_LEVEL&t;ft_t_warn
DECL|macro|TRACE_FUN
mdefine_line|#define TRACE_FUN(level)&t;ftape_function_nest_level++
DECL|macro|TRACE_EXIT
mdefine_line|#define TRACE_EXIT&t;&t;ftape_function_nest_level--; return
macro_line|#else
macro_line|#ifdef CONFIG_FT_FULL_DEBUG
DECL|macro|FT_TRACE_TOP_LEVEL
mdefine_line|#define FT_TRACE_TOP_LEVEL ft_t_any
macro_line|#else
DECL|macro|FT_TRACE_TOP_LEVEL
mdefine_line|#define FT_TRACE_TOP_LEVEL ft_t_flow
macro_line|#endif
DECL|macro|TRACE_FUN
mdefine_line|#define TRACE_FUN(level)&t;&t;&t;&t;&t;&bslash;&n;&t;const ft_trace_t _tracing = level;&t;&t;&t;&bslash;&n;&t;if (ftape_tracing &gt;= (ft_trace_t)(level) &amp;&amp;&t;&t;&bslash;&n;&t;    (ft_trace_t)(level) &lt;= FT_TRACE_TOP_LEVEL)&t;&t;&bslash;&n;&t;&t;ftape_trace_call(__FILE__, __FUNCTION__);&t;&bslash;&n;&t;ftape_function_nest_level ++;
DECL|macro|TRACE_EXIT
mdefine_line|#define TRACE_EXIT&t;&t;&t;&t;&t;&t;&bslash;&n;&t;--ftape_function_nest_level;&t;&t;&t;&t;&bslash;&n;&t;if (ftape_tracing &gt;= (ft_trace_t)(_tracing) &amp;&amp;&t;&t;&bslash;&n;&t;    (ft_trace_t)(_tracing) &lt;= FT_TRACE_TOP_LEVEL)&t;&bslash;&n;&t;&t;ftape_trace_exit(__FILE__, __FUNCTION__);&t;&bslash;&n;&t;return
macro_line|#endif
DECL|macro|TRACE
mdefine_line|#define TRACE(l, m, i...)&t;&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (ftape_tracing &gt;= (ft_trace_t)(l) &amp;&amp;&t;&t;&t;&bslash;&n;&t;    (ft_trace_t)(l) &lt;= FT_TRACE_TOP_LEVEL) {&t;&t;&bslash;&n;&t;&t;ftape_trace_log(__FILE__, __FUNCTION__);&t;&bslash;&n;&t;&t;printk(m&quot;.&bslash;n&quot; ,##i);&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&bslash;&n;}
DECL|macro|SET_TRACE_LEVEL
mdefine_line|#define SET_TRACE_LEVEL(l) &t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if ((ft_trace_t)(l) &lt;= FT_TRACE_TOP_LEVEL) {&t;&bslash;&n;&t;&t;ftape_tracing = (ft_trace_t)(l);&t;&bslash;&n;&t;} else {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;ftape_tracing = FT_TRACE_TOP_LEVEL;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&bslash;&n;}
DECL|macro|TRACE_LEVEL
mdefine_line|#define TRACE_LEVEL    &t;&t;&t;&t;&t;&t;&t;     &bslash;&n;((ftape_tracing &lt;= FT_TRACE_TOP_LEVEL) ? ftape_tracing : FT_TRACE_TOP_LEVEL)
multiline_comment|/*      Global variables declared in tracing.c&n; */
r_extern
id|ft_trace_t
id|ftape_tracing
suffix:semicolon
multiline_comment|/* sets default level */
r_extern
r_int
id|ftape_function_nest_level
suffix:semicolon
multiline_comment|/*      Global functions declared in tracing.c&n; */
r_extern
r_void
id|ftape_trace_call
c_func
(paren
r_const
r_char
op_star
id|file
comma
r_const
r_char
op_star
id|name
)paren
suffix:semicolon
r_extern
r_void
id|ftape_trace_exit
c_func
(paren
r_const
r_char
op_star
id|file
comma
r_const
r_char
op_star
id|name
)paren
suffix:semicolon
r_extern
r_void
id|ftape_trace_log
(paren
r_const
r_char
op_star
id|file
comma
r_const
r_char
op_star
id|name
)paren
suffix:semicolon
macro_line|#endif /* !defined(CONFIG_FT_NO_TRACE_AT_ALL) */
multiline_comment|/*&n; *   Abort with a message.&n; */
DECL|macro|TRACE_ABORT
mdefine_line|#define TRACE_ABORT(res, i...)&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&bslash;&n; &t;TRACE(i);&t;&t;&t;&t;&bslash;&n;&t;TRACE_EXIT res;&t;&t;&t;&t;&bslash;&n;}
multiline_comment|/*   The following transforms the common &quot;if(result &lt; 0) ... &quot; into a&n; *   one-liner.&n; */
DECL|macro|_TRACE_CATCH
mdefine_line|#define _TRACE_CATCH(level, fun, action)&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;int _res = (fun);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (_res &lt; 0) {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;do { action /* */ ; } while(0);&t;&t;&t;&t;&bslash;&n;&t;&t;TRACE_ABORT(_res, level, &quot;%s failed: %d&quot;, #fun,&t;_res);&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;}
DECL|macro|TRACE_CATCH
mdefine_line|#define TRACE_CATCH(fun, fail) _TRACE_CATCH(ft_t_err, fun, fail)
multiline_comment|/*  Abort the current function when signalled. This doesn&squot;t belong here,&n; *  but rather into ftape-rw.h (maybe)&n; */
DECL|macro|FT_SIGNAL_EXIT
mdefine_line|#define FT_SIGNAL_EXIT(sig_mask)&t;&t;&t;&t;&t;&bslash;&n;&t;if (sigtestsetmask(&amp;current-&gt;pending.signal, sig_mask)) {&t;&bslash;&n;&t;&t;TRACE_ABORT(-EINTR,&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;    ft_t_warn,&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;    &quot;interrupted by non-blockable signal&quot;);&t;&bslash;&n;&t;}
macro_line|#endif /* _FTAPE_TRACING_H */
eof
