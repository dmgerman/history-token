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
DECL|member|sdev
r_struct
id|sys_device
id|sdev
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
