multiline_comment|/* cyberstorm.h: Defines and structures for the CyberStorm SCSI driver.&n; *&n; * Copyright (C) 1996 Jesper Skov (jskov@cygnus.co.uk)&n; */
macro_line|#include &quot;NCR53C9x.h&quot;
macro_line|#ifndef CYBER_ESP_H
DECL|macro|CYBER_ESP_H
mdefine_line|#define CYBER_ESP_H
multiline_comment|/* The controller registers can be found in the Z2 config area at these&n; * offsets:&n; */
DECL|macro|CYBER_ESP_ADDR
mdefine_line|#define CYBER_ESP_ADDR 0xf400
DECL|macro|CYBER_DMA_ADDR
mdefine_line|#define CYBER_DMA_ADDR 0xf800
multiline_comment|/* The CyberStorm DMA interface */
DECL|struct|cyber_dma_registers
r_struct
id|cyber_dma_registers
(brace
DECL|member|dma_addr0
r_volatile
r_int
r_char
id|dma_addr0
suffix:semicolon
multiline_comment|/* DMA address (MSB) [0x000] */
DECL|member|dmapad1
r_int
r_char
id|dmapad1
(braket
l_int|1
)braket
suffix:semicolon
DECL|member|dma_addr1
r_volatile
r_int
r_char
id|dma_addr1
suffix:semicolon
multiline_comment|/* DMA address       [0x002] */
DECL|member|dmapad2
r_int
r_char
id|dmapad2
(braket
l_int|1
)braket
suffix:semicolon
DECL|member|dma_addr2
r_volatile
r_int
r_char
id|dma_addr2
suffix:semicolon
multiline_comment|/* DMA address       [0x004] */
DECL|member|dmapad3
r_int
r_char
id|dmapad3
(braket
l_int|1
)braket
suffix:semicolon
DECL|member|dma_addr3
r_volatile
r_int
r_char
id|dma_addr3
suffix:semicolon
multiline_comment|/* DMA address (LSB) [0x006] */
DECL|member|dmapad4
r_int
r_char
id|dmapad4
(braket
l_int|0x3fb
)braket
suffix:semicolon
DECL|member|cond_reg
r_volatile
r_int
r_char
id|cond_reg
suffix:semicolon
multiline_comment|/* DMA cond    (ro)  [0x402] */
DECL|macro|ctrl_reg
mdefine_line|#define ctrl_reg  cond_reg&t;&t;&t;/* DMA control (wo)  [0x402] */
)brace
suffix:semicolon
multiline_comment|/* DMA control bits */
DECL|macro|CYBER_DMA_LED
mdefine_line|#define CYBER_DMA_LED    0x80&t;/* HD led control 1 = on */
DECL|macro|CYBER_DMA_WRITE
mdefine_line|#define CYBER_DMA_WRITE  0x40&t;/* DMA direction. 1 = write */
DECL|macro|CYBER_DMA_Z3
mdefine_line|#define CYBER_DMA_Z3     0x20&t;/* 16 (Z2) or 32 (CHIP/Z3) bit DMA transfer */
multiline_comment|/* DMA status bits */
DECL|macro|CYBER_DMA_HNDL_INTR
mdefine_line|#define CYBER_DMA_HNDL_INTR 0x80&t;/* DMA IRQ pending? */
multiline_comment|/* The bits below appears to be Phase5 Debug bits only; they were not&n; * described by Phase5 so using them may seem a bit stupid...&n; */
DECL|macro|CYBER_HOST_ID
mdefine_line|#define CYBER_HOST_ID 0x02&t;/* If set, host ID should be 7, otherwise&n;&t;&t;&t;&t; * it should be 6.&n;&t;&t;&t;&t; */
DECL|macro|CYBER_SLOW_CABLE
mdefine_line|#define CYBER_SLOW_CABLE 0x08&t;/* If *not* set, assume SLOW_CABLE */
r_extern
r_int
id|cyber_esp_detect
c_func
(paren
r_struct
id|SHT
op_star
)paren
suffix:semicolon
r_extern
r_int
id|cyber_esp_release
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
DECL|macro|SCSI_CYBERSTORM
mdefine_line|#define SCSI_CYBERSTORM   { proc_name:&t;&t;&quot;esp-cyberstorm&quot;, &bslash;&n;&t;&t;&t;    proc_info:&t;&t;esp_proc_info, &bslash;&n;&t;&t;&t;    name:&t;&t;&quot;CyberStorm SCSI&quot;, &bslash;&n;&t;&t;&t;    detect:&t;&t;cyber_esp_detect, &bslash;&n;&t;&t;&t;    release:&t;&t;cyber_esp_release, &bslash;&n;&t;&t;&t;    queuecommand:&t;esp_queue, &bslash;&n;&t;&t;&t;    abort:&t;&t;esp_abort, &bslash;&n;&t;&t;&t;    reset:&t;&t;esp_reset, &bslash;&n;&t;&t;&t;    can_queue:          7, &bslash;&n;&t;&t;&t;    this_id:&t;&t;7, &bslash;&n;&t;&t;&t;    sg_tablesize:&t;SG_ALL, &bslash;&n;&t;&t;&t;    cmd_per_lun:&t;1, &bslash;&n;&t;&t;&t;    use_clustering:&t;ENABLE_CLUSTERING }
macro_line|#endif /* CYBER_ESP_H */
eof
