multiline_comment|/* fastlane.h: Defines and structures for the Fastlane SCSI driver.&n; *&n; * Copyright (C) 1996 Jesper Skov (jskov@cygnus.co.uk)&n; */
macro_line|#include &quot;NCR53C9x.h&quot;
macro_line|#ifndef FASTLANE_H
DECL|macro|FASTLANE_H
mdefine_line|#define FASTLANE_H
multiline_comment|/* The controller registers can be found in the Z2 config area at these&n; * offsets:&n; */
DECL|macro|FASTLANE_ESP_ADDR
mdefine_line|#define FASTLANE_ESP_ADDR 0x1000001
DECL|macro|FASTLANE_DMA_ADDR
mdefine_line|#define FASTLANE_DMA_ADDR 0x1000041
multiline_comment|/* The Fastlane DMA interface */
DECL|struct|fastlane_dma_registers
r_struct
id|fastlane_dma_registers
(brace
DECL|member|cond_reg
r_volatile
r_int
r_char
id|cond_reg
suffix:semicolon
multiline_comment|/* DMA status  (ro) [0x0000] */
DECL|macro|ctrl_reg
mdefine_line|#define ctrl_reg  cond_reg&t;&t;&t;/* DMA control (wo) [0x0000] */
DECL|member|dmapad1
r_int
r_char
id|dmapad1
(braket
l_int|0x3f
)braket
suffix:semicolon
DECL|member|clear_strobe
r_volatile
r_int
r_char
id|clear_strobe
suffix:semicolon
multiline_comment|/* DMA clear   (wo) [0x0040] */
)brace
suffix:semicolon
multiline_comment|/* DMA status bits */
DECL|macro|FASTLANE_DMA_MINT
mdefine_line|#define FASTLANE_DMA_MINT  0x80
DECL|macro|FASTLANE_DMA_IACT
mdefine_line|#define FASTLANE_DMA_IACT  0x40
DECL|macro|FASTLANE_DMA_CREQ
mdefine_line|#define FASTLANE_DMA_CREQ  0x20
multiline_comment|/* DMA control bits */
DECL|macro|FASTLANE_DMA_FCODE
mdefine_line|#define FASTLANE_DMA_FCODE 0xa0
DECL|macro|FASTLANE_DMA_MASK
mdefine_line|#define FASTLANE_DMA_MASK  0xf3
DECL|macro|FASTLANE_DMA_LED
mdefine_line|#define FASTLANE_DMA_LED   0x10&t;/* HD led control 1 = on */
DECL|macro|FASTLANE_DMA_WRITE
mdefine_line|#define FASTLANE_DMA_WRITE 0x08 /* 1 = write */
DECL|macro|FASTLANE_DMA_ENABLE
mdefine_line|#define FASTLANE_DMA_ENABLE 0x04 /* Enable DMA */
DECL|macro|FASTLANE_DMA_EDI
mdefine_line|#define FASTLANE_DMA_EDI   0x02&t;/* Enable DMA IRQ ? */
DECL|macro|FASTLANE_DMA_ESI
mdefine_line|#define FASTLANE_DMA_ESI   0x01&t;/* Enable SCSI IRQ */
r_extern
r_int
id|fastlane_esp_detect
c_func
(paren
r_struct
id|SHT
op_star
)paren
suffix:semicolon
r_extern
r_int
id|fastlane_esp_release
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
DECL|macro|SCSI_FASTLANE
mdefine_line|#define SCSI_FASTLANE     { proc_name:&t;&t;&quot;esp-fastlane&quot;, &bslash;&n;&t;&t;&t;    proc_info:&t;&t;esp_proc_info, &bslash;&n;&t;&t;&t;    name:&t;&t;&quot;Fastlane SCSI&quot;, &bslash;&n;&t;&t;&t;    detect:&t;&t;fastlane_esp_detect, &bslash;&n;&t;&t;&t;    release:&t;&t;fastlane_esp_release, &bslash;&n;&t;&t;&t;    queuecommand:&t;esp_queue, &bslash;&n;&t;&t;&t;    abort:&t;&t;esp_abort, &bslash;&n;&t;&t;&t;    reset:&t;&t;esp_reset, &bslash;&n;&t;&t;&t;    can_queue:          7, &bslash;&n;&t;&t;&t;    this_id:&t;&t;7, &bslash;&n;&t;&t;&t;    sg_tablesize:&t;SG_ALL, &bslash;&n;&t;&t;&t;    cmd_per_lun:&t;1, &bslash;&n;&t;&t;&t;    use_clustering:&t;ENABLE_CLUSTERING }
macro_line|#endif /* FASTLANE_H */
eof
