class images:
    def __init__(self,id,iid, shape,ntags,tags):
        self.iid=iid
        self.id=id
        self.shape = shape
        self.ntags = ntags
        self.tags = tags

n=int(input(""))
Imgs = []
v=0
tempiid,tempshape,tempntags,temptags=[],'H',[],[]
count=0
for i in range(0,n):
    line=input("").split(" ")
    if(line[0]!="V"):
        Imgs.append(images(count,i,line[0],line[1],line[2:]))
        count+=1
    else:
        if(v==1):
            tempiid.append(i)
            #temptags=union(line[2:],temptags)
            temptags=list(set(line[2:]) | set(temptags[0]))
            Imgs.append(images(count,tempiid,'H',len(temptags),temptags))
            tempiid,tempshape,tempntags,temptags=[],'H',[],[]
            v=0
            count+=1
        else:
            tempiid.append(i)
            tempntags.append(line[1])
            temptags.append(line[2:])
            v=+1
length=len(Imgs)
max1,maxid=-1,0
slides,next,done=[0],0,False
hash=[]
for i in range (0,length):
    hash.append(0)
for i in range(0,length):
    max1=-1
    for j in range(0,length):
        if(hash[next]==0 and hash[j]==0 and next!=j):
          done=True
          set_a = set(Imgs[next].tags)
          set_b = set(Imgs[j].tags)
          #caluculating in fact
          isn = len(set_a & set_b)
          a = len(set_a - set_b)
          b = len(set_b - set_a)
          min1=min(isn, a, b)
          if(max1<min1):
              max1=min1
              maxid=Imgs[j].id
    if(done):
        hash[next]=1
        slides.append(Imgs[maxid].iid)
        next=maxid
        done=False
print(len(slides))
for slide in slides:
    print(slide)
    '''if(type(slide)==list):
        print(slide[0],slide[1])
    else:
        print (slide)'''