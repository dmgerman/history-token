multiline_comment|/*&n; *&n; * linux/drivers/s390/net/ctcdbug.h ($Revision: 1.4 $)&n; *&n; * CTC / ESCON network driver - s390 dbf exploit.&n; *&n; * Copyright 2000,2003 IBM Corporation&n; *&n; *    Author(s): Original Code written by&n; *&t;&t;&t;  Peter Tiedemann (ptiedem@de.ibm.com)&n; *&n; *    $Revision: 1.4 $&t; $Date: 2004/10/15 09:26:58 $&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&t; See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;asm/debug.h&gt;
multiline_comment|/**&n; * Debug Facility stuff&n; */
DECL|macro|CTC_DBF_SETUP_NAME
mdefine_line|#define CTC_DBF_SETUP_NAME &quot;ctc_setup&quot;
DECL|macro|CTC_DBF_SETUP_LEN
mdefine_line|#define CTC_DBF_SETUP_LEN 16
DECL|macro|CTC_DBF_SETUP_INDEX
mdefine_line|#define CTC_DBF_SETUP_INDEX 3
DECL|macro|CTC_DBF_SETUP_NR_AREAS
mdefine_line|#define CTC_DBF_SETUP_NR_AREAS 1
DECL|macro|CTC_DBF_SETUP_LEVEL
mdefine_line|#define CTC_DBF_SETUP_LEVEL 3
DECL|macro|CTC_DBF_DATA_NAME
mdefine_line|#define CTC_DBF_DATA_NAME &quot;ctc_data&quot;
DECL|macro|CTC_DBF_DATA_LEN
mdefine_line|#define CTC_DBF_DATA_LEN 128
DECL|macro|CTC_DBF_DATA_INDEX
mdefine_line|#define CTC_DBF_DATA_INDEX 3
DECL|macro|CTC_DBF_DATA_NR_AREAS
mdefine_line|#define CTC_DBF_DATA_NR_AREAS 1
DECL|macro|CTC_DBF_DATA_LEVEL
mdefine_line|#define CTC_DBF_DATA_LEVEL 2
DECL|macro|CTC_DBF_TRACE_NAME
mdefine_line|#define CTC_DBF_TRACE_NAME &quot;ctc_trace&quot;
DECL|macro|CTC_DBF_TRACE_LEN
mdefine_line|#define CTC_DBF_TRACE_LEN 16
DECL|macro|CTC_DBF_TRACE_INDEX
mdefine_line|#define CTC_DBF_TRACE_INDEX 2
DECL|macro|CTC_DBF_TRACE_NR_AREAS
mdefine_line|#define CTC_DBF_TRACE_NR_AREAS 2
DECL|macro|CTC_DBF_TRACE_LEVEL
mdefine_line|#define CTC_DBF_TRACE_LEVEL 3
DECL|macro|DBF_TEXT
mdefine_line|#define DBF_TEXT(name,level,text) &bslash;&n;&t;do { &bslash;&n;&t;&t;debug_text_event(ctc_dbf_##name,level,text); &bslash;&n;&t;} while (0)
DECL|macro|DBF_HEX
mdefine_line|#define DBF_HEX(name,level,addr,len) &bslash;&n;&t;do { &bslash;&n;&t;&t;debug_event(ctc_dbf_##name,level,(void*)(addr),len); &bslash;&n;&t;} while (0)
id|DECLARE_PER_CPU
c_func
(paren
r_char
(braket
l_int|256
)braket
comma
id|ctc_dbf_txt_buf
)paren
suffix:semicolon
r_extern
id|debug_info_t
op_star
id|ctc_dbf_setup
suffix:semicolon
r_extern
id|debug_info_t
op_star
id|ctc_dbf_data
suffix:semicolon
r_extern
id|debug_info_t
op_star
id|ctc_dbf_trace
suffix:semicolon
DECL|macro|DBF_TEXT_
mdefine_line|#define DBF_TEXT_(name,level,text...)&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;char* ctc_dbf_txt_buf = get_cpu_var(ctc_dbf_txt_buf);&t;&bslash;&n;&t;&t;sprintf(ctc_dbf_txt_buf, text);&t;&t;&t;  &t;&bslash;&n;&t;&t;debug_text_event(ctc_dbf_##name,level,ctc_dbf_txt_buf);&t;&bslash;&n;&t;&t;put_cpu_var(ctc_dbf_txt_buf);&t;&t;&t;&t;&bslash;&n;&t;} while (0)
DECL|macro|DBF_SPRINTF
mdefine_line|#define DBF_SPRINTF(name,level,text...) &bslash;&n;&t;do { &bslash;&n;&t;&t;debug_sprintf_event(ctc_dbf_trace, level, ##text ); &bslash;&n;&t;&t;debug_sprintf_event(ctc_dbf_trace, level, text ); &bslash;&n;&t;} while (0)
r_int
id|ctc_register_dbf_views
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|ctc_unregister_dbf_views
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/**&n; * some more debug stuff&n; */
DECL|macro|HEXDUMP16
mdefine_line|#define HEXDUMP16(importance,header,ptr) &bslash;&n;PRINT_##importance(header &quot;%02x %02x %02x %02x  %02x %02x %02x %02x  &quot; &bslash;&n;&t;&t;   &quot;%02x %02x %02x %02x  %02x %02x %02x %02x&bslash;n&quot;, &bslash;&n;&t;&t;   *(((char*)ptr)),*(((char*)ptr)+1),*(((char*)ptr)+2), &bslash;&n;&t;&t;   *(((char*)ptr)+3),*(((char*)ptr)+4),*(((char*)ptr)+5), &bslash;&n;&t;&t;   *(((char*)ptr)+6),*(((char*)ptr)+7),*(((char*)ptr)+8), &bslash;&n;&t;&t;   *(((char*)ptr)+9),*(((char*)ptr)+10),*(((char*)ptr)+11), &bslash;&n;&t;&t;   *(((char*)ptr)+12),*(((char*)ptr)+13), &bslash;&n;&t;&t;   *(((char*)ptr)+14),*(((char*)ptr)+15)); &bslash;&n;PRINT_##importance(header &quot;%02x %02x %02x %02x  %02x %02x %02x %02x  &quot; &bslash;&n;&t;&t;   &quot;%02x %02x %02x %02x  %02x %02x %02x %02x&bslash;n&quot;, &bslash;&n;&t;&t;   *(((char*)ptr)+16),*(((char*)ptr)+17), &bslash;&n;&t;&t;   *(((char*)ptr)+18),*(((char*)ptr)+19), &bslash;&n;&t;&t;   *(((char*)ptr)+20),*(((char*)ptr)+21), &bslash;&n;&t;&t;   *(((char*)ptr)+22),*(((char*)ptr)+23), &bslash;&n;&t;&t;   *(((char*)ptr)+24),*(((char*)ptr)+25), &bslash;&n;&t;&t;   *(((char*)ptr)+26),*(((char*)ptr)+27), &bslash;&n;&t;&t;   *(((char*)ptr)+28),*(((char*)ptr)+29), &bslash;&n;&t;&t;   *(((char*)ptr)+30),*(((char*)ptr)+31));
r_static
r_inline
r_void
DECL|function|hex_dump
id|hex_dump
c_func
(paren
r_int
r_char
op_star
id|buf
comma
r_int
id|len
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|len
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|i
op_logical_and
op_logical_neg
(paren
id|i
op_mod
l_int|16
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%02x &quot;
comma
op_star
(paren
id|buf
op_plus
id|i
)paren
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
eof
