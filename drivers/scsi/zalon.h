macro_line|#ifndef ZALON7XX_H
DECL|macro|ZALON7XX_H
mdefine_line|#define ZALON7XX_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &quot;sym53c8xx_defs.h&quot;
r_extern
r_int
id|zalon7xx_detect
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
macro_line|#include &lt;scsi/scsicam.h&gt;
r_extern
r_struct
id|proc_dir_entry
id|proc_scsi_zalon7xx
suffix:semicolon
multiline_comment|/* borrowed from drivers/scsi/ncr53c8xx.h */
r_int
id|zalon7xx_detect
c_func
(paren
id|Scsi_Host_Template
op_star
id|tpnt
)paren
suffix:semicolon
r_const
r_char
op_star
id|ncr53c8xx_info
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|host
)paren
suffix:semicolon
r_int
id|ncr53c8xx_queue_command
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
macro_line|#ifdef MODULE
r_int
id|zalon7xx_release
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
macro_line|#else
DECL|macro|zalon7xx_release
mdefine_line|#define zalon7xx_release NULL
macro_line|#endif
DECL|macro|GSC_SCSI_ZALON_OFFSET
mdefine_line|#define GSC_SCSI_ZALON_OFFSET 0x800
DECL|macro|IO_MODULE_EIM
mdefine_line|#define IO_MODULE_EIM&t;&t;(1*4)
DECL|macro|IO_MODULE_DC_ADATA
mdefine_line|#define IO_MODULE_DC_ADATA&t;(2*4)
DECL|macro|IO_MODULE_II_CDATA
mdefine_line|#define IO_MODULE_II_CDATA&t;(3*4)
DECL|macro|IO_MODULE_IO_COMMAND
mdefine_line|#define IO_MODULE_IO_COMMAND&t;(12*4)
DECL|macro|IO_MODULE_IO_STATUS
mdefine_line|#define IO_MODULE_IO_STATUS&t;(13*4)
DECL|macro|IOSTATUS_RY
mdefine_line|#define IOSTATUS_RY             0x40
DECL|macro|IOSTATUS_FE
mdefine_line|#define IOSTATUS_FE             0x80
DECL|macro|IOIIDATA_SMINT5L
mdefine_line|#define IOIIDATA_SMINT5L        0x40000000
DECL|macro|IOIIDATA_MINT5EN
mdefine_line|#define IOIIDATA_MINT5EN        0x20000000
DECL|macro|IOIIDATA_PACKEN
mdefine_line|#define IOIIDATA_PACKEN         0x10000000
DECL|macro|IOIIDATA_PREFETCHEN
mdefine_line|#define IOIIDATA_PREFETCHEN     0x08000000
DECL|macro|IOIIDATA_IOII
mdefine_line|#define IOIIDATA_IOII           0x00000020
DECL|macro|CMD_RESET
mdefine_line|#define CMD_RESET&t;&t;5
macro_line|#endif /* ZALON7XX_H */
eof
