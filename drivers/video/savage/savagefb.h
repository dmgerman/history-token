multiline_comment|/*&n; * linux/drivers/video/savagefb.h -- S3 Savage Framebuffer Driver&n; *&n; * Copyright (c) 2001  Denis Oliver Kropp &lt;dok@convergence.de&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; */
macro_line|#ifndef __SAVAGEFB_H__
DECL|macro|__SAVAGEFB_H__
mdefine_line|#define __SAVAGEFB_H__
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;linux/i2c-id.h&gt;
macro_line|#include &lt;linux/i2c-algo-bit.h&gt;
macro_line|#include &quot;../edid.h&quot;
macro_line|#ifdef SAVAGEFB_DEBUG
DECL|macro|DBG
macro_line|# define DBG(x)&t;&t;printk (KERN_DEBUG &quot;savagefb: %s&bslash;n&quot;, (x));
macro_line|#else
DECL|macro|DBG
macro_line|# define DBG(x)
DECL|macro|SavagePrintRegs
macro_line|# define SavagePrintRegs(...)
macro_line|#endif
DECL|macro|PCI_CHIP_SAVAGE4
mdefine_line|#define PCI_CHIP_SAVAGE4      0x8a22
DECL|macro|PCI_CHIP_SAVAGE3D
mdefine_line|#define PCI_CHIP_SAVAGE3D     0x8a20
DECL|macro|PCI_CHIP_SAVAGE3D_MV
mdefine_line|#define PCI_CHIP_SAVAGE3D_MV  0x8a21
DECL|macro|PCI_CHIP_SAVAGE2000
mdefine_line|#define PCI_CHIP_SAVAGE2000   0x9102
DECL|macro|PCI_CHIP_SAVAGE_MX_MV
mdefine_line|#define PCI_CHIP_SAVAGE_MX_MV 0x8c10
DECL|macro|PCI_CHIP_SAVAGE_MX
mdefine_line|#define PCI_CHIP_SAVAGE_MX    0x8c11
DECL|macro|PCI_CHIP_SAVAGE_IX_MV
mdefine_line|#define PCI_CHIP_SAVAGE_IX_MV 0x8c12
DECL|macro|PCI_CHIP_SAVAGE_IX
mdefine_line|#define PCI_CHIP_SAVAGE_IX    0x8c13
DECL|macro|PCI_CHIP_PROSAVAGE_PM
mdefine_line|#define PCI_CHIP_PROSAVAGE_PM 0x8a25
DECL|macro|PCI_CHIP_PROSAVAGE_KM
mdefine_line|#define PCI_CHIP_PROSAVAGE_KM 0x8a26
multiline_comment|/* Twister is a code name; hope I get the real name soon. */
DECL|macro|PCI_CHIP_S3TWISTER_P
mdefine_line|#define PCI_CHIP_S3TWISTER_P  0x8d01
DECL|macro|PCI_CHIP_S3TWISTER_K
mdefine_line|#define PCI_CHIP_S3TWISTER_K  0x8d02
DECL|macro|PCI_CHIP_PROSAVAGE_DDR
mdefine_line|#define PCI_CHIP_PROSAVAGE_DDR          0x8d03
DECL|macro|PCI_CHIP_PROSAVAGE_DDRK
mdefine_line|#define PCI_CHIP_PROSAVAGE_DDRK         0x8d04
DECL|macro|PCI_CHIP_SUPSAV_MX128
mdefine_line|#define PCI_CHIP_SUPSAV_MX128&t;&t;0x8c22
DECL|macro|PCI_CHIP_SUPSAV_MX64
mdefine_line|#define PCI_CHIP_SUPSAV_MX64&t;&t;0x8c24
DECL|macro|PCI_CHIP_SUPSAV_MX64C
mdefine_line|#define PCI_CHIP_SUPSAV_MX64C&t;&t;0x8c26
DECL|macro|PCI_CHIP_SUPSAV_IX128SDR
mdefine_line|#define PCI_CHIP_SUPSAV_IX128SDR&t;0x8c2a
DECL|macro|PCI_CHIP_SUPSAV_IX128DDR
mdefine_line|#define PCI_CHIP_SUPSAV_IX128DDR&t;0x8c2b
DECL|macro|PCI_CHIP_SUPSAV_IX64SDR
mdefine_line|#define PCI_CHIP_SUPSAV_IX64SDR&t;&t;0x8c2c
DECL|macro|PCI_CHIP_SUPSAV_IX64DDR
mdefine_line|#define PCI_CHIP_SUPSAV_IX64DDR&t;&t;0x8c2d
DECL|macro|PCI_CHIP_SUPSAV_IXCSDR
mdefine_line|#define PCI_CHIP_SUPSAV_IXCSDR&t;&t;0x8c2e
DECL|macro|PCI_CHIP_SUPSAV_IXCDDR
mdefine_line|#define PCI_CHIP_SUPSAV_IXCDDR&t;&t;0x8c2f
DECL|macro|S3_SAVAGE3D_SERIES
mdefine_line|#define S3_SAVAGE3D_SERIES(chip)  ((chip&gt;=S3_SAVAGE3D) &amp;&amp; (chip&lt;=S3_SAVAGE_MX))
DECL|macro|S3_SAVAGE4_SERIES
mdefine_line|#define S3_SAVAGE4_SERIES(chip)   ((chip==S3_SAVAGE4) || (chip==S3_PROSAVAGE))
DECL|macro|S3_SAVAGE_MOBILE_SERIES
mdefine_line|#define S3_SAVAGE_MOBILE_SERIES(chip)  ((chip==S3_SAVAGE_MX) || (chip==S3_SUPERSAVAGE))
DECL|macro|S3_SAVAGE_SERIES
mdefine_line|#define S3_SAVAGE_SERIES(chip)    ((chip&gt;=S3_SAVAGE3D) &amp;&amp; (chip&lt;=S3_SAVAGE2000))
multiline_comment|/* Chip tags.  These are used to group the adapters into&n; * related families.&n; */
r_typedef
r_enum
(brace
DECL|enumerator|S3_UNKNOWN
id|S3_UNKNOWN
op_assign
l_int|0
comma
DECL|enumerator|S3_SAVAGE3D
id|S3_SAVAGE3D
comma
DECL|enumerator|S3_SAVAGE_MX
id|S3_SAVAGE_MX
comma
DECL|enumerator|S3_SAVAGE4
id|S3_SAVAGE4
comma
DECL|enumerator|S3_PROSAVAGE
id|S3_PROSAVAGE
comma
DECL|enumerator|S3_SUPERSAVAGE
id|S3_SUPERSAVAGE
comma
DECL|enumerator|S3_SAVAGE2000
id|S3_SAVAGE2000
comma
DECL|enumerator|S3_LAST
id|S3_LAST
DECL|typedef|savage_chipset
)brace
id|savage_chipset
suffix:semicolon
DECL|macro|BIOS_BSIZE
mdefine_line|#define BIOS_BSIZE&t;&t;     1024
DECL|macro|BIOS_BASE
mdefine_line|#define BIOS_BASE&t;&t;     0xc0000
DECL|macro|SAVAGE_NEWMMIO_REGBASE_S3
mdefine_line|#define SAVAGE_NEWMMIO_REGBASE_S3    0x1000000  /* 16MB */
DECL|macro|SAVAGE_NEWMMIO_REGBASE_S4
mdefine_line|#define SAVAGE_NEWMMIO_REGBASE_S4    0x0000000
DECL|macro|SAVAGE_NEWMMIO_REGSIZE
mdefine_line|#define SAVAGE_NEWMMIO_REGSIZE&t;     0x0080000  /* 512kb */
DECL|macro|SAVAGE_NEWMMIO_VGABASE
mdefine_line|#define SAVAGE_NEWMMIO_VGABASE&t;     0x8000
DECL|macro|BASE_FREQ
mdefine_line|#define BASE_FREQ&t;&t;     14318
DECL|macro|HALF_BASE_FREQ
mdefine_line|#define HALF_BASE_FREQ               7159
DECL|macro|FIFO_CONTROL_REG
mdefine_line|#define FIFO_CONTROL_REG&t;     0x8200
DECL|macro|MIU_CONTROL_REG
mdefine_line|#define MIU_CONTROL_REG&t;&t;     0x8204
DECL|macro|STREAMS_TIMEOUT_REG
mdefine_line|#define STREAMS_TIMEOUT_REG&t;     0x8208
DECL|macro|MISC_TIMEOUT_REG
mdefine_line|#define MISC_TIMEOUT_REG&t;     0x820c
DECL|macro|MONO_PAT_0
mdefine_line|#define MONO_PAT_0                   0xa4e8
DECL|macro|MONO_PAT_1
mdefine_line|#define MONO_PAT_1                   0xa4ec
DECL|macro|MAXFIFO
mdefine_line|#define MAXFIFO                      0x7f00
DECL|macro|BCI_CMD_NOP
mdefine_line|#define BCI_CMD_NOP                  0x40000000
DECL|macro|BCI_CMD_SETREG
mdefine_line|#define BCI_CMD_SETREG               0x96000000
DECL|macro|BCI_CMD_RECT
mdefine_line|#define BCI_CMD_RECT                 0x48000000
DECL|macro|BCI_CMD_RECT_XP
mdefine_line|#define BCI_CMD_RECT_XP              0x01000000
DECL|macro|BCI_CMD_RECT_YP
mdefine_line|#define BCI_CMD_RECT_YP              0x02000000
DECL|macro|BCI_CMD_SEND_COLOR
mdefine_line|#define BCI_CMD_SEND_COLOR           0x00008000
DECL|macro|BCI_CMD_DEST_GBD
mdefine_line|#define BCI_CMD_DEST_GBD             0x00000000
DECL|macro|BCI_CMD_SRC_GBD
mdefine_line|#define BCI_CMD_SRC_GBD              0x00000020
DECL|macro|BCI_CMD_SRC_SOLID
mdefine_line|#define BCI_CMD_SRC_SOLID            0x00000000
DECL|macro|BCI_CMD_SRC_MONO
mdefine_line|#define BCI_CMD_SRC_MONO             0x00000060
DECL|macro|BCI_CMD_CLIP_NEW
mdefine_line|#define BCI_CMD_CLIP_NEW             0x00006000
DECL|macro|BCI_CMD_CLIP_LR
mdefine_line|#define BCI_CMD_CLIP_LR              0x00004000
DECL|macro|BCI_CLIP_LR
mdefine_line|#define BCI_CLIP_LR(l, r)            ((((r) &lt;&lt; 16) | (l)) &amp; 0x0FFF0FFF)
DECL|macro|BCI_CLIP_TL
mdefine_line|#define BCI_CLIP_TL(t, l)            ((((t) &lt;&lt; 16) | (l)) &amp; 0x0FFF0FFF)
DECL|macro|BCI_CLIP_BR
mdefine_line|#define BCI_CLIP_BR(b, r)            ((((b) &lt;&lt; 16) | (r)) &amp; 0x0FFF0FFF)
DECL|macro|BCI_W_H
mdefine_line|#define BCI_W_H(w, h)                (((h) &lt;&lt; 16) | ((w) &amp; 0xFFF))
DECL|macro|BCI_X_Y
mdefine_line|#define BCI_X_Y(x, y)                (((y) &lt;&lt; 16) | ((x) &amp; 0xFFF))
DECL|macro|BCI_GBD1
mdefine_line|#define BCI_GBD1                     0xE0
DECL|macro|BCI_GBD2
mdefine_line|#define BCI_GBD2                     0xE1
DECL|macro|BCI_BUFFER_OFFSET
mdefine_line|#define BCI_BUFFER_OFFSET            0x10000
DECL|macro|BCI_SIZE
mdefine_line|#define BCI_SIZE                     0x4000
DECL|macro|BCI_SEND
mdefine_line|#define BCI_SEND(dw)                 writel(dw, par-&gt;bci_base + par-&gt;bci_ptr++)
DECL|macro|BCI_CMD_GET_ROP
mdefine_line|#define BCI_CMD_GET_ROP(cmd)         (((cmd) &gt;&gt; 16) &amp; 0xFF)
DECL|macro|BCI_CMD_SET_ROP
mdefine_line|#define BCI_CMD_SET_ROP(cmd, rop)    ((cmd) |= ((rop &amp; 0xFF) &lt;&lt; 16))
DECL|macro|BCI_CMD_SEND_COLOR
mdefine_line|#define BCI_CMD_SEND_COLOR           0x00008000
DECL|struct|xtimings
r_struct
id|xtimings
(brace
DECL|member|Clock
r_int
r_int
id|Clock
suffix:semicolon
DECL|member|HDisplay
r_int
r_int
id|HDisplay
suffix:semicolon
DECL|member|HSyncStart
r_int
r_int
id|HSyncStart
suffix:semicolon
DECL|member|HSyncEnd
r_int
r_int
id|HSyncEnd
suffix:semicolon
DECL|member|HTotal
r_int
r_int
id|HTotal
suffix:semicolon
DECL|member|HAdjusted
r_int
r_int
id|HAdjusted
suffix:semicolon
DECL|member|VDisplay
r_int
r_int
id|VDisplay
suffix:semicolon
DECL|member|VSyncStart
r_int
r_int
id|VSyncStart
suffix:semicolon
DECL|member|VSyncEnd
r_int
r_int
id|VSyncEnd
suffix:semicolon
DECL|member|VTotal
r_int
r_int
id|VTotal
suffix:semicolon
DECL|member|sync
r_int
r_int
id|sync
suffix:semicolon
DECL|member|dblscan
r_int
id|dblscan
suffix:semicolon
DECL|member|interlaced
r_int
id|interlaced
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* --------------------------------------------------------------------- */
DECL|macro|NR_PALETTE
mdefine_line|#define NR_PALETTE&t;256
r_struct
id|savagefb_par
suffix:semicolon
DECL|struct|savagefb_i2c_chan
r_struct
id|savagefb_i2c_chan
(brace
DECL|member|par
r_struct
id|savagefb_par
op_star
id|par
suffix:semicolon
DECL|member|adapter
r_struct
id|i2c_adapter
id|adapter
suffix:semicolon
DECL|member|algo
r_struct
id|i2c_algo_bit_data
id|algo
suffix:semicolon
DECL|member|ioaddr
r_volatile
id|u8
id|__iomem
op_star
id|ioaddr
suffix:semicolon
DECL|member|reg
id|u32
id|reg
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|savagefb_par
r_struct
id|savagefb_par
(brace
DECL|member|pcidev
r_struct
id|pci_dev
op_star
id|pcidev
suffix:semicolon
DECL|member|chip
id|savage_chipset
id|chip
suffix:semicolon
DECL|member|chan
r_struct
id|savagefb_i2c_chan
id|chan
suffix:semicolon
DECL|member|edid
r_int
r_char
op_star
id|edid
suffix:semicolon
DECL|member|pseudo_palette
id|u32
id|pseudo_palette
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|dacSpeedBpp
r_int
id|dacSpeedBpp
suffix:semicolon
DECL|member|maxClock
r_int
id|maxClock
suffix:semicolon
DECL|member|minClock
r_int
id|minClock
suffix:semicolon
DECL|member|numClocks
r_int
id|numClocks
suffix:semicolon
DECL|member|clock
r_int
id|clock
(braket
l_int|4
)braket
suffix:semicolon
r_struct
(brace
DECL|member|vbase
id|u8
id|__iomem
op_star
id|vbase
suffix:semicolon
DECL|member|pbase
id|u32
id|pbase
suffix:semicolon
DECL|member|len
id|u32
id|len
suffix:semicolon
macro_line|#ifdef CONFIG_MTRR
DECL|member|mtrr
r_int
id|mtrr
suffix:semicolon
macro_line|#endif
DECL|member|video
)brace
id|video
suffix:semicolon
r_struct
(brace
DECL|member|vbase
r_volatile
id|u8
id|__iomem
op_star
id|vbase
suffix:semicolon
DECL|member|pbase
id|u32
id|pbase
suffix:semicolon
DECL|member|len
id|u32
id|len
suffix:semicolon
DECL|member|mmio
)brace
id|mmio
suffix:semicolon
DECL|member|bci_base
r_volatile
id|u32
id|__iomem
op_star
id|bci_base
suffix:semicolon
DECL|member|bci_ptr
r_int
r_int
id|bci_ptr
suffix:semicolon
DECL|member|cob_offset
id|u32
id|cob_offset
suffix:semicolon
DECL|member|cob_size
id|u32
id|cob_size
suffix:semicolon
DECL|member|cob_index
r_int
id|cob_index
suffix:semicolon
DECL|member|SavageWaitIdle
r_void
(paren
op_star
id|SavageWaitIdle
)paren
(paren
r_struct
id|savagefb_par
op_star
id|par
)paren
suffix:semicolon
DECL|member|SavageWaitFifo
r_void
(paren
op_star
id|SavageWaitFifo
)paren
(paren
r_struct
id|savagefb_par
op_star
id|par
comma
r_int
id|space
)paren
suffix:semicolon
DECL|member|MCLK
DECL|member|REFCLK
DECL|member|LCDclk
r_int
id|MCLK
comma
id|REFCLK
comma
id|LCDclk
suffix:semicolon
DECL|member|HorizScaleFactor
r_int
id|HorizScaleFactor
suffix:semicolon
multiline_comment|/* Panels size */
DECL|member|SavagePanelWidth
r_int
id|SavagePanelWidth
suffix:semicolon
DECL|member|SavagePanelHeight
r_int
id|SavagePanelHeight
suffix:semicolon
r_struct
(brace
DECL|member|red
DECL|member|green
DECL|member|blue
DECL|member|transp
id|u16
id|red
comma
id|green
comma
id|blue
comma
id|transp
suffix:semicolon
DECL|member|palette
)brace
id|palette
(braket
id|NR_PALETTE
)braket
suffix:semicolon
DECL|member|depth
r_int
id|depth
suffix:semicolon
DECL|member|vwidth
r_int
id|vwidth
suffix:semicolon
DECL|member|MiscOutReg
r_int
r_char
id|MiscOutReg
suffix:semicolon
multiline_comment|/* Misc */
DECL|member|CRTC
r_int
r_char
id|CRTC
(braket
l_int|25
)braket
suffix:semicolon
multiline_comment|/* Crtc Controller */
DECL|member|Sequencer
r_int
r_char
id|Sequencer
(braket
l_int|5
)braket
suffix:semicolon
multiline_comment|/* Video Sequencer */
DECL|member|Graphics
r_int
r_char
id|Graphics
(braket
l_int|9
)braket
suffix:semicolon
multiline_comment|/* Video Graphics */
DECL|member|Attribute
r_int
r_char
id|Attribute
(braket
l_int|21
)braket
suffix:semicolon
multiline_comment|/* Video Atribute */
DECL|member|mode
DECL|member|refresh
r_int
r_int
id|mode
comma
id|refresh
suffix:semicolon
DECL|member|SR08
DECL|member|SR0E
DECL|member|SR0F
r_int
r_char
id|SR08
comma
id|SR0E
comma
id|SR0F
suffix:semicolon
DECL|member|SR10
DECL|member|SR11
DECL|member|SR12
DECL|member|SR13
DECL|member|SR15
DECL|member|SR18
DECL|member|SR29
DECL|member|SR30
r_int
r_char
id|SR10
comma
id|SR11
comma
id|SR12
comma
id|SR13
comma
id|SR15
comma
id|SR18
comma
id|SR29
comma
id|SR30
suffix:semicolon
DECL|member|SR54
r_int
r_char
id|SR54
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|Clock
r_int
r_char
id|Clock
suffix:semicolon
DECL|member|CR31
DECL|member|CR32
DECL|member|CR33
DECL|member|CR34
DECL|member|CR36
DECL|member|CR3A
DECL|member|CR3B
DECL|member|CR3C
r_int
r_char
id|CR31
comma
id|CR32
comma
id|CR33
comma
id|CR34
comma
id|CR36
comma
id|CR3A
comma
id|CR3B
comma
id|CR3C
suffix:semicolon
DECL|member|CR40
DECL|member|CR41
DECL|member|CR42
DECL|member|CR43
DECL|member|CR45
r_int
r_char
id|CR40
comma
id|CR41
comma
id|CR42
comma
id|CR43
comma
id|CR45
suffix:semicolon
DECL|member|CR50
DECL|member|CR51
DECL|member|CR53
DECL|member|CR55
DECL|member|CR58
DECL|member|CR5B
DECL|member|CR5D
DECL|member|CR5E
r_int
r_char
id|CR50
comma
id|CR51
comma
id|CR53
comma
id|CR55
comma
id|CR58
comma
id|CR5B
comma
id|CR5D
comma
id|CR5E
suffix:semicolon
DECL|member|CR60
DECL|member|CR63
DECL|member|CR65
DECL|member|CR66
DECL|member|CR67
DECL|member|CR68
DECL|member|CR69
DECL|member|CR6D
DECL|member|CR6F
r_int
r_char
id|CR60
comma
id|CR63
comma
id|CR65
comma
id|CR66
comma
id|CR67
comma
id|CR68
comma
id|CR69
comma
id|CR6D
comma
id|CR6F
suffix:semicolon
DECL|member|CR86
DECL|member|CR88
r_int
r_char
id|CR86
comma
id|CR88
suffix:semicolon
DECL|member|CR90
DECL|member|CR91
DECL|member|CRB0
r_int
r_char
id|CR90
comma
id|CR91
comma
id|CRB0
suffix:semicolon
DECL|member|STREAMS
r_int
r_int
id|STREAMS
(braket
l_int|22
)braket
suffix:semicolon
multiline_comment|/* yuck, streams regs */
DECL|member|MMPR0
DECL|member|MMPR1
DECL|member|MMPR2
DECL|member|MMPR3
r_int
r_int
id|MMPR0
comma
id|MMPR1
comma
id|MMPR2
comma
id|MMPR3
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|BCI_BD_BW_DISABLE
mdefine_line|#define BCI_BD_BW_DISABLE            0x10000000
DECL|macro|BCI_BD_SET_BPP
mdefine_line|#define BCI_BD_SET_BPP(bd, bpp)      ((bd) |= (((bpp) &amp; 0xFF) &lt;&lt; 16))
DECL|macro|BCI_BD_SET_STRIDE
mdefine_line|#define BCI_BD_SET_STRIDE(bd, st)    ((bd) |= ((st) &amp; 0xFFFF))
multiline_comment|/* IO functions */
DECL|macro|vga_in8
mdefine_line|#define  vga_in8(addr)         (inb (addr))
DECL|macro|vga_in16
mdefine_line|#define vga_in16(addr)         (inw (addr))
DECL|macro|vga_in32
mdefine_line|#define vga_in32(addr)         (inl (addr))
DECL|macro|vga_out8
mdefine_line|#define  vga_out8(addr,val)    (outb ((val), (addr)))
DECL|macro|vga_out16
mdefine_line|#define vga_out16(addr,val)    (outw ((val), (addr)))
DECL|macro|vga_out32
mdefine_line|#define vga_out32(addr,val)    (outl ((val), (addr)))
DECL|macro|savage_in16
mdefine_line|#define savage_in16(addr)      readw(par-&gt;mmio.vbase + (addr))
DECL|macro|savage_in32
mdefine_line|#define savage_in32(addr)      readl(par-&gt;mmio.vbase + (addr))
DECL|macro|savage_out16
mdefine_line|#define savage_out16(addr,val) writew((val), par-&gt;mmio.vbase + (addr))
DECL|macro|savage_out32
mdefine_line|#define savage_out32(addr,val) writel((val), par-&gt;mmio.vbase + (addr))
DECL|function|VGArCR
r_static
r_inline
id|u8
id|VGArCR
(paren
id|u8
id|index
)paren
(brace
id|outb
(paren
id|index
comma
l_int|0x3d4
)paren
suffix:semicolon
r_return
id|inb
(paren
l_int|0x3d5
)paren
suffix:semicolon
)brace
DECL|function|VGArGR
r_static
r_inline
id|u8
id|VGArGR
(paren
id|u8
id|index
)paren
(brace
id|outb
(paren
id|index
comma
l_int|0x3ce
)paren
suffix:semicolon
r_return
id|inb
(paren
l_int|0x3cf
)paren
suffix:semicolon
)brace
DECL|function|VGArSEQ
r_static
r_inline
id|u8
id|VGArSEQ
(paren
id|u8
id|index
)paren
(brace
id|outb
(paren
id|index
comma
l_int|0x3c4
)paren
suffix:semicolon
r_return
id|inb
(paren
l_int|0x3c5
)paren
suffix:semicolon
)brace
DECL|macro|VGAwCR
mdefine_line|#define VGAwCR(index, val) &bslash;&n;do {                       &bslash;&n;  vga_out8 (0x3d4, index); &bslash;&n;  vga_out8 (0x3d5, val);   &bslash;&n;} while (0)
DECL|macro|VGAwGR
mdefine_line|#define VGAwGR(index, val) &bslash;&n;do {                       &bslash;&n;  vga_out8 (0x3ce, index); &bslash;&n;  vga_out8 (0x3cf, val);   &bslash;&n;} while (0)
DECL|macro|VGAwSEQ
mdefine_line|#define VGAwSEQ(index, val) &bslash;&n;do {                        &bslash;&n;  vga_out8 (0x3c4, index);  &bslash;&n;  vga_out8 (0x3c5, val);    &bslash;&n;} while (0)
DECL|macro|VGAenablePalette
mdefine_line|#define VGAenablePalette() &bslash;&n;do {                       &bslash;&n;  u8 tmp;                  &bslash;&n;                           &bslash;&n;  tmp = vga_in8 (0x3da);   &bslash;&n;  vga_out8 (0x3c0, 0x00);  &bslash;&n;  paletteEnabled = 1;      &bslash;&n;} while (0)
DECL|macro|VGAdisablePalette
mdefine_line|#define VGAdisablePalette() &bslash;&n;do {                        &bslash;&n;  u8 tmp;                   &bslash;&n;                            &bslash;&n;  tmp = vga_in8 (0x3da);    &bslash;&n;  vga_out8 (0x3c0, 0x20);   &bslash;&n;  paletteEnabled = 0;       &bslash;&n;} while (0)
DECL|macro|VGAwATTR
mdefine_line|#define VGAwATTR(index, value) &bslash;&n;do {                           &bslash;&n;  u8 tmp;                      &bslash;&n;                               &bslash;&n;  if (paletteEnabled)          &bslash;&n;    index &amp;= ~0x20;            &bslash;&n;  else                         &bslash;&n;    index |= 0x20;             &bslash;&n;                               &bslash;&n;  tmp = vga_in8 (0x3da);       &bslash;&n;  vga_out8 (0x3c0, index);     &bslash;&n;  vga_out8 (0x3c0, value);     &bslash;&n;} while (0)
DECL|macro|VGAwMISC
mdefine_line|#define VGAwMISC(value)    &bslash;&n;do {                       &bslash;&n;  vga_out8 (0x3c2, value); &bslash;&n;} while (0)
macro_line|#ifndef CONFIG_FB_SAVAGE_ACCEL
DECL|macro|savagefb_set_clip
mdefine_line|#define savagefb_set_clip(x)
macro_line|#endif
DECL|macro|VerticalRetraceWait
mdefine_line|#define VerticalRetraceWait() &bslash;&n;{ &bslash;&n;&t;vga_out8 (0x3d4, 0x17); &bslash;&n;&t;if (vga_in8 (0x3d5) &amp; 0x80) { &bslash;&n;&t;&t;while ((vga_in8(0x3da) &amp; 0x08) == 0x08) ; &bslash;&n;&t;&t;while ((vga_in8(0x3da) &amp; 0x08) == 0x00) ; &bslash;&n;&t;} &bslash;&n;}
r_extern
r_int
id|savagefb_probe_i2c_connector
c_func
(paren
r_struct
id|savagefb_par
op_star
id|par
comma
id|u8
op_star
op_star
id|out_edid
)paren
suffix:semicolon
r_extern
r_void
id|savagefb_create_i2c_busses
c_func
(paren
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
r_extern
r_void
id|savagefb_delete_i2c_busses
c_func
(paren
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
r_extern
r_int
id|savagefb_sync
c_func
(paren
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
r_extern
r_void
id|savagefb_copyarea
c_func
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_const
r_struct
id|fb_copyarea
op_star
id|region
)paren
suffix:semicolon
r_extern
r_void
id|savagefb_fillrect
c_func
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_const
r_struct
id|fb_fillrect
op_star
id|rect
)paren
suffix:semicolon
r_extern
r_void
id|savagefb_imageblit
c_func
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_const
r_struct
id|fb_image
op_star
id|image
)paren
suffix:semicolon
macro_line|#endif /* __SAVAGEFB_H__ */
eof
