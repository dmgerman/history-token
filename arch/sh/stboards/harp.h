multiline_comment|/* &n; * Copyright (C) 2001 David J. Mckay (david.mckay@st.com)&n; *&n; * May be copied or modified under the terms of the GNU General Public&n; * License.  See linux/COPYING for more information.                            &n; *&n; * Defintions applicable to the STMicroelectronics ST40STB1 HARP and&n; * compatible boards.&n; */
macro_line|#if defined(CONFIG_SH_STB1_HARP)
DECL|macro|EPLD_BASE
mdefine_line|#define EPLD_BASE     0xa0800000
DECL|macro|EPLD_LED
mdefine_line|#define EPLD_LED      (EPLD_BASE+0x000c0000)
DECL|macro|EPLD_INTSTAT0
mdefine_line|#define EPLD_INTSTAT0 (EPLD_BASE+0x00200000)
DECL|macro|EPLD_INTSTAT1
mdefine_line|#define EPLD_INTSTAT1 (EPLD_BASE+0x00240000)
DECL|macro|EPLD_INTMASK0
mdefine_line|#define EPLD_INTMASK0 (EPLD_BASE+0x00280000)
DECL|macro|EPLD_INTMASK1
mdefine_line|#define EPLD_INTMASK1 (EPLD_BASE+0x002c0000)
DECL|macro|EPLD_PAGEADDR
mdefine_line|#define EPLD_PAGEADDR (EPLD_BASE+0x00300000)
DECL|macro|EPLD_REVID1
mdefine_line|#define EPLD_REVID1   (EPLD_BASE+0x00380000)
DECL|macro|EPLD_REVID2
mdefine_line|#define EPLD_REVID2   (EPLD_BASE+0x003c0000)
DECL|macro|EPLD_LED_ON
mdefine_line|#define EPLD_LED_ON  1
DECL|macro|EPLD_LED_OFF
mdefine_line|#define EPLD_LED_OFF 0
macro_line|#elif defined(CONFIG_SH_STB1_OVERDRIVE)
DECL|macro|EPLD_BASE
mdefine_line|#define EPLD_BASE     0xa7000000
DECL|macro|EPLD_REVID
mdefine_line|#define EPLD_REVID    (EPLD_BASE+0x00000000)
DECL|macro|EPLD_LED
mdefine_line|#define EPLD_LED      (EPLD_BASE+0x00040000)
DECL|macro|EPLD_INTMASK0
mdefine_line|#define EPLD_INTMASK0 (EPLD_BASE+0x001c0000)
DECL|macro|EPLD_INTMASK1
mdefine_line|#define EPLD_INTMASK1 (EPLD_BASE+0x00200000)
DECL|macro|EPLD_INTSTAT0
mdefine_line|#define EPLD_INTSTAT0 (EPLD_BASE+0x00240000)
DECL|macro|EPLD_INTSTAT1
mdefine_line|#define EPLD_INTSTAT1 (EPLD_BASE+0x00280000)
DECL|macro|EPLD_LED_ON
mdefine_line|#define EPLD_LED_ON  0
DECL|macro|EPLD_LED_OFF
mdefine_line|#define EPLD_LED_OFF 1
macro_line|#else
macro_line|#error Unknown board
macro_line|#endif
eof
