multiline_comment|/*&n; *&n; * BRIEF MODULE DESCRIPTION&n; *&t;Include file for Alchemy Semiconductor&squot;s Au1k CPU.&n; *&n; * Copyright 2004 Embedded Edge, LLC&n; *&t;dan@embeddededge.com&n; *&n; *  This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR IMPLIED&n; *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; */
multiline_comment|/* Specifics for the Au1xxx Programmable Serial Controllers, first&n; * seen in the AU1550 part.&n; */
macro_line|#ifndef _AU1000_PSC_H_
DECL|macro|_AU1000_PSC_H_
mdefine_line|#define _AU1000_PSC_H_
multiline_comment|/* The PSC base addresses.&n;*/
DECL|macro|PSC_BASE0
mdefine_line|#define PSC_BASE0&t;&t;0xb1a00000
DECL|macro|PSC_BASE1
mdefine_line|#define PSC_BASE1&t;&t;0xb1b00000
DECL|macro|PSC_BASE2
mdefine_line|#define PSC_BASE2&t;&t;0xb0a00000
DECL|macro|PSC_BASE3
mdefine_line|#define PSC_BASE3&t;&t;0xb0d00000
multiline_comment|/* These should be defined in a board specific file!&n;*/
macro_line|#ifdef CONFIG_MIPS_PB1550
DECL|macro|SPI_PSC_BASE
mdefine_line|#define SPI_PSC_BASE&t;&t;PSC_BASE0
DECL|macro|AC97_PSC_BASE
mdefine_line|#define AC97_PSC_BASE&t;&t;PSC_BASE1
DECL|macro|SMBUS_PSC_BASE
mdefine_line|#define SMBUS_PSC_BASE&t;&t;PSC_BASE2
macro_line|#endif
macro_line|#ifdef CONFIG_MIPS_DB1550
DECL|macro|SPI_PSC_BASE
mdefine_line|#define SPI_PSC_BASE&t;&t;PSC_BASE0
DECL|macro|AC97_PSC_BASE
mdefine_line|#define AC97_PSC_BASE&t;&t;PSC_BASE1
DECL|macro|SMBUS_PSC_BASE
mdefine_line|#define SMBUS_PSC_BASE&t;&t;PSC_BASE2
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
macro_line|#endif /* _AU1000_PSC_H_ */
eof
