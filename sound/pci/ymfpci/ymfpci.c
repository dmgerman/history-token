multiline_comment|/*&n; *  The driver for the Yamaha&squot;s DS1/DS1E cards&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/ymfpci.h&gt;
macro_line|#include &lt;sound/mpu401.h&gt;
macro_line|#include &lt;sound/opl3.h&gt;
macro_line|#include &lt;sound/initval.h&gt;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Jaroslav Kysela &lt;perex@suse.cz&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Yamaha DS-XG PCI&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_CLASSES
c_func
(paren
l_string|&quot;{sound}&quot;
)paren
suffix:semicolon
id|MODULE_DEVICES
c_func
(paren
l_string|&quot;{{Yamaha,YMF724},&quot;
l_string|&quot;{Yamaha,YMF724F},&quot;
l_string|&quot;{Yamaha,YMF740},&quot;
l_string|&quot;{Yamaha,YMF740C},&quot;
l_string|&quot;{Yamaha,YMF744},&quot;
l_string|&quot;{Yamaha,YMF754}}&quot;
)paren
suffix:semicolon
DECL|variable|index
r_static
r_int
id|index
(braket
id|SNDRV_CARDS
)braket
op_assign
id|SNDRV_DEFAULT_IDX
suffix:semicolon
multiline_comment|/* Index 0-MAX */
DECL|variable|id
r_static
r_char
op_star
id|id
(braket
id|SNDRV_CARDS
)braket
op_assign
id|SNDRV_DEFAULT_STR
suffix:semicolon
multiline_comment|/* ID for this card */
DECL|variable|enable
r_static
r_int
id|enable
(braket
id|SNDRV_CARDS
)braket
op_assign
id|SNDRV_DEFAULT_ENABLE_PNP
suffix:semicolon
multiline_comment|/* Enable this card */
DECL|variable|fm_port
r_static
r_int
id|fm_port
(braket
id|SNDRV_CARDS
)braket
suffix:semicolon
DECL|variable|mpu_port
r_static
r_int
id|mpu_port
(braket
id|SNDRV_CARDS
)braket
suffix:semicolon
macro_line|#ifdef SUPPORT_JOYSTICK
DECL|variable|joystick_port
r_static
r_int
id|joystick_port
(braket
id|SNDRV_CARDS
)braket
suffix:semicolon
macro_line|#endif
DECL|variable|rear_switch
r_static
r_int
id|rear_switch
(braket
id|SNDRV_CARDS
)braket
suffix:semicolon
DECL|variable|boot_devs
r_static
r_int
id|boot_devs
suffix:semicolon
id|module_param_array
c_func
(paren
id|index
comma
r_int
comma
id|boot_devs
comma
l_int|0444
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|index
comma
l_string|&quot;Index value for the Yamaha DS-XG PCI soundcard.&quot;
)paren
suffix:semicolon
id|MODULE_PARM_SYNTAX
c_func
(paren
id|index
comma
id|SNDRV_INDEX_DESC
)paren
suffix:semicolon
id|module_param_array
c_func
(paren
id|id
comma
id|charp
comma
id|boot_devs
comma
l_int|0444
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|id
comma
l_string|&quot;ID string for the Yamaha DS-XG PCI soundcard.&quot;
)paren
suffix:semicolon
id|MODULE_PARM_SYNTAX
c_func
(paren
id|id
comma
id|SNDRV_ID_DESC
)paren
suffix:semicolon
id|module_param_array
c_func
(paren
id|enable
comma
r_bool
comma
id|boot_devs
comma
l_int|0444
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|enable
comma
l_string|&quot;Enable Yamaha DS-XG soundcard.&quot;
)paren
suffix:semicolon
id|MODULE_PARM_SYNTAX
c_func
(paren
id|enable
comma
id|SNDRV_ENABLE_DESC
)paren
suffix:semicolon
id|module_param_array
c_func
(paren
id|mpu_port
comma
r_int
comma
id|boot_devs
comma
l_int|0444
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|mpu_port
comma
l_string|&quot;MPU-401 Port.&quot;
)paren
suffix:semicolon
id|MODULE_PARM_SYNTAX
c_func
(paren
id|mpu_port
comma
id|SNDRV_ENABLED
)paren
suffix:semicolon
id|module_param_array
c_func
(paren
id|fm_port
comma
r_int
comma
id|boot_devs
comma
l_int|0444
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|fm_port
comma
l_string|&quot;FM OPL-3 Port.&quot;
)paren
suffix:semicolon
id|MODULE_PARM_SYNTAX
c_func
(paren
id|fm_port
comma
id|SNDRV_ENABLED
)paren
suffix:semicolon
macro_line|#ifdef SUPPORT_JOYSTICK
id|module_param_array
c_func
(paren
id|joystick_port
comma
r_int
comma
id|boot_devs
comma
l_int|0444
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|joystick_port
comma
l_string|&quot;Joystick port address&quot;
)paren
suffix:semicolon
id|MODULE_PARM_SYNTAX
c_func
(paren
id|joystick_port
comma
id|SNDRV_ENABLED
)paren
suffix:semicolon
macro_line|#endif
id|module_param_array
c_func
(paren
id|rear_switch
comma
r_bool
comma
id|boot_devs
comma
l_int|0444
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|rear_switch
comma
l_string|&quot;Enable shared rear/line-in switch&quot;
)paren
suffix:semicolon
id|MODULE_PARM_SYNTAX
c_func
(paren
id|rear_switch
comma
id|SNDRV_ENABLED
l_string|&quot;,&quot;
id|SNDRV_BOOLEAN_FALSE_DESC
)paren
suffix:semicolon
DECL|variable|snd_ymfpci_ids
r_static
r_struct
id|pci_device_id
id|snd_ymfpci_ids
(braket
)braket
op_assign
(brace
(brace
l_int|0x1073
comma
l_int|0x0004
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
)brace
comma
multiline_comment|/* YMF724 */
(brace
l_int|0x1073
comma
l_int|0x000d
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
)brace
comma
multiline_comment|/* YMF724F */
(brace
l_int|0x1073
comma
l_int|0x000a
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
)brace
comma
multiline_comment|/* YMF740 */
(brace
l_int|0x1073
comma
l_int|0x000c
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
)brace
comma
multiline_comment|/* YMF740C */
(brace
l_int|0x1073
comma
l_int|0x0010
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
)brace
comma
multiline_comment|/* YMF744 */
(brace
l_int|0x1073
comma
l_int|0x0012
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
)brace
comma
multiline_comment|/* YMF754 */
(brace
l_int|0
comma
)brace
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
c_func
(paren
id|pci
comma
id|snd_ymfpci_ids
)paren
suffix:semicolon
DECL|function|snd_card_ymfpci_probe
r_static
r_int
id|__devinit
id|snd_card_ymfpci_probe
c_func
(paren
r_struct
id|pci_dev
op_star
id|pci
comma
r_const
r_struct
id|pci_device_id
op_star
id|pci_id
)paren
(brace
r_static
r_int
id|dev
suffix:semicolon
id|snd_card_t
op_star
id|card
suffix:semicolon
r_struct
id|resource
op_star
id|fm_res
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|resource
op_star
id|mpu_res
op_assign
l_int|NULL
suffix:semicolon
macro_line|#ifdef SUPPORT_JOYSTICK
r_struct
id|resource
op_star
id|joystick_res
op_assign
l_int|NULL
suffix:semicolon
macro_line|#endif
id|ymfpci_t
op_star
id|chip
suffix:semicolon
id|opl3_t
op_star
id|opl3
suffix:semicolon
r_char
op_star
id|str
suffix:semicolon
r_int
id|err
suffix:semicolon
id|u16
id|legacy_ctrl
comma
id|legacy_ctrl2
comma
id|old_legacy_ctrl
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_ge
id|SNDRV_CARDS
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|enable
(braket
id|dev
)braket
)paren
(brace
id|dev
op_increment
suffix:semicolon
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
id|card
op_assign
id|snd_card_new
c_func
(paren
id|index
(braket
id|dev
)braket
comma
id|id
(braket
id|dev
)braket
comma
id|THIS_MODULE
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|card
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_switch
c_cond
(paren
id|pci_id-&gt;device
)paren
(brace
r_case
l_int|0x0004
suffix:colon
id|str
op_assign
l_string|&quot;YMF724&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x000d
suffix:colon
id|str
op_assign
l_string|&quot;YMF724F&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x000a
suffix:colon
id|str
op_assign
l_string|&quot;YMF740&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x000c
suffix:colon
id|str
op_assign
l_string|&quot;YMF740C&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x0010
suffix:colon
id|str
op_assign
l_string|&quot;YMF744&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x0012
suffix:colon
id|str
op_assign
l_string|&quot;YMF754&quot;
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|str
op_assign
l_string|&quot;???&quot;
suffix:semicolon
r_break
suffix:semicolon
)brace
id|legacy_ctrl
op_assign
l_int|0
suffix:semicolon
id|legacy_ctrl2
op_assign
l_int|0x0800
suffix:semicolon
multiline_comment|/* SBEN = 0, SMOD = 01, LAD = 0 */
r_if
c_cond
(paren
id|pci_id-&gt;device
op_ge
l_int|0x0010
)paren
(brace
multiline_comment|/* YMF 744/754 */
r_if
c_cond
(paren
id|fm_port
(braket
id|dev
)braket
op_eq
l_int|1
)paren
(brace
multiline_comment|/* auto-detect */
id|fm_port
(braket
id|dev
)braket
op_assign
id|pci_resource_start
c_func
(paren
id|pci
comma
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|fm_port
(braket
id|dev
)braket
OG
l_int|0
op_logical_and
(paren
id|fm_res
op_assign
id|request_region
c_func
(paren
id|fm_port
(braket
id|dev
)braket
comma
l_int|4
comma
l_string|&quot;YMFPCI OPL3&quot;
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|legacy_ctrl
op_or_assign
id|YMFPCI_LEGACY_FMEN
suffix:semicolon
id|pci_write_config_word
c_func
(paren
id|pci
comma
id|PCIR_DSXG_FMBASE
comma
id|fm_port
(braket
id|dev
)braket
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mpu_port
(braket
id|dev
)braket
op_eq
l_int|1
)paren
(brace
multiline_comment|/* auto-detect */
id|mpu_port
(braket
id|dev
)braket
op_assign
id|pci_resource_start
c_func
(paren
id|pci
comma
l_int|1
)paren
op_plus
l_int|0x20
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mpu_port
(braket
id|dev
)braket
OG
l_int|0
op_logical_and
(paren
id|mpu_res
op_assign
id|request_region
c_func
(paren
id|mpu_port
(braket
id|dev
)braket
comma
l_int|2
comma
l_string|&quot;YMFPCI MPU401&quot;
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|legacy_ctrl
op_or_assign
id|YMFPCI_LEGACY_MEN
suffix:semicolon
id|pci_write_config_word
c_func
(paren
id|pci
comma
id|PCIR_DSXG_MPU401BASE
comma
id|mpu_port
(braket
id|dev
)braket
)paren
suffix:semicolon
)brace
macro_line|#ifdef SUPPORT_JOYSTICK
r_if
c_cond
(paren
id|joystick_port
(braket
id|dev
)braket
op_eq
l_int|1
)paren
(brace
multiline_comment|/* auto-detect */
id|joystick_port
(braket
id|dev
)braket
op_assign
id|pci_resource_start
c_func
(paren
id|pci
comma
l_int|2
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|joystick_port
(braket
id|dev
)braket
OG
l_int|0
op_logical_and
(paren
id|joystick_res
op_assign
id|request_region
c_func
(paren
id|joystick_port
(braket
id|dev
)braket
comma
l_int|1
comma
l_string|&quot;YMFPCI gameport&quot;
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|legacy_ctrl
op_or_assign
id|YMFPCI_LEGACY_JPEN
suffix:semicolon
id|pci_write_config_word
c_func
(paren
id|pci
comma
id|PCIR_DSXG_JOYBASE
comma
id|joystick_port
(braket
id|dev
)braket
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
r_else
(brace
r_switch
c_cond
(paren
id|fm_port
(braket
id|dev
)braket
)paren
(brace
r_case
l_int|0x388
suffix:colon
id|legacy_ctrl2
op_or_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x398
suffix:colon
id|legacy_ctrl2
op_or_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x3a0
suffix:colon
id|legacy_ctrl2
op_or_assign
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x3a8
suffix:colon
id|legacy_ctrl2
op_or_assign
l_int|3
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|fm_port
(braket
id|dev
)braket
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|fm_port
(braket
id|dev
)braket
OG
l_int|0
op_logical_and
(paren
id|fm_res
op_assign
id|request_region
c_func
(paren
id|fm_port
(braket
id|dev
)braket
comma
l_int|4
comma
l_string|&quot;YMFPCI OPL3&quot;
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|legacy_ctrl
op_or_assign
id|YMFPCI_LEGACY_FMEN
suffix:semicolon
)brace
r_else
(brace
id|legacy_ctrl2
op_and_assign
op_complement
id|YMFPCI_LEGACY2_FMIO
suffix:semicolon
id|fm_port
(braket
id|dev
)braket
op_assign
l_int|0
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|mpu_port
(braket
id|dev
)braket
)paren
(brace
r_case
l_int|0x330
suffix:colon
id|legacy_ctrl2
op_or_assign
l_int|0
op_lshift
l_int|4
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x300
suffix:colon
id|legacy_ctrl2
op_or_assign
l_int|1
op_lshift
l_int|4
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x332
suffix:colon
id|legacy_ctrl2
op_or_assign
l_int|2
op_lshift
l_int|4
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x334
suffix:colon
id|legacy_ctrl2
op_or_assign
l_int|3
op_lshift
l_int|4
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|mpu_port
(braket
id|dev
)braket
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mpu_port
(braket
id|dev
)braket
OG
l_int|0
op_logical_and
(paren
id|mpu_res
op_assign
id|request_region
c_func
(paren
id|mpu_port
(braket
id|dev
)braket
comma
l_int|2
comma
l_string|&quot;YMFPCI MPU401&quot;
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|legacy_ctrl
op_or_assign
id|YMFPCI_LEGACY_MEN
suffix:semicolon
)brace
r_else
(brace
id|legacy_ctrl2
op_and_assign
op_complement
id|YMFPCI_LEGACY2_MPUIO
suffix:semicolon
id|mpu_port
(braket
id|dev
)braket
op_assign
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef SUPPORT_JOYSTICK
r_if
c_cond
(paren
id|joystick_port
(braket
id|dev
)braket
op_eq
l_int|1
)paren
(brace
multiline_comment|/* auto-detect */
r_int
id|p
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
l_int|0x201
suffix:semicolon
id|p
op_le
l_int|0x205
suffix:semicolon
id|p
op_increment
)paren
(brace
r_if
c_cond
(paren
id|p
op_eq
l_int|0x203
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
(paren
id|joystick_res
op_assign
id|request_region
c_func
(paren
id|p
comma
l_int|1
comma
l_string|&quot;YMFPCI gameport&quot;
)paren
)paren
op_ne
l_int|NULL
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|joystick_res
)paren
id|joystick_port
(braket
id|dev
)braket
op_assign
id|p
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|joystick_port
(braket
id|dev
)braket
)paren
(brace
r_case
l_int|0x201
suffix:colon
id|legacy_ctrl2
op_or_assign
l_int|0
op_lshift
l_int|6
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x202
suffix:colon
id|legacy_ctrl2
op_or_assign
l_int|1
op_lshift
l_int|6
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x204
suffix:colon
id|legacy_ctrl2
op_or_assign
l_int|2
op_lshift
l_int|6
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x205
suffix:colon
id|legacy_ctrl2
op_or_assign
l_int|3
op_lshift
l_int|6
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|joystick_port
(braket
id|dev
)braket
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|joystick_res
op_logical_and
id|joystick_port
(braket
id|dev
)braket
OG
l_int|0
)paren
id|joystick_res
op_assign
id|request_region
c_func
(paren
id|joystick_port
(braket
id|dev
)braket
comma
l_int|1
comma
l_string|&quot;YMFPCI gameport&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|joystick_res
)paren
(brace
id|legacy_ctrl
op_or_assign
id|YMFPCI_LEGACY_JPEN
suffix:semicolon
)brace
r_else
(brace
id|legacy_ctrl2
op_and_assign
op_complement
id|YMFPCI_LEGACY2_JSIO
suffix:semicolon
id|joystick_port
(braket
id|dev
)braket
op_assign
l_int|0
suffix:semicolon
)brace
macro_line|#endif
)brace
r_if
c_cond
(paren
id|mpu_res
)paren
(brace
id|legacy_ctrl
op_or_assign
id|YMFPCI_LEGACY_MIEN
suffix:semicolon
id|legacy_ctrl2
op_or_assign
id|YMFPCI_LEGACY2_IMOD
suffix:semicolon
)brace
id|pci_read_config_word
c_func
(paren
id|pci
comma
id|PCIR_DSXG_LEGACY
comma
op_amp
id|old_legacy_ctrl
)paren
suffix:semicolon
id|pci_write_config_word
c_func
(paren
id|pci
comma
id|PCIR_DSXG_LEGACY
comma
id|legacy_ctrl
)paren
suffix:semicolon
id|pci_write_config_word
c_func
(paren
id|pci
comma
id|PCIR_DSXG_ELEGACY
comma
id|legacy_ctrl2
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_ymfpci_create
c_func
(paren
id|card
comma
id|pci
comma
id|old_legacy_ctrl
comma
op_amp
id|chip
)paren
)paren
OL
l_int|0
)paren
(brace
id|snd_card_free
c_func
(paren
id|card
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mpu_res
)paren
(brace
id|release_resource
c_func
(paren
id|mpu_res
)paren
suffix:semicolon
id|kfree_nocheck
c_func
(paren
id|mpu_res
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|fm_res
)paren
(brace
id|release_resource
c_func
(paren
id|fm_res
)paren
suffix:semicolon
id|kfree_nocheck
c_func
(paren
id|fm_res
)paren
suffix:semicolon
)brace
macro_line|#ifdef SUPPORT_JOYSTICK
r_if
c_cond
(paren
id|joystick_res
)paren
(brace
id|release_resource
c_func
(paren
id|joystick_res
)paren
suffix:semicolon
id|kfree_nocheck
c_func
(paren
id|joystick_res
)paren
suffix:semicolon
)brace
macro_line|#endif
r_return
id|err
suffix:semicolon
)brace
id|chip-&gt;fm_res
op_assign
id|fm_res
suffix:semicolon
id|chip-&gt;mpu_res
op_assign
id|mpu_res
suffix:semicolon
macro_line|#ifdef SUPPORT_JOYSTICK
id|chip-&gt;joystick_res
op_assign
id|joystick_res
suffix:semicolon
macro_line|#endif
id|strcpy
c_func
(paren
id|card-&gt;driver
comma
id|str
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|card-&gt;shortname
comma
l_string|&quot;Yamaha DS-XG (%s)&quot;
comma
id|str
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|card-&gt;longname
comma
l_string|&quot;%s at 0x%lx, irq %i&quot;
comma
id|card-&gt;shortname
comma
id|chip-&gt;reg_area_phys
comma
id|chip-&gt;irq
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_ymfpci_pcm
c_func
(paren
id|chip
comma
l_int|0
comma
l_int|NULL
)paren
)paren
OL
l_int|0
)paren
(brace
id|snd_card_free
c_func
(paren
id|card
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_ymfpci_pcm_spdif
c_func
(paren
id|chip
comma
l_int|1
comma
l_int|NULL
)paren
)paren
OL
l_int|0
)paren
(brace
id|snd_card_free
c_func
(paren
id|card
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_ymfpci_pcm_4ch
c_func
(paren
id|chip
comma
l_int|2
comma
l_int|NULL
)paren
)paren
OL
l_int|0
)paren
(brace
id|snd_card_free
c_func
(paren
id|card
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_ymfpci_pcm2
c_func
(paren
id|chip
comma
l_int|3
comma
l_int|NULL
)paren
)paren
OL
l_int|0
)paren
(brace
id|snd_card_free
c_func
(paren
id|card
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_ymfpci_mixer
c_func
(paren
id|chip
comma
id|rear_switch
(braket
id|dev
)braket
)paren
)paren
OL
l_int|0
)paren
(brace
id|snd_card_free
c_func
(paren
id|card
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_ymfpci_timer
c_func
(paren
id|chip
comma
l_int|0
)paren
)paren
OL
l_int|0
)paren
(brace
id|snd_card_free
c_func
(paren
id|card
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
r_if
c_cond
(paren
id|chip-&gt;mpu_res
)paren
(brace
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_mpu401_uart_new
c_func
(paren
id|card
comma
l_int|0
comma
id|MPU401_HW_YMFPCI
comma
id|mpu_port
(braket
id|dev
)braket
comma
l_int|1
comma
id|pci-&gt;irq
comma
l_int|0
comma
op_amp
id|chip-&gt;rawmidi
)paren
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;ymfpci: cannot initialize MPU401 at 0x%lx, skipping...&bslash;n&quot;
comma
id|mpu_port
(braket
id|dev
)braket
)paren
suffix:semicolon
id|legacy_ctrl
op_and_assign
op_complement
id|YMFPCI_LEGACY_MIEN
suffix:semicolon
multiline_comment|/* disable MPU401 irq */
id|pci_write_config_word
c_func
(paren
id|pci
comma
id|PCIR_DSXG_LEGACY
comma
id|legacy_ctrl
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|chip-&gt;fm_res
)paren
(brace
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_opl3_create
c_func
(paren
id|card
comma
id|fm_port
(braket
id|dev
)braket
comma
id|fm_port
(braket
id|dev
)braket
op_plus
l_int|2
comma
id|OPL3_HW_OPL3
comma
l_int|1
comma
op_amp
id|opl3
)paren
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;ymfpci: cannot initialize FM OPL3 at 0x%lx, skipping...&bslash;n&quot;
comma
id|fm_port
(braket
id|dev
)braket
)paren
suffix:semicolon
id|legacy_ctrl
op_and_assign
op_complement
id|YMFPCI_LEGACY_FMEN
suffix:semicolon
id|pci_write_config_word
c_func
(paren
id|pci
comma
id|PCIR_DSXG_LEGACY
comma
id|legacy_ctrl
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_opl3_hwdep_new
c_func
(paren
id|opl3
comma
l_int|0
comma
l_int|1
comma
l_int|NULL
)paren
)paren
OL
l_int|0
)paren
(brace
id|snd_card_free
c_func
(paren
id|card
)paren
suffix:semicolon
id|snd_printk
c_func
(paren
l_string|&quot;cannot create opl3 hwdep&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
)brace
macro_line|#ifdef SUPPORT_JOYSTICK
r_if
c_cond
(paren
id|chip-&gt;joystick_res
)paren
(brace
id|chip-&gt;gameport.io
op_assign
id|joystick_port
(braket
id|dev
)braket
suffix:semicolon
id|gameport_register_port
c_func
(paren
op_amp
id|chip-&gt;gameport
)paren
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_card_register
c_func
(paren
id|card
)paren
)paren
OL
l_int|0
)paren
(brace
id|snd_card_free
c_func
(paren
id|card
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
id|pci_set_drvdata
c_func
(paren
id|pci
comma
id|card
)paren
suffix:semicolon
id|dev
op_increment
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_card_ymfpci_remove
r_static
r_void
id|__devexit
id|snd_card_ymfpci_remove
c_func
(paren
r_struct
id|pci_dev
op_star
id|pci
)paren
(brace
id|snd_card_free
c_func
(paren
id|pci_get_drvdata
c_func
(paren
id|pci
)paren
)paren
suffix:semicolon
id|pci_set_drvdata
c_func
(paren
id|pci
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|variable|driver
r_static
r_struct
id|pci_driver
id|driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;Yamaha DS-XG PCI&quot;
comma
dot
id|id_table
op_assign
id|snd_ymfpci_ids
comma
dot
id|probe
op_assign
id|snd_card_ymfpci_probe
comma
dot
id|remove
op_assign
id|__devexit_p
c_func
(paren
id|snd_card_ymfpci_remove
)paren
comma
id|SND_PCI_PM_CALLBACKS
)brace
suffix:semicolon
DECL|function|alsa_card_ymfpci_init
r_static
r_int
id|__init
id|alsa_card_ymfpci_init
c_func
(paren
r_void
)paren
(brace
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|pci_module_init
c_func
(paren
op_amp
id|driver
)paren
)paren
OL
l_int|0
)paren
(brace
macro_line|#ifdef MODULE
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Yamaha DS-XG PCI soundcard not found or device busy&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
r_return
id|err
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|alsa_card_ymfpci_exit
r_static
r_void
id|__exit
id|alsa_card_ymfpci_exit
c_func
(paren
r_void
)paren
(brace
id|pci_unregister_driver
c_func
(paren
op_amp
id|driver
)paren
suffix:semicolon
)brace
id|module_init
c_func
(paren
id|alsa_card_ymfpci_init
)paren
id|module_exit
c_func
(paren
id|alsa_card_ymfpci_exit
)paren
eof
