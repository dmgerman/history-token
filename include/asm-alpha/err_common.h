multiline_comment|/*&n; *&t;linux/include/asm-alpha/err_common.h&n; *&n; *&t;Copyright (C) 2000 Jeff Wiedemeier (Compaq Computer Corporation)&n; *&n; *&t;Contains declarations and macros to support Alpha error handling&n; * &t;implementations.&n; */
macro_line|#ifndef __ALPHA_ERR_COMMON_H
DECL|macro|__ALPHA_ERR_COMMON_H
mdefine_line|#define __ALPHA_ERR_COMMON_H 1
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
DECL|macro|EL_TYPE__PAL__ENV__AMBIENT_TEMPERATURE
macro_line|#  define EL_TYPE__PAL__ENV__AMBIENT_TEMPERATURE&t;(10)
DECL|macro|EL_TYPE__PAL__ENV__AIRMOVER_FAN
macro_line|#  define EL_TYPE__PAL__ENV__AIRMOVER_FAN&t;&t;(11)
DECL|macro|EL_TYPE__PAL__ENV__VOLTAGE
macro_line|#  define EL_TYPE__PAL__ENV__VOLTAGE&t;&t;&t;(12)
DECL|macro|EL_TYPE__PAL__ENV__INTRUSION
macro_line|#  define EL_TYPE__PAL__ENV__INTRUSION&t;&t;&t;(13)
DECL|macro|EL_TYPE__PAL__ENV__POWER_SUPPLY
macro_line|#  define EL_TYPE__PAL__ENV__POWER_SUPPLY&t;&t;(14)
DECL|macro|EL_TYPE__PAL__ENV__LAN
macro_line|#  define EL_TYPE__PAL__ENV__LAN&t;&t;&t;(15)
DECL|macro|EL_TYPE__PAL__ENV__HOT_PLUG
macro_line|#  define EL_TYPE__PAL__ENV__HOT_PLUG&t;&t;&t;(16)
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
macro_line|#endif /* __ALPHA_ERR_COMMON_H */
eof
