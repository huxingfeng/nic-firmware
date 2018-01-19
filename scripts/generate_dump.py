#!/usr/bin/env python2
##
## Copyright (C) 2017,  Netronome Systems, Inc.  All rights reserved.
"""
This scripts generates troubleshoot init directives in an uc file
"""
import math
import sys
import argparse

class nfp_dump_type :
    type_cpp_csr = 0
    type_xpb_csr = 1
    type_me_csr = 2
    type_indirect_me_csr = 3
    type_rtsym = 4
    type_hwinfo = 5
    type_fwname = 6
    type_hwinfo_field = 7
    type_unset = 0xff

def init_directive(symbol, offset, value):
    swap = "(((" + value + " & 0xff) << 24) \\\n    | ((" + value + " & 0xff00) << 8) \\\n    | ((" + value + " & 0xff0000) >> 8) \\\n    | ((" + value + " & 0xff000000) >> 24))"
    return ".init" + " " + str(symbol) + "+" + str(offset) + " " + swap + "\n"

def generate(input_file, output_path, prefix, filename):

    #Dictionary of comments
    comments = {}
    comments["tat"] = ";tgt << 24 | act << 16 | tok << 8 | isld\n"
    comments["CSR offset"] = ";CSR offset\n"
    comments["dump length"] = ";dump length\n"
    comments["tlv length"] = ";tlv length\n"
    comments["level"] = ";level\n"
    comments["level length"] = ";level length\n"
    comments["value"] = ";value\n"
    comments["string index"] = ";string index\n"
    comments["CSR width"] = ";CSR width\n"
    comments[nfp_dump_type.type_xpb_csr] = ";type: xpb\n"
    comments[nfp_dump_type.type_cpp_csr] = ";type: cpp\n"
    comments[nfp_dump_type.type_me_csr] = ";type: mecsr\n"
    comments[nfp_dump_type.type_indirect_me_csr] = ";type: indirect mecsr\n"
    comments[nfp_dump_type.type_rtsym] = ";type: rtsym\n"
    comments[nfp_dump_type.type_hwinfo] = ";type: Hardware Info\n"
    comments[nfp_dump_type.type_fwname] = ";type: Firmware Name\n"
    comments[nfp_dump_type.type_hwinfo_field] = ";type: Hardware Info Field\n"

    symbol = str(prefix)
    symbol_name = "_" + symbol

    #Output to be written to file
    output_lines = ["#ifndef " + symbol.upper() + "_UC\n", \
                    "#define " + symbol.upper() + "_UC\n",\
                    ";This file is automatically generated\n",\
                    ";Do not edit\n",\
                    "; Format of data in NFP memory:\n", \
                    ";    Bit    3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0 0 0\n", \
                    ";    -----\ 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0\n", \
                    ";    Word  +---------------+---------------+---------------+---------------+\n", \
                    ";       0  |                             Level                             |\n", \
                    ";          +---------------+---------------+---------------+---------------+\n", \
                    ";       1  |  Level length in bytes, without \"level\" and \"level length\"    |\n", \
                    ";          +-------------------------------+-------------------------------+\n", \
                    ";       2  | Type ( E.g. 0 = CPP, 1 = XPB, 2 = ME CSR, etc...              |\n", \
                    ";          +-------------------------------+-------------------------------+\n", \
                    ";       3  |                 Length (not including Type and Length)        |\n", \
                    ";          +-------------------------------+-------------------------------+\n", \
                    ";       4  |                            Value                              |\n", \
                    ";          +-------------------------------+-------------------------------+\n", \
                    ";                                       ......\n", \
                    ";          +-------------------------------+-------------------------------+\n", \
                    ";       .  |                               Type                            |\n", \
                    ";          +-------------------------------+-------------------------------+\n", \
                    ";       .  |                               Length                          |\n", \
                    ";          +-------------------------------+-------------------------------+\n", \
                    ";       .  |                               Value                           |\n", \
                    ";          +-------------------------------+-------------------------------+\n", \
                    ";                                        .....\n", \
                    ";          +-------------------------------+-------------------------------+\n", \
                    ";       .  |                          Level                                |\n", \
                    ";          +-------------------------------+-------------------------------+\n", \
                    ";       .  |                          Level length                         |\n", \
                    ";          +-------------------------------+-------------------------------+\n", \
                    ";       .  |                               Type                            |\n", \
                    ";          +-------------------------------+-------------------------------+\n", \
                    ";       .  |                               Length                          |\n", \
                    ";          +-------------------------------+-------------------------------+\n", \
                    ";       .  |                               Value                           |\n", \
                    ";          +-------------------------------+-------------------------------+\n", \
                    ";                                      (etc...)\n", \
                    "\n"]

    alloc_mem_idx = len(output_lines)

    #Dictionary of types
    types = {}
    types["xpb"] = nfp_dump_type.type_xpb_csr
    types["cpp"] = nfp_dump_type.type_cpp_csr
    types["me_csr"] = nfp_dump_type.type_me_csr
    types["me_ind_csr"] = nfp_dump_type.type_indirect_me_csr
    types["rtsym"] = nfp_dump_type.type_rtsym
    types["hwinfo"] = nfp_dump_type.type_hwinfo
    types["fwname"] = nfp_dump_type.type_fwname
    types["hwinfo_field"] = nfp_dump_type.type_hwinfo_field

    prev_top = ""
    size_of_csr_struct = 12
    levels = []
    rtsyms = []
    csrs = []
    csr = []
    type = nfp_dump_type.type_unset
    level = -1
    lvl_len_offset = 0
    lvl_idx = -1
    lvl_len = 0
    level_ended = True

    tat_define = ""
    offset = 0

    version = ""

    string_index = 0
    max_csr_str_len = 0
    with open(input_file, 'r') as in_file_handle:
        for line in in_file_handle:

            #strip leading and trailing white space
            line = line.rstrip()
            line = line.lstrip()

            #Ignore empty lines
            if line == "":
                continue

            #Ignore comments
            if line.startswith("#") :
                continue

            #Parse metadata
            if line.startswith("@") :
                meta_str = line.split(":")
                if meta_str[0] == "@type" :
                    if level == -1:
                        raise ValueError('Level not set')
                    type = types[meta_str[1]]

                elif meta_str[0] == "@level" :
                    if not level_ended :
                        raise ValueError("Previous level not ended")

                    level = int(meta_str[1])

                    lvl_len = 0

                    lvl_len_offset = offset
                    offset += 8
                    lvl_idx = len(output_lines)
                    level_ended = False

                elif meta_str[0] == "@level_end" :
                    if level_ended :
                        raise ValueError("Found @level_end without @level")

                    #This level is done, write the length
                    output_lines.insert(lvl_idx, comments["level"])
                    lvl_idx += 1
                    output_lines.insert(lvl_idx, init_directive(symbol_name, lvl_len_offset, str(level)))
                    lvl_len_offset += 4
                    lvl_idx += 1

                    output_lines.insert(lvl_idx, comments["level length"])
                    lvl_idx += 1
                    output_lines.insert(lvl_idx, init_directive(symbol_name, lvl_len_offset, str(lvl_len)))
                    lvl_len_offset += 4

                    level_ended = True
                elif meta_str[0] == "@version" :
                    version = meta_str[1]

                else :
                    raise ValueError('Unknown Metadata')

                continue

            if type != nfp_dump_type.type_unset :

                if type == nfp_dump_type.type_rtsym or type == nfp_dump_type.type_hwinfo_field :

                    if level == -1:
                        raise ValueError('Level not set')

                    output_lines.append(comments[type])
                    output_lines.append(init_directive(symbol_name, offset, str(type)))
                    offset += 4
                    lvl_len += 4

                    str_len = len(line) + (4 - len(line) % 4)

                    if str_len > 128:
                        raise ValueError("RT symbol \""+ line +"\" name length exceeds 127 bytes")

                    output_lines.append(comments["tlv length"])
                    output_lines.append(init_directive(symbol_name, offset, str(str_len)))
                    offset += 4
                    lvl_len += 4


                    output_lines.append(comments["value"])
                    output_lines.append(";" + line + "\n")

                    init_str = ""
                    count = 1
                    for c in list(line) :
                        init_str += str(format(ord(c), 'x'))
                        if count % 4 == 0:
                            init_str = "0x" + init_str
                            output_lines.append(init_directive(symbol_name, offset, init_str))
                            lvl_len += 4
                            offset += 4
                            init_str = ""
                        count +=1

                    for i in xrange(count, (str_len + 1)) :
                        init_str += "00"
                    init_str = "0x" + init_str
                    output_lines.append(init_directive(symbol_name, offset, init_str))

                    offset += 4
                    lvl_len += 4

                    output_lines.append("\n")

                elif type == nfp_dump_type.type_hwinfo or type == nfp_dump_type.type_fwname:
                    if level == -1:
                        raise ValueError('Level not set')

                    output_lines.append(comments[type])
                    output_lines.append(init_directive(symbol_name, offset, str(type)))
                    offset += 4
                    lvl_len += 4

                    output_lines.append(comments["tlv length"])
                    output_lines.append(init_directive(symbol_name, offset, str(0)))
                    offset += 4
                    lvl_len += 4

                    output_lines.append("\n")
                else :
                    if level == -1:
                        raise ValueError('Level not set')

                    csr = line.split()
                    start_csr = csr[0].split(".")
                    start_top = start_csr[0] + "." + start_csr[1]
                    from_csr = csr[0]
                    if len(csr) < 2 :
                        to_csr = csr[0]
                    else :
                        to_csr = csr[1]

                    if start_top != prev_top  :
                        output_lines.append("\n")
                        if tat_define != "":
                            output_lines.append("#undef "+ tat_define + "\n")
                            output_lines.append("\n")

                        prev_top = start_top
                        tat_define = "__" + start_csr[0].split(":")[1] + "_" + start_csr[1]
                        top_value = "((csr_cpp_tgt(\"" + start_top + "\") << 24) \\\n" + \
                        "   | (csr_cpp_rdact(\"" + start_top + "\") << 16) \\\n" + \
                        "   | (csr_cpp_rdtok(\"" + start_top + "\") << 8) \\\n" + \
                        "   | csr_isld(\"" + start_top + "\"))"
                        output_lines.append("#define "+ tat_define + " " + top_value + "\n")

                    output_lines.append("\n")

                    output_lines.append(comments[type])
                    output_lines.append(init_directive(symbol_name, offset, str(type)))
                    offset += 4
                    lvl_len += 4

                    size_of_csr_struct = 0
                    csr_len_idx = len(output_lines)
                    csr_len_offset = offset
                    offset += 4
                    lvl_len += 4

                    output_lines.append(comments["tat"])
                    output_lines.append(init_directive(symbol_name, offset, tat_define))
                    offset += 4
                    lvl_len += 4
                    size_of_csr_struct += 4

                    output_lines.append(comments["CSR offset"])
                    output_lines.append(init_directive(symbol_name, offset, "csr_offset(\"" + from_csr + "\")"))
                    offset += 4
                    lvl_len += 4
                    size_of_csr_struct += 4

                    output_lines.append(comments["dump length"])
                    length_str = "(csr_offset(\"" + to_csr + "\") - csr_offset(\"" + from_csr + "\") + csr_width(\"" + from_csr + "\")/8)"
                    output_lines.append(init_directive(symbol_name, offset, length_str))
                    offset += 4
                    lvl_len += 4
                    size_of_csr_struct += 4

                    output_lines.append(comments["CSR width"])
                    output_lines.append(init_directive(symbol_name, offset, "csr_width(\"" + from_csr + "\")"))
                    offset += 4
                    lvl_len += 4
                    size_of_csr_struct += 4

                    # output_lines.append(comments["string index"])
                    # output_lines.append(init_directive(symbol_name, offset, str(string_index)))
                    # string_index += 1
                    # csrs.append(from_csr)
                    # if len(from_csr) > max_csr_str_len:
                        # max_csr_str_len = len(from_csr)
                    # offset += 4
                    # lvl_len += 4
                    # size_of_csr_struct += 4

                    output_lines.insert(csr_len_idx, comments["tlv length"])
                    csr_len_idx += 1
                    output_lines.insert(csr_len_idx, init_directive(symbol_name, csr_len_offset, str(size_of_csr_struct)))


            else :
                raise ValueError('Unknown Type')

        offset = offset + (8 - offset % 8)
        output_lines.insert(alloc_mem_idx, ".alloc_mem " + symbol_name + " emem global " + str(offset) + " 256\n")
        alloc_mem_idx += 1
        if version :
            output_lines.insert(alloc_mem_idx, ".alloc_mem " + symbol_name + "_version emem global 4 256\n")
            alloc_mem_idx += 1
            output_lines.insert(alloc_mem_idx, init_directive(symbol_name + "_version", 0, str(version)))
            alloc_mem_idx +=1

        output_lines.insert(alloc_mem_idx, "\n")
        alloc_mem_idx += 1

        output_lines.append("#endif\n")

        asm_file_name = output_path + "/" + filename + "_init.uc"
        out_file_handle = open(asm_file_name, "w")
        out_file_handle.writelines(output_lines)
        out_file_handle.close
        print "Generated " + asm_file_name

        c_file_name = output_path + "/" + filename + ".c"
        out_file_handle = open(c_file_name, "w")
        out_file_handle.writelines("")
        out_file_handle.writelines("__export __shared __align256 __emem uint32_t "
            + symbol + "[" + str(offset / 4) + "];\n")

        # out_file_handle.writelines("__export __shared __align256 __emem char "
            # + symbol + "str_tbl[" + str(string_index) + "][" + str(max_csr_str_len) + "] = {\n")

        # for csr in csrs:
            # out_file_handle.writelines("{\"" + csr + "\"},\n")

        # out_file_handle.writelines("};\n")

        print "Generated " + c_file_name
        out_file_handle.close


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='TODO')

    parser.add_argument('input_file',
            help='input file containing xpb, cpp mecsr or me_ind_csr')

    parser.add_argument('--file_name',
            help='output file name')

    parser.add_argument('--sym_prefix',
            help='symbol prefix')

    parser.add_argument('output_path',
            help='output path')

    global arguments
    arguments = parser.parse_args()

    if arguments.sym_prefix :
        prefix = arguments.sym_prefix
    else :
        prefix = "dump"

    if arguments.file_name :
        file_name = arguments.file_name
    else :
        prefix = file_name

    generate(arguments.input_file, arguments.output_path, prefix, file_name)

    sys.exit(0)
