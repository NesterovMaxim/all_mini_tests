import os
import numpy as np
import matplotlib.pyplot as plt

hist = {};

def file_stats(fname):
    with open(fname) as f:
	cnt = 0
        for line in f:
	    cnt += 1
	    key = len(line)
	    if key > 200:
		print("%s:%d ! %d" % (fname, cnt, key))
	    if key in hist:
		hist[key] += 1
	    else:
		hist[key] = 1
    #return i + 1

def process_dir(dir):
	for root, dirs, files in os.walk(dir):
	    for file in files:
	        if file.endswith(".cpp") or file.endswith(".inl") or file.endswith(".h"):
		     file_stats(os.path.join(root, file))


process_dir('./common/')
process_dir('./src/')
process_dir('./lib/')


def chart(d):
	width = 1.0     # gives histogram aspect to the bar diagram

	myDictionary = dict((k, v) for k, v in d.items() if k >= 100 and k < 200)
	plt.bar(myDictionary.keys(), myDictionary.values(), width, color='g')
	plt.show()

	myDictionary = dict((k, v) for k, v in d.items() if k >= 200)
	plt.bar(myDictionary.keys(), myDictionary.values(), width, color='g')
	plt.show()



chart(hist)