multiline_comment|/**** vi:set ts=8 sts=8 sw=8:************************************************&n; *&n; * Copyright (C) 2002 Marcin Dalecki &lt;martin@dalecki.de&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License version 2 as published by&n; * the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it will be useful, but WITHOUT&n; * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or&n; * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for&n; * more details.&n; */
multiline_comment|/*&n; * Generic ioctl handling for all ATA/ATAPI device drivers.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/blkpg.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/cdrom.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;ioctl.h&quot;
multiline_comment|/*&n; * Implement generic ioctls invoked from userspace to imlpement specific&n; * functionality.&n; *&n; * Unfortunately every single low level programm out there is using this&n; * interface.&n; */
DECL|function|do_cmd_ioctl
r_static
r_int
id|do_cmd_ioctl
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
comma
r_int
r_int
id|arg
)paren
(brace
r_int
id|err
op_assign
l_int|0
suffix:semicolon
id|u8
id|vals
(braket
l_int|4
)braket
suffix:semicolon
id|u8
op_star
id|argbuf
op_assign
id|vals
suffix:semicolon
r_int
id|argsize
op_assign
l_int|4
suffix:semicolon
r_struct
id|ata_taskfile
id|args
suffix:semicolon
multiline_comment|/* Second phase.&n;&t; */
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|vals
comma
(paren
r_void
op_star
)paren
id|arg
comma
l_int|4
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|args
comma
l_int|0
comma
r_sizeof
(paren
id|args
)paren
)paren
suffix:semicolon
id|args.taskfile.feature
op_assign
id|vals
(braket
l_int|2
)braket
suffix:semicolon
id|args.taskfile.sector_count
op_assign
id|vals
(braket
l_int|1
)braket
suffix:semicolon
id|args.taskfile.sector_number
op_assign
id|vals
(braket
l_int|3
)braket
suffix:semicolon
r_if
c_cond
(paren
id|vals
(braket
l_int|0
)braket
op_eq
id|WIN_SMART
)paren
(brace
id|args.taskfile.low_cylinder
op_assign
l_int|0x4f
suffix:semicolon
id|args.taskfile.high_cylinder
op_assign
l_int|0xc2
suffix:semicolon
)brace
r_else
(brace
id|args.taskfile.low_cylinder
op_assign
l_int|0x00
suffix:semicolon
id|args.taskfile.high_cylinder
op_assign
l_int|0x00
suffix:semicolon
)brace
id|args.taskfile.device_head
op_assign
l_int|0x00
suffix:semicolon
id|args.cmd
op_assign
id|vals
(braket
l_int|0
)braket
suffix:semicolon
r_if
c_cond
(paren
id|vals
(braket
l_int|3
)braket
)paren
(brace
id|argsize
op_assign
l_int|4
op_plus
(paren
id|SECTOR_WORDS
op_star
l_int|4
op_star
id|vals
(braket
l_int|3
)braket
)paren
suffix:semicolon
id|argbuf
op_assign
id|kmalloc
c_func
(paren
id|argsize
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|argbuf
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memcpy
c_func
(paren
id|argbuf
comma
id|vals
comma
l_int|4
)paren
suffix:semicolon
id|memset
c_func
(paren
id|argbuf
op_plus
l_int|4
comma
l_int|0
comma
id|argsize
op_minus
l_int|4
)paren
suffix:semicolon
)brace
multiline_comment|/* Issue ATA command and wait for completion.&n;&t; */
id|err
op_assign
id|ide_raw_taskfile
c_func
(paren
id|drive
comma
op_amp
id|args
comma
id|argbuf
op_plus
l_int|4
)paren
suffix:semicolon
id|argbuf
(braket
l_int|0
)braket
op_assign
id|drive-&gt;status
suffix:semicolon
id|argbuf
(braket
l_int|1
)braket
op_assign
id|args.taskfile.feature
suffix:semicolon
id|argbuf
(braket
l_int|2
)braket
op_assign
id|args.taskfile.sector_count
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_void
op_star
)paren
id|arg
comma
id|argbuf
comma
id|argsize
)paren
)paren
id|err
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|argsize
OG
l_int|4
)paren
id|kfree
c_func
(paren
id|argbuf
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*&n; * NOTE: Due to ridiculous coding habbits in the hdparm utility we have to&n; * always return unsigned long in case we are returning simple values.&n; */
DECL|function|ata_ioctl
r_int
id|ata_ioctl
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
r_int
r_int
id|major
comma
id|minor
suffix:semicolon
r_struct
id|ata_device
op_star
id|drive
suffix:semicolon
id|kdev_t
id|dev
suffix:semicolon
id|dev
op_assign
id|inode-&gt;i_rdev
suffix:semicolon
id|major
op_assign
id|major
c_func
(paren
id|dev
)paren
suffix:semicolon
id|minor
op_assign
id|minor
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|drive
op_assign
id|get_info_ptr
c_func
(paren
id|inode-&gt;i_rdev
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
multiline_comment|/* Contrary to popular beleve we disallow even the reading of the ioctl&n;&t; * values for users which don&squot;t have permission too. We do this becouse&n;&t; * such information could be used by an attacker to deply a simple-user&n;&t; * attack, which triggers bugs present only on a particular&n;&t; * configuration.&n;&t; */
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|HDIO_GET_32BIT
suffix:colon
(brace
r_int
r_int
id|val
op_assign
id|drive-&gt;channel-&gt;io_32bit
suffix:semicolon
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|val
comma
(paren
r_int
r_int
op_star
)paren
id|arg
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|HDIO_SET_32BIT
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
r_if
c_cond
(paren
id|arg
template_param
l_int|1
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|drive-&gt;channel-&gt;no_io_32bit
)paren
r_return
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
id|ide_spin_wait_hwgroup
c_func
(paren
id|drive
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|drive-&gt;channel-&gt;io_32bit
op_assign
id|arg
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
id|drive-&gt;channel-&gt;lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|HDIO_SET_PIO_MODE
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
r_if
c_cond
(paren
id|arg
template_param
l_int|255
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|drive-&gt;channel-&gt;tuneproc
)paren
r_return
op_minus
id|ENOSYS
suffix:semicolon
multiline_comment|/* FIXME: we can see that tuneproc whould do the&n;&t;&t;&t; * locking!.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|ide_spin_wait_hwgroup
c_func
(paren
id|drive
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|drive-&gt;channel
op_member_access_from_pointer
id|tuneproc
c_func
(paren
id|drive
comma
(paren
id|u8
)paren
id|arg
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
id|drive-&gt;channel-&gt;lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|HDIO_GET_UNMASKINTR
suffix:colon
(brace
r_int
r_int
id|val
op_assign
id|drive-&gt;channel-&gt;unmask
suffix:semicolon
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|val
comma
(paren
r_int
r_int
op_star
)paren
id|arg
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|HDIO_SET_UNMASKINTR
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
r_if
c_cond
(paren
id|arg
template_param
l_int|1
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|drive-&gt;channel-&gt;no_unmask
)paren
r_return
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
id|ide_spin_wait_hwgroup
c_func
(paren
id|drive
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|drive-&gt;channel-&gt;unmask
op_assign
id|arg
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
id|drive-&gt;channel-&gt;lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|HDIO_GET_DMA
suffix:colon
(brace
r_int
r_int
id|val
op_assign
id|drive-&gt;using_dma
suffix:semicolon
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|val
comma
(paren
r_int
r_int
op_star
)paren
id|arg
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|HDIO_SET_DMA
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
r_if
c_cond
(paren
id|arg
template_param
l_int|1
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|drive-&gt;driver
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|drive-&gt;id
op_logical_or
op_logical_neg
(paren
id|drive-&gt;id-&gt;capability
op_amp
l_int|1
)paren
op_logical_or
op_logical_neg
id|drive-&gt;channel-&gt;udma_setup
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|ide_spin_wait_hwgroup
c_func
(paren
id|drive
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|udma_enable
c_func
(paren
id|drive
comma
id|arg
comma
l_int|1
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
id|drive-&gt;channel-&gt;lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|HDIO_GETGEO
suffix:colon
(brace
r_struct
id|hd_geometry
op_star
id|loc
op_assign
(paren
r_struct
id|hd_geometry
op_star
)paren
id|arg
suffix:semicolon
r_int
r_int
id|bios_cyl
op_assign
id|drive-&gt;bios_cyl
suffix:semicolon
multiline_comment|/* truncate */
r_if
c_cond
(paren
op_logical_neg
id|loc
op_logical_or
(paren
id|drive-&gt;type
op_ne
id|ATA_DISK
op_logical_and
id|drive-&gt;type
op_ne
id|ATA_FLOPPY
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|drive-&gt;bios_head
comma
(paren
id|byte
op_star
)paren
op_amp
id|loc-&gt;heads
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|drive-&gt;bios_sect
comma
(paren
id|byte
op_star
)paren
op_amp
id|loc-&gt;sectors
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|bios_cyl
comma
(paren
r_int
r_int
op_star
)paren
op_amp
id|loc-&gt;cylinders
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|put_user
c_func
(paren
(paren
r_int
)paren
id|drive-&gt;part
(braket
id|minor
c_func
(paren
id|inode-&gt;i_rdev
)paren
op_amp
id|PARTN_MASK
)braket
dot
id|start_sect
comma
(paren
r_int
r_int
op_star
)paren
op_amp
id|loc-&gt;start
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|HDIO_GETGEO_BIG_RAW
suffix:colon
(brace
r_struct
id|hd_big_geometry
op_star
id|loc
op_assign
(paren
r_struct
id|hd_big_geometry
op_star
)paren
id|arg
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|loc
op_logical_or
(paren
id|drive-&gt;type
op_ne
id|ATA_DISK
op_logical_and
id|drive-&gt;type
op_ne
id|ATA_FLOPPY
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|drive-&gt;head
comma
(paren
id|u8
op_star
)paren
op_amp
id|loc-&gt;heads
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|drive-&gt;sect
comma
(paren
id|u8
op_star
)paren
op_amp
id|loc-&gt;sectors
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|drive-&gt;cyl
comma
(paren
r_int
r_int
op_star
)paren
op_amp
id|loc-&gt;cylinders
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|put_user
c_func
(paren
(paren
r_int
)paren
id|drive-&gt;part
(braket
id|minor
c_func
(paren
id|inode-&gt;i_rdev
)paren
op_amp
id|PARTN_MASK
)braket
dot
id|start_sect
comma
(paren
r_int
r_int
op_star
)paren
op_amp
id|loc-&gt;start
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|HDIO_GET_IDENTITY
suffix:colon
r_if
c_cond
(paren
id|minor
c_func
(paren
id|inode-&gt;i_rdev
)paren
op_amp
id|PARTN_MASK
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|drive-&gt;id
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMSG
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_char
op_star
)paren
id|arg
comma
(paren
r_char
op_star
)paren
id|drive-&gt;id
comma
r_sizeof
(paren
op_star
id|drive-&gt;id
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|HDIO_GET_NICE
suffix:colon
r_return
id|put_user
c_func
(paren
id|drive-&gt;dsc_overlap
op_lshift
id|IDE_NICE_DSC_OVERLAP
op_or
id|drive-&gt;atapi_overlap
op_lshift
id|IDE_NICE_ATAPI_OVERLAP
comma
(paren
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
r_case
id|HDIO_SET_NICE
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
r_if
c_cond
(paren
id|arg
op_ne
(paren
id|arg
op_amp
(paren
(paren
l_int|1
op_lshift
id|IDE_NICE_DSC_OVERLAP
)paren
)paren
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
id|drive-&gt;dsc_overlap
op_assign
(paren
id|arg
op_rshift
id|IDE_NICE_DSC_OVERLAP
)paren
op_amp
l_int|1
suffix:semicolon
multiline_comment|/* Only CD-ROM&squot;s and tapes support DSC overlap. */
r_if
c_cond
(paren
id|drive-&gt;dsc_overlap
op_logical_and
op_logical_neg
(paren
id|drive-&gt;type
op_eq
id|ATA_ROM
op_logical_or
id|drive-&gt;type
op_eq
id|ATA_TAPE
)paren
)paren
(brace
id|drive-&gt;dsc_overlap
op_assign
l_int|0
suffix:semicolon
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
r_case
id|HDIO_GET_BUSSTATE
suffix:colon
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|drive-&gt;channel-&gt;bus_state
comma
(paren
r_int
op_star
)paren
id|arg
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|HDIO_SET_BUSSTATE
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
r_if
c_cond
(paren
id|drive-&gt;channel-&gt;busproc
)paren
id|drive-&gt;channel
op_member_access_from_pointer
id|busproc
c_func
(paren
id|drive
comma
(paren
r_int
)paren
id|arg
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|HDIO_DRIVE_CMD
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|arg
)paren
(brace
r_if
c_cond
(paren
id|ide_spin_wait_hwgroup
c_func
(paren
id|drive
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
multiline_comment|/* Do nothing, just unlock */
id|spin_unlock_irq
c_func
(paren
id|drive-&gt;channel-&gt;lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
id|do_cmd_ioctl
c_func
(paren
id|drive
comma
id|arg
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * uniform packet command handling&n;&t;&t; */
r_case
id|CDROMEJECT
suffix:colon
r_case
id|CDROMCLOSETRAY
suffix:colon
r_return
id|block_ioctl
c_func
(paren
id|inode-&gt;i_bdev
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
r_case
id|BLKRRPART
suffix:colon
multiline_comment|/* Re-read partition tables */
r_return
id|ata_revalidate
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
r_case
id|BLKGETSIZE
suffix:colon
r_case
id|BLKGETSIZE64
suffix:colon
r_case
id|BLKROSET
suffix:colon
r_case
id|BLKROGET
suffix:colon
r_case
id|BLKFLSBUF
suffix:colon
r_case
id|BLKSSZGET
suffix:colon
r_case
id|BLKPG
suffix:colon
r_case
id|BLKELVGET
suffix:colon
r_case
id|BLKELVSET
suffix:colon
r_case
id|BLKBSZGET
suffix:colon
r_case
id|BLKBSZSET
suffix:colon
r_return
id|blk_ioctl
c_func
(paren
id|inode-&gt;i_bdev
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
multiline_comment|/* Now check whatever this particular ioctl has a device type&n;&t;&t; * specific implementation.&n;&t;&t; */
r_default
suffix:colon
(brace
)brace
r_if
c_cond
(paren
id|ata_ops
c_func
(paren
id|drive
)paren
op_logical_and
id|ata_ops
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|ioctl
)paren
r_return
id|ata_ops
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|ioctl
c_func
(paren
id|drive
comma
id|inode
comma
id|file
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
eof
