multiline_comment|/* $XConsortium: nvreg.h /main/2 1996/10/28 05:13:41 kaleb $ */
multiline_comment|/*&n; * Copyright 1996-1997  David J. McKay&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; *&n; * The above copyright notice and this permission notice shall be included in&n; * all copies or substantial portions of the Software.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR&n; * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * DAVID J. MCKAY BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,&n; * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF&n; * OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE&n; * SOFTWARE.&n; */
multiline_comment|/* $XFree86: xc/programs/Xserver/hw/xfree86/vga256/drivers/nv/nvreg.h,v 3.2.2.1 1998/01/18 10:35:36 hohndel Exp $ */
macro_line|#ifndef __NVREG_H_
DECL|macro|__NVREG_H_
mdefine_line|#define __NVREG_H_
multiline_comment|/* Little macro to construct bitmask for contiguous ranges of bits */
DECL|macro|BITMASK
mdefine_line|#define BITMASK(t,b) (((unsigned)(1U &lt;&lt; (((t)-(b)+1)))-1)  &lt;&lt; (b))
DECL|macro|MASKEXPAND
mdefine_line|#define MASKEXPAND(mask) BITMASK(1?mask,0?mask)
multiline_comment|/* Macro to set specific bitfields (mask has to be a macro x:y) ! */
DECL|macro|SetBF
mdefine_line|#define SetBF(mask,value) ((value) &lt;&lt; (0?mask))
DECL|macro|GetBF
mdefine_line|#define GetBF(var,mask) (((unsigned)((var) &amp; MASKEXPAND(mask))) &gt;&gt; (0?mask) )
DECL|macro|MaskAndSetBF
mdefine_line|#define MaskAndSetBF(var,mask,value) (var)=(((var)&amp;(~MASKEXPAND(mask)) &bslash;&n;                                             | SetBF(mask,value)))
DECL|macro|DEVICE_BASE
mdefine_line|#define DEVICE_BASE(device) (0?NV##_##device)
DECL|macro|DEVICE_SIZE
mdefine_line|#define DEVICE_SIZE(device) ((1?NV##_##device) - DEVICE_BASE(device)+1)
multiline_comment|/* This is where we will have to have conditional compilation */
DECL|macro|DEVICE_ACCESS
mdefine_line|#define DEVICE_ACCESS(device,reg) &bslash;&n;  nvCONTROL[(NV_##device##_##reg)/4]
DECL|macro|DEVICE_WRITE
mdefine_line|#define DEVICE_WRITE(device,reg,value) DEVICE_ACCESS(device,reg)=(value)
DECL|macro|DEVICE_READ
mdefine_line|#define DEVICE_READ(device,reg)        DEVICE_ACCESS(device,reg)
DECL|macro|DEVICE_PRINT
mdefine_line|#define DEVICE_PRINT(device,reg) &bslash;&n;  ErrorF(&quot;NV_&quot;#device&quot;_&quot;#reg&quot;=#%08lx&bslash;n&quot;,DEVICE_ACCESS(device,reg))
DECL|macro|DEVICE_DEF
mdefine_line|#define DEVICE_DEF(device,mask,value) &bslash;&n;  SetBF(NV_##device##_##mask,NV_##device##_##mask##_##value)
DECL|macro|DEVICE_VALUE
mdefine_line|#define DEVICE_VALUE(device,mask,value) SetBF(NV_##device##_##mask,value)
DECL|macro|DEVICE_MASK
mdefine_line|#define DEVICE_MASK(device,mask) MASKEXPAND(NV_##device##_##mask)
DECL|macro|PDAC_Write
mdefine_line|#define PDAC_Write(reg,value)           DEVICE_WRITE(PDAC,reg,value)
DECL|macro|PDAC_Read
mdefine_line|#define PDAC_Read(reg)                  DEVICE_READ(PDAC,reg)
DECL|macro|PDAC_Print
mdefine_line|#define PDAC_Print(reg)                 DEVICE_PRINT(PDAC,reg)
DECL|macro|PDAC_Def
mdefine_line|#define PDAC_Def(mask,value)            DEVICE_DEF(PDAC,mask,value)
DECL|macro|PDAC_Val
mdefine_line|#define PDAC_Val(mask,value)            DEVICE_VALUE(PDAC,mask,value)
DECL|macro|PDAC_Mask
mdefine_line|#define PDAC_Mask(mask)                 DEVICE_MASK(PDAC,mask)
DECL|macro|PFB_Write
mdefine_line|#define PFB_Write(reg,value)            DEVICE_WRITE(PFB,reg,value)
DECL|macro|PFB_Read
mdefine_line|#define PFB_Read(reg)                   DEVICE_READ(PFB,reg)
DECL|macro|PFB_Print
mdefine_line|#define PFB_Print(reg)                  DEVICE_PRINT(PFB,reg)
DECL|macro|PFB_Def
mdefine_line|#define PFB_Def(mask,value)             DEVICE_DEF(PFB,mask,value)
DECL|macro|PFB_Val
mdefine_line|#define PFB_Val(mask,value)             DEVICE_VALUE(PFB,mask,value)
DECL|macro|PFB_Mask
mdefine_line|#define PFB_Mask(mask)                  DEVICE_MASK(PFB,mask)
DECL|macro|PRM_Write
mdefine_line|#define PRM_Write(reg,value)            DEVICE_WRITE(PRM,reg,value)
DECL|macro|PRM_Read
mdefine_line|#define PRM_Read(reg)                   DEVICE_READ(PRM,reg)
DECL|macro|PRM_Print
mdefine_line|#define PRM_Print(reg)                  DEVICE_PRINT(PRM,reg)
DECL|macro|PRM_Def
mdefine_line|#define PRM_Def(mask,value)             DEVICE_DEF(PRM,mask,value)
DECL|macro|PRM_Val
mdefine_line|#define PRM_Val(mask,value)             DEVICE_VALUE(PRM,mask,value)
DECL|macro|PRM_Mask
mdefine_line|#define PRM_Mask(mask)                  DEVICE_MASK(PRM,mask)
DECL|macro|PGRAPH_Write
mdefine_line|#define PGRAPH_Write(reg,value)         DEVICE_WRITE(PGRAPH,reg,value)
DECL|macro|PGRAPH_Read
mdefine_line|#define PGRAPH_Read(reg)                DEVICE_READ(PGRAPH,reg)
DECL|macro|PGRAPH_Print
mdefine_line|#define PGRAPH_Print(reg)               DEVICE_PRINT(PGRAPH,reg)
DECL|macro|PGRAPH_Def
mdefine_line|#define PGRAPH_Def(mask,value)          DEVICE_DEF(PGRAPH,mask,value)
DECL|macro|PGRAPH_Val
mdefine_line|#define PGRAPH_Val(mask,value)          DEVICE_VALUE(PGRAPH,mask,value)
DECL|macro|PGRAPH_Mask
mdefine_line|#define PGRAPH_Mask(mask)               DEVICE_MASK(PGRAPH,mask)
DECL|macro|PDMA_Write
mdefine_line|#define PDMA_Write(reg,value)           DEVICE_WRITE(PDMA,reg,value)
DECL|macro|PDMA_Read
mdefine_line|#define PDMA_Read(reg)                  DEVICE_READ(PDMA,reg)
DECL|macro|PDMA_Print
mdefine_line|#define PDMA_Print(reg)                 DEVICE_PRINT(PDMA,reg)
DECL|macro|PDMA_Def
mdefine_line|#define PDMA_Def(mask,value)            DEVICE_DEF(PDMA,mask,value)
DECL|macro|PDMA_Val
mdefine_line|#define PDMA_Val(mask,value)            DEVICE_VALUE(PDMA,mask,value)
DECL|macro|PDMA_Mask
mdefine_line|#define PDMA_Mask(mask)                 DEVICE_MASK(PDMA,mask)
DECL|macro|PTIMER_Write
mdefine_line|#define PTIMER_Write(reg,value)         DEVICE_WRITE(PTIMER,reg,value)
DECL|macro|PTIMER_Read
mdefine_line|#define PTIMER_Read(reg)                DEVICE_READ(PTIMER,reg)
DECL|macro|PTIMER_Print
mdefine_line|#define PTIMER_Print(reg)               DEVICE_PRINT(PTIMER,reg)
DECL|macro|PTIMER_Def
mdefine_line|#define PTIMER_Def(mask,value)          DEVICE_DEF(PTIMER,mask,value)
DECL|macro|PTIMER_Val
mdefine_line|#define PTIMER_Val(mask,value)          DEVICE_VALUE(PTIEMR,mask,value)
DECL|macro|PTIMER_Mask
mdefine_line|#define PTIMER_Mask(mask)               DEVICE_MASK(PTIMER,mask)
DECL|macro|PEXTDEV_Write
mdefine_line|#define PEXTDEV_Write(reg,value)         DEVICE_WRITE(PEXTDEV,reg,value)
DECL|macro|PEXTDEV_Read
mdefine_line|#define PEXTDEV_Read(reg)                DEVICE_READ(PEXTDEV,reg)
DECL|macro|PEXTDEV_Print
mdefine_line|#define PEXTDEV_Print(reg)               DEVICE_PRINT(PEXTDEV,reg)
DECL|macro|PEXTDEV_Def
mdefine_line|#define PEXTDEV_Def(mask,value)          DEVICE_DEF(PEXTDEV,mask,value)
DECL|macro|PEXTDEV_Val
mdefine_line|#define PEXTDEV_Val(mask,value)          DEVICE_VALUE(PEXTDEV,mask,value)
DECL|macro|PEXTDEV_Mask
mdefine_line|#define PEXTDEV_Mask(mask)               DEVICE_MASK(PEXTDEV,mask)
DECL|macro|PFIFO_Write
mdefine_line|#define PFIFO_Write(reg,value)          DEVICE_WRITE(PFIFO,reg,value)
DECL|macro|PFIFO_Read
mdefine_line|#define PFIFO_Read(reg)                 DEVICE_READ(PFIFO,reg)
DECL|macro|PFIFO_Print
mdefine_line|#define PFIFO_Print(reg)                DEVICE_PRINT(PFIFO,reg)
DECL|macro|PFIFO_Def
mdefine_line|#define PFIFO_Def(mask,value)           DEVICE_DEF(PFIFO,mask,value)
DECL|macro|PFIFO_Val
mdefine_line|#define PFIFO_Val(mask,value)           DEVICE_VALUE(PFIFO,mask,value)
DECL|macro|PFIFO_Mask
mdefine_line|#define PFIFO_Mask(mask)                DEVICE_MASK(PFIFO,mask)
DECL|macro|PRAM_Write
mdefine_line|#define PRAM_Write(reg,value)           DEVICE_WRITE(PRAM,reg,value)
DECL|macro|PRAM_Read
mdefine_line|#define PRAM_Read(reg)                  DEVICE_READ(PRAM,reg)
DECL|macro|PRAM_Print
mdefine_line|#define PRAM_Print(reg)                 DEVICE_PRINT(PRAM,reg)
DECL|macro|PRAM_Def
mdefine_line|#define PRAM_Def(mask,value)            DEVICE_DEF(PRAM,mask,value)
DECL|macro|PRAM_Val
mdefine_line|#define PRAM_Val(mask,value)            DEVICE_VALUE(PRAM,mask,value)
DECL|macro|PRAM_Mask
mdefine_line|#define PRAM_Mask(mask)                 DEVICE_MASK(PRAM,mask)
DECL|macro|PRAMFC_Write
mdefine_line|#define PRAMFC_Write(reg,value)         DEVICE_WRITE(PRAMFC,reg,value)
DECL|macro|PRAMFC_Read
mdefine_line|#define PRAMFC_Read(reg)                DEVICE_READ(PRAMFC,reg)
DECL|macro|PRAMFC_Print
mdefine_line|#define PRAMFC_Print(reg)               DEVICE_PRINT(PRAMFC,reg)
DECL|macro|PRAMFC_Def
mdefine_line|#define PRAMFC_Def(mask,value)          DEVICE_DEF(PRAMFC,mask,value)
DECL|macro|PRAMFC_Val
mdefine_line|#define PRAMFC_Val(mask,value)          DEVICE_VALUE(PRAMFC,mask,value)
DECL|macro|PRAMFC_Mask
mdefine_line|#define PRAMFC_Mask(mask)               DEVICE_MASK(PRAMFC,mask)
DECL|macro|PMC_Write
mdefine_line|#define PMC_Write(reg,value)            DEVICE_WRITE(PMC,reg,value)
DECL|macro|PMC_Read
mdefine_line|#define PMC_Read(reg)                   DEVICE_READ(PMC,reg)
DECL|macro|PMC_Print
mdefine_line|#define PMC_Print(reg)                  DEVICE_PRINT(PMC,reg)
DECL|macro|PMC_Def
mdefine_line|#define PMC_Def(mask,value)             DEVICE_DEF(PMC,mask,value)
DECL|macro|PMC_Val
mdefine_line|#define PMC_Val(mask,value)             DEVICE_VALUE(PMC,mask,value)
DECL|macro|PMC_Mask
mdefine_line|#define PMC_Mask(mask)                  DEVICE_MASK(PMC,mask)
DECL|macro|PMC_Write
mdefine_line|#define PMC_Write(reg,value)            DEVICE_WRITE(PMC,reg,value)
DECL|macro|PMC_Read
mdefine_line|#define PMC_Read(reg)                   DEVICE_READ(PMC,reg)
DECL|macro|PMC_Print
mdefine_line|#define PMC_Print(reg)                  DEVICE_PRINT(PMC,reg)
DECL|macro|PMC_Def
mdefine_line|#define PMC_Def(mask,value)             DEVICE_DEF(PMC,mask,value)
DECL|macro|PMC_Val
mdefine_line|#define PMC_Val(mask,value)             DEVICE_VALUE(PMC,mask,value)
DECL|macro|PMC_Mask
mdefine_line|#define PMC_Mask(mask)                  DEVICE_MASK(PMC,mask)
DECL|macro|PBUS_Write
mdefine_line|#define PBUS_Write(reg,value)         DEVICE_WRITE(PBUS,reg,value)
DECL|macro|PBUS_Read
mdefine_line|#define PBUS_Read(reg)                DEVICE_READ(PBUS,reg)
DECL|macro|PBUS_Print
mdefine_line|#define PBUS_Print(reg)               DEVICE_PRINT(PBUS,reg)
DECL|macro|PBUS_Def
mdefine_line|#define PBUS_Def(mask,value)          DEVICE_DEF(PBUS,mask,value)
DECL|macro|PBUS_Val
mdefine_line|#define PBUS_Val(mask,value)          DEVICE_VALUE(PBUS,mask,value)
DECL|macro|PBUS_Mask
mdefine_line|#define PBUS_Mask(mask)               DEVICE_MASK(PBUS,mask)
DECL|macro|PRAMDAC_Write
mdefine_line|#define PRAMDAC_Write(reg,value)         DEVICE_WRITE(PRAMDAC,reg,value)
DECL|macro|PRAMDAC_Read
mdefine_line|#define PRAMDAC_Read(reg)                DEVICE_READ(PRAMDAC,reg)
DECL|macro|PRAMDAC_Print
mdefine_line|#define PRAMDAC_Print(reg)               DEVICE_PRINT(PRAMDAC,reg)
DECL|macro|PRAMDAC_Def
mdefine_line|#define PRAMDAC_Def(mask,value)          DEVICE_DEF(PRAMDAC,mask,value)
DECL|macro|PRAMDAC_Val
mdefine_line|#define PRAMDAC_Val(mask,value)          DEVICE_VALUE(PRAMDAC,mask,value)
DECL|macro|PRAMDAC_Mask
mdefine_line|#define PRAMDAC_Mask(mask)               DEVICE_MASK(PRAMDAC,mask)
DECL|macro|PDAC_ReadExt
mdefine_line|#define PDAC_ReadExt(reg) &bslash;&n;  ((PDAC_Write(INDEX_LO,(NV_PDAC_EXT_##reg) &amp; 0xff)),&bslash;&n;  (PDAC_Write(INDEX_HI,((NV_PDAC_EXT_##reg) &gt;&gt; 8) &amp; 0xff)),&bslash;&n;  (PDAC_Read(INDEX_DATA)))
DECL|macro|PDAC_WriteExt
mdefine_line|#define PDAC_WriteExt(reg,value)&bslash;&n;  ((PDAC_Write(INDEX_LO,(NV_PDAC_EXT_##reg) &amp; 0xff)),&bslash;&n;  (PDAC_Write(INDEX_HI,((NV_PDAC_EXT_##reg) &gt;&gt; 8) &amp; 0xff)),&bslash;&n;  (PDAC_Write(INDEX_DATA,(value))))
DECL|macro|CRTC_Write
mdefine_line|#define CRTC_Write(index,value) outb((index), 0x3d4); outb(value, 0x3d5)
DECL|macro|CRTC_Read
mdefine_line|#define CRTC_Read(index) (outb(index, 0x3d4),inb(0x3d5))
DECL|macro|PCRTC_Write
mdefine_line|#define PCRTC_Write(index,value) CRTC_Write(NV_PCRTC_##index,value)
DECL|macro|PCRTC_Read
mdefine_line|#define PCRTC_Read(index) CRTC_Read(NV_PCRTC_##index)
DECL|macro|PCRTC_Def
mdefine_line|#define PCRTC_Def(mask,value)          DEVICE_DEF(PCRTC,mask,value)
DECL|macro|PCRTC_Val
mdefine_line|#define PCRTC_Val(mask,value)          DEVICE_VALUE(PCRTC,mask,value)
DECL|macro|PCRTC_Mask
mdefine_line|#define PCRTC_Mask(mask)               DEVICE_MASK(PCRTC,mask)
DECL|macro|SR_Write
mdefine_line|#define SR_Write(index,value) outb(0x3c4,(index));outb(0x3c5,value)
DECL|macro|SR_Read
mdefine_line|#define SR_Read(index) (outb(0x3c4,index),inb(0x3c5))
r_extern
r_volatile
r_int
op_star
id|nvCONTROL
suffix:semicolon
DECL|enumerator|NV1
DECL|enumerator|NV3
DECL|enumerator|NV4
DECL|enumerator|NumNVChips
DECL|typedef|NVChipType
r_typedef
r_enum
(brace
id|NV1
comma
id|NV3
comma
id|NV4
comma
id|NumNVChips
)brace
id|NVChipType
suffix:semicolon
id|NVChipType
id|GetChipType
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
eof
