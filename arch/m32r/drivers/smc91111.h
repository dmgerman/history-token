multiline_comment|/*------------------------------------------------------------------------&n; . smc91111.h - macros for the LAN91C111 Ethernet Driver&n; .&n; . Copyright (C) 2001 Standard Microsystems Corporation (SMSC)&n; .       Developed by Simple Network Magic Corporation (SNMC)&n; . Copyright (C) 1996 by Erik Stahlman (ES)&n; .&n; . This program is free software; you can redistribute it and/or modify&n; . it under the terms of the GNU General Public License as published by&n; . the Free Software Foundation; either version 2 of the License, or&n; . (at your option) any later version.&n; .&n; . This program is distributed in the hope that it will be useful,&n; . but WITHOUT ANY WARRANTY; without even the implied warranty of&n; . MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; . GNU General Public License for more details.&n; .&n; . You should have received a copy of the GNU General Public License&n; . along with this program; if not, write to the Free Software&n; . Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; .&n; . This file contains register information and access macros for&n; . the LAN91C111 single chip ethernet controller.  It is a modified&n; . version of the smc9194.h file.&n; .&n; . Information contained in this file was obtained from the LAN91C111&n; . manual from SMC.  To get a copy, if you really want one, you can find&n; . information under www.smsc.com.&n; .&n; . Authors&n; . &t;Erik Stahlman&t;&t;&t;&t;( erik@vt.edu )&n; .&t;Daris A Nevil&t;&t;&t;&t;( dnevil@snmc.com )&n; .&n; . History&n; . 03/16/01&t;&t;Daris A Nevil&t;Modified for use with LAN91C111 device&n; .&n; ---------------------------------------------------------------------------*/
macro_line|#ifndef _SMC91111_H_
DECL|macro|_SMC91111_H_
mdefine_line|#define _SMC91111_H_
multiline_comment|/* I want some simple types */
DECL|typedef|byte
r_typedef
r_int
r_char
id|byte
suffix:semicolon
DECL|typedef|word
r_typedef
r_int
r_int
id|word
suffix:semicolon
DECL|typedef|dword
r_typedef
r_int
r_int
r_int
id|dword
suffix:semicolon
multiline_comment|/* Because of bank switching, the LAN91xxx uses only 16 I/O ports */
DECL|macro|SMC_IO_EXTENT
mdefine_line|#define SMC_IO_EXTENT&t;16
multiline_comment|/*---------------------------------------------------------------&n; .&n; . A description of the SMSC registers is probably in order here,&n; . although for details, the SMC datasheet is invaluable.&n; .&n; . Basically, the chip has 4 banks of registers ( 0 to 3 ), which&n; . are accessed by writing a number into the BANK_SELECT register&n; . ( I also use a SMC_SELECT_BANK macro for this ).&n; .&n; . The banks are configured so that for most purposes, bank 2 is all&n; . that is needed for simple run time tasks.&n; -----------------------------------------------------------------------*/
multiline_comment|/*&n; . Bank Select Register:&n; .&n; .&t;&t;yyyy yyyy 0000 00xx&n; .&t;&t;xx &t;&t;= bank number&n; .&t;&t;yyyy yyyy&t;= 0x33, for identification purposes.&n;*/
DECL|macro|BANK_SELECT
mdefine_line|#define&t;BANK_SELECT&t;&t;14
singleline_comment|// Transmit Control Register
multiline_comment|/* BANK 0  */
DECL|macro|TCR_REG
mdefine_line|#define&t;TCR_REG &t;0x0000 &t;
singleline_comment|// transmit control register
DECL|macro|TCR_ENABLE
mdefine_line|#define TCR_ENABLE&t;0x0001&t;
singleline_comment|// When 1 we can transmit
DECL|macro|TCR_LOOP
mdefine_line|#define TCR_LOOP&t;0x0002&t;
singleline_comment|// Controls output pin LBK
DECL|macro|TCR_FORCOL
mdefine_line|#define TCR_FORCOL&t;0x0004&t;
singleline_comment|// When 1 will force a collision
DECL|macro|TCR_PAD_EN
mdefine_line|#define TCR_PAD_EN&t;0x0080&t;
singleline_comment|// When 1 will pad tx frames &lt; 64 bytes w/0
DECL|macro|TCR_NOCRC
mdefine_line|#define TCR_NOCRC&t;0x0100&t;
singleline_comment|// When 1 will not append CRC to tx frames
DECL|macro|TCR_MON_CSN
mdefine_line|#define TCR_MON_CSN&t;0x0400&t;
singleline_comment|// When 1 tx monitors carrier
DECL|macro|TCR_FDUPLX
mdefine_line|#define TCR_FDUPLX    &t;0x0800  
singleline_comment|// When 1 enables full duplex operation
DECL|macro|TCR_STP_SQET
mdefine_line|#define TCR_STP_SQET&t;0x1000&t;
singleline_comment|// When 1 stops tx if Signal Quality Error
DECL|macro|TCR_EPH_LOOP
mdefine_line|#define&t;TCR_EPH_LOOP&t;0x2000&t;
singleline_comment|// When 1 enables EPH block loopback
DECL|macro|TCR_SWFDUP
mdefine_line|#define&t;TCR_SWFDUP&t;0x8000&t;
singleline_comment|// When 1 enables Switched Full Duplex mode
DECL|macro|TCR_CLEAR
mdefine_line|#define&t;TCR_CLEAR&t;0&t;/* do NOTHING */
multiline_comment|/* the default settings for the TCR register : */
multiline_comment|/* QUESTION: do I want to enable padding of short packets ? */
DECL|macro|TCR_DEFAULT
mdefine_line|#define&t;TCR_DEFAULT  &t;TCR_ENABLE
singleline_comment|// EPH Status Register
multiline_comment|/* BANK 0  */
DECL|macro|EPH_STATUS_REG
mdefine_line|#define EPH_STATUS_REG&t;0x0002
DECL|macro|ES_TX_SUC
mdefine_line|#define ES_TX_SUC&t;0x0001&t;
singleline_comment|// Last TX was successful
DECL|macro|ES_SNGL_COL
mdefine_line|#define ES_SNGL_COL&t;0x0002&t;
singleline_comment|// Single collision detected for last tx
DECL|macro|ES_MUL_COL
mdefine_line|#define ES_MUL_COL&t;0x0004&t;
singleline_comment|// Multiple collisions detected for last tx
DECL|macro|ES_LTX_MULT
mdefine_line|#define ES_LTX_MULT&t;0x0008&t;
singleline_comment|// Last tx was a multicast
DECL|macro|ES_16COL
mdefine_line|#define ES_16COL&t;0x0010&t;
singleline_comment|// 16 Collisions Reached
DECL|macro|ES_SQET
mdefine_line|#define ES_SQET&t;&t;0x0020&t;
singleline_comment|// Signal Quality Error Test
DECL|macro|ES_LTXBRD
mdefine_line|#define ES_LTXBRD&t;0x0040&t;
singleline_comment|// Last tx was a broadcast
DECL|macro|ES_TXDEFR
mdefine_line|#define ES_TXDEFR&t;0x0080&t;
singleline_comment|// Transmit Deferred
DECL|macro|ES_LATCOL
mdefine_line|#define ES_LATCOL&t;0x0200&t;
singleline_comment|// Late collision detected on last tx
DECL|macro|ES_LOSTCARR
mdefine_line|#define ES_LOSTCARR&t;0x0400&t;
singleline_comment|// Lost Carrier Sense
DECL|macro|ES_EXC_DEF
mdefine_line|#define ES_EXC_DEF&t;0x0800&t;
singleline_comment|// Excessive Deferral
DECL|macro|ES_CTR_ROL
mdefine_line|#define ES_CTR_ROL&t;0x1000&t;
singleline_comment|// Counter Roll Over indication
DECL|macro|ES_LINK_OK
mdefine_line|#define ES_LINK_OK&t;0x4000&t;
singleline_comment|// Driven by inverted value of nLNK pin
DECL|macro|ES_TXUNRN
mdefine_line|#define ES_TXUNRN&t;0x8000&t;
singleline_comment|// Tx Underrun
singleline_comment|// Receive Control Register
multiline_comment|/* BANK 0  */
DECL|macro|RCR_REG
mdefine_line|#define&t;RCR_REG&t;&t;0x0004
DECL|macro|RCR_RX_ABORT
mdefine_line|#define&t;RCR_RX_ABORT&t;0x0001&t;
singleline_comment|// Set if a rx frame was aborted
DECL|macro|RCR_PRMS
mdefine_line|#define&t;RCR_PRMS&t;0x0002&t;
singleline_comment|// Enable promiscuous mode
DECL|macro|RCR_ALMUL
mdefine_line|#define&t;RCR_ALMUL&t;0x0004&t;
singleline_comment|// When set accepts all multicast frames
DECL|macro|RCR_RXEN
mdefine_line|#define RCR_RXEN&t;0x0100&t;
singleline_comment|// IFF this is set, we can receive packets
DECL|macro|RCR_STRIP_CRC
mdefine_line|#define&t;RCR_STRIP_CRC&t;0x0200&t;
singleline_comment|// When set strips CRC from rx packets
DECL|macro|RCR_ABORT_ENB
mdefine_line|#define&t;RCR_ABORT_ENB&t;0x0200&t;
singleline_comment|// When set will abort rx on collision
DECL|macro|RCR_FILT_CAR
mdefine_line|#define&t;RCR_FILT_CAR&t;0x0400&t;
singleline_comment|// When set filters leading 12 bit s of carrier
DECL|macro|RCR_SOFTRST
mdefine_line|#define RCR_SOFTRST&t;0x8000 &t;
singleline_comment|// resets the chip
multiline_comment|/* the normal settings for the RCR register : */
DECL|macro|RCR_DEFAULT
mdefine_line|#define&t;RCR_DEFAULT&t;(RCR_STRIP_CRC | RCR_RXEN)
DECL|macro|RCR_CLEAR
mdefine_line|#define RCR_CLEAR&t;0x0&t;
singleline_comment|// set it to a base state
singleline_comment|// Counter Register
multiline_comment|/* BANK 0  */
DECL|macro|COUNTER_REG
mdefine_line|#define&t;COUNTER_REG&t;0x0006
singleline_comment|// Memory Information Register
multiline_comment|/* BANK 0  */
DECL|macro|MIR_REG
mdefine_line|#define&t;MIR_REG&t;&t;0x0008
singleline_comment|// Receive/Phy Control Register
multiline_comment|/* BANK 0  */
DECL|macro|RPC_REG
mdefine_line|#define&t;RPC_REG&t;&t;0x000A
DECL|macro|RPC_SPEED
mdefine_line|#define&t;RPC_SPEED&t;0x2000&t;
singleline_comment|// When 1 PHY is in 100Mbps mode.
DECL|macro|RPC_DPLX
mdefine_line|#define&t;RPC_DPLX&t;0x1000&t;
singleline_comment|// When 1 PHY is in Full-Duplex Mode
DECL|macro|RPC_ANEG
mdefine_line|#define&t;RPC_ANEG&t;0x0800&t;
singleline_comment|// When 1 PHY is in Auto-Negotiate Mode
DECL|macro|RPC_LSXA_SHFT
mdefine_line|#define&t;RPC_LSXA_SHFT&t;5&t;
singleline_comment|// Bits to shift LS2A,LS1A,LS0A to lsb
DECL|macro|RPC_LSXB_SHFT
mdefine_line|#define&t;RPC_LSXB_SHFT&t;2&t;
singleline_comment|// Bits to get LS2B,LS1B,LS0B to lsb
DECL|macro|RPC_LED_100_10
mdefine_line|#define RPC_LED_100_10&t;(0x00)&t;
singleline_comment|// LED = 100Mbps OR&squot;s with 10Mbps link detect
DECL|macro|RPC_LED_RES
mdefine_line|#define RPC_LED_RES&t;(0x01)&t;
singleline_comment|// LED = Reserved
DECL|macro|RPC_LED_10
mdefine_line|#define RPC_LED_10&t;(0x02)&t;
singleline_comment|// LED = 10Mbps link detect
DECL|macro|RPC_LED_FD
mdefine_line|#define RPC_LED_FD&t;(0x03)&t;
singleline_comment|// LED = Full Duplex Mode
DECL|macro|RPC_LED_TX_RX
mdefine_line|#define RPC_LED_TX_RX&t;(0x04)&t;
singleline_comment|// LED = TX or RX packet occurred
DECL|macro|RPC_LED_100
mdefine_line|#define RPC_LED_100&t;(0x05)&t;
singleline_comment|// LED = 100Mbps link dectect
DECL|macro|RPC_LED_TX
mdefine_line|#define RPC_LED_TX&t;(0x06)&t;
singleline_comment|// LED = TX packet occurred
DECL|macro|RPC_LED_RX
mdefine_line|#define RPC_LED_RX&t;(0x07)&t;
singleline_comment|// LED = RX packet occurred
macro_line|#if defined(__m32r__)
DECL|macro|RPC_DEFAULT
mdefine_line|#define RPC_DEFAULT (RPC_ANEG | (RPC_LED_TX_RX &lt;&lt; RPC_LSXA_SHFT) | (RPC_LED_100_10 &lt;&lt; RPC_LSXB_SHFT) | RPC_SPEED | RPC_DPLX)
macro_line|#else
DECL|macro|RPC_DEFAULT
mdefine_line|#define RPC_DEFAULT (RPC_ANEG | (RPC_LED_100 &lt;&lt; RPC_LSXA_SHFT) | (RPC_LED_FD &lt;&lt; RPC_LSXB_SHFT) | RPC_SPEED | RPC_DPLX)
macro_line|#endif
multiline_comment|/* Bank 0 0x000C is reserved */
singleline_comment|// Bank Select Register
multiline_comment|/* All Banks */
DECL|macro|BSR_REG
mdefine_line|#define BSR_REG&t;0x000E
singleline_comment|// Configuration Reg
multiline_comment|/* BANK 1 */
DECL|macro|CONFIG_REG
mdefine_line|#define CONFIG_REG&t;0x0000
DECL|macro|CONFIG_EXT_PHY
mdefine_line|#define CONFIG_EXT_PHY&t;0x0200&t;
singleline_comment|// 1=external MII, 0=internal Phy
DECL|macro|CONFIG_GPCNTRL
mdefine_line|#define CONFIG_GPCNTRL&t;0x0400&t;
singleline_comment|// Inverse value drives pin nCNTRL
DECL|macro|CONFIG_NO_WAIT
mdefine_line|#define CONFIG_NO_WAIT&t;0x1000&t;
singleline_comment|// When 1 no extra wait states on ISA bus
DECL|macro|CONFIG_EPH_POWER_EN
mdefine_line|#define CONFIG_EPH_POWER_EN 0x8000 
singleline_comment|// When 0 EPH is placed into low power mode.
singleline_comment|// Default is powered-up, Internal Phy, Wait States, and pin nCNTRL=low
DECL|macro|CONFIG_DEFAULT
mdefine_line|#define CONFIG_DEFAULT&t;(CONFIG_EPH_POWER_EN)
singleline_comment|// Base Address Register
multiline_comment|/* BANK 1 */
DECL|macro|BASE_REG
mdefine_line|#define&t;BASE_REG&t;0x0002
singleline_comment|// Individual Address Registers
multiline_comment|/* BANK 1 */
DECL|macro|ADDR0_REG
mdefine_line|#define&t;ADDR0_REG&t;0x0004
DECL|macro|ADDR1_REG
mdefine_line|#define&t;ADDR1_REG&t;0x0006
DECL|macro|ADDR2_REG
mdefine_line|#define&t;ADDR2_REG&t;0x0008
singleline_comment|// General Purpose Register
multiline_comment|/* BANK 1 */
DECL|macro|GP_REG
mdefine_line|#define&t;GP_REG&t;&t;0x000A
singleline_comment|// Control Register
multiline_comment|/* BANK 1 */
DECL|macro|CTL_REG
mdefine_line|#define&t;CTL_REG&t;&t;0x000C
DECL|macro|CTL_RCV_BAD
mdefine_line|#define CTL_RCV_BAD&t;0x4000 
singleline_comment|// When 1 bad CRC packets are received
DECL|macro|CTL_AUTO_RELEASE
mdefine_line|#define CTL_AUTO_RELEASE 0x0800 
singleline_comment|// When 1 tx pages are released automatically
DECL|macro|CTL_LE_ENABLE
mdefine_line|#define&t;CTL_LE_ENABLE&t;0x0080 
singleline_comment|// When 1 enables Link Error interrupt
DECL|macro|CTL_CR_ENABLE
mdefine_line|#define&t;CTL_CR_ENABLE&t;0x0040 
singleline_comment|// When 1 enables Counter Rollover interrupt
DECL|macro|CTL_TE_ENABLE
mdefine_line|#define&t;CTL_TE_ENABLE&t;0x0020 
singleline_comment|// When 1 enables Transmit Error interrupt
DECL|macro|CTL_EEPROM_SELECT
mdefine_line|#define&t;CTL_EEPROM_SELECT 0x0004 
singleline_comment|// Controls EEPROM reload &amp; store
DECL|macro|CTL_RELOAD
mdefine_line|#define&t;CTL_RELOAD&t;0x0002 
singleline_comment|// When set reads EEPROM into registers
DECL|macro|CTL_STORE
mdefine_line|#define&t;CTL_STORE&t;0x0001 
singleline_comment|// When set stores registers into EEPROM
singleline_comment|// MMU Command Register
multiline_comment|/* BANK 2 */
DECL|macro|MMU_CMD_REG
mdefine_line|#define MMU_CMD_REG&t;0x0000
DECL|macro|MC_BUSY
mdefine_line|#define MC_BUSY&t;&t;1&t;
singleline_comment|// When 1 the last release has not completed
DECL|macro|MC_NOP
mdefine_line|#define MC_NOP&t;&t;(0&lt;&lt;5)&t;
singleline_comment|// No Op
DECL|macro|MC_ALLOC
mdefine_line|#define&t;MC_ALLOC&t;(1&lt;&lt;5) &t;
singleline_comment|// OR with number of 256 byte packets
DECL|macro|MC_RESET
mdefine_line|#define&t;MC_RESET&t;(2&lt;&lt;5)&t;
singleline_comment|// Reset MMU to initial state
DECL|macro|MC_REMOVE
mdefine_line|#define&t;MC_REMOVE&t;(3&lt;&lt;5) &t;
singleline_comment|// Remove the current rx packet
DECL|macro|MC_RELEASE
mdefine_line|#define MC_RELEASE  &t;(4&lt;&lt;5) &t;
singleline_comment|// Remove and release the current rx packet
DECL|macro|MC_FREEPKT
mdefine_line|#define MC_FREEPKT  &t;(5&lt;&lt;5) &t;
singleline_comment|// Release packet in PNR register
DECL|macro|MC_ENQUEUE
mdefine_line|#define MC_ENQUEUE&t;(6&lt;&lt;5)&t;
singleline_comment|// Enqueue the packet for transmit
DECL|macro|MC_RSTTXFIFO
mdefine_line|#define MC_RSTTXFIFO&t;(7&lt;&lt;5)&t;
singleline_comment|// Reset the TX FIFOs
singleline_comment|// Packet Number Register
multiline_comment|/* BANK 2 */
DECL|macro|PN_REG
mdefine_line|#define&t;PN_REG&t;&t;0x0002
singleline_comment|// Allocation Result Register
multiline_comment|/* BANK 2 */
DECL|macro|AR_REG
mdefine_line|#define&t;AR_REG&t;&t;0x0003
DECL|macro|AR_FAILED
mdefine_line|#define AR_FAILED&t;0x80&t;
singleline_comment|// Alocation Failed
singleline_comment|// RX FIFO Ports Register
multiline_comment|/* BANK 2 */
DECL|macro|RXFIFO_REG
mdefine_line|#define RXFIFO_REG&t;0x0004&t;
singleline_comment|// Must be read as a word
DECL|macro|RXFIFO_REMPTY
mdefine_line|#define RXFIFO_REMPTY&t;0x8000&t;
singleline_comment|// RX FIFO Empty
singleline_comment|// TX FIFO Ports Register
multiline_comment|/* BANK 2 */
DECL|macro|TXFIFO_REG
mdefine_line|#define TXFIFO_REG&t;RXFIFO_REG&t;
singleline_comment|// Must be read as a word
DECL|macro|TXFIFO_TEMPTY
mdefine_line|#define TXFIFO_TEMPTY&t;0x80&t;
singleline_comment|// TX FIFO Empty
singleline_comment|// Pointer Register
multiline_comment|/* BANK 2 */
DECL|macro|PTR_REG
mdefine_line|#define PTR_REG&t;&t;0x0006
DECL|macro|PTR_RCV
mdefine_line|#define&t;PTR_RCV&t;&t;0x8000 
singleline_comment|// 1=Receive area, 0=Transmit area
DECL|macro|PTR_AUTOINC
mdefine_line|#define&t;PTR_AUTOINC &t;0x4000 
singleline_comment|// Auto increment the pointer on each access
DECL|macro|PTR_READ
mdefine_line|#define PTR_READ&t;0x2000 
singleline_comment|// When 1 the operation is a read
singleline_comment|// Data Register
multiline_comment|/* BANK 2 */
DECL|macro|DATA_REG
mdefine_line|#define&t;DATA_REG&t;0x0008
singleline_comment|// Interrupt Status/Acknowledge Register
multiline_comment|/* BANK 2 */
DECL|macro|INT_REG
mdefine_line|#define&t;INT_REG&t;&t;0x000C
singleline_comment|// Interrupt Mask Register
multiline_comment|/* BANK 2 */
DECL|macro|IM_REG
mdefine_line|#define IM_REG&t;&t;0x000D
DECL|macro|IM_MDINT
mdefine_line|#define&t;IM_MDINT&t;0x80 
singleline_comment|// PHY MI Register 18 Interrupt
DECL|macro|IM_ERCV_INT
mdefine_line|#define&t;IM_ERCV_INT&t;0x40 
singleline_comment|// Early Receive Interrupt
DECL|macro|IM_EPH_INT
mdefine_line|#define&t;IM_EPH_INT&t;0x20 
singleline_comment|// Set by Etheret Protocol Handler section
DECL|macro|IM_RX_OVRN_INT
mdefine_line|#define&t;IM_RX_OVRN_INT&t;0x10 
singleline_comment|// Set by Receiver Overruns
DECL|macro|IM_ALLOC_INT
mdefine_line|#define&t;IM_ALLOC_INT&t;0x08 
singleline_comment|// Set when allocation request is completed
DECL|macro|IM_TX_EMPTY_INT
mdefine_line|#define&t;IM_TX_EMPTY_INT&t;0x04 
singleline_comment|// Set if the TX FIFO goes empty
DECL|macro|IM_TX_INT
mdefine_line|#define&t;IM_TX_INT&t;0x02 
singleline_comment|// Transmit Interrrupt
DECL|macro|IM_RCV_INT
mdefine_line|#define IM_RCV_INT&t;0x01 
singleline_comment|// Receive Interrupt
singleline_comment|// Multicast Table Registers
multiline_comment|/* BANK 3 */
DECL|macro|MCAST_REG1
mdefine_line|#define&t;MCAST_REG1&t;0x0000
DECL|macro|MCAST_REG2
mdefine_line|#define&t;MCAST_REG2&t;0x0002
DECL|macro|MCAST_REG3
mdefine_line|#define&t;MCAST_REG3&t;0x0004
DECL|macro|MCAST_REG4
mdefine_line|#define&t;MCAST_REG4&t;0x0006
singleline_comment|// Management Interface Register (MII)
multiline_comment|/* BANK 3 */
DECL|macro|MII_REG
mdefine_line|#define&t;MII_REG&t;&t;0x0008
DECL|macro|MII_MSK_CRS100
mdefine_line|#define MII_MSK_CRS100&t;0x4000 
singleline_comment|// Disables CRS100 detection during tx half dup
DECL|macro|MII_MDOE
mdefine_line|#define MII_MDOE&t;0x0008 
singleline_comment|// MII Output Enable
DECL|macro|MII_MCLK
mdefine_line|#define MII_MCLK&t;0x0004 
singleline_comment|// MII Clock, pin MDCLK
DECL|macro|MII_MDI
mdefine_line|#define MII_MDI&t;&t;0x0002 
singleline_comment|// MII Input, pin MDI
DECL|macro|MII_MDO
mdefine_line|#define MII_MDO&t;&t;0x0001 
singleline_comment|// MII Output, pin MDO
singleline_comment|// Revision Register
multiline_comment|/* BANK 3 */
DECL|macro|REV_REG
mdefine_line|#define&t;REV_REG&t;&t;0x000A /* ( hi: chip id   low: rev # ) */
singleline_comment|// Early RCV Register
multiline_comment|/* BANK 3 */
multiline_comment|/* this is NOT on SMC9192 */
DECL|macro|ERCV_REG
mdefine_line|#define&t;ERCV_REG&t;0x000C
DECL|macro|ERCV_RCV_DISCRD
mdefine_line|#define ERCV_RCV_DISCRD&t;0x0080 
singleline_comment|// When 1 discards a packet being received
DECL|macro|ERCV_THRESHOLD
mdefine_line|#define ERCV_THRESHOLD&t;0x001F 
singleline_comment|// ERCV Threshold Mask
singleline_comment|// External Register
multiline_comment|/* BANK 7 */
DECL|macro|EXT_REG
mdefine_line|#define&t;EXT_REG&t;&t;0x0000
DECL|macro|CHIP_9192
mdefine_line|#define CHIP_9192&t;3
DECL|macro|CHIP_9194
mdefine_line|#define CHIP_9194&t;4
DECL|macro|CHIP_9195
mdefine_line|#define CHIP_9195&t;5
DECL|macro|CHIP_9196
mdefine_line|#define CHIP_9196&t;6
DECL|macro|CHIP_91100
mdefine_line|#define CHIP_91100&t;7
DECL|macro|CHIP_91100FD
mdefine_line|#define CHIP_91100FD&t;8
DECL|macro|CHIP_91111FD
mdefine_line|#define CHIP_91111FD&t;9
DECL|variable|chip_ids
r_static
r_const
r_char
op_star
id|chip_ids
(braket
l_int|15
)braket
op_assign
(brace
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
multiline_comment|/* 3 */
l_string|&quot;SMC91C90/91C92&quot;
comma
multiline_comment|/* 4 */
l_string|&quot;SMC91C94&quot;
comma
multiline_comment|/* 5 */
l_string|&quot;SMC91C95&quot;
comma
multiline_comment|/* 6 */
l_string|&quot;SMC91C96&quot;
comma
multiline_comment|/* 7 */
l_string|&quot;SMC91C100&quot;
comma
multiline_comment|/* 8 */
l_string|&quot;SMC91C100FD&quot;
comma
multiline_comment|/* 9 */
l_string|&quot;SMC91C11xFD&quot;
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)brace
suffix:semicolon
multiline_comment|/*&n; . Transmit status bits&n;*/
DECL|macro|TS_SUCCESS
mdefine_line|#define TS_SUCCESS 0x0001
DECL|macro|TS_LOSTCAR
mdefine_line|#define TS_LOSTCAR 0x0400
DECL|macro|TS_LATCOL
mdefine_line|#define TS_LATCOL  0x0200
DECL|macro|TS_16COL
mdefine_line|#define TS_16COL   0x0010
multiline_comment|/*&n; . Receive status bits&n;*/
DECL|macro|RS_ALGNERR
mdefine_line|#define RS_ALGNERR&t;0x8000
DECL|macro|RS_BRODCAST
mdefine_line|#define RS_BRODCAST&t;0x4000
DECL|macro|RS_BADCRC
mdefine_line|#define RS_BADCRC&t;0x2000
DECL|macro|RS_ODDFRAME
mdefine_line|#define RS_ODDFRAME&t;0x1000&t;
singleline_comment|// bug: the LAN91C111 never sets this on receive
DECL|macro|RS_TOOLONG
mdefine_line|#define RS_TOOLONG&t;0x0800
DECL|macro|RS_TOOSHORT
mdefine_line|#define RS_TOOSHORT&t;0x0400
DECL|macro|RS_MULTICAST
mdefine_line|#define RS_MULTICAST&t;0x0001
DECL|macro|RS_ERRORS
mdefine_line|#define RS_ERRORS&t;(RS_ALGNERR | RS_BADCRC | RS_TOOLONG | RS_TOOSHORT)
singleline_comment|// PHY Types
r_enum
(brace
DECL|enumerator|PHY_LAN83C183
id|PHY_LAN83C183
op_assign
l_int|1
comma
singleline_comment|// LAN91C111 Internal PHY
DECL|enumerator|PHY_LAN83C180
id|PHY_LAN83C180
)brace
suffix:semicolon
singleline_comment|// PHY Register Addresses (LAN91C111 Internal PHY)
singleline_comment|// PHY Control Register
DECL|macro|PHY_CNTL_REG
mdefine_line|#define PHY_CNTL_REG&t;&t;0x00
DECL|macro|PHY_CNTL_RST
mdefine_line|#define PHY_CNTL_RST&t;&t;0x8000&t;
singleline_comment|// 1=PHY Reset
DECL|macro|PHY_CNTL_LPBK
mdefine_line|#define PHY_CNTL_LPBK&t;&t;0x4000&t;
singleline_comment|// 1=PHY Loopback
DECL|macro|PHY_CNTL_SPEED
mdefine_line|#define PHY_CNTL_SPEED&t;&t;0x2000&t;
singleline_comment|// 1=100Mbps, 0=10Mpbs
DECL|macro|PHY_CNTL_ANEG_EN
mdefine_line|#define PHY_CNTL_ANEG_EN&t;0x1000 
singleline_comment|// 1=Enable Auto negotiation
DECL|macro|PHY_CNTL_PDN
mdefine_line|#define PHY_CNTL_PDN&t;&t;0x0800&t;
singleline_comment|// 1=PHY Power Down mode
DECL|macro|PHY_CNTL_MII_DIS
mdefine_line|#define PHY_CNTL_MII_DIS&t;0x0400&t;
singleline_comment|// 1=MII 4 bit interface disabled
DECL|macro|PHY_CNTL_ANEG_RST
mdefine_line|#define PHY_CNTL_ANEG_RST&t;0x0200 
singleline_comment|// 1=Reset Auto negotiate
DECL|macro|PHY_CNTL_DPLX
mdefine_line|#define PHY_CNTL_DPLX&t;&t;0x0100&t;
singleline_comment|// 1=Full Duplex, 0=Half Duplex
DECL|macro|PHY_CNTL_COLTST
mdefine_line|#define PHY_CNTL_COLTST&t;&t;0x0080&t;
singleline_comment|// 1= MII Colision Test
singleline_comment|// PHY Status Register
DECL|macro|PHY_STAT_REG
mdefine_line|#define PHY_STAT_REG&t;&t;0x01
DECL|macro|PHY_STAT_CAP_T4
mdefine_line|#define PHY_STAT_CAP_T4&t;&t;0x8000&t;
singleline_comment|// 1=100Base-T4 capable
DECL|macro|PHY_STAT_CAP_TXF
mdefine_line|#define PHY_STAT_CAP_TXF&t;0x4000&t;
singleline_comment|// 1=100Base-X full duplex capable
DECL|macro|PHY_STAT_CAP_TXH
mdefine_line|#define PHY_STAT_CAP_TXH&t;0x2000&t;
singleline_comment|// 1=100Base-X half duplex capable
DECL|macro|PHY_STAT_CAP_TF
mdefine_line|#define PHY_STAT_CAP_TF&t;&t;0x1000&t;
singleline_comment|// 1=10Mbps full duplex capable
DECL|macro|PHY_STAT_CAP_TH
mdefine_line|#define PHY_STAT_CAP_TH&t;&t;0x0800&t;
singleline_comment|// 1=10Mbps half duplex capable
DECL|macro|PHY_STAT_CAP_SUPR
mdefine_line|#define PHY_STAT_CAP_SUPR&t;0x0040&t;
singleline_comment|// 1=recv mgmt frames with not preamble
DECL|macro|PHY_STAT_ANEG_ACK
mdefine_line|#define PHY_STAT_ANEG_ACK&t;0x0020&t;
singleline_comment|// 1=ANEG has completed
DECL|macro|PHY_STAT_REM_FLT
mdefine_line|#define PHY_STAT_REM_FLT&t;0x0010&t;
singleline_comment|// 1=Remote Fault detected
DECL|macro|PHY_STAT_CAP_ANEG
mdefine_line|#define PHY_STAT_CAP_ANEG&t;0x0008&t;
singleline_comment|// 1=Auto negotiate capable
DECL|macro|PHY_STAT_LINK
mdefine_line|#define PHY_STAT_LINK&t;&t;0x0004&t;
singleline_comment|// 1=valid link
DECL|macro|PHY_STAT_JAB
mdefine_line|#define PHY_STAT_JAB&t;&t;0x0002&t;
singleline_comment|// 1=10Mbps jabber condition
DECL|macro|PHY_STAT_EXREG
mdefine_line|#define PHY_STAT_EXREG&t;&t;0x0001&t;
singleline_comment|// 1=extended registers implemented
singleline_comment|// PHY Identifier Registers
DECL|macro|PHY_ID1_REG
mdefine_line|#define PHY_ID1_REG&t;&t;0x02&t;
singleline_comment|// PHY Identifier 1
DECL|macro|PHY_ID2_REG
mdefine_line|#define PHY_ID2_REG&t;&t;0x03&t;
singleline_comment|// PHY Identifier 2
singleline_comment|// PHY Auto-Negotiation Advertisement Register
DECL|macro|PHY_AD_REG
mdefine_line|#define PHY_AD_REG&t;&t;0x04
DECL|macro|PHY_AD_NP
mdefine_line|#define PHY_AD_NP&t;&t;0x8000&t;
singleline_comment|// 1=PHY requests exchange of Next Page
DECL|macro|PHY_AD_ACK
mdefine_line|#define PHY_AD_ACK&t;&t;0x4000&t;
singleline_comment|// 1=got link code word from remote
DECL|macro|PHY_AD_RF
mdefine_line|#define PHY_AD_RF&t;&t;0x2000&t;
singleline_comment|// 1=advertise remote fault
DECL|macro|PHY_AD_T4
mdefine_line|#define PHY_AD_T4&t;&t;0x0200&t;
singleline_comment|// 1=PHY is capable of 100Base-T4
DECL|macro|PHY_AD_TX_FDX
mdefine_line|#define PHY_AD_TX_FDX&t;&t;0x0100&t;
singleline_comment|// 1=PHY is capable of 100Base-TX FDPLX
DECL|macro|PHY_AD_TX_HDX
mdefine_line|#define PHY_AD_TX_HDX&t;&t;0x0080&t;
singleline_comment|// 1=PHY is capable of 100Base-TX HDPLX
DECL|macro|PHY_AD_10_FDX
mdefine_line|#define PHY_AD_10_FDX&t;&t;0x0040&t;
singleline_comment|// 1=PHY is capable of 10Base-T FDPLX
DECL|macro|PHY_AD_10_HDX
mdefine_line|#define PHY_AD_10_HDX&t;&t;0x0020&t;
singleline_comment|// 1=PHY is capable of 10Base-T HDPLX
DECL|macro|PHY_AD_CSMA
mdefine_line|#define PHY_AD_CSMA&t;&t;0x0001&t;
singleline_comment|// 1=PHY is capable of 802.3 CMSA
singleline_comment|// PHY Auto-negotiation Remote End Capability Register
DECL|macro|PHY_RMT_REG
mdefine_line|#define PHY_RMT_REG&t;&t;0x05
singleline_comment|// Uses same bit definitions as PHY_AD_REG
singleline_comment|// PHY Configuration Register 1
DECL|macro|PHY_CFG1_REG
mdefine_line|#define PHY_CFG1_REG&t;&t;0x10
DECL|macro|PHY_CFG1_LNKDIS
mdefine_line|#define PHY_CFG1_LNKDIS&t;&t;0x8000&t;
singleline_comment|// 1=Rx Link Detect Function disabled
DECL|macro|PHY_CFG1_XMTDIS
mdefine_line|#define PHY_CFG1_XMTDIS&t;&t;0x4000&t;
singleline_comment|// 1=TP Transmitter Disabled
DECL|macro|PHY_CFG1_XMTPDN
mdefine_line|#define PHY_CFG1_XMTPDN&t;&t;0x2000&t;
singleline_comment|// 1=TP Transmitter Powered Down
DECL|macro|PHY_CFG1_BYPSCR
mdefine_line|#define PHY_CFG1_BYPSCR&t;&t;0x0400&t;
singleline_comment|// 1=Bypass scrambler/descrambler
DECL|macro|PHY_CFG1_UNSCDS
mdefine_line|#define PHY_CFG1_UNSCDS&t;&t;0x0200&t;
singleline_comment|// 1=Unscramble Idle Reception Disable
DECL|macro|PHY_CFG1_EQLZR
mdefine_line|#define PHY_CFG1_EQLZR&t;&t;0x0100&t;
singleline_comment|// 1=Rx Equalizer Disabled
DECL|macro|PHY_CFG1_CABLE
mdefine_line|#define PHY_CFG1_CABLE&t;&t;0x0080&t;
singleline_comment|// 1=STP(150ohm), 0=UTP(100ohm)
DECL|macro|PHY_CFG1_RLVL0
mdefine_line|#define PHY_CFG1_RLVL0&t;&t;0x0040&t;
singleline_comment|// 1=Rx Squelch level reduced by 4.5db
DECL|macro|PHY_CFG1_TLVL_SHIFT
mdefine_line|#define PHY_CFG1_TLVL_SHIFT&t;2&t;
singleline_comment|// Transmit Output Level Adjust
DECL|macro|PHY_CFG1_TLVL_MASK
mdefine_line|#define PHY_CFG1_TLVL_MASK&t;0x003C
DECL|macro|PHY_CFG1_TRF_MASK
mdefine_line|#define PHY_CFG1_TRF_MASK&t;0x0003&t;
singleline_comment|// Transmitter Rise/Fall time
singleline_comment|// PHY Configuration Register 2
DECL|macro|PHY_CFG2_REG
mdefine_line|#define PHY_CFG2_REG&t;&t;0x11
DECL|macro|PHY_CFG2_APOLDIS
mdefine_line|#define PHY_CFG2_APOLDIS&t;0x0020&t;
singleline_comment|// 1=Auto Polarity Correction disabled
DECL|macro|PHY_CFG2_JABDIS
mdefine_line|#define PHY_CFG2_JABDIS&t;&t;0x0010&t;
singleline_comment|// 1=Jabber disabled
DECL|macro|PHY_CFG2_MREG
mdefine_line|#define PHY_CFG2_MREG&t;&t;0x0008&t;
singleline_comment|// 1=Multiple register access (MII mgt)
DECL|macro|PHY_CFG2_INTMDIO
mdefine_line|#define PHY_CFG2_INTMDIO&t;0x0004&t;
singleline_comment|// 1=Interrupt signaled with MDIO pulseo
singleline_comment|// PHY Status Output (and Interrupt status) Register
DECL|macro|PHY_INT_REG
mdefine_line|#define PHY_INT_REG&t;&t;0x12&t;
singleline_comment|// Status Output (Interrupt Status)
DECL|macro|PHY_INT_INT
mdefine_line|#define PHY_INT_INT&t;&t;0x8000&t;
singleline_comment|// 1=bits have changed since last read
DECL|macro|PHY_INT_LNKFAIL
mdefine_line|#define&t;PHY_INT_LNKFAIL&t;&t;0x4000&t;
singleline_comment|// 1=Link Not detected
DECL|macro|PHY_INT_LOSSSYNC
mdefine_line|#define PHY_INT_LOSSSYNC&t;0x2000&t;
singleline_comment|// 1=Descrambler has lost sync
DECL|macro|PHY_INT_CWRD
mdefine_line|#define PHY_INT_CWRD&t;&t;0x1000&t;
singleline_comment|// 1=Invalid 4B5B code detected on rx
DECL|macro|PHY_INT_SSD
mdefine_line|#define PHY_INT_SSD&t;&t;0x0800&t;
singleline_comment|// 1=No Start Of Stream detected on rx
DECL|macro|PHY_INT_ESD
mdefine_line|#define PHY_INT_ESD&t;&t;0x0400&t;
singleline_comment|// 1=No End Of Stream detected on rx
DECL|macro|PHY_INT_RPOL
mdefine_line|#define PHY_INT_RPOL&t;&t;0x0200&t;
singleline_comment|// 1=Reverse Polarity detected
DECL|macro|PHY_INT_JAB
mdefine_line|#define PHY_INT_JAB&t;&t;0x0100&t;
singleline_comment|// 1=Jabber detected
DECL|macro|PHY_INT_SPDDET
mdefine_line|#define PHY_INT_SPDDET&t;&t;0x0080&t;
singleline_comment|// 1=100Base-TX mode, 0=10Base-T mode
DECL|macro|PHY_INT_DPLXDET
mdefine_line|#define PHY_INT_DPLXDET&t;&t;0x0040&t;
singleline_comment|// 1=Device in Full Duplex
singleline_comment|// PHY Interrupt/Status Mask Register
DECL|macro|PHY_MASK_REG
mdefine_line|#define PHY_MASK_REG&t;&t;0x13&t;
singleline_comment|// Interrupt Mask
singleline_comment|// Uses the same bit definitions as PHY_INT_REG
multiline_comment|/*-------------------------------------------------------------------------&n; .  I define some macros to make it easier to do somewhat common&n; . or slightly complicated, repeated tasks.&n; --------------------------------------------------------------------------*/
multiline_comment|/* select a register bank, 0 to 3  */
DECL|macro|SMC_SELECT_BANK
mdefine_line|#define SMC_SELECT_BANK(x)  { outw( x, ioaddr + BANK_SELECT ); }
multiline_comment|/* this enables an interrupt in the interrupt mask register */
DECL|macro|SMC_ENABLE_INT
mdefine_line|#define SMC_ENABLE_INT(x) {&bslash;&n;&t;&t;unsigned char mask;&bslash;&n;&t;&t;SMC_SELECT_BANK(2);&bslash;&n;&t;&t;mask = inb( ioaddr + IM_REG );&bslash;&n;&t;&t;mask |= (x);&bslash;&n;&t;&t;outb( mask, ioaddr + IM_REG ); &bslash;&n;}
multiline_comment|/* this disables an interrupt from the interrupt mask register */
DECL|macro|SMC_DISABLE_INT
mdefine_line|#define SMC_DISABLE_INT(x) {&bslash;&n;&t;&t;unsigned char mask;&bslash;&n;&t;&t;SMC_SELECT_BANK(2);&bslash;&n;&t;&t;mask = inb( ioaddr + IM_REG );&bslash;&n;&t;&t;mask &amp;= ~(x);&bslash;&n;&t;&t;outb( mask, ioaddr + IM_REG ); &bslash;&n;}
multiline_comment|/*----------------------------------------------------------------------&n; . Define the interrupts that I want to receive from the card&n; .&n; . I want:&n; .  IM_EPH_INT, for nasty errors&n; .  IM_RCV_INT, for happy received packets&n; .  IM_RX_OVRN_INT, because I have to kick the receiver&n; .  IM_MDINT, for PHY Register 18 Status Changes&n; --------------------------------------------------------------------------*/
DECL|macro|SMC_INTERRUPT_MASK
mdefine_line|#define SMC_INTERRUPT_MASK   (IM_EPH_INT | IM_RX_OVRN_INT | IM_RCV_INT | &bslash;&n;&t;IM_MDINT)
macro_line|#ifdef CONFIG_SYSCTL
multiline_comment|/*&n; * Declarations for the sysctl interface, which allows users the ability to&n; * control the finer aspects of the LAN91C111 chip.  Since the smc&n; * module currently registers its sysctl table dynamically, the sysctl path&n; * for module FOO is /proc/sys/dev/ethX/FOO&n; */
DECL|macro|CTL_SMC
mdefine_line|#define CTL_SMC         (CTL_BUS+1389)      
singleline_comment|// arbitrary and hopefully unused
r_enum
(brace
DECL|enumerator|CTL_SMC_INFO
id|CTL_SMC_INFO
op_assign
l_int|1
comma
singleline_comment|// Sysctl files information
DECL|enumerator|CTL_SMC_SWVER
id|CTL_SMC_SWVER
comma
singleline_comment|// Driver Software Version Info
DECL|enumerator|CTL_SMC_SWFDUP
id|CTL_SMC_SWFDUP
comma
singleline_comment|// Switched Full Duplex Mode
DECL|enumerator|CTL_SMC_EPHLOOP
id|CTL_SMC_EPHLOOP
comma
singleline_comment|// EPH Block Internal Loopback
DECL|enumerator|CTL_SMC_MIIOP
id|CTL_SMC_MIIOP
comma
singleline_comment|// MII Operation
DECL|enumerator|CTL_SMC_AUTONEG
id|CTL_SMC_AUTONEG
comma
singleline_comment|// Auto-negotiate Mode
DECL|enumerator|CTL_SMC_RFDUPLX
id|CTL_SMC_RFDUPLX
comma
singleline_comment|// Request Full Duplex Mode
DECL|enumerator|CTL_SMC_RSPEED
id|CTL_SMC_RSPEED
comma
singleline_comment|// Request Speed Selection
DECL|enumerator|CTL_SMC_AFDUPLX
id|CTL_SMC_AFDUPLX
comma
singleline_comment|// Actual Full Duplex Mode
DECL|enumerator|CTL_SMC_ASPEED
id|CTL_SMC_ASPEED
comma
singleline_comment|// Actual Speed Selection
DECL|enumerator|CTL_SMC_LNKFAIL
id|CTL_SMC_LNKFAIL
comma
singleline_comment|// Link Failed
DECL|enumerator|CTL_SMC_FORCOL
id|CTL_SMC_FORCOL
comma
singleline_comment|// Force a Collision
DECL|enumerator|CTL_SMC_FILTCAR
id|CTL_SMC_FILTCAR
comma
singleline_comment|// Filter Carrier
DECL|enumerator|CTL_SMC_FREEMEM
id|CTL_SMC_FREEMEM
comma
singleline_comment|// Free Buffer Memory
DECL|enumerator|CTL_SMC_TOTMEM
id|CTL_SMC_TOTMEM
comma
singleline_comment|// Total Buffer Memory
DECL|enumerator|CTL_SMC_LEDA
id|CTL_SMC_LEDA
comma
singleline_comment|// Output of LED-A
DECL|enumerator|CTL_SMC_LEDB
id|CTL_SMC_LEDB
comma
singleline_comment|// Output of LED-B
DECL|enumerator|CTL_SMC_CHIPREV
id|CTL_SMC_CHIPREV
comma
singleline_comment|// LAN91C111 Chip Revision ID
macro_line|#ifdef SMC_DEBUG
singleline_comment|// Register access for debugging
DECL|enumerator|CTL_SMC_REG_BSR
id|CTL_SMC_REG_BSR
comma
singleline_comment|// Bank Select
DECL|enumerator|CTL_SMC_REG_TCR
id|CTL_SMC_REG_TCR
comma
singleline_comment|// Transmit Control
DECL|enumerator|CTL_SMC_REG_ESR
id|CTL_SMC_REG_ESR
comma
singleline_comment|// EPH Status
DECL|enumerator|CTL_SMC_REG_RCR
id|CTL_SMC_REG_RCR
comma
singleline_comment|// Receive Control
DECL|enumerator|CTL_SMC_REG_CTRR
id|CTL_SMC_REG_CTRR
comma
singleline_comment|// Counter
DECL|enumerator|CTL_SMC_REG_MIR
id|CTL_SMC_REG_MIR
comma
singleline_comment|// Memory Information
DECL|enumerator|CTL_SMC_REG_RPCR
id|CTL_SMC_REG_RPCR
comma
singleline_comment|// Receive/Phy Control
DECL|enumerator|CTL_SMC_REG_CFGR
id|CTL_SMC_REG_CFGR
comma
singleline_comment|// Configuration
DECL|enumerator|CTL_SMC_REG_BAR
id|CTL_SMC_REG_BAR
comma
singleline_comment|// Base Address
DECL|enumerator|CTL_SMC_REG_IAR0
id|CTL_SMC_REG_IAR0
comma
singleline_comment|// Individual Address 0
DECL|enumerator|CTL_SMC_REG_IAR1
id|CTL_SMC_REG_IAR1
comma
singleline_comment|// Individual Address 1
DECL|enumerator|CTL_SMC_REG_IAR2
id|CTL_SMC_REG_IAR2
comma
singleline_comment|// Individual Address 2
DECL|enumerator|CTL_SMC_REG_GPR
id|CTL_SMC_REG_GPR
comma
singleline_comment|// General Purpose
DECL|enumerator|CTL_SMC_REG_CTLR
id|CTL_SMC_REG_CTLR
comma
singleline_comment|// Control
DECL|enumerator|CTL_SMC_REG_MCR
id|CTL_SMC_REG_MCR
comma
singleline_comment|// MMU Command
DECL|enumerator|CTL_SMC_REG_PNR
id|CTL_SMC_REG_PNR
comma
singleline_comment|// Packet Number
DECL|enumerator|CTL_SMC_REG_FPR
id|CTL_SMC_REG_FPR
comma
singleline_comment|// FIFO Ports
DECL|enumerator|CTL_SMC_REG_PTR
id|CTL_SMC_REG_PTR
comma
singleline_comment|// Pointer
DECL|enumerator|CTL_SMC_REG_DR
id|CTL_SMC_REG_DR
comma
singleline_comment|// Data
DECL|enumerator|CTL_SMC_REG_ISR
id|CTL_SMC_REG_ISR
comma
singleline_comment|// Interrupt Status
DECL|enumerator|CTL_SMC_REG_MTR1
id|CTL_SMC_REG_MTR1
comma
singleline_comment|// Multicast Table Entry 1
DECL|enumerator|CTL_SMC_REG_MTR2
id|CTL_SMC_REG_MTR2
comma
singleline_comment|// Multicast Table Entry 2
DECL|enumerator|CTL_SMC_REG_MTR3
id|CTL_SMC_REG_MTR3
comma
singleline_comment|// Multicast Table Entry 3
DECL|enumerator|CTL_SMC_REG_MTR4
id|CTL_SMC_REG_MTR4
comma
singleline_comment|// Multicast Table Entry 4
DECL|enumerator|CTL_SMC_REG_MIIR
id|CTL_SMC_REG_MIIR
comma
singleline_comment|// Management Interface
DECL|enumerator|CTL_SMC_REG_REVR
id|CTL_SMC_REG_REVR
comma
singleline_comment|// Revision
DECL|enumerator|CTL_SMC_REG_ERCVR
id|CTL_SMC_REG_ERCVR
comma
singleline_comment|// Early RCV
DECL|enumerator|CTL_SMC_REG_EXTR
id|CTL_SMC_REG_EXTR
comma
singleline_comment|// External
DECL|enumerator|CTL_SMC_PHY_CTRL
id|CTL_SMC_PHY_CTRL
comma
singleline_comment|// PHY Control
DECL|enumerator|CTL_SMC_PHY_STAT
id|CTL_SMC_PHY_STAT
comma
singleline_comment|// PHY Status
DECL|enumerator|CTL_SMC_PHY_ID1
id|CTL_SMC_PHY_ID1
comma
singleline_comment|// PHY ID1
DECL|enumerator|CTL_SMC_PHY_ID2
id|CTL_SMC_PHY_ID2
comma
singleline_comment|// PHY ID2
DECL|enumerator|CTL_SMC_PHY_ADC
id|CTL_SMC_PHY_ADC
comma
singleline_comment|// PHY Advertise Capability
DECL|enumerator|CTL_SMC_PHY_REMC
id|CTL_SMC_PHY_REMC
comma
singleline_comment|// PHY Advertise Capability
DECL|enumerator|CTL_SMC_PHY_CFG1
id|CTL_SMC_PHY_CFG1
comma
singleline_comment|// PHY Configuration 1
DECL|enumerator|CTL_SMC_PHY_CFG2
id|CTL_SMC_PHY_CFG2
comma
singleline_comment|// PHY Configuration 2
DECL|enumerator|CTL_SMC_PHY_INT
id|CTL_SMC_PHY_INT
comma
singleline_comment|// PHY Interrupt/Status Output
DECL|enumerator|CTL_SMC_PHY_MASK
id|CTL_SMC_PHY_MASK
comma
singleline_comment|// PHY Interrupt/Status Mask
macro_line|#endif
singleline_comment|// ---------------------------------------------------
DECL|enumerator|CTL_SMC_LAST_ENTRY
id|CTL_SMC_LAST_ENTRY
singleline_comment|// Add new entries above the line
)brace
suffix:semicolon
macro_line|#endif 
singleline_comment|// CONFIG_SYSCTL
macro_line|#endif  /* _SMC_91111_H_ */
eof
