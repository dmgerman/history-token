macro_line|#ifndef __CS461X_H
DECL|macro|__CS461X_H
mdefine_line|#define __CS461X_H
multiline_comment|/*&n; *  Copyright (c) by Cirrus Logic Corporation &lt;pcaudio@crystal.cirrus.com&gt;&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *  Definitions for Cirrus Logic CS461x chips&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
macro_line|#ifndef PCI_VENDOR_ID_CIRRUS
DECL|macro|PCI_VENDOR_ID_CIRRUS
mdefine_line|#define PCI_VENDOR_ID_CIRRUS            0x1013
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_CIRRUS_4610
DECL|macro|PCI_DEVICE_ID_CIRRUS_4610
mdefine_line|#define PCI_DEVICE_ID_CIRRUS_4610       0x6001
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_CIRRUS_4612
DECL|macro|PCI_DEVICE_ID_CIRRUS_4612
mdefine_line|#define PCI_DEVICE_ID_CIRRUS_4612       0x6003
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_CIRRUS_4615
DECL|macro|PCI_DEVICE_ID_CIRRUS_4615
mdefine_line|#define PCI_DEVICE_ID_CIRRUS_4615       0x6004
macro_line|#endif
multiline_comment|/*&n; *  Direct registers&n; */
multiline_comment|/*&n; *  The following define the offsets of the registers accessed via base address&n; *  register zero on the CS461x part.&n; */
DECL|macro|BA0_HISR
mdefine_line|#define BA0_HISR&t;&t;&t;&t;0x00000000
DECL|macro|BA0_HSR0
mdefine_line|#define BA0_HSR0                                0x00000004
DECL|macro|BA0_HICR
mdefine_line|#define BA0_HICR                                0x00000008
DECL|macro|BA0_DMSR
mdefine_line|#define BA0_DMSR                                0x00000100
DECL|macro|BA0_HSAR
mdefine_line|#define BA0_HSAR                                0x00000110
DECL|macro|BA0_HDAR
mdefine_line|#define BA0_HDAR                                0x00000114
DECL|macro|BA0_HDMR
mdefine_line|#define BA0_HDMR                                0x00000118
DECL|macro|BA0_HDCR
mdefine_line|#define BA0_HDCR                                0x0000011C
DECL|macro|BA0_PFMC
mdefine_line|#define BA0_PFMC                                0x00000200
DECL|macro|BA0_PFCV1
mdefine_line|#define BA0_PFCV1                               0x00000204
DECL|macro|BA0_PFCV2
mdefine_line|#define BA0_PFCV2                               0x00000208
DECL|macro|BA0_PCICFG00
mdefine_line|#define BA0_PCICFG00                            0x00000300
DECL|macro|BA0_PCICFG04
mdefine_line|#define BA0_PCICFG04                            0x00000304
DECL|macro|BA0_PCICFG08
mdefine_line|#define BA0_PCICFG08                            0x00000308
DECL|macro|BA0_PCICFG0C
mdefine_line|#define BA0_PCICFG0C                            0x0000030C
DECL|macro|BA0_PCICFG10
mdefine_line|#define BA0_PCICFG10                            0x00000310
DECL|macro|BA0_PCICFG14
mdefine_line|#define BA0_PCICFG14                            0x00000314
DECL|macro|BA0_PCICFG18
mdefine_line|#define BA0_PCICFG18                            0x00000318
DECL|macro|BA0_PCICFG1C
mdefine_line|#define BA0_PCICFG1C                            0x0000031C
DECL|macro|BA0_PCICFG20
mdefine_line|#define BA0_PCICFG20                            0x00000320
DECL|macro|BA0_PCICFG24
mdefine_line|#define BA0_PCICFG24                            0x00000324
DECL|macro|BA0_PCICFG28
mdefine_line|#define BA0_PCICFG28                            0x00000328
DECL|macro|BA0_PCICFG2C
mdefine_line|#define BA0_PCICFG2C                            0x0000032C
DECL|macro|BA0_PCICFG30
mdefine_line|#define BA0_PCICFG30                            0x00000330
DECL|macro|BA0_PCICFG34
mdefine_line|#define BA0_PCICFG34                            0x00000334
DECL|macro|BA0_PCICFG38
mdefine_line|#define BA0_PCICFG38                            0x00000338
DECL|macro|BA0_PCICFG3C
mdefine_line|#define BA0_PCICFG3C                            0x0000033C
DECL|macro|BA0_CLKCR1
mdefine_line|#define BA0_CLKCR1                              0x00000400
DECL|macro|BA0_CLKCR2
mdefine_line|#define BA0_CLKCR2                              0x00000404
DECL|macro|BA0_PLLM
mdefine_line|#define BA0_PLLM                                0x00000408
DECL|macro|BA0_PLLCC
mdefine_line|#define BA0_PLLCC                               0x0000040C
DECL|macro|BA0_FRR
mdefine_line|#define BA0_FRR                                 0x00000410 
DECL|macro|BA0_CFL1
mdefine_line|#define BA0_CFL1                                0x00000414
DECL|macro|BA0_CFL2
mdefine_line|#define BA0_CFL2                                0x00000418
DECL|macro|BA0_SERMC1
mdefine_line|#define BA0_SERMC1                              0x00000420
DECL|macro|BA0_SERMC2
mdefine_line|#define BA0_SERMC2                              0x00000424
DECL|macro|BA0_SERC1
mdefine_line|#define BA0_SERC1                               0x00000428
DECL|macro|BA0_SERC2
mdefine_line|#define BA0_SERC2                               0x0000042C
DECL|macro|BA0_SERC3
mdefine_line|#define BA0_SERC3                               0x00000430
DECL|macro|BA0_SERC4
mdefine_line|#define BA0_SERC4                               0x00000434
DECL|macro|BA0_SERC5
mdefine_line|#define BA0_SERC5                               0x00000438
DECL|macro|BA0_SERBSP
mdefine_line|#define BA0_SERBSP                              0x0000043C
DECL|macro|BA0_SERBST
mdefine_line|#define BA0_SERBST                              0x00000440
DECL|macro|BA0_SERBCM
mdefine_line|#define BA0_SERBCM                              0x00000444
DECL|macro|BA0_SERBAD
mdefine_line|#define BA0_SERBAD                              0x00000448
DECL|macro|BA0_SERBCF
mdefine_line|#define BA0_SERBCF                              0x0000044C
DECL|macro|BA0_SERBWP
mdefine_line|#define BA0_SERBWP                              0x00000450
DECL|macro|BA0_SERBRP
mdefine_line|#define BA0_SERBRP                              0x00000454
macro_line|#ifndef NO_CS4612
DECL|macro|BA0_ASER_FADDR
mdefine_line|#define BA0_ASER_FADDR                          0x00000458
macro_line|#endif
DECL|macro|BA0_ACCTL
mdefine_line|#define BA0_ACCTL                               0x00000460
DECL|macro|BA0_ACSTS
mdefine_line|#define BA0_ACSTS                               0x00000464
DECL|macro|BA0_ACOSV
mdefine_line|#define BA0_ACOSV                               0x00000468
DECL|macro|BA0_ACCAD
mdefine_line|#define BA0_ACCAD                               0x0000046C
DECL|macro|BA0_ACCDA
mdefine_line|#define BA0_ACCDA                               0x00000470
DECL|macro|BA0_ACISV
mdefine_line|#define BA0_ACISV                               0x00000474
DECL|macro|BA0_ACSAD
mdefine_line|#define BA0_ACSAD                               0x00000478
DECL|macro|BA0_ACSDA
mdefine_line|#define BA0_ACSDA                               0x0000047C
DECL|macro|BA0_JSPT
mdefine_line|#define BA0_JSPT                                0x00000480
DECL|macro|BA0_JSCTL
mdefine_line|#define BA0_JSCTL                               0x00000484
DECL|macro|BA0_JSC1
mdefine_line|#define BA0_JSC1                                0x00000488
DECL|macro|BA0_JSC2
mdefine_line|#define BA0_JSC2                                0x0000048C
DECL|macro|BA0_MIDCR
mdefine_line|#define BA0_MIDCR                               0x00000490
DECL|macro|BA0_MIDSR
mdefine_line|#define BA0_MIDSR                               0x00000494
DECL|macro|BA0_MIDWP
mdefine_line|#define BA0_MIDWP                               0x00000498
DECL|macro|BA0_MIDRP
mdefine_line|#define BA0_MIDRP                               0x0000049C
DECL|macro|BA0_JSIO
mdefine_line|#define BA0_JSIO                                0x000004A0
macro_line|#ifndef NO_CS4612
DECL|macro|BA0_ASER_MASTER
mdefine_line|#define BA0_ASER_MASTER                         0x000004A4
macro_line|#endif
DECL|macro|BA0_CFGI
mdefine_line|#define BA0_CFGI                                0x000004B0
DECL|macro|BA0_SSVID
mdefine_line|#define BA0_SSVID                               0x000004B4
DECL|macro|BA0_GPIOR
mdefine_line|#define BA0_GPIOR                               0x000004B8
macro_line|#ifndef NO_CS4612
DECL|macro|BA0_EGPIODR
mdefine_line|#define BA0_EGPIODR                             0x000004BC
DECL|macro|BA0_EGPIOPTR
mdefine_line|#define BA0_EGPIOPTR                            0x000004C0
DECL|macro|BA0_EGPIOTR
mdefine_line|#define BA0_EGPIOTR                             0x000004C4
DECL|macro|BA0_EGPIOWR
mdefine_line|#define BA0_EGPIOWR                             0x000004C8
DECL|macro|BA0_EGPIOSR
mdefine_line|#define BA0_EGPIOSR                             0x000004CC
DECL|macro|BA0_SERC6
mdefine_line|#define BA0_SERC6                               0x000004D0
DECL|macro|BA0_SERC7
mdefine_line|#define BA0_SERC7                               0x000004D4
DECL|macro|BA0_SERACC
mdefine_line|#define BA0_SERACC                              0x000004D8
DECL|macro|BA0_ACCTL2
mdefine_line|#define BA0_ACCTL2                              0x000004E0
DECL|macro|BA0_ACSTS2
mdefine_line|#define BA0_ACSTS2                              0x000004E4
DECL|macro|BA0_ACOSV2
mdefine_line|#define BA0_ACOSV2                              0x000004E8
DECL|macro|BA0_ACCAD2
mdefine_line|#define BA0_ACCAD2                              0x000004EC
DECL|macro|BA0_ACCDA2
mdefine_line|#define BA0_ACCDA2                              0x000004F0
DECL|macro|BA0_ACISV2
mdefine_line|#define BA0_ACISV2                              0x000004F4
DECL|macro|BA0_ACSAD2
mdefine_line|#define BA0_ACSAD2                              0x000004F8
DECL|macro|BA0_ACSDA2
mdefine_line|#define BA0_ACSDA2                              0x000004FC
DECL|macro|BA0_IOTAC0
mdefine_line|#define BA0_IOTAC0                              0x00000500
DECL|macro|BA0_IOTAC1
mdefine_line|#define BA0_IOTAC1                              0x00000504
DECL|macro|BA0_IOTAC2
mdefine_line|#define BA0_IOTAC2                              0x00000508
DECL|macro|BA0_IOTAC3
mdefine_line|#define BA0_IOTAC3                              0x0000050C
DECL|macro|BA0_IOTAC4
mdefine_line|#define BA0_IOTAC4                              0x00000510
DECL|macro|BA0_IOTAC5
mdefine_line|#define BA0_IOTAC5                              0x00000514
DECL|macro|BA0_IOTAC6
mdefine_line|#define BA0_IOTAC6                              0x00000518
DECL|macro|BA0_IOTAC7
mdefine_line|#define BA0_IOTAC7                              0x0000051C
DECL|macro|BA0_IOTAC8
mdefine_line|#define BA0_IOTAC8                              0x00000520
DECL|macro|BA0_IOTAC9
mdefine_line|#define BA0_IOTAC9                              0x00000524
DECL|macro|BA0_IOTAC10
mdefine_line|#define BA0_IOTAC10                             0x00000528
DECL|macro|BA0_IOTAC11
mdefine_line|#define BA0_IOTAC11                             0x0000052C
DECL|macro|BA0_IOTFR0
mdefine_line|#define BA0_IOTFR0                              0x00000540
DECL|macro|BA0_IOTFR1
mdefine_line|#define BA0_IOTFR1                              0x00000544
DECL|macro|BA0_IOTFR2
mdefine_line|#define BA0_IOTFR2                              0x00000548
DECL|macro|BA0_IOTFR3
mdefine_line|#define BA0_IOTFR3                              0x0000054C
DECL|macro|BA0_IOTFR4
mdefine_line|#define BA0_IOTFR4                              0x00000550
DECL|macro|BA0_IOTFR5
mdefine_line|#define BA0_IOTFR5                              0x00000554
DECL|macro|BA0_IOTFR6
mdefine_line|#define BA0_IOTFR6                              0x00000558
DECL|macro|BA0_IOTFR7
mdefine_line|#define BA0_IOTFR7                              0x0000055C
DECL|macro|BA0_IOTFIFO
mdefine_line|#define BA0_IOTFIFO                             0x00000580
DECL|macro|BA0_IOTRRD
mdefine_line|#define BA0_IOTRRD                              0x00000584
DECL|macro|BA0_IOTFP
mdefine_line|#define BA0_IOTFP                               0x00000588
DECL|macro|BA0_IOTCR
mdefine_line|#define BA0_IOTCR                               0x0000058C
DECL|macro|BA0_DPCID
mdefine_line|#define BA0_DPCID                               0x00000590
DECL|macro|BA0_DPCIA
mdefine_line|#define BA0_DPCIA                               0x00000594
DECL|macro|BA0_DPCIC
mdefine_line|#define BA0_DPCIC                               0x00000598
DECL|macro|BA0_PCPCIR
mdefine_line|#define BA0_PCPCIR                              0x00000600
DECL|macro|BA0_PCPCIG
mdefine_line|#define BA0_PCPCIG                              0x00000604
DECL|macro|BA0_PCPCIEN
mdefine_line|#define BA0_PCPCIEN                             0x00000608
DECL|macro|BA0_EPCIPMC
mdefine_line|#define BA0_EPCIPMC                             0x00000610
macro_line|#endif
multiline_comment|/*&n; *  The following define the offsets of the registers and memories accessed via&n; *  base address register one on the CS461x part.&n; */
DECL|macro|BA1_SP_DMEM0
mdefine_line|#define BA1_SP_DMEM0                            0x00000000
DECL|macro|BA1_SP_DMEM1
mdefine_line|#define BA1_SP_DMEM1                            0x00010000
DECL|macro|BA1_SP_PMEM
mdefine_line|#define BA1_SP_PMEM                             0x00020000
DECL|macro|BA1_SP_REG
mdefine_line|#define BA1_SP_REG&t;&t;&t;&t;0x00030000
DECL|macro|BA1_SPCR
mdefine_line|#define BA1_SPCR                                0x00030000
DECL|macro|BA1_DREG
mdefine_line|#define BA1_DREG                                0x00030004
DECL|macro|BA1_DSRWP
mdefine_line|#define BA1_DSRWP                               0x00030008
DECL|macro|BA1_TWPR
mdefine_line|#define BA1_TWPR                                0x0003000C
DECL|macro|BA1_SPWR
mdefine_line|#define BA1_SPWR                                0x00030010
DECL|macro|BA1_SPIR
mdefine_line|#define BA1_SPIR                                0x00030014
DECL|macro|BA1_FGR1
mdefine_line|#define BA1_FGR1                                0x00030020
DECL|macro|BA1_SPCS
mdefine_line|#define BA1_SPCS                                0x00030028
DECL|macro|BA1_SDSR
mdefine_line|#define BA1_SDSR                                0x0003002C
DECL|macro|BA1_FRMT
mdefine_line|#define BA1_FRMT                                0x00030030
DECL|macro|BA1_FRCC
mdefine_line|#define BA1_FRCC                                0x00030034
DECL|macro|BA1_FRSC
mdefine_line|#define BA1_FRSC                                0x00030038
DECL|macro|BA1_OMNI_MEM
mdefine_line|#define BA1_OMNI_MEM                            0x000E0000
multiline_comment|/*&n; *  The following defines are for the flags in the host interrupt status&n; *  register.&n; */
DECL|macro|HISR_VC_MASK
mdefine_line|#define HISR_VC_MASK                            0x0000FFFF
DECL|macro|HISR_VC0
mdefine_line|#define HISR_VC0                                0x00000001
DECL|macro|HISR_VC1
mdefine_line|#define HISR_VC1                                0x00000002
DECL|macro|HISR_VC2
mdefine_line|#define HISR_VC2                                0x00000004
DECL|macro|HISR_VC3
mdefine_line|#define HISR_VC3                                0x00000008
DECL|macro|HISR_VC4
mdefine_line|#define HISR_VC4                                0x00000010
DECL|macro|HISR_VC5
mdefine_line|#define HISR_VC5                                0x00000020
DECL|macro|HISR_VC6
mdefine_line|#define HISR_VC6                                0x00000040
DECL|macro|HISR_VC7
mdefine_line|#define HISR_VC7                                0x00000080
DECL|macro|HISR_VC8
mdefine_line|#define HISR_VC8                                0x00000100
DECL|macro|HISR_VC9
mdefine_line|#define HISR_VC9                                0x00000200
DECL|macro|HISR_VC10
mdefine_line|#define HISR_VC10                               0x00000400
DECL|macro|HISR_VC11
mdefine_line|#define HISR_VC11                               0x00000800
DECL|macro|HISR_VC12
mdefine_line|#define HISR_VC12                               0x00001000
DECL|macro|HISR_VC13
mdefine_line|#define HISR_VC13                               0x00002000
DECL|macro|HISR_VC14
mdefine_line|#define HISR_VC14                               0x00004000
DECL|macro|HISR_VC15
mdefine_line|#define HISR_VC15                               0x00008000
DECL|macro|HISR_INT0
mdefine_line|#define HISR_INT0                               0x00010000
DECL|macro|HISR_INT1
mdefine_line|#define HISR_INT1                               0x00020000
DECL|macro|HISR_DMAI
mdefine_line|#define HISR_DMAI                               0x00040000
DECL|macro|HISR_FROVR
mdefine_line|#define HISR_FROVR                              0x00080000
DECL|macro|HISR_MIDI
mdefine_line|#define HISR_MIDI                               0x00100000
macro_line|#ifdef NO_CS4612
DECL|macro|HISR_RESERVED
mdefine_line|#define HISR_RESERVED                           0x0FE00000
macro_line|#else
DECL|macro|HISR_SBINT
mdefine_line|#define HISR_SBINT                              0x00200000
DECL|macro|HISR_RESERVED
mdefine_line|#define HISR_RESERVED                           0x0FC00000
macro_line|#endif
DECL|macro|HISR_H0P
mdefine_line|#define HISR_H0P                                0x40000000
DECL|macro|HISR_INTENA
mdefine_line|#define HISR_INTENA                             0x80000000
multiline_comment|/*&n; *  The following defines are for the flags in the host signal register 0.&n; */
DECL|macro|HSR0_VC_MASK
mdefine_line|#define HSR0_VC_MASK                            0xFFFFFFFF
DECL|macro|HSR0_VC16
mdefine_line|#define HSR0_VC16                               0x00000001
DECL|macro|HSR0_VC17
mdefine_line|#define HSR0_VC17                               0x00000002
DECL|macro|HSR0_VC18
mdefine_line|#define HSR0_VC18                               0x00000004
DECL|macro|HSR0_VC19
mdefine_line|#define HSR0_VC19                               0x00000008
DECL|macro|HSR0_VC20
mdefine_line|#define HSR0_VC20                               0x00000010
DECL|macro|HSR0_VC21
mdefine_line|#define HSR0_VC21                               0x00000020
DECL|macro|HSR0_VC22
mdefine_line|#define HSR0_VC22                               0x00000040
DECL|macro|HSR0_VC23
mdefine_line|#define HSR0_VC23                               0x00000080
DECL|macro|HSR0_VC24
mdefine_line|#define HSR0_VC24                               0x00000100
DECL|macro|HSR0_VC25
mdefine_line|#define HSR0_VC25                               0x00000200
DECL|macro|HSR0_VC26
mdefine_line|#define HSR0_VC26                               0x00000400
DECL|macro|HSR0_VC27
mdefine_line|#define HSR0_VC27                               0x00000800
DECL|macro|HSR0_VC28
mdefine_line|#define HSR0_VC28                               0x00001000
DECL|macro|HSR0_VC29
mdefine_line|#define HSR0_VC29                               0x00002000
DECL|macro|HSR0_VC30
mdefine_line|#define HSR0_VC30                               0x00004000
DECL|macro|HSR0_VC31
mdefine_line|#define HSR0_VC31                               0x00008000
DECL|macro|HSR0_VC32
mdefine_line|#define HSR0_VC32                               0x00010000
DECL|macro|HSR0_VC33
mdefine_line|#define HSR0_VC33                               0x00020000
DECL|macro|HSR0_VC34
mdefine_line|#define HSR0_VC34                               0x00040000
DECL|macro|HSR0_VC35
mdefine_line|#define HSR0_VC35                               0x00080000
DECL|macro|HSR0_VC36
mdefine_line|#define HSR0_VC36                               0x00100000
DECL|macro|HSR0_VC37
mdefine_line|#define HSR0_VC37                               0x00200000
DECL|macro|HSR0_VC38
mdefine_line|#define HSR0_VC38                               0x00400000
DECL|macro|HSR0_VC39
mdefine_line|#define HSR0_VC39                               0x00800000
DECL|macro|HSR0_VC40
mdefine_line|#define HSR0_VC40                               0x01000000
DECL|macro|HSR0_VC41
mdefine_line|#define HSR0_VC41                               0x02000000
DECL|macro|HSR0_VC42
mdefine_line|#define HSR0_VC42                               0x04000000
DECL|macro|HSR0_VC43
mdefine_line|#define HSR0_VC43                               0x08000000
DECL|macro|HSR0_VC44
mdefine_line|#define HSR0_VC44                               0x10000000
DECL|macro|HSR0_VC45
mdefine_line|#define HSR0_VC45                               0x20000000
DECL|macro|HSR0_VC46
mdefine_line|#define HSR0_VC46                               0x40000000
DECL|macro|HSR0_VC47
mdefine_line|#define HSR0_VC47                               0x80000000
multiline_comment|/*&n; *  The following defines are for the flags in the host interrupt control&n; *  register.&n; */
DECL|macro|HICR_IEV
mdefine_line|#define HICR_IEV                                0x00000001
DECL|macro|HICR_CHGM
mdefine_line|#define HICR_CHGM                               0x00000002
multiline_comment|/*&n; *  The following defines are for the flags in the DMA status register.&n; */
DECL|macro|DMSR_HP
mdefine_line|#define DMSR_HP                                 0x00000001
DECL|macro|DMSR_HR
mdefine_line|#define DMSR_HR                                 0x00000002
DECL|macro|DMSR_SP
mdefine_line|#define DMSR_SP                                 0x00000004
DECL|macro|DMSR_SR
mdefine_line|#define DMSR_SR                                 0x00000008
multiline_comment|/*&n; *  The following defines are for the flags in the host DMA source address&n; *  register.&n; */
DECL|macro|HSAR_HOST_ADDR_MASK
mdefine_line|#define HSAR_HOST_ADDR_MASK                     0xFFFFFFFF
DECL|macro|HSAR_DSP_ADDR_MASK
mdefine_line|#define HSAR_DSP_ADDR_MASK                      0x0000FFFF
DECL|macro|HSAR_MEMID_MASK
mdefine_line|#define HSAR_MEMID_MASK                         0x000F0000
DECL|macro|HSAR_MEMID_SP_DMEM0
mdefine_line|#define HSAR_MEMID_SP_DMEM0                     0x00000000
DECL|macro|HSAR_MEMID_SP_DMEM1
mdefine_line|#define HSAR_MEMID_SP_DMEM1                     0x00010000
DECL|macro|HSAR_MEMID_SP_PMEM
mdefine_line|#define HSAR_MEMID_SP_PMEM                      0x00020000
DECL|macro|HSAR_MEMID_SP_DEBUG
mdefine_line|#define HSAR_MEMID_SP_DEBUG                     0x00030000
DECL|macro|HSAR_MEMID_OMNI_MEM
mdefine_line|#define HSAR_MEMID_OMNI_MEM                     0x000E0000
DECL|macro|HSAR_END
mdefine_line|#define HSAR_END                                0x40000000
DECL|macro|HSAR_ERR
mdefine_line|#define HSAR_ERR                                0x80000000
multiline_comment|/*&n; *  The following defines are for the flags in the host DMA destination address&n; *  register.&n; */
DECL|macro|HDAR_HOST_ADDR_MASK
mdefine_line|#define HDAR_HOST_ADDR_MASK                     0xFFFFFFFF
DECL|macro|HDAR_DSP_ADDR_MASK
mdefine_line|#define HDAR_DSP_ADDR_MASK                      0x0000FFFF
DECL|macro|HDAR_MEMID_MASK
mdefine_line|#define HDAR_MEMID_MASK                         0x000F0000
DECL|macro|HDAR_MEMID_SP_DMEM0
mdefine_line|#define HDAR_MEMID_SP_DMEM0                     0x00000000
DECL|macro|HDAR_MEMID_SP_DMEM1
mdefine_line|#define HDAR_MEMID_SP_DMEM1                     0x00010000
DECL|macro|HDAR_MEMID_SP_PMEM
mdefine_line|#define HDAR_MEMID_SP_PMEM                      0x00020000
DECL|macro|HDAR_MEMID_SP_DEBUG
mdefine_line|#define HDAR_MEMID_SP_DEBUG                     0x00030000
DECL|macro|HDAR_MEMID_OMNI_MEM
mdefine_line|#define HDAR_MEMID_OMNI_MEM                     0x000E0000
DECL|macro|HDAR_END
mdefine_line|#define HDAR_END                                0x40000000
DECL|macro|HDAR_ERR
mdefine_line|#define HDAR_ERR                                0x80000000
multiline_comment|/*&n; *  The following defines are for the flags in the host DMA control register.&n; */
DECL|macro|HDMR_AC_MASK
mdefine_line|#define HDMR_AC_MASK                            0x0000F000
DECL|macro|HDMR_AC_8_16
mdefine_line|#define HDMR_AC_8_16                            0x00001000
DECL|macro|HDMR_AC_M_S
mdefine_line|#define HDMR_AC_M_S                             0x00002000
DECL|macro|HDMR_AC_B_L
mdefine_line|#define HDMR_AC_B_L                             0x00004000
DECL|macro|HDMR_AC_S_U
mdefine_line|#define HDMR_AC_S_U                             0x00008000
multiline_comment|/*&n; *  The following defines are for the flags in the host DMA control register.&n; */
DECL|macro|HDCR_COUNT_MASK
mdefine_line|#define HDCR_COUNT_MASK                         0x000003FF
DECL|macro|HDCR_DONE
mdefine_line|#define HDCR_DONE                               0x00004000
DECL|macro|HDCR_OPT
mdefine_line|#define HDCR_OPT                                0x00008000
DECL|macro|HDCR_WBD
mdefine_line|#define HDCR_WBD                                0x00400000
DECL|macro|HDCR_WBS
mdefine_line|#define HDCR_WBS                                0x00800000
DECL|macro|HDCR_DMS_MASK
mdefine_line|#define HDCR_DMS_MASK                           0x07000000
DECL|macro|HDCR_DMS_LINEAR
mdefine_line|#define HDCR_DMS_LINEAR                         0x00000000
DECL|macro|HDCR_DMS_16_DWORDS
mdefine_line|#define HDCR_DMS_16_DWORDS                      0x01000000
DECL|macro|HDCR_DMS_32_DWORDS
mdefine_line|#define HDCR_DMS_32_DWORDS                      0x02000000
DECL|macro|HDCR_DMS_64_DWORDS
mdefine_line|#define HDCR_DMS_64_DWORDS                      0x03000000
DECL|macro|HDCR_DMS_128_DWORDS
mdefine_line|#define HDCR_DMS_128_DWORDS                     0x04000000
DECL|macro|HDCR_DMS_256_DWORDS
mdefine_line|#define HDCR_DMS_256_DWORDS                     0x05000000
DECL|macro|HDCR_DMS_512_DWORDS
mdefine_line|#define HDCR_DMS_512_DWORDS                     0x06000000
DECL|macro|HDCR_DMS_1024_DWORDS
mdefine_line|#define HDCR_DMS_1024_DWORDS                    0x07000000
DECL|macro|HDCR_DH
mdefine_line|#define HDCR_DH                                 0x08000000
DECL|macro|HDCR_SMS_MASK
mdefine_line|#define HDCR_SMS_MASK                           0x70000000
DECL|macro|HDCR_SMS_LINEAR
mdefine_line|#define HDCR_SMS_LINEAR                         0x00000000
DECL|macro|HDCR_SMS_16_DWORDS
mdefine_line|#define HDCR_SMS_16_DWORDS                      0x10000000
DECL|macro|HDCR_SMS_32_DWORDS
mdefine_line|#define HDCR_SMS_32_DWORDS                      0x20000000
DECL|macro|HDCR_SMS_64_DWORDS
mdefine_line|#define HDCR_SMS_64_DWORDS                      0x30000000
DECL|macro|HDCR_SMS_128_DWORDS
mdefine_line|#define HDCR_SMS_128_DWORDS                     0x40000000
DECL|macro|HDCR_SMS_256_DWORDS
mdefine_line|#define HDCR_SMS_256_DWORDS                     0x50000000
DECL|macro|HDCR_SMS_512_DWORDS
mdefine_line|#define HDCR_SMS_512_DWORDS                     0x60000000
DECL|macro|HDCR_SMS_1024_DWORDS
mdefine_line|#define HDCR_SMS_1024_DWORDS                    0x70000000
DECL|macro|HDCR_SH
mdefine_line|#define HDCR_SH                                 0x80000000
DECL|macro|HDCR_COUNT_SHIFT
mdefine_line|#define HDCR_COUNT_SHIFT                        0
multiline_comment|/*&n; *  The following defines are for the flags in the performance monitor control&n; *  register.&n; */
DECL|macro|PFMC_C1SS_MASK
mdefine_line|#define PFMC_C1SS_MASK                          0x0000001F
DECL|macro|PFMC_C1EV
mdefine_line|#define PFMC_C1EV                               0x00000020
DECL|macro|PFMC_C1RS
mdefine_line|#define PFMC_C1RS                               0x00008000
DECL|macro|PFMC_C2SS_MASK
mdefine_line|#define PFMC_C2SS_MASK                          0x001F0000
DECL|macro|PFMC_C2EV
mdefine_line|#define PFMC_C2EV                               0x00200000
DECL|macro|PFMC_C2RS
mdefine_line|#define PFMC_C2RS                               0x80000000
DECL|macro|PFMC_C1SS_SHIFT
mdefine_line|#define PFMC_C1SS_SHIFT                         0
DECL|macro|PFMC_C2SS_SHIFT
mdefine_line|#define PFMC_C2SS_SHIFT                         16
DECL|macro|PFMC_BUS_GRANT
mdefine_line|#define PFMC_BUS_GRANT                          0
DECL|macro|PFMC_GRANT_AFTER_REQ
mdefine_line|#define PFMC_GRANT_AFTER_REQ                    1
DECL|macro|PFMC_TRANSACTION
mdefine_line|#define PFMC_TRANSACTION                        2
DECL|macro|PFMC_DWORD_TRANSFER
mdefine_line|#define PFMC_DWORD_TRANSFER                     3
DECL|macro|PFMC_SLAVE_READ
mdefine_line|#define PFMC_SLAVE_READ                         4
DECL|macro|PFMC_SLAVE_WRITE
mdefine_line|#define PFMC_SLAVE_WRITE                        5
DECL|macro|PFMC_PREEMPTION
mdefine_line|#define PFMC_PREEMPTION                         6
DECL|macro|PFMC_DISCONNECT_RETRY
mdefine_line|#define PFMC_DISCONNECT_RETRY                   7
DECL|macro|PFMC_INTERRUPT
mdefine_line|#define PFMC_INTERRUPT                          8
DECL|macro|PFMC_BUS_OWNERSHIP
mdefine_line|#define PFMC_BUS_OWNERSHIP                      9
DECL|macro|PFMC_TRANSACTION_LAG
mdefine_line|#define PFMC_TRANSACTION_LAG                    10
DECL|macro|PFMC_PCI_CLOCK
mdefine_line|#define PFMC_PCI_CLOCK                          11
DECL|macro|PFMC_SERIAL_CLOCK
mdefine_line|#define PFMC_SERIAL_CLOCK                       12
DECL|macro|PFMC_SP_CLOCK
mdefine_line|#define PFMC_SP_CLOCK                           13
multiline_comment|/*&n; *  The following defines are for the flags in the performance counter value 1&n; *  register.&n; */
DECL|macro|PFCV1_PC1V_MASK
mdefine_line|#define PFCV1_PC1V_MASK                         0xFFFFFFFF
DECL|macro|PFCV1_PC1V_SHIFT
mdefine_line|#define PFCV1_PC1V_SHIFT                        0
multiline_comment|/*&n; *  The following defines are for the flags in the performance counter value 2&n; *  register.&n; */
DECL|macro|PFCV2_PC2V_MASK
mdefine_line|#define PFCV2_PC2V_MASK                         0xFFFFFFFF
DECL|macro|PFCV2_PC2V_SHIFT
mdefine_line|#define PFCV2_PC2V_SHIFT                        0
multiline_comment|/*&n; *  The following defines are for the flags in the clock control register 1.&n; */
DECL|macro|CLKCR1_OSCS
mdefine_line|#define CLKCR1_OSCS                             0x00000001
DECL|macro|CLKCR1_OSCP
mdefine_line|#define CLKCR1_OSCP                             0x00000002
DECL|macro|CLKCR1_PLLSS_MASK
mdefine_line|#define CLKCR1_PLLSS_MASK                       0x0000000C
DECL|macro|CLKCR1_PLLSS_SERIAL
mdefine_line|#define CLKCR1_PLLSS_SERIAL                     0x00000000
DECL|macro|CLKCR1_PLLSS_CRYSTAL
mdefine_line|#define CLKCR1_PLLSS_CRYSTAL                    0x00000004
DECL|macro|CLKCR1_PLLSS_PCI
mdefine_line|#define CLKCR1_PLLSS_PCI                        0x00000008
DECL|macro|CLKCR1_PLLSS_RESERVED
mdefine_line|#define CLKCR1_PLLSS_RESERVED                   0x0000000C
DECL|macro|CLKCR1_PLLP
mdefine_line|#define CLKCR1_PLLP                             0x00000010
DECL|macro|CLKCR1_SWCE
mdefine_line|#define CLKCR1_SWCE                             0x00000020
DECL|macro|CLKCR1_PLLOS
mdefine_line|#define CLKCR1_PLLOS                            0x00000040
multiline_comment|/*&n; *  The following defines are for the flags in the clock control register 2.&n; */
DECL|macro|CLKCR2_PDIVS_MASK
mdefine_line|#define CLKCR2_PDIVS_MASK                       0x0000000F
DECL|macro|CLKCR2_PDIVS_1
mdefine_line|#define CLKCR2_PDIVS_1                          0x00000001
DECL|macro|CLKCR2_PDIVS_2
mdefine_line|#define CLKCR2_PDIVS_2                          0x00000002
DECL|macro|CLKCR2_PDIVS_4
mdefine_line|#define CLKCR2_PDIVS_4                          0x00000004
DECL|macro|CLKCR2_PDIVS_7
mdefine_line|#define CLKCR2_PDIVS_7                          0x00000007
DECL|macro|CLKCR2_PDIVS_8
mdefine_line|#define CLKCR2_PDIVS_8                          0x00000008
DECL|macro|CLKCR2_PDIVS_16
mdefine_line|#define CLKCR2_PDIVS_16                         0x00000000
multiline_comment|/*&n; *  The following defines are for the flags in the PLL multiplier register.&n; */
DECL|macro|PLLM_MASK
mdefine_line|#define PLLM_MASK                               0x000000FF
DECL|macro|PLLM_SHIFT
mdefine_line|#define PLLM_SHIFT                              0
multiline_comment|/*&n; *  The following defines are for the flags in the PLL capacitor coefficient&n; *  register.&n; */
DECL|macro|PLLCC_CDR_MASK
mdefine_line|#define PLLCC_CDR_MASK                          0x00000007
macro_line|#ifndef NO_CS4610
DECL|macro|PLLCC_CDR_240_350_MHZ
mdefine_line|#define PLLCC_CDR_240_350_MHZ                   0x00000000
DECL|macro|PLLCC_CDR_184_265_MHZ
mdefine_line|#define PLLCC_CDR_184_265_MHZ                   0x00000001
DECL|macro|PLLCC_CDR_144_205_MHZ
mdefine_line|#define PLLCC_CDR_144_205_MHZ                   0x00000002
DECL|macro|PLLCC_CDR_111_160_MHZ
mdefine_line|#define PLLCC_CDR_111_160_MHZ                   0x00000003
DECL|macro|PLLCC_CDR_87_123_MHZ
mdefine_line|#define PLLCC_CDR_87_123_MHZ                    0x00000004
DECL|macro|PLLCC_CDR_67_96_MHZ
mdefine_line|#define PLLCC_CDR_67_96_MHZ                     0x00000005
DECL|macro|PLLCC_CDR_52_74_MHZ
mdefine_line|#define PLLCC_CDR_52_74_MHZ                     0x00000006
DECL|macro|PLLCC_CDR_45_58_MHZ
mdefine_line|#define PLLCC_CDR_45_58_MHZ                     0x00000007
macro_line|#endif
macro_line|#ifndef NO_CS4612
DECL|macro|PLLCC_CDR_271_398_MHZ
mdefine_line|#define PLLCC_CDR_271_398_MHZ                   0x00000000
DECL|macro|PLLCC_CDR_227_330_MHZ
mdefine_line|#define PLLCC_CDR_227_330_MHZ                   0x00000001
DECL|macro|PLLCC_CDR_167_239_MHZ
mdefine_line|#define PLLCC_CDR_167_239_MHZ                   0x00000002
DECL|macro|PLLCC_CDR_150_215_MHZ
mdefine_line|#define PLLCC_CDR_150_215_MHZ                   0x00000003
DECL|macro|PLLCC_CDR_107_154_MHZ
mdefine_line|#define PLLCC_CDR_107_154_MHZ                   0x00000004
DECL|macro|PLLCC_CDR_98_140_MHZ
mdefine_line|#define PLLCC_CDR_98_140_MHZ                    0x00000005
DECL|macro|PLLCC_CDR_73_104_MHZ
mdefine_line|#define PLLCC_CDR_73_104_MHZ                    0x00000006
DECL|macro|PLLCC_CDR_63_90_MHZ
mdefine_line|#define PLLCC_CDR_63_90_MHZ                     0x00000007
macro_line|#endif
DECL|macro|PLLCC_LPF_MASK
mdefine_line|#define PLLCC_LPF_MASK                          0x000000F8
macro_line|#ifndef NO_CS4610
DECL|macro|PLLCC_LPF_23850_60000_KHZ
mdefine_line|#define PLLCC_LPF_23850_60000_KHZ               0x00000000
DECL|macro|PLLCC_LPF_7960_26290_KHZ
mdefine_line|#define PLLCC_LPF_7960_26290_KHZ                0x00000008
DECL|macro|PLLCC_LPF_4160_10980_KHZ
mdefine_line|#define PLLCC_LPF_4160_10980_KHZ                0x00000018
DECL|macro|PLLCC_LPF_1740_4580_KHZ
mdefine_line|#define PLLCC_LPF_1740_4580_KHZ                 0x00000038
DECL|macro|PLLCC_LPF_724_1910_KHZ
mdefine_line|#define PLLCC_LPF_724_1910_KHZ                  0x00000078
DECL|macro|PLLCC_LPF_317_798_KHZ
mdefine_line|#define PLLCC_LPF_317_798_KHZ                   0x000000F8
macro_line|#endif
macro_line|#ifndef NO_CS4612
DECL|macro|PLLCC_LPF_25580_64530_KHZ
mdefine_line|#define PLLCC_LPF_25580_64530_KHZ               0x00000000
DECL|macro|PLLCC_LPF_14360_37270_KHZ
mdefine_line|#define PLLCC_LPF_14360_37270_KHZ               0x00000008
DECL|macro|PLLCC_LPF_6100_16020_KHZ
mdefine_line|#define PLLCC_LPF_6100_16020_KHZ                0x00000018
DECL|macro|PLLCC_LPF_2540_6690_KHZ
mdefine_line|#define PLLCC_LPF_2540_6690_KHZ                 0x00000038
DECL|macro|PLLCC_LPF_1050_2780_KHZ
mdefine_line|#define PLLCC_LPF_1050_2780_KHZ                 0x00000078
DECL|macro|PLLCC_LPF_450_1160_KHZ
mdefine_line|#define PLLCC_LPF_450_1160_KHZ                  0x000000F8
macro_line|#endif
multiline_comment|/*&n; *  The following defines are for the flags in the feature reporting register.&n; */
DECL|macro|FRR_FAB_MASK
mdefine_line|#define FRR_FAB_MASK                            0x00000003
DECL|macro|FRR_MASK_MASK
mdefine_line|#define FRR_MASK_MASK                           0x0000001C
macro_line|#ifdef NO_CS4612
DECL|macro|FRR_CFOP_MASK
mdefine_line|#define FRR_CFOP_MASK                           0x000000E0
macro_line|#else
DECL|macro|FRR_CFOP_MASK
mdefine_line|#define FRR_CFOP_MASK                           0x00000FE0
macro_line|#endif
DECL|macro|FRR_CFOP_NOT_DVD
mdefine_line|#define FRR_CFOP_NOT_DVD                        0x00000020
DECL|macro|FRR_CFOP_A3D
mdefine_line|#define FRR_CFOP_A3D                            0x00000040
DECL|macro|FRR_CFOP_128_PIN
mdefine_line|#define FRR_CFOP_128_PIN                        0x00000080
macro_line|#ifndef NO_CS4612
DECL|macro|FRR_CFOP_CS4280
mdefine_line|#define FRR_CFOP_CS4280                         0x00000800
macro_line|#endif
DECL|macro|FRR_FAB_SHIFT
mdefine_line|#define FRR_FAB_SHIFT                           0
DECL|macro|FRR_MASK_SHIFT
mdefine_line|#define FRR_MASK_SHIFT                          2
DECL|macro|FRR_CFOP_SHIFT
mdefine_line|#define FRR_CFOP_SHIFT                          5
multiline_comment|/*&n; *  The following defines are for the flags in the configuration load 1&n; *  register.&n; */
DECL|macro|CFL1_CLOCK_SOURCE_MASK
mdefine_line|#define CFL1_CLOCK_SOURCE_MASK                  0x00000003
DECL|macro|CFL1_CLOCK_SOURCE_CS423X
mdefine_line|#define CFL1_CLOCK_SOURCE_CS423X                0x00000000
DECL|macro|CFL1_CLOCK_SOURCE_AC97
mdefine_line|#define CFL1_CLOCK_SOURCE_AC97                  0x00000001
DECL|macro|CFL1_CLOCK_SOURCE_CRYSTAL
mdefine_line|#define CFL1_CLOCK_SOURCE_CRYSTAL               0x00000002
DECL|macro|CFL1_CLOCK_SOURCE_DUAL_AC97
mdefine_line|#define CFL1_CLOCK_SOURCE_DUAL_AC97             0x00000003
DECL|macro|CFL1_VALID_DATA_MASK
mdefine_line|#define CFL1_VALID_DATA_MASK                    0x000000FF
multiline_comment|/*&n; *  The following defines are for the flags in the configuration load 2&n; *  register.&n; */
DECL|macro|CFL2_VALID_DATA_MASK
mdefine_line|#define CFL2_VALID_DATA_MASK                    0x000000FF
multiline_comment|/*&n; *  The following defines are for the flags in the serial port master control&n; *  register 1.&n; */
DECL|macro|SERMC1_MSPE
mdefine_line|#define SERMC1_MSPE                             0x00000001
DECL|macro|SERMC1_PTC_MASK
mdefine_line|#define SERMC1_PTC_MASK                         0x0000000E
DECL|macro|SERMC1_PTC_CS423X
mdefine_line|#define SERMC1_PTC_CS423X                       0x00000000
DECL|macro|SERMC1_PTC_AC97
mdefine_line|#define SERMC1_PTC_AC97                         0x00000002
DECL|macro|SERMC1_PTC_DAC
mdefine_line|#define SERMC1_PTC_DAC                          0x00000004
DECL|macro|SERMC1_PLB
mdefine_line|#define SERMC1_PLB                              0x00000010
DECL|macro|SERMC1_XLB
mdefine_line|#define SERMC1_XLB                              0x00000020
multiline_comment|/*&n; *  The following defines are for the flags in the serial port master control&n; *  register 2.&n; */
DECL|macro|SERMC2_LROE
mdefine_line|#define SERMC2_LROE                             0x00000001
DECL|macro|SERMC2_MCOE
mdefine_line|#define SERMC2_MCOE                             0x00000002
DECL|macro|SERMC2_MCDIV
mdefine_line|#define SERMC2_MCDIV                            0x00000004
multiline_comment|/*&n; *  The following defines are for the flags in the serial port 1 configuration&n; *  register.&n; */
DECL|macro|SERC1_SO1EN
mdefine_line|#define SERC1_SO1EN                             0x00000001
DECL|macro|SERC1_SO1F_MASK
mdefine_line|#define SERC1_SO1F_MASK                         0x0000000E
DECL|macro|SERC1_SO1F_CS423X
mdefine_line|#define SERC1_SO1F_CS423X                       0x00000000
DECL|macro|SERC1_SO1F_AC97
mdefine_line|#define SERC1_SO1F_AC97                         0x00000002
DECL|macro|SERC1_SO1F_DAC
mdefine_line|#define SERC1_SO1F_DAC                          0x00000004
DECL|macro|SERC1_SO1F_SPDIF
mdefine_line|#define SERC1_SO1F_SPDIF                        0x00000006
multiline_comment|/*&n; *  The following defines are for the flags in the serial port 2 configuration&n; *  register.&n; */
DECL|macro|SERC2_SI1EN
mdefine_line|#define SERC2_SI1EN                             0x00000001
DECL|macro|SERC2_SI1F_MASK
mdefine_line|#define SERC2_SI1F_MASK                         0x0000000E
DECL|macro|SERC2_SI1F_CS423X
mdefine_line|#define SERC2_SI1F_CS423X                       0x00000000
DECL|macro|SERC2_SI1F_AC97
mdefine_line|#define SERC2_SI1F_AC97                         0x00000002
DECL|macro|SERC2_SI1F_ADC
mdefine_line|#define SERC2_SI1F_ADC                          0x00000004
DECL|macro|SERC2_SI1F_SPDIF
mdefine_line|#define SERC2_SI1F_SPDIF                        0x00000006
multiline_comment|/*&n; *  The following defines are for the flags in the serial port 3 configuration&n; *  register.&n; */
DECL|macro|SERC3_SO2EN
mdefine_line|#define SERC3_SO2EN                             0x00000001
DECL|macro|SERC3_SO2F_MASK
mdefine_line|#define SERC3_SO2F_MASK                         0x00000006
DECL|macro|SERC3_SO2F_DAC
mdefine_line|#define SERC3_SO2F_DAC                          0x00000000
DECL|macro|SERC3_SO2F_SPDIF
mdefine_line|#define SERC3_SO2F_SPDIF                        0x00000002
multiline_comment|/*&n; *  The following defines are for the flags in the serial port 4 configuration&n; *  register.&n; */
DECL|macro|SERC4_SO3EN
mdefine_line|#define SERC4_SO3EN                             0x00000001
DECL|macro|SERC4_SO3F_MASK
mdefine_line|#define SERC4_SO3F_MASK                         0x00000006
DECL|macro|SERC4_SO3F_DAC
mdefine_line|#define SERC4_SO3F_DAC                          0x00000000
DECL|macro|SERC4_SO3F_SPDIF
mdefine_line|#define SERC4_SO3F_SPDIF                        0x00000002
multiline_comment|/*&n; *  The following defines are for the flags in the serial port 5 configuration&n; *  register.&n; */
DECL|macro|SERC5_SI2EN
mdefine_line|#define SERC5_SI2EN                             0x00000001
DECL|macro|SERC5_SI2F_MASK
mdefine_line|#define SERC5_SI2F_MASK                         0x00000006
DECL|macro|SERC5_SI2F_ADC
mdefine_line|#define SERC5_SI2F_ADC                          0x00000000
DECL|macro|SERC5_SI2F_SPDIF
mdefine_line|#define SERC5_SI2F_SPDIF                        0x00000002
multiline_comment|/*&n; *  The following defines are for the flags in the serial port backdoor sample&n; *  pointer register.&n; */
DECL|macro|SERBSP_FSP_MASK
mdefine_line|#define SERBSP_FSP_MASK                         0x0000000F
DECL|macro|SERBSP_FSP_SHIFT
mdefine_line|#define SERBSP_FSP_SHIFT                        0
multiline_comment|/*&n; *  The following defines are for the flags in the serial port backdoor status&n; *  register.&n; */
DECL|macro|SERBST_RRDY
mdefine_line|#define SERBST_RRDY                             0x00000001
DECL|macro|SERBST_WBSY
mdefine_line|#define SERBST_WBSY                             0x00000002
multiline_comment|/*&n; *  The following defines are for the flags in the serial port backdoor command&n; *  register.&n; */
DECL|macro|SERBCM_RDC
mdefine_line|#define SERBCM_RDC                              0x00000001
DECL|macro|SERBCM_WRC
mdefine_line|#define SERBCM_WRC                              0x00000002
multiline_comment|/*&n; *  The following defines are for the flags in the serial port backdoor address&n; *  register.&n; */
macro_line|#ifdef NO_CS4612
DECL|macro|SERBAD_FAD_MASK
mdefine_line|#define SERBAD_FAD_MASK                         0x000000FF
macro_line|#else
DECL|macro|SERBAD_FAD_MASK
mdefine_line|#define SERBAD_FAD_MASK                         0x000001FF
macro_line|#endif
DECL|macro|SERBAD_FAD_SHIFT
mdefine_line|#define SERBAD_FAD_SHIFT                        0
multiline_comment|/*&n; *  The following defines are for the flags in the serial port backdoor&n; *  configuration register.&n; */
DECL|macro|SERBCF_HBP
mdefine_line|#define SERBCF_HBP                              0x00000001
multiline_comment|/*&n; *  The following defines are for the flags in the serial port backdoor write&n; *  port register.&n; */
DECL|macro|SERBWP_FWD_MASK
mdefine_line|#define SERBWP_FWD_MASK                         0x000FFFFF
DECL|macro|SERBWP_FWD_SHIFT
mdefine_line|#define SERBWP_FWD_SHIFT                        0
multiline_comment|/*&n; *  The following defines are for the flags in the serial port backdoor read&n; *  port register.&n; */
DECL|macro|SERBRP_FRD_MASK
mdefine_line|#define SERBRP_FRD_MASK                         0x000FFFFF
DECL|macro|SERBRP_FRD_SHIFT
mdefine_line|#define SERBRP_FRD_SHIFT                        0
multiline_comment|/*&n; *  The following defines are for the flags in the async FIFO address register.&n; */
macro_line|#ifndef NO_CS4612
DECL|macro|ASER_FADDR_A1_MASK
mdefine_line|#define ASER_FADDR_A1_MASK                      0x000001FF
DECL|macro|ASER_FADDR_EN1
mdefine_line|#define ASER_FADDR_EN1                          0x00008000
DECL|macro|ASER_FADDR_A2_MASK
mdefine_line|#define ASER_FADDR_A2_MASK                      0x01FF0000
DECL|macro|ASER_FADDR_EN2
mdefine_line|#define ASER_FADDR_EN2                          0x80000000
DECL|macro|ASER_FADDR_A1_SHIFT
mdefine_line|#define ASER_FADDR_A1_SHIFT                     0
DECL|macro|ASER_FADDR_A2_SHIFT
mdefine_line|#define ASER_FADDR_A2_SHIFT                     16
macro_line|#endif
multiline_comment|/*&n; *  The following defines are for the flags in the AC97 control register.&n; */
DECL|macro|ACCTL_RSTN
mdefine_line|#define ACCTL_RSTN                              0x00000001
DECL|macro|ACCTL_ESYN
mdefine_line|#define ACCTL_ESYN                              0x00000002
DECL|macro|ACCTL_VFRM
mdefine_line|#define ACCTL_VFRM                              0x00000004
DECL|macro|ACCTL_DCV
mdefine_line|#define ACCTL_DCV                               0x00000008
DECL|macro|ACCTL_CRW
mdefine_line|#define ACCTL_CRW                               0x00000010
DECL|macro|ACCTL_ASYN
mdefine_line|#define ACCTL_ASYN                              0x00000020
macro_line|#ifndef NO_CS4612
DECL|macro|ACCTL_TC
mdefine_line|#define ACCTL_TC                                0x00000040
macro_line|#endif
multiline_comment|/*&n; *  The following defines are for the flags in the AC97 status register.&n; */
DECL|macro|ACSTS_CRDY
mdefine_line|#define ACSTS_CRDY                              0x00000001
DECL|macro|ACSTS_VSTS
mdefine_line|#define ACSTS_VSTS                              0x00000002
macro_line|#ifndef NO_CS4612
DECL|macro|ACSTS_WKUP
mdefine_line|#define ACSTS_WKUP                              0x00000004
macro_line|#endif
multiline_comment|/*&n; *  The following defines are for the flags in the AC97 output slot valid&n; *  register.&n; */
DECL|macro|ACOSV_SLV3
mdefine_line|#define ACOSV_SLV3                              0x00000001
DECL|macro|ACOSV_SLV4
mdefine_line|#define ACOSV_SLV4                              0x00000002
DECL|macro|ACOSV_SLV5
mdefine_line|#define ACOSV_SLV5                              0x00000004
DECL|macro|ACOSV_SLV6
mdefine_line|#define ACOSV_SLV6                              0x00000008
DECL|macro|ACOSV_SLV7
mdefine_line|#define ACOSV_SLV7                              0x00000010
DECL|macro|ACOSV_SLV8
mdefine_line|#define ACOSV_SLV8                              0x00000020
DECL|macro|ACOSV_SLV9
mdefine_line|#define ACOSV_SLV9                              0x00000040
DECL|macro|ACOSV_SLV10
mdefine_line|#define ACOSV_SLV10                             0x00000080
DECL|macro|ACOSV_SLV11
mdefine_line|#define ACOSV_SLV11                             0x00000100
DECL|macro|ACOSV_SLV12
mdefine_line|#define ACOSV_SLV12                             0x00000200
multiline_comment|/*&n; *  The following defines are for the flags in the AC97 command address&n; *  register.&n; */
DECL|macro|ACCAD_CI_MASK
mdefine_line|#define ACCAD_CI_MASK                           0x0000007F
DECL|macro|ACCAD_CI_SHIFT
mdefine_line|#define ACCAD_CI_SHIFT                          0
multiline_comment|/*&n; *  The following defines are for the flags in the AC97 command data register.&n; */
DECL|macro|ACCDA_CD_MASK
mdefine_line|#define ACCDA_CD_MASK                           0x0000FFFF
DECL|macro|ACCDA_CD_SHIFT
mdefine_line|#define ACCDA_CD_SHIFT                          0
multiline_comment|/*&n; *  The following defines are for the flags in the AC97 input slot valid&n; *  register.&n; */
DECL|macro|ACISV_ISV3
mdefine_line|#define ACISV_ISV3                              0x00000001
DECL|macro|ACISV_ISV4
mdefine_line|#define ACISV_ISV4                              0x00000002
DECL|macro|ACISV_ISV5
mdefine_line|#define ACISV_ISV5                              0x00000004
DECL|macro|ACISV_ISV6
mdefine_line|#define ACISV_ISV6                              0x00000008
DECL|macro|ACISV_ISV7
mdefine_line|#define ACISV_ISV7                              0x00000010
DECL|macro|ACISV_ISV8
mdefine_line|#define ACISV_ISV8                              0x00000020
DECL|macro|ACISV_ISV9
mdefine_line|#define ACISV_ISV9                              0x00000040
DECL|macro|ACISV_ISV10
mdefine_line|#define ACISV_ISV10                             0x00000080
DECL|macro|ACISV_ISV11
mdefine_line|#define ACISV_ISV11                             0x00000100
DECL|macro|ACISV_ISV12
mdefine_line|#define ACISV_ISV12                             0x00000200
multiline_comment|/*&n; *  The following defines are for the flags in the AC97 status address&n; *  register.&n; */
DECL|macro|ACSAD_SI_MASK
mdefine_line|#define ACSAD_SI_MASK                           0x0000007F
DECL|macro|ACSAD_SI_SHIFT
mdefine_line|#define ACSAD_SI_SHIFT                          0
multiline_comment|/*&n; *  The following defines are for the flags in the AC97 status data register.&n; */
DECL|macro|ACSDA_SD_MASK
mdefine_line|#define ACSDA_SD_MASK                           0x0000FFFF
DECL|macro|ACSDA_SD_SHIFT
mdefine_line|#define ACSDA_SD_SHIFT                          0
multiline_comment|/*&n; *  The following defines are for the flags in the joystick poll/trigger&n; *  register.&n; */
DECL|macro|JSPT_CAX
mdefine_line|#define JSPT_CAX                                0x00000001
DECL|macro|JSPT_CAY
mdefine_line|#define JSPT_CAY                                0x00000002
DECL|macro|JSPT_CBX
mdefine_line|#define JSPT_CBX                                0x00000004
DECL|macro|JSPT_CBY
mdefine_line|#define JSPT_CBY                                0x00000008
DECL|macro|JSPT_BA1
mdefine_line|#define JSPT_BA1                                0x00000010
DECL|macro|JSPT_BA2
mdefine_line|#define JSPT_BA2                                0x00000020
DECL|macro|JSPT_BB1
mdefine_line|#define JSPT_BB1                                0x00000040
DECL|macro|JSPT_BB2
mdefine_line|#define JSPT_BB2                                0x00000080
multiline_comment|/*&n; *  The following defines are for the flags in the joystick control register.&n; */
DECL|macro|JSCTL_SP_MASK
mdefine_line|#define JSCTL_SP_MASK                           0x00000003
DECL|macro|JSCTL_SP_SLOW
mdefine_line|#define JSCTL_SP_SLOW                           0x00000000
DECL|macro|JSCTL_SP_MEDIUM_SLOW
mdefine_line|#define JSCTL_SP_MEDIUM_SLOW                    0x00000001
DECL|macro|JSCTL_SP_MEDIUM_FAST
mdefine_line|#define JSCTL_SP_MEDIUM_FAST                    0x00000002
DECL|macro|JSCTL_SP_FAST
mdefine_line|#define JSCTL_SP_FAST                           0x00000003
DECL|macro|JSCTL_ARE
mdefine_line|#define JSCTL_ARE                               0x00000004
multiline_comment|/*&n; *  The following defines are for the flags in the joystick coordinate pair 1&n; *  readback register.&n; */
DECL|macro|JSC1_Y1V_MASK
mdefine_line|#define JSC1_Y1V_MASK                           0x0000FFFF
DECL|macro|JSC1_X1V_MASK
mdefine_line|#define JSC1_X1V_MASK                           0xFFFF0000
DECL|macro|JSC1_Y1V_SHIFT
mdefine_line|#define JSC1_Y1V_SHIFT                          0
DECL|macro|JSC1_X1V_SHIFT
mdefine_line|#define JSC1_X1V_SHIFT                          16
multiline_comment|/*&n; *  The following defines are for the flags in the joystick coordinate pair 2&n; *  readback register.&n; */
DECL|macro|JSC2_Y2V_MASK
mdefine_line|#define JSC2_Y2V_MASK                           0x0000FFFF
DECL|macro|JSC2_X2V_MASK
mdefine_line|#define JSC2_X2V_MASK                           0xFFFF0000
DECL|macro|JSC2_Y2V_SHIFT
mdefine_line|#define JSC2_Y2V_SHIFT                          0
DECL|macro|JSC2_X2V_SHIFT
mdefine_line|#define JSC2_X2V_SHIFT                          16
multiline_comment|/*&n; *  The following defines are for the flags in the MIDI control register.&n; */
DECL|macro|MIDCR_TXE
mdefine_line|#define MIDCR_TXE                               0x00000001&t;/* Enable transmitting. */
DECL|macro|MIDCR_RXE
mdefine_line|#define MIDCR_RXE                               0x00000002&t;/* Enable receiving. */
DECL|macro|MIDCR_RIE
mdefine_line|#define MIDCR_RIE                               0x00000004&t;/* Interrupt upon tx ready. */
DECL|macro|MIDCR_TIE
mdefine_line|#define MIDCR_TIE                               0x00000008&t;/* Interrupt upon rx ready. */
DECL|macro|MIDCR_MLB
mdefine_line|#define MIDCR_MLB                               0x00000010&t;/* Enable midi loopback. */
DECL|macro|MIDCR_MRST
mdefine_line|#define MIDCR_MRST                              0x00000020&t;/* Reset interface. */
multiline_comment|/*&n; *  The following defines are for the flags in the MIDI status register.&n; */
DECL|macro|MIDSR_TBF
mdefine_line|#define MIDSR_TBF                               0x00000001&t;/* Tx FIFO is full. */
DECL|macro|MIDSR_RBE
mdefine_line|#define MIDSR_RBE                               0x00000002&t;/* Rx FIFO is empty. */
multiline_comment|/*&n; *  The following defines are for the flags in the MIDI write port register.&n; */
DECL|macro|MIDWP_MWD_MASK
mdefine_line|#define MIDWP_MWD_MASK                          0x000000FF
DECL|macro|MIDWP_MWD_SHIFT
mdefine_line|#define MIDWP_MWD_SHIFT                         0
multiline_comment|/*&n; *  The following defines are for the flags in the MIDI read port register.&n; */
DECL|macro|MIDRP_MRD_MASK
mdefine_line|#define MIDRP_MRD_MASK                          0x000000FF
DECL|macro|MIDRP_MRD_SHIFT
mdefine_line|#define MIDRP_MRD_SHIFT                         0
multiline_comment|/*&n; *  The following defines are for the flags in the joystick GPIO register.&n; */
DECL|macro|JSIO_DAX
mdefine_line|#define JSIO_DAX                                0x00000001
DECL|macro|JSIO_DAY
mdefine_line|#define JSIO_DAY                                0x00000002
DECL|macro|JSIO_DBX
mdefine_line|#define JSIO_DBX                                0x00000004
DECL|macro|JSIO_DBY
mdefine_line|#define JSIO_DBY                                0x00000008
DECL|macro|JSIO_AXOE
mdefine_line|#define JSIO_AXOE                               0x00000010
DECL|macro|JSIO_AYOE
mdefine_line|#define JSIO_AYOE                               0x00000020
DECL|macro|JSIO_BXOE
mdefine_line|#define JSIO_BXOE                               0x00000040
DECL|macro|JSIO_BYOE
mdefine_line|#define JSIO_BYOE                               0x00000080
multiline_comment|/*&n; *  The following defines are for the flags in the master async/sync serial&n; *  port enable register.&n; */
macro_line|#ifndef NO_CS4612
DECL|macro|ASER_MASTER_ME
mdefine_line|#define ASER_MASTER_ME                          0x00000001
macro_line|#endif
multiline_comment|/*&n; *  The following defines are for the flags in the configuration interface&n; *  register.&n; */
DECL|macro|CFGI_CLK
mdefine_line|#define CFGI_CLK                                0x00000001
DECL|macro|CFGI_DOUT
mdefine_line|#define CFGI_DOUT                               0x00000002
DECL|macro|CFGI_DIN_EEN
mdefine_line|#define CFGI_DIN_EEN                            0x00000004
DECL|macro|CFGI_EELD
mdefine_line|#define CFGI_EELD                               0x00000008
multiline_comment|/*&n; *  The following defines are for the flags in the subsystem ID and vendor ID&n; *  register.&n; */
DECL|macro|SSVID_VID_MASK
mdefine_line|#define SSVID_VID_MASK                          0x0000FFFF
DECL|macro|SSVID_SID_MASK
mdefine_line|#define SSVID_SID_MASK                          0xFFFF0000
DECL|macro|SSVID_VID_SHIFT
mdefine_line|#define SSVID_VID_SHIFT                         0
DECL|macro|SSVID_SID_SHIFT
mdefine_line|#define SSVID_SID_SHIFT                         16
multiline_comment|/*&n; *  The following defines are for the flags in the GPIO pin interface register.&n; */
DECL|macro|GPIOR_VOLDN
mdefine_line|#define GPIOR_VOLDN                             0x00000001
DECL|macro|GPIOR_VOLUP
mdefine_line|#define GPIOR_VOLUP                             0x00000002
DECL|macro|GPIOR_SI2D
mdefine_line|#define GPIOR_SI2D                              0x00000004
DECL|macro|GPIOR_SI2OE
mdefine_line|#define GPIOR_SI2OE                             0x00000008
multiline_comment|/*&n; *  The following defines are for the flags in the extended GPIO pin direction&n; *  register.&n; */
macro_line|#ifndef NO_CS4612
DECL|macro|EGPIODR_GPOE0
mdefine_line|#define EGPIODR_GPOE0                           0x00000001
DECL|macro|EGPIODR_GPOE1
mdefine_line|#define EGPIODR_GPOE1                           0x00000002
DECL|macro|EGPIODR_GPOE2
mdefine_line|#define EGPIODR_GPOE2                           0x00000004
DECL|macro|EGPIODR_GPOE3
mdefine_line|#define EGPIODR_GPOE3                           0x00000008
DECL|macro|EGPIODR_GPOE4
mdefine_line|#define EGPIODR_GPOE4                           0x00000010
DECL|macro|EGPIODR_GPOE5
mdefine_line|#define EGPIODR_GPOE5                           0x00000020
DECL|macro|EGPIODR_GPOE6
mdefine_line|#define EGPIODR_GPOE6                           0x00000040
DECL|macro|EGPIODR_GPOE7
mdefine_line|#define EGPIODR_GPOE7                           0x00000080
DECL|macro|EGPIODR_GPOE8
mdefine_line|#define EGPIODR_GPOE8                           0x00000100
macro_line|#endif
multiline_comment|/*&n; *  The following defines are for the flags in the extended GPIO pin polarity/&n; *  type register.&n; */
macro_line|#ifndef NO_CS4612
DECL|macro|EGPIOPTR_GPPT0
mdefine_line|#define EGPIOPTR_GPPT0                          0x00000001
DECL|macro|EGPIOPTR_GPPT1
mdefine_line|#define EGPIOPTR_GPPT1                          0x00000002
DECL|macro|EGPIOPTR_GPPT2
mdefine_line|#define EGPIOPTR_GPPT2                          0x00000004
DECL|macro|EGPIOPTR_GPPT3
mdefine_line|#define EGPIOPTR_GPPT3                          0x00000008
DECL|macro|EGPIOPTR_GPPT4
mdefine_line|#define EGPIOPTR_GPPT4                          0x00000010
DECL|macro|EGPIOPTR_GPPT5
mdefine_line|#define EGPIOPTR_GPPT5                          0x00000020
DECL|macro|EGPIOPTR_GPPT6
mdefine_line|#define EGPIOPTR_GPPT6                          0x00000040
DECL|macro|EGPIOPTR_GPPT7
mdefine_line|#define EGPIOPTR_GPPT7                          0x00000080
DECL|macro|EGPIOPTR_GPPT8
mdefine_line|#define EGPIOPTR_GPPT8                          0x00000100
macro_line|#endif
multiline_comment|/*&n; *  The following defines are for the flags in the extended GPIO pin sticky&n; *  register.&n; */
macro_line|#ifndef NO_CS4612
DECL|macro|EGPIOTR_GPS0
mdefine_line|#define EGPIOTR_GPS0                            0x00000001
DECL|macro|EGPIOTR_GPS1
mdefine_line|#define EGPIOTR_GPS1                            0x00000002
DECL|macro|EGPIOTR_GPS2
mdefine_line|#define EGPIOTR_GPS2                            0x00000004
DECL|macro|EGPIOTR_GPS3
mdefine_line|#define EGPIOTR_GPS3                            0x00000008
DECL|macro|EGPIOTR_GPS4
mdefine_line|#define EGPIOTR_GPS4                            0x00000010
DECL|macro|EGPIOTR_GPS5
mdefine_line|#define EGPIOTR_GPS5                            0x00000020
DECL|macro|EGPIOTR_GPS6
mdefine_line|#define EGPIOTR_GPS6                            0x00000040
DECL|macro|EGPIOTR_GPS7
mdefine_line|#define EGPIOTR_GPS7                            0x00000080
DECL|macro|EGPIOTR_GPS8
mdefine_line|#define EGPIOTR_GPS8                            0x00000100
macro_line|#endif
multiline_comment|/*&n; *  The following defines are for the flags in the extended GPIO ping wakeup&n; *  register.&n; */
macro_line|#ifndef NO_CS4612
DECL|macro|EGPIOWR_GPW0
mdefine_line|#define EGPIOWR_GPW0                            0x00000001
DECL|macro|EGPIOWR_GPW1
mdefine_line|#define EGPIOWR_GPW1                            0x00000002
DECL|macro|EGPIOWR_GPW2
mdefine_line|#define EGPIOWR_GPW2                            0x00000004
DECL|macro|EGPIOWR_GPW3
mdefine_line|#define EGPIOWR_GPW3                            0x00000008
DECL|macro|EGPIOWR_GPW4
mdefine_line|#define EGPIOWR_GPW4                            0x00000010
DECL|macro|EGPIOWR_GPW5
mdefine_line|#define EGPIOWR_GPW5                            0x00000020
DECL|macro|EGPIOWR_GPW6
mdefine_line|#define EGPIOWR_GPW6                            0x00000040
DECL|macro|EGPIOWR_GPW7
mdefine_line|#define EGPIOWR_GPW7                            0x00000080
DECL|macro|EGPIOWR_GPW8
mdefine_line|#define EGPIOWR_GPW8                            0x00000100
macro_line|#endif
multiline_comment|/*&n; *  The following defines are for the flags in the extended GPIO pin status&n; *  register.&n; */
macro_line|#ifndef NO_CS4612
DECL|macro|EGPIOSR_GPS0
mdefine_line|#define EGPIOSR_GPS0                            0x00000001
DECL|macro|EGPIOSR_GPS1
mdefine_line|#define EGPIOSR_GPS1                            0x00000002
DECL|macro|EGPIOSR_GPS2
mdefine_line|#define EGPIOSR_GPS2                            0x00000004
DECL|macro|EGPIOSR_GPS3
mdefine_line|#define EGPIOSR_GPS3                            0x00000008
DECL|macro|EGPIOSR_GPS4
mdefine_line|#define EGPIOSR_GPS4                            0x00000010
DECL|macro|EGPIOSR_GPS5
mdefine_line|#define EGPIOSR_GPS5                            0x00000020
DECL|macro|EGPIOSR_GPS6
mdefine_line|#define EGPIOSR_GPS6                            0x00000040
DECL|macro|EGPIOSR_GPS7
mdefine_line|#define EGPIOSR_GPS7                            0x00000080
DECL|macro|EGPIOSR_GPS8
mdefine_line|#define EGPIOSR_GPS8                            0x00000100
macro_line|#endif
multiline_comment|/*&n; *  The following defines are for the flags in the serial port 6 configuration&n; *  register.&n; */
macro_line|#ifndef NO_CS4612
DECL|macro|SERC6_ASDO2EN
mdefine_line|#define SERC6_ASDO2EN                           0x00000001
macro_line|#endif
multiline_comment|/*&n; *  The following defines are for the flags in the serial port 7 configuration&n; *  register.&n; */
macro_line|#ifndef NO_CS4612
DECL|macro|SERC7_ASDI2EN
mdefine_line|#define SERC7_ASDI2EN                           0x00000001
DECL|macro|SERC7_POSILB
mdefine_line|#define SERC7_POSILB                            0x00000002
DECL|macro|SERC7_SIPOLB
mdefine_line|#define SERC7_SIPOLB                            0x00000004
DECL|macro|SERC7_SOSILB
mdefine_line|#define SERC7_SOSILB                            0x00000008
DECL|macro|SERC7_SISOLB
mdefine_line|#define SERC7_SISOLB                            0x00000010
macro_line|#endif
multiline_comment|/*&n; *  The following defines are for the flags in the serial port AC link&n; *  configuration register.&n; */
macro_line|#ifndef NO_CS4612
DECL|macro|SERACC_CODEC_TYPE_MASK
mdefine_line|#define SERACC_CODEC_TYPE_MASK                  0x00000001
DECL|macro|SERACC_CODEC_TYPE_1_03
mdefine_line|#define SERACC_CODEC_TYPE_1_03                  0x00000000
DECL|macro|SERACC_CODEC_TYPE_2_0
mdefine_line|#define SERACC_CODEC_TYPE_2_0                   0x00000001
DECL|macro|SERACC_TWO_CODECS
mdefine_line|#define SERACC_TWO_CODECS                       0x00000002
DECL|macro|SERACC_MDM
mdefine_line|#define SERACC_MDM                              0x00000004
DECL|macro|SERACC_HSP
mdefine_line|#define SERACC_HSP                              0x00000008
macro_line|#endif
multiline_comment|/*&n; *  The following defines are for the flags in the AC97 control register 2.&n; */
macro_line|#ifndef NO_CS4612
DECL|macro|ACCTL2_RSTN
mdefine_line|#define ACCTL2_RSTN                             0x00000001
DECL|macro|ACCTL2_ESYN
mdefine_line|#define ACCTL2_ESYN                             0x00000002
DECL|macro|ACCTL2_VFRM
mdefine_line|#define ACCTL2_VFRM                             0x00000004
DECL|macro|ACCTL2_DCV
mdefine_line|#define ACCTL2_DCV                              0x00000008
DECL|macro|ACCTL2_CRW
mdefine_line|#define ACCTL2_CRW                              0x00000010
DECL|macro|ACCTL2_ASYN
mdefine_line|#define ACCTL2_ASYN                             0x00000020
macro_line|#endif
multiline_comment|/*&n; *  The following defines are for the flags in the AC97 status register 2.&n; */
macro_line|#ifndef NO_CS4612
DECL|macro|ACSTS2_CRDY
mdefine_line|#define ACSTS2_CRDY                             0x00000001
DECL|macro|ACSTS2_VSTS
mdefine_line|#define ACSTS2_VSTS                             0x00000002
macro_line|#endif
multiline_comment|/*&n; *  The following defines are for the flags in the AC97 output slot valid&n; *  register 2.&n; */
macro_line|#ifndef NO_CS4612
DECL|macro|ACOSV2_SLV3
mdefine_line|#define ACOSV2_SLV3                             0x00000001
DECL|macro|ACOSV2_SLV4
mdefine_line|#define ACOSV2_SLV4                             0x00000002
DECL|macro|ACOSV2_SLV5
mdefine_line|#define ACOSV2_SLV5                             0x00000004
DECL|macro|ACOSV2_SLV6
mdefine_line|#define ACOSV2_SLV6                             0x00000008
DECL|macro|ACOSV2_SLV7
mdefine_line|#define ACOSV2_SLV7                             0x00000010
DECL|macro|ACOSV2_SLV8
mdefine_line|#define ACOSV2_SLV8                             0x00000020
DECL|macro|ACOSV2_SLV9
mdefine_line|#define ACOSV2_SLV9                             0x00000040
DECL|macro|ACOSV2_SLV10
mdefine_line|#define ACOSV2_SLV10                            0x00000080
DECL|macro|ACOSV2_SLV11
mdefine_line|#define ACOSV2_SLV11                            0x00000100
DECL|macro|ACOSV2_SLV12
mdefine_line|#define ACOSV2_SLV12                            0x00000200
macro_line|#endif
multiline_comment|/*&n; *  The following defines are for the flags in the AC97 command address&n; *  register 2.&n; */
macro_line|#ifndef NO_CS4612
DECL|macro|ACCAD2_CI_MASK
mdefine_line|#define ACCAD2_CI_MASK                          0x0000007F
DECL|macro|ACCAD2_CI_SHIFT
mdefine_line|#define ACCAD2_CI_SHIFT                         0
macro_line|#endif
multiline_comment|/*&n; *  The following defines are for the flags in the AC97 command data register&n; *  2.&n; */
macro_line|#ifndef NO_CS4612
DECL|macro|ACCDA2_CD_MASK
mdefine_line|#define ACCDA2_CD_MASK                          0x0000FFFF
DECL|macro|ACCDA2_CD_SHIFT
mdefine_line|#define ACCDA2_CD_SHIFT                         0  
macro_line|#endif
multiline_comment|/*&n; *  The following defines are for the flags in the AC97 input slot valid&n; *  register 2.&n; */
macro_line|#ifndef NO_CS4612
DECL|macro|ACISV2_ISV3
mdefine_line|#define ACISV2_ISV3                             0x00000001
DECL|macro|ACISV2_ISV4
mdefine_line|#define ACISV2_ISV4                             0x00000002
DECL|macro|ACISV2_ISV5
mdefine_line|#define ACISV2_ISV5                             0x00000004
DECL|macro|ACISV2_ISV6
mdefine_line|#define ACISV2_ISV6                             0x00000008
DECL|macro|ACISV2_ISV7
mdefine_line|#define ACISV2_ISV7                             0x00000010
DECL|macro|ACISV2_ISV8
mdefine_line|#define ACISV2_ISV8                             0x00000020
DECL|macro|ACISV2_ISV9
mdefine_line|#define ACISV2_ISV9                             0x00000040
DECL|macro|ACISV2_ISV10
mdefine_line|#define ACISV2_ISV10                            0x00000080
DECL|macro|ACISV2_ISV11
mdefine_line|#define ACISV2_ISV11                            0x00000100
DECL|macro|ACISV2_ISV12
mdefine_line|#define ACISV2_ISV12                            0x00000200
macro_line|#endif
multiline_comment|/*&n; *  The following defines are for the flags in the AC97 status address&n; *  register 2.&n; */
macro_line|#ifndef NO_CS4612
DECL|macro|ACSAD2_SI_MASK
mdefine_line|#define ACSAD2_SI_MASK                          0x0000007F
DECL|macro|ACSAD2_SI_SHIFT
mdefine_line|#define ACSAD2_SI_SHIFT                         0
macro_line|#endif
multiline_comment|/*&n; *  The following defines are for the flags in the AC97 status data register 2.&n; */
macro_line|#ifndef NO_CS4612
DECL|macro|ACSDA2_SD_MASK
mdefine_line|#define ACSDA2_SD_MASK                          0x0000FFFF
DECL|macro|ACSDA2_SD_SHIFT
mdefine_line|#define ACSDA2_SD_SHIFT                         0
macro_line|#endif
multiline_comment|/*&n; *  The following defines are for the flags in the I/O trap address and control&n; *  registers (all 12).&n; */
macro_line|#ifndef NO_CS4612
DECL|macro|IOTAC_SA_MASK
mdefine_line|#define IOTAC_SA_MASK                           0x0000FFFF
DECL|macro|IOTAC_MSK_MASK
mdefine_line|#define IOTAC_MSK_MASK                          0x000F0000
DECL|macro|IOTAC_IODC_MASK
mdefine_line|#define IOTAC_IODC_MASK                         0x06000000
DECL|macro|IOTAC_IODC_16_BIT
mdefine_line|#define IOTAC_IODC_16_BIT                       0x00000000
DECL|macro|IOTAC_IODC_10_BIT
mdefine_line|#define IOTAC_IODC_10_BIT                       0x02000000
DECL|macro|IOTAC_IODC_12_BIT
mdefine_line|#define IOTAC_IODC_12_BIT                       0x04000000
DECL|macro|IOTAC_WSPI
mdefine_line|#define IOTAC_WSPI                              0x08000000
DECL|macro|IOTAC_RSPI
mdefine_line|#define IOTAC_RSPI                              0x10000000
DECL|macro|IOTAC_WSE
mdefine_line|#define IOTAC_WSE                               0x20000000
DECL|macro|IOTAC_WE
mdefine_line|#define IOTAC_WE                                0x40000000
DECL|macro|IOTAC_RE
mdefine_line|#define IOTAC_RE                                0x80000000
DECL|macro|IOTAC_SA_SHIFT
mdefine_line|#define IOTAC_SA_SHIFT                          0
DECL|macro|IOTAC_MSK_SHIFT
mdefine_line|#define IOTAC_MSK_SHIFT                         16
macro_line|#endif
multiline_comment|/*&n; *  The following defines are for the flags in the I/O trap fast read registers&n; *  (all 8).&n; */
macro_line|#ifndef NO_CS4612
DECL|macro|IOTFR_D_MASK
mdefine_line|#define IOTFR_D_MASK                            0x0000FFFF
DECL|macro|IOTFR_A_MASK
mdefine_line|#define IOTFR_A_MASK                            0x000F0000
DECL|macro|IOTFR_R_MASK
mdefine_line|#define IOTFR_R_MASK                            0x0F000000
DECL|macro|IOTFR_ALL
mdefine_line|#define IOTFR_ALL                               0x40000000
DECL|macro|IOTFR_VL
mdefine_line|#define IOTFR_VL                                0x80000000
DECL|macro|IOTFR_D_SHIFT
mdefine_line|#define IOTFR_D_SHIFT                           0
DECL|macro|IOTFR_A_SHIFT
mdefine_line|#define IOTFR_A_SHIFT                           16
DECL|macro|IOTFR_R_SHIFT
mdefine_line|#define IOTFR_R_SHIFT                           24
macro_line|#endif
multiline_comment|/*&n; *  The following defines are for the flags in the I/O trap FIFO register.&n; */
macro_line|#ifndef NO_CS4612
DECL|macro|IOTFIFO_BA_MASK
mdefine_line|#define IOTFIFO_BA_MASK                         0x00003FFF
DECL|macro|IOTFIFO_S_MASK
mdefine_line|#define IOTFIFO_S_MASK                          0x00FF0000
DECL|macro|IOTFIFO_OF
mdefine_line|#define IOTFIFO_OF                              0x40000000
DECL|macro|IOTFIFO_SPIOF
mdefine_line|#define IOTFIFO_SPIOF                           0x80000000
DECL|macro|IOTFIFO_BA_SHIFT
mdefine_line|#define IOTFIFO_BA_SHIFT                        0
DECL|macro|IOTFIFO_S_SHIFT
mdefine_line|#define IOTFIFO_S_SHIFT                         16
macro_line|#endif
multiline_comment|/*&n; *  The following defines are for the flags in the I/O trap retry read data&n; *  register.&n; */
macro_line|#ifndef NO_CS4612
DECL|macro|IOTRRD_D_MASK
mdefine_line|#define IOTRRD_D_MASK                           0x0000FFFF
DECL|macro|IOTRRD_RDV
mdefine_line|#define IOTRRD_RDV                              0x80000000
DECL|macro|IOTRRD_D_SHIFT
mdefine_line|#define IOTRRD_D_SHIFT                          0
macro_line|#endif
multiline_comment|/*&n; *  The following defines are for the flags in the I/O trap FIFO pointer&n; *  register.&n; */
macro_line|#ifndef NO_CS4612
DECL|macro|IOTFP_CA_MASK
mdefine_line|#define IOTFP_CA_MASK                           0x00003FFF
DECL|macro|IOTFP_PA_MASK
mdefine_line|#define IOTFP_PA_MASK                           0x3FFF0000
DECL|macro|IOTFP_CA_SHIFT
mdefine_line|#define IOTFP_CA_SHIFT                          0
DECL|macro|IOTFP_PA_SHIFT
mdefine_line|#define IOTFP_PA_SHIFT                          16
macro_line|#endif
multiline_comment|/*&n; *  The following defines are for the flags in the I/O trap control register.&n; */
macro_line|#ifndef NO_CS4612
DECL|macro|IOTCR_ITD
mdefine_line|#define IOTCR_ITD                               0x00000001
DECL|macro|IOTCR_HRV
mdefine_line|#define IOTCR_HRV                               0x00000002
DECL|macro|IOTCR_SRV
mdefine_line|#define IOTCR_SRV                               0x00000004
DECL|macro|IOTCR_DTI
mdefine_line|#define IOTCR_DTI                               0x00000008
DECL|macro|IOTCR_DFI
mdefine_line|#define IOTCR_DFI                               0x00000010
DECL|macro|IOTCR_DDP
mdefine_line|#define IOTCR_DDP                               0x00000020
DECL|macro|IOTCR_JTE
mdefine_line|#define IOTCR_JTE                               0x00000040
DECL|macro|IOTCR_PPE
mdefine_line|#define IOTCR_PPE                               0x00000080
macro_line|#endif
multiline_comment|/*&n; *  The following defines are for the flags in the direct PCI data register.&n; */
macro_line|#ifndef NO_CS4612
DECL|macro|DPCID_D_MASK
mdefine_line|#define DPCID_D_MASK                            0xFFFFFFFF
DECL|macro|DPCID_D_SHIFT
mdefine_line|#define DPCID_D_SHIFT                           0
macro_line|#endif
multiline_comment|/*&n; *  The following defines are for the flags in the direct PCI address register.&n; */
macro_line|#ifndef NO_CS4612
DECL|macro|DPCIA_A_MASK
mdefine_line|#define DPCIA_A_MASK                            0xFFFFFFFF
DECL|macro|DPCIA_A_SHIFT
mdefine_line|#define DPCIA_A_SHIFT                           0
macro_line|#endif
multiline_comment|/*&n; *  The following defines are for the flags in the direct PCI command register.&n; */
macro_line|#ifndef NO_CS4612
DECL|macro|DPCIC_C_MASK
mdefine_line|#define DPCIC_C_MASK                            0x0000000F
DECL|macro|DPCIC_C_IOREAD
mdefine_line|#define DPCIC_C_IOREAD                          0x00000002
DECL|macro|DPCIC_C_IOWRITE
mdefine_line|#define DPCIC_C_IOWRITE                         0x00000003
DECL|macro|DPCIC_BE_MASK
mdefine_line|#define DPCIC_BE_MASK                           0x000000F0
macro_line|#endif
multiline_comment|/*&n; *  The following defines are for the flags in the PC/PCI request register.&n; */
macro_line|#ifndef NO_CS4612
DECL|macro|PCPCIR_RDC_MASK
mdefine_line|#define PCPCIR_RDC_MASK                         0x00000007
DECL|macro|PCPCIR_C_MASK
mdefine_line|#define PCPCIR_C_MASK                           0x00007000
DECL|macro|PCPCIR_REQ
mdefine_line|#define PCPCIR_REQ                              0x00008000
DECL|macro|PCPCIR_RDC_SHIFT
mdefine_line|#define PCPCIR_RDC_SHIFT                        0
DECL|macro|PCPCIR_C_SHIFT
mdefine_line|#define PCPCIR_C_SHIFT                          12
macro_line|#endif
multiline_comment|/*&n; *  The following defines are for the flags in the PC/PCI grant register.&n; */
macro_line|#ifndef NO_CS4612
DECL|macro|PCPCIG_GDC_MASK
mdefine_line|#define PCPCIG_GDC_MASK                         0x00000007
DECL|macro|PCPCIG_VL
mdefine_line|#define PCPCIG_VL                               0x00008000
DECL|macro|PCPCIG_GDC_SHIFT
mdefine_line|#define PCPCIG_GDC_SHIFT                        0
macro_line|#endif
multiline_comment|/*&n; *  The following defines are for the flags in the PC/PCI master enable&n; *  register.&n; */
macro_line|#ifndef NO_CS4612
DECL|macro|PCPCIEN_EN
mdefine_line|#define PCPCIEN_EN                              0x00000001
macro_line|#endif
multiline_comment|/*&n; *  The following defines are for the flags in the extended PCI power&n; *  management control register.&n; */
macro_line|#ifndef NO_CS4612
DECL|macro|EPCIPMC_GWU
mdefine_line|#define EPCIPMC_GWU                             0x00000001
DECL|macro|EPCIPMC_FSPC
mdefine_line|#define EPCIPMC_FSPC                            0x00000002
macro_line|#endif 
multiline_comment|/*&n; *  The following defines are for the flags in the SP control register.&n; */
DECL|macro|SPCR_RUN
mdefine_line|#define SPCR_RUN                                0x00000001
DECL|macro|SPCR_STPFR
mdefine_line|#define SPCR_STPFR                              0x00000002
DECL|macro|SPCR_RUNFR
mdefine_line|#define SPCR_RUNFR                              0x00000004
DECL|macro|SPCR_TICK
mdefine_line|#define SPCR_TICK                               0x00000008
DECL|macro|SPCR_DRQEN
mdefine_line|#define SPCR_DRQEN                              0x00000020
DECL|macro|SPCR_RSTSP
mdefine_line|#define SPCR_RSTSP                              0x00000040
DECL|macro|SPCR_OREN
mdefine_line|#define SPCR_OREN                               0x00000080
macro_line|#ifndef NO_CS4612
DECL|macro|SPCR_PCIINT
mdefine_line|#define SPCR_PCIINT                             0x00000100
DECL|macro|SPCR_OINTD
mdefine_line|#define SPCR_OINTD                              0x00000200
DECL|macro|SPCR_CRE
mdefine_line|#define SPCR_CRE                                0x00008000
macro_line|#endif
multiline_comment|/*&n; *  The following defines are for the flags in the debug index register.&n; */
DECL|macro|DREG_REGID_MASK
mdefine_line|#define DREG_REGID_MASK                         0x0000007F
DECL|macro|DREG_DEBUG
mdefine_line|#define DREG_DEBUG                              0x00000080
DECL|macro|DREG_RGBK_MASK
mdefine_line|#define DREG_RGBK_MASK                          0x00000700
DECL|macro|DREG_TRAP
mdefine_line|#define DREG_TRAP                               0x00000800
macro_line|#if !defined(NO_CS4612)
macro_line|#if !defined(NO_CS4615)
DECL|macro|DREG_TRAPX
mdefine_line|#define DREG_TRAPX                              0x00001000
macro_line|#endif
macro_line|#endif
DECL|macro|DREG_REGID_SHIFT
mdefine_line|#define DREG_REGID_SHIFT                        0
DECL|macro|DREG_RGBK_SHIFT
mdefine_line|#define DREG_RGBK_SHIFT                         8
DECL|macro|DREG_RGBK_REGID_MASK
mdefine_line|#define DREG_RGBK_REGID_MASK                    0x0000077F
DECL|macro|DREG_REGID_R0
mdefine_line|#define DREG_REGID_R0                           0x00000010
DECL|macro|DREG_REGID_R1
mdefine_line|#define DREG_REGID_R1                           0x00000011
DECL|macro|DREG_REGID_R2
mdefine_line|#define DREG_REGID_R2                           0x00000012
DECL|macro|DREG_REGID_R3
mdefine_line|#define DREG_REGID_R3                           0x00000013
DECL|macro|DREG_REGID_R4
mdefine_line|#define DREG_REGID_R4                           0x00000014
DECL|macro|DREG_REGID_R5
mdefine_line|#define DREG_REGID_R5                           0x00000015
DECL|macro|DREG_REGID_R6
mdefine_line|#define DREG_REGID_R6                           0x00000016
DECL|macro|DREG_REGID_R7
mdefine_line|#define DREG_REGID_R7                           0x00000017
DECL|macro|DREG_REGID_R8
mdefine_line|#define DREG_REGID_R8                           0x00000018
DECL|macro|DREG_REGID_R9
mdefine_line|#define DREG_REGID_R9                           0x00000019
DECL|macro|DREG_REGID_RA
mdefine_line|#define DREG_REGID_RA                           0x0000001A
DECL|macro|DREG_REGID_RB
mdefine_line|#define DREG_REGID_RB                           0x0000001B
DECL|macro|DREG_REGID_RC
mdefine_line|#define DREG_REGID_RC                           0x0000001C
DECL|macro|DREG_REGID_RD
mdefine_line|#define DREG_REGID_RD                           0x0000001D
DECL|macro|DREG_REGID_RE
mdefine_line|#define DREG_REGID_RE                           0x0000001E
DECL|macro|DREG_REGID_RF
mdefine_line|#define DREG_REGID_RF                           0x0000001F
DECL|macro|DREG_REGID_RA_BUS_LOW
mdefine_line|#define DREG_REGID_RA_BUS_LOW                   0x00000020
DECL|macro|DREG_REGID_RA_BUS_HIGH
mdefine_line|#define DREG_REGID_RA_BUS_HIGH                  0x00000038
DECL|macro|DREG_REGID_YBUS_LOW
mdefine_line|#define DREG_REGID_YBUS_LOW                     0x00000050
DECL|macro|DREG_REGID_YBUS_HIGH
mdefine_line|#define DREG_REGID_YBUS_HIGH                    0x00000058
DECL|macro|DREG_REGID_TRAP_0
mdefine_line|#define DREG_REGID_TRAP_0                       0x00000100
DECL|macro|DREG_REGID_TRAP_1
mdefine_line|#define DREG_REGID_TRAP_1                       0x00000101
DECL|macro|DREG_REGID_TRAP_2
mdefine_line|#define DREG_REGID_TRAP_2                       0x00000102
DECL|macro|DREG_REGID_TRAP_3
mdefine_line|#define DREG_REGID_TRAP_3                       0x00000103
DECL|macro|DREG_REGID_TRAP_4
mdefine_line|#define DREG_REGID_TRAP_4                       0x00000104
DECL|macro|DREG_REGID_TRAP_5
mdefine_line|#define DREG_REGID_TRAP_5                       0x00000105
DECL|macro|DREG_REGID_TRAP_6
mdefine_line|#define DREG_REGID_TRAP_6                       0x00000106
DECL|macro|DREG_REGID_TRAP_7
mdefine_line|#define DREG_REGID_TRAP_7                       0x00000107
DECL|macro|DREG_REGID_INDIRECT_ADDRESS
mdefine_line|#define DREG_REGID_INDIRECT_ADDRESS             0x0000010E
DECL|macro|DREG_REGID_TOP_OF_STACK
mdefine_line|#define DREG_REGID_TOP_OF_STACK                 0x0000010F
macro_line|#if !defined(NO_CS4612)
macro_line|#if !defined(NO_CS4615)
DECL|macro|DREG_REGID_TRAP_8
mdefine_line|#define DREG_REGID_TRAP_8                       0x00000110
DECL|macro|DREG_REGID_TRAP_9
mdefine_line|#define DREG_REGID_TRAP_9                       0x00000111
DECL|macro|DREG_REGID_TRAP_10
mdefine_line|#define DREG_REGID_TRAP_10                      0x00000112
DECL|macro|DREG_REGID_TRAP_11
mdefine_line|#define DREG_REGID_TRAP_11                      0x00000113
DECL|macro|DREG_REGID_TRAP_12
mdefine_line|#define DREG_REGID_TRAP_12                      0x00000114
DECL|macro|DREG_REGID_TRAP_13
mdefine_line|#define DREG_REGID_TRAP_13                      0x00000115
DECL|macro|DREG_REGID_TRAP_14
mdefine_line|#define DREG_REGID_TRAP_14                      0x00000116
DECL|macro|DREG_REGID_TRAP_15
mdefine_line|#define DREG_REGID_TRAP_15                      0x00000117
DECL|macro|DREG_REGID_TRAP_16
mdefine_line|#define DREG_REGID_TRAP_16                      0x00000118
DECL|macro|DREG_REGID_TRAP_17
mdefine_line|#define DREG_REGID_TRAP_17                      0x00000119
DECL|macro|DREG_REGID_TRAP_18
mdefine_line|#define DREG_REGID_TRAP_18                      0x0000011A
DECL|macro|DREG_REGID_TRAP_19
mdefine_line|#define DREG_REGID_TRAP_19                      0x0000011B
DECL|macro|DREG_REGID_TRAP_20
mdefine_line|#define DREG_REGID_TRAP_20                      0x0000011C
DECL|macro|DREG_REGID_TRAP_21
mdefine_line|#define DREG_REGID_TRAP_21                      0x0000011D
DECL|macro|DREG_REGID_TRAP_22
mdefine_line|#define DREG_REGID_TRAP_22                      0x0000011E
DECL|macro|DREG_REGID_TRAP_23
mdefine_line|#define DREG_REGID_TRAP_23                      0x0000011F
macro_line|#endif
macro_line|#endif
DECL|macro|DREG_REGID_RSA0_LOW
mdefine_line|#define DREG_REGID_RSA0_LOW                     0x00000200
DECL|macro|DREG_REGID_RSA0_HIGH
mdefine_line|#define DREG_REGID_RSA0_HIGH                    0x00000201
DECL|macro|DREG_REGID_RSA1_LOW
mdefine_line|#define DREG_REGID_RSA1_LOW                     0x00000202
DECL|macro|DREG_REGID_RSA1_HIGH
mdefine_line|#define DREG_REGID_RSA1_HIGH                    0x00000203
DECL|macro|DREG_REGID_RSA2
mdefine_line|#define DREG_REGID_RSA2                         0x00000204
DECL|macro|DREG_REGID_RSA3
mdefine_line|#define DREG_REGID_RSA3                         0x00000205
DECL|macro|DREG_REGID_RSI0_LOW
mdefine_line|#define DREG_REGID_RSI0_LOW                     0x00000206
DECL|macro|DREG_REGID_RSI0_HIGH
mdefine_line|#define DREG_REGID_RSI0_HIGH                    0x00000207
DECL|macro|DREG_REGID_RSI1
mdefine_line|#define DREG_REGID_RSI1                         0x00000208
DECL|macro|DREG_REGID_RSI2
mdefine_line|#define DREG_REGID_RSI2                         0x00000209
DECL|macro|DREG_REGID_SAGUSTATUS
mdefine_line|#define DREG_REGID_SAGUSTATUS                   0x0000020A
DECL|macro|DREG_REGID_RSCONFIG01_LOW
mdefine_line|#define DREG_REGID_RSCONFIG01_LOW               0x0000020B
DECL|macro|DREG_REGID_RSCONFIG01_HIGH
mdefine_line|#define DREG_REGID_RSCONFIG01_HIGH              0x0000020C
DECL|macro|DREG_REGID_RSCONFIG23_LOW
mdefine_line|#define DREG_REGID_RSCONFIG23_LOW               0x0000020D
DECL|macro|DREG_REGID_RSCONFIG23_HIGH
mdefine_line|#define DREG_REGID_RSCONFIG23_HIGH              0x0000020E
DECL|macro|DREG_REGID_RSDMA01E
mdefine_line|#define DREG_REGID_RSDMA01E                     0x0000020F
DECL|macro|DREG_REGID_RSDMA23E
mdefine_line|#define DREG_REGID_RSDMA23E                     0x00000210
DECL|macro|DREG_REGID_RSD0_LOW
mdefine_line|#define DREG_REGID_RSD0_LOW                     0x00000211
DECL|macro|DREG_REGID_RSD0_HIGH
mdefine_line|#define DREG_REGID_RSD0_HIGH                    0x00000212
DECL|macro|DREG_REGID_RSD1_LOW
mdefine_line|#define DREG_REGID_RSD1_LOW                     0x00000213
DECL|macro|DREG_REGID_RSD1_HIGH
mdefine_line|#define DREG_REGID_RSD1_HIGH                    0x00000214
DECL|macro|DREG_REGID_RSD2_LOW
mdefine_line|#define DREG_REGID_RSD2_LOW                     0x00000215
DECL|macro|DREG_REGID_RSD2_HIGH
mdefine_line|#define DREG_REGID_RSD2_HIGH                    0x00000216
DECL|macro|DREG_REGID_RSD3_LOW
mdefine_line|#define DREG_REGID_RSD3_LOW                     0x00000217
DECL|macro|DREG_REGID_RSD3_HIGH
mdefine_line|#define DREG_REGID_RSD3_HIGH                    0x00000218
DECL|macro|DREG_REGID_SRAR_HIGH
mdefine_line|#define DREG_REGID_SRAR_HIGH                    0x0000021A
DECL|macro|DREG_REGID_SRAR_LOW
mdefine_line|#define DREG_REGID_SRAR_LOW                     0x0000021B
DECL|macro|DREG_REGID_DMA_STATE
mdefine_line|#define DREG_REGID_DMA_STATE                    0x0000021C
DECL|macro|DREG_REGID_CURRENT_DMA_STREAM
mdefine_line|#define DREG_REGID_CURRENT_DMA_STREAM           0x0000021D
DECL|macro|DREG_REGID_NEXT_DMA_STREAM
mdefine_line|#define DREG_REGID_NEXT_DMA_STREAM              0x0000021E
DECL|macro|DREG_REGID_CPU_STATUS
mdefine_line|#define DREG_REGID_CPU_STATUS                   0x00000300
DECL|macro|DREG_REGID_MAC_MODE
mdefine_line|#define DREG_REGID_MAC_MODE                     0x00000301
DECL|macro|DREG_REGID_STACK_AND_REPEAT
mdefine_line|#define DREG_REGID_STACK_AND_REPEAT             0x00000302
DECL|macro|DREG_REGID_INDEX0
mdefine_line|#define DREG_REGID_INDEX0                       0x00000304
DECL|macro|DREG_REGID_INDEX1
mdefine_line|#define DREG_REGID_INDEX1                       0x00000305
DECL|macro|DREG_REGID_DMA_STATE_0_3
mdefine_line|#define DREG_REGID_DMA_STATE_0_3                0x00000400
DECL|macro|DREG_REGID_DMA_STATE_4_7
mdefine_line|#define DREG_REGID_DMA_STATE_4_7                0x00000404
DECL|macro|DREG_REGID_DMA_STATE_8_11
mdefine_line|#define DREG_REGID_DMA_STATE_8_11               0x00000408
DECL|macro|DREG_REGID_DMA_STATE_12_15
mdefine_line|#define DREG_REGID_DMA_STATE_12_15              0x0000040C
DECL|macro|DREG_REGID_DMA_STATE_16_19
mdefine_line|#define DREG_REGID_DMA_STATE_16_19              0x00000410
DECL|macro|DREG_REGID_DMA_STATE_20_23
mdefine_line|#define DREG_REGID_DMA_STATE_20_23              0x00000414
DECL|macro|DREG_REGID_DMA_STATE_24_27
mdefine_line|#define DREG_REGID_DMA_STATE_24_27              0x00000418
DECL|macro|DREG_REGID_DMA_STATE_28_31
mdefine_line|#define DREG_REGID_DMA_STATE_28_31              0x0000041C
DECL|macro|DREG_REGID_DMA_STATE_32_35
mdefine_line|#define DREG_REGID_DMA_STATE_32_35              0x00000420
DECL|macro|DREG_REGID_DMA_STATE_36_39
mdefine_line|#define DREG_REGID_DMA_STATE_36_39              0x00000424
DECL|macro|DREG_REGID_DMA_STATE_40_43
mdefine_line|#define DREG_REGID_DMA_STATE_40_43              0x00000428
DECL|macro|DREG_REGID_DMA_STATE_44_47
mdefine_line|#define DREG_REGID_DMA_STATE_44_47              0x0000042C
DECL|macro|DREG_REGID_DMA_STATE_48_51
mdefine_line|#define DREG_REGID_DMA_STATE_48_51              0x00000430
DECL|macro|DREG_REGID_DMA_STATE_52_55
mdefine_line|#define DREG_REGID_DMA_STATE_52_55              0x00000434
DECL|macro|DREG_REGID_DMA_STATE_56_59
mdefine_line|#define DREG_REGID_DMA_STATE_56_59              0x00000438
DECL|macro|DREG_REGID_DMA_STATE_60_63
mdefine_line|#define DREG_REGID_DMA_STATE_60_63              0x0000043C
DECL|macro|DREG_REGID_DMA_STATE_64_67
mdefine_line|#define DREG_REGID_DMA_STATE_64_67              0x00000440
DECL|macro|DREG_REGID_DMA_STATE_68_71
mdefine_line|#define DREG_REGID_DMA_STATE_68_71              0x00000444
DECL|macro|DREG_REGID_DMA_STATE_72_75
mdefine_line|#define DREG_REGID_DMA_STATE_72_75              0x00000448
DECL|macro|DREG_REGID_DMA_STATE_76_79
mdefine_line|#define DREG_REGID_DMA_STATE_76_79              0x0000044C
DECL|macro|DREG_REGID_DMA_STATE_80_83
mdefine_line|#define DREG_REGID_DMA_STATE_80_83              0x00000450
DECL|macro|DREG_REGID_DMA_STATE_84_87
mdefine_line|#define DREG_REGID_DMA_STATE_84_87              0x00000454
DECL|macro|DREG_REGID_DMA_STATE_88_91
mdefine_line|#define DREG_REGID_DMA_STATE_88_91              0x00000458
DECL|macro|DREG_REGID_DMA_STATE_92_95
mdefine_line|#define DREG_REGID_DMA_STATE_92_95              0x0000045C
DECL|macro|DREG_REGID_TRAP_SELECT
mdefine_line|#define DREG_REGID_TRAP_SELECT                  0x00000500
DECL|macro|DREG_REGID_TRAP_WRITE_0
mdefine_line|#define DREG_REGID_TRAP_WRITE_0                 0x00000500
DECL|macro|DREG_REGID_TRAP_WRITE_1
mdefine_line|#define DREG_REGID_TRAP_WRITE_1                 0x00000501
DECL|macro|DREG_REGID_TRAP_WRITE_2
mdefine_line|#define DREG_REGID_TRAP_WRITE_2                 0x00000502
DECL|macro|DREG_REGID_TRAP_WRITE_3
mdefine_line|#define DREG_REGID_TRAP_WRITE_3                 0x00000503
DECL|macro|DREG_REGID_TRAP_WRITE_4
mdefine_line|#define DREG_REGID_TRAP_WRITE_4                 0x00000504
DECL|macro|DREG_REGID_TRAP_WRITE_5
mdefine_line|#define DREG_REGID_TRAP_WRITE_5                 0x00000505
DECL|macro|DREG_REGID_TRAP_WRITE_6
mdefine_line|#define DREG_REGID_TRAP_WRITE_6                 0x00000506
DECL|macro|DREG_REGID_TRAP_WRITE_7
mdefine_line|#define DREG_REGID_TRAP_WRITE_7                 0x00000507
macro_line|#if !defined(NO_CS4612)
macro_line|#if !defined(NO_CS4615)
DECL|macro|DREG_REGID_TRAP_WRITE_8
mdefine_line|#define DREG_REGID_TRAP_WRITE_8                 0x00000510
DECL|macro|DREG_REGID_TRAP_WRITE_9
mdefine_line|#define DREG_REGID_TRAP_WRITE_9                 0x00000511
DECL|macro|DREG_REGID_TRAP_WRITE_10
mdefine_line|#define DREG_REGID_TRAP_WRITE_10                0x00000512
DECL|macro|DREG_REGID_TRAP_WRITE_11
mdefine_line|#define DREG_REGID_TRAP_WRITE_11                0x00000513
DECL|macro|DREG_REGID_TRAP_WRITE_12
mdefine_line|#define DREG_REGID_TRAP_WRITE_12                0x00000514
DECL|macro|DREG_REGID_TRAP_WRITE_13
mdefine_line|#define DREG_REGID_TRAP_WRITE_13                0x00000515
DECL|macro|DREG_REGID_TRAP_WRITE_14
mdefine_line|#define DREG_REGID_TRAP_WRITE_14                0x00000516
DECL|macro|DREG_REGID_TRAP_WRITE_15
mdefine_line|#define DREG_REGID_TRAP_WRITE_15                0x00000517
DECL|macro|DREG_REGID_TRAP_WRITE_16
mdefine_line|#define DREG_REGID_TRAP_WRITE_16                0x00000518
DECL|macro|DREG_REGID_TRAP_WRITE_17
mdefine_line|#define DREG_REGID_TRAP_WRITE_17                0x00000519
DECL|macro|DREG_REGID_TRAP_WRITE_18
mdefine_line|#define DREG_REGID_TRAP_WRITE_18                0x0000051A
DECL|macro|DREG_REGID_TRAP_WRITE_19
mdefine_line|#define DREG_REGID_TRAP_WRITE_19                0x0000051B
DECL|macro|DREG_REGID_TRAP_WRITE_20
mdefine_line|#define DREG_REGID_TRAP_WRITE_20                0x0000051C
DECL|macro|DREG_REGID_TRAP_WRITE_21
mdefine_line|#define DREG_REGID_TRAP_WRITE_21                0x0000051D
DECL|macro|DREG_REGID_TRAP_WRITE_22
mdefine_line|#define DREG_REGID_TRAP_WRITE_22                0x0000051E
DECL|macro|DREG_REGID_TRAP_WRITE_23
mdefine_line|#define DREG_REGID_TRAP_WRITE_23                0x0000051F
macro_line|#endif
macro_line|#endif
DECL|macro|DREG_REGID_MAC0_ACC0_LOW
mdefine_line|#define DREG_REGID_MAC0_ACC0_LOW                0x00000600
DECL|macro|DREG_REGID_MAC0_ACC1_LOW
mdefine_line|#define DREG_REGID_MAC0_ACC1_LOW                0x00000601
DECL|macro|DREG_REGID_MAC0_ACC2_LOW
mdefine_line|#define DREG_REGID_MAC0_ACC2_LOW                0x00000602
DECL|macro|DREG_REGID_MAC0_ACC3_LOW
mdefine_line|#define DREG_REGID_MAC0_ACC3_LOW                0x00000603
DECL|macro|DREG_REGID_MAC1_ACC0_LOW
mdefine_line|#define DREG_REGID_MAC1_ACC0_LOW                0x00000604
DECL|macro|DREG_REGID_MAC1_ACC1_LOW
mdefine_line|#define DREG_REGID_MAC1_ACC1_LOW                0x00000605
DECL|macro|DREG_REGID_MAC1_ACC2_LOW
mdefine_line|#define DREG_REGID_MAC1_ACC2_LOW                0x00000606
DECL|macro|DREG_REGID_MAC1_ACC3_LOW
mdefine_line|#define DREG_REGID_MAC1_ACC3_LOW                0x00000607
DECL|macro|DREG_REGID_MAC0_ACC0_MID
mdefine_line|#define DREG_REGID_MAC0_ACC0_MID                0x00000608
DECL|macro|DREG_REGID_MAC0_ACC1_MID
mdefine_line|#define DREG_REGID_MAC0_ACC1_MID                0x00000609
DECL|macro|DREG_REGID_MAC0_ACC2_MID
mdefine_line|#define DREG_REGID_MAC0_ACC2_MID                0x0000060A
DECL|macro|DREG_REGID_MAC0_ACC3_MID
mdefine_line|#define DREG_REGID_MAC0_ACC3_MID                0x0000060B
DECL|macro|DREG_REGID_MAC1_ACC0_MID
mdefine_line|#define DREG_REGID_MAC1_ACC0_MID                0x0000060C
DECL|macro|DREG_REGID_MAC1_ACC1_MID
mdefine_line|#define DREG_REGID_MAC1_ACC1_MID                0x0000060D
DECL|macro|DREG_REGID_MAC1_ACC2_MID
mdefine_line|#define DREG_REGID_MAC1_ACC2_MID                0x0000060E
DECL|macro|DREG_REGID_MAC1_ACC3_MID
mdefine_line|#define DREG_REGID_MAC1_ACC3_MID                0x0000060F
DECL|macro|DREG_REGID_MAC0_ACC0_HIGH
mdefine_line|#define DREG_REGID_MAC0_ACC0_HIGH               0x00000610
DECL|macro|DREG_REGID_MAC0_ACC1_HIGH
mdefine_line|#define DREG_REGID_MAC0_ACC1_HIGH               0x00000611
DECL|macro|DREG_REGID_MAC0_ACC2_HIGH
mdefine_line|#define DREG_REGID_MAC0_ACC2_HIGH               0x00000612
DECL|macro|DREG_REGID_MAC0_ACC3_HIGH
mdefine_line|#define DREG_REGID_MAC0_ACC3_HIGH               0x00000613
DECL|macro|DREG_REGID_MAC1_ACC0_HIGH
mdefine_line|#define DREG_REGID_MAC1_ACC0_HIGH               0x00000614
DECL|macro|DREG_REGID_MAC1_ACC1_HIGH
mdefine_line|#define DREG_REGID_MAC1_ACC1_HIGH               0x00000615
DECL|macro|DREG_REGID_MAC1_ACC2_HIGH
mdefine_line|#define DREG_REGID_MAC1_ACC2_HIGH               0x00000616
DECL|macro|DREG_REGID_MAC1_ACC3_HIGH
mdefine_line|#define DREG_REGID_MAC1_ACC3_HIGH               0x00000617
DECL|macro|DREG_REGID_RSHOUT_LOW
mdefine_line|#define DREG_REGID_RSHOUT_LOW                   0x00000620
DECL|macro|DREG_REGID_RSHOUT_MID
mdefine_line|#define DREG_REGID_RSHOUT_MID                   0x00000628
DECL|macro|DREG_REGID_RSHOUT_HIGH
mdefine_line|#define DREG_REGID_RSHOUT_HIGH                  0x00000630
multiline_comment|/*&n; *  The following defines are for the flags in the DMA stream requestor write&n; */
DECL|macro|DSRWP_DSR_MASK
mdefine_line|#define DSRWP_DSR_MASK                          0x0000000F
DECL|macro|DSRWP_DSR_BG_RQ
mdefine_line|#define DSRWP_DSR_BG_RQ                         0x00000001
DECL|macro|DSRWP_DSR_PRIORITY_MASK
mdefine_line|#define DSRWP_DSR_PRIORITY_MASK                 0x00000006
DECL|macro|DSRWP_DSR_PRIORITY_0
mdefine_line|#define DSRWP_DSR_PRIORITY_0                    0x00000000
DECL|macro|DSRWP_DSR_PRIORITY_1
mdefine_line|#define DSRWP_DSR_PRIORITY_1                    0x00000002
DECL|macro|DSRWP_DSR_PRIORITY_2
mdefine_line|#define DSRWP_DSR_PRIORITY_2                    0x00000004
DECL|macro|DSRWP_DSR_PRIORITY_3
mdefine_line|#define DSRWP_DSR_PRIORITY_3                    0x00000006
DECL|macro|DSRWP_DSR_RQ_PENDING
mdefine_line|#define DSRWP_DSR_RQ_PENDING                    0x00000008
multiline_comment|/*&n; *  The following defines are for the flags in the trap write port register.&n; */
DECL|macro|TWPR_TW_MASK
mdefine_line|#define TWPR_TW_MASK                            0x0000FFFF
DECL|macro|TWPR_TW_SHIFT
mdefine_line|#define TWPR_TW_SHIFT                           0
multiline_comment|/*&n; *  The following defines are for the flags in the stack pointer write&n; *  register.&n; */
DECL|macro|SPWR_STKP_MASK
mdefine_line|#define SPWR_STKP_MASK                          0x0000000F
DECL|macro|SPWR_STKP_SHIFT
mdefine_line|#define SPWR_STKP_SHIFT                         0
multiline_comment|/*&n; *  The following defines are for the flags in the SP interrupt register.&n; */
DECL|macro|SPIR_FRI
mdefine_line|#define SPIR_FRI                                0x00000001
DECL|macro|SPIR_DOI
mdefine_line|#define SPIR_DOI                                0x00000002
DECL|macro|SPIR_GPI2
mdefine_line|#define SPIR_GPI2                               0x00000004
DECL|macro|SPIR_GPI3
mdefine_line|#define SPIR_GPI3                               0x00000008
DECL|macro|SPIR_IP0
mdefine_line|#define SPIR_IP0                                0x00000010
DECL|macro|SPIR_IP1
mdefine_line|#define SPIR_IP1                                0x00000020
DECL|macro|SPIR_IP2
mdefine_line|#define SPIR_IP2                                0x00000040
DECL|macro|SPIR_IP3
mdefine_line|#define SPIR_IP3                                0x00000080
multiline_comment|/*&n; *  The following defines are for the flags in the functional group 1 register.&n; */
DECL|macro|FGR1_F1S_MASK
mdefine_line|#define FGR1_F1S_MASK                           0x0000FFFF
DECL|macro|FGR1_F1S_SHIFT
mdefine_line|#define FGR1_F1S_SHIFT                          0
multiline_comment|/*&n; *  The following defines are for the flags in the SP clock status register.&n; */
DECL|macro|SPCS_FRI
mdefine_line|#define SPCS_FRI                                0x00000001
DECL|macro|SPCS_DOI
mdefine_line|#define SPCS_DOI                                0x00000002
DECL|macro|SPCS_GPI2
mdefine_line|#define SPCS_GPI2                               0x00000004
DECL|macro|SPCS_GPI3
mdefine_line|#define SPCS_GPI3                               0x00000008
DECL|macro|SPCS_IP0
mdefine_line|#define SPCS_IP0                                0x00000010
DECL|macro|SPCS_IP1
mdefine_line|#define SPCS_IP1                                0x00000020
DECL|macro|SPCS_IP2
mdefine_line|#define SPCS_IP2                                0x00000040
DECL|macro|SPCS_IP3
mdefine_line|#define SPCS_IP3                                0x00000080
DECL|macro|SPCS_SPRUN
mdefine_line|#define SPCS_SPRUN                              0x00000100
DECL|macro|SPCS_SLEEP
mdefine_line|#define SPCS_SLEEP                              0x00000200
DECL|macro|SPCS_FG
mdefine_line|#define SPCS_FG                                 0x00000400
DECL|macro|SPCS_ORUN
mdefine_line|#define SPCS_ORUN                               0x00000800
DECL|macro|SPCS_IRQ
mdefine_line|#define SPCS_IRQ                                0x00001000
DECL|macro|SPCS_FGN_MASK
mdefine_line|#define SPCS_FGN_MASK                           0x0000E000
DECL|macro|SPCS_FGN_SHIFT
mdefine_line|#define SPCS_FGN_SHIFT                          13
multiline_comment|/*&n; *  The following defines are for the flags in the SP DMA requestor status&n; *  register.&n; */
DECL|macro|SDSR_DCS_MASK
mdefine_line|#define SDSR_DCS_MASK                           0x000000FF
DECL|macro|SDSR_DCS_SHIFT
mdefine_line|#define SDSR_DCS_SHIFT                          0
DECL|macro|SDSR_DCS_NONE
mdefine_line|#define SDSR_DCS_NONE                           0x00000007
multiline_comment|/*&n; *  The following defines are for the flags in the frame timer register.&n; */
DECL|macro|FRMT_FTV_MASK
mdefine_line|#define FRMT_FTV_MASK                           0x0000FFFF
DECL|macro|FRMT_FTV_SHIFT
mdefine_line|#define FRMT_FTV_SHIFT                          0
multiline_comment|/*&n; *  The following defines are for the flags in the frame timer current count&n; *  register.&n; */
DECL|macro|FRCC_FCC_MASK
mdefine_line|#define FRCC_FCC_MASK                           0x0000FFFF
DECL|macro|FRCC_FCC_SHIFT
mdefine_line|#define FRCC_FCC_SHIFT                          0
multiline_comment|/*&n; *  The following defines are for the flags in the frame timer save count&n; *  register.&n; */
DECL|macro|FRSC_FCS_MASK
mdefine_line|#define FRSC_FCS_MASK                           0x0000FFFF
DECL|macro|FRSC_FCS_SHIFT
mdefine_line|#define FRSC_FCS_SHIFT                          0
multiline_comment|/*&n; *  The following define the various flags stored in the scatter/gather&n; *  descriptors.&n; */
DECL|macro|DMA_SG_NEXT_ENTRY_MASK
mdefine_line|#define DMA_SG_NEXT_ENTRY_MASK                  0x00000FF8
DECL|macro|DMA_SG_SAMPLE_END_MASK
mdefine_line|#define DMA_SG_SAMPLE_END_MASK                  0x0FFF0000
DECL|macro|DMA_SG_SAMPLE_END_FLAG
mdefine_line|#define DMA_SG_SAMPLE_END_FLAG                  0x10000000
DECL|macro|DMA_SG_LOOP_END_FLAG
mdefine_line|#define DMA_SG_LOOP_END_FLAG                    0x20000000
DECL|macro|DMA_SG_SIGNAL_END_FLAG
mdefine_line|#define DMA_SG_SIGNAL_END_FLAG                  0x40000000
DECL|macro|DMA_SG_SIGNAL_PAGE_FLAG
mdefine_line|#define DMA_SG_SIGNAL_PAGE_FLAG                 0x80000000
DECL|macro|DMA_SG_NEXT_ENTRY_SHIFT
mdefine_line|#define DMA_SG_NEXT_ENTRY_SHIFT                 3
DECL|macro|DMA_SG_SAMPLE_END_SHIFT
mdefine_line|#define DMA_SG_SAMPLE_END_SHIFT                 16
multiline_comment|/*&n; *  The following define the offsets of the fields within the on-chip generic&n; *  DMA requestor.&n; */
DECL|macro|DMA_RQ_CONTROL1
mdefine_line|#define DMA_RQ_CONTROL1                         0x00000000
DECL|macro|DMA_RQ_CONTROL2
mdefine_line|#define DMA_RQ_CONTROL2                         0x00000004
DECL|macro|DMA_RQ_SOURCE_ADDR
mdefine_line|#define DMA_RQ_SOURCE_ADDR                      0x00000008
DECL|macro|DMA_RQ_DESTINATION_ADDR
mdefine_line|#define DMA_RQ_DESTINATION_ADDR                 0x0000000C
DECL|macro|DMA_RQ_NEXT_PAGE_ADDR
mdefine_line|#define DMA_RQ_NEXT_PAGE_ADDR                   0x00000010
DECL|macro|DMA_RQ_NEXT_PAGE_SGDESC
mdefine_line|#define DMA_RQ_NEXT_PAGE_SGDESC                 0x00000014
DECL|macro|DMA_RQ_LOOP_START_ADDR
mdefine_line|#define DMA_RQ_LOOP_START_ADDR                  0x00000018
DECL|macro|DMA_RQ_POST_LOOP_ADDR
mdefine_line|#define DMA_RQ_POST_LOOP_ADDR                   0x0000001C
DECL|macro|DMA_RQ_PAGE_MAP_ADDR
mdefine_line|#define DMA_RQ_PAGE_MAP_ADDR                    0x00000020
multiline_comment|/*&n; *  The following defines are for the flags in the first control word of the&n; *  on-chip generic DMA requestor.&n; */
DECL|macro|DMA_RQ_C1_COUNT_MASK
mdefine_line|#define DMA_RQ_C1_COUNT_MASK                    0x000003FF
DECL|macro|DMA_RQ_C1_DESTINATION_SCATTER
mdefine_line|#define DMA_RQ_C1_DESTINATION_SCATTER           0x00001000
DECL|macro|DMA_RQ_C1_SOURCE_GATHER
mdefine_line|#define DMA_RQ_C1_SOURCE_GATHER                 0x00002000
DECL|macro|DMA_RQ_C1_DONE_FLAG
mdefine_line|#define DMA_RQ_C1_DONE_FLAG                     0x00004000
DECL|macro|DMA_RQ_C1_OPTIMIZE_STATE
mdefine_line|#define DMA_RQ_C1_OPTIMIZE_STATE                0x00008000
DECL|macro|DMA_RQ_C1_SAMPLE_END_STATE_MASK
mdefine_line|#define DMA_RQ_C1_SAMPLE_END_STATE_MASK         0x00030000
DECL|macro|DMA_RQ_C1_FULL_PAGE
mdefine_line|#define DMA_RQ_C1_FULL_PAGE                     0x00000000
DECL|macro|DMA_RQ_C1_BEFORE_SAMPLE_END
mdefine_line|#define DMA_RQ_C1_BEFORE_SAMPLE_END             0x00010000
DECL|macro|DMA_RQ_C1_PAGE_MAP_ERROR
mdefine_line|#define DMA_RQ_C1_PAGE_MAP_ERROR                0x00020000
DECL|macro|DMA_RQ_C1_AT_SAMPLE_END
mdefine_line|#define DMA_RQ_C1_AT_SAMPLE_END                 0x00030000
DECL|macro|DMA_RQ_C1_LOOP_END_STATE_MASK
mdefine_line|#define DMA_RQ_C1_LOOP_END_STATE_MASK           0x000C0000
DECL|macro|DMA_RQ_C1_NOT_LOOP_END
mdefine_line|#define DMA_RQ_C1_NOT_LOOP_END                  0x00000000
DECL|macro|DMA_RQ_C1_BEFORE_LOOP_END
mdefine_line|#define DMA_RQ_C1_BEFORE_LOOP_END               0x00040000
DECL|macro|DMA_RQ_C1_2PAGE_LOOP_BEGIN
mdefine_line|#define DMA_RQ_C1_2PAGE_LOOP_BEGIN              0x00080000
DECL|macro|DMA_RQ_C1_LOOP_BEGIN
mdefine_line|#define DMA_RQ_C1_LOOP_BEGIN                    0x000C0000
DECL|macro|DMA_RQ_C1_PAGE_MAP_MASK
mdefine_line|#define DMA_RQ_C1_PAGE_MAP_MASK                 0x00300000
DECL|macro|DMA_RQ_C1_PM_NONE_PENDING
mdefine_line|#define DMA_RQ_C1_PM_NONE_PENDING               0x00000000
DECL|macro|DMA_RQ_C1_PM_NEXT_PENDING
mdefine_line|#define DMA_RQ_C1_PM_NEXT_PENDING               0x00100000
DECL|macro|DMA_RQ_C1_PM_RESERVED
mdefine_line|#define DMA_RQ_C1_PM_RESERVED                   0x00200000
DECL|macro|DMA_RQ_C1_PM_LOOP_NEXT_PENDING
mdefine_line|#define DMA_RQ_C1_PM_LOOP_NEXT_PENDING          0x00300000
DECL|macro|DMA_RQ_C1_WRITEBACK_DEST_FLAG
mdefine_line|#define DMA_RQ_C1_WRITEBACK_DEST_FLAG           0x00400000
DECL|macro|DMA_RQ_C1_WRITEBACK_SRC_FLAG
mdefine_line|#define DMA_RQ_C1_WRITEBACK_SRC_FLAG            0x00800000
DECL|macro|DMA_RQ_C1_DEST_SIZE_MASK
mdefine_line|#define DMA_RQ_C1_DEST_SIZE_MASK                0x07000000
DECL|macro|DMA_RQ_C1_DEST_LINEAR
mdefine_line|#define DMA_RQ_C1_DEST_LINEAR                   0x00000000
DECL|macro|DMA_RQ_C1_DEST_MOD16
mdefine_line|#define DMA_RQ_C1_DEST_MOD16                    0x01000000
DECL|macro|DMA_RQ_C1_DEST_MOD32
mdefine_line|#define DMA_RQ_C1_DEST_MOD32                    0x02000000
DECL|macro|DMA_RQ_C1_DEST_MOD64
mdefine_line|#define DMA_RQ_C1_DEST_MOD64                    0x03000000
DECL|macro|DMA_RQ_C1_DEST_MOD128
mdefine_line|#define DMA_RQ_C1_DEST_MOD128                   0x04000000
DECL|macro|DMA_RQ_C1_DEST_MOD256
mdefine_line|#define DMA_RQ_C1_DEST_MOD256                   0x05000000
DECL|macro|DMA_RQ_C1_DEST_MOD512
mdefine_line|#define DMA_RQ_C1_DEST_MOD512                   0x06000000
DECL|macro|DMA_RQ_C1_DEST_MOD1024
mdefine_line|#define DMA_RQ_C1_DEST_MOD1024                  0x07000000
DECL|macro|DMA_RQ_C1_DEST_ON_HOST
mdefine_line|#define DMA_RQ_C1_DEST_ON_HOST                  0x08000000
DECL|macro|DMA_RQ_C1_SOURCE_SIZE_MASK
mdefine_line|#define DMA_RQ_C1_SOURCE_SIZE_MASK              0x70000000
DECL|macro|DMA_RQ_C1_SOURCE_LINEAR
mdefine_line|#define DMA_RQ_C1_SOURCE_LINEAR                 0x00000000
DECL|macro|DMA_RQ_C1_SOURCE_MOD16
mdefine_line|#define DMA_RQ_C1_SOURCE_MOD16                  0x10000000
DECL|macro|DMA_RQ_C1_SOURCE_MOD32
mdefine_line|#define DMA_RQ_C1_SOURCE_MOD32                  0x20000000
DECL|macro|DMA_RQ_C1_SOURCE_MOD64
mdefine_line|#define DMA_RQ_C1_SOURCE_MOD64                  0x30000000
DECL|macro|DMA_RQ_C1_SOURCE_MOD128
mdefine_line|#define DMA_RQ_C1_SOURCE_MOD128                 0x40000000
DECL|macro|DMA_RQ_C1_SOURCE_MOD256
mdefine_line|#define DMA_RQ_C1_SOURCE_MOD256                 0x50000000
DECL|macro|DMA_RQ_C1_SOURCE_MOD512
mdefine_line|#define DMA_RQ_C1_SOURCE_MOD512                 0x60000000
DECL|macro|DMA_RQ_C1_SOURCE_MOD1024
mdefine_line|#define DMA_RQ_C1_SOURCE_MOD1024                0x70000000
DECL|macro|DMA_RQ_C1_SOURCE_ON_HOST
mdefine_line|#define DMA_RQ_C1_SOURCE_ON_HOST                0x80000000
DECL|macro|DMA_RQ_C1_COUNT_SHIFT
mdefine_line|#define DMA_RQ_C1_COUNT_SHIFT                   0
multiline_comment|/*&n; *  The following defines are for the flags in the second control word of the&n; *  on-chip generic DMA requestor.&n; */
DECL|macro|DMA_RQ_C2_VIRTUAL_CHANNEL_MASK
mdefine_line|#define DMA_RQ_C2_VIRTUAL_CHANNEL_MASK          0x0000003F
DECL|macro|DMA_RQ_C2_VIRTUAL_SIGNAL_MASK
mdefine_line|#define DMA_RQ_C2_VIRTUAL_SIGNAL_MASK           0x00000300
DECL|macro|DMA_RQ_C2_NO_VIRTUAL_SIGNAL
mdefine_line|#define DMA_RQ_C2_NO_VIRTUAL_SIGNAL             0x00000000
DECL|macro|DMA_RQ_C2_SIGNAL_EVERY_DMA
mdefine_line|#define DMA_RQ_C2_SIGNAL_EVERY_DMA              0x00000100
DECL|macro|DMA_RQ_C2_SIGNAL_SOURCE_PINGPONG
mdefine_line|#define DMA_RQ_C2_SIGNAL_SOURCE_PINGPONG        0x00000200
DECL|macro|DMA_RQ_C2_SIGNAL_DEST_PINGPONG
mdefine_line|#define DMA_RQ_C2_SIGNAL_DEST_PINGPONG          0x00000300
DECL|macro|DMA_RQ_C2_AUDIO_CONVERT_MASK
mdefine_line|#define DMA_RQ_C2_AUDIO_CONVERT_MASK            0x0000F000
DECL|macro|DMA_RQ_C2_AC_NONE
mdefine_line|#define DMA_RQ_C2_AC_NONE                       0x00000000
DECL|macro|DMA_RQ_C2_AC_8_TO_16_BIT
mdefine_line|#define DMA_RQ_C2_AC_8_TO_16_BIT                0x00001000
DECL|macro|DMA_RQ_C2_AC_MONO_TO_STEREO
mdefine_line|#define DMA_RQ_C2_AC_MONO_TO_STEREO             0x00002000
DECL|macro|DMA_RQ_C2_AC_ENDIAN_CONVERT
mdefine_line|#define DMA_RQ_C2_AC_ENDIAN_CONVERT             0x00004000
DECL|macro|DMA_RQ_C2_AC_SIGNED_CONVERT
mdefine_line|#define DMA_RQ_C2_AC_SIGNED_CONVERT             0x00008000
DECL|macro|DMA_RQ_C2_LOOP_END_MASK
mdefine_line|#define DMA_RQ_C2_LOOP_END_MASK                 0x0FFF0000
DECL|macro|DMA_RQ_C2_LOOP_MASK
mdefine_line|#define DMA_RQ_C2_LOOP_MASK                     0x30000000
DECL|macro|DMA_RQ_C2_NO_LOOP
mdefine_line|#define DMA_RQ_C2_NO_LOOP                       0x00000000
DECL|macro|DMA_RQ_C2_ONE_PAGE_LOOP
mdefine_line|#define DMA_RQ_C2_ONE_PAGE_LOOP                 0x10000000
DECL|macro|DMA_RQ_C2_TWO_PAGE_LOOP
mdefine_line|#define DMA_RQ_C2_TWO_PAGE_LOOP                 0x20000000
DECL|macro|DMA_RQ_C2_MULTI_PAGE_LOOP
mdefine_line|#define DMA_RQ_C2_MULTI_PAGE_LOOP               0x30000000
DECL|macro|DMA_RQ_C2_SIGNAL_LOOP_BACK
mdefine_line|#define DMA_RQ_C2_SIGNAL_LOOP_BACK              0x40000000
DECL|macro|DMA_RQ_C2_SIGNAL_POST_BEGIN_PAGE
mdefine_line|#define DMA_RQ_C2_SIGNAL_POST_BEGIN_PAGE        0x80000000
DECL|macro|DMA_RQ_C2_VIRTUAL_CHANNEL_SHIFT
mdefine_line|#define DMA_RQ_C2_VIRTUAL_CHANNEL_SHIFT         0
DECL|macro|DMA_RQ_C2_LOOP_END_SHIFT
mdefine_line|#define DMA_RQ_C2_LOOP_END_SHIFT                16
multiline_comment|/*&n; *  The following defines are for the flags in the source and destination words&n; *  of the on-chip generic DMA requestor.&n; */
DECL|macro|DMA_RQ_SD_ADDRESS_MASK
mdefine_line|#define DMA_RQ_SD_ADDRESS_MASK                  0x0000FFFF
DECL|macro|DMA_RQ_SD_MEMORY_ID_MASK
mdefine_line|#define DMA_RQ_SD_MEMORY_ID_MASK                0x000F0000
DECL|macro|DMA_RQ_SD_SP_PARAM_ADDR
mdefine_line|#define DMA_RQ_SD_SP_PARAM_ADDR                 0x00000000
DECL|macro|DMA_RQ_SD_SP_SAMPLE_ADDR
mdefine_line|#define DMA_RQ_SD_SP_SAMPLE_ADDR                0x00010000
DECL|macro|DMA_RQ_SD_SP_PROGRAM_ADDR
mdefine_line|#define DMA_RQ_SD_SP_PROGRAM_ADDR               0x00020000
DECL|macro|DMA_RQ_SD_SP_DEBUG_ADDR
mdefine_line|#define DMA_RQ_SD_SP_DEBUG_ADDR                 0x00030000
DECL|macro|DMA_RQ_SD_OMNIMEM_ADDR
mdefine_line|#define DMA_RQ_SD_OMNIMEM_ADDR                  0x000E0000
DECL|macro|DMA_RQ_SD_END_FLAG
mdefine_line|#define DMA_RQ_SD_END_FLAG                      0x40000000
DECL|macro|DMA_RQ_SD_ERROR_FLAG
mdefine_line|#define DMA_RQ_SD_ERROR_FLAG                    0x80000000
DECL|macro|DMA_RQ_SD_ADDRESS_SHIFT
mdefine_line|#define DMA_RQ_SD_ADDRESS_SHIFT                 0
multiline_comment|/*&n; *  The following defines are for the flags in the page map address word of the&n; *  on-chip generic DMA requestor.&n; */
DECL|macro|DMA_RQ_PMA_LOOP_THIRD_PAGE_ENTRY_MASK
mdefine_line|#define DMA_RQ_PMA_LOOP_THIRD_PAGE_ENTRY_MASK   0x00000FF8
DECL|macro|DMA_RQ_PMA_PAGE_TABLE_MASK
mdefine_line|#define DMA_RQ_PMA_PAGE_TABLE_MASK              0xFFFFF000
DECL|macro|DMA_RQ_PMA_LOOP_THIRD_PAGE_ENTRY_SHIFT
mdefine_line|#define DMA_RQ_PMA_LOOP_THIRD_PAGE_ENTRY_SHIFT  3
DECL|macro|DMA_RQ_PMA_PAGE_TABLE_SHIFT
mdefine_line|#define DMA_RQ_PMA_PAGE_TABLE_SHIFT             12
DECL|macro|BA1_VARIDEC_BUF_1
mdefine_line|#define BA1_VARIDEC_BUF_1       0x000
DECL|macro|BA1_PDTC
mdefine_line|#define BA1_PDTC                0x0c0    /* BA1_PLAY_DMA_TRANSACTION_COUNT_REG */
DECL|macro|BA1_PFIE
mdefine_line|#define BA1_PFIE                0x0c4    /* BA1_PLAY_FORMAT_&amp;_INTERRUPT_ENABLE_REG */
DECL|macro|BA1_PBA
mdefine_line|#define BA1_PBA                 0x0c8    /* BA1_PLAY_BUFFER_ADDRESS */
DECL|macro|BA1_PVOL
mdefine_line|#define BA1_PVOL                0x0f8    /* BA1_PLAY_VOLUME_REG */
DECL|macro|BA1_PSRC
mdefine_line|#define BA1_PSRC                0x288    /* BA1_PLAY_SAMPLE_RATE_CORRECTION_REG */
DECL|macro|BA1_PCTL
mdefine_line|#define BA1_PCTL                0x2a4    /* BA1_PLAY_CONTROL_REG */
DECL|macro|BA1_PPI
mdefine_line|#define BA1_PPI                 0x2b4    /* BA1_PLAY_PHASE_INCREMENT_REG */
DECL|macro|BA1_CCTL
mdefine_line|#define BA1_CCTL                0x064    /* BA1_CAPTURE_CONTROL_REG */
DECL|macro|BA1_CIE
mdefine_line|#define BA1_CIE                 0x104    /* BA1_CAPTURE_INTERRUPT_ENABLE_REG */
DECL|macro|BA1_CBA
mdefine_line|#define BA1_CBA                 0x10c    /* BA1_CAPTURE_BUFFER_ADDRESS */
DECL|macro|BA1_CSRC
mdefine_line|#define BA1_CSRC                0x2c8    /* BA1_CAPTURE_SAMPLE_RATE_CORRECTION_REG */
DECL|macro|BA1_CCI
mdefine_line|#define BA1_CCI                 0x2d8    /* BA1_CAPTURE_COEFFICIENT_INCREMENT_REG */
DECL|macro|BA1_CD
mdefine_line|#define BA1_CD                  0x2e0    /* BA1_CAPTURE_DELAY_REG */
DECL|macro|BA1_CPI
mdefine_line|#define BA1_CPI                 0x2f4    /* BA1_CAPTURE_PHASE_INCREMENT_REG */
DECL|macro|BA1_CVOL
mdefine_line|#define BA1_CVOL                0x2f8    /* BA1_CAPTURE_VOLUME_REG */
DECL|macro|BA1_CFG1
mdefine_line|#define BA1_CFG1                0x134    /* BA1_CAPTURE_FRAME_GROUP_1_REG */
DECL|macro|BA1_CFG2
mdefine_line|#define BA1_CFG2                0x138    /* BA1_CAPTURE_FRAME_GROUP_2_REG */
DECL|macro|BA1_CCST
mdefine_line|#define BA1_CCST                0x13c    /* BA1_CAPTURE_CONSTANT_REG */
DECL|macro|BA1_CSPB
mdefine_line|#define BA1_CSPB                0x340    /* BA1_CAPTURE_SPB_ADDRESS */
multiline_comment|/*&n; *&n; */
DECL|macro|CS461X_MODE_OUTPUT
mdefine_line|#define CS461X_MODE_OUTPUT&t;(1&lt;&lt;0)&t; /* MIDI UART - output */ 
DECL|macro|CS461X_MODE_INPUT
mdefine_line|#define CS461X_MODE_INPUT&t;(1&lt;&lt;1)&t; /* MIDI UART - input */
singleline_comment|//****************************************************************************
singleline_comment|//
singleline_comment|// The following define the offsets of the AC97 shadow registers, which appear
singleline_comment|// as a virtual extension to the base address register zero memory range.
singleline_comment|//
singleline_comment|//****************************************************************************
DECL|macro|AC97_REG_OFFSET_MASK
mdefine_line|#define AC97_REG_OFFSET_MASK                    0x0000007EL
DECL|macro|AC97_CODEC_NUMBER_MASK
mdefine_line|#define AC97_CODEC_NUMBER_MASK                  0x00003000L
DECL|macro|BA0_AC97_RESET
mdefine_line|#define BA0_AC97_RESET                          0x00001000L
DECL|macro|BA0_AC97_MASTER_VOLUME
mdefine_line|#define BA0_AC97_MASTER_VOLUME                  0x00001002L
DECL|macro|BA0_AC97_HEADPHONE_VOLUME
mdefine_line|#define BA0_AC97_HEADPHONE_VOLUME               0x00001004L
DECL|macro|BA0_AC97_MASTER_VOLUME_MONO
mdefine_line|#define BA0_AC97_MASTER_VOLUME_MONO             0x00001006L
DECL|macro|BA0_AC97_MASTER_TONE
mdefine_line|#define BA0_AC97_MASTER_TONE                    0x00001008L
DECL|macro|BA0_AC97_PC_BEEP_VOLUME
mdefine_line|#define BA0_AC97_PC_BEEP_VOLUME                 0x0000100AL
DECL|macro|BA0_AC97_PHONE_VOLUME
mdefine_line|#define BA0_AC97_PHONE_VOLUME                   0x0000100CL
DECL|macro|BA0_AC97_MIC_VOLUME
mdefine_line|#define BA0_AC97_MIC_VOLUME                     0x0000100EL
DECL|macro|BA0_AC97_LINE_IN_VOLUME
mdefine_line|#define BA0_AC97_LINE_IN_VOLUME                 0x00001010L
DECL|macro|BA0_AC97_CD_VOLUME
mdefine_line|#define BA0_AC97_CD_VOLUME                      0x00001012L
DECL|macro|BA0_AC97_VIDEO_VOLUME
mdefine_line|#define BA0_AC97_VIDEO_VOLUME                   0x00001014L
DECL|macro|BA0_AC97_AUX_VOLUME
mdefine_line|#define BA0_AC97_AUX_VOLUME                     0x00001016L
DECL|macro|BA0_AC97_PCM_OUT_VOLUME
mdefine_line|#define BA0_AC97_PCM_OUT_VOLUME                 0x00001018L
DECL|macro|BA0_AC97_RECORD_SELECT
mdefine_line|#define BA0_AC97_RECORD_SELECT                  0x0000101AL
DECL|macro|BA0_AC97_RECORD_GAIN
mdefine_line|#define BA0_AC97_RECORD_GAIN                    0x0000101CL
DECL|macro|BA0_AC97_RECORD_GAIN_MIC
mdefine_line|#define BA0_AC97_RECORD_GAIN_MIC                0x0000101EL
DECL|macro|BA0_AC97_GENERAL_PURPOSE
mdefine_line|#define BA0_AC97_GENERAL_PURPOSE                0x00001020L
DECL|macro|BA0_AC97_3D_CONTROL
mdefine_line|#define BA0_AC97_3D_CONTROL                     0x00001022L
DECL|macro|BA0_AC97_MODEM_RATE
mdefine_line|#define BA0_AC97_MODEM_RATE                     0x00001024L
DECL|macro|BA0_AC97_POWERDOWN
mdefine_line|#define BA0_AC97_POWERDOWN                      0x00001026L
DECL|macro|BA0_AC97_EXT_AUDIO_ID
mdefine_line|#define BA0_AC97_EXT_AUDIO_ID                   0x00001028L
DECL|macro|BA0_AC97_EXT_AUDIO_POWER
mdefine_line|#define BA0_AC97_EXT_AUDIO_POWER                0x0000102AL
DECL|macro|BA0_AC97_PCM_FRONT_DAC_RATE
mdefine_line|#define BA0_AC97_PCM_FRONT_DAC_RATE             0x0000102CL
DECL|macro|BA0_AC97_PCM_SURR_DAC_RATE
mdefine_line|#define BA0_AC97_PCM_SURR_DAC_RATE              0x0000102EL
DECL|macro|BA0_AC97_PCM_LFE_DAC_RATE
mdefine_line|#define BA0_AC97_PCM_LFE_DAC_RATE               0x00001030L
DECL|macro|BA0_AC97_PCM_LR_ADC_RATE
mdefine_line|#define BA0_AC97_PCM_LR_ADC_RATE                0x00001032L
DECL|macro|BA0_AC97_MIC_ADC_RATE
mdefine_line|#define BA0_AC97_MIC_ADC_RATE                   0x00001034L
DECL|macro|BA0_AC97_6CH_VOL_C_LFE
mdefine_line|#define BA0_AC97_6CH_VOL_C_LFE                  0x00001036L
DECL|macro|BA0_AC97_6CH_VOL_SURROUND
mdefine_line|#define BA0_AC97_6CH_VOL_SURROUND               0x00001038L
DECL|macro|BA0_AC97_RESERVED_3A
mdefine_line|#define BA0_AC97_RESERVED_3A                    0x0000103AL
DECL|macro|BA0_AC97_EXT_MODEM_ID
mdefine_line|#define BA0_AC97_EXT_MODEM_ID                   0x0000103CL
DECL|macro|BA0_AC97_EXT_MODEM_POWER
mdefine_line|#define BA0_AC97_EXT_MODEM_POWER                0x0000103EL
DECL|macro|BA0_AC97_LINE1_CODEC_RATE
mdefine_line|#define BA0_AC97_LINE1_CODEC_RATE               0x00001040L
DECL|macro|BA0_AC97_LINE2_CODEC_RATE
mdefine_line|#define BA0_AC97_LINE2_CODEC_RATE               0x00001042L
DECL|macro|BA0_AC97_HANDSET_CODEC_RATE
mdefine_line|#define BA0_AC97_HANDSET_CODEC_RATE             0x00001044L
DECL|macro|BA0_AC97_LINE1_CODEC_LEVEL
mdefine_line|#define BA0_AC97_LINE1_CODEC_LEVEL              0x00001046L
DECL|macro|BA0_AC97_LINE2_CODEC_LEVEL
mdefine_line|#define BA0_AC97_LINE2_CODEC_LEVEL              0x00001048L
DECL|macro|BA0_AC97_HANDSET_CODEC_LEVEL
mdefine_line|#define BA0_AC97_HANDSET_CODEC_LEVEL            0x0000104AL
DECL|macro|BA0_AC97_GPIO_PIN_CONFIG
mdefine_line|#define BA0_AC97_GPIO_PIN_CONFIG                0x0000104CL
DECL|macro|BA0_AC97_GPIO_PIN_TYPE
mdefine_line|#define BA0_AC97_GPIO_PIN_TYPE                  0x0000104EL
DECL|macro|BA0_AC97_GPIO_PIN_STICKY
mdefine_line|#define BA0_AC97_GPIO_PIN_STICKY                0x00001050L
DECL|macro|BA0_AC97_GPIO_PIN_WAKEUP
mdefine_line|#define BA0_AC97_GPIO_PIN_WAKEUP                0x00001052L
DECL|macro|BA0_AC97_GPIO_PIN_STATUS
mdefine_line|#define BA0_AC97_GPIO_PIN_STATUS                0x00001054L
DECL|macro|BA0_AC97_MISC_MODEM_AFE_STAT
mdefine_line|#define BA0_AC97_MISC_MODEM_AFE_STAT            0x00001056L
DECL|macro|BA0_AC97_RESERVED_58
mdefine_line|#define BA0_AC97_RESERVED_58                    0x00001058L
DECL|macro|BA0_AC97_CRYSTAL_REV_N_FAB_ID
mdefine_line|#define BA0_AC97_CRYSTAL_REV_N_FAB_ID           0x0000105AL
DECL|macro|BA0_AC97_TEST_AND_MISC_CTRL
mdefine_line|#define BA0_AC97_TEST_AND_MISC_CTRL             0x0000105CL
DECL|macro|BA0_AC97_AC_MODE
mdefine_line|#define BA0_AC97_AC_MODE                        0x0000105EL
DECL|macro|BA0_AC97_MISC_CRYSTAL_CONTROL
mdefine_line|#define BA0_AC97_MISC_CRYSTAL_CONTROL           0x00001060L
DECL|macro|BA0_AC97_LINE1_HYPRID_CTRL
mdefine_line|#define BA0_AC97_LINE1_HYPRID_CTRL              0x00001062L
DECL|macro|BA0_AC97_VENDOR_RESERVED_64
mdefine_line|#define BA0_AC97_VENDOR_RESERVED_64             0x00001064L
DECL|macro|BA0_AC97_VENDOR_RESERVED_66
mdefine_line|#define BA0_AC97_VENDOR_RESERVED_66             0x00001066L
DECL|macro|BA0_AC97_SPDIF_CONTROL
mdefine_line|#define BA0_AC97_SPDIF_CONTROL                  0x00001068L
DECL|macro|BA0_AC97_VENDOR_RESERVED_6A
mdefine_line|#define BA0_AC97_VENDOR_RESERVED_6A             0x0000106AL
DECL|macro|BA0_AC97_VENDOR_RESERVED_6C
mdefine_line|#define BA0_AC97_VENDOR_RESERVED_6C             0x0000106CL
DECL|macro|BA0_AC97_VENDOR_RESERVED_6E
mdefine_line|#define BA0_AC97_VENDOR_RESERVED_6E             0x0000106EL
DECL|macro|BA0_AC97_VENDOR_RESERVED_70
mdefine_line|#define BA0_AC97_VENDOR_RESERVED_70             0x00001070L
DECL|macro|BA0_AC97_VENDOR_RESERVED_72
mdefine_line|#define BA0_AC97_VENDOR_RESERVED_72             0x00001072L
DECL|macro|BA0_AC97_VENDOR_RESERVED_74
mdefine_line|#define BA0_AC97_VENDOR_RESERVED_74             0x00001074L
DECL|macro|BA0_AC97_CAL_ADDRESS
mdefine_line|#define BA0_AC97_CAL_ADDRESS                    0x00001076L
DECL|macro|BA0_AC97_CAL_DATA
mdefine_line|#define BA0_AC97_CAL_DATA                       0x00001078L
DECL|macro|BA0_AC97_VENDOR_RESERVED_7A
mdefine_line|#define BA0_AC97_VENDOR_RESERVED_7A             0x0000107AL
DECL|macro|BA0_AC97_VENDOR_ID1
mdefine_line|#define BA0_AC97_VENDOR_ID1                     0x0000107CL
DECL|macro|BA0_AC97_VENDOR_ID2
mdefine_line|#define BA0_AC97_VENDOR_ID2                     0x0000107EL
macro_line|#endif&t;&t;&t;&t;/* __CS461X_H */
eof
