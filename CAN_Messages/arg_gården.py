import sys
from os import makedirs, path
import argparse import ArgumentParser
from our_informator import Info

if __name__ == "__main__":
    print(f'OUR NAME = {__name__}, BUT INFO NAME IS {Info.def_magic()}')

    arg_parser = ArgumentParser(
        description="This script read json file and generates c++ class (header and source file)")

    arg_parser.add_argument("-i", "--input", action="store",
                            help="Specify a path to read json file", required=True)

    arg_parser.add_argument("-o", "--Output_dir",
                            action="store", default="./Output.dir")

    arguments = arg_parser.parse_args()

    print(f'input file = {arguments.input}')
    print(f' output dir= {arguments.output_dir}')

    makedirs(arguments.output_dir)
    include_path = path.join(arguments.output_dir, "include", "CAN_Messages")
    makedirs(include_path)
    src_path = path.join(arguments.output_dir, "src")
    makedirs(src_path)
