#-*- coding: utf-8 -*-
import numpy as np
import os
import json
from sys import argv


if __name__ == "__main__":
	if len(argv) != 3:
		print "Usage:python test_file predict_file"
		os._exit(1)
	category = [u"公文",u"论文",u"简历",u"合同"]
	dim = 4
	f = open(argv[1])
	predict = open(argv[2]).readlines()
	test_json = json.load(f)
	matrix = np.zeros((dim,dim))
	total_acc = 0
	for i,each in enumerate(test_json):
		test_label = -1
		for j in range(dim):
			if category[j] == each['category']:
				test_label = j
				break
		if test_label == -1:
			print "Wrong Category in " + arv[1]
		predict_label = int(predict[i])
		matrix[test_label][predict_label] += 1
		if test_label == predict_label:
			total_acc += 1
	total_acc = float(total_acc)/len(predict)

	total_precision = 0
	total_recall = 0
	for i in range(matrix.shape[0]):
		row = sum(matrix[i])
		column = sum(matrix[r][i] for r in range(matrix.shape[0]))
		precision = float(matrix[i][i]/float(column))
		recall = float(matrix[i][i]/float(row))
		total_precision += precision
		total_recall += recall
		print category[i] + ' precision:%f' % precision
		print category[i] + ' recall%f' % recall
		print category[i] + ' f1%f' % (precision*recall*2/(precision+recall))

	print "total_acc:%f" % total_acc
	print "macro_average_precision:%f" % (total_precision/dim)
	print "macro_average_recall%f" % (total_recall/dim)
	print "macro_average_f1%f" % ((total_precision*total_recall)*2/((total_precision+total_recall)*dim))
