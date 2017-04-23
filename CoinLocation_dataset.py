import argparse as ap
import cv2
import numpy as np
import cv2.ml
import os

#from sklearn import linear_model

#from sklearn.externals import joblib
#from scipy.cluster.vq import *
#from sklearn.preprocessing import StandardScaler


def imlist(path):
    """
    The function imlist returns all the names of the files in 
    the directory path supplied as argument to the function.
    """
    return [os.path.join(path, f) for f in os.listdir(path)]


train_path = "classes"
training_names = os.listdir(train_path)

training_names.sort()


# Get all the path to the images and save them in a list
# image_paths and the corresponding label in image_paths
image_paths = []
image_classes = []
class_id = 0
f= open("img_database.txt","w+")
#print training_names

for training_name in training_names:
    dir = os.path.join(train_path, training_name)
    class_path = imlist(dir)
    No_of_Img= len(class_path)
    f.write("%d\r\n"% No_of_Img)
    class_path.sort()
    for path in class_path:
	#print path
	f.write(path+"\n")
	#print path[11]
	if path[11] == "1":
	    f.write("400 365\n")
	if path[11] == "2":    
	    f.write("185 735\n")
	if path[11] == "3":
	    f.write("257 125\n")
	if path[11] == "4":    
	    f.write("600 1400\n")
	if path[11] == "5":
	    f.write("1080 1155\n")
    #print "\n"
    f.write("\n")
    image_paths+=class_path
    image_classes+=[class_id]*len(class_path)
    class_id+=1

#print image_paths 
f.close()




