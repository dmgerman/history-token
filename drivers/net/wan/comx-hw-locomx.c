multiline_comment|/*&n; * Hardware driver for the LoCOMX card, using the generic z85230&n; * functions&n; *&n; * Author: Gergely Madarasz &lt;gorgo@itc.hu&gt;&n; *&n; * Based on skeleton code and old LoCOMX driver by Tivadar Szemethy &lt;tiv@itc.hu&gt; &n; * and the hostess_sv11 driver&n; *&n; * Contributors:&n; * Arnaldo Carvalho de Melo &lt;acme@conectiva.com.br&gt; (0.14)&n; *&n; * Copyright (C) 1999 ITConsult-Pro Co. &lt;info@itc.hu&gt;&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; *&n; * Version 0.10 (99/06/17):&n; *&t;&t;- rewritten for the z85230 layer&n; *&n; * Version 0.11 (99/06/21):&n; *&t;&t;- some printk&squot;s fixed&n; *&t;&t;- get rid of a memory leak (it was impossible though :))&n; * &n; * Version 0.12 (99/07/07):&n; *&t;&t;- check CTS for modem lines, not DCD (which is always high&n; *&t;&t;  in case of this board)&n; * Version 0.13 (99/07/08):&n; *&t;&t;- Fix the transmitter status check&n; *&t;&t;- Handle the net device statistics better&n; * Version 0.14 (00/08/15):&n; * &t;&t;- resource release on failure at LOCOMX_init&n; */
DECL|macro|VERSION
mdefine_line|#define VERSION &quot;0.14&quot;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &quot;comx.h&quot;
macro_line|#include &quot;z85230.h&quot;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Gergely Madarasz &lt;gorgo@itc.hu&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Hardware driver for the LoCOMX board&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|macro|RX_DMA
mdefine_line|#define RX_DMA 3
DECL|macro|TX_DMA
mdefine_line|#define TX_DMA 1
DECL|macro|LOCOMX_ID
mdefine_line|#define LOCOMX_ID 0x33
DECL|macro|LOCOMX_IO_EXTENT
mdefine_line|#define LOCOMX_IO_EXTENT 8
DECL|macro|LOCOMX_DEFAULT_IO
mdefine_line|#define LOCOMX_DEFAULT_IO 0x368
DECL|macro|LOCOMX_DEFAULT_IRQ
mdefine_line|#define LOCOMX_DEFAULT_IRQ 7
DECL|variable|z8530_locomx
id|u8
id|z8530_locomx
(braket
)braket
op_assign
(brace
l_int|11
comma
id|TCRTxCP
comma
l_int|14
comma
id|DTRREQ
comma
l_int|255
)brace
suffix:semicolon
DECL|struct|locomx_data
r_struct
id|locomx_data
(brace
DECL|member|io_extent
r_int
id|io_extent
suffix:semicolon
DECL|member|board
r_struct
id|z8530_dev
id|board
suffix:semicolon
DECL|member|status_timer
r_struct
id|timer_list
id|status_timer
suffix:semicolon
)brace
suffix:semicolon
DECL|function|LOCOMX_txe
r_static
r_int
id|LOCOMX_txe
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|comx_channel
op_star
id|ch
op_assign
id|dev-&gt;priv
suffix:semicolon
r_struct
id|locomx_data
op_star
id|hw
op_assign
id|ch-&gt;HW_privdata
suffix:semicolon
r_return
(paren
op_logical_neg
id|hw-&gt;board.chanA.tx_next_skb
)paren
suffix:semicolon
)brace
DECL|function|locomx_rx
r_static
r_void
id|locomx_rx
c_func
(paren
r_struct
id|z8530_channel
op_star
id|c
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
id|c-&gt;netdevice
suffix:semicolon
r_struct
id|comx_channel
op_star
id|ch
op_assign
id|dev-&gt;priv
suffix:semicolon
r_if
c_cond
(paren
id|ch-&gt;debug_flags
op_amp
id|DEBUG_HW_RX
)paren
(brace
id|comx_debug_skb
c_func
(paren
id|dev
comma
id|skb
comma
l_string|&quot;locomx_rx receiving&quot;
)paren
suffix:semicolon
)brace
id|ch
op_member_access_from_pointer
id|LINE_rx
c_func
(paren
id|dev
comma
id|skb
)paren
suffix:semicolon
)brace
DECL|function|LOCOMX_send_packet
r_static
r_int
id|LOCOMX_send_packet
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|comx_channel
op_star
id|ch
op_assign
(paren
r_struct
id|comx_channel
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_struct
id|locomx_data
op_star
id|hw
op_assign
id|ch-&gt;HW_privdata
suffix:semicolon
r_if
c_cond
(paren
id|ch-&gt;debug_flags
op_amp
id|DEBUG_HW_TX
)paren
(brace
id|comx_debug_bytes
c_func
(paren
id|dev
comma
id|skb-&gt;data
comma
id|skb-&gt;len
comma
l_string|&quot;LOCOMX_send_packet&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|ch-&gt;line_status
op_amp
id|LINE_UP
)paren
)paren
(brace
r_return
id|FRAME_DROPPED
suffix:semicolon
)brace
r_if
c_cond
(paren
id|z8530_queue_xmit
c_func
(paren
op_amp
id|hw-&gt;board.chanA
comma
id|skb
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: FRAME_DROPPED&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
r_return
id|FRAME_DROPPED
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ch-&gt;debug_flags
op_amp
id|DEBUG_HW_TX
)paren
(brace
id|comx_debug
c_func
(paren
id|dev
comma
l_string|&quot;%s: LOCOMX_send_packet was successful&bslash;n&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|hw-&gt;board.chanA.tx_next_skb
)paren
(brace
r_return
id|FRAME_QUEUED
suffix:semicolon
)brace
r_else
(brace
r_return
id|FRAME_ACCEPTED
suffix:semicolon
)brace
)brace
DECL|function|locomx_status_timerfun
r_static
r_void
id|locomx_status_timerfun
c_func
(paren
r_int
r_int
id|d
)paren
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
(paren
r_struct
id|net_device
op_star
)paren
id|d
suffix:semicolon
r_struct
id|comx_channel
op_star
id|ch
op_assign
id|dev-&gt;priv
suffix:semicolon
r_struct
id|locomx_data
op_star
id|hw
op_assign
id|ch-&gt;HW_privdata
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|ch-&gt;line_status
op_amp
id|LINE_UP
)paren
op_logical_and
(paren
id|hw-&gt;board.chanA.status
op_amp
id|CTS
)paren
)paren
(brace
id|ch
op_member_access_from_pointer
id|LINE_status
c_func
(paren
id|dev
comma
id|ch-&gt;line_status
op_or
id|LINE_UP
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|ch-&gt;line_status
op_amp
id|LINE_UP
)paren
op_logical_and
op_logical_neg
(paren
id|hw-&gt;board.chanA.status
op_amp
id|CTS
)paren
)paren
(brace
id|ch
op_member_access_from_pointer
id|LINE_status
c_func
(paren
id|dev
comma
id|ch-&gt;line_status
op_amp
op_complement
id|LINE_UP
)paren
suffix:semicolon
)brace
id|mod_timer
c_func
(paren
op_amp
id|hw-&gt;status_timer
comma
id|jiffies
op_plus
id|ch-&gt;lineup_delay
op_star
id|HZ
)paren
suffix:semicolon
)brace
DECL|function|LOCOMX_open
r_static
r_int
id|LOCOMX_open
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|comx_channel
op_star
id|ch
op_assign
id|dev-&gt;priv
suffix:semicolon
r_struct
id|locomx_data
op_star
id|hw
op_assign
id|ch-&gt;HW_privdata
suffix:semicolon
r_struct
id|proc_dir_entry
op_star
id|procfile
op_assign
id|ch-&gt;procdir-&gt;subdir
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;base_addr
op_logical_or
op_logical_neg
id|dev-&gt;irq
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|dev-&gt;base_addr
comma
id|hw-&gt;io_extent
comma
id|dev-&gt;name
)paren
)paren
(brace
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
id|hw-&gt;board.chanA.ctrlio
op_assign
id|dev-&gt;base_addr
op_plus
l_int|5
suffix:semicolon
id|hw-&gt;board.chanA.dataio
op_assign
id|dev-&gt;base_addr
op_plus
l_int|7
suffix:semicolon
id|hw-&gt;board.irq
op_assign
id|dev-&gt;irq
suffix:semicolon
id|hw-&gt;board.chanA.netdevice
op_assign
id|dev
suffix:semicolon
id|hw-&gt;board.chanA.dev
op_assign
op_amp
id|hw-&gt;board
suffix:semicolon
id|hw-&gt;board.name
op_assign
id|dev-&gt;name
suffix:semicolon
id|hw-&gt;board.chanA.txdma
op_assign
id|TX_DMA
suffix:semicolon
id|hw-&gt;board.chanA.rxdma
op_assign
id|RX_DMA
suffix:semicolon
id|hw-&gt;board.chanA.irqs
op_assign
op_amp
id|z8530_nop
suffix:semicolon
id|hw-&gt;board.chanB.irqs
op_assign
op_amp
id|z8530_nop
suffix:semicolon
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|dev-&gt;irq
comma
id|z8530_interrupt
comma
id|SA_INTERRUPT
comma
id|dev-&gt;name
comma
op_amp
id|hw-&gt;board
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: unable to obtain irq %d&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|dev-&gt;irq
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EAGAIN
suffix:semicolon
r_goto
id|irq_fail
suffix:semicolon
)brace
r_if
c_cond
(paren
id|request_dma
c_func
(paren
id|TX_DMA
comma
l_string|&quot;LoCOMX (TX)&quot;
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: unable to obtain TX DMA (DMA channel %d)&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|TX_DMA
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EAGAIN
suffix:semicolon
r_goto
id|dma1_fail
suffix:semicolon
)brace
r_if
c_cond
(paren
id|request_dma
c_func
(paren
id|RX_DMA
comma
l_string|&quot;LoCOMX (RX)&quot;
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: unable to obtain RX DMA (DMA channel %d)&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|RX_DMA
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EAGAIN
suffix:semicolon
r_goto
id|dma2_fail
suffix:semicolon
)brace
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|z8530_init
c_func
(paren
op_amp
id|hw-&gt;board
)paren
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: Z8530 device not found.&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|z8530_fail
suffix:semicolon
)brace
id|hw-&gt;board.chanA.dcdcheck
op_assign
id|CTS
suffix:semicolon
id|z8530_channel_load
c_func
(paren
op_amp
id|hw-&gt;board.chanA
comma
id|z8530_hdlc_kilostream_85230
)paren
suffix:semicolon
id|z8530_channel_load
c_func
(paren
op_amp
id|hw-&gt;board.chanA
comma
id|z8530_locomx
)paren
suffix:semicolon
id|z8530_channel_load
c_func
(paren
op_amp
id|hw-&gt;board.chanB
comma
id|z8530_dead_port
)paren
suffix:semicolon
id|z8530_describe
c_func
(paren
op_amp
id|hw-&gt;board
comma
l_string|&quot;I/O&quot;
comma
id|dev-&gt;base_addr
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|z8530_sync_dma_open
c_func
(paren
id|dev
comma
op_amp
id|hw-&gt;board.chanA
)paren
)paren
op_ne
l_int|0
)paren
(brace
r_goto
id|z8530_fail
suffix:semicolon
)brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|hw-&gt;board.active
op_assign
l_int|1
suffix:semicolon
id|hw-&gt;board.chanA.rx_function
op_assign
id|locomx_rx
suffix:semicolon
id|ch-&gt;init_status
op_or_assign
id|HW_OPEN
suffix:semicolon
r_if
c_cond
(paren
id|hw-&gt;board.chanA.status
op_amp
id|DCD
)paren
(brace
id|ch-&gt;line_status
op_or_assign
id|LINE_UP
suffix:semicolon
)brace
r_else
(brace
id|ch-&gt;line_status
op_and_assign
op_complement
id|LINE_UP
suffix:semicolon
)brace
id|comx_status
c_func
(paren
id|dev
comma
id|ch-&gt;line_status
)paren
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|hw-&gt;status_timer
)paren
suffix:semicolon
id|hw-&gt;status_timer.function
op_assign
id|locomx_status_timerfun
suffix:semicolon
id|hw-&gt;status_timer.data
op_assign
(paren
r_int
r_int
)paren
id|dev
suffix:semicolon
id|hw-&gt;status_timer.expires
op_assign
id|jiffies
op_plus
id|ch-&gt;lineup_delay
op_star
id|HZ
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|hw-&gt;status_timer
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|procfile
suffix:semicolon
id|procfile
op_assign
id|procfile-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|procfile-&gt;name
comma
id|FILENAME_IO
)paren
op_eq
l_int|0
op_logical_or
id|strcmp
c_func
(paren
id|procfile-&gt;name
comma
id|FILENAME_IRQ
)paren
op_eq
l_int|0
)paren
(brace
id|procfile-&gt;mode
op_assign
id|S_IFREG
op_or
l_int|0444
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
id|z8530_fail
suffix:colon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|free_dma
c_func
(paren
id|RX_DMA
)paren
suffix:semicolon
id|dma2_fail
suffix:colon
id|free_dma
c_func
(paren
id|TX_DMA
)paren
suffix:semicolon
id|dma1_fail
suffix:colon
id|free_irq
c_func
(paren
id|dev-&gt;irq
comma
op_amp
id|hw-&gt;board
)paren
suffix:semicolon
id|irq_fail
suffix:colon
id|release_region
c_func
(paren
id|dev-&gt;base_addr
comma
id|hw-&gt;io_extent
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|LOCOMX_close
r_static
r_int
id|LOCOMX_close
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|comx_channel
op_star
id|ch
op_assign
id|dev-&gt;priv
suffix:semicolon
r_struct
id|locomx_data
op_star
id|hw
op_assign
id|ch-&gt;HW_privdata
suffix:semicolon
r_struct
id|proc_dir_entry
op_star
id|procfile
op_assign
id|ch-&gt;procdir-&gt;subdir
suffix:semicolon
id|hw-&gt;board.chanA.rx_function
op_assign
id|z8530_null_rx
suffix:semicolon
id|netif_stop_queue
c_func
(paren
id|dev
)paren
suffix:semicolon
id|z8530_sync_dma_close
c_func
(paren
id|dev
comma
op_amp
id|hw-&gt;board.chanA
)paren
suffix:semicolon
id|z8530_shutdown
c_func
(paren
op_amp
id|hw-&gt;board
)paren
suffix:semicolon
id|del_timer
c_func
(paren
op_amp
id|hw-&gt;status_timer
)paren
suffix:semicolon
id|free_dma
c_func
(paren
id|RX_DMA
)paren
suffix:semicolon
id|free_dma
c_func
(paren
id|TX_DMA
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|dev-&gt;irq
comma
op_amp
id|hw-&gt;board
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|dev-&gt;base_addr
comma
l_int|8
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|procfile
suffix:semicolon
id|procfile
op_assign
id|procfile-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|procfile-&gt;name
comma
id|FILENAME_IO
)paren
op_eq
l_int|0
op_logical_or
id|strcmp
c_func
(paren
id|procfile-&gt;name
comma
id|FILENAME_IRQ
)paren
op_eq
l_int|0
)paren
(brace
id|procfile-&gt;mode
op_assign
id|S_IFREG
op_or
l_int|0644
suffix:semicolon
)brace
)brace
id|ch-&gt;init_status
op_and_assign
op_complement
id|HW_OPEN
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|LOCOMX_statistics
r_static
r_int
id|LOCOMX_statistics
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_char
op_star
id|page
)paren
(brace
r_int
id|len
op_assign
l_int|0
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|len
comma
l_string|&quot;Hello&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|function|LOCOMX_dump
r_static
r_int
id|LOCOMX_dump
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;LOCOMX_dump called&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|locomx_read_proc
r_static
r_int
id|locomx_read_proc
c_func
(paren
r_char
op_star
id|page
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|off
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|file
op_assign
(paren
r_struct
id|proc_dir_entry
op_star
)paren
id|data
suffix:semicolon
r_struct
id|net_device
op_star
id|dev
op_assign
id|file-&gt;parent-&gt;data
suffix:semicolon
r_int
id|len
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|file-&gt;name
comma
id|FILENAME_IO
)paren
op_eq
l_int|0
)paren
(brace
id|len
op_assign
id|sprintf
c_func
(paren
id|page
comma
l_string|&quot;0x%x&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|dev-&gt;base_addr
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|file-&gt;name
comma
id|FILENAME_IRQ
)paren
op_eq
l_int|0
)paren
(brace
id|len
op_assign
id|sprintf
c_func
(paren
id|page
comma
l_string|&quot;%d&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|dev-&gt;irq
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;hw_read_proc: internal error, filename %s&bslash;n&quot;
comma
id|file-&gt;name
)paren
suffix:semicolon
r_return
op_minus
id|EBADF
suffix:semicolon
)brace
r_if
c_cond
(paren
id|off
op_ge
id|len
)paren
(brace
op_star
id|eof
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
op_star
id|start
op_assign
id|page
op_plus
id|off
suffix:semicolon
r_if
c_cond
(paren
id|count
op_ge
id|len
op_minus
id|off
)paren
(brace
op_star
id|eof
op_assign
l_int|1
suffix:semicolon
)brace
r_return
id|min_t
c_func
(paren
r_int
comma
id|count
comma
id|len
op_minus
id|off
)paren
suffix:semicolon
)brace
DECL|function|locomx_write_proc
r_static
r_int
id|locomx_write_proc
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
op_star
id|buffer
comma
id|u_long
id|count
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|entry
op_assign
(paren
r_struct
id|proc_dir_entry
op_star
)paren
id|data
suffix:semicolon
r_struct
id|net_device
op_star
id|dev
op_assign
(paren
r_struct
id|net_device
op_star
)paren
id|entry-&gt;parent-&gt;data
suffix:semicolon
r_int
id|val
suffix:semicolon
r_char
op_star
id|page
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|page
op_assign
(paren
r_char
op_star
)paren
id|__get_free_page
c_func
(paren
id|GFP_KERNEL
)paren
)paren
)paren
(brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|copy_from_user
c_func
(paren
id|page
comma
id|buffer
comma
id|count
op_assign
id|min_t
c_func
(paren
r_int
r_int
comma
id|count
comma
id|PAGE_SIZE
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
(paren
id|page
op_plus
id|count
op_minus
l_int|1
)paren
op_eq
l_char|&squot;&bslash;n&squot;
)paren
(brace
op_star
(paren
id|page
op_plus
id|count
op_minus
l_int|1
)paren
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|entry-&gt;name
comma
id|FILENAME_IO
)paren
op_eq
l_int|0
)paren
(brace
id|val
op_assign
id|simple_strtoul
c_func
(paren
id|page
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
op_ne
l_int|0x360
op_logical_and
id|val
op_ne
l_int|0x368
op_logical_and
id|val
op_ne
l_int|0x370
op_logical_and
id|val
op_ne
l_int|0x378
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;LoCOMX: incorrect io address!&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|dev-&gt;base_addr
op_assign
id|val
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|entry-&gt;name
comma
id|FILENAME_IRQ
)paren
op_eq
l_int|0
)paren
(brace
id|val
op_assign
id|simple_strtoul
c_func
(paren
id|page
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
op_ne
l_int|3
op_logical_and
id|val
op_ne
l_int|4
op_logical_and
id|val
op_ne
l_int|5
op_logical_and
id|val
op_ne
l_int|6
op_logical_and
id|val
op_ne
l_int|7
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;LoCOMX: incorrect irq value!&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|dev-&gt;irq
op_assign
id|val
suffix:semicolon
)brace
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;locomx_write_proc: internal error, filename %s&bslash;n&quot;
comma
id|entry-&gt;name
)paren
suffix:semicolon
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|page
)paren
suffix:semicolon
r_return
op_minus
id|EBADF
suffix:semicolon
)brace
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|page
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
DECL|function|LOCOMX_init
r_static
r_int
id|LOCOMX_init
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|comx_channel
op_star
id|ch
op_assign
(paren
r_struct
id|comx_channel
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_struct
id|locomx_data
op_star
id|hw
suffix:semicolon
r_struct
id|proc_dir_entry
op_star
id|new_file
suffix:semicolon
multiline_comment|/* Alloc data for private structure */
r_if
c_cond
(paren
(paren
id|ch-&gt;HW_privdata
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|locomx_data
)paren
comma
id|GFP_KERNEL
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memset
c_func
(paren
id|hw
op_assign
id|ch-&gt;HW_privdata
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|locomx_data
)paren
)paren
suffix:semicolon
id|hw-&gt;io_extent
op_assign
id|LOCOMX_IO_EXTENT
suffix:semicolon
multiline_comment|/* Register /proc files */
r_if
c_cond
(paren
(paren
id|new_file
op_assign
id|create_proc_entry
c_func
(paren
id|FILENAME_IO
comma
id|S_IFREG
op_or
l_int|0644
comma
id|ch-&gt;procdir
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
r_goto
id|cleanup_HW_privdata
suffix:semicolon
)brace
id|new_file-&gt;data
op_assign
(paren
r_void
op_star
)paren
id|new_file
suffix:semicolon
id|new_file-&gt;read_proc
op_assign
op_amp
id|locomx_read_proc
suffix:semicolon
id|new_file-&gt;write_proc
op_assign
op_amp
id|locomx_write_proc
suffix:semicolon
id|new_file-&gt;nlink
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
(paren
id|new_file
op_assign
id|create_proc_entry
c_func
(paren
id|FILENAME_IRQ
comma
id|S_IFREG
op_or
l_int|0644
comma
id|ch-&gt;procdir
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
r_goto
id|cleanup_filename_io
suffix:semicolon
)brace
id|new_file-&gt;data
op_assign
(paren
r_void
op_star
)paren
id|new_file
suffix:semicolon
id|new_file-&gt;read_proc
op_assign
op_amp
id|locomx_read_proc
suffix:semicolon
id|new_file-&gt;write_proc
op_assign
op_amp
id|locomx_write_proc
suffix:semicolon
id|new_file-&gt;nlink
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* &t;No clock yet */
multiline_comment|/*&n;&t;if ((new_file = create_proc_entry(FILENAME_CLOCK, S_IFREG | 0644, &n;&t;    ch-&gt;procdir)) == NULL) {&n;&t;&t;return -EIO;&n;&t;}&n;&t;new_file-&gt;data = (void *)new_file;&n;&t;new_file-&gt;read_proc = &amp;locomx_read_proc;&n;&t;new_file-&gt;write_proc = &amp;locomx_write_proc;&n;&t;new_file-&gt;nlink = 1;&n;*/
id|ch-&gt;HW_access_board
op_assign
l_int|NULL
suffix:semicolon
id|ch-&gt;HW_release_board
op_assign
l_int|NULL
suffix:semicolon
id|ch-&gt;HW_txe
op_assign
id|LOCOMX_txe
suffix:semicolon
id|ch-&gt;HW_open
op_assign
id|LOCOMX_open
suffix:semicolon
id|ch-&gt;HW_close
op_assign
id|LOCOMX_close
suffix:semicolon
id|ch-&gt;HW_send_packet
op_assign
id|LOCOMX_send_packet
suffix:semicolon
id|ch-&gt;HW_statistics
op_assign
id|LOCOMX_statistics
suffix:semicolon
id|ch-&gt;HW_set_clock
op_assign
l_int|NULL
suffix:semicolon
id|ch-&gt;current_stats
op_assign
op_amp
id|hw-&gt;board.chanA.stats
suffix:semicolon
id|memcpy
c_func
(paren
id|ch-&gt;current_stats
comma
op_amp
id|ch-&gt;stats
comma
r_sizeof
(paren
r_struct
id|net_device_stats
)paren
)paren
suffix:semicolon
id|dev-&gt;base_addr
op_assign
id|LOCOMX_DEFAULT_IO
suffix:semicolon
id|dev-&gt;irq
op_assign
id|LOCOMX_DEFAULT_IRQ
suffix:semicolon
multiline_comment|/* O.K. Count one more user on this module */
id|MOD_INC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|cleanup_filename_io
suffix:colon
id|remove_proc_entry
c_func
(paren
id|FILENAME_IO
comma
id|ch-&gt;procdir
)paren
suffix:semicolon
id|cleanup_HW_privdata
suffix:colon
id|kfree
c_func
(paren
id|ch-&gt;HW_privdata
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
DECL|function|LOCOMX_exit
r_static
r_int
id|LOCOMX_exit
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|comx_channel
op_star
id|ch
op_assign
(paren
r_struct
id|comx_channel
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
id|ch-&gt;HW_access_board
op_assign
l_int|NULL
suffix:semicolon
id|ch-&gt;HW_release_board
op_assign
l_int|NULL
suffix:semicolon
id|ch-&gt;HW_txe
op_assign
l_int|NULL
suffix:semicolon
id|ch-&gt;HW_open
op_assign
l_int|NULL
suffix:semicolon
id|ch-&gt;HW_close
op_assign
l_int|NULL
suffix:semicolon
id|ch-&gt;HW_send_packet
op_assign
l_int|NULL
suffix:semicolon
id|ch-&gt;HW_statistics
op_assign
l_int|NULL
suffix:semicolon
id|ch-&gt;HW_set_clock
op_assign
l_int|NULL
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|ch-&gt;stats
comma
id|ch-&gt;current_stats
comma
r_sizeof
(paren
r_struct
id|net_device_stats
)paren
)paren
suffix:semicolon
id|ch-&gt;current_stats
op_assign
op_amp
id|ch-&gt;stats
suffix:semicolon
id|kfree
c_func
(paren
id|ch-&gt;HW_privdata
)paren
suffix:semicolon
id|remove_proc_entry
c_func
(paren
id|FILENAME_IO
comma
id|ch-&gt;procdir
)paren
suffix:semicolon
id|remove_proc_entry
c_func
(paren
id|FILENAME_IRQ
comma
id|ch-&gt;procdir
)paren
suffix:semicolon
singleline_comment|//&t;remove_proc_entry(FILENAME_CLOCK, ch-&gt;procdir);
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|locomx_hw
r_static
r_struct
id|comx_hardware
id|locomx_hw
op_assign
(brace
l_string|&quot;locomx&quot;
comma
id|VERSION
comma
id|LOCOMX_init
comma
id|LOCOMX_exit
comma
id|LOCOMX_dump
comma
l_int|NULL
)brace
suffix:semicolon
macro_line|#ifdef MODULE
DECL|macro|comx_hw_locomx_init
mdefine_line|#define comx_hw_locomx_init init_module
macro_line|#endif
DECL|function|comx_hw_locomx_init
r_int
id|__init
id|comx_hw_locomx_init
c_func
(paren
r_void
)paren
(brace
id|comx_register_hardware
c_func
(paren
op_amp
id|locomx_hw
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef MODULE
DECL|function|cleanup_module
r_void
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
id|comx_unregister_hardware
c_func
(paren
l_string|&quot;locomx&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#endif
eof
