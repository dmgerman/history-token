multiline_comment|/* sun3x_esp.h: Defines and structures for the Sun3x ESP&n; *&n; * (C) 1995 Thomas Bogendoerfer (tsbogend@alpha.franken.de)&n; */
macro_line|#ifndef _SUN3X_ESP_H
DECL|macro|_SUN3X_ESP_H
mdefine_line|#define _SUN3X_ESP_H
multiline_comment|/* For dvma controller register definitions. */
macro_line|#include &lt;asm/dvma.h&gt;
r_extern
r_int
id|sun3x_esp_detect
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
DECL|macro|DMA_PORTS_P
mdefine_line|#define DMA_PORTS_P        (dregs-&gt;cond_reg &amp; DMA_INT_ENAB)
DECL|macro|SCSI_SUN3X_ESP
mdefine_line|#define SCSI_SUN3X_ESP {                                        &bslash;&n;&t;&t;.proc_name      = &quot;esp&quot;,  &t;&t;&t;&bslash;&n;&t;&t;.proc_info      = &amp;esp_proc_info,&t;&t;&t;&bslash;&n;&t;&t;.name           = &quot;Sun ESP 100/100a/200&quot;,&t;&t;&bslash;&n;&t;&t;.detect         = sun3x_esp_detect,&t;&t;&bslash;&n;&t;&t;.info           = esp_info,&t;&t;&t;&bslash;&n;&t;&t;.command        = esp_command,&t;&t;&t;&bslash;&n;&t;&t;.queuecommand   = esp_queue,&t;&t;&t;&bslash;&n;&t;&t;.abort          = esp_abort,&t;&t;&t;&bslash;&n;&t;&t;.reset          = esp_reset,&t;&t;&t;&bslash;&n;&t;&t;.can_queue      = 7,&t;&t;&t;&t;&bslash;&n;&t;&t;.this_id        = 7,&t;&t;&t;&t;&bslash;&n;&t;&t;.sg_tablesize   = SG_ALL,&t;&t;&t;&t;&bslash;&n;&t;&t;.cmd_per_lun    = 1,&t;&t;&t;&t;&bslash;&n;&t;&t;.use_clustering = DISABLE_CLUSTERING, }
macro_line|#endif /* !(_SUN3X_ESP_H) */
eof
