multiline_comment|/*&n;** *************************************************************************&n;**&n;**&n;**     R C L A N M T L . H             $Revision: 6 $&n;**&n;**&n;**  RedCreek I2O LAN Message Transport Layer header file.&n;**&n;**  ---------------------------------------------------------------------&n;**  ---     Copyright (c) 1997-1999, RedCreek Communications Inc.     ---&n;**  ---                   All rights reserved.                        ---&n;**  ---------------------------------------------------------------------&n;**&n;**  File Description:&n;**&n;**  Header file for host I2O (Intelligent I/O) LAN message transport layer &n;**  API and data types.&n;**&n;**  This program is free software; you can redistribute it and/or modify&n;**  it under the terms of the GNU General Public License as published by&n;**  the Free Software Foundation; either version 2 of the License, or&n;**  (at your option) any later version.&n;&n;**  This program is distributed in the hope that it will be useful,&n;**  but WITHOUT ANY WARRANTY; without even the implied warranty of&n;**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;**  GNU General Public License for more details.&n;&n;**  You should have received a copy of the GNU General Public License&n;**  along with this program; if not, write to the Free Software&n;**  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;**&n;** *************************************************************************&n;*/
macro_line|#ifndef RCLANMTL_H
DECL|macro|RCLANMTL_H
mdefine_line|#define RCLANMTL_H
multiline_comment|/* Linux specific includes */
macro_line|#include &lt;asm/types.h&gt;
macro_line|#ifdef RC_LINUX_MODULE     /* linux modules need non-library version of string functions */
macro_line|#include &lt;linux/string.h&gt;
macro_line|#else
macro_line|#include &lt;string.h&gt;
macro_line|#endif
macro_line|#include &lt;linux/delay.h&gt; /* for udelay() */
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/if_ether.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;asm/io.h&gt;
multiline_comment|/* Debug stuff. Define for debug output */
DECL|macro|RCDEBUG
mdefine_line|#define RCDEBUG
macro_line|#ifdef RCDEBUG
DECL|macro|dprintk
mdefine_line|#define dprintk(args...) printk(KERN_DEBUG &quot;(rcpci45 driver:) &quot; args)
macro_line|#else
DECL|macro|dprintk
mdefine_line|#define dprintk(args...) { }
macro_line|#endif
multiline_comment|/* Typedefs */
multiline_comment|/* scalar data types */
DECL|typedef|U8
r_typedef
id|__u8
id|U8
suffix:semicolon
DECL|typedef|U16
r_typedef
id|__u16
id|U16
suffix:semicolon
DECL|typedef|U32
r_typedef
id|__u32
id|U32
suffix:semicolon
DECL|typedef|PU8
r_typedef
id|__u8
op_star
id|PU8
suffix:semicolon
DECL|typedef|PU16
r_typedef
id|__u16
op_star
id|PU16
suffix:semicolon
DECL|typedef|PU32
r_typedef
id|__u32
op_star
id|PU32
suffix:semicolon
DECL|typedef|BF
r_typedef
r_int
r_int
id|BF
suffix:semicolon
DECL|typedef|RC_RETURN
r_typedef
r_int
id|RC_RETURN
suffix:semicolon
multiline_comment|/* &n; ** type PFNWAITCALLBACK&n; **&n; ** pointer to void function - type used for WaitCallback in some functions &n; */
DECL|typedef|PFNWAITCALLBACK
r_typedef
r_void
(paren
op_star
id|PFNWAITCALLBACK
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* void argument avoids compiler complaint */
multiline_comment|/*&n; ** type PFNTXCALLBACK &n; **&n; ** Pointer to user&squot;s transmit callback function.  This user function is&n; ** called from RCProcI2OMsgQ() when packet have been transmitted from buffers&n; ** given in the RCI2OSendPacket() function.  BufferContext is a pointer to&n; ** an array of 32 bit context values.  These are the values the user assigned&n; ** and passed in the TCB to the RCI2OSendPacket() function.  PcktCount&n; ** indicates the number of buffer context values in the BufferContext[] array.&n; ** The User&squot;s TransmitCallbackFunction should recover (put back in free queue)&n; ** the packet buffers associated with the buffer context values.&n; */
DECL|typedef|PFNTXCALLBACK
r_typedef
r_void
(paren
op_star
id|PFNTXCALLBACK
)paren
(paren
id|U32
id|Status
comma
id|U16
id|PcktCount
comma
id|PU32
id|BufferContext
comma
r_struct
id|net_device
op_star
)paren
suffix:semicolon
multiline_comment|/* &n; ** type PFNRXCALLBACK &n; **&n; ** Pointer to user&squot;s receive callback function.  This user function&n; ** is called from RCProcI2OMsgQ() when packets have been received into&n; ** previously posted packet buffers throught the RCPostRecvBuffers() function.&n; ** The received callback function should process the Packet Descriptor Block&n; ** pointed to by PacketDescBlock. See Packet Decription Block below.&n; */
DECL|typedef|PFNRXCALLBACK
r_typedef
r_void
(paren
op_star
id|PFNRXCALLBACK
)paren
(paren
id|U32
id|Status
comma
id|U8
id|PktCount
comma
id|U32
id|BucketsRemain
comma
id|PU32
id|PacketDescBlock
comma
r_struct
id|net_device
op_star
)paren
suffix:semicolon
multiline_comment|/* &n; ** type PFNCALLBACK &n; **&n; ** Pointer to user&squot;s generic callback function.  This user function&n; ** can be passed to LANReset or LANShutdown and is called when the &n; ** the reset or shutdown is complete.&n; ** Param1 and Param2 are invalid for LANReset and LANShutdown.&n; */
DECL|typedef|PFNCALLBACK
r_typedef
r_void
(paren
op_star
id|PFNCALLBACK
)paren
(paren
id|U32
id|Status
comma
id|U32
id|Param1
comma
id|U32
id|Param2
comma
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/*&n;**  Message Unit CSR definitions for RedCreek PCI45 board&n;*/
DECL|struct|tag_rcatu
r_typedef
r_struct
id|tag_rcatu
(brace
DECL|member|APICRegSel
r_volatile
r_int
r_int
id|APICRegSel
suffix:semicolon
multiline_comment|/* APIC Register Select */
DECL|member|reserved0
r_volatile
r_int
r_int
id|reserved0
suffix:semicolon
DECL|member|APICWinReg
r_volatile
r_int
r_int
id|APICWinReg
suffix:semicolon
multiline_comment|/* APIC Window Register */
DECL|member|reserved1
r_volatile
r_int
r_int
id|reserved1
suffix:semicolon
DECL|member|InMsgReg0
r_volatile
r_int
r_int
id|InMsgReg0
suffix:semicolon
multiline_comment|/* inbound message register 0 */
DECL|member|InMsgReg1
r_volatile
r_int
r_int
id|InMsgReg1
suffix:semicolon
multiline_comment|/* inbound message register 1 */
DECL|member|OutMsgReg0
r_volatile
r_int
r_int
id|OutMsgReg0
suffix:semicolon
multiline_comment|/* outbound message register 0 */
DECL|member|OutMsgReg1
r_volatile
r_int
r_int
id|OutMsgReg1
suffix:semicolon
multiline_comment|/* outbound message register 1 */
DECL|member|InDoorReg
r_volatile
r_int
r_int
id|InDoorReg
suffix:semicolon
multiline_comment|/* inbound doorbell register */
DECL|member|InIntStat
r_volatile
r_int
r_int
id|InIntStat
suffix:semicolon
multiline_comment|/* inbound interrupt status register */
DECL|member|InIntMask
r_volatile
r_int
r_int
id|InIntMask
suffix:semicolon
multiline_comment|/* inbound interrupt mask register */
DECL|member|OutDoorReg
r_volatile
r_int
r_int
id|OutDoorReg
suffix:semicolon
multiline_comment|/* outbound doorbell register */
DECL|member|OutIntStat
r_volatile
r_int
r_int
id|OutIntStat
suffix:semicolon
multiline_comment|/* outbound interrupt status register */
DECL|member|OutIntMask
r_volatile
r_int
r_int
id|OutIntMask
suffix:semicolon
multiline_comment|/* outbound interrupt mask register */
DECL|member|reserved2
r_volatile
r_int
r_int
id|reserved2
suffix:semicolon
DECL|member|reserved3
r_volatile
r_int
r_int
id|reserved3
suffix:semicolon
DECL|member|InQueue
r_volatile
r_int
r_int
id|InQueue
suffix:semicolon
multiline_comment|/* inbound queue port */
DECL|member|OutQueue
r_volatile
r_int
r_int
id|OutQueue
suffix:semicolon
multiline_comment|/* outbound queue port */
DECL|member|reserved4
r_volatile
r_int
r_int
id|reserved4
suffix:semicolon
DECL|member|reserver5
r_volatile
r_int
r_int
id|reserver5
suffix:semicolon
multiline_comment|/* RedCreek extension */
DECL|member|EtherMacLow
r_volatile
r_int
r_int
id|EtherMacLow
suffix:semicolon
DECL|member|EtherMacHi
r_volatile
r_int
r_int
id|EtherMacHi
suffix:semicolon
DECL|member|IPaddr
r_volatile
r_int
r_int
id|IPaddr
suffix:semicolon
DECL|member|IPmask
r_volatile
r_int
r_int
id|IPmask
suffix:semicolon
DECL|typedef|PATU
)brace
op_star
id|PATU
suffix:semicolon
multiline_comment|/* &n; ** typedef PAB&n; **&n; ** PCI Adapter Block - holds instance specific information.&n; */
r_typedef
r_struct
(brace
DECL|member|p_atu
id|PATU
id|p_atu
suffix:semicolon
multiline_comment|/* ptr to  ATU register block */
DECL|member|pPci45LinBaseAddr
id|PU8
id|pPci45LinBaseAddr
suffix:semicolon
DECL|member|pLinOutMsgBlock
id|PU8
id|pLinOutMsgBlock
suffix:semicolon
DECL|member|outMsgBlockPhyAddr
id|U32
id|outMsgBlockPhyAddr
suffix:semicolon
DECL|member|pTransCallbackFunc
id|PFNTXCALLBACK
id|pTransCallbackFunc
suffix:semicolon
DECL|member|pRecvCallbackFunc
id|PFNRXCALLBACK
id|pRecvCallbackFunc
suffix:semicolon
DECL|member|pRebootCallbackFunc
id|PFNCALLBACK
id|pRebootCallbackFunc
suffix:semicolon
DECL|member|pCallbackFunc
id|PFNCALLBACK
id|pCallbackFunc
suffix:semicolon
DECL|member|IOPState
id|U16
id|IOPState
suffix:semicolon
DECL|member|InboundMFrameSize
id|U16
id|InboundMFrameSize
suffix:semicolon
DECL|typedef|PPAB
)brace
op_star
id|PPAB
suffix:semicolon
multiline_comment|/*&n; * Driver Private Area, DPA.&n; */
r_typedef
r_struct
(brace
DECL|member|id
id|U8
id|id
suffix:semicolon
multiline_comment|/* the AdapterID */
multiline_comment|/* These two field are basically for the RCioctl function.&n;     * I could not determine if they could be avoided. (RAA)*/
DECL|member|pci_addr
id|U32
id|pci_addr
suffix:semicolon
multiline_comment|/* the pci address of the adapter */
DECL|member|pci_addr_len
id|U32
id|pci_addr_len
suffix:semicolon
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
multiline_comment|/*  timer */
DECL|member|stats
r_struct
id|net_device_stats
id|stats
suffix:semicolon
multiline_comment|/* the statistics structure */
DECL|member|numOutRcvBuffers
r_int
r_int
id|numOutRcvBuffers
suffix:semicolon
multiline_comment|/* number of outstanding receive buffers*/
DECL|member|shutdown
r_int
r_char
id|shutdown
suffix:semicolon
DECL|member|reboot
r_int
r_char
id|reboot
suffix:semicolon
DECL|member|nexus
r_int
r_char
id|nexus
suffix:semicolon
DECL|member|msgbuf
id|PU8
id|msgbuf
suffix:semicolon
multiline_comment|/* Pointer to Lan Api Private Area */
DECL|member|PLanApiPA
id|PU8
id|PLanApiPA
suffix:semicolon
multiline_comment|/* Pointer to Lan Api Private Area (aligned) */
DECL|member|pPab
id|PPAB
id|pPab
suffix:semicolon
multiline_comment|/* Pointer to the PCI Adapter Block */
DECL|typedef|PDPA
)brace
op_star
id|PDPA
suffix:semicolon
multiline_comment|/* PCI/45 Configuration space values */
DECL|macro|RC_PCI45_VENDOR_ID
mdefine_line|#define RC_PCI45_VENDOR_ID  0x4916
DECL|macro|RC_PCI45_DEVICE_ID
mdefine_line|#define RC_PCI45_DEVICE_ID  0x1960
multiline_comment|/* RedCreek API function return values */
DECL|macro|RC_RTN_NO_ERROR
mdefine_line|#define RC_RTN_NO_ERROR             0
DECL|macro|RC_RTN_I2O_NOT_INIT
mdefine_line|#define RC_RTN_I2O_NOT_INIT         1
DECL|macro|RC_RTN_FREE_Q_EMPTY
mdefine_line|#define RC_RTN_FREE_Q_EMPTY         2
DECL|macro|RC_RTN_TCB_ERROR
mdefine_line|#define RC_RTN_TCB_ERROR            3
DECL|macro|RC_RTN_TRANSACTION_ERROR
mdefine_line|#define RC_RTN_TRANSACTION_ERROR    4
DECL|macro|RC_RTN_ADAPTER_ALREADY_INIT
mdefine_line|#define RC_RTN_ADAPTER_ALREADY_INIT 5
DECL|macro|RC_RTN_MALLOC_ERROR
mdefine_line|#define RC_RTN_MALLOC_ERROR         6
DECL|macro|RC_RTN_ADPTR_NOT_REGISTERED
mdefine_line|#define RC_RTN_ADPTR_NOT_REGISTERED 7
DECL|macro|RC_RTN_MSG_REPLY_TIMEOUT
mdefine_line|#define RC_RTN_MSG_REPLY_TIMEOUT    8
DECL|macro|RC_RTN_NO_I2O_STATUS
mdefine_line|#define RC_RTN_NO_I2O_STATUS        9
DECL|macro|RC_RTN_NO_FIRM_VER
mdefine_line|#define RC_RTN_NO_FIRM_VER         10
DECL|macro|RC_RTN_NO_LINK_SPEED
mdefine_line|#define RC_RTN_NO_LINK_SPEED       11
multiline_comment|/* Driver capability flags */
DECL|macro|WARM_REBOOT_CAPABLE
mdefine_line|#define WARM_REBOOT_CAPABLE      0x01
multiline_comment|/*&n;** Status - Transmit and Receive callback status word &n;**&n;** A 32 bit Status is returned to the TX and RX callback functions.  This value&n;** contains both the reply status and the detailed status as follows:&n;**&n;**  32    24     16            0&n;**  +------+------+------------+&n;**  | Reply|      |  Detailed  |&n;**  |Status|   0  |   Status   |&n;**  +------+------+------------+&n;**&n;** Reply Status and Detailed Status of zero indicates No Errors.&n;*/
multiline_comment|/* reply message status defines */
DECL|macro|I2O_REPLY_STATUS_SUCCESS
mdefine_line|#define    I2O_REPLY_STATUS_SUCCESS                    0x00
DECL|macro|I2O_REPLY_STATUS_ABORT_NO_DATA_TRANSFER
mdefine_line|#define    I2O_REPLY_STATUS_ABORT_NO_DATA_TRANSFER     0x02
DECL|macro|I2O_REPLY_STATUS_TRANSACTION_ERROR
mdefine_line|#define    I2O_REPLY_STATUS_TRANSACTION_ERROR          0x0A
multiline_comment|/* DetailedStatusCode defines */
DECL|macro|I2O_LAN_DSC_SUCCESS
mdefine_line|#define    I2O_LAN_DSC_SUCCESS                         0x0000
DECL|macro|I2O_LAN_DSC_DEVICE_FAILURE
mdefine_line|#define    I2O_LAN_DSC_DEVICE_FAILURE                  0x0001
DECL|macro|I2O_LAN_DSC_DESTINATION_NOT_FOUND
mdefine_line|#define    I2O_LAN_DSC_DESTINATION_NOT_FOUND           0x0002
DECL|macro|I2O_LAN_DSC_TRANSMIT_ERROR
mdefine_line|#define    I2O_LAN_DSC_TRANSMIT_ERROR                  0x0003
DECL|macro|I2O_LAN_DSC_TRANSMIT_ABORTED
mdefine_line|#define    I2O_LAN_DSC_TRANSMIT_ABORTED                0x0004
DECL|macro|I2O_LAN_DSC_RECEIVE_ERROR
mdefine_line|#define    I2O_LAN_DSC_RECEIVE_ERROR                   0x0005
DECL|macro|I2O_LAN_DSC_RECEIVE_ABORTED
mdefine_line|#define    I2O_LAN_DSC_RECEIVE_ABORTED                 0x0006
DECL|macro|I2O_LAN_DSC_DMA_ERROR
mdefine_line|#define    I2O_LAN_DSC_DMA_ERROR                       0x0007
DECL|macro|I2O_LAN_DSC_BAD_PACKET_DETECTED
mdefine_line|#define    I2O_LAN_DSC_BAD_PACKET_DETECTED             0x0008
DECL|macro|I2O_LAN_DSC_OUT_OF_MEMORY
mdefine_line|#define    I2O_LAN_DSC_OUT_OF_MEMORY                   0x0009
DECL|macro|I2O_LAN_DSC_BUCKET_OVERRUN
mdefine_line|#define    I2O_LAN_DSC_BUCKET_OVERRUN                  0x000A
DECL|macro|I2O_LAN_DSC_IOP_INTERNAL_ERROR
mdefine_line|#define    I2O_LAN_DSC_IOP_INTERNAL_ERROR              0x000B
DECL|macro|I2O_LAN_DSC_CANCELED
mdefine_line|#define    I2O_LAN_DSC_CANCELED                        0x000C
DECL|macro|I2O_LAN_DSC_INVALID_TRANSACTION_CONTEXT
mdefine_line|#define    I2O_LAN_DSC_INVALID_TRANSACTION_CONTEXT     0x000D
DECL|macro|I2O_LAN_DSC_DESTINATION_ADDRESS_DETECTED
mdefine_line|#define    I2O_LAN_DSC_DESTINATION_ADDRESS_DETECTED    0x000E
DECL|macro|I2O_LAN_DSC_DESTINATION_ADDRESS_OMITTED
mdefine_line|#define    I2O_LAN_DSC_DESTINATION_ADDRESS_OMITTED     0x000F
DECL|macro|I2O_LAN_DSC_PARTIAL_PACKET_RETURNED
mdefine_line|#define    I2O_LAN_DSC_PARTIAL_PACKET_RETURNED         0x0010
multiline_comment|/*&n;** Packet Description Block   (Received packets)&n;**&n;** A pointer to this block structure is returned to the ReceiveCallback &n;** function.  It contains the list of packet buffers which have either been&n;** filled with a packet or returned to host due to a LANReset function. &n;** Currently there will only be one packet per receive bucket (buffer) posted. &n;**&n;**   32   24               0     &n;**  +-----------------------+  -&bslash;&n;**  |   Buffer 1 Context    |    &bslash;&n;**  +-----------------------+     &bslash;&n;**  |      0xC0000000       |     / First Bucket Descriptor&n;**  +-----+-----------------+    /&n;**  |  0  | packet 1 length |   / &n;**  +-----------------------+  -&bslash;&n;**  |   Buffer 2 Context    |    &bslash;&n;**  +-----------------------+     &bslash;&n;**  |      0xC0000000       |     / Second Bucket Descriptor&n;**  +-----+-----------------+    /&n;**  |  0  | packet 2 length |   / &n;**  +-----+-----------------+  -&n;**  |         ...           |  ----- more bucket descriptors&n;**  +-----------------------+  -&bslash;&n;**  |   Buffer n Context    |    &bslash;&n;**  +-----------------------+     &bslash;&n;**  |      0xC0000000       |     / Last Bucket Descriptor&n;**  +-----+-----------------+    /&n;**  |  0  | packet n length |   / &n;**  +-----+-----------------+  -&n;**&n;** Buffer Context values are those given to adapter in the TCB on calls to&n;** RCPostRecvBuffers().&n;**  &n;*/
multiline_comment|/*&n;** Transaction Control Block (TCB) structure&n;**&n;** A structure like this is filled in by the user and passed by reference to &n;** RCI2OSendPacket() and RCPostRecvBuffers() functions.  Minimum size is five&n;** 32-bit words for one buffer with one segment descriptor.  &n;** MAX_NMBR_POST_BUFFERS_PER_MSG defines the maximum single segment buffers&n;** that can be described in a given TCB.&n;**&n;**   32                    0&n;**  +-----------------------+&n;**  |   Buffer Count        |  Number of buffers in the TCB&n;**  +-----------------------+&n;**  |   Buffer 1 Context    |  first buffer reference&n;**  +-----------------------+&n;**  |   Buffer 1 Seg Count  |  number of segments in buffer&n;**  +-----------------------+&n;**  |   Buffer 1 Seg Desc 1 |  first segment descriptor (size, physical address)&n;**  +-----------------------+&n;**  |         ...           |  more segment descriptors (size, physical address)&n;**  +-----------------------+&n;**  |   Buffer 1 Seg Desc n |  last segment descriptor (size, physical address)&n;**  +-----------------------+&n;**  |   Buffer 2 Context    |  second buffer reference&n;**  +-----------------------+&n;**  |   Buffer 2 Seg Count  |  number of segments in buffer&n;**  +-----------------------+&n;**  |   Buffer 2 Seg Desc 1 |  segment descriptor (size, physical address)&n;**  +-----------------------+&n;**  |         ...           |  more segment descriptors (size, physical address)&n;**  +-----------------------+&n;**  |   Buffer 2 Seg Desc n |&n;**  +-----------------------+&n;**  |         ...           |  more buffer descriptor blocks ...&n;**  +-----------------------+&n;**  |   Buffer n Context    |&n;**  +-----------------------+&n;**  |   Buffer n Seg Count  |&n;**  +-----------------------+&n;**  |   Buffer n Seg Desc 1 |&n;**  +-----------------------+&n;**  |         ...           |&n;**  +-----------------------+&n;**  |   Buffer n Seg Desc n |&n;**  +-----------------------+&n;**&n;**&n;** A TCB for one contigous packet buffer would look like the following:&n;**&n;**   32                    0&n;**  +-----------------------+&n;**  |         1             |  one buffer in the TCB&n;**  +-----------------------+&n;**  |  &lt;user&squot;s Context&gt;     |  user&squot;s buffer reference&n;**  +-----------------------+&n;**  |         1             |  one segment buffer&n;**  +-----------------------+                            _&n;**  |    &lt;buffer size&gt;      |  size                       &bslash; &n;**  +-----------------------+                              &bslash; segment descriptor&n;**  |  &lt;physical address&gt;   |  physical address of buffer  /&n;**  +-----------------------+                            _/&n;**&n;*/
multiline_comment|/* Buffer Segment Descriptor */
r_typedef
r_struct
(brace
DECL|member|size
id|U32
id|size
suffix:semicolon
DECL|member|phyAddress
id|U32
id|phyAddress
suffix:semicolon
)brace
DECL|typedef|BSD
DECL|typedef|PBSD
id|BSD
comma
op_star
id|PBSD
suffix:semicolon
DECL|typedef|PRCTCB
r_typedef
id|PU32
id|PRCTCB
suffix:semicolon
multiline_comment|/*&n;** -------------------------------------------------------------------------&n;** Exported functions comprising the API to the LAN I2O message transport layer&n;** -------------------------------------------------------------------------&n;*/
multiline_comment|/*&n; ** InitRCI2OMsgLayer()&n; ** &n; ** Called once prior to using the I2O LAN message transport layer.  User &n; ** provides both the physical and virual address of a locked page buffer &n; ** that is used as a private buffer for the RedCreek I2O message&n; ** transport layer.  This buffer must be a contigous memory block of a &n; ** minimum of 16K bytes and long word aligned.  The user also must provide&n; ** the base address of the RedCreek PCI adapter assigned by BIOS or operating&n; ** system.  &n; **&n; ** Inputs:  dev - the net_device struct for the device.&n; **          TransmitCallbackFunction - address of user&squot;s TX callback function&n; **          ReceiveCallbackFunction  - address of user&squot;s RX callback function&n; **          RebootCallbackFunction  - address of user&squot;s reboot callback function&n; **&n; */
id|RC_RETURN
id|RCInitI2OMsgLayer
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
id|PFNTXCALLBACK
id|TransmitCallbackFunction
comma
id|PFNRXCALLBACK
id|ReceiveCallbackFunction
comma
id|PFNCALLBACK
id|RebootCallbackFunction
)paren
suffix:semicolon
multiline_comment|/*&n; ** RCSetRavlinIPandMask()&n; **&n; ** Set the Ravlin 45/PCI cards IP address and network mask.&n; **&n; ** IP address and mask must be in network byte order.&n; ** For example, IP address 1.2.3.4 and mask 255.255.255.0 would be&n; ** 0x04030201 and 0x00FFFFFF on a little endian machine.&n; **&n; */
id|RC_RETURN
id|RCSetRavlinIPandMask
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
id|U32
id|ipAddr
comma
id|U32
id|netMask
)paren
suffix:semicolon
multiline_comment|/*&n;** =========================================================================&n;** RCGetRavlinIPandMask()&n;**&n;** get the IP address and MASK from the card&n;** &n;** =========================================================================&n;*/
id|RC_RETURN
id|RCGetRavlinIPandMask
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
id|PU32
id|pIpAddr
comma
id|PU32
id|pNetMask
comma
id|PFNWAITCALLBACK
id|WaitCallback
)paren
suffix:semicolon
multiline_comment|/* &n; ** RCProcI2OMsgQ()&n; ** &n; ** Called from user&squot;s polling loop or Interrupt Service Routine for a PCI &n; ** interrupt from the RedCreek PCI adapter.  User responsible for determining&n; ** and hooking the PCI interrupt. This function will call the registered&n; ** callback functions, TransmitCallbackFunction or ReceiveCallbackFunction,&n; ** if a TX or RX transaction has completed.&n; */
r_void
id|RCProcI2OMsgQ
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/*&n; ** Disable and Enable I2O interrupts.  I2O interrupts are enabled at Init time&n; ** but can be disabled and re-enabled through these two function calls.&n; ** Packets will still be put into any posted received buffers and packets will&n; ** be sent through RCI2OSendPacket() functions.  Disabling I2O interrupts&n; ** will prevent hardware interrupt to host even though the outbound I2O msg&n; ** queue is not emtpy.&n; */
id|RC_RETURN
id|RCEnableI2OInterrupts
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
id|RC_RETURN
id|RCDisableI2OInterrupts
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/* &n; ** RCPostRecvBuffers()&n; ** &n; ** Post user&squot;s page locked buffers for use by the PCI adapter to&n; ** return ethernet packets received from the LAN.  Transaction Control Block,&n; ** provided by user, contains buffer descriptor(s) which includes a buffer&n; ** context number along with buffer size and physical address.  See TCB above.&n; ** The buffer context and actual packet length are returned to the &n; ** ReceiveCallbackFunction when packets have been received.  Buffers posted&n; ** to the RedCreek adapter are considered owned by the adapter until the&n; ** context is return to user through the ReceiveCallbackFunction.&n; */
id|RC_RETURN
id|RCPostRecvBuffers
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
id|PRCTCB
id|pTransactionCtrlBlock
)paren
suffix:semicolon
DECL|macro|MAX_NMBR_POST_BUFFERS_PER_MSG
mdefine_line|#define MAX_NMBR_POST_BUFFERS_PER_MSG 32
multiline_comment|/*&n; ** RCI2OSendPacket()&n; ** &n; ** Send user&squot;s ethernet packet from a locked page buffer.  &n; ** Packet must have full MAC header, however without a CRC.  &n; ** Initiator context is a user provided value that is returned &n; ** to the TransmitCallbackFunction when packet buffer is free.&n; ** Transmit buffer are considered owned by the adapter until context&squot;s&n; ** returned to user through the TransmitCallbackFunction.&n; */
id|RC_RETURN
id|RCI2OSendPacket
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
id|U32
id|context
comma
id|PRCTCB
id|pTransactionCtrlBlock
)paren
suffix:semicolon
multiline_comment|/* Ethernet Link Statistics structure */
DECL|struct|tag_RC_link_stats
r_typedef
r_struct
id|tag_RC_link_stats
(brace
DECL|member|TX_good
id|U32
id|TX_good
suffix:semicolon
multiline_comment|/* good transmit frames */
DECL|member|TX_maxcol
id|U32
id|TX_maxcol
suffix:semicolon
multiline_comment|/* frames not TX due to MAX collisions */
DECL|member|TX_latecol
id|U32
id|TX_latecol
suffix:semicolon
multiline_comment|/* frames not TX due to late collisions */
DECL|member|TX_urun
id|U32
id|TX_urun
suffix:semicolon
multiline_comment|/* frames not TX due to DMA underrun */
DECL|member|TX_crs
id|U32
id|TX_crs
suffix:semicolon
multiline_comment|/* frames TX with lost carrier sense */
DECL|member|TX_def
id|U32
id|TX_def
suffix:semicolon
multiline_comment|/* frames deferred due to activity on link */
DECL|member|TX_singlecol
id|U32
id|TX_singlecol
suffix:semicolon
multiline_comment|/* frames TX with one and only on collision */
DECL|member|TX_multcol
id|U32
id|TX_multcol
suffix:semicolon
multiline_comment|/* frames TX with more than one collision */
DECL|member|TX_totcol
id|U32
id|TX_totcol
suffix:semicolon
multiline_comment|/* total collisions detected during TX */
DECL|member|Rcv_good
id|U32
id|Rcv_good
suffix:semicolon
multiline_comment|/* good frames received */
DECL|member|Rcv_CRCerr
id|U32
id|Rcv_CRCerr
suffix:semicolon
multiline_comment|/* frames RX and discarded with CRC errors */
DECL|member|Rcv_alignerr
id|U32
id|Rcv_alignerr
suffix:semicolon
multiline_comment|/* frames RX with alignment and CRC errors */
DECL|member|Rcv_reserr
id|U32
id|Rcv_reserr
suffix:semicolon
multiline_comment|/* good frames discarded due to no RX buffer */
DECL|member|Rcv_orun
id|U32
id|Rcv_orun
suffix:semicolon
multiline_comment|/* RX frames lost due to FIFO overrun */
DECL|member|Rcv_cdt
id|U32
id|Rcv_cdt
suffix:semicolon
multiline_comment|/* RX frames with collision during RX */
DECL|member|Rcv_runt
id|U32
id|Rcv_runt
suffix:semicolon
multiline_comment|/* RX frames shorter than 64 bytes */
)brace
DECL|typedef|RCLINKSTATS
DECL|typedef|P_RCLINKSTATS
id|RCLINKSTATS
comma
op_star
id|P_RCLINKSTATS
suffix:semicolon
multiline_comment|/*&n; ** RCGetLinkStatistics()&n; **&n; ** Returns link statistics in user&squot;s structure at address StatsReturnAddr&n; ** If given, not NULL, the function WaitCallback is called during the wait&n; ** loop while waiting for the adapter to respond.&n; */
id|RC_RETURN
id|RCGetLinkStatistics
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
id|P_RCLINKSTATS
id|StatsReturnAddr
comma
id|PFNWAITCALLBACK
id|WaitCallback
)paren
suffix:semicolon
multiline_comment|/*&n; ** RCGetLinkStatus()&n; **&n; ** Return link status, up or down, to user&squot;s location addressed by ReturnAddr.&n; ** If given, not NULL, the function WaitCallback is called during the wait&n; ** loop while waiting for the adapter to respond.&n; */
id|RC_RETURN
id|RCGetLinkStatus
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
id|PU32
id|pReturnStatus
comma
id|PFNWAITCALLBACK
id|WaitCallback
)paren
suffix:semicolon
multiline_comment|/* Link Status defines - value returned in pReturnStatus */
DECL|macro|RC_LAN_LINK_STATUS_DOWN
mdefine_line|#define RC_LAN_LINK_STATUS_DOWN     0
DECL|macro|RC_LAN_LINK_STATUS_UP
mdefine_line|#define RC_LAN_LINK_STATUS_UP       1
multiline_comment|/*&n; ** RCGetMAC()&n; **&n; ** Get the current MAC address assigned to user.  RedCreek Ravlin 45/PCI &n; ** has two MAC addresses.  One which is private to the PCI Card, and &n; ** another MAC which is given to the user as its link layer MAC address. The&n; ** adapter runs in promiscous mode because of the dual address requirement.&n; ** The MAC address is returned to the unsigned char array pointer to by mac.&n; */
id|RC_RETURN
id|RCGetMAC
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
id|PFNWAITCALLBACK
id|WaitCallback
)paren
suffix:semicolon
multiline_comment|/*&n; ** RCSetMAC()&n; **&n; ** Set a new user port MAC address.  This address will be returned on&n; ** subsequent RCGetMAC() calls.&n; */
id|RC_RETURN
id|RCSetMAC
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
id|PU8
id|mac
)paren
suffix:semicolon
multiline_comment|/*&n; ** RCSetLinkSpeed()&n; **&n; ** set adapter&squot;s link speed based on given input code.&n; */
id|RC_RETURN
id|RCSetLinkSpeed
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
id|U16
id|LinkSpeedCode
)paren
suffix:semicolon
multiline_comment|/* Set link speed codes */
DECL|macro|LNK_SPD_AUTO_NEG_NWAY
mdefine_line|#define LNK_SPD_AUTO_NEG_NWAY   0
DECL|macro|LNK_SPD_100MB_FULL
mdefine_line|#define LNK_SPD_100MB_FULL      1
DECL|macro|LNK_SPD_100MB_HALF
mdefine_line|#define LNK_SPD_100MB_HALF      2
DECL|macro|LNK_SPD_10MB_FULL
mdefine_line|#define LNK_SPD_10MB_FULL       3
DECL|macro|LNK_SPD_10MB_HALF
mdefine_line|#define LNK_SPD_10MB_HALF       4
multiline_comment|/*&n; ** RCGetLinkSpeed()&n; **&n; ** Return link speed code.&n; */
multiline_comment|/* Return link speed codes */
DECL|macro|LNK_SPD_UNKNOWN
mdefine_line|#define LNK_SPD_UNKNOWN         0
DECL|macro|LNK_SPD_100MB_FULL
mdefine_line|#define LNK_SPD_100MB_FULL      1
DECL|macro|LNK_SPD_100MB_HALF
mdefine_line|#define LNK_SPD_100MB_HALF      2
DECL|macro|LNK_SPD_10MB_FULL
mdefine_line|#define LNK_SPD_10MB_FULL       3
DECL|macro|LNK_SPD_10MB_HALF
mdefine_line|#define LNK_SPD_10MB_HALF       4
id|RC_RETURN
id|RCGetLinkSpeed
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
id|PU32
id|pLinkSpeedCode
comma
id|PFNWAITCALLBACK
id|WaitCallback
)paren
suffix:semicolon
multiline_comment|/*&n;** =========================================================================&n;** RCSetPromiscuousMode(struct net_device *dev, U16 Mode)&n;**&n;** Defined values for Mode:&n;**  0 - turn off promiscuous mode&n;**  1 - turn on  promiscuous mode&n;**&n;** =========================================================================&n;*/
DECL|macro|PROMISCUOUS_MODE_OFF
mdefine_line|#define PROMISCUOUS_MODE_OFF 0
DECL|macro|PROMISCUOUS_MODE_ON
mdefine_line|#define PROMISCUOUS_MODE_ON  1
id|RC_RETURN
id|RCSetPromiscuousMode
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
id|U16
id|Mode
)paren
suffix:semicolon
multiline_comment|/*&n;** =========================================================================&n;** RCGetPromiscuousMode(struct net_device *dev, PU32 pMode, PFNWAITCALLBACK WaitCallback)&n;**&n;** get promiscuous mode setting&n;**&n;** Possible return values placed in pMode:&n;**  0 = promisuous mode not set&n;**  1 = promisuous mode is set&n;**&n;** =========================================================================&n;*/
id|RC_RETURN
id|RCGetPromiscuousMode
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
id|PU32
id|pMode
comma
id|PFNWAITCALLBACK
id|WaitCallback
)paren
suffix:semicolon
multiline_comment|/*&n;** =========================================================================&n;** RCSetBroadcastMode(struct net_device *dev, U16 Mode)&n;**&n;** Defined values for Mode:&n;**  0 - turn off promiscuous mode&n;**  1 - turn on  promiscuous mode&n;**&n;** =========================================================================&n;*/
DECL|macro|BROADCAST_MODE_OFF
mdefine_line|#define BROADCAST_MODE_OFF 0
DECL|macro|BROADCAST_MODE_ON
mdefine_line|#define BROADCAST_MODE_ON  1
id|RC_RETURN
id|RCSetBroadcastMode
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
id|U16
id|Mode
)paren
suffix:semicolon
multiline_comment|/*&n;** =========================================================================&n;** RCGetBroadcastMode(struct net_device *dev, PU32 pMode, PFNWAITCALLBACK WaitCallback)&n;**&n;** get broadcast mode setting&n;**&n;** Possible return values placed in pMode:&n;**  0 = broadcast mode not set&n;**  1 = broadcast mode is set&n;**&n;** =========================================================================&n;*/
id|RC_RETURN
id|RCGetBroadcastMode
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
id|PU32
id|pMode
comma
id|PFNWAITCALLBACK
id|WaitCallback
)paren
suffix:semicolon
multiline_comment|/*&n;** =========================================================================&n;** RCReportDriverCapability(struct net_device *dev, U32 capability)&n;**&n;** Currently defined bits:&n;** WARM_REBOOT_CAPABLE   0x01&n;**&n;** =========================================================================&n;*/
id|RC_RETURN
id|RCReportDriverCapability
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
id|U32
id|capability
)paren
suffix:semicolon
multiline_comment|/*&n;** RCGetFirmwareVer()&n;**&n;** Return firmware version in the form &quot;SoftwareVersion : Bt BootVersion&quot;&n;**&n;** WARNING: user&squot;s space pointed to by pFirmString should be at least 60 bytes.&n;*/
id|RC_RETURN
id|RCGetFirmwareVer
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
id|PU8
id|pFirmString
comma
id|PFNWAITCALLBACK
id|WaitCallback
)paren
suffix:semicolon
multiline_comment|/*&n;** ----------------------------------------------&n;** LAN adapter Reset and Shutdown functions&n;** ----------------------------------------------&n;*/
multiline_comment|/* resource flag bit assignments for RCResetLANCard() &amp; RCShutdownLANCard() */
DECL|macro|RC_RESOURCE_RETURN_POSTED_RX_BUCKETS
mdefine_line|#define RC_RESOURCE_RETURN_POSTED_RX_BUCKETS  0x0001 
DECL|macro|RC_RESOURCE_RETURN_PEND_TX_BUFFERS
mdefine_line|#define RC_RESOURCE_RETURN_PEND_TX_BUFFERS    0x0002
multiline_comment|/*&n; ** RCResetLANCard()&n; **&n; ** Reset LAN card operation.  Causes a software reset of the ethernet&n; ** controller and restarts the command and receive units. Depending on &n; ** the ResourceFlags given, the buffers are either returned to the&n; ** host with reply status of I2O_REPLY_STATUS_ABORT_NO_DATA_TRANSFER and&n; ** detailed status of I2O_LAN_DSC_CANCELED (new receive buffers must be&n; ** posted after issuing this) OR the buffers are kept and reused by&n; ** the ethernet controller. If CallbackFunction is not NULL, the function&n; ** will be called when the reset is complete.  If the CallbackFunction is&n; ** NULL,a 1 will be put into the ReturnAddr after waiting for the reset &n; ** to complete (please disable I2O interrupts during this method).&n; ** Any outstanding transmit or receive buffers that are complete will be&n; ** returned via the normal reply messages before the requested resource&n; ** buffers are returned.&n; ** A call to RCPostRecvBuffers() is needed to return the ethernet to full&n; ** operation if the receive buffers were returned during LANReset.&n; ** Note: The IOP status is not affected by a LAN reset.&n; */
id|RC_RETURN
id|RCResetLANCard
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
id|U16
id|ResourceFlags
comma
id|PU32
id|ReturnAddr
comma
id|PFNCALLBACK
id|CallbackFunction
)paren
suffix:semicolon
multiline_comment|/*&n; ** RCShutdownLANCard()&n; **&n; ** Shutdown LAN card operation and put into an idle (suspended) state.&n; ** The LAN card is restarted with RCResetLANCard() function.&n; ** Depending on the ResourceFlags given, the buffers are either returned &n; ** to the host with reply status of I2O_REPLY_STATUS_ABORT_NO_DATA_TRANSFER &n; ** and detailed status of I2O_LAN_DSC_CANCELED (new receive buffers must be&n; ** posted after issuing this) OR the buffers are kept and reused by&n; ** the ethernet controller. If CallbackFunction is not NULL, the function&n; ** will be called when the reset is complete.  If the CallbackFunction is&n; ** NULL,a 1 will be put into the ReturnAddr after waiting for the reset &n; ** to complete (please disable I2O interrupts during this method).&n; ** Any outstanding transmit or receive buffers that are complete will be&n; ** returned via the normal reply messages before the requested resource&n; ** buffers are returned.&n; ** Note: The IOP status is not affected by a LAN shutdown.&n; */
id|RC_RETURN
id|RCShutdownLANCard
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
id|U16
id|ResourceFlags
comma
id|PU32
id|ReturnAddr
comma
id|PFNCALLBACK
id|CallbackFunction
)paren
suffix:semicolon
multiline_comment|/*&n; ** RCResetIOP();&n; **     Initializes IOPState to I2O_IOP_STATE_RESET.&n; **     Stops access to outbound message Q.&n; **     Discards any outstanding transmit or posted receive buffers.&n; **     Clears outbound message Q. &n; */
id|RC_RETURN
id|RCResetIOP
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
macro_line|#endif /* RCLANMTL_H */
eof
