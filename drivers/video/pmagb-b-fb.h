multiline_comment|/*&n; *      linux/drivers/video/pmagb-b-fb.h&n; *&n; *      TurboChannel PMAGB-B framebuffer card support,&n; *      Copyright (C) 1999, 2000, 2001 by&n; *      Michael Engel &lt;engel@unix-ag.org&gt; and &n; *      Karsten Merker &lt;merker@linxutag.org&gt;&n; *      This file is subject to the terms and conditions of the GNU General&n; *      Public License.  See the file COPYING in the main directory of this&n; *      archive for more details.&n; */
multiline_comment|/*&n; * Bt459 RAM DAC register base offset (rel. to TC slot base address)&n; */
DECL|macro|PMAGB_B_BT459_OFFSET
mdefine_line|#define PMAGB_B_BT459_OFFSET&t;&t;&t;0x001C0000
multiline_comment|/*&n; * Begin of PMAGB-B framebuffer memory, resolution is configurable:&n; * 1024x864x8 or 1280x1024x8, settable by jumper on the card&n; */
DECL|macro|PMAGB_B_ONBOARD_FBMEM_OFFSET
mdefine_line|#define PMAGB_B_ONBOARD_FBMEM_OFFSET&t;0x00201000
multiline_comment|/*&n; * Bt459 register offsets, byte-wide registers&n; */
DECL|macro|BT459_ADR_LOW
mdefine_line|#define BT459_ADR_LOW&t;&t;&t;BT459_OFFSET + 0x00&t;/* addr. low */
DECL|macro|BT459_ADR_HIGH
mdefine_line|#define BT459_ADR_HIGH&t;&t;&t;BT459_OFFSET + 0x04&t;/* addr. high */
DECL|macro|BT459_DATA
mdefine_line|#define BT459_DATA&t;&t;&t;BT459_OFFSET + 0x08&t;/* r/w data */
DECL|macro|BT459_CMAP
mdefine_line|#define BT459_CMAP&t;&t;&t;BT459_OFFSET + 0x0C&t;/* color map */
eof
