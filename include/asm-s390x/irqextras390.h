multiline_comment|/*&n; *  include/asm-s390/irqextras390.h&n; *&n; *  S390 version&n; *    Copyright (C) 1999 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Denis Joseph Barrow (djbarrow@de.ibm.com,barrow_dj@yahoo.com)&n; */
macro_line|#ifndef __irqextras390_h
DECL|macro|__irqextras390_h
mdefine_line|#define __irqextras390_h
multiline_comment|/*&n;  irqextras390.h by D.J. Barrow&n;  if you are a bitfield fan &amp;  are paranoid that ansi dosen&squot;t&n;  give hard definitions about the size of an int or long you might&n;  prefer these definitions as an alternative.&n;&n;*/
macro_line|#include &lt;linux/types.h&gt;
r_typedef
r_struct
(brace
DECL|member|key
r_int
id|key
suffix:colon
l_int|4
suffix:semicolon
DECL|member|s
r_int
id|s
suffix:colon
l_int|1
suffix:semicolon
DECL|member|l
r_int
id|l
suffix:colon
l_int|1
suffix:semicolon
DECL|member|cc
r_int
id|cc
suffix:colon
l_int|2
suffix:semicolon
DECL|member|f
r_int
id|f
suffix:colon
l_int|1
suffix:semicolon
DECL|member|p
r_int
id|p
suffix:colon
l_int|1
suffix:semicolon
DECL|member|i
r_int
id|i
suffix:colon
l_int|1
suffix:semicolon
DECL|member|a
r_int
id|a
suffix:colon
l_int|1
suffix:semicolon
DECL|member|u
r_int
id|u
suffix:colon
l_int|1
suffix:semicolon
DECL|member|z
r_int
id|z
suffix:colon
l_int|1
suffix:semicolon
DECL|member|e
r_int
id|e
suffix:colon
l_int|1
suffix:semicolon
DECL|member|n
r_int
id|n
suffix:colon
l_int|1
suffix:semicolon
DECL|member|zero
r_int
id|zero
suffix:colon
l_int|1
suffix:semicolon
DECL|member|fc_start
r_int
id|fc_start
suffix:colon
l_int|1
suffix:semicolon
DECL|member|fc_halt
r_int
id|fc_halt
suffix:colon
l_int|1
suffix:semicolon
DECL|member|fc_clear
r_int
id|fc_clear
suffix:colon
l_int|1
suffix:semicolon
DECL|member|ac_resume_pending
r_int
id|ac_resume_pending
suffix:colon
l_int|1
suffix:semicolon
DECL|member|ac_start_pending
r_int
id|ac_start_pending
suffix:colon
l_int|1
suffix:semicolon
DECL|member|ac_halt_pending
r_int
id|ac_halt_pending
suffix:colon
l_int|1
suffix:semicolon
DECL|member|ac_clear_pending
r_int
id|ac_clear_pending
suffix:colon
l_int|1
suffix:semicolon
DECL|member|ac_subchannel_active
r_int
id|ac_subchannel_active
suffix:colon
l_int|1
suffix:semicolon
DECL|member|ac_device_active
r_int
id|ac_device_active
suffix:colon
l_int|1
suffix:semicolon
DECL|member|ac_suspended
r_int
id|ac_suspended
suffix:colon
l_int|1
suffix:semicolon
DECL|member|sc_alert
r_int
id|sc_alert
suffix:colon
l_int|1
suffix:semicolon
DECL|member|sc_intermediate
r_int
id|sc_intermediate
suffix:colon
l_int|1
suffix:semicolon
DECL|member|sc_primary
r_int
id|sc_primary
suffix:colon
l_int|1
suffix:semicolon
DECL|member|sc_seconary
r_int
id|sc_seconary
suffix:colon
l_int|1
suffix:semicolon
DECL|member|sc_status_pending
r_int
id|sc_status_pending
suffix:colon
l_int|1
suffix:semicolon
DECL|member|ccw_address
id|__u32
id|ccw_address
suffix:semicolon
DECL|member|dev_status_attention
r_int
id|dev_status_attention
suffix:colon
l_int|1
suffix:semicolon
DECL|member|dev_status_modifier
r_int
id|dev_status_modifier
suffix:colon
l_int|1
suffix:semicolon
DECL|member|dev_status_control_unit_end
r_int
id|dev_status_control_unit_end
suffix:colon
l_int|1
suffix:semicolon
DECL|member|dev_status_busy
r_int
id|dev_status_busy
suffix:colon
l_int|1
suffix:semicolon
DECL|member|dev_status_channel_end
r_int
id|dev_status_channel_end
suffix:colon
l_int|1
suffix:semicolon
DECL|member|dev_status_device_end
r_int
id|dev_status_device_end
suffix:colon
l_int|1
suffix:semicolon
DECL|member|dev_status_unit_check
r_int
id|dev_status_unit_check
suffix:colon
l_int|1
suffix:semicolon
DECL|member|dev_status_unit_exception
r_int
id|dev_status_unit_exception
suffix:colon
l_int|1
suffix:semicolon
DECL|member|sch_status_program_cont_int
r_int
id|sch_status_program_cont_int
suffix:colon
l_int|1
suffix:semicolon
DECL|member|sch_status_incorrect_length
r_int
id|sch_status_incorrect_length
suffix:colon
l_int|1
suffix:semicolon
DECL|member|sch_status_program_check
r_int
id|sch_status_program_check
suffix:colon
l_int|1
suffix:semicolon
DECL|member|sch_status_protection_check
r_int
id|sch_status_protection_check
suffix:colon
l_int|1
suffix:semicolon
DECL|member|sch_status_channel_data_check
r_int
id|sch_status_channel_data_check
suffix:colon
l_int|1
suffix:semicolon
DECL|member|sch_status_channel_control_check
r_int
id|sch_status_channel_control_check
suffix:colon
l_int|1
suffix:semicolon
DECL|member|sch_status_interface_control_check
r_int
id|sch_status_interface_control_check
suffix:colon
l_int|1
suffix:semicolon
DECL|member|sch_status_chaining_check
r_int
id|sch_status_chaining_check
suffix:colon
l_int|1
suffix:semicolon
DECL|member|byte_count
id|__u16
id|byte_count
suffix:semicolon
DECL|typedef|scsw_bits_t
)brace
id|scsw_bits_t
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|flags
id|__u32
id|flags
suffix:semicolon
DECL|member|ccw_address
id|__u32
id|ccw_address
suffix:semicolon
DECL|member|dev_status
id|__u8
id|dev_status
suffix:semicolon
DECL|member|sch_status
id|__u8
id|sch_status
suffix:semicolon
DECL|member|byte_count
id|__u16
id|byte_count
suffix:semicolon
DECL|typedef|scsw_words_t
)brace
id|scsw_words_t
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|cmd_code
id|__u8
id|cmd_code
suffix:semicolon
DECL|member|cd
r_int
id|cd
suffix:colon
l_int|1
suffix:semicolon
DECL|member|cc
r_int
id|cc
suffix:colon
l_int|1
suffix:semicolon
DECL|member|sli
r_int
id|sli
suffix:colon
l_int|1
suffix:semicolon
DECL|member|skip
r_int
id|skip
suffix:colon
l_int|1
suffix:semicolon
DECL|member|pci
r_int
id|pci
suffix:colon
l_int|1
suffix:semicolon
DECL|member|ida
r_int
id|ida
suffix:colon
l_int|1
suffix:semicolon
DECL|member|s
r_int
id|s
suffix:colon
l_int|1
suffix:semicolon
DECL|member|res1
r_int
id|res1
suffix:colon
l_int|1
suffix:semicolon
DECL|member|count
id|__u16
id|count
suffix:semicolon
DECL|member|ccw_data_address
id|__u32
id|ccw_data_address
suffix:semicolon
DECL|typedef|ccw1_bits_t
)brace
id|ccw1_bits_t
id|__attribute__
c_func
(paren
(paren
id|packed
comma
id|aligned
c_func
(paren
l_int|8
)paren
)paren
)paren
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|interruption_parm
id|__u32
id|interruption_parm
suffix:semicolon
DECL|member|key
r_int
id|key
suffix:colon
l_int|4
suffix:semicolon
DECL|member|s
r_int
id|s
suffix:colon
l_int|1
suffix:semicolon
DECL|member|res1
r_int
id|res1
suffix:colon
l_int|3
suffix:semicolon
DECL|member|f
r_int
id|f
suffix:colon
l_int|1
suffix:semicolon
DECL|member|p
r_int
id|p
suffix:colon
l_int|1
suffix:semicolon
DECL|member|i
r_int
id|i
suffix:colon
l_int|1
suffix:semicolon
DECL|member|a
r_int
id|a
suffix:colon
l_int|1
suffix:semicolon
DECL|member|u
r_int
id|u
suffix:colon
l_int|1
suffix:semicolon
DECL|member|lpm
id|__u8
id|lpm
suffix:semicolon
DECL|member|l
r_int
id|l
suffix:colon
l_int|1
suffix:semicolon
DECL|member|res2
r_int
id|res2
suffix:colon
l_int|7
suffix:semicolon
DECL|member|ccw_program_address
id|ccw1_bits_t
op_star
id|ccw_program_address
suffix:semicolon
DECL|typedef|orb_bits_t
)brace
id|orb_bits_t
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
r_void
id|fixchannelprogram
c_func
(paren
id|orb_bits_t
op_star
id|orbptr
)paren
suffix:semicolon
r_void
id|fixccws
c_func
(paren
id|ccw1_bits_t
op_star
id|ccwptr
)paren
suffix:semicolon
r_enum
(brace
DECL|enumerator|ccw_write
id|ccw_write
op_assign
l_int|0x1
comma
DECL|enumerator|ccw_read
id|ccw_read
op_assign
l_int|0x2
comma
DECL|enumerator|ccw_read_backward
id|ccw_read_backward
op_assign
l_int|0xc
comma
DECL|enumerator|ccw_control
id|ccw_control
op_assign
l_int|0x3
comma
DECL|enumerator|ccw_sense
id|ccw_sense
op_assign
l_int|0x4
comma
DECL|enumerator|ccw_sense_id
id|ccw_sense_id
op_assign
l_int|0xe4
comma
DECL|enumerator|ccw_transfer_in_channel0
id|ccw_transfer_in_channel0
op_assign
l_int|0x8
comma
DECL|enumerator|ccw_transfer_in_channel1
id|ccw_transfer_in_channel1
op_assign
l_int|0x8
comma
DECL|enumerator|ccw_set_x_mode
id|ccw_set_x_mode
op_assign
l_int|0xc3
comma
singleline_comment|// according to uli&squot;s lan notes
DECL|enumerator|ccw_nop
id|ccw_nop
op_assign
l_int|0x3
singleline_comment|// according to uli&squot;s notes again
singleline_comment|// n.b. ccw_control clashes with this
singleline_comment|// so I presume its a special case of
singleline_comment|// control
)brace
suffix:semicolon
macro_line|#endif
eof
