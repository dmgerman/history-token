macro_line|#ifndef HAYESESP_H
DECL|macro|HAYESESP_H
mdefine_line|#define HAYESESP_H
DECL|struct|hayes_esp_config
r_struct
id|hayes_esp_config
(brace
DECL|member|flow_on
r_int
id|flow_on
suffix:semicolon
DECL|member|flow_off
r_int
id|flow_off
suffix:semicolon
DECL|member|rx_trigger
r_int
id|rx_trigger
suffix:semicolon
DECL|member|tx_trigger
r_int
id|tx_trigger
suffix:semicolon
DECL|member|pio_threshold
r_int
id|pio_threshold
suffix:semicolon
DECL|member|rx_timeout
r_int
r_char
id|rx_timeout
suffix:semicolon
DECL|member|dma_channel
r_char
id|dma_channel
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
DECL|macro|ESP_DMA_CHANNEL
mdefine_line|#define ESP_DMA_CHANNEL   0
DECL|macro|ESP_RX_TRIGGER
mdefine_line|#define ESP_RX_TRIGGER    768
DECL|macro|ESP_TX_TRIGGER
mdefine_line|#define ESP_TX_TRIGGER    768
DECL|macro|ESP_FLOW_OFF
mdefine_line|#define ESP_FLOW_OFF      1016
DECL|macro|ESP_FLOW_ON
mdefine_line|#define ESP_FLOW_ON       944
DECL|macro|ESP_RX_TMOUT
mdefine_line|#define ESP_RX_TMOUT      128
DECL|macro|ESP_PIO_THRESHOLD
mdefine_line|#define ESP_PIO_THRESHOLD 32
DECL|macro|ESP_IN_MAJOR
mdefine_line|#define ESP_IN_MAJOR&t;57&t;/* major dev # for dial in */
DECL|macro|ESP_OUT_MAJOR
mdefine_line|#define ESP_OUT_MAJOR&t;58&t;/* major dev # for dial out */
DECL|macro|ESPC_SCALE
mdefine_line|#define ESPC_SCALE &t;3
DECL|macro|UART_ESI_BASE
mdefine_line|#define UART_ESI_BASE&t;0x00
DECL|macro|UART_ESI_SID
mdefine_line|#define UART_ESI_SID&t;0x01
DECL|macro|UART_ESI_RX
mdefine_line|#define UART_ESI_RX&t;0x02
DECL|macro|UART_ESI_TX
mdefine_line|#define UART_ESI_TX&t;0x02
DECL|macro|UART_ESI_CMD1
mdefine_line|#define UART_ESI_CMD1&t;0x04
DECL|macro|UART_ESI_CMD2
mdefine_line|#define UART_ESI_CMD2&t;0x05
DECL|macro|UART_ESI_STAT1
mdefine_line|#define UART_ESI_STAT1&t;0x04
DECL|macro|UART_ESI_STAT2
mdefine_line|#define UART_ESI_STAT2&t;0x05
DECL|macro|UART_ESI_RWS
mdefine_line|#define UART_ESI_RWS&t;0x07
DECL|macro|UART_IER_DMA_TMOUT
mdefine_line|#define UART_IER_DMA_TMOUT&t;0x80
DECL|macro|UART_IER_DMA_TC
mdefine_line|#define UART_IER_DMA_TC&t;&t;0x08
DECL|macro|ESI_SET_IRQ
mdefine_line|#define ESI_SET_IRQ&t;&t;0x04
DECL|macro|ESI_SET_DMA_TMOUT
mdefine_line|#define ESI_SET_DMA_TMOUT&t;0x05
DECL|macro|ESI_SET_SRV_MASK
mdefine_line|#define ESI_SET_SRV_MASK&t;0x06
DECL|macro|ESI_SET_ERR_MASK
mdefine_line|#define ESI_SET_ERR_MASK&t;0x07
DECL|macro|ESI_SET_FLOW_CNTL
mdefine_line|#define ESI_SET_FLOW_CNTL&t;0x08
DECL|macro|ESI_SET_FLOW_CHARS
mdefine_line|#define ESI_SET_FLOW_CHARS&t;0x09
DECL|macro|ESI_SET_FLOW_LVL
mdefine_line|#define ESI_SET_FLOW_LVL&t;0x0a
DECL|macro|ESI_SET_TRIGGER
mdefine_line|#define ESI_SET_TRIGGER&t;&t;0x0b
DECL|macro|ESI_SET_RX_TIMEOUT
mdefine_line|#define ESI_SET_RX_TIMEOUT&t;0x0c
DECL|macro|ESI_SET_FLOW_TMOUT
mdefine_line|#define ESI_SET_FLOW_TMOUT&t;0x0d
DECL|macro|ESI_WRITE_UART
mdefine_line|#define ESI_WRITE_UART&t;&t;0x0e
DECL|macro|ESI_READ_UART
mdefine_line|#define ESI_READ_UART&t;&t;0x0f
DECL|macro|ESI_SET_MODE
mdefine_line|#define ESI_SET_MODE&t;&t;0x10
DECL|macro|ESI_GET_ERR_STAT
mdefine_line|#define ESI_GET_ERR_STAT&t;0x12
DECL|macro|ESI_GET_UART_STAT
mdefine_line|#define ESI_GET_UART_STAT&t;0x13
DECL|macro|ESI_GET_RX_AVAIL
mdefine_line|#define ESI_GET_RX_AVAIL&t;0x14
DECL|macro|ESI_GET_TX_AVAIL
mdefine_line|#define ESI_GET_TX_AVAIL&t;0x15
DECL|macro|ESI_START_DMA_RX
mdefine_line|#define ESI_START_DMA_RX&t;0x16
DECL|macro|ESI_START_DMA_TX
mdefine_line|#define ESI_START_DMA_TX&t;0x17
DECL|macro|ESI_ISSUE_BREAK
mdefine_line|#define ESI_ISSUE_BREAK&t;&t;0x1a
DECL|macro|ESI_FLUSH_RX
mdefine_line|#define ESI_FLUSH_RX&t;&t;0x1b
DECL|macro|ESI_FLUSH_TX
mdefine_line|#define ESI_FLUSH_TX&t;&t;0x1c
DECL|macro|ESI_SET_BAUD
mdefine_line|#define ESI_SET_BAUD&t;&t;0x1d
DECL|macro|ESI_SET_ENH_IRQ
mdefine_line|#define ESI_SET_ENH_IRQ&t;&t;0x1f
DECL|macro|ESI_SET_REINTR
mdefine_line|#define ESI_SET_REINTR&t;&t;0x20
DECL|macro|ESI_SET_PRESCALAR
mdefine_line|#define ESI_SET_PRESCALAR&t;0x23
DECL|macro|ESI_NO_COMMAND
mdefine_line|#define ESI_NO_COMMAND&t;&t;0xff
DECL|macro|ESP_STAT_RX_TIMEOUT
mdefine_line|#define ESP_STAT_RX_TIMEOUT&t;0x01
DECL|macro|ESP_STAT_DMA_RX
mdefine_line|#define ESP_STAT_DMA_RX&t;&t;0x02
DECL|macro|ESP_STAT_DMA_TX
mdefine_line|#define ESP_STAT_DMA_TX&t;&t;0x04
DECL|macro|ESP_STAT_NEVER_DMA
mdefine_line|#define ESP_STAT_NEVER_DMA      0x08
DECL|macro|ESP_STAT_USE_PIO
mdefine_line|#define ESP_STAT_USE_PIO        0x10
DECL|macro|ESP_EVENT_WRITE_WAKEUP
mdefine_line|#define ESP_EVENT_WRITE_WAKEUP&t;0
DECL|macro|ESP_MAGIC
mdefine_line|#define ESP_MAGIC&t;&t;0x53ee
DECL|macro|ESP_XMIT_SIZE
mdefine_line|#define ESP_XMIT_SIZE&t;&t;4096
DECL|struct|esp_struct
r_struct
id|esp_struct
(brace
DECL|member|magic
r_int
id|magic
suffix:semicolon
DECL|member|port
r_int
id|port
suffix:semicolon
DECL|member|irq
r_int
id|irq
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
multiline_comment|/* defined in tty.h */
DECL|member|tty
r_struct
id|tty_struct
op_star
id|tty
suffix:semicolon
DECL|member|read_status_mask
r_int
id|read_status_mask
suffix:semicolon
DECL|member|ignore_status_mask
r_int
id|ignore_status_mask
suffix:semicolon
DECL|member|timeout
r_int
id|timeout
suffix:semicolon
DECL|member|stat_flags
r_int
id|stat_flags
suffix:semicolon
DECL|member|custom_divisor
r_int
id|custom_divisor
suffix:semicolon
DECL|member|close_delay
r_int
id|close_delay
suffix:semicolon
DECL|member|closing_wait
r_int
r_int
id|closing_wait
suffix:semicolon
DECL|member|closing_wait2
r_int
r_int
id|closing_wait2
suffix:semicolon
DECL|member|IER
r_int
id|IER
suffix:semicolon
multiline_comment|/* Interrupt Enable Register */
DECL|member|MCR
r_int
id|MCR
suffix:semicolon
multiline_comment|/* Modem control register */
DECL|member|event
r_int
r_int
id|event
suffix:semicolon
DECL|member|last_active
r_int
r_int
id|last_active
suffix:semicolon
DECL|member|line
r_int
id|line
suffix:semicolon
DECL|member|count
r_int
id|count
suffix:semicolon
multiline_comment|/* # of fd on device */
DECL|member|blocked_open
r_int
id|blocked_open
suffix:semicolon
multiline_comment|/* # of blocked opens */
DECL|member|session
r_int
id|session
suffix:semicolon
multiline_comment|/* Session of opening process */
DECL|member|pgrp
r_int
id|pgrp
suffix:semicolon
multiline_comment|/* pgrp of opening process */
DECL|member|xmit_buf
r_int
r_char
op_star
id|xmit_buf
suffix:semicolon
DECL|member|xmit_head
r_int
id|xmit_head
suffix:semicolon
DECL|member|xmit_tail
r_int
id|xmit_tail
suffix:semicolon
DECL|member|xmit_cnt
r_int
id|xmit_cnt
suffix:semicolon
DECL|member|tqueue
r_struct
id|tq_struct
id|tqueue
suffix:semicolon
DECL|member|tqueue_hangup
r_struct
id|tq_struct
id|tqueue_hangup
suffix:semicolon
DECL|member|normal_termios
r_struct
id|termios
id|normal_termios
suffix:semicolon
DECL|member|callout_termios
r_struct
id|termios
id|callout_termios
suffix:semicolon
DECL|member|open_wait
id|wait_queue_head_t
id|open_wait
suffix:semicolon
DECL|member|close_wait
id|wait_queue_head_t
id|close_wait
suffix:semicolon
DECL|member|delta_msr_wait
id|wait_queue_head_t
id|delta_msr_wait
suffix:semicolon
DECL|member|break_wait
id|wait_queue_head_t
id|break_wait
suffix:semicolon
DECL|member|icount
r_struct
id|async_icount
id|icount
suffix:semicolon
multiline_comment|/* kernel counters for the 4 input interrupts */
DECL|member|config
r_struct
id|hayes_esp_config
id|config
suffix:semicolon
multiline_comment|/* port configuration */
DECL|member|next_port
r_struct
id|esp_struct
op_star
id|next_port
suffix:semicolon
multiline_comment|/* For the linked list */
)brace
suffix:semicolon
DECL|struct|esp_pio_buffer
r_struct
id|esp_pio_buffer
(brace
DECL|member|data
r_int
r_char
id|data
(braket
l_int|1024
)braket
suffix:semicolon
DECL|member|next
r_struct
id|esp_pio_buffer
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* ESP_H */
eof
