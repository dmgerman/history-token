multiline_comment|/*********************************************************************&n; *                &n; * Filename:      irda_device.h&n; * Version:       0.9&n; * Description:   Contains various declarations used by the drivers&n; * Status:        Experimental.&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Tue Apr 14 12:41:42 1998&n; * Modified at:   Mon Mar 20 09:08:57 2000&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * &n; *     Copyright (c) 1999-2000 Dag Brattli, All Rights Reserved.&n; *     Copyright (c) 1998 Thomas Davis, &lt;ratbert@radiks.net&gt;,&n; *     Copyright (c) 2000-2002 Jean Tourrilhes &lt;jt@hpl.hp.com&gt;&n; *&n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; * &n; *     This program is distributed in the hope that it will be useful,&n; *     but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the&n; *     GNU General Public License for more details.&n; * &n; *     You should have received a copy of the GNU General Public License &n; *     along with this program; if not, write to the Free Software &n; *     Foundation, Inc., 59 Temple Place, Suite 330, Boston, &n; *     MA 02111-1307 USA&n; *     &n; ********************************************************************/
multiline_comment|/*&n; * This header contains all the IrDA definitions a driver really&n; * needs, and therefore the driver should not need to include&n; * any other IrDA headers - Jean II&n; */
macro_line|#ifndef IRDA_DEVICE_H
DECL|macro|IRDA_DEVICE_H
mdefine_line|#define IRDA_DEVICE_H
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;&t;&t;/* struct sk_buff */
macro_line|#include &lt;linux/irda.h&gt;
macro_line|#include &lt;net/pkt_sched.h&gt;
macro_line|#include &lt;net/irda/irda.h&gt;
macro_line|#include &lt;net/irda/qos.h&gt;&t;&t;/* struct qos_info */
macro_line|#include &lt;net/irda/irqueue.h&gt;&t;&t;/* irda_queue_t */
multiline_comment|/* A few forward declarations (to make compiler happy) */
r_struct
id|irlap_cb
suffix:semicolon
multiline_comment|/* Some non-standard interface flags (should not conflict with any in if.h) */
DECL|macro|IFF_SIR
mdefine_line|#define IFF_SIR &t;0x0001 /* Supports SIR speeds */
DECL|macro|IFF_MIR
mdefine_line|#define IFF_MIR &t;0x0002 /* Supports MIR speeds */
DECL|macro|IFF_FIR
mdefine_line|#define IFF_FIR &t;0x0004 /* Supports FIR speeds */
DECL|macro|IFF_VFIR
mdefine_line|#define IFF_VFIR        0x0008 /* Supports VFIR speeds */
DECL|macro|IFF_PIO
mdefine_line|#define IFF_PIO   &t;0x0010 /* Supports PIO transfer of data */
DECL|macro|IFF_DMA
mdefine_line|#define IFF_DMA&t;&t;0x0020 /* Supports DMA transfer of data */
DECL|macro|IFF_SHM
mdefine_line|#define IFF_SHM         0x0040 /* Supports shared memory data transfers */
DECL|macro|IFF_DONGLE
mdefine_line|#define IFF_DONGLE      0x0080 /* Interface has a dongle attached */
DECL|macro|IFF_AIR
mdefine_line|#define IFF_AIR         0x0100 /* Supports Advanced IR (AIR) standards */
DECL|macro|IO_XMIT
mdefine_line|#define IO_XMIT 0x01
DECL|macro|IO_RECV
mdefine_line|#define IO_RECV 0x02
r_typedef
r_enum
(brace
DECL|enumerator|IRDA_IRLAP
id|IRDA_IRLAP
comma
multiline_comment|/* IrDA mode, and deliver to IrLAP */
DECL|enumerator|IRDA_RAW
id|IRDA_RAW
comma
multiline_comment|/* IrDA mode */
DECL|enumerator|SHARP_ASK
id|SHARP_ASK
comma
DECL|enumerator|TV_REMOTE
id|TV_REMOTE
comma
multiline_comment|/* Also known as Consumer Electronics IR */
DECL|typedef|INFRARED_MODE
)brace
id|INFRARED_MODE
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|IRDA_TASK_INIT
id|IRDA_TASK_INIT
comma
multiline_comment|/* All tasks are initialized with this state */
DECL|enumerator|IRDA_TASK_DONE
id|IRDA_TASK_DONE
comma
multiline_comment|/* Signals that the task is finished */
DECL|enumerator|IRDA_TASK_WAIT
id|IRDA_TASK_WAIT
comma
DECL|enumerator|IRDA_TASK_WAIT1
id|IRDA_TASK_WAIT1
comma
DECL|enumerator|IRDA_TASK_WAIT2
id|IRDA_TASK_WAIT2
comma
DECL|enumerator|IRDA_TASK_WAIT3
id|IRDA_TASK_WAIT3
comma
DECL|enumerator|IRDA_TASK_CHILD_INIT
id|IRDA_TASK_CHILD_INIT
comma
multiline_comment|/* Initializing child task */
DECL|enumerator|IRDA_TASK_CHILD_WAIT
id|IRDA_TASK_CHILD_WAIT
comma
multiline_comment|/* Waiting for child task to finish */
DECL|enumerator|IRDA_TASK_CHILD_DONE
id|IRDA_TASK_CHILD_DONE
multiline_comment|/* Child task is finished */
DECL|typedef|IRDA_TASK_STATE
)brace
id|IRDA_TASK_STATE
suffix:semicolon
r_struct
id|irda_task
suffix:semicolon
DECL|typedef|IRDA_TASK_CALLBACK
r_typedef
r_int
(paren
op_star
id|IRDA_TASK_CALLBACK
)paren
(paren
r_struct
id|irda_task
op_star
id|task
)paren
suffix:semicolon
DECL|struct|irda_task
r_struct
id|irda_task
(brace
DECL|member|q
id|irda_queue_t
id|q
suffix:semicolon
DECL|member|magic
id|magic_t
id|magic
suffix:semicolon
DECL|member|state
id|IRDA_TASK_STATE
id|state
suffix:semicolon
DECL|member|function
id|IRDA_TASK_CALLBACK
id|function
suffix:semicolon
DECL|member|finished
id|IRDA_TASK_CALLBACK
id|finished
suffix:semicolon
DECL|member|parent
r_struct
id|irda_task
op_star
id|parent
suffix:semicolon
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
DECL|member|instance
r_void
op_star
id|instance
suffix:semicolon
multiline_comment|/* Instance being called */
DECL|member|param
r_void
op_star
id|param
suffix:semicolon
multiline_comment|/* Parameter to be used by instance */
)brace
suffix:semicolon
multiline_comment|/* Dongle info */
r_struct
id|dongle_reg
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|issue
r_struct
id|dongle_reg
op_star
id|issue
suffix:semicolon
multiline_comment|/* Registration info */
DECL|member|dev
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
multiline_comment|/* Device we are attached to */
DECL|member|speed_task
r_struct
id|irda_task
op_star
id|speed_task
suffix:semicolon
multiline_comment|/* Task handling speed change */
DECL|member|reset_task
r_struct
id|irda_task
op_star
id|reset_task
suffix:semicolon
multiline_comment|/* Task handling reset */
DECL|member|speed
id|__u32
id|speed
suffix:semicolon
multiline_comment|/* Current speed */
multiline_comment|/* Callbacks to the IrDA device driver */
DECL|member|set_mode
r_int
(paren
op_star
id|set_mode
)paren
(paren
r_struct
id|net_device
op_star
comma
r_int
id|mode
)paren
suffix:semicolon
DECL|member|read
r_int
(paren
op_star
id|read
)paren
(paren
r_struct
id|net_device
op_star
id|dev
comma
id|__u8
op_star
id|buf
comma
r_int
id|len
)paren
suffix:semicolon
DECL|member|write
r_int
(paren
op_star
id|write
)paren
(paren
r_struct
id|net_device
op_star
id|dev
comma
id|__u8
op_star
id|buf
comma
r_int
id|len
)paren
suffix:semicolon
DECL|member|set_dtr_rts
r_int
(paren
op_star
id|set_dtr_rts
)paren
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|dtr
comma
r_int
id|rts
)paren
suffix:semicolon
DECL|typedef|dongle_t
)brace
id|dongle_t
suffix:semicolon
multiline_comment|/* Dongle registration info */
DECL|struct|dongle_reg
r_struct
id|dongle_reg
(brace
DECL|member|q
id|irda_queue_t
id|q
suffix:semicolon
multiline_comment|/* Must be first */
DECL|member|type
id|IRDA_DONGLE
id|type
suffix:semicolon
DECL|member|open
r_void
(paren
op_star
id|open
)paren
(paren
id|dongle_t
op_star
id|dongle
comma
r_struct
id|qos_info
op_star
id|qos
)paren
suffix:semicolon
DECL|member|close
r_void
(paren
op_star
id|close
)paren
(paren
id|dongle_t
op_star
id|dongle
)paren
suffix:semicolon
DECL|member|reset
r_int
(paren
op_star
id|reset
)paren
(paren
r_struct
id|irda_task
op_star
id|task
)paren
suffix:semicolon
DECL|member|change_speed
r_int
(paren
op_star
id|change_speed
)paren
(paren
r_struct
id|irda_task
op_star
id|task
)paren
suffix:semicolon
DECL|member|owner
r_struct
id|module
op_star
id|owner
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* &n; * Per-packet information we need to hide inside sk_buff &n; * (must not exceed 48 bytes, check with struct sk_buff) &n; */
DECL|struct|irda_skb_cb
r_struct
id|irda_skb_cb
(brace
DECL|member|magic
id|magic_t
id|magic
suffix:semicolon
multiline_comment|/* Be sure that we can trust the information */
DECL|member|next_speed
id|__u32
id|next_speed
suffix:semicolon
multiline_comment|/* The Speed to be set *after* this frame */
DECL|member|mtt
id|__u16
id|mtt
suffix:semicolon
multiline_comment|/* Minimum turn around time */
DECL|member|xbofs
id|__u16
id|xbofs
suffix:semicolon
multiline_comment|/* Number of xbofs required, used by SIR mode */
DECL|member|next_xbofs
id|__u16
id|next_xbofs
suffix:semicolon
multiline_comment|/* Number of xbofs required *after* this frame */
DECL|member|context
r_void
op_star
id|context
suffix:semicolon
multiline_comment|/* May be used by drivers */
DECL|member|destructor
r_void
(paren
op_star
id|destructor
)paren
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
multiline_comment|/* Used for flow control */
DECL|member|xbofs_delay
id|__u16
id|xbofs_delay
suffix:semicolon
multiline_comment|/* Number of xbofs used for generating the mtt */
DECL|member|line
id|__u8
id|line
suffix:semicolon
multiline_comment|/* Used by IrCOMM in IrLPT mode */
)brace
suffix:semicolon
multiline_comment|/* Chip specific info */
r_typedef
r_struct
(brace
DECL|member|cfg_base
r_int
id|cfg_base
suffix:semicolon
multiline_comment|/* Config register IO base */
DECL|member|sir_base
r_int
id|sir_base
suffix:semicolon
multiline_comment|/* SIR IO base */
DECL|member|fir_base
r_int
id|fir_base
suffix:semicolon
multiline_comment|/* FIR IO base */
DECL|member|mem_base
r_int
id|mem_base
suffix:semicolon
multiline_comment|/* Shared memory base */
DECL|member|sir_ext
r_int
id|sir_ext
suffix:semicolon
multiline_comment|/* Length of SIR iobase */
DECL|member|fir_ext
r_int
id|fir_ext
suffix:semicolon
multiline_comment|/* Length of FIR iobase */
DECL|member|irq
DECL|member|irq2
r_int
id|irq
comma
id|irq2
suffix:semicolon
multiline_comment|/* Interrupts used */
DECL|member|dma
DECL|member|dma2
r_int
id|dma
comma
id|dma2
suffix:semicolon
multiline_comment|/* DMA channel(s) used */
DECL|member|fifo_size
r_int
id|fifo_size
suffix:semicolon
multiline_comment|/* FIFO size */
DECL|member|irqflags
r_int
id|irqflags
suffix:semicolon
multiline_comment|/* interrupt flags (ie, SA_SHIRQ|SA_INTERRUPT) */
DECL|member|direction
r_int
id|direction
suffix:semicolon
multiline_comment|/* Link direction, used by some FIR drivers */
DECL|member|enabled
r_int
id|enabled
suffix:semicolon
multiline_comment|/* Powered on? */
DECL|member|suspended
r_int
id|suspended
suffix:semicolon
multiline_comment|/* Suspended by APM */
DECL|member|speed
id|__u32
id|speed
suffix:semicolon
multiline_comment|/* Currently used speed */
DECL|member|new_speed
id|__u32
id|new_speed
suffix:semicolon
multiline_comment|/* Speed we must change to when Tx is finished */
DECL|member|dongle_id
r_int
id|dongle_id
suffix:semicolon
multiline_comment|/* Dongle or transceiver currently used */
DECL|typedef|chipio_t
)brace
id|chipio_t
suffix:semicolon
multiline_comment|/* IO buffer specific info (inspired by struct sk_buff) */
r_typedef
r_struct
(brace
DECL|member|state
r_int
id|state
suffix:semicolon
multiline_comment|/* Receiving state (transmit state not used) */
DECL|member|in_frame
r_int
id|in_frame
suffix:semicolon
multiline_comment|/* True if receiving frame */
DECL|member|head
id|__u8
op_star
id|head
suffix:semicolon
multiline_comment|/* start of buffer */
DECL|member|data
id|__u8
op_star
id|data
suffix:semicolon
multiline_comment|/* start of data in buffer */
DECL|member|len
r_int
id|len
suffix:semicolon
multiline_comment|/* current length of data */
DECL|member|truesize
r_int
id|truesize
suffix:semicolon
multiline_comment|/* total allocated size of buffer */
DECL|member|fcs
id|__u16
id|fcs
suffix:semicolon
DECL|member|skb
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
multiline_comment|/* ZeroCopy Rx in async_unwrap_char() */
DECL|typedef|iobuff_t
)brace
id|iobuff_t
suffix:semicolon
multiline_comment|/* Maximum SIR frame (skb) that we expect to receive *unwrapped*.&n; * Max LAP MTU (I field) is 2048 bytes max (IrLAP 1.1, chapt 6.6.5, p40).&n; * Max LAP header is 2 bytes (for now).&n; * Max CRC is 2 bytes at SIR, 4 bytes at FIR. &n; * Need 1 byte for skb_reserve() to align IP header for IrLAN.&n; * Add a few extra bytes just to be safe (buffer is power of two anyway)&n; * Jean II */
DECL|macro|IRDA_SKB_MAX_MTU
mdefine_line|#define IRDA_SKB_MAX_MTU&t;2064
multiline_comment|/* Maximum SIR frame that we expect to send, wrapped (i.e. with XBOFS&n; * and escaped characters on top of above). */
DECL|macro|IRDA_SIR_MAX_FRAME
mdefine_line|#define IRDA_SIR_MAX_FRAME&t;4269
multiline_comment|/* The SIR unwrapper async_unwrap_char() will use a Rx-copy-break mechanism&n; * when using the optional ZeroCopy Rx, where only small frames are memcpy&n; * to a smaller skb to save memory. This is the threshold under which copy&n; * will happen (and over which it won&squot;t happen).&n; * Some FIR drivers may use this #define as well...&n; * This is the same value as various Ethernet drivers. - Jean II */
DECL|macro|IRDA_RX_COPY_THRESHOLD
mdefine_line|#define IRDA_RX_COPY_THRESHOLD  256
multiline_comment|/* Function prototypes */
r_int
id|irda_device_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|irda_device_cleanup
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* IrLAP entry points used by the drivers.&n; * We declare them here to avoid the driver pulling a whole bunch stack&n; * headers they don&squot;t really need - Jean II */
r_struct
id|irlap_cb
op_star
id|irlap_open
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|qos_info
op_star
id|qos
comma
r_const
r_char
op_star
id|hw_name
)paren
suffix:semicolon
r_void
id|irlap_close
c_func
(paren
r_struct
id|irlap_cb
op_star
id|self
)paren
suffix:semicolon
multiline_comment|/* Interface to be uses by IrLAP */
r_void
id|irda_device_set_media_busy
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|status
)paren
suffix:semicolon
r_int
id|irda_device_is_media_busy
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_int
id|irda_device_is_receiving
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/* Interface for internal use */
DECL|function|irda_device_txqueue_empty
r_static
r_inline
r_int
id|irda_device_txqueue_empty
c_func
(paren
r_const
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_return
(paren
id|skb_queue_len
c_func
(paren
op_amp
id|dev-&gt;qdisc-&gt;q
)paren
op_eq
l_int|0
)paren
suffix:semicolon
)brace
r_int
id|irda_device_set_raw_mode
c_func
(paren
r_struct
id|net_device
op_star
id|self
comma
r_int
id|status
)paren
suffix:semicolon
r_int
id|irda_device_set_dtr_rts
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|dtr
comma
r_int
id|rts
)paren
suffix:semicolon
r_int
id|irda_device_change_speed
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
id|__u32
id|speed
)paren
suffix:semicolon
r_struct
id|net_device
op_star
id|alloc_irdadev
c_func
(paren
r_int
id|sizeof_priv
)paren
suffix:semicolon
multiline_comment|/* Dongle interface */
r_void
id|irda_device_unregister_dongle
c_func
(paren
r_struct
id|dongle_reg
op_star
id|dongle
)paren
suffix:semicolon
r_int
id|irda_device_register_dongle
c_func
(paren
r_struct
id|dongle_reg
op_star
id|dongle
)paren
suffix:semicolon
id|dongle_t
op_star
id|irda_device_dongle_init
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|type
)paren
suffix:semicolon
r_int
id|irda_device_dongle_cleanup
c_func
(paren
id|dongle_t
op_star
id|dongle
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_ISA
r_void
id|irda_setup_dma
c_func
(paren
r_int
id|channel
comma
r_char
op_star
id|buffer
comma
r_int
id|count
comma
r_int
id|mode
)paren
suffix:semicolon
macro_line|#endif
r_void
id|irda_task_delete
c_func
(paren
r_struct
id|irda_task
op_star
id|task
)paren
suffix:semicolon
r_struct
id|irda_task
op_star
id|irda_task_execute
c_func
(paren
r_void
op_star
id|instance
comma
id|IRDA_TASK_CALLBACK
id|function
comma
id|IRDA_TASK_CALLBACK
id|finished
comma
r_struct
id|irda_task
op_star
id|parent
comma
r_void
op_star
id|param
)paren
suffix:semicolon
r_void
id|irda_task_next_state
c_func
(paren
r_struct
id|irda_task
op_star
id|task
comma
id|IRDA_TASK_STATE
id|state
)paren
suffix:semicolon
multiline_comment|/*&n; * Function irda_get_mtt (skb)&n; *&n; *    Utility function for getting the minimum turnaround time out of &n; *    the skb, where it has been hidden in the cb field.&n; */
DECL|function|irda_get_mtt
r_static
r_inline
id|__u16
id|irda_get_mtt
c_func
(paren
r_const
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_const
r_struct
id|irda_skb_cb
op_star
id|cb
op_assign
(paren
r_const
r_struct
id|irda_skb_cb
op_star
)paren
id|skb-&gt;cb
suffix:semicolon
r_return
(paren
id|cb-&gt;magic
op_eq
id|LAP_MAGIC
)paren
ques
c_cond
id|cb-&gt;mtt
suffix:colon
l_int|10000
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irda_get_next_speed (skb)&n; *&n; *    Extract the speed that should be set *after* this frame from the skb&n; *&n; * Note : return -1 for user space frames&n; */
DECL|function|irda_get_next_speed
r_static
r_inline
id|__u32
id|irda_get_next_speed
c_func
(paren
r_const
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_const
r_struct
id|irda_skb_cb
op_star
id|cb
op_assign
(paren
r_const
r_struct
id|irda_skb_cb
op_star
)paren
id|skb-&gt;cb
suffix:semicolon
r_return
(paren
id|cb-&gt;magic
op_eq
id|LAP_MAGIC
)paren
ques
c_cond
id|cb-&gt;next_speed
suffix:colon
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irda_get_next_xbofs (skb)&n; *&n; *    Extract the xbofs that should be set for this frame from the skb&n; *&n; * Note : default to 10 for user space frames&n; */
DECL|function|irda_get_xbofs
r_static
r_inline
id|__u16
id|irda_get_xbofs
c_func
(paren
r_const
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_const
r_struct
id|irda_skb_cb
op_star
id|cb
op_assign
(paren
r_const
r_struct
id|irda_skb_cb
op_star
)paren
id|skb-&gt;cb
suffix:semicolon
r_return
(paren
id|cb-&gt;magic
op_eq
id|LAP_MAGIC
)paren
ques
c_cond
id|cb-&gt;xbofs
suffix:colon
l_int|10
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irda_get_next_xbofs (skb)&n; *&n; *    Extract the xbofs that should be set *after* this frame from the skb&n; *&n; * Note : return -1 for user space frames&n; */
DECL|function|irda_get_next_xbofs
r_static
r_inline
id|__u16
id|irda_get_next_xbofs
c_func
(paren
r_const
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_const
r_struct
id|irda_skb_cb
op_star
id|cb
op_assign
(paren
r_const
r_struct
id|irda_skb_cb
op_star
)paren
id|skb-&gt;cb
suffix:semicolon
r_return
(paren
id|cb-&gt;magic
op_eq
id|LAP_MAGIC
)paren
ques
c_cond
id|cb-&gt;next_xbofs
suffix:colon
op_minus
l_int|1
suffix:semicolon
)brace
macro_line|#endif /* IRDA_DEVICE_H */
eof
