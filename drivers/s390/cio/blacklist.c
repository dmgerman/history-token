multiline_comment|/*&n; *  drivers/s390/cio/blacklist.c&n; *   S/390 common I/O routines -- blacklisting of specific devices&n; *   $Revision: 1.31 $&n; *&n; *    Copyright (C) 1999-2002 IBM Deutschland Entwicklung GmbH,&n; *&t;&t;&t;      IBM Corporation&n; *    Author(s): Ingo Adlung (adlung@de.ibm.com)&n; *&t;&t; Cornelia Huck (cohuck@de.ibm.com)&n; *&t;&t; Arnd Bergmann (arndb@de.ibm.com)&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;asm/cio.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;blacklist.h&quot;
macro_line|#include &quot;cio.h&quot;
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
multiline_comment|/*&n; * Function: blacklist_busid&n; * Get devno/busid from given string.&n; * Shamelessly grabbed from dasd_devmap.c.&n; */
r_static
r_inline
r_int
DECL|function|blacklist_busid
id|blacklist_busid
c_func
(paren
r_char
op_star
op_star
id|str
comma
r_int
op_star
id|id0
comma
r_int
op_star
id|id1
comma
r_int
op_star
id|devno
)paren
(brace
r_int
id|val
comma
id|old_style
suffix:semicolon
r_char
op_star
id|sav
suffix:semicolon
id|sav
op_assign
op_star
id|str
suffix:semicolon
multiline_comment|/* check for leading &squot;0x&squot; */
id|old_style
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|str
)paren
(braket
l_int|0
)braket
op_eq
l_char|&squot;0&squot;
op_logical_and
(paren
op_star
id|str
)paren
(braket
l_int|1
)braket
op_eq
l_char|&squot;x&squot;
)paren
(brace
op_star
id|str
op_add_assign
l_int|2
suffix:semicolon
id|old_style
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|isxdigit
c_func
(paren
(paren
op_star
id|str
)paren
(braket
l_int|0
)braket
)paren
)paren
multiline_comment|/* We require at least one hex digit */
r_goto
id|confused
suffix:semicolon
id|val
op_assign
id|simple_strtoul
c_func
(paren
op_star
id|str
comma
id|str
comma
l_int|16
)paren
suffix:semicolon
r_if
c_cond
(paren
id|old_style
op_logical_or
(paren
op_star
id|str
)paren
(braket
l_int|0
)braket
op_ne
l_char|&squot;.&squot;
)paren
(brace
op_star
id|id0
op_assign
op_star
id|id1
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|val
template_param
l_int|0xffff
)paren
r_goto
id|confused
suffix:semicolon
op_star
id|devno
op_assign
id|val
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|str
)paren
(braket
l_int|0
)braket
op_ne
l_char|&squot;,&squot;
op_logical_and
(paren
op_star
id|str
)paren
(braket
l_int|0
)braket
op_ne
l_char|&squot;-&squot;
op_logical_and
(paren
op_star
id|str
)paren
(braket
l_int|0
)braket
op_ne
l_char|&squot;&bslash;n&squot;
op_logical_and
(paren
op_star
id|str
)paren
(braket
l_int|0
)braket
op_ne
l_char|&squot;&bslash;0&squot;
)paren
r_goto
id|confused
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* New style x.y.z busid */
r_if
c_cond
(paren
id|val
template_param
l_int|0xff
)paren
r_goto
id|confused
suffix:semicolon
op_star
id|id0
op_assign
id|val
suffix:semicolon
(paren
op_star
id|str
)paren
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|isxdigit
c_func
(paren
(paren
op_star
id|str
)paren
(braket
l_int|0
)braket
)paren
)paren
multiline_comment|/* We require at least one hex digit */
r_goto
id|confused
suffix:semicolon
id|val
op_assign
id|simple_strtoul
c_func
(paren
op_star
id|str
comma
id|str
comma
l_int|16
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
template_param
l_int|0xff
op_logical_or
(paren
op_star
id|str
)paren
op_increment
(braket
l_int|0
)braket
op_ne
l_char|&squot;.&squot;
)paren
r_goto
id|confused
suffix:semicolon
op_star
id|id1
op_assign
id|val
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|isxdigit
c_func
(paren
(paren
op_star
id|str
)paren
(braket
l_int|0
)braket
)paren
)paren
multiline_comment|/* We require at least one hex digit */
r_goto
id|confused
suffix:semicolon
id|val
op_assign
id|simple_strtoul
c_func
(paren
op_star
id|str
comma
id|str
comma
l_int|16
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
template_param
l_int|0xffff
)paren
r_goto
id|confused
suffix:semicolon
op_star
id|devno
op_assign
id|val
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|str
)paren
(braket
l_int|0
)braket
op_ne
l_char|&squot;,&squot;
op_logical_and
(paren
op_star
id|str
)paren
(braket
l_int|0
)braket
op_ne
l_char|&squot;-&squot;
op_logical_and
(paren
op_star
id|str
)paren
(braket
l_int|0
)braket
op_ne
l_char|&squot;&bslash;n&squot;
op_logical_and
(paren
op_star
id|str
)paren
(braket
l_int|0
)braket
op_ne
l_char|&squot;&bslash;0&squot;
)paren
r_goto
id|confused
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|confused
suffix:colon
id|strsep
c_func
(paren
id|str
comma
l_string|&quot;,&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Invalid cio_ignore parameter &squot;%s&squot;&bslash;n&quot;
comma
id|sav
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
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
comma
id|from_id0
comma
id|to_id0
comma
id|from_id1
comma
id|to_id1
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
id|range_action
id|ra
op_assign
id|action
suffix:semicolon
r_while
c_loop
(paren
op_star
id|str
op_eq
l_char|&squot;,&squot;
)paren
(brace
id|str
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|str
op_eq
l_char|&squot;!&squot;
)paren
(brace
id|ra
op_assign
op_logical_neg
id|action
suffix:semicolon
op_increment
id|str
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Since we have to parse the proc commands and the&n;&t;&t; * kernel arguments we have to check four cases&n;&t;&t; */
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|str
comma
l_string|&quot;all,&quot;
comma
l_int|4
)paren
op_eq
l_int|0
op_logical_or
id|strcmp
c_func
(paren
id|str
comma
l_string|&quot;all&quot;
)paren
op_eq
l_int|0
op_logical_or
id|strncmp
c_func
(paren
id|str
comma
l_string|&quot;all&bslash;n&quot;
comma
l_int|4
)paren
op_eq
l_int|0
op_logical_or
id|strncmp
c_func
(paren
id|str
comma
l_string|&quot;all &quot;
comma
l_int|4
)paren
op_eq
l_int|0
)paren
(brace
id|from
op_assign
l_int|0
suffix:semicolon
id|to
op_assign
id|__MAX_SUBCHANNELS
suffix:semicolon
id|str
op_add_assign
l_int|3
suffix:semicolon
)brace
r_else
(brace
r_int
id|rc
suffix:semicolon
id|rc
op_assign
id|blacklist_busid
c_func
(paren
op_amp
id|str
comma
op_amp
id|from_id0
comma
op_amp
id|from_id1
comma
op_amp
id|from
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
r_continue
suffix:semicolon
id|to
op_assign
id|from
suffix:semicolon
id|to_id0
op_assign
id|from_id0
suffix:semicolon
id|to_id1
op_assign
id|from_id1
suffix:semicolon
r_if
c_cond
(paren
op_star
id|str
op_eq
l_char|&squot;-&squot;
)paren
(brace
id|str
op_increment
suffix:semicolon
id|rc
op_assign
id|blacklist_busid
c_func
(paren
op_amp
id|str
comma
op_amp
id|to_id0
comma
op_amp
id|to_id1
comma
op_amp
id|to
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|str
op_eq
l_char|&squot;-&squot;
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;invalid cio_ignore &quot;
l_string|&quot;parameter &squot;%s&squot;&bslash;n&quot;
comma
id|strsep
c_func
(paren
op_amp
id|str
comma
l_string|&quot;,&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|from_id0
op_ne
id|to_id0
)paren
op_logical_or
(paren
id|from_id1
op_ne
id|to_id1
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;invalid cio_ignore range &quot;
l_string|&quot;%x.%x.%04x-%x.%x.%04x&bslash;n&quot;
comma
id|from_id0
comma
id|from_id1
comma
id|from
comma
id|to_id0
comma
id|to_id1
comma
id|to
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
)brace
multiline_comment|/* FIXME: ignoring id0 and id1 here. */
id|pr_debug
c_func
(paren
l_string|&quot;blacklist_setup: adding range &quot;
l_string|&quot;from 0.0.%04x to 0.0.%04x&bslash;n&quot;
comma
id|from
comma
id|to
)paren
suffix:semicolon
id|blacklist_range
(paren
id|ra
comma
id|from
comma
id|to
)paren
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Parsing the commandline for blacklist parameters, e.g. to blacklist&n; * bus ids 0.0.1234, 0.0.1235 and 0.0.1236, you could use any of:&n; * - cio_ignore=1234-1236&n; * - cio_ignore=0x1234-0x1235,1236&n; * - cio_ignore=0x1234,1235-1236&n; * - cio_ignore=1236 cio_ignore=1234-0x1236&n; * - cio_ignore=1234 cio_ignore=1236 cio_ignore=0x1235&n; * - cio_ignore=0.0.1234-0.0.1236&n; * - cio_ignore=0.0.1234,0x1235,1236&n; * - ...&n; */
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
id|__MAX_SUBCHANNELS
suffix:semicolon
id|irq
op_increment
)paren
(brace
r_int
id|ret
suffix:semicolon
r_struct
id|subchannel
op_star
id|sch
suffix:semicolon
id|sch
op_assign
id|get_subchannel_by_schid
c_func
(paren
id|irq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sch
)paren
(brace
multiline_comment|/* Already known. */
id|put_device
c_func
(paren
op_amp
id|sch-&gt;dev
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|ret
op_assign
id|css_probe_device
c_func
(paren
id|irq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
op_minus
id|ENXIO
)paren
r_break
suffix:semicolon
multiline_comment|/* We&squot;re through. */
r_if
c_cond
(paren
id|ret
op_eq
op_minus
id|ENOMEM
)paren
multiline_comment|/*&n;&t;&t;&t; * Stop validation for now. Bad, but no need for a&n;&t;&t;&t; * panic.&n;&t;&t;&t; */
r_break
suffix:semicolon
)brace
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
multiline_comment|/* &n;&t;&t; * We don&squot;t need to check for known devices since&n;&t;&t; * css_probe_device will handle this correctly. &n;&t;&t; */
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
multiline_comment|/* FIXME: These should be real bus ids and not home-grown ones! */
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
l_int|18
suffix:semicolon
multiline_comment|/* &quot;0.0.ABCD-0.0.EFGH&bslash;n&quot; */
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
l_string|&quot;0.0.%04lx&quot;
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
l_string|&quot;-0.0.%04lx&quot;
comma
op_decrement
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
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
id|__user
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
