multiline_comment|/* $Id: oplib.h,v 1.13 2000/05/09 17:40:15 davem Exp $&n; * oplib.h:  Describes the interface and available routines in the&n; *           Linux Prom library.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; * Copyright (C) 1996 Jakub Jelinek (jj@sunsite.mff.cuni.cz)&n; */
macro_line|#ifndef __SPARC64_OPLIB_H
DECL|macro|__SPARC64_OPLIB_H
mdefine_line|#define __SPARC64_OPLIB_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/openprom.h&gt;
multiline_comment|/* Enumeration to describe the prom major version we have detected. */
DECL|enum|prom_major_version
r_enum
id|prom_major_version
(brace
DECL|enumerator|PROM_V0
id|PROM_V0
comma
multiline_comment|/* Original sun4c V0 prom */
DECL|enumerator|PROM_V2
id|PROM_V2
comma
multiline_comment|/* sun4c and early sun4m V2 prom */
DECL|enumerator|PROM_V3
id|PROM_V3
comma
multiline_comment|/* sun4m and later, up to sun4d/sun4e machines V3 */
DECL|enumerator|PROM_P1275
id|PROM_P1275
comma
multiline_comment|/* IEEE compliant ISA based Sun PROM, only sun4u */
DECL|enumerator|PROM_AP1000
id|PROM_AP1000
comma
multiline_comment|/* actually no prom at all */
)brace
suffix:semicolon
r_extern
r_enum
id|prom_major_version
id|prom_vers
suffix:semicolon
multiline_comment|/* Revision, and firmware revision. */
r_extern
r_int
r_int
id|prom_rev
comma
id|prom_prev
suffix:semicolon
multiline_comment|/* Root node of the prom device tree, this stays constant after&n; * initialization is complete.&n; */
r_extern
r_int
id|prom_root_node
suffix:semicolon
multiline_comment|/* PROM stdin and stdout */
r_extern
r_int
id|prom_stdin
comma
id|prom_stdout
suffix:semicolon
multiline_comment|/* /chosen node of the prom device tree, this stays constant after&n; * initialization is complete.&n; */
r_extern
r_int
id|prom_chosen_node
suffix:semicolon
DECL|struct|linux_mlist_p1275
r_struct
id|linux_mlist_p1275
(brace
DECL|member|theres_more
r_struct
id|linux_mlist_p1275
op_star
id|theres_more
suffix:semicolon
DECL|member|start_adr
r_int
r_int
id|start_adr
suffix:semicolon
DECL|member|num_bytes
r_int
r_int
id|num_bytes
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|linux_mem_p1275
r_struct
id|linux_mem_p1275
(brace
DECL|member|p1275_totphys
r_struct
id|linux_mlist_p1275
op_star
op_star
id|p1275_totphys
suffix:semicolon
DECL|member|p1275_prommap
r_struct
id|linux_mlist_p1275
op_star
op_star
id|p1275_prommap
suffix:semicolon
DECL|member|p1275_available
r_struct
id|linux_mlist_p1275
op_star
op_star
id|p1275_available
suffix:semicolon
multiline_comment|/* What we can use */
)brace
suffix:semicolon
multiline_comment|/* The functions... */
multiline_comment|/* You must call prom_init() before using any of the library services,&n; * preferably as early as possible.  Pass it the romvec pointer.&n; */
r_extern
r_void
id|prom_init
c_func
(paren
r_void
op_star
id|cif_handler
comma
r_void
op_star
id|cif_stack
)paren
suffix:semicolon
multiline_comment|/* Boot argument acquisition, returns the boot command line string. */
r_extern
r_char
op_star
id|prom_getbootargs
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Device utilities. */
multiline_comment|/* Device operations. */
multiline_comment|/* Open the device described by the passed string.  Note, that the format&n; * of the string is different on V0 vs. V2-&gt;higher proms.  The caller must&n; * know what he/she is doing!  Returns the device descriptor, an int.&n; */
r_extern
r_int
id|prom_devopen
c_func
(paren
r_char
op_star
id|device_string
)paren
suffix:semicolon
multiline_comment|/* Close a previously opened device described by the passed integer&n; * descriptor.&n; */
r_extern
r_int
id|prom_devclose
c_func
(paren
r_int
id|device_handle
)paren
suffix:semicolon
multiline_comment|/* Do a seek operation on the device described by the passed integer&n; * descriptor.&n; */
r_extern
r_void
id|prom_seek
c_func
(paren
r_int
id|device_handle
comma
r_int
r_int
id|seek_hival
comma
r_int
r_int
id|seek_lowval
)paren
suffix:semicolon
multiline_comment|/* Machine memory configuration routine. */
multiline_comment|/* This function returns a V0 format memory descriptor table, it has three&n; * entries.  One for the total amount of physical ram on the machine, one&n; * for the amount of physical ram available, and one describing the virtual&n; * areas which are allocated by the prom.  So, in a sense the physical&n; * available is a calculation of the total physical minus the physical mapped&n; * by the prom with virtual mappings.&n; *&n; * These lists are returned pre-sorted, this should make your life easier&n; * since the prom itself is way too lazy to do such nice things.&n; */
r_extern
r_struct
id|linux_mem_p1275
op_star
id|prom_meminfo
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Miscellaneous routines, don&squot;t really fit in any category per se. */
multiline_comment|/* Reboot the machine with the command line passed. */
r_extern
r_void
id|prom_reboot
c_func
(paren
r_char
op_star
id|boot_command
)paren
suffix:semicolon
multiline_comment|/* Evaluate the forth string passed. */
r_extern
r_void
id|prom_feval
c_func
(paren
r_char
op_star
id|forth_string
)paren
suffix:semicolon
multiline_comment|/* Enter the prom, with possibility of continuation with the &squot;go&squot;&n; * command in newer proms.&n; */
r_extern
r_void
id|prom_cmdline
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Enter the prom, with no chance of continuation for the stand-alone&n; * which calls this.&n; */
r_extern
r_void
id|prom_halt
c_func
(paren
r_void
)paren
id|__attribute__
(paren
(paren
id|noreturn
)paren
)paren
suffix:semicolon
multiline_comment|/* Set the PROM &squot;sync&squot; callback function to the passed function pointer.&n; * When the user gives the &squot;sync&squot; command at the prom prompt while the&n; * kernel is still active, the prom will call this routine.&n; *&n; */
DECL|typedef|callback_func_t
r_typedef
r_int
(paren
op_star
id|callback_func_t
)paren
(paren
r_int
op_star
id|cmd
)paren
suffix:semicolon
r_extern
r_void
id|prom_setcallback
c_func
(paren
id|callback_func_t
id|func_ptr
)paren
suffix:semicolon
multiline_comment|/* Acquire the IDPROM of the root node in the prom device tree.  This&n; * gets passed a buffer where you would like it stuffed.  The return value&n; * is the format type of this idprom or 0xff on error.&n; */
r_extern
r_int
r_char
id|prom_get_idprom
c_func
(paren
r_char
op_star
id|idp_buffer
comma
r_int
id|idpbuf_size
)paren
suffix:semicolon
multiline_comment|/* Get the prom major version. */
r_extern
r_int
id|prom_version
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Get the prom plugin revision. */
r_extern
r_int
id|prom_getrev
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Get the prom firmware revision. */
r_extern
r_int
id|prom_getprev
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Character operations to/from the console.... */
multiline_comment|/* Non-blocking get character from console. */
r_extern
r_int
id|prom_nbgetchar
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Non-blocking put character to console. */
r_extern
r_int
id|prom_nbputchar
c_func
(paren
r_char
id|character
)paren
suffix:semicolon
multiline_comment|/* Blocking get character from console. */
r_extern
r_char
id|prom_getchar
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Blocking put character to console. */
r_extern
r_void
id|prom_putchar
c_func
(paren
r_char
id|character
)paren
suffix:semicolon
multiline_comment|/* Prom&squot;s internal printf routine, don&squot;t use in kernel/boot code. */
r_void
id|prom_printf
c_func
(paren
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
suffix:semicolon
multiline_comment|/* Query for input device type */
DECL|enum|prom_input_device
r_enum
id|prom_input_device
(brace
DECL|enumerator|PROMDEV_IKBD
id|PROMDEV_IKBD
comma
multiline_comment|/* input from keyboard */
DECL|enumerator|PROMDEV_ITTYA
id|PROMDEV_ITTYA
comma
multiline_comment|/* input from ttya */
DECL|enumerator|PROMDEV_ITTYB
id|PROMDEV_ITTYB
comma
multiline_comment|/* input from ttyb */
DECL|enumerator|PROMDEV_I_UNK
id|PROMDEV_I_UNK
comma
)brace
suffix:semicolon
r_extern
r_enum
id|prom_input_device
id|prom_query_input_device
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Query for output device type */
DECL|enum|prom_output_device
r_enum
id|prom_output_device
(brace
DECL|enumerator|PROMDEV_OSCREEN
id|PROMDEV_OSCREEN
comma
multiline_comment|/* to screen */
DECL|enumerator|PROMDEV_OTTYA
id|PROMDEV_OTTYA
comma
multiline_comment|/* to ttya */
DECL|enumerator|PROMDEV_OTTYB
id|PROMDEV_OTTYB
comma
multiline_comment|/* to ttyb */
DECL|enumerator|PROMDEV_O_UNK
id|PROMDEV_O_UNK
comma
)brace
suffix:semicolon
r_extern
r_enum
id|prom_output_device
id|prom_query_output_device
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Multiprocessor operations... */
macro_line|#ifdef CONFIG_SMP
multiline_comment|/* Start the CPU with the given device tree node, context table, and context&n; * at the passed program counter.&n; */
r_extern
r_void
id|prom_startcpu
c_func
(paren
r_int
id|cpunode
comma
r_int
r_int
id|pc
comma
r_int
r_int
id|o0
)paren
suffix:semicolon
multiline_comment|/* Stop the current CPU. */
r_extern
r_void
id|prom_stopself
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Idle the current CPU. */
r_extern
r_void
id|prom_idleself
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Resume the CPU with the passed device tree node. */
r_extern
r_void
id|prom_resumecpu
c_func
(paren
r_int
id|cpunode
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Power management interfaces. */
multiline_comment|/* Put the current CPU to sleep. */
r_extern
r_void
id|prom_sleepself
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Put the entire system to sleep. */
r_extern
r_int
id|prom_sleepsystem
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Initiate a wakeup event. */
r_extern
r_int
id|prom_wakeupsystem
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* MMU and memory related OBP interfaces. */
multiline_comment|/* Get unique string identifying SIMM at given physical address. */
r_extern
r_int
id|prom_getunumber
c_func
(paren
r_int
id|syndrome_code
comma
r_int
r_int
id|phys_addr
comma
r_char
op_star
id|buf
comma
r_int
id|buflen
)paren
suffix:semicolon
multiline_comment|/* Retain physical memory to the caller across soft resets. */
r_extern
r_int
r_int
id|prom_retain
c_func
(paren
r_char
op_star
id|name
comma
r_int
r_int
id|pa_low
comma
r_int
r_int
id|pa_high
comma
r_int
id|size
comma
r_int
id|align
)paren
suffix:semicolon
multiline_comment|/* Load explicit I/D TLB entries into the calling processor. */
r_extern
r_int
id|prom_itlb_load
c_func
(paren
r_int
r_int
id|index
comma
r_int
r_int
id|tte_data
comma
r_int
r_int
id|vaddr
)paren
suffix:semicolon
r_extern
r_int
id|prom_dtlb_load
c_func
(paren
r_int
r_int
id|index
comma
r_int
r_int
id|tte_data
comma
r_int
r_int
id|vaddr
)paren
suffix:semicolon
multiline_comment|/* Map/Unmap client program address ranges.  First the format of&n; * the mapping mode argument.&n; */
DECL|macro|PROM_MAP_WRITE
mdefine_line|#define PROM_MAP_WRITE&t;0x0001 /* Writable */
DECL|macro|PROM_MAP_READ
mdefine_line|#define PROM_MAP_READ&t;0x0002 /* Readable - sw */
DECL|macro|PROM_MAP_EXEC
mdefine_line|#define PROM_MAP_EXEC&t;0x0004 /* Executable - sw */
DECL|macro|PROM_MAP_LOCKED
mdefine_line|#define PROM_MAP_LOCKED&t;0x0010 /* Locked, use i/dtlb load calls for this instead */
DECL|macro|PROM_MAP_CACHED
mdefine_line|#define PROM_MAP_CACHED&t;0x0020 /* Cacheable in both L1 and L2 caches */
DECL|macro|PROM_MAP_SE
mdefine_line|#define PROM_MAP_SE&t;0x0040 /* Side-Effects */
DECL|macro|PROM_MAP_GLOB
mdefine_line|#define PROM_MAP_GLOB&t;0x0080 /* Global */
DECL|macro|PROM_MAP_IE
mdefine_line|#define PROM_MAP_IE&t;0x0100 /* Invert-Endianness */
DECL|macro|PROM_MAP_DEFAULT
mdefine_line|#define PROM_MAP_DEFAULT (PROM_MAP_WRITE | PROM_MAP_READ | PROM_MAP_EXEC | PROM_MAP_CACHED)
r_extern
r_int
id|prom_map
c_func
(paren
r_int
id|mode
comma
r_int
r_int
id|size
comma
r_int
r_int
id|vaddr
comma
r_int
r_int
id|paddr
)paren
suffix:semicolon
r_extern
r_void
id|prom_unmap
c_func
(paren
r_int
r_int
id|size
comma
r_int
r_int
id|vaddr
)paren
suffix:semicolon
multiline_comment|/* PROM device tree traversal functions... */
macro_line|#ifdef PROMLIB_INTERNAL
multiline_comment|/* Internal version of prom_getchild. */
r_extern
r_int
id|__prom_getchild
c_func
(paren
r_int
id|parent_node
)paren
suffix:semicolon
multiline_comment|/* Internal version of prom_getsibling. */
r_extern
r_int
id|__prom_getsibling
c_func
(paren
r_int
id|node
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Get the child node of the given node, or zero if no child exists. */
r_extern
r_int
id|prom_getchild
c_func
(paren
r_int
id|parent_node
)paren
suffix:semicolon
multiline_comment|/* Get the next sibling node of the given node, or zero if no further&n; * siblings exist.&n; */
r_extern
r_int
id|prom_getsibling
c_func
(paren
r_int
id|node
)paren
suffix:semicolon
multiline_comment|/* Get the length, at the passed node, of the given property type.&n; * Returns -1 on error (ie. no such property at this node).&n; */
r_extern
r_int
id|prom_getproplen
c_func
(paren
r_int
id|thisnode
comma
r_char
op_star
id|property
)paren
suffix:semicolon
multiline_comment|/* Fetch the requested property using the given buffer.  Returns&n; * the number of bytes the prom put into your buffer or -1 on error.&n; */
r_extern
r_int
id|prom_getproperty
c_func
(paren
r_int
id|thisnode
comma
r_char
op_star
id|property
comma
r_char
op_star
id|prop_buffer
comma
r_int
id|propbuf_size
)paren
suffix:semicolon
multiline_comment|/* Acquire an integer property. */
r_extern
r_int
id|prom_getint
c_func
(paren
r_int
id|node
comma
r_char
op_star
id|property
)paren
suffix:semicolon
multiline_comment|/* Acquire an integer property, with a default value. */
r_extern
r_int
id|prom_getintdefault
c_func
(paren
r_int
id|node
comma
r_char
op_star
id|property
comma
r_int
id|defval
)paren
suffix:semicolon
multiline_comment|/* Acquire a boolean property, 0=FALSE 1=TRUE. */
r_extern
r_int
id|prom_getbool
c_func
(paren
r_int
id|node
comma
r_char
op_star
id|prop
)paren
suffix:semicolon
multiline_comment|/* Acquire a string property, null string on error. */
r_extern
r_void
id|prom_getstring
c_func
(paren
r_int
id|node
comma
r_char
op_star
id|prop
comma
r_char
op_star
id|buf
comma
r_int
id|bufsize
)paren
suffix:semicolon
multiline_comment|/* Does the passed node have the given &quot;name&quot;? YES=1 NO=0 */
r_extern
r_int
id|prom_nodematch
c_func
(paren
r_int
id|thisnode
comma
r_char
op_star
id|name
)paren
suffix:semicolon
multiline_comment|/* Puts in buffer a prom name in the form name@x,y or name (x for which_io &n; * and y for first regs phys address&n; */
r_extern
r_int
id|prom_getname
c_func
(paren
r_int
id|node
comma
r_char
op_star
id|buf
comma
r_int
id|buflen
)paren
suffix:semicolon
multiline_comment|/* Search all siblings starting at the passed node for &quot;name&quot; matching&n; * the given string.  Returns the node on success, zero on failure.&n; */
r_extern
r_int
id|prom_searchsiblings
c_func
(paren
r_int
id|node_start
comma
r_char
op_star
id|name
)paren
suffix:semicolon
multiline_comment|/* Return the first property type, as a string, for the given node.&n; * Returns a null string on error. Buffer should be at least 32B long.&n; */
r_extern
r_char
op_star
id|prom_firstprop
c_func
(paren
r_int
id|node
comma
r_char
op_star
id|buffer
)paren
suffix:semicolon
multiline_comment|/* Returns the next property after the passed property for the given&n; * node.  Returns null string on failure. Buffer should be at least 32B long.&n; */
r_extern
r_char
op_star
id|prom_nextprop
c_func
(paren
r_int
id|node
comma
r_char
op_star
id|prev_property
comma
r_char
op_star
id|buffer
)paren
suffix:semicolon
multiline_comment|/* Returns 1 if the specified node has given property. */
r_extern
r_int
id|prom_node_has_property
c_func
(paren
r_int
id|node
comma
r_char
op_star
id|property
)paren
suffix:semicolon
multiline_comment|/* Returns phandle of the path specified */
r_extern
r_int
id|prom_finddevice
c_func
(paren
r_char
op_star
id|name
)paren
suffix:semicolon
multiline_comment|/* Set the indicated property at the given node with the passed value.&n; * Returns the number of bytes of your value that the prom took.&n; */
r_extern
r_int
id|prom_setprop
c_func
(paren
r_int
id|node
comma
r_char
op_star
id|prop_name
comma
r_char
op_star
id|prop_value
comma
r_int
id|value_size
)paren
suffix:semicolon
r_extern
r_int
id|prom_pathtoinode
c_func
(paren
r_char
op_star
id|path
)paren
suffix:semicolon
r_extern
r_int
id|prom_inst2pkg
c_func
(paren
r_int
)paren
suffix:semicolon
multiline_comment|/* Client interface level routines. */
r_extern
r_void
id|prom_set_trap_table
c_func
(paren
r_int
r_int
id|tba
)paren
suffix:semicolon
multiline_comment|/* Dorking with Bus ranges... */
multiline_comment|/* Adjust reg values with the passed ranges. */
r_extern
r_void
id|prom_adjust_regs
c_func
(paren
r_struct
id|linux_prom_registers
op_star
id|regp
comma
r_int
id|nregs
comma
r_struct
id|linux_prom_ranges
op_star
id|rangep
comma
r_int
id|nranges
)paren
suffix:semicolon
multiline_comment|/* Adjust child ranges with the passed parent ranges. */
r_extern
r_void
id|prom_adjust_ranges
c_func
(paren
r_struct
id|linux_prom_ranges
op_star
id|cranges
comma
r_int
id|ncranges
comma
r_struct
id|linux_prom_ranges
op_star
id|pranges
comma
r_int
id|npranges
)paren
suffix:semicolon
multiline_comment|/* Apply ranges of any prom node (and optionally parent node as well) to registers. */
r_extern
r_void
id|prom_apply_generic_ranges
c_func
(paren
r_int
id|node
comma
r_int
id|parent
comma
r_struct
id|linux_prom_registers
op_star
id|sbusregs
comma
r_int
id|nregs
)paren
suffix:semicolon
r_extern
r_int
id|p1275_cmd
(paren
r_char
op_star
comma
r_int
comma
dot
dot
dot
)paren
suffix:semicolon
macro_line|#if 0
mdefine_line|#define P1275_SIZE(x) ((((long)((x) / 32)) &lt;&lt; 32) | (x))
macro_line|#else
DECL|macro|P1275_SIZE
mdefine_line|#define P1275_SIZE(x) x
macro_line|#endif
multiline_comment|/* We support at most 16 input and 1 output argument */
DECL|macro|P1275_ARG_NUMBER
mdefine_line|#define P1275_ARG_NUMBER&t;&t;0
DECL|macro|P1275_ARG_IN_STRING
mdefine_line|#define P1275_ARG_IN_STRING&t;&t;1
DECL|macro|P1275_ARG_OUT_BUF
mdefine_line|#define P1275_ARG_OUT_BUF&t;&t;2
DECL|macro|P1275_ARG_OUT_32B
mdefine_line|#define P1275_ARG_OUT_32B&t;&t;3
DECL|macro|P1275_ARG_IN_FUNCTION
mdefine_line|#define P1275_ARG_IN_FUNCTION&t;&t;4
DECL|macro|P1275_ARG_IN_BUF
mdefine_line|#define P1275_ARG_IN_BUF&t;&t;5
DECL|macro|P1275_ARG_IN_64B
mdefine_line|#define P1275_ARG_IN_64B&t;&t;6
DECL|macro|P1275_IN
mdefine_line|#define P1275_IN(x) ((x) &amp; 0xf)
DECL|macro|P1275_OUT
mdefine_line|#define P1275_OUT(x) (((x) &lt;&lt; 4) &amp; 0xf0)
DECL|macro|P1275_INOUT
mdefine_line|#define P1275_INOUT(i,o) (P1275_IN(i)|P1275_OUT(o))
DECL|macro|P1275_ARG
mdefine_line|#define P1275_ARG(n,x) ((x) &lt;&lt; ((n)*3 + 8))
macro_line|#endif /* !(__SPARC64_OPLIB_H) */
eof
