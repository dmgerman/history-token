macro_line|#ifndef _LINUX_MAJOR_H
DECL|macro|_LINUX_MAJOR_H
mdefine_line|#define _LINUX_MAJOR_H
multiline_comment|/*&n; * This file has definitions for major device numbers.&n; * For the device number assignments, see Documentation/devices.txt.&n; */
DECL|macro|UNNAMED_MAJOR
mdefine_line|#define UNNAMED_MAJOR&t;&t;0
DECL|macro|MEM_MAJOR
mdefine_line|#define MEM_MAJOR&t;&t;1
DECL|macro|RAMDISK_MAJOR
mdefine_line|#define RAMDISK_MAJOR&t;&t;1
DECL|macro|FLOPPY_MAJOR
mdefine_line|#define FLOPPY_MAJOR&t;&t;2
DECL|macro|PTY_MASTER_MAJOR
mdefine_line|#define PTY_MASTER_MAJOR&t;2
DECL|macro|IDE0_MAJOR
mdefine_line|#define IDE0_MAJOR&t;&t;3
DECL|macro|HD_MAJOR
mdefine_line|#define HD_MAJOR&t;&t;IDE0_MAJOR
DECL|macro|PTY_SLAVE_MAJOR
mdefine_line|#define PTY_SLAVE_MAJOR&t;&t;3
DECL|macro|TTY_MAJOR
mdefine_line|#define TTY_MAJOR&t;&t;4
DECL|macro|TTYAUX_MAJOR
mdefine_line|#define TTYAUX_MAJOR&t;&t;5
DECL|macro|LP_MAJOR
mdefine_line|#define LP_MAJOR&t;&t;6
DECL|macro|VCS_MAJOR
mdefine_line|#define VCS_MAJOR&t;&t;7
DECL|macro|LOOP_MAJOR
mdefine_line|#define LOOP_MAJOR&t;&t;7
DECL|macro|SCSI_DISK0_MAJOR
mdefine_line|#define SCSI_DISK0_MAJOR&t;8
DECL|macro|SCSI_TAPE_MAJOR
mdefine_line|#define SCSI_TAPE_MAJOR&t;&t;9
DECL|macro|MD_MAJOR
mdefine_line|#define MD_MAJOR&t;&t;9
DECL|macro|MISC_MAJOR
mdefine_line|#define MISC_MAJOR&t;&t;10
DECL|macro|SCSI_CDROM_MAJOR
mdefine_line|#define SCSI_CDROM_MAJOR&t;11
DECL|macro|MUX_MAJOR
mdefine_line|#define MUX_MAJOR&t;&t;11&t;/* PA-RISC only */
DECL|macro|QIC02_TAPE_MAJOR
mdefine_line|#define QIC02_TAPE_MAJOR&t;12
DECL|macro|XT_DISK_MAJOR
mdefine_line|#define XT_DISK_MAJOR&t;&t;13
DECL|macro|INPUT_MAJOR
mdefine_line|#define INPUT_MAJOR&t;&t;13
DECL|macro|SOUND_MAJOR
mdefine_line|#define SOUND_MAJOR&t;&t;14
DECL|macro|CDU31A_CDROM_MAJOR
mdefine_line|#define CDU31A_CDROM_MAJOR&t;15
DECL|macro|JOYSTICK_MAJOR
mdefine_line|#define JOYSTICK_MAJOR&t;&t;15
DECL|macro|GOLDSTAR_CDROM_MAJOR
mdefine_line|#define GOLDSTAR_CDROM_MAJOR&t;16
DECL|macro|OPTICS_CDROM_MAJOR
mdefine_line|#define OPTICS_CDROM_MAJOR&t;17
DECL|macro|SANYO_CDROM_MAJOR
mdefine_line|#define SANYO_CDROM_MAJOR&t;18
DECL|macro|CYCLADES_MAJOR
mdefine_line|#define CYCLADES_MAJOR&t;&t;19
DECL|macro|CYCLADESAUX_MAJOR
mdefine_line|#define CYCLADESAUX_MAJOR&t;20
DECL|macro|MITSUMI_X_CDROM_MAJOR
mdefine_line|#define MITSUMI_X_CDROM_MAJOR&t;20
DECL|macro|MFM_ACORN_MAJOR
mdefine_line|#define MFM_ACORN_MAJOR&t;&t;21&t;/* ARM Linux /dev/mfm */
DECL|macro|SCSI_GENERIC_MAJOR
mdefine_line|#define SCSI_GENERIC_MAJOR&t;21
DECL|macro|IDE1_MAJOR
mdefine_line|#define IDE1_MAJOR&t;&t;22
DECL|macro|DIGICU_MAJOR
mdefine_line|#define DIGICU_MAJOR&t;&t;22
DECL|macro|DIGI_MAJOR
mdefine_line|#define DIGI_MAJOR&t;&t;23
DECL|macro|MITSUMI_CDROM_MAJOR
mdefine_line|#define MITSUMI_CDROM_MAJOR&t;23
DECL|macro|CDU535_CDROM_MAJOR
mdefine_line|#define CDU535_CDROM_MAJOR&t;24
DECL|macro|STL_SERIALMAJOR
mdefine_line|#define STL_SERIALMAJOR&t;&t;24
DECL|macro|MATSUSHITA_CDROM_MAJOR
mdefine_line|#define MATSUSHITA_CDROM_MAJOR&t;25
DECL|macro|STL_CALLOUTMAJOR
mdefine_line|#define STL_CALLOUTMAJOR&t;25
DECL|macro|MATSUSHITA_CDROM2_MAJOR
mdefine_line|#define MATSUSHITA_CDROM2_MAJOR&t;26
DECL|macro|QIC117_TAPE_MAJOR
mdefine_line|#define QIC117_TAPE_MAJOR&t;27
DECL|macro|MATSUSHITA_CDROM3_MAJOR
mdefine_line|#define MATSUSHITA_CDROM3_MAJOR&t;27
DECL|macro|MATSUSHITA_CDROM4_MAJOR
mdefine_line|#define MATSUSHITA_CDROM4_MAJOR&t;28
DECL|macro|STL_SIOMEMMAJOR
mdefine_line|#define STL_SIOMEMMAJOR&t;&t;28
DECL|macro|ACSI_MAJOR
mdefine_line|#define ACSI_MAJOR&t;&t;28
DECL|macro|AZTECH_CDROM_MAJOR
mdefine_line|#define AZTECH_CDROM_MAJOR&t;29
DECL|macro|GRAPHDEV_MAJOR
mdefine_line|#define GRAPHDEV_MAJOR&t;&t;29   /* SparcLinux &amp; Linux/68k /dev/fb */
DECL|macro|CM206_CDROM_MAJOR
mdefine_line|#define CM206_CDROM_MAJOR&t;32
DECL|macro|IDE2_MAJOR
mdefine_line|#define IDE2_MAJOR&t;&t;33
DECL|macro|IDE3_MAJOR
mdefine_line|#define IDE3_MAJOR&t;&t;34
DECL|macro|Z8530_MAJOR
mdefine_line|#define Z8530_MAJOR&t;&t;34
DECL|macro|XPRAM_MAJOR
mdefine_line|#define XPRAM_MAJOR&t;&t;35   /* Expanded storage on S/390: &quot;slow ram&quot;*/
DECL|macro|NETLINK_MAJOR
mdefine_line|#define NETLINK_MAJOR&t;&t;36
DECL|macro|PS2ESDI_MAJOR
mdefine_line|#define PS2ESDI_MAJOR&t;&t;36
DECL|macro|IDETAPE_MAJOR
mdefine_line|#define IDETAPE_MAJOR&t;&t;37
DECL|macro|Z2RAM_MAJOR
mdefine_line|#define Z2RAM_MAJOR&t;&t;37
DECL|macro|APBLOCK_MAJOR
mdefine_line|#define APBLOCK_MAJOR&t;&t;38   /* AP1000 Block device */
DECL|macro|DDV_MAJOR
mdefine_line|#define DDV_MAJOR&t;&t;39   /* AP1000 DDV block device */
DECL|macro|NBD_MAJOR
mdefine_line|#define NBD_MAJOR&t;&t;43   /* Network block device&t;*/
DECL|macro|RISCOM8_NORMAL_MAJOR
mdefine_line|#define RISCOM8_NORMAL_MAJOR&t;48
DECL|macro|DAC960_MAJOR
mdefine_line|#define DAC960_MAJOR&t;&t;48   /* 48..55 */
DECL|macro|RISCOM8_CALLOUT_MAJOR
mdefine_line|#define RISCOM8_CALLOUT_MAJOR&t;49
DECL|macro|MKISS_MAJOR
mdefine_line|#define MKISS_MAJOR&t;&t;55
DECL|macro|DSP56K_MAJOR
mdefine_line|#define DSP56K_MAJOR&t;&t;55   /* DSP56001 processor device */
DECL|macro|IDE4_MAJOR
mdefine_line|#define IDE4_MAJOR&t;&t;56
DECL|macro|IDE5_MAJOR
mdefine_line|#define IDE5_MAJOR&t;&t;57
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
mdefine_line|#define SPECIALIX_NORMAL_MAJOR&t;75
DECL|macro|SPECIALIX_CALLOUT_MAJOR
mdefine_line|#define SPECIALIX_CALLOUT_MAJOR&t;76
DECL|macro|AURORA_MAJOR
mdefine_line|#define AURORA_MAJOR&t;&t;79
DECL|macro|I2O_MAJOR
mdefine_line|#define I2O_MAJOR&t;&t;80&t;/* 80-&gt;87 */
DECL|macro|SHMIQ_MAJOR
mdefine_line|#define SHMIQ_MAJOR&t;&t;85   /* Linux/mips, SGI /dev/shmiq */
DECL|macro|IDE6_MAJOR
mdefine_line|#define IDE6_MAJOR&t;&t;88
DECL|macro|IDE7_MAJOR
mdefine_line|#define IDE7_MAJOR&t;&t;89
DECL|macro|IDE8_MAJOR
mdefine_line|#define IDE8_MAJOR&t;&t;90
DECL|macro|IDE9_MAJOR
mdefine_line|#define IDE9_MAJOR&t;&t;91
DECL|macro|DASD_MAJOR
mdefine_line|#define DASD_MAJOR&t;&t;94
DECL|macro|MDISK_MAJOR
mdefine_line|#define MDISK_MAJOR&t;&t;95
DECL|macro|UBD_MAJOR
mdefine_line|#define UBD_MAJOR&t;&t;98
DECL|macro|JSFD_MAJOR
mdefine_line|#define JSFD_MAJOR&t;&t;99
DECL|macro|PHONE_MAJOR
mdefine_line|#define PHONE_MAJOR&t;&t;100
DECL|macro|COMPAQ_CISS_MAJOR
mdefine_line|#define COMPAQ_CISS_MAJOR&t;104
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
DECL|macro|SCSI_DISK8_MAJOR
mdefine_line|#define SCSI_DISK8_MAJOR&t;128
DECL|macro|SCSI_DISK9_MAJOR
mdefine_line|#define SCSI_DISK9_MAJOR&t;129
DECL|macro|SCSI_DISK10_MAJOR
mdefine_line|#define SCSI_DISK10_MAJOR&t;130
DECL|macro|SCSI_DISK11_MAJOR
mdefine_line|#define SCSI_DISK11_MAJOR&t;131
DECL|macro|SCSI_DISK12_MAJOR
mdefine_line|#define SCSI_DISK12_MAJOR&t;132
DECL|macro|SCSI_DISK13_MAJOR
mdefine_line|#define SCSI_DISK13_MAJOR&t;133
DECL|macro|SCSI_DISK14_MAJOR
mdefine_line|#define SCSI_DISK14_MAJOR&t;134
DECL|macro|SCSI_DISK15_MAJOR
mdefine_line|#define SCSI_DISK15_MAJOR&t;135
DECL|macro|UNIX98_PTY_MASTER_MAJOR
mdefine_line|#define UNIX98_PTY_MASTER_MAJOR&t;128
DECL|macro|UNIX98_PTY_MAJOR_COUNT
mdefine_line|#define UNIX98_PTY_MAJOR_COUNT&t;8
DECL|macro|UNIX98_PTY_SLAVE_MAJOR
mdefine_line|#define UNIX98_PTY_SLAVE_MAJOR&t;(UNIX98_PTY_MASTER_MAJOR+UNIX98_PTY_MAJOR_COUNT)
DECL|macro|RTF_MAJOR
mdefine_line|#define RTF_MAJOR&t;&t;150
DECL|macro|RAW_MAJOR
mdefine_line|#define RAW_MAJOR&t;&t;162
DECL|macro|USB_ACM_MAJOR
mdefine_line|#define USB_ACM_MAJOR&t;&t;166
DECL|macro|USB_ACM_AUX_MAJOR
mdefine_line|#define USB_ACM_AUX_MAJOR&t;167
DECL|macro|USB_CHAR_MAJOR
mdefine_line|#define USB_CHAR_MAJOR&t;&t;180
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
mdefine_line|#define OSST_MAJOR&t;&t;206&t;/* OnStream-SCx0 SCSI tape */
DECL|macro|IBM_TTY3270_MAJOR
mdefine_line|#define IBM_TTY3270_MAJOR&t;227
DECL|macro|IBM_FS3270_MAJOR
mdefine_line|#define IBM_FS3270_MAJOR&t;228
macro_line|#endif
eof
