multiline_comment|/* $Id$&n; *&n; * vic.h: Various VIC controller defines.  The VIC is an interrupt controller&n; *        used in Baget/MIPS series.&n; *&n; * Copyright (C) 1998 Gleb Raiko &amp; Vladimir Roganov&n; */
macro_line|#ifndef _MIPS_VIC_H
DECL|macro|_MIPS_VIC_H
mdefine_line|#define _MIPS_VIC_H
DECL|macro|VIC_VME_II
mdefine_line|#define VIC_VME_II       0x3
DECL|macro|VIC_VME_INT1
mdefine_line|#define VIC_VME_INT1     0x7
DECL|macro|VIC_VME_INT2
mdefine_line|#define VIC_VME_INT2     0xB
DECL|macro|VIC_VME_INT3
mdefine_line|#define VIC_VME_INT3     0xF
DECL|macro|VIC_VME_INT4
mdefine_line|#define VIC_VME_INT4     0x13
DECL|macro|VIC_VME_INT5
mdefine_line|#define VIC_VME_INT5     0x17
DECL|macro|VIC_VME_INT6
mdefine_line|#define VIC_VME_INT6     0x1B
DECL|macro|VIC_VME_INT7
mdefine_line|#define VIC_VME_INT7     0x1F
DECL|macro|VIC_DMA_INT
mdefine_line|#define VIC_DMA_INT      0x23
DECL|macro|VIC_LINT1
mdefine_line|#define VIC_LINT1        0x27
DECL|macro|VIC_LINT2
mdefine_line|#define VIC_LINT2        0x2B
DECL|macro|VIC_LINT3
mdefine_line|#define VIC_LINT3        0x2F
DECL|macro|VIC_LINT4
mdefine_line|#define VIC_LINT4        0x33
DECL|macro|VIC_LINT5
mdefine_line|#define VIC_LINT5        0x37
DECL|macro|VIC_LINT6
mdefine_line|#define VIC_LINT6        0x3B
DECL|macro|VIC_LINT7
mdefine_line|#define VIC_LINT7        0x3F
DECL|macro|VIC_ICGS_INT
mdefine_line|#define VIC_ICGS_INT     0x43
DECL|macro|VIC_ICMS_INT
mdefine_line|#define VIC_ICMS_INT     0x47
DECL|macro|VIC_INT_IPL
mdefine_line|#define    VIC_INT_IPL(lev)  ((~(lev))&amp;0x7)
DECL|macro|VIC_INT_ACTIVE
mdefine_line|#define    VIC_INT_ACTIVE    (1&lt;&lt;3)
DECL|macro|VIC_INT_AUTO
mdefine_line|#define    VIC_INT_AUTO      (0&lt;&lt;4)
DECL|macro|VIC_INT_NOAUTO
mdefine_line|#define    VIC_INT_NOAUTO    (1&lt;&lt;4)
DECL|macro|VIC_INT_LEVEL
mdefine_line|#define    VIC_INT_LEVEL     (0&lt;&lt;5)
DECL|macro|VIC_INT_EDGE
mdefine_line|#define    VIC_INT_EDGE      (1&lt;&lt;5)
DECL|macro|VIC_INT_LOW
mdefine_line|#define    VIC_INT_LOW       (0&lt;&lt;6)
DECL|macro|VIC_INT_HIGH
mdefine_line|#define    VIC_INT_HIGH      (1&lt;&lt;6)
DECL|macro|VIC_INT_ENABLE
mdefine_line|#define    VIC_INT_ENABLE    (0&lt;&lt;7)
DECL|macro|VIC_INT_DISABLE
mdefine_line|#define    VIC_INT_DISABLE   (1&lt;&lt;7)
DECL|macro|VIC_INT_SWITCH
mdefine_line|#define    VIC_INT_SWITCH(x) (1&lt;&lt;(((x)&amp;0x3)+4))
DECL|macro|VIC_ERR_INT
mdefine_line|#define VIC_ERR_INT      0x4B
DECL|macro|VIC_ERR_INT_SYSFAIL_ACTIVE
mdefine_line|#define    VIC_ERR_INT_SYSFAIL_ACTIVE  (1&lt;&lt;3)
DECL|macro|VIC_ERR_INT_SYSFAIL
mdefine_line|#define    VIC_ERR_INT_SYSFAIL  (1&lt;&lt;4)
DECL|macro|VIC_ERR_INT_TIMO
mdefine_line|#define    VIC_ERR_INT_TIMO     (1&lt;&lt;5)
DECL|macro|VIC_ERR_INT_WRPOST
mdefine_line|#define    VIC_ERR_INT_WRPOST   (1&lt;&lt;6)
DECL|macro|VIC_ERR_INT_ACFAIL
mdefine_line|#define    VIC_ERR_INT_ACFAIL   (1&lt;&lt;7)
DECL|macro|VIC_ICGS_BASE
mdefine_line|#define VIC_ICGS_BASE    0x4F
DECL|macro|VIC_ICMS_BASE
mdefine_line|#define VIC_ICMS_BASE    0x53
DECL|macro|VIC_ICxS_BASE_GSWITCH_MASK
mdefine_line|#define    VIC_ICxS_BASE_GSWITCH_MASK 0x3
DECL|macro|VIC_ICxS_BASE_ID
mdefine_line|#define    VIC_ICxS_BASE_ID(x)  (((x)&amp;0x3f)&lt;&lt;2)
DECL|macro|VIC_LOCAL_BASE
mdefine_line|#define VIC_LOCAL_BASE   0x57
DECL|macro|VIC_LOCAL_BASE_LINT_MASK
mdefine_line|#define    VIC_LOCAL_BASE_LINT_MASK 0x7
DECL|macro|VIC_LOCAL_BASE_ID
mdefine_line|#define    VIC_LOCAL_BASE_ID(x)  (((x)&amp;0x1f)&lt;&lt;3)
DECL|macro|VIC_ERR_BASE
mdefine_line|#define VIC_ERR_BASE     0x5B
DECL|macro|VIC_ERR_BASE_ACFAIL
mdefine_line|#define    VIC_ERR_BASE_ACFAIL   0
DECL|macro|VIC_ERR_BASE_WRPOST
mdefine_line|#define    VIC_ERR_BASE_WRPOST   1
DECL|macro|VIC_ERR_BASE_TIMO
mdefine_line|#define    VIC_ERR_BASE_TIMO     2
DECL|macro|VIC_ERR_BASE_SYSFAIL
mdefine_line|#define    VIC_ERR_BASE_SYSFAIL  3
DECL|macro|VIC_ERR_BASE_VMEACK
mdefine_line|#define    VIC_ERR_BASE_VMEACK   4
DECL|macro|VIC_ERR_BASE_DMA
mdefine_line|#define    VIC_ERR_BASE_DMA      5
DECL|macro|VIC_ERR_BASE_ID
mdefine_line|#define    VIC_ERR_BASE_ID(x)  (((x)&amp;0x1f)&lt;&lt;3)
DECL|macro|VIC_ICS
mdefine_line|#define VIC_ICS          0x5F
DECL|macro|VIC_IC0
mdefine_line|#define VIC_IC0          0x63
DECL|macro|VIC_IC1
mdefine_line|#define VIC_IC1          0x67
DECL|macro|VIC_IC2
mdefine_line|#define VIC_IC2          0x6B
DECL|macro|VIC_IC3
mdefine_line|#define VIC_IC3          0x6F
DECL|macro|VIC_IC4
mdefine_line|#define VIC_IC4          0x73
DECL|macro|VIC_ID
mdefine_line|#define VIC_ID           0x77
DECL|macro|VIC_IC6
mdefine_line|#define VIC_IC6          0x7B
DECL|macro|VIC_IC6_IRESET_STATUS
mdefine_line|#define    VIC_IC6_IRESET_STATUS (1&lt;&lt;7)
DECL|macro|VIC_IC6_HALT_STATUS
mdefine_line|#define    VIC_IC6_HALT_STATUS   (1&lt;&lt;6)
DECL|macro|VIC_IC6_SYSRESET
mdefine_line|#define    VIC_IC6_SYSRESET   (3&lt;&lt;0)
DECL|macro|VIC_IC6_RESET
mdefine_line|#define    VIC_IC6_RESET      (2&lt;&lt;0)
DECL|macro|VIC_IC6_HALT
mdefine_line|#define    VIC_IC6_HALT       (1&lt;&lt;0)
DECL|macro|VIC_IC6_RUN
mdefine_line|#define    VIC_IC6_RUN        (0&lt;&lt;0)
DECL|macro|VIC_IC7
mdefine_line|#define VIC_IC7          0x7F
DECL|macro|VIC_IC7_SYSFAIL
mdefine_line|#define    VIC_IC7_SYSFAIL     (1&lt;&lt;7)
DECL|macro|VIC_IC7_RESET
mdefine_line|#define    VIC_IC7_RESET       (1&lt;&lt;6)
DECL|macro|VIC_IC7_VME_MASTER
mdefine_line|#define    VIC_IC7_VME_MASTER  (1&lt;&lt;5)
DECL|macro|VIC_IC7_SEMSET
mdefine_line|#define    VIC_IC7_SEMSET(x)   ((1&lt;&lt;(x))&amp;0x1f)
DECL|macro|VIC_VME_REQ
mdefine_line|#define VIC_VME_REQ      0x83
DECL|macro|VIC_VME_BASE1
mdefine_line|#define VIC_VME_BASE1    0x87
DECL|macro|VIC_VME_BASE2
mdefine_line|#define VIC_VME_BASE2    0x8B
DECL|macro|VIC_VME_BASE3
mdefine_line|#define VIC_VME_BASE3    0x8F
DECL|macro|VIC_VME_BASE4
mdefine_line|#define VIC_VME_BASE4    0x93
DECL|macro|VIC_VME_BASE5
mdefine_line|#define VIC_VME_BASE5    0x97
DECL|macro|VIC_VME_BASE6
mdefine_line|#define VIC_VME_BASE6    0x9B
DECL|macro|VIC_VME_BASE7
mdefine_line|#define VIC_VME_BASE7    0x9F
DECL|macro|VIC_XFER_TIMO
mdefine_line|#define VIC_XFER_TIMO    0xA3
DECL|macro|VIC_XFER_TIMO_VME_PERIOD_INF
mdefine_line|#define    VIC_XFER_TIMO_VME_PERIOD_INF (7&lt;&lt;5)
DECL|macro|VIC_XFER_TIMO_VME_PERIOD_512
mdefine_line|#define    VIC_XFER_TIMO_VME_PERIOD_512 (6&lt;&lt;5)
DECL|macro|VIC_XFER_TIMO_VME_PERIOD_256
mdefine_line|#define    VIC_XFER_TIMO_VME_PERIOD_256 (5&lt;&lt;5)
DECL|macro|VIC_XFER_TIMO_VME_PERIOD_128
mdefine_line|#define    VIC_XFER_TIMO_VME_PERIOD_128 (4&lt;&lt;5)
DECL|macro|VIC_XFER_TIMO_VME_PERIOD_64
mdefine_line|#define    VIC_XFER_TIMO_VME_PERIOD_64 (3&lt;&lt;5)
DECL|macro|VIC_XFER_TIMO_VME_PERIOD_32
mdefine_line|#define    VIC_XFER_TIMO_VME_PERIOD_32 (2&lt;&lt;5)
DECL|macro|VIC_XFER_TIMO_VME_PERIOD_16
mdefine_line|#define    VIC_XFER_TIMO_VME_PERIOD_16 (1&lt;&lt;5)
DECL|macro|VIC_XFER_TIMO_VME_PERIOD_4
mdefine_line|#define    VIC_XFER_TIMO_VME_PERIOD_4  (0&lt;&lt;5)
DECL|macro|VIC_XFER_TIMO_VME_PERIOD_VAL
mdefine_line|#define    VIC_XFER_TIMO_VME_PERIOD_VAL(x) (((x)&gt;&gt;5)&amp;7)
DECL|macro|VIC_XFER_TIMO_LOCAL_PERIOD_INF
mdefine_line|#define    VIC_XFER_TIMO_LOCAL_PERIOD_INF (7&lt;&lt;2)
DECL|macro|VIC_XFER_TIMO_LOCAL_PERIOD_512
mdefine_line|#define    VIC_XFER_TIMO_LOCAL_PERIOD_512 (6&lt;&lt;2)
DECL|macro|VIC_XFER_TIMO_LOCAL_PERIOD_256
mdefine_line|#define    VIC_XFER_TIMO_LOCAL_PERIOD_256 (5&lt;&lt;2)
DECL|macro|VIC_XFER_TIMO_LOCAL_PERIOD_128
mdefine_line|#define    VIC_XFER_TIMO_LOCAL_PERIOD_128 (4&lt;&lt;2)
DECL|macro|VIC_XFER_TIMO_LOCAL_PERIOD_64
mdefine_line|#define    VIC_XFER_TIMO_LOCAL_PERIOD_64 (3&lt;&lt;2)
DECL|macro|VIC_XFER_TIMO_LOCAL_PERIOD_32
mdefine_line|#define    VIC_XFER_TIMO_LOCAL_PERIOD_32 (2&lt;&lt;2)
DECL|macro|VIC_XFER_TIMO_LOCAL_PERIOD_16
mdefine_line|#define    VIC_XFER_TIMO_LOCAL_PERIOD_16 (1&lt;&lt;2)
DECL|macro|VIC_XFER_TIMO_LOCAL_PERIOD_4
mdefine_line|#define    VIC_XFER_TIMO_LOCAL_PERIOD_4  (0&lt;&lt;2)
DECL|macro|VIC_XFER_TIMO_LOCAL_PERIOD_VAL
mdefine_line|#define    VIC_XFER_TIMO_LOCAL_PERIOD_VAL(x) (((x)&gt;&gt;2)&amp;7)
DECL|macro|VIC_XFER_TIMO_ARB
mdefine_line|#define    VIC_XFER_TIMO_ARB  (1&lt;&lt;1)
DECL|macro|VIC_XFER_TIMO_VME
mdefine_line|#define    VIC_XFER_TIMO_VME  (1&lt;&lt;0)
DECL|macro|VIC_LOCAL_TIM
mdefine_line|#define VIC_LOCAL_TIM    0xA7
DECL|macro|VIC_LOCAL_TIM_PAS_ASSERT
mdefine_line|#define    VIC_LOCAL_TIM_PAS_ASSERT(x)   (((x)-2)&amp;0xf)
DECL|macro|VIC_LOCAL_TIM_PAS_ASSERT_VAL
mdefine_line|#define    VIC_LOCAL_TIM_PAS_ASSERT_VAL(x) (((x)&amp;0xf)+2)
DECL|macro|VIC_LOCAT_TIM_DS_DEASSERT
mdefine_line|#define    VIC_LOCAT_TIM_DS_DEASSERT(x)  ((((x)-1)&amp;1)&lt;&lt;4)
DECL|macro|VIC_LOCAT_TIM_DS_DEASSERT_VAL
mdefine_line|#define    VIC_LOCAT_TIM_DS_DEASSERT_VAL(x)  ((((x)&gt;&gt;4)&amp;1)+1)
DECL|macro|VIC_LOCAL_TIM_PAS_DEASSERT
mdefine_line|#define    VIC_LOCAL_TIM_PAS_DEASSERT(x) ((((x)-1)&amp;0x7)&lt;&lt;5)
DECL|macro|VIC_LOCAL_TIM_PAS_DEASSERT_VAL
mdefine_line|#define    VIC_LOCAL_TIM_PAS_DEASSERT_VAL(x) ((((x)&gt;&gt;5)&amp;0x7)+1)
DECL|macro|VIC_BXFER_DEF
mdefine_line|#define VIC_BXFER_DEF    0xAB
DECL|macro|VIC_BXFER_DEF_VME_CROSS
mdefine_line|#define    VIC_BXFER_DEF_VME_CROSS    (1&lt;&lt;3)
DECL|macro|VIC_BXFER_DEF_LOCAL_CROSS
mdefine_line|#define    VIC_BXFER_DEF_LOCAL_CROSS  (1&lt;&lt;2)
DECL|macro|VIC_BXFER_DEF_AMSR
mdefine_line|#define    VIC_BXFER_DEF_AMSR   (1&lt;&lt;1)
DECL|macro|VIC_BXFER_DEF_DUAL
mdefine_line|#define    VIC_BXFER_DEF_DUAL   (1&lt;&lt;0)
DECL|macro|VIC_IFACE_CFG
mdefine_line|#define VIC_IFACE_CFG    0xAF
DECL|macro|VIC_IFACE_CFG_RMC3
mdefine_line|#define    VIC_IFACE_CFG_RMC3    (1&lt;&lt;7)
DECL|macro|VIC_IFACE_CFG_RMC2
mdefine_line|#define    VIC_IFACE_CFG_RMC2    (1&lt;&lt;6)
DECL|macro|VIC_IFACE_CFG_RMC1
mdefine_line|#define    VIC_IFACE_CFG_RMC1    (1&lt;&lt;5)
DECL|macro|VIC_IFACE_CFG_HALT
mdefine_line|#define    VIC_IFACE_CFG_HALT    (1&lt;&lt;4)
DECL|macro|VIC_IFACE_CFG_NOHALT
mdefine_line|#define    VIC_IFACE_CFG_NOHALT  (0&lt;&lt;4)
DECL|macro|VIC_IFACE_CFG_NORMC
mdefine_line|#define    VIC_IFACE_CFG_NORMC   (1&lt;&lt;3)
DECL|macro|VIC_IFACE_CFG_DEADLOCK_VAL
mdefine_line|#define    VIC_IFACE_CFG_DEADLOCK_VAL(x) (((x)&gt;&gt;3)&amp;3)
DECL|macro|VIC_IFACE_CFG_MSTAB
mdefine_line|#define    VIC_IFACE_CFG_MSTAB   (1&lt;&lt;2)
DECL|macro|VIC_IFACE_CFG_TURBO
mdefine_line|#define    VIC_IFACE_CFG_TURBO   (1&lt;&lt;1)
DECL|macro|VIC_IFACE_CFG_NOTURBO
mdefine_line|#define    VIC_IFACE_CFG_NOTURBO (0&lt;&lt;1)
DECL|macro|VIC_IFACE_CFG_VME
mdefine_line|#define    VIC_IFACE_CFG_VME     (1&lt;&lt;0)
DECL|macro|VIC_REQ_CFG
mdefine_line|#define VIC_REQ_CFG      0xB3
DECL|macro|VIC_REQ_CFG_FAIRNESS_DISABLED
mdefine_line|#define    VIC_REQ_CFG_FAIRNESS_DISABLED  0
DECL|macro|VIC_REQ_CFG_FAIRNESS_ENABLED
mdefine_line|#define    VIC_REQ_CFG_FAIRNESS_ENABLED   1
DECL|macro|VIC_REQ_CFG_TIMO_DISABLED
mdefine_line|#define    VIC_REQ_CFG_TIMO_DISABLED      0xf
DECL|macro|VIC_REQ_CFG_DRAM_REFRESH
mdefine_line|#define    VIC_REQ_CFG_DRAM_REFRESH       (1&lt;&lt;4)
DECL|macro|VIC_REQ_CFG_LEVEL
mdefine_line|#define    VIC_REQ_CFG_LEVEL(x)           (((x)&amp;3)&lt;&lt;5)
DECL|macro|VIC_REQ_CFG_PRIO_ARBITRATION
mdefine_line|#define    VIC_REQ_CFG_PRIO_ARBITRATION   (1&lt;&lt;7)
DECL|macro|VIC_REQ_CFG_RR_ARBITRATION
mdefine_line|#define    VIC_REQ_CFG_RR_ARBITRATION     (0&lt;&lt;7)
DECL|macro|VIC_AMS
mdefine_line|#define VIC_AMS          0xB7
DECL|macro|VIC_AMS_AM_2_0
mdefine_line|#define    VIC_AMS_AM_2_0   (1&lt;&lt;7)
DECL|macro|VIC_AMS_AM_5_3
mdefine_line|#define    VIC_AMS_AM_5_3   (1&lt;&lt;6)
DECL|macro|VIC_AMS_CODE
mdefine_line|#define    VIC_AMS_CODE(x)  ((x)&amp;0x1f)
DECL|macro|VIC_BERR_STATUS
mdefine_line|#define VIC_BERR_STATUS  0xBB
DECL|macro|VIC_DMA_STATUS
mdefine_line|#define VIC_DMA_STATUS   0xBF
DECL|macro|VIC_SS0CR0
mdefine_line|#define VIC_SS0CR0       0xC3
DECL|macro|VIC_SS1CR0
mdefine_line|#define VIC_SS1CR0       0xCB
DECL|macro|VIC_SSxCR0_LOCAL_XFER_ACCEL
mdefine_line|#define    VIC_SSxCR0_LOCAL_XFER_ACCEL  (2)
DECL|macro|VIC_SSxCR0_LOCAL_XFER_SINGLE
mdefine_line|#define    VIC_SSxCR0_LOCAL_XFER_SINGLE (1)
DECL|macro|VIC_SSxCR0_LOCAL_XFER_NONE
mdefine_line|#define    VIC_SSxCR0_LOCAL_XFER_NONE   (0)
DECL|macro|VIC_SSxCR0_A32
mdefine_line|#define    VIC_SSxCR0_A32       (0&lt;&lt;2)
DECL|macro|VIC_SSxCR0_A24
mdefine_line|#define    VIC_SSxCR0_A24       (1&lt;&lt;2)
DECL|macro|VIC_SSxCR0_A16
mdefine_line|#define    VIC_SSxCR0_A16       (2&lt;&lt;2)
DECL|macro|VIC_SSxCR0_USER
mdefine_line|#define    VIC_SSxCR0_USER      (3&lt;&lt;2)
DECL|macro|VIC_SSxCR0_D32
mdefine_line|#define    VIC_SSxCR0_D32       (1&lt;&lt;4)
DECL|macro|VIC_SSxCR0_SUPER
mdefine_line|#define    VIC_SSxCR0_SUPER     (1&lt;&lt;5)
DECL|macro|VIC_SS0CR0_TIMER_FREQ_MASK
mdefine_line|#define    VIC_SS0CR0_TIMER_FREQ_MASK   (3&lt;&lt;6)
DECL|macro|VIC_SS0CR0_TIMER_FREQ_NONE
mdefine_line|#define    VIC_SS0CR0_TIMER_FREQ_NONE   (0&lt;&lt;6)
DECL|macro|VIC_SS0CR0_TIMER_FREQ_50HZ
mdefine_line|#define    VIC_SS0CR0_TIMER_FREQ_50HZ   (1&lt;&lt;6)
DECL|macro|VIC_SS0CR0_TIMER_FREQ_1000HZ
mdefine_line|#define    VIC_SS0CR0_TIMER_FREQ_1000HZ (2&lt;&lt;6)
DECL|macro|VIC_SS0CR0_TIMER_FREQ_100HZ
mdefine_line|#define    VIC_SS0CR0_TIMER_FREQ_100HZ  (3&lt;&lt;6)
DECL|macro|VIC_SS1CR0_MASTER_WRPOST
mdefine_line|#define    VIC_SS1CR0_MASTER_WRPOST (1&lt;&lt;6)
DECL|macro|VIC_SS1CR0_SLAVE_WRPOST
mdefine_line|#define    VIC_SS1CR0_SLAVE_WRPOST  (1&lt;&lt;7)
DECL|macro|VIC_SS0CR1
mdefine_line|#define VIC_SS0CR1       0xC7
DECL|macro|VIC_SS1CR1
mdefine_line|#define VIC_SS1CR1       0xCF
DECL|macro|VIC_SSxCR1_TF2
mdefine_line|#define    VIC_SSxCR1_TF2(x)  (((x)&amp;0xf)&lt;&lt;4)
DECL|macro|VIC_SSxCR1_TF1
mdefine_line|#define    VIC_SSxCR1_TF1(x)  ((x)&amp;0xf)
DECL|macro|VIC_RELEASE
mdefine_line|#define VIC_RELEASE      0xD3
DECL|macro|VIC_RELEASE_BLKXFER_BLEN
mdefine_line|#define    VIC_RELEASE_BLKXFER_BLEN(x) ((x)&amp;0x1f)
DECL|macro|VIC_RELEASE_ROR
mdefine_line|#define    VIC_RELEASE_ROR             (0&lt;&lt;6) 
DECL|macro|VIC_RELEASE_RWD
mdefine_line|#define    VIC_RELEASE_RWD             (1&lt;&lt;6) 
DECL|macro|VIC_RELEASE_ROC
mdefine_line|#define    VIC_RELEASE_ROC             (2&lt;&lt;6) 
DECL|macro|VIC_RELEASE_BCAP
mdefine_line|#define    VIC_RELEASE_BCAP            (3&lt;&lt;6) 
DECL|macro|VIC_BXFER_CTRL
mdefine_line|#define VIC_BXFER_CTRL   0xD7
DECL|macro|VIC_BXFER_CTRL_MODULE
mdefine_line|#define    VIC_BXFER_CTRL_MODULE     (1&lt;&lt;7)
DECL|macro|VIC_BXFER_CTRL_LOCAL
mdefine_line|#define    VIC_BXFER_CTRL_LOCAL      (1&lt;&lt;6)
DECL|macro|VIC_BXFER_CTRL_MOVEM
mdefine_line|#define    VIC_BXFER_CTRL_MOVEM      (1&lt;&lt;5)
DECL|macro|VIC_BXFER_CTRL_READ
mdefine_line|#define    VIC_BXFER_CTRL_READ       (1&lt;&lt;4)
DECL|macro|VIC_BXFER_CTRL_WRITE
mdefine_line|#define    VIC_BXFER_CTRL_WRITE      (0&lt;&lt;4)
DECL|macro|VIC_BXFER_CTRL_INTERLEAVE
mdefine_line|#define    VIC_BXFER_CTRL_INTERLEAVE(x)  ((x)&amp;0xf)
DECL|macro|VIC_BXFER_LEN_LO
mdefine_line|#define VIC_BXFER_LEN_LO    0xDB
DECL|macro|VIC_BXFER_LEN_HI
mdefine_line|#define VIC_BXFER_LEN_HI    0xDF
DECL|macro|VIC_SYS_RESET
mdefine_line|#define VIC_SYS_RESET    0xE3
macro_line|#ifndef __LANGUAGE_ASSEMBLY__
DECL|macro|vic_inb
mdefine_line|#define vic_inb(p)    (*(volatile unsigned char *)(VIC_BASE + (p)))
DECL|macro|vic_outb
mdefine_line|#define vic_outb(v,p) (*((volatile unsigned char *)(VIC_BASE + (p))) = v)
macro_line|#endif /* __LANGUAGE_ASSEMBLY__ */
macro_line|#endif /* !(_MIPS_VIC_H) */
eof
