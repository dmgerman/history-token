multiline_comment|/* drivers/video/s1d3xxxfb.h&n; *&n; * (c) 2004 Simtec Electronics&n; * (c) 2005 Thibaut VARENE &lt;varenet@parisc-linux.org&gt;&n; *&n; * Header file for Epson S1D13XXX driver code&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License. See the file COPYING in the main directory of this archive for&n; * more details.&n; */
macro_line|#ifndef&t;S1D13XXXFB_H
DECL|macro|S1D13XXXFB_H
mdefine_line|#define&t;S1D13XXXFB_H
DECL|macro|S1D_PALETTE_SIZE
mdefine_line|#define S1D_PALETTE_SIZE&t;&t;256
DECL|macro|S1D_CHIP_REV
mdefine_line|#define S1D_CHIP_REV&t;&t;&t;7&t;/* expected chip revision number for s1d13806 */
DECL|macro|S1D_FBID
mdefine_line|#define S1D_FBID&t;&t;&t;&quot;S1D13806&quot;
DECL|macro|S1D_DEVICENAME
mdefine_line|#define S1D_DEVICENAME&t;&t;&t;&quot;s1d13806fb&quot;
multiline_comment|/* register definitions (tested on s1d13896) */
DECL|macro|S1DREG_REV_CODE
mdefine_line|#define S1DREG_REV_CODE&t;&t;&t;0x0000&t;/* Revision Code Register */
DECL|macro|S1DREG_MISC
mdefine_line|#define S1DREG_MISC&t;&t;&t;0x0001&t;/* Miscellaneous Register */
DECL|macro|S1DREG_GPIO_CNF0
mdefine_line|#define S1DREG_GPIO_CNF0&t;&t;0x0004&t;/* General IO Pins Configuration Register 0 */
DECL|macro|S1DREG_GPIO_CNF1
mdefine_line|#define S1DREG_GPIO_CNF1&t;&t;0x0005&t;/* General IO Pins Configuration Register 1 */
DECL|macro|S1DREG_GPIO_CTL0
mdefine_line|#define S1DREG_GPIO_CTL0&t;&t;0x0008&t;/* General IO Pins Control Register 0 */
DECL|macro|S1DREG_GPIO_CTL1
mdefine_line|#define S1DREG_GPIO_CTL1&t;&t;0x0009&t;/* General IO Pins Control Register 1 */
DECL|macro|S1DREG_CNF_STATUS
mdefine_line|#define S1DREG_CNF_STATUS&t;&t;0x000C&t;/* Configuration Status Readback Register */
DECL|macro|S1DREG_CLK_CNF
mdefine_line|#define S1DREG_CLK_CNF&t;&t;&t;0x0010&t;/* Memory Clock Configuration Register */
DECL|macro|S1DREG_LCD_CLK_CNF
mdefine_line|#define S1DREG_LCD_CLK_CNF&t;&t;0x0014&t;/* LCD Pixel Clock Configuration Register */
DECL|macro|S1DREG_CRT_CLK_CNF
mdefine_line|#define S1DREG_CRT_CLK_CNF&t;&t;0x0018&t;/* CRT/TV Pixel Clock Configuration Register */
DECL|macro|S1DREG_MPLUG_CLK_CNF
mdefine_line|#define S1DREG_MPLUG_CLK_CNF&t;&t;0x001C&t;/* MediaPlug Clock Configuration Register */
DECL|macro|S1DREG_CPU2MEM_WST_SEL
mdefine_line|#define S1DREG_CPU2MEM_WST_SEL&t;&t;0x001E&t;/* CPU To Memory Wait State Select Register */
DECL|macro|S1DREG_MEM_CNF
mdefine_line|#define S1DREG_MEM_CNF&t;&t;&t;0x0020&t;/* Memory Configuration Register */
DECL|macro|S1DREG_SDRAM_REF_RATE
mdefine_line|#define S1DREG_SDRAM_REF_RATE&t;&t;0x0021&t;/* SDRAM Refresh Rate Register */
DECL|macro|S1DREG_SDRAM_TC0
mdefine_line|#define S1DREG_SDRAM_TC0&t;&t;0x002A&t;/* SDRAM Timing Control Register 0 */
DECL|macro|S1DREG_SDRAM_TC1
mdefine_line|#define S1DREG_SDRAM_TC1&t;&t;0x002B&t;/* SDRAM Timing Control Register 1 */
DECL|macro|S1DREG_PANEL_TYPE
mdefine_line|#define S1DREG_PANEL_TYPE&t;&t;0x0030&t;/* Panel Type Register */
DECL|macro|S1DREG_MOD_RATE
mdefine_line|#define S1DREG_MOD_RATE&t;&t;&t;0x0031&t;/* MOD Rate Register */
DECL|macro|S1DREG_LCD_DISP_HWIDTH
mdefine_line|#define S1DREG_LCD_DISP_HWIDTH&t;&t;0x0032&t;/* LCD Horizontal Display Width Register: ((val)+1)*8)=pix/line */
DECL|macro|S1DREG_LCD_NDISP_HPER
mdefine_line|#define S1DREG_LCD_NDISP_HPER&t;&t;0x0034&t;/* LCD Horizontal Non-Display Period Register: ((val)+1)*8)=NDpix/line */
DECL|macro|S1DREG_TFT_FPLINE_START
mdefine_line|#define S1DREG_TFT_FPLINE_START&t;&t;0x0035&t;/* TFT FPLINE Start Position Register */
DECL|macro|S1DREG_TFT_FPLINE_PWIDTH
mdefine_line|#define S1DREG_TFT_FPLINE_PWIDTH&t;0x0036&t;/* TFT FPLINE Pulse Width Register. */
DECL|macro|S1DREG_LCD_DISP_VHEIGHT0
mdefine_line|#define S1DREG_LCD_DISP_VHEIGHT0&t;0x0038&t;/* LCD Vertical Display Height Register 0 */
DECL|macro|S1DREG_LCD_DISP_VHEIGHT1
mdefine_line|#define S1DREG_LCD_DISP_VHEIGHT1&t;0x0039&t;/* LCD Vertical Display Height Register 1 */
DECL|macro|S1DREG_LCD_NDISP_VPER
mdefine_line|#define S1DREG_LCD_NDISP_VPER&t;&t;0x003A&t;/* LCD Vertical Non-Display Period Register: (val)+1=NDlines */
DECL|macro|S1DREG_TFT_FPFRAME_START
mdefine_line|#define S1DREG_TFT_FPFRAME_START&t;0x003B&t;/* TFT FPFRAME Start Position Register */
DECL|macro|S1DREG_TFT_FPFRAME_PWIDTH
mdefine_line|#define S1DREG_TFT_FPFRAME_PWIDTH&t;0x003C&t;/* TFT FPFRAME Pulse Width Register */
DECL|macro|S1DREG_LCD_DISP_MODE
mdefine_line|#define S1DREG_LCD_DISP_MODE&t;&t;0x0040&t;/* LCD Display Mode Register */
DECL|macro|S1DREG_LCD_MISC
mdefine_line|#define S1DREG_LCD_MISC&t;&t;&t;0x0041&t;/* LCD Miscellaneous Register */
DECL|macro|S1DREG_LCD_DISP_START0
mdefine_line|#define S1DREG_LCD_DISP_START0&t;&t;0x0042&t;/* LCD Display Start Address Register 0 */
DECL|macro|S1DREG_LCD_DISP_START1
mdefine_line|#define S1DREG_LCD_DISP_START1&t;&t;0x0043&t;/* LCD Display Start Address Register 1 */
DECL|macro|S1DREG_LCD_DISP_START2
mdefine_line|#define S1DREG_LCD_DISP_START2&t;&t;0x0044&t;/* LCD Display Start Address Register 2 */
DECL|macro|S1DREG_LCD_MEM_OFF0
mdefine_line|#define S1DREG_LCD_MEM_OFF0&t;&t;0x0046&t;/* LCD Memory Address Offset Register 0 */
DECL|macro|S1DREG_LCD_MEM_OFF1
mdefine_line|#define S1DREG_LCD_MEM_OFF1&t;&t;0x0047&t;/* LCD Memory Address Offset Register 1 */
DECL|macro|S1DREG_LCD_PIX_PAN
mdefine_line|#define S1DREG_LCD_PIX_PAN&t;&t;0x0048&t;/* LCD Pixel Panning Register */
DECL|macro|S1DREG_LCD_DISP_FIFO_HTC
mdefine_line|#define S1DREG_LCD_DISP_FIFO_HTC&t;0x004A&t;/* LCD Display FIFO High Threshold Control Register */
DECL|macro|S1DREG_LCD_DISP_FIFO_LTC
mdefine_line|#define S1DREG_LCD_DISP_FIFO_LTC&t;0x004B&t;/* LCD Display FIFO Low Threshold Control Register */
DECL|macro|S1DREG_CRT_DISP_HWIDTH
mdefine_line|#define S1DREG_CRT_DISP_HWIDTH&t;&t;0x0050&t;/* CRT/TV Horizontal Display Width Register: ((val)+1)*8)=pix/line */
DECL|macro|S1DREG_CRT_NDISP_HPER
mdefine_line|#define S1DREG_CRT_NDISP_HPER&t;&t;0x0052&t;/* CRT/TV Horizontal Non-Display Period Register */
DECL|macro|S1DREG_CRT_HRTC_START
mdefine_line|#define S1DREG_CRT_HRTC_START&t;&t;0x0053&t;/* CRT/TV HRTC Start Position Register */
DECL|macro|S1DREG_CRT_HRTC_PWIDTH
mdefine_line|#define S1DREG_CRT_HRTC_PWIDTH&t;&t;0x0054&t;/* CRT/TV HRTC Pulse Width Register */
DECL|macro|S1DREG_CRT_DISP_VHEIGHT0
mdefine_line|#define S1DREG_CRT_DISP_VHEIGHT0&t;0x0056&t;/* CRT/TV Vertical Display Height Register 0 */
DECL|macro|S1DREG_CRT_DISP_VHEIGHT1
mdefine_line|#define S1DREG_CRT_DISP_VHEIGHT1&t;0x0057&t;/* CRT/TV Vertical Display Height Register 1 */
DECL|macro|S1DREG_CRT_NDISP_VPER
mdefine_line|#define S1DREG_CRT_NDISP_VPER&t;&t;0x0058&t;/* CRT/TV Vertical Non-Display Period Register */
DECL|macro|S1DREG_CRT_VRTC_START
mdefine_line|#define S1DREG_CRT_VRTC_START&t;&t;0x0059&t;/* CRT/TV VRTC Start Position Register */
DECL|macro|S1DREG_CRT_VRTC_PWIDTH
mdefine_line|#define S1DREG_CRT_VRTC_PWIDTH&t;&t;0x005A&t;/* CRT/TV VRTC Pulse Width Register */
DECL|macro|S1DREG_TV_OUT_CTL
mdefine_line|#define S1DREG_TV_OUT_CTL&t;&t;0x005B&t;/* TV Output Control Register */
DECL|macro|S1DREG_CRT_DISP_MODE
mdefine_line|#define S1DREG_CRT_DISP_MODE&t;&t;0x0060&t;/* CRT/TV Display Mode Register */
DECL|macro|S1DREG_CRT_DISP_START0
mdefine_line|#define S1DREG_CRT_DISP_START0&t;&t;0x0062&t;/* CRT/TV Display Start Address Register 0 */
DECL|macro|S1DREG_CRT_DISP_START1
mdefine_line|#define S1DREG_CRT_DISP_START1&t;&t;0x0063&t;/* CRT/TV Display Start Address Register 1 */
DECL|macro|S1DREG_CRT_DISP_START2
mdefine_line|#define S1DREG_CRT_DISP_START2&t;&t;0x0064&t;/* CRT/TV Display Start Address Register 2 */
DECL|macro|S1DREG_CRT_MEM_OFF0
mdefine_line|#define S1DREG_CRT_MEM_OFF0&t;&t;0x0066&t;/* CRT/TV Memory Address Offset Register 0 */
DECL|macro|S1DREG_CRT_MEM_OFF1
mdefine_line|#define S1DREG_CRT_MEM_OFF1&t;&t;0x0067&t;/* CRT/TV Memory Address Offset Register 1 */
DECL|macro|S1DREG_CRT_PIX_PAN
mdefine_line|#define S1DREG_CRT_PIX_PAN&t;&t;0x0068&t;/* CRT/TV Pixel Panning Register */
DECL|macro|S1DREG_CRT_DISP_FIFO_HTC
mdefine_line|#define S1DREG_CRT_DISP_FIFO_HTC&t;0x006A&t;/* CRT/TV Display FIFO High Threshold Control Register */
DECL|macro|S1DREG_CRT_DISP_FIFO_LTC
mdefine_line|#define S1DREG_CRT_DISP_FIFO_LTC&t;0x006B&t;/* CRT/TV Display FIFO Low Threshold Control Register */
DECL|macro|S1DREG_LCD_CUR_CTL
mdefine_line|#define S1DREG_LCD_CUR_CTL&t;&t;0x0070&t;/* LCD Ink/Cursor Control Register */
DECL|macro|S1DREG_LCD_CUR_START
mdefine_line|#define S1DREG_LCD_CUR_START&t;&t;0x0071&t;/* LCD Ink/Cursor Start Address Register */
DECL|macro|S1DREG_LCD_CUR_XPOS0
mdefine_line|#define S1DREG_LCD_CUR_XPOS0&t;&t;0x0072&t;/* LCD Cursor X Position Register 0 */
DECL|macro|S1DREG_LCD_CUR_XPOS1
mdefine_line|#define S1DREG_LCD_CUR_XPOS1&t;&t;0x0073&t;/* LCD Cursor X Position Register 1 */
DECL|macro|S1DREG_LCD_CUR_YPOS0
mdefine_line|#define S1DREG_LCD_CUR_YPOS0&t;&t;0x0074&t;/* LCD Cursor Y Position Register 0 */
DECL|macro|S1DREG_LCD_CUR_YPOS1
mdefine_line|#define S1DREG_LCD_CUR_YPOS1&t;&t;0x0075&t;/* LCD Cursor Y Position Register 1 */
DECL|macro|S1DREG_LCD_CUR_BCTL0
mdefine_line|#define S1DREG_LCD_CUR_BCTL0&t;&t;0x0076&t;/* LCD Ink/Cursor Blue Color 0 Register */
DECL|macro|S1DREG_LCD_CUR_GCTL0
mdefine_line|#define S1DREG_LCD_CUR_GCTL0&t;&t;0x0077&t;/* LCD Ink/Cursor Green Color 0 Register */
DECL|macro|S1DREG_LCD_CUR_RCTL0
mdefine_line|#define S1DREG_LCD_CUR_RCTL0&t;&t;0x0078&t;/* LCD Ink/Cursor Red Color 0 Register */
DECL|macro|S1DREG_LCD_CUR_BCTL1
mdefine_line|#define S1DREG_LCD_CUR_BCTL1&t;&t;0x007A&t;/* LCD Ink/Cursor Blue Color 1 Register */
DECL|macro|S1DREG_LCD_CUR_GCTL1
mdefine_line|#define S1DREG_LCD_CUR_GCTL1&t;&t;0x007B&t;/* LCD Ink/Cursor Green Color 1 Register */
DECL|macro|S1DREG_LCD_CUR_RCTL1
mdefine_line|#define S1DREG_LCD_CUR_RCTL1&t;&t;0x007C&t;/* LCD Ink/Cursor Red Color 1 Register */
DECL|macro|S1DREG_LCD_CUR_FIFO_HTC
mdefine_line|#define S1DREG_LCD_CUR_FIFO_HTC&t;&t;0x007E&t;/* LCD Ink/Cursor FIFO High Threshold Register */
DECL|macro|S1DREG_CRT_CUR_CTL
mdefine_line|#define S1DREG_CRT_CUR_CTL&t;&t;0x0080&t;/* CRT/TV Ink/Cursor Control Register */
DECL|macro|S1DREG_CRT_CUR_START
mdefine_line|#define S1DREG_CRT_CUR_START&t;&t;0x0081&t;/* CRT/TV Ink/Cursor Start Address Register */
DECL|macro|S1DREG_CRT_CUR_XPOS0
mdefine_line|#define S1DREG_CRT_CUR_XPOS0&t;&t;0x0082&t;/* CRT/TV Cursor X Position Register 0 */
DECL|macro|S1DREG_CRT_CUR_XPOS1
mdefine_line|#define S1DREG_CRT_CUR_XPOS1&t;&t;0x0083&t;/* CRT/TV Cursor X Position Register 1 */
DECL|macro|S1DREG_CRT_CUR_YPOS0
mdefine_line|#define S1DREG_CRT_CUR_YPOS0&t;&t;0x0084&t;/* CRT/TV Cursor Y Position Register 0 */
DECL|macro|S1DREG_CRT_CUR_YPOS1
mdefine_line|#define S1DREG_CRT_CUR_YPOS1&t;&t;0x0085&t;/* CRT/TV Cursor Y Position Register 1 */
DECL|macro|S1DREG_CRT_CUR_BCTL0
mdefine_line|#define S1DREG_CRT_CUR_BCTL0&t;&t;0x0086&t;/* CRT/TV Ink/Cursor Blue Color 0 Register */
DECL|macro|S1DREG_CRT_CUR_GCTL0
mdefine_line|#define S1DREG_CRT_CUR_GCTL0&t;&t;0x0087&t;/* CRT/TV Ink/Cursor Green Color 0 Register */
DECL|macro|S1DREG_CRT_CUR_RCTL0
mdefine_line|#define S1DREG_CRT_CUR_RCTL0&t;&t;0x0088&t;/* CRT/TV Ink/Cursor Red Color 0 Register */
DECL|macro|S1DREG_CRT_CUR_BCTL1
mdefine_line|#define S1DREG_CRT_CUR_BCTL1&t;&t;0x008A&t;/* CRT/TV Ink/Cursor Blue Color 1 Register */
DECL|macro|S1DREG_CRT_CUR_GCTL1
mdefine_line|#define S1DREG_CRT_CUR_GCTL1&t;&t;0x008B&t;/* CRT/TV Ink/Cursor Green Color 1 Register */
DECL|macro|S1DREG_CRT_CUR_RCTL1
mdefine_line|#define S1DREG_CRT_CUR_RCTL1&t;&t;0x008C&t;/* CRT/TV Ink/Cursor Red Color 1 Register */
DECL|macro|S1DREG_CRT_CUR_FIFO_HTC
mdefine_line|#define S1DREG_CRT_CUR_FIFO_HTC&t;&t;0x008E&t;/* CRT/TV Ink/Cursor FIFO High Threshold Register */
DECL|macro|S1DREG_BBLT_CTL0
mdefine_line|#define S1DREG_BBLT_CTL0&t;&t;0x0100&t;/* BitBLT Control Register 0 */
DECL|macro|S1DREG_BBLT_CTL1
mdefine_line|#define S1DREG_BBLT_CTL1&t;&t;0x0101&t;/* BitBLT Control Register 1 */
DECL|macro|S1DREG_BBLT_CC_EXP
mdefine_line|#define S1DREG_BBLT_CC_EXP&t;&t;0x0102&t;/* BitBLT Code/Color Expansion Register */
DECL|macro|S1DREG_BBLT_OP
mdefine_line|#define S1DREG_BBLT_OP&t;&t;&t;0x0103&t;/* BitBLT Operation Register */
DECL|macro|S1DREG_BBLT_SRC_START0
mdefine_line|#define S1DREG_BBLT_SRC_START0&t;&t;0x0104&t;/* BitBLT Source Start Address Register 0 */
DECL|macro|S1DREG_BBLT_SRC_START1
mdefine_line|#define S1DREG_BBLT_SRC_START1&t;&t;0x0105&t;/* BitBLT Source Start Address Register 1 */
DECL|macro|S1DREG_BBLT_SRC_START2
mdefine_line|#define S1DREG_BBLT_SRC_START2&t;&t;0x0106&t;/* BitBLT Source Start Address Register 2 */
DECL|macro|S1DREG_BBLT_DST_START0
mdefine_line|#define S1DREG_BBLT_DST_START0&t;&t;0x0108&t;/* BitBLT Destination Start Address Register 0 */
DECL|macro|S1DREG_BBLT_DST_START1
mdefine_line|#define S1DREG_BBLT_DST_START1&t;&t;0x0109&t;/* BitBLT Destination Start Address Register 1 */
DECL|macro|S1DREG_BBLT_DST_START2
mdefine_line|#define S1DREG_BBLT_DST_START2&t;&t;0x010A&t;/* BitBLT Destination Start Address Register 2 */
DECL|macro|S1DREG_BBLT_MEM_OFF0
mdefine_line|#define S1DREG_BBLT_MEM_OFF0&t;&t;0x010C&t;/* BitBLT Memory Address Offset Register 0 */
DECL|macro|S1DREG_BBLT_MEM_OFF1
mdefine_line|#define S1DREG_BBLT_MEM_OFF1&t;&t;0x010D&t;/* BitBLT Memory Address Offset Register 1 */
DECL|macro|S1DREG_BBLT_WIDTH0
mdefine_line|#define S1DREG_BBLT_WIDTH0&t;&t;0x0110&t;/* BitBLT Width Register 0 */
DECL|macro|S1DREG_BBLT_WIDTH1
mdefine_line|#define S1DREG_BBLT_WIDTH1&t;&t;0x0111&t;/* BitBLT Width Register 1 */
DECL|macro|S1DREG_BBLT_HEIGHT0
mdefine_line|#define S1DREG_BBLT_HEIGHT0&t;&t;0x0112&t;/* BitBLT Height Register 0 */
DECL|macro|S1DREG_BBLT_HEIGHT1
mdefine_line|#define S1DREG_BBLT_HEIGHT1&t;&t;0x0113&t;/* BitBLT Height Register 1 */
DECL|macro|S1DREG_BBLT_BGC0
mdefine_line|#define S1DREG_BBLT_BGC0&t;&t;0x0114&t;/* BitBLT Background Color Register 0 */
DECL|macro|S1DREG_BBLT_BGC1
mdefine_line|#define S1DREG_BBLT_BGC1&t;&t;0x0115&t;/* BitBLT Background Color Register 1 */
DECL|macro|S1DREG_BBLT_FGC0
mdefine_line|#define S1DREG_BBLT_FGC0&t;&t;0x0118&t;/* BitBLT Foreground Color Register 0 */
DECL|macro|S1DREG_BBLT_FGC1
mdefine_line|#define S1DREG_BBLT_FGC1&t;&t;0x0119&t;/* BitBLT Foreground Color Register 1 */
DECL|macro|S1DREG_LKUP_MODE
mdefine_line|#define S1DREG_LKUP_MODE&t;&t;0x01E0&t;/* Look-Up Table Mode Register */
DECL|macro|S1DREG_LKUP_ADDR
mdefine_line|#define S1DREG_LKUP_ADDR&t;&t;0x01E2&t;/* Look-Up Table Address Register */
DECL|macro|S1DREG_LKUP_DATA
mdefine_line|#define S1DREG_LKUP_DATA&t;&t;0x01E4&t;/* Look-Up Table Data Register */
DECL|macro|S1DREG_PS_CNF
mdefine_line|#define S1DREG_PS_CNF&t;&t;&t;0x01F0&t;/* Power Save Configuration Register */
DECL|macro|S1DREG_PS_STATUS
mdefine_line|#define S1DREG_PS_STATUS&t;&t;0x01F1&t;/* Power Save Status Register */
DECL|macro|S1DREG_CPU2MEM_WDOGT
mdefine_line|#define S1DREG_CPU2MEM_WDOGT&t;&t;0x01F4&t;/* CPU-to-Memory Access Watchdog Timer Register */
DECL|macro|S1DREG_COM_DISP_MODE
mdefine_line|#define S1DREG_COM_DISP_MODE&t;&t;0x01FC&t;/* Common Display Mode Register */
DECL|macro|S1DREG_DELAYOFF
mdefine_line|#define S1DREG_DELAYOFF&t;&t;&t;0xFFFE
DECL|macro|S1DREG_DELAYON
mdefine_line|#define S1DREG_DELAYON&t;&t;&t;0xFFFF
multiline_comment|/* Note: all above defines should go in separate header files&n;   when implementing other S1D13xxx chip support. */
DECL|struct|s1d13xxxfb_regval
r_struct
id|s1d13xxxfb_regval
(brace
DECL|member|addr
id|u16
id|addr
suffix:semicolon
DECL|member|value
id|u8
id|value
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|s1d13xxxfb_par
r_struct
id|s1d13xxxfb_par
(brace
DECL|member|regs
r_void
id|__iomem
op_star
id|regs
suffix:semicolon
DECL|member|display
r_int
r_char
id|display
suffix:semicolon
DECL|member|pseudo_palette
r_int
r_int
id|pseudo_palette
(braket
l_int|16
)braket
suffix:semicolon
macro_line|#ifdef CONFIG_PM
DECL|member|regs_save
r_void
op_star
id|regs_save
suffix:semicolon
multiline_comment|/* pm saves all registers here */
DECL|member|disp_save
r_void
op_star
id|disp_save
suffix:semicolon
multiline_comment|/* pm saves entire screen here */
macro_line|#endif
)brace
suffix:semicolon
DECL|struct|s1d13xxxfb_pdata
r_struct
id|s1d13xxxfb_pdata
(brace
DECL|member|initregs
r_const
r_struct
id|s1d13xxxfb_regval
op_star
id|initregs
suffix:semicolon
DECL|member|initregssize
r_const
r_int
r_int
id|initregssize
suffix:semicolon
DECL|member|platform_init_video
r_void
(paren
op_star
id|platform_init_video
)paren
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PM
DECL|member|platform_suspend_video
r_int
(paren
op_star
id|platform_suspend_video
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|platform_resume_video
r_int
(paren
op_star
id|platform_resume_video
)paren
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
macro_line|#endif
eof
