multiline_comment|/*&n; *  linux/drivers/video/kyro/STG4000Reg.h&n; *&n; *  Copyright (C) 2002 STMicroelectronics&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file COPYING in the main directory of this archive&n; * for more details.&n; */
macro_line|#ifndef _STG4000REG_H
DECL|macro|_STG4000REG_H
mdefine_line|#define _STG4000REG_H
DECL|macro|DWFILL
mdefine_line|#define DWFILL unsigned long :32
DECL|macro|WFILL
mdefine_line|#define WFILL unsigned short :16
multiline_comment|/*&n; * Macros that access memory mapped card registers in PCI space&n; * Add an appropraite section for your OS or processor architecture.&n; */
macro_line|#if defined(__KERNEL__)
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|macro|STG_WRITE_REG
mdefine_line|#define STG_WRITE_REG(reg,data) (writel(data,&amp;pSTGReg-&gt;reg))
DECL|macro|STG_READ_REG
mdefine_line|#define STG_READ_REG(reg)      (readl(&amp;pSTGReg-&gt;reg))
macro_line|#else
DECL|macro|STG_WRITE_REG
mdefine_line|#define STG_WRITE_REG(reg,data) (pSTGReg-&gt;reg = data)
DECL|macro|STG_READ_REG
mdefine_line|#define STG_READ_REG(reg)      (pSTGReg-&gt;reg)
macro_line|#endif /* __KERNEL__ */
DECL|macro|SET_BIT
mdefine_line|#define SET_BIT(n) (1&lt;&lt;(n))
DECL|macro|CLEAR_BIT
mdefine_line|#define CLEAR_BIT(n) (tmp &amp;= ~(1&lt;&lt;n))
DECL|macro|CLEAR_BITS_FRM_TO
mdefine_line|#define CLEAR_BITS_FRM_TO(frm, to) &bslash;&n;{&bslash;&n;int i; &bslash;&n;    for(i = frm; i&lt;= to; i++) &bslash;&n;&t;{ &bslash;&n;&t;    tmp &amp;= ~(1&lt;&lt;i); &bslash;&n;&t;} &bslash;&n;}
DECL|macro|CLEAR_BIT_2
mdefine_line|#define CLEAR_BIT_2(n) (usTemp &amp;= ~(1&lt;&lt;n))
DECL|macro|CLEAR_BITS_FRM_TO_2
mdefine_line|#define CLEAR_BITS_FRM_TO_2(frm, to) &bslash;&n;{&bslash;&n;int i; &bslash;&n;    for(i = frm; i&lt;= to; i++) &bslash;&n;&t;{ &bslash;&n;&t;    usTemp &amp;= ~(1&lt;&lt;i); &bslash;&n;&t;} &bslash;&n;}
multiline_comment|/* LUT select */
DECL|enum|_LUT_USES
r_typedef
r_enum
id|_LUT_USES
(brace
DECL|enumerator|NO_LUT
DECL|enumerator|RESERVED
DECL|enumerator|GRAPHICS
DECL|enumerator|OVERLAY
id|NO_LUT
op_assign
l_int|0
comma
id|RESERVED
comma
id|GRAPHICS
comma
id|OVERLAY
DECL|typedef|LUT_USES
)brace
id|LUT_USES
suffix:semicolon
multiline_comment|/* Primary surface pixel format select */
DECL|enum|_PIXEL_FORMAT
r_typedef
r_enum
id|_PIXEL_FORMAT
(brace
DECL|enumerator|_8BPP
DECL|enumerator|_15BPP
DECL|enumerator|_16BPP
DECL|enumerator|_24BPP
DECL|enumerator|_32BPP
id|_8BPP
op_assign
l_int|0
comma
id|_15BPP
comma
id|_16BPP
comma
id|_24BPP
comma
id|_32BPP
DECL|typedef|PIXEL_FORMAT
)brace
id|PIXEL_FORMAT
suffix:semicolon
multiline_comment|/* Overlay blending mode select */
DECL|enum|_BLEND_MODE
r_typedef
r_enum
id|_BLEND_MODE
(brace
DECL|enumerator|GRAPHICS_MODE
DECL|enumerator|COLOR_KEY
DECL|enumerator|PER_PIXEL_ALPHA
DECL|enumerator|GLOBAL_ALPHA
id|GRAPHICS_MODE
op_assign
l_int|0
comma
id|COLOR_KEY
comma
id|PER_PIXEL_ALPHA
comma
id|GLOBAL_ALPHA
comma
DECL|enumerator|CK_PIXEL_ALPHA
DECL|enumerator|CK_GLOBAL_ALPHA
id|CK_PIXEL_ALPHA
comma
id|CK_GLOBAL_ALPHA
DECL|typedef|OVRL_BLEND_MODE
)brace
id|OVRL_BLEND_MODE
suffix:semicolon
multiline_comment|/* Overlay Pixel format select */
DECL|enum|_OVRL_PIX_FORMAT
r_typedef
r_enum
id|_OVRL_PIX_FORMAT
(brace
DECL|enumerator|UYVY
DECL|enumerator|VYUY
DECL|enumerator|YUYV
DECL|enumerator|YVYU
id|UYVY
comma
id|VYUY
comma
id|YUYV
comma
id|YVYU
DECL|typedef|OVRL_PIX_FORMAT
)brace
id|OVRL_PIX_FORMAT
suffix:semicolon
multiline_comment|/* Register Table */
r_typedef
r_struct
(brace
multiline_comment|/* 0h  */
DECL|member|Thread0Enable
r_volatile
r_int
r_int
id|Thread0Enable
suffix:semicolon
multiline_comment|/* 0x0000 */
DECL|member|Thread1Enable
r_volatile
r_int
r_int
id|Thread1Enable
suffix:semicolon
multiline_comment|/* 0x0004 */
DECL|member|Thread0Recover
r_volatile
r_int
r_int
id|Thread0Recover
suffix:semicolon
multiline_comment|/* 0x0008 */
DECL|member|Thread1Recover
r_volatile
r_int
r_int
id|Thread1Recover
suffix:semicolon
multiline_comment|/* 0x000C */
DECL|member|Thread0Step
r_volatile
r_int
r_int
id|Thread0Step
suffix:semicolon
multiline_comment|/* 0x0010 */
DECL|member|Thread1Step
r_volatile
r_int
r_int
id|Thread1Step
suffix:semicolon
multiline_comment|/* 0x0014 */
DECL|member|VideoInStatus
r_volatile
r_int
r_int
id|VideoInStatus
suffix:semicolon
multiline_comment|/* 0x0018 */
DECL|member|Core2InSignStart
r_volatile
r_int
r_int
id|Core2InSignStart
suffix:semicolon
multiline_comment|/* 0x001C */
DECL|member|Core1ResetVector
r_volatile
r_int
r_int
id|Core1ResetVector
suffix:semicolon
multiline_comment|/* 0x0020 */
DECL|member|Core1ROMOffset
r_volatile
r_int
r_int
id|Core1ROMOffset
suffix:semicolon
multiline_comment|/* 0x0024 */
DECL|member|Core1ArbiterPriority
r_volatile
r_int
r_int
id|Core1ArbiterPriority
suffix:semicolon
multiline_comment|/* 0x0028 */
DECL|member|VideoInControl
r_volatile
r_int
r_int
id|VideoInControl
suffix:semicolon
multiline_comment|/* 0x002C */
DECL|member|VideoInReg0CtrlA
r_volatile
r_int
r_int
id|VideoInReg0CtrlA
suffix:semicolon
multiline_comment|/* 0x0030 */
DECL|member|VideoInReg0CtrlB
r_volatile
r_int
r_int
id|VideoInReg0CtrlB
suffix:semicolon
multiline_comment|/* 0x0034 */
DECL|member|VideoInReg1CtrlA
r_volatile
r_int
r_int
id|VideoInReg1CtrlA
suffix:semicolon
multiline_comment|/* 0x0038 */
DECL|member|VideoInReg1CtrlB
r_volatile
r_int
r_int
id|VideoInReg1CtrlB
suffix:semicolon
multiline_comment|/* 0x003C */
DECL|member|Thread0Kicker
r_volatile
r_int
r_int
id|Thread0Kicker
suffix:semicolon
multiline_comment|/* 0x0040 */
DECL|member|Core2InputSign
r_volatile
r_int
r_int
id|Core2InputSign
suffix:semicolon
multiline_comment|/* 0x0044 */
DECL|member|Thread0ProgCtr
r_volatile
r_int
r_int
id|Thread0ProgCtr
suffix:semicolon
multiline_comment|/* 0x0048 */
DECL|member|Thread1ProgCtr
r_volatile
r_int
r_int
id|Thread1ProgCtr
suffix:semicolon
multiline_comment|/* 0x004C */
DECL|member|Thread1Kicker
r_volatile
r_int
r_int
id|Thread1Kicker
suffix:semicolon
multiline_comment|/* 0x0050 */
DECL|member|GPRegister1
r_volatile
r_int
r_int
id|GPRegister1
suffix:semicolon
multiline_comment|/* 0x0054 */
DECL|member|GPRegister2
r_volatile
r_int
r_int
id|GPRegister2
suffix:semicolon
multiline_comment|/* 0x0058 */
DECL|member|GPRegister3
r_volatile
r_int
r_int
id|GPRegister3
suffix:semicolon
multiline_comment|/* 0x005C */
DECL|member|GPRegister4
r_volatile
r_int
r_int
id|GPRegister4
suffix:semicolon
multiline_comment|/* 0x0060 */
DECL|member|SerialIntA
r_volatile
r_int
r_int
id|SerialIntA
suffix:semicolon
multiline_comment|/* 0x0064 */
DECL|member|Fill0
r_volatile
r_int
r_int
id|Fill0
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* GAP 0x0068 - 0x007C */
DECL|member|SoftwareReset
r_volatile
r_int
r_int
id|SoftwareReset
suffix:semicolon
multiline_comment|/* 0x0080 */
DECL|member|SerialIntB
r_volatile
r_int
r_int
id|SerialIntB
suffix:semicolon
multiline_comment|/* 0x0084 */
DECL|member|Fill1
r_volatile
r_int
r_int
id|Fill1
(braket
l_int|37
)braket
suffix:semicolon
multiline_comment|/* GAP 0x0088 - 0x011C */
DECL|member|ROMELQV
r_volatile
r_int
r_int
id|ROMELQV
suffix:semicolon
multiline_comment|/* 0x011C */
DECL|member|WLWH
r_volatile
r_int
r_int
id|WLWH
suffix:semicolon
multiline_comment|/* 0x0120 */
DECL|member|ROMELWL
r_volatile
r_int
r_int
id|ROMELWL
suffix:semicolon
multiline_comment|/* 0x0124 */
DECL|member|dwFill_1
r_volatile
r_int
r_int
id|dwFill_1
suffix:semicolon
multiline_comment|/* GAP 0x0128 */
DECL|member|IntStatus
r_volatile
r_int
r_int
id|IntStatus
suffix:semicolon
multiline_comment|/* 0x012C */
DECL|member|IntMask
r_volatile
r_int
r_int
id|IntMask
suffix:semicolon
multiline_comment|/* 0x0130 */
DECL|member|IntClear
r_volatile
r_int
r_int
id|IntClear
suffix:semicolon
multiline_comment|/* 0x0134 */
DECL|member|Fill2
r_volatile
r_int
r_int
id|Fill2
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* GAP 0x0138 - 0x014C */
DECL|member|ROMGPIOA
r_volatile
r_int
r_int
id|ROMGPIOA
suffix:semicolon
multiline_comment|/* 0x0150 */
DECL|member|ROMGPIOB
r_volatile
r_int
r_int
id|ROMGPIOB
suffix:semicolon
multiline_comment|/* 0x0154 */
DECL|member|ROMGPIOC
r_volatile
r_int
r_int
id|ROMGPIOC
suffix:semicolon
multiline_comment|/* 0x0158 */
DECL|member|ROMGPIOD
r_volatile
r_int
r_int
id|ROMGPIOD
suffix:semicolon
multiline_comment|/* 0x015C */
DECL|member|Fill3
r_volatile
r_int
r_int
id|Fill3
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* GAP 0x0160 - 0x0168 */
DECL|member|AGPIntID
r_volatile
r_int
r_int
id|AGPIntID
suffix:semicolon
multiline_comment|/* 0x0168 */
DECL|member|AGPIntClassCode
r_volatile
r_int
r_int
id|AGPIntClassCode
suffix:semicolon
multiline_comment|/* 0x016C */
DECL|member|AGPIntBIST
r_volatile
r_int
r_int
id|AGPIntBIST
suffix:semicolon
multiline_comment|/* 0x0170 */
DECL|member|AGPIntSSID
r_volatile
r_int
r_int
id|AGPIntSSID
suffix:semicolon
multiline_comment|/* 0x0174 */
DECL|member|AGPIntPMCSR
r_volatile
r_int
r_int
id|AGPIntPMCSR
suffix:semicolon
multiline_comment|/* 0x0178 */
DECL|member|VGAFrameBufBase
r_volatile
r_int
r_int
id|VGAFrameBufBase
suffix:semicolon
multiline_comment|/* 0x017C */
DECL|member|VGANotify
r_volatile
r_int
r_int
id|VGANotify
suffix:semicolon
multiline_comment|/* 0x0180 */
DECL|member|DACPLLMode
r_volatile
r_int
r_int
id|DACPLLMode
suffix:semicolon
multiline_comment|/* 0x0184 */
DECL|member|Core1VideoClockDiv
r_volatile
r_int
r_int
id|Core1VideoClockDiv
suffix:semicolon
multiline_comment|/* 0x0188 */
DECL|member|AGPIntStat
r_volatile
r_int
r_int
id|AGPIntStat
suffix:semicolon
multiline_comment|/* 0x018C */
multiline_comment|/*&n;&t;   volatile unsigned long Fill4[0x0400/4 - 0x0190/4]; //GAP 0x0190 - 0x0400&n;&t;   volatile unsigned long Fill5[0x05FC/4 - 0x0400/4]; //GAP 0x0400 - 0x05FC Fog Table&n;&t;   volatile unsigned long Fill6[0x0604/4 - 0x0600/4]; //GAP 0x0600 - 0x0604&n;&t;   volatile unsigned long Fill7[0x0680/4 - 0x0608/4]; //GAP 0x0608 - 0x0680&n;&t;   volatile unsigned long Fill8[0x07FC/4 - 0x0684/4]; //GAP 0x0684 - 0x07FC&n;&t; */
DECL|member|Fill4
r_volatile
r_int
r_int
id|Fill4
(braket
l_int|412
)braket
suffix:semicolon
multiline_comment|/* 0x0190 - 0x07FC */
DECL|member|TACtrlStreamBase
r_volatile
r_int
r_int
id|TACtrlStreamBase
suffix:semicolon
multiline_comment|/* 0x0800 */
DECL|member|TAObjDataBase
r_volatile
r_int
r_int
id|TAObjDataBase
suffix:semicolon
multiline_comment|/* 0x0804 */
DECL|member|TAPtrDataBase
r_volatile
r_int
r_int
id|TAPtrDataBase
suffix:semicolon
multiline_comment|/* 0x0808 */
DECL|member|TARegionDataBase
r_volatile
r_int
r_int
id|TARegionDataBase
suffix:semicolon
multiline_comment|/* 0x080C */
DECL|member|TATailPtrBase
r_volatile
r_int
r_int
id|TATailPtrBase
suffix:semicolon
multiline_comment|/* 0x0810 */
DECL|member|TAPtrRegionSize
r_volatile
r_int
r_int
id|TAPtrRegionSize
suffix:semicolon
multiline_comment|/* 0x0814 */
DECL|member|TAConfiguration
r_volatile
r_int
r_int
id|TAConfiguration
suffix:semicolon
multiline_comment|/* 0x0818 */
DECL|member|TAObjDataStartAddr
r_volatile
r_int
r_int
id|TAObjDataStartAddr
suffix:semicolon
multiline_comment|/* 0x081C */
DECL|member|TAObjDataEndAddr
r_volatile
r_int
r_int
id|TAObjDataEndAddr
suffix:semicolon
multiline_comment|/* 0x0820 */
DECL|member|TAXScreenClip
r_volatile
r_int
r_int
id|TAXScreenClip
suffix:semicolon
multiline_comment|/* 0x0824 */
DECL|member|TAYScreenClip
r_volatile
r_int
r_int
id|TAYScreenClip
suffix:semicolon
multiline_comment|/* 0x0828 */
DECL|member|TARHWClamp
r_volatile
r_int
r_int
id|TARHWClamp
suffix:semicolon
multiline_comment|/* 0x082C */
DECL|member|TARHWCompare
r_volatile
r_int
r_int
id|TARHWCompare
suffix:semicolon
multiline_comment|/* 0x0830 */
DECL|member|TAStart
r_volatile
r_int
r_int
id|TAStart
suffix:semicolon
multiline_comment|/* 0x0834 */
DECL|member|TAObjReStart
r_volatile
r_int
r_int
id|TAObjReStart
suffix:semicolon
multiline_comment|/* 0x0838 */
DECL|member|TAPtrReStart
r_volatile
r_int
r_int
id|TAPtrReStart
suffix:semicolon
multiline_comment|/* 0x083C */
DECL|member|TAStatus1
r_volatile
r_int
r_int
id|TAStatus1
suffix:semicolon
multiline_comment|/* 0x0840 */
DECL|member|TAStatus2
r_volatile
r_int
r_int
id|TAStatus2
suffix:semicolon
multiline_comment|/* 0x0844 */
DECL|member|TAIntStatus
r_volatile
r_int
r_int
id|TAIntStatus
suffix:semicolon
multiline_comment|/* 0x0848 */
DECL|member|TAIntMask
r_volatile
r_int
r_int
id|TAIntMask
suffix:semicolon
multiline_comment|/* 0x084C */
DECL|member|Fill5
r_volatile
r_int
r_int
id|Fill5
(braket
l_int|235
)braket
suffix:semicolon
multiline_comment|/* GAP 0x0850 - 0x0BF8 */
DECL|member|TextureAddrThresh
r_volatile
r_int
r_int
id|TextureAddrThresh
suffix:semicolon
multiline_comment|/* 0x0BFC */
DECL|member|Core1Translation
r_volatile
r_int
r_int
id|Core1Translation
suffix:semicolon
multiline_comment|/* 0x0C00 */
DECL|member|TextureAddrReMap
r_volatile
r_int
r_int
id|TextureAddrReMap
suffix:semicolon
multiline_comment|/* 0x0C04 */
DECL|member|RenderOutAGPRemap
r_volatile
r_int
r_int
id|RenderOutAGPRemap
suffix:semicolon
multiline_comment|/* 0x0C08 */
DECL|member|_3DRegionReadTrans
r_volatile
r_int
r_int
id|_3DRegionReadTrans
suffix:semicolon
multiline_comment|/* 0x0C0C */
DECL|member|_3DPtrReadTrans
r_volatile
r_int
r_int
id|_3DPtrReadTrans
suffix:semicolon
multiline_comment|/* 0x0C10 */
DECL|member|_3DParamReadTrans
r_volatile
r_int
r_int
id|_3DParamReadTrans
suffix:semicolon
multiline_comment|/* 0x0C14 */
DECL|member|_3DRegionReadThresh
r_volatile
r_int
r_int
id|_3DRegionReadThresh
suffix:semicolon
multiline_comment|/* 0x0C18 */
DECL|member|_3DPtrReadThresh
r_volatile
r_int
r_int
id|_3DPtrReadThresh
suffix:semicolon
multiline_comment|/* 0x0C1C */
DECL|member|_3DParamReadThresh
r_volatile
r_int
r_int
id|_3DParamReadThresh
suffix:semicolon
multiline_comment|/* 0x0C20 */
DECL|member|_3DRegionReadAGPRemap
r_volatile
r_int
r_int
id|_3DRegionReadAGPRemap
suffix:semicolon
multiline_comment|/* 0x0C24 */
DECL|member|_3DPtrReadAGPRemap
r_volatile
r_int
r_int
id|_3DPtrReadAGPRemap
suffix:semicolon
multiline_comment|/* 0x0C28 */
DECL|member|_3DParamReadAGPRemap
r_volatile
r_int
r_int
id|_3DParamReadAGPRemap
suffix:semicolon
multiline_comment|/* 0x0C2C */
DECL|member|ZBufferAGPRemap
r_volatile
r_int
r_int
id|ZBufferAGPRemap
suffix:semicolon
multiline_comment|/* 0x0C30 */
DECL|member|TAIndexAGPRemap
r_volatile
r_int
r_int
id|TAIndexAGPRemap
suffix:semicolon
multiline_comment|/* 0x0C34 */
DECL|member|TAVertexAGPRemap
r_volatile
r_int
r_int
id|TAVertexAGPRemap
suffix:semicolon
multiline_comment|/* 0x0C38 */
DECL|member|TAUVAddrTrans
r_volatile
r_int
r_int
id|TAUVAddrTrans
suffix:semicolon
multiline_comment|/* 0x0C3C */
DECL|member|TATailPtrCacheTrans
r_volatile
r_int
r_int
id|TATailPtrCacheTrans
suffix:semicolon
multiline_comment|/* 0x0C40 */
DECL|member|TAParamWriteTrans
r_volatile
r_int
r_int
id|TAParamWriteTrans
suffix:semicolon
multiline_comment|/* 0x0C44 */
DECL|member|TAPtrWriteTrans
r_volatile
r_int
r_int
id|TAPtrWriteTrans
suffix:semicolon
multiline_comment|/* 0x0C48 */
DECL|member|TAParamWriteThresh
r_volatile
r_int
r_int
id|TAParamWriteThresh
suffix:semicolon
multiline_comment|/* 0x0C4C */
DECL|member|TAPtrWriteThresh
r_volatile
r_int
r_int
id|TAPtrWriteThresh
suffix:semicolon
multiline_comment|/* 0x0C50 */
DECL|member|TATailPtrCacheAGPRe
r_volatile
r_int
r_int
id|TATailPtrCacheAGPRe
suffix:semicolon
multiline_comment|/* 0x0C54 */
DECL|member|TAParamWriteAGPRe
r_volatile
r_int
r_int
id|TAParamWriteAGPRe
suffix:semicolon
multiline_comment|/* 0x0C58 */
DECL|member|TAPtrWriteAGPRe
r_volatile
r_int
r_int
id|TAPtrWriteAGPRe
suffix:semicolon
multiline_comment|/* 0x0C5C */
DECL|member|SDRAMArbiterConf
r_volatile
r_int
r_int
id|SDRAMArbiterConf
suffix:semicolon
multiline_comment|/* 0x0C60 */
DECL|member|SDRAMConf0
r_volatile
r_int
r_int
id|SDRAMConf0
suffix:semicolon
multiline_comment|/* 0x0C64 */
DECL|member|SDRAMConf1
r_volatile
r_int
r_int
id|SDRAMConf1
suffix:semicolon
multiline_comment|/* 0x0C68 */
DECL|member|SDRAMConf2
r_volatile
r_int
r_int
id|SDRAMConf2
suffix:semicolon
multiline_comment|/* 0x0C6C */
DECL|member|SDRAMRefresh
r_volatile
r_int
r_int
id|SDRAMRefresh
suffix:semicolon
multiline_comment|/* 0x0C70 */
DECL|member|SDRAMPowerStat
r_volatile
r_int
r_int
id|SDRAMPowerStat
suffix:semicolon
multiline_comment|/* 0x0C74 */
DECL|member|Fill6
r_volatile
r_int
r_int
id|Fill6
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* GAP 0x0C78 - 0x0C7C */
DECL|member|RAMBistData
r_volatile
r_int
r_int
id|RAMBistData
suffix:semicolon
multiline_comment|/* 0x0C80 */
DECL|member|RAMBistCtrl
r_volatile
r_int
r_int
id|RAMBistCtrl
suffix:semicolon
multiline_comment|/* 0x0C84 */
DECL|member|FIFOBistKey
r_volatile
r_int
r_int
id|FIFOBistKey
suffix:semicolon
multiline_comment|/* 0x0C88 */
DECL|member|RAMBistResult
r_volatile
r_int
r_int
id|RAMBistResult
suffix:semicolon
multiline_comment|/* 0x0C8C */
DECL|member|FIFOBistResult
r_volatile
r_int
r_int
id|FIFOBistResult
suffix:semicolon
multiline_comment|/* 0x0C90 */
multiline_comment|/*&n;&t;   volatile unsigned long Fill11[0x0CBC/4 - 0x0C94/4]; //GAP 0x0C94 - 0x0CBC&n;&t;   volatile unsigned long Fill12[0x0CD0/4 - 0x0CC0/4]; //GAP 0x0CC0 - 0x0CD0 3DRegisters&n;&t; */
DECL|member|Fill7
r_volatile
r_int
r_int
id|Fill7
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* 0x0c94 - 0x0cd0 */
DECL|member|SDRAMAddrSign
r_volatile
r_int
r_int
id|SDRAMAddrSign
suffix:semicolon
multiline_comment|/* 0x0CD4 */
DECL|member|SDRAMDataSign
r_volatile
r_int
r_int
id|SDRAMDataSign
suffix:semicolon
multiline_comment|/* 0x0CD8 */
DECL|member|SDRAMSignConf
r_volatile
r_int
r_int
id|SDRAMSignConf
suffix:semicolon
multiline_comment|/* 0x0CDC */
multiline_comment|/* DWFILL; //GAP 0x0CE0 */
DECL|member|dwFill_2
r_volatile
r_int
r_int
id|dwFill_2
suffix:semicolon
DECL|member|ISPSignature
r_volatile
r_int
r_int
id|ISPSignature
suffix:semicolon
multiline_comment|/* 0x0CE4 */
DECL|member|Fill8
r_volatile
r_int
r_int
id|Fill8
(braket
l_int|454
)braket
suffix:semicolon
multiline_comment|/*GAP 0x0CE8 - 0x13FC */
DECL|member|DACPrimAddress
r_volatile
r_int
r_int
id|DACPrimAddress
suffix:semicolon
multiline_comment|/* 0x1400 */
DECL|member|DACPrimSize
r_volatile
r_int
r_int
id|DACPrimSize
suffix:semicolon
multiline_comment|/* 0x1404 */
DECL|member|DACCursorAddr
r_volatile
r_int
r_int
id|DACCursorAddr
suffix:semicolon
multiline_comment|/* 0x1408 */
DECL|member|DACCursorCtrl
r_volatile
r_int
r_int
id|DACCursorCtrl
suffix:semicolon
multiline_comment|/* 0x140C */
DECL|member|DACOverlayAddr
r_volatile
r_int
r_int
id|DACOverlayAddr
suffix:semicolon
multiline_comment|/* 0x1410 */
DECL|member|DACOverlayUAddr
r_volatile
r_int
r_int
id|DACOverlayUAddr
suffix:semicolon
multiline_comment|/* 0x1414 */
DECL|member|DACOverlayVAddr
r_volatile
r_int
r_int
id|DACOverlayVAddr
suffix:semicolon
multiline_comment|/* 0x1418 */
DECL|member|DACOverlaySize
r_volatile
r_int
r_int
id|DACOverlaySize
suffix:semicolon
multiline_comment|/* 0x141C */
DECL|member|DACOverlayVtDec
r_volatile
r_int
r_int
id|DACOverlayVtDec
suffix:semicolon
multiline_comment|/* 0x1420 */
DECL|member|Fill9
r_volatile
r_int
r_int
id|Fill9
(braket
l_int|9
)braket
suffix:semicolon
multiline_comment|/* GAP 0x1424 - 0x1444 */
DECL|member|DACVerticalScal
r_volatile
r_int
r_int
id|DACVerticalScal
suffix:semicolon
multiline_comment|/* 0x1448 */
DECL|member|DACPixelFormat
r_volatile
r_int
r_int
id|DACPixelFormat
suffix:semicolon
multiline_comment|/* 0x144C */
DECL|member|DACHorizontalScal
r_volatile
r_int
r_int
id|DACHorizontalScal
suffix:semicolon
multiline_comment|/* 0x1450 */
DECL|member|DACVidWinStart
r_volatile
r_int
r_int
id|DACVidWinStart
suffix:semicolon
multiline_comment|/* 0x1454 */
DECL|member|DACVidWinEnd
r_volatile
r_int
r_int
id|DACVidWinEnd
suffix:semicolon
multiline_comment|/* 0x1458 */
DECL|member|DACBlendCtrl
r_volatile
r_int
r_int
id|DACBlendCtrl
suffix:semicolon
multiline_comment|/* 0x145C */
DECL|member|DACHorTim1
r_volatile
r_int
r_int
id|DACHorTim1
suffix:semicolon
multiline_comment|/* 0x1460 */
DECL|member|DACHorTim2
r_volatile
r_int
r_int
id|DACHorTim2
suffix:semicolon
multiline_comment|/* 0x1464 */
DECL|member|DACHorTim3
r_volatile
r_int
r_int
id|DACHorTim3
suffix:semicolon
multiline_comment|/* 0x1468 */
DECL|member|DACVerTim1
r_volatile
r_int
r_int
id|DACVerTim1
suffix:semicolon
multiline_comment|/* 0x146C */
DECL|member|DACVerTim2
r_volatile
r_int
r_int
id|DACVerTim2
suffix:semicolon
multiline_comment|/* 0x1470 */
DECL|member|DACVerTim3
r_volatile
r_int
r_int
id|DACVerTim3
suffix:semicolon
multiline_comment|/* 0x1474 */
DECL|member|DACBorderColor
r_volatile
r_int
r_int
id|DACBorderColor
suffix:semicolon
multiline_comment|/* 0x1478 */
DECL|member|DACSyncCtrl
r_volatile
r_int
r_int
id|DACSyncCtrl
suffix:semicolon
multiline_comment|/* 0x147C */
DECL|member|DACStreamCtrl
r_volatile
r_int
r_int
id|DACStreamCtrl
suffix:semicolon
multiline_comment|/* 0x1480 */
DECL|member|DACLUTAddress
r_volatile
r_int
r_int
id|DACLUTAddress
suffix:semicolon
multiline_comment|/* 0x1484 */
DECL|member|DACLUTData
r_volatile
r_int
r_int
id|DACLUTData
suffix:semicolon
multiline_comment|/* 0x1488 */
DECL|member|DACBurstCtrl
r_volatile
r_int
r_int
id|DACBurstCtrl
suffix:semicolon
multiline_comment|/* 0x148C */
DECL|member|DACCrcTrigger
r_volatile
r_int
r_int
id|DACCrcTrigger
suffix:semicolon
multiline_comment|/* 0x1490 */
DECL|member|DACCrcDone
r_volatile
r_int
r_int
id|DACCrcDone
suffix:semicolon
multiline_comment|/* 0x1494 */
DECL|member|DACCrcResult1
r_volatile
r_int
r_int
id|DACCrcResult1
suffix:semicolon
multiline_comment|/* 0x1498 */
DECL|member|DACCrcResult2
r_volatile
r_int
r_int
id|DACCrcResult2
suffix:semicolon
multiline_comment|/* 0x149C */
DECL|member|DACLinecount
r_volatile
r_int
r_int
id|DACLinecount
suffix:semicolon
multiline_comment|/* 0x14A0 */
DECL|member|Fill10
r_volatile
r_int
r_int
id|Fill10
(braket
l_int|151
)braket
suffix:semicolon
multiline_comment|/*GAP 0x14A4 - 0x16FC */
DECL|member|DigVidPortCtrl
r_volatile
r_int
r_int
id|DigVidPortCtrl
suffix:semicolon
multiline_comment|/* 0x1700 */
DECL|member|DigVidPortStat
r_volatile
r_int
r_int
id|DigVidPortStat
suffix:semicolon
multiline_comment|/* 0x1704 */
multiline_comment|/*&n;&t;   volatile unsigned long Fill11[0x1FFC/4 - 0x1708/4]; //GAP 0x1708 - 0x1FFC&n;&t;   volatile unsigned long Fill17[0x3000/4 - 0x2FFC/4]; //GAP 0x2000 - 0x2FFC ALUT&n;&t; */
DECL|member|Fill11
r_volatile
r_int
r_int
id|Fill11
(braket
l_int|1598
)braket
suffix:semicolon
multiline_comment|/* DWFILL; //GAP 0x3000          ALUT 256MB offset */
DECL|member|Fill_3
r_volatile
r_int
r_int
id|Fill_3
suffix:semicolon
DECL|typedef|STG4000REG
)brace
id|STG4000REG
suffix:semicolon
macro_line|#endif /* _STG4000REG_H */
eof
