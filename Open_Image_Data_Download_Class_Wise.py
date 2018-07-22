# -*- coding: utf-8 -*-
"""
Created on Sat Jul 21 17:16:14 2018

@author: Madhav
"""

import os
import urllib
import sys
import csv
import pandas as pd
import time
download_path = 'Open_Image_Download_Datasets/'
chunksize = 100000

def word_in (word, phrase):
    return word in phrase.lower().split()

def down(img_url,class_name,class_count,ids,f1):
    try:
        req = urllib.request.Request(img_url)
        raw_img = urllib.request.urlopen(req).read()
        f = open(download_path+class_name+"/"+str(class_count)+".jpg", "wb")
        f.write(raw_img)
        f.close
        f1.write(class_count," ",ids," ",img_url)
        class_count= class_count+1
        return class_count
    except:
        return class_count

def class_id(class_name):
    cll=[]
    idd = []
    with open('class-descriptions.csv',encoding ='utf8') as csvfile:
        names = csv.reader(csvfile, delimiter=',', quotechar='|')
        for name in names:
            for classes in class_name:
                if(word_in(classes, name[1])):
                #if(classes==name[1]):
                    cll.append(name[1])
                    idd.append(name[0])
    return cll,idd

def image_id(class_id11):
    idss = []
    for chunk in pd.read_csv('train-annotations-human-imagelabels.csv', chunksize=chunksize, low_memory=False):
        for ind, row in chunk.iterrows():
            if (class_id11 == row[2] and row[3]==1):
                idss.append(row[0])
    print(idss)
    return idss
            
def image_down(idss,cl1,f1):
    count1 = 0
    for chunk in pd.read_csv('train-images-with-labels-with-rotation.csv', chunksize=chunksize, low_memory=False):
        for ind, row in chunk.iterrows():
            for ids in idss:
                if (ids == row[0]):
                    count1 = down(row[2],cl1,count1,ids,f1)
                    print("Count",count1)
                
    
            
        
    
if __name__ == '__main__':
    print(time.time())
    class_name = sys.argv[1]
    class_count =0
    classes = ['helmet']
    #classes = ['cap','shirt','helmet','beard','weapon','gun']
    class_name1,idd_1 = class_id(classes)
    print(class_name1)
    print(idd_1)
    for idx,cl1 in enumerate(class_name1):
        if not os.path.exists(download_path+cl1):
            os.makedirs(download_path+cl1)
        f1 = open(download_path+cl1+"id.txt","a")
        idss = image_id(idd_1[idx])
        image_down(idss,cl1,f1)
        f1.close()
        print("Class:",cl1,"Time:",time.time())