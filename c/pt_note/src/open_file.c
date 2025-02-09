#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <libelf.h>
#include <gelf.h>
#include "../includes/open_elf.h"

 1. Open the ELF file to be injected
  2. Save the original entry point, e_entry
  3. Parse the program header table, looking for a PT_NOTE segment
  4. Convert the PT_NOTE segment to a PT_LOAD segment
  5. Change the memory protections for this segment to allow executable instructions
  6. Change the entry point address to an area that will not conflict with the 
     original program execution.
  7. Adjust the size on disk and virtual memory size to account for the size of the 
     injected code
  8. Point the offset of our converted segment to the end of the original binary, 
     where we will store the new code
  9. Patch the end of the code with instructions to jump to the original entry point
 10. Add our injected code to the end of the file
*11. Write the file back to disk, over the original file* -- we will not cover this 
     implementation variant here, which creates	a new temporary ELF binary on disk 
     and overwrites the host, as referenced above.


int
open_file(const char *file_, ElfFile *elf)
{
  // Zero out the ElfFile struct for hygiene purposes
  memset(elf, 0, sizeof(ElfFile));

  // Store the return value of open() to the fd field inside of the ElFile structk
  // elf being our pointer to the struct in this case.
  elf->fd = open(file_, O_RDWR);
  if(elf->fd < 0)
  { 
    perror("open");
    return EXIT_FAILURE;
  }
  
  return 0;
}

void
close_file(ElfFile *elf)
{
  return;
}

