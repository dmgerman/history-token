multiline_comment|/***********************************&n; * $Id: m68360_quicc.h,v 1.1 2002/03/02 15:01:07 gerg Exp $&n; ***********************************&n; *&n; ***************************************&n; * Definitions of QUICC memory structures&n; ***************************************&n; */
macro_line|#ifndef __M68360_QUICC_H
DECL|macro|__M68360_QUICC_H
mdefine_line|#define __M68360_QUICC_H
multiline_comment|/*&n; * include registers and&n; * parameter ram definitions files&n; */
macro_line|#include &lt;asm/m68360_regs.h&gt;
macro_line|#include &lt;asm/m68360_pram.h&gt;
multiline_comment|/* Buffer Descriptors */
DECL|struct|quicc_bd
r_typedef
r_struct
id|quicc_bd
(brace
DECL|member|status
r_volatile
r_int
r_int
id|status
suffix:semicolon
DECL|member|length
r_volatile
r_int
r_int
id|length
suffix:semicolon
DECL|member|buf
r_volatile
r_int
r_char
op_star
id|buf
suffix:semicolon
multiline_comment|/* WARNING: This is only true if *char is 32 bits */
DECL|typedef|QUICC_BD
)brace
id|QUICC_BD
suffix:semicolon
macro_line|#ifdef MOTOROLA_ORIGINAL
DECL|struct|user_data
r_struct
id|user_data
(brace
multiline_comment|/* BASE + 0x000: user data memory */
DECL|member|udata_bd_ucode
r_volatile
r_int
r_char
id|udata_bd_ucode
(braket
l_int|0x400
)braket
suffix:semicolon
multiline_comment|/*user data bd&squot;s Ucode*/
DECL|member|udata_bd
r_volatile
r_int
r_char
id|udata_bd
(braket
l_int|0x200
)braket
suffix:semicolon
multiline_comment|/*user data Ucode     */
DECL|member|ucode_ext
r_volatile
r_int
r_char
id|ucode_ext
(braket
l_int|0x100
)braket
suffix:semicolon
multiline_comment|/*Ucode Extention ram */
DECL|member|RESERVED1
r_volatile
r_int
r_char
id|RESERVED1
(braket
l_int|0x500
)braket
suffix:semicolon
multiline_comment|/* Reserved area      */
)brace
suffix:semicolon
macro_line|#else
DECL|struct|user_data
r_struct
id|user_data
(brace
multiline_comment|/* BASE + 0x000: user data memory */
DECL|member|udata_bd_ucode
r_volatile
r_int
r_char
id|udata_bd_ucode
(braket
l_int|0x400
)braket
suffix:semicolon
multiline_comment|/* user data, bds, Ucode*/
DECL|member|udata_bd1
r_volatile
r_int
r_char
id|udata_bd1
(braket
l_int|0x200
)braket
suffix:semicolon
multiline_comment|/* user, bds */
DECL|member|ucode_bd_scratch
r_volatile
r_int
r_char
id|ucode_bd_scratch
(braket
l_int|0x100
)braket
suffix:semicolon
multiline_comment|/* user, bds, ucode scratch */
DECL|member|udata_bd2
r_volatile
r_int
r_char
id|udata_bd2
(braket
l_int|0x100
)braket
suffix:semicolon
multiline_comment|/* user, bds */
DECL|member|RESERVED1
r_volatile
r_int
r_char
id|RESERVED1
(braket
l_int|0x400
)braket
suffix:semicolon
multiline_comment|/* Reserved area      */
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * internal ram&n; */
DECL|struct|quicc
r_typedef
r_struct
id|quicc
(brace
r_union
(brace
DECL|member|ch_pram_tbl
r_struct
id|quicc32_pram
id|ch_pram_tbl
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* 32*64(bytes) per channel */
DECL|member|u
r_struct
id|user_data
id|u
suffix:semicolon
DECL|member|ch_or_u
)brace
id|ch_or_u
suffix:semicolon
multiline_comment|/* multipul or user space */
multiline_comment|/* BASE + 0xc00: PARAMETER RAM */
r_union
(brace
DECL|struct|scc_pram
r_struct
id|scc_pram
(brace
r_union
(brace
DECL|member|h
r_struct
id|hdlc_pram
id|h
suffix:semicolon
DECL|member|u
r_struct
id|uart_pram
id|u
suffix:semicolon
DECL|member|b
r_struct
id|bisync_pram
id|b
suffix:semicolon
DECL|member|t
r_struct
id|transparent_pram
id|t
suffix:semicolon
DECL|member|RESERVED66
r_int
r_char
id|RESERVED66
(braket
l_int|0x70
)braket
suffix:semicolon
DECL|member|pscc
)brace
id|pscc
suffix:semicolon
multiline_comment|/* scc parameter area (protocol dependent) */
r_union
(brace
r_struct
(brace
DECL|member|RESERVED70
r_int
r_char
id|RESERVED70
(braket
l_int|0x10
)braket
suffix:semicolon
DECL|member|spi
r_struct
id|spi_pram
id|spi
suffix:semicolon
DECL|member|RESERVED72
r_int
r_char
id|RESERVED72
(braket
l_int|0x8
)braket
suffix:semicolon
DECL|member|timer
r_struct
id|timer_pram
id|timer
suffix:semicolon
DECL|member|timer_spi
)brace
id|timer_spi
suffix:semicolon
r_struct
(brace
DECL|member|idma
r_struct
id|idma_pram
id|idma
suffix:semicolon
DECL|member|RESERVED67
r_int
r_char
id|RESERVED67
(braket
l_int|0x4
)braket
suffix:semicolon
r_union
(brace
DECL|member|u
r_struct
id|smc_uart_pram
id|u
suffix:semicolon
DECL|member|t
r_struct
id|smc_trnsp_pram
id|t
suffix:semicolon
DECL|member|psmc
)brace
id|psmc
suffix:semicolon
DECL|member|idma_smc
)brace
id|idma_smc
suffix:semicolon
DECL|member|pothers
)brace
id|pothers
suffix:semicolon
DECL|member|scc
)brace
id|scc
suffix:semicolon
DECL|member|enet_scc
r_struct
id|ethernet_pram
id|enet_scc
suffix:semicolon
DECL|member|m
r_struct
id|global_multi_pram
id|m
suffix:semicolon
DECL|member|pr
r_int
r_char
id|pr
(braket
l_int|0x100
)braket
suffix:semicolon
DECL|member|pram
)brace
id|pram
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* reserved */
multiline_comment|/* BASE + 0x1000: INTERNAL REGISTERS */
multiline_comment|/* SIM */
DECL|member|sim_mcr
r_volatile
r_int
r_int
id|sim_mcr
suffix:semicolon
multiline_comment|/* module configuration reg */
DECL|member|sim_simtr
r_volatile
r_int
r_int
id|sim_simtr
suffix:semicolon
multiline_comment|/* module test register     */
DECL|member|RESERVED2
r_volatile
r_int
r_char
id|RESERVED2
(braket
l_int|0x2
)braket
suffix:semicolon
multiline_comment|/* Reserved area            */
DECL|member|sim_avr
r_volatile
r_int
r_char
id|sim_avr
suffix:semicolon
multiline_comment|/* auto vector reg          */
DECL|member|sim_rsr
r_volatile
r_int
r_char
id|sim_rsr
suffix:semicolon
multiline_comment|/* reset status reg         */
DECL|member|RESERVED3
r_volatile
r_int
r_char
id|RESERVED3
(braket
l_int|0x2
)braket
suffix:semicolon
multiline_comment|/* Reserved area            */
DECL|member|sim_clkocr
r_volatile
r_int
r_char
id|sim_clkocr
suffix:semicolon
multiline_comment|/* CLCO control register    */
DECL|member|RESERVED62
r_volatile
r_int
r_char
id|RESERVED62
(braket
l_int|0x3
)braket
suffix:semicolon
multiline_comment|/* Reserved area    */
DECL|member|sim_pllcr
r_volatile
r_int
r_int
id|sim_pllcr
suffix:semicolon
multiline_comment|/* PLL control register     */
DECL|member|RESERVED63
r_volatile
r_int
r_char
id|RESERVED63
(braket
l_int|0x2
)braket
suffix:semicolon
multiline_comment|/* Reserved area    */
DECL|member|sim_cdvcr
r_volatile
r_int
r_int
id|sim_cdvcr
suffix:semicolon
multiline_comment|/* Clock devider control register */
DECL|member|sim_pepar
r_volatile
r_int
r_int
id|sim_pepar
suffix:semicolon
multiline_comment|/* Port E pin assignment register */
DECL|member|RESERVED64
r_volatile
r_int
r_char
id|RESERVED64
(braket
l_int|0xa
)braket
suffix:semicolon
multiline_comment|/* Reserved area    */
DECL|member|sim_sypcr
r_volatile
r_int
r_char
id|sim_sypcr
suffix:semicolon
multiline_comment|/* system protection control*/
DECL|member|sim_swiv
r_volatile
r_int
r_char
id|sim_swiv
suffix:semicolon
multiline_comment|/* software interrupt vector*/
DECL|member|RESERVED6
r_volatile
r_int
r_char
id|RESERVED6
(braket
l_int|0x2
)braket
suffix:semicolon
multiline_comment|/* Reserved area            */
DECL|member|sim_picr
r_volatile
r_int
r_int
id|sim_picr
suffix:semicolon
multiline_comment|/* periodic interrupt control reg */
DECL|member|RESERVED7
r_volatile
r_int
r_char
id|RESERVED7
(braket
l_int|0x2
)braket
suffix:semicolon
multiline_comment|/* Reserved area            */
DECL|member|sim_pitr
r_volatile
r_int
r_int
id|sim_pitr
suffix:semicolon
multiline_comment|/* periodic interrupt timing reg */
DECL|member|RESERVED8
r_volatile
r_int
r_char
id|RESERVED8
(braket
l_int|0x3
)braket
suffix:semicolon
multiline_comment|/* Reserved area            */
DECL|member|sim_swsr
r_volatile
r_int
r_char
id|sim_swsr
suffix:semicolon
multiline_comment|/* software service         */
DECL|member|sim_bkar
r_volatile
r_int
r_int
id|sim_bkar
suffix:semicolon
multiline_comment|/* breakpoint address register*/
DECL|member|sim_bkcr
r_volatile
r_int
r_int
id|sim_bkcr
suffix:semicolon
multiline_comment|/* breakpoint control register*/
DECL|member|RESERVED10
r_volatile
r_int
r_char
id|RESERVED10
(braket
l_int|0x8
)braket
suffix:semicolon
multiline_comment|/* Reserved area    */
multiline_comment|/* MEMC */
DECL|member|memc_gmr
r_volatile
r_int
r_int
id|memc_gmr
suffix:semicolon
multiline_comment|/* Global memory register   */
DECL|member|memc_mstat
r_volatile
r_int
r_int
id|memc_mstat
suffix:semicolon
multiline_comment|/* MEMC status register     */
DECL|member|RESERVED11
r_volatile
r_int
r_char
id|RESERVED11
(braket
l_int|0xa
)braket
suffix:semicolon
multiline_comment|/* Reserved area    */
DECL|member|memc_br0
r_volatile
r_int
r_int
id|memc_br0
suffix:semicolon
multiline_comment|/* base register 0          */
DECL|member|memc_or0
r_volatile
r_int
r_int
id|memc_or0
suffix:semicolon
multiline_comment|/* option register 0        */
DECL|member|RESERVED12
r_volatile
r_int
r_char
id|RESERVED12
(braket
l_int|0x8
)braket
suffix:semicolon
multiline_comment|/* Reserved area    */
DECL|member|memc_br1
r_volatile
r_int
r_int
id|memc_br1
suffix:semicolon
multiline_comment|/* base register 1          */
DECL|member|memc_or1
r_volatile
r_int
r_int
id|memc_or1
suffix:semicolon
multiline_comment|/* option register 1        */
DECL|member|RESERVED13
r_volatile
r_int
r_char
id|RESERVED13
(braket
l_int|0x8
)braket
suffix:semicolon
multiline_comment|/* Reserved area    */
DECL|member|memc_br2
r_volatile
r_int
r_int
id|memc_br2
suffix:semicolon
multiline_comment|/* base register 2          */
DECL|member|memc_or2
r_volatile
r_int
r_int
id|memc_or2
suffix:semicolon
multiline_comment|/* option register 2        */
DECL|member|RESERVED14
r_volatile
r_int
r_char
id|RESERVED14
(braket
l_int|0x8
)braket
suffix:semicolon
multiline_comment|/* Reserved area    */
DECL|member|memc_br3
r_volatile
r_int
r_int
id|memc_br3
suffix:semicolon
multiline_comment|/* base register 3          */
DECL|member|memc_or3
r_volatile
r_int
r_int
id|memc_or3
suffix:semicolon
multiline_comment|/* option register 3        */
DECL|member|RESERVED15
r_volatile
r_int
r_char
id|RESERVED15
(braket
l_int|0x8
)braket
suffix:semicolon
multiline_comment|/* Reserved area    */
DECL|member|memc_br4
r_volatile
r_int
r_int
id|memc_br4
suffix:semicolon
multiline_comment|/* base register 3          */
DECL|member|memc_or4
r_volatile
r_int
r_int
id|memc_or4
suffix:semicolon
multiline_comment|/* option register 3        */
DECL|member|RESERVED16
r_volatile
r_int
r_char
id|RESERVED16
(braket
l_int|0x8
)braket
suffix:semicolon
multiline_comment|/* Reserved area    */
DECL|member|memc_br5
r_volatile
r_int
r_int
id|memc_br5
suffix:semicolon
multiline_comment|/* base register 3          */
DECL|member|memc_or5
r_volatile
r_int
r_int
id|memc_or5
suffix:semicolon
multiline_comment|/* option register 3        */
DECL|member|RESERVED17
r_volatile
r_int
r_char
id|RESERVED17
(braket
l_int|0x8
)braket
suffix:semicolon
multiline_comment|/* Reserved area    */
DECL|member|memc_br6
r_volatile
r_int
r_int
id|memc_br6
suffix:semicolon
multiline_comment|/* base register 3          */
DECL|member|memc_or6
r_volatile
r_int
r_int
id|memc_or6
suffix:semicolon
multiline_comment|/* option register 3        */
DECL|member|RESERVED18
r_volatile
r_int
r_char
id|RESERVED18
(braket
l_int|0x8
)braket
suffix:semicolon
multiline_comment|/* Reserved area    */
DECL|member|memc_br7
r_volatile
r_int
r_int
id|memc_br7
suffix:semicolon
multiline_comment|/* base register 3          */
DECL|member|memc_or7
r_volatile
r_int
r_int
id|memc_or7
suffix:semicolon
multiline_comment|/* option register 3        */
DECL|member|RESERVED9
r_volatile
r_int
r_char
id|RESERVED9
(braket
l_int|0x28
)braket
suffix:semicolon
multiline_comment|/* Reserved area    */
multiline_comment|/* TEST */
DECL|member|test_tstmra
r_volatile
r_int
r_int
id|test_tstmra
suffix:semicolon
multiline_comment|/* master shift a           */
DECL|member|test_tstmrb
r_volatile
r_int
r_int
id|test_tstmrb
suffix:semicolon
multiline_comment|/* master shift b           */
DECL|member|test_tstsc
r_volatile
r_int
r_int
id|test_tstsc
suffix:semicolon
multiline_comment|/* shift count              */
DECL|member|test_tstrc
r_volatile
r_int
r_int
id|test_tstrc
suffix:semicolon
multiline_comment|/* repetition counter       */
DECL|member|test_creg
r_volatile
r_int
r_int
id|test_creg
suffix:semicolon
multiline_comment|/* control                  */
DECL|member|test_dreg
r_volatile
r_int
r_int
id|test_dreg
suffix:semicolon
multiline_comment|/* destributed register     */
DECL|member|RESERVED58
r_volatile
r_int
r_char
id|RESERVED58
(braket
l_int|0x404
)braket
suffix:semicolon
multiline_comment|/* Reserved area    */
multiline_comment|/* IDMA1 */
DECL|member|idma_iccr
r_volatile
r_int
r_int
id|idma_iccr
suffix:semicolon
multiline_comment|/* channel configuration reg*/
DECL|member|RESERVED19
r_volatile
r_int
r_char
id|RESERVED19
(braket
l_int|0x2
)braket
suffix:semicolon
multiline_comment|/* Reserved area    */
DECL|member|idma1_cmr
r_volatile
r_int
r_int
id|idma1_cmr
suffix:semicolon
multiline_comment|/* dma mode reg             */
DECL|member|RESERVED68
r_volatile
r_int
r_char
id|RESERVED68
(braket
l_int|0x2
)braket
suffix:semicolon
multiline_comment|/* Reserved area    */
DECL|member|idma1_sapr
r_volatile
r_int
r_int
id|idma1_sapr
suffix:semicolon
multiline_comment|/* dma source addr ptr      */
DECL|member|idma1_dapr
r_volatile
r_int
r_int
id|idma1_dapr
suffix:semicolon
multiline_comment|/* dma destination addr ptr */
DECL|member|idma1_bcr
r_volatile
r_int
r_int
id|idma1_bcr
suffix:semicolon
multiline_comment|/* dma byte count reg       */
DECL|member|idma1_fcr
r_volatile
r_int
r_char
id|idma1_fcr
suffix:semicolon
multiline_comment|/* function code reg        */
DECL|member|RESERVED20
r_volatile
r_int
r_char
id|RESERVED20
suffix:semicolon
multiline_comment|/* Reserved area            */
DECL|member|idma1_cmar
r_volatile
r_int
r_char
id|idma1_cmar
suffix:semicolon
multiline_comment|/* channel mask reg         */
DECL|member|RESERVED21
r_volatile
r_int
r_char
id|RESERVED21
suffix:semicolon
multiline_comment|/* Reserved area            */
DECL|member|idma1_csr
r_volatile
r_int
r_char
id|idma1_csr
suffix:semicolon
multiline_comment|/* channel status reg       */
DECL|member|RESERVED22
r_volatile
r_int
r_char
id|RESERVED22
(braket
l_int|0x3
)braket
suffix:semicolon
multiline_comment|/* Reserved area    */
multiline_comment|/* SDMA */
DECL|member|sdma_sdsr
r_volatile
r_int
r_char
id|sdma_sdsr
suffix:semicolon
multiline_comment|/* status reg               */
DECL|member|RESERVED23
r_volatile
r_int
r_char
id|RESERVED23
suffix:semicolon
multiline_comment|/* Reserved area            */
DECL|member|sdma_sdcr
r_volatile
r_int
r_int
id|sdma_sdcr
suffix:semicolon
multiline_comment|/* configuration reg        */
DECL|member|sdma_sdar
r_volatile
r_int
r_int
id|sdma_sdar
suffix:semicolon
multiline_comment|/* address reg              */
multiline_comment|/* IDMA2 */
DECL|member|RESERVED69
r_volatile
r_int
r_char
id|RESERVED69
(braket
l_int|0x2
)braket
suffix:semicolon
multiline_comment|/* Reserved area    */
DECL|member|idma2_cmr
r_volatile
r_int
r_int
id|idma2_cmr
suffix:semicolon
multiline_comment|/* dma mode reg             */
DECL|member|idma2_sapr
r_volatile
r_int
r_int
id|idma2_sapr
suffix:semicolon
multiline_comment|/* dma source addr ptr      */
DECL|member|idma2_dapr
r_volatile
r_int
r_int
id|idma2_dapr
suffix:semicolon
multiline_comment|/* dma destination addr ptr */
DECL|member|idma2_bcr
r_volatile
r_int
r_int
id|idma2_bcr
suffix:semicolon
multiline_comment|/* dma byte count reg       */
DECL|member|idma2_fcr
r_volatile
r_int
r_char
id|idma2_fcr
suffix:semicolon
multiline_comment|/* function code reg        */
DECL|member|RESERVED24
r_volatile
r_int
r_char
id|RESERVED24
suffix:semicolon
multiline_comment|/* Reserved area            */
DECL|member|idma2_cmar
r_volatile
r_int
r_char
id|idma2_cmar
suffix:semicolon
multiline_comment|/* channel mask reg         */
DECL|member|RESERVED25
r_volatile
r_int
r_char
id|RESERVED25
suffix:semicolon
multiline_comment|/* Reserved area            */
DECL|member|idma2_csr
r_volatile
r_int
r_char
id|idma2_csr
suffix:semicolon
multiline_comment|/* channel status reg       */
DECL|member|RESERVED26
r_volatile
r_int
r_char
id|RESERVED26
(braket
l_int|0x7
)braket
suffix:semicolon
multiline_comment|/* Reserved area    */
multiline_comment|/* Interrupt Controller */
DECL|member|intr_cicr
r_volatile
r_int
r_int
id|intr_cicr
suffix:semicolon
multiline_comment|/* CP interrupt configuration reg*/
DECL|member|intr_cipr
r_volatile
r_int
r_int
id|intr_cipr
suffix:semicolon
multiline_comment|/* CP interrupt pending reg */
DECL|member|intr_cimr
r_volatile
r_int
r_int
id|intr_cimr
suffix:semicolon
multiline_comment|/* CP interrupt mask reg    */
DECL|member|intr_cisr
r_volatile
r_int
r_int
id|intr_cisr
suffix:semicolon
multiline_comment|/* CP interrupt in service reg*/
multiline_comment|/* Parallel I/O */
DECL|member|pio_padir
r_volatile
r_int
r_int
id|pio_padir
suffix:semicolon
multiline_comment|/* port A data direction reg */
DECL|member|pio_papar
r_volatile
r_int
r_int
id|pio_papar
suffix:semicolon
multiline_comment|/* port A pin assignment reg */
DECL|member|pio_paodr
r_volatile
r_int
r_int
id|pio_paodr
suffix:semicolon
multiline_comment|/* port A open drain reg    */
DECL|member|pio_padat
r_volatile
r_int
r_int
id|pio_padat
suffix:semicolon
multiline_comment|/* port A data register     */
DECL|member|RESERVED28
r_volatile
r_int
r_char
id|RESERVED28
(braket
l_int|0x8
)braket
suffix:semicolon
multiline_comment|/* Reserved area    */
DECL|member|pio_pcdir
r_volatile
r_int
r_int
id|pio_pcdir
suffix:semicolon
multiline_comment|/* port C data direction reg*/
DECL|member|pio_pcpar
r_volatile
r_int
r_int
id|pio_pcpar
suffix:semicolon
multiline_comment|/* port C pin assignment reg*/
DECL|member|pio_pcso
r_volatile
r_int
r_int
id|pio_pcso
suffix:semicolon
multiline_comment|/* port C special options   */
DECL|member|pio_pcdat
r_volatile
r_int
r_int
id|pio_pcdat
suffix:semicolon
multiline_comment|/* port C data register     */
DECL|member|pio_pcint
r_volatile
r_int
r_int
id|pio_pcint
suffix:semicolon
multiline_comment|/* port C interrupt cntrl reg */
DECL|member|RESERVED29
r_volatile
r_int
r_char
id|RESERVED29
(braket
l_int|0x16
)braket
suffix:semicolon
multiline_comment|/* Reserved area    */
multiline_comment|/* Timer */
DECL|member|timer_tgcr
r_volatile
r_int
r_int
id|timer_tgcr
suffix:semicolon
multiline_comment|/* timer global configuration reg */
DECL|member|RESERVED30
r_volatile
r_int
r_char
id|RESERVED30
(braket
l_int|0xe
)braket
suffix:semicolon
multiline_comment|/* Reserved area    */
DECL|member|timer_tmr1
r_volatile
r_int
r_int
id|timer_tmr1
suffix:semicolon
multiline_comment|/* timer 1 mode reg         */
DECL|member|timer_tmr2
r_volatile
r_int
r_int
id|timer_tmr2
suffix:semicolon
multiline_comment|/* timer 2 mode reg         */
DECL|member|timer_trr1
r_volatile
r_int
r_int
id|timer_trr1
suffix:semicolon
multiline_comment|/* timer 1 referance reg    */
DECL|member|timer_trr2
r_volatile
r_int
r_int
id|timer_trr2
suffix:semicolon
multiline_comment|/* timer 2 referance reg    */
DECL|member|timer_tcr1
r_volatile
r_int
r_int
id|timer_tcr1
suffix:semicolon
multiline_comment|/* timer 1 capture reg      */
DECL|member|timer_tcr2
r_volatile
r_int
r_int
id|timer_tcr2
suffix:semicolon
multiline_comment|/* timer 2 capture reg      */
DECL|member|timer_tcn1
r_volatile
r_int
r_int
id|timer_tcn1
suffix:semicolon
multiline_comment|/* timer 1 counter reg      */
DECL|member|timer_tcn2
r_volatile
r_int
r_int
id|timer_tcn2
suffix:semicolon
multiline_comment|/* timer 2 counter reg      */
DECL|member|timer_tmr3
r_volatile
r_int
r_int
id|timer_tmr3
suffix:semicolon
multiline_comment|/* timer 3 mode reg         */
DECL|member|timer_tmr4
r_volatile
r_int
r_int
id|timer_tmr4
suffix:semicolon
multiline_comment|/* timer 4 mode reg         */
DECL|member|timer_trr3
r_volatile
r_int
r_int
id|timer_trr3
suffix:semicolon
multiline_comment|/* timer 3 referance reg    */
DECL|member|timer_trr4
r_volatile
r_int
r_int
id|timer_trr4
suffix:semicolon
multiline_comment|/* timer 4 referance reg    */
DECL|member|timer_tcr3
r_volatile
r_int
r_int
id|timer_tcr3
suffix:semicolon
multiline_comment|/* timer 3 capture reg      */
DECL|member|timer_tcr4
r_volatile
r_int
r_int
id|timer_tcr4
suffix:semicolon
multiline_comment|/* timer 4 capture reg      */
DECL|member|timer_tcn3
r_volatile
r_int
r_int
id|timer_tcn3
suffix:semicolon
multiline_comment|/* timer 3 counter reg      */
DECL|member|timer_tcn4
r_volatile
r_int
r_int
id|timer_tcn4
suffix:semicolon
multiline_comment|/* timer 4 counter reg      */
DECL|member|timer_ter1
r_volatile
r_int
r_int
id|timer_ter1
suffix:semicolon
multiline_comment|/* timer 1 event reg        */
DECL|member|timer_ter2
r_volatile
r_int
r_int
id|timer_ter2
suffix:semicolon
multiline_comment|/* timer 2 event reg        */
DECL|member|timer_ter3
r_volatile
r_int
r_int
id|timer_ter3
suffix:semicolon
multiline_comment|/* timer 3 event reg        */
DECL|member|timer_ter4
r_volatile
r_int
r_int
id|timer_ter4
suffix:semicolon
multiline_comment|/* timer 4 event reg        */
DECL|member|RESERVED34
r_volatile
r_int
r_char
id|RESERVED34
(braket
l_int|0x8
)braket
suffix:semicolon
multiline_comment|/* Reserved area    */
multiline_comment|/* CP */
DECL|member|cp_cr
r_volatile
r_int
r_int
id|cp_cr
suffix:semicolon
multiline_comment|/* command register         */
DECL|member|RESERVED35
r_volatile
r_int
r_char
id|RESERVED35
(braket
l_int|0x2
)braket
suffix:semicolon
multiline_comment|/* Reserved area    */
DECL|member|cp_rccr
r_volatile
r_int
r_int
id|cp_rccr
suffix:semicolon
multiline_comment|/* main configuration reg   */
DECL|member|RESERVED37
r_volatile
r_int
r_char
id|RESERVED37
suffix:semicolon
multiline_comment|/* Reserved area            */
DECL|member|cp_rmds
r_volatile
r_int
r_char
id|cp_rmds
suffix:semicolon
multiline_comment|/* development support status reg */
DECL|member|cp_rmdr
r_volatile
r_int
r_int
id|cp_rmdr
suffix:semicolon
multiline_comment|/* development support control reg */
DECL|member|cp_rctr1
r_volatile
r_int
r_int
id|cp_rctr1
suffix:semicolon
multiline_comment|/* ram break register 1     */
DECL|member|cp_rctr2
r_volatile
r_int
r_int
id|cp_rctr2
suffix:semicolon
multiline_comment|/* ram break register 2     */
DECL|member|cp_rctr3
r_volatile
r_int
r_int
id|cp_rctr3
suffix:semicolon
multiline_comment|/* ram break register 3     */
DECL|member|cp_rctr4
r_volatile
r_int
r_int
id|cp_rctr4
suffix:semicolon
multiline_comment|/* ram break register 4     */
DECL|member|RESERVED59
r_volatile
r_int
r_char
id|RESERVED59
(braket
l_int|0x2
)braket
suffix:semicolon
multiline_comment|/* Reserved area    */
DECL|member|cp_rter
r_volatile
r_int
r_int
id|cp_rter
suffix:semicolon
multiline_comment|/* RISC timers event reg    */
DECL|member|RESERVED38
r_volatile
r_int
r_char
id|RESERVED38
(braket
l_int|0x2
)braket
suffix:semicolon
multiline_comment|/* Reserved area    */
DECL|member|cp_rtmr
r_volatile
r_int
r_int
id|cp_rtmr
suffix:semicolon
multiline_comment|/* RISC timers mask reg     */
DECL|member|RESERVED39
r_volatile
r_int
r_char
id|RESERVED39
(braket
l_int|0x14
)braket
suffix:semicolon
multiline_comment|/* Reserved area    */
multiline_comment|/* BRG */
r_union
(brace
DECL|member|l
r_volatile
r_int
r_int
id|l
suffix:semicolon
r_struct
(brace
DECL|member|BRGC_RESERV
r_volatile
r_int
r_int
id|BRGC_RESERV
suffix:colon
l_int|14
suffix:semicolon
DECL|member|rst
r_volatile
r_int
r_int
id|rst
suffix:colon
l_int|1
suffix:semicolon
DECL|member|en
r_volatile
r_int
r_int
id|en
suffix:colon
l_int|1
suffix:semicolon
DECL|member|extc
r_volatile
r_int
r_int
id|extc
suffix:colon
l_int|2
suffix:semicolon
DECL|member|atb
r_volatile
r_int
r_int
id|atb
suffix:colon
l_int|1
suffix:semicolon
DECL|member|cd
r_volatile
r_int
r_int
id|cd
suffix:colon
l_int|12
suffix:semicolon
DECL|member|div16
r_volatile
r_int
r_int
id|div16
suffix:colon
l_int|1
suffix:semicolon
DECL|member|b
)brace
id|b
suffix:semicolon
DECL|member|brgc
)brace
id|brgc
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* BRG1-BRG4 configuration regs*/
multiline_comment|/* SCC registers */
DECL|struct|scc_regs
r_struct
id|scc_regs
(brace
r_union
(brace
r_struct
(brace
multiline_comment|/* Low word. */
DECL|member|GSMR_RESERV2
r_volatile
r_int
r_int
id|GSMR_RESERV2
suffix:colon
l_int|1
suffix:semicolon
DECL|member|edge
r_volatile
r_int
r_int
id|edge
suffix:colon
l_int|2
suffix:semicolon
DECL|member|tci
r_volatile
r_int
r_int
id|tci
suffix:colon
l_int|1
suffix:semicolon
DECL|member|tsnc
r_volatile
r_int
r_int
id|tsnc
suffix:colon
l_int|2
suffix:semicolon
DECL|member|rinv
r_volatile
r_int
r_int
id|rinv
suffix:colon
l_int|1
suffix:semicolon
DECL|member|tinv
r_volatile
r_int
r_int
id|tinv
suffix:colon
l_int|1
suffix:semicolon
DECL|member|tpl
r_volatile
r_int
r_int
id|tpl
suffix:colon
l_int|3
suffix:semicolon
DECL|member|tpp
r_volatile
r_int
r_int
id|tpp
suffix:colon
l_int|2
suffix:semicolon
DECL|member|tend
r_volatile
r_int
r_int
id|tend
suffix:colon
l_int|1
suffix:semicolon
DECL|member|tdcr
r_volatile
r_int
r_int
id|tdcr
suffix:colon
l_int|2
suffix:semicolon
DECL|member|rdcr
r_volatile
r_int
r_int
id|rdcr
suffix:colon
l_int|2
suffix:semicolon
DECL|member|renc
r_volatile
r_int
r_int
id|renc
suffix:colon
l_int|3
suffix:semicolon
DECL|member|tenc
r_volatile
r_int
r_int
id|tenc
suffix:colon
l_int|3
suffix:semicolon
DECL|member|diag
r_volatile
r_int
r_int
id|diag
suffix:colon
l_int|2
suffix:semicolon
DECL|member|enr
r_volatile
r_int
r_int
id|enr
suffix:colon
l_int|1
suffix:semicolon
DECL|member|ent
r_volatile
r_int
r_int
id|ent
suffix:colon
l_int|1
suffix:semicolon
DECL|member|mode
r_volatile
r_int
r_int
id|mode
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* High word. */
DECL|member|GSMR_RESERV1
r_volatile
r_int
r_int
id|GSMR_RESERV1
suffix:colon
l_int|14
suffix:semicolon
DECL|member|pri
r_volatile
r_int
r_int
id|pri
suffix:colon
l_int|1
suffix:semicolon
DECL|member|gde
r_volatile
r_int
r_int
id|gde
suffix:colon
l_int|1
suffix:semicolon
DECL|member|tcrc
r_volatile
r_int
r_int
id|tcrc
suffix:colon
l_int|2
suffix:semicolon
DECL|member|revd
r_volatile
r_int
r_int
id|revd
suffix:colon
l_int|1
suffix:semicolon
DECL|member|trx
r_volatile
r_int
r_int
id|trx
suffix:colon
l_int|1
suffix:semicolon
DECL|member|ttx
r_volatile
r_int
r_int
id|ttx
suffix:colon
l_int|1
suffix:semicolon
DECL|member|cdp
r_volatile
r_int
r_int
id|cdp
suffix:colon
l_int|1
suffix:semicolon
DECL|member|ctsp
r_volatile
r_int
r_int
id|ctsp
suffix:colon
l_int|1
suffix:semicolon
DECL|member|cds
r_volatile
r_int
r_int
id|cds
suffix:colon
l_int|1
suffix:semicolon
DECL|member|ctss
r_volatile
r_int
r_int
id|ctss
suffix:colon
l_int|1
suffix:semicolon
DECL|member|tfl
r_volatile
r_int
r_int
id|tfl
suffix:colon
l_int|1
suffix:semicolon
DECL|member|rfw
r_volatile
r_int
r_int
id|rfw
suffix:colon
l_int|1
suffix:semicolon
DECL|member|txsy
r_volatile
r_int
r_int
id|txsy
suffix:colon
l_int|1
suffix:semicolon
DECL|member|synl
r_volatile
r_int
r_int
id|synl
suffix:colon
l_int|2
suffix:semicolon
DECL|member|rtsm
r_volatile
r_int
r_int
id|rtsm
suffix:colon
l_int|1
suffix:semicolon
DECL|member|rsyn
r_volatile
r_int
r_int
id|rsyn
suffix:colon
l_int|1
suffix:semicolon
DECL|member|b
)brace
id|b
suffix:semicolon
r_struct
(brace
DECL|member|low
r_volatile
r_int
r_int
id|low
suffix:semicolon
DECL|member|high
r_volatile
r_int
r_int
id|high
suffix:semicolon
DECL|member|w
)brace
id|w
suffix:semicolon
DECL|member|scc_gsmr
)brace
id|scc_gsmr
suffix:semicolon
multiline_comment|/* SCC general mode reg         */
DECL|member|scc_psmr
r_volatile
r_int
r_int
id|scc_psmr
suffix:semicolon
multiline_comment|/* protocol specific mode reg   */
DECL|member|RESERVED42
r_volatile
r_int
r_char
id|RESERVED42
(braket
l_int|0x2
)braket
suffix:semicolon
multiline_comment|/* Reserved area           */
DECL|member|scc_todr
r_volatile
r_int
r_int
id|scc_todr
suffix:semicolon
multiline_comment|/* SCC transmit on demand         */
DECL|member|scc_dsr
r_volatile
r_int
r_int
id|scc_dsr
suffix:semicolon
multiline_comment|/* SCC data sync reg        */
DECL|member|scc_scce
r_volatile
r_int
r_int
id|scc_scce
suffix:semicolon
multiline_comment|/* SCC event reg            */
DECL|member|RESERVED43
r_volatile
r_int
r_char
id|RESERVED43
(braket
l_int|0x2
)braket
suffix:semicolon
multiline_comment|/* Reserved area            */
DECL|member|scc_sccm
r_volatile
r_int
r_int
id|scc_sccm
suffix:semicolon
multiline_comment|/* SCC mask reg             */
DECL|member|RESERVED44
r_volatile
r_int
r_char
id|RESERVED44
(braket
l_int|0x1
)braket
suffix:semicolon
multiline_comment|/* Reserved area            */
DECL|member|scc_sccs
r_volatile
r_int
r_char
id|scc_sccs
suffix:semicolon
multiline_comment|/* SCC status reg           */
DECL|member|RESERVED45
r_volatile
r_int
r_char
id|RESERVED45
(braket
l_int|0x8
)braket
suffix:semicolon
multiline_comment|/* Reserved area           */
DECL|member|scc_regs
)brace
id|scc_regs
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* SMC */
DECL|struct|smc_regs
r_struct
id|smc_regs
(brace
DECL|member|RESERVED46
r_volatile
r_int
r_char
id|RESERVED46
(braket
l_int|0x2
)braket
suffix:semicolon
multiline_comment|/* Reserved area           */
DECL|member|smc_smcmr
r_volatile
r_int
r_int
id|smc_smcmr
suffix:semicolon
multiline_comment|/* SMC mode reg            */
DECL|member|RESERVED60
r_volatile
r_int
r_char
id|RESERVED60
(braket
l_int|0x2
)braket
suffix:semicolon
multiline_comment|/* Reserved area           */
DECL|member|smc_smce
r_volatile
r_int
r_char
id|smc_smce
suffix:semicolon
multiline_comment|/* SMC event reg           */
DECL|member|RESERVED47
r_volatile
r_int
r_char
id|RESERVED47
(braket
l_int|0x3
)braket
suffix:semicolon
multiline_comment|/* Reserved area           */
DECL|member|smc_smcm
r_volatile
r_int
r_char
id|smc_smcm
suffix:semicolon
multiline_comment|/* SMC mask reg            */
DECL|member|RESERVED48
r_volatile
r_int
r_char
id|RESERVED48
(braket
l_int|0x5
)braket
suffix:semicolon
multiline_comment|/* Reserved area           */
DECL|member|smc_regs
)brace
id|smc_regs
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* SPI */
DECL|member|spi_spmode
r_volatile
r_int
r_int
id|spi_spmode
suffix:semicolon
multiline_comment|/* SPI mode reg             */
DECL|member|RESERVED51
r_volatile
r_int
r_char
id|RESERVED51
(braket
l_int|0x4
)braket
suffix:semicolon
multiline_comment|/* Reserved area    */
DECL|member|spi_spie
r_volatile
r_int
r_char
id|spi_spie
suffix:semicolon
multiline_comment|/* SPI event reg            */
DECL|member|RESERVED52
r_volatile
r_int
r_char
id|RESERVED52
(braket
l_int|0x3
)braket
suffix:semicolon
multiline_comment|/* Reserved area    */
DECL|member|spi_spim
r_volatile
r_int
r_char
id|spi_spim
suffix:semicolon
multiline_comment|/* SPI mask reg             */
DECL|member|RESERVED53
r_volatile
r_int
r_char
id|RESERVED53
(braket
l_int|0x2
)braket
suffix:semicolon
multiline_comment|/* Reserved area    */
DECL|member|spi_spcom
r_volatile
r_int
r_char
id|spi_spcom
suffix:semicolon
multiline_comment|/* SPI command reg          */
DECL|member|RESERVED54
r_volatile
r_int
r_char
id|RESERVED54
(braket
l_int|0x4
)braket
suffix:semicolon
multiline_comment|/* Reserved area    */
multiline_comment|/* PIP */
DECL|member|pip_pipc
r_volatile
r_int
r_int
id|pip_pipc
suffix:semicolon
multiline_comment|/* pip configuration reg    */
DECL|member|RESERVED65
r_volatile
r_int
r_char
id|RESERVED65
(braket
l_int|0x2
)braket
suffix:semicolon
multiline_comment|/* Reserved area    */
DECL|member|pip_ptpr
r_volatile
r_int
r_int
id|pip_ptpr
suffix:semicolon
multiline_comment|/* pip timing parameters reg */
DECL|member|pip_pbdir
r_volatile
r_int
r_int
id|pip_pbdir
suffix:semicolon
multiline_comment|/* port b data direction reg */
DECL|member|pip_pbpar
r_volatile
r_int
r_int
id|pip_pbpar
suffix:semicolon
multiline_comment|/* port b pin assignment reg */
DECL|member|pip_pbodr
r_volatile
r_int
r_int
id|pip_pbodr
suffix:semicolon
multiline_comment|/* port b open drain reg    */
DECL|member|pip_pbdat
r_volatile
r_int
r_int
id|pip_pbdat
suffix:semicolon
multiline_comment|/* port b data reg          */
DECL|member|RESERVED71
r_volatile
r_int
r_char
id|RESERVED71
(braket
l_int|0x18
)braket
suffix:semicolon
multiline_comment|/* Reserved area    */
multiline_comment|/* Serial Interface */
DECL|member|si_simode
r_volatile
r_int
r_int
id|si_simode
suffix:semicolon
multiline_comment|/* SI mode register         */
DECL|member|si_sigmr
r_volatile
r_int
r_char
id|si_sigmr
suffix:semicolon
multiline_comment|/* SI global mode register  */
DECL|member|RESERVED55
r_volatile
r_int
r_char
id|RESERVED55
suffix:semicolon
multiline_comment|/* Reserved area            */
DECL|member|si_sistr
r_volatile
r_int
r_char
id|si_sistr
suffix:semicolon
multiline_comment|/* SI status register       */
DECL|member|si_sicmr
r_volatile
r_int
r_char
id|si_sicmr
suffix:semicolon
multiline_comment|/* SI command register      */
DECL|member|RESERVED56
r_volatile
r_int
r_char
id|RESERVED56
(braket
l_int|0x4
)braket
suffix:semicolon
multiline_comment|/* Reserved area           */
DECL|member|si_sicr
r_volatile
r_int
r_int
id|si_sicr
suffix:semicolon
multiline_comment|/* SI clock routing         */
DECL|member|si_sirp
r_volatile
r_int
r_int
id|si_sirp
suffix:semicolon
multiline_comment|/* SI ram pointers          */
DECL|member|RESERVED57
r_volatile
r_int
r_char
id|RESERVED57
(braket
l_int|0xc
)braket
suffix:semicolon
multiline_comment|/* Reserved area           */
DECL|member|si_siram
r_volatile
r_int
r_int
id|si_siram
(braket
l_int|0x80
)braket
suffix:semicolon
multiline_comment|/* SI routing ram          */
DECL|typedef|QUICC
)brace
id|QUICC
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Local variables:&n; *  c-indent-level: 4&n; *  c-basic-offset: 4&n; *  tab-width: 4&n; * End:&n; */
eof
