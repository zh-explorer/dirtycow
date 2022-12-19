import sys
from elftools.elf import sections
from elftools.elf.elffile import ELFFile
import os


def to_c_array(data: bytes) -> str:
    size_line = "unsigned int shellcode_size = %d;\n" % len(data)
    c_array = "unsigned char shellcode[] = {\n%s\n};\n"
    lines = ''
    while len(data) != 0:
        line_data = data[:16]
        data = data[16:]
        line = ''
        for b in line_data:
            line += "0x%02x, " % b
        line = line[:-1]
        line += '\n'
        lines += line


    return c_array % lines[:-1] + size_line


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

array = to_c_array(shellcode)

with open(out_file, 'w') as fp:
    fp.write(array)
