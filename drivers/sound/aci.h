macro_line|#ifndef _ACI_H_
DECL|macro|_ACI_H_
mdefine_line|#define _ACI_H_
r_extern
r_int
id|aci_port
suffix:semicolon
r_extern
r_int
id|aci_idcode
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* manufacturer and product ID */
r_extern
r_int
id|aci_version
suffix:semicolon
multiline_comment|/* ACI firmware version&t;*/
r_extern
r_int
id|aci_rw_cmd
c_func
(paren
r_int
id|write1
comma
r_int
id|write2
comma
r_int
id|write3
)paren
suffix:semicolon
r_extern
r_char
op_star
id|aci_radio_name
suffix:semicolon
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
DECL|macro|aci_indexed_cmd
mdefine_line|#define aci_indexed_cmd(a, b) aci_rw_cmd(a, b, -1)
DECL|macro|aci_write_cmd
mdefine_line|#define aci_write_cmd(a, b)   aci_rw_cmd(a, b, -1)
DECL|macro|aci_read_cmd
mdefine_line|#define aci_read_cmd(a)       aci_rw_cmd(a,-1, -1)
DECL|macro|COMMAND_REGISTER
mdefine_line|#define COMMAND_REGISTER    (aci_port)      /* write register */
DECL|macro|STATUS_REGISTER
mdefine_line|#define STATUS_REGISTER     (aci_port + 1)  /* read register */
DECL|macro|BUSY_REGISTER
mdefine_line|#define BUSY_REGISTER       (aci_port + 2)  /* also used for rds */
DECL|macro|RDS_REGISTER
mdefine_line|#define RDS_REGISTER        BUSY_REGISTER
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
multiline_comment|/*&n; * The following macro SCALE can be used to scale one integer volume&n; * value into another one using only integer arithmetic. If the input&n; * value x is in the range 0 &lt;= x &lt;= xmax, then the result will be in&n; * the range 0 &lt;= SCALE(xmax,ymax,x) &lt;= ymax.&n; *&n; * This macro has for all xmax, ymax &gt; 0 and all 0 &lt;= x &lt;= xmax the&n; * following nice properties:&n; *&n; * - SCALE(xmax,ymax,xmax) = ymax&n; * - SCALE(xmax,ymax,0) = 0&n; * - SCALE(xmax,ymax,SCALE(ymax,xmax,SCALE(xmax,ymax,x))) = SCALE(xmax,ymax,x)&n; *&n; * In addition, the rounding error is minimal and nicely distributed.&n; * The proofs are left as an exercise to the reader.&n; */
DECL|macro|SCALE
mdefine_line|#define SCALE(xmax,ymax,x) (((x)*(ymax)+(xmax)/2)/(xmax))
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
macro_line|#endif  /* _ACI_H_ */
eof
