macro_line|#ifndef _INIT_
DECL|macro|_INIT_
mdefine_line|#define _INIT_
macro_line|#include &quot;osdef.h&quot;
macro_line|#include &quot;initdef.h&quot;
macro_line|#include &quot;vgatypes.h&quot;
macro_line|#include &quot;vstruct.h&quot;
macro_line|#ifdef TC
macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;string.h&gt;
macro_line|#include &lt;conio.h&gt;
macro_line|#include &lt;dos.h&gt;
macro_line|#include &lt;stdlib.h&gt;
macro_line|#endif
macro_line|#ifdef LINUX_XF86
macro_line|#include &quot;xf86.h&quot;
macro_line|#include &quot;xf86Pci.h&quot;
macro_line|#include &quot;xf86PciInfo.h&quot;
macro_line|#include &quot;xf86_OSproc.h&quot;
macro_line|#include &quot;sis.h&quot;
macro_line|#include &quot;sis_regs.h&quot;
macro_line|#endif
macro_line|#ifdef LINUX_KERNEL
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,5,0)
macro_line|#include &lt;linux/sisfb.h&gt;
macro_line|#else
macro_line|#include &lt;video/sisfb.h&gt;
macro_line|#endif
macro_line|#endif
macro_line|#ifdef WIN2000
macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;string.h&gt;
macro_line|#include &lt;miniport.h&gt;
macro_line|#include &quot;dderror.h&quot;
macro_line|#include &quot;devioctl.h&quot;
macro_line|#include &quot;miniport.h&quot;
macro_line|#include &quot;ntddvdeo.h&quot;
macro_line|#include &quot;video.h&quot;
macro_line|#include &quot;sisv.h&quot;
macro_line|#include &quot;tools.h&quot;
macro_line|#endif
DECL|variable|SiS_DRAMType
r_const
id|USHORT
id|SiS_DRAMType
(braket
l_int|17
)braket
(braket
l_int|5
)braket
op_assign
initialization_block
suffix:semicolon
DECL|variable|SiS_SDRDRAM_TYPE
r_const
id|USHORT
id|SiS_SDRDRAM_TYPE
(braket
l_int|13
)braket
(braket
l_int|5
)braket
op_assign
(brace
(brace
l_int|2
comma
l_int|12
comma
l_int|9
comma
l_int|64
comma
l_int|0x35
)brace
comma
(brace
l_int|1
comma
l_int|13
comma
l_int|9
comma
l_int|64
comma
l_int|0x44
)brace
comma
(brace
l_int|2
comma
l_int|12
comma
l_int|8
comma
l_int|32
comma
l_int|0x31
)brace
comma
(brace
l_int|2
comma
l_int|11
comma
l_int|9
comma
l_int|32
comma
l_int|0x25
)brace
comma
(brace
l_int|1
comma
l_int|12
comma
l_int|9
comma
l_int|32
comma
l_int|0x34
)brace
comma
(brace
l_int|1
comma
l_int|13
comma
l_int|8
comma
l_int|32
comma
l_int|0x40
)brace
comma
(brace
l_int|2
comma
l_int|11
comma
l_int|8
comma
l_int|16
comma
l_int|0x21
)brace
comma
(brace
l_int|1
comma
l_int|12
comma
l_int|8
comma
l_int|16
comma
l_int|0x30
)brace
comma
(brace
l_int|1
comma
l_int|11
comma
l_int|9
comma
l_int|16
comma
l_int|0x24
)brace
comma
(brace
l_int|1
comma
l_int|11
comma
l_int|8
comma
l_int|8
comma
l_int|0x20
)brace
comma
(brace
l_int|2
comma
l_int|9
comma
l_int|8
comma
l_int|4
comma
l_int|0x01
)brace
comma
(brace
l_int|1
comma
l_int|10
comma
l_int|8
comma
l_int|4
comma
l_int|0x10
)brace
comma
(brace
l_int|1
comma
l_int|9
comma
l_int|8
comma
l_int|2
comma
l_int|0x00
)brace
)brace
suffix:semicolon
DECL|variable|SiS_DDRDRAM_TYPE
r_const
id|USHORT
id|SiS_DDRDRAM_TYPE
(braket
l_int|4
)braket
(braket
l_int|5
)braket
op_assign
(brace
(brace
l_int|2
comma
l_int|12
comma
l_int|9
comma
l_int|64
comma
l_int|0x35
)brace
comma
(brace
l_int|2
comma
l_int|12
comma
l_int|8
comma
l_int|32
comma
l_int|0x31
)brace
comma
(brace
l_int|2
comma
l_int|11
comma
l_int|8
comma
l_int|16
comma
l_int|0x21
)brace
comma
(brace
l_int|2
comma
l_int|9
comma
l_int|8
comma
l_int|4
comma
l_int|0x01
)brace
)brace
suffix:semicolon
DECL|variable|SiS_MDA_DAC
r_const
id|USHORT
id|SiS_MDA_DAC
(braket
)braket
op_assign
(brace
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x15
comma
l_int|0x15
comma
l_int|0x15
comma
l_int|0x15
comma
l_int|0x15
comma
l_int|0x15
comma
l_int|0x15
comma
l_int|0x15
comma
l_int|0x15
comma
l_int|0x15
comma
l_int|0x15
comma
l_int|0x15
comma
l_int|0x15
comma
l_int|0x15
comma
l_int|0x15
comma
l_int|0x15
comma
l_int|0x3F
comma
l_int|0x3F
comma
l_int|0x3F
comma
l_int|0x3F
comma
l_int|0x3F
comma
l_int|0x3F
comma
l_int|0x3F
comma
l_int|0x3F
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x15
comma
l_int|0x15
comma
l_int|0x15
comma
l_int|0x15
comma
l_int|0x15
comma
l_int|0x15
comma
l_int|0x15
comma
l_int|0x15
comma
l_int|0x15
comma
l_int|0x15
comma
l_int|0x15
comma
l_int|0x15
comma
l_int|0x15
comma
l_int|0x15
comma
l_int|0x15
comma
l_int|0x15
comma
l_int|0x3F
comma
l_int|0x3F
comma
l_int|0x3F
comma
l_int|0x3F
comma
l_int|0x3F
comma
l_int|0x3F
comma
l_int|0x3F
comma
l_int|0x3F
)brace
suffix:semicolon
DECL|variable|SiS_CGA_DAC
r_const
id|USHORT
id|SiS_CGA_DAC
(braket
)braket
op_assign
(brace
l_int|0x00
comma
l_int|0x10
comma
l_int|0x04
comma
l_int|0x14
comma
l_int|0x01
comma
l_int|0x11
comma
l_int|0x09
comma
l_int|0x15
comma
l_int|0x00
comma
l_int|0x10
comma
l_int|0x04
comma
l_int|0x14
comma
l_int|0x01
comma
l_int|0x11
comma
l_int|0x09
comma
l_int|0x15
comma
l_int|0x2A
comma
l_int|0x3A
comma
l_int|0x2E
comma
l_int|0x3E
comma
l_int|0x2B
comma
l_int|0x3B
comma
l_int|0x2F
comma
l_int|0x3F
comma
l_int|0x2A
comma
l_int|0x3A
comma
l_int|0x2E
comma
l_int|0x3E
comma
l_int|0x2B
comma
l_int|0x3B
comma
l_int|0x2F
comma
l_int|0x3F
comma
l_int|0x00
comma
l_int|0x10
comma
l_int|0x04
comma
l_int|0x14
comma
l_int|0x01
comma
l_int|0x11
comma
l_int|0x09
comma
l_int|0x15
comma
l_int|0x00
comma
l_int|0x10
comma
l_int|0x04
comma
l_int|0x14
comma
l_int|0x01
comma
l_int|0x11
comma
l_int|0x09
comma
l_int|0x15
comma
l_int|0x2A
comma
l_int|0x3A
comma
l_int|0x2E
comma
l_int|0x3E
comma
l_int|0x2B
comma
l_int|0x3B
comma
l_int|0x2F
comma
l_int|0x3F
comma
l_int|0x2A
comma
l_int|0x3A
comma
l_int|0x2E
comma
l_int|0x3E
comma
l_int|0x2B
comma
l_int|0x3B
comma
l_int|0x2F
comma
l_int|0x3F
)brace
suffix:semicolon
DECL|variable|SiS_EGA_DAC
r_const
id|USHORT
id|SiS_EGA_DAC
(braket
)braket
op_assign
(brace
l_int|0x00
comma
l_int|0x10
comma
l_int|0x04
comma
l_int|0x14
comma
l_int|0x01
comma
l_int|0x11
comma
l_int|0x05
comma
l_int|0x15
comma
l_int|0x20
comma
l_int|0x30
comma
l_int|0x24
comma
l_int|0x34
comma
l_int|0x21
comma
l_int|0x31
comma
l_int|0x25
comma
l_int|0x35
comma
l_int|0x08
comma
l_int|0x18
comma
l_int|0x0C
comma
l_int|0x1C
comma
l_int|0x09
comma
l_int|0x19
comma
l_int|0x0D
comma
l_int|0x1D
comma
l_int|0x28
comma
l_int|0x38
comma
l_int|0x2C
comma
l_int|0x3C
comma
l_int|0x29
comma
l_int|0x39
comma
l_int|0x2D
comma
l_int|0x3D
comma
l_int|0x02
comma
l_int|0x12
comma
l_int|0x06
comma
l_int|0x16
comma
l_int|0x03
comma
l_int|0x13
comma
l_int|0x07
comma
l_int|0x17
comma
l_int|0x22
comma
l_int|0x32
comma
l_int|0x26
comma
l_int|0x36
comma
l_int|0x23
comma
l_int|0x33
comma
l_int|0x27
comma
l_int|0x37
comma
l_int|0x0A
comma
l_int|0x1A
comma
l_int|0x0E
comma
l_int|0x1E
comma
l_int|0x0B
comma
l_int|0x1B
comma
l_int|0x0F
comma
l_int|0x1F
comma
l_int|0x2A
comma
l_int|0x3A
comma
l_int|0x2E
comma
l_int|0x3E
comma
l_int|0x2B
comma
l_int|0x3B
comma
l_int|0x2F
comma
l_int|0x3F
)brace
suffix:semicolon
DECL|variable|SiS_VGA_DAC
r_const
id|USHORT
id|SiS_VGA_DAC
(braket
)braket
op_assign
(brace
l_int|0x00
comma
l_int|0x10
comma
l_int|0x04
comma
l_int|0x14
comma
l_int|0x01
comma
l_int|0x11
comma
l_int|0x09
comma
l_int|0x15
comma
l_int|0x2A
comma
l_int|0x3A
comma
l_int|0x2E
comma
l_int|0x3E
comma
l_int|0x2B
comma
l_int|0x3B
comma
l_int|0x2F
comma
l_int|0x3F
comma
l_int|0x00
comma
l_int|0x05
comma
l_int|0x08
comma
l_int|0x0B
comma
l_int|0x0E
comma
l_int|0x11
comma
l_int|0x14
comma
l_int|0x18
comma
l_int|0x1C
comma
l_int|0x20
comma
l_int|0x24
comma
l_int|0x28
comma
l_int|0x2D
comma
l_int|0x32
comma
l_int|0x38
comma
l_int|0x3F
comma
l_int|0x00
comma
l_int|0x10
comma
l_int|0x1F
comma
l_int|0x2F
comma
l_int|0x3F
comma
l_int|0x1F
comma
l_int|0x27
comma
l_int|0x2F
comma
l_int|0x37
comma
l_int|0x3F
comma
l_int|0x2D
comma
l_int|0x31
comma
l_int|0x36
comma
l_int|0x3A
comma
l_int|0x3F
comma
l_int|0x00
comma
l_int|0x07
comma
l_int|0x0E
comma
l_int|0x15
comma
l_int|0x1C
comma
l_int|0x0E
comma
l_int|0x11
comma
l_int|0x15
comma
l_int|0x18
comma
l_int|0x1C
comma
l_int|0x14
comma
l_int|0x16
comma
l_int|0x18
comma
l_int|0x1A
comma
l_int|0x1C
comma
l_int|0x00
comma
l_int|0x04
comma
l_int|0x08
comma
l_int|0x0C
comma
l_int|0x10
comma
l_int|0x08
comma
l_int|0x0A
comma
l_int|0x0C
comma
l_int|0x0E
comma
l_int|0x10
comma
l_int|0x0B
comma
l_int|0x0C
comma
l_int|0x0D
comma
l_int|0x0F
comma
l_int|0x10
)brace
suffix:semicolon
r_void
id|SiS_SetReg1
c_func
(paren
id|USHORT
comma
id|USHORT
comma
id|USHORT
)paren
suffix:semicolon
r_void
id|SiS_SetReg2
c_func
(paren
id|SiS_Private
op_star
comma
id|USHORT
comma
id|USHORT
comma
id|USHORT
)paren
suffix:semicolon
r_void
id|SiS_SetReg3
c_func
(paren
id|USHORT
comma
id|USHORT
)paren
suffix:semicolon
r_void
id|SiS_SetReg4
c_func
(paren
id|USHORT
comma
id|ULONG
)paren
suffix:semicolon
r_void
id|SiS_SetReg5
c_func
(paren
id|USHORT
comma
id|USHORT
)paren
suffix:semicolon
id|UCHAR
id|SiS_GetReg1
c_func
(paren
id|USHORT
comma
id|USHORT
)paren
suffix:semicolon
id|UCHAR
id|SiS_GetReg2
c_func
(paren
id|USHORT
)paren
suffix:semicolon
id|ULONG
id|SiS_GetReg3
c_func
(paren
id|USHORT
)paren
suffix:semicolon
id|USHORT
id|SiS_GetReg4
c_func
(paren
id|USHORT
)paren
suffix:semicolon
r_void
id|SiS_ClearDAC
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|ULONG
)paren
suffix:semicolon
r_void
id|SiS_SetMemoryClock
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|UCHAR
op_star
id|ROMAddr
comma
id|PSIS_HW_DEVICE_INFO
id|HwDeviceExtension
)paren
suffix:semicolon
r_void
id|SiS_SetDRAMModeRegister
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|UCHAR
op_star
id|ROMAddr
comma
id|PSIS_HW_DEVICE_INFO
id|HwDeviceExtension
)paren
suffix:semicolon
id|BOOLEAN
id|SiS_SearchVBModeID
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|UCHAR
op_star
id|ROMAddr
comma
id|USHORT
op_star
id|ModeNo
)paren
suffix:semicolon
r_void
id|SiS_IsLowResolution
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|UCHAR
op_star
id|ROMAddr
comma
id|USHORT
id|ModeNo
comma
id|USHORT
id|ModeIdIndex
)paren
suffix:semicolon
macro_line|#ifdef SIS300
r_void
id|SiS_SetDRAMSize_300
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|PSIS_HW_DEVICE_INFO
id|HwDeviceExtension
)paren
suffix:semicolon
id|USHORT
id|SiS_ChkBUSWidth_300
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|ULONG
id|FBAddress
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef SIS315H
id|UCHAR
id|SiS_Get310DRAMType
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|UCHAR
op_star
id|ROMAddr
comma
id|PSIS_HW_DEVICE_INFO
id|HwDeviceExtension
)paren
suffix:semicolon
r_void
id|SiS_DDR_MRS
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
)paren
suffix:semicolon
r_void
id|SiS_SDR_MRS
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
)paren
suffix:semicolon
r_void
id|SiS_DisableRefresh
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
)paren
suffix:semicolon
r_void
id|SiS_EnableRefresh
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|UCHAR
op_star
id|ROMAddr
)paren
suffix:semicolon
r_void
id|SiS_SetDRAMSize_310
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|PSIS_HW_DEVICE_INFO
)paren
suffix:semicolon
r_void
id|SiS_DisableChannelInterleaving
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
r_int
id|index
comma
id|USHORT
id|SiS_DDRDRAM_TYPE
(braket
)braket
(braket
l_int|5
)braket
)paren
suffix:semicolon
r_void
id|SiS_SetDRAMSizingType
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
r_int
id|index
comma
id|USHORT
id|DRAMTYPE_TABLE
(braket
)braket
(braket
l_int|5
)braket
)paren
suffix:semicolon
r_void
id|SiS_CheckBusWidth_310
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|UCHAR
op_star
id|ROMAddress
comma
id|ULONG
id|FBAddress
comma
id|PSIS_HW_DEVICE_INFO
id|HwDeviceExtension
)paren
suffix:semicolon
r_int
id|SiS_SetRank
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
r_int
id|index
comma
id|UCHAR
id|RankNo
comma
id|USHORT
id|DRAMTYPE_TABLE
(braket
)braket
(braket
l_int|5
)braket
)paren
suffix:semicolon
r_int
id|SiS_SetDDRChannel
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
r_int
id|index
comma
id|UCHAR
id|ChannelNo
comma
id|USHORT
id|DRAMTYPE_TABLE
(braket
)braket
(braket
l_int|5
)braket
)paren
suffix:semicolon
r_int
id|SiS_CheckColumn
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
r_int
id|index
comma
id|USHORT
id|DRAMTYPE_TABLE
(braket
)braket
(braket
l_int|5
)braket
comma
id|ULONG
id|FBAddress
)paren
suffix:semicolon
r_int
id|SiS_CheckBanks
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
r_int
id|index
comma
id|USHORT
id|DRAMTYPE_TABLE
(braket
)braket
(braket
l_int|5
)braket
comma
id|ULONG
id|FBAddress
)paren
suffix:semicolon
r_int
id|SiS_CheckRank
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
r_int
id|RankNo
comma
r_int
id|index
comma
id|USHORT
id|DRAMTYPE_TABLE
(braket
)braket
(braket
l_int|5
)braket
comma
id|ULONG
id|FBAddress
)paren
suffix:semicolon
r_int
id|SiS_CheckDDRRank
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
r_int
id|RankNo
comma
r_int
id|index
comma
id|USHORT
id|DRAMTYPE_TABLE
(braket
)braket
(braket
l_int|5
)braket
comma
id|ULONG
id|FBAddress
)paren
suffix:semicolon
r_int
id|SiS_CheckRanks
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
r_int
id|RankNo
comma
r_int
id|index
comma
id|USHORT
id|DRAMTYPE_TABLE
(braket
)braket
(braket
l_int|5
)braket
comma
id|ULONG
id|FBAddress
)paren
suffix:semicolon
r_int
id|SiS_CheckDDRRanks
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
r_int
id|RankNo
comma
r_int
id|index
comma
id|USHORT
id|DRAMTYPE_TABLE
(braket
)braket
(braket
l_int|5
)braket
comma
id|ULONG
id|FBAddress
)paren
suffix:semicolon
r_int
id|SiS_SDRSizing
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|ULONG
id|FBAddress
)paren
suffix:semicolon
r_int
id|SiS_DDRSizing
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|ULONG
id|FBAddress
)paren
suffix:semicolon
r_int
id|Is315E
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
)paren
suffix:semicolon
r_void
id|SiS_VerifyMclk
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|ULONG
id|FBAddr
)paren
suffix:semicolon
macro_line|#endif
r_void
id|SiS_HandleCRT1
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
)paren
suffix:semicolon
r_void
id|SiS_Handle301B_1400x1050
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|USHORT
id|ModeNo
)paren
suffix:semicolon
r_void
id|SiS_SetEnableDstn
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
)paren
suffix:semicolon
r_void
id|SiS_Delay15us
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
)paren
suffix:semicolon
id|BOOLEAN
id|SiS_SearchModeID
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|UCHAR
op_star
id|ROMAddr
comma
id|USHORT
op_star
id|ModeNo
comma
id|USHORT
op_star
id|ModeIdIndex
)paren
suffix:semicolon
id|BOOLEAN
id|SiS_CheckMemorySize
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|UCHAR
op_star
id|ROMAddr
comma
id|PSIS_HW_DEVICE_INFO
id|HwDeviceExtension
comma
id|USHORT
id|ModeNo
comma
id|USHORT
id|ModeIdIndex
)paren
suffix:semicolon
id|UCHAR
id|SiS_GetModePtr
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|UCHAR
op_star
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
id|SiS_SetSeqRegs
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|UCHAR
op_star
id|ROMAddr
comma
id|USHORT
id|StandTableIndex
)paren
suffix:semicolon
r_void
id|SiS_SetMiscRegs
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|UCHAR
op_star
id|ROMAddr
comma
id|USHORT
id|StandTableIndex
)paren
suffix:semicolon
r_void
id|SiS_SetCRTCRegs
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|UCHAR
op_star
id|ROMAddr
comma
id|PSIS_HW_DEVICE_INFO
id|HwDeviceExtension
comma
id|USHORT
id|StandTableIndex
)paren
suffix:semicolon
r_void
id|SiS_SetATTRegs
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|UCHAR
op_star
id|ROMAddr
comma
id|USHORT
id|StandTableIndex
comma
id|PSIS_HW_DEVICE_INFO
id|HwDeviceExtension
)paren
suffix:semicolon
r_void
id|SiS_SetGRCRegs
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|UCHAR
op_star
id|ROMAddr
comma
id|USHORT
id|StandTableIndex
)paren
suffix:semicolon
r_void
id|SiS_ClearExt1Regs
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|PSIS_HW_DEVICE_INFO
id|HwDeviceExtension
)paren
suffix:semicolon
r_void
id|SiS_SetSync
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|UCHAR
op_star
id|ROMAddr
comma
id|USHORT
id|RefreshRateTableIndex
)paren
suffix:semicolon
r_void
id|SiS_SetCRT1CRTC
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|UCHAR
op_star
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
id|BOOLEAN
id|SiS_GetLCDACRT1Ptr
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|UCHAR
op_star
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
id|SiS_ResetCRT1VCLK
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|UCHAR
op_star
id|ROMAddr
comma
id|PSIS_HW_DEVICE_INFO
id|HwDeviceExtension
)paren
suffix:semicolon
r_void
id|SiS_SetCRT1VCLK
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|UCHAR
op_star
id|ROMAddr
comma
id|USHORT
id|ModeNo
comma
id|USHORT
id|ModeIdIndex
comma
id|PSIS_HW_DEVICE_INFO
comma
id|USHORT
id|RefreshRateTableIndex
)paren
suffix:semicolon
r_void
id|SiS_SetVCLKState
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|UCHAR
op_star
id|ROMAddr
comma
id|PSIS_HW_DEVICE_INFO
comma
id|USHORT
id|ModeNo
comma
id|USHORT
id|RefreshRateTableIndex
comma
id|USHORT
id|ModeIdIndex
)paren
suffix:semicolon
r_void
id|SiS_LoadDAC
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|PSIS_HW_DEVICE_INFO
comma
id|UCHAR
op_star
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
id|SiS_WriteDAC
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|USHORT
comma
id|USHORT
comma
id|USHORT
comma
id|USHORT
comma
id|USHORT
comma
id|USHORT
)paren
suffix:semicolon
r_void
id|SiS_DisplayOn
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
)paren
suffix:semicolon
r_void
id|SiS_DisplayOff
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
)paren
suffix:semicolon
r_void
id|SiS_SetCRT1ModeRegs
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|UCHAR
op_star
id|ROMAddr
comma
id|PSIS_HW_DEVICE_INFO
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
id|SiS_GetVBType
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|USHORT
id|BaseAddr
comma
id|PSIS_HW_DEVICE_INFO
)paren
suffix:semicolon
id|USHORT
id|SiS_ChkBUSWidth
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|UCHAR
op_star
id|ROMAddr
)paren
suffix:semicolon
id|USHORT
id|SiS_GetModeIDLength
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|UCHAR
op_star
id|ROMAddr
comma
id|USHORT
)paren
suffix:semicolon
id|USHORT
id|SiS_GetRefindexLength
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|UCHAR
op_star
id|ROMAddr
comma
id|USHORT
)paren
suffix:semicolon
r_void
id|SiS_SetInterlace
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|UCHAR
op_star
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
id|SiS_Set_LVDS_TRUMPION
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|PSIS_HW_DEVICE_INFO
id|HwDeviceExtension
)paren
suffix:semicolon
r_void
id|SiS_SetCRT1Offset
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|UCHAR
op_star
id|ROMAddr
comma
id|USHORT
comma
id|USHORT
comma
id|USHORT
comma
id|PSIS_HW_DEVICE_INFO
)paren
suffix:semicolon
macro_line|#ifdef SIS315H
r_void
id|SiS_SetCRT1FIFO_310
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|UCHAR
op_star
id|ROMAddr
comma
id|USHORT
comma
id|USHORT
comma
id|PSIS_HW_DEVICE_INFO
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef SIS300
r_void
id|SiS_SetCRT1FIFO_300
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|UCHAR
op_star
id|ROMAddr
comma
id|USHORT
id|ModeNo
comma
id|PSIS_HW_DEVICE_INFO
comma
id|USHORT
id|RefreshRateTableIndex
)paren
suffix:semicolon
r_void
id|SiS_SetCRT1FIFO_630
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|UCHAR
op_star
id|ROMAddr
comma
id|USHORT
id|ModeNo
comma
id|PSIS_HW_DEVICE_INFO
comma
id|USHORT
id|RefreshRateTableIndex
)paren
suffix:semicolon
id|USHORT
id|SiS_CalcDelay
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|UCHAR
op_star
id|ROMAddr
comma
id|USHORT
id|VCLK
comma
id|USHORT
id|colordepth
comma
id|USHORT
id|MCLK
)paren
suffix:semicolon
id|USHORT
id|SiS_DoCalcDelay
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|USHORT
id|MCLK
comma
id|USHORT
id|VCLK
comma
id|USHORT
id|colordepth
comma
id|USHORT
id|key
)paren
suffix:semicolon
id|USHORT
id|SiS_CalcDelay2
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|UCHAR
op_star
id|ROMAddr
comma
id|UCHAR
comma
id|PSIS_HW_DEVICE_INFO
id|HwDeviceExtension
)paren
suffix:semicolon
macro_line|#endif
r_void
id|SiS_ClearBuffer
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|PSIS_HW_DEVICE_INFO
comma
id|USHORT
id|ModeNo
)paren
suffix:semicolon
r_void
id|SiS_SetCRT1Group
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|UCHAR
op_star
id|ROMAddr
comma
id|PSIS_HW_DEVICE_INFO
id|HwDeviceExtension
comma
id|USHORT
id|ModeNo
comma
id|USHORT
id|ModeIdIndex
comma
id|USHORT
id|BaseAddr
)paren
suffix:semicolon
r_void
id|SiS_DetectMonitor
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|PSIS_HW_DEVICE_INFO
id|HwDeviceExtension
comma
id|USHORT
id|BaseAddr
)paren
suffix:semicolon
r_void
id|SiS_GetSenseStatus
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|PSIS_HW_DEVICE_INFO
id|HwDeviceExtension
comma
id|UCHAR
op_star
id|ROMAddr
)paren
suffix:semicolon
id|USHORT
id|SiS_TestMonitorType
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|UCHAR
id|R_DAC
comma
id|UCHAR
id|G_DAC
comma
id|UCHAR
id|B_DAC
)paren
suffix:semicolon
id|USHORT
id|SiS_SenseCHTV
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
)paren
suffix:semicolon
id|BOOLEAN
id|SiS_Sense
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|USHORT
id|tempbx
comma
id|USHORT
id|tempcx
)paren
suffix:semicolon
id|BOOLEAN
id|SiS_GetPanelID
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|PSIS_HW_DEVICE_INFO
)paren
suffix:semicolon
id|BOOLEAN
id|SiS_GetLCDDDCInfo
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|PSIS_HW_DEVICE_INFO
)paren
suffix:semicolon
id|USHORT
id|SiS_SenseLCD
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|PSIS_HW_DEVICE_INFO
)paren
suffix:semicolon
r_void
id|SiSRegInit
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|USHORT
id|BaseAddr
)paren
suffix:semicolon
r_void
id|SiSInitPtr
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|PSIS_HW_DEVICE_INFO
id|HwDeviceExtension
)paren
suffix:semicolon
r_void
id|SiSSetLVDSetc
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|PSIS_HW_DEVICE_INFO
id|HwDeviceExtension
comma
id|USHORT
id|ModeNo
)paren
suffix:semicolon
r_void
id|SiSInitPCIetc
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|PSIS_HW_DEVICE_INFO
id|HwDeviceExtension
)paren
suffix:semicolon
r_void
id|SiSDetermineROMUsage
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|PSIS_HW_DEVICE_INFO
id|HwDeviceExtension
comma
id|UCHAR
op_star
id|ROMAddr
)paren
suffix:semicolon
macro_line|#ifdef LINUX_XF86
id|USHORT
id|SiS_CalcModeIndex
c_func
(paren
id|ScrnInfoPtr
id|pScrn
comma
id|DisplayModePtr
id|mode
)paren
suffix:semicolon
id|USHORT
id|SiS_CheckCalcModeIndex
c_func
(paren
id|ScrnInfoPtr
id|pScrn
comma
id|DisplayModePtr
id|mode
comma
r_int
id|VBFlags
)paren
suffix:semicolon
id|USHORT
id|SiS_CheckBuildCustomMode
c_func
(paren
id|ScrnInfoPtr
id|pScrn
comma
id|DisplayModePtr
id|mode
comma
r_int
id|VBFlags
)paren
suffix:semicolon
r_void
id|SiS_SetPitch
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|ScrnInfoPtr
id|pScrn
comma
id|UShort
id|BaseAddr
)paren
suffix:semicolon
r_void
id|SiS_SetPitchCRT1
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|ScrnInfoPtr
id|pScrn
comma
id|UShort
id|BaseAddr
)paren
suffix:semicolon
r_void
id|SiS_SetPitchCRT2
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|ScrnInfoPtr
id|pScrn
comma
id|UShort
id|BaseAddr
)paren
suffix:semicolon
r_int
r_char
id|SiS_GetSetModeID
c_func
(paren
id|ScrnInfoPtr
id|pScrn
comma
r_int
r_char
id|id
)paren
suffix:semicolon
r_int
r_char
id|SiS_GetSetBIOSScratch
c_func
(paren
id|ScrnInfoPtr
id|pScrn
comma
id|USHORT
id|offset
comma
r_int
r_char
id|value
)paren
suffix:semicolon
r_extern
r_int
id|SiS_compute_vclk
c_func
(paren
r_int
id|Clock
comma
r_int
op_star
id|out_n
comma
r_int
op_star
id|out_dn
comma
r_int
op_star
id|out_div
comma
r_int
op_star
id|out_sbit
comma
r_int
op_star
id|out_scale
)paren
suffix:semicolon
macro_line|#endif
r_extern
id|USHORT
id|SiS_GetOffset
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|UCHAR
op_star
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
r_extern
id|USHORT
id|SiS_GetColorDepth
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|UCHAR
op_star
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
r_void
id|SiS_DisableBridge
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|PSIS_HW_DEVICE_INFO
id|HwDeviceExtension
comma
id|USHORT
id|BaseAddr
)paren
suffix:semicolon
r_extern
id|BOOLEAN
id|SiS_SetCRT2Group301
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|USHORT
id|BaseAddr
comma
id|UCHAR
op_star
id|ROMAddr
comma
id|USHORT
id|ModeNo
comma
id|PSIS_HW_DEVICE_INFO
id|HwDeviceExtension
)paren
suffix:semicolon
r_extern
r_void
id|SiS_PresetScratchregister
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|USHORT
id|SiS_P3d4
comma
id|PSIS_HW_DEVICE_INFO
id|HwDeviceExtension
)paren
suffix:semicolon
r_extern
r_void
id|SiS_UnLockCRT2
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|PSIS_HW_DEVICE_INFO
id|HwDeviceExtension
comma
id|USHORT
id|BaseAddr
)paren
suffix:semicolon
r_extern
r_void
id|SiS_LockCRT2
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|PSIS_HW_DEVICE_INFO
id|HwDeviceExtension
comma
id|USHORT
id|BaseAddr
)paren
suffix:semicolon
r_extern
id|BOOLEAN
id|SiS_BridgeIsOn
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|USHORT
id|BaseAddr
)paren
suffix:semicolon
r_extern
id|BOOLEAN
id|SiS_BridgeIsEnable
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|USHORT
id|BaseAddr
comma
id|PSIS_HW_DEVICE_INFO
)paren
suffix:semicolon
r_extern
r_void
id|SiS_GetVBInfo
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|USHORT
id|BaseAddr
comma
id|UCHAR
op_star
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
r_int
id|chkcrt2mode
)paren
suffix:semicolon
r_extern
id|BOOLEAN
id|SiS_GetLCDResInfo
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|UCHAR
op_star
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
r_extern
r_void
id|SiS_SetHiVision
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|USHORT
id|BaseAddr
comma
id|PSIS_HW_DEVICE_INFO
id|HwDeviceExtension
)paren
suffix:semicolon
r_extern
id|USHORT
id|SiS_GetRatePtrCRT2
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|UCHAR
op_star
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
r_extern
r_void
id|SiS_WhatIsThis
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|USHORT
id|myvbinfo
)paren
suffix:semicolon
r_extern
r_void
id|SiS_LongWait
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
)paren
suffix:semicolon
r_extern
r_void
id|SiS_SetRegOR
c_func
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
r_extern
r_void
id|SiS_SetRegAND
c_func
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
r_extern
r_void
id|SiS_SetRegANDOR
c_func
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
r_extern
id|USHORT
id|SiS_GetResInfo
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|UCHAR
op_star
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
r_void
id|SiS_SetCH700x
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|USHORT
id|tempax
)paren
suffix:semicolon
r_extern
id|USHORT
id|SiS_GetCH700x
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|USHORT
id|tempax
)paren
suffix:semicolon
r_extern
r_void
id|SiS_SetCH701x
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|USHORT
id|tempax
)paren
suffix:semicolon
r_extern
id|USHORT
id|SiS_GetCH701x
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|USHORT
id|tempax
)paren
suffix:semicolon
r_extern
r_void
id|SiS_SetCH70xx
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|USHORT
id|tempax
)paren
suffix:semicolon
r_extern
id|USHORT
id|SiS_GetCH70xx
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|USHORT
id|tempax
)paren
suffix:semicolon
r_extern
id|BOOLEAN
id|SiS_GetLVDSCRT1Ptr
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|UCHAR
op_star
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
r_extern
id|USHORT
id|SiS_GetVCLK2Ptr
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|UCHAR
op_star
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
r_extern
id|BOOLEAN
id|SiS_Is301B
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|USHORT
id|BaseAddr
)paren
suffix:semicolon
r_extern
id|BOOLEAN
id|SiS_IsM650
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|PSIS_HW_DEVICE_INFO
id|HwDeviceExtension
comma
id|USHORT
id|BaseAddr
)paren
suffix:semicolon
r_extern
id|BOOLEAN
id|SiS_LowModeStuff
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|USHORT
id|ModeNo
comma
id|PSIS_HW_DEVICE_INFO
id|HwDeviceExtension
)paren
suffix:semicolon
r_extern
id|BOOLEAN
id|SiS_IsVAMode
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|PSIS_HW_DEVICE_INFO
id|HwDeviceExtension
comma
id|USHORT
id|BaseAddr
)paren
suffix:semicolon
r_extern
id|BOOLEAN
id|SiS_IsDualEdge
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|PSIS_HW_DEVICE_INFO
id|HwDeviceExtension
comma
id|USHORT
id|BaseAddr
)paren
suffix:semicolon
r_extern
id|USHORT
id|SiS_GetMCLK
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|UCHAR
op_star
id|ROMAddr
comma
id|PSIS_HW_DEVICE_INFO
id|HwDeviceExtension
)paren
suffix:semicolon
macro_line|#ifdef LINUX_KERNEL
r_int
id|sisfb_mode_rate_to_dclock
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|PSIS_HW_DEVICE_INFO
id|HwDeviceExtension
comma
r_int
r_char
id|modeno
comma
r_int
r_char
id|rateindex
)paren
suffix:semicolon
r_int
id|sisfb_mode_rate_to_ddata
c_func
(paren
id|SiS_Private
op_star
id|SiS_Pr
comma
id|PSIS_HW_DEVICE_INFO
id|HwDeviceExtension
comma
r_int
r_char
id|modeno
comma
r_int
r_char
id|rateindex
comma
id|ULONG
op_star
id|left_margin
comma
id|ULONG
op_star
id|right_margin
comma
id|ULONG
op_star
id|upper_margin
comma
id|ULONG
op_star
id|lower_margin
comma
id|ULONG
op_star
id|hsync_len
comma
id|ULONG
op_star
id|vsync_len
comma
id|ULONG
op_star
id|sync
comma
id|ULONG
op_star
id|vmode
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
