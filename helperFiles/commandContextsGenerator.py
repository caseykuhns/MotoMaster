#Command Context generator

import sys

FILLER_CHAR = "x"

COMMAND_SET = ["G","S","R"] #Maximum of 8 values

SIZE_OF_COMMAND_SET = 1
for x in range (0, len(COMMAND_SET)):
    SIZE_OF_COMMAND_SET = SIZE_OF_COMMAND_SET * 2
    for x in range (0, SIZE_OF_COMMAND_SET):
        sys.stdout.write("#define ")
        for y in xrange(0,len(COMMAND_SET)):
            if((x & (1 << y)) >= 1):
              sys.stdout.write(COMMAND_SET[y])
            else:
              sys.stdout.write(FILLER_CHAR)
        sys.stdout.write(' ')
        print "0x{:02x}".format(x)

print"\r\n"

COMMAND_SET = ["G","S","R","C","M","S","C"] #Maximum of 8 values

SIZE_OF_COMMAND_SET = 1
for x in range (0, len(COMMAND_SET)):
    SIZE_OF_COMMAND_SET = SIZE_OF_COMMAND_SET * 2
    for x in range (0, SIZE_OF_COMMAND_SET):
        sys.stdout.write("#define ")
        for y in xrange(0,len(COMMAND_SET)):
            if((x & (1 << y)) >= 1):
              sys.stdout.write(COMMAND_SET[y])
            else:
              sys.stdout.write(FILLER_CHAR)
        sys.stdout.write(' ')
        print "0x{:02x}".format(x)

print"\r\n"

COMMAND_SET = ["E","L","P"] #Maximum of 8 values

SIZE_OF_COMMAND_SET = 1
for x in range (0, len(COMMAND_SET)):
    SIZE_OF_COMMAND_SET = SIZE_OF_COMMAND_SET * 2
    for x in range (0, SIZE_OF_COMMAND_SET):
        sys.stdout.write("#define ")
        for y in xrange(0,len(COMMAND_SET)):
            if((x & (1 << y)) >= 1):
              sys.stdout.write(COMMAND_SET[y])
            else:
              sys.stdout.write(FILLER_CHAR)
        sys.stdout.write(' ')
        print "0x{:02x}".format(x)
