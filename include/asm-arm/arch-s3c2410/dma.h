multiline_comment|/* linux/include/asm-arm/arch-bast/dma.h&n; *&n; * Copyright (C) 2003,2004 Simtec Electronics&n; *&t;Ben Dooks &lt;ben@simtec.co.uk&gt;&n; *&n; * Samsung S3C2410X DMA support&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * Changelog:&n; *  ??-May-2003 BJD   Created file&n; *  ??-Jun-2003 BJD   Added more dma functionality to go with arch&n; *  10-Nov-2004 BJD   Added sys_device support&n;*/
macro_line|#ifndef __ASM_ARCH_DMA_H
DECL|macro|__ASM_ARCH_DMA_H
mdefine_line|#define __ASM_ARCH_DMA_H __FILE__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sysdev.h&gt;
macro_line|#include &quot;hardware.h&quot;
multiline_comment|/*&n; * This is the maximum DMA address(physical address) that can be DMAd to.&n; *&n; */
DECL|macro|MAX_DMA_ADDRESS
mdefine_line|#define MAX_DMA_ADDRESS&t;&t;0x20000000
DECL|macro|MAX_DMA_TRANSFER_SIZE
mdefine_line|#define MAX_DMA_TRANSFER_SIZE   0x100000 /* Data Unit is half word  */
multiline_comment|/* according to the samsung port, we cannot use the regular&n; * dma channels... we must therefore provide our own interface&n; * for DMA, and allow our drivers to use that.&n; */
DECL|macro|MAX_DMA_CHANNELS
mdefine_line|#define MAX_DMA_CHANNELS&t;0
multiline_comment|/* we have 4 dma channels */
DECL|macro|S3C2410_DMA_CHANNELS
mdefine_line|#define S3C2410_DMA_CHANNELS        (4)
multiline_comment|/* types */
r_typedef
r_enum
(brace
DECL|enumerator|S3C2410_DMA_IDLE
id|S3C2410_DMA_IDLE
comma
DECL|enumerator|S3C2410_DMA_RUNNING
id|S3C2410_DMA_RUNNING
comma
DECL|enumerator|S3C2410_DMA_PAUSED
id|S3C2410_DMA_PAUSED
DECL|typedef|s3c2410_dma_state_t
)brace
id|s3c2410_dma_state_t
suffix:semicolon
multiline_comment|/* s3c2410_dma_loadst_t&n; *&n; * This represents the state of the DMA engine, wrt to the loaded / running&n; * transfers. Since we don&squot;t have any way of knowing exactly the state of&n; * the DMA transfers, we need to know the state to make decisions on wether&n; * we can&n; *&n; * S3C2410_DMA_NONE&n; *&n; * There are no buffers loaded (the channel should be inactive)&n; *&n; * S3C2410_DMA_1LOADED&n; *&n; * There is one buffer loaded, however it has not been confirmed to be&n; * loaded by the DMA engine. This may be because the channel is not&n; * yet running, or the DMA driver decided that it was too costly to&n; * sit and wait for it to happen.&n; *&n; * S3C2410_DMA_1RUNNING&n; *&n; * The buffer has been confirmed running, and not finisged&n; *&n; * S3C2410_DMA_1LOADED_1RUNNING&n; *&n; * There is a buffer waiting to be loaded by the DMA engine, and one&n; * currently running.&n;*/
r_typedef
r_enum
(brace
DECL|enumerator|S3C2410_DMALOAD_NONE
id|S3C2410_DMALOAD_NONE
comma
DECL|enumerator|S3C2410_DMALOAD_1LOADED
id|S3C2410_DMALOAD_1LOADED
comma
DECL|enumerator|S3C2410_DMALOAD_1RUNNING
id|S3C2410_DMALOAD_1RUNNING
comma
DECL|enumerator|S3C2410_DMALOAD_1LOADED_1RUNNING
id|S3C2410_DMALOAD_1LOADED_1RUNNING
comma
DECL|typedef|s3c2410_dma_loadst_t
)brace
id|s3c2410_dma_loadst_t
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|S3C2410_RES_OK
id|S3C2410_RES_OK
comma
DECL|enumerator|S3C2410_RES_ERR
id|S3C2410_RES_ERR
comma
DECL|enumerator|S3C2410_RES_ABORT
id|S3C2410_RES_ABORT
DECL|typedef|s3c2410_dma_buffresult_t
)brace
id|s3c2410_dma_buffresult_t
suffix:semicolon
DECL|typedef|s3c2410_dmasrc_t
r_typedef
r_enum
id|s3c2410_dmasrc_e
id|s3c2410_dmasrc_t
suffix:semicolon
DECL|enum|s3c2410_dmasrc_e
r_enum
id|s3c2410_dmasrc_e
(brace
DECL|enumerator|S3C2410_DMASRC_HW
id|S3C2410_DMASRC_HW
comma
multiline_comment|/* source is memory */
DECL|enumerator|S3C2410_DMASRC_MEM
id|S3C2410_DMASRC_MEM
multiline_comment|/* source is hardware */
)brace
suffix:semicolon
multiline_comment|/* enum s3c2410_chan_op_e&n; *&n; * operation codes passed to the DMA code by the user, and also used&n; * to inform the current channel owner of any changes to the system state&n;*/
DECL|enum|s3c2410_chan_op_e
r_enum
id|s3c2410_chan_op_e
(brace
DECL|enumerator|S3C2410_DMAOP_START
id|S3C2410_DMAOP_START
comma
DECL|enumerator|S3C2410_DMAOP_STOP
id|S3C2410_DMAOP_STOP
comma
DECL|enumerator|S3C2410_DMAOP_PAUSE
id|S3C2410_DMAOP_PAUSE
comma
DECL|enumerator|S3C2410_DMAOP_RESUME
id|S3C2410_DMAOP_RESUME
comma
DECL|enumerator|S3C2410_DMAOP_FLUSH
id|S3C2410_DMAOP_FLUSH
comma
DECL|enumerator|S3C2410_DMAOP_TIMEOUT
id|S3C2410_DMAOP_TIMEOUT
comma
multiline_comment|/* internal signal to handler */
)brace
suffix:semicolon
DECL|typedef|s3c2410_chan_op_t
r_typedef
r_enum
id|s3c2410_chan_op_e
id|s3c2410_chan_op_t
suffix:semicolon
multiline_comment|/* flags */
DECL|macro|S3C2410_DMAF_SLOW
mdefine_line|#define S3C2410_DMAF_SLOW         (1&lt;&lt;0)   /* slow, so don&squot;t worry about&n;&t;&t;&t;&t;&t;    * waiting for reloads */
DECL|macro|S3C2410_DMAF_AUTOSTART
mdefine_line|#define S3C2410_DMAF_AUTOSTART    (1&lt;&lt;1)   /* auto-start if buffer queued */
multiline_comment|/* dma buffer */
DECL|typedef|s3c2410_dma_buf_t
r_typedef
r_struct
id|s3c2410_dma_buf_s
id|s3c2410_dma_buf_t
suffix:semicolon
DECL|struct|s3c2410_dma_client
r_struct
id|s3c2410_dma_client
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|s3c2410_dma_client_t
r_typedef
r_struct
id|s3c2410_dma_client
id|s3c2410_dma_client_t
suffix:semicolon
multiline_comment|/* s3c2410_dma_buf_s&n; *&n; * internally used buffer structure to describe a queued or running&n; * buffer.&n;*/
DECL|struct|s3c2410_dma_buf_s
r_struct
id|s3c2410_dma_buf_s
(brace
DECL|member|next
id|s3c2410_dma_buf_t
op_star
id|next
suffix:semicolon
DECL|member|magic
r_int
id|magic
suffix:semicolon
multiline_comment|/* magic */
DECL|member|size
r_int
id|size
suffix:semicolon
multiline_comment|/* buffer size in bytes */
DECL|member|data
id|dma_addr_t
id|data
suffix:semicolon
multiline_comment|/* start of DMA data */
DECL|member|ptr
id|dma_addr_t
id|ptr
suffix:semicolon
multiline_comment|/* where the DMA got to [1] */
DECL|member|id
r_void
op_star
id|id
suffix:semicolon
multiline_comment|/* client&squot;s id */
)brace
suffix:semicolon
multiline_comment|/* [1] is this updated for both recv/send modes? */
DECL|typedef|s3c2410_dma_chan_t
r_typedef
r_struct
id|s3c2410_dma_chan_s
id|s3c2410_dma_chan_t
suffix:semicolon
multiline_comment|/* s3c2410_dma_cbfn_t&n; *&n; * buffer callback routine type&n;*/
DECL|typedef|s3c2410_dma_cbfn_t
r_typedef
r_void
(paren
op_star
id|s3c2410_dma_cbfn_t
)paren
(paren
id|s3c2410_dma_chan_t
op_star
comma
r_void
op_star
id|buf
comma
r_int
id|size
comma
id|s3c2410_dma_buffresult_t
id|result
)paren
suffix:semicolon
DECL|typedef|s3c2410_dma_opfn_t
r_typedef
r_int
(paren
op_star
id|s3c2410_dma_opfn_t
)paren
(paren
id|s3c2410_dma_chan_t
op_star
comma
id|s3c2410_chan_op_t
)paren
suffix:semicolon
DECL|struct|s3c2410_dma_stats_s
r_struct
id|s3c2410_dma_stats_s
(brace
DECL|member|loads
r_int
r_int
id|loads
suffix:semicolon
DECL|member|timeout_longest
r_int
r_int
id|timeout_longest
suffix:semicolon
DECL|member|timeout_shortest
r_int
r_int
id|timeout_shortest
suffix:semicolon
DECL|member|timeout_avg
r_int
r_int
id|timeout_avg
suffix:semicolon
DECL|member|timeout_failed
r_int
r_int
id|timeout_failed
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|s3c2410_dma_stats_t
r_typedef
r_struct
id|s3c2410_dma_stats_s
id|s3c2410_dma_stats_t
suffix:semicolon
multiline_comment|/* struct s3c2410_dma_chan_s&n; *&n; * full state information for each DMA channel&n;*/
DECL|struct|s3c2410_dma_chan_s
r_struct
id|s3c2410_dma_chan_s
(brace
multiline_comment|/* channel state flags and information */
DECL|member|number
r_int
r_char
id|number
suffix:semicolon
multiline_comment|/* number of this dma channel */
DECL|member|in_use
r_int
r_char
id|in_use
suffix:semicolon
multiline_comment|/* channel allocated */
DECL|member|irq_claimed
r_int
r_char
id|irq_claimed
suffix:semicolon
multiline_comment|/* irq claimed for channel */
DECL|member|irq_enabled
r_int
r_char
id|irq_enabled
suffix:semicolon
multiline_comment|/* irq enabled for channel */
DECL|member|xfer_unit
r_int
r_char
id|xfer_unit
suffix:semicolon
multiline_comment|/* size of an transfer */
multiline_comment|/* channel state */
DECL|member|state
id|s3c2410_dma_state_t
id|state
suffix:semicolon
DECL|member|load_state
id|s3c2410_dma_loadst_t
id|load_state
suffix:semicolon
DECL|member|client
id|s3c2410_dma_client_t
op_star
id|client
suffix:semicolon
multiline_comment|/* channel configuration */
DECL|member|source
id|s3c2410_dmasrc_t
id|source
suffix:semicolon
DECL|member|dev_addr
r_int
r_int
id|dev_addr
suffix:semicolon
DECL|member|load_timeout
r_int
r_int
id|load_timeout
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* channel flags */
multiline_comment|/* channel&squot;s hardware position and configuration */
DECL|member|regs
r_void
id|__iomem
op_star
id|regs
suffix:semicolon
multiline_comment|/* channels registers */
DECL|member|addr_reg
r_void
id|__iomem
op_star
id|addr_reg
suffix:semicolon
multiline_comment|/* data address register */
DECL|member|irq
r_int
r_int
id|irq
suffix:semicolon
multiline_comment|/* channel irq */
DECL|member|dcon
r_int
r_int
id|dcon
suffix:semicolon
multiline_comment|/* default value of DCON */
multiline_comment|/* driver handles */
DECL|member|callback_fn
id|s3c2410_dma_cbfn_t
id|callback_fn
suffix:semicolon
multiline_comment|/* buffer done callback */
DECL|member|op_fn
id|s3c2410_dma_opfn_t
id|op_fn
suffix:semicolon
multiline_comment|/* channel operation callback */
multiline_comment|/* stats gathering */
DECL|member|stats
id|s3c2410_dma_stats_t
op_star
id|stats
suffix:semicolon
DECL|member|stats_store
id|s3c2410_dma_stats_t
id|stats_store
suffix:semicolon
multiline_comment|/* buffer list and information */
DECL|member|curr
id|s3c2410_dma_buf_t
op_star
id|curr
suffix:semicolon
multiline_comment|/* current dma buffer */
DECL|member|next
id|s3c2410_dma_buf_t
op_star
id|next
suffix:semicolon
multiline_comment|/* next buffer to load */
DECL|member|end
id|s3c2410_dma_buf_t
op_star
id|end
suffix:semicolon
multiline_comment|/* end of queue */
multiline_comment|/* system device */
DECL|member|dev
r_struct
id|sys_device
id|dev
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* the currently allocated channel information */
r_extern
id|s3c2410_dma_chan_t
id|s3c2410_chans
(braket
)braket
suffix:semicolon
multiline_comment|/* note, we don&squot;t really use dma_device_t at the moment */
DECL|typedef|dma_device_t
r_typedef
r_int
r_int
id|dma_device_t
suffix:semicolon
multiline_comment|/* functions --------------------------------------------------------------- */
multiline_comment|/* s3c2410_dma_request&n; *&n; * request a dma channel exclusivley&n;*/
r_extern
r_int
id|s3c2410_dma_request
c_func
(paren
id|dmach_t
id|channel
comma
id|s3c2410_dma_client_t
op_star
comma
r_void
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/* s3c2410_dma_ctrl&n; *&n; * change the state of the dma channel&n;*/
r_extern
r_int
id|s3c2410_dma_ctrl
c_func
(paren
id|dmach_t
id|channel
comma
id|s3c2410_chan_op_t
id|op
)paren
suffix:semicolon
multiline_comment|/* s3c2410_dma_setflags&n; *&n; * set the channel&squot;s flags to a given state&n;*/
r_extern
r_int
id|s3c2410_dma_setflags
c_func
(paren
id|dmach_t
id|channel
comma
r_int
r_int
id|flags
)paren
suffix:semicolon
multiline_comment|/* s3c2410_dma_free&n; *&n; * free the dma channel (will also abort any outstanding operations)&n;*/
r_extern
r_int
id|s3c2410_dma_free
c_func
(paren
id|dmach_t
id|channel
comma
id|s3c2410_dma_client_t
op_star
)paren
suffix:semicolon
multiline_comment|/* s3c2410_dma_enqueue&n; *&n; * place the given buffer onto the queue of operations for the channel.&n; * The buffer must be allocated from dma coherent memory, or the Dcache/WB&n; * drained before the buffer is given to the DMA system.&n;*/
r_extern
r_int
id|s3c2410_dma_enqueue
c_func
(paren
id|dmach_t
id|channel
comma
r_void
op_star
id|id
comma
id|dma_addr_t
id|data
comma
r_int
id|size
)paren
suffix:semicolon
multiline_comment|/* s3c2410_dma_config&n; *&n; * configure the dma channel&n;*/
r_extern
r_int
id|s3c2410_dma_config
c_func
(paren
id|dmach_t
id|channel
comma
r_int
id|xferunit
comma
r_int
id|dcon
)paren
suffix:semicolon
multiline_comment|/* s3c2410_dma_devconfig&n; *&n; * configure the device we&squot;re talking to&n;*/
r_extern
r_int
id|s3c2410_dma_devconfig
c_func
(paren
r_int
id|channel
comma
id|s3c2410_dmasrc_t
id|source
comma
r_int
id|hwcfg
comma
r_int
r_int
id|devaddr
)paren
suffix:semicolon
multiline_comment|/* s3c2410_dma_getposition&n; *&n; * get the position that the dma transfer is currently at&n;*/
r_extern
r_int
id|s3c2410_dma_getposition
c_func
(paren
id|dmach_t
id|channel
comma
id|dma_addr_t
op_star
id|src
comma
id|dma_addr_t
op_star
id|dest
)paren
suffix:semicolon
r_extern
r_int
id|s3c2410_dma_set_opfn
c_func
(paren
id|dmach_t
comma
id|s3c2410_dma_opfn_t
id|rtn
)paren
suffix:semicolon
r_extern
r_int
id|s3c2410_dma_set_buffdone_fn
c_func
(paren
id|dmach_t
comma
id|s3c2410_dma_cbfn_t
id|rtn
)paren
suffix:semicolon
multiline_comment|/* DMA Register definitions */
DECL|macro|S3C2410_DMA_DISRC
mdefine_line|#define S3C2410_DMA_DISRC       (0x00)
DECL|macro|S3C2410_DMA_DISRCC
mdefine_line|#define S3C2410_DMA_DISRCC      (0x04)
DECL|macro|S3C2410_DMA_DIDST
mdefine_line|#define S3C2410_DMA_DIDST       (0x08)
DECL|macro|S3C2410_DMA_DIDSTC
mdefine_line|#define S3C2410_DMA_DIDSTC      (0x0C)
DECL|macro|S3C2410_DMA_DCON
mdefine_line|#define S3C2410_DMA_DCON        (0x10)
DECL|macro|S3C2410_DMA_DSTAT
mdefine_line|#define S3C2410_DMA_DSTAT       (0x14)
DECL|macro|S3C2410_DMA_DCSRC
mdefine_line|#define S3C2410_DMA_DCSRC       (0x18)
DECL|macro|S3C2410_DMA_DCDST
mdefine_line|#define S3C2410_DMA_DCDST       (0x1C)
DECL|macro|S3C2410_DMA_DMASKTRIG
mdefine_line|#define S3C2410_DMA_DMASKTRIG   (0x20)
DECL|macro|S3C2410_DISRCC_INC
mdefine_line|#define S3C2410_DISRCC_INC&t;(1&lt;&lt;0)
DECL|macro|S3C2410_DISRCC_APB
mdefine_line|#define S3C2410_DISRCC_APB&t;(1&lt;&lt;1)
DECL|macro|S3C2410_DMASKTRIG_STOP
mdefine_line|#define S3C2410_DMASKTRIG_STOP   (1&lt;&lt;2)
DECL|macro|S3C2410_DMASKTRIG_ON
mdefine_line|#define S3C2410_DMASKTRIG_ON     (1&lt;&lt;1)
DECL|macro|S3C2410_DMASKTRIG_SWTRIG
mdefine_line|#define S3C2410_DMASKTRIG_SWTRIG (1&lt;&lt;0)
DECL|macro|S3C2410_DCON_DEMAND
mdefine_line|#define S3C2410_DCON_DEMAND     (0&lt;&lt;31)
DECL|macro|S3C2410_DCON_HANDSHAKE
mdefine_line|#define S3C2410_DCON_HANDSHAKE  (1&lt;&lt;31)
DECL|macro|S3C2410_DCON_SYNC_PCLK
mdefine_line|#define S3C2410_DCON_SYNC_PCLK  (0&lt;&lt;30)
DECL|macro|S3C2410_DCON_SYNC_HCLK
mdefine_line|#define S3C2410_DCON_SYNC_HCLK  (1&lt;&lt;30)
DECL|macro|S3C2410_DCON_INTREQ
mdefine_line|#define S3C2410_DCON_INTREQ     (1&lt;&lt;29)
DECL|macro|S3C2410_DCON_CH0_XDREQ0
mdefine_line|#define S3C2410_DCON_CH0_XDREQ0&t;(0&lt;&lt;24)
DECL|macro|S3C2410_DCON_CH0_UART0
mdefine_line|#define S3C2410_DCON_CH0_UART0&t;(1&lt;&lt;24)
DECL|macro|S3C2410_DCON_CH0_SDI
mdefine_line|#define S3C2410_DCON_CH0_SDI&t;(2&lt;&lt;24)
DECL|macro|S3C2410_DCON_CH0_TIMER
mdefine_line|#define S3C2410_DCON_CH0_TIMER&t;(3&lt;&lt;24)
DECL|macro|S3C2410_DCON_CH0_USBEP1
mdefine_line|#define S3C2410_DCON_CH0_USBEP1&t;(4&lt;&lt;24)
DECL|macro|S3C2410_DCON_CH1_XDREQ1
mdefine_line|#define S3C2410_DCON_CH1_XDREQ1&t;(0&lt;&lt;24)
DECL|macro|S3C2410_DCON_CH1_UART1
mdefine_line|#define S3C2410_DCON_CH1_UART1&t;(1&lt;&lt;24)
DECL|macro|S3C2410_DCON_CH1_I2SSDI
mdefine_line|#define S3C2410_DCON_CH1_I2SSDI&t;(2&lt;&lt;24)
DECL|macro|S3C2410_DCON_CH1_SPI
mdefine_line|#define S3C2410_DCON_CH1_SPI&t;(3&lt;&lt;24)
DECL|macro|S3C2410_DCON_CH1_USBEP2
mdefine_line|#define S3C2410_DCON_CH1_USBEP2&t;(4&lt;&lt;24)
DECL|macro|S3C2410_DCON_CH2_I2SSDO
mdefine_line|#define S3C2410_DCON_CH2_I2SSDO&t;(0&lt;&lt;24)
DECL|macro|S3C2410_DCON_CH2_I2SSDI
mdefine_line|#define S3C2410_DCON_CH2_I2SSDI&t;(1&lt;&lt;24)
DECL|macro|S3C2410_DCON_CH2_SDI
mdefine_line|#define S3C2410_DCON_CH2_SDI&t;(2&lt;&lt;24)
DECL|macro|S3C2410_DCON_CH2_TIMER
mdefine_line|#define S3C2410_DCON_CH2_TIMER&t;(3&lt;&lt;24)
DECL|macro|S3C2410_DCON_CH2_USBEP3
mdefine_line|#define S3C2410_DCON_CH2_USBEP3&t;(4&lt;&lt;24)
DECL|macro|S3C2410_DCON_CH3_UART2
mdefine_line|#define S3C2410_DCON_CH3_UART2&t;(0&lt;&lt;24)
DECL|macro|S3C2410_DCON_CH3_SDI
mdefine_line|#define S3C2410_DCON_CH3_SDI&t;(1&lt;&lt;24)
DECL|macro|S3C2410_DCON_CH3_SPI
mdefine_line|#define S3C2410_DCON_CH3_SPI&t;(2&lt;&lt;24)
DECL|macro|S3C2410_DCON_CH3_TIMER
mdefine_line|#define S3C2410_DCON_CH3_TIMER&t;(3&lt;&lt;24)
DECL|macro|S3C2410_DCON_CH3_USBEP4
mdefine_line|#define S3C2410_DCON_CH3_USBEP4&t;(4&lt;&lt;24)
DECL|macro|S3C2410_DCON_SRCSHIFT
mdefine_line|#define S3C2410_DCON_SRCSHIFT   (24)
DECL|macro|S3C2410_DCON_SRCMASK
mdefine_line|#define S3C2410_DCON_SRCMASK&t;(7&lt;&lt;24)
DECL|macro|S3C2410_DCON_BYTE
mdefine_line|#define S3C2410_DCON_BYTE       (0&lt;&lt;20)
DECL|macro|S3C2410_DCON_HALFWORD
mdefine_line|#define S3C2410_DCON_HALFWORD   (1&lt;&lt;20)
DECL|macro|S3C2410_DCON_WORD
mdefine_line|#define S3C2410_DCON_WORD       (2&lt;&lt;20)
DECL|macro|S3C2410_DCON_AUTORELOAD
mdefine_line|#define S3C2410_DCON_AUTORELOAD (0&lt;&lt;22)
DECL|macro|S3C2410_DCON_NORELOAD
mdefine_line|#define S3C2410_DCON_NORELOAD   (1&lt;&lt;22)
DECL|macro|S3C2410_DCON_HWTRIG
mdefine_line|#define S3C2410_DCON_HWTRIG     (1&lt;&lt;23)
macro_line|#ifdef CONFIG_CPU_S3C2440
DECL|macro|S3C2440_DIDSTC_CHKINT
mdefine_line|#define S3C2440_DIDSTC_CHKINT&t;(1&lt;&lt;2)
DECL|macro|S3C2440_DCON_CH0_I2SSDO
mdefine_line|#define S3C2440_DCON_CH0_I2SSDO&t;(5&lt;&lt;24)
DECL|macro|S3C2440_DCON_CH0_PCMIN
mdefine_line|#define S3C2440_DCON_CH0_PCMIN&t;(6&lt;&lt;24)
DECL|macro|S3C2440_DCON_CH1_PCMOUT
mdefine_line|#define S3C2440_DCON_CH1_PCMOUT&t;(5&lt;&lt;24)
DECL|macro|S3C2440_DCON_CH1_SDI
mdefine_line|#define S3C2440_DCON_CH1_SDI&t;(6&lt;&lt;24)
DECL|macro|S3C2440_DCON_CH2_PCMIN
mdefine_line|#define S3C2440_DCON_CH2_PCMIN&t;(5&lt;&lt;24)
DECL|macro|S3C2440_DCON_CH2_MICIN
mdefine_line|#define S3C2440_DCON_CH2_MICIN&t;(6&lt;&lt;24)
DECL|macro|S3C2440_DCON_CH3_MICIN
mdefine_line|#define S3C2440_DCON_CH3_MICIN&t;(5&lt;&lt;24)
DECL|macro|S3C2440_DCON_CH3_PCMOUT
mdefine_line|#define S3C2440_DCON_CH3_PCMOUT&t;(6&lt;&lt;24)
macro_line|#endif
macro_line|#endif /* __ASM_ARCH_DMA_H */
eof
