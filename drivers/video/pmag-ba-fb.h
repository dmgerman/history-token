multiline_comment|/*&n; *      linux/drivers/video/pmag-ba-fb.h&n; *&n; *      TurboChannel PMAG-BA framebuffer card support,&n; *      Copyright (C) 1999,2000,2001 by&n; *      Michael Engel &lt;engel@unix-ag.org&gt;,&n; *      Karsten Merker &lt;merker@linuxtag.org&gt;&n; *      This file is subject to the terms and conditions of the GNU General&n; *      Public License.  See the file COPYING in the main directory of this&n; *      archive for more details.&n; */
multiline_comment|/*&n; * Bt459 RAM DAC register base offset (rel. to TC slot base address)&n; */
DECL|macro|PMAG_BA_BT459_OFFSET
mdefine_line|#define PMAG_BA_BT459_OFFSET                    0x00200000
multiline_comment|/*&n; * Begin of PMAG-BA framebuffer memory relative to TC slot address,&n; * resolution is 1024x864x8&n; */
DECL|macro|PMAG_BA_ONBOARD_FBMEM_OFFSET
mdefine_line|#define PMAG_BA_ONBOARD_FBMEM_OFFSET    0x00000000
eof
