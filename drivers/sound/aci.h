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
DECL|macro|ACI_SET_MUTE
mdefine_line|#define ACI_SET_MUTE          0x0d
DECL|macro|ACI_SET_POWERAMP
mdefine_line|#define ACI_SET_POWERAMP      0x0f
DECL|macro|ACI_SET_TUNERMUTE
mdefine_line|#define ACI_SET_TUNERMUTE     0xa3
DECL|macro|ACI_SET_TUNERMONO
mdefine_line|#define ACI_SET_TUNERMONO     0xa4
DECL|macro|ACI_SET_IDE
mdefine_line|#define ACI_SET_IDE           0xd0
DECL|macro|ACI_SET_WSS
mdefine_line|#define ACI_SET_WSS           0xd1
DECL|macro|ACI_SET_SOLOMODE
mdefine_line|#define ACI_SET_SOLOMODE      0xd2
DECL|macro|ACI_WRITE_IGAIN
mdefine_line|#define ACI_WRITE_IGAIN       0x03
DECL|macro|ACI_WRITE_TUNE
mdefine_line|#define ACI_WRITE_TUNE        0xa7
DECL|macro|ACI_READ_TUNERSTEREO
mdefine_line|#define ACI_READ_TUNERSTEREO  0xa8
DECL|macro|ACI_READ_TUNERSTATION
mdefine_line|#define ACI_READ_TUNERSTATION 0xa9
DECL|macro|ACI_READ_VERSION
mdefine_line|#define ACI_READ_VERSION      0xf1
DECL|macro|ACI_READ_IDCODE
mdefine_line|#define ACI_READ_IDCODE       0xf2
DECL|macro|ACI_INIT
mdefine_line|#define ACI_INIT              0xff
DECL|macro|ACI_STATUS
mdefine_line|#define ACI_STATUS            0xf0
DECL|macro|ACI_S_GENERAL
mdefine_line|#define     ACI_S_GENERAL     0x00
DECL|macro|ACI_S_READ_IGAIN
mdefine_line|#define     ACI_S_READ_IGAIN  0x21
DECL|macro|ACI_ERROR_OP
mdefine_line|#define ACI_ERROR_OP          0xdf
multiline_comment|/*&n; * The following macro SCALE can be used to scale one integer volume&n; * value into another one using only integer arithmetic. If the input&n; * value x is in the range 0 &lt;= x &lt;= xmax, then the result will be in&n; * the range 0 &lt;= SCALE(xmax,ymax,x) &lt;= ymax.&n; *&n; * This macro has for all xmax, ymax &gt; 0 and all 0 &lt;= x &lt;= xmax the&n; * following nice properties:&n; *&n; * - SCALE(xmax,ymax,xmax) = ymax&n; * - SCALE(xmax,ymax,0) = 0&n; * - SCALE(xmax,ymax,SCALE(ymax,xmax,SCALE(xmax,ymax,x))) = SCALE(xmax,ymax,x)&n; *&n; * In addition, the rounding error is minimal and nicely distributed.&n; * The proofs are left as an exercise to the reader.&n; */
DECL|macro|SCALE
mdefine_line|#define SCALE(xmax,ymax,x) (((x)*(ymax)+(xmax)/2)/(xmax))
macro_line|#endif  /* _ACI_H_ */
eof
