multiline_comment|/* Driver for USB Mass Storage compliant devices&n; * Ununsual Devices File&n; *&n; * $Id: unusual_devs.h,v 1.32 2002/02/25 02:41:24 mdharm Exp $&n; *&n; * Current development and maintenance by:&n; *   (c) 2000-2002 Matthew Dharm (mdharm-usb@one-eyed-alien.net)&n; *&n; * Initial work by:&n; *   (c) 2000 Adam J. Richter (adam@yggdrasil.com), Yggdrasil Computing, Inc.&n; *&n; * Please see http://www.one-eyed-alien.net/~mdharm/linux-usb for more&n; * information about this driver.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2, or (at your option) any&n; * later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; * General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write to the Free Software Foundation, Inc.,&n; * 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
multiline_comment|/* IMPORTANT NOTE: This file must be included in another file which does&n; * the following thing for it to work:&n; * The macro UNUSUAL_DEV() must be defined before this file is included&n; */
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* If you edit this file, please try to keep it sorted first by VendorID,&n; * then by ProductID.&n; */
id|UNUSUAL_DEV
c_func
(paren
l_int|0x03ee
comma
l_int|0x0000
comma
l_int|0x0000
comma
l_int|0x0245
comma
l_string|&quot;Mitsumi&quot;
comma
l_string|&quot;CD-R/RW Drive&quot;
comma
id|US_SC_8020
comma
id|US_PR_CBI
comma
l_int|NULL
comma
l_int|0
)paren
comma
id|UNUSUAL_DEV
c_func
(paren
l_int|0x03ee
comma
l_int|0x6901
comma
l_int|0x0000
comma
l_int|0x0100
comma
l_string|&quot;Mitsumi&quot;
comma
l_string|&quot;USB FDD&quot;
comma
id|US_SC_UFI
comma
id|US_PR_CBI
comma
l_int|NULL
comma
id|US_FL_SINGLE_LUN
)paren
comma
id|UNUSUAL_DEV
c_func
(paren
l_int|0x03f0
comma
l_int|0x0107
comma
l_int|0x0200
comma
l_int|0x0200
comma
l_string|&quot;HP&quot;
comma
l_string|&quot;CD-Writer+&quot;
comma
id|US_SC_8070
comma
id|US_PR_CB
comma
l_int|NULL
comma
l_int|0
)paren
comma
macro_line|#ifdef CONFIG_USB_STORAGE_HP8200e
id|UNUSUAL_DEV
c_func
(paren
l_int|0x03f0
comma
l_int|0x0207
comma
l_int|0x0001
comma
l_int|0x0001
comma
l_string|&quot;HP&quot;
comma
l_string|&quot;CD-Writer+ 8200e&quot;
comma
id|US_SC_8070
comma
id|US_PR_SCM_ATAPI
comma
id|init_8200e
comma
l_int|0
)paren
comma
id|UNUSUAL_DEV
c_func
(paren
l_int|0x03f0
comma
l_int|0x0307
comma
l_int|0x0001
comma
l_int|0x0001
comma
l_string|&quot;HP&quot;
comma
l_string|&quot;CD-Writer+ CD-4e&quot;
comma
id|US_SC_8070
comma
id|US_PR_SCM_ATAPI
comma
id|init_8200e
comma
l_int|0
)paren
comma
macro_line|#endif
multiline_comment|/* Deduced by Jonathan Woithe &lt;jwoithe@physics.adelaide.edu.au&gt;&n; * Entry needed for flags: US_FL_FIX_INQUIRY because initial inquiry message&n; * always fails and confuses drive; without US_FL_START_STOP, drive accesses&n; * (read or write) all fail.&n; */
id|UNUSUAL_DEV
c_func
(paren
l_int|0x0411
comma
l_int|0x001c
comma
l_int|0x0113
comma
l_int|0x0113
comma
l_string|&quot;Buffalo&quot;
comma
l_string|&quot;DUB-P40G HDD&quot;
comma
id|US_SC_SCSI
comma
id|US_PR_BULK
comma
l_int|NULL
comma
id|US_FL_FIX_INQUIRY
op_or
id|US_FL_START_STOP
)paren
comma
macro_line|#ifdef CONFIG_USB_STORAGE_DPCM
id|UNUSUAL_DEV
c_func
(paren
l_int|0x0436
comma
l_int|0x0005
comma
l_int|0x0100
comma
l_int|0x0100
comma
l_string|&quot;Microtech&quot;
comma
l_string|&quot;CameraMate (DPCM_USB)&quot;
comma
id|US_SC_SCSI
comma
id|US_PR_DPCM_USB
comma
l_int|NULL
comma
id|US_FL_START_STOP
)paren
comma
macro_line|#endif
multiline_comment|/* Made with the help of Edd Dumbill &lt;edd@usefulinc.com&gt; */
id|UNUSUAL_DEV
c_func
(paren
l_int|0x0451
comma
l_int|0x5409
comma
l_int|0x0001
comma
l_int|0x0001
comma
l_string|&quot;Frontier Labs&quot;
comma
l_string|&quot;Nex II Digital&quot;
comma
id|US_SC_SCSI
comma
id|US_PR_BULK
comma
l_int|NULL
comma
id|US_FL_START_STOP
)paren
comma
multiline_comment|/* Reported by Paul Stewart &lt;stewart@wetlogic.net&gt;&n; * This entry is needed because the device reports Sub=ff */
id|UNUSUAL_DEV
c_func
(paren
l_int|0x04a4
comma
l_int|0x0004
comma
l_int|0x0001
comma
l_int|0x0001
comma
l_string|&quot;Hitachi&quot;
comma
l_string|&quot;DVD-CAM DZ-MV100A Camcorder&quot;
comma
id|US_SC_SCSI
comma
id|US_PR_CB
comma
l_int|NULL
comma
id|US_FL_SINGLE_LUN
)paren
comma
id|UNUSUAL_DEV
c_func
(paren
l_int|0x04cb
comma
l_int|0x0100
comma
l_int|0x0000
comma
l_int|0x2210
comma
l_string|&quot;Fujifilm&quot;
comma
l_string|&quot;FinePix 1400Zoom&quot;
comma
id|US_SC_8070
comma
id|US_PR_CBI
comma
l_int|NULL
comma
id|US_FL_FIX_INQUIRY
)paren
comma
multiline_comment|/* Reported by Peter W&#xfffd;chtler &lt;pwaechtler@loewe-komp.de&gt;&n; * The device needs the flags only.&n; */
id|UNUSUAL_DEV
c_func
(paren
l_int|0x04ce
comma
l_int|0x0002
comma
l_int|0x0074
comma
l_int|0x0074
comma
l_string|&quot;ScanLogic&quot;
comma
l_string|&quot;SL11R-IDE&quot;
comma
id|US_SC_SCSI
comma
id|US_PR_BULK
comma
l_int|NULL
comma
id|US_FL_FIX_INQUIRY
)paren
comma
multiline_comment|/* Reported by Kriston Fincher &lt;kriston@airmail.net&gt;&n; * Patch submitted by Sean Millichamp &lt;sean@bruenor.org&gt;&n; * This is to support the Panasonic PalmCam PV-SD4090&n; * This entry is needed because the device reports Sub=ff &n; */
id|UNUSUAL_DEV
c_func
(paren
l_int|0x04da
comma
l_int|0x0901
comma
l_int|0x0100
comma
l_int|0x0200
comma
l_string|&quot;Panasonic&quot;
comma
l_string|&quot;LS-120 Camera&quot;
comma
id|US_SC_UFI
comma
id|US_PR_CBI
comma
l_int|NULL
comma
l_int|0
)paren
comma
multiline_comment|/* Reported by Peter W&#xfffd;chtler &lt;pwaechtler@loewe-komp.de&gt; */
id|UNUSUAL_DEV
c_func
(paren
l_int|0x04ce
comma
l_int|0x0002
comma
l_int|0x0074
comma
l_int|0x0074
comma
l_string|&quot;ScanLogic&quot;
comma
l_string|&quot;SL11R-IDE 0049SQFP-1.2 A002&quot;
comma
id|US_SC_SCSI
comma
id|US_PR_BULK
comma
l_int|NULL
comma
id|US_FL_FIX_INQUIRY
)paren
comma
multiline_comment|/* Most of the following entries were developed with the help of&n; * Shuttle/SCM directly.&n; */
id|UNUSUAL_DEV
c_func
(paren
l_int|0x04e6
comma
l_int|0x0001
comma
l_int|0x0200
comma
l_int|0x0200
comma
l_string|&quot;Matshita&quot;
comma
l_string|&quot;LS-120&quot;
comma
id|US_SC_8020
comma
id|US_PR_CB
comma
l_int|NULL
comma
l_int|0
)paren
comma
id|UNUSUAL_DEV
c_func
(paren
l_int|0x04e6
comma
l_int|0x0002
comma
l_int|0x0100
comma
l_int|0x0100
comma
l_string|&quot;Shuttle&quot;
comma
l_string|&quot;eUSCSI Bridge&quot;
comma
id|US_SC_SCSI
comma
id|US_PR_BULK
comma
id|usb_stor_euscsi_init
comma
id|US_FL_SCM_MULT_TARG
)paren
comma
macro_line|#ifdef CONFIG_USB_STORAGE_SDDR09
id|UNUSUAL_DEV
c_func
(paren
l_int|0x04e6
comma
l_int|0x0003
comma
l_int|0x0000
comma
l_int|0x9999
comma
l_string|&quot;Sandisk&quot;
comma
l_string|&quot;ImageMate SDDR09&quot;
comma
id|US_SC_SCSI
comma
id|US_PR_EUSB_SDDR09
comma
l_int|NULL
comma
id|US_FL_SINGLE_LUN
op_or
id|US_FL_START_STOP
)paren
comma
multiline_comment|/* This entry is from Andries.Brouwer@cwi.nl */
id|UNUSUAL_DEV
c_func
(paren
l_int|0x04e6
comma
l_int|0x0005
comma
l_int|0x0100
comma
l_int|0x0208
comma
l_string|&quot;SCM Microsystems&quot;
comma
l_string|&quot;eUSB SmartMedia / CompactFlash Adapter&quot;
comma
id|US_SC_SCSI
comma
id|US_PR_DPCM_USB
comma
id|sddr09_init
comma
id|US_FL_START_STOP
)paren
comma
macro_line|#endif
id|UNUSUAL_DEV
c_func
(paren
l_int|0x04e6
comma
l_int|0x0006
comma
l_int|0x0100
comma
l_int|0x0205
comma
l_string|&quot;Shuttle&quot;
comma
l_string|&quot;eUSB MMC Adapter&quot;
comma
id|US_SC_SCSI
comma
id|US_PR_CB
comma
l_int|NULL
comma
id|US_FL_SINGLE_LUN
)paren
comma
id|UNUSUAL_DEV
c_func
(paren
l_int|0x04e6
comma
l_int|0x0007
comma
l_int|0x0100
comma
l_int|0x0200
comma
l_string|&quot;Sony&quot;
comma
l_string|&quot;Hifd&quot;
comma
id|US_SC_SCSI
comma
id|US_PR_CB
comma
l_int|NULL
comma
id|US_FL_SINGLE_LUN
)paren
comma
id|UNUSUAL_DEV
c_func
(paren
l_int|0x04e6
comma
l_int|0x0009
comma
l_int|0x0200
comma
l_int|0x0200
comma
l_string|&quot;Shuttle&quot;
comma
l_string|&quot;eUSB ATA/ATAPI Adapter&quot;
comma
id|US_SC_8020
comma
id|US_PR_CB
comma
l_int|NULL
comma
l_int|0
)paren
comma
id|UNUSUAL_DEV
c_func
(paren
l_int|0x04e6
comma
l_int|0x000a
comma
l_int|0x0200
comma
l_int|0x0200
comma
l_string|&quot;Shuttle&quot;
comma
l_string|&quot;eUSB CompactFlash Adapter&quot;
comma
id|US_SC_8020
comma
id|US_PR_CB
comma
l_int|NULL
comma
l_int|0
)paren
comma
id|UNUSUAL_DEV
c_func
(paren
l_int|0x04e6
comma
l_int|0x000B
comma
l_int|0x0100
comma
l_int|0x0100
comma
l_string|&quot;Shuttle&quot;
comma
l_string|&quot;eUSCSI Bridge&quot;
comma
id|US_SC_SCSI
comma
id|US_PR_BULK
comma
id|usb_stor_euscsi_init
comma
id|US_FL_SCM_MULT_TARG
)paren
comma
id|UNUSUAL_DEV
c_func
(paren
l_int|0x04e6
comma
l_int|0x000C
comma
l_int|0x0100
comma
l_int|0x0100
comma
l_string|&quot;Shuttle&quot;
comma
l_string|&quot;eUSCSI Bridge&quot;
comma
id|US_SC_SCSI
comma
id|US_PR_BULK
comma
id|usb_stor_euscsi_init
comma
id|US_FL_SCM_MULT_TARG
)paren
comma
id|UNUSUAL_DEV
c_func
(paren
l_int|0x04e6
comma
l_int|0x0101
comma
l_int|0x0200
comma
l_int|0x0200
comma
l_string|&quot;Shuttle&quot;
comma
l_string|&quot;CD-RW Device&quot;
comma
id|US_SC_8020
comma
id|US_PR_CB
comma
l_int|NULL
comma
l_int|0
)paren
comma
multiline_comment|/* Reported by Bob Sass &lt;rls@vectordb.com&gt; -- only rev 1.33 tested */
id|UNUSUAL_DEV
c_func
(paren
l_int|0x050d
comma
l_int|0x0115
comma
l_int|0x0133
comma
l_int|0x0133
comma
l_string|&quot;Belkin&quot;
comma
l_string|&quot;USB SCSI Adaptor&quot;
comma
id|US_SC_SCSI
comma
id|US_PR_BULK
comma
id|usb_stor_euscsi_init
comma
id|US_FL_SCM_MULT_TARG
)paren
comma
multiline_comment|/* Iomega Clik! Drive &n; * Reported by David Chatenay &lt;dchatenay@hotmail.com&gt;&n; * The reason this is needed is not fully known.&n; */
id|UNUSUAL_DEV
c_func
(paren
l_int|0x0525
comma
l_int|0xa140
comma
l_int|0x0100
comma
l_int|0x0100
comma
l_string|&quot;Iomega&quot;
comma
l_string|&quot;USB Clik! 40&quot;
comma
id|US_SC_8070
comma
id|US_PR_BULK
comma
l_int|NULL
comma
id|US_FL_FIX_INQUIRY
op_or
id|US_FL_START_STOP
)paren
comma
multiline_comment|/* This entry is needed because the device reports Sub=ff */
id|UNUSUAL_DEV
c_func
(paren
l_int|0x054c
comma
l_int|0x0010
comma
l_int|0x0106
comma
l_int|0x0422
comma
l_string|&quot;Sony&quot;
comma
l_string|&quot;DSC-S30/S70/S75/505V/F505/F707&quot;
comma
id|US_SC_SCSI
comma
id|US_PR_CB
comma
l_int|NULL
comma
id|US_FL_SINGLE_LUN
op_or
id|US_FL_START_STOP
op_or
id|US_FL_MODE_XLATE
)paren
comma
multiline_comment|/* Reported by wim@geeks.nl */
id|UNUSUAL_DEV
c_func
(paren
l_int|0x054c
comma
l_int|0x0025
comma
l_int|0x0100
comma
l_int|0x0100
comma
l_string|&quot;Sony&quot;
comma
l_string|&quot;Memorystick NW-MS7&quot;
comma
id|US_SC_UFI
comma
id|US_PR_CB
comma
l_int|NULL
comma
id|US_FL_SINGLE_LUN
op_or
id|US_FL_START_STOP
)paren
comma
id|UNUSUAL_DEV
c_func
(paren
l_int|0x054c
comma
l_int|0x002d
comma
l_int|0x0100
comma
l_int|0x0100
comma
l_string|&quot;Sony&quot;
comma
l_string|&quot;Memorystick MSAC-US1&quot;
comma
id|US_SC_UFI
comma
id|US_PR_CB
comma
l_int|NULL
comma
id|US_FL_SINGLE_LUN
op_or
id|US_FL_START_STOP
)paren
comma
multiline_comment|/* Submitted by Klaus Mueller &lt;k.mueller@intershop.de&gt; */
id|UNUSUAL_DEV
c_func
(paren
l_int|0x054c
comma
l_int|0x002e
comma
l_int|0x0106
comma
l_int|0x0310
comma
l_string|&quot;Sony&quot;
comma
l_string|&quot;Handycam&quot;
comma
id|US_SC_SCSI
comma
id|US_PR_CB
comma
l_int|NULL
comma
id|US_FL_SINGLE_LUN
op_or
id|US_FL_START_STOP
op_or
id|US_FL_MODE_XLATE
)paren
comma
id|UNUSUAL_DEV
c_func
(paren
l_int|0x054c
comma
l_int|0x0032
comma
l_int|0x0000
comma
l_int|0x9999
comma
l_string|&quot;Sony&quot;
comma
l_string|&quot;Memorystick MSC-U01N&quot;
comma
id|US_SC_UFI
comma
id|US_PR_CB
comma
l_int|NULL
comma
id|US_FL_SINGLE_LUN
op_or
id|US_FL_START_STOP
)paren
comma
multiline_comment|/* Submitted by Nathan Babb &lt;nathan@lexi.com&gt; */
id|UNUSUAL_DEV
c_func
(paren
l_int|0x054c
comma
l_int|0x006d
comma
l_int|0x0000
comma
l_int|0x9999
comma
l_string|&quot;Sony&quot;
comma
l_string|&quot;PEG Mass Storage&quot;
comma
id|US_SC_8070
comma
id|US_PR_CBI
comma
l_int|NULL
comma
id|US_FL_FIX_INQUIRY
)paren
comma
id|UNUSUAL_DEV
c_func
(paren
l_int|0x057b
comma
l_int|0x0000
comma
l_int|0x0000
comma
l_int|0x0299
comma
l_string|&quot;Y-E Data&quot;
comma
l_string|&quot;Flashbuster-U&quot;
comma
id|US_SC_UFI
comma
id|US_PR_CB
comma
l_int|NULL
comma
id|US_FL_SINGLE_LUN
)paren
comma
id|UNUSUAL_DEV
c_func
(paren
l_int|0x057b
comma
l_int|0x0000
comma
l_int|0x0300
comma
l_int|0x9999
comma
l_string|&quot;Y-E Data&quot;
comma
l_string|&quot;Flashbuster-U&quot;
comma
id|US_SC_UFI
comma
id|US_PR_CBI
comma
l_int|NULL
comma
id|US_FL_SINGLE_LUN
)paren
comma
id|UNUSUAL_DEV
c_func
(paren
l_int|0x059f
comma
l_int|0xa601
comma
l_int|0x0200
comma
l_int|0x0200
comma
l_string|&quot;LaCie&quot;
comma
l_string|&quot;USB Hard Disk&quot;
comma
id|US_SC_RBC
comma
id|US_PR_CB
comma
l_int|NULL
comma
l_int|0
)paren
comma
macro_line|#ifdef CONFIG_USB_STORAGE_ISD200
id|UNUSUAL_DEV
c_func
(paren
l_int|0x05ab
comma
l_int|0x0031
comma
l_int|0x0100
comma
l_int|0x0110
comma
l_string|&quot;In-System&quot;
comma
l_string|&quot;USB/IDE Bridge (ATA/ATAPI)&quot;
comma
id|US_SC_ISD200
comma
id|US_PR_BULK
comma
id|isd200_Initialization
comma
l_int|0
)paren
comma
id|UNUSUAL_DEV
c_func
(paren
l_int|0x05ab
comma
l_int|0x0301
comma
l_int|0x0100
comma
l_int|0x0110
comma
l_string|&quot;In-System&quot;
comma
l_string|&quot;Portable USB Harddrive V2&quot;
comma
id|US_SC_ISD200
comma
id|US_PR_BULK
comma
id|isd200_Initialization
comma
l_int|0
)paren
comma
id|UNUSUAL_DEV
c_func
(paren
l_int|0x05ab
comma
l_int|0x0351
comma
l_int|0x0100
comma
l_int|0x0110
comma
l_string|&quot;In-System&quot;
comma
l_string|&quot;Portable USB Harddrive V2&quot;
comma
id|US_SC_ISD200
comma
id|US_PR_BULK
comma
id|isd200_Initialization
comma
l_int|0
)paren
comma
id|UNUSUAL_DEV
c_func
(paren
l_int|0x05ab
comma
l_int|0x5701
comma
l_int|0x0100
comma
l_int|0x0110
comma
l_string|&quot;In-System&quot;
comma
l_string|&quot;USB Storage Adapter V2&quot;
comma
id|US_SC_ISD200
comma
id|US_PR_BULK
comma
id|isd200_Initialization
comma
l_int|0
)paren
comma
id|UNUSUAL_DEV
c_func
(paren
l_int|0x054c
comma
l_int|0x002b
comma
l_int|0x0100
comma
l_int|0x0110
comma
l_string|&quot;Sony&quot;
comma
l_string|&quot;Portable USB Harddrive V2&quot;
comma
id|US_SC_ISD200
comma
id|US_PR_BULK
comma
id|isd200_Initialization
comma
l_int|0
)paren
comma
macro_line|#endif
macro_line|#ifdef CONFIG_USB_STORAGE_JUMPSHOT
id|UNUSUAL_DEV
c_func
(paren
l_int|0x05dc
comma
l_int|0x0001
comma
l_int|0x0000
comma
l_int|0x0001
comma
l_string|&quot;Lexar&quot;
comma
l_string|&quot;Jumpshot USB CF Reader&quot;
comma
id|US_SC_SCSI
comma
id|US_PR_JUMPSHOT
comma
l_int|NULL
comma
id|US_FL_MODE_XLATE
)paren
comma
macro_line|#endif
multiline_comment|/* Reported by Blake Matheny &lt;bmatheny@purdue.edu&gt; */
id|UNUSUAL_DEV
c_func
(paren
l_int|0x05dc
comma
l_int|0xb002
comma
l_int|0x0000
comma
l_int|0x0113
comma
l_string|&quot;Lexar&quot;
comma
l_string|&quot;USB CF Reader&quot;
comma
id|US_SC_SCSI
comma
id|US_PR_BULK
comma
l_int|NULL
comma
id|US_FL_FIX_INQUIRY
)paren
comma
multiline_comment|/* Reported by Carlos Villegas &lt;cav@uniscope.co.jp&gt;&n; * This device needs an INQUIRY of exactly 36-bytes to function.&n; * That is the only reason this entry is needed.&n; */
id|UNUSUAL_DEV
c_func
(paren
l_int|0x05e3
comma
l_int|0x0700
comma
l_int|0x0000
comma
l_int|0xffff
comma
l_string|&quot;SIIG&quot;
comma
l_string|&quot;CompactFlash Card Reader&quot;
comma
id|US_SC_SCSI
comma
id|US_PR_BULK
comma
l_int|NULL
comma
id|US_FL_FIX_INQUIRY
)paren
comma
multiline_comment|/* Reported by Peter Marks &lt;peter.marks@turner.com&gt;&n; * Like the SIIG unit above, this unit needs an INQUIRY to ask for exactly&n; * 36 bytes of data.  No more, no less. That is the only reason this entry&n; * is needed.&n; */
id|UNUSUAL_DEV
c_func
(paren
l_int|0x05e3
comma
l_int|0x0702
comma
l_int|0x0000
comma
l_int|0xffff
comma
l_string|&quot;EagleTec&quot;
comma
l_string|&quot;External Hard Disk&quot;
comma
id|US_SC_SCSI
comma
id|US_PR_BULK
comma
l_int|NULL
comma
id|US_FL_FIX_INQUIRY
)paren
comma
id|UNUSUAL_DEV
c_func
(paren
l_int|0x05e3
comma
l_int|0x0700
comma
l_int|0x0000
comma
l_int|0x9999
comma
l_string|&quot;Unknown&quot;
comma
l_string|&quot;GL641USB based CF Card reader&quot;
comma
id|US_SC_SCSI
comma
id|US_PR_BULK
comma
l_int|NULL
comma
id|US_FL_FIX_INQUIRY
op_or
id|US_FL_MODE_XLATE
)paren
comma
id|UNUSUAL_DEV
c_func
(paren
l_int|0x0644
comma
l_int|0x0000
comma
l_int|0x0100
comma
l_int|0x0100
comma
l_string|&quot;TEAC&quot;
comma
l_string|&quot;Floppy Drive&quot;
comma
id|US_SC_UFI
comma
id|US_PR_CB
comma
l_int|NULL
comma
l_int|0
)paren
comma
macro_line|#ifdef CONFIG_USB_STORAGE_SDDR09
id|UNUSUAL_DEV
c_func
(paren
l_int|0x066b
comma
l_int|0x0105
comma
l_int|0x0100
comma
l_int|0x0100
comma
l_string|&quot;Olympus&quot;
comma
l_string|&quot;Camedia MAUSB-2&quot;
comma
id|US_SC_SCSI
comma
id|US_PR_EUSB_SDDR09
comma
l_int|NULL
comma
id|US_FL_SINGLE_LUN
op_or
id|US_FL_START_STOP
)paren
comma
macro_line|#endif
multiline_comment|/* Submitted by kedar@centillium&n; * Needed for START_STOP flag, but that is unconfirmed */
id|UNUSUAL_DEV
c_func
(paren
l_int|0x0686
comma
l_int|0x4006
comma
l_int|0x0001
comma
l_int|0x0001
comma
l_string|&quot;Minolta&quot;
comma
l_string|&quot;Dimage S304&quot;
comma
id|US_SC_SCSI
comma
id|US_PR_BULK
comma
l_int|NULL
comma
id|US_FL_START_STOP
)paren
comma
multiline_comment|/* Submitted by f.brugmans@hccnet.nl&n; * Needed for START_STOP flag */
id|UNUSUAL_DEV
c_func
(paren
l_int|0x0686
comma
l_int|0x4007
comma
l_int|0x0001
comma
l_int|0x0001
comma
l_string|&quot;Minolta&quot;
comma
l_string|&quot;Dimage S304&quot;
comma
id|US_SC_SCSI
comma
id|US_PR_BULK
comma
l_int|NULL
comma
id|US_FL_START_STOP
)paren
comma
id|UNUSUAL_DEV
c_func
(paren
l_int|0x0693
comma
l_int|0x0002
comma
l_int|0x0100
comma
l_int|0x0100
comma
l_string|&quot;Hagiwara&quot;
comma
l_string|&quot;FlashGate SmartMedia&quot;
comma
id|US_SC_SCSI
comma
id|US_PR_BULK
comma
l_int|NULL
comma
l_int|0
)paren
comma
id|UNUSUAL_DEV
c_func
(paren
l_int|0x0693
comma
l_int|0x0005
comma
l_int|0x0100
comma
l_int|0x0100
comma
l_string|&quot;Hagiwara&quot;
comma
l_string|&quot;Flashgate&quot;
comma
id|US_SC_SCSI
comma
id|US_PR_BULK
comma
l_int|NULL
comma
l_int|0
)paren
comma
id|UNUSUAL_DEV
c_func
(paren
l_int|0x0781
comma
l_int|0x0001
comma
l_int|0x0200
comma
l_int|0x0200
comma
l_string|&quot;Sandisk&quot;
comma
l_string|&quot;ImageMate SDDR-05a&quot;
comma
id|US_SC_SCSI
comma
id|US_PR_CB
comma
l_int|NULL
comma
id|US_FL_SINGLE_LUN
op_or
id|US_FL_START_STOP
)paren
comma
id|UNUSUAL_DEV
c_func
(paren
l_int|0x0781
comma
l_int|0x0002
comma
l_int|0x0009
comma
l_int|0x0009
comma
l_string|&quot;Sandisk&quot;
comma
l_string|&quot;ImageMate SDDR-31&quot;
comma
id|US_SC_SCSI
comma
id|US_PR_BULK
comma
l_int|NULL
comma
id|US_FL_IGNORE_SER
)paren
comma
id|UNUSUAL_DEV
c_func
(paren
l_int|0x0781
comma
l_int|0x0100
comma
l_int|0x0100
comma
l_int|0x0100
comma
l_string|&quot;Sandisk&quot;
comma
l_string|&quot;ImageMate SDDR-12&quot;
comma
id|US_SC_SCSI
comma
id|US_PR_CB
comma
l_int|NULL
comma
id|US_FL_SINGLE_LUN
)paren
comma
macro_line|#ifdef CONFIG_USB_STORAGE_SDDR09
id|UNUSUAL_DEV
c_func
(paren
l_int|0x0781
comma
l_int|0x0200
comma
l_int|0x0000
comma
l_int|0x9999
comma
l_string|&quot;Sandisk&quot;
comma
l_string|&quot;ImageMate SDDR-09&quot;
comma
id|US_SC_SCSI
comma
id|US_PR_EUSB_SDDR09
comma
l_int|NULL
comma
id|US_FL_SINGLE_LUN
op_or
id|US_FL_START_STOP
)paren
comma
macro_line|#endif
macro_line|#ifdef CONFIG_USB_STORAGE_FREECOM
id|UNUSUAL_DEV
c_func
(paren
l_int|0x07ab
comma
l_int|0xfc01
comma
l_int|0x0000
comma
l_int|0x9999
comma
l_string|&quot;Freecom&quot;
comma
l_string|&quot;USB-IDE&quot;
comma
id|US_SC_QIC
comma
id|US_PR_FREECOM
comma
id|freecom_init
comma
l_int|0
)paren
comma
macro_line|#endif
id|UNUSUAL_DEV
c_func
(paren
l_int|0x07af
comma
l_int|0x0004
comma
l_int|0x0100
comma
l_int|0x0133
comma
l_string|&quot;Microtech&quot;
comma
l_string|&quot;USB-SCSI-DB25&quot;
comma
id|US_SC_SCSI
comma
id|US_PR_BULK
comma
id|usb_stor_euscsi_init
comma
id|US_FL_SCM_MULT_TARG
)paren
comma
id|UNUSUAL_DEV
c_func
(paren
l_int|0x07af
comma
l_int|0x0005
comma
l_int|0x0100
comma
l_int|0x0100
comma
l_string|&quot;Microtech&quot;
comma
l_string|&quot;USB-SCSI-HD50&quot;
comma
id|US_SC_SCSI
comma
id|US_PR_BULK
comma
id|usb_stor_euscsi_init
comma
id|US_FL_SCM_MULT_TARG
)paren
comma
macro_line|#ifdef CONFIG_USB_STORAGE_DPCM
id|UNUSUAL_DEV
c_func
(paren
l_int|0x07af
comma
l_int|0x0006
comma
l_int|0x0100
comma
l_int|0x0100
comma
l_string|&quot;Microtech&quot;
comma
l_string|&quot;CameraMate (DPCM_USB)&quot;
comma
id|US_SC_SCSI
comma
id|US_PR_DPCM_USB
comma
l_int|NULL
comma
id|US_FL_START_STOP
)paren
comma
macro_line|#endif
macro_line|#ifdef CONFIG_USB_STORAGE_DATAFAB
id|UNUSUAL_DEV
c_func
(paren
l_int|0x07c4
comma
l_int|0xa000
comma
l_int|0x0000
comma
l_int|0x0015
comma
l_string|&quot;Datafab&quot;
comma
l_string|&quot;MDCFE-B USB CF Reader&quot;
comma
id|US_SC_SCSI
comma
id|US_PR_DATAFAB
comma
l_int|NULL
comma
id|US_FL_MODE_XLATE
)paren
comma
multiline_comment|/*&n;&t; * The following Datafab-based devices may or may not work&n;&t; * using the current driver...the 0xffff is arbitrary since I&n;&t; * don&squot;t know what device versions exist for these guys.&n;&t; *&n;&t; * The 0xa003 and 0xa004 devices in particular I&squot;m curious about.&n;&t; * I&squot;m told they exist but so far nobody has come forward to say that&n;&t; * they work with this driver.  Given the success we&squot;ve had getting&n;&t; * other Datafab-based cards operational with this driver, I&squot;ve decided&n;&t; * to leave these two devices in the list.&n;&t; */
id|UNUSUAL_DEV
c_func
(paren
l_int|0x07c4
comma
l_int|0xa001
comma
l_int|0x0000
comma
l_int|0xffff
comma
l_string|&quot;SIIG/Datafab&quot;
comma
l_string|&quot;SIIG/Datafab Memory Stick+CF Reader/Writer&quot;
comma
id|US_SC_SCSI
comma
id|US_PR_DATAFAB
comma
l_int|NULL
comma
id|US_FL_MODE_XLATE
)paren
comma
id|UNUSUAL_DEV
c_func
(paren
l_int|0x07c4
comma
l_int|0xa003
comma
l_int|0x0000
comma
l_int|0xffff
comma
l_string|&quot;Datafab/Unknown&quot;
comma
l_string|&quot;Datafab-based Reader&quot;
comma
id|US_SC_SCSI
comma
id|US_PR_DATAFAB
comma
l_int|NULL
comma
id|US_FL_MODE_XLATE
)paren
comma
id|UNUSUAL_DEV
c_func
(paren
l_int|0x07c4
comma
l_int|0xa004
comma
l_int|0x0000
comma
l_int|0xffff
comma
l_string|&quot;Datafab/Unknown&quot;
comma
l_string|&quot;Datafab-based Reader&quot;
comma
id|US_SC_SCSI
comma
id|US_PR_DATAFAB
comma
l_int|NULL
comma
id|US_FL_MODE_XLATE
)paren
comma
id|UNUSUAL_DEV
c_func
(paren
l_int|0x07c4
comma
l_int|0xa005
comma
l_int|0x0000
comma
l_int|0xffff
comma
l_string|&quot;PNY/Datafab&quot;
comma
l_string|&quot;PNY/Datafab CF+SM Reader&quot;
comma
id|US_SC_SCSI
comma
id|US_PR_DATAFAB
comma
l_int|NULL
comma
id|US_FL_MODE_XLATE
)paren
comma
id|UNUSUAL_DEV
c_func
(paren
l_int|0x07c4
comma
l_int|0xa006
comma
l_int|0x0000
comma
l_int|0xffff
comma
l_string|&quot;Simple Tech/Datafab&quot;
comma
l_string|&quot;Simple Tech/Datafab CF+SM Reader&quot;
comma
id|US_SC_SCSI
comma
id|US_PR_DATAFAB
comma
l_int|NULL
comma
id|US_FL_MODE_XLATE
)paren
comma
multiline_comment|/* Submitted by Olaf Hering &lt;olh@suse.de&gt; */
id|UNUSUAL_DEV
c_func
(paren
l_int|0x07c4
comma
l_int|0xa109
comma
l_int|0x0000
comma
l_int|0xffff
comma
l_string|&quot;Datafab Systems, Inc.&quot;
comma
l_string|&quot;USB to CF + SM Combo (LC1)&quot;
comma
id|US_SC_SCSI
comma
id|US_PR_DATAFAB
comma
l_int|NULL
comma
id|US_FL_MODE_XLATE
)paren
comma
macro_line|#endif
macro_line|#ifdef CONFIG_USB_STORAGE_SDDR55
multiline_comment|/* Contributed by Peter Waechtler */
id|UNUSUAL_DEV
c_func
(paren
l_int|0x07c4
comma
l_int|0xa103
comma
l_int|0x0000
comma
l_int|0x9999
comma
l_string|&quot;Datafab&quot;
comma
l_string|&quot;MDSM-B reader&quot;
comma
id|US_SC_SCSI
comma
id|US_PR_SDDR55
comma
l_int|NULL
comma
id|US_FL_FIX_INQUIRY
)paren
comma
macro_line|#endif
multiline_comment|/* Casio QV 2x00/3x00/4000/8000 digital still cameras are not conformant&n; * to the USB storage specification in two ways:&n; * - They tell us they are using transport protocol CBI. In reality they&n; *   are using transport protocol CB.&n; * - They don&squot;t like the INQUIRY command. So we must handle this command&n; *   of the SCSI layer ourselves.&n; */
id|UNUSUAL_DEV
c_func
(paren
l_int|0x07cf
comma
l_int|0x1001
comma
l_int|0x1000
comma
l_int|0x9009
comma
l_string|&quot;Casio&quot;
comma
l_string|&quot;QV DigitalCamera&quot;
comma
id|US_SC_8070
comma
id|US_PR_CB
comma
l_int|NULL
comma
id|US_FL_FIX_INQUIRY
)paren
comma
id|UNUSUAL_DEV
c_func
(paren
l_int|0x097a
comma
l_int|0x0001
comma
l_int|0x0000
comma
l_int|0x0001
comma
l_string|&quot;Minds@Work&quot;
comma
l_string|&quot;Digital Wallet&quot;
comma
id|US_SC_SCSI
comma
id|US_PR_CB
comma
l_int|NULL
comma
id|US_FL_MODE_XLATE
)paren
comma
id|UNUSUAL_DEV
c_func
(paren
l_int|0x0a16
comma
l_int|0x8888
comma
l_int|0x0100
comma
l_int|0x0100
comma
l_string|&quot;IBM&quot;
comma
l_string|&quot;IBM USB Memory Key&quot;
comma
id|US_SC_SCSI
comma
id|US_PR_BULK
comma
l_int|NULL
comma
id|US_FL_FIX_INQUIRY
)paren
comma
macro_line|#ifdef CONFIG_USB_STORAGE_ISD200
id|UNUSUAL_DEV
c_func
(paren
l_int|0x0bf6
comma
l_int|0xa001
comma
l_int|0x0100
comma
l_int|0x0110
comma
l_string|&quot;ATI&quot;
comma
l_string|&quot;USB Cable 205&quot;
comma
id|US_SC_ISD200
comma
id|US_PR_BULK
comma
id|isd200_Initialization
comma
l_int|0
)paren
comma
macro_line|#endif
multiline_comment|/* EasyDisk support. Submitted by Stanislav Karchebny &lt;berk@madfire.net&gt; */
id|UNUSUAL_DEV
c_func
(paren
l_int|0x1065
comma
l_int|0x2136
comma
l_int|0x0000
comma
l_int|0x0001
comma
l_string|&quot;Global Channel Solutions&quot;
comma
l_string|&quot;EasyDisk EDxxxx&quot;
comma
id|US_SC_SCSI
comma
id|US_PR_BULK
comma
l_int|NULL
comma
id|US_FL_MODE_XLATE
op_or
id|US_FL_START_STOP
op_or
id|US_FL_FIX_INQUIRY
)paren
comma
multiline_comment|/* Submitted by Brian Hall &lt;brihall@bigfoot.com&gt;&n; * Needed for START_STOP flag */
id|UNUSUAL_DEV
c_func
(paren
l_int|0x0c76
comma
l_int|0x0003
comma
l_int|0x0100
comma
l_int|0x0100
comma
l_string|&quot;JMTek&quot;
comma
l_string|&quot;USBDrive&quot;
comma
id|US_SC_SCSI
comma
id|US_PR_BULK
comma
l_int|NULL
comma
id|US_FL_START_STOP
)paren
comma
multiline_comment|/* Reported by Dan Pilone &lt;pilone@slac.com&gt;&n; * The device needs the flags only.&n; * Also reported by Brian Hall &lt;brihall@bigfoot.com&gt;, again for flags.&n; * I also suspect this device may have a broken serial number.&n; */
id|UNUSUAL_DEV
c_func
(paren
l_int|0x1065
comma
l_int|0x2136
comma
l_int|0x0000
comma
l_int|0x9999
comma
l_string|&quot;CCYU TECHNOLOGY&quot;
comma
l_string|&quot;EasyDisk Portable Device&quot;
comma
id|US_SC_SCSI
comma
id|US_PR_BULK
comma
l_int|NULL
comma
id|US_FL_MODE_XLATE
op_or
id|US_FL_START_STOP
)paren
comma
macro_line|#ifdef CONFIG_USB_STORAGE_SDDR55
id|UNUSUAL_DEV
c_func
(paren
l_int|0x55aa
comma
l_int|0xa103
comma
l_int|0x0000
comma
l_int|0x9999
comma
l_string|&quot;Sandisk&quot;
comma
l_string|&quot;ImageMate SDDR55&quot;
comma
id|US_SC_SCSI
comma
id|US_PR_SDDR55
comma
l_int|NULL
comma
id|US_FL_SINGLE_LUN
)paren
comma
macro_line|#endif
eof
