multiline_comment|/*&n; *      linux/drivers/video/maxinefb.h&n; *&n; *      DECstation 5000/xx onboard framebuffer support, Copyright (C) 1999 by&n; *      Michael Engel &lt;engel@unix-ag.org&gt; and Karsten Merker &lt;merker@guug.de&gt;&n; *      This file is subject to the terms and conditions of the GNU General&n; *      Public License.  See the file COPYING in the main directory of this&n; *      archive for more details.&n; */
multiline_comment|/*&n; * IMS332 video controller register base address&n; */
DECL|macro|MAXINEFB_IMS332_ADDRESS
mdefine_line|#define MAXINEFB_IMS332_ADDRESS                  0xbc140000
multiline_comment|/*&n; * Begin of DECstation 5000/xx onboard framebuffer memory, default resolution&n; * is 1024x768x8&n; */
DECL|macro|DS5000_xx_ONBOARD_FBMEM_START
mdefine_line|#define DS5000_xx_ONBOARD_FBMEM_START&t;0xaa000000
multiline_comment|/*&n; *      The IMS 332 video controller used in the DECstation 5000/xx series&n; *      uses 32 bits wide registers; the following defines declare the&n; *      register numbers, to get the real offset, these have to be multiplied&n; *      by four.&n; */
DECL|macro|IMS332_REG_CURSOR_RAM
mdefine_line|#define IMS332_REG_CURSOR_RAM           0x200&t;/* hardware cursor bitmap */
multiline_comment|/*&n; * The color palette entries have the form 0x00BBGGRR&n; */
DECL|macro|IMS332_REG_COLOR_PALETTE
mdefine_line|#define IMS332_REG_COLOR_PALETTE        0x100&t;/* color palette, 256 entries */
DECL|macro|IMS332_REG_CURSOR_COLOR_PALETTE
mdefine_line|#define IMS332_REG_CURSOR_COLOR_PALETTE&t;0x0a1&t;/* cursor color palette, */
multiline_comment|/* 3 entries             */
eof
