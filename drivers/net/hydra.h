multiline_comment|/*&t;$Linux: hydra.h,v 1.0 1994/10/26 02:03:47 cgd Exp $&t;*/
multiline_comment|/*&n; * Copyright (c) 1994 Timo Rossi&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions and the following disclaimer.&n; * 2. Redistributions in binary form must reproduce the above copyright&n; *    notice, this list of conditions and the following disclaimer in the&n; *    documentation and/or other materials provided with the distribution.&n; * 3. All advertising materials mentioning features or use of this software&n; *    must display the following acknowledgement:&n; *      This product includes software developed by  Timo Rossi&n; * 4. The name of the author may not be used to endorse or promote products&n; *    derived from this software without specific prior written permission&n; *&n; * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS&squot;&squot; AND ANY EXPRESS OR&n; * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES&n; * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.&n; * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,&n; * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,&n; * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY&n; * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT&n; * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; */
multiline_comment|/*&n; * The Hydra Systems card uses the National Semiconductor&n; * 8390 NIC (Network Interface Controller) chip, located&n; * at card base address + 0xffe1. NIC registers are accessible&n; * only at odd byte addresses, so the register offsets must&n; * be multiplied by two.&n; *&n; * Card address PROM is located at card base + 0xffc0 (even byte addresses)&n; *&n; * RAM starts at the card base address, and is 16K or 64K.&n; * The current Amiga NetBSD hydra driver is hardwired for 16K.&n; * It seems that the RAM should be accessed as words or longwords only.&n; *&n; */
multiline_comment|/* adapted for Linux by Topi Kanerva 03/29/95&n;   with original author&squot;s permission          */
DECL|macro|HYDRA_NIC_BASE
mdefine_line|#define HYDRA_NIC_BASE 0xffe1
multiline_comment|/* Page0 registers */
DECL|macro|NIC_CR
mdefine_line|#define NIC_CR     0       /* Command register   */
DECL|macro|NIC_PSTART
mdefine_line|#define NIC_PSTART (1*2)   /* Page start (write) */
DECL|macro|NIC_PSTOP
mdefine_line|#define NIC_PSTOP  (2*2)   /* Page stop (write)  */
DECL|macro|NIC_BNDRY
mdefine_line|#define NIC_BNDRY  (3*2)   /* Boundary pointer   */
DECL|macro|NIC_TSR
mdefine_line|#define NIC_TSR    (4*2)   /* Transmit status (read) */
DECL|macro|NIC_TPSR
mdefine_line|#define NIC_TPSR   (4*2)   /* Transmit page start (write) */
DECL|macro|NIC_NCR
mdefine_line|#define NIC_NCR    (5*2)   /* Number of collisions, read  */
DECL|macro|NIC_TBCR0
mdefine_line|#define NIC_TBCR0  (5*2)   /* Transmit byte count low (write)  */
DECL|macro|NIC_FIFO
mdefine_line|#define NIC_FIFO   (6*2)   /* FIFO reg. (read)   */
DECL|macro|NIC_TBCR1
mdefine_line|#define NIC_TBCR1  (6*2)   /* Transmit byte count high (write) */
DECL|macro|NIC_ISR
mdefine_line|#define NIC_ISR    (7*2)   /* Interrupt status register */
DECL|macro|NIC_RBCR0
mdefine_line|#define NIC_RBCR0  (0xa*2) /* Remote byte count low (write)  */
DECL|macro|NIC_RBCR1
mdefine_line|#define NIC_RBCR1  (0xb*2) /* Remote byte count high (write) */
DECL|macro|NIC_RSR
mdefine_line|#define NIC_RSR    (0xc*2) /* Receive status (read)  */
DECL|macro|NIC_RCR
mdefine_line|#define NIC_RCR    (0xc*2) /* Receive config (write) */
DECL|macro|NIC_CNTR0
mdefine_line|#define NIC_CNTR0  (0xd*2) /* Frame alignment error count (read) */
DECL|macro|NIC_TCR
mdefine_line|#define NIC_TCR    (0xd*2) /* Transmit config (write)  */
DECL|macro|NIC_CNTR1
mdefine_line|#define NIC_CNTR1  (0xe*2) /* CRC error counter (read) */
DECL|macro|NIC_DCR
mdefine_line|#define NIC_DCR    (0xe*2) /* Data config (write) */
DECL|macro|NIC_CNTR2
mdefine_line|#define NIC_CNTR2  (0xf*2) /* missed packet counter (read) */
DECL|macro|NIC_IMR
mdefine_line|#define NIC_IMR    (0xf*2) /* Interrupt mask reg. (write)  */
multiline_comment|/* Page1 registers */
DECL|macro|NIC_PAR0
mdefine_line|#define NIC_PAR0   (1*2)   /* Physical address */
DECL|macro|NIC_PAR1
mdefine_line|#define NIC_PAR1   (2*2)
DECL|macro|NIC_PAR2
mdefine_line|#define NIC_PAR2   (3*2)
DECL|macro|NIC_PAR3
mdefine_line|#define NIC_PAR3   (4*2)
DECL|macro|NIC_PAR4
mdefine_line|#define NIC_PAR4   (5*2)
DECL|macro|NIC_PAR5
mdefine_line|#define NIC_PAR5   (6*2)
DECL|macro|NIC_CURR
mdefine_line|#define NIC_CURR   (7*2)   /* Current RX ring-buffer page */
DECL|macro|NIC_MAR0
mdefine_line|#define NIC_MAR0   (8*2)   /* Multicast address */
DECL|macro|NIC_MAR1
mdefine_line|#define NIC_MAR1   (9*2)
DECL|macro|NIC_MAR2
mdefine_line|#define NIC_MAR2   (0xa*2)
DECL|macro|NIC_MAR3
mdefine_line|#define NIC_MAR3   (0xb*2)
DECL|macro|NIC_MAR4
mdefine_line|#define NIC_MAR4   (0xc*2)
DECL|macro|NIC_MAR5
mdefine_line|#define NIC_MAR5   (0xd*2)
DECL|macro|NIC_MAR6
mdefine_line|#define NIC_MAR6   (0xe*2)
DECL|macro|NIC_MAR7
mdefine_line|#define NIC_MAR7   (0xf*2)
multiline_comment|/* Command register definitions */
DECL|macro|CR_STOP
mdefine_line|#define CR_STOP   0x01 /* Stop -- software reset command */
DECL|macro|CR_START
mdefine_line|#define CR_START  0x02 /* Start */
DECL|macro|CR_TXP
mdefine_line|#define CR_TXP   0x04 /* Transmit packet */
DECL|macro|CR_RD0
mdefine_line|#define CR_RD0    0x08 /* Remote DMA cmd */
DECL|macro|CR_RD1
mdefine_line|#define CR_RD1    0x10
DECL|macro|CR_RD2
mdefine_line|#define CR_RD2    0x20
DECL|macro|CR_NODMA
mdefine_line|#define CR_NODMA  CR_RD2
DECL|macro|CR_PS0
mdefine_line|#define CR_PS0    0x40 /* Page select */
DECL|macro|CR_PS1
mdefine_line|#define CR_PS1    0x80
DECL|macro|CR_PAGE0
mdefine_line|#define CR_PAGE0  0
DECL|macro|CR_PAGE1
mdefine_line|#define CR_PAGE1  CR_PS0
DECL|macro|CR_PAGE2
mdefine_line|#define CR_PAGE2  CR_PS1
multiline_comment|/* Interrupt status reg. definitions */
DECL|macro|ISR_PRX
mdefine_line|#define ISR_PRX   0x01 /* Packet received without errors */
DECL|macro|ISR_PTX
mdefine_line|#define ISR_PTX   0x02 /* Packet transmitted without errors */
DECL|macro|ISR_RXE
mdefine_line|#define ISR_RXE   0x04 /* Receive error  */
DECL|macro|ISR_TXE
mdefine_line|#define ISR_TXE   0x08 /* Transmit error */
DECL|macro|ISR_OVW
mdefine_line|#define ISR_OVW   0x10 /* Ring buffer overrun */
DECL|macro|ISR_CNT
mdefine_line|#define ISR_CNT   0x20 /* Counter overflow    */
DECL|macro|ISR_RDC
mdefine_line|#define ISR_RDC   0x40 /* Remote DMA compile */
DECL|macro|ISR_RST
mdefine_line|#define ISR_RST   0x80 /* Reset status      */
multiline_comment|/* Data config reg. definitions */
DECL|macro|DCR_WTS
mdefine_line|#define DCR_WTS   0x01 /* Word transfer select  */
DECL|macro|DCR_BOS
mdefine_line|#define DCR_BOS   0x02 /* Byte order select     */
DECL|macro|DCR_LAS
mdefine_line|#define DCR_LAS   0x04 /* Long address select   */
DECL|macro|DCR_LS
mdefine_line|#define DCR_LS    0x08 /* Loopback select       */
DECL|macro|DCR_AR
mdefine_line|#define DCR_AR    0x10 /* Auto-init remote      */
DECL|macro|DCR_FT0
mdefine_line|#define DCR_FT0   0x20 /* FIFO threshold select */
DECL|macro|DCR_FT1
mdefine_line|#define DCR_FT1   0x40
multiline_comment|/* Transmit config reg. definitions */
DECL|macro|TCR_CRC
mdefine_line|#define TCR_CRC  0x01 /* Inhibit CRC */
DECL|macro|TCR_LB0
mdefine_line|#define TCR_LB0  0x02 /* Loopback control */
DECL|macro|TCR_LB1
mdefine_line|#define TCR_LB1  0x04
DECL|macro|TCR_ATD
mdefine_line|#define TCR_ATD  0x08 /* Auto transmit disable */
DECL|macro|TCR_OFST
mdefine_line|#define TCR_OFST 0x10 /* Collision offset enable */
multiline_comment|/* Transmit status reg. definitions */
DECL|macro|TSR_PTX
mdefine_line|#define TSR_PTX  0x01 /* Packet transmitted */
DECL|macro|TSR_COL
mdefine_line|#define TSR_COL  0x04 /* Transmit collided */
DECL|macro|TSR_ABT
mdefine_line|#define TSR_ABT  0x08 /* Transmit aborted */
DECL|macro|TSR_CRS
mdefine_line|#define TSR_CRS  0x10 /* Carrier sense lost */
DECL|macro|TSR_FU
mdefine_line|#define TSR_FU   0x20 /* FIFO underrun */
DECL|macro|TSR_CDH
mdefine_line|#define TSR_CDH  0x40 /* CD Heartbeat */
DECL|macro|TSR_OWC
mdefine_line|#define TSR_OWC  0x80 /* Out of Window Collision */
multiline_comment|/* Receiver config register definitions */
DECL|macro|RCR_SEP
mdefine_line|#define RCR_SEP  0x01 /* Save errored packets */
DECL|macro|RCR_AR
mdefine_line|#define RCR_AR   0x02 /* Accept runt packets */
DECL|macro|RCR_AB
mdefine_line|#define RCR_AB   0x04 /* Accept broadcast */
DECL|macro|RCR_AM
mdefine_line|#define RCR_AM   0x08 /* Accept multicast */
DECL|macro|RCR_PRO
mdefine_line|#define RCR_PRO  0x10 /* Promiscuous mode */
DECL|macro|RCR_MON
mdefine_line|#define RCR_MON  0x20 /* Monitor mode */
multiline_comment|/* Receiver status register definitions */
DECL|macro|RSR_PRX
mdefine_line|#define RSR_PRX  0x01 /* Packet received without error */
DECL|macro|RSR_CRC
mdefine_line|#define RSR_CRC  0x02 /* CRC error */
DECL|macro|RSR_FAE
mdefine_line|#define RSR_FAE  0x04 /* Frame alignment error */
DECL|macro|RSR_FO
mdefine_line|#define RSR_FO   0x08 /* FIFO overrun */
DECL|macro|RSR_MPA
mdefine_line|#define RSR_MPA  0x10 /* Missed packet */
DECL|macro|RSR_PHY
mdefine_line|#define RSR_PHY  0x20 /* Physical address */
DECL|macro|RSR_DIS
mdefine_line|#define RSR_DIS  0x40 /* Received disabled */
DECL|macro|RSR_DFR
mdefine_line|#define RSR_DFR  0x80 /* Deferring (jabber) */
multiline_comment|/* Hydra System card address PROM offset */
DECL|macro|HYDRA_ADDRPROM
mdefine_line|#define HYDRA_ADDRPROM 0xffc0
eof
