multiline_comment|/*&n; * sbpcd.h   Specify interface address and interface type here.&n; */
multiline_comment|/*&n; * Attention! This file contains user-serviceable parts!&n; * I recommend to make use of it...&n; * If you feel helpless, look into linux/Documentation/cdrom/sbpcd&n; * (good idea anyway, at least before mailing me).&n; *&n; * The definitions for the first controller can get overridden by&n; * the kernel command line (&quot;lilo boot option&quot;).&n; * Examples:&n; *                                 sbpcd=0x300,LaserMate&n; *                             or&n; *                                 sbpcd=0x230,SoundBlaster&n; *                             or&n; *                                 sbpcd=0x338,SoundScape&n; *                             or&n; *                                 sbpcd=0x2C0,Teac16bit&n; *&n; * If sbpcd gets used as a module, you can load it with&n; *     insmod sbpcd.o sbpcd=0x300,0&n; * or&n; *     insmod sbpcd.o sbpcd=0x230,1&n; * or&n; *     insmod sbpcd.o sbpcd=0x338,2&n; * or&n; *     insmod sbpcd.o sbpcd=0x2C0,3&n; * respective to override the configured address and type.&n; */
multiline_comment|/*&n; * define your CDROM port base address as CDROM_PORT&n; * and specify the type of your interface card as SBPRO.&n; *&n; * address:&n; * ========&n; * SBPRO type addresses typically are 0x0230 (=0x220+0x10), 0x0250, ...&n; * LASERMATE type (CI-101P, WDH-7001C) addresses typically are 0x0300, ...&n; * SOUNDSCAPE addresses are from the LASERMATE type and range. You have to&n; * specify the REAL address here, not the configuration port address. Look&n; * at the CDROM driver&squot;s invoking line within your DOS CONFIG.SYS, or let&n; * sbpcd auto-probe, if you are not firm with the address.&n; * There are some soundcards on the market with 0x0630, 0x0650, ...; their&n; * type is not obvious (both types are possible).&n; *&n; * example: if your SBPRO audio address is 0x220, specify 0x230 and SBPRO 1.&n; *          if your soundcard has its CDROM port above 0x300, specify&n; *          that address and try SBPRO 0 first.&n; *          if your SoundScape configuration port is at 0x330, specify&n; *          0x338 and SBPRO 2.&n; *&n; * interface type:&n; * ===============&n; * set SBPRO to 1 for &quot;true&quot; SoundBlaster card&n; * set SBPRO to 0 for &quot;compatible&quot; soundcards and&n; *                for &quot;poor&quot; (no sound) interface cards.&n; * set SBPRO to 2 for Ensonic SoundScape or SPEA Media FX cards&n; * set SBPRO to 3 for Teac 16bit interface cards&n; *&n; * Almost all &quot;compatible&quot; sound boards need to set SBPRO to 0.&n; * If SBPRO is set wrong, the drives will get found - but any&n; * data access will give errors (audio access will work).&n; * The &quot;OmniCD&quot; no-sound interface card from CreativeLabs and most Teac&n; * interface cards need SBPRO 1.&n; *&n; * sound base:&n; * ===========&n; * The SOUND_BASE definition tells if we should try to turn the CD sound&n; * channels on. It will only be of use regarding soundcards with a SbPro&n; * compatible mixer.&n; *&n; * Example: #define SOUND_BASE 0x220 enables the sound card&squot;s CD channels&n; *          #define SOUND_BASE 0     leaves the soundcard untouched&n; */
DECL|macro|CDROM_PORT
mdefine_line|#define CDROM_PORT 0x340 /* &lt;-----------&lt;&lt; port address                      */
DECL|macro|SBPRO
mdefine_line|#define SBPRO      0     /* &lt;-----------&lt;&lt; interface type                    */
DECL|macro|MAX_DRIVES
mdefine_line|#define MAX_DRIVES 4     /* set to 1 if the card does not use &quot;drive select&quot; */
DECL|macro|SOUND_BASE
mdefine_line|#define SOUND_BASE 0x220 /* &lt;-----------&lt;&lt; sound address of this card or 0   */
multiline_comment|/*&n; * some more or less user dependent definitions - service them!&n; */
multiline_comment|/* Set this to 0 once you have configured your interface definitions right. */
DECL|macro|DISTRIBUTION
mdefine_line|#define DISTRIBUTION 1
multiline_comment|/*&n; * Time to wait after giving a message.&n; * This gets important if you enable non-standard DBG_xxx flags.&n; * You will see what happens if you omit the pause or make it&n; * too short. Be warned!&n; */
DECL|macro|KLOGD_PAUSE
mdefine_line|#define KLOGD_PAUSE 1
multiline_comment|/* tray control: eject tray if no disk is in */
macro_line|#if DISTRIBUTION
DECL|macro|JUKEBOX
mdefine_line|#define JUKEBOX 0
macro_line|#else
DECL|macro|JUKEBOX
mdefine_line|#define JUKEBOX 1
macro_line|#endif /* DISTRIBUTION */
multiline_comment|/* tray control: eject tray after last use */
macro_line|#if DISTRIBUTION
DECL|macro|EJECT
mdefine_line|#define EJECT 0
macro_line|#else
DECL|macro|EJECT
mdefine_line|#define EJECT 1
macro_line|#endif /* DISTRIBUTION */
multiline_comment|/* max. number of audio frames to read with one     */
multiline_comment|/* request (allocates n* 2352 bytes kernel memory!) */
multiline_comment|/* may be freely adjusted, f.e. 75 (= 1 sec.), at   */
multiline_comment|/* runtime by use of the CDROMAUDIOBUFSIZ ioctl.    */
DECL|macro|READ_AUDIO
mdefine_line|#define READ_AUDIO 0
multiline_comment|/* Optimizations for the Teac CD-55A drive read performance.&n; * SBP_TEAC_SPEED can be changed here, or one can set the &n; * variable &quot;teac&quot; when loading as a module.&n; * Valid settings are:&n; *   0 - very slow - the recommended &quot;DISTRIBUTION 1&quot; setup.&n; *   1 - 2x performance with little overhead. No busy waiting.&n; *   2 - 4x performance with 5ms overhead per read. Busy wait.&n; *&n; * Setting SBP_TEAC_SPEED or the variable &squot;teac&squot; to anything&n; * other than 0 may cause problems. If you run into them, first&n; * change SBP_TEAC_SPEED back to 0 and see if your drive responds&n; * normally. If yes, you are &quot;allowed&quot; to report your case - to help&n; * me with the driver, not to solve your hassle. Don&#xfffd;t mail if you&n; * simply are stuck into your own &quot;tuning&quot; experiments, you know?&n; */
DECL|macro|SBP_TEAC_SPEED
mdefine_line|#define SBP_TEAC_SPEED 1
multiline_comment|/*==========================================================================*/
multiline_comment|/*==========================================================================*/
multiline_comment|/*&n; * nothing to change below here if you are not fully aware what you&squot;re doing&n; */
macro_line|#ifndef _LINUX_SBPCD_H
DECL|macro|_LINUX_SBPCD_H
mdefine_line|#define _LINUX_SBPCD_H
multiline_comment|/*==========================================================================*/
multiline_comment|/*==========================================================================*/
multiline_comment|/*&n; * driver&squot;s own read_ahead, data mode&n; */
DECL|macro|SBP_BUFFER_FRAMES
mdefine_line|#define SBP_BUFFER_FRAMES 8 
DECL|macro|LONG_TIMING
mdefine_line|#define LONG_TIMING 0 /* test against timeouts with &quot;gold&quot; CDs on CR-521 */
DECL|macro|FUTURE
macro_line|#undef  FUTURE
DECL|macro|SAFE_MIXED
macro_line|#undef SAFE_MIXED
DECL|macro|TEST_UPC
mdefine_line|#define TEST_UPC 0
DECL|macro|SPEA_TEST
mdefine_line|#define SPEA_TEST 0
DECL|macro|TEST_STI
mdefine_line|#define TEST_STI 0
DECL|macro|OLD_BUSY
mdefine_line|#define OLD_BUSY 0
DECL|macro|PATH_CHECK
macro_line|#undef PATH_CHECK
macro_line|#ifndef SOUND_BASE
DECL|macro|SOUND_BASE
mdefine_line|#define SOUND_BASE 0
macro_line|#endif
macro_line|#if DISTRIBUTION
DECL|macro|SBP_TEAC_SPEED
macro_line|#undef SBP_TEAC_SPEED
DECL|macro|SBP_TEAC_SPEED
mdefine_line|#define SBP_TEAC_SPEED 0
macro_line|#endif
multiline_comment|/*==========================================================================*/
multiline_comment|/*&n; * DDI interface definitions&n; * &quot;invented&quot; by Fred N. van Kempen..&n; */
DECL|macro|DDIOCSDBG
mdefine_line|#define DDIOCSDBG&t;0x9000
multiline_comment|/*==========================================================================*/
multiline_comment|/*&n; * &quot;private&quot; IOCTL functions&n; */
DECL|macro|CDROMAUDIOBUFSIZ
mdefine_line|#define CDROMAUDIOBUFSIZ&t;0x5382 /* set the audio buffer size */
multiline_comment|/*==========================================================================*/
multiline_comment|/*&n; * Debug output levels&n; */
DECL|macro|DBG_INF
mdefine_line|#define DBG_INF&t;1&t;/* necessary information */
DECL|macro|DBG_BSZ
mdefine_line|#define DBG_BSZ&t;2&t;/* BLOCK_SIZE trace */
DECL|macro|DBG_REA
mdefine_line|#define DBG_REA&t;3&t;/* READ status trace */
DECL|macro|DBG_CHK
mdefine_line|#define DBG_CHK&t;4&t;/* MEDIA CHECK trace */
DECL|macro|DBG_TIM
mdefine_line|#define DBG_TIM&t;5&t;/* datarate timer test */
DECL|macro|DBG_INI
mdefine_line|#define DBG_INI&t;6&t;/* initialization trace */
DECL|macro|DBG_TOC
mdefine_line|#define DBG_TOC&t;7&t;/* tell TocEntry values */
DECL|macro|DBG_IOC
mdefine_line|#define DBG_IOC&t;8&t;/* ioctl trace */
DECL|macro|DBG_STA
mdefine_line|#define DBG_STA&t;9&t;/* ResponseStatus() trace */
DECL|macro|DBG_ERR
mdefine_line|#define DBG_ERR&t;10&t;/* cc_ReadError() trace */
DECL|macro|DBG_CMD
mdefine_line|#define DBG_CMD&t;11&t;/* cmd_out() trace */
DECL|macro|DBG_WRN
mdefine_line|#define DBG_WRN&t;12&t;/* give explanation before auto-probing */
DECL|macro|DBG_MUL
mdefine_line|#define DBG_MUL&t;13&t;/* multi session code test */
DECL|macro|DBG_IDX
mdefine_line|#define DBG_IDX&t;14&t;/* test code for drive_id !=0 */
DECL|macro|DBG_IOX
mdefine_line|#define DBG_IOX&t;15&t;/* some special information */
DECL|macro|DBG_DID
mdefine_line|#define DBG_DID&t;16&t;/* drive ID test */
DECL|macro|DBG_RES
mdefine_line|#define DBG_RES&t;17&t;/* drive reset info */
DECL|macro|DBG_SPI
mdefine_line|#define DBG_SPI&t;18&t;/* SpinUp test */
DECL|macro|DBG_IOS
mdefine_line|#define DBG_IOS&t;19&t;/* ioctl trace: subchannel functions */
DECL|macro|DBG_IO2
mdefine_line|#define DBG_IO2&t;20&t;/* ioctl trace: general */
DECL|macro|DBG_UPC
mdefine_line|#define DBG_UPC&t;21&t;/* show UPC information */
DECL|macro|DBG_XA1
mdefine_line|#define DBG_XA1&t;22&t;/* XA mode debugging */
DECL|macro|DBG_LCK
mdefine_line|#define DBG_LCK&t;23&t;/* door (un)lock info */
DECL|macro|DBG_SQ1
mdefine_line|#define DBG_SQ1&t;24&t;/* dump SubQ frame */
DECL|macro|DBG_AUD
mdefine_line|#define DBG_AUD&t;25&t;/* READ AUDIO debugging */
DECL|macro|DBG_SEQ
mdefine_line|#define DBG_SEQ&t;26&t;/* Sequoia interface configuration trace */
DECL|macro|DBG_LCS
mdefine_line|#define DBG_LCS&t;27&t;/* Longshine LCS-7260 debugging trace */
DECL|macro|DBG_CD2
mdefine_line|#define DBG_CD2&t;28&t;/* MKE/Funai CD200 debugging trace */
DECL|macro|DBG_TEA
mdefine_line|#define DBG_TEA&t;29&t;/* TEAC CD-55A debugging trace */
DECL|macro|DBG_ECS
mdefine_line|#define DBG_ECS&t;30&t;/* ECS-AT (Vertos 100) debugging trace */
DECL|macro|DBG_000
mdefine_line|#define DBG_000&t;31&t;/* unnecessary information */
multiline_comment|/*==========================================================================*/
multiline_comment|/*==========================================================================*/
multiline_comment|/*&n; * bits of flags_cmd_out:&n; */
DECL|macro|f_respo3
mdefine_line|#define f_respo3&t;&t;0x100
DECL|macro|f_putcmd
mdefine_line|#define f_putcmd&t;&t;0x80
DECL|macro|f_respo2
mdefine_line|#define f_respo2&t;&t;0x40
DECL|macro|f_lopsta
mdefine_line|#define f_lopsta&t;&t;0x20
DECL|macro|f_getsta
mdefine_line|#define f_getsta&t;&t;0x10
DECL|macro|f_ResponseStatus
mdefine_line|#define f_ResponseStatus&t;0x08
DECL|macro|f_obey_p_check
mdefine_line|#define f_obey_p_check&t;&t;0x04
DECL|macro|f_bit1
mdefine_line|#define f_bit1&t;&t;&t;0x02
DECL|macro|f_wait_if_busy
mdefine_line|#define f_wait_if_busy&t;&t;0x01
multiline_comment|/*&n; * diskstate_flags:&n; */
DECL|macro|x80_bit
mdefine_line|#define x80_bit&t;&t;&t;0x80
DECL|macro|upc_bit
mdefine_line|#define upc_bit&t;&t;&t;0x40
DECL|macro|volume_bit
mdefine_line|#define volume_bit&t;&t;0x20
DECL|macro|toc_bit
mdefine_line|#define toc_bit&t;&t;&t;0x10
DECL|macro|multisession_bit
mdefine_line|#define multisession_bit&t;0x08
DECL|macro|cd_size_bit
mdefine_line|#define cd_size_bit&t;&t;0x04
DECL|macro|subq_bit
mdefine_line|#define subq_bit&t;&t;0x02
DECL|macro|frame_size_bit
mdefine_line|#define frame_size_bit&t;&t;0x01
multiline_comment|/*&n; * disk states (bits of diskstate_flags):&n; */
DECL|macro|upc_valid
mdefine_line|#define upc_valid&t;&t;(D_S[d].diskstate_flags&amp;upc_bit)
DECL|macro|volume_valid
mdefine_line|#define volume_valid&t;&t;(D_S[d].diskstate_flags&amp;volume_bit)
DECL|macro|toc_valid
mdefine_line|#define toc_valid&t;&t;(D_S[d].diskstate_flags&amp;toc_bit)
DECL|macro|cd_size_valid
mdefine_line|#define cd_size_valid&t;&t;(D_S[d].diskstate_flags&amp;cd_size_bit)
DECL|macro|subq_valid
mdefine_line|#define subq_valid&t;&t;(D_S[d].diskstate_flags&amp;subq_bit)
DECL|macro|frame_size_valid
mdefine_line|#define frame_size_valid&t;(D_S[d].diskstate_flags&amp;frame_size_bit)
multiline_comment|/*&n; * the status_bits variable&n; */
DECL|macro|p_success
mdefine_line|#define p_success&t;0x100
DECL|macro|p_door_closed
mdefine_line|#define p_door_closed&t;0x80
DECL|macro|p_caddy_in
mdefine_line|#define p_caddy_in&t;0x40
DECL|macro|p_spinning
mdefine_line|#define p_spinning&t;0x20
DECL|macro|p_check
mdefine_line|#define p_check&t;&t;0x10
DECL|macro|p_busy_new
mdefine_line|#define p_busy_new&t;0x08
DECL|macro|p_door_locked
mdefine_line|#define p_door_locked&t;0x04
DECL|macro|p_disk_ok
mdefine_line|#define p_disk_ok&t;0x01
multiline_comment|/*&n; * LCS-7260 special status result bits:&n; */
DECL|macro|p_lcs_door_locked
mdefine_line|#define p_lcs_door_locked&t;0x02
DECL|macro|p_lcs_door_closed
mdefine_line|#define p_lcs_door_closed&t;0x01 /* probably disk_in */
multiline_comment|/*&n; * CR-52x special status result bits:&n; */
DECL|macro|p_caddin_old
mdefine_line|#define p_caddin_old&t;0x40
DECL|macro|p_success_old
mdefine_line|#define p_success_old&t;0x08
DECL|macro|p_busy_old
mdefine_line|#define p_busy_old&t;0x04
DECL|macro|p_bit_1
mdefine_line|#define p_bit_1&t;&t;0x02&t;/* hopefully unused now */
multiline_comment|/*&n; * &quot;generation specific&quot; defs of the status result bits:&n; */
DECL|macro|p0_door_closed
mdefine_line|#define p0_door_closed&t;0x80
DECL|macro|p0_caddy_in
mdefine_line|#define p0_caddy_in&t;0x40
DECL|macro|p0_spinning
mdefine_line|#define p0_spinning&t;0x20
DECL|macro|p0_check
mdefine_line|#define p0_check&t;0x10
DECL|macro|p0_success
mdefine_line|#define p0_success&t;0x08 /* unused */
DECL|macro|p0_busy
mdefine_line|#define p0_busy&t;&t;0x04
DECL|macro|p0_bit_1
mdefine_line|#define p0_bit_1&t;0x02 /* unused */
DECL|macro|p0_disk_ok
mdefine_line|#define p0_disk_ok&t;0x01
DECL|macro|pL_disk_in
mdefine_line|#define pL_disk_in&t;0x40
DECL|macro|pL_spinning
mdefine_line|#define pL_spinning&t;0x20
DECL|macro|pL_check
mdefine_line|#define pL_check&t;0x10
DECL|macro|pL_success
mdefine_line|#define pL_success&t;0x08 /* unused ?? */
DECL|macro|pL_busy
mdefine_line|#define pL_busy&t;&t;0x04
DECL|macro|pL_door_locked
mdefine_line|#define pL_door_locked&t;0x02
DECL|macro|pL_door_closed
mdefine_line|#define pL_door_closed&t;0x01
DECL|macro|pV_door_closed
mdefine_line|#define pV_door_closed&t;0x40
DECL|macro|pV_spinning
mdefine_line|#define pV_spinning&t;0x20
DECL|macro|pV_check
mdefine_line|#define pV_check&t;0x10
DECL|macro|pV_success
mdefine_line|#define pV_success&t;0x08
DECL|macro|pV_busy
mdefine_line|#define pV_busy&t;&t;0x04
DECL|macro|pV_door_locked
mdefine_line|#define pV_door_locked&t;0x02
DECL|macro|pV_disk_ok
mdefine_line|#define pV_disk_ok&t;0x01
DECL|macro|p1_door_closed
mdefine_line|#define p1_door_closed&t;0x80
DECL|macro|p1_disk_in
mdefine_line|#define p1_disk_in&t;0x40
DECL|macro|p1_spinning
mdefine_line|#define p1_spinning&t;0x20
DECL|macro|p1_check
mdefine_line|#define p1_check&t;0x10
DECL|macro|p1_busy
mdefine_line|#define p1_busy&t;&t;0x08
DECL|macro|p1_door_locked
mdefine_line|#define p1_door_locked&t;0x04
DECL|macro|p1_bit_1
mdefine_line|#define p1_bit_1&t;0x02 /* unused */
DECL|macro|p1_disk_ok
mdefine_line|#define p1_disk_ok&t;0x01
DECL|macro|p2_disk_ok
mdefine_line|#define p2_disk_ok&t;0x80
DECL|macro|p2_door_locked
mdefine_line|#define p2_door_locked&t;0x40
DECL|macro|p2_spinning
mdefine_line|#define p2_spinning&t;0x20
DECL|macro|p2_busy2
mdefine_line|#define p2_busy2&t;0x10
DECL|macro|p2_busy1
mdefine_line|#define p2_busy1&t;0x08
DECL|macro|p2_door_closed
mdefine_line|#define p2_door_closed&t;0x04
DECL|macro|p2_disk_in
mdefine_line|#define p2_disk_in&t;0x02
DECL|macro|p2_check
mdefine_line|#define p2_check&t;0x01
multiline_comment|/*&n; * used drive states:&n; */
DECL|macro|st_door_closed
mdefine_line|#define st_door_closed&t;(D_S[d].status_bits&amp;p_door_closed)
DECL|macro|st_caddy_in
mdefine_line|#define st_caddy_in&t;(D_S[d].status_bits&amp;p_caddy_in)
DECL|macro|st_spinning
mdefine_line|#define st_spinning&t;(D_S[d].status_bits&amp;p_spinning)
DECL|macro|st_check
mdefine_line|#define st_check&t;(D_S[d].status_bits&amp;p_check)
DECL|macro|st_busy
mdefine_line|#define st_busy&t;&t;(D_S[d].status_bits&amp;p_busy_new)
DECL|macro|st_door_locked
mdefine_line|#define st_door_locked&t;(D_S[d].status_bits&amp;p_door_locked)
DECL|macro|st_diskok
mdefine_line|#define st_diskok&t;(D_S[d].status_bits&amp;p_disk_ok)
multiline_comment|/*&n; * bits of the CDi_status register:&n; */
DECL|macro|s_not_result_ready
mdefine_line|#define s_not_result_ready&t;0x04 /* 0: &quot;result ready&quot; */
DECL|macro|s_not_data_ready
mdefine_line|#define s_not_data_ready&t;0x02 /* 0: &quot;data ready&quot;   */
DECL|macro|s_attention
mdefine_line|#define s_attention&t;&t;0x01 /* 1: &quot;attention required&quot; */
multiline_comment|/*&n; * usable as:&n; */
DECL|macro|DRV_ATTN
mdefine_line|#define DRV_ATTN&t;((inb(CDi_status)&amp;s_attention)!=0)
DECL|macro|DATA_READY
mdefine_line|#define DATA_READY&t;((inb(CDi_status)&amp;s_not_data_ready)==0)
DECL|macro|RESULT_READY
mdefine_line|#define RESULT_READY&t;((inb(CDi_status)&amp;s_not_result_ready)==0)
multiline_comment|/*&n; * drive families and types (firmware versions):&n; */
DECL|macro|drv_fam0
mdefine_line|#define drv_fam0&t;0x0100&t;&t;/* CR-52x family */
DECL|macro|drv_199
mdefine_line|#define drv_199&t;&t;(drv_fam0+0x01)&t;/* &lt;200 */
DECL|macro|drv_200
mdefine_line|#define drv_200&t;&t;(drv_fam0+0x02)&t;/* &lt;201 */
DECL|macro|drv_201
mdefine_line|#define drv_201&t;&t;(drv_fam0+0x03)&t;/* &lt;210 */
DECL|macro|drv_210
mdefine_line|#define drv_210&t;&t;(drv_fam0+0x04)&t;/* &lt;211 */
DECL|macro|drv_211
mdefine_line|#define drv_211&t;&t;(drv_fam0+0x05)&t;/* &lt;300 */
DECL|macro|drv_300
mdefine_line|#define drv_300&t;&t;(drv_fam0+0x06)&t;/* &gt;=300 */
DECL|macro|drv_fam1
mdefine_line|#define drv_fam1&t;0x0200&t;&t;/* CR-56x family */
DECL|macro|drv_099
mdefine_line|#define drv_099&t;&t;(drv_fam1+0x01)&t;/* &lt;100 */
DECL|macro|drv_100
mdefine_line|#define drv_100&t;&t;(drv_fam1+0x02)&t;/* &gt;=100, only 1.02 and 5.00 known */
DECL|macro|drv_fam2
mdefine_line|#define drv_fam2&t;0x0400&t;&t;/* CD200 family */
DECL|macro|drv_famT
mdefine_line|#define drv_famT&t;0x0800&t;&t;/* TEAC CD-55A */
DECL|macro|drv_famL
mdefine_line|#define drv_famL&t;0x1000&t;&t;/* Longshine family */
DECL|macro|drv_260
mdefine_line|#define drv_260&t;&t;(drv_famL+0x01)&t;/* LCS-7260 */
DECL|macro|drv_e1
mdefine_line|#define drv_e1&t;&t;(drv_famL+0x01)&t;/* LCS-7260, firmware &quot;A E1&quot; */
DECL|macro|drv_f4
mdefine_line|#define drv_f4&t;&t;(drv_famL+0x02)&t;/* LCS-7260, firmware &quot;A4F4&quot; */
DECL|macro|drv_famV
mdefine_line|#define drv_famV&t;0x2000&t;&t;/* ECS-AT (vertos-100) family */
DECL|macro|drv_at
mdefine_line|#define drv_at&t;&t;(drv_famV+0x01)&t;/* ECS-AT, firmware &quot;1.00&quot; */
DECL|macro|fam0_drive
mdefine_line|#define fam0_drive&t;(D_S[d].drv_type&amp;drv_fam0)
DECL|macro|famL_drive
mdefine_line|#define famL_drive&t;(D_S[d].drv_type&amp;drv_famL)
DECL|macro|famV_drive
mdefine_line|#define famV_drive&t;(D_S[d].drv_type&amp;drv_famV)
DECL|macro|fam1_drive
mdefine_line|#define fam1_drive&t;(D_S[d].drv_type&amp;drv_fam1)
DECL|macro|fam2_drive
mdefine_line|#define fam2_drive&t;(D_S[d].drv_type&amp;drv_fam2)
DECL|macro|famT_drive
mdefine_line|#define famT_drive&t;(D_S[d].drv_type&amp;drv_famT)
DECL|macro|fam0L_drive
mdefine_line|#define fam0L_drive&t;(D_S[d].drv_type&amp;(drv_fam0|drv_famL))
DECL|macro|fam0V_drive
mdefine_line|#define fam0V_drive&t;(D_S[d].drv_type&amp;(drv_fam0|drv_famV))
DECL|macro|famLV_drive
mdefine_line|#define famLV_drive&t;(D_S[d].drv_type&amp;(drv_famL|drv_famV))
DECL|macro|fam0LV_drive
mdefine_line|#define fam0LV_drive&t;(D_S[d].drv_type&amp;(drv_fam0|drv_famL|drv_famV))
DECL|macro|fam1L_drive
mdefine_line|#define fam1L_drive&t;(D_S[d].drv_type&amp;(drv_fam1|drv_famL))
DECL|macro|fam1V_drive
mdefine_line|#define fam1V_drive&t;(D_S[d].drv_type&amp;(drv_fam1|drv_famV))
DECL|macro|fam1LV_drive
mdefine_line|#define fam1LV_drive&t;(D_S[d].drv_type&amp;(drv_fam1|drv_famL|drv_famV))
DECL|macro|fam01_drive
mdefine_line|#define fam01_drive&t;(D_S[d].drv_type&amp;(drv_fam0|drv_fam1))
DECL|macro|fam12_drive
mdefine_line|#define fam12_drive&t;(D_S[d].drv_type&amp;(drv_fam1|drv_fam2))
DECL|macro|fam2T_drive
mdefine_line|#define fam2T_drive&t;(D_S[d].drv_type&amp;(drv_fam2|drv_famT))
multiline_comment|/*&n; * audio states:&n; */
DECL|macro|audio_completed
mdefine_line|#define audio_completed&t;3 /* Forgot this one! --AJK */
DECL|macro|audio_playing
mdefine_line|#define audio_playing&t;2
DECL|macro|audio_pausing
mdefine_line|#define audio_pausing&t;1
multiline_comment|/*&n; * drv_pattern, drv_options:&n; */
DECL|macro|speed_auto
mdefine_line|#define speed_auto&t;0x80
DECL|macro|speed_300
mdefine_line|#define speed_300&t;0x40
DECL|macro|speed_150
mdefine_line|#define speed_150&t;0x20
DECL|macro|audio_mono
mdefine_line|#define audio_mono&t;0x04
multiline_comment|/*&n; * values of cmd_type (0 else):&n; */
DECL|macro|READ_M1
mdefine_line|#define READ_M1&t;0x01&t;/* &quot;data mode 1&quot;: 2048 bytes per frame */
DECL|macro|READ_M2
mdefine_line|#define READ_M2&t;0x02&t;/* &quot;data mode 2&quot;: 12+2048+280 bytes per frame */
DECL|macro|READ_SC
mdefine_line|#define READ_SC&t;0x04&t;/* &quot;subchannel info&quot;: 96 bytes per frame */
DECL|macro|READ_AU
mdefine_line|#define READ_AU&t;0x08&t;/* &quot;audio frame&quot;: 2352 bytes per frame */
multiline_comment|/*&n; * sense_byte:&n; *&n; *          values: 00&n; *                  01&n; *                  81&n; *                  82 &quot;raw audio&quot; mode&n; *                  xx from infobuf[0] after 85 00 00 00 00 00 00&n; */
multiline_comment|/* audio status (bin) */
DECL|macro|aud_00
mdefine_line|#define aud_00 0x00 /* Audio status byte not supported or not valid */
DECL|macro|audx11
mdefine_line|#define audx11 0x0b /* Audio play operation in progress             */
DECL|macro|audx12
mdefine_line|#define audx12 0x0c /* Audio play operation paused                  */
DECL|macro|audx13
mdefine_line|#define audx13 0x0d /* Audio play operation successfully completed  */
DECL|macro|audx14
mdefine_line|#define audx14 0x0e /* Audio play operation stopped due to error    */
DECL|macro|audx15
mdefine_line|#define audx15 0x0f /* No current audio status to return            */
multiline_comment|/* audio status (bcd) */
DECL|macro|aud_11
mdefine_line|#define aud_11 0x11 /* Audio play operation in progress             */
DECL|macro|aud_12
mdefine_line|#define aud_12 0x12 /* Audio play operation paused                  */
DECL|macro|aud_13
mdefine_line|#define aud_13 0x13 /* Audio play operation successfully completed  */
DECL|macro|aud_14
mdefine_line|#define aud_14 0x14 /* Audio play operation stopped due to error    */
DECL|macro|aud_15
mdefine_line|#define aud_15 0x15 /* No current audio status to return            */
multiline_comment|/*&n; * highest allowed drive number (MINOR+1)&n; */
DECL|macro|NR_SBPCD
mdefine_line|#define NR_SBPCD&t;4
multiline_comment|/*&n; * we try to never disable interrupts - seems to work&n; */
DECL|macro|SBPCD_DIS_IRQ
mdefine_line|#define SBPCD_DIS_IRQ&t;0
multiline_comment|/*&n; * &quot;write byte to port&quot;&n; */
DECL|macro|OUT
mdefine_line|#define OUT(x,y)&t;outb(y,x)
multiline_comment|/*==========================================================================*/
DECL|macro|MIXER_addr
mdefine_line|#define MIXER_addr SOUND_BASE+4 /* sound card&squot;s address register */
DECL|macro|MIXER_data
mdefine_line|#define MIXER_data SOUND_BASE+5 /* sound card&squot;s data register */
DECL|macro|MIXER_CD_Volume
mdefine_line|#define MIXER_CD_Volume&t;0x28&t;/* internal SB Pro register address */
multiline_comment|/*==========================================================================*/
DECL|macro|MAX_TRACKS
mdefine_line|#define MAX_TRACKS&t;99
DECL|macro|ERR_DISKCHANGE
mdefine_line|#define ERR_DISKCHANGE 615
multiline_comment|/*==========================================================================*/
multiline_comment|/*&n; * To make conversions easier (machine dependent!)&n; */
DECL|union|_msf
r_typedef
r_union
id|_msf
(brace
DECL|member|n
id|u_int
id|n
suffix:semicolon
DECL|member|c
id|u_char
id|c
(braket
l_int|4
)braket
suffix:semicolon
DECL|typedef|MSF
)brace
id|MSF
suffix:semicolon
DECL|union|_blk
r_typedef
r_union
id|_blk
(brace
DECL|member|n
id|u_int
id|n
suffix:semicolon
DECL|member|c
id|u_char
id|c
(braket
l_int|4
)braket
suffix:semicolon
DECL|typedef|BLK
)brace
id|BLK
suffix:semicolon
multiline_comment|/*==========================================================================*/
multiline_comment|/*============================================================================&n;==============================================================================&n;&n;COMMAND SET of &quot;old&quot; drives like CR-521, CR-522&n;               (the CR-562 family is different):&n;&n;No.&t;Command&t;&t;&t;       Code&n;--------------------------------------------&n;&n;Drive Commands:&n; 1&t;Seek&t;&t;&t;&t;01&t;&n; 2&t;Read Data&t;&t;&t;02&n; 3&t;Read XA-Data&t;&t;&t;03&n; 4&t;Read Header&t;&t;&t;04&n; 5&t;Spin Up&t;&t;&t;&t;05&n; 6&t;Spin Down&t;&t;&t;06&n; 7&t;Diagnostic&t;&t;&t;07&n; 8&t;Read UPC&t;&t;&t;08&n; 9&t;Read ISRC&t;&t;&t;09&n;10&t;Play Audio&t;&t;&t;0A&n;11&t;Play Audio MSF&t;&t;&t;0B&n;12&t;Play Audio Track/Index&t;&t;0C&n;&n;Status Commands:&n;13&t;Read Status&t;&t;&t;81&t;&n;14&t;Read Error&t;&t;&t;82&n;15&t;Read Drive Version&t;&t;83&n;16&t;Mode Select&t;&t;&t;84&n;17&t;Mode Sense&t;&t;&t;85&n;18&t;Set XA Parameter&t;&t;86&n;19&t;Read XA Parameter&t;&t;87&n;20&t;Read Capacity&t;&t;&t;88&n;21&t;Read SUB_Q&t;&t;&t;89&n;22&t;Read Disc Code&t;&t;&t;8A&n;23&t;Read Disc Information&t;&t;8B&n;24&t;Read TOC&t;&t;&t;8C&n;25&t;Pause/Resume&t;&t;&t;8D&n;26&t;Read Packet&t;&t;&t;8E&n;27&t;Read Path Check&t;&t;&t;00&n; &n; &n;all numbers (lba, msf-bin, msf-bcd, counts) to transfer high byte first&n;&n;mnemo     7-byte command        #bytes response (r0...rn)&n;________ ____________________  ____ &n;&n;Read Status:&n;status:  81.                    (1)  one-byte command, gives the main&n;                                                          status byte&n;Read Error:&n;check1:  82 00 00 00 00 00 00.  (6)  r1: audio status&n;&n;Read Packet:&n;check2:  8e xx 00 00 00 00 00. (xx)  gets xx bytes response, relating&n;                                        to commands 01 04 05 07 08 09&n;&n;Play Audio:&n;play:    0a ll-bb-aa nn-nn-nn.  (0)  play audio, ll-bb-aa: starting block (lba),&n;                                                 nn-nn-nn: #blocks&n;Play Audio MSF:&n;         0b mm-ss-ff mm-ss-ff   (0)  play audio from/to&n;&n;Play Audio Track/Index:&n;         0c ...&n;&n;Pause/Resume:&n;pause:   8d pr 00 00 00 00 00.  (0)  pause (pr=00) &n;                                     resume (pr=80) audio playing&n;&n;Mode Select:&n;         84 00 nn-nn ??.?? 00   (0)  nn-nn: 2048 or 2340&n;                                     possibly defines transfer size&n;&n;set_vol: 84 83 00 00 sw le 00.  (0)  sw(itch): lrxxxxxx (off=1)&n;                                     le(vel): min=0, max=FF, else half&n;&t;&t;&t;&t;     (firmware 2.11)&n;&n;Mode Sense:&n;get_vol: 85 03 00 00 00 00 00.  (2)  tell current audio volume setting&n;&n;Read Disc Information:&n;tocdesc: 8b 00 00 00 00 00 00.  (6)  read the toc descriptor (&quot;msf-bin&quot;-format)&n;&n;Read TOC:&n;tocent:  8c fl nn 00 00 00 00.  (8)  read toc entry #nn&n;                                       (fl=0:&quot;lba&quot;-, =2:&quot;msf-bin&quot;-format)&n;&n;Read Capacity:&n;capacit: 88 00 00 00 00 00 00.  (5)  &quot;read CD-ROM capacity&quot;&n;&n;&n;Read Path Check:&n;ping:    00 00 00 00 00 00 00.  (2)  r0=AA, r1=55&n;                                     (&quot;ping&quot; if the drive is connected)&n;&n;Read Drive Version:&n;ident:   83 00 00 00 00 00 00. (12)  gives &quot;MATSHITAn.nn&quot; &n;                                     (n.nn = 2.01, 2.11., 3.00, ...)&n;&n;Seek:&n;seek:    01 00 ll-bb-aa 00 00.  (0)  &n;seek:    01 02 mm-ss-ff 00 00.  (0)  &n;&n;Read Data:&n;read:    02 xx-xx-xx nn-nn fl.  (?)  read nn-nn blocks of 2048 bytes,&n;                                     starting at block xx-xx-xx  &n;                                     fl=0: &quot;lba&quot;-, =2:&quot;msf-bcd&quot;-coded xx-xx-xx&n;&n;Read XA-Data:&n;read:    03 xx-xx-xx nn-nn fl.  (?)  read nn-nn blocks of 2340 bytes, &n;                                     starting at block xx-xx-xx&n;                                     fl=0: &quot;lba&quot;-, =2:&quot;msf-bcd&quot;-coded xx-xx-xx&n;&n;Read SUB_Q:&n;         89 fl 00 00 00 00 00. (13)  r0: audio status, r4-r7: lba/msf, &n;                                       fl=0: &quot;lba&quot;, fl=2: &quot;msf&quot;&n;&n;Read Disc Code:&n;         8a 00 00 00 00 00 00. (14)  possibly extended &quot;check condition&quot;-info&n;&n;Read Header:&n;         04 00 ll-bb-aa 00 00.  (0)   4 bytes response with &quot;check2&quot;&n;         04 02 mm-ss-ff 00 00.  (0)   4 bytes response with &quot;check2&quot;&n;&n;Spin Up:&n;         05 00 ll-bb-aa 00 00.  (0)  possibly implies a &quot;seek&quot;&n;&n;Spin Down:&n;         06 ...&n;&n;Diagnostic:&n;         07 00 ll-bb-aa 00 00.  (2)   2 bytes response with &quot;check2&quot;&n;         07 02 mm-ss-ff 00 00.  (2)   2 bytes response with &quot;check2&quot;&n;&n;Read UPC:&n;         08 00 ll-bb-aa 00 00. (16)  &n;         08 02 mm-ss-ff 00 00. (16)  &n;&n;Read ISRC:&n;         09 00 ll-bb-aa 00 00. (15)  15 bytes response with &quot;check2&quot;&n;         09 02 mm-ss-ff 00 00. (15)  15 bytes response with &quot;check2&quot;&n;&n;Set XA Parameter:&n;         86 ...&n;&n;Read XA Parameter:&n;         87 ...&n;&n;==============================================================================&n;============================================================================*/
multiline_comment|/*&n; * commands&n; *&n; * CR-52x:      CMD0_&n; * CR-56x:      CMD1_&n; * CD200:       CMD2_&n; * LCS-7260:    CMDL_&n; * TEAC CD-55A: CMDT_&n; * ECS-AT:      CMDV_&n; */
DECL|macro|CMD1_RESET
mdefine_line|#define CMD1_RESET&t;0x0a
DECL|macro|CMD2_RESET
mdefine_line|#define CMD2_RESET&t;0x01
DECL|macro|CMDT_RESET
mdefine_line|#define CMDT_RESET&t;0xc0
DECL|macro|CMD1_LOCK_CTL
mdefine_line|#define CMD1_LOCK_CTL&t;0x0c
DECL|macro|CMD2_LOCK_CTL
mdefine_line|#define CMD2_LOCK_CTL&t;0x1e
DECL|macro|CMDT_LOCK_CTL
mdefine_line|#define CMDT_LOCK_CTL&t;CMD2_LOCK_CTL
DECL|macro|CMDL_LOCK_CTL
mdefine_line|#define CMDL_LOCK_CTL&t;0x0e
DECL|macro|CMDV_LOCK_CTL
mdefine_line|#define CMDV_LOCK_CTL&t;CMDL_LOCK_CTL
DECL|macro|CMD1_TRAY_CTL
mdefine_line|#define CMD1_TRAY_CTL&t;0x07
DECL|macro|CMD2_TRAY_CTL
mdefine_line|#define CMD2_TRAY_CTL&t;0x1b
DECL|macro|CMDT_TRAY_CTL
mdefine_line|#define CMDT_TRAY_CTL&t;CMD2_TRAY_CTL
DECL|macro|CMDL_TRAY_CTL
mdefine_line|#define CMDL_TRAY_CTL&t;0x0d
DECL|macro|CMDV_TRAY_CTL
mdefine_line|#define CMDV_TRAY_CTL&t;CMDL_TRAY_CTL
DECL|macro|CMD1_MULTISESS
mdefine_line|#define CMD1_MULTISESS&t;0x8d
DECL|macro|CMDL_MULTISESS
mdefine_line|#define CMDL_MULTISESS&t;0x8c
DECL|macro|CMDV_MULTISESS
mdefine_line|#define CMDV_MULTISESS&t;CMDL_MULTISESS
DECL|macro|CMD1_SUBCHANINF
mdefine_line|#define CMD1_SUBCHANINF&t;0x11
DECL|macro|CMD2_SUBCHANINF
mdefine_line|#define CMD2_SUBCHANINF&t;0x??
DECL|macro|CMD1_ABORT
mdefine_line|#define CMD1_ABORT&t;0x08
DECL|macro|CMD2_ABORT
mdefine_line|#define CMD2_ABORT&t;0x08
DECL|macro|CMDT_ABORT
mdefine_line|#define CMDT_ABORT&t;0x08
DECL|macro|CMD2_x02
mdefine_line|#define CMD2_x02&t;0x02
DECL|macro|CMD2_SETSPEED
mdefine_line|#define CMD2_SETSPEED&t;0xda
DECL|macro|CMD0_PATH_CHECK
mdefine_line|#define CMD0_PATH_CHECK&t;0x00
DECL|macro|CMD1_PATH_CHECK
mdefine_line|#define CMD1_PATH_CHECK&t;0x???
DECL|macro|CMD2_PATH_CHECK
mdefine_line|#define CMD2_PATH_CHECK&t;0x???
DECL|macro|CMDT_PATH_CHECK
mdefine_line|#define CMDT_PATH_CHECK&t;0x???
DECL|macro|CMDL_PATH_CHECK
mdefine_line|#define CMDL_PATH_CHECK&t;CMD0_PATH_CHECK
DECL|macro|CMDV_PATH_CHECK
mdefine_line|#define CMDV_PATH_CHECK&t;CMD0_PATH_CHECK
DECL|macro|CMD0_SEEK
mdefine_line|#define CMD0_SEEK&t;0x01
DECL|macro|CMD1_SEEK
mdefine_line|#define CMD1_SEEK&t;CMD0_SEEK
DECL|macro|CMD2_SEEK
mdefine_line|#define CMD2_SEEK&t;0x2b
DECL|macro|CMDT_SEEK
mdefine_line|#define CMDT_SEEK&t;CMD2_SEEK
DECL|macro|CMDL_SEEK
mdefine_line|#define CMDL_SEEK&t;CMD0_SEEK
DECL|macro|CMDV_SEEK
mdefine_line|#define CMDV_SEEK&t;CMD0_SEEK
DECL|macro|CMD0_READ
mdefine_line|#define CMD0_READ&t;0x02
DECL|macro|CMD1_READ
mdefine_line|#define CMD1_READ&t;0x10
DECL|macro|CMD2_READ
mdefine_line|#define CMD2_READ&t;0x28
DECL|macro|CMDT_READ
mdefine_line|#define CMDT_READ&t;CMD2_READ
DECL|macro|CMDL_READ
mdefine_line|#define CMDL_READ&t;CMD0_READ
DECL|macro|CMDV_READ
mdefine_line|#define CMDV_READ&t;CMD0_READ
DECL|macro|CMD0_READ_XA
mdefine_line|#define CMD0_READ_XA&t;0x03
DECL|macro|CMD2_READ_XA
mdefine_line|#define CMD2_READ_XA&t;0xd4
DECL|macro|CMD2_READ_XA2
mdefine_line|#define CMD2_READ_XA2&t;0xd5
DECL|macro|CMDL_READ_XA
mdefine_line|#define CMDL_READ_XA&t;CMD0_READ_XA /* really ?? */
DECL|macro|CMDV_READ_XA
mdefine_line|#define CMDV_READ_XA&t;CMD0_READ_XA
DECL|macro|CMD0_READ_HEAD
mdefine_line|#define CMD0_READ_HEAD&t;0x04
DECL|macro|CMD0_SPINUP
mdefine_line|#define CMD0_SPINUP&t;0x05
DECL|macro|CMD1_SPINUP
mdefine_line|#define CMD1_SPINUP&t;0x02
DECL|macro|CMD2_SPINUP
mdefine_line|#define CMD2_SPINUP&t;CMD2_TRAY_CTL
DECL|macro|CMDL_SPINUP
mdefine_line|#define CMDL_SPINUP&t;CMD0_SPINUP
DECL|macro|CMDV_SPINUP
mdefine_line|#define CMDV_SPINUP&t;CMD0_SPINUP
DECL|macro|CMD0_SPINDOWN
mdefine_line|#define CMD0_SPINDOWN&t;0x06 /* really??? */
DECL|macro|CMD1_SPINDOWN
mdefine_line|#define CMD1_SPINDOWN&t;0x06
DECL|macro|CMD2_SPINDOWN
mdefine_line|#define CMD2_SPINDOWN&t;CMD2_TRAY_CTL
DECL|macro|CMDL_SPINDOWN
mdefine_line|#define CMDL_SPINDOWN&t;0x0d
DECL|macro|CMDV_SPINDOWN
mdefine_line|#define CMDV_SPINDOWN&t;CMD0_SPINDOWN
DECL|macro|CMD0_DIAG
mdefine_line|#define CMD0_DIAG&t;0x07
DECL|macro|CMD0_READ_UPC
mdefine_line|#define CMD0_READ_UPC&t;0x08
DECL|macro|CMD1_READ_UPC
mdefine_line|#define CMD1_READ_UPC&t;0x88
DECL|macro|CMD2_READ_UPC
mdefine_line|#define CMD2_READ_UPC&t;0x???
DECL|macro|CMDL_READ_UPC
mdefine_line|#define CMDL_READ_UPC&t;CMD0_READ_UPC
DECL|macro|CMDV_READ_UPC
mdefine_line|#define CMDV_READ_UPC&t;0x8f
DECL|macro|CMD0_READ_ISRC
mdefine_line|#define CMD0_READ_ISRC&t;0x09
DECL|macro|CMD0_PLAY
mdefine_line|#define CMD0_PLAY&t;0x0a
DECL|macro|CMD1_PLAY
mdefine_line|#define CMD1_PLAY&t;0x???
DECL|macro|CMD2_PLAY
mdefine_line|#define CMD2_PLAY&t;0x???
DECL|macro|CMDL_PLAY
mdefine_line|#define CMDL_PLAY&t;CMD0_PLAY
DECL|macro|CMDV_PLAY
mdefine_line|#define CMDV_PLAY&t;CMD0_PLAY
DECL|macro|CMD0_PLAY_MSF
mdefine_line|#define CMD0_PLAY_MSF&t;0x0b
DECL|macro|CMD1_PLAY_MSF
mdefine_line|#define CMD1_PLAY_MSF&t;0x0e
DECL|macro|CMD2_PLAY_MSF
mdefine_line|#define CMD2_PLAY_MSF&t;0x47
DECL|macro|CMDT_PLAY_MSF
mdefine_line|#define CMDT_PLAY_MSF&t;CMD2_PLAY_MSF
DECL|macro|CMDL_PLAY_MSF
mdefine_line|#define CMDL_PLAY_MSF&t;0x???
DECL|macro|CMD0_PLAY_TI
mdefine_line|#define CMD0_PLAY_TI&t;0x0c
DECL|macro|CMD1_PLAY_TI
mdefine_line|#define CMD1_PLAY_TI&t;0x0f
DECL|macro|CMD0_STATUS
mdefine_line|#define CMD0_STATUS&t;0x81
DECL|macro|CMD1_STATUS
mdefine_line|#define CMD1_STATUS&t;0x05
DECL|macro|CMD2_STATUS
mdefine_line|#define CMD2_STATUS&t;0x00
DECL|macro|CMDT_STATUS
mdefine_line|#define CMDT_STATUS&t;CMD2_STATUS
DECL|macro|CMDL_STATUS
mdefine_line|#define CMDL_STATUS&t;CMD0_STATUS
DECL|macro|CMDV_STATUS
mdefine_line|#define CMDV_STATUS&t;CMD0_STATUS
DECL|macro|CMD2_SEEK_LEADIN
mdefine_line|#define CMD2_SEEK_LEADIN 0x00
DECL|macro|CMD0_READ_ERR
mdefine_line|#define CMD0_READ_ERR&t;0x82
DECL|macro|CMD1_READ_ERR
mdefine_line|#define CMD1_READ_ERR&t;CMD0_READ_ERR
DECL|macro|CMD2_READ_ERR
mdefine_line|#define CMD2_READ_ERR&t;0x03
DECL|macro|CMDT_READ_ERR
mdefine_line|#define CMDT_READ_ERR&t;CMD2_READ_ERR /* get audio status */
DECL|macro|CMDL_READ_ERR
mdefine_line|#define CMDL_READ_ERR&t;CMD0_READ_ERR
DECL|macro|CMDV_READ_ERR
mdefine_line|#define CMDV_READ_ERR&t;CMD0_READ_ERR
DECL|macro|CMD0_READ_VER
mdefine_line|#define CMD0_READ_VER&t;0x83
DECL|macro|CMD1_READ_VER
mdefine_line|#define CMD1_READ_VER&t;CMD0_READ_VER
DECL|macro|CMD2_READ_VER
mdefine_line|#define CMD2_READ_VER&t;0x12
DECL|macro|CMDT_READ_VER
mdefine_line|#define CMDT_READ_VER&t;CMD2_READ_VER /* really ?? */
DECL|macro|CMDL_READ_VER
mdefine_line|#define CMDL_READ_VER&t;CMD0_READ_VER
DECL|macro|CMDV_READ_VER
mdefine_line|#define CMDV_READ_VER&t;CMD0_READ_VER
DECL|macro|CMD0_SETMODE
mdefine_line|#define CMD0_SETMODE&t;0x84
DECL|macro|CMD1_SETMODE
mdefine_line|#define CMD1_SETMODE&t;0x09
DECL|macro|CMD2_SETMODE
mdefine_line|#define CMD2_SETMODE&t;0x55
DECL|macro|CMDT_SETMODE
mdefine_line|#define CMDT_SETMODE&t;CMD2_SETMODE
DECL|macro|CMDL_SETMODE
mdefine_line|#define CMDL_SETMODE&t;CMD0_SETMODE
DECL|macro|CMD0_GETMODE
mdefine_line|#define CMD0_GETMODE&t;0x85
DECL|macro|CMD1_GETMODE
mdefine_line|#define CMD1_GETMODE&t;0x84
DECL|macro|CMD2_GETMODE
mdefine_line|#define CMD2_GETMODE&t;0x5a
DECL|macro|CMDT_GETMODE
mdefine_line|#define CMDT_GETMODE&t;CMD2_GETMODE
DECL|macro|CMDL_GETMODE
mdefine_line|#define CMDL_GETMODE&t;CMD0_GETMODE
DECL|macro|CMD0_SET_XA
mdefine_line|#define CMD0_SET_XA&t;0x86
DECL|macro|CMD0_GET_XA
mdefine_line|#define CMD0_GET_XA&t;0x87
DECL|macro|CMD0_CAPACITY
mdefine_line|#define CMD0_CAPACITY&t;0x88
DECL|macro|CMD1_CAPACITY
mdefine_line|#define CMD1_CAPACITY&t;0x85
DECL|macro|CMD2_CAPACITY
mdefine_line|#define CMD2_CAPACITY&t;0x25
DECL|macro|CMDL_CAPACITY
mdefine_line|#define CMDL_CAPACITY&t;CMD0_CAPACITY /* missing in some firmware versions */
DECL|macro|CMD0_READSUBQ
mdefine_line|#define CMD0_READSUBQ&t;0x89
DECL|macro|CMD1_READSUBQ
mdefine_line|#define CMD1_READSUBQ&t;0x87
DECL|macro|CMD2_READSUBQ
mdefine_line|#define CMD2_READSUBQ&t;0x42
DECL|macro|CMDT_READSUBQ
mdefine_line|#define CMDT_READSUBQ&t;CMD2_READSUBQ
DECL|macro|CMDL_READSUBQ
mdefine_line|#define CMDL_READSUBQ&t;CMD0_READSUBQ
DECL|macro|CMDV_READSUBQ
mdefine_line|#define CMDV_READSUBQ&t;CMD0_READSUBQ
DECL|macro|CMD0_DISKCODE
mdefine_line|#define CMD0_DISKCODE&t;0x8a
DECL|macro|CMD0_DISKINFO
mdefine_line|#define CMD0_DISKINFO&t;0x8b
DECL|macro|CMD1_DISKINFO
mdefine_line|#define CMD1_DISKINFO&t;CMD0_DISKINFO
DECL|macro|CMD2_DISKINFO
mdefine_line|#define CMD2_DISKINFO&t;0x43
DECL|macro|CMDT_DISKINFO
mdefine_line|#define CMDT_DISKINFO&t;CMD2_DISKINFO
DECL|macro|CMDL_DISKINFO
mdefine_line|#define CMDL_DISKINFO&t;CMD0_DISKINFO
DECL|macro|CMDV_DISKINFO
mdefine_line|#define CMDV_DISKINFO&t;CMD0_DISKINFO
DECL|macro|CMD0_READTOC
mdefine_line|#define CMD0_READTOC&t;0x8c
DECL|macro|CMD1_READTOC
mdefine_line|#define CMD1_READTOC&t;CMD0_READTOC
DECL|macro|CMD2_READTOC
mdefine_line|#define CMD2_READTOC&t;0x???
DECL|macro|CMDL_READTOC
mdefine_line|#define CMDL_READTOC&t;CMD0_READTOC
DECL|macro|CMDV_READTOC
mdefine_line|#define CMDV_READTOC&t;CMD0_READTOC
DECL|macro|CMD0_PAU_RES
mdefine_line|#define CMD0_PAU_RES&t;0x8d
DECL|macro|CMD1_PAU_RES
mdefine_line|#define CMD1_PAU_RES&t;0x0d
DECL|macro|CMD2_PAU_RES
mdefine_line|#define CMD2_PAU_RES&t;0x4b
DECL|macro|CMDT_PAUSE
mdefine_line|#define CMDT_PAUSE&t;CMD2_PAU_RES
DECL|macro|CMDL_PAU_RES
mdefine_line|#define CMDL_PAU_RES&t;CMD0_PAU_RES
DECL|macro|CMDV_PAUSE
mdefine_line|#define CMDV_PAUSE&t;CMD0_PAU_RES
DECL|macro|CMD0_PACKET
mdefine_line|#define CMD0_PACKET&t;0x8e
DECL|macro|CMD1_PACKET
mdefine_line|#define CMD1_PACKET&t;CMD0_PACKET
DECL|macro|CMD2_PACKET
mdefine_line|#define CMD2_PACKET&t;0x???
DECL|macro|CMDL_PACKET
mdefine_line|#define CMDL_PACKET&t;CMD0_PACKET
DECL|macro|CMDV_PACKET
mdefine_line|#define CMDV_PACKET&t;0x???
multiline_comment|/*==========================================================================*/
multiline_comment|/*==========================================================================*/
macro_line|#endif /* _LINUX_SBPCD_H */
multiline_comment|/*==========================================================================*/
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file. &n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-indent-level: 8&n; * c-brace-imaginary-offset: 0&n; * c-brace-offset: -8&n; * c-argdecl-indent: 8&n; * c-label-offset: -8&n; * c-continued-statement-offset: 8&n; * c-continued-brace-offset: 0&n; * End:&n; */
eof
