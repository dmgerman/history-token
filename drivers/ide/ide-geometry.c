multiline_comment|/*&n; * linux/drivers/ide/ide-geometry.c&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;linux/mc146818rtc.h&gt;
macro_line|#include &lt;asm/io.h&gt;
multiline_comment|/*&n; * We query CMOS about hard disks : it could be that we have a SCSI/ESDI/etc&n; * controller that is BIOS compatible with ST-506, and thus showing up in our&n; * BIOS table, but not register compatible, and therefore not present in CMOS.&n; *&n; * Furthermore, we will assume that our ST-506 drives &lt;if any&gt; are the primary&n; * drives in the system -- the ones reflected as drive 1 or 2.  The first&n; * drive is stored in the high nibble of CMOS byte 0x12, the second in the low&n; * nibble.  This will be either a 4 bit drive type or 0xf indicating use byte&n; * 0x19 for an 8 bit type, drive 1, 0x1a for drive 2 in CMOS.  A non-zero value&n; * means we have an AT controller hard disk for that drive.&n; *&n; * Of course, there is no guarantee that either drive is actually on the&n; * &quot;primary&quot; IDE interface, but we don&squot;t bother trying to sort that out here.&n; * If a drive is not actually on the primary interface, then these parameters&n; * will be ignored.  This results in the user having to supply the logical&n; * drive geometry as a boot parameter for each drive not on the primary i/f.&n; *&n; * The only &quot;perfect&quot; way to handle this would be to modify the setup.[cS] code&n; * to do BIOS calls Int13h/Fn08h and Int13h/Fn48h to get all of the drive info&n; * for us during initialization.  I have the necessary docs -- any takers?  -ml&n; *&n; * I did this, but it doesn&squot;t work - there is no reasonable way to find the&n; * correspondence between the BIOS numbering of the disks and the Linux&n; * numbering. -aeb&n; *&n; * The code below is bad. One of the problems is that drives 1 and 2&n; * may be SCSI disks (even when IDE disks are present), so that&n; * the geometry we read here from BIOS is attributed to the wrong disks.&n; * Consequently, also the former &quot;drive-&gt;present = 1&quot; below was a mistake.&n; *&n; * Eventually the entire routine below should be removed.&n; *&n; * 17-OCT-2000 rjohnson@analogic.com Added spin-locks for reading CMOS&n; * chip.&n; */
DECL|function|probe_cmos_for_drives
r_void
id|probe_cmos_for_drives
(paren
id|ide_hwif_t
op_star
id|hwif
)paren
(brace
macro_line|#ifdef __i386__
r_extern
r_struct
id|drive_info_struct
id|drive_info
suffix:semicolon
id|u8
id|cmos_disks
comma
op_star
id|BIOS
op_assign
(paren
id|u8
op_star
)paren
op_amp
id|drive_info
suffix:semicolon
r_int
id|unit
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|hwif-&gt;chipset
op_eq
id|ide_pdc4030
op_logical_and
id|hwif-&gt;channel
op_ne
l_int|0
)paren
r_return
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|rtc_lock
comma
id|flags
)paren
suffix:semicolon
id|cmos_disks
op_assign
id|CMOS_READ
c_func
(paren
l_int|0x12
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|rtc_lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* Extract drive geometry from CMOS+BIOS if not already setup */
r_for
c_loop
(paren
id|unit
op_assign
l_int|0
suffix:semicolon
id|unit
OL
id|MAX_DRIVES
suffix:semicolon
op_increment
id|unit
)paren
(brace
id|ide_drive_t
op_star
id|drive
op_assign
op_amp
id|hwif-&gt;drives
(braket
id|unit
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
id|cmos_disks
op_amp
(paren
l_int|0xf0
op_rshift
(paren
id|unit
op_star
l_int|4
)paren
)paren
)paren
op_logical_and
op_logical_neg
id|drive-&gt;present
op_logical_and
op_logical_neg
id|drive-&gt;nobios
)paren
(brace
id|u16
id|cyl
op_assign
op_star
(paren
id|u16
op_star
)paren
id|BIOS
suffix:semicolon
r_int
r_char
id|head
op_assign
op_star
(paren
id|BIOS
op_plus
l_int|2
)paren
suffix:semicolon
r_int
r_char
id|sect
op_assign
op_star
(paren
id|BIOS
op_plus
l_int|14
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cyl
OG
l_int|0
op_logical_and
id|head
OG
l_int|0
op_logical_and
id|sect
OG
l_int|0
op_logical_and
id|sect
OL
l_int|64
)paren
(brace
id|drive-&gt;cyl
op_assign
id|drive-&gt;bios_cyl
op_assign
id|cyl
suffix:semicolon
id|drive-&gt;head
op_assign
id|drive-&gt;bios_head
op_assign
id|head
suffix:semicolon
id|drive-&gt;sect
op_assign
id|drive-&gt;bios_sect
op_assign
id|sect
suffix:semicolon
id|drive-&gt;ctl
op_assign
op_star
(paren
id|BIOS
op_plus
l_int|8
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;hd%c: C/H/S=%d/%d/%d from BIOS ignored&bslash;n&quot;
comma
id|unit
op_plus
l_char|&squot;a&squot;
comma
id|cyl
comma
id|head
comma
id|sect
)paren
suffix:semicolon
)brace
)brace
id|BIOS
op_add_assign
l_int|16
suffix:semicolon
)brace
macro_line|#endif
)brace
r_extern
r_int
r_int
id|current_capacity
(paren
id|ide_drive_t
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * If heads is nonzero: find a translation with this many heads and S=63.&n; * Otherwise: find out how OnTrack Disk Manager would translate the disk.&n; */
DECL|function|ontrack
r_static
r_void
id|ontrack
c_func
(paren
id|ide_drive_t
op_star
id|drive
comma
r_int
id|heads
comma
r_int
r_int
op_star
id|c
comma
r_int
op_star
id|h
comma
r_int
op_star
id|s
)paren
(brace
r_static
r_const
id|u8
id|dm_head_vals
(braket
)braket
op_assign
(brace
l_int|4
comma
l_int|8
comma
l_int|16
comma
l_int|32
comma
l_int|64
comma
l_int|128
comma
l_int|255
comma
l_int|0
)brace
suffix:semicolon
r_const
id|u8
op_star
id|headp
op_assign
id|dm_head_vals
suffix:semicolon
r_int
r_int
id|total
suffix:semicolon
multiline_comment|/*&n;&t; * The specs say: take geometry as obtained from Identify,&n;&t; * compute total capacity C*H*S from that, and truncate to&n;&t; * 1024*255*63. Now take S=63, H the first in the sequence&n;&t; * 4, 8, 16, 32, 64, 128, 255 such that 63*H*1024 &gt;= total.&n;&t; * [Please tell aeb@cwi.nl in case this computes a&n;&t; * geometry different from what OnTrack uses.]&n;&t; */
id|total
op_assign
id|DRIVER
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|capacity
c_func
(paren
id|drive
)paren
suffix:semicolon
op_star
id|s
op_assign
l_int|63
suffix:semicolon
r_if
c_cond
(paren
id|heads
)paren
(brace
op_star
id|h
op_assign
id|heads
suffix:semicolon
op_star
id|c
op_assign
id|total
op_div
(paren
l_int|63
op_star
id|heads
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_while
c_loop
(paren
l_int|63
op_star
id|headp
(braket
l_int|0
)braket
op_star
l_int|1024
OL
id|total
op_logical_and
id|headp
(braket
l_int|1
)braket
op_ne
l_int|0
)paren
id|headp
op_increment
suffix:semicolon
op_star
id|h
op_assign
id|headp
(braket
l_int|0
)braket
suffix:semicolon
op_star
id|c
op_assign
id|total
op_div
(paren
l_int|63
op_star
id|headp
(braket
l_int|0
)braket
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This routine is called from the partition-table code in pt/msdos.c.&n; * It has two tasks:&n; * (i) to handle Ontrack DiskManager by offsetting everything by 63 sectors,&n; *  or to handle EZdrive by remapping sector 0 to sector 1.&n; * (ii) to invent a translated geometry.&n; * Part (i) is suppressed if the user specifies the &quot;noremap&quot; option&n; * on the command line.&n; * Part (ii) is suppressed if the user specifies an explicit geometry.&n; *&n; * The ptheads parameter is either 0 or tells about the number of&n; * heads shown by the end of the first nonempty partition.&n; * If this is either 16, 32, 64, 128, 240 or 255 we&squot;ll believe it.&n; *&n; * The xparm parameter has the following meaning:&n; *&t; 0 = convert to CHS with fewer than 1024 cyls&n; *&t;     using the same method as Ontrack DiskManager.&n; *&t; 1 = same as &quot;0&quot;, plus offset everything by 63 sectors.&n; *&t;-1 = similar to &quot;0&quot;, plus redirect sector 0 to sector 1.&n; *&t; 2 = convert to a CHS geometry with &quot;ptheads&quot; heads.&n; *&n; * Returns 0 if the translation was not possible, if the device was not &n; * an IDE disk drive, or if a geometry was &quot;forced&quot; on the commandline.&n; * Returns 1 if the geometry translation was successful.&n; */
DECL|function|ide_xlate_1024
r_int
id|ide_xlate_1024
(paren
r_struct
id|block_device
op_star
id|bdev
comma
r_int
id|xparm
comma
r_int
id|ptheads
comma
r_const
r_char
op_star
id|msg
)paren
(brace
id|ide_drive_t
op_star
id|drive
op_assign
id|bdev-&gt;bd_disk-&gt;private_data
suffix:semicolon
r_const
r_char
op_star
id|msg1
op_assign
l_string|&quot;&quot;
suffix:semicolon
r_int
id|heads
op_assign
l_int|0
suffix:semicolon
r_int
id|c
comma
id|h
comma
id|s
suffix:semicolon
r_int
id|transl
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* try translation */
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* remap? */
r_if
c_cond
(paren
id|drive-&gt;remap_0_to_1
op_ne
l_int|2
)paren
(brace
r_if
c_cond
(paren
id|xparm
op_eq
l_int|1
)paren
(brace
multiline_comment|/* DM */
id|drive-&gt;sect0
op_assign
l_int|63
suffix:semicolon
id|msg1
op_assign
l_string|&quot; [remap +63]&quot;
suffix:semicolon
id|ret
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|xparm
op_eq
op_minus
l_int|1
)paren
(brace
multiline_comment|/* EZ-Drive */
r_if
c_cond
(paren
id|drive-&gt;remap_0_to_1
op_eq
l_int|0
)paren
(brace
id|drive-&gt;remap_0_to_1
op_assign
l_int|1
suffix:semicolon
id|msg1
op_assign
l_string|&quot; [remap 0-&gt;1]&quot;
suffix:semicolon
id|ret
op_assign
l_int|1
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* There used to be code here that assigned drive-&gt;id-&gt;CHS&n;&t;   to drive-&gt;CHS and that to drive-&gt;bios_CHS. However,&n;&t;   some disks have id-&gt;C/H/S = 4092/16/63 but are larger than 2.1 GB.&n;&t;   In such cases that code was wrong.  Moreover,&n;&t;   there seems to be no reason to do any of these things. */
multiline_comment|/* translate? */
r_if
c_cond
(paren
id|drive-&gt;forced_geom
)paren
id|transl
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* does ptheads look reasonable? */
r_if
c_cond
(paren
id|ptheads
op_eq
l_int|32
op_logical_or
id|ptheads
op_eq
l_int|64
op_logical_or
id|ptheads
op_eq
l_int|128
op_logical_or
id|ptheads
op_eq
l_int|240
op_logical_or
id|ptheads
op_eq
l_int|255
)paren
id|heads
op_assign
id|ptheads
suffix:semicolon
r_if
c_cond
(paren
id|xparm
op_eq
l_int|2
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|heads
op_logical_or
(paren
id|drive-&gt;bios_head
op_ge
id|heads
op_logical_and
id|drive-&gt;bios_sect
op_eq
l_int|63
)paren
)paren
id|transl
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|xparm
op_eq
op_minus
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|drive-&gt;bios_head
OG
l_int|16
)paren
id|transl
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* we already have a translation */
)brace
r_if
c_cond
(paren
id|transl
)paren
(brace
id|ontrack
c_func
(paren
id|drive
comma
id|heads
comma
op_amp
id|c
comma
op_amp
id|h
comma
op_amp
id|s
)paren
suffix:semicolon
id|drive-&gt;bios_cyl
op_assign
id|c
suffix:semicolon
id|drive-&gt;bios_head
op_assign
id|h
suffix:semicolon
id|drive-&gt;bios_sect
op_assign
id|s
suffix:semicolon
id|ret
op_assign
l_int|1
suffix:semicolon
)brace
id|set_capacity
c_func
(paren
id|drive-&gt;disk
comma
id|current_capacity
c_func
(paren
id|drive
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s%s [%d/%d/%d]&quot;
comma
id|msg
comma
id|msg1
comma
id|drive-&gt;bios_cyl
comma
id|drive-&gt;bios_head
comma
id|drive-&gt;bios_sect
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
eof
