multiline_comment|/*&n; *  &n; *  Copyright (C) 2002 Intersil Americas Inc.&n; *  Copyright 2004 Jens Maurer &lt;Jens.Maurer@gmx.net&gt;&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/if_arp.h&gt;
macro_line|#include &quot;prismcompat.h&quot;
macro_line|#include &quot;isl_38xx.h&quot;
macro_line|#include &quot;islpci_mgt.h&quot;
macro_line|#include &quot;isl_oid.h&quot;&t;&t;/* additional types and defs for isl38xx fw */
macro_line|#include &quot;isl_ioctl.h&quot;
macro_line|#include &lt;net/iw_handler.h&gt;
multiline_comment|/******************************************************************************&n;        Global variable definition section&n;******************************************************************************/
DECL|variable|pc_debug
r_int
id|pc_debug
op_assign
id|VERBOSE
suffix:semicolon
id|module_param
c_func
(paren
id|pc_debug
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/******************************************************************************&n;    Driver general functions&n;******************************************************************************/
r_void
DECL|function|display_buffer
id|display_buffer
c_func
(paren
r_char
op_star
id|buffer
comma
r_int
id|length
)paren
(brace
r_if
c_cond
(paren
(paren
id|pc_debug
op_amp
id|SHOW_BUFFER_CONTENTS
)paren
op_eq
l_int|0
)paren
r_return
suffix:semicolon
r_while
c_loop
(paren
id|length
OG
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;[%02x]&quot;
comma
op_star
id|buffer
op_amp
l_int|255
)paren
suffix:semicolon
id|length
op_decrement
suffix:semicolon
id|buffer
op_increment
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*****************************************************************************&n;    Queue handling for management frames&n;******************************************************************************/
multiline_comment|/*&n; * Helper function to create a PIMFOR management frame header.&n; */
r_static
r_void
DECL|function|pimfor_encode_header
id|pimfor_encode_header
c_func
(paren
r_int
id|operation
comma
id|u32
id|oid
comma
id|u32
id|length
comma
id|pimfor_header_t
op_star
id|h
)paren
(brace
id|h-&gt;version
op_assign
id|PIMFOR_VERSION
suffix:semicolon
id|h-&gt;operation
op_assign
id|operation
suffix:semicolon
id|h-&gt;device_id
op_assign
id|PIMFOR_DEV_ID_MHLI_MIB
suffix:semicolon
id|h-&gt;flags
op_assign
l_int|0
suffix:semicolon
id|h-&gt;oid
op_assign
id|cpu_to_be32
c_func
(paren
id|oid
)paren
suffix:semicolon
id|h-&gt;length
op_assign
id|cpu_to_be32
c_func
(paren
id|length
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Helper function to analyze a PIMFOR management frame header.&n; */
r_static
id|pimfor_header_t
op_star
DECL|function|pimfor_decode_header
id|pimfor_decode_header
c_func
(paren
r_void
op_star
id|data
comma
r_int
id|len
)paren
(brace
id|pimfor_header_t
op_star
id|h
op_assign
id|data
suffix:semicolon
r_while
c_loop
(paren
(paren
r_void
op_star
)paren
id|h
OL
id|data
op_plus
id|len
)paren
(brace
r_if
c_cond
(paren
id|h-&gt;flags
op_amp
id|PIMFOR_FLAG_LITTLE_ENDIAN
)paren
(brace
id|le32_to_cpus
c_func
(paren
op_amp
id|h-&gt;oid
)paren
suffix:semicolon
id|le32_to_cpus
c_func
(paren
op_amp
id|h-&gt;length
)paren
suffix:semicolon
)brace
r_else
(brace
id|be32_to_cpus
c_func
(paren
op_amp
id|h-&gt;oid
)paren
suffix:semicolon
id|be32_to_cpus
c_func
(paren
op_amp
id|h-&gt;length
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|h-&gt;oid
op_ne
id|OID_INL_TUNNEL
)paren
r_return
id|h
suffix:semicolon
id|h
op_increment
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * Fill the receive queue for management frames with fresh buffers.&n; */
r_int
DECL|function|islpci_mgmt_rx_fill
id|islpci_mgmt_rx_fill
c_func
(paren
r_struct
id|net_device
op_star
id|ndev
)paren
(brace
id|islpci_private
op_star
id|priv
op_assign
id|netdev_priv
c_func
(paren
id|ndev
)paren
suffix:semicolon
id|isl38xx_control_block
op_star
id|cb
op_assign
multiline_comment|/* volatile not needed */
(paren
id|isl38xx_control_block
op_star
)paren
id|priv-&gt;control_block
suffix:semicolon
id|u32
id|curr
op_assign
id|le32_to_cpu
c_func
(paren
id|cb-&gt;driver_curr_frag
(braket
id|ISL38XX_CB_RX_MGMTQ
)braket
)paren
suffix:semicolon
macro_line|#if VERBOSE &gt; SHOW_ERROR_MESSAGES
id|DEBUG
c_func
(paren
id|SHOW_FUNCTION_CALLS
comma
l_string|&quot;islpci_mgmt_rx_fill &bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
r_while
c_loop
(paren
id|curr
op_minus
id|priv-&gt;index_mgmt_rx
OL
id|ISL38XX_CB_MGMT_QSIZE
)paren
(brace
id|u32
id|index
op_assign
id|curr
op_mod
id|ISL38XX_CB_MGMT_QSIZE
suffix:semicolon
r_struct
id|islpci_membuf
op_star
id|buf
op_assign
op_amp
id|priv-&gt;mgmt_rx
(braket
id|index
)braket
suffix:semicolon
id|isl38xx_fragment
op_star
id|frag
op_assign
op_amp
id|cb-&gt;rx_data_mgmt
(braket
id|index
)braket
suffix:semicolon
r_if
c_cond
(paren
id|buf-&gt;mem
op_eq
l_int|NULL
)paren
(brace
id|buf-&gt;mem
op_assign
id|kmalloc
c_func
(paren
id|MGMT_FRAME_SIZE
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buf-&gt;mem
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Error allocating management frame.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|buf-&gt;size
op_assign
id|MGMT_FRAME_SIZE
suffix:semicolon
)brace
r_if
c_cond
(paren
id|buf-&gt;pci_addr
op_eq
l_int|0
)paren
(brace
id|buf-&gt;pci_addr
op_assign
id|pci_map_single
c_func
(paren
id|priv-&gt;pdev
comma
id|buf-&gt;mem
comma
id|MGMT_FRAME_SIZE
comma
id|PCI_DMA_FROMDEVICE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buf-&gt;pci_addr
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Failed to make memory DMA&squot;able&bslash;n.&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
)brace
multiline_comment|/* be safe: always reset control block information */
id|frag-&gt;size
op_assign
id|cpu_to_le16
c_func
(paren
id|MGMT_FRAME_SIZE
)paren
suffix:semicolon
id|frag-&gt;flags
op_assign
l_int|0
suffix:semicolon
id|frag-&gt;address
op_assign
id|cpu_to_le32
c_func
(paren
id|buf-&gt;pci_addr
)paren
suffix:semicolon
id|curr
op_increment
suffix:semicolon
multiline_comment|/* The fragment address in the control block must have&n;&t;&t; * been written before announcing the frame buffer to&n;&t;&t; * device */
id|wmb
c_func
(paren
)paren
suffix:semicolon
id|cb-&gt;driver_curr_frag
(braket
id|ISL38XX_CB_RX_MGMTQ
)braket
op_assign
id|cpu_to_le32
c_func
(paren
id|curr
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Create and transmit a management frame using &quot;operation&quot; and &quot;oid&quot;,&n; * with arguments data/length.&n; * We either return an error and free the frame, or we return 0 and&n; * islpci_mgt_cleanup_transmit() frees the frame in the tx-done&n; * interrupt.&n; */
r_static
r_int
DECL|function|islpci_mgt_transmit
id|islpci_mgt_transmit
c_func
(paren
r_struct
id|net_device
op_star
id|ndev
comma
r_int
id|operation
comma
r_int
r_int
id|oid
comma
r_void
op_star
id|data
comma
r_int
id|length
)paren
(brace
id|islpci_private
op_star
id|priv
op_assign
id|netdev_priv
c_func
(paren
id|ndev
)paren
suffix:semicolon
id|isl38xx_control_block
op_star
id|cb
op_assign
(paren
id|isl38xx_control_block
op_star
)paren
id|priv-&gt;control_block
suffix:semicolon
r_void
op_star
id|p
suffix:semicolon
r_int
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|isl38xx_fragment
op_star
id|frag
suffix:semicolon
r_struct
id|islpci_membuf
id|buf
suffix:semicolon
id|u32
id|curr_frag
suffix:semicolon
r_int
id|index
suffix:semicolon
r_int
id|frag_len
op_assign
id|length
op_plus
id|PIMFOR_HEADER_SIZE
suffix:semicolon
macro_line|#if VERBOSE &gt; SHOW_ERROR_MESSAGES
id|DEBUG
c_func
(paren
id|SHOW_FUNCTION_CALLS
comma
l_string|&quot;islpci_mgt_transmit&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|frag_len
OG
id|MGMT_FRAME_SIZE
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s: mgmt frame too large %d&bslash;n&quot;
comma
id|ndev-&gt;name
comma
id|frag_len
)paren
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|p
op_assign
id|buf.mem
op_assign
id|kmalloc
c_func
(paren
id|frag_len
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buf.mem
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s: cannot allocate mgmt frame&bslash;n&quot;
comma
id|ndev-&gt;name
)paren
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
id|buf.size
op_assign
id|frag_len
suffix:semicolon
multiline_comment|/* create the header directly in the fragment data area */
id|pimfor_encode_header
c_func
(paren
id|operation
comma
id|oid
comma
id|length
comma
(paren
id|pimfor_header_t
op_star
)paren
id|p
)paren
suffix:semicolon
id|p
op_add_assign
id|PIMFOR_HEADER_SIZE
suffix:semicolon
r_if
c_cond
(paren
id|data
)paren
id|memcpy
c_func
(paren
id|p
comma
id|data
comma
id|length
)paren
suffix:semicolon
r_else
id|memset
c_func
(paren
id|p
comma
l_int|0
comma
id|length
)paren
suffix:semicolon
macro_line|#if VERBOSE &gt; SHOW_ERROR_MESSAGES
(brace
id|pimfor_header_t
op_star
id|h
op_assign
id|buf.mem
suffix:semicolon
id|DEBUG
c_func
(paren
id|SHOW_PIMFOR_FRAMES
comma
l_string|&quot;PIMFOR: op %i, oid 0x%08lx, device %i, flags 0x%x length 0x%x &bslash;n&quot;
comma
id|h-&gt;operation
comma
id|oid
comma
id|h-&gt;device_id
comma
id|h-&gt;flags
comma
id|length
)paren
suffix:semicolon
multiline_comment|/* display the buffer contents for debugging */
id|display_buffer
c_func
(paren
(paren
r_char
op_star
)paren
id|h
comma
r_sizeof
(paren
id|pimfor_header_t
)paren
)paren
suffix:semicolon
id|display_buffer
c_func
(paren
id|p
comma
id|length
)paren
suffix:semicolon
)brace
macro_line|#endif
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|buf.pci_addr
op_assign
id|pci_map_single
c_func
(paren
id|priv-&gt;pdev
comma
id|buf.mem
comma
id|frag_len
comma
id|PCI_DMA_TODEVICE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buf.pci_addr
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: cannot map PCI memory for mgmt&bslash;n&quot;
comma
id|ndev-&gt;name
)paren
suffix:semicolon
r_goto
id|error_free
suffix:semicolon
)brace
multiline_comment|/* Protect the control block modifications against interrupts. */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|priv-&gt;slock
comma
id|flags
)paren
suffix:semicolon
id|curr_frag
op_assign
id|le32_to_cpu
c_func
(paren
id|cb-&gt;driver_curr_frag
(braket
id|ISL38XX_CB_TX_MGMTQ
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|curr_frag
op_minus
id|priv-&gt;index_mgmt_tx
op_ge
id|ISL38XX_CB_MGMT_QSIZE
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: mgmt tx queue is still full&bslash;n&quot;
comma
id|ndev-&gt;name
)paren
suffix:semicolon
r_goto
id|error_unlock
suffix:semicolon
)brace
multiline_comment|/* commit the frame to the tx device queue */
id|index
op_assign
id|curr_frag
op_mod
id|ISL38XX_CB_MGMT_QSIZE
suffix:semicolon
id|priv-&gt;mgmt_tx
(braket
id|index
)braket
op_assign
id|buf
suffix:semicolon
id|frag
op_assign
op_amp
id|cb-&gt;tx_data_mgmt
(braket
id|index
)braket
suffix:semicolon
id|frag-&gt;size
op_assign
id|cpu_to_le16
c_func
(paren
id|frag_len
)paren
suffix:semicolon
id|frag-&gt;flags
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* for any other than the last fragment, set to 1 */
id|frag-&gt;address
op_assign
id|cpu_to_le32
c_func
(paren
id|buf.pci_addr
)paren
suffix:semicolon
multiline_comment|/* The fragment address in the control block must have&n;&t; * been written before announcing the frame buffer to&n;&t; * device */
id|wmb
c_func
(paren
)paren
suffix:semicolon
id|cb-&gt;driver_curr_frag
(braket
id|ISL38XX_CB_TX_MGMTQ
)braket
op_assign
id|cpu_to_le32
c_func
(paren
id|curr_frag
op_plus
l_int|1
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|priv-&gt;slock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* trigger the device */
id|islpci_trigger
c_func
(paren
id|priv
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|error_unlock
suffix:colon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|priv-&gt;slock
comma
id|flags
)paren
suffix:semicolon
id|error_free
suffix:colon
id|kfree
c_func
(paren
id|buf.mem
)paren
suffix:semicolon
id|error
suffix:colon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*&n; * Receive a management frame from the device.&n; * This can be an arbitrary number of traps, and at most one response&n; * frame for a previous request sent via islpci_mgt_transmit().&n; */
r_int
DECL|function|islpci_mgt_receive
id|islpci_mgt_receive
c_func
(paren
r_struct
id|net_device
op_star
id|ndev
)paren
(brace
id|islpci_private
op_star
id|priv
op_assign
id|netdev_priv
c_func
(paren
id|ndev
)paren
suffix:semicolon
id|isl38xx_control_block
op_star
id|cb
op_assign
(paren
id|isl38xx_control_block
op_star
)paren
id|priv-&gt;control_block
suffix:semicolon
id|u32
id|curr_frag
suffix:semicolon
macro_line|#if VERBOSE &gt; SHOW_ERROR_MESSAGES
id|DEBUG
c_func
(paren
id|SHOW_FUNCTION_CALLS
comma
l_string|&quot;islpci_mgt_receive &bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Only once per interrupt, determine fragment range to&n;&t; * process.  This avoids an endless loop (i.e. lockup) if&n;&t; * frames come in faster than we can process them. */
id|curr_frag
op_assign
id|le32_to_cpu
c_func
(paren
id|cb-&gt;device_curr_frag
(braket
id|ISL38XX_CB_RX_MGMTQ
)braket
)paren
suffix:semicolon
id|barrier
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|priv-&gt;index_mgmt_rx
OL
id|curr_frag
suffix:semicolon
id|priv-&gt;index_mgmt_rx
op_increment
)paren
(brace
id|pimfor_header_t
op_star
id|header
suffix:semicolon
id|u32
id|index
op_assign
id|priv-&gt;index_mgmt_rx
op_mod
id|ISL38XX_CB_MGMT_QSIZE
suffix:semicolon
r_struct
id|islpci_membuf
op_star
id|buf
op_assign
op_amp
id|priv-&gt;mgmt_rx
(braket
id|index
)braket
suffix:semicolon
id|u16
id|frag_len
suffix:semicolon
r_int
id|size
suffix:semicolon
r_struct
id|islpci_mgmtframe
op_star
id|frame
suffix:semicolon
multiline_comment|/* I have no idea (and no documentation) if flags != 0&n;&t;&t; * is possible.  Drop the frame, reuse the buffer. */
r_if
c_cond
(paren
id|le16_to_cpu
c_func
(paren
id|cb-&gt;rx_data_mgmt
(braket
id|index
)braket
dot
id|flags
)paren
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: unknown flags 0x%04x&bslash;n&quot;
comma
id|ndev-&gt;name
comma
id|le16_to_cpu
c_func
(paren
id|cb-&gt;rx_data_mgmt
(braket
id|index
)braket
dot
id|flags
)paren
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/* The device only returns the size of the header(s) here. */
id|frag_len
op_assign
id|le16_to_cpu
c_func
(paren
id|cb-&gt;rx_data_mgmt
(braket
id|index
)braket
dot
id|size
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * We appear to have no way to tell the device the&n;&t;&t; * size of a receive buffer.  Thus, if this check&n;&t;&t; * triggers, we likely have kernel heap corruption. */
r_if
c_cond
(paren
id|frag_len
OG
id|MGMT_FRAME_SIZE
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: Bogus packet size of %d (%#x).&bslash;n&quot;
comma
id|ndev-&gt;name
comma
id|frag_len
comma
id|frag_len
)paren
suffix:semicolon
id|frag_len
op_assign
id|MGMT_FRAME_SIZE
suffix:semicolon
)brace
multiline_comment|/* Ensure the results of device DMA are visible to the CPU. */
id|pci_dma_sync_single_for_cpu
c_func
(paren
id|priv-&gt;pdev
comma
id|buf-&gt;pci_addr
comma
id|buf-&gt;size
comma
id|PCI_DMA_FROMDEVICE
)paren
suffix:semicolon
multiline_comment|/* Perform endianess conversion for PIMFOR header in-place. */
id|header
op_assign
id|pimfor_decode_header
c_func
(paren
id|buf-&gt;mem
comma
id|frag_len
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|header
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: no PIMFOR header found&bslash;n&quot;
comma
id|ndev-&gt;name
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/* The device ID from the PIMFOR packet received from&n;&t;&t; * the MVC is always 0.  We forward a sensible device_id.&n;&t;&t; * Not that anyone upstream would care... */
id|header-&gt;device_id
op_assign
id|priv-&gt;ndev-&gt;ifindex
suffix:semicolon
macro_line|#if VERBOSE &gt; SHOW_ERROR_MESSAGES
id|DEBUG
c_func
(paren
id|SHOW_PIMFOR_FRAMES
comma
l_string|&quot;PIMFOR: op %i, oid 0x%08x, device %i, flags 0x%x length 0x%x &bslash;n&quot;
comma
id|header-&gt;operation
comma
id|header-&gt;oid
comma
id|header-&gt;device_id
comma
id|header-&gt;flags
comma
id|header-&gt;length
)paren
suffix:semicolon
multiline_comment|/* display the buffer contents for debugging */
id|display_buffer
c_func
(paren
(paren
r_char
op_star
)paren
id|header
comma
id|PIMFOR_HEADER_SIZE
)paren
suffix:semicolon
id|display_buffer
c_func
(paren
(paren
r_char
op_star
)paren
id|header
op_plus
id|PIMFOR_HEADER_SIZE
comma
id|header-&gt;length
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* nobody sends these */
r_if
c_cond
(paren
id|header-&gt;flags
op_amp
id|PIMFOR_FLAG_APPLIC_ORIGIN
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s: errant PIMFOR application frame&bslash;n&quot;
comma
id|ndev-&gt;name
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/* Determine frame size, skipping OID_INL_TUNNEL headers. */
id|size
op_assign
id|PIMFOR_HEADER_SIZE
op_plus
id|header-&gt;length
suffix:semicolon
id|frame
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|islpci_mgmtframe
)paren
op_plus
id|size
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|frame
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: Out of memory, cannot handle oid 0x%08x&bslash;n&quot;
comma
id|ndev-&gt;name
comma
id|header-&gt;oid
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|frame-&gt;ndev
op_assign
id|ndev
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|frame-&gt;buf
comma
id|header
comma
id|size
)paren
suffix:semicolon
id|frame-&gt;header
op_assign
(paren
id|pimfor_header_t
op_star
)paren
id|frame-&gt;buf
suffix:semicolon
id|frame-&gt;data
op_assign
id|frame-&gt;buf
op_plus
id|PIMFOR_HEADER_SIZE
suffix:semicolon
macro_line|#if VERBOSE &gt; SHOW_ERROR_MESSAGES
id|DEBUG
c_func
(paren
id|SHOW_PIMFOR_FRAMES
comma
l_string|&quot;frame: header: %p, data: %p, size: %d&bslash;n&quot;
comma
id|frame-&gt;header
comma
id|frame-&gt;data
comma
id|size
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|header-&gt;operation
op_eq
id|PIMFOR_OP_TRAP
)paren
(brace
macro_line|#if VERBOSE &gt; SHOW_ERROR_MESSAGES
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;TRAP: oid 0x%x, device %i, flags 0x%x length %i&bslash;n&quot;
comma
id|header-&gt;oid
comma
id|header-&gt;device_id
comma
id|header-&gt;flags
comma
id|header-&gt;length
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Create work to handle trap out of interrupt&n;&t;&t;&t; * context. */
id|INIT_WORK
c_func
(paren
op_amp
id|frame-&gt;ws
comma
id|prism54_process_trap
comma
id|frame
)paren
suffix:semicolon
id|schedule_work
c_func
(paren
op_amp
id|frame-&gt;ws
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Signal the one waiting process that a response&n;&t;&t;&t; * has been received. */
r_if
c_cond
(paren
(paren
id|frame
op_assign
id|xchg
c_func
(paren
op_amp
id|priv-&gt;mgmt_received
comma
id|frame
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: mgmt response not collected&bslash;n&quot;
comma
id|ndev-&gt;name
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|frame
)paren
suffix:semicolon
)brace
macro_line|#if VERBOSE &gt; SHOW_ERROR_MESSAGES
id|DEBUG
c_func
(paren
id|SHOW_TRACING
comma
l_string|&quot;Wake up Mgmt Queue&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|wake_up
c_func
(paren
op_amp
id|priv-&gt;mgmt_wqueue
)paren
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Cleanup the transmit queue by freeing all frames handled by the device.&n; */
r_void
DECL|function|islpci_mgt_cleanup_transmit
id|islpci_mgt_cleanup_transmit
c_func
(paren
r_struct
id|net_device
op_star
id|ndev
)paren
(brace
id|islpci_private
op_star
id|priv
op_assign
id|netdev_priv
c_func
(paren
id|ndev
)paren
suffix:semicolon
id|isl38xx_control_block
op_star
id|cb
op_assign
multiline_comment|/* volatile not needed */
(paren
id|isl38xx_control_block
op_star
)paren
id|priv-&gt;control_block
suffix:semicolon
id|u32
id|curr_frag
suffix:semicolon
macro_line|#if VERBOSE &gt; SHOW_ERROR_MESSAGES
id|DEBUG
c_func
(paren
id|SHOW_FUNCTION_CALLS
comma
l_string|&quot;islpci_mgt_cleanup_transmit&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Only once per cleanup, determine fragment range to&n;&t; * process.  This avoids an endless loop (i.e. lockup) if&n;&t; * the device became confused, incrementing device_curr_frag&n;&t; * rapidly. */
id|curr_frag
op_assign
id|le32_to_cpu
c_func
(paren
id|cb-&gt;device_curr_frag
(braket
id|ISL38XX_CB_TX_MGMTQ
)braket
)paren
suffix:semicolon
id|barrier
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|priv-&gt;index_mgmt_tx
OL
id|curr_frag
suffix:semicolon
id|priv-&gt;index_mgmt_tx
op_increment
)paren
(brace
r_int
id|index
op_assign
id|priv-&gt;index_mgmt_tx
op_mod
id|ISL38XX_CB_MGMT_QSIZE
suffix:semicolon
r_struct
id|islpci_membuf
op_star
id|buf
op_assign
op_amp
id|priv-&gt;mgmt_tx
(braket
id|index
)braket
suffix:semicolon
id|pci_unmap_single
c_func
(paren
id|priv-&gt;pdev
comma
id|buf-&gt;pci_addr
comma
id|buf-&gt;size
comma
id|PCI_DMA_TODEVICE
)paren
suffix:semicolon
id|buf-&gt;pci_addr
op_assign
l_int|0
suffix:semicolon
id|kfree
c_func
(paren
id|buf-&gt;mem
)paren
suffix:semicolon
id|buf-&gt;mem
op_assign
l_int|NULL
suffix:semicolon
id|buf-&gt;size
op_assign
l_int|0
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Perform one request-response transaction to the device.&n; */
r_int
DECL|function|islpci_mgt_transaction
id|islpci_mgt_transaction
c_func
(paren
r_struct
id|net_device
op_star
id|ndev
comma
r_int
id|operation
comma
r_int
r_int
id|oid
comma
r_void
op_star
id|senddata
comma
r_int
id|sendlen
comma
r_struct
id|islpci_mgmtframe
op_star
op_star
id|recvframe
)paren
(brace
id|islpci_private
op_star
id|priv
op_assign
id|netdev_priv
c_func
(paren
id|ndev
)paren
suffix:semicolon
r_const
r_int
id|wait_cycle_jiffies
op_assign
(paren
id|ISL38XX_WAIT_CYCLE
op_star
l_int|10
op_star
id|HZ
)paren
op_div
l_int|1000
suffix:semicolon
r_int
id|timeout_left
op_assign
id|ISL38XX_MAX_WAIT_CYCLES
op_star
id|wait_cycle_jiffies
suffix:semicolon
r_int
id|err
suffix:semicolon
id|DEFINE_WAIT
c_func
(paren
id|wait
)paren
suffix:semicolon
op_star
id|recvframe
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|down_interruptible
c_func
(paren
op_amp
id|priv-&gt;mgmt_sem
)paren
)paren
r_return
op_minus
id|ERESTARTSYS
suffix:semicolon
id|prepare_to_wait
c_func
(paren
op_amp
id|priv-&gt;mgmt_wqueue
comma
op_amp
id|wait
comma
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
id|err
op_assign
id|islpci_mgt_transmit
c_func
(paren
id|ndev
comma
id|operation
comma
id|oid
comma
id|senddata
comma
id|sendlen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|out
suffix:semicolon
id|err
op_assign
op_minus
id|ETIMEDOUT
suffix:semicolon
r_while
c_loop
(paren
id|timeout_left
OG
l_int|0
)paren
(brace
r_int
id|timeleft
suffix:semicolon
r_struct
id|islpci_mgmtframe
op_star
id|frame
suffix:semicolon
id|timeleft
op_assign
id|schedule_timeout
c_func
(paren
id|wait_cycle_jiffies
)paren
suffix:semicolon
id|frame
op_assign
id|xchg
c_func
(paren
op_amp
id|priv-&gt;mgmt_received
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|frame
)paren
(brace
r_if
c_cond
(paren
id|frame-&gt;header-&gt;oid
op_eq
id|oid
)paren
(brace
op_star
id|recvframe
op_assign
id|frame
suffix:semicolon
id|err
op_assign
l_int|0
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s: expecting oid 0x%x, received 0x%x.&bslash;n&quot;
comma
id|ndev-&gt;name
comma
(paren
r_int
r_int
)paren
id|oid
comma
id|frame-&gt;header-&gt;oid
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|frame
)paren
suffix:semicolon
id|frame
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|timeleft
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s: timeout waiting for mgmt response %lu, &quot;
l_string|&quot;triggering device&bslash;n&quot;
comma
id|ndev-&gt;name
comma
id|timeout_left
)paren
suffix:semicolon
id|islpci_trigger
c_func
(paren
id|priv
)paren
suffix:semicolon
)brace
id|timeout_left
op_add_assign
id|timeleft
op_minus
id|wait_cycle_jiffies
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: timeout waiting for mgmt response&bslash;n&quot;
comma
id|ndev-&gt;name
)paren
suffix:semicolon
multiline_comment|/* TODO: we should reset the device here */
id|out
suffix:colon
id|finish_wait
c_func
(paren
op_amp
id|priv-&gt;mgmt_wqueue
comma
op_amp
id|wait
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|priv-&gt;mgmt_sem
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
eof
