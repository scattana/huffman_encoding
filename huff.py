#!/usr/bin/env python3

import os
import string

FILES = {"pride.ascii", "frank.ascii", "heart.ascii", "2city.ascii", "alice.ascii"}

# format markdown table (header)
print("\n\n|          FILE         |    OLD SIZE   |    NEW SIZE   |     RATIO   |")
print("|-----------------------|---------------|---------------|-------------|")

# for each file in FILES, parse and output:
for file in FILES:
	comp_bitcount = 0
	orig_bitcount = 0
	# process file
	comm = "./huff -f tsv " + file
	a = os.popen(comm).read()
	
	# now have each line being read one by one!
	linelist = a.splitlines();
	fulllist = [line.split("\t") for line in linelist]
	
	# compute new bit count
	for count in [(len(big[1]))*(int(big[2])) for big in fulllist]:
		comp_bitcount = comp_bitcount + count

	# get old bit count
	orig_bitcount = (os.path.getsize(file))*8
	
	# compute compression ratio
	ratio = round((comp_bitcount/orig_bitcount)*100,2)	# as a percent
	
	# print each row to table
	print("|\t"+file+"\t|\t"+str(orig_bitcount)+"\t|\t"+str(comp_bitcount)+"\t|\t"+"{0:.2f}".format(ratio)+"%"+"|")
	
	#print(str(ratio) + "%")
	
# print blank lines at end
print("\n\n")	
