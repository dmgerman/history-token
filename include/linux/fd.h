macro_line|#ifndef _LINUX_FD_H
DECL|macro|_LINUX_FD_H
mdefine_line|#define _LINUX_FD_H
macro_line|#include &lt;linux/ioctl.h&gt;
multiline_comment|/* New file layout: Now the ioctl definitions immediately follow the&n; * definitions of the structures that they use */
multiline_comment|/*&n; * Geometry&n; */
DECL|struct|floppy_struct
r_struct
id|floppy_struct
(brace
DECL|member|size
r_int
r_int
id|size
comma
multiline_comment|/* nr of sectors total */
DECL|member|sect
id|sect
comma
multiline_comment|/* sectors per track */
DECL|member|head
id|head
comma
multiline_comment|/* nr of heads */
DECL|member|track
id|track
comma
multiline_comment|/* nr of tracks */
DECL|member|stretch
id|stretch
suffix:semicolon
multiline_comment|/* !=0 means double track steps */
DECL|macro|FD_STRETCH
mdefine_line|#define FD_STRETCH 1
DECL|macro|FD_SWAPSIDES
mdefine_line|#define FD_SWAPSIDES 2
DECL|member|gap
r_int
r_char
id|gap
comma
multiline_comment|/* gap1 size */
DECL|member|rate
id|rate
comma
multiline_comment|/* data rate. |= 0x40 for perpendicular */
DECL|macro|FD_2M
mdefine_line|#define FD_2M 0x4
DECL|macro|FD_SIZECODEMASK
mdefine_line|#define FD_SIZECODEMASK 0x38
DECL|macro|FD_SIZECODE
mdefine_line|#define FD_SIZECODE(floppy) (((((floppy)-&gt;rate&amp;FD_SIZECODEMASK)&gt;&gt; 3)+ 2) %8)
DECL|macro|FD_SECTSIZE
mdefine_line|#define FD_SECTSIZE(floppy) ( (floppy)-&gt;rate &amp; FD_2M ? &bslash;&n;&t;&t;&t;     512 : 128 &lt;&lt; FD_SIZECODE(floppy) )
DECL|macro|FD_PERP
mdefine_line|#define FD_PERP 0x40
DECL|member|spec1
id|spec1
comma
multiline_comment|/* stepping rate, head unload time */
DECL|member|fmt_gap
id|fmt_gap
suffix:semicolon
multiline_comment|/* gap2 size */
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/* used only for predefined formats */
)brace
suffix:semicolon
multiline_comment|/* commands needing write access have 0x40 set */
multiline_comment|/* commands needing super user access have 0x80 set */
DECL|macro|FDCLRPRM
mdefine_line|#define FDCLRPRM _IO(2, 0x41)
multiline_comment|/* clear user-defined parameters */
DECL|macro|FDSETPRM
mdefine_line|#define FDSETPRM _IOW(2, 0x42, struct floppy_struct) 
DECL|macro|FDSETMEDIAPRM
mdefine_line|#define FDSETMEDIAPRM FDSETPRM
multiline_comment|/* set user-defined parameters for current media */
DECL|macro|FDDEFPRM
mdefine_line|#define FDDEFPRM _IOW(2, 0x43, struct floppy_struct) 
DECL|macro|FDGETPRM
mdefine_line|#define FDGETPRM _IOR(2, 0x04, struct floppy_struct)
DECL|macro|FDDEFMEDIAPRM
mdefine_line|#define FDDEFMEDIAPRM FDDEFPRM
DECL|macro|FDGETMEDIAPRM
mdefine_line|#define FDGETMEDIAPRM FDGETPRM
multiline_comment|/* set/get disk parameters */
DECL|macro|FDMSGON
mdefine_line|#define&t;FDMSGON  _IO(2,0x45)
DECL|macro|FDMSGOFF
mdefine_line|#define&t;FDMSGOFF _IO(2,0x46)
multiline_comment|/* issue/don&squot;t issue kernel messages on media type change */
multiline_comment|/* &n; * Formatting (obsolete)&n; */
DECL|macro|FD_FILL_BYTE
mdefine_line|#define FD_FILL_BYTE 0xF6 /* format fill byte. */
DECL|struct|format_descr
r_struct
id|format_descr
(brace
DECL|member|device
DECL|member|head
DECL|member|track
r_int
r_int
id|device
comma
id|head
comma
id|track
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|FDFMTBEG
mdefine_line|#define FDFMTBEG _IO(2,0x47)
multiline_comment|/* begin formatting a disk */
DECL|macro|FDFMTTRK
mdefine_line|#define&t;FDFMTTRK _IOW(2,0x48, struct format_descr)
multiline_comment|/* format the specified track */
DECL|macro|FDFMTEND
mdefine_line|#define FDFMTEND _IO(2,0x49)
multiline_comment|/* end formatting a disk */
multiline_comment|/*&n; * Error thresholds&n; */
DECL|struct|floppy_max_errors
r_struct
id|floppy_max_errors
(brace
r_int
r_int
DECL|member|abort
m_abort
comma
multiline_comment|/* number of errors to be reached before aborting */
DECL|member|read_track
id|read_track
comma
multiline_comment|/* maximal number of errors permitted to read an&n;&t;&t;       * entire track at once */
DECL|member|reset
id|reset
comma
multiline_comment|/* maximal number of errors before a reset is tried */
DECL|member|recal
id|recal
comma
multiline_comment|/* maximal number of errors before a recalibrate is&n;&t;&t;       * tried */
multiline_comment|/*&n;&t;   * Threshold for reporting FDC errors to the console.&n;&t;   * Setting this to zero may flood your screen when using&n;&t;   * ultra cheap floppies ;-)&n;&t;   */
DECL|member|reporting
id|reporting
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|FDSETEMSGTRESH
mdefine_line|#define FDSETEMSGTRESH&t;_IO(2,0x4a)
multiline_comment|/* set fdc error reporting threshold */
DECL|macro|FDFLUSH
mdefine_line|#define FDFLUSH  _IO(2,0x4b)
multiline_comment|/* flush buffers for media; either for verifying media, or for&n; * handling a media change without closing the file descriptor */
DECL|macro|FDSETMAXERRS
mdefine_line|#define FDSETMAXERRS _IOW(2, 0x4c, struct floppy_max_errors)
DECL|macro|FDGETMAXERRS
mdefine_line|#define FDGETMAXERRS _IOR(2, 0x0e, struct floppy_max_errors)
multiline_comment|/* set/get abortion and read_track threshold. See also floppy_drive_params&n; * structure */
DECL|typedef|floppy_drive_name
r_typedef
r_char
id|floppy_drive_name
(braket
l_int|16
)braket
suffix:semicolon
DECL|macro|FDGETDRVTYP
mdefine_line|#define FDGETDRVTYP _IOR(2, 0x0f, floppy_drive_name)
multiline_comment|/* get drive type: 5 1/4 or 3 1/2 */
multiline_comment|/*&n; * Drive parameters (user modifiable)&n; */
DECL|struct|floppy_drive_params
r_struct
id|floppy_drive_params
(brace
DECL|member|cmos
r_int
r_char
id|cmos
suffix:semicolon
multiline_comment|/* CMOS type */
multiline_comment|/* Spec2 is (HLD&lt;&lt;1 | ND), where HLD is head load time (1=2ms, 2=4 ms &n;&t; * etc) and ND is set means no DMA. Hardcoded to 6 (HLD=6ms, use DMA).&n;&t; */
DECL|member|max_dtr
r_int
r_int
id|max_dtr
suffix:semicolon
multiline_comment|/* Step rate, usec */
DECL|member|hlt
r_int
r_int
id|hlt
suffix:semicolon
multiline_comment|/* Head load/settle time, msec */
DECL|member|hut
r_int
r_int
id|hut
suffix:semicolon
multiline_comment|/* Head unload time (remnant of &n;&t;&t;&t;&t;&t; * 8&quot; drives) */
DECL|member|srt
r_int
r_int
id|srt
suffix:semicolon
multiline_comment|/* Step rate, usec */
DECL|member|spinup
r_int
r_int
id|spinup
suffix:semicolon
multiline_comment|/* time needed for spinup (expressed&n;&t;&t;&t;&t;&t; * in jiffies) */
DECL|member|spindown
r_int
r_int
id|spindown
suffix:semicolon
multiline_comment|/* timeout needed for spindown */
DECL|member|spindown_offset
r_int
r_char
id|spindown_offset
suffix:semicolon
multiline_comment|/* decides in which position the disk&n;&t;&t;&t;&t;&t; * will stop */
DECL|member|select_delay
r_int
r_char
id|select_delay
suffix:semicolon
multiline_comment|/* delay to wait after select */
DECL|member|rps
r_int
r_char
id|rps
suffix:semicolon
multiline_comment|/* rotations per second */
DECL|member|tracks
r_int
r_char
id|tracks
suffix:semicolon
multiline_comment|/* maximum number of tracks */
DECL|member|timeout
r_int
r_int
id|timeout
suffix:semicolon
multiline_comment|/* timeout for interrupt requests */
DECL|member|interleave_sect
r_int
r_char
id|interleave_sect
suffix:semicolon
multiline_comment|/* if there are more sectors, use &n;&t;&t;&t;&t;&t; * interleave */
DECL|member|max_errors
r_struct
id|floppy_max_errors
id|max_errors
suffix:semicolon
DECL|member|flags
r_char
id|flags
suffix:semicolon
multiline_comment|/* various flags, including ftd_msg */
multiline_comment|/*&n; * Announce successful media type detection and media information loss after&n; * disk changes.&n; * Also used to enable/disable printing of overrun warnings.&n; */
DECL|macro|FTD_MSG
mdefine_line|#define FTD_MSG 0x10
DECL|macro|FD_BROKEN_DCL
mdefine_line|#define FD_BROKEN_DCL 0x20
DECL|macro|FD_DEBUG
mdefine_line|#define FD_DEBUG 0x02
DECL|macro|FD_SILENT_DCL_CLEAR
mdefine_line|#define FD_SILENT_DCL_CLEAR 0x4
DECL|macro|FD_INVERTED_DCL
mdefine_line|#define FD_INVERTED_DCL 0x80 /* must be 0x80, because of hardware &n;&t;&t;&t;&t;considerations */
DECL|member|read_track
r_char
id|read_track
suffix:semicolon
multiline_comment|/* use readtrack during probing? */
multiline_comment|/*&n; * Auto-detection. Each drive type has eight formats which are&n; * used in succession to try to read the disk. If the FDC cannot lock onto&n; * the disk, the next format is tried. This uses the variable &squot;probing&squot;.&n; */
DECL|member|autodetect
r_int
id|autodetect
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* autodetected formats */
DECL|member|checkfreq
r_int
id|checkfreq
suffix:semicolon
multiline_comment|/* how often should the drive be checked for disk &n;&t;&t;&t;* changes */
DECL|member|native_format
r_int
id|native_format
suffix:semicolon
multiline_comment|/* native format of this drive */
)brace
suffix:semicolon
r_enum
(brace
DECL|enumerator|FD_NEED_TWADDLE_BIT
id|FD_NEED_TWADDLE_BIT
comma
multiline_comment|/* more magic */
DECL|enumerator|FD_VERIFY_BIT
id|FD_VERIFY_BIT
comma
multiline_comment|/* inquire for write protection */
DECL|enumerator|FD_DISK_NEWCHANGE_BIT
id|FD_DISK_NEWCHANGE_BIT
comma
multiline_comment|/* change detected, and no action undertaken yet&n;&t;&t;&t;&t; * to clear media change status */
DECL|enumerator|FD_UNUSED_BIT
id|FD_UNUSED_BIT
comma
DECL|enumerator|FD_DISK_CHANGED_BIT
id|FD_DISK_CHANGED_BIT
comma
multiline_comment|/* disk has been changed since last i/o */
DECL|enumerator|FD_DISK_WRITABLE_BIT
id|FD_DISK_WRITABLE_BIT
multiline_comment|/* disk is writable */
)brace
suffix:semicolon
DECL|macro|FDSETDRVPRM
mdefine_line|#define FDSETDRVPRM _IOW(2, 0x90, struct floppy_drive_params)
DECL|macro|FDGETDRVPRM
mdefine_line|#define FDGETDRVPRM _IOR(2, 0x11, struct floppy_drive_params)
multiline_comment|/* set/get drive parameters */
multiline_comment|/*&n; * Current drive state (not directly modifiable by user, readonly)&n; */
DECL|struct|floppy_drive_struct
r_struct
id|floppy_drive_struct
(brace
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* values for these flags */
DECL|macro|FD_NEED_TWADDLE
mdefine_line|#define FD_NEED_TWADDLE (1 &lt;&lt; FD_NEED_TWADDLE_BIT)
DECL|macro|FD_VERIFY
mdefine_line|#define FD_VERIFY (1 &lt;&lt; FD_VERIFY_BIT)
DECL|macro|FD_DISK_NEWCHANGE
mdefine_line|#define FD_DISK_NEWCHANGE (1 &lt;&lt; FD_DISK_NEWCHANGE_BIT)
DECL|macro|FD_DISK_CHANGED
mdefine_line|#define FD_DISK_CHANGED (1 &lt;&lt; FD_DISK_CHANGED_BIT)
DECL|macro|FD_DISK_WRITABLE
mdefine_line|#define FD_DISK_WRITABLE (1 &lt;&lt; FD_DISK_WRITABLE_BIT)
DECL|member|spinup_date
r_int
r_int
id|spinup_date
suffix:semicolon
DECL|member|select_date
r_int
r_int
id|select_date
suffix:semicolon
DECL|member|first_read_date
r_int
r_int
id|first_read_date
suffix:semicolon
DECL|member|probed_format
r_int
id|probed_format
suffix:semicolon
DECL|member|track
r_int
id|track
suffix:semicolon
multiline_comment|/* current track */
DECL|member|maxblock
r_int
id|maxblock
suffix:semicolon
multiline_comment|/* id of highest block read */
DECL|member|maxtrack
r_int
id|maxtrack
suffix:semicolon
multiline_comment|/* id of highest half track read */
DECL|member|generation
r_int
id|generation
suffix:semicolon
multiline_comment|/* how many diskchanges? */
multiline_comment|/*&n; * (User-provided) media information is _not_ discarded after a media change&n; * if the corresponding keep_data flag is non-zero. Positive values are&n; * decremented after each probe.&n; */
DECL|member|keep_data
r_int
id|keep_data
suffix:semicolon
multiline_comment|/* Prevent &quot;aliased&quot; accesses. */
DECL|member|fd_ref
r_int
id|fd_ref
suffix:semicolon
DECL|member|fd_device
r_int
id|fd_device
suffix:semicolon
DECL|member|last_checked
r_int
r_int
id|last_checked
suffix:semicolon
multiline_comment|/* when was the drive last checked for a disk &n;&t;&t;&t;   * change? */
DECL|member|dmabuf
r_char
op_star
id|dmabuf
suffix:semicolon
DECL|member|bufblocks
r_int
id|bufblocks
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|FDGETDRVSTAT
mdefine_line|#define FDGETDRVSTAT _IOR(2, 0x12, struct floppy_drive_struct)
DECL|macro|FDPOLLDRVSTAT
mdefine_line|#define FDPOLLDRVSTAT _IOR(2, 0x13, struct floppy_drive_struct)
multiline_comment|/* get drive state: GET returns the cached state, POLL polls for new state */
multiline_comment|/*&n; * reset FDC&n; */
DECL|enum|reset_mode
r_enum
id|reset_mode
(brace
DECL|enumerator|FD_RESET_IF_NEEDED
id|FD_RESET_IF_NEEDED
comma
multiline_comment|/* reset only if the reset flags is set */
DECL|enumerator|FD_RESET_IF_RAWCMD
id|FD_RESET_IF_RAWCMD
comma
multiline_comment|/* obsolete */
DECL|enumerator|FD_RESET_ALWAYS
id|FD_RESET_ALWAYS
multiline_comment|/* reset always */
)brace
suffix:semicolon
DECL|macro|FDRESET
mdefine_line|#define FDRESET _IO(2, 0x54)
multiline_comment|/*&n; * FDC state&n; */
DECL|struct|floppy_fdc_state
r_struct
id|floppy_fdc_state
(brace
DECL|member|spec1
r_int
id|spec1
suffix:semicolon
multiline_comment|/* spec1 value last used */
DECL|member|spec2
r_int
id|spec2
suffix:semicolon
multiline_comment|/* spec2 value last used */
DECL|member|dtr
r_int
id|dtr
suffix:semicolon
DECL|member|version
r_int
r_char
id|version
suffix:semicolon
multiline_comment|/* FDC version code */
DECL|member|dor
r_int
r_char
id|dor
suffix:semicolon
DECL|member|address
r_int
r_int
id|address
suffix:semicolon
multiline_comment|/* io address */
DECL|member|rawcmd
r_int
r_int
id|rawcmd
suffix:colon
l_int|2
suffix:semicolon
DECL|member|reset
r_int
r_int
id|reset
suffix:colon
l_int|1
suffix:semicolon
DECL|member|need_configure
r_int
r_int
id|need_configure
suffix:colon
l_int|1
suffix:semicolon
DECL|member|perp_mode
r_int
r_int
id|perp_mode
suffix:colon
l_int|2
suffix:semicolon
DECL|member|has_fifo
r_int
r_int
id|has_fifo
suffix:colon
l_int|1
suffix:semicolon
DECL|member|driver_version
r_int
r_int
id|driver_version
suffix:semicolon
multiline_comment|/* version code for floppy driver */
DECL|macro|FD_DRIVER_VERSION
mdefine_line|#define FD_DRIVER_VERSION 0x100
multiline_comment|/* user programs using the floppy API should use floppy_fdc_state to&n; * get the version number of the floppy driver that they are running&n; * on. If this version number is bigger than the one compiled into the&n; * user program (the FD_DRIVER_VERSION define), it should be prepared&n; * to bigger structures&n; */
DECL|member|track
r_int
r_char
id|track
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Position of the heads of the 4 units attached to this FDC,&n;&t; * as stored on the FDC. In the future, the position as stored&n;&t; * on the FDC might not agree with the actual physical&n;&t; * position of these drive heads. By allowing such&n;&t; * disagreement, it will be possible to reset the FDC without&n;&t; * incurring the expensive cost of repositioning all heads.&n;&t; * Right now, these positions are hard wired to 0. */
)brace
suffix:semicolon
DECL|macro|FDGETFDCSTAT
mdefine_line|#define FDGETFDCSTAT _IOR(2, 0x15, struct floppy_fdc_state)
multiline_comment|/*&n; * Asynchronous Write error tracking&n; */
DECL|struct|floppy_write_errors
r_struct
id|floppy_write_errors
(brace
multiline_comment|/* Write error logging.&n;&t; *&n;&t; * These fields can be cleared with the FDWERRORCLR ioctl.&n;&t; * Only writes that were attempted but failed due to a physical media&n;&t; * error are logged.  write(2) calls that fail and return an error code&n;&t; * to the user process are not counted.&n;&t; */
DECL|member|write_errors
r_int
r_int
id|write_errors
suffix:semicolon
multiline_comment|/* number of physical write errors &n;&t;&t;&t;&t;     * encountered */
multiline_comment|/* position of first and last write errors */
DECL|member|first_error_sector
r_int
r_int
id|first_error_sector
suffix:semicolon
DECL|member|first_error_generation
r_int
id|first_error_generation
suffix:semicolon
DECL|member|last_error_sector
r_int
r_int
id|last_error_sector
suffix:semicolon
DECL|member|last_error_generation
r_int
id|last_error_generation
suffix:semicolon
DECL|member|badness
r_int
r_int
id|badness
suffix:semicolon
multiline_comment|/* highest retry count for a read or write &n;&t;&t;&t;       * operation */
)brace
suffix:semicolon
DECL|macro|FDWERRORCLR
mdefine_line|#define FDWERRORCLR  _IO(2, 0x56)
multiline_comment|/* clear write error and badness information */
DECL|macro|FDWERRORGET
mdefine_line|#define FDWERRORGET  _IOR(2, 0x17, struct floppy_write_errors)
multiline_comment|/* get write error and badness information */
multiline_comment|/*&n; * Raw commands&n; */
multiline_comment|/* new interface flag: now we can do them in batches */
DECL|macro|FDHAVEBATCHEDRAWCMD
mdefine_line|#define FDHAVEBATCHEDRAWCMD
DECL|struct|floppy_raw_cmd
r_struct
id|floppy_raw_cmd
(brace
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|macro|FD_RAW_READ
mdefine_line|#define FD_RAW_READ 1
DECL|macro|FD_RAW_WRITE
mdefine_line|#define FD_RAW_WRITE 2
DECL|macro|FD_RAW_NO_MOTOR
mdefine_line|#define FD_RAW_NO_MOTOR 4
DECL|macro|FD_RAW_DISK_CHANGE
mdefine_line|#define FD_RAW_DISK_CHANGE 4 /* out: disk change flag was set */
DECL|macro|FD_RAW_INTR
mdefine_line|#define FD_RAW_INTR 8    /* wait for an interrupt */
DECL|macro|FD_RAW_SPIN
mdefine_line|#define FD_RAW_SPIN 0x10 /* spin up the disk for this command */
DECL|macro|FD_RAW_NO_MOTOR_AFTER
mdefine_line|#define FD_RAW_NO_MOTOR_AFTER 0x20 /* switch the motor off after command &n;&t;&t;&t;&t;    * completion */
DECL|macro|FD_RAW_NEED_DISK
mdefine_line|#define FD_RAW_NEED_DISK 0x40  /* this command needs a disk to be present */
DECL|macro|FD_RAW_NEED_SEEK
mdefine_line|#define FD_RAW_NEED_SEEK 0x80  /* this command uses an implied seek (soft) */
multiline_comment|/* more &quot;in&quot; flags */
DECL|macro|FD_RAW_MORE
mdefine_line|#define FD_RAW_MORE 0x100  /* more records follow */
DECL|macro|FD_RAW_STOP_IF_FAILURE
mdefine_line|#define FD_RAW_STOP_IF_FAILURE 0x200 /* stop if we encounter a failure */
DECL|macro|FD_RAW_STOP_IF_SUCCESS
mdefine_line|#define FD_RAW_STOP_IF_SUCCESS 0x400 /* stop if command successful */
DECL|macro|FD_RAW_SOFTFAILURE
mdefine_line|#define FD_RAW_SOFTFAILURE 0x800 /* consider the return value for failure&n;&t;&t;&t;&t;  * detection too */
multiline_comment|/* more &quot;out&quot; flags */
DECL|macro|FD_RAW_FAILURE
mdefine_line|#define FD_RAW_FAILURE 0x10000 /* command sent to fdc, fdc returned error */
DECL|macro|FD_RAW_HARDFAILURE
mdefine_line|#define FD_RAW_HARDFAILURE 0x20000 /* fdc had to be reset, or timed out */
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
DECL|member|kernel_data
r_char
op_star
id|kernel_data
suffix:semicolon
multiline_comment|/* location of data buffer in the kernel */
DECL|member|next
r_struct
id|floppy_raw_cmd
op_star
id|next
suffix:semicolon
multiline_comment|/* used for chaining of raw cmd&squot;s &n;&t;&t;&t;&t;      * within the kernel */
DECL|member|length
r_int
id|length
suffix:semicolon
multiline_comment|/* in: length of dma transfer. out: remaining bytes */
DECL|member|phys_length
r_int
id|phys_length
suffix:semicolon
multiline_comment|/* physical length, if different from dma length */
DECL|member|buffer_length
r_int
id|buffer_length
suffix:semicolon
multiline_comment|/* length of allocated buffer */
DECL|member|rate
r_int
r_char
id|rate
suffix:semicolon
DECL|member|cmd_count
r_int
r_char
id|cmd_count
suffix:semicolon
DECL|member|cmd
r_int
r_char
id|cmd
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|reply_count
r_int
r_char
id|reply_count
suffix:semicolon
DECL|member|reply
r_int
r_char
id|reply
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|track
r_int
id|track
suffix:semicolon
DECL|member|resultcode
r_int
id|resultcode
suffix:semicolon
DECL|member|reserved1
r_int
id|reserved1
suffix:semicolon
DECL|member|reserved2
r_int
id|reserved2
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|FDRAWCMD
mdefine_line|#define FDRAWCMD _IO(2, 0x58)
multiline_comment|/* send a raw command to the fdc. Structure size not included, because of&n; * batches */
DECL|macro|FDTWADDLE
mdefine_line|#define FDTWADDLE _IO(2, 0x59)
multiline_comment|/* flicker motor-on bit before reading a sector. Experimental */
DECL|macro|FDEJECT
mdefine_line|#define FDEJECT _IO(2, 0x5a)
multiline_comment|/* eject the disk */
macro_line|#ifdef __KERNEL__
multiline_comment|/* eject the boot floppy (if we need the drive for a different root floppy) */
r_void
id|floppy_eject
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
