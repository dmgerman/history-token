multiline_comment|/* &n; * linux/mtio.h header file for Linux. Written by H. Bergman&n; *&n; * Modified for special ioctls provided by zftape in September 1997&n; * by C.-J. Heine.&n; */
macro_line|#ifndef _LINUX_MTIO_H
DECL|macro|_LINUX_MTIO_H
mdefine_line|#define _LINUX_MTIO_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#include &lt;linux/qic117.h&gt;
multiline_comment|/*&n; * Structures and definitions for mag tape io control commands&n; */
multiline_comment|/* structure for MTIOCTOP - mag tape op command */
DECL|struct|mtop
r_struct
id|mtop
(brace
DECL|member|mt_op
r_int
id|mt_op
suffix:semicolon
multiline_comment|/* operations defined below */
DECL|member|mt_count
r_int
id|mt_count
suffix:semicolon
multiline_comment|/* how many of them */
)brace
suffix:semicolon
multiline_comment|/* Magnetic Tape operations [Not all operations supported by all drivers]: */
DECL|macro|MTRESET
mdefine_line|#define MTRESET 0&t;/* +reset drive in case of problems */
DECL|macro|MTFSF
mdefine_line|#define MTFSF&t;1&t;/* forward space over FileMark,&n;&t;&t;&t; * position at first record of next file &n;&t;&t;&t; */
DECL|macro|MTBSF
mdefine_line|#define MTBSF&t;2&t;/* backward space FileMark (position before FM) */
DECL|macro|MTFSR
mdefine_line|#define MTFSR&t;3&t;/* forward space record */
DECL|macro|MTBSR
mdefine_line|#define MTBSR&t;4&t;/* backward space record */
DECL|macro|MTWEOF
mdefine_line|#define MTWEOF&t;5&t;/* write an end-of-file record (mark) */
DECL|macro|MTREW
mdefine_line|#define MTREW&t;6&t;/* rewind */
DECL|macro|MTOFFL
mdefine_line|#define MTOFFL&t;7&t;/* rewind and put the drive offline (eject?) */
DECL|macro|MTNOP
mdefine_line|#define MTNOP&t;8&t;/* no op, set status only (read with MTIOCGET) */
DECL|macro|MTRETEN
mdefine_line|#define MTRETEN 9&t;/* retension tape */
DECL|macro|MTBSFM
mdefine_line|#define MTBSFM&t;10&t;/* +backward space FileMark, position at FM */
DECL|macro|MTFSFM
mdefine_line|#define MTFSFM  11&t;/* +forward space FileMark, position at FM */
DECL|macro|MTEOM
mdefine_line|#define MTEOM&t;12&t;/* goto end of recorded media (for appending files).&n;&t;&t;&t; * MTEOM positions after the last FM, ready for&n;&t;&t;&t; * appending another file.&n;&t;&t;&t; */
DECL|macro|MTERASE
mdefine_line|#define MTERASE 13&t;/* erase tape -- be careful! */
DECL|macro|MTRAS1
mdefine_line|#define MTRAS1  14&t;/* run self test 1 (nondestructive) */
DECL|macro|MTRAS2
mdefine_line|#define MTRAS2&t;15&t;/* run self test 2 (destructive) */
DECL|macro|MTRAS3
mdefine_line|#define MTRAS3  16&t;/* reserved for self test 3 */
DECL|macro|MTSETBLK
mdefine_line|#define MTSETBLK 20&t;/* set block length (SCSI) */
DECL|macro|MTSETDENSITY
mdefine_line|#define MTSETDENSITY 21&t;/* set tape density (SCSI) */
DECL|macro|MTSEEK
mdefine_line|#define MTSEEK&t;22&t;/* seek to block (Tandberg, etc.) */
DECL|macro|MTTELL
mdefine_line|#define MTTELL&t;23&t;/* tell block (Tandberg, etc.) */
DECL|macro|MTSETDRVBUFFER
mdefine_line|#define MTSETDRVBUFFER 24 /* set the drive buffering according to SCSI-2 */
multiline_comment|/* ordinary buffered operation with code 1 */
DECL|macro|MTFSS
mdefine_line|#define MTFSS&t;25&t;/* space forward over setmarks */
DECL|macro|MTBSS
mdefine_line|#define MTBSS&t;26&t;/* space backward over setmarks */
DECL|macro|MTWSM
mdefine_line|#define MTWSM&t;27&t;/* write setmarks */
DECL|macro|MTLOCK
mdefine_line|#define MTLOCK  28&t;/* lock the drive door */
DECL|macro|MTUNLOCK
mdefine_line|#define MTUNLOCK 29&t;/* unlock the drive door */
DECL|macro|MTLOAD
mdefine_line|#define MTLOAD  30&t;/* execute the SCSI load command */
DECL|macro|MTUNLOAD
mdefine_line|#define MTUNLOAD 31&t;/* execute the SCSI unload command */
DECL|macro|MTCOMPRESSION
mdefine_line|#define MTCOMPRESSION 32/* control compression with SCSI mode page 15 */
DECL|macro|MTSETPART
mdefine_line|#define MTSETPART 33&t;/* Change the active tape partition */
DECL|macro|MTMKPART
mdefine_line|#define MTMKPART  34&t;/* Format the tape with one or two partitions */
multiline_comment|/* structure for MTIOCGET - mag tape get status command */
DECL|struct|mtget
r_struct
id|mtget
(brace
DECL|member|mt_type
r_int
id|mt_type
suffix:semicolon
multiline_comment|/* type of magtape device */
DECL|member|mt_resid
r_int
id|mt_resid
suffix:semicolon
multiline_comment|/* residual count: (not sure)&n;&t;&t;&t;&t; *&t;number of bytes ignored, or&n;&t;&t;&t;&t; *&t;number of files not skipped, or&n;&t;&t;&t;&t; *&t;number of records not skipped.&n;&t;&t;&t;&t; */
multiline_comment|/* the following registers are device dependent */
DECL|member|mt_dsreg
r_int
id|mt_dsreg
suffix:semicolon
multiline_comment|/* status register */
DECL|member|mt_gstat
r_int
id|mt_gstat
suffix:semicolon
multiline_comment|/* generic (device independent) status */
DECL|member|mt_erreg
r_int
id|mt_erreg
suffix:semicolon
multiline_comment|/* error register */
multiline_comment|/* The next two fields are not always used */
DECL|member|mt_fileno
id|__kernel_daddr_t
id|mt_fileno
suffix:semicolon
multiline_comment|/* number of current file on tape */
DECL|member|mt_blkno
id|__kernel_daddr_t
id|mt_blkno
suffix:semicolon
multiline_comment|/* current block number */
)brace
suffix:semicolon
multiline_comment|/*&n; * Constants for mt_type. Not all of these are supported,&n; * and these are not all of the ones that are supported.&n; */
DECL|macro|MT_ISUNKNOWN
mdefine_line|#define MT_ISUNKNOWN&t;&t;0x01
DECL|macro|MT_ISQIC02
mdefine_line|#define MT_ISQIC02&t;&t;0x02&t;/* Generic QIC-02 tape streamer */
DECL|macro|MT_ISWT5150
mdefine_line|#define MT_ISWT5150&t;&t;0x03&t;/* Wangtek 5150EQ, QIC-150, QIC-02 */
DECL|macro|MT_ISARCHIVE_5945L2
mdefine_line|#define MT_ISARCHIVE_5945L2&t;0x04&t;/* Archive 5945L-2, QIC-24, QIC-02? */
DECL|macro|MT_ISCMSJ500
mdefine_line|#define MT_ISCMSJ500&t;&t;0x05&t;/* CMS Jumbo 500 (QIC-02?) */
DECL|macro|MT_ISTDC3610
mdefine_line|#define MT_ISTDC3610&t;&t;0x06&t;/* Tandberg 6310, QIC-24 */
DECL|macro|MT_ISARCHIVE_VP60I
mdefine_line|#define MT_ISARCHIVE_VP60I&t;0x07&t;/* Archive VP60i, QIC-02 */
DECL|macro|MT_ISARCHIVE_2150L
mdefine_line|#define MT_ISARCHIVE_2150L&t;0x08&t;/* Archive Viper 2150L */
DECL|macro|MT_ISARCHIVE_2060L
mdefine_line|#define MT_ISARCHIVE_2060L&t;0x09&t;/* Archive Viper 2060L */
DECL|macro|MT_ISARCHIVESC499
mdefine_line|#define MT_ISARCHIVESC499&t;0x0A&t;/* Archive SC-499 QIC-36 controller */
DECL|macro|MT_ISQIC02_ALL_FEATURES
mdefine_line|#define MT_ISQIC02_ALL_FEATURES&t;0x0F&t;/* Generic QIC-02 with all features */
DECL|macro|MT_ISWT5099EEN24
mdefine_line|#define MT_ISWT5099EEN24&t;0x11&t;/* Wangtek 5099-een24, 60MB, QIC-24 */
DECL|macro|MT_ISTEAC_MT2ST
mdefine_line|#define MT_ISTEAC_MT2ST&t;&t;0x12&t;/* Teac MT-2ST 155mb drive, Teac DC-1 card (Wangtek type) */
DECL|macro|MT_ISEVEREX_FT40A
mdefine_line|#define MT_ISEVEREX_FT40A&t;0x32&t;/* Everex FT40A (QIC-40) */
DECL|macro|MT_ISDDS1
mdefine_line|#define MT_ISDDS1&t;&t;0x51&t;/* DDS device without partitions */
DECL|macro|MT_ISDDS2
mdefine_line|#define MT_ISDDS2&t;&t;0x52&t;/* DDS device with partitions */
DECL|macro|MT_ISONSTREAM_SC
mdefine_line|#define MT_ISONSTREAM_SC        0x61   /* OnStream SCSI tape drives (SC-x0)&n;&t;&t;&t;&t;&t;  and SCSI emulated (DI, DP, USB) */
DECL|macro|MT_ISSCSI1
mdefine_line|#define MT_ISSCSI1&t;&t;0x71&t;/* Generic ANSI SCSI-1 tape unit */
DECL|macro|MT_ISSCSI2
mdefine_line|#define MT_ISSCSI2&t;&t;0x72&t;/* Generic ANSI SCSI-2 tape unit */
multiline_comment|/* QIC-40/80/3010/3020 ftape supported drives.&n; * 20bit vendor ID + 0x800000 (see ftape-vendors.h)&n; */
DECL|macro|MT_ISFTAPE_UNKNOWN
mdefine_line|#define MT_ISFTAPE_UNKNOWN&t;0x800000 /* obsolete */
DECL|macro|MT_ISFTAPE_FLAG
mdefine_line|#define MT_ISFTAPE_FLAG&t;0x800000
DECL|struct|mt_tape_info
r_struct
id|mt_tape_info
(brace
DECL|member|t_type
r_int
id|t_type
suffix:semicolon
multiline_comment|/* device type id (mt_type) */
DECL|member|t_name
r_char
op_star
id|t_name
suffix:semicolon
multiline_comment|/* descriptive name */
)brace
suffix:semicolon
DECL|macro|MT_TAPE_INFO
mdefine_line|#define MT_TAPE_INFO&t;{ &bslash;&n;&t;{MT_ISUNKNOWN,&t;&t;&quot;Unknown type of tape device&quot;}, &bslash;&n;&t;{MT_ISQIC02,&t;&t;&quot;Generic QIC-02 tape streamer&quot;}, &bslash;&n;&t;{MT_ISWT5150,&t;&t;&quot;Wangtek 5150, QIC-150&quot;}, &bslash;&n;&t;{MT_ISARCHIVE_5945L2,&t;&quot;Archive 5945L-2&quot;}, &bslash;&n;&t;{MT_ISCMSJ500,&t;&t;&quot;CMS Jumbo 500&quot;}, &bslash;&n;&t;{MT_ISTDC3610,&t;&t;&quot;Tandberg TDC 3610, QIC-24&quot;}, &bslash;&n;&t;{MT_ISARCHIVE_VP60I,&t;&quot;Archive VP60i, QIC-02&quot;}, &bslash;&n;&t;{MT_ISARCHIVE_2150L,&t;&quot;Archive Viper 2150L&quot;}, &bslash;&n;&t;{MT_ISARCHIVE_2060L,&t;&quot;Archive Viper 2060L&quot;}, &bslash;&n;&t;{MT_ISARCHIVESC499,&t;&quot;Archive SC-499 QIC-36 controller&quot;}, &bslash;&n;&t;{MT_ISQIC02_ALL_FEATURES, &quot;Generic QIC-02 tape, all features&quot;}, &bslash;&n;&t;{MT_ISWT5099EEN24,&t;&quot;Wangtek 5099-een24, 60MB&quot;}, &bslash;&n;&t;{MT_ISTEAC_MT2ST,&t;&quot;Teac MT-2ST 155mb data cassette drive&quot;}, &bslash;&n;&t;{MT_ISEVEREX_FT40A,&t;&quot;Everex FT40A, QIC-40&quot;}, &bslash;&n;&t;{MT_ISONSTREAM_SC,      &quot;OnStream SC-, DI-, DP-, or USB tape drive&quot;}, &bslash;&n;&t;{MT_ISSCSI1,&t;&t;&quot;Generic SCSI-1 tape&quot;}, &bslash;&n;&t;{MT_ISSCSI2,&t;&t;&quot;Generic SCSI-2 tape&quot;}, &bslash;&n;&t;{0, NULL} &bslash;&n;}
multiline_comment|/* structure for MTIOCPOS - mag tape get position command */
DECL|struct|mtpos
r_struct
id|mtpos
(brace
DECL|member|mt_blkno
r_int
id|mt_blkno
suffix:semicolon
multiline_comment|/* current block number */
)brace
suffix:semicolon
multiline_comment|/* structure for MTIOCGETCONFIG/MTIOCSETCONFIG primarily intended&n; * as an interim solution for QIC-02 until DDI is fully implemented.&n; */
DECL|struct|mtconfiginfo
r_struct
id|mtconfiginfo
(brace
DECL|member|mt_type
r_int
id|mt_type
suffix:semicolon
multiline_comment|/* drive type */
DECL|member|ifc_type
r_int
id|ifc_type
suffix:semicolon
multiline_comment|/* interface card type */
DECL|member|irqnr
r_int
r_int
id|irqnr
suffix:semicolon
multiline_comment|/* IRQ number to use */
DECL|member|dmanr
r_int
r_int
id|dmanr
suffix:semicolon
multiline_comment|/* DMA channel to use */
DECL|member|port
r_int
r_int
id|port
suffix:semicolon
multiline_comment|/* IO port base address */
DECL|member|debug
r_int
r_int
id|debug
suffix:semicolon
multiline_comment|/* debugging flags */
DECL|member|have_dens
r_int
id|have_dens
suffix:colon
l_int|1
suffix:semicolon
DECL|member|have_bsf
r_int
id|have_bsf
suffix:colon
l_int|1
suffix:semicolon
DECL|member|have_fsr
r_int
id|have_fsr
suffix:colon
l_int|1
suffix:semicolon
DECL|member|have_bsr
r_int
id|have_bsr
suffix:colon
l_int|1
suffix:semicolon
DECL|member|have_eod
r_int
id|have_eod
suffix:colon
l_int|1
suffix:semicolon
DECL|member|have_seek
r_int
id|have_seek
suffix:colon
l_int|1
suffix:semicolon
DECL|member|have_tell
r_int
id|have_tell
suffix:colon
l_int|1
suffix:semicolon
DECL|member|have_ras1
r_int
id|have_ras1
suffix:colon
l_int|1
suffix:semicolon
DECL|member|have_ras2
r_int
id|have_ras2
suffix:colon
l_int|1
suffix:semicolon
DECL|member|have_ras3
r_int
id|have_ras3
suffix:colon
l_int|1
suffix:semicolon
DECL|member|have_qfa
r_int
id|have_qfa
suffix:colon
l_int|1
suffix:semicolon
DECL|member|pad1
r_int
id|pad1
suffix:colon
l_int|5
suffix:semicolon
DECL|member|reserved
r_char
id|reserved
(braket
l_int|10
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*  structure for MTIOCVOLINFO, query information about the volume&n; *  currently positioned at (zftape)&n; */
DECL|struct|mtvolinfo
r_struct
id|mtvolinfo
(brace
DECL|member|mt_volno
r_int
r_int
id|mt_volno
suffix:semicolon
multiline_comment|/* vol-number */
DECL|member|mt_blksz
r_int
r_int
id|mt_blksz
suffix:semicolon
multiline_comment|/* blocksize used when recording */
DECL|member|mt_rawsize
r_int
r_int
id|mt_rawsize
suffix:semicolon
multiline_comment|/* raw tape space consumed, in kb */
DECL|member|mt_size
r_int
r_int
id|mt_size
suffix:semicolon
multiline_comment|/* volume size after decompression, in kb */
DECL|member|mt_cmpr
r_int
r_int
id|mt_cmpr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* this volume has been compressed */
)brace
suffix:semicolon
multiline_comment|/* raw access to a floppy drive, read and write an arbitrary segment.&n; * For ftape/zftape to support formatting etc.&n; */
DECL|macro|MT_FT_RD_SINGLE
mdefine_line|#define MT_FT_RD_SINGLE  0
DECL|macro|MT_FT_RD_AHEAD
mdefine_line|#define MT_FT_RD_AHEAD   1
DECL|macro|MT_FT_WR_ASYNC
mdefine_line|#define MT_FT_WR_ASYNC   0 /* start tape only when all buffers are full     */
DECL|macro|MT_FT_WR_MULTI
mdefine_line|#define MT_FT_WR_MULTI   1 /* start tape, continue until buffers are empty  */
DECL|macro|MT_FT_WR_SINGLE
mdefine_line|#define MT_FT_WR_SINGLE  2 /* write a single segment and stop afterwards    */
DECL|macro|MT_FT_WR_DELETE
mdefine_line|#define MT_FT_WR_DELETE  3 /* write deleted data marks, one segment at time */
DECL|struct|mtftseg
r_struct
id|mtftseg
(brace
DECL|member|mt_segno
r_int
id|mt_segno
suffix:semicolon
multiline_comment|/* the segment to read or write */
DECL|member|mt_mode
r_int
id|mt_mode
suffix:semicolon
multiline_comment|/* modes for read/write (sync/async etc.) */
DECL|member|mt_result
r_int
id|mt_result
suffix:semicolon
multiline_comment|/* result of r/w request, not of the ioctl */
DECL|member|mt_data
r_void
op_star
id|mt_data
suffix:semicolon
multiline_comment|/* User space buffer: must be 29kb */
)brace
suffix:semicolon
multiline_comment|/* get tape capacity (ftape/zftape)&n; */
DECL|struct|mttapesize
r_struct
id|mttapesize
(brace
DECL|member|mt_capacity
r_int
r_int
id|mt_capacity
suffix:semicolon
multiline_comment|/* entire, uncompressed capacity &n;&t;&t;&t;&t;    * of a cartridge&n;&t;&t;&t;&t;    */
DECL|member|mt_used
r_int
r_int
id|mt_used
suffix:semicolon
multiline_comment|/* what has been used so far, raw &n;&t;&t;&t;&t;    * uncompressed amount&n;&t;&t;&t;&t;    */
)brace
suffix:semicolon
multiline_comment|/*  possible values of the ftfmt_op field&n; */
DECL|macro|FTFMT_SET_PARMS
mdefine_line|#define FTFMT_SET_PARMS&t;&t;1 /* set software parms */
DECL|macro|FTFMT_GET_PARMS
mdefine_line|#define FTFMT_GET_PARMS&t;&t;2 /* get software parms */
DECL|macro|FTFMT_FORMAT_TRACK
mdefine_line|#define FTFMT_FORMAT_TRACK&t;3 /* start formatting a tape track   */
DECL|macro|FTFMT_STATUS
mdefine_line|#define FTFMT_STATUS&t;&t;4 /* monitor formatting a tape track */
DECL|macro|FTFMT_VERIFY
mdefine_line|#define FTFMT_VERIFY&t;&t;5 /* verify the given segment        */
DECL|struct|ftfmtparms
r_struct
id|ftfmtparms
(brace
DECL|member|ft_qicstd
r_int
r_char
id|ft_qicstd
suffix:semicolon
multiline_comment|/* QIC-40/QIC-80/QIC-3010/QIC-3020 */
DECL|member|ft_fmtcode
r_int
r_char
id|ft_fmtcode
suffix:semicolon
multiline_comment|/* Refer to the QIC specs */
DECL|member|ft_fhm
r_int
r_char
id|ft_fhm
suffix:semicolon
multiline_comment|/* floppy head max */
DECL|member|ft_ftm
r_int
r_char
id|ft_ftm
suffix:semicolon
multiline_comment|/* floppy track max */
DECL|member|ft_spt
r_int
r_int
id|ft_spt
suffix:semicolon
multiline_comment|/* segments per track */
DECL|member|ft_tpc
r_int
r_int
id|ft_tpc
suffix:semicolon
multiline_comment|/* tracks per cartridge */
)brace
suffix:semicolon
DECL|struct|ftfmttrack
r_struct
id|ftfmttrack
(brace
DECL|member|ft_track
r_int
r_int
id|ft_track
suffix:semicolon
multiline_comment|/* track to format */
DECL|member|ft_gap3
r_int
r_char
id|ft_gap3
suffix:semicolon
multiline_comment|/* size of gap3, for FORMAT_TRK */
)brace
suffix:semicolon
DECL|struct|ftfmtstatus
r_struct
id|ftfmtstatus
(brace
DECL|member|ft_segment
r_int
r_int
id|ft_segment
suffix:semicolon
multiline_comment|/* segment currently being formatted */
)brace
suffix:semicolon
DECL|struct|ftfmtverify
r_struct
id|ftfmtverify
(brace
DECL|member|ft_segment
r_int
r_int
id|ft_segment
suffix:semicolon
multiline_comment|/* segment to verify */
DECL|member|ft_bsm
r_int
r_int
id|ft_bsm
suffix:semicolon
multiline_comment|/* bsm as result of VERIFY cmd */
)brace
suffix:semicolon
DECL|struct|mtftformat
r_struct
id|mtftformat
(brace
DECL|member|fmt_op
r_int
r_int
id|fmt_op
suffix:semicolon
multiline_comment|/* operation to perform */
DECL|union|fmt_arg
r_union
id|fmt_arg
(brace
DECL|member|fmt_parms
r_struct
id|ftfmtparms
id|fmt_parms
suffix:semicolon
multiline_comment|/* format parameters */
DECL|member|fmt_track
r_struct
id|ftfmttrack
id|fmt_track
suffix:semicolon
multiline_comment|/* ctrl while formatting */
DECL|member|fmt_status
r_struct
id|ftfmtstatus
id|fmt_status
suffix:semicolon
DECL|member|fmt_verify
r_struct
id|ftfmtverify
id|fmt_verify
suffix:semicolon
multiline_comment|/* for verifying */
DECL|member|fmt_arg
)brace
id|fmt_arg
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|mtftcmd
r_struct
id|mtftcmd
(brace
DECL|member|ft_wait_before
r_int
r_int
id|ft_wait_before
suffix:semicolon
multiline_comment|/* timeout to wait for drive to get ready &n;&t;&t;&t;&t;      * before command is sent. Milliseconds&n;&t;&t;&t;&t;      */
DECL|member|ft_cmd
id|qic117_cmd_t
id|ft_cmd
suffix:semicolon
multiline_comment|/* command to send */
DECL|member|ft_parm_cnt
r_int
r_char
id|ft_parm_cnt
suffix:semicolon
multiline_comment|/* zero: no parm is sent. */
DECL|member|ft_parms
r_int
r_char
id|ft_parms
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* parameter(s) to send to&n;&t;&t;&t;&t;      * the drive. The parms are nibbles&n;&t;&t;&t;&t;      * driver sends cmd + 2 step pulses */
DECL|member|ft_result_bits
r_int
r_int
id|ft_result_bits
suffix:semicolon
multiline_comment|/* if non zero, number of bits&n;&t;&t;&t;&t;      *&t;returned by the tape drive&n;&t;&t;&t;&t;      */
DECL|member|ft_result
r_int
r_int
id|ft_result
suffix:semicolon
multiline_comment|/* the result returned by the tape drive*/
DECL|member|ft_wait_after
r_int
r_int
id|ft_wait_after
suffix:semicolon
multiline_comment|/* timeout to wait for drive to get ready&n;&t;&t;&t;&t;      * after command is sent. 0: don&squot;t wait */
DECL|member|ft_status
r_int
id|ft_status
suffix:semicolon
multiline_comment|/* status returned by ready wait&n;&t;&t;&t;&t;      * undefined if timeout was 0.&n;&t;&t;&t;&t;      */
DECL|member|ft_error
r_int
id|ft_error
suffix:semicolon
multiline_comment|/* error code if error status was set by &n;&t;&t;&t;&t;      * command&n;&t;&t;&t;&t;      */
)brace
suffix:semicolon
multiline_comment|/* mag tape io control commands */
DECL|macro|MTIOCTOP
mdefine_line|#define&t;MTIOCTOP&t;_IOW(&squot;m&squot;, 1, struct mtop)&t;/* do a mag tape op */
DECL|macro|MTIOCGET
mdefine_line|#define&t;MTIOCGET&t;_IOR(&squot;m&squot;, 2, struct mtget)&t;/* get tape status */
DECL|macro|MTIOCPOS
mdefine_line|#define&t;MTIOCPOS&t;_IOR(&squot;m&squot;, 3, struct mtpos)&t;/* get tape position */
multiline_comment|/* The next two are used by the QIC-02 driver for runtime reconfiguration.&n; * See tpqic02.h for struct mtconfiginfo.&n; */
DECL|macro|MTIOCGETCONFIG
mdefine_line|#define&t;MTIOCGETCONFIG&t;_IOR(&squot;m&squot;, 4, struct mtconfiginfo) /* get tape config */
DECL|macro|MTIOCSETCONFIG
mdefine_line|#define&t;MTIOCSETCONFIG&t;_IOW(&squot;m&squot;, 5, struct mtconfiginfo) /* set tape config */
multiline_comment|/* the next six are used by the floppy ftape drivers and its frontends&n; * sorry, but MTIOCTOP commands are write only.&n; */
DECL|macro|MTIOCRDFTSEG
mdefine_line|#define&t;MTIOCRDFTSEG    _IOWR(&squot;m&squot;, 6, struct mtftseg)  /* read a segment */
DECL|macro|MTIOCWRFTSEG
mdefine_line|#define&t;MTIOCWRFTSEG    _IOWR(&squot;m&squot;, 7, struct mtftseg)   /* write a segment */
DECL|macro|MTIOCVOLINFO
mdefine_line|#define MTIOCVOLINFO&t;_IOR(&squot;m&squot;,  8, struct mtvolinfo) /* info about volume */
DECL|macro|MTIOCGETSIZE
mdefine_line|#define MTIOCGETSIZE    _IOR(&squot;m&squot;,  9, struct mttapesize)/* get cartridge size*/
DECL|macro|MTIOCFTFORMAT
mdefine_line|#define MTIOCFTFORMAT   _IOWR(&squot;m&squot;, 10, struct mtftformat) /* format ftape */
DECL|macro|MTIOCFTCMD
mdefine_line|#define MTIOCFTCMD&t;_IOWR(&squot;m&squot;, 11, struct mtftcmd) /* send QIC-117 cmd */
multiline_comment|/* Generic Mag Tape (device independent) status macros for examining&n; * mt_gstat -- HP-UX compatible.&n; * There is room for more generic status bits here, but I don&squot;t&n; * know which of them are reserved. At least three or so should&n; * be added to make this really useful.&n; */
DECL|macro|GMT_EOF
mdefine_line|#define GMT_EOF(x)              ((x) &amp; 0x80000000)
DECL|macro|GMT_BOT
mdefine_line|#define GMT_BOT(x)              ((x) &amp; 0x40000000)
DECL|macro|GMT_EOT
mdefine_line|#define GMT_EOT(x)              ((x) &amp; 0x20000000)
DECL|macro|GMT_SM
mdefine_line|#define GMT_SM(x)               ((x) &amp; 0x10000000)  /* DDS setmark */
DECL|macro|GMT_EOD
mdefine_line|#define GMT_EOD(x)              ((x) &amp; 0x08000000)  /* DDS EOD */
DECL|macro|GMT_WR_PROT
mdefine_line|#define GMT_WR_PROT(x)          ((x) &amp; 0x04000000)
multiline_comment|/* #define GMT_ ? &t;&t;((x) &amp; 0x02000000) */
DECL|macro|GMT_ONLINE
mdefine_line|#define GMT_ONLINE(x)           ((x) &amp; 0x01000000)
DECL|macro|GMT_D_6250
mdefine_line|#define GMT_D_6250(x)           ((x) &amp; 0x00800000)
DECL|macro|GMT_D_1600
mdefine_line|#define GMT_D_1600(x)           ((x) &amp; 0x00400000)
DECL|macro|GMT_D_800
mdefine_line|#define GMT_D_800(x)            ((x) &amp; 0x00200000)
multiline_comment|/* #define GMT_ ? &t;&t;((x) &amp; 0x00100000) */
multiline_comment|/* #define GMT_ ? &t;&t;((x) &amp; 0x00080000) */
DECL|macro|GMT_DR_OPEN
mdefine_line|#define GMT_DR_OPEN(x)          ((x) &amp; 0x00040000)  /* door open (no tape) */
multiline_comment|/* #define GMT_ ? &t;&t;((x) &amp; 0x00020000) */
DECL|macro|GMT_IM_REP_EN
mdefine_line|#define GMT_IM_REP_EN(x)        ((x) &amp; 0x00010000)  /* immediate report mode */
DECL|macro|GMT_CLN
mdefine_line|#define GMT_CLN(x)              ((x) &amp; 0x00008000)  /* cleaning requested */
multiline_comment|/* 15 generic status bits unused */
multiline_comment|/* SCSI-tape specific definitions */
multiline_comment|/* Bitfield shifts in the status  */
DECL|macro|MT_ST_BLKSIZE_SHIFT
mdefine_line|#define MT_ST_BLKSIZE_SHIFT&t;0
DECL|macro|MT_ST_BLKSIZE_MASK
mdefine_line|#define MT_ST_BLKSIZE_MASK&t;0xffffff
DECL|macro|MT_ST_DENSITY_SHIFT
mdefine_line|#define MT_ST_DENSITY_SHIFT&t;24
DECL|macro|MT_ST_DENSITY_MASK
mdefine_line|#define MT_ST_DENSITY_MASK&t;0xff000000
DECL|macro|MT_ST_SOFTERR_SHIFT
mdefine_line|#define MT_ST_SOFTERR_SHIFT&t;0
DECL|macro|MT_ST_SOFTERR_MASK
mdefine_line|#define MT_ST_SOFTERR_MASK&t;0xffff
multiline_comment|/* Bitfields for the MTSETDRVBUFFER ioctl */
DECL|macro|MT_ST_OPTIONS
mdefine_line|#define MT_ST_OPTIONS&t;&t;0xf0000000
DECL|macro|MT_ST_BOOLEANS
mdefine_line|#define MT_ST_BOOLEANS&t;&t;0x10000000
DECL|macro|MT_ST_SETBOOLEANS
mdefine_line|#define MT_ST_SETBOOLEANS&t;0x30000000
DECL|macro|MT_ST_CLEARBOOLEANS
mdefine_line|#define MT_ST_CLEARBOOLEANS&t;0x40000000
DECL|macro|MT_ST_WRITE_THRESHOLD
mdefine_line|#define MT_ST_WRITE_THRESHOLD&t;0x20000000
DECL|macro|MT_ST_DEF_BLKSIZE
mdefine_line|#define MT_ST_DEF_BLKSIZE&t;0x50000000
DECL|macro|MT_ST_DEF_OPTIONS
mdefine_line|#define MT_ST_DEF_OPTIONS&t;0x60000000
DECL|macro|MT_ST_TIMEOUTS
mdefine_line|#define MT_ST_TIMEOUTS&t;&t;0x70000000
DECL|macro|MT_ST_SET_TIMEOUT
mdefine_line|#define MT_ST_SET_TIMEOUT&t;(MT_ST_TIMEOUTS | 0x000000)
DECL|macro|MT_ST_SET_LONG_TIMEOUT
mdefine_line|#define MT_ST_SET_LONG_TIMEOUT&t;(MT_ST_TIMEOUTS | 0x100000)
DECL|macro|MT_ST_SET_CLN
mdefine_line|#define MT_ST_SET_CLN&t;&t;0x80000000
DECL|macro|MT_ST_BUFFER_WRITES
mdefine_line|#define MT_ST_BUFFER_WRITES&t;0x1
DECL|macro|MT_ST_ASYNC_WRITES
mdefine_line|#define MT_ST_ASYNC_WRITES&t;0x2
DECL|macro|MT_ST_READ_AHEAD
mdefine_line|#define MT_ST_READ_AHEAD&t;0x4
DECL|macro|MT_ST_DEBUGGING
mdefine_line|#define MT_ST_DEBUGGING&t;&t;0x8
DECL|macro|MT_ST_TWO_FM
mdefine_line|#define MT_ST_TWO_FM&t;&t;0x10
DECL|macro|MT_ST_FAST_MTEOM
mdefine_line|#define MT_ST_FAST_MTEOM&t;0x20
DECL|macro|MT_ST_AUTO_LOCK
mdefine_line|#define MT_ST_AUTO_LOCK&t;&t;0x40
DECL|macro|MT_ST_DEF_WRITES
mdefine_line|#define MT_ST_DEF_WRITES&t;0x80
DECL|macro|MT_ST_CAN_BSR
mdefine_line|#define MT_ST_CAN_BSR&t;&t;0x100
DECL|macro|MT_ST_NO_BLKLIMS
mdefine_line|#define MT_ST_NO_BLKLIMS&t;0x200
DECL|macro|MT_ST_CAN_PARTITIONS
mdefine_line|#define MT_ST_CAN_PARTITIONS    0x400
DECL|macro|MT_ST_SCSI2LOGICAL
mdefine_line|#define MT_ST_SCSI2LOGICAL      0x800
DECL|macro|MT_ST_SYSV
mdefine_line|#define MT_ST_SYSV              0x1000
DECL|macro|MT_ST_NOWAIT
mdefine_line|#define MT_ST_NOWAIT            0x2000
multiline_comment|/* The mode parameters to be controlled. Parameter chosen with bits 20-28 */
DECL|macro|MT_ST_CLEAR_DEFAULT
mdefine_line|#define MT_ST_CLEAR_DEFAULT&t;0xfffff
DECL|macro|MT_ST_DEF_DENSITY
mdefine_line|#define MT_ST_DEF_DENSITY&t;(MT_ST_DEF_OPTIONS | 0x100000)
DECL|macro|MT_ST_DEF_COMPRESSION
mdefine_line|#define MT_ST_DEF_COMPRESSION&t;(MT_ST_DEF_OPTIONS | 0x200000)
DECL|macro|MT_ST_DEF_DRVBUFFER
mdefine_line|#define MT_ST_DEF_DRVBUFFER&t;(MT_ST_DEF_OPTIONS | 0x300000)
multiline_comment|/* The offset for the arguments for the special HP changer load command. */
DECL|macro|MT_ST_HPLOADER_OFFSET
mdefine_line|#define MT_ST_HPLOADER_OFFSET 10000
macro_line|#endif /* _LINUX_MTIO_H */
eof
