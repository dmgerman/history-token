multiline_comment|/*********************************************************************&n; *                &n; * Filename:      toshoboe.h&n; * Version:       2.16&n; * Description:   Driver for the Toshiba OBOE (or type-O or 701)&n; *                FIR Chipset, also supports the DONAUOBOE (type-DO&n; *                or d01) FIR chipset which as far as I know is&n; *                register compatible.&n; * Status:        Experimental.&n; * Author:        James McKenzie &lt;james@fishsoup.dhs.org&gt;&n; * Created at:    Sat May 8  12:35:27 1999&n; * Modified: 2.16 Martin Lucina &lt;mato@kotelna.sk&gt;&n; * Modified: 2.16 Sat Jun 22 18:54:29 2002 (sync headers)&n; * Modified: 2.17 Christian Gennerat &lt;christian.gennerat@polytechnique.org&gt;&n; * Modified: 2.17 jeu sep 12 08:50:20 2002 (add lock to be used by spinlocks)&n; * &n; *     Copyright (c) 1999 James McKenzie, All Rights Reserved.&n; *      &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; *  &n; *     Neither James McKenzie nor Cambridge University admit liability nor&n; *     provide warranty for any of this software. This material is &n; *     provided &quot;AS-IS&quot; and at no charge.&n; * &n; *     Applicable Models : Libretto 100/110CT and many more.&n; *     Toshiba refers to this chip as the type-O IR port,&n; *     or the type-DO IR port.&n; *&n; * IrDA chip set list from Toshiba Computer Engineering Corp.&n; * model&t;&t;&t;method&t;maker&t;controler&t;&t;Version &n; * Portege 320CT&t;FIR,SIR Toshiba Oboe(Triangle) &n; * Portege 3010CT&t;FIR,SIR Toshiba Oboe(Sydney) &n; * Portege 3015CT&t;FIR,SIR Toshiba Oboe(Sydney) &n; * Portege 3020CT&t;FIR,SIR Toshiba Oboe(Sydney) &n; * Portege 7020CT&t;FIR,SIR ?&t;&t;?&n; * &n; * Satell. 4090XCDT&t;FIR,SIR ?&t;&t;?&n; * &n; * Libretto 100CT&t;FIR,SIR Toshiba Oboe &n; * Libretto 1000CT&t;FIR,SIR Toshiba Oboe &n; * &n; * TECRA750DVD&t;&t;FIR,SIR Toshiba Oboe(Triangle)&t;REV ID=14h &n; * TECRA780&t;&t;&t;FIR,SIR Toshiba Oboe(Sandlot)&t;REV ID=32h,33h &n; * TECRA750CDT&t;&t;FIR,SIR Toshiba Oboe(Triangle)&t;REV ID=13h,14h &n; * TECRA8000&t;&t;FIR,SIR Toshiba Oboe(ISKUR)&t;&t;REV ID=23h &n; * &n; ********************************************************************/
multiline_comment|/* The documentation for this chip is allegedly released         */
multiline_comment|/* However I have not seen it, not have I managed to contact     */
multiline_comment|/* anyone who has. HOWEVER the chip bears a striking resemblence */
multiline_comment|/* to the IrDA controller in the Toshiba RISC TMPR3922 chip      */
multiline_comment|/* the documentation for this is freely available at             */
multiline_comment|/* http://www.toshiba.com/taec/components/Generic/TMPR3922.shtml */
multiline_comment|/* The mapping between the registers in that document and the    */
multiline_comment|/* Registers in the 701 oboe chip are as follows    */
multiline_comment|/* 3922 reg     701 regs, by bit numbers                        */
multiline_comment|/*               7- 0  15- 8  24-16  31-25                      */
multiline_comment|/* $28            0x0    0x1                                    */
multiline_comment|/* $2c                                     SEE NOTE 1           */
multiline_comment|/* $30            0x6    0x7                                    */
multiline_comment|/* $34            0x8    0x9               SEE NOTE 2           */
multiline_comment|/* $38           0x10   0x11                                    */
multiline_comment|/* $3C                   0xe               SEE NOTE 3           */
multiline_comment|/* $40           0x12   0x13                                    */
multiline_comment|/* $44           0x14   0x15                                    */
multiline_comment|/* $48           0x16   0x17                                    */
multiline_comment|/* $4c           0x18   0x19                                    */
multiline_comment|/* $50           0x1a   0x1b                                    */
multiline_comment|/* FIXME: could be 0x1b 0x1a here */
multiline_comment|/* $54           0x1d   0x1c                                    */
multiline_comment|/* $5C           0xf                       SEE NOTE 4           */
multiline_comment|/* $130                                    SEE NOTE 5           */
multiline_comment|/* $134                                    SEE NOTE 6           */
multiline_comment|/*                                                              */
multiline_comment|/* NOTES:                                                       */
multiline_comment|/* 1. The pointer to ring is packed in most unceremoniusly      */
multiline_comment|/*    701 Register      Address bits    (A9-A0 must be zero)    */
multiline_comment|/*            0x4:      A17 A16 A15 A14 A13 A12 A11 A10         */
multiline_comment|/*            0x5:      A25 A24 A23 A22 A21 A20 A19 A18         */
multiline_comment|/*            0x2:        0   0 A31 A30 A29 A28 A27 A26         */
multiline_comment|/*                                                              */
multiline_comment|/* 2. The M$ drivers do a write 0x1 to 0x9, however the 3922    */
multiline_comment|/*    documentation would suggest that a write of 0x1 to 0x8    */
multiline_comment|/*    would be more appropriate.                                */
multiline_comment|/*                                                              */
multiline_comment|/* 3. This assignment is tenuous at best, register 0xe seems to */
multiline_comment|/*    have bits arranged 0 0 0 R/W R/W R/W R/W R/W              */
multiline_comment|/*    if either of the lower two bits are set the chip seems to */
multiline_comment|/*    switch off                                                */
multiline_comment|/*                                                              */
multiline_comment|/* 4. Bits 7-4 seem to be different 4 seems just to be generic  */
multiline_comment|/*    receiver busy flag                                        */
multiline_comment|/*                                                              */
multiline_comment|/* 5. and 6. The IER and ISR have a different bit assignment    */
multiline_comment|/*    The lower three bits of both read back as ones            */
multiline_comment|/* ISR is register 0xc, IER is register 0xd                     */
multiline_comment|/*           7      6      5      4      3      2      1      0 */
multiline_comment|/* 0xc: TxDone RxDone TxUndr RxOver SipRcv      1      1      1 */
multiline_comment|/* 0xd: TxDone RxDone TxUndr RxOver SipRcv      1      1      1 */
multiline_comment|/* TxDone xmitt done (generated only if generate interrupt bit  */
multiline_comment|/*   is set in the ring)                                        */
multiline_comment|/* RxDone recv completed (or other recv condition if you set it */
multiline_comment|/*   up                                                         */
multiline_comment|/* TxUnder underflow in Transmit FIFO                           */
multiline_comment|/* RxOver  overflow in Recv FIFO                                */
multiline_comment|/* SipRcv  received serial gap  (or other condition you set)    */
multiline_comment|/* Interrupts are enabled by writing a one to the IER register  */
multiline_comment|/* Interrupts are cleared by writting a one to the ISR register */
multiline_comment|/*                                                              */
multiline_comment|/* 6. The remaining registers: 0x6 and 0x3 appear to be         */
multiline_comment|/*    reserved parts of 16 or 32 bit registersthe remainder     */
multiline_comment|/*    0xa 0xb 0x1e 0x1f could possibly be (by their behaviour)  */
multiline_comment|/*    the Unicast Filter register at $58.                       */
multiline_comment|/*                                                              */
multiline_comment|/* 7. While the core obviously expects 32 bit accesses all the  */
multiline_comment|/*    M$ drivers do 8 bit accesses, infact the Miniport ones    */
multiline_comment|/*    write and read back the byte serveral times (why?)        */
macro_line|#ifndef TOSHOBOE_H
DECL|macro|TOSHOBOE_H
mdefine_line|#define TOSHOBOE_H
multiline_comment|/* Registers */
DECL|macro|OBOE_IO_EXTENT
mdefine_line|#define OBOE_IO_EXTENT&t;0x1f
multiline_comment|/*Receive and transmit slot pointers */
DECL|macro|OBOE_REG
mdefine_line|#define OBOE_REG(i)&t;(i+(self-&gt;base))
DECL|macro|OBOE_RXSLOT
mdefine_line|#define OBOE_RXSLOT&t;OBOE_REG(0x0)
DECL|macro|OBOE_TXSLOT
mdefine_line|#define OBOE_TXSLOT&t;OBOE_REG(0x1)
DECL|macro|OBOE_SLOT_MASK
mdefine_line|#define OBOE_SLOT_MASK&t;0x3f
DECL|macro|OBOE_TXRING_OFFSET
mdefine_line|#define OBOE_TXRING_OFFSET&t;&t;0x200
DECL|macro|OBOE_TXRING_OFFSET_IN_SLOTS
mdefine_line|#define OBOE_TXRING_OFFSET_IN_SLOTS&t;0x40
multiline_comment|/*pointer to the ring */
DECL|macro|OBOE_RING_BASE0
mdefine_line|#define OBOE_RING_BASE0&t;OBOE_REG(0x4)
DECL|macro|OBOE_RING_BASE1
mdefine_line|#define OBOE_RING_BASE1&t;OBOE_REG(0x5)
DECL|macro|OBOE_RING_BASE2
mdefine_line|#define OBOE_RING_BASE2&t;OBOE_REG(0x2)
DECL|macro|OBOE_RING_BASE3
mdefine_line|#define OBOE_RING_BASE3&t;OBOE_REG(0x3)
multiline_comment|/*Number of slots in the ring */
DECL|macro|OBOE_RING_SIZE
mdefine_line|#define OBOE_RING_SIZE  OBOE_REG(0x7)
DECL|macro|OBOE_RING_SIZE_RX4
mdefine_line|#define OBOE_RING_SIZE_RX4&t;0x00
DECL|macro|OBOE_RING_SIZE_RX8
mdefine_line|#define OBOE_RING_SIZE_RX8&t;0x01
DECL|macro|OBOE_RING_SIZE_RX16
mdefine_line|#define OBOE_RING_SIZE_RX16&t;0x03
DECL|macro|OBOE_RING_SIZE_RX32
mdefine_line|#define OBOE_RING_SIZE_RX32&t;0x07
DECL|macro|OBOE_RING_SIZE_RX64
mdefine_line|#define OBOE_RING_SIZE_RX64&t;0x0f
DECL|macro|OBOE_RING_SIZE_TX4
mdefine_line|#define OBOE_RING_SIZE_TX4&t;0x00
DECL|macro|OBOE_RING_SIZE_TX8
mdefine_line|#define OBOE_RING_SIZE_TX8&t;0x10
DECL|macro|OBOE_RING_SIZE_TX16
mdefine_line|#define OBOE_RING_SIZE_TX16&t;0x30
DECL|macro|OBOE_RING_SIZE_TX32
mdefine_line|#define OBOE_RING_SIZE_TX32&t;0x70
DECL|macro|OBOE_RING_SIZE_TX64
mdefine_line|#define OBOE_RING_SIZE_TX64&t;0xf0
DECL|macro|OBOE_RING_MAX_SIZE
mdefine_line|#define OBOE_RING_MAX_SIZE&t;64
multiline_comment|/*Causes the gubbins to re-examine the ring */
DECL|macro|OBOE_PROMPT
mdefine_line|#define OBOE_PROMPT&t;OBOE_REG(0x9)
DECL|macro|OBOE_PROMPT_BIT
mdefine_line|#define OBOE_PROMPT_BIT&t;&t;0x1
multiline_comment|/* Interrupt Status Register */
DECL|macro|OBOE_ISR
mdefine_line|#define OBOE_ISR&t;OBOE_REG(0xc)
multiline_comment|/* Interrupt Enable Register */
DECL|macro|OBOE_IER
mdefine_line|#define OBOE_IER&t;OBOE_REG(0xd)
multiline_comment|/* Interrupt bits for IER and ISR */
DECL|macro|OBOE_INT_TXDONE
mdefine_line|#define OBOE_INT_TXDONE&t;&t;0x80
DECL|macro|OBOE_INT_RXDONE
mdefine_line|#define OBOE_INT_RXDONE&t;&t;0x40
DECL|macro|OBOE_INT_TXUNDER
mdefine_line|#define OBOE_INT_TXUNDER&t;0x20
DECL|macro|OBOE_INT_RXOVER
mdefine_line|#define OBOE_INT_RXOVER&t;&t;0x10
DECL|macro|OBOE_INT_SIP
mdefine_line|#define OBOE_INT_SIP&t;&t;0x08
DECL|macro|OBOE_INT_MASK
mdefine_line|#define OBOE_INT_MASK&t;&t;0xf8
multiline_comment|/*Reset Register */
DECL|macro|OBOE_CONFIG1
mdefine_line|#define OBOE_CONFIG1&t;OBOE_REG(0xe)
DECL|macro|OBOE_CONFIG1_RST
mdefine_line|#define OBOE_CONFIG1_RST&t;0x01
DECL|macro|OBOE_CONFIG1_DISABLE
mdefine_line|#define OBOE_CONFIG1_DISABLE&t;0x02
DECL|macro|OBOE_CONFIG1_4
mdefine_line|#define OBOE_CONFIG1_4&t;&t;0x08
DECL|macro|OBOE_CONFIG1_8
mdefine_line|#define OBOE_CONFIG1_8&t;&t;0x08
DECL|macro|OBOE_CONFIG1_ON
mdefine_line|#define OBOE_CONFIG1_ON&t;&t;0x8
DECL|macro|OBOE_CONFIG1_RESET
mdefine_line|#define OBOE_CONFIG1_RESET&t;0xf
DECL|macro|OBOE_CONFIG1_OFF
mdefine_line|#define OBOE_CONFIG1_OFF&t;0xe
DECL|macro|OBOE_STATUS
mdefine_line|#define OBOE_STATUS&t;OBOE_REG(0xf)
DECL|macro|OBOE_STATUS_RXBUSY
mdefine_line|#define OBOE_STATUS_RXBUSY&t;0x10
DECL|macro|OBOE_STATUS_FIRRX
mdefine_line|#define OBOE_STATUS_FIRRX&t;0x04
DECL|macro|OBOE_STATUS_MIRRX
mdefine_line|#define OBOE_STATUS_MIRRX&t;0x02
DECL|macro|OBOE_STATUS_SIRRX
mdefine_line|#define OBOE_STATUS_SIRRX&t;0x01
multiline_comment|/*Speed control registers */
DECL|macro|OBOE_CONFIG0L
mdefine_line|#define OBOE_CONFIG0L&t;OBOE_REG(0x10)
DECL|macro|OBOE_CONFIG0H
mdefine_line|#define OBOE_CONFIG0H&t;OBOE_REG(0x11)
DECL|macro|OBOE_CONFIG0H_TXONLOOP
mdefine_line|#define OBOE_CONFIG0H_TXONLOOP  0x80 /*Transmit when looping (dangerous) */
DECL|macro|OBOE_CONFIG0H_LOOP
mdefine_line|#define OBOE_CONFIG0H_LOOP&t;0x40 /*Loopback Tx-&gt;Rx */
DECL|macro|OBOE_CONFIG0H_ENTX
mdefine_line|#define OBOE_CONFIG0H_ENTX&t;0x10 /*Enable Tx */
DECL|macro|OBOE_CONFIG0H_ENRX
mdefine_line|#define OBOE_CONFIG0H_ENRX&t;0x08 /*Enable Rx */
DECL|macro|OBOE_CONFIG0H_ENDMAC
mdefine_line|#define OBOE_CONFIG0H_ENDMAC&t;0x04 /*Enable/reset* the DMA controller */
DECL|macro|OBOE_CONFIG0H_RCVANY
mdefine_line|#define OBOE_CONFIG0H_RCVANY&t;0x02 /*DMA mode 1=bytes, 0=dwords */
DECL|macro|OBOE_CONFIG0L_CRC16
mdefine_line|#define OBOE_CONFIG0L_CRC16&t;0x80 /*CRC 1=16 bit 0=32 bit */
DECL|macro|OBOE_CONFIG0L_ENFIR
mdefine_line|#define OBOE_CONFIG0L_ENFIR&t;0x40 /*Enable FIR */
DECL|macro|OBOE_CONFIG0L_ENMIR
mdefine_line|#define OBOE_CONFIG0L_ENMIR&t;0x20 /*Enable MIR */
DECL|macro|OBOE_CONFIG0L_ENSIR
mdefine_line|#define OBOE_CONFIG0L_ENSIR&t;0x10 /*Enable SIR */
DECL|macro|OBOE_CONFIG0L_ENSIRF
mdefine_line|#define OBOE_CONFIG0L_ENSIRF&t;0x08 /*Enable SIR framer */
DECL|macro|OBOE_CONFIG0L_SIRTEST
mdefine_line|#define OBOE_CONFIG0L_SIRTEST&t;0x04 /*Enable SIR framer in MIR and FIR */
DECL|macro|OBOE_CONFIG0L_INVERTTX
mdefine_line|#define OBOE_CONFIG0L_INVERTTX  0x02 /*Invert Tx Line */
DECL|macro|OBOE_CONFIG0L_INVERTRX
mdefine_line|#define OBOE_CONFIG0L_INVERTRX  0x01 /*Invert Rx Line */
DECL|macro|OBOE_BOF
mdefine_line|#define OBOE_BOF&t;OBOE_REG(0x12)
DECL|macro|OBOE_EOF
mdefine_line|#define OBOE_EOF&t;OBOE_REG(0x13)
DECL|macro|OBOE_ENABLEL
mdefine_line|#define OBOE_ENABLEL&t;OBOE_REG(0x14)
DECL|macro|OBOE_ENABLEH
mdefine_line|#define OBOE_ENABLEH&t;OBOE_REG(0x15)
DECL|macro|OBOE_ENABLEH_PHYANDCLOCK
mdefine_line|#define OBOE_ENABLEH_PHYANDCLOCK&t;0x80 /*Toggle low to copy config in */
DECL|macro|OBOE_ENABLEH_CONFIGERR
mdefine_line|#define OBOE_ENABLEH_CONFIGERR&t;&t;0x40
DECL|macro|OBOE_ENABLEH_FIRON
mdefine_line|#define OBOE_ENABLEH_FIRON&t;&t;0x20
DECL|macro|OBOE_ENABLEH_MIRON
mdefine_line|#define OBOE_ENABLEH_MIRON&t;&t;0x10
DECL|macro|OBOE_ENABLEH_SIRON
mdefine_line|#define OBOE_ENABLEH_SIRON&t;&t;0x08
DECL|macro|OBOE_ENABLEH_ENTX
mdefine_line|#define OBOE_ENABLEH_ENTX&t;&t;0x04
DECL|macro|OBOE_ENABLEH_ENRX
mdefine_line|#define OBOE_ENABLEH_ENRX&t;&t;0x02
DECL|macro|OBOE_ENABLEH_CRC16
mdefine_line|#define OBOE_ENABLEH_CRC16&t;&t;0x01
DECL|macro|OBOE_ENABLEL_BROADCAST
mdefine_line|#define OBOE_ENABLEL_BROADCAST&t;&t;0x01
DECL|macro|OBOE_CURR_PCONFIGL
mdefine_line|#define OBOE_CURR_PCONFIGL&t;&t;OBOE_REG(0x16) /*Current config */
DECL|macro|OBOE_CURR_PCONFIGH
mdefine_line|#define OBOE_CURR_PCONFIGH&t;&t;OBOE_REG(0x17)
DECL|macro|OBOE_NEW_PCONFIGL
mdefine_line|#define OBOE_NEW_PCONFIGL&t;&t;OBOE_REG(0x18)
DECL|macro|OBOE_NEW_PCONFIGH
mdefine_line|#define OBOE_NEW_PCONFIGH&t;&t;OBOE_REG(0x19)
DECL|macro|OBOE_PCONFIGH_BAUDMASK
mdefine_line|#define OBOE_PCONFIGH_BAUDMASK&t;&t;0xfc
DECL|macro|OBOE_PCONFIGH_WIDTHMASK
mdefine_line|#define OBOE_PCONFIGH_WIDTHMASK&t;&t;0x04
DECL|macro|OBOE_PCONFIGL_WIDTHMASK
mdefine_line|#define OBOE_PCONFIGL_WIDTHMASK&t;&t;0xe0
DECL|macro|OBOE_PCONFIGL_PREAMBLEMASK
mdefine_line|#define OBOE_PCONFIGL_PREAMBLEMASK&t;0x1f
DECL|macro|OBOE_PCONFIG_BAUDMASK
mdefine_line|#define OBOE_PCONFIG_BAUDMASK&t;&t;0xfc00
DECL|macro|OBOE_PCONFIG_BAUDSHIFT
mdefine_line|#define OBOE_PCONFIG_BAUDSHIFT&t;&t;10
DECL|macro|OBOE_PCONFIG_WIDTHMASK
mdefine_line|#define OBOE_PCONFIG_WIDTHMASK&t;&t;0x04e0
DECL|macro|OBOE_PCONFIG_WIDTHSHIFT
mdefine_line|#define OBOE_PCONFIG_WIDTHSHIFT&t;&t;5
DECL|macro|OBOE_PCONFIG_PREAMBLEMASK
mdefine_line|#define OBOE_PCONFIG_PREAMBLEMASK&t;0x001f
DECL|macro|OBOE_PCONFIG_PREAMBLESHIFT
mdefine_line|#define OBOE_PCONFIG_PREAMBLESHIFT&t;0
DECL|macro|OBOE_MAXLENL
mdefine_line|#define OBOE_MAXLENL&t;&t;&t;OBOE_REG(0x1a)
DECL|macro|OBOE_MAXLENH
mdefine_line|#define OBOE_MAXLENH&t;&t;&t;OBOE_REG(0x1b)
DECL|macro|OBOE_RXCOUNTH
mdefine_line|#define OBOE_RXCOUNTH&t;&t;&t;OBOE_REG(0x1c) /*Reset on recipt */
DECL|macro|OBOE_RXCOUNTL
mdefine_line|#define OBOE_RXCOUNTL&t;&t;&t;OBOE_REG(0x1d) /*of whole packet */
multiline_comment|/* The PCI ID of the OBOE chip */
macro_line|#ifndef PCI_DEVICE_ID_FIR701
DECL|macro|PCI_DEVICE_ID_FIR701
mdefine_line|#define PCI_DEVICE_ID_FIR701 &t;0x0701
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_FIRD01
DECL|macro|PCI_DEVICE_ID_FIRD01
mdefine_line|#define PCI_DEVICE_ID_FIRD01 &t;0x0d01
macro_line|#endif
DECL|struct|OboeSlot
r_struct
id|OboeSlot
(brace
DECL|member|len
id|__u16
id|len
suffix:semicolon
multiline_comment|/*Tweleve bits of packet length */
DECL|member|unused
id|__u8
id|unused
suffix:semicolon
DECL|member|control
id|__u8
id|control
suffix:semicolon
multiline_comment|/*Slot control/status see below */
DECL|member|address
id|__u32
id|address
suffix:semicolon
multiline_comment|/*Slot buffer address */
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|macro|OBOE_NTASKS
mdefine_line|#define OBOE_NTASKS OBOE_TXRING_OFFSET_IN_SLOTS
DECL|struct|OboeRing
r_struct
id|OboeRing
(brace
DECL|member|rx
r_struct
id|OboeSlot
id|rx
(braket
id|OBOE_NTASKS
)braket
suffix:semicolon
DECL|member|tx
r_struct
id|OboeSlot
id|tx
(braket
id|OBOE_NTASKS
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|OBOE_RING_LEN
mdefine_line|#define OBOE_RING_LEN (sizeof(struct OboeRing))
DECL|macro|OBOE_CTL_TX_HW_OWNS
mdefine_line|#define OBOE_CTL_TX_HW_OWNS&t;0x80 /*W/R This slot owned by the hardware */
DECL|macro|OBOE_CTL_TX_DISTX_CRC
mdefine_line|#define OBOE_CTL_TX_DISTX_CRC&t;0x40 /*W Disable CRC generation for [FM]IR */
DECL|macro|OBOE_CTL_TX_BAD_CRC
mdefine_line|#define OBOE_CTL_TX_BAD_CRC     0x20 /*W Generate bad CRC */
DECL|macro|OBOE_CTL_TX_SIP
mdefine_line|#define OBOE_CTL_TX_SIP&t;&t;0x10   /*W Generate an SIP after xmittion */
DECL|macro|OBOE_CTL_TX_MKUNDER
mdefine_line|#define OBOE_CTL_TX_MKUNDER&t;0x08 /*W Generate an underrun error */
DECL|macro|OBOE_CTL_TX_RTCENTX
mdefine_line|#define OBOE_CTL_TX_RTCENTX&t;0x04 /*W Enable receiver and generate TXdone */
multiline_comment|/*  After this slot is processed        */
DECL|macro|OBOE_CTL_TX_UNDER
mdefine_line|#define OBOE_CTL_TX_UNDER&t;0x01  /*R Set by hardware to indicate underrun */
DECL|macro|OBOE_CTL_RX_HW_OWNS
mdefine_line|#define OBOE_CTL_RX_HW_OWNS&t;0x80 /*W/R This slot owned by hardware */
DECL|macro|OBOE_CTL_RX_PHYERR
mdefine_line|#define OBOE_CTL_RX_PHYERR&t;0x40 /*R Decoder error on receiption */
DECL|macro|OBOE_CTL_RX_CRCERR
mdefine_line|#define OBOE_CTL_RX_CRCERR&t;0x20 /*R CRC error only set for [FM]IR */
DECL|macro|OBOE_CTL_RX_LENGTH
mdefine_line|#define OBOE_CTL_RX_LENGTH&t;0x10 /*R Packet &gt; max Rx length  */
DECL|macro|OBOE_CTL_RX_OVER
mdefine_line|#define OBOE_CTL_RX_OVER&t;0x08   /*R set to indicate an overflow */
DECL|macro|OBOE_CTL_RX_SIRBAD
mdefine_line|#define OBOE_CTL_RX_SIRBAD&t;0x04 /*R SIR had BOF in packet or ABORT sequence */
DECL|macro|OBOE_CTL_RX_RXEOF
mdefine_line|#define OBOE_CTL_RX_RXEOF&t;0x02  /*R Finished receiving on this slot */
DECL|struct|toshoboe_cb
r_struct
id|toshoboe_cb
(brace
DECL|member|netdev
r_struct
id|net_device
op_star
id|netdev
suffix:semicolon
multiline_comment|/* Yes! we are some kind of netdevice */
DECL|member|stats
r_struct
id|net_device_stats
id|stats
suffix:semicolon
DECL|member|ttydev
r_struct
id|tty_driver
id|ttydev
suffix:semicolon
DECL|member|irlap
r_struct
id|irlap_cb
op_star
id|irlap
suffix:semicolon
multiline_comment|/* The link layer we are binded to */
DECL|member|io
id|chipio_t
id|io
suffix:semicolon
multiline_comment|/* IrDA controller information */
DECL|member|qos
r_struct
id|qos_info
id|qos
suffix:semicolon
multiline_comment|/* QoS capabilities for this device */
DECL|member|flags
id|__u32
id|flags
suffix:semicolon
multiline_comment|/* Interface flags */
DECL|member|pdev
r_struct
id|pci_dev
op_star
id|pdev
suffix:semicolon
multiline_comment|/*PCI device */
DECL|member|base
r_int
id|base
suffix:semicolon
multiline_comment|/*IO base */
DECL|member|txpending
r_int
id|txpending
suffix:semicolon
multiline_comment|/*how many tx&squot;s are pending */
DECL|member|txs
DECL|member|rxs
r_int
id|txs
comma
id|rxs
suffix:semicolon
multiline_comment|/*Which slots are we at  */
DECL|member|irdad
r_int
id|irdad
suffix:semicolon
multiline_comment|/*Driver under control of netdev end  */
DECL|member|async
r_int
id|async
suffix:semicolon
multiline_comment|/*Driver under control of async end   */
DECL|member|stopped
r_int
id|stopped
suffix:semicolon
multiline_comment|/*Stopped by some or other APM stuff */
DECL|member|filter
r_int
id|filter
suffix:semicolon
multiline_comment|/*In SIR mode do we want to receive&n;                                   frames or byte ranges */
DECL|member|ringbuf
r_void
op_star
id|ringbuf
suffix:semicolon
multiline_comment|/*The ring buffer */
DECL|member|ring
r_struct
id|OboeRing
op_star
id|ring
suffix:semicolon
multiline_comment|/*The ring */
DECL|member|tx_bufs
r_void
op_star
id|tx_bufs
(braket
id|OBOE_RING_MAX_SIZE
)braket
suffix:semicolon
multiline_comment|/*The buffers   */
DECL|member|rx_bufs
r_void
op_star
id|rx_bufs
(braket
id|OBOE_RING_MAX_SIZE
)braket
suffix:semicolon
DECL|member|speed
r_int
id|speed
suffix:semicolon
multiline_comment|/*Current setting of the speed */
DECL|member|new_speed
r_int
id|new_speed
suffix:semicolon
multiline_comment|/*Set to request a speed change */
multiline_comment|/* The spinlock protect critical parts of the driver.&n; *&t;Locking is done like this :&n; *&t;&t;spin_lock_irqsave(&amp;self-&gt;spinlock, flags);&n; *&t;Releasing the lock :&n; *&t;&t;spin_unlock_irqrestore(&amp;self-&gt;spinlock, flags);&n; */
DECL|member|spinlock
id|spinlock_t
id|spinlock
suffix:semicolon
multiline_comment|/* Used for the probe and diagnostics code */
DECL|member|int_rx
r_int
id|int_rx
suffix:semicolon
DECL|member|int_tx
r_int
id|int_tx
suffix:semicolon
DECL|member|int_txunder
r_int
id|int_txunder
suffix:semicolon
DECL|member|int_rxover
r_int
id|int_rxover
suffix:semicolon
DECL|member|int_sip
r_int
id|int_sip
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
