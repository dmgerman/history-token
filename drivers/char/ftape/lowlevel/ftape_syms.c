multiline_comment|/*&n; *      Copyright (C) 1996-1997 Claus-Justus Heine&n;&n; This program is free software; you can redistribute it and/or modify&n; it under the terms of the GNU General Public License as published by&n; the Free Software Foundation; either version 2, or (at your option)&n; any later version.&n;&n; This program is distributed in the hope that it will be useful,&n; but WITHOUT ANY WARRANTY; without even the implied warranty of&n; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; GNU General Public License for more details.&n;&n; You should have received a copy of the GNU General Public License&n; along with this program; see the file COPYING.  If not, write to&n; the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n; *&n; * $Source: /homes/cvs/ftape-stacked/ftape/lowlevel/ftape_syms.c,v $&n; * $Revision: 1.4 $&n; * $Date: 1997/10/17 00:03:51 $&n; *&n; *      This file contains the symbols that the ftape low level&n; *      part of the QIC-40/80/3010/3020 floppy-tape driver &quot;ftape&quot;&n; *      exports to its high level clients&n; */
macro_line|#include &lt;linux/config.h&gt;
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
multiline_comment|/* bad sector handling from ftape-bsm.c */
DECL|variable|ftape_get_bad_sector_entry
id|EXPORT_SYMBOL
c_func
(paren
id|ftape_get_bad_sector_entry
)paren
suffix:semicolon
DECL|variable|ftape_find_end_of_bsm_list
id|EXPORT_SYMBOL
c_func
(paren
id|ftape_find_end_of_bsm_list
)paren
suffix:semicolon
multiline_comment|/* from ftape-rw.c */
DECL|variable|ftape_set_state
id|EXPORT_SYMBOL
c_func
(paren
id|ftape_set_state
)paren
suffix:semicolon
multiline_comment|/* from ftape-ctl.c */
DECL|variable|ftape_seek_to_bot
id|EXPORT_SYMBOL
c_func
(paren
id|ftape_seek_to_bot
)paren
suffix:semicolon
DECL|variable|ftape_seek_to_eot
id|EXPORT_SYMBOL
c_func
(paren
id|ftape_seek_to_eot
)paren
suffix:semicolon
DECL|variable|ftape_abort_operation
id|EXPORT_SYMBOL
c_func
(paren
id|ftape_abort_operation
)paren
suffix:semicolon
DECL|variable|ftape_get_status
id|EXPORT_SYMBOL
c_func
(paren
id|ftape_get_status
)paren
suffix:semicolon
DECL|variable|ftape_enable
id|EXPORT_SYMBOL
c_func
(paren
id|ftape_enable
)paren
suffix:semicolon
DECL|variable|ftape_disable
id|EXPORT_SYMBOL
c_func
(paren
id|ftape_disable
)paren
suffix:semicolon
DECL|variable|ftape_mmap
id|EXPORT_SYMBOL
c_func
(paren
id|ftape_mmap
)paren
suffix:semicolon
DECL|variable|ftape_calibrate_data_rate
id|EXPORT_SYMBOL
c_func
(paren
id|ftape_calibrate_data_rate
)paren
suffix:semicolon
multiline_comment|/* from ftape-io.c */
DECL|variable|ftape_reset_drive
id|EXPORT_SYMBOL
c_func
(paren
id|ftape_reset_drive
)paren
suffix:semicolon
DECL|variable|ftape_command
id|EXPORT_SYMBOL
c_func
(paren
id|ftape_command
)paren
suffix:semicolon
DECL|variable|ftape_parameter
id|EXPORT_SYMBOL
c_func
(paren
id|ftape_parameter
)paren
suffix:semicolon
DECL|variable|ftape_ready_wait
id|EXPORT_SYMBOL
c_func
(paren
id|ftape_ready_wait
)paren
suffix:semicolon
DECL|variable|ftape_report_operation
id|EXPORT_SYMBOL
c_func
(paren
id|ftape_report_operation
)paren
suffix:semicolon
DECL|variable|ftape_report_error
id|EXPORT_SYMBOL
c_func
(paren
id|ftape_report_error
)paren
suffix:semicolon
multiline_comment|/* from ftape-read.c */
DECL|variable|ftape_read_segment_fraction
id|EXPORT_SYMBOL
c_func
(paren
id|ftape_read_segment_fraction
)paren
suffix:semicolon
DECL|variable|ftape_zap_read_buffers
id|EXPORT_SYMBOL
c_func
(paren
id|ftape_zap_read_buffers
)paren
suffix:semicolon
DECL|variable|ftape_read_header_segment
id|EXPORT_SYMBOL
c_func
(paren
id|ftape_read_header_segment
)paren
suffix:semicolon
DECL|variable|ftape_decode_header_segment
id|EXPORT_SYMBOL
c_func
(paren
id|ftape_decode_header_segment
)paren
suffix:semicolon
multiline_comment|/* from ftape-write.c */
DECL|variable|ftape_write_segment
id|EXPORT_SYMBOL
c_func
(paren
id|ftape_write_segment
)paren
suffix:semicolon
DECL|variable|ftape_start_writing
id|EXPORT_SYMBOL
c_func
(paren
id|ftape_start_writing
)paren
suffix:semicolon
DECL|variable|ftape_loop_until_writes_done
id|EXPORT_SYMBOL
c_func
(paren
id|ftape_loop_until_writes_done
)paren
suffix:semicolon
multiline_comment|/* from ftape-buffer.h */
DECL|variable|ftape_set_nr_buffers
id|EXPORT_SYMBOL
c_func
(paren
id|ftape_set_nr_buffers
)paren
suffix:semicolon
multiline_comment|/* from ftape-format.h */
DECL|variable|ftape_format_track
id|EXPORT_SYMBOL
c_func
(paren
id|ftape_format_track
)paren
suffix:semicolon
DECL|variable|ftape_format_status
id|EXPORT_SYMBOL
c_func
(paren
id|ftape_format_status
)paren
suffix:semicolon
DECL|variable|ftape_verify_segment
id|EXPORT_SYMBOL
c_func
(paren
id|ftape_verify_segment
)paren
suffix:semicolon
multiline_comment|/* from tracing.c */
macro_line|#ifndef CONFIG_FT_NO_TRACE_AT_ALL
DECL|variable|ftape_tracing
id|EXPORT_SYMBOL
c_func
(paren
id|ftape_tracing
)paren
suffix:semicolon
DECL|variable|ftape_function_nest_level
id|EXPORT_SYMBOL
c_func
(paren
id|ftape_function_nest_level
)paren
suffix:semicolon
DECL|variable|ftape_trace_call
id|EXPORT_SYMBOL
c_func
(paren
id|ftape_trace_call
)paren
suffix:semicolon
DECL|variable|ftape_trace_exit
id|EXPORT_SYMBOL
c_func
(paren
id|ftape_trace_exit
)paren
suffix:semicolon
DECL|variable|ftape_trace_log
id|EXPORT_SYMBOL
c_func
(paren
id|ftape_trace_log
)paren
suffix:semicolon
macro_line|#endif
eof
