multiline_comment|/*&n;  nubus.h: various definitions and prototypes for NuBus drivers to use.&n;&n;  Originally written by Alan Cox.&n;&n;  Hacked to death by C. Scott Ananian and David Huggins-Daines.&n;  &n;  Some of the constants in here are from the corresponding&n;  NetBSD/OpenBSD header file, by Allen Briggs.  We figured out the&n;  rest of them on our own. */
macro_line|#ifndef LINUX_NUBUS_H
DECL|macro|LINUX_NUBUS_H
mdefine_line|#define LINUX_NUBUS_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;asm/nubus.h&gt;
macro_line|#endif
DECL|enum|nubus_category
r_enum
id|nubus_category
(brace
DECL|enumerator|NUBUS_CAT_BOARD
id|NUBUS_CAT_BOARD
op_assign
l_int|0x0001
comma
DECL|enumerator|NUBUS_CAT_DISPLAY
id|NUBUS_CAT_DISPLAY
op_assign
l_int|0x0003
comma
DECL|enumerator|NUBUS_CAT_NETWORK
id|NUBUS_CAT_NETWORK
op_assign
l_int|0x0004
comma
DECL|enumerator|NUBUS_CAT_COMMUNICATIONS
id|NUBUS_CAT_COMMUNICATIONS
op_assign
l_int|0x0006
comma
DECL|enumerator|NUBUS_CAT_FONT
id|NUBUS_CAT_FONT
op_assign
l_int|0x0009
comma
DECL|enumerator|NUBUS_CAT_CPU
id|NUBUS_CAT_CPU
op_assign
l_int|0x000A
comma
multiline_comment|/* For lack of a better name */
DECL|enumerator|NUBUS_CAT_DUODOCK
id|NUBUS_CAT_DUODOCK
op_assign
l_int|0x0020
)brace
suffix:semicolon
DECL|enum|nubus_type_network
r_enum
id|nubus_type_network
(brace
DECL|enumerator|NUBUS_TYPE_ETHERNET
id|NUBUS_TYPE_ETHERNET
op_assign
l_int|0x0001
comma
DECL|enumerator|NUBUS_TYPE_RS232
id|NUBUS_TYPE_RS232
op_assign
l_int|0x0002
)brace
suffix:semicolon
DECL|enum|nubus_type_display
r_enum
id|nubus_type_display
(brace
DECL|enumerator|NUBUS_TYPE_VIDEO
id|NUBUS_TYPE_VIDEO
op_assign
l_int|0x0001
)brace
suffix:semicolon
DECL|enum|nubus_type_cpu
r_enum
id|nubus_type_cpu
(brace
DECL|enumerator|NUBUS_TYPE_68020
id|NUBUS_TYPE_68020
op_assign
l_int|0x0003
comma
DECL|enumerator|NUBUS_TYPE_68030
id|NUBUS_TYPE_68030
op_assign
l_int|0x0004
comma
DECL|enumerator|NUBUS_TYPE_68040
id|NUBUS_TYPE_68040
op_assign
l_int|0x0005
)brace
suffix:semicolon
multiline_comment|/* Known &lt;Cat,Type,SW,HW&gt; tuples: (according to TattleTech and Slots)&n; *  68030 motherboards: &lt;10,4,0,24&gt;&n; *  68040 motherboards: &lt;10,5,0,24&gt;&n; *  DuoDock Plus: &lt;32,1,1,2&gt;&n; *&n; *  Toby Frame Buffer card: &lt;3,1,1,1&gt;&n; *  RBV built-in video (IIci): &lt;3,1,1,24&gt;&n; *  Valkyrie built-in video (Q630): &lt;3,1,1,46&gt;&n; *  Macintosh Display Card: &lt;3,1,1,25&gt;&n; *  Sonora built-in video (P460): &lt;3,1,1,34&gt;&n; *  Jet framebuffer (DuoDock Plus): &lt;3,1,1,41&gt;&n; *&n; *  SONIC comm-slot/on-board and DuoDock Ethernet: &lt;4,1,1,272&gt;&n; *  SONIC LC-PDS Ethernet (Dayna, but like Apple 16-bit, sort of): &lt;4,1,1,271&gt;&n; *  Sonic Systems Ethernet A-Series Card: &lt;4,1,268,256&gt;&n; *  Asante MacCon NuBus-A: &lt;4,1,260,256&gt; (alpha-1.0,1.1 revision)&n; *   ROM on the above card: &lt;2,1,0,0&gt;&n; *  Cabletron ethernet card: &lt;4,1,1,265&gt;&n; *  Farallon ethernet card: &lt;4,1,268,256&gt; (identical to Sonic Systems card)&n; *  Kinetics EtherPort IIN: &lt;4,1,259,262&gt;&n; *  API Engineering EtherRun_LCa PDS enet card: &lt;4,1,282,256&gt;&n; *&n; *  Add your devices to the list!  You can obtain the &quot;Slots&quot; utility&n; *  from Apple&squot;s FTP site at:&n; *  ftp://dev.apple.com/devworld/Tool_Chest/Devices_-_Hardware/NuBus_Slot_Manager/&n; *&n; *  Alternately, TattleTech can be found at any Info-Mac mirror site.  &n; *  or from its distribution site: ftp://ftp.decismkr.com/dms&n; */
multiline_comment|/* DrSW: Uniquely identifies the software interface to a board.  This&n;   is usually the one you want to look at when writing a driver.  It&squot;s&n;   not as useful as you think, though, because as we should know by&n;   now (duh), &quot;Apple Compatible&quot; can mean a lot of things... */
multiline_comment|/* Add known DrSW values here */
DECL|enum|nubus_drsw
r_enum
id|nubus_drsw
(brace
multiline_comment|/* NUBUS_CAT_DISPLAY */
DECL|enumerator|NUBUS_DRSW_APPLE
id|NUBUS_DRSW_APPLE
op_assign
l_int|0x0001
comma
DECL|enumerator|NUBUS_DRSW_APPLE_HIRES
id|NUBUS_DRSW_APPLE_HIRES
op_assign
l_int|0x0013
comma
multiline_comment|/* MacII HiRes card driver */
multiline_comment|/* NUBUS_CAT_NETWORK */
DECL|enumerator|NUBUS_DRSW_CABLETRON
id|NUBUS_DRSW_CABLETRON
op_assign
l_int|0x0001
comma
DECL|enumerator|NUBUS_DRSW_SONIC_LC
id|NUBUS_DRSW_SONIC_LC
op_assign
l_int|0x0001
comma
DECL|enumerator|NUBUS_DRSW_KINETICS
id|NUBUS_DRSW_KINETICS
op_assign
l_int|0x0103
comma
DECL|enumerator|NUBUS_DRSW_ASANTE
id|NUBUS_DRSW_ASANTE
op_assign
l_int|0x0104
comma
DECL|enumerator|NUBUS_DRSW_DAYNA
id|NUBUS_DRSW_DAYNA
op_assign
l_int|0x010b
comma
DECL|enumerator|NUBUS_DRSW_FARALLON
id|NUBUS_DRSW_FARALLON
op_assign
l_int|0x010c
comma
DECL|enumerator|NUBUS_DRSW_APPLE_SN
id|NUBUS_DRSW_APPLE_SN
op_assign
l_int|0x010f
comma
DECL|enumerator|NUBUS_DRSW_FOCUS
id|NUBUS_DRSW_FOCUS
op_assign
l_int|0x011a
comma
DECL|enumerator|NUBUS_DRSW_ASANTE_CS
id|NUBUS_DRSW_ASANTE_CS
op_assign
l_int|0x011d
comma
multiline_comment|/* use asante SMC9194 driver */
multiline_comment|/* NUBUS_CAT_CPU */
DECL|enumerator|NUBUS_DRSW_NONE
id|NUBUS_DRSW_NONE
op_assign
l_int|0x0000
comma
)brace
suffix:semicolon
multiline_comment|/* DrHW: Uniquely identifies the hardware interface to a board (or at&n;   least, it should...  some video cards are known to incorrectly&n;   identify themselves as Toby cards) */
multiline_comment|/* Add known DrHW values here */
DECL|enum|nubus_drhw
r_enum
id|nubus_drhw
(brace
multiline_comment|/* NUBUS_CAT_DISPLAY */
DECL|enumerator|NUBUS_DRHW_APPLE_TFB
id|NUBUS_DRHW_APPLE_TFB
op_assign
l_int|0x0001
comma
multiline_comment|/* Toby frame buffer card */
DECL|enumerator|NUBUS_DRHW_APPLE_RBV1
id|NUBUS_DRHW_APPLE_RBV1
op_assign
l_int|0x0018
comma
multiline_comment|/* IIci RBV video */
DECL|enumerator|NUBUS_DRHW_APPLE_MDC
id|NUBUS_DRHW_APPLE_MDC
op_assign
l_int|0x0019
comma
multiline_comment|/* Macintosh Display Card */
DECL|enumerator|NUBUS_DRHW_APPLE_SONORA
id|NUBUS_DRHW_APPLE_SONORA
op_assign
l_int|0x0022
comma
multiline_comment|/* Sonora built-in video */
DECL|enumerator|NUBUS_DRHW_APPLE_VALKYRIE
id|NUBUS_DRHW_APPLE_VALKYRIE
op_assign
l_int|0x002e
comma
DECL|enumerator|NUBUS_DRHW_APPLE_JET
id|NUBUS_DRHW_APPLE_JET
op_assign
l_int|0x0029
comma
multiline_comment|/* Jet framebuffer (DuoDock) */
multiline_comment|/* NUBUS_CAT_NETWORK */
DECL|enumerator|NUBUS_DRHW_INTERLAN
id|NUBUS_DRHW_INTERLAN
op_assign
l_int|0x0100
comma
DECL|enumerator|NUBUS_DRHW_SMC9194
id|NUBUS_DRHW_SMC9194
op_assign
l_int|0x0101
comma
DECL|enumerator|NUBUS_DRHW_KINETICS
id|NUBUS_DRHW_KINETICS
op_assign
l_int|0x0106
comma
DECL|enumerator|NUBUS_DRHW_CABLETRON
id|NUBUS_DRHW_CABLETRON
op_assign
l_int|0x0109
comma
DECL|enumerator|NUBUS_DRHW_ASANTE_LC
id|NUBUS_DRHW_ASANTE_LC
op_assign
l_int|0x010f
comma
DECL|enumerator|NUBUS_DRHW_SONIC
id|NUBUS_DRHW_SONIC
op_assign
l_int|0x0110
comma
)brace
suffix:semicolon
multiline_comment|/* Resource IDs: These are the identifiers for the various weird and&n;   wonderful tidbits of information that may or may not reside in the&n;   NuBus ROM directory. */
DECL|enum|nubus_res_id
r_enum
id|nubus_res_id
(brace
DECL|enumerator|NUBUS_RESID_TYPE
id|NUBUS_RESID_TYPE
op_assign
l_int|0x0001
comma
DECL|enumerator|NUBUS_RESID_NAME
id|NUBUS_RESID_NAME
op_assign
l_int|0x0002
comma
DECL|enumerator|NUBUS_RESID_ICON
id|NUBUS_RESID_ICON
op_assign
l_int|0x0003
comma
DECL|enumerator|NUBUS_RESID_DRVRDIR
id|NUBUS_RESID_DRVRDIR
op_assign
l_int|0x0004
comma
DECL|enumerator|NUBUS_RESID_LOADREC
id|NUBUS_RESID_LOADREC
op_assign
l_int|0x0005
comma
DECL|enumerator|NUBUS_RESID_BOOTREC
id|NUBUS_RESID_BOOTREC
op_assign
l_int|0x0006
comma
DECL|enumerator|NUBUS_RESID_FLAGS
id|NUBUS_RESID_FLAGS
op_assign
l_int|0x0007
comma
DECL|enumerator|NUBUS_RESID_HWDEVID
id|NUBUS_RESID_HWDEVID
op_assign
l_int|0x0008
comma
DECL|enumerator|NUBUS_RESID_MINOR_BASEOS
id|NUBUS_RESID_MINOR_BASEOS
op_assign
l_int|0x000a
comma
DECL|enumerator|NUBUS_RESID_MINOR_LENGTH
id|NUBUS_RESID_MINOR_LENGTH
op_assign
l_int|0x000b
comma
DECL|enumerator|NUBUS_RESID_MAJOR_BASEOS
id|NUBUS_RESID_MAJOR_BASEOS
op_assign
l_int|0x000c
comma
DECL|enumerator|NUBUS_RESID_MAJOR_LENGTH
id|NUBUS_RESID_MAJOR_LENGTH
op_assign
l_int|0x000d
comma
DECL|enumerator|NUBUS_RESID_CICN
id|NUBUS_RESID_CICN
op_assign
l_int|0x000f
comma
DECL|enumerator|NUBUS_RESID_ICL8
id|NUBUS_RESID_ICL8
op_assign
l_int|0x0010
comma
DECL|enumerator|NUBUS_RESID_ICL4
id|NUBUS_RESID_ICL4
op_assign
l_int|0x0011
comma
)brace
suffix:semicolon
multiline_comment|/* Category-specific resources. */
DECL|enum|nubus_board_res_id
r_enum
id|nubus_board_res_id
(brace
DECL|enumerator|NUBUS_RESID_BOARDID
id|NUBUS_RESID_BOARDID
op_assign
l_int|0x0020
comma
DECL|enumerator|NUBUS_RESID_PRAMINITDATA
id|NUBUS_RESID_PRAMINITDATA
op_assign
l_int|0x0021
comma
DECL|enumerator|NUBUS_RESID_PRIMARYINIT
id|NUBUS_RESID_PRIMARYINIT
op_assign
l_int|0x0022
comma
DECL|enumerator|NUBUS_RESID_TIMEOUTCONST
id|NUBUS_RESID_TIMEOUTCONST
op_assign
l_int|0x0023
comma
DECL|enumerator|NUBUS_RESID_VENDORINFO
id|NUBUS_RESID_VENDORINFO
op_assign
l_int|0x0024
comma
DECL|enumerator|NUBUS_RESID_BOARDFLAGS
id|NUBUS_RESID_BOARDFLAGS
op_assign
l_int|0x0025
comma
DECL|enumerator|NUBUS_RESID_SECONDINIT
id|NUBUS_RESID_SECONDINIT
op_assign
l_int|0x0026
comma
multiline_comment|/* Not sure why Apple put these next two in here */
DECL|enumerator|NUBUS_RESID_VIDNAMES
id|NUBUS_RESID_VIDNAMES
op_assign
l_int|0x0041
comma
DECL|enumerator|NUBUS_RESID_VIDMODES
id|NUBUS_RESID_VIDMODES
op_assign
l_int|0x007e
)brace
suffix:semicolon
multiline_comment|/* Fields within the vendor info directory */
DECL|enum|nubus_vendor_res_id
r_enum
id|nubus_vendor_res_id
(brace
DECL|enumerator|NUBUS_RESID_VEND_ID
id|NUBUS_RESID_VEND_ID
op_assign
l_int|0x0001
comma
DECL|enumerator|NUBUS_RESID_VEND_SERIAL
id|NUBUS_RESID_VEND_SERIAL
op_assign
l_int|0x0002
comma
DECL|enumerator|NUBUS_RESID_VEND_REV
id|NUBUS_RESID_VEND_REV
op_assign
l_int|0x0003
comma
DECL|enumerator|NUBUS_RESID_VEND_PART
id|NUBUS_RESID_VEND_PART
op_assign
l_int|0x0004
comma
DECL|enumerator|NUBUS_RESID_VEND_DATE
id|NUBUS_RESID_VEND_DATE
op_assign
l_int|0x0005
)brace
suffix:semicolon
DECL|enum|nubus_net_res_id
r_enum
id|nubus_net_res_id
(brace
DECL|enumerator|NUBUS_RESID_MAC_ADDRESS
id|NUBUS_RESID_MAC_ADDRESS
op_assign
l_int|0x0080
)brace
suffix:semicolon
DECL|enum|nubus_cpu_res_id
r_enum
id|nubus_cpu_res_id
(brace
DECL|enumerator|NUBUS_RESID_MEMINFO
id|NUBUS_RESID_MEMINFO
op_assign
l_int|0x0081
comma
DECL|enumerator|NUBUS_RESID_ROMINFO
id|NUBUS_RESID_ROMINFO
op_assign
l_int|0x0082
)brace
suffix:semicolon
DECL|enum|nubus_display_res_id
r_enum
id|nubus_display_res_id
(brace
DECL|enumerator|NUBUS_RESID_GAMMADIR
id|NUBUS_RESID_GAMMADIR
op_assign
l_int|0x0040
comma
DECL|enumerator|NUBUS_RESID_FIRSTMODE
id|NUBUS_RESID_FIRSTMODE
op_assign
l_int|0x0080
comma
DECL|enumerator|NUBUS_RESID_SECONDMODE
id|NUBUS_RESID_SECONDMODE
op_assign
l_int|0x0081
comma
DECL|enumerator|NUBUS_RESID_THIRDMODE
id|NUBUS_RESID_THIRDMODE
op_assign
l_int|0x0082
comma
DECL|enumerator|NUBUS_RESID_FOURTHMODE
id|NUBUS_RESID_FOURTHMODE
op_assign
l_int|0x0083
comma
DECL|enumerator|NUBUS_RESID_FIFTHMODE
id|NUBUS_RESID_FIFTHMODE
op_assign
l_int|0x0084
comma
DECL|enumerator|NUBUS_RESID_SIXTHMODE
id|NUBUS_RESID_SIXTHMODE
op_assign
l_int|0x0085
)brace
suffix:semicolon
DECL|struct|nubus_dir
r_struct
id|nubus_dir
(brace
DECL|member|base
r_int
r_char
op_star
id|base
suffix:semicolon
DECL|member|ptr
r_int
r_char
op_star
id|ptr
suffix:semicolon
DECL|member|done
r_int
id|done
suffix:semicolon
DECL|member|mask
r_int
id|mask
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nubus_dirent
r_struct
id|nubus_dirent
(brace
DECL|member|base
r_int
r_char
op_star
id|base
suffix:semicolon
DECL|member|type
r_int
r_char
id|type
suffix:semicolon
DECL|member|data
id|__u32
id|data
suffix:semicolon
multiline_comment|/* Actually 24bits used */
DECL|member|mask
r_int
id|mask
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nubus_board
r_struct
id|nubus_board
(brace
DECL|member|next
r_struct
id|nubus_board
op_star
id|next
suffix:semicolon
DECL|member|first_dev
r_struct
id|nubus_dev
op_star
id|first_dev
suffix:semicolon
multiline_comment|/* Only 9-E actually exist, though 0-8 are also theoretically&n;&t;   possible, and 0 is a special case which represents the&n;&t;   motherboard and onboard peripherals (Ethernet, video) */
DECL|member|slot
r_int
id|slot
suffix:semicolon
multiline_comment|/* For slot 0, this is bogus. */
DECL|member|name
r_char
id|name
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* Format block */
DECL|member|fblock
r_int
r_char
op_star
id|fblock
suffix:semicolon
multiline_comment|/* Root directory (does *not* always equal fblock + doffset!) */
DECL|member|directory
r_int
r_char
op_star
id|directory
suffix:semicolon
DECL|member|slot_addr
r_int
r_int
id|slot_addr
suffix:semicolon
multiline_comment|/* Offset to root directory (sometimes) */
DECL|member|doffset
r_int
r_int
id|doffset
suffix:semicolon
multiline_comment|/* Length over which to compute the crc */
DECL|member|rom_length
r_int
r_int
id|rom_length
suffix:semicolon
multiline_comment|/* Completely useless most of the time */
DECL|member|crc
r_int
r_int
id|crc
suffix:semicolon
DECL|member|rev
r_int
r_char
id|rev
suffix:semicolon
DECL|member|format
r_int
r_char
id|format
suffix:semicolon
DECL|member|lanes
r_int
r_char
id|lanes
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nubus_dev
r_struct
id|nubus_dev
(brace
multiline_comment|/* Next link in device list */
DECL|member|next
r_struct
id|nubus_dev
op_star
id|next
suffix:semicolon
multiline_comment|/* Directory entry in /proc/bus/nubus */
DECL|member|procdir
r_struct
id|proc_dir_entry
op_star
id|procdir
suffix:semicolon
multiline_comment|/* The functional resource ID of this device */
DECL|member|resid
r_int
r_char
id|resid
suffix:semicolon
multiline_comment|/* These are mostly here for convenience; we could always read&n;&t;   them from the ROMs if we wanted to */
DECL|member|category
r_int
r_int
id|category
suffix:semicolon
DECL|member|type
r_int
r_int
id|type
suffix:semicolon
DECL|member|dr_sw
r_int
r_int
id|dr_sw
suffix:semicolon
DECL|member|dr_hw
r_int
r_int
id|dr_hw
suffix:semicolon
multiline_comment|/* This is the device&squot;s name rather than the board&squot;s.&n;&t;   Sometimes they are different.  Usually the board name is&n;&t;   more correct. */
DECL|member|name
r_char
id|name
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* MacOS driver (I kid you not) */
DECL|member|driver
r_int
r_char
op_star
id|driver
suffix:semicolon
multiline_comment|/* Actually this is an offset */
DECL|member|iobase
r_int
r_int
id|iobase
suffix:semicolon
DECL|member|iosize
r_int
r_int
id|iosize
suffix:semicolon
DECL|member|flags
DECL|member|hwdevid
r_int
r_char
id|flags
comma
id|hwdevid
suffix:semicolon
multiline_comment|/* Functional directory */
DECL|member|directory
r_int
r_char
op_star
id|directory
suffix:semicolon
multiline_comment|/* Much of our info comes from here */
DECL|member|board
r_struct
id|nubus_board
op_star
id|board
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* This is all NuBus devices (used to find devices later on) */
r_extern
r_struct
id|nubus_dev
op_star
id|nubus_devices
suffix:semicolon
multiline_comment|/* This is all NuBus cards */
r_extern
r_struct
id|nubus_board
op_star
id|nubus_boards
suffix:semicolon
multiline_comment|/* Generic NuBus interface functions, modelled after the PCI interface */
r_void
id|nubus_scan_bus
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|nubus_proc_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|get_nubus_list
c_func
(paren
r_char
op_star
id|buf
)paren
suffix:semicolon
r_int
id|nubus_proc_attach_device
c_func
(paren
r_struct
id|nubus_dev
op_star
id|dev
)paren
suffix:semicolon
r_int
id|nubus_proc_detach_device
c_func
(paren
r_struct
id|nubus_dev
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/* If we need more precision we can add some more of these */
r_struct
id|nubus_dev
op_star
id|nubus_find_device
c_func
(paren
r_int
r_int
id|category
comma
r_int
r_int
id|type
comma
r_int
r_int
id|dr_hw
comma
r_int
r_int
id|dr_sw
comma
r_const
r_struct
id|nubus_dev
op_star
id|from
)paren
suffix:semicolon
r_struct
id|nubus_dev
op_star
id|nubus_find_type
c_func
(paren
r_int
r_int
id|category
comma
r_int
r_int
id|type
comma
r_const
r_struct
id|nubus_dev
op_star
id|from
)paren
suffix:semicolon
multiline_comment|/* Might have more than one device in a slot, you know... */
r_struct
id|nubus_dev
op_star
id|nubus_find_slot
c_func
(paren
r_int
r_int
id|slot
comma
r_const
r_struct
id|nubus_dev
op_star
id|from
)paren
suffix:semicolon
multiline_comment|/* These are somewhat more NuBus-specific.  They all return 0 for&n;   success and -1 for failure, as you&squot;d expect. */
multiline_comment|/* The root directory which contains the board and functional&n;   directories */
r_int
id|nubus_get_root_dir
c_func
(paren
r_const
r_struct
id|nubus_board
op_star
id|board
comma
r_struct
id|nubus_dir
op_star
id|dir
)paren
suffix:semicolon
multiline_comment|/* The board directory */
r_int
id|nubus_get_board_dir
c_func
(paren
r_const
r_struct
id|nubus_board
op_star
id|board
comma
r_struct
id|nubus_dir
op_star
id|dir
)paren
suffix:semicolon
multiline_comment|/* The functional directory */
r_int
id|nubus_get_func_dir
c_func
(paren
r_const
r_struct
id|nubus_dev
op_star
id|dev
comma
r_struct
id|nubus_dir
op_star
id|dir
)paren
suffix:semicolon
multiline_comment|/* These work on any directory gotten via the above */
r_int
id|nubus_readdir
c_func
(paren
r_struct
id|nubus_dir
op_star
id|dir
comma
r_struct
id|nubus_dirent
op_star
id|ent
)paren
suffix:semicolon
r_int
id|nubus_find_rsrc
c_func
(paren
r_struct
id|nubus_dir
op_star
id|dir
comma
r_int
r_char
id|rsrc_type
comma
r_struct
id|nubus_dirent
op_star
id|ent
)paren
suffix:semicolon
r_int
id|nubus_rewinddir
c_func
(paren
r_struct
id|nubus_dir
op_star
id|dir
)paren
suffix:semicolon
multiline_comment|/* Things to do with directory entries */
r_int
id|nubus_get_subdir
c_func
(paren
r_const
r_struct
id|nubus_dirent
op_star
id|ent
comma
r_struct
id|nubus_dir
op_star
id|dir
)paren
suffix:semicolon
r_void
id|nubus_get_rsrc_mem
c_func
(paren
r_void
op_star
id|dest
comma
r_const
r_struct
id|nubus_dirent
op_star
id|dirent
comma
r_int
id|len
)paren
suffix:semicolon
r_void
id|nubus_get_rsrc_str
c_func
(paren
r_void
op_star
id|dest
comma
r_const
r_struct
id|nubus_dirent
op_star
id|dirent
comma
r_int
id|maxlen
)paren
suffix:semicolon
multiline_comment|/* We&squot;d like to get rid of this eventually.  Only daynaport.c uses it now. */
DECL|function|nubus_slot_addr
r_static
r_inline
r_void
op_star
id|nubus_slot_addr
c_func
(paren
r_int
id|slot
)paren
(brace
r_return
(paren
r_void
op_star
)paren
(paren
l_int|0xF0000000
op_or
(paren
id|slot
op_lshift
l_int|24
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif /* LINUX_NUBUS_H */
eof
