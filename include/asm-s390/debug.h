multiline_comment|/*&n; *  include/asm-s390/debug.h&n; *   S/390 debug facility&n; *&n; *    Copyright (C) 1999, 2000 IBM Deutschland Entwicklung GmbH,&n; *                             IBM Corporation&n; */
macro_line|#ifndef DEBUG_H
DECL|macro|DEBUG_H
mdefine_line|#define DEBUG_H
multiline_comment|/* Note:&n; * struct __debug_entry must be defined outside of #ifdef __KERNEL__ &n; * in order to allow a user program to analyze the &squot;raw&squot;-view.&n; */
DECL|struct|__debug_entry
r_struct
id|__debug_entry
(brace
r_union
(brace
r_struct
(brace
DECL|member|clock
r_int
r_int
r_int
id|clock
suffix:colon
l_int|52
suffix:semicolon
DECL|member|exception
r_int
r_int
r_int
id|exception
suffix:colon
l_int|1
suffix:semicolon
DECL|member|used
r_int
r_int
r_int
id|used
suffix:colon
l_int|1
suffix:semicolon
DECL|member|unused
r_int
r_int
r_int
id|unused
suffix:colon
l_int|1
suffix:semicolon
DECL|member|cpuid
r_int
r_int
r_int
id|cpuid
suffix:colon
l_int|9
suffix:semicolon
DECL|member|fields
)brace
id|fields
suffix:semicolon
DECL|member|stck
r_int
r_int
r_int
id|stck
suffix:semicolon
DECL|member|id
)brace
id|id
suffix:semicolon
DECL|member|caller
r_void
op_star
id|caller
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/version.h&gt;
macro_line|#if (LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,3,0))
macro_line|#include &lt;asm/spinlock.h&gt;
macro_line|#else
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#endif /* LINUX_VERSION_CODE */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
DECL|macro|DEBUG_MAX_LEVEL
mdefine_line|#define DEBUG_MAX_LEVEL            6  /* debug levels range from 0 to 6 */
DECL|macro|DEBUG_OFF_LEVEL
mdefine_line|#define DEBUG_OFF_LEVEL            -1 /* level where debug is switched off */
DECL|macro|DEBUG_MAX_VIEWS
mdefine_line|#define DEBUG_MAX_VIEWS            10 /* max number of views in proc fs */
DECL|macro|DEBUG_MAX_PROCF_LEN
mdefine_line|#define DEBUG_MAX_PROCF_LEN        16 /* max length for a proc file name */
DECL|macro|DEBUG_DEFAULT_LEVEL
mdefine_line|#define DEBUG_DEFAULT_LEVEL        3  /* initial debug level */
DECL|macro|DEBUG_FEATURE_VERSION
mdefine_line|#define DEBUG_FEATURE_VERSION      1  /* version of debug feature */
DECL|macro|DEBUG_DIR_ROOT
mdefine_line|#define DEBUG_DIR_ROOT &quot;s390dbf&quot; /* name of debug root directory in proc fs */
DECL|macro|DEBUG_DATA
mdefine_line|#define DEBUG_DATA(entry) (char*)(entry + 1) /* data is stored behind */
multiline_comment|/* the entry information */
DECL|macro|STCK
mdefine_line|#define STCK(x)&t;asm volatile (&quot;STCK %0&quot;:&quot;=m&quot; (x))
DECL|typedef|debug_entry_t
r_typedef
r_struct
id|__debug_entry
id|debug_entry_t
suffix:semicolon
r_struct
id|debug_view
suffix:semicolon
DECL|struct|debug_info
r_typedef
r_struct
id|debug_info
(brace
DECL|member|next
r_struct
id|debug_info
op_star
id|next
suffix:semicolon
DECL|member|prev
r_struct
id|debug_info
op_star
id|prev
suffix:semicolon
DECL|member|ref_count
id|atomic_t
id|ref_count
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|level
r_int
id|level
suffix:semicolon
DECL|member|nr_areas
r_int
id|nr_areas
suffix:semicolon
DECL|member|page_order
r_int
id|page_order
suffix:semicolon
DECL|member|buf_size
r_int
id|buf_size
suffix:semicolon
DECL|member|entry_size
r_int
id|entry_size
suffix:semicolon
DECL|member|areas
id|debug_entry_t
op_star
op_star
id|areas
suffix:semicolon
DECL|member|active_area
r_int
id|active_area
suffix:semicolon
DECL|member|active_entry
r_int
op_star
id|active_entry
suffix:semicolon
DECL|member|proc_root_entry
r_struct
id|proc_dir_entry
op_star
id|proc_root_entry
suffix:semicolon
DECL|member|proc_entries
r_struct
id|proc_dir_entry
op_star
id|proc_entries
(braket
id|DEBUG_MAX_VIEWS
)braket
suffix:semicolon
DECL|member|views
r_struct
id|debug_view
op_star
id|views
(braket
id|DEBUG_MAX_VIEWS
)braket
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
id|DEBUG_MAX_PROCF_LEN
)braket
suffix:semicolon
DECL|typedef|debug_info_t
)brace
id|debug_info_t
suffix:semicolon
DECL|typedef|debug_header_proc_t
r_typedef
r_int
(paren
id|debug_header_proc_t
)paren
(paren
id|debug_info_t
op_star
id|id
comma
r_struct
id|debug_view
op_star
id|view
comma
r_int
id|area
comma
id|debug_entry_t
op_star
id|entry
comma
r_char
op_star
id|out_buf
)paren
suffix:semicolon
DECL|typedef|debug_format_proc_t
r_typedef
r_int
(paren
id|debug_format_proc_t
)paren
(paren
id|debug_info_t
op_star
id|id
comma
r_struct
id|debug_view
op_star
id|view
comma
r_char
op_star
id|out_buf
comma
r_const
r_char
op_star
id|in_buf
)paren
suffix:semicolon
DECL|typedef|debug_prolog_proc_t
r_typedef
r_int
(paren
id|debug_prolog_proc_t
)paren
(paren
id|debug_info_t
op_star
id|id
comma
r_struct
id|debug_view
op_star
id|view
comma
r_char
op_star
id|out_buf
)paren
suffix:semicolon
DECL|typedef|debug_input_proc_t
r_typedef
r_int
(paren
id|debug_input_proc_t
)paren
(paren
id|debug_info_t
op_star
id|id
comma
r_struct
id|debug_view
op_star
id|view
comma
r_struct
id|file
op_star
id|file
comma
r_const
r_char
op_star
id|user_buf
comma
r_int
id|in_buf_size
comma
id|loff_t
op_star
id|offset
)paren
suffix:semicolon
r_int
id|debug_dflt_header_fn
c_func
(paren
id|debug_info_t
op_star
id|id
comma
r_struct
id|debug_view
op_star
id|view
comma
r_int
id|area
comma
id|debug_entry_t
op_star
id|entry
comma
r_char
op_star
id|out_buf
)paren
suffix:semicolon
DECL|struct|debug_view
r_struct
id|debug_view
(brace
DECL|member|name
r_char
id|name
(braket
id|DEBUG_MAX_PROCF_LEN
)braket
suffix:semicolon
DECL|member|prolog_proc
id|debug_prolog_proc_t
op_star
id|prolog_proc
suffix:semicolon
DECL|member|header_proc
id|debug_header_proc_t
op_star
id|header_proc
suffix:semicolon
DECL|member|format_proc
id|debug_format_proc_t
op_star
id|format_proc
suffix:semicolon
DECL|member|input_proc
id|debug_input_proc_t
op_star
id|input_proc
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|debug_view
id|debug_hex_ascii_view
suffix:semicolon
r_extern
r_struct
id|debug_view
id|debug_raw_view
suffix:semicolon
id|debug_info_t
op_star
id|debug_register
c_func
(paren
r_char
op_star
id|name
comma
r_int
id|pages_index
comma
r_int
id|nr_areas
comma
r_int
id|buf_size
)paren
suffix:semicolon
r_void
id|debug_unregister
c_func
(paren
id|debug_info_t
op_star
id|id
)paren
suffix:semicolon
r_void
id|debug_set_level
c_func
(paren
id|debug_info_t
op_star
id|id
comma
r_int
id|new_level
)paren
suffix:semicolon
id|debug_entry_t
op_star
id|debug_event
c_func
(paren
id|debug_info_t
op_star
id|id
comma
r_int
id|level
comma
r_void
op_star
id|data
comma
r_int
id|length
)paren
suffix:semicolon
id|debug_entry_t
op_star
id|debug_int_event
c_func
(paren
id|debug_info_t
op_star
id|id
comma
r_int
id|level
comma
r_int
r_int
id|tag
)paren
suffix:semicolon
id|debug_entry_t
op_star
id|debug_text_event
c_func
(paren
id|debug_info_t
op_star
id|id
comma
r_int
id|level
comma
r_const
r_char
op_star
id|txt
)paren
suffix:semicolon
id|debug_entry_t
op_star
id|debug_exception
c_func
(paren
id|debug_info_t
op_star
id|id
comma
r_int
id|level
comma
r_void
op_star
id|data
comma
r_int
id|length
)paren
suffix:semicolon
id|debug_entry_t
op_star
id|debug_int_exception
c_func
(paren
id|debug_info_t
op_star
id|id
comma
r_int
id|level
comma
r_int
r_int
id|tag
)paren
suffix:semicolon
id|debug_entry_t
op_star
id|debug_text_exception
c_func
(paren
id|debug_info_t
op_star
id|id
comma
r_int
id|level
comma
r_const
r_char
op_star
id|txt
)paren
suffix:semicolon
r_static
r_inline
id|debug_entry_t
op_star
DECL|function|debug_long_event
id|debug_long_event
(paren
id|debug_info_t
op_star
id|id
comma
r_int
id|level
comma
r_int
r_int
id|tag
)paren
(brace
r_int
r_int
id|t
op_assign
id|tag
suffix:semicolon
r_return
id|debug_event
c_func
(paren
id|id
comma
id|level
comma
op_amp
id|t
comma
r_sizeof
(paren
r_int
r_int
)paren
)paren
suffix:semicolon
)brace
r_static
r_inline
id|debug_entry_t
op_star
DECL|function|debug_long_exception
id|debug_long_exception
(paren
id|debug_info_t
op_star
id|id
comma
r_int
id|level
comma
r_int
r_int
id|tag
)paren
(brace
r_int
r_int
id|t
op_assign
id|tag
suffix:semicolon
r_return
id|debug_exception
c_func
(paren
id|id
comma
id|level
comma
op_amp
id|t
comma
r_sizeof
(paren
r_int
r_int
)paren
)paren
suffix:semicolon
)brace
r_int
id|debug_register_view
c_func
(paren
id|debug_info_t
op_star
id|id
comma
r_struct
id|debug_view
op_star
id|view
)paren
suffix:semicolon
r_int
id|debug_unregister_view
c_func
(paren
id|debug_info_t
op_star
id|id
comma
r_struct
id|debug_view
op_star
id|view
)paren
suffix:semicolon
multiline_comment|/*&n;   define the debug levels:&n;   - 0 No debugging output to console or syslog&n;   - 1 Log internal errors to syslog, ignore check conditions &n;   - 2 Log internal errors and check conditions to syslog&n;   - 3 Log internal errors to console, log check conditions to syslog&n;   - 4 Log internal errors and check conditions to console&n;   - 5 panic on internal errors, log check conditions to console&n;   - 6 panic on both, internal errors and check conditions&n; */
macro_line|#ifndef DEBUG_LEVEL
DECL|macro|DEBUG_LEVEL
mdefine_line|#define DEBUG_LEVEL 4
macro_line|#endif
DECL|macro|INTERNAL_ERRMSG
mdefine_line|#define INTERNAL_ERRMSG(x,y...) &quot;E&quot; __FILE__ &quot;%d: &quot; x, __LINE__, y
DECL|macro|INTERNAL_WRNMSG
mdefine_line|#define INTERNAL_WRNMSG(x,y...) &quot;W&quot; __FILE__ &quot;%d: &quot; x, __LINE__, y
DECL|macro|INTERNAL_INFMSG
mdefine_line|#define INTERNAL_INFMSG(x,y...) &quot;I&quot; __FILE__ &quot;%d: &quot; x, __LINE__, y
DECL|macro|INTERNAL_DEBMSG
mdefine_line|#define INTERNAL_DEBMSG(x,y...) &quot;D&quot; __FILE__ &quot;%d: &quot; x, __LINE__, y
macro_line|#if DEBUG_LEVEL &gt; 0
DECL|macro|PRINT_DEBUG
mdefine_line|#define PRINT_DEBUG(x...) printk ( KERN_DEBUG PRINTK_HEADER x )
DECL|macro|PRINT_INFO
mdefine_line|#define PRINT_INFO(x...) printk ( KERN_INFO PRINTK_HEADER x )
DECL|macro|PRINT_WARN
mdefine_line|#define PRINT_WARN(x...) printk ( KERN_WARNING PRINTK_HEADER x )
DECL|macro|PRINT_ERR
mdefine_line|#define PRINT_ERR(x...) printk ( KERN_ERR PRINTK_HEADER x )
DECL|macro|PRINT_FATAL
mdefine_line|#define PRINT_FATAL(x...) panic ( PRINTK_HEADER x )
macro_line|#else
DECL|macro|PRINT_DEBUG
mdefine_line|#define PRINT_DEBUG(x...) printk ( KERN_DEBUG PRINTK_HEADER x )
DECL|macro|PRINT_INFO
mdefine_line|#define PRINT_INFO(x...) printk ( KERN_DEBUG PRINTK_HEADER x )
DECL|macro|PRINT_WARN
mdefine_line|#define PRINT_WARN(x...) printk ( KERN_DEBUG PRINTK_HEADER x )
DECL|macro|PRINT_ERR
mdefine_line|#define PRINT_ERR(x...) printk ( KERN_DEBUG PRINTK_HEADER x )
DECL|macro|PRINT_FATAL
mdefine_line|#define PRINT_FATAL(x...) printk ( KERN_DEBUG PRINTK_HEADER x )
macro_line|#endif&t;&t;&t;&t;/* DASD_DEBUG */
macro_line|#if DASD_DEBUG &gt; 4
DECL|macro|INTERNAL_ERROR
mdefine_line|#define INTERNAL_ERROR(x...) PRINT_FATAL ( INTERNAL_ERRMSG ( x ) )
macro_line|#elif DASD_DEBUG &gt; 2
DECL|macro|INTERNAL_ERROR
mdefine_line|#define INTERNAL_ERROR(x...) PRINT_ERR ( INTERNAL_ERRMSG ( x ) )
macro_line|#elif DASD_DEBUG &gt; 0
DECL|macro|INTERNAL_ERROR
mdefine_line|#define INTERNAL_ERROR(x...) PRINT_WARN ( INTERNAL_ERRMSG ( x ) )
macro_line|#else
DECL|macro|INTERNAL_ERROR
mdefine_line|#define INTERNAL_ERROR(x...)
macro_line|#endif&t;&t;&t;&t;/* DASD_DEBUG */
macro_line|#if DASD_DEBUG &gt; 5
DECL|macro|INTERNAL_CHECK
mdefine_line|#define INTERNAL_CHECK(x...) PRINT_FATAL ( INTERNAL_CHKMSG ( x ) )
macro_line|#elif DASD_DEBUG &gt; 3
DECL|macro|INTERNAL_CHECK
mdefine_line|#define INTERNAL_CHECK(x...) PRINT_ERR ( INTERNAL_CHKMSG ( x ) )
macro_line|#elif DASD_DEBUG &gt; 1
DECL|macro|INTERNAL_CHECK
mdefine_line|#define INTERNAL_CHECK(x...) PRINT_WARN ( INTERNAL_CHKMSG ( x ) )
macro_line|#else
DECL|macro|INTERNAL_CHECK
mdefine_line|#define INTERNAL_CHECK(x...)
macro_line|#endif&t;&t;&t;&t;/* DASD_DEBUG */
DECL|macro|DEBUG_MALLOC
macro_line|#undef DEBUG_MALLOC
macro_line|#ifdef DEBUG_MALLOC
DECL|variable|b
r_void
op_star
id|b
suffix:semicolon
DECL|macro|kmalloc
mdefine_line|#define kmalloc(x...) (PRINT_INFO(&quot; kmalloc %p&bslash;n&quot;,b=kmalloc(x)),b)
DECL|macro|kfree
mdefine_line|#define kfree(x) PRINT_INFO(&quot; kfree %p&bslash;n&quot;,x);kfree(x)
DECL|macro|get_free_page
mdefine_line|#define get_free_page(x...) (PRINT_INFO(&quot; gfp %p&bslash;n&quot;,b=get_free_page(x)),b)
DECL|macro|__get_free_pages
mdefine_line|#define __get_free_pages(x...) (PRINT_INFO(&quot; gfps %p&bslash;n&quot;,b=__get_free_pages(x)),b)
macro_line|#endif&t;&t;&t;&t;/* DEBUG_MALLOC */
macro_line|#endif&t;&t;&t;&t;/* __KERNEL__ */
macro_line|#endif&t;&t;&t;&t;/* DEBUG_H */
eof
