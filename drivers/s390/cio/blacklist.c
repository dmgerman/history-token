multiline_comment|/*&n; *  drivers/s390/cio/blacklist.c&n; *   S/390 common I/O routines -- blacklisting of specific devices&n; *   $Revision: 1.22 $&n; *&n; *    Copyright (C) 1999-2002 IBM Deutschland Entwicklung GmbH,&n; *&t;&t;&t;      IBM Corporation&n; *    Author(s): Ingo Adlung (adlung@de.ibm.com)&n; *&t;&t; Cornelia Huck (cohuck@de.ibm.com)&n; *&t;&t; Arnd Bergmann (arndb@de.ibm.com)&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;blacklist.h&quot;
macro_line|#include &quot;cio_debug.h&quot;
macro_line|#include &quot;css.h&quot;
multiline_comment|/*&n; * &quot;Blacklisting&quot; of certain devices:&n; * Device numbers given in the commandline as cio_ignore=... won&squot;t be known&n; * to Linux.&n; *&n; * These can be single devices or ranges of devices&n; */
multiline_comment|/* 65536 bits to indicate if a devno is blacklisted or not */
DECL|macro|__BL_DEV_WORDS
mdefine_line|#define __BL_DEV_WORDS (__MAX_SUBCHANNELS + (8*sizeof(long) - 1) / &bslash;&n;&t;&t;&t; (8*sizeof(long)))
DECL|variable|bl_dev
r_static
r_int
r_int
id|bl_dev
(braket
id|__BL_DEV_WORDS
)braket
suffix:semicolon
DECL|enumerator|add
DECL|enumerator|free
DECL|typedef|range_action
r_typedef
r_enum
(brace
id|add
comma
id|free
)brace
id|range_action
suffix:semicolon
multiline_comment|/*&n; * Function: blacklist_range&n; * (Un-)blacklist the devices from-to&n; */
r_static
r_inline
r_void
DECL|function|blacklist_range
id|blacklist_range
(paren
id|range_action
id|action
comma
r_int
r_int
id|from
comma
r_int
r_int
id|to
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|to
)paren
id|to
op_assign
id|from
suffix:semicolon
r_if
c_cond
(paren
id|from
OG
id|to
op_logical_or
id|to
OG
id|__MAX_SUBCHANNELS
)paren
(brace
id|printk
(paren
id|KERN_WARNING
l_string|&quot;Invalid blacklist range &quot;
l_string|&quot;0x%04x to 0x%04x, skipping&bslash;n&quot;
comma
id|from
comma
id|to
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_for
c_loop
(paren
suffix:semicolon
id|from
op_le
id|to
suffix:semicolon
id|from
op_increment
)paren
(brace
r_if
c_cond
(paren
id|action
op_eq
id|add
)paren
id|set_bit
(paren
id|from
comma
id|bl_dev
)paren
suffix:semicolon
r_else
id|clear_bit
(paren
id|from
comma
id|bl_dev
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * function: blacklist_strtoul&n; * Strip leading &squot;0x&squot; and interpret the values as Hex&n; */
r_static
r_inline
r_int
DECL|function|blacklist_strtoul
id|blacklist_strtoul
(paren
r_const
r_char
op_star
id|str
comma
r_char
op_star
op_star
id|stra
)paren
(brace
r_if
c_cond
(paren
op_star
id|str
op_eq
l_char|&squot;0&squot;
)paren
(brace
r_if
c_cond
(paren
op_star
(paren
op_increment
id|str
)paren
op_eq
l_char|&squot;x&squot;
)paren
multiline_comment|/* strip leading zero */
id|str
op_increment
suffix:semicolon
multiline_comment|/* strip leading x */
)brace
r_return
id|simple_strtoul
(paren
id|str
comma
id|stra
comma
l_int|16
)paren
suffix:semicolon
multiline_comment|/* interpret anything as hex */
)brace
r_static
r_inline
r_int
DECL|function|blacklist_parse_parameters
id|blacklist_parse_parameters
(paren
r_char
op_star
id|str
comma
id|range_action
id|action
)paren
(brace
r_int
r_int
id|from
comma
id|to
suffix:semicolon
r_while
c_loop
(paren
op_star
id|str
op_ne
l_int|0
op_logical_and
op_star
id|str
op_ne
l_char|&squot;&bslash;n&squot;
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|isxdigit
c_func
(paren
op_star
id|str
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;blacklist_setup: error parsing &quot;
l_string|&quot;&bslash;&quot;%s&bslash;&quot;&bslash;n&quot;
comma
id|str
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|from
op_assign
id|blacklist_strtoul
(paren
id|str
comma
op_amp
id|str
)paren
suffix:semicolon
id|to
op_assign
(paren
op_star
id|str
op_eq
l_char|&squot;-&squot;
)paren
ques
c_cond
id|blacklist_strtoul
(paren
id|str
op_plus
l_int|1
comma
op_amp
id|str
)paren
suffix:colon
id|from
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;blacklist_setup: adding range &quot;
l_string|&quot;from 0x%04x to 0x%04x&bslash;n&quot;
comma
id|from
comma
id|to
)paren
suffix:semicolon
id|blacklist_range
(paren
id|action
comma
id|from
comma
id|to
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|str
op_eq
l_char|&squot;,&squot;
)paren
id|str
op_increment
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Parsing the commandline for blacklist parameters, e.g. to blacklist&n; * device IDs 0x1234, 0x1235 and 0x1236, you could use any of:&n; * - cio_ignore=1234-1236&n; * - cio_ignore=0x1234-0x1235,1236&n; * - cio_ignore=0x1234,1235-1236&n; * - cio_ignore=1236 cio_ignore=1234-0x1236&n; * - cio_ignore=1234 cio_ignore=1236 cio_ignore=0x1235&n; * - ...&n; */
r_static
r_int
id|__init
DECL|function|blacklist_setup
id|blacklist_setup
(paren
r_char
op_star
id|str
)paren
(brace
id|CIO_MSG_EVENT
c_func
(paren
l_int|6
comma
l_string|&quot;Reading blacklist parameters&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|blacklist_parse_parameters
(paren
id|str
comma
id|add
)paren
suffix:semicolon
)brace
id|__setup
(paren
l_string|&quot;cio_ignore=&quot;
comma
id|blacklist_setup
)paren
suffix:semicolon
multiline_comment|/* Checking if devices are blacklisted */
multiline_comment|/*&n; * Function: is_blacklisted&n; * Returns 1 if the given devicenumber can be found in the blacklist,&n; * otherwise 0.&n; * Used by validate_subchannel()&n; */
r_int
DECL|function|is_blacklisted
id|is_blacklisted
(paren
r_int
id|devno
)paren
(brace
r_return
id|test_bit
(paren
id|devno
comma
id|bl_dev
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_PROC_FS
multiline_comment|/*&n; * Function: s390_redo_validation&n; * Look for no longer blacklisted devices&n; * FIXME: there must be a better way to do this */
r_static
r_inline
r_void
DECL|function|s390_redo_validation
id|s390_redo_validation
(paren
r_void
)paren
(brace
r_int
id|irq
suffix:semicolon
id|CIO_TRACE_EVENT
(paren
l_int|0
comma
l_string|&quot;redoval&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|irq
op_assign
l_int|0
suffix:semicolon
id|irq
op_le
id|highest_subchannel
suffix:semicolon
id|irq
op_increment
)paren
id|css_probe_device
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Function: blacklist_parse_proc_parameters&n; * parse the stuff which is piped to /proc/cio_ignore&n; */
r_static
r_inline
r_void
DECL|function|blacklist_parse_proc_parameters
id|blacklist_parse_proc_parameters
(paren
r_char
op_star
id|buf
)paren
(brace
r_if
c_cond
(paren
id|strncmp
(paren
id|buf
comma
l_string|&quot;free &quot;
comma
l_int|5
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|strstr
(paren
id|buf
op_plus
l_int|5
comma
l_string|&quot;all&quot;
)paren
)paren
id|blacklist_range
(paren
id|free
comma
l_int|0
comma
id|__MAX_SUBCHANNELS
)paren
suffix:semicolon
r_else
id|blacklist_parse_parameters
(paren
id|buf
op_plus
l_int|5
comma
id|free
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|strncmp
(paren
id|buf
comma
l_string|&quot;add &quot;
comma
l_int|4
)paren
op_eq
l_int|0
)paren
(brace
multiline_comment|/* FIXME: the old code was checking if the new bl&squot;ed&n;&t;&t; * devices are already known to the system so&n;&t;&t; * validate_subchannel would still give a working&n;&t;&t; * status. is that necessary? */
id|blacklist_parse_parameters
(paren
id|buf
op_plus
l_int|4
comma
id|add
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
(paren
id|KERN_WARNING
l_string|&quot;cio_ignore: Parse error; &bslash;n&quot;
id|KERN_WARNING
l_string|&quot;try using &squot;free all|&lt;devno-range&gt;,&quot;
l_string|&quot;&lt;devno-range&gt;,...&squot;&bslash;n&quot;
id|KERN_WARNING
l_string|&quot;or &squot;add &lt;devno-range&gt;,&quot;
l_string|&quot;&lt;devno-range&gt;,...&squot;&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|s390_redo_validation
(paren
)paren
suffix:semicolon
)brace
DECL|function|cio_ignore_read
r_static
r_int
id|cio_ignore_read
(paren
r_char
op_star
id|page
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|off
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
(brace
r_const
r_int
r_int
id|entry_size
op_assign
l_int|14
suffix:semicolon
multiline_comment|/* &quot;0xABCD-0xEFGH&bslash;n&quot; */
r_int
id|devno
suffix:semicolon
r_int
id|len
suffix:semicolon
id|len
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|devno
op_assign
id|off
suffix:semicolon
multiline_comment|/* abuse the page variable&n;&t;&t;&t;   * as counter, see fs/proc/generic.c */
id|devno
op_le
id|__MAX_SUBCHANNELS
op_logical_and
id|len
op_plus
id|entry_size
OL
id|count
suffix:semicolon
id|devno
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|devno
comma
id|bl_dev
)paren
)paren
r_continue
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|len
comma
l_string|&quot;0x%04lx&quot;
comma
id|devno
)paren
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|devno
op_plus
l_int|1
comma
id|bl_dev
)paren
)paren
(brace
multiline_comment|/* print range */
r_while
c_loop
(paren
op_increment
id|devno
OL
id|__MAX_SUBCHANNELS
)paren
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|devno
comma
id|bl_dev
)paren
)paren
r_break
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|len
comma
l_string|&quot;-0x%04lx&quot;
comma
id|devno
)paren
suffix:semicolon
)brace
id|len
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|len
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|devno
op_le
id|__MAX_SUBCHANNELS
)paren
op_star
id|eof
op_assign
l_int|1
suffix:semicolon
op_star
id|start
op_assign
(paren
r_char
op_star
)paren
(paren
id|devno
op_minus
id|off
)paren
suffix:semicolon
multiline_comment|/* number of checked entries */
r_return
id|len
suffix:semicolon
)brace
DECL|function|cio_ignore_write
r_static
r_int
id|cio_ignore_write
(paren
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
r_int
id|user_len
comma
r_void
op_star
id|data
)paren
(brace
r_char
op_star
id|buf
suffix:semicolon
r_if
c_cond
(paren
id|user_len
OG
l_int|65536
)paren
id|user_len
op_assign
l_int|65536
suffix:semicolon
id|buf
op_assign
id|vmalloc
(paren
id|user_len
op_plus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* maybe better use the stack? */
r_if
c_cond
(paren
id|buf
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
id|strncpy_from_user
(paren
id|buf
comma
id|user_buf
comma
id|user_len
)paren
OL
l_int|0
)paren
(brace
id|vfree
(paren
id|buf
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|buf
(braket
id|user_len
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|blacklist_parse_proc_parameters
(paren
id|buf
)paren
suffix:semicolon
id|vfree
(paren
id|buf
)paren
suffix:semicolon
r_return
id|user_len
suffix:semicolon
)brace
r_static
r_int
DECL|function|cio_ignore_proc_init
id|cio_ignore_proc_init
(paren
r_void
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|entry
suffix:semicolon
id|entry
op_assign
id|create_proc_entry
(paren
l_string|&quot;cio_ignore&quot;
comma
id|S_IFREG
op_or
id|S_IRUGO
op_or
id|S_IWUSR
comma
op_amp
id|proc_root
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|entry
)paren
r_return
l_int|0
suffix:semicolon
id|entry-&gt;read_proc
op_assign
id|cio_ignore_read
suffix:semicolon
id|entry-&gt;write_proc
op_assign
id|cio_ignore_write
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|cio_ignore_proc_init
id|__initcall
(paren
id|cio_ignore_proc_init
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_PROC_FS */
eof
