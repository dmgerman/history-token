multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000-2003 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#ifndef _ASM_IA64_SN_IOERROR_H
DECL|macro|_ASM_IA64_SN_IOERROR_H
mdefine_line|#define _ASM_IA64_SN_IOERROR_H
multiline_comment|/*&n; * IO error structure.&n; *&n; * This structure would expand to hold the information retrieved from&n; * all IO related error registers.&n; *&n; * This structure is defined to hold all system specific&n; * information related to a single error.&n; *&n; * This serves a couple of purpose.&n; *      - Error handling often involves translating one form of address to other&n; *        form. So, instead of having different data structures at each level,&n; *        we have a single structure, and the appropriate fields get filled in&n; *        at each layer.&n; *      - This provides a way to dump all error related information in any layer&n; *        of erorr handling (debugging aid).&n; *&n; * A second possibility is to allow each layer to define its own error&n; * data structure, and fill in the proper fields. This has the advantage&n; * of isolating the layers.&n; * A big concern is the potential stack usage (and overflow), if each layer&n; * defines these structures on stack (assuming we don&squot;t want to do kmalloc.&n; *&n; * Any layer wishing to pass extra information to a layer next to it in&n; * error handling hierarchy, can do so as a separate parameter.&n; */
DECL|struct|io_error_s
r_typedef
r_struct
id|io_error_s
(brace
multiline_comment|/* Bit fields indicating which structure fields are valid */
r_union
(brace
r_struct
(brace
DECL|member|ievb_errortype
r_int
id|ievb_errortype
suffix:colon
l_int|1
suffix:semicolon
DECL|member|ievb_widgetnum
r_int
id|ievb_widgetnum
suffix:colon
l_int|1
suffix:semicolon
DECL|member|ievb_widgetdev
r_int
id|ievb_widgetdev
suffix:colon
l_int|1
suffix:semicolon
DECL|member|ievb_srccpu
r_int
id|ievb_srccpu
suffix:colon
l_int|1
suffix:semicolon
DECL|member|ievb_srcnode
r_int
id|ievb_srcnode
suffix:colon
l_int|1
suffix:semicolon
DECL|member|ievb_errnode
r_int
id|ievb_errnode
suffix:colon
l_int|1
suffix:semicolon
DECL|member|ievb_sysioaddr
r_int
id|ievb_sysioaddr
suffix:colon
l_int|1
suffix:semicolon
DECL|member|ievb_xtalkaddr
r_int
id|ievb_xtalkaddr
suffix:colon
l_int|1
suffix:semicolon
DECL|member|ievb_busspace
r_int
id|ievb_busspace
suffix:colon
l_int|1
suffix:semicolon
DECL|member|ievb_busaddr
r_int
id|ievb_busaddr
suffix:colon
l_int|1
suffix:semicolon
DECL|member|ievb_vaddr
r_int
id|ievb_vaddr
suffix:colon
l_int|1
suffix:semicolon
DECL|member|ievb_memaddr
r_int
id|ievb_memaddr
suffix:colon
l_int|1
suffix:semicolon
DECL|member|ievb_epc
r_int
id|ievb_epc
suffix:colon
l_int|1
suffix:semicolon
DECL|member|ievb_ef
r_int
id|ievb_ef
suffix:colon
l_int|1
suffix:semicolon
DECL|member|ievb_tnum
r_int
id|ievb_tnum
suffix:colon
l_int|1
suffix:semicolon
DECL|member|iev_b
)brace
id|iev_b
suffix:semicolon
DECL|member|iev_a
r_int
id|iev_a
suffix:semicolon
DECL|member|ie_v
)brace
id|ie_v
suffix:semicolon
DECL|member|ie_errortype
r_int
id|ie_errortype
suffix:semicolon
multiline_comment|/* error type: extra info about error */
DECL|member|ie_widgetnum
r_int
id|ie_widgetnum
suffix:semicolon
multiline_comment|/* Widget number that&squot;s in error */
DECL|member|ie_widgetdev
r_int
id|ie_widgetdev
suffix:semicolon
multiline_comment|/* Device within widget in error */
DECL|member|ie_srccpu
id|cpuid_t
id|ie_srccpu
suffix:semicolon
multiline_comment|/* CPU on srcnode generating error */
DECL|member|ie_srcnode
id|cnodeid_t
id|ie_srcnode
suffix:semicolon
multiline_comment|/* Node which caused the error   */
DECL|member|ie_errnode
id|cnodeid_t
id|ie_errnode
suffix:semicolon
multiline_comment|/* Node where error was noticed  */
DECL|member|ie_sysioaddr
id|iopaddr_t
id|ie_sysioaddr
suffix:semicolon
multiline_comment|/* Sys specific IO address       */
DECL|member|ie_xtalkaddr
id|iopaddr_t
id|ie_xtalkaddr
suffix:semicolon
multiline_comment|/* Xtalk (48bit) addr of Error   */
DECL|member|ie_busspace
id|iopaddr_t
id|ie_busspace
suffix:semicolon
multiline_comment|/* Bus specific address space    */
DECL|member|ie_busaddr
id|iopaddr_t
id|ie_busaddr
suffix:semicolon
multiline_comment|/* Bus specific address          */
DECL|member|ie_vaddr
id|caddr_t
id|ie_vaddr
suffix:semicolon
multiline_comment|/* Virtual address of error      */
DECL|member|ie_memaddr
id|iopaddr_t
id|ie_memaddr
suffix:semicolon
multiline_comment|/* Physical memory address       */
DECL|member|ie_epc
id|caddr_t
id|ie_epc
suffix:semicolon
multiline_comment|/* pc when error reported&t; */
DECL|member|ie_ef
id|caddr_t
id|ie_ef
suffix:semicolon
multiline_comment|/* eframe when error reported&t; */
DECL|member|ie_tnum
r_int
id|ie_tnum
suffix:semicolon
multiline_comment|/* Xtalk TNUM field */
DECL|typedef|ioerror_t
)brace
id|ioerror_t
suffix:semicolon
DECL|macro|IOERROR_INIT
mdefine_line|#define&t;IOERROR_INIT(e)&t;&t;do { (e)-&gt;ie_v.iev_a = 0; } while (0)
DECL|macro|IOERROR_SETVALUE
mdefine_line|#define&t;IOERROR_SETVALUE(e,f,v)&t;do { (e)-&gt;ie_ ## f = (v); (e)-&gt;ie_v.iev_b.ievb_ ## f = 1; } while (0)
macro_line|#endif /* _ASM_IA64_SN_IOERROR_H */
eof
