multiline_comment|/*&n; * SWIM access through the IOP&n; * Written by Joshua M. Thompson&n; */
multiline_comment|/* IOP number and channel number for the SWIM */
DECL|macro|SWIM_IOP
mdefine_line|#define SWIM_IOP&t;IOP_NUM_ISM
DECL|macro|SWIM_CHAN
mdefine_line|#define SWIM_CHAN&t;1
multiline_comment|/* Command code: */
DECL|macro|CMD_INIT
mdefine_line|#define CMD_INIT&t;&t;0x01&t;/* Initialize                  */
DECL|macro|CMD_SHUTDOWN
mdefine_line|#define CMD_SHUTDOWN&t;&t;0x02&t;/* Shutdown                    */
DECL|macro|CMD_START_POLL
mdefine_line|#define CMD_START_POLL&t;&t;0x03&t;/* Start insert/eject polling  */
DECL|macro|CMD_STOP_POLL
mdefine_line|#define CMD_STOP_POLL&t;&t;0x04&t;/* Stop insert/eject polling   */
DECL|macro|CMD_SETHFSTAG
mdefine_line|#define CMD_SETHFSTAG&t;&t;0x05&t;/* Set HFS tag buffer address  */
DECL|macro|CMD_STATUS
mdefine_line|#define CMD_STATUS&t;&t;0x06&t;/* Status                      */
DECL|macro|CMD_EJECT
mdefine_line|#define CMD_EJECT&t;&t;0x07&t;/* Eject                       */
DECL|macro|CMD_FORMAT
mdefine_line|#define CMD_FORMAT&t;&t;0x08&t;/* Format                      */
DECL|macro|CMD_FORMAT_VERIFY
mdefine_line|#define CMD_FORMAT_VERIFY&t;0x09&t;/* Format and Verify           */
DECL|macro|CMD_WRITE
mdefine_line|#define CMD_WRITE&t;&t;0x0A&t;/* Write                       */
DECL|macro|CMD_READ
mdefine_line|#define CMD_READ&t;&t;0x0B&t;/* Read                        */
DECL|macro|CMD_READ_VERIFY
mdefine_line|#define CMD_READ_VERIFY&t;&t;0x0C&t;/* Read and Verify             */
DECL|macro|CMD_CACHE_CTRL
mdefine_line|#define CMD_CACHE_CTRL&t;&t;0x0D&t;/* Cache control               */
DECL|macro|CMD_TAGBUFF_CTRL
mdefine_line|#define CMD_TAGBUFF_CTRL&t;0x0E&t;/* Tag buffer control          */
DECL|macro|CMD_GET_ICON
mdefine_line|#define CMD_GET_ICON&t;&t;0x0F&t;/* Get Icon                    */
multiline_comment|/* Drive types: */
multiline_comment|/* note: apple sez DRV_FDHD is 4, but I get back a type */
multiline_comment|/*       of 5 when I do a drive status check on my FDHD */
DECL|macro|DRV_NONE
mdefine_line|#define&t;DRV_NONE&t;0&t;/* No drive             */
DECL|macro|DRV_UNKNOWN
mdefine_line|#define&t;DRV_UNKNOWN&t;1&t;/* Unspecified drive    */
DECL|macro|DRV_400K
mdefine_line|#define&t;DRV_400K&t;2&t;/* 400K                 */
DECL|macro|DRV_800K
mdefine_line|#define&t;DRV_800K&t;3&t;/* 400K/800K            */
DECL|macro|DRV_FDHD
mdefine_line|#define&t;DRV_FDHD&t;5&t;/* 400K/800K/720K/1440K */
DECL|macro|DRV_HD20
mdefine_line|#define&t;DRV_HD20&t;7&t;/* Apple HD20           */
multiline_comment|/* Format types: */
DECL|macro|FMT_HD20
mdefine_line|#define&t;FMT_HD20&t;0x0001&t;/*  Apple HD20 */
DECL|macro|FMT_400K
mdefine_line|#define&t;FMT_400K&t;0x0002&t;/*  400K (GCR) */
DECL|macro|FMT_800K
mdefine_line|#define&t;FMT_800K&t;0x0004&t;/*  800K (GCR) */
DECL|macro|FMT_720K
mdefine_line|#define&t;FMT_720K&t;0x0008&t;/*  720K (MFM) */
DECL|macro|FMT_1440K
mdefine_line|#define&t;FMT_1440K&t;0x0010&t;/* 1.44M (MFM) */
DECL|macro|FMD_KIND_400K
mdefine_line|#define&t;FMD_KIND_400K&t;1
DECL|macro|FMD_KIND_800K
mdefine_line|#define&t;FMD_KIND_800K&t;2
DECL|macro|FMD_KIND_720K
mdefine_line|#define&t;FMD_KIND_720K&t;3
DECL|macro|FMD_KIND_1440K
mdefine_line|#define&t;FMD_KIND_1440K&t;1
multiline_comment|/* Icon Flags: */
DECL|macro|ICON_MEDIA
mdefine_line|#define&t;ICON_MEDIA&t;0x01&t;/* Have IOP supply media icon */
DECL|macro|ICON_DRIVE
mdefine_line|#define&t;ICON_DRIVE&t;0x01&t;/* Have IOP supply drive icon */
multiline_comment|/* Error codes: */
DECL|macro|gcrOnMFMErr
mdefine_line|#define&t;gcrOnMFMErr&t;-400&t;/* GCR (400/800K) on HD media */
DECL|macro|verErr
mdefine_line|#define&t;verErr&t;&t;-84&t;/* verify failed */
DECL|macro|fmt2Err
mdefine_line|#define&t;fmt2Err&t;&t;-83&t;/* cant get enough sync during format */
DECL|macro|fmt1Err
mdefine_line|#define&t;fmt1Err&t;&t;-82&t;/* can&squot;t find sector 0 after track format */
DECL|macro|sectNFErr
mdefine_line|#define&t;sectNFErr&t;-81&t;/* can&squot;t find sector */
DECL|macro|seekErr
mdefine_line|#define&t;seekErr&t;&t;-80&t;/* drive error during seek */
DECL|macro|spdAdjErr
mdefine_line|#define&t;spdAdjErr&t;-79&t;/* can&squot;t set drive speed */
DECL|macro|twoSideErr
mdefine_line|#define&t;twoSideErr&t;-78&t;/* drive is single-sided */
DECL|macro|initIWMErr
mdefine_line|#define&t;initIWMErr&t;-77&t;/* error during initialization */
DECL|macro|tk0badErr
mdefine_line|#define&t;tk0badErr&t;-76&t;/* track zero is bad */
DECL|macro|cantStepErr
mdefine_line|#define&t;cantStepErr&t;-75&t;/* drive error during step */
DECL|macro|wrUnderrun
mdefine_line|#define&t;wrUnderrun&t;-74&t;/* write underrun occurred */
DECL|macro|badDBtSlp
mdefine_line|#define&t;badDBtSlp&t;-73&t;/* bad data bitslip marks */
DECL|macro|badDCksum
mdefine_line|#define&t;badDCksum&t;-72&t;/* bad data checksum */
DECL|macro|noDtaMkErr
mdefine_line|#define&t;noDtaMkErr&t;-71&t;/* can&squot;t find data mark */
DECL|macro|badBtSlpErr
mdefine_line|#define&t;badBtSlpErr&t;-70&t;/* bad address bitslip marks */
DECL|macro|badCksmErr
mdefine_line|#define&t;badCksmErr&t;-69&t;/* bad address-mark checksum */
DECL|macro|dataVerErr
mdefine_line|#define&t;dataVerErr&t;-68&t;/* read-verify failed */
DECL|macro|noAdrMkErr
mdefine_line|#define&t;noAdrMkErr&t;-67&t;/* can&squot;t find an address mark */
DECL|macro|noNybErr
mdefine_line|#define&t;noNybErr&t;-66&t;/* no nybbles? disk is probably degaussed */
DECL|macro|offLinErr
mdefine_line|#define&t;offLinErr&t;-65&t;/* no disk in drive */
DECL|macro|noDriveErr
mdefine_line|#define&t;noDriveErr&t;-64&t;/* drive isn&squot;t connected */
DECL|macro|nsDrvErr
mdefine_line|#define&t;nsDrvErr&t;-56&t;/* no such drive */
DECL|macro|paramErr
mdefine_line|#define&t;paramErr&t;-50&t;/* bad positioning information */
DECL|macro|wPrErr
mdefine_line|#define&t;wPrErr&t;&t;-44&t;/* write protected */
DECL|macro|openErr
mdefine_line|#define&t;openErr&t;&t;-23&t;/* already initialized */
macro_line|#ifndef __ASSEMBLY__
DECL|struct|swim_drvstatus
r_struct
id|swim_drvstatus
(brace
DECL|member|curr_track
id|__u16
id|curr_track
suffix:semicolon
multiline_comment|/* Current track number                   */
DECL|member|write_prot
id|__u8
id|write_prot
suffix:semicolon
multiline_comment|/* 0x80 if disk is write protected        */
DECL|member|disk_in_drive
id|__u8
id|disk_in_drive
suffix:semicolon
multiline_comment|/* 0x01 or 0x02 if a disk is in the drive */
DECL|member|installed
id|__u8
id|installed
suffix:semicolon
multiline_comment|/* 0x01 if drive installed, 0xFF if not   */
DECL|member|num_sides
id|__u8
id|num_sides
suffix:semicolon
multiline_comment|/* 0x80 if two-sided format supported     */
DECL|member|two_sided
id|__u8
id|two_sided
suffix:semicolon
multiline_comment|/* 0xff if two-sided format diskette      */
DECL|member|new_interface
id|__u8
id|new_interface
suffix:semicolon
multiline_comment|/* 0x00 if old 400K drive, 0xFF if newer  */
DECL|member|errors
id|__u16
id|errors
suffix:semicolon
multiline_comment|/* Disk error count                       */
r_struct
(brace
multiline_comment|/* 32 bits */
DECL|member|reserved
id|__u16
id|reserved
suffix:semicolon
DECL|member|__u16
id|__u16
suffix:colon
l_int|4
suffix:semicolon
DECL|member|external
id|__u16
id|external
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive is external        */
DECL|member|scsi
id|__u16
id|scsi
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive is a SCSI drive    */
DECL|member|fixed
id|__u16
id|fixed
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive has fixed media    */
DECL|member|secondary
id|__u16
id|secondary
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Drive is secondary drive */
DECL|member|type
id|__u8
id|type
suffix:semicolon
multiline_comment|/* Drive type               */
DECL|member|info
)brace
id|info
suffix:semicolon
DECL|member|mfm_drive
id|__u8
id|mfm_drive
suffix:semicolon
multiline_comment|/* 0xFF if this is an FDHD drive    */
DECL|member|mfm_disk
id|__u8
id|mfm_disk
suffix:semicolon
multiline_comment|/* 0xFF if 720K/1440K (MFM) disk    */
DECL|member|mfm_format
id|__u8
id|mfm_format
suffix:semicolon
multiline_comment|/* 0x00 if 720K, 0xFF if 1440K      */
DECL|member|ctlr_type
id|__u8
id|ctlr_type
suffix:semicolon
multiline_comment|/* 0x00 if IWM, 0xFF if SWIM        */
DECL|member|curr_format
id|__u16
id|curr_format
suffix:semicolon
multiline_comment|/* Current format type              */
DECL|member|allowed_fmt
id|__u16
id|allowed_fmt
suffix:semicolon
multiline_comment|/* Allowed format types             */
DECL|member|num_blocks
id|__u32
id|num_blocks
suffix:semicolon
multiline_comment|/* Number of blocks on disk         */
DECL|member|icon_flags
id|__u8
id|icon_flags
suffix:semicolon
multiline_comment|/* Icon flags                       */
DECL|member|unusued
id|__u8
id|unusued
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Commands issued from the host to the IOP: */
DECL|struct|swimcmd_init
r_struct
id|swimcmd_init
(brace
DECL|member|code
id|__u8
id|code
suffix:semicolon
multiline_comment|/* CMD_INIT */
DECL|member|unusued
id|__u8
id|unusued
suffix:semicolon
DECL|member|error
id|__u16
id|error
suffix:semicolon
DECL|member|drives
id|__u8
id|drives
(braket
l_int|28
)braket
suffix:semicolon
multiline_comment|/* drive type list */
)brace
suffix:semicolon
DECL|struct|swimcmd_startpoll
r_struct
id|swimcmd_startpoll
(brace
DECL|member|code
id|__u8
id|code
suffix:semicolon
multiline_comment|/* CMD_START_POLL */
DECL|member|unusued
id|__u8
id|unusued
suffix:semicolon
DECL|member|error
id|__u16
id|error
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|swimcmd_sethfstag
r_struct
id|swimcmd_sethfstag
(brace
DECL|member|code
id|__u8
id|code
suffix:semicolon
multiline_comment|/* CMD_SETHFSTAG */
DECL|member|unusued
id|__u8
id|unusued
suffix:semicolon
DECL|member|error
id|__u16
id|error
suffix:semicolon
DECL|member|tagbuf
id|caddr_t
id|tagbuf
suffix:semicolon
multiline_comment|/* HFS tag buffer address */
)brace
suffix:semicolon
DECL|struct|swimcmd_status
r_struct
id|swimcmd_status
(brace
DECL|member|code
id|__u8
id|code
suffix:semicolon
multiline_comment|/* CMD_STATUS */
DECL|member|drive_num
id|__u8
id|drive_num
suffix:semicolon
DECL|member|error
id|__u16
id|error
suffix:semicolon
DECL|member|status
r_struct
id|swim_drvstatus
id|status
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|swimcmd_eject
r_struct
id|swimcmd_eject
(brace
DECL|member|code
id|__u8
id|code
suffix:semicolon
multiline_comment|/* CMD_EJECT */
DECL|member|drive_num
id|__u8
id|drive_num
suffix:semicolon
DECL|member|error
id|__u16
id|error
suffix:semicolon
DECL|member|status
r_struct
id|swim_drvstatus
id|status
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|swimcmd_format
r_struct
id|swimcmd_format
(brace
DECL|member|code
id|__u8
id|code
suffix:semicolon
multiline_comment|/* CMD_FORMAT */
DECL|member|drive_num
id|__u8
id|drive_num
suffix:semicolon
DECL|member|error
id|__u16
id|error
suffix:semicolon
r_union
(brace
r_struct
(brace
DECL|member|fmt
id|__u16
id|fmt
suffix:semicolon
multiline_comment|/* format kind                  */
DECL|member|hdrbyte
id|__u8
id|hdrbyte
suffix:semicolon
multiline_comment|/* fmt byte for hdr (0=default) */
DECL|member|interleave
id|__u8
id|interleave
suffix:semicolon
multiline_comment|/* interleave (0 = default)     */
DECL|member|databuf
id|caddr_t
id|databuf
suffix:semicolon
multiline_comment|/* sector data buff (0=default  */
DECL|member|tagbuf
id|caddr_t
id|tagbuf
suffix:semicolon
multiline_comment|/* tag data buffer (0=default)  */
DECL|member|f
)brace
id|f
suffix:semicolon
DECL|member|status
r_struct
id|swim_drvstatus
id|status
suffix:semicolon
DECL|member|p
)brace
id|p
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|swimcmd_fmtverify
r_struct
id|swimcmd_fmtverify
(brace
DECL|member|code
id|__u8
id|code
suffix:semicolon
multiline_comment|/* CMD_FORMAT_VERIFY */
DECL|member|drive_num
id|__u8
id|drive_num
suffix:semicolon
DECL|member|error
id|__u16
id|error
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|swimcmd_rw
r_struct
id|swimcmd_rw
(brace
DECL|member|code
id|__u8
id|code
suffix:semicolon
multiline_comment|/* CMD_READ, CMD_WRITE or CMD_READ_VERIFY */
DECL|member|drive_num
id|__u8
id|drive_num
suffix:semicolon
DECL|member|error
id|__u16
id|error
suffix:semicolon
DECL|member|buffer
id|caddr_t
id|buffer
suffix:semicolon
multiline_comment|/* R/W buffer address */
DECL|member|first_block
id|__u32
id|first_block
suffix:semicolon
multiline_comment|/* Starting block     */
DECL|member|num_blocks
id|__u32
id|num_blocks
suffix:semicolon
multiline_comment|/* Number of blocks   */
DECL|member|tag
id|__u8
id|tag
(braket
l_int|12
)braket
suffix:semicolon
multiline_comment|/* tag data           */
)brace
suffix:semicolon
DECL|struct|swimcmd_cachectl
r_struct
id|swimcmd_cachectl
(brace
DECL|member|code
id|__u8
id|code
suffix:semicolon
multiline_comment|/* CMD_CACHE_CTRL */
DECL|member|unused
id|__u8
id|unused
suffix:semicolon
DECL|member|error
id|__u16
id|error
suffix:semicolon
DECL|member|enable
id|__u8
id|enable
suffix:semicolon
multiline_comment|/* Nonzero to enable cache                */
DECL|member|install
id|__u8
id|install
suffix:semicolon
multiline_comment|/* +1 = install, -1 = remove, 0 = neither */
)brace
suffix:semicolon
DECL|struct|swimcmd_tagbufctl
r_struct
id|swimcmd_tagbufctl
(brace
DECL|member|code
id|__u8
id|code
suffix:semicolon
multiline_comment|/* CMD_TAGBUFF_CTRL */
DECL|member|unused
id|__u8
id|unused
suffix:semicolon
DECL|member|error
id|__u16
id|error
suffix:semicolon
DECL|member|buf
id|caddr_t
id|buf
suffix:semicolon
multiline_comment|/* buffer address or 0 to disable */
)brace
suffix:semicolon
DECL|struct|swimcmd_geticon
r_struct
id|swimcmd_geticon
(brace
DECL|member|code
id|__u8
id|code
suffix:semicolon
multiline_comment|/* CMD_GET_ICON */
DECL|member|drive_num
id|__u8
id|drive_num
suffix:semicolon
DECL|member|error
id|__u16
id|error
suffix:semicolon
DECL|member|buffer
id|caddr_t
id|buffer
suffix:semicolon
multiline_comment|/* Nuffer address */
DECL|member|kind
id|__u16
id|kind
suffix:semicolon
multiline_comment|/* 0 = media icon, 1 = drive icon */
DECL|member|unused
id|__u16
id|unused
suffix:semicolon
DECL|member|max_bytes
id|__u16
id|max_bytes
suffix:semicolon
multiline_comment|/* maximum  byte count */
)brace
suffix:semicolon
multiline_comment|/* Messages from the SWIM IOP to the host CPU: */
DECL|struct|swimmsg_status
r_struct
id|swimmsg_status
(brace
DECL|member|code
id|__u8
id|code
suffix:semicolon
multiline_comment|/* 1 = insert, 2 = eject, 3 = status changed */
DECL|member|drive_num
id|__u8
id|drive_num
suffix:semicolon
DECL|member|error
id|__u16
id|error
suffix:semicolon
DECL|member|status
r_struct
id|swim_drvstatus
id|status
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* __ASSEMBLY__ */
eof
