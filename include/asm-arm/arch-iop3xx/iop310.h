multiline_comment|/*&n; * linux/include/asm/arch-iop310/iop310.h&n; *&n; * Intel IOP310 Compainion Chip definitions&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#ifndef _IOP310_HW_H_
DECL|macro|_IOP310_HW_H_
mdefine_line|#define _IOP310_HW_H_
multiline_comment|/*&n; * IOP310 I/O and Mem space regions for PCI autoconfiguration&n; */
DECL|macro|IOP310_PCISEC_LOWER_IO
mdefine_line|#define IOP310_PCISEC_LOWER_IO&t;&t;0x90010000
DECL|macro|IOP310_PCISEC_UPPER_IO
mdefine_line|#define IOP310_PCISEC_UPPER_IO&t;&t;0x9001ffff
DECL|macro|IOP310_PCISEC_LOWER_MEM
mdefine_line|#define IOP310_PCISEC_LOWER_MEM&t;&t;0x88000000
DECL|macro|IOP310_PCISEC_UPPER_MEM
mdefine_line|#define IOP310_PCISEC_UPPER_MEM&t;&t;0x8bffffff
DECL|macro|IOP310_PCIPRI_LOWER_IO
mdefine_line|#define IOP310_PCIPRI_LOWER_IO&t;&t;0x90000000
DECL|macro|IOP310_PCIPRI_UPPER_IO
mdefine_line|#define IOP310_PCIPRI_UPPER_IO&t;&t;0x9000ffff
DECL|macro|IOP310_PCIPRI_LOWER_MEM
mdefine_line|#define IOP310_PCIPRI_LOWER_MEM&t;&t;0x80000000
DECL|macro|IOP310_PCIPRI_UPPER_MEM
mdefine_line|#define IOP310_PCIPRI_UPPER_MEM&t;&t;0x83ffffff
DECL|macro|IOP310_PCI_WINDOW_SIZE
mdefine_line|#define IOP310_PCI_WINDOW_SIZE&t;&t;64 * 0x100000
multiline_comment|/*&n; * IOP310 chipset registers&n; */
DECL|macro|IOP310_VIRT_MEM_BASE
mdefine_line|#define IOP310_VIRT_MEM_BASE 0xe8001000  /* chip virtual mem address*/
DECL|macro|IOP310_PHY_MEM_BASE
mdefine_line|#define IOP310_PHY_MEM_BASE  0x00001000  /* chip physical memory address */
DECL|macro|IOP310_REG_ADDR
mdefine_line|#define IOP310_REG_ADDR(reg) (IOP310_VIRT_MEM_BASE | IOP310_PHY_MEM_BASE | (reg))
multiline_comment|/* PCI-to-PCI Bridge Unit 0x00001000 through 0x000010FF */
DECL|macro|IOP310_VIDR
mdefine_line|#define IOP310_VIDR    (volatile u16 *)IOP310_REG_ADDR(0x00001000)
DECL|macro|IOP310_DIDR
mdefine_line|#define IOP310_DIDR    (volatile u16 *)IOP310_REG_ADDR(0x00001002)
DECL|macro|IOP310_PCR
mdefine_line|#define IOP310_PCR     (volatile u16 *)IOP310_REG_ADDR(0x00001004)
DECL|macro|IOP310_PSR
mdefine_line|#define IOP310_PSR     (volatile u16 *)IOP310_REG_ADDR(0x00001006)
DECL|macro|IOP310_RIDR
mdefine_line|#define IOP310_RIDR    (volatile u8  *)IOP310_REG_ADDR(0x00001008)
DECL|macro|IOP310_CCR
mdefine_line|#define IOP310_CCR     (volatile u32 *)IOP310_REG_ADDR(0x00001009)
DECL|macro|IOP310_CLSR
mdefine_line|#define IOP310_CLSR    (volatile u8  *)IOP310_REG_ADDR(0x0000100C)
DECL|macro|IOP310_PLTR
mdefine_line|#define IOP310_PLTR    (volatile u8  *)IOP310_REG_ADDR(0x0000100D)
DECL|macro|IOP310_HTR
mdefine_line|#define IOP310_HTR     (volatile u8  *)IOP310_REG_ADDR(0x0000100E)
multiline_comment|/* Reserved 0x0000100F through  0x00001017 */
DECL|macro|IOP310_PBNR
mdefine_line|#define IOP310_PBNR    (volatile u8  *)IOP310_REG_ADDR(0x00001018)
DECL|macro|IOP310_SBNR
mdefine_line|#define IOP310_SBNR    (volatile u8  *)IOP310_REG_ADDR(0x00001019)
DECL|macro|IOP310_SUBBNR
mdefine_line|#define IOP310_SUBBNR  (volatile u8  *)IOP310_REG_ADDR(0x0000101A)
DECL|macro|IOP310_SLTR
mdefine_line|#define IOP310_SLTR    (volatile u8  *)IOP310_REG_ADDR(0x0000101B)
DECL|macro|IOP310_IOBR
mdefine_line|#define IOP310_IOBR    (volatile u8  *)IOP310_REG_ADDR(0x0000101C)
DECL|macro|IOP310_IOLR
mdefine_line|#define IOP310_IOLR    (volatile u8  *)IOP310_REG_ADDR(0x0000101D)
DECL|macro|IOP310_SSR
mdefine_line|#define IOP310_SSR     (volatile u16 *)IOP310_REG_ADDR(0x0000101E)
DECL|macro|IOP310_MBR
mdefine_line|#define IOP310_MBR     (volatile u16 *)IOP310_REG_ADDR(0x00001020)
DECL|macro|IOP310_MLR
mdefine_line|#define IOP310_MLR     (volatile u16 *)IOP310_REG_ADDR(0x00001022)
DECL|macro|IOP310_PMBR
mdefine_line|#define IOP310_PMBR    (volatile u16 *)IOP310_REG_ADDR(0x00001024)
DECL|macro|IOP310_PMLR
mdefine_line|#define IOP310_PMLR    (volatile u16 *)IOP310_REG_ADDR(0x00001026)
multiline_comment|/* Reserved 0x00001028 through 0x00001033 */
DECL|macro|IOP310_CAPR
mdefine_line|#define IOP310_CAPR    (volatile u8  *)IOP310_REG_ADDR(0x00001034)
multiline_comment|/* Reserved 0x00001035 through 0x0000103D */
DECL|macro|IOP310_BCR
mdefine_line|#define IOP310_BCR     (volatile u16 *)IOP310_REG_ADDR(0x0000103E)
DECL|macro|IOP310_EBCR
mdefine_line|#define IOP310_EBCR    (volatile u16 *)IOP310_REG_ADDR(0x00001040)
DECL|macro|IOP310_SISR
mdefine_line|#define IOP310_SISR    (volatile u16 *)IOP310_REG_ADDR(0x00001042)
DECL|macro|IOP310_PBISR
mdefine_line|#define IOP310_PBISR   (volatile u32 *)IOP310_REG_ADDR(0x00001044)
DECL|macro|IOP310_SBISR
mdefine_line|#define IOP310_SBISR   (volatile u32 *)IOP310_REG_ADDR(0x00001048)
DECL|macro|IOP310_SACR
mdefine_line|#define IOP310_SACR    (volatile u32 *)IOP310_REG_ADDR(0x0000104C)
DECL|macro|IOP310_PIRSR
mdefine_line|#define IOP310_PIRSR   (volatile u32 *)IOP310_REG_ADDR(0x00001050)
DECL|macro|IOP310_SIOBR
mdefine_line|#define IOP310_SIOBR   (volatile u8  *)IOP310_REG_ADDR(0x00001054)
DECL|macro|IOP310_SIOLR
mdefine_line|#define IOP310_SIOLR   (volatile u8  *)IOP310_REG_ADDR(0x00001055)
DECL|macro|IOP310_SCDR
mdefine_line|#define IOP310_SCDR    (volatile u8  *)IOP310_REG_ADDR(0x00001056)
DECL|macro|IOP310_SMBR
mdefine_line|#define IOP310_SMBR    (volatile u16 *)IOP310_REG_ADDR(0x00001058)
DECL|macro|IOP310_SMLR
mdefine_line|#define IOP310_SMLR    (volatile u16 *)IOP310_REG_ADDR(0x0000105A)
DECL|macro|IOP310_SDER
mdefine_line|#define IOP310_SDER    (volatile u16 *)IOP310_REG_ADDR(0x0000105C)
DECL|macro|IOP310_QCR
mdefine_line|#define IOP310_QCR     (volatile u16 *)IOP310_REG_ADDR(0x0000105E)
DECL|macro|IOP310_CAPID
mdefine_line|#define IOP310_CAPID   (volatile u8  *)IOP310_REG_ADDR(0x00001068)
DECL|macro|IOP310_NIPTR
mdefine_line|#define IOP310_NIPTR   (volatile u8  *)IOP310_REG_ADDR(0x00001069)
DECL|macro|IOP310_PMCR
mdefine_line|#define IOP310_PMCR    (volatile u16 *)IOP310_REG_ADDR(0x0000106A)
DECL|macro|IOP310_PMCSR
mdefine_line|#define IOP310_PMCSR   (volatile u16 *)IOP310_REG_ADDR(0x0000106C)
DECL|macro|IOP310_PMCSRBSE
mdefine_line|#define IOP310_PMCSRBSE (volatile u8 *)IOP310_REG_ADDR(0x0000106E)
multiline_comment|/* Reserved 0x00001064 through 0x000010FFH */
multiline_comment|/* Performance monitoring unit  0x00001100 through 0x000011FF*/
DECL|macro|IOP310_PMONGTMR
mdefine_line|#define IOP310_PMONGTMR    (volatile u32 *)IOP310_REG_ADDR(0x00001100)
DECL|macro|IOP310_PMONESR
mdefine_line|#define IOP310_PMONESR     (volatile u32 *)IOP310_REG_ADDR(0x00001104)
DECL|macro|IOP310_PMONEMISR
mdefine_line|#define IOP310_PMONEMISR   (volatile u32 *)IOP310_REG_ADDR(0x00001108)
DECL|macro|IOP310_PMONGTSR
mdefine_line|#define IOP310_PMONGTSR    (volatile u32 *)IOP310_REG_ADDR(0x00001110)
DECL|macro|IOP310_PMONPECR1
mdefine_line|#define IOP310_PMONPECR1   (volatile u32 *)IOP310_REG_ADDR(0x00001114)
DECL|macro|IOP310_PMONPECR2
mdefine_line|#define IOP310_PMONPECR2   (volatile u32 *)IOP310_REG_ADDR(0x00001118)
DECL|macro|IOP310_PMONPECR3
mdefine_line|#define IOP310_PMONPECR3   (volatile u32 *)IOP310_REG_ADDR(0x0000111C)
DECL|macro|IOP310_PMONPECR4
mdefine_line|#define IOP310_PMONPECR4   (volatile u32 *)IOP310_REG_ADDR(0x00001120)
DECL|macro|IOP310_PMONPECR5
mdefine_line|#define IOP310_PMONPECR5   (volatile u32 *)IOP310_REG_ADDR(0x00001124)
DECL|macro|IOP310_PMONPECR6
mdefine_line|#define IOP310_PMONPECR6   (volatile u32 *)IOP310_REG_ADDR(0x00001128)
DECL|macro|IOP310_PMONPECR7
mdefine_line|#define IOP310_PMONPECR7   (volatile u32 *)IOP310_REG_ADDR(0x0000112C)
DECL|macro|IOP310_PMONPECR8
mdefine_line|#define IOP310_PMONPECR8   (volatile u32 *)IOP310_REG_ADDR(0x00001130)
DECL|macro|IOP310_PMONPECR9
mdefine_line|#define IOP310_PMONPECR9   (volatile u32 *)IOP310_REG_ADDR(0x00001134)
DECL|macro|IOP310_PMONPECR10
mdefine_line|#define IOP310_PMONPECR10  (volatile u32 *)IOP310_REG_ADDR(0x00001138)
DECL|macro|IOP310_PMONPECR11
mdefine_line|#define IOP310_PMONPECR11  (volatile u32 *)IOP310_REG_ADDR(0x0000113C)
DECL|macro|IOP310_PMONPECR12
mdefine_line|#define IOP310_PMONPECR12  (volatile u32 *)IOP310_REG_ADDR(0x00001140)
DECL|macro|IOP310_PMONPECR13
mdefine_line|#define IOP310_PMONPECR13  (volatile u32 *)IOP310_REG_ADDR(0x00001144)
DECL|macro|IOP310_PMONPECR14
mdefine_line|#define IOP310_PMONPECR14  (volatile u32 *)IOP310_REG_ADDR(0x00001148)
multiline_comment|/* Address Translation Unit 0x00001200 through 0x000012FF */
DECL|macro|IOP310_ATUVID
mdefine_line|#define IOP310_ATUVID     (volatile u16 *)IOP310_REG_ADDR(0x00001200)
DECL|macro|IOP310_ATUDID
mdefine_line|#define IOP310_ATUDID     (volatile u16 *)IOP310_REG_ADDR(0x00001202)
DECL|macro|IOP310_PATUCMD
mdefine_line|#define IOP310_PATUCMD    (volatile u16 *)IOP310_REG_ADDR(0x00001204)
DECL|macro|IOP310_PATUSR
mdefine_line|#define IOP310_PATUSR     (volatile u16 *)IOP310_REG_ADDR(0x00001206)
DECL|macro|IOP310_ATURID
mdefine_line|#define IOP310_ATURID     (volatile u8  *)IOP310_REG_ADDR(0x00001208)
DECL|macro|IOP310_ATUCCR
mdefine_line|#define IOP310_ATUCCR     (volatile u32 *)IOP310_REG_ADDR(0x00001209)
DECL|macro|IOP310_ATUCLSR
mdefine_line|#define IOP310_ATUCLSR    (volatile u8  *)IOP310_REG_ADDR(0x0000120C)
DECL|macro|IOP310_ATULT
mdefine_line|#define IOP310_ATULT      (volatile u8  *)IOP310_REG_ADDR(0x0000120D)
DECL|macro|IOP310_ATUHTR
mdefine_line|#define IOP310_ATUHTR     (volatile u8  *)IOP310_REG_ADDR(0x0000120E)
DECL|macro|IOP310_PIABAR
mdefine_line|#define IOP310_PIABAR     (volatile u32 *)IOP310_REG_ADDR(0x00001210)
multiline_comment|/* Reserved 0x00001214 through 0x0000122B */
DECL|macro|IOP310_ASVIR
mdefine_line|#define IOP310_ASVIR      (volatile u16 *)IOP310_REG_ADDR(0x0000122C)
DECL|macro|IOP310_ASIR
mdefine_line|#define IOP310_ASIR       (volatile u16 *)IOP310_REG_ADDR(0x0000122E)
DECL|macro|IOP310_ERBAR
mdefine_line|#define IOP310_ERBAR      (volatile u32 *)IOP310_REG_ADDR(0x00001230)
DECL|macro|IOP310_ATUCAPPTR
mdefine_line|#define IOP310_ATUCAPPTR  (volatile u8  *)IOP310_REG_ADDR(0x00001234)
multiline_comment|/* Reserved 0x00001235 through 0x0000123B */
DECL|macro|IOP310_ATUILR
mdefine_line|#define IOP310_ATUILR     (volatile u8  *)IOP310_REG_ADDR(0x0000123C)
DECL|macro|IOP310_ATUIPR
mdefine_line|#define IOP310_ATUIPR     (volatile u8  *)IOP310_REG_ADDR(0x0000123D)
DECL|macro|IOP310_ATUMGNT
mdefine_line|#define IOP310_ATUMGNT    (volatile u8  *)IOP310_REG_ADDR(0x0000123E)
DECL|macro|IOP310_ATUMLAT
mdefine_line|#define IOP310_ATUMLAT    (volatile u8  *)IOP310_REG_ADDR(0x0000123F)
DECL|macro|IOP310_PIALR
mdefine_line|#define IOP310_PIALR      (volatile u32 *)IOP310_REG_ADDR(0x00001240)
DECL|macro|IOP310_PIATVR
mdefine_line|#define IOP310_PIATVR     (volatile u32 *)IOP310_REG_ADDR(0x00001244)
DECL|macro|IOP310_SIABAR
mdefine_line|#define IOP310_SIABAR     (volatile u32 *)IOP310_REG_ADDR(0x00001248)
DECL|macro|IOP310_SIALR
mdefine_line|#define IOP310_SIALR      (volatile u32 *)IOP310_REG_ADDR(0x0000124C)
DECL|macro|IOP310_SIATVR
mdefine_line|#define IOP310_SIATVR     (volatile u32 *)IOP310_REG_ADDR(0x00001250)
DECL|macro|IOP310_POMWVR
mdefine_line|#define IOP310_POMWVR     (volatile u32 *)IOP310_REG_ADDR(0x00001254)
multiline_comment|/* Reserved 0x00001258 through 0x0000125B */
DECL|macro|IOP310_POIOWVR
mdefine_line|#define IOP310_POIOWVR    (volatile u32 *)IOP310_REG_ADDR(0x0000125C)
DECL|macro|IOP310_PODWVR
mdefine_line|#define IOP310_PODWVR     (volatile u32 *)IOP310_REG_ADDR(0x00001260)
DECL|macro|IOP310_POUDR
mdefine_line|#define IOP310_POUDR      (volatile u32 *)IOP310_REG_ADDR(0x00001264)
DECL|macro|IOP310_SOMWVR
mdefine_line|#define IOP310_SOMWVR     (volatile u32 *)IOP310_REG_ADDR(0x00001268)
DECL|macro|IOP310_SOIOWVR
mdefine_line|#define IOP310_SOIOWVR    (volatile u32 *)IOP310_REG_ADDR(0x0000126C)
multiline_comment|/* Reserved 0x00001270 through 0x00001273*/
DECL|macro|IOP310_ERLR
mdefine_line|#define IOP310_ERLR       (volatile u32 *)IOP310_REG_ADDR(0x00001274)
DECL|macro|IOP310_ERTVR
mdefine_line|#define IOP310_ERTVR      (volatile u32 *)IOP310_REG_ADDR(0x00001278)
multiline_comment|/* Reserved 0x00001279 through 0x0000127C*/
DECL|macro|IOP310_ATUCAPID
mdefine_line|#define IOP310_ATUCAPID   (volatile u8  *)IOP310_REG_ADDR(0x00001280)
DECL|macro|IOP310_ATUNIPTR
mdefine_line|#define IOP310_ATUNIPTR   (volatile u8  *)IOP310_REG_ADDR(0x00001281)
DECL|macro|IOP310_APMCR
mdefine_line|#define IOP310_APMCR      (volatile u16 *)IOP310_REG_ADDR(0x00001282)
DECL|macro|IOP310_APMCSR
mdefine_line|#define IOP310_APMCSR     (volatile u16 *)IOP310_REG_ADDR(0x00001284)
multiline_comment|/* Reserved 0x00001286 through 0x00001287 */
DECL|macro|IOP310_ATUCR
mdefine_line|#define IOP310_ATUCR      (volatile u32 *)IOP310_REG_ADDR(0x00001288)
multiline_comment|/* Reserved 0x00001289  through 0x0000128C*/
DECL|macro|IOP310_PATUISR
mdefine_line|#define IOP310_PATUISR    (volatile u32 *)IOP310_REG_ADDR(0x00001290)
DECL|macro|IOP310_SATUISR
mdefine_line|#define IOP310_SATUISR    (volatile u32 *)IOP310_REG_ADDR(0x00001294)
DECL|macro|IOP310_SATUCMD
mdefine_line|#define IOP310_SATUCMD    (volatile u16 *)IOP310_REG_ADDR(0x00001298)
DECL|macro|IOP310_SATUSR
mdefine_line|#define IOP310_SATUSR     (volatile u16 *)IOP310_REG_ADDR(0x0000129A)
DECL|macro|IOP310_SODWVR
mdefine_line|#define IOP310_SODWVR     (volatile u32 *)IOP310_REG_ADDR(0x0000129C)
DECL|macro|IOP310_SOUDR
mdefine_line|#define IOP310_SOUDR      (volatile u32 *)IOP310_REG_ADDR(0x000012A0)
DECL|macro|IOP310_POCCAR
mdefine_line|#define IOP310_POCCAR     (volatile u32 *)IOP310_REG_ADDR(0x000012A4)
DECL|macro|IOP310_SOCCAR
mdefine_line|#define IOP310_SOCCAR     (volatile u32 *)IOP310_REG_ADDR(0x000012A8)
DECL|macro|IOP310_POCCDR
mdefine_line|#define IOP310_POCCDR     (volatile u32 *)IOP310_REG_ADDR(0x000012AC)
DECL|macro|IOP310_SOCCDR
mdefine_line|#define IOP310_SOCCDR     (volatile u32 *)IOP310_REG_ADDR(0x000012B0)
DECL|macro|IOP310_PAQCR
mdefine_line|#define IOP310_PAQCR      (volatile u32 *)IOP310_REG_ADDR(0x000012B4)
DECL|macro|IOP310_SAQCR
mdefine_line|#define IOP310_SAQCR      (volatile u32 *)IOP310_REG_ADDR(0x000012B8)
DECL|macro|IOP310_PATUIMR
mdefine_line|#define IOP310_PATUIMR    (volatile u32 *)IOP310_REG_ADDR(0x000012BC)
DECL|macro|IOP310_SATUIMR
mdefine_line|#define IOP310_SATUIMR    (volatile u32 *)IOP310_REG_ADDR(0x000012C0)
multiline_comment|/* Reserved 0x000012C4 through 0x000012FF */
multiline_comment|/* Messaging Unit 0x00001300 through 0x000013FF */
DECL|macro|IOP310_MUIMR0
mdefine_line|#define IOP310_MUIMR0       (volatile u32 *)IOP310_REG_ADDR(0x00001310)
DECL|macro|IOP310_MUIMR1
mdefine_line|#define IOP310_MUIMR1       (volatile u32 *)IOP310_REG_ADDR(0x00001314)
DECL|macro|IOP310_MUOMR0
mdefine_line|#define IOP310_MUOMR0       (volatile u32 *)IOP310_REG_ADDR(0x00001318)
DECL|macro|IOP310_MUOMR1
mdefine_line|#define IOP310_MUOMR1       (volatile u32 *)IOP310_REG_ADDR(0x0000131C)
DECL|macro|IOP310_MUIDR
mdefine_line|#define IOP310_MUIDR        (volatile u32 *)IOP310_REG_ADDR(0x00001320)
DECL|macro|IOP310_MUIISR
mdefine_line|#define IOP310_MUIISR       (volatile u32 *)IOP310_REG_ADDR(0x00001324)
DECL|macro|IOP310_MUIIMR
mdefine_line|#define IOP310_MUIIMR       (volatile u32 *)IOP310_REG_ADDR(0x00001328)
DECL|macro|IOP310_MUODR
mdefine_line|#define IOP310_MUODR        (volatile u32 *)IOP310_REG_ADDR(0x0000132C)
DECL|macro|IOP310_MUOISR
mdefine_line|#define IOP310_MUOISR       (volatile u32 *)IOP310_REG_ADDR(0x00001330)
DECL|macro|IOP310_MUOIMR
mdefine_line|#define IOP310_MUOIMR       (volatile u32 *)IOP310_REG_ADDR(0x00001334)
DECL|macro|IOP310_MUMUCR
mdefine_line|#define IOP310_MUMUCR       (volatile u32 *)IOP310_REG_ADDR(0x00001350)
DECL|macro|IOP310_MUQBAR
mdefine_line|#define IOP310_MUQBAR       (volatile u32 *)IOP310_REG_ADDR(0x00001354)
DECL|macro|IOP310_MUIFHPR
mdefine_line|#define IOP310_MUIFHPR      (volatile u32 *)IOP310_REG_ADDR(0x00001360)
DECL|macro|IOP310_MUIFTPR
mdefine_line|#define IOP310_MUIFTPR      (volatile u32 *)IOP310_REG_ADDR(0x00001364)
DECL|macro|IOP310_MUIPHPR
mdefine_line|#define IOP310_MUIPHPR      (volatile u32 *)IOP310_REG_ADDR(0x00001368)
DECL|macro|IOP310_MUIPTPR
mdefine_line|#define IOP310_MUIPTPR      (volatile u32 *)IOP310_REG_ADDR(0x0000136C)
DECL|macro|IOP310_MUOFHPR
mdefine_line|#define IOP310_MUOFHPR      (volatile u32 *)IOP310_REG_ADDR(0x00001370)
DECL|macro|IOP310_MUOFTPR
mdefine_line|#define IOP310_MUOFTPR      (volatile u32 *)IOP310_REG_ADDR(0x00001374)
DECL|macro|IOP310_MUOPHPR
mdefine_line|#define IOP310_MUOPHPR      (volatile u32 *)IOP310_REG_ADDR(0x00001378)
DECL|macro|IOP310_MUOPTPR
mdefine_line|#define IOP310_MUOPTPR      (volatile u32 *)IOP310_REG_ADDR(0x0000137C)
DECL|macro|IOP310_MUIAR
mdefine_line|#define IOP310_MUIAR        (volatile u32 *)IOP310_REG_ADDR(0x00001380)
multiline_comment|/* DMA Controller 0x00001400 through 0x000014FF */
DECL|macro|IOP310_DMA0CCR
mdefine_line|#define IOP310_DMA0CCR     (volatile u32 *)IOP310_REG_ADDR(0x00001400)
DECL|macro|IOP310_DMA0CSR
mdefine_line|#define IOP310_DMA0CSR     (volatile u32 *)IOP310_REG_ADDR(0x00001404)
multiline_comment|/* Reserved 0x001408 through 0x00140B */
DECL|macro|IOP310_DMA0DAR
mdefine_line|#define IOP310_DMA0DAR     (volatile u32 *)IOP310_REG_ADDR(0x0000140C)
DECL|macro|IOP310_DMA0NDAR
mdefine_line|#define IOP310_DMA0NDAR    (volatile u32 *)IOP310_REG_ADDR(0x00001410)
DECL|macro|IOP310_DMA0PADR
mdefine_line|#define IOP310_DMA0PADR    (volatile u32 *)IOP310_REG_ADDR(0x00001414)
DECL|macro|IOP310_DMA0PUADR
mdefine_line|#define IOP310_DMA0PUADR   (volatile u32 *)IOP310_REG_ADDR(0x00001418)
DECL|macro|IOP310_DMA0LADR
mdefine_line|#define IOP310_DMA0LADR    (volatile u32 *)IOP310_REG_ADDR(0x0000141C)
DECL|macro|IOP310_DMA0BCR
mdefine_line|#define IOP310_DMA0BCR     (volatile u32 *)IOP310_REG_ADDR(0x00001420)
DECL|macro|IOP310_DMA0DCR
mdefine_line|#define IOP310_DMA0DCR     (volatile u32 *)IOP310_REG_ADDR(0x00001424)
multiline_comment|/* Reserved 0x00001428 through 0x0000143F */
DECL|macro|IOP310_DMA1CCR
mdefine_line|#define IOP310_DMA1CCR     (volatile u32 *)IOP310_REG_ADDR(0x00001440)
DECL|macro|IOP310_DMA1CSR
mdefine_line|#define IOP310_DMA1CSR     (volatile u32 *)IOP310_REG_ADDR(0x00001444)
multiline_comment|/* Reserved 0x00001448 through 0x0000144B */
DECL|macro|IOP310_DMA1DAR
mdefine_line|#define IOP310_DMA1DAR     (volatile u32 *)IOP310_REG_ADDR(0x0000144C)
DECL|macro|IOP310_DMA1NDAR
mdefine_line|#define IOP310_DMA1NDAR    (volatile u32 *)IOP310_REG_ADDR(0x00001450)
DECL|macro|IOP310_DMA1PADR
mdefine_line|#define IOP310_DMA1PADR    (volatile u32 *)IOP310_REG_ADDR(0x00001454)
DECL|macro|IOP310_DMA1PUADR
mdefine_line|#define IOP310_DMA1PUADR   (volatile u32 *)IOP310_REG_ADDR(0x00001458)
DECL|macro|IOP310_DMA1LADR
mdefine_line|#define IOP310_DMA1LADR    (volatile u32 *)IOP310_REG_ADDR(0x0000145C)
DECL|macro|IOP310_DMA1BCR
mdefine_line|#define IOP310_DMA1BCR     (volatile u32 *)IOP310_REG_ADDR(0x00001460)
DECL|macro|IOP310_DMA1DCR
mdefine_line|#define IOP310_DMA1DCR     (volatile u32 *)IOP310_REG_ADDR(0x00001464)
multiline_comment|/* Reserved 0x00001468 through 0x0000147F */
DECL|macro|IOP310_DMA2CCR
mdefine_line|#define IOP310_DMA2CCR     (volatile u32 *)IOP310_REG_ADDR(0x00001480)
DECL|macro|IOP310_DMA2CSR
mdefine_line|#define IOP310_DMA2CSR     (volatile u32 *)IOP310_REG_ADDR(0x00001484)
multiline_comment|/* Reserved 0x00001488 through 0x0000148B */
DECL|macro|IOP310_DMA2DAR
mdefine_line|#define IOP310_DMA2DAR     (volatile u32 *)IOP310_REG_ADDR(0x0000148C)
DECL|macro|IOP310_DMA2NDAR
mdefine_line|#define IOP310_DMA2NDAR    (volatile u32 *)IOP310_REG_ADDR(0x00001490)
DECL|macro|IOP310_DMA2PADR
mdefine_line|#define IOP310_DMA2PADR    (volatile u32 *)IOP310_REG_ADDR(0x00001494)
DECL|macro|IOP310_DMA2PUADR
mdefine_line|#define IOP310_DMA2PUADR   (volatile u32 *)IOP310_REG_ADDR(0x00001498)
DECL|macro|IOP310_DMA2LADR
mdefine_line|#define IOP310_DMA2LADR    (volatile u32 *)IOP310_REG_ADDR(0x0000149C)
DECL|macro|IOP310_DMA2BCR
mdefine_line|#define IOP310_DMA2BCR     (volatile u32 *)IOP310_REG_ADDR(0x000014A0)
DECL|macro|IOP310_DMA2DCR
mdefine_line|#define IOP310_DMA2DCR     (volatile u32 *)IOP310_REG_ADDR(0x000014A4)
multiline_comment|/* Memory controller 0x00001500 through 0x0015FF */
multiline_comment|/* core interface unit 0x00001640 - 0x0000167F */
DECL|macro|IOP310_CIUISR
mdefine_line|#define IOP310_CIUISR     (volatile u32 *)IOP310_REG_ADDR(0x00001644)
multiline_comment|/* PCI and Peripheral Interrupt Controller 0x00001700 - 0x0000171B */
DECL|macro|IOP310_IRQISR
mdefine_line|#define IOP310_IRQISR     (volatile u32 *)IOP310_REG_ADDR(0x00001700)
DECL|macro|IOP310_FIQ2ISR
mdefine_line|#define IOP310_FIQ2ISR    (volatile u32 *)IOP310_REG_ADDR(0x00001704)
DECL|macro|IOP310_FIQ1ISR
mdefine_line|#define IOP310_FIQ1ISR    (volatile u32 *)IOP310_REG_ADDR(0x00001708)
DECL|macro|IOP310_PDIDR
mdefine_line|#define IOP310_PDIDR      (volatile u32 *)IOP310_REG_ADDR(0x00001710)
multiline_comment|/* AAU registers. DJ 0x00001800 - 0x00001838 */
DECL|macro|IOP310_AAUACR
mdefine_line|#define IOP310_AAUACR    (volatile u32 *)IOP310_REG_ADDR(0x00001800)
DECL|macro|IOP310_AAUASR
mdefine_line|#define IOP310_AAUASR    (volatile u32 *)IOP310_REG_ADDR(0x00001804)
DECL|macro|IOP310_AAUADAR
mdefine_line|#define IOP310_AAUADAR   (volatile u32 *)IOP310_REG_ADDR(0x00001808)
DECL|macro|IOP310_AAUANDAR
mdefine_line|#define IOP310_AAUANDAR  (volatile u32 *)IOP310_REG_ADDR(0x0000180C)
DECL|macro|IOP310_AAUSAR1
mdefine_line|#define IOP310_AAUSAR1   (volatile u32 *)IOP310_REG_ADDR(0x00001810)
DECL|macro|IOP310_AAUSAR2
mdefine_line|#define IOP310_AAUSAR2   (volatile u32 *)IOP310_REG_ADDR(0x00001814)
DECL|macro|IOP310_AAUSAR3
mdefine_line|#define IOP310_AAUSAR3   (volatile u32 *)IOP310_REG_ADDR(0x00001818)
DECL|macro|IOP310_AAUSAR4
mdefine_line|#define IOP310_AAUSAR4   (volatile u32 *)IOP310_REG_ADDR(0x0000181C)
DECL|macro|IOP310_AAUDAR
mdefine_line|#define IOP310_AAUDAR    (volatile u32 *)IOP310_REG_ADDR(0x00001820)
DECL|macro|IOP310_AAUABCR
mdefine_line|#define IOP310_AAUABCR   (volatile u32 *)IOP310_REG_ADDR(0x00001824)
DECL|macro|IOP310_AAUADCR
mdefine_line|#define IOP310_AAUADCR   (volatile u32 *)IOP310_REG_ADDR(0x00001828)
DECL|macro|IOP310_AAUSAR5
mdefine_line|#define IOP310_AAUSAR5   (volatile u32 *)IOP310_REG_ADDR(0x0000182C)
DECL|macro|IOP310_AAUSAR6
mdefine_line|#define IOP310_AAUSAR6   (volatile u32 *)IOP310_REG_ADDR(0x00001830)
DECL|macro|IOP310_AAUSAR7
mdefine_line|#define IOP310_AAUSAR7   (volatile u32 *)IOP310_REG_ADDR(0x00001834)
DECL|macro|IOP310_AAUSAR8
mdefine_line|#define IOP310_AAUSAR8   (volatile u32 *)IOP310_REG_ADDR(0x00001838)
macro_line|#endif 
singleline_comment|// _IOP310_HW_H_
eof
