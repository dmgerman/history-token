multiline_comment|/*&n; * ohci1394.h - driver for OHCI 1394 boards&n; * Copyright (C)1999,2000 Sebastien Rougeaux &lt;sebastien.rougeaux@anu.edu.au&gt;&n; *                        Gord Peters &lt;GordPeters@smarttech.com&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software Foundation,&n; * Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.&n; */
macro_line|#ifndef _OHCI1394_H
DECL|macro|_OHCI1394_H
mdefine_line|#define _OHCI1394_H
macro_line|#include &quot;ieee1394_types.h&quot;
DECL|macro|IEEE1394_USE_BOTTOM_HALVES
mdefine_line|#define IEEE1394_USE_BOTTOM_HALVES 1
DECL|macro|OHCI1394_DRIVER_NAME
mdefine_line|#define OHCI1394_DRIVER_NAME      &quot;ohci1394&quot;
DECL|macro|USE_DEVICE
mdefine_line|#define USE_DEVICE 0
macro_line|#if USE_DEVICE
macro_line|#ifndef PCI_DEVICE_ID_TI_OHCI1394_LV22
DECL|macro|PCI_DEVICE_ID_TI_OHCI1394_LV22
mdefine_line|#define PCI_DEVICE_ID_TI_OHCI1394_LV22 0x8009
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_TI_OHCI1394_LV23
DECL|macro|PCI_DEVICE_ID_TI_OHCI1394_LV23
mdefine_line|#define PCI_DEVICE_ID_TI_OHCI1394_LV23 0x8019
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_TI_OHCI1394_LV26
DECL|macro|PCI_DEVICE_ID_TI_OHCI1394_LV26
mdefine_line|#define PCI_DEVICE_ID_TI_OHCI1394_LV26 0x8020
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_TI_OHCI1394_PCI4450
DECL|macro|PCI_DEVICE_ID_TI_OHCI1394_PCI4450
mdefine_line|#define PCI_DEVICE_ID_TI_OHCI1394_PCI4450 0x8011
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_VIA_OHCI1394
DECL|macro|PCI_DEVICE_ID_VIA_OHCI1394
mdefine_line|#define PCI_DEVICE_ID_VIA_OHCI1394 0x3044
macro_line|#endif
macro_line|#ifndef PCI_VENDOR_ID_SONY
DECL|macro|PCI_VENDOR_ID_SONY
mdefine_line|#define PCI_VENDOR_ID_SONY 0x104d
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_SONY_CXD3222
DECL|macro|PCI_DEVICE_ID_SONY_CXD3222
mdefine_line|#define PCI_DEVICE_ID_SONY_CXD3222 0x8039
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_NEC_1394
DECL|macro|PCI_DEVICE_ID_NEC_1394
mdefine_line|#define PCI_DEVICE_ID_NEC_1394 0x00cd
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_NEC_UPD72862
DECL|macro|PCI_DEVICE_ID_NEC_UPD72862
mdefine_line|#define PCI_DEVICE_ID_NEC_UPD72862      0x0063
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_NEC_UPD72870
DECL|macro|PCI_DEVICE_ID_NEC_UPD72870
mdefine_line|#define PCI_DEVICE_ID_NEC_UPD72870      0x00cd
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_NEC_UPD72871
DECL|macro|PCI_DEVICE_ID_NEC_UPD72871
mdefine_line|#define PCI_DEVICE_ID_NEC_UPD72871      0x00ce
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_APPLE_UNI_N_FW
DECL|macro|PCI_DEVICE_ID_APPLE_UNI_N_FW
mdefine_line|#define PCI_DEVICE_ID_APPLE_UNI_N_FW&t;0x0018
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_ALI_OHCI1394_M5251
DECL|macro|PCI_DEVICE_ID_ALI_OHCI1394_M5251
mdefine_line|#define PCI_DEVICE_ID_ALI_OHCI1394_M5251 0x5251
macro_line|#endif
macro_line|#ifndef PCI_VENDOR_ID_LUCENT
DECL|macro|PCI_VENDOR_ID_LUCENT
mdefine_line|#define PCI_VENDOR_ID_LUCENT 0x11c1
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_LUCENT_FW323
DECL|macro|PCI_DEVICE_ID_LUCENT_FW323
mdefine_line|#define PCI_DEVICE_ID_LUCENT_FW323 0x5811
macro_line|#endif
macro_line|#endif /* USE_DEVICE */
DECL|macro|MAX_OHCI1394_CARDS
mdefine_line|#define MAX_OHCI1394_CARDS        4
DECL|macro|OHCI1394_MAX_AT_REQ_RETRIES
mdefine_line|#define OHCI1394_MAX_AT_REQ_RETRIES       0x2
DECL|macro|OHCI1394_MAX_AT_RESP_RETRIES
mdefine_line|#define OHCI1394_MAX_AT_RESP_RETRIES      0x2
DECL|macro|OHCI1394_MAX_PHYS_RESP_RETRIES
mdefine_line|#define OHCI1394_MAX_PHYS_RESP_RETRIES    0x8
DECL|macro|OHCI1394_MAX_SELF_ID_ERRORS
mdefine_line|#define OHCI1394_MAX_SELF_ID_ERRORS       16
DECL|macro|AR_REQ_NUM_DESC
mdefine_line|#define AR_REQ_NUM_DESC                   4 /* number of AR req descriptors */
DECL|macro|AR_REQ_BUF_SIZE
mdefine_line|#define AR_REQ_BUF_SIZE           PAGE_SIZE /* size of AR req buffers */
DECL|macro|AR_REQ_SPLIT_BUF_SIZE
mdefine_line|#define AR_REQ_SPLIT_BUF_SIZE     PAGE_SIZE /* split packet buffer */
DECL|macro|AR_RESP_NUM_DESC
mdefine_line|#define AR_RESP_NUM_DESC                  4 /* number of AR resp descriptors */
DECL|macro|AR_RESP_BUF_SIZE
mdefine_line|#define AR_RESP_BUF_SIZE          PAGE_SIZE /* size of AR resp buffers */
DECL|macro|AR_RESP_SPLIT_BUF_SIZE
mdefine_line|#define AR_RESP_SPLIT_BUF_SIZE    PAGE_SIZE /* split packet buffer */
DECL|macro|IR_NUM_DESC
mdefine_line|#define IR_NUM_DESC                      16 /* number of IR descriptors */
DECL|macro|IR_BUF_SIZE
mdefine_line|#define IR_BUF_SIZE               PAGE_SIZE /* 4096 bytes/buffer */
DECL|macro|IR_SPLIT_BUF_SIZE
mdefine_line|#define IR_SPLIT_BUF_SIZE         PAGE_SIZE /* split packet buffer */
DECL|macro|AT_REQ_NUM_DESC
mdefine_line|#define AT_REQ_NUM_DESC                  32 /* number of AT req descriptors */
DECL|macro|AT_RESP_NUM_DESC
mdefine_line|#define AT_RESP_NUM_DESC                 32 /* number of AT resp descriptors */
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
multiline_comment|/* DMA receive context */
DECL|struct|dma_rcv_ctx
r_struct
id|dma_rcv_ctx
(brace
DECL|member|ohci
r_void
op_star
id|ohci
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
id|tq_struct
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
multiline_comment|/* DMA transmit context */
DECL|struct|dma_trm_ctx
r_struct
id|dma_trm_ctx
(brace
DECL|member|ohci
r_void
op_star
id|ohci
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
DECL|member|fifo_first
r_struct
id|hpsb_packet
op_star
id|fifo_first
suffix:semicolon
DECL|member|fifo_last
r_struct
id|hpsb_packet
op_star
id|fifo_last
suffix:semicolon
multiline_comment|/* list of pending packets to be inserted in the AT FIFO */
DECL|member|pending_first
r_struct
id|hpsb_packet
op_star
id|pending_first
suffix:semicolon
DECL|member|pending_last
r_struct
id|hpsb_packet
op_star
id|pending_last
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|task
r_struct
id|tq_struct
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
multiline_comment|/* video device template */
DECL|struct|video_template
r_struct
id|video_template
(brace
DECL|member|irq_handler
r_void
(paren
op_star
id|irq_handler
)paren
(paren
r_int
id|card
comma
id|quadlet_t
id|isoRecvEvent
comma
id|quadlet_t
id|isoXmitEvent
)paren
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
DECL|member|state
id|u32
id|state
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
DECL|member|max_packet_size
r_int
r_int
id|max_packet_size
suffix:semicolon
multiline_comment|/* async receive */
DECL|member|ar_resp_context
r_struct
id|dma_rcv_ctx
op_star
id|ar_resp_context
suffix:semicolon
DECL|member|ar_req_context
r_struct
id|dma_rcv_ctx
op_star
id|ar_req_context
suffix:semicolon
multiline_comment|/* async transmit */
DECL|member|at_resp_context
r_struct
id|dma_trm_ctx
op_star
id|at_resp_context
suffix:semicolon
DECL|member|at_req_context
r_struct
id|dma_trm_ctx
op_star
id|at_req_context
suffix:semicolon
multiline_comment|/* iso receive */
DECL|member|ir_context
r_struct
id|dma_rcv_ctx
op_star
id|ir_context
suffix:semicolon
DECL|member|IR_channel_lock
id|spinlock_t
id|IR_channel_lock
suffix:semicolon
DECL|member|nb_iso_rcv_ctx
r_int
id|nb_iso_rcv_ctx
suffix:semicolon
multiline_comment|/* iso transmit */
DECL|member|nb_iso_xmit_ctx
r_int
id|nb_iso_xmit_ctx
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
DECL|member|self_id_errors
r_int
id|self_id_errors
suffix:semicolon
DECL|member|NumBusResets
r_int
id|NumBusResets
suffix:semicolon
multiline_comment|/* video device */
DECL|member|video_tmpl
r_struct
id|video_template
op_star
id|video_tmpl
suffix:semicolon
)brace
suffix:semicolon
DECL|function|cross_bound
r_inline
r_static
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
r_inline
r_static
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
r_inline
r_static
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
multiline_comment|/* This structure is not properly initialized ... it is taken from&n;   the lynx_csr_rom written by Andreas ... Some fields in the root&n;   directory and the module dependent info needs to be modified&n;   I do not have the proper doc */
DECL|variable|ohci_csr_rom
id|quadlet_t
id|ohci_csr_rom
(braket
)braket
op_assign
(brace
multiline_comment|/* bus info block */
l_int|0x04040000
comma
multiline_comment|/* info/CRC length, CRC */
l_int|0x31333934
comma
multiline_comment|/* 1394 magic number */
l_int|0xf07da002
comma
multiline_comment|/* cyc_clk_acc = 125us, max_rec = 1024 */
l_int|0x00000000
comma
multiline_comment|/* vendor ID, chip ID high (written from card info) */
l_int|0x00000000
comma
multiline_comment|/* chip ID low (written from card info) */
multiline_comment|/* root directory - FIXME */
l_int|0x00090000
comma
multiline_comment|/* CRC length, CRC */
l_int|0x03080028
comma
multiline_comment|/* vendor ID (Texas Instr.) */
l_int|0x81000009
comma
multiline_comment|/* offset to textual ID */
l_int|0x0c000200
comma
multiline_comment|/* node capabilities */
l_int|0x8d00000e
comma
multiline_comment|/* offset to unique ID */
l_int|0xc7000010
comma
multiline_comment|/* offset to module independent info */
l_int|0x04000000
comma
multiline_comment|/* module hardware version */
l_int|0x81000026
comma
multiline_comment|/* offset to textual ID */
l_int|0x09000000
comma
multiline_comment|/* node hardware version */
l_int|0x81000026
comma
multiline_comment|/* offset to textual ID */
multiline_comment|/* module vendor ID textual */
l_int|0x00080000
comma
multiline_comment|/* CRC length, CRC */
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x54455841
comma
multiline_comment|/* &quot;Texas Instruments&quot; */
l_int|0x5320494e
comma
l_int|0x53545255
comma
l_int|0x4d454e54
comma
l_int|0x53000000
comma
multiline_comment|/* node unique ID leaf */
l_int|0x00020000
comma
multiline_comment|/* CRC length, CRC */
l_int|0x08002856
comma
multiline_comment|/* vendor ID, chip ID high */
l_int|0x0000083E
comma
multiline_comment|/* chip ID low */
multiline_comment|/* module dependent info - FIXME */
l_int|0x00060000
comma
multiline_comment|/* CRC length, CRC */
l_int|0xb8000006
comma
multiline_comment|/* ??? offset to module textual ID */
l_int|0x81000004
comma
multiline_comment|/* ??? textual descriptor */
l_int|0x00000000
comma
multiline_comment|/* SRAM size */
l_int|0x00000000
comma
multiline_comment|/* AUXRAM size */
l_int|0x00000000
comma
multiline_comment|/* AUX device */
multiline_comment|/* module textual ID */
l_int|0x00050000
comma
multiline_comment|/* CRC length, CRC */
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x54534231
comma
multiline_comment|/* &quot;TSB12LV22&quot; */
l_int|0x324c5632
comma
l_int|0x32000000
comma
multiline_comment|/* part number */
l_int|0x00060000
comma
multiline_comment|/* CRC length, CRC */
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x39383036
comma
multiline_comment|/* &quot;9806000-0001&quot; */
l_int|0x3030342d
comma
l_int|0x30303431
comma
l_int|0x20000001
comma
multiline_comment|/* module hardware version textual */
l_int|0x00050000
comma
multiline_comment|/* CRC length, CRC */
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x5453424b
comma
multiline_comment|/* &quot;TSBKOHCI403&quot; */
l_int|0x4f484349
comma
l_int|0x34303300
comma
multiline_comment|/* node hardware version textual */
l_int|0x00050000
comma
multiline_comment|/* CRC length, CRC */
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x54534234
comma
multiline_comment|/* &quot;TSB41LV03&quot; */
l_int|0x314c5630
comma
l_int|0x33000000
)brace
suffix:semicolon
multiline_comment|/* 2 KiloBytes of register space */
DECL|macro|OHCI1394_REGISTER_SIZE
mdefine_line|#define OHCI1394_REGISTER_SIZE                0x800       
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
DECL|macro|OHCI1394_AsReqTrContextControlSet
mdefine_line|#define OHCI1394_AsReqTrContextControlSet     0x180
DECL|macro|OHCI1394_AsReqTrContextControlClear
mdefine_line|#define OHCI1394_AsReqTrContextControlClear   0x184
DECL|macro|OHCI1394_AsReqTrCommandPtr
mdefine_line|#define OHCI1394_AsReqTrCommandPtr            0x18C
DECL|macro|OHCI1394_AsRspTrContextControlSet
mdefine_line|#define OHCI1394_AsRspTrContextControlSet     0x1A0
DECL|macro|OHCI1394_AsRspTrContextControlClear
mdefine_line|#define OHCI1394_AsRspTrContextControlClear   0x1A4
DECL|macro|OHCI1394_AsRspTrCommandPtr
mdefine_line|#define OHCI1394_AsRspTrCommandPtr            0x1AC
DECL|macro|OHCI1394_AsReqRcvContextControlSet
mdefine_line|#define OHCI1394_AsReqRcvContextControlSet    0x1C0
DECL|macro|OHCI1394_AsReqRcvContextControlClear
mdefine_line|#define OHCI1394_AsReqRcvContextControlClear  0x1C4
DECL|macro|OHCI1394_AsReqRcvCommandPtr
mdefine_line|#define OHCI1394_AsReqRcvCommandPtr           0x1CC
DECL|macro|OHCI1394_AsRspRcvContextControlSet
mdefine_line|#define OHCI1394_AsRspRcvContextControlSet    0x1E0
DECL|macro|OHCI1394_AsRspRcvContextControlClear
mdefine_line|#define OHCI1394_AsRspRcvContextControlClear  0x1E4
DECL|macro|OHCI1394_AsRspRcvCommandPtr
mdefine_line|#define OHCI1394_AsRspRcvCommandPtr           0x1EC
multiline_comment|/* Isochronous transmit registers */
multiline_comment|/* Add (32 * n) for context n */
DECL|macro|OHCI1394_IsoXmitContextControlSet
mdefine_line|#define OHCI1394_IsoXmitContextControlSet     0x200
DECL|macro|OHCI1394_IsoXmitContextControlClear
mdefine_line|#define OHCI1394_IsoXmitContextControlClear   0x204
DECL|macro|OHCI1394_IsoXmitCommandPtr
mdefine_line|#define OHCI1394_IsoXmitCommandPtr            0x20C
multiline_comment|/* Isochronous receive registers */
multiline_comment|/* Add (32 * n) for context n */
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
DECL|macro|OUTPUT_MORE
mdefine_line|#define OUTPUT_MORE                      0x00000000
DECL|macro|OUTPUT_MORE_IMMEDIATE
mdefine_line|#define OUTPUT_MORE_IMMEDIATE            0x02000000
DECL|macro|OUTPUT_LAST
mdefine_line|#define OUTPUT_LAST                      0x103c0000
DECL|macro|OUTPUT_LAST_IMMEDIATE
mdefine_line|#define OUTPUT_LAST_IMMEDIATE            0x123c0000
DECL|macro|DMA_SPEED_100
mdefine_line|#define DMA_SPEED_100                    0x0
DECL|macro|DMA_SPEED_200
mdefine_line|#define DMA_SPEED_200                    0x1
DECL|macro|DMA_SPEED_400
mdefine_line|#define DMA_SPEED_400                    0x2
DECL|macro|OHCI1394_TCODE_PHY
mdefine_line|#define OHCI1394_TCODE_PHY               0xE
r_void
id|ohci1394_stop_context
c_func
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
r_int
id|ohci1394_register_video
c_func
(paren
r_struct
id|ti_ohci
op_star
id|ohci
comma
r_struct
id|video_template
op_star
id|tmpl
)paren
suffix:semicolon
r_void
id|ohci1394_unregister_video
c_func
(paren
r_struct
id|ti_ohci
op_star
id|ohci
comma
r_struct
id|video_template
op_star
id|tmpl
)paren
suffix:semicolon
macro_line|#endif
eof
