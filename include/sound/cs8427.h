macro_line|#ifndef __SOUND_CS8427_H
DECL|macro|__SOUND_CS8427_H
mdefine_line|#define __SOUND_CS8427_H
multiline_comment|/*&n; *  Routines for Cirrus Logic CS8427&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;,&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &lt;sound/i2c.h&gt;
DECL|macro|CS8427_BASE_ADDR
mdefine_line|#define CS8427_BASE_ADDR&t;0x10&t;/* base I2C address */
DECL|macro|CS8427_REG_AUTOINC
mdefine_line|#define CS8427_REG_AUTOINC&t;0x80&t;/* flag - autoincrement */
DECL|macro|CS8427_REG_CONTROL1
mdefine_line|#define CS8427_REG_CONTROL1&t;0x01
DECL|macro|CS8427_REG_CONTROL2
mdefine_line|#define CS8427_REG_CONTROL2&t;0x02
DECL|macro|CS8427_REG_DATAFLOW
mdefine_line|#define CS8427_REG_DATAFLOW&t;0x03
DECL|macro|CS8427_REG_CLOCKSOURCE
mdefine_line|#define CS8427_REG_CLOCKSOURCE&t;0x04
DECL|macro|CS8427_REG_SERIALINPUT
mdefine_line|#define CS8427_REG_SERIALINPUT&t;0x05
DECL|macro|CS8427_REG_SERIALOUTPUT
mdefine_line|#define CS8427_REG_SERIALOUTPUT&t;0x06
DECL|macro|CS8427_REG_INT1STATUS
mdefine_line|#define CS8427_REG_INT1STATUS&t;0x07
DECL|macro|CS8427_REG_INT2STATUS
mdefine_line|#define CS8427_REG_INT2STATUS&t;0x08
DECL|macro|CS8427_REG_INT1MASK
mdefine_line|#define CS8427_REG_INT1MASK&t;0x09
DECL|macro|CS8427_REG_INT1MODEMSB
mdefine_line|#define CS8427_REG_INT1MODEMSB&t;0x0a
DECL|macro|CS8427_REG_INT1MODELSB
mdefine_line|#define CS8427_REG_INT1MODELSB&t;0x0b
DECL|macro|CS8427_REG_INT2MASK
mdefine_line|#define CS8427_REG_INT2MASK&t;0x0c
DECL|macro|CS8427_REG_INT2MODEMSB
mdefine_line|#define CS8427_REG_INT2MODEMSB&t;0x0d
DECL|macro|CS8427_REG_INT2MODELSB
mdefine_line|#define CS8427_REG_INT2MODELSB&t;0x0e
DECL|macro|CS8427_REG_RECVCSDATA
mdefine_line|#define CS8427_REG_RECVCSDATA&t;0x0f
DECL|macro|CS8427_REG_RECVERRORS
mdefine_line|#define CS8427_REG_RECVERRORS&t;0x10
DECL|macro|CS8427_REG_RECVERRMASK
mdefine_line|#define CS8427_REG_RECVERRMASK&t;0x11
DECL|macro|CS8427_REG_CSDATABUF
mdefine_line|#define CS8427_REG_CSDATABUF&t;0x12
DECL|macro|CS8427_REG_UDATABUF
mdefine_line|#define CS8427_REG_UDATABUF&t;0x13
DECL|macro|CS8427_REG_QSUBCODE
mdefine_line|#define CS8427_REG_QSUBCODE&t;0x14&t;/* 0x14-0x1d (10 bytes) */
DECL|macro|CS8427_REG_OMCKRMCKRATIO
mdefine_line|#define CS8427_REG_OMCKRMCKRATIO 0x1e
DECL|macro|CS8427_REG_CORU_DATABUF
mdefine_line|#define CS8427_REG_CORU_DATABUF&t;0x20
DECL|macro|CS8427_REG_ID_AND_VER
mdefine_line|#define CS8427_REG_ID_AND_VER&t;0x7f
multiline_comment|/* CS8427_REG_CONTROL1 bits */
DECL|macro|CS8427_SWCLK
mdefine_line|#define CS8427_SWCLK&t;&t;(1&lt;&lt;7)&t;/* 0 = RMCK default, 1 = OMCK output on RMCK pin */
DECL|macro|CS8427_VSET
mdefine_line|#define CS8427_VSET&t;&t;(1&lt;&lt;6)&t;/* 0 = valid PCM data, 1 = invalid PCM data */
DECL|macro|CS8427_MUTESAO
mdefine_line|#define CS8427_MUTESAO&t;&t;(1&lt;&lt;5)&t;/* mute control for the serial audio output port, 0 = disabled, 1 = enabled */
DECL|macro|CS8427_MUTEAES
mdefine_line|#define CS8427_MUTEAES&t;&t;(1&lt;&lt;4)&t;/* mute control for the AES transmitter output, 0 = disabled, 1 = enabled */
DECL|macro|CS8427_INTMASK
mdefine_line|#define CS8427_INTMASK&t;&t;(3&lt;&lt;1)&t;/* interrupt output pin setup mask */
DECL|macro|CS8427_INTACTHIGH
mdefine_line|#define CS8427_INTACTHIGH&t;(0&lt;&lt;1)&t;/* active high */
DECL|macro|CS8427_INTACTLOW
mdefine_line|#define CS8427_INTACTLOW&t;(1&lt;&lt;1)&t;/* active low */
DECL|macro|CS8427_INTOPENDRAIN
mdefine_line|#define CS8427_INTOPENDRAIN&t;(2&lt;&lt;1)&t;/* open drain, active low */
DECL|macro|CS8427_TCBLDIR
mdefine_line|#define CS8427_TCBLDIR&t;&t;(1&lt;&lt;0)&t;/* 0 = TCBL is an input, 1 = TCBL is an output */
multiline_comment|/* CS8427_REQ_CONTROL2 bits */
DECL|macro|CS8427_HOLDMASK
mdefine_line|#define CS8427_HOLDMASK&t;&t;(3&lt;&lt;5)&t;/* action when a receiver error occurs */
DECL|macro|CS8427_HOLDLASTSAMPLE
mdefine_line|#define CS8427_HOLDLASTSAMPLE&t;(0&lt;&lt;5)&t;/* hold the last valid sample */
DECL|macro|CS8427_HOLDZERO
mdefine_line|#define CS8427_HOLDZERO&t;&t;(1&lt;&lt;5)&t;/* replace the current audio sample with zero (mute) */
DECL|macro|CS8427_HOLDNOCHANGE
mdefine_line|#define CS8427_HOLDNOCHANGE&t;(2&lt;&lt;5)&t;/* do not change the received audio sample */
DECL|macro|CS8427_RMCKF
mdefine_line|#define CS8427_RMCKF&t;&t;(1&lt;&lt;4)&t;/* 0 = 256*Fsi, 1 = 128*Fsi */
DECL|macro|CS8427_MMR
mdefine_line|#define CS8427_MMR&t;&t;(1&lt;&lt;3)&t;/* AES3 receiver operation, 0 = stereo, 1 = mono */
DECL|macro|CS8427_MMT
mdefine_line|#define CS8427_MMT&t;&t;(1&lt;&lt;2)&t;/* AES3 transmitter operation, 0 = stereo, 1 = mono */
DECL|macro|CS8427_MMTCS
mdefine_line|#define CS8427_MMTCS&t;&t;(1&lt;&lt;1)&t;/* 0 = use A + B CS data, 1 = use MMTLR CS data */
DECL|macro|CS8427_MMTLR
mdefine_line|#define CS8427_MMTLR&t;&t;(1&lt;&lt;0)&t;/* 0 = use A CS data, 1 = use B CS data */
multiline_comment|/* CS8427_REG_DATAFLOW */
DECL|macro|CS8427_TXOFF
mdefine_line|#define CS8427_TXOFF&t;&t;(1&lt;&lt;6)&t;/* AES3 transmitter Output, 0 = normal operation, 1 = off (0V) */
DECL|macro|CS8427_AESBP
mdefine_line|#define CS8427_AESBP&t;&t;(1&lt;&lt;5)&t;/* AES3 hardware bypass mode, 0 = normal, 1 = bypass (RX-&gt;TX) */
DECL|macro|CS8427_TXDMASK
mdefine_line|#define CS8427_TXDMASK&t;&t;(3&lt;&lt;3)&t;/* AES3 Transmitter Data Source Mask */
DECL|macro|CS8427_TXDSERIAL
mdefine_line|#define CS8427_TXDSERIAL&t;(1&lt;&lt;3)&t;/* TXD - serial audio input port */
DECL|macro|CS8427_TXAES3DRECEIVER
mdefine_line|#define CS8427_TXAES3DRECEIVER&t;(2&lt;&lt;3)&t;/* TXD - AES3 receiver */
DECL|macro|CS8427_SPDMASK
mdefine_line|#define CS8427_SPDMASK&t;&t;(3&lt;&lt;1)&t;/* Serial Audio Output Port Data Source Mask */
DECL|macro|CS8427_SPDSERIAL
mdefine_line|#define CS8427_SPDSERIAL&t;(1&lt;&lt;1)&t;/* SPD - serial audio input port */
DECL|macro|CS8427_SPDAES3RECEIVER
mdefine_line|#define CS8427_SPDAES3RECEIVER&t;(2&lt;&lt;1)&t;/* SPD - AES3 receiver */
multiline_comment|/* CS8427_REG_CLOCKSOURCE */
DECL|macro|CS8427_RUN
mdefine_line|#define CS8427_RUN&t;&t;(1&lt;&lt;6)&t;/* 0 = clock off, 1 = clock on */
DECL|macro|CS8427_CLKMASK
mdefine_line|#define CS8427_CLKMASK&t;&t;(3&lt;&lt;4)&t;/* OMCK frequency mask */
DECL|macro|CS8427_CLK256
mdefine_line|#define CS8427_CLK256&t;&t;(0&lt;&lt;4)&t;/* 256*Fso */
DECL|macro|CS8427_CLK384
mdefine_line|#define CS8427_CLK384&t;&t;(1&lt;&lt;4)&t;/* 384*Fso */
DECL|macro|CS8427_CLK512
mdefine_line|#define CS8427_CLK512&t;&t;(2&lt;&lt;4)&t;/* 512*Fso */
DECL|macro|CS8427_OUTC
mdefine_line|#define CS8427_OUTC&t;&t;(1&lt;&lt;3)&t;/* Output Time Base, 0 = OMCK, 1 = recovered input clock */
DECL|macro|CS8427_INC
mdefine_line|#define CS8427_INC&t;&t;(1&lt;&lt;2)&t;/* Input Time Base Clock Source, 0 = recoverd input clock, 1 = OMCK input pin */
DECL|macro|CS8427_RXDMASK
mdefine_line|#define CS8427_RXDMASK&t;&t;(3&lt;&lt;0)&t;/* Recovered Input Clock Source Mask */
DECL|macro|CS8427_RXDILRCK
mdefine_line|#define CS8427_RXDILRCK&t;&t;(0&lt;&lt;0)&t;/* 256*Fsi from ILRCK pin */
DECL|macro|CS8427_RXDAES3INPUT
mdefine_line|#define CS8427_RXDAES3INPUT&t;(1&lt;&lt;0)&t;/* 256*Fsi from AES3 input */
DECL|macro|CS8427_EXTCLOCKRESET
mdefine_line|#define CS8427_EXTCLOCKRESET&t;(2&lt;&lt;0)&t;/* bypass PLL, 256*Fsi clock, synchronous reset */
DECL|macro|CS8427_EXTCLOCK
mdefine_line|#define CS8427_EXTCLOCK&t;&t;(3&lt;&lt;0)&t;/* bypass PLL, 256*Fsi clock */
multiline_comment|/* CS8427_REG_SERIALINPUT */
DECL|macro|CS8427_SIMS
mdefine_line|#define CS8427_SIMS&t;&t;(1&lt;&lt;7)&t;/* 0 = slave, 1 = master mode */
DECL|macro|CS8427_SISF
mdefine_line|#define CS8427_SISF&t;&t;(1&lt;&lt;6)&t;/* ISCLK freq, 0 = 64*Fsi, 1 = 128*Fsi */
DECL|macro|CS8427_SIRESMASK
mdefine_line|#define CS8427_SIRESMASK&t;(3&lt;&lt;4)&t;/* Resolution of the input data for right justified formats */
DECL|macro|CS8427_SIRES24
mdefine_line|#define CS8427_SIRES24&t;&t;(0&lt;&lt;4)&t;/* SIRES 24-bit */
DECL|macro|CS8427_SIRES20
mdefine_line|#define CS8427_SIRES20&t;&t;(1&lt;&lt;4)&t;/* SIRES 20-bit */
DECL|macro|CS8427_SIRES16
mdefine_line|#define CS8427_SIRES16&t;&t;(2&lt;&lt;4)&t;/* SIRES 16-bit */
DECL|macro|CS8427_SIJUST
mdefine_line|#define CS8427_SIJUST&t;&t;(1&lt;&lt;3)&t;/* Justification of SDIN data relative to ILRCK, 0 = left-justified, 1 = right-justified */
DECL|macro|CS8427_SIDEL
mdefine_line|#define CS8427_SIDEL&t;&t;(1&lt;&lt;2)&t;/* Delay of SDIN data relative to ILRCK for left-justified data formats, 0 = first ISCLK period, 1 = second ISCLK period */
DECL|macro|CS8427_SISPOL
mdefine_line|#define CS8427_SISPOL&t;&t;(1&lt;&lt;1)&t;/* ICLK clock polarity, 0 = rising edge of ISCLK, 1 = falling edge of ISCLK */
DECL|macro|CS8427_SILRPOL
mdefine_line|#define CS8427_SILRPOL&t;&t;(1&lt;&lt;0)&t;/* ILRCK clock polarity, 0 = SDIN data left channel when ILRCK is high, 1 = SDIN right when ILRCK is high */
multiline_comment|/* CS8427_REG_SERIALOUTPUT */
DECL|macro|CS8427_SOMS
mdefine_line|#define CS8427_SOMS&t;&t;(1&lt;&lt;7)&t;/* 0 = slave, 1 = master mode */
DECL|macro|CS8427_SOSF
mdefine_line|#define CS8427_SOSF&t;&t;(1&lt;&lt;6)&t;/* OSCLK freq, 0 = 64*Fso, 1 = 128*Fso */
DECL|macro|CS8427_SORESMASK
mdefine_line|#define CS8427_SORESMASK&t;(3&lt;&lt;4)&t;/* Resolution of the output data on SDOUT and AES3 output */
DECL|macro|CS8427_SORES24
mdefine_line|#define CS8427_SORES24&t;&t;(0&lt;&lt;4)&t;/* SIRES 24-bit */
DECL|macro|CS8427_SORES20
mdefine_line|#define CS8427_SORES20&t;&t;(1&lt;&lt;4)&t;/* SIRES 20-bit */
DECL|macro|CS8427_SORES16
mdefine_line|#define CS8427_SORES16&t;&t;(2&lt;&lt;4)&t;/* SIRES 16-bit */
DECL|macro|CS8427_SORESDIRECT
mdefine_line|#define CS8427_SORESDIRECT&t;(2&lt;&lt;4)&t;/* SIRES direct copy from AES3 receiver */
DECL|macro|CS8427_SOJUST
mdefine_line|#define CS8427_SOJUST&t;&t;(1&lt;&lt;3)&t;/* Justification of SDOUT data relative to OLRCK, 0 = left-justified, 1 = right-justified */
DECL|macro|CS8427_SODEL
mdefine_line|#define CS8427_SODEL&t;&t;(1&lt;&lt;2)&t;/* Delay of SDOUT data relative to OLRCK for left-justified data formats, 0 = first OSCLK period, 1 = second OSCLK period */
DECL|macro|CS8427_SOSPOL
mdefine_line|#define CS8427_SOSPOL&t;&t;(1&lt;&lt;1)&t;/* OSCLK clock polarity, 0 = rising edge of ISCLK, 1 = falling edge of ISCLK */
DECL|macro|CS8427_SOLRPOL
mdefine_line|#define CS8427_SOLRPOL&t;&t;(1&lt;&lt;0)&t;/* OLRCK clock polarity, 0 = SDOUT data left channel when OLRCK is high, 1 = SDOUT right when OLRCK is high */
multiline_comment|/* CS8427_REG_INT1STATUS */
DECL|macro|CS8427_TSLIP
mdefine_line|#define CS8427_TSLIP&t;&t;(1&lt;&lt;7)&t;/* AES3 transmitter source data slip interrupt */
DECL|macro|CS8427_OSLIP
mdefine_line|#define CS8427_OSLIP&t;&t;(1&lt;&lt;6)&t;/* Serial audio output port data slip interrupt */
DECL|macro|CS8427_DETC
mdefine_line|#define CS8427_DETC&t;&t;(1&lt;&lt;2)&t;/* D to E C-buffer transfer interrupt */
DECL|macro|CS8427_EFTC
mdefine_line|#define CS8427_EFTC&t;&t;(1&lt;&lt;1)&t;/* E to F C-buffer transfer interrupt */
DECL|macro|CS8427_RERR
mdefine_line|#define CS8427_RERR&t;&t;(1&lt;&lt;0)&t;/* A receiver error has occurred */
multiline_comment|/* CS8427_REG_INT2STATUS */
DECL|macro|CS8427_DETU
mdefine_line|#define CS8427_DETU&t;&t;(1&lt;&lt;3)&t;/* D to E U-buffer transfer interrupt */
DECL|macro|CS8427_EFTU
mdefine_line|#define CS8427_EFTU&t;&t;(1&lt;&lt;2)&t;/* E to F U-buffer transfer interrupt */
DECL|macro|CS8427_QCH
mdefine_line|#define CS8427_QCH&t;&t;(1&lt;&lt;1)&t;/* A new block of Q-subcode data is available for reading */
multiline_comment|/* CS8427_REG_INT1MODEMSB &amp;&amp; CS8427_REG_INT1MODELSB */
multiline_comment|/* bits are defined in CS8427_REG_INT1STATUS */
multiline_comment|/* CS8427_REG_INT2MODEMSB &amp;&amp; CS8427_REG_INT2MODELSB */
multiline_comment|/* bits are defined in CS8427_REG_INT2STATUS */
DECL|macro|CS8427_INTMODERISINGMSB
mdefine_line|#define CS8427_INTMODERISINGMSB&t;0
DECL|macro|CS8427_INTMODERESINGLSB
mdefine_line|#define CS8427_INTMODERESINGLSB&t;0
DECL|macro|CS8427_INTMODEFALLINGMSB
mdefine_line|#define CS8427_INTMODEFALLINGMSB 0
DECL|macro|CS8427_INTMODEFALLINGLSB
mdefine_line|#define CS8427_INTMODEFALLINGLSB 1
DECL|macro|CS8427_INTMODELEVELMSB
mdefine_line|#define CS8427_INTMODELEVELMSB&t;1
DECL|macro|CS8427_INTMODELEVELLSB
mdefine_line|#define CS8427_INTMODELEVELLSB&t;0
multiline_comment|/* CS8427_REG_RECVCSDATA */
DECL|macro|CS8427_AUXMASK
mdefine_line|#define CS8427_AUXMASK&t;&t;(15&lt;&lt;4)&t;/* auxiliary data field width */
DECL|macro|CS8427_AUXSHIFT
mdefine_line|#define CS8427_AUXSHIFT&t;&t;4
DECL|macro|CS8427_PRO
mdefine_line|#define CS8427_PRO&t;&t;(1&lt;&lt;3)&t;/* Channel status block format indicator */
DECL|macro|CS8427_AUDIO
mdefine_line|#define CS8427_AUDIO&t;&t;(1&lt;&lt;2)&t;/* Audio indicator (0 = audio, 1 = nonaudio */
DECL|macro|CS8427_COPY
mdefine_line|#define CS8427_COPY&t;&t;(1&lt;&lt;1)&t;/* 0 = copyright asserted, 1 = copyright not asserted */
DECL|macro|CS8427_ORIG
mdefine_line|#define CS8427_ORIG&t;&t;(1&lt;&lt;0)&t;/* SCMS generation indicator, 0 = 1st generation or highter, 1 = original */
multiline_comment|/* CS8427_REG_RECVERRORS */
multiline_comment|/* CS8427_REG_RECVERRMASK for CS8427_RERR */
DECL|macro|CS8427_QCRC
mdefine_line|#define CS8427_QCRC&t;&t;(1&lt;&lt;6)&t;/* Q-subcode data CRC error indicator */
DECL|macro|CS8427_CCRC
mdefine_line|#define CS8427_CCRC&t;&t;(1&lt;&lt;5)&t;/* Chancnel Status Block Cyclick Redundancy Check Bit */
DECL|macro|CS8427_UNLOCK
mdefine_line|#define CS8427_UNLOCK&t;&t;(1&lt;&lt;4)&t;/* PLL lock status bit */
DECL|macro|CS8427_V
mdefine_line|#define CS8427_V&t;&t;(1&lt;&lt;3)&t;/* 0 = valid data */
DECL|macro|CS8427_CONF
mdefine_line|#define CS8427_CONF&t;&t;(1&lt;&lt;2)&t;/* Confidence bit */
DECL|macro|CS8427_BIP
mdefine_line|#define CS8427_BIP&t;&t;(1&lt;&lt;1)&t;/* Bi-phase error bit */
DECL|macro|CS8427_PAR
mdefine_line|#define CS8427_PAR&t;&t;(1&lt;&lt;0)&t;/* Parity error */
multiline_comment|/* CS8427_REG_CSDATABUF&t;*/
DECL|macro|CS8427_BSEL
mdefine_line|#define CS8427_BSEL&t;&t;(1&lt;&lt;5)&t;/* 0 = CS data, 1 = U data */
DECL|macro|CS8427_CBMR
mdefine_line|#define CS8427_CBMR&t;&t;(1&lt;&lt;4)&t;/* 0 = overwrite first 5 bytes for CS D to E buffer, 1 = prevent */
DECL|macro|CS8427_DETCI
mdefine_line|#define CS8427_DETCI&t;&t;(1&lt;&lt;3)&t;/* D to E CS data buffer transfer inhibit bit, 0 = allow, 1 = inhibit */
DECL|macro|CS8427_EFTCI
mdefine_line|#define CS8427_EFTCI&t;&t;(1&lt;&lt;2)&t;/* E to F CS data buffer transfer inhibit bit, 0 = allow, 1 = inhibit */
DECL|macro|CS8427_CAM
mdefine_line|#define CS8427_CAM&t;&t;(1&lt;&lt;1)&t;/* CS data buffer control port access mode bit, 0 = one byte, 1 = two byte */
DECL|macro|CS8427_CHS
mdefine_line|#define CS8427_CHS&t;&t;(1&lt;&lt;0)&t;/* Channel select bit, 0 = Channel A, 1 = Channel B */
multiline_comment|/* CS8427_REG_UDATABUF */
DECL|macro|CS8427_UD
mdefine_line|#define CS8427_UD&t;&t;(1&lt;&lt;4)&t;/* User data pin (U) direction, 0 = input, 1 = output */
DECL|macro|CS8427_UBMMASK
mdefine_line|#define CS8427_UBMMASK&t;&t;(3&lt;&lt;2)&t;/* Operating mode of the AES3 U bit manager */
DECL|macro|CS8427_UBMZEROS
mdefine_line|#define CS8427_UBMZEROS&t;&t;(0&lt;&lt;2)&t;/* transmit all zeros mode */
DECL|macro|CS8427_UBMBLOCK
mdefine_line|#define CS8427_UBMBLOCK&t;&t;(1&lt;&lt;2)&t;/* block mode */
DECL|macro|CS8427_DETUI
mdefine_line|#define CS8427_DETUI&t;&t;(1&lt;&lt;1)&t;/* D to E U-data buffer transfer inhibit bit, 0 = allow, 1 = inhibit */
DECL|macro|CS8427_EFTUI
mdefine_line|#define CS8427_EFTUI&t;&t;(1&lt;&lt;1)&t;/* E to F U-data buffer transfer inhibit bit, 0 = allow, 1 = inhibit */
multiline_comment|/* CS8427_REG_ID_AND_VER */
DECL|macro|CS8427_IDMASK
mdefine_line|#define CS8427_IDMASK&t;&t;(15&lt;&lt;4)
DECL|macro|CS8427_IDSHIFT
mdefine_line|#define CS8427_IDSHIFT&t;&t;4
DECL|macro|CS8427_VERMASK
mdefine_line|#define CS8427_VERMASK&t;&t;(15&lt;&lt;0)
DECL|macro|CS8427_VERSHIFT
mdefine_line|#define CS8427_VERSHIFT&t;&t;0
DECL|macro|CS8427_VER8427A
mdefine_line|#define CS8427_VER8427A&t;&t;0x71
r_int
id|snd_cs8427_detect
c_func
(paren
id|snd_i2c_bus_t
op_star
id|bus
comma
r_int
r_char
id|addr
)paren
suffix:semicolon
r_int
id|snd_cs8427_create
c_func
(paren
id|snd_i2c_bus_t
op_star
id|bus
comma
r_int
r_char
id|addr
comma
id|snd_i2c_device_t
op_star
op_star
id|r_cs8427
)paren
suffix:semicolon
r_int
id|snd_cs8427_iec958_build
c_func
(paren
id|snd_i2c_device_t
op_star
id|cs8427
comma
id|snd_pcm_substream_t
op_star
id|playback_substream
comma
id|snd_pcm_substream_t
op_star
id|capture_substream
)paren
suffix:semicolon
r_int
id|snd_cs8427_iec958_active
c_func
(paren
id|snd_i2c_device_t
op_star
id|cs8427
comma
r_int
id|active
)paren
suffix:semicolon
r_int
id|snd_cs8427_iec958_pcm
c_func
(paren
id|snd_i2c_device_t
op_star
id|cs8427
comma
r_int
r_int
id|rate
)paren
suffix:semicolon
macro_line|#endif /* __SOUND_CS8427_H */
eof
