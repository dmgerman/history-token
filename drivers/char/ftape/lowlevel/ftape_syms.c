multiline_comment|/*&n; *      Copyright (C) 1996-1997 Claus-Justus Heine&n;&n; This program is free software; you can redistribute it and/or modify&n; it under the terms of the GNU General Public License as published by&n; the Free Software Foundation; either version 2, or (at your option)&n; any later version.&n;&n; This program is distributed in the hope that it will be useful,&n; but WITHOUT ANY WARRANTY; without even the implied warranty of&n; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; GNU General Public License for more details.&n;&n; You should have received a copy of the GNU General Public License&n; along with this program; see the file COPYING.  If not, write to&n; the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n; *&n; * $Source: /homes/cvs/ftape-stacked/ftape/lowlevel/ftape_syms.c,v $&n; * $Revision: 1.4 $&n; * $Date: 1997/10/17 00:03:51 $&n; *&n; *      This file contains the symbols that the ftape low level&n; *      part of the QIC-40/80/3010/3020 floppy-tape driver &quot;ftape&quot;&n; *      exports to it&squot;s high level clients&n; */
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/ftape.h&gt;
macro_line|#include &quot;../lowlevel/ftape-tracing.h&quot;
macro_line|#include &quot;../lowlevel/ftape-init.h&quot;
macro_line|#include &quot;../lowlevel/fdc-io.h&quot;
macro_line|#include &quot;../lowlevel/ftape-read.h&quot;
macro_line|#include &quot;../lowlevel/ftape-write.h&quot;
macro_line|#include &quot;../lowlevel/ftape-io.h&quot;
macro_line|#include &quot;../lowlevel/ftape-ctl.h&quot;
macro_line|#include &quot;../lowlevel/ftape-rw.h&quot;
macro_line|#include &quot;../lowlevel/ftape-bsm.h&quot;
macro_line|#include &quot;../lowlevel/ftape-buffer.h&quot;
macro_line|#include &quot;../lowlevel/ftape-format.h&quot;
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VER(2,1,18)
DECL|macro|FT_KSYM
macro_line|# define FT_KSYM(sym) EXPORT_SYMBOL(sym);
macro_line|#else
DECL|macro|FT_KSYM
macro_line|# define FT_KSYM(sym) X(sym),
macro_line|#endif
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VER(2,1,18)
DECL|variable|ftape_symbol_table
r_struct
id|symbol_table
id|ftape_symbol_table
op_assign
(brace
macro_line|#include &lt;linux/symtab_begin.h&gt;
macro_line|#endif
multiline_comment|/* bad sector handling from ftape-bsm.c */
id|FT_KSYM
c_func
(paren
id|ftape_get_bad_sector_entry
)paren
id|FT_KSYM
c_func
(paren
id|ftape_find_end_of_bsm_list
)paren
multiline_comment|/* from ftape-rw.c */
id|FT_KSYM
c_func
(paren
id|ftape_set_state
)paren
multiline_comment|/* from ftape-ctl.c */
id|FT_KSYM
c_func
(paren
id|ftape_seek_to_bot
)paren
id|FT_KSYM
c_func
(paren
id|ftape_seek_to_eot
)paren
id|FT_KSYM
c_func
(paren
id|ftape_abort_operation
)paren
id|FT_KSYM
c_func
(paren
id|ftape_get_status
)paren
id|FT_KSYM
c_func
(paren
id|ftape_enable
)paren
id|FT_KSYM
c_func
(paren
id|ftape_disable
)paren
id|FT_KSYM
c_func
(paren
id|ftape_mmap
)paren
id|FT_KSYM
c_func
(paren
id|ftape_calibrate_data_rate
)paren
multiline_comment|/* from ftape-io.c */
id|FT_KSYM
c_func
(paren
id|ftape_reset_drive
)paren
id|FT_KSYM
c_func
(paren
id|ftape_command
)paren
id|FT_KSYM
c_func
(paren
id|ftape_parameter
)paren
id|FT_KSYM
c_func
(paren
id|ftape_ready_wait
)paren
id|FT_KSYM
c_func
(paren
id|ftape_report_operation
)paren
id|FT_KSYM
c_func
(paren
id|ftape_report_error
)paren
multiline_comment|/* from ftape-read.c */
id|FT_KSYM
c_func
(paren
id|ftape_read_segment_fraction
)paren
id|FT_KSYM
c_func
(paren
id|ftape_zap_read_buffers
)paren
id|FT_KSYM
c_func
(paren
id|ftape_read_header_segment
)paren
id|FT_KSYM
c_func
(paren
id|ftape_decode_header_segment
)paren
multiline_comment|/* from ftape-write.c */
id|FT_KSYM
c_func
(paren
id|ftape_write_segment
)paren
id|FT_KSYM
c_func
(paren
id|ftape_start_writing
)paren
id|FT_KSYM
c_func
(paren
id|ftape_loop_until_writes_done
)paren
multiline_comment|/* from ftape-buffer.h */
id|FT_KSYM
c_func
(paren
id|ftape_set_nr_buffers
)paren
multiline_comment|/* from ftape-format.h */
id|FT_KSYM
c_func
(paren
id|ftape_format_track
)paren
id|FT_KSYM
c_func
(paren
id|ftape_format_status
)paren
id|FT_KSYM
c_func
(paren
id|ftape_verify_segment
)paren
multiline_comment|/* from tracing.c */
macro_line|#ifndef CONFIG_FT_NO_TRACE_AT_ALL
id|FT_KSYM
c_func
(paren
id|ftape_tracing
)paren
id|FT_KSYM
c_func
(paren
id|ftape_function_nest_level
)paren
id|FT_KSYM
c_func
(paren
id|ftape_trace_call
)paren
id|FT_KSYM
c_func
(paren
id|ftape_trace_exit
)paren
id|FT_KSYM
c_func
(paren
id|ftape_trace_log
)paren
macro_line|#endif
multiline_comment|/* end of ksym table */
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VER(2,1,18)
macro_line|#include &lt;linux/symtab_end.h&gt;
)brace
suffix:semicolon
macro_line|#endif
eof
