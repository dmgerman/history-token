multiline_comment|/*&n; *  linux/drivers/mmc/mmci.h - ARM PrimeCell MMCI PL180/1 driver&n; *&n; *  Copyright (C) 2003 Deep Blue Solutions, Ltd, All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
DECL|macro|MMCIPOWER
mdefine_line|#define MMCIPOWER&t;&t;0x000
DECL|macro|MCI_PWR_OFF
mdefine_line|#define MCI_PWR_OFF&t;&t;0x00
DECL|macro|MCI_PWR_UP
mdefine_line|#define MCI_PWR_UP&t;&t;0x02
DECL|macro|MCI_PWR_ON
mdefine_line|#define MCI_PWR_ON&t;&t;0x03
DECL|macro|MCI_OD
mdefine_line|#define MCI_OD&t;&t;&t;(1 &lt;&lt; 6)
DECL|macro|MCI_ROD
mdefine_line|#define MCI_ROD&t;&t;&t;(1 &lt;&lt; 7)
DECL|macro|MMCICLOCK
mdefine_line|#define MMCICLOCK&t;&t;0x004
DECL|macro|MCI_CLK_ENABLE
mdefine_line|#define MCI_CLK_ENABLE&t;&t;(1 &lt;&lt; 8)
DECL|macro|MCI_CLK_PWRSAVE
mdefine_line|#define MCI_CLK_PWRSAVE&t;&t;(1 &lt;&lt; 9)
DECL|macro|MCI_CLK_BYPASS
mdefine_line|#define MCI_CLK_BYPASS&t;&t;(1 &lt;&lt; 10)
DECL|macro|MMCIARGUMENT
mdefine_line|#define MMCIARGUMENT&t;&t;0x008
DECL|macro|MMCICOMMAND
mdefine_line|#define MMCICOMMAND&t;&t;0x00c
DECL|macro|MCI_CPSM_RESPONSE
mdefine_line|#define MCI_CPSM_RESPONSE&t;(1 &lt;&lt; 6)
DECL|macro|MCI_CPSM_LONGRSP
mdefine_line|#define MCI_CPSM_LONGRSP&t;(1 &lt;&lt; 7)
DECL|macro|MCI_CPSM_INTERRUPT
mdefine_line|#define MCI_CPSM_INTERRUPT&t;(1 &lt;&lt; 8)
DECL|macro|MCI_CPSM_PENDING
mdefine_line|#define MCI_CPSM_PENDING&t;(1 &lt;&lt; 9)
DECL|macro|MCI_CPSM_ENABLE
mdefine_line|#define MCI_CPSM_ENABLE&t;&t;(1 &lt;&lt; 10)
DECL|macro|MMCIRESPCMD
mdefine_line|#define MMCIRESPCMD&t;&t;0x010
DECL|macro|MMCIRESPONSE0
mdefine_line|#define MMCIRESPONSE0&t;&t;0x014
DECL|macro|MMCIRESPONSE1
mdefine_line|#define MMCIRESPONSE1&t;&t;0x018
DECL|macro|MMCIRESPONSE2
mdefine_line|#define MMCIRESPONSE2&t;&t;0x01c
DECL|macro|MMCIRESPONSE3
mdefine_line|#define MMCIRESPONSE3&t;&t;0x020
DECL|macro|MMCIDATATIMER
mdefine_line|#define MMCIDATATIMER&t;&t;0x024
DECL|macro|MMCIDATALENGTH
mdefine_line|#define MMCIDATALENGTH&t;&t;0x028
DECL|macro|MMCIDATACTRL
mdefine_line|#define MMCIDATACTRL&t;&t;0x02c
DECL|macro|MCI_DPSM_ENABLE
mdefine_line|#define MCI_DPSM_ENABLE&t;&t;(1 &lt;&lt; 0)
DECL|macro|MCI_DPSM_DIRECTION
mdefine_line|#define MCI_DPSM_DIRECTION&t;(1 &lt;&lt; 1)
DECL|macro|MCI_DPSM_MODE
mdefine_line|#define MCI_DPSM_MODE&t;&t;(1 &lt;&lt; 2)
DECL|macro|MCI_DPSM_DMAENABLE
mdefine_line|#define MCI_DPSM_DMAENABLE&t;(1 &lt;&lt; 3)
DECL|macro|MMCIDATACNT
mdefine_line|#define MMCIDATACNT&t;&t;0x030
DECL|macro|MMCISTATUS
mdefine_line|#define MMCISTATUS&t;&t;0x034
DECL|macro|MCI_CMDCRCFAIL
mdefine_line|#define MCI_CMDCRCFAIL&t;&t;(1 &lt;&lt; 0)
DECL|macro|MCI_DATACRCFAIL
mdefine_line|#define MCI_DATACRCFAIL&t;&t;(1 &lt;&lt; 1)
DECL|macro|MCI_CMDTIMEOUT
mdefine_line|#define MCI_CMDTIMEOUT&t;&t;(1 &lt;&lt; 2)
DECL|macro|MCI_DATATIMEOUT
mdefine_line|#define MCI_DATATIMEOUT&t;&t;(1 &lt;&lt; 3)
DECL|macro|MCI_TXUNDERRUN
mdefine_line|#define MCI_TXUNDERRUN&t;&t;(1 &lt;&lt; 4)
DECL|macro|MCI_RXOVERRUN
mdefine_line|#define MCI_RXOVERRUN&t;&t;(1 &lt;&lt; 5)
DECL|macro|MCI_CMDRESPEND
mdefine_line|#define MCI_CMDRESPEND&t;&t;(1 &lt;&lt; 6)
DECL|macro|MCI_CMDSENT
mdefine_line|#define MCI_CMDSENT&t;&t;(1 &lt;&lt; 7)
DECL|macro|MCI_DATAEND
mdefine_line|#define MCI_DATAEND&t;&t;(1 &lt;&lt; 8)
DECL|macro|MCI_DATABLOCKEND
mdefine_line|#define MCI_DATABLOCKEND&t;(1 &lt;&lt; 10)
DECL|macro|MCI_CMDACTIVE
mdefine_line|#define MCI_CMDACTIVE&t;&t;(1 &lt;&lt; 11)
DECL|macro|MCI_TXACTIVE
mdefine_line|#define MCI_TXACTIVE&t;&t;(1 &lt;&lt; 12)
DECL|macro|MCI_RXACTIVE
mdefine_line|#define MCI_RXACTIVE&t;&t;(1 &lt;&lt; 13)
DECL|macro|MCI_TXFIFOHALFEMPTY
mdefine_line|#define MCI_TXFIFOHALFEMPTY&t;(1 &lt;&lt; 14)
DECL|macro|MCI_RXFIFOHALFFULL
mdefine_line|#define MCI_RXFIFOHALFFULL&t;(1 &lt;&lt; 15)
DECL|macro|MCI_TXFIFOFULL
mdefine_line|#define MCI_TXFIFOFULL&t;&t;(1 &lt;&lt; 16)
DECL|macro|MCI_RXFIFOFULL
mdefine_line|#define MCI_RXFIFOFULL&t;&t;(1 &lt;&lt; 17)
DECL|macro|MCI_TXFIFOEMPTY
mdefine_line|#define MCI_TXFIFOEMPTY&t;&t;(1 &lt;&lt; 18)
DECL|macro|MCI_RXFIFOEMPTY
mdefine_line|#define MCI_RXFIFOEMPTY&t;&t;(1 &lt;&lt; 19)
DECL|macro|MCI_TXDATAAVLBL
mdefine_line|#define MCI_TXDATAAVLBL&t;&t;(1 &lt;&lt; 20)
DECL|macro|MCI_RXDATAAVLBL
mdefine_line|#define MCI_RXDATAAVLBL&t;&t;(1 &lt;&lt; 21)
DECL|macro|MMCICLEAR
mdefine_line|#define MMCICLEAR&t;&t;0x038
DECL|macro|MCI_CMDCRCFAILCLR
mdefine_line|#define MCI_CMDCRCFAILCLR&t;(1 &lt;&lt; 0)
DECL|macro|MCI_DATACRCFAILCLR
mdefine_line|#define MCI_DATACRCFAILCLR&t;(1 &lt;&lt; 1)
DECL|macro|MCI_CMDTIMEOUTCLR
mdefine_line|#define MCI_CMDTIMEOUTCLR&t;(1 &lt;&lt; 2)
DECL|macro|MCI_DATATIMEOUTCLR
mdefine_line|#define MCI_DATATIMEOUTCLR&t;(1 &lt;&lt; 3)
DECL|macro|MCI_TXUNDERRUNCLR
mdefine_line|#define MCI_TXUNDERRUNCLR&t;(1 &lt;&lt; 4)
DECL|macro|MCI_RXOVERRUNCLR
mdefine_line|#define MCI_RXOVERRUNCLR&t;(1 &lt;&lt; 5)
DECL|macro|MCI_CMDRESPENDCLR
mdefine_line|#define MCI_CMDRESPENDCLR&t;(1 &lt;&lt; 6)
DECL|macro|MCI_CMDSENTCLR
mdefine_line|#define MCI_CMDSENTCLR&t;&t;(1 &lt;&lt; 7)
DECL|macro|MCI_DATAENDCLR
mdefine_line|#define MCI_DATAENDCLR&t;&t;(1 &lt;&lt; 8)
DECL|macro|MCI_DATABLOCKENDCLR
mdefine_line|#define MCI_DATABLOCKENDCLR&t;(1 &lt;&lt; 10)
DECL|macro|MMCIMASK0
mdefine_line|#define MMCIMASK0&t;&t;0x03c
DECL|macro|MCI_CMDCRCFAILMASK
mdefine_line|#define MCI_CMDCRCFAILMASK&t;(1 &lt;&lt; 0)
DECL|macro|MCI_DATACRCFAILMASK
mdefine_line|#define MCI_DATACRCFAILMASK&t;(1 &lt;&lt; 1)
DECL|macro|MCI_CMDTIMEOUTMASK
mdefine_line|#define MCI_CMDTIMEOUTMASK&t;(1 &lt;&lt; 2)
DECL|macro|MCI_DATATIMEOUTMASK
mdefine_line|#define MCI_DATATIMEOUTMASK&t;(1 &lt;&lt; 3)
DECL|macro|MCI_TXUNDERRUNMASK
mdefine_line|#define MCI_TXUNDERRUNMASK&t;(1 &lt;&lt; 4)
DECL|macro|MCI_RXOVERRUNMASK
mdefine_line|#define MCI_RXOVERRUNMASK&t;(1 &lt;&lt; 5)
DECL|macro|MCI_CMDRESPENDMASK
mdefine_line|#define MCI_CMDRESPENDMASK&t;(1 &lt;&lt; 6)
DECL|macro|MCI_CMDSENTMASK
mdefine_line|#define MCI_CMDSENTMASK&t;&t;(1 &lt;&lt; 7)
DECL|macro|MCI_DATAENDMASK
mdefine_line|#define MCI_DATAENDMASK&t;&t;(1 &lt;&lt; 8)
DECL|macro|MCI_DATABLOCKENDMASK
mdefine_line|#define MCI_DATABLOCKENDMASK&t;(1 &lt;&lt; 10)
DECL|macro|MCI_CMDACTIVEMASK
mdefine_line|#define MCI_CMDACTIVEMASK&t;(1 &lt;&lt; 11)
DECL|macro|MCI_TXACTIVEMASK
mdefine_line|#define MCI_TXACTIVEMASK&t;(1 &lt;&lt; 12)
DECL|macro|MCI_RXACTIVEMASK
mdefine_line|#define MCI_RXACTIVEMASK&t;(1 &lt;&lt; 13)
DECL|macro|MCI_TXFIFOHALFEMPTYMASK
mdefine_line|#define MCI_TXFIFOHALFEMPTYMASK&t;(1 &lt;&lt; 14)
DECL|macro|MCI_RXFIFOHALFFULLMASK
mdefine_line|#define MCI_RXFIFOHALFFULLMASK&t;(1 &lt;&lt; 15)
DECL|macro|MCI_TXFIFOFULLMASK
mdefine_line|#define MCI_TXFIFOFULLMASK&t;(1 &lt;&lt; 16)
DECL|macro|MCI_RXFIFOFULLMASK
mdefine_line|#define MCI_RXFIFOFULLMASK&t;(1 &lt;&lt; 17)
DECL|macro|MCI_TXFIFOEMPTYMASK
mdefine_line|#define MCI_TXFIFOEMPTYMASK&t;(1 &lt;&lt; 18)
DECL|macro|MCI_RXFIFOEMPTYMASK
mdefine_line|#define MCI_RXFIFOEMPTYMASK&t;(1 &lt;&lt; 19)
DECL|macro|MCI_TXDATAAVLBLMASK
mdefine_line|#define MCI_TXDATAAVLBLMASK&t;(1 &lt;&lt; 20)
DECL|macro|MCI_RXDATAAVLBLMASK
mdefine_line|#define MCI_RXDATAAVLBLMASK&t;(1 &lt;&lt; 21)
DECL|macro|MMCIMASK1
mdefine_line|#define MMCIMASK1&t;&t;0x040
DECL|macro|MMCIFIFOCNT
mdefine_line|#define MMCIFIFOCNT&t;&t;0x048
DECL|macro|MMCIFIFO
mdefine_line|#define MMCIFIFO&t;&t;0x080 /* to 0x0bc */
DECL|macro|MCI_IRQENABLE
mdefine_line|#define MCI_IRQENABLE&t;&bslash;&n;&t;(MCI_CMDCRCFAILMASK|MCI_DATACRCFAILMASK|MCI_CMDTIMEOUTMASK|&t;&bslash;&n;&t;MCI_DATATIMEOUTMASK|MCI_TXUNDERRUNMASK|MCI_RXOVERRUNMASK|&t;&bslash;&n;&t;MCI_CMDRESPENDMASK|MCI_CMDSENTMASK|MCI_DATABLOCKENDMASK)
multiline_comment|/*&n; * The size of the FIFO in bytes.&n; */
DECL|macro|MCI_FIFOSIZE
mdefine_line|#define MCI_FIFOSIZE&t;(16*4)
DECL|macro|MCI_FIFOHALFSIZE
mdefine_line|#define MCI_FIFOHALFSIZE (MCI_FIFOSIZE / 2)
DECL|macro|NR_SG
mdefine_line|#define NR_SG&t;&t;16
r_struct
id|clk
suffix:semicolon
DECL|struct|mmci_host
r_struct
id|mmci_host
(brace
DECL|member|base
r_void
op_star
id|base
suffix:semicolon
DECL|member|mrq
r_struct
id|mmc_request
op_star
id|mrq
suffix:semicolon
DECL|member|cmd
r_struct
id|mmc_command
op_star
id|cmd
suffix:semicolon
DECL|member|data
r_struct
id|mmc_data
op_star
id|data
suffix:semicolon
DECL|member|mmc
r_struct
id|mmc_host
op_star
id|mmc
suffix:semicolon
DECL|member|clk
r_struct
id|clk
op_star
id|clk
suffix:semicolon
DECL|member|data_xfered
r_int
r_int
id|data_xfered
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|mclk
r_int
r_int
id|mclk
suffix:semicolon
DECL|member|cclk
r_int
r_int
id|cclk
suffix:semicolon
DECL|member|pwr
id|u32
id|pwr
suffix:semicolon
DECL|member|plat
r_struct
id|mmc_platform_data
op_star
id|plat
suffix:semicolon
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
DECL|member|oldstat
r_int
r_int
id|oldstat
suffix:semicolon
DECL|member|sg_len
r_int
r_int
id|sg_len
suffix:semicolon
multiline_comment|/* pio stuff */
DECL|member|sg_ptr
r_struct
id|scatterlist
op_star
id|sg_ptr
suffix:semicolon
DECL|member|sg_off
r_int
r_int
id|sg_off
suffix:semicolon
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
)brace
suffix:semicolon
DECL|function|mmci_init_sg
r_static
r_inline
r_void
id|mmci_init_sg
c_func
(paren
r_struct
id|mmci_host
op_star
id|host
comma
r_struct
id|mmc_data
op_star
id|data
)paren
(brace
multiline_comment|/*&n;&t; * Ideally, we want the higher levels to pass us a scatter list.&n;&t; */
id|host-&gt;sg_len
op_assign
id|data-&gt;sg_len
suffix:semicolon
id|host-&gt;sg_ptr
op_assign
id|data-&gt;sg
suffix:semicolon
id|host-&gt;sg_off
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|mmci_next_sg
r_static
r_inline
r_int
id|mmci_next_sg
c_func
(paren
r_struct
id|mmci_host
op_star
id|host
)paren
(brace
id|host-&gt;sg_ptr
op_increment
suffix:semicolon
id|host-&gt;sg_off
op_assign
l_int|0
suffix:semicolon
r_return
op_decrement
id|host-&gt;sg_len
suffix:semicolon
)brace
DECL|function|mmci_kmap_atomic
r_static
r_inline
r_char
op_star
id|mmci_kmap_atomic
c_func
(paren
r_struct
id|mmci_host
op_star
id|host
comma
r_int
r_int
op_star
id|flags
)paren
(brace
r_struct
id|scatterlist
op_star
id|sg
op_assign
id|host-&gt;sg_ptr
suffix:semicolon
id|local_irq_save
c_func
(paren
op_star
id|flags
)paren
suffix:semicolon
r_return
id|kmap_atomic
c_func
(paren
id|sg-&gt;page
comma
id|KM_BIO_SRC_IRQ
)paren
op_plus
id|sg-&gt;offset
suffix:semicolon
)brace
DECL|function|mmci_kunmap_atomic
r_static
r_inline
r_void
id|mmci_kunmap_atomic
c_func
(paren
r_struct
id|mmci_host
op_star
id|host
comma
r_int
r_int
op_star
id|flags
)paren
(brace
id|kunmap_atomic
c_func
(paren
id|host-&gt;sg_ptr-&gt;page
comma
id|KM_BIO_SRC_IRQ
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
op_star
id|flags
)paren
suffix:semicolon
)brace
eof
