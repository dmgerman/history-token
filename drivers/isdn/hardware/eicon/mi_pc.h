multiline_comment|/*&n; *&n;  Copyright (c) Eicon Networks, 2002.&n; *&n;  This source file is supplied for the use with&n;  Eicon Networks range of DIVA Server Adapters.&n; *&n;  Eicon File Revision :    2.1&n; *&n;  This program is free software; you can redistribute it and/or modify&n;  it under the terms of the GNU General Public License as published by&n;  the Free Software Foundation; either version 2, or (at your option)&n;  any later version.&n; *&n;  This program is distributed in the hope that it will be useful,&n;  but WITHOUT ANY WARRANTY OF ANY KIND WHATSOEVER INCLUDING ANY&n;  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n;  See the GNU General Public License for more details.&n; *&n;  You should have received a copy of the GNU General Public License&n;  along with this program; if not, write to the Free Software&n;  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
multiline_comment|/*----------------------------------------------------------------------------&n;// MAESTRA ISA PnP */
DECL|macro|BRI_MEMORY_BASE
mdefine_line|#define BRI_MEMORY_BASE                 0x1f700000
DECL|macro|BRI_MEMORY_SIZE
mdefine_line|#define BRI_MEMORY_SIZE                 0x00100000  /* 1MB on the BRI                         */
DECL|macro|BRI_SHARED_RAM_SIZE
mdefine_line|#define BRI_SHARED_RAM_SIZE             0x00010000  /* 64k shared RAM                         */
DECL|macro|BRI_RAY_TAYLOR_DSP_CODE_SIZE
mdefine_line|#define BRI_RAY_TAYLOR_DSP_CODE_SIZE    0x00020000  /* max 128k DSP-Code (Ray Taylor&squot;s code)  */
DECL|macro|BRI_ORG_MAX_DSP_CODE_SIZE
mdefine_line|#define BRI_ORG_MAX_DSP_CODE_SIZE       0x00050000  /* max 320k DSP-Code (Telindus)           */
DECL|macro|BRI_V90D_MAX_DSP_CODE_SIZE
mdefine_line|#define BRI_V90D_MAX_DSP_CODE_SIZE      0x00060000  /* max 384k DSP-Code if V.90D included    */
DECL|macro|BRI_CACHED_ADDR
mdefine_line|#define BRI_CACHED_ADDR(x)              (((x) &amp; 0x1fffffffL) | 0x80000000L)
DECL|macro|BRI_UNCACHED_ADDR
mdefine_line|#define BRI_UNCACHED_ADDR(x)            (((x) &amp; 0x1fffffffL) | 0xa0000000L)
DECL|macro|ADDR
mdefine_line|#define ADDR  4
DECL|macro|ADDRH
mdefine_line|#define ADDRH 6
DECL|macro|DATA
mdefine_line|#define DATA  0
DECL|macro|RESET
mdefine_line|#define RESET 7
DECL|macro|DEFAULT_ADDRESS
mdefine_line|#define DEFAULT_ADDRESS 0x240
DECL|macro|DEFAULT_IRQ
mdefine_line|#define DEFAULT_IRQ     3
DECL|macro|M_PCI_ADDR
mdefine_line|#define M_PCI_ADDR   0x04  /* MAESTRA BRI PCI */
DECL|macro|M_PCI_ADDRH
mdefine_line|#define M_PCI_ADDRH  0x0c  /* MAESTRA BRI PCI */
DECL|macro|M_PCI_DATA
mdefine_line|#define M_PCI_DATA   0x00  /* MAESTRA BRI PCI */
DECL|macro|M_PCI_RESET
mdefine_line|#define M_PCI_RESET  0x10  /* MAESTRA BRI PCI */
multiline_comment|/*----------------------------------------------------------------------------&n;// MAESTRA PRI PCI */
DECL|macro|MP_IRQ_RESET
mdefine_line|#define MP_IRQ_RESET                    0xc18       /* offset of isr in the CONFIG memory bar */
DECL|macro|MP_IRQ_RESET_VAL
mdefine_line|#define MP_IRQ_RESET_VAL                0xfe        /* value to clear an interrupt            */
DECL|macro|MP_MEMORY_SIZE
mdefine_line|#define MP_MEMORY_SIZE                  0x00400000  /* 4MB on standard PRI                    */
DECL|macro|MP2_MEMORY_SIZE
mdefine_line|#define MP2_MEMORY_SIZE                 0x00800000  /* 8MB on PRI Rev. 2                      */
DECL|macro|MP_SHARED_RAM_OFFSET
mdefine_line|#define MP_SHARED_RAM_OFFSET            0x00001000  /* offset of shared RAM base in the DRAM memory bar */
DECL|macro|MP_SHARED_RAM_SIZE
mdefine_line|#define MP_SHARED_RAM_SIZE              0x00010000  /* 64k shared RAM                         */
DECL|macro|MP_PROTOCOL_OFFSET
mdefine_line|#define MP_PROTOCOL_OFFSET              (MP_SHARED_RAM_OFFSET + MP_SHARED_RAM_SIZE)
DECL|macro|MP_RAY_TAYLOR_DSP_CODE_SIZE
mdefine_line|#define MP_RAY_TAYLOR_DSP_CODE_SIZE     0x00040000  /* max 256k DSP-Code (Ray Taylor&squot;s code)  */
DECL|macro|MP_ORG_MAX_DSP_CODE_SIZE
mdefine_line|#define MP_ORG_MAX_DSP_CODE_SIZE        0x00060000  /* max 384k DSP-Code (Telindus)           */
DECL|macro|MP_V90D_MAX_DSP_CODE_SIZE
mdefine_line|#define MP_V90D_MAX_DSP_CODE_SIZE       0x00070000  /* max 448k DSP-Code if V.90D included)   */
DECL|macro|MP_VOIP_MAX_DSP_CODE_SIZE
mdefine_line|#define MP_VOIP_MAX_DSP_CODE_SIZE       0x00090000  /* max 576k DSP-Code if voice over IP included */
DECL|macro|MP_CACHED_ADDR
mdefine_line|#define MP_CACHED_ADDR(x)               (((x) &amp; 0x1fffffffL) | 0x80000000L)
DECL|macro|MP_UNCACHED_ADDR
mdefine_line|#define MP_UNCACHED_ADDR(x)             (((x) &amp; 0x1fffffffL) | 0xa0000000L)
DECL|macro|MP_RESET
mdefine_line|#define MP_RESET         0x20        /* offset of RESET register in the DEVICES memory bar */
multiline_comment|/* RESET register bits */
DECL|macro|_MP_S2M_RESET
mdefine_line|#define _MP_S2M_RESET    0x10        /* active lo   */
DECL|macro|_MP_LED2
mdefine_line|#define _MP_LED2         0x08        /* 1 = on      */
DECL|macro|_MP_LED1
mdefine_line|#define _MP_LED1         0x04        /* 1 = on      */
DECL|macro|_MP_DSP_RESET
mdefine_line|#define _MP_DSP_RESET    0x02        /* active lo   */
DECL|macro|_MP_RISC_RESET
mdefine_line|#define _MP_RISC_RESET   0x81        /* active hi, bit 7 for compatibility with old boards */
multiline_comment|/* CPU exception context structure in MP shared ram after trap */
DECL|typedef|MP_XCPTC
r_typedef
r_struct
id|mp_xcptcontext_s
id|MP_XCPTC
suffix:semicolon
DECL|struct|mp_xcptcontext_s
r_struct
id|mp_xcptcontext_s
(brace
DECL|member|sr
id|dword
id|sr
suffix:semicolon
DECL|member|cr
id|dword
id|cr
suffix:semicolon
DECL|member|epc
id|dword
id|epc
suffix:semicolon
DECL|member|vaddr
id|dword
id|vaddr
suffix:semicolon
DECL|member|regs
id|dword
id|regs
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|mdlo
id|dword
id|mdlo
suffix:semicolon
DECL|member|mdhi
id|dword
id|mdhi
suffix:semicolon
DECL|member|reseverd
id|dword
id|reseverd
suffix:semicolon
DECL|member|xclass
id|dword
id|xclass
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* boot interface structure for PRI */
DECL|struct|mp_load
r_struct
id|mp_load
(brace
DECL|member|cmd
id|dword
r_volatile
id|cmd
suffix:semicolon
DECL|member|addr
id|dword
r_volatile
id|addr
suffix:semicolon
DECL|member|len
id|dword
r_volatile
id|len
suffix:semicolon
DECL|member|err
id|dword
r_volatile
id|err
suffix:semicolon
DECL|member|live
id|dword
r_volatile
id|live
suffix:semicolon
DECL|member|res1
id|dword
r_volatile
id|res1
(braket
l_int|0x1b
)braket
suffix:semicolon
DECL|member|TrapId
id|dword
r_volatile
id|TrapId
suffix:semicolon
multiline_comment|/* has value 0x999999XX on a CPU trap */
DECL|member|res2
id|dword
r_volatile
id|res2
(braket
l_int|0x03
)braket
suffix:semicolon
DECL|member|xcpt
id|MP_XCPTC
r_volatile
id|xcpt
suffix:semicolon
multiline_comment|/* contains register dump */
DECL|member|rest
id|dword
r_volatile
id|rest
(braket
(paren
(paren
l_int|0x1020
op_rshift
l_int|2
)paren
op_minus
l_int|6
)paren
op_minus
l_int|0x1b
op_minus
l_int|1
op_minus
l_int|0x03
op_minus
(paren
r_sizeof
(paren
id|MP_XCPTC
)paren
op_rshift
l_int|2
)paren
)braket
suffix:semicolon
DECL|member|signature
id|dword
r_volatile
id|signature
suffix:semicolon
DECL|member|data
id|dword
id|data
(braket
l_int|60000
)braket
suffix:semicolon
multiline_comment|/* real interface description */
)brace
suffix:semicolon
multiline_comment|/*----------------------------------------------------------------------------*/
multiline_comment|/* SERVER 4BRI (Quattro PCI)                                                  */
DECL|macro|MQ_BOARD_REG_OFFSET
mdefine_line|#define MQ_BOARD_REG_OFFSET             0x800000    /* PC relative On board registers offset  */
DECL|macro|MQ_BREG_RISC
mdefine_line|#define MQ_BREG_RISC                    0x1200      /* RISC Reset ect                         */
DECL|macro|MQ_RISC_COLD_RESET_MASK
mdefine_line|#define MQ_RISC_COLD_RESET_MASK         0x0001      /* RISC Cold reset                        */
DECL|macro|MQ_RISC_WARM_RESET_MASK
mdefine_line|#define MQ_RISC_WARM_RESET_MASK         0x0002      /* RISC Warm reset                        */
DECL|macro|MQ_BREG_IRQ_TEST
mdefine_line|#define MQ_BREG_IRQ_TEST                0x0608      /* Interrupt request, no CPU interaction  */
DECL|macro|MQ_IRQ_REQ_ON
mdefine_line|#define MQ_IRQ_REQ_ON                   0x1
DECL|macro|MQ_IRQ_REQ_OFF
mdefine_line|#define MQ_IRQ_REQ_OFF                  0x0
DECL|macro|MQ_BOARD_DSP_OFFSET
mdefine_line|#define MQ_BOARD_DSP_OFFSET             0xa00000    /* PC relative On board DSP regs offset   */
DECL|macro|MQ_DSP1_ADDR_OFFSET
mdefine_line|#define MQ_DSP1_ADDR_OFFSET             0x0008      /* Addr register offset DSP 1 subboard 1  */
DECL|macro|MQ_DSP2_ADDR_OFFSET
mdefine_line|#define MQ_DSP2_ADDR_OFFSET             0x0208      /* Addr register offset DSP 2 subboard 1  */
DECL|macro|MQ_DSP1_DATA_OFFSET
mdefine_line|#define MQ_DSP1_DATA_OFFSET             0x0000      /* Data register offset DSP 1 subboard 1  */
DECL|macro|MQ_DSP2_DATA_OFFSET
mdefine_line|#define MQ_DSP2_DATA_OFFSET             0x0200      /* Data register offset DSP 2 subboard 1  */
DECL|macro|MQ_DSP_JUNK_OFFSET
mdefine_line|#define MQ_DSP_JUNK_OFFSET              0x0400      /* DSP Data/Addr regs subboard offset     */
DECL|macro|MQ_ISAC_DSP_RESET
mdefine_line|#define MQ_ISAC_DSP_RESET               0x0028      /* ISAC and DSP reset address offset      */
DECL|macro|MQ_BOARD_ISAC_DSP_RESET
mdefine_line|#define MQ_BOARD_ISAC_DSP_RESET         0x800028    /* ISAC and DSP reset address offset      */
DECL|macro|MQ_INSTANCE_COUNT
mdefine_line|#define MQ_INSTANCE_COUNT               4           /* 4BRI consists of four instances        */
DECL|macro|MQ_MEMORY_SIZE
mdefine_line|#define MQ_MEMORY_SIZE                  0x00400000  /* 4MB on standard 4BRI                   */
DECL|macro|MQ_CTRL_SIZE
mdefine_line|#define MQ_CTRL_SIZE                    0x00002000  /* 8K memory mapped registers             */
DECL|macro|MQ_SHARED_RAM_SIZE
mdefine_line|#define MQ_SHARED_RAM_SIZE              0x00010000  /* 64k shared RAM                         */
DECL|macro|MQ_ORG_MAX_DSP_CODE_SIZE
mdefine_line|#define MQ_ORG_MAX_DSP_CODE_SIZE        0x00050000  /* max 320k DSP-Code (Telindus) */
DECL|macro|MQ_V90D_MAX_DSP_CODE_SIZE
mdefine_line|#define MQ_V90D_MAX_DSP_CODE_SIZE       0x00060000  /* max 384K DSP-Code if V.90D included */
DECL|macro|MQ_VOIP_MAX_DSP_CODE_SIZE
mdefine_line|#define MQ_VOIP_MAX_DSP_CODE_SIZE       0x00028000  /* max 4*160k = 640K DSP-Code if voice over IP included */
DECL|macro|MQ_CACHED_ADDR
mdefine_line|#define MQ_CACHED_ADDR(x)               (((x) &amp; 0x1fffffffL) | 0x80000000L)
DECL|macro|MQ_UNCACHED_ADDR
mdefine_line|#define MQ_UNCACHED_ADDR(x)             (((x) &amp; 0x1fffffffL) | 0xa0000000L)
multiline_comment|/*--------------------------------------------------------------------------------------------*/
multiline_comment|/* Additional definitions reflecting the different address map of the  SERVER 4BRI V2          */
DECL|macro|MQ2_BREG_RISC
mdefine_line|#define MQ2_BREG_RISC                   0x0200      /* RISC Reset ect                         */
DECL|macro|MQ2_BREG_IRQ_TEST
mdefine_line|#define MQ2_BREG_IRQ_TEST               0x0400      /* Interrupt request, no CPU interaction  */
DECL|macro|MQ2_BOARD_DSP_OFFSET
mdefine_line|#define MQ2_BOARD_DSP_OFFSET            0x800000    /* PC relative On board DSP regs offset   */
DECL|macro|MQ2_DSP1_DATA_OFFSET
mdefine_line|#define MQ2_DSP1_DATA_OFFSET            0x1800      /* Data register offset DSP 1 subboard 1  */
DECL|macro|MQ2_DSP1_ADDR_OFFSET
mdefine_line|#define MQ2_DSP1_ADDR_OFFSET            0x1808      /* Addr register offset DSP 1 subboard 1  */
DECL|macro|MQ2_DSP2_DATA_OFFSET
mdefine_line|#define MQ2_DSP2_DATA_OFFSET            0x1810      /* Data register offset DSP 2 subboard 1  */
DECL|macro|MQ2_DSP2_ADDR_OFFSET
mdefine_line|#define MQ2_DSP2_ADDR_OFFSET            0x1818      /* Addr register offset DSP 2 subboard 1  */
DECL|macro|MQ2_DSP_JUNK_OFFSET
mdefine_line|#define MQ2_DSP_JUNK_OFFSET             0x1000      /* DSP Data/Addr regs subboard offset     */
DECL|macro|MQ2_ISAC_DSP_RESET
mdefine_line|#define MQ2_ISAC_DSP_RESET              0x0000      /* ISAC and DSP reset address offset      */
DECL|macro|MQ2_BOARD_ISAC_DSP_RESET
mdefine_line|#define MQ2_BOARD_ISAC_DSP_RESET        0x800000    /* ISAC and DSP reset address offset      */
DECL|macro|MQ2_IPACX_CONFIG
mdefine_line|#define MQ2_IPACX_CONFIG                0x0300      /* IPACX Configuration TE(0)/NT(1)        */
DECL|macro|MQ2_BOARD_IPACX_CONFIG
mdefine_line|#define MQ2_BOARD_IPACX_CONFIG          0x800300    /*     &quot;&quot;                                 */
DECL|macro|MQ2_MEMORY_SIZE
mdefine_line|#define MQ2_MEMORY_SIZE                 0x01000000  /* 16MB code/data memory                  */
DECL|macro|MQ2_CTRL_SIZE
mdefine_line|#define MQ2_CTRL_SIZE                   0x00008000  /* 32K memory mapped registers            */
multiline_comment|/*----------------------------------------------------------------------------*/
multiline_comment|/* SERVER BRI 2M/2F as derived from 4BRI V2                                   */
DECL|macro|BRI2_MEMORY_SIZE
mdefine_line|#define BRI2_MEMORY_SIZE                0x00800000  /* 8MB code/data memory                   */
DECL|macro|BRI2_PROTOCOL_MEMORY_SIZE
mdefine_line|#define BRI2_PROTOCOL_MEMORY_SIZE       (MQ2_MEMORY_SIZE &gt;&gt; 2) /*  same as one 4BRI Rev.2 task */
DECL|macro|BRI2_CTRL_SIZE
mdefine_line|#define BRI2_CTRL_SIZE                  0x00008000  /* 32K memory mapped registers            */
DECL|macro|M_INSTANCE_COUNT
mdefine_line|#define M_INSTANCE_COUNT                1           /*  BRI consists of one instance          */
multiline_comment|/*&n; * Some useful constants for proper initialization of the GT6401x&n; */
DECL|macro|ID_REG
mdefine_line|#define ID_REG        0x0000      /*Pci reg-contain the Dev&amp;Ven ID of the card*/
DECL|macro|RAS0_BASEREG
mdefine_line|#define RAS0_BASEREG  0x0010      /*Ras0 register - contain the base addr Ras0*/
DECL|macro|RAS2_BASEREG
mdefine_line|#define RAS2_BASEREG  0x0014
DECL|macro|CS_BASEREG
mdefine_line|#define CS_BASEREG    0x0018
DECL|macro|BOOT_BASEREG
mdefine_line|#define BOOT_BASEREG  0x001c
DECL|macro|GTREGS_BASEREG
mdefine_line|#define GTREGS_BASEREG 0x0024   /*GTRegsBase reg-contain the base addr where*/
multiline_comment|/*the GT64010 internal regs where mapped    */
multiline_comment|/*&n; *  GT64010 internal registers&n; */
multiline_comment|/* DRAM device coding  */
DECL|macro|LOW_RAS0_DREG
mdefine_line|#define LOW_RAS0_DREG 0x0400    /*Ras0 low decode address*/
DECL|macro|HI_RAS0_DREG
mdefine_line|#define HI_RAS0_DREG  0x0404    /*Ras0 high decode address*/
DECL|macro|LOW_RAS1_DREG
mdefine_line|#define LOW_RAS1_DREG 0x0408    /*Ras1 low decode address*/
DECL|macro|HI_RAS1_DREG
mdefine_line|#define HI_RAS1_DREG  0x040c    /*Ras1 high decode address*/
DECL|macro|LOW_RAS2_DREG
mdefine_line|#define LOW_RAS2_DREG 0x0410    /*Ras2 low decode address*/
DECL|macro|HI_RAS2_DREG
mdefine_line|#define HI_RAS2_DREG  0x0414    /*Ras2 high decode address*/
DECL|macro|LOW_RAS3_DREG
mdefine_line|#define LOW_RAS3_DREG 0x0418    /*Ras3 low decode address*/
DECL|macro|HI_RAS3_DREG
mdefine_line|#define HI_RAS3_DREG  0x041c    /*Ras3 high decode address*/
multiline_comment|/* I/O CS device coding  */
DECL|macro|LOW_CS0_DREG
mdefine_line|#define LOW_CS0_DREG  0x0420 /* CS0* low decode register */
DECL|macro|HI_CS0_DREG
mdefine_line|#define HI_CS0_DREG   0x0424 /* CS0* high decode register */
DECL|macro|LOW_CS1_DREG
mdefine_line|#define LOW_CS1_DREG  0x0428 /* CS1* low decode register */
DECL|macro|HI_CS1_DREG
mdefine_line|#define HI_CS1_DREG   0x042c /* CS1* high decode register */
DECL|macro|LOW_CS2_DREG
mdefine_line|#define LOW_CS2_DREG  0x0430 /* CS2* low decode register */
DECL|macro|HI_CS2_DREG
mdefine_line|#define HI_CS2_DREG   0x0434 /* CS2* high decode register */
DECL|macro|LOW_CS3_DREG
mdefine_line|#define LOW_CS3_DREG  0x0438 /* CS3* low decode register */
DECL|macro|HI_CS3_DREG
mdefine_line|#define HI_CS3_DREG   0x043c /* CS3* high decode register */
multiline_comment|/* Boot PROM device coding */
DECL|macro|LOW_BOOTCS_DREG
mdefine_line|#define LOW_BOOTCS_DREG 0x0440 /* Boot CS low decode register */
DECL|macro|HI_BOOTCS_DREG
mdefine_line|#define HI_BOOTCS_DREG 0x0444 /* Boot CS High decode register */
multiline_comment|/* DRAM group coding (for CPU)  */
DECL|macro|LO_RAS10_GREG
mdefine_line|#define LO_RAS10_GREG 0x0008    /*Ras1..0 group low decode address*/
DECL|macro|HI_RAS10_GREG
mdefine_line|#define HI_RAS10_GREG 0x0010    /*Ras1..0 group high decode address*/
DECL|macro|LO_RAS32_GREG
mdefine_line|#define LO_RAS32_GREG 0x0018    /*Ras3..2 group low decode address  */
DECL|macro|HI_RAS32_GREG
mdefine_line|#define HI_RAS32_GREG 0x0020    /*Ras3..2 group high decode address  */
multiline_comment|/* I/O CS group coding for (CPU)  */
DECL|macro|LO_CS20_GREG
mdefine_line|#define LO_CS20_GREG  0x0028 /* CS2..0 group low decode register */
DECL|macro|HI_CS20_GREG
mdefine_line|#define HI_CS20_GREG  0x0030 /* CS2..0 group high decode register */
DECL|macro|LO_CS3B_GREG
mdefine_line|#define LO_CS3B_GREG  0x0038 /* CS3 &amp; PROM group low decode register */
DECL|macro|HI_CS3B_GREG
mdefine_line|#define HI_CS3B_GREG  0x0040 /* CS3 &amp; PROM group high decode register */
multiline_comment|/* Galileo specific PCI config. */
DECL|macro|PCI_TIMEOUT_RET
mdefine_line|#define PCI_TIMEOUT_RET 0x0c04 /* Time Out and retry register */
DECL|macro|RAS10_BANKSIZE
mdefine_line|#define RAS10_BANKSIZE 0x0c08 /* RAS 1..0 group PCI bank size */
DECL|macro|RAS32_BANKSIZE
mdefine_line|#define RAS32_BANKSIZE 0x0c0c /* RAS 3..2 group PCI bank size */
DECL|macro|CS20_BANKSIZE
mdefine_line|#define CS20_BANKSIZE 0x0c10 /* CS 2..0 group PCI bank size */
DECL|macro|CS3B_BANKSIZE
mdefine_line|#define CS3B_BANKSIZE 0x0c14 /* CS 3 &amp; Boot group PCI bank size */
DECL|macro|DRAM_SIZE
mdefine_line|#define DRAM_SIZE     0x0001      /*Dram size in mega bytes*/
DECL|macro|PROM_SIZE
mdefine_line|#define PROM_SIZE     0x08000     /*Prom size in bytes*/
multiline_comment|/*--------------------------------------------------------------------------*/
DECL|macro|OFFS_DIVA_INIT_TASK_COUNT
mdefine_line|#define OFFS_DIVA_INIT_TASK_COUNT 0x68
DECL|macro|OFFS_DSP_CODE_BASE_ADDR
mdefine_line|#define OFFS_DSP_CODE_BASE_ADDR   0x6c
DECL|macro|OFFS_XLOG_BUF_ADDR
mdefine_line|#define OFFS_XLOG_BUF_ADDR        0x70
DECL|macro|OFFS_XLOG_COUNT_ADDR
mdefine_line|#define OFFS_XLOG_COUNT_ADDR      0x74
DECL|macro|OFFS_XLOG_OUT_ADDR
mdefine_line|#define OFFS_XLOG_OUT_ADDR        0x78
DECL|macro|OFFS_PROTOCOL_END_ADDR
mdefine_line|#define OFFS_PROTOCOL_END_ADDR    0x7c
DECL|macro|OFFS_PROTOCOL_ID_STRING
mdefine_line|#define OFFS_PROTOCOL_ID_STRING   0x80
multiline_comment|/*--------------------------------------------------------------------------*/
eof
