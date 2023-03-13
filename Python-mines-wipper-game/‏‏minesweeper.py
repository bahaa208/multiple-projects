"""
Student: bhaa asli ****
ID: 208264523
Assignment no. 6
Program: minesweeper.py
"""

import random
""" ***** TRY TO BUILD MINI MINESWEPER GAME!! THESE GAME IS SIMLIAR TOTHE REALE ONE **** """




class mssquare: # FIRST  BUILD THE CLASS FOR EVERY SQUARE IN THE BOARD!!!
    def __init__(self):
        self.__has_mine = False
        self.__hidden = True
        self.__neighbor_mines = 0
    @property
    def has_mine(self):
        return self.__has_mine
    @property
    def hidden(self):
        return self.__hidden
    @property #                   WE HER USEING THE GETTER AND THE SETTER IN THE FUNCTION !
    def neighbor_mines(self):
        return self.__neighbor_mines
    
    @has_mine.setter
    def has_mine(self,Value):
        self.__has_mine = Value
    @hidden.setter
    def hidden(self,Value):
        self.__hidden = Value
    @neighbor_mines.setter
    def neighbor_mines(self,Value):
        self.__neighbor_mines = Value
        
def ThrowBomb(Lst,gun):   #  BUILD FUNCTION THAT DISTRIBUTE THE MINE IN THE SQUARE 
    i=0
    while(i<gun):
        x=random.randint(0, len(Lst)-1)
        y=random.randint(0,len(Lst)-1)
        if Lst[y][x].has_mine!='no!':
            Lst[y][x].has_mine=True
            Lst[y][x].neighbor_mines = '*'
            i+=1   
    for i in range(len(Lst)):
        for j in range(len(Lst)):
            if Lst[i][j].has_mine == False:
                Lst[i][j].neighbor_mines = 0  
                
                
            
    
       
    
def Check(ch): # small function that help us to consider the number
    if ch.has_mine == True:
        return 1
    return 0

def ConsiderNumbers(Lst): # WE HER CONSIDRING THE NUMBER AFTER PUTING THE MINE
    for i in range(len(Lst)):
        for j in range(len(Lst)):
            if Lst[i][j].has_mine == False:
                if i!=(len(Lst)-1) :                
                    Lst[i][j].neighbor_mines+=Check(Lst[i+1][j])                            
                if j!=(len(Lst)-1) :
                    Lst[i][j].neighbor_mines+=Check(Lst[i][j+1])
                if i!=0 :
                    Lst[i][j].neighbor_mines+=Check(Lst[i-1][j])
                if j!=0 :
                    Lst[i][j].neighbor_mines+=Check(Lst[i][j-1])
                if i!= len(Lst)-1  and j!= len(Lst)-1 :
                    Lst[i][j].neighbor_mines+=Check(Lst[i+1][j+1])
                if i!= len(Lst)-1  and j!=0 :
                    Lst[i][j].neighbor_mines+=Check(Lst[i+1][j-1])
                if i!=0 and j!= len(Lst)-1  :
                    Lst[i][j].neighbor_mines+=Check(Lst[i-1][j+1])
                if i!=0 and j!=0 :
                    Lst[i][j].neighbor_mines+=Check(Lst[i-1][j-1])

     
def PrintMatrix(lst,long_line): # HER WE MAKE THE SQUARE OF THE GAME
     for i in range(len(lst)):
         print(" "*3 + str(i+1),end='')
     print()
     print(" "+"+---"*long_line +"+")
     for i in range(len(lst)):
          print(i+1,end='')
          for j in range(len(lst)):
              if  lst[i][j].hidden ==False:                  
                      print("| "+str(lst[i][j].neighbor_mines)+" ",end='')                                    
              if lst[i][j].hidden:                    
                  print("|   ",end='')                    
          print("|")
          print(" "+"+---"*len(lst)+"+")
         
         
def Open_Req(Lst,lst1,y,x,ch=""): # RECORCITION THAT OPEN THE SQUARE AT THE BEGNNING
    if y<0 or x<0 or y>= len(Lst) or x >= len(Lst) or lst1[y][x]==1:         
       return 
    lst1[y][x]=1            
    
    if Lst[y][x].neighbor_mines != 0 and Lst[y][x].has_mine==False:
        Lst[y][x].hidden = False
        return
    
    if(ch!="U"):
        Open_Req(Lst,lst1,y+1,x,"D")
    if(ch!="D"):            
        Open_Req(Lst,lst1,y-1,x,"U")
    if(ch!="R"):
        Open_Req(Lst,lst1,y,x-1,"L")
    if(ch!="L"):
        Open_Req(Lst,lst1,y,x+1,"R")
    if(ch!="DL"):
        Open_Req(Lst,lst1,y+1,x+1,"DR")
    if(ch!="DR"):            
        Open_Req(Lst,lst1,y+1,x-1,"DL")   
    if(ch!="UR"):
        Open_Req(Lst,lst1,y-1,x-1,"UL")
    if(ch!="UL"):
        Open_Req(Lst,lst1,y-1,x+1,"UR")
def main(): #                                     her is the main begnning of the game 
    
    try: # if input wasnt a digit ***
        long_line = int(input(" size  choose anumber between 5 To 9 :")) # size of the squer 
        gun = int(input(f"number of the mine , choose anumber between  ({long_line} , {2*long_line}) ! :")) # quntiti of mine

    except:
         raise Exception(' wrong input \ntry again !')
      
   
        
    square = [[mssquare() for i in range(long_line)] for i in range(long_line)]
    PrintMatrix(square,long_line)
         
    x,y= input(" the beginning is now Enter x y :").split()  # the first wen the game is open  
    x = int(x)
    y = int(y)
    
    if y>long_line or x> long_line:
          raise Exception('try again :(')
    if y<1 or x< 1:
          raise Exception('try again :(')
            
    x-=1
    y-=1
    square[y][x].has_mine = 'no!'# all this ro make shoure that place x,y dosnt have a maine
    square[y][x].hidden= False
    
    if y!=len(square)-1 :   
        square[y+1][x].has_mine = 'no!' # i use the string 'no!' to make shore tha there is no mine 
        square[y+1][x].hidden= False
    if x!=len(square)-1 :   
        square[y][x+1].has_mine = 'no!'
        square[y][x+1].hidden= False
    if y!=0 :   
        square[y-1][x].has_mine = 'no!'
        square[y-1][x].hidden= False
    if x!=0 :   
        square[y][x-1].has_mine ='no!'
        square[y][x-1].hidden= False
    if x!=len(square)-1 and y!=len(square)-1 :
        square[y+1][x+1].has_mine = 'no!'
        square[y+1][x+1].hidden= False
    if x!=len(square)-1 and y!=0  :
        square[y-1][x+1].has_mine = 'no!'
        square[y-1][x+1].hidden= False
    if x!=0 and y!=len(square)-1 :
        square[y+1][x-1].has_mine = 'no!'
        square[y+1][x-1].hidden= False
    if x!=0 and y!=0 :
        square[y-1][x-1].has_mine = 'no!'
        square[y-1][x-1].hidden= False
    lst1 = [[ 0 for t in range(long_line)] for t in range(long_line)] # to out of reqorction
    ThrowBomb(square, gun)
    
    ConsiderNumbers(square)        
    Open_Req(square,lst1,y, x)
    PrintMatrix(square,long_line)
    game = 'begin'
    count = 0
    to_won = 1
    while game !='lose':# her is the beginning of the game !!
         try:    
            y,x=input(" Enter x y:").split()
            y = int(y.strip())-1
            x = int(x.strip())-1
      
            if square[y][x].has_mine==True:
                print(f'\nsorry you lose the game :(\nyou play a {count} time ')
                game = 'lose'
                for i in range(len(square)):
                    for q in range(len(square)):
                        square[i][q].hidden = False
                PrintMatrix(square,long_line)
                print(' you tuch a mine :(\nbetter luck in the next time')
                break
            if square[y][x].has_mine==False or square[y][x].has_mine== 'no!':                
                square[y][x].hidden = False
                PrintMatrix(square,long_line)
            for i in range(len(square)):
                for q in range(len(square)):
                    if square[i][q].has_mine==True :
                            to_won+=1
            if to_won==gun:
                print()
                print()
                
                PrintMatrix(square,long_line)
                
                print(' you won :)\n congratulations ** ')
                break
         except Exception as error: # rais exception wen somthing wroung
                print("somthing wrong with input try again :)")
    
main()
