multiline_comment|/*&n; *&t;Adaptec AAC series RAID controller driver&n; *&t;(c) Copyright 2001 Red Hat Inc.&t;&lt;alan@redhat.com&gt;&n; *&n; * based on the old aacraid driver that is..&n; * Adaptec aacraid device driver for Linux.&n; *&n; * Copyright (c) 2000 Adaptec, Inc. (aacraid@adaptec.com)&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; see the file COPYING.  If not, write to&n; * the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * Module Name:&n; *   linit.c&n; *&n; * Abstract: Linux Driver entry module for Adaptec RAID Array Controller&n; */
DECL|macro|AAC_DRIVER_VERSION
mdefine_line|#define AAC_DRIVER_VERSION&t;&t;&quot;1.1.2-lk1&quot;
DECL|macro|AAC_DRIVER_BUILD_DATE
mdefine_line|#define AAC_DRIVER_BUILD_DATE&t;&t;__DATE__
DECL|macro|AAC_DRIVERNAME
mdefine_line|#define AAC_DRIVERNAME&t;&t;&t;&quot;aacraid&quot;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/completion.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &lt;scsi/scsi.h&gt;
macro_line|#include &lt;scsi/scsi_cmnd.h&gt;
macro_line|#include &lt;scsi/scsi_device.h&gt;
macro_line|#include &lt;scsi/scsi_host.h&gt;
macro_line|#include &lt;scsi/scsi_tcq.h&gt;
macro_line|#include &lt;scsi/scsicam.h&gt;
macro_line|#include &quot;aacraid.h&quot;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Red Hat Inc and Adaptec&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Dell PERC2, 2/Si, 3/Si, 3/Di, &quot;
l_string|&quot;Adaptec Advanced Raid Products, &quot;
l_string|&quot;and HP NetRAID-4M SCSI driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|nondasd
r_int
id|nondasd
op_assign
op_minus
l_int|1
suffix:semicolon
id|module_param
c_func
(paren
id|nondasd
comma
r_int
comma
id|S_IRUGO
op_or
id|S_IWUSR
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|nondasd
comma
l_string|&quot;Control scanning of hba for nondasd devices. 0=off, 1=on&quot;
)paren
suffix:semicolon
DECL|variable|paemode
r_int
id|paemode
op_assign
op_minus
l_int|1
suffix:semicolon
id|module_param
c_func
(paren
id|paemode
comma
r_int
comma
id|S_IRUGO
op_or
id|S_IWUSR
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|paemode
comma
l_string|&quot;Control whether dma addressing is using PAE. 0=off, 1=on&quot;
)paren
suffix:semicolon
DECL|variable|aac_devices
r_struct
id|aac_dev
op_star
id|aac_devices
(braket
id|MAXIMUM_NUM_ADAPTERS
)braket
suffix:semicolon
DECL|variable|aac_count
r_static
r_int
id|aac_count
suffix:semicolon
DECL|variable|aac_cfg_major
r_static
r_int
id|aac_cfg_major
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/*&n; * Because of the way Linux names scsi devices, the order in this table has&n; * become important.  Check for on-board Raid first, add-in cards second.&n; *&n; * Note: The last field is used to index into aac_drivers below.&n; */
DECL|variable|aac_pci_tbl
r_static
r_struct
id|pci_device_id
id|aac_pci_tbl
(braket
)braket
op_assign
(brace
(brace
l_int|0x1028
comma
l_int|0x0001
comma
l_int|0x1028
comma
l_int|0x0001
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* PERC 2/Si */
(brace
l_int|0x1028
comma
l_int|0x0002
comma
l_int|0x1028
comma
l_int|0x0002
comma
l_int|0
comma
l_int|0
comma
l_int|1
)brace
comma
multiline_comment|/* PERC 3/Di */
(brace
l_int|0x1028
comma
l_int|0x0003
comma
l_int|0x1028
comma
l_int|0x0003
comma
l_int|0
comma
l_int|0
comma
l_int|2
)brace
comma
multiline_comment|/* PERC 3/Si */
(brace
l_int|0x1028
comma
l_int|0x0004
comma
l_int|0x1028
comma
l_int|0x00d0
comma
l_int|0
comma
l_int|0
comma
l_int|3
)brace
comma
multiline_comment|/* PERC 3/Si */
(brace
l_int|0x1028
comma
l_int|0x0002
comma
l_int|0x1028
comma
l_int|0x00d1
comma
l_int|0
comma
l_int|0
comma
l_int|4
)brace
comma
multiline_comment|/* PERC 3/Di */
(brace
l_int|0x1028
comma
l_int|0x0002
comma
l_int|0x1028
comma
l_int|0x00d9
comma
l_int|0
comma
l_int|0
comma
l_int|5
)brace
comma
multiline_comment|/* PERC 3/Di */
(brace
l_int|0x1028
comma
l_int|0x000a
comma
l_int|0x1028
comma
l_int|0x0106
comma
l_int|0
comma
l_int|0
comma
l_int|6
)brace
comma
multiline_comment|/* PERC 3/Di */
(brace
l_int|0x1028
comma
l_int|0x000a
comma
l_int|0x1028
comma
l_int|0x011b
comma
l_int|0
comma
l_int|0
comma
l_int|7
)brace
comma
multiline_comment|/* PERC 3/Di */
(brace
l_int|0x1028
comma
l_int|0x000a
comma
l_int|0x1028
comma
l_int|0x0121
comma
l_int|0
comma
l_int|0
comma
l_int|8
)brace
comma
multiline_comment|/* PERC 3/Di */
(brace
l_int|0x9005
comma
l_int|0x0283
comma
l_int|0x9005
comma
l_int|0x0283
comma
l_int|0
comma
l_int|0
comma
l_int|9
)brace
comma
multiline_comment|/* catapult*/
(brace
l_int|0x9005
comma
l_int|0x0284
comma
l_int|0x9005
comma
l_int|0x0284
comma
l_int|0
comma
l_int|0
comma
l_int|10
)brace
comma
multiline_comment|/* tomcat*/
(brace
l_int|0x9005
comma
l_int|0x0285
comma
l_int|0x9005
comma
l_int|0x0286
comma
l_int|0
comma
l_int|0
comma
l_int|11
)brace
comma
multiline_comment|/* Adaptec 2120S (Crusader)*/
(brace
l_int|0x9005
comma
l_int|0x0285
comma
l_int|0x9005
comma
l_int|0x0285
comma
l_int|0
comma
l_int|0
comma
l_int|12
)brace
comma
multiline_comment|/* Adaptec 2200S (Vulcan)*/
(brace
l_int|0x9005
comma
l_int|0x0285
comma
l_int|0x9005
comma
l_int|0x0287
comma
l_int|0
comma
l_int|0
comma
l_int|13
)brace
comma
multiline_comment|/* Adaptec 2200S (Vulcan-2m)*/
(brace
l_int|0x9005
comma
l_int|0x0285
comma
l_int|0x17aa
comma
l_int|0x0286
comma
l_int|0
comma
l_int|0
comma
l_int|14
)brace
comma
multiline_comment|/* Legend S220*/
(brace
l_int|0x9005
comma
l_int|0x0285
comma
l_int|0x17aa
comma
l_int|0x0287
comma
l_int|0
comma
l_int|0
comma
l_int|15
)brace
comma
multiline_comment|/* Legend S230*/
(brace
l_int|0x9005
comma
l_int|0x0285
comma
l_int|0x9005
comma
l_int|0x0288
comma
l_int|0
comma
l_int|0
comma
l_int|16
)brace
comma
multiline_comment|/* Adaptec 3230S (Harrier)*/
(brace
l_int|0x9005
comma
l_int|0x0285
comma
l_int|0x9005
comma
l_int|0x0289
comma
l_int|0
comma
l_int|0
comma
l_int|17
)brace
comma
multiline_comment|/* Adaptec 3240S (Tornado)*/
(brace
l_int|0x9005
comma
l_int|0x0285
comma
l_int|0x9005
comma
l_int|0x028a
comma
l_int|0
comma
l_int|0
comma
l_int|18
)brace
comma
multiline_comment|/* ASR-2020S PCI-X ZCR (Skyhawk)*/
(brace
l_int|0x9005
comma
l_int|0x0285
comma
l_int|0x9005
comma
l_int|0x028b
comma
l_int|0
comma
l_int|0
comma
l_int|19
)brace
comma
multiline_comment|/* ASR-2020S SO-DIMM PCI-X ZCR(Terminator)*/
(brace
l_int|0x9005
comma
l_int|0x0285
comma
l_int|0x9005
comma
l_int|0x0290
comma
l_int|0
comma
l_int|0
comma
l_int|20
)brace
comma
multiline_comment|/* AAR-2410SA PCI SATA 4ch (Jaguar II)*/
(brace
l_int|0x9005
comma
l_int|0x0250
comma
l_int|0x1014
comma
l_int|0x0279
comma
l_int|0
comma
l_int|0
comma
l_int|21
)brace
comma
multiline_comment|/* (Marco)*/
(brace
l_int|0x9005
comma
l_int|0x0250
comma
l_int|0x1014
comma
l_int|0x028c
comma
l_int|0
comma
l_int|0
comma
l_int|22
)brace
comma
multiline_comment|/* (Sebring)*/
(brace
l_int|0x9005
comma
l_int|0x0285
comma
l_int|0x1028
comma
l_int|0x0287
comma
l_int|0
comma
l_int|0
comma
l_int|23
)brace
comma
multiline_comment|/* Perc 320/DC*/
(brace
l_int|0x1011
comma
l_int|0x0046
comma
l_int|0x9005
comma
l_int|0x0365
comma
l_int|0
comma
l_int|0
comma
l_int|24
)brace
comma
multiline_comment|/* Adaptec 5400S (Mustang)*/
(brace
l_int|0x1011
comma
l_int|0x0046
comma
l_int|0x9005
comma
l_int|0x0364
comma
l_int|0
comma
l_int|0
comma
l_int|25
)brace
comma
multiline_comment|/* Adaptec 5400S (Mustang)*/
(brace
l_int|0x1011
comma
l_int|0x0046
comma
l_int|0x9005
comma
l_int|0x1364
comma
l_int|0
comma
l_int|0
comma
l_int|26
)brace
comma
multiline_comment|/* Dell PERC2 &quot;Quad Channel&quot; */
(brace
l_int|0x1011
comma
l_int|0x0046
comma
l_int|0x103c
comma
l_int|0x10c2
comma
l_int|0
comma
l_int|0
comma
l_int|27
)brace
comma
multiline_comment|/* HP NetRAID-4M */
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
id|aac_pci_tbl
)paren
suffix:semicolon
multiline_comment|/*&n; * dmb - For now we add the number of channels to this structure.  &n; * In the future we should add a fib that reports the number of channels&n; * for the card.  At that time we can remove the channels from here&n; */
DECL|variable|aac_drivers
r_static
r_struct
id|aac_driver_ident
id|aac_drivers
(braket
)braket
op_assign
(brace
(brace
id|aac_rx_init
comma
l_string|&quot;percraid&quot;
comma
l_string|&quot;DELL    &quot;
comma
l_string|&quot;PERCRAID        &quot;
comma
l_int|2
)brace
comma
multiline_comment|/* PERC 2/Si */
(brace
id|aac_rx_init
comma
l_string|&quot;percraid&quot;
comma
l_string|&quot;DELL    &quot;
comma
l_string|&quot;PERCRAID        &quot;
comma
l_int|2
)brace
comma
multiline_comment|/* PERC 3/Di */
(brace
id|aac_rx_init
comma
l_string|&quot;percraid&quot;
comma
l_string|&quot;DELL    &quot;
comma
l_string|&quot;PERCRAID        &quot;
comma
l_int|2
)brace
comma
multiline_comment|/* PERC 3/Si */
(brace
id|aac_rx_init
comma
l_string|&quot;percraid&quot;
comma
l_string|&quot;DELL    &quot;
comma
l_string|&quot;PERCRAID        &quot;
comma
l_int|2
)brace
comma
multiline_comment|/* PERC 3/Si */
(brace
id|aac_rx_init
comma
l_string|&quot;percraid&quot;
comma
l_string|&quot;DELL    &quot;
comma
l_string|&quot;PERCRAID        &quot;
comma
l_int|2
)brace
comma
multiline_comment|/* PERC 3/Di */
(brace
id|aac_rx_init
comma
l_string|&quot;percraid&quot;
comma
l_string|&quot;DELL    &quot;
comma
l_string|&quot;PERCRAID        &quot;
comma
l_int|2
)brace
comma
multiline_comment|/* PERC 3/Di */
(brace
id|aac_rx_init
comma
l_string|&quot;percraid&quot;
comma
l_string|&quot;DELL    &quot;
comma
l_string|&quot;PERCRAID        &quot;
comma
l_int|2
)brace
comma
multiline_comment|/* PERC 3/Di */
(brace
id|aac_rx_init
comma
l_string|&quot;percraid&quot;
comma
l_string|&quot;DELL    &quot;
comma
l_string|&quot;PERCRAID        &quot;
comma
l_int|2
)brace
comma
multiline_comment|/* PERC 3/Di */
(brace
id|aac_rx_init
comma
l_string|&quot;percraid&quot;
comma
l_string|&quot;DELL    &quot;
comma
l_string|&quot;PERCRAID        &quot;
comma
l_int|2
)brace
comma
multiline_comment|/* PERC 3/Di */
(brace
id|aac_rx_init
comma
l_string|&quot;aacraid&quot;
comma
l_string|&quot;ADAPTEC &quot;
comma
l_string|&quot;catapult        &quot;
comma
l_int|2
)brace
comma
multiline_comment|/* catapult*/
(brace
id|aac_rx_init
comma
l_string|&quot;aacraid&quot;
comma
l_string|&quot;ADAPTEC &quot;
comma
l_string|&quot;tomcat          &quot;
comma
l_int|2
)brace
comma
multiline_comment|/* tomcat*/
(brace
id|aac_rx_init
comma
l_string|&quot;aacraid&quot;
comma
l_string|&quot;ADAPTEC &quot;
comma
l_string|&quot;Adaptec 2120S   &quot;
comma
l_int|1
)brace
comma
multiline_comment|/* Adaptec 2120S (Crusader)*/
(brace
id|aac_rx_init
comma
l_string|&quot;aacraid&quot;
comma
l_string|&quot;ADAPTEC &quot;
comma
l_string|&quot;Adaptec 2200S   &quot;
comma
l_int|2
)brace
comma
multiline_comment|/* Adaptec 2200S (Vulcan)*/
(brace
id|aac_rx_init
comma
l_string|&quot;aacraid&quot;
comma
l_string|&quot;ADAPTEC &quot;
comma
l_string|&quot;Adaptec 2200S   &quot;
comma
l_int|2
)brace
comma
multiline_comment|/* Adaptec 2200S (Vulcan-2m)*/
(brace
id|aac_rx_init
comma
l_string|&quot;aacraid&quot;
comma
l_string|&quot;Legend  &quot;
comma
l_string|&quot;Legend S220     &quot;
comma
l_int|1
)brace
comma
multiline_comment|/* Legend S220*/
(brace
id|aac_rx_init
comma
l_string|&quot;aacraid&quot;
comma
l_string|&quot;Legend  &quot;
comma
l_string|&quot;Legend S230     &quot;
comma
l_int|2
)brace
comma
multiline_comment|/* Legend S230*/
(brace
id|aac_rx_init
comma
l_string|&quot;aacraid&quot;
comma
l_string|&quot;ADAPTEC &quot;
comma
l_string|&quot;Adaptec 3230S   &quot;
comma
l_int|2
)brace
comma
multiline_comment|/* Adaptec 3230S (Harrier)*/
(brace
id|aac_rx_init
comma
l_string|&quot;aacraid&quot;
comma
l_string|&quot;ADAPTEC &quot;
comma
l_string|&quot;Adaptec 3240S   &quot;
comma
l_int|2
)brace
comma
multiline_comment|/* Adaptec 3240S (Tornado)*/
(brace
id|aac_rx_init
comma
l_string|&quot;aacraid&quot;
comma
l_string|&quot;ADAPTEC &quot;
comma
l_string|&quot;ASR-2020S PCI-X &quot;
comma
l_int|2
)brace
comma
multiline_comment|/* ASR-2020S PCI-X ZCR (Skyhawk)*/
(brace
id|aac_rx_init
comma
l_string|&quot;aacraid&quot;
comma
l_string|&quot;ADAPTEC &quot;
comma
l_string|&quot;ASR-2020S PCI-X &quot;
comma
l_int|2
)brace
comma
multiline_comment|/* ASR-2020S SO-DIMM PCI-X ZCR(Terminator)*/
(brace
id|aac_rx_init
comma
l_string|&quot;aacraid&quot;
comma
l_string|&quot;ADAPTEC &quot;
comma
l_string|&quot;AAR-2410SA SATA &quot;
comma
l_int|2
)brace
comma
multiline_comment|/* AAR-2410SA PCI SATA 4ch (Jaguar II)*/
(brace
id|aac_rx_init
comma
l_string|&quot;aacraid&quot;
comma
l_string|&quot;ADAPTEC &quot;
comma
l_string|&quot;Adaptec         &quot;
comma
l_int|2
)brace
comma
multiline_comment|/* (Marco)*/
(brace
id|aac_rx_init
comma
l_string|&quot;aacraid&quot;
comma
l_string|&quot;ADAPTEC &quot;
comma
l_string|&quot;Adaptec         &quot;
comma
l_int|2
)brace
comma
multiline_comment|/* (Sebring)*/
(brace
id|aac_rx_init
comma
l_string|&quot;percraid&quot;
comma
l_string|&quot;DELL    &quot;
comma
l_string|&quot;PERC 320/DC     &quot;
comma
l_int|2
)brace
comma
multiline_comment|/* Perc 320/DC*/
(brace
id|aac_sa_init
comma
l_string|&quot;aacraid&quot;
comma
l_string|&quot;ADAPTEC &quot;
comma
l_string|&quot;Adaptec 5400S   &quot;
comma
l_int|4
)brace
comma
multiline_comment|/* Adaptec 5400S (Mustang)*/
(brace
id|aac_sa_init
comma
l_string|&quot;aacraid&quot;
comma
l_string|&quot;ADAPTEC &quot;
comma
l_string|&quot;AAC-364         &quot;
comma
l_int|4
)brace
comma
multiline_comment|/* Adaptec 5400S (Mustang)*/
(brace
id|aac_sa_init
comma
l_string|&quot;percraid&quot;
comma
l_string|&quot;DELL    &quot;
comma
l_string|&quot;PERCRAID        &quot;
comma
l_int|4
)brace
comma
multiline_comment|/* Dell PERC2 &quot;Quad Channel&quot; */
(brace
id|aac_sa_init
comma
l_string|&quot;hpnraid&quot;
comma
l_string|&quot;HP      &quot;
comma
l_string|&quot;NetRAID         &quot;
comma
l_int|4
)brace
multiline_comment|/* HP NetRAID-4M */
)brace
suffix:semicolon
multiline_comment|/**&n; *&t;aac_queuecommand&t;-&t;queue a SCSI command&n; *&t;@cmd:&t;&t;SCSI command to queue&n; *&t;@done:&t;&t;Function to call on command completion&n; *&n; *&t;Queues a command for execution by the associated Host Adapter.&n; *&n; *&t;TODO: unify with aac_scsi_cmd().&n; */
DECL|function|aac_queuecommand
r_static
r_int
id|aac_queuecommand
c_func
(paren
r_struct
id|scsi_cmnd
op_star
id|cmd
comma
r_void
(paren
op_star
id|done
)paren
(paren
r_struct
id|scsi_cmnd
op_star
)paren
)paren
(brace
id|cmd-&gt;scsi_done
op_assign
id|done
suffix:semicolon
r_return
(paren
id|aac_scsi_cmd
c_func
(paren
id|cmd
)paren
ques
c_cond
id|FAILED
suffix:colon
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;aac_info&t;&t;-&t;Returns the host adapter name&n; *&t;@shost:&t;&t;Scsi host to report on&n; *&n; *&t;Returns a static string describing the device in question&n; */
DECL|function|aac_info
r_const
r_char
op_star
id|aac_info
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|shost
)paren
(brace
r_struct
id|aac_dev
op_star
id|dev
op_assign
(paren
r_struct
id|aac_dev
op_star
)paren
id|shost-&gt;hostdata
suffix:semicolon
r_return
id|aac_drivers
(braket
id|dev-&gt;cardtype
)braket
dot
id|name
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;aac_get_driver_ident&n; * &t;@devtype: index into lookup table&n; *&n; * &t;Returns a pointer to the entry in the driver lookup table.&n; */
DECL|function|aac_get_driver_ident
r_struct
id|aac_driver_ident
op_star
id|aac_get_driver_ident
c_func
(paren
r_int
id|devtype
)paren
(brace
r_return
op_amp
id|aac_drivers
(braket
id|devtype
)braket
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;aac_biosparm&t;-&t;return BIOS parameters for disk&n; *&t;@sdev: The scsi device corresponding to the disk&n; *&t;@bdev: the block device corresponding to the disk&n; *&t;@capacity: the sector capacity of the disk&n; *&t;@geom: geometry block to fill in&n; *&n; *&t;Return the Heads/Sectors/Cylinders BIOS Disk Parameters for Disk.  &n; *&t;The default disk geometry is 64 heads, 32 sectors, and the appropriate &n; *&t;number of cylinders so as not to exceed drive capacity.  In order for &n; *&t;disks equal to or larger than 1 GB to be addressable by the BIOS&n; *&t;without exceeding the BIOS limitation of 1024 cylinders, Extended &n; *&t;Translation should be enabled.   With Extended Translation enabled, &n; *&t;drives between 1 GB inclusive and 2 GB exclusive are given a disk &n; *&t;geometry of 128 heads and 32 sectors, and drives above 2 GB inclusive &n; *&t;are given a disk geometry of 255 heads and 63 sectors.  However, if &n; *&t;the BIOS detects that the Extended Translation setting does not match &n; *&t;the geometry in the partition table, then the translation inferred &n; *&t;from the partition table will be used by the BIOS, and a warning may &n; *&t;be displayed.&n; */
DECL|function|aac_biosparm
r_static
r_int
id|aac_biosparm
c_func
(paren
r_struct
id|scsi_device
op_star
id|sdev
comma
r_struct
id|block_device
op_star
id|bdev
comma
id|sector_t
id|capacity
comma
r_int
op_star
id|geom
)paren
(brace
r_struct
id|diskparm
op_star
id|param
op_assign
(paren
r_struct
id|diskparm
op_star
)paren
id|geom
suffix:semicolon
r_int
r_char
op_star
id|buf
suffix:semicolon
id|dprintk
c_func
(paren
(paren
id|KERN_DEBUG
l_string|&quot;aac_biosparm.&bslash;n&quot;
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Assuming extended translation is enabled - #REVISIT#&n;&t; */
r_if
c_cond
(paren
id|capacity
op_ge
l_int|2
op_star
l_int|1024
op_star
l_int|1024
)paren
(brace
multiline_comment|/* 1 GB in 512 byte sectors */
r_if
c_cond
(paren
id|capacity
op_ge
l_int|4
op_star
l_int|1024
op_star
l_int|1024
)paren
(brace
multiline_comment|/* 2 GB in 512 byte sectors */
id|param-&gt;heads
op_assign
l_int|255
suffix:semicolon
id|param-&gt;sectors
op_assign
l_int|63
suffix:semicolon
)brace
r_else
(brace
id|param-&gt;heads
op_assign
l_int|128
suffix:semicolon
id|param-&gt;sectors
op_assign
l_int|32
suffix:semicolon
)brace
)brace
r_else
(brace
id|param-&gt;heads
op_assign
l_int|64
suffix:semicolon
id|param-&gt;sectors
op_assign
l_int|32
suffix:semicolon
)brace
id|param-&gt;cylinders
op_assign
id|cap_to_cyls
c_func
(paren
id|capacity
comma
id|param-&gt;heads
op_star
id|param-&gt;sectors
)paren
suffix:semicolon
multiline_comment|/* &n;&t; *&t;Read the first 1024 bytes from the disk device, if the boot&n;&t; *&t;sector partition table is valid, search for a partition table&n;&t; *&t;entry whose end_head matches one of the standard geometry &n;&t; *&t;translations ( 64/32, 128/32, 255/63 ).&n;&t; */
id|buf
op_assign
id|scsi_bios_ptable
c_func
(paren
id|bdev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
(paren
r_int
r_int
op_star
)paren
(paren
id|buf
op_plus
l_int|0x40
)paren
op_eq
id|cpu_to_le16
c_func
(paren
l_int|0xaa55
)paren
)paren
(brace
r_struct
id|partition
op_star
id|first
op_assign
(paren
r_struct
id|partition
op_star
)paren
id|buf
suffix:semicolon
r_struct
id|partition
op_star
id|entry
op_assign
id|first
suffix:semicolon
r_int
id|saved_cylinders
op_assign
id|param-&gt;cylinders
suffix:semicolon
r_int
id|num
suffix:semicolon
r_int
r_char
id|end_head
comma
id|end_sec
suffix:semicolon
r_for
c_loop
(paren
id|num
op_assign
l_int|0
suffix:semicolon
id|num
OL
l_int|4
suffix:semicolon
id|num
op_increment
)paren
(brace
id|end_head
op_assign
id|entry-&gt;end_head
suffix:semicolon
id|end_sec
op_assign
id|entry-&gt;end_sector
op_amp
l_int|0x3f
suffix:semicolon
r_if
c_cond
(paren
id|end_head
op_eq
l_int|63
)paren
(brace
id|param-&gt;heads
op_assign
l_int|64
suffix:semicolon
id|param-&gt;sectors
op_assign
l_int|32
suffix:semicolon
r_break
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|end_head
op_eq
l_int|127
)paren
(brace
id|param-&gt;heads
op_assign
l_int|128
suffix:semicolon
id|param-&gt;sectors
op_assign
l_int|32
suffix:semicolon
r_break
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|end_head
op_eq
l_int|254
)paren
(brace
id|param-&gt;heads
op_assign
l_int|255
suffix:semicolon
id|param-&gt;sectors
op_assign
l_int|63
suffix:semicolon
r_break
suffix:semicolon
)brace
id|entry
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|num
op_eq
l_int|4
)paren
(brace
id|end_head
op_assign
id|first-&gt;end_head
suffix:semicolon
id|end_sec
op_assign
id|first-&gt;end_sector
op_amp
l_int|0x3f
suffix:semicolon
)brace
id|param-&gt;cylinders
op_assign
id|cap_to_cyls
c_func
(paren
id|capacity
comma
id|param-&gt;heads
op_star
id|param-&gt;sectors
)paren
suffix:semicolon
r_if
c_cond
(paren
id|num
OL
l_int|4
op_logical_and
id|end_sec
op_eq
id|param-&gt;sectors
)paren
(brace
r_if
c_cond
(paren
id|param-&gt;cylinders
op_ne
id|saved_cylinders
)paren
id|dprintk
c_func
(paren
(paren
id|KERN_DEBUG
l_string|&quot;Adopting geometry: heads=%d, sectors=%d from partition table %d.&bslash;n&quot;
comma
id|param-&gt;heads
comma
id|param-&gt;sectors
comma
id|num
)paren
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|end_head
OG
l_int|0
op_logical_or
id|end_sec
OG
l_int|0
)paren
(brace
id|dprintk
c_func
(paren
(paren
id|KERN_DEBUG
l_string|&quot;Strange geometry: heads=%d, sectors=%d in partition table %d.&bslash;n&quot;
comma
id|end_head
op_plus
l_int|1
comma
id|end_sec
comma
id|num
)paren
)paren
suffix:semicolon
id|dprintk
c_func
(paren
(paren
id|KERN_DEBUG
l_string|&quot;Using geometry: heads=%d, sectors=%d.&bslash;n&quot;
comma
id|param-&gt;heads
comma
id|param-&gt;sectors
)paren
)paren
suffix:semicolon
)brace
)brace
id|kfree
c_func
(paren
id|buf
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;aac_queuedepth&t;&t;-&t;compute queue depths&n; *&t;@sdev:&t;SCSI device we are considering&n; *&n; *&t;Selects queue depths for each target device based on the host adapter&squot;s&n; *&t;total capacity and the queue depth supported by the target device.&n; *&t;A queue depth of one automatically disables tagged queueing.&n; */
DECL|function|aac_slave_configure
r_static
r_int
id|aac_slave_configure
c_func
(paren
r_struct
id|scsi_device
op_star
id|sdev
)paren
(brace
r_if
c_cond
(paren
id|sdev-&gt;tagged_supported
)paren
id|scsi_adjust_queue_depth
c_func
(paren
id|sdev
comma
id|MSG_ORDERED_TAG
comma
l_int|128
)paren
suffix:semicolon
r_else
id|scsi_adjust_queue_depth
c_func
(paren
id|sdev
comma
l_int|0
comma
l_int|1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|aac_ioctl
r_static
r_int
id|aac_ioctl
c_func
(paren
r_struct
id|scsi_device
op_star
id|sdev
comma
r_int
id|cmd
comma
r_void
op_star
id|arg
)paren
(brace
r_struct
id|aac_dev
op_star
id|dev
op_assign
(paren
r_struct
id|aac_dev
op_star
)paren
id|sdev-&gt;host-&gt;hostdata
suffix:semicolon
r_return
id|aac_do_ioctl
c_func
(paren
id|dev
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * XXX: does aac really need no error handling??&n; */
DECL|function|aac_eh_abort
r_static
r_int
id|aac_eh_abort
c_func
(paren
r_struct
id|scsi_cmnd
op_star
id|cmd
)paren
(brace
r_return
id|FAILED
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;aac_cfg_open&t;&t;-&t;open a configuration file&n; *&t;@inode: inode being opened&n; *&t;@file: file handle attached&n; *&n; *&t;Called when the configuration device is opened. Does the needed&n; *&t;set up on the handle and then returns&n; *&n; *&t;Bugs: This needs extending to check a given adapter is present&n; *&t;so we can support hot plugging, and to ref count adapters.&n; */
DECL|function|aac_cfg_open
r_static
r_int
id|aac_cfg_open
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_int
id|minor
op_assign
id|iminor
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|minor
op_ge
id|aac_count
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|file-&gt;private_data
op_assign
id|aac_devices
(braket
id|minor
)braket
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;aac_cfg_ioctl&t;&t;-&t;AAC configuration request&n; *&t;@inode: inode of device&n; *&t;@file: file handle&n; *&t;@cmd: ioctl command code&n; *&t;@arg: argument&n; *&n; *&t;Handles a configuration ioctl. Currently this involves wrapping it&n; *&t;up and feeding it into the nasty windowsalike glue layer.&n; *&n; *&t;Bugs: Needs locking against parallel ioctls lower down&n; *&t;Bugs: Needs to handle hot plugging&n; */
DECL|function|aac_cfg_ioctl
r_static
r_int
id|aac_cfg_ioctl
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_return
id|aac_do_ioctl
c_func
(paren
id|file-&gt;private_data
comma
id|cmd
comma
(paren
r_void
op_star
)paren
id|arg
)paren
suffix:semicolon
)brace
DECL|variable|aac_cfg_fops
r_static
r_struct
id|file_operations
id|aac_cfg_fops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|ioctl
op_assign
id|aac_cfg_ioctl
comma
dot
id|open
op_assign
id|aac_cfg_open
comma
)brace
suffix:semicolon
DECL|variable|aac_driver_template
r_static
r_struct
id|scsi_host_template
id|aac_driver_template
op_assign
(brace
dot
id|module
op_assign
id|THIS_MODULE
comma
dot
id|name
op_assign
l_string|&quot;AAC&quot;
comma
dot
id|proc_name
op_assign
l_string|&quot;aacraid&quot;
comma
dot
id|info
op_assign
id|aac_info
comma
dot
id|ioctl
op_assign
id|aac_ioctl
comma
dot
id|queuecommand
op_assign
id|aac_queuecommand
comma
dot
id|bios_param
op_assign
id|aac_biosparm
comma
dot
id|slave_configure
op_assign
id|aac_slave_configure
comma
dot
id|eh_abort_handler
op_assign
id|aac_eh_abort
comma
dot
id|can_queue
op_assign
id|AAC_NUM_IO_FIB
comma
dot
id|this_id
op_assign
l_int|16
comma
dot
id|sg_tablesize
op_assign
l_int|16
comma
dot
id|max_sectors
op_assign
l_int|128
comma
dot
id|cmd_per_lun
op_assign
id|AAC_NUM_IO_FIB
comma
dot
id|use_clustering
op_assign
id|ENABLE_CLUSTERING
comma
)brace
suffix:semicolon
DECL|function|aac_probe_one
r_static
r_int
id|__devinit
id|aac_probe_one
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
r_const
r_struct
id|pci_device_id
op_star
id|id
)paren
(brace
r_int
id|index
op_assign
id|id-&gt;driver_data
suffix:semicolon
r_struct
id|Scsi_Host
op_star
id|shost
suffix:semicolon
r_struct
id|fsa_scsi_hba
op_star
id|fsa_dev_ptr
suffix:semicolon
r_struct
id|aac_dev
op_star
id|aac
suffix:semicolon
r_int
id|container
suffix:semicolon
r_int
id|error
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|pci_enable_device
c_func
(paren
id|pdev
)paren
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|pci_set_dma_mask
c_func
(paren
id|pdev
comma
l_int|0xFFFFFFFFULL
)paren
)paren
r_goto
id|out
suffix:semicolon
id|pci_set_master
c_func
(paren
id|pdev
)paren
suffix:semicolon
multiline_comment|/* Increment the host adapter count */
id|aac_count
op_increment
suffix:semicolon
id|shost
op_assign
id|scsi_host_alloc
c_func
(paren
op_amp
id|aac_driver_template
comma
r_sizeof
(paren
r_struct
id|aac_dev
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|shost
)paren
r_goto
id|out_disable_pdev
suffix:semicolon
id|shost-&gt;irq
op_assign
id|pdev-&gt;irq
suffix:semicolon
id|shost-&gt;base
op_assign
id|pci_resource_start
c_func
(paren
id|pdev
comma
l_int|0
)paren
suffix:semicolon
id|shost-&gt;unique_id
op_assign
id|aac_count
op_minus
l_int|1
suffix:semicolon
id|aac
op_assign
(paren
r_struct
id|aac_dev
op_star
)paren
id|shost-&gt;hostdata
suffix:semicolon
id|aac-&gt;scsi_host_ptr
op_assign
id|shost
suffix:semicolon
id|aac-&gt;pdev
op_assign
id|pdev
suffix:semicolon
id|aac-&gt;name
op_assign
id|aac_driver_template.name
suffix:semicolon
id|aac-&gt;id
op_assign
id|shost-&gt;unique_id
suffix:semicolon
id|aac-&gt;cardtype
op_assign
id|index
suffix:semicolon
id|aac-&gt;fibs
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|fib
)paren
op_star
id|AAC_NUM_FIB
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|aac-&gt;fibs
)paren
r_goto
id|out_free_host
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|aac-&gt;fib_lock
)paren
suffix:semicolon
multiline_comment|/* Initialize the ordinal number of the device to -1 */
id|fsa_dev_ptr
op_assign
op_amp
id|aac-&gt;fsa_dev
suffix:semicolon
r_for
c_loop
(paren
id|container
op_assign
l_int|0
suffix:semicolon
id|container
OL
id|MAXIMUM_NUM_CONTAINERS
suffix:semicolon
id|container
op_increment
)paren
id|fsa_dev_ptr-&gt;devname
(braket
id|container
)braket
(braket
l_int|0
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|aac_drivers
(braket
id|index
)braket
dot
id|init
)paren
(paren
id|aac
comma
id|shost-&gt;unique_id
)paren
)paren
r_goto
id|out_free_fibs
suffix:semicolon
id|aac_get_adapter_info
c_func
(paren
id|aac
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * max channel will be the physical channels plus 1 virtual channel&n;&t; * all containers are on the virtual channel 0&n;&t; * physical channels are address by their actual physical number+1&n;&t; */
r_if
c_cond
(paren
id|aac-&gt;nondasd_support
op_eq
l_int|1
)paren
id|shost-&gt;max_channel
op_assign
id|aac_drivers
(braket
id|index
)braket
dot
id|channels
op_plus
l_int|1
suffix:semicolon
r_else
id|shost-&gt;max_channel
op_assign
l_int|1
suffix:semicolon
id|aac_get_containers
c_func
(paren
id|aac
)paren
suffix:semicolon
id|aac_devices
(braket
id|aac_count
op_minus
l_int|1
)braket
op_assign
id|aac
suffix:semicolon
multiline_comment|/*&n;&t; * dmb - we may need to move the setting of these parms somewhere else once&n;&t; * we get a fib that can report the actual numbers&n;&t; */
id|shost-&gt;max_id
op_assign
id|AAC_MAX_TARGET
suffix:semicolon
id|shost-&gt;max_lun
op_assign
id|AAC_MAX_LUN
suffix:semicolon
id|error
op_assign
id|scsi_add_host
c_func
(paren
id|shost
comma
op_amp
id|pdev-&gt;dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|out_deinit
suffix:semicolon
id|pci_set_drvdata
c_func
(paren
id|pdev
comma
id|shost
)paren
suffix:semicolon
id|scsi_scan_host
c_func
(paren
id|shost
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|out_deinit
suffix:colon
id|kill_proc
c_func
(paren
id|aac-&gt;thread_pid
comma
id|SIGKILL
comma
l_int|0
)paren
suffix:semicolon
id|wait_for_completion
c_func
(paren
op_amp
id|aac-&gt;aif_completion
)paren
suffix:semicolon
id|aac_send_shutdown
c_func
(paren
id|aac
)paren
suffix:semicolon
id|fib_map_free
c_func
(paren
id|aac
)paren
suffix:semicolon
id|pci_free_consistent
c_func
(paren
id|aac-&gt;pdev
comma
id|aac-&gt;comm_size
comma
id|aac-&gt;comm_addr
comma
id|aac-&gt;comm_phys
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|aac-&gt;queues
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|pdev-&gt;irq
comma
id|aac
)paren
suffix:semicolon
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
id|aac-&gt;regs.sa
)paren
suffix:semicolon
id|out_free_fibs
suffix:colon
id|kfree
c_func
(paren
id|aac-&gt;fibs
)paren
suffix:semicolon
id|out_free_host
suffix:colon
id|scsi_host_put
c_func
(paren
id|shost
)paren
suffix:semicolon
id|out_disable_pdev
suffix:colon
id|pci_disable_device
c_func
(paren
id|pdev
)paren
suffix:semicolon
id|aac_count
op_decrement
suffix:semicolon
id|out
suffix:colon
r_return
id|error
suffix:semicolon
)brace
DECL|function|aac_remove_one
r_static
r_void
id|__devexit
id|aac_remove_one
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
)paren
(brace
r_struct
id|Scsi_Host
op_star
id|shost
op_assign
id|pci_get_drvdata
c_func
(paren
id|pdev
)paren
suffix:semicolon
r_struct
id|aac_dev
op_star
id|aac
op_assign
(paren
r_struct
id|aac_dev
op_star
)paren
id|shost-&gt;hostdata
suffix:semicolon
id|scsi_remove_host
c_func
(paren
id|shost
)paren
suffix:semicolon
id|kill_proc
c_func
(paren
id|aac-&gt;thread_pid
comma
id|SIGKILL
comma
l_int|0
)paren
suffix:semicolon
id|wait_for_completion
c_func
(paren
op_amp
id|aac-&gt;aif_completion
)paren
suffix:semicolon
id|aac_send_shutdown
c_func
(paren
id|aac
)paren
suffix:semicolon
id|fib_map_free
c_func
(paren
id|aac
)paren
suffix:semicolon
id|pci_free_consistent
c_func
(paren
id|aac-&gt;pdev
comma
id|aac-&gt;comm_size
comma
id|aac-&gt;comm_addr
comma
id|aac-&gt;comm_phys
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|aac-&gt;queues
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|pdev-&gt;irq
comma
id|aac
)paren
suffix:semicolon
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
id|aac-&gt;regs.sa
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|aac-&gt;fibs
)paren
suffix:semicolon
id|scsi_host_put
c_func
(paren
id|shost
)paren
suffix:semicolon
id|pci_disable_device
c_func
(paren
id|pdev
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * We don&squot;t decrement aac_count here because adapters can be unplugged&n;&t; * in a different order than they were detected.  If we&squot;re ever going&n;&t; * to overflow MAXIMUM_NUM_ADAPTERS we&squot;ll have to consider using a&n;&t; * bintmap of free aac_devices slots.&n;&t; */
macro_line|#if 0
id|aac_count
op_decrement
suffix:semicolon
macro_line|#endif
)brace
DECL|variable|aac_pci_driver
r_static
r_struct
id|pci_driver
id|aac_pci_driver
op_assign
(brace
dot
id|name
op_assign
id|AAC_DRIVERNAME
comma
dot
id|id_table
op_assign
id|aac_pci_tbl
comma
dot
id|probe
op_assign
id|aac_probe_one
comma
dot
id|remove
op_assign
id|__devexit_p
c_func
(paren
id|aac_remove_one
)paren
comma
)brace
suffix:semicolon
DECL|function|aac_init
r_static
r_int
id|__init
id|aac_init
c_func
(paren
r_void
)paren
(brace
r_int
id|error
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Red Hat/Adaptec aacraid driver (%s %s)&bslash;n&quot;
comma
id|AAC_DRIVER_VERSION
comma
id|AAC_DRIVER_BUILD_DATE
)paren
suffix:semicolon
id|error
op_assign
id|pci_module_init
c_func
(paren
op_amp
id|aac_pci_driver
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
id|aac_cfg_major
op_assign
id|register_chrdev
c_func
(paren
l_int|0
comma
l_string|&quot;aac&quot;
comma
op_amp
id|aac_cfg_fops
)paren
suffix:semicolon
r_if
c_cond
(paren
id|aac_cfg_major
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;aacraid: unable to register &bslash;&quot;aac&bslash;&quot; device.&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|aac_exit
r_static
r_void
id|__exit
id|aac_exit
c_func
(paren
r_void
)paren
(brace
id|unregister_chrdev
c_func
(paren
id|aac_cfg_major
comma
l_string|&quot;aac&quot;
)paren
suffix:semicolon
id|pci_unregister_driver
c_func
(paren
op_amp
id|aac_pci_driver
)paren
suffix:semicolon
)brace
DECL|variable|aac_init
id|module_init
c_func
(paren
id|aac_init
)paren
suffix:semicolon
DECL|variable|aac_exit
id|module_exit
c_func
(paren
id|aac_exit
)paren
suffix:semicolon
eof
