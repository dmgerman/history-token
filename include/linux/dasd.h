macro_line|#ifndef DASD_H
DECL|macro|DASD_H
mdefine_line|#define DASD_H
multiline_comment|/* First of all the external stuff */
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
DECL|macro|IOCTL_LETTER
mdefine_line|#define IOCTL_LETTER &squot;D&squot;
DECL|macro|BIODASDFORMAT
mdefine_line|#define BIODASDFORMAT  _IO(IOCTL_LETTER,0) /* Format the volume or an extent */
DECL|macro|BIODASDDISABLE
mdefine_line|#define BIODASDDISABLE _IO(IOCTL_LETTER,1) /* Disable the volume (for Linux) */
DECL|macro|BIODASDENABLE
mdefine_line|#define BIODASDENABLE  _IO(IOCTL_LETTER,2) /* Enable the volume (for Linux) */
multiline_comment|/* Stuff for reading and writing the Label-Area to/from user space */
DECL|macro|BIODASDGTVLBL
mdefine_line|#define BIODASDGTVLBL  _IOR(IOCTL_LETTER,3,dasd_volume_label_t)
DECL|macro|BIODASDSTVLBL
mdefine_line|#define BIODASDSTVLBL  _IOW(IOCTL_LETTER,4,dasd_volume_label_t)
DECL|macro|BIODASDRWTB
mdefine_line|#define BIODASDRWTB    _IOWR(IOCTL_LETTER,5,int)
DECL|macro|BIODASDRSID
mdefine_line|#define BIODASDRSID    _IOR(IOCTL_LETTER,6,senseid_t)
r_typedef
r_union
(brace
DECL|member|bytes
r_char
id|bytes
(braket
l_int|512
)braket
suffix:semicolon
r_struct
(brace
multiline_comment|/* 80 Bytes of Label data */
DECL|member|identifier
r_char
id|identifier
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* e.g. &quot;LNX1&quot;, &quot;VOL1&quot; or &quot;CMS1&quot; */
DECL|member|label
r_char
id|label
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* Given by user */
DECL|member|security
r_char
id|security
suffix:semicolon
DECL|member|vtoc
r_char
id|vtoc
(braket
l_int|5
)braket
suffix:semicolon
multiline_comment|/* Null in &quot;LNX1&quot;-labelled partitions */
DECL|member|reserved0
r_char
id|reserved0
(braket
l_int|5
)braket
suffix:semicolon
DECL|member|ci_size
r_int
id|ci_size
suffix:semicolon
DECL|member|blk_per_ci
r_int
id|blk_per_ci
suffix:semicolon
DECL|member|lab_per_ci
r_int
id|lab_per_ci
suffix:semicolon
DECL|member|reserved1
r_char
id|reserved1
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|owner
r_char
id|owner
(braket
l_int|0xe
)braket
suffix:semicolon
DECL|member|no_part
r_char
id|no_part
suffix:semicolon
DECL|member|reserved2
r_char
id|reserved2
(braket
l_int|0x1c
)braket
suffix:semicolon
multiline_comment|/* 16 Byte of some information on the dasd */
DECL|member|blocksize
r_int
id|blocksize
suffix:semicolon
DECL|member|nopart
r_char
id|nopart
suffix:semicolon
DECL|member|unused
r_char
id|unused
suffix:semicolon
DECL|member|unused2
r_int
id|unused2
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* 7*10 = 70 Bytes of partition data */
r_struct
(brace
DECL|member|type
r_char
id|type
suffix:semicolon
DECL|member|start
r_int
id|start
suffix:semicolon
DECL|member|size
r_int
id|size
suffix:semicolon
DECL|member|unused
r_char
id|unused
suffix:semicolon
DECL|member|part
)brace
id|part
(braket
l_int|7
)braket
suffix:semicolon
DECL|member|label
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|label
suffix:semicolon
DECL|typedef|dasd_volume_label_t
)brace
id|dasd_volume_label_t
suffix:semicolon
r_typedef
r_union
(brace
r_struct
(brace
DECL|member|no
r_int
r_int
id|no
suffix:semicolon
DECL|member|ct
r_int
r_int
id|ct
suffix:semicolon
DECL|member|input
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|input
suffix:semicolon
r_struct
(brace
DECL|member|noct
r_int
r_int
id|noct
suffix:semicolon
DECL|member|output
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|output
suffix:semicolon
DECL|typedef|dasd_xlate_t
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|dasd_xlate_t
suffix:semicolon
r_int
id|dasd_init
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef MODULE
r_int
id|init_module
(paren
r_void
)paren
suffix:semicolon
r_void
id|cleanup_module
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* MODULE */
multiline_comment|/* Definitions for blk.h */
multiline_comment|/* #define DASD_MAGIC 0x44415344  is ascii-&quot;DASD&quot; */
multiline_comment|/* #define dasd_MAGIC 0x64617364;  is ascii-&quot;dasd&quot; */
DECL|macro|DASD_MAGIC
mdefine_line|#define DASD_MAGIC 0xC4C1E2C4 /* is ebcdic-&quot;DASD&quot; */
DECL|macro|dasd_MAGIC
mdefine_line|#define dasd_MAGIC 0x8481A284 /* is ebcdic-&quot;dasd&quot; */
DECL|macro|DASD_NAME
mdefine_line|#define DASD_NAME &quot;dasd&quot;
DECL|macro|DASD_PARTN_BITS
mdefine_line|#define DASD_PARTN_BITS 2
DECL|macro|DASD_MAX_DEVICES
mdefine_line|#define DASD_MAX_DEVICES (256&gt;&gt;DASD_PARTN_BITS)
DECL|macro|MAJOR_NR
mdefine_line|#define MAJOR_NR DASD_MAJOR
DECL|macro|PARTN_BITS
mdefine_line|#define PARTN_BITS DASD_PARTN_BITS
macro_line|#ifdef __KERNEL__
multiline_comment|/* Now lets turn to the internal sbtuff */
multiline_comment|/*&n;   define the debug levels:&n;   - 0 No debugging output to console or syslog&n;   - 1 Log internal errors to syslog, ignore check conditions &n;   - 2 Log internal errors and check conditions to syslog&n;   - 3 Log internal errors to console, log check conditions to syslog&n;   - 4 Log internal errors and check conditions to console&n;   - 5 panic on internal errors, log check conditions to console&n;   - 6 panic on both, internal errors and check conditions&n; */
DECL|macro|DASD_DEBUG
mdefine_line|#define DASD_DEBUG 4
DECL|macro|DASD_PROFILE
mdefine_line|#define DASD_PROFILE
multiline_comment|/*&n;   define the level of paranoia&n;   - 0 quite sure, that things are going right&n;   - 1 sanity checking, only to avoid panics&n;   - 2 normal sanity checking&n;   - 3 extensive sanity checks&n;   - 4 exhaustive debug messages&n; */
DECL|macro|DASD_PARANOIA
mdefine_line|#define DASD_PARANOIA 2
multiline_comment|/*&n;   define the depth of flow control, which is logged as a check condition&n;   - 0 No flow control messages&n;   - 1 Entry of functions logged like check condition&n;   - 2 Entry and exit of functions logged like check conditions&n;   - 3 Internal structure broken down&n;   - 4 unrolling of loops,...&n; */
DECL|macro|DASD_FLOW_CONTROL
mdefine_line|#define DASD_FLOW_CONTROL 0
macro_line|#if DASD_DEBUG &gt; 0
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
DECL|macro|INTERNAL_ERRMSG
mdefine_line|#define INTERNAL_ERRMSG(x,y...) &bslash;&n;&quot;Internal error: in file &quot; __FILE__ &quot; line: %d: &quot; x, __LINE__, y
DECL|macro|INTERNAL_CHKMSG
mdefine_line|#define INTERNAL_CHKMSG(x,y...) &bslash;&n;&quot;Inconsistency: in file &quot; __FILE__ &quot; line: %d: &quot; x, __LINE__, y
DECL|macro|INTERNAL_FLWMSG
mdefine_line|#define INTERNAL_FLWMSG(x,y...) &bslash;&n;&quot;Flow control: file &quot; __FILE__ &quot; line: %d: &quot; x, __LINE__, y
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
macro_line|#if DASD_DEBUG &gt; 3
DECL|macro|INTERNAL_FLOW
mdefine_line|#define INTERNAL_FLOW(x...) PRINT_ERR ( INTERNAL_FLWMSG ( x ) )
macro_line|#elif DASD_DEBUG &gt; 2
DECL|macro|INTERNAL_FLOW
mdefine_line|#define INTERNAL_FLOW(x...) PRINT_WARN ( INTERNAL_FLWMSG ( x ) )
macro_line|#else
DECL|macro|INTERNAL_FLOW
mdefine_line|#define INTERNAL_FLOW(x...)
macro_line|#endif&t;&t;&t;&t;/* DASD_DEBUG */
macro_line|#if DASD_FLOW_CONTROL &gt; 0
DECL|macro|FUNCTION_ENTRY
mdefine_line|#define FUNCTION_ENTRY(x) INTERNAL_FLOW( x &quot;entered %s&bslash;n&quot;,&quot;&quot; );
macro_line|#else
DECL|macro|FUNCTION_ENTRY
mdefine_line|#define FUNCTION_ENTRY(x)
macro_line|#endif&t;&t;&t;&t;/* DASD_FLOW_CONTROL */
macro_line|#if DASD_FLOW_CONTROL &gt; 1
DECL|macro|FUNCTION_EXIT
mdefine_line|#define FUNCTION_EXIT(x) INTERNAL_FLOW( x &quot;exited %s&bslash;n&quot;,&quot;&quot; );
macro_line|#else
DECL|macro|FUNCTION_EXIT
mdefine_line|#define FUNCTION_EXIT(x)
macro_line|#endif&t;&t;&t;&t;/* DASD_FLOW_CONTROL */
macro_line|#if DASD_FLOW_CONTROL &gt; 2
DECL|macro|FUNCTION_CONTROL
mdefine_line|#define FUNCTION_CONTROL(x...) INTERNAL_FLOW( x );
macro_line|#else
DECL|macro|FUNCTION_CONTROL
mdefine_line|#define FUNCTION_CONTROL(x...)
macro_line|#endif&t;&t;&t;&t;/* DASD_FLOW_CONTROL */
macro_line|#if DASD_FLOW_CONTROL &gt; 3
DECL|macro|LOOP_CONTROL
mdefine_line|#define LOOP_CONTROL(x...) INTERNAL_FLOW( x );
macro_line|#else
DECL|macro|LOOP_CONTROL
mdefine_line|#define LOOP_CONTROL(x...)
macro_line|#endif&t;&t;&t;&t;/* DASD_FLOW_CONTROL */
DECL|macro|DASD_DO_IO_SLEEP
mdefine_line|#define DASD_DO_IO_SLEEP 0x01
DECL|macro|DASD_DO_IO_NOLOCK
mdefine_line|#define DASD_DO_IO_NOLOCK 0x02
DECL|macro|DASD_DO_IO_NODEC
mdefine_line|#define DASD_DO_IO_NODEC 0x04
DECL|macro|DASD_NOT_FORMATTED
mdefine_line|#define DASD_NOT_FORMATTED 0x01
r_extern
id|wait_queue_head_t
id|dasd_waitq
suffix:semicolon
DECL|macro|DEBUG_DASD_MALLOC
macro_line|#undef DEBUG_DASD_MALLOC
macro_line|#ifdef DEBUG_DASD_MALLOC
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
macro_line|#endif&t;&t;&t;&t;/* DEBUG_DASD_MALLOC */
macro_line|#endif&t;&t;&t;&t;/* __KERNEL__ */
macro_line|#endif&t;&t;&t;&t;/* DASD_H */
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-indent-level: 4 &n; * c-brace-imaginary-offset: 0&n; * c-brace-offset: -4&n; * c-argdecl-indent: 4&n; * c-label-offset: -4&n; * c-continued-statement-offset: 4&n; * c-continued-brace-offset: 0&n; * indent-tabs-mode: nil&n; * tab-width: 8&n; * End:&n; */
eof
