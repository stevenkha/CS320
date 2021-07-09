import re
import sys

#check for a command line argument
if len(sys.argv) > 1:
    file_name = sys.argv[1]
else:
    print("No input file given")
    sys.exit()

#parse the given input file and split the setnence based on the FANBOYS conjuctions
with open(file_name, 'r') as reader:
    sentence = reader.readline()
    split_sentence = re.split(r', for\s|, and\s|, nor\s|, but\s|, or\s|, yet\s|, so\s', sentence)
#iterate through the list of phrases, number them, and print them out
for i in range(1, len(split_sentence) + 1):
    print(str(i) + ": " + split_sentence[i - 1])