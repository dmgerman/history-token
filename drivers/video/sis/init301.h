multiline_comment|/* $XFree86: xc/programs/Xserver/hw/xfree86/drivers/sis/init301.h,v 1.4 2000/12/02 01:16:17 dawes Exp $ */
macro_line|#ifndef  _INIT301_
DECL|macro|_INIT301_
mdefine_line|#define  _INIT301_
macro_line|#include &quot;osdef.h&quot;
macro_line|#include &quot;initdef.h&quot;
macro_line|#include &quot;vgatypes.h&quot;
macro_line|#include &quot;vstruct.h&quot;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/sisfb.h&gt;
DECL|variable|SiS_SetFlag
id|USHORT
id|SiS_SetFlag
suffix:semicolon
DECL|variable|SiS_RVBHCFACT
DECL|variable|SiS_RVBHCMAX
DECL|variable|SiS_RVBHRS
id|USHORT
id|SiS_RVBHCFACT
comma
id|SiS_RVBHCMAX
comma
id|SiS_RVBHRS
suffix:semicolon
DECL|variable|SiS_VGAVT
DECL|variable|SiS_VGAHT
id|USHORT
id|SiS_VGAVT
comma
id|SiS_VGAHT
suffix:semicolon
DECL|variable|SiS_VT
DECL|variable|SiS_HT
id|USHORT
id|SiS_VT
comma
id|SiS_HT
suffix:semicolon
DECL|variable|SiS_VGAVDE
DECL|variable|SiS_VGAHDE
id|USHORT
id|SiS_VGAVDE
comma
id|SiS_VGAHDE
suffix:semicolon
DECL|variable|SiS_VDE
DECL|variable|SiS_HDE
id|USHORT
id|SiS_VDE
comma
id|SiS_HDE
suffix:semicolon
DECL|variable|SiS_NewFlickerMode
DECL|variable|SiS_RY1COE
DECL|variable|SiS_RY2COE
DECL|variable|SiS_RY3COE
DECL|variable|SiS_RY4COE
id|USHORT
id|SiS_NewFlickerMode
comma
id|SiS_RY1COE
comma
id|SiS_RY2COE
comma
id|SiS_RY3COE
comma
id|SiS_RY4COE
suffix:semicolon
DECL|variable|SiS_LCDHDES
DECL|variable|SiS_LCDVDES
id|USHORT
id|SiS_LCDHDES
comma
id|SiS_LCDVDES
suffix:semicolon
DECL|variable|SiS_DDC_Port
id|USHORT
id|SiS_DDC_Port
suffix:semicolon
DECL|variable|SiS_DDC_Index
id|USHORT
id|SiS_DDC_Index
suffix:semicolon
DECL|variable|SiS_DDC_DataShift
id|USHORT
id|SiS_DDC_DataShift
suffix:semicolon
DECL|variable|SiS_DDC_DeviceAddr
id|USHORT
id|SiS_DDC_DeviceAddr
suffix:semicolon
DECL|variable|SiS_DDC_Flag
id|USHORT
id|SiS_DDC_Flag
suffix:semicolon
DECL|variable|SiS_DDC_ReadAddr
id|USHORT
id|SiS_DDC_ReadAddr
suffix:semicolon
DECL|variable|SiS_DDC_Buffer
id|USHORT
id|SiS_DDC_Buffer
suffix:semicolon
r_extern
id|USHORT
id|SiS_CRT1Mode
suffix:semicolon
r_extern
id|USHORT
id|SiS_P3c4
comma
id|SiS_P3d4
suffix:semicolon
multiline_comment|/*extern   USHORT      SiS_P3c0,SiS_P3ce,SiS_P3c2;*/
r_extern
id|USHORT
id|SiS_P3ca
suffix:semicolon
multiline_comment|/*extern   USHORT      SiS_P3c6,SiS_P3c7,SiS_P3c8;*/
r_extern
id|USHORT
id|SiS_P3c9
suffix:semicolon
r_extern
id|USHORT
id|SiS_P3da
suffix:semicolon
r_extern
id|USHORT
id|SiS_Part1Port
comma
id|SiS_Part2Port
suffix:semicolon
r_extern
id|USHORT
id|SiS_Part3Port
comma
id|SiS_Part4Port
comma
id|SiS_Part5Port
suffix:semicolon
r_extern
id|USHORT
id|SiS_MDA_DAC
(braket
)braket
suffix:semicolon
r_extern
id|USHORT
id|SiS_CGA_DAC
(braket
)braket
suffix:semicolon
r_extern
id|USHORT
id|SiS_EGA_DAC
(braket
)braket
suffix:semicolon
r_extern
id|USHORT
id|SiS_VGA_DAC
(braket
)braket
suffix:semicolon
r_extern
id|USHORT
id|SiS_ModeType
suffix:semicolon
r_extern
id|USHORT
id|SiS_SelectCRT2Rate
suffix:semicolon
r_extern
id|USHORT
id|SiS_IF_DEF_LVDS
suffix:semicolon
r_extern
id|USHORT
id|SiS_IF_DEF_TRUMPION
suffix:semicolon
r_extern
id|USHORT
id|SiS_IF_DEF_CH7005
suffix:semicolon
r_extern
id|USHORT
id|SiS_IF_DEF_HiVision
suffix:semicolon
r_extern
id|USHORT
id|SiS_IF_DEF_DSTN
suffix:semicolon
multiline_comment|/*add for dstn */
r_extern
id|USHORT
id|SiS_VBInfo
suffix:semicolon
r_extern
id|USHORT
id|SiS_VBType
suffix:semicolon
multiline_comment|/*301b */
r_extern
id|USHORT
id|SiS_LCDResInfo
suffix:semicolon
r_extern
id|USHORT
id|SiS_LCDTypeInfo
suffix:semicolon
r_extern
id|USHORT
id|SiS_LCDInfo
suffix:semicolon
r_extern
id|BOOLEAN
id|SiS_SearchVBModeID
(paren
id|ULONG
comma
id|USHORT
)paren
suffix:semicolon
r_extern
id|BOOLEAN
id|SiS_Is301B
(paren
id|USHORT
id|BaseAddr
)paren
suffix:semicolon
multiline_comment|/*301b */
r_extern
id|BOOLEAN
id|SiS_IsDisableCRT2
(paren
id|USHORT
id|BaseAddr
)paren
suffix:semicolon
r_extern
id|BOOLEAN
id|SiS_IsVAMode
(paren
id|USHORT
id|BaseAddr
)paren
suffix:semicolon
r_extern
id|BOOLEAN
id|SiS_IsDualEdge
(paren
id|USHORT
id|BaseAddr
)paren
suffix:semicolon
multiline_comment|/*end 301b*/
r_void
id|SiS_SetDefCRT2ExtRegs
(paren
id|USHORT
id|BaseAddr
)paren
suffix:semicolon
id|USHORT
id|SiS_GetRatePtrCRT2
(paren
id|ULONG
id|ROMAddr
comma
id|USHORT
id|ModeNo
comma
id|USHORT
id|ModeIdIndex
)paren
suffix:semicolon
id|BOOLEAN
id|SiS_AjustCRT2Rate
(paren
id|ULONG
id|ROMAddr
comma
id|USHORT
id|ModeNo
comma
id|USHORT
id|MODEIdIndex
comma
id|USHORT
id|RefreshRateTableIndex
comma
id|USHORT
op_star
id|i
)paren
suffix:semicolon
r_void
id|SiS_SaveCRT2Info
(paren
id|USHORT
id|ModeNo
)paren
suffix:semicolon
r_void
id|SiS_GetCRT2Data
(paren
id|ULONG
id|ROMAddr
comma
id|USHORT
id|ModeNo
comma
id|USHORT
id|ModeIdIndex
comma
id|USHORT
id|RefreshRateTableIndex
)paren
suffix:semicolon
r_void
id|SiS_GetCRT2DataLVDS
(paren
id|ULONG
id|ROMAddr
comma
id|USHORT
id|ModeNo
comma
id|USHORT
id|ModeIdIndex
comma
id|USHORT
id|RefreshRateTableIndex
)paren
suffix:semicolon
r_void
id|SiS_GetCRT2PtrA
(paren
id|ULONG
id|ROMAddr
comma
id|USHORT
id|ModeNo
comma
id|USHORT
id|ModeIdIndex
comma
id|USHORT
id|RefreshRateTableIndex
comma
id|USHORT
op_star
id|CRT2Index
comma
id|USHORT
op_star
id|ResIndex
)paren
suffix:semicolon
multiline_comment|/*301b */
r_void
id|SiS_GetCRT2Data301
(paren
id|ULONG
id|ROMAddr
comma
id|USHORT
id|ModeNo
comma
id|USHORT
id|ModeIdIndex
comma
id|USHORT
id|RefreshRateTableIndex
)paren
suffix:semicolon
id|USHORT
id|SiS_GetResInfo
(paren
id|ULONG
id|ROMAddr
comma
id|USHORT
id|ModeNo
comma
id|USHORT
id|ModeIdIndex
)paren
suffix:semicolon
r_void
id|SiS_GetCRT2ResInfo
(paren
id|ULONG
id|ROMAddr
comma
id|USHORT
id|ModeNo
comma
id|USHORT
id|ModeIdIndex
)paren
suffix:semicolon
r_void
id|SiS_GetRAMDAC2DATA
(paren
id|ULONG
id|ROMAddr
comma
id|USHORT
id|ModeNo
comma
id|USHORT
id|ModeIdIndex
comma
id|USHORT
id|RefreshRateTableIndex
)paren
suffix:semicolon
r_void
id|SiS_GetCRT2Ptr
(paren
id|ULONG
id|ROMAddr
comma
id|USHORT
id|ModeNo
comma
id|USHORT
id|ModeIdIndex
comma
id|USHORT
id|RefreshRateTableIndex
comma
id|USHORT
op_star
id|CRT2Index
comma
id|USHORT
op_star
id|ResIndex
)paren
suffix:semicolon
r_void
id|SiS_SetCRT2ModeRegs
(paren
id|USHORT
id|BaseAddr
comma
id|USHORT
id|ModeNo
comma
id|PSIS_HW_DEVICE_INFO
)paren
suffix:semicolon
r_void
id|SiS_GetLVDSDesData
(paren
id|ULONG
id|ROMAddr
comma
id|USHORT
id|ModeNo
comma
id|USHORT
id|ModeIdIndex
comma
id|USHORT
id|RefreshRateTableIndex
)paren
suffix:semicolon
r_void
id|SiS_SetCRT2Offset
(paren
id|USHORT
id|Part1Port
comma
id|ULONG
id|ROMAddr
comma
id|USHORT
id|ModeNo
comma
id|USHORT
id|ModeIdIndex
comma
id|USHORT
id|RefreshRateTableIndex
comma
id|PSIS_HW_DEVICE_INFO
id|HwDeviceExtension
)paren
suffix:semicolon
id|USHORT
id|SiS_GetOffset
(paren
id|ULONG
id|ROMAddr
comma
id|USHORT
id|ModeNo
comma
id|USHORT
id|ModeIdIndex
comma
id|USHORT
id|RefreshRateTableIndex
comma
id|PSIS_HW_DEVICE_INFO
id|HwDeviceExtension
)paren
suffix:semicolon
id|USHORT
id|SiS_GetColorDepth
(paren
id|ULONG
id|ROMAddr
comma
id|USHORT
id|ModeNo
comma
id|USHORT
id|ModeIdIndex
)paren
suffix:semicolon
id|USHORT
id|SiS_GetVCLK
(paren
id|ULONG
id|ROMAddr
comma
id|USHORT
id|ModeNo
)paren
suffix:semicolon
id|USHORT
id|SiS_GetVCLKPtr
(paren
id|ULONG
id|ROMAddr
comma
id|USHORT
id|ModeNo
)paren
suffix:semicolon
id|USHORT
id|SiS_GetColorTh
(paren
id|ULONG
id|ROMAddr
)paren
suffix:semicolon
id|USHORT
id|SiS_GetMCLK
(paren
id|ULONG
id|ROMAddr
)paren
suffix:semicolon
id|USHORT
id|SiS_GetMCLKPtr
(paren
id|ULONG
id|ROMAddr
)paren
suffix:semicolon
id|USHORT
id|SiS_GetDRAMType
(paren
id|ULONG
id|ROMAddr
)paren
suffix:semicolon
id|USHORT
id|SiS_CalcDelayVB
(paren
r_void
)paren
suffix:semicolon
r_extern
id|USHORT
id|SiS_GetVCLK2Ptr
(paren
id|ULONG
id|ROMAddr
comma
id|USHORT
id|ModeNo
comma
id|USHORT
id|ModeIdIndex
comma
id|USHORT
id|RefreshRateTableIndex
comma
id|PSIS_HW_DEVICE_INFO
id|HwDeviceExtension
)paren
suffix:semicolon
r_void
id|SiS_SetCRT2Sync
(paren
id|USHORT
id|BaseAddr
comma
id|ULONG
id|ROMAddr
comma
id|USHORT
id|ModeNo
comma
id|USHORT
id|RefreshRateTableIndex
)paren
suffix:semicolon
r_void
id|SiS_SetRegANDOR
(paren
id|USHORT
id|Port
comma
id|USHORT
id|Index
comma
id|USHORT
id|DataAND
comma
id|USHORT
id|DataOR
)paren
suffix:semicolon
r_void
id|SiS_SetRegOR
(paren
id|USHORT
id|Port
comma
id|USHORT
id|Index
comma
id|USHORT
id|DataOR
)paren
suffix:semicolon
r_void
id|SiS_SetRegAND
(paren
id|USHORT
id|Port
comma
id|USHORT
id|Index
comma
id|USHORT
id|DataAND
)paren
suffix:semicolon
id|USHORT
id|SiS_GetVGAHT2
(paren
r_void
)paren
suffix:semicolon
r_void
id|SiS_SetGroup2
(paren
id|USHORT
id|BaseAddr
comma
id|ULONG
id|ROMAddr
comma
id|USHORT
id|ModeNo
comma
id|USHORT
id|ModeIdIndex
comma
id|USHORT
id|RefreshRateTableIndex
comma
id|PSIS_HW_DEVICE_INFO
id|HwDeviceExtension
)paren
suffix:semicolon
r_void
id|SiS_SetGroup3
(paren
id|USHORT
id|BaseAddr
comma
id|ULONG
id|ROMAddr
comma
id|USHORT
id|ModeNo
comma
id|USHORT
id|ModeIdIndex
comma
id|PSIS_HW_DEVICE_INFO
id|HwDeviceExtension
)paren
suffix:semicolon
r_void
id|SiS_SetGroup4
(paren
id|USHORT
id|BaseAddr
comma
id|ULONG
id|ROMAddr
comma
id|USHORT
id|ModeNo
comma
id|USHORT
id|ModeIdIndex
comma
id|USHORT
id|RefreshRateTableIndex
comma
id|PSIS_HW_DEVICE_INFO
id|HwDeviceExtension
)paren
suffix:semicolon
r_void
id|SiS_SetGroup5
(paren
id|USHORT
id|BaseAddr
comma
id|ULONG
id|ROMAddr
comma
id|USHORT
id|ModeNo
comma
id|USHORT
id|ModeIdIndex
)paren
suffix:semicolon
r_void
id|SiS_SetCRT2VCLK
(paren
id|USHORT
id|BaseAddr
comma
id|ULONG
id|ROMAddr
comma
id|USHORT
id|ModeNo
comma
id|USHORT
id|ModeIdIndex
comma
id|USHORT
id|RefreshRateTableIndex
comma
id|PSIS_HW_DEVICE_INFO
id|HwDeviceExtension
)paren
suffix:semicolon
r_void
id|SiS_EnableCRT2
(paren
r_void
)paren
suffix:semicolon
r_void
id|SiS_LoadDAC2
(paren
id|ULONG
id|ROMAddr
comma
id|USHORT
id|Part5Port
comma
id|USHORT
id|ModeNo
comma
id|USHORT
id|ModeIdIndex
)paren
suffix:semicolon
r_void
id|SiS_WriteDAC2
(paren
id|USHORT
id|Pdata
comma
id|USHORT
id|dl
comma
id|USHORT
id|ah
comma
id|USHORT
id|al
comma
id|USHORT
id|dh
)paren
suffix:semicolon
r_void
id|SiS_GetVBInfo301
(paren
id|USHORT
id|BaseAddr
comma
id|ULONG
id|ROMAddr
comma
id|USHORT
id|ModeNo
comma
id|USHORT
id|ModeIdIndex
comma
id|PSIS_HW_DEVICE_INFO
id|HwDeviceExtension
)paren
suffix:semicolon
id|BOOLEAN
id|SiS_GetLCDResInfo
(paren
id|ULONG
id|ROMAddr
comma
id|USHORT
id|P3d4
comma
id|USHORT
id|ModeNo
comma
id|USHORT
id|ModeIdIndex
)paren
suffix:semicolon
id|BOOLEAN
id|SiS_BridgeIsOn
(paren
id|USHORT
id|BaseAddr
)paren
suffix:semicolon
id|BOOLEAN
id|SiS_BridgeIsEnable
(paren
id|USHORT
id|BaseAddr
comma
id|PSIS_HW_DEVICE_INFO
)paren
suffix:semicolon
id|BOOLEAN
id|SiS_BridgeInSlave
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*void     SiS_PresetScratchregister(USHORT P3d4);*/
r_void
id|SiS_PresetScratchregister
(paren
id|USHORT
id|SiS_P3d4
comma
id|PSIS_HW_DEVICE_INFO
id|HwDeviceExtension
)paren
suffix:semicolon
r_void
id|SiS_SetTVSystem
(paren
id|VOID
)paren
suffix:semicolon
r_void
id|SiS_LongWait
(paren
id|VOID
)paren
suffix:semicolon
id|USHORT
id|SiS_GetQueueConfig
(paren
id|VOID
)paren
suffix:semicolon
r_void
id|SiS_VBLongWait
(paren
id|VOID
)paren
suffix:semicolon
id|USHORT
id|SiS_GetVCLKLen
(paren
id|ULONG
id|ROMAddr
)paren
suffix:semicolon
id|BOOLEAN
id|SiS_WaitVBRetrace
(paren
id|USHORT
id|BaseAddr
)paren
suffix:semicolon
r_void
id|SiS_SetCRT2ECLK
(paren
id|ULONG
id|ROMAddr
comma
id|USHORT
id|ModeNo
comma
id|USHORT
id|ModeIdIndex
comma
id|USHORT
id|RefreshRateTableIndex
comma
id|PSIS_HW_DEVICE_INFO
id|HwDeviceExtension
)paren
suffix:semicolon
r_void
id|SiS_GetLVDSDesPtr
(paren
id|ULONG
id|ROMAddr
comma
id|USHORT
id|ModeNo
comma
id|USHORT
id|ModeIdIndex
comma
id|USHORT
id|RefreshRateTableIndex
comma
id|USHORT
op_star
id|PanelIndex
comma
id|USHORT
op_star
id|ResIndex
)paren
suffix:semicolon
r_void
id|SiS_GetLVDSDesPtrA
(paren
id|ULONG
id|ROMAddr
comma
id|USHORT
id|ModeNo
comma
id|USHORT
id|ModeIdIndex
comma
id|USHORT
id|RefreshRateTableIndex
comma
id|USHORT
op_star
id|PanelIndex
comma
id|USHORT
op_star
id|ResIndex
)paren
suffix:semicolon
multiline_comment|/*301b */
r_void
id|SiS_SetTPData
(paren
id|VOID
)paren
suffix:semicolon
r_void
id|SiS_ModCRT1CRTC
(paren
id|ULONG
id|ROMAddr
comma
id|USHORT
id|ModeNo
comma
id|USHORT
id|ModeIdIndex
comma
id|USHORT
id|RefreshRateTableIndex
)paren
suffix:semicolon
r_extern
id|BOOLEAN
id|SiS_GetLVDSCRT1Ptr
(paren
id|ULONG
id|ROMAddr
comma
id|USHORT
id|ModeNo
comma
id|USHORT
id|ModeIdIndex
comma
id|USHORT
id|RefreshRateTableIndex
comma
id|USHORT
op_star
id|ResInfo
comma
id|USHORT
op_star
id|DisplayType
)paren
suffix:semicolon
r_void
id|SiS_SetCHTVReg
(paren
id|ULONG
id|ROMAddr
comma
id|USHORT
id|ModeNo
comma
id|USHORT
id|ModeIdIndex
comma
id|USHORT
id|RefreshRateTableIndex
)paren
suffix:semicolon
r_void
id|SiS_SetCHTVRegANDOR
(paren
id|USHORT
id|tempax
comma
id|USHORT
id|tempbh
)paren
suffix:semicolon
r_void
id|SiS_GetCHTVRegPtr
(paren
id|ULONG
id|ROMAddr
comma
id|USHORT
id|ModeNo
comma
id|USHORT
id|ModeIdIndex
comma
id|USHORT
id|RefreshRateTableIndex
)paren
suffix:semicolon
r_void
id|SiS_SetCH7005
(paren
id|USHORT
id|tempax
)paren
suffix:semicolon
id|USHORT
id|SiS_GetCH7005
(paren
id|USHORT
id|tempax
)paren
suffix:semicolon
r_void
id|SiS_SetSwitchDDC2
(paren
r_void
)paren
suffix:semicolon
r_void
id|SiS_SetStart
(paren
r_void
)paren
suffix:semicolon
r_void
id|SiS_SetStop
(paren
r_void
)paren
suffix:semicolon
r_void
id|SiS_DDC2Delay
(paren
r_void
)paren
suffix:semicolon
r_void
id|SiS_SetSCLKLow
(paren
r_void
)paren
suffix:semicolon
r_void
id|SiS_SetSCLKHigh
(paren
r_void
)paren
suffix:semicolon
id|USHORT
id|SiS_ReadDDC2Data
(paren
id|USHORT
id|tempax
)paren
suffix:semicolon
id|USHORT
id|SiS_WriteDDC2Data
(paren
id|USHORT
id|tempax
)paren
suffix:semicolon
id|USHORT
id|SiS_CheckACK
(paren
r_void
)paren
suffix:semicolon
r_void
id|SiS_OEM310Setting
(paren
id|PSIS_HW_DEVICE_INFO
id|HwDeviceExtension
comma
id|USHORT
id|BaseAddr
comma
id|ULONG
id|ROMAddr
comma
id|USHORT
id|ModeNo
comma
id|USHORT
id|ModeIdIndex
)paren
suffix:semicolon
r_void
id|SiS_OEM300Setting
(paren
id|PSIS_HW_DEVICE_INFO
id|HwDeviceExtension
comma
id|USHORT
id|BaseAddr
comma
id|ULONG
id|ROMAddr
comma
id|USHORT
id|ModeNo
)paren
suffix:semicolon
id|USHORT
id|GetRevisionID
(paren
id|PSIS_HW_DEVICE_INFO
id|HwDeviceExtension
)paren
suffix:semicolon
r_extern
r_void
id|SiS_SetReg1
(paren
id|USHORT
comma
id|USHORT
comma
id|USHORT
)paren
suffix:semicolon
r_extern
r_void
id|SiS_SetReg3
(paren
id|USHORT
comma
id|USHORT
)paren
suffix:semicolon
r_extern
id|UCHAR
id|SiS_GetReg1
(paren
id|USHORT
comma
id|USHORT
)paren
suffix:semicolon
r_extern
id|UCHAR
id|SiS_GetReg2
(paren
id|USHORT
)paren
suffix:semicolon
r_extern
id|BOOLEAN
id|SiS_SearchModeID
(paren
id|ULONG
id|ROMAddr
comma
id|USHORT
id|ModeNo
comma
id|USHORT
op_star
id|ModeIdIndex
)paren
suffix:semicolon
r_extern
id|BOOLEAN
id|SiS_GetRatePtr
(paren
id|ULONG
comma
id|USHORT
)paren
suffix:semicolon
r_extern
r_void
id|SiS_SetReg4
(paren
id|USHORT
comma
id|ULONG
)paren
suffix:semicolon
r_extern
id|ULONG
id|SiS_GetReg3
(paren
id|USHORT
)paren
suffix:semicolon
r_extern
r_void
id|SiS_DisplayOff
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|SiS_CRT2AutoThreshold
(paren
id|USHORT
id|BaseAddr
)paren
suffix:semicolon
r_extern
r_void
id|SiS_DisplayOn
(paren
r_void
)paren
suffix:semicolon
r_extern
id|UCHAR
id|SiS_GetModePtr
(paren
id|ULONG
id|ROMAddr
comma
id|USHORT
id|ModeNo
comma
id|USHORT
id|ModeIdIndex
)paren
suffix:semicolon
r_extern
id|UCHAR
id|SiS_Get310DRAMType
(paren
id|ULONG
id|ROMAddr
)paren
suffix:semicolon
id|BOOLEAN
id|SiS_SetCRT2Group301
(paren
id|USHORT
id|BaseAddr
comma
id|ULONG
id|ROMAddr
comma
id|USHORT
id|ModeNo
comma
id|PSIS_HW_DEVICE_INFO
id|HwDeviceExtension
)paren
suffix:semicolon
r_void
id|SiS_SetGroup1
(paren
id|USHORT
id|BaseAddr
comma
id|ULONG
id|ROMAddr
comma
id|USHORT
id|ModeNo
comma
id|USHORT
id|ModeIdIndex
comma
id|PSIS_HW_DEVICE_INFO
id|HwDeviceExtension
comma
id|USHORT
id|RefreshRateTableIndex
)paren
suffix:semicolon
r_void
id|SiS_SetGroup1_LVDS
(paren
id|USHORT
id|BaseAddr
comma
id|ULONG
id|ROMAddr
comma
id|USHORT
id|ModeNo
comma
id|USHORT
id|ModeIdIndex
comma
id|PSIS_HW_DEVICE_INFO
id|HwDeviceExtension
comma
id|USHORT
id|RefreshRateTableIndex
)paren
suffix:semicolon
r_void
id|SiS_SetGroup1_LCDA
(paren
id|USHORT
id|BaseAddr
comma
id|ULONG
id|ROMAddr
comma
id|USHORT
id|ModeNo
comma
id|USHORT
id|ModeIdIndex
comma
id|PSIS_HW_DEVICE_INFO
id|HwDeviceExtension
comma
id|USHORT
id|RefreshRateTableIndex
)paren
suffix:semicolon
multiline_comment|/*301b */
r_void
id|SiS_SetGroup1_301
(paren
id|USHORT
id|BaseAddr
comma
id|ULONG
id|ROMAddr
comma
id|USHORT
id|ModeNo
comma
id|USHORT
id|ModeIdIndex
comma
id|PSIS_HW_DEVICE_INFO
id|HwDeviceExtension
comma
id|USHORT
id|RefreshRateTableIndex
)paren
suffix:semicolon
r_void
id|SiS_SetCRT2FIFO
(paren
id|USHORT
id|Part1Port
comma
id|ULONG
id|ROMAddr
comma
id|USHORT
id|ModeNo
comma
id|PSIS_HW_DEVICE_INFO
id|HwDeviceExtension
)paren
suffix:semicolon
r_void
id|SiS_SetCRT2FIFO2
(paren
id|USHORT
id|Part1Port
comma
id|ULONG
id|ROMAddr
comma
id|USHORT
id|ModeNo
comma
id|PSIS_HW_DEVICE_INFO
id|HwDeviceExtension
)paren
suffix:semicolon
id|BOOLEAN
id|SiS_GetLCDDDCInfo
(paren
id|PSIS_HW_DEVICE_INFO
id|HwDeviceExtension
)paren
suffix:semicolon
r_void
id|SiS_UnLockCRT2
(paren
id|PSIS_HW_DEVICE_INFO
comma
id|USHORT
id|BaseAddr
)paren
suffix:semicolon
r_void
id|SiS_LockCRT2
(paren
id|PSIS_HW_DEVICE_INFO
comma
id|USHORT
id|BaseAddr
)paren
suffix:semicolon
r_void
id|SiS_DisableBridge
(paren
id|PSIS_HW_DEVICE_INFO
comma
id|USHORT
id|BaseAddr
)paren
suffix:semicolon
r_void
id|SiS_EnableBridge
(paren
id|PSIS_HW_DEVICE_INFO
comma
id|USHORT
id|BaseAddr
)paren
suffix:semicolon
r_void
id|SiS_SetPanelDelay
(paren
id|USHORT
id|DelayTime
)paren
suffix:semicolon
r_void
id|SiS_LCD_Wait_Time
(paren
id|UCHAR
id|DelayTime
)paren
suffix:semicolon
macro_line|#endif
eof