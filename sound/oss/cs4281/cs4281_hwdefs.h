singleline_comment|//****************************************************************************
singleline_comment|//
singleline_comment|// HWDEFS.H - Definitions of the registers and data structures used by the
singleline_comment|//            CS4281
singleline_comment|//
singleline_comment|// Copyright (c) 1999,2000,2001 Crystal Semiconductor Corp.
singleline_comment|//
singleline_comment|//****************************************************************************
macro_line|#ifndef _H_HWDEFS
DECL|macro|_H_HWDEFS
mdefine_line|#define _H_HWDEFS
singleline_comment|//****************************************************************************
singleline_comment|//
singleline_comment|// The following define the offsets of the registers located in the PCI
singleline_comment|// configuration space of the CS4281 part.
singleline_comment|//
singleline_comment|//****************************************************************************
DECL|macro|PCICONFIG_DEVID_VENID
mdefine_line|#define PCICONFIG_DEVID_VENID                   0x00000000L
DECL|macro|PCICONFIG_STATUS_COMMAND
mdefine_line|#define PCICONFIG_STATUS_COMMAND                0x00000004L
DECL|macro|PCICONFIG_CLASS_REVISION
mdefine_line|#define PCICONFIG_CLASS_REVISION                0x00000008L
DECL|macro|PCICONFIG_LATENCY_TIMER
mdefine_line|#define PCICONFIG_LATENCY_TIMER                 0x0000000CL
DECL|macro|PCICONFIG_BA0
mdefine_line|#define PCICONFIG_BA0                           0x00000010L
DECL|macro|PCICONFIG_BA1
mdefine_line|#define PCICONFIG_BA1                           0x00000014L
DECL|macro|PCICONFIG_SUBSYSID_SUBSYSVENID
mdefine_line|#define PCICONFIG_SUBSYSID_SUBSYSVENID          0x0000002CL
DECL|macro|PCICONFIG_INTERRUPT
mdefine_line|#define PCICONFIG_INTERRUPT                     0x0000003CL
singleline_comment|//****************************************************************************
singleline_comment|//
singleline_comment|// The following define the offsets of the registers accessed via base address
singleline_comment|// register zero on the CS4281 part.
singleline_comment|//
singleline_comment|//****************************************************************************
DECL|macro|BA0_HISR
mdefine_line|#define BA0_HISR                                0x00000000L
DECL|macro|BA0_HICR
mdefine_line|#define BA0_HICR                                0x00000008L
DECL|macro|BA0_HIMR
mdefine_line|#define BA0_HIMR                                0x0000000CL
DECL|macro|BA0_IIER
mdefine_line|#define BA0_IIER                                0x00000010L
DECL|macro|BA0_HDSR0
mdefine_line|#define BA0_HDSR0                               0x000000F0L
DECL|macro|BA0_HDSR1
mdefine_line|#define BA0_HDSR1                               0x000000F4L
DECL|macro|BA0_HDSR2
mdefine_line|#define BA0_HDSR2                               0x000000F8L
DECL|macro|BA0_HDSR3
mdefine_line|#define BA0_HDSR3                               0x000000FCL
DECL|macro|BA0_DCA0
mdefine_line|#define BA0_DCA0                                0x00000110L
DECL|macro|BA0_DCC0
mdefine_line|#define BA0_DCC0                                0x00000114L
DECL|macro|BA0_DBA0
mdefine_line|#define BA0_DBA0                                0x00000118L
DECL|macro|BA0_DBC0
mdefine_line|#define BA0_DBC0                                0x0000011CL
DECL|macro|BA0_DCA1
mdefine_line|#define BA0_DCA1                                0x00000120L
DECL|macro|BA0_DCC1
mdefine_line|#define BA0_DCC1                                0x00000124L
DECL|macro|BA0_DBA1
mdefine_line|#define BA0_DBA1                                0x00000128L
DECL|macro|BA0_DBC1
mdefine_line|#define BA0_DBC1                                0x0000012CL
DECL|macro|BA0_DCA2
mdefine_line|#define BA0_DCA2                                0x00000130L
DECL|macro|BA0_DCC2
mdefine_line|#define BA0_DCC2                                0x00000134L
DECL|macro|BA0_DBA2
mdefine_line|#define BA0_DBA2                                0x00000138L
DECL|macro|BA0_DBC2
mdefine_line|#define BA0_DBC2                                0x0000013CL
DECL|macro|BA0_DCA3
mdefine_line|#define BA0_DCA3                                0x00000140L
DECL|macro|BA0_DCC3
mdefine_line|#define BA0_DCC3                                0x00000144L
DECL|macro|BA0_DBA3
mdefine_line|#define BA0_DBA3                                0x00000148L
DECL|macro|BA0_DBC3
mdefine_line|#define BA0_DBC3                                0x0000014CL
DECL|macro|BA0_DMR0
mdefine_line|#define BA0_DMR0                                0x00000150L
DECL|macro|BA0_DCR0
mdefine_line|#define BA0_DCR0                                0x00000154L
DECL|macro|BA0_DMR1
mdefine_line|#define BA0_DMR1                                0x00000158L
DECL|macro|BA0_DCR1
mdefine_line|#define BA0_DCR1                                0x0000015CL
DECL|macro|BA0_DMR2
mdefine_line|#define BA0_DMR2                                0x00000160L
DECL|macro|BA0_DCR2
mdefine_line|#define BA0_DCR2                                0x00000164L
DECL|macro|BA0_DMR3
mdefine_line|#define BA0_DMR3                                0x00000168L
DECL|macro|BA0_DCR3
mdefine_line|#define BA0_DCR3                                0x0000016CL
DECL|macro|BA0_DLMR
mdefine_line|#define BA0_DLMR                                0x00000170L
DECL|macro|BA0_DLSR
mdefine_line|#define BA0_DLSR                                0x00000174L
DECL|macro|BA0_FCR0
mdefine_line|#define BA0_FCR0                                0x00000180L
DECL|macro|BA0_FCR1
mdefine_line|#define BA0_FCR1                                0x00000184L
DECL|macro|BA0_FCR2
mdefine_line|#define BA0_FCR2                                0x00000188L
DECL|macro|BA0_FCR3
mdefine_line|#define BA0_FCR3                                0x0000018CL
DECL|macro|BA0_FPDR0
mdefine_line|#define BA0_FPDR0                               0x00000190L
DECL|macro|BA0_FPDR1
mdefine_line|#define BA0_FPDR1                               0x00000194L
DECL|macro|BA0_FPDR2
mdefine_line|#define BA0_FPDR2                               0x00000198L
DECL|macro|BA0_FPDR3
mdefine_line|#define BA0_FPDR3                               0x0000019CL
DECL|macro|BA0_FCHS
mdefine_line|#define BA0_FCHS                                0x0000020CL
DECL|macro|BA0_FSIC0
mdefine_line|#define BA0_FSIC0                               0x00000210L
DECL|macro|BA0_FSIC1
mdefine_line|#define BA0_FSIC1                               0x00000214L
DECL|macro|BA0_FSIC2
mdefine_line|#define BA0_FSIC2                               0x00000218L
DECL|macro|BA0_FSIC3
mdefine_line|#define BA0_FSIC3                               0x0000021CL
DECL|macro|BA0_PCICFG00
mdefine_line|#define BA0_PCICFG00                            0x00000300L
DECL|macro|BA0_PCICFG04
mdefine_line|#define BA0_PCICFG04                            0x00000304L
DECL|macro|BA0_PCICFG08
mdefine_line|#define BA0_PCICFG08                            0x00000308L
DECL|macro|BA0_PCICFG0C
mdefine_line|#define BA0_PCICFG0C                            0x0000030CL
DECL|macro|BA0_PCICFG10
mdefine_line|#define BA0_PCICFG10                            0x00000310L
DECL|macro|BA0_PCICFG14
mdefine_line|#define BA0_PCICFG14                            0x00000314L
DECL|macro|BA0_PCICFG18
mdefine_line|#define BA0_PCICFG18                            0x00000318L
DECL|macro|BA0_PCICFG1C
mdefine_line|#define BA0_PCICFG1C                            0x0000031CL
DECL|macro|BA0_PCICFG20
mdefine_line|#define BA0_PCICFG20                            0x00000320L
DECL|macro|BA0_PCICFG24
mdefine_line|#define BA0_PCICFG24                            0x00000324L
DECL|macro|BA0_PCICFG28
mdefine_line|#define BA0_PCICFG28                            0x00000328L
DECL|macro|BA0_PCICFG2C
mdefine_line|#define BA0_PCICFG2C                            0x0000032CL
DECL|macro|BA0_PCICFG30
mdefine_line|#define BA0_PCICFG30                            0x00000330L
DECL|macro|BA0_PCICFG34
mdefine_line|#define BA0_PCICFG34                            0x00000334L
DECL|macro|BA0_PCICFG38
mdefine_line|#define BA0_PCICFG38                            0x00000338L
DECL|macro|BA0_PCICFG3C
mdefine_line|#define BA0_PCICFG3C                            0x0000033CL
DECL|macro|BA0_PCICFG40
mdefine_line|#define BA0_PCICFG40                            0x00000340L
DECL|macro|BA0_PMCS
mdefine_line|#define BA0_PMCS                                0x00000344L
DECL|macro|BA0_CWPR
mdefine_line|#define BA0_CWPR                                0x000003E0L
DECL|macro|BA0_EPPMC
mdefine_line|#define BA0_EPPMC                               0x000003E4L
DECL|macro|BA0_GPIOR
mdefine_line|#define BA0_GPIOR                               0x000003E8L
DECL|macro|BA0_SPMC
mdefine_line|#define BA0_SPMC                                0x000003ECL
DECL|macro|BA0_CFLR
mdefine_line|#define BA0_CFLR                                0x000003F0L
DECL|macro|BA0_IISR
mdefine_line|#define BA0_IISR                                0x000003F4L
DECL|macro|BA0_TMS
mdefine_line|#define BA0_TMS                                 0x000003F8L
DECL|macro|BA0_SSVID
mdefine_line|#define BA0_SSVID                               0x000003FCL
DECL|macro|BA0_CLKCR1
mdefine_line|#define BA0_CLKCR1                              0x00000400L
DECL|macro|BA0_FRR
mdefine_line|#define BA0_FRR                                 0x00000410L
DECL|macro|BA0_SLT12O
mdefine_line|#define BA0_SLT12O                              0x0000041CL
DECL|macro|BA0_SERMC
mdefine_line|#define BA0_SERMC                               0x00000420L
DECL|macro|BA0_SERC1
mdefine_line|#define BA0_SERC1                               0x00000428L
DECL|macro|BA0_SERC2
mdefine_line|#define BA0_SERC2                               0x0000042CL
DECL|macro|BA0_SLT12M
mdefine_line|#define BA0_SLT12M                              0x0000045CL
DECL|macro|BA0_ACCTL
mdefine_line|#define BA0_ACCTL                               0x00000460L
DECL|macro|BA0_ACSTS
mdefine_line|#define BA0_ACSTS                               0x00000464L
DECL|macro|BA0_ACOSV
mdefine_line|#define BA0_ACOSV                               0x00000468L
DECL|macro|BA0_ACCAD
mdefine_line|#define BA0_ACCAD                               0x0000046CL
DECL|macro|BA0_ACCDA
mdefine_line|#define BA0_ACCDA                               0x00000470L
DECL|macro|BA0_ACISV
mdefine_line|#define BA0_ACISV                               0x00000474L
DECL|macro|BA0_ACSAD
mdefine_line|#define BA0_ACSAD                               0x00000478L
DECL|macro|BA0_ACSDA
mdefine_line|#define BA0_ACSDA                               0x0000047CL
DECL|macro|BA0_JSPT
mdefine_line|#define BA0_JSPT                                0x00000480L
DECL|macro|BA0_JSCTL
mdefine_line|#define BA0_JSCTL                               0x00000484L
DECL|macro|BA0_MIDCR
mdefine_line|#define BA0_MIDCR                               0x00000490L
DECL|macro|BA0_MIDCMD
mdefine_line|#define BA0_MIDCMD                              0x00000494L
DECL|macro|BA0_MIDSR
mdefine_line|#define BA0_MIDSR                               0x00000494L
DECL|macro|BA0_MIDWP
mdefine_line|#define BA0_MIDWP                               0x00000498L
DECL|macro|BA0_MIDRP
mdefine_line|#define BA0_MIDRP                               0x0000049CL
DECL|macro|BA0_AODSD1
mdefine_line|#define BA0_AODSD1                              0x000004A8L
DECL|macro|BA0_AODSD2
mdefine_line|#define BA0_AODSD2                              0x000004ACL
DECL|macro|BA0_CFGI
mdefine_line|#define BA0_CFGI                                0x000004B0L
DECL|macro|BA0_SLT12M2
mdefine_line|#define BA0_SLT12M2                             0x000004DCL
DECL|macro|BA0_ACSTS2
mdefine_line|#define BA0_ACSTS2                              0x000004E4L
DECL|macro|BA0_ACISV2
mdefine_line|#define BA0_ACISV2                              0x000004F4L
DECL|macro|BA0_ACSAD2
mdefine_line|#define BA0_ACSAD2                              0x000004F8L
DECL|macro|BA0_ACSDA2
mdefine_line|#define BA0_ACSDA2                              0x000004FCL
DECL|macro|BA0_IOTGP
mdefine_line|#define BA0_IOTGP                               0x00000500L
DECL|macro|BA0_IOTSB
mdefine_line|#define BA0_IOTSB                               0x00000504L
DECL|macro|BA0_IOTFM
mdefine_line|#define BA0_IOTFM                               0x00000508L
DECL|macro|BA0_IOTDMA
mdefine_line|#define BA0_IOTDMA                              0x0000050CL
DECL|macro|BA0_IOTAC0
mdefine_line|#define BA0_IOTAC0                              0x00000500L
DECL|macro|BA0_IOTAC1
mdefine_line|#define BA0_IOTAC1                              0x00000504L
DECL|macro|BA0_IOTAC2
mdefine_line|#define BA0_IOTAC2                              0x00000508L
DECL|macro|BA0_IOTAC3
mdefine_line|#define BA0_IOTAC3                              0x0000050CL
DECL|macro|BA0_IOTPCP
mdefine_line|#define BA0_IOTPCP                              0x0000052CL
DECL|macro|BA0_IOTCC
mdefine_line|#define BA0_IOTCC                               0x00000530L
DECL|macro|BA0_IOTCR
mdefine_line|#define BA0_IOTCR                               0x0000058CL
DECL|macro|BA0_PCPRR
mdefine_line|#define BA0_PCPRR                               0x00000600L
DECL|macro|BA0_PCPGR
mdefine_line|#define BA0_PCPGR                               0x00000604L
DECL|macro|BA0_PCPCR
mdefine_line|#define BA0_PCPCR                               0x00000608L
DECL|macro|BA0_PCPCIEN
mdefine_line|#define BA0_PCPCIEN                             0x00000608L
DECL|macro|BA0_SBMAR
mdefine_line|#define BA0_SBMAR                               0x00000700L
DECL|macro|BA0_SBMDR
mdefine_line|#define BA0_SBMDR                               0x00000704L
DECL|macro|BA0_SBRR
mdefine_line|#define BA0_SBRR                                0x00000708L
DECL|macro|BA0_SBRDP
mdefine_line|#define BA0_SBRDP                               0x0000070CL
DECL|macro|BA0_SBWDP
mdefine_line|#define BA0_SBWDP                               0x00000710L
DECL|macro|BA0_SBWBS
mdefine_line|#define BA0_SBWBS                               0x00000710L
DECL|macro|BA0_SBRBS
mdefine_line|#define BA0_SBRBS                               0x00000714L
DECL|macro|BA0_FMSR
mdefine_line|#define BA0_FMSR                                0x00000730L
DECL|macro|BA0_B0AP
mdefine_line|#define BA0_B0AP                                0x00000730L
DECL|macro|BA0_FMDP
mdefine_line|#define BA0_FMDP                                0x00000734L
DECL|macro|BA0_B1AP
mdefine_line|#define BA0_B1AP                                0x00000738L
DECL|macro|BA0_B1DP
mdefine_line|#define BA0_B1DP                                0x0000073CL
DECL|macro|BA0_SSPM
mdefine_line|#define BA0_SSPM                                0x00000740L
DECL|macro|BA0_DACSR
mdefine_line|#define BA0_DACSR                               0x00000744L
DECL|macro|BA0_ADCSR
mdefine_line|#define BA0_ADCSR                               0x00000748L
DECL|macro|BA0_SSCR
mdefine_line|#define BA0_SSCR                                0x0000074CL
DECL|macro|BA0_FMLVC
mdefine_line|#define BA0_FMLVC                               0x00000754L
DECL|macro|BA0_FMRVC
mdefine_line|#define BA0_FMRVC                               0x00000758L
DECL|macro|BA0_SRCSA
mdefine_line|#define BA0_SRCSA                               0x0000075CL
DECL|macro|BA0_PPLVC
mdefine_line|#define BA0_PPLVC                               0x00000760L
DECL|macro|BA0_PPRVC
mdefine_line|#define BA0_PPRVC                               0x00000764L
DECL|macro|BA0_PASR
mdefine_line|#define BA0_PASR                                0x00000768L
DECL|macro|BA0_CASR
mdefine_line|#define BA0_CASR                                0x0000076CL
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
singleline_comment|//****************************************************************************
singleline_comment|//
singleline_comment|// The following define the offsets of the registers and memories accessed via
singleline_comment|// base address register one on the CS4281 part.
singleline_comment|//
singleline_comment|//****************************************************************************
singleline_comment|//****************************************************************************
singleline_comment|//
singleline_comment|// The following defines are for the flags in the PCI device ID/vendor ID
singleline_comment|// register.
singleline_comment|//
singleline_comment|//****************************************************************************
DECL|macro|PDV_VENID_MASK
mdefine_line|#define PDV_VENID_MASK                          0x0000FFFFL
DECL|macro|PDV_DEVID_MASK
mdefine_line|#define PDV_DEVID_MASK                          0xFFFF0000L
DECL|macro|PDV_VENID_SHIFT
mdefine_line|#define PDV_VENID_SHIFT                         0L
DECL|macro|PDV_DEVID_SHIFT
mdefine_line|#define PDV_DEVID_SHIFT                         16L
DECL|macro|VENID_CIRRUS_LOGIC
mdefine_line|#define VENID_CIRRUS_LOGIC                      0x1013L
DECL|macro|DEVID_CS4281
mdefine_line|#define DEVID_CS4281                            0x6005L
singleline_comment|//****************************************************************************
singleline_comment|//
singleline_comment|// The following defines are for the flags in the PCI status and command
singleline_comment|// register.
singleline_comment|//
singleline_comment|//****************************************************************************
DECL|macro|PSC_IO_SPACE_ENABLE
mdefine_line|#define PSC_IO_SPACE_ENABLE                     0x00000001L
DECL|macro|PSC_MEMORY_SPACE_ENABLE
mdefine_line|#define PSC_MEMORY_SPACE_ENABLE                 0x00000002L
DECL|macro|PSC_BUS_MASTER_ENABLE
mdefine_line|#define PSC_BUS_MASTER_ENABLE                   0x00000004L
DECL|macro|PSC_SPECIAL_CYCLES
mdefine_line|#define PSC_SPECIAL_CYCLES                      0x00000008L
DECL|macro|PSC_MWI_ENABLE
mdefine_line|#define PSC_MWI_ENABLE                          0x00000010L
DECL|macro|PSC_VGA_PALETTE_SNOOP
mdefine_line|#define PSC_VGA_PALETTE_SNOOP                   0x00000020L
DECL|macro|PSC_PARITY_RESPONSE
mdefine_line|#define PSC_PARITY_RESPONSE                     0x00000040L
DECL|macro|PSC_WAIT_CONTROL
mdefine_line|#define PSC_WAIT_CONTROL                        0x00000080L
DECL|macro|PSC_SERR_ENABLE
mdefine_line|#define PSC_SERR_ENABLE                         0x00000100L
DECL|macro|PSC_FAST_B2B_ENABLE
mdefine_line|#define PSC_FAST_B2B_ENABLE                     0x00000200L
DECL|macro|PSC_UDF_MASK
mdefine_line|#define PSC_UDF_MASK                            0x007F0000L
DECL|macro|PSC_FAST_B2B_CAPABLE
mdefine_line|#define PSC_FAST_B2B_CAPABLE                    0x00800000L
DECL|macro|PSC_PARITY_ERROR_DETECTED
mdefine_line|#define PSC_PARITY_ERROR_DETECTED               0x01000000L
DECL|macro|PSC_DEVSEL_TIMING_MASK
mdefine_line|#define PSC_DEVSEL_TIMING_MASK                  0x06000000L
DECL|macro|PSC_TARGET_ABORT_SIGNALLED
mdefine_line|#define PSC_TARGET_ABORT_SIGNALLED              0x08000000L
DECL|macro|PSC_RECEIVED_TARGET_ABORT
mdefine_line|#define PSC_RECEIVED_TARGET_ABORT               0x10000000L
DECL|macro|PSC_RECEIVED_MASTER_ABORT
mdefine_line|#define PSC_RECEIVED_MASTER_ABORT               0x20000000L
DECL|macro|PSC_SIGNALLED_SERR
mdefine_line|#define PSC_SIGNALLED_SERR                      0x40000000L
DECL|macro|PSC_DETECTED_PARITY_ERROR
mdefine_line|#define PSC_DETECTED_PARITY_ERROR               0x80000000L
DECL|macro|PSC_UDF_SHIFT
mdefine_line|#define PSC_UDF_SHIFT                           16L
DECL|macro|PSC_DEVSEL_TIMING_SHIFT
mdefine_line|#define PSC_DEVSEL_TIMING_SHIFT                 25L
singleline_comment|//****************************************************************************
singleline_comment|//
singleline_comment|// The following defines are for the flags in the PCI class/revision ID
singleline_comment|// register.
singleline_comment|//
singleline_comment|//****************************************************************************
DECL|macro|PCR_REVID_MASK
mdefine_line|#define PCR_REVID_MASK                          0x000000FFL
DECL|macro|PCR_INTERFACE_MASK
mdefine_line|#define PCR_INTERFACE_MASK                      0x0000FF00L
DECL|macro|PCR_SUBCLASS_MASK
mdefine_line|#define PCR_SUBCLASS_MASK                       0x00FF0000L
DECL|macro|PCR_CLASS_MASK
mdefine_line|#define PCR_CLASS_MASK                          0xFF000000L
DECL|macro|PCR_REVID_SHIFT
mdefine_line|#define PCR_REVID_SHIFT                         0L
DECL|macro|PCR_INTERFACE_SHIFT
mdefine_line|#define PCR_INTERFACE_SHIFT                     8L
DECL|macro|PCR_SUBCLASS_SHIFT
mdefine_line|#define PCR_SUBCLASS_SHIFT                      16L
DECL|macro|PCR_CLASS_SHIFT
mdefine_line|#define PCR_CLASS_SHIFT                         24L
singleline_comment|//****************************************************************************
singleline_comment|//
singleline_comment|// The following defines are for the flags in the PCI latency timer register.
singleline_comment|//
singleline_comment|//****************************************************************************
DECL|macro|PLT_CACHE_LINE_SIZE_MASK
mdefine_line|#define PLT_CACHE_LINE_SIZE_MASK                0x000000FFL
DECL|macro|PLT_LATENCY_TIMER_MASK
mdefine_line|#define PLT_LATENCY_TIMER_MASK                  0x0000FF00L
DECL|macro|PLT_HEADER_TYPE_MASK
mdefine_line|#define PLT_HEADER_TYPE_MASK                    0x00FF0000L
DECL|macro|PLT_BIST_MASK
mdefine_line|#define PLT_BIST_MASK                           0xFF000000L
DECL|macro|PLT_CACHE_LINE_SIZE_SHIFT
mdefine_line|#define PLT_CACHE_LINE_SIZE_SHIFT               0L
DECL|macro|PLT_LATENCY_TIMER_SHIFT
mdefine_line|#define PLT_LATENCY_TIMER_SHIFT                 8L
DECL|macro|PLT_HEADER_TYPE_SHIFT
mdefine_line|#define PLT_HEADER_TYPE_SHIFT                   16L
DECL|macro|PLT_BIST_SHIFT
mdefine_line|#define PLT_BIST_SHIFT                          24L
singleline_comment|//****************************************************************************
singleline_comment|//
singleline_comment|// The following defines are for the flags in the PCI base address registers.
singleline_comment|//
singleline_comment|//****************************************************************************
DECL|macro|PBAR_MEMORY_SPACE_INDICATOR
mdefine_line|#define PBAR_MEMORY_SPACE_INDICATOR             0x00000001L
DECL|macro|PBAR_LOCATION_TYPE_MASK
mdefine_line|#define PBAR_LOCATION_TYPE_MASK                 0x00000006L
DECL|macro|PBAR_NOT_PREFETCHABLE
mdefine_line|#define PBAR_NOT_PREFETCHABLE                   0x00000008L
DECL|macro|PBAR_ADDRESS_MASK
mdefine_line|#define PBAR_ADDRESS_MASK                       0xFFFFFFF0L
DECL|macro|PBAR_LOCATION_TYPE_SHIFT
mdefine_line|#define PBAR_LOCATION_TYPE_SHIFT                1L
singleline_comment|//****************************************************************************
singleline_comment|//
singleline_comment|// The following defines are for the flags in the PCI subsystem ID/subsystem
singleline_comment|// vendor ID register.
singleline_comment|//
singleline_comment|//****************************************************************************
DECL|macro|PSS_SUBSYSTEM_VENDOR_ID_MASK
mdefine_line|#define PSS_SUBSYSTEM_VENDOR_ID_MASK            0x0000FFFFL
DECL|macro|PSS_SUBSYSTEM_ID_MASK
mdefine_line|#define PSS_SUBSYSTEM_ID_MASK                   0xFFFF0000L
DECL|macro|PSS_SUBSYSTEM_VENDOR_ID_SHIFT
mdefine_line|#define PSS_SUBSYSTEM_VENDOR_ID_SHIFT           0L
DECL|macro|PSS_SUBSYSTEM_ID_SHIFT
mdefine_line|#define PSS_SUBSYSTEM_ID_SHIFT                  16L
singleline_comment|//****************************************************************************
singleline_comment|//
singleline_comment|// The following defines are for the flags in the PCI interrupt register.
singleline_comment|//
singleline_comment|//****************************************************************************
DECL|macro|PI_LINE_MASK
mdefine_line|#define PI_LINE_MASK                            0x000000FFL
DECL|macro|PI_PIN_MASK
mdefine_line|#define PI_PIN_MASK                             0x0000FF00L
DECL|macro|PI_MIN_GRANT_MASK
mdefine_line|#define PI_MIN_GRANT_MASK                       0x00FF0000L
DECL|macro|PI_MAX_LATENCY_MASK
mdefine_line|#define PI_MAX_LATENCY_MASK                     0xFF000000L
DECL|macro|PI_LINE_SHIFT
mdefine_line|#define PI_LINE_SHIFT                           0L
DECL|macro|PI_PIN_SHIFT
mdefine_line|#define PI_PIN_SHIFT                            8L
DECL|macro|PI_MIN_GRANT_SHIFT
mdefine_line|#define PI_MIN_GRANT_SHIFT                      16L
DECL|macro|PI_MAX_LATENCY_SHIFT
mdefine_line|#define PI_MAX_LATENCY_SHIFT                    24L
singleline_comment|//****************************************************************************
singleline_comment|//
singleline_comment|// The following defines are for the flags in the host interrupt status
singleline_comment|// register.
singleline_comment|//
singleline_comment|//****************************************************************************
DECL|macro|HISR_HVOLMASK
mdefine_line|#define HISR_HVOLMASK                            0x00000003L
DECL|macro|HISR_VDNI
mdefine_line|#define HISR_VDNI                                0x00000001L
DECL|macro|HISR_VUPI
mdefine_line|#define HISR_VUPI                                0x00000002L
DECL|macro|HISR_GP1I
mdefine_line|#define HISR_GP1I                                0x00000004L
DECL|macro|HISR_GP3I
mdefine_line|#define HISR_GP3I                                0x00000008L
DECL|macro|HISR_GPSI
mdefine_line|#define HISR_GPSI                                0x00000010L
DECL|macro|HISR_GPPI
mdefine_line|#define HISR_GPPI                                0x00000020L
DECL|macro|HISR_DMAI
mdefine_line|#define HISR_DMAI                                0x00040000L
DECL|macro|HISR_FIFOI
mdefine_line|#define HISR_FIFOI                               0x00100000L
DECL|macro|HISR_HVOL
mdefine_line|#define HISR_HVOL                                0x00200000L
DECL|macro|HISR_MIDI
mdefine_line|#define HISR_MIDI                                0x00400000L
DECL|macro|HISR_SBINT
mdefine_line|#define HISR_SBINT                               0x00800000L
DECL|macro|HISR_INTENA
mdefine_line|#define HISR_INTENA                              0x80000000L
DECL|macro|HISR_DMA_MASK
mdefine_line|#define HISR_DMA_MASK                            0x00000F00L
DECL|macro|HISR_FIFO_MASK
mdefine_line|#define HISR_FIFO_MASK                           0x0000F000L
DECL|macro|HISR_DMA_SHIFT
mdefine_line|#define HISR_DMA_SHIFT                           8L
DECL|macro|HISR_FIFO_SHIFT
mdefine_line|#define HISR_FIFO_SHIFT                          12L
DECL|macro|HISR_FIFO0
mdefine_line|#define HISR_FIFO0                               0x00001000L
DECL|macro|HISR_FIFO1
mdefine_line|#define HISR_FIFO1                               0x00002000L
DECL|macro|HISR_FIFO2
mdefine_line|#define HISR_FIFO2                               0x00004000L
DECL|macro|HISR_FIFO3
mdefine_line|#define HISR_FIFO3                               0x00008000L
DECL|macro|HISR_DMA0
mdefine_line|#define HISR_DMA0                                0x00000100L
DECL|macro|HISR_DMA1
mdefine_line|#define HISR_DMA1                                0x00000200L
DECL|macro|HISR_DMA2
mdefine_line|#define HISR_DMA2                                0x00000400L
DECL|macro|HISR_DMA3
mdefine_line|#define HISR_DMA3                                0x00000800L
DECL|macro|HISR_RESERVED
mdefine_line|#define HISR_RESERVED                            0x40000000L
singleline_comment|//****************************************************************************
singleline_comment|//
singleline_comment|// The following defines are for the flags in the host interrupt control
singleline_comment|// register.
singleline_comment|//
singleline_comment|//****************************************************************************
DECL|macro|HICR_IEV
mdefine_line|#define HICR_IEV                                 0x00000001L
DECL|macro|HICR_CHGM
mdefine_line|#define HICR_CHGM                                0x00000002L
singleline_comment|//****************************************************************************
singleline_comment|//
singleline_comment|// The following defines are for the flags in the DMA Mode Register n
singleline_comment|// (DMRn)
singleline_comment|//
singleline_comment|//****************************************************************************
DECL|macro|DMRn_TR_MASK
mdefine_line|#define DMRn_TR_MASK                             0x0000000CL
DECL|macro|DMRn_TR_SHIFT
mdefine_line|#define DMRn_TR_SHIFT                            2L
DECL|macro|DMRn_AUTO
mdefine_line|#define DMRn_AUTO                                0x00000010L
DECL|macro|DMRn_TR_READ
mdefine_line|#define DMRn_TR_READ                             0x00000008L
DECL|macro|DMRn_TR_WRITE
mdefine_line|#define DMRn_TR_WRITE                            0x00000004L
DECL|macro|DMRn_TYPE_MASK
mdefine_line|#define DMRn_TYPE_MASK                           0x000000C0L
DECL|macro|DMRn_TYPE_SHIFT
mdefine_line|#define DMRn_TYPE_SHIFT                          6L
DECL|macro|DMRn_SIZE8
mdefine_line|#define DMRn_SIZE8                               0x00010000L
DECL|macro|DMRn_MONO
mdefine_line|#define DMRn_MONO                                0x00020000L
DECL|macro|DMRn_BEND
mdefine_line|#define DMRn_BEND                                0x00040000L
DECL|macro|DMRn_USIGN
mdefine_line|#define DMRn_USIGN                               0x00080000L
DECL|macro|DMRn_SIZE20
mdefine_line|#define DMRn_SIZE20                              0x00100000L
DECL|macro|DMRn_SWAPC
mdefine_line|#define DMRn_SWAPC                               0x00400000L
DECL|macro|DMRn_CBC
mdefine_line|#define DMRn_CBC                                 0x01000000L
DECL|macro|DMRn_TBC
mdefine_line|#define DMRn_TBC                                 0x02000000L
DECL|macro|DMRn_POLL
mdefine_line|#define DMRn_POLL                                0x10000000L
DECL|macro|DMRn_DMA
mdefine_line|#define DMRn_DMA                                 0x20000000L
DECL|macro|DMRn_FSEL_MASK
mdefine_line|#define DMRn_FSEL_MASK                           0xC0000000L
DECL|macro|DMRn_FSEL_SHIFT
mdefine_line|#define DMRn_FSEL_SHIFT                          30L
DECL|macro|DMRn_FSEL0
mdefine_line|#define DMRn_FSEL0                               0x00000000L
DECL|macro|DMRn_FSEL1
mdefine_line|#define DMRn_FSEL1                               0x40000000L
DECL|macro|DMRn_FSEL2
mdefine_line|#define DMRn_FSEL2                               0x80000000L
DECL|macro|DMRn_FSEL3
mdefine_line|#define DMRn_FSEL3                               0xC0000000L
singleline_comment|//****************************************************************************
singleline_comment|//
singleline_comment|// The following defines are for the flags in the DMA Command Register n
singleline_comment|// (DCRn)
singleline_comment|//
singleline_comment|//****************************************************************************
DECL|macro|DCRn_HTCIE
mdefine_line|#define DCRn_HTCIE                               0x00020000L
DECL|macro|DCRn_TCIE
mdefine_line|#define DCRn_TCIE                                0x00010000L
DECL|macro|DCRn_MSK
mdefine_line|#define DCRn_MSK                                 0x00000001L
singleline_comment|//****************************************************************************
singleline_comment|//
singleline_comment|// The following defines are for the flags in the FIFO Control 
singleline_comment|// register n.(FCRn)
singleline_comment|//
singleline_comment|//****************************************************************************
DECL|macro|FCRn_OF_MASK
mdefine_line|#define FCRn_OF_MASK                            0x0000007FL
DECL|macro|FCRn_OF_SHIFT
mdefine_line|#define FCRn_OF_SHIFT                           0L
DECL|macro|FCRn_SZ_MASK
mdefine_line|#define FCRn_SZ_MASK                            0x00007F00L
DECL|macro|FCRn_SZ_SHIFT
mdefine_line|#define FCRn_SZ_SHIFT                           8L
DECL|macro|FCRn_LS_MASK
mdefine_line|#define FCRn_LS_MASK                            0x001F0000L
DECL|macro|FCRn_LS_SHIFT
mdefine_line|#define FCRn_LS_SHIFT                           16L
DECL|macro|FCRn_RS_MASK
mdefine_line|#define FCRn_RS_MASK                            0x1F000000L
DECL|macro|FCRn_RS_SHIFT
mdefine_line|#define FCRn_RS_SHIFT                           24L
DECL|macro|FCRn_FEN
mdefine_line|#define FCRn_FEN                                0x80000000L
DECL|macro|FCRn_PSH
mdefine_line|#define FCRn_PSH                                0x20000000L
DECL|macro|FCRn_DACZ
mdefine_line|#define FCRn_DACZ                               0x40000000L
singleline_comment|//****************************************************************************
singleline_comment|//
singleline_comment|// The following defines are for the flags in the serial port Power Management
singleline_comment|// control register.(SPMC)
singleline_comment|//
singleline_comment|//****************************************************************************
DECL|macro|SPMC_RSTN
mdefine_line|#define SPMC_RSTN                               0x00000001L
DECL|macro|SPMC_ASYN
mdefine_line|#define SPMC_ASYN                               0x00000002L
DECL|macro|SPMC_WUP1
mdefine_line|#define SPMC_WUP1                               0x00000004L
DECL|macro|SPMC_WUP2
mdefine_line|#define SPMC_WUP2                               0x00000008L
DECL|macro|SPMC_ASDI2E
mdefine_line|#define SPMC_ASDI2E                             0x00000100L
DECL|macro|SPMC_ESSPD
mdefine_line|#define SPMC_ESSPD                              0x00000200L
DECL|macro|SPMC_GISPEN
mdefine_line|#define SPMC_GISPEN                             0x00004000L
DECL|macro|SPMC_GIPPEN
mdefine_line|#define SPMC_GIPPEN                             0x00008000L
singleline_comment|//****************************************************************************
singleline_comment|//
singleline_comment|// The following defines are for the flags in the Configuration Load register.
singleline_comment|// (CFLR)
singleline_comment|//
singleline_comment|//****************************************************************************
DECL|macro|CFLR_CLOCK_SOURCE_MASK
mdefine_line|#define CFLR_CLOCK_SOURCE_MASK                  0x00000003L
DECL|macro|CFLR_CLOCK_SOURCE_AC97
mdefine_line|#define CFLR_CLOCK_SOURCE_AC97                  0x00000001L
DECL|macro|CFLR_CB0_MASK
mdefine_line|#define CFLR_CB0_MASK                            0x000000FFL
DECL|macro|CFLR_CB1_MASK
mdefine_line|#define CFLR_CB1_MASK                            0x0000FF00L
DECL|macro|CFLR_CB2_MASK
mdefine_line|#define CFLR_CB2_MASK                            0x00FF0000L
DECL|macro|CFLR_CB3_MASK
mdefine_line|#define CFLR_CB3_MASK                            0xFF000000L
DECL|macro|CFLR_CB0_SHIFT
mdefine_line|#define CFLR_CB0_SHIFT                           0L
DECL|macro|CFLR_CB1_SHIFT
mdefine_line|#define CFLR_CB1_SHIFT                           8L
DECL|macro|CFLR_CB2_SHIFT
mdefine_line|#define CFLR_CB2_SHIFT                           16L
DECL|macro|CFLR_CB3_SHIFT
mdefine_line|#define CFLR_CB3_SHIFT                           24L
DECL|macro|IOTCR_DMA0
mdefine_line|#define IOTCR_DMA0                              0x00000000L
DECL|macro|IOTCR_DMA1
mdefine_line|#define IOTCR_DMA1                              0x00000400L
DECL|macro|IOTCR_DMA2
mdefine_line|#define IOTCR_DMA2                              0x00000800L
DECL|macro|IOTCR_DMA3
mdefine_line|#define IOTCR_DMA3                              0x00000C00L
DECL|macro|IOTCR_CCLS
mdefine_line|#define IOTCR_CCLS                              0x00000100L
DECL|macro|IOTCR_PCPCI
mdefine_line|#define IOTCR_PCPCI                             0x00000200L
DECL|macro|IOTCR_DDMA
mdefine_line|#define IOTCR_DDMA                              0x00000300L
DECL|macro|SBWBS_WBB
mdefine_line|#define SBWBS_WBB                               0x00000080L
singleline_comment|//****************************************************************************
singleline_comment|//
singleline_comment|// The following defines are for the flags in the SRC Slot Assignment Register
singleline_comment|// (SRCSA)
singleline_comment|//
singleline_comment|//****************************************************************************
DECL|macro|SRCSA_PLSS_MASK
mdefine_line|#define SRCSA_PLSS_MASK                         0x0000001FL
DECL|macro|SRCSA_PLSS_SHIFT
mdefine_line|#define SRCSA_PLSS_SHIFT                        0L
DECL|macro|SRCSA_PRSS_MASK
mdefine_line|#define SRCSA_PRSS_MASK                         0x00001F00L
DECL|macro|SRCSA_PRSS_SHIFT
mdefine_line|#define SRCSA_PRSS_SHIFT                        8L
DECL|macro|SRCSA_CLSS_MASK
mdefine_line|#define SRCSA_CLSS_MASK                         0x001F0000L
DECL|macro|SRCSA_CLSS_SHIFT
mdefine_line|#define SRCSA_CLSS_SHIFT                        16L
DECL|macro|SRCSA_CRSS_MASK
mdefine_line|#define SRCSA_CRSS_MASK                         0x1F000000L
DECL|macro|SRCSA_CRSS_SHIFT
mdefine_line|#define SRCSA_CRSS_SHIFT                        24L
singleline_comment|//****************************************************************************
singleline_comment|//
singleline_comment|// The following defines are for the flags in the Sound System Power Management
singleline_comment|// register.(SSPM)
singleline_comment|//
singleline_comment|//****************************************************************************
DECL|macro|SSPM_FPDN
mdefine_line|#define SSPM_FPDN                               0x00000080L
DECL|macro|SSPM_MIXEN
mdefine_line|#define SSPM_MIXEN                              0x00000040L
DECL|macro|SSPM_CSRCEN
mdefine_line|#define SSPM_CSRCEN                             0x00000020L
DECL|macro|SSPM_PSRCEN
mdefine_line|#define SSPM_PSRCEN                             0x00000010L
DECL|macro|SSPM_JSEN
mdefine_line|#define SSPM_JSEN                               0x00000008L
DECL|macro|SSPM_ACLEN
mdefine_line|#define SSPM_ACLEN                              0x00000004L
DECL|macro|SSPM_FMEN
mdefine_line|#define SSPM_FMEN                               0x00000002L
singleline_comment|//****************************************************************************
singleline_comment|//
singleline_comment|// The following defines are for the flags in the Sound System Control
singleline_comment|// Register. (SSCR)
singleline_comment|//
singleline_comment|//****************************************************************************
DECL|macro|SSCR_SB
mdefine_line|#define SSCR_SB                                 0x00000004L
DECL|macro|SSCR_HVC
mdefine_line|#define SSCR_HVC                                0x00000008L
DECL|macro|SSCR_LPFIFO
mdefine_line|#define SSCR_LPFIFO                             0x00000040L
DECL|macro|SSCR_LPSRC
mdefine_line|#define SSCR_LPSRC                              0x00000080L
DECL|macro|SSCR_XLPSRC
mdefine_line|#define SSCR_XLPSRC                             0x00000100L
DECL|macro|SSCR_MVMD
mdefine_line|#define SSCR_MVMD                               0x00010000L
DECL|macro|SSCR_MVAD
mdefine_line|#define SSCR_MVAD                               0x00020000L
DECL|macro|SSCR_MVLD
mdefine_line|#define SSCR_MVLD                               0x00040000L
DECL|macro|SSCR_MVCS
mdefine_line|#define SSCR_MVCS                               0x00080000L
singleline_comment|//****************************************************************************
singleline_comment|//
singleline_comment|// The following defines are for the flags in the Clock Control Register 1. 
singleline_comment|// (CLKCR1)
singleline_comment|//
singleline_comment|//****************************************************************************
DECL|macro|CLKCR1_DLLSS_MASK
mdefine_line|#define CLKCR1_DLLSS_MASK                       0x0000000CL
DECL|macro|CLKCR1_DLLSS_SHIFT
mdefine_line|#define CLKCR1_DLLSS_SHIFT                      2L
DECL|macro|CLKCR1_DLLP
mdefine_line|#define CLKCR1_DLLP                             0x00000010L
DECL|macro|CLKCR1_SWCE
mdefine_line|#define CLKCR1_SWCE                             0x00000020L
DECL|macro|CLKCR1_DLLOS
mdefine_line|#define CLKCR1_DLLOS                            0x00000040L
DECL|macro|CLKCR1_CKRA
mdefine_line|#define CLKCR1_CKRA                             0x00010000L
DECL|macro|CLKCR1_CKRN
mdefine_line|#define CLKCR1_CKRN                             0x00020000L
DECL|macro|CLKCR1_DLLRDY
mdefine_line|#define CLKCR1_DLLRDY                           0x01000000L
DECL|macro|CLKCR1_CLKON
mdefine_line|#define CLKCR1_CLKON                            0x02000000L
singleline_comment|//****************************************************************************
singleline_comment|//
singleline_comment|// The following defines are for the flags in the Sound Blaster Read Buffer
singleline_comment|// Status.(SBRBS)
singleline_comment|//
singleline_comment|//****************************************************************************
DECL|macro|SBRBS_RD_MASK
mdefine_line|#define SBRBS_RD_MASK                           0x0000007FL
DECL|macro|SBRBS_RD_SHIFT
mdefine_line|#define SBRBS_RD_SHIFT                          0L
DECL|macro|SBRBS_RBF
mdefine_line|#define SBRBS_RBF                               0x00000080L
singleline_comment|//****************************************************************************
singleline_comment|//
singleline_comment|// The following defines are for the flags in the serial port master control
singleline_comment|// register.(SERMC)
singleline_comment|//
singleline_comment|//****************************************************************************
DECL|macro|SERMC_MSPE
mdefine_line|#define SERMC_MSPE                              0x00000001L
DECL|macro|SERMC_PTC_MASK
mdefine_line|#define SERMC_PTC_MASK                          0x0000000EL
DECL|macro|SERMC_PTC_SHIFT
mdefine_line|#define SERMC_PTC_SHIFT                         1L
DECL|macro|SERMC_PTC_AC97
mdefine_line|#define SERMC_PTC_AC97                          0x00000002L
DECL|macro|SERMC_PLB
mdefine_line|#define SERMC_PLB                               0x00000010L
DECL|macro|SERMC_PXLB
mdefine_line|#define SERMC_PXLB                              0x00000020L
DECL|macro|SERMC_LOFV
mdefine_line|#define SERMC_LOFV                              0x00080000L
DECL|macro|SERMC_SLB
mdefine_line|#define SERMC_SLB                               0x00100000L
DECL|macro|SERMC_SXLB
mdefine_line|#define SERMC_SXLB                              0x00200000L
DECL|macro|SERMC_ODSEN1
mdefine_line|#define SERMC_ODSEN1                            0x01000000L
DECL|macro|SERMC_ODSEN2
mdefine_line|#define SERMC_ODSEN2                            0x02000000L
singleline_comment|//****************************************************************************
singleline_comment|//
singleline_comment|// The following defines are for the flags in the General Purpose I/O Register. 
singleline_comment|// (GPIOR)
singleline_comment|//
singleline_comment|//****************************************************************************
DECL|macro|GPIOR_VDNS
mdefine_line|#define GPIOR_VDNS                              0x00000001L
DECL|macro|GPIOR_VUPS
mdefine_line|#define GPIOR_VUPS                              0x00000002L
DECL|macro|GPIOR_GP1S
mdefine_line|#define GPIOR_GP1S                              0x00000004L
DECL|macro|GPIOR_GP3S
mdefine_line|#define GPIOR_GP3S                              0x00000008L
DECL|macro|GPIOR_GPSS
mdefine_line|#define GPIOR_GPSS                              0x00000010L
DECL|macro|GPIOR_GPPS
mdefine_line|#define GPIOR_GPPS                              0x00000020L
DECL|macro|GPIOR_GP1D
mdefine_line|#define GPIOR_GP1D                              0x00000400L
DECL|macro|GPIOR_GP3D
mdefine_line|#define GPIOR_GP3D                              0x00000800L
DECL|macro|GPIOR_VDNLT
mdefine_line|#define GPIOR_VDNLT                             0x00010000L
DECL|macro|GPIOR_VDNPO
mdefine_line|#define GPIOR_VDNPO                             0x00020000L
DECL|macro|GPIOR_VDNST
mdefine_line|#define GPIOR_VDNST                             0x00040000L
DECL|macro|GPIOR_VDNW
mdefine_line|#define GPIOR_VDNW                              0x00080000L
DECL|macro|GPIOR_VUPLT
mdefine_line|#define GPIOR_VUPLT                             0x00100000L
DECL|macro|GPIOR_VUPPO
mdefine_line|#define GPIOR_VUPPO                             0x00200000L
DECL|macro|GPIOR_VUPST
mdefine_line|#define GPIOR_VUPST                             0x00400000L
DECL|macro|GPIOR_VUPW
mdefine_line|#define GPIOR_VUPW                              0x00800000L
DECL|macro|GPIOR_GP1OE
mdefine_line|#define GPIOR_GP1OE                             0x01000000L
DECL|macro|GPIOR_GP1PT
mdefine_line|#define GPIOR_GP1PT                             0x02000000L
DECL|macro|GPIOR_GP1ST
mdefine_line|#define GPIOR_GP1ST                             0x04000000L
DECL|macro|GPIOR_GP1W
mdefine_line|#define GPIOR_GP1W                              0x08000000L
DECL|macro|GPIOR_GP3OE
mdefine_line|#define GPIOR_GP3OE                             0x10000000L
DECL|macro|GPIOR_GP3PT
mdefine_line|#define GPIOR_GP3PT                             0x20000000L
DECL|macro|GPIOR_GP3ST
mdefine_line|#define GPIOR_GP3ST                             0x40000000L
DECL|macro|GPIOR_GP3W
mdefine_line|#define GPIOR_GP3W                              0x80000000L
singleline_comment|//****************************************************************************
singleline_comment|//
singleline_comment|// The following defines are for the flags in the clock control register 1.
singleline_comment|//
singleline_comment|//****************************************************************************
DECL|macro|CLKCR1_PLLSS_MASK
mdefine_line|#define CLKCR1_PLLSS_MASK                       0x0000000CL
DECL|macro|CLKCR1_PLLSS_SERIAL
mdefine_line|#define CLKCR1_PLLSS_SERIAL                     0x00000000L
DECL|macro|CLKCR1_PLLSS_CRYSTAL
mdefine_line|#define CLKCR1_PLLSS_CRYSTAL                    0x00000004L
DECL|macro|CLKCR1_PLLSS_PCI
mdefine_line|#define CLKCR1_PLLSS_PCI                        0x00000008L
DECL|macro|CLKCR1_PLLSS_RESERVED
mdefine_line|#define CLKCR1_PLLSS_RESERVED                   0x0000000CL
DECL|macro|CLKCR1_PLLP
mdefine_line|#define CLKCR1_PLLP                             0x00000010L
DECL|macro|CLKCR1_SWCE
mdefine_line|#define CLKCR1_SWCE                             0x00000020L
DECL|macro|CLKCR1_PLLOS
mdefine_line|#define CLKCR1_PLLOS                            0x00000040L
singleline_comment|//****************************************************************************
singleline_comment|//
singleline_comment|// The following defines are for the flags in the feature reporting register.
singleline_comment|//
singleline_comment|//****************************************************************************
DECL|macro|FRR_FAB_MASK
mdefine_line|#define FRR_FAB_MASK                            0x00000003L
DECL|macro|FRR_MASK_MASK
mdefine_line|#define FRR_MASK_MASK                           0x0000001CL
DECL|macro|FRR_ID_MASK
mdefine_line|#define FRR_ID_MASK                             0x00003000L
DECL|macro|FRR_FAB_SHIFT
mdefine_line|#define FRR_FAB_SHIFT                           0L
DECL|macro|FRR_MASK_SHIFT
mdefine_line|#define FRR_MASK_SHIFT                          2L
DECL|macro|FRR_ID_SHIFT
mdefine_line|#define FRR_ID_SHIFT                            12L
singleline_comment|//****************************************************************************
singleline_comment|//
singleline_comment|// The following defines are for the flags in the serial port 1 configuration
singleline_comment|// register.
singleline_comment|//
singleline_comment|//****************************************************************************
DECL|macro|SERC1_VALUE
mdefine_line|#define SERC1_VALUE                             0x00000003L
DECL|macro|SERC1_SO1EN
mdefine_line|#define SERC1_SO1EN                             0x00000001L
DECL|macro|SERC1_SO1F_MASK
mdefine_line|#define SERC1_SO1F_MASK                         0x0000000EL
DECL|macro|SERC1_SO1F_CS423X
mdefine_line|#define SERC1_SO1F_CS423X                       0x00000000L
DECL|macro|SERC1_SO1F_AC97
mdefine_line|#define SERC1_SO1F_AC97                         0x00000002L
DECL|macro|SERC1_SO1F_DAC
mdefine_line|#define SERC1_SO1F_DAC                          0x00000004L
DECL|macro|SERC1_SO1F_SPDIF
mdefine_line|#define SERC1_SO1F_SPDIF                        0x00000006L
singleline_comment|//****************************************************************************
singleline_comment|//
singleline_comment|// The following defines are for the flags in the serial port 2 configuration
singleline_comment|// register.
singleline_comment|//
singleline_comment|//****************************************************************************
DECL|macro|SERC2_VALUE
mdefine_line|#define SERC2_VALUE                             0x00000003L
DECL|macro|SERC2_SI1EN
mdefine_line|#define SERC2_SI1EN                             0x00000001L
DECL|macro|SERC2_SI1F_MASK
mdefine_line|#define SERC2_SI1F_MASK                         0x0000000EL
DECL|macro|SERC2_SI1F_CS423X
mdefine_line|#define SERC2_SI1F_CS423X                       0x00000000L
DECL|macro|SERC2_SI1F_AC97
mdefine_line|#define SERC2_SI1F_AC97                         0x00000002L
DECL|macro|SERC2_SI1F_ADC
mdefine_line|#define SERC2_SI1F_ADC                          0x00000004L
DECL|macro|SERC2_SI1F_SPDIF
mdefine_line|#define SERC2_SI1F_SPDIF                        0x00000006L
singleline_comment|//****************************************************************************
singleline_comment|//
singleline_comment|// The following defines are for the flags in the AC97 control register.
singleline_comment|//
singleline_comment|//****************************************************************************
DECL|macro|ACCTL_ESYN
mdefine_line|#define ACCTL_ESYN                              0x00000002L
DECL|macro|ACCTL_VFRM
mdefine_line|#define ACCTL_VFRM                              0x00000004L
DECL|macro|ACCTL_DCV
mdefine_line|#define ACCTL_DCV                               0x00000008L
DECL|macro|ACCTL_CRW
mdefine_line|#define ACCTL_CRW                               0x00000010L
DECL|macro|ACCTL_TC
mdefine_line|#define ACCTL_TC                                0x00000040L
singleline_comment|//****************************************************************************
singleline_comment|//
singleline_comment|// The following defines are for the flags in the AC97 status register.
singleline_comment|//
singleline_comment|//****************************************************************************
DECL|macro|ACSTS_CRDY
mdefine_line|#define ACSTS_CRDY                              0x00000001L
DECL|macro|ACSTS_VSTS
mdefine_line|#define ACSTS_VSTS                              0x00000002L
singleline_comment|//****************************************************************************
singleline_comment|//
singleline_comment|// The following defines are for the flags in the AC97 output slot valid
singleline_comment|// register.
singleline_comment|//
singleline_comment|//****************************************************************************
DECL|macro|ACOSV_SLV3
mdefine_line|#define ACOSV_SLV3                              0x00000001L
DECL|macro|ACOSV_SLV4
mdefine_line|#define ACOSV_SLV4                              0x00000002L
DECL|macro|ACOSV_SLV5
mdefine_line|#define ACOSV_SLV5                              0x00000004L
DECL|macro|ACOSV_SLV6
mdefine_line|#define ACOSV_SLV6                              0x00000008L
DECL|macro|ACOSV_SLV7
mdefine_line|#define ACOSV_SLV7                              0x00000010L
DECL|macro|ACOSV_SLV8
mdefine_line|#define ACOSV_SLV8                              0x00000020L
DECL|macro|ACOSV_SLV9
mdefine_line|#define ACOSV_SLV9                              0x00000040L
DECL|macro|ACOSV_SLV10
mdefine_line|#define ACOSV_SLV10                             0x00000080L
DECL|macro|ACOSV_SLV11
mdefine_line|#define ACOSV_SLV11                             0x00000100L
DECL|macro|ACOSV_SLV12
mdefine_line|#define ACOSV_SLV12                             0x00000200L
singleline_comment|//****************************************************************************
singleline_comment|//
singleline_comment|// The following defines are for the flags in the AC97 command address
singleline_comment|// register.
singleline_comment|//
singleline_comment|//****************************************************************************
DECL|macro|ACCAD_CI_MASK
mdefine_line|#define ACCAD_CI_MASK                           0x0000007FL
DECL|macro|ACCAD_CI_SHIFT
mdefine_line|#define ACCAD_CI_SHIFT                          0L
singleline_comment|//****************************************************************************
singleline_comment|//
singleline_comment|// The following defines are for the flags in the AC97 command data register.
singleline_comment|//
singleline_comment|//****************************************************************************
DECL|macro|ACCDA_CD_MASK
mdefine_line|#define ACCDA_CD_MASK                           0x0000FFFFL
DECL|macro|ACCDA_CD_SHIFT
mdefine_line|#define ACCDA_CD_SHIFT                          0L
singleline_comment|//****************************************************************************
singleline_comment|//
singleline_comment|// The following defines are for the flags in the AC97 input slot valid
singleline_comment|// register.
singleline_comment|//
singleline_comment|//****************************************************************************
DECL|macro|ACISV_ISV3
mdefine_line|#define ACISV_ISV3                              0x00000001L
DECL|macro|ACISV_ISV4
mdefine_line|#define ACISV_ISV4                              0x00000002L
DECL|macro|ACISV_ISV5
mdefine_line|#define ACISV_ISV5                              0x00000004L
DECL|macro|ACISV_ISV6
mdefine_line|#define ACISV_ISV6                              0x00000008L
DECL|macro|ACISV_ISV7
mdefine_line|#define ACISV_ISV7                              0x00000010L
DECL|macro|ACISV_ISV8
mdefine_line|#define ACISV_ISV8                              0x00000020L
DECL|macro|ACISV_ISV9
mdefine_line|#define ACISV_ISV9                              0x00000040L
DECL|macro|ACISV_ISV10
mdefine_line|#define ACISV_ISV10                             0x00000080L
DECL|macro|ACISV_ISV11
mdefine_line|#define ACISV_ISV11                             0x00000100L
DECL|macro|ACISV_ISV12
mdefine_line|#define ACISV_ISV12                             0x00000200L
singleline_comment|//****************************************************************************
singleline_comment|//
singleline_comment|// The following defines are for the flags in the AC97 status address
singleline_comment|// register.
singleline_comment|//
singleline_comment|//****************************************************************************
DECL|macro|ACSAD_SI_MASK
mdefine_line|#define ACSAD_SI_MASK                           0x0000007FL
DECL|macro|ACSAD_SI_SHIFT
mdefine_line|#define ACSAD_SI_SHIFT                          0L
singleline_comment|//****************************************************************************
singleline_comment|//
singleline_comment|// The following defines are for the flags in the AC97 status data register.
singleline_comment|//
singleline_comment|//****************************************************************************
DECL|macro|ACSDA_SD_MASK
mdefine_line|#define ACSDA_SD_MASK                           0x0000FFFFL
DECL|macro|ACSDA_SD_SHIFT
mdefine_line|#define ACSDA_SD_SHIFT                          0L
singleline_comment|//****************************************************************************
singleline_comment|//
singleline_comment|// The following defines are for the flags in the I/O trap address and control
singleline_comment|// registers (all 12).
singleline_comment|//
singleline_comment|//****************************************************************************
DECL|macro|IOTAC_SA_MASK
mdefine_line|#define IOTAC_SA_MASK                           0x0000FFFFL
DECL|macro|IOTAC_MSK_MASK
mdefine_line|#define IOTAC_MSK_MASK                          0x000F0000L
DECL|macro|IOTAC_IODC_MASK
mdefine_line|#define IOTAC_IODC_MASK                         0x06000000L
DECL|macro|IOTAC_IODC_16_BIT
mdefine_line|#define IOTAC_IODC_16_BIT                       0x00000000L
DECL|macro|IOTAC_IODC_10_BIT
mdefine_line|#define IOTAC_IODC_10_BIT                       0x02000000L
DECL|macro|IOTAC_IODC_12_BIT
mdefine_line|#define IOTAC_IODC_12_BIT                       0x04000000L
DECL|macro|IOTAC_WSPI
mdefine_line|#define IOTAC_WSPI                              0x08000000L
DECL|macro|IOTAC_RSPI
mdefine_line|#define IOTAC_RSPI                              0x10000000L
DECL|macro|IOTAC_WSE
mdefine_line|#define IOTAC_WSE                               0x20000000L
DECL|macro|IOTAC_WE
mdefine_line|#define IOTAC_WE                                0x40000000L
DECL|macro|IOTAC_RE
mdefine_line|#define IOTAC_RE                                0x80000000L
DECL|macro|IOTAC_SA_SHIFT
mdefine_line|#define IOTAC_SA_SHIFT                          0L
DECL|macro|IOTAC_MSK_SHIFT
mdefine_line|#define IOTAC_MSK_SHIFT                         16L
singleline_comment|//****************************************************************************
singleline_comment|//
singleline_comment|// The following defines are for the flags in the PC/PCI master enable
singleline_comment|// register.
singleline_comment|//
singleline_comment|//****************************************************************************
DECL|macro|PCPCIEN_EN
mdefine_line|#define PCPCIEN_EN                              0x00000001L
singleline_comment|//****************************************************************************
singleline_comment|//
singleline_comment|// The following defines are for the flags in the joystick poll/trigger
singleline_comment|// register.
singleline_comment|//
singleline_comment|//****************************************************************************
DECL|macro|JSPT_CAX
mdefine_line|#define JSPT_CAX                                0x00000001L
DECL|macro|JSPT_CAY
mdefine_line|#define JSPT_CAY                                0x00000002L
DECL|macro|JSPT_CBX
mdefine_line|#define JSPT_CBX                                0x00000004L
DECL|macro|JSPT_CBY
mdefine_line|#define JSPT_CBY                                0x00000008L
DECL|macro|JSPT_BA1
mdefine_line|#define JSPT_BA1                                0x00000010L
DECL|macro|JSPT_BA2
mdefine_line|#define JSPT_BA2                                0x00000020L
DECL|macro|JSPT_BB1
mdefine_line|#define JSPT_BB1                                0x00000040L
DECL|macro|JSPT_BB2
mdefine_line|#define JSPT_BB2                                0x00000080L
singleline_comment|//****************************************************************************
singleline_comment|//
singleline_comment|// The following defines are for the flags in the joystick control register.
singleline_comment|// The TBF bit has been moved from MIDSR register to JSCTL register bit 8.
singleline_comment|//
singleline_comment|//****************************************************************************
DECL|macro|JSCTL_SP_MASK
mdefine_line|#define JSCTL_SP_MASK                           0x00000003L
DECL|macro|JSCTL_SP_SLOW
mdefine_line|#define JSCTL_SP_SLOW                           0x00000000L
DECL|macro|JSCTL_SP_MEDIUM_SLOW
mdefine_line|#define JSCTL_SP_MEDIUM_SLOW                    0x00000001L
DECL|macro|JSCTL_SP_MEDIUM_FAST
mdefine_line|#define JSCTL_SP_MEDIUM_FAST                    0x00000002L
DECL|macro|JSCTL_SP_FAST
mdefine_line|#define JSCTL_SP_FAST                           0x00000003L
DECL|macro|JSCTL_ARE
mdefine_line|#define JSCTL_ARE                               0x00000004L
DECL|macro|JSCTL_TBF
mdefine_line|#define JSCTL_TBF                               0x00000100L
singleline_comment|//****************************************************************************
singleline_comment|//
singleline_comment|// The following defines are for the flags in the MIDI control register.
singleline_comment|//
singleline_comment|//****************************************************************************
DECL|macro|MIDCR_TXE
mdefine_line|#define MIDCR_TXE                               0x00000001L
DECL|macro|MIDCR_RXE
mdefine_line|#define MIDCR_RXE                               0x00000002L
DECL|macro|MIDCR_RIE
mdefine_line|#define MIDCR_RIE                               0x00000004L
DECL|macro|MIDCR_TIE
mdefine_line|#define MIDCR_TIE                               0x00000008L
DECL|macro|MIDCR_MLB
mdefine_line|#define MIDCR_MLB                               0x00000010L
DECL|macro|MIDCR_MRST
mdefine_line|#define MIDCR_MRST                              0x00000020L
singleline_comment|//****************************************************************************
singleline_comment|//
singleline_comment|// The following defines are for the flags in the MIDI status register.
singleline_comment|//
singleline_comment|//****************************************************************************
DECL|macro|MIDSR_RBE
mdefine_line|#define MIDSR_RBE                               0x00000080L
DECL|macro|MIDSR_RDA
mdefine_line|#define MIDSR_RDA                               0x00008000L
singleline_comment|//****************************************************************************
singleline_comment|//
singleline_comment|// The following defines are for the flags in the MIDI write port register.
singleline_comment|//
singleline_comment|//****************************************************************************
DECL|macro|MIDWP_MWD_MASK
mdefine_line|#define MIDWP_MWD_MASK                          0x000000FFL
DECL|macro|MIDWP_MWD_SHIFT
mdefine_line|#define MIDWP_MWD_SHIFT                         0L
singleline_comment|//****************************************************************************
singleline_comment|//
singleline_comment|// The following defines are for the flags in the MIDI read port register.
singleline_comment|//
singleline_comment|//****************************************************************************
DECL|macro|MIDRP_MRD_MASK
mdefine_line|#define MIDRP_MRD_MASK                          0x000000FFL
DECL|macro|MIDRP_MRD_SHIFT
mdefine_line|#define MIDRP_MRD_SHIFT                         0L
singleline_comment|//****************************************************************************
singleline_comment|//
singleline_comment|// The following defines are for the flags in the configuration interface
singleline_comment|// register.
singleline_comment|//
singleline_comment|//****************************************************************************
DECL|macro|CFGI_CLK
mdefine_line|#define CFGI_CLK                                0x00000001L
DECL|macro|CFGI_DOUT
mdefine_line|#define CFGI_DOUT                               0x00000002L
DECL|macro|CFGI_DIN_EEN
mdefine_line|#define CFGI_DIN_EEN                            0x00000004L
DECL|macro|CFGI_EELD
mdefine_line|#define CFGI_EELD                               0x00000008L
singleline_comment|//****************************************************************************
singleline_comment|//
singleline_comment|// The following defines are for the flags in the subsystem ID and vendor ID
singleline_comment|// register.
singleline_comment|//
singleline_comment|//****************************************************************************
DECL|macro|SSVID_VID_MASK
mdefine_line|#define SSVID_VID_MASK                          0x0000FFFFL
DECL|macro|SSVID_SID_MASK
mdefine_line|#define SSVID_SID_MASK                          0xFFFF0000L
DECL|macro|SSVID_VID_SHIFT
mdefine_line|#define SSVID_VID_SHIFT                         0L
DECL|macro|SSVID_SID_SHIFT
mdefine_line|#define SSVID_SID_SHIFT                         16L
singleline_comment|//****************************************************************************
singleline_comment|//
singleline_comment|// The following defines are for the flags in the GPIO pin interface register.
singleline_comment|//
singleline_comment|//****************************************************************************
DECL|macro|GPIOR_VOLDN
mdefine_line|#define GPIOR_VOLDN                             0x00000001L
DECL|macro|GPIOR_VOLUP
mdefine_line|#define GPIOR_VOLUP                             0x00000002L
DECL|macro|GPIOR_SI2D
mdefine_line|#define GPIOR_SI2D                              0x00000004L
DECL|macro|GPIOR_SI2OE
mdefine_line|#define GPIOR_SI2OE                             0x00000008L
singleline_comment|//****************************************************************************
singleline_comment|//
singleline_comment|// The following defines are for the flags in the AC97 status register 2.
singleline_comment|//
singleline_comment|//****************************************************************************
DECL|macro|ACSTS2_CRDY
mdefine_line|#define ACSTS2_CRDY                             0x00000001L
DECL|macro|ACSTS2_VSTS
mdefine_line|#define ACSTS2_VSTS                             0x00000002L
singleline_comment|//****************************************************************************
singleline_comment|//
singleline_comment|// The following defines are for the flags in the AC97 input slot valid
singleline_comment|// register 2.
singleline_comment|//
singleline_comment|//****************************************************************************
DECL|macro|ACISV2_ISV3
mdefine_line|#define ACISV2_ISV3                             0x00000001L
DECL|macro|ACISV2_ISV4
mdefine_line|#define ACISV2_ISV4                             0x00000002L
DECL|macro|ACISV2_ISV5
mdefine_line|#define ACISV2_ISV5                             0x00000004L
DECL|macro|ACISV2_ISV6
mdefine_line|#define ACISV2_ISV6                             0x00000008L
DECL|macro|ACISV2_ISV7
mdefine_line|#define ACISV2_ISV7                             0x00000010L
DECL|macro|ACISV2_ISV8
mdefine_line|#define ACISV2_ISV8                             0x00000020L
DECL|macro|ACISV2_ISV9
mdefine_line|#define ACISV2_ISV9                             0x00000040L
DECL|macro|ACISV2_ISV10
mdefine_line|#define ACISV2_ISV10                            0x00000080L
DECL|macro|ACISV2_ISV11
mdefine_line|#define ACISV2_ISV11                            0x00000100L
DECL|macro|ACISV2_ISV12
mdefine_line|#define ACISV2_ISV12                            0x00000200L
singleline_comment|//****************************************************************************
singleline_comment|//
singleline_comment|// The following defines are for the flags in the AC97 status address
singleline_comment|// register 2.
singleline_comment|//
singleline_comment|//****************************************************************************
DECL|macro|ACSAD2_SI_MASK
mdefine_line|#define ACSAD2_SI_MASK                          0x0000007FL
DECL|macro|ACSAD2_SI_SHIFT
mdefine_line|#define ACSAD2_SI_SHIFT                         0L
singleline_comment|//****************************************************************************
singleline_comment|//
singleline_comment|// The following defines are for the flags in the AC97 status data register 2.
singleline_comment|//
singleline_comment|//****************************************************************************
DECL|macro|ACSDA2_SD_MASK
mdefine_line|#define ACSDA2_SD_MASK                          0x0000FFFFL
DECL|macro|ACSDA2_SD_SHIFT
mdefine_line|#define ACSDA2_SD_SHIFT                         0L
singleline_comment|//****************************************************************************
singleline_comment|//
singleline_comment|// The following defines are for the flags in the I/O trap control register.
singleline_comment|//
singleline_comment|//****************************************************************************
DECL|macro|IOTCR_ITD
mdefine_line|#define IOTCR_ITD                               0x00000001L
DECL|macro|IOTCR_HRV
mdefine_line|#define IOTCR_HRV                               0x00000002L
DECL|macro|IOTCR_SRV
mdefine_line|#define IOTCR_SRV                               0x00000004L
DECL|macro|IOTCR_DTI
mdefine_line|#define IOTCR_DTI                               0x00000008L
DECL|macro|IOTCR_DFI
mdefine_line|#define IOTCR_DFI                               0x00000010L
DECL|macro|IOTCR_DDP
mdefine_line|#define IOTCR_DDP                               0x00000020L
DECL|macro|IOTCR_JTE
mdefine_line|#define IOTCR_JTE                               0x00000040L
DECL|macro|IOTCR_PPE
mdefine_line|#define IOTCR_PPE                               0x00000080L
singleline_comment|//****************************************************************************
singleline_comment|//
singleline_comment|// The following defines are for the flags in the I/O trap address and control
singleline_comment|// registers for Hardware Master Volume.  
singleline_comment|//
singleline_comment|//****************************************************************************
DECL|macro|IOTGP_SA_MASK
mdefine_line|#define IOTGP_SA_MASK                           0x0000FFFFL
DECL|macro|IOTGP_MSK_MASK
mdefine_line|#define IOTGP_MSK_MASK                          0x000F0000L
DECL|macro|IOTGP_IODC_MASK
mdefine_line|#define IOTGP_IODC_MASK                         0x06000000L
DECL|macro|IOTGP_IODC_16_BIT
mdefine_line|#define IOTGP_IODC_16_BIT                       0x00000000L
DECL|macro|IOTGP_IODC_10_BIT
mdefine_line|#define IOTGP_IODC_10_BIT                       0x02000000L
DECL|macro|IOTGP_IODC_12_BIT
mdefine_line|#define IOTGP_IODC_12_BIT                       0x04000000L
DECL|macro|IOTGP_WSPI
mdefine_line|#define IOTGP_WSPI                              0x08000000L
DECL|macro|IOTGP_RSPI
mdefine_line|#define IOTGP_RSPI                              0x10000000L
DECL|macro|IOTGP_WSE
mdefine_line|#define IOTGP_WSE                               0x20000000L
DECL|macro|IOTGP_WE
mdefine_line|#define IOTGP_WE                                0x40000000L
DECL|macro|IOTGP_RE
mdefine_line|#define IOTGP_RE                                0x80000000L
DECL|macro|IOTGP_SA_SHIFT
mdefine_line|#define IOTGP_SA_SHIFT                          0L
DECL|macro|IOTGP_MSK_SHIFT
mdefine_line|#define IOTGP_MSK_SHIFT                         16L
singleline_comment|//****************************************************************************
singleline_comment|//
singleline_comment|// The following defines are for the flags in the I/O trap address and control
singleline_comment|// registers for Sound Blaster
singleline_comment|//
singleline_comment|//****************************************************************************
DECL|macro|IOTSB_SA_MASK
mdefine_line|#define IOTSB_SA_MASK                           0x0000FFFFL
DECL|macro|IOTSB_MSK_MASK
mdefine_line|#define IOTSB_MSK_MASK                          0x000F0000L
DECL|macro|IOTSB_IODC_MASK
mdefine_line|#define IOTSB_IODC_MASK                         0x06000000L
DECL|macro|IOTSB_IODC_16_BIT
mdefine_line|#define IOTSB_IODC_16_BIT                       0x00000000L
DECL|macro|IOTSB_IODC_10_BIT
mdefine_line|#define IOTSB_IODC_10_BIT                       0x02000000L
DECL|macro|IOTSB_IODC_12_BIT
mdefine_line|#define IOTSB_IODC_12_BIT                       0x04000000L
DECL|macro|IOTSB_WSPI
mdefine_line|#define IOTSB_WSPI                              0x08000000L
DECL|macro|IOTSB_RSPI
mdefine_line|#define IOTSB_RSPI                              0x10000000L
DECL|macro|IOTSB_WSE
mdefine_line|#define IOTSB_WSE                               0x20000000L
DECL|macro|IOTSB_WE
mdefine_line|#define IOTSB_WE                                0x40000000L
DECL|macro|IOTSB_RE
mdefine_line|#define IOTSB_RE                                0x80000000L
DECL|macro|IOTSB_SA_SHIFT
mdefine_line|#define IOTSB_SA_SHIFT                          0L
DECL|macro|IOTSB_MSK_SHIFT
mdefine_line|#define IOTSB_MSK_SHIFT                         16L
singleline_comment|//****************************************************************************
singleline_comment|//
singleline_comment|// The following defines are for the flags in the I/O trap address and control
singleline_comment|// registers for FM.
singleline_comment|//
singleline_comment|//****************************************************************************
DECL|macro|IOTFM_SA_MASK
mdefine_line|#define IOTFM_SA_MASK                           0x0000FFFFL
DECL|macro|IOTFM_MSK_MASK
mdefine_line|#define IOTFM_MSK_MASK                          0x000F0000L
DECL|macro|IOTFM_IODC_MASK
mdefine_line|#define IOTFM_IODC_MASK                         0x06000000L
DECL|macro|IOTFM_IODC_16_BIT
mdefine_line|#define IOTFM_IODC_16_BIT                       0x00000000L
DECL|macro|IOTFM_IODC_10_BIT
mdefine_line|#define IOTFM_IODC_10_BIT                       0x02000000L
DECL|macro|IOTFM_IODC_12_BIT
mdefine_line|#define IOTFM_IODC_12_BIT                       0x04000000L
DECL|macro|IOTFM_WSPI
mdefine_line|#define IOTFM_WSPI                              0x08000000L
DECL|macro|IOTFM_RSPI
mdefine_line|#define IOTFM_RSPI                              0x10000000L
DECL|macro|IOTFM_WSE
mdefine_line|#define IOTFM_WSE                               0x20000000L
DECL|macro|IOTFM_WE
mdefine_line|#define IOTFM_WE                                0x40000000L
DECL|macro|IOTFM_RE
mdefine_line|#define IOTFM_RE                                0x80000000L
DECL|macro|IOTFM_SA_SHIFT
mdefine_line|#define IOTFM_SA_SHIFT                          0L
DECL|macro|IOTFM_MSK_SHIFT
mdefine_line|#define IOTFM_MSK_SHIFT                         16L
singleline_comment|//****************************************************************************
singleline_comment|//
singleline_comment|// The following defines are for the flags in the PC/PCI request register.
singleline_comment|//
singleline_comment|//****************************************************************************
DECL|macro|PCPRR_RDC_MASK
mdefine_line|#define PCPRR_RDC_MASK                         0x00000007L
DECL|macro|PCPRR_REQ
mdefine_line|#define PCPRR_REQ                              0x00008000L
DECL|macro|PCPRR_RDC_SHIFT
mdefine_line|#define PCPRR_RDC_SHIFT                        0L
singleline_comment|//****************************************************************************
singleline_comment|//
singleline_comment|// The following defines are for the flags in the PC/PCI grant register.
singleline_comment|//
singleline_comment|//****************************************************************************
DECL|macro|PCPGR_GDC_MASK
mdefine_line|#define PCPGR_GDC_MASK                         0x00000007L
DECL|macro|PCPGR_VL
mdefine_line|#define PCPGR_VL                               0x00008000L
DECL|macro|PCPGR_GDC_SHIFT
mdefine_line|#define PCPGR_GDC_SHIFT                        0L
singleline_comment|//****************************************************************************
singleline_comment|//
singleline_comment|// The following defines are for the flags in the PC/PCI Control Register.
singleline_comment|//
singleline_comment|//****************************************************************************
DECL|macro|PCPCR_EN
mdefine_line|#define PCPCR_EN                               0x00000001L
singleline_comment|//****************************************************************************
singleline_comment|//
singleline_comment|// The following defines are for the flags in the debug index register.
singleline_comment|//
singleline_comment|//****************************************************************************
DECL|macro|DREG_REGID_MASK
mdefine_line|#define DREG_REGID_MASK                         0x0000007FL
DECL|macro|DREG_DEBUG
mdefine_line|#define DREG_DEBUG                              0x00000080L
DECL|macro|DREG_RGBK_MASK
mdefine_line|#define DREG_RGBK_MASK                          0x00000700L
DECL|macro|DREG_TRAP
mdefine_line|#define DREG_TRAP                               0x00000800L
macro_line|#if !defined(NO_CS4612)
macro_line|#if !defined(NO_CS4615)
DECL|macro|DREG_TRAPX
mdefine_line|#define DREG_TRAPX                              0x00001000L
macro_line|#endif
macro_line|#endif
DECL|macro|DREG_REGID_SHIFT
mdefine_line|#define DREG_REGID_SHIFT                        0L
DECL|macro|DREG_RGBK_SHIFT
mdefine_line|#define DREG_RGBK_SHIFT                         8L
DECL|macro|DREG_RGBK_REGID_MASK
mdefine_line|#define DREG_RGBK_REGID_MASK                    0x0000077FL
DECL|macro|DREG_REGID_R0
mdefine_line|#define DREG_REGID_R0                           0x00000010L
DECL|macro|DREG_REGID_R1
mdefine_line|#define DREG_REGID_R1                           0x00000011L
DECL|macro|DREG_REGID_R2
mdefine_line|#define DREG_REGID_R2                           0x00000012L
DECL|macro|DREG_REGID_R3
mdefine_line|#define DREG_REGID_R3                           0x00000013L
DECL|macro|DREG_REGID_R4
mdefine_line|#define DREG_REGID_R4                           0x00000014L
DECL|macro|DREG_REGID_R5
mdefine_line|#define DREG_REGID_R5                           0x00000015L
DECL|macro|DREG_REGID_R6
mdefine_line|#define DREG_REGID_R6                           0x00000016L
DECL|macro|DREG_REGID_R7
mdefine_line|#define DREG_REGID_R7                           0x00000017L
DECL|macro|DREG_REGID_R8
mdefine_line|#define DREG_REGID_R8                           0x00000018L
DECL|macro|DREG_REGID_R9
mdefine_line|#define DREG_REGID_R9                           0x00000019L
DECL|macro|DREG_REGID_RA
mdefine_line|#define DREG_REGID_RA                           0x0000001AL
DECL|macro|DREG_REGID_RB
mdefine_line|#define DREG_REGID_RB                           0x0000001BL
DECL|macro|DREG_REGID_RC
mdefine_line|#define DREG_REGID_RC                           0x0000001CL
DECL|macro|DREG_REGID_RD
mdefine_line|#define DREG_REGID_RD                           0x0000001DL
DECL|macro|DREG_REGID_RE
mdefine_line|#define DREG_REGID_RE                           0x0000001EL
DECL|macro|DREG_REGID_RF
mdefine_line|#define DREG_REGID_RF                           0x0000001FL
DECL|macro|DREG_REGID_RA_BUS_LOW
mdefine_line|#define DREG_REGID_RA_BUS_LOW                   0x00000020L
DECL|macro|DREG_REGID_RA_BUS_HIGH
mdefine_line|#define DREG_REGID_RA_BUS_HIGH                  0x00000038L
DECL|macro|DREG_REGID_YBUS_LOW
mdefine_line|#define DREG_REGID_YBUS_LOW                     0x00000050L
DECL|macro|DREG_REGID_YBUS_HIGH
mdefine_line|#define DREG_REGID_YBUS_HIGH                    0x00000058L
DECL|macro|DREG_REGID_TRAP_0
mdefine_line|#define DREG_REGID_TRAP_0                       0x00000100L
DECL|macro|DREG_REGID_TRAP_1
mdefine_line|#define DREG_REGID_TRAP_1                       0x00000101L
DECL|macro|DREG_REGID_TRAP_2
mdefine_line|#define DREG_REGID_TRAP_2                       0x00000102L
DECL|macro|DREG_REGID_TRAP_3
mdefine_line|#define DREG_REGID_TRAP_3                       0x00000103L
DECL|macro|DREG_REGID_TRAP_4
mdefine_line|#define DREG_REGID_TRAP_4                       0x00000104L
DECL|macro|DREG_REGID_TRAP_5
mdefine_line|#define DREG_REGID_TRAP_5                       0x00000105L
DECL|macro|DREG_REGID_TRAP_6
mdefine_line|#define DREG_REGID_TRAP_6                       0x00000106L
DECL|macro|DREG_REGID_TRAP_7
mdefine_line|#define DREG_REGID_TRAP_7                       0x00000107L
DECL|macro|DREG_REGID_INDIRECT_ADDRESS
mdefine_line|#define DREG_REGID_INDIRECT_ADDRESS             0x0000010EL
DECL|macro|DREG_REGID_TOP_OF_STACK
mdefine_line|#define DREG_REGID_TOP_OF_STACK                 0x0000010FL
macro_line|#if !defined(NO_CS4612)
macro_line|#if !defined(NO_CS4615)
DECL|macro|DREG_REGID_TRAP_8
mdefine_line|#define DREG_REGID_TRAP_8                       0x00000110L
DECL|macro|DREG_REGID_TRAP_9
mdefine_line|#define DREG_REGID_TRAP_9                       0x00000111L
DECL|macro|DREG_REGID_TRAP_10
mdefine_line|#define DREG_REGID_TRAP_10                      0x00000112L
DECL|macro|DREG_REGID_TRAP_11
mdefine_line|#define DREG_REGID_TRAP_11                      0x00000113L
DECL|macro|DREG_REGID_TRAP_12
mdefine_line|#define DREG_REGID_TRAP_12                      0x00000114L
DECL|macro|DREG_REGID_TRAP_13
mdefine_line|#define DREG_REGID_TRAP_13                      0x00000115L
DECL|macro|DREG_REGID_TRAP_14
mdefine_line|#define DREG_REGID_TRAP_14                      0x00000116L
DECL|macro|DREG_REGID_TRAP_15
mdefine_line|#define DREG_REGID_TRAP_15                      0x00000117L
DECL|macro|DREG_REGID_TRAP_16
mdefine_line|#define DREG_REGID_TRAP_16                      0x00000118L
DECL|macro|DREG_REGID_TRAP_17
mdefine_line|#define DREG_REGID_TRAP_17                      0x00000119L
DECL|macro|DREG_REGID_TRAP_18
mdefine_line|#define DREG_REGID_TRAP_18                      0x0000011AL
DECL|macro|DREG_REGID_TRAP_19
mdefine_line|#define DREG_REGID_TRAP_19                      0x0000011BL
DECL|macro|DREG_REGID_TRAP_20
mdefine_line|#define DREG_REGID_TRAP_20                      0x0000011CL
DECL|macro|DREG_REGID_TRAP_21
mdefine_line|#define DREG_REGID_TRAP_21                      0x0000011DL
DECL|macro|DREG_REGID_TRAP_22
mdefine_line|#define DREG_REGID_TRAP_22                      0x0000011EL
DECL|macro|DREG_REGID_TRAP_23
mdefine_line|#define DREG_REGID_TRAP_23                      0x0000011FL
macro_line|#endif
macro_line|#endif
DECL|macro|DREG_REGID_RSA0_LOW
mdefine_line|#define DREG_REGID_RSA0_LOW                     0x00000200L
DECL|macro|DREG_REGID_RSA0_HIGH
mdefine_line|#define DREG_REGID_RSA0_HIGH                    0x00000201L
DECL|macro|DREG_REGID_RSA1_LOW
mdefine_line|#define DREG_REGID_RSA1_LOW                     0x00000202L
DECL|macro|DREG_REGID_RSA1_HIGH
mdefine_line|#define DREG_REGID_RSA1_HIGH                    0x00000203L
DECL|macro|DREG_REGID_RSA2
mdefine_line|#define DREG_REGID_RSA2                         0x00000204L
DECL|macro|DREG_REGID_RSA3
mdefine_line|#define DREG_REGID_RSA3                         0x00000205L
DECL|macro|DREG_REGID_RSI0_LOW
mdefine_line|#define DREG_REGID_RSI0_LOW                     0x00000206L
DECL|macro|DREG_REGID_RSI0_HIGH
mdefine_line|#define DREG_REGID_RSI0_HIGH                    0x00000207L
DECL|macro|DREG_REGID_RSI1
mdefine_line|#define DREG_REGID_RSI1                         0x00000208L
DECL|macro|DREG_REGID_RSI2
mdefine_line|#define DREG_REGID_RSI2                         0x00000209L
DECL|macro|DREG_REGID_SAGUSTATUS
mdefine_line|#define DREG_REGID_SAGUSTATUS                   0x0000020AL
DECL|macro|DREG_REGID_RSCONFIG01_LOW
mdefine_line|#define DREG_REGID_RSCONFIG01_LOW               0x0000020BL
DECL|macro|DREG_REGID_RSCONFIG01_HIGH
mdefine_line|#define DREG_REGID_RSCONFIG01_HIGH              0x0000020CL
DECL|macro|DREG_REGID_RSCONFIG23_LOW
mdefine_line|#define DREG_REGID_RSCONFIG23_LOW               0x0000020DL
DECL|macro|DREG_REGID_RSCONFIG23_HIGH
mdefine_line|#define DREG_REGID_RSCONFIG23_HIGH              0x0000020EL
DECL|macro|DREG_REGID_RSDMA01E
mdefine_line|#define DREG_REGID_RSDMA01E                     0x0000020FL
DECL|macro|DREG_REGID_RSDMA23E
mdefine_line|#define DREG_REGID_RSDMA23E                     0x00000210L
DECL|macro|DREG_REGID_RSD0_LOW
mdefine_line|#define DREG_REGID_RSD0_LOW                     0x00000211L
DECL|macro|DREG_REGID_RSD0_HIGH
mdefine_line|#define DREG_REGID_RSD0_HIGH                    0x00000212L
DECL|macro|DREG_REGID_RSD1_LOW
mdefine_line|#define DREG_REGID_RSD1_LOW                     0x00000213L
DECL|macro|DREG_REGID_RSD1_HIGH
mdefine_line|#define DREG_REGID_RSD1_HIGH                    0x00000214L
DECL|macro|DREG_REGID_RSD2_LOW
mdefine_line|#define DREG_REGID_RSD2_LOW                     0x00000215L
DECL|macro|DREG_REGID_RSD2_HIGH
mdefine_line|#define DREG_REGID_RSD2_HIGH                    0x00000216L
DECL|macro|DREG_REGID_RSD3_LOW
mdefine_line|#define DREG_REGID_RSD3_LOW                     0x00000217L
DECL|macro|DREG_REGID_RSD3_HIGH
mdefine_line|#define DREG_REGID_RSD3_HIGH                    0x00000218L
DECL|macro|DREG_REGID_SRAR_HIGH
mdefine_line|#define DREG_REGID_SRAR_HIGH                    0x0000021AL
DECL|macro|DREG_REGID_SRAR_LOW
mdefine_line|#define DREG_REGID_SRAR_LOW                     0x0000021BL
DECL|macro|DREG_REGID_DMA_STATE
mdefine_line|#define DREG_REGID_DMA_STATE                    0x0000021CL
DECL|macro|DREG_REGID_CURRENT_DMA_STREAM
mdefine_line|#define DREG_REGID_CURRENT_DMA_STREAM           0x0000021DL
DECL|macro|DREG_REGID_NEXT_DMA_STREAM
mdefine_line|#define DREG_REGID_NEXT_DMA_STREAM              0x0000021EL
DECL|macro|DREG_REGID_CPU_STATUS
mdefine_line|#define DREG_REGID_CPU_STATUS                   0x00000300L
DECL|macro|DREG_REGID_MAC_MODE
mdefine_line|#define DREG_REGID_MAC_MODE                     0x00000301L
DECL|macro|DREG_REGID_STACK_AND_REPEAT
mdefine_line|#define DREG_REGID_STACK_AND_REPEAT             0x00000302L
DECL|macro|DREG_REGID_INDEX0
mdefine_line|#define DREG_REGID_INDEX0                       0x00000304L
DECL|macro|DREG_REGID_INDEX1
mdefine_line|#define DREG_REGID_INDEX1                       0x00000305L
DECL|macro|DREG_REGID_DMA_STATE_0_3
mdefine_line|#define DREG_REGID_DMA_STATE_0_3                0x00000400L
DECL|macro|DREG_REGID_DMA_STATE_4_7
mdefine_line|#define DREG_REGID_DMA_STATE_4_7                0x00000404L
DECL|macro|DREG_REGID_DMA_STATE_8_11
mdefine_line|#define DREG_REGID_DMA_STATE_8_11               0x00000408L
DECL|macro|DREG_REGID_DMA_STATE_12_15
mdefine_line|#define DREG_REGID_DMA_STATE_12_15              0x0000040CL
DECL|macro|DREG_REGID_DMA_STATE_16_19
mdefine_line|#define DREG_REGID_DMA_STATE_16_19              0x00000410L
DECL|macro|DREG_REGID_DMA_STATE_20_23
mdefine_line|#define DREG_REGID_DMA_STATE_20_23              0x00000414L
DECL|macro|DREG_REGID_DMA_STATE_24_27
mdefine_line|#define DREG_REGID_DMA_STATE_24_27              0x00000418L
DECL|macro|DREG_REGID_DMA_STATE_28_31
mdefine_line|#define DREG_REGID_DMA_STATE_28_31              0x0000041CL
DECL|macro|DREG_REGID_DMA_STATE_32_35
mdefine_line|#define DREG_REGID_DMA_STATE_32_35              0x00000420L
DECL|macro|DREG_REGID_DMA_STATE_36_39
mdefine_line|#define DREG_REGID_DMA_STATE_36_39              0x00000424L
DECL|macro|DREG_REGID_DMA_STATE_40_43
mdefine_line|#define DREG_REGID_DMA_STATE_40_43              0x00000428L
DECL|macro|DREG_REGID_DMA_STATE_44_47
mdefine_line|#define DREG_REGID_DMA_STATE_44_47              0x0000042CL
DECL|macro|DREG_REGID_DMA_STATE_48_51
mdefine_line|#define DREG_REGID_DMA_STATE_48_51              0x00000430L
DECL|macro|DREG_REGID_DMA_STATE_52_55
mdefine_line|#define DREG_REGID_DMA_STATE_52_55              0x00000434L
DECL|macro|DREG_REGID_DMA_STATE_56_59
mdefine_line|#define DREG_REGID_DMA_STATE_56_59              0x00000438L
DECL|macro|DREG_REGID_DMA_STATE_60_63
mdefine_line|#define DREG_REGID_DMA_STATE_60_63              0x0000043CL
DECL|macro|DREG_REGID_DMA_STATE_64_67
mdefine_line|#define DREG_REGID_DMA_STATE_64_67              0x00000440L
DECL|macro|DREG_REGID_DMA_STATE_68_71
mdefine_line|#define DREG_REGID_DMA_STATE_68_71              0x00000444L
DECL|macro|DREG_REGID_DMA_STATE_72_75
mdefine_line|#define DREG_REGID_DMA_STATE_72_75              0x00000448L
DECL|macro|DREG_REGID_DMA_STATE_76_79
mdefine_line|#define DREG_REGID_DMA_STATE_76_79              0x0000044CL
DECL|macro|DREG_REGID_DMA_STATE_80_83
mdefine_line|#define DREG_REGID_DMA_STATE_80_83              0x00000450L
DECL|macro|DREG_REGID_DMA_STATE_84_87
mdefine_line|#define DREG_REGID_DMA_STATE_84_87              0x00000454L
DECL|macro|DREG_REGID_DMA_STATE_88_91
mdefine_line|#define DREG_REGID_DMA_STATE_88_91              0x00000458L
DECL|macro|DREG_REGID_DMA_STATE_92_95
mdefine_line|#define DREG_REGID_DMA_STATE_92_95              0x0000045CL
DECL|macro|DREG_REGID_TRAP_SELECT
mdefine_line|#define DREG_REGID_TRAP_SELECT                  0x00000500L
DECL|macro|DREG_REGID_TRAP_WRITE_0
mdefine_line|#define DREG_REGID_TRAP_WRITE_0                 0x00000500L
DECL|macro|DREG_REGID_TRAP_WRITE_1
mdefine_line|#define DREG_REGID_TRAP_WRITE_1                 0x00000501L
DECL|macro|DREG_REGID_TRAP_WRITE_2
mdefine_line|#define DREG_REGID_TRAP_WRITE_2                 0x00000502L
DECL|macro|DREG_REGID_TRAP_WRITE_3
mdefine_line|#define DREG_REGID_TRAP_WRITE_3                 0x00000503L
DECL|macro|DREG_REGID_TRAP_WRITE_4
mdefine_line|#define DREG_REGID_TRAP_WRITE_4                 0x00000504L
DECL|macro|DREG_REGID_TRAP_WRITE_5
mdefine_line|#define DREG_REGID_TRAP_WRITE_5                 0x00000505L
DECL|macro|DREG_REGID_TRAP_WRITE_6
mdefine_line|#define DREG_REGID_TRAP_WRITE_6                 0x00000506L
DECL|macro|DREG_REGID_TRAP_WRITE_7
mdefine_line|#define DREG_REGID_TRAP_WRITE_7                 0x00000507L
macro_line|#if !defined(NO_CS4612)
macro_line|#if !defined(NO_CS4615)
DECL|macro|DREG_REGID_TRAP_WRITE_8
mdefine_line|#define DREG_REGID_TRAP_WRITE_8                 0x00000510L
DECL|macro|DREG_REGID_TRAP_WRITE_9
mdefine_line|#define DREG_REGID_TRAP_WRITE_9                 0x00000511L
DECL|macro|DREG_REGID_TRAP_WRITE_10
mdefine_line|#define DREG_REGID_TRAP_WRITE_10                0x00000512L
DECL|macro|DREG_REGID_TRAP_WRITE_11
mdefine_line|#define DREG_REGID_TRAP_WRITE_11                0x00000513L
DECL|macro|DREG_REGID_TRAP_WRITE_12
mdefine_line|#define DREG_REGID_TRAP_WRITE_12                0x00000514L
DECL|macro|DREG_REGID_TRAP_WRITE_13
mdefine_line|#define DREG_REGID_TRAP_WRITE_13                0x00000515L
DECL|macro|DREG_REGID_TRAP_WRITE_14
mdefine_line|#define DREG_REGID_TRAP_WRITE_14                0x00000516L
DECL|macro|DREG_REGID_TRAP_WRITE_15
mdefine_line|#define DREG_REGID_TRAP_WRITE_15                0x00000517L
DECL|macro|DREG_REGID_TRAP_WRITE_16
mdefine_line|#define DREG_REGID_TRAP_WRITE_16                0x00000518L
DECL|macro|DREG_REGID_TRAP_WRITE_17
mdefine_line|#define DREG_REGID_TRAP_WRITE_17                0x00000519L
DECL|macro|DREG_REGID_TRAP_WRITE_18
mdefine_line|#define DREG_REGID_TRAP_WRITE_18                0x0000051AL
DECL|macro|DREG_REGID_TRAP_WRITE_19
mdefine_line|#define DREG_REGID_TRAP_WRITE_19                0x0000051BL
DECL|macro|DREG_REGID_TRAP_WRITE_20
mdefine_line|#define DREG_REGID_TRAP_WRITE_20                0x0000051CL
DECL|macro|DREG_REGID_TRAP_WRITE_21
mdefine_line|#define DREG_REGID_TRAP_WRITE_21                0x0000051DL
DECL|macro|DREG_REGID_TRAP_WRITE_22
mdefine_line|#define DREG_REGID_TRAP_WRITE_22                0x0000051EL
DECL|macro|DREG_REGID_TRAP_WRITE_23
mdefine_line|#define DREG_REGID_TRAP_WRITE_23                0x0000051FL
macro_line|#endif
macro_line|#endif
DECL|macro|DREG_REGID_MAC0_ACC0_LOW
mdefine_line|#define DREG_REGID_MAC0_ACC0_LOW                0x00000600L
DECL|macro|DREG_REGID_MAC0_ACC1_LOW
mdefine_line|#define DREG_REGID_MAC0_ACC1_LOW                0x00000601L
DECL|macro|DREG_REGID_MAC0_ACC2_LOW
mdefine_line|#define DREG_REGID_MAC0_ACC2_LOW                0x00000602L
DECL|macro|DREG_REGID_MAC0_ACC3_LOW
mdefine_line|#define DREG_REGID_MAC0_ACC3_LOW                0x00000603L
DECL|macro|DREG_REGID_MAC1_ACC0_LOW
mdefine_line|#define DREG_REGID_MAC1_ACC0_LOW                0x00000604L
DECL|macro|DREG_REGID_MAC1_ACC1_LOW
mdefine_line|#define DREG_REGID_MAC1_ACC1_LOW                0x00000605L
DECL|macro|DREG_REGID_MAC1_ACC2_LOW
mdefine_line|#define DREG_REGID_MAC1_ACC2_LOW                0x00000606L
DECL|macro|DREG_REGID_MAC1_ACC3_LOW
mdefine_line|#define DREG_REGID_MAC1_ACC3_LOW                0x00000607L
DECL|macro|DREG_REGID_MAC0_ACC0_MID
mdefine_line|#define DREG_REGID_MAC0_ACC0_MID                0x00000608L
DECL|macro|DREG_REGID_MAC0_ACC1_MID
mdefine_line|#define DREG_REGID_MAC0_ACC1_MID                0x00000609L
DECL|macro|DREG_REGID_MAC0_ACC2_MID
mdefine_line|#define DREG_REGID_MAC0_ACC2_MID                0x0000060AL
DECL|macro|DREG_REGID_MAC0_ACC3_MID
mdefine_line|#define DREG_REGID_MAC0_ACC3_MID                0x0000060BL
DECL|macro|DREG_REGID_MAC1_ACC0_MID
mdefine_line|#define DREG_REGID_MAC1_ACC0_MID                0x0000060CL
DECL|macro|DREG_REGID_MAC1_ACC1_MID
mdefine_line|#define DREG_REGID_MAC1_ACC1_MID                0x0000060DL
DECL|macro|DREG_REGID_MAC1_ACC2_MID
mdefine_line|#define DREG_REGID_MAC1_ACC2_MID                0x0000060EL
DECL|macro|DREG_REGID_MAC1_ACC3_MID
mdefine_line|#define DREG_REGID_MAC1_ACC3_MID                0x0000060FL
DECL|macro|DREG_REGID_MAC0_ACC0_HIGH
mdefine_line|#define DREG_REGID_MAC0_ACC0_HIGH               0x00000610L
DECL|macro|DREG_REGID_MAC0_ACC1_HIGH
mdefine_line|#define DREG_REGID_MAC0_ACC1_HIGH               0x00000611L
DECL|macro|DREG_REGID_MAC0_ACC2_HIGH
mdefine_line|#define DREG_REGID_MAC0_ACC2_HIGH               0x00000612L
DECL|macro|DREG_REGID_MAC0_ACC3_HIGH
mdefine_line|#define DREG_REGID_MAC0_ACC3_HIGH               0x00000613L
DECL|macro|DREG_REGID_MAC1_ACC0_HIGH
mdefine_line|#define DREG_REGID_MAC1_ACC0_HIGH               0x00000614L
DECL|macro|DREG_REGID_MAC1_ACC1_HIGH
mdefine_line|#define DREG_REGID_MAC1_ACC1_HIGH               0x00000615L
DECL|macro|DREG_REGID_MAC1_ACC2_HIGH
mdefine_line|#define DREG_REGID_MAC1_ACC2_HIGH               0x00000616L
DECL|macro|DREG_REGID_MAC1_ACC3_HIGH
mdefine_line|#define DREG_REGID_MAC1_ACC3_HIGH               0x00000617L
DECL|macro|DREG_REGID_RSHOUT_LOW
mdefine_line|#define DREG_REGID_RSHOUT_LOW                   0x00000620L
DECL|macro|DREG_REGID_RSHOUT_MID
mdefine_line|#define DREG_REGID_RSHOUT_MID                   0x00000628L
DECL|macro|DREG_REGID_RSHOUT_HIGH
mdefine_line|#define DREG_REGID_RSHOUT_HIGH                  0x00000630L
singleline_comment|//****************************************************************************
singleline_comment|//
singleline_comment|// The following defines are for the flags in the AC97 S/PDIF Control register.
singleline_comment|//
singleline_comment|//****************************************************************************
DECL|macro|SPDIF_CONTROL_SPDIF_EN
mdefine_line|#define SPDIF_CONTROL_SPDIF_EN                 0x00008000L
DECL|macro|SPDIF_CONTROL_VAL
mdefine_line|#define SPDIF_CONTROL_VAL                      0x00004000L
DECL|macro|SPDIF_CONTROL_COPY
mdefine_line|#define SPDIF_CONTROL_COPY                     0x00000004L
DECL|macro|SPDIF_CONTROL_CC0
mdefine_line|#define SPDIF_CONTROL_CC0                      0x00000010L
DECL|macro|SPDIF_CONTROL_CC1
mdefine_line|#define SPDIF_CONTROL_CC1                      0x00000020L
DECL|macro|SPDIF_CONTROL_CC2
mdefine_line|#define SPDIF_CONTROL_CC2                      0x00000040L
DECL|macro|SPDIF_CONTROL_CC3
mdefine_line|#define SPDIF_CONTROL_CC3                      0x00000080L
DECL|macro|SPDIF_CONTROL_CC4
mdefine_line|#define SPDIF_CONTROL_CC4                      0x00000100L
DECL|macro|SPDIF_CONTROL_CC5
mdefine_line|#define SPDIF_CONTROL_CC5                      0x00000200L
DECL|macro|SPDIF_CONTROL_CC6
mdefine_line|#define SPDIF_CONTROL_CC6                      0x00000400L
DECL|macro|SPDIF_CONTROL_L
mdefine_line|#define SPDIF_CONTROL_L                        0x00000800L
macro_line|#endif 
singleline_comment|// _H_HWDEFS
eof
