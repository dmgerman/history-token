multiline_comment|/******************************************************************************&n; *&n; * nicstar.h&n; *&n; * Header file for the nicstar device driver.&n; *&n; * Author: Rui Prior (rprior@inescn.pt)&n; * PowerPC support by Jay Talbott (jay_talbott@mcg.mot.com) April 1999&n; *&n; * (C) INESC 1998&n; *&n; ******************************************************************************/
macro_line|#ifndef _LINUX_NICSTAR_H_
DECL|macro|_LINUX_NICSTAR_H_
mdefine_line|#define _LINUX_NICSTAR_H_
multiline_comment|/* Includes *******************************************************************/
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/uio.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/atmdev.h&gt;
macro_line|#include &lt;linux/atm_nicstar.h&gt;
multiline_comment|/* Options ********************************************************************/
DECL|macro|NS_DEBUG_SPINLOCKS
macro_line|#undef NS_DEBUG_SPINLOCKS
DECL|macro|NS_MAX_CARDS
mdefine_line|#define NS_MAX_CARDS 4&t;&t;/* Maximum number of NICStAR based cards&n;&t;&t;&t;&t;   controlled by the device driver. Must&n;                                   be &lt;= 5 */
DECL|macro|RCQ_SUPPORT
macro_line|#undef RCQ_SUPPORT&t;&t;/* Do not define this for now */
DECL|macro|NS_TST_NUM_ENTRIES
mdefine_line|#define NS_TST_NUM_ENTRIES 2340&t;/* + 1 for return */
DECL|macro|NS_TST_RESERVED
mdefine_line|#define NS_TST_RESERVED 340&t;/* N. entries reserved for UBR/ABR/VBR */
DECL|macro|NS_SMBUFSIZE
mdefine_line|#define NS_SMBUFSIZE 48&t;&t;/* 48, 96, 240 or 2048 */
DECL|macro|NS_LGBUFSIZE
mdefine_line|#define NS_LGBUFSIZE 16384&t;/* 2048, 4096, 8192 or 16384 */
DECL|macro|NS_RSQSIZE
mdefine_line|#define NS_RSQSIZE 8192&t;&t;/* 2048, 4096 or 8192 */
DECL|macro|NS_VPIBITS
mdefine_line|#define NS_VPIBITS 2&t;&t;/* 0, 1, 2, or 8 */
DECL|macro|NS_MAX_RCTSIZE
mdefine_line|#define NS_MAX_RCTSIZE 4096&t;/* Number of entries. 4096 or 16384.&n;                                   Define 4096 only if (all) your card(s)&n;&t;&t;&t;&t;   have 32K x 32bit SRAM, in which case&n;&t;&t;&t;&t;   setting this to 16384 will just waste a&n;&t;&t;&t;&t;   lot of memory.&n;&t;&t;&t;&t;   Setting this to 4096 for a card with&n;&t;&t;&t;&t;   128K x 32bit SRAM will limit the maximum&n;&t;&t;&t;&t;   VCI. */
multiline_comment|/*#define NS_PCI_LATENCY 64*/
multiline_comment|/* Must be a multiple of 32 */
multiline_comment|/* Number of buffers initially allocated */
DECL|macro|NUM_SB
mdefine_line|#define NUM_SB 32&t;/* Must be even */
DECL|macro|NUM_LB
mdefine_line|#define NUM_LB 24&t;/* Must be even */
DECL|macro|NUM_HB
mdefine_line|#define NUM_HB 8&t;/* Pre-allocated huge buffers */
DECL|macro|NUM_IOVB
mdefine_line|#define NUM_IOVB 48&t;/* Iovec buffers */
multiline_comment|/* Lower level for count of buffers */
DECL|macro|MIN_SB
mdefine_line|#define MIN_SB 8&t;/* Must be even */
DECL|macro|MIN_LB
mdefine_line|#define MIN_LB 8&t;/* Must be even */
DECL|macro|MIN_HB
mdefine_line|#define MIN_HB 6
DECL|macro|MIN_IOVB
mdefine_line|#define MIN_IOVB 8
multiline_comment|/* Upper level for count of buffers */
DECL|macro|MAX_SB
mdefine_line|#define MAX_SB 64&t;/* Must be even, &lt;= 508 */
DECL|macro|MAX_LB
mdefine_line|#define MAX_LB 48&t;/* Must be even, &lt;= 508 */
DECL|macro|MAX_HB
mdefine_line|#define MAX_HB 10
DECL|macro|MAX_IOVB
mdefine_line|#define MAX_IOVB 80
multiline_comment|/* These are the absolute maximum allowed for the ioctl() */
DECL|macro|TOP_SB
mdefine_line|#define TOP_SB 256&t;/* Must be even, &lt;= 508 */
DECL|macro|TOP_LB
mdefine_line|#define TOP_LB 128&t;/* Must be even, &lt;= 508 */
DECL|macro|TOP_HB
mdefine_line|#define TOP_HB 64
DECL|macro|TOP_IOVB
mdefine_line|#define TOP_IOVB 256
DECL|macro|MAX_TBD_PER_VC
mdefine_line|#define MAX_TBD_PER_VC 1&t;/* Number of TBDs before a TSR */
DECL|macro|MAX_TBD_PER_SCQ
mdefine_line|#define MAX_TBD_PER_SCQ 10&t;/* Only meaningful for variable rate SCQs */
DECL|macro|ENABLE_TSQFIE
macro_line|#undef ENABLE_TSQFIE
DECL|macro|SCQFULL_TIMEOUT
mdefine_line|#define SCQFULL_TIMEOUT (5 * HZ)
DECL|macro|NS_POLL_PERIOD
mdefine_line|#define NS_POLL_PERIOD (HZ)
DECL|macro|PCR_TOLERANCE
mdefine_line|#define PCR_TOLERANCE (1.0001)
multiline_comment|/* ESI stuff ******************************************************************/
DECL|macro|NICSTAR_EPROM_MAC_ADDR_OFFSET
mdefine_line|#define NICSTAR_EPROM_MAC_ADDR_OFFSET 0x6C
multiline_comment|/* #defines *******************************************************************/
DECL|macro|NS_IOREMAP_SIZE
mdefine_line|#define NS_IOREMAP_SIZE 4096
DECL|macro|BUF_SM
mdefine_line|#define BUF_SM 0x00000000&t;/* These two are used for push_rxbufs() */
DECL|macro|BUF_LG
mdefine_line|#define BUF_LG 0x00000001       /* CMD, Write_FreeBufQ, LBUF bit */
DECL|macro|NS_HBUFSIZE
mdefine_line|#define NS_HBUFSIZE 65568&t;/* Size of max. AAL5 PDU */
DECL|macro|NS_MAX_IOVECS
mdefine_line|#define NS_MAX_IOVECS (2 + (65568 - NS_SMBUFSIZE) / &bslash;&n;                       (NS_LGBUFSIZE - (NS_LGBUFSIZE % 48)))
DECL|macro|NS_IOVBUFSIZE
mdefine_line|#define NS_IOVBUFSIZE (NS_MAX_IOVECS * (sizeof(struct iovec)))
DECL|macro|NS_SMBUFSIZE_USABLE
mdefine_line|#define NS_SMBUFSIZE_USABLE (NS_SMBUFSIZE - NS_SMBUFSIZE % 48)
DECL|macro|NS_LGBUFSIZE_USABLE
mdefine_line|#define NS_LGBUFSIZE_USABLE (NS_LGBUFSIZE - NS_LGBUFSIZE % 48)
DECL|macro|NS_AAL0_HEADER
mdefine_line|#define NS_AAL0_HEADER (ATM_AAL0_SDU - ATM_CELL_PAYLOAD)&t;/* 4 bytes */
DECL|macro|NS_SMSKBSIZE
mdefine_line|#define NS_SMSKBSIZE (NS_SMBUFSIZE + NS_AAL0_HEADER)
DECL|macro|NS_LGSKBSIZE
mdefine_line|#define NS_LGSKBSIZE (NS_SMBUFSIZE + NS_LGBUFSIZE)
multiline_comment|/* NICStAR structures located in host memory **********************************/
multiline_comment|/* RSQ - Receive Status Queue &n; *&n; * Written by the NICStAR, read by the device driver.&n; */
DECL|struct|ns_rsqe
r_typedef
r_struct
id|ns_rsqe
(brace
DECL|member|word_1
id|u32
id|word_1
suffix:semicolon
DECL|member|buffer_handle
id|u32
id|buffer_handle
suffix:semicolon
DECL|member|final_aal5_crc32
id|u32
id|final_aal5_crc32
suffix:semicolon
DECL|member|word_4
id|u32
id|word_4
suffix:semicolon
DECL|typedef|ns_rsqe
)brace
id|ns_rsqe
suffix:semicolon
DECL|macro|ns_rsqe_vpi
mdefine_line|#define ns_rsqe_vpi(ns_rsqep) &bslash;&n;        ((le32_to_cpu((ns_rsqep)-&gt;word_1) &amp; 0x00FF0000) &gt;&gt; 16)
DECL|macro|ns_rsqe_vci
mdefine_line|#define ns_rsqe_vci(ns_rsqep) &bslash;&n;        (le32_to_cpu((ns_rsqep)-&gt;word_1) &amp; 0x0000FFFF)
DECL|macro|NS_RSQE_VALID
mdefine_line|#define NS_RSQE_VALID      0x80000000
DECL|macro|NS_RSQE_NZGFC
mdefine_line|#define NS_RSQE_NZGFC      0x00004000
DECL|macro|NS_RSQE_EOPDU
mdefine_line|#define NS_RSQE_EOPDU      0x00002000
DECL|macro|NS_RSQE_BUFSIZE
mdefine_line|#define NS_RSQE_BUFSIZE    0x00001000
DECL|macro|NS_RSQE_CONGESTION
mdefine_line|#define NS_RSQE_CONGESTION 0x00000800
DECL|macro|NS_RSQE_CLP
mdefine_line|#define NS_RSQE_CLP        0x00000400
DECL|macro|NS_RSQE_CRCERR
mdefine_line|#define NS_RSQE_CRCERR     0x00000200
DECL|macro|NS_RSQE_BUFSIZE_SM
mdefine_line|#define NS_RSQE_BUFSIZE_SM 0x00000000
DECL|macro|NS_RSQE_BUFSIZE_LG
mdefine_line|#define NS_RSQE_BUFSIZE_LG 0x00001000
DECL|macro|ns_rsqe_valid
mdefine_line|#define ns_rsqe_valid(ns_rsqep) &bslash;&n;        (le32_to_cpu((ns_rsqep)-&gt;word_4) &amp; NS_RSQE_VALID)
DECL|macro|ns_rsqe_nzgfc
mdefine_line|#define ns_rsqe_nzgfc(ns_rsqep) &bslash;&n;        (le32_to_cpu((ns_rsqep)-&gt;word_4) &amp; NS_RSQE_NZGFC)
DECL|macro|ns_rsqe_eopdu
mdefine_line|#define ns_rsqe_eopdu(ns_rsqep) &bslash;&n;        (le32_to_cpu((ns_rsqep)-&gt;word_4) &amp; NS_RSQE_EOPDU)
DECL|macro|ns_rsqe_bufsize
mdefine_line|#define ns_rsqe_bufsize(ns_rsqep) &bslash;&n;        (le32_to_cpu((ns_rsqep)-&gt;word_4) &amp; NS_RSQE_BUFSIZE)
DECL|macro|ns_rsqe_congestion
mdefine_line|#define ns_rsqe_congestion(ns_rsqep) &bslash;&n;        (le32_to_cpu((ns_rsqep)-&gt;word_4) &amp; NS_RSQE_CONGESTION)
DECL|macro|ns_rsqe_clp
mdefine_line|#define ns_rsqe_clp(ns_rsqep) &bslash;&n;        (le32_to_cpu((ns_rsqep)-&gt;word_4) &amp; NS_RSQE_CLP)
DECL|macro|ns_rsqe_crcerr
mdefine_line|#define ns_rsqe_crcerr(ns_rsqep) &bslash;&n;        (le32_to_cpu((ns_rsqep)-&gt;word_4) &amp; NS_RSQE_CRCERR)
DECL|macro|ns_rsqe_cellcount
mdefine_line|#define ns_rsqe_cellcount(ns_rsqep) &bslash;&n;        (le32_to_cpu((ns_rsqep)-&gt;word_4) &amp; 0x000001FF)
DECL|macro|ns_rsqe_init
mdefine_line|#define ns_rsqe_init(ns_rsqep) &bslash;&n;        ((ns_rsqep)-&gt;word_4 = cpu_to_le32(0x00000000)) 
DECL|macro|NS_RSQ_NUM_ENTRIES
mdefine_line|#define NS_RSQ_NUM_ENTRIES (NS_RSQSIZE / 16)
DECL|macro|NS_RSQ_ALIGNMENT
mdefine_line|#define NS_RSQ_ALIGNMENT NS_RSQSIZE
multiline_comment|/* RCQ - Raw Cell Queue&n; *&n; * Written by the NICStAR, read by the device driver.&n; */
DECL|struct|cell_payload
r_typedef
r_struct
id|cell_payload
(brace
DECL|member|word
id|u32
id|word
(braket
l_int|12
)braket
suffix:semicolon
DECL|typedef|cell_payload
)brace
id|cell_payload
suffix:semicolon
DECL|struct|ns_rcqe
r_typedef
r_struct
id|ns_rcqe
(brace
DECL|member|word_1
id|u32
id|word_1
suffix:semicolon
DECL|member|word_2
id|u32
id|word_2
suffix:semicolon
DECL|member|word_3
id|u32
id|word_3
suffix:semicolon
DECL|member|word_4
id|u32
id|word_4
suffix:semicolon
DECL|member|payload
id|cell_payload
id|payload
suffix:semicolon
DECL|typedef|ns_rcqe
)brace
id|ns_rcqe
suffix:semicolon
DECL|macro|NS_RCQE_SIZE
mdefine_line|#define NS_RCQE_SIZE 64&t;&t;/* bytes */
DECL|macro|ns_rcqe_islast
mdefine_line|#define ns_rcqe_islast(ns_rcqep) &bslash;&n;        (le32_to_cpu((ns_rcqep)-&gt;word_2) != 0x00000000)
DECL|macro|ns_rcqe_cellheader
mdefine_line|#define ns_rcqe_cellheader(ns_rcqep) &bslash;&n;        (le32_to_cpu((ns_rcqep)-&gt;word_1))
DECL|macro|ns_rcqe_nextbufhandle
mdefine_line|#define ns_rcqe_nextbufhandle(ns_rcqep) &bslash;&n;        (le32_to_cpu((ns_rcqep)-&gt;word_2))
multiline_comment|/* SCQ - Segmentation Channel Queue &n; *&n; * Written by the device driver, read by the NICStAR.&n; */
DECL|struct|ns_scqe
r_typedef
r_struct
id|ns_scqe
(brace
DECL|member|word_1
id|u32
id|word_1
suffix:semicolon
DECL|member|word_2
id|u32
id|word_2
suffix:semicolon
DECL|member|word_3
id|u32
id|word_3
suffix:semicolon
DECL|member|word_4
id|u32
id|word_4
suffix:semicolon
DECL|typedef|ns_scqe
)brace
id|ns_scqe
suffix:semicolon
multiline_comment|/* NOTE: SCQ entries can be either a TBD (Transmit Buffer Descriptors)&n;            or TSR (Transmit Status Requests) */
DECL|macro|NS_SCQE_TYPE_TBD
mdefine_line|#define NS_SCQE_TYPE_TBD 0x00000000
DECL|macro|NS_SCQE_TYPE_TSR
mdefine_line|#define NS_SCQE_TYPE_TSR 0x80000000
DECL|macro|NS_TBD_EOPDU
mdefine_line|#define NS_TBD_EOPDU 0x40000000
DECL|macro|NS_TBD_AAL0
mdefine_line|#define NS_TBD_AAL0  0x00000000
DECL|macro|NS_TBD_AAL34
mdefine_line|#define NS_TBD_AAL34 0x04000000
DECL|macro|NS_TBD_AAL5
mdefine_line|#define NS_TBD_AAL5  0x08000000
DECL|macro|NS_TBD_VPI_MASK
mdefine_line|#define NS_TBD_VPI_MASK 0x0FF00000
DECL|macro|NS_TBD_VCI_MASK
mdefine_line|#define NS_TBD_VCI_MASK 0x000FFFF0
DECL|macro|NS_TBD_VC_MASK
mdefine_line|#define NS_TBD_VC_MASK (NS_TBD_VPI_MASK | NS_TBD_VCI_MASK)
DECL|macro|NS_TBD_VPI_SHIFT
mdefine_line|#define NS_TBD_VPI_SHIFT 20
DECL|macro|NS_TBD_VCI_SHIFT
mdefine_line|#define NS_TBD_VCI_SHIFT 4
DECL|macro|ns_tbd_mkword_1
mdefine_line|#define ns_tbd_mkword_1(flags, m, n, buflen) &bslash;&n;      (cpu_to_le32((flags) | (m) &lt;&lt; 23 | (n) &lt;&lt; 16 | (buflen)))
DECL|macro|ns_tbd_mkword_1_novbr
mdefine_line|#define ns_tbd_mkword_1_novbr(flags, buflen) &bslash;&n;      (cpu_to_le32((flags) | (buflen) | 0x00810000))
DECL|macro|ns_tbd_mkword_3
mdefine_line|#define ns_tbd_mkword_3(control, pdulen) &bslash;&n;      (cpu_to_le32((control) &lt;&lt; 16 | (pdulen)))
DECL|macro|ns_tbd_mkword_4
mdefine_line|#define ns_tbd_mkword_4(gfc, vpi, vci, pt, clp) &bslash;&n;      (cpu_to_le32((gfc) &lt;&lt; 28 | (vpi) &lt;&lt; 20 | (vci) &lt;&lt; 4 | (pt) &lt;&lt; 1 | (clp)))
DECL|macro|NS_TSR_INTENABLE
mdefine_line|#define NS_TSR_INTENABLE 0x20000000
DECL|macro|NS_TSR_SCDISVBR
mdefine_line|#define NS_TSR_SCDISVBR 0xFFFF&t;&t;/* Use as scdi for VBR SCD */
DECL|macro|ns_tsr_mkword_1
mdefine_line|#define ns_tsr_mkword_1(flags) &bslash;&n;        (cpu_to_le32(NS_SCQE_TYPE_TSR | (flags)))
DECL|macro|ns_tsr_mkword_2
mdefine_line|#define ns_tsr_mkword_2(scdi, scqi) &bslash;&n;        (cpu_to_le32((scdi) &lt;&lt; 16 | 0x00008000 | (scqi)))
DECL|macro|ns_scqe_is_tsr
mdefine_line|#define ns_scqe_is_tsr(ns_scqep) &bslash;&n;        (le32_to_cpu((ns_scqep)-&gt;word_1) &amp; NS_SCQE_TYPE_TSR)
DECL|macro|VBR_SCQ_NUM_ENTRIES
mdefine_line|#define VBR_SCQ_NUM_ENTRIES 512
DECL|macro|VBR_SCQSIZE
mdefine_line|#define VBR_SCQSIZE 8192
DECL|macro|CBR_SCQ_NUM_ENTRIES
mdefine_line|#define CBR_SCQ_NUM_ENTRIES 64
DECL|macro|CBR_SCQSIZE
mdefine_line|#define CBR_SCQSIZE 1024
DECL|macro|NS_SCQE_SIZE
mdefine_line|#define NS_SCQE_SIZE 16
multiline_comment|/* TSQ - Transmit Status Queue&n; *&n; * Written by the NICStAR, read by the device driver.&n; */
DECL|struct|ns_tsi
r_typedef
r_struct
id|ns_tsi
(brace
DECL|member|word_1
id|u32
id|word_1
suffix:semicolon
DECL|member|word_2
id|u32
id|word_2
suffix:semicolon
DECL|typedef|ns_tsi
)brace
id|ns_tsi
suffix:semicolon
multiline_comment|/* NOTE: The first word can be a status word copied from the TSR which&n;            originated the TSI, or a timer overflow indicator. In this last&n;&t;    case, the value of the first word is all zeroes. */
DECL|macro|NS_TSI_EMPTY
mdefine_line|#define NS_TSI_EMPTY          0x80000000
DECL|macro|NS_TSI_TIMESTAMP_MASK
mdefine_line|#define NS_TSI_TIMESTAMP_MASK 0x00FFFFFF
DECL|macro|ns_tsi_isempty
mdefine_line|#define ns_tsi_isempty(ns_tsip) &bslash;&n;        (le32_to_cpu((ns_tsip)-&gt;word_2) &amp; NS_TSI_EMPTY)
DECL|macro|ns_tsi_gettimestamp
mdefine_line|#define ns_tsi_gettimestamp(ns_tsip) &bslash;&n;        (le32_to_cpu((ns_tsip)-&gt;word_2) &amp; NS_TSI_TIMESTAMP_MASK)
DECL|macro|ns_tsi_init
mdefine_line|#define ns_tsi_init(ns_tsip) &bslash;&n;        ((ns_tsip)-&gt;word_2 = cpu_to_le32(NS_TSI_EMPTY))
DECL|macro|NS_TSQSIZE
mdefine_line|#define NS_TSQSIZE 8192
DECL|macro|NS_TSQ_NUM_ENTRIES
mdefine_line|#define NS_TSQ_NUM_ENTRIES 1024
DECL|macro|NS_TSQ_ALIGNMENT
mdefine_line|#define NS_TSQ_ALIGNMENT 8192
DECL|macro|NS_TSI_SCDISVBR
mdefine_line|#define NS_TSI_SCDISVBR NS_TSR_SCDISVBR
DECL|macro|ns_tsi_tmrof
mdefine_line|#define ns_tsi_tmrof(ns_tsip) &bslash;&n;        (le32_to_cpu((ns_tsip)-&gt;word_1) == 0x00000000)
DECL|macro|ns_tsi_getscdindex
mdefine_line|#define ns_tsi_getscdindex(ns_tsip) &bslash;&n;        ((le32_to_cpu((ns_tsip)-&gt;word_1) &amp; 0xFFFF0000) &gt;&gt; 16)
DECL|macro|ns_tsi_getscqpos
mdefine_line|#define ns_tsi_getscqpos(ns_tsip) &bslash;&n;        (le32_to_cpu((ns_tsip)-&gt;word_1) &amp; 0x00007FFF)
multiline_comment|/* NICStAR structures located in local SRAM ***********************************/
multiline_comment|/* RCT - Receive Connection Table&n; *&n; * Written by both the NICStAR and the device driver.&n; */
DECL|struct|ns_rcte
r_typedef
r_struct
id|ns_rcte
(brace
DECL|member|word_1
id|u32
id|word_1
suffix:semicolon
DECL|member|buffer_handle
id|u32
id|buffer_handle
suffix:semicolon
DECL|member|dma_address
id|u32
id|dma_address
suffix:semicolon
DECL|member|aal5_crc32
id|u32
id|aal5_crc32
suffix:semicolon
DECL|typedef|ns_rcte
)brace
id|ns_rcte
suffix:semicolon
DECL|macro|NS_RCTE_BSFB
mdefine_line|#define NS_RCTE_BSFB            0x00200000  /* Rev. D only */
DECL|macro|NS_RCTE_NZGFC
mdefine_line|#define NS_RCTE_NZGFC           0x00100000
DECL|macro|NS_RCTE_CONNECTOPEN
mdefine_line|#define NS_RCTE_CONNECTOPEN     0x00080000
DECL|macro|NS_RCTE_AALMASK
mdefine_line|#define NS_RCTE_AALMASK         0x00070000
DECL|macro|NS_RCTE_AAL0
mdefine_line|#define NS_RCTE_AAL0            0x00000000
DECL|macro|NS_RCTE_AAL34
mdefine_line|#define NS_RCTE_AAL34           0x00010000
DECL|macro|NS_RCTE_AAL5
mdefine_line|#define NS_RCTE_AAL5            0x00020000
DECL|macro|NS_RCTE_RCQ
mdefine_line|#define NS_RCTE_RCQ             0x00030000
DECL|macro|NS_RCTE_RAWCELLINTEN
mdefine_line|#define NS_RCTE_RAWCELLINTEN    0x00008000
DECL|macro|NS_RCTE_RXCONSTCELLADDR
mdefine_line|#define NS_RCTE_RXCONSTCELLADDR 0x00004000
DECL|macro|NS_RCTE_BUFFVALID
mdefine_line|#define NS_RCTE_BUFFVALID       0x00002000
DECL|macro|NS_RCTE_FBDSIZE
mdefine_line|#define NS_RCTE_FBDSIZE         0x00001000
DECL|macro|NS_RCTE_EFCI
mdefine_line|#define NS_RCTE_EFCI            0x00000800
DECL|macro|NS_RCTE_CLP
mdefine_line|#define NS_RCTE_CLP             0x00000400
DECL|macro|NS_RCTE_CRCERROR
mdefine_line|#define NS_RCTE_CRCERROR        0x00000200
DECL|macro|NS_RCTE_CELLCOUNT_MASK
mdefine_line|#define NS_RCTE_CELLCOUNT_MASK  0x000001FF
DECL|macro|NS_RCTE_FBDSIZE_SM
mdefine_line|#define NS_RCTE_FBDSIZE_SM 0x00000000
DECL|macro|NS_RCTE_FBDSIZE_LG
mdefine_line|#define NS_RCTE_FBDSIZE_LG 0x00001000
DECL|macro|NS_RCT_ENTRY_SIZE
mdefine_line|#define NS_RCT_ENTRY_SIZE 4&t;/* Number of dwords */
multiline_comment|/* NOTE: We could make macros to contruct the first word of the RCTE,&n;            but that doesn&squot;t seem to make much sense... */
multiline_comment|/* FBD - Free Buffer Descriptor&n; *&n; * Written by the device driver using via the command register.&n; */
DECL|struct|ns_fbd
r_typedef
r_struct
id|ns_fbd
(brace
DECL|member|buffer_handle
id|u32
id|buffer_handle
suffix:semicolon
DECL|member|dma_address
id|u32
id|dma_address
suffix:semicolon
DECL|typedef|ns_fbd
)brace
id|ns_fbd
suffix:semicolon
multiline_comment|/* TST - Transmit Schedule Table&n; *&n; * Written by the device driver.&n; */
DECL|typedef|ns_tste
r_typedef
id|u32
id|ns_tste
suffix:semicolon
DECL|macro|NS_TST_OPCODE_MASK
mdefine_line|#define NS_TST_OPCODE_MASK 0x60000000
DECL|macro|NS_TST_OPCODE_NULL
mdefine_line|#define NS_TST_OPCODE_NULL     0x00000000 /* Insert null cell */
DECL|macro|NS_TST_OPCODE_FIXED
mdefine_line|#define NS_TST_OPCODE_FIXED    0x20000000 /* Cell from a fixed rate channel */
DECL|macro|NS_TST_OPCODE_VARIABLE
mdefine_line|#define NS_TST_OPCODE_VARIABLE 0x40000000
DECL|macro|NS_TST_OPCODE_END
mdefine_line|#define NS_TST_OPCODE_END      0x60000000 /* Jump */
DECL|macro|ns_tste_make
mdefine_line|#define ns_tste_make(opcode, sramad) (opcode | sramad)
multiline_comment|/* NOTE:&n;&n;      - When the opcode is FIXED, sramad specifies the SRAM address of the&n;        SCD for that fixed rate channel.&n;      - When the opcode is END, sramad specifies the SRAM address of the&n;        location of the next TST entry to read.&n;    */
multiline_comment|/* SCD - Segmentation Channel Descriptor&n; *&n; * Written by both the device driver and the NICStAR&n; */
DECL|struct|ns_scd
r_typedef
r_struct
id|ns_scd
(brace
DECL|member|word_1
id|u32
id|word_1
suffix:semicolon
DECL|member|word_2
id|u32
id|word_2
suffix:semicolon
DECL|member|partial_aal5_crc
id|u32
id|partial_aal5_crc
suffix:semicolon
DECL|member|reserved
id|u32
id|reserved
suffix:semicolon
DECL|member|cache_a
id|ns_scqe
id|cache_a
suffix:semicolon
DECL|member|cache_b
id|ns_scqe
id|cache_b
suffix:semicolon
DECL|typedef|ns_scd
)brace
id|ns_scd
suffix:semicolon
DECL|macro|NS_SCD_BASE_MASK_VAR
mdefine_line|#define NS_SCD_BASE_MASK_VAR 0xFFFFE000&t;&t;/* Variable rate */
DECL|macro|NS_SCD_BASE_MASK_FIX
mdefine_line|#define NS_SCD_BASE_MASK_FIX 0xFFFFFC00&t;&t;/* Fixed rate */
DECL|macro|NS_SCD_TAIL_MASK_VAR
mdefine_line|#define NS_SCD_TAIL_MASK_VAR 0x00001FF0
DECL|macro|NS_SCD_TAIL_MASK_FIX
mdefine_line|#define NS_SCD_TAIL_MASK_FIX 0x000003F0
DECL|macro|NS_SCD_HEAD_MASK_VAR
mdefine_line|#define NS_SCD_HEAD_MASK_VAR 0x00001FF0
DECL|macro|NS_SCD_HEAD_MASK_FIX
mdefine_line|#define NS_SCD_HEAD_MASK_FIX 0x000003F0
DECL|macro|NS_SCD_XMITFOREVER
mdefine_line|#define NS_SCD_XMITFOREVER   0x02000000
multiline_comment|/* NOTE: There are other fields in word 2 of the SCD, but as they should&n;            not be needed in the device driver they are not defined here. */
multiline_comment|/* NICStAR local SRAM memory map **********************************************/
DECL|macro|NS_RCT
mdefine_line|#define NS_RCT           0x00000
DECL|macro|NS_RCT_32_END
mdefine_line|#define NS_RCT_32_END    0x03FFF
DECL|macro|NS_RCT_128_END
mdefine_line|#define NS_RCT_128_END   0x0FFFF
DECL|macro|NS_UNUSED_32
mdefine_line|#define NS_UNUSED_32     0x04000
DECL|macro|NS_UNUSED_128
mdefine_line|#define NS_UNUSED_128    0x10000
DECL|macro|NS_UNUSED_END
mdefine_line|#define NS_UNUSED_END    0x1BFFF
DECL|macro|NS_TST_FRSCD
mdefine_line|#define NS_TST_FRSCD     0x1C000
DECL|macro|NS_TST_FRSCD_END
mdefine_line|#define NS_TST_FRSCD_END 0x1E7DB
DECL|macro|NS_VRSCD2
mdefine_line|#define NS_VRSCD2        0x1E7DC
DECL|macro|NS_VRSCD2_END
mdefine_line|#define NS_VRSCD2_END    0x1E7E7
DECL|macro|NS_VRSCD1
mdefine_line|#define NS_VRSCD1        0x1E7E8
DECL|macro|NS_VRSCD1_END
mdefine_line|#define NS_VRSCD1_END    0x1E7F3
DECL|macro|NS_VRSCD0
mdefine_line|#define NS_VRSCD0        0x1E7F4
DECL|macro|NS_VRSCD0_END
mdefine_line|#define NS_VRSCD0_END    0x1E7FF
DECL|macro|NS_RXFIFO
mdefine_line|#define NS_RXFIFO        0x1E800
DECL|macro|NS_RXFIFO_END
mdefine_line|#define NS_RXFIFO_END    0x1F7FF
DECL|macro|NS_SMFBQ
mdefine_line|#define NS_SMFBQ         0x1F800
DECL|macro|NS_SMFBQ_END
mdefine_line|#define NS_SMFBQ_END     0x1FBFF
DECL|macro|NS_LGFBQ
mdefine_line|#define NS_LGFBQ         0x1FC00
DECL|macro|NS_LGFBQ_END
mdefine_line|#define NS_LGFBQ_END     0x1FFFF
multiline_comment|/* NISCtAR operation registers ************************************************/
multiline_comment|/* See Section 3.4 of `IDT77211 NICStAR User Manual&squot; from www.idt.com */
DECL|enum|ns_regs
r_enum
id|ns_regs
(brace
DECL|enumerator|DR0
id|DR0
op_assign
l_int|0x00
comma
multiline_comment|/* Data Register 0 R/W*/
DECL|enumerator|DR1
id|DR1
op_assign
l_int|0x04
comma
multiline_comment|/* Data Register 1 W */
DECL|enumerator|DR2
id|DR2
op_assign
l_int|0x08
comma
multiline_comment|/* Data Register 2 W */
DECL|enumerator|DR3
id|DR3
op_assign
l_int|0x0C
comma
multiline_comment|/* Data Register 3 W */
DECL|enumerator|CMD
id|CMD
op_assign
l_int|0x10
comma
multiline_comment|/* Command W */
DECL|enumerator|CFG
id|CFG
op_assign
l_int|0x14
comma
multiline_comment|/* Configuration R/W */
DECL|enumerator|STAT
id|STAT
op_assign
l_int|0x18
comma
multiline_comment|/* Status R/W */
DECL|enumerator|RSQB
id|RSQB
op_assign
l_int|0x1C
comma
multiline_comment|/* Receive Status Queue Base W */
DECL|enumerator|RSQT
id|RSQT
op_assign
l_int|0x20
comma
multiline_comment|/* Receive Status Queue Tail R */
DECL|enumerator|RSQH
id|RSQH
op_assign
l_int|0x24
comma
multiline_comment|/* Receive Status Queue Head W */
DECL|enumerator|CDC
id|CDC
op_assign
l_int|0x28
comma
multiline_comment|/* Cell Drop Counter R/clear */
DECL|enumerator|VPEC
id|VPEC
op_assign
l_int|0x2C
comma
multiline_comment|/* VPI/VCI Lookup Error Count R/clear */
DECL|enumerator|ICC
id|ICC
op_assign
l_int|0x30
comma
multiline_comment|/* Invalid Cell Count R/clear */
DECL|enumerator|RAWCT
id|RAWCT
op_assign
l_int|0x34
comma
multiline_comment|/* Raw Cell Tail R */
DECL|enumerator|TMR
id|TMR
op_assign
l_int|0x38
comma
multiline_comment|/* Timer R */
DECL|enumerator|TSTB
id|TSTB
op_assign
l_int|0x3C
comma
multiline_comment|/* Transmit Schedule Table Base R/W */
DECL|enumerator|TSQB
id|TSQB
op_assign
l_int|0x40
comma
multiline_comment|/* Transmit Status Queue Base W */
DECL|enumerator|TSQT
id|TSQT
op_assign
l_int|0x44
comma
multiline_comment|/* Transmit Status Queue Tail R */
DECL|enumerator|TSQH
id|TSQH
op_assign
l_int|0x48
comma
multiline_comment|/* Transmit Status Queue Head W */
DECL|enumerator|GP
id|GP
op_assign
l_int|0x4C
comma
multiline_comment|/* General Purpose R/W */
DECL|enumerator|VPM
id|VPM
op_assign
l_int|0x50
multiline_comment|/* VPI/VCI Mask W */
)brace
suffix:semicolon
multiline_comment|/* NICStAR commands issued to the CMD register ********************************/
multiline_comment|/* Top 4 bits are command opcode, lower 28 are parameters. */
DECL|macro|NS_CMD_NO_OPERATION
mdefine_line|#define NS_CMD_NO_OPERATION         0x00000000
multiline_comment|/* params always 0 */
DECL|macro|NS_CMD_OPENCLOSE_CONNECTION
mdefine_line|#define NS_CMD_OPENCLOSE_CONNECTION 0x20000000
multiline_comment|/* b19{1=open,0=close} b18-2{SRAM addr} */
DECL|macro|NS_CMD_WRITE_SRAM
mdefine_line|#define NS_CMD_WRITE_SRAM           0x40000000
multiline_comment|/* b18-2{SRAM addr} b1-0{burst size} */
DECL|macro|NS_CMD_READ_SRAM
mdefine_line|#define NS_CMD_READ_SRAM            0x50000000
multiline_comment|/* b18-2{SRAM addr} */
DECL|macro|NS_CMD_WRITE_FREEBUFQ
mdefine_line|#define NS_CMD_WRITE_FREEBUFQ       0x60000000
multiline_comment|/* b0{large buf indicator} */
DECL|macro|NS_CMD_READ_UTILITY
mdefine_line|#define NS_CMD_READ_UTILITY         0x80000000
multiline_comment|/* b8{1=select UTL_CS1} b9{1=select UTL_CS0} b7-0{bus addr} */
DECL|macro|NS_CMD_WRITE_UTILITY
mdefine_line|#define NS_CMD_WRITE_UTILITY        0x90000000
multiline_comment|/* b8{1=select UTL_CS1} b9{1=select UTL_CS0} b7-0{bus addr} */
DECL|macro|NS_CMD_OPEN_CONNECTION
mdefine_line|#define NS_CMD_OPEN_CONNECTION (NS_CMD_OPENCLOSE_CONNECTION | 0x00080000)
DECL|macro|NS_CMD_CLOSE_CONNECTION
mdefine_line|#define NS_CMD_CLOSE_CONNECTION NS_CMD_OPENCLOSE_CONNECTION
multiline_comment|/* NICStAR configuration bits *************************************************/
DECL|macro|NS_CFG_SWRST
mdefine_line|#define NS_CFG_SWRST          0x80000000    /* Software Reset */
DECL|macro|NS_CFG_RXPATH
mdefine_line|#define NS_CFG_RXPATH         0x20000000    /* Receive Path Enable */
DECL|macro|NS_CFG_SMBUFSIZE_MASK
mdefine_line|#define NS_CFG_SMBUFSIZE_MASK 0x18000000    /* Small Receive Buffer Size */
DECL|macro|NS_CFG_LGBUFSIZE_MASK
mdefine_line|#define NS_CFG_LGBUFSIZE_MASK 0x06000000    /* Large Receive Buffer Size */
DECL|macro|NS_CFG_EFBIE
mdefine_line|#define NS_CFG_EFBIE          0x01000000    /* Empty Free Buffer Queue&n;                                               Interrupt Enable */
DECL|macro|NS_CFG_RSQSIZE_MASK
mdefine_line|#define NS_CFG_RSQSIZE_MASK   0x00C00000    /* Receive Status Queue Size */
DECL|macro|NS_CFG_ICACCEPT
mdefine_line|#define NS_CFG_ICACCEPT       0x00200000    /* Invalid Cell Accept */
DECL|macro|NS_CFG_IGNOREGFC
mdefine_line|#define NS_CFG_IGNOREGFC      0x00100000    /* Ignore General Flow Control */
DECL|macro|NS_CFG_VPIBITS_MASK
mdefine_line|#define NS_CFG_VPIBITS_MASK   0x000C0000    /* VPI/VCI Bits Size Select */
DECL|macro|NS_CFG_RCTSIZE_MASK
mdefine_line|#define NS_CFG_RCTSIZE_MASK   0x00030000    /* Receive Connection Table Size */
DECL|macro|NS_CFG_VCERRACCEPT
mdefine_line|#define NS_CFG_VCERRACCEPT    0x00008000    /* VPI/VCI Error Cell Accept */
DECL|macro|NS_CFG_RXINT_MASK
mdefine_line|#define NS_CFG_RXINT_MASK     0x00007000    /* End of Receive PDU Interrupt&n;                                               Handling */
DECL|macro|NS_CFG_RAWIE
mdefine_line|#define NS_CFG_RAWIE          0x00000800    /* Raw Cell Qu&squot; Interrupt Enable */
DECL|macro|NS_CFG_RSQAFIE
mdefine_line|#define NS_CFG_RSQAFIE        0x00000400    /* Receive Queue Almost Full&n;                                               Interrupt Enable */
DECL|macro|NS_CFG_RXRM
mdefine_line|#define NS_CFG_RXRM           0x00000200    /* Receive RM Cells */
DECL|macro|NS_CFG_TMRROIE
mdefine_line|#define NS_CFG_TMRROIE        0x00000080    /* Timer Roll Over Interrupt&n;                                               Enable */
DECL|macro|NS_CFG_TXEN
mdefine_line|#define NS_CFG_TXEN           0x00000020    /* Transmit Operation Enable */
DECL|macro|NS_CFG_TXIE
mdefine_line|#define NS_CFG_TXIE           0x00000010    /* Transmit Status Interrupt&n;                                               Enable */
DECL|macro|NS_CFG_TXURIE
mdefine_line|#define NS_CFG_TXURIE         0x00000008    /* Transmit Under-run Interrupt&n;                                               Enable */
DECL|macro|NS_CFG_UMODE
mdefine_line|#define NS_CFG_UMODE          0x00000004    /* Utopia Mode (cell/byte) Select */
DECL|macro|NS_CFG_TSQFIE
mdefine_line|#define NS_CFG_TSQFIE         0x00000002    /* Transmit Status Queue Full&n;                                               Interrupt Enable */
DECL|macro|NS_CFG_PHYIE
mdefine_line|#define NS_CFG_PHYIE          0x00000001    /* PHY Interrupt Enable */
DECL|macro|NS_CFG_SMBUFSIZE_48
mdefine_line|#define NS_CFG_SMBUFSIZE_48    0x00000000
DECL|macro|NS_CFG_SMBUFSIZE_96
mdefine_line|#define NS_CFG_SMBUFSIZE_96    0x08000000
DECL|macro|NS_CFG_SMBUFSIZE_240
mdefine_line|#define NS_CFG_SMBUFSIZE_240   0x10000000
DECL|macro|NS_CFG_SMBUFSIZE_2048
mdefine_line|#define NS_CFG_SMBUFSIZE_2048  0x18000000
DECL|macro|NS_CFG_LGBUFSIZE_2048
mdefine_line|#define NS_CFG_LGBUFSIZE_2048  0x00000000
DECL|macro|NS_CFG_LGBUFSIZE_4096
mdefine_line|#define NS_CFG_LGBUFSIZE_4096  0x02000000
DECL|macro|NS_CFG_LGBUFSIZE_8192
mdefine_line|#define NS_CFG_LGBUFSIZE_8192  0x04000000
DECL|macro|NS_CFG_LGBUFSIZE_16384
mdefine_line|#define NS_CFG_LGBUFSIZE_16384 0x06000000
DECL|macro|NS_CFG_RSQSIZE_2048
mdefine_line|#define NS_CFG_RSQSIZE_2048 0x00000000
DECL|macro|NS_CFG_RSQSIZE_4096
mdefine_line|#define NS_CFG_RSQSIZE_4096 0x00400000
DECL|macro|NS_CFG_RSQSIZE_8192
mdefine_line|#define NS_CFG_RSQSIZE_8192 0x00800000
DECL|macro|NS_CFG_VPIBITS_0
mdefine_line|#define NS_CFG_VPIBITS_0 0x00000000
DECL|macro|NS_CFG_VPIBITS_1
mdefine_line|#define NS_CFG_VPIBITS_1 0x00040000
DECL|macro|NS_CFG_VPIBITS_2
mdefine_line|#define NS_CFG_VPIBITS_2 0x00080000
DECL|macro|NS_CFG_VPIBITS_8
mdefine_line|#define NS_CFG_VPIBITS_8 0x000C0000
DECL|macro|NS_CFG_RCTSIZE_4096_ENTRIES
mdefine_line|#define NS_CFG_RCTSIZE_4096_ENTRIES  0x00000000
DECL|macro|NS_CFG_RCTSIZE_8192_ENTRIES
mdefine_line|#define NS_CFG_RCTSIZE_8192_ENTRIES  0x00010000
DECL|macro|NS_CFG_RCTSIZE_16384_ENTRIES
mdefine_line|#define NS_CFG_RCTSIZE_16384_ENTRIES 0x00020000
DECL|macro|NS_CFG_RXINT_NOINT
mdefine_line|#define NS_CFG_RXINT_NOINT   0x00000000
DECL|macro|NS_CFG_RXINT_NODELAY
mdefine_line|#define NS_CFG_RXINT_NODELAY 0x00001000
DECL|macro|NS_CFG_RXINT_314US
mdefine_line|#define NS_CFG_RXINT_314US   0x00002000
DECL|macro|NS_CFG_RXINT_624US
mdefine_line|#define NS_CFG_RXINT_624US   0x00003000
DECL|macro|NS_CFG_RXINT_899US
mdefine_line|#define NS_CFG_RXINT_899US   0x00004000
multiline_comment|/* NICStAR STATus bits ********************************************************/
DECL|macro|NS_STAT_SFBQC_MASK
mdefine_line|#define NS_STAT_SFBQC_MASK 0xFF000000   /* hi 8 bits Small Buffer Queue Count */
DECL|macro|NS_STAT_LFBQC_MASK
mdefine_line|#define NS_STAT_LFBQC_MASK 0x00FF0000   /* hi 8 bits Large Buffer Queue Count */
DECL|macro|NS_STAT_TSIF
mdefine_line|#define NS_STAT_TSIF       0x00008000   /* Transmit Status Queue Indicator */
DECL|macro|NS_STAT_TXICP
mdefine_line|#define NS_STAT_TXICP      0x00004000   /* Transmit Incomplete PDU */
DECL|macro|NS_STAT_TSQF
mdefine_line|#define NS_STAT_TSQF       0x00001000   /* Transmit Status Queue Full */
DECL|macro|NS_STAT_TMROF
mdefine_line|#define NS_STAT_TMROF      0x00000800   /* Timer Overflow */
DECL|macro|NS_STAT_PHYI
mdefine_line|#define NS_STAT_PHYI       0x00000400   /* PHY Device Interrupt */
DECL|macro|NS_STAT_CMDBZ
mdefine_line|#define NS_STAT_CMDBZ      0x00000200   /* Command Busy */
DECL|macro|NS_STAT_SFBQF
mdefine_line|#define NS_STAT_SFBQF      0x00000100   /* Small Buffer Queue Full */
DECL|macro|NS_STAT_LFBQF
mdefine_line|#define NS_STAT_LFBQF      0x00000080   /* Large Buffer Queue Full */
DECL|macro|NS_STAT_RSQF
mdefine_line|#define NS_STAT_RSQF       0x00000040   /* Receive Status Queue Full */
DECL|macro|NS_STAT_EOPDU
mdefine_line|#define NS_STAT_EOPDU      0x00000020   /* End of PDU */
DECL|macro|NS_STAT_RAWCF
mdefine_line|#define NS_STAT_RAWCF      0x00000010   /* Raw Cell Flag */
DECL|macro|NS_STAT_SFBQE
mdefine_line|#define NS_STAT_SFBQE      0x00000008   /* Small Buffer Queue Empty */
DECL|macro|NS_STAT_LFBQE
mdefine_line|#define NS_STAT_LFBQE      0x00000004   /* Large Buffer Queue Empty */
DECL|macro|NS_STAT_RSQAF
mdefine_line|#define NS_STAT_RSQAF      0x00000002   /* Receive Status Queue Almost Full */
DECL|macro|ns_stat_sfbqc_get
mdefine_line|#define ns_stat_sfbqc_get(stat) (((stat) &amp; NS_STAT_SFBQC_MASK) &gt;&gt; 23)
DECL|macro|ns_stat_lfbqc_get
mdefine_line|#define ns_stat_lfbqc_get(stat) (((stat) &amp; NS_STAT_LFBQC_MASK) &gt;&gt; 15)
multiline_comment|/* #defines which depend on other #defines ************************************/
DECL|macro|NS_TST0
mdefine_line|#define NS_TST0 NS_TST_FRSCD
DECL|macro|NS_TST1
mdefine_line|#define NS_TST1 (NS_TST_FRSCD + NS_TST_NUM_ENTRIES + 1)
DECL|macro|NS_FRSCD
mdefine_line|#define NS_FRSCD (NS_TST1 + NS_TST_NUM_ENTRIES + 1)
DECL|macro|NS_FRSCD_SIZE
mdefine_line|#define NS_FRSCD_SIZE 12&t;/* 12 dwords */
DECL|macro|NS_FRSCD_NUM
mdefine_line|#define NS_FRSCD_NUM ((NS_TST_FRSCD_END + 1 - NS_FRSCD) / NS_FRSCD_SIZE)
macro_line|#if (NS_SMBUFSIZE == 48)
DECL|macro|NS_CFG_SMBUFSIZE
mdefine_line|#define NS_CFG_SMBUFSIZE NS_CFG_SMBUFSIZE_48
macro_line|#elif (NS_SMBUFSIZE == 96)
DECL|macro|NS_CFG_SMBUFSIZE
mdefine_line|#define NS_CFG_SMBUFSIZE NS_CFG_SMBUFSIZE_96
macro_line|#elif (NS_SMBUFSIZE == 240)
DECL|macro|NS_CFG_SMBUFSIZE
mdefine_line|#define NS_CFG_SMBUFSIZE NS_CFG_SMBUFSIZE_240
macro_line|#elif (NS_SMBUFSIZE == 2048)
DECL|macro|NS_CFG_SMBUFSIZE
mdefine_line|#define NS_CFG_SMBUFSIZE NS_CFG_SMBUFSIZE_2048
macro_line|#else
macro_line|#error NS_SMBUFSIZE is incorrect in nicstar.h
macro_line|#endif /* NS_SMBUFSIZE */
macro_line|#if (NS_LGBUFSIZE == 2048)
DECL|macro|NS_CFG_LGBUFSIZE
mdefine_line|#define NS_CFG_LGBUFSIZE NS_CFG_LGBUFSIZE_2048
macro_line|#elif (NS_LGBUFSIZE == 4096)
DECL|macro|NS_CFG_LGBUFSIZE
mdefine_line|#define NS_CFG_LGBUFSIZE NS_CFG_LGBUFSIZE_4096
macro_line|#elif (NS_LGBUFSIZE == 8192)
DECL|macro|NS_CFG_LGBUFSIZE
mdefine_line|#define NS_CFG_LGBUFSIZE NS_CFG_LGBUFSIZE_8192
macro_line|#elif (NS_LGBUFSIZE == 16384)
DECL|macro|NS_CFG_LGBUFSIZE
mdefine_line|#define NS_CFG_LGBUFSIZE NS_CFG_LGBUFSIZE_16384
macro_line|#else
macro_line|#error NS_LGBUFSIZE is incorrect in nicstar.h
macro_line|#endif /* NS_LGBUFSIZE */
macro_line|#if (NS_RSQSIZE == 2048)
DECL|macro|NS_CFG_RSQSIZE
mdefine_line|#define NS_CFG_RSQSIZE NS_CFG_RSQSIZE_2048
macro_line|#elif (NS_RSQSIZE == 4096)
DECL|macro|NS_CFG_RSQSIZE
mdefine_line|#define NS_CFG_RSQSIZE NS_CFG_RSQSIZE_4096
macro_line|#elif (NS_RSQSIZE == 8192)
DECL|macro|NS_CFG_RSQSIZE
mdefine_line|#define NS_CFG_RSQSIZE NS_CFG_RSQSIZE_8192
macro_line|#else
macro_line|#error NS_RSQSIZE is incorrect in nicstar.h
macro_line|#endif /* NS_RSQSIZE */
macro_line|#if (NS_VPIBITS == 0)
DECL|macro|NS_CFG_VPIBITS
mdefine_line|#define NS_CFG_VPIBITS NS_CFG_VPIBITS_0
macro_line|#elif (NS_VPIBITS == 1)
DECL|macro|NS_CFG_VPIBITS
mdefine_line|#define NS_CFG_VPIBITS NS_CFG_VPIBITS_1
macro_line|#elif (NS_VPIBITS == 2)
DECL|macro|NS_CFG_VPIBITS
mdefine_line|#define NS_CFG_VPIBITS NS_CFG_VPIBITS_2
macro_line|#elif (NS_VPIBITS == 8)
DECL|macro|NS_CFG_VPIBITS
mdefine_line|#define NS_CFG_VPIBITS NS_CFG_VPIBITS_8
macro_line|#else
macro_line|#error NS_VPIBITS is incorrect in nicstar.h
macro_line|#endif /* NS_VPIBITS */
macro_line|#ifdef RCQ_SUPPORT
DECL|macro|NS_CFG_RAWIE_OPT
mdefine_line|#define NS_CFG_RAWIE_OPT NS_CFG_RAWIE
macro_line|#else
DECL|macro|NS_CFG_RAWIE_OPT
mdefine_line|#define NS_CFG_RAWIE_OPT 0x00000000
macro_line|#endif /* RCQ_SUPPORT */
macro_line|#ifdef ENABLE_TSQFIE
DECL|macro|NS_CFG_TSQFIE_OPT
mdefine_line|#define NS_CFG_TSQFIE_OPT NS_CFG_TSQFIE
macro_line|#else
DECL|macro|NS_CFG_TSQFIE_OPT
mdefine_line|#define NS_CFG_TSQFIE_OPT 0x00000000
macro_line|#endif /* ENABLE_TSQFIE */
multiline_comment|/* PCI stuff ******************************************************************/
macro_line|#ifndef PCI_VENDOR_ID_IDT
DECL|macro|PCI_VENDOR_ID_IDT
mdefine_line|#define PCI_VENDOR_ID_IDT 0x111D
macro_line|#endif /* PCI_VENDOR_ID_IDT */
macro_line|#ifndef PCI_DEVICE_ID_IDT_IDT77201
DECL|macro|PCI_DEVICE_ID_IDT_IDT77201
mdefine_line|#define PCI_DEVICE_ID_IDT_IDT77201 0x0001
macro_line|#endif /* PCI_DEVICE_ID_IDT_IDT77201 */
multiline_comment|/* Device driver structures ***************************************************/
DECL|struct|tsq_info
r_typedef
r_struct
id|tsq_info
(brace
DECL|member|org
r_void
op_star
id|org
suffix:semicolon
DECL|member|base
id|ns_tsi
op_star
id|base
suffix:semicolon
DECL|member|next
id|ns_tsi
op_star
id|next
suffix:semicolon
DECL|member|last
id|ns_tsi
op_star
id|last
suffix:semicolon
DECL|typedef|tsq_info
)brace
id|tsq_info
suffix:semicolon
DECL|struct|scq_info
r_typedef
r_struct
id|scq_info
(brace
DECL|member|org
r_void
op_star
id|org
suffix:semicolon
DECL|member|base
id|ns_scqe
op_star
id|base
suffix:semicolon
DECL|member|last
id|ns_scqe
op_star
id|last
suffix:semicolon
DECL|member|next
id|ns_scqe
op_star
id|next
suffix:semicolon
DECL|member|tail
r_volatile
id|ns_scqe
op_star
id|tail
suffix:semicolon
multiline_comment|/* Not related to the nicstar register */
DECL|member|num_entries
r_int
id|num_entries
suffix:semicolon
DECL|member|skb
r_struct
id|sk_buff
op_star
op_star
id|skb
suffix:semicolon
multiline_comment|/* Pointer to an array of pointers&n;                                           to the sk_buffs used for tx */
DECL|member|scd
id|u32
id|scd
suffix:semicolon
multiline_comment|/* SRAM address of the corresponding&n;                                           SCD */
DECL|member|tbd_count
r_int
id|tbd_count
suffix:semicolon
multiline_comment|/* Only meaningful on variable rate */
DECL|member|scqfull_waitq
id|wait_queue_head_t
id|scqfull_waitq
suffix:semicolon
DECL|member|full
r_volatile
r_char
id|full
suffix:semicolon
multiline_comment|/* SCQ full indicator */
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
multiline_comment|/* SCQ spinlock */
macro_line|#ifdef NS_DEBUG_SPINLOCKS
DECL|member|has_lock
r_volatile
r_int
id|has_lock
suffix:semicolon
DECL|member|cpu_lock
r_volatile
r_int
id|cpu_lock
suffix:semicolon
macro_line|#endif /* NS_DEBUG_SPINLOCKS */
DECL|typedef|scq_info
)brace
id|scq_info
suffix:semicolon
DECL|struct|rsq_info
r_typedef
r_struct
id|rsq_info
(brace
DECL|member|org
r_void
op_star
id|org
suffix:semicolon
DECL|member|base
id|ns_rsqe
op_star
id|base
suffix:semicolon
DECL|member|next
id|ns_rsqe
op_star
id|next
suffix:semicolon
DECL|member|last
id|ns_rsqe
op_star
id|last
suffix:semicolon
DECL|typedef|rsq_info
)brace
id|rsq_info
suffix:semicolon
DECL|struct|skb_pool
r_typedef
r_struct
id|skb_pool
(brace
DECL|member|count
r_volatile
r_int
id|count
suffix:semicolon
multiline_comment|/* number of buffers in the queue */
DECL|member|queue
r_struct
id|sk_buff_head
id|queue
suffix:semicolon
DECL|typedef|skb_pool
)brace
id|skb_pool
suffix:semicolon
multiline_comment|/* NOTE: for small and large buffer pools, the count is not used, as the&n;         actual value used for buffer management is the one read from the&n;&t; card. */
DECL|struct|vc_map
r_typedef
r_struct
id|vc_map
(brace
DECL|member|tx
r_volatile
r_int
id|tx
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* TX vc? */
DECL|member|rx
r_volatile
r_int
id|rx
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* RX vc? */
DECL|member|tx_vcc
DECL|member|rx_vcc
r_struct
id|atm_vcc
op_star
id|tx_vcc
comma
op_star
id|rx_vcc
suffix:semicolon
DECL|member|rx_iov
r_struct
id|sk_buff
op_star
id|rx_iov
suffix:semicolon
multiline_comment|/* RX iovector skb */
DECL|member|scq
id|scq_info
op_star
id|scq
suffix:semicolon
multiline_comment|/* To keep track of the SCQ */
DECL|member|cbr_scd
id|u32
id|cbr_scd
suffix:semicolon
multiline_comment|/* SRAM address of the corresponding&n;               &t;&t;&t;&t;   SCD. 0x00000000 for UBR/VBR/ABR */
DECL|member|tbd_count
r_int
id|tbd_count
suffix:semicolon
DECL|typedef|vc_map
)brace
id|vc_map
suffix:semicolon
DECL|struct|ns_dev
r_typedef
r_struct
id|ns_dev
(brace
DECL|member|index
r_int
id|index
suffix:semicolon
multiline_comment|/* Card ID to the device driver */
DECL|member|sram_size
r_int
id|sram_size
suffix:semicolon
multiline_comment|/* In k x 32bit words. 32 or 128 */
DECL|member|membase
r_int
r_int
id|membase
suffix:semicolon
multiline_comment|/* Card&squot;s memory base address */
DECL|member|max_pcr
r_int
r_int
id|max_pcr
suffix:semicolon
DECL|member|rct_size
r_int
id|rct_size
suffix:semicolon
multiline_comment|/* Number of entries */
DECL|member|vpibits
r_int
id|vpibits
suffix:semicolon
DECL|member|vcibits
r_int
id|vcibits
suffix:semicolon
DECL|member|pcidev
r_struct
id|pci_dev
op_star
id|pcidev
suffix:semicolon
DECL|member|atmdev
r_struct
id|atm_dev
op_star
id|atmdev
suffix:semicolon
DECL|member|tsq
id|tsq_info
id|tsq
suffix:semicolon
DECL|member|rsq
id|rsq_info
id|rsq
suffix:semicolon
DECL|member|scq0
DECL|member|scq1
DECL|member|scq2
id|scq_info
op_star
id|scq0
comma
op_star
id|scq1
comma
op_star
id|scq2
suffix:semicolon
multiline_comment|/* VBR SCQs */
DECL|member|sbpool
id|skb_pool
id|sbpool
suffix:semicolon
multiline_comment|/* Small buffers */
DECL|member|lbpool
id|skb_pool
id|lbpool
suffix:semicolon
multiline_comment|/* Large buffers */
DECL|member|hbpool
id|skb_pool
id|hbpool
suffix:semicolon
multiline_comment|/* Pre-allocated huge buffers */
DECL|member|iovpool
id|skb_pool
id|iovpool
suffix:semicolon
multiline_comment|/* iovector buffers */
DECL|member|efbie
r_volatile
r_int
id|efbie
suffix:semicolon
multiline_comment|/* Empty free buf. queue int. enabled */
DECL|member|tst_addr
r_volatile
id|u32
id|tst_addr
suffix:semicolon
multiline_comment|/* SRAM address of the TST in use */
DECL|member|tst_free_entries
r_volatile
r_int
id|tst_free_entries
suffix:semicolon
DECL|member|vcmap
id|vc_map
id|vcmap
(braket
id|NS_MAX_RCTSIZE
)braket
suffix:semicolon
DECL|member|tste2vc
id|vc_map
op_star
id|tste2vc
(braket
id|NS_TST_NUM_ENTRIES
)braket
suffix:semicolon
DECL|member|scd2vc
id|vc_map
op_star
id|scd2vc
(braket
id|NS_FRSCD_NUM
)braket
suffix:semicolon
DECL|member|sbnr
id|buf_nr
id|sbnr
suffix:semicolon
DECL|member|lbnr
id|buf_nr
id|lbnr
suffix:semicolon
DECL|member|hbnr
id|buf_nr
id|hbnr
suffix:semicolon
DECL|member|iovnr
id|buf_nr
id|iovnr
suffix:semicolon
DECL|member|sbfqc
r_int
id|sbfqc
suffix:semicolon
DECL|member|lbfqc
r_int
id|lbfqc
suffix:semicolon
DECL|member|sm_handle
id|u32
id|sm_handle
suffix:semicolon
DECL|member|sm_addr
id|u32
id|sm_addr
suffix:semicolon
DECL|member|lg_handle
id|u32
id|lg_handle
suffix:semicolon
DECL|member|lg_addr
id|u32
id|lg_addr
suffix:semicolon
DECL|member|rcbuf
r_struct
id|sk_buff
op_star
id|rcbuf
suffix:semicolon
multiline_comment|/* Current raw cell buffer */
DECL|member|rawch
id|u32
id|rawch
suffix:semicolon
multiline_comment|/* Raw cell queue head */
DECL|member|intcnt
r_int
id|intcnt
suffix:semicolon
multiline_comment|/* Interrupt counter */
DECL|member|int_lock
id|spinlock_t
id|int_lock
suffix:semicolon
multiline_comment|/* Interrupt lock */
DECL|member|res_lock
id|spinlock_t
id|res_lock
suffix:semicolon
multiline_comment|/* Card resource lock */
macro_line|#ifdef NS_DEBUG_SPINLOCKS
DECL|member|has_int_lock
r_volatile
r_int
id|has_int_lock
suffix:semicolon
DECL|member|cpu_int
r_volatile
r_int
id|cpu_int
suffix:semicolon
DECL|member|has_res_lock
r_volatile
r_int
id|has_res_lock
suffix:semicolon
DECL|member|cpu_res
r_volatile
r_int
id|cpu_res
suffix:semicolon
macro_line|#endif /* NS_DEBUG_SPINLOCKS */
DECL|typedef|ns_dev
)brace
id|ns_dev
suffix:semicolon
multiline_comment|/* NOTE: Each tste2vc entry relates a given TST entry to the corresponding&n;            CBR vc. If the entry is not allocated, it must be NULL.&n;&t;    &n;&t;    There are two TSTs so the driver can modify them on the fly&n;&t;    without stopping the transmission.&n;&t;    &n;&t;    scd2vc allows us to find out unused fixed rate SCDs, because&n;&t;    they must have a NULL pointer here. */
macro_line|#endif /* _LINUX_NICSTAR_H_ */
eof
