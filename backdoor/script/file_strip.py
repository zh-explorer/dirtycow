import sys
from elftools.elf import sections
from elftools.elf.elffile import ELFFile
import os

elf_file = sys.argv[1]
out_file = sys.argv[2]

elf = ELFFile(open(elf_file, 'rb'))

sym_section: sections.SymbolTableSection = elf.get_section_by_name(".symtab")

shellcode_start = sym_section.get_symbol_by_name("__shellcode_start")[0].entry
shellcode_start_offset = shellcode_start['st_value']

shellcode_end = sym_section.get_symbol_by_name("__shellcode_end")[0].entry
shellcode_end_offset = shellcode_end['st_value']

with open(elf_file, 'rb') as fp:
    fp.seek(shellcode_start_offset, os.SEEK_SET)
    shellcode = fp.read(shellcode_end_offset - shellcode_start_offset)

with open(out_file, 'wb') as fp:
    fp.write(shellcode)
