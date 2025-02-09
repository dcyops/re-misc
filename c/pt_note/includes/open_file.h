#ifndef OPEN_FILE_H
#define OPEN_FILE_H

#include <elf.h>
#include <stdint.h>
#include <stdio.h>

#if defined(__x86_64__) || \
    defined(_M_X64) || \
    defined(__aarch64__) || \
    defined(__PPC64__)

#define ElfW(type) Elf64_##type
#else
#define ElfW(type) Elf32_##type
#endif

typedef struct {
    int fd;
    ElfW(Ehdr) header;
    ElfW(Phdr) *program_headers;
}ElfFile;

int open_file(const char *file_, ElfFile *elf);
void close_file(ElfFile *elf);

// void parse_elf_headers(ElfFile *elf);
// void convert_note_to_load (const char *file_);
// void adjust_entry_point (const char *file_);
// void insert_code (const char *file_);
// int create_new_elf (const char *file_);

#endif /* INSPECT_FILE_H */
/* EOF */
