macro_line|#ifndef _MIROPCM20_RDS_CORE_H_
DECL|macro|_MIROPCM20_RDS_CORE_H_
mdefine_line|#define _MIROPCM20_RDS_CORE_H_
r_extern
r_int
id|aci_rds_cmd
c_func
(paren
r_int
r_char
id|cmd
comma
r_int
r_char
id|databuffer
(braket
)braket
comma
r_int
id|datasize
)paren
suffix:semicolon
DECL|macro|RDS_STATUS
mdefine_line|#define RDS_STATUS      0x01
DECL|macro|RDS_STATIONNAME
mdefine_line|#define RDS_STATIONNAME 0x02
DECL|macro|RDS_TEXT
mdefine_line|#define RDS_TEXT        0x03
DECL|macro|RDS_ALTFREQ
mdefine_line|#define RDS_ALTFREQ     0x04
DECL|macro|RDS_TIMEDATE
mdefine_line|#define RDS_TIMEDATE    0x05
DECL|macro|RDS_PI_CODE
mdefine_line|#define RDS_PI_CODE     0x06
DECL|macro|RDS_PTYTATP
mdefine_line|#define RDS_PTYTATP     0x07
DECL|macro|RDS_RESET
mdefine_line|#define RDS_RESET       0x08
DECL|macro|RDS_RXVALUE
mdefine_line|#define RDS_RXVALUE     0x09
r_extern
r_void
id|__exit
id|unload_aci_rds
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|__init
id|attach_aci_rds
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* _MIROPCM20_RDS_CORE_H_ */
eof
