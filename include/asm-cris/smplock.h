macro_line|#ifndef __ASM_CRIS_SMPLOCK_H
DECL|macro|__ASM_CRIS_SMPLOCK_H
mdefine_line|#define __ASM_CRIS_SMPLOCK_H
multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifndef CONFIG_SMP
DECL|macro|lock_kernel
mdefine_line|#define lock_kernel()                           do { } while(0)
DECL|macro|unlock_kernel
mdefine_line|#define unlock_kernel()                         do { } while(0)
DECL|macro|release_kernel_lock
mdefine_line|#define release_kernel_lock(task, cpu, depth)   ((depth) = 1)
DECL|macro|reacquire_kernel_lock
mdefine_line|#define reacquire_kernel_lock(task, cpu, depth) do { } while(0)
macro_line|#else
macro_line|#error &quot;We do not support SMP on CRIS&quot;
macro_line|#endif
macro_line|#endif
eof
