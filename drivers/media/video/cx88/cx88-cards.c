multiline_comment|/*&n; * device driver for Conexant 2388x based TV cards&n; * card-specific stuff.&n; *&n; * (c) 2003 Gerd Knorr &lt;kraxel@bytesex.org&gt; [SuSE Labs]&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &quot;cx88.h&quot;
multiline_comment|/* ------------------------------------------------------------------ */
multiline_comment|/* board config info                                                  */
DECL|variable|cx88_boards
r_struct
id|cx88_board
id|cx88_boards
(braket
)braket
op_assign
(brace
(braket
id|CX88_BOARD_UNKNOWN
)braket
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;UNKNOWN/GENERIC&quot;
comma
dot
id|tuner_type
op_assign
id|UNSET
comma
dot
id|input
op_assign
(brace
(brace
dot
id|type
op_assign
id|CX88_VMUX_COMPOSITE1
comma
dot
id|vmux
op_assign
l_int|0
comma
)brace
comma
(brace
dot
id|type
op_assign
id|CX88_VMUX_COMPOSITE2
comma
dot
id|vmux
op_assign
l_int|1
comma
)brace
comma
(brace
dot
id|type
op_assign
id|CX88_VMUX_COMPOSITE3
comma
dot
id|vmux
op_assign
l_int|2
comma
)brace
comma
(brace
dot
id|type
op_assign
id|CX88_VMUX_COMPOSITE4
comma
dot
id|vmux
op_assign
l_int|3
comma
)brace
)brace
comma
)brace
comma
(braket
id|CX88_BOARD_HAUPPAUGE
)braket
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;Hauppauge WinTV 34xxx models&quot;
comma
dot
id|tuner_type
op_assign
id|UNSET
comma
dot
id|input
op_assign
(brace
(brace
dot
id|type
op_assign
id|CX88_VMUX_TELEVISION
comma
dot
id|vmux
op_assign
l_int|0
comma
singleline_comment|//.gpio0  = 0xff03,
dot
id|gpio0
op_assign
l_int|0xff01
comma
)brace
comma
(brace
dot
id|type
op_assign
id|CX88_VMUX_DEBUG
comma
dot
id|vmux
op_assign
l_int|0
comma
dot
id|gpio0
op_assign
l_int|0xff00
comma
)brace
comma
(brace
dot
id|type
op_assign
id|CX88_VMUX_COMPOSITE1
comma
dot
id|vmux
op_assign
l_int|1
comma
dot
id|gpio0
op_assign
l_int|0xff02
comma
)brace
)brace
comma
dot
id|radio
op_assign
(brace
dot
id|type
op_assign
id|CX88_RADIO
comma
dot
id|gpio0
op_assign
l_int|0xff01
comma
)brace
comma
)brace
comma
(braket
id|CX88_BOARD_GDI
)braket
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;GDI Black Gold&quot;
comma
dot
id|tuner_type
op_assign
id|UNSET
comma
dot
id|input
op_assign
(brace
(brace
dot
id|type
op_assign
id|CX88_VMUX_TELEVISION
comma
dot
id|vmux
op_assign
l_int|0
comma
)brace
)brace
comma
)brace
comma
(braket
id|CX88_BOARD_PIXELVIEW
)braket
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;PixelView&quot;
comma
dot
id|tuner_type
op_assign
id|UNSET
comma
dot
id|input
op_assign
(brace
(brace
dot
id|type
op_assign
id|CX88_VMUX_TELEVISION
comma
dot
id|vmux
op_assign
l_int|0
comma
)brace
comma
(brace
dot
id|type
op_assign
id|CX88_VMUX_COMPOSITE1
comma
dot
id|vmux
op_assign
l_int|1
comma
)brace
comma
(brace
dot
id|type
op_assign
id|CX88_VMUX_SVIDEO
comma
dot
id|vmux
op_assign
l_int|2
comma
)brace
)brace
comma
)brace
comma
(braket
id|CX88_BOARD_ATI_WONDER_PRO
)braket
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;ATI TV Wonder Pro&quot;
comma
dot
id|tuner_type
op_assign
id|UNSET
comma
dot
id|input
op_assign
(brace
(brace
dot
id|type
op_assign
id|CX88_VMUX_TELEVISION
comma
dot
id|vmux
op_assign
l_int|0
comma
)brace
)brace
comma
)brace
comma
(braket
id|CX88_BOARD_WINFAST2000XP
)braket
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;Leadtek Winfast 2000XP Expert&quot;
comma
dot
id|tuner_type
op_assign
l_int|38
comma
dot
id|input
op_assign
(brace
(brace
dot
id|type
op_assign
id|CX88_VMUX_TELEVISION
comma
dot
id|vmux
op_assign
l_int|0
comma
)brace
)brace
comma
dot
id|radio
op_assign
(brace
dot
id|type
op_assign
id|CX88_RADIO
comma
)brace
comma
)brace
comma
(braket
id|CX88_BOARD_AVERTV_303
)braket
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;AverTV Studio 303 (M126)&quot;
comma
dot
id|tuner_type
op_assign
id|TUNER_PHILIPS_PAL_DK
comma
dot
id|input
op_assign
(brace
(brace
dot
id|type
op_assign
id|CX88_VMUX_TELEVISION
comma
dot
id|vmux
op_assign
l_int|0
comma
)brace
)brace
comma
)brace
comma
(braket
id|CX88_BOARD_MSI_TVANYWHERE
)braket
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;MSI TV-@nywhere Master&quot;
comma
dot
id|tuner_type
op_assign
l_int|33
comma
dot
id|input
op_assign
(brace
(brace
dot
id|type
op_assign
id|CX88_VMUX_TELEVISION
comma
dot
id|vmux
op_assign
l_int|0
comma
)brace
comma
(brace
dot
id|type
op_assign
id|CX88_VMUX_COMPOSITE1
comma
dot
id|vmux
op_assign
l_int|1
comma
)brace
comma
(brace
dot
id|type
op_assign
id|CX88_VMUX_SVIDEO
comma
dot
id|vmux
op_assign
l_int|2
comma
)brace
)brace
comma
dot
id|radio
op_assign
(brace
dot
id|type
op_assign
id|CX88_RADIO
comma
)brace
comma
)brace
comma
(braket
id|CX88_BOARD_WINFAST_DV2000
)braket
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;Leadtek Winfast DV2000&quot;
comma
dot
id|tuner_type
op_assign
l_int|38
comma
dot
id|input
op_assign
(brace
(brace
dot
id|type
op_assign
id|CX88_VMUX_TELEVISION
comma
dot
id|vmux
op_assign
l_int|0
comma
)brace
)brace
comma
dot
id|radio
op_assign
(brace
dot
id|type
op_assign
id|CX88_RADIO
comma
)brace
comma
)brace
comma
)brace
suffix:semicolon
DECL|variable|cx88_bcount
r_const
r_int
r_int
id|cx88_bcount
op_assign
id|ARRAY_SIZE
c_func
(paren
id|cx88_boards
)paren
suffix:semicolon
multiline_comment|/* ------------------------------------------------------------------ */
multiline_comment|/* PCI subsystem IDs                                                  */
DECL|variable|cx88_subids
r_struct
id|cx88_subid
id|cx88_subids
(braket
)braket
op_assign
(brace
(brace
dot
id|subvendor
op_assign
l_int|0x0070
comma
dot
id|subdevice
op_assign
l_int|0x3400
comma
dot
id|card
op_assign
id|CX88_BOARD_HAUPPAUGE
comma
)brace
comma
(brace
dot
id|subvendor
op_assign
l_int|0x0070
comma
dot
id|subdevice
op_assign
l_int|0x3401
comma
dot
id|card
op_assign
id|CX88_BOARD_HAUPPAUGE
comma
)brace
comma
(brace
dot
id|subvendor
op_assign
l_int|0x14c7
comma
dot
id|subdevice
op_assign
l_int|0x0106
comma
dot
id|card
op_assign
id|CX88_BOARD_GDI
comma
)brace
comma
(brace
dot
id|subvendor
op_assign
l_int|0x14c7
comma
dot
id|subdevice
op_assign
l_int|0x0107
comma
multiline_comment|/* with mpeg encoder */
dot
id|card
op_assign
id|CX88_BOARD_GDI
comma
)brace
comma
(brace
dot
id|subvendor
op_assign
id|PCI_VENDOR_ID_ATI
comma
dot
id|subdevice
op_assign
l_int|0x00f8
comma
dot
id|card
op_assign
id|CX88_BOARD_ATI_WONDER_PRO
comma
)brace
comma
(brace
dot
id|subvendor
op_assign
l_int|0x107d
comma
dot
id|subdevice
op_assign
l_int|0x6611
comma
dot
id|card
op_assign
id|CX88_BOARD_WINFAST2000XP
comma
)brace
comma
(brace
dot
id|subvendor
op_assign
l_int|0x107d
comma
dot
id|subdevice
op_assign
l_int|0x6620
comma
dot
id|card
op_assign
id|CX88_BOARD_WINFAST_DV2000
comma
)brace
comma
(brace
dot
id|subvendor
op_assign
l_int|0x1461
comma
dot
id|subdevice
op_assign
l_int|0x000b
comma
dot
id|card
op_assign
id|CX88_BOARD_AVERTV_303
comma
)brace
comma
(brace
dot
id|subvendor
op_assign
l_int|0x1462
comma
dot
id|subdevice
op_assign
l_int|0x8606
comma
dot
id|card
op_assign
id|CX88_BOARD_MSI_TVANYWHERE
comma
)brace
)brace
suffix:semicolon
DECL|variable|cx88_idcount
r_const
r_int
r_int
id|cx88_idcount
op_assign
id|ARRAY_SIZE
c_func
(paren
id|cx88_subids
)paren
suffix:semicolon
multiline_comment|/* ----------------------------------------------------------------------- */
multiline_comment|/* some hauppauge specific stuff                                           */
r_static
r_struct
(brace
DECL|member|id
r_int
id|id
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|variable|__devinitdata
)brace
id|hauppauge_tuner
(braket
)braket
id|__devinitdata
op_assign
(brace
(brace
id|TUNER_ABSENT
comma
l_string|&quot;&quot;
)brace
comma
(brace
id|TUNER_ABSENT
comma
l_string|&quot;External&quot;
)brace
comma
(brace
id|TUNER_ABSENT
comma
l_string|&quot;Unspecified&quot;
)brace
comma
(brace
id|TUNER_PHILIPS_PAL
comma
l_string|&quot;Philips FI1216&quot;
)brace
comma
(brace
id|TUNER_PHILIPS_SECAM
comma
l_string|&quot;Philips FI1216MF&quot;
)brace
comma
(brace
id|TUNER_PHILIPS_NTSC
comma
l_string|&quot;Philips FI1236&quot;
)brace
comma
(brace
id|TUNER_PHILIPS_PAL_I
comma
l_string|&quot;Philips FI1246&quot;
)brace
comma
(brace
id|TUNER_PHILIPS_PAL_DK
comma
l_string|&quot;Philips FI1256&quot;
)brace
comma
(brace
id|TUNER_PHILIPS_PAL
comma
l_string|&quot;Philips FI1216 MK2&quot;
)brace
comma
(brace
id|TUNER_PHILIPS_SECAM
comma
l_string|&quot;Philips FI1216MF MK2&quot;
)brace
comma
(brace
id|TUNER_PHILIPS_NTSC
comma
l_string|&quot;Philips FI1236 MK2&quot;
)brace
comma
(brace
id|TUNER_PHILIPS_PAL_I
comma
l_string|&quot;Philips FI1246 MK2&quot;
)brace
comma
(brace
id|TUNER_PHILIPS_PAL_DK
comma
l_string|&quot;Philips FI1256 MK2&quot;
)brace
comma
(brace
id|TUNER_TEMIC_NTSC
comma
l_string|&quot;Temic 4032FY5&quot;
)brace
comma
(brace
id|TUNER_TEMIC_PAL
comma
l_string|&quot;Temic 4002FH5&quot;
)brace
comma
(brace
id|TUNER_TEMIC_PAL_I
comma
l_string|&quot;Temic 4062FY5&quot;
)brace
comma
(brace
id|TUNER_PHILIPS_PAL
comma
l_string|&quot;Philips FR1216 MK2&quot;
)brace
comma
(brace
id|TUNER_PHILIPS_SECAM
comma
l_string|&quot;Philips FR1216MF MK2&quot;
)brace
comma
(brace
id|TUNER_PHILIPS_NTSC
comma
l_string|&quot;Philips FR1236 MK2&quot;
)brace
comma
(brace
id|TUNER_PHILIPS_PAL_I
comma
l_string|&quot;Philips FR1246 MK2&quot;
)brace
comma
(brace
id|TUNER_PHILIPS_PAL_DK
comma
l_string|&quot;Philips FR1256 MK2&quot;
)brace
comma
(brace
id|TUNER_PHILIPS_PAL
comma
l_string|&quot;Philips FM1216&quot;
)brace
comma
(brace
id|TUNER_PHILIPS_SECAM
comma
l_string|&quot;Philips FM1216MF&quot;
)brace
comma
(brace
id|TUNER_PHILIPS_NTSC
comma
l_string|&quot;Philips FM1236&quot;
)brace
comma
(brace
id|TUNER_PHILIPS_PAL_I
comma
l_string|&quot;Philips FM1246&quot;
)brace
comma
(brace
id|TUNER_PHILIPS_PAL_DK
comma
l_string|&quot;Philips FM1256&quot;
)brace
comma
(brace
id|TUNER_TEMIC_4036FY5_NTSC
comma
l_string|&quot;Temic 4036FY5&quot;
)brace
comma
(brace
id|TUNER_ABSENT
comma
l_string|&quot;Samsung TCPN9082D&quot;
)brace
comma
(brace
id|TUNER_ABSENT
comma
l_string|&quot;Samsung TCPM9092P&quot;
)brace
comma
(brace
id|TUNER_TEMIC_4006FH5_PAL
comma
l_string|&quot;Temic 4006FH5&quot;
)brace
comma
(brace
id|TUNER_ABSENT
comma
l_string|&quot;Samsung TCPN9085D&quot;
)brace
comma
(brace
id|TUNER_ABSENT
comma
l_string|&quot;Samsung TCPB9085P&quot;
)brace
comma
(brace
id|TUNER_ABSENT
comma
l_string|&quot;Samsung TCPL9091P&quot;
)brace
comma
(brace
id|TUNER_TEMIC_4039FR5_NTSC
comma
l_string|&quot;Temic 4039FR5&quot;
)brace
comma
(brace
id|TUNER_PHILIPS_FQ1216ME
comma
l_string|&quot;Philips FQ1216 ME&quot;
)brace
comma
(brace
id|TUNER_TEMIC_4066FY5_PAL_I
comma
l_string|&quot;Temic 4066FY5&quot;
)brace
comma
(brace
id|TUNER_PHILIPS_NTSC
comma
l_string|&quot;Philips TD1536&quot;
)brace
comma
(brace
id|TUNER_PHILIPS_NTSC
comma
l_string|&quot;Philips TD1536D&quot;
)brace
comma
(brace
id|TUNER_PHILIPS_NTSC
comma
l_string|&quot;Philips FMR1236&quot;
)brace
comma
multiline_comment|/* mono radio */
(brace
id|TUNER_ABSENT
comma
l_string|&quot;Philips FI1256MP&quot;
)brace
comma
(brace
id|TUNER_ABSENT
comma
l_string|&quot;Samsung TCPQ9091P&quot;
)brace
comma
(brace
id|TUNER_TEMIC_4006FN5_MULTI_PAL
comma
l_string|&quot;Temic 4006FN5&quot;
)brace
comma
(brace
id|TUNER_TEMIC_4009FR5_PAL
comma
l_string|&quot;Temic 4009FR5&quot;
)brace
comma
(brace
id|TUNER_TEMIC_4046FM5
comma
l_string|&quot;Temic 4046FM5&quot;
)brace
comma
(brace
id|TUNER_TEMIC_4009FN5_MULTI_PAL_FM
comma
l_string|&quot;Temic 4009FN5&quot;
)brace
comma
(brace
id|TUNER_ABSENT
comma
l_string|&quot;Philips TD1536D_FH_44&quot;
)brace
comma
(brace
id|TUNER_LG_NTSC_FM
comma
l_string|&quot;LG TPI8NSR01F&quot;
)brace
comma
(brace
id|TUNER_LG_PAL_FM
comma
l_string|&quot;LG TPI8PSB01D&quot;
)brace
comma
(brace
id|TUNER_LG_PAL
comma
l_string|&quot;LG TPI8PSB11D&quot;
)brace
comma
(brace
id|TUNER_LG_PAL_I_FM
comma
l_string|&quot;LG TAPC-I001D&quot;
)brace
comma
(brace
id|TUNER_LG_PAL_I
comma
l_string|&quot;LG TAPC-I701D&quot;
)brace
)brace
suffix:semicolon
DECL|function|hauppauge_eeprom
r_static
r_void
id|__devinit
id|hauppauge_eeprom
c_func
(paren
r_struct
id|cx8800_dev
op_star
id|dev
comma
id|u8
op_star
id|eeprom_data
)paren
(brace
r_int
r_int
id|blk2
comma
id|tuner
comma
id|radio
comma
id|model
suffix:semicolon
r_if
c_cond
(paren
id|eeprom_data
(braket
l_int|0
)braket
op_ne
l_int|0x84
op_logical_or
id|eeprom_data
(braket
l_int|2
)braket
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: Hauppauge eeprom: invalid&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Block 2 starts after len+3 bytes header */
id|blk2
op_assign
id|eeprom_data
(braket
l_int|1
)braket
op_plus
l_int|3
suffix:semicolon
multiline_comment|/* decode + use some config infos */
id|model
op_assign
id|eeprom_data
(braket
l_int|12
)braket
op_lshift
l_int|8
op_or
id|eeprom_data
(braket
l_int|11
)braket
suffix:semicolon
id|tuner
op_assign
id|eeprom_data
(braket
l_int|9
)braket
suffix:semicolon
id|radio
op_assign
id|eeprom_data
(braket
id|blk2
op_minus
l_int|1
)braket
op_amp
l_int|0x01
suffix:semicolon
r_if
c_cond
(paren
id|tuner
OL
id|ARRAY_SIZE
c_func
(paren
id|hauppauge_tuner
)paren
)paren
id|dev-&gt;tuner_type
op_assign
id|hauppauge_tuner
(braket
id|tuner
)braket
dot
id|id
suffix:semicolon
r_if
c_cond
(paren
id|radio
)paren
id|dev-&gt;has_radio
op_assign
l_int|1
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: hauppauge eeprom: model=%d, &quot;
l_string|&quot;tuner=%s (%d), radio=%s&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|model
comma
id|hauppauge_tuner
(braket
id|tuner
)braket
dot
id|name
comma
id|dev-&gt;tuner_type
comma
id|radio
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* ----------------------------------------------------------------------- */
multiline_comment|/* some GDI (was: Modular Technology) specific stuff                       */
r_static
r_struct
(brace
DECL|member|id
r_int
id|id
suffix:semicolon
DECL|member|fm
r_int
id|fm
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|variable|gdi_tuner
)brace
id|gdi_tuner
(braket
)braket
op_assign
(brace
(braket
l_int|0x01
)braket
op_assign
(brace
dot
id|id
op_assign
id|TUNER_ABSENT
comma
dot
id|name
op_assign
l_string|&quot;NTSC_M&quot;
)brace
comma
(braket
l_int|0x02
)braket
op_assign
(brace
dot
id|id
op_assign
id|TUNER_ABSENT
comma
dot
id|name
op_assign
l_string|&quot;PAL_B&quot;
)brace
comma
(braket
l_int|0x03
)braket
op_assign
(brace
dot
id|id
op_assign
id|TUNER_ABSENT
comma
dot
id|name
op_assign
l_string|&quot;BAL_I&quot;
)brace
comma
(braket
l_int|0x04
)braket
op_assign
(brace
dot
id|id
op_assign
id|TUNER_ABSENT
comma
dot
id|name
op_assign
l_string|&quot;PAL_D&quot;
)brace
comma
(braket
l_int|0x05
)braket
op_assign
(brace
dot
id|id
op_assign
id|TUNER_ABSENT
comma
dot
id|name
op_assign
l_string|&quot;SECAM&quot;
)brace
comma
(braket
l_int|0x10
)braket
op_assign
(brace
dot
id|id
op_assign
id|TUNER_ABSENT
comma
dot
id|fm
op_assign
l_int|1
comma
dot
id|name
op_assign
l_string|&quot;TEMIC_4049&quot;
)brace
comma
(braket
l_int|0x11
)braket
op_assign
(brace
dot
id|id
op_assign
id|TUNER_TEMIC_4136FY5
comma
dot
id|name
op_assign
l_string|&quot;TEMIC_4136&quot;
)brace
comma
(braket
l_int|0x12
)braket
op_assign
(brace
dot
id|id
op_assign
id|TUNER_ABSENT
comma
dot
id|name
op_assign
l_string|&quot;TEMIC_4146&quot;
)brace
comma
(braket
l_int|0x20
)braket
op_assign
(brace
dot
id|id
op_assign
id|TUNER_PHILIPS_FQ1216ME
comma
dot
id|fm
op_assign
l_int|1
comma
dot
id|name
op_assign
l_string|&quot;PHILIPS_FQ1216_MK3&quot;
)brace
comma
(braket
l_int|0x21
)braket
op_assign
(brace
dot
id|id
op_assign
id|TUNER_ABSENT
comma
dot
id|fm
op_assign
l_int|1
comma
dot
id|name
op_assign
l_string|&quot;PHILIPS_FQ1236_MK3&quot;
)brace
comma
(braket
l_int|0x22
)braket
op_assign
(brace
dot
id|id
op_assign
id|TUNER_ABSENT
comma
dot
id|name
op_assign
l_string|&quot;PHILIPS_FI1236_MK3&quot;
)brace
comma
(braket
l_int|0x23
)braket
op_assign
(brace
dot
id|id
op_assign
id|TUNER_ABSENT
comma
dot
id|name
op_assign
l_string|&quot;PHILIPS_FI1216_MK3&quot;
)brace
comma
)brace
suffix:semicolon
DECL|function|gdi_eeprom
r_static
r_void
id|__devinit
id|gdi_eeprom
c_func
(paren
r_struct
id|cx8800_dev
op_star
id|dev
comma
id|u8
op_star
id|eeprom_data
)paren
(brace
r_char
op_star
id|name
op_assign
(paren
id|eeprom_data
(braket
l_int|0x0d
)braket
OL
id|ARRAY_SIZE
c_func
(paren
id|gdi_tuner
)paren
)paren
ques
c_cond
id|gdi_tuner
(braket
id|eeprom_data
(braket
l_int|0x0d
)braket
)braket
dot
id|name
suffix:colon
l_int|NULL
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: GDI: tuner=%s&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|name
ques
c_cond
id|name
suffix:colon
l_string|&quot;unknown&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|NULL
op_eq
id|name
)paren
r_return
suffix:semicolon
id|dev-&gt;tuner_type
op_assign
id|gdi_tuner
(braket
id|eeprom_data
(braket
l_int|0x0d
)braket
)braket
dot
id|id
suffix:semicolon
id|dev-&gt;has_radio
op_assign
id|gdi_tuner
(braket
id|eeprom_data
(braket
l_int|0x0d
)braket
)braket
dot
id|fm
suffix:semicolon
)brace
multiline_comment|/* ----------------------------------------------------------------------- */
r_static
r_int
DECL|function|i2c_eeprom
id|i2c_eeprom
c_func
(paren
r_struct
id|i2c_client
op_star
id|c
comma
r_int
r_char
op_star
id|eedata
comma
r_int
id|len
)paren
(brace
r_int
r_char
id|buf
suffix:semicolon
r_int
id|err
suffix:semicolon
id|c-&gt;addr
op_assign
l_int|0xa0
op_rshift
l_int|1
suffix:semicolon
id|buf
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
l_int|1
op_ne
(paren
id|err
op_assign
id|i2c_master_send
c_func
(paren
id|c
comma
op_amp
id|buf
comma
l_int|1
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;cx88: Huh, no eeprom present (err=%d)?&bslash;n&quot;
comma
id|err
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|len
op_ne
(paren
id|err
op_assign
id|i2c_master_recv
c_func
(paren
id|c
comma
id|eedata
comma
id|len
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;cx88: i2c eeprom read error (err=%d)&bslash;n&quot;
comma
id|err
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
macro_line|#if 0
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|len
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
l_int|0
op_eq
(paren
id|i
op_mod
l_int|16
)paren
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;cx88 ee: %02x:&quot;
comma
id|i
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; %02x&quot;
comma
id|eedata
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|15
op_eq
(paren
id|i
op_mod
l_int|16
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cx88_card_setup
r_void
id|__devinit
id|cx88_card_setup
c_func
(paren
r_struct
id|cx8800_dev
op_star
id|dev
)paren
(brace
r_static
id|u8
id|eeprom
(braket
l_int|128
)braket
suffix:semicolon
r_switch
c_cond
(paren
id|dev-&gt;board
)paren
(brace
r_case
id|CX88_BOARD_HAUPPAUGE
suffix:colon
r_if
c_cond
(paren
l_int|0
op_eq
id|dev-&gt;i2c_rc
)paren
id|i2c_eeprom
c_func
(paren
op_amp
id|dev-&gt;i2c_client
comma
id|eeprom
comma
r_sizeof
(paren
id|eeprom
)paren
)paren
suffix:semicolon
id|hauppauge_eeprom
c_func
(paren
id|dev
comma
id|eeprom
op_plus
l_int|8
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CX88_BOARD_GDI
suffix:colon
r_if
c_cond
(paren
l_int|0
op_eq
id|dev-&gt;i2c_rc
)paren
id|i2c_eeprom
c_func
(paren
op_amp
id|dev-&gt;i2c_client
comma
id|eeprom
comma
r_sizeof
(paren
id|eeprom
)paren
)paren
suffix:semicolon
id|gdi_eeprom
c_func
(paren
id|dev
comma
id|eeprom
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/* ------------------------------------------------------------------ */
DECL|variable|cx88_boards
id|EXPORT_SYMBOL
c_func
(paren
id|cx88_boards
)paren
suffix:semicolon
DECL|variable|cx88_bcount
id|EXPORT_SYMBOL
c_func
(paren
id|cx88_bcount
)paren
suffix:semicolon
DECL|variable|cx88_subids
id|EXPORT_SYMBOL
c_func
(paren
id|cx88_subids
)paren
suffix:semicolon
DECL|variable|cx88_idcount
id|EXPORT_SYMBOL
c_func
(paren
id|cx88_idcount
)paren
suffix:semicolon
DECL|variable|cx88_card_setup
id|EXPORT_SYMBOL
c_func
(paren
id|cx88_card_setup
)paren
suffix:semicolon
multiline_comment|/*&n; * Local variables:&n; * c-basic-offset: 8&n; * End:&n; */
eof
