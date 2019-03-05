# this wont work this is backbone for another algorithm yet to be implemented

import sys
import os
import numpy

class images:
    
    def __init__(self,iid, shape,ntags,tags):
        self.iid=iid
        self.shape = shape
        self.ntags = ntags
        self.tags = tags

    def findTag(self, R, C):
        '''
        Check if the slice is within the boundaries of the pizza
        '''
        try:
            assert (R[0] >= 0) and (C[0] >= 0)
            self.pizza[R[0], C[0]] # try if the upper left corner is inside the pizza
            self.pizza[R[1], C[1]] # try if the lower right corner is inside the pizza
            return True
        except:
            return False
    
    


def write_file(imagePositionArray,imageObjectList,filename,):
    '''
    Write the output file
    '''
    with open(filename, 'w') as f:
        f.write('{}\n'.format(len(imagePositionArray)))
        for slic in imagePositionArray:
            f.write(' '.join([str(item) for item in slic]) + '\n')


def read_file(filename):   
    with open(filename, 'r') as f:
        noOfImages = int(f.readline())
        # read no of inputs and create a image list
        listOfImages=[]
        imageArray=[i for i in range(0,noOfImages)]
        for i in range(0,noOfImages):
            #read line
            line=f.readline().split(" ")
            #create image objects and add to list
            listOfImages.append(images(i,line[0],line[1],line[2:]))
            #add H in image front and vertical in image array back by swaping
            
    indexOfHV=[]
           #also adjust in
    return listOfImages,imageArray,indexOfHV



def photoslider():
     
   
    return

def main():
    '''
    Main function
    '''
    
    if len(sys.argv) < 3:
        sys.exit('Syntax: %s <filename> <output>' % sys.argv[0])

   # print('Running on file %s' % sys.argv[1])

    listOfImages,imagePositionArray,indexofHV = read_file(sys.argv[1])
    
    write_file([],[],sys.argv[2])


if __name__ == '__main__':
    main()