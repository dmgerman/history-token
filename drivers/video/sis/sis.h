multiline_comment|/*&n; * SiS 300/630/730/540/315/550/[M]650/651/[M]661[FM]X/740/[M]741[GX]/330/[M]760[GX]&n; * frame buffer driver for Linux kernels &gt;=2.4.14 and &gt;=2.6.3&n; *&n; * Copyright (C) 2001-2004 Thomas Winischhofer, Vienna, Austria.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the named License,&n; * or any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA&n; */
macro_line|#ifndef _SIS_H
DECL|macro|_SIS_H
mdefine_line|#define _SIS_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &quot;osdef.h&quot;
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,5,0)
macro_line|#include &lt;video/sisfb.h&gt;
macro_line|#else
macro_line|#include &lt;linux/sisfb.h&gt;
macro_line|#endif
macro_line|#include &quot;vgatypes.h&quot;
macro_line|#include &quot;vstruct.h&quot;
DECL|macro|VER_MAJOR
mdefine_line|#define VER_MAJOR                 1
DECL|macro|VER_MINOR
mdefine_line|#define VER_MINOR                 7
DECL|macro|VER_LEVEL
mdefine_line|#define VER_LEVEL                 17
DECL|macro|SIS_CONFIG_COMPAT
macro_line|#undef SIS_CONFIG_COMPAT
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,5,0)
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#ifdef CONFIG_COMPAT
macro_line|#include &lt;linux/ioctl32.h&gt;
DECL|macro|SIS_CONFIG_COMPAT
mdefine_line|#define SIS_CONFIG_COMPAT
macro_line|#endif
macro_line|#elif LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,4,19)
macro_line|#ifdef __x86_64__
multiline_comment|/* Shouldn&squot;t we check for CONFIG_IA32_EMULATION here? */
macro_line|#include &lt;asm/ioctl32.h&gt;
DECL|macro|SIS_CONFIG_COMPAT
mdefine_line|#define SIS_CONFIG_COMPAT
macro_line|#endif
macro_line|#endif
macro_line|#if LINUX_VERSION_CODE &gt; KERNEL_VERSION(2,6,8)
DECL|macro|SIS_IOTYPE1
mdefine_line|#define SIS_IOTYPE1 void __iomem
DECL|macro|SIS_IOTYPE2
mdefine_line|#define SIS_IOTYPE2 __iomem
DECL|macro|SISINITSTATIC
mdefine_line|#define SISINITSTATIC static
macro_line|#else
DECL|macro|SIS_IOTYPE1
mdefine_line|#define SIS_IOTYPE1 unsigned char
DECL|macro|SIS_IOTYPE2
mdefine_line|#define SIS_IOTYPE2
DECL|macro|SISINITSTATIC
mdefine_line|#define SISINITSTATIC
macro_line|#endif
DECL|macro|SISFBDEBUG
macro_line|#undef SISFBDEBUG
macro_line|#ifdef SISFBDEBUG
DECL|macro|DPRINTK
mdefine_line|#define DPRINTK(fmt, args...) printk(KERN_DEBUG &quot;%s: &quot; fmt, __FUNCTION__ , ## args)
DECL|macro|TWDEBUG
mdefine_line|#define TWDEBUG(x) printk(KERN_INFO x &quot;&bslash;n&quot;);
macro_line|#else
DECL|macro|DPRINTK
mdefine_line|#define DPRINTK(fmt, args...)
DECL|macro|TWDEBUG
mdefine_line|#define TWDEBUG(x)
macro_line|#endif
DECL|macro|SISFAIL
mdefine_line|#define SISFAIL(x) do { printk(x &quot;&bslash;n&quot;); return -EINVAL; } while(0)
multiline_comment|/* To be included in pci_ids.h */
macro_line|#ifndef PCI_DEVICE_ID_SI_650_VGA
DECL|macro|PCI_DEVICE_ID_SI_650_VGA
mdefine_line|#define PCI_DEVICE_ID_SI_650_VGA  0x6325
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_SI_650
DECL|macro|PCI_DEVICE_ID_SI_650
mdefine_line|#define PCI_DEVICE_ID_SI_650      0x0650
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_SI_651
DECL|macro|PCI_DEVICE_ID_SI_651
mdefine_line|#define PCI_DEVICE_ID_SI_651      0x0651
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_SI_740
DECL|macro|PCI_DEVICE_ID_SI_740
mdefine_line|#define PCI_DEVICE_ID_SI_740      0x0740
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_SI_330
DECL|macro|PCI_DEVICE_ID_SI_330
mdefine_line|#define PCI_DEVICE_ID_SI_330      0x0330
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_SI_660_VGA
DECL|macro|PCI_DEVICE_ID_SI_660_VGA
mdefine_line|#define PCI_DEVICE_ID_SI_660_VGA  0x6330
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_SI_661
DECL|macro|PCI_DEVICE_ID_SI_661
mdefine_line|#define PCI_DEVICE_ID_SI_661      0x0661
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_SI_741
DECL|macro|PCI_DEVICE_ID_SI_741
mdefine_line|#define PCI_DEVICE_ID_SI_741      0x0741
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_SI_660
DECL|macro|PCI_DEVICE_ID_SI_660
mdefine_line|#define PCI_DEVICE_ID_SI_660      0x0660
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_SI_760
DECL|macro|PCI_DEVICE_ID_SI_760
mdefine_line|#define PCI_DEVICE_ID_SI_760      0x0760
macro_line|#endif
multiline_comment|/* To be included in fb.h */
macro_line|#ifndef FB_ACCEL_SIS_GLAMOUR_2
DECL|macro|FB_ACCEL_SIS_GLAMOUR_2
mdefine_line|#define FB_ACCEL_SIS_GLAMOUR_2&t;  40&t;/* SiS 315, 65x, 740, 661, 741  */
macro_line|#endif
macro_line|#ifndef FB_ACCEL_SIS_XABRE
DECL|macro|FB_ACCEL_SIS_XABRE
mdefine_line|#define FB_ACCEL_SIS_XABRE        41&t;/* SiS 330 (&quot;Xabre&quot;), 760 &t;*/
macro_line|#endif
DECL|macro|MAX_ROM_SCAN
mdefine_line|#define MAX_ROM_SCAN              0x10000
multiline_comment|/* ivideo-&gt;caps */
DECL|macro|HW_CURSOR_CAP
mdefine_line|#define HW_CURSOR_CAP             0x80
DECL|macro|TURBO_QUEUE_CAP
mdefine_line|#define TURBO_QUEUE_CAP           0x40
DECL|macro|AGP_CMD_QUEUE_CAP
mdefine_line|#define AGP_CMD_QUEUE_CAP         0x20
DECL|macro|VM_CMD_QUEUE_CAP
mdefine_line|#define VM_CMD_QUEUE_CAP          0x10
DECL|macro|MMIO_CMD_QUEUE_CAP
mdefine_line|#define MMIO_CMD_QUEUE_CAP        0x08
multiline_comment|/* For 300 series */
DECL|macro|TURBO_QUEUE_AREA_SIZE
mdefine_line|#define TURBO_QUEUE_AREA_SIZE     0x80000 /* 512K */
DECL|macro|HW_CURSOR_AREA_SIZE_300
mdefine_line|#define HW_CURSOR_AREA_SIZE_300   0x1000  /* 4K */
multiline_comment|/* For 315/Xabre series */
DECL|macro|COMMAND_QUEUE_AREA_SIZE
mdefine_line|#define COMMAND_QUEUE_AREA_SIZE   0x80000 /* 512K */
DECL|macro|COMMAND_QUEUE_THRESHOLD
mdefine_line|#define COMMAND_QUEUE_THRESHOLD   0x1F
DECL|macro|HW_CURSOR_AREA_SIZE_315
mdefine_line|#define HW_CURSOR_AREA_SIZE_315   0x4000  /* 16K */
DECL|macro|SIS_OH_ALLOC_SIZE
mdefine_line|#define SIS_OH_ALLOC_SIZE         4000
DECL|macro|SENTINEL
mdefine_line|#define SENTINEL                  0x7fffffff
DECL|macro|SEQ_ADR
mdefine_line|#define SEQ_ADR                   0x14
DECL|macro|SEQ_DATA
mdefine_line|#define SEQ_DATA                  0x15
DECL|macro|DAC_ADR
mdefine_line|#define DAC_ADR                   0x18
DECL|macro|DAC_DATA
mdefine_line|#define DAC_DATA                  0x19
DECL|macro|CRTC_ADR
mdefine_line|#define CRTC_ADR                  0x24
DECL|macro|CRTC_DATA
mdefine_line|#define CRTC_DATA                 0x25
DECL|macro|DAC2_ADR
mdefine_line|#define DAC2_ADR                  (0x16-0x30)
DECL|macro|DAC2_DATA
mdefine_line|#define DAC2_DATA                 (0x17-0x30)
DECL|macro|VB_PART1_ADR
mdefine_line|#define VB_PART1_ADR              (0x04-0x30)
DECL|macro|VB_PART1_DATA
mdefine_line|#define VB_PART1_DATA             (0x05-0x30)
DECL|macro|VB_PART2_ADR
mdefine_line|#define VB_PART2_ADR              (0x10-0x30)
DECL|macro|VB_PART2_DATA
mdefine_line|#define VB_PART2_DATA             (0x11-0x30)
DECL|macro|VB_PART3_ADR
mdefine_line|#define VB_PART3_ADR              (0x12-0x30)
DECL|macro|VB_PART3_DATA
mdefine_line|#define VB_PART3_DATA             (0x13-0x30)
DECL|macro|VB_PART4_ADR
mdefine_line|#define VB_PART4_ADR              (0x14-0x30)
DECL|macro|VB_PART4_DATA
mdefine_line|#define VB_PART4_DATA             (0x15-0x30)
DECL|macro|SISSR
mdefine_line|#define SISSR&t;&t;&t;  ivideo-&gt;SiS_Pr.SiS_P3c4
DECL|macro|SISCR
mdefine_line|#define SISCR                     ivideo-&gt;SiS_Pr.SiS_P3d4
DECL|macro|SISDACA
mdefine_line|#define SISDACA                   ivideo-&gt;SiS_Pr.SiS_P3c8
DECL|macro|SISDACD
mdefine_line|#define SISDACD                   ivideo-&gt;SiS_Pr.SiS_P3c9
DECL|macro|SISPART1
mdefine_line|#define SISPART1                  ivideo-&gt;SiS_Pr.SiS_Part1Port
DECL|macro|SISPART2
mdefine_line|#define SISPART2                  ivideo-&gt;SiS_Pr.SiS_Part2Port
DECL|macro|SISPART3
mdefine_line|#define SISPART3                  ivideo-&gt;SiS_Pr.SiS_Part3Port
DECL|macro|SISPART4
mdefine_line|#define SISPART4                  ivideo-&gt;SiS_Pr.SiS_Part4Port
DECL|macro|SISPART5
mdefine_line|#define SISPART5                  ivideo-&gt;SiS_Pr.SiS_Part5Port
DECL|macro|SISDAC2A
mdefine_line|#define SISDAC2A                  SISPART5
DECL|macro|SISDAC2D
mdefine_line|#define SISDAC2D                  (SISPART5 + 1)
DECL|macro|SISMISCR
mdefine_line|#define SISMISCR                  (ivideo-&gt;SiS_Pr.RelIO + 0x1c)
DECL|macro|SISMISCW
mdefine_line|#define SISMISCW                  ivideo-&gt;SiS_Pr.SiS_P3c2
DECL|macro|SISINPSTAT
mdefine_line|#define SISINPSTAT&t;&t;  (ivideo-&gt;SiS_Pr.RelIO + 0x2a)
DECL|macro|SISPEL
mdefine_line|#define SISPEL&t;&t;&t;  ivideo-&gt;SiS_Pr.SiS_P3c6
DECL|macro|IND_SIS_PASSWORD
mdefine_line|#define IND_SIS_PASSWORD          0x05  /* SRs */
DECL|macro|IND_SIS_COLOR_MODE
mdefine_line|#define IND_SIS_COLOR_MODE        0x06
DECL|macro|IND_SIS_RAMDAC_CONTROL
mdefine_line|#define IND_SIS_RAMDAC_CONTROL    0x07
DECL|macro|IND_SIS_DRAM_SIZE
mdefine_line|#define IND_SIS_DRAM_SIZE         0x14
DECL|macro|IND_SIS_MODULE_ENABLE
mdefine_line|#define IND_SIS_MODULE_ENABLE     0x1E
DECL|macro|IND_SIS_PCI_ADDRESS_SET
mdefine_line|#define IND_SIS_PCI_ADDRESS_SET   0x20
DECL|macro|IND_SIS_TURBOQUEUE_ADR
mdefine_line|#define IND_SIS_TURBOQUEUE_ADR    0x26
DECL|macro|IND_SIS_TURBOQUEUE_SET
mdefine_line|#define IND_SIS_TURBOQUEUE_SET    0x27
DECL|macro|IND_SIS_POWER_ON_TRAP
mdefine_line|#define IND_SIS_POWER_ON_TRAP     0x38
DECL|macro|IND_SIS_POWER_ON_TRAP2
mdefine_line|#define IND_SIS_POWER_ON_TRAP2    0x39
DECL|macro|IND_SIS_CMDQUEUE_SET
mdefine_line|#define IND_SIS_CMDQUEUE_SET      0x26
DECL|macro|IND_SIS_CMDQUEUE_THRESHOLD
mdefine_line|#define IND_SIS_CMDQUEUE_THRESHOLD  0x27
DECL|macro|IND_SIS_AGP_IO_PAD
mdefine_line|#define IND_SIS_AGP_IO_PAD        0x48
DECL|macro|SIS_CRT2_WENABLE_300
mdefine_line|#define SIS_CRT2_WENABLE_300 &t;  0x24  /* Part1 */
DECL|macro|SIS_CRT2_WENABLE_315
mdefine_line|#define SIS_CRT2_WENABLE_315 &t;  0x2F
DECL|macro|SIS_PASSWORD
mdefine_line|#define SIS_PASSWORD              0x86  /* SR05 */
DECL|macro|SIS_INTERLACED_MODE
mdefine_line|#define SIS_INTERLACED_MODE       0x20  /* SR06 */
DECL|macro|SIS_8BPP_COLOR_MODE
mdefine_line|#define SIS_8BPP_COLOR_MODE       0x0
DECL|macro|SIS_15BPP_COLOR_MODE
mdefine_line|#define SIS_15BPP_COLOR_MODE      0x1
DECL|macro|SIS_16BPP_COLOR_MODE
mdefine_line|#define SIS_16BPP_COLOR_MODE      0x2
DECL|macro|SIS_32BPP_COLOR_MODE
mdefine_line|#define SIS_32BPP_COLOR_MODE      0x4
DECL|macro|SIS_ENABLE_2D
mdefine_line|#define SIS_ENABLE_2D             0x40  /* SR1E */
DECL|macro|SIS_MEM_MAP_IO_ENABLE
mdefine_line|#define SIS_MEM_MAP_IO_ENABLE     0x01  /* SR20 */
DECL|macro|SIS_PCI_ADDR_ENABLE
mdefine_line|#define SIS_PCI_ADDR_ENABLE       0x80
DECL|macro|SIS_AGP_CMDQUEUE_ENABLE
mdefine_line|#define SIS_AGP_CMDQUEUE_ENABLE   0x80  /* 315/330 series SR26 */
DECL|macro|SIS_VRAM_CMDQUEUE_ENABLE
mdefine_line|#define SIS_VRAM_CMDQUEUE_ENABLE  0x40
DECL|macro|SIS_MMIO_CMD_ENABLE
mdefine_line|#define SIS_MMIO_CMD_ENABLE       0x20
DECL|macro|SIS_CMD_QUEUE_SIZE_512k
mdefine_line|#define SIS_CMD_QUEUE_SIZE_512k   0x00
DECL|macro|SIS_CMD_QUEUE_SIZE_1M
mdefine_line|#define SIS_CMD_QUEUE_SIZE_1M     0x04
DECL|macro|SIS_CMD_QUEUE_SIZE_2M
mdefine_line|#define SIS_CMD_QUEUE_SIZE_2M     0x08
DECL|macro|SIS_CMD_QUEUE_SIZE_4M
mdefine_line|#define SIS_CMD_QUEUE_SIZE_4M     0x0C
DECL|macro|SIS_CMD_QUEUE_RESET
mdefine_line|#define SIS_CMD_QUEUE_RESET       0x01
DECL|macro|SIS_CMD_AUTO_CORR
mdefine_line|#define SIS_CMD_AUTO_CORR&t;  0x02
DECL|macro|SIS_SIMULTANEOUS_VIEW_ENABLE
mdefine_line|#define SIS_SIMULTANEOUS_VIEW_ENABLE  0x01  /* CR30 */
DECL|macro|SIS_MODE_SELECT_CRT2
mdefine_line|#define SIS_MODE_SELECT_CRT2      0x02
DECL|macro|SIS_VB_OUTPUT_COMPOSITE
mdefine_line|#define SIS_VB_OUTPUT_COMPOSITE   0x04
DECL|macro|SIS_VB_OUTPUT_SVIDEO
mdefine_line|#define SIS_VB_OUTPUT_SVIDEO      0x08
DECL|macro|SIS_VB_OUTPUT_SCART
mdefine_line|#define SIS_VB_OUTPUT_SCART       0x10
DECL|macro|SIS_VB_OUTPUT_LCD
mdefine_line|#define SIS_VB_OUTPUT_LCD         0x20
DECL|macro|SIS_VB_OUTPUT_CRT2
mdefine_line|#define SIS_VB_OUTPUT_CRT2        0x40
DECL|macro|SIS_VB_OUTPUT_HIVISION
mdefine_line|#define SIS_VB_OUTPUT_HIVISION    0x80
DECL|macro|SIS_VB_OUTPUT_DISABLE
mdefine_line|#define SIS_VB_OUTPUT_DISABLE     0x20  /* CR31 */
DECL|macro|SIS_DRIVER_MODE
mdefine_line|#define SIS_DRIVER_MODE           0x40
DECL|macro|SIS_VB_COMPOSITE
mdefine_line|#define SIS_VB_COMPOSITE          0x01  /* CR32 */
DECL|macro|SIS_VB_SVIDEO
mdefine_line|#define SIS_VB_SVIDEO             0x02
DECL|macro|SIS_VB_SCART
mdefine_line|#define SIS_VB_SCART              0x04
DECL|macro|SIS_VB_LCD
mdefine_line|#define SIS_VB_LCD                0x08
DECL|macro|SIS_VB_CRT2
mdefine_line|#define SIS_VB_CRT2               0x10
DECL|macro|SIS_CRT1
mdefine_line|#define SIS_CRT1                  0x20
DECL|macro|SIS_VB_HIVISION
mdefine_line|#define SIS_VB_HIVISION           0x40
DECL|macro|SIS_VB_YPBPR
mdefine_line|#define SIS_VB_YPBPR              0x80
DECL|macro|SIS_VB_TV
mdefine_line|#define SIS_VB_TV                 (SIS_VB_COMPOSITE | SIS_VB_SVIDEO | &bslash;&n;                                   SIS_VB_SCART | SIS_VB_HIVISION | SIS_VB_YPBPR)
DECL|macro|SIS_EXTERNAL_CHIP_MASK
mdefine_line|#define SIS_EXTERNAL_CHIP_MASK    &t;   0x0E  /* CR37 (&lt; SiS 660) */
DECL|macro|SIS_EXTERNAL_CHIP_SIS301
mdefine_line|#define SIS_EXTERNAL_CHIP_SIS301           0x01  /* in CR37 &lt;&lt; 1 ! */
DECL|macro|SIS_EXTERNAL_CHIP_LVDS
mdefine_line|#define SIS_EXTERNAL_CHIP_LVDS             0x02
DECL|macro|SIS_EXTERNAL_CHIP_TRUMPION
mdefine_line|#define SIS_EXTERNAL_CHIP_TRUMPION         0x03
DECL|macro|SIS_EXTERNAL_CHIP_LVDS_CHRONTEL
mdefine_line|#define SIS_EXTERNAL_CHIP_LVDS_CHRONTEL    0x04
DECL|macro|SIS_EXTERNAL_CHIP_CHRONTEL
mdefine_line|#define SIS_EXTERNAL_CHIP_CHRONTEL         0x05
DECL|macro|SIS310_EXTERNAL_CHIP_LVDS
mdefine_line|#define SIS310_EXTERNAL_CHIP_LVDS          0x02
DECL|macro|SIS310_EXTERNAL_CHIP_LVDS_CHRONTEL
mdefine_line|#define SIS310_EXTERNAL_CHIP_LVDS_CHRONTEL 0x03
DECL|macro|SIS_AGP_2X
mdefine_line|#define SIS_AGP_2X                0x20  /* CR48 */
DECL|macro|HW_DEVICE_EXTENSION
mdefine_line|#define HW_DEVICE_EXTENSION&t;  SIS_HW_INFO
DECL|macro|PHW_DEVICE_EXTENSION
mdefine_line|#define PHW_DEVICE_EXTENSION      PSIS_HW_INFO
multiline_comment|/* I/O port access macros */
DECL|macro|inSISREG
mdefine_line|#define inSISREG(base)          inb(base)
DECL|macro|outSISREG
mdefine_line|#define outSISREG(base,val)     outb(val,base)
DECL|macro|orSISREG
mdefine_line|#define orSISREG(base,val)      &t;&t;&t;&bslash;&n;&t;&t;    do { &t;&t;&t;&t;&bslash;&n;                      u8 __Temp = inSISREG(base); &t;&bslash;&n;                      outSISREG(base, __Temp | (val)); &t;&bslash;&n;                    } while (0)
DECL|macro|andSISREG
mdefine_line|#define andSISREG(base,val)     &t;&t;&t;&bslash;&n;&t;&t;    do { &t;&t;&t;&t;&bslash;&n;                      u8 __Temp = inSISREG(base); &t;&bslash;&n;                      outSISREG(base, __Temp &amp; (val)); &t;&bslash;&n;                    } while (0)
DECL|macro|inSISIDXREG
mdefine_line|#define inSISIDXREG(base,idx,var)   &t;&t;&bslash;&n;&t;&t;    do { &t;&t;&t;&bslash;&n;                      outSISREG(base, idx); &t;&bslash;&n;&t;&t;      var = inSISREG((base)+1);&t;&bslash;&n;                    } while (0)
DECL|macro|outSISIDXREG
mdefine_line|#define outSISIDXREG(base,idx,val)  &t;&t;&bslash;&n;&t;&t;    do { &t;&t;&t;&bslash;&n;                      outSISREG(base, idx); &t;&bslash;&n;&t;&t;      outSISREG((base)+1, val); &bslash;&n;                    } while (0)
DECL|macro|orSISIDXREG
mdefine_line|#define orSISIDXREG(base,idx,val)   &t;&t;&t;&t;&bslash;&n;&t;&t;    do { &t;&t;&t;&t;&t;&bslash;&n;                      u8 __Temp; &t;&t;&t;&t;&bslash;&n;                      outSISREG(base, idx);   &t;&t;&t;&bslash;&n;                      __Temp = inSISREG((base)+1) | (val); &t;&bslash;&n;&t;&t;      outSISREG((base)+1, __Temp);&t;&t;&bslash;&n;                    } while (0)
DECL|macro|andSISIDXREG
mdefine_line|#define andSISIDXREG(base,idx,and)  &t;&t;&t;&t;&bslash;&n;&t;&t;    do { &t;&t;&t;&t;&t;&bslash;&n;                      u8 __Temp; &t;&t;&t;&t;&bslash;&n;                      outSISREG(base, idx);   &t;&t;&t;&bslash;&n;                      __Temp = inSISREG((base)+1) &amp; (and); &t;&bslash;&n;&t;&t;      outSISREG((base)+1, __Temp);&t;&t;&bslash;&n;                    } while (0)
DECL|macro|setSISIDXREG
mdefine_line|#define setSISIDXREG(base,idx,and,or)   &t;&t;   &t;&t;&bslash;&n;&t;&t;    do { &t;&t;&t;&t;   &t;&t;&bslash;&n;                      u8 __Temp; &t;&t;   &t;&t;&t;&bslash;&n;                      outSISREG(base, idx);   &t;&t;   &t;&t;&bslash;&n;                      __Temp = (inSISREG((base)+1) &amp; (and)) | (or); &t;&bslash;&n;&t;&t;      outSISREG((base)+1, __Temp);&t;&t;&t;&bslash;&n;                    } while (0)
multiline_comment|/* MMIO access macros */
DECL|macro|MMIO_IN8
mdefine_line|#define MMIO_IN8(base, offset)  readb((base+offset))
DECL|macro|MMIO_IN16
mdefine_line|#define MMIO_IN16(base, offset) readw((base+offset))
DECL|macro|MMIO_IN32
mdefine_line|#define MMIO_IN32(base, offset) readl((base+offset))
DECL|macro|MMIO_OUT8
mdefine_line|#define MMIO_OUT8(base, offset, val)  writeb(((u8)(val)), (base+offset))
DECL|macro|MMIO_OUT16
mdefine_line|#define MMIO_OUT16(base, offset, val) writew(((u16)(val)), (base+offset))
DECL|macro|MMIO_OUT32
mdefine_line|#define MMIO_OUT32(base, offset, val) writel(((u32)(val)), (base+offset))
multiline_comment|/* Queue control MMIO registers */
DECL|macro|Q_BASE_ADDR
mdefine_line|#define Q_BASE_ADDR&t;&t;0x85C0  /* Base address of software queue */
DECL|macro|Q_WRITE_PTR
mdefine_line|#define Q_WRITE_PTR&t;&t;0x85C4  /* Current write pointer */
DECL|macro|Q_READ_PTR
mdefine_line|#define Q_READ_PTR&t;&t;0x85C8  /* Current read pointer */
DECL|macro|Q_STATUS
mdefine_line|#define Q_STATUS&t;&t;0x85CC  /* queue status */
DECL|macro|MMIO_QUEUE_PHYBASE
mdefine_line|#define MMIO_QUEUE_PHYBASE      Q_BASE_ADDR
DECL|macro|MMIO_QUEUE_WRITEPORT
mdefine_line|#define MMIO_QUEUE_WRITEPORT    Q_WRITE_PTR
DECL|macro|MMIO_QUEUE_READPORT
mdefine_line|#define MMIO_QUEUE_READPORT     Q_READ_PTR
macro_line|#ifndef FB_BLANK_UNBLANK
DECL|macro|FB_BLANK_UNBLANK
mdefine_line|#define FB_BLANK_UNBLANK &t;0
macro_line|#endif
macro_line|#ifndef FB_BLANK_NORMAL
DECL|macro|FB_BLANK_NORMAL
mdefine_line|#define FB_BLANK_NORMAL  &t;1
macro_line|#endif
macro_line|#ifndef FB_BLANK_VSYNC_SUSPEND
DECL|macro|FB_BLANK_VSYNC_SUSPEND
mdefine_line|#define FB_BLANK_VSYNC_SUSPEND &t;2
macro_line|#endif
macro_line|#ifndef FB_BLANK_HSYNC_SUSPEND
DECL|macro|FB_BLANK_HSYNC_SUSPEND
mdefine_line|#define FB_BLANK_HSYNC_SUSPEND &t;3
macro_line|#endif
macro_line|#ifndef FB_BLANK_POWERDOWN
DECL|macro|FB_BLANK_POWERDOWN
mdefine_line|#define FB_BLANK_POWERDOWN &t;4
macro_line|#endif
DECL|enum|_SIS_LCD_TYPE
r_enum
id|_SIS_LCD_TYPE
(brace
DECL|enumerator|LCD_INVALID
id|LCD_INVALID
op_assign
l_int|0
comma
DECL|enumerator|LCD_800x600
id|LCD_800x600
comma
DECL|enumerator|LCD_1024x768
id|LCD_1024x768
comma
DECL|enumerator|LCD_1280x1024
id|LCD_1280x1024
comma
DECL|enumerator|LCD_1280x960
id|LCD_1280x960
comma
DECL|enumerator|LCD_640x480
id|LCD_640x480
comma
DECL|enumerator|LCD_1600x1200
id|LCD_1600x1200
comma
DECL|enumerator|LCD_1920x1440
id|LCD_1920x1440
comma
DECL|enumerator|LCD_2048x1536
id|LCD_2048x1536
comma
DECL|enumerator|LCD_320x480
id|LCD_320x480
comma
multiline_comment|/* FSTN */
DECL|enumerator|LCD_1400x1050
id|LCD_1400x1050
comma
DECL|enumerator|LCD_1152x864
id|LCD_1152x864
comma
DECL|enumerator|LCD_1152x768
id|LCD_1152x768
comma
DECL|enumerator|LCD_1280x768
id|LCD_1280x768
comma
DECL|enumerator|LCD_1024x600
id|LCD_1024x600
comma
DECL|enumerator|LCD_640x480_2
id|LCD_640x480_2
comma
multiline_comment|/* DSTN */
DECL|enumerator|LCD_640x480_3
id|LCD_640x480_3
comma
multiline_comment|/* DSTN */
DECL|enumerator|LCD_848x480
id|LCD_848x480
comma
DECL|enumerator|LCD_1280x800
id|LCD_1280x800
comma
DECL|enumerator|LCD_1680x1050
id|LCD_1680x1050
comma
DECL|enumerator|LCD_1280x720
id|LCD_1280x720
comma
DECL|enumerator|LCD_CUSTOM
id|LCD_CUSTOM
comma
DECL|enumerator|LCD_UNKNOWN
id|LCD_UNKNOWN
)brace
suffix:semicolon
DECL|enum|_SIS_CMDTYPE
r_enum
id|_SIS_CMDTYPE
(brace
DECL|enumerator|MMIO_CMD
id|MMIO_CMD
op_assign
l_int|0
comma
DECL|enumerator|AGP_CMD_QUEUE
id|AGP_CMD_QUEUE
comma
DECL|enumerator|VM_CMD_QUEUE
id|VM_CMD_QUEUE
comma
)brace
suffix:semicolon
DECL|typedef|SIS_CMDTYPE
r_typedef
r_int
r_int
id|SIS_CMDTYPE
suffix:semicolon
multiline_comment|/* Our &quot;par&quot; */
DECL|struct|sis_video_info
r_struct
id|sis_video_info
(brace
DECL|member|cardnumber
r_int
id|cardnumber
suffix:semicolon
DECL|member|memyselfandi
r_struct
id|fb_info
op_star
id|memyselfandi
suffix:semicolon
DECL|member|sishw_ext
id|SIS_HW_INFO
id|sishw_ext
suffix:semicolon
DECL|member|SiS_Pr
id|SiS_Private
id|SiS_Pr
suffix:semicolon
DECL|member|sisfbinfo
id|sisfb_info
id|sisfbinfo
suffix:semicolon
multiline_comment|/* For ioctl SISFB_GET_INFO */
DECL|member|default_var
r_struct
id|fb_var_screeninfo
id|default_var
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,5,0)
DECL|member|sisfb_fix
r_struct
id|fb_fix_screeninfo
id|sisfb_fix
suffix:semicolon
DECL|member|pseudo_palette
id|u32
id|pseudo_palette
(braket
l_int|17
)braket
suffix:semicolon
macro_line|#endif
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,5,0)
DECL|member|sis_disp
r_struct
id|display
id|sis_disp
suffix:semicolon
DECL|member|sisfb_sw
r_struct
id|display_switch
id|sisfb_sw
suffix:semicolon
r_struct
(brace
DECL|member|red
DECL|member|green
DECL|member|blue
DECL|member|pad
id|u16
id|red
comma
id|green
comma
id|blue
comma
id|pad
suffix:semicolon
DECL|member|sis_palette
)brace
id|sis_palette
(braket
l_int|256
)braket
suffix:semicolon
r_union
(brace
macro_line|#ifdef FBCON_HAS_CFB16
DECL|member|cfb16
id|u16
id|cfb16
(braket
l_int|16
)braket
suffix:semicolon
macro_line|#endif
macro_line|#ifdef FBCON_HAS_CFB32
DECL|member|cfb32
id|u32
id|cfb32
(braket
l_int|16
)braket
suffix:semicolon
macro_line|#endif
DECL|member|sis_fbcon_cmap
)brace
id|sis_fbcon_cmap
suffix:semicolon
macro_line|#endif
DECL|struct|sisfb_monitor
r_struct
id|sisfb_monitor
(brace
DECL|member|hmin
id|u16
id|hmin
suffix:semicolon
DECL|member|hmax
id|u16
id|hmax
suffix:semicolon
DECL|member|vmin
id|u16
id|vmin
suffix:semicolon
DECL|member|vmax
id|u16
id|vmax
suffix:semicolon
DECL|member|dclockmax
id|u32
id|dclockmax
suffix:semicolon
DECL|member|feature
id|u8
id|feature
suffix:semicolon
DECL|member|datavalid
id|BOOLEAN
id|datavalid
suffix:semicolon
DECL|member|sisfb_thismonitor
)brace
id|sisfb_thismonitor
suffix:semicolon
DECL|member|chip_id
r_int
id|chip_id
suffix:semicolon
DECL|member|myid
r_char
id|myid
(braket
l_int|40
)braket
suffix:semicolon
DECL|member|nbridge
r_struct
id|pci_dev
op_star
id|nbridge
suffix:semicolon
DECL|member|mni
r_int
id|mni
suffix:semicolon
multiline_comment|/* Mode number index */
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,5,0)
DECL|member|currcon
r_int
id|currcon
suffix:semicolon
macro_line|#endif
DECL|member|video_size
r_int
r_int
id|video_size
suffix:semicolon
DECL|member|video_base
r_int
r_int
id|video_base
suffix:semicolon
DECL|member|mmio_size
r_int
r_int
id|mmio_size
suffix:semicolon
DECL|member|mmio_base
r_int
r_int
id|mmio_base
suffix:semicolon
DECL|member|vga_base
r_int
r_int
id|vga_base
suffix:semicolon
DECL|member|video_vbase
id|SIS_IOTYPE1
op_star
id|video_vbase
suffix:semicolon
DECL|member|mmio_vbase
id|SIS_IOTYPE1
op_star
id|mmio_vbase
suffix:semicolon
DECL|member|bios_abase
r_int
r_char
op_star
id|bios_abase
suffix:semicolon
DECL|member|mtrr
r_int
id|mtrr
suffix:semicolon
DECL|member|sisfb_mem
id|u32
id|sisfb_mem
suffix:semicolon
DECL|member|sisfb_parm_mem
id|u32
id|sisfb_parm_mem
suffix:semicolon
DECL|member|sisfb_accel
r_int
id|sisfb_accel
suffix:semicolon
DECL|member|sisfb_ypan
r_int
id|sisfb_ypan
suffix:semicolon
DECL|member|sisfb_max
r_int
id|sisfb_max
suffix:semicolon
DECL|member|sisfb_userom
r_int
id|sisfb_userom
suffix:semicolon
DECL|member|sisfb_useoem
r_int
id|sisfb_useoem
suffix:semicolon
DECL|member|sisfb_mode_idx
r_int
id|sisfb_mode_idx
suffix:semicolon
DECL|member|sisfb_parm_rate
r_int
id|sisfb_parm_rate
suffix:semicolon
DECL|member|sisfb_crt1off
r_int
id|sisfb_crt1off
suffix:semicolon
DECL|member|sisfb_forcecrt1
r_int
id|sisfb_forcecrt1
suffix:semicolon
DECL|member|sisfb_crt2type
r_int
id|sisfb_crt2type
suffix:semicolon
DECL|member|sisfb_crt2flags
r_int
id|sisfb_crt2flags
suffix:semicolon
DECL|member|sisfb_dstn
r_int
id|sisfb_dstn
suffix:semicolon
DECL|member|sisfb_fstn
r_int
id|sisfb_fstn
suffix:semicolon
DECL|member|sisfb_tvplug
r_int
id|sisfb_tvplug
suffix:semicolon
DECL|member|sisfb_tvstd
r_int
id|sisfb_tvstd
suffix:semicolon
DECL|member|sisfb_filter
r_int
id|sisfb_filter
suffix:semicolon
DECL|member|sisfb_nocrt2rate
r_int
id|sisfb_nocrt2rate
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,5,0)
DECL|member|sisfb_inverse
r_int
id|sisfb_inverse
suffix:semicolon
macro_line|#endif
DECL|member|heapstart
id|u32
id|heapstart
suffix:semicolon
multiline_comment|/* offset  */
DECL|member|sisfb_heap_start
id|SIS_IOTYPE1
op_star
id|sisfb_heap_start
suffix:semicolon
multiline_comment|/* address */
DECL|member|sisfb_heap_end
id|SIS_IOTYPE1
op_star
id|sisfb_heap_end
suffix:semicolon
multiline_comment|/* address */
DECL|member|sisfb_heap_size
id|u32
id|sisfb_heap_size
suffix:semicolon
DECL|member|havenoheap
r_int
id|havenoheap
suffix:semicolon
macro_line|#if 0
id|SIS_HEAP
id|sisfb_heap
suffix:semicolon
macro_line|#endif
DECL|member|video_bpp
r_int
id|video_bpp
suffix:semicolon
DECL|member|video_cmap_len
r_int
id|video_cmap_len
suffix:semicolon
DECL|member|video_width
r_int
id|video_width
suffix:semicolon
DECL|member|video_height
r_int
id|video_height
suffix:semicolon
DECL|member|refresh_rate
r_int
r_int
id|refresh_rate
suffix:semicolon
DECL|member|chip
r_int
r_int
id|chip
suffix:semicolon
DECL|member|revision_id
id|u8
id|revision_id
suffix:semicolon
DECL|member|video_linelength
r_int
id|video_linelength
suffix:semicolon
multiline_comment|/* real pitch */
DECL|member|scrnpitchCRT1
r_int
id|scrnpitchCRT1
suffix:semicolon
multiline_comment|/* pitch regarding interlace */
DECL|member|DstColor
id|u16
id|DstColor
suffix:semicolon
multiline_comment|/* For 2d acceleration */
DECL|member|SiS310_AccelDepth
id|u32
id|SiS310_AccelDepth
suffix:semicolon
DECL|member|CommandReg
id|u32
id|CommandReg
suffix:semicolon
DECL|member|cmdqueuelength
r_int
id|cmdqueuelength
suffix:semicolon
DECL|member|lockaccel
id|spinlock_t
id|lockaccel
suffix:semicolon
multiline_comment|/* Do not use outside of kernel! */
DECL|member|pcibus
r_int
r_int
id|pcibus
suffix:semicolon
DECL|member|pcislot
r_int
r_int
id|pcislot
suffix:semicolon
DECL|member|pcifunc
r_int
r_int
id|pcifunc
suffix:semicolon
DECL|member|accel
r_int
id|accel
suffix:semicolon
DECL|member|subsysvendor
id|u16
id|subsysvendor
suffix:semicolon
DECL|member|subsysdevice
id|u16
id|subsysdevice
suffix:semicolon
DECL|member|vbflags
id|u32
id|vbflags
suffix:semicolon
multiline_comment|/* Replacing deprecated stuff from above */
DECL|member|currentvbflags
id|u32
id|currentvbflags
suffix:semicolon
DECL|member|lcdxres
DECL|member|lcdyres
r_int
id|lcdxres
comma
id|lcdyres
suffix:semicolon
DECL|member|lcddefmodeidx
DECL|member|tvdefmodeidx
DECL|member|defmodeidx
r_int
id|lcddefmodeidx
comma
id|tvdefmodeidx
comma
id|defmodeidx
suffix:semicolon
DECL|member|CRT2LCDType
id|u32
id|CRT2LCDType
suffix:semicolon
multiline_comment|/* defined in &quot;SIS_LCD_TYPE&quot; */
DECL|member|current_bpp
r_int
id|current_bpp
suffix:semicolon
DECL|member|current_width
r_int
id|current_width
suffix:semicolon
DECL|member|current_height
r_int
id|current_height
suffix:semicolon
DECL|member|current_htotal
r_int
id|current_htotal
suffix:semicolon
DECL|member|current_vtotal
r_int
id|current_vtotal
suffix:semicolon
DECL|member|current_linelength
r_int
id|current_linelength
suffix:semicolon
DECL|member|current_pixclock
id|__u32
id|current_pixclock
suffix:semicolon
DECL|member|current_refresh_rate
r_int
id|current_refresh_rate
suffix:semicolon
DECL|member|mode_no
id|u8
id|mode_no
suffix:semicolon
DECL|member|rate_idx
id|u8
id|rate_idx
suffix:semicolon
DECL|member|modechanged
r_int
id|modechanged
suffix:semicolon
DECL|member|modeprechange
r_int
r_char
id|modeprechange
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,5,0)
DECL|member|sisfb_lastrates
id|u8
id|sisfb_lastrates
(braket
l_int|128
)braket
suffix:semicolon
macro_line|#endif
DECL|member|newrom
r_int
id|newrom
suffix:semicolon
DECL|member|registered
r_int
id|registered
suffix:semicolon
DECL|member|warncount
r_int
id|warncount
suffix:semicolon
macro_line|#ifdef SIS_CONFIG_COMPAT
DECL|member|ioctl32registered
r_int
id|ioctl32registered
suffix:semicolon
DECL|member|ioctl32vblankregistered
r_int
id|ioctl32vblankregistered
suffix:semicolon
macro_line|#endif
DECL|member|sisvga_engine
r_int
id|sisvga_engine
suffix:semicolon
DECL|member|hwcursor_size
r_int
id|hwcursor_size
suffix:semicolon
DECL|member|CRT2_write_enable
r_int
id|CRT2_write_enable
suffix:semicolon
DECL|member|caps
id|u8
id|caps
suffix:semicolon
DECL|member|detectedpdc
id|u8
id|detectedpdc
suffix:semicolon
DECL|member|detectedpdca
id|u8
id|detectedpdca
suffix:semicolon
DECL|member|detectedlcda
id|u8
id|detectedlcda
suffix:semicolon
DECL|member|hwcursor_vbase
id|SIS_IOTYPE1
op_star
id|hwcursor_vbase
suffix:semicolon
DECL|member|chronteltype
r_int
id|chronteltype
suffix:semicolon
DECL|member|tvxpos
DECL|member|tvypos
r_int
id|tvxpos
comma
id|tvypos
suffix:semicolon
DECL|member|p2_1f
DECL|member|p2_20
DECL|member|p2_2b
DECL|member|p2_42
DECL|member|p2_43
DECL|member|p2_01
DECL|member|p2_02
id|u8
id|p2_1f
comma
id|p2_20
comma
id|p2_2b
comma
id|p2_42
comma
id|p2_43
comma
id|p2_01
comma
id|p2_02
suffix:semicolon
DECL|member|tvx
DECL|member|tvy
r_int
id|tvx
comma
id|tvy
suffix:semicolon
DECL|member|sisfblocked
id|u8
id|sisfblocked
suffix:semicolon
DECL|member|next
r_struct
id|sis_video_info
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|_SIS_OH
r_typedef
r_struct
id|_SIS_OH
(brace
DECL|member|poh_next
r_struct
id|_SIS_OH
op_star
id|poh_next
suffix:semicolon
DECL|member|poh_prev
r_struct
id|_SIS_OH
op_star
id|poh_prev
suffix:semicolon
DECL|member|offset
id|u32
id|offset
suffix:semicolon
DECL|member|size
id|u32
id|size
suffix:semicolon
DECL|typedef|SIS_OH
)brace
id|SIS_OH
suffix:semicolon
DECL|struct|_SIS_OHALLOC
r_typedef
r_struct
id|_SIS_OHALLOC
(brace
DECL|member|poha_next
r_struct
id|_SIS_OHALLOC
op_star
id|poha_next
suffix:semicolon
DECL|member|aoh
id|SIS_OH
id|aoh
(braket
l_int|1
)braket
suffix:semicolon
DECL|typedef|SIS_OHALLOC
)brace
id|SIS_OHALLOC
suffix:semicolon
DECL|struct|_SIS_HEAP
r_typedef
r_struct
id|_SIS_HEAP
(brace
DECL|member|oh_free
id|SIS_OH
id|oh_free
suffix:semicolon
DECL|member|oh_used
id|SIS_OH
id|oh_used
suffix:semicolon
DECL|member|poh_freelist
id|SIS_OH
op_star
id|poh_freelist
suffix:semicolon
DECL|member|poha_chain
id|SIS_OHALLOC
op_star
id|poha_chain
suffix:semicolon
DECL|member|max_freesize
id|u32
id|max_freesize
suffix:semicolon
DECL|member|vinfo
r_struct
id|sis_video_info
op_star
id|vinfo
suffix:semicolon
DECL|typedef|SIS_HEAP
)brace
id|SIS_HEAP
suffix:semicolon
macro_line|#endif
eof
