macro_line|#ifndef _LINUX_MAJOR_H
DECL|macro|_LINUX_MAJOR_H
mdefine_line|#define _LINUX_MAJOR_H
multiline_comment|/*&n; * This file has definitions for major device numbers.&n; * For the device number assignments, see Documentation/devices.txt.&n; */
multiline_comment|/* limits */
multiline_comment|/*&n; * Important: Don&squot;t change this to 256.  Major number 255 is and must be&n; * reserved for future expansion into a larger dev_t space.&n; */
DECL|macro|MAX_CHRDEV
mdefine_line|#define MAX_CHRDEV&t;255
DECL|macro|MAX_BLKDEV
mdefine_line|#define MAX_BLKDEV&t;255
DECL|macro|UNNAMED_MAJOR
mdefine_line|#define UNNAMED_MAJOR&t;0
DECL|macro|MEM_MAJOR
mdefine_line|#define MEM_MAJOR&t;1
DECL|macro|RAMDISK_MAJOR
mdefine_line|#define RAMDISK_MAJOR&t;1
DECL|macro|FLOPPY_MAJOR
mdefine_line|#define FLOPPY_MAJOR&t;2
DECL|macro|PTY_MASTER_MAJOR
mdefine_line|#define PTY_MASTER_MAJOR 2
DECL|macro|IDE0_MAJOR
mdefine_line|#define IDE0_MAJOR&t;3
DECL|macro|PTY_SLAVE_MAJOR
mdefine_line|#define PTY_SLAVE_MAJOR 3
DECL|macro|HD_MAJOR
mdefine_line|#define HD_MAJOR&t;IDE0_MAJOR
DECL|macro|TTY_MAJOR
mdefine_line|#define TTY_MAJOR&t;4
DECL|macro|TTYAUX_MAJOR
mdefine_line|#define TTYAUX_MAJOR&t;5
DECL|macro|LP_MAJOR
mdefine_line|#define LP_MAJOR&t;6
DECL|macro|VCS_MAJOR
mdefine_line|#define VCS_MAJOR&t;7
DECL|macro|LOOP_MAJOR
mdefine_line|#define LOOP_MAJOR&t;7
DECL|macro|SCSI_DISK0_MAJOR
mdefine_line|#define SCSI_DISK0_MAJOR 8
DECL|macro|SCSI_TAPE_MAJOR
mdefine_line|#define SCSI_TAPE_MAJOR&t;9
DECL|macro|MD_MAJOR
mdefine_line|#define MD_MAJOR        9
DECL|macro|MISC_MAJOR
mdefine_line|#define MISC_MAJOR&t;10
DECL|macro|SCSI_CDROM_MAJOR
mdefine_line|#define SCSI_CDROM_MAJOR 11
DECL|macro|QIC02_TAPE_MAJOR
mdefine_line|#define QIC02_TAPE_MAJOR 12
DECL|macro|XT_DISK_MAJOR
mdefine_line|#define XT_DISK_MAJOR&t;13
DECL|macro|SOUND_MAJOR
mdefine_line|#define SOUND_MAJOR&t;14
DECL|macro|CDU31A_CDROM_MAJOR
mdefine_line|#define CDU31A_CDROM_MAJOR 15
DECL|macro|JOYSTICK_MAJOR
mdefine_line|#define JOYSTICK_MAJOR&t;15
DECL|macro|GOLDSTAR_CDROM_MAJOR
mdefine_line|#define GOLDSTAR_CDROM_MAJOR 16
DECL|macro|OPTICS_CDROM_MAJOR
mdefine_line|#define OPTICS_CDROM_MAJOR 17
DECL|macro|SANYO_CDROM_MAJOR
mdefine_line|#define SANYO_CDROM_MAJOR 18
DECL|macro|CYCLADES_MAJOR
mdefine_line|#define CYCLADES_MAJOR  19
DECL|macro|CYCLADESAUX_MAJOR
mdefine_line|#define CYCLADESAUX_MAJOR 20
DECL|macro|MITSUMI_X_CDROM_MAJOR
mdefine_line|#define MITSUMI_X_CDROM_MAJOR 20
DECL|macro|MFM_ACORN_MAJOR
mdefine_line|#define MFM_ACORN_MAJOR 21&t;/* ARM Linux /dev/mfm */
DECL|macro|SCSI_GENERIC_MAJOR
mdefine_line|#define SCSI_GENERIC_MAJOR 21
DECL|macro|Z8530_MAJOR
mdefine_line|#define Z8530_MAJOR 34
DECL|macro|DIGI_MAJOR
mdefine_line|#define DIGI_MAJOR 23
DECL|macro|IDE1_MAJOR
mdefine_line|#define IDE1_MAJOR&t;22
DECL|macro|DIGICU_MAJOR
mdefine_line|#define DIGICU_MAJOR 22
DECL|macro|MITSUMI_CDROM_MAJOR
mdefine_line|#define MITSUMI_CDROM_MAJOR 23
DECL|macro|CDU535_CDROM_MAJOR
mdefine_line|#define CDU535_CDROM_MAJOR 24
DECL|macro|STL_SERIALMAJOR
mdefine_line|#define STL_SERIALMAJOR 24
DECL|macro|MATSUSHITA_CDROM_MAJOR
mdefine_line|#define MATSUSHITA_CDROM_MAJOR 25
DECL|macro|STL_CALLOUTMAJOR
mdefine_line|#define STL_CALLOUTMAJOR 25
DECL|macro|MATSUSHITA_CDROM2_MAJOR
mdefine_line|#define MATSUSHITA_CDROM2_MAJOR 26
DECL|macro|QIC117_TAPE_MAJOR
mdefine_line|#define QIC117_TAPE_MAJOR 27
DECL|macro|MATSUSHITA_CDROM3_MAJOR
mdefine_line|#define MATSUSHITA_CDROM3_MAJOR 27
DECL|macro|MATSUSHITA_CDROM4_MAJOR
mdefine_line|#define MATSUSHITA_CDROM4_MAJOR 28
DECL|macro|STL_SIOMEMMAJOR
mdefine_line|#define STL_SIOMEMMAJOR 28
DECL|macro|ACSI_MAJOR
mdefine_line|#define ACSI_MAJOR&t;28
DECL|macro|AZTECH_CDROM_MAJOR
mdefine_line|#define AZTECH_CDROM_MAJOR 29
DECL|macro|GRAPHDEV_MAJOR
mdefine_line|#define GRAPHDEV_MAJOR&t;29&t;/* SparcLinux &amp; Linux/68k /dev/fb */
DECL|macro|SHMIQ_MAJOR
mdefine_line|#define SHMIQ_MAJOR&t;85&t;/* Linux/mips, SGI /dev/shmiq */
DECL|macro|CM206_CDROM_MAJOR
mdefine_line|#define CM206_CDROM_MAJOR 32
DECL|macro|IDE2_MAJOR
mdefine_line|#define IDE2_MAJOR&t;33
DECL|macro|IDE3_MAJOR
mdefine_line|#define IDE3_MAJOR&t;34
DECL|macro|XPRAM_MAJOR
mdefine_line|#define XPRAM_MAJOR     35      /* expanded storage on S/390 = &quot;slow ram&quot; */
multiline_comment|/* proposed by Peter                      */
DECL|macro|NETLINK_MAJOR
mdefine_line|#define NETLINK_MAJOR&t;36
DECL|macro|PS2ESDI_MAJOR
mdefine_line|#define PS2ESDI_MAJOR&t;36
DECL|macro|IDETAPE_MAJOR
mdefine_line|#define IDETAPE_MAJOR&t;37
DECL|macro|Z2RAM_MAJOR
mdefine_line|#define Z2RAM_MAJOR&t;37
DECL|macro|APBLOCK_MAJOR
mdefine_line|#define APBLOCK_MAJOR   38   /* AP1000 Block device */
DECL|macro|DDV_MAJOR
mdefine_line|#define DDV_MAJOR       39   /* AP1000 DDV block device */
DECL|macro|NBD_MAJOR
mdefine_line|#define NBD_MAJOR&t;43   /* Network block device&t;*/
DECL|macro|RISCOM8_NORMAL_MAJOR
mdefine_line|#define RISCOM8_NORMAL_MAJOR 48
DECL|macro|DAC960_MAJOR
mdefine_line|#define DAC960_MAJOR&t;48&t;/* 48..55 */
DECL|macro|RISCOM8_CALLOUT_MAJOR
mdefine_line|#define RISCOM8_CALLOUT_MAJOR 49
DECL|macro|MKISS_MAJOR
mdefine_line|#define MKISS_MAJOR&t;55
DECL|macro|DSP56K_MAJOR
mdefine_line|#define DSP56K_MAJOR    55   /* DSP56001 processor device */
DECL|macro|IDE4_MAJOR
mdefine_line|#define IDE4_MAJOR&t;56
DECL|macro|IDE5_MAJOR
mdefine_line|#define IDE5_MAJOR&t;57
DECL|macro|LVM_BLK_MAJOR
mdefine_line|#define LVM_BLK_MAJOR&t;58&t;/* Logical Volume Manager */
DECL|macro|SCSI_DISK1_MAJOR
mdefine_line|#define SCSI_DISK1_MAJOR&t;65
DECL|macro|SCSI_DISK2_MAJOR
mdefine_line|#define SCSI_DISK2_MAJOR&t;66
DECL|macro|SCSI_DISK3_MAJOR
mdefine_line|#define SCSI_DISK3_MAJOR&t;67
DECL|macro|SCSI_DISK4_MAJOR
mdefine_line|#define SCSI_DISK4_MAJOR&t;68
DECL|macro|SCSI_DISK5_MAJOR
mdefine_line|#define SCSI_DISK5_MAJOR&t;69
DECL|macro|SCSI_DISK6_MAJOR
mdefine_line|#define SCSI_DISK6_MAJOR&t;70
DECL|macro|SCSI_DISK7_MAJOR
mdefine_line|#define SCSI_DISK7_MAJOR&t;71
DECL|macro|COMPAQ_SMART2_MAJOR
mdefine_line|#define COMPAQ_SMART2_MAJOR&t;72
DECL|macro|COMPAQ_SMART2_MAJOR1
mdefine_line|#define COMPAQ_SMART2_MAJOR1&t;73
DECL|macro|COMPAQ_SMART2_MAJOR2
mdefine_line|#define COMPAQ_SMART2_MAJOR2&t;74
DECL|macro|COMPAQ_SMART2_MAJOR3
mdefine_line|#define COMPAQ_SMART2_MAJOR3&t;75
DECL|macro|COMPAQ_SMART2_MAJOR4
mdefine_line|#define COMPAQ_SMART2_MAJOR4&t;76
DECL|macro|COMPAQ_SMART2_MAJOR5
mdefine_line|#define COMPAQ_SMART2_MAJOR5&t;77
DECL|macro|COMPAQ_SMART2_MAJOR6
mdefine_line|#define COMPAQ_SMART2_MAJOR6&t;78
DECL|macro|COMPAQ_SMART2_MAJOR7
mdefine_line|#define COMPAQ_SMART2_MAJOR7&t;79
DECL|macro|SPECIALIX_NORMAL_MAJOR
mdefine_line|#define SPECIALIX_NORMAL_MAJOR 75
DECL|macro|SPECIALIX_CALLOUT_MAJOR
mdefine_line|#define SPECIALIX_CALLOUT_MAJOR 76
DECL|macro|COMPAQ_CISS_MAJOR
mdefine_line|#define COMPAQ_CISS_MAJOR &t;104
DECL|macro|COMPAQ_CISS_MAJOR1
mdefine_line|#define COMPAQ_CISS_MAJOR1&t;105
DECL|macro|COMPAQ_CISS_MAJOR2
mdefine_line|#define COMPAQ_CISS_MAJOR2      106
DECL|macro|COMPAQ_CISS_MAJOR3
mdefine_line|#define COMPAQ_CISS_MAJOR3      107
DECL|macro|COMPAQ_CISS_MAJOR4
mdefine_line|#define COMPAQ_CISS_MAJOR4      108
DECL|macro|COMPAQ_CISS_MAJOR5
mdefine_line|#define COMPAQ_CISS_MAJOR5      109
DECL|macro|COMPAQ_CISS_MAJOR6
mdefine_line|#define COMPAQ_CISS_MAJOR6      110
DECL|macro|COMPAQ_CISS_MAJOR7
mdefine_line|#define COMPAQ_CISS_MAJOR7      111
DECL|macro|ATARAID_MAJOR
mdefine_line|#define ATARAID_MAJOR&t;&t;114
DECL|macro|DASD_MAJOR
mdefine_line|#define DASD_MAJOR      94&t;/* Official assignations from Peter */
DECL|macro|MDISK_MAJOR
mdefine_line|#define MDISK_MAJOR     95&t;/* Official assignations from Peter */
DECL|macro|I2O_MAJOR
mdefine_line|#define I2O_MAJOR&t;&t;80&t;/* 80-&gt;87 */
DECL|macro|IDE6_MAJOR
mdefine_line|#define IDE6_MAJOR&t;88
DECL|macro|IDE7_MAJOR
mdefine_line|#define IDE7_MAJOR&t;89
DECL|macro|IDE8_MAJOR
mdefine_line|#define IDE8_MAJOR&t;90
DECL|macro|IDE9_MAJOR
mdefine_line|#define IDE9_MAJOR&t;91
DECL|macro|UBD_MAJOR
mdefine_line|#define UBD_MAJOR&t;98
DECL|macro|AURORA_MAJOR
mdefine_line|#define AURORA_MAJOR 79
DECL|macro|JSFD_MAJOR
mdefine_line|#define JSFD_MAJOR&t;99
DECL|macro|PHONE_MAJOR
mdefine_line|#define PHONE_MAJOR&t;100
DECL|macro|LVM_CHAR_MAJOR
mdefine_line|#define LVM_CHAR_MAJOR&t;109&t;/* Logical Volume Manager */
DECL|macro|RTF_MAJOR
mdefine_line|#define RTF_MAJOR&t;150
DECL|macro|RAW_MAJOR
mdefine_line|#define RAW_MAJOR&t;162
DECL|macro|USB_ACM_MAJOR
mdefine_line|#define USB_ACM_MAJOR&t;&t;166
DECL|macro|USB_ACM_AUX_MAJOR
mdefine_line|#define USB_ACM_AUX_MAJOR&t;167
DECL|macro|USB_CHAR_MAJOR
mdefine_line|#define USB_CHAR_MAJOR&t;&t;180
DECL|macro|UNIX98_PTY_MASTER_MAJOR
mdefine_line|#define UNIX98_PTY_MASTER_MAJOR&t;128
DECL|macro|UNIX98_PTY_MAJOR_COUNT
mdefine_line|#define UNIX98_PTY_MAJOR_COUNT&t;8
DECL|macro|UNIX98_PTY_SLAVE_MAJOR
mdefine_line|#define UNIX98_PTY_SLAVE_MAJOR&t;(UNIX98_PTY_MASTER_MAJOR+UNIX98_PTY_MAJOR_COUNT)
DECL|macro|VXVM_MAJOR
mdefine_line|#define VXVM_MAJOR&t;&t;199&t;/* VERITAS volume i/o driver    */
DECL|macro|VXSPEC_MAJOR
mdefine_line|#define VXSPEC_MAJOR&t;&t;200&t;/* VERITAS volume config driver */
DECL|macro|VXDMP_MAJOR
mdefine_line|#define VXDMP_MAJOR&t;&t;201&t;/* VERITAS volume multipath driver */
DECL|macro|MSR_MAJOR
mdefine_line|#define MSR_MAJOR&t;&t;202
DECL|macro|CPUID_MAJOR
mdefine_line|#define CPUID_MAJOR&t;&t;203
DECL|macro|OSST_MAJOR
mdefine_line|#define OSST_MAJOR&t;206&t;/* OnStream-SCx0 SCSI tape */
DECL|macro|IBM_TTY3270_MAJOR
mdefine_line|#define IBM_TTY3270_MAJOR       227&t;/* Official allocations now */
DECL|macro|IBM_FS3270_MAJOR
mdefine_line|#define IBM_FS3270_MAJOR        228
multiline_comment|/*&n; * Tests for SCSI devices.&n; */
DECL|macro|SCSI_DISK_MAJOR
mdefine_line|#define SCSI_DISK_MAJOR(M) ((M) == SCSI_DISK0_MAJOR || &bslash;&n;  ((M) &gt;= SCSI_DISK1_MAJOR &amp;&amp; (M) &lt;= SCSI_DISK7_MAJOR))
DECL|macro|SCSI_BLK_MAJOR
mdefine_line|#define SCSI_BLK_MAJOR(M) &bslash;&n;  (SCSI_DISK_MAJOR(M)&t;&bslash;&n;   || (M) == SCSI_CDROM_MAJOR)
DECL|function|scsi_blk_major
r_static
id|__inline__
r_int
id|scsi_blk_major
c_func
(paren
r_int
id|m
)paren
(brace
r_return
id|SCSI_BLK_MAJOR
c_func
(paren
id|m
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Tests for IDE devices&n; */
DECL|macro|IDE_DISK_MAJOR
mdefine_line|#define IDE_DISK_MAJOR(M)&t;((M) == IDE0_MAJOR || (M) == IDE1_MAJOR || &bslash;&n;&t;&t;&t;&t;(M) == IDE2_MAJOR || (M) == IDE3_MAJOR || &bslash;&n;&t;&t;&t;&t;(M) == IDE4_MAJOR || (M) == IDE5_MAJOR || &bslash;&n;&t;&t;&t;&t;(M) == IDE6_MAJOR || (M) == IDE7_MAJOR || &bslash;&n;&t;&t;&t;&t;(M) == IDE8_MAJOR || (M) == IDE9_MAJOR)
DECL|function|ide_blk_major
r_static
id|__inline__
r_int
id|ide_blk_major
c_func
(paren
r_int
id|m
)paren
(brace
r_return
id|IDE_DISK_MAJOR
c_func
(paren
id|m
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
