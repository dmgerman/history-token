multiline_comment|/*&n; * Driver for USB Scanners (linux-2.5.54)&n; *&n; * Copyright (C) 1999, 2000, 2001, 2002 David E. Nelson&n; *&n; * Brian Beattie &lt;beattie@beattie-home.net&gt;&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License as&n; * published by the Free Software Foundation; either version 2 of the&n; * License, or (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; * General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * 05/21/02 Currently maintained by Brian Beattie &lt;beattie@beattie-home.net&gt;&n; *&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
singleline_comment|// #define DEBUG
DECL|macro|DRIVER_VERSION
mdefine_line|#define DRIVER_VERSION &quot;0.4.10&quot;
DECL|macro|DRIVER_DESC
mdefine_line|#define DRIVER_DESC &quot;USB Scanner Driver&quot;
macro_line|#include &lt;linux/usb.h&gt;
DECL|variable|vendor
DECL|variable|product
DECL|variable|read_timeout
r_static
id|__s32
id|vendor
op_assign
op_minus
l_int|1
comma
id|product
op_assign
op_minus
l_int|1
comma
id|read_timeout
op_assign
l_int|0
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Brian Beattie, beattie@beattie-home.net&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
id|DRIVER_DESC
l_string|&quot; &quot;
id|DRIVER_VERSION
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|vendor
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|vendor
comma
l_string|&quot;User specified USB idVendor&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|product
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|product
comma
l_string|&quot;User specified USB idProduct&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|read_timeout
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|read_timeout
comma
l_string|&quot;User specified read timeout in seconds&quot;
)paren
suffix:semicolon
multiline_comment|/* WARNING: These DATA_DUMP&squot;s can produce a lot of data. Caveat Emptor. */
singleline_comment|// #define RD_DATA_DUMP /* Enable to dump data - limited to 24 bytes */
singleline_comment|// #define WR_DATA_DUMP /* DEBUG does not have to be defined. */
DECL|variable|scanner_device_ids
r_static
r_struct
id|usb_device_id
id|scanner_device_ids
(braket
)braket
op_assign
(brace
multiline_comment|/* Acer (now Benq) */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x04a5
comma
l_int|0x2060
)paren
)brace
comma
multiline_comment|/* 620U &amp; 640U (!)*/
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x04a5
comma
l_int|0x2040
)paren
)brace
comma
multiline_comment|/* 620U (!) */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x04a5
comma
l_int|0x20c0
)paren
)brace
comma
multiline_comment|/* 1240UT, 1240U */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x04a5
comma
l_int|0x2022
)paren
)brace
comma
multiline_comment|/* 340U */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x04a5
comma
l_int|0x1a20
)paren
)brace
comma
multiline_comment|/* Unknown - Oliver Schwartz */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x04a5
comma
l_int|0x1a2a
)paren
)brace
comma
multiline_comment|/* Another 620U */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x04a5
comma
l_int|0x207e
)paren
)brace
comma
multiline_comment|/* 640BU */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x04a5
comma
l_int|0x20be
)paren
)brace
comma
multiline_comment|/* Unknown - Oliver Schwartz */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x04a5
comma
l_int|0x20de
)paren
)brace
comma
multiline_comment|/* S2W 3300U */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x04a5
comma
l_int|0x20b0
)paren
)brace
comma
multiline_comment|/* Benq 4300 */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x04a5
comma
l_int|0x20fe
)paren
)brace
comma
multiline_comment|/* Benq 5300 */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x04a5
comma
l_int|0x20fc
)paren
)brace
comma
multiline_comment|/* Benq 5000 */
multiline_comment|/* Agfa */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x06bd
comma
l_int|0x0001
)paren
)brace
comma
multiline_comment|/* SnapScan 1212U */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x06bd
comma
l_int|0x0002
)paren
)brace
comma
multiline_comment|/* SnapScan 1236U */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x06bd
comma
l_int|0x2061
)paren
)brace
comma
multiline_comment|/* Another SnapScan 1212U (?)*/
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x06bd
comma
l_int|0x0100
)paren
)brace
comma
multiline_comment|/* SnapScan Touch */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x06bd
comma
l_int|0x2091
)paren
)brace
comma
multiline_comment|/* SnapScan e20 */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x06bd
comma
l_int|0x2095
)paren
)brace
comma
multiline_comment|/* SnapScan e25 */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x06bd
comma
l_int|0x2097
)paren
)brace
comma
multiline_comment|/* SnapScan e26 */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x06bd
comma
l_int|0x208d
)paren
)brace
comma
multiline_comment|/* Snapscan e40 */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x06bd
comma
l_int|0x2093
)paren
)brace
comma
multiline_comment|/* SnapScan e10*/
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x06bd
comma
l_int|0x20ff
)paren
)brace
comma
multiline_comment|/* SnapScan e42*/
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x06bd
comma
l_int|0x208f
)paren
)brace
comma
multiline_comment|/* SnapScan e50*/
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x06bd
comma
l_int|0x20fd
)paren
)brace
comma
multiline_comment|/* SnapScan e52*/
multiline_comment|/* Benq: see Acer */
multiline_comment|/* Canon */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x04a9
comma
l_int|0x2201
)paren
)brace
comma
multiline_comment|/* FB320U */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x04a9
comma
l_int|0x2205
)paren
)brace
comma
multiline_comment|/* FB1210U */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x04a9
comma
l_int|0x2202
)paren
)brace
comma
multiline_comment|/* CanoScan FB620U */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x04a9
comma
l_int|0x2204
)paren
)brace
comma
multiline_comment|/* CanoScan FB630U/FB636U */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x04a9
comma
l_int|0x2206
)paren
)brace
comma
multiline_comment|/* CanoScan N650U/N656U */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x04a9
comma
l_int|0x2207
)paren
)brace
comma
multiline_comment|/* CanoScan N1220U */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x04a9
comma
l_int|0x2208
)paren
)brace
comma
multiline_comment|/* CanoScan D660U */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x04a9
comma
l_int|0x220b
)paren
)brace
comma
multiline_comment|/* D646U */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x04a9
comma
l_int|0x220d
)paren
)brace
comma
multiline_comment|/* CanoScan N670U/N676U/LIDE 20 */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x04a9
comma
l_int|0x220e
)paren
)brace
comma
multiline_comment|/* CanoScan N1240U/LIDE 30 */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x04a9
comma
l_int|0x3042
)paren
)brace
comma
multiline_comment|/* FS4000US */
multiline_comment|/* Colorado -- See Primax/Colorado below */
multiline_comment|/* Epson -- See Seiko/Epson below */
multiline_comment|/* Genius */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x0458
comma
l_int|0x2001
)paren
)brace
comma
multiline_comment|/* ColorPage-Vivid Pro */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x0458
comma
l_int|0x2007
)paren
)brace
comma
multiline_comment|/* ColorPage HR6 V2 */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x0458
comma
l_int|0x2008
)paren
)brace
comma
multiline_comment|/* ColorPage-HR6 V2 */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x0458
comma
l_int|0x2009
)paren
)brace
comma
multiline_comment|/* ColorPage-HR6A */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x0458
comma
l_int|0x2011
)paren
)brace
comma
multiline_comment|/* ColorPage-Vivid3x */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x0458
comma
l_int|0x2013
)paren
)brace
comma
multiline_comment|/* ColorPage-HR7 */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x0458
comma
l_int|0x2015
)paren
)brace
comma
multiline_comment|/* ColorPage-HR7LE */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x0458
comma
l_int|0x2016
)paren
)brace
comma
multiline_comment|/* ColorPage-HR6X */
multiline_comment|/* Hewlett Packard */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x03f0
comma
l_int|0x0505
)paren
)brace
comma
multiline_comment|/* ScanJet 2100C */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x03f0
comma
l_int|0x0605
)paren
)brace
comma
multiline_comment|/* 2200C */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x03f0
comma
l_int|0x0901
)paren
)brace
comma
multiline_comment|/* 2300C */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x03f0
comma
l_int|0x0205
)paren
)brace
comma
multiline_comment|/* 3300C */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x03f0
comma
l_int|0x0405
)paren
)brace
comma
multiline_comment|/* 3400C */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x03f0
comma
l_int|0x0101
)paren
)brace
comma
multiline_comment|/* 4100C */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x03f0
comma
l_int|0x0105
)paren
)brace
comma
multiline_comment|/* 4200C */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x03f0
comma
l_int|0x0305
)paren
)brace
comma
multiline_comment|/* 4300C */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x03f0
comma
l_int|0x0705
)paren
)brace
comma
multiline_comment|/* 4400C */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x03f0
comma
l_int|0x0102
)paren
)brace
comma
multiline_comment|/* PhotoSmart S20 */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x03f0
comma
l_int|0x0401
)paren
)brace
comma
multiline_comment|/* 5200C */
singleline_comment|//&t;{ USB_DEVICE(0x03f0, 0x0701) },&t;/* 5300C - NOT SUPPORTED - see http://www.neatech.nl/oss/HP5300C/ */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x03f0
comma
l_int|0x0201
)paren
)brace
comma
multiline_comment|/* 6200C */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x03f0
comma
l_int|0x0601
)paren
)brace
comma
multiline_comment|/* 6300C */
multiline_comment|/* iVina */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x0638
comma
l_int|0x0268
)paren
)brace
comma
multiline_comment|/* 1200U */
multiline_comment|/* Lexmark */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x043d
comma
l_int|0x002d
)paren
)brace
comma
multiline_comment|/* X70/X73 */
multiline_comment|/* Lifetec */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x05d8
comma
l_int|0x4002
)paren
)brace
comma
multiline_comment|/* Lifetec LT9385 */
multiline_comment|/* Memorex */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x0461
comma
l_int|0x0346
)paren
)brace
comma
multiline_comment|/* 6136u - repackaged Primax ? */
multiline_comment|/* Microtek -- No longer supported - Enable SCSI and USB Microtek in kernel config */
singleline_comment|//&t;{ USB_DEVICE(0x05da, 0x0099) },&t;/* ScanMaker X6 - X6U */
singleline_comment|//&t;{ USB_DEVICE(0x05da, 0x0094) },&t;/* Phantom 336CX - C3 */
singleline_comment|//&t;{ USB_DEVICE(0x05da, 0x00a0) },&t;/* Phantom 336CX - C3 #2 */
singleline_comment|//&t;{ USB_DEVICE(0x05da, 0x009a) },&t;/* Phantom C6 */
singleline_comment|//&t;{ USB_DEVICE(0x05da, 0x00a3) },&t;/* ScanMaker V6USL */
singleline_comment|//&t;{ USB_DEVICE(0x05da, 0x80a3) },&t;/* ScanMaker V6USL #2 */
singleline_comment|//&t;{ USB_DEVICE(0x05da, 0x80ac) },&t;/* ScanMaker V6UL - SpicyU */
multiline_comment|/* Minolta */
singleline_comment|//&t;{ USB_DEVICE(0x0638,0x026a) }, /* Minolta Dimage Scan Dual II */
singleline_comment|//&t;{ USB_DEVICE(0x0686, 0x4004) }, /* Scan Elite II (need interrupt ep) */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x0686
comma
l_int|0x400d
)paren
)brace
comma
multiline_comment|/* Scan Dual III */
multiline_comment|/* Mustek */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x055f
comma
l_int|0x0001
)paren
)brace
comma
multiline_comment|/* ScanExpress 1200 CU */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x0400
comma
l_int|0x1000
)paren
)brace
comma
multiline_comment|/* BearPaw 1200 */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x055f
comma
l_int|0x0002
)paren
)brace
comma
multiline_comment|/* ScanExpress 600 CU */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x055f
comma
l_int|0x0873
)paren
)brace
comma
multiline_comment|/* ScanExpress 600 USB */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x055f
comma
l_int|0x0003
)paren
)brace
comma
multiline_comment|/* ScanExpress 1200 USB */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x055f
comma
l_int|0x0006
)paren
)brace
comma
multiline_comment|/* ScanExpress 1200 UB */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x055f
comma
l_int|0x0007
)paren
)brace
comma
multiline_comment|/* ScanExpress 1200 USB Plus */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x055f
comma
l_int|0x0210
)paren
)brace
comma
multiline_comment|/* ScanExpress A3 USB */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x0400
comma
l_int|0x1001
)paren
)brace
comma
multiline_comment|/* BearPaw 2400 */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x055f
comma
l_int|0x0008
)paren
)brace
comma
multiline_comment|/* ScanExpress 1200 CU Plus */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x055f
comma
l_int|0x0010
)paren
)brace
comma
multiline_comment|/* BearPaw 1200F */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x055f
comma
l_int|0x0218
)paren
)brace
comma
multiline_comment|/* BearPaw 2400 TA */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x05d8
comma
l_int|0x4002
)paren
)brace
comma
multiline_comment|/* BearPaw 1200 CU and ScanExpress 1200 UB Plus */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x055f
comma
l_int|0x0219
)paren
)brace
comma
multiline_comment|/* BearPaw 2400 TA Plus */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x055f
comma
l_int|0x021c
)paren
)brace
comma
multiline_comment|/* BearPaw 1200 CU Plus */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x055f
comma
l_int|0x021d
)paren
)brace
comma
multiline_comment|/* Bearpaw 2400 CU Plus */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x055f
comma
l_int|0x021e
)paren
)brace
comma
multiline_comment|/* BearPaw 1200 TA/CS */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x055f
comma
l_int|0x0400
)paren
)brace
comma
multiline_comment|/* BearPaw 2400 TA PRO */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x055f
comma
l_int|0x1000
)paren
)brace
comma
multiline_comment|/* BearPaw 4800 TA PRO */
multiline_comment|/* Nikon */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x04b0
comma
l_int|0x4000
)paren
)brace
comma
multiline_comment|/* Coolscan LS 40 ED */
multiline_comment|/* Plustek */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x07b3
comma
l_int|0x0017
)paren
)brace
comma
multiline_comment|/* OpticPro UT12/UT16/UT24 */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x07b3
comma
l_int|0x0011
)paren
)brace
comma
multiline_comment|/* OpticPro U24 */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x07b3
comma
l_int|0x0010
)paren
)brace
comma
multiline_comment|/* OpticPro U12 */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x07b3
comma
l_int|0x0015
)paren
)brace
comma
multiline_comment|/* OpticPro U24 */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x07b3
comma
l_int|0x0005
)paren
)brace
comma
multiline_comment|/* Unknown */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x07b3
comma
l_int|0x0007
)paren
)brace
comma
multiline_comment|/* Unknown */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x07b3
comma
l_int|0x000F
)paren
)brace
comma
multiline_comment|/* Unknown */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x07b3
comma
l_int|0x0012
)paren
)brace
comma
multiline_comment|/* Unknown */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x07b3
comma
l_int|0x0013
)paren
)brace
comma
multiline_comment|/* Unknown */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x07b3
comma
l_int|0x0014
)paren
)brace
comma
multiline_comment|/* Unknown */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x07b3
comma
l_int|0x0016
)paren
)brace
comma
multiline_comment|/* Unknown */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x07b3
comma
l_int|0x0012
)paren
)brace
comma
multiline_comment|/* Unknown */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x07b3
comma
l_int|0x0401
)paren
)brace
comma
multiline_comment|/* OpticPro 1248U */
multiline_comment|/* Primax/Colorado */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x0461
comma
l_int|0x0300
)paren
)brace
comma
multiline_comment|/* G2-300 #1 */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x0461
comma
l_int|0x0380
)paren
)brace
comma
multiline_comment|/* G2-600 #1 */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x0461
comma
l_int|0x0301
)paren
)brace
comma
multiline_comment|/* G2E-300 #1 */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x0461
comma
l_int|0x0381
)paren
)brace
comma
multiline_comment|/* ReadyScan 636i */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x0461
comma
l_int|0x0302
)paren
)brace
comma
multiline_comment|/* G2-300 #2 */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x0461
comma
l_int|0x0382
)paren
)brace
comma
multiline_comment|/* G2-600 #2 */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x0461
comma
l_int|0x0303
)paren
)brace
comma
multiline_comment|/* G2E-300 #2 */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x0461
comma
l_int|0x0383
)paren
)brace
comma
multiline_comment|/* G2E-600 */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x0461
comma
l_int|0x0340
)paren
)brace
comma
multiline_comment|/* Colorado USB 9600 */
singleline_comment|// { USB_DEVICE(0x0461, 0x0360) },&t;/* Colorado USB 19200 - undetected endpoint */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x0461
comma
l_int|0x0341
)paren
)brace
comma
multiline_comment|/* Colorado 600u */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x0461
comma
l_int|0x0361
)paren
)brace
comma
multiline_comment|/* Colorado 1200u */
multiline_comment|/* Relisis */
singleline_comment|// { USB_DEVICE(0x0475, 0x0103) },&t;/* Episode - undetected endpoint */
multiline_comment|/* Seiko/Epson Corp. */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x04b8
comma
l_int|0x0101
)paren
)brace
comma
multiline_comment|/* Perfection 636U and 636Photo */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x04b8
comma
l_int|0x0102
)paren
)brace
comma
multiline_comment|/* GT-2200 */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x04b8
comma
l_int|0x0103
)paren
)brace
comma
multiline_comment|/* Perfection 610 */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x04b8
comma
l_int|0x0104
)paren
)brace
comma
multiline_comment|/* Perfection 1200U and 1200Photo*/
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x04b8
comma
l_int|0x0105
)paren
)brace
comma
multiline_comment|/* StylusScan 2000 */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x04b8
comma
l_int|0x0106
)paren
)brace
comma
multiline_comment|/* Stylus Scan 2500 */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x04b8
comma
l_int|0x0107
)paren
)brace
comma
multiline_comment|/* Expression 1600 */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x04b8
comma
l_int|0x0109
)paren
)brace
comma
multiline_comment|/* Expression 1640XL */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x04b8
comma
l_int|0x010a
)paren
)brace
comma
multiline_comment|/* Perfection 1640SU and 1640SU Photo */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x04b8
comma
l_int|0x010b
)paren
)brace
comma
multiline_comment|/* Perfection 1240U */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x04b8
comma
l_int|0x010c
)paren
)brace
comma
multiline_comment|/* Perfection 640U */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x04b8
comma
l_int|0x010e
)paren
)brace
comma
multiline_comment|/* Expression 1680 */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x04b8
comma
l_int|0x010f
)paren
)brace
comma
multiline_comment|/* Perfection 1250U */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x04b8
comma
l_int|0x0110
)paren
)brace
comma
multiline_comment|/* Perfection 1650 */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x04b8
comma
l_int|0x0112
)paren
)brace
comma
multiline_comment|/* Perfection 2450 - GT-9700 for the Japanese mkt */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x04b8
comma
l_int|0x0114
)paren
)brace
comma
multiline_comment|/* Perfection 660 */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x04b8
comma
l_int|0x011b
)paren
)brace
comma
multiline_comment|/* Perfection 2400 Photo */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x04b8
comma
l_int|0x011c
)paren
)brace
comma
multiline_comment|/* Perfection 3200 */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x04b8
comma
l_int|0x011d
)paren
)brace
comma
multiline_comment|/* Perfection 1260 */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x04b8
comma
l_int|0x011e
)paren
)brace
comma
multiline_comment|/* Perfection 1660 Photo */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x04b8
comma
l_int|0x0802
)paren
)brace
comma
multiline_comment|/* Stylus CX3200 */
multiline_comment|/* Umax */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x1606
comma
l_int|0x0010
)paren
)brace
comma
multiline_comment|/* Astra 1220U */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x1606
comma
l_int|0x0030
)paren
)brace
comma
multiline_comment|/* Astra 2000U */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x1606
comma
l_int|0x0060
)paren
)brace
comma
multiline_comment|/* Astra 3400U/3450U */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x1606
comma
l_int|0x0130
)paren
)brace
comma
multiline_comment|/* Astra 2100U */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x1606
comma
l_int|0x0160
)paren
)brace
comma
multiline_comment|/* Astra 5400U */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x1606
comma
l_int|0x0230
)paren
)brace
comma
multiline_comment|/* Astra 2200U */
multiline_comment|/* Visioneer */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x04a7
comma
l_int|0x0221
)paren
)brace
comma
multiline_comment|/* OneTouch 5300 USB */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x04a7
comma
l_int|0x0211
)paren
)brace
comma
multiline_comment|/* OneTouch 7600 USB */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x04a7
comma
l_int|0x0231
)paren
)brace
comma
multiline_comment|/* 6100 USB */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x04a7
comma
l_int|0x0311
)paren
)brace
comma
multiline_comment|/* 6200 EPP/USB */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x04a7
comma
l_int|0x0321
)paren
)brace
comma
multiline_comment|/* OneTouch 8100 EPP/USB */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x04a7
comma
l_int|0x0331
)paren
)brace
comma
multiline_comment|/* OneTouch 8600 EPP/USB */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x0461
comma
l_int|0x0345
)paren
)brace
comma
multiline_comment|/* 6200 (actually Primax?) */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x0461
comma
l_int|0x0371
)paren
)brace
comma
multiline_comment|/* Onetouch 8920 USB (actually Primax?) */
(brace
)brace
multiline_comment|/* Terminating entry */
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
(paren
id|usb
comma
id|scanner_device_ids
)paren
suffix:semicolon
DECL|macro|IS_EP_BULK
mdefine_line|#define IS_EP_BULK(ep)  ((ep)-&gt;bmAttributes == USB_ENDPOINT_XFER_BULK ? 1 : 0)
DECL|macro|IS_EP_BULK_IN
mdefine_line|#define IS_EP_BULK_IN(ep) (IS_EP_BULK(ep) &amp;&amp; ((ep)-&gt;bEndpointAddress &amp; USB_ENDPOINT_DIR_MASK) == USB_DIR_IN)
DECL|macro|IS_EP_BULK_OUT
mdefine_line|#define IS_EP_BULK_OUT(ep) (IS_EP_BULK(ep) &amp;&amp; ((ep)-&gt;bEndpointAddress &amp; USB_ENDPOINT_DIR_MASK) == USB_DIR_OUT)
DECL|macro|IS_EP_INTR
mdefine_line|#define IS_EP_INTR(ep) ((ep)-&gt;bmAttributes == USB_ENDPOINT_XFER_INT ? 1 : 0)
DECL|macro|USB_SCN_MINOR
mdefine_line|#define USB_SCN_MINOR(X) minor((X)-&gt;i_rdev)
macro_line|#ifdef DEBUG
DECL|macro|SCN_DEBUG
mdefine_line|#define SCN_DEBUG(X) X
macro_line|#else
DECL|macro|SCN_DEBUG
mdefine_line|#define SCN_DEBUG(X)
macro_line|#endif
DECL|macro|IBUF_SIZE
mdefine_line|#define IBUF_SIZE 32768
DECL|macro|OBUF_SIZE
mdefine_line|#define OBUF_SIZE 4096
multiline_comment|/* read_scanner timeouts -- RD_NAK_TIMEOUT * RD_EXPIRE = Number of seconds */
DECL|macro|RD_NAK_TIMEOUT
mdefine_line|#define RD_NAK_TIMEOUT (10*HZ)&t;/* Default number of X seconds to wait */
DECL|macro|RD_EXPIRE
mdefine_line|#define RD_EXPIRE 12&t;&t;/* Number of attempts to wait X seconds */
multiline_comment|/* read vendor and product IDs from the scanner */
DECL|macro|SCANNER_IOCTL_VENDOR
mdefine_line|#define SCANNER_IOCTL_VENDOR _IOR(&squot;U&squot;, 0x20, int)
DECL|macro|SCANNER_IOCTL_PRODUCT
mdefine_line|#define SCANNER_IOCTL_PRODUCT _IOR(&squot;U&squot;, 0x21, int)
multiline_comment|/* send/recv a control message to the scanner */
DECL|macro|SCANNER_IOCTL_CTRLMSG
mdefine_line|#define SCANNER_IOCTL_CTRLMSG _IOWR(&squot;U&squot;, 0x22, struct usb_ctrlrequest)
multiline_comment|/* USB bInterfaceClass used by Hewlett-Packard ScanJet 3300c and Genius HR6&n;   USB - Vivid III */
DECL|macro|SCN_CLASS_SCANJET
mdefine_line|#define SCN_CLASS_SCANJET 16
macro_line|#ifdef CONFIG_USB_DYNAMIC_MINORS
DECL|macro|SCN_MAX_MNR
mdefine_line|#define SCN_MAX_MNR 256
DECL|macro|SCN_BASE_MNR
mdefine_line|#define SCN_BASE_MNR 0
macro_line|#else
DECL|macro|SCN_MAX_MNR
mdefine_line|#define SCN_MAX_MNR 16&t;&t;/* We&squot;re allocated 16 minors */
DECL|macro|SCN_BASE_MNR
mdefine_line|#define SCN_BASE_MNR 48&t;&t;/* USB Scanners start at minor 48 */
macro_line|#endif
r_static
id|DECLARE_MUTEX
(paren
id|scn_mutex
)paren
suffix:semicolon
multiline_comment|/* Initializes to unlocked */
DECL|struct|scn_usb_data
r_struct
id|scn_usb_data
(brace
DECL|member|scn_dev
r_struct
id|usb_device
op_star
id|scn_dev
suffix:semicolon
DECL|member|devfs
id|devfs_handle_t
id|devfs
suffix:semicolon
multiline_comment|/* devfs device */
DECL|member|scn_irq
r_struct
id|urb
op_star
id|scn_irq
suffix:semicolon
DECL|member|ifnum
r_int
r_int
id|ifnum
suffix:semicolon
multiline_comment|/* Interface number of the USB device */
DECL|member|scn_minor
r_int
id|scn_minor
suffix:semicolon
multiline_comment|/* Scanner minor - used in disconnect() */
DECL|member|button
r_int
r_char
id|button
suffix:semicolon
multiline_comment|/* Front panel buffer */
DECL|member|isopen
r_char
id|isopen
suffix:semicolon
multiline_comment|/* Not zero if the device is open */
DECL|member|present
r_char
id|present
suffix:semicolon
multiline_comment|/* Not zero if device is present */
DECL|member|obuf
DECL|member|ibuf
r_char
op_star
id|obuf
comma
op_star
id|ibuf
suffix:semicolon
multiline_comment|/* transfer buffers */
DECL|member|bulk_in_ep
DECL|member|bulk_out_ep
DECL|member|intr_ep
r_char
id|bulk_in_ep
comma
id|bulk_out_ep
comma
id|intr_ep
suffix:semicolon
multiline_comment|/* Endpoint assignments */
DECL|member|rd_wait_q
id|wait_queue_head_t
id|rd_wait_q
suffix:semicolon
multiline_comment|/* read timeouts */
DECL|member|sem
r_struct
id|semaphore
id|sem
suffix:semicolon
multiline_comment|/* lock to prevent concurrent reads or writes */
DECL|member|rd_nak_timeout
r_int
r_int
id|rd_nak_timeout
suffix:semicolon
multiline_comment|/* Seconds to wait before read() timeout. */
)brace
suffix:semicolon
r_extern
id|devfs_handle_t
id|usb_devfs_handle
suffix:semicolon
DECL|variable|scanner_driver
r_static
r_struct
id|usb_driver
id|scanner_driver
suffix:semicolon
eof
