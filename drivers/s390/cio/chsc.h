macro_line|#ifndef S390_CHSC_H
DECL|macro|S390_CHSC_H
mdefine_line|#define S390_CHSC_H
DECL|macro|NR_CHPIDS
mdefine_line|#define NR_CHPIDS 256
DECL|macro|CHP_OFFLINE
mdefine_line|#define CHP_OFFLINE 0
DECL|macro|CHP_LOGICALLY_OFFLINE
mdefine_line|#define CHP_LOGICALLY_OFFLINE 1
DECL|macro|CHP_STANDBY
mdefine_line|#define CHP_STANDBY 2
DECL|macro|CHP_ONLINE
mdefine_line|#define CHP_ONLINE 3
DECL|macro|CHSC_SEI_ACC_CHPID
mdefine_line|#define CHSC_SEI_ACC_CHPID        1
DECL|macro|CHSC_SEI_ACC_LINKADDR
mdefine_line|#define CHSC_SEI_ACC_LINKADDR     2
DECL|macro|CHSC_SEI_ACC_FULLLINKADDR
mdefine_line|#define CHSC_SEI_ACC_FULLLINKADDR 3
DECL|struct|sei_area
r_struct
id|sei_area
(brace
r_struct
(brace
multiline_comment|/* word 0 */
DECL|member|command_code1
id|__u16
id|command_code1
suffix:semicolon
DECL|member|command_code2
id|__u16
id|command_code2
suffix:semicolon
multiline_comment|/* word 1 */
DECL|member|reserved1
id|__u32
id|reserved1
suffix:semicolon
multiline_comment|/* word 2 */
DECL|member|reserved2
id|__u32
id|reserved2
suffix:semicolon
multiline_comment|/* word 3 */
DECL|member|reserved3
id|__u32
id|reserved3
suffix:semicolon
DECL|member|request_block
)brace
id|__attribute__
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
id|request_block
suffix:semicolon
r_struct
(brace
multiline_comment|/* word 0 */
DECL|member|length
id|__u16
id|length
suffix:semicolon
DECL|member|response_code
id|__u16
id|response_code
suffix:semicolon
multiline_comment|/* word 1 */
DECL|member|reserved1
id|__u32
id|reserved1
suffix:semicolon
multiline_comment|/* word 2 */
DECL|member|flags
id|__u8
id|flags
suffix:semicolon
DECL|member|vf
id|__u8
id|vf
suffix:semicolon
multiline_comment|/* validity flags */
DECL|member|rs
id|__u8
id|rs
suffix:semicolon
multiline_comment|/* reporting source */
DECL|member|cc
id|__u8
id|cc
suffix:semicolon
multiline_comment|/* content code */
multiline_comment|/* word 3 */
DECL|member|fla
id|__u16
id|fla
suffix:semicolon
multiline_comment|/* full link address */
DECL|member|rsid
id|__u16
id|rsid
suffix:semicolon
multiline_comment|/* reporting source id */
multiline_comment|/* word 4 */
DECL|member|reserved2
id|__u32
id|reserved2
suffix:semicolon
multiline_comment|/* word 5 */
DECL|member|reserved3
id|__u32
id|reserved3
suffix:semicolon
multiline_comment|/* word 6 */
DECL|member|ccdf
id|__u32
id|ccdf
suffix:semicolon
multiline_comment|/* content-code dependent field */
multiline_comment|/* word 7 */
DECL|member|reserved4
id|__u32
id|reserved4
suffix:semicolon
multiline_comment|/* word 8 */
DECL|member|reserved5
id|__u32
id|reserved5
suffix:semicolon
multiline_comment|/* word 9 */
DECL|member|reserved6
id|__u32
id|reserved6
suffix:semicolon
DECL|member|response_block
)brace
id|__attribute__
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
id|response_block
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
comma
id|aligned
c_func
(paren
id|PAGE_SIZE
)paren
)paren
)paren
suffix:semicolon
DECL|struct|ssd_area
r_struct
id|ssd_area
(brace
r_struct
(brace
multiline_comment|/* word 0 */
DECL|member|command_code1
id|__u16
id|command_code1
suffix:semicolon
DECL|member|command_code2
id|__u16
id|command_code2
suffix:semicolon
multiline_comment|/* word 1 */
DECL|member|reserved1
id|__u16
id|reserved1
suffix:semicolon
DECL|member|f_sch
id|__u16
id|f_sch
suffix:semicolon
multiline_comment|/* first subchannel */
multiline_comment|/* word 2 */
DECL|member|reserved2
id|__u16
id|reserved2
suffix:semicolon
DECL|member|l_sch
id|__u16
id|l_sch
suffix:semicolon
multiline_comment|/* last subchannel */
multiline_comment|/* word 3 */
DECL|member|reserved3
id|__u32
id|reserved3
suffix:semicolon
DECL|member|request_block
)brace
id|__attribute__
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
id|request_block
suffix:semicolon
r_struct
(brace
multiline_comment|/* word 0 */
DECL|member|length
id|__u16
id|length
suffix:semicolon
DECL|member|response_code
id|__u16
id|response_code
suffix:semicolon
multiline_comment|/* word 1 */
DECL|member|reserved1
id|__u32
id|reserved1
suffix:semicolon
multiline_comment|/* word 2 */
DECL|member|sch_valid
id|__u8
id|sch_valid
suffix:colon
l_int|1
suffix:semicolon
DECL|member|dev_valid
id|__u8
id|dev_valid
suffix:colon
l_int|1
suffix:semicolon
DECL|member|st
id|__u8
id|st
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* subchannel type */
DECL|member|zeroes
id|__u8
id|zeroes
suffix:colon
l_int|3
suffix:semicolon
DECL|member|unit_addr
id|__u8
id|unit_addr
suffix:semicolon
multiline_comment|/* unit address */
DECL|member|devno
id|__u16
id|devno
suffix:semicolon
multiline_comment|/* device number */
multiline_comment|/* word 3 */
DECL|member|path_mask
id|__u8
id|path_mask
suffix:semicolon
DECL|member|fla_valid_mask
id|__u8
id|fla_valid_mask
suffix:semicolon
DECL|member|sch
id|__u16
id|sch
suffix:semicolon
multiline_comment|/* subchannel */
multiline_comment|/* words 4-5 */
DECL|member|chpid
id|__u8
id|chpid
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* chpids 0-7 */
multiline_comment|/* words 6-9 */
DECL|member|fla
id|__u16
id|fla
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* full link addresses 0-7 */
DECL|member|response_block
)brace
id|__attribute__
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
id|response_block
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
comma
id|aligned
c_func
(paren
id|PAGE_SIZE
)paren
)paren
)paren
suffix:semicolon
DECL|struct|channel_path
r_struct
id|channel_path
(brace
DECL|member|id
r_int
id|id
suffix:semicolon
DECL|member|state
r_int
id|state
suffix:semicolon
DECL|member|dev
r_struct
id|device
id|dev
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|channel_path
op_star
id|chps
(braket
)braket
suffix:semicolon
r_extern
r_void
id|s390_process_css
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|chsc_validate_chpids
c_func
(paren
r_struct
id|subchannel
op_star
)paren
suffix:semicolon
macro_line|#endif
eof
