# imm : str
def immToBin(imm, numOfBits=4):
	immBin = format(int(imm), "0"+str(numOfBits)+"b") 
	return immBin

def regToBin(reg):
	# $t0 to $13: 0000 to 1101
	if reg[:2] == "$t":
		return format(int(reg[2:]), "04b")
	elif reg == "$acc":
		return "1110"
	elif reg == "$cout":
		return "1111"
	else:
		print("ERROR: invalid register", reg)
		return ""
	

print('Running Divvy Assembler:')

fileName = "./assembly.txt"
w_file = open("Machine3.txt", "w")

assembly = []
with open(fileName, "r") as f:
	assembly = f.readlines()
assemblyCopy = assembly[:]
assembly = []

# getting rid of comments and blank lines
for line in assemblyCopy: 
	splited = line.split()
	if len(splited) and splited[0][0] != "#":
		assembly.append(line)

for line in assembly:

	str_array = line.split()
	instruction = str_array[0]
	flag = str_array[1]

	opcode = ""
	fiveBits = "00000"

	if instruction == "move":
		opcode = "0000"
		imm = str_array[1]
		immBin = immToBin(imm, 5)
		fiveBits = immBin
	elif instruction in ["add", "sor", "sand", "sgt", "seq"] :
		index = ["add", "sor", "sand", "sgt", "seq"].index(instruction)
		opcode = ["0001", "0010", "0011", "0100", "0101"][index]
		if flag == "0":
			imm = str_array[2]
			immBin = immToBin(imm)
			fiveBits = flag + immBin
		else:
			regAddr = str_array[2]
			regBin = regToBin(regAddr)
			fiveBits = flag + regBin
	elif instruction == "shift":
		opcode = "0110"
		imm = str_array[2]
		immBin = immToBin(imm)
		fiveBits = flag + immBin
	elif instruction in ["load", "store"]:
		index = ["load", "store"].index(instruction)
		opcode = ["0111", "1000"][index]
		regAddr = str_array[2]
		regBin = regToBin(regAddr)
		fiveBits = flag + regBin
	elif instruction in ["be", "bne"]:
		label = str_array[1]
		index =  ["be", "bne"].index(instruction)
		opcode = ["1001", "1010"][index]
		
		# store the value of $acc into $t12
		w_file.write("1000"+"0"+regToBin("$t12")+"\n")
		# store the MSB of label LUT index into acc
		w_file.write("0000"+label+"_MSB"+"\n")
		# shift-left the value in acc
		w_file.write("0110"+"0"+immToBin("4")+"\n")
		# or the LSB of label LUT index with the value in acc
		w_file.write("0010"+"0"+label+"_LSB\n")
		# store the value of acc into $t13
		w_file.write("1000"+"0"+regToBin("$t13")+"\n")
		# restore acc
		w_file.write("0111"+"0"+regToBin("$t12")+"\n")
		
		fiveBits = "0"+regToBin("$t13")
	elif instruction == "neg":
		opcode = "1011"
	elif instruction == "halt":
		opcode = "1100"
	else:
		print("instruction is invalid", instruction)
		exit()
		
	w_file.write(opcode + fiveBits + "\t#" + line)

# TODO create a file for LUT

w_file.close()

