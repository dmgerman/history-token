multiline_comment|/*&n; * IEEE 1394 for Linux&n; *&n; * kernel ISO transmission/reception&n; *&n; * Copyright (C) 2002 Maas Digital LLC&n; *&n; * This code is licensed under the GPL.  See the file COPYING in the root&n; * directory of the kernel sources for details.&n; */
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &quot;iso.h&quot;
DECL|function|hpsb_iso_stop
r_void
id|hpsb_iso_stop
c_func
(paren
r_struct
id|hpsb_iso
op_star
id|iso
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|iso-&gt;flags
op_amp
id|HPSB_ISO_DRIVER_STARTED
)paren
)paren
r_return
suffix:semicolon
id|iso-&gt;host-&gt;driver
op_member_access_from_pointer
id|isoctl
c_func
(paren
id|iso
comma
id|iso-&gt;type
op_eq
id|HPSB_ISO_XMIT
ques
c_cond
id|XMIT_STOP
suffix:colon
id|RECV_STOP
comma
l_int|0
)paren
suffix:semicolon
id|iso-&gt;flags
op_and_assign
op_complement
id|HPSB_ISO_DRIVER_STARTED
suffix:semicolon
)brace
DECL|function|hpsb_iso_shutdown
r_void
id|hpsb_iso_shutdown
c_func
(paren
r_struct
id|hpsb_iso
op_star
id|iso
)paren
(brace
r_if
c_cond
(paren
id|iso-&gt;flags
op_amp
id|HPSB_ISO_DRIVER_INIT
)paren
(brace
id|hpsb_iso_stop
c_func
(paren
id|iso
)paren
suffix:semicolon
id|iso-&gt;host-&gt;driver
op_member_access_from_pointer
id|isoctl
c_func
(paren
id|iso
comma
id|iso-&gt;type
op_eq
id|HPSB_ISO_XMIT
ques
c_cond
id|XMIT_SHUTDOWN
suffix:colon
id|RECV_SHUTDOWN
comma
l_int|0
)paren
suffix:semicolon
id|iso-&gt;flags
op_and_assign
op_complement
id|HPSB_ISO_DRIVER_INIT
suffix:semicolon
)brace
id|dma_region_free
c_func
(paren
op_amp
id|iso-&gt;data_buf
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|iso
)paren
suffix:semicolon
)brace
DECL|function|hpsb_iso_common_init
r_static
r_struct
id|hpsb_iso
op_star
id|hpsb_iso_common_init
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
comma
r_enum
id|hpsb_iso_type
id|type
comma
r_int
r_int
id|data_buf_size
comma
r_int
r_int
id|buf_packets
comma
r_int
id|channel
comma
r_int
id|irq_interval
comma
r_void
(paren
op_star
id|callback
)paren
(paren
r_struct
id|hpsb_iso
op_star
)paren
)paren
(brace
r_struct
id|hpsb_iso
op_star
id|iso
suffix:semicolon
r_int
id|dma_direction
suffix:semicolon
multiline_comment|/* make sure driver supports the ISO API */
r_if
c_cond
(paren
op_logical_neg
id|host-&gt;driver-&gt;isoctl
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;ieee1394: host driver &squot;%s&squot; does not support the rawiso API&bslash;n&quot;
comma
id|host-&gt;driver-&gt;name
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* sanitize parameters */
r_if
c_cond
(paren
id|buf_packets
OL
l_int|2
)paren
(brace
id|buf_packets
op_assign
l_int|2
suffix:semicolon
)brace
r_if
c_cond
(paren
id|irq_interval
template_param
id|buf_packets
op_div
l_int|2
)paren
(brace
id|irq_interval
op_assign
id|buf_packets
op_div
l_int|2
suffix:semicolon
)brace
r_if
c_cond
(paren
id|channel
OL
op_minus
l_int|1
op_logical_or
id|channel
op_ge
l_int|64
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* channel = -1 is OK for multi-channel recv but not for xmit */
r_if
c_cond
(paren
id|type
op_eq
id|HPSB_ISO_XMIT
op_logical_and
id|channel
OL
l_int|0
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* allocate and write the struct hpsb_iso */
id|iso
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|iso
)paren
op_plus
id|buf_packets
op_star
r_sizeof
(paren
r_struct
id|hpsb_iso_packet_info
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|iso
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
id|iso-&gt;infos
op_assign
(paren
r_struct
id|hpsb_iso_packet_info
op_star
)paren
(paren
id|iso
op_plus
l_int|1
)paren
suffix:semicolon
id|iso-&gt;type
op_assign
id|type
suffix:semicolon
id|iso-&gt;host
op_assign
id|host
suffix:semicolon
id|iso-&gt;hostdata
op_assign
l_int|NULL
suffix:semicolon
id|iso-&gt;callback
op_assign
id|callback
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|iso-&gt;waitq
)paren
suffix:semicolon
id|iso-&gt;channel
op_assign
id|channel
suffix:semicolon
id|iso-&gt;irq_interval
op_assign
id|irq_interval
suffix:semicolon
id|dma_region_init
c_func
(paren
op_amp
id|iso-&gt;data_buf
)paren
suffix:semicolon
id|iso-&gt;buf_size
op_assign
id|round_up_to_page
c_func
(paren
id|data_buf_size
)paren
suffix:semicolon
id|iso-&gt;buf_packets
op_assign
id|buf_packets
suffix:semicolon
id|iso-&gt;pkt_dma
op_assign
l_int|0
suffix:semicolon
id|iso-&gt;first_packet
op_assign
l_int|0
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|iso-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|iso-&gt;type
op_eq
id|HPSB_ISO_XMIT
)paren
(brace
id|iso-&gt;n_ready_packets
op_assign
id|iso-&gt;buf_packets
suffix:semicolon
id|dma_direction
op_assign
id|PCI_DMA_TODEVICE
suffix:semicolon
)brace
r_else
(brace
id|iso-&gt;n_ready_packets
op_assign
l_int|0
suffix:semicolon
id|dma_direction
op_assign
id|PCI_DMA_FROMDEVICE
suffix:semicolon
)brace
id|atomic_set
c_func
(paren
op_amp
id|iso-&gt;overflows
comma
l_int|0
)paren
suffix:semicolon
id|iso-&gt;flags
op_assign
l_int|0
suffix:semicolon
id|iso-&gt;prebuffer
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* allocate the packet buffer */
r_if
c_cond
(paren
id|dma_region_alloc
c_func
(paren
op_amp
id|iso-&gt;data_buf
comma
id|iso-&gt;buf_size
comma
id|host-&gt;pdev
comma
id|dma_direction
)paren
)paren
(brace
r_goto
id|err
suffix:semicolon
)brace
r_return
id|iso
suffix:semicolon
id|err
suffix:colon
id|hpsb_iso_shutdown
c_func
(paren
id|iso
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|hpsb_iso_n_ready
r_int
id|hpsb_iso_n_ready
c_func
(paren
r_struct
id|hpsb_iso
op_star
id|iso
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|val
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|iso-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|val
op_assign
id|iso-&gt;n_ready_packets
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|iso-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
DECL|function|hpsb_iso_xmit_init
r_struct
id|hpsb_iso
op_star
id|hpsb_iso_xmit_init
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
comma
r_int
r_int
id|data_buf_size
comma
r_int
r_int
id|buf_packets
comma
r_int
id|channel
comma
r_int
id|speed
comma
r_int
id|irq_interval
comma
r_void
(paren
op_star
id|callback
)paren
(paren
r_struct
id|hpsb_iso
op_star
)paren
)paren
(brace
r_struct
id|hpsb_iso
op_star
id|iso
op_assign
id|hpsb_iso_common_init
c_func
(paren
id|host
comma
id|HPSB_ISO_XMIT
comma
id|data_buf_size
comma
id|buf_packets
comma
id|channel
comma
id|irq_interval
comma
id|callback
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|iso
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
id|iso-&gt;speed
op_assign
id|speed
suffix:semicolon
multiline_comment|/* tell the driver to start working */
r_if
c_cond
(paren
id|host-&gt;driver
op_member_access_from_pointer
id|isoctl
c_func
(paren
id|iso
comma
id|XMIT_INIT
comma
l_int|0
)paren
)paren
(brace
r_goto
id|err
suffix:semicolon
)brace
id|iso-&gt;flags
op_or_assign
id|HPSB_ISO_DRIVER_INIT
suffix:semicolon
r_return
id|iso
suffix:semicolon
id|err
suffix:colon
id|hpsb_iso_shutdown
c_func
(paren
id|iso
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|hpsb_iso_recv_init
r_struct
id|hpsb_iso
op_star
id|hpsb_iso_recv_init
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
comma
r_int
r_int
id|data_buf_size
comma
r_int
r_int
id|buf_packets
comma
r_int
id|channel
comma
r_int
id|irq_interval
comma
r_void
(paren
op_star
id|callback
)paren
(paren
r_struct
id|hpsb_iso
op_star
)paren
)paren
(brace
r_struct
id|hpsb_iso
op_star
id|iso
op_assign
id|hpsb_iso_common_init
c_func
(paren
id|host
comma
id|HPSB_ISO_RECV
comma
id|data_buf_size
comma
id|buf_packets
comma
id|channel
comma
id|irq_interval
comma
id|callback
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|iso
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* tell the driver to start working */
r_if
c_cond
(paren
id|host-&gt;driver
op_member_access_from_pointer
id|isoctl
c_func
(paren
id|iso
comma
id|RECV_INIT
comma
l_int|0
)paren
)paren
(brace
r_goto
id|err
suffix:semicolon
)brace
id|iso-&gt;flags
op_or_assign
id|HPSB_ISO_DRIVER_INIT
suffix:semicolon
r_return
id|iso
suffix:semicolon
id|err
suffix:colon
id|hpsb_iso_shutdown
c_func
(paren
id|iso
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|hpsb_iso_recv_listen_channel
r_int
id|hpsb_iso_recv_listen_channel
c_func
(paren
r_struct
id|hpsb_iso
op_star
id|iso
comma
r_int
r_char
id|channel
)paren
(brace
r_if
c_cond
(paren
id|iso-&gt;type
op_ne
id|HPSB_ISO_RECV
op_logical_or
id|iso-&gt;channel
op_ne
op_minus
l_int|1
op_logical_or
id|channel
op_ge
l_int|64
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
id|iso-&gt;host-&gt;driver
op_member_access_from_pointer
id|isoctl
c_func
(paren
id|iso
comma
id|RECV_LISTEN_CHANNEL
comma
id|channel
)paren
suffix:semicolon
)brace
DECL|function|hpsb_iso_recv_unlisten_channel
r_int
id|hpsb_iso_recv_unlisten_channel
c_func
(paren
r_struct
id|hpsb_iso
op_star
id|iso
comma
r_int
r_char
id|channel
)paren
(brace
r_if
c_cond
(paren
id|iso-&gt;type
op_ne
id|HPSB_ISO_RECV
op_logical_or
id|iso-&gt;channel
op_ne
op_minus
l_int|1
op_logical_or
id|channel
op_ge
l_int|64
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
id|iso-&gt;host-&gt;driver
op_member_access_from_pointer
id|isoctl
c_func
(paren
id|iso
comma
id|RECV_UNLISTEN_CHANNEL
comma
id|channel
)paren
suffix:semicolon
)brace
DECL|function|hpsb_iso_recv_set_channel_mask
r_int
id|hpsb_iso_recv_set_channel_mask
c_func
(paren
r_struct
id|hpsb_iso
op_star
id|iso
comma
id|u64
id|mask
)paren
(brace
r_if
c_cond
(paren
id|iso-&gt;type
op_ne
id|HPSB_ISO_RECV
op_logical_or
id|iso-&gt;channel
op_ne
op_minus
l_int|1
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
id|iso-&gt;host-&gt;driver
op_member_access_from_pointer
id|isoctl
c_func
(paren
id|iso
comma
id|RECV_SET_CHANNEL_MASK
comma
(paren
r_int
r_int
)paren
op_amp
id|mask
)paren
suffix:semicolon
)brace
DECL|function|do_iso_xmit_start
r_static
r_int
id|do_iso_xmit_start
c_func
(paren
r_struct
id|hpsb_iso
op_star
id|iso
comma
r_int
id|cycle
)paren
(brace
r_int
id|retval
op_assign
id|iso-&gt;host-&gt;driver
op_member_access_from_pointer
id|isoctl
c_func
(paren
id|iso
comma
id|XMIT_START
comma
id|cycle
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
(brace
r_return
id|retval
suffix:semicolon
)brace
id|iso-&gt;flags
op_or_assign
id|HPSB_ISO_DRIVER_STARTED
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|hpsb_iso_xmit_start
r_int
id|hpsb_iso_xmit_start
c_func
(paren
r_struct
id|hpsb_iso
op_star
id|iso
comma
r_int
id|cycle
comma
r_int
id|prebuffer
)paren
(brace
r_if
c_cond
(paren
id|iso-&gt;type
op_ne
id|HPSB_ISO_XMIT
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|iso-&gt;flags
op_amp
id|HPSB_ISO_DRIVER_STARTED
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cycle
OL
op_minus
l_int|1
)paren
(brace
id|cycle
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|cycle
op_ge
l_int|8000
)paren
(brace
id|cycle
op_mod_assign
l_int|8000
suffix:semicolon
)brace
id|iso-&gt;xmit_cycle
op_assign
id|cycle
suffix:semicolon
r_if
c_cond
(paren
id|prebuffer
OL
l_int|0
)paren
(brace
id|prebuffer
op_assign
id|iso-&gt;buf_packets
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|prebuffer
op_eq
l_int|0
)paren
(brace
id|prebuffer
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|prebuffer
OG
id|iso-&gt;buf_packets
)paren
(brace
id|prebuffer
op_assign
id|iso-&gt;buf_packets
suffix:semicolon
)brace
id|iso-&gt;prebuffer
op_assign
id|prebuffer
suffix:semicolon
multiline_comment|/* remember the starting cycle; DMA will commence from xmit_queue_packets()&n;&t;   once enough packets have been buffered */
id|iso-&gt;start_cycle
op_assign
id|cycle
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hpsb_iso_recv_start
r_int
id|hpsb_iso_recv_start
c_func
(paren
r_struct
id|hpsb_iso
op_star
id|iso
comma
r_int
id|cycle
comma
r_int
id|tag_mask
comma
r_int
id|sync
)paren
(brace
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
r_int
id|isoctl_args
(braket
l_int|3
)braket
suffix:semicolon
r_if
c_cond
(paren
id|iso-&gt;type
op_ne
id|HPSB_ISO_RECV
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|iso-&gt;flags
op_amp
id|HPSB_ISO_DRIVER_STARTED
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cycle
OL
op_minus
l_int|1
)paren
(brace
id|cycle
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|cycle
op_ge
l_int|8000
)paren
(brace
id|cycle
op_mod_assign
l_int|8000
suffix:semicolon
)brace
id|isoctl_args
(braket
l_int|0
)braket
op_assign
id|cycle
suffix:semicolon
r_if
c_cond
(paren
id|tag_mask
OL
l_int|0
)paren
(brace
multiline_comment|/* match all tags */
id|tag_mask
op_assign
l_int|0xF
suffix:semicolon
)brace
id|isoctl_args
(braket
l_int|1
)braket
op_assign
id|tag_mask
suffix:semicolon
id|isoctl_args
(braket
l_int|2
)braket
op_assign
id|sync
suffix:semicolon
id|retval
op_assign
id|iso-&gt;host-&gt;driver
op_member_access_from_pointer
id|isoctl
c_func
(paren
id|iso
comma
id|RECV_START
comma
(paren
r_int
r_int
)paren
op_amp
id|isoctl_args
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
(brace
r_return
id|retval
suffix:semicolon
)brace
id|iso-&gt;flags
op_or_assign
id|HPSB_ISO_DRIVER_STARTED
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/* check to make sure the user has not supplied bogus values of offset/len&n;   that would cause the kernel to access memory outside the buffer */
DECL|function|hpsb_iso_check_offset_len
r_static
r_int
id|hpsb_iso_check_offset_len
c_func
(paren
r_struct
id|hpsb_iso
op_star
id|iso
comma
r_int
r_int
id|offset
comma
r_int
r_int
id|len
comma
r_int
r_int
op_star
id|out_offset
comma
r_int
r_int
op_star
id|out_len
)paren
(brace
r_if
c_cond
(paren
id|offset
op_ge
id|iso-&gt;buf_size
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
multiline_comment|/* make sure the packet does not go beyond the end of the buffer */
r_if
c_cond
(paren
id|offset
op_plus
id|len
OG
id|iso-&gt;buf_size
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
multiline_comment|/* check for wrap-around */
r_if
c_cond
(paren
id|offset
op_plus
id|len
OL
id|offset
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
multiline_comment|/* now we can trust &squot;offset&squot; and &squot;length&squot; */
op_star
id|out_offset
op_assign
id|offset
suffix:semicolon
op_star
id|out_len
op_assign
id|len
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hpsb_iso_xmit_queue_packet
r_int
id|hpsb_iso_xmit_queue_packet
c_func
(paren
r_struct
id|hpsb_iso
op_star
id|iso
comma
id|u32
id|offset
comma
id|u16
id|len
comma
id|u8
id|tag
comma
id|u8
id|sy
)paren
(brace
r_struct
id|hpsb_iso_packet_info
op_star
id|info
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|rv
suffix:semicolon
r_if
c_cond
(paren
id|iso-&gt;type
op_ne
id|HPSB_ISO_XMIT
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* is there space in the buffer? */
r_if
c_cond
(paren
id|iso-&gt;n_ready_packets
op_le
l_int|0
)paren
(brace
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|info
op_assign
op_amp
id|iso-&gt;infos
(braket
id|iso-&gt;first_packet
)braket
suffix:semicolon
multiline_comment|/* check for bogus offset/length */
r_if
c_cond
(paren
id|hpsb_iso_check_offset_len
c_func
(paren
id|iso
comma
id|offset
comma
id|len
comma
op_amp
id|info-&gt;offset
comma
op_amp
id|info-&gt;len
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|info-&gt;tag
op_assign
id|tag
suffix:semicolon
id|info-&gt;sy
op_assign
id|sy
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|iso-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|rv
op_assign
id|iso-&gt;host-&gt;driver
op_member_access_from_pointer
id|isoctl
c_func
(paren
id|iso
comma
id|XMIT_QUEUE
comma
(paren
r_int
r_int
)paren
id|info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rv
)paren
(brace
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* increment cursors */
id|iso-&gt;first_packet
op_assign
(paren
id|iso-&gt;first_packet
op_plus
l_int|1
)paren
op_mod
id|iso-&gt;buf_packets
suffix:semicolon
id|iso-&gt;xmit_cycle
op_assign
(paren
id|iso-&gt;xmit_cycle
op_plus
l_int|1
)paren
op_mod
l_int|8000
suffix:semicolon
id|iso-&gt;n_ready_packets
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|iso-&gt;prebuffer
op_ne
l_int|0
)paren
(brace
id|iso-&gt;prebuffer
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|iso-&gt;prebuffer
op_le
l_int|0
)paren
(brace
id|iso-&gt;prebuffer
op_assign
l_int|0
suffix:semicolon
id|rv
op_assign
id|do_iso_xmit_start
c_func
(paren
id|iso
comma
id|iso-&gt;start_cycle
)paren
suffix:semicolon
)brace
)brace
id|out
suffix:colon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|iso-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|rv
suffix:semicolon
)brace
DECL|function|hpsb_iso_xmit_sync
r_int
id|hpsb_iso_xmit_sync
c_func
(paren
r_struct
id|hpsb_iso
op_star
id|iso
)paren
(brace
r_if
c_cond
(paren
id|iso-&gt;type
op_ne
id|HPSB_ISO_XMIT
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
id|wait_event_interruptible
c_func
(paren
id|iso-&gt;waitq
comma
id|hpsb_iso_n_ready
c_func
(paren
id|iso
)paren
op_eq
id|iso-&gt;buf_packets
)paren
suffix:semicolon
)brace
DECL|function|hpsb_iso_packet_sent
r_void
id|hpsb_iso_packet_sent
c_func
(paren
r_struct
id|hpsb_iso
op_star
id|iso
comma
r_int
id|cycle
comma
r_int
id|error
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|iso-&gt;lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* predict the cycle of the next packet to be queued */
multiline_comment|/* jump ahead by the number of packets that are already buffered */
id|cycle
op_add_assign
id|iso-&gt;buf_packets
op_minus
id|iso-&gt;n_ready_packets
suffix:semicolon
id|cycle
op_mod_assign
l_int|8000
suffix:semicolon
id|iso-&gt;xmit_cycle
op_assign
id|cycle
suffix:semicolon
id|iso-&gt;n_ready_packets
op_increment
suffix:semicolon
id|iso-&gt;pkt_dma
op_assign
(paren
id|iso-&gt;pkt_dma
op_plus
l_int|1
)paren
op_mod
id|iso-&gt;buf_packets
suffix:semicolon
r_if
c_cond
(paren
id|iso-&gt;n_ready_packets
op_eq
id|iso-&gt;buf_packets
op_logical_or
id|error
op_ne
l_int|0
)paren
(brace
multiline_comment|/* the buffer has run empty! */
id|atomic_inc
c_func
(paren
op_amp
id|iso-&gt;overflows
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|iso-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|hpsb_iso_packet_received
r_void
id|hpsb_iso_packet_received
c_func
(paren
r_struct
id|hpsb_iso
op_star
id|iso
comma
id|u32
id|offset
comma
id|u16
id|len
comma
id|u16
id|cycle
comma
id|u8
id|channel
comma
id|u8
id|tag
comma
id|u8
id|sy
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|iso-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|iso-&gt;n_ready_packets
op_eq
id|iso-&gt;buf_packets
)paren
(brace
multiline_comment|/* overflow! */
id|atomic_inc
c_func
(paren
op_amp
id|iso-&gt;overflows
)paren
suffix:semicolon
)brace
r_else
(brace
r_struct
id|hpsb_iso_packet_info
op_star
id|info
op_assign
op_amp
id|iso-&gt;infos
(braket
id|iso-&gt;pkt_dma
)braket
suffix:semicolon
id|info-&gt;offset
op_assign
id|offset
suffix:semicolon
id|info-&gt;len
op_assign
id|len
suffix:semicolon
id|info-&gt;cycle
op_assign
id|cycle
suffix:semicolon
id|info-&gt;channel
op_assign
id|channel
suffix:semicolon
id|info-&gt;tag
op_assign
id|tag
suffix:semicolon
id|info-&gt;sy
op_assign
id|sy
suffix:semicolon
id|iso-&gt;pkt_dma
op_assign
(paren
id|iso-&gt;pkt_dma
op_plus
l_int|1
)paren
op_mod
id|iso-&gt;buf_packets
suffix:semicolon
id|iso-&gt;n_ready_packets
op_increment
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|iso-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|hpsb_iso_recv_release_packets
r_int
id|hpsb_iso_recv_release_packets
c_func
(paren
r_struct
id|hpsb_iso
op_star
id|iso
comma
r_int
r_int
id|n_packets
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|i
suffix:semicolon
r_int
id|rv
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|iso-&gt;type
op_ne
id|HPSB_ISO_RECV
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|iso-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|n_packets
suffix:semicolon
id|i
op_increment
)paren
(brace
id|rv
op_assign
id|iso-&gt;host-&gt;driver
op_member_access_from_pointer
id|isoctl
c_func
(paren
id|iso
comma
id|RECV_RELEASE
comma
(paren
r_int
r_int
)paren
op_amp
id|iso-&gt;infos
(braket
id|iso-&gt;first_packet
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rv
)paren
(brace
r_break
suffix:semicolon
)brace
id|iso-&gt;first_packet
op_assign
(paren
id|iso-&gt;first_packet
op_plus
l_int|1
)paren
op_mod
id|iso-&gt;buf_packets
suffix:semicolon
id|iso-&gt;n_ready_packets
op_decrement
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|iso-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|rv
suffix:semicolon
)brace
DECL|function|hpsb_iso_wake
r_void
id|hpsb_iso_wake
c_func
(paren
r_struct
id|hpsb_iso
op_star
id|iso
)paren
(brace
id|wake_up_interruptible
c_func
(paren
op_amp
id|iso-&gt;waitq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|iso-&gt;callback
)paren
(brace
id|iso
op_member_access_from_pointer
id|callback
c_func
(paren
id|iso
)paren
suffix:semicolon
)brace
)brace
eof
