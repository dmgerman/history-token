multiline_comment|/* -*-linux-c-*-&n;&n; * vendor-specific code for SCSI CD-ROM&squot;s goes here.&n; *&n; * This is needed becauce most of the new features (multisession and&n; * the like) are too new to be included into the SCSI-II standard (to&n; * be exact: there is&squot;nt anything in my draft copy).&n; *&n; * Aug 1997: Ha! Got a SCSI-3 cdrom spec across my fingers. SCSI-3 does&n; *           multisession using the READ TOC command (like SONY).&n; *&n; *           Rearranged stuff here: SCSI-3 is included allways, support&n; *           for NEC/TOSHIBA/HP commands is optional.&n; *&n; *   Gerd Knorr &lt;kraxel@cs.tu-berlin.de&gt; &n; *&n; * --------------------------------------------------------------------------&n; *&n; * support for XA/multisession-CD&squot;s&n; * &n; *   - NEC:     Detection and support of multisession CD&squot;s.&n; *     &n; *   - TOSHIBA: Detection and support of multisession CD&squot;s.&n; *              Some XA-Sector tweaking, required for older drives.&n; *&n; *   - SONY:    Detection and support of multisession CD&squot;s.&n; *              added by Thomas Quinot &lt;thomas@cuivre.freenix.fr&gt;&n; *&n; *   - PIONEER, HITACHI, PLEXTOR, MATSHITA, TEAC, PHILIPS: known to&n; *              work with SONY (SCSI3 now)  code.&n; *&n; *   - HP:      Much like SONY, but a little different... (Thomas)&n; *              HP-Writers only ??? Maybe other CD-Writers work with this too ?&n; *              HP 6020 writers now supported.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &quot;hosts.h&quot;
macro_line|#include &lt;scsi/scsi_ioctl.h&gt;
macro_line|#include &lt;linux/cdrom.h&gt;
macro_line|#include &quot;sr.h&quot;
macro_line|#if 0
mdefine_line|#define DEBUG
macro_line|#endif
multiline_comment|/* here are some constants to sort the vendors into groups */
DECL|macro|VENDOR_SCSI3
mdefine_line|#define VENDOR_SCSI3           1&t;/* default: scsi-3 mmc */
DECL|macro|VENDOR_NEC
mdefine_line|#define VENDOR_NEC             2
DECL|macro|VENDOR_TOSHIBA
mdefine_line|#define VENDOR_TOSHIBA         3
DECL|macro|VENDOR_WRITER
mdefine_line|#define VENDOR_WRITER          4&t;/* pre-scsi3 writers */
DECL|function|sr_vendor_init
r_void
id|sr_vendor_init
c_func
(paren
id|Scsi_CD
op_star
id|cd
)paren
(brace
macro_line|#ifndef CONFIG_BLK_DEV_SR_VENDOR
id|cd-&gt;vendor
op_assign
id|VENDOR_SCSI3
suffix:semicolon
macro_line|#else
r_char
op_star
id|vendor
op_assign
id|cd-&gt;device-&gt;vendor
suffix:semicolon
r_char
op_star
id|model
op_assign
id|cd-&gt;device-&gt;model
suffix:semicolon
multiline_comment|/* default */
id|cd-&gt;vendor
op_assign
id|VENDOR_SCSI3
suffix:semicolon
r_if
c_cond
(paren
id|cd-&gt;readcd_known
)paren
multiline_comment|/* this is true for scsi3/mmc drives - no more checks */
r_return
suffix:semicolon
r_if
c_cond
(paren
id|cd-&gt;device-&gt;type
op_eq
id|TYPE_WORM
)paren
(brace
id|cd-&gt;vendor
op_assign
id|VENDOR_WRITER
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|vendor
comma
l_string|&quot;NEC&quot;
comma
l_int|3
)paren
)paren
(brace
id|cd-&gt;vendor
op_assign
id|VENDOR_NEC
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|model
comma
l_string|&quot;CD-ROM DRIVE:25&quot;
comma
l_int|15
)paren
op_logical_or
op_logical_neg
id|strncmp
c_func
(paren
id|model
comma
l_string|&quot;CD-ROM DRIVE:36&quot;
comma
l_int|15
)paren
op_logical_or
op_logical_neg
id|strncmp
c_func
(paren
id|model
comma
l_string|&quot;CD-ROM DRIVE:83&quot;
comma
l_int|15
)paren
op_logical_or
op_logical_neg
id|strncmp
c_func
(paren
id|model
comma
l_string|&quot;CD-ROM DRIVE:84 &quot;
comma
l_int|16
)paren
macro_line|#if 0
multiline_comment|/* my NEC 3x returns the read-raw data if a read-raw&n;&t;&t;   is followed by a read for the same sector - aeb */
op_logical_or
op_logical_neg
id|strncmp
c_func
(paren
id|model
comma
l_string|&quot;CD-ROM DRIVE:500&quot;
comma
l_int|16
)paren
macro_line|#endif
)paren
multiline_comment|/* these can&squot;t handle multisession, may hang */
id|cd-&gt;cdi.mask
op_or_assign
id|CDC_MULTI_SESSION
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|vendor
comma
l_string|&quot;TOSHIBA&quot;
comma
l_int|7
)paren
)paren
(brace
id|cd-&gt;vendor
op_assign
id|VENDOR_TOSHIBA
suffix:semicolon
)brace
macro_line|#endif
)brace
multiline_comment|/* small handy function for switching block length using MODE SELECT,&n; * used by sr_read_sector() */
DECL|function|sr_set_blocklength
r_int
id|sr_set_blocklength
c_func
(paren
id|Scsi_CD
op_star
id|cd
comma
r_int
id|blocklength
)paren
(brace
r_int
r_char
op_star
id|buffer
suffix:semicolon
multiline_comment|/* the buffer for the ioctl */
r_int
r_char
id|cmd
(braket
id|MAX_COMMAND_SIZE
)braket
suffix:semicolon
multiline_comment|/* the scsi-command */
r_struct
id|ccs_modesel_head
op_star
id|modesel
suffix:semicolon
r_int
id|rc
comma
id|density
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_SR_VENDOR
r_if
c_cond
(paren
id|cd-&gt;vendor
op_eq
id|VENDOR_TOSHIBA
)paren
id|density
op_assign
(paren
id|blocklength
OG
l_int|2048
)paren
ques
c_cond
l_int|0x81
suffix:colon
l_int|0x83
suffix:semicolon
macro_line|#endif
id|buffer
op_assign
(paren
r_int
r_char
op_star
)paren
id|kmalloc
c_func
(paren
l_int|512
comma
id|GFP_KERNEL
op_or
id|GFP_DMA
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buffer
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;%s: MODE SELECT 0x%x/%d&bslash;n&quot;
comma
id|cd-&gt;cdi.name
comma
id|density
comma
id|blocklength
)paren
suffix:semicolon
macro_line|#endif
id|memset
c_func
(paren
id|cmd
comma
l_int|0
comma
id|MAX_COMMAND_SIZE
)paren
suffix:semicolon
id|cmd
(braket
l_int|0
)braket
op_assign
id|MODE_SELECT
suffix:semicolon
id|cmd
(braket
l_int|1
)braket
op_assign
(paren
id|cd-&gt;device-&gt;scsi_level
op_le
id|SCSI_2
)paren
ques
c_cond
(paren
id|cd-&gt;device-&gt;lun
op_lshift
l_int|5
)paren
suffix:colon
l_int|0
suffix:semicolon
id|cmd
(braket
l_int|1
)braket
op_or_assign
(paren
l_int|1
op_lshift
l_int|4
)paren
suffix:semicolon
id|cmd
(braket
l_int|4
)braket
op_assign
l_int|12
suffix:semicolon
id|modesel
op_assign
(paren
r_struct
id|ccs_modesel_head
op_star
)paren
id|buffer
suffix:semicolon
id|memset
c_func
(paren
id|modesel
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|modesel
)paren
)paren
suffix:semicolon
id|modesel-&gt;block_desc_length
op_assign
l_int|0x08
suffix:semicolon
id|modesel-&gt;density
op_assign
id|density
suffix:semicolon
id|modesel-&gt;block_length_med
op_assign
(paren
id|blocklength
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
suffix:semicolon
id|modesel-&gt;block_length_lo
op_assign
id|blocklength
op_amp
l_int|0xff
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_eq
(paren
id|rc
op_assign
id|sr_do_ioctl
c_func
(paren
id|cd
comma
id|cmd
comma
id|buffer
comma
r_sizeof
(paren
op_star
id|modesel
)paren
comma
l_int|0
comma
id|SCSI_DATA_WRITE
comma
l_int|NULL
)paren
)paren
)paren
(brace
id|cd-&gt;device-&gt;sector_size
op_assign
id|blocklength
suffix:semicolon
)brace
macro_line|#ifdef DEBUG
r_else
id|printk
c_func
(paren
l_string|&quot;%s: switching blocklength to %d bytes failed&bslash;n&quot;
comma
id|cd-&gt;cdi.name
comma
id|blocklength
)paren
suffix:semicolon
macro_line|#endif
id|kfree
c_func
(paren
id|buffer
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/* This function gets called after a media change. Checks if the CD is&n;   multisession, asks for offset etc. */
DECL|macro|BCD_TO_BIN
mdefine_line|#define BCD_TO_BIN(x)    ((((int)x &amp; 0xf0) &gt;&gt; 4)*10 + ((int)x &amp; 0x0f))
DECL|function|sr_cd_check
r_int
id|sr_cd_check
c_func
(paren
r_struct
id|cdrom_device_info
op_star
id|cdi
)paren
(brace
id|Scsi_CD
op_star
id|cd
op_assign
id|cdi-&gt;handle
suffix:semicolon
r_int
r_int
id|sector
suffix:semicolon
r_int
r_char
op_star
id|buffer
suffix:semicolon
multiline_comment|/* the buffer for the ioctl */
r_int
r_char
id|cmd
(braket
id|MAX_COMMAND_SIZE
)braket
suffix:semicolon
multiline_comment|/* the scsi-command */
r_int
id|rc
comma
id|no_multi
suffix:semicolon
r_if
c_cond
(paren
id|cd-&gt;cdi.mask
op_amp
id|CDC_MULTI_SESSION
)paren
r_return
l_int|0
suffix:semicolon
id|buffer
op_assign
(paren
r_int
r_char
op_star
)paren
id|kmalloc
c_func
(paren
l_int|512
comma
id|GFP_KERNEL
op_or
id|GFP_DMA
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buffer
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|sector
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* the multisession sector offset goes here  */
id|no_multi
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* flag: the drive can&squot;t handle multisession */
id|rc
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|cd-&gt;vendor
)paren
(brace
r_case
id|VENDOR_SCSI3
suffix:colon
id|memset
c_func
(paren
id|cmd
comma
l_int|0
comma
id|MAX_COMMAND_SIZE
)paren
suffix:semicolon
id|cmd
(braket
l_int|0
)braket
op_assign
id|READ_TOC
suffix:semicolon
id|cmd
(braket
l_int|1
)braket
op_assign
(paren
id|cd-&gt;device-&gt;scsi_level
op_le
id|SCSI_2
)paren
ques
c_cond
(paren
id|cd-&gt;device-&gt;lun
op_lshift
l_int|5
)paren
suffix:colon
l_int|0
suffix:semicolon
id|cmd
(braket
l_int|8
)braket
op_assign
l_int|12
suffix:semicolon
id|cmd
(braket
l_int|9
)braket
op_assign
l_int|0x40
suffix:semicolon
id|rc
op_assign
id|sr_do_ioctl
c_func
(paren
id|cd
comma
id|cmd
comma
id|buffer
comma
l_int|12
comma
l_int|1
comma
id|SCSI_DATA_READ
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_ne
l_int|0
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
(paren
id|buffer
(braket
l_int|0
)braket
op_lshift
l_int|8
)paren
op_plus
id|buffer
(braket
l_int|1
)braket
OL
l_int|0x0a
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: Hmm, seems the drive &quot;
l_string|&quot;doesn&squot;t support multisession CD&squot;s&bslash;n&quot;
comma
id|cd-&gt;cdi.name
)paren
suffix:semicolon
id|no_multi
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
id|sector
op_assign
id|buffer
(braket
l_int|11
)braket
op_plus
(paren
id|buffer
(braket
l_int|10
)braket
op_lshift
l_int|8
)paren
op_plus
(paren
id|buffer
(braket
l_int|9
)braket
op_lshift
l_int|16
)paren
op_plus
(paren
id|buffer
(braket
l_int|8
)braket
op_lshift
l_int|24
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buffer
(braket
l_int|6
)braket
op_le
l_int|1
)paren
(brace
multiline_comment|/* ignore sector offsets from first track */
id|sector
op_assign
l_int|0
suffix:semicolon
)brace
r_break
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_SR_VENDOR
r_case
id|VENDOR_NEC
suffix:colon
(brace
r_int
r_int
id|min
comma
id|sec
comma
id|frame
suffix:semicolon
id|memset
c_func
(paren
id|cmd
comma
l_int|0
comma
id|MAX_COMMAND_SIZE
)paren
suffix:semicolon
id|cmd
(braket
l_int|0
)braket
op_assign
l_int|0xde
suffix:semicolon
id|cmd
(braket
l_int|1
)braket
op_assign
(paren
id|cd-&gt;device-&gt;scsi_level
op_le
id|SCSI_2
)paren
ques
c_cond
(paren
id|cd-&gt;device-&gt;lun
op_lshift
l_int|5
)paren
suffix:colon
l_int|0
suffix:semicolon
id|cmd
(braket
l_int|1
)braket
op_or_assign
l_int|0x03
suffix:semicolon
id|cmd
(braket
l_int|2
)braket
op_assign
l_int|0xb0
suffix:semicolon
id|rc
op_assign
id|sr_do_ioctl
c_func
(paren
id|cd
comma
id|cmd
comma
id|buffer
comma
l_int|0x16
comma
l_int|1
comma
id|SCSI_DATA_READ
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_ne
l_int|0
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|buffer
(braket
l_int|14
)braket
op_ne
l_int|0
op_logical_and
id|buffer
(braket
l_int|14
)braket
op_ne
l_int|0xb0
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: Hmm, seems the cdrom &quot;
l_string|&quot;doesn&squot;t support multisession CD&squot;s&bslash;n&quot;
comma
id|cd-&gt;cdi.name
)paren
suffix:semicolon
id|no_multi
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
id|min
op_assign
id|BCD_TO_BIN
c_func
(paren
id|buffer
(braket
l_int|15
)braket
)paren
suffix:semicolon
id|sec
op_assign
id|BCD_TO_BIN
c_func
(paren
id|buffer
(braket
l_int|16
)braket
)paren
suffix:semicolon
id|frame
op_assign
id|BCD_TO_BIN
c_func
(paren
id|buffer
(braket
l_int|17
)braket
)paren
suffix:semicolon
id|sector
op_assign
id|min
op_star
id|CD_SECS
op_star
id|CD_FRAMES
op_plus
id|sec
op_star
id|CD_FRAMES
op_plus
id|frame
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|VENDOR_TOSHIBA
suffix:colon
(brace
r_int
r_int
id|min
comma
id|sec
comma
id|frame
suffix:semicolon
multiline_comment|/* we request some disc information (is it a XA-CD ?,&n;&t;&t;&t; * where starts the last session ?) */
id|memset
c_func
(paren
id|cmd
comma
l_int|0
comma
id|MAX_COMMAND_SIZE
)paren
suffix:semicolon
id|cmd
(braket
l_int|0
)braket
op_assign
l_int|0xc7
suffix:semicolon
id|cmd
(braket
l_int|1
)braket
op_assign
(paren
id|cd-&gt;device-&gt;scsi_level
op_le
id|SCSI_2
)paren
ques
c_cond
(paren
id|cd-&gt;device-&gt;lun
op_lshift
l_int|5
)paren
suffix:colon
l_int|0
suffix:semicolon
id|cmd
(braket
l_int|1
)braket
op_or_assign
l_int|0x03
suffix:semicolon
id|rc
op_assign
id|sr_do_ioctl
c_func
(paren
id|cd
comma
id|cmd
comma
id|buffer
comma
l_int|4
comma
l_int|1
comma
id|SCSI_DATA_READ
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_eq
op_minus
id|EINVAL
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: Hmm, seems the drive &quot;
l_string|&quot;doesn&squot;t support multisession CD&squot;s&bslash;n&quot;
comma
id|cd-&gt;cdi.name
)paren
suffix:semicolon
id|no_multi
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|rc
op_ne
l_int|0
)paren
r_break
suffix:semicolon
id|min
op_assign
id|BCD_TO_BIN
c_func
(paren
id|buffer
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|sec
op_assign
id|BCD_TO_BIN
c_func
(paren
id|buffer
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|frame
op_assign
id|BCD_TO_BIN
c_func
(paren
id|buffer
(braket
l_int|3
)braket
)paren
suffix:semicolon
id|sector
op_assign
id|min
op_star
id|CD_SECS
op_star
id|CD_FRAMES
op_plus
id|sec
op_star
id|CD_FRAMES
op_plus
id|frame
suffix:semicolon
r_if
c_cond
(paren
id|sector
)paren
id|sector
op_sub_assign
id|CD_MSF_OFFSET
suffix:semicolon
id|sr_set_blocklength
c_func
(paren
id|cd
comma
l_int|2048
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|VENDOR_WRITER
suffix:colon
id|memset
c_func
(paren
id|cmd
comma
l_int|0
comma
id|MAX_COMMAND_SIZE
)paren
suffix:semicolon
id|cmd
(braket
l_int|0
)braket
op_assign
id|READ_TOC
suffix:semicolon
id|cmd
(braket
l_int|1
)braket
op_assign
(paren
id|cd-&gt;device-&gt;scsi_level
op_le
id|SCSI_2
)paren
ques
c_cond
(paren
id|cd-&gt;device-&gt;lun
op_lshift
l_int|5
)paren
suffix:colon
l_int|0
suffix:semicolon
id|cmd
(braket
l_int|8
)braket
op_assign
l_int|0x04
suffix:semicolon
id|cmd
(braket
l_int|9
)braket
op_assign
l_int|0x40
suffix:semicolon
id|rc
op_assign
id|sr_do_ioctl
c_func
(paren
id|cd
comma
id|cmd
comma
id|buffer
comma
l_int|0x04
comma
l_int|1
comma
id|SCSI_DATA_READ
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_ne
l_int|0
)paren
(brace
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|rc
op_assign
id|buffer
(braket
l_int|2
)braket
)paren
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: No finished session&bslash;n&quot;
comma
id|cd-&gt;cdi.name
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|cmd
(braket
l_int|0
)braket
op_assign
id|READ_TOC
suffix:semicolon
multiline_comment|/* Read TOC */
id|cmd
(braket
l_int|1
)braket
op_assign
(paren
id|cd-&gt;device-&gt;scsi_level
op_le
id|SCSI_2
)paren
ques
c_cond
(paren
id|cd-&gt;device-&gt;lun
op_lshift
l_int|5
)paren
suffix:colon
l_int|0
suffix:semicolon
id|cmd
(braket
l_int|6
)braket
op_assign
id|rc
op_amp
l_int|0x7f
suffix:semicolon
multiline_comment|/* number of last session */
id|cmd
(braket
l_int|8
)braket
op_assign
l_int|0x0c
suffix:semicolon
id|cmd
(braket
l_int|9
)braket
op_assign
l_int|0x40
suffix:semicolon
id|rc
op_assign
id|sr_do_ioctl
c_func
(paren
id|cd
comma
id|cmd
comma
id|buffer
comma
l_int|12
comma
l_int|1
comma
id|SCSI_DATA_READ
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_ne
l_int|0
)paren
(brace
r_break
suffix:semicolon
)brace
id|sector
op_assign
id|buffer
(braket
l_int|11
)braket
op_plus
(paren
id|buffer
(braket
l_int|10
)braket
op_lshift
l_int|8
)paren
op_plus
(paren
id|buffer
(braket
l_int|9
)braket
op_lshift
l_int|16
)paren
op_plus
(paren
id|buffer
(braket
l_int|8
)braket
op_lshift
l_int|24
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* CONFIG_BLK_DEV_SR_VENDOR */
r_default
suffix:colon
multiline_comment|/* should not happen */
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: unknown vendor code (%i), not initialized ?&bslash;n&quot;
comma
id|cd-&gt;cdi.name
comma
id|cd-&gt;vendor
)paren
suffix:semicolon
id|sector
op_assign
l_int|0
suffix:semicolon
id|no_multi
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
id|cd-&gt;ms_offset
op_assign
id|sector
suffix:semicolon
id|cd-&gt;xa_flag
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|CDS_AUDIO
op_ne
id|sr_disk_status
c_func
(paren
id|cdi
)paren
op_logical_and
l_int|1
op_eq
id|sr_is_xa
c_func
(paren
id|cd
)paren
)paren
id|cd-&gt;xa_flag
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
l_int|2048
op_ne
id|cd-&gt;device-&gt;sector_size
)paren
(brace
id|sr_set_blocklength
c_func
(paren
id|cd
comma
l_int|2048
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|no_multi
)paren
id|cdi-&gt;mask
op_or_assign
id|CDC_MULTI_SESSION
suffix:semicolon
macro_line|#ifdef DEBUG
r_if
c_cond
(paren
id|sector
)paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s: multisession offset=%lu&bslash;n&quot;
comma
id|cd-&gt;cdi.name
comma
id|sector
)paren
suffix:semicolon
macro_line|#endif
id|kfree
c_func
(paren
id|buffer
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
eof
