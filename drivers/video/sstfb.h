multiline_comment|/*&n; * linux/drivers/video/sstfb.h -- voodoo graphics frame buffer&n; *&n; *     Copyright (c) 2000,2001 Ghozlane Toumi &lt;gtoumi@messel.emse.fr&gt;&n; *&n; *     Created 28 Aug 2001 by Ghozlane Toumi&n; *&n; * $Id: sstfb.h,v 1.1.4.1 2001/08/29 01:30:38 ghoz Exp $&n; */
macro_line|#ifndef _SSTFB_H_
DECL|macro|_SSTFB_H_
mdefine_line|#define _SSTFB_H_
multiline_comment|/*&n; *&n; *  Debug Stuff&n; *&n; */
macro_line|#ifdef SST_DEBUG
DECL|macro|dprintk
macro_line|#  define dprintk(X...)&t;printk(KERN_DEBUG &quot;sstfb: &quot; X)
macro_line|#else
DECL|macro|dprintk
macro_line|#  define dprintk(X...)
DECL|macro|SST_DEBUG_REG
macro_line|#  undef SST_DEBUG_REG
DECL|macro|SST_DEBUG_FUNC
macro_line|#  undef SST_DEBUG_FUNC
DECL|macro|SST_DEBUG_VAR
macro_line|#  undef SST_DEBUG_VAR
DECL|macro|SST_DEBUG_IOCTL
macro_line|#  undef SST_DEBUG_IOCTL
macro_line|#endif
macro_line|#if (SST_DEBUG_REG &gt; 0)
DECL|macro|r_dprintk
macro_line|#  define r_dprintk(X...)&t;dprintk(X)
macro_line|#else
DECL|macro|r_dprintk
macro_line|#  define r_dprintk(X...)
macro_line|#endif
macro_line|#if (SST_DEBUG_REG &gt; 1)
DECL|macro|r_ddprintk
macro_line|#  define r_ddprintk(X...)&t;dprintk(&quot; &quot; X)
macro_line|#else
DECL|macro|r_ddprintk
macro_line|#  define r_ddprintk(X...)
macro_line|#endif
macro_line|#if (SST_DEBUG_FUNC &gt; 0)
DECL|macro|f_dprintk
macro_line|#  define f_dprintk(X...)&t;dprintk(X)
macro_line|#else
DECL|macro|f_dprintk
macro_line|#  define f_dprintk(X...)
macro_line|#endif
macro_line|#if (SST_DEBUG_FUNC &gt; 1)
DECL|macro|f_ddprintk
macro_line|#  define f_ddprintk(X...)&t;dprintk(&quot; &quot; X)
macro_line|#else
DECL|macro|f_ddprintk
macro_line|#  define f_ddprintk(X...)
macro_line|#endif
macro_line|#if (SST_DEBUG_FUNC &gt; 2)
DECL|macro|f_dddprintk
macro_line|#  define f_dddprintk(X...)&t;dprintk(&quot; &quot; X)
macro_line|#else
DECL|macro|f_dddprintk
macro_line|#  define f_dddprintk(X...)
macro_line|#endif
macro_line|#if (SST_DEBUG_VAR &gt; 0)
DECL|macro|v_dprintk
macro_line|#  define v_dprintk(X...)&t;dprintk(X)
DECL|macro|print_var
macro_line|#  define print_var(V, X...)&t;&bslash;&n;   {&t;&t;&t;&t;&bslash;&n;     dprintk(X);&t;&t;&bslash;&n;     printk(&quot; :&bslash;n&quot;);&t;&t;&bslash;&n;     sst_dbg_print_var(V);&t;&bslash;&n;   }
macro_line|#else
DECL|macro|v_dprintk
macro_line|#  define v_dprintk(X...)
DECL|macro|print_var
macro_line|#  define print_var(X,Y...)
macro_line|#endif
DECL|macro|eprintk
mdefine_line|#define eprintk(X...)&t;printk(KERN_ERR &quot;sstfb: &quot; X)
DECL|macro|iprintk
mdefine_line|#define iprintk(X...)&t;printk(KERN_INFO &quot;sstfb: &quot; X)
DECL|macro|wprintk
mdefine_line|#define wprintk(X...)&t;printk(KERN_WARNING &quot;sstfb: &quot; X)
DECL|macro|BIT
mdefine_line|#define BIT(x)&t;&t;(1ul &lt;&lt; (x))
DECL|macro|PS2KHZ
mdefine_line|#define PS2KHZ(a)&t;(1000000000UL/(a))&t;/* picoseconds to KHz */
DECL|macro|KHZ2PS
mdefine_line|#define KHZ2PS(a)&t;(1000000000UL/(a))
macro_line|#ifndef ABS
DECL|macro|ABS
macro_line|# define ABS(x)&t;&t;(((x)&lt;0)?-(x):(x))
macro_line|#endif
singleline_comment|//void Dump_regs(void);
multiline_comment|/*&n; *&n; *  Const&n; *&n; */
multiline_comment|/* pci stuff */
DECL|macro|PCI_INIT_ENABLE
mdefine_line|#define PCI_INIT_ENABLE&t;&t;0x40
DECL|macro|PCI_EN_INIT_WR
macro_line|#  define PCI_EN_INIT_WR&t;  BIT(0)
DECL|macro|PCI_EN_FIFO_WR
macro_line|#  define PCI_EN_FIFO_WR&t;  BIT(1)
DECL|macro|PCI_REMAP_DAC
macro_line|#  define PCI_REMAP_DAC&t;&t;  BIT(2)
DECL|macro|PCI_VCLK_ENABLE
mdefine_line|#define PCI_VCLK_ENABLE&t;&t;0xc0&t;/* enable video */
DECL|macro|PCI_VCLK_DISABLE
mdefine_line|#define PCI_VCLK_DISABLE&t;0xe0
multiline_comment|/* register offsets from memBaseAddr */
DECL|macro|STATUS
mdefine_line|#define STATUS&t;&t;&t;0x0000
DECL|macro|STATUS_FBI_BUSY
macro_line|#  define STATUS_FBI_BUSY&t;  BIT(7)
DECL|macro|FBZMODE
mdefine_line|#define FBZMODE&t;&t;&t;0x0110
DECL|macro|EN_CLIPPING
macro_line|#  define EN_CLIPPING&t;&t;  BIT(0)&t;/* enable clipping */
DECL|macro|EN_RGB_WRITE
macro_line|#  define EN_RGB_WRITE&t;&t;  BIT(9)&t;/* enable writes to rgb area */
DECL|macro|EN_ALPHA_WRITE
macro_line|#  define EN_ALPHA_WRITE&t;  BIT(10)
DECL|macro|ENGINE_INVERT_Y
macro_line|#  define ENGINE_INVERT_Y&t;  BIT(17)&t;/* invert Y origin (pipe) */
DECL|macro|LFBMODE
mdefine_line|#define LFBMODE&t;&t;&t;0x0114
DECL|macro|LFB_565
macro_line|#  define LFB_565&t;&t;  0&t;&t;/* bits 3:0 .16 bits RGB */
DECL|macro|LFB_888
macro_line|#  define LFB_888&t;&t;  4&t;&t;/* 24 bits RGB */
DECL|macro|LFB_8888
macro_line|#  define LFB_8888&t;&t;  5&t;&t;/* 32 bits ARGB */
DECL|macro|WR_BUFF_FRONT
macro_line|#  define WR_BUFF_FRONT&t;&t;  0&t;&t;/* write buf select (front) */
DECL|macro|WR_BUFF_BACK
macro_line|#  define WR_BUFF_BACK&t;&t;  (1 &lt;&lt; 4)&t;/* back */
DECL|macro|RD_BUFF_FRONT
macro_line|#  define RD_BUFF_FRONT&t;&t;  0&t;&t;/* read buff select (front) */
DECL|macro|RD_BUFF_BACK
macro_line|#  define RD_BUFF_BACK&t;&t;  (1 &lt;&lt; 6)&t;/* back */
DECL|macro|EN_PXL_PIPELINE
macro_line|#  define EN_PXL_PIPELINE&t;  BIT(8)&t;/* pixel pipeline (clip..)*/
DECL|macro|LFB_INVERT_Y
macro_line|#  define LFB_INVERT_Y&t;&t;  BIT(13)&t;/* invert Y origin (LFB) */
DECL|macro|CLIP_LEFT_RIGHT
mdefine_line|#define CLIP_LEFT_RIGHT&t;&t;0x0118
DECL|macro|CLIP_LOWY_HIGHY
mdefine_line|#define CLIP_LOWY_HIGHY&t;&t;0x011c
DECL|macro|NOPCMD
mdefine_line|#define NOPCMD&t;&t;&t;0x0120
DECL|macro|FASTFILLCMD
mdefine_line|#define FASTFILLCMD&t;&t;0x0124
DECL|macro|SWAPBUFFCMD
mdefine_line|#define SWAPBUFFCMD&t;&t;0x0128
DECL|macro|FBIINIT4
mdefine_line|#define FBIINIT4&t;&t;0x0200&t;&t;/* misc controls */
DECL|macro|FAST_PCI_READS
macro_line|#  define FAST_PCI_READS&t;  0&t;&t;/* 1 waitstate */
DECL|macro|SLOW_PCI_READS
macro_line|#  define SLOW_PCI_READS&t;  BIT(0)&t;/* 2 ws */
DECL|macro|LFB_READ_AHEAD
macro_line|#  define LFB_READ_AHEAD&t;  BIT(1)
DECL|macro|BACKPORCH
mdefine_line|#define BACKPORCH&t;&t;0x0208
DECL|macro|VIDEODIMENSIONS
mdefine_line|#define VIDEODIMENSIONS&t;&t;0x020c
DECL|macro|FBIINIT0
mdefine_line|#define FBIINIT0&t;&t;0x0210&t;&t;/* misc+fifo  controls */
DECL|macro|EN_VGA_PASSTHROUGH
macro_line|#  define EN_VGA_PASSTHROUGH&t;  BIT(0)
DECL|macro|FBI_RESET
macro_line|#  define FBI_RESET&t;&t;  BIT(1)
DECL|macro|FIFO_RESET
macro_line|#  define FIFO_RESET&t;&t;  BIT(2)
DECL|macro|FBIINIT1
mdefine_line|#define FBIINIT1&t;&t;0x0214&t;&t;/* PCI + video controls */
DECL|macro|VIDEO_MASK
macro_line|#  define VIDEO_MASK&t;&t;  0x8080010f&t;/* masks video related bits V1+V2*/
DECL|macro|FAST_PCI_WRITES
macro_line|#  define FAST_PCI_WRITES&t;  0&t;&t;/* 0 ws */
DECL|macro|SLOW_PCI_WRITES
macro_line|#  define SLOW_PCI_WRITES&t;  BIT(1)&t;/* 1 ws */
DECL|macro|EN_LFB_READ
macro_line|#  define EN_LFB_READ&t;&t;  BIT(3)
DECL|macro|TILES_IN_X_SHIFT
macro_line|#  define TILES_IN_X_SHIFT&t;  4
DECL|macro|VIDEO_RESET
macro_line|#  define VIDEO_RESET&t;&t;  BIT(8)
DECL|macro|EN_BLANKING
macro_line|#  define EN_BLANKING&t;&t;  BIT(12)
DECL|macro|EN_DATA_OE
macro_line|#  define EN_DATA_OE&t;&t;  BIT(13)
DECL|macro|EN_BLANK_OE
macro_line|#  define EN_BLANK_OE&t;&t;  BIT(14)
DECL|macro|EN_HVSYNC_OE
macro_line|#  define EN_HVSYNC_OE&t;&t;  BIT(15)
DECL|macro|EN_DCLK_OE
macro_line|#  define EN_DCLK_OE&t;&t;  BIT(16)
DECL|macro|SEL_INPUT_VCLK_2X
macro_line|#  define SEL_INPUT_VCLK_2X&t;  0&t;&t;/* bit 17 */
DECL|macro|SEL_INPUT_VCLK_SLAVE
macro_line|#  define SEL_INPUT_VCLK_SLAVE&t;  BIT(17)
DECL|macro|SEL_SOURCE_VCLK_SLAVE
macro_line|#  define SEL_SOURCE_VCLK_SLAVE&t;  0&t;&t;/* bits 21:20 */
DECL|macro|SEL_SOURCE_VCLK_2X_DIV2
macro_line|#  define SEL_SOURCE_VCLK_2X_DIV2 (0x01 &lt;&lt; 20)
DECL|macro|SEL_SOURCE_VCLK_2X_SEL
macro_line|#  define SEL_SOURCE_VCLK_2X_SEL  (0x02 &lt;&lt; 20)
DECL|macro|EN_24BPP
macro_line|#  define EN_24BPP&t;&t;  BIT(22)
DECL|macro|TILES_IN_X_MSB_SHIFT
macro_line|#  define TILES_IN_X_MSB_SHIFT&t;  24&t;&t;/* v2 */
DECL|macro|VCLK_2X_SEL_DEL_SHIFT
macro_line|#  define VCLK_2X_SEL_DEL_SHIFT&t;  27&t;&t;/* vclk out delay 0,4,6,8ns */
DECL|macro|VCLK_DEL_SHIFT
macro_line|#  define VCLK_DEL_SHIFT&t;  29&t;&t;/* vclk in delay */
DECL|macro|FBIINIT2
mdefine_line|#define FBIINIT2&t;&t;0x0218&t;&t;/* Dram controls */
DECL|macro|EN_FAST_RAS_READ
macro_line|#  define EN_FAST_RAS_READ&t;  BIT(5)
DECL|macro|EN_DRAM_OE
macro_line|#  define EN_DRAM_OE&t;&t;  BIT(6)
DECL|macro|EN_FAST_RD_AHEAD_WR
macro_line|#  define EN_FAST_RD_AHEAD_WR&t;  BIT(7)
DECL|macro|VIDEO_OFFSET_SHIFT
macro_line|#  define VIDEO_OFFSET_SHIFT&t;  11&t;&t;/* unit: #rows tile 64x16/2 */
DECL|macro|SWAP_DACVSYNC
macro_line|#  define SWAP_DACVSYNC&t;&t;  0
DECL|macro|SWAP_DACDATA0
macro_line|#  define SWAP_DACDATA0&t;&t;  (1 &lt;&lt; 9)
DECL|macro|SWAP_FIFO_STALL
macro_line|#  define SWAP_FIFO_STALL&t;  (2 &lt;&lt; 9)
DECL|macro|EN_RD_AHEAD_FIFO
macro_line|#  define EN_RD_AHEAD_FIFO&t;  BIT(21)
DECL|macro|EN_DRAM_REFRESH
macro_line|#  define EN_DRAM_REFRESH&t;  BIT(22)
DECL|macro|DRAM_REFRESH_16
macro_line|#  define DRAM_REFRESH_16&t;  (0x30 &lt;&lt; 23)&t;/* dram 16 ms */
DECL|macro|DAC_READ
mdefine_line|#define DAC_READ&t;&t;FBIINIT2&t;/* in remap mode */
DECL|macro|FBIINIT3
mdefine_line|#define FBIINIT3&t;&t;0x021c&t;&t;/* fbi controls */
DECL|macro|DISABLE_TEXTURE
macro_line|#  define DISABLE_TEXTURE&t;  BIT(6)
DECL|macro|Y_SWAP_ORIGIN_SHIFT
macro_line|#  define Y_SWAP_ORIGIN_SHIFT&t;  22&t;&t;/* Y swap substraction value */
DECL|macro|HSYNC
mdefine_line|#define HSYNC&t;&t;&t;0x0220
DECL|macro|VSYNC
mdefine_line|#define VSYNC&t;&t;&t;0x0224
DECL|macro|DAC_DATA
mdefine_line|#define DAC_DATA&t;&t;0x022c
DECL|macro|DAC_READ_CMD
macro_line|#  define DAC_READ_CMD&t;&t;  BIT(11)&t;/* set read dacreg mode */
DECL|macro|FBIINIT5
mdefine_line|#define FBIINIT5&t;&t;0x0244&t;&t;/* v2 specific */
DECL|macro|FBIINIT6
mdefine_line|#define FBIINIT6&t;&t;0x0248&t;&t;/* v2 specific */
DECL|macro|FBIINIT7
mdefine_line|#define FBIINIT7&t;&t;0x024c&t;&t;/* v2 specific */
DECL|macro|TILES_IN_X_LSB_SHIFT
macro_line|#  define TILES_IN_X_LSB_SHIFT&t;  30&t;&t;/* v2 */
multiline_comment|/* Dac Registers */
DECL|macro|DACREG_WMA
mdefine_line|#define DACREG_WMA&t;&t;0x0&t;/* pixel write mode address */
DECL|macro|DACREG_LUT
mdefine_line|#define DACREG_LUT&t;&t;0x01&t;/* color value */
DECL|macro|DACREG_RMR
mdefine_line|#define DACREG_RMR&t;&t;0x02&t;/* pixel mask */
DECL|macro|DACREG_RMA
mdefine_line|#define DACREG_RMA&t;&t;0x03&t;/* pixel read mode address */
multiline_comment|/*Dac registers in indexed mode (TI, ATT dacs) */
DECL|macro|DACREG_ADDR_I
mdefine_line|#define DACREG_ADDR_I&t;&t;DACREG_WMA
DECL|macro|DACREG_DATA_I
mdefine_line|#define DACREG_DATA_I&t;&t;DACREG_RMR
DECL|macro|DACREG_RMR_I
mdefine_line|#define DACREG_RMR_I&t;&t;0x00
DECL|macro|DACREG_CR0_I
mdefine_line|#define DACREG_CR0_I&t;&t;0x01
DECL|macro|DACREG_CR0_EN_INDEXED
macro_line|#  define DACREG_CR0_EN_INDEXED&t;  BIT(0)&t;/* enable indexec mode */
DECL|macro|DACREG_CR0_8BIT
macro_line|#  define DACREG_CR0_8BIT&t;  BIT(1)&t;/* set dac to 8 bits/read */
DECL|macro|DACREG_CR0_PWDOWN
macro_line|#  define DACREG_CR0_PWDOWN&t;  BIT(3)&t;/* powerdown dac */
DECL|macro|DACREG_CR0_16BPP
macro_line|#  define DACREG_CR0_16BPP&t;  0x30&t;&t;/* mode 3 */
DECL|macro|DACREG_CR0_24BPP
macro_line|#  define DACREG_CR0_24BPP&t;  0x50&t;&t;/* mode 5 */
DECL|macro|DACREG_CR1_I
mdefine_line|#define&t;DACREG_CR1_I&t;&t;0x05
DECL|macro|DACREG_CC_I
mdefine_line|#define DACREG_CC_I&t;&t;0x06
DECL|macro|DACREG_CC_CLKA
macro_line|#  define DACREG_CC_CLKA&t;  BIT(7)&t;/* clk A controled by regs */
DECL|macro|DACREG_CC_CLKA_C
macro_line|#  define DACREG_CC_CLKA_C&t;  (2&lt;&lt;4)&t;/* clk A uses reg C */
DECL|macro|DACREG_CC_CLKB
macro_line|#  define DACREG_CC_CLKB&t;  BIT(3)&t;/* clk B controled by regs */
DECL|macro|DACREG_CC_CLKB_D
macro_line|#  define DACREG_CC_CLKB_D&t;  3&t;&t;/* clkB uses reg D */
DECL|macro|DACREG_AC0_I
mdefine_line|#define DACREG_AC0_I&t;&t;0x48&t;&t;/* clock A reg C */
DECL|macro|DACREG_AC1_I
mdefine_line|#define DACREG_AC1_I&t;&t;0x49
DECL|macro|DACREG_BD0_I
mdefine_line|#define DACREG_BD0_I&t;&t;0x6c&t;&t;/* clock B reg D */
DECL|macro|DACREG_BD1_I
mdefine_line|#define DACREG_BD1_I&t;&t;0x6d
multiline_comment|/* identification constants */
DECL|macro|DACREG_MIR_TI
mdefine_line|#define DACREG_MIR_TI&t;&t;0x97
DECL|macro|DACREG_DIR_TI
mdefine_line|#define DACREG_DIR_TI&t;&t;0x09
DECL|macro|DACREG_MIR_ATT
mdefine_line|#define DACREG_MIR_ATT&t;&t;0x84
DECL|macro|DACREG_DIR_ATT
mdefine_line|#define DACREG_DIR_ATT&t;&t;0x09
multiline_comment|/* ics dac specific registers*/
DECL|macro|DACREG_ICS_PLLWMA
mdefine_line|#define DACREG_ICS_PLLWMA&t;0x04&t;/* PLL write mode address */
DECL|macro|DACREG_ICS_PLLDATA
mdefine_line|#define DACREG_ICS_PLLDATA&t;0x05&t;/* PLL data /parameter */
DECL|macro|DACREG_ICS_CMD
mdefine_line|#define DACREG_ICS_CMD&t;&t;0x06&t;/* command */
DECL|macro|DACREG_ICS_CMD_16BPP
macro_line|#  define DACREG_ICS_CMD_16BPP&t;  0x50&t;/* ics color mode 6 (16bpp bypass)*/
DECL|macro|DACREG_ICS_CMD_24BPP
macro_line|#  define DACREG_ICS_CMD_24BPP&t;  0x70&t;/* ics color mode 7 (24bpp bypass)*/
DECL|macro|DACREG_ICS_CMD_PWDOWN
macro_line|#  define DACREG_ICS_CMD_PWDOWN BIT(0)&t;/* powerdown dac */
DECL|macro|DACREG_ICS_PLLRMA
mdefine_line|#define DACREG_ICS_PLLRMA&t;0x07&t;/* PLL read mode address */
multiline_comment|/*&n; * pll parameter register:&n; * indexed : write addr to PLLWMA, write data in PLLDATA.&n; * for reads use PLLRMA .&n; * 8 freq registers (0-7) for video clock (CLK0)&n; * 2 freq registers (a-b) for graphic clock (CLK1)&n; */
DECL|macro|DACREG_ICS_PLL_CLK0_1_INI
mdefine_line|#define DACREG_ICS_PLL_CLK0_1_INI 0x55&t;/* initial pll M value for freq f1  */
DECL|macro|DACREG_ICS_PLL_CLK0_7_INI
mdefine_line|#define DACREG_ICS_PLL_CLK0_7_INI 0x71&t;/* f7 */
DECL|macro|DACREG_ICS_PLL_CLK1_B_INI
mdefine_line|#define DACREG_ICS_PLL_CLK1_B_INI 0x79&t;/* fb */
DECL|macro|DACREG_ICS_PLL_CTRL
mdefine_line|#define DACREG_ICS_PLL_CTRL&t;0x0e
DECL|macro|DACREG_ICS_CLK0
macro_line|#  define DACREG_ICS_CLK0&t;  BIT(5)
DECL|macro|DACREG_ICS_CLK0_0
macro_line|#  define DACREG_ICS_CLK0_0&t;  0
DECL|macro|DACREG_ICS_CLK1_A
macro_line|#  define DACREG_ICS_CLK1_A&t;  0&t;/* bit4 */
multiline_comment|/* sst default init registers */
DECL|macro|FBIINIT0_DEFAULT
mdefine_line|#define FBIINIT0_DEFAULT EN_VGA_PASSTHROUGH
DECL|macro|FBIINIT1_DEFAULT
mdefine_line|#define FBIINIT1_DEFAULT &t;&bslash;&n;&t;(&t;&t;&t;&bslash;&n;&t;  FAST_PCI_WRITES&t;&bslash;&n;/*&t;  SLOW_PCI_WRITES*/&t;&bslash;&n;&t;| VIDEO_RESET&t;&t;&bslash;&n;&t;| 10 &lt;&lt; TILES_IN_X_SHIFT&bslash;&n;&t;| SEL_SOURCE_VCLK_2X_SEL&bslash;&n;&t;| EN_LFB_READ&t;&t;&bslash;&n;&t;)
DECL|macro|FBIINIT2_DEFAULT
mdefine_line|#define FBIINIT2_DEFAULT&t;&bslash;&n;&t;(&t;&t;&t;&bslash;&n;&t; SWAP_DACVSYNC&t;&t;&bslash;&n;&t;| EN_DRAM_OE&t;&t;&bslash;&n;&t;| DRAM_REFRESH_16&t;&bslash;&n;&t;| EN_DRAM_REFRESH&t;&bslash;&n;&t;| EN_FAST_RAS_READ&t;&bslash;&n;&t;| EN_RD_AHEAD_FIFO&t;&bslash;&n;&t;| EN_FAST_RD_AHEAD_WR&t;&bslash;&n;&t;)
DECL|macro|FBIINIT3_DEFAULT
mdefine_line|#define FBIINIT3_DEFAULT &t;&bslash;&n;&t;( DISABLE_TEXTURE )
DECL|macro|FBIINIT4_DEFAULT
mdefine_line|#define FBIINIT4_DEFAULT&t;&bslash;&n;&t;(&t;&t;&t;&bslash;&n;&t;  FAST_PCI_READS&t;&bslash;&n;/*&t;  SLOW_PCI_READS*/&t;&bslash;&n;&t;| LFB_READ_AHEAD&t;&bslash;&n;&t;)
multiline_comment|/* Careful with this one : writing back the data just read will trash the DAC&n;   reading some fields give logic value on pins, but setting this field will&n;   set the source signal driving the pin. conclusion : just use the default&n;   as a base before writing back .&n;*/
DECL|macro|FBIINIT6_DEFAULT
mdefine_line|#define FBIINIT6_DEFAULT&t;(0x0)
multiline_comment|/*&n; *&n; * Misc Const&n; *&n; */
multiline_comment|/* used to know witch clock to set */
DECL|macro|VID_CLOCK
mdefine_line|#define VID_CLOCK&t;0
DECL|macro|GFX_CLOCK
mdefine_line|#define GFX_CLOCK&t;1
multiline_comment|/* freq max */
DECL|macro|DAC_FREF
mdefine_line|#define DAC_FREF&t;14318&t;/* DAC reference freq (Khz) */
DECL|macro|VCO_MAX
mdefine_line|#define VCO_MAX&t;&t;260000
multiline_comment|/*&n; *&n; *  Declarations&n; *&n; */
DECL|struct|pll_timing
r_struct
id|pll_timing
(brace
DECL|member|m
id|u8
id|m
suffix:semicolon
DECL|member|n
id|u8
id|n
suffix:semicolon
DECL|member|p
id|u8
id|p
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|dac_switch
r_struct
id|dac_switch
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|detect
r_int
(paren
op_star
id|detect
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|set_pll
r_int
(paren
op_star
id|set_pll
)paren
(paren
r_const
r_struct
id|pll_timing
op_star
id|t
comma
r_const
r_int
id|clock
)paren
suffix:semicolon
DECL|member|set_vidmod
r_void
(paren
op_star
id|set_vidmod
)paren
(paren
r_const
r_int
id|bpp
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sst_spec
r_struct
id|sst_spec
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|default_gfx_clock
r_int
id|default_gfx_clock
suffix:semicolon
multiline_comment|/* 50000 for voodoo1, 75000 for voodoo2 */
DECL|member|max_gfxclk
r_int
id|max_gfxclk
suffix:semicolon
multiline_comment|/* ! in Mhz ie 60 for voodoo 1 */
)brace
suffix:semicolon
DECL|struct|sstfb_par
r_struct
id|sstfb_par
(brace
DECL|member|bpp
r_int
r_int
id|bpp
suffix:semicolon
DECL|member|xDim
r_int
r_int
id|xDim
suffix:semicolon
multiline_comment|/* xres */
DECL|member|hSyncOn
r_int
r_int
id|hSyncOn
suffix:semicolon
multiline_comment|/* hsync_len */
DECL|member|hSyncOff
r_int
r_int
id|hSyncOff
suffix:semicolon
multiline_comment|/* left_margin + xres + right_margin */
DECL|member|hBackPorch
r_int
r_int
id|hBackPorch
suffix:semicolon
multiline_comment|/* left_margin */
DECL|member|yDim
r_int
r_int
id|yDim
suffix:semicolon
DECL|member|vSyncOn
r_int
r_int
id|vSyncOn
suffix:semicolon
DECL|member|vSyncOff
r_int
r_int
id|vSyncOff
suffix:semicolon
DECL|member|vBackPorch
r_int
r_int
id|vBackPorch
suffix:semicolon
DECL|member|freq
r_int
r_int
id|freq
suffix:semicolon
multiline_comment|/* freq in picoseconds */
DECL|member|tiles_in_X
r_int
r_int
id|tiles_in_X
suffix:semicolon
multiline_comment|/* num of tiles in X res */
)brace
suffix:semicolon
DECL|struct|sstfb_info
r_struct
id|sstfb_info
(brace
DECL|member|info
r_struct
id|fb_info
id|info
suffix:semicolon
DECL|member|current_par
r_struct
id|sstfb_par
id|current_par
suffix:semicolon
DECL|member|dev
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
r_struct
(brace
DECL|member|base
r_int
r_int
id|base
suffix:semicolon
multiline_comment|/* physical */
DECL|member|vbase
r_int
r_int
id|vbase
suffix:semicolon
multiline_comment|/* virtual (CPU view) */
DECL|member|len
r_int
r_int
id|len
suffix:semicolon
DECL|member|video
)brace
id|video
suffix:semicolon
multiline_comment|/* fb memory info */
r_struct
(brace
DECL|member|base
r_int
r_int
id|base
suffix:semicolon
DECL|member|vbase
r_int
r_int
id|vbase
suffix:semicolon
DECL|member|mmio
)brace
id|mmio
suffix:semicolon
multiline_comment|/* registers memory info */
DECL|member|dac_sw
r_struct
id|dac_switch
op_star
id|dac_sw
suffix:semicolon
multiline_comment|/* dac specific functions */
DECL|member|spec
r_struct
id|sst_spec
op_star
id|spec
suffix:semicolon
DECL|member|is_voodoo2
r_int
id|is_voodoo2
suffix:semicolon
DECL|member|revision
id|u8
id|revision
suffix:semicolon
multiline_comment|/* status */
DECL|member|configured
r_int
id|configured
suffix:semicolon
multiline_comment|/*&t;int&t;indexed_mode;&n;&t;int&t;vgapass;&n;&t;int&t;clipping; */
DECL|member|gfx_clock
r_int
id|gfx_clock
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* _SSTFB_H_ */
eof
