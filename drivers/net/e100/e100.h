multiline_comment|/*******************************************************************************&n;&n;This software program is available to you under a choice of one of two &n;licenses. You may choose to be licensed under either the GNU General Public &n;License (GPL) Version 2, June 1991, available at &n;http://www.fsf.org/copyleft/gpl.html, or the Intel BSD + Patent License, the &n;text of which follows:&n;&n;Recipient has requested a license and Intel Corporation (&quot;Intel&quot;) is willing&n;to grant a license for the software entitled Linux Base Driver for the &n;Intel(R) PRO/100 Family of Adapters (e100) (the &quot;Software&quot;) being provided &n;by Intel Corporation. The following definitions apply to this license:&n;&n;&quot;Licensed Patents&quot; means patent claims licensable by Intel Corporation which &n;are necessarily infringed by the use of sale of the Software alone or when &n;combined with the operating system referred to below.&n;&n;&quot;Recipient&quot; means the party to whom Intel delivers this Software.&n;&n;&quot;Licensee&quot; means Recipient and those third parties that receive a license to &n;any operating system available under the GNU Public License version 2.0 or &n;later.&n;&n;Copyright (c) 1999 - 2002 Intel Corporation.&n;All rights reserved.&n;&n;The license is provided to Recipient and Recipient&squot;s Licensees under the &n;following terms.&n;&n;Redistribution and use in source and binary forms of the Software, with or &n;without modification, are permitted provided that the following conditions &n;are met:&n;&n;Redistributions of source code of the Software may retain the above &n;copyright notice, this list of conditions and the following disclaimer.&n;&n;Redistributions in binary form of the Software may reproduce the above &n;copyright notice, this list of conditions and the following disclaimer in &n;the documentation and/or materials provided with the distribution.&n;&n;Neither the name of Intel Corporation nor the names of its contributors &n;shall be used to endorse or promote products derived from this Software &n;without specific prior written permission.&n;&n;Intel hereby grants Recipient and Licensees a non-exclusive, worldwide, &n;royalty-free patent license under Licensed Patents to make, use, sell, offer &n;to sell, import and otherwise transfer the Software, if any, in source code &n;and object code form. This license shall include changes to the Software &n;that are error corrections or other minor changes to the Software that do &n;not add functionality or features when the Software is incorporated in any &n;version of an operating system that has been distributed under the GNU &n;General Public License 2.0 or later. This patent license shall apply to the &n;combination of the Software and any operating system licensed under the GNU &n;Public License version 2.0 or later if, at the time Intel provides the &n;Software to Recipient, such addition of the Software to the then publicly &n;available versions of such operating systems available under the GNU Public &n;License version 2.0 or later (whether in gold, beta or alpha form) causes &n;such combination to be covered by the Licensed Patents. The patent license &n;shall not apply to any other combinations which include the Software. NO &n;hardware per se is licensed hereunder.&n;&n;THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS &quot;AS IS&quot; &n;AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE &n;IMPLIED WARRANTIES OF MECHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE &n;ARE DISCLAIMED. IN NO EVENT SHALL INTEL OR IT CONTRIBUTORS BE LIABLE FOR ANY &n;DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES &n;(INCLUDING, BUT NOT LIMITED, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; &n;ANY LOSS OF USE; DATA, OR PROFITS; OR BUSINESS INTERUPTION) HOWEVER CAUSED &n;AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY OR &n;TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE &n;OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n;*******************************************************************************/
macro_line|#ifndef _E100_INC_
DECL|macro|_E100_INC_
mdefine_line|#define _E100_INC_
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/unaligned.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#ifdef SIOCETHTOOL
macro_line|#include &lt;linux/ethtool.h&gt;
macro_line|#include &lt;linux/inetdevice.h&gt;
macro_line|#endif
macro_line|#include &lt;linux/if.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
multiline_comment|/*&n; *  Configure parameters for buffers per controller.&n; *  If the machine this is being used on is a faster machine (i.e. &gt; 150MHz)&n; *  and running on a 10MBS network then more queueing of data occurs. This&n; *  may indicate the some of the numbers below should be adjusted.  Here are&n; *  some typical numbers:&n; *                             MAX_TCB 64&n; *                             MAX_RFD 64&n; *  The default numbers give work well on most systems tests so no real&n; *  adjustments really need to take place.  Also, if the machine is connected&n; *  to a 100MBS network the numbers described above can be lowered from the&n; *  defaults as considerably less data will be queued.&n; */
DECL|macro|MAX_TCB
mdefine_line|#define MAX_TCB        64&t;/* number of transmit control blocks */
DECL|macro|MAX_TBD
mdefine_line|#define MAX_TBD        MAX_TCB
DECL|macro|TX_FRAME_CNT
mdefine_line|#define TX_FRAME_CNT   8&t;/* consecutive transmit frames per interrupt */
multiline_comment|/* TX_FRAME_CNT must be less than MAX_TCB    */
DECL|macro|MAX_RFD
mdefine_line|#define MAX_RFD      64
DECL|macro|E100_DEFAULT_TCB
mdefine_line|#define E100_DEFAULT_TCB   MAX_TCB
DECL|macro|E100_MIN_TCB
mdefine_line|#define E100_MIN_TCB       2*TX_FRAME_CNT + 3&t;/* make room for at least 2 interrupts */
macro_line|#ifdef __ia64__
multiline_comment|/* We can&squot;t use too many DMAble buffers on IA64 machines with &gt;4 GB mem */
DECL|macro|E100_MAX_TCB
mdefine_line|#define E100_MAX_TCB       64
macro_line|#else
DECL|macro|E100_MAX_TCB
mdefine_line|#define E100_MAX_TCB       1024
macro_line|#endif /*  __ia64__ */
DECL|macro|E100_DEFAULT_RFD
mdefine_line|#define E100_DEFAULT_RFD   MAX_RFD
DECL|macro|E100_MIN_RFD
mdefine_line|#define E100_MIN_RFD       8
macro_line|#ifdef __ia64__
multiline_comment|/* We can&squot;t use too many DMAble buffers on IA64 machines with &gt;4 GB mem */
DECL|macro|E100_MAX_RFD
mdefine_line|#define E100_MAX_RFD       64
macro_line|#else
DECL|macro|E100_MAX_RFD
mdefine_line|#define E100_MAX_RFD       1024
macro_line|#endif /*  __ia64__ */
DECL|macro|E100_DEFAULT_XSUM
mdefine_line|#define E100_DEFAULT_XSUM         true
DECL|macro|E100_DEFAULT_BER
mdefine_line|#define E100_DEFAULT_BER          ZLOCK_MAX_ERRORS
DECL|macro|E100_DEFAULT_SPEED_DUPLEX
mdefine_line|#define E100_DEFAULT_SPEED_DUPLEX 0
DECL|macro|E100_DEFAULT_FC
mdefine_line|#define E100_DEFAULT_FC           0
DECL|macro|E100_DEFAULT_IFS
mdefine_line|#define E100_DEFAULT_IFS          true
DECL|macro|E100_DEFAULT_UCODE
mdefine_line|#define E100_DEFAULT_UCODE        true
DECL|macro|TX_THRSHLD
mdefine_line|#define TX_THRSHLD     8
multiline_comment|/* sleep time is at least 50 ms, in jiffies */
DECL|macro|SLEEP_TIME
mdefine_line|#define SLEEP_TIME ((HZ / 20) + 1)
DECL|macro|CUS_TIMEOUT
mdefine_line|#define CUS_TIMEOUT 1000
multiline_comment|/* IFS parameters */
DECL|macro|MIN_NUMBER_OF_TRANSMITS_100
mdefine_line|#define MIN_NUMBER_OF_TRANSMITS_100 1000
DECL|macro|MIN_NUMBER_OF_TRANSMITS_10
mdefine_line|#define MIN_NUMBER_OF_TRANSMITS_10  100
DECL|macro|E100_MAX_NIC
mdefine_line|#define E100_MAX_NIC 16
DECL|macro|E100_MAX_BUSY_WAIT
mdefine_line|#define E100_MAX_BUSY_WAIT 50&t;/*Max udelays in wait_scb and wait_cus_idle */
multiline_comment|/* CPUSAVER_BUNDLE_MAX: Sets the maximum number of frames that will be bundled.&n; * In some situations, such as the TCP windowing algorithm, it may be&n; * better to limit the growth of the bundle size than let it go as&n; * high as it can, because that could cause too much added latency.&n; * The default is six, because this is the number of packets in the&n; * default TCP window size.  A value of 1 would make CPUSaver indicate&n; * an interrupt for every frame received.  If you do not want to put&n; * a limit on the bundle size, set this value to xFFFF.&n; */
DECL|macro|E100_DEFAULT_CPUSAVER_BUNDLE_MAX
mdefine_line|#define E100_DEFAULT_CPUSAVER_BUNDLE_MAX&t;6
DECL|macro|E100_DEFAULT_CPUSAVER_INTERRUPT_DELAY
mdefine_line|#define E100_DEFAULT_CPUSAVER_INTERRUPT_DELAY&t;0x600
DECL|macro|E100_DEFAULT_BUNDLE_SMALL_FR
mdefine_line|#define E100_DEFAULT_BUNDLE_SMALL_FR&t;&t;false
DECL|macro|E100_DEFAULT_RX_CONGESTION_CONTROL
mdefine_line|#define E100_DEFAULT_RX_CONGESTION_CONTROL&t;true
multiline_comment|/* end of configurables */
multiline_comment|/* ====================================================================== */
multiline_comment|/*                                hw                                      */
multiline_comment|/* ====================================================================== */
multiline_comment|/* timeout for command completion */
DECL|macro|E100_CMD_WAIT
mdefine_line|#define E100_CMD_WAIT   100&t;/* iterations */
DECL|struct|driver_stats
r_struct
id|driver_stats
(brace
DECL|member|net_stats
r_struct
id|net_device_stats
id|net_stats
suffix:semicolon
DECL|member|tx_late_col
r_int
r_int
id|tx_late_col
suffix:semicolon
DECL|member|tx_ok_defrd
r_int
r_int
id|tx_ok_defrd
suffix:semicolon
DECL|member|tx_one_retry
r_int
r_int
id|tx_one_retry
suffix:semicolon
DECL|member|tx_mt_one_retry
r_int
r_int
id|tx_mt_one_retry
suffix:semicolon
DECL|member|rcv_cdt_frames
r_int
r_int
id|rcv_cdt_frames
suffix:semicolon
DECL|member|xmt_fc_pkts
r_int
r_int
id|xmt_fc_pkts
suffix:semicolon
DECL|member|rcv_fc_pkts
r_int
r_int
id|rcv_fc_pkts
suffix:semicolon
DECL|member|rcv_fc_unsupported
r_int
r_int
id|rcv_fc_unsupported
suffix:semicolon
DECL|member|xmt_tco_pkts
r_int
r_int
id|xmt_tco_pkts
suffix:semicolon
DECL|member|rcv_tco_pkts
r_int
r_int
id|rcv_tco_pkts
suffix:semicolon
DECL|member|rx_intr_pkts
r_int
r_int
id|rx_intr_pkts
suffix:semicolon
DECL|member|rx_tasklet_pkts
r_int
r_int
id|rx_tasklet_pkts
suffix:semicolon
DECL|member|poll_intr_switch
r_int
r_int
id|poll_intr_switch
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* TODO: kill me when we can do C99 */
DECL|macro|false
mdefine_line|#define false&t;&t;(0)
DECL|macro|true
mdefine_line|#define true&t;&t;(1)
multiline_comment|/* Changed for 82558 and 82559 enhancements */
multiline_comment|/* defines for 82558/9 flow control CSR values */
DECL|macro|DFLT_FC_THLD
mdefine_line|#define DFLT_FC_THLD       0x00&t;/* Rx FIFO threshold of 0.5KB free  */
DECL|macro|DFLT_FC_CMD
mdefine_line|#define DFLT_FC_CMD        0x00&t;/* FC Command in CSR */
multiline_comment|/* ====================================================================== */
multiline_comment|/*                              equates                                   */
multiline_comment|/* ====================================================================== */
multiline_comment|/*&n; * These are general purpose defines &n; */
multiline_comment|/* Bit Mask definitions */
DECL|macro|BIT_0
mdefine_line|#define BIT_0       0x0001
DECL|macro|BIT_1
mdefine_line|#define BIT_1       0x0002
DECL|macro|BIT_2
mdefine_line|#define BIT_2       0x0004
DECL|macro|BIT_3
mdefine_line|#define BIT_3       0x0008
DECL|macro|BIT_4
mdefine_line|#define BIT_4       0x0010
DECL|macro|BIT_5
mdefine_line|#define BIT_5       0x0020
DECL|macro|BIT_6
mdefine_line|#define BIT_6       0x0040
DECL|macro|BIT_7
mdefine_line|#define BIT_7       0x0080
DECL|macro|BIT_8
mdefine_line|#define BIT_8       0x0100
DECL|macro|BIT_9
mdefine_line|#define BIT_9       0x0200
DECL|macro|BIT_10
mdefine_line|#define BIT_10      0x0400
DECL|macro|BIT_11
mdefine_line|#define BIT_11      0x0800
DECL|macro|BIT_12
mdefine_line|#define BIT_12      0x1000
DECL|macro|BIT_13
mdefine_line|#define BIT_13      0x2000
DECL|macro|BIT_14
mdefine_line|#define BIT_14      0x4000
DECL|macro|BIT_15
mdefine_line|#define BIT_15      0x8000
DECL|macro|BIT_28
mdefine_line|#define BIT_28      0x10000000
DECL|macro|BIT_0_2
mdefine_line|#define BIT_0_2     0x0007
DECL|macro|BIT_0_3
mdefine_line|#define BIT_0_3     0x000F
DECL|macro|BIT_0_4
mdefine_line|#define BIT_0_4     0x001F
DECL|macro|BIT_0_5
mdefine_line|#define BIT_0_5     0x003F
DECL|macro|BIT_0_6
mdefine_line|#define BIT_0_6     0x007F
DECL|macro|BIT_0_7
mdefine_line|#define BIT_0_7     0x00FF
DECL|macro|BIT_0_8
mdefine_line|#define BIT_0_8     0x01FF
DECL|macro|BIT_0_13
mdefine_line|#define BIT_0_13    0x3FFF
DECL|macro|BIT_0_15
mdefine_line|#define BIT_0_15    0xFFFF
DECL|macro|BIT_1_2
mdefine_line|#define BIT_1_2     0x0006
DECL|macro|BIT_1_3
mdefine_line|#define BIT_1_3     0x000E
DECL|macro|BIT_2_5
mdefine_line|#define BIT_2_5     0x003C
DECL|macro|BIT_3_4
mdefine_line|#define BIT_3_4     0x0018
DECL|macro|BIT_4_5
mdefine_line|#define BIT_4_5     0x0030
DECL|macro|BIT_4_6
mdefine_line|#define BIT_4_6     0x0070
DECL|macro|BIT_4_7
mdefine_line|#define BIT_4_7     0x00F0
DECL|macro|BIT_5_7
mdefine_line|#define BIT_5_7     0x00E0
DECL|macro|BIT_5_12
mdefine_line|#define BIT_5_12    0x1FE0
DECL|macro|BIT_5_15
mdefine_line|#define BIT_5_15    0xFFE0
DECL|macro|BIT_6_7
mdefine_line|#define BIT_6_7     0x00c0
DECL|macro|BIT_7_11
mdefine_line|#define BIT_7_11    0x0F80
DECL|macro|BIT_8_10
mdefine_line|#define BIT_8_10    0x0700
DECL|macro|BIT_9_13
mdefine_line|#define BIT_9_13    0x3E00
DECL|macro|BIT_12_15
mdefine_line|#define BIT_12_15   0xF000
DECL|macro|BIT_8_15
mdefine_line|#define BIT_8_15    0xFF00
DECL|macro|BIT_16_20
mdefine_line|#define BIT_16_20   0x001F0000
DECL|macro|BIT_21_25
mdefine_line|#define BIT_21_25   0x03E00000
DECL|macro|BIT_26_27
mdefine_line|#define BIT_26_27   0x0C000000
multiline_comment|/* Transmit Threshold related constants */
DECL|macro|DEFAULT_TX_PER_UNDERRUN
mdefine_line|#define DEFAULT_TX_PER_UNDERRUN         20000
DECL|macro|MAX_MULTICAST_ADDRS
mdefine_line|#define MAX_MULTICAST_ADDRS             64
DECL|macro|MAX_FILTER
mdefine_line|#define MAX_FILTER                      16
DECL|macro|FULL_DUPLEX
mdefine_line|#define FULL_DUPLEX      2
DECL|macro|HALF_DUPLEX
mdefine_line|#define HALF_DUPLEX      1
multiline_comment|/*&n; * These defines are specific to the 82557 &n; */
multiline_comment|/* E100 PORT functions -- lower 4 bits */
DECL|macro|PORT_SOFTWARE_RESET
mdefine_line|#define PORT_SOFTWARE_RESET         0
DECL|macro|PORT_SELFTEST
mdefine_line|#define PORT_SELFTEST               1
DECL|macro|PORT_SELECTIVE_RESET
mdefine_line|#define PORT_SELECTIVE_RESET        2
DECL|macro|PORT_DUMP
mdefine_line|#define PORT_DUMP                   3
multiline_comment|/* SCB Status Word bit definitions */
multiline_comment|/* Interrupt status/ack fields */
multiline_comment|/* ER and FCP interrupts for 82558 masks  */
DECL|macro|SCB_STATUS_ACK_MASK
mdefine_line|#define SCB_STATUS_ACK_MASK        BIT_8_15&t;/* Status Mask */
DECL|macro|SCB_STATUS_ACK_CX
mdefine_line|#define SCB_STATUS_ACK_CX          BIT_15&t;/* CU Completed Action Cmd */
DECL|macro|SCB_STATUS_ACK_FR
mdefine_line|#define SCB_STATUS_ACK_FR          BIT_14&t;/* RU Received A Frame */
DECL|macro|SCB_STATUS_ACK_CNA
mdefine_line|#define SCB_STATUS_ACK_CNA         BIT_13&t;/* CU Became Inactive (IDLE) */
DECL|macro|SCB_STATUS_ACK_RNR
mdefine_line|#define SCB_STATUS_ACK_RNR         BIT_12&t;/* RU Became Not Ready */
DECL|macro|SCB_STATUS_ACK_MDI
mdefine_line|#define SCB_STATUS_ACK_MDI         BIT_11&t;/* MDI read or write done */
DECL|macro|SCB_STATUS_ACK_SWI
mdefine_line|#define SCB_STATUS_ACK_SWI         BIT_10&t;/* S/W generated interrupt */
DECL|macro|SCB_STATUS_ACK_ER
mdefine_line|#define SCB_STATUS_ACK_ER          BIT_9&t;/* Early Receive */
DECL|macro|SCB_STATUS_ACK_FCP
mdefine_line|#define SCB_STATUS_ACK_FCP         BIT_8&t;/* Flow Control Pause */
multiline_comment|/*- CUS Fields */
DECL|macro|SCB_CUS_MASK
mdefine_line|#define SCB_CUS_MASK            (BIT_6 | BIT_7)&t;/* CUS 2-bit Mask */
DECL|macro|SCB_CUS_IDLE
mdefine_line|#define SCB_CUS_IDLE            0&t;/* CU Idle */
DECL|macro|SCB_CUS_SUSPEND
mdefine_line|#define SCB_CUS_SUSPEND         BIT_6&t;/* CU Suspended */
DECL|macro|SCB_CUS_ACTIVE
mdefine_line|#define SCB_CUS_ACTIVE          BIT_7&t;/* CU Active */
multiline_comment|/*- RUS Fields */
DECL|macro|SCB_RUS_IDLE
mdefine_line|#define SCB_RUS_IDLE            0&t;/* RU Idle */
DECL|macro|SCB_RUS_MASK
mdefine_line|#define SCB_RUS_MASK            BIT_2_5&t;/* RUS 3-bit Mask */
DECL|macro|SCB_RUS_SUSPEND
mdefine_line|#define SCB_RUS_SUSPEND         BIT_2&t;/* RU Suspended */
DECL|macro|SCB_RUS_NO_RESOURCES
mdefine_line|#define SCB_RUS_NO_RESOURCES    BIT_3&t;/* RU Out Of Resources */
DECL|macro|SCB_RUS_READY
mdefine_line|#define SCB_RUS_READY           BIT_4&t;/* RU Ready */
DECL|macro|SCB_RUS_SUSP_NO_RBDS
mdefine_line|#define SCB_RUS_SUSP_NO_RBDS    (BIT_2 | BIT_5)&t;/* RU No More RBDs */
DECL|macro|SCB_RUS_NO_RBDS
mdefine_line|#define SCB_RUS_NO_RBDS         (BIT_3 | BIT_5)&t;/* RU No More RBDs */
DECL|macro|SCB_RUS_READY_NO_RBDS
mdefine_line|#define SCB_RUS_READY_NO_RBDS   (BIT_4 | BIT_5)&t;/* RU Ready, No RBDs */
multiline_comment|/* SCB Command Word bit definitions */
multiline_comment|/*- CUC fields */
multiline_comment|/* Changing mask to 4 bits */
DECL|macro|SCB_CUC_MASK
mdefine_line|#define SCB_CUC_MASK            BIT_4_7&t;/* CUC 4-bit Mask */
DECL|macro|SCB_CUC_NOOP
mdefine_line|#define SCB_CUC_NOOP            0
DECL|macro|SCB_CUC_START
mdefine_line|#define SCB_CUC_START           BIT_4&t;/* CU Start */
DECL|macro|SCB_CUC_RESUME
mdefine_line|#define SCB_CUC_RESUME          BIT_5&t;/* CU Resume */
multiline_comment|/* Changed for 82558 enhancements */
DECL|macro|SCB_CUC_STATIC_RESUME
mdefine_line|#define SCB_CUC_STATIC_RESUME   (BIT_5 | BIT_7)&t;/* 82558/9 Static Resume */
DECL|macro|SCB_CUC_DUMP_ADDR
mdefine_line|#define SCB_CUC_DUMP_ADDR       BIT_6&t;/* CU Dump Counters Address */
DECL|macro|SCB_CUC_DUMP_STAT
mdefine_line|#define SCB_CUC_DUMP_STAT       (BIT_4 | BIT_6)&t;/* CU Dump stat. counters */
DECL|macro|SCB_CUC_LOAD_BASE
mdefine_line|#define SCB_CUC_LOAD_BASE       (BIT_5 | BIT_6)&t;/* Load the CU base */
multiline_comment|/* Below was defined as BIT_4_7 */
DECL|macro|SCB_CUC_DUMP_RST_STAT
mdefine_line|#define SCB_CUC_DUMP_RST_STAT   BIT_4_6&t;/* CU Dump &amp; reset statistics cntrs */
multiline_comment|/*- RUC fields */
DECL|macro|SCB_RUC_MASK
mdefine_line|#define SCB_RUC_MASK            BIT_0_2&t;/* RUC 3-bit Mask */
DECL|macro|SCB_RUC_START
mdefine_line|#define SCB_RUC_START           BIT_0&t;/* RU Start */
DECL|macro|SCB_RUC_RESUME
mdefine_line|#define SCB_RUC_RESUME          BIT_1&t;/* RU Resume */
DECL|macro|SCB_RUC_ABORT
mdefine_line|#define SCB_RUC_ABORT           BIT_2&t;/* RU Abort */
DECL|macro|SCB_RUC_LOAD_HDS
mdefine_line|#define SCB_RUC_LOAD_HDS        (BIT_0 | BIT_2)&t;/* Load RFD Header Data Size */
DECL|macro|SCB_RUC_LOAD_BASE
mdefine_line|#define SCB_RUC_LOAD_BASE       (BIT_1 | BIT_2)&t;/* Load the RU base */
DECL|macro|SCB_RUC_RBD_RESUME
mdefine_line|#define SCB_RUC_RBD_RESUME      BIT_0_2&t;/* RBD resume */
multiline_comment|/* Interrupt fields (assuming byte addressing) */
DECL|macro|SCB_INT_MASK
mdefine_line|#define SCB_INT_MASK            BIT_0&t;/* Mask interrupts */
DECL|macro|SCB_SOFT_INT
mdefine_line|#define SCB_SOFT_INT            BIT_1&t;/* Generate a S/W interrupt */
multiline_comment|/*  Specific Interrupt Mask Bits (upper byte of SCB Command word) */
DECL|macro|SCB_FCP_INT_MASK
mdefine_line|#define SCB_FCP_INT_MASK        BIT_2&t;/* Flow Control Pause */
DECL|macro|SCB_ER_INT_MASK
mdefine_line|#define SCB_ER_INT_MASK         BIT_3&t;/* Early Receive */
DECL|macro|SCB_RNR_INT_MASK
mdefine_line|#define SCB_RNR_INT_MASK        BIT_4&t;/* RU Not Ready */
DECL|macro|SCB_CNA_INT_MASK
mdefine_line|#define SCB_CNA_INT_MASK        BIT_5&t;/* CU Not Active */
DECL|macro|SCB_FR_INT_MASK
mdefine_line|#define SCB_FR_INT_MASK         BIT_6&t;/* Frame Received */
DECL|macro|SCB_CX_INT_MASK
mdefine_line|#define SCB_CX_INT_MASK         BIT_7&t;/* CU eXecution w/ I-bit done */
DECL|macro|SCB_BACHELOR_INT_MASK
mdefine_line|#define SCB_BACHELOR_INT_MASK   BIT_2_7&t;/* 82558 interrupt mask bits */
DECL|macro|SCB_GCR2_EEPROM_ACCESS_SEMAPHORE
mdefine_line|#define SCB_GCR2_EEPROM_ACCESS_SEMAPHORE BIT_7
multiline_comment|/* EEPROM bit definitions */
multiline_comment|/*- EEPROM control register bits */
DECL|macro|EN_TRNF
mdefine_line|#define EN_TRNF          0x10&t;/* Enable turnoff */
DECL|macro|EEDO
mdefine_line|#define EEDO             0x08&t;/* EEPROM data out */
DECL|macro|EEDI
mdefine_line|#define EEDI             0x04&t;/* EEPROM data in (set for writing data) */
DECL|macro|EECS
mdefine_line|#define EECS             0x02&t;/* EEPROM chip select (1=hi, 0=lo) */
DECL|macro|EESK
mdefine_line|#define EESK             0x01&t;/* EEPROM shift clock (1=hi, 0=lo) */
multiline_comment|/*- EEPROM opcodes */
DECL|macro|EEPROM_READ_OPCODE
mdefine_line|#define EEPROM_READ_OPCODE          06
DECL|macro|EEPROM_WRITE_OPCODE
mdefine_line|#define EEPROM_WRITE_OPCODE         05
DECL|macro|EEPROM_ERASE_OPCODE
mdefine_line|#define EEPROM_ERASE_OPCODE         07
DECL|macro|EEPROM_EWEN_OPCODE
mdefine_line|#define EEPROM_EWEN_OPCODE          19&t;/* Erase/write enable */
DECL|macro|EEPROM_EWDS_OPCODE
mdefine_line|#define EEPROM_EWDS_OPCODE          16&t;/* Erase/write disable */
multiline_comment|/*- EEPROM data locations */
DECL|macro|EEPROM_NODE_ADDRESS_BYTE_0
mdefine_line|#define EEPROM_NODE_ADDRESS_BYTE_0      0
DECL|macro|EEPROM_COMPATIBILITY_WORD
mdefine_line|#define EEPROM_COMPATIBILITY_WORD       3
DECL|macro|EEPROM_PWA_NO
mdefine_line|#define EEPROM_PWA_NO                   8
DECL|macro|EEPROM_ID_WORD
mdefine_line|#define EEPROM_ID_WORD&t;&t;&t;0x0A
DECL|macro|EEPROM_SUM
mdefine_line|#define EEPROM_SUM                      0xbaba
singleline_comment|// Zero Locking Algorithm definitions:
DECL|macro|ZLOCK_ZERO_MASK
mdefine_line|#define ZLOCK_ZERO_MASK&t;&t;0x00F0
DECL|macro|ZLOCK_MAX_READS
mdefine_line|#define ZLOCK_MAX_READS&t;&t;50&t;
DECL|macro|ZLOCK_SET_ZERO
mdefine_line|#define ZLOCK_SET_ZERO&t;&t;0x2010
DECL|macro|ZLOCK_MAX_SLEEP
mdefine_line|#define ZLOCK_MAX_SLEEP&t;&t;300 * HZ&t;
DECL|macro|ZLOCK_MAX_ERRORS
mdefine_line|#define ZLOCK_MAX_ERRORS&t;300
multiline_comment|/* E100 Action Commands */
DECL|macro|CB_IA_ADDRESS
mdefine_line|#define CB_IA_ADDRESS           1
DECL|macro|CB_CONFIGURE
mdefine_line|#define CB_CONFIGURE            2
DECL|macro|CB_MULTICAST
mdefine_line|#define CB_MULTICAST            3
DECL|macro|CB_TRANSMIT
mdefine_line|#define CB_TRANSMIT             4
DECL|macro|CB_LOAD_MICROCODE
mdefine_line|#define CB_LOAD_MICROCODE       5
DECL|macro|CB_LOAD_FILTER
mdefine_line|#define CB_LOAD_FILTER&t;&t;8
DECL|macro|CB_MAX_NONTX_CMD
mdefine_line|#define CB_MAX_NONTX_CMD        9
DECL|macro|CB_IPCB_TRANSMIT
mdefine_line|#define CB_IPCB_TRANSMIT        9
multiline_comment|/* Pre-defined Filter Bits */
DECL|macro|CB_FILTER_EL
mdefine_line|#define CB_FILTER_EL            0x80000000
DECL|macro|CB_FILTER_FIX
mdefine_line|#define CB_FILTER_FIX           0x40000000
DECL|macro|CB_FILTER_ARP
mdefine_line|#define CB_FILTER_ARP           0x08000000
DECL|macro|CB_FILTER_IA_MATCH
mdefine_line|#define CB_FILTER_IA_MATCH      0x02000000
multiline_comment|/* Command Block (CB) Field Definitions */
multiline_comment|/*- CB Command Word */
DECL|macro|CB_EL_BIT
mdefine_line|#define CB_EL_BIT           BIT_15&t;/* CB EL Bit */
DECL|macro|CB_S_BIT
mdefine_line|#define CB_S_BIT            BIT_14&t;/* CB Suspend Bit */
DECL|macro|CB_I_BIT
mdefine_line|#define CB_I_BIT            BIT_13&t;/* CB Interrupt Bit */
DECL|macro|CB_TX_SF_BIT
mdefine_line|#define CB_TX_SF_BIT        BIT_3&t;/* TX CB Flexible Mode */
DECL|macro|CB_CMD_MASK
mdefine_line|#define CB_CMD_MASK         BIT_0_3&t;/* CB 4-bit CMD Mask */
DECL|macro|CB_CID_DEFAULT
mdefine_line|#define CB_CID_DEFAULT      (0x1f &lt;&lt; 8)&t;/* CB 5-bit CID (max value) */
multiline_comment|/*- CB Status Word */
DECL|macro|CB_STATUS_MASK
mdefine_line|#define CB_STATUS_MASK          BIT_12_15&t;/* CB Status Mask (4-bits) */
DECL|macro|CB_STATUS_COMPLETE
mdefine_line|#define CB_STATUS_COMPLETE      BIT_15&t;/* CB Complete Bit */
DECL|macro|CB_STATUS_OK
mdefine_line|#define CB_STATUS_OK            BIT_13&t;/* CB OK Bit */
DECL|macro|CB_STATUS_UNDERRUN
mdefine_line|#define CB_STATUS_UNDERRUN      BIT_12&t;/* CB A Bit */
DECL|macro|CB_STATUS_FAIL
mdefine_line|#define CB_STATUS_FAIL          BIT_11&t;/* CB Fail (F) Bit */
multiline_comment|/*misc command bits */
DECL|macro|CB_TX_EOF_BIT
mdefine_line|#define CB_TX_EOF_BIT           BIT_15&t;/* TX CB/TBD EOF Bit */
multiline_comment|/* Config params */
DECL|macro|CB_CFIG_BYTE_COUNT
mdefine_line|#define CB_CFIG_BYTE_COUNT          22&t;/* 22 config bytes */
DECL|macro|CB_CFIG_D102_BYTE_COUNT
mdefine_line|#define CB_CFIG_D102_BYTE_COUNT    10
multiline_comment|/* Receive Frame Descriptor Fields */
multiline_comment|/*- RFD Status Bits */
DECL|macro|RFD_RECEIVE_COLLISION
mdefine_line|#define RFD_RECEIVE_COLLISION   BIT_0&t;/* Collision detected on Receive */
DECL|macro|RFD_IA_MATCH
mdefine_line|#define RFD_IA_MATCH            BIT_1&t;/* Indv Address Match Bit */
DECL|macro|RFD_RX_ERR
mdefine_line|#define RFD_RX_ERR              BIT_4&t;/* RX_ERR pin on Phy was set */
DECL|macro|RFD_FRAME_TOO_SHORT
mdefine_line|#define RFD_FRAME_TOO_SHORT     BIT_7&t;/* Receive Frame Short */
DECL|macro|RFD_DMA_OVERRUN
mdefine_line|#define RFD_DMA_OVERRUN         BIT_8&t;/* Receive DMA Overrun */
DECL|macro|RFD_NO_RESOURCES
mdefine_line|#define RFD_NO_RESOURCES        BIT_9&t;/* No Buffer Space */
DECL|macro|RFD_ALIGNMENT_ERROR
mdefine_line|#define RFD_ALIGNMENT_ERROR     BIT_10&t;/* Alignment Error */
DECL|macro|RFD_CRC_ERROR
mdefine_line|#define RFD_CRC_ERROR           BIT_11&t;/* CRC Error */
DECL|macro|RFD_STATUS_OK
mdefine_line|#define RFD_STATUS_OK           BIT_13&t;/* RFD OK Bit */
DECL|macro|RFD_STATUS_COMPLETE
mdefine_line|#define RFD_STATUS_COMPLETE     BIT_15&t;/* RFD Complete Bit */
multiline_comment|/*- RFD Command Bits*/
DECL|macro|RFD_EL_BIT
mdefine_line|#define RFD_EL_BIT      BIT_15&t;/* RFD EL Bit */
DECL|macro|RFD_S_BIT
mdefine_line|#define RFD_S_BIT       BIT_14&t;/* RFD Suspend Bit */
DECL|macro|RFD_H_BIT
mdefine_line|#define RFD_H_BIT       BIT_4&t;/* Header RFD Bit */
DECL|macro|RFD_SF_BIT
mdefine_line|#define RFD_SF_BIT      BIT_3&t;/* RFD Flexible Mode */
multiline_comment|/*- RFD misc bits*/
DECL|macro|RFD_EOF_BIT
mdefine_line|#define RFD_EOF_BIT         BIT_15&t;/* RFD End-Of-Frame Bit */
DECL|macro|RFD_F_BIT
mdefine_line|#define RFD_F_BIT           BIT_14&t;/* RFD Buffer Fetch Bit */
DECL|macro|RFD_ACT_COUNT_MASK
mdefine_line|#define RFD_ACT_COUNT_MASK  BIT_0_13&t;/* RFD Actual Count Mask */
multiline_comment|/* Receive Buffer Descriptor Fields*/
DECL|macro|RBD_EOF_BIT
mdefine_line|#define RBD_EOF_BIT             BIT_15&t;/* RBD End-Of-Frame Bit */
DECL|macro|RBD_F_BIT
mdefine_line|#define RBD_F_BIT               BIT_14&t;/* RBD Buffer Fetch Bit */
DECL|macro|RBD_ACT_COUNT_MASK
mdefine_line|#define RBD_ACT_COUNT_MASK      BIT_0_13&t;/* RBD Actual Count Mask */
DECL|macro|SIZE_FIELD_MASK
mdefine_line|#define SIZE_FIELD_MASK     BIT_0_13&t;/* Size of the associated buffer */
DECL|macro|RBD_EL_BIT
mdefine_line|#define RBD_EL_BIT          BIT_15&t;/* RBD EL Bit */
multiline_comment|/* Self Test Results*/
DECL|macro|CB_SELFTEST_FAIL_BIT
mdefine_line|#define CB_SELFTEST_FAIL_BIT        BIT_12
DECL|macro|CB_SELFTEST_DIAG_BIT
mdefine_line|#define CB_SELFTEST_DIAG_BIT        BIT_5
DECL|macro|CB_SELFTEST_REGISTER_BIT
mdefine_line|#define CB_SELFTEST_REGISTER_BIT    BIT_3
DECL|macro|CB_SELFTEST_ROM_BIT
mdefine_line|#define CB_SELFTEST_ROM_BIT         BIT_2
DECL|macro|CB_SELFTEST_ERROR_MASK
mdefine_line|#define CB_SELFTEST_ERROR_MASK ( &bslash;&n;                CB_SELFTEST_FAIL_BIT | CB_SELFTEST_DIAG_BIT | &bslash;&n;                CB_SELFTEST_REGISTER_BIT | CB_SELFTEST_ROM_BIT)
multiline_comment|/* adapter vendor &amp; device ids */
DECL|macro|PCI_OHIO_BOARD
mdefine_line|#define PCI_OHIO_BOARD   0x10f0&t;/* subdevice ID, Ohio dual port nic */
multiline_comment|/* Values for PCI_REV_ID_REGISTER values */
DECL|macro|D101A4_REV_ID
mdefine_line|#define D101A4_REV_ID      4&t;/* 82558 A4 stepping */
DECL|macro|D101B0_REV_ID
mdefine_line|#define D101B0_REV_ID      5&t;/* 82558 B0 stepping */
DECL|macro|D101MA_REV_ID
mdefine_line|#define D101MA_REV_ID      8&t;/* 82559 A0 stepping */
DECL|macro|D101S_REV_ID
mdefine_line|#define D101S_REV_ID      9&t;/* 82559S A-step */
DECL|macro|D102_REV_ID
mdefine_line|#define D102_REV_ID      12
DECL|macro|D102C_REV_ID
mdefine_line|#define D102C_REV_ID     13&t;/* 82550 step C */
DECL|macro|D102E_REV_ID
mdefine_line|#define D102E_REV_ID     15
multiline_comment|/* ############Start of 82555 specific defines################## */
DECL|macro|PHY_82555_LED_SWITCH_CONTROL
mdefine_line|#define PHY_82555_LED_SWITCH_CONTROL    &t;0x1b&t;/* 82555 led switch control register */
multiline_comment|/* 82555 led switch control reg. opcodes */
DECL|macro|PHY_82555_LED_NORMAL_CONTROL
mdefine_line|#define PHY_82555_LED_NORMAL_CONTROL    0&t;
singleline_comment|// control back to the 8255X
DECL|macro|PHY_82555_LED_DRIVER_CONTROL
mdefine_line|#define PHY_82555_LED_DRIVER_CONTROL    BIT_2&t;
singleline_comment|// the driver is in control
DECL|macro|PHY_82555_LED_OFF
mdefine_line|#define PHY_82555_LED_OFF               BIT_2&t;
singleline_comment|// activity LED is off
DECL|macro|PHY_82555_LED_ON_559
mdefine_line|#define PHY_82555_LED_ON_559           (BIT_0 | BIT_2)&t;
singleline_comment|// activity LED is on for 559 and later
DECL|macro|PHY_82555_LED_ON_PRE_559
mdefine_line|#define PHY_82555_LED_ON_PRE_559       (BIT_0 | BIT_1 | BIT_2)&t;
singleline_comment|// activity LED is on for 558 and before
singleline_comment|// Describe the state of the phy led.
singleline_comment|// needed for the function : &squot;e100_blink_timer&squot;
DECL|enum|led_state_e
r_enum
id|led_state_e
(brace
DECL|enumerator|LED_OFF
id|LED_OFF
op_assign
l_int|0
comma
DECL|enumerator|LED_ON
id|LED_ON
comma
)brace
suffix:semicolon
multiline_comment|/* ############End of 82555 specific defines##################### */
DECL|macro|RFD_PARSE_BIT
mdefine_line|#define RFD_PARSE_BIT&t;&t;&t;BIT_3
DECL|macro|RFD_TCP_PACKET
mdefine_line|#define RFD_TCP_PACKET&t;&t;&t;0x00
DECL|macro|RFD_UDP_PACKET
mdefine_line|#define RFD_UDP_PACKET&t;&t;&t;0x01
DECL|macro|TCPUDP_CHECKSUM_BIT_VALID
mdefine_line|#define TCPUDP_CHECKSUM_BIT_VALID&t;BIT_4
DECL|macro|TCPUDP_CHECKSUM_VALID
mdefine_line|#define TCPUDP_CHECKSUM_VALID&t;&t;BIT_5
DECL|macro|CHECKSUM_PROTOCOL_MASK
mdefine_line|#define CHECKSUM_PROTOCOL_MASK&t;&t;0x03
DECL|macro|VLAN_SIZE
mdefine_line|#define VLAN_SIZE   4
DECL|macro|CHKSUM_SIZE
mdefine_line|#define CHKSUM_SIZE 2
DECL|macro|RFD_DATA_SIZE
mdefine_line|#define RFD_DATA_SIZE (ETH_FRAME_LEN + CHKSUM_SIZE + VLAN_SIZE)
multiline_comment|/* Bits for bdp-&gt;flags */
DECL|macro|DF_LINK_FC_CAP
mdefine_line|#define DF_LINK_FC_CAP     0x00000001&t;/* Link is flow control capable */
DECL|macro|DF_CSUM_OFFLOAD
mdefine_line|#define DF_CSUM_OFFLOAD    0x00000002
DECL|macro|DF_UCODE_LOADED
mdefine_line|#define DF_UCODE_LOADED    0x00000004
DECL|macro|USE_IPCB
mdefine_line|#define USE_IPCB           0x00000008&t;/* set if using ipcb for transmits */
DECL|macro|IS_BACHELOR
mdefine_line|#define IS_BACHELOR        0x00000010&t;/* set if 82558 or newer board */
DECL|macro|IS_ICH
mdefine_line|#define IS_ICH             0x00000020
DECL|macro|DF_SPEED_FORCED
mdefine_line|#define DF_SPEED_FORCED    0x00000040&t;/* set if speed is forced */
DECL|typedef|net_dev_stats_t
r_typedef
r_struct
id|net_device_stats
id|net_dev_stats_t
suffix:semicolon
multiline_comment|/* needed macros */
multiline_comment|/* These macros use the bdp pointer. If you use them it better be defined */
DECL|macro|PREV_TCB_USED
mdefine_line|#define PREV_TCB_USED(X)  ((X).tail ? (X).tail - 1 : bdp-&gt;params.TxDescriptors - 1)
DECL|macro|NEXT_TCB_TOUSE
mdefine_line|#define NEXT_TCB_TOUSE(X) ((((X) + 1) &gt;= bdp-&gt;params.TxDescriptors) ? 0 : (X) + 1)
DECL|macro|TCB_TO_USE
mdefine_line|#define TCB_TO_USE(X)     ((X).tail)
DECL|macro|TCBS_AVAIL
mdefine_line|#define TCBS_AVAIL(X)     (NEXT_TCB_TOUSE( NEXT_TCB_TOUSE((X).tail)) != (X).head)
DECL|macro|RFD_POINTER
mdefine_line|#define RFD_POINTER(skb,bdp)      ((rfd_t *) (((unsigned char *)((skb)-&gt;data))-((bdp)-&gt;rfd_size)))
DECL|macro|SKB_RFD_STATUS
mdefine_line|#define SKB_RFD_STATUS(skb,bdp)   ((RFD_POINTER((skb),(bdp)))-&gt;rfd_header.cb_status)
DECL|macro|GET_SKB_DMA_ADDR
mdefine_line|#define GET_SKB_DMA_ADDR(skb)&t;&t;( *(dma_addr_t *)( (skb)-&gt;cb) )
DECL|macro|SET_SKB_DMA_ADDR
mdefine_line|#define SET_SKB_DMA_ADDR(skb,dma_addr)&t;( *(dma_addr_t *)( (skb)-&gt;cb) = (dma_addr) )
multiline_comment|/* ====================================================================== */
multiline_comment|/*                              82557                                     */
multiline_comment|/* ====================================================================== */
multiline_comment|/* Changed for 82558 enhancement */
DECL|struct|_d101_scb_ext_t
r_typedef
r_struct
id|_d101_scb_ext_t
(brace
DECL|member|scb_rx_dma_cnt
id|u32
id|scb_rx_dma_cnt
suffix:semicolon
multiline_comment|/* Rx DMA byte count */
DECL|member|scb_early_rx_int
id|u8
id|scb_early_rx_int
suffix:semicolon
multiline_comment|/* Early Rx DMA byte count */
DECL|member|scb_fc_thld
id|u8
id|scb_fc_thld
suffix:semicolon
multiline_comment|/* Flow Control threshold */
DECL|member|scb_fc_xon_xoff
id|u8
id|scb_fc_xon_xoff
suffix:semicolon
multiline_comment|/* Flow Control XON/XOFF values */
DECL|member|scb_pmdr
id|u8
id|scb_pmdr
suffix:semicolon
multiline_comment|/* Power Mgmt. Driver Reg */
DECL|typedef|d101_scb_ext
)brace
id|d101_scb_ext
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
suffix:semicolon
multiline_comment|/* Changed for 82559 enhancement */
DECL|struct|_d101m_scb_ext_t
r_typedef
r_struct
id|_d101m_scb_ext_t
(brace
DECL|member|scb_rx_dma_cnt
id|u32
id|scb_rx_dma_cnt
suffix:semicolon
multiline_comment|/* Rx DMA byte count */
DECL|member|scb_early_rx_int
id|u8
id|scb_early_rx_int
suffix:semicolon
multiline_comment|/* Early Rx DMA byte count */
DECL|member|scb_fc_thld
id|u8
id|scb_fc_thld
suffix:semicolon
multiline_comment|/* Flow Control threshold */
DECL|member|scb_fc_xon_xoff
id|u8
id|scb_fc_xon_xoff
suffix:semicolon
multiline_comment|/* Flow Control XON/XOFF values */
DECL|member|scb_pmdr
id|u8
id|scb_pmdr
suffix:semicolon
multiline_comment|/* Power Mgmt. Driver Reg */
DECL|member|scb_gen_ctrl
id|u8
id|scb_gen_ctrl
suffix:semicolon
multiline_comment|/* General Control */
DECL|member|scb_gen_stat
id|u8
id|scb_gen_stat
suffix:semicolon
multiline_comment|/* General Status */
DECL|member|scb_reserved
id|u16
id|scb_reserved
suffix:semicolon
multiline_comment|/* Reserved */
DECL|member|scb_function_event
id|u32
id|scb_function_event
suffix:semicolon
multiline_comment|/* Cardbus Function Event */
DECL|member|scb_function_event_mask
id|u32
id|scb_function_event_mask
suffix:semicolon
multiline_comment|/* Cardbus Function Mask */
DECL|member|scb_function_present_state
id|u32
id|scb_function_present_state
suffix:semicolon
multiline_comment|/* Cardbus Function state */
DECL|member|scb_force_event
id|u32
id|scb_force_event
suffix:semicolon
multiline_comment|/* Cardbus Force Event */
DECL|typedef|d101m_scb_ext
)brace
id|d101m_scb_ext
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
suffix:semicolon
multiline_comment|/* Changed for 82550 enhancement */
DECL|struct|_d102_scb_ext_t
r_typedef
r_struct
id|_d102_scb_ext_t
(brace
DECL|member|scb_rx_dma_cnt
id|u32
id|scb_rx_dma_cnt
suffix:semicolon
multiline_comment|/* Rx DMA byte count */
DECL|member|scb_early_rx_int
id|u8
id|scb_early_rx_int
suffix:semicolon
multiline_comment|/* Early Rx DMA byte count */
DECL|member|scb_fc_thld
id|u8
id|scb_fc_thld
suffix:semicolon
multiline_comment|/* Flow Control threshold */
DECL|member|scb_fc_xon_xoff
id|u8
id|scb_fc_xon_xoff
suffix:semicolon
multiline_comment|/* Flow Control XON/XOFF values */
DECL|member|scb_pmdr
id|u8
id|scb_pmdr
suffix:semicolon
multiline_comment|/* Power Mgmt. Driver Reg */
DECL|member|scb_gen_ctrl
id|u8
id|scb_gen_ctrl
suffix:semicolon
multiline_comment|/* General Control */
DECL|member|scb_gen_stat
id|u8
id|scb_gen_stat
suffix:semicolon
multiline_comment|/* General Status */
DECL|member|scb_gen_ctrl2
id|u8
id|scb_gen_ctrl2
suffix:semicolon
DECL|member|scb_reserved
id|u8
id|scb_reserved
suffix:semicolon
multiline_comment|/* Reserved */
DECL|member|scb_scheduling_reg
id|u32
id|scb_scheduling_reg
suffix:semicolon
DECL|member|scb_reserved2
id|u32
id|scb_reserved2
suffix:semicolon
DECL|member|scb_function_event
id|u32
id|scb_function_event
suffix:semicolon
multiline_comment|/* Cardbus Function Event */
DECL|member|scb_function_event_mask
id|u32
id|scb_function_event_mask
suffix:semicolon
multiline_comment|/* Cardbus Function Mask */
DECL|member|scb_function_present_state
id|u32
id|scb_function_present_state
suffix:semicolon
multiline_comment|/* Cardbus Function state */
DECL|member|scb_force_event
id|u32
id|scb_force_event
suffix:semicolon
multiline_comment|/* Cardbus Force Event */
DECL|typedef|d102_scb_ext
)brace
id|d102_scb_ext
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
suffix:semicolon
multiline_comment|/*&n; * 82557 status control block. this will be memory mapped &amp; will hang of the&n; * the bdp, which hangs of the bdp. This is the brain of it.&n; */
DECL|struct|_scb_t
r_typedef
r_struct
id|_scb_t
(brace
DECL|member|scb_status
id|u16
id|scb_status
suffix:semicolon
multiline_comment|/* SCB Status register */
DECL|member|scb_cmd_low
id|u8
id|scb_cmd_low
suffix:semicolon
multiline_comment|/* SCB Command register (low byte) */
DECL|member|scb_cmd_hi
id|u8
id|scb_cmd_hi
suffix:semicolon
multiline_comment|/* SCB Command register (high byte) */
DECL|member|scb_gen_ptr
id|u32
id|scb_gen_ptr
suffix:semicolon
multiline_comment|/* SCB General pointer */
DECL|member|scb_port
id|u32
id|scb_port
suffix:semicolon
multiline_comment|/* PORT register */
DECL|member|scb_flsh_cntrl
id|u16
id|scb_flsh_cntrl
suffix:semicolon
multiline_comment|/* Flash Control register */
DECL|member|scb_eprm_cntrl
id|u16
id|scb_eprm_cntrl
suffix:semicolon
multiline_comment|/* EEPROM control register */
DECL|member|scb_mdi_cntrl
id|u32
id|scb_mdi_cntrl
suffix:semicolon
multiline_comment|/* MDI Control Register */
multiline_comment|/* Changed for 82558 enhancement */
r_union
(brace
DECL|member|scb_rx_dma_cnt
id|u32
id|scb_rx_dma_cnt
suffix:semicolon
multiline_comment|/* Rx DMA byte count */
DECL|member|d101_scb
id|d101_scb_ext
id|d101_scb
suffix:semicolon
multiline_comment|/* 82558/9 specific fields */
DECL|member|d101m_scb
id|d101m_scb_ext
id|d101m_scb
suffix:semicolon
multiline_comment|/* 82559 specific fields */
DECL|member|d102_scb
id|d102_scb_ext
id|d102_scb
suffix:semicolon
DECL|member|scb_ext
)brace
id|scb_ext
suffix:semicolon
DECL|typedef|scb_t
)brace
id|scb_t
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
suffix:semicolon
multiline_comment|/* Self test&n; * This is used to dump results of the self test &n; */
DECL|struct|_self_test_t
r_typedef
r_struct
id|_self_test_t
(brace
DECL|member|st_sign
id|u32
id|st_sign
suffix:semicolon
multiline_comment|/* Self Test Signature */
DECL|member|st_result
id|u32
id|st_result
suffix:semicolon
multiline_comment|/* Self Test Results */
DECL|typedef|self_test_t
)brace
id|self_test_t
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
suffix:semicolon
multiline_comment|/* &n; *  Statistical Counters &n; */
multiline_comment|/* 82557 counters */
DECL|struct|_basic_cntr_t
r_typedef
r_struct
id|_basic_cntr_t
(brace
DECL|member|xmt_gd_frames
id|u32
id|xmt_gd_frames
suffix:semicolon
multiline_comment|/* Good frames transmitted */
DECL|member|xmt_max_coll
id|u32
id|xmt_max_coll
suffix:semicolon
multiline_comment|/* Fatal frames -- had max collisions */
DECL|member|xmt_late_coll
id|u32
id|xmt_late_coll
suffix:semicolon
multiline_comment|/* Fatal frames -- had a late coll. */
DECL|member|xmt_uruns
id|u32
id|xmt_uruns
suffix:semicolon
multiline_comment|/* Xmit underruns (fatal or re-transmit) */
DECL|member|xmt_lost_crs
id|u32
id|xmt_lost_crs
suffix:semicolon
multiline_comment|/* Frames transmitted without CRS */
DECL|member|xmt_deferred
id|u32
id|xmt_deferred
suffix:semicolon
multiline_comment|/* Deferred transmits */
DECL|member|xmt_sngl_coll
id|u32
id|xmt_sngl_coll
suffix:semicolon
multiline_comment|/* Transmits that had 1 and only 1 coll. */
DECL|member|xmt_mlt_coll
id|u32
id|xmt_mlt_coll
suffix:semicolon
multiline_comment|/* Transmits that had multiple coll. */
DECL|member|xmt_ttl_coll
id|u32
id|xmt_ttl_coll
suffix:semicolon
multiline_comment|/* Transmits that had 1+ collisions. */
DECL|member|rcv_gd_frames
id|u32
id|rcv_gd_frames
suffix:semicolon
multiline_comment|/* Good frames received */
DECL|member|rcv_crc_errs
id|u32
id|rcv_crc_errs
suffix:semicolon
multiline_comment|/* Aligned frames that had a CRC error */
DECL|member|rcv_algn_errs
id|u32
id|rcv_algn_errs
suffix:semicolon
multiline_comment|/* Receives that had alignment errors */
DECL|member|rcv_rsrc_err
id|u32
id|rcv_rsrc_err
suffix:semicolon
multiline_comment|/* Good frame dropped cuz no resources */
DECL|member|rcv_oruns
id|u32
id|rcv_oruns
suffix:semicolon
multiline_comment|/* Overrun errors - bus was busy */
DECL|member|rcv_err_coll
id|u32
id|rcv_err_coll
suffix:semicolon
multiline_comment|/* Received frms. that encountered coll. */
DECL|member|rcv_shrt_frames
id|u32
id|rcv_shrt_frames
suffix:semicolon
multiline_comment|/* Received frames that were to short */
DECL|typedef|basic_cntr_t
)brace
id|basic_cntr_t
suffix:semicolon
multiline_comment|/* 82558 extended statistic counters */
DECL|struct|_ext_cntr_t
r_typedef
r_struct
id|_ext_cntr_t
(brace
DECL|member|xmt_fc_frames
id|u32
id|xmt_fc_frames
suffix:semicolon
DECL|member|rcv_fc_frames
id|u32
id|rcv_fc_frames
suffix:semicolon
DECL|member|rcv_fc_unsupported
id|u32
id|rcv_fc_unsupported
suffix:semicolon
DECL|typedef|ext_cntr_t
)brace
id|ext_cntr_t
suffix:semicolon
multiline_comment|/* 82559 TCO statistic counters */
DECL|struct|_tco_cntr_t
r_typedef
r_struct
id|_tco_cntr_t
(brace
DECL|member|xmt_tco_frames
id|u16
id|xmt_tco_frames
suffix:semicolon
DECL|member|rcv_tco_frames
id|u16
id|rcv_tco_frames
suffix:semicolon
DECL|typedef|tco_cntr_t
)brace
id|tco_cntr_t
suffix:semicolon
multiline_comment|/* Structures to access thet physical dump area */
multiline_comment|/* Use one of these types, according to the statisitcal counters mode,&n;   to cast the pointer to the physical dump area and access the cmd_complete&n;   DWORD. */
multiline_comment|/* 557-mode : only basic counters + cmd_complete */
DECL|struct|_err_cntr_557_t
r_typedef
r_struct
id|_err_cntr_557_t
(brace
DECL|member|basic_stats
id|basic_cntr_t
id|basic_stats
suffix:semicolon
DECL|member|cmd_complete
id|u32
id|cmd_complete
suffix:semicolon
DECL|typedef|err_cntr_557_t
)brace
id|err_cntr_557_t
suffix:semicolon
multiline_comment|/* 558-mode : basic + extended counters + cmd_complete */
DECL|struct|_err_cntr_558_t
r_typedef
r_struct
id|_err_cntr_558_t
(brace
DECL|member|basic_stats
id|basic_cntr_t
id|basic_stats
suffix:semicolon
DECL|member|extended_stats
id|ext_cntr_t
id|extended_stats
suffix:semicolon
DECL|member|cmd_complete
id|u32
id|cmd_complete
suffix:semicolon
DECL|typedef|err_cntr_558_t
)brace
id|err_cntr_558_t
suffix:semicolon
multiline_comment|/* 559-mode : basic + extended + TCO counters + cmd_complete */
DECL|struct|_err_cntr_559_t
r_typedef
r_struct
id|_err_cntr_559_t
(brace
DECL|member|basic_stats
id|basic_cntr_t
id|basic_stats
suffix:semicolon
DECL|member|extended_stats
id|ext_cntr_t
id|extended_stats
suffix:semicolon
DECL|member|tco_stats
id|tco_cntr_t
id|tco_stats
suffix:semicolon
DECL|member|cmd_complete
id|u32
id|cmd_complete
suffix:semicolon
DECL|typedef|err_cntr_559_t
)brace
id|err_cntr_559_t
suffix:semicolon
multiline_comment|/* This typedef defines the struct needed to hold the largest number of counters */
DECL|typedef|max_counters_t
r_typedef
id|err_cntr_559_t
id|max_counters_t
suffix:semicolon
multiline_comment|/* Different statistical-counters mode the controller may be in */
DECL|enum|_stat_mode_t
r_typedef
r_enum
id|_stat_mode_t
(brace
DECL|enumerator|E100_BASIC_STATS
id|E100_BASIC_STATS
op_assign
l_int|0
comma
multiline_comment|/* 82557 stats : 16 counters / 16 dw */
DECL|enumerator|E100_EXTENDED_STATS
id|E100_EXTENDED_STATS
comma
multiline_comment|/* 82558 stats : 19 counters / 19 dw */
DECL|enumerator|E100_TCO_STATS
id|E100_TCO_STATS
multiline_comment|/* 82559 stats : 21 counters / 20 dw */
DECL|typedef|stat_mode_t
)brace
id|stat_mode_t
suffix:semicolon
multiline_comment|/* dump statistical counters complete codes */
DECL|macro|DUMP_STAT_COMPLETED
mdefine_line|#define DUMP_STAT_COMPLETED&t;0xA005
DECL|macro|DUMP_RST_STAT_COMPLETED
mdefine_line|#define DUMP_RST_STAT_COMPLETED&t;0xA007
multiline_comment|/* Command Block (CB) Generic Header Structure*/
DECL|struct|_cb_header_t
r_typedef
r_struct
id|_cb_header_t
(brace
DECL|member|cb_status
id|u16
id|cb_status
suffix:semicolon
multiline_comment|/* Command Block Status */
DECL|member|cb_cmd
id|u16
id|cb_cmd
suffix:semicolon
multiline_comment|/* Command Block Command */
DECL|member|cb_lnk_ptr
id|u32
id|cb_lnk_ptr
suffix:semicolon
multiline_comment|/* Link To Next CB */
DECL|typedef|cb_header_t
)brace
id|cb_header_t
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
suffix:semicolon
singleline_comment|//* Individual Address Command Block (IA_CB)*/
DECL|struct|_ia_cb_t
r_typedef
r_struct
id|_ia_cb_t
(brace
DECL|member|ia_cb_hdr
id|cb_header_t
id|ia_cb_hdr
suffix:semicolon
DECL|member|ia_addr
id|u8
id|ia_addr
(braket
id|ETH_ALEN
)braket
suffix:semicolon
DECL|typedef|ia_cb_t
)brace
id|ia_cb_t
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
suffix:semicolon
multiline_comment|/* Configure Command Block (CONFIG_CB)*/
DECL|struct|_config_cb_t
r_typedef
r_struct
id|_config_cb_t
(brace
DECL|member|cfg_cbhdr
id|cb_header_t
id|cfg_cbhdr
suffix:semicolon
DECL|member|cfg_byte
id|u8
id|cfg_byte
(braket
id|CB_CFIG_BYTE_COUNT
op_plus
id|CB_CFIG_D102_BYTE_COUNT
)braket
suffix:semicolon
DECL|typedef|config_cb_t
)brace
id|config_cb_t
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
suffix:semicolon
multiline_comment|/* MultiCast Command Block (MULTICAST_CB)*/
DECL|struct|_multicast_cb_t
r_typedef
r_struct
id|_multicast_cb_t
(brace
DECL|member|mc_cbhdr
id|cb_header_t
id|mc_cbhdr
suffix:semicolon
DECL|member|mc_count
id|u16
id|mc_count
suffix:semicolon
multiline_comment|/* Number of multicast addresses */
DECL|member|mc_addr
id|u8
id|mc_addr
(braket
(paren
id|ETH_ALEN
op_star
id|MAX_MULTICAST_ADDRS
)paren
)braket
suffix:semicolon
DECL|typedef|mltcst_cb_t
)brace
id|mltcst_cb_t
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
suffix:semicolon
DECL|macro|UCODE_MAX_DWORDS
mdefine_line|#define UCODE_MAX_DWORDS&t;134
multiline_comment|/* Load Microcode Command Block (LOAD_UCODE_CB)*/
DECL|struct|_load_ucode_cb_t
r_typedef
r_struct
id|_load_ucode_cb_t
(brace
DECL|member|load_ucode_cbhdr
id|cb_header_t
id|load_ucode_cbhdr
suffix:semicolon
DECL|member|ucode_dword
id|u32
id|ucode_dword
(braket
id|UCODE_MAX_DWORDS
)braket
suffix:semicolon
DECL|typedef|load_ucode_cb_t
)brace
id|load_ucode_cb_t
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
suffix:semicolon
multiline_comment|/* Load Programmable Filter Data*/
DECL|struct|_filter_cb_t
r_typedef
r_struct
id|_filter_cb_t
(brace
DECL|member|filter_cb_hdr
id|cb_header_t
id|filter_cb_hdr
suffix:semicolon
DECL|member|filter_data
id|u32
id|filter_data
(braket
id|MAX_FILTER
)braket
suffix:semicolon
DECL|typedef|filter_cb_t
)brace
id|filter_cb_t
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
suffix:semicolon
multiline_comment|/* NON_TRANSMIT_CB -- Generic Non-Transmit Command Block &n; */
DECL|struct|_nxmit_cb_t
r_typedef
r_struct
id|_nxmit_cb_t
(brace
r_union
(brace
DECL|member|config
id|config_cb_t
id|config
suffix:semicolon
DECL|member|setup
id|ia_cb_t
id|setup
suffix:semicolon
DECL|member|load_ucode
id|load_ucode_cb_t
id|load_ucode
suffix:semicolon
DECL|member|multicast
id|mltcst_cb_t
id|multicast
suffix:semicolon
DECL|member|filter
id|filter_cb_t
id|filter
suffix:semicolon
DECL|member|ntcb
)brace
id|ntcb
suffix:semicolon
DECL|typedef|nxmit_cb_t
)brace
id|nxmit_cb_t
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
suffix:semicolon
multiline_comment|/*Block for queuing for postponed execution of the non-transmit commands*/
DECL|struct|_nxmit_cb_entry_t
r_typedef
r_struct
id|_nxmit_cb_entry_t
(brace
DECL|member|list_elem
r_struct
id|list_head
id|list_elem
suffix:semicolon
DECL|member|non_tx_cmd
id|nxmit_cb_t
op_star
id|non_tx_cmd
suffix:semicolon
DECL|member|dma_addr
id|dma_addr_t
id|dma_addr
suffix:semicolon
DECL|member|expiration_time
r_int
r_int
id|expiration_time
suffix:semicolon
DECL|typedef|nxmit_cb_entry_t
)brace
id|nxmit_cb_entry_t
suffix:semicolon
multiline_comment|/* States for postponed non tx commands execution */
DECL|enum|_non_tx_cmd_state_t
r_typedef
r_enum
id|_non_tx_cmd_state_t
(brace
DECL|enumerator|E100_NON_TX_IDLE
id|E100_NON_TX_IDLE
op_assign
l_int|0
comma
multiline_comment|/* No queued NON-TX commands */
DECL|enumerator|E100_WAIT_TX_FINISH
id|E100_WAIT_TX_FINISH
comma
multiline_comment|/* Wait for completion of the TX activities */
DECL|enumerator|E100_WAIT_NON_TX_FINISH
id|E100_WAIT_NON_TX_FINISH
multiline_comment|/* Wait for completion of the non TX command */
DECL|typedef|non_tx_cmd_state_t
)brace
id|non_tx_cmd_state_t
suffix:semicolon
multiline_comment|/* some defines for the ipcb */
DECL|macro|IPCB_IP_CHECKSUM_ENABLE
mdefine_line|#define IPCB_IP_CHECKSUM_ENABLE &t;BIT_4
DECL|macro|IPCB_TCPUDP_CHECKSUM_ENABLE
mdefine_line|#define IPCB_TCPUDP_CHECKSUM_ENABLE&t;BIT_5
DECL|macro|IPCB_TCP_PACKET
mdefine_line|#define IPCB_TCP_PACKET &t;&t;BIT_6
DECL|macro|IPCB_LARGESEND_ENABLE
mdefine_line|#define IPCB_LARGESEND_ENABLE &t;&t;BIT_7
DECL|macro|IPCB_HARDWAREPARSING_ENABLE
mdefine_line|#define IPCB_HARDWAREPARSING_ENABLE&t;BIT_0
DECL|macro|IPCB_INSERTVLAN_ENABLE
mdefine_line|#define IPCB_INSERTVLAN_ENABLE &t;&t;BIT_1
DECL|macro|IPCB_IP_ACTIVATION_DEFAULT
mdefine_line|#define IPCB_IP_ACTIVATION_DEFAULT      IPCB_HARDWAREPARSING_ENABLE
multiline_comment|/* Transmit Buffer Descriptor (TBD)*/
DECL|struct|_tbd_t
r_typedef
r_struct
id|_tbd_t
(brace
DECL|member|tbd_buf_addr
id|u32
id|tbd_buf_addr
suffix:semicolon
multiline_comment|/* Physical Transmit Buffer Address */
DECL|member|tbd_buf_cnt
id|u16
id|tbd_buf_cnt
suffix:semicolon
multiline_comment|/* Actual Count Of Bytes */
DECL|member|padd
id|u16
id|padd
suffix:semicolon
DECL|typedef|tbd_t
)brace
id|tbd_t
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
suffix:semicolon
multiline_comment|/* d102 specific fields */
DECL|struct|_tcb_ipcb_t
r_typedef
r_struct
id|_tcb_ipcb_t
(brace
DECL|member|schedule_low
id|u16
id|schedule_low
suffix:semicolon
DECL|member|ip_schedule
id|u8
id|ip_schedule
suffix:semicolon
DECL|member|ip_activation_high
id|u8
id|ip_activation_high
suffix:semicolon
DECL|member|vlan
id|u16
id|vlan
suffix:semicolon
DECL|member|ip_header_offset
id|u8
id|ip_header_offset
suffix:semicolon
DECL|member|tcp_header_offset
id|u8
id|tcp_header_offset
suffix:semicolon
r_union
(brace
DECL|member|sec_rec_phys_addr
id|u32
id|sec_rec_phys_addr
suffix:semicolon
DECL|member|tbd_zero_address
id|u32
id|tbd_zero_address
suffix:semicolon
DECL|member|tbd_sec_addr
)brace
id|tbd_sec_addr
suffix:semicolon
r_union
(brace
DECL|member|sec_rec_size
id|u16
id|sec_rec_size
suffix:semicolon
DECL|member|tbd_zero_size
id|u16
id|tbd_zero_size
suffix:semicolon
DECL|member|tbd_sec_size
)brace
id|tbd_sec_size
suffix:semicolon
DECL|member|total_tcp_payload
id|u16
id|total_tcp_payload
suffix:semicolon
DECL|typedef|tcb_ipcb_t
)brace
id|tcb_ipcb_t
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
suffix:semicolon
macro_line|#ifdef MAX_SKB_FRAGS
DECL|macro|E100_ZEROCOPY
mdefine_line|#define E100_ZEROCOPY
macro_line|#endif
macro_line|#ifdef E100_ZEROCOPY
DECL|macro|E100_TBD_ARRAY_SIZE
mdefine_line|#define E100_TBD_ARRAY_SIZE (2+MAX_SKB_FRAGS)
macro_line|#else
DECL|macro|E100_TBD_ARRAY_SIZE
mdefine_line|#define E100_TBD_ARRAY_SIZE 2
macro_line|#endif /*E100_ZEROCOPY */
multiline_comment|/* Transmit Command Block (TCB)*/
DECL|struct|_tcb_t
r_struct
id|_tcb_t
(brace
DECL|member|tcb_hdr
id|cb_header_t
id|tcb_hdr
suffix:semicolon
DECL|member|tcb_tbd_ptr
id|u32
id|tcb_tbd_ptr
suffix:semicolon
multiline_comment|/* TBD address */
DECL|member|tcb_cnt
id|u16
id|tcb_cnt
suffix:semicolon
multiline_comment|/* Data Bytes In TCB past header */
DECL|member|tcb_thrshld
id|u8
id|tcb_thrshld
suffix:semicolon
multiline_comment|/* TX Threshold for FIFO Extender */
DECL|member|tcb_tbd_num
id|u8
id|tcb_tbd_num
suffix:semicolon
r_union
(brace
DECL|member|ipcb
id|tcb_ipcb_t
id|ipcb
suffix:semicolon
multiline_comment|/* d102 ipcb fields */
DECL|member|tbd_array
id|tbd_t
id|tbd_array
(braket
id|E100_TBD_ARRAY_SIZE
)braket
suffix:semicolon
DECL|member|tcbu
)brace
id|tcbu
suffix:semicolon
multiline_comment|/* From here onward we can dump anything we want as long as the&n;&t; * size of the total structure is a multiple of a paragraph&n;&t; * boundary ( i.e. -16 bit aligned ).&n;&t; */
DECL|member|tbd_ptr
id|tbd_t
op_star
id|tbd_ptr
suffix:semicolon
macro_line|#ifdef E100_ZEROCOPY
DECL|member|tcb_tbd_dflt_ptr
id|u32
id|tcb_tbd_dflt_ptr
suffix:semicolon
multiline_comment|/* TBD address for non-segmented packet */
DECL|member|tcb_tbd_expand_ptr
id|u32
id|tcb_tbd_expand_ptr
suffix:semicolon
multiline_comment|/* TBD address for segmented packet */
macro_line|#endif&t;&t;&t;&t;/*E100_ZEROCOPY */
DECL|member|tcb_skb
r_struct
id|sk_buff
op_star
id|tcb_skb
suffix:semicolon
multiline_comment|/* the associated socket buffer */
DECL|member|tcb_phys
id|dma_addr_t
id|tcb_phys
suffix:semicolon
multiline_comment|/* phys addr of the TCB */
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
suffix:semicolon
macro_line|#ifndef _TCB_T_
DECL|macro|_TCB_T_
mdefine_line|#define _TCB_T_
DECL|typedef|tcb_t
r_typedef
r_struct
id|_tcb_t
id|tcb_t
suffix:semicolon
macro_line|#endif
multiline_comment|/* Receive Frame Descriptor (RFD) - will be using the simple model*/
DECL|struct|_rfd_t
r_struct
id|_rfd_t
(brace
multiline_comment|/* 8255x */
DECL|member|rfd_header
id|cb_header_t
id|rfd_header
suffix:semicolon
DECL|member|rfd_rbd_ptr
id|u32
id|rfd_rbd_ptr
suffix:semicolon
multiline_comment|/* Receive Buffer Descriptor Addr */
DECL|member|rfd_act_cnt
id|u16
id|rfd_act_cnt
suffix:semicolon
multiline_comment|/* Number Of Bytes Received */
DECL|member|rfd_sz
id|u16
id|rfd_sz
suffix:semicolon
multiline_comment|/* Number Of Bytes In RFD */
multiline_comment|/* D102 aka Gamla */
DECL|member|vlanid
id|u16
id|vlanid
suffix:semicolon
DECL|member|rcvparserstatus
id|u8
id|rcvparserstatus
suffix:semicolon
DECL|member|reserved
id|u8
id|reserved
suffix:semicolon
DECL|member|securitystatus
id|u16
id|securitystatus
suffix:semicolon
DECL|member|checksumstatus
id|u8
id|checksumstatus
suffix:semicolon
DECL|member|zerocopystatus
id|u8
id|zerocopystatus
suffix:semicolon
DECL|member|pad
id|u8
id|pad
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* data should be 16 byte aligned */
DECL|member|data
id|u8
id|data
(braket
id|RFD_DATA_SIZE
)braket
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
suffix:semicolon
macro_line|#ifndef _RFD_T_
DECL|macro|_RFD_T_
mdefine_line|#define _RFD_T_
DECL|typedef|rfd_t
r_typedef
r_struct
id|_rfd_t
id|rfd_t
suffix:semicolon
macro_line|#endif
multiline_comment|/* Receive Buffer Descriptor (RBD)*/
DECL|struct|_rbd_t
r_typedef
r_struct
id|_rbd_t
(brace
DECL|member|rbd_act_cnt
id|u16
id|rbd_act_cnt
suffix:semicolon
multiline_comment|/* Number Of Bytes Received */
DECL|member|rbd_filler
id|u16
id|rbd_filler
suffix:semicolon
DECL|member|rbd_lnk_addr
id|u32
id|rbd_lnk_addr
suffix:semicolon
multiline_comment|/* Link To Next RBD */
DECL|member|rbd_rcb_addr
id|u32
id|rbd_rcb_addr
suffix:semicolon
multiline_comment|/* Receive Buffer Address */
DECL|member|rbd_sz
id|u16
id|rbd_sz
suffix:semicolon
multiline_comment|/* Receive Buffer Size */
DECL|member|rbd_filler1
id|u16
id|rbd_filler1
suffix:semicolon
DECL|typedef|rbd_t
)brace
id|rbd_t
id|__attribute__
(paren
(paren
id|__packed__
)paren
)paren
suffix:semicolon
multiline_comment|/*&n; * This structure is used to maintain a FIFO access to a resource that is &n; * maintained as a circular queue. The resource to be maintained is pointed&n; * to by the &quot;data&quot; field in the structure below. In this driver the TCBs&squot;, &n; * TBDs&squot; &amp; RFDs&squot; are maintained  as a circular queue &amp; are managed thru this&n; * structure.&n; */
DECL|struct|_buf_pool_t
r_typedef
r_struct
id|_buf_pool_t
(brace
DECL|member|head
r_int
r_int
id|head
suffix:semicolon
multiline_comment|/* index to first used resource */
DECL|member|tail
r_int
r_int
id|tail
suffix:semicolon
multiline_comment|/* index to last used resource */
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
multiline_comment|/* points to resource pool */
DECL|typedef|buf_pool_t
)brace
id|buf_pool_t
suffix:semicolon
multiline_comment|/*Rx skb holding structure*/
DECL|struct|rx_list_elem
r_struct
id|rx_list_elem
(brace
DECL|member|list_elem
r_struct
id|list_head
id|list_elem
suffix:semicolon
DECL|member|dma_addr
id|dma_addr_t
id|dma_addr
suffix:semicolon
DECL|member|skb
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
)brace
suffix:semicolon
DECL|enum|next_cu_cmd_e
DECL|enumerator|RESUME_NO_WAIT
DECL|enumerator|RESUME_WAIT
DECL|enumerator|START_WAIT
r_enum
id|next_cu_cmd_e
(brace
id|RESUME_NO_WAIT
op_assign
l_int|0
comma
id|RESUME_WAIT
comma
id|START_WAIT
)brace
suffix:semicolon
DECL|enum|zlock_state_e
DECL|enumerator|ZLOCK_INITIAL
DECL|enumerator|ZLOCK_READING
DECL|enumerator|ZLOCK_SLEEPING
r_enum
id|zlock_state_e
(brace
id|ZLOCK_INITIAL
comma
id|ZLOCK_READING
comma
id|ZLOCK_SLEEPING
)brace
suffix:semicolon
DECL|enum|tx_queue_stop_type
DECL|enumerator|LONG_STOP
DECL|enumerator|SHORT_STOP
r_enum
id|tx_queue_stop_type
(brace
id|LONG_STOP
op_assign
l_int|0
comma
id|SHORT_STOP
)brace
suffix:semicolon
multiline_comment|/* 64 bit aligned size */
DECL|macro|E100_SIZE_64A
mdefine_line|#define E100_SIZE_64A(X) ((sizeof(X) + 7) &amp; ~0x7)
DECL|struct|_bd_dma_able_t
r_typedef
r_struct
id|_bd_dma_able_t
(brace
DECL|member|selftest
r_char
id|selftest
(braket
id|E100_SIZE_64A
c_func
(paren
id|self_test_t
)paren
)braket
suffix:semicolon
DECL|member|stats_counters
r_char
id|stats_counters
(braket
id|E100_SIZE_64A
c_func
(paren
id|max_counters_t
)paren
)braket
suffix:semicolon
DECL|typedef|bd_dma_able_t
)brace
id|bd_dma_able_t
suffix:semicolon
multiline_comment|/* bit masks for bool parameters */
DECL|macro|PRM_XSUMRX
mdefine_line|#define PRM_XSUMRX       0x00000001
DECL|macro|PRM_UCODE
mdefine_line|#define PRM_UCODE        0x00000002
DECL|macro|PRM_FC
mdefine_line|#define PRM_FC           0x00000004
DECL|macro|PRM_IFS
mdefine_line|#define PRM_IFS          0x00000008
DECL|macro|PRM_BUNDLE_SMALL
mdefine_line|#define PRM_BUNDLE_SMALL 0x00000010
DECL|macro|PRM_RX_CONG
mdefine_line|#define PRM_RX_CONG      0x00000020
DECL|struct|cfg_params
r_struct
id|cfg_params
(brace
DECL|member|e100_speed_duplex
r_int
id|e100_speed_duplex
suffix:semicolon
DECL|member|RxDescriptors
r_int
id|RxDescriptors
suffix:semicolon
DECL|member|TxDescriptors
r_int
id|TxDescriptors
suffix:semicolon
DECL|member|IntDelay
r_int
id|IntDelay
suffix:semicolon
DECL|member|BundleMax
r_int
id|BundleMax
suffix:semicolon
DECL|member|ber
r_int
id|ber
suffix:semicolon
DECL|member|PollingMaxWork
r_int
id|PollingMaxWork
suffix:semicolon
DECL|member|b_params
id|u32
id|b_params
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|e100_private
r_struct
id|e100_private
(brace
DECL|member|flags
id|u32
id|flags
suffix:semicolon
multiline_comment|/* board management flags */
DECL|member|tx_per_underrun
id|u32
id|tx_per_underrun
suffix:semicolon
multiline_comment|/* number of good tx frames per underrun */
DECL|member|tx_count
r_int
r_int
id|tx_count
suffix:semicolon
multiline_comment|/* count of tx frames, so we can request an interrupt */
DECL|member|tx_thld
id|u8
id|tx_thld
suffix:semicolon
multiline_comment|/* stores transmit threshold */
DECL|member|eeprom_size
id|u16
id|eeprom_size
suffix:semicolon
DECL|member|pwa_no
id|u32
id|pwa_no
suffix:semicolon
multiline_comment|/* PWA: xxxxxx-0xx */
DECL|member|perm_node_address
id|u8
id|perm_node_address
(braket
id|ETH_ALEN
)braket
suffix:semicolon
DECL|member|active_rx_list
r_struct
id|list_head
id|active_rx_list
suffix:semicolon
multiline_comment|/* list of rx buffers */
DECL|member|rx_struct_pool
r_struct
id|list_head
id|rx_struct_pool
suffix:semicolon
multiline_comment|/* pool of rx buffer struct headers */
DECL|member|rfd_size
id|u16
id|rfd_size
suffix:semicolon
multiline_comment|/* size of the adapter&squot;s RFD struct */
DECL|member|skb_req
r_int
id|skb_req
suffix:semicolon
multiline_comment|/* number of skbs neede by the adapter */
DECL|member|intr_mask
id|u8
id|intr_mask
suffix:semicolon
multiline_comment|/* mask for interrupt status */
DECL|member|dma_able
r_void
op_star
id|dma_able
suffix:semicolon
multiline_comment|/* dma allocated structs */
DECL|member|dma_able_phys
id|dma_addr_t
id|dma_able_phys
suffix:semicolon
DECL|member|selftest
id|self_test_t
op_star
id|selftest
suffix:semicolon
multiline_comment|/* pointer to self test area */
DECL|member|selftest_phys
id|dma_addr_t
id|selftest_phys
suffix:semicolon
multiline_comment|/* phys addr of selftest */
DECL|member|stats_counters
id|max_counters_t
op_star
id|stats_counters
suffix:semicolon
multiline_comment|/* pointer to stats table */
DECL|member|stat_cnt_phys
id|dma_addr_t
id|stat_cnt_phys
suffix:semicolon
multiline_comment|/* phys addr of stat counter area */
DECL|member|stat_mode
id|stat_mode_t
id|stat_mode
suffix:semicolon
multiline_comment|/* statistics mode: extended, TCO, basic */
DECL|member|scb
id|scb_t
op_star
id|scb
suffix:semicolon
multiline_comment|/* memory mapped ptr to 82557 scb */
DECL|member|last_tcb
id|tcb_t
op_star
id|last_tcb
suffix:semicolon
multiline_comment|/* pointer to last tcb sent */
DECL|member|tcb_pool
id|buf_pool_t
id|tcb_pool
suffix:semicolon
multiline_comment|/* adapter&squot;s TCB array */
DECL|member|tcb_phys
id|dma_addr_t
id|tcb_phys
suffix:semicolon
multiline_comment|/* phys addr of start of TCBs */
DECL|member|cur_line_speed
id|u16
id|cur_line_speed
suffix:semicolon
DECL|member|cur_dplx_mode
id|u16
id|cur_dplx_mode
suffix:semicolon
DECL|member|device
r_struct
id|net_device
op_star
id|device
suffix:semicolon
DECL|member|pdev
r_struct
id|pci_dev
op_star
id|pdev
suffix:semicolon
DECL|member|drv_stats
r_struct
id|driver_stats
id|drv_stats
suffix:semicolon
DECL|member|rev_id
id|u8
id|rev_id
suffix:semicolon
multiline_comment|/* adapter PCI revision ID */
DECL|member|device_type
r_int
r_int
id|device_type
suffix:semicolon
multiline_comment|/* device type from e100_vendor.h */
DECL|member|phy_addr
r_int
r_int
id|phy_addr
suffix:semicolon
multiline_comment|/* address of PHY component */
DECL|member|PhyId
r_int
r_int
id|PhyId
suffix:semicolon
multiline_comment|/* ID of PHY component */
DECL|member|PhyState
r_int
r_int
id|PhyState
suffix:semicolon
multiline_comment|/* state for the fix squelch algorithm */
DECL|member|PhyDelay
r_int
r_int
id|PhyDelay
suffix:semicolon
multiline_comment|/* delay for the fix squelch algorithm */
multiline_comment|/* Lock defintions for the driver */
DECL|member|bd_lock
id|spinlock_t
id|bd_lock
suffix:semicolon
multiline_comment|/* board lock */
DECL|member|bd_non_tx_lock
id|spinlock_t
id|bd_non_tx_lock
suffix:semicolon
multiline_comment|/* Non transmit command lock  */
DECL|member|config_lock
id|spinlock_t
id|config_lock
suffix:semicolon
multiline_comment|/* config block lock */
DECL|member|mdi_access_lock
id|spinlock_t
id|mdi_access_lock
suffix:semicolon
multiline_comment|/* mdi lock */
DECL|member|watchdog_timer
r_struct
id|timer_list
id|watchdog_timer
suffix:semicolon
multiline_comment|/* watchdog timer id */
multiline_comment|/* non-tx commands parameters */
DECL|member|nontx_timer_id
r_struct
id|timer_list
id|nontx_timer_id
suffix:semicolon
multiline_comment|/* non-tx timer id */
DECL|member|non_tx_cmd_list
r_struct
id|list_head
id|non_tx_cmd_list
suffix:semicolon
DECL|member|non_tx_command_state
id|non_tx_cmd_state_t
id|non_tx_command_state
suffix:semicolon
DECL|member|same_cmd_entry
id|nxmit_cb_entry_t
op_star
id|same_cmd_entry
(braket
id|CB_MAX_NONTX_CMD
)braket
suffix:semicolon
DECL|member|next_cu_cmd
r_enum
id|next_cu_cmd_e
id|next_cu_cmd
suffix:semicolon
multiline_comment|/* Zero Locking Algorithm data members */
DECL|member|zlock_state
r_enum
id|zlock_state_e
id|zlock_state
suffix:semicolon
DECL|member|zlock_read_data
id|u8
id|zlock_read_data
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* number of times each value 0-15 was read */
DECL|member|zlock_read_cnt
id|u16
id|zlock_read_cnt
suffix:semicolon
multiline_comment|/* counts number of reads */
DECL|member|zlock_sleep_cnt
id|ulong
id|zlock_sleep_cnt
suffix:semicolon
multiline_comment|/* keeps track of &quot;sleep&quot; time */
DECL|member|config
id|u8
id|config
(braket
id|CB_CFIG_BYTE_COUNT
op_plus
id|CB_CFIG_D102_BYTE_COUNT
)braket
suffix:semicolon
multiline_comment|/* IFS params */
DECL|member|ifs_state
id|u8
id|ifs_state
suffix:semicolon
DECL|member|ifs_value
id|u8
id|ifs_value
suffix:semicolon
DECL|member|params
r_struct
id|cfg_params
id|params
suffix:semicolon
multiline_comment|/* adapter&squot;s command line parameters */
DECL|member|proc_parent
r_struct
id|proc_dir_entry
op_star
id|proc_parent
suffix:semicolon
DECL|member|isolate_lock
id|rwlock_t
id|isolate_lock
suffix:semicolon
DECL|member|driver_isolated
r_int
id|driver_isolated
suffix:semicolon
DECL|member|speed_duplex_caps
id|u32
id|speed_duplex_caps
suffix:semicolon
multiline_comment|/* adapter&squot;s speed/duplex capabilities */
DECL|member|polling_tasklet
r_struct
id|tasklet_struct
id|polling_tasklet
suffix:semicolon
macro_line|#ifdef ETHTOOL_GWOL
multiline_comment|/* WOL params for ethtool */
DECL|member|wolsupported
id|u32
id|wolsupported
suffix:semicolon
DECL|member|wolopts
id|u32
id|wolopts
suffix:semicolon
DECL|member|ip_lbytes
id|u16
id|ip_lbytes
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
DECL|macro|E100_AUTONEG
mdefine_line|#define E100_AUTONEG        0
DECL|macro|E100_SPEED_10_HALF
mdefine_line|#define E100_SPEED_10_HALF  1
DECL|macro|E100_SPEED_10_FULL
mdefine_line|#define E100_SPEED_10_FULL  2
DECL|macro|E100_SPEED_100_HALF
mdefine_line|#define E100_SPEED_100_HALF 3
DECL|macro|E100_SPEED_100_FULL
mdefine_line|#define E100_SPEED_100_FULL 4
multiline_comment|/********* function prototypes *************/
r_extern
r_void
id|e100_isolate_driver
c_func
(paren
r_struct
id|e100_private
op_star
id|bdp
)paren
suffix:semicolon
r_extern
r_void
id|e100_sw_reset
c_func
(paren
r_struct
id|e100_private
op_star
id|bdp
comma
id|u32
id|reset_cmd
)paren
suffix:semicolon
r_extern
r_void
id|e100_start_cu
c_func
(paren
r_struct
id|e100_private
op_star
id|bdp
comma
id|tcb_t
op_star
id|tcb
)paren
suffix:semicolon
r_extern
r_void
id|e100_free_non_tx_cmd
c_func
(paren
r_struct
id|e100_private
op_star
id|bdp
comma
id|nxmit_cb_entry_t
op_star
id|non_tx_cmd
)paren
suffix:semicolon
r_extern
id|nxmit_cb_entry_t
op_star
id|e100_alloc_non_tx_cmd
c_func
(paren
r_struct
id|e100_private
op_star
id|bdp
)paren
suffix:semicolon
r_extern
r_int
r_char
id|e100_exec_non_cu_cmd
c_func
(paren
r_struct
id|e100_private
op_star
id|bdp
comma
id|nxmit_cb_entry_t
op_star
id|cmd
)paren
suffix:semicolon
r_extern
r_int
r_char
id|e100_selftest
c_func
(paren
r_struct
id|e100_private
op_star
id|bdp
comma
id|u32
op_star
id|st_timeout
comma
id|u32
op_star
id|st_result
)paren
suffix:semicolon
r_extern
r_int
r_char
id|e100_get_link_state
c_func
(paren
r_struct
id|e100_private
op_star
id|bdp
)paren
suffix:semicolon
r_extern
r_int
r_char
id|e100_wait_scb
c_func
(paren
r_struct
id|e100_private
op_star
id|bdp
)paren
suffix:semicolon
macro_line|#endif
eof
