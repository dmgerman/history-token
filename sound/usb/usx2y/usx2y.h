multiline_comment|/*&n; * Driver for Tascam US-X2Y USB soundcards&n; *&n; * Copyright (c) 2003 by Karsten Wiese &lt;annabellesgarden@yahoo.de&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#ifndef __SOUND_USX2Y_COMMON_H
DECL|macro|__SOUND_USX2Y_COMMON_H
mdefine_line|#define __SOUND_USX2Y_COMMON_H
DECL|macro|USX2Y_DRIVER_VERSION
mdefine_line|#define USX2Y_DRIVER_VERSION&t;0x0100&t;/* 0.1.0 */
multiline_comment|/* hwdep id string */
DECL|macro|SND_USX2Y_LOADER_ID
mdefine_line|#define SND_USX2Y_LOADER_ID&t;&t;&quot;USX2Y Loader&quot;
DECL|macro|SND_USX2Y_USBPCM_ID
mdefine_line|#define SND_USX2Y_USBPCM_ID&t;&t;&quot;USX2Y USBPCM&quot;
multiline_comment|/* hardware type */
r_enum
(brace
DECL|enumerator|USX2Y_TYPE_122
id|USX2Y_TYPE_122
comma
DECL|enumerator|USX2Y_TYPE_224
id|USX2Y_TYPE_224
comma
DECL|enumerator|USX2Y_TYPE_428
id|USX2Y_TYPE_428
comma
DECL|enumerator|USX2Y_TYPE_NUMS
id|USX2Y_TYPE_NUMS
)brace
suffix:semicolon
DECL|macro|USB_ID_US122
mdefine_line|#define USB_ID_US122 0x8007
DECL|macro|USB_ID_US224
mdefine_line|#define USB_ID_US224 0x8005
DECL|macro|USB_ID_US428
mdefine_line|#define USB_ID_US428 0x8001
multiline_comment|/* chip status */
r_enum
(brace
DECL|enumerator|USX2Y_STAT_CHIP_INIT
id|USX2Y_STAT_CHIP_INIT
op_assign
(paren
l_int|1
op_lshift
l_int|0
)paren
comma
multiline_comment|/* all operational */
DECL|enumerator|USX2Y_STAT_CHIP_MMAP_PCM_URBS
id|USX2Y_STAT_CHIP_MMAP_PCM_URBS
op_assign
(paren
l_int|1
op_lshift
l_int|1
)paren
comma
multiline_comment|/* pcm transport over mmaped urbs */
DECL|enumerator|USX2Y_STAT_CHIP_HUP
id|USX2Y_STAT_CHIP_HUP
op_assign
(paren
l_int|1
op_lshift
l_int|31
)paren
comma
multiline_comment|/* all operational */
)brace
suffix:semicolon
macro_line|#endif /* __SOUND_USX2Y_COMMON_H */
eof
