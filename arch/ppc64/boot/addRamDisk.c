macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;stdlib.h&gt;
macro_line|#include &lt;netinet/in.h&gt;
macro_line|#include &lt;unistd.h&gt;
macro_line|#include &lt;sys/types.h&gt;
macro_line|#include &lt;sys/stat.h&gt;
macro_line|#include &lt;string.h&gt;
DECL|macro|ElfHeaderSize
mdefine_line|#define ElfHeaderSize  (64 * 1024)
DECL|macro|ElfPages
mdefine_line|#define ElfPages  (ElfHeaderSize / 4096)
DECL|macro|KERNELBASE
mdefine_line|#define KERNELBASE (0xc000000000000000)
DECL|function|get4k
r_void
id|get4k
c_func
(paren
id|FILE
op_star
id|file
comma
r_char
op_star
id|buf
)paren
(brace
r_int
id|j
suffix:semicolon
r_int
id|num
op_assign
id|fread
c_func
(paren
id|buf
comma
l_int|1
comma
l_int|4096
comma
id|file
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
id|num
suffix:semicolon
id|j
OL
l_int|4096
suffix:semicolon
op_increment
id|j
)paren
id|buf
(braket
id|j
)braket
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|put4k
r_void
id|put4k
c_func
(paren
id|FILE
op_star
id|file
comma
r_char
op_star
id|buf
)paren
(brace
id|fwrite
c_func
(paren
id|buf
comma
l_int|1
comma
l_int|4096
comma
id|file
)paren
suffix:semicolon
)brace
DECL|function|death
r_void
id|death
c_func
(paren
r_const
r_char
op_star
id|msg
comma
id|FILE
op_star
id|fdesc
comma
r_const
r_char
op_star
id|fname
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
id|msg
)paren
suffix:semicolon
id|fclose
c_func
(paren
id|fdesc
)paren
suffix:semicolon
id|unlink
c_func
(paren
id|fname
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|main
r_int
id|main
c_func
(paren
r_int
id|argc
comma
r_char
op_star
op_star
id|argv
)paren
(brace
r_char
id|inbuf
(braket
l_int|4096
)braket
suffix:semicolon
id|FILE
op_star
id|ramDisk
op_assign
l_int|NULL
suffix:semicolon
id|FILE
op_star
id|sysmap
op_assign
l_int|NULL
suffix:semicolon
id|FILE
op_star
id|inputVmlinux
op_assign
l_int|NULL
suffix:semicolon
id|FILE
op_star
id|outputVmlinux
op_assign
l_int|NULL
suffix:semicolon
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|ramFileLen
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|ramLen
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|roundR
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|sysmapFileLen
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|sysmapLen
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|sysmapPages
op_assign
l_int|0
suffix:semicolon
r_char
op_star
id|ptr_end
op_assign
l_int|NULL
suffix:semicolon
r_int
r_int
id|offset_end
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|kernelLen
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|actualKernelLen
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|round
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|roundedKernelLen
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|ramStartOffs
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|ramPages
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|roundedKernelPages
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|hvReleaseData
op_assign
l_int|0
suffix:semicolon
id|u_int32_t
id|eyeCatcher
op_assign
l_int|0xc8a5d9c4
suffix:semicolon
r_int
r_int
id|naca
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|xRamDisk
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|xRamDiskSize
op_assign
l_int|0
suffix:semicolon
r_int
id|padPages
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|argc
OL
l_int|2
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Name of RAM disk file missing.&bslash;n&quot;
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|argc
OL
l_int|3
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Name of System Map input file is missing.&bslash;n&quot;
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|argc
OL
l_int|4
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Name of vmlinux file missing.&bslash;n&quot;
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|argc
OL
l_int|5
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Name of vmlinux output file missing.&bslash;n&quot;
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
id|ramDisk
op_assign
id|fopen
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
l_string|&quot;r&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ramDisk
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;RAM disk file &bslash;&quot;%s&bslash;&quot; failed to open.&bslash;n&quot;
comma
id|argv
(braket
l_int|1
)braket
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
id|sysmap
op_assign
id|fopen
c_func
(paren
id|argv
(braket
l_int|2
)braket
comma
l_string|&quot;r&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sysmap
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;System Map file &bslash;&quot;%s&bslash;&quot; failed to open.&bslash;n&quot;
comma
id|argv
(braket
l_int|2
)braket
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
id|inputVmlinux
op_assign
id|fopen
c_func
(paren
id|argv
(braket
l_int|3
)braket
comma
l_string|&quot;r&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inputVmlinux
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;vmlinux file &bslash;&quot;%s&bslash;&quot; failed to open.&bslash;n&quot;
comma
id|argv
(braket
l_int|3
)braket
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
id|outputVmlinux
op_assign
id|fopen
c_func
(paren
id|argv
(braket
l_int|4
)braket
comma
l_string|&quot;w+&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|outputVmlinux
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;output vmlinux file &bslash;&quot;%s&bslash;&quot; failed to open.&bslash;n&quot;
comma
id|argv
(braket
l_int|4
)braket
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/* Input Vmlinux file */
id|fseek
c_func
(paren
id|inputVmlinux
comma
l_int|0
comma
id|SEEK_END
)paren
suffix:semicolon
id|kernelLen
op_assign
id|ftell
c_func
(paren
id|inputVmlinux
)paren
suffix:semicolon
id|fseek
c_func
(paren
id|inputVmlinux
comma
l_int|0
comma
id|SEEK_SET
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;kernel file size = %d&bslash;n&quot;
comma
id|kernelLen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|kernelLen
op_eq
l_int|0
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;You must have a linux kernel specified as argv[3]&bslash;n&quot;
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
id|actualKernelLen
op_assign
id|kernelLen
op_minus
id|ElfHeaderSize
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;actual kernel length (minus ELF header) = %d&bslash;n&quot;
comma
id|actualKernelLen
)paren
suffix:semicolon
id|round
op_assign
id|actualKernelLen
op_mod
l_int|4096
suffix:semicolon
id|roundedKernelLen
op_assign
id|actualKernelLen
suffix:semicolon
r_if
c_cond
(paren
id|round
)paren
id|roundedKernelLen
op_add_assign
(paren
l_int|4096
op_minus
id|round
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;Vmlinux length rounded up to a 4k multiple = %ld/0x%lx &bslash;n&quot;
comma
id|roundedKernelLen
comma
id|roundedKernelLen
)paren
suffix:semicolon
id|roundedKernelPages
op_assign
id|roundedKernelLen
op_div
l_int|4096
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;Vmlinux pages to copy = %ld/0x%lx &bslash;n&quot;
comma
id|roundedKernelPages
comma
id|roundedKernelPages
)paren
suffix:semicolon
multiline_comment|/* Input System Map file */
multiline_comment|/* (needs to be processed simply to determine if we need to add pad pages due to the static variables not being included in the vmlinux) */
id|fseek
c_func
(paren
id|sysmap
comma
l_int|0
comma
id|SEEK_END
)paren
suffix:semicolon
id|sysmapFileLen
op_assign
id|ftell
c_func
(paren
id|sysmap
)paren
suffix:semicolon
id|fseek
c_func
(paren
id|sysmap
comma
l_int|0
comma
id|SEEK_SET
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%s file size = %ld/0x%lx &bslash;n&quot;
comma
id|argv
(braket
l_int|2
)braket
comma
id|sysmapFileLen
comma
id|sysmapFileLen
)paren
suffix:semicolon
id|sysmapLen
op_assign
id|sysmapFileLen
suffix:semicolon
id|roundR
op_assign
l_int|4096
op_minus
(paren
id|sysmapLen
op_mod
l_int|4096
)paren
suffix:semicolon
r_if
c_cond
(paren
id|roundR
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;Rounding System Map file up to a multiple of 4096, adding %ld/0x%lx &bslash;n&quot;
comma
id|roundR
comma
id|roundR
)paren
suffix:semicolon
id|sysmapLen
op_add_assign
id|roundR
suffix:semicolon
)brace
id|printf
c_func
(paren
l_string|&quot;Rounded System Map size is %ld/0x%lx &bslash;n&quot;
comma
id|sysmapLen
comma
id|sysmapLen
)paren
suffix:semicolon
multiline_comment|/* Process the Sysmap file to determine where _end is */
id|sysmapPages
op_assign
id|sysmapLen
op_div
l_int|4096
suffix:semicolon
multiline_comment|/* read the whole file line by line, expect that it doesnt fail */
r_while
c_loop
(paren
id|fgets
c_func
(paren
id|inbuf
comma
l_int|4096
comma
id|sysmap
)paren
)paren
suffix:semicolon
multiline_comment|/* search for _end in the last page of the system map */
id|ptr_end
op_assign
id|strstr
c_func
(paren
id|inbuf
comma
l_string|&quot; _end&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ptr_end
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Unable to find _end in the sysmap file &bslash;n&quot;
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;inbuf: &bslash;n&quot;
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%s &bslash;n&quot;
comma
id|inbuf
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
id|printf
c_func
(paren
l_string|&quot;Found _end in the last page of the sysmap - backing up 10 characters it looks like %s&quot;
comma
id|ptr_end
op_minus
l_int|10
)paren
suffix:semicolon
multiline_comment|/* convert address of _end in system map to hex offset. */
id|offset_end
op_assign
(paren
r_int
r_int
)paren
id|strtol
c_func
(paren
id|ptr_end
op_minus
l_int|10
comma
l_int|NULL
comma
l_int|16
)paren
suffix:semicolon
multiline_comment|/* calc how many pages we need to insert between the vmlinux and the start of the ram disk */
id|padPages
op_assign
id|offset_end
op_div
l_int|4096
op_minus
id|roundedKernelPages
suffix:semicolon
multiline_comment|/* Check and see if the vmlinux is already larger than _end in System.map */
r_if
c_cond
(paren
id|padPages
OL
l_int|0
)paren
(brace
multiline_comment|/* vmlinux is larger than _end - adjust the offset to the start of the embedded ram disk */
id|offset_end
op_assign
id|roundedKernelLen
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;vmlinux is larger than _end indicates it needs to be - offset_end = %lx &bslash;n&quot;
comma
id|offset_end
)paren
suffix:semicolon
id|padPages
op_assign
l_int|0
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;will insert %lx pages between the vmlinux and the start of the ram disk &bslash;n&quot;
comma
id|padPages
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* _end is larger than vmlinux - use the offset to _end that we calculated from the system map */
id|printf
c_func
(paren
l_string|&quot;vmlinux is smaller than _end indicates is needed - offset_end = %lx &bslash;n&quot;
comma
id|offset_end
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;will insert %lx pages between the vmlinux and the start of the ram disk &bslash;n&quot;
comma
id|padPages
)paren
suffix:semicolon
)brace
multiline_comment|/* Input Ram Disk file */
singleline_comment|// Set the offset that the ram disk will be started at.
id|ramStartOffs
op_assign
id|offset_end
suffix:semicolon
multiline_comment|/* determined from the input vmlinux file and the system map */
id|printf
c_func
(paren
l_string|&quot;Ram Disk will start at offset = 0x%lx &bslash;n&quot;
comma
id|ramStartOffs
)paren
suffix:semicolon
id|fseek
c_func
(paren
id|ramDisk
comma
l_int|0
comma
id|SEEK_END
)paren
suffix:semicolon
id|ramFileLen
op_assign
id|ftell
c_func
(paren
id|ramDisk
)paren
suffix:semicolon
id|fseek
c_func
(paren
id|ramDisk
comma
l_int|0
comma
id|SEEK_SET
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%s file size = %ld/0x%lx &bslash;n&quot;
comma
id|argv
(braket
l_int|1
)braket
comma
id|ramFileLen
comma
id|ramFileLen
)paren
suffix:semicolon
id|ramLen
op_assign
id|ramFileLen
suffix:semicolon
id|roundR
op_assign
l_int|4096
op_minus
(paren
id|ramLen
op_mod
l_int|4096
)paren
suffix:semicolon
r_if
c_cond
(paren
id|roundR
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;Rounding RAM disk file up to a multiple of 4096, adding %ld/0x%lx &bslash;n&quot;
comma
id|roundR
comma
id|roundR
)paren
suffix:semicolon
id|ramLen
op_add_assign
id|roundR
suffix:semicolon
)brace
id|printf
c_func
(paren
l_string|&quot;Rounded RAM disk size is %ld/0x%lx &bslash;n&quot;
comma
id|ramLen
comma
id|ramLen
)paren
suffix:semicolon
id|ramPages
op_assign
id|ramLen
op_div
l_int|4096
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;RAM disk pages to copy = %ld/0x%lx&bslash;n&quot;
comma
id|ramPages
comma
id|ramPages
)paren
suffix:semicolon
singleline_comment|// Copy 64K ELF header
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
(paren
id|ElfPages
)paren
suffix:semicolon
op_increment
id|i
)paren
(brace
id|get4k
c_func
(paren
id|inputVmlinux
comma
id|inbuf
)paren
suffix:semicolon
id|put4k
c_func
(paren
id|outputVmlinux
comma
id|inbuf
)paren
suffix:semicolon
)brace
multiline_comment|/* Copy the vmlinux (as full pages). */
id|fseek
c_func
(paren
id|inputVmlinux
comma
id|ElfHeaderSize
comma
id|SEEK_SET
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|roundedKernelPages
suffix:semicolon
op_increment
id|i
)paren
(brace
id|get4k
c_func
(paren
id|inputVmlinux
comma
id|inbuf
)paren
suffix:semicolon
id|put4k
c_func
(paren
id|outputVmlinux
comma
id|inbuf
)paren
suffix:semicolon
)brace
multiline_comment|/* Insert pad pages (if appropriate) that are needed between */
multiline_comment|/* | the end of the vmlinux and the ram disk. */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|padPages
suffix:semicolon
op_increment
id|i
)paren
(brace
id|memset
c_func
(paren
id|inbuf
comma
l_int|0
comma
l_int|4096
)paren
suffix:semicolon
id|put4k
c_func
(paren
id|outputVmlinux
comma
id|inbuf
)paren
suffix:semicolon
)brace
multiline_comment|/* Copy the ram disk (as full pages). */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|ramPages
suffix:semicolon
op_increment
id|i
)paren
(brace
id|get4k
c_func
(paren
id|ramDisk
comma
id|inbuf
)paren
suffix:semicolon
id|put4k
c_func
(paren
id|outputVmlinux
comma
id|inbuf
)paren
suffix:semicolon
)brace
multiline_comment|/* Close the input files */
id|fclose
c_func
(paren
id|ramDisk
)paren
suffix:semicolon
id|fclose
c_func
(paren
id|inputVmlinux
)paren
suffix:semicolon
multiline_comment|/* And flush the written output file */
id|fflush
c_func
(paren
id|outputVmlinux
)paren
suffix:semicolon
multiline_comment|/* Fixup the new vmlinux to contain the ram disk starting offset (xRamDisk) and the ram disk size (xRamDiskSize) */
multiline_comment|/* fseek to the hvReleaseData pointer */
id|fseek
c_func
(paren
id|outputVmlinux
comma
id|ElfHeaderSize
op_plus
l_int|0x24
comma
id|SEEK_SET
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fread
c_func
(paren
op_amp
id|hvReleaseData
comma
l_int|4
comma
l_int|1
comma
id|outputVmlinux
)paren
op_ne
l_int|1
)paren
(brace
id|death
c_func
(paren
l_string|&quot;Could not read hvReleaseData pointer&bslash;n&quot;
comma
id|outputVmlinux
comma
id|argv
(braket
l_int|4
)braket
)paren
suffix:semicolon
)brace
id|hvReleaseData
op_assign
id|ntohl
c_func
(paren
id|hvReleaseData
)paren
suffix:semicolon
multiline_comment|/* Convert to native int */
id|printf
c_func
(paren
l_string|&quot;hvReleaseData is at %08x&bslash;n&quot;
comma
id|hvReleaseData
)paren
suffix:semicolon
multiline_comment|/* fseek to the hvReleaseData */
id|fseek
c_func
(paren
id|outputVmlinux
comma
id|ElfHeaderSize
op_plus
id|hvReleaseData
comma
id|SEEK_SET
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fread
c_func
(paren
id|inbuf
comma
l_int|0x40
comma
l_int|1
comma
id|outputVmlinux
)paren
op_ne
l_int|1
)paren
(brace
id|death
c_func
(paren
l_string|&quot;Could not read hvReleaseData&bslash;n&quot;
comma
id|outputVmlinux
comma
id|argv
(braket
l_int|4
)braket
)paren
suffix:semicolon
)brace
multiline_comment|/* Check hvReleaseData sanity */
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|inbuf
comma
op_amp
id|eyeCatcher
comma
l_int|4
)paren
op_ne
l_int|0
)paren
(brace
id|death
c_func
(paren
l_string|&quot;hvReleaseData is invalid&bslash;n&quot;
comma
id|outputVmlinux
comma
id|argv
(braket
l_int|4
)braket
)paren
suffix:semicolon
)brace
multiline_comment|/* Get the naca pointer */
id|naca
op_assign
id|ntohl
c_func
(paren
op_star
(paren
(paren
id|u_int32_t
op_star
)paren
op_amp
id|inbuf
(braket
l_int|0x0C
)braket
)paren
)paren
op_minus
id|KERNELBASE
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;Naca is at offset 0x%lx &bslash;n&quot;
comma
id|naca
)paren
suffix:semicolon
multiline_comment|/* fseek to the naca */
id|fseek
c_func
(paren
id|outputVmlinux
comma
id|ElfHeaderSize
op_plus
id|naca
comma
id|SEEK_SET
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fread
c_func
(paren
id|inbuf
comma
l_int|0x18
comma
l_int|1
comma
id|outputVmlinux
)paren
op_ne
l_int|1
)paren
(brace
id|death
c_func
(paren
l_string|&quot;Could not read naca&bslash;n&quot;
comma
id|outputVmlinux
comma
id|argv
(braket
l_int|4
)braket
)paren
suffix:semicolon
)brace
id|xRamDisk
op_assign
id|ntohl
c_func
(paren
op_star
(paren
(paren
id|u_int32_t
op_star
)paren
op_amp
id|inbuf
(braket
l_int|0x0c
)braket
)paren
)paren
suffix:semicolon
id|xRamDiskSize
op_assign
id|ntohl
c_func
(paren
op_star
(paren
(paren
id|u_int32_t
op_star
)paren
op_amp
id|inbuf
(braket
l_int|0x14
)braket
)paren
)paren
suffix:semicolon
multiline_comment|/* Make sure a RAM disk isn&squot;t already present */
r_if
c_cond
(paren
(paren
id|xRamDisk
op_ne
l_int|0
)paren
op_logical_or
(paren
id|xRamDiskSize
op_ne
l_int|0
)paren
)paren
(brace
id|death
c_func
(paren
l_string|&quot;RAM disk is already attached to this kernel&bslash;n&quot;
comma
id|outputVmlinux
comma
id|argv
(braket
l_int|4
)braket
)paren
suffix:semicolon
)brace
multiline_comment|/* Fill in the values */
op_star
(paren
(paren
id|u_int32_t
op_star
)paren
op_amp
id|inbuf
(braket
l_int|0x0c
)braket
)paren
op_assign
id|htonl
c_func
(paren
id|ramStartOffs
)paren
suffix:semicolon
op_star
(paren
(paren
id|u_int32_t
op_star
)paren
op_amp
id|inbuf
(braket
l_int|0x14
)braket
)paren
op_assign
id|htonl
c_func
(paren
id|ramPages
)paren
suffix:semicolon
multiline_comment|/* Write out the new naca */
id|fflush
c_func
(paren
id|outputVmlinux
)paren
suffix:semicolon
id|fseek
c_func
(paren
id|outputVmlinux
comma
id|ElfHeaderSize
op_plus
id|naca
comma
id|SEEK_SET
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fwrite
c_func
(paren
id|inbuf
comma
l_int|0x18
comma
l_int|1
comma
id|outputVmlinux
)paren
op_ne
l_int|1
)paren
(brace
id|death
c_func
(paren
l_string|&quot;Could not write naca&bslash;n&quot;
comma
id|outputVmlinux
comma
id|argv
(braket
l_int|4
)braket
)paren
suffix:semicolon
)brace
id|printf
c_func
(paren
l_string|&quot;Ram Disk of 0x%lx pages is attached to the kernel at offset 0x%08x&bslash;n&quot;
comma
id|ramPages
comma
id|ramStartOffs
)paren
suffix:semicolon
multiline_comment|/* Done */
id|fclose
c_func
(paren
id|outputVmlinux
)paren
suffix:semicolon
multiline_comment|/* Set permission to executable */
id|chmod
c_func
(paren
id|argv
(braket
l_int|4
)braket
comma
id|S_IRUSR
op_or
id|S_IWUSR
op_or
id|S_IXUSR
op_or
id|S_IRGRP
op_or
id|S_IXGRP
op_or
id|S_IROTH
op_or
id|S_IXOTH
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
