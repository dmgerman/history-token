macro_line|#ifndef _ASM_NUMNODES_H_
DECL|macro|_ASM_NUMNODES_H_
mdefine_line|#define _ASM_NUMNODES_H_
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_DISCONTIGMEM
macro_line|#if defined(CONFIG_CHIP_M32700)
DECL|macro|NODES_SHIFT
mdefine_line|#define&t;NODES_SHIFT&t;1&t;/* Max 2 Nodes */
macro_line|#endif&t;/* CONFIG_CHIP_M32700 */
macro_line|#endif&t;/* CONFIG_DISCONTIGMEM */
macro_line|#endif&t;/* _ASM_NUMNODES_H_ */
eof
