multiline_comment|/*&n; * This file define the new driver API for Wireless Extensions&n; *&n; * Version :&t;2&t;6.12.01&n; *&n; * Authors :&t;Jean Tourrilhes - HPL - &lt;jt@hpl.hp.com&gt;&n; * Copyright (c) 2001 Jean Tourrilhes, All Rights Reserved.&n; */
macro_line|#ifndef _IW_HANDLER_H
DECL|macro|_IW_HANDLER_H
mdefine_line|#define _IW_HANDLER_H
multiline_comment|/************************** DOCUMENTATION **************************/
multiline_comment|/*&n; * Initial driver API (1996 -&gt; onward) :&n; * -----------------------------------&n; * The initial API just sends the IOCTL request received from user space&n; * to the driver (via the driver ioctl handler). The driver has to&n; * handle all the rest...&n; *&n; * The initial API also defines a specific handler in struct net_device&n; * to handle wireless statistics.&n; *&n; * The initial APIs served us well and has proven a reasonably good design.&n; * However, there is a few shortcommings :&n; *&t;o No events, everything is a request to the driver.&n; *&t;o Large ioctl function in driver with gigantic switch statement&n; *&t;  (i.e. spaghetti code).&n; *&t;o Driver has to mess up with copy_to/from_user, and in many cases&n; *&t;  does it unproperly. Common mistakes are :&n; *&t;&t;* buffer overflows (no checks or off by one checks)&n; *&t;&t;* call copy_to/from_user with irq disabled&n; *&t;o The user space interface is tied to ioctl because of the use&n; *&t;  copy_to/from_user.&n; *&n; * New driver API (2001 -&gt; onward) :&n; * -------------------------------&n; * The new driver API is just a bunch of standard functions (handlers),&n; * each handling a specific Wireless Extension. The driver just export&n; * the list of handler it supports, and those will be called apropriately.&n; *&n; * I tried to keep the main advantage of the previous API (simplicity,&n; * efficiency and light weight), and also I provide a good dose of backward&n; * compatibility (most structures are the same, driver can use both API&n; * simultaneously, ...).&n; * Hopefully, I&squot;ve also addressed the shortcomming of the initial API.&n; *&n; * The advantage of the new API are :&n; *&t;o Handling of Extensions in driver broken in small contained functions&n; *&t;o Tighter checks of ioctl before calling the driver&n; *&t;o Flexible commit strategy (at least, the start of it)&n; *&t;o Backward compatibility (can be mixed with old API)&n; *&t;o Driver doesn&squot;t have to worry about memory and user-space issues&n; * The last point is important for the following reasons :&n; *&t;o You are now able to call the new driver API from any API you&n; *&t;&t;want (including from within other parts of the kernel).&n; *&t;o Common mistakes are avoided (buffer overflow, user space copy&n; *&t;&t;with irq disabled and so on).&n; *&n; * The Drawback of the new API are :&n; *&t;o bloat (especially kernel)&n; *&t;o need to migrate existing drivers to new API&n; * My initial testing shows that the new API adds around 3kB to the kernel&n; * and save between 0 and 5kB from a typical driver.&n; * Also, as all structures and data types are unchanged, the migration is&n; * quite straightforward (but tedious).&n; *&n; * ---&n; *&n; * The new driver API is defined below in this file. User space should&n; * not be aware of what&squot;s happening down there...&n; *&n; * A new kernel wrapper is in charge of validating the IOCTLs and calling&n; * the appropriate driver handler. This is implemented in :&n; *&t;# net/core/wireless.c&n; *&n; * The driver export the list of handlers in :&n; *&t;# include/linux/netdevice.h (one place)&n; *&n; * The new driver API is available for WIRELESS_EXT &gt;= 13.&n; * Good luck with migration to the new API ;-)&n; */
multiline_comment|/* ---------------------- THE IMPLEMENTATION ---------------------- */
multiline_comment|/*&n; * Some of the choice I&squot;ve made are pretty controversials. Defining an&n; * API is very much weighting compromises. This goes into some of the&n; * details and the thinking behind the implementation.&n; *&n; * Implementation goals :&n; * --------------------&n; * The implementation goals were as follow :&n; *&t;o Obvious : you should not need a PhD to understand what&squot;s happening,&n; *&t;&t;the benefit is easier maintainance.&n; *&t;o Flexible : it should accomodate a wide variety of driver&n; *&t;&t;implementations and be as flexible as the old API.&n; *&t;o Lean : it should be efficient memory wise to minimise the impact&n; *&t;&t;on kernel footprint.&n; *&t;o Transparent to user space : the large number of user space&n; *&t;&t;applications that use Wireless Extensions should not need&n; *&t;&t;any modifications.&n; *&n; * Array of functions versus Struct of functions&n; * ---------------------------------------------&n; * 1) Having an array of functions allow the kernel code to access the&n; * handler in a single lookup, which is much more efficient (think hash&n; * table here).&n; * 2) The only drawback is that driver writer may put their handler in&n; * the wrong slot. This is trivial to test (I set the frequency, the&n; * bitrate changes). Once the handler is in the proper slot, it will be&n; * there forever, because the array is only extended at the end.&n; * 3) Backward/forward compatibility : adding new handler just require&n; * extending the array, so you can put newer driver in older kernel&n; * without having to patch the kernel code (and vice versa).&n; *&n; * All handler are of the same generic type&n; * ----------------------------------------&n; * That&squot;s a feature !!!&n; * 1) Having a generic handler allow to have generic code, which is more&n; * efficient. If each of the handler was individually typed I would need&n; * to add a big switch in the kernel (== more bloat). This solution is&n; * more scalable, adding new Wireless Extensions doesn&squot;t add new code.&n; * 2) You can use the same handler in different slots of the array. For&n; * hardware, it may be more efficient or logical to handle multiple&n; * Wireless Extensions with a single function, and the API allow you to&n; * do that. (An example would be a single record on the card to control&n; * both bitrate and frequency, the handler would read the old record,&n; * modify it according to info-&gt;cmd and rewrite it).&n; *&n; * Functions prototype uses union iwreq_data&n; * -----------------------------------------&n; * Some would have prefered functions defined this way :&n; *&t;static int mydriver_ioctl_setrate(struct net_device *dev, &n; *&t;&t;&t;&t;&t;  long rate, int auto)&n; * 1) The kernel code doesn&squot;t &quot;validate&quot; the content of iwreq_data, and&n; * can&squot;t do it (different hardware may have different notion of what a&n; * valid frequency is), so we don&squot;t pretend that we do it.&n; * 2) The above form is not extendable. If I want to add a flag (for&n; * example to distinguish setting max rate and basic rate), I would&n; * break the prototype. Using iwreq_data is more flexible.&n; * 3) Also, the above form is not generic (see above).&n; * 4) I don&squot;t expect driver developper using the wrong field of the&n; * union (Doh !), so static typechecking doesn&squot;t add much value.&n; * 5) Lastly, you can skip the union by doing :&n; *&t;static int mydriver_ioctl_setrate(struct net_device *dev,&n; *&t;&t;&t;&t;&t;  struct iw_request_info *info,&n; *&t;&t;&t;&t;&t;  struct iw_param *rrq,&n; *&t;&t;&t;&t;&t;  char *extra)&n; * And then adding the handler in the array like this :&n; *        (iw_handler) mydriver_ioctl_setrate,             // SIOCSIWRATE&n; *&n; * Using functions and not a registry&n; * ----------------------------------&n; * Another implementation option would have been for every instance to&n; * define a registry (a struct containing all the Wireless Extensions)&n; * and only have a function to commit the registry to the hardware.&n; * 1) This approach can be emulated by the current code, but not&n; * vice versa.&n; * 2) Some drivers don&squot;t keep any configuration in the driver, for them&n; * adding such a registry would be a significant bloat.&n; * 3) The code to translate from Wireless Extension to native format is&n; * needed anyway, so it would not reduce significantely the amount of code.&n; * 4) The current approach only selectively translate Wireless Extensions&n; * to native format and only selectively set, whereas the registry approach&n; * would require to translate all WE and set all parameters for any single&n; * change.&n; * 5) For many Wireless Extensions, the GET operation return the current&n; * dynamic value, not the value that was set.&n; *&n; * This header is &lt;net/iw_handler.h&gt;&n; * ---------------------------------&n; * 1) This header is kernel space only and should not be exported to&n; * user space. Headers in &quot;include/linux/&quot; are exported, headers in&n; * &quot;include/net/&quot; are not.&n; *&n; * Mixed 32/64 bit issues&n; * ----------------------&n; * The Wireless Extensions are designed to be 64 bit clean, by using only&n; * datatypes with explicit storage size.&n; * There are some issues related to kernel and user space using different&n; * memory model, and in particular 64bit kernel with 32bit user space.&n; * The problem is related to struct iw_point, that contains a pointer&n; * that *may* need to be translated.&n; * This is quite messy. The new API doesn&squot;t solve this problem (it can&squot;t),&n; * but is a step in the right direction :&n; * 1) Meta data about each ioctl is easily available, so we know what type&n; * of translation is needed.&n; * 2) The move of data between kernel and user space is only done in a single&n; * place in the kernel, so adding specific hooks in there is possible.&n; * 3) In the long term, it allows to move away from using ioctl as the&n; * user space API.&n; *&n; * So many comments and so few code&n; * --------------------------------&n; * That&squot;s a feature. Comments won&squot;t bloat the resulting kernel binary.&n; */
multiline_comment|/***************************** INCLUDES *****************************/
macro_line|#include &lt;linux/wireless.h&gt;&t;&t;/* IOCTL user space API */
multiline_comment|/***************************** VERSION *****************************/
multiline_comment|/*&n; * This constant is used to know which version of the driver API is&n; * available. Hopefully, this will be pretty stable and no changes&n; * will be needed...&n; * I just plan to increment with each new version.&n; */
DECL|macro|IW_HANDLER_VERSION
mdefine_line|#define IW_HANDLER_VERSION&t;2
multiline_comment|/**************************** CONSTANTS ****************************/
multiline_comment|/* Special error message for the driver to indicate that we&n; * should do a commit after return from the iw_handler */
DECL|macro|EIWCOMMIT
mdefine_line|#define EIWCOMMIT&t;EINPROGRESS
multiline_comment|/* Flags available in struct iw_request_info */
DECL|macro|IW_REQUEST_FLAG_NONE
mdefine_line|#define IW_REQUEST_FLAG_NONE&t;0x0000&t;/* No flag so far */
multiline_comment|/* Type of headers we know about (basically union iwreq_data) */
DECL|macro|IW_HEADER_TYPE_NULL
mdefine_line|#define IW_HEADER_TYPE_NULL&t;0&t;/* Not available */
DECL|macro|IW_HEADER_TYPE_CHAR
mdefine_line|#define IW_HEADER_TYPE_CHAR&t;2&t;/* char [IFNAMSIZ] */
DECL|macro|IW_HEADER_TYPE_UINT
mdefine_line|#define IW_HEADER_TYPE_UINT&t;4&t;/* __u32 */
DECL|macro|IW_HEADER_TYPE_FREQ
mdefine_line|#define IW_HEADER_TYPE_FREQ&t;5&t;/* struct iw_freq */
DECL|macro|IW_HEADER_TYPE_POINT
mdefine_line|#define IW_HEADER_TYPE_POINT&t;6&t;/* struct iw_point */
DECL|macro|IW_HEADER_TYPE_PARAM
mdefine_line|#define IW_HEADER_TYPE_PARAM&t;7&t;/* struct iw_param */
DECL|macro|IW_HEADER_TYPE_ADDR
mdefine_line|#define IW_HEADER_TYPE_ADDR&t;8&t;/* struct sockaddr */
multiline_comment|/* Handling flags */
multiline_comment|/* Most are not implemented. I just use them as a reminder of some&n; * cool features we might need one day ;-) */
DECL|macro|IW_DESCR_FLAG_NONE
mdefine_line|#define IW_DESCR_FLAG_NONE&t;0x0000&t;/* Obvious */
multiline_comment|/* Wrapper level flags */
DECL|macro|IW_DESCR_FLAG_DUMP
mdefine_line|#define IW_DESCR_FLAG_DUMP&t;0x0001&t;/* Not part of the dump command */
DECL|macro|IW_DESCR_FLAG_EVENT
mdefine_line|#define IW_DESCR_FLAG_EVENT&t;0x0002&t;/* Generate an event on SET */
DECL|macro|IW_DESCR_FLAG_RESTRICT
mdefine_line|#define IW_DESCR_FLAG_RESTRICT&t;0x0004&t;/* GET request is ROOT only */
multiline_comment|/* Driver level flags */
DECL|macro|IW_DESCR_FLAG_WAIT
mdefine_line|#define IW_DESCR_FLAG_WAIT&t;0x0100&t;/* Wait for driver event */
multiline_comment|/****************************** TYPES ******************************/
multiline_comment|/* ----------------------- WIRELESS HANDLER ----------------------- */
multiline_comment|/*&n; * A wireless handler is just a standard function, that looks like the&n; * ioctl handler.&n; * We also define there how a handler list look like... As the Wireless&n; * Extension space is quite dense, we use a simple array, which is faster&n; * (that&squot;s the perfect hash table ;-).&n; */
multiline_comment|/*&n; * Meta data about the request passed to the iw_handler.&n; * Most handlers can safely ignore what&squot;s in there.&n; * The &squot;cmd&squot; field might come handy if you want to use the same handler&n; * for multiple command...&n; * This struct is also my long term insurance. I can add new fields here&n; * without breaking the prototype of iw_handler...&n; */
DECL|struct|iw_request_info
r_struct
id|iw_request_info
(brace
DECL|member|cmd
id|__u16
id|cmd
suffix:semicolon
multiline_comment|/* Wireless Extension command */
DECL|member|flags
id|__u16
id|flags
suffix:semicolon
multiline_comment|/* More to come ;-) */
)brace
suffix:semicolon
multiline_comment|/*&n; * This is how a function handling a Wireless Extension should look&n; * like (both get and set, standard and private).&n; */
DECL|typedef|iw_handler
r_typedef
r_int
(paren
op_star
id|iw_handler
)paren
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|iw_request_info
op_star
id|info
comma
r_union
id|iwreq_data
op_star
id|wrqu
comma
r_char
op_star
id|extra
)paren
suffix:semicolon
multiline_comment|/*&n; * This define all the handler that the driver export.&n; * As you need only one per driver type, please use a static const&n; * shared by all driver instances... Same for the members...&n; * This will be linked from net_device in &lt;linux/netdevice.h&gt;&n; */
DECL|struct|iw_handler_def
r_struct
id|iw_handler_def
(brace
multiline_comment|/* Number of handlers defined (more precisely, index of the&n;&t; * last defined handler + 1) */
DECL|member|num_standard
id|__u16
id|num_standard
suffix:semicolon
DECL|member|num_private
id|__u16
id|num_private
suffix:semicolon
multiline_comment|/* Number of private arg description */
DECL|member|num_private_args
id|__u16
id|num_private_args
suffix:semicolon
multiline_comment|/* Array of handlers for standard ioctls&n;&t; * We will call dev-&gt;wireless_handlers-&gt;standard[ioctl - SIOCSIWNAME]&n;&t; */
DECL|member|standard
id|iw_handler
op_star
id|standard
suffix:semicolon
multiline_comment|/* Array of handlers for private ioctls&n;&t; * Will call dev-&gt;wireless_handlers-&gt;private[ioctl - SIOCIWFIRSTPRIV]&n;&t; */
DECL|member|private
id|iw_handler
op_star
r_private
suffix:semicolon
multiline_comment|/* Arguments of private handler. This one is just a list, so you&n;&t; * can put it in any order you want and should not leave holes...&n;&t; * We will automatically export that to user space... */
DECL|member|private_args
r_struct
id|iw_priv_args
op_star
id|private_args
suffix:semicolon
multiline_comment|/* In the long term, get_wireless_stats will move from&n;&t; * &squot;struct net_device&squot; to here, to minimise bloat. */
)brace
suffix:semicolon
multiline_comment|/* ----------------------- WIRELESS EVENTS ----------------------- */
multiline_comment|/*&n; * Currently we don&squot;t support events, so let&squot;s just plan for the&n; * future...&n; */
multiline_comment|/*&n; * A Wireless Event.&n; */
singleline_comment|// How do we define short header ? We don&squot;t want a flag on length.
singleline_comment|// Probably a flag on event ? Highest bit to zero...
DECL|struct|iw_event
r_struct
id|iw_event
(brace
DECL|member|length
id|__u16
id|length
suffix:semicolon
multiline_comment|/* Lenght of this stuff */
DECL|member|event
id|__u16
id|event
suffix:semicolon
multiline_comment|/* Wireless IOCTL */
DECL|member|header
r_union
id|iwreq_data
id|header
suffix:semicolon
multiline_comment|/* IOCTL fixed payload */
DECL|member|extra
r_char
id|extra
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* Optional IOCTL data */
)brace
suffix:semicolon
multiline_comment|/* ---------------------- IOCTL DESCRIPTION ---------------------- */
multiline_comment|/*&n; * One of the main goal of the new interface is to deal entirely with&n; * user space/kernel space memory move.&n; * For that, we need to know :&n; *&t;o if iwreq is a pointer or contain the full data&n; *&t;o what is the size of the data to copy&n; *&n; * For private IOCTLs, we use the same rules as used by iwpriv and&n; * defined in struct iw_priv_args.&n; *&n; * For standard IOCTLs, things are quite different and we need to&n; * use the stuctures below. Actually, this struct is also more&n; * efficient, but that&squot;s another story...&n; */
multiline_comment|/*&n; * Describe how a standard IOCTL looks like.&n; */
DECL|struct|iw_ioctl_description
r_struct
id|iw_ioctl_description
(brace
DECL|member|header_type
id|__u8
id|header_type
suffix:semicolon
multiline_comment|/* NULL, iw_point or other */
DECL|member|token_type
id|__u8
id|token_type
suffix:semicolon
multiline_comment|/* Future */
DECL|member|token_size
id|__u16
id|token_size
suffix:semicolon
multiline_comment|/* Granularity of payload */
DECL|member|min_tokens
id|__u16
id|min_tokens
suffix:semicolon
multiline_comment|/* Min acceptable token number */
DECL|member|max_tokens
id|__u16
id|max_tokens
suffix:semicolon
multiline_comment|/* Max acceptable token number */
DECL|member|flags
id|__u32
id|flags
suffix:semicolon
multiline_comment|/* Special handling of the request */
)brace
suffix:semicolon
multiline_comment|/* Need to think of short header translation table. Later. */
multiline_comment|/**************************** PROTOTYPES ****************************/
multiline_comment|/*&n; * Functions part of the Wireless Extensions (defined in net/core/wireless.c).&n; * Those may be called only within the kernel.&n; */
multiline_comment|/* First : function strictly used inside the kernel */
multiline_comment|/* Handle /proc/net/wireless, called in net/code/dev.c */
r_extern
r_int
id|dev_get_wireless_info
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
suffix:semicolon
multiline_comment|/* Handle IOCTLs, called in net/code/dev.c */
r_extern
r_int
id|wireless_process_ioctl
c_func
(paren
r_struct
id|ifreq
op_star
id|ifr
comma
r_int
r_int
id|cmd
)paren
suffix:semicolon
multiline_comment|/* Second : functions that may be called by driver modules */
multiline_comment|/* None yet */
macro_line|#endif&t;/* _LINUX_WIRELESS_H */
eof
