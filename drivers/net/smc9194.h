multiline_comment|/*------------------------------------------------------------------------&n; . smc9194.h&n; . Copyright (C) 1996 by Erik Stahlman &n; .&n; . This software may be used and distributed according to the terms&n; . of the GNU Public License, incorporated herein by reference.&n; .&n; . This file contains register information and access macros for &n; . the SMC91xxx chipset.   &n; . &n; . Information contained in this file was obtained from the SMC91C94 &n; . manual from SMC.  To get a copy, if you really want one, you can find &n; . information under www.smc.com in the components division.&n; . ( this thanks to advice from Donald Becker ).&n; . &n; . Authors&n; . &t;Erik Stahlman&t;&t;&t;&t;( erik@vt.edu )&n; .&n; . History&n; . 01/06/96&t;&t; Erik Stahlman   moved definitions here from main .c file&n; . 01/19/96&t;&t; Erik Stahlman&t;  polished this up some, and added better&n; .&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;  error handling&n; .&n; ---------------------------------------------------------------------------*/
macro_line|#ifndef _SMC9194_H_
DECL|macro|_SMC9194_H_
mdefine_line|#define _SMC9194_H_
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
multiline_comment|/* Because of bank switching, the SMC91xxx uses only 16 I/O ports */
DECL|macro|SMC_IO_EXTENT
mdefine_line|#define SMC_IO_EXTENT&t;16
multiline_comment|/*---------------------------------------------------------------&n; .  &n; . A description of the SMC registers is probably in order here,&n; . although for details, the SMC datasheet is invaluable.  &n; . &n; . Basically, the chip has 4 banks of registers ( 0 to 3 ), which&n; . are accessed by writing a number into the BANK_SELECT register&n; . ( I also use a SMC_SELECT_BANK macro for this ).&n; . &n; . The banks are configured so that for most purposes, bank 2 is all&n; . that is needed for simple run time tasks.  &n; -----------------------------------------------------------------------*/
multiline_comment|/*&n; . Bank Select Register: &n; .&n; .&t;&t;yyyy yyyy 0000 00xx  &n; .&t;&t;xx &t;&t;= bank number&n; .&t;&t;yyyy yyyy&t;= 0x33, for identification purposes.&n;*/
DECL|macro|BANK_SELECT
mdefine_line|#define&t;BANK_SELECT&t;&t;14
multiline_comment|/* BANK 0  */
DECL|macro|TCR
mdefine_line|#define&t;TCR &t;&t;0    &t;/* transmit control register */
DECL|macro|TCR_ENABLE
mdefine_line|#define TCR_ENABLE&t;0x0001&t;/* if this is 1, we can transmit */ 
DECL|macro|TCR_FDUPLX
mdefine_line|#define TCR_FDUPLX    &t;0x0800  /* receive packets sent out */
DECL|macro|TCR_STP_SQET
mdefine_line|#define TCR_STP_SQET&t;0x1000&t;/* stop transmitting if Signal quality error */
DECL|macro|TCR_MON_CNS
mdefine_line|#define&t;TCR_MON_CNS&t;0x0400&t;/* monitors the carrier status */
DECL|macro|TCR_PAD_ENABLE
mdefine_line|#define&t;TCR_PAD_ENABLE&t;0x0080&t;/* pads short packets to 64 bytes */
DECL|macro|TCR_CLEAR
mdefine_line|#define&t;TCR_CLEAR&t;0&t;/* do NOTHING */
multiline_comment|/* the normal settings for the TCR register : */
multiline_comment|/* QUESTION: do I want to enable padding of short packets ? */
DECL|macro|TCR_NORMAL
mdefine_line|#define&t;TCR_NORMAL  &t;TCR_ENABLE 
DECL|macro|EPH_STATUS
mdefine_line|#define EPH_STATUS&t;2
DECL|macro|ES_LINK_OK
mdefine_line|#define ES_LINK_OK&t;0x4000&t;/* is the link integrity ok ? */
DECL|macro|RCR
mdefine_line|#define&t;RCR&t;&t;4
DECL|macro|RCR_SOFTRESET
mdefine_line|#define RCR_SOFTRESET&t;0x8000 &t;/* resets the chip */&t;
DECL|macro|RCR_STRIP_CRC
mdefine_line|#define&t;RCR_STRIP_CRC&t;0x200&t;/* strips CRC */
DECL|macro|RCR_ENABLE
mdefine_line|#define RCR_ENABLE&t;0x100&t;/* IFF this is set, we can receive packets */
DECL|macro|RCR_ALMUL
mdefine_line|#define RCR_ALMUL&t;0x4 &t;/* receive all multicast packets */
DECL|macro|RCR_PROMISC
mdefine_line|#define&t;RCR_PROMISC&t;0x2&t;/* enable promiscuous mode */
multiline_comment|/* the normal settings for the RCR register : */
DECL|macro|RCR_NORMAL
mdefine_line|#define&t;RCR_NORMAL&t;(RCR_STRIP_CRC | RCR_ENABLE)
DECL|macro|RCR_CLEAR
mdefine_line|#define RCR_CLEAR&t;0x0&t;&t;/* set it to a base state */
DECL|macro|COUNTER
mdefine_line|#define&t;COUNTER&t;&t;6
DECL|macro|MIR
mdefine_line|#define&t;MIR&t;&t;8
DECL|macro|MCR
mdefine_line|#define&t;MCR&t;&t;10
multiline_comment|/* 12 is reserved */
multiline_comment|/* BANK 1 */
DECL|macro|CONFIG
mdefine_line|#define CONFIG&t;&t;&t;0
DECL|macro|CFG_AUI_SELECT
mdefine_line|#define CFG_AUI_SELECT&t; &t;0x100
DECL|macro|BASE
mdefine_line|#define&t;BASE&t;&t;&t;2
DECL|macro|ADDR0
mdefine_line|#define&t;ADDR0&t;&t;&t;4
DECL|macro|ADDR1
mdefine_line|#define&t;ADDR1&t;&t;&t;6
DECL|macro|ADDR2
mdefine_line|#define&t;ADDR2&t;&t;&t;8
DECL|macro|GENERAL
mdefine_line|#define&t;GENERAL&t;&t;&t;10
DECL|macro|CONTROL
mdefine_line|#define&t;CONTROL&t;&t;&t;12
DECL|macro|CTL_POWERDOWN
mdefine_line|#define&t;CTL_POWERDOWN&t;&t;0x2000
DECL|macro|CTL_LE_ENABLE
mdefine_line|#define&t;CTL_LE_ENABLE&t;&t;0x80
DECL|macro|CTL_CR_ENABLE
mdefine_line|#define&t;CTL_CR_ENABLE&t;&t;0x40
DECL|macro|CTL_TE_ENABLE
mdefine_line|#define&t;CTL_TE_ENABLE&t;&t;0x0020
DECL|macro|CTL_AUTO_RELEASE
mdefine_line|#define CTL_AUTO_RELEASE&t;0x0800
DECL|macro|CTL_EPROM_ACCESS
mdefine_line|#define&t;CTL_EPROM_ACCESS&t;0x0003 /* high if Eprom is being read */
multiline_comment|/* BANK 2 */
DECL|macro|MMU_CMD
mdefine_line|#define MMU_CMD&t;&t;0
DECL|macro|MC_BUSY
mdefine_line|#define MC_BUSY&t;&t;1&t;/* only readable bit in the register */
DECL|macro|MC_NOP
mdefine_line|#define MC_NOP&t;&t;0
DECL|macro|MC_ALLOC
mdefine_line|#define&t;MC_ALLOC&t;0x20  &t;/* or with number of 256 byte packets */
DECL|macro|MC_RESET
mdefine_line|#define&t;MC_RESET&t;0x40&t;
DECL|macro|MC_REMOVE
mdefine_line|#define&t;MC_REMOVE&t;0x60  &t;/* remove the current rx packet */
DECL|macro|MC_RELEASE
mdefine_line|#define MC_RELEASE  &t;0x80  &t;/* remove and release the current rx packet */
DECL|macro|MC_FREEPKT
mdefine_line|#define MC_FREEPKT  &t;0xA0  &t;/* Release packet in PNR register */
DECL|macro|MC_ENQUEUE
mdefine_line|#define MC_ENQUEUE&t;0xC0 &t;/* Enqueue the packet for transmit */
DECL|macro|PNR_ARR
mdefine_line|#define&t;PNR_ARR&t;&t;2
DECL|macro|FIFO_PORTS
mdefine_line|#define FIFO_PORTS&t;4
DECL|macro|FP_RXEMPTY
mdefine_line|#define FP_RXEMPTY  0x8000
DECL|macro|FP_TXEMPTY
mdefine_line|#define FP_TXEMPTY  0x80
DECL|macro|POINTER
mdefine_line|#define&t;POINTER&t;&t;6
DECL|macro|PTR_READ
mdefine_line|#define PTR_READ&t;0x2000
DECL|macro|PTR_RCV
mdefine_line|#define&t;PTR_RCV&t;&t;0x8000
DECL|macro|PTR_AUTOINC
mdefine_line|#define&t;PTR_AUTOINC &t;0x4000
DECL|macro|PTR_AUTO_INC
mdefine_line|#define PTR_AUTO_INC&t;0x0040
DECL|macro|DATA_1
mdefine_line|#define&t;DATA_1&t;&t;8
DECL|macro|DATA_2
mdefine_line|#define&t;DATA_2&t;&t;10
DECL|macro|INTERRUPT
mdefine_line|#define&t;INTERRUPT&t;12
DECL|macro|INT_MASK
mdefine_line|#define INT_MASK&t;13
DECL|macro|IM_RCV_INT
mdefine_line|#define IM_RCV_INT&t;0x1
DECL|macro|IM_TX_INT
mdefine_line|#define&t;IM_TX_INT&t;0x2
DECL|macro|IM_TX_EMPTY_INT
mdefine_line|#define&t;IM_TX_EMPTY_INT&t;0x4&t;
DECL|macro|IM_ALLOC_INT
mdefine_line|#define&t;IM_ALLOC_INT&t;0x8
DECL|macro|IM_RX_OVRN_INT
mdefine_line|#define&t;IM_RX_OVRN_INT&t;0x10
DECL|macro|IM_EPH_INT
mdefine_line|#define&t;IM_EPH_INT&t;0x20
DECL|macro|IM_ERCV_INT
mdefine_line|#define&t;IM_ERCV_INT&t;0x40 /* not on SMC9192 */&t;&t;
multiline_comment|/* BANK 3 */
DECL|macro|MULTICAST1
mdefine_line|#define&t;MULTICAST1&t;0
DECL|macro|MULTICAST2
mdefine_line|#define&t;MULTICAST2&t;2
DECL|macro|MULTICAST3
mdefine_line|#define&t;MULTICAST3&t;4
DECL|macro|MULTICAST4
mdefine_line|#define&t;MULTICAST4&t;6
DECL|macro|MGMT
mdefine_line|#define&t;MGMT&t;&t;8
DECL|macro|REVISION
mdefine_line|#define&t;REVISION&t;10 /* ( hi: chip id   low: rev # ) */
multiline_comment|/* this is NOT on SMC9192 */
DECL|macro|ERCV
mdefine_line|#define&t;ERCV&t;&t;12
DECL|macro|CHIP_9190
mdefine_line|#define CHIP_9190&t;3
DECL|macro|CHIP_9194
mdefine_line|#define CHIP_9194&t;4
DECL|macro|CHIP_9195
mdefine_line|#define CHIP_9195&t;5
DECL|macro|CHIP_91100
mdefine_line|#define CHIP_91100&t;7
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
l_int|NULL
comma
multiline_comment|/* 7 */
l_string|&quot;SMC91C100&quot;
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
comma
l_int|NULL
comma
l_int|NULL
)brace
suffix:semicolon
multiline_comment|/* &n; . Transmit status bits &n;*/
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
DECL|macro|RS_BADCRC
mdefine_line|#define RS_BADCRC&t;0x2000
DECL|macro|RS_ODDFRAME
mdefine_line|#define RS_ODDFRAME&t;0x1000
DECL|macro|RS_TOOLONG
mdefine_line|#define RS_TOOLONG&t;0x0800
DECL|macro|RS_TOOSHORT
mdefine_line|#define RS_TOOSHORT&t;0x0400
DECL|macro|RS_MULTICAST
mdefine_line|#define RS_MULTICAST&t;0x0001
DECL|macro|RS_ERRORS
mdefine_line|#define RS_ERRORS&t;(RS_ALGNERR | RS_BADCRC | RS_TOOLONG | RS_TOOSHORT) 
DECL|variable|interfaces
r_static
r_const
r_char
op_star
id|interfaces
(braket
l_int|2
)braket
op_assign
(brace
l_string|&quot;TP&quot;
comma
l_string|&quot;AUI&quot;
)brace
suffix:semicolon
multiline_comment|/*-------------------------------------------------------------------------&n; .  I define some macros to make it easier to do somewhat common&n; . or slightly complicated, repeated tasks. &n; --------------------------------------------------------------------------*/
multiline_comment|/* select a register bank, 0 to 3  */
DECL|macro|SMC_SELECT_BANK
mdefine_line|#define SMC_SELECT_BANK(x)  { outw( x, ioaddr + BANK_SELECT ); } 
multiline_comment|/* define a small delay for the reset */
DECL|macro|SMC_DELAY
mdefine_line|#define SMC_DELAY() { inw( ioaddr + RCR );&bslash;&n;&t;&t;&t;inw( ioaddr + RCR );&bslash;&n;&t;&t;&t;inw( ioaddr + RCR );  }
multiline_comment|/* this enables an interrupt in the interrupt mask register */
DECL|macro|SMC_ENABLE_INT
mdefine_line|#define SMC_ENABLE_INT(x) {&bslash;&n;&t;&t;unsigned char mask;&bslash;&n;&t;&t;SMC_SELECT_BANK(2);&bslash;&n;&t;&t;mask = inb( ioaddr + INT_MASK );&bslash;&n;&t;&t;mask |= (x);&bslash;&n;&t;&t;outb( mask, ioaddr + INT_MASK ); &bslash;&n;}
multiline_comment|/* this disables an interrupt from the interrupt mask register */
DECL|macro|SMC_DISABLE_INT
mdefine_line|#define SMC_DISABLE_INT(x) {&bslash;&n;&t;&t;unsigned char mask;&bslash;&n;&t;&t;SMC_SELECT_BANK(2);&bslash;&n;&t;&t;mask = inb( ioaddr + INT_MASK );&bslash;&n;&t;&t;mask &amp;= ~(x);&bslash;&n;&t;&t;outb( mask, ioaddr + INT_MASK ); &bslash;&n;}
multiline_comment|/*----------------------------------------------------------------------&n; . Define the interrupts that I want to receive from the card&n; . &n; . I want: &n; .  IM_EPH_INT, for nasty errors&n; .  IM_RCV_INT, for happy received packets&n; .  IM_RX_OVRN_INT, because I have to kick the receiver&n; --------------------------------------------------------------------------*/
DECL|macro|SMC_INTERRUPT_MASK
mdefine_line|#define SMC_INTERRUPT_MASK   (IM_EPH_INT | IM_RX_OVRN_INT | IM_RCV_INT) 
macro_line|#endif  /* _SMC_9194_H_ */
eof
