macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;scsi/scsi_device.h&gt;
macro_line|#include &lt;scsi/scsi_devinfo.h&gt;
macro_line|#include &quot;scsi_priv.h&quot;
multiline_comment|/*&n; * scsi_dev_info_list: structure to hold black/white listed devices.&n; */
DECL|struct|scsi_dev_info_list
r_struct
id|scsi_dev_info_list
(brace
DECL|member|dev_info_list
r_struct
id|list_head
id|dev_info_list
suffix:semicolon
DECL|member|vendor
r_char
id|vendor
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|model
r_char
id|model
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|member|compatible
r_int
id|compatible
suffix:semicolon
multiline_comment|/* for use with scsi_static_device_list entries */
)brace
suffix:semicolon
DECL|variable|spaces
r_static
r_const
r_char
id|spaces
(braket
)braket
op_assign
l_string|&quot;                &quot;
suffix:semicolon
multiline_comment|/* 16 of them */
DECL|variable|scsi_default_dev_flags
r_static
r_int
id|scsi_default_dev_flags
suffix:semicolon
r_static
id|LIST_HEAD
c_func
(paren
id|scsi_dev_info_list
)paren
suffix:semicolon
DECL|variable|scsi_dev_flags
r_static
id|__initdata
r_char
id|scsi_dev_flags
(braket
l_int|256
)braket
suffix:semicolon
multiline_comment|/*&n; * scsi_static_device_list: deprecated list of devices that require&n; * settings that differ from the default, includes black-listed (broken)&n; * devices. The entries here are added to the tail of scsi_dev_info_list&n; * via scsi_dev_info_list_init.&n; *&n; * Do not add to this list, use the command line or proc interface to add&n; * to the scsi_dev_info_list. This table will eventually go away.&n; */
r_static
r_struct
(brace
DECL|member|vendor
r_char
op_star
id|vendor
suffix:semicolon
DECL|member|model
r_char
op_star
id|model
suffix:semicolon
DECL|member|revision
r_char
op_star
id|revision
suffix:semicolon
multiline_comment|/* revision known to be bad, unused */
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|variable|__initdata
)brace
id|scsi_static_device_list
(braket
)braket
id|__initdata
op_assign
(brace
multiline_comment|/*&n;&t; * The following devices are known not to tolerate a lun != 0 scan&n;&t; * for one reason or another. Some will respond to all luns,&n;&t; * others will lock up.&n;&t; */
(brace
l_string|&quot;Aashima&quot;
comma
l_string|&quot;IMAGERY 2400SP&quot;
comma
l_string|&quot;1.03&quot;
comma
id|BLIST_NOLUN
)brace
comma
multiline_comment|/* locks up */
(brace
l_string|&quot;CHINON&quot;
comma
l_string|&quot;CD-ROM CDS-431&quot;
comma
l_string|&quot;H42&quot;
comma
id|BLIST_NOLUN
)brace
comma
multiline_comment|/* locks up */
(brace
l_string|&quot;CHINON&quot;
comma
l_string|&quot;CD-ROM CDS-535&quot;
comma
l_string|&quot;Q14&quot;
comma
id|BLIST_NOLUN
)brace
comma
multiline_comment|/* locks up */
(brace
l_string|&quot;DENON&quot;
comma
l_string|&quot;DRD-25X&quot;
comma
l_string|&quot;V&quot;
comma
id|BLIST_NOLUN
)brace
comma
multiline_comment|/* locks up */
(brace
l_string|&quot;HITACHI&quot;
comma
l_string|&quot;DK312C&quot;
comma
l_string|&quot;CM81&quot;
comma
id|BLIST_NOLUN
)brace
comma
multiline_comment|/* responds to all lun */
(brace
l_string|&quot;HITACHI&quot;
comma
l_string|&quot;DK314C&quot;
comma
l_string|&quot;CR21&quot;
comma
id|BLIST_NOLUN
)brace
comma
multiline_comment|/* responds to all lun */
(brace
l_string|&quot;IMS&quot;
comma
l_string|&quot;CDD521/10&quot;
comma
l_string|&quot;2.06&quot;
comma
id|BLIST_NOLUN
)brace
comma
multiline_comment|/* locks up */
(brace
l_string|&quot;MAXTOR&quot;
comma
l_string|&quot;XT-3280&quot;
comma
l_string|&quot;PR02&quot;
comma
id|BLIST_NOLUN
)brace
comma
multiline_comment|/* locks up */
(brace
l_string|&quot;MAXTOR&quot;
comma
l_string|&quot;XT-4380S&quot;
comma
l_string|&quot;B3C&quot;
comma
id|BLIST_NOLUN
)brace
comma
multiline_comment|/* locks up */
(brace
l_string|&quot;MAXTOR&quot;
comma
l_string|&quot;MXT-1240S&quot;
comma
l_string|&quot;I1.2&quot;
comma
id|BLIST_NOLUN
)brace
comma
multiline_comment|/* locks up */
(brace
l_string|&quot;MAXTOR&quot;
comma
l_string|&quot;XT-4170S&quot;
comma
l_string|&quot;B5A&quot;
comma
id|BLIST_NOLUN
)brace
comma
multiline_comment|/* locks up */
(brace
l_string|&quot;MAXTOR&quot;
comma
l_string|&quot;XT-8760S&quot;
comma
l_string|&quot;B7B&quot;
comma
id|BLIST_NOLUN
)brace
comma
multiline_comment|/* locks up */
(brace
l_string|&quot;MEDIAVIS&quot;
comma
l_string|&quot;RENO CD-ROMX2A&quot;
comma
l_string|&quot;2.03&quot;
comma
id|BLIST_NOLUN
)brace
comma
multiline_comment|/* responds to all lun */
(brace
l_string|&quot;NEC&quot;
comma
l_string|&quot;CD-ROM DRIVE:841&quot;
comma
l_string|&quot;1.0&quot;
comma
id|BLIST_NOLUN
)brace
comma
multiline_comment|/* locks up */
(brace
l_string|&quot;PHILIPS&quot;
comma
l_string|&quot;PCA80SC&quot;
comma
l_string|&quot;V4-2&quot;
comma
id|BLIST_NOLUN
)brace
comma
multiline_comment|/* responds to all lun */
(brace
l_string|&quot;RODIME&quot;
comma
l_string|&quot;RO3000S&quot;
comma
l_string|&quot;2.33&quot;
comma
id|BLIST_NOLUN
)brace
comma
multiline_comment|/* locks up */
(brace
l_string|&quot;SUN&quot;
comma
l_string|&quot;SENA&quot;
comma
l_int|NULL
comma
id|BLIST_NOLUN
)brace
comma
multiline_comment|/* responds to all luns */
multiline_comment|/*&n;&t; * The following causes a failed REQUEST SENSE on lun 1 for&n;&t; * aha152x controller, which causes SCSI code to reset bus.&n;&t; */
(brace
l_string|&quot;SANYO&quot;
comma
l_string|&quot;CRD-250S&quot;
comma
l_string|&quot;1.20&quot;
comma
id|BLIST_NOLUN
)brace
comma
multiline_comment|/*&n;&t; * The following causes a failed REQUEST SENSE on lun 1 for&n;&t; * aha152x controller, which causes SCSI code to reset bus.&n;&t; */
(brace
l_string|&quot;SEAGATE&quot;
comma
l_string|&quot;ST157N&quot;
comma
l_string|&quot;&bslash;004|j&quot;
comma
id|BLIST_NOLUN
)brace
comma
(brace
l_string|&quot;SEAGATE&quot;
comma
l_string|&quot;ST296&quot;
comma
l_string|&quot;921&quot;
comma
id|BLIST_NOLUN
)brace
comma
multiline_comment|/* responds to all lun */
(brace
l_string|&quot;SEAGATE&quot;
comma
l_string|&quot;ST1581&quot;
comma
l_string|&quot;6538&quot;
comma
id|BLIST_NOLUN
)brace
comma
multiline_comment|/* responds to all lun */
(brace
l_string|&quot;SONY&quot;
comma
l_string|&quot;CD-ROM CDU-541&quot;
comma
l_string|&quot;4.3d&quot;
comma
id|BLIST_NOLUN
)brace
comma
(brace
l_string|&quot;SONY&quot;
comma
l_string|&quot;CD-ROM CDU-55S&quot;
comma
l_string|&quot;1.0i&quot;
comma
id|BLIST_NOLUN
)brace
comma
(brace
l_string|&quot;SONY&quot;
comma
l_string|&quot;CD-ROM CDU-561&quot;
comma
l_string|&quot;1.7x&quot;
comma
id|BLIST_NOLUN
)brace
comma
(brace
l_string|&quot;SONY&quot;
comma
l_string|&quot;CD-ROM CDU-8012&quot;
comma
l_int|NULL
comma
id|BLIST_NOLUN
)brace
comma
(brace
l_string|&quot;TANDBERG&quot;
comma
l_string|&quot;TDC 3600&quot;
comma
l_string|&quot;U07&quot;
comma
id|BLIST_NOLUN
)brace
comma
multiline_comment|/* locks up */
(brace
l_string|&quot;TEAC&quot;
comma
l_string|&quot;CD-R55S&quot;
comma
l_string|&quot;1.0H&quot;
comma
id|BLIST_NOLUN
)brace
comma
multiline_comment|/* locks up */
multiline_comment|/*&n;&t; * The following causes a failed REQUEST SENSE on lun 1 for&n;&t; * seagate controller, which causes SCSI code to reset bus.&n;&t; */
(brace
l_string|&quot;TEAC&quot;
comma
l_string|&quot;CD-ROM&quot;
comma
l_string|&quot;1.06&quot;
comma
id|BLIST_NOLUN
)brace
comma
(brace
l_string|&quot;TEAC&quot;
comma
l_string|&quot;MT-2ST/45S2-27&quot;
comma
l_string|&quot;RV M&quot;
comma
id|BLIST_NOLUN
)brace
comma
multiline_comment|/* responds to all lun */
multiline_comment|/*&n;&t; * The following causes a failed REQUEST SENSE on lun 1 for&n;&t; * seagate controller, which causes SCSI code to reset bus.&n;&t; */
(brace
l_string|&quot;HP&quot;
comma
l_string|&quot;C1750A&quot;
comma
l_string|&quot;3226&quot;
comma
id|BLIST_NOLUN
)brace
comma
multiline_comment|/* scanjet iic */
(brace
l_string|&quot;HP&quot;
comma
l_string|&quot;C1790A&quot;
comma
l_string|&quot;&quot;
comma
id|BLIST_NOLUN
)brace
comma
multiline_comment|/* scanjet iip */
(brace
l_string|&quot;HP&quot;
comma
l_string|&quot;C2500A&quot;
comma
l_string|&quot;&quot;
comma
id|BLIST_NOLUN
)brace
comma
multiline_comment|/* scanjet iicx */
(brace
l_string|&quot;MEDIAVIS&quot;
comma
l_string|&quot;CDR-H93MV&quot;
comma
l_string|&quot;1.31&quot;
comma
id|BLIST_NOLUN
)brace
comma
multiline_comment|/* locks up */
(brace
l_string|&quot;MICROTEK&quot;
comma
l_string|&quot;ScanMaker II&quot;
comma
l_string|&quot;5.61&quot;
comma
id|BLIST_NOLUN
)brace
comma
multiline_comment|/* responds to all lun */
(brace
l_string|&quot;MITSUMI&quot;
comma
l_string|&quot;CD-R CR-2201CS&quot;
comma
l_string|&quot;6119&quot;
comma
id|BLIST_NOLUN
)brace
comma
multiline_comment|/* locks up */
(brace
l_string|&quot;NEC&quot;
comma
l_string|&quot;D3856&quot;
comma
l_string|&quot;0009&quot;
comma
id|BLIST_NOLUN
)brace
comma
(brace
l_string|&quot;QUANTUM&quot;
comma
l_string|&quot;LPS525S&quot;
comma
l_string|&quot;3110&quot;
comma
id|BLIST_NOLUN
)brace
comma
multiline_comment|/* locks up */
(brace
l_string|&quot;QUANTUM&quot;
comma
l_string|&quot;PD1225S&quot;
comma
l_string|&quot;3110&quot;
comma
id|BLIST_NOLUN
)brace
comma
multiline_comment|/* locks up */
(brace
l_string|&quot;QUANTUM&quot;
comma
l_string|&quot;FIREBALL ST4.3S&quot;
comma
l_string|&quot;0F0C&quot;
comma
id|BLIST_NOLUN
)brace
comma
multiline_comment|/* locks up */
(brace
l_string|&quot;RELISYS&quot;
comma
l_string|&quot;Scorpio&quot;
comma
l_int|NULL
comma
id|BLIST_NOLUN
)brace
comma
multiline_comment|/* responds to all lun */
(brace
l_string|&quot;SANKYO&quot;
comma
l_string|&quot;CP525&quot;
comma
l_string|&quot;6.64&quot;
comma
id|BLIST_NOLUN
)brace
comma
multiline_comment|/* causes failed REQ SENSE, extra reset */
(brace
l_string|&quot;TEXEL&quot;
comma
l_string|&quot;CD-ROM&quot;
comma
l_string|&quot;1.06&quot;
comma
id|BLIST_NOLUN
)brace
comma
(brace
l_string|&quot;YAMAHA&quot;
comma
l_string|&quot;CDR100&quot;
comma
l_string|&quot;1.00&quot;
comma
id|BLIST_NOLUN
)brace
comma
multiline_comment|/* locks up */
(brace
l_string|&quot;YAMAHA&quot;
comma
l_string|&quot;CDR102&quot;
comma
l_string|&quot;1.00&quot;
comma
id|BLIST_NOLUN
)brace
comma
multiline_comment|/* locks up */
(brace
l_string|&quot;YAMAHA&quot;
comma
l_string|&quot;CRW8424S&quot;
comma
l_string|&quot;1.0&quot;
comma
id|BLIST_NOLUN
)brace
comma
multiline_comment|/* locks up */
(brace
l_string|&quot;YAMAHA&quot;
comma
l_string|&quot;CRW6416S&quot;
comma
l_string|&quot;1.0c&quot;
comma
id|BLIST_NOLUN
)brace
comma
multiline_comment|/* locks up */
multiline_comment|/*&n;&t; * Other types of devices that have special flags.&n;&t; */
(brace
l_string|&quot;ADAPTEC&quot;
comma
l_string|&quot;AACRAID&quot;
comma
l_int|NULL
comma
id|BLIST_FORCELUN
)brace
comma
(brace
l_string|&quot;ADAPTEC&quot;
comma
l_string|&quot;Adaptec 5400S&quot;
comma
l_int|NULL
comma
id|BLIST_FORCELUN
)brace
comma
(brace
l_string|&quot;AFT PRO&quot;
comma
l_string|&quot;-IX CF&quot;
comma
l_string|&quot;0.0&gt;&quot;
comma
id|BLIST_FORCELUN
)brace
comma
(brace
l_string|&quot;BELKIN&quot;
comma
l_string|&quot;USB 2 HS-CF&quot;
comma
l_string|&quot;1.95&quot;
comma
id|BLIST_FORCELUN
)brace
comma
(brace
l_string|&quot;CANON&quot;
comma
l_string|&quot;IPUBJD&quot;
comma
l_int|NULL
comma
id|BLIST_SPARSELUN
)brace
comma
(brace
l_string|&quot;CBOX3&quot;
comma
l_string|&quot;USB Storage-SMC&quot;
comma
l_string|&quot;300A&quot;
comma
id|BLIST_FORCELUN
)brace
comma
(brace
l_string|&quot;CMD&quot;
comma
l_string|&quot;CRA-7280&quot;
comma
l_int|NULL
comma
id|BLIST_SPARSELUN
)brace
comma
multiline_comment|/* CMD RAID Controller */
(brace
l_string|&quot;CNSI&quot;
comma
l_string|&quot;G7324&quot;
comma
l_int|NULL
comma
id|BLIST_SPARSELUN
)brace
comma
multiline_comment|/* Chaparral G7324 RAID */
(brace
l_string|&quot;CNSi&quot;
comma
l_string|&quot;G8324&quot;
comma
l_int|NULL
comma
id|BLIST_SPARSELUN
)brace
comma
multiline_comment|/* Chaparral G8324 RAID */
(brace
l_string|&quot;COMPAQ&quot;
comma
l_string|&quot;LOGICAL VOLUME&quot;
comma
l_int|NULL
comma
id|BLIST_FORCELUN
)brace
comma
(brace
l_string|&quot;COMPAQ&quot;
comma
l_string|&quot;CR3500&quot;
comma
l_int|NULL
comma
id|BLIST_FORCELUN
)brace
comma
(brace
l_string|&quot;COMPAQ&quot;
comma
l_string|&quot;MSA1000&quot;
comma
l_int|NULL
comma
id|BLIST_SPARSELUN
op_or
id|BLIST_NOSTARTONADD
)brace
comma
(brace
l_string|&quot;COMPAQ&quot;
comma
l_string|&quot;MSA1000 VOLUME&quot;
comma
l_int|NULL
comma
id|BLIST_SPARSELUN
op_or
id|BLIST_NOSTARTONADD
)brace
comma
(brace
l_string|&quot;COMPAQ&quot;
comma
l_string|&quot;HSV110&quot;
comma
l_int|NULL
comma
id|BLIST_REPORTLUN2
op_or
id|BLIST_NOSTARTONADD
)brace
comma
(brace
l_string|&quot;DDN&quot;
comma
l_string|&quot;SAN DataDirector&quot;
comma
l_string|&quot;*&quot;
comma
id|BLIST_SPARSELUN
)brace
comma
(brace
l_string|&quot;DEC&quot;
comma
l_string|&quot;HSG80&quot;
comma
l_int|NULL
comma
id|BLIST_SPARSELUN
op_or
id|BLIST_NOSTARTONADD
)brace
comma
(brace
l_string|&quot;DELL&quot;
comma
l_string|&quot;PV660F&quot;
comma
l_int|NULL
comma
id|BLIST_SPARSELUN
)brace
comma
(brace
l_string|&quot;DELL&quot;
comma
l_string|&quot;PV660F   PSEUDO&quot;
comma
l_int|NULL
comma
id|BLIST_SPARSELUN
)brace
comma
(brace
l_string|&quot;DELL&quot;
comma
l_string|&quot;PSEUDO DEVICE .&quot;
comma
l_int|NULL
comma
id|BLIST_SPARSELUN
)brace
comma
multiline_comment|/* Dell PV 530F */
(brace
l_string|&quot;DELL&quot;
comma
l_string|&quot;PV530F&quot;
comma
l_int|NULL
comma
id|BLIST_SPARSELUN
)brace
comma
(brace
l_string|&quot;DELL&quot;
comma
l_string|&quot;PERCRAID&quot;
comma
l_int|NULL
comma
id|BLIST_FORCELUN
)brace
comma
(brace
l_string|&quot;DGC&quot;
comma
l_string|&quot;RAID&quot;
comma
l_int|NULL
comma
id|BLIST_SPARSELUN
)brace
comma
multiline_comment|/* Dell PV 650F, storage on LUN 0 */
(brace
l_string|&quot;DGC&quot;
comma
l_string|&quot;DISK&quot;
comma
l_int|NULL
comma
id|BLIST_SPARSELUN
)brace
comma
multiline_comment|/* Dell PV 650F, no storage on LUN 0 */
(brace
l_string|&quot;EMC&quot;
comma
l_string|&quot;SYMMETRIX&quot;
comma
l_int|NULL
comma
id|BLIST_SPARSELUN
op_or
id|BLIST_LARGELUN
op_or
id|BLIST_FORCELUN
)brace
comma
(brace
l_string|&quot;EMULEX&quot;
comma
l_string|&quot;MD21/S2     ESDI&quot;
comma
l_int|NULL
comma
id|BLIST_SINGLELUN
)brace
comma
(brace
l_string|&quot;FSC&quot;
comma
l_string|&quot;CentricStor&quot;
comma
l_string|&quot;*&quot;
comma
id|BLIST_SPARSELUN
op_or
id|BLIST_LARGELUN
)brace
comma
(brace
l_string|&quot;Generic&quot;
comma
l_string|&quot;USB SD Reader&quot;
comma
l_string|&quot;1.00&quot;
comma
id|BLIST_FORCELUN
)brace
comma
(brace
l_string|&quot;Generic&quot;
comma
l_string|&quot;USB Storage-SMC&quot;
comma
l_string|&quot;0180&quot;
comma
id|BLIST_FORCELUN
)brace
comma
(brace
l_string|&quot;Generic&quot;
comma
l_string|&quot;USB Storage-SMC&quot;
comma
l_string|&quot;0207&quot;
comma
id|BLIST_FORCELUN
)brace
comma
(brace
l_string|&quot;HITACHI&quot;
comma
l_string|&quot;DF400&quot;
comma
l_string|&quot;*&quot;
comma
id|BLIST_SPARSELUN
)brace
comma
(brace
l_string|&quot;HITACHI&quot;
comma
l_string|&quot;DF500&quot;
comma
l_string|&quot;*&quot;
comma
id|BLIST_SPARSELUN
)brace
comma
(brace
l_string|&quot;HITACHI&quot;
comma
l_string|&quot;DF600&quot;
comma
l_string|&quot;*&quot;
comma
id|BLIST_SPARSELUN
)brace
comma
(brace
l_string|&quot;HP&quot;
comma
l_string|&quot;A6189A&quot;
comma
l_int|NULL
comma
id|BLIST_SPARSELUN
op_or
id|BLIST_LARGELUN
)brace
comma
multiline_comment|/* HP VA7400 */
(brace
l_string|&quot;HP&quot;
comma
l_string|&quot;OPEN-&quot;
comma
l_string|&quot;*&quot;
comma
id|BLIST_SPARSELUN
op_or
id|BLIST_LARGELUN
)brace
comma
multiline_comment|/* HP XP Arrays */
(brace
l_string|&quot;HP&quot;
comma
l_string|&quot;NetRAID-4M&quot;
comma
l_int|NULL
comma
id|BLIST_FORCELUN
)brace
comma
(brace
l_string|&quot;HP&quot;
comma
l_string|&quot;HSV100&quot;
comma
l_int|NULL
comma
id|BLIST_REPORTLUN2
op_or
id|BLIST_NOSTARTONADD
)brace
comma
(brace
l_string|&quot;HP&quot;
comma
l_string|&quot;C1557A&quot;
comma
l_int|NULL
comma
id|BLIST_FORCELUN
)brace
comma
(brace
l_string|&quot;IBM&quot;
comma
l_string|&quot;AuSaV1S2&quot;
comma
l_int|NULL
comma
id|BLIST_FORCELUN
)brace
comma
(brace
l_string|&quot;IBM&quot;
comma
l_string|&quot;ProFibre 4000R&quot;
comma
l_string|&quot;*&quot;
comma
id|BLIST_SPARSELUN
op_or
id|BLIST_LARGELUN
)brace
comma
(brace
l_string|&quot;iomega&quot;
comma
l_string|&quot;jaz 1GB&quot;
comma
l_string|&quot;J.86&quot;
comma
id|BLIST_NOTQ
op_or
id|BLIST_NOLUN
)brace
comma
(brace
l_string|&quot;IOMEGA&quot;
comma
l_string|&quot;Io20S         *F&quot;
comma
l_int|NULL
comma
id|BLIST_KEY
)brace
comma
(brace
l_string|&quot;INSITE&quot;
comma
l_string|&quot;Floptical   F*8I&quot;
comma
l_int|NULL
comma
id|BLIST_KEY
)brace
comma
(brace
l_string|&quot;INSITE&quot;
comma
l_string|&quot;I325VM&quot;
comma
l_int|NULL
comma
id|BLIST_KEY
)brace
comma
(brace
l_string|&quot;LASOUND&quot;
comma
l_string|&quot;CDX7405&quot;
comma
l_string|&quot;3.10&quot;
comma
id|BLIST_MAX5LUN
op_or
id|BLIST_SINGLELUN
)brace
comma
(brace
l_string|&quot;MATSHITA&quot;
comma
l_string|&quot;PD-1&quot;
comma
l_int|NULL
comma
id|BLIST_FORCELUN
op_or
id|BLIST_SINGLELUN
)brace
comma
(brace
l_string|&quot;Medion&quot;
comma
l_string|&quot;Flash XL  MMC/SD&quot;
comma
l_string|&quot;2.6D&quot;
comma
id|BLIST_FORCELUN
)brace
comma
(brace
l_string|&quot;MegaRAID&quot;
comma
l_string|&quot;LD&quot;
comma
l_int|NULL
comma
id|BLIST_FORCELUN
)brace
comma
(brace
l_string|&quot;MICROP&quot;
comma
l_string|&quot;4110&quot;
comma
l_int|NULL
comma
id|BLIST_NOTQ
)brace
comma
(brace
l_string|&quot;MYLEX&quot;
comma
l_string|&quot;DACARMRB&quot;
comma
l_string|&quot;*&quot;
comma
id|BLIST_REPORTLUN2
)brace
comma
(brace
l_string|&quot;nCipher&quot;
comma
l_string|&quot;Fastness Crypto&quot;
comma
l_int|NULL
comma
id|BLIST_FORCELUN
)brace
comma
(brace
l_string|&quot;NAKAMICH&quot;
comma
l_string|&quot;MJ-4.8S&quot;
comma
l_int|NULL
comma
id|BLIST_FORCELUN
op_or
id|BLIST_SINGLELUN
)brace
comma
(brace
l_string|&quot;NAKAMICH&quot;
comma
l_string|&quot;MJ-5.16S&quot;
comma
l_int|NULL
comma
id|BLIST_FORCELUN
op_or
id|BLIST_SINGLELUN
)brace
comma
(brace
l_string|&quot;NEC&quot;
comma
l_string|&quot;PD-1 ODX654P&quot;
comma
l_int|NULL
comma
id|BLIST_FORCELUN
op_or
id|BLIST_SINGLELUN
)brace
comma
(brace
l_string|&quot;NRC&quot;
comma
l_string|&quot;MBR-7&quot;
comma
l_int|NULL
comma
id|BLIST_FORCELUN
op_or
id|BLIST_SINGLELUN
)brace
comma
(brace
l_string|&quot;NRC&quot;
comma
l_string|&quot;MBR-7.4&quot;
comma
l_int|NULL
comma
id|BLIST_FORCELUN
op_or
id|BLIST_SINGLELUN
)brace
comma
(brace
l_string|&quot;PIONEER&quot;
comma
l_string|&quot;CD-ROM DRM-600&quot;
comma
l_int|NULL
comma
id|BLIST_FORCELUN
op_or
id|BLIST_SINGLELUN
)brace
comma
(brace
l_string|&quot;PIONEER&quot;
comma
l_string|&quot;CD-ROM DRM-602X&quot;
comma
l_int|NULL
comma
id|BLIST_FORCELUN
op_or
id|BLIST_SINGLELUN
)brace
comma
(brace
l_string|&quot;PIONEER&quot;
comma
l_string|&quot;CD-ROM DRM-604X&quot;
comma
l_int|NULL
comma
id|BLIST_FORCELUN
op_or
id|BLIST_SINGLELUN
)brace
comma
(brace
l_string|&quot;REGAL&quot;
comma
l_string|&quot;CDC-4X&quot;
comma
l_int|NULL
comma
id|BLIST_MAX5LUN
op_or
id|BLIST_SINGLELUN
)brace
comma
(brace
l_string|&quot;SanDisk&quot;
comma
l_string|&quot;ImageMate CF-SD1&quot;
comma
l_int|NULL
comma
id|BLIST_FORCELUN
)brace
comma
(brace
l_string|&quot;SGI&quot;
comma
l_string|&quot;RAID3&quot;
comma
l_string|&quot;*&quot;
comma
id|BLIST_SPARSELUN
)brace
comma
(brace
l_string|&quot;SGI&quot;
comma
l_string|&quot;RAID5&quot;
comma
l_string|&quot;*&quot;
comma
id|BLIST_SPARSELUN
)brace
comma
(brace
l_string|&quot;SGI&quot;
comma
l_string|&quot;TP9100&quot;
comma
l_string|&quot;*&quot;
comma
id|BLIST_REPORTLUN2
)brace
comma
(brace
l_string|&quot;SMSC&quot;
comma
l_string|&quot;USB 2 HS-CF&quot;
comma
l_int|NULL
comma
id|BLIST_SPARSELUN
)brace
comma
(brace
l_string|&quot;SONY&quot;
comma
l_string|&quot;CD-ROM CDU-8001&quot;
comma
l_int|NULL
comma
id|BLIST_BORKEN
)brace
comma
(brace
l_string|&quot;SONY&quot;
comma
l_string|&quot;TSL&quot;
comma
l_int|NULL
comma
id|BLIST_FORCELUN
)brace
comma
multiline_comment|/* DDS3 &amp; DDS4 autoloaders */
(brace
l_string|&quot;SUN&quot;
comma
l_string|&quot;T300&quot;
comma
l_string|&quot;*&quot;
comma
id|BLIST_SPARSELUN
)brace
comma
(brace
l_string|&quot;SUN&quot;
comma
l_string|&quot;T4&quot;
comma
l_string|&quot;*&quot;
comma
id|BLIST_SPARSELUN
)brace
comma
(brace
l_string|&quot;TEXEL&quot;
comma
l_string|&quot;CD-ROM&quot;
comma
l_string|&quot;1.06&quot;
comma
id|BLIST_BORKEN
)brace
comma
(brace
l_string|&quot;TOSHIBA&quot;
comma
l_string|&quot;CDROM&quot;
comma
l_int|NULL
comma
id|BLIST_ISROM
)brace
comma
(brace
l_string|&quot;TOSHIBA&quot;
comma
l_string|&quot;CD-ROM&quot;
comma
l_int|NULL
comma
id|BLIST_ISROM
)brace
comma
(brace
l_string|&quot;USB2.0&quot;
comma
l_string|&quot;SMARTMEDIA/XD&quot;
comma
l_int|NULL
comma
id|BLIST_FORCELUN
)brace
comma
(brace
l_string|&quot;XYRATEX&quot;
comma
l_string|&quot;RS&quot;
comma
l_string|&quot;*&quot;
comma
id|BLIST_SPARSELUN
op_or
id|BLIST_LARGELUN
)brace
comma
(brace
l_string|&quot;Zzyzx&quot;
comma
l_string|&quot;RocketStor 500S&quot;
comma
l_int|NULL
comma
id|BLIST_SPARSELUN
)brace
comma
(brace
l_string|&quot;Zzyzx&quot;
comma
l_string|&quot;RocketStor 2000&quot;
comma
l_int|NULL
comma
id|BLIST_SPARSELUN
)brace
comma
(brace
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|0
)brace
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * scsi_strcpy_devinfo: called from scsi_dev_info_list_add to copy into&n; * devinfo vendor and model strings.&n; */
DECL|function|scsi_strcpy_devinfo
r_static
r_void
id|scsi_strcpy_devinfo
c_func
(paren
r_char
op_star
id|name
comma
r_char
op_star
id|to
comma
r_int
id|to_length
comma
r_char
op_star
id|from
comma
r_int
id|compatible
)paren
(brace
r_int
id|from_length
suffix:semicolon
id|from_length
op_assign
id|strlen
c_func
(paren
id|from
)paren
suffix:semicolon
id|strncpy
c_func
(paren
id|to
comma
id|from
comma
id|min
c_func
(paren
id|to_length
comma
id|from_length
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|from_length
OL
id|to_length
)paren
(brace
r_if
c_cond
(paren
id|compatible
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * NUL terminate the string if it is short.&n;&t;&t;&t; */
id|to
(braket
id|from_length
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* &n;&t;&t;&t; * space pad the string if it is short. &n;&t;&t;&t; */
id|strncpy
c_func
(paren
op_amp
id|to
(braket
id|from_length
)braket
comma
id|spaces
comma
id|to_length
op_minus
id|from_length
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|from_length
OG
id|to_length
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: %s string &squot;%s&squot; is too long&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|name
comma
id|from
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * scsi_dev_info_list_add: add one dev_info list entry.&n; * @vendor:&t;vendor string&n; * @model:&t;model (product) string&n; * @strflags:&t;integer string&n; * @flag:&t;if strflags NULL, use this flag value&n; *&n; * Description:&n; * &t;Create and add one dev_info entry for @vendor, @model, @strflags or&n; * &t;@flag. If @compatible, add to the tail of the list, do not space&n; * &t;pad, and set devinfo-&gt;compatible. The scsi_static_device_list entries&n; * &t;are added with @compatible 1 and @clfags NULL.&n; *&n; * Returns: 0 OK, -error on failure.&n; **/
DECL|function|scsi_dev_info_list_add
r_static
r_int
id|scsi_dev_info_list_add
c_func
(paren
r_int
id|compatible
comma
r_char
op_star
id|vendor
comma
r_char
op_star
id|model
comma
r_char
op_star
id|strflags
comma
r_int
id|flags
)paren
(brace
r_struct
id|scsi_dev_info_list
op_star
id|devinfo
suffix:semicolon
id|devinfo
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|devinfo
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|devinfo
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: no memory&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|scsi_strcpy_devinfo
c_func
(paren
l_string|&quot;vendor&quot;
comma
id|devinfo-&gt;vendor
comma
r_sizeof
(paren
id|devinfo-&gt;vendor
)paren
comma
id|vendor
comma
id|compatible
)paren
suffix:semicolon
id|scsi_strcpy_devinfo
c_func
(paren
l_string|&quot;model&quot;
comma
id|devinfo-&gt;model
comma
r_sizeof
(paren
id|devinfo-&gt;model
)paren
comma
id|model
comma
id|compatible
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strflags
)paren
id|devinfo-&gt;flags
op_assign
id|simple_strtoul
c_func
(paren
id|strflags
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
r_else
id|devinfo-&gt;flags
op_assign
id|flags
suffix:semicolon
id|devinfo-&gt;compatible
op_assign
id|compatible
suffix:semicolon
r_if
c_cond
(paren
id|compatible
)paren
id|list_add_tail
c_func
(paren
op_amp
id|devinfo-&gt;dev_info_list
comma
op_amp
id|scsi_dev_info_list
)paren
suffix:semicolon
r_else
id|list_add
c_func
(paren
op_amp
id|devinfo-&gt;dev_info_list
comma
op_amp
id|scsi_dev_info_list
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * scsi_dev_info_list_add_str: parse dev_list and add to the&n; * scsi_dev_info_list.&n; * @dev_list:&t;string of device flags to add&n; *&n; * Description:&n; * &t;Parse dev_list, and add entries to the scsi_dev_info_list.&n; * &t;dev_list is of the form &quot;vendor:product:flag,vendor:product:flag&quot;.&n; * &t;dev_list is modified via strsep. Can be called for command line&n; * &t;addition, for proc or mabye a sysfs interface.&n; *&n; * Returns: 0 if OK, -error on failure.&n; **/
DECL|function|scsi_dev_info_list_add_str
r_static
r_int
id|scsi_dev_info_list_add_str
c_func
(paren
r_char
op_star
id|dev_list
)paren
(brace
r_char
op_star
id|vendor
comma
op_star
id|model
comma
op_star
id|strflags
comma
op_star
id|next
suffix:semicolon
r_char
op_star
id|next_check
suffix:semicolon
r_int
id|res
op_assign
l_int|0
suffix:semicolon
id|next
op_assign
id|dev_list
suffix:semicolon
r_if
c_cond
(paren
id|next
op_logical_and
id|next
(braket
l_int|0
)braket
op_eq
l_char|&squot;&quot;&squot;
)paren
(brace
multiline_comment|/*&n;&t;&t; * Ignore both the leading and trailing quote.&n;&t;&t; */
id|next
op_increment
suffix:semicolon
id|next_check
op_assign
l_string|&quot;,&bslash;&quot;&quot;
suffix:semicolon
)brace
r_else
(brace
id|next_check
op_assign
l_string|&quot;,&quot;
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * For the leading and trailing &squot;&quot;&squot; case, the for loop comes&n;&t; * through the last time with vendor[0] == &squot;&bslash;0&squot;.&n;&t; */
r_for
c_loop
(paren
id|vendor
op_assign
id|strsep
c_func
(paren
op_amp
id|next
comma
l_string|&quot;:&quot;
)paren
suffix:semicolon
id|vendor
op_logical_and
(paren
id|vendor
(braket
l_int|0
)braket
op_ne
l_char|&squot;&bslash;0&squot;
)paren
op_logical_and
(paren
id|res
op_eq
l_int|0
)paren
suffix:semicolon
id|vendor
op_assign
id|strsep
c_func
(paren
op_amp
id|next
comma
l_string|&quot;:&quot;
)paren
)paren
(brace
id|strflags
op_assign
l_int|NULL
suffix:semicolon
id|model
op_assign
id|strsep
c_func
(paren
op_amp
id|next
comma
l_string|&quot;:&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|model
)paren
id|strflags
op_assign
id|strsep
c_func
(paren
op_amp
id|next
comma
id|next_check
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|model
op_logical_or
op_logical_neg
id|strflags
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: bad dev info string &squot;%s&squot; &squot;%s&squot;&quot;
l_string|&quot; &squot;%s&squot;&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|vendor
comma
id|model
comma
id|strflags
)paren
suffix:semicolon
id|res
op_assign
op_minus
id|EINVAL
suffix:semicolon
)brace
r_else
id|res
op_assign
id|scsi_dev_info_list_add
c_func
(paren
l_int|0
multiline_comment|/* compatible */
comma
id|vendor
comma
id|model
comma
id|strflags
comma
l_int|0
)paren
suffix:semicolon
)brace
r_return
id|res
suffix:semicolon
)brace
multiline_comment|/**&n; * get_device_flags - get device specific flags from the dynamic device&n; * list. Called during scan time.&n; * @vendor:&t;vendor name&n; * @model:&t;model name&n; *&n; * Description:&n; *     Search the scsi_dev_info_list for an entry matching @vendor and&n; *     @model, if found, return the matching flags value, else return&n; *     the host or global default settings.&n; **/
DECL|function|scsi_get_device_flags
r_int
id|scsi_get_device_flags
c_func
(paren
r_struct
id|scsi_device
op_star
id|sdev
comma
r_int
r_char
op_star
id|vendor
comma
r_int
r_char
op_star
id|model
)paren
(brace
r_struct
id|scsi_dev_info_list
op_star
id|devinfo
suffix:semicolon
r_int
r_int
id|bflags
suffix:semicolon
id|bflags
op_assign
id|sdev-&gt;sdev_bflags
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bflags
)paren
id|bflags
op_assign
id|scsi_default_dev_flags
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|devinfo
comma
op_amp
id|scsi_dev_info_list
comma
id|dev_info_list
)paren
(brace
r_if
c_cond
(paren
id|devinfo-&gt;compatible
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Behave like the older version of get_device_flags.&n;&t;&t;&t; */
r_int
id|max
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * XXX why skip leading spaces? If an odd INQUIRY&n;&t;&t;&t; * value, that should have been part of the&n;&t;&t;&t; * scsi_static_device_list[] entry, such as &quot;  FOO&quot;&n;&t;&t;&t; * rather than &quot;FOO&quot;. Since this code is already&n;&t;&t;&t; * here, and we don&squot;t know what device it is&n;&t;&t;&t; * trying to work with, leave it as-is.&n;&t;&t;&t; */
id|max
op_assign
l_int|8
suffix:semicolon
multiline_comment|/* max length of vendor */
r_while
c_loop
(paren
(paren
id|max
OG
l_int|0
)paren
op_logical_and
op_star
id|vendor
op_eq
l_char|&squot; &squot;
)paren
(brace
id|max
op_decrement
suffix:semicolon
id|vendor
op_increment
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t;&t; * XXX removing the following strlen() would be&n;&t;&t;&t; * good, using it means that for a an entry not in&n;&t;&t;&t; * the list, we scan every byte of every vendor&n;&t;&t;&t; * listed in scsi_static_device_list[], and never match&n;&t;&t;&t; * a single one (and still have to compare at&n;&t;&t;&t; * least the first byte of each vendor).&n;&t;&t;&t; */
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|devinfo-&gt;vendor
comma
id|vendor
comma
id|min
c_func
(paren
id|max
comma
id|strlen
c_func
(paren
id|devinfo-&gt;vendor
)paren
)paren
)paren
)paren
r_continue
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Skip spaces again.&n;&t;&t;&t; */
id|max
op_assign
l_int|16
suffix:semicolon
multiline_comment|/* max length of model */
r_while
c_loop
(paren
(paren
id|max
OG
l_int|0
)paren
op_logical_and
op_star
id|model
op_eq
l_char|&squot; &squot;
)paren
(brace
id|max
op_decrement
suffix:semicolon
id|model
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|devinfo-&gt;model
comma
id|model
comma
id|min
c_func
(paren
id|max
comma
id|strlen
c_func
(paren
id|devinfo-&gt;model
)paren
)paren
)paren
)paren
r_continue
suffix:semicolon
r_return
id|devinfo-&gt;flags
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|devinfo-&gt;vendor
comma
id|vendor
comma
r_sizeof
(paren
id|devinfo-&gt;vendor
)paren
)paren
op_logical_and
op_logical_neg
id|memcmp
c_func
(paren
id|devinfo-&gt;model
comma
id|model
comma
r_sizeof
(paren
id|devinfo-&gt;model
)paren
)paren
)paren
r_return
id|devinfo-&gt;flags
suffix:semicolon
)brace
)brace
r_return
id|bflags
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SCSI_PROC_FS
multiline_comment|/* &n; * proc_scsi_dev_info_read: dump the scsi_dev_info_list via&n; * /proc/scsi/device_info&n; */
DECL|function|proc_scsi_devinfo_read
r_static
r_int
id|proc_scsi_devinfo_read
c_func
(paren
r_char
op_star
id|buffer
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|length
)paren
(brace
r_struct
id|scsi_dev_info_list
op_star
id|devinfo
suffix:semicolon
r_int
id|size
comma
id|len
op_assign
l_int|0
suffix:semicolon
id|off_t
id|begin
op_assign
l_int|0
suffix:semicolon
id|off_t
id|pos
op_assign
l_int|0
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|devinfo
comma
op_amp
id|scsi_dev_info_list
comma
id|dev_info_list
)paren
(brace
id|size
op_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;&squot;%.8s&squot; &squot;%.16s&squot; 0x%x&bslash;n&quot;
comma
id|devinfo-&gt;vendor
comma
id|devinfo-&gt;model
comma
id|devinfo-&gt;flags
)paren
suffix:semicolon
id|len
op_add_assign
id|size
suffix:semicolon
id|pos
op_assign
id|begin
op_plus
id|len
suffix:semicolon
r_if
c_cond
(paren
id|pos
OL
id|offset
)paren
(brace
id|len
op_assign
l_int|0
suffix:semicolon
id|begin
op_assign
id|pos
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pos
OG
id|offset
op_plus
id|length
)paren
r_goto
id|stop_output
suffix:semicolon
)brace
id|stop_output
suffix:colon
op_star
id|start
op_assign
id|buffer
op_plus
(paren
id|offset
op_minus
id|begin
)paren
suffix:semicolon
multiline_comment|/* Start of wanted data */
id|len
op_sub_assign
(paren
id|offset
op_minus
id|begin
)paren
suffix:semicolon
multiline_comment|/* Start slop */
r_if
c_cond
(paren
id|len
OG
id|length
)paren
id|len
op_assign
id|length
suffix:semicolon
multiline_comment|/* Ending slop */
r_return
(paren
id|len
)paren
suffix:semicolon
)brace
multiline_comment|/* &n; * proc_scsi_dev_info_write: allow additions to the scsi_dev_info_list via&n; * /proc.&n; *&n; * Use: echo &quot;vendor:model:flag&quot; &gt; /proc/scsi/device_info&n; *&n; * To add a black/white list entry for vendor and model with an integer&n; * value of flag to the scsi device info list.&n; */
DECL|function|proc_scsi_devinfo_write
r_static
r_int
id|proc_scsi_devinfo_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
id|__user
op_star
id|buf
comma
r_int
r_int
id|length
comma
r_void
op_star
id|data
)paren
(brace
r_char
op_star
id|buffer
suffix:semicolon
r_int
id|err
op_assign
id|length
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buf
op_logical_or
id|length
OG
id|PAGE_SIZE
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|buffer
op_assign
(paren
r_char
op_star
)paren
id|__get_free_page
c_func
(paren
id|GFP_KERNEL
)paren
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|buffer
comma
id|buf
comma
id|length
)paren
)paren
(brace
id|err
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|length
OL
id|PAGE_SIZE
)paren
id|buffer
(braket
id|length
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_else
r_if
c_cond
(paren
id|buffer
(braket
id|PAGE_SIZE
op_minus
l_int|1
)braket
)paren
(brace
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|scsi_dev_info_list_add_str
c_func
(paren
id|buffer
)paren
suffix:semicolon
id|out
suffix:colon
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|buffer
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_SCSI_PROC_FS */
id|module_param_string
c_func
(paren
id|dev_flags
comma
id|scsi_dev_flags
comma
r_sizeof
(paren
id|scsi_dev_flags
)paren
comma
l_int|0
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|dev_flags
comma
l_string|&quot;Given scsi_dev_flags=vendor:model:flags[,v:m:f] add black/white&quot;
l_string|&quot; list entries for vendor and model with an integer value of flags&quot;
l_string|&quot; to the scsi device info list&quot;
)paren
suffix:semicolon
id|module_param_named
c_func
(paren
id|default_dev_flags
comma
id|scsi_default_dev_flags
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
id|default_dev_flags
comma
l_string|&quot;scsi default device flag integer value&quot;
)paren
suffix:semicolon
multiline_comment|/**&n; * scsi_dev_info_list_delete: called from scsi.c:exit_scsi to remove&n; * &t;the scsi_dev_info_list.&n; **/
DECL|function|scsi_exit_devinfo
r_void
id|scsi_exit_devinfo
c_func
(paren
r_void
)paren
(brace
r_struct
id|list_head
op_star
id|lh
comma
op_star
id|lh_next
suffix:semicolon
r_struct
id|scsi_dev_info_list
op_star
id|devinfo
suffix:semicolon
macro_line|#ifdef CONFIG_SCSI_PROC_FS
id|remove_proc_entry
c_func
(paren
l_string|&quot;scsi/device_info&quot;
comma
l_int|0
)paren
suffix:semicolon
macro_line|#endif
id|list_for_each_safe
c_func
(paren
id|lh
comma
id|lh_next
comma
op_amp
id|scsi_dev_info_list
)paren
(brace
id|devinfo
op_assign
id|list_entry
c_func
(paren
id|lh
comma
r_struct
id|scsi_dev_info_list
comma
id|dev_info_list
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|devinfo
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; * scsi_dev_list_init: set up the dynamic device list.&n; * @dev_list:&t;string of device flags to add&n; *&n; * Description:&n; * &t;Add command line @dev_list entries, then add&n; * &t;scsi_static_device_list entries to the scsi device info list.&n; **/
DECL|function|scsi_init_devinfo
r_int
id|scsi_init_devinfo
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_SCSI_PROC_FS
r_struct
id|proc_dir_entry
op_star
id|p
suffix:semicolon
macro_line|#endif
r_int
id|error
comma
id|i
suffix:semicolon
id|error
op_assign
id|scsi_dev_info_list_add_str
c_func
(paren
id|scsi_dev_flags
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
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|scsi_static_device_list
(braket
id|i
)braket
dot
id|vendor
suffix:semicolon
id|i
op_increment
)paren
(brace
id|error
op_assign
id|scsi_dev_info_list_add
c_func
(paren
l_int|1
multiline_comment|/* compatibile */
comma
id|scsi_static_device_list
(braket
id|i
)braket
dot
id|vendor
comma
id|scsi_static_device_list
(braket
id|i
)braket
dot
id|model
comma
l_int|NULL
comma
id|scsi_static_device_list
(braket
id|i
)braket
dot
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|out
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SCSI_PROC_FS
id|p
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;scsi/device_info&quot;
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
(brace
id|error
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|p-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|p-&gt;get_info
op_assign
id|proc_scsi_devinfo_read
suffix:semicolon
id|p-&gt;write_proc
op_assign
id|proc_scsi_devinfo_write
suffix:semicolon
macro_line|#endif /* CONFIG_SCSI_PROC_FS */
id|out
suffix:colon
r_if
c_cond
(paren
id|error
)paren
id|scsi_exit_devinfo
c_func
(paren
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
eof
