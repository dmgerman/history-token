multiline_comment|/******************************************************************************&n; *&n; *&t;(C)Copyright 1998,1999 SysKonnect,&n; *&t;a business unit of Schneider &amp; Koch &amp; Co. Datensysteme GmbH.&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;The information in this file is provided &quot;AS IS&quot; without warranty.&n; *&n; ******************************************************************************/
macro_line|#ifndef&t;_SKFBI_H_
DECL|macro|_SKFBI_H_
mdefine_line|#define&t;_SKFBI_H_
macro_line|#ifdef SYNC
DECL|macro|exist_board_far
mdefine_line|#define exist_board_far&t;&t;&t;exist_board
DECL|macro|get_board_para_far
mdefine_line|#define get_board_para_far&t;&t;get_board_para
macro_line|#endif
multiline_comment|/*&n; * physical address offset + IO-Port base address&n; */
macro_line|#ifndef&t;PCI
DECL|macro|ADDR
mdefine_line|#define&t;ADDR(a)&t;((a)+smc-&gt;hw.iop)
DECL|macro|ADDRS
mdefine_line|#define&t;ADDRS(smc,a) ((a)+(smc)-&gt;hw.iop)
macro_line|#endif
multiline_comment|/*&n; * FDDI-Fx (x := {I(SA), E(ISA), M(CA), P(CI)})&n; *&t;address calculation &amp; function defines&n; */
macro_line|#ifdef&t;EISA
multiline_comment|/*&n; * Configuration PROM:&t; !! all 8-Bit IO&squot;s !!&n; *&t;&t;&t;&t;&t;    |&lt;-&t;  MAC-Address&t; -&gt;|&n; *&t;/-+--+--+--+--+-//-+--+--+--+--+-//-+--+--+--+--+-//-+--+--+--+--+-/&n; * val:&t;  |PROD_ID0..3|&t;   | free      |    |00|00|5A|40|    |nn|mm|00|00|&n; *&t;/-+--+--+--+--+-//-+--+--+--+--+-//-+--+--+--+--+-//-+--+--+--+--+-/&n; * IO-&t;  ^&t;      ^&t;   ^&t;&t;    ^&t;&t;     ^&n; * port&t;0C80&t;    0C83  0C88&t;&t;   0C90&t;&t;    0C98&n; *&t;  |&t;       &bslash;&n; *&t;  |&t;&t;&bslash;&n; *&t;  |&t;&t; &bslash;______________________________________________&n; * EISA Expansion Board Product ID:&t;&t;&t;&t;&t;&bslash;&n; * BIT:&t;  |7 6 5 4 3 2 1 0|&t;&t;&t;&t;&t;&t; &bslash;&n; *&t;  | PROD_ID0&t;  | PROD_ID1&t;  | PROD_ID2&t;  | PROD_ID3&t;  |&n; *&t;  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+&n; *&t;  |0| MAN_C0  | MAN_C1&t;| MAN_C2  | PROD1 | PROD0 | REV1  | REV0  |&n; *&t;  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+&n; *&t;   ^=reserved&t;&t;&t;  | product numb. | revision numb |&n; * MAN_Cx = compressed manufacterer code (x:=0..2)&n; *&t;ASCII : &squot;A&squot;..&squot;Z&squot; : 0x41..0x5A -&gt; compr.(c-0x40) : 0x01..0x1A (5Bits!)&n; */
macro_line|#ifndef&t;MULT_OEM
macro_line|#ifndef&t;OEM_CONCEPT
DECL|macro|MAN_C0
mdefine_line|#define&t;MAN_C0&t;&t;(&squot;S&squot;-0x40)
DECL|macro|MAN_C1
mdefine_line|#define&t;MAN_C1&t;&t;(&squot;K&squot;-0x40)
DECL|macro|MAN_C2
mdefine_line|#define&t;MAN_C2&t;&t;(&squot;D&squot;-0x40)
DECL|macro|PROD_ID0
mdefine_line|#define&t;PROD_ID0&t;(u_char)((MAN_C0&lt;&lt;2) | (MAN_C1&gt;&gt;3))
DECL|macro|PROD_ID1
mdefine_line|#define&t;PROD_ID1&t;(u_char)(((MAN_C1&lt;&lt;5) &amp; 0xff) | MAN_C2)
DECL|macro|PROD_ID2
mdefine_line|#define&t;PROD_ID2&t;(u_char)(1)&t;/* prod. nr. */
DECL|macro|PROD_ID3
mdefine_line|#define&t;PROD_ID3&t;(u_char)(0)&t;/* rev. nr. */
macro_line|#ifndef&t;OEM_USER_DATA
DECL|macro|OEM_USER_DATA
mdefine_line|#define&t;OEM_USER_DATA&t;&quot;SK-NET FDDI V2.0 Userdata&quot;
macro_line|#endif
macro_line|#else&t;/*  OEM_CONCEPT */
multiline_comment|/* MAN_C(0|1|2) no longer present (ra). */
DECL|macro|PROD_ID0
mdefine_line|#define&t;PROD_ID0&t;(u_char)OEM_PROD_ID0
DECL|macro|PROD_ID1
mdefine_line|#define&t;PROD_ID1&t;(u_char)OEM_PROD_ID1
DECL|macro|PROD_ID2
mdefine_line|#define&t;PROD_ID2&t;(u_char)OEM_PROD_ID2
DECL|macro|PROD_ID3
mdefine_line|#define&t;PROD_ID3&t;(u_char)OEM_PROD_ID3
macro_line|#endif&t;/* OEM_CONCEPT */
DECL|macro|SKLOGO
mdefine_line|#define&t;SKLOGO&t;&t;PROD_ID0, PROD_ID1, PROD_ID2, PROD_ID3
macro_line|#endif&t;/* MULT_OEM */
DECL|macro|SADDRL
mdefine_line|#define&t;SADDRL&t;(0)&t;&t;/* start address SKLOGO */
DECL|macro|SA_MAC
mdefine_line|#define&t;SA_MAC&t;(0x10)&t;&t;/* start addr. MAC_AD within the PROM */
DECL|macro|PRA_OFF
mdefine_line|#define&t;PRA_OFF&t;(4)
DECL|macro|SA_PMD_TYPE
mdefine_line|#define SA_PMD_TYPE&t;(8)&t;/* start addr. PMD-Type */
DECL|macro|SKFDDI_PSZ
mdefine_line|#define&t;SKFDDI_PSZ&t;32&t;&t;/* address PROM size */
multiline_comment|/*&n; * address transmission from logical to physical offset address on board&n; */
DECL|macro|FMA
mdefine_line|#define FMA(a)&t;(0x0400|((a)&lt;&lt;1))&t;/* FORMAC+ (r/w) */
DECL|macro|P1A
mdefine_line|#define P1A(a)&t;(0x0800|((a)&lt;&lt;1))&t;/* PLC1 (r/w) */
DECL|macro|P2A
mdefine_line|#define P2A(a)&t;(0x0840|((a)&lt;&lt;1))&t;/* PLC2 (r/w) */
DECL|macro|TIA
mdefine_line|#define TIA(a)&t;(0x0880|((a)&lt;&lt;1))&t;/* Timer (r/w) */
DECL|macro|PRA
mdefine_line|#define PRA(a)&t;(0x0c80| (a))&t;&t;/* configuration PROM */
DECL|macro|C0A
mdefine_line|#define&t;C0A(a)&t;(0x0c84| (a))&t;&t;/* config. RAM */
DECL|macro|C1A
mdefine_line|#define&t;C1A(a)&t;(0x0ca0| (a))&t;&t;/* IRQ-, DMA-nr., EPROM type */
DECL|macro|C2A
mdefine_line|#define&t;C2A(a)&t;(0x0ca4| (a))&t;&t;/* EPROM and PAGE selector */
DECL|macro|CONF
mdefine_line|#define&t;CONF&t;C0A(0)&t;&t;&t;/* config RAM (card enable bit port) */
DECL|macro|PGRA
mdefine_line|#define PGRA&t;C2A(0)&t;&t;&t;/* Flash page register */
DECL|macro|CDID
mdefine_line|#define&t;CDID&t;PRA(0)&t;&t;&t;/* Card ID I/O port addr. offset */
multiline_comment|/*&n; * physical address offset + slot specific IO-Port base address&n; */
DECL|macro|FM_A
mdefine_line|#define FM_A(a)&t;(FMA(a)+smc-&gt;hw.iop)&t;/* FORMAC Plus physical addr */
DECL|macro|P1_A
mdefine_line|#define P1_A(a)&t;(P1A(a)+smc-&gt;hw.iop)&t;/* PLC1 (r/w) */
DECL|macro|P2_A
mdefine_line|#define P2_A(a)&t;(P2A(a)+smc-&gt;hw.iop)&t;/* PLC2 (r/w) */
DECL|macro|TI_A
mdefine_line|#define TI_A(a)&t;(TIA(a)+smc-&gt;hw.iop)&t;/* Timer (r/w) */
DECL|macro|PR_A
mdefine_line|#define PR_A(a)&t;(PRA(a)+smc-&gt;hw.iop)&t;/* config. PROM */
DECL|macro|C0_A
mdefine_line|#define C0_A(a)&t;(C0A(a)+smc-&gt;hw.iop)&t;/* config. RAM */
DECL|macro|C1_A
mdefine_line|#define C1_A(a)&t;(C1A(a)+smc-&gt;hw.iop)&t;/* config. RAM */
DECL|macro|C2_A
mdefine_line|#define C2_A(a)&t;(C2A(a)+smc-&gt;hw.iop)&t;/* config. RAM */
DECL|macro|CSRA
mdefine_line|#define&t;CSRA&t;0x0008&t;&t;/* control/status register address (r/w) */
DECL|macro|ISRA
mdefine_line|#define&t;ISRA&t;0x0008&t;&t;/* int. source register address (upper 8Bits) */
DECL|macro|PLC1I
mdefine_line|#define PLC1I&t;0x001a&t;&t;/* clear PLC1 interrupt (write only) */
DECL|macro|PLC2I
mdefine_line|#define PLC2I&t;0x0020&t;&t;/* clear PLC2 interrupt (write only) */
DECL|macro|CSFA
mdefine_line|#define CSFA&t;0x001c&t;&t;/* control/status FIFO BUSY flags (read only) */
DECL|macro|RQAA
mdefine_line|#define RQAA&t;0x001c&t;&t;/* Request reg. (write only) */
DECL|macro|WCTA
mdefine_line|#define WCTA&t;0x001e&t;&t;/* word counter (r/w) */
DECL|macro|FFLAG
mdefine_line|#define&t;FFLAG&t;0x005e&t;&t;/* FLAG/V_FULL (FIFO almost full, write only)*/
DECL|macro|CSR_A
mdefine_line|#define&t;CSR_A&t;(CSRA+smc-&gt;hw.iop)&t;/* control/status register address (r/w) */
macro_line|#ifdef UNIX
DECL|macro|CSR_AS
mdefine_line|#define&t;CSR_AS(smc)&t;(CSRA+(smc)-&gt;hw.iop)&t;/* control/status register address (r/w) */
macro_line|#endif
DECL|macro|ISR_A
mdefine_line|#define&t;ISR_A&t;(ISRA+smc-&gt;hw.iop)&t;/* int. source register address (upper 8Bits) */
DECL|macro|PLC1_I
mdefine_line|#define PLC1_I&t;(PLC1I+smc-&gt;hw.iop)&t;/* clear PLC1 internupt (write only) */
DECL|macro|PLC2_I
mdefine_line|#define PLC2_I&t;(PLC2I+smc-&gt;hw.iop)&t;/* clear PLC2 interrupt (write only) */
DECL|macro|CSF_A
mdefine_line|#define CSF_A&t;(CSFA+smc-&gt;hw.iop)&t;/* control/status FIFO BUSY flags (r/w) */
DECL|macro|RQA_A
mdefine_line|#define RQA_A&t;(RQAA+smc-&gt;hw.iop)&t;/* Request reg. (write only) */
DECL|macro|WCT_A
mdefine_line|#define WCT_A&t;(WCTA+smc-&gt;hw.iop)&t;/* word counter (r/w) */
DECL|macro|FFLAG_A
mdefine_line|#define&t;FFLAG_A&t;(FFLAG+smc-&gt;hw.iop)&t;/* FLAG/V_FULL (FIFO almost full, write only)*/
multiline_comment|/*&n; * control/status register CSRA&t;bits&n; */
multiline_comment|/* write */
DECL|macro|CS_CRESET
mdefine_line|#define CS_CRESET&t;0x01&t;&t;/* Card reset (0=reset) */
DECL|macro|CS_RESET_FIFO
mdefine_line|#define&t;CS_RESET_FIFO&t;0x02&t;&t;/* FIFO reset (0=reset) */
DECL|macro|CS_IMSK
mdefine_line|#define&t;CS_IMSK&t;&t;0x04&t;&t;/* enable IRQ (1=enable, 0=disable) */
DECL|macro|CS_EN_IRQ_TC
mdefine_line|#define&t;CS_EN_IRQ_TC&t;0x08&t;&t;/* enable IRQ from transfer counter */
DECL|macro|CS_BYPASS
mdefine_line|#define CS_BYPASS&t;0x20&t;&t;/* bypass switch (0=remove, 1=insert)*/
DECL|macro|CS_LED_0
mdefine_line|#define CS_LED_0&t;0x40&t;&t;/* switch LED 0 */
DECL|macro|CS_LED_1
mdefine_line|#define&t;CS_LED_1&t;0x80&t;&t;/* switch LED 1 */
multiline_comment|/* read */
DECL|macro|CS_BYSTAT
mdefine_line|#define&t;CS_BYSTAT&t;0x40&t;&t;/* 0=Bypass exist, 1= ..not */
DECL|macro|CS_SAS
mdefine_line|#define&t;CS_SAS&t;&t;0x80&t;&t;/* single attachement station (=1) */
multiline_comment|/*&n; * control/status register CSFA bits (FIFO)&n; */
DECL|macro|CSF_MUX0
mdefine_line|#define&t;CSF_MUX0&t;0x01
DECL|macro|CSF_MUX1
mdefine_line|#define&t;CSF_MUX1&t;0x02
DECL|macro|CSF_HSREQ0
mdefine_line|#define&t;CSF_HSREQ0&t;0x04
DECL|macro|CSF_HSREQ1
mdefine_line|#define&t;CSF_HSREQ1&t;0x08
DECL|macro|CSF_HSREQ2
mdefine_line|#define&t;CSF_HSREQ2&t;0x10
DECL|macro|CSF_BUSY_DMA
mdefine_line|#define&t;CSF_BUSY_DMA&t;0x40
DECL|macro|CSF_BUSY_FIFO
mdefine_line|#define&t;CSF_BUSY_FIFO&t;0x80
multiline_comment|/*&n; * Interrupt source register ISRA (upper 8 data bits) read only &amp; low activ.&n; */
DECL|macro|IS_MINTR1
mdefine_line|#define IS_MINTR1&t;0x0100&t;&t;/* FORMAC ST1U/L &amp; ~IMSK1U/L*/
DECL|macro|IS_MINTR2
mdefine_line|#define IS_MINTR2&t;0x0200&t;&t;/* FORMAC ST2U/L &amp; ~IMSK2U/L*/
DECL|macro|IS_PLINT1
mdefine_line|#define IS_PLINT1&t;0x0400&t;&t;/* PLC1 */
DECL|macro|IS_PLINT2
mdefine_line|#define IS_PLINT2&t;0x0800&t;&t;/* PLC2 */
DECL|macro|IS_TIMINT
mdefine_line|#define IS_TIMINT&t;0x1000&t;&t;/* Timer 82C54-2 */
DECL|macro|IS_TC
mdefine_line|#define&t;IS_TC&t;&t;0x2000&t;&t;/* transf. counter */
DECL|macro|ALL_IRSR
mdefine_line|#define&t;ALL_IRSR (IS_MINTR1|IS_MINTR2|IS_PLINT1|IS_PLINT2|IS_TIMINT|IS_TC)
multiline_comment|/*&n; * CONFIG&lt;0&gt; RAM (C0_A())&n; */
DECL|macro|CFG_CARD_EN
mdefine_line|#define&t;CFG_CARD_EN&t;0x01&t;&t;/* card enable */
multiline_comment|/*&n; * CONFIG&lt;1&gt; RAM (C1_A())&n; */
DECL|macro|CFG_IRQ_SEL
mdefine_line|#define&t;CFG_IRQ_SEL&t;0x03&t;&t;/* IRQ select (4 nr.) */
DECL|macro|CFG_IRQ_TT
mdefine_line|#define&t;CFG_IRQ_TT&t;0x04&t;&t;/* IRQ trigger type (LEVEL/EDGE) */
DECL|macro|CFG_DRQ_SEL
mdefine_line|#define&t;CFG_DRQ_SEL&t;0x18&t;&t;/* DMA requ. (4 nr.) */
DECL|macro|CFG_BOOT_EN
mdefine_line|#define&t;CFG_BOOT_EN&t;0x20&t;&t;/* 0=BOOT-, 1=Application Software */
DECL|macro|CFG_PROG_EN
mdefine_line|#define&t;CFG_PROG_EN&t;0x40&t;&t;/* V_Prog for FLASH_PROM (1=on) */
multiline_comment|/*&n; * CONFIG&lt;2&gt; RAM (C2_A())&n; */
DECL|macro|CFG_EPROM_SEL
mdefine_line|#define&t;CFG_EPROM_SEL&t;0x0f&t;&t;/* FPROM start address selection */
DECL|macro|CFG_PAGE
mdefine_line|#define&t;CFG_PAGE&t;0xf0&t;&t;/* FPROM page selection */
DECL|macro|READ_PROM
mdefine_line|#define&t;READ_PROM(a)&t;((u_char)inp(a))
DECL|macro|GET_PAGE
mdefine_line|#define&t;GET_PAGE(i)&t;outp(C2_A(0),((int)(i)&lt;&lt;4) | (inp(C2_A(0)) &amp; ~CFG_PAGE))
DECL|macro|FPROM_SW
mdefine_line|#define&t;FPROM_SW()&t;(inp(C1_A(0)) &amp; CFG_BOOT_EN)
DECL|macro|MAX_PAGES
mdefine_line|#define&t;MAX_PAGES&t;16&t;&t;/* 16 pages */
DECL|macro|MAX_FADDR
mdefine_line|#define&t;MAX_FADDR&t;0x2000&t;&t;/* 8K per page */
DECL|macro|VPP_ON
mdefine_line|#define&t;VPP_ON()&t;outp(C1_A(0),inp(C1_A(0)) |  CFG_PROG_EN)
DECL|macro|VPP_OFF
mdefine_line|#define&t;VPP_OFF()&t;outp(C1_A(0),inp(C1_A(0)) &amp; ~CFG_PROG_EN)
DECL|macro|DMA_BUSY
mdefine_line|#define&t;DMA_BUSY()&t;(inpw(CSF_A) &amp; CSF_BUSY_DMA)
DECL|macro|FIFO_BUSY
mdefine_line|#define FIFO_BUSY()&t;(inpw(CSF_A) &amp; CSF_BUSY_FIFO)
DECL|macro|DMA_FIFO_BUSY
mdefine_line|#define&t;DMA_FIFO_BUSY()&t;(inpw(CSF_A) &amp; (CSF_BUSY_DMA | CSF_BUSY_FIFO))
DECL|macro|BUS_CHECK
mdefine_line|#define&t;BUS_CHECK()
macro_line|#ifdef UNISYS
multiline_comment|/* For UNISYS use another macro with drv_usecewait function */
DECL|macro|CHECK_DMA
mdefine_line|#define CHECK_DMA() {u_long k = 1000000; &bslash;&n;&t;&t;while (k &amp;&amp; (DMA_BUSY())) { k--; drv_usecwait(20); } &bslash;&n;&t;&t;if (!k) SMT_PANIC(smc,HWM_E0003,HWM_E0003_MSG) ; }
macro_line|#else
DECL|macro|CHECK_DMA
mdefine_line|#define CHECK_DMA() {u_long k = 1000000 ;&bslash;&n;&t;&t;while (k &amp;&amp; (DMA_BUSY())) k-- ;&bslash;&n;&t;&t;if (!k) SMT_PANIC(smc,HWM_E0003,HWM_E0003_MSG) ; }
macro_line|#endif
DECL|macro|CHECK_FIFO
mdefine_line|#define CHECK_FIFO() {u_long k = 1000000 ;&bslash;&n;&t;&t;while (k &amp;&amp; (FIFO_BUSY())) k-- ;&bslash;&n;&t;&t;if (!k) SMT_PANIC(smc,HWM_E0019,HWM_E0019_MSG) ; }
DECL|macro|CHECK_DMA_FIFO
mdefine_line|#define CHECK_DMA_FIFO() {u_long k = 1000000 ;&bslash;&n;&t;&t;while (k &amp;&amp; (DMA_FIFO_BUSY())) k-- ;&bslash;&n;&t;&t;if (!k) SMT_PANIC(smc,HWM_E0004,HWM_E0004_MSG) ; }
DECL|macro|GET_ISR
mdefine_line|#define&t;GET_ISR()&t;~inpw(ISR_A)
DECL|macro|CHECK_ISR
mdefine_line|#define CHECK_ISR()&t;~inpw(ISR_A)
macro_line|#ifndef UNIX
macro_line|#ifndef&t;WINNT
DECL|macro|CLI_FBI
mdefine_line|#define&t;CLI_FBI()&t;outpw(CSR_A,(inpw(CSR_A)&amp;&bslash;&n;&t;&t;&t;(CS_CRESET|CS_BYPASS))|CS_RESET_FIFO|smc-&gt;hw.led)
macro_line|#else&t;/* WINNT */
DECL|macro|CLI_FBI
mdefine_line|#define CLI_FBI()&t;outpw(CSR_A,(l_inpw(CSR_A)&amp;&bslash;&n;&t;&t;&t;(CS_CRESET|CS_BYPASS))|CS_RESET_FIFO|smc-&gt;hw.led)
macro_line|#endif&t;/* WINNT */
macro_line|#else&t;/* UNIX */
DECL|macro|CLI_FBI
mdefine_line|#define&t;CLI_FBI(smc)&t;outpw(CSR_AS(smc),(inpw(CSR_AS(smc))&amp;&bslash;&n;&t;&t;&t;(CS_CRESET|CS_BYPASS))|CS_RESET_FIFO|(smc)-&gt;hw.led)
macro_line|#endif
macro_line|#ifndef UNIX
DECL|macro|STI_FBI
mdefine_line|#define&t;STI_FBI()&t;outpw(CSR_A,(inpw(CSR_A)&amp;&bslash;&n;&t;&t;(CS_CRESET|CS_BYPASS|CS_RESET_FIFO))|CS_IMSK|smc-&gt;hw.led)
macro_line|#else
DECL|macro|STI_FBI
mdefine_line|#define&t;STI_FBI(smc)&t;outpw(CSR_AS(smc),(inpw(CSR_AS(smc))&amp;&bslash;&n;&t;&t;(CS_CRESET|CS_BYPASS|CS_RESET_FIFO))|CS_IMSK|(smc)-&gt;hw.led)
macro_line|#endif
multiline_comment|/* EISA DMA Controller */
DECL|macro|DMA_WRITE_SINGLE_MASK_BIT_M
mdefine_line|#define DMA_WRITE_SINGLE_MASK_BIT_M&t;0x0a&t;/* Master DMA Controller */
DECL|macro|DMA_WRITE_SINGLE_MASK_BIT_S
mdefine_line|#define DMA_WRITE_SINGLE_MASK_BIT_S&t;0xd4&t;/* Slave DMA Controller */
DECL|macro|DMA_CLEAR_BYTE_POINTER_M
mdefine_line|#define DMA_CLEAR_BYTE_POINTER_M&t;0x0c
DECL|macro|DMA_CLEAR_BYTE_POINTER_S
mdefine_line|#define DMA_CLEAR_BYTE_POINTER_S&t;0xd8
macro_line|#endif&t;/* EISA */
macro_line|#ifdef&t;MCA
multiline_comment|/*&n; * POS Register:&t; !! all I/O&squot;s are 8-Bit !!&n; */
DECL|macro|POS_SYS_SETUP
mdefine_line|#define&t;POS_SYS_SETUP&t;0x94&t;/* system setup register */
DECL|macro|POS_SYSTEM
mdefine_line|#define&t;POS_SYSTEM&t;0xff&t;/* system mode */
DECL|macro|POS_CHANNEL_POS
mdefine_line|#define&t;POS_CHANNEL_POS&t;0x96&t;/* register slot ID */
DECL|macro|POS_CHANNEL_BIT
mdefine_line|#define&t;POS_CHANNEL_BIT&t;0x08&t;/* mask for -&quot;- */
DECL|macro|POS_BASE
mdefine_line|#define&t;POS_BASE&t;0x100&t;/* POS base address */
DECL|macro|POS_ID_LOW
mdefine_line|#define&t;POS_ID_LOW&t;POS_BASE&t;/* card ID low */
DECL|macro|POS_ID_HIGH
mdefine_line|#define&t;POS_ID_HIGH&t;(POS_BASE+1)&t;/* card ID high */
DECL|macro|POS_102
mdefine_line|#define&t;POS_102&t;&t;(POS_BASE+2)&t;/* card en., arbitration level .. */
DECL|macro|POS_103
mdefine_line|#define&t;POS_103&t;&t;(POS_BASE+3)&t;/* FPROM addr, page */
DECL|macro|POS_104
mdefine_line|#define&t;POS_104&t;&t;(POS_BASE+4)&t;/* I/O, IRQ */
DECL|macro|POS_105
mdefine_line|#define&t;POS_105&t;&t;(POS_BASE+5)&t;/* POS_CHCK */
DECL|macro|POS_106
mdefine_line|#define&t;POS_106&t;&t;(POS_BASE+6)&t;/* to read VPD */
DECL|macro|POS_107
mdefine_line|#define&t;POS_107&t;&t;(POS_BASE+7)&t;/* added without function */
multiline_comment|/* FM1 card IDs */
DECL|macro|FM1_CARD_ID0
mdefine_line|#define&t;FM1_CARD_ID0&t;0x83
DECL|macro|FM1_CARD_ID1
mdefine_line|#define&t;FM1_CARD_ID1&t;0
DECL|macro|FM1_IBM_ID0
mdefine_line|#define&t;FM1_IBM_ID0&t;0x9c
DECL|macro|FM1_IBM_ID1
mdefine_line|#define&t;FM1_IBM_ID1&t;0x8f
multiline_comment|/* FM2 card IDs */
DECL|macro|FM2_CARD_ID0
mdefine_line|#define&t;FM2_CARD_ID0&t;0xab
DECL|macro|FM2_CARD_ID1
mdefine_line|#define&t;FM2_CARD_ID1&t;0
DECL|macro|FM2_IBM_ID0
mdefine_line|#define&t;FM2_IBM_ID0&t;0x7e
DECL|macro|FM2_IBM_ID1
mdefine_line|#define&t;FM2_IBM_ID1&t;0x8f
multiline_comment|/* Board revision. */
DECL|macro|FM1_REV
mdefine_line|#define FM1_REV&t;&t;0
DECL|macro|FM2_REV
mdefine_line|#define FM2_REV&t;&t;1
DECL|macro|MAX_SLOT
mdefine_line|#define&t;MAX_SLOT&t;8
multiline_comment|/*&n; * POS_102&n; */
DECL|macro|POS_CARD_EN
mdefine_line|#define&t;POS_CARD_EN&t;0x01&t;/* card enable =1 */
DECL|macro|POS_SDAT_EN
mdefine_line|#define&t;POS_SDAT_EN&t;0x02&t;/* enable 32-bit streaming data mode */
DECL|macro|POS_EN_CHKINT
mdefine_line|#define&t;POS_EN_CHKINT&t;0x04&t;/* enable int. from check line asserted */
DECL|macro|POS_EN_BUS_ERR
mdefine_line|#define&t;POS_EN_BUS_ERR&t;0x08&t;/* enable int. on invalid busmaster transf. */
DECL|macro|POS_FAIRNESS
mdefine_line|#define&t;POS_FAIRNESS&t;0x10&t;/* fairnes on =1 */
multiline_comment|/* attention: arbitration level used with bit 0 POS 105 */
DECL|macro|POS_LARBIT
mdefine_line|#define&t;POS_LARBIT&t;0xe0&t;/* arbitration level&t;(0,0,0)-&gt;level = 0x8&n;&t;&t;&t;&t;&t;&t;&t;(1,1,1)-&gt;level = 0xf */
multiline_comment|/*&n; * POS_103&n; */
DECL|macro|POS_PAGE
mdefine_line|#define&t;POS_PAGE&t;0x07&t;/* FPROM page selection */
DECL|macro|POS_BOOT_EN
mdefine_line|#define&t;POS_BOOT_EN&t;0x08&t;/* boot PROM enable =1 */
DECL|macro|POS_MSEL
mdefine_line|#define&t;POS_MSEL&t;0x70&t;/* memory start address for FPROM mapping */
DECL|macro|PROG_EN
mdefine_line|#define&t;PROG_EN&t;&t;0x80&t;/* FM1: Vpp prog on/off */
DECL|macro|POS_SDR
mdefine_line|#define&t;POS_SDR&t;&t;0x80&t;/* FM2: Streaming data bit */
multiline_comment|/*&n; * POS_104&n; */
DECL|macro|POS_IOSEL
mdefine_line|#define&t;POS_IOSEL&t;0x3f&t;/* selected I/O base address */
DECL|macro|POS_IRQSEL
mdefine_line|#define&t;POS_IRQSEL&t;0xc0&t;/* selected interrupt */
multiline_comment|/*&n; * POS_105&n; */
DECL|macro|POS_CHCK
mdefine_line|#define&t;POS_CHCK&t;0x80
DECL|macro|POS_SYNC_ERR
mdefine_line|#define POS_SYNC_ERR&t;0x20&t;/* FM2: synchronous error reporting&t;*/
DECL|macro|POS_PAR_DATA
mdefine_line|#define POS_PAR_DATA&t;0x10&t;/* FM2: data parity enable bit&t;*/
DECL|macro|POS_PAR_ADDR
mdefine_line|#define POS_PAR_ADDR&t;0x08&t;/* FM2: address parity enable bit&t;*/
DECL|macro|POS_IRQHSEL
mdefine_line|#define&t;POS_IRQHSEL&t;0x02&t;/* FM2: Highest bit for IRQ_selection&t;*/
DECL|macro|POS_HARBIT
mdefine_line|#define POS_HARBIT&t;0x01&t;/* Highest bit in Bus arbitration selection */
DECL|macro|SA_MAC
mdefine_line|#define&t;SA_MAC&t;(0)&t;&t;/* start addr. MAC_AD within the PROM&t;*/
DECL|macro|PRA_OFF
mdefine_line|#define&t;PRA_OFF&t;(0)
DECL|macro|SA_PMD_TYPE
mdefine_line|#define SA_PMD_TYPE&t;(8)&t;/* start addr. PMD-Type&t;*/
multiline_comment|/*&n; * address transmission from logical to physical offset address on board&n; */
DECL|macro|FMA
mdefine_line|#define&t;FMA(a)&t;(0x0100|((a)&lt;&lt;1))&t;/* FORMAC+ (r/w) */
DECL|macro|P2
mdefine_line|#define&t;P2(a)&t;(0x00c0|((a)&lt;&lt;1))&t;/* PLC2 (r/w) (DAS) */
DECL|macro|P1
mdefine_line|#define&t;P1(a)&t;(0x0080|((a)&lt;&lt;1))&t;/* PLC1 (r/w) */
DECL|macro|TI
mdefine_line|#define&t;TI(a)&t;(0x0060|((a)&lt;&lt;1))&t;/* Timer (r/w) */
DECL|macro|PR
mdefine_line|#define&t;PR(a)&t;(0x0040|((a)&lt;&lt;1))&t;/* configuration PROM */
DECL|macro|CS
mdefine_line|#define&t;CS(a)&t;(0x0020| (a))&t;&t;/* control/status */
DECL|macro|FF
mdefine_line|#define&t;FF(a)&t;(0x0010|((a)&lt;&lt;1))&t;/* FIFO ASIC */
DECL|macro|CT
mdefine_line|#define&t;CT(a)&t;(0x0000|((a)&lt;&lt;1))&t;/* counter */
multiline_comment|/*&n; * counter&n; */
DECL|macro|ACLA
mdefine_line|#define&t;ACLA&t;CT(0)&t;&t;/* address counter low */
DECL|macro|ACHA
mdefine_line|#define&t;ACHA&t;CT(1)&t;&t;/* address counter high */
DECL|macro|BCN
mdefine_line|#define&t;BCN&t;CT(2)&t;&t;/* byte counter */
DECL|macro|MUX
mdefine_line|#define&t;MUX&t;CT(3)&t;&t;/* MUX-register */
DECL|macro|WCN
mdefine_line|#define&t;WCN&t;CT(0x08)&t;/* word counter */
DECL|macro|FFLG
mdefine_line|#define&t;FFLG&t;CT(0x09)&t;/* FIFO Flags */
multiline_comment|/*&n; * test/control register (FM2 only)&n; */
DECL|macro|CNT_TST
mdefine_line|#define CNT_TST&t;0x018&t;&t;/* Counter test control register */
DECL|macro|CNT_STP
mdefine_line|#define CNT_STP 0x01a&t;&t;/* Counter test step reg. (8 Bit) */
multiline_comment|/*&n; * CS register (read only)&n; */
DECL|macro|CSRA
mdefine_line|#define&t;CSRA&t;CS(0)&t;&t;/* control/status register address */
DECL|macro|CSFA
mdefine_line|#define&t;CSFA&t;CS(2)&t;&t;/* control/status FIFO BUSY ...&t; */
DECL|macro|ISRA
mdefine_line|#define&t;ISRA&t;CS(4)&t;&t;/* first int. source register address */
DECL|macro|ISR2
mdefine_line|#define&t;ISR2&t;CS(6)&t;&t;/* second int. source register address */
DECL|macro|LEDR
mdefine_line|#define&t;LEDR&t;CS(0x0c)&t;/* LED register r/w */
DECL|macro|CSIL
mdefine_line|#define&t;CSIL&t;CS(0x10)&t;/* I/O mapped POS_ID_low (100) */
DECL|macro|CSIH
mdefine_line|#define&t;CSIH&t;CS(0x12)&t;/*&t;- &quot; - POS_ID_HIGH (101) */
DECL|macro|CSA
mdefine_line|#define&t;CSA&t;CS(0x14)&t;/*&t;- &quot; - POS_102 */
DECL|macro|CSM
mdefine_line|#define&t;CSM&t;CS(0x0e)&t;/*&t;- &quot; - POS_103 */
DECL|macro|CSM_FM1
mdefine_line|#define&t;CSM_FM1&t;CS(0x16)&t;/*&t;- &quot; - POS_103 (copy in FM1) */
DECL|macro|CSI
mdefine_line|#define&t;CSI&t;CS(0x18)&t;/*&t;- &quot; - POS_104 */
DECL|macro|CSS
mdefine_line|#define&t;CSS&t;CS(0x1a)&t;/*&t;- &quot; - POS_105 */
DECL|macro|CSP_06
mdefine_line|#define&t;CSP_06&t;CS(0x1c)&t;/*&t;- &quot; - POS_106 */
DECL|macro|WDOG_ST
mdefine_line|#define&t;WDOG_ST&t;&t;0x1c&t;/* Watchdog status (FM2 only)&t;*/
DECL|macro|WDOG_EN
mdefine_line|#define&t;WDOG_EN&t;&t;0x1c&t;/* Watchdog enabling (FM2 only, 8Bit)&t;*/
DECL|macro|WDOG_DIS
mdefine_line|#define&t;WDOG_DIS&t;0x1e&t;/* Watchdog disabling (FM2 only, 8Bit)&t;*/
DECL|macro|PGRA
mdefine_line|#define PGRA&t;CSM&t;&t;/* Flash page register */
DECL|macro|WCTA
mdefine_line|#define&t;WCTA&t;FF(0)&t;&t;/* word counter */
DECL|macro|FFLAG
mdefine_line|#define&t;FFLAG&t;FF(1)&t;&t;/* FLAG/V_FULL (FIFO almost full, write only)*/
multiline_comment|/*&n; * Timer register (FM2 only)&n; */
DECL|macro|RTM_CNT
mdefine_line|#define RTM_CNT&t;&t;0x28&t;&t;/* RTM Counter */
DECL|macro|TI_DIV
mdefine_line|#define TI_DIV&t;&t;0x60&t;&t;/* Timer Prescaler */
DECL|macro|TI_CH1
mdefine_line|#define TI_CH1&t;&t;0x62&t;&t;/* Timer channel 1 counter */
DECL|macro|TI_STOP
mdefine_line|#define TI_STOP&t;&t;0x64&t;&t;/* Stop timer on channel 1 */
DECL|macro|TI_STRT
mdefine_line|#define TI_STRT&t;&t;0x66&t;&t;/* Start timer on channel 1 */
DECL|macro|TI_INI2
mdefine_line|#define TI_INI2&t;&t;0x68&t;&t;/* Timer: Bus master preemption */
DECL|macro|TI_CNT2
mdefine_line|#define TI_CNT2&t;&t;0x6a&t;&t;/* Timer */
DECL|macro|TI_INI3
mdefine_line|#define TI_INI3&t;&t;0x6c&t;&t;/* Timer: Streaming data */
DECL|macro|TI_CNT3
mdefine_line|#define TI_CNT3&t;&t;0x6e&t;&t;/* Timer */
DECL|macro|WDOG_LO
mdefine_line|#define WDOG_LO&t;&t;0x70&t;&t;/* Watchdog counter low */
DECL|macro|WDOG_HI
mdefine_line|#define WDOG_HI&t;&t;0x72&t;&t;/* Watchdog counter high */
DECL|macro|RTM_PRE
mdefine_line|#define RTM_PRE&t;&t;0x74&t;&t;/* restr. token prescaler */
DECL|macro|RTM_TIM
mdefine_line|#define RTM_TIM&t;&t;0x76&t;&t;/* restr. token timer */
multiline_comment|/*&n; * Recommended Timeout values (for FM2 timer only)&n; */
DECL|macro|TOUT_BM_PRE
mdefine_line|#define TOUT_BM_PRE&t;188&t;&t;/* 3.76 usec&t;*/
DECL|macro|TOUT_S_DAT
mdefine_line|#define TOUT_S_DAT&t;374&t;&t;/* 7.48 usec&t;*/
multiline_comment|/*&n; * CS register (write only)&n; */
DECL|macro|HSR
mdefine_line|#define&t;HSR(p)&t;CS(0x18|(p))&t;/* Host request register */
DECL|macro|RTM_PUT
mdefine_line|#define&t;RTM_PUT&t;&t;0x36&t;&t;/* restr. token counter write */
DECL|macro|RTM_GET
mdefine_line|#define&t;RTM_GET&t;&t;0x28&t;&t;/*&t;- &quot; -&t;clear */
DECL|macro|RTM_CLEAR
mdefine_line|#define&t;RTM_CLEAR&t;0x34&t;&t;/*&t;- &quot; -&t;read */
multiline_comment|/*&n; * BCN&t;Bit definitions&n; */
DECL|macro|BCN_BUSY
mdefine_line|#define BCN_BUSY&t;0x8000&t;&t;/* DMA Busy flag */
DECL|macro|BCN_AZERO
mdefine_line|#define BCN_AZERO&t;0x4000&t;&t;/* Almost zero flag (BCN &lt; 4) */
DECL|macro|BCN_STREAM
mdefine_line|#define BCN_STREAM&t;0x2000&t;&t;/* Allow streaming data (BCN &gt;= 8) */
multiline_comment|/*&n; * WCN&t;Bit definitions&n; */
DECL|macro|WCN_ZERO
mdefine_line|#define WCN_ZERO&t;0x2000&t;&t;/* Zero flag (counted to zero) */
DECL|macro|WCN_AZERO
mdefine_line|#define WCN_AZERO&t;0x1000&t;&t;/* Almost zero flag (BCN &lt; 4) */
multiline_comment|/*&n; * CNT_TST&t;Bit definitions&n; */
DECL|macro|CNT_MODE
mdefine_line|#define CNT_MODE&t;0x01&t;&t;/* Go into test mode */
DECL|macro|CNT_D32
mdefine_line|#define&t;CNT_D32&t;&t;0x02&t;&t;/* 16/32 BIT test mode */
multiline_comment|/*&n; * FIFO Flag&t;&t;FIFO Flags/Vfull register&n; */
DECL|macro|FF_VFULL
mdefine_line|#define FF_VFULL&t;0x003f&t;&t;/* V_full value mask */
DECL|macro|FFLG_FULL
mdefine_line|#define FFLG_FULL&t;0x2000&t;&t;/* FULL flag */
DECL|macro|FFLG_A_FULL
mdefine_line|#define FFLG_A_FULL&t;0x1000&t;&t;/* Almost full flag */
DECL|macro|FFLG_VFULL
mdefine_line|#define FFLG_VFULL&t;0x0800&t;&t;/* V_full Flag */
DECL|macro|FFLG_A_EMP
mdefine_line|#define FFLG_A_EMP&t;0x0400&t;&t;/* almost empty flag */
DECL|macro|FFLG_EMP
mdefine_line|#define FFLG_EMP&t;0x0200&t;&t;/* empty flag */
DECL|macro|FFLG_T_EMP
mdefine_line|#define FFLG_T_EMP&t;0x0100&t;&t;/* totally empty flag */
multiline_comment|/*&n; * WDOG&t;&t;Watchdog status register&n; */
DECL|macro|WDOG_ALM
mdefine_line|#define WDOG_ALM&t;0x01&t;&t;/* Watchdog alarm Bit */
DECL|macro|WDOG_ACT
mdefine_line|#define WDOG_ACT&t;0x02&t;&t;/* Watchdog active Bit */
multiline_comment|/*&n; * CS(0)&t;CONTROLS&n; */
DECL|macro|CS_CRESET
mdefine_line|#define&t;CS_CRESET&t;0x0001
DECL|macro|FIFO_RST
mdefine_line|#define&t;FIFO_RST&t;0x0002
DECL|macro|CS_IMSK
mdefine_line|#define&t;CS_IMSK&t;&t;0x0004
DECL|macro|EN_IRQ_CHCK
mdefine_line|#define&t;EN_IRQ_CHCK&t;0x0008
DECL|macro|EN_IRQ_TOKEN
mdefine_line|#define&t;EN_IRQ_TOKEN&t;0x0010
DECL|macro|EN_IRQ_TC
mdefine_line|#define&t;EN_IRQ_TC&t;0x0020
DECL|macro|TOKEN_STATUS
mdefine_line|#define&t;TOKEN_STATUS&t;0x0040
DECL|macro|RTM_CHANGE
mdefine_line|#define&t;RTM_CHANGE&t;0x0080
DECL|macro|CS_SAS
mdefine_line|#define&t;CS_SAS&t;&t;0x0100
DECL|macro|CS_BYSTAT
mdefine_line|#define&t;CS_BYSTAT&t;0x0200&t;/* bypass connected (0=conn.) */
DECL|macro|CS_BYPASS
mdefine_line|#define&t;CS_BYPASS&t;0x0400&t;/* bypass on/off indication */
multiline_comment|/*&n; * CS(2)&t;FIFOSTAT&n; */
DECL|macro|HSREQ
mdefine_line|#define&t;HSREQ&t;&t;0x0007
DECL|macro|BIGDIR
mdefine_line|#define&t;BIGDIR&t;&t;0x0008
DECL|macro|CSF_BUSY_FIFO
mdefine_line|#define&t;CSF_BUSY_FIFO&t;0x0010
DECL|macro|CSF_BUSY_DMA
mdefine_line|#define&t;CSF_BUSY_DMA&t;0x0020
DECL|macro|SLOT_32
mdefine_line|#define&t;SLOT_32&t;&t;0x0040
DECL|macro|LED_0
mdefine_line|#define&t;LED_0&t;&t;0x0001
DECL|macro|LED_1
mdefine_line|#define&t;LED_1&t;&t;0x0002
DECL|macro|LED_2
mdefine_line|#define&t;LED_2&t;&t;0x0100
DECL|macro|MAX_PAGES
mdefine_line|#define&t;MAX_PAGES&t;8&t;&t;/* pages */
DECL|macro|MAX_FADDR
mdefine_line|#define&t;MAX_FADDR&t;0x4000&t;&t;/* 16K per page */
multiline_comment|/*&n; *&t;IRQ = ISRA || ISR2 ;&n; *&n; *&t;ISRA = IRQ_OTH_EN &amp;&amp; (IS_LAN | IS_BUS) ;&n; *&t;ISR2 = IRQ_TC_EN &amp;&amp; IS_TC ;&n; *&n; *&t;IS_LAN = (IS_MINTR1 | IS_MINTR2 | IS_PLINT1 | IS_PLINT2 | IS_TIMINT) ||&n; *&t;&t; (IRQ_EN_TOKEN &amp;&amp; IS_TOKEN) ;&n; *&t;IS_BUS = IRQ_CHCK_EN &amp;&amp; (IS_BUSERR | IS_CHCK_L) ;&n; */
multiline_comment|/*&n; *&t;ISRA&t;!!! activ high !!!&n; */
DECL|macro|IS_MINTR1
mdefine_line|#define&t;IS_MINTR1&t;0x0001&t;&t;/* FORMAC ST1U/L &amp; ~IMSK1U/L*/
DECL|macro|IS_MINTR2
mdefine_line|#define&t;IS_MINTR2&t;0x0002&t;&t;/* FORMAC ST2U/L &amp; ~IMSK2U/L*/
DECL|macro|IS_PLINT1
mdefine_line|#define&t;IS_PLINT1&t;0x0004&t;&t;/* PLC1 */
DECL|macro|IS_PLINT2
mdefine_line|#define&t;IS_PLINT2&t;0x0008&t;&t;/* PLC2 */
DECL|macro|IS_TIMINT
mdefine_line|#define&t;IS_TIMINT&t;0x0010&t;&t;/* Timer 82C54-2 */
DECL|macro|IS_TOKEN
mdefine_line|#define&t;IS_TOKEN&t;0x0020&t;&t;/* restrictet token monitoring */
DECL|macro|IS_CHCK_L
mdefine_line|#define&t;IS_CHCK_L&t;0x0040&t;&t;/* check line asserted */
DECL|macro|IS_BUSERR
mdefine_line|#define&t;IS_BUSERR&t;0x0080&t;&t;/* bus error */
multiline_comment|/*&n; *&t;ISR2&n; */
DECL|macro|IS_TC
mdefine_line|#define&t;IS_TC&t;&t;0x0001&t;&t;/* terminal count irq */
DECL|macro|IS_SFDBKRTN
mdefine_line|#define IS_SFDBKRTN&t;0x0002&t;&t;/* selected feedback return */
DECL|macro|IS_D16
mdefine_line|#define IS_D16&t;&t;0x0004&t;&t;/* DS16 */
DECL|macro|IS_D32
mdefine_line|#define&t;IS_D32&t;&t;0x0008&t;&t;/* DS32 */
DECL|macro|IS_DPEI
mdefine_line|#define IS_DPEI&t;&t;0x0010&t;&t;/* Data Parity Indication */
DECL|macro|ALL_IRSR
mdefine_line|#define&t;ALL_IRSR&t;0x00ff
DECL|macro|FM_A
mdefine_line|#define&t;FM_A(a)&t;ADDR(FMA(a))&t;/* FORMAC Plus physical addr */
DECL|macro|P1_A
mdefine_line|#define&t;P1_A(a)&t;ADDR(P1(a))&t;/* PLC1 (r/w) */
DECL|macro|P2_A
mdefine_line|#define&t;P2_A(a)&t;ADDR(P2(a))&t;/* PLC2 (r/w) (DAS) */
DECL|macro|TI_A
mdefine_line|#define&t;TI_A(a)&t;ADDR(TI(a))&t;/* Timer (r/w) FM1 only! */
DECL|macro|PR_A
mdefine_line|#define&t;PR_A(a)&t;ADDR(PR(a))&t;/* config. PROM */
DECL|macro|CS_A
mdefine_line|#define&t;CS_A(a)&t;ADDR(CS(a))&t;/* control/status */
DECL|macro|ISR1_A
mdefine_line|#define&t;ISR1_A&t;ADDR(ISRA)&t;/* first int. source register address */
DECL|macro|ISR2_A
mdefine_line|#define&t;ISR2_A&t;ADDR(ISR2)&t;/* second&t;-&quot;-&t; */
DECL|macro|CSR_A
mdefine_line|#define&t;CSR_A&t;ADDR(CSRA)&t;/* control/status register address */
DECL|macro|CSF_A
mdefine_line|#define&t;CSF_A&t;ADDR(CSFA)&t;/* control/status FIFO BUSY flags (r/w) */
DECL|macro|CSIL_A
mdefine_line|#define&t;CSIL_A&t;ADDR(CSIL)&t;/* I/O mapped POS_ID_low (102) */
DECL|macro|CSIH_A
mdefine_line|#define&t;CSIH_A&t;ADDR(CSIH)&t;/*&t;- &quot; - POS_ID_HIGH (101) */
DECL|macro|CSA_A
mdefine_line|#define&t;CSA_A&t;ADDR(CSA)&t;/*&t;- &quot; - POS_102 */
DECL|macro|CSI_A
mdefine_line|#define&t;CSI_A&t;ADDR(CSI)&t;/*&t;- &quot; - POS_104 */
DECL|macro|CSM_A
mdefine_line|#define&t;CSM_A&t;ADDR(CSM)&t;/*&t;- &quot; - POS_103 */
DECL|macro|CSM_FM1_A
mdefine_line|#define&t;CSM_FM1_A&t;ADDR(CSM_FM1)&t;/*&t;- &quot; - POS_103 (2nd copy, FM1) */
DECL|macro|CSP_06_A
mdefine_line|#define&t;CSP_06_A&t;ADDR(CSP_06)&t;/*&t;- &quot; - POS_106 */
DECL|macro|WCT_A
mdefine_line|#define&t;WCT_A&t;ADDR(WCTA)&t;/* word counter (r/w) */
DECL|macro|FFLAG_A
mdefine_line|#define&t;FFLAG_A&t;ADDR(FFLAG)&t;/* FLAG/V_FULL (FIFO almost full, write only)*/
DECL|macro|ACL_A
mdefine_line|#define&t;ACL_A&t;ADDR(ACLA)&t;/* address counter low */
DECL|macro|ACH_A
mdefine_line|#define&t;ACH_A&t;ADDR(ACHA)&t;/* address counter high */
DECL|macro|BCN_A
mdefine_line|#define&t;BCN_A&t;ADDR(BCN)&t;/* byte counter */
DECL|macro|MUX_A
mdefine_line|#define&t;MUX_A&t;ADDR(MUX)&t;/* MUX-register */
DECL|macro|ISR_A
mdefine_line|#define&t;ISR_A&t;ADDR(ISRA)&t;/* Interrupt Source Register */
DECL|macro|FIFO_RESET_A
mdefine_line|#define&t;FIFO_RESET_A&t;ADDR(FIFO_RESET)&t;/* reset the FIFO */
DECL|macro|FIFO_EN_A
mdefine_line|#define&t;FIFO_EN_A&t;ADDR(FIFO_EN)&t;&t;/* enable the FIFO */
DECL|macro|WDOG_EN_A
mdefine_line|#define WDOG_EN_A&t;ADDR(WDOG_EN)&t;&t;/* reset and start the WDOG */
DECL|macro|WDOG_DIS_A
mdefine_line|#define WDOG_DIS_A&t;ADDR(WDOG_DIS)&t;&t;/* disable the WDOG */
multiline_comment|/*&n; * all control reg. (read!) are 8 bit (except PAGE_RG_A and LEDR_A)&n; */
DECL|macro|HSR_A
mdefine_line|#define&t;HSR_A(p)&t;ADDR(HSR(p))&t;/* Host request register */
DECL|macro|STAT_BYP
mdefine_line|#define&t;STAT_BYP&t;0&t;&t;/* bypass station */
DECL|macro|STAT_INS
mdefine_line|#define&t;STAT_INS&t;2&t;&t;/* insert station */
DECL|macro|BYPASS
mdefine_line|#define&t;BYPASS(o)&t;CS(0x10|(o))&t;/* o=STAT_BYP || STAT_INS */
DECL|macro|IRQ_TC_EN
mdefine_line|#define&t;IRQ_TC_EN&t;CS(0x0b)&t;/* enable/disable IRQ on TC */
DECL|macro|IRQ_TC_DIS
mdefine_line|#define&t;IRQ_TC_DIS&t;CS(0x0a)
DECL|macro|IRQ_TOKEN_EN
mdefine_line|#define&t;IRQ_TOKEN_EN&t;CS(9)&t;&t;/* enable/disable IRQ on restr. Token */
DECL|macro|IRQ_TOKEN_DIS
mdefine_line|#define&t;IRQ_TOKEN_DIS&t;CS(8)
DECL|macro|IRQ_CHCK_EN
mdefine_line|#define&t;IRQ_CHCK_EN&t;CS(7)&t;&t;/*&t;-&quot;-&t;IRQ after CHCK line */
DECL|macro|IRQ_CHCK_DIS
mdefine_line|#define&t;IRQ_CHCK_DIS&t;CS(6)
DECL|macro|IRQ_OTH_EN
mdefine_line|#define&t;IRQ_OTH_EN&t;CS(5)&t;&t;/*&t;-&quot;-&t;other IRQ&squot;s */
DECL|macro|IRQ_OTH_DIS
mdefine_line|#define&t;IRQ_OTH_DIS&t;CS(4)
DECL|macro|FIFO_EN
mdefine_line|#define&t;FIFO_EN&t;&t;CS(3)&t;&t;/* disable (reset), enable FIFO */
DECL|macro|FIFO_RESET
mdefine_line|#define&t;FIFO_RESET&t;CS(2)
DECL|macro|CARD_EN
mdefine_line|#define&t;CARD_EN&t;&t;CS(1)&t;&t;/* disable (reset), enable card */
DECL|macro|CARD_DIS
mdefine_line|#define&t;CARD_DIS&t;CS(0)
DECL|macro|LEDR_A
mdefine_line|#define&t;LEDR_A&t;&t;ADDR(LEDR)&t;/* D0=green, D1=yellow, D8=L2 */
DECL|macro|PAGE_RG_A
mdefine_line|#define&t;PAGE_RG_A&t;ADDR(CSM)&t;/* D&lt;2..0&gt; */
DECL|macro|IRQ_CHCK_EN_A
mdefine_line|#define&t;IRQ_CHCK_EN_A&t;ADDR(IRQ_CHCK_EN)
DECL|macro|IRQ_CHCK_DIS_A
mdefine_line|#define IRQ_CHCK_DIS_A&t;ADDR(IRQ_CHCK_DIS)
DECL|macro|GET_PAGE
mdefine_line|#define&t;GET_PAGE(bank)&t;outpw(PAGE_RG_A,(inpw(PAGE_RG_A) &amp;&bslash;&n;&t;&t;&t;&t;(~POS_PAGE)) |(int) (bank))
DECL|macro|VPP_ON
mdefine_line|#define&t;VPP_ON()&t;if (smc-&gt;hw.rev == FM1_REV) {&t;&bslash;&n;&t;&t;&t;&t;outpw(PAGE_RG_A,&t;&bslash;&n;&t;&t;&t;&t;(inpw(PAGE_RG_A) &amp; POS_PAGE) | PROG_EN); &bslash;&n;&t;&t;&t;}
DECL|macro|VPP_OFF
mdefine_line|#define&t;VPP_OFF()&t;if (smc-&gt;hw.rev == FM1_REV) {&t;&bslash;&n;&t;&t;&t;&t;outpw(PAGE_RG_A,(inpw(PAGE_RG_A) &amp; POS_PAGE)); &bslash;&n;&t;&t;&t;}
DECL|macro|SKFDDI_PSZ
mdefine_line|#define&t;SKFDDI_PSZ&t;16&t;&t;/* address PROM size */
DECL|macro|READ_PROM
mdefine_line|#define&t;READ_PROM(a)&t;((u_char)inp(a))
DECL|macro|GET_ISR
mdefine_line|#define&t;GET_ISR()&t;~inpw(ISR1_A)
macro_line|#ifndef&t;TCI
DECL|macro|CHECK_ISR
mdefine_line|#define&t;CHECK_ISR()&t;~inpw(ISR1_A)
DECL|macro|CHECK_ISR_SMP
mdefine_line|#define&t;CHECK_ISR_SMP(iop)&t;~inpw((iop)+ISRA)
macro_line|#else
DECL|macro|CHECK_ISR
mdefine_line|#define&t;CHECK_ISR()&t;&t;(~inpw(ISR1_A) | ~inpw(ISR2_A))
DECL|macro|CHECK_ISR_SMP
mdefine_line|#define&t;CHECK_ISR_SMP(iop)&t;(~inpw((iop)+ISRA) | ~inpw((iop)+ISR2))
macro_line|#endif
DECL|macro|DMA_BUSY
mdefine_line|#define&t;DMA_BUSY()&t;(inpw(CSF_A) &amp; CSF_BUSY_DMA)
DECL|macro|FIFO_BUSY
mdefine_line|#define&t;FIFO_BUSY()&t;(inpw(CSF_A) &amp; CSF_BUSY_FIFO)
DECL|macro|DMA_FIFO_BUSY
mdefine_line|#define&t;DMA_FIFO_BUSY()&t;(inpw(CSF_A) &amp; (CSF_BUSY_DMA | CSF_BUSY_FIFO))
DECL|macro|BUS_CHECK
mdefine_line|#define&t;BUS_CHECK() {&t;int i ; &bslash;&n;&t;&t;&t;if ((i = GET_ISR()) &amp; IS_BUSERR) &bslash;&n;&t;&t;&t;&t;SMT_PANIC(smc,HWM_E0020,HWM_E0020_MSG) ; &bslash;&n;&t;&t;&t;if (i &amp; IS_CHCK_L) &bslash;&n;&t;&t;&t;&t;SMT_PANIC(smc,HWM_E0014,HWM_E0014_MSG) ; &bslash;&n;&t;&t;}
DECL|macro|CHECK_DMA
mdefine_line|#define&t;CHECK_DMA() {&t;u_long k = 10000 ; &bslash;&n;&t;&t; while (k &amp;&amp; (DMA_BUSY())) { &bslash;&n;&t;&t;&t;k-- ; &bslash;&n;&t;&t;&t;BUS_CHECK() ; &bslash;&n;&t;&t; } &bslash;&n;&t;&t; if (!k) SMT_PANIC(smc,HWM_E0003,HWM_E0003_MSG) ; }
DECL|macro|CHECK_FIFO
mdefine_line|#define&t;CHECK_FIFO() {u_long k = 1000000 ;&bslash;&n;&t;&t; while (k &amp;&amp; (FIFO_BUSY())) k-- ;&bslash;&n;&t;&t; if (!k) SMT_PANIC(smc,HWM_E0019,HWM_E0019_MSG) ; }
DECL|macro|CHECK_DMA_FIFO
mdefine_line|#define&t;CHECK_DMA_FIFO() {u_long k = 1000000 ;&bslash;&n;&t;&t; while (k &amp;&amp; (DMA_FIFO_BUSY())) { &bslash;&n;&t;&t;&t;k-- ;&bslash;&n;&t;&t;&t;BUS_CHECK() ; &bslash;&n;&t;&t; } &bslash;&n;&t;&t; if (!k) SMT_PANIC(smc,HWM_E0004,HWM_E0004_MSG) ; }
macro_line|#ifndef UNIX
DECL|macro|CLI_FBI
mdefine_line|#define&t;CLI_FBI()&t;outp(ADDR(IRQ_OTH_DIS),0)
macro_line|#else
DECL|macro|CLI_FBI
mdefine_line|#define&t;CLI_FBI(smc)&t;outp(ADDRS((smc),IRQ_OTH_DIS),0)
macro_line|#endif
macro_line|#ifndef&t;TCI
DECL|macro|CLI_FBI_SMP
mdefine_line|#define&t;CLI_FBI_SMP(iop)&t;outp((iop)+IRQ_OTH_DIS,0)
macro_line|#else
DECL|macro|CLI_FBI_SMP
mdefine_line|#define&t;CLI_FBI_SMP(iop)&t;outp((iop)+IRQ_OTH_DIS,0) ;&bslash;&n;&t;&t;&t;&t;outp((iop)+IRQ_TC_DIS,0)
macro_line|#endif
macro_line|#ifndef UNIX
DECL|macro|STI_FBI
mdefine_line|#define&t;STI_FBI()&t;outp(ADDR(IRQ_OTH_EN),0)
macro_line|#else
DECL|macro|STI_FBI
mdefine_line|#define&t;STI_FBI(smc)&t;outp(ADDRS((smc),IRQ_OTH_EN),0)
macro_line|#endif
multiline_comment|/*&n; * Terminal count primitives&n; */
DECL|macro|CLI_TCI
mdefine_line|#define CLI_TCI(smc)&t;outp(ADDRS((smc),IRQ_TC_DIS),0)
DECL|macro|STI_TCI
mdefine_line|#define STI_TCI(smc)&t;outp(ADDRS((smc),IRQ_TC_EN),0)
DECL|macro|CHECK_TC
mdefine_line|#define CHECK_TC(smc,k)&t;{(k) = 10000 ;&bslash;&n;&t;while ((k) &amp;&amp; (~inpw(ISR2_A) &amp; IS_TC)) (k)-- ;&bslash;&n;&t;if (!k) SMT_PANIC(smc,HWM_E0018,HWM_E0018_MSG) ; }
macro_line|#endif&t;/* MCA */
macro_line|#ifdef&t;ISA
multiline_comment|/*&n; * address transmission from logic NPADDR6-0 to physical offset address on board&n; */
DECL|macro|FMA
mdefine_line|#define FMA(a)&t;(0x8000|(((a)&amp;0x07)&lt;&lt;1)|(((a)&amp;0x78)&lt;&lt;7))  /* FORMAC+ (r/w) */
DECL|macro|PRA
mdefine_line|#define PRA(a)&t;(0x1000|(((a)&amp;0x07)&lt;&lt;1)|(((a)&amp;0x18)&lt;&lt;7))  /* PROM (read only)*/
DECL|macro|P1A
mdefine_line|#define P1A(a)&t;(0x4000|(((a)&amp;0x07)&lt;&lt;1)|(((a)&amp;0x18)&lt;&lt;7))  /* PLC1 (r/w) */
DECL|macro|P2A
mdefine_line|#define P2A(a)&t;(0x5000|(((a)&amp;0x07)&lt;&lt;1)|(((a)&amp;0x18)&lt;&lt;7))  /* PLC2 (r/w) */
DECL|macro|TIA
mdefine_line|#define TIA(a)&t;(0x6000|(((a)&amp;0x03)&lt;&lt;1))&t;&t;  /* Timer (r/w) */
DECL|macro|ISRA
mdefine_line|#define&t;ISRA&t;0x0000&t;&t;/* int. source register address (read only) */
DECL|macro|ACLA
mdefine_line|#define&t;ACLA&t;0x0000&t;&t;/* address counter low address (write only) */
DECL|macro|ACHA
mdefine_line|#define&t;ACHA&t;0x0002&t;&t;/* address counter high address (write only) */
DECL|macro|TRCA
mdefine_line|#define&t;TRCA&t;0x0004&t;&t;/* transfer counter address (write only) */
DECL|macro|PGRA
mdefine_line|#define&t;PGRA&t;0x0006&t;&t;/* page register address (write only) */
DECL|macro|RQAA
mdefine_line|#define RQAA&t;0x2000&t;&t;/* Request reg. (write only) */
DECL|macro|CSRA
mdefine_line|#define&t;CSRA&t;0x3000&t;&t;/* control/status register address (r/w) */
multiline_comment|/*&n; * physical address offset + IO-Port base address&n; */
DECL|macro|FM_A
mdefine_line|#define FM_A(a)&t;(FMA(a)+smc-&gt;hw.iop)&t;/* FORMAC Plus physical addr */
DECL|macro|PR_A
mdefine_line|#define PR_A(a)&t;(PRA(a)+smc-&gt;hw.iop)&t;/* PROM (read only)*/
DECL|macro|P1_A
mdefine_line|#define P1_A(a)&t;(P1A(a)+smc-&gt;hw.iop)&t;/* PLC1 (r/w) */
DECL|macro|P2_A
mdefine_line|#define P2_A(a)&t;(P2A(a)+smc-&gt;hw.iop)&t;/* PLC2 (r/w) */
DECL|macro|TI_A
mdefine_line|#define TI_A(a)&t;(TIA(a)+smc-&gt;hw.iop)&t;/* Timer (r/w) */
DECL|macro|ISR_A
mdefine_line|#define&t;ISR_A&t;(0x0000+smc-&gt;hw.iop) /* int. source register address (read only) */
DECL|macro|ACL_A
mdefine_line|#define&t;ACL_A&t;(0x0000+smc-&gt;hw.iop) /* address counter low address (write only) */
DECL|macro|ACH_A
mdefine_line|#define&t;ACH_A&t;(0x0002+smc-&gt;hw.iop) /* address counter high address (write only)*/
DECL|macro|TRC_A
mdefine_line|#define&t;TRC_A&t;(0x0004+smc-&gt;hw.iop) /* transfer counter address (write only) */
DECL|macro|PGR_A
mdefine_line|#define&t;PGR_A&t;(0x0006+smc-&gt;hw.iop) /* page register address (write only) */
DECL|macro|RQA_A
mdefine_line|#define RQA_A&t;(0x2000+smc-&gt;hw.iop) /* Request reg. (write only) */
DECL|macro|CSR_A
mdefine_line|#define&t;CSR_A&t;(0x3000+smc-&gt;hw.iop) /* control/status register address (r/w) */
macro_line|#ifdef UNIX
DECL|macro|CSR_AS
mdefine_line|#define&t;CSR_AS(smc) (0x3000+(smc)-&gt;hw.iop) /* control/status register address */
macro_line|#endif
DECL|macro|PLC1_I
mdefine_line|#define&t;PLC1_I&t;(0x3400+smc-&gt;hw.iop) /* clear PLC1 interrupt bit */
DECL|macro|PLC2_I
mdefine_line|#define&t;PLC2_I&t;(0x3800+smc-&gt;hw.iop) /* clear PLC2 interrupt bit */
macro_line|#ifndef&t;MULT_OEM
macro_line|#ifndef&t;OEM_CONCEPT
DECL|macro|SKLOGO_STR
mdefine_line|#define&t;SKLOGO_STR&t;&quot;SKFDDI&quot;
macro_line|#else&t;/* OEM_CONCEPT */
DECL|macro|SKLOGO_STR
mdefine_line|#define&t;SKLOGO_STR&t;OEM_FDDI_LOGO
macro_line|#endif&t;/* OEM_CONCEPT */
macro_line|#endif  /* MULT_OEM */
DECL|macro|SADDRL
mdefine_line|#define&t;SADDRL&t;(24)&t;&t;/* start address SKLOGO */
DECL|macro|SA_MAC
mdefine_line|#define&t;SA_MAC&t;(0)&t;&t;/* start addr. MAC_AD within the PROM */
DECL|macro|PRA_OFF
mdefine_line|#define&t;PRA_OFF&t;(0)
DECL|macro|SA_PMD_TYPE
mdefine_line|#define SA_PMD_TYPE&t;(8)&t;/* start addr. PMD-Type */
DECL|macro|CDID
mdefine_line|#define&t;CDID&t;(PRA(SADDRL))&t;/* Card ID int/O port addr. offset */
DECL|macro|NEXT_CDID
mdefine_line|#define&t;NEXT_CDID&t;((PRA(SADDRL+1)) - CDID)
DECL|macro|SKFDDI_PSZ
mdefine_line|#define&t;SKFDDI_PSZ&t;32&t;&t;/* address PROM size */
DECL|macro|READ_PROM
mdefine_line|#define&t;READ_PROM(a)&t;((u_char)inpw(a))
DECL|macro|GET_PAGE
mdefine_line|#define&t;GET_PAGE(i)&t;outpw(PGR_A,(int)(i))
DECL|macro|MAX_PAGES
mdefine_line|#define&t;MAX_PAGES&t;16&t;&t;/* 16 pages */
DECL|macro|MAX_FADDR
mdefine_line|#define&t;MAX_FADDR&t;0x2000&t;&t;/* 8K per page */
DECL|macro|VPP_OFF
mdefine_line|#define&t;VPP_OFF()&t;outpw(CSR_A,(inpw(CSR_A) &amp; (CS_CRESET|CS_BYPASS)))
DECL|macro|VPP_ON
mdefine_line|#define&t;VPP_ON()&t;outpw(CSR_A,(inpw(CSR_A) &amp; (CS_CRESET|CS_BYPASS)) | &bslash;&n;&t;&t;&t;&t;CS_VPPSW)
multiline_comment|/*&n; * control/status register CSRA&t;bits (log. addr: 0x3000)&n; */
multiline_comment|/* write */
DECL|macro|CS_CRESET
mdefine_line|#define CS_CRESET&t;0x01&t;&t;/* Card reset (0=reset) */
DECL|macro|CS_IMSK
mdefine_line|#define&t;CS_IMSK&t;&t;0x02&t;&t;/* enable IRQ (1=enable, 0=disable) */
DECL|macro|CS_RESINT1
mdefine_line|#define CS_RESINT1&t;0x04&t;&t;/* PLINT1 reset */
DECL|macro|CS_VPPSW
mdefine_line|#define&t;CS_VPPSW&t;0x10&t;&t;/* 12V power switch (0=off, 1=on) */
DECL|macro|CS_BYPASS
mdefine_line|#define CS_BYPASS&t;0x20&t;&t;/* bypass switch (0=remove, 1=insert)*/
DECL|macro|CS_RESINT2
mdefine_line|#define CS_RESINT2&t;0x40&t;&t;/* PLINT2 reset */
multiline_comment|/* read */
DECL|macro|CS_BUSY
mdefine_line|#define&t;CS_BUSY&t;&t;0x04&t;&t;/* master transfer activ (=1) */
DECL|macro|CS_SW_EPROM
mdefine_line|#define&t;CS_SW_EPROM&t;0x08&t;&t;/* 0=Application Soft. 1=BOOT-EPROM */
DECL|macro|CS_BYSTAT
mdefine_line|#define&t;CS_BYSTAT&t;0x40&t;&t;/* 0=Bypass exist, 1= ..not */
DECL|macro|CS_SAS
mdefine_line|#define&t;CS_SAS&t;&t;0x80&t;&t;/* single attachement station (=1) */
multiline_comment|/*&n; * Interrupt source register ISRA (log. addr: 0x0000) read only &amp; low activ.&n; */
DECL|macro|IS_MINTR1
mdefine_line|#define IS_MINTR1&t;0x01&t;&t;/* FORMAC ST1U/L &amp;&amp; ~IMSK1U/L*/
DECL|macro|IS_MINTR2
mdefine_line|#define IS_MINTR2&t;0x02&t;&t;/* FORMAC ST2U/L &amp;&amp; ~IMSK2U/L*/
DECL|macro|IS_PLINT1
mdefine_line|#define IS_PLINT1&t;0x04&t;&t;/* PLC1 */
DECL|macro|IS_PLINT2
mdefine_line|#define IS_PLINT2&t;0x08&t;&t;/* PLC2 */
DECL|macro|IS_TIMINT
mdefine_line|#define IS_TIMINT&t;0x10&t;&t;/* Timer 82C54-2 */
DECL|macro|ALL_IRSR
mdefine_line|#define&t;ALL_IRSR&t;(IS_MINTR1|IS_MINTR2|IS_PLINT1|IS_PLINT2|IS_TIMINT)
DECL|macro|FPROM_SW
mdefine_line|#define&t;FPROM_SW()&t;(inpw(CSR_A)&amp;CS_SW_EPROM)
DECL|macro|DMA_BUSY
mdefine_line|#define&t;DMA_BUSY()&t;(inpw(CSR_A)&amp;CS_BUSY)
DECL|macro|CHECK_FIFO
mdefine_line|#define CHECK_FIFO()
DECL|macro|BUS_CHECK
mdefine_line|#define&t;BUS_CHECK()
multiline_comment|/*&n; * set Host Request register (wr.)&n; */
DECL|macro|SET_HRQ
mdefine_line|#define SET_HRQ(qup)&t;outpw(RQA_A+((qup)&lt;&lt;1),0)
macro_line|#ifndef UNIX
macro_line|#ifndef WINNT
DECL|macro|CLI_FBI
mdefine_line|#define&t;CLI_FBI()&t;outpw(CSR_A,(inpw(CSR_A)&amp;(CS_CRESET|CS_BYPASS|CS_VPPSW)))
macro_line|#else
DECL|macro|CLI_FBI
mdefine_line|#define&t;CLI_FBI()&t;outpw(CSR_A,(l_inpw(CSR_A) &amp; &bslash;&n;&t;&t;&t;&t;(CS_CRESET|CS_BYPASS|CS_VPPSW)))
macro_line|#endif
macro_line|#else
DECL|macro|CLI_FBI
mdefine_line|#define&t;CLI_FBI(smc)&t;outpw(CSR_AS(smc),(inpw(CSR_AS(smc))&amp; &bslash;&n;&t;&t;&t;&t;&t;&t;(CS_CRESET|CS_BYPASS|CS_VPPSW)))
macro_line|#endif
macro_line|#ifndef UNIX
DECL|macro|STI_FBI
mdefine_line|#define&t;STI_FBI()&t;outpw(CSR_A,(inpw(CSR_A) &amp; &bslash;&n;&t;&t;&t;&t;(CS_CRESET|CS_BYPASS|CS_VPPSW)) | CS_IMSK)
macro_line|#else
DECL|macro|STI_FBI
mdefine_line|#define&t;STI_FBI(smc)&t;outpw(CSR_AS(smc),(inpw(CSR_AS(smc)) &amp; &bslash;&n;&t;&t;&t;&t;(CS_CRESET|CS_BYPASS|CS_VPPSW)) | CS_IMSK)
macro_line|#endif
DECL|macro|CHECK_DMA
mdefine_line|#define CHECK_DMA()&t;{unsigned k = 10000 ;&bslash;&n;&t;&t;&t;while (k &amp;&amp; (DMA_BUSY())) k-- ;&bslash;&n;&t;&t;&t;if (!k) SMT_PANIC(smc,HWM_E0003,HWM_E0003_MSG) ; }
DECL|macro|GET_ISR
mdefine_line|#define&t;GET_ISR()&t;~inpw(ISR_A)
macro_line|#endif&t;/* ISA */
multiline_comment|/*--------------------------------------------------------------------------*/
macro_line|#ifdef&t;PCI
multiline_comment|/*&n; *&t;(DV)&t;= only defined for Da Vinci&n; *&t;(ML)&t;= only defined for Monalisa&n; */
multiline_comment|/*&n; * Configuration Space header&n; */
DECL|macro|PCI_VENDOR_ID
mdefine_line|#define&t;PCI_VENDOR_ID&t;0x00&t;/* 16 bit&t;Vendor ID */
DECL|macro|PCI_DEVICE_ID
mdefine_line|#define&t;PCI_DEVICE_ID&t;0x02&t;/* 16 bit&t;Device ID */
DECL|macro|PCI_COMMAND
mdefine_line|#define&t;PCI_COMMAND&t;0x04&t;/* 16 bit&t;Command */
DECL|macro|PCI_STATUS
mdefine_line|#define&t;PCI_STATUS&t;0x06&t;/* 16 bit&t;Status */
DECL|macro|PCI_REV_ID
mdefine_line|#define&t;PCI_REV_ID&t;0x08&t;/*  8 bit&t;Revision ID */
DECL|macro|PCI_CLASS_CODE
mdefine_line|#define&t;PCI_CLASS_CODE&t;0x09&t;/* 24 bit&t;Class Code */
DECL|macro|PCI_CACHE_LSZ
mdefine_line|#define&t;PCI_CACHE_LSZ&t;0x0c&t;/*  8 bit&t;Cache Line Size */
DECL|macro|PCI_LAT_TIM
mdefine_line|#define&t;PCI_LAT_TIM&t;0x0d&t;/*  8 bit&t;Latency Timer */
DECL|macro|PCI_HEADER_T
mdefine_line|#define&t;PCI_HEADER_T&t;0x0e&t;/*  8 bit&t;Header Type */
DECL|macro|PCI_BIST
mdefine_line|#define&t;PCI_BIST&t;0x0f&t;/*  8 bit&t;Built-in selftest */
DECL|macro|PCI_BASE_1ST
mdefine_line|#define&t;PCI_BASE_1ST&t;0x10&t;/* 32 bit&t;1st Base address */
DECL|macro|PCI_BASE_2ND
mdefine_line|#define&t;PCI_BASE_2ND&t;0x14&t;/* 32 bit&t;2nd Base address */
multiline_comment|/* Byte 18..2b:&t;Reserved */
DECL|macro|PCI_SUB_VID
mdefine_line|#define&t;PCI_SUB_VID&t;0x2c&t;/* 16 bit&t;Subsystem Vendor ID */
DECL|macro|PCI_SUB_ID
mdefine_line|#define&t;PCI_SUB_ID&t;0x2e&t;/* 16 bit&t;Subsystem ID */
DECL|macro|PCI_BASE_ROM
mdefine_line|#define&t;PCI_BASE_ROM&t;0x30&t;/* 32 bit&t;Expansion ROM Base Address */
multiline_comment|/* Byte 34..33:&t;Reserved */
DECL|macro|PCI_CAP_PTR
mdefine_line|#define PCI_CAP_PTR&t;0x34&t;/*  8 bit (ML)&t;Capabilities Ptr */
multiline_comment|/* Byte 35..3b:&t;Reserved */
DECL|macro|PCI_IRQ_LINE
mdefine_line|#define&t;PCI_IRQ_LINE&t;0x3c&t;/*  8 bit&t;Interrupt Line */
DECL|macro|PCI_IRQ_PIN
mdefine_line|#define&t;PCI_IRQ_PIN&t;0x3d&t;/*  8 bit&t;Interrupt Pin */
DECL|macro|PCI_MIN_GNT
mdefine_line|#define&t;PCI_MIN_GNT&t;0x3e&t;/*  8 bit&t;Min_Gnt */
DECL|macro|PCI_MAX_LAT
mdefine_line|#define&t;PCI_MAX_LAT&t;0x3f&t;/*  8 bit&t;Max_Lat */
multiline_comment|/* Device Dependent Region */
DECL|macro|PCI_OUR_REG
mdefine_line|#define&t;PCI_OUR_REG&t;0x40&t;/* 32 bit (DV)&t;Our Register */
DECL|macro|PCI_OUR_REG_1
mdefine_line|#define&t;PCI_OUR_REG_1&t;0x40&t;/* 32 bit (ML)&t;Our Register 1 */
DECL|macro|PCI_OUR_REG_2
mdefine_line|#define&t;PCI_OUR_REG_2&t;0x44&t;/* 32 bit (ML)&t;Our Register 2 */
multiline_comment|/* Power Management Region */
DECL|macro|PCI_PM_CAP_ID
mdefine_line|#define PCI_PM_CAP_ID&t;0x48&t;/*  8 bit (ML)&t;Power Management Cap. ID */
DECL|macro|PCI_PM_NITEM
mdefine_line|#define PCI_PM_NITEM&t;0x49&t;/*  8 bit (ML)&t;Next Item Ptr */
DECL|macro|PCI_PM_CAP_REG
mdefine_line|#define PCI_PM_CAP_REG&t;0x4a&t;/* 16 bit (ML)&t;Power Management Capabilities */
DECL|macro|PCI_PM_CTL_STS
mdefine_line|#define PCI_PM_CTL_STS&t;0x4c&t;/* 16 bit (ML)&t;Power Manag. Control/Status */
multiline_comment|/* Byte 0x4e:&t;Reserved */
DECL|macro|PCI_PM_DAT_REG
mdefine_line|#define PCI_PM_DAT_REG&t;0x4f&t;/*  8 bit (ML)&t;Power Manag. Data Register */
multiline_comment|/* VPD Region */
DECL|macro|PCI_VPD_CAP_ID
mdefine_line|#define&t;PCI_VPD_CAP_ID&t;0x50&t;/*  8 bit (ML)&t;VPD Cap. ID */
DECL|macro|PCI_VPD_NITEM
mdefine_line|#define PCI_VPD_NITEM&t;0x51&t;/*  8 bit (ML)&t;Next Item Ptr */
DECL|macro|PCI_VPD_ADR_REG
mdefine_line|#define PCI_VPD_ADR_REG&t;0x52&t;/* 16 bit (ML)&t;VPD Address Register */
DECL|macro|PCI_VPD_DAT_REG
mdefine_line|#define PCI_VPD_DAT_REG&t;0x54&t;/* 32 bit (ML)&t;VPD Data Register */
multiline_comment|/* Byte 58..ff:&t;Reserved */
multiline_comment|/*&n; * I2C Address (PCI Config)&n; *&n; * Note: The temperature and voltage sensors are relocated on a different&n; *&t; I2C bus.&n; */
DECL|macro|I2C_ADDR_VPD
mdefine_line|#define I2C_ADDR_VPD&t;0xA0&t;/* I2C address for the VPD EEPROM */ 
multiline_comment|/*&n; * Define Bits and Values of the registers&n; */
multiline_comment|/*&t;PCI_VENDOR_ID&t;16 bit&t;Vendor ID */
multiline_comment|/*&t;PCI_DEVICE_ID&t;16 bit&t;Device ID */
multiline_comment|/* Values for Vendor ID and Device ID shall be patched into the code */
multiline_comment|/*&t;PCI_COMMAND&t;16 bit&t;Command */
DECL|macro|PCI_FBTEN
mdefine_line|#define&t;PCI_FBTEN&t;0x0200&t;/* Bit 9:&t;Fast Back-To-Back enable */
DECL|macro|PCI_SERREN
mdefine_line|#define&t;PCI_SERREN&t;0x0100&t;/* Bit 8:&t;SERR enable */
DECL|macro|PCI_ADSTEP
mdefine_line|#define&t;PCI_ADSTEP&t;0x0080&t;/* Bit 7:&t;Address Stepping */
DECL|macro|PCI_PERREN
mdefine_line|#define&t;PCI_PERREN&t;0x0040&t;/* Bit 6:&t;Parity Report Response enable */
DECL|macro|PCI_VGA_SNOOP
mdefine_line|#define&t;PCI_VGA_SNOOP&t;0x0020&t;/* Bit 5:&t;VGA palette snoop */
DECL|macro|PCI_MWIEN
mdefine_line|#define&t;PCI_MWIEN&t;0x0010&t;/* Bit 4:&t;Memory write an inv cycl ena */
DECL|macro|PCI_SCYCEN
mdefine_line|#define&t;PCI_SCYCEN&t;0x0008&t;/* Bit 3:&t;Special Cycle enable */
DECL|macro|PCI_BMEN
mdefine_line|#define&t;PCI_BMEN&t;0x0004&t;/* Bit 2:&t;Bus Master enable */
DECL|macro|PCI_MEMEN
mdefine_line|#define&t;PCI_MEMEN&t;0x0002&t;/* Bit 1:&t;Memory Space Access enable */
DECL|macro|PCI_IOEN
mdefine_line|#define&t;PCI_IOEN&t;0x0001&t;/* Bit 0:&t;IO Space Access enable */
multiline_comment|/*&t;PCI_STATUS&t;16 bit&t;Status */
DECL|macro|PCI_PERR
mdefine_line|#define&t;PCI_PERR&t;0x8000&t;/* Bit 15:&t;Parity Error */
DECL|macro|PCI_SERR
mdefine_line|#define&t;PCI_SERR&t;0x4000&t;/* Bit 14:&t;Signaled SERR */
DECL|macro|PCI_RMABORT
mdefine_line|#define&t;PCI_RMABORT&t;0x2000&t;/* Bit 13:&t;Received Master Abort */
DECL|macro|PCI_RTABORT
mdefine_line|#define&t;PCI_RTABORT&t;0x1000&t;/* Bit 12:&t;Received Target Abort */
DECL|macro|PCI_STABORT
mdefine_line|#define&t;PCI_STABORT&t;0x0800&t;/* Bit 11:&t;Sent Target Abort */
DECL|macro|PCI_DEVSEL
mdefine_line|#define&t;PCI_DEVSEL&t;0x0600&t;/* Bit 10..9:&t;DEVSEL Timing */
DECL|macro|PCI_DEV_FAST
mdefine_line|#define&t;PCI_DEV_FAST&t;(0&lt;&lt;9)&t;/*&t;&t;fast */
DECL|macro|PCI_DEV_MEDIUM
mdefine_line|#define&t;PCI_DEV_MEDIUM&t;(1&lt;&lt;9)&t;/*&t;&t;medium */
DECL|macro|PCI_DEV_SLOW
mdefine_line|#define&t;PCI_DEV_SLOW&t;(2&lt;&lt;9)&t;/*&t;&t;slow */
DECL|macro|PCI_DATAPERR
mdefine_line|#define&t;PCI_DATAPERR&t;0x0100&t;/* Bit 8:&t;DATA Parity error detected */
DECL|macro|PCI_FB2BCAP
mdefine_line|#define&t;PCI_FB2BCAP&t;0x0080&t;/* Bit 7:&t;Fast Back-to-Back Capability */
DECL|macro|PCI_UDF
mdefine_line|#define&t;PCI_UDF&t;&t;0x0040&t;/* Bit 6:&t;User Defined Features */
DECL|macro|PCI_66MHZCAP
mdefine_line|#define PCI_66MHZCAP&t;0x0020&t;/* Bit 5:&t;66 MHz PCI bus clock capable */
DECL|macro|PCI_NEWCAP
mdefine_line|#define PCI_NEWCAP&t;0x0010&t;/* Bit 4:&t;New cap. list implemented */
DECL|macro|PCI_ERRBITS
mdefine_line|#define PCI_ERRBITS&t;(PCI_PERR|PCI_SERR|PCI_RMABORT|PCI_STABORT|PCI_DATAPERR)
multiline_comment|/*&t;PCI_REV_ID&t;8 bit&t;Revision ID */
multiline_comment|/*&t;PCI_CLASS_CODE&t;24 bit&t;Class Code */
multiline_comment|/*&t;Byte 2:&t;&t;Base Class&t;&t;(02) */
multiline_comment|/*&t;Byte 1:&t;&t;SubClass&t;&t;(02) */
multiline_comment|/*&t;Byte 0:&t;&t;Programming Interface&t;(00) */
multiline_comment|/*&t;PCI_CACHE_LSZ&t;8 bit&t;Cache Line Size */
multiline_comment|/*&t;Possible values: 0,2,4,8,16&t;*/
multiline_comment|/*&t;PCI_LAT_TIM&t;8 bit&t;Latency Timer */
multiline_comment|/*&t;PCI_HEADER_T&t;8 bit&t;Header Type */
DECL|macro|PCI_HD_MF_DEV
mdefine_line|#define&t;PCI_HD_MF_DEV&t;0x80&t;/* Bit 7:&t;0= single, 1= multi-func dev */
DECL|macro|PCI_HD_TYPE
mdefine_line|#define&t;PCI_HD_TYPE&t;0x7f&t;/* Bit 6..0:&t;Header Layout 0= normal */
multiline_comment|/*&t;PCI_BIST&t;8 bit&t;Built-in selftest */
DECL|macro|PCI_BIST_CAP
mdefine_line|#define&t;PCI_BIST_CAP&t;0x80&t;/* Bit 7:&t;BIST Capable */
DECL|macro|PCI_BIST_ST
mdefine_line|#define&t;PCI_BIST_ST&t;0x40&t;/* Bit 6:&t;Start BIST */
DECL|macro|PCI_BIST_RET
mdefine_line|#define&t;PCI_BIST_RET&t;0x0f&t;/* Bit 3..0:&t;Completion Code */
multiline_comment|/*&t;PCI_BASE_1ST&t;32 bit&t;1st Base address */
DECL|macro|PCI_MEMSIZE
mdefine_line|#define&t;PCI_MEMSIZE&t;0x800L       /* use 2 kB Memory Base */
DECL|macro|PCI_MEMBASE_BITS
mdefine_line|#define&t;PCI_MEMBASE_BITS 0xfffff800L /* Bit 31..11:&t;Memory Base Address */
DECL|macro|PCI_MEMSIZE_BIIS
mdefine_line|#define&t;PCI_MEMSIZE_BIIS 0x000007f0L /* Bit 10..4:&t;Memory Size Req. */
DECL|macro|PCI_PREFEN
mdefine_line|#define&t;PCI_PREFEN&t;0x00000008L  /* Bit 3:&t;&t;Prefetchable */
DECL|macro|PCI_MEM_TYP
mdefine_line|#define&t;PCI_MEM_TYP&t;0x00000006L  /* Bit 2..1:&t;Memory Type */
DECL|macro|PCI_MEM32BIT
mdefine_line|#define&t;PCI_MEM32BIT&t;(0&lt;&lt;1)&t;     /* Base addr anywhere in 32 Bit range */
DECL|macro|PCI_MEM1M
mdefine_line|#define&t;PCI_MEM1M&t;(1&lt;&lt;1)&t;     /* Base addr below 1 MegaByte */
DECL|macro|PCI_MEM64BIT
mdefine_line|#define&t;PCI_MEM64BIT&t;(2&lt;&lt;1)&t;     /* Base addr anywhere in 64 Bit range */
DECL|macro|PCI_MEMSPACE
mdefine_line|#define&t;PCI_MEMSPACE&t;0x00000001L  /* Bit 0:&t;Memory Space Indic. */
multiline_comment|/*&t;PCI_BASE_2ND&t;32 bit&t;2nd Base address */
DECL|macro|PCI_IOBASE
mdefine_line|#define&t;PCI_IOBASE&t;0xffffff00L  /* Bit 31..8:  I/O Base address */
DECL|macro|PCI_IOSIZE
mdefine_line|#define&t;PCI_IOSIZE&t;0x000000fcL  /* Bit 7..2:   I/O Size Requirements */
DECL|macro|PCI_IOSPACE
mdefine_line|#define&t;PCI_IOSPACE&t;0x00000001L  /* Bit 0:&t;    I/O Space Indicator */
multiline_comment|/*&t;PCI_SUB_VID&t;16 bit&t;Subsystem Vendor ID */
multiline_comment|/*&t;PCI_SUB_ID&t;16 bit&t;Subsystem ID */
multiline_comment|/*&t;PCI_BASE_ROM&t;32 bit&t;Expansion ROM Base Address */
DECL|macro|PCI_ROMBASE
mdefine_line|#define&t;PCI_ROMBASE&t;0xfffe0000L  /* Bit 31..17: ROM BASE address (1st) */
DECL|macro|PCI_ROMBASZ
mdefine_line|#define&t;PCI_ROMBASZ&t;0x0001c000L  /* Bit 16..14: Treat as BASE or SIZE */
DECL|macro|PCI_ROMSIZE
mdefine_line|#define&t;PCI_ROMSIZE&t;0x00003800L  /* Bit 13..11: ROM Size Requirements */
DECL|macro|PCI_ROMEN
mdefine_line|#define&t;PCI_ROMEN&t;0x00000001L  /* Bit 0:&t;    Address Decode enable */
multiline_comment|/*&t;PCI_CAP_PTR&t;8 bit&t;New Capabilities Pointers */
multiline_comment|/*&t;PCI_IRQ_LINE&t;8 bit&t;Interrupt Line */
multiline_comment|/*&t;PCI_IRQ_PIN&t;8 bit&t;Interrupt Pin */
multiline_comment|/*&t;PCI_MIN_GNT&t;8 bit&t;Min_Gnt */
multiline_comment|/*&t;PCI_MAX_LAT&t;8 bit&t;Max_Lat */
multiline_comment|/* Device Dependent Region */
multiline_comment|/*&t;PCI_OUR_REG&t;(DV)&t;32 bit&t;Our Register */
multiline_comment|/*&t;PCI_OUR_REG_1&t;(ML)&t;32 bit&t;Our Register 1 */
multiline_comment|/*&t; Bit 31..29:&t;reserved */
DECL|macro|PCI_PATCH_DIR
mdefine_line|#define&t;PCI_PATCH_DIR&t;(3L&lt;&lt;27)  /*(DV) Bit 28..27:&t;Ext Patchs direction */
DECL|macro|PCI_PATCH_DIR_0
mdefine_line|#define PCI_PATCH_DIR_0&t;(1L&lt;&lt;27)  /*(DV) Type of the pins EXT_PATCHS&lt;1..0&gt;   */
DECL|macro|PCI_PATCH_DIR_1
mdefine_line|#define PCI_PATCH_DIR_1 (1L&lt;&lt;28)  /*&t;   0 = input&t;&t;&t;     */
multiline_comment|/*&t;   1 = output&t;&t;&t;     */
DECL|macro|PCI_EXT_PATCHS
mdefine_line|#define&t;PCI_EXT_PATCHS&t;(3L&lt;&lt;25)  /*(DV) Bit 26..25:&t;Extended Patches     */
DECL|macro|PCI_EXT_PATCH_0
mdefine_line|#define PCI_EXT_PATCH_0 (1L&lt;&lt;25)  /*(DV)&t;&t;&t;&t;     */
DECL|macro|PCI_EXT_PATCH_1
mdefine_line|#define PCI_EXT_PATCH_1 (1L&lt;&lt;26)  /*&t; CLK for MicroWire (ML)&t;&t;     */
DECL|macro|PCI_VIO
mdefine_line|#define PCI_VIO&t;&t;(1L&lt;&lt;25)  /*(ML)&t;&t;&t;&t;     */
DECL|macro|PCI_EN_BOOT
mdefine_line|#define&t;PCI_EN_BOOT&t;(1L&lt;&lt;24)  /*&t; Bit 24:&t;Enable BOOT via ROM  */
multiline_comment|/*&t;   1 = Don&squot;t boot with ROM&t;     */
multiline_comment|/*&t;   0 = Boot with ROM&t;&t;     */
DECL|macro|PCI_EN_IO
mdefine_line|#define&t;PCI_EN_IO&t;(1L&lt;&lt;23)  /*&t; Bit 23:&t;Mapping to IO space  */
DECL|macro|PCI_EN_FPROM
mdefine_line|#define&t;PCI_EN_FPROM&t;(1L&lt;&lt;22)  /*&t; Bit 22:&t;FLASH mapped to mem? */
multiline_comment|/*&t;   1 = Map Flash to Memory&t;     */
multiline_comment|/*&t;   0 = Disable all addr. decoding    */
DECL|macro|PCI_PAGESIZE
mdefine_line|#define&t;PCI_PAGESIZE&t;(3L&lt;&lt;20)  /*&t; Bit 21..20:&t;FLASH Page Size&t;     */
DECL|macro|PCI_PAGE_16
mdefine_line|#define&t;PCI_PAGE_16&t;(0L&lt;&lt;20)  /*&t;&t;16 k pages&t;&t;     */
DECL|macro|PCI_PAGE_32K
mdefine_line|#define&t;PCI_PAGE_32K&t;(1L&lt;&lt;20)  /*&t;&t;32 k pages&t;&t;     */
DECL|macro|PCI_PAGE_64K
mdefine_line|#define&t;PCI_PAGE_64K&t;(2L&lt;&lt;20)  /*&t;&t;64 k pages&t;&t;     */
DECL|macro|PCI_PAGE_128K
mdefine_line|#define&t;PCI_PAGE_128K&t;(3L&lt;&lt;20)  /*&t;&t;128 k pages&t;&t;     */
multiline_comment|/*&t; Bit 19: reserved (ML) and (DV)&t;     */
DECL|macro|PCI_PAGEREG
mdefine_line|#define&t;PCI_PAGEREG&t;(7L&lt;&lt;16)  /*&t; Bit 18..16:&t;Page Register&t;     */
multiline_comment|/*&t; Bit 15:&t;reserved&t;     */
DECL|macro|PCI_FORCE_BE
mdefine_line|#define&t;PCI_FORCE_BE&t;(1L&lt;&lt;14)  /*&t; Bit 14:&t;Assert all BEs on MR */
DECL|macro|PCI_DIS_MRL
mdefine_line|#define&t;PCI_DIS_MRL&t;(1L&lt;&lt;13)  /*&t; Bit 13:&t;Disable Mem R Line   */
DECL|macro|PCI_DIS_MRM
mdefine_line|#define&t;PCI_DIS_MRM&t;(1L&lt;&lt;12)  /*&t; Bit 12:&t;Disable Mem R multip */
DECL|macro|PCI_DIS_MWI
mdefine_line|#define&t;PCI_DIS_MWI&t;(1L&lt;&lt;11)  /*&t; Bit 11:&t;Disable Mem W &amp; inv  */
DECL|macro|PCI_DISC_CLS
mdefine_line|#define&t;PCI_DISC_CLS&t;(1L&lt;&lt;10)  /*&t; Bit 10:&t;Disc: cacheLsz bound */
DECL|macro|PCI_BURST_DIS
mdefine_line|#define&t;PCI_BURST_DIS&t;(1L&lt;&lt;9)&t;  /*&t; Bit  9:&t;Burst Disable&t;     */
DECL|macro|PCI_BYTE_SWAP
mdefine_line|#define&t;PCI_BYTE_SWAP&t;(1L&lt;&lt;8)&t;  /*(DV) Bit  8:&t;Byte Swap in DATA    */
DECL|macro|PCI_SKEW_DAS
mdefine_line|#define&t;PCI_SKEW_DAS&t;(0xfL&lt;&lt;4) /*&t; Bit 7..4:&t;Skew Ctrl, DAS Ext   */
DECL|macro|PCI_SKEW_BASE
mdefine_line|#define&t;PCI_SKEW_BASE&t;(0xfL&lt;&lt;0) /*&t; Bit 3..0:&t;Skew Ctrl, Base&t;     */
multiline_comment|/*&t;PCI_OUR_REG_2&t;(ML)&t;32 bit&t;Our Register 2 (Monalisa only) */
DECL|macro|PCI_VPD_WR_TH
mdefine_line|#define PCI_VPD_WR_TH&t;(0xffL&lt;&lt;24)&t;/* Bit 24..31&t;VPD Write Threshold  */
DECL|macro|PCI_DEV_SEL
mdefine_line|#define&t;PCI_DEV_SEL&t;(0x7fL&lt;&lt;17)&t;/* Bit 17..23&t;EEPROM Device Select */
DECL|macro|PCI_VPD_ROM_SZ
mdefine_line|#define&t;PCI_VPD_ROM_SZ&t;(7L&lt;&lt;14)&t;/* Bit 14..16&t;VPD ROM Size&t;     */
multiline_comment|/* Bit 12..13&t;reserved&t;     */
DECL|macro|PCI_PATCH_DIR2
mdefine_line|#define&t;PCI_PATCH_DIR2&t;(0xfL&lt;&lt;8)&t;/* Bit  8..11&t;Ext Patchs dir 2..5  */
DECL|macro|PCI_PATCH_DIR_2
mdefine_line|#define&t;PCI_PATCH_DIR_2&t;(1L&lt;&lt;8)&t;&t;/* Bit  8&t;CS for MicroWire     */
DECL|macro|PCI_PATCH_DIR_3
mdefine_line|#define&t;PCI_PATCH_DIR_3&t;(1L&lt;&lt;9)
DECL|macro|PCI_PATCH_DIR_4
mdefine_line|#define&t;PCI_PATCH_DIR_4&t;(1L&lt;&lt;10)
DECL|macro|PCI_PATCH_DIR_5
mdefine_line|#define&t;PCI_PATCH_DIR_5&t;(1L&lt;&lt;11)
DECL|macro|PCI_EXT_PATCHS2
mdefine_line|#define PCI_EXT_PATCHS2 (0xfL&lt;&lt;4)&t;/* Bit  4..7&t;Extended Patches     */
DECL|macro|PCI_EXT_PATCH_2
mdefine_line|#define&t;PCI_EXT_PATCH_2&t;(1L&lt;&lt;4)&t;&t;/* Bit  4&t;CS for MicroWire     */
DECL|macro|PCI_EXT_PATCH_3
mdefine_line|#define&t;PCI_EXT_PATCH_3&t;(1L&lt;&lt;5)
DECL|macro|PCI_EXT_PATCH_4
mdefine_line|#define&t;PCI_EXT_PATCH_4&t;(1L&lt;&lt;6)
DECL|macro|PCI_EXT_PATCH_5
mdefine_line|#define&t;PCI_EXT_PATCH_5&t;(1L&lt;&lt;7)
DECL|macro|PCI_EN_DUMMY_RD
mdefine_line|#define&t;PCI_EN_DUMMY_RD&t;(1L&lt;&lt;3)&t;&t;/* Bit  3&t;Enable Dummy Read    */
DECL|macro|PCI_REV_DESC
mdefine_line|#define PCI_REV_DESC&t;(1L&lt;&lt;2)&t;&t;/* Bit  2&t;Reverse Desc. Bytes  */
DECL|macro|PCI_USEADDR64
mdefine_line|#define PCI_USEADDR64&t;(1L&lt;&lt;1)&t;&t;/* Bit  1&t;Use 64 Bit Addresse  */
DECL|macro|PCI_USEDATA64
mdefine_line|#define PCI_USEDATA64&t;(1L&lt;&lt;0)&t;&t;/* Bit  0&t;Use 64 Bit Data bus ext*/
multiline_comment|/* Power Management Region */
multiline_comment|/*&t;PCI_PM_CAP_ID&t;&t; 8 bit (ML)&t;Power Management Cap. ID */
multiline_comment|/*&t;PCI_PM_NITEM&t;&t; 8 bit (ML)&t;Next Item Ptr */
multiline_comment|/*&t;PCI_PM_CAP_REG&t;&t;16 bit (ML)&t;Power Management Capabilities*/
DECL|macro|PCI_PME_SUP
mdefine_line|#define&t;PCI_PME_SUP&t;(0x1f&lt;&lt;11)&t;/* Bit 11..15&t;PM Manag. Event Support*/
DECL|macro|PCI_PM_D2_SUB
mdefine_line|#define PCI_PM_D2_SUB&t;(1&lt;&lt;10)&t;&t;/* Bit 10&t;D2 Support Bit&t;     */
DECL|macro|PCI_PM_D1_SUB
mdefine_line|#define PCI_PM_D1_SUB&t;(1&lt;&lt;9)&t;&t;/* Bit 9&t;D1 Support Bit       */
multiline_comment|/* Bit 6..8 reserved&t;&t;     */
DECL|macro|PCI_PM_DSI
mdefine_line|#define PCI_PM_DSI&t;(1&lt;&lt;5)&t;&t;/* Bit 5&t;Device Specific Init.*/
DECL|macro|PCI_PM_APS
mdefine_line|#define PCI_PM_APS&t;(1&lt;&lt;4)&t;&t;/* Bit 4&t;Auxialiary Power Src */
DECL|macro|PCI_PME_CLOCK
mdefine_line|#define PCI_PME_CLOCK&t;(1&lt;&lt;3)&t;&t;/* Bit 3&t;PM Event Clock       */
DECL|macro|PCI_PM_VER
mdefine_line|#define PCI_PM_VER&t;(7&lt;&lt;0)&t;&t;/* Bit 0..2&t;PM PCI Spec. version */
multiline_comment|/*&t;PCI_PM_CTL_STS&t;&t;16 bit (ML)&t;Power Manag. Control/Status  */
DECL|macro|PCI_PME_STATUS
mdefine_line|#define&t;PCI_PME_STATUS&t;(1&lt;&lt;15)&t;&t;/* Bit 15 &t;PFA doesn&squot;t sup. PME#*/
DECL|macro|PCI_PM_DAT_SCL
mdefine_line|#define PCI_PM_DAT_SCL&t;(3&lt;&lt;13)&t;&t;/* Bit 13..14&t;dat reg Scaling factor */
DECL|macro|PCI_PM_DAT_SEL
mdefine_line|#define PCI_PM_DAT_SEL&t;(0xf&lt;&lt;9)&t;/* Bit  9..12&t;PM data selector field */
multiline_comment|/* Bit  7.. 2&t;reserved&t;     */
DECL|macro|PCI_PM_STATE
mdefine_line|#define PCI_PM_STATE&t;(3&lt;&lt;0)&t;&t;/* Bit  0.. 1&t;Power Management State */
DECL|macro|PCI_PM_STATE_D0
mdefine_line|#define PCI_PM_STATE_D0&t;(0&lt;&lt;0)&t;&t;/* D0:&t;Operational (default) */
DECL|macro|PCI_PM_STATE_D1
mdefine_line|#define&t;PCI_PM_STATE_D1&t;(1&lt;&lt;0)&t;&t;/* D1:&t;not supported */
DECL|macro|PCI_PM_STATE_D2
mdefine_line|#define PCI_PM_STATE_D2&t;(2&lt;&lt;0)&t;&t;/* D2:&t;not supported */
DECL|macro|PCI_PM_STATE_D3
mdefine_line|#define PCI_PM_STATE_D3 (3&lt;&lt;0)&t;&t;/* D3:&t;HOT, Power Down and Reset */
multiline_comment|/*&t;PCI_PM_DAT_REG&t;&t; 8 bit (ML)&t;Power Manag. Data Register */
multiline_comment|/* VPD Region */
multiline_comment|/*&t;PCI_VPD_CAP_ID&t;&t; 8 bit (ML)&t;VPD Cap. ID */
multiline_comment|/*&t;PCI_VPD_NITEM&t;&t; 8 bit (ML)&t;Next Item Ptr */
multiline_comment|/*&t;PCI_VPD_ADR_REG&t;&t;16 bit (ML)&t;VPD Address Register */
DECL|macro|PCI_VPD_FLAG
mdefine_line|#define&t;PCI_VPD_FLAG&t;(1&lt;&lt;15)&t;&t;/* Bit 15&t;starts VPD rd/wd cycle*/
DECL|macro|PCI_VPD_ADDR
mdefine_line|#define PCI_VPD_ADDR&t;(0x3fff&lt;&lt;0)&t;/* Bit  0..14&t;VPD address */
multiline_comment|/*&t;PCI_VPD_DAT_REG&t;&t;32 bit (ML)&t;VPD Data Register */
multiline_comment|/*&n; *&t;Control Register File:&n; *&t;Bank 0&n; */
DECL|macro|B0_RAP
mdefine_line|#define&t;B0_RAP&t;&t;0x0000&t;/*  8 bit register address port */
multiline_comment|/* 0x0001 - 0x0003:&t;reserved */
DECL|macro|B0_CTRL
mdefine_line|#define&t;B0_CTRL&t;&t;0x0004&t;/*  8 bit control register */
DECL|macro|B0_DAS
mdefine_line|#define&t;B0_DAS&t;&t;0x0005&t;/*  8 Bit control register (DAS) */
DECL|macro|B0_LED
mdefine_line|#define&t;B0_LED&t;&t;0x0006&t;/*  8 Bit LED register */
DECL|macro|B0_TST_CTRL
mdefine_line|#define&t;B0_TST_CTRL&t;0x0007&t;/*  8 bit test control register */
DECL|macro|B0_ISRC
mdefine_line|#define&t;B0_ISRC&t;&t;0x0008&t;/* 32 bit Interrupt source register */
DECL|macro|B0_IMSK
mdefine_line|#define&t;B0_IMSK&t;&t;0x000c&t;/* 32 bit Interrupt mask register */
multiline_comment|/* 0x0010 - 0x006b:&t;formac+ (supernet_3) fequently used registers */
DECL|macro|B0_CMDREG1
mdefine_line|#define B0_CMDREG1&t;0x0010&t;/* write command reg 1 instruction */
DECL|macro|B0_CMDREG2
mdefine_line|#define B0_CMDREG2&t;0x0014&t;/* write command reg 2 instruction */
DECL|macro|B0_ST1U
mdefine_line|#define B0_ST1U&t;&t;0x0010&t;/* read upper 16-bit of status reg 1 */
DECL|macro|B0_ST1L
mdefine_line|#define B0_ST1L&t;&t;0x0014&t;/* read lower 16-bit of status reg 1 */
DECL|macro|B0_ST2U
mdefine_line|#define B0_ST2U&t;&t;0x0018&t;/* read upper 16-bit of status reg 2 */
DECL|macro|B0_ST2L
mdefine_line|#define B0_ST2L&t;&t;0x001c&t;/* read lower 16-bit of status reg 2 */
DECL|macro|B0_MARR
mdefine_line|#define B0_MARR&t;&t;0x0020&t;/* r/w the memory read addr register */
DECL|macro|B0_MARW
mdefine_line|#define B0_MARW&t;&t;0x0024&t;/* r/w the memory write addr register*/
DECL|macro|B0_MDRU
mdefine_line|#define B0_MDRU&t;&t;0x0028&t;/* r/w upper 16-bit of mem. data reg */
DECL|macro|B0_MDRL
mdefine_line|#define B0_MDRL&t;&t;0x002c&t;/* r/w lower 16-bit of mem. data reg */
DECL|macro|B0_MDREG3
mdefine_line|#define&t;B0_MDREG3&t;0x0030&t;/* r/w Mode Register 3 */
DECL|macro|B0_ST3U
mdefine_line|#define&t;B0_ST3U&t;&t;0x0034&t;/* read upper 16-bit of status reg 3 */
DECL|macro|B0_ST3L
mdefine_line|#define&t;B0_ST3L&t;&t;0x0038&t;/* read lower 16-bit of status reg 3 */
DECL|macro|B0_IMSK3U
mdefine_line|#define&t;B0_IMSK3U&t;0x003c&t;/* r/w upper 16-bit of IMSK reg 3 */
DECL|macro|B0_IMSK3L
mdefine_line|#define&t;B0_IMSK3L&t;0x0040&t;/* r/w lower 16-bit of IMSK reg 3 */
DECL|macro|B0_IVR
mdefine_line|#define&t;B0_IVR&t;&t;0x0044&t;/* read Interrupt Vector register */
DECL|macro|B0_IMR
mdefine_line|#define&t;B0_IMR&t;&t;0x0048&t;/* r/w Interrupt mask register */
multiline_comment|/* 0x4c&t;Hidden */
DECL|macro|B0_CNTRL_A
mdefine_line|#define B0_CNTRL_A&t;0x0050&t;/* control register A (r/w) */
DECL|macro|B0_CNTRL_B
mdefine_line|#define B0_CNTRL_B&t;0x0054&t;/* control register B (r/w) */
DECL|macro|B0_INTR_MASK
mdefine_line|#define B0_INTR_MASK&t;0x0058&t;/* interrupt mask (r/w) */
DECL|macro|B0_XMIT_VECTOR
mdefine_line|#define B0_XMIT_VECTOR&t;0x005c&t;/* transmit vector register (r/w) */
DECL|macro|B0_STATUS_A
mdefine_line|#define B0_STATUS_A&t;0x0060&t;/* status register A (read only) */
DECL|macro|B0_STATUS_B
mdefine_line|#define B0_STATUS_B&t;0x0064&t;/* status register B (read only) */
DECL|macro|B0_CNTRL_C
mdefine_line|#define B0_CNTRL_C&t;0x0068&t;/* control register C (r/w) */
DECL|macro|B0_MDREG1
mdefine_line|#define&t;B0_MDREG1&t;0x006c&t;/* r/w Mode Register 1 */
DECL|macro|B0_R1_CSR
mdefine_line|#define&t;B0_R1_CSR&t;0x0070&t;/* 32 bit BMU control/status reg (rec q 1) */
DECL|macro|B0_R2_CSR
mdefine_line|#define&t;B0_R2_CSR&t;0x0074&t;/* 32 bit BMU control/status reg (rec q 2)(DV)*/
DECL|macro|B0_XA_CSR
mdefine_line|#define&t;B0_XA_CSR&t;0x0078&t;/* 32 bit BMU control/status reg (a xmit q) */
DECL|macro|B0_XS_CSR
mdefine_line|#define&t;B0_XS_CSR&t;0x007c&t;/* 32 bit BMU control/status reg (s xmit q) */
multiline_comment|/*&n; *&t;Bank 1&n; *&t;- completely empty (this is the RAP Block window)&n; *&t;Note: if RAP = 1 this page is reserved&n; */
multiline_comment|/*&n; *&t;Bank 2&n; */
DECL|macro|B2_MAC_0
mdefine_line|#define&t;B2_MAC_0&t;0x0100&t;/*  8 bit MAC address Byte 0 */
DECL|macro|B2_MAC_1
mdefine_line|#define&t;B2_MAC_1&t;0x0101&t;/*  8 bit MAC address Byte 1 */
DECL|macro|B2_MAC_2
mdefine_line|#define&t;B2_MAC_2&t;0x0102&t;/*  8 bit MAC address Byte 2 */
DECL|macro|B2_MAC_3
mdefine_line|#define&t;B2_MAC_3&t;0x0103&t;/*  8 bit MAC address Byte 3 */
DECL|macro|B2_MAC_4
mdefine_line|#define&t;B2_MAC_4&t;0x0104&t;/*  8 bit MAC address Byte 4 */
DECL|macro|B2_MAC_5
mdefine_line|#define&t;B2_MAC_5&t;0x0105&t;/*  8 bit MAC address Byte 5 */
DECL|macro|B2_MAC_6
mdefine_line|#define&t;B2_MAC_6&t;0x0106&t;/*  8 bit MAC address Byte 6 (== 0) (DV) */
DECL|macro|B2_MAC_7
mdefine_line|#define&t;B2_MAC_7&t;0x0107&t;/*  8 bit MAC address Byte 7 (== 0) (DV) */
DECL|macro|B2_CONN_TYP
mdefine_line|#define B2_CONN_TYP&t;0x0108&t;/*  8 bit Connector type */
DECL|macro|B2_PMD_TYP
mdefine_line|#define B2_PMD_TYP&t;0x0109&t;/*  8 bit PMD type */
multiline_comment|/* 0x010a - 0x010b:&t;reserved */
multiline_comment|/* Eprom registers are currently of no use */
DECL|macro|B2_E_0
mdefine_line|#define B2_E_0&t;&t;0x010c&t;/*  8 bit EPROM Byte 0 */
DECL|macro|B2_E_1
mdefine_line|#define B2_E_1&t;&t;0x010d&t;/*  8 bit EPROM Byte 1 */
DECL|macro|B2_E_2
mdefine_line|#define B2_E_2&t;&t;0x010e&t;/*  8 bit EPROM Byte 2 */
DECL|macro|B2_E_3
mdefine_line|#define B2_E_3&t;&t;0x010f&t;/*  8 bit EPROM Byte 3 */
DECL|macro|B2_FAR
mdefine_line|#define B2_FAR&t;&t;0x0110&t;/* 32 bit Flash-Prom Address Register/Counter */
DECL|macro|B2_FDP
mdefine_line|#define B2_FDP&t;&t;0x0114&t;/*  8 bit Flash-Prom Data Port */
multiline_comment|/* 0x0115 - 0x0117:&t;reserved */
DECL|macro|B2_LD_CRTL
mdefine_line|#define B2_LD_CRTL&t;0x0118&t;/*  8 bit loader control */
DECL|macro|B2_LD_TEST
mdefine_line|#define B2_LD_TEST&t;0x0119&t;/*  8 bit loader test */
multiline_comment|/* 0x011a - 0x011f:&t;reserved */
DECL|macro|B2_TI_INI
mdefine_line|#define B2_TI_INI&t;0x0120&t;/* 32 bit Timer init value */
DECL|macro|B2_TI_VAL
mdefine_line|#define B2_TI_VAL&t;0x0124&t;/* 32 bit Timer value */
DECL|macro|B2_TI_CRTL
mdefine_line|#define B2_TI_CRTL&t;0x0128&t;/*  8 bit Timer control */
DECL|macro|B2_TI_TEST
mdefine_line|#define B2_TI_TEST&t;0x0129&t;/*  8 Bit Timer Test */
multiline_comment|/* 0x012a - 0x012f:&t;reserved */
DECL|macro|B2_WDOG_INI
mdefine_line|#define B2_WDOG_INI&t;0x0130&t;/* 32 bit Watchdog init value */
DECL|macro|B2_WDOG_VAL
mdefine_line|#define B2_WDOG_VAL&t;0x0134&t;/* 32 bit Watchdog value */
DECL|macro|B2_WDOG_CRTL
mdefine_line|#define B2_WDOG_CRTL&t;0x0138&t;/*  8 bit Watchdog control */
DECL|macro|B2_WDOG_TEST
mdefine_line|#define B2_WDOG_TEST&t;0x0139&t;/*  8 Bit Watchdog Test */
multiline_comment|/* 0x013a - 0x013f:&t;reserved */
DECL|macro|B2_RTM_INI
mdefine_line|#define B2_RTM_INI&t;0x0140&t;/* 32 bit RTM init value */
DECL|macro|B2_RTM_VAL
mdefine_line|#define B2_RTM_VAL&t;0x0144&t;/* 32 bit RTM value */
DECL|macro|B2_RTM_CRTL
mdefine_line|#define B2_RTM_CRTL&t;0x0148&t;/*  8 bit RTM control */
DECL|macro|B2_RTM_TEST
mdefine_line|#define B2_RTM_TEST&t;0x0149&t;/*  8 Bit RTM Test */
DECL|macro|B2_TOK_COUNT
mdefine_line|#define B2_TOK_COUNT&t;0x014c&t;/* (ML)&t;32 bit&t;Token Counter */
DECL|macro|B2_DESC_ADDR_H
mdefine_line|#define B2_DESC_ADDR_H&t;0x0150&t;/* (ML) 32 bit&t;Desciptor Base Addr Reg High */
DECL|macro|B2_CTRL_2
mdefine_line|#define B2_CTRL_2&t;0x0154&t;/* (ML)&t; 8 bit&t;Control Register 2 */
DECL|macro|B2_IFACE_REG
mdefine_line|#define B2_IFACE_REG&t;0x0155&t;/* (ML)&t; 8 bit&t;Interface Register */
multiline_comment|/* 0x0156:&t;&t;reserved */
DECL|macro|B2_TST_CTRL_2
mdefine_line|#define B2_TST_CTRL_2&t;0x0157&t;/* (ML)  8 bit&t;Test Control Register 2 */
DECL|macro|B2_I2C_CTRL
mdefine_line|#define B2_I2C_CTRL&t;0x0158&t;/* (ML)&t;32 bit&t;I2C Control Register */
DECL|macro|B2_I2C_DATA
mdefine_line|#define B2_I2C_DATA&t;0x015c&t;/* (ML) 32 bit&t;I2C Data Register */
DECL|macro|B2_IRQ_MOD_INI
mdefine_line|#define B2_IRQ_MOD_INI&t;0x0160&t;/* (ML) 32 bit&t;IRQ Moderation Timer Init Reg. */
DECL|macro|B2_IRQ_MOD_VAL
mdefine_line|#define B2_IRQ_MOD_VAL&t;0x0164&t;/* (ML)&t;32 bit&t;IRQ Moderation Timer Value */
DECL|macro|B2_IRQ_MOD_CTRL
mdefine_line|#define B2_IRQ_MOD_CTRL&t;0x0168&t;/* (ML)  8 bit&t;IRQ Moderation Timer Control */
DECL|macro|B2_IRQ_MOD_TEST
mdefine_line|#define B2_IRQ_MOD_TEST&t;0x0169&t;/* (ML)&t; 8 bit&t;IRQ Moderation Timer Test */
multiline_comment|/* 0x016a - 0x017f:&t;reserved */
multiline_comment|/*&n; *&t;Bank 3&n; */
multiline_comment|/*&n; * This is a copy of the Configuration register file (lower half)&n; */
DECL|macro|B3_CFG_SPC
mdefine_line|#define B3_CFG_SPC&t;0x180
multiline_comment|/*&n; *&t;Bank 4&n; */
DECL|macro|B4_R1_D
mdefine_line|#define B4_R1_D&t;&t;0x0200&t;/* &t;4*32 bit current receive Descriptor  */
DECL|macro|B4_R1_DA
mdefine_line|#define B4_R1_DA&t;0x0210&t;/* &t;32 bit current rec desc address&t;     */
DECL|macro|B4_R1_AC
mdefine_line|#define B4_R1_AC&t;0x0214&t;/* &t;32 bit current receive Address Count */
DECL|macro|B4_R1_BC
mdefine_line|#define B4_R1_BC&t;0x0218&t;/*&t;32 bit current receive Byte Counter  */
DECL|macro|B4_R1_CSR
mdefine_line|#define B4_R1_CSR&t;0x021c&t;/* &t;32 bit BMU Control/Status Register   */
DECL|macro|B4_R1_F
mdefine_line|#define B4_R1_F&t;&t;0x0220&t;/* &t;32 bit flag register&t;&t;     */
DECL|macro|B4_R1_T1
mdefine_line|#define B4_R1_T1&t;0x0224&t;/* &t;32 bit Test Register 1&t;&t;     */
DECL|macro|B4_R1_T1_TR
mdefine_line|#define B4_R1_T1_TR&t;0x0224&t;/* &t;8 bit Test Register 1 TR&t;     */
DECL|macro|B4_R1_T1_WR
mdefine_line|#define B4_R1_T1_WR&t;0x0225&t;/* &t;8 bit Test Register 1 WR&t;     */
DECL|macro|B4_R1_T1_RD
mdefine_line|#define B4_R1_T1_RD&t;0x0226&t;/* &t;8 bit Test Register 1 RD&t;     */
DECL|macro|B4_R1_T1_SV
mdefine_line|#define B4_R1_T1_SV&t;0x0227&t;/* &t;8 bit Test Register 1 SV&t;     */
DECL|macro|B4_R1_T2
mdefine_line|#define B4_R1_T2&t;0x0228&t;/* &t;32 bit Test Register 2&t;&t;     */
DECL|macro|B4_R1_T3
mdefine_line|#define B4_R1_T3&t;0x022c&t;/* &t;32 bit Test Register 3&t;&t;     */
DECL|macro|B4_R1_DA_H
mdefine_line|#define B4_R1_DA_H&t;0x0230&t;/* (ML)&t;32 bit Curr Rx Desc Address High     */
DECL|macro|B4_R1_AC_H
mdefine_line|#define B4_R1_AC_H&t;0x0234&t;/* (ML)&t;32 bit Curr Addr Counter High dword  */
multiline_comment|/* 0x0238 - 0x023f:&t;reserved&t;  */
multiline_comment|/* Receive queue 2 is removed on Monalisa */
DECL|macro|B4_R2_D
mdefine_line|#define B4_R2_D&t;&t;0x0240&t;/* 4*32 bit current receive Descriptor&t;(q2) */
DECL|macro|B4_R2_DA
mdefine_line|#define B4_R2_DA&t;0x0250&t;/* 32 bit current rec desc address&t;(q2) */
DECL|macro|B4_R2_AC
mdefine_line|#define B4_R2_AC&t;0x0254&t;/* 32 bit current receive Address Count&t;(q2) */
DECL|macro|B4_R2_BC
mdefine_line|#define B4_R2_BC&t;0x0258&t;/* 32 bit current receive Byte Counter&t;(q2) */
DECL|macro|B4_R2_CSR
mdefine_line|#define B4_R2_CSR&t;0x025c&t;/* 32 bit BMU Control/Status Register&t;(q2) */
DECL|macro|B4_R2_F
mdefine_line|#define B4_R2_F&t;&t;0x0260&t;/* 32 bit flag register&t;&t;&t;(q2) */
DECL|macro|B4_R2_T1
mdefine_line|#define B4_R2_T1&t;0x0264&t;/* 32 bit Test Register 1&t;&t;(q2) */
DECL|macro|B4_R2_T1_TR
mdefine_line|#define B4_R2_T1_TR&t;0x0264&t;/* 8 bit Test Register 1 TR&t;&t;(q2) */
DECL|macro|B4_R2_T1_WR
mdefine_line|#define B4_R2_T1_WR&t;0x0265&t;/* 8 bit Test Register 1 WR&t;&t;(q2) */
DECL|macro|B4_R2_T1_RD
mdefine_line|#define B4_R2_T1_RD&t;0x0266&t;/* 8 bit Test Register 1 RD&t;&t;(q2) */
DECL|macro|B4_R2_T1_SV
mdefine_line|#define B4_R2_T1_SV&t;0x0267&t;/* 8 bit Test Register 1 SV&t;&t;(q2) */
DECL|macro|B4_R2_T2
mdefine_line|#define B4_R2_T2&t;0x0268&t;/* 32 bit Test Register 2&t;&t;(q2) */
DECL|macro|B4_R2_T3
mdefine_line|#define B4_R2_T3&t;0x026c&t;/* 32 bit Test Register 3&t;&t;(q2) */
multiline_comment|/* 0x0270 - 0x027c:&t;reserved */
multiline_comment|/*&n; *&t;Bank 5&n; */
DECL|macro|B5_XA_D
mdefine_line|#define B5_XA_D&t;&t;0x0280&t;/* 4*32 bit current transmit Descriptor&t;(xa) */
DECL|macro|B5_XA_DA
mdefine_line|#define B5_XA_DA&t;0x0290&t;/* 32 bit current tx desc address&t;(xa) */
DECL|macro|B5_XA_AC
mdefine_line|#define B5_XA_AC&t;0x0294&t;/* 32 bit current tx Address Count&t;(xa) */
DECL|macro|B5_XA_BC
mdefine_line|#define B5_XA_BC&t;0x0298&t;/* 32 bit current tx Byte Counter&t;(xa) */
DECL|macro|B5_XA_CSR
mdefine_line|#define B5_XA_CSR&t;0x029c&t;/* 32 bit BMU Control/Status Register&t;(xa) */
DECL|macro|B5_XA_F
mdefine_line|#define B5_XA_F&t;&t;0x02a0&t;/* 32 bit flag register&t;&t;&t;(xa) */
DECL|macro|B5_XA_T1
mdefine_line|#define B5_XA_T1&t;0x02a4&t;/* 32 bit Test Register 1&t;&t;(xa) */
DECL|macro|B5_XA_T1_TR
mdefine_line|#define B5_XA_T1_TR&t;0x02a4&t;/* 8 bit Test Register 1 TR&t;&t;(xa) */
DECL|macro|B5_XA_T1_WR
mdefine_line|#define B5_XA_T1_WR&t;0x02a5&t;/* 8 bit Test Register 1 WR&t;&t;(xa) */
DECL|macro|B5_XA_T1_RD
mdefine_line|#define B5_XA_T1_RD&t;0x02a6&t;/* 8 bit Test Register 1 RD&t;&t;(xa) */
DECL|macro|B5_XA_T1_SV
mdefine_line|#define B5_XA_T1_SV&t;0x02a7&t;/* 8 bit Test Register 1 SV&t;&t;(xa) */
DECL|macro|B5_XA_T2
mdefine_line|#define B5_XA_T2&t;0x02a8&t;/* 32 bit Test Register 2&t;&t;(xa) */
DECL|macro|B5_XA_T3
mdefine_line|#define B5_XA_T3&t;0x02ac&t;/* 32 bit Test Register 3&t;&t;(xa) */
DECL|macro|B5_XA_DA_H
mdefine_line|#define B5_XA_DA_H&t;0x02b0&t;/* (ML)&t;32 bit Curr Tx Desc Address High     */
DECL|macro|B5_XA_AC_H
mdefine_line|#define B5_XA_AC_H&t;0x02b4&t;/* (ML)&t;32 bit Curr Addr Counter High dword  */
multiline_comment|/* 0x02b8 - 0x02bc:&t;reserved */
DECL|macro|B5_XS_D
mdefine_line|#define B5_XS_D&t;&t;0x02c0&t;/* 4*32 bit current transmit Descriptor&t;(xs) */
DECL|macro|B5_XS_DA
mdefine_line|#define B5_XS_DA&t;0x02d0&t;/* 32 bit current tx desc address&t;(xs) */
DECL|macro|B5_XS_AC
mdefine_line|#define B5_XS_AC&t;0x02d4&t;/* 32 bit current transmit Address Count(xs) */
DECL|macro|B5_XS_BC
mdefine_line|#define B5_XS_BC&t;0x02d8&t;/* 32 bit current transmit Byte Counter&t;(xs) */
DECL|macro|B5_XS_CSR
mdefine_line|#define B5_XS_CSR&t;0x02dc&t;/* 32 bit BMU Control/Status Register&t;(xs) */
DECL|macro|B5_XS_F
mdefine_line|#define B5_XS_F&t;&t;0x02e0&t;/* 32 bit flag register&t;&t;&t;(xs) */
DECL|macro|B5_XS_T1
mdefine_line|#define B5_XS_T1&t;0x02e4&t;/* 32 bit Test Register 1&t;&t;(xs) */
DECL|macro|B5_XS_T1_TR
mdefine_line|#define B5_XS_T1_TR&t;0x02e4&t;/* 8 bit Test Register 1 TR&t;&t;(xs) */
DECL|macro|B5_XS_T1_WR
mdefine_line|#define B5_XS_T1_WR&t;0x02e5&t;/* 8 bit Test Register 1 WR&t;&t;(xs) */
DECL|macro|B5_XS_T1_RD
mdefine_line|#define B5_XS_T1_RD&t;0x02e6&t;/* 8 bit Test Register 1 RD&t;&t;(xs) */
DECL|macro|B5_XS_T1_SV
mdefine_line|#define B5_XS_T1_SV&t;0x02e7&t;/* 8 bit Test Register 1 SV&t;&t;(xs) */
DECL|macro|B5_XS_T2
mdefine_line|#define B5_XS_T2&t;0x02e8&t;/* 32 bit Test Register 2&t;&t;(xs) */
DECL|macro|B5_XS_T3
mdefine_line|#define B5_XS_T3&t;0x02ec&t;/* 32 bit Test Register 3&t;&t;(xs) */
DECL|macro|B5_XS_DA_H
mdefine_line|#define B5_XS_DA_H&t;0x02f0&t;/* (ML)&t;32 bit Curr Tx Desc Address High     */
DECL|macro|B5_XS_AC_H
mdefine_line|#define B5_XS_AC_H&t;0x02f4&t;/* (ML)&t;32 bit Curr Addr Counter High dword  */
multiline_comment|/* 0x02f8 - 0x02fc:&t;reserved */
multiline_comment|/*&n; *&t;Bank 6&n; */
multiline_comment|/* External PLC-S registers (SN2 compatibility for DV) */
multiline_comment|/* External registers (ML) */
DECL|macro|B6_EXT_REG
mdefine_line|#define B6_EXT_REG&t;0x300
multiline_comment|/*&n; *&t;Bank 7&n; */
multiline_comment|/* DAS PLC-S Registers */
multiline_comment|/*&n; *&t;Bank 8 - 15&n; */
multiline_comment|/* IFCP registers */
multiline_comment|/*---------------------------------------------------------------------------*/
multiline_comment|/* Definitions of the Bits in the registers */
multiline_comment|/*&t;B0_RAP&t;&t;16 bit register address port */
DECL|macro|RAP_RAP
mdefine_line|#define&t;RAP_RAP&t;&t;0x0f&t;/* Bit 3..0:&t;0 = block0, .., f = block15 */
multiline_comment|/*&t;B0_CTRL&t;&t;8 bit control register */
DECL|macro|CTRL_FDDI_CLR
mdefine_line|#define CTRL_FDDI_CLR&t;(1&lt;&lt;7)&t;/* Bit 7: (ML)&t;Clear FDDI Reset */
DECL|macro|CTRL_FDDI_SET
mdefine_line|#define CTRL_FDDI_SET&t;(1&lt;&lt;6)&t;/* Bit 6: (ML)&t;Set FDDI Reset */
DECL|macro|CTRL_HPI_CLR
mdefine_line|#define&t;CTRL_HPI_CLR&t;(1&lt;&lt;5)&t;/* Bit 5:&t;Clear HPI SM reset */
DECL|macro|CTRL_HPI_SET
mdefine_line|#define&t;CTRL_HPI_SET&t;(1&lt;&lt;4)&t;/* Bit 4:&t;Set HPI SM reset */
DECL|macro|CTRL_MRST_CLR
mdefine_line|#define&t;CTRL_MRST_CLR&t;(1&lt;&lt;3)&t;/* Bit 3:&t;Clear Master reset */
DECL|macro|CTRL_MRST_SET
mdefine_line|#define&t;CTRL_MRST_SET&t;(1&lt;&lt;2)&t;/* Bit 2:&t;Set Master reset */
DECL|macro|CTRL_RST_CLR
mdefine_line|#define&t;CTRL_RST_CLR&t;(1&lt;&lt;1)&t;/* Bit 1:&t;Clear Software reset */
DECL|macro|CTRL_RST_SET
mdefine_line|#define&t;CTRL_RST_SET&t;(1&lt;&lt;0)&t;/* Bit 0:&t;Set Software reset */
multiline_comment|/*&t;B0_DAS&t;&t;8 Bit control register (DAS) */
DECL|macro|BUS_CLOCK
mdefine_line|#define BUS_CLOCK&t;(1&lt;&lt;7)&t;/* Bit 7: (ML)&t;Bus Clock 0/1 = 33/66MHz */
DECL|macro|BUS_SLOT_SZ
mdefine_line|#define BUS_SLOT_SZ&t;(1&lt;&lt;6)&t;/* Bit 6: (ML)&t;Slot Size 0/1 = 32/64 bit slot*/
multiline_comment|/* Bit 5..4:&t;reserved */
DECL|macro|DAS_AVAIL
mdefine_line|#define&t;DAS_AVAIL&t;(1&lt;&lt;3)&t;/* Bit 3:&t;1 = DAS, 0 = SAS */
DECL|macro|DAS_BYP_ST
mdefine_line|#define DAS_BYP_ST&t;(1&lt;&lt;2)&t;/* Bit 2:&t;1 = avail,SAS, 0 = not avail */
DECL|macro|DAS_BYP_INS
mdefine_line|#define DAS_BYP_INS&t;(1&lt;&lt;1)&t;/* Bit 1:&t;1 = insert Bypass */
DECL|macro|DAS_BYP_RMV
mdefine_line|#define DAS_BYP_RMV&t;(1&lt;&lt;0)&t;/* Bit 0:&t;1 = remove Bypass */
multiline_comment|/*&t;B0_LED&t;&t;8 Bit LED register */
multiline_comment|/* Bit 7..6:&t;reserved */
DECL|macro|LED_2_ON
mdefine_line|#define LED_2_ON&t;(1&lt;&lt;5)&t;/* Bit 5:&t;1 = switch LED_2 on (left,gn)*/
DECL|macro|LED_2_OFF
mdefine_line|#define LED_2_OFF&t;(1&lt;&lt;4)&t;/* Bit 4:&t;1 = switch LED_2 off */
DECL|macro|LED_1_ON
mdefine_line|#define LED_1_ON&t;(1&lt;&lt;3)&t;/* Bit 3:&t;1 = switch LED_1 on (mid,yel)*/
DECL|macro|LED_1_OFF
mdefine_line|#define LED_1_OFF&t;(1&lt;&lt;2)&t;/* Bit 2:&t;1 = switch LED_1 off */
DECL|macro|LED_0_ON
mdefine_line|#define LED_0_ON&t;(1&lt;&lt;1)&t;/* Bit 1:&t;1 = switch LED_0 on (rght,gn)*/
DECL|macro|LED_0_OFF
mdefine_line|#define LED_0_OFF&t;(1&lt;&lt;0)&t;/* Bit 0:&t;1 = switch LED_0 off */
multiline_comment|/* This hardware defines are very ugly therefore we define some others */
DECL|macro|LED_GA_ON
mdefine_line|#define LED_GA_ON&t;LED_2_ON&t;/* S port = A port */
DECL|macro|LED_GA_OFF
mdefine_line|#define LED_GA_OFF&t;LED_2_OFF&t;/* S port = A port */
DECL|macro|LED_MY_ON
mdefine_line|#define LED_MY_ON&t;LED_1_ON
DECL|macro|LED_MY_OFF
mdefine_line|#define LED_MY_OFF&t;LED_1_OFF
DECL|macro|LED_GB_ON
mdefine_line|#define LED_GB_ON&t;LED_0_ON
DECL|macro|LED_GB_OFF
mdefine_line|#define LED_GB_OFF&t;LED_0_OFF
multiline_comment|/*&t;B0_TST_CTRL&t;8 bit test control register */
DECL|macro|TST_FRC_DPERR_MR
mdefine_line|#define&t;TST_FRC_DPERR_MR&t;(1&lt;&lt;7)&t;/* Bit 7:  force DATAPERR on MST RE. */
DECL|macro|TST_FRC_DPERR_MW
mdefine_line|#define&t;TST_FRC_DPERR_MW&t;(1&lt;&lt;6)&t;/* Bit 6:  force DATAPERR on MST WR. */
DECL|macro|TST_FRC_DPERR_TR
mdefine_line|#define&t;TST_FRC_DPERR_TR&t;(1&lt;&lt;5)&t;/* Bit 5:  force DATAPERR on TRG RE. */
DECL|macro|TST_FRC_DPERR_TW
mdefine_line|#define&t;TST_FRC_DPERR_TW&t;(1&lt;&lt;4)&t;/* Bit 4:  force DATAPERR on TRG WR. */
DECL|macro|TST_FRC_APERR_M
mdefine_line|#define&t;TST_FRC_APERR_M&t;&t;(1&lt;&lt;3)&t;/* Bit 3:  force ADDRPERR on MST     */
DECL|macro|TST_FRC_APERR_T
mdefine_line|#define&t;TST_FRC_APERR_T&t;&t;(1&lt;&lt;2)&t;/* Bit 2:  force ADDRPERR on TRG     */
DECL|macro|TST_CFG_WRITE_ON
mdefine_line|#define&t;TST_CFG_WRITE_ON&t;(1&lt;&lt;1)&t;/* Bit 1:  ena configuration reg. WR */
DECL|macro|TST_CFG_WRITE_OFF
mdefine_line|#define&t;TST_CFG_WRITE_OFF&t;(1&lt;&lt;0)&t;/* Bit 0:  dis configuration reg. WR */
multiline_comment|/*&t;B0_ISRC&t;&t;32 bit Interrupt source register */
multiline_comment|/* Bit 31..28:&t;reserved&t;     */
DECL|macro|IS_I2C_READY
mdefine_line|#define IS_I2C_READY&t;(1L&lt;&lt;27)&t;/* Bit 27: (ML)&t;IRQ on end of I2C tx */
DECL|macro|IS_IRQ_SW
mdefine_line|#define IS_IRQ_SW&t;(1L&lt;&lt;26)&t;/* Bit 26: (ML)&t;SW forced IRQ&t;     */
DECL|macro|IS_EXT_REG
mdefine_line|#define IS_EXT_REG&t;(1L&lt;&lt;25)&t;/* Bit 25: (ML) IRQ from external reg*/
DECL|macro|IS_IRQ_STAT
mdefine_line|#define&t;IS_IRQ_STAT&t;(1L&lt;&lt;24)&t;/* Bit 24:&t;IRQ status execption */
multiline_comment|/*   PERR, RMABORT, RTABORT DATAPERR */
DECL|macro|IS_IRQ_MST_ERR
mdefine_line|#define&t;IS_IRQ_MST_ERR&t;(1L&lt;&lt;23)&t;/* Bit 23:&t;IRQ master error     */
multiline_comment|/*   RMABORT, RTABORT, DATAPERR&t;     */
DECL|macro|IS_TIMINT
mdefine_line|#define&t;IS_TIMINT&t;(1L&lt;&lt;22)&t;/* Bit 22:&t;IRQ_TIMER&t;*/
DECL|macro|IS_TOKEN
mdefine_line|#define&t;IS_TOKEN&t;(1L&lt;&lt;21)&t;/* Bit 21:&t;IRQ_RTM&t;&t;*/
multiline_comment|/*&n; * Note: The DAS is our First Port (!=PA)&n; */
DECL|macro|IS_PLINT1
mdefine_line|#define&t;IS_PLINT1&t;(1L&lt;&lt;20)&t;/* Bit 20:&t;IRQ_PHY_DAS&t;*/
DECL|macro|IS_PLINT2
mdefine_line|#define&t;IS_PLINT2&t;(1L&lt;&lt;19)&t;/* Bit 19:&t;IRQ_IFCP_4&t;*/
DECL|macro|IS_MINTR3
mdefine_line|#define&t;IS_MINTR3&t;(1L&lt;&lt;18)&t;/* Bit 18:&t;IRQ_IFCP_3/IRQ_PHY */
DECL|macro|IS_MINTR2
mdefine_line|#define&t;IS_MINTR2&t;(1L&lt;&lt;17)&t;/* Bit 17:&t;IRQ_IFCP_2/IRQ_MAC_2 */
DECL|macro|IS_MINTR1
mdefine_line|#define&t;IS_MINTR1&t;(1L&lt;&lt;16)&t;/* Bit 16:&t;IRQ_IFCP_1/IRQ_MAC_1 */
multiline_comment|/* Receive Queue 1 */
DECL|macro|IS_R1_P
mdefine_line|#define&t;IS_R1_P&t;&t;(1L&lt;&lt;15)&t;/* Bit 15:&t;Parity Error (q1) */
DECL|macro|IS_R1_B
mdefine_line|#define&t;IS_R1_B&t;&t;(1L&lt;&lt;14)&t;/* Bit 14:&t;End of Buffer (q1) */
DECL|macro|IS_R1_F
mdefine_line|#define&t;IS_R1_F&t;&t;(1L&lt;&lt;13)&t;/* Bit 13:&t;End of Frame (q1) */
DECL|macro|IS_R1_C
mdefine_line|#define&t;IS_R1_C&t;&t;(1L&lt;&lt;12)&t;/* Bit 12:&t;Encoding Error (q1) */
multiline_comment|/* Receive Queue 2 */
DECL|macro|IS_R2_P
mdefine_line|#define&t;IS_R2_P&t;&t;(1L&lt;&lt;11)&t;/* Bit 11: (DV)&t;Parity Error (q2) */
DECL|macro|IS_R2_B
mdefine_line|#define&t;IS_R2_B&t;&t;(1L&lt;&lt;10)&t;/* Bit 10: (DV)&t;End of Buffer (q2) */
DECL|macro|IS_R2_F
mdefine_line|#define&t;IS_R2_F&t;&t;(1L&lt;&lt;9)&t;&t;/* Bit&t;9: (DV)&t;End of Frame (q2) */
DECL|macro|IS_R2_C
mdefine_line|#define&t;IS_R2_C&t;&t;(1L&lt;&lt;8)&t;&t;/* Bit&t;8: (DV)&t;Encoding Error (q2) */
multiline_comment|/* Asynchronous Transmit queue */
multiline_comment|/* Bit  7:&t;reserved */
DECL|macro|IS_XA_B
mdefine_line|#define&t;IS_XA_B&t;&t;(1L&lt;&lt;6)&t;&t;/* Bit&t;6:&t;End of Buffer (xa) */
DECL|macro|IS_XA_F
mdefine_line|#define&t;IS_XA_F&t;&t;(1L&lt;&lt;5)&t;&t;/* Bit&t;5:&t;End of Frame (xa) */
DECL|macro|IS_XA_C
mdefine_line|#define&t;IS_XA_C&t;&t;(1L&lt;&lt;4)&t;&t;/* Bit&t;4:&t;Encoding Error (xa) */
multiline_comment|/* Synchronous Transmit queue */
multiline_comment|/* Bit  3:&t;reserved */
DECL|macro|IS_XS_B
mdefine_line|#define&t;IS_XS_B&t;&t;(1L&lt;&lt;2)&t;&t;/* Bit&t;2:&t;End of Buffer (xs) */
DECL|macro|IS_XS_F
mdefine_line|#define&t;IS_XS_F&t;&t;(1L&lt;&lt;1)&t;&t;/* Bit&t;1:&t;End of Frame (xs) */
DECL|macro|IS_XS_C
mdefine_line|#define&t;IS_XS_C&t;&t;(1L&lt;&lt;0)&t;&t;/* Bit&t;0:&t;Encoding Error (xs) */
multiline_comment|/*&n; * Define all valid interrupt source Bits from GET_ISR ()&n; */
DECL|macro|ALL_IRSR
mdefine_line|#define&t;ALL_IRSR&t;0x01ffff77L&t;/* (DV) */
DECL|macro|ALL_IRSR_ML
mdefine_line|#define&t;ALL_IRSR_ML&t;0x0ffff077L&t;/* (ML) */
multiline_comment|/*&t;B0_IMSK&t;&t;32 bit Interrupt mask register */
multiline_comment|/*&n; * The Bit definnition of this register are the same as of the interrupt&n; * source register. These definition are directly derived from the Hardware&n; * spec.&n; */
multiline_comment|/* Bit 31..28:&t;reserved&t;     */
DECL|macro|IRQ_I2C_READY
mdefine_line|#define IRQ_I2C_READY&t;(1L&lt;&lt;27)&t;/* Bit 27: (ML)&t;IRQ on end of I2C tx */
DECL|macro|IRQ_SW
mdefine_line|#define IRQ_SW&t;&t;(1L&lt;&lt;26)&t;/* Bit 26: (ML)&t;SW forced IRQ&t;     */
DECL|macro|IRQ_EXT_REG
mdefine_line|#define IRQ_EXT_REG&t;(1L&lt;&lt;25)&t;/* Bit 25: (ML) IRQ from external reg*/
DECL|macro|IRQ_STAT
mdefine_line|#define&t;IRQ_STAT&t;(1L&lt;&lt;24)&t;/* Bit 24:&t;IRQ status execption */
multiline_comment|/*   PERR, RMABORT, RTABORT DATAPERR */
DECL|macro|IRQ_MST_ERR
mdefine_line|#define&t;IRQ_MST_ERR&t;(1L&lt;&lt;23)&t;/* Bit 23:&t;IRQ master error     */
multiline_comment|/*   RMABORT, RTABORT, DATAPERR&t;     */
DECL|macro|IRQ_TIMER
mdefine_line|#define&t;IRQ_TIMER&t;(1L&lt;&lt;22)&t;/* Bit 22:&t;IRQ_TIMER&t;*/
DECL|macro|IRQ_RTM
mdefine_line|#define&t;IRQ_RTM&t;&t;(1L&lt;&lt;21)&t;/* Bit 21:&t;IRQ_RTM&t;&t;*/
DECL|macro|IRQ_DAS
mdefine_line|#define&t;IRQ_DAS&t;&t;(1L&lt;&lt;20)&t;/* Bit 20:&t;IRQ_PHY_DAS&t;*/
DECL|macro|IRQ_IFCP_4
mdefine_line|#define&t;IRQ_IFCP_4&t;(1L&lt;&lt;19)&t;/* Bit 19:&t;IRQ_IFCP_4&t;*/
DECL|macro|IRQ_IFCP_3
mdefine_line|#define&t;IRQ_IFCP_3&t;(1L&lt;&lt;18)&t;/* Bit 18:&t;IRQ_IFCP_3/IRQ_PHY */
DECL|macro|IRQ_IFCP_2
mdefine_line|#define&t;IRQ_IFCP_2&t;(1L&lt;&lt;17)&t;/* Bit 17:&t;IRQ_IFCP_2/IRQ_MAC_2 */
DECL|macro|IRQ_IFCP_1
mdefine_line|#define&t;IRQ_IFCP_1&t;(1L&lt;&lt;16)&t;/* Bit 16:&t;IRQ_IFCP_1/IRQ_MAC_1 */
multiline_comment|/* Receive Queue 1 */
DECL|macro|IRQ_R1_P
mdefine_line|#define&t;IRQ_R1_P&t;(1L&lt;&lt;15)&t;/* Bit 15:&t;Parity Error (q1) */
DECL|macro|IRQ_R1_B
mdefine_line|#define&t;IRQ_R1_B&t;(1L&lt;&lt;14)&t;/* Bit 14:&t;End of Buffer (q1) */
DECL|macro|IRQ_R1_F
mdefine_line|#define&t;IRQ_R1_F&t;(1L&lt;&lt;13)&t;/* Bit 13:&t;End of Frame (q1) */
DECL|macro|IRQ_R1_C
mdefine_line|#define&t;IRQ_R1_C&t;(1L&lt;&lt;12)&t;/* Bit 12:&t;Encoding Error (q1) */
multiline_comment|/* Receive Queue 2 */
DECL|macro|IRQ_R2_P
mdefine_line|#define&t;IRQ_R2_P&t;(1L&lt;&lt;11)&t;/* Bit 11: (DV)&t;Parity Error (q2) */
DECL|macro|IRQ_R2_B
mdefine_line|#define&t;IRQ_R2_B&t;(1L&lt;&lt;10)&t;/* Bit 10: (DV)&t;End of Buffer (q2) */
DECL|macro|IRQ_R2_F
mdefine_line|#define&t;IRQ_R2_F&t;(1L&lt;&lt;9)&t;&t;/* Bit&t;9: (DV)&t;End of Frame (q2) */
DECL|macro|IRQ_R2_C
mdefine_line|#define&t;IRQ_R2_C&t;(1L&lt;&lt;8)&t;&t;/* Bit&t;8: (DV)&t;Encoding Error (q2) */
multiline_comment|/* Asynchronous Transmit queue */
multiline_comment|/* Bit  7:&t;reserved */
DECL|macro|IRQ_XA_B
mdefine_line|#define&t;IRQ_XA_B&t;(1L&lt;&lt;6)&t;&t;/* Bit&t;6:&t;End of Buffer (xa) */
DECL|macro|IRQ_XA_F
mdefine_line|#define&t;IRQ_XA_F&t;(1L&lt;&lt;5)&t;&t;/* Bit&t;5:&t;End of Frame (xa) */
DECL|macro|IRQ_XA_C
mdefine_line|#define&t;IRQ_XA_C&t;(1L&lt;&lt;4)&t;&t;/* Bit&t;4:&t;Encoding Error (xa) */
multiline_comment|/* Synchronous Transmit queue */
multiline_comment|/* Bit  3:&t;reserved */
DECL|macro|IRQ_XS_B
mdefine_line|#define&t;IRQ_XS_B&t;(1L&lt;&lt;2)&t;&t;/* Bit&t;2:&t;End of Buffer (xs) */
DECL|macro|IRQ_XS_F
mdefine_line|#define&t;IRQ_XS_F&t;(1L&lt;&lt;1)&t;&t;/* Bit&t;1:&t;End of Frame (xs) */
DECL|macro|IRQ_XS_C
mdefine_line|#define&t;IRQ_XS_C&t;(1L&lt;&lt;0)&t;&t;/* Bit&t;0:&t;Encoding Error (xs) */
multiline_comment|/* 0x0010 - 0x006b:&t;formac+ (supernet_3) fequently used registers */
multiline_comment|/*&t;B0_R1_CSR&t;32 bit BMU control/status reg (rec q 1 ) */
multiline_comment|/*&t;B0_R2_CSR&t;32 bit BMU control/status reg (rec q 2 ) */
multiline_comment|/*&t;B0_XA_CSR&t;32 bit BMU control/status reg (a xmit q ) */
multiline_comment|/*&t;B0_XS_CSR&t;32 bit BMU control/status reg (s xmit q ) */
multiline_comment|/* The registers are the same as B4_R1_CSR, B4_R2_CSR, B5_Xa_CSR, B5_XS_CSR */
multiline_comment|/*&t;B2_MAC_0&t;8 bit MAC address Byte 0 */
multiline_comment|/*&t;B2_MAC_1&t;8 bit MAC address Byte 1 */
multiline_comment|/*&t;B2_MAC_2&t;8 bit MAC address Byte 2 */
multiline_comment|/*&t;B2_MAC_3&t;8 bit MAC address Byte 3 */
multiline_comment|/*&t;B2_MAC_4&t;8 bit MAC address Byte 4 */
multiline_comment|/*&t;B2_MAC_5&t;8 bit MAC address Byte 5 */
multiline_comment|/*&t;B2_MAC_6&t;8 bit MAC address Byte 6 (== 0) (DV) */
multiline_comment|/*&t;B2_MAC_7&t;8 bit MAC address Byte 7 (== 0) (DV) */
multiline_comment|/*&t;B2_CONN_TYP&t;8 bit Connector type */
multiline_comment|/*&t;B2_PMD_TYP&t;8 bit PMD type */
multiline_comment|/*&t;Values of connector and PMD type comply to SysKonnect internal std */
multiline_comment|/*&t;The EPROM register are currently of no use */
multiline_comment|/*&t;B2_E_0&t;&t;8 bit EPROM Byte 0 */
multiline_comment|/*&t;B2_E_1&t;&t;8 bit EPROM Byte 1 */
multiline_comment|/*&t;B2_E_2&t;&t;8 bit EPROM Byte 2 */
multiline_comment|/*&t;B2_E_3&t;&t;8 bit EPROM Byte 3 */
multiline_comment|/*&t;B2_FAR&t;&t;32 bit Flash-Prom Address Register/Counter */
DECL|macro|FAR_ADDR
mdefine_line|#define&t;FAR_ADDR&t;0x1ffffL&t;/* Bit 16..0:&t;FPROM Address mask */
multiline_comment|/*&t;B2_FDP&t;&t;8 bit Flash-Prom Data Port */
multiline_comment|/*&t;B2_LD_CRTL&t;8 bit loader control */
multiline_comment|/*&t;Bits are currently reserved */
multiline_comment|/*&t;B2_LD_TEST&t;8 bit loader test */
DECL|macro|LD_T_ON
mdefine_line|#define&t;LD_T_ON&t;&t;(1&lt;&lt;3)&t;/* Bit 3:    Loader Testmode on */
DECL|macro|LD_T_OFF
mdefine_line|#define&t;LD_T_OFF&t;(1&lt;&lt;2)&t;/* Bit 2:    Loader Testmode off */
DECL|macro|LD_T_STEP
mdefine_line|#define&t;LD_T_STEP&t;(1&lt;&lt;1)&t;/* Bit 1:    Decrement FPROM addr. Counter */
DECL|macro|LD_START
mdefine_line|#define&t;LD_START&t;(1&lt;&lt;0)&t;/* Bit 0:    Start loading FPROM */
multiline_comment|/*&t;B2_TI_INI&t;32 bit Timer init value */
multiline_comment|/*&t;B2_TI_VAL&t;32 bit Timer value */
multiline_comment|/*&t;B2_TI_CRTL&t;8 bit Timer control */
multiline_comment|/*&t;B2_TI_TEST&t;8 Bit Timer Test */
multiline_comment|/*&t;B2_WDOG_INI&t;32 bit Watchdog init value */
multiline_comment|/*&t;B2_WDOG_VAL&t;32 bit Watchdog value */
multiline_comment|/*&t;B2_WDOG_CRTL&t;8 bit Watchdog control */
multiline_comment|/*&t;B2_WDOG_TEST&t;8 Bit Watchdog Test */
multiline_comment|/*&t;B2_RTM_INI&t;32 bit RTM init value */
multiline_comment|/*&t;B2_RTM_VAL&t;32 bit RTM value */
multiline_comment|/*&t;B2_RTM_CRTL&t;8 bit RTM control */
multiline_comment|/*&t;B2_RTM_TEST&t;8 Bit RTM Test */
multiline_comment|/*&t;B2_&lt;TIM&gt;_CRTL&t;8 bit &lt;TIM&gt; control */
multiline_comment|/*&t;B2_IRQ_MOD_INI&t;32 bit IRQ Moderation Timer Init Reg.&t;(ML) */
multiline_comment|/*&t;B2_IRQ_MOD_VAL&t;32 bit IRQ Moderation Timer Value&t;(ML) */
multiline_comment|/*&t;B2_IRQ_MOD_CTRL&t;8 bit IRQ Moderation Timer Control&t;(ML) */
multiline_comment|/*&t;B2_IRQ_MOD_TEST&t;8 bit IRQ Moderation Timer Test&t;&t;(ML) */
DECL|macro|GET_TOK_CT
mdefine_line|#define GET_TOK_CT&t;(1&lt;&lt;4)&t;/* Bit 4: Get the Token Counter (RTM) */
DECL|macro|TIM_RES_TOK
mdefine_line|#define TIM_RES_TOK&t;(1&lt;&lt;3)&t;/* Bit 3: RTM Status: 1 == restricted */
DECL|macro|TIM_ALARM
mdefine_line|#define TIM_ALARM&t;(1&lt;&lt;3)&t;/* Bit 3: Timer Alarm (WDOG) */
DECL|macro|TIM_START
mdefine_line|#define TIM_START&t;(1&lt;&lt;2)&t;/* Bit 2: Start Timer (TI,WDOG,RTM,IRQ_MOD)*/
DECL|macro|TIM_STOP
mdefine_line|#define TIM_STOP&t;(1&lt;&lt;1)&t;/* Bit 1: Stop Timer (TI,WDOG,RTM,IRQ_MOD) */
DECL|macro|TIM_CL_IRQ
mdefine_line|#define TIM_CL_IRQ&t;(1&lt;&lt;0)&t;/* Bit 0: Clear Timer IRQ (TI,WDOG,RTM) */
multiline_comment|/*&t;B2_&lt;TIM&gt;_TEST&t;8 Bit &lt;TIM&gt; Test */
DECL|macro|TIM_T_ON
mdefine_line|#define&t;TIM_T_ON&t;(1&lt;&lt;2)&t;/* Bit 2: Test mode on (TI,WDOG,RTM,IRQ_MOD) */
DECL|macro|TIM_T_OFF
mdefine_line|#define&t;TIM_T_OFF&t;(1&lt;&lt;1)&t;/* Bit 1: Test mode off (TI,WDOG,RTM,IRQ_MOD) */
DECL|macro|TIM_T_STEP
mdefine_line|#define&t;TIM_T_STEP&t;(1&lt;&lt;0)&t;/* Bit 0: Test step (TI,WDOG,RTM,IRQ_MOD) */
multiline_comment|/*&t;B2_TOK_COUNT&t;0x014c&t;(ML)&t;32 bit&t;Token Counter */
multiline_comment|/*&t;B2_DESC_ADDR_H&t;0x0150&t;(ML)&t;32 bit&t;Desciptor Base Addr Reg High */
multiline_comment|/*&t;B2_CTRL_2&t;0x0154&t;(ML)&t; 8 bit&t;Control Register 2 */
multiline_comment|/* Bit 7..5:&t;reserved&t;&t;*/
DECL|macro|CTRL_CL_I2C_IRQ
mdefine_line|#define CTRL_CL_I2C_IRQ (1&lt;&lt;4)&t;/* Bit 4:&t;Clear I2C IRQ&t;&t;*/
DECL|macro|CTRL_ST_SW_IRQ
mdefine_line|#define CTRL_ST_SW_IRQ&t;(1&lt;&lt;3)&t;/* Bit 3:&t;Set IRQ SW Request&t;*/
DECL|macro|CTRL_CL_SW_IRQ
mdefine_line|#define CTRL_CL_SW_IRQ&t;(1&lt;&lt;2)&t;/* Bit 2:&t;Clear IRQ SW Request&t;*/
DECL|macro|CTRL_STOP_DONE
mdefine_line|#define CTRL_STOP_DONE&t;(1&lt;&lt;1)&t;/* Bit 1:&t;Stop Master is finished */
DECL|macro|CTRL_STOP_MAST
mdefine_line|#define&t;CTRL_STOP_MAST&t;(1&lt;&lt;0)&t;/* Bit 0:&t;Command Bit to stop the master*/
multiline_comment|/*&t;B2_IFACE_REG&t;0x0155&t;(ML)&t; 8 bit&t;Interface Register */
multiline_comment|/* Bit 7..3:&t;reserved&t;&t;*/
DECL|macro|IF_I2C_DATA_DIR
mdefine_line|#define&t;IF_I2C_DATA_DIR&t;(1&lt;&lt;2)&t;/* Bit 2:&t;direction of IF_I2C_DATA*/
DECL|macro|IF_I2C_DATA
mdefine_line|#define IF_I2C_DATA&t;(1&lt;&lt;1)&t;/* Bit 1:&t;I2C Data Port&t;&t;*/
DECL|macro|IF_I2C_CLK
mdefine_line|#define&t;IF_I2C_CLK&t;(1&lt;&lt;0)&t;/* Bit 0:&t;I2C Clock Port&t;&t;*/
multiline_comment|/* 0x0156:&t;&t;reserved */
multiline_comment|/*&t;B2_TST_CTRL_2&t;0x0157&t;(ML)&t; 8 bit&t;Test Control Register 2 */
multiline_comment|/* Bit 7..4:&t;reserved */
multiline_comment|/* force the following error on */
multiline_comment|/* the next master read/write&t;*/
DECL|macro|TST_FRC_DPERR_MR64
mdefine_line|#define TST_FRC_DPERR_MR64&t;(1&lt;&lt;3)&t;/* Bit 3:&t;DataPERR RD 64&t;*/
DECL|macro|TST_FRC_DPERR_MW64
mdefine_line|#define TST_FRC_DPERR_MW64&t;(1&lt;&lt;2)&t;/* Bit 2:&t;DataPERR WR 64&t;*/
DECL|macro|TST_FRC_APERR_1M64
mdefine_line|#define TST_FRC_APERR_1M64&t;(1&lt;&lt;1)&t;/* Bit 1:&t;AddrPERR on 1. phase */
DECL|macro|TST_FRC_APERR_2M64
mdefine_line|#define TST_FRC_APERR_2M64&t;(1&lt;&lt;0)&t;/* Bit 0:&t;AddrPERR on 2. phase */
multiline_comment|/*&t;B2_I2C_CTRL&t;0x0158&t;(ML)&t;32 bit&t;I2C Control Register&t;       */
DECL|macro|I2C_FLAG
mdefine_line|#define&t;I2C_FLAG&t;(1L&lt;&lt;31)&t;/* Bit 31:&t;Start read/write if WR */
DECL|macro|I2C_ADDR
mdefine_line|#define I2C_ADDR&t;(0x7fffL&lt;&lt;16)&t;/* Bit 30..16:&t;Addr to be read/written*/
DECL|macro|I2C_DEV_SEL
mdefine_line|#define&t;I2C_DEV_SEL&t;(0x7fL&lt;&lt;9)&t;/* Bit  9..15:&t;I2C Device Select      */
multiline_comment|/* Bit  5.. 8:&t;reserved&t;       */
DECL|macro|I2C_BURST_LEN
mdefine_line|#define I2C_BURST_LEN&t;(1L&lt;&lt;4)&t;&t;/* Bit  4&t;Burst Len, 1/4 bytes   */
DECL|macro|I2C_DEV_SIZE
mdefine_line|#define I2C_DEV_SIZE&t;(7L&lt;&lt;1)&t;&t;/* Bit&t;1.. 3:&t;I2C Device Size&t;       */
DECL|macro|I2C_025K_DEV
mdefine_line|#define I2C_025K_DEV&t;(0L&lt;&lt;1)&t;&t;/*&t;&t;0: 256 Bytes or smaller*/
DECL|macro|I2C_05K_DEV
mdefine_line|#define I2C_05K_DEV&t;(1L&lt;&lt;1)&t;&t;/* &t;&t;1: 512&t;Bytes&t;       */
DECL|macro|I2C_1K_DEV
mdefine_line|#define&t;I2C_1K_DEV&t;(2L&lt;&lt;1)&t;&t;/*&t;&t;2: 1024 Bytes&t;       */
DECL|macro|I2C_2K_DEV
mdefine_line|#define I2C_2K_DEV&t;(3L&lt;&lt;1)&t;&t;/*&t;&t;3: 2048&t;Bytes&t;       */
DECL|macro|I2C_4K_DEV
mdefine_line|#define&t;I2C_4K_DEV&t;(4L&lt;&lt;1)&t;&t;/*&t;&t;4: 4096 Bytes&t;       */
DECL|macro|I2C_8K_DEV
mdefine_line|#define&t;I2C_8K_DEV&t;(5L&lt;&lt;1)&t;&t;/*&t;&t;5: 8192 Bytes&t;       */
DECL|macro|I2C_16K_DEV
mdefine_line|#define&t;I2C_16K_DEV&t;(6L&lt;&lt;1)&t;&t;/*&t;&t;6: 16384 Bytes&t;       */
DECL|macro|I2C_32K_DEV
mdefine_line|#define&t;I2C_32K_DEV&t;(7L&lt;&lt;1)&t;&t;/*&t;&t;7: 32768 Bytes&t;       */
DECL|macro|I2C_STOP_BIT
mdefine_line|#define I2C_STOP_BIT&t;(1&lt;&lt;0)&t;&t;/* Bit  0:&t;Interrupt I2C transfer */
multiline_comment|/*&n; * I2C Addresses&n; *&n; * The temperature sensor and the voltage sensor are on the same I2C bus.&n; * Note: The voltage sensor (Micorwire) will be selected by PCI_EXT_PATCH_1&n; *&t; in PCI_OUR_REG 1.&n; */
DECL|macro|I2C_ADDR_TEMP
mdefine_line|#define&t;I2C_ADDR_TEMP&t;0x90&t;/* I2C Address Temperature Sensor */
multiline_comment|/*&t;B2_I2C_DATA&t;0x015c&t;(ML)&t;32 bit&t;I2C Data Register */
multiline_comment|/*&t;B4_R1_D&t;&t;4*32 bit current receive Descriptor&t;(q1) */
multiline_comment|/*&t;B4_R1_DA&t;32 bit current rec desc address&t;&t;(q1) */
multiline_comment|/*&t;B4_R1_AC&t;32 bit current receive Address Count&t;(q1) */
multiline_comment|/*&t;B4_R1_BC&t;32 bit current receive Byte Counter&t;(q1) */
multiline_comment|/*&t;B4_R1_CSR&t;32 bit BMU Control/Status Register&t;(q1) */
multiline_comment|/*&t;B4_R1_F&t;&t;32 bit flag register&t;&t;&t;(q1) */
multiline_comment|/*&t;B4_R1_T1&t;32 bit Test Register 1&t;&t; &t;(q1) */
multiline_comment|/*&t;B4_R1_T2&t;32 bit Test Register 2&t;&t; &t;(q1) */
multiline_comment|/*&t;B4_R1_T3&t;32 bit Test Register 3&t;&t; &t;(q1) */
multiline_comment|/*&t;B4_R2_D&t;&t;4*32 bit current receive Descriptor&t;(q2) */
multiline_comment|/*&t;B4_R2_DA&t;32 bit current rec desc address&t;&t;(q2) */
multiline_comment|/*&t;B4_R2_AC&t;32 bit current receive Address Count&t;(q2) */
multiline_comment|/*&t;B4_R2_BC&t;32 bit current receive Byte Counter&t;(q2) */
multiline_comment|/*&t;B4_R2_CSR&t;32 bit BMU Control/Status Register&t;(q2) */
multiline_comment|/*&t;B4_R2_F&t;&t;32 bit flag register&t;&t;&t;(q2) */
multiline_comment|/*&t;B4_R2_T1&t;32 bit Test Register 1&t;&t;&t;(q2) */
multiline_comment|/*&t;B4_R2_T2&t;32 bit Test Register 2&t;&t;&t;(q2) */
multiline_comment|/*&t;B4_R2_T3&t;32 bit Test Register 3&t;&t;&t;(q2) */
multiline_comment|/*&t;B5_XA_D&t;&t;4*32 bit current receive Descriptor&t;(xa) */
multiline_comment|/*&t;B5_XA_DA&t;32 bit current rec desc address&t;&t;(xa) */
multiline_comment|/*&t;B5_XA_AC&t;32 bit current receive Address Count&t;(xa) */
multiline_comment|/*&t;B5_XA_BC&t;32 bit current receive Byte Counter&t;(xa) */
multiline_comment|/*&t;B5_XA_CSR&t;32 bit BMU Control/Status Register&t;(xa) */
multiline_comment|/*&t;B5_XA_F&t;&t;32 bit flag register&t;&t;&t;(xa) */
multiline_comment|/*&t;B5_XA_T1&t;32 bit Test Register 1&t;&t;&t;(xa) */
multiline_comment|/*&t;B5_XA_T2&t;32 bit Test Register 2&t;&t;&t;(xa) */
multiline_comment|/*&t;B5_XA_T3&t;32 bit Test Register 3&t;&t;&t;(xa) */
multiline_comment|/*&t;B5_XS_D&t;&t;4*32 bit current receive Descriptor&t;(xs) */
multiline_comment|/*&t;B5_XS_DA&t;32 bit current rec desc address&t;&t;(xs) */
multiline_comment|/*&t;B5_XS_AC&t;32 bit current receive Address Count&t;(xs) */
multiline_comment|/*&t;B5_XS_BC&t;32 bit current receive Byte Counter&t;(xs) */
multiline_comment|/*&t;B5_XS_CSR&t;32 bit BMU Control/Status Register&t;(xs) */
multiline_comment|/*&t;B5_XS_F&t;&t;32 bit flag register&t;&t;&t;(xs) */
multiline_comment|/*&t;B5_XS_T1&t;32 bit Test Register 1&t;&t;&t;(xs) */
multiline_comment|/*&t;B5_XS_T2&t;32 bit Test Register 2&t;&t;&t;(xs) */
multiline_comment|/*&t;B5_XS_T3&t;32 bit Test Register 3&t;&t;&t;(xs) */
multiline_comment|/*&t;B5_&lt;xx&gt;_CSR&t;32 bit BMU Control/Status Register&t;(xx) */
DECL|macro|CSR_DESC_CLEAR
mdefine_line|#define&t;CSR_DESC_CLEAR&t;(1L&lt;&lt;21)    /* Bit 21:&t;Clear Reset for Descr */
DECL|macro|CSR_DESC_SET
mdefine_line|#define&t;CSR_DESC_SET&t;(1L&lt;&lt;20)    /* Bit 20:&t;Set Reset for Descr */
DECL|macro|CSR_FIFO_CLEAR
mdefine_line|#define&t;CSR_FIFO_CLEAR&t;(1L&lt;&lt;19)    /* Bit 19:&t;Clear Reset for FIFO */
DECL|macro|CSR_FIFO_SET
mdefine_line|#define&t;CSR_FIFO_SET&t;(1L&lt;&lt;18)    /* Bit 18:&t;Set Reset for FIFO */
DECL|macro|CSR_HPI_RUN
mdefine_line|#define&t;CSR_HPI_RUN&t;(1L&lt;&lt;17)    /* Bit 17:&t;Release HPI SM */
DECL|macro|CSR_HPI_RST
mdefine_line|#define&t;CSR_HPI_RST&t;(1L&lt;&lt;16)    /* Bit 16:&t;Reset HPI SM to Idle */
DECL|macro|CSR_SV_RUN
mdefine_line|#define&t;CSR_SV_RUN&t;(1L&lt;&lt;15)    /* Bit 15:&t;Release Supervisor SM */
DECL|macro|CSR_SV_RST
mdefine_line|#define&t;CSR_SV_RST&t;(1L&lt;&lt;14)    /* Bit 14:&t;Reset Supervisor SM */
DECL|macro|CSR_DREAD_RUN
mdefine_line|#define&t;CSR_DREAD_RUN&t;(1L&lt;&lt;13)    /* Bit 13:&t;Release Descr Read SM */
DECL|macro|CSR_DREAD_RST
mdefine_line|#define&t;CSR_DREAD_RST&t;(1L&lt;&lt;12)    /* Bit 12:&t;Reset Descr Read SM */
DECL|macro|CSR_DWRITE_RUN
mdefine_line|#define&t;CSR_DWRITE_RUN&t;(1L&lt;&lt;11)    /* Bit 11:&t;Rel. Descr Write SM */
DECL|macro|CSR_DWRITE_RST
mdefine_line|#define&t;CSR_DWRITE_RST&t;(1L&lt;&lt;10)    /* Bit 10:&t;Reset Descr Write SM */
DECL|macro|CSR_TRANS_RUN
mdefine_line|#define&t;CSR_TRANS_RUN&t;(1L&lt;&lt;9)     /* Bit 9:&t;Release Transfer SM */
DECL|macro|CSR_TRANS_RST
mdefine_line|#define&t;CSR_TRANS_RST&t;(1L&lt;&lt;8)     /* Bit 8:&t;Reset Transfer SM */
multiline_comment|/* Bit 7..5: reserved */
DECL|macro|CSR_START
mdefine_line|#define&t;CSR_START&t;(1L&lt;&lt;4)     /* Bit 4:&t;Start Rec/Xmit Queue */
DECL|macro|CSR_IRQ_CL_P
mdefine_line|#define&t;CSR_IRQ_CL_P&t;(1L&lt;&lt;3)     /* Bit 3:&t;Clear Parity IRQ, Rcv */
DECL|macro|CSR_IRQ_CL_B
mdefine_line|#define&t;CSR_IRQ_CL_B&t;(1L&lt;&lt;2)     /* Bit 2:&t;Clear EOB IRQ */
DECL|macro|CSR_IRQ_CL_F
mdefine_line|#define&t;CSR_IRQ_CL_F&t;(1L&lt;&lt;1)     /* Bit 1:&t;Clear EOF IRQ */
DECL|macro|CSR_IRQ_CL_C
mdefine_line|#define&t;CSR_IRQ_CL_C&t;(1L&lt;&lt;0)     /* Bit 0:&t;Clear ERR IRQ */
DECL|macro|CSR_SET_RESET
mdefine_line|#define CSR_SET_RESET&t;(CSR_DESC_SET|CSR_FIFO_SET|CSR_HPI_RST|CSR_SV_RST|&bslash;&n;&t;&t;&t;CSR_DREAD_RST|CSR_DWRITE_RST|CSR_TRANS_RST)
DECL|macro|CSR_CLR_RESET
mdefine_line|#define CSR_CLR_RESET&t;(CSR_DESC_CLEAR|CSR_FIFO_CLEAR|CSR_HPI_RUN|CSR_SV_RUN|&bslash;&n;&t;&t;&t;CSR_DREAD_RUN|CSR_DWRITE_RUN|CSR_TRANS_RUN)
multiline_comment|/*&t;B5_&lt;xx&gt;_F&t;32 bit flag register&t;&t; (xx) */
multiline_comment|/* Bit 28..31:&t;reserved&t;      */
DECL|macro|F_ALM_FULL
mdefine_line|#define F_ALM_FULL&t;(1L&lt;&lt;27)&t;/* Bit 27: (ML)&t;FIFO almost full      */
DECL|macro|F_FIFO_EOF
mdefine_line|#define F_FIFO_EOF&t;(1L&lt;&lt;26)&t;/* Bit 26: (ML)&t;Fag bit in FIFO       */
DECL|macro|F_WM_REACHED
mdefine_line|#define F_WM_REACHED&t;(1L&lt;&lt;25)&t;/* Bit 25: (ML)&t;Watermark reached     */
DECL|macro|F_UP_DW_USED
mdefine_line|#define F_UP_DW_USED&t;(1L&lt;&lt;24)&t;/* Bit 24: (ML) Upper Dword used (bug)*/
multiline_comment|/* Bit 23: &t;reserved&t;      */
DECL|macro|F_FIFO_LEVEL
mdefine_line|#define F_FIFO_LEVEL&t;(0x1fL&lt;&lt;16)&t;/* Bit 16..22:(ML) # of Qwords in FIFO*/
multiline_comment|/* Bit  8..15: &t;reserved&t;      */
DECL|macro|F_ML_WATER_M
mdefine_line|#define F_ML_WATER_M&t;0x0000ffL&t;/* Bit  0.. 7:(ML) Watermark&t;      */
DECL|macro|FLAG_WATER
mdefine_line|#define&t;FLAG_WATER&t;0x00001fL&t;/* Bit 4..0:(DV) Level of req data tr.*/
multiline_comment|/*&t;B5_&lt;xx&gt;_T1&t;32 bit Test Register 1&t;&t; (xx) */
multiline_comment|/*&t;&t;Holds four State Machine control Bytes */
DECL|macro|SM_CRTL_SV
mdefine_line|#define&t;SM_CRTL_SV&t;(0xffL&lt;&lt;24) /* Bit 31..24:  Control Supervisor SM */
DECL|macro|SM_CRTL_RD
mdefine_line|#define&t;SM_CRTL_RD&t;(0xffL&lt;&lt;16) /* Bit 23..16:  Control Read Desc SM */
DECL|macro|SM_CRTL_WR
mdefine_line|#define&t;SM_CRTL_WR&t;(0xffL&lt;&lt;8)  /* Bit 15..8:   Control Write Desc SM */
DECL|macro|SM_CRTL_TR
mdefine_line|#define&t;SM_CRTL_TR&t;(0xffL&lt;&lt;0)  /* Bit 7..0:    Control Transfer SM */
multiline_comment|/*&t;B4_&lt;xx&gt;_T1_TR&t;8 bit Test Register 1 TR&t;&t;(xx) */
multiline_comment|/*&t;B4_&lt;xx&gt;_T1_WR&t;8 bit Test Register 1 WR&t;&t;(xx) */
multiline_comment|/*&t;B4_&lt;xx&gt;_T1_RD&t;8 bit Test Register 1 RD&t;&t;(xx) */
multiline_comment|/*&t;B4_&lt;xx&gt;_T1_SV&t;8 bit Test Register 1 SV&t;&t;(xx) */
multiline_comment|/* The control status byte of each machine looks like ... */
DECL|macro|SM_STATE
mdefine_line|#define&t;SM_STATE&t;0xf0&t;/* Bit 7..4:&t;State which shall be loaded */
DECL|macro|SM_LOAD
mdefine_line|#define&t;SM_LOAD&t;&t;0x08&t;/* Bit 3:&t;Load the SM with SM_STATE */
DECL|macro|SM_TEST_ON
mdefine_line|#define&t;SM_TEST_ON&t;0x04&t;/* Bit 2:&t;Switch on SM Test Mode */
DECL|macro|SM_TEST_OFF
mdefine_line|#define&t;SM_TEST_OFF&t;0x02&t;/* Bit 1:&t;Go off the Test Mode */
DECL|macro|SM_STEP
mdefine_line|#define&t;SM_STEP&t;&t;0x01&t;/* Bit 0:&t;Step the State Machine */
multiline_comment|/* The coding of the states */
DECL|macro|SM_SV_IDLE
mdefine_line|#define&t;SM_SV_IDLE&t;0x0&t;/* Supervisor&t;Idle&t;&t;Tr/Re&t;     */
DECL|macro|SM_SV_RES_START
mdefine_line|#define&t;SM_SV_RES_START&t;0x1&t;/* Supervisor&t;Res_Start&t;Tr/Re&t;     */
DECL|macro|SM_SV_GET_DESC
mdefine_line|#define&t;SM_SV_GET_DESC&t;0x3&t;/* Supervisor&t;Get_Desc&t;Tr/Re&t;     */
DECL|macro|SM_SV_CHECK
mdefine_line|#define&t;SM_SV_CHECK&t;0x2&t;/* Supervisor&t;Check&t;&t;Tr/Re&t;     */
DECL|macro|SM_SV_MOV_DATA
mdefine_line|#define&t;SM_SV_MOV_DATA&t;0x6&t;/* Supervisor&t;Move_Data&t;Tr/Re&t;     */
DECL|macro|SM_SV_PUT_DESC
mdefine_line|#define&t;SM_SV_PUT_DESC&t;0x7&t;/* Supervisor&t;Put_Desc&t;Tr/Re&t;     */
DECL|macro|SM_SV_SET_IRQ
mdefine_line|#define&t;SM_SV_SET_IRQ&t;0x5&t;/* Supervisor&t;Set_Irq&t;&t;Tr/Re&t;     */
DECL|macro|SM_RD_IDLE
mdefine_line|#define&t;SM_RD_IDLE&t;0x0&t;/* Read Desc.&t;Idle&t;&t;Tr/Re&t;     */
DECL|macro|SM_RD_LOAD
mdefine_line|#define&t;SM_RD_LOAD&t;0x1&t;/* Read Desc.&t;Load&t;&t;Tr/Re&t;     */
DECL|macro|SM_RD_WAIT_TC
mdefine_line|#define&t;SM_RD_WAIT_TC&t;0x3&t;/* Read Desc.&t;Wait_TC&t;&t;Tr/Re&t;     */
DECL|macro|SM_RD_RST_EOF
mdefine_line|#define&t;SM_RD_RST_EOF&t;0x6&t;/* Read Desc.&t;Reset_EOF&t;   Re&t;     */
DECL|macro|SM_RD_WDONE_R
mdefine_line|#define&t;SM_RD_WDONE_R&t;0x2&t;/* Read Desc.&t;Wait_Done&t;   Re&t;     */
DECL|macro|SM_RD_WDONE_T
mdefine_line|#define&t;SM_RD_WDONE_T&t;0x4&t;/* Read Desc.&t;Wait_Done&t;Tr   &t;     */
DECL|macro|SM_TR_IDLE
mdefine_line|#define&t;SM_TR_IDLE&t;0x0&t;/* Trans. Data&t;Idle&t;&t;Tr/Re&t;     */
DECL|macro|SM_TR_LOAD
mdefine_line|#define&t;SM_TR_LOAD&t;0x3&t;/* Trans. Data&t;Load&t;&t;Tr/Re&t;     */
DECL|macro|SM_TR_LOAD_R_ML
mdefine_line|#define&t;SM_TR_LOAD_R_ML&t;0x1&t;/* Trans. Data&t;Load&t;&t;  /Re&t;(ML) */
DECL|macro|SM_TR_WAIT_TC
mdefine_line|#define&t;SM_TR_WAIT_TC&t;0x2&t;/* Trans. Data&t;Wait_TC&t;&t;Tr/Re&t;     */
DECL|macro|SM_TR_WDONE
mdefine_line|#define&t;SM_TR_WDONE&t;0x4&t;/* Trans. Data&t;Wait_Done&t;Tr/Re&t;     */
DECL|macro|SM_WR_IDLE
mdefine_line|#define&t;SM_WR_IDLE&t;0x0&t;/* Write Desc.&t;Idle&t;&t;Tr/Re&t;     */
DECL|macro|SM_WR_ABLEN
mdefine_line|#define&t;SM_WR_ABLEN&t;0x1&t;/* Write Desc.&t;Act_Buf_Length&t;Tr/Re&t;     */
DECL|macro|SM_WR_LD_A4
mdefine_line|#define&t;SM_WR_LD_A4&t;0x2&t;/* Write Desc.&t;Load_A4&t;&t;   Re&t;     */
DECL|macro|SM_WR_RES_OWN
mdefine_line|#define&t;SM_WR_RES_OWN&t;0x2&t;/* Write Desc.&t;Res_OWN&t;&t;Tr   &t;     */
DECL|macro|SM_WR_WAIT_EOF
mdefine_line|#define&t;SM_WR_WAIT_EOF&t;0x3&t;/* Write Desc.&t;Wait_EOF&t;   Re&t;     */
DECL|macro|SM_WR_LD_N2C_R
mdefine_line|#define&t;SM_WR_LD_N2C_R&t;0x4&t;/* Write Desc.&t;Load_N2C&t;   Re&t;     */
DECL|macro|SM_WR_WAIT_TC_R
mdefine_line|#define&t;SM_WR_WAIT_TC_R&t;0x5&t;/* Write Desc.&t;Wait_TC&t;&t;   Re&t;     */
DECL|macro|SM_WR_WAIT_TC4
mdefine_line|#define&t;SM_WR_WAIT_TC4&t;0x6&t;/* Write Desc.&t;Wait_TC4&t;   Re&t;     */
DECL|macro|SM_WR_LD_A_T
mdefine_line|#define&t;SM_WR_LD_A_T&t;0x6&t;/* Write Desc.&t;Load_A&t;&t;Tr   &t;     */
DECL|macro|SM_WR_LD_A_R
mdefine_line|#define&t;SM_WR_LD_A_R&t;0x7&t;/* Write Desc.&t;Load_A&t;&t;   Re&t;     */
DECL|macro|SM_WR_WAIT_TC_T
mdefine_line|#define&t;SM_WR_WAIT_TC_T&t;0x7&t;/* Write Desc.&t;Wait_TC&t;&t;Tr   &t;     */
DECL|macro|SM_WR_LD_N2C_T
mdefine_line|#define&t;SM_WR_LD_N2C_T&t;0xc&t;/* Write Desc.&t;Load_N2C&t;Tr   &t;     */
DECL|macro|SM_WR_WDONE_T
mdefine_line|#define&t;SM_WR_WDONE_T&t;0x9&t;/* Write Desc.&t;Wait_Done&t;Tr   &t;     */
DECL|macro|SM_WR_WDONE_R
mdefine_line|#define&t;SM_WR_WDONE_R&t;0xc&t;/* Write Desc.&t;Wait_Done&t;   Re&t;     */
DECL|macro|SM_WR_LD_D_AD
mdefine_line|#define SM_WR_LD_D_AD&t;0xe&t;/* Write Desc.  Load_Dumr_A&t;   Re&t;(ML) */
DECL|macro|SM_WR_WAIT_D_TC
mdefine_line|#define SM_WR_WAIT_D_TC&t;0xf&t;/* Write Desc.&t;Wait_Dumr_TC&t;   Re&t;(ML) */
multiline_comment|/*&t;B5_&lt;xx&gt;_T2&t;32 bit Test Register 2&t;&t; (xx) */
multiline_comment|/* Note: This register is only defined for the transmit queues */
multiline_comment|/* Bit 31..8:&t;reserved */
DECL|macro|AC_TEST_ON
mdefine_line|#define&t;AC_TEST_ON&t;(1&lt;&lt;7)&t;/* Bit 7:&t;Address Counter Test Mode on */
DECL|macro|AC_TEST_OFF
mdefine_line|#define&t;AC_TEST_OFF&t;(1&lt;&lt;6)&t;/* Bit 6:&t;Address Counter Test Mode off*/
DECL|macro|BC_TEST_ON
mdefine_line|#define&t;BC_TEST_ON&t;(1&lt;&lt;5)&t;/* Bit 5:&t;Byte Counter Test Mode on */
DECL|macro|BC_TEST_OFF
mdefine_line|#define&t;BC_TEST_OFF&t;(1&lt;&lt;4)&t;/* Bit 4:&t;Byte Counter Test Mode off */
DECL|macro|TEST_STEP04
mdefine_line|#define&t;TEST_STEP04&t;(1&lt;&lt;3)&t;/* Bit 3:&t;Inc AC/Dec BC by 4 */
DECL|macro|TEST_STEP03
mdefine_line|#define&t;TEST_STEP03&t;(1&lt;&lt;2)&t;/* Bit 2:&t;Inc AC/Dec BC by 3 */
DECL|macro|TEST_STEP02
mdefine_line|#define&t;TEST_STEP02&t;(1&lt;&lt;1)&t;/* Bit 1:&t;Inc AC/Dec BC by 2 */
DECL|macro|TEST_STEP01
mdefine_line|#define&t;TEST_STEP01&t;(1&lt;&lt;0)&t;/* Bit 0:&t;Inc AC/Dec BC by 1 */
multiline_comment|/*&t;B5_&lt;xx&gt;_T3&t;32 bit Test Register 3&t;&t; (xx) */
multiline_comment|/* Note: This register is only defined for the transmit queues */
multiline_comment|/* Bit 31..8:&t;reserved */
DECL|macro|T3_MUX_2
mdefine_line|#define T3_MUX_2&t;(1&lt;&lt;7)&t;/* Bit 7: (ML)&t;Mux position MSB */
DECL|macro|T3_VRAM_2
mdefine_line|#define T3_VRAM_2&t;(1&lt;&lt;6)&t;/* Bit 6: (ML)&t;Virtual RAM buffer addr MSB */
DECL|macro|T3_LOOP
mdefine_line|#define&t;T3_LOOP&t;&t;(1&lt;&lt;5)&t;/* Bit 5: &t;Set Loopback (Xmit) */
DECL|macro|T3_UNLOOP
mdefine_line|#define&t;T3_UNLOOP&t;(1&lt;&lt;4)&t;/* Bit 4: &t;Unset Loopback (Xmit) */
DECL|macro|T3_MUX
mdefine_line|#define&t;T3_MUX&t;&t;(3&lt;&lt;2)&t;/* Bit 3..2:&t;Mux position */
DECL|macro|T3_VRAM
mdefine_line|#define&t;T3_VRAM&t;&t;(3&lt;&lt;0)&t;/* Bit 1..0:&t;Virtual RAM buffer Address */
multiline_comment|/* PCI card IDs */
multiline_comment|/*&n; * Note: The following 4 byte definitions shall not be used! Use OEM Concept!&n; */
DECL|macro|PCI_VEND_ID0
mdefine_line|#define&t;PCI_VEND_ID0&t;0x48&t;&t;/* PCI vendor ID (SysKonnect) */
DECL|macro|PCI_VEND_ID1
mdefine_line|#define&t;PCI_VEND_ID1&t;0x11&t;&t;/* PCI vendor ID (SysKonnect) */
multiline_comment|/*&t;&t; (High byte) */
DECL|macro|PCI_DEV_ID0
mdefine_line|#define&t;PCI_DEV_ID0&t;0x00&t;&t;/* PCI device ID */
DECL|macro|PCI_DEV_ID1
mdefine_line|#define&t;PCI_DEV_ID1&t;0x40&t;&t;/* PCI device ID (High byte) */
multiline_comment|/*#define PCI_CLASS&t;0x02*/
multiline_comment|/* PCI class code: network device */
DECL|macro|PCI_NW_CLASS
mdefine_line|#define PCI_NW_CLASS&t;0x02&t;&t;/* PCI class code: network device */
DECL|macro|PCI_SUB_CLASS
mdefine_line|#define PCI_SUB_CLASS&t;0x02&t;&t;/* PCI subclass ID: FDDI device */
DECL|macro|PCI_PROG_INTFC
mdefine_line|#define PCI_PROG_INTFC&t;0x00&t;&t;/* PCI programming Interface (=0) */
multiline_comment|/*&n; * address transmission from logical to physical offset address on board&n; */
DECL|macro|FMA
mdefine_line|#define&t;FMA(a)&t;(0x0400|((a)&lt;&lt;2))&t;/* FORMAC+ (r/w) (SN3) */
DECL|macro|P1
mdefine_line|#define&t;P1(a)&t;(0x0380|((a)&lt;&lt;2))&t;/* PLC1 (r/w) (DAS) */
DECL|macro|P2
mdefine_line|#define&t;P2(a)&t;(0x0600|((a)&lt;&lt;2))&t;/* PLC2 (r/w) (covered by the SN3) */
DECL|macro|PRA
mdefine_line|#define PRA(a)&t;(B2_MAC_0 + (a))&t;/* configuration PROM (MAC address) */
multiline_comment|/*&n; * FlashProm specification&n; */
DECL|macro|MAX_PAGES
mdefine_line|#define&t;MAX_PAGES&t;0x20000L&t;/* Every byte has a single page */
DECL|macro|MAX_FADDR
mdefine_line|#define&t;MAX_FADDR&t;1&t;&t;/* 1 byte per page */
multiline_comment|/*&n; * Receive / Transmit Buffer Control word&n; */
DECL|macro|BMU_OWN
mdefine_line|#define&t;BMU_OWN&t;&t;(1UL&lt;&lt;31)&t;/* OWN bit: 0 == host, 1 == adapter */
DECL|macro|BMU_STF
mdefine_line|#define&t;BMU_STF&t;&t;(1L&lt;&lt;30)&t;/* Start of Frame ?&t;&t;*/
DECL|macro|BMU_EOF
mdefine_line|#define&t;BMU_EOF&t;&t;(1L&lt;&lt;29)&t;/* End of Frame ?&t;&t;*/
DECL|macro|BMU_EN_IRQ_EOB
mdefine_line|#define&t;BMU_EN_IRQ_EOB&t;(1L&lt;&lt;28)&t;/* Enable &quot;End of Buffer&quot; IRQ&t;*/
DECL|macro|BMU_EN_IRQ_EOF
mdefine_line|#define&t;BMU_EN_IRQ_EOF&t;(1L&lt;&lt;27)&t;/* Enable &quot;End of Frame&quot; IRQ&t;*/
DECL|macro|BMU_DEV_0
mdefine_line|#define&t;BMU_DEV_0&t;(1L&lt;&lt;26)&t;/* RX: don&squot;t transfer to system mem */
DECL|macro|BMU_SMT_TX
mdefine_line|#define BMU_SMT_TX&t;(1L&lt;&lt;25)&t;/* TX: if set, buffer type SMT_MBuf */
DECL|macro|BMU_ST_BUF
mdefine_line|#define BMU_ST_BUF&t;(1L&lt;&lt;25)&t;/* RX: copy of start of frame */
DECL|macro|BMU_UNUSED
mdefine_line|#define BMU_UNUSED&t;(1L&lt;&lt;24)&t;/* Set if the Descr is curr unused */
DECL|macro|BMU_SW
mdefine_line|#define BMU_SW&t;&t;(3L&lt;&lt;24)&t;/* 2 Bits reserved for SW usage */
DECL|macro|BMU_CHECK
mdefine_line|#define&t;BMU_CHECK&t;0x00550000L&t;/* To identify the control word */
DECL|macro|BMU_BBC
mdefine_line|#define&t;BMU_BBC&t;&t;0x0000FFFFL&t;/* R/T Buffer Byte Count        */
multiline_comment|/*&n; * physical address offset + IO-Port base address&n; */
macro_line|#ifdef MEM_MAPPED_IO
DECL|macro|ADDR
mdefine_line|#define&t;ADDR(a)&t;&t;(char far *) smc-&gt;hw.iop+(a)
DECL|macro|ADDRS
mdefine_line|#define&t;ADDRS(smc,a)&t;(char far *) (smc)-&gt;hw.iop+(a)
macro_line|#else
DECL|macro|ADDR
mdefine_line|#define&t;ADDR(a)&t;(((a)&gt;&gt;7) ? (outp(smc-&gt;hw.iop+B0_RAP,(a)&gt;&gt;7), &bslash;&n;&t;(smc-&gt;hw.iop+(((a)&amp;0x7F)|((a)&gt;&gt;7 ? 0x80:0)))) : &bslash;&n;&t;(smc-&gt;hw.iop+(((a)&amp;0x7F)|((a)&gt;&gt;7 ? 0x80:0))))
DECL|macro|ADDRS
mdefine_line|#define&t;ADDRS(smc,a) (((a)&gt;&gt;7) ? (outp((smc)-&gt;hw.iop+B0_RAP,(a)&gt;&gt;7), &bslash;&n;&t;((smc)-&gt;hw.iop+(((a)&amp;0x7F)|((a)&gt;&gt;7 ? 0x80:0)))) : &bslash;&n;&t;((smc)-&gt;hw.iop+(((a)&amp;0x7F)|((a)&gt;&gt;7 ? 0x80:0))))
macro_line|#endif
multiline_comment|/*&n; * Define a macro to access the configuration space&n; */
DECL|macro|PCI_C
mdefine_line|#define PCI_C(a)&t;ADDR(B3_CFG_SPC + (a))&t;/* PCI Config Space */
DECL|macro|EXT_R
mdefine_line|#define EXT_R(a)&t;ADDR(B6_EXT_REG + (a))&t;/* External Registers */
multiline_comment|/*&n; * Define some values needed for the MAC address (PROM)&n; */
DECL|macro|SA_MAC
mdefine_line|#define&t;SA_MAC&t;&t;(0)&t;/* start addr. MAC_AD within the PROM */
DECL|macro|PRA_OFF
mdefine_line|#define&t;PRA_OFF&t;&t;(0)&t;/* offset correction when 4th byte reading */
DECL|macro|SKFDDI_PSZ
mdefine_line|#define&t;SKFDDI_PSZ&t;8&t;/* address PROM size */
DECL|macro|FM_A
mdefine_line|#define&t;FM_A(a)&t;ADDR(FMA(a))&t;/* FORMAC Plus physical addr */
DECL|macro|P1_A
mdefine_line|#define&t;P1_A(a)&t;ADDR(P1(a))&t;/* PLC1 (r/w) */
DECL|macro|P2_A
mdefine_line|#define&t;P2_A(a)&t;ADDR(P2(a))&t;/* PLC2 (r/w) (DAS) */
DECL|macro|PR_A
mdefine_line|#define PR_A(a)&t;ADDR(PRA(a))&t;/* config. PROM (MAC address) */
multiline_comment|/*&n; * Macro to read the PROM&n; */
DECL|macro|READ_PROM
mdefine_line|#define&t;READ_PROM(a)&t;((u_char)inp(a))
DECL|macro|GET_PAGE
mdefine_line|#define&t;GET_PAGE(bank)&t;outpd(ADDR(B2_FAR),bank)
DECL|macro|VPP_ON
mdefine_line|#define&t;VPP_ON()
DECL|macro|VPP_OFF
mdefine_line|#define&t;VPP_OFF()
multiline_comment|/*&n; * Note: Values of the Interrupt Source Register are defined above&n; */
DECL|macro|ISR_A
mdefine_line|#define ISR_A&t;&t;ADDR(B0_ISRC)
DECL|macro|GET_ISR
mdefine_line|#define&t;GET_ISR()&t;&t;inpd(ISR_A)
DECL|macro|GET_ISR_SMP
mdefine_line|#define GET_ISR_SMP(iop)&t;inpd((iop)+B0_ISRC)
DECL|macro|CHECK_ISR
mdefine_line|#define&t;CHECK_ISR()&t;&t;(inpd(ISR_A) &amp; inpd(ADDR(B0_IMSK)))
DECL|macro|CHECK_ISR_SMP
mdefine_line|#define CHECK_ISR_SMP(iop)&t;(inpd((iop)+B0_ISRC) &amp; inpd((iop)+B0_IMSK))
DECL|macro|BUS_CHECK
mdefine_line|#define&t;BUS_CHECK()
multiline_comment|/*&n; * CLI_FBI:&t;Disable Board Interrupts&n; * STI_FBI:&t;Enable Board Interrupts&n; */
macro_line|#ifndef UNIX
DECL|macro|CLI_FBI
mdefine_line|#define&t;CLI_FBI()&t;outpd(ADDR(B0_IMSK),0)
macro_line|#else
DECL|macro|CLI_FBI
mdefine_line|#define&t;CLI_FBI(smc)&t;outpd(ADDRS((smc),B0_IMSK),0)
macro_line|#endif
macro_line|#ifndef UNIX
DECL|macro|STI_FBI
mdefine_line|#define&t;STI_FBI()&t;outpd(ADDR(B0_IMSK),smc-&gt;hw.is_imask)
macro_line|#else
DECL|macro|STI_FBI
mdefine_line|#define&t;STI_FBI(smc)&t;outpd(ADDRS((smc),B0_IMSK),(smc)-&gt;hw.is_imask)
macro_line|#endif
DECL|macro|CLI_FBI_SMP
mdefine_line|#define CLI_FBI_SMP(iop)&t;outpd((iop)+B0_IMSK,0)
DECL|macro|STI_FBI_SMP
mdefine_line|#define&t;STI_FBI_SMP(smc,iop)&t;outpd((iop)+B0_IMSK,(smc)-&gt;hw.is_imask)
macro_line|#endif&t;/* PCI */
multiline_comment|/*--------------------------------------------------------------------------*/
multiline_comment|/*&n; * 12 bit transfer (dword) counter:&n; *&t;(ISA:&t;2*trc = number of byte)&n; *&t;(EISA:&t;4*trc = number of byte)&n; *&t;(MCA:&t;4*trc = number of byte)&n; */
DECL|macro|MAX_TRANS
mdefine_line|#define&t;MAX_TRANS&t;(0x0fff)
multiline_comment|/*&n; * PC PIC&n; */
DECL|macro|MST_8259
mdefine_line|#define&t;MST_8259 (0x20)
DECL|macro|SLV_8259
mdefine_line|#define&t;SLV_8259 (0xA0)
DECL|macro|TPS
mdefine_line|#define TPS&t;&t;(18)&t;&t;/* ticks per second */
multiline_comment|/*&n; * error timer defs&n; */
DECL|macro|TN
mdefine_line|#define&t;TN&t;&t;(4)&t;/* number of supported timer = TN+1 */
DECL|macro|SNPPND_TIME
mdefine_line|#define&t;SNPPND_TIME&t;(5)&t;/* buffer memory access over mem. data reg. */
DECL|macro|MAC_AD
mdefine_line|#define&t;MAC_AD&t;0x405a0000
DECL|macro|MODR1
mdefine_line|#define MODR1&t;FM_A(FM_MDREG1)&t;/* mode register 1 */
DECL|macro|MODR2
mdefine_line|#define MODR2&t;FM_A(FM_MDREG2)&t;/* mode register 2 */
DECL|macro|CMDR1
mdefine_line|#define CMDR1&t;FM_A(FM_CMDREG1)&t;/* command register 1 */
DECL|macro|CMDR2
mdefine_line|#define CMDR2&t;FM_A(FM_CMDREG2)&t;/* command register 2 */
multiline_comment|/*&n; * function defines&n; */
DECL|macro|CLEAR
mdefine_line|#define&t;CLEAR(io,mask)&t;&t;outpw((io),inpw(io)&amp;(~(mask)))
DECL|macro|SET
mdefine_line|#define&t;SET(io,mask)&t;&t;outpw((io),inpw(io)|(mask))
DECL|macro|GET
mdefine_line|#define&t;GET(io,mask)&t;&t;(inpw(io)&amp;(mask))
DECL|macro|SETMASK
mdefine_line|#define&t;SETMASK(io,val,mask)&t;outpw((io),(inpw(io) &amp; ~(mask)) | (val))
multiline_comment|/*&n; * PHY Port A (PA) = PLC 1&n; * With SuperNet 3 PHY-A and PHY S are identical.&n; */
DECL|macro|PLC
mdefine_line|#define&t;PLC(np,reg)&t;(((np) == PA) ? P2_A(reg) : P1_A(reg))
multiline_comment|/*&n; * set memory address register for write and read&n; */
DECL|macro|MARW
mdefine_line|#define&t;MARW(ma)&t;outpw(FM_A(FM_MARW),(unsigned int)(ma))
DECL|macro|MARR
mdefine_line|#define&t;MARR(ma)&t;outpw(FM_A(FM_MARR),(unsigned int)(ma))
multiline_comment|/*&n; * read/write from/to memory data register&n; */
multiline_comment|/* write double word */
DECL|macro|MDRW
mdefine_line|#define&t;MDRW(dd)&t;outpw(FM_A(FM_MDRU),(unsigned int)((dd)&gt;&gt;16)) ;&bslash;&n;&t;&t;&t;outpw(FM_A(FM_MDRL),(unsigned int)(dd))
macro_line|#ifndef WINNT
multiline_comment|/* read double word */
DECL|macro|MDRR
mdefine_line|#define&t;MDRR()&t;&t;(((long)inpw(FM_A(FM_MDRU))&lt;&lt;16) + inpw(FM_A(FM_MDRL)))
multiline_comment|/* read FORMAC+ 32-bit status register */
DECL|macro|GET_ST1
mdefine_line|#define&t;GET_ST1()&t;(((long)inpw(FM_A(FM_ST1U))&lt;&lt;16) + inpw(FM_A(FM_ST1L)))
DECL|macro|GET_ST2
mdefine_line|#define&t;GET_ST2()&t;(((long)inpw(FM_A(FM_ST2U))&lt;&lt;16) + inpw(FM_A(FM_ST2L)))
macro_line|#ifdef&t;SUPERNET_3
DECL|macro|GET_ST3
mdefine_line|#define&t;GET_ST3()&t;(((long)inpw(FM_A(FM_ST3U))&lt;&lt;16) + inpw(FM_A(FM_ST3L)))
macro_line|#endif
macro_line|#else
multiline_comment|/* read double word */
DECL|macro|MDRR
mdefine_line|#define MDRR()&t;&t;inp2w((FM_A(FM_MDRU)),(FM_A(FM_MDRL)))
multiline_comment|/* read FORMAC+ 32-bit status register */
DECL|macro|GET_ST1
mdefine_line|#define GET_ST1()&t;inp2w((FM_A(FM_ST1U)),(FM_A(FM_ST1L)))
DECL|macro|GET_ST2
mdefine_line|#define GET_ST2()&t;inp2w((FM_A(FM_ST2U)),(FM_A(FM_ST2L)))
macro_line|#ifdef&t;SUPERNET_3
DECL|macro|GET_ST3
mdefine_line|#define GET_ST3()&t;inp2w((FM_A(FM_ST3U)),(FM_A(FM_ST3L)))
macro_line|#endif
macro_line|#endif
multiline_comment|/* Special timer macro for 82c54 */
multiline_comment|/* timer access over data bus bit 8..15 */
DECL|macro|OUT_82c54_TIMER
mdefine_line|#define&t;OUT_82c54_TIMER(port,val)&t;outpw(TI_A(port),(val)&lt;&lt;8)
DECL|macro|IN_82c54_TIMER
mdefine_line|#define&t;IN_82c54_TIMER(port)&t;&t;((inpw(TI_A(port))&gt;&gt;8) &amp; 0xff)
macro_line|#ifdef&t;DEBUG
DECL|macro|DB_MAC
mdefine_line|#define&t;DB_MAC(mac,st) {if (debug_mac &amp; 0x1)&bslash;&n;&t;&t;&t;&t;printf(&quot;M&quot;) ;&bslash;&n;&t;&t;&t;if (debug_mac &amp; 0x2)&bslash;&n;&t;&t;&t;&t;printf(&quot;&bslash;tMAC %d status 0x%08lx&bslash;n&quot;,mac,st) ;&bslash;&n;&t;&t;&t;if (debug_mac &amp; 0x4)&bslash;&n;&t;&t;&t;&t;dp_mac(mac,st) ;&bslash;&n;}
DECL|macro|DB_PLC
mdefine_line|#define&t;DB_PLC(p,iev) {&t;if (debug_plc &amp; 0x1)&bslash;&n;&t;&t;&t;&t;printf(&quot;P&quot;) ;&bslash;&n;&t;&t;&t;if (debug_plc &amp; 0x2)&bslash;&n;&t;&t;&t;&t;printf(&quot;&bslash;tPLC %s Int 0x%04x&bslash;n&quot;, &bslash;&n;&t;&t;&t;&t;&t;(p == PA) ? &quot;A&quot; : &quot;B&quot;, iev) ;&bslash;&n;&t;&t;&t;if (debug_plc &amp; 0x4)&bslash;&n;&t;&t;&t;&t;dp_plc(p,iev) ;&bslash;&n;}
DECL|macro|DB_TIMER
mdefine_line|#define&t;DB_TIMER() {&t;if (debug_timer &amp; 0x1)&bslash;&n;&t;&t;&t;&t;printf(&quot;T&quot;) ;&bslash;&n;&t;&t;&t;if (debug_timer &amp; 0x2)&bslash;&n;&t;&t;&t;&t;printf(&quot;&bslash;tTimer ISR&bslash;n&quot;) ;&bslash;&n;}
macro_line|#else&t;/* no DEBUG */
DECL|macro|DB_MAC
mdefine_line|#define&t;DB_MAC(mac,st)
DECL|macro|DB_PLC
mdefine_line|#define&t;DB_PLC(p,iev)
DECL|macro|DB_TIMER
mdefine_line|#define&t;DB_TIMER()
macro_line|#endif&t;/* no DEBUG */
DECL|macro|INC_PTR
mdefine_line|#define&t;INC_PTR(sp,cp,ep)&t;if (++cp == ep) cp = sp
multiline_comment|/*&n; * timer defs&n; */
DECL|macro|COUNT
mdefine_line|#define&t;COUNT(t)&t;((t)&lt;&lt;6)&t;/* counter */
DECL|macro|RW_OP
mdefine_line|#define&t;RW_OP(o)&t;((o)&lt;&lt;4)&t;/* read/write operation */
DECL|macro|TMODE
mdefine_line|#define&t;TMODE(m)&t;((m)&lt;&lt;1)&t;/* timer mode */
macro_line|#endif
eof
