multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000-2002 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#ifndef _ASM_IA64_SN_IOERROR_H
DECL|macro|_ASM_IA64_SN_IOERROR_H
mdefine_line|#define _ASM_IA64_SN_IOERROR_H
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/sn/types.h&gt;
multiline_comment|/*&n; * Macros defining the various Errors to be handled as part of&n; * IO Error handling.&n; */
multiline_comment|/*&n; * List of errors to be handled by each subsystem.&n; * &quot;error_code&quot; field will take one of these values.&n; * The error code is built up of single bits expressing&n; * our confidence that the error was that type; note&n; * that it is possible to have a PIO or DMA error where&n; * we don&squot;t know whether it was a READ or a WRITE, or&n; * even a READ or WRITE error that we&squot;re not sure whether&n; * to call a PIO or DMA.&n; *&n; * It is also possible to set both PIO and DMA, and possible&n; * to set both READ and WRITE; the first may be nonsensical&n; * but the second *could* be used to designate an access&n; * that is known to be a read-modify-write cycle. It is&n; * quite possible that nobody will ever use PIO|DMA or&n; * READ|WRITE ... but being flexible is good.&n; */
DECL|macro|IOECODE_UNSPEC
mdefine_line|#define&t;IOECODE_UNSPEC&t;&t;0
DECL|macro|IOECODE_READ
mdefine_line|#define&t;IOECODE_READ&t;&t;1
DECL|macro|IOECODE_WRITE
mdefine_line|#define&t;IOECODE_WRITE&t;&t;2
DECL|macro|IOECODE_PIO
mdefine_line|#define&t;IOECODE_PIO&t;&t;4
DECL|macro|IOECODE_DMA
mdefine_line|#define&t;IOECODE_DMA&t;&t;8
DECL|macro|IOECODE_PIO_READ
mdefine_line|#define&t;IOECODE_PIO_READ&t;(IOECODE_PIO|IOECODE_READ)
DECL|macro|IOECODE_PIO_WRITE
mdefine_line|#define&t;IOECODE_PIO_WRITE&t;(IOECODE_PIO|IOECODE_WRITE)
DECL|macro|IOECODE_DMA_READ
mdefine_line|#define&t;IOECODE_DMA_READ&t;(IOECODE_DMA|IOECODE_READ)
DECL|macro|IOECODE_DMA_WRITE
mdefine_line|#define&t;IOECODE_DMA_WRITE&t;(IOECODE_DMA|IOECODE_WRITE)
multiline_comment|/* support older names, but try to move everything&n; * to using new names that identify which package&n; * controls their values ...&n; */
DECL|macro|PIO_READ_ERROR
mdefine_line|#define&t;PIO_READ_ERROR&t;&t;IOECODE_PIO_READ
DECL|macro|PIO_WRITE_ERROR
mdefine_line|#define&t;PIO_WRITE_ERROR&t;&t;IOECODE_PIO_WRITE
DECL|macro|DMA_READ_ERROR
mdefine_line|#define&t;DMA_READ_ERROR&t;&t;IOECODE_DMA_READ
DECL|macro|DMA_WRITE_ERROR
mdefine_line|#define&t;DMA_WRITE_ERROR&t;&t;IOECODE_DMA_WRITE
multiline_comment|/*&n; * List of error numbers returned by error handling sub-system.&n; */
DECL|macro|IOERROR_HANDLED
mdefine_line|#define&t;IOERROR_HANDLED&t;&t;0&t;/* Error Properly handled.        */
DECL|macro|IOERROR_NODEV
mdefine_line|#define&t;IOERROR_NODEV&t;&t;0x1&t;/* No such device attached        */
DECL|macro|IOERROR_BADHANDLE
mdefine_line|#define&t;IOERROR_BADHANDLE&t;0x2&t;/* Received bad handle            */
DECL|macro|IOERROR_BADWIDGETNUM
mdefine_line|#define&t;IOERROR_BADWIDGETNUM&t;0x3&t;/* Bad widget number              */
DECL|macro|IOERROR_BADERRORCODE
mdefine_line|#define&t;IOERROR_BADERRORCODE&t;0x4&t;/* Bad error code passed in       */
DECL|macro|IOERROR_INVALIDADDR
mdefine_line|#define&t;IOERROR_INVALIDADDR&t;0x5&t;/* Invalid address specified      */
DECL|macro|IOERROR_WIDGETLEVEL
mdefine_line|#define&t;IOERROR_WIDGETLEVEL&t;0x6&t;/* Some failure at widget level    */
DECL|macro|IOERROR_XTALKLEVEL
mdefine_line|#define&t;IOERROR_XTALKLEVEL&t;0x7
DECL|macro|IOERROR_HWGRAPH_LOOKUP
mdefine_line|#define&t;IOERROR_HWGRAPH_LOOKUP&t;0x8&t;/* hwgraph lookup failed for path  */
DECL|macro|IOERROR_UNHANDLED
mdefine_line|#define&t;IOERROR_UNHANDLED&t;0x9&t;/* handler rejected error          */
DECL|macro|IOERROR_PANIC
mdefine_line|#define&t;IOERROR_PANIC&t;&t;0xA&t;/* subsidiary handler has already&n;&t;&t;&t;&t;&t; * started decode: continue error&n;&t;&t;&t;&t;&t; * data dump, and panic from top&n;&t;&t;&t;&t;&t; * caller in error chain.&n;&t;&t;&t;&t;&t; */
multiline_comment|/*&n; * IO errors at the bus/device driver level&n; */
DECL|macro|IOERROR_DEV_NOTFOUND
mdefine_line|#define&t;IOERROR_DEV_NOTFOUND&t;0x10&t;/* Device matching bus addr not found */
DECL|macro|IOERROR_DEV_SHUTDOWN
mdefine_line|#define&t;IOERROR_DEV_SHUTDOWN&t;0x11&t;/* Device has been shutdown        */
multiline_comment|/*&n; * Type of address.&n; * Indicates the direction of transfer that caused the error.&n; */
DECL|macro|IOERROR_ADDR_PIO
mdefine_line|#define&t;IOERROR_ADDR_PIO&t;1&t;/* Error Address generated due to PIO */
DECL|macro|IOERROR_ADDR_DMA
mdefine_line|#define&t;IOERROR_ADDR_DMA&t;2&t;/* Error address generated due to DMA */
multiline_comment|/*&n; * IO error structure.&n; *&n; * This structure would expand to hold the information retrieved from&n; * all IO related error registers.&n; *&n; * This structure is defined to hold all system specific&n; * information related to a single error.&n; *&n; * This serves a couple of purpose.&n; *      - Error handling often involves translating one form of address to other&n; *        form. So, instead of having different data structures at each level,&n; *        we have a single structure, and the appropriate fields get filled in&n; *        at each layer.&n; *      - This provides a way to dump all error related information in any layer&n; *        of erorr handling (debugging aid).&n; *&n; * A second possibility is to allow each layer to define its own error&n; * data structure, and fill in the proper fields. This has the advantage&n; * of isolating the layers.&n; * A big concern is the potential stack usage (and overflow), if each layer&n; * defines these structures on stack (assuming we don&squot;t want to do kmalloc.&n; *&n; * Any layer wishing to pass extra information to a layer next to it in&n; * error handling hierarchy, can do so as a separate parameter.&n; */
DECL|struct|io_error_s
r_typedef
r_struct
id|io_error_s
(brace
multiline_comment|/* Bit fields indicating which sturcture fields are valid */
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
id|paddr_t
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
DECL|typedef|ioerror_t
)brace
id|ioerror_t
suffix:semicolon
DECL|macro|IOERROR_INIT
mdefine_line|#define&t;IOERROR_INIT(e)&t;&t;do { (e)-&gt;ie_v.iev_a = 0; } while (0)
DECL|macro|IOERROR_SETVALUE
mdefine_line|#define&t;IOERROR_SETVALUE(e,f,v)&t;do { (e)-&gt;ie_ ## f = (v); (e)-&gt;ie_v.iev_b.ievb_ ## f = 1; } while (0)
DECL|macro|IOERROR_FIELDVALID
mdefine_line|#define&t;IOERROR_FIELDVALID(e,f)&t;(((e)-&gt;ie_v.iev_b.ievb_ ## f) != 0)
DECL|macro|IOERROR_GETVALUE
mdefine_line|#define&t;IOERROR_GETVALUE(e,f)&t;(ASSERT(IOERROR_FIELDVALID(e,f)),((e)-&gt;ie_ ## f))
multiline_comment|/* hub code likes to call the SysAD address &quot;hubaddr&quot; ... */
DECL|macro|ie_hubaddr
mdefine_line|#define&t;ie_hubaddr&t;ie_sysioaddr
DECL|macro|ievb_hubaddr
mdefine_line|#define&t;ievb_hubaddr&t;ievb_sysioaddr
macro_line|#endif
multiline_comment|/*&n; * Error handling Modes.&n; */
r_typedef
r_enum
(brace
DECL|enumerator|MODE_DEVPROBE
id|MODE_DEVPROBE
comma
multiline_comment|/* Probing mode. Errors not fatal */
DECL|enumerator|MODE_DEVERROR
id|MODE_DEVERROR
comma
multiline_comment|/* Error while system is running */
DECL|enumerator|MODE_DEVUSERERROR
id|MODE_DEVUSERERROR
comma
multiline_comment|/* Device Error created due to user mode access */
DECL|enumerator|MODE_DEVREENABLE
id|MODE_DEVREENABLE
multiline_comment|/* Reenable pass                */
DECL|typedef|ioerror_mode_t
)brace
id|ioerror_mode_t
suffix:semicolon
DECL|typedef|error_handler_f
r_typedef
r_int
id|error_handler_f
c_func
(paren
r_void
op_star
comma
r_int
comma
id|ioerror_mode_t
comma
id|ioerror_t
op_star
)paren
suffix:semicolon
DECL|typedef|error_handler_arg_t
r_typedef
r_void
op_star
id|error_handler_arg_t
suffix:semicolon
r_extern
r_void
id|ioerror_dump
c_func
(paren
r_char
op_star
comma
r_int
comma
r_int
comma
id|ioerror_t
op_star
)paren
suffix:semicolon
macro_line|#ifdef&t;ERROR_DEBUG
DECL|macro|IOERROR_DUMP
mdefine_line|#define&t;IOERROR_DUMP(x, y, z, t)&t;ioerror_dump((x), (y), (z), (t))
DECL|macro|IOERR_PRINTF
mdefine_line|#define&t;IOERR_PRINTF(x)&t;(x)
macro_line|#else
DECL|macro|IOERROR_DUMP
mdefine_line|#define&t;IOERROR_DUMP(x, y, z, t)
DECL|macro|IOERR_PRINTF
mdefine_line|#define&t;IOERR_PRINTF(x)
macro_line|#endif&t;&t;&t;&t;/* ERROR_DEBUG */
macro_line|#endif /* _ASM_IA64_SN_IOERROR_H */
eof
