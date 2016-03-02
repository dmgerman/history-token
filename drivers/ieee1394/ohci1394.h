multiline_comment|/*&n; * ohci1394.h - driver for OHCI 1394 boards&n; * Copyright (C)1999,2000 Sebastien Rougeaux &lt;sebastien.rougeaux@anu.edu.au&gt;&n; *                        Gord Peters &lt;GordPeters@smarttech.com&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software Foundation,&n; * Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.&n; */
macro_line|#ifndef _OHCI1394_H
DECL|macro|_OHCI1394_H
mdefine_line|#define _OHCI1394_H
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;ieee1394_types.h&quot;
macro_line|#include &lt;asm/io.h&gt;
DECL|macro|OHCI1394_DRIVER_NAME
mdefine_line|#define OHCI1394_DRIVER_NAME      &quot;ohci1394&quot;
DECL|macro|OHCI1394_MAX_AT_REQ_RETRIES
mdefine_line|#define OHCI1394_MAX_AT_REQ_RETRIES&t;0x2
DECL|macro|OHCI1394_MAX_AT_RESP_RETRIES
mdefine_line|#define OHCI1394_MAX_AT_RESP_RETRIES&t;0x2
DECL|macro|OHCI1394_MAX_PHYS_RESP_RETRIES
mdefine_line|#define OHCI1394_MAX_PHYS_RESP_RETRIES&t;0x8
DECL|macro|OHCI1394_MAX_SELF_ID_ERRORS
mdefine_line|#define OHCI1394_MAX_SELF_ID_ERRORS&t;16
DECL|macro|AR_REQ_NUM_DESC
mdefine_line|#define AR_REQ_NUM_DESC&t;&t;4&t;&t;/* number of AR req descriptors */
DECL|macro|AR_REQ_BUF_SIZE
mdefine_line|#define AR_REQ_BUF_SIZE&t;&t;PAGE_SIZE&t;/* size of AR req buffers */
DECL|macro|AR_REQ_SPLIT_BUF_SIZE
mdefine_line|#define AR_REQ_SPLIT_BUF_SIZE&t;PAGE_SIZE&t;/* split packet buffer */
DECL|macro|AR_RESP_NUM_DESC
mdefine_line|#define AR_RESP_NUM_DESC&t;4&t;&t;/* number of AR resp descriptors */
DECL|macro|AR_RESP_BUF_SIZE
mdefine_line|#define AR_RESP_BUF_SIZE&t;PAGE_SIZE&t;/* size of AR resp buffers */
DECL|macro|AR_RESP_SPLIT_BUF_SIZE
mdefine_line|#define AR_RESP_SPLIT_BUF_SIZE&t;PAGE_SIZE&t;/* split packet buffer */
DECL|macro|IR_NUM_DESC
mdefine_line|#define IR_NUM_DESC&t;&t;16&t;&t;/* number of IR descriptors */
DECL|macro|IR_BUF_SIZE
mdefine_line|#define IR_BUF_SIZE&t;&t;PAGE_SIZE&t;/* 4096 bytes/buffer */
DECL|macro|IR_SPLIT_BUF_SIZE
mdefine_line|#define IR_SPLIT_BUF_SIZE&t;PAGE_SIZE&t;/* split packet buffer */
DECL|macro|IT_NUM_DESC
mdefine_line|#define IT_NUM_DESC&t;&t;16&t;/* number of IT descriptors */
DECL|macro|AT_REQ_NUM_DESC
mdefine_line|#define AT_REQ_NUM_DESC&t;&t;32&t;/* number of AT req descriptors */
DECL|macro|AT_RESP_NUM_DESC
mdefine_line|#define AT_RESP_NUM_DESC&t;32&t;/* number of AT resp descriptors */
DECL|macro|OHCI_LOOP_COUNT
mdefine_line|#define OHCI_LOOP_COUNT&t;&t;100&t;/* Number of loops for reg read waits */
DECL|macro|OHCI_CONFIG_ROM_LEN
mdefine_line|#define OHCI_CONFIG_ROM_LEN&t;1024&t;/* Length of the mapped configrom space */
DECL|macro|OHCI1394_SI_DMA_BUF_SIZE
mdefine_line|#define OHCI1394_SI_DMA_BUF_SIZE&t;8192 /* length of the selfid buffer */
multiline_comment|/* PCI configuration space addresses */
DECL|macro|OHCI1394_PCI_HCI_Control
mdefine_line|#define OHCI1394_PCI_HCI_Control 0x40
DECL|struct|dma_cmd
r_struct
id|dma_cmd
(brace
DECL|member|control
id|u32
id|control
suffix:semicolon
DECL|member|address
id|u32
id|address
suffix:semicolon
DECL|member|branchAddress
id|u32
id|branchAddress
suffix:semicolon
DECL|member|status
id|u32
id|status
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * FIXME:&n; * It is important that a single at_dma_prg does not cross a page boundary&n; * The proper way to do it would be to do the check dynamically as the&n; * programs are inserted into the AT fifo.&n; */
DECL|struct|at_dma_prg
r_struct
id|at_dma_prg
(brace
DECL|member|begin
r_struct
id|dma_cmd
id|begin
suffix:semicolon
DECL|member|data
id|quadlet_t
id|data
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|end
r_struct
id|dma_cmd
id|end
suffix:semicolon
DECL|member|pad
id|quadlet_t
id|pad
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* FIXME: quick hack for memory alignment */
)brace
suffix:semicolon
multiline_comment|/* identify whether a DMA context is asynchronous or isochronous */
DECL|enum|context_type
DECL|enumerator|DMA_CTX_ASYNC_REQ
DECL|enumerator|DMA_CTX_ASYNC_RESP
DECL|enumerator|DMA_CTX_ISO
r_enum
id|context_type
(brace
id|DMA_CTX_ASYNC_REQ
comma
id|DMA_CTX_ASYNC_RESP
comma
id|DMA_CTX_ISO
)brace
suffix:semicolon
multiline_comment|/* DMA receive context */
DECL|struct|dma_rcv_ctx
r_struct
id|dma_rcv_ctx
(brace
DECL|member|ohci
r_struct
id|ti_ohci
op_star
id|ohci
suffix:semicolon
DECL|member|type
r_enum
id|context_type
id|type
suffix:semicolon
DECL|member|ctx
r_int
id|ctx
suffix:semicolon
DECL|member|num_desc
r_int
r_int
id|num_desc
suffix:semicolon
DECL|member|buf_size
r_int
r_int
id|buf_size
suffix:semicolon
DECL|member|split_buf_size
r_int
r_int
id|split_buf_size
suffix:semicolon
multiline_comment|/* dma block descriptors */
DECL|member|prg_cpu
r_struct
id|dma_cmd
op_star
op_star
id|prg_cpu
suffix:semicolon
DECL|member|prg_bus
id|dma_addr_t
op_star
id|prg_bus
suffix:semicolon
DECL|member|prg_pool
r_struct
id|pci_pool
op_star
id|prg_pool
suffix:semicolon
multiline_comment|/* dma buffers */
DECL|member|buf_cpu
id|quadlet_t
op_star
op_star
id|buf_cpu
suffix:semicolon
DECL|member|buf_bus
id|dma_addr_t
op_star
id|buf_bus
suffix:semicolon
DECL|member|buf_ind
r_int
r_int
id|buf_ind
suffix:semicolon
DECL|member|buf_offset
r_int
r_int
id|buf_offset
suffix:semicolon
DECL|member|spb
id|quadlet_t
op_star
id|spb
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|task
r_struct
id|tasklet_struct
id|task
suffix:semicolon
DECL|member|ctrlClear
r_int
id|ctrlClear
suffix:semicolon
DECL|member|ctrlSet
r_int
id|ctrlSet
suffix:semicolon
DECL|member|cmdPtr
r_int
id|cmdPtr
suffix:semicolon
DECL|member|ctxtMatch
r_int
id|ctxtMatch
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* DMA transmit context */
DECL|struct|dma_trm_ctx
r_struct
id|dma_trm_ctx
(brace
DECL|member|ohci
r_struct
id|ti_ohci
op_star
id|ohci
suffix:semicolon
DECL|member|type
r_enum
id|context_type
id|type
suffix:semicolon
DECL|member|ctx
r_int
id|ctx
suffix:semicolon
DECL|member|num_desc
r_int
r_int
id|num_desc
suffix:semicolon
multiline_comment|/* dma block descriptors */
DECL|member|prg_cpu
r_struct
id|at_dma_prg
op_star
op_star
id|prg_cpu
suffix:semicolon
DECL|member|prg_bus
id|dma_addr_t
op_star
id|prg_bus
suffix:semicolon
DECL|member|prg_pool
r_struct
id|pci_pool
op_star
id|prg_pool
suffix:semicolon
DECL|member|prg_ind
r_int
r_int
id|prg_ind
suffix:semicolon
DECL|member|sent_ind
r_int
r_int
id|sent_ind
suffix:semicolon
DECL|member|free_prgs
r_int
id|free_prgs
suffix:semicolon
DECL|member|branchAddrPtr
id|quadlet_t
op_star
id|branchAddrPtr
suffix:semicolon
multiline_comment|/* list of packets inserted in the AT FIFO */
DECL|member|fifo_list
r_struct
id|list_head
id|fifo_list
suffix:semicolon
multiline_comment|/* list of pending packets to be inserted in the AT FIFO */
DECL|member|pending_list
r_struct
id|list_head
id|pending_list
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|task
r_struct
id|tasklet_struct
id|task
suffix:semicolon
DECL|member|ctrlClear
r_int
id|ctrlClear
suffix:semicolon
DECL|member|ctrlSet
r_int
id|ctrlSet
suffix:semicolon
DECL|member|cmdPtr
r_int
id|cmdPtr
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ohci1394_iso_tasklet
r_struct
id|ohci1394_iso_tasklet
(brace
DECL|member|tasklet
r_struct
id|tasklet_struct
id|tasklet
suffix:semicolon
DECL|member|link
r_struct
id|list_head
id|link
suffix:semicolon
DECL|member|context
r_int
id|context
suffix:semicolon
DECL|enumerator|OHCI_ISO_TRANSMIT
DECL|enumerator|OHCI_ISO_RECEIVE
r_enum
(brace
id|OHCI_ISO_TRANSMIT
comma
id|OHCI_ISO_RECEIVE
comma
DECL|enumerator|OHCI_ISO_MULTICHANNEL_RECEIVE
DECL|member|type
id|OHCI_ISO_MULTICHANNEL_RECEIVE
)brace
id|type
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ti_ohci
r_struct
id|ti_ohci
(brace
DECL|member|id
r_int
id|id
suffix:semicolon
multiline_comment|/* sequential card number */
DECL|member|dev
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
r_enum
(brace
DECL|enumerator|OHCI_INIT_ALLOC_HOST
id|OHCI_INIT_ALLOC_HOST
comma
DECL|enumerator|OHCI_INIT_HAVE_MEM_REGION
id|OHCI_INIT_HAVE_MEM_REGION
comma
DECL|enumerator|OHCI_INIT_HAVE_IOMAPPING
id|OHCI_INIT_HAVE_IOMAPPING
comma
DECL|enumerator|OHCI_INIT_HAVE_CONFIG_ROM_BUFFER
id|OHCI_INIT_HAVE_CONFIG_ROM_BUFFER
comma
DECL|enumerator|OHCI_INIT_HAVE_SELFID_BUFFER
id|OHCI_INIT_HAVE_SELFID_BUFFER
comma
DECL|enumerator|OHCI_INIT_HAVE_TXRX_BUFFERS__MAYBE
id|OHCI_INIT_HAVE_TXRX_BUFFERS__MAYBE
comma
DECL|enumerator|OHCI_INIT_HAVE_IRQ
id|OHCI_INIT_HAVE_IRQ
comma
DECL|enumerator|OHCI_INIT_DONE
id|OHCI_INIT_DONE
comma
DECL|member|init_state
)brace
id|init_state
suffix:semicolon
multiline_comment|/* remapped memory spaces */
DECL|member|registers
r_void
op_star
id|registers
suffix:semicolon
multiline_comment|/* dma buffer for self-id packets */
DECL|member|selfid_buf_cpu
id|quadlet_t
op_star
id|selfid_buf_cpu
suffix:semicolon
DECL|member|selfid_buf_bus
id|dma_addr_t
id|selfid_buf_bus
suffix:semicolon
multiline_comment|/* buffer for csr config rom */
DECL|member|csr_config_rom_cpu
id|quadlet_t
op_star
id|csr_config_rom_cpu
suffix:semicolon
DECL|member|csr_config_rom_bus
id|dma_addr_t
id|csr_config_rom_bus
suffix:semicolon
DECL|member|csr_config_rom_length
r_int
id|csr_config_rom_length
suffix:semicolon
DECL|member|max_packet_size
r_int
r_int
id|max_packet_size
suffix:semicolon
multiline_comment|/* async receive */
DECL|member|ar_resp_context
r_struct
id|dma_rcv_ctx
id|ar_resp_context
suffix:semicolon
DECL|member|ar_req_context
r_struct
id|dma_rcv_ctx
id|ar_req_context
suffix:semicolon
multiline_comment|/* async transmit */
DECL|member|at_resp_context
r_struct
id|dma_trm_ctx
id|at_resp_context
suffix:semicolon
DECL|member|at_req_context
r_struct
id|dma_trm_ctx
id|at_req_context
suffix:semicolon
multiline_comment|/* iso receive */
DECL|member|nb_iso_rcv_ctx
r_int
id|nb_iso_rcv_ctx
suffix:semicolon
DECL|member|ir_ctx_usage
r_int
r_int
id|ir_ctx_usage
suffix:semicolon
multiline_comment|/* use test_and_set_bit() for atomicity */
DECL|member|ir_multichannel_used
r_int
r_int
id|ir_multichannel_used
suffix:semicolon
multiline_comment|/* ditto */
DECL|member|IR_channel_lock
id|spinlock_t
id|IR_channel_lock
suffix:semicolon
multiline_comment|/* iso receive (legacy API) */
DECL|member|ir_legacy_channels
id|u64
id|ir_legacy_channels
suffix:semicolon
multiline_comment|/* note: this differs from ISO_channel_usage;&n;&t;&t;&t;&t;   it only accounts for channels listened to&n;&t;&t;&t;&t;   by the legacy API, so that we can know when&n;&t;&t;&t;&t;   it is safe to free the legacy API context */
DECL|member|ir_legacy_context
r_struct
id|dma_rcv_ctx
id|ir_legacy_context
suffix:semicolon
DECL|member|ir_legacy_tasklet
r_struct
id|ohci1394_iso_tasklet
id|ir_legacy_tasklet
suffix:semicolon
multiline_comment|/* iso transmit */
DECL|member|nb_iso_xmit_ctx
r_int
id|nb_iso_xmit_ctx
suffix:semicolon
DECL|member|it_ctx_usage
r_int
r_int
id|it_ctx_usage
suffix:semicolon
multiline_comment|/* use test_and_set_bit() for atomicity */
multiline_comment|/* iso transmit (legacy API) */
DECL|member|it_legacy_context
r_struct
id|dma_trm_ctx
id|it_legacy_context
suffix:semicolon
DECL|member|it_legacy_tasklet
r_struct
id|ohci1394_iso_tasklet
id|it_legacy_tasklet
suffix:semicolon
DECL|member|ISO_channel_usage
id|u64
id|ISO_channel_usage
suffix:semicolon
multiline_comment|/* IEEE-1394 part follows */
DECL|member|host
r_struct
id|hpsb_host
op_star
id|host
suffix:semicolon
DECL|member|phyid
DECL|member|isroot
r_int
id|phyid
comma
id|isroot
suffix:semicolon
DECL|member|phy_reg_lock
id|spinlock_t
id|phy_reg_lock
suffix:semicolon
DECL|member|event_lock
id|spinlock_t
id|event_lock
suffix:semicolon
DECL|member|self_id_errors
r_int
id|self_id_errors
suffix:semicolon
multiline_comment|/* Tasklets for iso receive and transmit, used by video1394,&n;&t; * amdtp and dv1394 */
DECL|member|iso_tasklet_list
r_struct
id|list_head
id|iso_tasklet_list
suffix:semicolon
DECL|member|iso_tasklet_list_lock
id|spinlock_t
id|iso_tasklet_list_lock
suffix:semicolon
multiline_comment|/* Swap the selfid buffer? */
DECL|member|selfid_swap
r_int
r_int
id|selfid_swap
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Some Apple chipset seem to swap incoming headers for us */
DECL|member|no_swap_incoming
r_int
r_int
id|no_swap_incoming
suffix:colon
l_int|1
suffix:semicolon
)brace
suffix:semicolon
DECL|function|cross_bound
r_static
r_inline
r_int
id|cross_bound
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|size
)paren
(brace
r_int
id|cross
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|size
OG
id|PAGE_SIZE
)paren
(brace
id|cross
op_assign
id|size
op_div
id|PAGE_SIZE
suffix:semicolon
id|size
op_sub_assign
id|cross
op_star
id|PAGE_SIZE
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|PAGE_SIZE
op_minus
id|addr
op_mod
id|PAGE_SIZE
)paren
OL
id|size
)paren
id|cross
op_increment
suffix:semicolon
r_return
id|cross
suffix:semicolon
)brace
multiline_comment|/*&n; * Register read and write helper functions.&n; */
DECL|function|reg_write
r_static
r_inline
r_void
id|reg_write
c_func
(paren
r_const
r_struct
id|ti_ohci
op_star
id|ohci
comma
r_int
id|offset
comma
id|u32
id|data
)paren
(brace
id|writel
c_func
(paren
id|data
comma
id|ohci-&gt;registers
op_plus
id|offset
)paren
suffix:semicolon
)brace
DECL|function|reg_read
r_static
r_inline
id|u32
id|reg_read
c_func
(paren
r_const
r_struct
id|ti_ohci
op_star
id|ohci
comma
r_int
id|offset
)paren
(brace
r_return
id|readl
c_func
(paren
id|ohci-&gt;registers
op_plus
id|offset
)paren
suffix:semicolon
)brace
multiline_comment|/* 2 KiloBytes of register space */
DECL|macro|OHCI1394_REGISTER_SIZE
mdefine_line|#define OHCI1394_REGISTER_SIZE                0x800       
multiline_comment|/* Offsets relative to context bases defined below */
DECL|macro|OHCI1394_ContextControlSet
mdefine_line|#define OHCI1394_ContextControlSet            0x000
DECL|macro|OHCI1394_ContextControlClear
mdefine_line|#define OHCI1394_ContextControlClear          0x004
DECL|macro|OHCI1394_ContextCommandPtr
mdefine_line|#define OHCI1394_ContextCommandPtr            0x00C
multiline_comment|/* register map */
DECL|macro|OHCI1394_Version
mdefine_line|#define OHCI1394_Version                      0x000
DECL|macro|OHCI1394_GUID_ROM
mdefine_line|#define OHCI1394_GUID_ROM                     0x004
DECL|macro|OHCI1394_ATRetries
mdefine_line|#define OHCI1394_ATRetries                    0x008
DECL|macro|OHCI1394_CSRData
mdefine_line|#define OHCI1394_CSRData                      0x00C
DECL|macro|OHCI1394_CSRCompareData
mdefine_line|#define OHCI1394_CSRCompareData               0x010
DECL|macro|OHCI1394_CSRControl
mdefine_line|#define OHCI1394_CSRControl                   0x014
DECL|macro|OHCI1394_ConfigROMhdr
mdefine_line|#define OHCI1394_ConfigROMhdr                 0x018
DECL|macro|OHCI1394_BusID
mdefine_line|#define OHCI1394_BusID                        0x01C
DECL|macro|OHCI1394_BusOptions
mdefine_line|#define OHCI1394_BusOptions                   0x020
DECL|macro|OHCI1394_GUIDHi
mdefine_line|#define OHCI1394_GUIDHi                       0x024
DECL|macro|OHCI1394_GUIDLo
mdefine_line|#define OHCI1394_GUIDLo                       0x028
DECL|macro|OHCI1394_ConfigROMmap
mdefine_line|#define OHCI1394_ConfigROMmap                 0x034
DECL|macro|OHCI1394_PostedWriteAddressLo
mdefine_line|#define OHCI1394_PostedWriteAddressLo         0x038
DECL|macro|OHCI1394_PostedWriteAddressHi
mdefine_line|#define OHCI1394_PostedWriteAddressHi         0x03C
DECL|macro|OHCI1394_VendorID
mdefine_line|#define OHCI1394_VendorID                     0x040
DECL|macro|OHCI1394_HCControlSet
mdefine_line|#define OHCI1394_HCControlSet                 0x050
DECL|macro|OHCI1394_HCControlClear
mdefine_line|#define OHCI1394_HCControlClear               0x054
DECL|macro|OHCI1394_SelfIDBuffer
mdefine_line|#define OHCI1394_SelfIDBuffer                 0x064
DECL|macro|OHCI1394_SelfIDCount
mdefine_line|#define OHCI1394_SelfIDCount                  0x068
DECL|macro|OHCI1394_IRMultiChanMaskHiSet
mdefine_line|#define OHCI1394_IRMultiChanMaskHiSet         0x070
DECL|macro|OHCI1394_IRMultiChanMaskHiClear
mdefine_line|#define OHCI1394_IRMultiChanMaskHiClear       0x074
DECL|macro|OHCI1394_IRMultiChanMaskLoSet
mdefine_line|#define OHCI1394_IRMultiChanMaskLoSet         0x078
DECL|macro|OHCI1394_IRMultiChanMaskLoClear
mdefine_line|#define OHCI1394_IRMultiChanMaskLoClear       0x07C
DECL|macro|OHCI1394_IntEventSet
mdefine_line|#define OHCI1394_IntEventSet                  0x080
DECL|macro|OHCI1394_IntEventClear
mdefine_line|#define OHCI1394_IntEventClear                0x084
DECL|macro|OHCI1394_IntMaskSet
mdefine_line|#define OHCI1394_IntMaskSet                   0x088
DECL|macro|OHCI1394_IntMaskClear
mdefine_line|#define OHCI1394_IntMaskClear                 0x08C
DECL|macro|OHCI1394_IsoXmitIntEventSet
mdefine_line|#define OHCI1394_IsoXmitIntEventSet           0x090
DECL|macro|OHCI1394_IsoXmitIntEventClear
mdefine_line|#define OHCI1394_IsoXmitIntEventClear         0x094
DECL|macro|OHCI1394_IsoXmitIntMaskSet
mdefine_line|#define OHCI1394_IsoXmitIntMaskSet            0x098
DECL|macro|OHCI1394_IsoXmitIntMaskClear
mdefine_line|#define OHCI1394_IsoXmitIntMaskClear          0x09C
DECL|macro|OHCI1394_IsoRecvIntEventSet
mdefine_line|#define OHCI1394_IsoRecvIntEventSet           0x0A0
DECL|macro|OHCI1394_IsoRecvIntEventClear
mdefine_line|#define OHCI1394_IsoRecvIntEventClear         0x0A4
DECL|macro|OHCI1394_IsoRecvIntMaskSet
mdefine_line|#define OHCI1394_IsoRecvIntMaskSet            0x0A8
DECL|macro|OHCI1394_IsoRecvIntMaskClear
mdefine_line|#define OHCI1394_IsoRecvIntMaskClear          0x0AC
DECL|macro|OHCI1394_InitialBandwidthAvailable
mdefine_line|#define OHCI1394_InitialBandwidthAvailable    0x0B0
DECL|macro|OHCI1394_InitialChannelsAvailableHi
mdefine_line|#define OHCI1394_InitialChannelsAvailableHi   0x0B4
DECL|macro|OHCI1394_InitialChannelsAvailableLo
mdefine_line|#define OHCI1394_InitialChannelsAvailableLo   0x0B8
DECL|macro|OHCI1394_FairnessControl
mdefine_line|#define OHCI1394_FairnessControl              0x0DC
DECL|macro|OHCI1394_LinkControlSet
mdefine_line|#define OHCI1394_LinkControlSet               0x0E0
DECL|macro|OHCI1394_LinkControlClear
mdefine_line|#define OHCI1394_LinkControlClear             0x0E4
DECL|macro|OHCI1394_NodeID
mdefine_line|#define OHCI1394_NodeID                       0x0E8
DECL|macro|OHCI1394_PhyControl
mdefine_line|#define OHCI1394_PhyControl                   0x0EC
DECL|macro|OHCI1394_IsochronousCycleTimer
mdefine_line|#define OHCI1394_IsochronousCycleTimer        0x0F0
DECL|macro|OHCI1394_AsReqFilterHiSet
mdefine_line|#define OHCI1394_AsReqFilterHiSet             0x100
DECL|macro|OHCI1394_AsReqFilterHiClear
mdefine_line|#define OHCI1394_AsReqFilterHiClear           0x104
DECL|macro|OHCI1394_AsReqFilterLoSet
mdefine_line|#define OHCI1394_AsReqFilterLoSet             0x108
DECL|macro|OHCI1394_AsReqFilterLoClear
mdefine_line|#define OHCI1394_AsReqFilterLoClear           0x10C
DECL|macro|OHCI1394_PhyReqFilterHiSet
mdefine_line|#define OHCI1394_PhyReqFilterHiSet            0x110
DECL|macro|OHCI1394_PhyReqFilterHiClear
mdefine_line|#define OHCI1394_PhyReqFilterHiClear          0x114
DECL|macro|OHCI1394_PhyReqFilterLoSet
mdefine_line|#define OHCI1394_PhyReqFilterLoSet            0x118
DECL|macro|OHCI1394_PhyReqFilterLoClear
mdefine_line|#define OHCI1394_PhyReqFilterLoClear          0x11C
DECL|macro|OHCI1394_PhyUpperBound
mdefine_line|#define OHCI1394_PhyUpperBound                0x120
DECL|macro|OHCI1394_AsReqTrContextBase
mdefine_line|#define OHCI1394_AsReqTrContextBase           0x180
DECL|macro|OHCI1394_AsReqTrContextControlSet
mdefine_line|#define OHCI1394_AsReqTrContextControlSet     0x180
DECL|macro|OHCI1394_AsReqTrContextControlClear
mdefine_line|#define OHCI1394_AsReqTrContextControlClear   0x184
DECL|macro|OHCI1394_AsReqTrCommandPtr
mdefine_line|#define OHCI1394_AsReqTrCommandPtr            0x18C
DECL|macro|OHCI1394_AsRspTrContextBase
mdefine_line|#define OHCI1394_AsRspTrContextBase           0x1A0
DECL|macro|OHCI1394_AsRspTrContextControlSet
mdefine_line|#define OHCI1394_AsRspTrContextControlSet     0x1A0
DECL|macro|OHCI1394_AsRspTrContextControlClear
mdefine_line|#define OHCI1394_AsRspTrContextControlClear   0x1A4
DECL|macro|OHCI1394_AsRspTrCommandPtr
mdefine_line|#define OHCI1394_AsRspTrCommandPtr            0x1AC
DECL|macro|OHCI1394_AsReqRcvContextBase
mdefine_line|#define OHCI1394_AsReqRcvContextBase          0x1C0
DECL|macro|OHCI1394_AsReqRcvContextControlSet
mdefine_line|#define OHCI1394_AsReqRcvContextControlSet    0x1C0
DECL|macro|OHCI1394_AsReqRcvContextControlClear
mdefine_line|#define OHCI1394_AsReqRcvContextControlClear  0x1C4
DECL|macro|OHCI1394_AsReqRcvCommandPtr
mdefine_line|#define OHCI1394_AsReqRcvCommandPtr           0x1CC
DECL|macro|OHCI1394_AsRspRcvContextBase
mdefine_line|#define OHCI1394_AsRspRcvContextBase          0x1E0
DECL|macro|OHCI1394_AsRspRcvContextControlSet
mdefine_line|#define OHCI1394_AsRspRcvContextControlSet    0x1E0
DECL|macro|OHCI1394_AsRspRcvContextControlClear
mdefine_line|#define OHCI1394_AsRspRcvContextControlClear  0x1E4
DECL|macro|OHCI1394_AsRspRcvCommandPtr
mdefine_line|#define OHCI1394_AsRspRcvCommandPtr           0x1EC
multiline_comment|/* Isochronous transmit registers */
multiline_comment|/* Add (16 * n) for context n */
DECL|macro|OHCI1394_IsoXmitContextBase
mdefine_line|#define OHCI1394_IsoXmitContextBase           0x200
DECL|macro|OHCI1394_IsoXmitContextControlSet
mdefine_line|#define OHCI1394_IsoXmitContextControlSet     0x200
DECL|macro|OHCI1394_IsoXmitContextControlClear
mdefine_line|#define OHCI1394_IsoXmitContextControlClear   0x204
DECL|macro|OHCI1394_IsoXmitCommandPtr
mdefine_line|#define OHCI1394_IsoXmitCommandPtr            0x20C
multiline_comment|/* Isochronous receive registers */
multiline_comment|/* Add (32 * n) for context n */
DECL|macro|OHCI1394_IsoRcvContextBase
mdefine_line|#define OHCI1394_IsoRcvContextBase            0x400
DECL|macro|OHCI1394_IsoRcvContextControlSet
mdefine_line|#define OHCI1394_IsoRcvContextControlSet      0x400
DECL|macro|OHCI1394_IsoRcvContextControlClear
mdefine_line|#define OHCI1394_IsoRcvContextControlClear    0x404
DECL|macro|OHCI1394_IsoRcvCommandPtr
mdefine_line|#define OHCI1394_IsoRcvCommandPtr             0x40C
DECL|macro|OHCI1394_IsoRcvContextMatch
mdefine_line|#define OHCI1394_IsoRcvContextMatch           0x410
multiline_comment|/* Interrupts Mask/Events */
DECL|macro|OHCI1394_reqTxComplete
mdefine_line|#define OHCI1394_reqTxComplete           0x00000001
DECL|macro|OHCI1394_respTxComplete
mdefine_line|#define OHCI1394_respTxComplete          0x00000002
DECL|macro|OHCI1394_ARRQ
mdefine_line|#define OHCI1394_ARRQ                    0x00000004
DECL|macro|OHCI1394_ARRS
mdefine_line|#define OHCI1394_ARRS                    0x00000008
DECL|macro|OHCI1394_RQPkt
mdefine_line|#define OHCI1394_RQPkt                   0x00000010
DECL|macro|OHCI1394_RSPkt
mdefine_line|#define OHCI1394_RSPkt                   0x00000020
DECL|macro|OHCI1394_isochTx
mdefine_line|#define OHCI1394_isochTx                 0x00000040
DECL|macro|OHCI1394_isochRx
mdefine_line|#define OHCI1394_isochRx                 0x00000080
DECL|macro|OHCI1394_postedWriteErr
mdefine_line|#define OHCI1394_postedWriteErr          0x00000100
DECL|macro|OHCI1394_lockRespErr
mdefine_line|#define OHCI1394_lockRespErr             0x00000200
DECL|macro|OHCI1394_selfIDComplete
mdefine_line|#define OHCI1394_selfIDComplete          0x00010000
DECL|macro|OHCI1394_busReset
mdefine_line|#define OHCI1394_busReset                0x00020000
DECL|macro|OHCI1394_phy
mdefine_line|#define OHCI1394_phy                     0x00080000
DECL|macro|OHCI1394_cycleSynch
mdefine_line|#define OHCI1394_cycleSynch              0x00100000
DECL|macro|OHCI1394_cycle64Seconds
mdefine_line|#define OHCI1394_cycle64Seconds          0x00200000
DECL|macro|OHCI1394_cycleLost
mdefine_line|#define OHCI1394_cycleLost               0x00400000
DECL|macro|OHCI1394_cycleInconsistent
mdefine_line|#define OHCI1394_cycleInconsistent       0x00800000
DECL|macro|OHCI1394_unrecoverableError
mdefine_line|#define OHCI1394_unrecoverableError      0x01000000
DECL|macro|OHCI1394_cycleTooLong
mdefine_line|#define OHCI1394_cycleTooLong            0x02000000
DECL|macro|OHCI1394_phyRegRcvd
mdefine_line|#define OHCI1394_phyRegRcvd              0x04000000
DECL|macro|OHCI1394_masterIntEnable
mdefine_line|#define OHCI1394_masterIntEnable         0x80000000
multiline_comment|/* DMA Control flags */
DECL|macro|DMA_CTL_OUTPUT_MORE
mdefine_line|#define DMA_CTL_OUTPUT_MORE              0x00000000
DECL|macro|DMA_CTL_OUTPUT_LAST
mdefine_line|#define DMA_CTL_OUTPUT_LAST              0x10000000
DECL|macro|DMA_CTL_INPUT_MORE
mdefine_line|#define DMA_CTL_INPUT_MORE               0x20000000
DECL|macro|DMA_CTL_INPUT_LAST
mdefine_line|#define DMA_CTL_INPUT_LAST               0x30000000
DECL|macro|DMA_CTL_UPDATE
mdefine_line|#define DMA_CTL_UPDATE                   0x08000000
DECL|macro|DMA_CTL_IMMEDIATE
mdefine_line|#define DMA_CTL_IMMEDIATE                0x02000000
DECL|macro|DMA_CTL_IRQ
mdefine_line|#define DMA_CTL_IRQ                      0x00300000
DECL|macro|DMA_CTL_BRANCH
mdefine_line|#define DMA_CTL_BRANCH                   0x000c0000
DECL|macro|DMA_CTL_WAIT
mdefine_line|#define DMA_CTL_WAIT                     0x00030000
multiline_comment|/* OHCI evt_* error types, table 3-2 of the OHCI 1.1 spec. */
DECL|macro|EVT_NO_STATUS
mdefine_line|#define EVT_NO_STATUS&t;&t;0x0&t;/* No event status */
DECL|macro|EVT_RESERVED_A
mdefine_line|#define EVT_RESERVED_A&t;&t;0x1&t;/* Reserved, not used !!! */
DECL|macro|EVT_LONG_PACKET
mdefine_line|#define EVT_LONG_PACKET&t;&t;0x2&t;/* The revc data was longer than the buf */
DECL|macro|EVT_MISSING_ACK
mdefine_line|#define EVT_MISSING_ACK&t;&t;0x3&t;/* A subaction gap was detected before an ack&n;&t;&t;&t;&t;&t;   arrived, or recv&squot;d ack had a parity error */
DECL|macro|EVT_UNDERRUN
mdefine_line|#define EVT_UNDERRUN&t;&t;0x4&t;/* Underrun on corresponding FIFO, packet&n;&t;&t;&t;&t;&t;   truncated */
DECL|macro|EVT_OVERRUN
mdefine_line|#define EVT_OVERRUN&t;&t;0x5&t;/* A recv FIFO overflowed on reception of ISO&n;&t;&t;&t;&t;&t;   packet */
DECL|macro|EVT_DESCRIPTOR_READ
mdefine_line|#define EVT_DESCRIPTOR_READ&t;0x6&t;/* An unrecoverable error occured while host was&n;&t;&t;&t;&t;&t;   reading a descriptor block */
DECL|macro|EVT_DATA_READ
mdefine_line|#define EVT_DATA_READ&t;&t;0x7&t;/* An error occured while host controller was&n;&t;&t;&t;&t;&t;   attempting to read from host memory in the data&n;&t;&t;&t;&t;&t;   stage of descriptor processing */
DECL|macro|EVT_DATA_WRITE
mdefine_line|#define EVT_DATA_WRITE&t;&t;0x8&t;/* An error occured while host controller was&n;&t;&t;&t;&t;&t;   attempting to write either during the data stage&n;&t;&t;&t;&t;&t;   of descriptor processing, or when processing a single&n;&t;&t;&t;&t;&t;   16-bit host memory write */
DECL|macro|EVT_BUS_RESET
mdefine_line|#define EVT_BUS_RESET&t;&t;0x9&t;/* Identifies a PHY packet in the recv buffer as&n;&t;&t;&t;&t;&t;   being a synthesized bus reset packet */
DECL|macro|EVT_TIMEOUT
mdefine_line|#define EVT_TIMEOUT&t;&t;0xa&t;/* Indicates that the asynchronous transmit response&n;&t;&t;&t;&t;&t;   packet expired and was not transmitted, or that an&n;&t;&t;&t;&t;&t;   IT DMA context experienced a skip processing overflow */
DECL|macro|EVT_TCODE_ERR
mdefine_line|#define EVT_TCODE_ERR&t;&t;0xb&t;/* A bad tCode is associated with this packet.&n;&t;&t;&t;&t;&t;   The packet was flushed */
DECL|macro|EVT_RESERVED_B
mdefine_line|#define EVT_RESERVED_B&t;&t;0xc&t;/* Reserved, not used !!! */
DECL|macro|EVT_RESERVED_C
mdefine_line|#define EVT_RESERVED_C&t;&t;0xd&t;/* Reserved, not used !!! */
DECL|macro|EVT_UNKNOWN
mdefine_line|#define EVT_UNKNOWN&t;&t;0xe&t;/* An error condition has occurred that cannot be&n;&t;&t;&t;&t;&t;   represented by any other event codes defined herein. */
DECL|macro|EVT_FLUSHED
mdefine_line|#define EVT_FLUSHED&t;&t;0xf&t;/* Send by the link side of output FIFO when asynchronous&n;&t;&t;&t;&t;&t;   packets are being flushed due to a bus reset. */
DECL|macro|OHCI1394_TCODE_PHY
mdefine_line|#define OHCI1394_TCODE_PHY               0xE
r_void
id|ohci1394_init_iso_tasklet
c_func
(paren
r_struct
id|ohci1394_iso_tasklet
op_star
id|tasklet
comma
r_int
id|type
comma
r_void
(paren
op_star
id|func
)paren
(paren
r_int
r_int
)paren
comma
r_int
r_int
id|data
)paren
suffix:semicolon
r_int
id|ohci1394_register_iso_tasklet
c_func
(paren
r_struct
id|ti_ohci
op_star
id|ohci
comma
r_struct
id|ohci1394_iso_tasklet
op_star
id|tasklet
)paren
suffix:semicolon
r_void
id|ohci1394_unregister_iso_tasklet
c_func
(paren
r_struct
id|ti_ohci
op_star
id|ohci
comma
r_struct
id|ohci1394_iso_tasklet
op_star
id|tasklet
)paren
suffix:semicolon
multiline_comment|/* returns zero if successful, one if DMA context is locked up */
r_int
id|ohci1394_stop_context
(paren
r_struct
id|ti_ohci
op_star
id|ohci
comma
r_int
id|reg
comma
r_char
op_star
id|msg
)paren
suffix:semicolon
r_struct
id|ti_ohci
op_star
id|ohci1394_get_struct
c_func
(paren
r_int
id|card_num
)paren
suffix:semicolon
macro_line|#endif
eof
