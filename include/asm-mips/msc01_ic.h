multiline_comment|/*&n; * PCI Register definitions for the MIPS System Controller.&n; *&n; * Copyright (C) 2004 MIPS Technologies, Inc.  All rights reserved.&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; */
macro_line|#ifndef __ASM_MIPS_BOARDS_MSC01_IC_H
DECL|macro|__ASM_MIPS_BOARDS_MSC01_IC_H
mdefine_line|#define __ASM_MIPS_BOARDS_MSC01_IC_H
multiline_comment|/*****************************************************************************&n; * Register offset addresses&n; *****************************************************************************/
DECL|macro|MSC01_IC_RST_OFS
mdefine_line|#define MSC01_IC_RST_OFS     0x00008    /* Software reset              */
DECL|macro|MSC01_IC_ENAL_OFS
mdefine_line|#define MSC01_IC_ENAL_OFS    0x00100    /* Int_in enable mask 31:0     */
DECL|macro|MSC01_IC_ENAH_OFS
mdefine_line|#define MSC01_IC_ENAH_OFS    0x00108    /* Int_in enable mask 63:32    */
DECL|macro|MSC01_IC_DISL_OFS
mdefine_line|#define MSC01_IC_DISL_OFS    0x00120    /* Int_in disable mask 31:0    */
DECL|macro|MSC01_IC_DISH_OFS
mdefine_line|#define MSC01_IC_DISH_OFS    0x00128    /* Int_in disable mask 63:32   */
DECL|macro|MSC01_IC_ISBL_OFS
mdefine_line|#define MSC01_IC_ISBL_OFS    0x00140    /* Raw int_in 31:0             */
DECL|macro|MSC01_IC_ISBH_OFS
mdefine_line|#define MSC01_IC_ISBH_OFS    0x00148    /* Raw int_in 63:32            */
DECL|macro|MSC01_IC_ISAL_OFS
mdefine_line|#define MSC01_IC_ISAL_OFS    0x00160    /* Masked int_in 31:0          */
DECL|macro|MSC01_IC_ISAH_OFS
mdefine_line|#define MSC01_IC_ISAH_OFS    0x00168    /* Masked int_in 63:32         */
DECL|macro|MSC01_IC_LVL_OFS
mdefine_line|#define MSC01_IC_LVL_OFS     0x00180    /* Disable priority int_out    */
DECL|macro|MSC01_IC_RAMW_OFS
mdefine_line|#define MSC01_IC_RAMW_OFS    0x00180    /* Shadow set RAM (EI)&t;       */
DECL|macro|MSC01_IC_OSB_OFS
mdefine_line|#define MSC01_IC_OSB_OFS     0x00188    /* Raw int_out                 */
DECL|macro|MSC01_IC_OSA_OFS
mdefine_line|#define MSC01_IC_OSA_OFS     0x00190    /* Masked int_out              */
DECL|macro|MSC01_IC_GENA_OFS
mdefine_line|#define MSC01_IC_GENA_OFS    0x00198    /* Global HW int enable        */
DECL|macro|MSC01_IC_BASE_OFS
mdefine_line|#define MSC01_IC_BASE_OFS    0x001a0    /* Base address of IC_VEC      */
DECL|macro|MSC01_IC_VEC_OFS
mdefine_line|#define MSC01_IC_VEC_OFS     0x001b0    /* Active int&squot;s vector address */
DECL|macro|MSC01_IC_EOI_OFS
mdefine_line|#define MSC01_IC_EOI_OFS     0x001c0    /* Enable lower level ints     */
DECL|macro|MSC01_IC_CFG_OFS
mdefine_line|#define MSC01_IC_CFG_OFS     0x001c8    /* Configuration register      */
DECL|macro|MSC01_IC_TRLD_OFS
mdefine_line|#define MSC01_IC_TRLD_OFS    0x001d0    /* Interval timer reload val   */
DECL|macro|MSC01_IC_TVAL_OFS
mdefine_line|#define MSC01_IC_TVAL_OFS    0x001e0    /* Interval timer current val  */
DECL|macro|MSC01_IC_TCFG_OFS
mdefine_line|#define MSC01_IC_TCFG_OFS    0x001f0    /* Interval timer config       */
DECL|macro|MSC01_IC_SUP_OFS
mdefine_line|#define MSC01_IC_SUP_OFS     0x00200    /* Set up int_in line 0        */
DECL|macro|MSC01_IC_ENA_OFS
mdefine_line|#define MSC01_IC_ENA_OFS     0x00800    /* Int_in enable mask 63:0     */
DECL|macro|MSC01_IC_DIS_OFS
mdefine_line|#define MSC01_IC_DIS_OFS     0x00820    /* Int_in disable mask 63:0    */
DECL|macro|MSC01_IC_ISB_OFS
mdefine_line|#define MSC01_IC_ISB_OFS     0x00840    /* Raw int_in 63:0             */
DECL|macro|MSC01_IC_ISA_OFS
mdefine_line|#define MSC01_IC_ISA_OFS     0x00860    /* Masked int_in 63:0          */
multiline_comment|/*****************************************************************************&n; * Register field encodings&n; *****************************************************************************/
DECL|macro|MSC01_IC_RST_RST_SHF
mdefine_line|#define MSC01_IC_RST_RST_SHF      0
DECL|macro|MSC01_IC_RST_RST_MSK
mdefine_line|#define MSC01_IC_RST_RST_MSK      0x00000001
DECL|macro|MSC01_IC_RST_RST_BIT
mdefine_line|#define MSC01_IC_RST_RST_BIT      MSC01_IC_RST_RST_MSK
DECL|macro|MSC01_IC_LVL_LVL_SHF
mdefine_line|#define MSC01_IC_LVL_LVL_SHF      0
DECL|macro|MSC01_IC_LVL_LVL_MSK
mdefine_line|#define MSC01_IC_LVL_LVL_MSK      0x000000ff
DECL|macro|MSC01_IC_LVL_SPUR_SHF
mdefine_line|#define MSC01_IC_LVL_SPUR_SHF     16
DECL|macro|MSC01_IC_LVL_SPUR_MSK
mdefine_line|#define MSC01_IC_LVL_SPUR_MSK     0x00010000
DECL|macro|MSC01_IC_LVL_SPUR_BIT
mdefine_line|#define MSC01_IC_LVL_SPUR_BIT     MSC01_IC_LVL_SPUR_MSK
DECL|macro|MSC01_IC_RAMW_RIPL_SHF
mdefine_line|#define MSC01_IC_RAMW_RIPL_SHF&t;  0
DECL|macro|MSC01_IC_RAMW_RIPL_MSK
mdefine_line|#define MSC01_IC_RAMW_RIPL_MSK&t;  0x0000003f
DECL|macro|MSC01_IC_RAMW_DATA_SHF
mdefine_line|#define MSC01_IC_RAMW_DATA_SHF&t;  6
DECL|macro|MSC01_IC_RAMW_DATA_MSK
mdefine_line|#define MSC01_IC_RAMW_DATA_MSK&t;  0x00000fc0
DECL|macro|MSC01_IC_RAMW_ADDR_SHF
mdefine_line|#define MSC01_IC_RAMW_ADDR_SHF&t;  25
DECL|macro|MSC01_IC_RAMW_ADDR_MSK
mdefine_line|#define MSC01_IC_RAMW_ADDR_MSK&t;  0x7e000000
DECL|macro|MSC01_IC_RAMW_READ_SHF
mdefine_line|#define MSC01_IC_RAMW_READ_SHF&t;  31
DECL|macro|MSC01_IC_RAMW_READ_MSK
mdefine_line|#define MSC01_IC_RAMW_READ_MSK&t;  0x80000000
DECL|macro|MSC01_IC_RAMW_READ_BIT
mdefine_line|#define MSC01_IC_RAMW_READ_BIT&t;  MSC01_IC_RAMW_READ_MSK
DECL|macro|MSC01_IC_OSB_OSB_SHF
mdefine_line|#define MSC01_IC_OSB_OSB_SHF      0
DECL|macro|MSC01_IC_OSB_OSB_MSK
mdefine_line|#define MSC01_IC_OSB_OSB_MSK      0x000000ff
DECL|macro|MSC01_IC_OSA_OSA_SHF
mdefine_line|#define MSC01_IC_OSA_OSA_SHF      0
DECL|macro|MSC01_IC_OSA_OSA_MSK
mdefine_line|#define MSC01_IC_OSA_OSA_MSK      0x000000ff
DECL|macro|MSC01_IC_GENA_GENA_SHF
mdefine_line|#define MSC01_IC_GENA_GENA_SHF    0
DECL|macro|MSC01_IC_GENA_GENA_MSK
mdefine_line|#define MSC01_IC_GENA_GENA_MSK    0x00000001
DECL|macro|MSC01_IC_GENA_GENA_BIT
mdefine_line|#define MSC01_IC_GENA_GENA_BIT    MSC01_IC_GENA_GENA_MSK
DECL|macro|MSC01_IC_CFG_DIS_SHF
mdefine_line|#define MSC01_IC_CFG_DIS_SHF      0
DECL|macro|MSC01_IC_CFG_DIS_MSK
mdefine_line|#define MSC01_IC_CFG_DIS_MSK      0x00000001
DECL|macro|MSC01_IC_CFG_DIS_BIT
mdefine_line|#define MSC01_IC_CFG_DIS_BIT      MSC01_IC_CFG_DIS_MSK
DECL|macro|MSC01_IC_CFG_SHFT_SHF
mdefine_line|#define MSC01_IC_CFG_SHFT_SHF     8
DECL|macro|MSC01_IC_CFG_SHFT_MSK
mdefine_line|#define MSC01_IC_CFG_SHFT_MSK     0x00000f00
DECL|macro|MSC01_IC_TCFG_ENA_SHF
mdefine_line|#define MSC01_IC_TCFG_ENA_SHF     0
DECL|macro|MSC01_IC_TCFG_ENA_MSK
mdefine_line|#define MSC01_IC_TCFG_ENA_MSK     0x00000001
DECL|macro|MSC01_IC_TCFG_ENA_BIT
mdefine_line|#define MSC01_IC_TCFG_ENA_BIT     MSC01_IC_TCFG_ENA_MSK
DECL|macro|MSC01_IC_TCFG_INT_SHF
mdefine_line|#define MSC01_IC_TCFG_INT_SHF     8
DECL|macro|MSC01_IC_TCFG_INT_MSK
mdefine_line|#define MSC01_IC_TCFG_INT_MSK     0x00000100
DECL|macro|MSC01_IC_TCFG_INT_BIT
mdefine_line|#define MSC01_IC_TCFG_INT_BIT     MSC01_IC_TCFG_INT_MSK
DECL|macro|MSC01_IC_TCFG_EDGE_SHF
mdefine_line|#define MSC01_IC_TCFG_EDGE_SHF    16
DECL|macro|MSC01_IC_TCFG_EDGE_MSK
mdefine_line|#define MSC01_IC_TCFG_EDGE_MSK    0x00010000
DECL|macro|MSC01_IC_TCFG_EDGE_BIT
mdefine_line|#define MSC01_IC_TCFG_EDGE_BIT    MSC01_IC_TCFG_EDGE_MSK
DECL|macro|MSC01_IC_SUP_PRI_SHF
mdefine_line|#define MSC01_IC_SUP_PRI_SHF      0
DECL|macro|MSC01_IC_SUP_PRI_MSK
mdefine_line|#define MSC01_IC_SUP_PRI_MSK      0x00000007
DECL|macro|MSC01_IC_SUP_EDGE_SHF
mdefine_line|#define MSC01_IC_SUP_EDGE_SHF     8
DECL|macro|MSC01_IC_SUP_EDGE_MSK
mdefine_line|#define MSC01_IC_SUP_EDGE_MSK     0x00000100
DECL|macro|MSC01_IC_SUP_EDGE_BIT
mdefine_line|#define MSC01_IC_SUP_EDGE_BIT     MSC01_IC_SUP_EDGE_MSK
DECL|macro|MSC01_IC_SUP_STEP
mdefine_line|#define MSC01_IC_SUP_STEP         8
multiline_comment|/*&n; * MIPS System controller interrupt register base.&n; *&n; * FIXME - are these macros specific to Malta and co or to the MSC?  If the&n; * latter, they should be moved elsewhere.&n; */
DECL|macro|MIPS_MSC01_IC_REG_BASE
mdefine_line|#define MIPS_MSC01_IC_REG_BASE&t;0x1bc40000
multiline_comment|/*****************************************************************************&n; * Absolute register addresses&n; *****************************************************************************/
DECL|macro|MSC01_IC_RST
mdefine_line|#define MSC01_IC_RST     (MSC01_IC_REG_BASE + MSC01_IC_RST_OFS)
DECL|macro|MSC01_IC_ENAL
mdefine_line|#define MSC01_IC_ENAL    (MSC01_IC_REG_BASE + MSC01_IC_ENAL_OFS)
DECL|macro|MSC01_IC_ENAH
mdefine_line|#define MSC01_IC_ENAH    (MSC01_IC_REG_BASE + MSC01_IC_ENAH_OFS)
DECL|macro|MSC01_IC_DISL
mdefine_line|#define MSC01_IC_DISL    (MSC01_IC_REG_BASE + MSC01_IC_DISL_OFS)
DECL|macro|MSC01_IC_DISH
mdefine_line|#define MSC01_IC_DISH    (MSC01_IC_REG_BASE + MSC01_IC_DISH_OFS)
DECL|macro|MSC01_IC_ISBL
mdefine_line|#define MSC01_IC_ISBL    (MSC01_IC_REG_BASE + MSC01_IC_ISBL_OFS)
DECL|macro|MSC01_IC_ISBH
mdefine_line|#define MSC01_IC_ISBH    (MSC01_IC_REG_BASE + MSC01_IC_ISBH_OFS)
DECL|macro|MSC01_IC_ISAL
mdefine_line|#define MSC01_IC_ISAL    (MSC01_IC_REG_BASE + MSC01_IC_ISAL_OFS)
DECL|macro|MSC01_IC_ISAH
mdefine_line|#define MSC01_IC_ISAH    (MSC01_IC_REG_BASE + MSC01_IC_ISAH_OFS)
DECL|macro|MSC01_IC_LVL
mdefine_line|#define MSC01_IC_LVL     (MSC01_IC_REG_BASE + MSC01_IC_LVL_OFS)
DECL|macro|MSC01_IC_RAMW
mdefine_line|#define MSC01_IC_RAMW    (MSC01_IC_REG_BASE + MSC01_IC_RAMW_OFS)
DECL|macro|MSC01_IC_OSB
mdefine_line|#define MSC01_IC_OSB     (MSC01_IC_REG_BASE + MSC01_IC_OSB_OFS)
DECL|macro|MSC01_IC_OSA
mdefine_line|#define MSC01_IC_OSA     (MSC01_IC_REG_BASE + MSC01_IC_OSA_OFS)
DECL|macro|MSC01_IC_GENA
mdefine_line|#define MSC01_IC_GENA    (MSC01_IC_REG_BASE + MSC01_IC_GENA_OFS)
DECL|macro|MSC01_IC_BASE
mdefine_line|#define MSC01_IC_BASE    (MSC01_IC_REG_BASE + MSC01_IC_BASE_OFS)
DECL|macro|MSC01_IC_VEC
mdefine_line|#define MSC01_IC_VEC     (MSC01_IC_REG_BASE + MSC01_IC_VEC_OFS)
DECL|macro|MSC01_IC_EOI
mdefine_line|#define MSC01_IC_EOI     (MSC01_IC_REG_BASE + MSC01_IC_EOI_OFS)
DECL|macro|MSC01_IC_CFG
mdefine_line|#define MSC01_IC_CFG     (MSC01_IC_REG_BASE + MSC01_IC_CFG_OFS)
DECL|macro|MSC01_IC_TRLD
mdefine_line|#define MSC01_IC_TRLD    (MSC01_IC_REG_BASE + MSC01_IC_TRLD_OFS)
DECL|macro|MSC01_IC_TVAL
mdefine_line|#define MSC01_IC_TVAL    (MSC01_IC_REG_BASE + MSC01_IC_TVAL_OFS)
DECL|macro|MSC01_IC_TCFG
mdefine_line|#define MSC01_IC_TCFG    (MSC01_IC_REG_BASE + MSC01_IC_TCFG_OFS)
DECL|macro|MSC01_IC_SUP
mdefine_line|#define MSC01_IC_SUP     (MSC01_IC_REG_BASE + MSC01_IC_SUP_OFS)
DECL|macro|MSC01_IC_ENA
mdefine_line|#define MSC01_IC_ENA     (MSC01_IC_REG_BASE + MSC01_IC_ENA_OFS)
DECL|macro|MSC01_IC_DIS
mdefine_line|#define MSC01_IC_DIS     (MSC01_IC_REG_BASE + MSC01_IC_DIS_OFS)
DECL|macro|MSC01_IC_ISB
mdefine_line|#define MSC01_IC_ISB     (MSC01_IC_REG_BASE + MSC01_IC_ISB_OFS)
DECL|macro|MSC01_IC_ISA
mdefine_line|#define MSC01_IC_ISA     (MSC01_IC_REG_BASE + MSC01_IC_ISA_OFS)
multiline_comment|/*&n; * Soc-it interrupts are configurable.&n; * Every board describes its IRQ mapping with this table.&n; */
DECL|struct|msc_irqmap
r_typedef
r_struct
id|msc_irqmap
(brace
DECL|member|im_irq
r_int
id|im_irq
suffix:semicolon
DECL|member|im_type
r_int
id|im_type
suffix:semicolon
DECL|member|im_lvl
r_int
id|im_lvl
suffix:semicolon
DECL|typedef|msc_irqmap_t
)brace
id|msc_irqmap_t
suffix:semicolon
multiline_comment|/* im_type */
DECL|macro|MSC01_IRQ_LEVEL
mdefine_line|#define MSC01_IRQ_LEVEL&t;&t;0
DECL|macro|MSC01_IRQ_EDGE
mdefine_line|#define MSC01_IRQ_EDGE&t;&t;1
r_extern
r_void
id|__init
id|init_msc_irqs
c_func
(paren
r_int
r_int
id|base
comma
id|msc_irqmap_t
op_star
id|imp
comma
r_int
id|nirq
)paren
suffix:semicolon
r_extern
r_void
id|ll_msc_irq
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
macro_line|#endif /* __ASM_MIPS_BOARDS_MSC01_IC_H */
eof
