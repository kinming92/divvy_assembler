# imm : str
def immToBin(imm, numOfBits=4):
    immBin = format(int(imm), "0"+str(numOfBits)+"b") 
    return immBin

def regToBin(reg):
    # $t0 to $13: 0000 to 1101
    if reg[:2] == "$t":
        number = int(reg[2:])
        if number > 13:
            exit("ERROR: invalid register"+reg)
        return format(number, "04b")
    elif reg == "$acc":
        return "1110"
    elif reg == "$cout":
        return "1111"
    else:
        exit("ERROR: invalid register"+reg)

import sys

print('Running Divvy Assembler:')

fileName = "./assembly.txt"
wFileName = "machine_code.txt"

if len(sys.argv) == 2:
    fileName = sys.argv[1]
elif len(sys.argv) == 3:
    fileName = sys.argv[1]
    wFileName = sys.argv[2]
else:
    exit("The number of argument is incorrect\n"+
        "Usage: python assembler.py [assemblyFileName.txt] (outputFileName.txt)")

assembly = []
# get assembly without comments or blank lines
with open(fileName, "r") as f:
    for line in f.readlines():
        splited = line.split()
        if len(splited) and splited[0][0] != "#":
            assembly.append(line)

labels = []
labelAddrs = []
writeCount = 0
machineCodes = []
for i, line in enumerate(assembly):

    strArray = line.split()
    instruction = strArray[0]
    flag = strArray[1] if len(strArray) > 1 else 0

    opcode = ""
    fiveBits = "00000"

    if instruction == "move":
        opcode = "0000"
        imm = strArray[1]
        immBin = immToBin(imm, 5)
        fiveBits = immBin
    elif instruction in ["add", "sor", "sand", "sgt", "seq"] :
        index = ["add", "sor", "sand", "sgt", "seq"].index(instruction)
        opcode = ["0001", "0010", "0011", "0100", "0101"][index]
        if flag == "0":
            imm = strArray[2]
            immBin = immToBin(imm)
            fiveBits = flag + immBin
        else:
            regAddr = strArray[2]
            regBin = regToBin(regAddr)
            fiveBits = flag + regBin
    elif instruction == "shift":
        opcode = "0110"
        imm = strArray[2]
        immBin = immToBin(imm)
        fiveBits = flag + immBin
    elif instruction in ["load", "store"]:
        index = ["load", "store"].index(instruction)
        opcode = ["0111", "1000"][index]
        regAddr = strArray[2]
        regBin = regToBin(regAddr)
        fiveBits = flag + regBin
    elif instruction in ["be", "bne"]:
        label = strArray[1]
        index =  ["be", "bne"].index(instruction)
        opcode = ["1001", "1010"][index]

        # store the value of $acc into $t12
        machineCodes.append("1000"+"0"+regToBin("$t12")+"\n")
        # store the MSB of label LUT index into acc
        machineCodes.append("00000 "+label+" MSB"+"\n")
        # shift-left the value in acc
        machineCodes.append("0110"+"0"+immToBin("4")+"\n")
        # or the LSB of label LUT index with the value in acc
        machineCodes.append("0010"+"0 "+label+" LSB\n")
        # store the value of acc into $t13
        machineCodes.append("1000"+"0"+regToBin("$t13")+"\n")
        # restore acc
        machineCodes.append("0111"+"0"+regToBin("$t12")+"\n")
        writeCount += 6

        fiveBits = "0"+regToBin("$t13")
    elif instruction == "neg":
        opcode = "1011"
    elif instruction == "halt":
        opcode = "1100"
    # Label found
    elif instruction[-1] == ":":
        labels.append(instruction[:-1])
        labelAddrs.append(writeCount)
        # don't wanna write any machine code for label
        continue
    else:
        exit("invalid instruction at "+str(i+1)+" : "+instruction)

    machineCodes.append(opcode + fiveBits + "\t#" + line)
    writeCount += 1


finalMachineCodes = []
for line in machineCodes:
    lineToAppend = line
    if "MSB" in line or "LSB" in line:
        splited = line.split()
        frontMachineCode = splited[0]
        label = splited[1]
        if "MSB" in line:
            lineToAppend = frontMachineCode + format(labels.index(label), "08b")[:4] + "\n"

        elif "LSB" in line:
            lineToAppend = frontMachineCode + format(labels.index(label), "08b")[4:] + "\n"
    finalMachineCodes.append(lineToAppend)

with open(wFileName, "w") as wFile:
    for line in finalMachineCodes:
        wFile.write(line)

# TODO create a file for LUT
lutFileName = "lut.txt"
with open(lutFileName, "w") as lutFile:
    for i, label in enumerate(labels):
        addr = labelAddrs[i]
        lutFile.write(format(addr, "016b")+"\n")



print('Ran Divvy Assembler:')
