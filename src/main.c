/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 04:54:35 by tdelage           #+#    #+#             */
/*   Updated: 2024/02/14 13:01:50 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <elf.h>
#include "structs.h"
#include <stdio.h>
#include <string.h>

#define ELF64_SECTION_HEADER_SIZE 0x40

int main(int count, char **args)
{
        int bits = 0;
        char *fileName = "a.out";
        if(count > 1) fileName = args[1];
        int fd = open(fileName, O_RDONLY);
        if(fd == -1) {
                ft_putstr_fd("Error: ", 1);
                ft_putstr_fd(fileName, 1);
                ft_putendl_fd(" not found", 1);
                return 1;
        }
        struct stat buf;
        fstat(fd, &buf);
        void *ptr = mmap(NULL, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
        if(ptr == MAP_FAILED) {
                ft_putendl_fd("Error: mmap failed", 1);
                return 1;
        }
        close(fd);
        struct ELFHeader *head = (struct ELFHeader *)ptr;
        t_u64 offset = 0;
        if(head->ELFSize == 1) {
                bits = 32;
                offset = ((t_u64)((struct ELF32Header *)ptr)->ELFSectionTable);
        } else if(head->ELFSize == 2) {
                bits = 64;
                offset = ((struct ELF64Header *)ptr)->ELFSectionTable;
        }
        if(!bits) {
                munmap(ptr, buf.st_size);
                return 1;
        }
        if(bits == 64) {
                struct ELF64Header *header = (struct ELF64Header *)ptr;
                struct ELF64SectionHeader *section = (struct ELF64SectionHeader *)(ptr + offset);
                section = (struct ELF64SectionHeader *)(ptr + offset);
                printf("%d\n", header->ELFSectionHeaderNumbr);
                for(t_u64 i = 1; i < header->ELFSectionHeaderNumbr; i++) {
                        if(i == header->ELFSectionNameEntry) continue;
                        if(section[i].ESHType == 2 || section[i].ESHType == 11) {
                                struct ELF64SymbolTableEntry *entry = (struct ELF64SymbolTableEntry *)(ptr + section[i].ESHOffset);
                                for(t_u64 j = 1; j < section[i].ESHSize / section[i].ESHEntrySize; j++) {
                                        char c = 'X';
                                        if(entry[j].ESTEType == STT_FILE) continue;
                                        if(entry[j].ESTESHIndex == SHN_ABS) c = 'A';
                                        else if(entry[j].ESTESHIndex == SHN_COMMON) c = 'C';
                                        if(entry[j].ESTEType == STT_FUNC) c = 'T';
                                        if(entry[j].ESTEBind == STB_LOCAL) c = ft_tolower(c);
                                        else if(entry[j].ESTEBind == STB_GLOBAL) c = ft_toupper(c);
                                        if(entry[j].ESTESHIndex == SHN_UNDEF) c = 'U';
                                        char *name = (char *)ptr + section[section[i].ESHIndex].ESHOffset + entry[j].ESTEName;
                                        if(!entry[j].ESTEValue) printf("                 %c %s => 0x%x\n", c, name, entry[j].ESTEType);
                                        else printf("%016llx %c %s => 0x%x\n", entry[j].ESTEValue, c, name, entry[j].ESTEType);
                                }
                        }
                }
        }
        munmap(ptr, buf.st_size);
        return 0;
}
