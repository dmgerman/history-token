multiline_comment|/* dec_esp.h: Defines and structures for the JAZZ SCSI driver.&n; *&n; * DECstation changes Copyright (C) 1998 Harald Koerfgen&n; * and David Airlie&n; *&n; * based on jazz_esp.h:&n; * Copyright (C) 1997 Thomas Bogendoerfer (tsbogend@alpha.franken.de)&n; */
macro_line|#ifndef DEC_ESP_H
DECL|macro|DEC_ESP_H
mdefine_line|#define DEC_ESP_H
macro_line|#include &quot;NCR53C9x.h&quot;
DECL|macro|DEC_SCSI_SREG
mdefine_line|#define DEC_SCSI_SREG 0
DECL|macro|DEC_SCSI_DMAREG
mdefine_line|#define DEC_SCSI_DMAREG 0x40000
DECL|macro|DEC_SCSI_SRAM
mdefine_line|#define DEC_SCSI_SRAM 0x80000
DECL|macro|DEC_SCSI_DIAG
mdefine_line|#define DEC_SCSI_DIAG 0xC0000
r_extern
r_int
id|dec_esp_detect
c_func
(paren
r_struct
id|SHT
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
DECL|macro|SCSI_DEC_ESP
mdefine_line|#define SCSI_DEC_ESP {                                         &bslash;&n;&t;&t;.proc_name      = &quot;esp&quot;,&t;&t;&t;&t;&bslash;&n;&t;&t;.proc_info      = &amp;esp_proc_info,&t;&t;&t;&bslash;&n;&t;&t;.name           = &quot;NCR53C94&quot;,&t;&t;&t;&bslash;&n;&t;&t;.detect         = dec_esp_detect,&t;&t;&t;&bslash;&n;&t;&t;.info           = esp_info,&t;&t;&t;&bslash;&n;&t;&t;.command        = esp_command,&t;&t;&t;&bslash;&n;&t;&t;.queuecommand   = esp_queue,&t;&t;&t;&bslash;&n;&t;&t;.abort          = esp_abort,&t;&t;&t;&bslash;&n;&t;&t;.reset          = esp_reset,&t;&t;&t;&bslash;&n;&t;&t;.can_queue      = 7,&t;&t;&t;&t;&bslash;&n;&t;&t;.this_id        = 7,&t;&t;&t;&t;&bslash;&n;&t;&t;.sg_tablesize   = SG_ALL,&t;&t;&t;&t;&bslash;&n;&t;&t;.cmd_per_lun    = 1,&t;&t;&t;&t;&bslash;&n;&t;&t;.use_clustering = DISABLE_CLUSTERING, }
macro_line|#endif /* DEC_ESP_H */
eof
