multiline_comment|/*&n; * include/asm-ppc/ppc4xx_dma.h&n; *&n; * IBM PPC4xx DMA engine library&n; *&n; * Copyright 2000-2004 MontaVista Software Inc.&n; *&n; * Cleaned up a bit more, Matt Porter &lt;mporter@kernel.crashing.org&gt;&n; *&n; * Original code by Armin Kuster &lt;akuster@mvista.com&gt;&n; * and Pete Popov &lt;ppopov@mvista.com&gt;&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; *&n; * You should have received a copy of the  GNU General Public License along&n; * with this program; if not, write  to the Free Software Foundation, Inc.,&n; * 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASMPPC_PPC4xx_DMA_H
DECL|macro|__ASMPPC_PPC4xx_DMA_H
mdefine_line|#define __ASMPPC_PPC4xx_DMA_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/mmu.h&gt;
macro_line|#include &lt;asm/ibm4xx.h&gt;
DECL|macro|DEBUG_4xxDMA
macro_line|#undef DEBUG_4xxDMA
DECL|macro|MAX_PPC4xx_DMA_CHANNELS
mdefine_line|#define MAX_PPC4xx_DMA_CHANNELS&t;&t;4
multiline_comment|/* in arch/ppc/kernel/setup.c -- Cort */
r_extern
r_int
r_int
id|DMA_MODE_WRITE
comma
id|DMA_MODE_READ
suffix:semicolon
multiline_comment|/*&n; * Function return status codes&n; * These values are used to indicate whether or not the function&n; * call was successful, or a bad/invalid parameter was passed.&n; */
DECL|macro|DMA_STATUS_GOOD
mdefine_line|#define DMA_STATUS_GOOD&t;&t;&t;0
DECL|macro|DMA_STATUS_BAD_CHANNEL
mdefine_line|#define DMA_STATUS_BAD_CHANNEL&t;&t;1
DECL|macro|DMA_STATUS_BAD_HANDLE
mdefine_line|#define DMA_STATUS_BAD_HANDLE&t;&t;2
DECL|macro|DMA_STATUS_BAD_MODE
mdefine_line|#define DMA_STATUS_BAD_MODE&t;&t;3
DECL|macro|DMA_STATUS_NULL_POINTER
mdefine_line|#define DMA_STATUS_NULL_POINTER&t;&t;4
DECL|macro|DMA_STATUS_OUT_OF_MEMORY
mdefine_line|#define DMA_STATUS_OUT_OF_MEMORY&t;5
DECL|macro|DMA_STATUS_SGL_LIST_EMPTY
mdefine_line|#define DMA_STATUS_SGL_LIST_EMPTY&t;6
DECL|macro|DMA_STATUS_GENERAL_ERROR
mdefine_line|#define DMA_STATUS_GENERAL_ERROR&t;7
DECL|macro|DMA_STATUS_CHANNEL_NOTFREE
mdefine_line|#define DMA_STATUS_CHANNEL_NOTFREE&t;8
DECL|macro|DMA_CHANNEL_BUSY
mdefine_line|#define DMA_CHANNEL_BUSY&t;&t;0x80000000
multiline_comment|/*&n; * These indicate status as returned from the DMA Status Register.&n; */
DECL|macro|DMA_STATUS_NO_ERROR
mdefine_line|#define DMA_STATUS_NO_ERROR&t;0
DECL|macro|DMA_STATUS_CS
mdefine_line|#define DMA_STATUS_CS&t;&t;1&t;/* Count Status        */
DECL|macro|DMA_STATUS_TS
mdefine_line|#define DMA_STATUS_TS&t;&t;2&t;/* Transfer Status     */
DECL|macro|DMA_STATUS_DMA_ERROR
mdefine_line|#define DMA_STATUS_DMA_ERROR&t;3&t;/* DMA Error Occurred  */
DECL|macro|DMA_STATUS_DMA_BUSY
mdefine_line|#define DMA_STATUS_DMA_BUSY&t;4&t;/* The channel is busy */
multiline_comment|/*&n; * DMA Channel Control Registers&n; */
macro_line|#ifdef CONFIG_44x
DECL|macro|PPC4xx_DMA_64BIT
mdefine_line|#define&t;PPC4xx_DMA_64BIT
DECL|macro|DMA_CR_OFFSET
mdefine_line|#define DMA_CR_OFFSET 1
macro_line|#else
DECL|macro|DMA_CR_OFFSET
mdefine_line|#define DMA_CR_OFFSET 0
macro_line|#endif
DECL|macro|DMA_CE_ENABLE
mdefine_line|#define DMA_CE_ENABLE        (1&lt;&lt;31)&t;/* DMA Channel Enable */
DECL|macro|SET_DMA_CE_ENABLE
mdefine_line|#define SET_DMA_CE_ENABLE(x) (((x)&amp;0x1)&lt;&lt;31)
DECL|macro|GET_DMA_CE_ENABLE
mdefine_line|#define GET_DMA_CE_ENABLE(x) (((x)&amp;DMA_CE_ENABLE)&gt;&gt;31)
DECL|macro|DMA_CIE_ENABLE
mdefine_line|#define DMA_CIE_ENABLE        (1&lt;&lt;30)&t;/* DMA Channel Interrupt Enable */
DECL|macro|SET_DMA_CIE_ENABLE
mdefine_line|#define SET_DMA_CIE_ENABLE(x) (((x)&amp;0x1)&lt;&lt;30)
DECL|macro|GET_DMA_CIE_ENABLE
mdefine_line|#define GET_DMA_CIE_ENABLE(x) (((x)&amp;DMA_CIE_ENABLE)&gt;&gt;30)
DECL|macro|DMA_TD
mdefine_line|#define DMA_TD                (1&lt;&lt;29)
DECL|macro|SET_DMA_TD
mdefine_line|#define SET_DMA_TD(x)         (((x)&amp;0x1)&lt;&lt;29)
DECL|macro|GET_DMA_TD
mdefine_line|#define GET_DMA_TD(x)         (((x)&amp;DMA_TD)&gt;&gt;29)
DECL|macro|DMA_PL
mdefine_line|#define DMA_PL                (1&lt;&lt;28)&t;/* Peripheral Location */
DECL|macro|SET_DMA_PL
mdefine_line|#define SET_DMA_PL(x)         (((x)&amp;0x1)&lt;&lt;28)
DECL|macro|GET_DMA_PL
mdefine_line|#define GET_DMA_PL(x)         (((x)&amp;DMA_PL)&gt;&gt;28)
DECL|macro|EXTERNAL_PERIPHERAL
mdefine_line|#define EXTERNAL_PERIPHERAL    0
DECL|macro|INTERNAL_PERIPHERAL
mdefine_line|#define INTERNAL_PERIPHERAL    1
DECL|macro|SET_DMA_PW
mdefine_line|#define SET_DMA_PW(x)     (((x)&amp;0x3)&lt;&lt;(26-DMA_CR_OFFSET))&t;/* Peripheral Width */
DECL|macro|DMA_PW_MASK
mdefine_line|#define DMA_PW_MASK       SET_DMA_PW(3)
DECL|macro|PW_8
mdefine_line|#define   PW_8                 0
DECL|macro|PW_16
mdefine_line|#define   PW_16                1
DECL|macro|PW_32
mdefine_line|#define   PW_32                2
DECL|macro|PW_64
mdefine_line|#define   PW_64                3
multiline_comment|/* FIXME: Add PW_128 support for 440GP DMA block */
DECL|macro|GET_DMA_PW
mdefine_line|#define GET_DMA_PW(x)     (((x)&amp;DMA_PW_MASK)&gt;&gt;(26-DMA_CR_OFFSET))
DECL|macro|DMA_DAI
mdefine_line|#define DMA_DAI           (1&lt;&lt;(25-DMA_CR_OFFSET))&t;/* Destination Address Increment */
DECL|macro|SET_DMA_DAI
mdefine_line|#define SET_DMA_DAI(x)    (((x)&amp;0x1)&lt;&lt;(25-DMA_CR_OFFSET))
DECL|macro|DMA_SAI
mdefine_line|#define DMA_SAI           (1&lt;&lt;(24-DMA_CR_OFFSET))&t;/* Source Address Increment */
DECL|macro|SET_DMA_SAI
mdefine_line|#define SET_DMA_SAI(x)    (((x)&amp;0x1)&lt;&lt;(24-DMA_CR_OFFSET))
DECL|macro|DMA_BEN
mdefine_line|#define DMA_BEN           (1&lt;&lt;(23-DMA_CR_OFFSET))&t;/* Buffer Enable */
DECL|macro|SET_DMA_BEN
mdefine_line|#define SET_DMA_BEN(x)    (((x)&amp;0x1)&lt;&lt;(23-DMA_CR_OFFSET))
DECL|macro|SET_DMA_TM
mdefine_line|#define SET_DMA_TM(x)     (((x)&amp;0x3)&lt;&lt;(21-DMA_CR_OFFSET))&t;/* Transfer Mode */
DECL|macro|DMA_TM_MASK
mdefine_line|#define DMA_TM_MASK       SET_DMA_TM(3)
DECL|macro|TM_PERIPHERAL
mdefine_line|#define   TM_PERIPHERAL        0&t;/* Peripheral */
DECL|macro|TM_RESERVED
mdefine_line|#define   TM_RESERVED          1&t;/* Reserved */
DECL|macro|TM_S_MM
mdefine_line|#define   TM_S_MM              2&t;/* Memory to Memory */
DECL|macro|TM_D_MM
mdefine_line|#define   TM_D_MM              3&t;/* Device Paced Memory to Memory */
DECL|macro|GET_DMA_TM
mdefine_line|#define GET_DMA_TM(x)     (((x)&amp;DMA_TM_MASK)&gt;&gt;(21-DMA_CR_OFFSET))
DECL|macro|SET_DMA_PSC
mdefine_line|#define SET_DMA_PSC(x)    (((x)&amp;0x3)&lt;&lt;(19-DMA_CR_OFFSET))&t;/* Peripheral Setup Cycles */
DECL|macro|DMA_PSC_MASK
mdefine_line|#define DMA_PSC_MASK      SET_DMA_PSC(3)
DECL|macro|GET_DMA_PSC
mdefine_line|#define GET_DMA_PSC(x)    (((x)&amp;DMA_PSC_MASK)&gt;&gt;(19-DMA_CR_OFFSET))
DECL|macro|SET_DMA_PWC
mdefine_line|#define SET_DMA_PWC(x)    (((x)&amp;0x3F)&lt;&lt;(13-DMA_CR_OFFSET))&t;/* Peripheral Wait Cycles */
DECL|macro|DMA_PWC_MASK
mdefine_line|#define DMA_PWC_MASK      SET_DMA_PWC(0x3F)
DECL|macro|GET_DMA_PWC
mdefine_line|#define GET_DMA_PWC(x)    (((x)&amp;DMA_PWC_MASK)&gt;&gt;(13-DMA_CR_OFFSET))
DECL|macro|SET_DMA_PHC
mdefine_line|#define SET_DMA_PHC(x)    (((x)&amp;0x7)&lt;&lt;(10-DMA_CR_OFFSET))&t;/* Peripheral Hold Cycles */
DECL|macro|DMA_PHC_MASK
mdefine_line|#define DMA_PHC_MASK      SET_DMA_PHC(0x7)
DECL|macro|GET_DMA_PHC
mdefine_line|#define GET_DMA_PHC(x)    (((x)&amp;DMA_PHC_MASK)&gt;&gt;(10-DMA_CR_OFFSET))
DECL|macro|DMA_ETD_OUTPUT
mdefine_line|#define DMA_ETD_OUTPUT     (1&lt;&lt;(9-DMA_CR_OFFSET))&t;/* EOT pin is a TC output */
DECL|macro|SET_DMA_ETD
mdefine_line|#define SET_DMA_ETD(x)     (((x)&amp;0x1)&lt;&lt;(9-DMA_CR_OFFSET))
DECL|macro|DMA_TCE_ENABLE
mdefine_line|#define DMA_TCE_ENABLE     (1&lt;&lt;(8-DMA_CR_OFFSET))
DECL|macro|SET_DMA_TCE
mdefine_line|#define SET_DMA_TCE(x)     (((x)&amp;0x1)&lt;&lt;(8-DMA_CR_OFFSET))
DECL|macro|DMA_DEC
mdefine_line|#define DMA_DEC            (1&lt;&lt;(2))&t;/* Address Decrement */
DECL|macro|SET_DMA_DEC
mdefine_line|#define SET_DMA_DEC(x)     (((x)&amp;0x1)&lt;&lt;2)
DECL|macro|GET_DMA_DEC
mdefine_line|#define GET_DMA_DEC(x)     (((x)&amp;DMA_DEC)&gt;&gt;2)
multiline_comment|/*&n; * Transfer Modes&n; * These modes are defined in a way that makes it possible to&n; * simply &quot;or&quot; in the value in the control register.&n; */
DECL|macro|DMA_MODE_MM
mdefine_line|#define DMA_MODE_MM&t;&t;(SET_DMA_TM(TM_S_MM))&t;/* memory to memory */
multiline_comment|/* Device-paced memory to memory, */
multiline_comment|/* device is at source address    */
DECL|macro|DMA_MODE_MM_DEVATSRC
mdefine_line|#define DMA_MODE_MM_DEVATSRC&t;(DMA_TD | SET_DMA_TM(TM_D_MM))
multiline_comment|/* Device-paced memory to memory,      */
multiline_comment|/* device is at destination address    */
DECL|macro|DMA_MODE_MM_DEVATDST
mdefine_line|#define DMA_MODE_MM_DEVATDST&t;(SET_DMA_TM(TM_D_MM))
multiline_comment|/* 405gp/440gp */
DECL|macro|SET_DMA_PREFETCH
mdefine_line|#define SET_DMA_PREFETCH(x)   (((x)&amp;0x3)&lt;&lt;(4-DMA_CR_OFFSET))&t;/* Memory Read Prefetch */
DECL|macro|DMA_PREFETCH_MASK
mdefine_line|#define DMA_PREFETCH_MASK      SET_DMA_PREFETCH(3)
DECL|macro|PREFETCH_1
mdefine_line|#define   PREFETCH_1           0&t;/* Prefetch 1 Double Word */
DECL|macro|PREFETCH_2
mdefine_line|#define   PREFETCH_2           1
DECL|macro|PREFETCH_4
mdefine_line|#define   PREFETCH_4           2
DECL|macro|GET_DMA_PREFETCH
mdefine_line|#define GET_DMA_PREFETCH(x) (((x)&amp;DMA_PREFETCH_MASK)&gt;&gt;(4-DMA_CR_OFFSET))
DECL|macro|DMA_PCE
mdefine_line|#define DMA_PCE            (1&lt;&lt;(3-DMA_CR_OFFSET))&t;/* Parity Check Enable */
DECL|macro|SET_DMA_PCE
mdefine_line|#define SET_DMA_PCE(x)     (((x)&amp;0x1)&lt;&lt;(3-DMA_CR_OFFSET))
DECL|macro|GET_DMA_PCE
mdefine_line|#define GET_DMA_PCE(x)     (((x)&amp;DMA_PCE)&gt;&gt;(3-DMA_CR_OFFSET))
multiline_comment|/* stb3x */
DECL|macro|DMA_ECE_ENABLE
mdefine_line|#define DMA_ECE_ENABLE (1&lt;&lt;5)
DECL|macro|SET_DMA_ECE
mdefine_line|#define SET_DMA_ECE(x) (((x)&amp;0x1)&lt;&lt;5)
DECL|macro|GET_DMA_ECE
mdefine_line|#define GET_DMA_ECE(x) (((x)&amp;DMA_ECE_ENABLE)&gt;&gt;5)
DECL|macro|DMA_TCD_DISABLE
mdefine_line|#define DMA_TCD_DISABLE&t;(1&lt;&lt;4)
DECL|macro|SET_DMA_TCD
mdefine_line|#define SET_DMA_TCD(x) (((x)&amp;0x1)&lt;&lt;4)
DECL|macro|GET_DMA_TCD
mdefine_line|#define GET_DMA_TCD(x) (((x)&amp;DMA_TCD_DISABLE)&gt;&gt;4)
DECL|typedef|sgl_handle_t
r_typedef
r_uint32
id|sgl_handle_t
suffix:semicolon
macro_line|#ifdef CONFIG_PPC4xx_EDMA
DECL|macro|SGL_LIST_SIZE
mdefine_line|#define SGL_LIST_SIZE 4096
DECL|macro|DMA_PPC4xx_SIZE
mdefine_line|#define DMA_PPC4xx_SIZE SGL_LIST_SIZE
DECL|macro|SET_DMA_PRIORITY
mdefine_line|#define SET_DMA_PRIORITY(x)   (((x)&amp;0x3)&lt;&lt;(6-DMA_CR_OFFSET))&t;/* DMA Channel Priority */
DECL|macro|DMA_PRIORITY_MASK
mdefine_line|#define DMA_PRIORITY_MASK SET_DMA_PRIORITY(3)
DECL|macro|PRIORITY_LOW
mdefine_line|#define PRIORITY_LOW           0
DECL|macro|PRIORITY_MID_LOW
mdefine_line|#define PRIORITY_MID_LOW       1
DECL|macro|PRIORITY_MID_HIGH
mdefine_line|#define PRIORITY_MID_HIGH      2
DECL|macro|PRIORITY_HIGH
mdefine_line|#define PRIORITY_HIGH          3
DECL|macro|GET_DMA_PRIORITY
mdefine_line|#define GET_DMA_PRIORITY(x) (((x)&amp;DMA_PRIORITY_MASK)&gt;&gt;(6-DMA_CR_OFFSET))
multiline_comment|/*&n; * DMA Polarity Configuration Register&n; */
DECL|macro|DMAReq_ActiveLow
mdefine_line|#define DMAReq_ActiveLow(chan) (1&lt;&lt;(31-(chan*3)))
DECL|macro|DMAAck_ActiveLow
mdefine_line|#define DMAAck_ActiveLow(chan) (1&lt;&lt;(30-(chan*3)))
DECL|macro|EOT_ActiveLow
mdefine_line|#define EOT_ActiveLow(chan)    (1&lt;&lt;(29-(chan*3)))&t;/* End of Transfer */
multiline_comment|/*&n; * DMA Sleep Mode Register&n; */
DECL|macro|SLEEP_MODE_ENABLE
mdefine_line|#define SLEEP_MODE_ENABLE (1&lt;&lt;21)
multiline_comment|/*&n; * DMA Status Register&n; */
DECL|macro|DMA_CS0
mdefine_line|#define DMA_CS0           (1&lt;&lt;31)&t;/* Terminal Count has been reached */
DECL|macro|DMA_CS1
mdefine_line|#define DMA_CS1           (1&lt;&lt;30)
DECL|macro|DMA_CS2
mdefine_line|#define DMA_CS2           (1&lt;&lt;29)
DECL|macro|DMA_CS3
mdefine_line|#define DMA_CS3           (1&lt;&lt;28)
DECL|macro|DMA_TS0
mdefine_line|#define DMA_TS0           (1&lt;&lt;27)&t;/* End of Transfer has been requested */
DECL|macro|DMA_TS1
mdefine_line|#define DMA_TS1           (1&lt;&lt;26)
DECL|macro|DMA_TS2
mdefine_line|#define DMA_TS2           (1&lt;&lt;25)
DECL|macro|DMA_TS3
mdefine_line|#define DMA_TS3           (1&lt;&lt;24)
DECL|macro|DMA_CH0_ERR
mdefine_line|#define DMA_CH0_ERR       (1&lt;&lt;23)&t;/* DMA Chanel 0 Error */
DECL|macro|DMA_CH1_ERR
mdefine_line|#define DMA_CH1_ERR       (1&lt;&lt;22)
DECL|macro|DMA_CH2_ERR
mdefine_line|#define DMA_CH2_ERR       (1&lt;&lt;21)
DECL|macro|DMA_CH3_ERR
mdefine_line|#define DMA_CH3_ERR       (1&lt;&lt;20)
DECL|macro|DMA_IN_DMA_REQ0
mdefine_line|#define DMA_IN_DMA_REQ0   (1&lt;&lt;19)&t;/* Internal DMA Request is pending */
DECL|macro|DMA_IN_DMA_REQ1
mdefine_line|#define DMA_IN_DMA_REQ1   (1&lt;&lt;18)
DECL|macro|DMA_IN_DMA_REQ2
mdefine_line|#define DMA_IN_DMA_REQ2   (1&lt;&lt;17)
DECL|macro|DMA_IN_DMA_REQ3
mdefine_line|#define DMA_IN_DMA_REQ3   (1&lt;&lt;16)
DECL|macro|DMA_EXT_DMA_REQ0
mdefine_line|#define DMA_EXT_DMA_REQ0  (1&lt;&lt;15)&t;/* External DMA Request is pending */
DECL|macro|DMA_EXT_DMA_REQ1
mdefine_line|#define DMA_EXT_DMA_REQ1  (1&lt;&lt;14)
DECL|macro|DMA_EXT_DMA_REQ2
mdefine_line|#define DMA_EXT_DMA_REQ2  (1&lt;&lt;13)
DECL|macro|DMA_EXT_DMA_REQ3
mdefine_line|#define DMA_EXT_DMA_REQ3  (1&lt;&lt;12)
DECL|macro|DMA_CH0_BUSY
mdefine_line|#define DMA_CH0_BUSY      (1&lt;&lt;11)&t;/* DMA Channel 0 Busy */
DECL|macro|DMA_CH1_BUSY
mdefine_line|#define DMA_CH1_BUSY      (1&lt;&lt;10)
DECL|macro|DMA_CH2_BUSY
mdefine_line|#define DMA_CH2_BUSY       (1&lt;&lt;9)
DECL|macro|DMA_CH3_BUSY
mdefine_line|#define DMA_CH3_BUSY       (1&lt;&lt;8)
DECL|macro|DMA_SG0
mdefine_line|#define DMA_SG0            (1&lt;&lt;7)&t;/* DMA Channel 0 Scatter/Gather in progress */
DECL|macro|DMA_SG1
mdefine_line|#define DMA_SG1            (1&lt;&lt;6)
DECL|macro|DMA_SG2
mdefine_line|#define DMA_SG2            (1&lt;&lt;5)
DECL|macro|DMA_SG3
mdefine_line|#define DMA_SG3            (1&lt;&lt;4)
multiline_comment|/* DMA Channel Count Register */
DECL|macro|DMA_CTC_BTEN
mdefine_line|#define DMA_CTC_BTEN     (1&lt;&lt;23)    /* Burst Enable/Disable bit */
DECL|macro|DMA_CTC_BSIZ_MSK
mdefine_line|#define DMA_CTC_BSIZ_MSK (3&lt;&lt;21)    /* Mask of the Burst size bits */
DECL|macro|DMA_CTC_BSIZ_2
mdefine_line|#define DMA_CTC_BSIZ_2   (0)
DECL|macro|DMA_CTC_BSIZ_4
mdefine_line|#define DMA_CTC_BSIZ_4   (1&lt;&lt;21)
DECL|macro|DMA_CTC_BSIZ_8
mdefine_line|#define DMA_CTC_BSIZ_8   (2&lt;&lt;21)
DECL|macro|DMA_CTC_BSIZ_16
mdefine_line|#define DMA_CTC_BSIZ_16  (3&lt;&lt;21)
multiline_comment|/*&n; * DMA SG Command Register&n; */
DECL|macro|SSG_ENABLE
mdefine_line|#define SSG_ENABLE(chan)   &t;(1&lt;&lt;(31-chan))&t;/* Start Scatter Gather */
DECL|macro|SSG_MASK_ENABLE
mdefine_line|#define SSG_MASK_ENABLE(chan)&t;(1&lt;&lt;(15-chan))&t;/* Enable writing to SSG0 bit */
multiline_comment|/*&n; * DMA Scatter/Gather Descriptor Bit fields&n; */
DECL|macro|SG_LINK
mdefine_line|#define SG_LINK            (1&lt;&lt;31)&t;/* Link */
DECL|macro|SG_TCI_ENABLE
mdefine_line|#define SG_TCI_ENABLE      (1&lt;&lt;29)&t;/* Enable Terminal Count Interrupt */
DECL|macro|SG_ETI_ENABLE
mdefine_line|#define SG_ETI_ENABLE      (1&lt;&lt;28)&t;/* Enable End of Transfer Interrupt */
DECL|macro|SG_ERI_ENABLE
mdefine_line|#define SG_ERI_ENABLE      (1&lt;&lt;27)&t;/* Enable Error Interrupt */
DECL|macro|SG_COUNT_MASK
mdefine_line|#define SG_COUNT_MASK       0xFFFF&t;/* Count Field */
DECL|macro|SET_DMA_CONTROL
mdefine_line|#define SET_DMA_CONTROL &bslash;&n; &t;&t;(SET_DMA_CIE_ENABLE(p_init-&gt;int_enable) | /* interrupt enable         */ &bslash;&n; &t;&t;SET_DMA_BEN(p_init-&gt;buffer_enable)     | /* buffer enable            */&bslash;&n;&t;&t;SET_DMA_ETD(p_init-&gt;etd_output)        | /* end of transfer pin      */ &bslash;&n;&t;       &t;SET_DMA_TCE(p_init-&gt;tce_enable)        | /* terminal count enable    */ &bslash;&n;                SET_DMA_PL(p_init-&gt;pl)                 | /* peripheral location      */ &bslash;&n;                SET_DMA_DAI(p_init-&gt;dai)               | /* dest addr increment      */ &bslash;&n;                SET_DMA_SAI(p_init-&gt;sai)               | /* src addr increment       */ &bslash;&n;                SET_DMA_PRIORITY(p_init-&gt;cp)           |  /* channel priority        */ &bslash;&n;                SET_DMA_PW(p_init-&gt;pwidth)             |  /* peripheral/bus width    */ &bslash;&n;                SET_DMA_PSC(p_init-&gt;psc)               |  /* peripheral setup cycles */ &bslash;&n;                SET_DMA_PWC(p_init-&gt;pwc)               |  /* peripheral wait cycles  */ &bslash;&n;                SET_DMA_PHC(p_init-&gt;phc)               |  /* peripheral hold cycles  */ &bslash;&n;                SET_DMA_PREFETCH(p_init-&gt;pf)              /* read prefetch           */)
DECL|macro|GET_DMA_POLARITY
mdefine_line|#define GET_DMA_POLARITY(chan) (DMAReq_ActiveLow(chan) | DMAAck_ActiveLow(chan) | EOT_ActiveLow(chan))
macro_line|#elif defined(CONFIG_STBXXX_DMA)&t;&t;/* stb03xxx */
DECL|macro|DMA_PPC4xx_SIZE
mdefine_line|#define DMA_PPC4xx_SIZE&t;4096
multiline_comment|/*&n; * DMA Status Register&n; */
DECL|macro|SET_DMA_PRIORITY
mdefine_line|#define SET_DMA_PRIORITY(x)   (((x)&amp;0x00800001))&t;/* DMA Channel Priority */
DECL|macro|DMA_PRIORITY_MASK
mdefine_line|#define DMA_PRIORITY_MASK&t;0x00800001
DECL|macro|PRIORITY_LOW
mdefine_line|#define   PRIORITY_LOW         &t;0x00000000
DECL|macro|PRIORITY_MID_LOW
mdefine_line|#define   PRIORITY_MID_LOW     &t;0x00000001
DECL|macro|PRIORITY_MID_HIGH
mdefine_line|#define   PRIORITY_MID_HIGH    &t;0x00800000
DECL|macro|PRIORITY_HIGH
mdefine_line|#define   PRIORITY_HIGH        &t;0x00800001
DECL|macro|GET_DMA_PRIORITY
mdefine_line|#define GET_DMA_PRIORITY(x) (((((x)&amp;DMA_PRIORITY_MASK) &amp;0x00800000) &gt;&gt; 22 ) | (((x)&amp;DMA_PRIORITY_MASK) &amp;0x00000001))
DECL|macro|DMA_CS0
mdefine_line|#define DMA_CS0           (1&lt;&lt;31)&t;/* Terminal Count has been reached */
DECL|macro|DMA_CS1
mdefine_line|#define DMA_CS1           (1&lt;&lt;30)
DECL|macro|DMA_CS2
mdefine_line|#define DMA_CS2           (1&lt;&lt;29)
DECL|macro|DMA_CS3
mdefine_line|#define DMA_CS3           (1&lt;&lt;28)
DECL|macro|DMA_TS0
mdefine_line|#define DMA_TS0           (1&lt;&lt;27)&t;/* End of Transfer has been requested */
DECL|macro|DMA_TS1
mdefine_line|#define DMA_TS1           (1&lt;&lt;26)
DECL|macro|DMA_TS2
mdefine_line|#define DMA_TS2           (1&lt;&lt;25)
DECL|macro|DMA_TS3
mdefine_line|#define DMA_TS3           (1&lt;&lt;24)
DECL|macro|DMA_CH0_ERR
mdefine_line|#define DMA_CH0_ERR       (1&lt;&lt;23)&t;/* DMA Chanel 0 Error */
DECL|macro|DMA_CH1_ERR
mdefine_line|#define DMA_CH1_ERR       (1&lt;&lt;22)
DECL|macro|DMA_CH2_ERR
mdefine_line|#define DMA_CH2_ERR       (1&lt;&lt;21)
DECL|macro|DMA_CH3_ERR
mdefine_line|#define DMA_CH3_ERR       (1&lt;&lt;20)
DECL|macro|DMA_CT0
mdefine_line|#define DMA_CT0&t;&t;  (1&lt;&lt;19)&t;/* Chained transfere */
DECL|macro|DMA_IN_DMA_REQ0
mdefine_line|#define DMA_IN_DMA_REQ0   (1&lt;&lt;18)&t;/* Internal DMA Request is pending */
DECL|macro|DMA_IN_DMA_REQ1
mdefine_line|#define DMA_IN_DMA_REQ1   (1&lt;&lt;17)
DECL|macro|DMA_IN_DMA_REQ2
mdefine_line|#define DMA_IN_DMA_REQ2   (1&lt;&lt;16)
DECL|macro|DMA_IN_DMA_REQ3
mdefine_line|#define DMA_IN_DMA_REQ3   (1&lt;&lt;15)
DECL|macro|DMA_EXT_DMA_REQ0
mdefine_line|#define DMA_EXT_DMA_REQ0  (1&lt;&lt;14)&t;/* External DMA Request is pending */
DECL|macro|DMA_EXT_DMA_REQ1
mdefine_line|#define DMA_EXT_DMA_REQ1  (1&lt;&lt;13)
DECL|macro|DMA_EXT_DMA_REQ2
mdefine_line|#define DMA_EXT_DMA_REQ2  (1&lt;&lt;12)
DECL|macro|DMA_EXT_DMA_REQ3
mdefine_line|#define DMA_EXT_DMA_REQ3  (1&lt;&lt;11)
DECL|macro|DMA_CH0_BUSY
mdefine_line|#define DMA_CH0_BUSY      (1&lt;&lt;10)&t;/* DMA Channel 0 Busy */
DECL|macro|DMA_CH1_BUSY
mdefine_line|#define DMA_CH1_BUSY      (1&lt;&lt;9)
DECL|macro|DMA_CH2_BUSY
mdefine_line|#define DMA_CH2_BUSY       (1&lt;&lt;8)
DECL|macro|DMA_CH3_BUSY
mdefine_line|#define DMA_CH3_BUSY       (1&lt;&lt;7)
DECL|macro|DMA_CT1
mdefine_line|#define DMA_CT1            (1&lt;&lt;6)&t;/* Chained transfere */
DECL|macro|DMA_CT2
mdefine_line|#define DMA_CT2            (1&lt;&lt;5)
DECL|macro|DMA_CT3
mdefine_line|#define DMA_CT3            (1&lt;&lt;4)
DECL|macro|DMA_CH_ENABLE
mdefine_line|#define DMA_CH_ENABLE (1&lt;&lt;7)
DECL|macro|SET_DMA_CH
mdefine_line|#define SET_DMA_CH(x) (((x)&amp;0x1)&lt;&lt;7)
DECL|macro|GET_DMA_CH
mdefine_line|#define GET_DMA_CH(x) (((x)&amp;DMA_CH_ENABLE)&gt;&gt;7)
multiline_comment|/* STBx25xxx dma unique */
multiline_comment|/* enable device port on a dma channel&n; * example ext 0 on dma 1&n; */
DECL|macro|SSP0_RECV
mdefine_line|#define&t;SSP0_RECV&t;15
DECL|macro|SSP0_XMIT
mdefine_line|#define&t;SSP0_XMIT&t;14
DECL|macro|EXT_DMA_0
mdefine_line|#define EXT_DMA_0&t;12
DECL|macro|SC1_XMIT
mdefine_line|#define&t;SC1_XMIT&t;11
DECL|macro|SC1_RECV
mdefine_line|#define SC1_RECV&t;10
DECL|macro|EXT_DMA_2
mdefine_line|#define EXT_DMA_2&t;9
DECL|macro|EXT_DMA_3
mdefine_line|#define&t;EXT_DMA_3&t;8
DECL|macro|SERIAL2_XMIT
mdefine_line|#define SERIAL2_XMIT&t;7
DECL|macro|SERIAL2_RECV
mdefine_line|#define SERIAL2_RECV&t;6
DECL|macro|SC0_XMIT
mdefine_line|#define SC0_XMIT &t;5
DECL|macro|SC0_RECV
mdefine_line|#define&t;SC0_RECV&t;4
DECL|macro|SERIAL1_XMIT
mdefine_line|#define&t;SERIAL1_XMIT&t;3
DECL|macro|SERIAL1_RECV
mdefine_line|#define SERIAL1_RECV&t;2
DECL|macro|SERIAL0_XMIT
mdefine_line|#define&t;SERIAL0_XMIT&t;1
DECL|macro|SERIAL0_RECV
mdefine_line|#define SERIAL0_RECV&t;0
DECL|macro|DMA_CHAN_0
mdefine_line|#define DMA_CHAN_0&t;1
DECL|macro|DMA_CHAN_1
mdefine_line|#define DMA_CHAN_1&t;2
DECL|macro|DMA_CHAN_2
mdefine_line|#define DMA_CHAN_2&t;3
DECL|macro|DMA_CHAN_3
mdefine_line|#define DMA_CHAN_3&t;4
multiline_comment|/* end STBx25xx */
multiline_comment|/*&n; * Bit 30 must be one for Redwoods, otherwise transfers may receive errors.&n; */
DECL|macro|DMA_CR_MB0
mdefine_line|#define DMA_CR_MB0 0x2
DECL|macro|SET_DMA_CONTROL
mdefine_line|#define SET_DMA_CONTROL &bslash;&n;       &t;&t;(SET_DMA_CIE_ENABLE(p_init-&gt;int_enable) |  /* interrupt enable         */ &bslash;&n;&t;&t;SET_DMA_ETD(p_init-&gt;etd_output)        |  /* end of transfer pin      */ &bslash;&n;&t;&t;SET_DMA_TCE(p_init-&gt;tce_enable)        |  /* terminal count enable    */ &bslash;&n;&t;&t;SET_DMA_PL(p_init-&gt;pl)                 |  /* peripheral location      */ &bslash;&n;&t;&t;SET_DMA_DAI(p_init-&gt;dai)               |  /* dest addr increment      */ &bslash;&n;&t;&t;SET_DMA_SAI(p_init-&gt;sai)               |  /* src addr increment       */ &bslash;&n;&t;&t;SET_DMA_PRIORITY(p_init-&gt;cp)           |  /* channel priority        */  &bslash;&n;&t;&t;SET_DMA_PW(p_init-&gt;pwidth)             |  /* peripheral/bus width    */ &bslash;&n;&t;&t;SET_DMA_PSC(p_init-&gt;psc)               |  /* peripheral setup cycles */ &bslash;&n;&t;&t;SET_DMA_PWC(p_init-&gt;pwc)               |  /* peripheral wait cycles  */ &bslash;&n;&t;&t;SET_DMA_PHC(p_init-&gt;phc)               |  /* peripheral hold cycles  */ &bslash;&n;&t;&t;SET_DMA_TCD(p_init-&gt;tcd_disable)&t;  |  /* TC chain mode disable   */ &bslash;&n;&t;&t;SET_DMA_ECE(p_init-&gt;ece_enable)&t;  |  /* ECE chanin mode enable  */ &bslash;&n;&t;&t;SET_DMA_CH(p_init-&gt;ch_enable)&t;|    /* Chain enable &t;        */ &bslash;&n;&t;&t;DMA_CR_MB0&t;&t;&t;&t;/* must be one */)
DECL|macro|GET_DMA_POLARITY
mdefine_line|#define GET_DMA_POLARITY(chan) chan
macro_line|#endif
r_typedef
r_struct
(brace
DECL|member|in_use
r_int
r_int
id|in_use
suffix:semicolon
multiline_comment|/* set when channel is being used, clr when&n;&t;&t;&t;&t; * available.&n;&t;&t;&t;&t; */
multiline_comment|/*&n;&t; * Valid polarity settings:&n;&t; *   DMAReq_ActiveLow(n)&n;&t; *   DMAAck_ActiveLow(n)&n;&t; *   EOT_ActiveLow(n)&n;&t; *&n;&t; *   n is 0 to max dma chans&n;&t; */
DECL|member|polarity
r_int
r_int
id|polarity
suffix:semicolon
DECL|member|buffer_enable
r_char
id|buffer_enable
suffix:semicolon
multiline_comment|/* Boolean: buffer enable            */
DECL|member|tce_enable
r_char
id|tce_enable
suffix:semicolon
multiline_comment|/* Boolean: terminal count enable    */
DECL|member|etd_output
r_char
id|etd_output
suffix:semicolon
multiline_comment|/* Boolean: eot pin is a tc output   */
DECL|member|pce
r_char
id|pce
suffix:semicolon
multiline_comment|/* Boolean: parity check enable      */
multiline_comment|/*&n;&t; * Peripheral location:&n;&t; * INTERNAL_PERIPHERAL (UART0 on the 405GP)&n;&t; * EXTERNAL_PERIPHERAL&n;&t; */
DECL|member|pl
r_char
id|pl
suffix:semicolon
multiline_comment|/* internal/external peripheral      */
multiline_comment|/*&n;&t; * Valid pwidth settings:&n;&t; *   PW_8&n;&t; *   PW_16&n;&t; *   PW_32&n;&t; *   PW_64&n;&t; */
DECL|member|pwidth
r_int
r_int
id|pwidth
suffix:semicolon
DECL|member|dai
r_char
id|dai
suffix:semicolon
multiline_comment|/* Boolean: dst address increment   */
DECL|member|sai
r_char
id|sai
suffix:semicolon
multiline_comment|/* Boolean: src address increment   */
multiline_comment|/*&n;&t; * Valid psc settings: 0-3&n;&t; */
DECL|member|psc
r_int
r_int
id|psc
suffix:semicolon
multiline_comment|/* Peripheral Setup Cycles         */
multiline_comment|/*&n;&t; * Valid pwc settings:&n;&t; * 0-63&n;&t; */
DECL|member|pwc
r_int
r_int
id|pwc
suffix:semicolon
multiline_comment|/* Peripheral Wait Cycles          */
multiline_comment|/*&n;&t; * Valid phc settings:&n;&t; * 0-7&n;&t; */
DECL|member|phc
r_int
r_int
id|phc
suffix:semicolon
multiline_comment|/* Peripheral Hold Cycles          */
multiline_comment|/*&n;&t; * Valid cp (channel priority) settings:&n;&t; *   PRIORITY_LOW&n;&t; *   PRIORITY_MID_LOW&n;&t; *   PRIORITY_MID_HIGH&n;&t; *   PRIORITY_HIGH&n;&t; */
DECL|member|cp
r_int
r_int
id|cp
suffix:semicolon
multiline_comment|/* channel priority                */
multiline_comment|/*&n;&t; * Valid pf (memory read prefetch) settings:&n;&t; *&n;&t; *   PREFETCH_1&n;&t; *   PREFETCH_2&n;&t; *   PREFETCH_4&n;&t; */
DECL|member|pf
r_int
r_int
id|pf
suffix:semicolon
multiline_comment|/* memory read prefetch            */
multiline_comment|/*&n;&t; * Boolean: channel interrupt enable&n;&t; * NOTE: for sgl transfers, only the last descriptor will be setup to&n;&t; * interrupt.&n;&t; */
DECL|member|int_enable
r_char
id|int_enable
suffix:semicolon
DECL|member|shift
r_char
id|shift
suffix:semicolon
multiline_comment|/* easy access to byte_count shift, based on */
multiline_comment|/* the width of the channel                  */
DECL|member|control
r_uint32
id|control
suffix:semicolon
multiline_comment|/* channel control word                      */
multiline_comment|/* These variabled are used ONLY in single dma transfers              */
DECL|member|mode
r_int
r_int
id|mode
suffix:semicolon
multiline_comment|/* transfer mode                     */
DECL|member|addr
id|phys_addr_t
id|addr
suffix:semicolon
DECL|member|ce
r_char
id|ce
suffix:semicolon
multiline_comment|/* channel enable */
macro_line|#ifdef CONFIG_STB03xxx
DECL|member|ch_enable
r_char
id|ch_enable
suffix:semicolon
DECL|member|tcd_disable
r_char
id|tcd_disable
suffix:semicolon
DECL|member|ece_enable
r_char
id|ece_enable
suffix:semicolon
DECL|member|td
r_char
id|td
suffix:semicolon
multiline_comment|/* transfer direction */
macro_line|#endif
DECL|member|int_on_final_sg
r_char
id|int_on_final_sg
suffix:semicolon
multiline_comment|/* for scatter/gather - only interrupt on last sg */
DECL|typedef|ppc_dma_ch_t
)brace
id|ppc_dma_ch_t
suffix:semicolon
multiline_comment|/*&n; * PPC44x DMA implementations have a slightly different&n; * descriptor layout.  Probably moved about due to the&n; * change to 64-bit addresses and link pointer. I don&squot;t&n; * know why they didn&squot;t just leave control_count after&n; * the dst_addr.&n; */
macro_line|#ifdef PPC4xx_DMA_64BIT
r_typedef
r_struct
(brace
DECL|member|control
r_uint32
id|control
suffix:semicolon
DECL|member|control_count
r_uint32
id|control_count
suffix:semicolon
DECL|member|src_addr
id|phys_addr_t
id|src_addr
suffix:semicolon
DECL|member|dst_addr
id|phys_addr_t
id|dst_addr
suffix:semicolon
DECL|member|next
id|phys_addr_t
id|next
suffix:semicolon
DECL|typedef|ppc_sgl_t
)brace
id|ppc_sgl_t
suffix:semicolon
macro_line|#else
r_typedef
r_struct
(brace
DECL|member|control
r_uint32
id|control
suffix:semicolon
DECL|member|src_addr
id|phys_addr_t
id|src_addr
suffix:semicolon
DECL|member|dst_addr
id|phys_addr_t
id|dst_addr
suffix:semicolon
DECL|member|control_count
r_uint32
id|control_count
suffix:semicolon
DECL|member|next
r_uint32
id|next
suffix:semicolon
DECL|typedef|ppc_sgl_t
)brace
id|ppc_sgl_t
suffix:semicolon
macro_line|#endif
r_typedef
r_struct
(brace
DECL|member|dmanr
r_int
r_int
id|dmanr
suffix:semicolon
DECL|member|control
r_uint32
id|control
suffix:semicolon
multiline_comment|/* channel ctrl word; loaded from each descrptr */
DECL|member|sgl_control
r_uint32
id|sgl_control
suffix:semicolon
multiline_comment|/* LK, TCI, ETI, and ERI bits in sgl descriptor */
DECL|member|dma_addr
id|dma_addr_t
id|dma_addr
suffix:semicolon
multiline_comment|/* dma (physical) address of this list          */
DECL|member|phead
id|ppc_sgl_t
op_star
id|phead
suffix:semicolon
DECL|member|phead_dma
id|dma_addr_t
id|phead_dma
suffix:semicolon
DECL|member|ptail
id|ppc_sgl_t
op_star
id|ptail
suffix:semicolon
DECL|member|ptail_dma
id|dma_addr_t
id|ptail_dma
suffix:semicolon
DECL|typedef|sgl_list_info_t
)brace
id|sgl_list_info_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|src_addr
id|phys_addr_t
op_star
id|src_addr
suffix:semicolon
DECL|member|dst_addr
id|phys_addr_t
op_star
id|dst_addr
suffix:semicolon
DECL|member|dma_src_addr
id|phys_addr_t
id|dma_src_addr
suffix:semicolon
DECL|member|dma_dst_addr
id|phys_addr_t
id|dma_dst_addr
suffix:semicolon
DECL|typedef|pci_alloc_desc_t
)brace
id|pci_alloc_desc_t
suffix:semicolon
r_extern
id|ppc_dma_ch_t
id|dma_channels
(braket
)braket
suffix:semicolon
multiline_comment|/*&n; * The DMA API are in ppc4xx_dma.c and ppc4xx_sgdma.c&n; */
r_extern
r_int
id|ppc4xx_init_dma_channel
c_func
(paren
r_int
r_int
comma
id|ppc_dma_ch_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ppc4xx_get_channel_config
c_func
(paren
r_int
r_int
comma
id|ppc_dma_ch_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ppc4xx_set_channel_priority
c_func
(paren
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
r_int
id|ppc4xx_get_peripheral_width
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|ppc4xx_set_sg_addr
c_func
(paren
r_int
comma
id|phys_addr_t
)paren
suffix:semicolon
r_extern
r_int
id|ppc4xx_add_dma_sgl
c_func
(paren
id|sgl_handle_t
comma
id|phys_addr_t
comma
id|phys_addr_t
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|ppc4xx_enable_dma_sgl
c_func
(paren
id|sgl_handle_t
)paren
suffix:semicolon
r_extern
r_void
id|ppc4xx_disable_dma_sgl
c_func
(paren
id|sgl_handle_t
)paren
suffix:semicolon
r_extern
r_int
id|ppc4xx_get_dma_sgl_residue
c_func
(paren
id|sgl_handle_t
comma
id|phys_addr_t
op_star
comma
id|phys_addr_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ppc4xx_delete_dma_sgl_element
c_func
(paren
id|sgl_handle_t
comma
id|phys_addr_t
op_star
comma
id|phys_addr_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ppc4xx_alloc_dma_handle
c_func
(paren
id|sgl_handle_t
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|ppc4xx_free_dma_handle
c_func
(paren
id|sgl_handle_t
)paren
suffix:semicolon
r_extern
r_int
id|ppc4xx_get_dma_status
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|ppc4xx_enable_burst
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
id|ppc4xx_disable_burst
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
id|ppc4xx_set_burst_size
c_func
(paren
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|ppc4xx_set_src_addr
c_func
(paren
r_int
id|dmanr
comma
id|phys_addr_t
id|src_addr
)paren
suffix:semicolon
r_extern
r_void
id|ppc4xx_set_dst_addr
c_func
(paren
r_int
id|dmanr
comma
id|phys_addr_t
id|dst_addr
)paren
suffix:semicolon
r_extern
r_void
id|ppc4xx_enable_dma
c_func
(paren
r_int
r_int
id|dmanr
)paren
suffix:semicolon
r_extern
r_void
id|ppc4xx_disable_dma
c_func
(paren
r_int
r_int
id|dmanr
)paren
suffix:semicolon
r_extern
r_void
id|ppc4xx_set_dma_count
c_func
(paren
r_int
r_int
id|dmanr
comma
r_int
r_int
id|count
)paren
suffix:semicolon
r_extern
r_int
id|ppc4xx_get_dma_residue
c_func
(paren
r_int
r_int
id|dmanr
)paren
suffix:semicolon
r_extern
r_void
id|ppc4xx_set_dma_addr2
c_func
(paren
r_int
r_int
id|dmanr
comma
id|phys_addr_t
id|src_dma_addr
comma
id|phys_addr_t
id|dst_dma_addr
)paren
suffix:semicolon
r_extern
r_int
id|ppc4xx_enable_dma_interrupt
c_func
(paren
r_int
r_int
id|dmanr
)paren
suffix:semicolon
r_extern
r_int
id|ppc4xx_disable_dma_interrupt
c_func
(paren
r_int
r_int
id|dmanr
)paren
suffix:semicolon
r_extern
r_int
id|ppc4xx_clr_dma_status
c_func
(paren
r_int
r_int
id|dmanr
)paren
suffix:semicolon
r_extern
r_int
id|ppc4xx_map_dma_port
c_func
(paren
r_int
r_int
id|dmanr
comma
r_int
r_int
id|ocp_dma
comma
r_int
id|dma_chan
)paren
suffix:semicolon
r_extern
r_int
id|ppc4xx_disable_dma_port
c_func
(paren
r_int
r_int
id|dmanr
comma
r_int
r_int
id|ocp_dma
comma
r_int
id|dma_chan
)paren
suffix:semicolon
r_extern
r_int
id|ppc4xx_set_dma_mode
c_func
(paren
r_int
r_int
id|dmanr
comma
r_int
r_int
id|mode
)paren
suffix:semicolon
multiline_comment|/* These are in kernel/dma.c: */
multiline_comment|/* reserve a DMA channel */
r_extern
r_int
id|request_dma
c_func
(paren
r_int
r_int
id|dmanr
comma
r_const
r_char
op_star
id|device_id
)paren
suffix:semicolon
multiline_comment|/* release it again */
r_extern
r_void
id|free_dma
c_func
(paren
r_int
r_int
id|dmanr
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif&t;&t;&t;&t;/* __KERNEL__ */
eof
