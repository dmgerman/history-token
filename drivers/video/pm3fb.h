multiline_comment|/*&n; *  linux/drivers/video/pm3fb.h -- 3DLabs Permedia3 frame buffer device&n; *  &n; *  Copyright (C) 2001 Romain Dolbeau &lt;dolbeau@irisa.fr&gt;&n; *  Copyright (C) 2001 Sven Luther, &lt;luther@dpt-info.u-strasbg.fr&gt;&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License. See the file COPYING in the main directory of this archive for&n; *  more details.&n; *&n; *  $Header: /cvsroot/linux/drivers/video/pm3fb.h,v 1.1 2002/02/25 19:11:06 marcelo Exp $&n; *&n; */
macro_line|#ifndef PM3FB_H
DECL|macro|PM3FB_H
mdefine_line|#define PM3FB_H
multiline_comment|/**********************************************&n;*  GLINT Permedia3 Control Status registers   *&n;***********************************************/
multiline_comment|/* Control Status Registers */
DECL|macro|PM3ResetStatus
mdefine_line|#define PM3ResetStatus&t;&t;&t;&t;&t;&t;0x0000
DECL|macro|PM3IntEnable
mdefine_line|#define PM3IntEnable&t;&t;&t;&t;&t;&t;0x0008
DECL|macro|PM3IntFlags
mdefine_line|#define PM3IntFlags&t;&t;&t;&t;&t;&t;0x0010
DECL|macro|PM3InFIFOSpace
mdefine_line|#define PM3InFIFOSpace&t;&t;&t;&t;&t;&t;0x0018
DECL|macro|PM3OutFIFOWords
mdefine_line|#define PM3OutFIFOWords&t;&t;&t;&t;&t;&t;0x0020
DECL|macro|PM3DMAAddress
mdefine_line|#define PM3DMAAddress&t;&t;&t;&t;&t;&t;0x0028
DECL|macro|PM3DMACount
mdefine_line|#define PM3DMACount&t;&t;&t;&t;&t;&t;0x0030
DECL|macro|PM3ErrorFlags
mdefine_line|#define PM3ErrorFlags&t;&t;&t;&t;&t;&t;0x0038
DECL|macro|PM3VClkCtl
mdefine_line|#define PM3VClkCtl&t;&t;&t;&t;&t;&t;0x0040
DECL|macro|PM3TestRegister
mdefine_line|#define PM3TestRegister&t;&t;&t;&t;&t;&t;0x0048
DECL|macro|PM3Aperture0
mdefine_line|#define PM3Aperture0&t;&t;&t;&t;&t;&t;0x0050
DECL|macro|PM3Aperture1
mdefine_line|#define PM3Aperture1&t;&t;&t;&t;&t;&t;0x0058
DECL|macro|PM3DMAControl
mdefine_line|#define PM3DMAControl&t;&t;&t;&t;&t;&t;0x0060
DECL|macro|PM3FIFODis
mdefine_line|#define PM3FIFODis&t;&t;&t;&t;&t;&t;0x0068
DECL|macro|PM3ChipConfig
mdefine_line|#define PM3ChipConfig&t;&t;&t;&t;&t;&t;0x0070
DECL|macro|PM3AGPControl
mdefine_line|#define PM3AGPControl&t;&t;&t;&t;&t;&t;0x0078
DECL|macro|PM3GPOutDMAAddress
mdefine_line|#define PM3GPOutDMAAddress&t;&t;&t;&t;&t;0x0080
DECL|macro|PM3PCIFeedbackCount
mdefine_line|#define PM3PCIFeedbackCount&t;&t;&t;&t;&t;0x0088
DECL|macro|PM3PCIAbortStatus
mdefine_line|#define PM3PCIAbortStatus&t;&t;&t;&t;&t;0x0090
DECL|macro|PM3PCIAbortAddress
mdefine_line|#define PM3PCIAbortAddress&t;&t;&t;&t;&t;0x0098
DECL|macro|PM3PCIPLLStatus
mdefine_line|#define PM3PCIPLLStatus&t;&t;&t;&t;&t;&t;0x00f0
DECL|macro|PM3HostTextureAddress
mdefine_line|#define PM3HostTextureAddress&t;&t;&t;&t;&t;0x0100
DECL|macro|PM3TextureDownloadControl
mdefine_line|#define PM3TextureDownloadControl&t;&t;&t;&t;0x0108
DECL|macro|PM3TextureOperation
mdefine_line|#define PM3TextureOperation&t;&t;&t;&t;&t;0x0110
DECL|macro|PM3LogicalTexturePage
mdefine_line|#define PM3LogicalTexturePage&t;&t;&t;&t;&t;0x0118
DECL|macro|PM3TexDMAAddress
mdefine_line|#define PM3TexDMAAddress&t;&t;&t;&t;&t;0x0120
DECL|macro|PM3TexFIFOSpace
mdefine_line|#define PM3TexFIFOSpace&t;&t;&t;&t;&t;&t;0x0128
multiline_comment|/**********************************************&n;*  GLINT Permedia3 Region 0 Bypass Controls   *&n;***********************************************/
DECL|macro|PM3ByAperture1Mode
mdefine_line|#define PM3ByAperture1Mode&t;&t;&t;&t;&t;0x0300
DECL|macro|PM3ByApertureMode_BYTESWAP_ABCD
mdefine_line|#define PM3ByApertureMode_BYTESWAP_ABCD&t;&t;&t;(0&lt;&lt;0)
DECL|macro|PM3ByApertureMode_BYTESWAP_BADC
mdefine_line|#define PM3ByApertureMode_BYTESWAP_BADC&t;&t;&t;(1&lt;&lt;0)
DECL|macro|PM3ByApertureMode_BYTESWAP_CDAB
mdefine_line|#define PM3ByApertureMode_BYTESWAP_CDAB&t;&t;&t;(2&lt;&lt;0)
DECL|macro|PM3ByApertureMode_BYTESWAP_DCBA
mdefine_line|#define PM3ByApertureMode_BYTESWAP_DCBA&t;&t;&t;(3&lt;&lt;0)
DECL|macro|PM3ByApertureMode_PATCH_DISABLE
mdefine_line|#define PM3ByApertureMode_PATCH_DISABLE&t;&t;&t;(0&lt;&lt;2)
DECL|macro|PM3ByApertureMode_PATCH_ENABLE
mdefine_line|#define PM3ByApertureMode_PATCH_ENABLE&t;&t;&t;(1&lt;&lt;2)
DECL|macro|PM3ByApertureMode_FORMAT_RAW
mdefine_line|#define PM3ByApertureMode_FORMAT_RAW&t;&t;&t;(0&lt;&lt;3)
DECL|macro|PM3ByApertureMode_FORMAT_YUYV
mdefine_line|#define PM3ByApertureMode_FORMAT_YUYV&t;&t;&t;(1&lt;&lt;3)
DECL|macro|PM3ByApertureMode_FORMAT_UYVY
mdefine_line|#define PM3ByApertureMode_FORMAT_UYVY&t;&t;&t;(2&lt;&lt;3)
DECL|macro|PM3ByApertureMode_PIXELSIZE_8BIT
mdefine_line|#define PM3ByApertureMode_PIXELSIZE_8BIT&t;&t;(0&lt;&lt;5)
DECL|macro|PM3ByApertureMode_PIXELSIZE_16BIT
mdefine_line|#define PM3ByApertureMode_PIXELSIZE_16BIT&t;&t;(1&lt;&lt;5)
DECL|macro|PM3ByApertureMode_PIXELSIZE_32BIT
mdefine_line|#define PM3ByApertureMode_PIXELSIZE_32BIT&t;&t;(2&lt;&lt;5)
DECL|macro|PM3ByApertureMode_PIXELSIZE_MASK
mdefine_line|#define PM3ByApertureMode_PIXELSIZE_MASK        (3&lt;&lt;5)
DECL|macro|PM3ByApertureMode_EFFECTIVE_STRIDE_1024
mdefine_line|#define PM3ByApertureMode_EFFECTIVE_STRIDE_1024&t;&t;(0&lt;&lt;7)
DECL|macro|PM3ByApertureMode_EFFECTIVE_STRIDE_2048
mdefine_line|#define PM3ByApertureMode_EFFECTIVE_STRIDE_2048&t;&t;(1&lt;&lt;7)
DECL|macro|PM3ByApertureMode_EFFECTIVE_STRIDE_4096
mdefine_line|#define PM3ByApertureMode_EFFECTIVE_STRIDE_4096&t;&t;(2&lt;&lt;7)
DECL|macro|PM3ByApertureMode_EFFECTIVE_STRIDE_8192
mdefine_line|#define PM3ByApertureMode_EFFECTIVE_STRIDE_8192&t;&t;(3&lt;&lt;7)
DECL|macro|PM3ByApertureMode_PATCH_OFFSET_X
mdefine_line|#define PM3ByApertureMode_PATCH_OFFSET_X(off)&t;(((off)&amp;7f)&lt;&lt;9)
DECL|macro|PM3ByApertureMode_PATCH_OFFSET_Y
mdefine_line|#define PM3ByApertureMode_PATCH_OFFSET_Y(off)&t;(((off)&amp;7f)&lt;&lt;16)
DECL|macro|PM3ByApertureMode_FRAMEBUFFER
mdefine_line|#define PM3ByApertureMode_FRAMEBUFFER&t;&t;&t;(0&lt;&lt;21)
DECL|macro|PM3ByApertureMode_LOCALBUFFER
mdefine_line|#define PM3ByApertureMode_LOCALBUFFER&t;&t;&t;(1&lt;&lt;21)
DECL|macro|PM3ByApertureMode_DOUBLE_WRITE_OFF
mdefine_line|#define PM3ByApertureMode_DOUBLE_WRITE_OFF&t;&t;(0&lt;&lt;22)
DECL|macro|PM3ByApertureMode_DOUBLE_WRITE_1MB
mdefine_line|#define PM3ByApertureMode_DOUBLE_WRITE_1MB&t;&t;(1&lt;&lt;22)
DECL|macro|PM3ByApertureMode_DOUBLE_WRITE_2MB
mdefine_line|#define PM3ByApertureMode_DOUBLE_WRITE_2MB&t;&t;(2&lt;&lt;22)
DECL|macro|PM3ByApertureMode_DOUBLE_WRITE_4MB
mdefine_line|#define PM3ByApertureMode_DOUBLE_WRITE_4MB&t;&t;(3&lt;&lt;22)
DECL|macro|PM3ByApertureMode_DOUBLE_WRITE_8MB
mdefine_line|#define PM3ByApertureMode_DOUBLE_WRITE_8MB&t;&t;(4&lt;&lt;22)
DECL|macro|PM3ByApertureMode_DOUBLE_WRITE_16MB
mdefine_line|#define PM3ByApertureMode_DOUBLE_WRITE_16MB&t;&t;(5&lt;&lt;22)
DECL|macro|PM3ByApertureMode_DOUBLE_WRITE_32MB
mdefine_line|#define PM3ByApertureMode_DOUBLE_WRITE_32MB&t;&t;(6&lt;&lt;22)
DECL|macro|PM3ByAperture2Mode
mdefine_line|#define PM3ByAperture2Mode&t;&t;&t;&t;&t;0x0328
multiline_comment|/**********************************************&n;*  GLINT Permedia3 Memory Control (0x1000)    *&n;***********************************************/
DECL|macro|PM3MemCounter
mdefine_line|#define PM3MemCounter&t;&t;&t;&t;&t;&t;0x1000
DECL|macro|PM3MemBypassWriteMask
mdefine_line|#define PM3MemBypassWriteMask&t;&t;&t;&t;&t;0x1008
DECL|macro|PM3MemScratch
mdefine_line|#define PM3MemScratch&t;&t;&t;&t;&t;&t;0x1010
DECL|macro|PM3LocalMemCaps
mdefine_line|#define PM3LocalMemCaps&t;&t;&t;&t;&t;&t;0x1018
DECL|macro|PM3LocalMemCaps_NoWriteMask
mdefine_line|#define PM3LocalMemCaps_NoWriteMask                     (1 &lt;&lt; 28)
DECL|macro|PM3LocalMemTimings
mdefine_line|#define PM3LocalMemTimings&t;&t;&t;&t;&t;0x1020
DECL|macro|PM3LocalMemControl
mdefine_line|#define PM3LocalMemControl&t;&t;&t;&t;&t;0x1028
DECL|macro|PM3LocalMemRefresh
mdefine_line|#define PM3LocalMemRefresh&t;&t;&t;&t;&t;0x1030
DECL|macro|PM3LocalMemPowerDown
mdefine_line|#define PM3LocalMemPowerDown&t;&t;&t;&t;&t;0x1038
DECL|macro|PM3RemoteMemControl
mdefine_line|#define PM3RemoteMemControl&t;&t;&t;&t;&t;0x1100
multiline_comment|/**********************************************&n;*  GLINT Permedia3 Video Control (0x3000)     *&n;***********************************************/
DECL|macro|PM3ScreenBase
mdefine_line|#define PM3ScreenBase&t;&t;&t;&t;&t;&t;0x3000
DECL|macro|PM3ScreenStride
mdefine_line|#define PM3ScreenStride&t;&t;&t;&t;&t;&t;0x3008
DECL|macro|PM3HTotal
mdefine_line|#define PM3HTotal&t;&t;&t;&t;&t;&t;0x3010
DECL|macro|PM3HgEnd
mdefine_line|#define PM3HgEnd&t;&t;&t;&t;&t;&t;0x3018
DECL|macro|PM3HbEnd
mdefine_line|#define PM3HbEnd&t;&t;&t;&t;&t;&t;0x3020
DECL|macro|PM3HsStart
mdefine_line|#define PM3HsStart&t;&t;&t;&t;&t;&t;0x3028
DECL|macro|PM3HsEnd
mdefine_line|#define PM3HsEnd&t;&t;&t;&t;&t;&t;0x3030
DECL|macro|PM3VTotal
mdefine_line|#define PM3VTotal&t;&t;&t;&t;&t;&t;0x3038
DECL|macro|PM3VbEnd
mdefine_line|#define PM3VbEnd&t;&t;&t;&t;&t;&t;0x3040
DECL|macro|PM3VsStart
mdefine_line|#define PM3VsStart&t;&t;&t;&t;&t;&t;0x3048
DECL|macro|PM3VsEnd
mdefine_line|#define PM3VsEnd&t;&t;&t;&t;&t;&t;0x3050
DECL|macro|PM3VideoControl
mdefine_line|#define PM3VideoControl&t;&t;&t;&t;&t;&t;0x3058
DECL|macro|PM3VideoControl_DISABLE
mdefine_line|#define PM3VideoControl_DISABLE&t;&t;&t;&t;(0&lt;&lt;0)
DECL|macro|PM3VideoControl_ENABLE
mdefine_line|#define PM3VideoControl_ENABLE&t;&t;&t;&t;(1&lt;&lt;0)
DECL|macro|PM3VideoControl_BLANK_ACTIVE_HIGH
mdefine_line|#define PM3VideoControl_BLANK_ACTIVE_HIGH&t;&t;(0&lt;&lt;1)
DECL|macro|PM3VideoControl_BLANK_ACTIVE_LOW
mdefine_line|#define PM3VideoControl_BLANK_ACTIVE_LOW&t;&t;(1&lt;&lt;1)
DECL|macro|PM3VideoControl_LINE_DOUBLE_OFF
mdefine_line|#define PM3VideoControl_LINE_DOUBLE_OFF&t;&t;&t;(0&lt;&lt;2)
DECL|macro|PM3VideoControl_LINE_DOUBLE_ON
mdefine_line|#define PM3VideoControl_LINE_DOUBLE_ON&t;&t;&t;(1&lt;&lt;2)
DECL|macro|PM3VideoControl_HSYNC_FORCE_HIGH
mdefine_line|#define PM3VideoControl_HSYNC_FORCE_HIGH&t;&t;(0&lt;&lt;3)
DECL|macro|PM3VideoControl_HSYNC_ACTIVE_HIGH
mdefine_line|#define PM3VideoControl_HSYNC_ACTIVE_HIGH&t;&t;(1&lt;&lt;3)
DECL|macro|PM3VideoControl_HSYNC_FORCE_LOW
mdefine_line|#define PM3VideoControl_HSYNC_FORCE_LOW&t;&t;&t;(2&lt;&lt;3)
DECL|macro|PM3VideoControl_HSYNC_ACTIVE_LOW
mdefine_line|#define PM3VideoControl_HSYNC_ACTIVE_LOW&t;&t;(3&lt;&lt;3)
DECL|macro|PM3VideoControl_HSYNC_MASK
mdefine_line|#define PM3VideoControl_HSYNC_MASK          (3&lt;&lt;3)
DECL|macro|PM3VideoControl_VSYNC_FORCE_HIGH
mdefine_line|#define PM3VideoControl_VSYNC_FORCE_HIGH&t;&t;(0&lt;&lt;5)
DECL|macro|PM3VideoControl_VSYNC_ACTIVE_HIGH
mdefine_line|#define PM3VideoControl_VSYNC_ACTIVE_HIGH&t;&t;(1&lt;&lt;5)
DECL|macro|PM3VideoControl_VSYNC_FORCE_LOW
mdefine_line|#define PM3VideoControl_VSYNC_FORCE_LOW&t;&t;&t;(2&lt;&lt;5)
DECL|macro|PM3VideoControl_VSYNC_ACTIVE_LOW
mdefine_line|#define PM3VideoControl_VSYNC_ACTIVE_LOW&t;&t;(3&lt;&lt;5)
DECL|macro|PM3VideoControl_VSYNC_MASK
mdefine_line|#define PM3VideoControl_VSYNC_MASK          (3&lt;&lt;5)
DECL|macro|PM3VideoControl_BYTE_DOUBLE_OFF
mdefine_line|#define PM3VideoControl_BYTE_DOUBLE_OFF&t;&t;&t;(0&lt;&lt;7)
DECL|macro|PM3VideoControl_BYTE_DOUBLE_ON
mdefine_line|#define PM3VideoControl_BYTE_DOUBLE_ON&t;&t;&t;(1&lt;&lt;7)
DECL|macro|PM3VideoControl_BUFFER_SWAP_SYNCON_FRAMEBLANK
mdefine_line|#define PM3VideoControl_BUFFER_SWAP_SYNCON_FRAMEBLANK&t;(0&lt;&lt;9)
DECL|macro|PM3VideoControl_BUFFER_SWAP_FREE_RUNNING
mdefine_line|#define PM3VideoControl_BUFFER_SWAP_FREE_RUNNING&t;(1&lt;&lt;9)
DECL|macro|PM3VideoControl_BUFFER_SWAP_LIMITETO_FRAMERATE
mdefine_line|#define PM3VideoControl_BUFFER_SWAP_LIMITETO_FRAMERATE&t;(2&lt;&lt;9)
DECL|macro|PM3VideoControl_STEREO_DISABLE
mdefine_line|#define PM3VideoControl_STEREO_DISABLE&t;&t;&t;(0&lt;&lt;11)
DECL|macro|PM3VideoControl_STEREO_ENABLE
mdefine_line|#define PM3VideoControl_STEREO_ENABLE&t;&t;&t;(1&lt;&lt;11)
DECL|macro|PM3VideoControl_RIGHT_EYE_ACTIVE_HIGH
mdefine_line|#define PM3VideoControl_RIGHT_EYE_ACTIVE_HIGH&t;&t;(0&lt;&lt;12)
DECL|macro|PM3VideoControl_RIGHT_EYE_ACTIVE_LOW
mdefine_line|#define PM3VideoControl_RIGHT_EYE_ACTIVE_LOW&t;&t;(1&lt;&lt;12)
DECL|macro|PM3VideoControl_VIDEO_EXT_LOW
mdefine_line|#define PM3VideoControl_VIDEO_EXT_LOW&t;&t;&t;(0&lt;&lt;14)
DECL|macro|PM3VideoControl_VIDEO_EXT_HIGH
mdefine_line|#define PM3VideoControl_VIDEO_EXT_HIGH&t;&t;&t;(1&lt;&lt;14)
DECL|macro|PM3VideoControl_SYNC_MODE_INDEPENDENT
mdefine_line|#define PM3VideoControl_SYNC_MODE_INDEPENDENT&t;&t;(0&lt;&lt;16)
DECL|macro|PM3VideoControl_SYNC_MODE_SYNCTO_VSA
mdefine_line|#define PM3VideoControl_SYNC_MODE_SYNCTO_VSA&t;&t;(1&lt;&lt;16)
DECL|macro|PM3VideoControl_SYNC_MODE_SYNCTO_VSB
mdefine_line|#define PM3VideoControl_SYNC_MODE_SYNCTO_VSB&t;&t;(2&lt;&lt;16)
DECL|macro|PM3VideoControl_PATCH_DISABLE
mdefine_line|#define PM3VideoControl_PATCH_DISABLE&t;&t;&t;(0&lt;&lt;18)
DECL|macro|PM3VideoControl_PATCH_ENABLE
mdefine_line|#define PM3VideoControl_PATCH_ENABLE&t;&t;&t;(1&lt;&lt;18)
DECL|macro|PM3VideoControl_PIXELSIZE_8BIT
mdefine_line|#define PM3VideoControl_PIXELSIZE_8BIT&t;&t;&t;(0&lt;&lt;19)
DECL|macro|PM3VideoControl_PIXELSIZE_16BIT
mdefine_line|#define PM3VideoControl_PIXELSIZE_16BIT&t;&t;&t;(1&lt;&lt;19)
DECL|macro|PM3VideoControl_PIXELSIZE_32BIT
mdefine_line|#define PM3VideoControl_PIXELSIZE_32BIT&t;&t;&t;(2&lt;&lt;19)
DECL|macro|PM3VideoControl_DISPLAY_DISABLE
mdefine_line|#define PM3VideoControl_DISPLAY_DISABLE&t;&t;&t;(0&lt;&lt;21)
DECL|macro|PM3VideoControl_DISPLAY_ENABLE
mdefine_line|#define PM3VideoControl_DISPLAY_ENABLE&t;&t;&t;(1&lt;&lt;21)
DECL|macro|PM3VideoControl_PATCH_OFFSET_X
mdefine_line|#define PM3VideoControl_PATCH_OFFSET_X(off)&t;(((off)&amp;0x3f)&lt;&lt;22)
DECL|macro|PM3VideoControl_PATCH_OFFSET_Y
mdefine_line|#define PM3VideoControl_PATCH_OFFSET_Y(off)&t;(((off)&amp;0x3f)&lt;&lt;28)
DECL|macro|PM3InterruptLine
mdefine_line|#define PM3InterruptLine&t;&t;&t;&t;&t;0x3060
DECL|macro|PM3DisplayData
mdefine_line|#define PM3DisplayData&t;&t;&t;&t;&t;&t;0x3068
DECL|macro|PM3VerticalLineCount
mdefine_line|#define PM3VerticalLineCount&t;&t;&t;&t;&t;0x3070
DECL|macro|PM3FifoControl
mdefine_line|#define PM3FifoControl&t;&t;&t;&t;&t;&t;0x3078
DECL|macro|PM3ScreenBaseRight
mdefine_line|#define PM3ScreenBaseRight&t;&t;&t;&t;&t;0x3080
DECL|macro|PM3MiscControl
mdefine_line|#define PM3MiscControl&t;&t;&t;&t;&t;&t;0x3088
DECL|macro|PM3VideoOverlayUpdate
mdefine_line|#define PM3VideoOverlayUpdate&t;&t;&t;&t;&t;0x3100
DECL|macro|PM3VideoOverlayUpdate_DISABLE
mdefine_line|#define PM3VideoOverlayUpdate_DISABLE                   (0&lt;&lt;0)
DECL|macro|PM3VideoOverlayUpdate_ENABLE
mdefine_line|#define PM3VideoOverlayUpdate_ENABLE                    (1&lt;&lt;0)
DECL|macro|PM3VideoOverlayMode
mdefine_line|#define PM3VideoOverlayMode&t;&t;&t;&t;&t;0x3108
DECL|macro|PM3VideoOverlayMode_DISABLE
mdefine_line|#define PM3VideoOverlayMode_DISABLE&t;&t;&t;(0&lt;&lt;0)
DECL|macro|PM3VideoOverlayMode_ENABLE
mdefine_line|#define PM3VideoOverlayMode_ENABLE&t;&t;&t;(1&lt;&lt;0)
DECL|macro|PM3VideoOverlayMode_BUFFERSYNC_MANUAL
mdefine_line|#define PM3VideoOverlayMode_BUFFERSYNC_MANUAL           (0&lt;&lt;1)
DECL|macro|PM3VideoOverlayMode_BUFFERSYNC_VIDEOSTREAMA
mdefine_line|#define PM3VideoOverlayMode_BUFFERSYNC_VIDEOSTREAMA     (1&lt;&lt;1)
DECL|macro|PM3VideoOverlayMode_BUFFERSYNC_VIDEOSTREAMB
mdefine_line|#define PM3VideoOverlayMode_BUFFERSYNC_VIDEOSTREAMB     (2&lt;&lt;1)
DECL|macro|PM3VideoOverlayMode_FIELDPOLARITY_NORMAL
mdefine_line|#define PM3VideoOverlayMode_FIELDPOLARITY_NORMAL        (0&lt;&lt;4)
DECL|macro|PM3VideoOverlayMode_FIELDPOLARITY_INVERT
mdefine_line|#define PM3VideoOverlayMode_FIELDPOLARITY_INVERT        (1&lt;&lt;4)
DECL|macro|PM3VideoOverlayMode_PIXELSIZE_8BIT
mdefine_line|#define PM3VideoOverlayMode_PIXELSIZE_8BIT              (0&lt;&lt;5)
DECL|macro|PM3VideoOverlayMode_PIXELSIZE_16BIT
mdefine_line|#define PM3VideoOverlayMode_PIXELSIZE_16BIT             (1&lt;&lt;5)
DECL|macro|PM3VideoOverlayMode_PIXELSIZE_32BIT
mdefine_line|#define PM3VideoOverlayMode_PIXELSIZE_32BIT             (2&lt;&lt;5)
DECL|macro|PM3VideoOverlayMode_COLORFORMAT_RGB8888
mdefine_line|#define PM3VideoOverlayMode_COLORFORMAT_RGB8888 ((0&lt;&lt;7)|(1&lt;&lt;12)|(2&lt;&lt;5))
DECL|macro|PM3VideoOverlayMode_COLORFORMAT_RGB4444
mdefine_line|#define PM3VideoOverlayMode_COLORFORMAT_RGB4444 ((1&lt;&lt;7)|(1&lt;&lt;12)|(1&lt;&lt;5))
DECL|macro|PM3VideoOverlayMode_COLORFORMAT_RGB5551
mdefine_line|#define PM3VideoOverlayMode_COLORFORMAT_RGB5551 ((2&lt;&lt;7)|(1&lt;&lt;12)|(1&lt;&lt;5))
DECL|macro|PM3VideoOverlayMode_COLORFORMAT_RGB565
mdefine_line|#define PM3VideoOverlayMode_COLORFORMAT_RGB565  ((3&lt;&lt;7)|(1&lt;&lt;12)|(1&lt;&lt;5))
DECL|macro|PM3VideoOverlayMode_COLORFORMAT_RGB332
mdefine_line|#define PM3VideoOverlayMode_COLORFORMAT_RGB332  ((4&lt;&lt;7)|(1&lt;&lt;12)|(0&lt;&lt;5))
DECL|macro|PM3VideoOverlayMode_COLORFORMAT_BGR8888
mdefine_line|#define PM3VideoOverlayMode_COLORFORMAT_BGR8888 ((0&lt;&lt;7)|(2&lt;&lt;5))
DECL|macro|PM3VideoOverlayMode_COLORFORMAT_BGR4444
mdefine_line|#define PM3VideoOverlayMode_COLORFORMAT_BGR4444 ((1&lt;&lt;7)|(1&lt;&lt;5))
DECL|macro|PM3VideoOverlayMode_COLORFORMAT_BGR5551
mdefine_line|#define PM3VideoOverlayMode_COLORFORMAT_BGR5551 ((2&lt;&lt;7)|(1&lt;&lt;5))
DECL|macro|PM3VideoOverlayMode_COLORFORMAT_BGR565
mdefine_line|#define PM3VideoOverlayMode_COLORFORMAT_BGR565  ((3&lt;&lt;7)|(1&lt;&lt;5))
DECL|macro|PM3VideoOverlayMode_COLORFORMAT_BGR332
mdefine_line|#define PM3VideoOverlayMode_COLORFORMAT_BGR332  ((4&lt;&lt;7)|(0&lt;&lt;5))
DECL|macro|PM3VideoOverlayMode_COLORFORMAT_CI8
mdefine_line|#define PM3VideoOverlayMode_COLORFORMAT_CI8     ((5&lt;&lt;7)|(1&lt;&lt;12)|(0&lt;&lt;5))
DECL|macro|PM3VideoOverlayMode_COLORFORMAT_VUY444
mdefine_line|#define PM3VideoOverlayMode_COLORFORMAT_VUY444  ((2&lt;&lt;10)|(1&lt;&lt;12)|(2&lt;&lt;5))
DECL|macro|PM3VideoOverlayMode_COLORFORMAT_YUV444
mdefine_line|#define PM3VideoOverlayMode_COLORFORMAT_YUV444  ((2&lt;&lt;10)|(2&lt;&lt;5))
DECL|macro|PM3VideoOverlayMode_COLORFORMAT_VUY422
mdefine_line|#define PM3VideoOverlayMode_COLORFORMAT_VUY422  ((1&lt;&lt;10)|(1&lt;&lt;12)|(1&lt;&lt;5))
DECL|macro|PM3VideoOverlayMode_COLORFORMAT_YUV422
mdefine_line|#define PM3VideoOverlayMode_COLORFORMAT_YUV422  ((1&lt;&lt;10)|(1&lt;&lt;5))
DECL|macro|PM3VideoOverlayMode_COLORORDER_BGR
mdefine_line|#define PM3VideoOverlayMode_COLORORDER_BGR              (0&lt;&lt;12)
DECL|macro|PM3VideoOverlayMode_COLORORDER_RGB
mdefine_line|#define PM3VideoOverlayMode_COLORORDER_RGB              (1&lt;&lt;12)
DECL|macro|PM3VideoOverlayMode_LINEARCOLOREXT_OFF
mdefine_line|#define PM3VideoOverlayMode_LINEARCOLOREXT_OFF          (0&lt;&lt;13)
DECL|macro|PM3VideoOverlayMode_LINEARCOLOREXT_ON
mdefine_line|#define PM3VideoOverlayMode_LINEARCOLOREXT_ON           (1&lt;&lt;13)
DECL|macro|PM3VideoOverlayMode_FILTER_MASK
mdefine_line|#define PM3VideoOverlayMode_FILTER_MASK                 (3&lt;&lt;14)
DECL|macro|PM3VideoOverlayMode_FILTER_OFF
mdefine_line|#define PM3VideoOverlayMode_FILTER_OFF                  (0&lt;&lt;14)
DECL|macro|PM3VideoOverlayMode_FILTER_FULL
mdefine_line|#define PM3VideoOverlayMode_FILTER_FULL                 (1&lt;&lt;14)
DECL|macro|PM3VideoOverlayMode_FILTER_PARTIAL
mdefine_line|#define PM3VideoOverlayMode_FILTER_PARTIAL              (2&lt;&lt;14)
DECL|macro|PM3VideoOverlayMode_DEINTERLACE_OFF
mdefine_line|#define PM3VideoOverlayMode_DEINTERLACE_OFF             (0&lt;&lt;16)
DECL|macro|PM3VideoOverlayMode_DEINTERLACE_BOB
mdefine_line|#define PM3VideoOverlayMode_DEINTERLACE_BOB             (1&lt;&lt;16)
DECL|macro|PM3VideoOverlayMode_PATCHMODE_OFF
mdefine_line|#define PM3VideoOverlayMode_PATCHMODE_OFF               (0&lt;&lt;18)
DECL|macro|PM3VideoOverlayMode_PATCHMODE_ON
mdefine_line|#define PM3VideoOverlayMode_PATCHMODE_ON                (1&lt;&lt;18)
DECL|macro|PM3VideoOverlayMode_FLIP_VIDEO
mdefine_line|#define PM3VideoOverlayMode_FLIP_VIDEO                  (0&lt;&lt;20)
DECL|macro|PM3VideoOverlayMode_FLIP_VIDEOSTREAMA
mdefine_line|#define PM3VideoOverlayMode_FLIP_VIDEOSTREAMA           (1&lt;&lt;20)
DECL|macro|PM3VideoOverlayMode_FLIP_VIDEOSTREAMB
mdefine_line|#define PM3VideoOverlayMode_FLIP_VIDEOSTREAMB           (2&lt;&lt;20)
DECL|macro|PM3VideoOverlayMode_MIRROR_MASK
mdefine_line|#define PM3VideoOverlayMode_MIRROR_MASK                 (3&lt;&lt;23)
DECL|macro|PM3VideoOverlayMode_MIRRORX_OFF
mdefine_line|#define PM3VideoOverlayMode_MIRRORX_OFF                 (0&lt;&lt;23)
DECL|macro|PM3VideoOverlayMode_MIRRORX_ON
mdefine_line|#define PM3VideoOverlayMode_MIRRORX_ON                  (1&lt;&lt;23)
DECL|macro|PM3VideoOverlayMode_MIRRORY_OFF
mdefine_line|#define PM3VideoOverlayMode_MIRRORY_OFF                 (0&lt;&lt;24)
DECL|macro|PM3VideoOverlayMode_MIRRORY_ON
mdefine_line|#define PM3VideoOverlayMode_MIRRORY_ON                  (1&lt;&lt;24)
DECL|macro|PM3VideoOverlayFifoControl
mdefine_line|#define PM3VideoOverlayFifoControl&t;&t;&t;&t;0x3110
DECL|macro|PM3VideoOverlayIndex
mdefine_line|#define PM3VideoOverlayIndex&t;&t;&t;&t;&t;0x3118
DECL|macro|PM3VideoOverlayBase0
mdefine_line|#define PM3VideoOverlayBase0&t;&t;&t;&t;&t;0x3120
DECL|macro|PM3VideoOverlayBase1
mdefine_line|#define PM3VideoOverlayBase1&t;&t;&t;&t;&t;0x3128
DECL|macro|PM3VideoOverlayBase2
mdefine_line|#define PM3VideoOverlayBase2&t;&t;&t;&t;&t;0x3130
DECL|macro|PM3VideoOverlayStride
mdefine_line|#define PM3VideoOverlayStride&t;&t;&t;&t;&t;0x3138
DECL|macro|PM3VideoOverlayStride_STRIDE
mdefine_line|#define PM3VideoOverlayStride_STRIDE(s)         (((s)&amp;0xfff)&lt;&lt;0)
DECL|macro|PM3VideoOverlayWidth
mdefine_line|#define PM3VideoOverlayWidth                                    0x3140
DECL|macro|PM3VideoOverlayWidth_WIDTH
mdefine_line|#define PM3VideoOverlayWidth_WIDTH(w)           (((w)&amp;0xfff)&lt;&lt;0)
DECL|macro|PM3VideoOverlayHeight
mdefine_line|#define PM3VideoOverlayHeight                                   0x3148
DECL|macro|PM3VideoOverlayHeight_HEIGHT
mdefine_line|#define PM3VideoOverlayHeight_HEIGHT(h)         (((h)&amp;0xfff)&lt;&lt;0)
DECL|macro|PM3VideoOverlayOrigin
mdefine_line|#define PM3VideoOverlayOrigin                                   0x3150
DECL|macro|PM3VideoOverlayOrigin_XORIGIN
mdefine_line|#define PM3VideoOverlayOrigin_XORIGIN(x)        (((x)&amp;0xfff)&lt;&lt;0)
DECL|macro|PM3VideoOverlayOrigin_YORIGIN
mdefine_line|#define PM3VideoOverlayOrigin_YORIGIN(y)        (((y)&amp;0xfff)&lt;&lt;16)
DECL|macro|PM3VideoOverlayShrinkXDelta
mdefine_line|#define PM3VideoOverlayShrinkXDelta                             0x3158
DECL|macro|PM3VideoOverlayShrinkXDelta_NONE
mdefine_line|#define PM3VideoOverlayShrinkXDelta_NONE                (1&lt;&lt;16)
DECL|macro|PM3VideoOverlayShrinkXDelta_DELTA
mdefine_line|#define PM3VideoOverlayShrinkXDelta_DELTA(s,d)          &bslash;&n;                ((((s)&lt;&lt;16)/(d))&amp;0x0ffffff0)
DECL|macro|PM3VideoOverlayZoomXDelta
mdefine_line|#define PM3VideoOverlayZoomXDelta                               0x3160
DECL|macro|PM3VideoOverlayZoomXDelta_NONE
mdefine_line|#define PM3VideoOverlayZoomXDelta_NONE                  (1&lt;&lt;16)
DECL|macro|PM3VideoOverlayZoomXDelta_DELTA
mdefine_line|#define PM3VideoOverlayZoomXDelta_DELTA(s,d)            &bslash;&n;                ((((s)&lt;&lt;16)/(d))&amp;0x0001fff0)
DECL|macro|PM3VideoOverlayYDelta
mdefine_line|#define PM3VideoOverlayYDelta                                   0x3168
DECL|macro|PM3VideoOverlayYDelta_NONE
mdefine_line|#define PM3VideoOverlayYDelta_NONE                      (1&lt;&lt;16)
DECL|macro|PM3VideoOverlayYDelta_DELTA
mdefine_line|#define PM3VideoOverlayYDelta_DELTA(s,d)                        &bslash;&n;                ((((s)&lt;&lt;16)/(d))&amp;0x0ffffff0)
DECL|macro|PM3VideoOverlayFieldOffset
mdefine_line|#define PM3VideoOverlayFieldOffset&t;&t;&t;&t;0x3170
DECL|macro|PM3VideoOverlayStatus
mdefine_line|#define PM3VideoOverlayStatus&t;&t;&t;&t;&t;0x3178
multiline_comment|/**********************************************&n;*  GLINT Permedia3 RAMDAC Registers (0x4000)  *&n;***********************************************/
multiline_comment|/* Direct Registers */
DECL|macro|PM3RD_PaletteWriteAddress
mdefine_line|#define PM3RD_PaletteWriteAddress&t;&t;&t;&t;0x4000
DECL|macro|PM3RD_PaletteData
mdefine_line|#define PM3RD_PaletteData&t;&t;&t;&t;&t;0x4008
DECL|macro|PM3RD_PixelMask
mdefine_line|#define PM3RD_PixelMask&t;&t;&t;&t;&t;&t;0x4010
DECL|macro|PM3RD_PaletteReadAddress
mdefine_line|#define PM3RD_PaletteReadAddress&t;&t;&t;&t;0x4018
DECL|macro|PM3RD_IndexLow
mdefine_line|#define PM3RD_IndexLow&t;&t;&t;&t;&t;&t;0x4020
DECL|macro|PM3RD_IndexHigh
mdefine_line|#define PM3RD_IndexHigh&t;&t;&t;&t;&t;&t;0x4028
DECL|macro|PM3RD_IndexedData
mdefine_line|#define PM3RD_IndexedData&t;&t;&t;&t;&t;0x4030
DECL|macro|PM3RD_IndexControl
mdefine_line|#define PM3RD_IndexControl&t;&t;&t;&t;&t;0x4038
DECL|macro|PM3RD_IndexControl_AUTOINCREMENT_ENABLE
mdefine_line|#define PM3RD_IndexControl_AUTOINCREMENT_ENABLE&t;&t;(1&lt;&lt;0)
DECL|macro|PM3RD_IndexControl_AUTOINCREMENT_DISABLE
mdefine_line|#define PM3RD_IndexControl_AUTOINCREMENT_DISABLE&t;(0&lt;&lt;0)
multiline_comment|/* Indirect Registers */
DECL|macro|PM3RD_MiscControl
mdefine_line|#define PM3RD_MiscControl&t;&t;&t;&t;&t;0x000
DECL|macro|PM3RD_MiscControl_HIGHCOLOR_RES_DISABLE
mdefine_line|#define PM3RD_MiscControl_HIGHCOLOR_RES_DISABLE&t;&t;(0&lt;&lt;0)
DECL|macro|PM3RD_MiscControl_HIGHCOLOR_RES_ENABLE
mdefine_line|#define PM3RD_MiscControl_HIGHCOLOR_RES_ENABLE&t;&t;(1&lt;&lt;0)
DECL|macro|PM3RD_MiscControl_PIXELDOUBLE_DISABLE
mdefine_line|#define PM3RD_MiscControl_PIXELDOUBLE_DISABLE&t;&t;(0&lt;&lt;1)
DECL|macro|PM3RD_MiscControl_PIXELDOUBLE_ENABLE
mdefine_line|#define PM3RD_MiscControl_PIXELDOUBLE_ENABLE&t;&t;(1&lt;&lt;1)
DECL|macro|PM3RD_MiscControl_LASTREAD_ADDR_DISABLE
mdefine_line|#define PM3RD_MiscControl_LASTREAD_ADDR_DISABLE&t;&t;(0&lt;&lt;2)
DECL|macro|PM3RD_MiscControl_LASTREAD_ADDR_ENABLE
mdefine_line|#define PM3RD_MiscControl_LASTREAD_ADDR_ENABLE&t;&t;(1&lt;&lt;2)
DECL|macro|PM3RD_MiscControl_DIRECTCOLOR_DISABLE
mdefine_line|#define PM3RD_MiscControl_DIRECTCOLOR_DISABLE&t;&t;(0&lt;&lt;3)
DECL|macro|PM3RD_MiscControl_DIRECTCOLOR_ENABLE
mdefine_line|#define PM3RD_MiscControl_DIRECTCOLOR_ENABLE&t;&t;(1&lt;&lt;3)
DECL|macro|PM3RD_MiscControl_OVERLAY_DISABLE
mdefine_line|#define PM3RD_MiscControl_OVERLAY_DISABLE&t;&t;(0&lt;&lt;4)
DECL|macro|PM3RD_MiscControl_OVERLAY_ENABLE
mdefine_line|#define PM3RD_MiscControl_OVERLAY_ENABLE&t;&t;(1&lt;&lt;4)
DECL|macro|PM3RD_MiscControl_PIXELDOUBLE_BUFFER_DISABLE
mdefine_line|#define PM3RD_MiscControl_PIXELDOUBLE_BUFFER_DISABLE&t;(0&lt;&lt;5)
DECL|macro|PM3RD_MiscControl_PIXELDOUBLE_BUFFER_ENABLE
mdefine_line|#define PM3RD_MiscControl_PIXELDOUBLE_BUFFER_ENABLE&t;(1&lt;&lt;5)
DECL|macro|PM3RD_MiscControl_VSB_OUTPUT_DISABLE
mdefine_line|#define PM3RD_MiscControl_VSB_OUTPUT_DISABLE&t;&t;(0&lt;&lt;6)
DECL|macro|PM3RD_MiscControl_VSB_OUTPUT_ENABLE
mdefine_line|#define PM3RD_MiscControl_VSB_OUTPUT_ENABLE&t;&t;(1&lt;&lt;6)
DECL|macro|PM3RD_MiscControl_STEREODOUBLE_BUFFER_DISABLE
mdefine_line|#define PM3RD_MiscControl_STEREODOUBLE_BUFFER_DISABLE&t;(0&lt;&lt;7)
DECL|macro|PM3RD_MiscControl_STEREODOUBLE_BUFFER_ENABLE
mdefine_line|#define PM3RD_MiscControl_STEREODOUBLE_BUFFER_ENABLE&t;(1&lt;&lt;7)
DECL|macro|PM3RD_SyncControl
mdefine_line|#define PM3RD_SyncControl&t;&t;&t;&t;&t;0x001
DECL|macro|PM3RD_SyncControl_HSYNC_ACTIVE_LOW
mdefine_line|#define PM3RD_SyncControl_HSYNC_ACTIVE_LOW&t;&t;(0&lt;&lt;0)
DECL|macro|PM3RD_SyncControl_HSYNC_ACTIVE_HIGH
mdefine_line|#define PM3RD_SyncControl_HSYNC_ACTIVE_HIGH&t;&t;(1&lt;&lt;0)
DECL|macro|PM3RD_SyncControl_HSYNC_FORCE_ACTIVE
mdefine_line|#define PM3RD_SyncControl_HSYNC_FORCE_ACTIVE&t;&t;(3&lt;&lt;0)
DECL|macro|PM3RD_SyncControl_HSYNC_FORCE_INACTIVE
mdefine_line|#define PM3RD_SyncControl_HSYNC_FORCE_INACTIVE&t;&t;(4&lt;&lt;0)
DECL|macro|PM3RD_SyncControl_HSYNC_TRI_STATE
mdefine_line|#define PM3RD_SyncControl_HSYNC_TRI_STATE&t;&t;(2&lt;&lt;0)
DECL|macro|PM3RD_SyncControl_VSYNC_ACTIVE_LOW
mdefine_line|#define PM3RD_SyncControl_VSYNC_ACTIVE_LOW&t;&t;(0&lt;&lt;3)
DECL|macro|PM3RD_SyncControl_VSYNC_ACTIVE_HIGH
mdefine_line|#define PM3RD_SyncControl_VSYNC_ACTIVE_HIGH&t;&t;(1&lt;&lt;3)
DECL|macro|PM3RD_SyncControl_VSYNC_TRI_STATE
mdefine_line|#define PM3RD_SyncControl_VSYNC_TRI_STATE&t;&t;(2&lt;&lt;3)
DECL|macro|PM3RD_SyncControl_VSYNC_FORCE_ACTIVE
mdefine_line|#define PM3RD_SyncControl_VSYNC_FORCE_ACTIVE&t;&t;(3&lt;&lt;3)
DECL|macro|PM3RD_SyncControl_VSYNC_FORCE_INACTIVE
mdefine_line|#define PM3RD_SyncControl_VSYNC_FORCE_INACTIVE&t;&t;(4&lt;&lt;3)
DECL|macro|PM3RD_SyncControl_HSYNC_OVERRIDE_SETBY_HSYNC
mdefine_line|#define PM3RD_SyncControl_HSYNC_OVERRIDE_SETBY_HSYNC&t;(0&lt;&lt;6)
DECL|macro|PM3RD_SyncControl_HSYNC_OVERRIDE_FORCE_HIGH
mdefine_line|#define PM3RD_SyncControl_HSYNC_OVERRIDE_FORCE_HIGH&t;(1&lt;&lt;6)
DECL|macro|PM3RD_SyncControl_VSYNC_OVERRIDE_SETBY_VSYNC
mdefine_line|#define PM3RD_SyncControl_VSYNC_OVERRIDE_SETBY_VSYNC&t;(0&lt;&lt;7)
DECL|macro|PM3RD_SyncControl_VSYNC_OVERRIDE_FORCE_HIGH
mdefine_line|#define PM3RD_SyncControl_VSYNC_OVERRIDE_FORCE_HIGH&t;(1&lt;&lt;7)
DECL|macro|PM3RD_DACControl
mdefine_line|#define PM3RD_DACControl&t;&t;&t;&t;&t;0x002
DECL|macro|PM3RD_DACControl_DAC_POWER_ON
mdefine_line|#define PM3RD_DACControl_DAC_POWER_ON&t;&t;&t;(0&lt;&lt;0)
DECL|macro|PM3RD_DACControl_DAC_POWER_OFF
mdefine_line|#define PM3RD_DACControl_DAC_POWER_OFF&t;&t;&t;(1&lt;&lt;0)
DECL|macro|PM3RD_DACControl_SYNC_ON_GREEN_DISABLE
mdefine_line|#define PM3RD_DACControl_SYNC_ON_GREEN_DISABLE&t;&t;(0&lt;&lt;3)
DECL|macro|PM3RD_DACControl_SYNC_ON_GREEN_ENABLE
mdefine_line|#define PM3RD_DACControl_SYNC_ON_GREEN_ENABLE&t;&t;(1&lt;&lt;3)
DECL|macro|PM3RD_DACControl_BLANK_RED_DAC_DISABLE
mdefine_line|#define PM3RD_DACControl_BLANK_RED_DAC_DISABLE&t;&t;(0&lt;&lt;4)
DECL|macro|PM3RD_DACControl_BLANK_RED_DAC_ENABLE
mdefine_line|#define PM3RD_DACControl_BLANK_RED_DAC_ENABLE&t;&t;(1&lt;&lt;4)
DECL|macro|PM3RD_DACControl_BLANK_GREEN_DAC_DISABLE
mdefine_line|#define PM3RD_DACControl_BLANK_GREEN_DAC_DISABLE&t;(0&lt;&lt;5)
DECL|macro|PM3RD_DACControl_BLANK_GREEN_DAC_ENABLE
mdefine_line|#define PM3RD_DACControl_BLANK_GREEN_DAC_ENABLE&t;&t;(1&lt;&lt;5)
DECL|macro|PM3RD_DACControl_BLANK_BLUE_DAC_DISABLE
mdefine_line|#define PM3RD_DACControl_BLANK_BLUE_DAC_DISABLE&t;&t;(0&lt;&lt;6)
DECL|macro|PM3RD_DACControl_BLANK_BLUE_DAC_ENABLE
mdefine_line|#define PM3RD_DACControl_BLANK_BLUE_DAC_ENABLE&t;&t;(1&lt;&lt;6)
DECL|macro|PM3RD_DACControl_BLANK_PEDESTAL_DISABLE
mdefine_line|#define PM3RD_DACControl_BLANK_PEDESTAL_DISABLE&t;&t;(0&lt;&lt;7)
DECL|macro|PM3RD_DACControl_BLANK_PEDESTAL_ENABLE
mdefine_line|#define PM3RD_DACControl_BLANK_PEDESTAL_ENABLE&t;&t;(1&lt;&lt;7)
DECL|macro|PM3RD_PixelSize
mdefine_line|#define PM3RD_PixelSize&t;&t;&t;&t;&t;&t;0x003
DECL|macro|PM3RD_PixelSize_24_BIT_PIXELS
mdefine_line|#define PM3RD_PixelSize_24_BIT_PIXELS&t;&t;&t;(4&lt;&lt;0)
DECL|macro|PM3RD_PixelSize_32_BIT_PIXELS
mdefine_line|#define PM3RD_PixelSize_32_BIT_PIXELS&t;&t;&t;(2&lt;&lt;0)
DECL|macro|PM3RD_PixelSize_16_BIT_PIXELS
mdefine_line|#define PM3RD_PixelSize_16_BIT_PIXELS&t;&t;&t;(1&lt;&lt;0)
DECL|macro|PM3RD_PixelSize_8_BIT_PIXELS
mdefine_line|#define PM3RD_PixelSize_8_BIT_PIXELS&t;&t;&t;(0&lt;&lt;0)
DECL|macro|PM3RD_ColorFormat
mdefine_line|#define PM3RD_ColorFormat&t;&t;&t;&t;&t;0x004
DECL|macro|PM3RD_ColorFormat_LINEAR_COLOR_EXT_ENABLE
mdefine_line|#define PM3RD_ColorFormat_LINEAR_COLOR_EXT_ENABLE&t;(1&lt;&lt;6)
DECL|macro|PM3RD_ColorFormat_LINEAR_COLOR_EXT_DISABLE
mdefine_line|#define PM3RD_ColorFormat_LINEAR_COLOR_EXT_DISABLE&t;(0&lt;&lt;6)
DECL|macro|PM3RD_ColorFormat_COLOR_ORDER_BLUE_LOW
mdefine_line|#define PM3RD_ColorFormat_COLOR_ORDER_BLUE_LOW&t;&t;(1&lt;&lt;5)
DECL|macro|PM3RD_ColorFormat_COLOR_ORDER_RED_LOW
mdefine_line|#define PM3RD_ColorFormat_COLOR_ORDER_RED_LOW&t;&t;(0&lt;&lt;5)
DECL|macro|PM3RD_ColorFormat_COLOR_FORMAT_MASK
mdefine_line|#define PM3RD_ColorFormat_COLOR_FORMAT_MASK&t;&t;(0x1f&lt;&lt;0)
DECL|macro|PM3RD_ColorFormat_8888_COLOR
mdefine_line|#define PM3RD_ColorFormat_8888_COLOR&t;&t;&t;(0&lt;&lt;0)
DECL|macro|PM3RD_ColorFormat_5551_FRONT_COLOR
mdefine_line|#define PM3RD_ColorFormat_5551_FRONT_COLOR&t;&t;(1&lt;&lt;0)
DECL|macro|PM3RD_ColorFormat_4444_COLOR
mdefine_line|#define PM3RD_ColorFormat_4444_COLOR&t;&t;&t;(2&lt;&lt;0)
DECL|macro|PM3RD_ColorFormat_332_FRONT_COLOR
mdefine_line|#define PM3RD_ColorFormat_332_FRONT_COLOR&t;&t;(5&lt;&lt;0)
DECL|macro|PM3RD_ColorFormat_332_BACK_COLOR
mdefine_line|#define PM3RD_ColorFormat_332_BACK_COLOR&t;&t;(6&lt;&lt;0)
DECL|macro|PM3RD_ColorFormat_2321_FRONT_COLOR
mdefine_line|#define PM3RD_ColorFormat_2321_FRONT_COLOR&t;&t;(9&lt;&lt;0)
DECL|macro|PM3RD_ColorFormat_2321_BACK_COLOR
mdefine_line|#define PM3RD_ColorFormat_2321_BACK_COLOR&t;&t;(10&lt;&lt;0)
DECL|macro|PM3RD_ColorFormat_232_FRONTOFF_COLOR
mdefine_line|#define PM3RD_ColorFormat_232_FRONTOFF_COLOR&t;&t;(11&lt;&lt;0)
DECL|macro|PM3RD_ColorFormat_232_BACKOFF_COLOR
mdefine_line|#define PM3RD_ColorFormat_232_BACKOFF_COLOR&t;&t;(12&lt;&lt;0)
DECL|macro|PM3RD_ColorFormat_5551_BACK_COLOR
mdefine_line|#define PM3RD_ColorFormat_5551_BACK_COLOR&t;&t;(13&lt;&lt;0)
DECL|macro|PM3RD_ColorFormat_CI8_COLOR
mdefine_line|#define PM3RD_ColorFormat_CI8_COLOR&t;&t;&t;(14&lt;&lt;0)
DECL|macro|PM3RD_ColorFormat_565_FRONT_COLOR
mdefine_line|#define PM3RD_ColorFormat_565_FRONT_COLOR&t;&t;(16&lt;&lt;0)
DECL|macro|PM3RD_ColorFormat_565_BACK_COLOR
mdefine_line|#define PM3RD_ColorFormat_565_BACK_COLOR&t;&t;(17&lt;&lt;0)
DECL|macro|PM3RD_CursorMode
mdefine_line|#define PM3RD_CursorMode&t;&t;&t;&t;&t;0x005
DECL|macro|PM3RD_CursorMode_CURSOR_DISABLE
mdefine_line|#define PM3RD_CursorMode_CURSOR_DISABLE&t;&t;&t;(0&lt;&lt;0)
DECL|macro|PM3RD_CursorMode_CURSOR_ENABLE
mdefine_line|#define PM3RD_CursorMode_CURSOR_ENABLE&t;&t;&t;(1&lt;&lt;0)
DECL|macro|PM3RD_CursorMode_FORMAT_64x64_2BPE_P0123
mdefine_line|#define PM3RD_CursorMode_FORMAT_64x64_2BPE_P0123&t;(0&lt;&lt;2)
DECL|macro|PM3RD_CursorMode_FORMAT_32x32_2BPE_P0
mdefine_line|#define PM3RD_CursorMode_FORMAT_32x32_2BPE_P0&t;&t;(1&lt;&lt;2)
DECL|macro|PM3RD_CursorMode_FORMAT_32x32_2BPE_P1
mdefine_line|#define PM3RD_CursorMode_FORMAT_32x32_2BPE_P1&t;&t;(2&lt;&lt;2)
DECL|macro|PM3RD_CursorMode_FORMAT_32x32_2BPE_P2
mdefine_line|#define PM3RD_CursorMode_FORMAT_32x32_2BPE_P2&t;&t;(3&lt;&lt;2)
DECL|macro|PM3RD_CursorMode_FORMAT_32x32_2BPE_P3
mdefine_line|#define PM3RD_CursorMode_FORMAT_32x32_2BPE_P3&t;&t;(4&lt;&lt;2)
DECL|macro|PM3RD_CursorMode_FORMAT_32x32_4BPE_P01
mdefine_line|#define PM3RD_CursorMode_FORMAT_32x32_4BPE_P01&t;&t;(5&lt;&lt;2)
DECL|macro|PM3RD_CursorMode_FORMAT_32x32_4BPE_P23
mdefine_line|#define PM3RD_CursorMode_FORMAT_32x32_4BPE_P23&t;&t;(6&lt;&lt;2)
DECL|macro|PM3RD_CursorMode_TYPE_MS
mdefine_line|#define PM3RD_CursorMode_TYPE_MS&t;&t;&t;(0&lt;&lt;4)
DECL|macro|PM3RD_CursorMode_TYPE_X
mdefine_line|#define PM3RD_CursorMode_TYPE_X&t;&t;&t;&t;(1&lt;&lt;4)
DECL|macro|PM3RD_CursorMode_REVERSE_PIXEL_ORDER_DISABLE
mdefine_line|#define PM3RD_CursorMode_REVERSE_PIXEL_ORDER_DISABLE&t;(0&lt;&lt;6)
DECL|macro|PM3RD_CursorMode_REVERSE_PIXEL_ORDER_ENABLE
mdefine_line|#define PM3RD_CursorMode_REVERSE_PIXEL_ORDER_ENABLE&t;(1&lt;&lt;6)
DECL|macro|PM3RD_CursorMode_REVERSE_PIXEL_ORDER_3_COLOR
mdefine_line|#define PM3RD_CursorMode_REVERSE_PIXEL_ORDER_3_COLOR&t;(2&lt;&lt;6)
DECL|macro|PM3RD_CursorMode_REVERSE_PIXEL_ORDER_15_COLOR
mdefine_line|#define PM3RD_CursorMode_REVERSE_PIXEL_ORDER_15_COLOR&t;(3&lt;&lt;6)
DECL|macro|PM3RD_CursorControl
mdefine_line|#define PM3RD_CursorControl&t;&t;&t;&t;&t;0x006
DECL|macro|PM3RD_CursorControl_DOUBLE_X_DISABLED
mdefine_line|#define PM3RD_CursorControl_DOUBLE_X_DISABLED&t;&t;(0&lt;&lt;0)
DECL|macro|PM3RD_CursorControl_DOUBLE_X_ENABLED
mdefine_line|#define PM3RD_CursorControl_DOUBLE_X_ENABLED&t;&t;(1&lt;&lt;0)
DECL|macro|PM3RD_CursorControl_DOUBLE_Y_DISABLED
mdefine_line|#define PM3RD_CursorControl_DOUBLE_Y_DISABLED&t;&t;(0&lt;&lt;1)
DECL|macro|PM3RD_CursorControl_DOUBLE_Y_ENABLED
mdefine_line|#define PM3RD_CursorControl_DOUBLE_Y_ENABLED&t;&t;(1&lt;&lt;1)
DECL|macro|PM3RD_CursorControl_READBACK_POS_DISABLED
mdefine_line|#define PM3RD_CursorControl_READBACK_POS_DISABLED&t;(0&lt;&lt;2)
DECL|macro|PM3RD_CursorControl_READBACK_POS_ENABLED
mdefine_line|#define PM3RD_CursorControl_READBACK_POS_ENABLED&t;(1&lt;&lt;2)
DECL|macro|PM3RD_CursorXLow
mdefine_line|#define PM3RD_CursorXLow&t;&t;&t;&t;&t;0x007
DECL|macro|PM3RD_CursorXHigh
mdefine_line|#define PM3RD_CursorXHigh&t;&t;&t;&t;&t;0x008
DECL|macro|PM3RD_CursorYLow
mdefine_line|#define PM3RD_CursorYLow&t;&t;&t;&t;&t;0x009
DECL|macro|PM3RD_CursorYHigh
mdefine_line|#define PM3RD_CursorYHigh&t;&t;&t;&t;&t;0x00a
DECL|macro|PM3RD_CursorHotSpotX
mdefine_line|#define PM3RD_CursorHotSpotX&t;&t;&t;&t;&t;0x00b
DECL|macro|PM3RD_CursorHotSpotY
mdefine_line|#define PM3RD_CursorHotSpotY&t;&t;&t;&t;&t;0x00c
DECL|macro|PM3RD_OverlayKey
mdefine_line|#define PM3RD_OverlayKey&t;&t;&t;&t;&t;0x00d
DECL|macro|PM3RD_Pan
mdefine_line|#define PM3RD_Pan&t;&t;&t;&t;&t;&t;0x00e
DECL|macro|PM3RD_Pan_DISABLE
mdefine_line|#define PM3RD_Pan_DISABLE&t;&t;&t;&t;(0&lt;&lt;0)
DECL|macro|PM3RD_Pan_ENABLE
mdefine_line|#define PM3RD_Pan_ENABLE&t;&t;&t;&t;(1&lt;&lt;0)
DECL|macro|PM3RD_Pan_GATE_DISABLE
mdefine_line|#define PM3RD_Pan_GATE_DISABLE&t;&t;&t;&t;(0&lt;&lt;1)
DECL|macro|PM3RD_Pan_GATE_ENABLE
mdefine_line|#define PM3RD_Pan_GATE_ENABLE&t;&t;&t;&t;(1&lt;&lt;1)
DECL|macro|PM3RD_Sense
mdefine_line|#define PM3RD_Sense&t;&t;&t;&t;&t;&t;0x00f
DECL|macro|PM3RD_CheckControl
mdefine_line|#define PM3RD_CheckControl&t;&t;&t;&t;&t;0x018
DECL|macro|PM3RD_CheckControl_PIXEL_DISABLED
mdefine_line|#define PM3RD_CheckControl_PIXEL_DISABLED&t;&t;(0&lt;&lt;0)
DECL|macro|PM3RD_CheckControl_PIXEL_ENABLED
mdefine_line|#define PM3RD_CheckControl_PIXEL_ENABLED&t;&t;(1&lt;&lt;0)
DECL|macro|PM3RD_CheckControl_LUT_DISABLED
mdefine_line|#define PM3RD_CheckControl_LUT_DISABLED&t;&t;&t;(0&lt;&lt;1)
DECL|macro|PM3RD_CheckControl_LUT_ENABLED
mdefine_line|#define PM3RD_CheckControl_LUT_ENABLED&t;&t;&t;(1&lt;&lt;1)
DECL|macro|PM3RD_CheckPixelRed
mdefine_line|#define PM3RD_CheckPixelRed&t;&t;&t;&t;&t;0x019
DECL|macro|PM3RD_CheckPixelGreen
mdefine_line|#define PM3RD_CheckPixelGreen&t;&t;&t;&t;&t;0x01a
DECL|macro|PM3RD_CheckPixelBlue
mdefine_line|#define PM3RD_CheckPixelBlue&t;&t;&t;&t;&t;0x01b
DECL|macro|PM3RD_CheckLUTRed
mdefine_line|#define PM3RD_CheckLUTRed&t;&t;&t;&t;&t;0x01c
DECL|macro|PM3RD_CheckLUTGreen
mdefine_line|#define PM3RD_CheckLUTGreen&t;&t;&t;&t;&t;0x01d
DECL|macro|PM3RD_CheckLUTBlue
mdefine_line|#define PM3RD_CheckLUTBlue&t;&t;&t;&t;&t;0x01e
DECL|macro|PM3RD_Scratch
mdefine_line|#define PM3RD_Scratch&t;&t;&t;&t;&t;&t;0x01f
DECL|macro|PM3RD_VideoOverlayControl
mdefine_line|#define PM3RD_VideoOverlayControl&t;&t;&t;&t;0x020
DECL|macro|PM3RD_VideoOverlayControl_DISABLE
mdefine_line|#define PM3RD_VideoOverlayControl_DISABLE               (0&lt;&lt;0)
DECL|macro|PM3RD_VideoOverlayControl_ENABLE
mdefine_line|#define PM3RD_VideoOverlayControl_ENABLE                (1&lt;&lt;0)
DECL|macro|PM3RD_VideoOverlayControl_MODE_MASK
mdefine_line|#define PM3RD_VideoOverlayControl_MODE_MASK             (3&lt;&lt;1)
DECL|macro|PM3RD_VideoOverlayControl_MODE_MAINKEY
mdefine_line|#define PM3RD_VideoOverlayControl_MODE_MAINKEY          (0&lt;&lt;1)
DECL|macro|PM3RD_VideoOverlayControl_MODE_OVERLAYKEY
mdefine_line|#define PM3RD_VideoOverlayControl_MODE_OVERLAYKEY       (1&lt;&lt;1)
DECL|macro|PM3RD_VideoOverlayControl_MODE_ALWAYS
mdefine_line|#define PM3RD_VideoOverlayControl_MODE_ALWAYS           (2&lt;&lt;1)
DECL|macro|PM3RD_VideoOverlayControl_MODE_BLEND
mdefine_line|#define PM3RD_VideoOverlayControl_MODE_BLEND            (3&lt;&lt;1)
DECL|macro|PM3RD_VideoOverlayControl_DIRECTCOLOR_DISABLED
mdefine_line|#define PM3RD_VideoOverlayControl_DIRECTCOLOR_DISABLED  (0&lt;&lt;3)
DECL|macro|PM3RD_VideoOverlayControl_DIRECTCOLOR_ENABLED
mdefine_line|#define PM3RD_VideoOverlayControl_DIRECTCOLOR_ENABLED   (1&lt;&lt;3)
DECL|macro|PM3RD_VideoOverlayControl_BLENDSRC_MAIN
mdefine_line|#define PM3RD_VideoOverlayControl_BLENDSRC_MAIN         (0&lt;&lt;4)
DECL|macro|PM3RD_VideoOverlayControl_BLENDSRC_REGISTER
mdefine_line|#define PM3RD_VideoOverlayControl_BLENDSRC_REGISTER     (1&lt;&lt;4)
DECL|macro|PM3RD_VideoOverlayControl_KEY_COLOR
mdefine_line|#define PM3RD_VideoOverlayControl_KEY_COLOR             (0&lt;&lt;5)
DECL|macro|PM3RD_VideoOverlayControl_KEY_ALPHA
mdefine_line|#define PM3RD_VideoOverlayControl_KEY_ALPHA             (1&lt;&lt;5)
DECL|macro|PM3RD_VideoOverlayXStartLow
mdefine_line|#define PM3RD_VideoOverlayXStartLow&t;&t;&t;&t;0x021
DECL|macro|PM3RD_VideoOverlayXStartHigh
mdefine_line|#define PM3RD_VideoOverlayXStartHigh&t;&t;&t;&t;0x022
DECL|macro|PM3RD_VideoOverlayYStartLow
mdefine_line|#define PM3RD_VideoOverlayYStartLow&t;&t;&t;&t;0x023
DECL|macro|PM3RD_VideoOverlayYStartHigh
mdefine_line|#define PM3RD_VideoOverlayYStartHigh&t;&t;&t;&t;0x024
DECL|macro|PM3RD_VideoOverlayXEndLow
mdefine_line|#define PM3RD_VideoOverlayXEndLow&t;&t;&t;&t;0x025
DECL|macro|PM3RD_VideoOverlayXEndHigh
mdefine_line|#define PM3RD_VideoOverlayXEndHigh&t;&t;&t;&t;0x026
DECL|macro|PM3RD_VideoOverlayYEndLow
mdefine_line|#define PM3RD_VideoOverlayYEndLow&t;&t;&t;&t;0x027
DECL|macro|PM3RD_VideoOverlayYEndHigh
mdefine_line|#define PM3RD_VideoOverlayYEndHigh&t;&t;&t;&t;0x028
DECL|macro|PM3RD_VideoOverlayKeyR
mdefine_line|#define PM3RD_VideoOverlayKeyR&t;&t;&t;&t;&t;0x029
DECL|macro|PM3RD_VideoOverlayKeyG
mdefine_line|#define PM3RD_VideoOverlayKeyG&t;&t;&t;&t;&t;0x02a
DECL|macro|PM3RD_VideoOverlayKeyB
mdefine_line|#define PM3RD_VideoOverlayKeyB&t;&t;&t;&t;&t;0x02b
DECL|macro|PM3RD_VideoOverlayBlend
mdefine_line|#define PM3RD_VideoOverlayBlend&t;&t;&t;&t;&t;0x02c
DECL|macro|PM3RD_VideoOverlayBlend_FACTOR_0_PERCENT
mdefine_line|#define PM3RD_VideoOverlayBlend_FACTOR_0_PERCENT        (0&lt;&lt;6)
DECL|macro|PM3RD_VideoOverlayBlend_FACTOR_25_PERCENT
mdefine_line|#define PM3RD_VideoOverlayBlend_FACTOR_25_PERCENT       (1&lt;&lt;6)
DECL|macro|PM3RD_VideoOverlayBlend_FACTOR_75_PERCENT
mdefine_line|#define PM3RD_VideoOverlayBlend_FACTOR_75_PERCENT       (2&lt;&lt;6)
DECL|macro|PM3RD_VideoOverlayBlend_FACTOR_100_PERCENT
mdefine_line|#define PM3RD_VideoOverlayBlend_FACTOR_100_PERCENT      (3&lt;&lt;6)
DECL|macro|PM3RD_DClkSetup1
mdefine_line|#define PM3RD_DClkSetup1&t;&t;&t;&t;&t;0x1f0
DECL|macro|PM3RD_DClkSetup2
mdefine_line|#define PM3RD_DClkSetup2&t;&t;&t;&t;&t;0x1f1
DECL|macro|PM3RD_KClkSetup1
mdefine_line|#define PM3RD_KClkSetup1&t;&t;&t;&t;&t;0x1f2
DECL|macro|PM3RD_KClkSetup2
mdefine_line|#define PM3RD_KClkSetup2&t;&t;&t;&t;&t;0x1f3
DECL|macro|PM3RD_DClkControl
mdefine_line|#define PM3RD_DClkControl&t;&t;&t;&t;&t;0x200
DECL|macro|PM3RD_DClkControl_SOURCE_PLL
mdefine_line|#define PM3RD_DClkControl_SOURCE_PLL&t;&t;&t;(0&lt;&lt;4)
DECL|macro|PM3RD_DClkControl_SOURCE_VSA
mdefine_line|#define PM3RD_DClkControl_SOURCE_VSA&t;&t;&t;(1&lt;&lt;4)
DECL|macro|PM3RD_DClkControl_SOURCE_VSB
mdefine_line|#define PM3RD_DClkControl_SOURCE_VSB&t;&t;&t;(2&lt;&lt;4)
DECL|macro|PM3RD_DClkControl_SOURCE_EXT
mdefine_line|#define PM3RD_DClkControl_SOURCE_EXT&t;&t;&t;(3&lt;&lt;4)
DECL|macro|PM3RD_DClkControl_STATE_RUN
mdefine_line|#define PM3RD_DClkControl_STATE_RUN&t;&t;&t;(2&lt;&lt;2)
DECL|macro|PM3RD_DClkControl_STATE_HIGH
mdefine_line|#define PM3RD_DClkControl_STATE_HIGH&t;&t;&t;(1&lt;&lt;2)
DECL|macro|PM3RD_DClkControl_STATE_LOW
mdefine_line|#define PM3RD_DClkControl_STATE_LOW&t;&t;&t;(0&lt;&lt;2)
DECL|macro|PM3RD_DClkControl_LOCKED
mdefine_line|#define PM3RD_DClkControl_LOCKED&t;&t;&t;(1&lt;&lt;1)
DECL|macro|PM3RD_DClkControl_NOT_LOCKED
mdefine_line|#define PM3RD_DClkControl_NOT_LOCKED&t;&t;&t;(0&lt;&lt;1)
DECL|macro|PM3RD_DClkControl_ENABLE
mdefine_line|#define PM3RD_DClkControl_ENABLE&t;&t;&t;(1&lt;&lt;0)
DECL|macro|PM3RD_DClkControl_DISABLE
mdefine_line|#define PM3RD_DClkControl_DISABLE&t;&t;&t;(0&lt;&lt;0)
DECL|macro|PM3RD_DClk0PreScale
mdefine_line|#define PM3RD_DClk0PreScale&t;&t;&t;&t;&t;0x201
DECL|macro|PM3RD_DClk0FeedbackScale
mdefine_line|#define PM3RD_DClk0FeedbackScale&t;&t;&t;&t;0x202
DECL|macro|PM3RD_DClk0PostScale
mdefine_line|#define PM3RD_DClk0PostScale&t;&t;&t;&t;&t;0x203
DECL|macro|PM3_REF_CLOCK
mdefine_line|#define PM3_REF_CLOCK                                   14318
DECL|macro|PM3RD_DClk1PreScale
mdefine_line|#define PM3RD_DClk1PreScale&t;&t;&t;&t;&t;0x204
DECL|macro|PM3RD_DClk1FeedbackScale
mdefine_line|#define PM3RD_DClk1FeedbackScale&t;&t;&t;&t;0x205
DECL|macro|PM3RD_DClk1PostScale
mdefine_line|#define PM3RD_DClk1PostScale&t;&t;&t;&t;&t;0x206
DECL|macro|PM3RD_DClk2PreScale
mdefine_line|#define PM3RD_DClk2PreScale&t;&t;&t;&t;&t;0x207
DECL|macro|PM3RD_DClk2FeedbackScale
mdefine_line|#define PM3RD_DClk2FeedbackScale&t;&t;&t;&t;0x208
DECL|macro|PM3RD_DClk2PostScale
mdefine_line|#define PM3RD_DClk2PostScale&t;&t;&t;&t;&t;0x209
DECL|macro|PM3RD_DClk3PreScale
mdefine_line|#define PM3RD_DClk3PreScale&t;&t;&t;&t;&t;0x20a
DECL|macro|PM3RD_DClk3FeedbackScale
mdefine_line|#define PM3RD_DClk3FeedbackScale&t;&t;&t;&t;0x20b
DECL|macro|PM3RD_DClk3PostScale
mdefine_line|#define PM3RD_DClk3PostScale&t;&t;&t;&t;&t;0x20c
DECL|macro|PM3RD_KClkControl
mdefine_line|#define PM3RD_KClkControl&t;&t;&t;&t;&t;0x20d
DECL|macro|PM3RD_KClkControl_DISABLE
mdefine_line|#define PM3RD_KClkControl_DISABLE&t;&t;&t;(0&lt;&lt;0)
DECL|macro|PM3RD_KClkControl_ENABLE
mdefine_line|#define PM3RD_KClkControl_ENABLE&t;&t;&t;(1&lt;&lt;0)
DECL|macro|PM3RD_KClkControl_NOT_LOCKED
mdefine_line|#define PM3RD_KClkControl_NOT_LOCKED&t;&t;&t;(0&lt;&lt;1)
DECL|macro|PM3RD_KClkControl_LOCKED
mdefine_line|#define PM3RD_KClkControl_LOCKED&t;&t;&t;(1&lt;&lt;1)
DECL|macro|PM3RD_KClkControl_STATE_LOW
mdefine_line|#define PM3RD_KClkControl_STATE_LOW&t;&t;&t;(0&lt;&lt;2)
DECL|macro|PM3RD_KClkControl_STATE_HIGH
mdefine_line|#define PM3RD_KClkControl_STATE_HIGH&t;&t;&t;(1&lt;&lt;2)
DECL|macro|PM3RD_KClkControl_STATE_RUN
mdefine_line|#define PM3RD_KClkControl_STATE_RUN&t;&t;&t;(2&lt;&lt;2)
DECL|macro|PM3RD_KClkControl_STATE_LOW_POWER
mdefine_line|#define PM3RD_KClkControl_STATE_LOW_POWER&t;&t;(3&lt;&lt;2)
DECL|macro|PM3RD_KClkControl_SOURCE_PCLK
mdefine_line|#define PM3RD_KClkControl_SOURCE_PCLK&t;&t;&t;(0&lt;&lt;4)
DECL|macro|PM3RD_KClkControl_SOURCE_HALF_PCLK
mdefine_line|#define PM3RD_KClkControl_SOURCE_HALF_PCLK&t;&t;(1&lt;&lt;4)
DECL|macro|PM3RD_KClkControl_SOURCE_PLL
mdefine_line|#define PM3RD_KClkControl_SOURCE_PLL&t;&t;&t;(2&lt;&lt;4)
DECL|macro|PM3RD_KClkPreScale
mdefine_line|#define PM3RD_KClkPreScale&t;&t;&t;&t;&t;0x20e
DECL|macro|PM3RD_KClkFeedbackScale
mdefine_line|#define PM3RD_KClkFeedbackScale&t;&t;&t;&t;&t;0x20f
DECL|macro|PM3RD_KClkPostScale
mdefine_line|#define PM3RD_KClkPostScale&t;&t;&t;&t;&t;0x210
DECL|macro|PM3RD_MClkControl
mdefine_line|#define PM3RD_MClkControl&t;&t;&t;&t;&t;0x211
DECL|macro|PM3RD_MClkControl_DISABLE
mdefine_line|#define PM3RD_MClkControl_DISABLE&t;&t;&t;(0&lt;&lt;0)
DECL|macro|PM3RD_MClkControl_ENABLE
mdefine_line|#define PM3RD_MClkControl_ENABLE&t;&t;&t;(1&lt;&lt;0)
DECL|macro|PM3RD_MClkControl_NOT_LOCKED
mdefine_line|#define PM3RD_MClkControl_NOT_LOCKED&t;&t;&t;(0&lt;&lt;1)
DECL|macro|PM3RD_MClkControl_LOCKED
mdefine_line|#define PM3RD_MClkControl_LOCKED&t;&t;&t;(1&lt;&lt;1)
DECL|macro|PM3RD_MClkControl_STATE_LOW
mdefine_line|#define PM3RD_MClkControl_STATE_LOW&t;&t;&t;(0&lt;&lt;2)
DECL|macro|PM3RD_MClkControl_STATE_HIGH
mdefine_line|#define PM3RD_MClkControl_STATE_HIGH&t;&t;&t;(1&lt;&lt;2)
DECL|macro|PM3RD_MClkControl_STATE_RUN
mdefine_line|#define PM3RD_MClkControl_STATE_RUN&t;&t;&t;(2&lt;&lt;2)
DECL|macro|PM3RD_MClkControl_STATE_LOW_POWER
mdefine_line|#define PM3RD_MClkControl_STATE_LOW_POWER&t;&t;(3&lt;&lt;2)
DECL|macro|PM3RD_MClkControl_SOURCE_PCLK
mdefine_line|#define PM3RD_MClkControl_SOURCE_PCLK&t;&t;&t;(0&lt;&lt;4)
DECL|macro|PM3RD_MClkControl_SOURCE_HALF_PCLK
mdefine_line|#define PM3RD_MClkControl_SOURCE_HALF_PCLK&t;&t;(1&lt;&lt;4)
DECL|macro|PM3RD_MClkControl_SOURCE_HALF_EXT
mdefine_line|#define PM3RD_MClkControl_SOURCE_HALF_EXT&t;&t;(3&lt;&lt;4)
DECL|macro|PM3RD_MClkControl_SOURCE_EXT
mdefine_line|#define PM3RD_MClkControl_SOURCE_EXT&t;&t;&t;(4&lt;&lt;4)
DECL|macro|PM3RD_MClkControl_SOURCE_HALF_KCLK
mdefine_line|#define PM3RD_MClkControl_SOURCE_HALF_KCLK&t;&t;(5&lt;&lt;4)
DECL|macro|PM3RD_MClkControl_SOURCE_KCLK
mdefine_line|#define PM3RD_MClkControl_SOURCE_KCLK&t;&t;&t;(6&lt;&lt;4)
DECL|macro|PM3RD_MClkPreScale
mdefine_line|#define PM3RD_MClkPreScale&t;&t;&t;&t;&t;0x212
DECL|macro|PM3RD_MClkFeedbackScale
mdefine_line|#define PM3RD_MClkFeedbackScale&t;&t;&t;&t;&t;0x213
DECL|macro|PM3RD_MClkPostScale
mdefine_line|#define PM3RD_MClkPostScale&t;&t;&t;&t;&t;0x214
DECL|macro|PM3RD_SClkControl
mdefine_line|#define PM3RD_SClkControl&t;&t;&t;&t;&t;0x215
DECL|macro|PM3RD_SClkControl_DISABLE
mdefine_line|#define PM3RD_SClkControl_DISABLE&t;&t;&t;(0&lt;&lt;0)
DECL|macro|PM3RD_SClkControl_ENABLE
mdefine_line|#define PM3RD_SClkControl_ENABLE&t;&t;&t;(1&lt;&lt;0)
DECL|macro|PM3RD_SClkControl_NOT_LOCKED
mdefine_line|#define PM3RD_SClkControl_NOT_LOCKED&t;&t;&t;(0&lt;&lt;1)
DECL|macro|PM3RD_SClkControl_LOCKED
mdefine_line|#define PM3RD_SClkControl_LOCKED&t;&t;&t;(1&lt;&lt;1)
DECL|macro|PM3RD_SClkControl_STATE_LOW
mdefine_line|#define PM3RD_SClkControl_STATE_LOW&t;&t;&t;(0&lt;&lt;2)
DECL|macro|PM3RD_SClkControl_STATE_HIGH
mdefine_line|#define PM3RD_SClkControl_STATE_HIGH&t;&t;&t;(1&lt;&lt;2)
DECL|macro|PM3RD_SClkControl_STATE_RUN
mdefine_line|#define PM3RD_SClkControl_STATE_RUN&t;&t;&t;(2&lt;&lt;2)
DECL|macro|PM3RD_SClkControl_STATE_LOW_POWER
mdefine_line|#define PM3RD_SClkControl_STATE_LOW_POWER&t;&t;(3&lt;&lt;2)
DECL|macro|PM3RD_SClkControl_SOURCE_PCLK
mdefine_line|#define PM3RD_SClkControl_SOURCE_PCLK&t;&t;&t;(0&lt;&lt;4)
DECL|macro|PM3RD_SClkControl_SOURCE_HALF_PCLK
mdefine_line|#define PM3RD_SClkControl_SOURCE_HALF_PCLK&t;&t;(1&lt;&lt;4)
DECL|macro|PM3RD_SClkControl_SOURCE_HALF_EXT
mdefine_line|#define PM3RD_SClkControl_SOURCE_HALF_EXT&t;&t;(3&lt;&lt;4)
DECL|macro|PM3RD_SClkControl_SOURCE_EXT
mdefine_line|#define PM3RD_SClkControl_SOURCE_EXT&t;&t;&t;(4&lt;&lt;4)
DECL|macro|PM3RD_SClkControl_SOURCE_HALF_KCLK
mdefine_line|#define PM3RD_SClkControl_SOURCE_HALF_KCLK&t;&t;(5&lt;&lt;4)
DECL|macro|PM3RD_SClkControl_SOURCE_KCLK
mdefine_line|#define PM3RD_SClkControl_SOURCE_KCLK&t;&t;&t;(6&lt;&lt;4)
DECL|macro|PM3RD_SClkPreScale
mdefine_line|#define PM3RD_SClkPreScale&t;&t;&t;&t;&t;0x216
DECL|macro|PM3RD_SClkFeedbackScale
mdefine_line|#define PM3RD_SClkFeedbackScale&t;&t;&t;&t;&t;0x217
DECL|macro|PM3RD_SClkPostScale
mdefine_line|#define PM3RD_SClkPostScale&t;&t;&t;&t;&t;0x218
DECL|macro|PM3RD_CursorPalette
mdefine_line|#define PM3RD_CursorPalette(p)&t;&t;&t;&t;&t;(0x303+(p))
DECL|macro|PM3RD_CursorPattern
mdefine_line|#define PM3RD_CursorPattern(p)&t;&t;&t;&t;&t;(0x400+(p))
multiline_comment|/******************************************************&n;*  GLINT Permedia3 Video Streaming Registers (0x5000) *&n;*******************************************************/
DECL|macro|PM3VSConfiguration
mdefine_line|#define PM3VSConfiguration&t;&t;&t;&t;&t;0x5800
multiline_comment|/**********************************************&n;*  GLINT Permedia3 Core Registers (0x8000+)   *&n;***********************************************/
DECL|macro|PM3AALineWidth
mdefine_line|#define PM3AALineWidth&t;&t;&t;&t;&t;&t;0x94c0
DECL|macro|PM3AAPointsize
mdefine_line|#define PM3AAPointsize&t;&t;&t;&t;&t;&t;0x94a0
DECL|macro|PM3AlphaBlendAlphaMode
mdefine_line|#define PM3AlphaBlendAlphaMode&t;&t;&t;&t;&t;0xafa8
DECL|macro|PM3AlphaBlendAlphaModeAnd
mdefine_line|#define PM3AlphaBlendAlphaModeAnd&t;&t;&t;&t;0xad30
DECL|macro|PM3AlphaBlendAlphaModeOr
mdefine_line|#define PM3AlphaBlendAlphaModeOr&t;&t;&t;&t;0xad38
DECL|macro|PM3AlphaBlendColorMode
mdefine_line|#define PM3AlphaBlendColorMode&t;&t;&t;&t;&t;0xafa0
DECL|macro|PM3AlphaBlendColorModeAnd
mdefine_line|#define PM3AlphaBlendColorModeAnd&t;&t;&t;&t;0xacb0
DECL|macro|PM3AlphaBlendColorModeOr
mdefine_line|#define PM3AlphaBlendColorModeOr&t;&t;&t;&t;0xacb8
DECL|macro|PM3AlphaDestColor
mdefine_line|#define PM3AlphaDestColor&t;&t;&t;&t;&t;0xaf88
DECL|macro|PM3AlphaSourceColor
mdefine_line|#define PM3AlphaSourceColor&t;&t;&t;&t;&t;0xaf80
DECL|macro|PM3AlphaTestMode
mdefine_line|#define PM3AlphaTestMode&t;&t;&t;&t;&t;0x8800
DECL|macro|PM3AlphaTestModeAnd
mdefine_line|#define PM3AlphaTestModeAnd&t;&t;&t;&t;&t;0xabf0
DECL|macro|PM3AlphaTestModeOr
mdefine_line|#define PM3AlphaTestModeOr&t;&t;&t;&t;&t;0xabf8
DECL|macro|PM3AntialiasMode
mdefine_line|#define PM3AntialiasMode&t;&t;&t;&t;&t;0x8808
DECL|macro|PM3AntialiasModeAnd
mdefine_line|#define PM3AntialiasModeAnd&t;&t;&t;&t;&t;0xac00
DECL|macro|PM3AntialiasModeOr
mdefine_line|#define PM3AntialiasModeOr&t;&t;&t;&t;&t;0xac08
multiline_comment|/* ... */
DECL|macro|PM3BackgroundColor
mdefine_line|#define PM3BackgroundColor&t;&t;&t;&t;&t;0xb0c8
multiline_comment|/* ... */
DECL|macro|PM3ColorDDAMode
mdefine_line|#define PM3ColorDDAMode&t;&t;&t;&t;&t;&t;0x87e0
DECL|macro|PM3ColorDDAModeAnd
mdefine_line|#define PM3ColorDDAModeAnd&t;&t;&t;&t;&t;0xabe0
DECL|macro|PM3ColorDDAModeOr
mdefine_line|#define PM3ColorDDAModeOr&t;&t;&t;&t;&t;0xabe8
DECL|macro|PM3CommandInterrupt
mdefine_line|#define PM3CommandInterrupt&t;&t;&t;&t;&t;0xa990
DECL|macro|PM3ConstantColorDDA
mdefine_line|#define PM3ConstantColorDDA&t;&t;&t;&t;&t;0xafb0
DECL|macro|PM3ConstantColorDDA_R
mdefine_line|#define PM3ConstantColorDDA_R(r)&t;&t;((r)&amp;0xff)
DECL|macro|PM3ConstantColorDDA_G
mdefine_line|#define PM3ConstantColorDDA_G(g)&t;&t;(((g)&amp;0xff)&lt;&lt;8)
DECL|macro|PM3ConstantColorDDA_B
mdefine_line|#define PM3ConstantColorDDA_B(b)&t;&t;(((b)&amp;0xff)&lt;&lt;16)
DECL|macro|PM3ConstantColorDDA_A
mdefine_line|#define PM3ConstantColorDDA_A(a)&t;&t;(((a)&amp;0xff)&lt;&lt;24)
DECL|macro|PM3ContextData
mdefine_line|#define PM3ContextData&t;&t;&t;&t;&t;&t;0x8dd0
DECL|macro|PM3ContextDump
mdefine_line|#define PM3ContextDump&t;&t;&t;&t;&t;&t;0x8dc0
DECL|macro|PM3ContextRestore
mdefine_line|#define PM3ContextRestore&t;&t;&t;&t;&t;0x8dc8
DECL|macro|PM3Continue
mdefine_line|#define PM3Continue&t;&t;&t;&t;&t;&t;0x8058
DECL|macro|PM3ContinueNewDom
mdefine_line|#define PM3ContinueNewDom&t;&t;&t;&t;&t;0x8048
DECL|macro|PM3ContinueNewLine
mdefine_line|#define PM3ContinueNewLine&t;&t;&t;&t;&t;0x8040
DECL|macro|PM3ContinueNewSub
mdefine_line|#define PM3ContinueNewSub&t;&t;&t;&t;&t;0x8050
DECL|macro|PM3Count
mdefine_line|#define PM3Count&t;&t;&t;&t;&t;&t;0x8030
multiline_comment|/* ... */
DECL|macro|PM3DeltaControl
mdefine_line|#define PM3DeltaControl&t;&t;&t;&t;&t;&t;0x9350
DECL|macro|PM3DeltaControlAnd
mdefine_line|#define PM3DeltaControlAnd&t;&t;&t;&t;&t;0xab20
DECL|macro|PM3DeltaControlOr
mdefine_line|#define PM3DeltaControlOr&t;&t;&t;&t;&t;0xab28
DECL|macro|PM3DeltaMode
mdefine_line|#define PM3DeltaMode&t;&t;&t;&t;&t;&t;0x9300
DECL|macro|PM3DeltaModeAnd
mdefine_line|#define PM3DeltaModeAnd&t;&t;&t;&t;&t;&t;0xaad0
DECL|macro|PM3DeltaModeOr
mdefine_line|#define PM3DeltaModeOr&t;&t;&t;&t;&t;&t;0xaad8
multiline_comment|/* ... */
DECL|macro|PM3DitherMode
mdefine_line|#define PM3DitherMode&t;&t;&t;&t;&t;&t;0x8818
DECL|macro|PM3DitherModeAnd
mdefine_line|#define PM3DitherModeAnd&t;&t;&t;&t;&t;0xacd0
DECL|macro|PM3DitherModeOr
mdefine_line|#define PM3DitherModeOr&t;&t;&t;&t;&t;&t;0xacd8
multiline_comment|/* ... */
DECL|macro|PM3dXDom
mdefine_line|#define PM3dXDom&t;&t;&t;&t;&t;&t;0x8008
DECL|macro|PM3dXSub
mdefine_line|#define PM3dXSub&t;&t;&t;&t;&t;&t;0x8018
DECL|macro|PM3dY
mdefine_line|#define PM3dY&t;&t;&t;&t;&t;&t;&t;0x8028
multiline_comment|/* ... */
DECL|macro|PM3FBBlockColor
mdefine_line|#define PM3FBBlockColor&t;&t;&t;&t;&t;&t;0x8ac8
DECL|macro|PM3FBBlockColor0
mdefine_line|#define PM3FBBlockColor0&t;&t;&t;&t;&t;0xb060
DECL|macro|PM3FBBlockColor1
mdefine_line|#define PM3FBBlockColor1&t;&t;&t;&t;&t;0xb068
DECL|macro|PM3FBBlockColor2
mdefine_line|#define PM3FBBlockColor2&t;&t;&t;&t;&t;0xb070
DECL|macro|PM3FBBlockColor3
mdefine_line|#define PM3FBBlockColor3&t;&t;&t;&t;&t;0xb078
DECL|macro|PM3FBBlockColorBack
mdefine_line|#define PM3FBBlockColorBack&t;&t;&t;&t;&t;0xb0a0
DECL|macro|PM3FBBlockColorBack0
mdefine_line|#define PM3FBBlockColorBack0&t;&t;&t;&t;&t;0xb080
DECL|macro|PM3FBBlockColorBack1
mdefine_line|#define PM3FBBlockColorBack1&t;&t;&t;&t;&t;0xb088
DECL|macro|PM3FBBlockColorBack2
mdefine_line|#define PM3FBBlockColorBack2&t;&t;&t;&t;&t;0xb090
DECL|macro|PM3FBBlockColorBack3
mdefine_line|#define PM3FBBlockColorBack3&t;&t;&t;&t;&t;0xb098
DECL|macro|PM3FBColor
mdefine_line|#define PM3FBColor&t;&t;&t;&t;&t;&t;0x8a98
DECL|macro|PM3FBDestReadBufferAddr0
mdefine_line|#define PM3FBDestReadBufferAddr0&t;&t;&t;&t;0xae80
DECL|macro|PM3FBDestReadBufferAddr1
mdefine_line|#define PM3FBDestReadBufferAddr1&t;&t;&t;&t;0xae88
DECL|macro|PM3FBDestReadBufferAddr2
mdefine_line|#define PM3FBDestReadBufferAddr2&t;&t;&t;&t;0xae90
DECL|macro|PM3FBDestReadBufferAddr3
mdefine_line|#define PM3FBDestReadBufferAddr3&t;&t;&t;&t;0xae98
DECL|macro|PM3FBDestReadBufferOffset0
mdefine_line|#define PM3FBDestReadBufferOffset0&t;&t;&t;&t;0xaea0
DECL|macro|PM3FBDestReadBufferOffset1
mdefine_line|#define PM3FBDestReadBufferOffset1&t;&t;&t;&t;0xaea8
DECL|macro|PM3FBDestReadBufferOffset2
mdefine_line|#define PM3FBDestReadBufferOffset2&t;&t;&t;&t;0xaeb0
DECL|macro|PM3FBDestReadBufferOffset3
mdefine_line|#define PM3FBDestReadBufferOffset3&t;&t;&t;&t;0xaeb8
DECL|macro|PM3FBDestReadBufferOffset_XOffset
mdefine_line|#define PM3FBDestReadBufferOffset_XOffset(x)&t;((x)&amp;0xffff)
DECL|macro|PM3FBDestReadBufferOffset_YOffset
mdefine_line|#define PM3FBDestReadBufferOffset_YOffset(y)&t;(((y)&amp;0xffff)&lt;&lt;16)
DECL|macro|PM3FBDestReadBufferWidth0
mdefine_line|#define PM3FBDestReadBufferWidth0&t;&t;&t;&t;0xaec0
DECL|macro|PM3FBDestReadBufferWidth1
mdefine_line|#define PM3FBDestReadBufferWidth1&t;&t;&t;&t;0xaec8
DECL|macro|PM3FBDestReadBufferWidth2
mdefine_line|#define PM3FBDestReadBufferWidth2&t;&t;&t;&t;0xaed0
DECL|macro|PM3FBDestReadBufferWidth3
mdefine_line|#define PM3FBDestReadBufferWidth3&t;&t;&t;&t;0xaed8
DECL|macro|PM3FBDestReadBufferWidth_Width
mdefine_line|#define PM3FBDestReadBufferWidth_Width(w)&t;((w)&amp;0x0fff)
DECL|macro|PM3FBDestReadEnables
mdefine_line|#define PM3FBDestReadEnables&t;&t;&t;&t;&t;0xaee8
DECL|macro|PM3FBDestReadEnablesAnd
mdefine_line|#define PM3FBDestReadEnablesAnd&t;&t;&t;&t;&t;0xad20
DECL|macro|PM3FBDestReadEnablesOr
mdefine_line|#define PM3FBDestReadEnablesOr&t;&t;&t;&t;&t;0xad28
DECL|macro|PM3FBDestReadEnables_E
mdefine_line|#define PM3FBDestReadEnables_E(e)&t;&t;((e)&amp;0xff)
DECL|macro|PM3FBDestReadEnables_E0
mdefine_line|#define PM3FBDestReadEnables_E0&t;&t;&t;&t;1&lt;&lt;0
DECL|macro|PM3FBDestReadEnables_E1
mdefine_line|#define PM3FBDestReadEnables_E1&t;&t;&t;&t;1&lt;&lt;1
DECL|macro|PM3FBDestReadEnables_E2
mdefine_line|#define PM3FBDestReadEnables_E2&t;&t;&t;&t;1&lt;&lt;2
DECL|macro|PM3FBDestReadEnables_E3
mdefine_line|#define PM3FBDestReadEnables_E3&t;&t;&t;&t;1&lt;&lt;3
DECL|macro|PM3FBDestReadEnables_E4
mdefine_line|#define PM3FBDestReadEnables_E4&t;&t;&t;&t;1&lt;&lt;4
DECL|macro|PM3FBDestReadEnables_E5
mdefine_line|#define PM3FBDestReadEnables_E5&t;&t;&t;&t;1&lt;&lt;5
DECL|macro|PM3FBDestReadEnables_E6
mdefine_line|#define PM3FBDestReadEnables_E6&t;&t;&t;&t;1&lt;&lt;6
DECL|macro|PM3FBDestReadEnables_E7
mdefine_line|#define PM3FBDestReadEnables_E7&t;&t;&t;&t;1&lt;&lt;7
DECL|macro|PM3FBDestReadEnables_R
mdefine_line|#define PM3FBDestReadEnables_R(r)&t;&t;(((r)&amp;0xff)&lt;&lt;8)
DECL|macro|PM3FBDestReadEnables_R0
mdefine_line|#define PM3FBDestReadEnables_R0&t;&t;&t;&t;1&lt;&lt;8
DECL|macro|PM3FBDestReadEnables_R1
mdefine_line|#define PM3FBDestReadEnables_R1&t;&t;&t;&t;1&lt;&lt;9
DECL|macro|PM3FBDestReadEnables_R2
mdefine_line|#define PM3FBDestReadEnables_R2&t;&t;&t;&t;1&lt;&lt;10
DECL|macro|PM3FBDestReadEnables_R3
mdefine_line|#define PM3FBDestReadEnables_R3&t;&t;&t;&t;1&lt;&lt;11
DECL|macro|PM3FBDestReadEnables_R4
mdefine_line|#define PM3FBDestReadEnables_R4&t;&t;&t;&t;1&lt;&lt;12
DECL|macro|PM3FBDestReadEnables_R5
mdefine_line|#define PM3FBDestReadEnables_R5&t;&t;&t;&t;1&lt;&lt;13
DECL|macro|PM3FBDestReadEnables_R6
mdefine_line|#define PM3FBDestReadEnables_R6&t;&t;&t;&t;1&lt;&lt;14
DECL|macro|PM3FBDestReadEnables_R7
mdefine_line|#define PM3FBDestReadEnables_R7&t;&t;&t;&t;1&lt;&lt;15
DECL|macro|PM3FBDestReadEnables_ReferenceAlpha
mdefine_line|#define PM3FBDestReadEnables_ReferenceAlpha(a)&t;(((a)&amp;0xff)&lt;&lt;24)
DECL|macro|PM3FBDestReadMode
mdefine_line|#define PM3FBDestReadMode&t;&t;&t;&t;&t;0xaee0
DECL|macro|PM3FBDestReadModeAnd
mdefine_line|#define PM3FBDestReadModeAnd&t;&t;&t;&t;&t;0xac90
DECL|macro|PM3FBDestReadModeOr
mdefine_line|#define PM3FBDestReadModeOr&t;&t;&t;&t;&t;0xac98
DECL|macro|PM3FBDestReadMode_ReadDisable
mdefine_line|#define PM3FBDestReadMode_ReadDisable&t;&t;&t;0&lt;&lt;0
DECL|macro|PM3FBDestReadMode_ReadEnable
mdefine_line|#define PM3FBDestReadMode_ReadEnable&t;&t;&t;1&lt;&lt;0
DECL|macro|PM3FBDestReadMode_StripePitch
mdefine_line|#define PM3FBDestReadMode_StripePitch(sp)&t;(((sp)&amp;0x7)&lt;&lt;2
DECL|macro|PM3FBDestReadMode_StripeHeight
mdefine_line|#define PM3FBDestReadMode_StripeHeight(sh)&t;(((sh)&amp;0x7)&lt;&lt;7
DECL|macro|PM3FBDestReadMode_Enable0
mdefine_line|#define PM3FBDestReadMode_Enable0&t;&t;&t;1&lt;&lt;8
DECL|macro|PM3FBDestReadMode_Enable1
mdefine_line|#define PM3FBDestReadMode_Enable1&t;&t;&t;1&lt;&lt;9
DECL|macro|PM3FBDestReadMode_Enable2
mdefine_line|#define PM3FBDestReadMode_Enable2&t;&t;&t;1&lt;&lt;10
DECL|macro|PM3FBDestReadMode_Enable3
mdefine_line|#define PM3FBDestReadMode_Enable3&t;&t;&t;1&lt;&lt;11
DECL|macro|PM3FBDestReadMode_Layout0
mdefine_line|#define PM3FBDestReadMode_Layout0(l)&t;&t;(((l)&amp;0x3)&lt;&lt;12
DECL|macro|PM3FBDestReadMode_Layout1
mdefine_line|#define PM3FBDestReadMode_Layout1(l)&t;&t;(((l)&amp;0x3)&lt;&lt;14
DECL|macro|PM3FBDestReadMode_Layout2
mdefine_line|#define PM3FBDestReadMode_Layout2(l)&t;&t;(((l)&amp;0x3)&lt;&lt;16
DECL|macro|PM3FBDestReadMode_Layout3
mdefine_line|#define PM3FBDestReadMode_Layout3(l)&t;&t;(((l)&amp;0x3)&lt;&lt;18
DECL|macro|PM3FBDestReadMode_Origin0
mdefine_line|#define PM3FBDestReadMode_Origin0&t;&t;&t;1&lt;&lt;20
DECL|macro|PM3FBDestReadMode_Origin1
mdefine_line|#define PM3FBDestReadMode_Origin1&t;&t;&t;1&lt;&lt;21
DECL|macro|PM3FBDestReadMode_Origin2
mdefine_line|#define PM3FBDestReadMode_Origin2&t;&t;&t;1&lt;&lt;22
DECL|macro|PM3FBDestReadMode_Origin3
mdefine_line|#define PM3FBDestReadMode_Origin3&t;&t;&t;1&lt;&lt;23
DECL|macro|PM3FBDestReadMode_Blocking
mdefine_line|#define PM3FBDestReadMode_Blocking&t;&t;&t;1&lt;&lt;24
DECL|macro|PM3FBDestReadMode_UseReadEnabled
mdefine_line|#define PM3FBDestReadMode_UseReadEnabled&t;&t;1&lt;&lt;26
DECL|macro|PM3FBDestReadMode_AlphaFiltering
mdefine_line|#define PM3FBDestReadMode_AlphaFiltering&t;&t;1&lt;&lt;27
DECL|macro|PM3FBHardwareWriteMask
mdefine_line|#define PM3FBHardwareWriteMask&t;&t;&t;&t;&t;0x8ac0
DECL|macro|PM3FBSoftwareWriteMask
mdefine_line|#define PM3FBSoftwareWriteMask&t;&t;&t;&t;&t;0x8820
DECL|macro|PM3FBData
mdefine_line|#define PM3FBData&t;&t;&t;&t;&t;&t;0x8aa0
DECL|macro|PM3FBSourceData
mdefine_line|#define PM3FBSourceData&t;&t;&t;&t;&t;&t;0x8aa8
DECL|macro|PM3FBSourceReadBufferAddr
mdefine_line|#define PM3FBSourceReadBufferAddr&t;&t;&t;&t;0xaf08
DECL|macro|PM3FBSourceReadBufferOffset
mdefine_line|#define PM3FBSourceReadBufferOffset&t;&t;&t;&t;0xaf10
DECL|macro|PM3FBSourceReadBufferOffset_XOffset
mdefine_line|#define PM3FBSourceReadBufferOffset_XOffset(x)&t;((x)&amp;0xffff)
DECL|macro|PM3FBSourceReadBufferOffset_YOffset
mdefine_line|#define PM3FBSourceReadBufferOffset_YOffset(y)&t;(((y)&amp;0xffff)&lt;&lt;16)
DECL|macro|PM3FBSourceReadBufferWidth
mdefine_line|#define PM3FBSourceReadBufferWidth&t;&t;&t;&t;0xaf18
DECL|macro|PM3FBSourceReadBufferWidth_Width
mdefine_line|#define PM3FBSourceReadBufferWidth_Width(w)&t;((w)&amp;0x0fff)
DECL|macro|PM3FBSourceReadMode
mdefine_line|#define PM3FBSourceReadMode&t;&t;&t;&t;&t;0xaf00
DECL|macro|PM3FBSourceReadModeAnd
mdefine_line|#define PM3FBSourceReadModeAnd&t;&t;&t;&t;&t;0xaca0
DECL|macro|PM3FBSourceReadModeOr
mdefine_line|#define PM3FBSourceReadModeOr&t;&t;&t;&t;&t;0xaca8
DECL|macro|PM3FBSourceReadMode_ReadDisable
mdefine_line|#define PM3FBSourceReadMode_ReadDisable&t;&t;&t;(0&lt;&lt;0)
DECL|macro|PM3FBSourceReadMode_ReadEnable
mdefine_line|#define PM3FBSourceReadMode_ReadEnable&t;&t;&t;(1&lt;&lt;0)
DECL|macro|PM3FBSourceReadMode_StripePitch
mdefine_line|#define PM3FBSourceReadMode_StripePitch(sp)&t;(((sp)&amp;0x7)&lt;&lt;2
DECL|macro|PM3FBSourceReadMode_StripeHeight
mdefine_line|#define PM3FBSourceReadMode_StripeHeight(sh)&t;(((sh)&amp;0x7)&lt;&lt;7
DECL|macro|PM3FBSourceReadMode_Layout
mdefine_line|#define PM3FBSourceReadMode_Layout(l)&t;&t;(((l)&amp;0x3)&lt;&lt;8
DECL|macro|PM3FBSourceReadMode_Origin
mdefine_line|#define PM3FBSourceReadMode_Origin&t;&t;&t;1&lt;&lt;10
DECL|macro|PM3FBSourceReadMode_Blocking
mdefine_line|#define PM3FBSourceReadMode_Blocking&t;&t;&t;1&lt;&lt;11
DECL|macro|PM3FBSourceReadMode_UserTexelCoord
mdefine_line|#define PM3FBSourceReadMode_UserTexelCoord&t;&t;1&lt;&lt;13
DECL|macro|PM3FBSourceReadMode_WrapXEnable
mdefine_line|#define PM3FBSourceReadMode_WrapXEnable&t;&t;&t;1&lt;&lt;14
DECL|macro|PM3FBSourceReadMode_WrapYEnable
mdefine_line|#define PM3FBSourceReadMode_WrapYEnable&t;&t;&t;1&lt;&lt;15
DECL|macro|PM3FBSourceReadMode_WrapX
mdefine_line|#define PM3FBSourceReadMode_WrapX(w)&t;&t;(((w)&amp;0xf)&lt;&lt;16
DECL|macro|PM3FBSourceReadMode_WrapY
mdefine_line|#define PM3FBSourceReadMode_WrapY(w)&t;&t;(((w)&amp;0xf)&lt;&lt;20
DECL|macro|PM3FBSourceReadMode_ExternalSourceData
mdefine_line|#define PM3FBSourceReadMode_ExternalSourceData&t;&t;1&lt;&lt;24
DECL|macro|PM3FBWriteBufferAddr0
mdefine_line|#define PM3FBWriteBufferAddr0                                   0xb000
DECL|macro|PM3FBWriteBufferAddr1
mdefine_line|#define PM3FBWriteBufferAddr1                                   0xb008
DECL|macro|PM3FBWriteBufferAddr2
mdefine_line|#define PM3FBWriteBufferAddr2                                   0xb010
DECL|macro|PM3FBWriteBufferAddr3
mdefine_line|#define PM3FBWriteBufferAddr3                                   0xb018
DECL|macro|PM3FBWriteBufferOffset0
mdefine_line|#define PM3FBWriteBufferOffset0                                 0xb020
DECL|macro|PM3FBWriteBufferOffset1
mdefine_line|#define PM3FBWriteBufferOffset1                                 0xb028
DECL|macro|PM3FBWriteBufferOffset2
mdefine_line|#define PM3FBWriteBufferOffset2                                 0xb030
DECL|macro|PM3FBWriteBufferOffset3
mdefine_line|#define PM3FBWriteBufferOffset3                                 0xb038
DECL|macro|PM3FBWriteBufferOffset_XOffset
mdefine_line|#define PM3FBWriteBufferOffset_XOffset(x)&t;&t;((x)&amp;0xffff)
DECL|macro|PM3FBWriteBufferOffset_YOffset
mdefine_line|#define PM3FBWriteBufferOffset_YOffset(y)&t;&t;(((y)&amp;0xffff)&lt;&lt;16)
DECL|macro|PM3FBWriteBufferWidth0
mdefine_line|#define PM3FBWriteBufferWidth0                                  0xb040
DECL|macro|PM3FBWriteBufferWidth1
mdefine_line|#define PM3FBWriteBufferWidth1                                  0xb048
DECL|macro|PM3FBWriteBufferWidth2
mdefine_line|#define PM3FBWriteBufferWidth2                                  0xb050
DECL|macro|PM3FBWriteBufferWidth3
mdefine_line|#define PM3FBWriteBufferWidth3                                  0xb058
DECL|macro|PM3FBWriteBufferWidth_Width
mdefine_line|#define PM3FBWriteBufferWidth_Width(w)&t;&t;&t;((w)&amp;0x0fff)
DECL|macro|PM3FBWriteMode
mdefine_line|#define PM3FBWriteMode                                          0x8ab8
DECL|macro|PM3FBWriteModeAnd
mdefine_line|#define PM3FBWriteModeAnd                                       0xacf0
DECL|macro|PM3FBWriteModeOr
mdefine_line|#define PM3FBWriteModeOr                                        0xacf8
DECL|macro|PM3FBWriteMode_WriteDisable
mdefine_line|#define PM3FBWriteMode_WriteDisable                     0&lt;&lt;0
DECL|macro|PM3FBWriteMode_WriteEnable
mdefine_line|#define PM3FBWriteMode_WriteEnable                      1&lt;&lt;0
DECL|macro|PM3FBWriteMode_Replicate
mdefine_line|#define PM3FBWriteMode_Replicate                        1&lt;&lt;4
DECL|macro|PM3FBWriteMode_OpaqueSpan
mdefine_line|#define PM3FBWriteMode_OpaqueSpan                       1&lt;&lt;5
DECL|macro|PM3FBWriteMode_StripePitch
mdefine_line|#define PM3FBWriteMode_StripePitch(p)            (((p)&amp;0x7)&lt;&lt;6)
DECL|macro|PM3FBWriteMode_StripeHeight
mdefine_line|#define PM3FBWriteMode_StripeHeight(h)           (((h)&amp;0x7)&lt;&lt;9)
DECL|macro|PM3FBWriteMode_Enable0
mdefine_line|#define PM3FBWriteMode_Enable0                          1&lt;&lt;12
DECL|macro|PM3FBWriteMode_Enable1
mdefine_line|#define PM3FBWriteMode_Enable1                          1&lt;&lt;13
DECL|macro|PM3FBWriteMode_Enable2
mdefine_line|#define PM3FBWriteMode_Enable2                          1&lt;&lt;14
DECL|macro|PM3FBWriteMode_Enable3
mdefine_line|#define PM3FBWriteMode_Enable3                          1&lt;&lt;15
DECL|macro|PM3FBWriteMode_Layout0
mdefine_line|#define PM3FBWriteMode_Layout0(l)               (((l)&amp;0x3)&lt;&lt;16)
DECL|macro|PM3FBWriteMode_Layout1
mdefine_line|#define PM3FBWriteMode_Layout1(l)               (((l)&amp;0x3)&lt;&lt;18)
DECL|macro|PM3FBWriteMode_Layout2
mdefine_line|#define PM3FBWriteMode_Layout2(l)               (((l)&amp;0x3)&lt;&lt;20)
DECL|macro|PM3FBWriteMode_Layout3
mdefine_line|#define PM3FBWriteMode_Layout3(l)               (((l)&amp;0x3)&lt;&lt;22)
DECL|macro|PM3FBWriteMode_Origin0
mdefine_line|#define PM3FBWriteMode_Origin0                          1&lt;&lt;24
DECL|macro|PM3FBWriteMode_Origin1
mdefine_line|#define PM3FBWriteMode_Origin1                          1&lt;&lt;25
DECL|macro|PM3FBWriteMode_Origin2
mdefine_line|#define PM3FBWriteMode_Origin2                          1&lt;&lt;26
DECL|macro|PM3FBWriteMode_Origin3
mdefine_line|#define PM3FBWriteMode_Origin3                          1&lt;&lt;27
DECL|macro|PM3ForegroundColor
mdefine_line|#define PM3ForegroundColor&t;&t;&t;&t;&t;0xb0c0
multiline_comment|/* ... */
DECL|macro|PM3GIDMode
mdefine_line|#define PM3GIDMode&t;&t;&t;&t;&t;&t;0xb538
DECL|macro|PM3GIDModeAnd
mdefine_line|#define PM3GIDModeAnd&t;&t;&t;&t;&t;&t;0xb5b0
DECL|macro|PM3GIDModeOr
mdefine_line|#define PM3GIDModeOr&t;&t;&t;&t;&t;&t;0xb5b8
multiline_comment|/* ... */
DECL|macro|PM3LBDestReadBufferAddr
mdefine_line|#define PM3LBDestReadBufferAddr&t;&t;&t;&t;&t;0xb510
DECL|macro|PM3LBDestReadBufferOffset
mdefine_line|#define PM3LBDestReadBufferOffset&t;&t;&t;&t;0xb518
DECL|macro|PM3LBDestReadEnables
mdefine_line|#define PM3LBDestReadEnables&t;&t;&t;&t;&t;0xb508
DECL|macro|PM3LBDestReadEnablesAnd
mdefine_line|#define PM3LBDestReadEnablesAnd&t;&t;&t;&t;&t;0xb590
DECL|macro|PM3LBDestReadEnablesOr
mdefine_line|#define PM3LBDestReadEnablesOr&t;&t;&t;&t;&t;0xb598
DECL|macro|PM3LBDestReadMode
mdefine_line|#define PM3LBDestReadMode&t;&t;&t;&t;&t;0xb500
DECL|macro|PM3LBDestReadModeAnd
mdefine_line|#define PM3LBDestReadModeAnd&t;&t;&t;&t;&t;0xb580
DECL|macro|PM3LBDestReadModeOr
mdefine_line|#define PM3LBDestReadModeOr&t;&t;&t;&t;&t;0xb588
DECL|macro|PM3LBDestReadMode_Disable
mdefine_line|#define PM3LBDestReadMode_Disable&t;&t;&t;0&lt;&lt;0
DECL|macro|PM3LBDestReadMode_Enable
mdefine_line|#define PM3LBDestReadMode_Enable&t;&t;&t;1&lt;&lt;0
DECL|macro|PM3LBDestReadMode_StripePitch
mdefine_line|#define PM3LBDestReadMode_StripePitch(p)&t;&t;(((p)&amp;0x7)&lt;&lt;2)
DECL|macro|PM3LBDestReadMode_StripeHeight
mdefine_line|#define PM3LBDestReadMode_StripeHeight(h)&t;&t;(((h)&amp;0x7)&lt;&lt;5)
DECL|macro|PM3LBDestReadMode_Layout
mdefine_line|#define PM3LBDestReadMode_Layout&t;&t;&t;1&lt;&lt;8
DECL|macro|PM3LBDestReadMode_Origin
mdefine_line|#define PM3LBDestReadMode_Origin&t;&t;&t;1&lt;&lt;9
DECL|macro|PM3LBDestReadMode_UserReadEnables
mdefine_line|#define PM3LBDestReadMode_UserReadEnables&t;&t;1&lt;&lt;10
DECL|macro|PM3LBDestReadMode_Packed16
mdefine_line|#define PM3LBDestReadMode_Packed16&t;&t;&t;1&lt;&lt;11
DECL|macro|PM3LBDestReadMode_Width
mdefine_line|#define PM3LBDestReadMode_Width(w)&t;&t;&t;(((w)&amp;0xfff)&lt;&lt;12)
DECL|macro|PM3LBReadFormat
mdefine_line|#define PM3LBReadFormat&t;&t;&t;&t;&t;&t;0x8888
DECL|macro|PM3LBReadFormat_DepthWidth
mdefine_line|#define PM3LBReadFormat_DepthWidth(w)&t;&t;&t;(((w)&amp;0x3)&lt;&lt;0)
DECL|macro|PM3LBReadFormat_StencilWidth
mdefine_line|#define PM3LBReadFormat_StencilWidth(w)&t;&t;&t;(((w)&amp;0xf)&lt;&lt;2)
DECL|macro|PM3LBReadFormat_StencilPosition
mdefine_line|#define PM3LBReadFormat_StencilPosition(p)&t;&t;(((p)&amp;0x1f)&lt;&lt;6)
DECL|macro|PM3LBReadFormat_FCPWidth
mdefine_line|#define PM3LBReadFormat_FCPWidth(w)&t;&t;&t;(((w)&amp;0xf)&lt;&lt;11)
DECL|macro|PM3LBReadFormat_FCPPosition
mdefine_line|#define PM3LBReadFormat_FCPPosition(p)&t;&t;&t;(((p)&amp;0x1f)&lt;&lt;15)
DECL|macro|PM3LBReadFormat_GIDWidth
mdefine_line|#define PM3LBReadFormat_GIDWidth(w)&t;&t;&t;(((w)&amp;0x7)&lt;&lt;20)
DECL|macro|PM3LBReadFormat_GIDPosition
mdefine_line|#define PM3LBReadFormat_GIDPosition(p)&t;&t;&t;(((p)&amp;0x1f)&lt;&lt;23)
DECL|macro|PM3LBSourceReadBufferAddr
mdefine_line|#define PM3LBSourceReadBufferAddr&t;&t;&t;&t;0xb528
DECL|macro|PM3LBSourceReadBufferOffset
mdefine_line|#define PM3LBSourceReadBufferOffset&t;&t;&t;&t;0xb530
DECL|macro|PM3LBSourceReadMode
mdefine_line|#define PM3LBSourceReadMode&t;&t;&t;&t;&t;0xb520
DECL|macro|PM3LBSourceReadModeAnd
mdefine_line|#define PM3LBSourceReadModeAnd&t;&t;&t;&t;&t;0xb5a0
DECL|macro|PM3LBSourceReadModeOr
mdefine_line|#define PM3LBSourceReadModeOr&t;&t;&t;&t;&t;0xb5a8
DECL|macro|PM3LBSourceReadMode_Enable
mdefine_line|#define PM3LBSourceReadMode_Enable&t;&t;&t;1&lt;&lt;0
DECL|macro|PM3LBSourceReadMode_StripePitch
mdefine_line|#define PM3LBSourceReadMode_StripePitch(p)&t;&t;(((p)&amp;0x7)&lt;&lt;2)
DECL|macro|PM3LBSourceReadMode_StripeHeight
mdefine_line|#define PM3LBSourceReadMode_StripeHeight(h)&t;&t;(((h)&amp;0x7)&lt;&lt;5)
DECL|macro|PM3LBSourceReadMode_Layout
mdefine_line|#define PM3LBSourceReadMode_Layout&t;&t;&t;1&lt;&lt;8
DECL|macro|PM3LBSourceReadMode_Origin
mdefine_line|#define PM3LBSourceReadMode_Origin&t;&t;&t;1&lt;&lt;9
DECL|macro|PM3LBSourceReadMode_Packed16
mdefine_line|#define PM3LBSourceReadMode_Packed16&t;&t;&t;1&lt;&lt;10
DECL|macro|PM3LBSourceReadMode_Width
mdefine_line|#define PM3LBSourceReadMode_Width(w)&t;&t;&t;(((w)&amp;0xfff)&lt;&lt;11)
DECL|macro|PM3LBStencil
mdefine_line|#define PM3LBStencil&t;&t;&t;&t;&t;&t;0x88a8
DECL|macro|PM3LBWriteBufferAddr
mdefine_line|#define PM3LBWriteBufferAddr&t;&t;&t;&t;&t;0xb540
DECL|macro|PM3LBWriteBufferOffset
mdefine_line|#define PM3LBWriteBufferOffset&t;&t;&t;&t;&t;0xb548
DECL|macro|PM3LBWriteFormat
mdefine_line|#define PM3LBWriteFormat&t;&t;&t;&t;&t;0x88c8
DECL|macro|PM3LBWriteFormat_DepthWidth
mdefine_line|#define PM3LBWriteFormat_DepthWidth(w)&t;&t;&t;(((w)&amp;0x3)&lt;&lt;0)
DECL|macro|PM3LBWriteFormat_StencilWidth
mdefine_line|#define PM3LBWriteFormat_StencilWidth(w)&t;&t;(((w)&amp;0xf)&lt;&lt;2)
DECL|macro|PM3LBWriteFormat_StencilPosition
mdefine_line|#define PM3LBWriteFormat_StencilPosition(p)&t;&t;(((p)&amp;0x1f)&lt;&lt;6)
DECL|macro|PM3LBWriteFormat_GIDWidth
mdefine_line|#define PM3LBWriteFormat_GIDWidth(w)&t;&t;&t;(((w)&amp;0x7)&lt;&lt;20)
DECL|macro|PM3LBWriteFormat_GIDPosition
mdefine_line|#define PM3LBWriteFormat_GIDPosition(p)&t;&t;&t;(((p)&amp;0x1f)&lt;&lt;23)
DECL|macro|PM3LBWriteMode
mdefine_line|#define PM3LBWriteMode&t;&t;&t;&t;&t;&t;0x88c0
DECL|macro|PM3LBWriteModeAnd
mdefine_line|#define PM3LBWriteModeAnd&t;&t;&t;&t;&t;0xac80
DECL|macro|PM3LBWriteModeOr
mdefine_line|#define PM3LBWriteModeOr&t;&t;&t;&t;&t;0xac88
DECL|macro|PM3LBWriteMode_WriteDisable
mdefine_line|#define PM3LBWriteMode_WriteDisable&t;&t;&t;0&lt;&lt;0
DECL|macro|PM3LBWriteMode_WriteEnable
mdefine_line|#define PM3LBWriteMode_WriteEnable&t;&t;&t;1&lt;&lt;0
DECL|macro|PM3LBWriteMode_StripePitch
mdefine_line|#define PM3LBWriteMode_StripePitch(p)&t;&t;&t;(((p)&amp;0x7)&lt;&lt;3)
DECL|macro|PM3LBWriteMode_StripeHeight
mdefine_line|#define PM3LBWriteMode_StripeHeight(h)&t;&t;&t;(((h)&amp;0x7)&lt;&lt;6)
DECL|macro|PM3LBWriteMode_Layout
mdefine_line|#define PM3LBWriteMode_Layout&t;&t;&t;&t;1&lt;&lt;9
DECL|macro|PM3LBWriteMode_Origin
mdefine_line|#define PM3LBWriteMode_Origin&t;&t;&t;&t;1&lt;&lt;10
DECL|macro|PM3LBWriteMode_Packed16
mdefine_line|#define PM3LBWriteMode_Packed16&t;&t;&t;&t;1&lt;&lt;11
DECL|macro|PM3LBWriteMode_Width
mdefine_line|#define PM3LBWriteMode_Width(w)&t;&t;&t;&t;(((w)&amp;0xfff)&lt;&lt;12)
multiline_comment|/* ... */
DECL|macro|PM3LineStippleMode
mdefine_line|#define PM3LineStippleMode&t;&t;&t;&t;&t;0x81a8
DECL|macro|PM3LineStippleModeAnd
mdefine_line|#define PM3LineStippleModeAnd&t;&t;&t;&t;&t;0xabc0
DECL|macro|PM3LineStippleModeOr
mdefine_line|#define PM3LineStippleModeOr&t;&t;&t;&t;&t;0xabc8
DECL|macro|PM3LoadLineStippleCounters
mdefine_line|#define PM3LoadLineStippleCounters&t;&t;&t;&t;0x81b0
multiline_comment|/* ... */
DECL|macro|PM3LogicalOpMode
mdefine_line|#define PM3LogicalOpMode&t;&t;&t;&t;&t;0x8828
DECL|macro|PM3LogicalOpModeAnd
mdefine_line|#define PM3LogicalOpModeAnd&t;&t;&t;&t;&t;0xace0
DECL|macro|PM3LogicalOpModeOr
mdefine_line|#define PM3LogicalOpModeOr&t;&t;&t;&t;&t;0xace8
DECL|macro|PM3LogicalOpMode_Disable
mdefine_line|#define PM3LogicalOpMode_Disable&t;&t;&t;(0&lt;&lt;0)
DECL|macro|PM3LogicalOpMode_Enable
mdefine_line|#define PM3LogicalOpMode_Enable&t;&t;&t;&t;(1&lt;&lt;0)
DECL|macro|PM3LogicalOpMode_LogicOp
mdefine_line|#define PM3LogicalOpMode_LogicOp(op)&t;&t;&t;(((op)&amp;0xf)&lt;&lt;1)
DECL|macro|PM3LogicalOpMode_UseConstantWriteData_Disable
mdefine_line|#define PM3LogicalOpMode_UseConstantWriteData_Disable&t;(0&lt;&lt;5)
DECL|macro|PM3LogicalOpMode_UseConstantWriteData_Enable
mdefine_line|#define PM3LogicalOpMode_UseConstantWriteData_Enable&t;(1&lt;&lt;5)
DECL|macro|PM3LogicalOpMode_Background_Disable
mdefine_line|#define PM3LogicalOpMode_Background_Disable&t;&t;(0&lt;&lt;6)
DECL|macro|PM3LogicalOpMode_Background_Enable
mdefine_line|#define PM3LogicalOpMode_Background_Enable&t;&t;(1&lt;&lt;6)
DECL|macro|PM3LogicalOpMode_Background_LogicOp
mdefine_line|#define PM3LogicalOpMode_Background_LogicOp(op)&t;&t;(((op)&amp;0xf)&lt;&lt;7)
DECL|macro|PM3LogicalOpMode_UseConstantSource_Disable
mdefine_line|#define PM3LogicalOpMode_UseConstantSource_Disable&t;(0&lt;&lt;11)
DECL|macro|PM3LogicalOpMode_UseConstantSource_Enable
mdefine_line|#define PM3LogicalOpMode_UseConstantSource_Enable&t;(1&lt;&lt;11)
multiline_comment|/* ... */
DECL|macro|PM3LUT
mdefine_line|#define PM3LUT&t;&t;&t;&t;&t;&t;&t;0x8e80
multiline_comment|/* ... */
DECL|macro|PM3LUT
mdefine_line|#define PM3LUT&t;&t;&t;&t;&t;&t;&t;0x8e80
DECL|macro|PM3LUTAddress
mdefine_line|#define PM3LUTAddress&t;&t;&t;&t;&t;&t;0x84d0
DECL|macro|PM3LUTData
mdefine_line|#define PM3LUTData&t;&t;&t;&t;&t;&t;0x84c8
DECL|macro|PM3LUTIndex
mdefine_line|#define PM3LUTIndex&t;&t;&t;&t;&t;&t;0x84c0
DECL|macro|PM3LUTMode
mdefine_line|#define PM3LUTMode&t;&t;&t;&t;&t;&t;0xb378
DECL|macro|PM3LUTModeAnd
mdefine_line|#define PM3LUTModeAnd&t;&t;&t;&t;&t;&t;0xad70
DECL|macro|PM3LUTModeOr
mdefine_line|#define PM3LUTModeOr&t;&t;&t;&t;&t;&t;0xad78
DECL|macro|PM3LUTTransfer
mdefine_line|#define PM3LUTTransfer&t;&t;&t;&t;&t;&t;0x84d8
multiline_comment|/* ... */
DECL|macro|PM3PixelSize
mdefine_line|#define PM3PixelSize&t;&t;&t;&t;&t;&t;0x80c0
DECL|macro|PM3PixelSize_GLOBAL_32BIT
mdefine_line|#define PM3PixelSize_GLOBAL_32BIT&t;&t;&t;(0&lt;&lt;0)
DECL|macro|PM3PixelSize_GLOBAL_16BIT
mdefine_line|#define PM3PixelSize_GLOBAL_16BIT&t;&t;&t;(1&lt;&lt;0)
DECL|macro|PM3PixelSize_GLOBAL_8BIT
mdefine_line|#define PM3PixelSize_GLOBAL_8BIT&t;&t;&t;(2&lt;&lt;0)
DECL|macro|PM3PixelSize_RASTERIZER_32BIT
mdefine_line|#define PM3PixelSize_RASTERIZER_32BIT&t;&t;&t;(0&lt;&lt;2)
DECL|macro|PM3PixelSize_RASTERIZER_16BIT
mdefine_line|#define PM3PixelSize_RASTERIZER_16BIT&t;&t;&t;(1&lt;&lt;2)
DECL|macro|PM3PixelSize_RASTERIZER_8BIT
mdefine_line|#define PM3PixelSize_RASTERIZER_8BIT&t;&t;&t;(2&lt;&lt;2)
DECL|macro|PM3PixelSize_SCISSOR_AND_STIPPLE_32BIT
mdefine_line|#define PM3PixelSize_SCISSOR_AND_STIPPLE_32BIT&t;&t;(0&lt;&lt;4)
DECL|macro|PM3PixelSize_SCISSOR_AND_STIPPLE_16BIT
mdefine_line|#define PM3PixelSize_SCISSOR_AND_STIPPLE_16BIT&t;&t;(1&lt;&lt;4)
DECL|macro|PM3PixelSize_SCISSOR_AND_STIPPLE_8BIT
mdefine_line|#define PM3PixelSize_SCISSOR_AND_STIPPLE_8BIT&t;&t;(2&lt;&lt;4)
DECL|macro|PM3PixelSize_TEXTURE_32BIT
mdefine_line|#define PM3PixelSize_TEXTURE_32BIT&t;&t;&t;(0&lt;&lt;6)
DECL|macro|PM3PixelSize_TEXTURE_16BIT
mdefine_line|#define PM3PixelSize_TEXTURE_16BIT&t;&t;&t;(1&lt;&lt;6)
DECL|macro|PM3PixelSize_TEXTURE_8BIT
mdefine_line|#define PM3PixelSize_TEXTURE_8BIT&t;&t;&t;(2&lt;&lt;6)
DECL|macro|PM3PixelSize_LUT_32BIT
mdefine_line|#define PM3PixelSize_LUT_32BIT&t;&t;&t;&t;(0&lt;&lt;8)
DECL|macro|PM3PixelSize_LUT_16BIT
mdefine_line|#define PM3PixelSize_LUT_16BIT&t;&t;&t;&t;(1&lt;&lt;8)
DECL|macro|PM3PixelSize_LUT_8BIT
mdefine_line|#define PM3PixelSize_LUT_8BIT&t;&t;&t;&t;(2&lt;&lt;8)
DECL|macro|PM3PixelSize_FRAMEBUFFER_32BIT
mdefine_line|#define PM3PixelSize_FRAMEBUFFER_32BIT&t;&t;&t;(0&lt;&lt;10)
DECL|macro|PM3PixelSize_FRAMEBUFFER_16BIT
mdefine_line|#define PM3PixelSize_FRAMEBUFFER_16BIT&t;&t;&t;(1&lt;&lt;10)
DECL|macro|PM3PixelSize_FRAMEBUFFER_8BIT
mdefine_line|#define PM3PixelSize_FRAMEBUFFER_8BIT&t;&t;&t;(2&lt;&lt;10)
DECL|macro|PM3PixelSize_LOGICAL_OP_32BIT
mdefine_line|#define PM3PixelSize_LOGICAL_OP_32BIT&t;&t;&t;(0&lt;&lt;12)
DECL|macro|PM3PixelSize_LOGICAL_OP_16BIT
mdefine_line|#define PM3PixelSize_LOGICAL_OP_16BIT&t;&t;&t;(1&lt;&lt;12)
DECL|macro|PM3PixelSize_LOGICAL_OP_8BIT
mdefine_line|#define PM3PixelSize_LOGICAL_OP_8BIT&t;&t;&t;(2&lt;&lt;12)
DECL|macro|PM3PixelSize_LOCALBUFFER_32BIT
mdefine_line|#define PM3PixelSize_LOCALBUFFER_32BIT&t;&t;&t;(0&lt;&lt;14)
DECL|macro|PM3PixelSize_LOCALBUFFER_16BIT
mdefine_line|#define PM3PixelSize_LOCALBUFFER_16BIT&t;&t;&t;(1&lt;&lt;14)
DECL|macro|PM3PixelSize_LOCALBUFFER_8BIT
mdefine_line|#define PM3PixelSize_LOCALBUFFER_8BIT&t;&t;&t;(2&lt;&lt;14)
DECL|macro|PM3PixelSize_SETUP_32BIT
mdefine_line|#define PM3PixelSize_SETUP_32BIT&t;&t;&t;(0&lt;&lt;16)
DECL|macro|PM3PixelSize_SETUP_16BIT
mdefine_line|#define PM3PixelSize_SETUP_16BIT&t;&t;&t;(1&lt;&lt;16)
DECL|macro|PM3PixelSize_SETUP_8BIT
mdefine_line|#define PM3PixelSize_SETUP_8BIT&t;&t;&t;&t;(2&lt;&lt;16)
DECL|macro|PM3PixelSize_GLOBAL
mdefine_line|#define PM3PixelSize_GLOBAL&t;&t;&t;&t;(0&lt;&lt;31)
DECL|macro|PM3PixelSize_INDIVIDUAL
mdefine_line|#define PM3PixelSize_INDIVIDUAL&t;&t;&t;&t;(1&lt;&lt;31)
multiline_comment|/* ... */
DECL|macro|PM3Render
mdefine_line|#define PM3Render&t;&t;&t;&t;&t;&t;0x8038
DECL|macro|PM3Render_AreaStipple_Disable
mdefine_line|#define PM3Render_AreaStipple_Disable&t;&t;&t;(0&lt;&lt;0)
DECL|macro|PM3Render_AreaStipple_Enable
mdefine_line|#define PM3Render_AreaStipple_Enable&t;&t;&t;(1&lt;&lt;0)
DECL|macro|PM3Render_LineStipple_Disable
mdefine_line|#define PM3Render_LineStipple_Disable&t;&t;&t;(0&lt;&lt;1)
DECL|macro|PM3Render_LineStipple_Enable
mdefine_line|#define PM3Render_LineStipple_Enable&t;&t;&t;(1&lt;&lt;1)
DECL|macro|PM3Render_ResetLine_Disable
mdefine_line|#define PM3Render_ResetLine_Disable&t;&t;&t;(0&lt;&lt;2)
DECL|macro|PM3Render_ResetLine_Enable
mdefine_line|#define PM3Render_ResetLine_Enable&t;&t;&t;(1&lt;&lt;2)
DECL|macro|PM3Render_FastFill_Disable
mdefine_line|#define PM3Render_FastFill_Disable&t;&t;&t;(0&lt;&lt;3)
DECL|macro|PM3Render_FastFill_Enable
mdefine_line|#define PM3Render_FastFill_Enable&t;&t;&t;(1&lt;&lt;3)
DECL|macro|PM3Render_Primitive_Line
mdefine_line|#define PM3Render_Primitive_Line&t;&t;&t;(0&lt;&lt;6)
DECL|macro|PM3Render_Primitive_Trapezoid
mdefine_line|#define PM3Render_Primitive_Trapezoid&t;&t;&t;(1&lt;&lt;6)
DECL|macro|PM3Render_Primitive_Point
mdefine_line|#define PM3Render_Primitive_Point&t;&t;&t;(2&lt;&lt;6)
DECL|macro|PM3Render_Antialias_Disable
mdefine_line|#define PM3Render_Antialias_Disable&t;&t;&t;(0&lt;&lt;8)
DECL|macro|PM3Render_Antialias_Enable
mdefine_line|#define PM3Render_Antialias_Enable&t;&t;&t;(1&lt;&lt;8)
DECL|macro|PM3Render_Antialias_SubPixelRes_4x4
mdefine_line|#define PM3Render_Antialias_SubPixelRes_4x4&t;&t;(0&lt;&lt;9)
DECL|macro|PM3Render_Antialias_SubPixelRes_8x8
mdefine_line|#define PM3Render_Antialias_SubPixelRes_8x8&t;&t;(1&lt;&lt;9)
DECL|macro|PM3Render_UsePointTable_Disable
mdefine_line|#define PM3Render_UsePointTable_Disable&t;&t;&t;(0&lt;&lt;10)
DECL|macro|PM3Render_UsePointTable_Enable
mdefine_line|#define PM3Render_UsePointTable_Enable&t;&t;&t;(1&lt;&lt;10)
DECL|macro|PM3Render_SyncOnbitMask_Disable
mdefine_line|#define PM3Render_SyncOnbitMask_Disable&t;&t;&t;(0&lt;&lt;11)
DECL|macro|PM3Render_SyncOnBitMask_Enable
mdefine_line|#define PM3Render_SyncOnBitMask_Enable&t;&t;&t;(1&lt;&lt;11)
DECL|macro|PM3Render_SyncOnHostData_Disable
mdefine_line|#define PM3Render_SyncOnHostData_Disable&t;&t;(0&lt;&lt;12)
DECL|macro|PM3Render_SyncOnHostData_Enable
mdefine_line|#define PM3Render_SyncOnHostData_Enable&t;&t;&t;(1&lt;&lt;12)
DECL|macro|PM3Render_Texture_Disable
mdefine_line|#define PM3Render_Texture_Disable&t;&t;&t;(0&lt;&lt;13)
DECL|macro|PM3Render_Texture_Enable
mdefine_line|#define PM3Render_Texture_Enable&t;&t;&t;(1&lt;&lt;13)
DECL|macro|PM3Render_Fog_Disable
mdefine_line|#define PM3Render_Fog_Disable&t;&t;&t;&t;(0&lt;&lt;14)
DECL|macro|PM3Render_Fog_Enable
mdefine_line|#define PM3Render_Fog_Enable&t;&t;&t;&t;(1&lt;&lt;14)
DECL|macro|PM3Render_Coverage_Disable
mdefine_line|#define PM3Render_Coverage_Disable&t;&t;&t;(0&lt;&lt;15)
DECL|macro|PM3Render_Coverage_Enable
mdefine_line|#define PM3Render_Coverage_Enable&t;&t;&t;(1&lt;&lt;15)
DECL|macro|PM3Render_SubPixelCorrection_Disable
mdefine_line|#define PM3Render_SubPixelCorrection_Disable&t;&t;(0&lt;&lt;16)
DECL|macro|PM3Render_SubPixelCorrection_Enable
mdefine_line|#define PM3Render_SubPixelCorrection_Enable&t;&t;(1&lt;&lt;16)
DECL|macro|PM3Render_SpanOperation_Disable
mdefine_line|#define PM3Render_SpanOperation_Disable&t;&t;&t;(0&lt;&lt;18)
DECL|macro|PM3Render_SpanOperation_Enable
mdefine_line|#define PM3Render_SpanOperation_Enable&t;&t;&t;(1&lt;&lt;18)
DECL|macro|PM3Render_FBSourceRead_Disable
mdefine_line|#define PM3Render_FBSourceRead_Disable&t;&t;&t;(0&lt;&lt;27)
DECL|macro|PM3Render_FBSourceRead_Enable
mdefine_line|#define PM3Render_FBSourceRead_Enable&t;&t;&t;(1&lt;&lt;27)
DECL|macro|PM3RasterizerMode
mdefine_line|#define PM3RasterizerMode&t;&t;&t;&t;&t;0x80a0
DECL|macro|PM3RasterizerModeAnd
mdefine_line|#define PM3RasterizerModeAnd&t;&t;&t;&t;&t;0xaba0
DECL|macro|PM3RasterizerModeOr
mdefine_line|#define PM3RasterizerModeOr&t;&t;&t;&t;&t;0xabb8
DECL|macro|PM3RectangleHeight
mdefine_line|#define PM3RectangleHeight&t;&t;&t;&t;&t;0x94e0
DECL|macro|PM3Render
mdefine_line|#define PM3Render&t;&t;&t;&t;&t;&t;0x8038
DECL|macro|PM3RepeatLine
mdefine_line|#define PM3RepeatLine&t;&t;&t;&t;&t;&t;0x9328
DECL|macro|PM3ResetPickResult
mdefine_line|#define PM3ResetPickResult&t;&t;&t;&t;&t;0x8c20
DECL|macro|PM3RLEMask
mdefine_line|#define PM3RLEMask&t;&t;&t;&t;&t;&t;0x8c48
DECL|macro|PM3RouterMode
mdefine_line|#define PM3RouterMode&t;&t;&t;&t;&t;&t;0x8840
DECL|macro|PM3RStart
mdefine_line|#define PM3RStart&t;&t;&t;&t;&t;&t;0x8780
DECL|macro|PM3S1Start
mdefine_line|#define PM3S1Start&t;&t;&t;&t;&t;&t;0x8400
DECL|macro|PM3aveLineStippleCounters
mdefine_line|#define PM3aveLineStippleCounters&t;&t;&t;&t;0x81c0
DECL|macro|PM3ScissorMaxXY
mdefine_line|#define PM3ScissorMaxXY&t;&t;&t;&t;&t;&t;0x8190
DECL|macro|PM3ScissorMinXY
mdefine_line|#define PM3ScissorMinXY&t;&t;&t;&t;&t;&t;0x8188
DECL|macro|PM3ScissorMode
mdefine_line|#define PM3ScissorMode&t;&t;&t;&t;&t;&t;0x8180
DECL|macro|PM3ScissorModeAnd
mdefine_line|#define PM3ScissorModeAnd&t;&t;&t;&t;&t;0xabb0
DECL|macro|PM3ScissorModeOr
mdefine_line|#define PM3ScissorModeOr&t;&t;&t;&t;&t;0xabb8
DECL|macro|PM3ScreenSize
mdefine_line|#define PM3ScreenSize&t;&t;&t;&t;&t;&t;0x8198
DECL|macro|PM3Security
mdefine_line|#define PM3Security&t;&t;&t;&t;&t;&t;0x8908
DECL|macro|PM3SetLogicalTexturePage
mdefine_line|#define PM3SetLogicalTexturePage&t;&t;&t;&t;0xb360
DECL|macro|PM3SizeOfFramebuffer
mdefine_line|#define PM3SizeOfFramebuffer&t;&t;&t;&t;&t;0xb0a8
DECL|macro|PM3SStart
mdefine_line|#define PM3SStart&t;&t;&t;&t;&t;&t;0x8388
DECL|macro|PM3StartXDom
mdefine_line|#define PM3StartXDom&t;&t;&t;&t;&t;&t;0x8000
DECL|macro|PM3StartXSub
mdefine_line|#define PM3StartXSub&t;&t;&t;&t;&t;&t;0x8010
DECL|macro|PM3StartY
mdefine_line|#define PM3StartY&t;&t;&t;&t;&t;&t;0x8020
multiline_comment|/* ... */
DECL|macro|PM3SpanColorMask
mdefine_line|#define PM3SpanColorMask&t;&t;&t;&t;&t;0x8168
multiline_comment|/* ... */
DECL|macro|PM3TextureApplicationMode
mdefine_line|#define PM3TextureApplicationMode&t;&t;&t;&t;0x8680
DECL|macro|PM3TextureApplicationModeAnd
mdefine_line|#define PM3TextureApplicationModeAnd&t;&t;&t;&t;0xac50
DECL|macro|PM3TextureApplicationModeOr
mdefine_line|#define PM3TextureApplicationModeOr&t;&t;&t;&t;0xac58
DECL|macro|PM3TextureBaseAddr
mdefine_line|#define PM3TextureBaseAddr&t;&t;&t;&t;&t;0x8500
DECL|macro|PM3TextureCacheControl
mdefine_line|#define PM3TextureCacheControl&t;&t;&t;&t;&t;0x8490
DECL|macro|PM3TextureChromaLower0
mdefine_line|#define PM3TextureChromaLower0&t;&t;&t;&t;&t;0x84f0
DECL|macro|PM3TextureChromaLower1
mdefine_line|#define PM3TextureChromaLower1&t;&t;&t;&t;&t;0x8608
DECL|macro|PM3TextureChromaUpper0
mdefine_line|#define PM3TextureChromaUpper0&t;&t;&t;&t;&t;0x84e8
DECL|macro|PM3TextureChromaUpper1
mdefine_line|#define PM3TextureChromaUpper1&t;&t;&t;&t;&t;0x8600
DECL|macro|PM3TextureCompositeAlphaMode0
mdefine_line|#define PM3TextureCompositeAlphaMode0&t;&t;&t;&t;0xb310
DECL|macro|PM3TextureCompositeAlphaMode0And
mdefine_line|#define PM3TextureCompositeAlphaMode0And&t;&t;&t;0xb390
DECL|macro|PM3TextureCompositeAlphaMode0Or
mdefine_line|#define PM3TextureCompositeAlphaMode0Or&t;&t;&t;&t;0xb398
DECL|macro|PM3TextureCompositeAlphaMode1
mdefine_line|#define PM3TextureCompositeAlphaMode1&t;&t;&t;&t;0xb320
DECL|macro|PM3TextureCompositeAlphaMode1And
mdefine_line|#define PM3TextureCompositeAlphaMode1And&t;&t;&t;0xb3b0
DECL|macro|PM3TextureCompositeAlphaMode1Or
mdefine_line|#define PM3TextureCompositeAlphaMode1Or&t;&t;&t;&t;0xb3b8
DECL|macro|PM3TextureCompositeColorMode0
mdefine_line|#define PM3TextureCompositeColorMode0&t;&t;&t;&t;0xb308
DECL|macro|PM3TextureCompositeColorMode0And
mdefine_line|#define PM3TextureCompositeColorMode0And&t;&t;&t;0xb380
DECL|macro|PM3TextureCompositeColorMode0Or
mdefine_line|#define PM3TextureCompositeColorMode0Or&t;&t;&t;&t;0xb388
DECL|macro|PM3TextureCompositeColorMode1
mdefine_line|#define PM3TextureCompositeColorMode1&t;&t;&t;&t;0xb318
DECL|macro|PM3TextureCompositeColorMode1And
mdefine_line|#define PM3TextureCompositeColorMode1And&t;&t;&t;0xb3a0
DECL|macro|PM3TextureCompositeColorMode1Or
mdefine_line|#define PM3TextureCompositeColorMode1Or&t;&t;&t;&t;0xb3a8
DECL|macro|PM3TextureCompositeFactor0
mdefine_line|#define PM3TextureCompositeFactor0&t;&t;&t;&t;0xb328
DECL|macro|PM3TextureCompositeFactor1
mdefine_line|#define PM3TextureCompositeFactor1&t;&t;&t;&t;0xb330
DECL|macro|PM3TextureCompositeMode
mdefine_line|#define PM3TextureCompositeMode&t;&t;&t;&t;&t;0xb300
DECL|macro|PM3TextureCoordMode
mdefine_line|#define PM3TextureCoordMode&t;&t;&t;&t;&t;0x8380
DECL|macro|PM3TextureCoordModeAnd
mdefine_line|#define PM3TextureCoordModeAnd&t;&t;&t;&t;&t;0xac20
DECL|macro|PM3TextureCoordModeOr
mdefine_line|#define PM3TextureCoordModeOr&t;&t;&t;&t;&t;0xac28
DECL|macro|PM3TextureData
mdefine_line|#define PM3TextureData&t;&t;&t;&t;&t;&t;0x88e8
multiline_comment|/*&n;#define PM3TextureDownloadControl&t;&t;&t;&t;0x0108&n;*/
DECL|macro|PM3TextureDownloadOffset
mdefine_line|#define PM3TextureDownloadOffset&t;&t;&t;&t;0x88f0
DECL|macro|PM3TextureEnvColor
mdefine_line|#define PM3TextureEnvColor&t;&t;&t;&t;&t;0x8688
DECL|macro|PM3TextureFilterMode
mdefine_line|#define PM3TextureFilterMode&t;&t;&t;&t;&t;0x84e0
DECL|macro|PM3TextureFilterModeAnd
mdefine_line|#define PM3TextureFilterModeAnd&t;&t;&t;&t;&t;0xad50
DECL|macro|PM3TextureFilterModeOr
mdefine_line|#define PM3TextureFilterModeOr&t;&t;&t;&t;&t;0xad58
DECL|macro|PM3TextureIndexMode0
mdefine_line|#define PM3TextureIndexMode0&t;&t;&t;&t;&t;0xb338
DECL|macro|PM3TextureIndexMode0And
mdefine_line|#define PM3TextureIndexMode0And&t;&t;&t;&t;&t;0xb3c0
DECL|macro|PM3TextureIndexMode0Or
mdefine_line|#define PM3TextureIndexMode0Or&t;&t;&t;&t;&t;0xb3c8
DECL|macro|PM3TextureIndexMode1
mdefine_line|#define PM3TextureIndexMode1&t;&t;&t;&t;&t;0xb340
DECL|macro|PM3TextureIndexMode1And
mdefine_line|#define PM3TextureIndexMode1And&t;&t;&t;&t;&t;0xb3d0
DECL|macro|PM3TextureIndexMode1Or
mdefine_line|#define PM3TextureIndexMode1Or&t;&t;&t;&t;&t;0xb3d8
multiline_comment|/* ... */
DECL|macro|PM3TextureMapSize
mdefine_line|#define PM3TextureMapSize                                       0xb428
DECL|macro|PM3TextureMapWidth0
mdefine_line|#define PM3TextureMapWidth0                                     0x8580
DECL|macro|PM3TextureMapWidth1
mdefine_line|#define PM3TextureMapWidth1                                     0x8588
DECL|macro|PM3TextureMapWidth_Width
mdefine_line|#define PM3TextureMapWidth_Width(w)             ((w&amp;0xfff)&lt;&lt;0)
DECL|macro|PM3TextureMapWidth_BorderLayout
mdefine_line|#define PM3TextureMapWidth_BorderLayout                 (1&lt;&lt;12)
DECL|macro|PM3TextureMapWidth_Layout_Linear
mdefine_line|#define PM3TextureMapWidth_Layout_Linear                (0&lt;&lt;13)
DECL|macro|PM3TextureMapWidth_Layout_Patch64
mdefine_line|#define PM3TextureMapWidth_Layout_Patch64               (1&lt;&lt;13)
DECL|macro|PM3TextureMapWidth_Layout_Patch32_2
mdefine_line|#define PM3TextureMapWidth_Layout_Patch32_2             (2&lt;&lt;13)
DECL|macro|PM3TextureMapWidth_Layout_Patch2
mdefine_line|#define PM3TextureMapWidth_Layout_Patch2                (3&lt;&lt;13)
DECL|macro|PM3TextureMapWidth_HostTexture
mdefine_line|#define PM3TextureMapWidth_HostTexture                  (1&lt;&lt;15)
DECL|macro|PM3TextureReadMode0
mdefine_line|#define PM3TextureReadMode0                                     0xb400
DECL|macro|PM3TextureReadMode0And
mdefine_line|#define PM3TextureReadMode0And                                  0xac30
DECL|macro|PM3TextureReadMode0Or
mdefine_line|#define PM3TextureReadMode0Or                                   0xac38
DECL|macro|PM3TextureReadMode1
mdefine_line|#define PM3TextureReadMode1                                     0xb408
DECL|macro|PM3TextureReadMode1And
mdefine_line|#define PM3TextureReadMode1And                                  0xad40
DECL|macro|PM3TextureReadMode1Or
mdefine_line|#define PM3TextureReadMode1Or                                   0xad48
multiline_comment|/* ... */
DECL|macro|PM3WaitForCompletion
mdefine_line|#define PM3WaitForCompletion&t;&t;&t;&t;&t;0x80b8
DECL|macro|PM3Window
mdefine_line|#define PM3Window&t;&t;&t;&t;&t;&t;0x8980
DECL|macro|PM3Window_ForceLBUpdate
mdefine_line|#define PM3Window_ForceLBUpdate&t;&t;&t;&t;1&lt;&lt;3
DECL|macro|PM3Window_LBUpdateSource
mdefine_line|#define PM3Window_LBUpdateSource&t;&t;&t;1&lt;&lt;4
DECL|macro|PM3Window_FrameCount
mdefine_line|#define PM3Window_FrameCount(c)&t;&t;&t;&t;(((c)&amp;0xff)&lt;&lt;9
DECL|macro|PM3Window_StencilFCP
mdefine_line|#define PM3Window_StencilFCP&t;&t;&t;&t;1&lt;&lt;17
DECL|macro|PM3Window_DepthFCP
mdefine_line|#define PM3Window_DepthFCP&t;&t;&t;&t;1&lt;&lt;18
DECL|macro|PM3Window_OverrideWriteFiltering
mdefine_line|#define PM3Window_OverrideWriteFiltering&t;&t;1&lt;&lt;19
DECL|macro|PM3WindowAnd
mdefine_line|#define PM3WindowAnd&t;&t;&t;&t;&t;&t;0xab80
DECL|macro|PM3WindowOr
mdefine_line|#define PM3WindowOr&t;&t;&t;&t;&t;&t;0xab88
DECL|macro|PM3WindowOrigin
mdefine_line|#define PM3WindowOrigin&t;&t;&t;&t;&t;&t;0x81c8
DECL|macro|PM3XBias
mdefine_line|#define PM3XBias&t;&t;&t;&t;&t;&t;0x9480
DECL|macro|PM3YBias
mdefine_line|#define PM3YBias&t;&t;&t;&t;&t;&t;0x9488
DECL|macro|PM3YLimits
mdefine_line|#define PM3YLimits&t;&t;&t;&t;&t;&t;0x80a8
DECL|macro|PM3UVMode
mdefine_line|#define PM3UVMode&t;&t;&t;&t;&t;&t;0x8f00
DECL|macro|PM3ZFogBias
mdefine_line|#define PM3ZFogBias&t;&t;&t;&t;&t;&t;0x86b8
DECL|macro|PM3ZStart
mdefine_line|#define PM3ZStart&t;&t;&t;&t;&t;&t;0xadd8
DECL|macro|PM3ZStartL
mdefine_line|#define PM3ZStartL&t;&t;&t;&t;&t;&t;0x89b8
DECL|macro|PM3ZStartU
mdefine_line|#define PM3ZStartU&t;&t;&t;&t;&t;&t;0x89b0
multiline_comment|/**********************************************&n;*  GLINT Permedia3 2D setup Unit              *&n;***********************************************/
DECL|macro|PM3Config2D
mdefine_line|#define PM3Config2D&t;&t;&t;&t;&t;&t;0xb618
DECL|macro|PM3Config2D_OpaqueSpan
mdefine_line|#define PM3Config2D_OpaqueSpan&t;&t;&t;&t;1&lt;&lt;0
DECL|macro|PM3Config2D_MultiRXBlit
mdefine_line|#define PM3Config2D_MultiRXBlit&t;&t;&t;&t;1&lt;&lt;1
DECL|macro|PM3Config2D_UserScissorEnable
mdefine_line|#define PM3Config2D_UserScissorEnable&t;&t;&t;1&lt;&lt;2
DECL|macro|PM3Config2D_FBDestReadEnable
mdefine_line|#define PM3Config2D_FBDestReadEnable&t;&t;&t;1&lt;&lt;3
DECL|macro|PM3Config2D_AlphaBlendEnable
mdefine_line|#define PM3Config2D_AlphaBlendEnable&t;&t;&t;1&lt;&lt;4
DECL|macro|PM3Config2D_DitherEnable
mdefine_line|#define PM3Config2D_DitherEnable&t;&t;&t;1&lt;&lt;5
DECL|macro|PM3Config2D_ForegroundROPEnable
mdefine_line|#define PM3Config2D_ForegroundROPEnable&t;&t;&t;1&lt;&lt;6
DECL|macro|PM3Config2D_ForegroundROP
mdefine_line|#define PM3Config2D_ForegroundROP(rop)&t;&t;(((rop)&amp;0xf)&lt;&lt;7)
DECL|macro|PM3Config2D_BackgroundROPEnable
mdefine_line|#define PM3Config2D_BackgroundROPEnable&t;&t;&t;1&lt;&lt;11
DECL|macro|PM3Config2D_BackgroundROP
mdefine_line|#define PM3Config2D_BackgroundROP(rop)&t;&t;(((rop)&amp;0xf)&lt;&lt;12)
DECL|macro|PM3Config2D_UseConstantSource
mdefine_line|#define PM3Config2D_UseConstantSource&t;&t;&t;1&lt;&lt;16
DECL|macro|PM3Config2D_FBWriteEnable
mdefine_line|#define PM3Config2D_FBWriteEnable&t;&t;&t;1&lt;&lt;17
DECL|macro|PM3Config2D_Blocking
mdefine_line|#define PM3Config2D_Blocking&t;&t;&t;&t;1&lt;&lt;18
DECL|macro|PM3Config2D_ExternalSourceData
mdefine_line|#define PM3Config2D_ExternalSourceData&t;&t;&t;1&lt;&lt;19
DECL|macro|PM3Config2D_LUTModeEnable
mdefine_line|#define PM3Config2D_LUTModeEnable&t;&t;&t;1&lt;&lt;20
DECL|macro|PM3DownloadGlyphwidth
mdefine_line|#define PM3DownloadGlyphwidth&t;&t;&t;&t;&t;0xb658
DECL|macro|PM3DownloadGlyphwidth_GlyphWidth
mdefine_line|#define PM3DownloadGlyphwidth_GlyphWidth(gw)&t;((gw)&amp;0xffff)
DECL|macro|PM3DownloadTarget
mdefine_line|#define PM3DownloadTarget&t;&t;&t;&t;&t;0xb650
DECL|macro|PM3DownloadTarget_TagName
mdefine_line|#define PM3DownloadTarget_TagName(tag)&t;&t;((tag)&amp;0x1fff)
DECL|macro|PM3GlyphData
mdefine_line|#define PM3GlyphData&t;&t;&t;&t;&t;&t;0xb660
DECL|macro|PM3GlyphPosition
mdefine_line|#define PM3GlyphPosition&t;&t;&t;&t;&t;0xb608
DECL|macro|PM3GlyphPosition_XOffset
mdefine_line|#define PM3GlyphPosition_XOffset(x)&t;&t;((x)&amp;0xffff)
DECL|macro|PM3GlyphPosition_YOffset
mdefine_line|#define PM3GlyphPosition_YOffset(y)&t;&t;(((y)&amp;0xffff)&lt;&lt;16)
DECL|macro|PM3Packed4Pixels
mdefine_line|#define PM3Packed4Pixels&t;&t;&t;&t;&t;0xb668
DECL|macro|PM3Packed8Pixels
mdefine_line|#define PM3Packed8Pixels&t;&t;&t;&t;&t;0xb630
DECL|macro|PM3Packed16Pixels
mdefine_line|#define PM3Packed16Pixels&t;&t;&t;&t;&t;0xb638
DECL|macro|PM3RectanglePosition
mdefine_line|#define PM3RectanglePosition&t;&t;&t;&t;&t;0xb600
DECL|macro|PM3RectanglePosition_XOffset
mdefine_line|#define PM3RectanglePosition_XOffset(x)&t;&t;((x)&amp;0xffff)
DECL|macro|PM3RectanglePosition_YOffset
mdefine_line|#define PM3RectanglePosition_YOffset(y)&t;&t;(((y)&amp;0xffff)&lt;&lt;16)
DECL|macro|PM3Render2D
mdefine_line|#define PM3Render2D&t;&t;&t;&t;&t;&t;0xb640
DECL|macro|PM3Render2D_Width
mdefine_line|#define PM3Render2D_Width(w)&t;&t;&t;((w)&amp;0x0fff)
DECL|macro|PM3Render2D_Operation_Normal
mdefine_line|#define PM3Render2D_Operation_Normal&t;&t;&t;0&lt;&lt;12
DECL|macro|PM3Render2D_Operation_SyncOnHostData
mdefine_line|#define PM3Render2D_Operation_SyncOnHostData&t;&t;1&lt;&lt;12
DECL|macro|PM3Render2D_Operation_SyncOnBitMask
mdefine_line|#define PM3Render2D_Operation_SyncOnBitMask&t;&t;2&lt;&lt;12
DECL|macro|PM3Render2D_Operation_PatchOrderRendering
mdefine_line|#define PM3Render2D_Operation_PatchOrderRendering&t;3&lt;&lt;12
DECL|macro|PM3Render2D_FBSourceReadEnable
mdefine_line|#define PM3Render2D_FBSourceReadEnable&t;&t;&t;1&lt;&lt;14
DECL|macro|PM3Render2D_SpanOperation
mdefine_line|#define PM3Render2D_SpanOperation&t;&t;&t;1&lt;&lt;15
DECL|macro|PM3Render2D_Height
mdefine_line|#define PM3Render2D_Height(h)&t;&t;&t;(((h)&amp;0x0fff)&lt;&lt;16)
DECL|macro|PM3Render2D_XPositive
mdefine_line|#define PM3Render2D_XPositive&t;&t;&t;&t;1&lt;&lt;28
DECL|macro|PM3Render2D_YPositive
mdefine_line|#define PM3Render2D_YPositive&t;&t;&t;&t;1&lt;&lt;29
DECL|macro|PM3Render2D_AreaStippleEnable
mdefine_line|#define PM3Render2D_AreaStippleEnable&t;&t;&t;1&lt;&lt;30
DECL|macro|PM3Render2D_TextureEnable
mdefine_line|#define PM3Render2D_TextureEnable&t;&t;&t;1&lt;&lt;31
DECL|macro|PM3Render2DGlyph
mdefine_line|#define PM3Render2DGlyph&t;&t;&t;&t;&t;0xb648
DECL|macro|PM3Render2DGlyph_Width
mdefine_line|#define PM3Render2DGlyph_Width(w)&t;&t;((w)&amp;0x7f)
DECL|macro|PM3Render2DGlyph_Height
mdefine_line|#define PM3Render2DGlyph_Height(h)&t;&t;(((h)&amp;0x7f)&lt;&lt;7)
DECL|macro|PM3Render2DGlyph_XOffset
mdefine_line|#define PM3Render2DGlyph_XOffset(x)&t;&t;(((x)&amp;0x1ff)&lt;&lt;14)
DECL|macro|PM3Render2DGlyph_YOffset
mdefine_line|#define PM3Render2DGlyph_YOffset(y)&t;&t;(((y)&amp;0x1ff)&lt;&lt;23)
DECL|macro|PM3RenderPatchOffset
mdefine_line|#define PM3RenderPatchOffset&t;&t;&t;&t;&t;0xb610
DECL|macro|PM3RenderPatchOffset_XOffset
mdefine_line|#define PM3RenderPatchOffset_XOffset(x)&t;&t;((x)&amp;0xffff)
DECL|macro|PM3RenderPatchOffset_YOffset
mdefine_line|#define PM3RenderPatchOffset_YOffset(y)&t;&t;(((y)&amp;0xffff)&lt;&lt;16)
DECL|macro|PM3RLCount
mdefine_line|#define PM3RLCount&t;&t;&t;&t;&t;&t;0xb678
DECL|macro|PM3RLCount_Count
mdefine_line|#define PM3RLCount_Count(c)&t;&t;&t;((c)&amp;0x0fff)
DECL|macro|PM3RLData
mdefine_line|#define PM3RLData&t;&t;&t;&t;&t;&t;0xb670
multiline_comment|/**********************************************&n;*  GLINT Permedia3 Alias Register             *&n;***********************************************/
DECL|macro|PM3FillBackgroundColor
mdefine_line|#define PM3FillBackgroundColor                                  0x8330
DECL|macro|PM3FillConfig2D0
mdefine_line|#define PM3FillConfig2D0                                        0x8338
DECL|macro|PM3FillConfig2D1
mdefine_line|#define PM3FillConfig2D1                                        0x8360
DECL|macro|PM3FillConfig2D_OpaqueSpan
mdefine_line|#define PM3FillConfig2D_OpaqueSpan                      1&lt;&lt;0
DECL|macro|PM3FillConfig2D_MultiRXBlit
mdefine_line|#define PM3FillConfig2D_MultiRXBlit                     1&lt;&lt;1
DECL|macro|PM3FillConfig2D_UserScissorEnable
mdefine_line|#define PM3FillConfig2D_UserScissorEnable               1&lt;&lt;2
DECL|macro|PM3FillConfig2D_FBDestReadEnable
mdefine_line|#define PM3FillConfig2D_FBDestReadEnable                1&lt;&lt;3
DECL|macro|PM3FillConfig2D_AlphaBlendEnable
mdefine_line|#define PM3FillConfig2D_AlphaBlendEnable                1&lt;&lt;4
DECL|macro|PM3FillConfig2D_DitherEnable
mdefine_line|#define PM3FillConfig2D_DitherEnable                    1&lt;&lt;5
DECL|macro|PM3FillConfig2D_ForegroundROPEnable
mdefine_line|#define PM3FillConfig2D_ForegroundROPEnable             1&lt;&lt;6
DECL|macro|PM3FillConfig2D_ForegroundROP
mdefine_line|#define PM3FillConfig2D_ForegroundROP(rop)              (((rop)&amp;0xf)&lt;&lt;7)
DECL|macro|PM3FillConfig2D_BackgroundROPEnable
mdefine_line|#define PM3FillConfig2D_BackgroundROPEnable             1&lt;&lt;11
DECL|macro|PM3FillConfig2D_BackgroundROP
mdefine_line|#define PM3FillConfig2D_BackgroundROP(rop)              (((rop)&amp;0xf)&lt;&lt;12)
DECL|macro|PM3FillConfig2D_UseConstantSource
mdefine_line|#define PM3FillConfig2D_UseConstantSource               1&lt;&lt;16
DECL|macro|PM3FillConfig2D_FBWriteEnable
mdefine_line|#define PM3FillConfig2D_FBWriteEnable                   1&lt;&lt;17
DECL|macro|PM3FillConfig2D_Blocking
mdefine_line|#define PM3FillConfig2D_Blocking                        1&lt;&lt;18
DECL|macro|PM3FillConfig2D_ExternalSourceData
mdefine_line|#define PM3FillConfig2D_ExternalSourceData              1&lt;&lt;19
DECL|macro|PM3FillConfig2D_LUTModeEnable
mdefine_line|#define PM3FillConfig2D_LUTModeEnable                   1&lt;&lt;20
DECL|macro|PM3FillFBDestReadBufferAddr
mdefine_line|#define PM3FillFBDestReadBufferAddr                             0x8310
DECL|macro|PM3FillFBSourceReadBufferAddr
mdefine_line|#define PM3FillFBSourceReadBufferAddr                           0x8308
DECL|macro|PM3FillFBSourceReadBufferOffset
mdefine_line|#define PM3FillFBSourceReadBufferOffset                         0x8340
DECL|macro|PM3FillFBSourceReadBufferOffset_XOffset
mdefine_line|#define PM3FillFBSourceReadBufferOffset_XOffset(x)     ((x)&amp;0xffff)
DECL|macro|PM3FillFBSourceReadBufferOffset_YOffset
mdefine_line|#define PM3FillFBSourceReadBufferOffset_YOffset(y)      (((y)&amp;0xffff)&lt;&lt;16)
DECL|macro|PM3FillFBWriteBufferAddr
mdefine_line|#define PM3FillFBWriteBufferAddr                                0x8300
DECL|macro|PM3FillForegroundColor0
mdefine_line|#define PM3FillForegroundColor0                                 0x8328
DECL|macro|PM3FillForegroundColor1
mdefine_line|#define PM3FillForegroundColor1                                 0x8358
DECL|macro|PM3FillGlyphPosition
mdefine_line|#define PM3FillGlyphPosition                                    0x8368
DECL|macro|PM3FillGlyphPosition_XOffset
mdefine_line|#define PM3FillGlyphPosition_XOffset(x)                        ((x)&amp;0xffff)
DECL|macro|PM3FillGlyphPosition_YOffset
mdefine_line|#define PM3FillGlyphPosition_YOffset(y)                        (((y)&amp;0xffff)&lt;&lt;16)
DECL|macro|PM3FillRectanglePosition
mdefine_line|#define PM3FillRectanglePosition                                0x8348
DECL|macro|PM3FillRectanglePosition_XOffset
mdefine_line|#define PM3FillRectanglePosition_XOffset(x)            ((x)&amp;0xffff)
DECL|macro|PM3FillRectanglePosition_YOffset
mdefine_line|#define PM3FillRectanglePosition_YOffset(y)            (((y)&amp;0xffff)&lt;&lt;16)
DECL|macro|PM3_REGS_SIZE
mdefine_line|#define PM3_REGS_SIZE           0x10000
DECL|macro|PM3_MAX_PIXCLOCK
mdefine_line|#define PM3_MAX_PIXCLOCK        300000
multiline_comment|/* a few more useful registers &amp; regs value... */
DECL|macro|PM3Sync
mdefine_line|#define PM3Sync 0x8c40
DECL|macro|PM3Sync_Tag
mdefine_line|#define PM3Sync_Tag 0x188
DECL|macro|PM3FilterMode
mdefine_line|#define PM3FilterMode 0x8c00
DECL|macro|PM3FilterModeSync
mdefine_line|#define PM3FilterModeSync 0x400
DECL|macro|PM3OutputFifo
mdefine_line|#define PM3OutputFifo 0x2000
DECL|macro|PM3StatisticMode
mdefine_line|#define PM3StatisticMode 0x8c08
DECL|macro|PM3AreaStippleMode
mdefine_line|#define PM3AreaStippleMode 0x81a0
DECL|macro|AreaStipplePattern0
mdefine_line|#define AreaStipplePattern0&t;&t;&t;&t;&t;(0x8200)
DECL|macro|AreaStipplePattern1
mdefine_line|#define AreaStipplePattern1&t;&t;&t;&t;&t;(0x8208)
DECL|macro|AreaStipplePattern2
mdefine_line|#define AreaStipplePattern2&t;&t;&t;&t;&t;(0x8210)
DECL|macro|AreaStipplePattern3
mdefine_line|#define AreaStipplePattern3&t;&t;&t;&t;&t;(0x8218)
DECL|macro|AreaStipplePattern4
mdefine_line|#define AreaStipplePattern4&t;&t;&t;&t;&t;(0x8220)
DECL|macro|AreaStipplePattern5
mdefine_line|#define AreaStipplePattern5&t;&t;&t;&t;&t;(0x8228)
DECL|macro|AreaStipplePattern6
mdefine_line|#define AreaStipplePattern6&t;&t;&t;&t;&t;(0x8230)
DECL|macro|AreaStipplePattern7
mdefine_line|#define AreaStipplePattern7&t;&t;&t;&t;&t;(0x8238)
DECL|macro|AreaStipplePattern8
mdefine_line|#define AreaStipplePattern8&t;&t;&t;&t;&t;(0x8240)
DECL|macro|AreaStipplePattern9
mdefine_line|#define AreaStipplePattern9&t;&t;&t;&t;&t;(0x8248)
DECL|macro|AreaStipplePattern10
mdefine_line|#define AreaStipplePattern10&t;&t;&t;&t;&t;(0x8250)
DECL|macro|AreaStipplePattern11
mdefine_line|#define AreaStipplePattern11&t;&t;&t;&t;&t;(0x8258)
DECL|macro|AreaStipplePattern12
mdefine_line|#define AreaStipplePattern12&t;&t;&t;&t;&t;(0x8260)
DECL|macro|AreaStipplePattern13
mdefine_line|#define AreaStipplePattern13&t;&t;&t;&t;&t;(0x8268)
DECL|macro|AreaStipplePattern14
mdefine_line|#define AreaStipplePattern14&t;&t;&t;&t;&t;(0x8270)
DECL|macro|AreaStipplePattern15
mdefine_line|#define AreaStipplePattern15&t;&t;&t;&t;&t;(0x8278)
DECL|macro|AreaStipplePattern16
mdefine_line|#define AreaStipplePattern16&t;&t;&t;&t;&t;(0x8280)
DECL|macro|AreaStipplePattern17
mdefine_line|#define AreaStipplePattern17&t;&t;&t;&t;&t;(0x8288)
DECL|macro|AreaStipplePattern18
mdefine_line|#define AreaStipplePattern18&t;&t;&t;&t;&t;(0x8290)
DECL|macro|AreaStipplePattern19
mdefine_line|#define AreaStipplePattern19&t;&t;&t;&t;&t;(0x8298)
DECL|macro|AreaStipplePattern20
mdefine_line|#define AreaStipplePattern20&t;&t;&t;&t;&t;(0x82a0)
DECL|macro|AreaStipplePattern21
mdefine_line|#define AreaStipplePattern21&t;&t;&t;&t;&t;(0x82a8)
DECL|macro|AreaStipplePattern22
mdefine_line|#define AreaStipplePattern22&t;&t;&t;&t;&t;(0x82b0)
DECL|macro|AreaStipplePattern23
mdefine_line|#define AreaStipplePattern23&t;&t;&t;&t;&t;(0x82b8)
DECL|macro|AreaStipplePattern24
mdefine_line|#define AreaStipplePattern24&t;&t;&t;&t;&t;(0x82c0)
DECL|macro|AreaStipplePattern25
mdefine_line|#define AreaStipplePattern25&t;&t;&t;&t;&t;(0x82c8)
DECL|macro|AreaStipplePattern26
mdefine_line|#define AreaStipplePattern26&t;&t;&t;&t;&t;(0x82d0)
DECL|macro|AreaStipplePattern27
mdefine_line|#define AreaStipplePattern27&t;&t;&t;&t;&t;(0x82d8)
DECL|macro|AreaStipplePattern28
mdefine_line|#define AreaStipplePattern28&t;&t;&t;&t;&t;(0x82eo)
DECL|macro|AreaStipplePattern29
mdefine_line|#define AreaStipplePattern29&t;&t;&t;&t;&t;(0x82e8)
DECL|macro|AreaStipplePattern30
mdefine_line|#define AreaStipplePattern30&t;&t;&t;&t;&t;(0x82f0)
DECL|macro|AreaStipplePattern31
mdefine_line|#define AreaStipplePattern31&t;&t;&t;&t;&t;(0x82f8)
DECL|macro|AreaStipplePattern_indexed
mdefine_line|#define AreaStipplePattern_indexed(i)             (0x8200 + ((i) * 0x8))
DECL|macro|PM3DepthMode
mdefine_line|#define PM3DepthMode 0x89a0
DECL|macro|PM3StencilMode
mdefine_line|#define PM3StencilMode 0x8988
DECL|macro|PM3StencilData
mdefine_line|#define PM3StencilData 0x8990
DECL|macro|PM3TextureReadMode
mdefine_line|#define PM3TextureReadMode 0x8670
DECL|macro|PM3FogMode
mdefine_line|#define PM3FogMode 0x8690
DECL|macro|PM3ChromaTestMode
mdefine_line|#define PM3ChromaTestMode 0x8f18
DECL|macro|PM3YUVMode
mdefine_line|#define PM3YUVMode 0x8f00
DECL|macro|PM3BitMaskPattern
mdefine_line|#define PM3BitMaskPattern 0x8068
multiline_comment|/* ***************************** */
multiline_comment|/* ***** pm3fb IOCTL const ***** */
multiline_comment|/* ***************************** */
multiline_comment|/* debug-only IOCTL */
DECL|macro|PM3FBIO_CLEARMEMORY
mdefine_line|#define PM3FBIO_CLEARMEMORY 0x504D3300 /* &squot;PM3&bslash;000&squot; */
DECL|macro|PM3FBIO_CLEARCMAP
mdefine_line|#define PM3FBIO_CLEARCMAP   0x504D3301 /* &squot;PM3&bslash;001&squot; */
multiline_comment|/* common use IOCTL */
DECL|macro|PM3FBIO_RESETCHIP
mdefine_line|#define PM3FBIO_RESETCHIP   0x504D33FF /* &squot;PM3&bslash;377&squot; */
multiline_comment|/* ***************************************** */
multiline_comment|/* ***** pm3fb useful define and macro ***** */
multiline_comment|/* ***************************************** */
multiline_comment|/* kernel -specific definitions */
multiline_comment|/* what kernel is this ? */
macro_line|#if ((LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,5,0)) &amp;&amp; (LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,6,0)))
DECL|macro|KERNEL_2_5
mdefine_line|#define KERNEL_2_5
macro_line|#endif
macro_line|#if ((LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,4,0)) &amp;&amp; (LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,5,0)))
DECL|macro|KERNEL_2_4
mdefine_line|#define KERNEL_2_4
macro_line|#endif
macro_line|#if ((LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,2,0)) &amp;&amp; (LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,3,0))) 
DECL|macro|KERNEL_2_2
mdefine_line|#define KERNEL_2_2
multiline_comment|/* pci_resource_start, available in 2.2.18 */
macro_line|#include &lt;linux/kcomp.h&gt;
macro_line|#ifdef CONFIG_FB_OF
DECL|macro|SUPPORT_FB_OF
mdefine_line|#define SUPPORT_FB_OF
macro_line|#endif
macro_line|#endif
macro_line|#if (!defined(KERNEL_2_2)) &amp;&amp; (!defined(KERNEL_2_4)) &amp;&amp; (!defined(KERNEL_2_5))
macro_line|#error &quot;Only kernel 2.2.x, kernel 2.4.y and kernel 2.5.z might work&quot;
macro_line|#endif
multiline_comment|/* not sure if/why it&squot;s needed. doesn&squot;t work without on my PowerMac... */
macro_line|#ifdef __BIG_ENDIAN
DECL|macro|MUST_BYTESWAP
mdefine_line|#define MUST_BYTESWAP
macro_line|#endif
multiline_comment|/* for compatibility between 2.5, 2.4 and 2.2 */
macro_line|#ifndef B_FREE
DECL|macro|B_FREE
mdefine_line|#define B_FREE   -1
macro_line|#endif
multiline_comment|/* permedia3 -specific definitions */
DECL|macro|PM3_SCALE_TO_CLOCK
mdefine_line|#define PM3_SCALE_TO_CLOCK(pr, fe, po) ((2 * PM3_REF_CLOCK * fe) / (pr * (1 &lt;&lt; (po))))
DECL|macro|PICOS2KHZ
mdefine_line|#define PICOS2KHZ(a) (1000000000UL/(a))
DECL|macro|KHZ2PICOS
mdefine_line|#define KHZ2PICOS(a) (1000000000UL/(a))
multiline_comment|/* in case it&squot;s not in linux/pci.h */
macro_line|#ifndef PCI_DEVICE_ID_3DLABS_PERMEDIA3
DECL|macro|PCI_DEVICE_ID_3DLABS_PERMEDIA3
mdefine_line|#define PCI_DEVICE_ID_3DLABS_PERMEDIA3 0x000a
macro_line|#endif
multiline_comment|/* max number of simultaneous board */
multiline_comment|/* warning : make sure module array def&squot;s are coherent with PM3_MAX_BOARD */
DECL|macro|PM3_MAX_BOARD
mdefine_line|#define PM3_MAX_BOARD 4
DECL|macro|PM3_MAX_BOARD_MODULE_ARRAY_SHORT
mdefine_line|#define PM3_MAX_BOARD_MODULE_ARRAY_SHORT &quot;1-4h&quot;
DECL|macro|PM3_MAX_BOARD_MODULE_ARRAY_STRING
mdefine_line|#define PM3_MAX_BOARD_MODULE_ARRAY_STRING &quot;1-4s&quot;
multiline_comment|/* max size of options */
DECL|macro|PM3_OPTIONS_SIZE
mdefine_line|#define PM3_OPTIONS_SIZE 256
multiline_comment|/* max size of font name */
DECL|macro|PM3_FONTNAME_SIZE
mdefine_line|#define PM3_FONTNAME_SIZE 40
multiline_comment|/* do we want accelerated console  */
DECL|macro|PM3FB_USE_ACCEL
mdefine_line|#define PM3FB_USE_ACCEL 1
multiline_comment|/* useful ? */
DECL|macro|CHAR_IS_NUM
mdefine_line|#define CHAR_IS_NUM(a)  ((((a) &gt;= &squot;0&squot;) &amp;&amp; ((a) &lt;= &squot;9&squot;)) ? 1 : 0)
multiline_comment|/* for driver debugging ONLY */
multiline_comment|/* 0 = assert only, 1 = error, 2 = info, 3+ = verbose */
multiline_comment|/* define PM3FB_MASTER_DEBUG 1 */
macro_line|#if defined(PM3FB_MASTER_DEBUG) &amp;&amp; (PM3FB_MASTER_DEBUG &gt;= 3)
DECL|macro|PM3FB_TRACE
mdefine_line|#define PM3FB_TRACE
macro_line|#endif /* defined(PM3FB_MASTER_DEBUG) &amp;&amp; (PM3FB_MASTER_DEBUG &gt;= 3) */
macro_line|#ifdef PM3FB_MASTER_DEBUG
DECL|macro|DPRINTK
mdefine_line|#define DPRINTK(l,a,b...) do { if ((l) &lt;= PM3FB_MASTER_DEBUG) printk(&quot;pm3fb: %s: &quot; a, __FUNCTION__ , ## b); } while (0)
DECL|macro|DASSERT
mdefine_line|#define DASSERT(t,a,b...) do { if (!(t)) printk(&quot;pm3fb: _assert failed: %s: &quot; a, __FUNCTION__ , ## b); } while (0)
macro_line|#ifdef PM3FB_TRACE
DECL|macro|DTRACE
mdefine_line|#define DTRACE printk(&quot;pm3fb: _enter %s&bslash;n&quot;, __FUNCTION__)
macro_line|#else /* PM3FB_TRACE */
DECL|macro|DTRACE
mdefine_line|#define DTRACE
macro_line|#endif /* PM3FB_TRACE */
macro_line|#else /* PM3FB_MASTER_DEBUG */
DECL|macro|DPRINTK
mdefine_line|#define DPRINTK(l,a,b...)
DECL|macro|DASSERT
mdefine_line|#define DASSERT(t,a,b...)
DECL|macro|DTRACE
mdefine_line|#define DTRACE
macro_line|#endif /* PM3FB_MASTER_DEBUG */
macro_line|#if defined(PM3FB_MASTER_DEBUG) &amp;&amp; (PM3FB_MASTER_DEBUG &gt;= 2)
DECL|macro|PM3_SHOW_CUR_MODE
mdefine_line|#define PM3_SHOW_CUR_MODE pm3fb_show_cur_mode(l_fb_info)
macro_line|#else
DECL|macro|PM3_SHOW_CUR_MODE
mdefine_line|#define PM3_SHOW_CUR_MODE /* pm3fb_show_cur_mode() */
macro_line|#endif
multiline_comment|/* ******************************************** */
multiline_comment|/* ***** A bunch of register-access macro ***** */
multiline_comment|/* ******************************************** */
macro_line|#ifdef KERNEL_2_2
macro_line|#ifdef MUST_BYTESWAP /* we are writing big_endian to big_endian through a little_endian macro */
DECL|macro|PM3_READ_REG
mdefine_line|#define PM3_READ_REG(r) __swab32(readl((l_fb_info-&gt;vIOBase + r)))
DECL|macro|PM3_WRITE_REG
mdefine_line|#define PM3_WRITE_REG(r, v) writel(__swab32(v), (l_fb_info-&gt;vIOBase + r))
macro_line|#else /* MUST_BYTESWAP */
DECL|macro|PM3_WRITE_REG
mdefine_line|#define PM3_WRITE_REG(r, v) writel(v, (l_fb_info-&gt;vIOBase + r))
DECL|macro|PM3_READ_REG
mdefine_line|#define PM3_READ_REG(r) readl((l_fb_info-&gt;vIOBase + r))
macro_line|#endif /* MUST_BYTESWAP */
macro_line|#endif /* KERNEL_2_2 */
macro_line|#if (defined KERNEL_2_4) || (defined KERNEL_2_5) /* native-endian access */
DECL|macro|PM3_WRITE_REG
mdefine_line|#define PM3_WRITE_REG(r, v) fb_writel(v, (l_fb_info-&gt;vIOBase + r))
DECL|macro|PM3_READ_REG
mdefine_line|#define PM3_READ_REG(r) fb_readl((l_fb_info-&gt;vIOBase + r))
macro_line|#endif /* KERNEL_2_4 or KERNEL_2_5 */
DECL|macro|depth2bpp
mdefine_line|#define depth2bpp(d) ((d + 7L) &amp; ~7L)
DECL|macro|depth2ByPP
mdefine_line|#define depth2ByPP(d) (depth2bpp(d) / 8)
DECL|macro|depth_supported
mdefine_line|#define depth_supported(d) ((d == 8) || (d == 12) || (d == 15) || (d == 16) || (d==32))
DECL|macro|PM3_WAIT
mdefine_line|#define PM3_WAIT(n) &bslash;&n;do{ &bslash;&n;&t;while(PM3_READ_REG(PM3InFIFOSpace)&lt;(n)); &bslash;&n;} while(0)
DECL|macro|PM3_DELAY
mdefine_line|#define PM3_DELAY(x) do { &bslash;&n;        int delay = x; &bslash;&n;        unsigned char tmp; &bslash;&n;        while(delay--){tmp = PM3_READ_REG(PM3InFIFOSpace);}; &bslash;&n;} while(0)
DECL|macro|PM3_SLOW_WRITE_REG
mdefine_line|#define PM3_SLOW_WRITE_REG(r,v)&t;&bslash;&n;do{                             &bslash;&n;    DASSERT((l_fb_info-&gt;vIOBase != (unsigned char*)(-1)), &quot;l_fb_info-&gt;vIOBase mapped in slow write&bslash;n&quot;); &bslash;&n;&t;mb();                   &bslash;&n;&t;PM3_WAIT(1);            &bslash;&n;&t;mb();                   &bslash;&n;    PM3_WRITE_REG(r,v);     &bslash;&n;} while(0)
DECL|macro|PM3_SET_INDEX
mdefine_line|#define PM3_SET_INDEX(index) &bslash;&n;do{ &bslash;&n;&t;PM3_SLOW_WRITE_REG(PM3RD_IndexHigh,(((index)&gt;&gt;8)&amp;0xff)); &bslash;&n;&t;PM3_SLOW_WRITE_REG(PM3RD_IndexLow,((index)&amp;0xff)); &bslash;&n;} while(0)
DECL|macro|PM3_WRITE_DAC_REG
mdefine_line|#define PM3_WRITE_DAC_REG(r, v) &bslash;&n;do { &bslash;&n;     DASSERT((l_fb_info-&gt;vIOBase != (unsigned char*)(-1)), &quot;l_fb_info-&gt;vIOBase mapped in write dac reg&bslash;n&quot;); &bslash;&n;     PM3_SET_INDEX(r); &bslash;&n;     mb(); &bslash;&n;     PM3_WRITE_REG(PM3RD_IndexedData, v); &bslash;&n;} while (0)
multiline_comment|/* next one is really a function, added as a macro to be consistent */
DECL|macro|PM3_READ_DAC_REG
mdefine_line|#define PM3_READ_DAC_REG(r) pm3fb_read_dac_reg(l_fb_info, r)
DECL|macro|PM3_COLOR
mdefine_line|#define PM3_COLOR(c) &bslash;&n;do { &bslash;&n;  if (l_fb_info-&gt;current_par-&gt;depth == 8) &bslash;&n;    { &bslash;&n;      c = (c &amp; 0xFF); &bslash;&n;      c = c | (c &lt;&lt; 8); &bslash;&n;    } &bslash;&n;  if ((l_fb_info-&gt;current_par-&gt;depth == 8) || (depth2bpp(l_fb_info-&gt;current_par-&gt;depth) == 16)) &bslash;&n;    { &bslash;&n;      c = (c &amp; 0xFFFF); &bslash;&n;      c = c | (c &lt;&lt; 16); &bslash;&n;    } &bslash;&n;} while (0)
macro_line|#endif PM3FB_H
eof
