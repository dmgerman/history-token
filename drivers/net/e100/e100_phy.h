multiline_comment|/*******************************************************************************&n;&n;This software program is available to you under a choice of one of two &n;licenses. You may choose to be licensed under either the GNU General Public &n;License (GPL) Version 2, June 1991, available at &n;http://www.fsf.org/copyleft/gpl.html, or the Intel BSD + Patent License, the &n;text of which follows:&n;&n;Recipient has requested a license and Intel Corporation (&quot;Intel&quot;) is willing&n;to grant a license for the software entitled Linux Base Driver for the &n;Intel(R) PRO/100 Family of Adapters (e100) (the &quot;Software&quot;) being provided &n;by Intel Corporation. The following definitions apply to this license:&n;&n;&quot;Licensed Patents&quot; means patent claims licensable by Intel Corporation which &n;are necessarily infringed by the use of sale of the Software alone or when &n;combined with the operating system referred to below.&n;&n;&quot;Recipient&quot; means the party to whom Intel delivers this Software.&n;&n;&quot;Licensee&quot; means Recipient and those third parties that receive a license to &n;any operating system available under the GNU Public License version 2.0 or &n;later.&n;&n;Copyright (c) 1999 - 2002 Intel Corporation.&n;All rights reserved.&n;&n;The license is provided to Recipient and Recipient&squot;s Licensees under the &n;following terms.&n;&n;Redistribution and use in source and binary forms of the Software, with or &n;without modification, are permitted provided that the following conditions &n;are met:&n;&n;Redistributions of source code of the Software may retain the above &n;copyright notice, this list of conditions and the following disclaimer.&n;&n;Redistributions in binary form of the Software may reproduce the above &n;copyright notice, this list of conditions and the following disclaimer in &n;the documentation and/or materials provided with the distribution.&n;&n;Neither the name of Intel Corporation nor the names of its contributors &n;shall be used to endorse or promote products derived from this Software &n;without specific prior written permission.&n;&n;Intel hereby grants Recipient and Licensees a non-exclusive, worldwide, &n;royalty-free patent license under Licensed Patents to make, use, sell, offer &n;to sell, import and otherwise transfer the Software, if any, in source code &n;and object code form. This license shall include changes to the Software &n;that are error corrections or other minor changes to the Software that do &n;not add functionality or features when the Software is incorporated in any &n;version of an operating system that has been distributed under the GNU &n;General Public License 2.0 or later. This patent license shall apply to the &n;combination of the Software and any operating system licensed under the GNU &n;Public License version 2.0 or later if, at the time Intel provides the &n;Software to Recipient, such addition of the Software to the then publicly &n;available versions of such operating systems available under the GNU Public &n;License version 2.0 or later (whether in gold, beta or alpha form) causes &n;such combination to be covered by the Licensed Patents. The patent license &n;shall not apply to any other combinations which include the Software. NO &n;hardware per se is licensed hereunder.&n;&n;THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS &quot;AS IS&quot; &n;AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE &n;IMPLIED WARRANTIES OF MECHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE &n;ARE DISCLAIMED. IN NO EVENT SHALL INTEL OR IT CONTRIBUTORS BE LIABLE FOR ANY &n;DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES &n;(INCLUDING, BUT NOT LIMITED, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; &n;ANY LOSS OF USE; DATA, OR PROFITS; OR BUSINESS INTERUPTION) HOWEVER CAUSED &n;AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY OR &n;TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE &n;OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n;*******************************************************************************/
macro_line|#ifndef _E100_PHY_INC_
DECL|macro|_E100_PHY_INC_
mdefine_line|#define _E100_PHY_INC_
macro_line|#include &quot;e100.h&quot;
macro_line|#include &lt;linux/mii.h&gt;
multiline_comment|/*&n; * Auto-polarity enable/disable&n; * e100_autopolarity = 0 =&gt; disable auto-polarity&n; * e100_autopolarity = 1 =&gt; enable auto-polarity&n; * e100_autopolarity = 2 =&gt; let software determine&n; */
DECL|macro|E100_AUTOPOLARITY
mdefine_line|#define E100_AUTOPOLARITY 2
DECL|macro|IS_NC3133
mdefine_line|#define IS_NC3133(bdp) (((bdp)-&gt;pdev-&gt;subsystem_vendor == 0x0E11) &amp;&amp; &bslash;&n;                        ((bdp)-&gt;pdev-&gt;subsystem_device == 0xB0E1))
DECL|macro|PHY_503
mdefine_line|#define PHY_503                 0
DECL|macro|PHY_100_A
mdefine_line|#define PHY_100_A               0x000003E0
DECL|macro|PHY_100_C
mdefine_line|#define PHY_100_C               0x035002A8
DECL|macro|PHY_NSC_TX
mdefine_line|#define PHY_NSC_TX              0x5c002000
DECL|macro|PHY_82562ET
mdefine_line|#define PHY_82562ET             0x033002A8
DECL|macro|PHY_82562EM
mdefine_line|#define PHY_82562EM             0x032002A8
DECL|macro|PHY_82562EH
mdefine_line|#define PHY_82562EH             0x017002A8
DECL|macro|PHY_82555_TX
mdefine_line|#define PHY_82555_TX            0x015002a8&t;/* added this for 82555 */
DECL|macro|PHY_OTHER
mdefine_line|#define PHY_OTHER               0xFFFF
DECL|macro|MAX_PHY_ADDR
mdefine_line|#define MAX_PHY_ADDR            31
DECL|macro|MIN_PHY_ADDR
mdefine_line|#define MIN_PHY_ADDR            0
DECL|macro|PHY_MODEL_REV_ID_MASK
mdefine_line|#define PHY_MODEL_REV_ID_MASK   0xFFF0FFFF
DECL|macro|PHY_DEFAULT_ADDRESS
mdefine_line|#define PHY_DEFAULT_ADDRESS 1
DECL|macro|PHY_ADDRESS_503
mdefine_line|#define PHY_ADDRESS_503 32
multiline_comment|/* MDI Control register bit definitions */
DECL|macro|MDI_PHY_READY
mdefine_line|#define MDI_PHY_READY&t;    BIT_28&t;/* PHY is ready for next MDI cycle */
DECL|macro|MDI_NC3133_CONFIG_REG
mdefine_line|#define MDI_NC3133_CONFIG_REG           0x19
DECL|macro|MDI_NC3133_100FX_ENABLE
mdefine_line|#define MDI_NC3133_100FX_ENABLE         BIT_2
DECL|macro|MDI_NC3133_INT_ENABLE_REG
mdefine_line|#define MDI_NC3133_INT_ENABLE_REG       0x17
DECL|macro|MDI_NC3133_INT_ENABLE
mdefine_line|#define MDI_NC3133_INT_ENABLE           BIT_1
multiline_comment|/* MDI Control register opcode definitions */
DECL|macro|MDI_WRITE
mdefine_line|#define MDI_WRITE 1&t;&t;/* Phy Write */
DECL|macro|MDI_READ
mdefine_line|#define MDI_READ  2&t;&t;/* Phy read */
multiline_comment|/* MDI register set*/
DECL|macro|AUTO_NEG_NEXT_PAGE_REG
mdefine_line|#define AUTO_NEG_NEXT_PAGE_REG&t;    0x07&t;/* Auto-negotiation next page xmit */
DECL|macro|EXTENDED_REG_0
mdefine_line|#define EXTENDED_REG_0&t;&t;    0x10&t;/* Extended reg 0 (Phy 100 modes) */
DECL|macro|EXTENDED_REG_1
mdefine_line|#define EXTENDED_REG_1&t;&t;    0x14&t;/* Extended reg 1 (Phy 100 error indications) */
DECL|macro|NSC_CONG_CONTROL_REG
mdefine_line|#define NSC_CONG_CONTROL_REG&t;    0x17&t;/* National (TX) congestion control */
DECL|macro|NSC_SPEED_IND_REG
mdefine_line|#define NSC_SPEED_IND_REG&t;    0x19&t;/* National (TX) speed indication */
multiline_comment|/* ############Start of 82555 specific defines################## */
multiline_comment|/* Intel 82555 specific registers */
DECL|macro|PHY_82555_CSR
mdefine_line|#define PHY_82555_CSR&t;&t;    0x10&t;/* 82555 CSR */
DECL|macro|PHY_82555_SPECIAL_CONTROL
mdefine_line|#define PHY_82555_SPECIAL_CONTROL   0x11&t;/* 82555 special control register */
DECL|macro|PHY_82555_RCV_ERR
mdefine_line|#define PHY_82555_RCV_ERR&t;    0x15&t;/* 82555 100BaseTx Receive Error&n;&t;&t;&t;&t;&t;&t; * Frame Counter */
DECL|macro|PHY_82555_SYMBOL_ERR
mdefine_line|#define PHY_82555_SYMBOL_ERR&t;    0x16&t;/* 82555 RCV Symbol Error Counter */
DECL|macro|PHY_82555_PREM_EOF_ERR
mdefine_line|#define PHY_82555_PREM_EOF_ERR&t;    0x17&t;/* 82555 100BaseTx RCV Premature End&n;&t;&t;&t;&t;&t;&t; * of Frame Error Counter */
DECL|macro|PHY_82555_EOF_COUNTER
mdefine_line|#define PHY_82555_EOF_COUNTER&t;    0x18&t;/* 82555 end of frame error counter */
DECL|macro|PHY_82555_MDI_EQUALIZER_CSR
mdefine_line|#define PHY_82555_MDI_EQUALIZER_CSR 0x1a&t;/* 82555 specific equalizer reg. */
multiline_comment|/* 82555 CSR bits */
DECL|macro|PHY_82555_SPEED_BIT
mdefine_line|#define PHY_82555_SPEED_BIT    BIT_1
DECL|macro|PHY_82555_POLARITY_BIT
mdefine_line|#define PHY_82555_POLARITY_BIT BIT_8
multiline_comment|/* 82555 equalizer reg. opcodes */
DECL|macro|ENABLE_ZERO_FORCING
mdefine_line|#define ENABLE_ZERO_FORCING  0x2010&t;/* write to ASD conf. reg. 0 */
DECL|macro|DISABLE_ZERO_FORCING
mdefine_line|#define DISABLE_ZERO_FORCING 0x2000&t;/* write to ASD conf. reg. 0 */
multiline_comment|/* 82555 special control reg. opcodes */
DECL|macro|DISABLE_AUTO_POLARITY
mdefine_line|#define DISABLE_AUTO_POLARITY 0x0010
DECL|macro|EXTENDED_SQUELCH_BIT
mdefine_line|#define EXTENDED_SQUELCH_BIT  BIT_2
multiline_comment|/* ############End of 82555 specific defines##################### */
multiline_comment|/* Auto-Negotiation advertisement register bit definitions*/
DECL|macro|NWAY_AD_FC_SUPPORTED
mdefine_line|#define NWAY_AD_FC_SUPPORTED    0x0400&t;/* Flow Control supported */
multiline_comment|/* Auto-Negotiation link partner ability register bit definitions*/
DECL|macro|NWAY_LP_ABILITY
mdefine_line|#define NWAY_LP_ABILITY&t;        0x07e0&t;/* technologies supported */
multiline_comment|/* PHY 100 Extended Register 0 bit definitions*/
DECL|macro|PHY_100_ER0_FDX_INDIC
mdefine_line|#define PHY_100_ER0_FDX_INDIC&t;BIT_0&t;/* 1 = FDX, 0 = half duplex */
DECL|macro|PHY_100_ER0_SPEED_INDIC
mdefine_line|#define PHY_100_ER0_SPEED_INDIC BIT_1&t;/* 1 = 100Mbps, 0= 10Mbps */
multiline_comment|/* National Semiconductor TX phy congestion control register bit definitions*/
DECL|macro|NSC_TX_CONG_TXREADY
mdefine_line|#define NSC_TX_CONG_TXREADY  BIT_10&t;/* Makes TxReady an input */
DECL|macro|NSC_TX_CONG_ENABLE
mdefine_line|#define NSC_TX_CONG_ENABLE   BIT_8&t;/* Enables congestion control */
multiline_comment|/* National Semiconductor TX phy speed indication register bit definitions*/
DECL|macro|NSC_TX_SPD_INDC_SPEED
mdefine_line|#define NSC_TX_SPD_INDC_SPEED BIT_6&t;/* 0 = 100Mbps, 1=10Mbps */
multiline_comment|/************* function prototypes ************/
r_extern
r_int
r_char
id|e100_phy_init
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
id|e100_update_link_state
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
id|e100_phy_check
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
id|e100_phy_set_speed_duplex
c_func
(paren
r_struct
id|e100_private
op_star
id|bdp
comma
r_int
r_char
id|force_restart
)paren
suffix:semicolon
r_extern
r_void
id|e100_phy_reset
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
id|e100_mdi_write
c_func
(paren
r_struct
id|e100_private
op_star
comma
id|u32
comma
id|u32
comma
id|u16
)paren
suffix:semicolon
r_extern
r_void
id|e100_mdi_read
c_func
(paren
r_struct
id|e100_private
op_star
comma
id|u32
comma
id|u32
comma
id|u16
op_star
)paren
suffix:semicolon
macro_line|#endif
eof
