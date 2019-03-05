#!/usr/bin/python3
import os
import argparse

arg_parser = argparse.ArgumentParser(description='Add source files to qt .pro file')
arg_parser.add_argument('pro_file', help='.pro file target')
arg_parser.add_argument('directories', metavar='Dir', nargs='+', help='Directories containing sources files')
args = arg_parser.parse_args()

source_extension = [".cpp"]
header_extension = [".hpp", ".h"]

HEADER_VAR = "\nHEADERS += \\\n"
SOURCE_VAR = "\nSOURCES += \\\n"

def add_source():
	fileStream = open(args.pro_file, 'a')
	fileStream.write(SOURCE_VAR[:-3] + '\n')
	fileStream.close()

def add_header():
	fileStream = open(args.pro_file, 'a')
	fileStream.write(HEADER_VAR[:-3] + '\n')
	fileStream.close()

for dir in args.directories:
	for f in os.listdir(dir):
		filename, extension = os.path.splitext(f)
		if extension in source_extension:
			SOURCE_VAR += '\t' + os.path.join(dir, f) + ' \\\n'
		elif extension in header_extension:
			HEADER_VAR += '\t' + os.path.join(dir, f) + ' \\\n'
add_source()
add_header()
