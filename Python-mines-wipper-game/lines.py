"""
Student: bhaa asli
ID: 208264523
Assignment no. 6
Program: minesweeper.py
"""

""" build aprogram that can caluclation apoint in axsis x y and caluclation
 the intersection of to line and move the equation to file """ 
class point: #     the class in the beginning to build the point 
    def __init__(self,x,y):
        if  isinstance(x,int)==False and isinstance(x,float)==False :   
            raise Exception('something wrong x must be adigit !')
        self.__x = x
        if  isinstance(y,int)==False and isinstance(y,float)==False :   
            raise Exception('something wrong y must be adigit !')
        self.__y = y
        
    def __str__(self): # method to print the equation in the file  
        return f'({self.__x:01},{self.__y:g})'
    @property
    def x(self):
        return self.__x
    @x.setter 
    def x(self,new):
        if  isinstance(new,int)==False and isinstance(new,float)==False :   
            raise Exception('something wrong x must be adigit !')
        self.__x = new
    @property # her we use the getter and the setter to contrul with point for change them wen we want !
    def y(self):
        return self.__y
    @y.setter 
    def y(self,new):       
        if  isinstance(new,int)==False and isinstance(new,float)==False :   
            raise Exception('something wrong y must be adigit !')
        self.__y = new
class line: # another class that build the line using two point 
   
    def __init__(self,p1,p2): #the builder that build the line 
        if isinstance(p1,point)== False or isinstance(p2,point) == False:
             raise Exception("somthing wrong check the point")
        self.__p1 = p1
        self.__p2 = p2
        self.__p1x = p1.x
        self.__p1y = p1.y
        self.__p2x = p2.x
        self.__p2y = p2.y
        
      
    
    @property
    def p1(self):
        return self.__p1
    @p1.setter   # using some getter and setter to more control 
    def p1(self,new):
        if isinstance(new,point)==False :   
            raise Exception('something wrong  with point !')
       
        self.__p1 = new
       
    @property
    def p2(self):
        return self.__p2
    @p2.setter 
    def p2(self,new):       
        if isinstance(new,point)==False :   
            raise Exception('something wrong  with point !')
        self.__p2 = new
    
    def is_virtical(self):
        return self.__p1x == self.__p2x
    
    def slope(self):
        if self.__p1x == self.__p2x:
            return None
        else:
            return (float(self.__p1y)-float(self.__p2y))/(float(self.__p1x)-float(self.__p2x))
            
       
        
        
    def y_intersect(self): # this function returned the intersection with axis y
        if self.__p1x == self.__p2x:
            return None
        vv = float(self.__p1y)+float(self.slope())*-1*float(self.__p1x)
       
        return f'(0,{vv})'
        
    def __str__(self):
         if  self.__p1x == self.__p2x:     
             
             return f' x =  {self.__p1x}'
         if self.slope() == '0':
             return f' y = {self.__p1y}'
         else:
             m = -self.slope()*self.__p1x+self.__p1y
             return ' y  = {0:.2f}*x + {1:.2f}'.format(self.slope(),m)
             
         
    def parallel(self, other):
        if self.slope() == other.slope():
            return True
        else:
            return False
    def equals(self, other):
        if self.slope() == other.slope() and self.y_intersect() == other.y_intersect():
            return True
        else:
            return False
    def intersection(self,other): # intersection with two line
        
        if self.slope() == other.slope() and self.y_intersect() == other.y_intersect():
            return None
        if self.slope() == None or other.slope() == None:
            return None
        if (-1*self.slope()+other.slope())!=0:
             x = (self.__p1y +-1*other.__p1y +(self.slope()*-self.__p1x) +(other.slope()*other.__p1x))/(-1*self.slope()+other.slope())
             y = self.__p1y + (self.slope()*-self.__p1x) + self.slope()*x
             return f'({x:.2f},{y:.2f})'
        
file = open('input2.txt','r')
data = file.read().split('\n')
file.close()
file = open('output2.txt','w')
data = [i.split() for i in data]
lis = [] # list for the all the point we take from the file 

for q in range(1,len(data)+1):
    
    if len(data[q-1]) !=4:
        
        file.write('Error')
    else:
        
          p1 = point(float(data[q-1][0]),float(data[q-1][1]))
          p2 = point(float(data[q-1][2]),float(data[q-1][3])) # calculat every two point 
          li = line(p1, p2)
          lis.append(li)
for s in range(len(lis)):
    file.write(f'line {s+1} :'+str(lis[s])+'\n')
    for a in range(len(lis)):
        if lis[a] != lis[s]:
            if lis[s].equals(lis[a]):
                if s+1>a+1:
                      file.write(f'line {s+1} is equals to line {a+1}\n')
            if lis[s].parallel(lis[a]): 
                  if s+1>a+1:
                      file.write(f'line {s+1} is parallel to line {a+1}\n')
                
            if lis[s].intersection(lis[a]) != None:
                if s+1>a+1:
                    file.write(f'line {s+1} with line {a+1} : {lis[s].intersection(lis[a])}\n')
            
                    
    file.write('\n')
file.close() # done   !!
            
    
   
                        
           
