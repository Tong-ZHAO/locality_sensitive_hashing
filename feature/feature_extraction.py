"""
This file is used to choose randomly train dataset and val dateset 
from Imagenet dataset, and then extract their features. In this 
project, we use the 'fc7' of a pretrained Alexnet, whose dimension is 4096.

If you want to use this file, please change the parameter 'img_path'
in the first function to specify the path to the dataset you want to use.
"""

from keras.models import Sequential, Model

from sklearn.metrics.pairwise import cosine_distances, euclidean_distances
from sklearn.neighbors import DistanceMetric

import Image
import numpy as np
import os 
import argparse
import pickle

# load Alexnet
import model

def compute_random_image_path(class_num, img_num, out_path, out_name) : 
	"""
	a function to create train dataset randomly
	"""

        # the path of imagenet dataset
	img_path = '/home/xt/tong/mopsi/ILSVRC2015/Data/CLS-LOC/train'

	# choose classes
	class_index = np.random.choice(1000, min(class_num, 1000), replace=False)
	class_id = [os.listdir(img_path)[x] for x in class_index]

	# create label file
	fp_label = open(os.path.join(out_path, out_name + '_train_label.txt'), 'w')
	image_path = []
	index = 0

	# choose images from each class
	for i, folder in enumerate(class_id):
		fold_name = os.path.join(img_path, folder)
		img_name = os.listdir(fold_name)
		img_index = np.random.choice(len(img_name), min(img_num, len(img_name)), replace=False)

		for j in img_index:
			image_path.append(os.path.join(fold_name, img_name[j]))
			fp_label.write(os.path.join(fold_name, img_name[j]) + ' ' + str(i) + ' ' + str(index) + '\n')
			index += 1

		if i % 100 == 0:
			print '%d folders ok...' % i

	fp_label.close()
	return image_path

def to_rgb(im):
	"""
	This function is to change a gray image to rgb image
	"""
	# we use weave to do the assignment in C code
	# this only gets compiled on the first call
	import scipy.weave as weave
	w, h = im.shape
	ret = np.empty((w, h, 3), dtype=np.float64)
	code = """
	int impos=0;
	int retpos=0;
	for(int j=0; j<Nim[1]; j++)
	{
		for (int i=0; i<Nim[0]; i++)
		{
			unsigned char d=im[impos++];
			ret[retpos++] = d;
			ret[retpos++] = d;
			ret[retpos++] = d;
		}
	}
	"""
	weave.inline(code, ["im", "ret"])
	return ret

def feature_extraction(image_path, batchsize, out_path, out_name, save_flag):
	"""
	This function is to extract features from alexnet. 
	Be careful that the total number of images must be a multiple of 1000
	"""

	print '\nLoad alexnet KERAS model...'
	# the path of the weights of pretraine Alexnet
	alexnet = model.AlexNet('/home/xt/tong/mopsi/feature/keras/alexnet_weights.h5')

	net = Model(input=alexnet.input, output=alexnet.get_layer('dense_2').output)

	nb_image = len(image_path)
	feature = np.zeros((nb_image, 4096))

	# divide into minibatchs of 1000 images
	index = 0
	nb_batch = nb_image / 1000
	
	# handle with 1000 images each time
	for m in range(nb_batch):
		image_batch = np.zeros((1000, 3, 227, 227))

		print '\n Load %dth 1000 images...' % m
		for i,img_path in enumerate(image_path[m * 1000: m * 1000 + 1000]) :
			im = Image.open(img_path)
			im = im.resize((227,227))
			im = np.array(im).astype(np.float32)
			if im.shape == (227, 227):
				im = to_rgb(im)
			im[:,:,0] -= 123.68
			im[:,:,1] -= 116.779
			im[:,:,2] -= 103.939
			im = im.transpose((2,0,1))
			im = np.expand_dims(im, axis=0)
			image_batch[i] = im

		# extraction of feature
		print "Extract features..."
		feature[m * 1000: m * 1000 + 1000] = net.predict(image_batch, batch_size = batchsize)

	"""
	# check distance between features
	dis = cosine_similarity(feature)
	print dis
	"""

	# save feature matrix to pkl file
	fp_f = open(os.path.join(out_path, out_name + '_feature.pkl'), 'wb')
	pickle.dump(feature, fp_f)
	fp_f.close()

	# write feature to txt
        fp = open(os.path.join(out_path, out_name + '_feature.txt'), "w")
        for item in feature :
                fp.write(' '.join(map(str,list(item))))
                fp.write('\n')
        fp.close()


	# save cosine distance
	if save_flag[0]:
		print '\nSave cosine distance...'
		cos_dis = cosine_distances(feature)
		fp_cos = open(out_path + 'dis/' + out_name + '_cosine_dis.pkl', 'wb')
		pickle.dump(cos_dis, fp_cos)
		fp_cos.close()

	# save euclidean distance
	if save_flag[1]:
		print '\nSave euclidean distance...'
		euc_dis = euclidean_distances(feature)
		fp_euc = open(out_path + 'dis/' + out_name +  '_euclidean_dis.pkl' , 'wb')
                pickle.dump(euc_dis, fp_euc)
                fp_euc.close()

	# save hamming distance
	if save_flag[2]:
		print '\nSave hamming distance...'
		dist = DistanceMetric.get_metric('hamming')
		ham_dis = dist.pairwise(np.where(feature > 0, 1, 0))
		fp_ham = open(out_path + 'dis/' + out_name + '_hamming_dis.pkl' , 'wb')
                pickle.dump(ham_dis, fp_ham)
                fp_ham.close()

	# save jaccard distance
	if save_flag[3]:
		print '\nSave jaccard distance...'
                dist = DistanceMetric.get_metric('jaccard')
                jac_dis = dist.pairwise(feature != 0)
                fp_jac = open(out_path + 'dis/' + out_name + '_jaccard_dis.pkl' , 'wb')
                pickle.dump(jac_dis, fp_jac)
                fp_jac.close()  

	return feature

def create_validation_set(feature, val_size, out_path, out_name):
	"""
	This function is to create val dataset from train dataset
	"""

	print "\nCreate validation dataset..."

	val_index = np.random.choice(feature.shape[0], val_size, replace=False)
	fp_val = open(os.path.join(out_path, out_name + '_val_feature.txt'), 'w')
	fp_val_label = open(os.path.join(out_path, out_name + '_val_index.txt'), 'w')
	
	for i in val_index:
		fp_val.write(' '.join(map(str, list(feature[i]))))
		fp_val.write('\n')
	
	fp_val_label.write(' '.join(map(str, list(val_index))))

	fp_val.close()
	fp_val_label.close()

if __name__ == "__main__":

	parser = argparse.ArgumentParser()

	print '\n******--------- Get feature info with keras alexnet feature  ------*******'
	print '\n feature txt is stored as :'
	print '						feature0 feature1 ... feature4095'
	print '\n label txt is stored as :'
	print '                     img_path classification_label'
	# global setup settings, and checkpoints
	parser.add_argument('-nc', '--class_num', dest='class_number', type=int, help='class number ( <= 1000)')
	parser.add_argument('-ni', '--img_num', dest='image_number', type=int, help='image number')
	parser.add_argument('-p', '--path', dest='output_path', type=str, help='output file path')
	parser.add_argument('-n', '--name', dest='output_name', type=str, help='output file name')
	parser.add_argument('-bs', '--batchsize', dest='batchsize', type=int, help='batch size for alexnet')
	parser.add_argument('-v', '--val_size', dest='val_size', type=int, help='size of validation set')
	parser.add_argument('-dj', '--jaccard', dest='flag_jac', type=int, help='calculate jaccard distance')
	parser.add_argument('-de', '--euclidean', dest='flag_euc', type=int, help='calculate euclidean distance')
	parser.add_argument('-dh', '--hamming', dest='flag_ham', type=int, help='calculate hamming distance')
	parser.add_argument('-dc', '--cosine', dest='flag_cos', type=int, help='calculate cosine distance')

	args = parser.parse_args()
	params = vars(args) # convert to ordinary dict
	
	# create train dataset
	image_path = compute_random_image_path(params['class_number'], params['image_number'], params['output_path'], params['output_name'])
	print '\n-- %d classes, %d images in total' % (params['class_number'], len(image_path))

	# extract features
	print '\n Begin to extract featurs...'
	save_flag = [params['flag_cos'], params['flag_euc'], params['flag_ham'], params['flag_jac']]
	feature = feature_extraction(image_path, params['batchsize'], params['output_path'], params['output_name'], save_flag)

	# create val dataset
	create_validation_set(feature, params['val_size'], params['output_path'], params['output_name'])
