multiline_comment|/*&n; * Author: MontaVista Software, Inc.&n; *         source@mvista.com&n; *&n; * Copyright 2001-2002 MontaVista Software Inc.&n; *&n; *  This program is free software; you can redistribute it and/or modify it&n; *  under the terms of the GNU General Public License as published by the&n; *  Free Software Foundation; either version 2 of the License, or (at your&n; *  option) any later version.&n; *&n; *  THIS SOFTWARE IS PROVIDED ``AS IS&squot;&squot; AND ANY EXPRESS OR IMPLIED&n; *  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.&n; *  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,&n; *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS&n; *  OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND&n; *  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR&n; *  TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE&n; *  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef __ASM_TX4927_TX4927_H
DECL|macro|__ASM_TX4927_TX4927_H
mdefine_line|#define __ASM_TX4927_TX4927_H
macro_line|#include &lt;asm/tx4927/tx4927_mips.h&gt;
multiline_comment|/*&n; This register naming came from the intergrate cpu/controoler name TX4927&n; followed by the device name from table 4.2.2 on page 4-3 and then followed&n; by the register name from table 4.2.3 on pages 4-4 to 4-8.  The manaul&n; used is &quot;TMPR4927BT Preliminary Rev 0.1 20.Jul.2001&quot;.&n; */
DECL|macro|TX4927_SIO_0_BASE
mdefine_line|#define TX4927_SIO_0_BASE
multiline_comment|/* TX4927 controller */
DECL|macro|TX4927_BASE
mdefine_line|#define TX4927_BASE                     0xfff1f0000
DECL|macro|TX4927_BASE
mdefine_line|#define TX4927_BASE                     0xfff1f0000
DECL|macro|TX4927_LIMIT
mdefine_line|#define TX4927_LIMIT                    0xfff1fffff
multiline_comment|/* TX4927 SDRAM controller (64-bit registers) */
DECL|macro|TX4927_SDRAMC_BASE
mdefine_line|#define TX4927_SDRAMC_BASE              0x8000 
DECL|macro|TX4927_SDRAMC_SDCCR0
mdefine_line|#define TX4927_SDRAMC_SDCCR0            0x8000 
DECL|macro|TX4927_SDRAMC_SDCCR1
mdefine_line|#define TX4927_SDRAMC_SDCCR1            0x8008
DECL|macro|TX4927_SDRAMC_SDCCR2
mdefine_line|#define TX4927_SDRAMC_SDCCR2            0x8010
DECL|macro|TX4927_SDRAMC_SDCCR3
mdefine_line|#define TX4927_SDRAMC_SDCCR3            0x8018
DECL|macro|TX4927_SDRAMC_SDCTR
mdefine_line|#define TX4927_SDRAMC_SDCTR             0x8040
DECL|macro|TX4927_SDRAMC_SDCMD
mdefine_line|#define TX4927_SDRAMC_SDCMD             0x8058
DECL|macro|TX4927_SDRAMC_LIMIT
mdefine_line|#define TX4927_SDRAMC_LIMIT             0x8fff 
multiline_comment|/* TX4927 external bus controller (64-bit registers) */
DECL|macro|TX4927_EBUSC_BASE
mdefine_line|#define TX4927_EBUSC_BASE               0x9000
DECL|macro|TX4927_EBUSC_EBCCR0
mdefine_line|#define TX4927_EBUSC_EBCCR0             0x9000
DECL|macro|TX4927_EBUSC_EBCCR1
mdefine_line|#define TX4927_EBUSC_EBCCR1             0x9008
DECL|macro|TX4927_EBUSC_EBCCR2
mdefine_line|#define TX4927_EBUSC_EBCCR2             0x9010
DECL|macro|TX4927_EBUSC_EBCCR3
mdefine_line|#define TX4927_EBUSC_EBCCR3             0x9018
DECL|macro|TX4927_EBUSC_EBCCR4
mdefine_line|#define TX4927_EBUSC_EBCCR4             0x9020
DECL|macro|TX4927_EBUSC_EBCCR5
mdefine_line|#define TX4927_EBUSC_EBCCR5             0x9028
DECL|macro|TX4927_EBUSC_EBCCR6
mdefine_line|#define TX4927_EBUSC_EBCCR6             0x9030
DECL|macro|TX4927_EBUSC_EBCCR7
mdefine_line|#define TX4927_EBUSC_EBCCR7             0x9008
DECL|macro|TX4927_EBUSC_LIMIT
mdefine_line|#define TX4927_EBUSC_LIMIT              0x9fff
multiline_comment|/* TX4927 SDRRAM Error Check Correction (64-bit registers) */
DECL|macro|TX4927_ECC_BASE
mdefine_line|#define TX4927_ECC_BASE                 0xa000
DECL|macro|TX4927_ECC_ECCCR
mdefine_line|#define TX4927_ECC_ECCCR                0xa000
DECL|macro|TX4927_ECC_ECCSR
mdefine_line|#define TX4927_ECC_ECCSR                0xa008
DECL|macro|TX4927_ECC_LIMIT
mdefine_line|#define TX4927_ECC_LIMIT                0xafff
multiline_comment|/* TX4927 DMA Controller (64-bit registers) */
DECL|macro|TX4927_DMAC_BASE
mdefine_line|#define TX4927_DMAC_BASE                0xb000
DECL|macro|TX4927_DMAC_TBD
mdefine_line|#define TX4927_DMAC_TBD                 0xb000
DECL|macro|TX4927_DMAC_LIMIT
mdefine_line|#define TX4927_DMAC_LIMIT               0xbfff
multiline_comment|/* TX4927 PCI Controller (32-bit registers) */
DECL|macro|TX4927_PCIC_BASE
mdefine_line|#define TX4927_PCIC_BASE                0xd000
DECL|macro|TX4927_PCIC_TBD
mdefine_line|#define TX4927_PCIC_TBD                 0xb000
DECL|macro|TX4927_PCIC_LIMIT
mdefine_line|#define TX4927_PCIC_LIMIT               0xdfff
multiline_comment|/* TX4927 Configuration registers (64-bit registers) */
DECL|macro|TX4927_CONFIG_BASE
mdefine_line|#define TX4927_CONFIG_BASE                       0xe000
DECL|macro|TX4927_CONFIG_CCFG
mdefine_line|#define TX4927_CONFIG_CCFG                       0xe000
DECL|macro|TX4927_CONFIG_CCFG_RESERVED_42_63
mdefine_line|#define TX4927_CONFIG_CCFG_RESERVED_42_63                BM_63_42
DECL|macro|TX4927_CONFIG_CCFG_WDRST
mdefine_line|#define TX4927_CONFIG_CCFG_WDRST                         BM_41_41
DECL|macro|TX4927_CONFIG_CCFG_WDREXEN
mdefine_line|#define TX4927_CONFIG_CCFG_WDREXEN                       BM_40_40
DECL|macro|TX4927_CONFIG_CCFG_BCFG
mdefine_line|#define TX4927_CONFIG_CCFG_BCFG                          BM_39_32
DECL|macro|TX4927_CONFIG_CCFG_RESERVED_27_31
mdefine_line|#define TX4927_CONFIG_CCFG_RESERVED_27_31                BM_31_27
DECL|macro|TX4927_CONFIG_CCFG_GTOT
mdefine_line|#define TX4927_CONFIG_CCFG_GTOT                          BM_26_25
DECL|macro|TX4927_CONFIG_CCFG_GTOT_4096
mdefine_line|#define TX4927_CONFIG_CCFG_GTOT_4096                     BM_26_25
DECL|macro|TX4927_CONFIG_CCFG_GTOT_2048
mdefine_line|#define TX4927_CONFIG_CCFG_GTOT_2048                     BM_26_26
DECL|macro|TX4927_CONFIG_CCFG_GTOT_1024
mdefine_line|#define TX4927_CONFIG_CCFG_GTOT_1024                     BM_25_25
DECL|macro|TX4927_CONFIG_CCFG_GTOT_0512
mdefine_line|#define TX4927_CONFIG_CCFG_GTOT_0512                   (~BM_26_25)
DECL|macro|TX4927_CONFIG_CCFG_TINTDIS
mdefine_line|#define TX4927_CONFIG_CCFG_TINTDIS                       BM_24_24
DECL|macro|TX4927_CONFIG_CCFG_PCI66
mdefine_line|#define TX4927_CONFIG_CCFG_PCI66                         BM_23_23
DECL|macro|TX4927_CONFIG_CCFG_PCIMODE
mdefine_line|#define TX4927_CONFIG_CCFG_PCIMODE                       BM_22_22
DECL|macro|TX4927_CONFIG_CCFG_RESERVED_20_21
mdefine_line|#define TX4927_CONFIG_CCFG_RESERVED_20_21                BM_21_20
DECL|macro|TX4927_CONFIG_CCFG_DIVMODE
mdefine_line|#define TX4927_CONFIG_CCFG_DIVMODE                       BM_19_17
DECL|macro|TX4927_CONFIG_CCFG_DIVMODE_2_0
mdefine_line|#define TX4927_CONFIG_CCFG_DIVMODE_2_0                   BM_19_19
DECL|macro|TX4927_CONFIG_CCFG_DIVMODE_3_0
mdefine_line|#define TX4927_CONFIG_CCFG_DIVMODE_3_0                  (BM_19_19|BM_17_17)
DECL|macro|TX4927_CONFIG_CCFG_DIVMODE_4_0
mdefine_line|#define TX4927_CONFIG_CCFG_DIVMODE_4_0                   BM_19_18
DECL|macro|TX4927_CONFIG_CCFG_DIVMODE_2_5
mdefine_line|#define TX4927_CONFIG_CCFG_DIVMODE_2_5                   BM_19_17
DECL|macro|TX4927_CONFIG_CCFG_DIVMODE_8_0
mdefine_line|#define TX4927_CONFIG_CCFG_DIVMODE_8_0                 (~BM_19_17)
DECL|macro|TX4927_CONFIG_CCFG_DIVMODE_12_0
mdefine_line|#define TX4927_CONFIG_CCFG_DIVMODE_12_0                  BM_17_17
DECL|macro|TX4927_CONFIG_CCFG_DIVMODE_16_0
mdefine_line|#define TX4927_CONFIG_CCFG_DIVMODE_16_0                  BM_18_18
DECL|macro|TX4927_CONFIG_CCFG_DIVMODE_10_0
mdefine_line|#define TX4927_CONFIG_CCFG_DIVMODE_10_0                  BM_18_17
DECL|macro|TX4927_CONFIG_CCFG_BEOW
mdefine_line|#define TX4927_CONFIG_CCFG_BEOW                          BM_16_16
DECL|macro|TX4927_CONFIG_CCFG_WR
mdefine_line|#define TX4927_CONFIG_CCFG_WR                            BM_15_15
DECL|macro|TX4927_CONFIG_CCFG_TOE
mdefine_line|#define TX4927_CONFIG_CCFG_TOE                           BM_14_14
DECL|macro|TX4927_CONFIG_CCFG_PCIARB
mdefine_line|#define TX4927_CONFIG_CCFG_PCIARB                        BM_13_13
DECL|macro|TX4927_CONFIG_CCFG_PCIDIVMODE
mdefine_line|#define TX4927_CONFIG_CCFG_PCIDIVMODE                    BM_12_11
DECL|macro|TX4927_CONFIG_CCFG_RESERVED_08_10
mdefine_line|#define TX4927_CONFIG_CCFG_RESERVED_08_10                BM_10_08
DECL|macro|TX4927_CONFIG_CCFG_SYSSP
mdefine_line|#define TX4927_CONFIG_CCFG_SYSSP                         BM_07_06
DECL|macro|TX4927_CONFIG_CCFG_RESERVED_03_05
mdefine_line|#define TX4927_CONFIG_CCFG_RESERVED_03_05                BM_05_03
DECL|macro|TX4927_CONFIG_CCFG_ENDIAN
mdefine_line|#define TX4927_CONFIG_CCFG_ENDIAN                        BM_02_02
DECL|macro|TX4927_CONFIG_CCFG_ARMODE
mdefine_line|#define TX4927_CONFIG_CCFG_ARMODE                        BM_01_01
DECL|macro|TX4927_CONFIG_CCFG_ACEHOLD
mdefine_line|#define TX4927_CONFIG_CCFG_ACEHOLD                       BM_00_00
DECL|macro|TX4927_CONFIG_REVID
mdefine_line|#define TX4927_CONFIG_REVID                      0xe008
DECL|macro|TX4927_CONFIG_REVID_RESERVED_32_63
mdefine_line|#define TX4927_CONFIG_REVID_RESERVED_32_63               BM_32_63
DECL|macro|TX4927_CONFIG_REVID_PCODE
mdefine_line|#define TX4927_CONFIG_REVID_PCODE                        BM_16_31
DECL|macro|TX4927_CONFIG_REVID_MJERREV
mdefine_line|#define TX4927_CONFIG_REVID_MJERREV                      BM_12_15
DECL|macro|TX4927_CONFIG_REVID_MINEREV
mdefine_line|#define TX4927_CONFIG_REVID_MINEREV                      BM_08_11
DECL|macro|TX4927_CONFIG_REVID_MJREV
mdefine_line|#define TX4927_CONFIG_REVID_MJREV                        BM_04_07
DECL|macro|TX4927_CONFIG_REVID_MINREV
mdefine_line|#define TX4927_CONFIG_REVID_MINREV                       BM_00_03
DECL|macro|TX4927_CONFIG_PCFG
mdefine_line|#define TX4927_CONFIG_PCFG                       0xe010
DECL|macro|TX4927_CONFIG_PCFG_RESERVED_57_63
mdefine_line|#define TX4927_CONFIG_PCFG_RESERVED_57_63                BM_57_63
DECL|macro|TX4927_CONFIG_PCFG_DRVDATA
mdefine_line|#define TX4927_CONFIG_PCFG_DRVDATA                       BM_56_56
DECL|macro|TX4927_CONFIG_PCFG_DRVCB
mdefine_line|#define TX4927_CONFIG_PCFG_DRVCB                         BM_55_55
DECL|macro|TX4927_CONFIG_PCFG_DRVDQM
mdefine_line|#define TX4927_CONFIG_PCFG_DRVDQM                        BM_54_54
DECL|macro|TX4927_CONFIG_PCFG_DRVADDR
mdefine_line|#define TX4927_CONFIG_PCFG_DRVADDR                       BM_53_53
DECL|macro|TX4927_CONFIG_PCFG_DRVCKE
mdefine_line|#define TX4927_CONFIG_PCFG_DRVCKE                        BM_52_52
DECL|macro|TX4927_CONFIG_PCFG_DRVRAS
mdefine_line|#define TX4927_CONFIG_PCFG_DRVRAS                        BM_51_51
DECL|macro|TX4927_CONFIG_PCFG_DRVCAS
mdefine_line|#define TX4927_CONFIG_PCFG_DRVCAS                        BM_50_50
DECL|macro|TX4927_CONFIG_PCFG_DRVWE
mdefine_line|#define TX4927_CONFIG_PCFG_DRVWE                         BM_49_49
DECL|macro|TX4927_CONFIG_PCFG_DRVCS3
mdefine_line|#define TX4927_CONFIG_PCFG_DRVCS3                        BM_48_48
DECL|macro|TX4927_CONFIG_PCFG_DRVCS2
mdefine_line|#define TX4927_CONFIG_PCFG_DRVCS2                        BM_47_47
DECL|macro|TX4927_CONFIG_PCFG_DRVCS1
mdefine_line|#define TX4927_CONFIG_PCFG_DRVCS1                        BM_46_4k
DECL|macro|TX4927_CONFIG_PCFG_DRVCS0
mdefine_line|#define TX4927_CONFIG_PCFG_DRVCS0                        BM_45_45
DECL|macro|TX4927_CONFIG_PCFG_DRVCK3
mdefine_line|#define TX4927_CONFIG_PCFG_DRVCK3                        BM_44_44
DECL|macro|TX4927_CONFIG_PCFG_DRVCK2
mdefine_line|#define TX4927_CONFIG_PCFG_DRVCK2                        BM_43_43
DECL|macro|TX4927_CONFIG_PCFG_DRVCK1
mdefine_line|#define TX4927_CONFIG_PCFG_DRVCK1                        BM_42_42
DECL|macro|TX4927_CONFIG_PCFG_DRVCK0
mdefine_line|#define TX4927_CONFIG_PCFG_DRVCK0                        BM_41_41
DECL|macro|TX4927_CONFIG_PCFG_DRVCKIN
mdefine_line|#define TX4927_CONFIG_PCFG_DRVCKIN                       BM_40_40
DECL|macro|TX4927_CONFIG_PCFG_RESERVED_33_39
mdefine_line|#define TX4927_CONFIG_PCFG_RESERVED_33_39                BM_33_39
DECL|macro|TX4927_CONFIG_PCFG_BYPASS_PLL
mdefine_line|#define TX4927_CONFIG_PCFG_BYPASS_PLL                    BM_32_32
DECL|macro|TX4927_CONFIG_PCFG_RESERVED_30_31
mdefine_line|#define TX4927_CONFIG_PCFG_RESERVED_30_31                BM_30_31
DECL|macro|TX4927_CONFIG_PCFG_SDCLKDLY
mdefine_line|#define TX4927_CONFIG_PCFG_SDCLKDLY                      BM_28_29
DECL|macro|TX4927_CONFIG_PCFG_SDCLKDLY_DELAY_1
mdefine_line|#define TX4927_CONFIG_PCFG_SDCLKDLY_DELAY_1            (~BM_28_29)
DECL|macro|TX4927_CONFIG_PCFG_SDCLKDLY_DELAY_2
mdefine_line|#define TX4927_CONFIG_PCFG_SDCLKDLY_DELAY_2              BM_28_28
DECL|macro|TX4927_CONFIG_PCFG_SDCLKDLY_DELAY_3
mdefine_line|#define TX4927_CONFIG_PCFG_SDCLKDLY_DELAY_3              BM_29_29
DECL|macro|TX4927_CONFIG_PCFG_SDCLKDLY_DELAY_4
mdefine_line|#define TX4927_CONFIG_PCFG_SDCLKDLY_DELAY_4              BM_28_29
DECL|macro|TX4927_CONFIG_PCFG_SYSCLKEN
mdefine_line|#define TX4927_CONFIG_PCFG_SYSCLKEN                      BM_27_27
DECL|macro|TX4927_CONFIG_PCFG_SDCLKEN3
mdefine_line|#define TX4927_CONFIG_PCFG_SDCLKEN3                      BM_26_26
DECL|macro|TX4927_CONFIG_PCFG_SDCLKEN2
mdefine_line|#define TX4927_CONFIG_PCFG_SDCLKEN2                      BM_25_25
DECL|macro|TX4927_CONFIG_PCFG_SDCLKEN1
mdefine_line|#define TX4927_CONFIG_PCFG_SDCLKEN1                      BM_24_24
DECL|macro|TX4927_CONFIG_PCFG_SDCLKEN0
mdefine_line|#define TX4927_CONFIG_PCFG_SDCLKEN0                      BM_23_23
DECL|macro|TX4927_CONFIG_PCFG_SDCLKINEN
mdefine_line|#define TX4927_CONFIG_PCFG_SDCLKINEN                     BM_22_22
DECL|macro|TX4927_CONFIG_PCFG_PCICLKEN5
mdefine_line|#define TX4927_CONFIG_PCFG_PCICLKEN5                     BM_21_21
DECL|macro|TX4927_CONFIG_PCFG_PCICLKEN4
mdefine_line|#define TX4927_CONFIG_PCFG_PCICLKEN4                     BM_20_20
DECL|macro|TX4927_CONFIG_PCFG_PCICLKEN3
mdefine_line|#define TX4927_CONFIG_PCFG_PCICLKEN3                     BM_19_19
DECL|macro|TX4927_CONFIG_PCFG_PCICLKEN2
mdefine_line|#define TX4927_CONFIG_PCFG_PCICLKEN2                     BM_18_18
DECL|macro|TX4927_CONFIG_PCFG_PCICLKEN1
mdefine_line|#define TX4927_CONFIG_PCFG_PCICLKEN1                     BM_17_17
DECL|macro|TX4927_CONFIG_PCFG_PCICLKEN0
mdefine_line|#define TX4927_CONFIG_PCFG_PCICLKEN0                     BM_16_16
DECL|macro|TX4927_CONFIG_PCFG_RESERVED_10_15
mdefine_line|#define TX4927_CONFIG_PCFG_RESERVED_10_15                BM_10_15
DECL|macro|TX4927_CONFIG_PCFG_SEL2
mdefine_line|#define TX4927_CONFIG_PCFG_SEL2                          BM_09_09
DECL|macro|TX4927_CONFIG_PCFG_SEL1
mdefine_line|#define TX4927_CONFIG_PCFG_SEL1                          BM_08_08
DECL|macro|TX4927_CONFIG_PCFG_DMASEL3
mdefine_line|#define TX4927_CONFIG_PCFG_DMASEL3                       BM_06_07
DECL|macro|TX4927_CONFIG_PCFG_DMASEL3_DMAREQ3
mdefine_line|#define TX4927_CONFIG_PCFG_DMASEL3_DMAREQ3             (~BM_06_07)
DECL|macro|TX4927_CONFIG_PCFG_DMASEL3_SIO0
mdefine_line|#define TX4927_CONFIG_PCFG_DMASEL3_SIO0                  BM_06_06
DECL|macro|TX4927_CONFIG_PCFG_DMASEL3_ACLC3
mdefine_line|#define TX4927_CONFIG_PCFG_DMASEL3_ACLC3                 BM_07_07
DECL|macro|TX4927_CONFIG_PCFG_DMASEL3_ACLC1
mdefine_line|#define TX4927_CONFIG_PCFG_DMASEL3_ACLC1                 BM_06_07
DECL|macro|TX4927_CONFIG_PCFG_DMASEL2
mdefine_line|#define TX4927_CONFIG_PCFG_DMASEL2                       BM_06_07
DECL|macro|TX4927_CONFIG_PCFG_DMASEL2_SEL2_0_DMAREQ2
mdefine_line|#define TX4927_CONFIG_PCFG_DMASEL2_SEL2_0_DMAREQ2      (~BM_06_07)
DECL|macro|TX4927_CONFIG_PCFG_DMASEL2_SEL2_0_SIO0
mdefine_line|#define TX4927_CONFIG_PCFG_DMASEL2_SEL2_0_SIO0           BM_06_06
DECL|macro|TX4927_CONFIG_PCFG_DMASEL2_SEL2_0_RESERVED_10
mdefine_line|#define TX4927_CONFIG_PCFG_DMASEL2_SEL2_0_RESERVED_10    BM_07_07
DECL|macro|TX4927_CONFIG_PCFG_DMASEL2_SEL2_0_RESERVED_11
mdefine_line|#define TX4927_CONFIG_PCFG_DMASEL2_SEL2_0_RESERVED_11    BM_06_07
DECL|macro|TX4927_CONFIG_PCFG_DMASEL2_SEL2_1_ACLC1
mdefine_line|#define TX4927_CONFIG_PCFG_DMASEL2_SEL2_1_ACLC1        (~BM_06_07)
DECL|macro|TX4927_CONFIG_PCFG_DMASEL2_SEL2_1_SIO0
mdefine_line|#define TX4927_CONFIG_PCFG_DMASEL2_SEL2_1_SIO0           BM_06_06
DECL|macro|TX4927_CONFIG_PCFG_DMASEL2_SEL2_1_ACLC2
mdefine_line|#define TX4927_CONFIG_PCFG_DMASEL2_SEL2_1_ACLC2          BM_07_07
DECL|macro|TX4927_CONFIG_PCFG_DMASEL2_SEL2_1_ACLC0
mdefine_line|#define TX4927_CONFIG_PCFG_DMASEL2_SEL2_1_ACLC0          BM_06_07
DECL|macro|TX4927_CONFIG_PCFG_DMASEL1
mdefine_line|#define TX4927_CONFIG_PCFG_DMASEL1                       BM_02_03
DECL|macro|TX4927_CONFIG_PCFG_DMASEL1_DMAREQ1
mdefine_line|#define TX4927_CONFIG_PCFG_DMASEL1_DMAREQ1             (~BM_02_03)
DECL|macro|TX4927_CONFIG_PCFG_DMASEL1_SIO1
mdefine_line|#define TX4927_CONFIG_PCFG_DMASEL1_SIO1                  BM_02_02
DECL|macro|TX4927_CONFIG_PCFG_DMASEL1_ACLC1
mdefine_line|#define TX4927_CONFIG_PCFG_DMASEL1_ACLC1                 BM_03_03
DECL|macro|TX4927_CONFIG_PCFG_DMASEL1_ACLC3
mdefine_line|#define TX4927_CONFIG_PCFG_DMASEL1_ACLC3                 BM_02_03
DECL|macro|TX4927_CONFIG_PCFG_DMASEL0
mdefine_line|#define TX4927_CONFIG_PCFG_DMASEL0                       BM_00_01
DECL|macro|TX4927_CONFIG_PCFG_DMASEL0_DMAREQ0
mdefine_line|#define TX4927_CONFIG_PCFG_DMASEL0_DMAREQ0             (~BM_00_01)
DECL|macro|TX4927_CONFIG_PCFG_DMASEL0_SIO1
mdefine_line|#define TX4927_CONFIG_PCFG_DMASEL0_SIO1                  BM_00_00
DECL|macro|TX4927_CONFIG_PCFG_DMASEL0_ACLC0
mdefine_line|#define TX4927_CONFIG_PCFG_DMASEL0_ACLC0                 BM_01_01
DECL|macro|TX4927_CONFIG_PCFG_DMASEL0_ACLC2
mdefine_line|#define TX4927_CONFIG_PCFG_DMASEL0_ACLC2                 BM_00_01
DECL|macro|TX4927_CONFIG_TOEA
mdefine_line|#define TX4927_CONFIG_TOEA                       0xe018
DECL|macro|TX4927_CONFIG_TOEA_RESERVED_36_63
mdefine_line|#define TX4927_CONFIG_TOEA_RESERVED_36_63                BM_36_63
DECL|macro|TX4927_CONFIG_TOEA_TOEA
mdefine_line|#define TX4927_CONFIG_TOEA_TOEA                          BM_00_35
DECL|macro|TX4927_CONFIG_CLKCTR
mdefine_line|#define TX4927_CONFIG_CLKCTR                     0xe020
DECL|macro|TX4927_CONFIG_CLKCTR_RESERVED_26_63
mdefine_line|#define TX4927_CONFIG_CLKCTR_RESERVED_26_63              BM_26_63
DECL|macro|TX4927_CONFIG_CLKCTR_ACLCKD
mdefine_line|#define TX4927_CONFIG_CLKCTR_ACLCKD                      BM_25_25
DECL|macro|TX4927_CONFIG_CLKCTR_PIOCKD
mdefine_line|#define TX4927_CONFIG_CLKCTR_PIOCKD                      BM_24_24
DECL|macro|TX4927_CONFIG_CLKCTR_DMACKD
mdefine_line|#define TX4927_CONFIG_CLKCTR_DMACKD                      BM_23_23
DECL|macro|TX4927_CONFIG_CLKCTR_PCICKD
mdefine_line|#define TX4927_CONFIG_CLKCTR_PCICKD                      BM_22_22
DECL|macro|TX4927_CONFIG_CLKCTR_SET_21
mdefine_line|#define TX4927_CONFIG_CLKCTR_SET_21                      BM_21_21
DECL|macro|TX4927_CONFIG_CLKCTR_TM0CKD
mdefine_line|#define TX4927_CONFIG_CLKCTR_TM0CKD                      BM_20_20
DECL|macro|TX4927_CONFIG_CLKCTR_TM1CKD
mdefine_line|#define TX4927_CONFIG_CLKCTR_TM1CKD                      BM_19_19
DECL|macro|TX4927_CONFIG_CLKCTR_TM2CKD
mdefine_line|#define TX4927_CONFIG_CLKCTR_TM2CKD                      BM_18_18
DECL|macro|TX4927_CONFIG_CLKCTR_SIO0CKD
mdefine_line|#define TX4927_CONFIG_CLKCTR_SIO0CKD                     BM_17_17
DECL|macro|TX4927_CONFIG_CLKCTR_SIO1CKD
mdefine_line|#define TX4927_CONFIG_CLKCTR_SIO1CKD                     BM_16_16
DECL|macro|TX4927_CONFIG_CLKCTR_RESERVED_10_15
mdefine_line|#define TX4927_CONFIG_CLKCTR_RESERVED_10_15              BM_10_15
DECL|macro|TX4927_CONFIG_CLKCTR_ACLRST
mdefine_line|#define TX4927_CONFIG_CLKCTR_ACLRST                      BM_09_09
DECL|macro|TX4927_CONFIG_CLKCTR_PIORST
mdefine_line|#define TX4927_CONFIG_CLKCTR_PIORST                      BM_08_08
DECL|macro|TX4927_CONFIG_CLKCTR_DMARST
mdefine_line|#define TX4927_CONFIG_CLKCTR_DMARST                      BM_07_07
DECL|macro|TX4927_CONFIG_CLKCTR_PCIRST
mdefine_line|#define TX4927_CONFIG_CLKCTR_PCIRST                      BM_06_06
DECL|macro|TX4927_CONFIG_CLKCTR_RESERVED_05_05
mdefine_line|#define TX4927_CONFIG_CLKCTR_RESERVED_05_05              BM_05_05
DECL|macro|TX4927_CONFIG_CLKCTR_TM0RST
mdefine_line|#define TX4927_CONFIG_CLKCTR_TM0RST                      BM_04_04
DECL|macro|TX4927_CONFIG_CLKCTR_TM1RST
mdefine_line|#define TX4927_CONFIG_CLKCTR_TM1RST                      BM_03_03
DECL|macro|TX4927_CONFIG_CLKCTR_TM2RST
mdefine_line|#define TX4927_CONFIG_CLKCTR_TM2RST                      BM_02_02
DECL|macro|TX4927_CONFIG_CLKCTR_SIO0RST
mdefine_line|#define TX4927_CONFIG_CLKCTR_SIO0RST                     BM_01_01
DECL|macro|TX4927_CONFIG_CLKCTR_SIO1RST
mdefine_line|#define TX4927_CONFIG_CLKCTR_SIO1RST                     BM_00_00
DECL|macro|TX4927_CONFIG_GARBC
mdefine_line|#define TX4927_CONFIG_GARBC                      0xe030
DECL|macro|TX4927_CONFIG_GARBC_RESERVED_10_63
mdefine_line|#define TX4927_CONFIG_GARBC_RESERVED_10_63               BM_10_63
DECL|macro|TX4927_CONFIG_GARBC_SET_09
mdefine_line|#define TX4927_CONFIG_GARBC_SET_09                       BM_09_09
DECL|macro|TX4927_CONFIG_GARBC_ARBMD
mdefine_line|#define TX4927_CONFIG_GARBC_ARBMD                        BM_08_08
DECL|macro|TX4927_CONFIG_GARBC_RESERVED_06_07
mdefine_line|#define TX4927_CONFIG_GARBC_RESERVED_06_07               BM_06_07
DECL|macro|TX4927_CONFIG_GARBC_PRIORITY_H1
mdefine_line|#define TX4927_CONFIG_GARBC_PRIORITY_H1                  BM_04_05
DECL|macro|TX4927_CONFIG_GARBC_PRIORITY_H1_PCI
mdefine_line|#define TX4927_CONFIG_GARBC_PRIORITY_H1_PCI            (~BM_04_05)
DECL|macro|TX4927_CONFIG_GARBC_PRIORITY_H1_PDMAC
mdefine_line|#define TX4927_CONFIG_GARBC_PRIORITY_H1_PDMAC            BM_04_04
DECL|macro|TX4927_CONFIG_GARBC_PRIORITY_H1_DMAC
mdefine_line|#define TX4927_CONFIG_GARBC_PRIORITY_H1_DMAC             BM_05_05
DECL|macro|TX4927_CONFIG_GARBC_PRIORITY_H1_BAD_VALUE
mdefine_line|#define TX4927_CONFIG_GARBC_PRIORITY_H1_BAD_VALUE        BM_04_05
DECL|macro|TX4927_CONFIG_GARBC_PRIORITY_H2
mdefine_line|#define TX4927_CONFIG_GARBC_PRIORITY_H2                  BM_02_03
DECL|macro|TX4927_CONFIG_GARBC_PRIORITY_H2_PCI
mdefine_line|#define TX4927_CONFIG_GARBC_PRIORITY_H2_PCI            (~BM_02_03)
DECL|macro|TX4927_CONFIG_GARBC_PRIORITY_H2_PDMAC
mdefine_line|#define TX4927_CONFIG_GARBC_PRIORITY_H2_PDMAC            BM_02_02
DECL|macro|TX4927_CONFIG_GARBC_PRIORITY_H2_DMAC
mdefine_line|#define TX4927_CONFIG_GARBC_PRIORITY_H2_DMAC             BM_03_03
DECL|macro|TX4927_CONFIG_GARBC_PRIORITY_H2_BAD_VALUE
mdefine_line|#define TX4927_CONFIG_GARBC_PRIORITY_H2_BAD_VALUE        BM_02_03
DECL|macro|TX4927_CONFIG_GARBC_PRIORITY_H3
mdefine_line|#define TX4927_CONFIG_GARBC_PRIORITY_H3                  BM_00_01
DECL|macro|TX4927_CONFIG_GARBC_PRIORITY_H3_PCI
mdefine_line|#define TX4927_CONFIG_GARBC_PRIORITY_H3_PCI            (~BM_00_01)
DECL|macro|TX4927_CONFIG_GARBC_PRIORITY_H3_PDMAC
mdefine_line|#define TX4927_CONFIG_GARBC_PRIORITY_H3_PDMAC            BM_00_00
DECL|macro|TX4927_CONFIG_GARBC_PRIORITY_H3_DMAC
mdefine_line|#define TX4927_CONFIG_GARBC_PRIORITY_H3_DMAC             BM_01_01
DECL|macro|TX4927_CONFIG_GARBC_PRIORITY_H3_BAD_VALUE
mdefine_line|#define TX4927_CONFIG_GARBC_PRIORITY_H3_BAD_VALUE        BM_00_01
DECL|macro|TX4927_CONFIG_RAMP
mdefine_line|#define TX4927_CONFIG_RAMP                       0xe048
DECL|macro|TX4927_CONFIG_RAMP_RESERVED_20_63
mdefine_line|#define TX4927_CONFIG_RAMP_RESERVED_20_63                BM_20_63
DECL|macro|TX4927_CONFIG_RAMP_RAMP
mdefine_line|#define TX4927_CONFIG_RAMP_RAMP                          BM_00_19
DECL|macro|TX4927_CONFIG_LIMIT
mdefine_line|#define TX4927_CONFIG_LIMIT                      0xefff
multiline_comment|/* TX4927 Timer 0 (32-bit registers) */
DECL|macro|TX4927_TMR0_BASE
mdefine_line|#define TX4927_TMR0_BASE                0xf000
DECL|macro|TX4927_TMR0_TMTCR0
mdefine_line|#define TX4927_TMR0_TMTCR0              0xf004
DECL|macro|TX4927_TMR0_TMTISR0
mdefine_line|#define TX4927_TMR0_TMTISR0             0xf008
DECL|macro|TX4927_TMR0_TMCPRA0
mdefine_line|#define TX4927_TMR0_TMCPRA0             0xf008
DECL|macro|TX4927_TMR0_TMCPRB0
mdefine_line|#define TX4927_TMR0_TMCPRB0             0xf00c
DECL|macro|TX4927_TMR0_TMITMR0
mdefine_line|#define TX4927_TMR0_TMITMR0             0xf010
DECL|macro|TX4927_TMR0_TMCCDR0
mdefine_line|#define TX4927_TMR0_TMCCDR0             0xf020
DECL|macro|TX4927_TMR0_TMPGMR0
mdefine_line|#define TX4927_TMR0_TMPGMR0             0xf030
DECL|macro|TX4927_TMR0_TMTRR0
mdefine_line|#define TX4927_TMR0_TMTRR0              0xf0f0
DECL|macro|TX4927_TMR0_LIMIT
mdefine_line|#define TX4927_TMR0_LIMIT               0xf0ff
multiline_comment|/* TX4927 Timer 1 (32-bit registers) */
DECL|macro|TX4927_TMR1_BASE
mdefine_line|#define TX4927_TMR1_BASE                0xf100
DECL|macro|TX4927_TMR1_TMTCR1
mdefine_line|#define TX4927_TMR1_TMTCR1              0xf104
DECL|macro|TX4927_TMR1_TMTISR1
mdefine_line|#define TX4927_TMR1_TMTISR1             0xf108
DECL|macro|TX4927_TMR1_TMCPRA1
mdefine_line|#define TX4927_TMR1_TMCPRA1             0xf108
DECL|macro|TX4927_TMR1_TMCPRB1
mdefine_line|#define TX4927_TMR1_TMCPRB1             0xf10c
DECL|macro|TX4927_TMR1_TMITMR1
mdefine_line|#define TX4927_TMR1_TMITMR1             0xf110
DECL|macro|TX4927_TMR1_TMCCDR1
mdefine_line|#define TX4927_TMR1_TMCCDR1             0xf120
DECL|macro|TX4927_TMR1_TMPGMR1
mdefine_line|#define TX4927_TMR1_TMPGMR1             0xf130
DECL|macro|TX4927_TMR1_TMTRR1
mdefine_line|#define TX4927_TMR1_TMTRR1              0xf1f0
DECL|macro|TX4927_TMR1_LIMIT
mdefine_line|#define TX4927_TMR1_LIMIT               0xf1ff
multiline_comment|/* TX4927 Timer 2 (32-bit registers) */
DECL|macro|TX4927_TMR2_BASE
mdefine_line|#define TX4927_TMR2_BASE                0xf200
DECL|macro|TX4927_TMR2_TMTCR2
mdefine_line|#define TX4927_TMR2_TMTCR2              0xf104
DECL|macro|TX4927_TMR2_TMTISR2
mdefine_line|#define TX4927_TMR2_TMTISR2             0xf208
DECL|macro|TX4927_TMR2_TMCPRA2
mdefine_line|#define TX4927_TMR2_TMCPRA2             0xf208
DECL|macro|TX4927_TMR2_TMCPRB2
mdefine_line|#define TX4927_TMR2_TMCPRB2             0xf20c
DECL|macro|TX4927_TMR2_TMITMR2
mdefine_line|#define TX4927_TMR2_TMITMR2             0xf210
DECL|macro|TX4927_TMR2_TMCCDR2
mdefine_line|#define TX4927_TMR2_TMCCDR2             0xf220
DECL|macro|TX4927_TMR2_TMPGMR2
mdefine_line|#define TX4927_TMR2_TMPGMR2             0xf230
DECL|macro|TX4927_TMR2_TMTRR2
mdefine_line|#define TX4927_TMR2_TMTRR2              0xf2f0
DECL|macro|TX4927_TMR2_LIMIT
mdefine_line|#define TX4927_TMR2_LIMIT               0xf2ff
multiline_comment|/* TX4927 serial port 0 (32-bit registers) */
DECL|macro|TX4927_SIO0_BASE
mdefine_line|#define TX4927_SIO0_BASE                         0xf300 
DECL|macro|TX4927_SIO0_SILCR0
mdefine_line|#define TX4927_SIO0_SILCR0                       0xf300 
DECL|macro|TX4927_SIO0_SILCR0_RESERVED_16_31
mdefine_line|#define TX4927_SIO0_SILCR0_RESERVED_16_31                BM_16_31
DECL|macro|TX4927_SIO0_SILCR0_RWUB
mdefine_line|#define TX4927_SIO0_SILCR0_RWUB                          BM_15_15
DECL|macro|TX4927_SIO0_SILCR0_TWUB
mdefine_line|#define TX4927_SIO0_SILCR0_TWUB                          BM_14_14
DECL|macro|TX4927_SIO0_SILCR0_UODE
mdefine_line|#define TX4927_SIO0_SILCR0_UODE                          BM_13_13
DECL|macro|TX4927_SIO0_SILCR0_RESERVED_07_12
mdefine_line|#define TX4927_SIO0_SILCR0_RESERVED_07_12                BM_07_12
DECL|macro|TX4927_SIO0_SILCR0_SCS
mdefine_line|#define TX4927_SIO0_SILCR0_SCS                           BM_05_06
DECL|macro|TX4927_SIO0_SILCR0_SCS_IMBUSCLK_IC
mdefine_line|#define TX4927_SIO0_SILCR0_SCS_IMBUSCLK_IC             (~BM_05_06)
DECL|macro|TX4927_SIO0_SILCR0_SCS_IMBUSCLK_BRG
mdefine_line|#define TX4927_SIO0_SILCR0_SCS_IMBUSCLK_BRG              BM_05_05
DECL|macro|TX4927_SIO0_SILCR0_SCS_SCLK_EC
mdefine_line|#define TX4927_SIO0_SILCR0_SCS_SCLK_EC                   BM_06_06
DECL|macro|TX4927_SIO0_SILCR0_SCS_SCLK_BRG
mdefine_line|#define TX4927_SIO0_SILCR0_SCS_SCLK_BRG                  BM_05_06
DECL|macro|TX4927_SIO0_SILCR0_UEPS
mdefine_line|#define TX4927_SIO0_SILCR0_UEPS                          BM_04_04
DECL|macro|TX4927_SIO0_SILCR0_UPEN
mdefine_line|#define TX4927_SIO0_SILCR0_UPEN                          BM_03_03
DECL|macro|TX4927_SIO0_SILCR0_USBL
mdefine_line|#define TX4927_SIO0_SILCR0_USBL                          BM_02_02
DECL|macro|TX4927_SIO0_SILCR0_UMODE
mdefine_line|#define TX4927_SIO0_SILCR0_UMODE                         BM_00_01
DECL|macro|TX4927_SIO0_SILCR0_UMODE_DATA_8_BIT
mdefine_line|#define TX4927_SIO0_SILCR0_UMODE_DATA_8_BIT              BM_00_01
DECL|macro|TX4927_SIO0_SILCR0_UMODE_DATA_7_BIT
mdefine_line|#define TX4927_SIO0_SILCR0_UMODE_DATA_7_BIT            (~BM_00_01)
DECL|macro|TX4927_SIO0_SILCR0_UMODE_DATA_8_BIT_MC
mdefine_line|#define TX4927_SIO0_SILCR0_UMODE_DATA_8_BIT_MC           BM_01_01
DECL|macro|TX4927_SIO0_SILCR0_UMODE_DATA_7_BIT_MC
mdefine_line|#define TX4927_SIO0_SILCR0_UMODE_DATA_7_BIT_MC           BM_00_01
DECL|macro|TX4927_SIO0_SIDICR0
mdefine_line|#define TX4927_SIO0_SIDICR0                      0xf304 
DECL|macro|TX4927_SIO0_SIDICR0_RESERVED_16_31
mdefine_line|#define TX4927_SIO0_SIDICR0_RESERVED_16_31               BM_16_31
DECL|macro|TX4927_SIO0_SIDICR0_TDE
mdefine_line|#define TX4927_SIO0_SIDICR0_TDE                          BM_15_15
DECL|macro|TX4927_SIO0_SIDICR0_RDE
mdefine_line|#define TX4927_SIO0_SIDICR0_RDE                          BM_14_14
DECL|macro|TX4927_SIO0_SIDICR0_TIE
mdefine_line|#define TX4927_SIO0_SIDICR0_TIE                          BM_13_13
DECL|macro|TX4927_SIO0_SIDICR0_RIE
mdefine_line|#define TX4927_SIO0_SIDICR0_RIE                          BM_12_12
DECL|macro|TX4927_SIO0_SIDICR0_SPIE
mdefine_line|#define TX4927_SIO0_SIDICR0_SPIE                         BM_11_11
DECL|macro|TX4927_SIO0_SIDICR0_CTSAC
mdefine_line|#define TX4927_SIO0_SIDICR0_CTSAC                        BM_09_10
DECL|macro|TX4927_SIO0_SIDICR0_CTSAC_NONE
mdefine_line|#define TX4927_SIO0_SIDICR0_CTSAC_NONE                 (~BM_09_10)
DECL|macro|TX4927_SIO0_SIDICR0_CTSAC_RISE
mdefine_line|#define TX4927_SIO0_SIDICR0_CTSAC_RISE                   BM_09_09
DECL|macro|TX4927_SIO0_SIDICR0_CTSAC_FALL
mdefine_line|#define TX4927_SIO0_SIDICR0_CTSAC_FALL                   BM_10_10
DECL|macro|TX4927_SIO0_SIDICR0_CTSAC_BOTH
mdefine_line|#define TX4927_SIO0_SIDICR0_CTSAC_BOTH                   BM_09_10
DECL|macro|TX4927_SIO0_SIDICR0_RESERVED_06_08
mdefine_line|#define TX4927_SIO0_SIDICR0_RESERVED_06_08               BM_06_08
DECL|macro|TX4927_SIO0_SIDICR0_STIE
mdefine_line|#define TX4927_SIO0_SIDICR0_STIE                         BM_00_05
DECL|macro|TX4927_SIO0_SIDICR0_STIE_NONE
mdefine_line|#define TX4927_SIO0_SIDICR0_STIE_NONE                  (~BM_00_05)
DECL|macro|TX4927_SIO0_SIDICR0_STIE_OERS
mdefine_line|#define TX4927_SIO0_SIDICR0_STIE_OERS                    BM_05_05
DECL|macro|TX4927_SIO0_SIDICR0_STIE_CTSAC
mdefine_line|#define TX4927_SIO0_SIDICR0_STIE_CTSAC                   BM_04_04
DECL|macro|TX4927_SIO0_SIDICR0_STIE_RBRKD
mdefine_line|#define TX4927_SIO0_SIDICR0_STIE_RBRKD                   BM_03_03
DECL|macro|TX4927_SIO0_SIDICR0_STIE_TRDY
mdefine_line|#define TX4927_SIO0_SIDICR0_STIE_TRDY                    BM_02_02
DECL|macro|TX4927_SIO0_SIDICR0_STIE_TXALS
mdefine_line|#define TX4927_SIO0_SIDICR0_STIE_TXALS                   BM_01_01
DECL|macro|TX4927_SIO0_SIDICR0_STIE_UBRKD
mdefine_line|#define TX4927_SIO0_SIDICR0_STIE_UBRKD                   BM_00_00
DECL|macro|TX4927_SIO0_SIDISR0
mdefine_line|#define TX4927_SIO0_SIDISR0                      0xf308 
DECL|macro|TX4927_SIO0_SIDISR0_RESERVED_16_31
mdefine_line|#define TX4927_SIO0_SIDISR0_RESERVED_16_31               BM_16_31
DECL|macro|TX4927_SIO0_SIDISR0_UBRK
mdefine_line|#define TX4927_SIO0_SIDISR0_UBRK                         BM_15_15
DECL|macro|TX4927_SIO0_SIDISR0_UVALID
mdefine_line|#define TX4927_SIO0_SIDISR0_UVALID                       BM_14_14
DECL|macro|TX4927_SIO0_SIDISR0_UFER
mdefine_line|#define TX4927_SIO0_SIDISR0_UFER                         BM_13_13
DECL|macro|TX4927_SIO0_SIDISR0_UPER
mdefine_line|#define TX4927_SIO0_SIDISR0_UPER                         BM_12_12
DECL|macro|TX4927_SIO0_SIDISR0_UOER
mdefine_line|#define TX4927_SIO0_SIDISR0_UOER                         BM_11_11
DECL|macro|TX4927_SIO0_SIDISR0_ERI
mdefine_line|#define TX4927_SIO0_SIDISR0_ERI                          BM_10_10
DECL|macro|TX4927_SIO0_SIDISR0_TOUT
mdefine_line|#define TX4927_SIO0_SIDISR0_TOUT                         BM_09_09
DECL|macro|TX4927_SIO0_SIDISR0_TDIS
mdefine_line|#define TX4927_SIO0_SIDISR0_TDIS                         BM_08_08
DECL|macro|TX4927_SIO0_SIDISR0_RDIS
mdefine_line|#define TX4927_SIO0_SIDISR0_RDIS                         BM_07_07
DECL|macro|TX4927_SIO0_SIDISR0_STIS
mdefine_line|#define TX4927_SIO0_SIDISR0_STIS                         BM_06_06
DECL|macro|TX4927_SIO0_SIDISR0_RESERVED_05_05
mdefine_line|#define TX4927_SIO0_SIDISR0_RESERVED_05_05               BM_05_05
DECL|macro|TX4927_SIO0_SIDISR0_RFDN
mdefine_line|#define TX4927_SIO0_SIDISR0_RFDN                         BM_00_04
DECL|macro|TX4927_SIO0_SISCISR0
mdefine_line|#define TX4927_SIO0_SISCISR0                     0xf30c 
DECL|macro|TX4927_SIO0_SISCISR0_RESERVED_06_31
mdefine_line|#define TX4927_SIO0_SISCISR0_RESERVED_06_31              BM_06_31
DECL|macro|TX4927_SIO0_SISCISR0_OERS
mdefine_line|#define TX4927_SIO0_SISCISR0_OERS                        BM_05_05
DECL|macro|TX4927_SIO0_SISCISR0_CTSS
mdefine_line|#define TX4927_SIO0_SISCISR0_CTSS                        BM_04_04
DECL|macro|TX4927_SIO0_SISCISR0_RBRKD
mdefine_line|#define TX4927_SIO0_SISCISR0_RBRKD                       BM_03_03
DECL|macro|TX4927_SIO0_SISCISR0_TRDY
mdefine_line|#define TX4927_SIO0_SISCISR0_TRDY                        BM_02_02
DECL|macro|TX4927_SIO0_SISCISR0_TXALS
mdefine_line|#define TX4927_SIO0_SISCISR0_TXALS                       BM_01_01
DECL|macro|TX4927_SIO0_SISCISR0_UBRKD
mdefine_line|#define TX4927_SIO0_SISCISR0_UBRKD                       BM_00_00
DECL|macro|TX4927_SIO0_SIFCR0
mdefine_line|#define TX4927_SIO0_SIFCR0                       0xf310 
DECL|macro|TX4927_SIO0_SIFCR0_RESERVED_16_31
mdefine_line|#define TX4927_SIO0_SIFCR0_RESERVED_16_31                BM_16_31
DECL|macro|TX4927_SIO0_SIFCR0_SWRST
mdefine_line|#define TX4927_SIO0_SIFCR0_SWRST                         BM_16_31
DECL|macro|TX4927_SIO0_SIFCR0_RESERVED_09_14
mdefine_line|#define TX4927_SIO0_SIFCR0_RESERVED_09_14                BM_09_14
DECL|macro|TX4927_SIO0_SIFCR0_RDIL
mdefine_line|#define TX4927_SIO0_SIFCR0_RDIL                          BM_16_31
DECL|macro|TX4927_SIO0_SIFCR0_RDIL_BYTES_1
mdefine_line|#define TX4927_SIO0_SIFCR0_RDIL_BYTES_1                (~BM_07_08)
DECL|macro|TX4927_SIO0_SIFCR0_RDIL_BYTES_4
mdefine_line|#define TX4927_SIO0_SIFCR0_RDIL_BYTES_4                  BM_07_07
DECL|macro|TX4927_SIO0_SIFCR0_RDIL_BYTES_8
mdefine_line|#define TX4927_SIO0_SIFCR0_RDIL_BYTES_8                  BM_08_08
DECL|macro|TX4927_SIO0_SIFCR0_RDIL_BYTES_12
mdefine_line|#define TX4927_SIO0_SIFCR0_RDIL_BYTES_12                 BM_07_08
DECL|macro|TX4927_SIO0_SIFCR0_RESERVED_05_06
mdefine_line|#define TX4927_SIO0_SIFCR0_RESERVED_05_06                BM_05_06
DECL|macro|TX4927_SIO0_SIFCR0_TDIL
mdefine_line|#define TX4927_SIO0_SIFCR0_TDIL                          BM_03_04
DECL|macro|TX4927_SIO0_SIFCR0_TDIL_BYTES_1
mdefine_line|#define TX4927_SIO0_SIFCR0_TDIL_BYTES_1                (~BM_03_04)
DECL|macro|TX4927_SIO0_SIFCR0_TDIL_BYTES_4
mdefine_line|#define TX4927_SIO0_SIFCR0_TDIL_BYTES_4                  BM_03_03
DECL|macro|TX4927_SIO0_SIFCR0_TDIL_BYTES_8
mdefine_line|#define TX4927_SIO0_SIFCR0_TDIL_BYTES_8                  BM_04_04
DECL|macro|TX4927_SIO0_SIFCR0_TDIL_BYTES_0
mdefine_line|#define TX4927_SIO0_SIFCR0_TDIL_BYTES_0                  BM_03_04
DECL|macro|TX4927_SIO0_SIFCR0_TFRST
mdefine_line|#define TX4927_SIO0_SIFCR0_TFRST                         BM_02_02
DECL|macro|TX4927_SIO0_SIFCR0_RFRST
mdefine_line|#define TX4927_SIO0_SIFCR0_RFRST                         BM_01_01
DECL|macro|TX4927_SIO0_SIFCR0_FRSTE
mdefine_line|#define TX4927_SIO0_SIFCR0_FRSTE                         BM_00_00
DECL|macro|TX4927_SIO0_SIFLCR0
mdefine_line|#define TX4927_SIO0_SIFLCR0                      0xf314 
DECL|macro|TX4927_SIO0_SIFLCR0_RESERVED_13_31
mdefine_line|#define TX4927_SIO0_SIFLCR0_RESERVED_13_31               BM_13_31
DECL|macro|TX4927_SIO0_SIFLCR0_RCS
mdefine_line|#define TX4927_SIO0_SIFLCR0_RCS                          BM_12_12
DECL|macro|TX4927_SIO0_SIFLCR0_TES
mdefine_line|#define TX4927_SIO0_SIFLCR0_TES                          BM_11_11
DECL|macro|TX4927_SIO0_SIFLCR0_RESERVED_10_10
mdefine_line|#define TX4927_SIO0_SIFLCR0_RESERVED_10_10               BM_10_10
DECL|macro|TX4927_SIO0_SIFLCR0_RTSSC
mdefine_line|#define TX4927_SIO0_SIFLCR0_RTSSC                        BM_09_09
DECL|macro|TX4927_SIO0_SIFLCR0_RSDE
mdefine_line|#define TX4927_SIO0_SIFLCR0_RSDE                         BM_08_08
DECL|macro|TX4927_SIO0_SIFLCR0_TSDE
mdefine_line|#define TX4927_SIO0_SIFLCR0_TSDE                         BM_07_07
DECL|macro|TX4927_SIO0_SIFLCR0_RESERVED_05_06
mdefine_line|#define TX4927_SIO0_SIFLCR0_RESERVED_05_06               BM_05_06
DECL|macro|TX4927_SIO0_SIFLCR0_RTSTL
mdefine_line|#define TX4927_SIO0_SIFLCR0_RTSTL                        BM_01_04
DECL|macro|TX4927_SIO0_SIFLCR0_TBRK
mdefine_line|#define TX4927_SIO0_SIFLCR0_TBRK                         BM_00_00
DECL|macro|TX4927_SIO0_SIBGR0
mdefine_line|#define TX4927_SIO0_SIBGR0                       0xf318 
DECL|macro|TX4927_SIO0_SIBGR0_RESERVED_10_31
mdefine_line|#define TX4927_SIO0_SIBGR0_RESERVED_10_31                BM_10_31
DECL|macro|TX4927_SIO0_SIBGR0_BCLK
mdefine_line|#define TX4927_SIO0_SIBGR0_BCLK                          BM_08_09
DECL|macro|TX4927_SIO0_SIBGR0_BCLK_T0
mdefine_line|#define TX4927_SIO0_SIBGR0_BCLK_T0                     (~BM_08_09)
DECL|macro|TX4927_SIO0_SIBGR0_BCLK_T2
mdefine_line|#define TX4927_SIO0_SIBGR0_BCLK_T2                       BM_08_08
DECL|macro|TX4927_SIO0_SIBGR0_BCLK_T4
mdefine_line|#define TX4927_SIO0_SIBGR0_BCLK_T4                       BM_09_09
DECL|macro|TX4927_SIO0_SIBGR0_BCLK_T6
mdefine_line|#define TX4927_SIO0_SIBGR0_BCLK_T6                       BM_08_09
DECL|macro|TX4927_SIO0_SIBGR0_BRD
mdefine_line|#define TX4927_SIO0_SIBGR0_BRD                           BM_00_07
DECL|macro|TX4927_SIO0_SITFIF00
mdefine_line|#define TX4927_SIO0_SITFIF00                     0xf31c 
DECL|macro|TX4927_SIO0_SITFIF00_RESERVED_08_31
mdefine_line|#define TX4927_SIO0_SITFIF00_RESERVED_08_31              BM_08_31
DECL|macro|TX4927_SIO0_SITFIF00_TXD
mdefine_line|#define TX4927_SIO0_SITFIF00_TXD                         BM_00_07
DECL|macro|TX4927_SIO0_SIRFIFO0
mdefine_line|#define TX4927_SIO0_SIRFIFO0                     0xf320          
DECL|macro|TX4927_SIO0_SIRFIFO0_RESERVED_08_31
mdefine_line|#define TX4927_SIO0_SIRFIFO0_RESERVED_08_31              BM_08_31
DECL|macro|TX4927_SIO0_SIRFIFO0_RXD
mdefine_line|#define TX4927_SIO0_SIRFIFO0_RXD                         BM_00_07
DECL|macro|TX4927_SIO0_SIRFIFO0
mdefine_line|#define TX4927_SIO0_SIRFIFO0                     0xf320          
DECL|macro|TX4927_SIO0_LIMIT
mdefine_line|#define TX4927_SIO0_LIMIT                        0xf3ff 
multiline_comment|/* TX4927 serial port 1 (32-bit registers) */
DECL|macro|TX4927_SIO1_BASE
mdefine_line|#define TX4927_SIO1_BASE                0xf400 
DECL|macro|TX4927_SIO1_SILCR1
mdefine_line|#define TX4927_SIO1_SILCR1              0xf400 
DECL|macro|TX4927_SIO1_SIDICR1
mdefine_line|#define TX4927_SIO1_SIDICR1             0xf404 
DECL|macro|TX4927_SIO1_SIDISR1
mdefine_line|#define TX4927_SIO1_SIDISR1             0xf408 
DECL|macro|TX4927_SIO1_SISCISR1
mdefine_line|#define TX4927_SIO1_SISCISR1            0xf40c 
DECL|macro|TX4927_SIO1_SIFCR1
mdefine_line|#define TX4927_SIO1_SIFCR1              0xf410 
DECL|macro|TX4927_SIO1_SIFLCR1
mdefine_line|#define TX4927_SIO1_SIFLCR1             0xf414 
DECL|macro|TX4927_SIO1_SIBGR1
mdefine_line|#define TX4927_SIO1_SIBGR1              0xf418 
DECL|macro|TX4927_SIO1_SITFIF01
mdefine_line|#define TX4927_SIO1_SITFIF01            0xf41c 
DECL|macro|TX4927_SIO1_SIRFIFO1
mdefine_line|#define TX4927_SIO1_SIRFIFO1            0xf420 
DECL|macro|TX4927_SIO1_LIMIT
mdefine_line|#define TX4927_SIO1_LIMIT               0xf4ff 
multiline_comment|/* TX4927 parallel port (32-bit registers) */
DECL|macro|TX4927_PIO_BASE
mdefine_line|#define TX4927_PIO_BASE                 0xf500
DECL|macro|TX4927_PIO_PIOD0
mdefine_line|#define TX4927_PIO_PIOD0                0xf500
DECL|macro|TX4927_PIO_PIODI
mdefine_line|#define TX4927_PIO_PIODI                0xf504
DECL|macro|TX4927_PIO_PIODIR
mdefine_line|#define TX4927_PIO_PIODIR               0xf508
DECL|macro|TX4927_PIO_PIOOD
mdefine_line|#define TX4927_PIO_PIOOD                0xf50c
DECL|macro|TX4927_PIO_LIMIT
mdefine_line|#define TX4927_PIO_LIMIT                0xf50f
multiline_comment|/* TX4927 Interrupt Controller (32-bit registers) */
DECL|macro|TX4927_IRC_BASE
mdefine_line|#define TX4927_IRC_BASE                 0xf510
DECL|macro|TX4927_IRC_IRFLAG0
mdefine_line|#define TX4927_IRC_IRFLAG0              0xf510
DECL|macro|TX4927_IRC_IRFLAG1
mdefine_line|#define TX4927_IRC_IRFLAG1              0xf514
DECL|macro|TX4927_IRC_IRPOL
mdefine_line|#define TX4927_IRC_IRPOL                0xf518
DECL|macro|TX4927_IRC_IRRCNT
mdefine_line|#define TX4927_IRC_IRRCNT               0xf51c
DECL|macro|TX4927_IRC_IRMASKINT
mdefine_line|#define TX4927_IRC_IRMASKINT            0xf520
DECL|macro|TX4927_IRC_IRMASKEXT
mdefine_line|#define TX4927_IRC_IRMASKEXT            0xf524
DECL|macro|TX4927_IRC_IRDEN
mdefine_line|#define TX4927_IRC_IRDEN                0xf600
DECL|macro|TX4927_IRC_IRDM0
mdefine_line|#define TX4927_IRC_IRDM0                0xf604
DECL|macro|TX4927_IRC_IRDM1
mdefine_line|#define TX4927_IRC_IRDM1                0xf608
DECL|macro|TX4927_IRC_IRLVL0
mdefine_line|#define TX4927_IRC_IRLVL0               0xf610
DECL|macro|TX4927_IRC_IRLVL1
mdefine_line|#define TX4927_IRC_IRLVL1               0xf614
DECL|macro|TX4927_IRC_IRLVL2
mdefine_line|#define TX4927_IRC_IRLVL2               0xf618
DECL|macro|TX4927_IRC_IRLVL3
mdefine_line|#define TX4927_IRC_IRLVL3               0xf61c
DECL|macro|TX4927_IRC_IRLVL4
mdefine_line|#define TX4927_IRC_IRLVL4               0xf620
DECL|macro|TX4927_IRC_IRLVL5
mdefine_line|#define TX4927_IRC_IRLVL5               0xf624
DECL|macro|TX4927_IRC_IRLVL6
mdefine_line|#define TX4927_IRC_IRLVL6               0xf628
DECL|macro|TX4927_IRC_IRLVL7
mdefine_line|#define TX4927_IRC_IRLVL7               0xf62c
DECL|macro|TX4927_IRC_IRMSK
mdefine_line|#define TX4927_IRC_IRMSK                0xf640
DECL|macro|TX4927_IRC_IREDC
mdefine_line|#define TX4927_IRC_IREDC                0xf660
DECL|macro|TX4927_IRC_IRPND
mdefine_line|#define TX4927_IRC_IRPND                0xf680
DECL|macro|TX4927_IRC_IRCS
mdefine_line|#define TX4927_IRC_IRCS                 0xf6a0
DECL|macro|TX4927_IRC_LIMIT
mdefine_line|#define TX4927_IRC_LIMIT                0xf6ff
multiline_comment|/* TX4927 AC-link controller (32-bit registers) */
DECL|macro|TX4927_ACLC_BASE
mdefine_line|#define TX4927_ACLC_BASE                0xf700
DECL|macro|TX4927_ACLC_ACCTLEN
mdefine_line|#define TX4927_ACLC_ACCTLEN             0xf700
DECL|macro|TX4927_ACLC_ACCTLDIS
mdefine_line|#define TX4927_ACLC_ACCTLDIS            0xf704
DECL|macro|TX4927_ACLC_ACREGACC
mdefine_line|#define TX4927_ACLC_ACREGACC            0xf708
DECL|macro|TX4927_ACLC_ACINTSTS
mdefine_line|#define TX4927_ACLC_ACINTSTS            0xf710
DECL|macro|TX4927_ACLC_ACINTMSTS
mdefine_line|#define TX4927_ACLC_ACINTMSTS           0xf714
DECL|macro|TX4927_ACLC_ACINTEN
mdefine_line|#define TX4927_ACLC_ACINTEN             0xf718
DECL|macro|TX4927_ACLC_ACINTDIS
mdefine_line|#define TX4927_ACLC_ACINTDIS            0xf71c
DECL|macro|TX4927_ACLC_ACSEMAPH
mdefine_line|#define TX4927_ACLC_ACSEMAPH            0xf720
DECL|macro|TX4927_ACLC_ACGPIDAT
mdefine_line|#define TX4927_ACLC_ACGPIDAT            0xf740
DECL|macro|TX4927_ACLC_ACGPODAT
mdefine_line|#define TX4927_ACLC_ACGPODAT            0xf744
DECL|macro|TX4927_ACLC_ACSLTEN
mdefine_line|#define TX4927_ACLC_ACSLTEN             0xf748
DECL|macro|TX4927_ACLC_ACSLTDIS
mdefine_line|#define TX4927_ACLC_ACSLTDIS            0xf74c
DECL|macro|TX4927_ACLC_ACFIFOSTS
mdefine_line|#define TX4927_ACLC_ACFIFOSTS           0xf750
DECL|macro|TX4927_ACLC_ACDMASTS
mdefine_line|#define TX4927_ACLC_ACDMASTS            0xf780
DECL|macro|TX4927_ACLC_ACDMASEL
mdefine_line|#define TX4927_ACLC_ACDMASEL            0xf784
DECL|macro|TX4927_ACLC_ACAUDODAT
mdefine_line|#define TX4927_ACLC_ACAUDODAT           0xf7a0
DECL|macro|TX4927_ACLC_ACSURRDAT
mdefine_line|#define TX4927_ACLC_ACSURRDAT           0xf7a4
DECL|macro|TX4927_ACLC_ACCENTDAT
mdefine_line|#define TX4927_ACLC_ACCENTDAT           0xf7a8
DECL|macro|TX4927_ACLC_ACLFEDAT
mdefine_line|#define TX4927_ACLC_ACLFEDAT            0xf7ac
DECL|macro|TX4927_ACLC_ACAUDIDAT
mdefine_line|#define TX4927_ACLC_ACAUDIDAT           0xf7b0
DECL|macro|TX4927_ACLC_ACMODODAT
mdefine_line|#define TX4927_ACLC_ACMODODAT           0xf7b8
DECL|macro|TX4927_ACLC_ACMODIDAT
mdefine_line|#define TX4927_ACLC_ACMODIDAT           0xf7bc
DECL|macro|TX4927_ACLC_ACREVID
mdefine_line|#define TX4927_ACLC_ACREVID             0xf7fc
DECL|macro|TX4927_ACLC_LIMIT
mdefine_line|#define TX4927_ACLC_LIMIT               0xf7ff
DECL|macro|TX4927_REG
mdefine_line|#define TX4927_REG(x) ((TX4927_BASE)+(x))
DECL|macro|TX4927_RD08
mdefine_line|#define TX4927_RD08( reg      )   (*(vu08*)(reg))
DECL|macro|TX4927_WR08
mdefine_line|#define TX4927_WR08( reg, val )  ((*(vu08*)(reg))=(val))
DECL|macro|TX4927_RD16
mdefine_line|#define TX4927_RD16( reg      )   (*(vu16*)(reg))
DECL|macro|TX4927_WR16
mdefine_line|#define TX4927_WR16( reg, val )  ((*(vu16*)(reg))=(val))
DECL|macro|TX4927_RD32
mdefine_line|#define TX4927_RD32( reg      )   (*(vu32*)(reg))
DECL|macro|TX4927_WR32
mdefine_line|#define TX4927_WR32( reg, val )  ((*(vu32*)(reg))=(val))
DECL|macro|TX4927_RD64
mdefine_line|#define TX4927_RD64( reg      )   (*(vu64*)(reg))
DECL|macro|TX4927_WR64
mdefine_line|#define TX4927_WR64( reg, val )  ((*(vu64*)(reg))=(val))
DECL|macro|TX4927_RD
mdefine_line|#define TX4927_RD( reg      ) TX4927_RD32( reg )
DECL|macro|TX4927_WR
mdefine_line|#define TX4927_WR( reg, val ) TX4927_WR32( reg, val )
DECL|macro|MI8259_IRQ_ISA_RAW_BEG
mdefine_line|#define MI8259_IRQ_ISA_RAW_BEG   0    /* optional backplane i8259 */
DECL|macro|MI8259_IRQ_ISA_RAW_END
mdefine_line|#define MI8259_IRQ_ISA_RAW_END  15
DECL|macro|TX4927_IRQ_CP0_RAW_BEG
mdefine_line|#define TX4927_IRQ_CP0_RAW_BEG   0    /* tx4927 cpu built-in cp0 */
DECL|macro|TX4927_IRQ_CP0_RAW_END
mdefine_line|#define TX4927_IRQ_CP0_RAW_END   7
DECL|macro|TX4927_IRQ_PIC_RAW_BEG
mdefine_line|#define TX4927_IRQ_PIC_RAW_BEG   0    /* tx4927 cpu build-in pic */
DECL|macro|TX4927_IRQ_PIC_RAW_END
mdefine_line|#define TX4927_IRQ_PIC_RAW_END  31
DECL|macro|MI8259_IRQ_ISA_BEG
mdefine_line|#define MI8259_IRQ_ISA_BEG                          MI8259_IRQ_ISA_RAW_BEG   /*  0 */
DECL|macro|MI8259_IRQ_ISA_END
mdefine_line|#define MI8259_IRQ_ISA_END                          MI8259_IRQ_ISA_RAW_END   /* 15 */
DECL|macro|TX4927_IRQ_CP0_BEG
mdefine_line|#define TX4927_IRQ_CP0_BEG  ((MI8259_IRQ_ISA_END+1)+TX4927_IRQ_CP0_RAW_BEG)  /* 16 */
DECL|macro|TX4927_IRQ_CP0_END
mdefine_line|#define TX4927_IRQ_CP0_END  ((MI8259_IRQ_ISA_END+1)+TX4927_IRQ_CP0_RAW_END)  /* 23 */
DECL|macro|TX4927_IRQ_PIC_BEG
mdefine_line|#define TX4927_IRQ_PIC_BEG  ((TX4927_IRQ_CP0_END+1)+TX4927_IRQ_PIC_RAW_BEG)  /* 24 */
DECL|macro|TX4927_IRQ_PIC_END
mdefine_line|#define TX4927_IRQ_PIC_END  ((TX4927_IRQ_CP0_END+1)+TX4927_IRQ_PIC_RAW_END)  /* 55 */
DECL|macro|TX4927_IRQ_USER0
mdefine_line|#define TX4927_IRQ_USER0            (TX4927_IRQ_CP0_BEG+0)
DECL|macro|TX4927_IRQ_USER1
mdefine_line|#define TX4927_IRQ_USER1            (TX4927_IRQ_CP0_BEG+1)
DECL|macro|TX4927_IRQ_NEST_PIC_ON_CP0
mdefine_line|#define TX4927_IRQ_NEST_PIC_ON_CP0  (TX4927_IRQ_CP0_BEG+2)
DECL|macro|TX4927_IRQ_CPU_TIMER
mdefine_line|#define TX4927_IRQ_CPU_TIMER        (TX4927_IRQ_CP0_BEG+7)
DECL|macro|TX4927_IRQ_NEST_EXT_ON_PIC
mdefine_line|#define TX4927_IRQ_NEST_EXT_ON_PIC  (TX4927_IRQ_PIC_BEG+3)
macro_line|#endif /* __ASM_TX4927_TX4927_H */
eof
