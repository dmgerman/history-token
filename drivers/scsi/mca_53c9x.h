multiline_comment|/* mca_53c94.h: Defines and structures for the SCSI adapter found on NCR 35xx&n; *  (and maybe some other) Microchannel machines.&n; *&n; * Code taken mostly from Cyberstorm SCSI drivers&n; *   Copyright (C) 1996 Jesper Skov (jskov@cygnus.co.uk)&n; *&n; * Hacked to work with the NCR MCA stuff by Tymm Twillman (tymm@computer.org)&n; *   1998&n; */
macro_line|#include &quot;NCR53C9x.h&quot;
macro_line|#ifndef MCA_53C9X_H
DECL|macro|MCA_53C9X_H
mdefine_line|#define MCA_53C9X_H
multiline_comment|/*&n; * From ibmmca.c (IBM scsi controller card driver) -- used for turning PS2 disk&n; *  activity LED on and off&n; */
DECL|macro|PS2_SYS_CTR
mdefine_line|#define PS2_SYS_CTR&t;0x92
r_extern
r_int
id|mca_esp_detect
c_func
(paren
r_struct
id|SHT
op_star
)paren
suffix:semicolon
r_extern
r_int
id|mca_esp_release
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_extern
r_const
r_char
op_star
id|esp_info
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_extern
r_int
id|esp_queue
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
r_extern
r_int
id|esp_command
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_extern
r_int
id|esp_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_extern
r_int
id|esp_reset
c_func
(paren
id|Scsi_Cmnd
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
id|esp_proc_info
c_func
(paren
r_char
op_star
id|buffer
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|length
comma
r_int
id|hostno
comma
r_int
id|inout
)paren
suffix:semicolon
DECL|macro|MCA_53C9X
mdefine_line|#define MCA_53C9X         { proc_name:&t;&t;&quot;esp&quot;, &bslash;&n;&t;&t;&t;    name:&t;&t;&quot;NCR 53c9x SCSI&quot;, &bslash;&n;&t;&t;&t;    detect:&t;&t;mca_esp_detect, &bslash;&n;&t;&t;&t;    release:&t;&t;mca_esp_release, &bslash;&n;&t;&t;&t;    queuecommand:&t;esp_queue, &bslash;&n;&t;&t;&t;    abort:&t;&t;esp_abort, &bslash;&n;&t;&t;&t;    reset:&t;&t;esp_reset, &bslash;&n;&t;&t;&t;    can_queue:          7, &bslash;&n;&t;&t;&t;    sg_tablesize:&t;SG_ALL, &bslash;&n;&t;&t;&t;    cmd_per_lun:&t;1, &bslash;&n;                            unchecked_isa_dma:  1, &bslash;&n;&t;&t;&t;    use_clustering:&t;DISABLE_CLUSTERING }
multiline_comment|/* Ports the ncr&squot;s 53c94 can be put at; indexed by pos register value */
DECL|macro|MCA_53C9X_IO_PORTS
mdefine_line|#define MCA_53C9X_IO_PORTS {                             &bslash;&n;                         0x0000, 0x0240, 0x0340, 0x0400, &bslash;&n;&t;                 0x0420, 0x3240, 0x8240, 0xA240, &bslash;&n;&t;                }
multiline_comment|/*&n; * Supposedly there were some cards put together with the &squot;c9x and 86c01.  If&n; *   they have different ID&squot;s from the ones on the 3500 series machines, &n; *   you can add them here and hopefully things will work out.&n; */
DECL|macro|MCA_53C9X_IDS
mdefine_line|#define MCA_53C9X_IDS {          &bslash;&n;                         0x7F4C, &bslash;&n;&t;&t;&t; 0x0000, &bslash;&n;                        }
macro_line|#endif /* MCA_53C9X_H */
eof
