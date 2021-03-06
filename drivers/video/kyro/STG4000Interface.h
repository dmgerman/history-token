multiline_comment|/*&n; *  linux/drivers/video/kyro/STG4000Interface.h&n; *&n; *  Copyright (C) 2002 STMicroelectronics&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file COPYING in the main directory of this archive&n; * for more details.&n; */
macro_line|#ifndef _STG4000INTERFACE_H
DECL|macro|_STG4000INTERFACE_H
mdefine_line|#define _STG4000INTERFACE_H
r_struct
id|pci_dev
suffix:semicolon
multiline_comment|/*&n; * Ramdac Setup&n; */
r_extern
r_int
id|InitialiseRamdac
c_func
(paren
r_volatile
id|STG4000REG
id|__iomem
op_star
id|pSTGReg
comma
id|u32
id|displayDepth
comma
id|u32
id|displayWidth
comma
id|u32
id|displayHeight
comma
id|s32
id|HSyncPolarity
comma
id|s32
id|VSyncPolarity
comma
id|u32
op_star
id|pixelClock
)paren
suffix:semicolon
r_extern
r_void
id|DisableRamdacOutput
c_func
(paren
r_volatile
id|STG4000REG
id|__iomem
op_star
id|pSTGReg
)paren
suffix:semicolon
r_extern
r_void
id|EnableRamdacOutput
c_func
(paren
r_volatile
id|STG4000REG
id|__iomem
op_star
id|pSTGReg
)paren
suffix:semicolon
multiline_comment|/*&n; * Timing generator setup&n; */
r_extern
r_void
id|DisableVGA
c_func
(paren
r_volatile
id|STG4000REG
id|__iomem
op_star
id|pSTGReg
)paren
suffix:semicolon
r_extern
r_void
id|StopVTG
c_func
(paren
r_volatile
id|STG4000REG
id|__iomem
op_star
id|pSTGReg
)paren
suffix:semicolon
r_extern
r_void
id|StartVTG
c_func
(paren
r_volatile
id|STG4000REG
id|__iomem
op_star
id|pSTGReg
)paren
suffix:semicolon
r_extern
r_void
id|SetupVTG
c_func
(paren
r_volatile
id|STG4000REG
id|__iomem
op_star
id|pSTGReg
comma
r_const
r_struct
id|kyrofb_info
op_star
id|pTiming
)paren
suffix:semicolon
r_extern
id|u32
id|ProgramClock
c_func
(paren
id|u32
id|refClock
comma
id|u32
id|coreClock
comma
id|u32
op_star
id|FOut
comma
id|u32
op_star
id|ROut
comma
id|u32
op_star
id|POut
)paren
suffix:semicolon
r_extern
r_int
id|SetCoreClockPLL
c_func
(paren
r_volatile
id|STG4000REG
id|__iomem
op_star
id|pSTGReg
comma
r_struct
id|pci_dev
op_star
id|pDev
)paren
suffix:semicolon
multiline_comment|/*&n; * Overlay setup&n; */
r_extern
r_void
id|ResetOverlayRegisters
c_func
(paren
r_volatile
id|STG4000REG
id|__iomem
op_star
id|pSTGReg
)paren
suffix:semicolon
r_extern
r_int
id|CreateOverlaySurface
c_func
(paren
r_volatile
id|STG4000REG
id|__iomem
op_star
id|pSTGReg
comma
id|u32
id|ulWidth
comma
id|u32
id|ulHeight
comma
r_int
id|bLinear
comma
id|u32
id|ulOverlayOffset
comma
id|u32
op_star
id|retStride
comma
id|u32
op_star
id|retUVStride
)paren
suffix:semicolon
r_extern
r_int
id|SetOverlayBlendMode
c_func
(paren
r_volatile
id|STG4000REG
id|__iomem
op_star
id|pSTGReg
comma
id|OVRL_BLEND_MODE
id|mode
comma
id|u32
id|ulAlpha
comma
id|u32
id|ulColorKey
)paren
suffix:semicolon
r_extern
r_int
id|SetOverlayViewPort
c_func
(paren
r_volatile
id|STG4000REG
id|__iomem
op_star
id|pSTGReg
comma
id|u32
id|left
comma
id|u32
id|top
comma
id|u32
id|right
comma
id|u32
id|bottom
)paren
suffix:semicolon
r_extern
r_void
id|EnableOverlayPlane
c_func
(paren
r_volatile
id|STG4000REG
id|__iomem
op_star
id|pSTGReg
)paren
suffix:semicolon
macro_line|#endif /* _STG4000INTERFACE_H */
eof
