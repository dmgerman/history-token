multiline_comment|/*----------------------------------------------------------------------------+&n;|       This source code has been made available to you by IBM on an AS-IS&n;|       basis.  Anyone receiving this source is licensed under IBM&n;|       copyrights to use it in any way he or she deems fit, including&n;|       copying it, modifying it, compiling it, and redistributing it either&n;|       with or without modifications.  No license under IBM patents or&n;|       patent applications is to be implied by the copyright license.&n;|&n;|       Any user of this software should understand that IBM cannot provide&n;|       technical support for this software and will not be responsible for&n;|       any consequences resulting from the use of this software.&n;|&n;|       Any person who transfers this source code or any derivative work&n;|       must include the IBM copyright notice, this paragraph, and the&n;|       preceding two paragraphs in the transferred software.&n;|&n;|       COPYRIGHT   I B M   CORPORATION 1997&n;|       LICENSED MATERIAL  -  PROGRAM PROPERTY OF I B M&n;+----------------------------------------------------------------------------*/
multiline_comment|/*----------------------------------------------------------------------------+&n;| Author:    Tony J. Cerreto&n;| Component: Assembler include file.&n;| File:      ppc_40x.h&n;| Purpose:   Include file containing PPC DCR defines.&n;|&n;| Changes:&n;| Date       Author  Comment&n;| ---------  ------  --------------------------------------------------------&n;| 01-Mar-00  tjc     Created&n;+----------------------------------------------------------------------------*/
multiline_comment|/* added by linguohui*/
DECL|macro|MW
mdefine_line|#define MW
multiline_comment|/*----------------------------------------------------------------------------+&n;| PPC Special purpose registers Numbers&n;+----------------------------------------------------------------------------*/
DECL|macro|ccr0
mdefine_line|#define ccr0            0x3b3               /* core configuration reg        */
DECL|macro|ctr
mdefine_line|#define ctr             0x009               /* count register                */
DECL|macro|ctrreg
mdefine_line|#define ctrreg          0x009               /* count register                */
DECL|macro|dbcr0
mdefine_line|#define dbcr0           0x3f2               /* debug control register 0      */
DECL|macro|dbcr1
mdefine_line|#define dbcr1           0x3bd               /* debug control register 1      */
DECL|macro|dbsr
mdefine_line|#define dbsr            0x3f0               /* debug status register         */
DECL|macro|dccr
mdefine_line|#define dccr            0x3fa               /* data cache control reg.       */
DECL|macro|dcwr
mdefine_line|#define dcwr            0x3ba               /* data cache write-thru reg     */
DECL|macro|dear
mdefine_line|#define dear            0x3d5               /* data exeption address reg     */
DECL|macro|esr
mdefine_line|#define esr             0x3d4               /* execption syndrome registe    */
DECL|macro|evpr
mdefine_line|#define evpr            0x3d6               /* exeption vector prefix reg    */
DECL|macro|iccr
mdefine_line|#define iccr            0x3fb               /* instruction cache cntrl re    */
DECL|macro|icdbdr
mdefine_line|#define icdbdr          0x3d3               /* instr cache dbug data reg     */
DECL|macro|lrreg
mdefine_line|#define lrreg           0x008               /* link register                 */
DECL|macro|pid
mdefine_line|#define pid             0x3b1               /* process id reg                */
DECL|macro|pit
mdefine_line|#define pit             0x3db               /* programmable interval time    */
DECL|macro|pvr
mdefine_line|#define pvr             0x11f               /* processor version register    */
DECL|macro|sgr
mdefine_line|#define sgr             0x3b9               /* storage guarded reg           */
DECL|macro|sler
mdefine_line|#define sler            0x3bb               /* storage little endian reg     */
DECL|macro|sprg0
mdefine_line|#define sprg0           0x110               /* special general purpose 0     */
DECL|macro|sprg1
mdefine_line|#define sprg1           0x111               /* special general purpose 1     */
DECL|macro|sprg2
mdefine_line|#define sprg2           0x112               /* special general purpose 2     */
DECL|macro|sprg3
mdefine_line|#define sprg3           0x113               /* special general purpose 3     */
DECL|macro|sprg4
mdefine_line|#define sprg4           0x114               /* special general purpose 4     */
DECL|macro|sprg5
mdefine_line|#define sprg5           0x115               /* special general purpose 5     */
DECL|macro|sprg6
mdefine_line|#define sprg6           0x116               /* special general purpose 6     */
DECL|macro|sprg7
mdefine_line|#define sprg7           0x117               /* special general purpose 7     */
DECL|macro|srr0
mdefine_line|#define srr0            0x01a               /* save/restore register 0       */
DECL|macro|srr1
mdefine_line|#define srr1            0x01b               /* save/restore register 1       */
DECL|macro|srr2
mdefine_line|#define srr2            0x3de               /* save/restore register 2       */
DECL|macro|srr3
mdefine_line|#define srr3            0x3df               /* save/restore register 3       */
DECL|macro|tbhi
mdefine_line|#define tbhi            0x11D
DECL|macro|tblo
mdefine_line|#define tblo            0x11C
DECL|macro|tcr
mdefine_line|#define tcr             0x3da               /* timer control register        */
DECL|macro|tsr
mdefine_line|#define tsr             0x3d8               /* timer status register         */
DECL|macro|xerreg
mdefine_line|#define xerreg          0x001               /* fixed point exception         */
DECL|macro|xer
mdefine_line|#define xer             0x001               /* fixed point exception         */
DECL|macro|zpr
mdefine_line|#define zpr             0x3b0               /* zone protection reg           */
multiline_comment|/*----------------------------------------------------------------------------+&n;| Decompression Controller&n;+----------------------------------------------------------------------------*/
DECL|macro|kiar
mdefine_line|#define kiar            0x014               /* Decompression cntl addr reg   */
DECL|macro|kidr
mdefine_line|#define kidr            0x015               /* Decompression cntl data reg   */
DECL|macro|kitor0
mdefine_line|#define kitor0          0x00                /* index table origin Reg 0      */
DECL|macro|kitor1
mdefine_line|#define kitor1          0x01                /* index table origin Reg 1      */
DECL|macro|kitor2
mdefine_line|#define kitor2          0x02                /* index table origin Reg 2      */
DECL|macro|kitor3
mdefine_line|#define kitor3          0x03                /* index table origin Reg 3      */
DECL|macro|kaddr0
mdefine_line|#define kaddr0          0x04                /* addr decode Definition Reg 0  */
DECL|macro|kaddr1
mdefine_line|#define kaddr1          0x05                /* addr decode Definition Reg 1  */
DECL|macro|kconf
mdefine_line|#define kconf           0x40                /* Decompression cntl config reg */
DECL|macro|kid
mdefine_line|#define kid             0x41                /* Decompression cntl id reg     */
DECL|macro|kver
mdefine_line|#define kver            0x42                /* Decompression cntl ver number */
DECL|macro|kpear
mdefine_line|#define kpear           0x50                /* bus error addr reg (PLB)      */
DECL|macro|kbear
mdefine_line|#define kbear           0x51                /* bus error addr reg (DCP-EBC)  */
DECL|macro|kesr0
mdefine_line|#define kesr0           0x52                /* bus error status reg 0        */
multiline_comment|/*----------------------------------------------------------------------------+&n;| Romeo Specific Device Control Register Numbers.&n;+----------------------------------------------------------------------------*/
macro_line|#ifndef VESTA
DECL|macro|cdbcr
mdefine_line|#define cdbcr           0x3d7                   /* cache debug cntrl reg     */
DECL|macro|a_latcnt
mdefine_line|#define a_latcnt        0x1a9                   /* PLB Latency count         */
DECL|macro|a_tgval
mdefine_line|#define a_tgval         0x1ac                   /* tone generation value     */
DECL|macro|a_plb_pr
mdefine_line|#define a_plb_pr        0x1bf                   /* PLB priority              */
DECL|macro|cic_sel1
mdefine_line|#define cic_sel1        0x031                   /* select register 1         */
DECL|macro|cic_sel2
mdefine_line|#define cic_sel2        0x032                   /* select register 2         */
DECL|macro|clkgcrst
mdefine_line|#define clkgcrst        0x122                   /* chip reset register */
DECL|macro|cp_cpmsr
mdefine_line|#define cp_cpmsr        0x100                   /*rstatus register           */
DECL|macro|cp_cpmer
mdefine_line|#define cp_cpmer        0x101                   /* enable register           */
DECL|macro|dcp_kiar
mdefine_line|#define dcp_kiar        0x190                   /* indirect address register */
DECL|macro|dcp_kidr
mdefine_line|#define dcp_kidr        0x191                   /* indirect data register    */
DECL|macro|hsmc_mcgr
mdefine_line|#define hsmc_mcgr       0x1c0                   /* HSMC global register      */
DECL|macro|hsmc_mcbesr
mdefine_line|#define hsmc_mcbesr     0x1c1                   /* bus error status register */
DECL|macro|hsmc_mcbear
mdefine_line|#define hsmc_mcbear     0x1c2                   /* bus error address register*/
DECL|macro|hsmc_mcbr0
mdefine_line|#define hsmc_mcbr0      0x1c4                   /* SDRAM sub-ctrl bank reg 0 */
DECL|macro|hsmc_mccr0
mdefine_line|#define hsmc_mccr0      0x1c5                   /* SDRAM sub-ctrl ctrl reg 0 */
DECL|macro|hsmc_mcbr1
mdefine_line|#define hsmc_mcbr1      0x1c7                   /* SDRAM sub-ctrl bank reg 1 */
DECL|macro|hsmc_mccr1
mdefine_line|#define hsmc_mccr1      0x1c8                   /* SDRAM sub-ctrl ctrl reg 1 */
DECL|macro|hsmc_sysr
mdefine_line|#define hsmc_sysr       0x1d1                   /* system register           */
DECL|macro|hsmc_data
mdefine_line|#define hsmc_data       0x1d2                   /* data register             */
DECL|macro|hsmc_mccrr
mdefine_line|#define hsmc_mccrr      0x1d3                   /* refresh register          */
DECL|macro|ocm_pbar
mdefine_line|#define ocm_pbar        0x1E0                   /* base address register     */
DECL|macro|plb0_pacr0
mdefine_line|#define plb0_pacr0      0x057                   /* PLB arbiter control reg   */
DECL|macro|plb1_pacr1
mdefine_line|#define plb1_pacr1      0x067                   /* PLB arbiter control reg   */
DECL|macro|v_displb
mdefine_line|#define v_displb        0x157                   /* set left border of display*/
DECL|macro|v_disptb
mdefine_line|#define v_disptb        0x158                   /* top border of display     */
DECL|macro|v_osd_la
mdefine_line|#define v_osd_la        0x159                   /* first link address for OSD*/
DECL|macro|v_ptsdlta
mdefine_line|#define v_ptsdlta       0x15E                   /* PTS delta register        */
DECL|macro|v_v0base
mdefine_line|#define v_v0base        0x16C                   /* base mem add for VBI-0    */
DECL|macro|v_v1base
mdefine_line|#define v_v1base        0x16D                   /* base mem add for VBI-1    */
DECL|macro|v_osbase
mdefine_line|#define v_osbase        0x16E                   /* base mem add for OSD data */
macro_line|#endif
multiline_comment|/*----------------------------------------------------------------------------+&n;| Vesta Device Control Register Numbers.&n;+----------------------------------------------------------------------------*/
multiline_comment|/*----------------------------------------------------------------------------+&n;| Cross bar switch.&n;+----------------------------------------------------------------------------*/
DECL|macro|cbs0_cr
mdefine_line|#define cbs0_cr         0x010               /* CBS configuration register    */
multiline_comment|/*----------------------------------------------------------------------------+&n;| DCR external master (DCRX).&n;+----------------------------------------------------------------------------*/
DECL|macro|dcrx0_icr
mdefine_line|#define dcrx0_icr       0x020               /* internal control register     */
DECL|macro|dcrx0_isr
mdefine_line|#define dcrx0_isr       0x021               /* internal status register      */
DECL|macro|dcrx0_ecr
mdefine_line|#define dcrx0_ecr       0x022               /* external control register     */
DECL|macro|dcrx0_esr
mdefine_line|#define dcrx0_esr       0x023               /* external status register      */
DECL|macro|dcrx0_tar
mdefine_line|#define dcrx0_tar       0x024               /* target address register       */
DECL|macro|dcrx0_tdr
mdefine_line|#define dcrx0_tdr       0x025               /* target data register          */
DECL|macro|dcrx0_igr
mdefine_line|#define dcrx0_igr       0x026               /* interrupt generation register */
DECL|macro|dcrx0_bcr
mdefine_line|#define dcrx0_bcr       0x027               /* buffer control register       */
multiline_comment|/*----------------------------------------------------------------------------+&n;| Chip interconnect configuration.&n;+----------------------------------------------------------------------------*/
DECL|macro|cic0_cr
mdefine_line|#define cic0_cr         0x030               /* CIC control register          */
DECL|macro|cic0_vcr
mdefine_line|#define cic0_vcr        0x033               /* video macro control reg       */
DECL|macro|cic0_sel3
mdefine_line|#define cic0_sel3       0x035               /* select register 3             */
multiline_comment|/*----------------------------------------------------------------------------+&n;| Chip interconnect configuration.&n;+----------------------------------------------------------------------------*/
DECL|macro|sgpo0_sgpO
mdefine_line|#define sgpo0_sgpO      0x036               /* simplified GPIO output        */
DECL|macro|sgpo0_gpod
mdefine_line|#define sgpo0_gpod      0x037               /* simplified GPIO open drain    */
DECL|macro|sgpo0_gptc
mdefine_line|#define sgpo0_gptc      0x038               /* simplified GPIO tristate cntl */
DECL|macro|sgpo0_gpi
mdefine_line|#define sgpo0_gpi       0x039               /* simplified GPIO input         */
multiline_comment|/*----------------------------------------------------------------------------+&n;| Universal interrupt controller.&n;+----------------------------------------------------------------------------*/
DECL|macro|uic0_sr
mdefine_line|#define uic0_sr         0x040               /* status register               */
DECL|macro|uic0_srs
mdefine_line|#define uic0_srs        0x041               /* status register set           */
DECL|macro|uic0_er
mdefine_line|#define uic0_er         0x042               /* enable register               */
DECL|macro|uic0_cr
mdefine_line|#define uic0_cr         0x043               /* critical register             */
DECL|macro|uic0_pr
mdefine_line|#define uic0_pr         0x044               /* parity register               */
DECL|macro|uic0_tr
mdefine_line|#define uic0_tr         0x045               /* triggering register           */
DECL|macro|uic0_msr
mdefine_line|#define uic0_msr        0x046               /* masked status register        */
DECL|macro|uic0_vr
mdefine_line|#define uic0_vr         0x047               /* vector register               */
DECL|macro|uic0_vcr
mdefine_line|#define uic0_vcr        0x048               /* enable config register        */
multiline_comment|/*----------------------------------------------------------------------------+&n;| PLB 0 and 1.&n;+----------------------------------------------------------------------------*/
DECL|macro|pb0_pesr
mdefine_line|#define pb0_pesr        0x054               /* PLB error status reg 0        */
DECL|macro|pb0_pesrs
mdefine_line|#define pb0_pesrs       0x055               /* PLB error status reg 0 set    */
DECL|macro|pb0_pear
mdefine_line|#define pb0_pear        0x056               /* PLB error address reg         */
DECL|macro|pb1_pesr
mdefine_line|#define pb1_pesr        0x064               /* PLB error status reg 1        */
DECL|macro|pb1_pesrs
mdefine_line|#define pb1_pesrs       0x065               /* PLB error status reg 1 set    */
DECL|macro|pb1_pear
mdefine_line|#define pb1_pear        0x066               /* PLB error address reg         */
multiline_comment|/*----------------------------------------------------------------------------+&n;| EBIU DCR registers.&n;+----------------------------------------------------------------------------*/
DECL|macro|ebiu0_brcrh0
mdefine_line|#define ebiu0_brcrh0    0x070               /* bus region register 0 high    */
DECL|macro|ebiu0_brcrh1
mdefine_line|#define ebiu0_brcrh1    0x071               /* bus region register 1 high    */
DECL|macro|ebiu0_brcrh2
mdefine_line|#define ebiu0_brcrh2    0x072               /* bus region register 2 high    */
DECL|macro|ebiu0_brcrh3
mdefine_line|#define ebiu0_brcrh3    0x073               /* bus region register 3 high    */
DECL|macro|ebiu0_brcrh4
mdefine_line|#define ebiu0_brcrh4    0x074               /* bus region register 4 high    */
DECL|macro|ebiu0_brcrh5
mdefine_line|#define ebiu0_brcrh5    0x075               /* bus region register 5 high    */
DECL|macro|ebiu0_brcrh6
mdefine_line|#define ebiu0_brcrh6    0x076               /* bus region register 6 high    */
DECL|macro|ebiu0_brcrh7
mdefine_line|#define ebiu0_brcrh7    0x077               /* bus region register 7 high    */
DECL|macro|ebiu0_brcr0
mdefine_line|#define ebiu0_brcr0     0x080               /* bus region register 0         */
DECL|macro|ebiu0_brcr1
mdefine_line|#define ebiu0_brcr1     0x081               /* bus region register 1         */
DECL|macro|ebiu0_brcr2
mdefine_line|#define ebiu0_brcr2     0x082               /* bus region register 2         */
DECL|macro|ebiu0_brcr3
mdefine_line|#define ebiu0_brcr3     0x083               /* bus region register 3         */
DECL|macro|ebiu0_brcr4
mdefine_line|#define ebiu0_brcr4     0x084               /* bus region register 4         */
DECL|macro|ebiu0_brcr5
mdefine_line|#define ebiu0_brcr5     0x085               /* bus region register 5         */
DECL|macro|ebiu0_brcr6
mdefine_line|#define ebiu0_brcr6     0x086               /* bus region register 6         */
DECL|macro|ebiu0_brcr7
mdefine_line|#define ebiu0_brcr7     0x087               /* bus region register 7         */
DECL|macro|ebiu0_bear
mdefine_line|#define ebiu0_bear      0x090               /* bus error address register    */
DECL|macro|ebiu0_besr
mdefine_line|#define ebiu0_besr      0x091               /* bus error syndrome reg        */
DECL|macro|ebiu0_besr0s
mdefine_line|#define ebiu0_besr0s    0x093               /* bus error syndrome reg        */
DECL|macro|ebiu0_biucr
mdefine_line|#define ebiu0_biucr     0x09a               /* bus interface control reg     */
multiline_comment|/*----------------------------------------------------------------------------+&n;| OPB bridge.&n;+----------------------------------------------------------------------------*/
DECL|macro|opbw0_gesr
mdefine_line|#define opbw0_gesr      0x0b0               /* error status reg              */
DECL|macro|opbw0_gesrs
mdefine_line|#define opbw0_gesrs     0x0b1               /* error status reg              */
DECL|macro|opbw0_gear
mdefine_line|#define opbw0_gear      0x0b2               /* error address reg             */
multiline_comment|/*----------------------------------------------------------------------------+&n;| DMA.&n;+----------------------------------------------------------------------------*/
DECL|macro|dma0_cr0
mdefine_line|#define dma0_cr0        0x0c0               /* DMA channel control reg 0     */
DECL|macro|dma0_ct0
mdefine_line|#define dma0_ct0        0x0c1               /* DMA count register 0          */
DECL|macro|dma0_da0
mdefine_line|#define dma0_da0        0x0c2               /* DMA destination addr reg 0    */
DECL|macro|dma0_sa0
mdefine_line|#define dma0_sa0        0x0c3               /* DMA source addr register 0    */
DECL|macro|dma0_cc0
mdefine_line|#define dma0_cc0        0x0c4               /* DMA chained count 0           */
DECL|macro|dma0_cr1
mdefine_line|#define dma0_cr1        0x0c8               /* DMA channel control reg 1     */
DECL|macro|dma0_ct1
mdefine_line|#define dma0_ct1        0x0c9               /* DMA count register 1          */
DECL|macro|dma0_da1
mdefine_line|#define dma0_da1        0x0ca               /* DMA destination addr reg 1    */
DECL|macro|dma0_sa1
mdefine_line|#define dma0_sa1        0x0cb               /* DMA source addr register 1    */
DECL|macro|dma0_cc1
mdefine_line|#define dma0_cc1        0x0cc               /* DMA chained count 1           */
DECL|macro|dma0_cr2
mdefine_line|#define dma0_cr2        0x0d0               /* DMA channel control reg 2     */
DECL|macro|dma0_ct2
mdefine_line|#define dma0_ct2        0x0d1               /* DMA count register 2          */
DECL|macro|dma0_da2
mdefine_line|#define dma0_da2        0x0d2               /* DMA destination addr reg 2    */
DECL|macro|dma0_sa2
mdefine_line|#define dma0_sa2        0x0d3               /* DMA source addr register 2    */
DECL|macro|dma0_cc2
mdefine_line|#define dma0_cc2        0x0d4               /* DMA chained count 2           */
DECL|macro|dma0_cr3
mdefine_line|#define dma0_cr3        0x0d8               /* DMA channel control reg 3     */
DECL|macro|dma0_ct3
mdefine_line|#define dma0_ct3        0x0d9               /* DMA count register 3          */
DECL|macro|dma0_da3
mdefine_line|#define dma0_da3        0x0da               /* DMA destination addr reg 3    */
DECL|macro|dma0_sa3
mdefine_line|#define dma0_sa3        0x0db               /* DMA source addr register 3    */
DECL|macro|dma0_cc3
mdefine_line|#define dma0_cc3        0x0dc               /* DMA chained count 3           */
DECL|macro|dma0_sr
mdefine_line|#define dma0_sr         0x0e0               /* DMA status register           */
DECL|macro|dma0_srs
mdefine_line|#define dma0_srs        0x0e1               /* DMA status register           */
DECL|macro|dma0_s1
mdefine_line|#define dma0_s1         0x031               /* DMA select1 register          */
DECL|macro|dma0_s2
mdefine_line|#define dma0_s2         0x032               /* DMA select2 register          */
multiline_comment|/*---------------------------------------------------------------------------+&n;| Clock and power management.&n;+----------------------------------------------------------------------------*/
DECL|macro|cpm0_fr
mdefine_line|#define cpm0_fr         0x102               /* force register                */
multiline_comment|/*----------------------------------------------------------------------------+&n;| Serial Clock Control.&n;+----------------------------------------------------------------------------*/
DECL|macro|ser0_ccr
mdefine_line|#define ser0_ccr        0x120               /* serial clock control register */
multiline_comment|/*----------------------------------------------------------------------------+&n;| Audio Clock Control.&n;+----------------------------------------------------------------------------*/
DECL|macro|aud0_apcr
mdefine_line|#define aud0_apcr       0x121               /* audio clock ctrl register     */
multiline_comment|/*----------------------------------------------------------------------------+&n;| DENC.&n;+----------------------------------------------------------------------------*/
DECL|macro|denc0_idr
mdefine_line|#define denc0_idr       0x130               /* DENC ID register              */
DECL|macro|denc0_cr1
mdefine_line|#define denc0_cr1       0x131               /* control register 1            */
DECL|macro|denc0_rr1
mdefine_line|#define denc0_rr1       0x132               /* microvision 1 (reserved 1)    */
DECL|macro|denc0_cr2
mdefine_line|#define denc0_cr2       0x133               /* control register 2            */
DECL|macro|denc0_rr2
mdefine_line|#define denc0_rr2       0x134               /* microvision 2 (reserved 2)    */
DECL|macro|denc0_rr3
mdefine_line|#define denc0_rr3       0x135               /* microvision 3 (reserved 3)    */
DECL|macro|denc0_rr4
mdefine_line|#define denc0_rr4       0x136               /* microvision 4 (reserved 4)    */
DECL|macro|denc0_rr5
mdefine_line|#define denc0_rr5       0x137               /* microvision 5 (reserved 5)    */
DECL|macro|denc0_ccdr
mdefine_line|#define denc0_ccdr      0x138               /* closed caption data           */
DECL|macro|denc0_cccr
mdefine_line|#define denc0_cccr      0x139               /* closed caption control        */
DECL|macro|denc0_trr
mdefine_line|#define denc0_trr       0x13A               /* teletext request register     */
DECL|macro|denc0_tosr
mdefine_line|#define denc0_tosr      0x13B               /* teletext odd field line se    */
DECL|macro|denc0_tesr
mdefine_line|#define denc0_tesr      0x13C               /* teletext even field line s    */
DECL|macro|denc0_rlsr
mdefine_line|#define denc0_rlsr      0x13D               /* RGB rhift left register       */
DECL|macro|denc0_vlsr
mdefine_line|#define denc0_vlsr      0x13E               /* video level shift register    */
DECL|macro|denc0_vsr
mdefine_line|#define denc0_vsr       0x13F               /* video scaling register        */
multiline_comment|/*----------------------------------------------------------------------------+&n;| Video decoder.  Suspect 0x179, 0x169, 0x16a, 0x152 (rc).&n;+----------------------------------------------------------------------------*/
DECL|macro|vid0_ccntl
mdefine_line|#define vid0_ccntl      0x140               /* control decoder operation     */
DECL|macro|vid0_cmode
mdefine_line|#define vid0_cmode      0x141               /* video operational mode        */
DECL|macro|vid0_sstc0
mdefine_line|#define vid0_sstc0      0x142               /* STC high order bits 31:0      */
DECL|macro|vid0_sstc1
mdefine_line|#define vid0_sstc1      0x143               /* STC low order bit 32          */
DECL|macro|vid0_spts0
mdefine_line|#define vid0_spts0      0x144               /* PTS high order bits 31:0      */
DECL|macro|vid0_spts1
mdefine_line|#define vid0_spts1      0x145               /* PTS low order bit 32          */
DECL|macro|vid0_fifo
mdefine_line|#define vid0_fifo       0x146               /* FIFO data port                */
DECL|macro|vid0_fifos
mdefine_line|#define vid0_fifos      0x147               /* FIFO status                   */
DECL|macro|vid0_cmd
mdefine_line|#define vid0_cmd        0x148               /* send command to decoder       */
DECL|macro|vid0_cmdd
mdefine_line|#define vid0_cmdd       0x149               /* port for command params       */
DECL|macro|vid0_cmdst
mdefine_line|#define vid0_cmdst      0x14A               /* command status                */
DECL|macro|vid0_cmdad
mdefine_line|#define vid0_cmdad      0x14B               /* command address               */
DECL|macro|vid0_procia
mdefine_line|#define vid0_procia     0x14C               /* instruction store             */
DECL|macro|vid0_procid
mdefine_line|#define vid0_procid     0x14D               /* data port for I_Store         */
DECL|macro|vid0_osdm
mdefine_line|#define vid0_osdm       0x151               /* OSD mode control              */
DECL|macro|vid0_hosti
mdefine_line|#define vid0_hosti      0x152               /* base interrupt register       */
DECL|macro|vid0_mask
mdefine_line|#define vid0_mask       0x153               /* interrupt mask register       */
DECL|macro|vid0_dispm
mdefine_line|#define vid0_dispm      0x154               /* operational mode for Disp     */
DECL|macro|vid0_dispd
mdefine_line|#define vid0_dispd      0x155               /* setting for &squot;Sync&squot; delay      */
DECL|macro|vid0_vbctl
mdefine_line|#define vid0_vbctl      0x156               /* VBI                           */
DECL|macro|vid0_ttxctl
mdefine_line|#define vid0_ttxctl     0x157               /* teletext control              */
DECL|macro|vid0_disptb
mdefine_line|#define vid0_disptb     0x158               /* display left/top border       */
DECL|macro|vid0_osdgla
mdefine_line|#define vid0_osdgla     0x159               /* Graphics plane link addr      */
DECL|macro|vid0_osdila
mdefine_line|#define vid0_osdila     0x15A               /* Image plane link addr         */
DECL|macro|vid0_rbthr
mdefine_line|#define vid0_rbthr      0x15B               /* rate buffer threshold         */
DECL|macro|vid0_osdcla
mdefine_line|#define vid0_osdcla     0x15C               /* Cursor link addr              */
DECL|macro|vid0_stcca
mdefine_line|#define vid0_stcca      0x15D               /* STC common address            */
DECL|macro|vid0_ptsctl
mdefine_line|#define vid0_ptsctl     0x15F               /* PTS Control                   */
DECL|macro|vid0_wprot
mdefine_line|#define vid0_wprot      0x165               /* write protect for I_Store     */
DECL|macro|vid0_vcqa
mdefine_line|#define vid0_vcqa       0x167               /* video clip queued block Ad    */
DECL|macro|vid0_vcql
mdefine_line|#define vid0_vcql       0x168               /* video clip queued block Le    */
DECL|macro|vid0_blksz
mdefine_line|#define vid0_blksz      0x169               /* block size bytes for copy op  */
DECL|macro|vid0_srcad
mdefine_line|#define vid0_srcad      0x16a               /* copy source address bits 6-31 */
DECL|macro|vid0_udbas
mdefine_line|#define vid0_udbas      0x16B               /* base mem add for user data    */
DECL|macro|vid0_vbibas
mdefine_line|#define vid0_vbibas     0x16C               /* base mem add for VBI 0/1      */
DECL|macro|vid0_osdibas
mdefine_line|#define vid0_osdibas    0x16D               /* Image plane base address      */
DECL|macro|vid0_osdgbas
mdefine_line|#define vid0_osdgbas    0x16E               /* Graphic plane base address    */
DECL|macro|vid0_rbbase
mdefine_line|#define vid0_rbbase     0x16F               /* base mem add for video buf    */
DECL|macro|vid0_dramad
mdefine_line|#define vid0_dramad     0x170               /* DRAM address                  */
DECL|macro|vid0_dramdt
mdefine_line|#define vid0_dramdt     0x171               /* data port for DRAM access     */
DECL|macro|vid0_dramcs
mdefine_line|#define vid0_dramcs     0x172               /* DRAM command and statusa      */
DECL|macro|vid0_vcwa
mdefine_line|#define vid0_vcwa       0x173               /* v clip work address           */
DECL|macro|vid0_vcwl
mdefine_line|#define vid0_vcwl       0x174               /* v clip work length            */
DECL|macro|vid0_mseg0
mdefine_line|#define vid0_mseg0      0x175               /* segment address 0             */
DECL|macro|vid0_mseg1
mdefine_line|#define vid0_mseg1      0x176               /* segment address 1             */
DECL|macro|vid0_mseg2
mdefine_line|#define vid0_mseg2      0x177               /* segment address 2             */
DECL|macro|vid0_mseg3
mdefine_line|#define vid0_mseg3      0x178               /* segment address 3             */
DECL|macro|vid0_fbbase
mdefine_line|#define vid0_fbbase     0x179               /* frame buffer base memory      */
DECL|macro|vid0_osdcbas
mdefine_line|#define vid0_osdcbas    0x17A               /* Cursor base addr              */
DECL|macro|vid0_lboxtb
mdefine_line|#define vid0_lboxtb     0x17B               /* top left border               */
DECL|macro|vid0_trdly
mdefine_line|#define vid0_trdly      0x17C               /* transparency gate delay       */
DECL|macro|vid0_sbord
mdefine_line|#define vid0_sbord      0x17D               /* left/top small pict. bord.    */
DECL|macro|vid0_zoffs
mdefine_line|#define vid0_zoffs      0x17E               /* hor/ver zoom window           */
DECL|macro|vid0_rbsz
mdefine_line|#define vid0_rbsz       0x17F               /* rate buffer size read         */
multiline_comment|/*----------------------------------------------------------------------------+&n;| Transport demultiplexer.&n;+----------------------------------------------------------------------------*/
DECL|macro|xpt0_lr
mdefine_line|#define xpt0_lr         0x180               /* demux location register       */
DECL|macro|xpt0_data
mdefine_line|#define xpt0_data       0x181               /* demux data register           */
DECL|macro|xpt0_ir
mdefine_line|#define xpt0_ir         0x182               /* demux interrupt register      */
DECL|macro|xpt0_config1
mdefine_line|#define xpt0_config1    0x0000              /* configuration 1               */
DECL|macro|xpt0_control1
mdefine_line|#define xpt0_control1   0x0001              /* control 1                     */
DECL|macro|xpt0_festat
mdefine_line|#define xpt0_festat     0x0002              /* Front-end status              */
DECL|macro|xpt0_feimask
mdefine_line|#define xpt0_feimask    0x0003              /* Front_end interrupt Mask      */
DECL|macro|xpt0_ocmcnfg
mdefine_line|#define xpt0_ocmcnfg    0x0004              /* OCM Address                   */
DECL|macro|xpt0_settapi
mdefine_line|#define xpt0_settapi    0x0005              /* Set TAP Interrupt             */
DECL|macro|xpt0_pcrhi
mdefine_line|#define xpt0_pcrhi      0x0010              /* PCR High                      */
DECL|macro|xpt0_pcrlow
mdefine_line|#define xpt0_pcrlow     0x0011              /* PCR Low                       */
DECL|macro|xpt0_lstchi
mdefine_line|#define xpt0_lstchi     0x0012              /* Latched STC High              */
DECL|macro|xpt0_lstclow
mdefine_line|#define xpt0_lstclow    0x0013              /* Latched STC Low               */
DECL|macro|xpt0_stchi
mdefine_line|#define xpt0_stchi      0x0014              /* STC High                      */
DECL|macro|xpt0_stclow
mdefine_line|#define xpt0_stclow     0x0015              /* STC Low                       */
DECL|macro|xpt0_pwm
mdefine_line|#define xpt0_pwm        0x0016              /* PWM                           */
DECL|macro|xpt0_pcrstct
mdefine_line|#define xpt0_pcrstct    0x0017              /* PCR-STC Threshold             */
DECL|macro|xpt0_pcrstcd
mdefine_line|#define xpt0_pcrstcd    0x0018              /* PCR-STC Delta                 */
DECL|macro|xpt0_stccomp
mdefine_line|#define xpt0_stccomp    0x0019              /* STC Compare                   */
DECL|macro|xpt0_stccmpd
mdefine_line|#define xpt0_stccmpd    0x001a              /* STC Compare Disarm            */
DECL|macro|xpt0_dsstat
mdefine_line|#define xpt0_dsstat     0x0048              /* Descrambler Status            */
DECL|macro|xpt0_dsimask
mdefine_line|#define xpt0_dsimask    0x0049              /* Descrambler Interrupt Mask    */
DECL|macro|xpt0_vcchng
mdefine_line|#define xpt0_vcchng     0x01f0              /* Video Channel Change          */
DECL|macro|xpt0_acchng
mdefine_line|#define xpt0_acchng     0x01f1              /* Audio Channel Change          */
DECL|macro|xpt0_axenable
mdefine_line|#define xpt0_axenable   0x01fe              /* Aux PID Enables               */
DECL|macro|xpt0_pcrpid
mdefine_line|#define xpt0_pcrpid     0x01ff              /* PCR PID                       */
DECL|macro|xpt0_config2
mdefine_line|#define xpt0_config2    0x1000              /* Configuration 2               */
DECL|macro|xpt0_pbuflvl
mdefine_line|#define xpt0_pbuflvl    0x1002              /* Packet Buffer Level           */
DECL|macro|xpt0_intmask
mdefine_line|#define xpt0_intmask    0x1003              /* Interrupt Mask                */
DECL|macro|xpt0_plbcnfg
mdefine_line|#define xpt0_plbcnfg    0x1004              /* PLB Configuration             */
DECL|macro|xpt0_qint
mdefine_line|#define xpt0_qint       0x1010              /* Queues Interrupts             */
DECL|macro|xpt0_qintmsk
mdefine_line|#define xpt0_qintmsk    0x1011              /* Queues Interrupts Mask        */
DECL|macro|xpt0_astatus
mdefine_line|#define xpt0_astatus    0x1012              /* Audio Status                  */
DECL|macro|xpt0_aintmask
mdefine_line|#define xpt0_aintmask   0x1013              /* Audio Interrupt Mask          */
DECL|macro|xpt0_vstatus
mdefine_line|#define xpt0_vstatus    0x1014              /* Video Status                  */
DECL|macro|xpt0_vintmask
mdefine_line|#define xpt0_vintmask   0x1015              /* Video Interrupt Mask          */
DECL|macro|xpt0_qbase
mdefine_line|#define xpt0_qbase      0x1020              /* Queue Base                    */
DECL|macro|xpt0_bucketq
mdefine_line|#define xpt0_bucketq    0x1021              /* Bucket Queue                  */
DECL|macro|xpt0_qstops
mdefine_line|#define xpt0_qstops     0x1024              /* Queue Stops                   */
DECL|macro|xpt0_qresets
mdefine_line|#define xpt0_qresets    0x1025              /* Queue Resets                  */
DECL|macro|xpt0_sfchng
mdefine_line|#define xpt0_sfchng     0x1026              /* Section Filter Change         */
multiline_comment|/*----------------------------------------------------------------------------+&n;| Audio decoder. Suspect 0x1ad, 0x1b4, 0x1a3, 0x1a5 (read/write status)&n;+----------------------------------------------------------------------------*/
DECL|macro|aud0_ctrl0
mdefine_line|#define aud0_ctrl0      0x1a0               /* control 0                     */
DECL|macro|aud0_ctrl1
mdefine_line|#define aud0_ctrl1      0x1a1               /* control 1                     */
DECL|macro|aud0_ctrl2
mdefine_line|#define aud0_ctrl2      0x1a2               /* control 2                     */
DECL|macro|aud0_cmd
mdefine_line|#define aud0_cmd        0x1a3               /* command register              */
DECL|macro|aud0_isr
mdefine_line|#define aud0_isr        0x1a4               /* interrupt status register     */
DECL|macro|aud0_imr
mdefine_line|#define aud0_imr        0x1a5               /* interrupt mask register       */
DECL|macro|aud0_dsr
mdefine_line|#define aud0_dsr        0x1a6               /* decoder status register       */
DECL|macro|aud0_stc
mdefine_line|#define aud0_stc        0x1a7               /* system time clock             */
DECL|macro|aud0_csr
mdefine_line|#define aud0_csr        0x1a8               /* channel status register       */
DECL|macro|aud0_lcnt
mdefine_line|#define aud0_lcnt       0x1a9               /* queued address register 2     */
DECL|macro|aud0_pts
mdefine_line|#define aud0_pts        0x1aa               /* presentation time stamp       */
DECL|macro|aud0_tgctrl
mdefine_line|#define aud0_tgctrl     0x1ab               /* tone generation control       */
DECL|macro|aud0_qlr2
mdefine_line|#define aud0_qlr2       0x1ac               /* queued length register 2      */
DECL|macro|aud0_auxd
mdefine_line|#define aud0_auxd       0x1ad               /* aux data                      */
DECL|macro|aud0_strmid
mdefine_line|#define aud0_strmid     0x1ae               /* stream ID                     */
DECL|macro|aud0_qar
mdefine_line|#define aud0_qar        0x1af               /* queued address register       */
DECL|macro|aud0_dsps
mdefine_line|#define aud0_dsps       0x1b0               /* DSP status                    */
DECL|macro|aud0_qlr
mdefine_line|#define aud0_qlr        0x1b1               /* queued len address            */
DECL|macro|aud0_dspc
mdefine_line|#define aud0_dspc       0x1b2               /* DSP control                   */
DECL|macro|aud0_wlr2
mdefine_line|#define aud0_wlr2       0x1b3               /* working length register 2     */
DECL|macro|aud0_instd
mdefine_line|#define aud0_instd      0x1b4               /* instruction download          */
DECL|macro|aud0_war
mdefine_line|#define aud0_war        0x1b5               /* working address register      */
DECL|macro|aud0_seg1
mdefine_line|#define aud0_seg1       0x1b6               /* segment 1 base register       */
DECL|macro|aud0_seg2
mdefine_line|#define aud0_seg2       0x1b7               /* segment 2 base register       */
DECL|macro|aud0_avf
mdefine_line|#define aud0_avf        0x1b9               /* audio att value front         */
DECL|macro|aud0_avr
mdefine_line|#define aud0_avr        0x1ba               /* audio att value rear          */
DECL|macro|aud0_avc
mdefine_line|#define aud0_avc        0x1bb               /* audio att value center        */
DECL|macro|aud0_seg3
mdefine_line|#define aud0_seg3       0x1bc               /* segment 3 base register       */
DECL|macro|aud0_offset
mdefine_line|#define aud0_offset     0x1bd               /* offset address                */
DECL|macro|aud0_wrl
mdefine_line|#define aud0_wrl        0x1be               /* working length register       */
DECL|macro|aud0_war2
mdefine_line|#define aud0_war2       0x1bf               /* working address register 2    */
multiline_comment|/*----------------------------------------------------------------------------+&n;| High speed memory controller 0 and 1.&n;+----------------------------------------------------------------------------*/
DECL|macro|hsmc0_gr
mdefine_line|#define hsmc0_gr        0x1e0               /* HSMC global register          */
DECL|macro|hsmc0_besr
mdefine_line|#define hsmc0_besr      0x1e1               /* bus error status register     */
DECL|macro|hsmc0_bear
mdefine_line|#define hsmc0_bear      0x1e2               /* bus error address register    */
DECL|macro|hsmc0_br0
mdefine_line|#define hsmc0_br0       0x1e4               /* SDRAM sub-ctrl bank reg 0     */
DECL|macro|hsmc0_cr0
mdefine_line|#define hsmc0_cr0       0x1e5               /* SDRAM sub-ctrl ctrl reg 0     */
DECL|macro|hsmc0_br1
mdefine_line|#define hsmc0_br1       0x1e7               /* SDRAM sub-ctrl bank reg 1     */
DECL|macro|hsmc0_cr1
mdefine_line|#define hsmc0_cr1       0x1e8               /* SDRAM sub-ctrl ctrl reg 1     */
DECL|macro|hsmc0_sysr
mdefine_line|#define hsmc0_sysr      0x1f1               /* system register               */
DECL|macro|hsmc0_data
mdefine_line|#define hsmc0_data      0x1f2               /* data register                 */
DECL|macro|hsmc0_crr
mdefine_line|#define hsmc0_crr       0x1f3               /* refresh register              */
DECL|macro|hsmc1_gr
mdefine_line|#define hsmc1_gr        0x1c0               /* HSMC global register          */
DECL|macro|hsmc1_besr
mdefine_line|#define hsmc1_besr      0x1c1               /* bus error status register     */
DECL|macro|hsmc1_bear
mdefine_line|#define hsmc1_bear      0x1c2               /* bus error address register    */
DECL|macro|hsmc1_br0
mdefine_line|#define hsmc1_br0       0x1c4               /* SDRAM sub-ctrl bank reg 0     */
DECL|macro|hsmc1_cr0
mdefine_line|#define hsmc1_cr0       0x1c5               /* SDRAM sub-ctrl ctrl reg 0     */
DECL|macro|hsmc1_br1
mdefine_line|#define hsmc1_br1       0x1c7               /* SDRAM sub-ctrl bank reg 1     */
DECL|macro|hsmc1_cr1
mdefine_line|#define hsmc1_cr1       0x1c8               /* SDRAM sub-ctrl ctrl reg 1     */
DECL|macro|hsmc1_sysr
mdefine_line|#define hsmc1_sysr      0x1d1               /* system register               */
DECL|macro|hsmc1_data
mdefine_line|#define hsmc1_data      0x1d2               /* data register                 */
DECL|macro|hsmc1_crr
mdefine_line|#define hsmc1_crr       0x1d3               /* refresh register              */
multiline_comment|/*----------------------------------------------------------------------------+&n;| Machine State Register bit definitions.&n;+----------------------------------------------------------------------------*/
DECL|macro|msr_ape
mdefine_line|#define msr_ape         0x00100000
DECL|macro|msr_apa
mdefine_line|#define msr_apa         0x00080000
DECL|macro|msr_we
mdefine_line|#define msr_we          0x00040000
DECL|macro|msr_ce
mdefine_line|#define msr_ce          0x00020000
DECL|macro|msr_ile
mdefine_line|#define msr_ile         0x00010000
DECL|macro|msr_ee
mdefine_line|#define msr_ee          0x00008000
DECL|macro|msr_pr
mdefine_line|#define msr_pr          0x00004000
DECL|macro|msr_me
mdefine_line|#define msr_me          0x00001000
DECL|macro|msr_de
mdefine_line|#define msr_de          0x00000200
DECL|macro|msr_ir
mdefine_line|#define msr_ir          0x00000020
DECL|macro|msr_dr
mdefine_line|#define msr_dr          0x00000010
DECL|macro|msr_le
mdefine_line|#define msr_le          0x00000001
multiline_comment|/*----------------------------------------------------------------------------+&n;| Used during interrupt processing.&n;+----------------------------------------------------------------------------*/
DECL|macro|stack_reg_image_size
mdefine_line|#define stack_reg_image_size            160
multiline_comment|/*----------------------------------------------------------------------------+&n;| Function prolog definition and other Metaware (EABI) defines.&n;+----------------------------------------------------------------------------*/
macro_line|#ifdef MW
DECL|macro|r0
mdefine_line|#define r0              0
DECL|macro|r1
mdefine_line|#define r1              1
DECL|macro|r2
mdefine_line|#define r2              2
DECL|macro|r3
mdefine_line|#define r3              3
DECL|macro|r4
mdefine_line|#define r4              4
DECL|macro|r5
mdefine_line|#define r5              5
DECL|macro|r6
mdefine_line|#define r6              6
DECL|macro|r7
mdefine_line|#define r7              7
DECL|macro|r8
mdefine_line|#define r8              8
DECL|macro|r9
mdefine_line|#define r9              9
DECL|macro|r10
mdefine_line|#define r10             10
DECL|macro|r11
mdefine_line|#define r11             11
DECL|macro|r12
mdefine_line|#define r12             12
DECL|macro|r13
mdefine_line|#define r13             13
DECL|macro|r14
mdefine_line|#define r14             14
DECL|macro|r15
mdefine_line|#define r15             15
DECL|macro|r16
mdefine_line|#define r16             16
DECL|macro|r17
mdefine_line|#define r17             17
DECL|macro|r18
mdefine_line|#define r18             18
DECL|macro|r19
mdefine_line|#define r19             19
DECL|macro|r20
mdefine_line|#define r20             20
DECL|macro|r21
mdefine_line|#define r21             21
DECL|macro|r22
mdefine_line|#define r22             22
DECL|macro|r23
mdefine_line|#define r23             23
DECL|macro|r24
mdefine_line|#define r24             24
DECL|macro|r25
mdefine_line|#define r25             25
DECL|macro|r26
mdefine_line|#define r26             26
DECL|macro|r27
mdefine_line|#define r27             27
DECL|macro|r28
mdefine_line|#define r28             28
DECL|macro|r29
mdefine_line|#define r29             29
DECL|macro|r30
mdefine_line|#define r30             30
DECL|macro|r31
mdefine_line|#define r31             31
DECL|macro|cr0
mdefine_line|#define cr0             0
DECL|macro|cr1
mdefine_line|#define cr1             1
DECL|macro|cr2
mdefine_line|#define cr2             2
DECL|macro|cr3
mdefine_line|#define cr3             3
DECL|macro|cr4
mdefine_line|#define cr4             4
DECL|macro|cr5
mdefine_line|#define cr5             5
DECL|macro|cr6
mdefine_line|#define cr6             6
DECL|macro|cr7
mdefine_line|#define cr7             7
DECL|macro|function_prolog
mdefine_line|#define function_prolog(func_name)      .text; &bslash;&n;                                        .align  2; &bslash;&n;                                        .globl  func_name; &bslash;&n;                                        func_name:
DECL|macro|function_epilog
mdefine_line|#define function_epilog(func_name)      .type func_name,@function; &bslash;&n;                                        .size func_name,.-func_name
DECL|macro|function_call
mdefine_line|#define function_call(func_name)        bl func_name
DECL|macro|stack_frame_min
mdefine_line|#define stack_frame_min                 8
DECL|macro|stack_frame_bc
mdefine_line|#define stack_frame_bc                  0
DECL|macro|stack_frame_lr
mdefine_line|#define stack_frame_lr                  4
DECL|macro|stack_neg_off
mdefine_line|#define stack_neg_off                   0
macro_line|#endif
multiline_comment|/*----------------------------------------------------------------------------+&n;| Function prolog definition and other DIAB (Elf) defines.&n;+----------------------------------------------------------------------------*/
macro_line|#ifdef ELF_DIAB
id|fprolog
suffix:colon
id|macro
id|f_name
dot
id|text
dot
id|align
l_int|2
dot
id|globl
id|f_name
id|f_name
suffix:colon
id|endm
id|fepilog
suffix:colon
id|macro
id|f_name
dot
id|type
id|f_name
comma
"@"
id|function
dot
id|size
id|f_name
comma
dot
op_minus
id|f_name
id|endm
DECL|macro|function_prolog
mdefine_line|#define function_prolog(func_name)      fprolog func_name
DECL|macro|function_epilog
mdefine_line|#define function_epilog(func_name)      fepilog func_name
DECL|macro|function_call
mdefine_line|#define function_call(func_name)        bl func_name
DECL|macro|stack_frame_min
mdefine_line|#define stack_frame_min                 8
DECL|macro|stack_frame_bc
mdefine_line|#define stack_frame_bc                  0
DECL|macro|stack_frame_lr
mdefine_line|#define stack_frame_lr                  4
DECL|macro|stack_neg_off
mdefine_line|#define stack_neg_off                   0
macro_line|#endif
multiline_comment|/*----------------------------------------------------------------------------+&n;| Function prolog definition and other Xlc (XCOFF) defines.&n;+----------------------------------------------------------------------------*/
macro_line|#ifdef XCOFF
dot
id|machine
l_string|&quot;403ga&quot;
DECL|macro|r0
mdefine_line|#define r0              0
DECL|macro|r1
mdefine_line|#define r1              1
DECL|macro|r2
mdefine_line|#define r2              2
DECL|macro|r3
mdefine_line|#define r3              3
DECL|macro|r4
mdefine_line|#define r4              4
DECL|macro|r5
mdefine_line|#define r5              5
DECL|macro|r6
mdefine_line|#define r6              6
DECL|macro|r7
mdefine_line|#define r7              7
DECL|macro|r8
mdefine_line|#define r8              8
DECL|macro|r9
mdefine_line|#define r9              9
DECL|macro|r10
mdefine_line|#define r10             10
DECL|macro|r11
mdefine_line|#define r11             11
DECL|macro|r12
mdefine_line|#define r12             12
DECL|macro|r13
mdefine_line|#define r13             13
DECL|macro|r14
mdefine_line|#define r14             14
DECL|macro|r15
mdefine_line|#define r15             15
DECL|macro|r16
mdefine_line|#define r16             16
DECL|macro|r17
mdefine_line|#define r17             17
DECL|macro|r18
mdefine_line|#define r18             18
DECL|macro|r19
mdefine_line|#define r19             19
DECL|macro|r20
mdefine_line|#define r20             20
DECL|macro|r21
mdefine_line|#define r21             21
DECL|macro|r22
mdefine_line|#define r22             22
DECL|macro|r23
mdefine_line|#define r23             23
DECL|macro|r24
mdefine_line|#define r24             24
DECL|macro|r25
mdefine_line|#define r25             25
DECL|macro|r26
mdefine_line|#define r26             26
DECL|macro|r27
mdefine_line|#define r27             27
DECL|macro|r28
mdefine_line|#define r28             28
DECL|macro|r29
mdefine_line|#define r29             29
DECL|macro|r30
mdefine_line|#define r30             30
DECL|macro|r31
mdefine_line|#define r31             31
DECL|macro|cr0
mdefine_line|#define cr0             0
DECL|macro|cr1
mdefine_line|#define cr1             1
DECL|macro|cr2
mdefine_line|#define cr2             2
DECL|macro|cr3
mdefine_line|#define cr3             3
DECL|macro|cr4
mdefine_line|#define cr4             4
DECL|macro|cr5
mdefine_line|#define cr5             5
DECL|macro|cr6
mdefine_line|#define cr6             6
DECL|macro|cr7
mdefine_line|#define cr7             7
DECL|macro|function_prolog
mdefine_line|#define function_prolog(func_name)      .csect .func_name[PR]; &bslash;&n;                                        .globl .func_name[PR]; &bslash;&n;                                        func_name:
DECL|macro|function_epilog
mdefine_line|#define function_epilog(func_name)      .toc; &bslash;&n;                                        .csect  func_name[DS]; &bslash;&n;                                        .globl  func_name[DS]; &bslash;&n;                                        .long   .func_name[PR]; &bslash;&n;                                        .long   TOC[tc0]
DECL|macro|function_call
mdefine_line|#define function_call(func_name)        .extern .func_name[PR]; &bslash;&n;                                        stw     r2,stack_frame_toc(r1); &bslash;&n;                                        mfspr   r2,sprg0; &bslash;&n;                                        bl      .func_name[PR]; &bslash;&n;                                        lwz     r2,stack_frame_toc(r1)
DECL|macro|stack_frame_min
mdefine_line|#define stack_frame_min                 56
DECL|macro|stack_frame_bc
mdefine_line|#define stack_frame_bc                  0
DECL|macro|stack_frame_lr
mdefine_line|#define stack_frame_lr                  8
DECL|macro|stack_frame_toc
mdefine_line|#define stack_frame_toc                 20
DECL|macro|stack_neg_off
mdefine_line|#define stack_neg_off                   276
macro_line|#endif
DECL|macro|function_prolog
mdefine_line|#define function_prolog(func_name)      .text; &bslash;&n;                                        .align  2; &bslash;&n;                                        .globl  func_name; &bslash;&n;                                        func_name:
DECL|macro|function_epilog
mdefine_line|#define function_epilog(func_name)      .type func_name,@function; &bslash;&n;                                        .size func_name,.-func_name
DECL|macro|function_call
mdefine_line|#define function_call(func_name)        bl func_name
multiline_comment|/*----------------------------------------------------------------------------+&n;| Function prolog definition for GNU&n;+----------------------------------------------------------------------------*/
macro_line|#ifdef _GNU_TOOL
DECL|macro|function_prolog
mdefine_line|#define function_prolog(func_name)      .globl  func_name; &bslash;&n;                                        func_name:
DECL|macro|function_epilog
mdefine_line|#define function_epilog(func_name)
macro_line|#endif
eof
