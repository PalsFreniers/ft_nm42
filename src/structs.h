#ifndef STRUCTS_H
#define STRUCTS_H

#include "../libft/libft.h"

struct ELFHeader {
        t_u32 ELFMagic;
        t_u8  ELFSize;
};

struct ELF32Header {
        t_u32 ELFMagic;
        t_u8  ELFSize;
        t_u8  ELFEndian;
        t_u8  ELFOne;
        t_u8  ELFSystem;
        t_u8  ELFAbiVersion;
        t_u8  ELFPadding[7];
        t_u16 ELFObjctType;
        t_u16 ELFArch;
        t_u32 ELFVersion;
        t_u32 ELFStart;
        t_u32 ELFHeadTable;
        t_u32 ELFSectionTable;
        t_u32 ELFArchSpec;
        t_u16 ELFHeadSize;
        t_u16 ELFProgHeaderSize;
        t_u16 ELFProgHeaderNumber;
        t_u16 ELFSectionHeaderSize;
        t_u16 ELFSectionHeaderNumbr;
        t_u16 ELFSectionNameEntry;
};

struct ELF64Header {
        t_u32 ELFMagic;
        t_u8  ELFSize;
        t_u8  ELFEndian;
        t_u8  ELFOne;
        t_u8  ELFSystem;
        t_u8  ELFAbiVersion;
        t_u8  ELFPadding[7];
        t_u16 ELFObjctType;
        t_u16 ELFArch;
        t_u32 ELFVersion;
        t_u64 ELFStart;
        t_u64 ELFHeadTable;
        t_u64 ELFSectionTable;
        t_u32 ELFArchSpec;
        t_u16 ELFHeadSize;
        t_u16 ELFProgHeaderSize;
        t_u16 ELFProgHeaderNumber;
        t_u16 ELFSectionHeaderSize;
        t_u16 ELFSectionHeaderNumbr;
        t_u16 ELFSectionNameEntry;
};

struct ELF64SectionHeader {
        t_u32 ESHName;
        t_u32 ESHType;
        t_u64 ESHFlags;
        t_u64 ESHAddress;
        t_u64 ESHOffset;
        t_u64 ESHSize;
        t_u32 ESHIndex;
        t_u32 ESHInfo;
        t_u64 ESHAlign;
        t_u64 ESHEntrySize;
};

struct ELF64SymbolTableEntry {
        t_u32 ESTEName;
        union { 
                t_u8  ESTEInfo;
                struct {
                        t_u8  ESTEType : 4;
                        t_u8  ESTEBind : 4;
                };
        };
        union {
                t_u8  ESTEOther;
                struct {
                        t_u8  ESTEVisibility : 2;
                        t_u8  ESTEPadding : 6;
                };
        };
        t_u16 ESTESHIndex;
        t_u64 ESTEValue;
        t_u64 ESTESize;
};

#endif // STRUCTS_H
