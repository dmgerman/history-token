multiline_comment|/*&n; *&t;ultrastor.c&t;(C) 1991 David B. Gentzel&n; *&t;Low-level scsi driver for UltraStor 14F&n; *&t;by David B. Gentzel, Whitfield Software Services, Carnegie, PA&n; *&t;    (gentzel@nova.enet.dec.com)&n; *  scatter/gather added by Scott Taylor (n217cg@tamuts.tamu.edu)&n; *  24F support by John F. Carr (jfc@athena.mit.edu)&n; *    John&squot;s work modified by Caleb Epstein (cae@jpmorgan.com) and &n; *    Eric Youngdale (eric@tantalus.nrl.navy.mil).&n; *&t;Thanks to UltraStor for providing the necessary documentation&n; */
macro_line|#ifndef _ULTRASTOR_H
DECL|macro|_ULTRASTOR_H
mdefine_line|#define _ULTRASTOR_H
macro_line|#include &lt;linux/kdev_t.h&gt;
r_int
id|ultrastor_detect
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_const
r_char
op_star
id|ultrastor_info
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|shpnt
)paren
suffix:semicolon
r_int
id|ultrastor_queuecommand
c_func
(paren
id|Scsi_Cmnd
op_star
comma
r_void
(paren
op_star
id|done
)paren
(paren
id|Scsi_Cmnd
op_star
)paren
)paren
suffix:semicolon
r_int
id|ultrastor_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|ultrastor_reset
c_func
(paren
id|Scsi_Cmnd
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_int
id|ultrastor_biosparam
c_func
(paren
id|Disk
op_star
comma
id|kdev_t
comma
r_int
op_star
)paren
suffix:semicolon
DECL|macro|ULTRASTOR_14F_MAX_SG
mdefine_line|#define ULTRASTOR_14F_MAX_SG 16
DECL|macro|ULTRASTOR_24F_MAX_SG
mdefine_line|#define ULTRASTOR_24F_MAX_SG 33
DECL|macro|ULTRASTOR_MAX_CMDS_PER_LUN
mdefine_line|#define ULTRASTOR_MAX_CMDS_PER_LUN 5
DECL|macro|ULTRASTOR_MAX_CMDS
mdefine_line|#define ULTRASTOR_MAX_CMDS 16
DECL|macro|ULTRASTOR_24F_PORT
mdefine_line|#define ULTRASTOR_24F_PORT 0xC80
DECL|macro|ULTRASTOR_14F
mdefine_line|#define ULTRASTOR_14F {   name:              &quot;UltraStor 14F/24F/34F&quot;, &t;&bslash;&n;&t;&t;&t;  detect:            ultrastor_detect, &t;&t;&bslash;&n;&t;&t;&t;  info:              ultrastor_info, &t;&t;&bslash;&n;&t;&t;&t;  queuecommand:      ultrastor_queuecommand,&t;&bslash;&n;&t;&t;&t;  abort:             ultrastor_abort, &t;&t;&bslash;&n;&t;&t;&t;  reset:             ultrastor_reset,&t;&t;&bslash;&n;&t;&t;&t;  bios_param:        ultrastor_biosparam, &t;&bslash;&n;&t;&t;&t;  can_queue:         ULTRASTOR_MAX_CMDS,&t;&bslash;&n;&t;&t;&t;  this_id:           0, &t;&t;&t;&bslash;&n;&t;&t;&t;  sg_tablesize:      ULTRASTOR_14F_MAX_SG, &t;&bslash;&n;&t;&t;&t;  cmd_per_lun:       ULTRASTOR_MAX_CMDS_PER_LUN,&bslash;&n;&t;&t;&t;  unchecked_isa_dma: 1, &t;&t;&t;&bslash;&n;&t;&t;&t;  use_clustering:    ENABLE_CLUSTERING }
macro_line|#ifdef ULTRASTOR_PRIVATE
DECL|macro|UD_ABORT
mdefine_line|#define UD_ABORT&t;0x0001
DECL|macro|UD_COMMAND
mdefine_line|#define UD_COMMAND&t;0x0002
DECL|macro|UD_DETECT
mdefine_line|#define UD_DETECT&t;0x0004
DECL|macro|UD_INTERRUPT
mdefine_line|#define UD_INTERRUPT&t;0x0008
DECL|macro|UD_RESET
mdefine_line|#define UD_RESET&t;0x0010
DECL|macro|UD_MULTI_CMD
mdefine_line|#define UD_MULTI_CMD&t;0x0020
DECL|macro|UD_CSIR
mdefine_line|#define UD_CSIR&t;&t;0x0040
DECL|macro|UD_ERROR
mdefine_line|#define UD_ERROR&t;0x0080
multiline_comment|/* #define PORT_OVERRIDE 0x330 */
multiline_comment|/* Values for the PRODUCT_ID ports for the 14F */
DECL|macro|US14F_PRODUCT_ID_0
mdefine_line|#define US14F_PRODUCT_ID_0 0x56
DECL|macro|US14F_PRODUCT_ID_1
mdefine_line|#define US14F_PRODUCT_ID_1 0x40&t;&t;/* NOTE: Only upper nibble is used */
DECL|macro|US24F_PRODUCT_ID_0
mdefine_line|#define US24F_PRODUCT_ID_0 0x56
DECL|macro|US24F_PRODUCT_ID_1
mdefine_line|#define US24F_PRODUCT_ID_1 0x63
DECL|macro|US24F_PRODUCT_ID_2
mdefine_line|#define US24F_PRODUCT_ID_2 0x02
multiline_comment|/* Subversion values */
DECL|macro|U14F
mdefine_line|#define U14F 0
DECL|macro|U34F
mdefine_line|#define U34F 1
multiline_comment|/* MSCP field values */
multiline_comment|/* Opcode */
DECL|macro|OP_HOST_ADAPTER
mdefine_line|#define OP_HOST_ADAPTER 0x1
DECL|macro|OP_SCSI
mdefine_line|#define OP_SCSI 0x2
DECL|macro|OP_RESET
mdefine_line|#define OP_RESET 0x4
multiline_comment|/* Date Transfer Direction */
DECL|macro|DTD_SCSI
mdefine_line|#define DTD_SCSI 0x0
DECL|macro|DTD_IN
mdefine_line|#define DTD_IN 0x1
DECL|macro|DTD_OUT
mdefine_line|#define DTD_OUT 0x2
DECL|macro|DTD_NONE
mdefine_line|#define DTD_NONE 0x3
multiline_comment|/* Host Adapter command subcodes */
DECL|macro|HA_CMD_INQUIRY
mdefine_line|#define HA_CMD_INQUIRY 0x1
DECL|macro|HA_CMD_SELF_DIAG
mdefine_line|#define HA_CMD_SELF_DIAG 0x2
DECL|macro|HA_CMD_READ_BUFF
mdefine_line|#define HA_CMD_READ_BUFF 0x3
DECL|macro|HA_CMD_WRITE_BUFF
mdefine_line|#define HA_CMD_WRITE_BUFF 0x4
macro_line|#endif
macro_line|#endif
eof
