multiline_comment|/*&n;  Madge Ambassador ATM Adapter driver.&n;  Copyright (C) 1995-1999  Madge Networks Ltd.&n;&n;  This program is free software; you can redistribute it and/or modify&n;  it under the terms of the GNU General Public License as published by&n;  the Free Software Foundation; either version 2 of the License, or&n;  (at your option) any later version.&n;&n;  This program is distributed in the hope that it will be useful,&n;  but WITHOUT ANY WARRANTY; without even the implied warranty of&n;  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;  GNU General Public License for more details.&n;&n;  You should have received a copy of the GNU General Public License&n;  along with this program; if not, write to the Free Software&n;  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n;&n;  The GNU GPL is contained in /usr/doc/copyright/GPL on a Debian&n;  system and in the file COPYING in the Linux kernel source.&n;*/
macro_line|#ifndef AMBASSADOR_H
DECL|macro|AMBASSADOR_H
mdefine_line|#define AMBASSADOR_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_ATM_AMBASSADOR_DEBUG
DECL|macro|DEBUG_AMBASSADOR
mdefine_line|#define DEBUG_AMBASSADOR
macro_line|#endif
DECL|macro|DEV_LABEL
mdefine_line|#define DEV_LABEL                          &quot;amb&quot;
macro_line|#ifndef PCI_VENDOR_ID_MADGE
DECL|macro|PCI_VENDOR_ID_MADGE
mdefine_line|#define PCI_VENDOR_ID_MADGE                0x10B6
macro_line|#endif
macro_line|#ifndef PCI_VENDOR_ID_MADGE_AMBASSADOR
DECL|macro|PCI_DEVICE_ID_MADGE_AMBASSADOR
mdefine_line|#define PCI_DEVICE_ID_MADGE_AMBASSADOR     0x1001
macro_line|#endif
macro_line|#ifndef PCI_VENDOR_ID_MADGE_AMBASSADOR_BAD
DECL|macro|PCI_DEVICE_ID_MADGE_AMBASSADOR_BAD
mdefine_line|#define PCI_DEVICE_ID_MADGE_AMBASSADOR_BAD 0x1002
macro_line|#endif
singleline_comment|// diagnostic output
DECL|macro|PRINTK
mdefine_line|#define PRINTK(severity,format,args...) &bslash;&n;  printk(severity DEV_LABEL &quot;: &quot; format &quot;&bslash;n&quot; , ## args)
macro_line|#ifdef DEBUG_AMBASSADOR
DECL|macro|DBG_ERR
mdefine_line|#define DBG_ERR  0x0001
DECL|macro|DBG_WARN
mdefine_line|#define DBG_WARN 0x0002
DECL|macro|DBG_INFO
mdefine_line|#define DBG_INFO 0x0004
DECL|macro|DBG_INIT
mdefine_line|#define DBG_INIT 0x0008
DECL|macro|DBG_LOAD
mdefine_line|#define DBG_LOAD 0x0010
DECL|macro|DBG_VCC
mdefine_line|#define DBG_VCC  0x0020
DECL|macro|DBG_QOS
mdefine_line|#define DBG_QOS  0x0040
DECL|macro|DBG_CMD
mdefine_line|#define DBG_CMD  0x0080
DECL|macro|DBG_TX
mdefine_line|#define DBG_TX   0x0100
DECL|macro|DBG_RX
mdefine_line|#define DBG_RX   0x0200
DECL|macro|DBG_SKB
mdefine_line|#define DBG_SKB  0x0400
DECL|macro|DBG_POOL
mdefine_line|#define DBG_POOL 0x0800
DECL|macro|DBG_IRQ
mdefine_line|#define DBG_IRQ  0x1000
DECL|macro|DBG_FLOW
mdefine_line|#define DBG_FLOW 0x2000
DECL|macro|DBG_REGS
mdefine_line|#define DBG_REGS 0x4000
DECL|macro|DBG_DATA
mdefine_line|#define DBG_DATA 0x8000
DECL|macro|DBG_MASK
mdefine_line|#define DBG_MASK 0xffff
multiline_comment|/* the ## prevents the annoying double expansion of the macro arguments */
multiline_comment|/* KERN_INFO is used since KERN_DEBUG often does not make it to the console */
DECL|macro|PRINTDB
mdefine_line|#define PRINTDB(bits,format,args...) &bslash;&n;  ( (debug &amp; (bits)) ? printk (KERN_INFO DEV_LABEL &quot;: &quot; format , ## args) : 1 )
DECL|macro|PRINTDM
mdefine_line|#define PRINTDM(bits,format,args...) &bslash;&n;  ( (debug &amp; (bits)) ? printk (format , ## args) : 1 )
DECL|macro|PRINTDE
mdefine_line|#define PRINTDE(bits,format,args...) &bslash;&n;  ( (debug &amp; (bits)) ? printk (format &quot;&bslash;n&quot; , ## args) : 1 )
DECL|macro|PRINTD
mdefine_line|#define PRINTD(bits,format,args...) &bslash;&n;  ( (debug &amp; (bits)) ? printk (KERN_INFO DEV_LABEL &quot;: &quot; format &quot;&bslash;n&quot; , ## args) : 1 )
macro_line|#else
DECL|macro|PRINTD
mdefine_line|#define PRINTD(bits,format,args...)
DECL|macro|PRINTDB
mdefine_line|#define PRINTDB(bits,format,args...)
DECL|macro|PRINTDM
mdefine_line|#define PRINTDM(bits,format,args...)
DECL|macro|PRINTDE
mdefine_line|#define PRINTDE(bits,format,args...)
macro_line|#endif
DECL|macro|PRINTDD
mdefine_line|#define PRINTDD(bits,format,args...)
DECL|macro|PRINTDDB
mdefine_line|#define PRINTDDB(sec,fmt,args...)
DECL|macro|PRINTDDM
mdefine_line|#define PRINTDDM(sec,fmt,args...)
DECL|macro|PRINTDDE
mdefine_line|#define PRINTDDE(sec,fmt,args...)
singleline_comment|// tunable values (?)
multiline_comment|/* MUST be powers of two -- why ? */
DECL|macro|COM_Q_ENTRIES
mdefine_line|#define COM_Q_ENTRIES        8
DECL|macro|TX_Q_ENTRIES
mdefine_line|#define TX_Q_ENTRIES        32
DECL|macro|RX_Q_ENTRIES
mdefine_line|#define RX_Q_ENTRIES        64
singleline_comment|// fixed values
singleline_comment|// guessing
DECL|macro|AMB_EXTENT
mdefine_line|#define AMB_EXTENT         0x80
singleline_comment|// Minimum allowed size for an Ambassador queue
DECL|macro|MIN_QUEUE_SIZE
mdefine_line|#define MIN_QUEUE_SIZE     2
singleline_comment|// Ambassador microcode allows 1 to 4 pools, we use 4 (simpler)
DECL|macro|NUM_RX_POOLS
mdefine_line|#define NUM_RX_POOLS&t;   4
singleline_comment|// minimum RX buffers required to cope with replenishing delay
DECL|macro|MIN_RX_BUFFERS
mdefine_line|#define MIN_RX_BUFFERS&t;   1
singleline_comment|// minimum PCI latency we will tolerate (32 IS TOO SMALL)
DECL|macro|MIN_PCI_LATENCY
mdefine_line|#define MIN_PCI_LATENCY   64 
singleline_comment|// 255
singleline_comment|// VCs supported by card (VPI always 0)
DECL|macro|NUM_VPI_BITS
mdefine_line|#define NUM_VPI_BITS       0
DECL|macro|NUM_VCI_BITS
mdefine_line|#define NUM_VCI_BITS      10
DECL|macro|NUM_VCS
mdefine_line|#define NUM_VCS         1024
multiline_comment|/* The status field bits defined so far. */
DECL|macro|RX_ERR
mdefine_line|#define RX_ERR&t;&t;0x8000 
singleline_comment|// always present if there is an error (hmm)
DECL|macro|CRC_ERR
mdefine_line|#define CRC_ERR&t;&t;0x4000 
singleline_comment|// AAL5 CRC error
DECL|macro|LEN_ERR
mdefine_line|#define LEN_ERR&t;&t;0x2000 
singleline_comment|// overlength frame
DECL|macro|ABORT_ERR
mdefine_line|#define ABORT_ERR&t;0x1000 
singleline_comment|// zero length field in received frame
DECL|macro|UNUSED_ERR
mdefine_line|#define UNUSED_ERR&t;0x0800 
singleline_comment|// buffer returned unused
singleline_comment|// Adaptor commands
DECL|macro|SRB_OPEN_VC
mdefine_line|#define SRB_OPEN_VC&t;&t;0
multiline_comment|/* par_0: dwordswap(VC_number) */
multiline_comment|/* par_1: dwordswap(flags&lt;&lt;16) or wordswap(flags)*/
multiline_comment|/* flags:&t;&t;*/
multiline_comment|/* LANE:&t;0x0004&t;&t;*/
multiline_comment|/* NOT_UBR:&t;0x0008&t;&t;*/
multiline_comment|/* ABR:&t;&t;0x0010&t;&t;*/
multiline_comment|/* RxPool0:&t;0x0000&t;&t;*/
multiline_comment|/* RxPool1:&t;0x0020&t;&t;*/
multiline_comment|/* RxPool2:&t;0x0040&t;&t;*/
multiline_comment|/* RxPool3:&t;0x0060&t;&t;*/
multiline_comment|/* par_2: dwordswap(fp_rate&lt;&lt;16) or wordswap(fp_rate) */
DECL|macro|SRB_CLOSE_VC
mdefine_line|#define&t;SRB_CLOSE_VC&t;&t;1
multiline_comment|/* par_0: dwordswap(VC_number) */
DECL|macro|SRB_GET_BIA
mdefine_line|#define&t;SRB_GET_BIA&t;&t;2
multiline_comment|/* returns &t;&t;*/
multiline_comment|/* par_0: dwordswap(half BIA) */
multiline_comment|/* par_1: dwordswap(half BIA) */
DECL|macro|SRB_GET_SUNI_STATS
mdefine_line|#define&t;SRB_GET_SUNI_STATS&t;3
multiline_comment|/* par_0: dwordswap(physical_host_address) */
DECL|macro|SRB_SET_BITS_8
mdefine_line|#define&t;SRB_SET_BITS_8&t;&t;4
DECL|macro|SRB_SET_BITS_16
mdefine_line|#define&t;SRB_SET_BITS_16&t;&t;5
DECL|macro|SRB_SET_BITS_32
mdefine_line|#define&t;SRB_SET_BITS_32&t;&t;6
DECL|macro|SRB_CLEAR_BITS_8
mdefine_line|#define&t;SRB_CLEAR_BITS_8&t;7
DECL|macro|SRB_CLEAR_BITS_16
mdefine_line|#define&t;SRB_CLEAR_BITS_16&t;8
DECL|macro|SRB_CLEAR_BITS_32
mdefine_line|#define&t;SRB_CLEAR_BITS_32&t;9
multiline_comment|/* par_0: dwordswap(ATMizer address)&t;*/
multiline_comment|/* par_1: dwordswap(mask) */
DECL|macro|SRB_SET_8
mdefine_line|#define&t;SRB_SET_8&t;&t;10
DECL|macro|SRB_SET_16
mdefine_line|#define&t;SRB_SET_16&t;&t;11
DECL|macro|SRB_SET_32
mdefine_line|#define&t;SRB_SET_32&t;&t;12
multiline_comment|/* par_0: dwordswap(ATMizer address)&t;*/
multiline_comment|/* par_1: dwordswap(data) */
DECL|macro|SRB_GET_32
mdefine_line|#define&t;SRB_GET_32&t;&t;13
multiline_comment|/* par_0: dwordswap(ATMizer address)&t;*/
multiline_comment|/* returns&t;&t;&t;*/
multiline_comment|/* par_1: dwordswap(ATMizer data) */
DECL|macro|SRB_GET_VERSION
mdefine_line|#define SRB_GET_VERSION&t;&t;14
multiline_comment|/* returns &t;&t;*/
multiline_comment|/* par_0: dwordswap(Major Version) */
multiline_comment|/* par_1: dwordswap(Minor Version) */
DECL|macro|SRB_FLUSH_BUFFER_Q
mdefine_line|#define SRB_FLUSH_BUFFER_Q&t;15
multiline_comment|/* Only flags to define which buffer pool; all others must be zero */
multiline_comment|/* par_0: dwordswap(flags&lt;&lt;16) or wordswap(flags)*/
DECL|macro|SRB_GET_DMA_SPEEDS
mdefine_line|#define&t;SRB_GET_DMA_SPEEDS&t;16
multiline_comment|/* returns &t;&t;*/
multiline_comment|/* par_0: dwordswap(Read speed (bytes/sec)) */
multiline_comment|/* par_1: dwordswap(Write speed (bytes/sec)) */
DECL|macro|SRB_MODIFY_VC_RATE
mdefine_line|#define SRB_MODIFY_VC_RATE&t;17
multiline_comment|/* par_0: dwordswap(VC_number) */
multiline_comment|/* par_1: dwordswap(fp_rate&lt;&lt;16) or wordswap(fp_rate) */
DECL|macro|SRB_MODIFY_VC_FLAGS
mdefine_line|#define SRB_MODIFY_VC_FLAGS&t;18
multiline_comment|/* par_0: dwordswap(VC_number) */
multiline_comment|/* par_1: dwordswap(flags&lt;&lt;16) or wordswap(flags)*/
multiline_comment|/* flags:&t;&t;*/
multiline_comment|/* LANE:&t;0x0004&t;&t;*/
multiline_comment|/* NOT_UBR:&t;0x0008&t;&t;*/
multiline_comment|/* ABR:&t;&t;0x0010&t;&t;*/
multiline_comment|/* RxPool0:&t;0x0000&t;&t;*/
multiline_comment|/* RxPool1:&t;0x0020&t;&t;*/
multiline_comment|/* RxPool2:&t;0x0040&t;&t;*/
multiline_comment|/* RxPool3:&t;0x0060&t;&t;*/
DECL|macro|SRB_RATE_SHIFT
mdefine_line|#define SRB_RATE_SHIFT          16
DECL|macro|SRB_POOL_SHIFT
mdefine_line|#define SRB_POOL_SHIFT          (SRB_FLAGS_SHIFT+5)
DECL|macro|SRB_FLAGS_SHIFT
mdefine_line|#define SRB_FLAGS_SHIFT         16
DECL|macro|SRB_STOP_TASKING
mdefine_line|#define&t;SRB_STOP_TASKING&t;19
DECL|macro|SRB_START_TASKING
mdefine_line|#define&t;SRB_START_TASKING&t;20
DECL|macro|SRB_SHUT_DOWN
mdefine_line|#define SRB_SHUT_DOWN&t;&t;21
DECL|macro|MAX_SRB
mdefine_line|#define MAX_SRB&t;&t;&t;21
DECL|macro|SRB_COMPLETE
mdefine_line|#define SRB_COMPLETE&t;&t;0xffffffff
DECL|macro|TX_FRAME
mdefine_line|#define TX_FRAME          &t;0x80000000
singleline_comment|// number of types of SRB MUST be a power of two -- why?
DECL|macro|NUM_OF_SRB
mdefine_line|#define NUM_OF_SRB&t;32
singleline_comment|// number of bits of period info for rate
DECL|macro|MAX_RATE_BITS
mdefine_line|#define MAX_RATE_BITS&t;6
DECL|macro|TX_UBR
mdefine_line|#define TX_UBR          0x0000
DECL|macro|TX_UBR_CAPPED
mdefine_line|#define TX_UBR_CAPPED   0x0008
DECL|macro|TX_ABR
mdefine_line|#define TX_ABR          0x0018
DECL|macro|TX_FRAME_NOTCAP
mdefine_line|#define TX_FRAME_NOTCAP 0x0000
DECL|macro|TX_FRAME_CAPPED
mdefine_line|#define TX_FRAME_CAPPED 0x8000
DECL|macro|FP_155_RATE
mdefine_line|#define FP_155_RATE&t;0x24b1
DECL|macro|FP_25_RATE
mdefine_line|#define FP_25_RATE&t;0x1f9d
multiline_comment|/* #define VERSION_NUMBER 0x01000000 // initial release */
multiline_comment|/* #define VERSION_NUMBER 0x01010000 // fixed startup probs PLX MB0 not cleared */
multiline_comment|/* #define VERSION_NUMBER 0x01020000 // changed SUNI reset timings; allowed r/w onchip */
multiline_comment|/* #define VERSION_NUMBER 0x01030000 // clear local doorbell int reg on reset */
multiline_comment|/* #define VERSION_NUMBER 0x01040000 // PLX bug work around version PLUS */
multiline_comment|/* remove race conditions on basic interface */
multiline_comment|/* indicate to the host that diagnostics */
multiline_comment|/* have finished; if failed, how and what  */
multiline_comment|/* failed */
multiline_comment|/* fix host memory test to fix PLX bug */
multiline_comment|/* allow flash upgrade and BIA upgrade directly */
multiline_comment|/*  */
DECL|macro|VERSION_NUMBER
mdefine_line|#define VERSION_NUMBER 0x01050025 /* Jason&squot;s first hacked version. */
multiline_comment|/* Change in download algorithm */
DECL|macro|DMA_VALID
mdefine_line|#define DMA_VALID 0xb728e149 /* completely random */
DECL|macro|FLASH_BASE
mdefine_line|#define FLASH_BASE 0xa0c00000
DECL|macro|FLASH_SIZE
mdefine_line|#define FLASH_SIZE 0x00020000&t;&t;&t;/* 128K */
DECL|macro|BIA_BASE
mdefine_line|#define BIA_BASE (FLASH_BASE+0x0001c000)&t;/* Flash Sector 7 */
DECL|macro|BIA_ADDRESS
mdefine_line|#define BIA_ADDRESS ((void *)0xa0c1c000)
DECL|macro|PLX_BASE
mdefine_line|#define PLX_BASE 0xe0000000
r_typedef
r_enum
(brace
DECL|enumerator|host_memory_test
id|host_memory_test
op_assign
l_int|1
comma
DECL|enumerator|read_adapter_memory
id|read_adapter_memory
comma
DECL|enumerator|write_adapter_memory
id|write_adapter_memory
comma
DECL|enumerator|adapter_start
id|adapter_start
comma
DECL|enumerator|get_version_number
id|get_version_number
comma
DECL|enumerator|interrupt_host
id|interrupt_host
comma
DECL|enumerator|flash_erase_sector
id|flash_erase_sector
comma
DECL|enumerator|adap_download_block
id|adap_download_block
op_assign
l_int|0x20
comma
DECL|enumerator|adap_erase_flash
id|adap_erase_flash
comma
DECL|enumerator|adap_run_in_iram
id|adap_run_in_iram
comma
DECL|enumerator|adap_end_download
id|adap_end_download
DECL|typedef|loader_command
)brace
id|loader_command
suffix:semicolon
DECL|macro|BAD_COMMAND
mdefine_line|#define BAD_COMMAND                     (-1)
DECL|macro|COMMAND_IN_PROGRESS
mdefine_line|#define COMMAND_IN_PROGRESS             1
DECL|macro|COMMAND_PASSED_TEST
mdefine_line|#define COMMAND_PASSED_TEST             2
DECL|macro|COMMAND_FAILED_TEST
mdefine_line|#define COMMAND_FAILED_TEST             3
DECL|macro|COMMAND_READ_DATA_OK
mdefine_line|#define COMMAND_READ_DATA_OK            4
DECL|macro|COMMAND_READ_BAD_ADDRESS
mdefine_line|#define COMMAND_READ_BAD_ADDRESS        5
DECL|macro|COMMAND_WRITE_DATA_OK
mdefine_line|#define COMMAND_WRITE_DATA_OK           6
DECL|macro|COMMAND_WRITE_BAD_ADDRESS
mdefine_line|#define COMMAND_WRITE_BAD_ADDRESS       7
DECL|macro|COMMAND_WRITE_FLASH_FAILURE
mdefine_line|#define COMMAND_WRITE_FLASH_FAILURE     8
DECL|macro|COMMAND_COMPLETE
mdefine_line|#define COMMAND_COMPLETE                9
DECL|macro|COMMAND_FLASH_ERASE_FAILURE
mdefine_line|#define COMMAND_FLASH_ERASE_FAILURE&t;10
DECL|macro|COMMAND_WRITE_BAD_DATA
mdefine_line|#define COMMAND_WRITE_BAD_DATA&t;&t;11
multiline_comment|/* bit fields for mailbox[0] return values */
DECL|macro|GPINT_TST_FAILURE
mdefine_line|#define GPINT_TST_FAILURE               0x00000001      
DECL|macro|SUNI_DATA_PATTERN_FAILURE
mdefine_line|#define SUNI_DATA_PATTERN_FAILURE       0x00000002
DECL|macro|SUNI_DATA_BITS_FAILURE
mdefine_line|#define SUNI_DATA_BITS_FAILURE          0x00000004
DECL|macro|SUNI_UTOPIA_FAILURE
mdefine_line|#define SUNI_UTOPIA_FAILURE             0x00000008
DECL|macro|SUNI_FIFO_FAILURE
mdefine_line|#define SUNI_FIFO_FAILURE               0x00000010
DECL|macro|SRAM_FAILURE
mdefine_line|#define SRAM_FAILURE                    0x00000020
DECL|macro|SELF_TEST_FAILURE
mdefine_line|#define SELF_TEST_FAILURE               0x0000003f
multiline_comment|/* mailbox[1] = 0 in progress, -1 on completion */
multiline_comment|/* mailbox[2] = current test 00 00 test(8 bit) phase(8 bit) */
multiline_comment|/* mailbox[3] = last failure, 00 00 test(8 bit) phase(8 bit) */
multiline_comment|/* mailbox[4],mailbox[5],mailbox[6] random failure values */
multiline_comment|/* PLX/etc. memory map including command structure */
multiline_comment|/* These registers may also be memory mapped in PCI memory */
DECL|macro|UNUSED_LOADER_MAILBOXES
mdefine_line|#define UNUSED_LOADER_MAILBOXES 6
r_typedef
r_struct
(brace
DECL|member|stuff
id|u32
id|stuff
(braket
l_int|16
)braket
suffix:semicolon
r_union
(brace
r_struct
(brace
DECL|member|result
id|u32
id|result
suffix:semicolon
DECL|member|ready
id|u32
id|ready
suffix:semicolon
DECL|member|stuff
id|u32
id|stuff
(braket
id|UNUSED_LOADER_MAILBOXES
)braket
suffix:semicolon
DECL|member|loader
)brace
id|loader
suffix:semicolon
r_struct
(brace
DECL|member|cmd_address
id|u32
id|cmd_address
suffix:semicolon
DECL|member|tx_address
id|u32
id|tx_address
suffix:semicolon
DECL|member|rx_address
id|u32
id|rx_address
(braket
id|NUM_RX_POOLS
)braket
suffix:semicolon
DECL|member|gen_counter
id|u32
id|gen_counter
suffix:semicolon
DECL|member|spare
id|u32
id|spare
suffix:semicolon
DECL|member|adapter
)brace
id|adapter
suffix:semicolon
DECL|member|mb
)brace
id|mb
suffix:semicolon
DECL|member|doorbell
id|u32
id|doorbell
suffix:semicolon
DECL|member|interrupt
id|u32
id|interrupt
suffix:semicolon
DECL|member|interrupt_control
id|u32
id|interrupt_control
suffix:semicolon
DECL|member|reset_control
id|u32
id|reset_control
suffix:semicolon
DECL|typedef|amb_mem
)brace
id|amb_mem
suffix:semicolon
multiline_comment|/* RESET bit, IRQ (card to host) and doorbell (host to card) enable bits */
DECL|macro|AMB_RESET_BITS
mdefine_line|#define AMB_RESET_BITS&t;   0x40000000
DECL|macro|AMB_INTERRUPT_BITS
mdefine_line|#define AMB_INTERRUPT_BITS 0x00000300
DECL|macro|AMB_DOORBELL_BITS
mdefine_line|#define AMB_DOORBELL_BITS  0x00030000
multiline_comment|/* loader commands */
DECL|macro|MAX_COMMAND_DATA
mdefine_line|#define MAX_COMMAND_DATA 13
DECL|macro|MAX_TRANSFER_DATA
mdefine_line|#define MAX_TRANSFER_DATA 11
r_typedef
r_struct
(brace
DECL|member|address
id|u32
id|address
suffix:semicolon
DECL|member|count
id|u32
id|count
suffix:semicolon
DECL|member|data
id|u32
id|data
(braket
id|MAX_TRANSFER_DATA
)braket
suffix:semicolon
DECL|typedef|transfer_block
)brace
id|transfer_block
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|result
id|u32
id|result
suffix:semicolon
DECL|member|command
id|u32
id|command
suffix:semicolon
r_union
(brace
DECL|member|transfer
id|transfer_block
id|transfer
suffix:semicolon
DECL|member|version
id|u32
id|version
suffix:semicolon
DECL|member|start
id|u32
id|start
suffix:semicolon
DECL|member|data
id|u32
id|data
(braket
id|MAX_COMMAND_DATA
)braket
suffix:semicolon
DECL|member|payload
)brace
id|payload
suffix:semicolon
DECL|member|valid
id|u32
id|valid
suffix:semicolon
DECL|typedef|loader_block
)brace
id|loader_block
suffix:semicolon
multiline_comment|/* command queue */
multiline_comment|/* Again all data are BIG ENDIAN */
r_typedef
r_struct
(brace
r_union
(brace
r_struct
(brace
DECL|member|vc
id|u32
id|vc
suffix:semicolon
DECL|member|flags
id|u32
id|flags
suffix:semicolon
DECL|member|rate
id|u32
id|rate
suffix:semicolon
DECL|member|open
)brace
id|open
suffix:semicolon
r_struct
(brace
DECL|member|vc
id|u32
id|vc
suffix:semicolon
DECL|member|rate
id|u32
id|rate
suffix:semicolon
DECL|member|modify_rate
)brace
id|modify_rate
suffix:semicolon
r_struct
(brace
DECL|member|vc
id|u32
id|vc
suffix:semicolon
DECL|member|flags
id|u32
id|flags
suffix:semicolon
DECL|member|modify_flags
)brace
id|modify_flags
suffix:semicolon
r_struct
(brace
DECL|member|vc
id|u32
id|vc
suffix:semicolon
DECL|member|close
)brace
id|close
suffix:semicolon
r_struct
(brace
DECL|member|lower4
id|u32
id|lower4
suffix:semicolon
DECL|member|upper2
id|u32
id|upper2
suffix:semicolon
DECL|member|bia
)brace
id|bia
suffix:semicolon
r_struct
(brace
DECL|member|address
id|u32
id|address
suffix:semicolon
DECL|member|suni
)brace
id|suni
suffix:semicolon
r_struct
(brace
DECL|member|major
id|u32
id|major
suffix:semicolon
DECL|member|minor
id|u32
id|minor
suffix:semicolon
DECL|member|version
)brace
id|version
suffix:semicolon
r_struct
(brace
DECL|member|read
id|u32
id|read
suffix:semicolon
DECL|member|write
id|u32
id|write
suffix:semicolon
DECL|member|speed
)brace
id|speed
suffix:semicolon
r_struct
(brace
DECL|member|flags
id|u32
id|flags
suffix:semicolon
DECL|member|flush
)brace
id|flush
suffix:semicolon
r_struct
(brace
DECL|member|address
id|u32
id|address
suffix:semicolon
DECL|member|data
id|u32
id|data
suffix:semicolon
DECL|member|memory
)brace
id|memory
suffix:semicolon
DECL|member|par
id|u32
id|par
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|args
)brace
id|args
suffix:semicolon
DECL|member|request
id|u32
id|request
suffix:semicolon
DECL|typedef|command
)brace
id|command
suffix:semicolon
multiline_comment|/* transmit queues and associated structures */
multiline_comment|/* The hosts transmit structure. All BIG ENDIAN; host address&n;   restricted to first 1GByte, but address passed to the card must&n;   have the top MS bit or&squot;ed in. -- check this */
multiline_comment|/* TX is described by 1+ tx_frags followed by a tx_frag_end */
r_typedef
r_struct
(brace
DECL|member|bytes
id|u32
id|bytes
suffix:semicolon
DECL|member|address
id|u32
id|address
suffix:semicolon
DECL|typedef|tx_frag
)brace
id|tx_frag
suffix:semicolon
multiline_comment|/* apart from handle the fields here are for the adapter to play with&n;   and should be set to zero */
r_typedef
r_struct
(brace
DECL|member|handle
id|u32
id|handle
suffix:semicolon
DECL|member|vc
id|u16
id|vc
suffix:semicolon
DECL|member|next_descriptor_length
id|u16
id|next_descriptor_length
suffix:semicolon
DECL|member|next_descriptor
id|u32
id|next_descriptor
suffix:semicolon
macro_line|#ifdef AMB_NEW_MICROCODE
DECL|member|cpcs_uu
id|u8
id|cpcs_uu
suffix:semicolon
DECL|member|cpi
id|u8
id|cpi
suffix:semicolon
DECL|member|pad
id|u16
id|pad
suffix:semicolon
macro_line|#endif
DECL|typedef|tx_frag_end
)brace
id|tx_frag_end
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|tx_frag
id|tx_frag
id|tx_frag
suffix:semicolon
DECL|member|tx_frag_end
id|tx_frag_end
id|tx_frag_end
suffix:semicolon
DECL|member|skb
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
DECL|typedef|tx_simple
)brace
id|tx_simple
suffix:semicolon
macro_line|#if 0
r_typedef
r_union
(brace
id|tx_frag
id|fragment
suffix:semicolon
id|tx_frag_end
id|end_of_list
suffix:semicolon
)brace
id|tx_descr
suffix:semicolon
macro_line|#endif
multiline_comment|/* this &quot;points&quot; to the sequence of fragments and trailer */
r_typedef
r_struct
(brace
DECL|member|vc
id|u16
id|vc
suffix:semicolon
DECL|member|tx_descr_length
id|u16
id|tx_descr_length
suffix:semicolon
DECL|member|tx_descr_addr
id|u32
id|tx_descr_addr
suffix:semicolon
DECL|typedef|tx_in
)brace
id|tx_in
suffix:semicolon
multiline_comment|/* handle is the handle from tx_in */
r_typedef
r_struct
(brace
DECL|member|handle
id|u32
id|handle
suffix:semicolon
DECL|typedef|tx_out
)brace
id|tx_out
suffix:semicolon
multiline_comment|/* receive frame structure */
multiline_comment|/* All BIG ENDIAN; handle is as passed from host; length is zero for&n;   aborted frames, and frames with errors. Header is actually VC&n;   number, lec-id is NOT yet supported. */
r_typedef
r_struct
(brace
DECL|member|handle
id|u32
id|handle
suffix:semicolon
DECL|member|vc
id|u16
id|vc
suffix:semicolon
DECL|member|lec_id
id|u16
id|lec_id
suffix:semicolon
singleline_comment|// unused
DECL|member|status
id|u16
id|status
suffix:semicolon
DECL|member|length
id|u16
id|length
suffix:semicolon
DECL|typedef|rx_out
)brace
id|rx_out
suffix:semicolon
multiline_comment|/* buffer supply structure */
r_typedef
r_struct
(brace
DECL|member|handle
id|u32
id|handle
suffix:semicolon
DECL|member|host_address
id|u32
id|host_address
suffix:semicolon
DECL|typedef|rx_in
)brace
id|rx_in
suffix:semicolon
multiline_comment|/* This first structure is the area in host memory where the adapter&n;   writes its pointer values. These pointer values are BIG ENDIAN and&n;   reside in the same 4MB &squot;page&squot; as this structure. The host gives the&n;   adapter the address of this block by sending a doorbell interrupt&n;   to the adapter after downloading the code and setting it going. The&n;   addresses have the top 10 bits set to 1010000010b -- really?&n;   &n;   The host must initialise these before handing the block to the&n;   adapter. */
r_typedef
r_struct
(brace
DECL|member|command_start
id|u32
id|command_start
suffix:semicolon
multiline_comment|/* SRB commands completions */
DECL|member|command_end
id|u32
id|command_end
suffix:semicolon
multiline_comment|/* SRB commands completions */
DECL|member|tx_start
id|u32
id|tx_start
suffix:semicolon
DECL|member|tx_end
id|u32
id|tx_end
suffix:semicolon
DECL|member|txcom_start
id|u32
id|txcom_start
suffix:semicolon
multiline_comment|/* tx completions */
DECL|member|txcom_end
id|u32
id|txcom_end
suffix:semicolon
multiline_comment|/* tx completions */
r_struct
(brace
DECL|member|buffer_start
id|u32
id|buffer_start
suffix:semicolon
DECL|member|buffer_end
id|u32
id|buffer_end
suffix:semicolon
DECL|member|buffer_q_get
id|u32
id|buffer_q_get
suffix:semicolon
DECL|member|buffer_q_end
id|u32
id|buffer_q_end
suffix:semicolon
DECL|member|buffer_aptr
id|u32
id|buffer_aptr
suffix:semicolon
DECL|member|rx_start
id|u32
id|rx_start
suffix:semicolon
multiline_comment|/* rx completions */
DECL|member|rx_end
id|u32
id|rx_end
suffix:semicolon
DECL|member|rx_ptr
id|u32
id|rx_ptr
suffix:semicolon
DECL|member|buffer_size
id|u32
id|buffer_size
suffix:semicolon
multiline_comment|/* size of host buffer */
DECL|member|rec_struct
)brace
id|rec_struct
(braket
id|NUM_RX_POOLS
)braket
suffix:semicolon
macro_line|#ifdef AMB_NEW_MICROCODE
DECL|member|init_flags
id|u16
id|init_flags
suffix:semicolon
DECL|member|talk_block_spare
id|u16
id|talk_block_spare
suffix:semicolon
macro_line|#endif
DECL|typedef|adap_talk_block
)brace
id|adap_talk_block
suffix:semicolon
multiline_comment|/* This structure must be kept in line with the vcr image in sarmain.h&n;   &n;   This is the structure in the host filled in by the adapter by&n;   GET_SUNI_STATS */
r_typedef
r_struct
(brace
DECL|member|racp_chcs
id|u8
id|racp_chcs
suffix:semicolon
DECL|member|racp_uhcs
id|u8
id|racp_uhcs
suffix:semicolon
DECL|member|spare
id|u16
id|spare
suffix:semicolon
DECL|member|racp_rcell
id|u32
id|racp_rcell
suffix:semicolon
DECL|member|tacp_tcell
id|u32
id|tacp_tcell
suffix:semicolon
DECL|member|flags
id|u32
id|flags
suffix:semicolon
DECL|member|dropped_cells
id|u32
id|dropped_cells
suffix:semicolon
DECL|member|dropped_frames
id|u32
id|dropped_frames
suffix:semicolon
DECL|typedef|suni_stats
)brace
id|suni_stats
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|dead
id|dead
DECL|typedef|amb_flags
)brace
id|amb_flags
suffix:semicolon
DECL|macro|NEXTQ
mdefine_line|#define NEXTQ(current,start,limit) &bslash;&n;  ( (current)+1 &lt; (limit) ? (current)+1 : (start) ) 
r_typedef
r_struct
(brace
DECL|member|start
id|command
op_star
id|start
suffix:semicolon
DECL|member|in
id|command
op_star
id|in
suffix:semicolon
DECL|member|out
id|command
op_star
id|out
suffix:semicolon
DECL|member|limit
id|command
op_star
id|limit
suffix:semicolon
DECL|typedef|amb_cq_ptrs
)brace
id|amb_cq_ptrs
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|pending
r_int
r_int
id|pending
suffix:semicolon
DECL|member|high
r_int
r_int
id|high
suffix:semicolon
DECL|member|filled
r_int
r_int
id|filled
suffix:semicolon
DECL|member|maximum
r_int
r_int
id|maximum
suffix:semicolon
singleline_comment|// size - 1 (q implementation)
DECL|member|ptrs
id|amb_cq_ptrs
id|ptrs
suffix:semicolon
DECL|typedef|amb_cq
)brace
id|amb_cq
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|pending
r_int
r_int
id|pending
suffix:semicolon
DECL|member|high
r_int
r_int
id|high
suffix:semicolon
DECL|member|filled
r_int
r_int
id|filled
suffix:semicolon
DECL|member|maximum
r_int
r_int
id|maximum
suffix:semicolon
singleline_comment|// size - 1 (q implementation)
r_struct
(brace
DECL|member|start
id|tx_in
op_star
id|start
suffix:semicolon
DECL|member|ptr
id|tx_in
op_star
id|ptr
suffix:semicolon
DECL|member|limit
id|tx_in
op_star
id|limit
suffix:semicolon
DECL|member|in
)brace
id|in
suffix:semicolon
r_struct
(brace
DECL|member|start
id|tx_out
op_star
id|start
suffix:semicolon
DECL|member|ptr
id|tx_out
op_star
id|ptr
suffix:semicolon
DECL|member|limit
id|tx_out
op_star
id|limit
suffix:semicolon
DECL|member|out
)brace
id|out
suffix:semicolon
DECL|typedef|amb_txq
)brace
id|amb_txq
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|pending
r_int
r_int
id|pending
suffix:semicolon
DECL|member|low
r_int
r_int
id|low
suffix:semicolon
DECL|member|emptied
r_int
r_int
id|emptied
suffix:semicolon
DECL|member|maximum
r_int
r_int
id|maximum
suffix:semicolon
singleline_comment|// size - 1 (q implementation)
r_struct
(brace
DECL|member|start
id|rx_in
op_star
id|start
suffix:semicolon
DECL|member|ptr
id|rx_in
op_star
id|ptr
suffix:semicolon
DECL|member|limit
id|rx_in
op_star
id|limit
suffix:semicolon
DECL|member|in
)brace
id|in
suffix:semicolon
r_struct
(brace
DECL|member|start
id|rx_out
op_star
id|start
suffix:semicolon
DECL|member|ptr
id|rx_out
op_star
id|ptr
suffix:semicolon
DECL|member|limit
id|rx_out
op_star
id|limit
suffix:semicolon
DECL|member|out
)brace
id|out
suffix:semicolon
DECL|member|buffers_wanted
r_int
r_int
id|buffers_wanted
suffix:semicolon
DECL|member|buffer_size
r_int
r_int
id|buffer_size
suffix:semicolon
DECL|typedef|amb_rxq
)brace
id|amb_rxq
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|tx_ok
r_int
r_int
id|tx_ok
suffix:semicolon
r_struct
(brace
DECL|member|ok
r_int
r_int
id|ok
suffix:semicolon
DECL|member|error
r_int
r_int
id|error
suffix:semicolon
DECL|member|badcrc
r_int
r_int
id|badcrc
suffix:semicolon
DECL|member|toolong
r_int
r_int
id|toolong
suffix:semicolon
DECL|member|aborted
r_int
r_int
id|aborted
suffix:semicolon
DECL|member|unused
r_int
r_int
id|unused
suffix:semicolon
DECL|member|rx
)brace
id|rx
suffix:semicolon
DECL|typedef|amb_stats
)brace
id|amb_stats
suffix:semicolon
singleline_comment|// a single struct pointed to by atm_vcc-&gt;dev_data
r_typedef
r_struct
(brace
DECL|member|tx_vc_bits
id|u8
id|tx_vc_bits
suffix:colon
l_int|7
suffix:semicolon
DECL|member|tx_present
id|u8
id|tx_present
suffix:colon
l_int|1
suffix:semicolon
DECL|typedef|amb_tx_info
)brace
id|amb_tx_info
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|pool
r_int
r_char
id|pool
suffix:semicolon
DECL|typedef|amb_rx_info
)brace
id|amb_rx_info
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|rx_info
id|amb_rx_info
id|rx_info
suffix:semicolon
DECL|member|tx_frame_bits
id|u16
id|tx_frame_bits
suffix:semicolon
DECL|member|tx_rate
r_int
r_int
id|tx_rate
suffix:semicolon
DECL|member|rx_rate
r_int
r_int
id|rx_rate
suffix:semicolon
DECL|typedef|amb_vcc
)brace
id|amb_vcc
suffix:semicolon
DECL|struct|amb_dev
r_struct
id|amb_dev
(brace
DECL|member|irq
id|u8
id|irq
suffix:semicolon
DECL|member|flags
id|u8
id|flags
suffix:semicolon
DECL|member|iobase
id|u32
id|iobase
suffix:semicolon
DECL|member|membase
id|u32
op_star
id|membase
suffix:semicolon
macro_line|#ifdef FILL_RX_POOLS_IN_BH
DECL|member|bh
r_struct
id|tq_struct
id|bh
suffix:semicolon
macro_line|#endif
DECL|member|cq
id|amb_cq
id|cq
suffix:semicolon
DECL|member|txq
id|amb_txq
id|txq
suffix:semicolon
DECL|member|rxq
id|amb_rxq
id|rxq
(braket
id|NUM_RX_POOLS
)braket
suffix:semicolon
DECL|member|vcc_sf
r_struct
id|semaphore
id|vcc_sf
suffix:semicolon
DECL|member|txer
id|amb_tx_info
id|txer
(braket
id|NUM_VCS
)braket
suffix:semicolon
DECL|member|rxer
r_struct
id|atm_vcc
op_star
id|rxer
(braket
id|NUM_VCS
)braket
suffix:semicolon
DECL|member|tx_avail
r_int
r_int
id|tx_avail
suffix:semicolon
DECL|member|rx_avail
r_int
r_int
id|rx_avail
suffix:semicolon
DECL|member|stats
id|amb_stats
id|stats
suffix:semicolon
DECL|member|atm_dev
r_struct
id|atm_dev
op_star
id|atm_dev
suffix:semicolon
DECL|member|pci_dev
r_struct
id|pci_dev
op_star
id|pci_dev
suffix:semicolon
DECL|member|prev
r_struct
id|amb_dev
op_star
id|prev
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|amb_dev
r_typedef
r_struct
id|amb_dev
id|amb_dev
suffix:semicolon
DECL|macro|AMB_DEV
mdefine_line|#define AMB_DEV(atm_dev) ((amb_dev *) (atm_dev)-&gt;dev_data)
DECL|macro|AMB_VCC
mdefine_line|#define AMB_VCC(atm_vcc) ((amb_vcc *) (atm_vcc)-&gt;dev_data)
multiline_comment|/* the microcode */
r_typedef
r_struct
(brace
DECL|member|start
id|u32
id|start
suffix:semicolon
DECL|member|count
r_int
r_int
id|count
suffix:semicolon
DECL|typedef|region
)brace
id|region
suffix:semicolon
DECL|variable|ucode_regions
r_static
id|region
id|ucode_regions
(braket
)braket
suffix:semicolon
DECL|variable|ucode_data
r_static
id|u32
id|ucode_data
(braket
)braket
suffix:semicolon
DECL|variable|ucode_start
r_static
id|u32
id|ucode_start
suffix:semicolon
multiline_comment|/* rate rounding */
r_typedef
r_enum
(brace
DECL|enumerator|round_up
id|round_up
comma
DECL|enumerator|round_down
id|round_down
comma
DECL|enumerator|round_nearest
id|round_nearest
DECL|typedef|rounding
)brace
id|rounding
suffix:semicolon
macro_line|#endif
eof
