multiline_comment|/*&n; * This file define a set of standard wireless extensions&n; *&n; * Version :&t;11&t;28.3.01&n; *&n; * Authors :&t;Jean Tourrilhes - HPL - &lt;jt@hpl.hp.com&gt;&n; */
macro_line|#ifndef _LINUX_WIRELESS_H
DECL|macro|_LINUX_WIRELESS_H
mdefine_line|#define _LINUX_WIRELESS_H
multiline_comment|/************************** DOCUMENTATION **************************/
multiline_comment|/*&n; * Basically, the wireless extensions are for now a set of standard ioctl&n; * call + /proc/net/wireless&n; *&n; * The entry /proc/net/wireless give statistics and information on the&n; * driver.&n; * This is better than having each driver having its entry because&n; * its centralised and we may remove the driver module safely.&n; *&n; * Ioctl are used to configure the driver and issue commands.  This is&n; * better than command line options of insmod because we may want to&n; * change dynamically (while the driver is running) some parameters.&n; *&n; * The ioctl mechanimsm are copied from standard devices ioctl.&n; * We have the list of command plus a structure descibing the&n; * data exchanged...&n; * Note that to add these ioctl, I was obliged to modify :&n; *&t;net/core/dev.c (two place + add include)&n; *&t;net/ipv4/af_inet.c (one place + add include)&n; *&n; * /proc/net/wireless is a copy of /proc/net/dev.&n; * We have a structure for data passed from the driver to /proc/net/wireless&n; * Too add this, I&squot;ve modified :&n; *&t;net/core/dev.c (two other places)&n; *&t;include/linux/netdevice.h (one place)&n; *&t;include/linux/proc_fs.h (one place)&n; *&n; * Do not add here things that are redundant with other mechanisms&n; * (drivers init, ifconfig, /proc/net/dev, ...) and with are not&n; * wireless specific.&n; *&n; * These wireless extensions are not magic : each driver has to provide&n; * support for them...&n; *&n; * IMPORTANT NOTE : As everything in the kernel, this is very much a&n; * work in progress. Contact me if you have ideas of improvements...&n; */
multiline_comment|/***************************** INCLUDES *****************************/
macro_line|#include &lt;linux/types.h&gt;&t;&t;/* for &quot;caddr_t&quot; et al&t;&t;*/
macro_line|#include &lt;linux/socket.h&gt;&t;&t;/* for &quot;struct sockaddr&quot; et al&t;*/
macro_line|#include &lt;linux/if.h&gt;&t;&t;&t;/* for IFNAMSIZ and co... */
multiline_comment|/**************************** CONSTANTS ****************************/
multiline_comment|/* --------------------------- VERSION --------------------------- */
multiline_comment|/*&n; * This constant is used to know the availability of the wireless&n; * extensions and to know which version of wireless extensions it is&n; * (there is some stuff that will be added in the future...)&n; * I just plan to increment with each new version.&n; */
DECL|macro|WIRELESS_EXT
mdefine_line|#define WIRELESS_EXT&t;11
multiline_comment|/*&n; * Changes :&n; *&n; * V2 to V3&n; * --------&n; *&t;Alan Cox start some incompatibles changes. I&squot;ve integrated a bit more.&n; *&t;- Encryption renamed to Encode to avoid US regulation problems&n; *&t;- Frequency changed from float to struct to avoid problems on old 386&n; *&n; * V3 to V4&n; * --------&n; *&t;- Add sensitivity&n; *&n; * V4 to V5&n; * --------&n; *&t;- Missing encoding definitions in range&n; *&t;- Access points stuff&n; *&n; * V5 to V6&n; * --------&n; *&t;- 802.11 support (ESSID ioctls)&n; *&n; * V6 to V7&n; * --------&n; *&t;- define IW_ESSID_MAX_SIZE and IW_MAX_AP&n; *&n; * V7 to V8&n; * --------&n; *&t;- Changed my e-mail address&n; *&t;- More 802.11 support (nickname, rate, rts, frag)&n; *&t;- List index in frequencies&n; *&n; * V8 to V9&n; * --------&n; *&t;- Support for &squot;mode of operation&squot; (ad-hoc, managed...)&n; *&t;- Support for unicast and multicast power saving&n; *&t;- Change encoding to support larger tokens (&gt;64 bits)&n; *&t;- Updated iw_params (disable, flags) and use it for NWID&n; *&t;- Extracted iw_point from iwreq for clarity&n; *&n; * V9 to V10&n; * ---------&n; *&t;- Add PM capability to range structure&n; *&t;- Add PM modifier : MAX/MIN/RELATIVE&n; *&t;- Add encoding option : IW_ENCODE_NOKEY&n; *&t;- Add TxPower ioctls (work like TxRate)&n; *&n; * V10 to V11&n; * ----------&n; *&t;- Add WE version in range (help backward/forward compatibility)&n; *&t;- Add retry ioctls (work like PM)&n; */
multiline_comment|/* -------------------------- IOCTL LIST -------------------------- */
multiline_comment|/* Basic operations */
DECL|macro|SIOCSIWNAME
mdefine_line|#define SIOCSIWNAME&t;0x8B00&t;&t;/* Unused */
DECL|macro|SIOCGIWNAME
mdefine_line|#define SIOCGIWNAME&t;0x8B01&t;&t;/* get name == wireless protocol */
DECL|macro|SIOCSIWNWID
mdefine_line|#define SIOCSIWNWID&t;0x8B02&t;&t;/* set network id (the cell) */
DECL|macro|SIOCGIWNWID
mdefine_line|#define SIOCGIWNWID&t;0x8B03&t;&t;/* get network id */
DECL|macro|SIOCSIWFREQ
mdefine_line|#define SIOCSIWFREQ&t;0x8B04&t;&t;/* set channel/frequency (Hz) */
DECL|macro|SIOCGIWFREQ
mdefine_line|#define SIOCGIWFREQ&t;0x8B05&t;&t;/* get channel/frequency (Hz) */
DECL|macro|SIOCSIWMODE
mdefine_line|#define SIOCSIWMODE&t;0x8B06&t;&t;/* set operation mode */
DECL|macro|SIOCGIWMODE
mdefine_line|#define SIOCGIWMODE&t;0x8B07&t;&t;/* get operation mode */
DECL|macro|SIOCSIWSENS
mdefine_line|#define SIOCSIWSENS&t;0x8B08&t;&t;/* set sensitivity (dBm) */
DECL|macro|SIOCGIWSENS
mdefine_line|#define SIOCGIWSENS&t;0x8B09&t;&t;/* get sensitivity (dBm) */
multiline_comment|/* Informative stuff */
DECL|macro|SIOCSIWRANGE
mdefine_line|#define SIOCSIWRANGE&t;0x8B0A&t;&t;/* Unused */
DECL|macro|SIOCGIWRANGE
mdefine_line|#define SIOCGIWRANGE&t;0x8B0B&t;&t;/* Get range of parameters */
DECL|macro|SIOCSIWPRIV
mdefine_line|#define SIOCSIWPRIV&t;0x8B0C&t;&t;/* Unused */
DECL|macro|SIOCGIWPRIV
mdefine_line|#define SIOCGIWPRIV&t;0x8B0D&t;&t;/* get private ioctl interface info */
multiline_comment|/* Mobile IP support */
DECL|macro|SIOCSIWSPY
mdefine_line|#define SIOCSIWSPY&t;0x8B10&t;&t;/* set spy addresses */
DECL|macro|SIOCGIWSPY
mdefine_line|#define SIOCGIWSPY&t;0x8B11&t;&t;/* get spy info (quality of link) */
multiline_comment|/* Access Point manipulation */
DECL|macro|SIOCSIWAP
mdefine_line|#define SIOCSIWAP&t;0x8B14&t;&t;/* set access point MAC addresses */
DECL|macro|SIOCGIWAP
mdefine_line|#define SIOCGIWAP&t;0x8B15&t;&t;/* get access point MAC addresses */
DECL|macro|SIOCGIWAPLIST
mdefine_line|#define SIOCGIWAPLIST&t;0x8B17&t;&t;/* get list of access point in range */
multiline_comment|/* 802.11 specific support */
DECL|macro|SIOCSIWESSID
mdefine_line|#define SIOCSIWESSID&t;0x8B1A&t;&t;/* set ESSID (network name) */
DECL|macro|SIOCGIWESSID
mdefine_line|#define SIOCGIWESSID&t;0x8B1B&t;&t;/* get ESSID */
DECL|macro|SIOCSIWNICKN
mdefine_line|#define SIOCSIWNICKN&t;0x8B1C&t;&t;/* set node name/nickname */
DECL|macro|SIOCGIWNICKN
mdefine_line|#define SIOCGIWNICKN&t;0x8B1D&t;&t;/* get node name/nickname */
multiline_comment|/* As the ESSID and NICKN are strings up to 32 bytes long, it doesn&squot;t fit&n; * within the &squot;iwreq&squot; structure, so we need to use the &squot;data&squot; member to&n; * point to a string in user space, like it is done for RANGE...&n; * The &quot;flags&quot; member indicate if the ESSID is active or not (promiscuous).&n; */
multiline_comment|/* Other parameters useful in 802.11 and some other devices */
DECL|macro|SIOCSIWRATE
mdefine_line|#define SIOCSIWRATE&t;0x8B20&t;&t;/* set default bit rate (bps) */
DECL|macro|SIOCGIWRATE
mdefine_line|#define SIOCGIWRATE&t;0x8B21&t;&t;/* get default bit rate (bps) */
DECL|macro|SIOCSIWRTS
mdefine_line|#define SIOCSIWRTS&t;0x8B22&t;&t;/* set RTS/CTS threshold (bytes) */
DECL|macro|SIOCGIWRTS
mdefine_line|#define SIOCGIWRTS&t;0x8B23&t;&t;/* get RTS/CTS threshold (bytes) */
DECL|macro|SIOCSIWFRAG
mdefine_line|#define SIOCSIWFRAG&t;0x8B24&t;&t;/* set fragmentation thr (bytes) */
DECL|macro|SIOCGIWFRAG
mdefine_line|#define SIOCGIWFRAG&t;0x8B25&t;&t;/* get fragmentation thr (bytes) */
DECL|macro|SIOCSIWTXPOW
mdefine_line|#define SIOCSIWTXPOW&t;0x8B26&t;&t;/* set transmit power (dBm) */
DECL|macro|SIOCGIWTXPOW
mdefine_line|#define SIOCGIWTXPOW&t;0x8B27&t;&t;/* get transmit power (dBm) */
DECL|macro|SIOCSIWRETRY
mdefine_line|#define SIOCSIWRETRY&t;0x8B28&t;&t;/* set retry limits and lifetime */
DECL|macro|SIOCGIWRETRY
mdefine_line|#define SIOCGIWRETRY&t;0x8B29&t;&t;/* get retry limits and lifetime */
multiline_comment|/* Encoding stuff (scrambling, hardware security, WEP...) */
DECL|macro|SIOCSIWENCODE
mdefine_line|#define SIOCSIWENCODE&t;0x8B2A&t;&t;/* set encoding token &amp; mode */
DECL|macro|SIOCGIWENCODE
mdefine_line|#define SIOCGIWENCODE&t;0x8B2B&t;&t;/* get encoding token &amp; mode */
multiline_comment|/* Power saving stuff (power management, unicast and multicast) */
DECL|macro|SIOCSIWPOWER
mdefine_line|#define SIOCSIWPOWER&t;0x8B2C&t;&t;/* set Power Management settings */
DECL|macro|SIOCGIWPOWER
mdefine_line|#define SIOCGIWPOWER&t;0x8B2D&t;&t;/* get Power Management settings */
multiline_comment|/* ------------------------- IOCTL STUFF ------------------------- */
multiline_comment|/* The first and the last (range) */
DECL|macro|SIOCIWFIRST
mdefine_line|#define SIOCIWFIRST&t;0x8B00
DECL|macro|SIOCIWLAST
mdefine_line|#define SIOCIWLAST&t;0x8B30
multiline_comment|/* Even : get (world access), odd : set (root access) */
DECL|macro|IW_IS_SET
mdefine_line|#define IW_IS_SET(cmd)&t;(!((cmd) &amp; 0x1))
DECL|macro|IW_IS_GET
mdefine_line|#define IW_IS_GET(cmd)&t;((cmd) &amp; 0x1)
multiline_comment|/* ------------------------- PRIVATE INFO ------------------------- */
multiline_comment|/*&n; * The following is used with SIOCGIWPRIV. It allow a driver to define&n; * the interface (name, type of data) for its private ioctl.&n; * Privates ioctl are SIOCDEVPRIVATE -&gt; SIOCDEVPRIVATE + 0xF&n; */
DECL|macro|IW_PRIV_TYPE_MASK
mdefine_line|#define IW_PRIV_TYPE_MASK&t;0x7000&t;/* Type of arguments */
DECL|macro|IW_PRIV_TYPE_NONE
mdefine_line|#define IW_PRIV_TYPE_NONE&t;0x0000
DECL|macro|IW_PRIV_TYPE_BYTE
mdefine_line|#define IW_PRIV_TYPE_BYTE&t;0x1000&t;/* Char as number */
DECL|macro|IW_PRIV_TYPE_CHAR
mdefine_line|#define IW_PRIV_TYPE_CHAR&t;0x2000&t;/* Char as character */
DECL|macro|IW_PRIV_TYPE_INT
mdefine_line|#define IW_PRIV_TYPE_INT&t;0x4000&t;/* 32 bits int */
DECL|macro|IW_PRIV_TYPE_FLOAT
mdefine_line|#define IW_PRIV_TYPE_FLOAT&t;0x5000
DECL|macro|IW_PRIV_SIZE_FIXED
mdefine_line|#define IW_PRIV_SIZE_FIXED&t;0x0800&t;/* Variable or fixed nuber of args */
DECL|macro|IW_PRIV_SIZE_MASK
mdefine_line|#define IW_PRIV_SIZE_MASK&t;0x07FF&t;/* Max number of those args */
multiline_comment|/*&n; * Note : if the number of args is fixed and the size &lt; 16 octets,&n; * instead of passing a pointer we will put args in the iwreq struct...&n; */
multiline_comment|/* ----------------------- OTHER CONSTANTS ----------------------- */
multiline_comment|/* Maximum frequencies in the range struct */
DECL|macro|IW_MAX_FREQUENCIES
mdefine_line|#define IW_MAX_FREQUENCIES&t;16
multiline_comment|/* Note : if you have something like 80 frequencies,&n; * don&squot;t increase this constant and don&squot;t fill the frequency list.&n; * The user will be able to set by channel anyway... */
multiline_comment|/* Maximum bit rates in the range struct */
DECL|macro|IW_MAX_BITRATES
mdefine_line|#define IW_MAX_BITRATES&t;&t;8
multiline_comment|/* Maximum tx powers in the range struct */
DECL|macro|IW_MAX_TXPOWER
mdefine_line|#define IW_MAX_TXPOWER&t;&t;8
multiline_comment|/* Maximum of address that you may set with SPY */
DECL|macro|IW_MAX_SPY
mdefine_line|#define IW_MAX_SPY&t;&t;8
multiline_comment|/* Maximum of address that you may get in the&n;   list of access points in range */
DECL|macro|IW_MAX_AP
mdefine_line|#define IW_MAX_AP&t;&t;8
multiline_comment|/* Maximum size of the ESSID and NICKN strings */
DECL|macro|IW_ESSID_MAX_SIZE
mdefine_line|#define IW_ESSID_MAX_SIZE&t;32
multiline_comment|/* Modes of operation */
DECL|macro|IW_MODE_AUTO
mdefine_line|#define IW_MODE_AUTO&t;0&t;/* Let the driver decides */
DECL|macro|IW_MODE_ADHOC
mdefine_line|#define IW_MODE_ADHOC&t;1&t;/* Single cell network */
DECL|macro|IW_MODE_INFRA
mdefine_line|#define IW_MODE_INFRA&t;2&t;/* Multi cell network, roaming, ... */
DECL|macro|IW_MODE_MASTER
mdefine_line|#define IW_MODE_MASTER&t;3&t;/* Synchronisation master or Access Point */
DECL|macro|IW_MODE_REPEAT
mdefine_line|#define IW_MODE_REPEAT&t;4&t;/* Wireless Repeater (forwarder) */
DECL|macro|IW_MODE_SECOND
mdefine_line|#define IW_MODE_SECOND&t;5&t;/* Secondary master/repeater (backup) */
multiline_comment|/* Maximum number of size of encoding token available&n; * they are listed in the range structure */
DECL|macro|IW_MAX_ENCODING_SIZES
mdefine_line|#define IW_MAX_ENCODING_SIZES&t;8
multiline_comment|/* Maximum size of the encoding token in bytes */
DECL|macro|IW_ENCODING_TOKEN_MAX
mdefine_line|#define IW_ENCODING_TOKEN_MAX&t;32&t;/* 256 bits (for now) */
multiline_comment|/* Flags for encoding (along with the token) */
DECL|macro|IW_ENCODE_INDEX
mdefine_line|#define IW_ENCODE_INDEX&t;&t;0x00FF&t;/* Token index (if needed) */
DECL|macro|IW_ENCODE_FLAGS
mdefine_line|#define IW_ENCODE_FLAGS&t;&t;0xFF00&t;/* Flags defined below */
DECL|macro|IW_ENCODE_MODE
mdefine_line|#define IW_ENCODE_MODE&t;&t;0xF000&t;/* Modes defined below */
DECL|macro|IW_ENCODE_DISABLED
mdefine_line|#define IW_ENCODE_DISABLED&t;0x8000&t;/* Encoding disabled */
DECL|macro|IW_ENCODE_ENABLED
mdefine_line|#define IW_ENCODE_ENABLED&t;0x0000&t;/* Encoding enabled */
DECL|macro|IW_ENCODE_RESTRICTED
mdefine_line|#define IW_ENCODE_RESTRICTED&t;0x4000&t;/* Refuse non-encoded packets */
DECL|macro|IW_ENCODE_OPEN
mdefine_line|#define IW_ENCODE_OPEN&t;&t;0x2000&t;/* Accept non-encoded packets */
DECL|macro|IW_ENCODE_NOKEY
mdefine_line|#define IW_ENCODE_NOKEY         0x0800  /* Key is write only, so not present */
multiline_comment|/* Power management flags available (along with the value, if any) */
DECL|macro|IW_POWER_ON
mdefine_line|#define IW_POWER_ON&t;&t;0x0000&t;/* No details... */
DECL|macro|IW_POWER_TYPE
mdefine_line|#define IW_POWER_TYPE&t;&t;0xF000&t;/* Type of parameter */
DECL|macro|IW_POWER_PERIOD
mdefine_line|#define IW_POWER_PERIOD&t;&t;0x1000&t;/* Value is a period/duration of  */
DECL|macro|IW_POWER_TIMEOUT
mdefine_line|#define IW_POWER_TIMEOUT&t;0x2000&t;/* Value is a timeout (to go asleep) */
DECL|macro|IW_POWER_MODE
mdefine_line|#define IW_POWER_MODE&t;&t;0x0F00&t;/* Power Management mode */
DECL|macro|IW_POWER_UNICAST_R
mdefine_line|#define IW_POWER_UNICAST_R&t;0x0100&t;/* Receive only unicast messages */
DECL|macro|IW_POWER_MULTICAST_R
mdefine_line|#define IW_POWER_MULTICAST_R&t;0x0200&t;/* Receive only multicast messages */
DECL|macro|IW_POWER_ALL_R
mdefine_line|#define IW_POWER_ALL_R&t;&t;0x0300&t;/* Receive all messages though PM */
DECL|macro|IW_POWER_FORCE_S
mdefine_line|#define IW_POWER_FORCE_S&t;0x0400&t;/* Force PM procedure for sending unicast */
DECL|macro|IW_POWER_REPEATER
mdefine_line|#define IW_POWER_REPEATER&t;0x0800&t;/* Repeat broadcast messages in PM period */
DECL|macro|IW_POWER_MODIFIER
mdefine_line|#define IW_POWER_MODIFIER&t;0x000F&t;/* Modify a parameter */
DECL|macro|IW_POWER_MIN
mdefine_line|#define IW_POWER_MIN&t;&t;0x0001&t;/* Value is a minimum  */
DECL|macro|IW_POWER_MAX
mdefine_line|#define IW_POWER_MAX&t;&t;0x0002&t;/* Value is a maximum */
DECL|macro|IW_POWER_RELATIVE
mdefine_line|#define IW_POWER_RELATIVE&t;0x0004&t;/* Value is not in seconds/ms/us */
multiline_comment|/* Transmit Power flags available */
DECL|macro|IW_TXPOW_DBM
mdefine_line|#define IW_TXPOW_DBM&t;&t;0x0000&t;/* Value is in dBm */
DECL|macro|IW_TXPOW_MWATT
mdefine_line|#define IW_TXPOW_MWATT&t;&t;0x0001&t;/* Value is in mW */
multiline_comment|/* Retry limits and lifetime flags available */
DECL|macro|IW_RETRY_ON
mdefine_line|#define IW_RETRY_ON&t;&t;0x0000&t;/* No details... */
DECL|macro|IW_RETRY_TYPE
mdefine_line|#define IW_RETRY_TYPE&t;&t;0xF000&t;/* Type of parameter */
DECL|macro|IW_RETRY_LIMIT
mdefine_line|#define IW_RETRY_LIMIT&t;&t;0x1000&t;/* Maximum number of retries*/
DECL|macro|IW_RETRY_LIFETIME
mdefine_line|#define IW_RETRY_LIFETIME&t;0x2000&t;/* Maximum duration of retries in us */
DECL|macro|IW_RETRY_MODIFIER
mdefine_line|#define IW_RETRY_MODIFIER&t;0x000F&t;/* Modify a parameter */
DECL|macro|IW_RETRY_MIN
mdefine_line|#define IW_RETRY_MIN&t;&t;0x0001&t;/* Value is a minimum  */
DECL|macro|IW_RETRY_MAX
mdefine_line|#define IW_RETRY_MAX&t;&t;0x0002&t;/* Value is a maximum */
DECL|macro|IW_RETRY_RELATIVE
mdefine_line|#define IW_RETRY_RELATIVE&t;0x0004&t;/* Value is not in seconds/ms/us */
multiline_comment|/****************************** TYPES ******************************/
multiline_comment|/* --------------------------- SUBTYPES --------------------------- */
multiline_comment|/*&n; *&t;Generic format for most parameters that fit in an int&n; */
DECL|struct|iw_param
r_struct
id|iw_param
(brace
DECL|member|value
id|__s32
id|value
suffix:semicolon
multiline_comment|/* The value of the parameter itself */
DECL|member|fixed
id|__u8
id|fixed
suffix:semicolon
multiline_comment|/* Hardware should not use auto select */
DECL|member|disabled
id|__u8
id|disabled
suffix:semicolon
multiline_comment|/* Disable the feature */
DECL|member|flags
id|__u16
id|flags
suffix:semicolon
multiline_comment|/* Various specifc flags (if any) */
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;For all data larger than 16 octets, we need to use a&n; *&t;pointer to memory allocated in user space.&n; */
DECL|struct|iw_point
r_struct
id|iw_point
(brace
DECL|member|pointer
id|caddr_t
id|pointer
suffix:semicolon
multiline_comment|/* Pointer to the data  (in user space) */
DECL|member|length
id|__u16
id|length
suffix:semicolon
multiline_comment|/* number of fields or size in bytes */
DECL|member|flags
id|__u16
id|flags
suffix:semicolon
multiline_comment|/* Optional params */
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;A frequency&n; *&t;For numbers lower than 10^9, we encode the number in &squot;m&squot; and&n; *&t;set &squot;e&squot; to 0&n; *&t;For number greater than 10^9, we divide it by the lowest power&n; *&t;of 10 to get &squot;m&squot; lower than 10^9, with &squot;m&squot;= f / (10^&squot;e&squot;)...&n; *&t;The power of 10 is in &squot;e&squot;, the result of the division is in &squot;m&squot;.&n; */
DECL|struct|iw_freq
r_struct
id|iw_freq
(brace
DECL|member|m
id|__u32
id|m
suffix:semicolon
multiline_comment|/* Mantissa */
DECL|member|e
id|__u16
id|e
suffix:semicolon
multiline_comment|/* Exponent */
DECL|member|i
id|__u8
id|i
suffix:semicolon
multiline_comment|/* List index (when in range struct) */
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;Quality of the link&n; */
DECL|struct|iw_quality
r_struct
id|iw_quality
(brace
DECL|member|qual
id|__u8
id|qual
suffix:semicolon
multiline_comment|/* link quality (%retries, SNR or better...) */
DECL|member|level
id|__u8
id|level
suffix:semicolon
multiline_comment|/* signal level */
DECL|member|noise
id|__u8
id|noise
suffix:semicolon
multiline_comment|/* noise level */
DECL|member|updated
id|__u8
id|updated
suffix:semicolon
multiline_comment|/* Flags to know if updated */
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;Packet discarded in the wireless adapter due to&n; *&t;&quot;wireless&quot; specific problems...&n; */
DECL|struct|iw_discarded
r_struct
id|iw_discarded
(brace
DECL|member|nwid
id|__u32
id|nwid
suffix:semicolon
multiline_comment|/* Wrong nwid */
DECL|member|code
id|__u32
id|code
suffix:semicolon
multiline_comment|/* Unable to code/decode */
DECL|member|misc
id|__u32
id|misc
suffix:semicolon
multiline_comment|/* Others cases */
)brace
suffix:semicolon
multiline_comment|/* ------------------------ WIRELESS STATS ------------------------ */
multiline_comment|/*&n; * Wireless statistics (used for /proc/net/wireless)&n; */
DECL|struct|iw_statistics
r_struct
id|iw_statistics
(brace
DECL|member|status
id|__u16
id|status
suffix:semicolon
multiline_comment|/* Status&n;&t;&t;&t;&t;&t; * - device dependent for now */
DECL|member|qual
r_struct
id|iw_quality
id|qual
suffix:semicolon
multiline_comment|/* Quality of the link&n;&t;&t;&t;&t;&t;&t; * (instant/mean/max) */
DECL|member|discard
r_struct
id|iw_discarded
id|discard
suffix:semicolon
multiline_comment|/* Packet discarded counts */
)brace
suffix:semicolon
multiline_comment|/* ------------------------ IOCTL REQUEST ------------------------ */
multiline_comment|/*&n; * The structure to exchange data for ioctl.&n; * This structure is the same as &squot;struct ifreq&squot;, but (re)defined for&n; * convenience...&n; *&n; * Note that it should fit on the same memory footprint !&n; * You should check this when increasing the above structures (16 octets)&n; * 16 octets = 128 bits. Warning, pointers might be 64 bits wide...&n; */
DECL|struct|iwreq
r_struct
id|iwreq
(brace
r_union
(brace
DECL|member|ifrn_name
r_char
id|ifrn_name
(braket
id|IFNAMSIZ
)braket
suffix:semicolon
multiline_comment|/* if name, e.g. &quot;eth0&quot; */
DECL|member|ifr_ifrn
)brace
id|ifr_ifrn
suffix:semicolon
multiline_comment|/* Data part */
r_union
(brace
multiline_comment|/* Config - generic */
DECL|member|name
r_char
id|name
(braket
id|IFNAMSIZ
)braket
suffix:semicolon
multiline_comment|/* Name : used to verify the presence of  wireless extensions.&n;&t;&t; * Name of the protocol/provider... */
DECL|member|essid
r_struct
id|iw_point
id|essid
suffix:semicolon
multiline_comment|/* Extended network name */
DECL|member|nwid
r_struct
id|iw_param
id|nwid
suffix:semicolon
multiline_comment|/* network id (or domain - the cell) */
DECL|member|freq
r_struct
id|iw_freq
id|freq
suffix:semicolon
multiline_comment|/* frequency or channel :&n;&t;&t;&t;&t;&t; * 0-1000 = channel&n;&t;&t;&t;&t;&t; * &gt; 1000 = frequency in Hz */
DECL|member|sens
r_struct
id|iw_param
id|sens
suffix:semicolon
multiline_comment|/* signal level threshold */
DECL|member|bitrate
r_struct
id|iw_param
id|bitrate
suffix:semicolon
multiline_comment|/* default bit rate */
DECL|member|txpower
r_struct
id|iw_param
id|txpower
suffix:semicolon
multiline_comment|/* default transmit power */
DECL|member|rts
r_struct
id|iw_param
id|rts
suffix:semicolon
multiline_comment|/* RTS threshold threshold */
DECL|member|frag
r_struct
id|iw_param
id|frag
suffix:semicolon
multiline_comment|/* Fragmentation threshold */
DECL|member|mode
id|__u32
id|mode
suffix:semicolon
multiline_comment|/* Operation mode */
DECL|member|retry
r_struct
id|iw_param
id|retry
suffix:semicolon
multiline_comment|/* Retry limits &amp; lifetime */
DECL|member|encoding
r_struct
id|iw_point
id|encoding
suffix:semicolon
multiline_comment|/* Encoding stuff : tokens */
DECL|member|power
r_struct
id|iw_param
id|power
suffix:semicolon
multiline_comment|/* PM duration/timeout */
DECL|member|ap_addr
r_struct
id|sockaddr
id|ap_addr
suffix:semicolon
multiline_comment|/* Access point address */
DECL|member|data
r_struct
id|iw_point
id|data
suffix:semicolon
multiline_comment|/* Other large parameters */
DECL|member|u
)brace
id|u
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* -------------------------- IOCTL DATA -------------------------- */
multiline_comment|/*&n; *&t;For those ioctl which want to exchange mode data that what could&n; *&t;fit in the above structure...&n; */
multiline_comment|/*&n; *&t;Range of parameters&n; */
DECL|struct|iw_range
r_struct
id|iw_range
(brace
multiline_comment|/* Informative stuff (to choose between different interface) */
DECL|member|throughput
id|__u32
id|throughput
suffix:semicolon
multiline_comment|/* To give an idea... */
multiline_comment|/* In theory this value should be the maximum benchmarked&n;&t; * TCP/IP throughput, because with most of these devices the&n;&t; * bit rate is meaningless (overhead an co) to estimate how&n;&t; * fast the connection will go and pick the fastest one.&n;&t; * I suggest people to play with Netperf or any benchmark...&n;&t; */
multiline_comment|/* NWID (or domain id) */
DECL|member|min_nwid
id|__u32
id|min_nwid
suffix:semicolon
multiline_comment|/* Minimal NWID we are able to set */
DECL|member|max_nwid
id|__u32
id|max_nwid
suffix:semicolon
multiline_comment|/* Maximal NWID we are able to set */
multiline_comment|/* Frequency */
DECL|member|num_channels
id|__u16
id|num_channels
suffix:semicolon
multiline_comment|/* Number of channels [0; num - 1] */
DECL|member|num_frequency
id|__u8
id|num_frequency
suffix:semicolon
multiline_comment|/* Number of entry in the list */
DECL|member|freq
r_struct
id|iw_freq
id|freq
(braket
id|IW_MAX_FREQUENCIES
)braket
suffix:semicolon
multiline_comment|/* list */
multiline_comment|/* Note : this frequency list doesn&squot;t need to fit channel numbers */
multiline_comment|/* signal level threshold range */
DECL|member|sensitivity
id|__s32
id|sensitivity
suffix:semicolon
multiline_comment|/* Quality of link &amp; SNR stuff */
DECL|member|max_qual
r_struct
id|iw_quality
id|max_qual
suffix:semicolon
multiline_comment|/* Quality of the link */
multiline_comment|/* Rates */
DECL|member|num_bitrates
id|__u8
id|num_bitrates
suffix:semicolon
multiline_comment|/* Number of entries in the list */
DECL|member|bitrate
id|__s32
id|bitrate
(braket
id|IW_MAX_BITRATES
)braket
suffix:semicolon
multiline_comment|/* list, in bps */
multiline_comment|/* RTS threshold */
DECL|member|min_rts
id|__s32
id|min_rts
suffix:semicolon
multiline_comment|/* Minimal RTS threshold */
DECL|member|max_rts
id|__s32
id|max_rts
suffix:semicolon
multiline_comment|/* Maximal RTS threshold */
multiline_comment|/* Frag threshold */
DECL|member|min_frag
id|__s32
id|min_frag
suffix:semicolon
multiline_comment|/* Minimal frag threshold */
DECL|member|max_frag
id|__s32
id|max_frag
suffix:semicolon
multiline_comment|/* Maximal frag threshold */
multiline_comment|/* Power Management duration &amp; timeout */
DECL|member|min_pmp
id|__s32
id|min_pmp
suffix:semicolon
multiline_comment|/* Minimal PM period */
DECL|member|max_pmp
id|__s32
id|max_pmp
suffix:semicolon
multiline_comment|/* Maximal PM period */
DECL|member|min_pmt
id|__s32
id|min_pmt
suffix:semicolon
multiline_comment|/* Minimal PM timeout */
DECL|member|max_pmt
id|__s32
id|max_pmt
suffix:semicolon
multiline_comment|/* Maximal PM timeout */
DECL|member|pmp_flags
id|__u16
id|pmp_flags
suffix:semicolon
multiline_comment|/* How to decode max/min PM period */
DECL|member|pmt_flags
id|__u16
id|pmt_flags
suffix:semicolon
multiline_comment|/* How to decode max/min PM timeout */
DECL|member|pm_capa
id|__u16
id|pm_capa
suffix:semicolon
multiline_comment|/* What PM options are supported */
multiline_comment|/* Encoder stuff */
DECL|member|encoding_size
id|__u16
id|encoding_size
(braket
id|IW_MAX_ENCODING_SIZES
)braket
suffix:semicolon
multiline_comment|/* Different token sizes */
DECL|member|num_encoding_sizes
id|__u8
id|num_encoding_sizes
suffix:semicolon
multiline_comment|/* Number of entry in the list */
DECL|member|max_encoding_tokens
id|__u8
id|max_encoding_tokens
suffix:semicolon
multiline_comment|/* Max number of tokens */
multiline_comment|/* Transmit power */
DECL|member|txpower_capa
id|__u16
id|txpower_capa
suffix:semicolon
multiline_comment|/* What options are supported */
DECL|member|num_txpower
id|__u8
id|num_txpower
suffix:semicolon
multiline_comment|/* Number of entries in the list */
DECL|member|txpower
id|__s32
id|txpower
(braket
id|IW_MAX_TXPOWER
)braket
suffix:semicolon
multiline_comment|/* list, in bps */
multiline_comment|/* Wireless Extension version info */
DECL|member|we_version_compiled
id|__u8
id|we_version_compiled
suffix:semicolon
multiline_comment|/* Must be WIRELESS_EXT */
DECL|member|we_version_source
id|__u8
id|we_version_source
suffix:semicolon
multiline_comment|/* Last update of source */
multiline_comment|/* Retry limits and lifetime */
DECL|member|retry_capa
id|__u16
id|retry_capa
suffix:semicolon
multiline_comment|/* What retry options are supported */
DECL|member|retry_flags
id|__u16
id|retry_flags
suffix:semicolon
multiline_comment|/* How to decode max/min retry limit */
DECL|member|r_time_flags
id|__u16
id|r_time_flags
suffix:semicolon
multiline_comment|/* How to decode max/min retry life */
DECL|member|min_retry
id|__s32
id|min_retry
suffix:semicolon
multiline_comment|/* Minimal number of retries */
DECL|member|max_retry
id|__s32
id|max_retry
suffix:semicolon
multiline_comment|/* Maximal number of retries */
DECL|member|min_r_time
id|__s32
id|min_r_time
suffix:semicolon
multiline_comment|/* Minimal retry lifetime */
DECL|member|max_r_time
id|__s32
id|max_r_time
suffix:semicolon
multiline_comment|/* Maximal retry lifetime */
)brace
suffix:semicolon
multiline_comment|/*&n; * Private ioctl interface information&n; */
DECL|struct|iw_priv_args
r_struct
id|iw_priv_args
(brace
DECL|member|cmd
id|__u32
id|cmd
suffix:semicolon
multiline_comment|/* Number of the ioctl to issue */
DECL|member|set_args
id|__u16
id|set_args
suffix:semicolon
multiline_comment|/* Type and number of args */
DECL|member|get_args
id|__u16
id|get_args
suffix:semicolon
multiline_comment|/* Type and number of args */
DECL|member|name
r_char
id|name
(braket
id|IFNAMSIZ
)braket
suffix:semicolon
multiline_comment|/* Name of the extension */
)brace
suffix:semicolon
macro_line|#endif&t;/* _LINUX_WIRELESS_H */
eof
