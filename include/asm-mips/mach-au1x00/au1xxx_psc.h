multiline_comment|/*&n; *&n; * BRIEF MODULE DESCRIPTION&n; *&t;Include file for Alchemy Semiconductor&squot;s Au1k CPU.&n; *&n; * Copyright 2004 Embedded Edge, LLC&n; *&t;dan@embeddededge.com&n; *&n; *  This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR IMPLIED&n; *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; */
multiline_comment|/* Specifics for the Au1xxx Programmable Serial Controllers, first&n; * seen in the AU1550 part.&n; */
macro_line|#ifndef _AU1000_PSC_H_
DECL|macro|_AU1000_PSC_H_
mdefine_line|#define _AU1000_PSC_H_
multiline_comment|/* The PSC base addresses.  */
macro_line|#ifdef CONFIG_SOC_AU1550
DECL|macro|PSC0_BASE_ADDR
mdefine_line|#define PSC0_BASE_ADDR&t;&t;0xb1a00000
DECL|macro|PSC1_BASE_ADDR
mdefine_line|#define PSC1_BASE_ADDR&t;&t;0xb1b00000
DECL|macro|PSC2_BASE_ADDR
mdefine_line|#define PSC2_BASE_ADDR&t;&t;0xb0a00000
DECL|macro|PSC3_BASE_ADDR
mdefine_line|#define PSC3_BASE_ADDR&t;&t;0xb0d00000
macro_line|#endif
multiline_comment|/* The PSC select and control registers are common to&n; * all protocols.&n; */
DECL|macro|PSC_SEL_OFFSET
mdefine_line|#define PSC_SEL_OFFSET&t;&t;0x00000000
DECL|macro|PSC_CTRL_OFFSET
mdefine_line|#define PSC_CTRL_OFFSET&t;&t;0x00000004
DECL|macro|PSC_SEL_CLK_MASK
mdefine_line|#define PSC_SEL_CLK_MASK&t;(3 &lt;&lt; 4)
DECL|macro|PSC_SEL_CLK_INTCLK
mdefine_line|#define PSC_SEL_CLK_INTCLK&t;(0 &lt;&lt; 4)
DECL|macro|PSC_SEL_CLK_EXTCLK
mdefine_line|#define PSC_SEL_CLK_EXTCLK&t;(1 &lt;&lt; 4)
DECL|macro|PSC_SEL_CLK_SERCLK
mdefine_line|#define PSC_SEL_CLK_SERCLK&t;(2 &lt;&lt; 4)
DECL|macro|PSC_SEL_PS_MASK
mdefine_line|#define PSC_SEL_PS_MASK&t;&t;0x00000007
DECL|macro|PSC_SEL_PS_DISABLED
mdefine_line|#define PSC_SEL_PS_DISABLED&t;(0)
DECL|macro|PSC_SEL_PS_SPIMODE
mdefine_line|#define PSC_SEL_PS_SPIMODE&t;(2)
DECL|macro|PSC_SEL_PS_I2SMODE
mdefine_line|#define PSC_SEL_PS_I2SMODE&t;(3)
DECL|macro|PSC_SEL_PS_AC97MODE
mdefine_line|#define PSC_SEL_PS_AC97MODE&t;(4)
DECL|macro|PSC_SEL_PS_SMBUSMODE
mdefine_line|#define PSC_SEL_PS_SMBUSMODE&t;(5)
DECL|macro|PSC_CTRL_DISABLE
mdefine_line|#define PSC_CTRL_DISABLE&t;(0)
DECL|macro|PSC_CTRL_SUSPEND
mdefine_line|#define PSC_CTRL_SUSPEND&t;(2)
DECL|macro|PSC_CTRL_ENABLE
mdefine_line|#define PSC_CTRL_ENABLE&t;&t;(3)
multiline_comment|/* AC97 Registers.&n;*/
DECL|macro|PSC_AC97CFG_OFFSET
mdefine_line|#define PSC_AC97CFG_OFFSET&t;0x00000008
DECL|macro|PSC_AC97MSK_OFFSET
mdefine_line|#define PSC_AC97MSK_OFFSET&t;0x0000000c
DECL|macro|PSC_AC97PCR_OFFSET
mdefine_line|#define PSC_AC97PCR_OFFSET&t;0x00000010
DECL|macro|PSC_AC97STAT_OFFSET
mdefine_line|#define PSC_AC97STAT_OFFSET&t;0x00000014
DECL|macro|PSC_AC97EVNT_OFFSET
mdefine_line|#define PSC_AC97EVNT_OFFSET&t;0x00000018
DECL|macro|PSC_AC97TXRX_OFFSET
mdefine_line|#define PSC_AC97TXRX_OFFSET&t;0x0000001c
DECL|macro|PSC_AC97CDC_OFFSET
mdefine_line|#define PSC_AC97CDC_OFFSET&t;0x00000020
DECL|macro|PSC_AC97RST_OFFSET
mdefine_line|#define PSC_AC97RST_OFFSET&t;0x00000024
DECL|macro|PSC_AC97GPO_OFFSET
mdefine_line|#define PSC_AC97GPO_OFFSET&t;0x00000028
DECL|macro|PSC_AC97GPI_OFFSET
mdefine_line|#define PSC_AC97GPI_OFFSET&t;0x0000002c
DECL|macro|AC97_PSC_SEL
mdefine_line|#define AC97_PSC_SEL&t;&t;(AC97_PSC_BASE + PSC_SEL_OFFSET)
DECL|macro|AC97_PSC_CTRL
mdefine_line|#define AC97_PSC_CTRL&t;&t;(AC97_PSC_BASE + PSC_CTRL_OFFSET)
DECL|macro|PSC_AC97CFG
mdefine_line|#define PSC_AC97CFG&t;&t;(AC97_PSC_BASE + PSC_AC97CFG_OFFSET)
DECL|macro|PSC_AC97MSK
mdefine_line|#define PSC_AC97MSK&t;&t;(AC97_PSC_BASE + PSC_AC97MSK_OFFSET)
DECL|macro|PSC_AC97PCR
mdefine_line|#define PSC_AC97PCR&t;&t;(AC97_PSC_BASE + PSC_AC97PCR_OFFSET)
DECL|macro|PSC_AC97STAT
mdefine_line|#define PSC_AC97STAT&t;&t;(AC97_PSC_BASE + PSC_AC97STAT_OFFSET)
DECL|macro|PSC_AC97EVNT
mdefine_line|#define PSC_AC97EVNT&t;&t;(AC97_PSC_BASE + PSC_AC97EVNT_OFFSET)
DECL|macro|PSC_AC97TXRX
mdefine_line|#define PSC_AC97TXRX&t;&t;(AC97_PSC_BASE + PSC_AC97TXRX_OFFSET)
DECL|macro|PSC_AC97CDC
mdefine_line|#define PSC_AC97CDC&t;&t;(AC97_PSC_BASE + PSC_AC97CDC_OFFSET)
DECL|macro|PSC_AC97RST
mdefine_line|#define PSC_AC97RST&t;&t;(AC97_PSC_BASE + PSC_AC97RST_OFFSET)
DECL|macro|PSC_AC97GPO
mdefine_line|#define PSC_AC97GPO&t;&t;(AC97_PSC_BASE + PSC_AC97GPO_OFFSET)
DECL|macro|PSC_AC97GPI
mdefine_line|#define PSC_AC97GPI&t;&t;(AC97_PSC_BASE + PSC_AC97GPI_OFFSET)
multiline_comment|/* AC97 Config Register.&n;*/
DECL|macro|PSC_AC97CFG_RT_MASK
mdefine_line|#define PSC_AC97CFG_RT_MASK&t;(3 &lt;&lt; 30)
DECL|macro|PSC_AC97CFG_RT_FIFO1
mdefine_line|#define PSC_AC97CFG_RT_FIFO1&t;(0 &lt;&lt; 30)
DECL|macro|PSC_AC97CFG_RT_FIFO2
mdefine_line|#define PSC_AC97CFG_RT_FIFO2&t;(1 &lt;&lt; 30)
DECL|macro|PSC_AC97CFG_RT_FIFO4
mdefine_line|#define PSC_AC97CFG_RT_FIFO4&t;(2 &lt;&lt; 30)
DECL|macro|PSC_AC97CFG_RT_FIFO8
mdefine_line|#define PSC_AC97CFG_RT_FIFO8&t;(3 &lt;&lt; 30)
DECL|macro|PSC_AC97CFG_TT_MASK
mdefine_line|#define PSC_AC97CFG_TT_MASK&t;(3 &lt;&lt; 28)
DECL|macro|PSC_AC97CFG_TT_FIFO1
mdefine_line|#define PSC_AC97CFG_TT_FIFO1&t;(0 &lt;&lt; 28)
DECL|macro|PSC_AC97CFG_TT_FIFO2
mdefine_line|#define PSC_AC97CFG_TT_FIFO2&t;(1 &lt;&lt; 28)
DECL|macro|PSC_AC97CFG_TT_FIFO4
mdefine_line|#define PSC_AC97CFG_TT_FIFO4&t;(2 &lt;&lt; 28)
DECL|macro|PSC_AC97CFG_TT_FIFO8
mdefine_line|#define PSC_AC97CFG_TT_FIFO8&t;(3 &lt;&lt; 28)
DECL|macro|PSC_AC97CFG_DD_DISABLE
mdefine_line|#define PSC_AC97CFG_DD_DISABLE&t;(1 &lt;&lt; 27)
DECL|macro|PSC_AC97CFG_DE_ENABLE
mdefine_line|#define PSC_AC97CFG_DE_ENABLE&t;(1 &lt;&lt; 26)
DECL|macro|PSC_AC97CFG_SE_ENABLE
mdefine_line|#define PSC_AC97CFG_SE_ENABLE&t;(1 &lt;&lt; 25)
DECL|macro|PSC_AC97CFG_LEN_MASK
mdefine_line|#define PSC_AC97CFG_LEN_MASK&t;(0xf &lt;&lt; 21)
DECL|macro|PSC_AC97CFG_TXSLOT_MASK
mdefine_line|#define PSC_AC97CFG_TXSLOT_MASK&t;(0x3ff &lt;&lt; 11)
DECL|macro|PSC_AC97CFG_RXSLOT_MASK
mdefine_line|#define PSC_AC97CFG_RXSLOT_MASK&t;(0x3ff &lt;&lt; 1)
DECL|macro|PSC_AC97CFG_GE_ENABLE
mdefine_line|#define PSC_AC97CFG_GE_ENABLE&t;(1)
multiline_comment|/* Enable slots 3-12.&n;*/
DECL|macro|PSC_AC97CFG_TXSLOT_ENA
mdefine_line|#define PSC_AC97CFG_TXSLOT_ENA(x)&t;(1 &lt;&lt; (((x) - 3) + 11))
DECL|macro|PSC_AC97CFG_RXSLOT_ENA
mdefine_line|#define PSC_AC97CFG_RXSLOT_ENA(x)&t;(1 &lt;&lt; (((x) - 3) + 1))
multiline_comment|/* The word length equation is ((x) * 2) + 2, so choose &squot;x&squot; appropriately.&n; * The only sensible numbers are 7, 9, or possibly 11.  Nah, just do the&n; * arithmetic in the macro.&n; */
DECL|macro|PSC_AC97CFG_SET_LEN
mdefine_line|#define PSC_AC97CFG_SET_LEN(x)&t;(((((x)-2)/2) &amp; 0xf) &lt;&lt; 21)
DECL|macro|PSC_AC97CFG_GET_LEN
mdefine_line|#define PSC_AC97CFG_GET_LEN(x)&t;(((((x) &gt;&gt; 21) &amp; 0xf) * 2) + 2)
multiline_comment|/* AC97 Mask Register.&n;*/
DECL|macro|PSC_AC97MSK_GR
mdefine_line|#define PSC_AC97MSK_GR&t;&t;(1 &lt;&lt; 25)
DECL|macro|PSC_AC97MSK_CD
mdefine_line|#define PSC_AC97MSK_CD&t;&t;(1 &lt;&lt; 24)
DECL|macro|PSC_AC97MSK_RR
mdefine_line|#define PSC_AC97MSK_RR&t;&t;(1 &lt;&lt; 13)
DECL|macro|PSC_AC97MSK_RO
mdefine_line|#define PSC_AC97MSK_RO&t;&t;(1 &lt;&lt; 12)
DECL|macro|PSC_AC97MSK_RU
mdefine_line|#define PSC_AC97MSK_RU&t;&t;(1 &lt;&lt; 11)
DECL|macro|PSC_AC97MSK_TR
mdefine_line|#define PSC_AC97MSK_TR&t;&t;(1 &lt;&lt; 10)
DECL|macro|PSC_AC97MSK_TO
mdefine_line|#define PSC_AC97MSK_TO&t;&t;(1 &lt;&lt; 9)
DECL|macro|PSC_AC97MSK_TU
mdefine_line|#define PSC_AC97MSK_TU&t;&t;(1 &lt;&lt; 8)
DECL|macro|PSC_AC97MSK_RD
mdefine_line|#define PSC_AC97MSK_RD&t;&t;(1 &lt;&lt; 5)
DECL|macro|PSC_AC97MSK_TD
mdefine_line|#define PSC_AC97MSK_TD&t;&t;(1 &lt;&lt; 4)
DECL|macro|PSC_AC97MSK_ALLMASK
mdefine_line|#define PSC_AC97MSK_ALLMASK&t;(PSC_AC97MSK_GR | PSC_AC97MSK_CD | &bslash;&n;&t;&t;&t;&t; PSC_AC97MSK_RR | PSC_AC97MSK_RO | &bslash;&n;&t;&t;&t;&t; PSC_AC97MSK_RU | PSC_AC97MSK_TR | &bslash;&n;&t;&t;&t;&t; PSC_AC97MSK_TO | PSC_AC97MSK_TU | &bslash;&n;&t;&t;&t;&t; PSC_AC97MSK_RD | PSC_AC97MSK_TD)
multiline_comment|/* AC97 Protocol Control Register.&n;*/
DECL|macro|PSC_AC97PCR_RC
mdefine_line|#define PSC_AC97PCR_RC&t;&t;(1 &lt;&lt; 6)
DECL|macro|PSC_AC97PCR_RP
mdefine_line|#define PSC_AC97PCR_RP&t;&t;(1 &lt;&lt; 5)
DECL|macro|PSC_AC97PCR_RS
mdefine_line|#define PSC_AC97PCR_RS&t;&t;(1 &lt;&lt; 4)
DECL|macro|PSC_AC97PCR_TC
mdefine_line|#define PSC_AC97PCR_TC&t;&t;(1 &lt;&lt; 2)
DECL|macro|PSC_AC97PCR_TP
mdefine_line|#define PSC_AC97PCR_TP&t;&t;(1 &lt;&lt; 1)
DECL|macro|PSC_AC97PCR_TS
mdefine_line|#define PSC_AC97PCR_TS&t;&t;(1 &lt;&lt; 0)
multiline_comment|/* AC97 Status register (read only).&n;*/
DECL|macro|PSC_AC97STAT_CB
mdefine_line|#define PSC_AC97STAT_CB&t;&t;(1 &lt;&lt; 26)
DECL|macro|PSC_AC97STAT_CP
mdefine_line|#define PSC_AC97STAT_CP&t;&t;(1 &lt;&lt; 25)
DECL|macro|PSC_AC97STAT_CR
mdefine_line|#define PSC_AC97STAT_CR&t;&t;(1 &lt;&lt; 24)
DECL|macro|PSC_AC97STAT_RF
mdefine_line|#define PSC_AC97STAT_RF&t;&t;(1 &lt;&lt; 13)
DECL|macro|PSC_AC97STAT_RE
mdefine_line|#define PSC_AC97STAT_RE&t;&t;(1 &lt;&lt; 12)
DECL|macro|PSC_AC97STAT_RR
mdefine_line|#define PSC_AC97STAT_RR&t;&t;(1 &lt;&lt; 11)
DECL|macro|PSC_AC97STAT_TF
mdefine_line|#define PSC_AC97STAT_TF&t;&t;(1 &lt;&lt; 10)
DECL|macro|PSC_AC97STAT_TE
mdefine_line|#define PSC_AC97STAT_TE&t;&t;(1 &lt;&lt; 9)
DECL|macro|PSC_AC97STAT_TR
mdefine_line|#define PSC_AC97STAT_TR&t;&t;(1 &lt;&lt; 8)
DECL|macro|PSC_AC97STAT_RB
mdefine_line|#define PSC_AC97STAT_RB&t;&t;(1 &lt;&lt; 5)
DECL|macro|PSC_AC97STAT_TB
mdefine_line|#define PSC_AC97STAT_TB&t;&t;(1 &lt;&lt; 4)
DECL|macro|PSC_AC97STAT_DI
mdefine_line|#define PSC_AC97STAT_DI&t;&t;(1 &lt;&lt; 2)
DECL|macro|PSC_AC97STAT_DR
mdefine_line|#define PSC_AC97STAT_DR&t;&t;(1 &lt;&lt; 1)
DECL|macro|PSC_AC97STAT_SR
mdefine_line|#define PSC_AC97STAT_SR&t;&t;(1 &lt;&lt; 0)
multiline_comment|/* AC97 Event Register.&n;*/
DECL|macro|PSC_AC97EVNT_GR
mdefine_line|#define PSC_AC97EVNT_GR&t;&t;(1 &lt;&lt; 25)
DECL|macro|PSC_AC97EVNT_CD
mdefine_line|#define PSC_AC97EVNT_CD&t;&t;(1 &lt;&lt; 24)
DECL|macro|PSC_AC97EVNT_RR
mdefine_line|#define PSC_AC97EVNT_RR&t;&t;(1 &lt;&lt; 13)
DECL|macro|PSC_AC97EVNT_RO
mdefine_line|#define PSC_AC97EVNT_RO&t;&t;(1 &lt;&lt; 12)
DECL|macro|PSC_AC97EVNT_RU
mdefine_line|#define PSC_AC97EVNT_RU&t;&t;(1 &lt;&lt; 11)
DECL|macro|PSC_AC97EVNT_TR
mdefine_line|#define PSC_AC97EVNT_TR&t;&t;(1 &lt;&lt; 10)
DECL|macro|PSC_AC97EVNT_TO
mdefine_line|#define PSC_AC97EVNT_TO&t;&t;(1 &lt;&lt; 9)
DECL|macro|PSC_AC97EVNT_TU
mdefine_line|#define PSC_AC97EVNT_TU&t;&t;(1 &lt;&lt; 8)
DECL|macro|PSC_AC97EVNT_RD
mdefine_line|#define PSC_AC97EVNT_RD&t;&t;(1 &lt;&lt; 5)
DECL|macro|PSC_AC97EVNT_TD
mdefine_line|#define PSC_AC97EVNT_TD&t;&t;(1 &lt;&lt; 4)
multiline_comment|/* CODEC Command Register.&n;*/
DECL|macro|PSC_AC97CDC_RD
mdefine_line|#define PSC_AC97CDC_RD&t;&t;(1 &lt;&lt; 25)
DECL|macro|PSC_AC97CDC_ID_MASK
mdefine_line|#define PSC_AC97CDC_ID_MASK&t;(3 &lt;&lt; 23)
DECL|macro|PSC_AC97CDC_INDX_MASK
mdefine_line|#define PSC_AC97CDC_INDX_MASK&t;(0x7f &lt;&lt; 16)
DECL|macro|PSC_AC97CDC_ID
mdefine_line|#define PSC_AC97CDC_ID(x)&t;(((x) &amp; 0x3) &lt;&lt; 23)
DECL|macro|PSC_AC97CDC_INDX
mdefine_line|#define PSC_AC97CDC_INDX(x)&t;(((x) &amp; 0x7f) &lt;&lt; 16)
multiline_comment|/* AC97 Reset Control Register.&n;*/
DECL|macro|PSC_AC97RST_RST
mdefine_line|#define PSC_AC97RST_RST&t;&t;(1 &lt;&lt; 1)
DECL|macro|PSC_AC97RST_SNC
mdefine_line|#define PSC_AC97RST_SNC&t;&t;(1 &lt;&lt; 0)
multiline_comment|/* PSC in I2S Mode.&n;*/
DECL|struct|psc_i2s
r_typedef
r_struct
id|psc_i2s
(brace
DECL|member|psc_sel
id|u32
id|psc_sel
suffix:semicolon
DECL|member|psc_ctrl
id|u32
id|psc_ctrl
suffix:semicolon
DECL|member|psc_i2scfg
id|u32
id|psc_i2scfg
suffix:semicolon
DECL|member|psc_i2smsk
id|u32
id|psc_i2smsk
suffix:semicolon
DECL|member|psc_i2spcr
id|u32
id|psc_i2spcr
suffix:semicolon
DECL|member|psc_i2sstat
id|u32
id|psc_i2sstat
suffix:semicolon
DECL|member|psc_i2sevent
id|u32
id|psc_i2sevent
suffix:semicolon
DECL|member|psc_i2stxrx
id|u32
id|psc_i2stxrx
suffix:semicolon
DECL|member|psc_i2sudf
id|u32
id|psc_i2sudf
suffix:semicolon
DECL|typedef|psc_i2s_t
)brace
id|psc_i2s_t
suffix:semicolon
multiline_comment|/* I2S Config Register.&n;*/
DECL|macro|PSC_I2SCFG_RT_MASK
mdefine_line|#define PSC_I2SCFG_RT_MASK&t;(3 &lt;&lt; 30)
DECL|macro|PSC_I2SCFG_RT_FIFO1
mdefine_line|#define PSC_I2SCFG_RT_FIFO1&t;(0 &lt;&lt; 30)
DECL|macro|PSC_I2SCFG_RT_FIFO2
mdefine_line|#define PSC_I2SCFG_RT_FIFO2&t;(1 &lt;&lt; 30)
DECL|macro|PSC_I2SCFG_RT_FIFO4
mdefine_line|#define PSC_I2SCFG_RT_FIFO4&t;(2 &lt;&lt; 30)
DECL|macro|PSC_I2SCFG_RT_FIFO8
mdefine_line|#define PSC_I2SCFG_RT_FIFO8&t;(3 &lt;&lt; 30)
DECL|macro|PSC_I2SCFG_TT_MASK
mdefine_line|#define PSC_I2SCFG_TT_MASK&t;(3 &lt;&lt; 28)
DECL|macro|PSC_I2SCFG_TT_FIFO1
mdefine_line|#define PSC_I2SCFG_TT_FIFO1&t;(0 &lt;&lt; 28)
DECL|macro|PSC_I2SCFG_TT_FIFO2
mdefine_line|#define PSC_I2SCFG_TT_FIFO2&t;(1 &lt;&lt; 28)
DECL|macro|PSC_I2SCFG_TT_FIFO4
mdefine_line|#define PSC_I2SCFG_TT_FIFO4&t;(2 &lt;&lt; 28)
DECL|macro|PSC_I2SCFG_TT_FIFO8
mdefine_line|#define PSC_I2SCFG_TT_FIFO8&t;(3 &lt;&lt; 28)
DECL|macro|PSC_I2SCFG_DD_DISABLE
mdefine_line|#define PSC_I2SCFG_DD_DISABLE&t;(1 &lt;&lt; 27)
DECL|macro|PSC_I2SCFG_DE_ENABLE
mdefine_line|#define PSC_I2SCFG_DE_ENABLE&t;(1 &lt;&lt; 26)
DECL|macro|PSC_I2SCFG_SET_WS
mdefine_line|#define PSC_I2SCFG_SET_WS(x)&t;(((((x) / 2) - 1) &amp; 0x7f) &lt;&lt; 16)
DECL|macro|PSC_I2SCFG_WI
mdefine_line|#define PSC_I2SCFG_WI&t;&t;(1 &lt;&lt; 15)
DECL|macro|PSC_I2SCFG_DIV_MASK
mdefine_line|#define PSC_I2SCFG_DIV_MASK&t;(3 &lt;&lt; 13)
DECL|macro|PSC_I2SCFG_DIV2
mdefine_line|#define PSC_I2SCFG_DIV2&t;&t;(0 &lt;&lt; 13)
DECL|macro|PSC_I2SCFG_DIV4
mdefine_line|#define PSC_I2SCFG_DIV4&t;&t;(1 &lt;&lt; 13)
DECL|macro|PSC_I2SCFG_DIV8
mdefine_line|#define PSC_I2SCFG_DIV8&t;&t;(2 &lt;&lt; 13)
DECL|macro|PSC_I2SCFG_DIV16
mdefine_line|#define PSC_I2SCFG_DIV16&t;(3 &lt;&lt; 13)
DECL|macro|PSC_I2SCFG_BI
mdefine_line|#define PSC_I2SCFG_BI&t;&t;(1 &lt;&lt; 12)
DECL|macro|PSC_I2SCFG_BUF
mdefine_line|#define PSC_I2SCFG_BUF&t;&t;(1 &lt;&lt; 11)
DECL|macro|PSC_I2SCFG_MLJ
mdefine_line|#define PSC_I2SCFG_MLJ&t;&t;(1 &lt;&lt; 10)
DECL|macro|PSC_I2SCFG_XM
mdefine_line|#define PSC_I2SCFG_XM&t;&t;(1 &lt;&lt; 9)
multiline_comment|/* The word length equation is simply LEN+1.&n; */
DECL|macro|PSC_I2SCFG_SET_LEN
mdefine_line|#define PSC_I2SCFG_SET_LEN(x)&t;((((x) - 1) &amp; 0x1f) &lt;&lt; 4)
DECL|macro|PSC_I2SCFG_GET_LEN
mdefine_line|#define PSC_I2SCFG_GET_LEN(x)&t;((((x) &gt;&gt; 4) &amp; 0x1f) + 1)
DECL|macro|PSC_I2SCFG_LB
mdefine_line|#define PSC_I2SCFG_LB&t;&t;(1 &lt;&lt; 2)
DECL|macro|PSC_I2SCFG_MLF
mdefine_line|#define PSC_I2SCFG_MLF&t;&t;(1 &lt;&lt; 1)
DECL|macro|PSC_I2SCFG_MS
mdefine_line|#define PSC_I2SCFG_MS&t;&t;(1 &lt;&lt; 0)
multiline_comment|/* I2S Mask Register.&n;*/
DECL|macro|PSC_I2SMSK_RR
mdefine_line|#define PSC_I2SMSK_RR&t;&t;(1 &lt;&lt; 13)
DECL|macro|PSC_I2SMSK_RO
mdefine_line|#define PSC_I2SMSK_RO&t;&t;(1 &lt;&lt; 12)
DECL|macro|PSC_I2SMSK_RU
mdefine_line|#define PSC_I2SMSK_RU&t;&t;(1 &lt;&lt; 11)
DECL|macro|PSC_I2SMSK_TR
mdefine_line|#define PSC_I2SMSK_TR&t;&t;(1 &lt;&lt; 10)
DECL|macro|PSC_I2SMSK_TO
mdefine_line|#define PSC_I2SMSK_TO&t;&t;(1 &lt;&lt; 9)
DECL|macro|PSC_I2SMSK_TU
mdefine_line|#define PSC_I2SMSK_TU&t;&t;(1 &lt;&lt; 8)
DECL|macro|PSC_I2SMSK_RD
mdefine_line|#define PSC_I2SMSK_RD&t;&t;(1 &lt;&lt; 5)
DECL|macro|PSC_I2SMSK_TD
mdefine_line|#define PSC_I2SMSK_TD&t;&t;(1 &lt;&lt; 4)
DECL|macro|PSC_I2SMSK_ALLMASK
mdefine_line|#define PSC_I2SMSK_ALLMASK&t;(PSC_I2SMSK_RR | PSC_I2SMSK_RO | &bslash;&n;&t;&t;&t;&t; PSC_I2SMSK_RU | PSC_I2SMSK_TR | &bslash;&n;&t;&t;&t;&t; PSC_I2SMSK_TO | PSC_I2SMSK_TU | &bslash;&n;&t;&t;&t;&t; PSC_I2SMSK_RD | PSC_I2SMSK_TD)
multiline_comment|/* I2S Protocol Control Register.&n;*/
DECL|macro|PSC_I2SPCR_RC
mdefine_line|#define PSC_I2SPCR_RC&t;&t;(1 &lt;&lt; 6)
DECL|macro|PSC_I2SPCR_RP
mdefine_line|#define PSC_I2SPCR_RP&t;&t;(1 &lt;&lt; 5)
DECL|macro|PSC_I2SPCR_RS
mdefine_line|#define PSC_I2SPCR_RS&t;&t;(1 &lt;&lt; 4)
DECL|macro|PSC_I2SPCR_TC
mdefine_line|#define PSC_I2SPCR_TC&t;&t;(1 &lt;&lt; 2)
DECL|macro|PSC_I2SPCR_TP
mdefine_line|#define PSC_I2SPCR_TP&t;&t;(1 &lt;&lt; 1)
DECL|macro|PSC_I2SPCR_TS
mdefine_line|#define PSC_I2SPCR_TS&t;&t;(1 &lt;&lt; 0)
multiline_comment|/* I2S Status register (read only).&n;*/
DECL|macro|PSC_I2SSTAT_RF
mdefine_line|#define PSC_I2SSTAT_RF&t;&t;(1 &lt;&lt; 13)
DECL|macro|PSC_I2SSTAT_RE
mdefine_line|#define PSC_I2SSTAT_RE&t;&t;(1 &lt;&lt; 12)
DECL|macro|PSC_I2SSTAT_RR
mdefine_line|#define PSC_I2SSTAT_RR&t;&t;(1 &lt;&lt; 11)
DECL|macro|PSC_I2SSTAT_TF
mdefine_line|#define PSC_I2SSTAT_TF&t;&t;(1 &lt;&lt; 10)
DECL|macro|PSC_I2SSTAT_TE
mdefine_line|#define PSC_I2SSTAT_TE&t;&t;(1 &lt;&lt; 9)
DECL|macro|PSC_I2SSTAT_TR
mdefine_line|#define PSC_I2SSTAT_TR&t;&t;(1 &lt;&lt; 8)
DECL|macro|PSC_I2SSTAT_RB
mdefine_line|#define PSC_I2SSTAT_RB&t;&t;(1 &lt;&lt; 5)
DECL|macro|PSC_I2SSTAT_TB
mdefine_line|#define PSC_I2SSTAT_TB&t;&t;(1 &lt;&lt; 4)
DECL|macro|PSC_I2SSTAT_DI
mdefine_line|#define PSC_I2SSTAT_DI&t;&t;(1 &lt;&lt; 2)
DECL|macro|PSC_I2SSTAT_DR
mdefine_line|#define PSC_I2SSTAT_DR&t;&t;(1 &lt;&lt; 1)
DECL|macro|PSC_I2SSTAT_SR
mdefine_line|#define PSC_I2SSTAT_SR&t;&t;(1 &lt;&lt; 0)
multiline_comment|/* I2S Event Register.&n;*/
DECL|macro|PSC_I2SEVNT_RR
mdefine_line|#define PSC_I2SEVNT_RR&t;&t;(1 &lt;&lt; 13)
DECL|macro|PSC_I2SEVNT_RO
mdefine_line|#define PSC_I2SEVNT_RO&t;&t;(1 &lt;&lt; 12)
DECL|macro|PSC_I2SEVNT_RU
mdefine_line|#define PSC_I2SEVNT_RU&t;&t;(1 &lt;&lt; 11)
DECL|macro|PSC_I2SEVNT_TR
mdefine_line|#define PSC_I2SEVNT_TR&t;&t;(1 &lt;&lt; 10)
DECL|macro|PSC_I2SEVNT_TO
mdefine_line|#define PSC_I2SEVNT_TO&t;&t;(1 &lt;&lt; 9)
DECL|macro|PSC_I2SEVNT_TU
mdefine_line|#define PSC_I2SEVNT_TU&t;&t;(1 &lt;&lt; 8)
DECL|macro|PSC_I2SEVNT_RD
mdefine_line|#define PSC_I2SEVNT_RD&t;&t;(1 &lt;&lt; 5)
DECL|macro|PSC_I2SEVNT_TD
mdefine_line|#define PSC_I2SEVNT_TD&t;&t;(1 &lt;&lt; 4)
multiline_comment|/* PSC in SPI Mode.&n;*/
DECL|struct|psc_spi
r_typedef
r_struct
id|psc_spi
(brace
DECL|member|psc_sel
id|u32
id|psc_sel
suffix:semicolon
DECL|member|psc_ctrl
id|u32
id|psc_ctrl
suffix:semicolon
DECL|member|psc_spicfg
id|u32
id|psc_spicfg
suffix:semicolon
DECL|member|psc_spimsk
id|u32
id|psc_spimsk
suffix:semicolon
DECL|member|psc_spipcr
id|u32
id|psc_spipcr
suffix:semicolon
DECL|member|psc_spistat
id|u32
id|psc_spistat
suffix:semicolon
DECL|member|psc_spievent
id|u32
id|psc_spievent
suffix:semicolon
DECL|member|psc_spitxrx
id|u32
id|psc_spitxrx
suffix:semicolon
DECL|typedef|psc_spi_t
)brace
id|psc_spi_t
suffix:semicolon
multiline_comment|/* SPI Config Register.&n;*/
DECL|macro|PSC_SPICFG_RT_MASK
mdefine_line|#define PSC_SPICFG_RT_MASK&t;(3 &lt;&lt; 30)
DECL|macro|PSC_SPICFG_RT_FIFO1
mdefine_line|#define PSC_SPICFG_RT_FIFO1&t;(0 &lt;&lt; 30)
DECL|macro|PSC_SPICFG_RT_FIFO2
mdefine_line|#define PSC_SPICFG_RT_FIFO2&t;(1 &lt;&lt; 30)
DECL|macro|PSC_SPICFG_RT_FIFO4
mdefine_line|#define PSC_SPICFG_RT_FIFO4&t;(2 &lt;&lt; 30)
DECL|macro|PSC_SPICFG_RT_FIFO8
mdefine_line|#define PSC_SPICFG_RT_FIFO8&t;(3 &lt;&lt; 30)
DECL|macro|PSC_SPICFG_TT_MASK
mdefine_line|#define PSC_SPICFG_TT_MASK&t;(3 &lt;&lt; 28)
DECL|macro|PSC_SPICFG_TT_FIFO1
mdefine_line|#define PSC_SPICFG_TT_FIFO1&t;(0 &lt;&lt; 28)
DECL|macro|PSC_SPICFG_TT_FIFO2
mdefine_line|#define PSC_SPICFG_TT_FIFO2&t;(1 &lt;&lt; 28)
DECL|macro|PSC_SPICFG_TT_FIFO4
mdefine_line|#define PSC_SPICFG_TT_FIFO4&t;(2 &lt;&lt; 28)
DECL|macro|PSC_SPICFG_TT_FIFO8
mdefine_line|#define PSC_SPICFG_TT_FIFO8&t;(3 &lt;&lt; 28)
DECL|macro|PSC_SPICFG_DD_DISABLE
mdefine_line|#define PSC_SPICFG_DD_DISABLE&t;(1 &lt;&lt; 27)
DECL|macro|PSC_SPICFG_DE_ENABLE
mdefine_line|#define PSC_SPICFG_DE_ENABLE&t;(1 &lt;&lt; 26)
DECL|macro|PSC_SPICFG_CLR_BAUD
mdefine_line|#define PSC_SPICFG_CLR_BAUD(x)&t;((x) &amp; ~((0x3f) &lt;&lt; 15))
DECL|macro|PSC_SPICFG_SET_BAUD
mdefine_line|#define PSC_SPICFG_SET_BAUD(x)&t;(((x) &amp; 0x3f) &lt;&lt; 15)
DECL|macro|PSC_SPICFG_SET_DIV
mdefine_line|#define PSC_SPICFG_SET_DIV(x)&t;(((x) &amp; 0x03) &lt;&lt; 13)
DECL|macro|PSC_SPICFG_DIV2
mdefine_line|#define PSC_SPICFG_DIV2&t;&t;0
DECL|macro|PSC_SPICFG_DIV4
mdefine_line|#define PSC_SPICFG_DIV4&t;&t;1
DECL|macro|PSC_SPICFG_DIV8
mdefine_line|#define PSC_SPICFG_DIV8&t;&t;2
DECL|macro|PSC_SPICFG_DIV16
mdefine_line|#define PSC_SPICFG_DIV16&t;3
DECL|macro|PSC_SPICFG_BI
mdefine_line|#define PSC_SPICFG_BI&t;&t;(1 &lt;&lt; 12)
DECL|macro|PSC_SPICFG_PSE
mdefine_line|#define PSC_SPICFG_PSE&t;&t;(1 &lt;&lt; 11)
DECL|macro|PSC_SPICFG_CGE
mdefine_line|#define PSC_SPICFG_CGE&t;&t;(1 &lt;&lt; 10)
DECL|macro|PSC_SPICFG_CDE
mdefine_line|#define PSC_SPICFG_CDE&t;&t;(1 &lt;&lt; 9)
DECL|macro|PSC_SPICFG_CLR_LEN
mdefine_line|#define PSC_SPICFG_CLR_LEN(x)&t;((x) &amp; ~((0x1f) &lt;&lt; 4))
DECL|macro|PSC_SPICFG_SET_LEN
mdefine_line|#define PSC_SPICFG_SET_LEN(x)&t;(((x-1) &amp; 0x1f) &lt;&lt; 4)
DECL|macro|PSC_SPICFG_LB
mdefine_line|#define PSC_SPICFG_LB&t;&t;(1 &lt;&lt; 3)
DECL|macro|PSC_SPICFG_MLF
mdefine_line|#define PSC_SPICFG_MLF&t;&t;(1 &lt;&lt; 1)
DECL|macro|PSC_SPICFG_MO
mdefine_line|#define PSC_SPICFG_MO&t;&t;(1 &lt;&lt; 0)
multiline_comment|/* SPI Mask Register.&n;*/
DECL|macro|PSC_SPIMSK_MM
mdefine_line|#define PSC_SPIMSK_MM&t;&t;(1 &lt;&lt; 16)
DECL|macro|PSC_SPIMSK_RR
mdefine_line|#define PSC_SPIMSK_RR&t;&t;(1 &lt;&lt; 13)
DECL|macro|PSC_SPIMSK_RO
mdefine_line|#define PSC_SPIMSK_RO&t;&t;(1 &lt;&lt; 12)
DECL|macro|PSC_SPIMSK_RU
mdefine_line|#define PSC_SPIMSK_RU&t;&t;(1 &lt;&lt; 11)
DECL|macro|PSC_SPIMSK_TR
mdefine_line|#define PSC_SPIMSK_TR&t;&t;(1 &lt;&lt; 10)
DECL|macro|PSC_SPIMSK_TO
mdefine_line|#define PSC_SPIMSK_TO&t;&t;(1 &lt;&lt; 9)
DECL|macro|PSC_SPIMSK_TU
mdefine_line|#define PSC_SPIMSK_TU&t;&t;(1 &lt;&lt; 8)
DECL|macro|PSC_SPIMSK_SD
mdefine_line|#define PSC_SPIMSK_SD&t;&t;(1 &lt;&lt; 5)
DECL|macro|PSC_SPIMSK_MD
mdefine_line|#define PSC_SPIMSK_MD&t;&t;(1 &lt;&lt; 4)
DECL|macro|PSC_SPIMSK_ALLMASK
mdefine_line|#define PSC_SPIMSK_ALLMASK&t;(PSC_SPIMSK_MM | PSC_SPIMSK_RR | &bslash;&n;&t;&t;&t;&t; PSC_SPIMSK_RO | PSC_SPIMSK_TO | &bslash;&n;&t;&t;&t;&t; PSC_SPIMSK_TU | PSC_SPIMSK_SD | &bslash;&n;&t;&t;&t;&t; PSC_SPIMSK_MD)
multiline_comment|/* SPI Protocol Control Register.&n;*/
DECL|macro|PSC_SPIPCR_RC
mdefine_line|#define PSC_SPIPCR_RC&t;&t;(1 &lt;&lt; 6)
DECL|macro|PSC_SPIPCR_SP
mdefine_line|#define PSC_SPIPCR_SP&t;&t;(1 &lt;&lt; 5)
DECL|macro|PSC_SPIPCR_SS
mdefine_line|#define PSC_SPIPCR_SS&t;&t;(1 &lt;&lt; 4)
DECL|macro|PSC_SPIPCR_TC
mdefine_line|#define PSC_SPIPCR_TC&t;&t;(1 &lt;&lt; 2)
DECL|macro|PSC_SPIPCR_MS
mdefine_line|#define PSC_SPIPCR_MS&t;&t;(1 &lt;&lt; 0)
multiline_comment|/* SPI Status register (read only).&n;*/
DECL|macro|PSC_SPISTAT_RF
mdefine_line|#define PSC_SPISTAT_RF&t;&t;(1 &lt;&lt; 13)
DECL|macro|PSC_SPISTAT_RE
mdefine_line|#define PSC_SPISTAT_RE&t;&t;(1 &lt;&lt; 12)
DECL|macro|PSC_SPISTAT_RR
mdefine_line|#define PSC_SPISTAT_RR&t;&t;(1 &lt;&lt; 11)
DECL|macro|PSC_SPISTAT_TF
mdefine_line|#define PSC_SPISTAT_TF&t;&t;(1 &lt;&lt; 10)
DECL|macro|PSC_SPISTAT_TE
mdefine_line|#define PSC_SPISTAT_TE&t;&t;(1 &lt;&lt; 9)
DECL|macro|PSC_SPISTAT_TR
mdefine_line|#define PSC_SPISTAT_TR&t;&t;(1 &lt;&lt; 8)
DECL|macro|PSC_SPISTAT_SB
mdefine_line|#define PSC_SPISTAT_SB&t;&t;(1 &lt;&lt; 5)
DECL|macro|PSC_SPISTAT_MB
mdefine_line|#define PSC_SPISTAT_MB&t;&t;(1 &lt;&lt; 4)
DECL|macro|PSC_SPISTAT_DI
mdefine_line|#define PSC_SPISTAT_DI&t;&t;(1 &lt;&lt; 2)
DECL|macro|PSC_SPISTAT_DR
mdefine_line|#define PSC_SPISTAT_DR&t;&t;(1 &lt;&lt; 1)
DECL|macro|PSC_SPISTAT_SR
mdefine_line|#define PSC_SPISTAT_SR&t;&t;(1 &lt;&lt; 0)
multiline_comment|/* SPI Event Register.&n;*/
DECL|macro|PSC_SPIEVNT_MM
mdefine_line|#define PSC_SPIEVNT_MM&t;&t;(1 &lt;&lt; 16)
DECL|macro|PSC_SPIEVNT_RR
mdefine_line|#define PSC_SPIEVNT_RR&t;&t;(1 &lt;&lt; 13)
DECL|macro|PSC_SPIEVNT_RO
mdefine_line|#define PSC_SPIEVNT_RO&t;&t;(1 &lt;&lt; 12)
DECL|macro|PSC_SPIEVNT_RU
mdefine_line|#define PSC_SPIEVNT_RU&t;&t;(1 &lt;&lt; 11)
DECL|macro|PSC_SPIEVNT_TR
mdefine_line|#define PSC_SPIEVNT_TR&t;&t;(1 &lt;&lt; 10)
DECL|macro|PSC_SPIEVNT_TO
mdefine_line|#define PSC_SPIEVNT_TO&t;&t;(1 &lt;&lt; 9)
DECL|macro|PSC_SPIEVNT_TU
mdefine_line|#define PSC_SPIEVNT_TU&t;&t;(1 &lt;&lt; 8)
DECL|macro|PSC_SPIEVNT_SD
mdefine_line|#define PSC_SPIEVNT_SD&t;&t;(1 &lt;&lt; 5)
DECL|macro|PSC_SPIEVNT_MD
mdefine_line|#define PSC_SPIEVNT_MD&t;&t;(1 &lt;&lt; 4)
multiline_comment|/* Transmit register control.&n;*/
DECL|macro|PSC_SPITXRX_LC
mdefine_line|#define PSC_SPITXRX_LC&t;&t;(1 &lt;&lt; 29)
DECL|macro|PSC_SPITXRX_SR
mdefine_line|#define PSC_SPITXRX_SR&t;&t;(1 &lt;&lt; 28)
multiline_comment|/* PSC in SMBus (I2C) Mode.&n;*/
DECL|struct|psc_smb
r_typedef
r_struct
id|psc_smb
(brace
DECL|member|psc_sel
id|u32
id|psc_sel
suffix:semicolon
DECL|member|psc_ctrl
id|u32
id|psc_ctrl
suffix:semicolon
DECL|member|psc_smbcfg
id|u32
id|psc_smbcfg
suffix:semicolon
DECL|member|psc_smbmsk
id|u32
id|psc_smbmsk
suffix:semicolon
DECL|member|psc_smbpcr
id|u32
id|psc_smbpcr
suffix:semicolon
DECL|member|psc_smbstat
id|u32
id|psc_smbstat
suffix:semicolon
DECL|member|psc_smbevnt
id|u32
id|psc_smbevnt
suffix:semicolon
DECL|member|psc_smbtxrx
id|u32
id|psc_smbtxrx
suffix:semicolon
DECL|member|psc_smbtmr
id|u32
id|psc_smbtmr
suffix:semicolon
DECL|typedef|psc_smb_t
)brace
id|psc_smb_t
suffix:semicolon
multiline_comment|/* SMBus Config Register.&n;*/
DECL|macro|PSC_SMBCFG_RT_MASK
mdefine_line|#define PSC_SMBCFG_RT_MASK&t;(3 &lt;&lt; 30)
DECL|macro|PSC_SMBCFG_RT_FIFO1
mdefine_line|#define PSC_SMBCFG_RT_FIFO1&t;(0 &lt;&lt; 30)
DECL|macro|PSC_SMBCFG_RT_FIFO2
mdefine_line|#define PSC_SMBCFG_RT_FIFO2&t;(1 &lt;&lt; 30)
DECL|macro|PSC_SMBCFG_RT_FIFO4
mdefine_line|#define PSC_SMBCFG_RT_FIFO4&t;(2 &lt;&lt; 30)
DECL|macro|PSC_SMBCFG_RT_FIFO8
mdefine_line|#define PSC_SMBCFG_RT_FIFO8&t;(3 &lt;&lt; 30)
DECL|macro|PSC_SMBCFG_TT_MASK
mdefine_line|#define PSC_SMBCFG_TT_MASK&t;(3 &lt;&lt; 28)
DECL|macro|PSC_SMBCFG_TT_FIFO1
mdefine_line|#define PSC_SMBCFG_TT_FIFO1&t;(0 &lt;&lt; 28)
DECL|macro|PSC_SMBCFG_TT_FIFO2
mdefine_line|#define PSC_SMBCFG_TT_FIFO2&t;(1 &lt;&lt; 28)
DECL|macro|PSC_SMBCFG_TT_FIFO4
mdefine_line|#define PSC_SMBCFG_TT_FIFO4&t;(2 &lt;&lt; 28)
DECL|macro|PSC_SMBCFG_TT_FIFO8
mdefine_line|#define PSC_SMBCFG_TT_FIFO8&t;(3 &lt;&lt; 28)
DECL|macro|PSC_SMBCFG_DD_DISABLE
mdefine_line|#define PSC_SMBCFG_DD_DISABLE&t;(1 &lt;&lt; 27)
DECL|macro|PSC_SMBCFG_DE_ENABLE
mdefine_line|#define PSC_SMBCFG_DE_ENABLE&t;(1 &lt;&lt; 26)
DECL|macro|PSC_SMBCFG_SET_DIV
mdefine_line|#define PSC_SMBCFG_SET_DIV(x)&t;(((x) &amp; 0x03) &lt;&lt; 13)
DECL|macro|PSC_SMBCFG_DIV2
mdefine_line|#define PSC_SMBCFG_DIV2&t;&t;0
DECL|macro|PSC_SMBCFG_DIV4
mdefine_line|#define PSC_SMBCFG_DIV4&t;&t;1
DECL|macro|PSC_SMBCFG_DIV8
mdefine_line|#define PSC_SMBCFG_DIV8&t;&t;2
DECL|macro|PSC_SMBCFG_DIV16
mdefine_line|#define PSC_SMBCFG_DIV16&t;3
DECL|macro|PSC_SMBCFG_GCE
mdefine_line|#define PSC_SMBCFG_GCE&t;&t;(1 &lt;&lt; 9)
DECL|macro|PSC_SMBCFG_SFM
mdefine_line|#define PSC_SMBCFG_SFM&t;&t;(1 &lt;&lt; 8)
DECL|macro|PSC_SMBCFG_SET_SLV
mdefine_line|#define PSC_SMBCFG_SET_SLV(x)&t;(((x) &amp; 0x7f) &lt;&lt; 1)
multiline_comment|/* SMBus Mask Register.&n;*/
DECL|macro|PSC_SMBMSK_DN
mdefine_line|#define PSC_SMBMSK_DN&t;&t;(1 &lt;&lt; 30)
DECL|macro|PSC_SMBMSK_AN
mdefine_line|#define PSC_SMBMSK_AN&t;&t;(1 &lt;&lt; 29)
DECL|macro|PSC_SMBMSK_AL
mdefine_line|#define PSC_SMBMSK_AL&t;&t;(1 &lt;&lt; 28)
DECL|macro|PSC_SMBMSK_RR
mdefine_line|#define PSC_SMBMSK_RR&t;&t;(1 &lt;&lt; 13)
DECL|macro|PSC_SMBMSK_RO
mdefine_line|#define PSC_SMBMSK_RO&t;&t;(1 &lt;&lt; 12)
DECL|macro|PSC_SMBMSK_RU
mdefine_line|#define PSC_SMBMSK_RU&t;&t;(1 &lt;&lt; 11)
DECL|macro|PSC_SMBMSK_TR
mdefine_line|#define PSC_SMBMSK_TR&t;&t;(1 &lt;&lt; 10)
DECL|macro|PSC_SMBMSK_TO
mdefine_line|#define PSC_SMBMSK_TO&t;&t;(1 &lt;&lt; 9)
DECL|macro|PSC_SMBMSK_TU
mdefine_line|#define PSC_SMBMSK_TU&t;&t;(1 &lt;&lt; 8)
DECL|macro|PSC_SMBMSK_SD
mdefine_line|#define PSC_SMBMSK_SD&t;&t;(1 &lt;&lt; 5)
DECL|macro|PSC_SMBMSK_MD
mdefine_line|#define PSC_SMBMSK_MD&t;&t;(1 &lt;&lt; 4)
DECL|macro|PSC_SMBMSK_ALLMASK
mdefine_line|#define PSC_SMBMSK_ALLMASK&t;(PSC_SMBMSK_DN | PSC_SMBMSK_AN | &bslash;&n;&t;&t;&t;&t; PSC_SMBMSK_AL | PSC_SMBMSK_RR | &bslash;&n;&t;&t;&t;&t; PSC_SMBMSK_RO | PSC_SMBMSK_TO | &bslash;&n;&t;&t;&t;&t; PSC_SMBMSK_TU | PSC_SMBMSK_SD | &bslash;&n;&t;&t;&t;&t; PSC_SMBMSK_MD)
multiline_comment|/* SMBus Protocol Control Register.&n;*/
DECL|macro|PSC_SMBPCR_DC
mdefine_line|#define PSC_SMBPCR_DC&t;&t;(1 &lt;&lt; 2)
DECL|macro|PSC_SMBPCR_MS
mdefine_line|#define PSC_SMBPCR_MS&t;&t;(1 &lt;&lt; 0)
multiline_comment|/* SMBus Status register (read only).&n;*/
DECL|macro|PSC_SMBSTAT_BB
mdefine_line|#define PSC_SMBSTAT_BB&t;&t;(1 &lt;&lt; 28)
DECL|macro|PSC_SMBSTAT_RF
mdefine_line|#define PSC_SMBSTAT_RF&t;&t;(1 &lt;&lt; 13)
DECL|macro|PSC_SMBSTAT_RE
mdefine_line|#define PSC_SMBSTAT_RE&t;&t;(1 &lt;&lt; 12)
DECL|macro|PSC_SMBSTAT_RR
mdefine_line|#define PSC_SMBSTAT_RR&t;&t;(1 &lt;&lt; 11)
DECL|macro|PSC_SMBSTAT_TF
mdefine_line|#define PSC_SMBSTAT_TF&t;&t;(1 &lt;&lt; 10)
DECL|macro|PSC_SMBSTAT_TE
mdefine_line|#define PSC_SMBSTAT_TE&t;&t;(1 &lt;&lt; 9)
DECL|macro|PSC_SMBSTAT_TR
mdefine_line|#define PSC_SMBSTAT_TR&t;&t;(1 &lt;&lt; 8)
DECL|macro|PSC_SMBSTAT_SB
mdefine_line|#define PSC_SMBSTAT_SB&t;&t;(1 &lt;&lt; 5)
DECL|macro|PSC_SMBSTAT_MB
mdefine_line|#define PSC_SMBSTAT_MB&t;&t;(1 &lt;&lt; 4)
DECL|macro|PSC_SMBSTAT_DI
mdefine_line|#define PSC_SMBSTAT_DI&t;&t;(1 &lt;&lt; 2)
DECL|macro|PSC_SMBSTAT_DR
mdefine_line|#define PSC_SMBSTAT_DR&t;&t;(1 &lt;&lt; 1)
DECL|macro|PSC_SMBSTAT_SR
mdefine_line|#define PSC_SMBSTAT_SR&t;&t;(1 &lt;&lt; 0)
multiline_comment|/* SMBus Event Register.&n;*/
DECL|macro|PSC_SMBEVNT_DN
mdefine_line|#define PSC_SMBEVNT_DN&t;&t;(1 &lt;&lt; 30)
DECL|macro|PSC_SMBEVNT_AN
mdefine_line|#define PSC_SMBEVNT_AN&t;&t;(1 &lt;&lt; 29)
DECL|macro|PSC_SMBEVNT_AL
mdefine_line|#define PSC_SMBEVNT_AL&t;&t;(1 &lt;&lt; 28)
DECL|macro|PSC_SMBEVNT_RR
mdefine_line|#define PSC_SMBEVNT_RR&t;&t;(1 &lt;&lt; 13)
DECL|macro|PSC_SMBEVNT_RO
mdefine_line|#define PSC_SMBEVNT_RO&t;&t;(1 &lt;&lt; 12)
DECL|macro|PSC_SMBEVNT_RU
mdefine_line|#define PSC_SMBEVNT_RU&t;&t;(1 &lt;&lt; 11)
DECL|macro|PSC_SMBEVNT_TR
mdefine_line|#define PSC_SMBEVNT_TR&t;&t;(1 &lt;&lt; 10)
DECL|macro|PSC_SMBEVNT_TO
mdefine_line|#define PSC_SMBEVNT_TO&t;&t;(1 &lt;&lt; 9)
DECL|macro|PSC_SMBEVNT_TU
mdefine_line|#define PSC_SMBEVNT_TU&t;&t;(1 &lt;&lt; 8)
DECL|macro|PSC_SMBEVNT_SD
mdefine_line|#define PSC_SMBEVNT_SD&t;&t;(1 &lt;&lt; 5)
DECL|macro|PSC_SMBEVNT_MD
mdefine_line|#define PSC_SMBEVNT_MD&t;&t;(1 &lt;&lt; 4)
DECL|macro|PSC_SMBEVNT_ALLCLR
mdefine_line|#define PSC_SMBEVNT_ALLCLR&t;(PSC_SMBEVNT_DN | PSC_SMBEVNT_AN | &bslash;&n;&t;&t;&t;&t; PSC_SMBEVNT_AL | PSC_SMBEVNT_RR | &bslash;&n;&t;&t;&t;&t; PSC_SMBEVNT_RO | PSC_SMBEVNT_TO | &bslash;&n;&t;&t;&t;&t; PSC_SMBEVNT_TU | PSC_SMBEVNT_SD | &bslash;&n;&t;&t;&t;&t; PSC_SMBEVNT_MD)
multiline_comment|/* Transmit register control.&n;*/
DECL|macro|PSC_SMBTXRX_RSR
mdefine_line|#define PSC_SMBTXRX_RSR&t;&t;(1 &lt;&lt; 30)
DECL|macro|PSC_SMBTXRX_STP
mdefine_line|#define PSC_SMBTXRX_STP&t;&t;(1 &lt;&lt; 29)
DECL|macro|PSC_SMBTXRX_DATAMASK
mdefine_line|#define PSC_SMBTXRX_DATAMASK&t;(0xff)
multiline_comment|/* SMBus protocol timers register.&n;*/
DECL|macro|PSC_SMBTMR_SET_TH
mdefine_line|#define PSC_SMBTMR_SET_TH(x)&t;(((x) &amp; 0x3) &lt;&lt; 30)
DECL|macro|PSC_SMBTMR_SET_PS
mdefine_line|#define PSC_SMBTMR_SET_PS(x)&t;(((x) &amp; 0x1f) &lt;&lt; 25)
DECL|macro|PSC_SMBTMR_SET_PU
mdefine_line|#define PSC_SMBTMR_SET_PU(x)&t;(((x) &amp; 0x1f) &lt;&lt; 20)
DECL|macro|PSC_SMBTMR_SET_SH
mdefine_line|#define PSC_SMBTMR_SET_SH(x)&t;(((x) &amp; 0x1f) &lt;&lt; 15)
DECL|macro|PSC_SMBTMR_SET_SU
mdefine_line|#define PSC_SMBTMR_SET_SU(x)&t;(((x) &amp; 0x1f) &lt;&lt; 10)
DECL|macro|PSC_SMBTMR_SET_CL
mdefine_line|#define PSC_SMBTMR_SET_CL(x)&t;(((x) &amp; 0x1f) &lt;&lt; 5)
DECL|macro|PSC_SMBTMR_SET_CH
mdefine_line|#define PSC_SMBTMR_SET_CH(x)&t;(((x) &amp; 0x1f) &lt;&lt; 0)
macro_line|#endif /* _AU1000_PSC_H_ */
eof
