multiline_comment|/* Driver for USB Mass Storage compliant devices&n; * Ununsual Devices File&n; *&n; * $Id: unusual_devs.h,v 1.32 2002/02/25 02:41:24 mdharm Exp $&n; *&n; * Current development and maintenance by:&n; *   (c) 2000-2002 Matthew Dharm (mdharm-usb@one-eyed-alien.net)&n; *&n; * Initial work by:&n; *   (c) 2000 Adam J. Richter (adam@yggdrasil.com), Yggdrasil Computing, Inc.&n; *&n; * Please see http://www.one-eyed-alien.net/~mdharm/linux-usb for more&n; * information about this driver.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2, or (at your option) any&n; * later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; * General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write to the Free Software Foundation, Inc.,&n; * 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
multiline_comment|/* IMPORTANT NOTE: This file must be included in another file which does&n; * the following thing for it to work:&n; * The macro UNUSUAL_DEV() must be defined before this file is included&n; */
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* If you edit this file, please try to keep it sorted first by VendorID,&n; * then by ProductID.&n; *&n; * If you want to add an entry for this file, please send the following&n; * to greg@kroah.com:&n; *&t;- patch that adds the entry for your device which includes your&n; *&t;  email address right above the entry.&n; *&t;- a copy of /proc/bus/usb/devices with your device plugged in&n; *&t;  running with this patch.&n; *&n; */
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
id|US_SC_DEVICE
comma
id|US_PR_DEVICE
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
multiline_comment|/* &lt;torsten.scherer@uni-bielefeld.de&gt;: I don&squot;t know the name of the bridge&n; * manufacturer, but I&squot;ve got an external USB drive by the Revoltec company&n; * that needs this. otherwise the drive is recognized as /dev/sda, but any&n; * access to it blocks indefinitely.&n; */
id|UNUSUAL_DEV
c_func
(paren
l_int|0x0402
comma
l_int|0x5621
comma
l_int|0x0103
comma
l_int|0x0103
comma
l_string|&quot;Revoltec&quot;
comma
l_string|&quot;USB/IDE Bridge (ATA/ATAPI)&quot;
comma
id|US_SC_DEVICE
comma
id|US_PR_DEVICE
comma
l_int|NULL
comma
id|US_FL_FIX_INQUIRY
)paren
comma
multiline_comment|/* Deduced by Jonathan Woithe &lt;jwoithe@physics.adelaide.edu.au&gt;&n; * Entry needed for flags: US_FL_FIX_INQUIRY because initial inquiry message&n; * always fails and confuses drive.&n; */
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
id|US_SC_DEVICE
comma
id|US_PR_DEVICE
comma
l_int|NULL
comma
id|US_FL_FIX_INQUIRY
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
l_int|0
)paren
comma
macro_line|#endif
multiline_comment|/* Patch submitted by Alessandro Fracchetti &lt;al.fracchetti@tin.it&gt; */
id|UNUSUAL_DEV
c_func
(paren
l_int|0x0482
comma
l_int|0x0105
comma
l_int|0x0100
comma
l_int|0x0100
comma
l_string|&quot;Kyocera&quot;
comma
l_string|&quot;Finecam L3&quot;
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
multiline_comment|/* Patch submitted by Philipp Friedrich &lt;philipp@void.at&gt; */
id|UNUSUAL_DEV
c_func
(paren
l_int|0x0482
comma
l_int|0x0100
comma
l_int|0x0100
comma
l_int|0x0100
comma
l_string|&quot;Kyocera&quot;
comma
l_string|&quot;Finecam S3x&quot;
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
multiline_comment|/* Patch submitted by Philipp Friedrich &lt;philipp@void.at&gt; */
id|UNUSUAL_DEV
c_func
(paren
l_int|0x0482
comma
l_int|0x0101
comma
l_int|0x0100
comma
l_int|0x0100
comma
l_string|&quot;Kyocera&quot;
comma
l_string|&quot;Finecam S4&quot;
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
multiline_comment|/* Patch submitted by Stephane Galles &lt;stephane.galles@free.fr&gt; */
id|UNUSUAL_DEV
c_func
(paren
l_int|0x0482
comma
l_int|0x0103
comma
l_int|0x0100
comma
l_int|0x0100
comma
l_string|&quot;Kyocera&quot;
comma
l_string|&quot;Finecam S5&quot;
comma
id|US_SC_DEVICE
comma
id|US_PR_DEVICE
comma
l_int|NULL
comma
id|US_FL_FIX_INQUIRY
)paren
comma
multiline_comment|/* Patch for Kyocera Finecam L3&n; * Submitted by Michael Krauth &lt;michael.krauth@web.de&gt;&n; */
id|UNUSUAL_DEV
c_func
(paren
l_int|0x0482
comma
l_int|0x0105
comma
l_int|0x0100
comma
l_int|0x0100
comma
l_string|&quot;Kyocera&quot;
comma
l_string|&quot;Finecam L3&quot;
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
multiline_comment|/* Reported by Simon Levitt &lt;simon@whattf.com&gt;&n; * This entry needs Sub and Proto fields */
id|UNUSUAL_DEV
c_func
(paren
l_int|0x04b8
comma
l_int|0x0601
comma
l_int|0x0100
comma
l_int|0x0100
comma
l_string|&quot;Epson&quot;
comma
l_string|&quot;875DC Storage&quot;
comma
id|US_SC_SCSI
comma
id|US_PR_CB
comma
l_int|NULL
comma
id|US_FL_FIX_INQUIRY
)paren
comma
multiline_comment|/* Reported by Khalid Aziz &lt;khalid@gonehiking.org&gt;&n; * This entry is needed because the device reports Sub=ff */
id|UNUSUAL_DEV
c_func
(paren
l_int|0x04b8
comma
l_int|0x0602
comma
l_int|0x0110
comma
l_int|0x0110
comma
l_string|&quot;Epson&quot;
comma
l_string|&quot;785EPX Storage&quot;
comma
id|US_SC_SCSI
comma
id|US_PR_BULK
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
id|US_SC_UFI
comma
id|US_PR_DEVICE
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
id|US_SC_DEVICE
comma
id|US_PR_DEVICE
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
id|US_PR_DEVICE
comma
l_int|NULL
comma
l_int|0
)paren
comma
multiline_comment|/* From Yukihiro Nakai, via zaitcev@yahoo.com.&n; * This is needed for CB instead of CBI */
id|UNUSUAL_DEV
c_func
(paren
l_int|0x04da
comma
l_int|0x0d05
comma
l_int|0x0000
comma
l_int|0x0000
comma
l_string|&quot;Sharp CE-CW05&quot;
comma
l_string|&quot;CD-R/RW Drive&quot;
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
id|US_SC_DEVICE
comma
id|US_PR_DEVICE
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
l_int|0
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
id|US_PR_DEVICE
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
l_int|0x0450
comma
l_string|&quot;Sony&quot;
comma
l_string|&quot;DSC-S30/S70/S75/505V/F505/F707/F717/P8&quot;
comma
id|US_SC_SCSI
comma
id|US_PR_DEVICE
comma
l_int|NULL
comma
id|US_FL_SINGLE_LUN
op_or
id|US_FL_MODE_XLATE
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
l_int|0x0500
comma
l_int|0x0500
comma
l_string|&quot;Sony&quot;
comma
l_string|&quot;DSC-T1&quot;
comma
id|US_SC_8070
comma
id|US_PR_DEVICE
comma
l_int|NULL
comma
id|US_FL_SINGLE_LUN
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
id|US_SC_DEVICE
comma
id|US_PR_DEVICE
comma
l_int|NULL
comma
id|US_FL_SINGLE_LUN
)paren
comma
macro_line|#ifdef CONFIG_USB_STORAGE_ISD200
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
id|US_SC_DEVICE
comma
id|US_PR_DEVICE
comma
l_int|NULL
comma
id|US_FL_SINGLE_LUN
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
id|US_PR_DEVICE
comma
l_int|NULL
comma
id|US_FL_SINGLE_LUN
op_or
id|US_FL_MODE_XLATE
)paren
comma
multiline_comment|/* Submitted by Rajesh Kumble Nayak &lt;nayak@obs-nice.fr&gt; */
id|UNUSUAL_DEV
c_func
(paren
l_int|0x054c
comma
l_int|0x002e
comma
l_int|0x0500
comma
l_int|0x0500
comma
l_string|&quot;Sony&quot;
comma
l_string|&quot;Handycam HC-85&quot;
comma
id|US_SC_UFI
comma
id|US_PR_DEVICE
comma
l_int|NULL
comma
id|US_FL_SINGLE_LUN
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
id|US_SC_DEVICE
comma
id|US_PR_DEVICE
comma
l_int|NULL
comma
id|US_FL_SINGLE_LUN
)paren
comma
multiline_comment|/* Submitted by Michal Mlotek &lt;mlotek@foobar.pl&gt; */
id|UNUSUAL_DEV
c_func
(paren
l_int|0x054c
comma
l_int|0x0058
comma
l_int|0x0000
comma
l_int|0x9999
comma
l_string|&quot;Sony&quot;
comma
l_string|&quot;PEG N760c Memorystick&quot;
comma
id|US_SC_DEVICE
comma
id|US_PR_DEVICE
comma
l_int|NULL
comma
id|US_FL_FIX_INQUIRY
)paren
comma
id|UNUSUAL_DEV
c_func
(paren
l_int|0x054c
comma
l_int|0x0069
comma
l_int|0x0000
comma
l_int|0x9999
comma
l_string|&quot;Sony&quot;
comma
l_string|&quot;Memorystick MSC-U03&quot;
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
id|US_SC_DEVICE
comma
id|US_PR_DEVICE
comma
l_int|NULL
comma
id|US_FL_FIX_INQUIRY
)paren
comma
multiline_comment|/* Submitted by Mike Alborn &lt;malborn@deandra.homeip.net&gt; */
id|UNUSUAL_DEV
c_func
(paren
l_int|0x054c
comma
l_int|0x016a
comma
l_int|0x0000
comma
l_int|0x9999
comma
l_string|&quot;Sony&quot;
comma
l_string|&quot;PEG Mass Storage&quot;
comma
id|US_SC_DEVICE
comma
id|US_PR_DEVICE
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
id|US_SC_DEVICE
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
id|US_SC_DEVICE
comma
id|US_PR_DEVICE
comma
l_int|NULL
comma
id|US_FL_SINGLE_LUN
)paren
comma
multiline_comment|/* Fabrizio Fellini &lt;fello@libero.it&gt; */
id|UNUSUAL_DEV
c_func
(paren
l_int|0x0595
comma
l_int|0x4343
comma
l_int|0x0000
comma
l_int|0x2210
comma
l_string|&quot;Fujifilm&quot;
comma
l_string|&quot;Digital Camera EX-20 DSC&quot;
comma
id|US_SC_8070
comma
id|US_PR_DEVICE
comma
l_int|NULL
comma
l_int|0
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
multiline_comment|/* Submitted by Jol Bourquard &lt;numlock@freesurf.ch&gt; */
id|UNUSUAL_DEV
c_func
(paren
l_int|0x05ab
comma
l_int|0x0060
comma
l_int|0x1104
comma
l_int|0x1110
comma
l_string|&quot;In-System&quot;
comma
l_string|&quot;PyroGate External CD-ROM Enclosure (FCD-523)&quot;
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
id|US_FL_NEED_OVERRIDE
op_or
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
id|US_SC_DEVICE
comma
id|US_PR_DEVICE
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
l_string|&quot;Genesys Logic&quot;
comma
l_string|&quot;USB to IDE Card Reader&quot;
comma
id|US_SC_DEVICE
comma
id|US_PR_DEVICE
comma
l_int|NULL
comma
id|US_FL_FIX_INQUIRY
)paren
comma
multiline_comment|/* Submitted Alexander Oltu &lt;alexander@all-2.com&gt; */
id|UNUSUAL_DEV
c_func
(paren
l_int|0x05e3
comma
l_int|0x0701
comma
l_int|0x0000
comma
l_int|0xffff
comma
l_string|&quot;Genesys Logic&quot;
comma
l_string|&quot;USB to IDE Optical&quot;
comma
id|US_SC_DEVICE
comma
id|US_PR_DEVICE
comma
l_int|NULL
comma
id|US_FL_MODE_XLATE
)paren
comma
multiline_comment|/* Reported by Peter Marks &lt;peter.marks@turner.com&gt;&n; * Like the SIIG unit above, this unit needs an INQUIRY to ask for exactly&n; * 36 bytes of data.  No more, no less. That is the only reason this entry&n; * is needed.&n; *&n; * ST818 slim drives (rev 0.02) don&squot;t need special care.&n;*/
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
l_string|&quot;Genesys Logic&quot;
comma
l_string|&quot;USB to IDE Disk&quot;
comma
id|US_SC_DEVICE
comma
id|US_PR_DEVICE
comma
l_int|NULL
comma
id|US_FL_FIX_INQUIRY
)paren
comma
multiline_comment|/* Reported by Hanno Boeck &lt;hanno@gmx.de&gt;&n; * Taken from the Lycoris Kernel */
id|UNUSUAL_DEV
c_func
(paren
l_int|0x0636
comma
l_int|0x0003
comma
l_int|0x0000
comma
l_int|0x9999
comma
l_string|&quot;Vivitar&quot;
comma
l_string|&quot;Vivicam 35Xx&quot;
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
)paren
comma
macro_line|#endif
multiline_comment|/* Submitted by Benny Sjostrand &lt;benny@hostmobility.com&gt; */
id|UNUSUAL_DEV
c_func
(paren
l_int|0x0686
comma
l_int|0x4011
comma
l_int|0x0001
comma
l_int|0x0001
comma
l_string|&quot;Minolta&quot;
comma
l_string|&quot;Dimage F300&quot;
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
multiline_comment|/* Reported by Miguel A. Fosas &lt;amn3s1a@ono.com&gt; */
id|UNUSUAL_DEV
c_func
(paren
l_int|0x0686
comma
l_int|0x4017
comma
l_int|0x0001
comma
l_int|0x0001
comma
l_string|&quot;Minolta&quot;
comma
l_string|&quot;DIMAGE E223&quot;
comma
id|US_SC_SCSI
comma
id|US_PR_DEVICE
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
id|US_SC_DEVICE
comma
id|US_PR_DEVICE
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
l_int|0
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
macro_line|#ifdef CONFIG_USB_STORAGE_DATAFAB
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
multiline_comment|/* SM part - aeb &lt;Andries.Brouwer@cwi.nl&gt; */
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
id|US_PR_SDDR55
comma
l_int|NULL
comma
id|US_FL_SINGLE_LUN
)paren
comma
macro_line|#endif
multiline_comment|/* Datafab KECF-USB / Sagatek DCS-CF / Simpletech Flashlink UCF-100&n; * Only revision 1.13 tested (same for all of the above devices,&n; * based on the Datafab DF-UG-07 chip).  Needed for US_FL_FIX_INQUIRY.&n; * Submitted by Marek Michalkiewicz &lt;marekm@amelek.gda.pl&gt;.&n; * See also http://martin.wilck.bei.t-online.de/#kecf .&n; */
id|UNUSUAL_DEV
c_func
(paren
l_int|0x07c4
comma
l_int|0xa400
comma
l_int|0x0000
comma
l_int|0xffff
comma
l_string|&quot;Datafab&quot;
comma
l_string|&quot;KECF-USB&quot;
comma
id|US_SC_DEVICE
comma
id|US_PR_DEVICE
comma
l_int|NULL
comma
id|US_FL_FIX_INQUIRY
)paren
comma
multiline_comment|/* Casio QV 2x00/3x00/4000/8000 digital still cameras are not conformant&n; * to the USB storage specification in two ways:&n; * - They tell us they are using transport protocol CBI. In reality they&n; *   are using transport protocol CB.&n; * - They don&squot;t like the INQUIRY command. So we must handle this command&n; *   of the SCSI layer ourselves.&n; * - Some cameras with idProduct=0x1001 and bcdDevice=0x1000 have&n; *   bInterfaceProtocol=0x00 (US_PR_CBI) while others have 0x01 (US_PR_CB).&n; *   So don&squot;t remove the US_PR_CB override!&n; * - Cameras with bcdDevice=0x9009 require the US_SC_8070 override.&n; */
id|UNUSUAL_DEV
c_func
(paren
l_int|0x07cf
comma
l_int|0x1001
comma
l_int|0x1000
comma
l_int|0x9999
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
id|US_FL_NEED_OVERRIDE
op_or
id|US_FL_FIX_INQUIRY
)paren
comma
multiline_comment|/* Submitted by Hartmut Wahl &lt;hwahl@hwahl.de&gt;*/
id|UNUSUAL_DEV
c_func
(paren
l_int|0x0839
comma
l_int|0x000a
comma
l_int|0x0001
comma
l_int|0x0001
comma
l_string|&quot;Samsung&quot;
comma
l_string|&quot;Digimax 410&quot;
comma
id|US_SC_DEVICE
comma
id|US_PR_DEVICE
comma
l_int|NULL
comma
id|US_FL_FIX_INQUIRY
)paren
comma
multiline_comment|/* Aiptek PocketCAM 3Mega&n; * Nicolas DUPEUX &lt;nicolas@dupeux.net&gt; &n; */
id|UNUSUAL_DEV
c_func
(paren
l_int|0x08ca
comma
l_int|0x2011
comma
l_int|0x0000
comma
l_int|0x9999
comma
l_string|&quot;AIPTEK&quot;
comma
l_string|&quot;PocketCAM 3Mega&quot;
comma
id|US_SC_DEVICE
comma
id|US_PR_DEVICE
comma
l_int|NULL
comma
id|US_FL_MODE_XLATE
)paren
comma
multiline_comment|/* Entry needed for flags. Moreover, all devices with this ID use&n; * bulk-only transport, but _some_ falsely report Control/Bulk instead.&n; * One example is &quot;Trumpion Digital Research MYMP3&quot;.&n; * Submitted by Bjoern Brill &lt;brill(at)fs.math.uni-frankfurt.de&gt;&n; */
id|UNUSUAL_DEV
c_func
(paren
l_int|0x090a
comma
l_int|0x1001
comma
l_int|0x0100
comma
l_int|0x0100
comma
l_string|&quot;Trumpion&quot;
comma
l_string|&quot;t33520 USB Flash Card Controller&quot;
comma
id|US_SC_DEVICE
comma
id|US_PR_BULK
comma
l_int|NULL
comma
id|US_FL_MODE_XLATE
)paren
comma
multiline_comment|/* Trumpion Microelectronics MP3 player (felipe_alfaro@linuxmail.org) */
id|UNUSUAL_DEV
c_func
(paren
l_int|0x090a
comma
l_int|0x1200
comma
l_int|0x0000
comma
l_int|0x9999
comma
l_string|&quot;Trumpion&quot;
comma
l_string|&quot;MP3 player&quot;
comma
id|US_SC_RBC
comma
id|US_PR_BULK
comma
l_int|NULL
comma
id|US_FL_MODE_XLATE
)paren
comma
multiline_comment|/* aeb */
id|UNUSUAL_DEV
c_func
(paren
l_int|0x090c
comma
l_int|0x1132
comma
l_int|0x0000
comma
l_int|0xffff
comma
l_string|&quot;Feiya&quot;
comma
l_string|&quot;5-in-1 Card Reader&quot;
comma
id|US_SC_DEVICE
comma
id|US_PR_DEVICE
comma
l_int|NULL
comma
id|US_FL_FIX_CAPACITY
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
id|US_SC_DEVICE
comma
id|US_PR_DEVICE
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
id|US_SC_DEVICE
comma
id|US_PR_DEVICE
comma
l_int|NULL
comma
id|US_FL_FIX_INQUIRY
)paren
comma
multiline_comment|/* This Pentax still camera is not conformant&n; * to the USB storage specification: -&n; * - It does not like the INQUIRY command. So we must handle this command&n; *   of the SCSI layer ourselves.&n; * Tested on Rev. 10.00 (0x1000)&n; * Submitted by James Courtier-Dutton &lt;James@superbug.demon.co.uk&gt;&n; */
id|UNUSUAL_DEV
c_func
(paren
l_int|0x0a17
comma
l_int|0x0004
comma
l_int|0x1000
comma
l_int|0x1000
comma
l_string|&quot;Pentax&quot;
comma
l_string|&quot;Optio 2/3/400&quot;
comma
id|US_SC_DEVICE
comma
id|US_PR_DEVICE
comma
l_int|NULL
comma
id|US_FL_FIX_INQUIRY
)paren
comma
multiline_comment|/* Submitted by Per Winkvist &lt;per.winkvist@uk.com&gt; */
id|UNUSUAL_DEV
c_func
(paren
l_int|0x0a17
comma
l_int|0x006
comma
l_int|0x0000
comma
l_int|0xffff
comma
l_string|&quot;Pentax&quot;
comma
l_string|&quot;Optio S/S4&quot;
comma
id|US_SC_DEVICE
comma
id|US_PR_DEVICE
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
macro_line|#ifdef CONFIG_USB_STORAGE_DATAFAB
id|UNUSUAL_DEV
c_func
(paren
l_int|0x0c0b
comma
l_int|0xa109
comma
l_int|0x0000
comma
l_int|0xffff
comma
l_string|&quot;Acomdata&quot;
comma
l_string|&quot;CF&quot;
comma
id|US_SC_SCSI
comma
id|US_PR_DATAFAB
comma
l_int|NULL
comma
id|US_FL_SINGLE_LUN
)paren
comma
macro_line|#endif
macro_line|#ifdef CONFIG_USB_STORAGE_SDDR55
id|UNUSUAL_DEV
c_func
(paren
l_int|0x0c0b
comma
l_int|0xa109
comma
l_int|0x0000
comma
l_int|0xffff
comma
l_string|&quot;Acomdata&quot;
comma
l_string|&quot;SM&quot;
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
multiline_comment|/* Submitted by Joris Struyve &lt;joris@struyve.be&gt; */
id|UNUSUAL_DEV
c_func
(paren
l_int|0x0d96
comma
l_int|0x410a
comma
l_int|0x0001
comma
l_int|0xffff
comma
l_string|&quot;Medion&quot;
comma
l_string|&quot;MD 7425&quot;
comma
id|US_SC_DEVICE
comma
id|US_PR_DEVICE
comma
l_int|NULL
comma
id|US_FL_FIX_INQUIRY
)paren
comma
multiline_comment|/*&n; * Entry for Jenoptik JD 5200z3&n; *&n; * email: car.busse@gmx.de&n; */
id|UNUSUAL_DEV
c_func
(paren
l_int|0x0d96
comma
l_int|0x5200
comma
l_int|0x0001
comma
l_int|0x0200
comma
l_string|&quot;Jenoptik&quot;
comma
l_string|&quot;JD 5200 z3&quot;
comma
id|US_SC_DEVICE
comma
id|US_PR_DEVICE
comma
l_int|NULL
comma
id|US_FL_FIX_INQUIRY
)paren
comma
multiline_comment|/* Reported by Lubomir Blaha &lt;tritol@trilogic.cz&gt;&n; * I _REALLY_ don&squot;t know what 3rd, 4th number and all defines mean, but this&n; * works for me. Can anybody correct these values? (I able to test corrected&n; * version.)&n; */
id|UNUSUAL_DEV
c_func
(paren
l_int|0x0dd8
comma
l_int|0x1060
comma
l_int|0x0000
comma
l_int|0xffff
comma
l_string|&quot;Netac&quot;
comma
l_string|&quot;USB-CF-Card&quot;
comma
id|US_SC_DEVICE
comma
id|US_PR_DEVICE
comma
l_int|NULL
comma
id|US_FL_FIX_INQUIRY
)paren
comma
multiline_comment|/* Submitted by Antoine Mairesse &lt;antoine.mairesse@free.fr&gt; */
id|UNUSUAL_DEV
c_func
(paren
l_int|0x0ed1
comma
l_int|0x6660
comma
l_int|0x0100
comma
l_int|0x0300
comma
l_string|&quot;USB&quot;
comma
l_string|&quot;Solid state disk&quot;
comma
id|US_SC_DEVICE
comma
id|US_PR_DEVICE
comma
l_int|NULL
comma
id|US_FL_FIX_INQUIRY
)paren
comma
multiline_comment|/* Reported by Kevin Cernekee &lt;kpc-usbdev@gelato.uiuc.edu&gt;&n; * Tested on hardware version 1.10.&n; * Entry is needed only for the initializer function override.&n; */
id|UNUSUAL_DEV
c_func
(paren
l_int|0x1019
comma
l_int|0x0c55
comma
l_int|0x0000
comma
l_int|0x9999
comma
l_string|&quot;Desknote&quot;
comma
l_string|&quot;UCR-61S2B&quot;
comma
id|US_SC_DEVICE
comma
id|US_PR_DEVICE
comma
id|usb_stor_ucr61s2b_init
comma
l_int|0
)paren
comma
multiline_comment|/* Reported by Dan Pilone &lt;pilone@slac.com&gt;&n; * The device needs the flags only.&n; * Also reported by Brian Hall &lt;brihall@pcisys.net&gt;, again for flags.&n; * I also suspect this device may have a broken serial number.&n; */
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
id|US_SC_DEVICE
comma
id|US_PR_DEVICE
comma
l_int|NULL
comma
id|US_FL_MODE_XLATE
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
