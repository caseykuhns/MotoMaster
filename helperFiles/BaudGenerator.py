#Baud rate generator

#Using the atmega328 data sheet this code was generated to calculate the
#baudrate settings to be pushed into the UBBRn register location.

#Simply add additional baud rates to baudList and CPU frequencies to fCPU_list.
# Try to keep the list in order to maintain readability.

baudList = [
	300,
	1200,
	2400,
	4800,
	9600,
	14400,
	19200,
	28800,
	38400,
	57600,
	76800,
	115200,
	230400,
	250000,
	500000,
	1000000]

#define 1mhz for scale
CPU_SCALE = 1000000

fCPU_List = [
	1.0,
	1.8432,
	2.0,
	3.6864,
	4.0,
	7.3728,
	8.0,
	11.0592,
	14.7456,
	16.0,
	18.4320,
	20.0]


print "#if F_CPU == %d" % (fCPU_List[0] * CPU_SCALE) 
#CPU_FREQUENCY
for x in xrange (0,len(fCPU_List)):
#BAUDRATE
#Skip the first instance
    if x > 0:
    	print "#elif F_CPU == %d" % (fCPU_List[x] * CPU_SCALE)
    for y in xrange (0,len(baudList)):
	f_osc = fCPU_List[x] * CPU_SCALE
	baudVar = baudList[y] * 16
	UBBR = round((f_osc / baudVar), 0) - 1
	#Test to see if it is possible to generate baud
	if f_osc >= baudVar:
		if UBBR < 4095: #Can the UBBR register fit the value
        		print' #define BAUD_%d %d' % (baudList[y], UBBR)
    print" "
print"#endif"
