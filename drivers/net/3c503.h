multiline_comment|/* Definitions for the 3Com 3c503 Etherlink 2. */
multiline_comment|/* This file is distributed under the GPL.&n;   Many of these names and comments are directly from the Crynwr packet&n;   drivers, which are released under the GPL. */
DECL|macro|EL2H
mdefine_line|#define EL2H (dev-&gt;base_addr + 0x400)
DECL|macro|EL2L
mdefine_line|#define EL2L (dev-&gt;base_addr)
multiline_comment|/* Vendor unique hardware addr. prefix. 3Com has 2 because they ran&n;   out of available addresses on the first one... */
DECL|macro|OLD_3COM_ID
mdefine_line|#define OLD_3COM_ID&t;0x02608c
DECL|macro|NEW_3COM_ID
mdefine_line|#define NEW_3COM_ID&t;0x0020af
multiline_comment|/* Shared memory management parameters. NB: The 8 bit cards have only&n;   one bank (MB1) which serves both Tx and Rx packet space. The 16bit&n;   cards have 2 banks, MB0 for Tx packets, and MB1 for Rx packets. &n;   You choose which bank appears in the sh. mem window with EGACFR_MBSn */
DECL|macro|EL2_MB0_START_PG
mdefine_line|#define EL2_MB0_START_PG&t;(0x00)&t;/* EL2/16 Tx packets go in bank 0 */
DECL|macro|EL2_MB1_START_PG
mdefine_line|#define EL2_MB1_START_PG&t;(0x20)&t;/* First page of bank 1 */
DECL|macro|EL2_MB1_STOP_PG
mdefine_line|#define EL2_MB1_STOP_PG&t;&t;(0x40)&t;/* Last page +1 of bank 1 */
multiline_comment|/* 3Com 3c503 ASIC registers */
DECL|macro|E33G_STARTPG
mdefine_line|#define E33G_STARTPG&t;(EL2H+0)&t;/* Start page, matching EN0_STARTPG */
DECL|macro|E33G_STOPPG
mdefine_line|#define E33G_STOPPG&t;(EL2H+1)&t;/* Stop page, must match EN0_STOPPG */
DECL|macro|E33G_DRQCNT
mdefine_line|#define E33G_DRQCNT&t;(EL2H+2)&t;/* DMA burst count */
DECL|macro|E33G_IOBASE
mdefine_line|#define E33G_IOBASE&t;(EL2H+3)&t;/* Read of I/O base jumpers. */
multiline_comment|/* (non-useful, but it also appears at the end of EPROM space) */
DECL|macro|E33G_ROMBASE
mdefine_line|#define E33G_ROMBASE&t;(EL2H+4)&t;/* Read of memory base jumpers. */
DECL|macro|E33G_GACFR
mdefine_line|#define E33G_GACFR&t;(EL2H+5)&t;/* Config/setup bits for the ASIC GA */
DECL|macro|E33G_CNTRL
mdefine_line|#define E33G_CNTRL&t;(EL2H+6)&t;/* Board&squot;s main control register */
DECL|macro|E33G_STATUS
mdefine_line|#define E33G_STATUS&t;(EL2H+7)&t;/* Status on completions. */
DECL|macro|E33G_IDCFR
mdefine_line|#define E33G_IDCFR&t;(EL2H+8)&t;/* Interrupt/DMA config register */
multiline_comment|/* (Which IRQ to assert, DMA chan to use) */
DECL|macro|E33G_DMAAH
mdefine_line|#define E33G_DMAAH&t;(EL2H+9)&t;/* High byte of DMA address reg */
DECL|macro|E33G_DMAAL
mdefine_line|#define E33G_DMAAL&t;(EL2H+10)&t;/* Low byte of DMA address reg */
multiline_comment|/* &quot;Vector pointer&quot; - if this address matches a read, the EPROM (rather than&n;   shared RAM) is mapped into memory space. */
DECL|macro|E33G_VP2
mdefine_line|#define E33G_VP2&t;(EL2H+11)
DECL|macro|E33G_VP1
mdefine_line|#define E33G_VP1&t;(EL2H+12)
DECL|macro|E33G_VP0
mdefine_line|#define E33G_VP0&t;(EL2H+13)
DECL|macro|E33G_FIFOH
mdefine_line|#define E33G_FIFOH&t;(EL2H+14)&t;/* FIFO for programmed I/O moves */
DECL|macro|E33G_FIFOL
mdefine_line|#define E33G_FIFOL&t;(EL2H+15)&t;/* ... low byte of above. */
multiline_comment|/* Bits in E33G_CNTRL register: */
DECL|macro|ECNTRL_RESET
mdefine_line|#define ECNTRL_RESET&t;(0x01)&t;/* Software reset of the ASIC and 8390 */
DECL|macro|ECNTRL_THIN
mdefine_line|#define ECNTRL_THIN&t;(0x02)&t;/* Onboard xcvr enable, AUI disable */
DECL|macro|ECNTRL_AUI
mdefine_line|#define ECNTRL_AUI&t;(0x00)&t;/* Onboard xcvr disable, AUI enable */
DECL|macro|ECNTRL_SAPROM
mdefine_line|#define ECNTRL_SAPROM&t;(0x04)&t;/* Map the station address prom */
DECL|macro|ECNTRL_DBLBFR
mdefine_line|#define ECNTRL_DBLBFR&t;(0x20)&t;/* FIFO configuration bit */
DECL|macro|ECNTRL_OUTPUT
mdefine_line|#define ECNTRL_OUTPUT&t;(0x40)&t;/* PC-to-3C503 direction if 1 */
DECL|macro|ECNTRL_INPUT
mdefine_line|#define ECNTRL_INPUT&t;(0x00)&t;/* 3C503-to-PC direction if 0 */
DECL|macro|ECNTRL_START
mdefine_line|#define ECNTRL_START&t;(0x80)&t;/* Start the DMA logic */
multiline_comment|/* Bits in E33G_STATUS register: */
DECL|macro|ESTAT_DPRDY
mdefine_line|#define ESTAT_DPRDY&t;(0x80)&t;/* Data port (of FIFO) ready */
DECL|macro|ESTAT_UFLW
mdefine_line|#define ESTAT_UFLW&t;(0x40)&t;/* Tried to read FIFO when it was empty */
DECL|macro|ESTAT_OFLW
mdefine_line|#define ESTAT_OFLW&t;(0x20)&t;/* Tried to write FIFO when it was full */
DECL|macro|ESTAT_DTC
mdefine_line|#define ESTAT_DTC&t;(0x10)&t;/* Terminal Count from PC bus DMA logic */
DECL|macro|ESTAT_DIP
mdefine_line|#define ESTAT_DIP&t;(0x08)&t;/* DMA In Progress */
multiline_comment|/* Bits in E33G_GACFR register: */
DECL|macro|EGACFR_NIM
mdefine_line|#define EGACFR_NIM&t;(0x80)&t;/* NIC interrupt mask */
DECL|macro|EGACFR_TCM
mdefine_line|#define EGACFR_TCM&t;(0x40)&t;/* DMA term. count interrupt mask */
DECL|macro|EGACFR_RSEL
mdefine_line|#define EGACFR_RSEL&t;(0x08)&t;/* Map a bank of card mem into system mem */
DECL|macro|EGACFR_MBS2
mdefine_line|#define EGACFR_MBS2&t;(0x04)&t;/* Memory bank select, bit 2. */
DECL|macro|EGACFR_MBS1
mdefine_line|#define EGACFR_MBS1&t;(0x02)&t;/* Memory bank select, bit 1. */
DECL|macro|EGACFR_MBS0
mdefine_line|#define EGACFR_MBS0&t;(0x01)&t;/* Memory bank select, bit 0. */
DECL|macro|EGACFR_NORM
mdefine_line|#define EGACFR_NORM&t;(0x49)&t;/* TCM | RSEL | MBS0 */
DECL|macro|EGACFR_IRQOFF
mdefine_line|#define EGACFR_IRQOFF&t;(0xc9)&t;/* TCM | RSEL | MBS0 | NIM */
multiline_comment|/*&n;&t;MBS2&t;MBS1&t;MBS0&t;Sh. mem windows card mem at:&n;&t;----&t;----&t;----&t;-----------------------------&n;&t;0&t;0&t;0&t;0x0000 -- bank 0&n;&t;0&t;0&t;1&t;0x2000 -- bank 1 (only choice for 8bit card)&n;&t;0&t;1&t;0&t;0x4000 -- bank 2, not used&n;&t;0&t;1&t;1&t;0x6000 -- bank 3, not used&n;&n;There was going to be a 32k card that used bank 2 and 3, but it &n;never got produced.&n;&n;*/
multiline_comment|/* End of 3C503 parameter definitions */
eof
