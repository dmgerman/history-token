multiline_comment|/*-*- linux-c -*-&n; *  linux/drivers/video/i810.h -- Intel 810 General Definitions/Declarations&n; *&n; *      Copyright (C) 2001 Antonino Daplas&lt;adaplas@pol.net&gt;&n; *      All Rights Reserved      &n; *&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License. See the file COPYING in the main directory of this archive for&n; *  more details.&n; */
macro_line|#ifndef __I810_H__
DECL|macro|__I810_H__
mdefine_line|#define __I810_H__
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/agp_backend.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &lt;video/vga.h&gt;
multiline_comment|/* Fence */
DECL|macro|TILEWALK_X
mdefine_line|#define TILEWALK_X            (0 &lt;&lt; 12)
DECL|macro|TILEWALK_Y
mdefine_line|#define TILEWALK_Y            (1 &lt;&lt; 12)
multiline_comment|/* Raster ops */
DECL|macro|COLOR_COPY_ROP
mdefine_line|#define COLOR_COPY_ROP        0xF0
DECL|macro|PAT_COPY_ROP
mdefine_line|#define PAT_COPY_ROP          0xCC
DECL|macro|CLEAR_ROP
mdefine_line|#define CLEAR_ROP             0x00
DECL|macro|WHITE_ROP
mdefine_line|#define WHITE_ROP             0xFF
DECL|macro|INVERT_ROP
mdefine_line|#define INVERT_ROP            0x55
DECL|macro|XOR_ROP
mdefine_line|#define XOR_ROP               0x5A
multiline_comment|/* 2D Engine definitions */
DECL|macro|SOLIDPATTERN
mdefine_line|#define SOLIDPATTERN          0x80000000
DECL|macro|NONSOLID
mdefine_line|#define NONSOLID              0x00000000
DECL|macro|BPP8
mdefine_line|#define BPP8                  (0 &lt;&lt; 24)
DECL|macro|BPP16
mdefine_line|#define BPP16                 (1 &lt;&lt; 24)
DECL|macro|BPP24
mdefine_line|#define BPP24                 (2 &lt;&lt; 24)
DECL|macro|PIXCONF8
mdefine_line|#define PIXCONF8              (2 &lt;&lt; 16)
DECL|macro|PIXCONF15
mdefine_line|#define PIXCONF15             (4 &lt;&lt; 16)
DECL|macro|PIXCONF16
mdefine_line|#define PIXCONF16             (5 &lt;&lt; 16)
DECL|macro|PIXCONF24
mdefine_line|#define PIXCONF24             (6 &lt;&lt; 16)
DECL|macro|PIXCONF32
mdefine_line|#define PIXCONF32             (7 &lt;&lt; 16)
DECL|macro|DYN_COLOR_EN
mdefine_line|#define DYN_COLOR_EN          (1 &lt;&lt; 26)
DECL|macro|DYN_COLOR_DIS
mdefine_line|#define DYN_COLOR_DIS         (0 &lt;&lt; 26)
DECL|macro|INCREMENT
mdefine_line|#define INCREMENT             0x00000000
DECL|macro|DECREMENT
mdefine_line|#define DECREMENT             (0x01 &lt;&lt; 30)
DECL|macro|ARB_ON
mdefine_line|#define ARB_ON                0x00000001
DECL|macro|ARB_OFF
mdefine_line|#define ARB_OFF               0x00000000
DECL|macro|SYNC_FLIP
mdefine_line|#define SYNC_FLIP             0x00000000
DECL|macro|ASYNC_FLIP
mdefine_line|#define ASYNC_FLIP            0x00000040
DECL|macro|OPTYPE_MASK
mdefine_line|#define OPTYPE_MASK           0xE0000000
DECL|macro|PARSER_MASK
mdefine_line|#define PARSER_MASK           0x001F8000 
DECL|macro|D2_MASK
mdefine_line|#define D2_MASK               0x001FC000         /* 2D mask */
multiline_comment|/* Instruction type */
multiline_comment|/* There are more but pertains to 3D */
DECL|macro|PARSER
mdefine_line|#define PARSER                0x00000000
DECL|macro|BLIT
mdefine_line|#define BLIT                  (0x02 &lt;&lt; 29)
DECL|macro|RENDER
mdefine_line|#define RENDER                (0x03 &lt;&lt; 29)
multiline_comment|/* Parser */
DECL|macro|NOP
mdefine_line|#define NOP                   0x00               /* No operation, padding */
DECL|macro|BP_INT
mdefine_line|#define BP_INT                (0x01 &lt;&lt; 23)         /* Breakpoint interrupt */
DECL|macro|USR_INT
mdefine_line|#define USR_INT               (0x02 &lt;&lt; 23)         /* User interrupt */
DECL|macro|WAIT_FOR_EVNT
mdefine_line|#define WAIT_FOR_EVNT         (0x03 &lt;&lt; 23)         /* Wait for event */
DECL|macro|FLUSH
mdefine_line|#define FLUSH                 (0x04 &lt;&lt; 23)              
DECL|macro|CONTEXT_SEL
mdefine_line|#define CONTEXT_SEL           (0x05 &lt;&lt; 23)
DECL|macro|REPORT_HEAD
mdefine_line|#define REPORT_HEAD           (0x07 &lt;&lt; 23)
DECL|macro|ARB_ON_OFF
mdefine_line|#define ARB_ON_OFF            (0x08 &lt;&lt; 23)
DECL|macro|OVERLAY_FLIP
mdefine_line|#define OVERLAY_FLIP          (0x11 &lt;&lt; 23)
DECL|macro|LOAD_SCAN_INC
mdefine_line|#define LOAD_SCAN_INC         (0x12 &lt;&lt; 23)
DECL|macro|LOAD_SCAN_EX
mdefine_line|#define LOAD_SCAN_EX          (0x13 &lt;&lt; 23)
DECL|macro|FRONT_BUFFER
mdefine_line|#define FRONT_BUFFER          (0x14 &lt;&lt; 23)
DECL|macro|DEST_BUFFER
mdefine_line|#define DEST_BUFFER           (0x15 &lt;&lt; 23)
DECL|macro|Z_BUFFER
mdefine_line|#define Z_BUFFER              (0x16 &lt;&lt; 23)       
DECL|macro|STORE_DWORD_IMM
mdefine_line|#define STORE_DWORD_IMM       (0x20 &lt;&lt; 23)
DECL|macro|STORE_DWORD_IDX
mdefine_line|#define STORE_DWORD_IDX       (0x21 &lt;&lt; 23)
DECL|macro|BATCH_BUFFER
mdefine_line|#define BATCH_BUFFER          (0x30 &lt;&lt; 23)
multiline_comment|/* Blit */
DECL|macro|SETUP_BLIT
mdefine_line|#define SETUP_BLIT                      0x00
DECL|macro|SETUP_MONO_PATTERN_SL_BLT
mdefine_line|#define SETUP_MONO_PATTERN_SL_BLT       (0x10 &lt;&lt; 22)
DECL|macro|PIXEL_BLT
mdefine_line|#define PIXEL_BLT                       (0x20 &lt;&lt; 22)
DECL|macro|SCANLINE_BLT
mdefine_line|#define SCANLINE_BLT                    (0x21 &lt;&lt; 22)
DECL|macro|TEXT_BLT
mdefine_line|#define TEXT_BLT                        (0x22 &lt;&lt; 22)
DECL|macro|TEXT_IMM_BLT
mdefine_line|#define TEXT_IMM_BLT                    (0x30 &lt;&lt; 22)
DECL|macro|COLOR_BLT
mdefine_line|#define COLOR_BLT                       (0x40 &lt;&lt; 22)
DECL|macro|MONO_PAT_BLIT
mdefine_line|#define MONO_PAT_BLIT                   (0x42 &lt;&lt; 22)
DECL|macro|SOURCE_COPY_BLIT
mdefine_line|#define SOURCE_COPY_BLIT                (0x43 &lt;&lt; 22)
DECL|macro|MONO_SOURCE_COPY_BLIT
mdefine_line|#define MONO_SOURCE_COPY_BLIT           (0x44 &lt;&lt; 22)
DECL|macro|SOURCE_COPY_IMMEDIATE
mdefine_line|#define SOURCE_COPY_IMMEDIATE           (0x60 &lt;&lt; 22)
DECL|macro|MONO_SOURCE_COPY_IMMEDIATE
mdefine_line|#define MONO_SOURCE_COPY_IMMEDIATE      (0x61 &lt;&lt; 22)
DECL|macro|VERSION_MAJOR
mdefine_line|#define VERSION_MAJOR            0
DECL|macro|VERSION_MINOR
mdefine_line|#define VERSION_MINOR            9
DECL|macro|VERSION_TEENIE
mdefine_line|#define VERSION_TEENIE           0
DECL|macro|BRANCH_VERSION
mdefine_line|#define BRANCH_VERSION           &quot;&quot;
multiline_comment|/* mvo: intel i815 */
macro_line|#ifndef PCI_DEVICE_ID_INTEL_82815_100
DECL|macro|PCI_DEVICE_ID_INTEL_82815_100
mdefine_line|#define PCI_DEVICE_ID_INTEL_82815_100           0x1102
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_INTEL_82815_NOAGP
DECL|macro|PCI_DEVICE_ID_INTEL_82815_NOAGP
mdefine_line|#define PCI_DEVICE_ID_INTEL_82815_NOAGP         0x1112
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_INTEL_82815_FULL_CTRL
DECL|macro|PCI_DEVICE_ID_INTEL_82815_FULL_CTRL
mdefine_line|#define PCI_DEVICE_ID_INTEL_82815_FULL_CTRL     0x1130
macro_line|#endif 
multiline_comment|/* General Defines */
DECL|macro|I810_PAGESIZE
mdefine_line|#define I810_PAGESIZE               4096
DECL|macro|MAX_DMA_SIZE
mdefine_line|#define MAX_DMA_SIZE                (1024 * 4096)
DECL|macro|SAREA_SIZE
mdefine_line|#define SAREA_SIZE                  4096
DECL|macro|PCI_I810_MISCC
mdefine_line|#define PCI_I810_MISCC              0x72
DECL|macro|MMIO_SIZE
mdefine_line|#define MMIO_SIZE                   (512*1024)
DECL|macro|GTT_SIZE
mdefine_line|#define GTT_SIZE                    (16*1024) 
DECL|macro|RINGBUFFER_SIZE
mdefine_line|#define RINGBUFFER_SIZE             (64*1024)
DECL|macro|CURSOR_SIZE
mdefine_line|#define CURSOR_SIZE                 4096 
DECL|macro|OFF
mdefine_line|#define OFF                         0
DECL|macro|ON
mdefine_line|#define ON                          1
DECL|macro|MAX_KEY
mdefine_line|#define MAX_KEY                     256
DECL|macro|WAIT_COUNT
mdefine_line|#define WAIT_COUNT                  10000000
DECL|macro|IRING_PAD
mdefine_line|#define IRING_PAD                   8
DECL|macro|FONTDATAMAX
mdefine_line|#define FONTDATAMAX                 8192
multiline_comment|/* Masks (AND ops) and OR&squot;s */
DECL|macro|FB_START_MASK
mdefine_line|#define FB_START_MASK               (0x3f &lt;&lt; (32 - 6))
DECL|macro|MMIO_ADDR_MASK
mdefine_line|#define MMIO_ADDR_MASK              (0x1FFF &lt;&lt; (32 - 13))
DECL|macro|FREQ_MASK
mdefine_line|#define FREQ_MASK                   0x1EF
DECL|macro|SCR_OFF
mdefine_line|#define SCR_OFF                     0x20
DECL|macro|DRAM_ON
mdefine_line|#define DRAM_ON                     0x08            
DECL|macro|DRAM_OFF
mdefine_line|#define DRAM_OFF                    0xE7
DECL|macro|PG_ENABLE_MASK
mdefine_line|#define PG_ENABLE_MASK              0x01
DECL|macro|RING_SIZE_MASK
mdefine_line|#define RING_SIZE_MASK              (RINGBUFFER_SIZE - 1);
multiline_comment|/* defines for restoring registers partially */
DECL|macro|ADDR_MAP_MASK
mdefine_line|#define ADDR_MAP_MASK               (0x07 &lt;&lt; 5)
DECL|macro|DISP_CTRL
mdefine_line|#define DISP_CTRL                   ~0
DECL|macro|PIXCONF_0
mdefine_line|#define PIXCONF_0                   (0x64 &lt;&lt; 8)
DECL|macro|PIXCONF_2
mdefine_line|#define PIXCONF_2                   (0xF3 &lt;&lt; 24)
DECL|macro|PIXCONF_1
mdefine_line|#define PIXCONF_1                   (0xF0 &lt;&lt; 16)
DECL|macro|MN_MASK
mdefine_line|#define MN_MASK                     0x3FF03FF
DECL|macro|P_OR
mdefine_line|#define P_OR                        (0x7 &lt;&lt; 4)                    
DECL|macro|DAC_BIT
mdefine_line|#define DAC_BIT                     (1 &lt;&lt; 16)
DECL|macro|INTERLACE_BIT
mdefine_line|#define INTERLACE_BIT               (1 &lt;&lt; 7)
DECL|macro|IER_MASK
mdefine_line|#define IER_MASK                    (3 &lt;&lt; 13)
DECL|macro|IMR_MASK
mdefine_line|#define IMR_MASK                    (3 &lt;&lt; 13)
multiline_comment|/* Power Management */
DECL|macro|DPMS_MASK
mdefine_line|#define DPMS_MASK                   0xF0000
DECL|macro|POWERON
mdefine_line|#define POWERON                     0x00000
DECL|macro|STANDBY
mdefine_line|#define STANDBY                     0x20000
DECL|macro|SUSPEND
mdefine_line|#define SUSPEND                     0x80000
DECL|macro|POWERDOWN
mdefine_line|#define POWERDOWN                   0xA0000
DECL|macro|EMR_MASK
mdefine_line|#define EMR_MASK                    ~0x3F
DECL|macro|FW_BLC_MASK
mdefine_line|#define FW_BLC_MASK                 ~(0x3F|(7 &lt;&lt; 8)|(0x3F &lt;&lt; 12)|(7 &lt;&lt; 20))
multiline_comment|/* Ringbuffer */
DECL|macro|RBUFFER_START_MASK
mdefine_line|#define RBUFFER_START_MASK          0xFFFFF000
DECL|macro|RBUFFER_SIZE_MASK
mdefine_line|#define RBUFFER_SIZE_MASK           0x001FF000
DECL|macro|RBUFFER_HEAD_MASK
mdefine_line|#define RBUFFER_HEAD_MASK           0x001FFFFC
DECL|macro|RBUFFER_TAIL_MASK
mdefine_line|#define RBUFFER_TAIL_MASK           0x001FFFF8
multiline_comment|/* Video Timings */
DECL|macro|REF_FREQ
mdefine_line|#define REF_FREQ                    24000000
DECL|macro|TARGET_N_MAX
mdefine_line|#define TARGET_N_MAX                30
DECL|macro|MAX_PIXELCLOCK
mdefine_line|#define MAX_PIXELCLOCK              230000000
DECL|macro|MIN_PIXELCLOCK
mdefine_line|#define MIN_PIXELCLOCK               15000000
DECL|macro|VFMAX
mdefine_line|#define VFMAX                       60
DECL|macro|VFMIN
mdefine_line|#define VFMIN                       60
DECL|macro|HFMAX
mdefine_line|#define HFMAX                       30000
DECL|macro|HFMIN
mdefine_line|#define HFMIN                       29000
multiline_comment|/* Cursor */
DECL|macro|CURSOR_ENABLE_MASK
mdefine_line|#define CURSOR_ENABLE_MASK          0x1000             
DECL|macro|CURSOR_MODE_64_TRANS
mdefine_line|#define CURSOR_MODE_64_TRANS        4
DECL|macro|CURSOR_MODE_64_XOR
mdefine_line|#define CURSOR_MODE_64_XOR&t;    5
DECL|macro|CURSOR_MODE_64_3C
mdefine_line|#define CURSOR_MODE_64_3C&t;    6&t;
DECL|macro|COORD_INACTIVE
mdefine_line|#define COORD_INACTIVE              0
DECL|macro|COORD_ACTIVE
mdefine_line|#define COORD_ACTIVE                (1 &lt;&lt; 4)
DECL|macro|EXTENDED_PALETTE
mdefine_line|#define EXTENDED_PALETTE&t;    1
multiline_comment|/* AGP Memory Types*/
DECL|macro|AGP_NORMAL_MEMORY
mdefine_line|#define AGP_NORMAL_MEMORY           0
DECL|macro|AGP_DCACHE_MEMORY
mdefine_line|#define AGP_DCACHE_MEMORY&t;    1
DECL|macro|AGP_PHYSICAL_MEMORY
mdefine_line|#define AGP_PHYSICAL_MEMORY         2
multiline_comment|/* Allocated resource Flags */
DECL|macro|FRAMEBUFFER_REQ
mdefine_line|#define FRAMEBUFFER_REQ             1
DECL|macro|MMIO_REQ
mdefine_line|#define MMIO_REQ                    2
DECL|macro|PCI_DEVICE_ENABLED
mdefine_line|#define PCI_DEVICE_ENABLED          4
DECL|macro|HAS_FONTCACHE
mdefine_line|#define HAS_FONTCACHE               8 
multiline_comment|/* driver flags */
DECL|macro|HAS_MTRR
mdefine_line|#define HAS_MTRR                    1
DECL|macro|HAS_ACCELERATION
mdefine_line|#define HAS_ACCELERATION            2
DECL|macro|ALWAYS_SYNC
mdefine_line|#define ALWAYS_SYNC                 4
DECL|macro|LOCKUP
mdefine_line|#define LOCKUP                      8
DECL|macro|USE_HWCUR
mdefine_line|#define USE_HWCUR                  16
DECL|struct|gtt_data
r_struct
id|gtt_data
(brace
DECL|member|i810_fb_memory
r_struct
id|agp_memory
op_star
id|i810_fb_memory
suffix:semicolon
DECL|member|i810_cursor_memory
r_struct
id|agp_memory
op_star
id|i810_cursor_memory
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|mode_registers
r_struct
id|mode_registers
(brace
DECL|member|pixclock
DECL|member|M
DECL|member|N
DECL|member|P
id|u32
id|pixclock
comma
id|M
comma
id|N
comma
id|P
suffix:semicolon
DECL|member|cr00
DECL|member|cr01
DECL|member|cr02
DECL|member|cr03
id|u8
id|cr00
comma
id|cr01
comma
id|cr02
comma
id|cr03
suffix:semicolon
DECL|member|cr04
DECL|member|cr05
DECL|member|cr06
DECL|member|cr07
id|u8
id|cr04
comma
id|cr05
comma
id|cr06
comma
id|cr07
suffix:semicolon
DECL|member|cr09
DECL|member|cr10
DECL|member|cr11
DECL|member|cr12
id|u8
id|cr09
comma
id|cr10
comma
id|cr11
comma
id|cr12
suffix:semicolon
DECL|member|cr13
DECL|member|cr15
DECL|member|cr16
DECL|member|cr30
id|u8
id|cr13
comma
id|cr15
comma
id|cr16
comma
id|cr30
suffix:semicolon
DECL|member|cr31
DECL|member|cr32
DECL|member|cr33
DECL|member|cr35
DECL|member|cr39
id|u8
id|cr31
comma
id|cr32
comma
id|cr33
comma
id|cr35
comma
id|cr39
suffix:semicolon
DECL|member|bpp8_100
DECL|member|bpp16_100
id|u32
id|bpp8_100
comma
id|bpp16_100
suffix:semicolon
DECL|member|bpp24_100
DECL|member|bpp8_133
id|u32
id|bpp24_100
comma
id|bpp8_133
suffix:semicolon
DECL|member|bpp16_133
DECL|member|bpp24_133
id|u32
id|bpp16_133
comma
id|bpp24_133
suffix:semicolon
DECL|member|msr
id|u8
id|msr
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|heap_data
r_struct
id|heap_data
(brace
DECL|member|physical
r_int
r_int
id|physical
suffix:semicolon
DECL|member|virtual
id|__u8
id|__iomem
op_star
r_virtual
suffix:semicolon
DECL|member|offset
id|u32
id|offset
suffix:semicolon
DECL|member|size
id|u32
id|size
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|state_registers
r_struct
id|state_registers
(brace
DECL|member|dclk_1d
DECL|member|dclk_2d
DECL|member|dclk_0ds
id|u32
id|dclk_1d
comma
id|dclk_2d
comma
id|dclk_0ds
suffix:semicolon
DECL|member|pixconf
DECL|member|fw_blc
DECL|member|pgtbl_ctl
id|u32
id|pixconf
comma
id|fw_blc
comma
id|pgtbl_ctl
suffix:semicolon
DECL|member|fence0
DECL|member|hws_pga
DECL|member|dplystas
id|u32
id|fence0
comma
id|hws_pga
comma
id|dplystas
suffix:semicolon
DECL|member|bltcntl
DECL|member|hwstam
DECL|member|ier
DECL|member|iir
DECL|member|imr
id|u16
id|bltcntl
comma
id|hwstam
comma
id|ier
comma
id|iir
comma
id|imr
suffix:semicolon
DECL|member|cr00
DECL|member|cr01
DECL|member|cr02
DECL|member|cr03
DECL|member|cr04
id|u8
id|cr00
comma
id|cr01
comma
id|cr02
comma
id|cr03
comma
id|cr04
suffix:semicolon
DECL|member|cr05
DECL|member|cr06
DECL|member|cr07
DECL|member|cr08
DECL|member|cr09
id|u8
id|cr05
comma
id|cr06
comma
id|cr07
comma
id|cr08
comma
id|cr09
suffix:semicolon
DECL|member|cr10
DECL|member|cr11
DECL|member|cr12
DECL|member|cr13
DECL|member|cr14
id|u8
id|cr10
comma
id|cr11
comma
id|cr12
comma
id|cr13
comma
id|cr14
suffix:semicolon
DECL|member|cr15
DECL|member|cr16
DECL|member|cr17
DECL|member|cr80
DECL|member|gr10
id|u8
id|cr15
comma
id|cr16
comma
id|cr17
comma
id|cr80
comma
id|gr10
suffix:semicolon
DECL|member|cr30
DECL|member|cr31
DECL|member|cr32
DECL|member|cr33
DECL|member|cr35
id|u8
id|cr30
comma
id|cr31
comma
id|cr32
comma
id|cr33
comma
id|cr35
suffix:semicolon
DECL|member|cr39
DECL|member|cr41
DECL|member|cr70
DECL|member|sr01
DECL|member|msr
id|u8
id|cr39
comma
id|cr41
comma
id|cr70
comma
id|sr01
comma
id|msr
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|i810fb_par
r_struct
id|i810fb_par
(brace
DECL|member|regs
r_struct
id|mode_registers
id|regs
suffix:semicolon
DECL|member|hw_state
r_struct
id|state_registers
id|hw_state
suffix:semicolon
DECL|member|i810_gtt
r_struct
id|gtt_data
id|i810_gtt
suffix:semicolon
DECL|member|i810fb_ops
r_struct
id|fb_ops
id|i810fb_ops
suffix:semicolon
DECL|member|dev
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
DECL|member|aperture
r_struct
id|heap_data
id|aperture
suffix:semicolon
DECL|member|fb
r_struct
id|heap_data
id|fb
suffix:semicolon
DECL|member|iring
r_struct
id|heap_data
id|iring
suffix:semicolon
DECL|member|cursor_heap
r_struct
id|heap_data
id|cursor_heap
suffix:semicolon
DECL|member|state
r_struct
id|vgastate
id|state
suffix:semicolon
DECL|member|use_count
id|atomic_t
id|use_count
suffix:semicolon
DECL|member|pseudo_palette
id|u32
id|pseudo_palette
(braket
l_int|17
)braket
suffix:semicolon
DECL|member|mmio_start_phys
r_int
r_int
id|mmio_start_phys
suffix:semicolon
DECL|member|mmio_start_virtual
id|u8
id|__iomem
op_star
id|mmio_start_virtual
suffix:semicolon
DECL|member|pitch
id|u32
id|pitch
suffix:semicolon
DECL|member|pixconf
id|u32
id|pixconf
suffix:semicolon
DECL|member|watermark
id|u32
id|watermark
suffix:semicolon
DECL|member|mem_freq
id|u32
id|mem_freq
suffix:semicolon
DECL|member|res_flags
id|u32
id|res_flags
suffix:semicolon
DECL|member|dev_flags
id|u32
id|dev_flags
suffix:semicolon
DECL|member|cur_tail
id|u32
id|cur_tail
suffix:semicolon
DECL|member|depth
id|u32
id|depth
suffix:semicolon
DECL|member|blit_bpp
id|u32
id|blit_bpp
suffix:semicolon
DECL|member|ovract
id|u32
id|ovract
suffix:semicolon
DECL|member|cur_state
id|u32
id|cur_state
suffix:semicolon
DECL|member|mtrr_reg
r_int
id|mtrr_reg
suffix:semicolon
DECL|member|bltcntl
id|u16
id|bltcntl
suffix:semicolon
DECL|member|interlace
id|u8
id|interlace
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* &n; * Register I/O&n; */
DECL|macro|i810_readb
mdefine_line|#define i810_readb(where, mmio) readb(mmio + where)
DECL|macro|i810_readw
mdefine_line|#define i810_readw(where, mmio) readw(mmio + where)
DECL|macro|i810_readl
mdefine_line|#define i810_readl(where, mmio) readl(mmio + where)
DECL|macro|i810_writeb
mdefine_line|#define i810_writeb(where, mmio, val) writeb(val, mmio + where) 
DECL|macro|i810_writew
mdefine_line|#define i810_writew(where, mmio, val) writew(val, mmio + where)
DECL|macro|i810_writel
mdefine_line|#define i810_writel(where, mmio, val) writel(val, mmio + where)
macro_line|#endif /* __I810_H__ */
eof
