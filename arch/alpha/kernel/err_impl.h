multiline_comment|/*&n; *&t;linux/arch/alpha/kernel/err_impl.h&n; *&n; *&t;Copyright (C) 2000 Jeff Wiedemeier (Compaq Computer Corporation)&n; *&n; *&t;Contains declarations and macros to support Alpha error handling&n; * &t;implementations.&n; */
multiline_comment|/*&n; * SCB Vector definitions&n; */
DECL|macro|SCB_Q_SYSERR
mdefine_line|#define SCB_Q_SYSERR&t;0x620
DECL|macro|SCB_Q_PROCERR
mdefine_line|#define SCB_Q_PROCERR&t;0x630
DECL|macro|SCB_Q_SYSMCHK
mdefine_line|#define SCB_Q_SYSMCHK&t;0x660
DECL|macro|SCB_Q_PROCMCHK
mdefine_line|#define SCB_Q_PROCMCHK&t;0x670
DECL|macro|SCB_Q_SYSEVENT
mdefine_line|#define SCB_Q_SYSEVENT&t;0x680
multiline_comment|/*&n; * Disposition definitions for logout frame parser&n; */
DECL|macro|MCHK_DISPOSITION_UNKNOWN_ERROR
mdefine_line|#define MCHK_DISPOSITION_UNKNOWN_ERROR&t;&t;0x00
DECL|macro|MCHK_DISPOSITION_REPORT
mdefine_line|#define MCHK_DISPOSITION_REPORT&t;&t;&t;0x01
DECL|macro|MCHK_DISPOSITION_DISMISS
mdefine_line|#define MCHK_DISPOSITION_DISMISS&t;&t;0x02
multiline_comment|/*&n; * Error Log definitions&n; */
multiline_comment|/*&n; * Types&n; */
DECL|macro|EL_CLASS__TERMINATION
mdefine_line|#define EL_CLASS__TERMINATION&t;&t;(0)
DECL|macro|EL_TYPE__TERMINATION__TERMINATION
macro_line|#  define EL_TYPE__TERMINATION__TERMINATION&t;&t;(0)
DECL|macro|EL_CLASS__HEADER
mdefine_line|#define EL_CLASS__HEADER&t;&t;(5)
DECL|macro|EL_TYPE__HEADER__SYSTEM_ERROR_FRAME
macro_line|#  define EL_TYPE__HEADER__SYSTEM_ERROR_FRAME&t;&t;(1)
DECL|macro|EL_TYPE__HEADER__SYSTEM_EVENT_FRAME
macro_line|#  define EL_TYPE__HEADER__SYSTEM_EVENT_FRAME&t;&t;(2)
DECL|macro|EL_TYPE__HEADER__HALT_FRAME
macro_line|#  define EL_TYPE__HEADER__HALT_FRAME&t;&t;&t;(3)
DECL|macro|EL_TYPE__HEADER__LOGOUT_FRAME
macro_line|#  define EL_TYPE__HEADER__LOGOUT_FRAME&t;&t;&t;(19)
DECL|macro|EL_CLASS__GENERAL_NOTIFICATION
mdefine_line|#define EL_CLASS__GENERAL_NOTIFICATION&t;(9)
DECL|macro|EL_CLASS__PCI_ERROR_FRAME
mdefine_line|#define EL_CLASS__PCI_ERROR_FRAME&t;(11)
DECL|macro|EL_CLASS__REGATTA_FAMILY
mdefine_line|#define EL_CLASS__REGATTA_FAMILY&t;(12)
DECL|macro|EL_TYPE__REGATTA__PROCESSOR_ERROR_FRAME
macro_line|#  define EL_TYPE__REGATTA__PROCESSOR_ERROR_FRAME&t;(1)
DECL|macro|EL_TYPE__REGATTA__SYSTEM_ERROR_FRAME
macro_line|#  define EL_TYPE__REGATTA__SYSTEM_ERROR_FRAME&t;&t;(2)
DECL|macro|EL_TYPE__REGATTA__ENVIRONMENTAL_FRAME
macro_line|#  define EL_TYPE__REGATTA__ENVIRONMENTAL_FRAME&t;&t;(3)
DECL|macro|EL_TYPE__REGATTA__TITAN_PCHIP0_EXTENDED
macro_line|#  define EL_TYPE__REGATTA__TITAN_PCHIP0_EXTENDED&t;(8)
DECL|macro|EL_TYPE__REGATTA__TITAN_PCHIP1_EXTENDED
macro_line|#  define EL_TYPE__REGATTA__TITAN_PCHIP1_EXTENDED&t;(9)
DECL|macro|EL_TYPE__REGATTA__TITAN_MEMORY_EXTENDED
macro_line|#  define EL_TYPE__REGATTA__TITAN_MEMORY_EXTENDED&t;(10)
DECL|macro|EL_TYPE__REGATTA__PROCESSOR_DBL_ERROR_HALT
macro_line|#  define EL_TYPE__REGATTA__PROCESSOR_DBL_ERROR_HALT&t;(11)
DECL|macro|EL_TYPE__REGATTA__SYSTEM_DBL_ERROR_HALT
macro_line|#  define EL_TYPE__REGATTA__SYSTEM_DBL_ERROR_HALT&t;(12)
DECL|macro|EL_CLASS__PAL
mdefine_line|#define EL_CLASS__PAL                   (14)
DECL|macro|EL_TYPE__PAL__LOGOUT_FRAME
macro_line|#  define EL_TYPE__PAL__LOGOUT_FRAME                    (1)
DECL|macro|EL_TYPE__PAL__EV7_PROCESSOR
macro_line|#  define EL_TYPE__PAL__EV7_PROCESSOR&t;&t;&t;(4)
DECL|macro|EL_TYPE__PAL__EV7_ZBOX
macro_line|#  define EL_TYPE__PAL__EV7_ZBOX&t;&t;&t;(5)
DECL|macro|EL_TYPE__PAL__EV7_RBOX
macro_line|#  define EL_TYPE__PAL__EV7_RBOX&t;&t;&t;(6)
DECL|macro|EL_TYPE__PAL__EV7_IO
macro_line|#  define EL_TYPE__PAL__EV7_IO&t;&t;&t;&t;(7)
DECL|union|el_timestamp
r_union
id|el_timestamp
(brace
r_struct
(brace
DECL|member|second
id|u8
id|second
suffix:semicolon
DECL|member|minute
id|u8
id|minute
suffix:semicolon
DECL|member|hour
id|u8
id|hour
suffix:semicolon
DECL|member|day
id|u8
id|day
suffix:semicolon
DECL|member|month
id|u8
id|month
suffix:semicolon
DECL|member|year
id|u8
id|year
suffix:semicolon
DECL|member|b
)brace
id|b
suffix:semicolon
DECL|member|as_int
id|u64
id|as_int
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|el_subpacket
r_struct
id|el_subpacket
(brace
DECL|member|length
id|u16
id|length
suffix:semicolon
multiline_comment|/* length of header (in bytes)&t;*/
DECL|member|class
id|u16
r_class
suffix:semicolon
multiline_comment|/* header class and type...   &t;*/
DECL|member|type
id|u16
id|type
suffix:semicolon
multiline_comment|/* ...determine content     &t;*/
DECL|member|revision
id|u16
id|revision
suffix:semicolon
multiline_comment|/* header revision &t;&t;*/
r_union
(brace
r_struct
(brace
multiline_comment|/* Class 5, Type 1 - System Error&t;*/
DECL|member|frame_length
id|u32
id|frame_length
suffix:semicolon
DECL|member|frame_packet_count
id|u32
id|frame_packet_count
suffix:semicolon
DECL|member|sys_err
)brace
id|sys_err
suffix:semicolon
r_struct
(brace
multiline_comment|/* Class 5, Type 2 - System Event &t;*/
DECL|member|timestamp
r_union
id|el_timestamp
id|timestamp
suffix:semicolon
DECL|member|frame_length
id|u32
id|frame_length
suffix:semicolon
DECL|member|frame_packet_count
id|u32
id|frame_packet_count
suffix:semicolon
DECL|member|sys_event
)brace
id|sys_event
suffix:semicolon
r_struct
(brace
multiline_comment|/* Class 5, Type 3 - Double Error Halt&t;*/
DECL|member|halt_code
id|u16
id|halt_code
suffix:semicolon
DECL|member|reserved
id|u16
id|reserved
suffix:semicolon
DECL|member|timestamp
r_union
id|el_timestamp
id|timestamp
suffix:semicolon
DECL|member|frame_length
id|u32
id|frame_length
suffix:semicolon
DECL|member|frame_packet_count
id|u32
id|frame_packet_count
suffix:semicolon
DECL|member|err_halt
)brace
id|err_halt
suffix:semicolon
r_struct
(brace
multiline_comment|/* Clasee 5, Type 19 - Logout Frame Header */
DECL|member|frame_length
id|u32
id|frame_length
suffix:semicolon
DECL|member|frame_flags
id|u32
id|frame_flags
suffix:semicolon
DECL|member|cpu_offset
id|u32
id|cpu_offset
suffix:semicolon
DECL|member|system_offset
id|u32
id|system_offset
suffix:semicolon
DECL|member|logout_header
)brace
id|logout_header
suffix:semicolon
r_struct
(brace
multiline_comment|/* Class 12 - Regatta&t;&t;&t;*/
DECL|member|cpuid
id|u64
id|cpuid
suffix:semicolon
DECL|member|data_start
id|u64
id|data_start
(braket
l_int|1
)braket
suffix:semicolon
DECL|member|regatta_frame
)brace
id|regatta_frame
suffix:semicolon
r_struct
(brace
multiline_comment|/* Raw &t;&t;&t;&t;        */
DECL|member|data_start
id|u64
id|data_start
(braket
l_int|1
)braket
suffix:semicolon
DECL|member|raw
)brace
id|raw
suffix:semicolon
DECL|member|by_type
)brace
id|by_type
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|el_subpacket_annotation
r_struct
id|el_subpacket_annotation
(brace
DECL|member|next
r_struct
id|el_subpacket_annotation
op_star
id|next
suffix:semicolon
DECL|member|class
id|u16
r_class
suffix:semicolon
DECL|member|type
id|u16
id|type
suffix:semicolon
DECL|member|revision
id|u16
id|revision
suffix:semicolon
DECL|member|description
r_char
op_star
id|description
suffix:semicolon
DECL|member|annotation
r_char
op_star
op_star
id|annotation
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SUBPACKET_ANNOTATION
mdefine_line|#define SUBPACKET_ANNOTATION(c, t, r, d, a) {NULL, (c), (t), (r), (d), (a)}
DECL|struct|el_subpacket_handler
r_struct
id|el_subpacket_handler
(brace
DECL|member|next
r_struct
id|el_subpacket_handler
op_star
id|next
suffix:semicolon
DECL|member|class
id|u16
r_class
suffix:semicolon
DECL|member|handler
r_struct
id|el_subpacket
op_star
(paren
op_star
id|handler
)paren
(paren
r_struct
id|el_subpacket
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SUBPACKET_HANDLER_INIT
mdefine_line|#define SUBPACKET_HANDLER_INIT(c, h) {NULL, (c), (h)}
multiline_comment|/*&n; * Extract a field from a register given it&squot;s name. defines&n; * for the LSB (__S - shift count) and bitmask (__M) are required&n; */
DECL|macro|EXTRACT
mdefine_line|#define EXTRACT(u, f) (((u) &gt;&gt; f##__S) &amp; f##__M)
multiline_comment|/*&n; * err_common.c&n; */
r_extern
r_char
op_star
id|err_print_prefix
suffix:semicolon
r_extern
r_void
id|mchk_dump_mem
c_func
(paren
r_void
op_star
comma
r_int
comma
r_char
op_star
op_star
)paren
suffix:semicolon
r_extern
r_void
id|mchk_dump_logout_frame
c_func
(paren
r_struct
id|el_common
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ev7_register_error_handlers
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ev7_machine_check
c_func
(paren
id|u64
comma
id|u64
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_extern
r_void
id|ev6_register_error_handlers
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|ev6_process_logout_frame
c_func
(paren
r_struct
id|el_common
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|ev6_machine_check
c_func
(paren
id|u64
comma
id|u64
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|el_subpacket
op_star
id|el_process_subpacket
c_func
(paren
r_struct
id|el_subpacket
op_star
)paren
suffix:semicolon
r_extern
r_void
id|el_annotate_subpacket
c_func
(paren
r_struct
id|el_subpacket
op_star
)paren
suffix:semicolon
r_extern
r_void
id|cdl_check_console_data_log
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|cdl_register_subpacket_annotation
c_func
(paren
r_struct
id|el_subpacket_annotation
op_star
)paren
suffix:semicolon
r_extern
r_int
id|cdl_register_subpacket_handler
c_func
(paren
r_struct
id|el_subpacket_handler
op_star
)paren
suffix:semicolon
eof
