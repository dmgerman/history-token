multiline_comment|/*&n; * -- &lt;linux/cdrom.h&gt;&n; * General header file for linux CD-ROM drivers &n; * Copyright (C) 1992         David Giller, rafetmad@oxy.edu&n; *               1994, 1995   Eberhard Moenkeberg, emoenke@gwdg.de&n; *               1996         David van Leeuwen, david@tm.tno.nl&n; *               1997, 1998   Erik Andersen, andersee@debian.org&n; *               1998-2000    Jens Axboe, axboe@suse.de&n; */
macro_line|#ifndef&t;_LINUX_CDROM_H
DECL|macro|_LINUX_CDROM_H
mdefine_line|#define&t;_LINUX_CDROM_H
macro_line|#include &lt;asm/byteorder.h&gt;
multiline_comment|/*******************************************************&n; * As of Linux 2.1.x, all Linux CD-ROM application programs will use this &n; * (and only this) include file.  It is my hope to provide Linux with&n; * a uniform interface between software accessing CD-ROMs and the various &n; * device drivers that actually talk to the drives.  There may still be&n; * 23 different kinds of strange CD-ROM drives, but at least there will &n; * now be one, and only one, Linux CD-ROM interface.&n; *&n; * Additionally, as of Linux 2.1.x, all Linux application programs &n; * should use the O_NONBLOCK option when opening a CD-ROM device &n; * for subsequent ioctl commands.  This allows for neat system errors &n; * like &quot;No medium found&quot; or &quot;Wrong medium type&quot; upon attempting to &n; * mount or play an empty slot, mount an audio disc, or play a data disc.&n; * Generally, changing an application program to support O_NONBLOCK&n; * is as easy as the following:&n; *       -    drive = open(&quot;/dev/cdrom&quot;, O_RDONLY);&n; *       +    drive = open(&quot;/dev/cdrom&quot;, O_RDONLY | O_NONBLOCK);&n; * It is worth the small change.&n; *&n; *  Patches for many common CD programs (provided by David A. van Leeuwen)&n; *  can be found at:  ftp://ftp.gwdg.de/pub/linux/cdrom/drivers/cm206/&n; * &n; *******************************************************/
multiline_comment|/* When a driver supports a certain function, but the cdrom drive we are &n; * using doesn&squot;t, we will return the error EDRIVE_CANT_DO_THIS.  We will &n; * borrow the &quot;Operation not supported&quot; error from the network folks to &n; * accomplish this.  Maybe someday we will get a more targeted error code, &n; * but this will do for now... */
DECL|macro|EDRIVE_CANT_DO_THIS
mdefine_line|#define EDRIVE_CANT_DO_THIS  EOPNOTSUPP
multiline_comment|/*******************************************************&n; * The CD-ROM IOCTL commands  -- these should be supported by &n; * all the various cdrom drivers.  For the CD-ROM ioctls, we &n; * will commandeer byte 0x53, or &squot;S&squot;.&n; *******************************************************/
DECL|macro|CDROMPAUSE
mdefine_line|#define CDROMPAUSE&t;&t;0x5301 /* Pause Audio Operation */ 
DECL|macro|CDROMRESUME
mdefine_line|#define CDROMRESUME&t;&t;0x5302 /* Resume paused Audio Operation */
DECL|macro|CDROMPLAYMSF
mdefine_line|#define CDROMPLAYMSF&t;&t;0x5303 /* Play Audio MSF (struct cdrom_msf) */
DECL|macro|CDROMPLAYTRKIND
mdefine_line|#define CDROMPLAYTRKIND&t;&t;0x5304 /* Play Audio Track/index &n;                                           (struct cdrom_ti) */
DECL|macro|CDROMREADTOCHDR
mdefine_line|#define CDROMREADTOCHDR&t;&t;0x5305 /* Read TOC header &n;                                           (struct cdrom_tochdr) */
DECL|macro|CDROMREADTOCENTRY
mdefine_line|#define CDROMREADTOCENTRY&t;0x5306 /* Read TOC entry &n;                                           (struct cdrom_tocentry) */
DECL|macro|CDROMSTOP
mdefine_line|#define CDROMSTOP&t;&t;0x5307 /* Stop the cdrom drive */
DECL|macro|CDROMSTART
mdefine_line|#define CDROMSTART&t;&t;0x5308 /* Start the cdrom drive */
DECL|macro|CDROMEJECT
mdefine_line|#define CDROMEJECT&t;&t;0x5309 /* Ejects the cdrom media */
DECL|macro|CDROMVOLCTRL
mdefine_line|#define CDROMVOLCTRL&t;&t;0x530a /* Control output volume &n;                                           (struct cdrom_volctrl) */
DECL|macro|CDROMSUBCHNL
mdefine_line|#define CDROMSUBCHNL&t;&t;0x530b /* Read subchannel data &n;                                           (struct cdrom_subchnl) */
DECL|macro|CDROMREADMODE2
mdefine_line|#define CDROMREADMODE2&t;&t;0x530c /* Read CDROM mode 2 data (2336 Bytes) &n;                                           (struct cdrom_read) */
DECL|macro|CDROMREADMODE1
mdefine_line|#define CDROMREADMODE1&t;&t;0x530d /* Read CDROM mode 1 data (2048 Bytes)&n;                                           (struct cdrom_read) */
DECL|macro|CDROMREADAUDIO
mdefine_line|#define CDROMREADAUDIO&t;&t;0x530e /* (struct cdrom_read_audio) */
DECL|macro|CDROMEJECT_SW
mdefine_line|#define CDROMEJECT_SW&t;&t;0x530f /* enable(1)/disable(0) auto-ejecting */
DECL|macro|CDROMMULTISESSION
mdefine_line|#define CDROMMULTISESSION&t;0x5310 /* Obtain the start-of-last-session &n;                                           address of multi session disks &n;                                           (struct cdrom_multisession) */
DECL|macro|CDROM_GET_MCN
mdefine_line|#define CDROM_GET_MCN&t;&t;0x5311 /* Obtain the &quot;Universal Product Code&quot; &n;                                           if available (struct cdrom_mcn) */
DECL|macro|CDROM_GET_UPC
mdefine_line|#define CDROM_GET_UPC&t;&t;CDROM_GET_MCN  /* This one is depricated, &n;                                          but here anyway for compatability */
DECL|macro|CDROMRESET
mdefine_line|#define CDROMRESET&t;&t;0x5312 /* hard-reset the drive */
DECL|macro|CDROMVOLREAD
mdefine_line|#define CDROMVOLREAD&t;&t;0x5313 /* Get the drive&squot;s volume setting &n;                                          (struct cdrom_volctrl) */
DECL|macro|CDROMREADRAW
mdefine_line|#define CDROMREADRAW&t;&t;0x5314&t;/* read data in raw mode (2352 Bytes)&n;                                           (struct cdrom_read) */
multiline_comment|/* &n; * These ioctls are used only used in aztcd.c and optcd.c&n; */
DECL|macro|CDROMREADCOOKED
mdefine_line|#define CDROMREADCOOKED&t;&t;0x5315&t;/* read data in cooked mode */
DECL|macro|CDROMSEEK
mdefine_line|#define CDROMSEEK&t;&t;0x5316  /* seek msf address */
multiline_comment|/*&n; * This ioctl is only used by the scsi-cd driver.  &n;   It is for playing audio in logical block addressing mode.&n; */
DECL|macro|CDROMPLAYBLK
mdefine_line|#define CDROMPLAYBLK&t;&t;0x5317&t;/* (struct cdrom_blk) */
multiline_comment|/* &n; * These ioctls are only used in optcd.c&n; */
DECL|macro|CDROMREADALL
mdefine_line|#define CDROMREADALL&t;&t;0x5318&t;/* read all 2646 bytes */
multiline_comment|/* &n; * These ioctls are (now) only in ide-cd.c for controlling &n; * drive spindown time.  They should be implemented in the&n; * Uniform driver, via generic packet commands, GPCMD_MODE_SELECT_10,&n; * GPCMD_MODE_SENSE_10 and the GPMODE_POWER_PAGE...&n; *  -Erik&n; */
DECL|macro|CDROMGETSPINDOWN
mdefine_line|#define CDROMGETSPINDOWN        0x531d
DECL|macro|CDROMSETSPINDOWN
mdefine_line|#define CDROMSETSPINDOWN        0x531e
multiline_comment|/* &n; * These ioctls are implemented through the uniform CD-ROM driver&n; * They _will_ be adopted by all CD-ROM drivers, when all the CD-ROM&n; * drivers are eventually ported to the uniform CD-ROM driver interface.&n; */
DECL|macro|CDROMCLOSETRAY
mdefine_line|#define CDROMCLOSETRAY&t;&t;0x5319&t;/* pendant of CDROMEJECT */
DECL|macro|CDROM_SET_OPTIONS
mdefine_line|#define CDROM_SET_OPTIONS&t;0x5320  /* Set behavior options */
DECL|macro|CDROM_CLEAR_OPTIONS
mdefine_line|#define CDROM_CLEAR_OPTIONS&t;0x5321  /* Clear behavior options */
DECL|macro|CDROM_SELECT_SPEED
mdefine_line|#define CDROM_SELECT_SPEED&t;0x5322  /* Set the CD-ROM speed */
DECL|macro|CDROM_SELECT_DISC
mdefine_line|#define CDROM_SELECT_DISC&t;0x5323  /* Select disc (for juke-boxes) */
DECL|macro|CDROM_MEDIA_CHANGED
mdefine_line|#define CDROM_MEDIA_CHANGED&t;0x5325  /* Check is media changed  */
DECL|macro|CDROM_DRIVE_STATUS
mdefine_line|#define CDROM_DRIVE_STATUS&t;0x5326  /* Get tray position, etc. */
DECL|macro|CDROM_DISC_STATUS
mdefine_line|#define CDROM_DISC_STATUS&t;0x5327  /* Get disc type, etc. */
DECL|macro|CDROM_CHANGER_NSLOTS
mdefine_line|#define CDROM_CHANGER_NSLOTS    0x5328  /* Get number of slots */
DECL|macro|CDROM_LOCKDOOR
mdefine_line|#define CDROM_LOCKDOOR&t;&t;0x5329  /* lock or unlock door */
DECL|macro|CDROM_DEBUG
mdefine_line|#define CDROM_DEBUG&t;&t;0x5330&t;/* Turn debug messages on/off */
DECL|macro|CDROM_GET_CAPABILITY
mdefine_line|#define CDROM_GET_CAPABILITY&t;0x5331&t;/* get capabilities */
multiline_comment|/* Note that scsi/scsi_ioctl.h also uses 0x5382 - 0x5386.&n; * Future CDROM ioctls should be kept below 0x537F&n; */
multiline_comment|/* This ioctl is only used by sbpcd at the moment */
DECL|macro|CDROMAUDIOBUFSIZ
mdefine_line|#define CDROMAUDIOBUFSIZ        0x5382&t;/* set the audio buffer size */
multiline_comment|/* conflict with SCSI_IOCTL_GET_IDLUN */
multiline_comment|/* DVD-ROM Specific ioctls */
DECL|macro|DVD_READ_STRUCT
mdefine_line|#define DVD_READ_STRUCT&t;&t;0x5390  /* Read structure */
DECL|macro|DVD_WRITE_STRUCT
mdefine_line|#define DVD_WRITE_STRUCT&t;0x5391  /* Write structure */
DECL|macro|DVD_AUTH
mdefine_line|#define DVD_AUTH&t;&t;0x5392  /* Authentication */
DECL|macro|CDROM_SEND_PACKET
mdefine_line|#define CDROM_SEND_PACKET&t;0x5393&t;/* send a packet to the drive */
DECL|macro|CDROM_NEXT_WRITABLE
mdefine_line|#define CDROM_NEXT_WRITABLE&t;0x5394&t;/* get next writable block */
DECL|macro|CDROM_LAST_WRITTEN
mdefine_line|#define CDROM_LAST_WRITTEN&t;0x5395&t;/* get last block written on disc */
multiline_comment|/*******************************************************&n; * CDROM IOCTL structures&n; *******************************************************/
multiline_comment|/* Address in MSF format */
DECL|struct|cdrom_msf0
r_struct
id|cdrom_msf0
(brace
DECL|member|minute
id|__u8
id|minute
suffix:semicolon
DECL|member|second
id|__u8
id|second
suffix:semicolon
DECL|member|frame
id|__u8
id|frame
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Address in either MSF or logical format */
DECL|union|cdrom_addr
r_union
id|cdrom_addr
(brace
DECL|member|msf
r_struct
id|cdrom_msf0
id|msf
suffix:semicolon
DECL|member|lba
r_int
id|lba
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* This struct is used by the CDROMPLAYMSF ioctl */
DECL|struct|cdrom_msf
r_struct
id|cdrom_msf
(brace
DECL|member|cdmsf_min0
id|__u8
id|cdmsf_min0
suffix:semicolon
multiline_comment|/* start minute */
DECL|member|cdmsf_sec0
id|__u8
id|cdmsf_sec0
suffix:semicolon
multiline_comment|/* start second */
DECL|member|cdmsf_frame0
id|__u8
id|cdmsf_frame0
suffix:semicolon
multiline_comment|/* start frame */
DECL|member|cdmsf_min1
id|__u8
id|cdmsf_min1
suffix:semicolon
multiline_comment|/* end minute */
DECL|member|cdmsf_sec1
id|__u8
id|cdmsf_sec1
suffix:semicolon
multiline_comment|/* end second */
DECL|member|cdmsf_frame1
id|__u8
id|cdmsf_frame1
suffix:semicolon
multiline_comment|/* end frame */
)brace
suffix:semicolon
multiline_comment|/* This struct is used by the CDROMPLAYTRKIND ioctl */
DECL|struct|cdrom_ti
r_struct
id|cdrom_ti
(brace
DECL|member|cdti_trk0
id|__u8
id|cdti_trk0
suffix:semicolon
multiline_comment|/* start track */
DECL|member|cdti_ind0
id|__u8
id|cdti_ind0
suffix:semicolon
multiline_comment|/* start index */
DECL|member|cdti_trk1
id|__u8
id|cdti_trk1
suffix:semicolon
multiline_comment|/* end track */
DECL|member|cdti_ind1
id|__u8
id|cdti_ind1
suffix:semicolon
multiline_comment|/* end index */
)brace
suffix:semicolon
multiline_comment|/* This struct is used by the CDROMREADTOCHDR ioctl */
DECL|struct|cdrom_tochdr
r_struct
id|cdrom_tochdr
(brace
DECL|member|cdth_trk0
id|__u8
id|cdth_trk0
suffix:semicolon
multiline_comment|/* start track */
DECL|member|cdth_trk1
id|__u8
id|cdth_trk1
suffix:semicolon
multiline_comment|/* end track */
)brace
suffix:semicolon
multiline_comment|/* This struct is used by the CDROMVOLCTRL and CDROMVOLREAD ioctls */
DECL|struct|cdrom_volctrl
r_struct
id|cdrom_volctrl
(brace
DECL|member|channel0
id|__u8
id|channel0
suffix:semicolon
DECL|member|channel1
id|__u8
id|channel1
suffix:semicolon
DECL|member|channel2
id|__u8
id|channel2
suffix:semicolon
DECL|member|channel3
id|__u8
id|channel3
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* This struct is used by the CDROMSUBCHNL ioctl */
DECL|struct|cdrom_subchnl
r_struct
id|cdrom_subchnl
(brace
DECL|member|cdsc_format
id|__u8
id|cdsc_format
suffix:semicolon
DECL|member|cdsc_audiostatus
id|__u8
id|cdsc_audiostatus
suffix:semicolon
DECL|member|cdsc_adr
id|__u8
id|cdsc_adr
suffix:colon
l_int|4
suffix:semicolon
DECL|member|cdsc_ctrl
id|__u8
id|cdsc_ctrl
suffix:colon
l_int|4
suffix:semicolon
DECL|member|cdsc_trk
id|__u8
id|cdsc_trk
suffix:semicolon
DECL|member|cdsc_ind
id|__u8
id|cdsc_ind
suffix:semicolon
DECL|member|cdsc_absaddr
r_union
id|cdrom_addr
id|cdsc_absaddr
suffix:semicolon
DECL|member|cdsc_reladdr
r_union
id|cdrom_addr
id|cdsc_reladdr
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* This struct is used by the CDROMREADTOCENTRY ioctl */
DECL|struct|cdrom_tocentry
r_struct
id|cdrom_tocentry
(brace
DECL|member|cdte_track
id|__u8
id|cdte_track
suffix:semicolon
DECL|member|cdte_adr
id|__u8
id|cdte_adr
suffix:colon
l_int|4
suffix:semicolon
DECL|member|cdte_ctrl
id|__u8
id|cdte_ctrl
suffix:colon
l_int|4
suffix:semicolon
DECL|member|cdte_format
id|__u8
id|cdte_format
suffix:semicolon
DECL|member|cdte_addr
r_union
id|cdrom_addr
id|cdte_addr
suffix:semicolon
DECL|member|cdte_datamode
id|__u8
id|cdte_datamode
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* This struct is used by the CDROMREADMODE1, and CDROMREADMODE2 ioctls */
DECL|struct|cdrom_read
r_struct
id|cdrom_read
(brace
DECL|member|cdread_lba
r_int
id|cdread_lba
suffix:semicolon
DECL|member|cdread_bufaddr
r_char
op_star
id|cdread_bufaddr
suffix:semicolon
DECL|member|cdread_buflen
r_int
id|cdread_buflen
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* This struct is used by the CDROMREADAUDIO ioctl */
DECL|struct|cdrom_read_audio
r_struct
id|cdrom_read_audio
(brace
DECL|member|addr
r_union
id|cdrom_addr
id|addr
suffix:semicolon
multiline_comment|/* frame address */
DECL|member|addr_format
id|__u8
id|addr_format
suffix:semicolon
multiline_comment|/* CDROM_LBA or CDROM_MSF */
DECL|member|nframes
r_int
id|nframes
suffix:semicolon
multiline_comment|/* number of 2352-byte-frames to read at once */
DECL|member|buf
id|__u8
op_star
id|buf
suffix:semicolon
multiline_comment|/* frame buffer (size: nframes*2352 bytes) */
)brace
suffix:semicolon
multiline_comment|/* This struct is used with the CDROMMULTISESSION ioctl */
DECL|struct|cdrom_multisession
r_struct
id|cdrom_multisession
(brace
DECL|member|addr
r_union
id|cdrom_addr
id|addr
suffix:semicolon
multiline_comment|/* frame address: start-of-last-session &n;&t;                           (not the new &quot;frame 16&quot;!).  Only valid&n;&t;                           if the &quot;xa_flag&quot; is true. */
DECL|member|xa_flag
id|__u8
id|xa_flag
suffix:semicolon
multiline_comment|/* 1: &quot;is XA disk&quot; */
DECL|member|addr_format
id|__u8
id|addr_format
suffix:semicolon
multiline_comment|/* CDROM_LBA or CDROM_MSF */
)brace
suffix:semicolon
multiline_comment|/* This struct is used with the CDROM_GET_MCN ioctl.  &n; * Very few audio discs actually have Universal Product Code information, &n; * which should just be the Medium Catalog Number on the box.  Also note &n; * that the way the codeis written on CD is _not_ uniform across all discs!&n; */
DECL|struct|cdrom_mcn
r_struct
id|cdrom_mcn
(brace
DECL|member|medium_catalog_number
id|__u8
id|medium_catalog_number
(braket
l_int|14
)braket
suffix:semicolon
multiline_comment|/* 13 ASCII digits, null-terminated */
)brace
suffix:semicolon
multiline_comment|/* This is used by the CDROMPLAYBLK ioctl */
DECL|struct|cdrom_blk
r_struct
id|cdrom_blk
(brace
DECL|member|from
r_int
id|from
suffix:semicolon
DECL|member|len
r_int
r_int
id|len
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|CDROM_PACKET_SIZE
mdefine_line|#define CDROM_PACKET_SIZE&t;12
DECL|macro|CGC_DATA_UNKNOWN
mdefine_line|#define CGC_DATA_UNKNOWN&t;0
DECL|macro|CGC_DATA_WRITE
mdefine_line|#define CGC_DATA_WRITE&t;&t;1
DECL|macro|CGC_DATA_READ
mdefine_line|#define CGC_DATA_READ&t;&t;2
DECL|macro|CGC_DATA_NONE
mdefine_line|#define CGC_DATA_NONE&t;&t;3
multiline_comment|/* for CDROM_PACKET_COMMAND ioctl */
DECL|struct|cdrom_generic_command
r_struct
id|cdrom_generic_command
(brace
DECL|member|cmd
r_int
r_char
id|cmd
(braket
id|CDROM_PACKET_SIZE
)braket
suffix:semicolon
DECL|member|buffer
r_int
r_char
op_star
id|buffer
suffix:semicolon
DECL|member|buflen
r_int
r_int
id|buflen
suffix:semicolon
DECL|member|stat
r_int
id|stat
suffix:semicolon
DECL|member|sense
r_struct
id|request_sense
op_star
id|sense
suffix:semicolon
DECL|member|data_direction
r_int
r_char
id|data_direction
suffix:semicolon
DECL|member|quiet
r_int
id|quiet
suffix:semicolon
DECL|member|timeout
r_int
id|timeout
suffix:semicolon
DECL|member|reserved
r_void
op_star
id|reserved
(braket
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * A CD-ROM physical sector size is 2048, 2052, 2056, 2324, 2332, 2336, &n; * 2340, or 2352 bytes long.  &n;&n;*         Sector types of the standard CD-ROM data formats:&n; *&n; * format   sector type               user data size (bytes)&n; * -----------------------------------------------------------------------------&n; *   1     (Red Book)    CD-DA          2352    (CD_FRAMESIZE_RAW)&n; *   2     (Yellow Book) Mode1 Form1    2048    (CD_FRAMESIZE)&n; *   3     (Yellow Book) Mode1 Form2    2336    (CD_FRAMESIZE_RAW0)&n; *   4     (Green Book)  Mode2 Form1    2048    (CD_FRAMESIZE)&n; *   5     (Green Book)  Mode2 Form2    2328    (2324+4 spare bytes)&n; *&n; *&n; *       The layout of the standard CD-ROM data formats:&n; * -----------------------------------------------------------------------------&n; * - audio (red):                  | audio_sample_bytes |&n; *                                 |        2352        |&n; *&n; * - data (yellow, mode1):         | sync - head - data - EDC - zero - ECC |&n; *                                 |  12  -   4  - 2048 -  4  -   8  - 276 |&n; *&n; * - data (yellow, mode2):         | sync - head - data |&n; *                                 |  12  -   4  - 2336 |&n; *&n; * - XA data (green, mode2 form1): | sync - head - sub - data - EDC - ECC |&n; *                                 |  12  -   4  -  8  - 2048 -  4  - 276 |&n; *&n; * - XA data (green, mode2 form2): | sync - head - sub - data - Spare |&n; *                                 |  12  -   4  -  8  - 2324 -  4    |&n; *&n; */
multiline_comment|/* Some generally useful CD-ROM information -- mostly based on the above */
DECL|macro|CD_MINS
mdefine_line|#define CD_MINS              74 /* max. minutes per CD, not really a limit */
DECL|macro|CD_SECS
mdefine_line|#define CD_SECS              60 /* seconds per minute */
DECL|macro|CD_FRAMES
mdefine_line|#define CD_FRAMES            75 /* frames per second */
DECL|macro|CD_SYNC_SIZE
mdefine_line|#define CD_SYNC_SIZE         12 /* 12 sync bytes per raw data frame */
DECL|macro|CD_MSF_OFFSET
mdefine_line|#define CD_MSF_OFFSET       150 /* MSF numbering offset of first frame */
DECL|macro|CD_CHUNK_SIZE
mdefine_line|#define CD_CHUNK_SIZE        24 /* lowest-level &quot;data bytes piece&quot; */
DECL|macro|CD_NUM_OF_CHUNKS
mdefine_line|#define CD_NUM_OF_CHUNKS     98 /* chunks per frame */
DECL|macro|CD_FRAMESIZE_SUB
mdefine_line|#define CD_FRAMESIZE_SUB     96 /* subchannel data &quot;frame&quot; size */
DECL|macro|CD_HEAD_SIZE
mdefine_line|#define CD_HEAD_SIZE          4 /* header (address) bytes per raw data frame */
DECL|macro|CD_SUBHEAD_SIZE
mdefine_line|#define CD_SUBHEAD_SIZE       8 /* subheader bytes per raw XA data frame */
DECL|macro|CD_EDC_SIZE
mdefine_line|#define CD_EDC_SIZE           4 /* bytes EDC per most raw data frame types */
DECL|macro|CD_ZERO_SIZE
mdefine_line|#define CD_ZERO_SIZE          8 /* bytes zero per yellow book mode 1 frame */
DECL|macro|CD_ECC_SIZE
mdefine_line|#define CD_ECC_SIZE         276 /* bytes ECC per most raw data frame types */
DECL|macro|CD_FRAMESIZE
mdefine_line|#define CD_FRAMESIZE       2048 /* bytes per frame, &quot;cooked&quot; mode */
DECL|macro|CD_FRAMESIZE_RAW
mdefine_line|#define CD_FRAMESIZE_RAW   2352 /* bytes per frame, &quot;raw&quot; mode */
DECL|macro|CD_FRAMESIZE_RAWER
mdefine_line|#define CD_FRAMESIZE_RAWER 2646 /* The maximum possible returned bytes */ 
multiline_comment|/* most drives don&squot;t deliver everything: */
DECL|macro|CD_FRAMESIZE_RAW1
mdefine_line|#define CD_FRAMESIZE_RAW1 (CD_FRAMESIZE_RAW-CD_SYNC_SIZE) /*2340*/
DECL|macro|CD_FRAMESIZE_RAW0
mdefine_line|#define CD_FRAMESIZE_RAW0 (CD_FRAMESIZE_RAW-CD_SYNC_SIZE-CD_HEAD_SIZE) /*2336*/
DECL|macro|CD_XA_HEAD
mdefine_line|#define CD_XA_HEAD        (CD_HEAD_SIZE+CD_SUBHEAD_SIZE) /* &quot;before data&quot; part of raw XA frame */
DECL|macro|CD_XA_TAIL
mdefine_line|#define CD_XA_TAIL        (CD_EDC_SIZE+CD_ECC_SIZE) /* &quot;after data&quot; part of raw XA frame */
DECL|macro|CD_XA_SYNC_HEAD
mdefine_line|#define CD_XA_SYNC_HEAD   (CD_SYNC_SIZE+CD_XA_HEAD) /* sync bytes + header of XA frame */
multiline_comment|/* CD-ROM address types (cdrom_tocentry.cdte_format) */
DECL|macro|CDROM_LBA
mdefine_line|#define&t;CDROM_LBA 0x01 /* &quot;logical block&quot;: first frame is #0 */
DECL|macro|CDROM_MSF
mdefine_line|#define&t;CDROM_MSF 0x02 /* &quot;minute-second-frame&quot;: binary, not bcd here! */
multiline_comment|/* bit to tell whether track is data or audio (cdrom_tocentry.cdte_ctrl) */
DECL|macro|CDROM_DATA_TRACK
mdefine_line|#define&t;CDROM_DATA_TRACK&t;0x04
multiline_comment|/* The leadout track is always 0xAA, regardless of # of tracks on disc */
DECL|macro|CDROM_LEADOUT
mdefine_line|#define&t;CDROM_LEADOUT&t;&t;0xAA
multiline_comment|/* audio states (from SCSI-2, but seen with other drives, too) */
DECL|macro|CDROM_AUDIO_INVALID
mdefine_line|#define&t;CDROM_AUDIO_INVALID&t;0x00&t;/* audio status not supported */
DECL|macro|CDROM_AUDIO_PLAY
mdefine_line|#define&t;CDROM_AUDIO_PLAY&t;0x11&t;/* audio play operation in progress */
DECL|macro|CDROM_AUDIO_PAUSED
mdefine_line|#define&t;CDROM_AUDIO_PAUSED&t;0x12&t;/* audio play operation paused */
DECL|macro|CDROM_AUDIO_COMPLETED
mdefine_line|#define&t;CDROM_AUDIO_COMPLETED&t;0x13&t;/* audio play successfully completed */
DECL|macro|CDROM_AUDIO_ERROR
mdefine_line|#define&t;CDROM_AUDIO_ERROR&t;0x14&t;/* audio play stopped due to error */
DECL|macro|CDROM_AUDIO_NO_STATUS
mdefine_line|#define&t;CDROM_AUDIO_NO_STATUS&t;0x15&t;/* no current audio status to return */
multiline_comment|/* capability flags used with the uniform CD-ROM driver */
DECL|macro|CDC_CLOSE_TRAY
mdefine_line|#define CDC_CLOSE_TRAY&t;&t;0x1     /* caddy systems _can&squot;t_ close */
DECL|macro|CDC_OPEN_TRAY
mdefine_line|#define CDC_OPEN_TRAY&t;&t;0x2     /* but _can_ eject.  */
DECL|macro|CDC_LOCK
mdefine_line|#define CDC_LOCK&t;&t;0x4     /* disable manual eject */
DECL|macro|CDC_SELECT_SPEED
mdefine_line|#define CDC_SELECT_SPEED &t;0x8     /* programmable speed */
DECL|macro|CDC_SELECT_DISC
mdefine_line|#define CDC_SELECT_DISC&t;&t;0x10    /* select disc from juke-box */
DECL|macro|CDC_MULTI_SESSION
mdefine_line|#define CDC_MULTI_SESSION &t;0x20    /* read sessions&gt;1 */
DECL|macro|CDC_MCN
mdefine_line|#define CDC_MCN&t;&t;&t;0x40    /* Medium Catalog Number */
DECL|macro|CDC_MEDIA_CHANGED
mdefine_line|#define CDC_MEDIA_CHANGED &t;0x80    /* media changed */
DECL|macro|CDC_PLAY_AUDIO
mdefine_line|#define CDC_PLAY_AUDIO&t;&t;0x100   /* audio functions */
DECL|macro|CDC_RESET
mdefine_line|#define CDC_RESET               0x200   /* hard reset device */
DECL|macro|CDC_IOCTLS
mdefine_line|#define CDC_IOCTLS              0x400   /* driver has non-standard ioctls */
DECL|macro|CDC_DRIVE_STATUS
mdefine_line|#define CDC_DRIVE_STATUS        0x800   /* driver implements drive status */
DECL|macro|CDC_GENERIC_PACKET
mdefine_line|#define CDC_GENERIC_PACKET&t;0x1000&t;/* driver implements generic packets */
DECL|macro|CDC_CD_R
mdefine_line|#define CDC_CD_R&t;&t;0x2000&t;/* drive is a CD-R */
DECL|macro|CDC_CD_RW
mdefine_line|#define CDC_CD_RW&t;&t;0x4000&t;/* drive is a CD-RW */
DECL|macro|CDC_DVD
mdefine_line|#define CDC_DVD&t;&t;&t;0x8000&t;/* drive is a DVD */
DECL|macro|CDC_DVD_R
mdefine_line|#define CDC_DVD_R&t;&t;0x10000&t;/* drive can write DVD-R */
DECL|macro|CDC_DVD_RAM
mdefine_line|#define CDC_DVD_RAM&t;&t;0x20000&t;/* drive can write DVD-RAM */
multiline_comment|/* drive status possibilities returned by CDROM_DRIVE_STATUS ioctl */
DECL|macro|CDS_NO_INFO
mdefine_line|#define CDS_NO_INFO&t;&t;0&t;/* if not implemented */
DECL|macro|CDS_NO_DISC
mdefine_line|#define CDS_NO_DISC&t;&t;1
DECL|macro|CDS_TRAY_OPEN
mdefine_line|#define CDS_TRAY_OPEN&t;&t;2
DECL|macro|CDS_DRIVE_NOT_READY
mdefine_line|#define CDS_DRIVE_NOT_READY&t;3
DECL|macro|CDS_DISC_OK
mdefine_line|#define CDS_DISC_OK&t;&t;4
multiline_comment|/* return values for the CDROM_DISC_STATUS ioctl */
multiline_comment|/* can also return CDS_NO_[INFO|DISC], from above */
DECL|macro|CDS_AUDIO
mdefine_line|#define CDS_AUDIO&t;&t;100
DECL|macro|CDS_DATA_1
mdefine_line|#define CDS_DATA_1&t;&t;101
DECL|macro|CDS_DATA_2
mdefine_line|#define CDS_DATA_2&t;&t;102
DECL|macro|CDS_XA_2_1
mdefine_line|#define CDS_XA_2_1&t;&t;103
DECL|macro|CDS_XA_2_2
mdefine_line|#define CDS_XA_2_2&t;&t;104
DECL|macro|CDS_MIXED
mdefine_line|#define CDS_MIXED&t;&t;105
multiline_comment|/* User-configurable behavior options for the uniform CD-ROM driver */
DECL|macro|CDO_AUTO_CLOSE
mdefine_line|#define CDO_AUTO_CLOSE&t;&t;0x1     /* close tray on first open() */
DECL|macro|CDO_AUTO_EJECT
mdefine_line|#define CDO_AUTO_EJECT&t;&t;0x2     /* open tray on last release() */
DECL|macro|CDO_USE_FFLAGS
mdefine_line|#define CDO_USE_FFLAGS&t;&t;0x4     /* use O_NONBLOCK information on open */
DECL|macro|CDO_LOCK
mdefine_line|#define CDO_LOCK&t;&t;0x8     /* lock tray on open files */
DECL|macro|CDO_CHECK_TYPE
mdefine_line|#define CDO_CHECK_TYPE&t;&t;0x10    /* check type on open for data */
multiline_comment|/* Special codes used when specifying changer slots. */
DECL|macro|CDSL_NONE
mdefine_line|#define CDSL_NONE       &t;((int) (~0U&gt;&gt;1)-1)
DECL|macro|CDSL_CURRENT
mdefine_line|#define CDSL_CURRENT    &t;((int) (~0U&gt;&gt;1))
multiline_comment|/* For partition based multisession access. IDE can handle 64 partitions&n; * per drive - SCSI CD-ROM&squot;s use minors to differentiate between the&n; * various drives, so we can&squot;t do multisessions the same way there.&n; * Use the -o session=x option to mount on them.&n; */
DECL|macro|CD_PART_MAX
mdefine_line|#define CD_PART_MAX&t;&t;64
DECL|macro|CD_PART_MASK
mdefine_line|#define CD_PART_MASK&t;&t;(CD_PART_MAX - 1)
multiline_comment|/*********************************************************************&n; * Generic Packet commands, MMC commands, and such&n; *********************************************************************/
multiline_comment|/* The generic packet command opcodes for CD/DVD Logical Units,&n; * From Table 57 of the SFF8090 Ver. 3 (Mt. Fuji) draft standard. */
DECL|macro|GPCMD_BLANK
mdefine_line|#define GPCMD_BLANK&t;&t;&t;    0xa1
DECL|macro|GPCMD_CLOSE_TRACK
mdefine_line|#define GPCMD_CLOSE_TRACK&t;&t;    0x5b
DECL|macro|GPCMD_FLUSH_CACHE
mdefine_line|#define GPCMD_FLUSH_CACHE&t;&t;    0x35
DECL|macro|GPCMD_FORMAT_UNIT
mdefine_line|#define GPCMD_FORMAT_UNIT&t;&t;    0x04
DECL|macro|GPCMD_GET_CONFIGURATION
mdefine_line|#define GPCMD_GET_CONFIGURATION&t;&t;    0x46
DECL|macro|GPCMD_GET_EVENT_STATUS_NOTIFICATION
mdefine_line|#define GPCMD_GET_EVENT_STATUS_NOTIFICATION 0x4a
DECL|macro|GPCMD_GET_PERFORMANCE
mdefine_line|#define GPCMD_GET_PERFORMANCE&t;&t;    0xac
DECL|macro|GPCMD_INQUIRY
mdefine_line|#define GPCMD_INQUIRY&t;&t;&t;    0x12
DECL|macro|GPCMD_LOAD_UNLOAD
mdefine_line|#define GPCMD_LOAD_UNLOAD&t;&t;    0xa6
DECL|macro|GPCMD_MECHANISM_STATUS
mdefine_line|#define GPCMD_MECHANISM_STATUS&t;&t;    0xbd
DECL|macro|GPCMD_MODE_SELECT_10
mdefine_line|#define GPCMD_MODE_SELECT_10&t;&t;    0x55
DECL|macro|GPCMD_MODE_SENSE_10
mdefine_line|#define GPCMD_MODE_SENSE_10&t;&t;    0x5a
DECL|macro|GPCMD_PAUSE_RESUME
mdefine_line|#define GPCMD_PAUSE_RESUME&t;&t;    0x4b
DECL|macro|GPCMD_PLAY_AUDIO_10
mdefine_line|#define GPCMD_PLAY_AUDIO_10&t;&t;    0x45
DECL|macro|GPCMD_PLAY_AUDIO_MSF
mdefine_line|#define GPCMD_PLAY_AUDIO_MSF&t;&t;    0x47
DECL|macro|GPCMD_PLAY_AUDIO_TI
mdefine_line|#define GPCMD_PLAY_AUDIO_TI&t;&t;    0x48
DECL|macro|GPCMD_PLAY_CD
mdefine_line|#define GPCMD_PLAY_CD&t;&t;&t;    0xbc
DECL|macro|GPCMD_PREVENT_ALLOW_MEDIUM_REMOVAL
mdefine_line|#define GPCMD_PREVENT_ALLOW_MEDIUM_REMOVAL  0x1e
DECL|macro|GPCMD_READ_10
mdefine_line|#define GPCMD_READ_10&t;&t;&t;    0x28
DECL|macro|GPCMD_READ_12
mdefine_line|#define GPCMD_READ_12&t;&t;&t;    0xa8
DECL|macro|GPCMD_READ_CDVD_CAPACITY
mdefine_line|#define GPCMD_READ_CDVD_CAPACITY&t;    0x25
DECL|macro|GPCMD_READ_CD
mdefine_line|#define GPCMD_READ_CD&t;&t;&t;    0xbe
DECL|macro|GPCMD_READ_CD_MSF
mdefine_line|#define GPCMD_READ_CD_MSF&t;&t;    0xb9
DECL|macro|GPCMD_READ_DISC_INFO
mdefine_line|#define GPCMD_READ_DISC_INFO&t;&t;    0x51
DECL|macro|GPCMD_READ_DVD_STRUCTURE
mdefine_line|#define GPCMD_READ_DVD_STRUCTURE&t;    0xad
DECL|macro|GPCMD_READ_FORMAT_CAPACITIES
mdefine_line|#define GPCMD_READ_FORMAT_CAPACITIES&t;    0x23
DECL|macro|GPCMD_READ_HEADER
mdefine_line|#define GPCMD_READ_HEADER&t;&t;    0x44
DECL|macro|GPCMD_READ_TRACK_RZONE_INFO
mdefine_line|#define GPCMD_READ_TRACK_RZONE_INFO&t;    0x52
DECL|macro|GPCMD_READ_SUBCHANNEL
mdefine_line|#define GPCMD_READ_SUBCHANNEL&t;&t;    0x42
DECL|macro|GPCMD_READ_TOC_PMA_ATIP
mdefine_line|#define GPCMD_READ_TOC_PMA_ATIP&t;&t;    0x43
DECL|macro|GPCMD_REPAIR_RZONE_TRACK
mdefine_line|#define GPCMD_REPAIR_RZONE_TRACK&t;    0x58
DECL|macro|GPCMD_REPORT_KEY
mdefine_line|#define GPCMD_REPORT_KEY&t;&t;    0xa4
DECL|macro|GPCMD_REQUEST_SENSE
mdefine_line|#define GPCMD_REQUEST_SENSE&t;&t;    0x03
DECL|macro|GPCMD_RESERVE_RZONE_TRACK
mdefine_line|#define GPCMD_RESERVE_RZONE_TRACK&t;    0x53
DECL|macro|GPCMD_SCAN
mdefine_line|#define GPCMD_SCAN&t;&t;&t;    0xba
DECL|macro|GPCMD_SEEK
mdefine_line|#define GPCMD_SEEK&t;&t;&t;    0x2b
DECL|macro|GPCMD_SEND_DVD_STRUCTURE
mdefine_line|#define GPCMD_SEND_DVD_STRUCTURE&t;    0xad
DECL|macro|GPCMD_SEND_EVENT
mdefine_line|#define GPCMD_SEND_EVENT&t;&t;    0xa2
DECL|macro|GPCMD_SEND_KEY
mdefine_line|#define GPCMD_SEND_KEY&t;&t;&t;    0xa3
DECL|macro|GPCMD_SEND_OPC
mdefine_line|#define GPCMD_SEND_OPC&t;&t;&t;    0x54
DECL|macro|GPCMD_SET_READ_AHEAD
mdefine_line|#define GPCMD_SET_READ_AHEAD&t;&t;    0xa7
DECL|macro|GPCMD_SET_STREAMING
mdefine_line|#define GPCMD_SET_STREAMING&t;&t;    0xb6
DECL|macro|GPCMD_START_STOP_UNIT
mdefine_line|#define GPCMD_START_STOP_UNIT&t;&t;    0x1b
DECL|macro|GPCMD_STOP_PLAY_SCAN
mdefine_line|#define GPCMD_STOP_PLAY_SCAN&t;&t;    0x4e
DECL|macro|GPCMD_TEST_UNIT_READY
mdefine_line|#define GPCMD_TEST_UNIT_READY&t;&t;    0x00
DECL|macro|GPCMD_VERIFY_10
mdefine_line|#define GPCMD_VERIFY_10&t;&t;&t;    0x2f
DECL|macro|GPCMD_WRITE_10
mdefine_line|#define GPCMD_WRITE_10&t;&t;&t;    0x2a
DECL|macro|GPCMD_WRITE_AND_VERIFY_10
mdefine_line|#define GPCMD_WRITE_AND_VERIFY_10&t;    0x2e
multiline_comment|/* This is listed as optional in ATAPI 2.6, but is (curiously) &n; * missing from Mt. Fuji, Table 57.  It _is_ mentioned in Mt. Fuji&n; * Table 377 as an MMC command for SCSi devices though...  Most ATAPI&n; * drives support it. */
DECL|macro|GPCMD_SET_SPEED
mdefine_line|#define GPCMD_SET_SPEED&t;&t;&t;    0xbb
multiline_comment|/* This seems to be a SCSI specific CD-ROM opcode &n; * to play data at track/index */
DECL|macro|GPCMD_PLAYAUDIO_TI
mdefine_line|#define GPCMD_PLAYAUDIO_TI&t;&t;    0x48
multiline_comment|/*&n; * From MS Media Status Notification Support Specification. For&n; * older drives only.&n; */
DECL|macro|GPCMD_GET_MEDIA_STATUS
mdefine_line|#define GPCMD_GET_MEDIA_STATUS&t;&t;    0xda
multiline_comment|/* Mode page codes for mode sense/set */
DECL|macro|GPMODE_R_W_ERROR_PAGE
mdefine_line|#define GPMODE_R_W_ERROR_PAGE&t;&t;0x01
DECL|macro|GPMODE_WRITE_PARMS_PAGE
mdefine_line|#define GPMODE_WRITE_PARMS_PAGE&t;&t;0x05
DECL|macro|GPMODE_AUDIO_CTL_PAGE
mdefine_line|#define GPMODE_AUDIO_CTL_PAGE&t;&t;0x0e
DECL|macro|GPMODE_POWER_PAGE
mdefine_line|#define GPMODE_POWER_PAGE&t;&t;0x1a
DECL|macro|GPMODE_FAULT_FAIL_PAGE
mdefine_line|#define GPMODE_FAULT_FAIL_PAGE&t;&t;0x1c
DECL|macro|GPMODE_TO_PROTECT_PAGE
mdefine_line|#define GPMODE_TO_PROTECT_PAGE&t;&t;0x1d
DECL|macro|GPMODE_CAPABILITIES_PAGE
mdefine_line|#define GPMODE_CAPABILITIES_PAGE&t;0x2a
DECL|macro|GPMODE_ALL_PAGES
mdefine_line|#define GPMODE_ALL_PAGES&t;&t;0x3f
multiline_comment|/* Not in Mt. Fuji, but in ATAPI 2.6 -- depricated now in favor&n; * of MODE_SENSE_POWER_PAGE */
DECL|macro|GPMODE_CDROM_PAGE
mdefine_line|#define GPMODE_CDROM_PAGE&t;&t;0x0d
multiline_comment|/* DVD struct types */
DECL|macro|DVD_STRUCT_PHYSICAL
mdefine_line|#define DVD_STRUCT_PHYSICAL&t;0x00
DECL|macro|DVD_STRUCT_COPYRIGHT
mdefine_line|#define DVD_STRUCT_COPYRIGHT&t;0x01
DECL|macro|DVD_STRUCT_DISCKEY
mdefine_line|#define DVD_STRUCT_DISCKEY&t;0x02
DECL|macro|DVD_STRUCT_BCA
mdefine_line|#define DVD_STRUCT_BCA&t;&t;0x03
DECL|macro|DVD_STRUCT_MANUFACT
mdefine_line|#define DVD_STRUCT_MANUFACT&t;0x04
DECL|struct|dvd_layer
r_struct
id|dvd_layer
(brace
DECL|member|book_version
id|__u8
id|book_version
suffix:colon
l_int|4
suffix:semicolon
DECL|member|book_type
id|__u8
id|book_type
suffix:colon
l_int|4
suffix:semicolon
DECL|member|min_rate
id|__u8
id|min_rate
suffix:colon
l_int|4
suffix:semicolon
DECL|member|disc_size
id|__u8
id|disc_size
suffix:colon
l_int|4
suffix:semicolon
DECL|member|layer_type
id|__u8
id|layer_type
suffix:colon
l_int|4
suffix:semicolon
DECL|member|track_path
id|__u8
id|track_path
suffix:colon
l_int|1
suffix:semicolon
DECL|member|nlayers
id|__u8
id|nlayers
suffix:colon
l_int|2
suffix:semicolon
DECL|member|track_density
id|__u8
id|track_density
suffix:colon
l_int|4
suffix:semicolon
DECL|member|linear_density
id|__u8
id|linear_density
suffix:colon
l_int|4
suffix:semicolon
DECL|member|bca
id|__u8
id|bca
suffix:colon
l_int|1
suffix:semicolon
DECL|member|start_sector
id|__u32
id|start_sector
suffix:semicolon
DECL|member|end_sector
id|__u32
id|end_sector
suffix:semicolon
DECL|member|end_sector_l0
id|__u32
id|end_sector_l0
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|DVD_LAYERS
mdefine_line|#define DVD_LAYERS&t;4
DECL|struct|dvd_physical
r_struct
id|dvd_physical
(brace
DECL|member|type
id|__u8
id|type
suffix:semicolon
DECL|member|layer_num
id|__u8
id|layer_num
suffix:semicolon
DECL|member|layer
r_struct
id|dvd_layer
id|layer
(braket
id|DVD_LAYERS
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|dvd_copyright
r_struct
id|dvd_copyright
(brace
DECL|member|type
id|__u8
id|type
suffix:semicolon
DECL|member|layer_num
id|__u8
id|layer_num
suffix:semicolon
DECL|member|cpst
id|__u8
id|cpst
suffix:semicolon
DECL|member|rmi
id|__u8
id|rmi
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|dvd_disckey
r_struct
id|dvd_disckey
(brace
DECL|member|type
id|__u8
id|type
suffix:semicolon
DECL|member|agid
r_int
id|agid
suffix:colon
l_int|2
suffix:semicolon
DECL|member|value
id|__u8
id|value
(braket
l_int|2048
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|dvd_bca
r_struct
id|dvd_bca
(brace
DECL|member|type
id|__u8
id|type
suffix:semicolon
DECL|member|len
r_int
id|len
suffix:semicolon
DECL|member|value
id|__u8
id|value
(braket
l_int|188
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|dvd_manufact
r_struct
id|dvd_manufact
(brace
DECL|member|type
id|__u8
id|type
suffix:semicolon
DECL|member|layer_num
id|__u8
id|layer_num
suffix:semicolon
DECL|member|len
r_int
id|len
suffix:semicolon
DECL|member|value
id|__u8
id|value
(braket
l_int|2048
)braket
suffix:semicolon
)brace
suffix:semicolon
r_typedef
r_union
(brace
DECL|member|type
id|__u8
id|type
suffix:semicolon
DECL|member|physical
r_struct
id|dvd_physical
id|physical
suffix:semicolon
DECL|member|copyright
r_struct
id|dvd_copyright
id|copyright
suffix:semicolon
DECL|member|disckey
r_struct
id|dvd_disckey
id|disckey
suffix:semicolon
DECL|member|bca
r_struct
id|dvd_bca
id|bca
suffix:semicolon
DECL|member|manufact
r_struct
id|dvd_manufact
id|manufact
suffix:semicolon
DECL|typedef|dvd_struct
)brace
id|dvd_struct
suffix:semicolon
multiline_comment|/*&n; * DVD authentication ioctl&n; */
multiline_comment|/* Authentication states */
DECL|macro|DVD_LU_SEND_AGID
mdefine_line|#define DVD_LU_SEND_AGID&t;0
DECL|macro|DVD_HOST_SEND_CHALLENGE
mdefine_line|#define DVD_HOST_SEND_CHALLENGE&t;1
DECL|macro|DVD_LU_SEND_KEY1
mdefine_line|#define DVD_LU_SEND_KEY1&t;2
DECL|macro|DVD_LU_SEND_CHALLENGE
mdefine_line|#define DVD_LU_SEND_CHALLENGE&t;3
DECL|macro|DVD_HOST_SEND_KEY2
mdefine_line|#define DVD_HOST_SEND_KEY2&t;4
multiline_comment|/* Termination states */
DECL|macro|DVD_AUTH_ESTABLISHED
mdefine_line|#define DVD_AUTH_ESTABLISHED&t;5
DECL|macro|DVD_AUTH_FAILURE
mdefine_line|#define DVD_AUTH_FAILURE&t;6
multiline_comment|/* Other functions */
DECL|macro|DVD_LU_SEND_TITLE_KEY
mdefine_line|#define DVD_LU_SEND_TITLE_KEY&t;7
DECL|macro|DVD_LU_SEND_ASF
mdefine_line|#define DVD_LU_SEND_ASF&t;&t;8
DECL|macro|DVD_INVALIDATE_AGID
mdefine_line|#define DVD_INVALIDATE_AGID&t;9
DECL|macro|DVD_LU_SEND_RPC_STATE
mdefine_line|#define DVD_LU_SEND_RPC_STATE&t;10
DECL|macro|DVD_HOST_SEND_RPC_STATE
mdefine_line|#define DVD_HOST_SEND_RPC_STATE&t;11
multiline_comment|/* State data */
DECL|typedef|dvd_key
r_typedef
id|__u8
id|dvd_key
(braket
l_int|5
)braket
suffix:semicolon
multiline_comment|/* 40-bit value, MSB is first elem. */
DECL|typedef|dvd_challenge
r_typedef
id|__u8
id|dvd_challenge
(braket
l_int|10
)braket
suffix:semicolon
multiline_comment|/* 80-bit value, MSB is first elem. */
DECL|struct|dvd_lu_send_agid
r_struct
id|dvd_lu_send_agid
(brace
DECL|member|type
id|__u8
id|type
suffix:semicolon
DECL|member|agid
r_int
id|agid
suffix:colon
l_int|2
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|dvd_host_send_challenge
r_struct
id|dvd_host_send_challenge
(brace
DECL|member|type
id|__u8
id|type
suffix:semicolon
DECL|member|agid
r_int
id|agid
suffix:colon
l_int|2
suffix:semicolon
DECL|member|chal
id|dvd_challenge
id|chal
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|dvd_send_key
r_struct
id|dvd_send_key
(brace
DECL|member|type
id|__u8
id|type
suffix:semicolon
DECL|member|agid
r_int
id|agid
suffix:colon
l_int|2
suffix:semicolon
DECL|member|key
id|dvd_key
id|key
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|dvd_lu_send_challenge
r_struct
id|dvd_lu_send_challenge
(brace
DECL|member|type
id|__u8
id|type
suffix:semicolon
DECL|member|agid
r_int
id|agid
suffix:colon
l_int|2
suffix:semicolon
DECL|member|chal
id|dvd_challenge
id|chal
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|DVD_CPM_NO_COPYRIGHT
mdefine_line|#define DVD_CPM_NO_COPYRIGHT&t;0
DECL|macro|DVD_CPM_COPYRIGHTED
mdefine_line|#define DVD_CPM_COPYRIGHTED&t;1
DECL|macro|DVD_CP_SEC_NONE
mdefine_line|#define DVD_CP_SEC_NONE&t;&t;0
DECL|macro|DVD_CP_SEC_EXIST
mdefine_line|#define DVD_CP_SEC_EXIST&t;1
DECL|macro|DVD_CGMS_UNRESTRICTED
mdefine_line|#define DVD_CGMS_UNRESTRICTED&t;0
DECL|macro|DVD_CGMS_SINGLE
mdefine_line|#define DVD_CGMS_SINGLE&t;&t;2
DECL|macro|DVD_CGMS_RESTRICTED
mdefine_line|#define DVD_CGMS_RESTRICTED&t;3
DECL|struct|dvd_lu_send_title_key
r_struct
id|dvd_lu_send_title_key
(brace
DECL|member|type
id|__u8
id|type
suffix:semicolon
DECL|member|agid
r_int
id|agid
suffix:colon
l_int|2
suffix:semicolon
DECL|member|title_key
id|dvd_key
id|title_key
suffix:semicolon
DECL|member|lba
r_int
id|lba
suffix:semicolon
DECL|member|cpm
r_int
id|cpm
suffix:colon
l_int|1
suffix:semicolon
DECL|member|cp_sec
r_int
id|cp_sec
suffix:colon
l_int|1
suffix:semicolon
DECL|member|cgms
r_int
id|cgms
suffix:colon
l_int|2
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|dvd_lu_send_asf
r_struct
id|dvd_lu_send_asf
(brace
DECL|member|type
id|__u8
id|type
suffix:semicolon
DECL|member|agid
r_int
id|agid
suffix:colon
l_int|2
suffix:semicolon
DECL|member|asf
r_int
id|asf
suffix:colon
l_int|1
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|dvd_host_send_rpcstate
r_struct
id|dvd_host_send_rpcstate
(brace
DECL|member|type
id|__u8
id|type
suffix:semicolon
DECL|member|pdrc
id|__u8
id|pdrc
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|dvd_lu_send_rpcstate
r_struct
id|dvd_lu_send_rpcstate
(brace
DECL|member|type
id|__u8
id|type
suffix:colon
l_int|2
suffix:semicolon
DECL|member|vra
id|__u8
id|vra
suffix:colon
l_int|3
suffix:semicolon
DECL|member|ucca
id|__u8
id|ucca
suffix:colon
l_int|3
suffix:semicolon
DECL|member|region_mask
id|__u8
id|region_mask
suffix:semicolon
DECL|member|rpc_scheme
id|__u8
id|rpc_scheme
suffix:semicolon
)brace
suffix:semicolon
r_typedef
r_union
(brace
DECL|member|type
id|__u8
id|type
suffix:semicolon
DECL|member|lsa
r_struct
id|dvd_lu_send_agid
id|lsa
suffix:semicolon
DECL|member|hsc
r_struct
id|dvd_host_send_challenge
id|hsc
suffix:semicolon
DECL|member|lsk
r_struct
id|dvd_send_key
id|lsk
suffix:semicolon
DECL|member|lsc
r_struct
id|dvd_lu_send_challenge
id|lsc
suffix:semicolon
DECL|member|hsk
r_struct
id|dvd_send_key
id|hsk
suffix:semicolon
DECL|member|lstk
r_struct
id|dvd_lu_send_title_key
id|lstk
suffix:semicolon
DECL|member|lsasf
r_struct
id|dvd_lu_send_asf
id|lsasf
suffix:semicolon
DECL|member|hrpcs
r_struct
id|dvd_host_send_rpcstate
id|hrpcs
suffix:semicolon
DECL|member|lrpcs
r_struct
id|dvd_lu_send_rpcstate
id|lrpcs
suffix:semicolon
DECL|typedef|dvd_authinfo
)brace
id|dvd_authinfo
suffix:semicolon
DECL|struct|request_sense
r_struct
id|request_sense
(brace
macro_line|#if defined(__BIG_ENDIAN_BITFIELD)
DECL|member|valid
id|__u8
id|valid
suffix:colon
l_int|1
suffix:semicolon
DECL|member|error_code
id|__u8
id|error_code
suffix:colon
l_int|7
suffix:semicolon
macro_line|#elif defined(__LITTLE_ENDIAN_BITFIELD)
id|__u8
id|error_code
suffix:colon
l_int|7
suffix:semicolon
id|__u8
id|valid
suffix:colon
l_int|1
suffix:semicolon
macro_line|#endif
DECL|member|segment_number
id|__u8
id|segment_number
suffix:semicolon
macro_line|#if defined(__BIG_ENDIAN_BITFIELD)
DECL|member|reserved1
id|__u8
id|reserved1
suffix:colon
l_int|2
suffix:semicolon
DECL|member|ili
id|__u8
id|ili
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved2
id|__u8
id|reserved2
suffix:colon
l_int|1
suffix:semicolon
DECL|member|sense_key
id|__u8
id|sense_key
suffix:colon
l_int|4
suffix:semicolon
macro_line|#elif defined(__LITTLE_ENDIAN_BITFIELD)
DECL|member|sense_key
id|__u8
id|sense_key
suffix:colon
l_int|4
suffix:semicolon
DECL|member|reserved2
id|__u8
id|reserved2
suffix:colon
l_int|1
suffix:semicolon
DECL|member|ili
id|__u8
id|ili
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved1
id|__u8
id|reserved1
suffix:colon
l_int|2
suffix:semicolon
macro_line|#endif
DECL|member|information
id|__u8
id|information
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|add_sense_len
id|__u8
id|add_sense_len
suffix:semicolon
DECL|member|command_info
id|__u8
id|command_info
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|asc
id|__u8
id|asc
suffix:semicolon
DECL|member|ascq
id|__u8
id|ascq
suffix:semicolon
DECL|member|fruc
id|__u8
id|fruc
suffix:semicolon
DECL|member|sks
id|__u8
id|sks
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|asb
id|__u8
id|asb
(braket
l_int|46
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
DECL|struct|cdrom_write_settings
r_struct
id|cdrom_write_settings
(brace
DECL|member|fpacket
r_int
r_char
id|fpacket
suffix:semicolon
multiline_comment|/* fixed/variable packets */
DECL|member|packet_size
r_int
r_int
id|packet_size
suffix:semicolon
multiline_comment|/* write out this number of packets */
DECL|member|nwa
r_int
r_int
id|nwa
suffix:semicolon
multiline_comment|/* next writeable address */
DECL|member|writeable
r_int
r_char
id|writeable
suffix:semicolon
multiline_comment|/* cdrom is writeable */
)brace
suffix:semicolon
multiline_comment|/* Uniform cdrom data structures for cdrom.c */
DECL|struct|cdrom_device_info
r_struct
id|cdrom_device_info
(brace
DECL|member|ops
r_struct
id|cdrom_device_ops
op_star
id|ops
suffix:semicolon
multiline_comment|/* link to device_ops */
DECL|member|next
r_struct
id|cdrom_device_info
op_star
id|next
suffix:semicolon
multiline_comment|/* next device_info for this major */
DECL|member|handle
r_void
op_star
id|handle
suffix:semicolon
multiline_comment|/* driver-dependent data */
DECL|member|de
id|devfs_handle_t
id|de
suffix:semicolon
multiline_comment|/* real driver should create this  */
DECL|member|number
r_int
id|number
suffix:semicolon
multiline_comment|/* generic driver updates this  */
multiline_comment|/* specifications */
DECL|member|dev
id|kdev_t
id|dev
suffix:semicolon
multiline_comment|/* device number */
DECL|member|mask
r_int
id|mask
suffix:semicolon
multiline_comment|/* mask of capability: disables them */
DECL|member|speed
r_int
id|speed
suffix:semicolon
multiline_comment|/* maximum speed for reading data */
DECL|member|capacity
r_int
id|capacity
suffix:semicolon
multiline_comment|/* number of discs in jukebox */
multiline_comment|/* device-related storage */
DECL|member|options
r_int
id|options
suffix:colon
l_int|30
suffix:semicolon
multiline_comment|/* options flags */
DECL|member|mc_flags
r_int
id|mc_flags
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* media change buffer flags */
DECL|member|use_count
r_int
id|use_count
suffix:semicolon
multiline_comment|/* number of times device opened */
DECL|member|name
r_char
id|name
(braket
l_int|20
)braket
suffix:semicolon
multiline_comment|/* name of the device type */
multiline_comment|/* per-device flags */
DECL|member|sanyo_slot
id|__u8
id|sanyo_slot
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* Sanyo 3 CD changer support */
DECL|member|reserved
id|__u8
id|reserved
suffix:colon
l_int|6
suffix:semicolon
multiline_comment|/* not used yet */
DECL|member|write
r_struct
id|cdrom_write_settings
id|write
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|cdrom_device_ops
r_struct
id|cdrom_device_ops
(brace
multiline_comment|/* routines */
DECL|member|open
r_int
(paren
op_star
id|open
)paren
(paren
r_struct
id|cdrom_device_info
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|release
r_void
(paren
op_star
id|release
)paren
(paren
r_struct
id|cdrom_device_info
op_star
)paren
suffix:semicolon
DECL|member|drive_status
r_int
(paren
op_star
id|drive_status
)paren
(paren
r_struct
id|cdrom_device_info
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|media_changed
r_int
(paren
op_star
id|media_changed
)paren
(paren
r_struct
id|cdrom_device_info
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|tray_move
r_int
(paren
op_star
id|tray_move
)paren
(paren
r_struct
id|cdrom_device_info
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|lock_door
r_int
(paren
op_star
id|lock_door
)paren
(paren
r_struct
id|cdrom_device_info
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|select_speed
r_int
(paren
op_star
id|select_speed
)paren
(paren
r_struct
id|cdrom_device_info
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|select_disc
r_int
(paren
op_star
id|select_disc
)paren
(paren
r_struct
id|cdrom_device_info
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|get_last_session
r_int
(paren
op_star
id|get_last_session
)paren
(paren
r_struct
id|cdrom_device_info
op_star
comma
r_struct
id|cdrom_multisession
op_star
)paren
suffix:semicolon
DECL|member|get_mcn
r_int
(paren
op_star
id|get_mcn
)paren
(paren
r_struct
id|cdrom_device_info
op_star
comma
r_struct
id|cdrom_mcn
op_star
)paren
suffix:semicolon
multiline_comment|/* hard reset device */
DECL|member|reset
r_int
(paren
op_star
id|reset
)paren
(paren
r_struct
id|cdrom_device_info
op_star
)paren
suffix:semicolon
multiline_comment|/* play stuff */
DECL|member|audio_ioctl
r_int
(paren
op_star
id|audio_ioctl
)paren
(paren
r_struct
id|cdrom_device_info
op_star
comma
r_int
r_int
comma
r_void
op_star
)paren
suffix:semicolon
multiline_comment|/* dev-specific */
DECL|member|dev_ioctl
r_int
(paren
op_star
id|dev_ioctl
)paren
(paren
r_struct
id|cdrom_device_info
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/* driver specifications */
DECL|member|capability
r_const
r_int
id|capability
suffix:semicolon
multiline_comment|/* capability flags */
DECL|member|n_minors
r_int
id|n_minors
suffix:semicolon
multiline_comment|/* number of active minor devices */
multiline_comment|/* handle uniform packets for scsi type devices (scsi,atapi) */
DECL|member|generic_packet
r_int
(paren
op_star
id|generic_packet
)paren
(paren
r_struct
id|cdrom_device_info
op_star
comma
r_struct
id|cdrom_generic_command
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* the general block_device operations structure: */
r_extern
r_int
id|cdrom_open
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
)paren
suffix:semicolon
r_extern
r_int
id|cdrom_release
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
)paren
suffix:semicolon
r_extern
r_int
id|cdrom_ioctl
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
comma
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
id|cdrom_media_changed
c_func
(paren
id|kdev_t
)paren
suffix:semicolon
r_extern
r_int
id|register_cdrom
c_func
(paren
r_struct
id|cdrom_device_info
op_star
id|cdi
)paren
suffix:semicolon
r_extern
r_int
id|unregister_cdrom
c_func
(paren
r_struct
id|cdrom_device_info
op_star
id|cdi
)paren
suffix:semicolon
DECL|function|devfs_plain_cdrom
r_static
r_inline
r_void
id|devfs_plain_cdrom
c_func
(paren
r_struct
id|cdrom_device_info
op_star
id|cdi
comma
r_struct
id|block_device_operations
op_star
id|ops
)paren
(brace
r_char
id|vname
(braket
l_int|23
)braket
suffix:semicolon
id|sprintf
(paren
id|vname
comma
l_string|&quot;cdroms/cdrom%d&quot;
comma
id|cdi-&gt;number
)paren
suffix:semicolon
id|cdi-&gt;de
op_assign
id|devfs_register
(paren
l_int|NULL
comma
id|vname
comma
id|DEVFS_FL_DEFAULT
comma
id|major
c_func
(paren
id|cdi-&gt;dev
)paren
comma
id|minor
c_func
(paren
id|cdi-&gt;dev
)paren
comma
id|S_IFBLK
op_or
id|S_IRUGO
op_or
id|S_IWUGO
comma
id|ops
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_typedef
r_struct
(brace
DECL|member|data
r_int
id|data
suffix:semicolon
DECL|member|audio
r_int
id|audio
suffix:semicolon
DECL|member|cdi
r_int
id|cdi
suffix:semicolon
DECL|member|xa
r_int
id|xa
suffix:semicolon
DECL|member|error
r_int
id|error
suffix:semicolon
DECL|typedef|tracktype
)brace
id|tracktype
suffix:semicolon
r_extern
r_void
id|cdrom_count_tracks
c_func
(paren
r_struct
id|cdrom_device_info
op_star
id|cdi
comma
id|tracktype
op_star
id|tracks
)paren
suffix:semicolon
r_extern
r_int
id|cdrom_get_next_writable
c_func
(paren
id|kdev_t
id|dev
comma
r_int
op_star
id|next_writable
)paren
suffix:semicolon
r_extern
r_int
id|cdrom_get_last_written
c_func
(paren
id|kdev_t
id|dev
comma
r_int
op_star
id|last_written
)paren
suffix:semicolon
r_extern
r_int
id|cdrom_number_of_slots
c_func
(paren
r_struct
id|cdrom_device_info
op_star
id|cdi
)paren
suffix:semicolon
r_extern
r_int
id|cdrom_select_disc
c_func
(paren
r_struct
id|cdrom_device_info
op_star
id|cdi
comma
r_int
id|slot
)paren
suffix:semicolon
r_extern
r_int
id|cdrom_mode_select
c_func
(paren
r_struct
id|cdrom_device_info
op_star
id|cdi
comma
r_struct
id|cdrom_generic_command
op_star
id|cgc
)paren
suffix:semicolon
r_extern
r_int
id|cdrom_mode_sense
c_func
(paren
r_struct
id|cdrom_device_info
op_star
id|cdi
comma
r_struct
id|cdrom_generic_command
op_star
id|cgc
comma
r_int
id|page_code
comma
r_int
id|page_control
)paren
suffix:semicolon
r_extern
r_void
id|init_cdrom_command
c_func
(paren
r_struct
id|cdrom_generic_command
op_star
id|cgc
comma
r_void
op_star
id|buffer
comma
r_int
id|len
comma
r_int
id|type
)paren
suffix:semicolon
r_extern
r_struct
id|cdrom_device_info
op_star
id|cdrom_find_device
c_func
(paren
id|kdev_t
id|dev
)paren
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|disc_information_length
id|__u16
id|disc_information_length
suffix:semicolon
macro_line|#if defined(__BIG_ENDIAN_BITFIELD)
DECL|member|reserved1
id|__u8
id|reserved1
suffix:colon
l_int|3
suffix:semicolon
DECL|member|erasable
id|__u8
id|erasable
suffix:colon
l_int|1
suffix:semicolon
DECL|member|border_status
id|__u8
id|border_status
suffix:colon
l_int|2
suffix:semicolon
DECL|member|disc_status
id|__u8
id|disc_status
suffix:colon
l_int|2
suffix:semicolon
macro_line|#elif defined(__LITTLE_ENDIAN_BITFIELD)
DECL|member|disc_status
id|__u8
id|disc_status
suffix:colon
l_int|2
suffix:semicolon
DECL|member|border_status
id|__u8
id|border_status
suffix:colon
l_int|2
suffix:semicolon
DECL|member|erasable
id|__u8
id|erasable
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved1
id|__u8
id|reserved1
suffix:colon
l_int|3
suffix:semicolon
macro_line|#else
macro_line|#error &quot;Please fix &lt;asm/byteorder.h&gt;&quot;
macro_line|#endif
DECL|member|n_first_track
id|__u8
id|n_first_track
suffix:semicolon
DECL|member|n_sessions_lsb
id|__u8
id|n_sessions_lsb
suffix:semicolon
DECL|member|first_track_lsb
id|__u8
id|first_track_lsb
suffix:semicolon
DECL|member|last_track_lsb
id|__u8
id|last_track_lsb
suffix:semicolon
macro_line|#if defined(__BIG_ENDIAN_BITFIELD)
DECL|member|did_v
id|__u8
id|did_v
suffix:colon
l_int|1
suffix:semicolon
DECL|member|dbc_v
id|__u8
id|dbc_v
suffix:colon
l_int|1
suffix:semicolon
DECL|member|uru
id|__u8
id|uru
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved2
id|__u8
id|reserved2
suffix:colon
l_int|5
suffix:semicolon
macro_line|#elif defined(__LITTLE_ENDIAN_BITFIELD)
DECL|member|reserved2
id|__u8
id|reserved2
suffix:colon
l_int|5
suffix:semicolon
DECL|member|uru
id|__u8
id|uru
suffix:colon
l_int|1
suffix:semicolon
DECL|member|dbc_v
id|__u8
id|dbc_v
suffix:colon
l_int|1
suffix:semicolon
DECL|member|did_v
id|__u8
id|did_v
suffix:colon
l_int|1
suffix:semicolon
macro_line|#endif
DECL|member|disc_type
id|__u8
id|disc_type
suffix:semicolon
DECL|member|n_sessions_msb
id|__u8
id|n_sessions_msb
suffix:semicolon
DECL|member|first_track_msb
id|__u8
id|first_track_msb
suffix:semicolon
DECL|member|last_track_msb
id|__u8
id|last_track_msb
suffix:semicolon
DECL|member|disc_id
id|__u32
id|disc_id
suffix:semicolon
DECL|member|lead_in
id|__u32
id|lead_in
suffix:semicolon
DECL|member|lead_out
id|__u32
id|lead_out
suffix:semicolon
DECL|member|disc_bar_code
id|__u8
id|disc_bar_code
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|reserved3
id|__u8
id|reserved3
suffix:semicolon
DECL|member|n_opc
id|__u8
id|n_opc
suffix:semicolon
DECL|typedef|disc_information
)brace
id|disc_information
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|track_information_length
id|__u16
id|track_information_length
suffix:semicolon
DECL|member|track_lsb
id|__u8
id|track_lsb
suffix:semicolon
DECL|member|session_lsb
id|__u8
id|session_lsb
suffix:semicolon
DECL|member|reserved1
id|__u8
id|reserved1
suffix:semicolon
macro_line|#if defined(__BIG_ENDIAN_BITFIELD)
DECL|member|reserved2
id|__u8
id|reserved2
suffix:colon
l_int|2
suffix:semicolon
DECL|member|damage
id|__u8
id|damage
suffix:colon
l_int|1
suffix:semicolon
DECL|member|copy
id|__u8
id|copy
suffix:colon
l_int|1
suffix:semicolon
DECL|member|track_mode
id|__u8
id|track_mode
suffix:colon
l_int|4
suffix:semicolon
DECL|member|rt
id|__u8
id|rt
suffix:colon
l_int|1
suffix:semicolon
DECL|member|blank
id|__u8
id|blank
suffix:colon
l_int|1
suffix:semicolon
DECL|member|packet
id|__u8
id|packet
suffix:colon
l_int|1
suffix:semicolon
DECL|member|fp
id|__u8
id|fp
suffix:colon
l_int|1
suffix:semicolon
DECL|member|data_mode
id|__u8
id|data_mode
suffix:colon
l_int|4
suffix:semicolon
DECL|member|reserved3
id|__u8
id|reserved3
suffix:colon
l_int|6
suffix:semicolon
DECL|member|lra_v
id|__u8
id|lra_v
suffix:colon
l_int|1
suffix:semicolon
DECL|member|nwa_v
id|__u8
id|nwa_v
suffix:colon
l_int|1
suffix:semicolon
macro_line|#elif defined(__LITTLE_ENDIAN_BITFIELD)
DECL|member|track_mode
id|__u8
id|track_mode
suffix:colon
l_int|4
suffix:semicolon
DECL|member|copy
id|__u8
id|copy
suffix:colon
l_int|1
suffix:semicolon
DECL|member|damage
id|__u8
id|damage
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved2
id|__u8
id|reserved2
suffix:colon
l_int|2
suffix:semicolon
DECL|member|data_mode
id|__u8
id|data_mode
suffix:colon
l_int|4
suffix:semicolon
DECL|member|fp
id|__u8
id|fp
suffix:colon
l_int|1
suffix:semicolon
DECL|member|packet
id|__u8
id|packet
suffix:colon
l_int|1
suffix:semicolon
DECL|member|blank
id|__u8
id|blank
suffix:colon
l_int|1
suffix:semicolon
DECL|member|rt
id|__u8
id|rt
suffix:colon
l_int|1
suffix:semicolon
DECL|member|nwa_v
id|__u8
id|nwa_v
suffix:colon
l_int|1
suffix:semicolon
DECL|member|lra_v
id|__u8
id|lra_v
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved3
id|__u8
id|reserved3
suffix:colon
l_int|6
suffix:semicolon
macro_line|#endif
DECL|member|track_start
id|__u32
id|track_start
suffix:semicolon
DECL|member|next_writable
id|__u32
id|next_writable
suffix:semicolon
DECL|member|free_blocks
id|__u32
id|free_blocks
suffix:semicolon
DECL|member|fixed_packet_size
id|__u32
id|fixed_packet_size
suffix:semicolon
DECL|member|track_size
id|__u32
id|track_size
suffix:semicolon
DECL|member|last_rec_address
id|__u32
id|last_rec_address
suffix:semicolon
DECL|typedef|track_information
)brace
id|track_information
suffix:semicolon
r_extern
r_int
id|cdrom_get_disc_info
c_func
(paren
id|kdev_t
id|dev
comma
id|disc_information
op_star
id|di
)paren
suffix:semicolon
r_extern
r_int
id|cdrom_get_track_info
c_func
(paren
id|kdev_t
id|dev
comma
id|__u16
id|track
comma
id|__u8
id|type
comma
id|track_information
op_star
id|ti
)paren
suffix:semicolon
multiline_comment|/* The SCSI spec says there could be 256 slots. */
DECL|macro|CDROM_MAX_SLOTS
mdefine_line|#define CDROM_MAX_SLOTS&t;256
DECL|struct|cdrom_mechstat_header
r_struct
id|cdrom_mechstat_header
(brace
macro_line|#if defined(__BIG_ENDIAN_BITFIELD)
DECL|member|fault
id|__u8
id|fault
suffix:colon
l_int|1
suffix:semicolon
DECL|member|changer_state
id|__u8
id|changer_state
suffix:colon
l_int|2
suffix:semicolon
DECL|member|curslot
id|__u8
id|curslot
suffix:colon
l_int|5
suffix:semicolon
DECL|member|mech_state
id|__u8
id|mech_state
suffix:colon
l_int|3
suffix:semicolon
DECL|member|door_open
id|__u8
id|door_open
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved1
id|__u8
id|reserved1
suffix:colon
l_int|4
suffix:semicolon
macro_line|#elif defined(__LITTLE_ENDIAN_BITFIELD)
id|__u8
id|curslot
suffix:colon
l_int|5
suffix:semicolon
id|__u8
id|changer_state
suffix:colon
l_int|2
suffix:semicolon
id|__u8
id|fault
suffix:colon
l_int|1
suffix:semicolon
id|__u8
id|reserved1
suffix:colon
l_int|4
suffix:semicolon
id|__u8
id|door_open
suffix:colon
l_int|1
suffix:semicolon
id|__u8
id|mech_state
suffix:colon
l_int|3
suffix:semicolon
macro_line|#endif
DECL|member|curlba
id|__u8
id|curlba
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|nslots
id|__u8
id|nslots
suffix:semicolon
DECL|member|slot_tablelen
id|__u16
id|slot_tablelen
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|cdrom_slot
r_struct
id|cdrom_slot
(brace
macro_line|#if defined(__BIG_ENDIAN_BITFIELD)
DECL|member|disc_present
id|__u8
id|disc_present
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved1
id|__u8
id|reserved1
suffix:colon
l_int|6
suffix:semicolon
DECL|member|change
id|__u8
id|change
suffix:colon
l_int|1
suffix:semicolon
macro_line|#elif defined(__LITTLE_ENDIAN_BITFIELD)
id|__u8
id|change
suffix:colon
l_int|1
suffix:semicolon
id|__u8
id|reserved1
suffix:colon
l_int|6
suffix:semicolon
id|__u8
id|disc_present
suffix:colon
l_int|1
suffix:semicolon
macro_line|#endif
DECL|member|reserved2
id|__u8
id|reserved2
(braket
l_int|3
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|cdrom_changer_info
r_struct
id|cdrom_changer_info
(brace
DECL|member|hdr
r_struct
id|cdrom_mechstat_header
id|hdr
suffix:semicolon
DECL|member|slots
r_struct
id|cdrom_slot
id|slots
(braket
id|CDROM_MAX_SLOTS
)braket
suffix:semicolon
)brace
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|mechtype_caddy
id|mechtype_caddy
op_assign
l_int|0
comma
DECL|enumerator|mechtype_tray
id|mechtype_tray
op_assign
l_int|1
comma
DECL|enumerator|mechtype_popup
id|mechtype_popup
op_assign
l_int|2
comma
DECL|enumerator|mechtype_individual_changer
id|mechtype_individual_changer
op_assign
l_int|4
comma
DECL|enumerator|mechtype_cartridge_changer
id|mechtype_cartridge_changer
op_assign
l_int|5
DECL|typedef|mechtype_t
)brace
id|mechtype_t
suffix:semicolon
DECL|struct|mode_page_header
r_struct
id|mode_page_header
(brace
DECL|member|mode_data_length
id|__u16
id|mode_data_length
suffix:semicolon
DECL|member|medium_type
id|__u8
id|medium_type
suffix:semicolon
DECL|member|reserved1
id|__u8
id|reserved1
suffix:semicolon
DECL|member|reserved2
id|__u8
id|reserved2
suffix:semicolon
DECL|member|reserved3
id|__u8
id|reserved3
suffix:semicolon
DECL|member|desc_length
id|__u16
id|desc_length
suffix:semicolon
)brace
suffix:semicolon
r_typedef
r_struct
(brace
macro_line|#if defined(__BIG_ENDIAN_BITFIELD)
DECL|member|ps
id|__u8
id|ps
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved1
id|__u8
id|reserved1
suffix:colon
l_int|1
suffix:semicolon
DECL|member|page_code
id|__u8
id|page_code
suffix:colon
l_int|6
suffix:semicolon
DECL|member|page_length
id|__u8
id|page_length
suffix:semicolon
DECL|member|reserved2
id|__u8
id|reserved2
suffix:colon
l_int|1
suffix:semicolon
DECL|member|bufe
id|__u8
id|bufe
suffix:colon
l_int|1
suffix:semicolon
DECL|member|ls_v
id|__u8
id|ls_v
suffix:colon
l_int|1
suffix:semicolon
DECL|member|test_write
id|__u8
id|test_write
suffix:colon
l_int|1
suffix:semicolon
DECL|member|write_type
id|__u8
id|write_type
suffix:colon
l_int|4
suffix:semicolon
DECL|member|multi_session
id|__u8
id|multi_session
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* or border, DVD */
DECL|member|fp
id|__u8
id|fp
suffix:colon
l_int|1
suffix:semicolon
DECL|member|copy
id|__u8
id|copy
suffix:colon
l_int|1
suffix:semicolon
DECL|member|track_mode
id|__u8
id|track_mode
suffix:colon
l_int|4
suffix:semicolon
DECL|member|reserved3
id|__u8
id|reserved3
suffix:colon
l_int|4
suffix:semicolon
DECL|member|data_block_type
id|__u8
id|data_block_type
suffix:colon
l_int|4
suffix:semicolon
macro_line|#elif defined(__LITTLE_ENDIAN_BITFIELD)
id|__u8
id|page_code
suffix:colon
l_int|6
suffix:semicolon
id|__u8
id|reserved1
suffix:colon
l_int|1
suffix:semicolon
id|__u8
id|ps
suffix:colon
l_int|1
suffix:semicolon
id|__u8
id|page_length
suffix:semicolon
id|__u8
id|write_type
suffix:colon
l_int|4
suffix:semicolon
id|__u8
id|test_write
suffix:colon
l_int|1
suffix:semicolon
id|__u8
id|ls_v
suffix:colon
l_int|1
suffix:semicolon
id|__u8
id|bufe
suffix:colon
l_int|1
suffix:semicolon
id|__u8
id|reserved2
suffix:colon
l_int|1
suffix:semicolon
id|__u8
id|track_mode
suffix:colon
l_int|4
suffix:semicolon
id|__u8
id|copy
suffix:colon
l_int|1
suffix:semicolon
id|__u8
id|fp
suffix:colon
l_int|1
suffix:semicolon
id|__u8
id|multi_session
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* or border, DVD */
id|__u8
id|data_block_type
suffix:colon
l_int|4
suffix:semicolon
id|__u8
id|reserved3
suffix:colon
l_int|4
suffix:semicolon
macro_line|#endif
DECL|member|link_size
id|__u8
id|link_size
suffix:semicolon
DECL|member|reserved4
id|__u8
id|reserved4
suffix:semicolon
macro_line|#if defined(__BIG_ENDIAN_BITFIELD)
DECL|member|reserved5
id|__u8
id|reserved5
suffix:colon
l_int|2
suffix:semicolon
DECL|member|app_code
id|__u8
id|app_code
suffix:colon
l_int|6
suffix:semicolon
macro_line|#elif defined(__LITTLE_ENDIAN_BITFIELD)
DECL|member|app_code
id|__u8
id|app_code
suffix:colon
l_int|6
suffix:semicolon
DECL|member|reserved5
id|__u8
id|reserved5
suffix:colon
l_int|2
suffix:semicolon
macro_line|#endif
DECL|member|session_format
id|__u8
id|session_format
suffix:semicolon
DECL|member|reserved6
id|__u8
id|reserved6
suffix:semicolon
DECL|member|packet_size
id|__u32
id|packet_size
suffix:semicolon
DECL|member|audio_pause
id|__u16
id|audio_pause
suffix:semicolon
DECL|member|mcn
id|__u8
id|mcn
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|isrc
id|__u8
id|isrc
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|subhdr0
id|__u8
id|subhdr0
suffix:semicolon
DECL|member|subhdr1
id|__u8
id|subhdr1
suffix:semicolon
DECL|member|subhdr2
id|__u8
id|subhdr2
suffix:semicolon
DECL|member|subhdr3
id|__u8
id|subhdr3
suffix:semicolon
DECL|typedef|write_param_page
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
id|write_param_page
suffix:semicolon
DECL|struct|modesel_head
r_struct
id|modesel_head
(brace
DECL|member|reserved1
id|__u8
id|reserved1
suffix:semicolon
DECL|member|medium
id|__u8
id|medium
suffix:semicolon
DECL|member|reserved2
id|__u8
id|reserved2
suffix:semicolon
DECL|member|block_desc_length
id|__u8
id|block_desc_length
suffix:semicolon
DECL|member|density
id|__u8
id|density
suffix:semicolon
DECL|member|number_of_blocks_hi
id|__u8
id|number_of_blocks_hi
suffix:semicolon
DECL|member|number_of_blocks_med
id|__u8
id|number_of_blocks_med
suffix:semicolon
DECL|member|number_of_blocks_lo
id|__u8
id|number_of_blocks_lo
suffix:semicolon
DECL|member|reserved3
id|__u8
id|reserved3
suffix:semicolon
DECL|member|block_length_hi
id|__u8
id|block_length_hi
suffix:semicolon
DECL|member|block_length_med
id|__u8
id|block_length_med
suffix:semicolon
DECL|member|block_length_lo
id|__u8
id|block_length_lo
suffix:semicolon
)brace
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|report_key_length
id|__u16
id|report_key_length
suffix:semicolon
DECL|member|reserved1
id|__u8
id|reserved1
suffix:semicolon
DECL|member|reserved2
id|__u8
id|reserved2
suffix:semicolon
macro_line|#if defined(__BIG_ENDIAN_BITFIELD)
DECL|member|type_code
id|__u8
id|type_code
suffix:colon
l_int|2
suffix:semicolon
DECL|member|vra
id|__u8
id|vra
suffix:colon
l_int|3
suffix:semicolon
DECL|member|ucca
id|__u8
id|ucca
suffix:colon
l_int|3
suffix:semicolon
macro_line|#elif defined(__LITTLE_ENDIAN_BITFIELD)
DECL|member|ucca
id|__u8
id|ucca
suffix:colon
l_int|3
suffix:semicolon
DECL|member|vra
id|__u8
id|vra
suffix:colon
l_int|3
suffix:semicolon
DECL|member|type_code
id|__u8
id|type_code
suffix:colon
l_int|2
suffix:semicolon
macro_line|#endif
DECL|member|region_mask
id|__u8
id|region_mask
suffix:semicolon
DECL|member|rpc_scheme
id|__u8
id|rpc_scheme
suffix:semicolon
DECL|member|reserved3
id|__u8
id|reserved3
suffix:semicolon
DECL|typedef|rpc_state_t
)brace
id|rpc_state_t
suffix:semicolon
macro_line|#endif  /* End of kernel only stuff */ 
macro_line|#endif  /* _LINUX_CDROM_H */
eof
