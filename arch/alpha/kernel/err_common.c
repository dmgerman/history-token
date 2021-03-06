multiline_comment|/*&n; *&t;linux/arch/alpha/kernel/err_common.c&n; *&n; *&t;Copyright (C) 2000 Jeff Wiedemeier (Compaq Computer Corporation)&n; *&n; *&t;Error handling code supporting Alpha systems&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/hwrpb.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/err_common.h&gt;
macro_line|#include &quot;err_impl.h&quot;
macro_line|#include &quot;proto.h&quot;
multiline_comment|/*&n; * err_print_prefix -- error handling print routines should prefix&n; * all prints with this&n; */
DECL|variable|err_print_prefix
r_char
op_star
id|err_print_prefix
op_assign
id|KERN_NOTICE
suffix:semicolon
"&f;"
multiline_comment|/*&n; * Generic&n; */
r_void
DECL|function|mchk_dump_mem
id|mchk_dump_mem
c_func
(paren
r_void
op_star
id|data
comma
r_int
id|length
comma
r_char
op_star
op_star
id|annotation
)paren
(brace
r_int
r_int
op_star
id|ldata
op_assign
id|data
suffix:semicolon
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
(paren
id|i
op_star
r_sizeof
(paren
op_star
id|ldata
)paren
)paren
OL
id|length
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|annotation
op_logical_and
op_logical_neg
id|annotation
(braket
id|i
)braket
)paren
id|annotation
op_assign
l_int|NULL
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s    %08x: %016lx    %s&bslash;n&quot;
comma
id|err_print_prefix
comma
(paren
r_int
)paren
(paren
id|i
op_star
r_sizeof
(paren
op_star
id|ldata
)paren
)paren
comma
id|ldata
(braket
id|i
)braket
comma
id|annotation
ques
c_cond
id|annotation
(braket
id|i
)braket
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
)brace
)brace
r_void
DECL|function|mchk_dump_logout_frame
id|mchk_dump_logout_frame
c_func
(paren
r_struct
id|el_common
op_star
id|mchk_header
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s  -- Frame Header --&bslash;n&quot;
l_string|&quot;    Frame Size:   %d (0x%x) bytes&bslash;n&quot;
l_string|&quot;    Flags:        %s%s&bslash;n&quot;
l_string|&quot;    MCHK Code:    0x%x&bslash;n&quot;
l_string|&quot;    Frame Rev:    %d&bslash;n&quot;
l_string|&quot;    Proc Offset:  0x%08x&bslash;n&quot;
l_string|&quot;    Sys Offset:   0x%08x&bslash;n&quot;
l_string|&quot;  -- Processor Region --&bslash;n&quot;
comma
id|err_print_prefix
comma
id|mchk_header-&gt;size
comma
id|mchk_header-&gt;size
comma
id|mchk_header-&gt;retry
ques
c_cond
l_string|&quot;RETRY &quot;
suffix:colon
l_string|&quot;&quot;
comma
id|mchk_header-&gt;err2
ques
c_cond
l_string|&quot;SECOND_ERR &quot;
suffix:colon
l_string|&quot;&quot;
comma
id|mchk_header-&gt;code
comma
id|mchk_header-&gt;frame_rev
comma
id|mchk_header-&gt;proc_offset
comma
id|mchk_header-&gt;sys_offset
)paren
suffix:semicolon
id|mchk_dump_mem
c_func
(paren
(paren
r_void
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|mchk_header
op_plus
id|mchk_header-&gt;proc_offset
)paren
comma
id|mchk_header-&gt;sys_offset
op_minus
id|mchk_header-&gt;proc_offset
comma
l_int|NULL
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s  -- System Region --&bslash;n&quot;
comma
id|err_print_prefix
)paren
suffix:semicolon
id|mchk_dump_mem
c_func
(paren
(paren
r_void
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|mchk_header
op_plus
id|mchk_header-&gt;sys_offset
)paren
comma
id|mchk_header-&gt;size
op_minus
id|mchk_header-&gt;sys_offset
comma
l_int|NULL
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s  -- End of Frame --&bslash;n&quot;
comma
id|err_print_prefix
)paren
suffix:semicolon
)brace
"&f;"
multiline_comment|/*&n; * Console Data Log&n; */
multiline_comment|/* Data */
DECL|variable|subpacket_handler_list
r_static
r_struct
id|el_subpacket_handler
op_star
id|subpacket_handler_list
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|subpacket_annotation_list
r_static
r_struct
id|el_subpacket_annotation
op_star
id|subpacket_annotation_list
op_assign
l_int|NULL
suffix:semicolon
r_static
r_struct
id|el_subpacket
op_star
DECL|function|el_process_header_subpacket
id|el_process_header_subpacket
c_func
(paren
r_struct
id|el_subpacket
op_star
id|header
)paren
(brace
r_union
id|el_timestamp
id|timestamp
suffix:semicolon
r_char
op_star
id|name
op_assign
l_string|&quot;UNKNOWN EVENT&quot;
suffix:semicolon
r_int
id|packet_count
op_assign
l_int|0
suffix:semicolon
r_int
id|length
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|header
op_member_access_from_pointer
r_class
op_ne
id|EL_CLASS__HEADER
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s** Unexpected header CLASS %d TYPE %d, aborting&bslash;n&quot;
comma
id|err_print_prefix
comma
id|header
op_member_access_from_pointer
r_class
comma
id|header-&gt;type
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|header-&gt;type
)paren
(brace
r_case
id|EL_TYPE__HEADER__SYSTEM_ERROR_FRAME
suffix:colon
id|name
op_assign
l_string|&quot;SYSTEM ERROR&quot;
suffix:semicolon
id|length
op_assign
id|header-&gt;by_type.sys_err.frame_length
suffix:semicolon
id|packet_count
op_assign
id|header-&gt;by_type.sys_err.frame_packet_count
suffix:semicolon
id|timestamp.as_int
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|EL_TYPE__HEADER__SYSTEM_EVENT_FRAME
suffix:colon
id|name
op_assign
l_string|&quot;SYSTEM EVENT&quot;
suffix:semicolon
id|length
op_assign
id|header-&gt;by_type.sys_event.frame_length
suffix:semicolon
id|packet_count
op_assign
id|header-&gt;by_type.sys_event.frame_packet_count
suffix:semicolon
id|timestamp
op_assign
id|header-&gt;by_type.sys_event.timestamp
suffix:semicolon
r_break
suffix:semicolon
r_case
id|EL_TYPE__HEADER__HALT_FRAME
suffix:colon
id|name
op_assign
l_string|&quot;ERROR HALT&quot;
suffix:semicolon
id|length
op_assign
id|header-&gt;by_type.err_halt.frame_length
suffix:semicolon
id|packet_count
op_assign
id|header-&gt;by_type.err_halt.frame_packet_count
suffix:semicolon
id|timestamp
op_assign
id|header-&gt;by_type.err_halt.timestamp
suffix:semicolon
r_break
suffix:semicolon
r_case
id|EL_TYPE__HEADER__LOGOUT_FRAME
suffix:colon
id|name
op_assign
l_string|&quot;LOGOUT FRAME&quot;
suffix:semicolon
id|length
op_assign
id|header-&gt;by_type.logout_header.frame_length
suffix:semicolon
id|packet_count
op_assign
l_int|1
suffix:semicolon
id|timestamp.as_int
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* Unknown */
id|printk
c_func
(paren
l_string|&quot;%s** Unknown header - CLASS %d TYPE %d, aborting&bslash;n&quot;
comma
id|err_print_prefix
comma
id|header
op_member_access_from_pointer
r_class
comma
id|header-&gt;type
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;%s*** %s:&bslash;n&quot;
l_string|&quot;  CLASS %d, TYPE %d&bslash;n&quot;
comma
id|err_print_prefix
comma
id|name
comma
id|header
op_member_access_from_pointer
r_class
comma
id|header-&gt;type
)paren
suffix:semicolon
id|el_print_timestamp
c_func
(paren
op_amp
id|timestamp
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Process the subpackets&n;&t; */
id|el_process_subpackets
c_func
(paren
id|header
comma
id|packet_count
)paren
suffix:semicolon
multiline_comment|/* return the next header */
id|header
op_assign
(paren
r_struct
id|el_subpacket
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|header
op_plus
id|header-&gt;length
op_plus
id|length
)paren
suffix:semicolon
r_return
id|header
suffix:semicolon
)brace
r_static
r_struct
id|el_subpacket
op_star
DECL|function|el_process_subpacket_reg
id|el_process_subpacket_reg
c_func
(paren
r_struct
id|el_subpacket
op_star
id|header
)paren
(brace
r_struct
id|el_subpacket
op_star
id|next
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|el_subpacket_handler
op_star
id|h
op_assign
id|subpacket_handler_list
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|h
op_logical_and
id|h
op_member_access_from_pointer
r_class
op_ne
id|header
op_member_access_from_pointer
r_class
suffix:semicolon
id|h
op_assign
id|h-&gt;next
)paren
suffix:semicolon
r_if
c_cond
(paren
id|h
)paren
id|next
op_assign
id|h
op_member_access_from_pointer
id|handler
c_func
(paren
id|header
)paren
suffix:semicolon
r_return
id|next
suffix:semicolon
)brace
r_void
DECL|function|el_print_timestamp
id|el_print_timestamp
c_func
(paren
r_union
id|el_timestamp
op_star
id|timestamp
)paren
(brace
r_if
c_cond
(paren
id|timestamp-&gt;as_int
)paren
id|printk
c_func
(paren
l_string|&quot;%s  TIMESTAMP: %d/%d/%02d %d:%02d:%0d&bslash;n&quot;
comma
id|err_print_prefix
comma
id|timestamp-&gt;b.month
comma
id|timestamp-&gt;b.day
comma
id|timestamp-&gt;b.year
comma
id|timestamp-&gt;b.hour
comma
id|timestamp-&gt;b.minute
comma
id|timestamp-&gt;b.second
)paren
suffix:semicolon
)brace
r_void
DECL|function|el_process_subpackets
id|el_process_subpackets
c_func
(paren
r_struct
id|el_subpacket
op_star
id|header
comma
r_int
id|packet_count
)paren
(brace
r_struct
id|el_subpacket
op_star
id|subpacket
suffix:semicolon
r_int
id|i
suffix:semicolon
id|subpacket
op_assign
(paren
r_struct
id|el_subpacket
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|header
op_plus
id|header-&gt;length
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|subpacket
op_logical_and
id|i
OL
id|packet_count
suffix:semicolon
id|i
op_increment
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%sPROCESSING SUBPACKET %d&bslash;n&quot;
comma
id|err_print_prefix
comma
id|i
)paren
suffix:semicolon
id|subpacket
op_assign
id|el_process_subpacket
c_func
(paren
id|subpacket
)paren
suffix:semicolon
)brace
)brace
r_struct
id|el_subpacket
op_star
DECL|function|el_process_subpacket
id|el_process_subpacket
c_func
(paren
r_struct
id|el_subpacket
op_star
id|header
)paren
(brace
r_struct
id|el_subpacket
op_star
id|next
op_assign
l_int|NULL
suffix:semicolon
r_switch
c_cond
(paren
id|header
op_member_access_from_pointer
r_class
)paren
(brace
r_case
id|EL_CLASS__TERMINATION
suffix:colon
multiline_comment|/* Termination packet, there are no more */
r_break
suffix:semicolon
r_case
id|EL_CLASS__HEADER
suffix:colon
id|next
op_assign
id|el_process_header_subpacket
c_func
(paren
id|header
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
r_if
c_cond
(paren
l_int|NULL
op_eq
(paren
id|next
op_assign
id|el_process_subpacket_reg
c_func
(paren
id|header
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s** Unexpected header CLASS %d TYPE %d&quot;
l_string|&quot; -- aborting.&bslash;n&quot;
comma
id|err_print_prefix
comma
id|header
op_member_access_from_pointer
r_class
comma
id|header-&gt;type
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_return
id|next
suffix:semicolon
)brace
r_void
DECL|function|el_annotate_subpacket
id|el_annotate_subpacket
c_func
(paren
r_struct
id|el_subpacket
op_star
id|header
)paren
(brace
r_struct
id|el_subpacket_annotation
op_star
id|a
suffix:semicolon
r_char
op_star
op_star
id|annotation
op_assign
l_int|NULL
suffix:semicolon
r_for
c_loop
(paren
id|a
op_assign
id|subpacket_annotation_list
suffix:semicolon
id|a
suffix:semicolon
id|a
op_assign
id|a-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|a
op_member_access_from_pointer
r_class
op_eq
id|header
op_member_access_from_pointer
r_class
op_logical_and
id|a-&gt;type
op_eq
id|header-&gt;type
op_logical_and
id|a-&gt;revision
op_eq
id|header-&gt;revision
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * We found the annotation&n;&t;&t;&t; */
id|annotation
op_assign
id|a-&gt;annotation
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s  %s&bslash;n&quot;
comma
id|err_print_prefix
comma
id|a-&gt;description
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|mchk_dump_mem
c_func
(paren
id|header
comma
id|header-&gt;length
comma
id|annotation
)paren
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|cdl_process_console_data_log
id|cdl_process_console_data_log
c_func
(paren
r_int
id|cpu
comma
r_struct
id|percpu_struct
op_star
id|pcpu
)paren
(brace
r_struct
id|el_subpacket
op_star
id|header
op_assign
(paren
r_struct
id|el_subpacket
op_star
)paren
(paren
id|IDENT_ADDR
op_or
id|pcpu-&gt;console_data_log_pa
)paren
suffix:semicolon
r_int
id|err
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s******* CONSOLE DATA LOG FOR CPU %d. *******&bslash;n&quot;
l_string|&quot;*** Error(s) were logged on a previous boot&bslash;n&quot;
comma
id|err_print_prefix
comma
id|cpu
)paren
suffix:semicolon
r_for
c_loop
(paren
id|err
op_assign
l_int|0
suffix:semicolon
id|header
op_logical_and
(paren
id|header
op_member_access_from_pointer
r_class
op_ne
id|EL_CLASS__TERMINATION
)paren
suffix:semicolon
id|err
op_increment
)paren
id|header
op_assign
id|el_process_subpacket
c_func
(paren
id|header
)paren
suffix:semicolon
multiline_comment|/* let the console know it&squot;s ok to clear the error(s) at restart */
id|pcpu-&gt;console_data_log_pa
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s*** %d total error(s) logged&bslash;n&quot;
l_string|&quot;**** END OF CONSOLE DATA LOG FOR CPU %d ****&bslash;n&quot;
comma
id|err_print_prefix
comma
id|err
comma
id|cpu
)paren
suffix:semicolon
)brace
r_void
id|__init
DECL|function|cdl_check_console_data_log
id|cdl_check_console_data_log
c_func
(paren
r_void
)paren
(brace
r_struct
id|percpu_struct
op_star
id|pcpu
suffix:semicolon
r_int
r_int
id|cpu
suffix:semicolon
r_for
c_loop
(paren
id|cpu
op_assign
l_int|0
suffix:semicolon
id|cpu
OL
id|hwrpb-&gt;nr_processors
suffix:semicolon
id|cpu
op_increment
)paren
(brace
id|pcpu
op_assign
(paren
r_struct
id|percpu_struct
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|hwrpb
op_plus
id|hwrpb-&gt;processor_offset
op_plus
id|cpu
op_star
id|hwrpb-&gt;processor_size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pcpu-&gt;console_data_log_pa
)paren
id|cdl_process_console_data_log
c_func
(paren
id|cpu
comma
id|pcpu
)paren
suffix:semicolon
)brace
)brace
r_int
id|__init
DECL|function|cdl_register_subpacket_annotation
id|cdl_register_subpacket_annotation
c_func
(paren
r_struct
id|el_subpacket_annotation
op_star
r_new
)paren
(brace
r_struct
id|el_subpacket_annotation
op_star
id|a
op_assign
id|subpacket_annotation_list
suffix:semicolon
r_if
c_cond
(paren
id|a
op_eq
l_int|NULL
)paren
id|subpacket_annotation_list
op_assign
r_new
suffix:semicolon
r_else
(brace
r_for
c_loop
(paren
suffix:semicolon
id|a-&gt;next
op_ne
l_int|NULL
suffix:semicolon
id|a
op_assign
id|a-&gt;next
)paren
(brace
r_if
c_cond
(paren
(paren
id|a
op_member_access_from_pointer
r_class
op_eq
r_new
op_member_access_from_pointer
r_class
op_logical_and
id|a-&gt;type
op_eq
r_new
op_member_access_from_pointer
id|type
)paren
op_logical_or
id|a
op_eq
r_new
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Attempted to re-register &quot;
l_string|&quot;subpacket annotation&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
id|a-&gt;next
op_assign
r_new
suffix:semicolon
)brace
r_new
op_member_access_from_pointer
id|next
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_int
id|__init
DECL|function|cdl_register_subpacket_handler
id|cdl_register_subpacket_handler
c_func
(paren
r_struct
id|el_subpacket_handler
op_star
r_new
)paren
(brace
r_struct
id|el_subpacket_handler
op_star
id|h
op_assign
id|subpacket_handler_list
suffix:semicolon
r_if
c_cond
(paren
id|h
op_eq
l_int|NULL
)paren
id|subpacket_handler_list
op_assign
r_new
suffix:semicolon
r_else
(brace
r_for
c_loop
(paren
suffix:semicolon
id|h-&gt;next
op_ne
l_int|NULL
suffix:semicolon
id|h
op_assign
id|h-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|h
op_member_access_from_pointer
r_class
op_eq
r_new
op_member_access_from_pointer
r_class
op_logical_or
id|h
op_eq
r_new
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Attempted to re-register &quot;
l_string|&quot;subpacket handler&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
id|h-&gt;next
op_assign
r_new
suffix:semicolon
)brace
r_new
op_member_access_from_pointer
id|next
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
