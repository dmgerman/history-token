multiline_comment|/*******************************************************************************&n;&n;This software program is available to you under a choice of one of two &n;licenses. You may choose to be licensed under either the GNU General Public &n;License 2.0, June 1991, available at http://www.fsf.org/copyleft/gpl.html, &n;or the Intel BSD + Patent License, the text of which follows:&n;&n;Recipient has requested a license and Intel Corporation (&quot;Intel&quot;) is willing&n;to grant a license for the software entitled Linux Base Driver for the &n;Intel(R) PRO/100 Family of Adapters (e100) (the &quot;Software&quot;) being provided &n;by Intel Corporation. The following definitions apply to this license:&n;&n;&quot;Licensed Patents&quot; means patent claims licensable by Intel Corporation which &n;are necessarily infringed by the use of sale of the Software alone or when &n;combined with the operating system referred to below.&n;&n;&quot;Recipient&quot; means the party to whom Intel delivers this Software.&n;&n;&quot;Licensee&quot; means Recipient and those third parties that receive a license to &n;any operating system available under the GNU General Public License 2.0 or &n;later.&n;&n;Copyright (c) 1999 - 2002 Intel Corporation.&n;All rights reserved.&n;&n;The license is provided to Recipient and Recipient&squot;s Licensees under the &n;following terms.&n;&n;Redistribution and use in source and binary forms of the Software, with or &n;without modification, are permitted provided that the following conditions &n;are met:&n;&n;Redistributions of source code of the Software may retain the above &n;copyright notice, this list of conditions and the following disclaimer.&n;&n;Redistributions in binary form of the Software may reproduce the above &n;copyright notice, this list of conditions and the following disclaimer in &n;the documentation and/or materials provided with the distribution.&n;&n;Neither the name of Intel Corporation nor the names of its contributors &n;shall be used to endorse or promote products derived from this Software &n;without specific prior written permission.&n;&n;Intel hereby grants Recipient and Licensees a non-exclusive, worldwide, &n;royalty-free patent license under Licensed Patents to make, use, sell, offer &n;to sell, import and otherwise transfer the Software, if any, in source code &n;and object code form. This license shall include changes to the Software &n;that are error corrections or other minor changes to the Software that do &n;not add functionality or features when the Software is incorporated in any &n;version of an operating system that has been distributed under the GNU &n;General Public License 2.0 or later. This patent license shall apply to the &n;combination of the Software and any operating system licensed under the GNU &n;General Public License 2.0 or later if, at the time Intel provides the &n;Software to Recipient, such addition of the Software to the then publicly &n;available versions of such operating systems available under the GNU General &n;Public License 2.0 or later (whether in gold, beta or alpha form) causes &n;such combination to be covered by the Licensed Patents. The patent license &n;shall not apply to any other combinations which include the Software. NO &n;hardware per se is licensed hereunder.&n;&n;THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS &quot;AS IS&quot; &n;AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE &n;IMPLIED WARRANTIES OF MECHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE &n;ARE DISCLAIMED. IN NO EVENT SHALL INTEL OR IT CONTRIBUTORS BE LIABLE FOR ANY &n;DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES &n;(INCLUDING, BUT NOT LIMITED, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; &n;ANY LOSS OF USE; DATA, OR PROFITS; OR BUSINESS INTERUPTION) HOWEVER CAUSED &n;AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY OR &n;TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE &n;OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n;*******************************************************************************/
macro_line|#ifndef _E100_CONFIG_INC_
DECL|macro|_E100_CONFIG_INC_
mdefine_line|#define _E100_CONFIG_INC_
macro_line|#include &quot;e100.h&quot;
DECL|macro|E100_CONFIG
mdefine_line|#define E100_CONFIG(bdp, X) ((bdp)-&gt;config[0] = max_t(u8, (bdp)-&gt;config[0], (X)+1))
DECL|macro|CB_CFIG_MIN_PARAMS
mdefine_line|#define CB_CFIG_MIN_PARAMS         8
multiline_comment|/* byte 0 bit definitions*/
DECL|macro|CB_CFIG_BYTE_COUNT_MASK
mdefine_line|#define CB_CFIG_BYTE_COUNT_MASK     BIT_0_5&t;/* Byte count occupies bit 5-0 */
multiline_comment|/* byte 1 bit definitions*/
DECL|macro|CB_CFIG_RXFIFO_LIMIT_MASK
mdefine_line|#define CB_CFIG_RXFIFO_LIMIT_MASK   BIT_0_4&t;/* RxFifo limit mask */
DECL|macro|CB_CFIG_TXFIFO_LIMIT_MASK
mdefine_line|#define CB_CFIG_TXFIFO_LIMIT_MASK   BIT_4_7&t;/* TxFifo limit mask */
multiline_comment|/* byte 2 bit definitions -- ADAPTIVE_IFS*/
multiline_comment|/* word 3 bit definitions -- RESERVED*/
multiline_comment|/* Changed for 82558 enhancements */
multiline_comment|/* byte 3 bit definitions */
DECL|macro|CB_CFIG_MWI_EN
mdefine_line|#define CB_CFIG_MWI_EN      BIT_0&t;/* Enable MWI on PCI bus */
DECL|macro|CB_CFIG_TYPE_EN
mdefine_line|#define CB_CFIG_TYPE_EN     BIT_1&t;/* Type Enable */
DECL|macro|CB_CFIG_READAL_EN
mdefine_line|#define CB_CFIG_READAL_EN   BIT_2&t;/* Enable Read Align */
DECL|macro|CB_CFIG_TERMCL_EN
mdefine_line|#define CB_CFIG_TERMCL_EN   BIT_3&t;/* Cache line write  */
multiline_comment|/* byte 4 bit definitions*/
DECL|macro|CB_CFIG_RX_MIN_DMA_MASK
mdefine_line|#define CB_CFIG_RX_MIN_DMA_MASK     BIT_0_6&t;/* Rx minimum DMA count mask */
multiline_comment|/* byte 5 bit definitions*/
DECL|macro|CB_CFIG_TX_MIN_DMA_MASK
mdefine_line|#define CB_CFIG_TX_MIN_DMA_MASK BIT_0_6&t;/* Tx minimum DMA count mask */
DECL|macro|CB_CFIG_DMBC_EN
mdefine_line|#define CB_CFIG_DMBC_EN         BIT_7&t;/* Enable Tx/Rx min. DMA counts */
multiline_comment|/* Changed for 82558 enhancements */
multiline_comment|/* byte 6 bit definitions*/
DECL|macro|CB_CFIG_LATE_SCB
mdefine_line|#define CB_CFIG_LATE_SCB           BIT_0&t;/* Update SCB After New Tx Start */
DECL|macro|CB_CFIG_DIRECT_DMA_DIS
mdefine_line|#define CB_CFIG_DIRECT_DMA_DIS     BIT_1&t;/* Direct DMA mode */
DECL|macro|CB_CFIG_TNO_INT
mdefine_line|#define CB_CFIG_TNO_INT            BIT_2&t;/* Tx Not OK Interrupt */
DECL|macro|CB_CFIG_TCO_STAT
mdefine_line|#define CB_CFIG_TCO_STAT           BIT_2&t;/* TCO statistics in 559 and above */
DECL|macro|CB_CFIG_CI_INT
mdefine_line|#define CB_CFIG_CI_INT             BIT_3&t;/* Command Complete Interrupt */
DECL|macro|CB_CFIG_EXT_TCB_DIS
mdefine_line|#define CB_CFIG_EXT_TCB_DIS        BIT_4&t;/* Extended TCB */
DECL|macro|CB_CFIG_EXT_STAT_DIS
mdefine_line|#define CB_CFIG_EXT_STAT_DIS       BIT_5&t;/* Extended Stats */
DECL|macro|CB_CFIG_SAVE_BAD_FRAMES
mdefine_line|#define CB_CFIG_SAVE_BAD_FRAMES    BIT_7&t;/* Save Bad Frames Enabled */
multiline_comment|/* byte 7 bit definitions*/
DECL|macro|CB_CFIG_DISC_SHORT_FRAMES
mdefine_line|#define CB_CFIG_DISC_SHORT_FRAMES   BIT_0&t;/* Discard Short Frames */
DECL|macro|CB_CFIG_DYNTBD_EN
mdefine_line|#define CB_CFIG_DYNTBD_EN           BIT_7&t;/* Enable dynamic TBD */
multiline_comment|/* Enable extended RFD&squot;s on D102 */
DECL|macro|CB_CFIG_EXTENDED_RFD
mdefine_line|#define CB_CFIG_EXTENDED_RFD        BIT_5
multiline_comment|/* byte 8 bit definitions*/
DECL|macro|CB_CFIG_503_MII
mdefine_line|#define CB_CFIG_503_MII             BIT_0&t;/* 503 vs. MII mode */
multiline_comment|/* byte 9 bit definitions -- pre-defined all zeros*/
DECL|macro|CB_LINK_STATUS_WOL
mdefine_line|#define CB_LINK_STATUS_WOL&t;BIT_5
multiline_comment|/* byte 10 bit definitions*/
DECL|macro|CB_CFIG_NO_SRCADR
mdefine_line|#define CB_CFIG_NO_SRCADR       BIT_3&t;/* No Source Address Insertion */
DECL|macro|CB_CFIG_PREAMBLE_LEN
mdefine_line|#define CB_CFIG_PREAMBLE_LEN    BIT_4_5&t;/* Preamble Length */
DECL|macro|CB_CFIG_LOOPBACK_MODE
mdefine_line|#define CB_CFIG_LOOPBACK_MODE   BIT_6_7&t;/* Loopback Mode */
DECL|macro|CB_CFIG_LOOPBACK_NORMAL
mdefine_line|#define CB_CFIG_LOOPBACK_NORMAL 0
DECL|macro|CB_CFIG_LOOPBACK_INTERNAL
mdefine_line|#define CB_CFIG_LOOPBACK_INTERNAL BIT_6
DECL|macro|CB_CFIG_LOOPBACK_EXTERNAL
mdefine_line|#define CB_CFIG_LOOPBACK_EXTERNAL BIT_6_7
multiline_comment|/* byte 11 bit definitions*/
DECL|macro|CB_CFIG_LINEAR_PRIORITY
mdefine_line|#define CB_CFIG_LINEAR_PRIORITY     BIT_0_2&t;/* Linear Priority */
multiline_comment|/* byte 12 bit definitions*/
DECL|macro|CB_CFIG_LINEAR_PRI_MODE
mdefine_line|#define CB_CFIG_LINEAR_PRI_MODE     BIT_0&t;/* Linear Priority mode */
DECL|macro|CB_CFIG_IFS_MASK
mdefine_line|#define CB_CFIG_IFS_MASK            BIT_4_7&t;/* Interframe Spacing mask */
multiline_comment|/* byte 13 bit definitions -- pre-defined all zeros*/
multiline_comment|/* byte 14 bit definitions -- pre-defined 0xf2*/
multiline_comment|/* byte 15 bit definitions*/
DECL|macro|CB_CFIG_PROMISCUOUS
mdefine_line|#define CB_CFIG_PROMISCUOUS         BIT_0&t;/* Promiscuous Mode Enable */
DECL|macro|CB_CFIG_BROADCAST_DIS
mdefine_line|#define CB_CFIG_BROADCAST_DIS       BIT_1&t;/* Broadcast Mode Disable */
DECL|macro|CB_CFIG_CRS_OR_CDT
mdefine_line|#define CB_CFIG_CRS_OR_CDT          BIT_7&t;/* CRS Or CDT */
multiline_comment|/* byte 16 bit definitions -- pre-defined all zeros*/
DECL|macro|DFLT_FC_DELAY_LSB
mdefine_line|#define DFLT_FC_DELAY_LSB  0x1f&t;/* Delay for outgoing Pause frames */
DECL|macro|DFLT_NO_FC_DELAY_LSB
mdefine_line|#define DFLT_NO_FC_DELAY_LSB  0x00&t;/* no flow control default value */
multiline_comment|/* byte 17 bit definitions -- pre-defined 0x40*/
DECL|macro|DFLT_FC_DELAY_MSB
mdefine_line|#define DFLT_FC_DELAY_MSB  0x01&t;/* Delay for outgoing Pause frames */
DECL|macro|DFLT_NO_FC_DELAY_MSB
mdefine_line|#define DFLT_NO_FC_DELAY_MSB  0x40&t;/* no flow control default value */
multiline_comment|/* byte 18 bit definitions*/
DECL|macro|CB_CFIG_STRIPPING
mdefine_line|#define CB_CFIG_STRIPPING           BIT_0&t;/* Padding Disabled */
DECL|macro|CB_CFIG_PADDING
mdefine_line|#define CB_CFIG_PADDING             BIT_1&t;/* Padding Disabled */
DECL|macro|CB_CFIG_CRC_IN_MEM
mdefine_line|#define CB_CFIG_CRC_IN_MEM          BIT_2&t;/* Transfer CRC To Memory */
multiline_comment|/* byte 19 bit definitions*/
DECL|macro|CB_CFIG_TX_ADDR_WAKE
mdefine_line|#define CB_CFIG_TX_ADDR_WAKE        BIT_0&t;/* Address Wakeup */
DECL|macro|CB_DISABLE_MAGPAK_WAKE
mdefine_line|#define CB_DISABLE_MAGPAK_WAKE      BIT_1&t;/* Magic Packet Wakeup disable */
multiline_comment|/* Changed TX_FC_EN to TX_FC_DIS because 0 enables, 1 disables. Jul 8, 1999 */
DECL|macro|CB_CFIG_TX_FC_DIS
mdefine_line|#define CB_CFIG_TX_FC_DIS           BIT_2&t;/* Tx Flow Control Disable */
DECL|macro|CB_CFIG_FC_RESTOP
mdefine_line|#define CB_CFIG_FC_RESTOP           BIT_3&t;/* Rx Flow Control Restop */
DECL|macro|CB_CFIG_FC_RESTART
mdefine_line|#define CB_CFIG_FC_RESTART          BIT_4&t;/* Rx Flow Control Restart */
DECL|macro|CB_CFIG_FC_REJECT
mdefine_line|#define CB_CFIG_FC_REJECT           BIT_5&t;/* Rx Flow Control Restart */
DECL|macro|CB_CFIG_FC_OPTS
mdefine_line|#define CB_CFIG_FC_OPTS (CB_CFIG_FC_RESTOP | CB_CFIG_FC_RESTART | CB_CFIG_FC_REJECT)
multiline_comment|/* end 82558/9 specifics */
DECL|macro|CB_CFIG_FORCE_FDX
mdefine_line|#define CB_CFIG_FORCE_FDX           BIT_6&t;/* Force Full Duplex */
DECL|macro|CB_CFIG_FDX_ENABLE
mdefine_line|#define CB_CFIG_FDX_ENABLE          BIT_7&t;/* Full Duplex Enabled */
multiline_comment|/* byte 20 bit definitions*/
DECL|macro|CB_CFIG_MULTI_IA
mdefine_line|#define CB_CFIG_MULTI_IA            BIT_6&t;/* Multiple IA Addr */
multiline_comment|/* byte 21 bit definitions*/
DECL|macro|CB_CFIG_MULTICAST_ALL
mdefine_line|#define CB_CFIG_MULTICAST_ALL       BIT_3&t;/* Multicast All */
multiline_comment|/* byte 22 bit defines */
DECL|macro|CB_CFIG_RECEIVE_GAMLA_MODE
mdefine_line|#define CB_CFIG_RECEIVE_GAMLA_MODE  BIT_0&t;/* D102 receive mode */
DECL|macro|CB_CFIG_VLAN_DROP_ENABLE
mdefine_line|#define CB_CFIG_VLAN_DROP_ENABLE    BIT_1&t;/* vlan stripping */
DECL|macro|CB_CFIG_LONG_RX_OK
mdefine_line|#define CB_CFIG_LONG_RX_OK&t;    BIT_3
DECL|macro|NO_LOOPBACK
mdefine_line|#define NO_LOOPBACK&t;0&t;
DECL|macro|MAC_LOOPBACK
mdefine_line|#define MAC_LOOPBACK&t;0x01
DECL|macro|PHY_LOOPBACK
mdefine_line|#define PHY_LOOPBACK&t;0x02
multiline_comment|/* function prototypes */
r_extern
r_void
id|e100_config_init
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
id|e100_force_config
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
id|e100_config
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
id|e100_config_fc
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
id|e100_config_promisc
c_func
(paren
r_struct
id|e100_private
op_star
id|bdp
comma
r_int
r_char
id|enable
)paren
suffix:semicolon
r_extern
r_void
id|e100_config_brdcast_dsbl
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
id|e100_config_mulcast_enbl
c_func
(paren
r_struct
id|e100_private
op_star
id|bdp
comma
r_int
r_char
id|enable
)paren
suffix:semicolon
r_extern
r_void
id|e100_config_ifs
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
id|e100_config_force_dplx
c_func
(paren
r_struct
id|e100_private
op_star
id|bdp
)paren
suffix:semicolon
r_extern
id|u8
id|e100_config_loopback_mode
c_func
(paren
r_struct
id|e100_private
op_star
id|bdp
comma
id|u8
id|mode
)paren
suffix:semicolon
r_extern
id|u8
id|e100_config_dynamic_tbd
c_func
(paren
r_struct
id|e100_private
op_star
id|bdp
comma
id|u8
id|enable
)paren
suffix:semicolon
r_extern
id|u8
id|e100_config_tcb_ext_enable
c_func
(paren
r_struct
id|e100_private
op_star
id|bdp
comma
id|u8
id|enable
)paren
suffix:semicolon
macro_line|#endif /* _E100_CONFIG_INC_ */
eof
