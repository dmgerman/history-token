multiline_comment|/* $Id: oplib.h,v 1.23 2001/12/21 00:54:31 davem Exp $&n; * oplib.h:  Describes the interface and available routines in the&n; *           Linux Prom library.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef __SPARC_OPLIB_H
DECL|macro|__SPARC_OPLIB_H
mdefine_line|#define __SPARC_OPLIB_H
macro_line|#include &lt;asm/openprom.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
multiline_comment|/* The master romvec pointer... */
r_extern
r_struct
id|linux_romvec
op_star
id|romvec
suffix:semicolon
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
DECL|enumerator|PROM_SUN4
id|PROM_SUN4
comma
multiline_comment|/* Old sun4 proms are totally different, but we&squot;ll shoehorn it to make it fit */
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
multiline_comment|/* Pointer to prom structure containing the device tree traversal&n; * and usage utility functions.  Only prom-lib should use these,&n; * users use the interface defined by the library only!&n; */
r_extern
r_struct
id|linux_nodeops
op_star
id|prom_nodeops
suffix:semicolon
multiline_comment|/* The functions... */
multiline_comment|/* You must call prom_init() before using any of the library services,&n; * preferably as early as possible.  Pass it the romvec pointer.&n; */
r_extern
r_void
id|prom_init
c_func
(paren
r_struct
id|linux_romvec
op_star
id|rom_ptr
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
multiline_comment|/* Map and unmap devices in IO space at virtual addresses. Note that the&n; * virtual address you pass is a request and the prom may put your mappings&n; * somewhere else, so check your return value as that is where your new&n; * mappings really are!&n; *&n; * Another note, these are only available on V2 or higher proms!&n; */
r_extern
r_char
op_star
id|prom_mapio
c_func
(paren
r_char
op_star
id|virt_hint
comma
r_int
id|io_space
comma
r_int
r_int
id|phys_addr
comma
r_int
r_int
id|num_bytes
)paren
suffix:semicolon
r_extern
r_void
id|prom_unmapio
c_func
(paren
r_char
op_star
id|virt_addr
comma
r_int
r_int
id|num_bytes
)paren
suffix:semicolon
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
id|linux_mem_v0
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
multiline_comment|/* Set the PROM &squot;sync&squot; callback function to the passed function pointer.&n; * When the user gives the &squot;sync&squot; command at the prom prompt while the&n; * kernel is still active, the prom will call this routine.&n; *&n; * XXX The arguments are different on V0 vs. V2-&gt;higher proms, grrr! XXX&n; */
DECL|typedef|sync_func_t
r_typedef
r_void
(paren
op_star
id|sync_func_t
)paren
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|prom_setsync
c_func
(paren
id|sync_func_t
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
multiline_comment|/* Start the CPU with the given device tree node, context table, and context&n; * at the passed program counter.&n; */
r_extern
r_int
id|prom_startcpu
c_func
(paren
r_int
id|cpunode
comma
r_struct
id|linux_prom_registers
op_star
id|context_table
comma
r_int
id|context
comma
r_char
op_star
id|program_counter
)paren
suffix:semicolon
multiline_comment|/* Stop the CPU with the passed device tree node. */
r_extern
r_int
id|prom_stopcpu
c_func
(paren
r_int
id|cpunode
)paren
suffix:semicolon
multiline_comment|/* Idle the CPU with the passed device tree node. */
r_extern
r_int
id|prom_idlecpu
c_func
(paren
r_int
id|cpunode
)paren
suffix:semicolon
multiline_comment|/* Re-Start the CPU with the passed device tree node. */
r_extern
r_int
id|prom_restartcpu
c_func
(paren
r_int
id|cpunode
)paren
suffix:semicolon
multiline_comment|/* PROM memory allocation facilities... */
multiline_comment|/* Allocated at possibly the given virtual address a chunk of the&n; * indicated size.&n; */
r_extern
r_char
op_star
id|prom_alloc
c_func
(paren
r_char
op_star
id|virt_hint
comma
r_int
r_int
id|size
)paren
suffix:semicolon
multiline_comment|/* Free a previously allocated chunk. */
r_extern
r_void
id|prom_free
c_func
(paren
r_char
op_star
id|virt_addr
comma
r_int
r_int
id|size
)paren
suffix:semicolon
multiline_comment|/* Sun4/sun4c specific memory-management startup hook. */
multiline_comment|/* Map the passed segment in the given context at the passed&n; * virtual address.&n; */
r_extern
r_void
id|prom_putsegment
c_func
(paren
r_int
id|context
comma
r_int
r_int
id|virt_addr
comma
r_int
id|physical_segment
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
multiline_comment|/* Return the first property type, as a string, for the given node.&n; * Returns a null string on error.&n; */
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
multiline_comment|/* Returns the next property after the passed property for the given&n; * node.  Returns null string on failure.&n; */
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
multiline_comment|/* Dorking with Bus ranges... */
multiline_comment|/* Apply promlib probes OBIO ranges to registers. */
r_extern
r_void
id|prom_apply_obio_ranges
c_func
(paren
r_struct
id|linux_prom_registers
op_star
id|obioregs
comma
r_int
id|nregs
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
id|spinlock_t
id|prom_lock
suffix:semicolon
macro_line|#endif /* !(__SPARC_OPLIB_H) */
eof
