multiline_comment|/******************************************************************************&n;             Device driver for Interphase ATM PCI adapter cards &n;                    Author: Peter Wang  &lt;pwang@iphase.com&gt;            &n;                   Interphase Corporation  &lt;www.iphase.com&gt;           &n;                               Version: 1.0   &n;               iphase.h:  This is the header file for iphase.c. &n;*******************************************************************************&n;      &n;      This software may be used and distributed according to the terms&n;      of the GNU Public License (GPL), incorporated herein by reference.&n;      Drivers based on this skeleton fall under the GPL and must retain&n;      the authorship (implicit copyright) notice.&n;&n;      This program is distributed in the hope that it will be useful, but&n;      WITHOUT ANY WARRANTY; without even the implied warranty of&n;      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU&n;      General Public License for more details.&n;      &n;      Modified from an incomplete driver for Interphase 5575 1KVC 1M card which &n;      was originally written by Monalisa Agrawal at UNH. Now this driver &n;      supports a variety of varients of Interphase ATM PCI (i)Chip adapter &n;      card family (See www.iphase.com/products/ClassSheet.cfm?ClassID=ATM) &n;      in terms of PHY type, the size of control memory and the size of &n;      packet memory. The followings are the change log and history:&n;     &n;          Bugfix the Mona&squot;s UBR driver.&n;          Modify the basic memory allocation and dma logic.&n;          Port the driver to the latest kernel from 2.0.46.&n;          Complete the ABR logic of the driver, and added the ABR work-&n;              around for the hardware anormalies.&n;          Add the CBR support.&n;&t;  Add the flow control logic to the driver to allow rate-limit VC.&n;          Add 4K VC support to the board with 512K control memory.&n;          Add the support of all the variants of the Interphase ATM PCI &n;          (i)Chip adapter cards including x575 (155M OC3 and UTP155), x525&n;          (25M UTP25) and x531 (DS3 and E3).&n;          Add SMP support.&n;&n;      Support and updates available at: ftp://ftp.iphase.com/pub/atm&n;&n;*******************************************************************************/
macro_line|#ifndef IPHASE_H  
DECL|macro|IPHASE_H
mdefine_line|#define IPHASE_H  
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/************************ IADBG DEFINE *********************************/
multiline_comment|/* IADebugFlag Bit Map */
DECL|macro|IF_IADBG_INIT_ADAPTER
mdefine_line|#define IF_IADBG_INIT_ADAPTER   0x00000001        
singleline_comment|// init adapter info
DECL|macro|IF_IADBG_TX
mdefine_line|#define IF_IADBG_TX             0x00000002        
singleline_comment|// debug TX
DECL|macro|IF_IADBG_RX
mdefine_line|#define IF_IADBG_RX             0x00000004        
singleline_comment|// debug RX
DECL|macro|IF_IADBG_QUERY_INFO
mdefine_line|#define IF_IADBG_QUERY_INFO     0x00000008        
singleline_comment|// debug Request call
DECL|macro|IF_IADBG_SHUTDOWN
mdefine_line|#define IF_IADBG_SHUTDOWN       0x00000010        
singleline_comment|// debug shutdown event
DECL|macro|IF_IADBG_INTR
mdefine_line|#define IF_IADBG_INTR           0x00000020        
singleline_comment|// debug interrupt DPC
DECL|macro|IF_IADBG_TXPKT
mdefine_line|#define IF_IADBG_TXPKT          0x00000040  &t;  
singleline_comment|// debug TX PKT
DECL|macro|IF_IADBG_RXPKT
mdefine_line|#define IF_IADBG_RXPKT          0x00000080  &t;  
singleline_comment|// debug RX PKT
DECL|macro|IF_IADBG_ERR
mdefine_line|#define IF_IADBG_ERR            0x00000100        
singleline_comment|// debug system error
DECL|macro|IF_IADBG_EVENT
mdefine_line|#define IF_IADBG_EVENT          0x00000200        
singleline_comment|// debug event
DECL|macro|IF_IADBG_DIS_INTR
mdefine_line|#define IF_IADBG_DIS_INTR       0x00001000        
singleline_comment|// debug disable interrupt
DECL|macro|IF_IADBG_EN_INTR
mdefine_line|#define IF_IADBG_EN_INTR        0x00002000        
singleline_comment|// debug enable interrupt
DECL|macro|IF_IADBG_LOUD
mdefine_line|#define IF_IADBG_LOUD           0x00004000        
singleline_comment|// debugging info
DECL|macro|IF_IADBG_VERY_LOUD
mdefine_line|#define IF_IADBG_VERY_LOUD      0x00008000        
singleline_comment|// excessive debugging info
DECL|macro|IF_IADBG_CBR
mdefine_line|#define IF_IADBG_CBR            0x00100000  &t;  
singleline_comment|//
DECL|macro|IF_IADBG_UBR
mdefine_line|#define IF_IADBG_UBR            0x00200000  &t;  
singleline_comment|//
DECL|macro|IF_IADBG_ABR
mdefine_line|#define IF_IADBG_ABR            0x00400000        
singleline_comment|//
DECL|macro|IF_IADBG_DESC
mdefine_line|#define IF_IADBG_DESC           0x01000000        
singleline_comment|//
DECL|macro|IF_IADBG_SUNI_STAT
mdefine_line|#define IF_IADBG_SUNI_STAT      0x02000000        
singleline_comment|// suni statistics
DECL|macro|IF_IADBG_RESET
mdefine_line|#define IF_IADBG_RESET          0x04000000        
r_extern
r_int
r_int
id|IADebugFlag
suffix:semicolon
DECL|macro|IF_IADBG
mdefine_line|#define IF_IADBG(f) if (IADebugFlag &amp; (f))
macro_line|#ifdef  CONFIG_ATM_IA_DEBUG   /* Debug build */
DECL|macro|IF_LOUD
mdefine_line|#define IF_LOUD(A) IF_IADBG(IF_IADBG_LOUD) { A }
DECL|macro|IF_ERR
mdefine_line|#define IF_ERR(A) IF_IADBG(IF_IADBG_ERR) { A }
DECL|macro|IF_VERY_LOUD
mdefine_line|#define IF_VERY_LOUD(A) IF_IADBG( IF_IADBG_VERY_LOUD ) { A }
DECL|macro|IF_INIT_ADAPTER
mdefine_line|#define IF_INIT_ADAPTER(A) IF_IADBG( IF_IADBG_INIT_ADAPTER ) { A }
DECL|macro|IF_INIT
mdefine_line|#define IF_INIT(A) IF_IADBG( IF_IADBG_INIT_ADAPTER ) { A }
DECL|macro|IF_SUNI_STAT
mdefine_line|#define IF_SUNI_STAT(A) IF_IADBG( IF_IADBG_SUNI_STAT ) { A }
DECL|macro|IF_QUERY_INFO
mdefine_line|#define IF_QUERY_INFO(A) IF_IADBG( IF_IADBG_QUERY_INFO ) { A }
DECL|macro|IF_COPY_OVER
mdefine_line|#define IF_COPY_OVER(A) IF_IADBG( IF_IADBG_COPY_OVER ) { A }
DECL|macro|IF_INTR
mdefine_line|#define IF_INTR(A) IF_IADBG( IF_IADBG_INTR ) { A }
DECL|macro|IF_DIS_INTR
mdefine_line|#define IF_DIS_INTR(A) IF_IADBG( IF_IADBG_DIS_INTR ) { A }
DECL|macro|IF_EN_INTR
mdefine_line|#define IF_EN_INTR(A) IF_IADBG( IF_IADBG_EN_INTR ) { A }
DECL|macro|IF_TX
mdefine_line|#define IF_TX(A) IF_IADBG( IF_IADBG_TX ) { A }
DECL|macro|IF_RX
mdefine_line|#define IF_RX(A) IF_IADBG( IF_IADBG_RX ) { A }
DECL|macro|IF_TXPKT
mdefine_line|#define IF_TXPKT(A) IF_IADBG( IF_IADBG_TXPKT ) { A }
DECL|macro|IF_RXPKT
mdefine_line|#define IF_RXPKT(A) IF_IADBG( IF_IADBG_RXPKT ) { A }
DECL|macro|IF_SHUTDOWN
mdefine_line|#define IF_SHUTDOWN(A) IF_IADBG(IF_IADBG_SHUTDOWN) { A }
DECL|macro|IF_CBR
mdefine_line|#define IF_CBR(A) IF_IADBG( IF_IADBG_CBR ) { A }
DECL|macro|IF_UBR
mdefine_line|#define IF_UBR(A) IF_IADBG( IF_IADBG_UBR ) { A }
DECL|macro|IF_ABR
mdefine_line|#define IF_ABR(A) IF_IADBG( IF_IADBG_ABR ) { A }
DECL|macro|IF_EVENT
mdefine_line|#define IF_EVENT(A) IF_IADBG( IF_IADBG_EVENT) { A }
macro_line|#else /* free build */
DECL|macro|IF_LOUD
mdefine_line|#define IF_LOUD(A)
DECL|macro|IF_VERY_LOUD
mdefine_line|#define IF_VERY_LOUD(A)
DECL|macro|IF_INIT_ADAPTER
mdefine_line|#define IF_INIT_ADAPTER(A)
DECL|macro|IF_INIT
mdefine_line|#define IF_INIT(A)
DECL|macro|IF_SUNI_STAT
mdefine_line|#define IF_SUNI_STAT(A)
DECL|macro|IF_PVC_CHKPKT
mdefine_line|#define IF_PVC_CHKPKT(A)
DECL|macro|IF_QUERY_INFO
mdefine_line|#define IF_QUERY_INFO(A)
DECL|macro|IF_COPY_OVER
mdefine_line|#define IF_COPY_OVER(A)
DECL|macro|IF_HANG
mdefine_line|#define IF_HANG(A)
DECL|macro|IF_INTR
mdefine_line|#define IF_INTR(A)
DECL|macro|IF_DIS_INTR
mdefine_line|#define IF_DIS_INTR(A)
DECL|macro|IF_EN_INTR
mdefine_line|#define IF_EN_INTR(A)
DECL|macro|IF_TX
mdefine_line|#define IF_TX(A)
DECL|macro|IF_RX
mdefine_line|#define IF_RX(A)
DECL|macro|IF_TXDEBUG
mdefine_line|#define IF_TXDEBUG(A)
DECL|macro|IF_VC
mdefine_line|#define IF_VC(A)
DECL|macro|IF_ERR
mdefine_line|#define IF_ERR(A) 
DECL|macro|IF_CBR
mdefine_line|#define IF_CBR(A)
DECL|macro|IF_UBR
mdefine_line|#define IF_UBR(A)
DECL|macro|IF_ABR
mdefine_line|#define IF_ABR(A)
DECL|macro|IF_SHUTDOWN
mdefine_line|#define IF_SHUTDOWN(A)
DECL|macro|DbgPrint
mdefine_line|#define DbgPrint(A)
DECL|macro|IF_EVENT
mdefine_line|#define IF_EVENT(A)
DECL|macro|IF_TXPKT
mdefine_line|#define IF_TXPKT(A) 
DECL|macro|IF_RXPKT
mdefine_line|#define IF_RXPKT(A)
macro_line|#endif /* CONFIG_ATM_IA_DEBUG */ 
DECL|macro|isprint
mdefine_line|#define isprint(a) ((a &gt;=&squot; &squot;)&amp;&amp;(a &lt;= &squot;~&squot;))  
DECL|macro|ATM_DESC
mdefine_line|#define ATM_DESC(skb) (skb-&gt;protocol)
DECL|macro|IA_SKB_STATE
mdefine_line|#define IA_SKB_STATE(skb) (skb-&gt;protocol)
DECL|macro|IA_DLED
mdefine_line|#define IA_DLED   1
DECL|macro|IA_TX_DONE
mdefine_line|#define IA_TX_DONE 2
multiline_comment|/* iadbg defines */
DECL|macro|IA_CMD
mdefine_line|#define IA_CMD   0x7749
r_typedef
r_struct
(brace
DECL|member|cmd
r_int
id|cmd
suffix:semicolon
DECL|member|sub_cmd
r_int
id|sub_cmd
suffix:semicolon
DECL|member|len
r_int
id|len
suffix:semicolon
DECL|member|maddr
id|u32
id|maddr
suffix:semicolon
DECL|member|status
r_int
id|status
suffix:semicolon
DECL|member|buf
r_void
op_star
id|buf
suffix:semicolon
DECL|typedef|IA_CMDBUF
DECL|typedef|PIA_CMDBUF
)brace
id|IA_CMDBUF
comma
op_star
id|PIA_CMDBUF
suffix:semicolon
multiline_comment|/* cmds */
DECL|macro|MEMDUMP
mdefine_line|#define MEMDUMP     &t;&t;0x01
multiline_comment|/* sub_cmds */
DECL|macro|MEMDUMP_SEGREG
mdefine_line|#define MEMDUMP_SEGREG          0x2
DECL|macro|MEMDUMP_DEV
mdefine_line|#define MEMDUMP_DEV  &t;&t;0x1
DECL|macro|MEMDUMP_REASSREG
mdefine_line|#define MEMDUMP_REASSREG        0x3
DECL|macro|MEMDUMP_FFL
mdefine_line|#define MEMDUMP_FFL             0x4
DECL|macro|READ_REG
mdefine_line|#define READ_REG                0x5
DECL|macro|WAKE_DBG_WAIT
mdefine_line|#define WAKE_DBG_WAIT           0x6
multiline_comment|/************************ IADBG DEFINE END ***************************/
DECL|macro|Boolean
mdefine_line|#define Boolean(x)    &t;((x) ? 1 : 0)
DECL|macro|NR_VCI
mdefine_line|#define NR_VCI 1024&t;&t;/* number of VCIs */  
DECL|macro|NR_VCI_LD
mdefine_line|#define NR_VCI_LD 10&t;&t;/* log2(NR_VCI) */  
DECL|macro|NR_VCI_4K
mdefine_line|#define NR_VCI_4K 4096 &t;&t;/* number of VCIs */  
DECL|macro|NR_VCI_4K_LD
mdefine_line|#define NR_VCI_4K_LD 12&t;&t;/* log2(NR_VCI) */  
DECL|macro|MEM_VALID
mdefine_line|#define MEM_VALID 0xfffffff0&t;/* mask base address with this */  
macro_line|#ifndef PCI_VENDOR_ID_IPHASE  
DECL|macro|PCI_VENDOR_ID_IPHASE
mdefine_line|#define PCI_VENDOR_ID_IPHASE 0x107e  
macro_line|#endif  
macro_line|#ifndef PCI_DEVICE_ID_IPHASE_5575  
DECL|macro|PCI_DEVICE_ID_IPHASE_5575
mdefine_line|#define PCI_DEVICE_ID_IPHASE_5575 0x0008  
macro_line|#endif  
DECL|macro|DEV_LABEL
mdefine_line|#define DEV_LABEL &t;&quot;ia&quot;  
DECL|macro|PCR
mdefine_line|#define PCR&t;207692  
DECL|macro|ICR
mdefine_line|#define ICR&t;100000  
DECL|macro|MCR
mdefine_line|#define MCR&t;0  
DECL|macro|TBE
mdefine_line|#define TBE&t;1000  
DECL|macro|FRTT
mdefine_line|#define FRTT&t;1  
DECL|macro|RIF
mdefine_line|#define RIF&t;2&t;&t;  
DECL|macro|RDF
mdefine_line|#define RDF&t;4  
DECL|macro|NRMCODE
mdefine_line|#define NRMCODE 5&t;/* 0 - 7 */  
DECL|macro|TRMCODE
mdefine_line|#define TRMCODE&t;3&t;/* 0 - 7 */  
DECL|macro|CDFCODE
mdefine_line|#define CDFCODE&t;6  
DECL|macro|ATDFCODE
mdefine_line|#define ATDFCODE 2&t;/* 0 - 15 */  
multiline_comment|/*---------------------- Packet/Cell Memory ------------------------*/
DECL|macro|TX_PACKET_RAM
mdefine_line|#define TX_PACKET_RAM &t;0x00000 /* start of Trasnmit Packet memory - 0 */  
DECL|macro|DFL_TX_BUF_SZ
mdefine_line|#define DFL_TX_BUF_SZ&t;10240&t;/* 10 K buffers */  
DECL|macro|DFL_TX_BUFFERS
mdefine_line|#define DFL_TX_BUFFERS     50 &t;/* number of packet buffers for Tx   &n;&t;&t;&t;&t;&t;- descriptor 0 unused */  
DECL|macro|REASS_RAM_SIZE
mdefine_line|#define REASS_RAM_SIZE 0x10000  /* for 64K 1K VC board */  
DECL|macro|RX_PACKET_RAM
mdefine_line|#define RX_PACKET_RAM &t;0x80000 /* start of Receive Packet memory - 512K */  
DECL|macro|DFL_RX_BUF_SZ
mdefine_line|#define DFL_RX_BUF_SZ&t;10240&t;/* 10k buffers */  
DECL|macro|DFL_RX_BUFFERS
mdefine_line|#define DFL_RX_BUFFERS      50&t;/* number of packet buffers for Rx   &n;&t;&t;&t;&t;&t;- descriptor 0 unused */  
DECL|struct|cpcs_trailer
r_struct
id|cpcs_trailer
(brace
DECL|member|control
id|u_short
id|control
suffix:semicolon
DECL|member|length
id|u_short
id|length
suffix:semicolon
DECL|member|crc32
id|u_int
id|crc32
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ia_vcc
r_struct
id|ia_vcc
(brace
DECL|member|rxing
r_int
id|rxing
suffix:semicolon
DECL|member|txing
r_int
id|txing
suffix:semicolon
DECL|member|NumCbrEntry
r_int
id|NumCbrEntry
suffix:semicolon
DECL|member|pcr
id|u32
id|pcr
suffix:semicolon
DECL|member|saved_tx_quota
id|u32
id|saved_tx_quota
suffix:semicolon
DECL|member|flow_inc
r_int
id|flow_inc
suffix:semicolon
DECL|member|txing_skb
r_struct
id|sk_buff_head
id|txing_skb
suffix:semicolon
DECL|member|ltimeout
r_int
id|ltimeout
suffix:semicolon
DECL|member|vc_desc_cnt
id|u8
id|vc_desc_cnt
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|abr_vc_table
r_struct
id|abr_vc_table
(brace
DECL|member|status
id|u_char
id|status
suffix:semicolon
DECL|member|rdf
id|u_char
id|rdf
suffix:semicolon
DECL|member|air
id|u_short
id|air
suffix:semicolon
DECL|member|res
id|u_int
id|res
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|req_rm_cell_data1
id|u_int
id|req_rm_cell_data1
suffix:semicolon
DECL|member|req_rm_cell_data2
id|u_int
id|req_rm_cell_data2
suffix:semicolon
DECL|member|add_rm_cell_data1
id|u_int
id|add_rm_cell_data1
suffix:semicolon
DECL|member|add_rm_cell_data2
id|u_int
id|add_rm_cell_data2
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* 32 byte entries */
DECL|struct|main_vc
r_struct
id|main_vc
(brace
DECL|member|type
id|u_short
id|type
suffix:semicolon
DECL|macro|ABR
mdefine_line|#define ABR&t;0x8000  
DECL|macro|UBR
mdefine_line|#define UBR &t;0xc000  
DECL|macro|CBR
mdefine_line|#define CBR&t;0x0000  
multiline_comment|/* ABR fields */
DECL|member|nrm
id|u_short
id|nrm
suffix:semicolon
DECL|member|trm
id|u_short
id|trm
suffix:semicolon
DECL|member|rm_timestamp_hi
id|u_short
id|rm_timestamp_hi
suffix:semicolon
DECL|member|rm_timestamp_lo
id|u_short
id|rm_timestamp_lo
suffix:colon
l_int|8
comma
DECL|member|crm
id|crm
suffix:colon
l_int|8
suffix:semicolon
DECL|member|remainder
id|u_short
id|remainder
suffix:semicolon
multiline_comment|/* ABR and UBR fields - last 10 bits*/
DECL|member|next_vc_sched
id|u_short
id|next_vc_sched
suffix:semicolon
DECL|member|present_desc
id|u_short
id|present_desc
suffix:semicolon
multiline_comment|/* all classes */
DECL|member|last_cell_slot
id|u_short
id|last_cell_slot
suffix:semicolon
multiline_comment|/* ABR and UBR */
DECL|member|pcr
id|u_short
id|pcr
suffix:semicolon
DECL|member|fraction
id|u_short
id|fraction
suffix:semicolon
DECL|member|icr
id|u_short
id|icr
suffix:semicolon
DECL|member|atdf
id|u_short
id|atdf
suffix:semicolon
DECL|member|mcr
id|u_short
id|mcr
suffix:semicolon
DECL|member|acr
id|u_short
id|acr
suffix:semicolon
DECL|member|unack
id|u_short
id|unack
suffix:colon
l_int|8
comma
DECL|member|status
id|status
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* all classes */
DECL|macro|UIOLI
mdefine_line|#define UIOLI 0x80  
DECL|macro|CRC_APPEND
mdefine_line|#define CRC_APPEND 0x40&t;&t;&t;/* for status field - CRC-32 append */  
DECL|macro|ABR_STATE
mdefine_line|#define ABR_STATE 0x02  
)brace
suffix:semicolon
multiline_comment|/* 8 byte entries */
DECL|struct|ext_vc
r_struct
id|ext_vc
(brace
DECL|member|atm_hdr1
id|u_short
id|atm_hdr1
suffix:semicolon
DECL|member|atm_hdr2
id|u_short
id|atm_hdr2
suffix:semicolon
DECL|member|last_desc
id|u_short
id|last_desc
suffix:semicolon
DECL|member|out_of_rate_link
id|u_short
id|out_of_rate_link
suffix:semicolon
multiline_comment|/* reserved for UBR and CBR */
)brace
suffix:semicolon
DECL|macro|DLE_ENTRIES
mdefine_line|#define DLE_ENTRIES 256  
DECL|macro|DMA_INT_ENABLE
mdefine_line|#define DMA_INT_ENABLE 0x0002&t;/* use for both Tx and Rx */  
DECL|macro|TX_DLE_PSI
mdefine_line|#define TX_DLE_PSI 0x0001  
multiline_comment|/* Descriptor List Entries (DLE) */
DECL|struct|dle
r_struct
id|dle
(brace
DECL|member|sys_pkt_addr
id|u32
id|sys_pkt_addr
suffix:semicolon
DECL|member|local_pkt_addr
id|u32
id|local_pkt_addr
suffix:semicolon
DECL|member|bytes
id|u32
id|bytes
suffix:semicolon
DECL|member|prq_wr_ptr_data
id|u16
id|prq_wr_ptr_data
suffix:semicolon
DECL|member|mode
id|u16
id|mode
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|dle_q
r_struct
id|dle_q
(brace
DECL|member|start
r_struct
id|dle
op_star
id|start
suffix:semicolon
DECL|member|end
r_struct
id|dle
op_star
id|end
suffix:semicolon
DECL|member|read
r_struct
id|dle
op_star
id|read
suffix:semicolon
DECL|member|write
r_struct
id|dle
op_star
id|write
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|free_desc_q
r_struct
id|free_desc_q
(brace
DECL|member|desc
r_int
id|desc
suffix:semicolon
multiline_comment|/* Descriptor number */
DECL|member|next
r_struct
id|free_desc_q
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|tx_buf_desc
r_struct
id|tx_buf_desc
(brace
DECL|member|desc_mode
r_int
r_int
id|desc_mode
suffix:semicolon
DECL|member|vc_index
r_int
r_int
id|vc_index
suffix:semicolon
DECL|member|res1
r_int
r_int
id|res1
suffix:semicolon
multiline_comment|/* reserved field */
DECL|member|bytes
r_int
r_int
id|bytes
suffix:semicolon
DECL|member|buf_start_hi
r_int
r_int
id|buf_start_hi
suffix:semicolon
DECL|member|buf_start_lo
r_int
r_int
id|buf_start_lo
suffix:semicolon
DECL|member|res2
r_int
r_int
id|res2
(braket
l_int|10
)braket
suffix:semicolon
multiline_comment|/* reserved field */
)brace
suffix:semicolon
DECL|struct|rx_buf_desc
r_struct
id|rx_buf_desc
(brace
DECL|member|desc_mode
r_int
r_int
id|desc_mode
suffix:semicolon
DECL|member|vc_index
r_int
r_int
id|vc_index
suffix:semicolon
DECL|member|vpi
r_int
r_int
id|vpi
suffix:semicolon
DECL|member|bytes
r_int
r_int
id|bytes
suffix:semicolon
DECL|member|buf_start_hi
r_int
r_int
id|buf_start_hi
suffix:semicolon
DECL|member|buf_start_lo
r_int
r_int
id|buf_start_lo
suffix:semicolon
DECL|member|dma_start_hi
r_int
r_int
id|dma_start_hi
suffix:semicolon
DECL|member|dma_start_lo
r_int
r_int
id|dma_start_lo
suffix:semicolon
DECL|member|crc_upper
r_int
r_int
id|crc_upper
suffix:semicolon
DECL|member|crc_lower
r_int
r_int
id|crc_lower
suffix:semicolon
DECL|member|res
DECL|member|timeout
r_int
r_int
id|res
suffix:colon
l_int|8
comma
id|timeout
suffix:colon
l_int|8
suffix:semicolon
DECL|member|res2
r_int
r_int
id|res2
(braket
l_int|5
)braket
suffix:semicolon
multiline_comment|/* reserved field */
)brace
suffix:semicolon
multiline_comment|/*--------SAR stuff ---------------------*/
DECL|macro|EPROM_SIZE
mdefine_line|#define EPROM_SIZE 0x40000&t;/* says 64K in the docs ??? */  
DECL|macro|MAC1_LEN
mdefine_line|#define MAC1_LEN&t;4&t;   &t;&t;&t;&t;&t;  
DECL|macro|MAC2_LEN
mdefine_line|#define MAC2_LEN&t;2  
multiline_comment|/*------------ PCI Memory Space Map, 128K SAR memory ----------------*/
DECL|macro|IPHASE5575_PCI_CONFIG_REG_BASE
mdefine_line|#define IPHASE5575_PCI_CONFIG_REG_BASE&t;0x0000  
DECL|macro|IPHASE5575_BUS_CONTROL_REG_BASE
mdefine_line|#define IPHASE5575_BUS_CONTROL_REG_BASE 0x1000&t;/* offsets 0x00 - 0x3c */  
DECL|macro|IPHASE5575_FRAG_CONTROL_REG_BASE
mdefine_line|#define IPHASE5575_FRAG_CONTROL_REG_BASE 0x2000  
DECL|macro|IPHASE5575_REASS_CONTROL_REG_BASE
mdefine_line|#define IPHASE5575_REASS_CONTROL_REG_BASE 0x3000  
DECL|macro|IPHASE5575_DMA_CONTROL_REG_BASE
mdefine_line|#define IPHASE5575_DMA_CONTROL_REG_BASE&t;0x4000  
DECL|macro|IPHASE5575_FRONT_END_REG_BASE
mdefine_line|#define IPHASE5575_FRONT_END_REG_BASE IPHASE5575_DMA_CONTROL_REG_BASE  
DECL|macro|IPHASE5575_FRAG_CONTROL_RAM_BASE
mdefine_line|#define IPHASE5575_FRAG_CONTROL_RAM_BASE 0x10000  
DECL|macro|IPHASE5575_REASS_CONTROL_RAM_BASE
mdefine_line|#define IPHASE5575_REASS_CONTROL_RAM_BASE 0x20000  
multiline_comment|/*------------ Bus interface control registers -----------------*/
DECL|macro|IPHASE5575_BUS_CONTROL_REG
mdefine_line|#define IPHASE5575_BUS_CONTROL_REG&t;0x00  
DECL|macro|IPHASE5575_BUS_STATUS_REG
mdefine_line|#define IPHASE5575_BUS_STATUS_REG&t;0x01&t;/* actual offset 0x04 */  
DECL|macro|IPHASE5575_MAC1
mdefine_line|#define IPHASE5575_MAC1&t;&t;&t;0x02  
DECL|macro|IPHASE5575_REV
mdefine_line|#define IPHASE5575_REV&t;&t;&t;0x03  
DECL|macro|IPHASE5575_MAC2
mdefine_line|#define IPHASE5575_MAC2&t;&t;&t;0x03&t;/*actual offset 0x0e-reg 0x0c*/  
DECL|macro|IPHASE5575_EXT_RESET
mdefine_line|#define IPHASE5575_EXT_RESET&t;&t;0x04  
DECL|macro|IPHASE5575_INT_RESET
mdefine_line|#define IPHASE5575_INT_RESET&t;&t;0x05&t;/* addr 1c ?? reg 0x06 */  
DECL|macro|IPHASE5575_PCI_ADDR_PAGE
mdefine_line|#define IPHASE5575_PCI_ADDR_PAGE&t;0x07&t;/* reg 0x08, 0x09 ?? */  
DECL|macro|IPHASE5575_EEPROM_ACCESS
mdefine_line|#define IPHASE5575_EEPROM_ACCESS&t;0x0a&t;/* actual offset 0x28 */  
DECL|macro|IPHASE5575_CELL_FIFO_QUEUE_SZ
mdefine_line|#define IPHASE5575_CELL_FIFO_QUEUE_SZ&t;0x0b  
DECL|macro|IPHASE5575_CELL_FIFO_MARK_STATE
mdefine_line|#define IPHASE5575_CELL_FIFO_MARK_STATE&t;0x0c  
DECL|macro|IPHASE5575_CELL_FIFO_READ_PTR
mdefine_line|#define IPHASE5575_CELL_FIFO_READ_PTR&t;0x0d  
DECL|macro|IPHASE5575_CELL_FIFO_WRITE_PTR
mdefine_line|#define IPHASE5575_CELL_FIFO_WRITE_PTR&t;0x0e  
DECL|macro|IPHASE5575_CELL_FIFO_CELLS_AVL
mdefine_line|#define IPHASE5575_CELL_FIFO_CELLS_AVL&t;0x0f&t;/* actual offset 0x3c */  
multiline_comment|/* Bus Interface Control Register bits */
DECL|macro|CTRL_FE_RST
mdefine_line|#define CTRL_FE_RST&t;0x80000000  
DECL|macro|CTRL_LED
mdefine_line|#define CTRL_LED&t;0x40000000  
DECL|macro|CTRL_25MBPHY
mdefine_line|#define CTRL_25MBPHY&t;0x10000000  
DECL|macro|CTRL_ENCMBMEM
mdefine_line|#define CTRL_ENCMBMEM&t;0x08000000  
DECL|macro|CTRL_ENOFFSEG
mdefine_line|#define CTRL_ENOFFSEG&t;0x01000000  
DECL|macro|CTRL_ERRMASK
mdefine_line|#define CTRL_ERRMASK&t;0x00400000  
DECL|macro|CTRL_DLETMASK
mdefine_line|#define CTRL_DLETMASK&t;0x00100000  
DECL|macro|CTRL_DLERMASK
mdefine_line|#define CTRL_DLERMASK&t;0x00080000  
DECL|macro|CTRL_FEMASK
mdefine_line|#define CTRL_FEMASK&t;0x00040000  
DECL|macro|CTRL_SEGMASK
mdefine_line|#define CTRL_SEGMASK&t;0x00020000  
DECL|macro|CTRL_REASSMASK
mdefine_line|#define CTRL_REASSMASK&t;0x00010000  
DECL|macro|CTRL_CSPREEMPT
mdefine_line|#define CTRL_CSPREEMPT&t;0x00002000  
DECL|macro|CTRL_B128
mdefine_line|#define CTRL_B128&t;0x00000200  
DECL|macro|CTRL_B64
mdefine_line|#define CTRL_B64&t;0x00000100  
DECL|macro|CTRL_B48
mdefine_line|#define CTRL_B48&t;0x00000080  
DECL|macro|CTRL_B32
mdefine_line|#define CTRL_B32&t;0x00000040  
DECL|macro|CTRL_B16
mdefine_line|#define CTRL_B16&t;0x00000020  
DECL|macro|CTRL_B8
mdefine_line|#define CTRL_B8&t;&t;0x00000010  
multiline_comment|/* Bus Interface Status Register bits */
DECL|macro|STAT_CMEMSIZ
mdefine_line|#define STAT_CMEMSIZ&t;0xc0000000  
DECL|macro|STAT_ADPARCK
mdefine_line|#define STAT_ADPARCK&t;0x20000000  
DECL|macro|STAT_RESVD
mdefine_line|#define STAT_RESVD&t;0x1fffff80  
DECL|macro|STAT_ERRINT
mdefine_line|#define STAT_ERRINT&t;0x00000040  
DECL|macro|STAT_MARKINT
mdefine_line|#define STAT_MARKINT&t;0x00000020  
DECL|macro|STAT_DLETINT
mdefine_line|#define STAT_DLETINT&t;0x00000010  
DECL|macro|STAT_DLERINT
mdefine_line|#define STAT_DLERINT&t;0x00000008  
DECL|macro|STAT_FEINT
mdefine_line|#define STAT_FEINT&t;0x00000004  
DECL|macro|STAT_SEGINT
mdefine_line|#define STAT_SEGINT&t;0x00000002  
DECL|macro|STAT_REASSINT
mdefine_line|#define STAT_REASSINT&t;0x00000001  
multiline_comment|/*--------------- Segmentation control registers -----------------*/
multiline_comment|/* The segmentation registers are 16 bits access and the addresses  &n;&t;are defined as such so the addresses are the actual &quot;offsets&quot; */
DECL|macro|IDLEHEADHI
mdefine_line|#define IDLEHEADHI&t;0x00  
DECL|macro|IDLEHEADLO
mdefine_line|#define IDLEHEADLO&t;0x01  
DECL|macro|MAXRATE
mdefine_line|#define MAXRATE&t;&t;0x02  
multiline_comment|/* Values for MAXRATE register for 155Mbps and 25.6 Mbps operation */
DECL|macro|RATE155
mdefine_line|#define RATE155&t;&t;0x64b1 
singleline_comment|// 16 bits float format 
DECL|macro|MAX_ATM_155
mdefine_line|#define MAX_ATM_155     352768 
singleline_comment|// Cells/second p.118
DECL|macro|RATE25
mdefine_line|#define RATE25&t;&t;0x5f9d  
DECL|macro|STPARMS
mdefine_line|#define STPARMS&t;&t;0x03  
DECL|macro|STPARMS_1K
mdefine_line|#define STPARMS_1K&t;0x008c  
DECL|macro|STPARMS_2K
mdefine_line|#define STPARMS_2K&t;0x0049  
DECL|macro|STPARMS_4K
mdefine_line|#define STPARMS_4K&t;0x0026  
DECL|macro|COMP_EN
mdefine_line|#define COMP_EN&t;&t;0x4000  
DECL|macro|CBR_EN
mdefine_line|#define CBR_EN&t;&t;0x2000  
DECL|macro|ABR_EN
mdefine_line|#define ABR_EN&t;&t;0x0800  
DECL|macro|UBR_EN
mdefine_line|#define UBR_EN&t;&t;0x0400  
DECL|macro|ABRUBR_ARB
mdefine_line|#define ABRUBR_ARB&t;0x04  
DECL|macro|RM_TYPE
mdefine_line|#define RM_TYPE&t;&t;0x05  
multiline_comment|/*Value for RM_TYPE register for ATM Forum Traffic Mangement4.0 support*/
DECL|macro|RM_TYPE_4_0
mdefine_line|#define RM_TYPE_4_0&t;0x0100  
DECL|macro|SEG_COMMAND_REG
mdefine_line|#define SEG_COMMAND_REG&t;&t;0x17  
multiline_comment|/* Values for the command register */
DECL|macro|RESET_SEG
mdefine_line|#define RESET_SEG 0x0055  
DECL|macro|RESET_SEG_STATE
mdefine_line|#define RESET_SEG_STATE&t;0x00aa  
DECL|macro|RESET_TX_CELL_CTR
mdefine_line|#define RESET_TX_CELL_CTR 0x00cc  
DECL|macro|CBR_PTR_BASE
mdefine_line|#define CBR_PTR_BASE&t;0x20  
DECL|macro|ABR_SBPTR_BASE
mdefine_line|#define ABR_SBPTR_BASE&t;0x22  
DECL|macro|UBR_SBPTR_BASE
mdefine_line|#define UBR_SBPTR_BASE  0x23  
DECL|macro|ABRWQ_BASE
mdefine_line|#define ABRWQ_BASE&t;0x26  
DECL|macro|UBRWQ_BASE
mdefine_line|#define UBRWQ_BASE&t;0x27  
DECL|macro|VCT_BASE
mdefine_line|#define VCT_BASE&t;0x28  
DECL|macro|VCTE_BASE
mdefine_line|#define VCTE_BASE&t;0x29  
DECL|macro|CBR_TAB_BEG
mdefine_line|#define CBR_TAB_BEG&t;0x2c  
DECL|macro|CBR_TAB_END
mdefine_line|#define CBR_TAB_END&t;0x2d  
DECL|macro|PRQ_ST_ADR
mdefine_line|#define PRQ_ST_ADR&t;0x30  
DECL|macro|PRQ_ED_ADR
mdefine_line|#define PRQ_ED_ADR&t;0x31  
DECL|macro|PRQ_RD_PTR
mdefine_line|#define PRQ_RD_PTR&t;0x32  
DECL|macro|PRQ_WR_PTR
mdefine_line|#define PRQ_WR_PTR&t;0x33  
DECL|macro|TCQ_ST_ADR
mdefine_line|#define TCQ_ST_ADR&t;0x34  
DECL|macro|TCQ_ED_ADR
mdefine_line|#define TCQ_ED_ADR &t;0x35  
DECL|macro|TCQ_RD_PTR
mdefine_line|#define TCQ_RD_PTR&t;0x36  
DECL|macro|TCQ_WR_PTR
mdefine_line|#define TCQ_WR_PTR&t;0x37  
DECL|macro|SEG_QUEUE_BASE
mdefine_line|#define SEG_QUEUE_BASE&t;0x40  
DECL|macro|SEG_DESC_BASE
mdefine_line|#define SEG_DESC_BASE&t;0x41  
DECL|macro|MODE_REG_0
mdefine_line|#define MODE_REG_0&t;0x45  
DECL|macro|T_ONLINE
mdefine_line|#define T_ONLINE&t;0x0002&t;&t;/* (i)chipSAR is online */  
DECL|macro|MODE_REG_1
mdefine_line|#define MODE_REG_1&t;0x46  
DECL|macro|MODE_REG_1_VAL
mdefine_line|#define MODE_REG_1_VAL&t;0x0400&t;&t;/*for propoer device operation*/  
DECL|macro|SEG_INTR_STATUS_REG
mdefine_line|#define SEG_INTR_STATUS_REG 0x47  
DECL|macro|SEG_MASK_REG
mdefine_line|#define SEG_MASK_REG&t;0x48  
DECL|macro|TRANSMIT_DONE
mdefine_line|#define TRANSMIT_DONE 0x0200
DECL|macro|TCQ_NOT_EMPTY
mdefine_line|#define TCQ_NOT_EMPTY 0x1000&t;/* this can be used for both the interrupt   &n;&t;&t;&t;&t;status registers as well as the mask register */  
DECL|macro|CELL_CTR_HIGH_AUTO
mdefine_line|#define CELL_CTR_HIGH_AUTO 0x49  
DECL|macro|CELL_CTR_HIGH_NOAUTO
mdefine_line|#define CELL_CTR_HIGH_NOAUTO 0xc9  
DECL|macro|CELL_CTR_LO_AUTO
mdefine_line|#define CELL_CTR_LO_AUTO 0x4a  
DECL|macro|CELL_CTR_LO_NOAUTO
mdefine_line|#define CELL_CTR_LO_NOAUTO 0xca  
multiline_comment|/* Diagnostic registers */
DECL|macro|NEXTDESC
mdefine_line|#define NEXTDESC &t;0x59  
DECL|macro|NEXTVC
mdefine_line|#define NEXTVC&t;&t;0x5a  
DECL|macro|PSLOTCNT
mdefine_line|#define PSLOTCNT&t;0x5d  
DECL|macro|NEWDN
mdefine_line|#define NEWDN&t;&t;0x6a  
DECL|macro|NEWVC
mdefine_line|#define NEWVC&t;&t;0x6b  
DECL|macro|SBPTR
mdefine_line|#define SBPTR&t;&t;0x6c  
DECL|macro|ABRWQ_WRPTR
mdefine_line|#define ABRWQ_WRPTR&t;0x6f  
DECL|macro|ABRWQ_RDPTR
mdefine_line|#define ABRWQ_RDPTR&t;0x70  
DECL|macro|UBRWQ_WRPTR
mdefine_line|#define UBRWQ_WRPTR&t;0x71  
DECL|macro|UBRWQ_RDPTR
mdefine_line|#define UBRWQ_RDPTR&t;0x72  
DECL|macro|CBR_VC
mdefine_line|#define CBR_VC&t;&t;0x73  
DECL|macro|ABR_SBVC
mdefine_line|#define ABR_SBVC&t;0x75  
DECL|macro|UBR_SBVC
mdefine_line|#define UBR_SBVC&t;0x76  
DECL|macro|ABRNEXTLINK
mdefine_line|#define ABRNEXTLINK&t;0x78  
DECL|macro|UBRNEXTLINK
mdefine_line|#define UBRNEXTLINK&t;0x79  
multiline_comment|/*----------------- Reassembly control registers ---------------------*/
multiline_comment|/* The reassembly registers are 16 bits access and the addresses  &n;&t;are defined as such so the addresses are the actual &quot;offsets&quot; */
DECL|macro|MODE_REG
mdefine_line|#define MODE_REG&t;0x00  
DECL|macro|R_ONLINE
mdefine_line|#define R_ONLINE&t;0x0002&t;&t;/* (i)chip is online */  
DECL|macro|IGN_RAW_FL
mdefine_line|#define IGN_RAW_FL     &t;0x0004
DECL|macro|PROTOCOL_ID
mdefine_line|#define PROTOCOL_ID&t;0x01  
DECL|macro|REASS_MASK_REG
mdefine_line|#define REASS_MASK_REG&t;0x02  
DECL|macro|REASS_INTR_STATUS_REG
mdefine_line|#define REASS_INTR_STATUS_REG&t;0x03  
multiline_comment|/* Interrupt Status register bits */
DECL|macro|RX_PKT_CTR_OF
mdefine_line|#define RX_PKT_CTR_OF&t;0x8000  
DECL|macro|RX_ERR_CTR_OF
mdefine_line|#define RX_ERR_CTR_OF&t;0x4000  
DECL|macro|RX_CELL_CTR_OF
mdefine_line|#define RX_CELL_CTR_OF&t;0x1000  
DECL|macro|RX_FREEQ_EMPT
mdefine_line|#define RX_FREEQ_EMPT&t;0x0200  
DECL|macro|RX_EXCPQ_FL
mdefine_line|#define RX_EXCPQ_FL&t;0x0080  
DECL|macro|RX_RAWQ_FL
mdefine_line|#define&t;RX_RAWQ_FL&t;0x0010  
DECL|macro|RX_EXCP_RCVD
mdefine_line|#define RX_EXCP_RCVD&t;0x0008  
DECL|macro|RX_PKT_RCVD
mdefine_line|#define RX_PKT_RCVD&t;0x0004  
DECL|macro|RX_RAW_RCVD
mdefine_line|#define RX_RAW_RCVD&t;0x0001  
DECL|macro|DRP_PKT_CNTR
mdefine_line|#define DRP_PKT_CNTR&t;0x04  
DECL|macro|ERR_CNTR
mdefine_line|#define ERR_CNTR&t;0x05  
DECL|macro|RAW_BASE_ADR
mdefine_line|#define RAW_BASE_ADR&t;0x08  
DECL|macro|CELL_CTR0
mdefine_line|#define CELL_CTR0&t;0x0c  
DECL|macro|CELL_CTR1
mdefine_line|#define CELL_CTR1&t;0x0d  
DECL|macro|REASS_COMMAND_REG
mdefine_line|#define REASS_COMMAND_REG&t;0x0f  
multiline_comment|/* Values for command register */
DECL|macro|RESET_REASS
mdefine_line|#define RESET_REASS&t;0x0055  
DECL|macro|RESET_REASS_STATE
mdefine_line|#define RESET_REASS_STATE 0x00aa  
DECL|macro|RESET_DRP_PKT_CNTR
mdefine_line|#define RESET_DRP_PKT_CNTR 0x00f1  
DECL|macro|RESET_ERR_CNTR
mdefine_line|#define RESET_ERR_CNTR&t;0x00f2  
DECL|macro|RESET_CELL_CNTR
mdefine_line|#define RESET_CELL_CNTR 0x00f8  
DECL|macro|RESET_REASS_ALL_REGS
mdefine_line|#define RESET_REASS_ALL_REGS 0x00ff  
DECL|macro|REASS_DESC_BASE
mdefine_line|#define REASS_DESC_BASE&t;0x10  
DECL|macro|VC_LKUP_BASE
mdefine_line|#define VC_LKUP_BASE&t;0x11  
DECL|macro|REASS_TABLE_BASE
mdefine_line|#define REASS_TABLE_BASE 0x12  
DECL|macro|REASS_QUEUE_BASE
mdefine_line|#define REASS_QUEUE_BASE 0x13  
DECL|macro|PKT_TM_CNT
mdefine_line|#define PKT_TM_CNT&t;0x16  
DECL|macro|TMOUT_RANGE
mdefine_line|#define TMOUT_RANGE&t;0x17  
DECL|macro|INTRVL_CNTR
mdefine_line|#define INTRVL_CNTR&t;0x18  
DECL|macro|TMOUT_INDX
mdefine_line|#define TMOUT_INDX&t;0x19  
DECL|macro|VP_LKUP_BASE
mdefine_line|#define VP_LKUP_BASE&t;0x1c  
DECL|macro|VP_FILTER
mdefine_line|#define VP_FILTER&t;0x1d  
DECL|macro|ABR_LKUP_BASE
mdefine_line|#define ABR_LKUP_BASE&t;0x1e  
DECL|macro|FREEQ_ST_ADR
mdefine_line|#define FREEQ_ST_ADR&t;0x24  
DECL|macro|FREEQ_ED_ADR
mdefine_line|#define FREEQ_ED_ADR&t;0x25  
DECL|macro|FREEQ_RD_PTR
mdefine_line|#define FREEQ_RD_PTR&t;0x26  
DECL|macro|FREEQ_WR_PTR
mdefine_line|#define FREEQ_WR_PTR&t;0x27  
DECL|macro|PCQ_ST_ADR
mdefine_line|#define PCQ_ST_ADR&t;0x28  
DECL|macro|PCQ_ED_ADR
mdefine_line|#define PCQ_ED_ADR&t;0x29  
DECL|macro|PCQ_RD_PTR
mdefine_line|#define PCQ_RD_PTR&t;0x2a  
DECL|macro|PCQ_WR_PTR
mdefine_line|#define PCQ_WR_PTR&t;0x2b  
DECL|macro|EXCP_Q_ST_ADR
mdefine_line|#define EXCP_Q_ST_ADR&t;0x2c  
DECL|macro|EXCP_Q_ED_ADR
mdefine_line|#define EXCP_Q_ED_ADR&t;0x2d  
DECL|macro|EXCP_Q_RD_PTR
mdefine_line|#define EXCP_Q_RD_PTR&t;0x2e  
DECL|macro|EXCP_Q_WR_PTR
mdefine_line|#define EXCP_Q_WR_PTR&t;0x2f  
DECL|macro|CC_FIFO_ST_ADR
mdefine_line|#define CC_FIFO_ST_ADR&t;0x34  
DECL|macro|CC_FIFO_ED_ADR
mdefine_line|#define CC_FIFO_ED_ADR&t;0x35  
DECL|macro|CC_FIFO_RD_PTR
mdefine_line|#define CC_FIFO_RD_PTR&t;0x36  
DECL|macro|CC_FIFO_WR_PTR
mdefine_line|#define CC_FIFO_WR_PTR&t;0x37  
DECL|macro|STATE_REG
mdefine_line|#define STATE_REG&t;0x38  
DECL|macro|BUF_SIZE
mdefine_line|#define BUF_SIZE&t;0x42  
DECL|macro|XTRA_RM_OFFSET
mdefine_line|#define XTRA_RM_OFFSET&t;0x44  
DECL|macro|DRP_PKT_CNTR_NC
mdefine_line|#define DRP_PKT_CNTR_NC&t;0x84  
DECL|macro|ERR_CNTR_NC
mdefine_line|#define ERR_CNTR_NC&t;0x85  
DECL|macro|CELL_CNTR0_NC
mdefine_line|#define CELL_CNTR0_NC&t;0x8c  
DECL|macro|CELL_CNTR1_NC
mdefine_line|#define CELL_CNTR1_NC&t;0x8d  
multiline_comment|/* State Register bits */
DECL|macro|EXCPQ_EMPTY
mdefine_line|#define EXCPQ_EMPTY&t;0x0040  
DECL|macro|PCQ_EMPTY
mdefine_line|#define PCQ_EMPTY&t;0x0010  
DECL|macro|FREEQ_EMPTY
mdefine_line|#define FREEQ_EMPTY&t;0x0004  
multiline_comment|/*----------------- Front End registers/ DMA control --------------*/
multiline_comment|/* There is a lot of documentation error regarding these offsets ???   &n;&t;eg:- 2 offsets given 800, a00 for rx counter  &n;&t;similarly many others  &n;   Remember again that the offsets are to be 4*register number, so  &n;&t;correct the #defines here   &n;*/
DECL|macro|IPHASE5575_TX_COUNTER
mdefine_line|#define IPHASE5575_TX_COUNTER&t;&t;0x200&t;/* offset - 0x800 */  
DECL|macro|IPHASE5575_RX_COUNTER
mdefine_line|#define IPHASE5575_RX_COUNTER&t;&t;0x280&t;/* offset - 0xa00 */  
DECL|macro|IPHASE5575_TX_LIST_ADDR
mdefine_line|#define IPHASE5575_TX_LIST_ADDR&t;&t;0x300&t;/* offset - 0xc00 */  
DECL|macro|IPHASE5575_RX_LIST_ADDR
mdefine_line|#define IPHASE5575_RX_LIST_ADDR&t;&t;0x380&t;/* offset - 0xe00 */  
multiline_comment|/*--------------------------- RAM ---------------------------*/
multiline_comment|/* These memory maps are actually offsets from the segmentation and reassembly  RAM base addresses */
multiline_comment|/* Segmentation Control Memory map */
DECL|macro|TX_DESC_BASE
mdefine_line|#define TX_DESC_BASE&t;0x0000&t;/* Buffer Decriptor Table */  
DECL|macro|TX_COMP_Q
mdefine_line|#define TX_COMP_Q&t;0x1000&t;/* Transmit Complete Queue */  
DECL|macro|PKT_RDY_Q
mdefine_line|#define PKT_RDY_Q&t;0x1400&t;/* Packet Ready Queue */  
DECL|macro|CBR_SCHED_TABLE
mdefine_line|#define CBR_SCHED_TABLE&t;0x1800&t;/* CBR Table */  
DECL|macro|UBR_SCHED_TABLE
mdefine_line|#define UBR_SCHED_TABLE&t;0x3000&t;/* UBR Table */  
DECL|macro|UBR_WAIT_Q
mdefine_line|#define UBR_WAIT_Q&t;0x4000&t;/* UBR Wait Queue */  
DECL|macro|ABR_SCHED_TABLE
mdefine_line|#define ABR_SCHED_TABLE&t;0x5000&t;/* ABR Table */  
DECL|macro|ABR_WAIT_Q
mdefine_line|#define ABR_WAIT_Q&t;0x5800&t;/* ABR Wait Queue */  
DECL|macro|EXT_VC_TABLE
mdefine_line|#define EXT_VC_TABLE&t;0x6000&t;/* Extended VC Table */  
DECL|macro|MAIN_VC_TABLE
mdefine_line|#define MAIN_VC_TABLE&t;0x8000&t;/* Main VC Table */  
DECL|macro|SCHEDSZ
mdefine_line|#define SCHEDSZ&t;&t;1024&t;/* ABR and UBR Scheduling Table size */  
DECL|macro|TX_DESC_TABLE_SZ
mdefine_line|#define TX_DESC_TABLE_SZ 128&t;/* Number of entries in the Transmit   &n;&t;&t;&t;&t;&t;Buffer Descriptor Table */  
multiline_comment|/* These are used as table offsets in Descriptor Table address generation */
DECL|macro|DESC_MODE
mdefine_line|#define DESC_MODE&t;0x0  
DECL|macro|VC_INDEX
mdefine_line|#define VC_INDEX&t;0x1  
DECL|macro|BYTE_CNT
mdefine_line|#define BYTE_CNT&t;0x3  
DECL|macro|PKT_START_HI
mdefine_line|#define PKT_START_HI&t;0x4  
DECL|macro|PKT_START_LO
mdefine_line|#define PKT_START_LO&t;0x5  
multiline_comment|/* Descriptor Mode Word Bits */
DECL|macro|EOM_EN
mdefine_line|#define EOM_EN&t;0x0800  
DECL|macro|AAL5
mdefine_line|#define AAL5&t;0x0100  
DECL|macro|APP_CRC32
mdefine_line|#define APP_CRC32 0x0400  
DECL|macro|CMPL_INT
mdefine_line|#define CMPL_INT  0x1000
DECL|macro|TABLE_ADDRESS
mdefine_line|#define TABLE_ADDRESS(db, dn, to) &bslash;&n;&t;(((unsigned long)(db &amp; 0x04)) &lt;&lt; 16) | (dn &lt;&lt; 5) | (to &lt;&lt; 1)  
multiline_comment|/* Reassembly Control Memory Map */
DECL|macro|RX_DESC_BASE
mdefine_line|#define RX_DESC_BASE&t;0x0000&t;/* Buffer Descriptor Table */  
DECL|macro|VP_TABLE
mdefine_line|#define VP_TABLE&t;0x5c00&t;/* VP Table */  
DECL|macro|EXCEPTION_Q
mdefine_line|#define EXCEPTION_Q&t;0x5e00&t;/* Exception Queue */  
DECL|macro|FREE_BUF_DESC_Q
mdefine_line|#define FREE_BUF_DESC_Q&t;0x6000&t;/* Free Buffer Descriptor Queue */  
DECL|macro|PKT_COMP_Q
mdefine_line|#define PKT_COMP_Q&t;0x6800&t;/* Packet Complete Queue */  
DECL|macro|REASS_TABLE
mdefine_line|#define REASS_TABLE&t;0x7000&t;/* Reassembly Table */  
DECL|macro|RX_VC_TABLE
mdefine_line|#define RX_VC_TABLE&t;0x7800&t;/* VC Table */  
DECL|macro|ABR_VC_TABLE
mdefine_line|#define ABR_VC_TABLE&t;0x8000&t;/* ABR VC Table */  
DECL|macro|RX_DESC_TABLE_SZ
mdefine_line|#define RX_DESC_TABLE_SZ 736&t;/* Number of entries in the Receive   &n;&t;&t;&t;&t;&t;Buffer Descriptor Table */  
DECL|macro|VP_TABLE_SZ
mdefine_line|#define VP_TABLE_SZ&t;256&t; /* Number of entries in VPTable */   
DECL|macro|RX_VC_TABLE_SZ
mdefine_line|#define RX_VC_TABLE_SZ &t;1024&t;/* Number of entries in VC Table */   
DECL|macro|REASS_TABLE_SZ
mdefine_line|#define REASS_TABLE_SZ &t;1024&t;/* Number of entries in Reassembly Table */  
multiline_comment|/* Buffer Descriptor Table */
DECL|macro|RX_ACT
mdefine_line|#define RX_ACT&t;0x8000  
DECL|macro|RX_VPVC
mdefine_line|#define RX_VPVC&t;0x4000  
DECL|macro|RX_CNG
mdefine_line|#define RX_CNG&t;0x0040  
DECL|macro|RX_CER
mdefine_line|#define RX_CER&t;0x0008  
DECL|macro|RX_PTE
mdefine_line|#define RX_PTE&t;0x0004  
DECL|macro|RX_OFL
mdefine_line|#define RX_OFL&t;0x0002  
DECL|macro|NUM_RX_EXCP
mdefine_line|#define NUM_RX_EXCP   32
multiline_comment|/* Reassembly Table */
DECL|macro|NO_AAL5_PKT
mdefine_line|#define NO_AAL5_PKT&t;0x0000  
DECL|macro|AAL5_PKT_REASSEMBLED
mdefine_line|#define AAL5_PKT_REASSEMBLED 0x4000  
DECL|macro|AAL5_PKT_TERMINATED
mdefine_line|#define AAL5_PKT_TERMINATED 0x8000  
DECL|macro|RAW_PKT
mdefine_line|#define RAW_PKT&t;&t;0xc000  
DECL|macro|REASS_ABR
mdefine_line|#define REASS_ABR&t;0x2000  
multiline_comment|/*-------------------- Base Registers --------------------*/
DECL|macro|REG_BASE
mdefine_line|#define REG_BASE IPHASE5575_BUS_CONTROL_REG_BASE  
DECL|macro|RAM_BASE
mdefine_line|#define RAM_BASE IPHASE5575_FRAG_CONTROL_RAM_BASE  
DECL|macro|PHY_BASE
mdefine_line|#define PHY_BASE IPHASE5575_FRONT_END_REG_BASE  
DECL|macro|SEG_BASE
mdefine_line|#define SEG_BASE IPHASE5575_FRAG_CONTROL_REG_BASE  
DECL|macro|REASS_BASE
mdefine_line|#define REASS_BASE IPHASE5575_REASS_CONTROL_REG_BASE  
DECL|typedef|freg_t
r_typedef
r_volatile
id|u_int
id|freg_t
suffix:semicolon
DECL|typedef|rreg_t
r_typedef
id|u_int
id|rreg_t
suffix:semicolon
DECL|struct|_ffredn_t
r_typedef
r_struct
id|_ffredn_t
(brace
DECL|member|idlehead_high
id|freg_t
id|idlehead_high
suffix:semicolon
multiline_comment|/* Idle cell header (high)              */
DECL|member|idlehead_low
id|freg_t
id|idlehead_low
suffix:semicolon
multiline_comment|/* Idle cell header (low)               */
DECL|member|maxrate
id|freg_t
id|maxrate
suffix:semicolon
multiline_comment|/* Maximum rate                         */
DECL|member|stparms
id|freg_t
id|stparms
suffix:semicolon
multiline_comment|/* Traffic Management Parameters        */
DECL|member|abrubr_abr
id|freg_t
id|abrubr_abr
suffix:semicolon
multiline_comment|/* ABRUBR Priority Byte 1, TCR Byte 0   */
DECL|member|rm_type
id|freg_t
id|rm_type
suffix:semicolon
multiline_comment|/*                                      */
DECL|member|filler5
id|u_int
id|filler5
(braket
l_int|0x17
op_minus
l_int|0x06
)braket
suffix:semicolon
DECL|member|cmd_reg
id|freg_t
id|cmd_reg
suffix:semicolon
multiline_comment|/* Command register                     */
DECL|member|filler18
id|u_int
id|filler18
(braket
l_int|0x20
op_minus
l_int|0x18
)braket
suffix:semicolon
DECL|member|cbr_base
id|freg_t
id|cbr_base
suffix:semicolon
multiline_comment|/* CBR Pointer Base                     */
DECL|member|vbr_base
id|freg_t
id|vbr_base
suffix:semicolon
multiline_comment|/* VBR Pointer Base                     */
DECL|member|abr_base
id|freg_t
id|abr_base
suffix:semicolon
multiline_comment|/* ABR Pointer Base                     */
DECL|member|ubr_base
id|freg_t
id|ubr_base
suffix:semicolon
multiline_comment|/* UBR Pointer Base                     */
DECL|member|filler24
id|u_int
id|filler24
suffix:semicolon
DECL|member|vbrwq_base
id|freg_t
id|vbrwq_base
suffix:semicolon
multiline_comment|/* VBR Wait Queue Base                  */
DECL|member|abrwq_base
id|freg_t
id|abrwq_base
suffix:semicolon
multiline_comment|/* ABR Wait Queue Base                  */
DECL|member|ubrwq_base
id|freg_t
id|ubrwq_base
suffix:semicolon
multiline_comment|/* UBR Wait Queue Base                  */
DECL|member|vct_base
id|freg_t
id|vct_base
suffix:semicolon
multiline_comment|/* Main VC Table Base                   */
DECL|member|vcte_base
id|freg_t
id|vcte_base
suffix:semicolon
multiline_comment|/* Extended Main VC Table Base          */
DECL|member|filler2a
id|u_int
id|filler2a
(braket
l_int|0x2C
op_minus
l_int|0x2A
)braket
suffix:semicolon
DECL|member|cbr_tab_beg
id|freg_t
id|cbr_tab_beg
suffix:semicolon
multiline_comment|/* CBR Table Begin                      */
DECL|member|cbr_tab_end
id|freg_t
id|cbr_tab_end
suffix:semicolon
multiline_comment|/* CBR Table End                        */
DECL|member|cbr_pointer
id|freg_t
id|cbr_pointer
suffix:semicolon
multiline_comment|/* CBR Pointer                          */
DECL|member|filler2f
id|u_int
id|filler2f
(braket
l_int|0x30
op_minus
l_int|0x2F
)braket
suffix:semicolon
DECL|member|prq_st_adr
id|freg_t
id|prq_st_adr
suffix:semicolon
multiline_comment|/* Packet Ready Queue Start Address     */
DECL|member|prq_ed_adr
id|freg_t
id|prq_ed_adr
suffix:semicolon
multiline_comment|/* Packet Ready Queue End Address       */
DECL|member|prq_rd_ptr
id|freg_t
id|prq_rd_ptr
suffix:semicolon
multiline_comment|/* Packet Ready Queue read pointer      */
DECL|member|prq_wr_ptr
id|freg_t
id|prq_wr_ptr
suffix:semicolon
multiline_comment|/* Packet Ready Queue write pointer     */
DECL|member|tcq_st_adr
id|freg_t
id|tcq_st_adr
suffix:semicolon
multiline_comment|/* Transmit Complete Queue Start Address*/
DECL|member|tcq_ed_adr
id|freg_t
id|tcq_ed_adr
suffix:semicolon
multiline_comment|/* Transmit Complete Queue End Address  */
DECL|member|tcq_rd_ptr
id|freg_t
id|tcq_rd_ptr
suffix:semicolon
multiline_comment|/* Transmit Complete Queue read pointer */
DECL|member|tcq_wr_ptr
id|freg_t
id|tcq_wr_ptr
suffix:semicolon
multiline_comment|/* Transmit Complete Queue write pointer*/
DECL|member|filler38
id|u_int
id|filler38
(braket
l_int|0x40
op_minus
l_int|0x38
)braket
suffix:semicolon
DECL|member|queue_base
id|freg_t
id|queue_base
suffix:semicolon
multiline_comment|/* Base address for PRQ and TCQ         */
DECL|member|desc_base
id|freg_t
id|desc_base
suffix:semicolon
multiline_comment|/* Base address of descriptor table     */
DECL|member|filler42
id|u_int
id|filler42
(braket
l_int|0x45
op_minus
l_int|0x42
)braket
suffix:semicolon
DECL|member|mode_reg_0
id|freg_t
id|mode_reg_0
suffix:semicolon
multiline_comment|/* Mode register 0                      */
DECL|member|mode_reg_1
id|freg_t
id|mode_reg_1
suffix:semicolon
multiline_comment|/* Mode register 1                      */
DECL|member|intr_status_reg
id|freg_t
id|intr_status_reg
suffix:semicolon
multiline_comment|/* Interrupt Status register            */
DECL|member|mask_reg
id|freg_t
id|mask_reg
suffix:semicolon
multiline_comment|/* Mask Register                        */
DECL|member|cell_ctr_high1
id|freg_t
id|cell_ctr_high1
suffix:semicolon
multiline_comment|/* Total cell transfer count (high)     */
DECL|member|cell_ctr_lo1
id|freg_t
id|cell_ctr_lo1
suffix:semicolon
multiline_comment|/* Total cell transfer count (low)      */
DECL|member|state_reg
id|freg_t
id|state_reg
suffix:semicolon
multiline_comment|/* Status register                      */
DECL|member|filler4c
id|u_int
id|filler4c
(braket
l_int|0x58
op_minus
l_int|0x4c
)braket
suffix:semicolon
DECL|member|curr_desc_num
id|freg_t
id|curr_desc_num
suffix:semicolon
multiline_comment|/* Contains the current descriptor num  */
DECL|member|next_desc
id|freg_t
id|next_desc
suffix:semicolon
multiline_comment|/* Next descriptor                      */
DECL|member|next_vc
id|freg_t
id|next_vc
suffix:semicolon
multiline_comment|/* Next VC                              */
DECL|member|filler5b
id|u_int
id|filler5b
(braket
l_int|0x5d
op_minus
l_int|0x5b
)braket
suffix:semicolon
DECL|member|present_slot_cnt
id|freg_t
id|present_slot_cnt
suffix:semicolon
multiline_comment|/* Present slot count                  */
DECL|member|filler5e
id|u_int
id|filler5e
(braket
l_int|0x6a
op_minus
l_int|0x5e
)braket
suffix:semicolon
DECL|member|new_desc_num
id|freg_t
id|new_desc_num
suffix:semicolon
multiline_comment|/* New descriptor number                */
DECL|member|new_vc
id|freg_t
id|new_vc
suffix:semicolon
multiline_comment|/* New VC                               */
DECL|member|sched_tbl_ptr
id|freg_t
id|sched_tbl_ptr
suffix:semicolon
multiline_comment|/* Schedule table pointer               */
DECL|member|vbrwq_wptr
id|freg_t
id|vbrwq_wptr
suffix:semicolon
multiline_comment|/* VBR wait queue write pointer         */
DECL|member|vbrwq_rptr
id|freg_t
id|vbrwq_rptr
suffix:semicolon
multiline_comment|/* VBR wait queue read pointer          */
DECL|member|abrwq_wptr
id|freg_t
id|abrwq_wptr
suffix:semicolon
multiline_comment|/* ABR wait queue write pointer         */
DECL|member|abrwq_rptr
id|freg_t
id|abrwq_rptr
suffix:semicolon
multiline_comment|/* ABR wait queue read pointer          */
DECL|member|ubrwq_wptr
id|freg_t
id|ubrwq_wptr
suffix:semicolon
multiline_comment|/* UBR wait queue write pointer         */
DECL|member|ubrwq_rptr
id|freg_t
id|ubrwq_rptr
suffix:semicolon
multiline_comment|/* UBR wait queue read pointer          */
DECL|member|cbr_vc
id|freg_t
id|cbr_vc
suffix:semicolon
multiline_comment|/* CBR VC                               */
DECL|member|vbr_sb_vc
id|freg_t
id|vbr_sb_vc
suffix:semicolon
multiline_comment|/* VBR SB VC                            */
DECL|member|abr_sb_vc
id|freg_t
id|abr_sb_vc
suffix:semicolon
multiline_comment|/* ABR SB VC                            */
DECL|member|ubr_sb_vc
id|freg_t
id|ubr_sb_vc
suffix:semicolon
multiline_comment|/* UBR SB VC                            */
DECL|member|vbr_next_link
id|freg_t
id|vbr_next_link
suffix:semicolon
multiline_comment|/* VBR next link                        */
DECL|member|abr_next_link
id|freg_t
id|abr_next_link
suffix:semicolon
multiline_comment|/* ABR next link                        */
DECL|member|ubr_next_link
id|freg_t
id|ubr_next_link
suffix:semicolon
multiline_comment|/* UBR next link                        */
DECL|member|filler7a
id|u_int
id|filler7a
(braket
l_int|0x7c
op_minus
l_int|0x7a
)braket
suffix:semicolon
DECL|member|out_rate_head
id|freg_t
id|out_rate_head
suffix:semicolon
multiline_comment|/* Out of rate head                     */
DECL|member|filler7d
id|u_int
id|filler7d
(braket
l_int|0xca
op_minus
l_int|0x7d
)braket
suffix:semicolon
multiline_comment|/* pad out to full address space   */
DECL|member|cell_ctr_high1_nc
id|freg_t
id|cell_ctr_high1_nc
suffix:semicolon
multiline_comment|/* Total cell transfer count (high)   */
DECL|member|cell_ctr_lo1_nc
id|freg_t
id|cell_ctr_lo1_nc
suffix:semicolon
multiline_comment|/* Total cell transfer count (low)      */
DECL|member|fillercc
id|u_int
id|fillercc
(braket
l_int|0x100
op_minus
l_int|0xcc
)braket
suffix:semicolon
multiline_comment|/* pad out to full address space   */
DECL|typedef|ffredn_t
)brace
id|ffredn_t
suffix:semicolon
DECL|struct|_rfredn_t
r_typedef
r_struct
id|_rfredn_t
(brace
DECL|member|mode_reg_0
id|rreg_t
id|mode_reg_0
suffix:semicolon
multiline_comment|/* Mode register 0                      */
DECL|member|protocol_id
id|rreg_t
id|protocol_id
suffix:semicolon
multiline_comment|/* Protocol ID                          */
DECL|member|mask_reg
id|rreg_t
id|mask_reg
suffix:semicolon
multiline_comment|/* Mask Register                        */
DECL|member|intr_status_reg
id|rreg_t
id|intr_status_reg
suffix:semicolon
multiline_comment|/* Interrupt status register            */
DECL|member|drp_pkt_cntr
id|rreg_t
id|drp_pkt_cntr
suffix:semicolon
multiline_comment|/* Dropped packet cntr (clear on read)  */
DECL|member|err_cntr
id|rreg_t
id|err_cntr
suffix:semicolon
multiline_comment|/* Error Counter (cleared on read)      */
DECL|member|filler6
id|u_int
id|filler6
(braket
l_int|0x08
op_minus
l_int|0x06
)braket
suffix:semicolon
DECL|member|raw_base_adr
id|rreg_t
id|raw_base_adr
suffix:semicolon
multiline_comment|/* Base addr for raw cell Q             */
DECL|member|filler2
id|u_int
id|filler2
(braket
l_int|0x0c
op_minus
l_int|0x09
)braket
suffix:semicolon
DECL|member|cell_ctr0
id|rreg_t
id|cell_ctr0
suffix:semicolon
multiline_comment|/* Cell Counter 0 (cleared when read)   */
DECL|member|cell_ctr1
id|rreg_t
id|cell_ctr1
suffix:semicolon
multiline_comment|/* Cell Counter 1 (cleared when read)   */
DECL|member|filler3
id|u_int
id|filler3
(braket
l_int|0x0f
op_minus
l_int|0x0e
)braket
suffix:semicolon
DECL|member|cmd_reg
id|rreg_t
id|cmd_reg
suffix:semicolon
multiline_comment|/* Command register                     */
DECL|member|desc_base
id|rreg_t
id|desc_base
suffix:semicolon
multiline_comment|/* Base address for description table   */
DECL|member|vc_lkup_base
id|rreg_t
id|vc_lkup_base
suffix:semicolon
multiline_comment|/* Base address for VC lookup table     */
DECL|member|reass_base
id|rreg_t
id|reass_base
suffix:semicolon
multiline_comment|/* Base address for reassembler table   */
DECL|member|queue_base
id|rreg_t
id|queue_base
suffix:semicolon
multiline_comment|/* Base address for Communication queue */
DECL|member|filler14
id|u_int
id|filler14
(braket
l_int|0x16
op_minus
l_int|0x14
)braket
suffix:semicolon
DECL|member|pkt_tm_cnt
id|rreg_t
id|pkt_tm_cnt
suffix:semicolon
multiline_comment|/* Packet Timeout and count register    */
DECL|member|tmout_range
id|rreg_t
id|tmout_range
suffix:semicolon
multiline_comment|/* Range of reassembley IDs for timeout */
DECL|member|intrvl_cntr
id|rreg_t
id|intrvl_cntr
suffix:semicolon
multiline_comment|/* Packet aging interval counter        */
DECL|member|tmout_indx
id|rreg_t
id|tmout_indx
suffix:semicolon
multiline_comment|/* index of pkt being tested for aging  */
DECL|member|filler1a
id|u_int
id|filler1a
(braket
l_int|0x1c
op_minus
l_int|0x1a
)braket
suffix:semicolon
DECL|member|vp_lkup_base
id|rreg_t
id|vp_lkup_base
suffix:semicolon
multiline_comment|/* Base address for VP lookup table     */
DECL|member|vp_filter
id|rreg_t
id|vp_filter
suffix:semicolon
multiline_comment|/* VP filter register                   */
DECL|member|abr_lkup_base
id|rreg_t
id|abr_lkup_base
suffix:semicolon
multiline_comment|/* Base address of ABR VC Table         */
DECL|member|filler1f
id|u_int
id|filler1f
(braket
l_int|0x24
op_minus
l_int|0x1f
)braket
suffix:semicolon
DECL|member|fdq_st_adr
id|rreg_t
id|fdq_st_adr
suffix:semicolon
multiline_comment|/* Free desc queue start address        */
DECL|member|fdq_ed_adr
id|rreg_t
id|fdq_ed_adr
suffix:semicolon
multiline_comment|/* Free desc queue end address          */
DECL|member|fdq_rd_ptr
id|rreg_t
id|fdq_rd_ptr
suffix:semicolon
multiline_comment|/* Free desc queue read pointer         */
DECL|member|fdq_wr_ptr
id|rreg_t
id|fdq_wr_ptr
suffix:semicolon
multiline_comment|/* Free desc queue write pointer        */
DECL|member|pcq_st_adr
id|rreg_t
id|pcq_st_adr
suffix:semicolon
multiline_comment|/* Packet Complete queue start address  */
DECL|member|pcq_ed_adr
id|rreg_t
id|pcq_ed_adr
suffix:semicolon
multiline_comment|/* Packet Complete queue end address    */
DECL|member|pcq_rd_ptr
id|rreg_t
id|pcq_rd_ptr
suffix:semicolon
multiline_comment|/* Packet Complete queue read pointer   */
DECL|member|pcq_wr_ptr
id|rreg_t
id|pcq_wr_ptr
suffix:semicolon
multiline_comment|/* Packet Complete queue write pointer  */
DECL|member|excp_st_adr
id|rreg_t
id|excp_st_adr
suffix:semicolon
multiline_comment|/* Exception queue start address        */
DECL|member|excp_ed_adr
id|rreg_t
id|excp_ed_adr
suffix:semicolon
multiline_comment|/* Exception queue end address          */
DECL|member|excp_rd_ptr
id|rreg_t
id|excp_rd_ptr
suffix:semicolon
multiline_comment|/* Exception queue read pointer         */
DECL|member|excp_wr_ptr
id|rreg_t
id|excp_wr_ptr
suffix:semicolon
multiline_comment|/* Exception queue write pointer        */
DECL|member|filler30
id|u_int
id|filler30
(braket
l_int|0x34
op_minus
l_int|0x30
)braket
suffix:semicolon
DECL|member|raw_st_adr
id|rreg_t
id|raw_st_adr
suffix:semicolon
multiline_comment|/* Raw Cell start address               */
DECL|member|raw_ed_adr
id|rreg_t
id|raw_ed_adr
suffix:semicolon
multiline_comment|/* Raw Cell end address                 */
DECL|member|raw_rd_ptr
id|rreg_t
id|raw_rd_ptr
suffix:semicolon
multiline_comment|/* Raw Cell read pointer                */
DECL|member|raw_wr_ptr
id|rreg_t
id|raw_wr_ptr
suffix:semicolon
multiline_comment|/* Raw Cell write pointer               */
DECL|member|state_reg
id|rreg_t
id|state_reg
suffix:semicolon
multiline_comment|/* State Register                       */
DECL|member|filler39
id|u_int
id|filler39
(braket
l_int|0x42
op_minus
l_int|0x39
)braket
suffix:semicolon
DECL|member|buf_size
id|rreg_t
id|buf_size
suffix:semicolon
multiline_comment|/* Buffer size                          */
DECL|member|filler43
id|u_int
id|filler43
suffix:semicolon
DECL|member|xtra_rm_offset
id|rreg_t
id|xtra_rm_offset
suffix:semicolon
multiline_comment|/* Offset of the additional turnaround RM */
DECL|member|filler45
id|u_int
id|filler45
(braket
l_int|0x84
op_minus
l_int|0x45
)braket
suffix:semicolon
DECL|member|drp_pkt_cntr_nc
id|rreg_t
id|drp_pkt_cntr_nc
suffix:semicolon
multiline_comment|/* Dropped Packet cntr, Not clear on rd */
DECL|member|err_cntr_nc
id|rreg_t
id|err_cntr_nc
suffix:semicolon
multiline_comment|/* Error Counter, Not clear on read     */
DECL|member|filler86
id|u_int
id|filler86
(braket
l_int|0x8c
op_minus
l_int|0x86
)braket
suffix:semicolon
DECL|member|cell_ctr0_nc
id|rreg_t
id|cell_ctr0_nc
suffix:semicolon
multiline_comment|/* Cell Counter 0,  Not clear on read   */
DECL|member|cell_ctr1_nc
id|rreg_t
id|cell_ctr1_nc
suffix:semicolon
multiline_comment|/* Cell Counter 1, Not clear on read    */
DECL|member|filler8e
id|u_int
id|filler8e
(braket
l_int|0x100
op_minus
l_int|0x8e
)braket
suffix:semicolon
multiline_comment|/* pad out to full address space   */
DECL|typedef|rfredn_t
)brace
id|rfredn_t
suffix:semicolon
r_typedef
r_struct
(brace
multiline_comment|/* Atlantic */
DECL|member|ffredn
id|ffredn_t
id|ffredn
suffix:semicolon
multiline_comment|/* F FRED                       */
DECL|member|rfredn
id|rfredn_t
id|rfredn
suffix:semicolon
multiline_comment|/* R FRED                       */
DECL|typedef|ia_regs_t
)brace
id|ia_regs_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|f_vc_type
id|u_short
id|f_vc_type
suffix:semicolon
multiline_comment|/* VC type              */
DECL|member|f_nrm
id|u_short
id|f_nrm
suffix:semicolon
multiline_comment|/* Nrm&t;&t;&t;*/
DECL|member|f_nrmexp
id|u_short
id|f_nrmexp
suffix:semicolon
multiline_comment|/* Nrm Exp              */
DECL|member|reserved6
id|u_short
id|reserved6
suffix:semicolon
multiline_comment|/* &t;&t;&t;*/
DECL|member|f_crm
id|u_short
id|f_crm
suffix:semicolon
multiline_comment|/* Crm&t;&t;&t;*/
DECL|member|reserved10
id|u_short
id|reserved10
suffix:semicolon
multiline_comment|/* Reserved&t;&t;*/
DECL|member|reserved12
id|u_short
id|reserved12
suffix:semicolon
multiline_comment|/* Reserved&t;&t;*/
DECL|member|reserved14
id|u_short
id|reserved14
suffix:semicolon
multiline_comment|/* Reserved&t;&t;*/
DECL|member|last_cell_slot
id|u_short
id|last_cell_slot
suffix:semicolon
multiline_comment|/* last_cell_slot_count&t;*/
DECL|member|f_pcr
id|u_short
id|f_pcr
suffix:semicolon
multiline_comment|/* Peak Cell Rate&t;*/
DECL|member|fraction
id|u_short
id|fraction
suffix:semicolon
multiline_comment|/* fraction&t;&t;*/
DECL|member|f_icr
id|u_short
id|f_icr
suffix:semicolon
multiline_comment|/* Initial Cell Rate&t;*/
DECL|member|f_cdf
id|u_short
id|f_cdf
suffix:semicolon
multiline_comment|/* */
DECL|member|f_mcr
id|u_short
id|f_mcr
suffix:semicolon
multiline_comment|/* Minimum Cell Rate&t;*/
DECL|member|f_acr
id|u_short
id|f_acr
suffix:semicolon
multiline_comment|/* Allowed Cell Rate&t;*/
DECL|member|f_status
id|u_short
id|f_status
suffix:semicolon
multiline_comment|/* */
DECL|typedef|f_vc_abr_entry
)brace
id|f_vc_abr_entry
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|r_status_rdf
id|u_short
id|r_status_rdf
suffix:semicolon
multiline_comment|/* status + RDF         */
DECL|member|r_air
id|u_short
id|r_air
suffix:semicolon
multiline_comment|/* AIR                  */
DECL|member|reserved4
id|u_short
id|reserved4
(braket
l_int|14
)braket
suffix:semicolon
multiline_comment|/* Reserved             */
DECL|typedef|r_vc_abr_entry
)brace
id|r_vc_abr_entry
suffix:semicolon
DECL|macro|MRM
mdefine_line|#define MRM 3
DECL|macro|MIN
mdefine_line|#define MIN(x,y)&t;((x) &lt; (y)) ? (x) : (y)
DECL|struct|srv_cls_param
r_typedef
r_struct
id|srv_cls_param
(brace
DECL|member|class_type
id|u32
id|class_type
suffix:semicolon
multiline_comment|/* CBR/VBR/ABR/UBR; use the enum above */
DECL|member|pcr
id|u32
id|pcr
suffix:semicolon
multiline_comment|/* Peak Cell Rate (24-bit) */
multiline_comment|/* VBR parameters */
DECL|member|scr
id|u32
id|scr
suffix:semicolon
multiline_comment|/* sustainable cell rate */
DECL|member|max_burst_size
id|u32
id|max_burst_size
suffix:semicolon
multiline_comment|/* ?? cell rate or data rate */
multiline_comment|/* ABR only UNI 4.0 Parameters */
DECL|member|mcr
id|u32
id|mcr
suffix:semicolon
multiline_comment|/* Min Cell Rate (24-bit) */
DECL|member|icr
id|u32
id|icr
suffix:semicolon
multiline_comment|/* Initial Cell Rate (24-bit) */
DECL|member|tbe
id|u32
id|tbe
suffix:semicolon
multiline_comment|/* Transient Buffer Exposure (24-bit) */
DECL|member|frtt
id|u32
id|frtt
suffix:semicolon
multiline_comment|/* Fixed Round Trip Time (24-bit) */
macro_line|#if 0   /* Additional Parameters of TM 4.0 */
id|bits
l_int|31
l_int|30
l_int|29
l_int|28
l_int|27
op_minus
l_int|25
l_int|24
op_minus
l_int|22
l_int|21
op_minus
l_int|19
l_int|18
op_minus
l_int|9
op_decrement
op_decrement
op_decrement
op_decrement
op_decrement
op_decrement
op_decrement
op_decrement
op_decrement
op_decrement
op_decrement
op_decrement
op_decrement
op_decrement
op_decrement
op_decrement
op_decrement
op_decrement
op_decrement
op_decrement
op_decrement
op_decrement
op_decrement
op_decrement
op_decrement
op_decrement
op_decrement
op_decrement
op_decrement
op_decrement
op_decrement
op_decrement
op_decrement
op_decrement
op_decrement
op_decrement
op_decrement
op_decrement
op_minus
op_or
id|NRM
id|present
op_or
id|TRM
id|prsnt
op_or
id|CDF
id|prsnt
op_or
id|ADTF
id|prsnt
op_or
id|NRM
op_or
id|TRM
op_or
id|CDF
op_or
id|ADTF
op_or
op_decrement
op_decrement
op_decrement
op_decrement
op_decrement
op_decrement
op_decrement
op_decrement
op_decrement
op_decrement
op_decrement
op_decrement
op_decrement
op_decrement
op_decrement
op_decrement
op_decrement
op_decrement
op_decrement
op_decrement
op_decrement
op_decrement
op_decrement
op_decrement
op_decrement
op_decrement
op_decrement
op_decrement
op_decrement
op_decrement
op_decrement
op_decrement
op_decrement
op_decrement
op_decrement
op_decrement
op_decrement
op_decrement
op_minus
macro_line|#endif /* 0 */
DECL|member|nrm
id|u8
id|nrm
suffix:semicolon
multiline_comment|/* Max # of Cells for each forward RM&n;                                        cell (3-bit) */
DECL|member|trm
id|u8
id|trm
suffix:semicolon
multiline_comment|/* Time between forward RM cells (3-bit) */
DECL|member|adtf
id|u16
id|adtf
suffix:semicolon
multiline_comment|/* ACR Decrease Time Factor (10-bit) */
DECL|member|cdf
id|u8
id|cdf
suffix:semicolon
multiline_comment|/* Cutoff Decrease Factor (3-bit) */
DECL|member|rif
id|u8
id|rif
suffix:semicolon
multiline_comment|/* Rate Increment Factor (4-bit) */
DECL|member|rdf
id|u8
id|rdf
suffix:semicolon
multiline_comment|/* Rate Decrease Factor (4-bit) */
DECL|member|reserved
id|u8
id|reserved
suffix:semicolon
multiline_comment|/* 8 bits to keep structure word aligned */
DECL|typedef|srv_cls_param_t
)brace
id|srv_cls_param_t
suffix:semicolon
DECL|struct|testTable_t
r_struct
id|testTable_t
(brace
DECL|member|lastTime
id|u16
id|lastTime
suffix:semicolon
DECL|member|fract
id|u16
id|fract
suffix:semicolon
DECL|member|vc_status
id|u8
id|vc_status
suffix:semicolon
)brace
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|vci
id|u16
id|vci
suffix:semicolon
DECL|member|error
id|u16
id|error
suffix:semicolon
DECL|typedef|RX_ERROR_Q
)brace
id|RX_ERROR_Q
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|active
id|u8
id|active
suffix:colon
l_int|1
suffix:semicolon
DECL|member|abr
id|u8
id|abr
suffix:colon
l_int|1
suffix:semicolon
DECL|member|ubr
id|u8
id|ubr
suffix:colon
l_int|1
suffix:semicolon
DECL|member|cnt
id|u8
id|cnt
suffix:colon
l_int|5
suffix:semicolon
DECL|macro|VC_ACTIVE
mdefine_line|#define VC_ACTIVE &t;0x01
DECL|macro|VC_ABR
mdefine_line|#define VC_ABR&t;&t;0x02
DECL|macro|VC_UBR
mdefine_line|#define VC_UBR&t;&t;0x04
DECL|typedef|vcstatus_t
)brace
id|vcstatus_t
suffix:semicolon
DECL|struct|ia_rfL_t
r_struct
id|ia_rfL_t
(brace
DECL|member|fdq_st
id|u32
id|fdq_st
suffix:semicolon
multiline_comment|/* Free desc queue start address        */
DECL|member|fdq_ed
id|u32
id|fdq_ed
suffix:semicolon
multiline_comment|/* Free desc queue end address          */
DECL|member|fdq_rd
id|u32
id|fdq_rd
suffix:semicolon
multiline_comment|/* Free desc queue read pointer         */
DECL|member|fdq_wr
id|u32
id|fdq_wr
suffix:semicolon
multiline_comment|/* Free desc queue write pointer        */
DECL|member|pcq_st
id|u32
id|pcq_st
suffix:semicolon
multiline_comment|/* Packet Complete queue start address  */
DECL|member|pcq_ed
id|u32
id|pcq_ed
suffix:semicolon
multiline_comment|/* Packet Complete queue end address    */
DECL|member|pcq_rd
id|u32
id|pcq_rd
suffix:semicolon
multiline_comment|/* Packet Complete queue read pointer   */
DECL|member|pcq_wr
id|u32
id|pcq_wr
suffix:semicolon
multiline_comment|/* Packet Complete queue write pointer  */
)brace
suffix:semicolon
DECL|struct|ia_ffL_t
r_struct
id|ia_ffL_t
(brace
DECL|member|prq_st
id|u32
id|prq_st
suffix:semicolon
multiline_comment|/* Packet Ready Queue Start Address     */
DECL|member|prq_ed
id|u32
id|prq_ed
suffix:semicolon
multiline_comment|/* Packet Ready Queue End Address       */
DECL|member|prq_wr
id|u32
id|prq_wr
suffix:semicolon
multiline_comment|/* Packet Ready Queue write pointer     */
DECL|member|tcq_st
id|u32
id|tcq_st
suffix:semicolon
multiline_comment|/* Transmit Complete Queue Start Address*/
DECL|member|tcq_ed
id|u32
id|tcq_ed
suffix:semicolon
multiline_comment|/* Transmit Complete Queue End Address  */
DECL|member|tcq_rd
id|u32
id|tcq_rd
suffix:semicolon
multiline_comment|/* Transmit Complete Queue read pointer */
)brace
suffix:semicolon
DECL|struct|desc_tbl_t
r_struct
id|desc_tbl_t
(brace
DECL|member|timestamp
id|u32
id|timestamp
suffix:semicolon
DECL|member|iavcc
r_struct
id|ia_vcc
op_star
id|iavcc
suffix:semicolon
DECL|member|txskb
r_struct
id|sk_buff
op_star
id|txskb
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ia_rtn_q
r_typedef
r_struct
id|ia_rtn_q
(brace
DECL|member|data
r_struct
id|desc_tbl_t
id|data
suffix:semicolon
DECL|member|next
DECL|member|tail
r_struct
id|ia_rtn_q
op_star
id|next
comma
op_star
id|tail
suffix:semicolon
DECL|typedef|IARTN_Q
)brace
id|IARTN_Q
suffix:semicolon
DECL|macro|SUNI_LOSV
mdefine_line|#define SUNI_LOSV   &t;0x04
r_typedef
r_struct
(brace
DECL|member|suni_master_reset
id|u32
id|suni_master_reset
suffix:semicolon
multiline_comment|/* SUNI Master Reset and Identity     */
DECL|member|suni_master_config
id|u32
id|suni_master_config
suffix:semicolon
multiline_comment|/* SUNI Master Configuration          */
DECL|member|suni_master_intr_stat
id|u32
id|suni_master_intr_stat
suffix:semicolon
multiline_comment|/* SUNI Master Interrupt Status       */
DECL|member|suni_reserved1
id|u32
id|suni_reserved1
suffix:semicolon
multiline_comment|/* Reserved                           */
DECL|member|suni_master_clk_monitor
id|u32
id|suni_master_clk_monitor
suffix:semicolon
multiline_comment|/* SUNI Master Clock Monitor          */
DECL|member|suni_master_control
id|u32
id|suni_master_control
suffix:semicolon
multiline_comment|/* SUNI Master Clock Monitor          */
DECL|member|suni_reserved2
id|u32
id|suni_reserved2
(braket
l_int|10
)braket
suffix:semicolon
multiline_comment|/* Reserved                           */
DECL|member|suni_rsop_control
id|u32
id|suni_rsop_control
suffix:semicolon
multiline_comment|/* RSOP Control/Interrupt Enable      */
DECL|member|suni_rsop_status
id|u32
id|suni_rsop_status
suffix:semicolon
multiline_comment|/* RSOP Status/Interrupt States       */
DECL|member|suni_rsop_section_bip8l
id|u32
id|suni_rsop_section_bip8l
suffix:semicolon
multiline_comment|/* RSOP Section BIP-8 LSB             */
DECL|member|suni_rsop_section_bip8m
id|u32
id|suni_rsop_section_bip8m
suffix:semicolon
multiline_comment|/* RSOP Section BIP-8 MSB             */
DECL|member|suni_tsop_control
id|u32
id|suni_tsop_control
suffix:semicolon
multiline_comment|/* TSOP Control                       */
DECL|member|suni_tsop_diag
id|u32
id|suni_tsop_diag
suffix:semicolon
multiline_comment|/* TSOP Disgnostics                   */
DECL|member|suni_tsop_reserved
id|u32
id|suni_tsop_reserved
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* TSOP Reserved                      */
DECL|member|suni_rlop_cs
id|u32
id|suni_rlop_cs
suffix:semicolon
multiline_comment|/* RLOP Control/Status                */
DECL|member|suni_rlop_intr
id|u32
id|suni_rlop_intr
suffix:semicolon
multiline_comment|/* RLOP Interrupt Enable/Status       */
DECL|member|suni_rlop_line_bip24l
id|u32
id|suni_rlop_line_bip24l
suffix:semicolon
multiline_comment|/* RLOP Line BIP-24 LSB               */
DECL|member|suni_rlop_line_bip24
id|u32
id|suni_rlop_line_bip24
suffix:semicolon
multiline_comment|/* RLOP Line BIP-24                   */
DECL|member|suni_rlop_line_bip24m
id|u32
id|suni_rlop_line_bip24m
suffix:semicolon
multiline_comment|/* RLOP Line BIP-24 MSB               */
DECL|member|suni_rlop_line_febel
id|u32
id|suni_rlop_line_febel
suffix:semicolon
multiline_comment|/* RLOP Line FEBE LSB                 */
DECL|member|suni_rlop_line_febe
id|u32
id|suni_rlop_line_febe
suffix:semicolon
multiline_comment|/* RLOP Line FEBE                     */
DECL|member|suni_rlop_line_febem
id|u32
id|suni_rlop_line_febem
suffix:semicolon
multiline_comment|/* RLOP Line FEBE MSB                 */
DECL|member|suni_tlop_control
id|u32
id|suni_tlop_control
suffix:semicolon
multiline_comment|/* TLOP Control                       */
DECL|member|suni_tlop_disg
id|u32
id|suni_tlop_disg
suffix:semicolon
multiline_comment|/* TLOP Disgnostics                   */
DECL|member|suni_tlop_reserved
id|u32
id|suni_tlop_reserved
(braket
l_int|14
)braket
suffix:semicolon
multiline_comment|/* TLOP Reserved                      */
DECL|member|suni_rpop_cs
id|u32
id|suni_rpop_cs
suffix:semicolon
multiline_comment|/* RPOP Status/Control                */
DECL|member|suni_rpop_intr
id|u32
id|suni_rpop_intr
suffix:semicolon
multiline_comment|/* RPOP Interrupt/Status              */
DECL|member|suni_rpop_reserved
id|u32
id|suni_rpop_reserved
suffix:semicolon
multiline_comment|/* RPOP Reserved                      */
DECL|member|suni_rpop_intr_ena
id|u32
id|suni_rpop_intr_ena
suffix:semicolon
multiline_comment|/* RPOP Interrupt Enable              */
DECL|member|suni_rpop_reserved1
id|u32
id|suni_rpop_reserved1
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* RPOP Reserved                      */
DECL|member|suni_rpop_path_sig
id|u32
id|suni_rpop_path_sig
suffix:semicolon
multiline_comment|/* RPOP Path Signal Label             */
DECL|member|suni_rpop_bip8l
id|u32
id|suni_rpop_bip8l
suffix:semicolon
multiline_comment|/* RPOP Path BIP-8 LSB                */
DECL|member|suni_rpop_bip8m
id|u32
id|suni_rpop_bip8m
suffix:semicolon
multiline_comment|/* RPOP Path BIP-8 MSB                */
DECL|member|suni_rpop_febel
id|u32
id|suni_rpop_febel
suffix:semicolon
multiline_comment|/* RPOP Path FEBE LSB                 */
DECL|member|suni_rpop_febem
id|u32
id|suni_rpop_febem
suffix:semicolon
multiline_comment|/* RPOP Path FEBE MSB                 */
DECL|member|suni_rpop_reserved2
id|u32
id|suni_rpop_reserved2
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* RPOP Reserved                      */
DECL|member|suni_tpop_cntrl_daig
id|u32
id|suni_tpop_cntrl_daig
suffix:semicolon
multiline_comment|/* TPOP Control/Disgnostics           */
DECL|member|suni_tpop_pointer_ctrl
id|u32
id|suni_tpop_pointer_ctrl
suffix:semicolon
multiline_comment|/* TPOP Pointer Control               */
DECL|member|suni_tpop_sourcer_ctrl
id|u32
id|suni_tpop_sourcer_ctrl
suffix:semicolon
multiline_comment|/* TPOP Source Control                */
DECL|member|suni_tpop_reserved1
id|u32
id|suni_tpop_reserved1
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* TPOP Reserved                      */
DECL|member|suni_tpop_arb_prtl
id|u32
id|suni_tpop_arb_prtl
suffix:semicolon
multiline_comment|/* TPOP Arbitrary Pointer LSB         */
DECL|member|suni_tpop_arb_prtm
id|u32
id|suni_tpop_arb_prtm
suffix:semicolon
multiline_comment|/* TPOP Arbitrary Pointer MSB         */
DECL|member|suni_tpop_reserved2
id|u32
id|suni_tpop_reserved2
suffix:semicolon
multiline_comment|/* TPOP Reserved                      */
DECL|member|suni_tpop_path_sig
id|u32
id|suni_tpop_path_sig
suffix:semicolon
multiline_comment|/* TPOP Path Signal Lable             */
DECL|member|suni_tpop_path_status
id|u32
id|suni_tpop_path_status
suffix:semicolon
multiline_comment|/* TPOP Path Status                   */
DECL|member|suni_tpop_reserved3
id|u32
id|suni_tpop_reserved3
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* TPOP Reserved                      */
DECL|member|suni_racp_cs
id|u32
id|suni_racp_cs
suffix:semicolon
multiline_comment|/* RACP Control/Status                */
DECL|member|suni_racp_intr
id|u32
id|suni_racp_intr
suffix:semicolon
multiline_comment|/* RACP Interrupt Enable/Status       */
DECL|member|suni_racp_hdr_pattern
id|u32
id|suni_racp_hdr_pattern
suffix:semicolon
multiline_comment|/* RACP Match Header Pattern          */
DECL|member|suni_racp_hdr_mask
id|u32
id|suni_racp_hdr_mask
suffix:semicolon
multiline_comment|/* RACP Match Header Mask             */
DECL|member|suni_racp_corr_hcs
id|u32
id|suni_racp_corr_hcs
suffix:semicolon
multiline_comment|/* RACP Correctable HCS Error Count   */
DECL|member|suni_racp_uncorr_hcs
id|u32
id|suni_racp_uncorr_hcs
suffix:semicolon
multiline_comment|/* RACP Uncorrectable HCS Error Count */
DECL|member|suni_racp_reserved
id|u32
id|suni_racp_reserved
(braket
l_int|10
)braket
suffix:semicolon
multiline_comment|/* RACP Reserved                      */
DECL|member|suni_tacp_control
id|u32
id|suni_tacp_control
suffix:semicolon
multiline_comment|/* TACP Control                       */
DECL|member|suni_tacp_idle_hdr_pat
id|u32
id|suni_tacp_idle_hdr_pat
suffix:semicolon
multiline_comment|/* TACP Idle Cell Header Pattern      */
DECL|member|suni_tacp_idle_pay_pay
id|u32
id|suni_tacp_idle_pay_pay
suffix:semicolon
multiline_comment|/* TACP Idle Cell Payld Octet Pattern */
DECL|member|suni_tacp_reserved
id|u32
id|suni_tacp_reserved
(braket
l_int|5
)braket
suffix:semicolon
multiline_comment|/* TACP Reserved                      */
DECL|member|suni_reserved3
id|u32
id|suni_reserved3
(braket
l_int|24
)braket
suffix:semicolon
multiline_comment|/* Reserved                           */
DECL|member|suni_master_test
id|u32
id|suni_master_test
suffix:semicolon
multiline_comment|/* SUNI Master Test                   */
DECL|member|suni_reserved_test
id|u32
id|suni_reserved_test
suffix:semicolon
multiline_comment|/* SUNI Reserved for Test             */
DECL|typedef|IA_SUNI
)brace
id|IA_SUNI
suffix:semicolon
DECL|struct|_SUNI_STATS_
r_typedef
r_struct
id|_SUNI_STATS_
(brace
DECL|member|valid
id|u32
id|valid
suffix:semicolon
singleline_comment|// 1 = oc3 PHY card
DECL|member|carrier_detect
id|u32
id|carrier_detect
suffix:semicolon
singleline_comment|// GPIN input
singleline_comment|// RSOP: receive section overhead processor
DECL|member|rsop_oof_state
id|u16
id|rsop_oof_state
suffix:semicolon
singleline_comment|// 1 = out of frame
DECL|member|rsop_lof_state
id|u16
id|rsop_lof_state
suffix:semicolon
singleline_comment|// 1 = loss of frame
DECL|member|rsop_los_state
id|u16
id|rsop_los_state
suffix:semicolon
singleline_comment|// 1 = loss of signal
DECL|member|rsop_los_count
id|u32
id|rsop_los_count
suffix:semicolon
singleline_comment|// loss of signal count
DECL|member|rsop_bse_count
id|u32
id|rsop_bse_count
suffix:semicolon
singleline_comment|// section BIP-8 error count
singleline_comment|// RLOP: receive line overhead processor
DECL|member|rlop_ferf_state
id|u16
id|rlop_ferf_state
suffix:semicolon
singleline_comment|// 1 = far end receive failure
DECL|member|rlop_lais_state
id|u16
id|rlop_lais_state
suffix:semicolon
singleline_comment|// 1 = line AIS
DECL|member|rlop_lbe_count
id|u32
id|rlop_lbe_count
suffix:semicolon
singleline_comment|// BIP-24 count
DECL|member|rlop_febe_count
id|u32
id|rlop_febe_count
suffix:semicolon
singleline_comment|// FEBE count;
singleline_comment|// RPOP: receive path overhead processor
DECL|member|rpop_lop_state
id|u16
id|rpop_lop_state
suffix:semicolon
singleline_comment|// 1 = LOP
DECL|member|rpop_pais_state
id|u16
id|rpop_pais_state
suffix:semicolon
singleline_comment|// 1 = path AIS
DECL|member|rpop_pyel_state
id|u16
id|rpop_pyel_state
suffix:semicolon
singleline_comment|// 1 = path yellow alert
DECL|member|rpop_bip_count
id|u32
id|rpop_bip_count
suffix:semicolon
singleline_comment|// path BIP-8 error count
DECL|member|rpop_febe_count
id|u32
id|rpop_febe_count
suffix:semicolon
singleline_comment|// path FEBE error count
DECL|member|rpop_psig
id|u16
id|rpop_psig
suffix:semicolon
singleline_comment|// path signal label value
singleline_comment|// RACP: receive ATM cell processor
DECL|member|racp_hp_state
id|u16
id|racp_hp_state
suffix:semicolon
singleline_comment|// hunt/presync state
DECL|member|racp_fu_count
id|u32
id|racp_fu_count
suffix:semicolon
singleline_comment|// FIFO underrun count
DECL|member|racp_fo_count
id|u32
id|racp_fo_count
suffix:semicolon
singleline_comment|// FIFO overrun count
DECL|member|racp_chcs_count
id|u32
id|racp_chcs_count
suffix:semicolon
singleline_comment|// correctable HCS error count
DECL|member|racp_uchcs_count
id|u32
id|racp_uchcs_count
suffix:semicolon
singleline_comment|// uncorrectable HCS error count
DECL|typedef|IA_SUNI_STATS
)brace
id|IA_SUNI_STATS
suffix:semicolon
DECL|struct|iadev_t
r_typedef
r_struct
id|iadev_t
(brace
multiline_comment|/*-----base pointers into (i)chipSAR+ address space */
DECL|member|phy
id|u32
op_star
id|phy
suffix:semicolon
multiline_comment|/* base pointer into phy(SUNI) */
DECL|member|dma
id|u32
op_star
id|dma
suffix:semicolon
multiline_comment|/* base pointer into DMA control   &n;&t;&t;&t;&t;&t;&t;registers */
DECL|member|reg
id|u32
op_star
id|reg
suffix:semicolon
multiline_comment|/* base pointer to SAR registers  &n;&t;&t;&t;&t;&t;   - Bus Interface Control Regs */
DECL|member|seg_reg
id|u32
op_star
id|seg_reg
suffix:semicolon
multiline_comment|/* base pointer to segmentation engine  &n;&t;&t;&t;&t;&t;&t;internal registers */
DECL|member|reass_reg
id|u32
op_star
id|reass_reg
suffix:semicolon
multiline_comment|/* base pointer to reassemble engine  &n;&t;&t;&t;&t;&t;&t;internal registers */
DECL|member|ram
id|u32
op_star
id|ram
suffix:semicolon
multiline_comment|/* base pointer to SAR RAM */
DECL|member|seg_ram
r_int
r_int
id|seg_ram
suffix:semicolon
DECL|member|reass_ram
r_int
r_int
id|reass_ram
suffix:semicolon
DECL|member|tx_dle_q
r_struct
id|dle_q
id|tx_dle_q
suffix:semicolon
DECL|member|tx_free_desc_qhead
r_struct
id|free_desc_q
op_star
id|tx_free_desc_qhead
suffix:semicolon
DECL|member|tx_dma_q
DECL|member|tx_backlog
r_struct
id|sk_buff_head
id|tx_dma_q
comma
id|tx_backlog
suffix:semicolon
DECL|member|tx_lock
id|spinlock_t
id|tx_lock
suffix:semicolon
DECL|member|tx_return_q
id|IARTN_Q
id|tx_return_q
suffix:semicolon
DECL|member|close_pending
id|u32
id|close_pending
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &gt;= 0x20303
DECL|member|close_wait
id|wait_queue_head_t
id|close_wait
suffix:semicolon
DECL|member|timeout_wait
id|wait_queue_head_t
id|timeout_wait
suffix:semicolon
macro_line|#else
DECL|member|close_wait
r_struct
id|wait_queue
op_star
id|close_wait
suffix:semicolon
DECL|member|timeout_wait
r_struct
id|wait_queue
op_star
id|timeout_wait
suffix:semicolon
macro_line|#endif
DECL|member|tx_buf
id|caddr_t
op_star
id|tx_buf
suffix:semicolon
DECL|member|num_tx_desc
DECL|member|tx_buf_sz
DECL|member|rate_limit
id|u16
id|num_tx_desc
comma
id|tx_buf_sz
comma
id|rate_limit
suffix:semicolon
DECL|member|tx_cell_cnt
DECL|member|tx_pkt_cnt
id|u32
id|tx_cell_cnt
comma
id|tx_pkt_cnt
suffix:semicolon
DECL|member|MAIN_VC_TABLE_ADDR
DECL|member|EXT_VC_TABLE_ADDR
DECL|member|ABR_SCHED_TABLE_ADDR
id|u32
id|MAIN_VC_TABLE_ADDR
comma
id|EXT_VC_TABLE_ADDR
comma
id|ABR_SCHED_TABLE_ADDR
suffix:semicolon
DECL|member|rx_dle_q
r_struct
id|dle_q
id|rx_dle_q
suffix:semicolon
DECL|member|rx_free_desc_qhead
r_struct
id|free_desc_q
op_star
id|rx_free_desc_qhead
suffix:semicolon
DECL|member|rx_dma_q
r_struct
id|sk_buff_head
id|rx_dma_q
suffix:semicolon
DECL|member|rx_lock
DECL|member|misc_lock
id|spinlock_t
id|rx_lock
comma
id|misc_lock
suffix:semicolon
DECL|member|rx_open
r_struct
id|atm_vcc
op_star
op_star
id|rx_open
suffix:semicolon
multiline_comment|/* list of all open VCs */
DECL|member|num_rx_desc
DECL|member|rx_buf_sz
DECL|member|rxing
id|u16
id|num_rx_desc
comma
id|rx_buf_sz
comma
id|rxing
suffix:semicolon
DECL|member|rx_pkt_ram
DECL|member|rx_tmp_cnt
DECL|member|rx_tmp_jif
id|u32
id|rx_pkt_ram
comma
id|rx_tmp_cnt
comma
id|rx_tmp_jif
suffix:semicolon
DECL|member|RX_DESC_BASE_ADDR
id|u32
id|RX_DESC_BASE_ADDR
suffix:semicolon
DECL|member|drop_rxpkt
DECL|member|drop_rxcell
DECL|member|rx_cell_cnt
DECL|member|rx_pkt_cnt
id|u32
id|drop_rxpkt
comma
id|drop_rxcell
comma
id|rx_cell_cnt
comma
id|rx_pkt_cnt
suffix:semicolon
DECL|member|next_board
r_struct
id|atm_dev
op_star
id|next_board
suffix:semicolon
multiline_comment|/* other iphase devices */
DECL|member|pci
r_struct
id|pci_dev
op_star
id|pci
suffix:semicolon
DECL|member|mem
r_int
id|mem
suffix:semicolon
DECL|member|base_diff
r_int
r_int
id|base_diff
suffix:semicolon
multiline_comment|/* virtual - real base address */
DECL|member|real_base
DECL|member|base
r_int
r_int
id|real_base
comma
id|base
suffix:semicolon
multiline_comment|/* real and virtual base address */
DECL|member|pci_map_size
r_int
r_int
id|pci_map_size
suffix:semicolon
multiline_comment|/*pci map size of board */
DECL|member|irq
r_int
r_char
id|irq
suffix:semicolon
DECL|member|bus
r_int
r_char
id|bus
suffix:semicolon
DECL|member|dev_fn
r_int
r_char
id|dev_fn
suffix:semicolon
DECL|member|phy_type
id|u_short
id|phy_type
suffix:semicolon
DECL|member|num_vc
DECL|member|memSize
DECL|member|memType
id|u_short
id|num_vc
comma
id|memSize
comma
id|memType
suffix:semicolon
DECL|member|ffL
r_struct
id|ia_ffL_t
id|ffL
suffix:semicolon
DECL|member|rfL
r_struct
id|ia_rfL_t
id|rfL
suffix:semicolon
multiline_comment|/* Suni stat */
singleline_comment|// IA_SUNI_STATS suni_stats;
DECL|member|carrier_detect
r_int
r_char
id|carrier_detect
suffix:semicolon
multiline_comment|/* CBR related */
singleline_comment|// transmit DMA &amp; Receive
DECL|member|tx_dma_cnt
r_int
r_int
id|tx_dma_cnt
suffix:semicolon
singleline_comment|// number of elements on dma queue
DECL|member|rx_dma_cnt
r_int
r_int
id|rx_dma_cnt
suffix:semicolon
singleline_comment|// number of elements on rx dma queue
DECL|member|NumEnabledCBR
r_int
r_int
id|NumEnabledCBR
suffix:semicolon
singleline_comment|// number of CBR VCI&squot;s enabled.     CBR
singleline_comment|// receive MARK  for Cell FIFO
DECL|member|rx_mark_cnt
r_int
r_int
id|rx_mark_cnt
suffix:semicolon
singleline_comment|// number of elements on mark queue
DECL|member|CbrTotEntries
r_int
r_int
id|CbrTotEntries
suffix:semicolon
singleline_comment|// Total CBR Entries in Scheduling Table.
DECL|member|CbrRemEntries
r_int
r_int
id|CbrRemEntries
suffix:semicolon
singleline_comment|// Remaining CBR Entries in Scheduling Table.
DECL|member|CbrEntryPt
r_int
r_int
id|CbrEntryPt
suffix:semicolon
singleline_comment|// CBR Sched Table Entry Point.
DECL|member|Granularity
r_int
r_int
id|Granularity
suffix:semicolon
singleline_comment|// CBR Granularity given Table Size.
multiline_comment|/* ABR related */
DECL|member|sum_mcr
DECL|member|sum_cbr
DECL|member|LineRate
r_int
r_int
id|sum_mcr
comma
id|sum_cbr
comma
id|LineRate
suffix:semicolon
DECL|member|n_abr
r_int
r_int
id|n_abr
suffix:semicolon
DECL|member|desc_tbl
r_struct
id|desc_tbl_t
op_star
id|desc_tbl
suffix:semicolon
DECL|member|host_tcq_wr
id|u_short
id|host_tcq_wr
suffix:semicolon
DECL|member|testTable
r_struct
id|testTable_t
op_star
op_star
id|testTable
suffix:semicolon
DECL|typedef|IADEV
)brace
id|IADEV
suffix:semicolon
DECL|macro|INPH_IA_DEV
mdefine_line|#define INPH_IA_DEV(d) ((IADEV *) (d)-&gt;dev_data)  
DECL|macro|INPH_IA_VCC
mdefine_line|#define INPH_IA_VCC(v) ((struct ia_vcc *) (v)-&gt;dev_data)  
multiline_comment|/******************* IDT77105 25MB/s PHY DEFINE *****************************/
r_typedef
r_struct
(brace
DECL|member|mb25_master_ctrl
id|u_int
id|mb25_master_ctrl
suffix:semicolon
multiline_comment|/* Master control&t;&t;     */
DECL|member|mb25_intr_status
id|u_int
id|mb25_intr_status
suffix:semicolon
multiline_comment|/* Interrupt status&t;&t;     */
DECL|member|mb25_diag_control
id|u_int
id|mb25_diag_control
suffix:semicolon
multiline_comment|/* Diagnostic control&t;&t;     */
DECL|member|mb25_led_hec
id|u_int
id|mb25_led_hec
suffix:semicolon
multiline_comment|/* LED driver and HEC status/control */
DECL|member|mb25_low_byte_counter
id|u_int
id|mb25_low_byte_counter
suffix:semicolon
multiline_comment|/* Low byte counter&t;&t;     */
DECL|member|mb25_high_byte_counter
id|u_int
id|mb25_high_byte_counter
suffix:semicolon
multiline_comment|/* High byte counter&t;&t;     */
DECL|typedef|ia_mb25_t
)brace
id|ia_mb25_t
suffix:semicolon
multiline_comment|/*&n; * Master Control&n; */
DECL|macro|MB25_MC_UPLO
mdefine_line|#define&t;MB25_MC_UPLO&t;0x80&t;&t;/* UPLO&t;&t;&t;&t;     */
DECL|macro|MB25_MC_DREC
mdefine_line|#define&t;MB25_MC_DREC&t;0x40&t;&t;/* Discard receive cell errors&t;     */
DECL|macro|MB25_MC_ECEIO
mdefine_line|#define&t;MB25_MC_ECEIO&t;0x20&t;&t;/* Enable Cell Error Interrupts Only */
DECL|macro|MB25_MC_TDPC
mdefine_line|#define&t;MB25_MC_TDPC&t;0x10&t;&t;/* Transmit data parity check&t;     */
DECL|macro|MB25_MC_DRIC
mdefine_line|#define&t;MB25_MC_DRIC&t;0x08&t;&t;/* Discard receive idle cells&t;     */
DECL|macro|MB25_MC_HALTTX
mdefine_line|#define&t;MB25_MC_HALTTX&t;0x04&t;&t;/* Halt Tx&t;&t;&t;     */
DECL|macro|MB25_MC_UMS
mdefine_line|#define&t;MB25_MC_UMS&t;0x02&t;&t;/* UTOPIA mode select&t;&t;     */
DECL|macro|MB25_MC_ENABLED
mdefine_line|#define&t;MB25_MC_ENABLED&t;0x01&t;&t;/* Enable interrupt&t;&t;     */
multiline_comment|/*&n; * Interrupt Status&n; */
DECL|macro|MB25_IS_GSB
mdefine_line|#define&t;MB25_IS_GSB&t;0x40&t;&t;/* GOOD Symbol Bit&t;&t;     */&t;
DECL|macro|MB25_IS_HECECR
mdefine_line|#define&t;MB25_IS_HECECR&t;0x20&t;&t;/* HEC error cell received&t;     */
DECL|macro|MB25_IS_SCR
mdefine_line|#define&t;MB25_IS_SCR&t;0x10&t;&t;/* &quot;Short Cell&quot; Received&t;     */
DECL|macro|MB25_IS_TPE
mdefine_line|#define&t;MB25_IS_TPE&t;0x08&t;&t;/* Trnamsit Parity Error&t;     */
DECL|macro|MB25_IS_RSCC
mdefine_line|#define&t;MB25_IS_RSCC&t;0x04&t;&t;/* Receive Signal Condition change   */
DECL|macro|MB25_IS_RCSE
mdefine_line|#define&t;MB25_IS_RCSE&t;0x02&t;&t;/* Received Cell Symbol Error&t;     */
DECL|macro|MB25_IS_RFIFOO
mdefine_line|#define&t;MB25_IS_RFIFOO&t;0x01&t;&t;/* Received FIFO Overrun&t;     */
multiline_comment|/*&n; * Diagnostic Control&n; */
DECL|macro|MB25_DC_FTXCD
mdefine_line|#define&t;MB25_DC_FTXCD&t;0x80&t;&t;/* Force TxClav deassert&t;     */&t;
DECL|macro|MB25_DC_RXCOS
mdefine_line|#define&t;MB25_DC_RXCOS&t;0x40&t;&t;/* RxClav operation select&t;     */
DECL|macro|MB25_DC_ECEIO
mdefine_line|#define&t;MB25_DC_ECEIO&t;0x20&t;&t;/* Single/Multi-PHY config select    */
DECL|macro|MB25_DC_RLFLUSH
mdefine_line|#define&t;MB25_DC_RLFLUSH&t;0x10&t;&t;/* Clear receive FIFO&t;&t;     */
DECL|macro|MB25_DC_IXPE
mdefine_line|#define&t;MB25_DC_IXPE&t;0x08&t;&t;/* Insert xmit payload error&t;     */
DECL|macro|MB25_DC_IXHECE
mdefine_line|#define&t;MB25_DC_IXHECE&t;0x04&t;&t;/* Insert Xmit HEC Error&t;     */
DECL|macro|MB25_DC_LB_MASK
mdefine_line|#define&t;MB25_DC_LB_MASK&t;0x03&t;&t;/* Loopback control mask&t;     */
DECL|macro|MB25_DC_LL
mdefine_line|#define&t;MB25_DC_LL&t;0x03&t;&t;/* Line Loopback&t;&t;     */
DECL|macro|MB25_DC_PL
mdefine_line|#define&t;MB25_DC_PL&t;0x02&t;&t;/* PHY Loopback&t;&t;&t;     */
DECL|macro|MB25_DC_NM
mdefine_line|#define&t;MB25_DC_NM&t;0x00&t;&t;
DECL|macro|FE_MASK
mdefine_line|#define FE_MASK &t;0x00F0
DECL|macro|FE_MULTI_MODE
mdefine_line|#define FE_MULTI_MODE&t;0x0000
DECL|macro|FE_SINGLE_MODE
mdefine_line|#define FE_SINGLE_MODE  0x0010 
DECL|macro|FE_UTP_OPTION
mdefine_line|#define FE_UTP_OPTION  &t;0x0020
DECL|macro|FE_25MBIT_PHY
mdefine_line|#define FE_25MBIT_PHY&t;0x0040
DECL|macro|FE_DS3_PHY
mdefine_line|#define FE_DS3_PHY      0x0080          /* DS3 */
DECL|macro|FE_E3_PHY
mdefine_line|#define FE_E3_PHY       0x0090          /* E3 */
r_extern
r_void
id|ia_mb25_init
(paren
id|IADEV
op_star
)paren
suffix:semicolon
multiline_comment|/*********************** SUNI_PM7345 PHY DEFINE HERE *********************/
DECL|struct|_suni_pm7345_t
r_typedef
r_struct
id|_suni_pm7345_t
(brace
DECL|member|suni_config
id|u_int
id|suni_config
suffix:semicolon
multiline_comment|/* SUNI Configuration */
DECL|member|suni_intr_enbl
id|u_int
id|suni_intr_enbl
suffix:semicolon
multiline_comment|/* SUNI Interrupt Enable */
DECL|member|suni_intr_stat
id|u_int
id|suni_intr_stat
suffix:semicolon
multiline_comment|/* SUNI Interrupt Status */
DECL|member|suni_control
id|u_int
id|suni_control
suffix:semicolon
multiline_comment|/* SUNI Control */
DECL|member|suni_id_reset
id|u_int
id|suni_id_reset
suffix:semicolon
multiline_comment|/* SUNI Reset and Identity */
DECL|member|suni_data_link_ctrl
id|u_int
id|suni_data_link_ctrl
suffix:semicolon
DECL|member|suni_rboc_conf_intr_enbl
id|u_int
id|suni_rboc_conf_intr_enbl
suffix:semicolon
DECL|member|suni_rboc_stat
id|u_int
id|suni_rboc_stat
suffix:semicolon
DECL|member|suni_ds3_frm_cfg
id|u_int
id|suni_ds3_frm_cfg
suffix:semicolon
DECL|member|suni_ds3_frm_intr_enbl
id|u_int
id|suni_ds3_frm_intr_enbl
suffix:semicolon
DECL|member|suni_ds3_frm_intr_stat
id|u_int
id|suni_ds3_frm_intr_stat
suffix:semicolon
DECL|member|suni_ds3_frm_stat
id|u_int
id|suni_ds3_frm_stat
suffix:semicolon
DECL|member|suni_rfdl_cfg
id|u_int
id|suni_rfdl_cfg
suffix:semicolon
DECL|member|suni_rfdl_enbl_stat
id|u_int
id|suni_rfdl_enbl_stat
suffix:semicolon
DECL|member|suni_rfdl_stat
id|u_int
id|suni_rfdl_stat
suffix:semicolon
DECL|member|suni_rfdl_data
id|u_int
id|suni_rfdl_data
suffix:semicolon
DECL|member|suni_pmon_chng
id|u_int
id|suni_pmon_chng
suffix:semicolon
DECL|member|suni_pmon_intr_enbl_stat
id|u_int
id|suni_pmon_intr_enbl_stat
suffix:semicolon
DECL|member|suni_reserved1
id|u_int
id|suni_reserved1
(braket
l_int|0x13
op_minus
l_int|0x11
)braket
suffix:semicolon
DECL|member|suni_pmon_lcv_evt_cnt_lsb
id|u_int
id|suni_pmon_lcv_evt_cnt_lsb
suffix:semicolon
DECL|member|suni_pmon_lcv_evt_cnt_msb
id|u_int
id|suni_pmon_lcv_evt_cnt_msb
suffix:semicolon
DECL|member|suni_pmon_fbe_evt_cnt_lsb
id|u_int
id|suni_pmon_fbe_evt_cnt_lsb
suffix:semicolon
DECL|member|suni_pmon_fbe_evt_cnt_msb
id|u_int
id|suni_pmon_fbe_evt_cnt_msb
suffix:semicolon
DECL|member|suni_pmon_sez_det_cnt_lsb
id|u_int
id|suni_pmon_sez_det_cnt_lsb
suffix:semicolon
DECL|member|suni_pmon_sez_det_cnt_msb
id|u_int
id|suni_pmon_sez_det_cnt_msb
suffix:semicolon
DECL|member|suni_pmon_pe_evt_cnt_lsb
id|u_int
id|suni_pmon_pe_evt_cnt_lsb
suffix:semicolon
DECL|member|suni_pmon_pe_evt_cnt_msb
id|u_int
id|suni_pmon_pe_evt_cnt_msb
suffix:semicolon
DECL|member|suni_pmon_ppe_evt_cnt_lsb
id|u_int
id|suni_pmon_ppe_evt_cnt_lsb
suffix:semicolon
DECL|member|suni_pmon_ppe_evt_cnt_msb
id|u_int
id|suni_pmon_ppe_evt_cnt_msb
suffix:semicolon
DECL|member|suni_pmon_febe_evt_cnt_lsb
id|u_int
id|suni_pmon_febe_evt_cnt_lsb
suffix:semicolon
DECL|member|suni_pmon_febe_evt_cnt_msb
id|u_int
id|suni_pmon_febe_evt_cnt_msb
suffix:semicolon
DECL|member|suni_ds3_tran_cfg
id|u_int
id|suni_ds3_tran_cfg
suffix:semicolon
DECL|member|suni_ds3_tran_diag
id|u_int
id|suni_ds3_tran_diag
suffix:semicolon
DECL|member|suni_reserved2
id|u_int
id|suni_reserved2
(braket
l_int|0x23
op_minus
l_int|0x21
)braket
suffix:semicolon
DECL|member|suni_xfdl_cfg
id|u_int
id|suni_xfdl_cfg
suffix:semicolon
DECL|member|suni_xfdl_intr_st
id|u_int
id|suni_xfdl_intr_st
suffix:semicolon
DECL|member|suni_xfdl_xmit_data
id|u_int
id|suni_xfdl_xmit_data
suffix:semicolon
DECL|member|suni_xboc_code
id|u_int
id|suni_xboc_code
suffix:semicolon
DECL|member|suni_splr_cfg
id|u_int
id|suni_splr_cfg
suffix:semicolon
DECL|member|suni_splr_intr_en
id|u_int
id|suni_splr_intr_en
suffix:semicolon
DECL|member|suni_splr_intr_st
id|u_int
id|suni_splr_intr_st
suffix:semicolon
DECL|member|suni_splr_status
id|u_int
id|suni_splr_status
suffix:semicolon
DECL|member|suni_splt_cfg
id|u_int
id|suni_splt_cfg
suffix:semicolon
DECL|member|suni_splt_cntl
id|u_int
id|suni_splt_cntl
suffix:semicolon
DECL|member|suni_splt_diag_g1
id|u_int
id|suni_splt_diag_g1
suffix:semicolon
DECL|member|suni_splt_f1
id|u_int
id|suni_splt_f1
suffix:semicolon
DECL|member|suni_cppm_loc_meters
id|u_int
id|suni_cppm_loc_meters
suffix:semicolon
DECL|member|suni_cppm_chng_of_cppm_perf_meter
id|u_int
id|suni_cppm_chng_of_cppm_perf_meter
suffix:semicolon
DECL|member|suni_cppm_b1_err_cnt_lsb
id|u_int
id|suni_cppm_b1_err_cnt_lsb
suffix:semicolon
DECL|member|suni_cppm_b1_err_cnt_msb
id|u_int
id|suni_cppm_b1_err_cnt_msb
suffix:semicolon
DECL|member|suni_cppm_framing_err_cnt_lsb
id|u_int
id|suni_cppm_framing_err_cnt_lsb
suffix:semicolon
DECL|member|suni_cppm_framing_err_cnt_msb
id|u_int
id|suni_cppm_framing_err_cnt_msb
suffix:semicolon
DECL|member|suni_cppm_febe_cnt_lsb
id|u_int
id|suni_cppm_febe_cnt_lsb
suffix:semicolon
DECL|member|suni_cppm_febe_cnt_msb
id|u_int
id|suni_cppm_febe_cnt_msb
suffix:semicolon
DECL|member|suni_cppm_hcs_err_cnt_lsb
id|u_int
id|suni_cppm_hcs_err_cnt_lsb
suffix:semicolon
DECL|member|suni_cppm_hcs_err_cnt_msb
id|u_int
id|suni_cppm_hcs_err_cnt_msb
suffix:semicolon
DECL|member|suni_cppm_idle_un_cell_cnt_lsb
id|u_int
id|suni_cppm_idle_un_cell_cnt_lsb
suffix:semicolon
DECL|member|suni_cppm_idle_un_cell_cnt_msb
id|u_int
id|suni_cppm_idle_un_cell_cnt_msb
suffix:semicolon
DECL|member|suni_cppm_rcv_cell_cnt_lsb
id|u_int
id|suni_cppm_rcv_cell_cnt_lsb
suffix:semicolon
DECL|member|suni_cppm_rcv_cell_cnt_msb
id|u_int
id|suni_cppm_rcv_cell_cnt_msb
suffix:semicolon
DECL|member|suni_cppm_xmit_cell_cnt_lsb
id|u_int
id|suni_cppm_xmit_cell_cnt_lsb
suffix:semicolon
DECL|member|suni_cppm_xmit_cell_cnt_msb
id|u_int
id|suni_cppm_xmit_cell_cnt_msb
suffix:semicolon
DECL|member|suni_rxcp_ctrl
id|u_int
id|suni_rxcp_ctrl
suffix:semicolon
DECL|member|suni_rxcp_fctrl
id|u_int
id|suni_rxcp_fctrl
suffix:semicolon
DECL|member|suni_rxcp_intr_en_sts
id|u_int
id|suni_rxcp_intr_en_sts
suffix:semicolon
DECL|member|suni_rxcp_idle_pat_h1
id|u_int
id|suni_rxcp_idle_pat_h1
suffix:semicolon
DECL|member|suni_rxcp_idle_pat_h2
id|u_int
id|suni_rxcp_idle_pat_h2
suffix:semicolon
DECL|member|suni_rxcp_idle_pat_h3
id|u_int
id|suni_rxcp_idle_pat_h3
suffix:semicolon
DECL|member|suni_rxcp_idle_pat_h4
id|u_int
id|suni_rxcp_idle_pat_h4
suffix:semicolon
DECL|member|suni_rxcp_idle_mask_h1
id|u_int
id|suni_rxcp_idle_mask_h1
suffix:semicolon
DECL|member|suni_rxcp_idle_mask_h2
id|u_int
id|suni_rxcp_idle_mask_h2
suffix:semicolon
DECL|member|suni_rxcp_idle_mask_h3
id|u_int
id|suni_rxcp_idle_mask_h3
suffix:semicolon
DECL|member|suni_rxcp_idle_mask_h4
id|u_int
id|suni_rxcp_idle_mask_h4
suffix:semicolon
DECL|member|suni_rxcp_cell_pat_h1
id|u_int
id|suni_rxcp_cell_pat_h1
suffix:semicolon
DECL|member|suni_rxcp_cell_pat_h2
id|u_int
id|suni_rxcp_cell_pat_h2
suffix:semicolon
DECL|member|suni_rxcp_cell_pat_h3
id|u_int
id|suni_rxcp_cell_pat_h3
suffix:semicolon
DECL|member|suni_rxcp_cell_pat_h4
id|u_int
id|suni_rxcp_cell_pat_h4
suffix:semicolon
DECL|member|suni_rxcp_cell_mask_h1
id|u_int
id|suni_rxcp_cell_mask_h1
suffix:semicolon
DECL|member|suni_rxcp_cell_mask_h2
id|u_int
id|suni_rxcp_cell_mask_h2
suffix:semicolon
DECL|member|suni_rxcp_cell_mask_h3
id|u_int
id|suni_rxcp_cell_mask_h3
suffix:semicolon
DECL|member|suni_rxcp_cell_mask_h4
id|u_int
id|suni_rxcp_cell_mask_h4
suffix:semicolon
DECL|member|suni_rxcp_hcs_cs
id|u_int
id|suni_rxcp_hcs_cs
suffix:semicolon
DECL|member|suni_rxcp_lcd_cnt_threshold
id|u_int
id|suni_rxcp_lcd_cnt_threshold
suffix:semicolon
DECL|member|suni_reserved3
id|u_int
id|suni_reserved3
(braket
l_int|0x57
op_minus
l_int|0x54
)braket
suffix:semicolon
DECL|member|suni_txcp_ctrl
id|u_int
id|suni_txcp_ctrl
suffix:semicolon
DECL|member|suni_txcp_intr_en_sts
id|u_int
id|suni_txcp_intr_en_sts
suffix:semicolon
DECL|member|suni_txcp_idle_pat_h1
id|u_int
id|suni_txcp_idle_pat_h1
suffix:semicolon
DECL|member|suni_txcp_idle_pat_h2
id|u_int
id|suni_txcp_idle_pat_h2
suffix:semicolon
DECL|member|suni_txcp_idle_pat_h3
id|u_int
id|suni_txcp_idle_pat_h3
suffix:semicolon
DECL|member|suni_txcp_idle_pat_h4
id|u_int
id|suni_txcp_idle_pat_h4
suffix:semicolon
DECL|member|suni_txcp_idle_pat_h5
id|u_int
id|suni_txcp_idle_pat_h5
suffix:semicolon
DECL|member|suni_txcp_idle_payload
id|u_int
id|suni_txcp_idle_payload
suffix:semicolon
DECL|member|suni_e3_frm_fram_options
id|u_int
id|suni_e3_frm_fram_options
suffix:semicolon
DECL|member|suni_e3_frm_maint_options
id|u_int
id|suni_e3_frm_maint_options
suffix:semicolon
DECL|member|suni_e3_frm_fram_intr_enbl
id|u_int
id|suni_e3_frm_fram_intr_enbl
suffix:semicolon
DECL|member|suni_e3_frm_fram_intr_ind_stat
id|u_int
id|suni_e3_frm_fram_intr_ind_stat
suffix:semicolon
DECL|member|suni_e3_frm_maint_intr_enbl
id|u_int
id|suni_e3_frm_maint_intr_enbl
suffix:semicolon
DECL|member|suni_e3_frm_maint_intr_ind
id|u_int
id|suni_e3_frm_maint_intr_ind
suffix:semicolon
DECL|member|suni_e3_frm_maint_stat
id|u_int
id|suni_e3_frm_maint_stat
suffix:semicolon
DECL|member|suni_reserved4
id|u_int
id|suni_reserved4
suffix:semicolon
DECL|member|suni_e3_tran_fram_options
id|u_int
id|suni_e3_tran_fram_options
suffix:semicolon
DECL|member|suni_e3_tran_stat_diag_options
id|u_int
id|suni_e3_tran_stat_diag_options
suffix:semicolon
DECL|member|suni_e3_tran_bip_8_err_mask
id|u_int
id|suni_e3_tran_bip_8_err_mask
suffix:semicolon
DECL|member|suni_e3_tran_maint_adapt_options
id|u_int
id|suni_e3_tran_maint_adapt_options
suffix:semicolon
DECL|member|suni_ttb_ctrl
id|u_int
id|suni_ttb_ctrl
suffix:semicolon
DECL|member|suni_ttb_trail_trace_id_stat
id|u_int
id|suni_ttb_trail_trace_id_stat
suffix:semicolon
DECL|member|suni_ttb_ind_addr
id|u_int
id|suni_ttb_ind_addr
suffix:semicolon
DECL|member|suni_ttb_ind_data
id|u_int
id|suni_ttb_ind_data
suffix:semicolon
DECL|member|suni_ttb_exp_payload_type
id|u_int
id|suni_ttb_exp_payload_type
suffix:semicolon
DECL|member|suni_ttb_payload_type_ctrl_stat
id|u_int
id|suni_ttb_payload_type_ctrl_stat
suffix:semicolon
DECL|member|suni_pad5
id|u_int
id|suni_pad5
(braket
l_int|0x7f
op_minus
l_int|0x71
)braket
suffix:semicolon
DECL|member|suni_master_test
id|u_int
id|suni_master_test
suffix:semicolon
DECL|member|suni_pad6
id|u_int
id|suni_pad6
(braket
l_int|0xff
op_minus
l_int|0x80
)braket
suffix:semicolon
DECL|typedef|suni_pm7345_t
)brace
id|suni_pm7345_t
suffix:semicolon
DECL|macro|SUNI_PM7345_T
mdefine_line|#define SUNI_PM7345_T suni_pm7345_t
DECL|macro|SUNI_PM7345
mdefine_line|#define SUNI_PM7345     0x20            /* Suni chip type */
DECL|macro|SUNI_PM5346
mdefine_line|#define SUNI_PM5346     0x30            /* Suni chip type */
multiline_comment|/*&n; * SUNI_PM7345 Configuration&n; */
DECL|macro|SUNI_PM7345_CLB
mdefine_line|#define SUNI_PM7345_CLB         0x01    /* Cell loopback        */
DECL|macro|SUNI_PM7345_PLB
mdefine_line|#define SUNI_PM7345_PLB         0x02    /* Payload loopback     */
DECL|macro|SUNI_PM7345_DLB
mdefine_line|#define SUNI_PM7345_DLB         0x04    /* Diagnostic loopback  */
DECL|macro|SUNI_PM7345_LLB
mdefine_line|#define SUNI_PM7345_LLB         0x80    /* Line loopback        */
DECL|macro|SUNI_PM7345_E3ENBL
mdefine_line|#define SUNI_PM7345_E3ENBL      0x40    /* E3 enable bit        */
DECL|macro|SUNI_PM7345_LOOPT
mdefine_line|#define SUNI_PM7345_LOOPT       0x10    /* LOOPT enable bit     */
DECL|macro|SUNI_PM7345_FIFOBP
mdefine_line|#define SUNI_PM7345_FIFOBP      0x20    /* FIFO bypass          */
DECL|macro|SUNI_PM7345_FRMRBP
mdefine_line|#define SUNI_PM7345_FRMRBP      0x08    /* Framer bypass        */
multiline_comment|/*&n; * DS3 FRMR Interrupt Enable&n; */
DECL|macro|SUNI_DS3_COFAE
mdefine_line|#define SUNI_DS3_COFAE  0x80            /* Enable change of frame align */
DECL|macro|SUNI_DS3_REDE
mdefine_line|#define SUNI_DS3_REDE   0x40            /* Enable DS3 RED state intr    */
DECL|macro|SUNI_DS3_CBITE
mdefine_line|#define SUNI_DS3_CBITE  0x20            /* Enable Appl ID channel intr  */
DECL|macro|SUNI_DS3_FERFE
mdefine_line|#define SUNI_DS3_FERFE  0x10            /* Enable Far End Receive Failure intr*/
DECL|macro|SUNI_DS3_IDLE
mdefine_line|#define SUNI_DS3_IDLE   0x08            /* Enable Idle signal intr      */
DECL|macro|SUNI_DS3_AISE
mdefine_line|#define SUNI_DS3_AISE   0x04            /* Enable Alarm Indication signal intr*/
DECL|macro|SUNI_DS3_OOFE
mdefine_line|#define SUNI_DS3_OOFE   0x02            /* Enable Out of frame intr     */
DECL|macro|SUNI_DS3_LOSE
mdefine_line|#define SUNI_DS3_LOSE   0x01            /* Enable Loss of signal intr   */
multiline_comment|/*&n; * DS3 FRMR Status&n; */
DECL|macro|SUNI_DS3_ACE
mdefine_line|#define SUNI_DS3_ACE    0x80            /* Additional Configuration Reg */
DECL|macro|SUNI_DS3_REDV
mdefine_line|#define SUNI_DS3_REDV   0x40            /* DS3 RED state                */
DECL|macro|SUNI_DS3_CBITV
mdefine_line|#define SUNI_DS3_CBITV  0x20            /* Application ID channel state */
DECL|macro|SUNI_DS3_FERFV
mdefine_line|#define SUNI_DS3_FERFV  0x10            /* Far End Receive Failure state*/
DECL|macro|SUNI_DS3_IDLV
mdefine_line|#define SUNI_DS3_IDLV   0x08            /* Idle signal state            */
DECL|macro|SUNI_DS3_AISV
mdefine_line|#define SUNI_DS3_AISV   0x04            /* Alarm Indication signal state*/
DECL|macro|SUNI_DS3_OOFV
mdefine_line|#define SUNI_DS3_OOFV   0x02            /* Out of frame state           */
DECL|macro|SUNI_DS3_LOSV
mdefine_line|#define SUNI_DS3_LOSV   0x01            /* Loss of signal state         */
multiline_comment|/*&n; * E3 FRMR Interrupt/Status&n; */
DECL|macro|SUNI_E3_CZDI
mdefine_line|#define SUNI_E3_CZDI    0x40            /* Consecutive Zeros indicator  */
DECL|macro|SUNI_E3_LOSI
mdefine_line|#define SUNI_E3_LOSI    0x20            /* Loss of signal intr status   */
DECL|macro|SUNI_E3_LCVI
mdefine_line|#define SUNI_E3_LCVI    0x10            /* Line code violation intr     */
DECL|macro|SUNI_E3_COFAI
mdefine_line|#define SUNI_E3_COFAI   0x08            /* Change of frame align intr   */
DECL|macro|SUNI_E3_OOFI
mdefine_line|#define SUNI_E3_OOFI    0x04            /* Out of frame intr status     */
DECL|macro|SUNI_E3_LOS
mdefine_line|#define SUNI_E3_LOS     0x02            /* Loss of signal state         */
DECL|macro|SUNI_E3_OOF
mdefine_line|#define SUNI_E3_OOF     0x01            /* Out of frame state           */
multiline_comment|/*&n; * E3 FRMR Maintenance Status&n; */
DECL|macro|SUNI_E3_AISD
mdefine_line|#define SUNI_E3_AISD    0x80            /* Alarm Indication signal state*/
DECL|macro|SUNI_E3_FERF_RAI
mdefine_line|#define SUNI_E3_FERF_RAI        0x40    /* FERF/RAI indicator           */
DECL|macro|SUNI_E3_FEBE
mdefine_line|#define SUNI_E3_FEBE    0x20            /* Far End Block Error indicator*/
multiline_comment|/*&n; * RXCP Control/Status&n; */
DECL|macro|SUNI_DS3_HCSPASS
mdefine_line|#define SUNI_DS3_HCSPASS        0x80    /* Pass cell with HEC errors    */
DECL|macro|SUNI_DS3_HCSDQDB
mdefine_line|#define SUNI_DS3_HCSDQDB        0x40    /* Control octets in HCS calc   */
DECL|macro|SUNI_DS3_HCSADD
mdefine_line|#define SUNI_DS3_HCSADD         0x20    /* Add coset poly               */
DECL|macro|SUNI_DS3_HCK
mdefine_line|#define SUNI_DS3_HCK            0x10    /* Control FIFO data path integ chk*/
DECL|macro|SUNI_DS3_BLOCK
mdefine_line|#define SUNI_DS3_BLOCK          0x08    /* Enable cell filtering        */
DECL|macro|SUNI_DS3_DSCR
mdefine_line|#define SUNI_DS3_DSCR           0x04    /* Disable payload descrambling */
DECL|macro|SUNI_DS3_OOCDV
mdefine_line|#define SUNI_DS3_OOCDV          0x02    /* Cell delineation state       */
DECL|macro|SUNI_DS3_FIFORST
mdefine_line|#define SUNI_DS3_FIFORST        0x01    /* Cell FIFO reset              */
multiline_comment|/*&n; * RXCP Interrupt Enable/Status&n; */
DECL|macro|SUNI_DS3_OOCDE
mdefine_line|#define SUNI_DS3_OOCDE  0x80            /* Intr enable, change in CDS   */
DECL|macro|SUNI_DS3_HCSE
mdefine_line|#define SUNI_DS3_HCSE   0x40            /* Intr enable, corr HCS errors */
DECL|macro|SUNI_DS3_FIFOE
mdefine_line|#define SUNI_DS3_FIFOE  0x20            /* Intr enable, unco HCS errors */
DECL|macro|SUNI_DS3_OOCDI
mdefine_line|#define SUNI_DS3_OOCDI  0x10            /* SYNC state                   */
DECL|macro|SUNI_DS3_UHCSI
mdefine_line|#define SUNI_DS3_UHCSI  0x08            /* Uncorr. HCS errors detected  */
DECL|macro|SUNI_DS3_COCAI
mdefine_line|#define SUNI_DS3_COCAI  0x04            /* Corr. HCS errors detected    */
DECL|macro|SUNI_DS3_FOVRI
mdefine_line|#define SUNI_DS3_FOVRI  0x02            /* FIFO overrun                 */
DECL|macro|SUNI_DS3_FUDRI
mdefine_line|#define SUNI_DS3_FUDRI  0x01            /* FIFO underrun                */
r_extern
r_void
id|ia_suni_pm7345_init
(paren
id|IADEV
op_star
id|iadev
)paren
suffix:semicolon
singleline_comment|///////////////////SUNI_PM7345 PHY DEFINE END /////////////////////////////
multiline_comment|/* ia_eeprom define*/
DECL|macro|MEM_SIZE_MASK
mdefine_line|#define MEM_SIZE_MASK   0x000F          /* mask of 4 bits defining memory size*/
DECL|macro|MEM_SIZE_128K
mdefine_line|#define MEM_SIZE_128K   0x0000          /* board has 128k buffer */
DECL|macro|MEM_SIZE_512K
mdefine_line|#define MEM_SIZE_512K   0x0001          /* board has 512K of buffer */
DECL|macro|MEM_SIZE_1M
mdefine_line|#define MEM_SIZE_1M     0x0002          /* board has 1M of buffer */
multiline_comment|/* 0x3 to 0xF are reserved for future */
DECL|macro|FE_MASK
mdefine_line|#define FE_MASK         0x00F0          /* mask of 4 bits defining FE type */
DECL|macro|FE_MULTI_MODE
mdefine_line|#define FE_MULTI_MODE   0x0000          /* 155 MBit multimode fiber */
DECL|macro|FE_SINGLE_MODE
mdefine_line|#define FE_SINGLE_MODE  0x0010          /* 155 MBit single mode laser */
DECL|macro|FE_UTP_OPTION
mdefine_line|#define FE_UTP_OPTION   0x0020          /* 155 MBit UTP front end */
DECL|macro|NOVRAM_SIZE
mdefine_line|#define&t;NOVRAM_SIZE&t;64
DECL|macro|CMD_LEN
mdefine_line|#define&t;CMD_LEN&t;&t;10
multiline_comment|/***********&n; *&n; *&t;Switches and defines for header files.&n; *&n; *&t;The following defines are used to turn on and off&n; *&t;various options in the header files. Primarily useful&n; *&t;for debugging.&n; *&n; ***********/
multiline_comment|/*&n; * a list of the commands that can be sent to the NOVRAM&n; */
DECL|macro|EXTEND
mdefine_line|#define&t;EXTEND&t;0x100
DECL|macro|IAWRITE
mdefine_line|#define&t;IAWRITE&t;0x140
DECL|macro|IAREAD
mdefine_line|#define&t;IAREAD&t;0x180
DECL|macro|ERASE
mdefine_line|#define&t;ERASE&t;0x1c0
DECL|macro|EWDS
mdefine_line|#define&t;EWDS&t;0x00
DECL|macro|WRAL
mdefine_line|#define&t;WRAL&t;0x10
DECL|macro|ERAL
mdefine_line|#define&t;ERAL&t;0x20
DECL|macro|EWEN
mdefine_line|#define&t;EWEN&t;0x30
multiline_comment|/*&n; * these bits duplicate the hw_flip.h register settings&n; * note: how the data in / out bits are defined in the flipper specification &n; */
DECL|macro|NVCE
mdefine_line|#define&t;NVCE&t;0x02
DECL|macro|NVSK
mdefine_line|#define&t;NVSK&t;0x01
DECL|macro|NVDO
mdefine_line|#define&t;NVDO&t;0x08&t;
DECL|macro|NVDI
mdefine_line|#define NVDI&t;0x04
multiline_comment|/***********************&n; *&n; * This define ands the value and the current config register and puts&n; * the result in the config register&n; *&n; ***********************/
DECL|macro|CFG_AND
mdefine_line|#define&t;CFG_AND(val) { &bslash;&n;&t;&t;u32 t; &bslash;&n;&t;&t;t = readl(iadev-&gt;reg+IPHASE5575_EEPROM_ACCESS); &bslash;&n;&t;&t;t &amp;= (val); &bslash;&n;&t;&t;writel(t, iadev-&gt;reg+IPHASE5575_EEPROM_ACCESS); &bslash;&n;&t;}
multiline_comment|/***********************&n; *&n; * This define ors the value and the current config register and puts&n; * the result in the config register&n; *&n; ***********************/
DECL|macro|CFG_OR
mdefine_line|#define&t;CFG_OR(val) { &bslash;&n;&t;&t;u32 t; &bslash;&n;&t;&t;t =  readl(iadev-&gt;reg+IPHASE5575_EEPROM_ACCESS); &bslash;&n;&t;&t;t |= (val); &bslash;&n;&t;&t;writel(t, iadev-&gt;reg+IPHASE5575_EEPROM_ACCESS); &bslash;&n;&t;}
multiline_comment|/***********************&n; *&n; * Send a command to the NOVRAM, the command is in cmd.&n; *&n; * clear CE and SK. Then assert CE.&n; * Clock each of the command bits out in the correct order with SK&n; * exit with CE still asserted&n; *&n; ***********************/
DECL|macro|NVRAM_CMD
mdefine_line|#define&t;NVRAM_CMD(cmd) { &bslash;&n;&t;&t;int&t;i; &bslash;&n;&t;&t;u_short c = cmd; &bslash;&n;&t;&t;CFG_AND(~(NVCE|NVSK)); &bslash;&n;&t;&t;CFG_OR(NVCE); &bslash;&n;&t;&t;for (i=0; i&lt;CMD_LEN; i++) { &bslash;&n;&t;&t;&t;NVRAM_CLKOUT((c &amp; (1 &lt;&lt; (CMD_LEN - 1))) ? 1 : 0); &bslash;&n;&t;&t;&t;c &lt;&lt;= 1; &bslash;&n;&t;&t;} &bslash;&n;&t;}
multiline_comment|/***********************&n; *&n; * clear the CE, this must be used after each command is complete&n; *&n; ***********************/
DECL|macro|NVRAM_CLR_CE
mdefine_line|#define&t;NVRAM_CLR_CE&t;{CFG_AND(~NVCE)}
multiline_comment|/***********************&n; *&n; * clock the data bit in bitval out to the NOVRAM.  The bitval must be&n; * a 1 or 0, or the clockout operation is undefined&n; *&n; ***********************/
DECL|macro|NVRAM_CLKOUT
mdefine_line|#define&t;NVRAM_CLKOUT(bitval) { &bslash;&n;&t;&t;CFG_AND(~NVDI); &bslash;&n;&t;&t;CFG_OR((bitval) ? NVDI : 0); &bslash;&n;&t;&t;CFG_OR(NVSK); &bslash;&n;&t;&t;CFG_AND( ~NVSK); &bslash;&n;&t;}
multiline_comment|/***********************&n; *&n; * clock the data bit in and return a 1 or 0, depending on the value&n; * that was received from the NOVRAM&n; *&n; ***********************/
DECL|macro|NVRAM_CLKIN
mdefine_line|#define&t;NVRAM_CLKIN(value) { &bslash;&n;&t;&t;u32 _t; &bslash;&n;&t;&t;CFG_OR(NVSK); &bslash;&n;&t;&t;CFG_AND(~NVSK); &bslash;&n;&t;&t;_t = readl(iadev-&gt;reg+IPHASE5575_EEPROM_ACCESS); &bslash;&n;&t;&t;value = (_t &amp; NVDO) ? 1 : 0; &bslash;&n;&t;}
macro_line|#endif /* IPHASE_H */
eof
