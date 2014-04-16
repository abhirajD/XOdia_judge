#! /usr/bin/env python

import sys, threading, time, os, resource
from subprocess import Popen, PIPE, call

argtemp=sys.argv;
					
name1=argtemp[1];
name2=argtemp[2];

tx=name1.split(".");	
ty=name2.split(".");

atx=tx[0];
aty=ty[0];

log_file=atx+"."+aty+".log";

bot=1;
bot1DQ=0
bot2DQ=0
count=0;
exit=0;
log=open(log_file,"w+")

f = open("grid.txt","r+")
f.seek(665);

for i in range(0,324):
	f.write(".");
f.close();

#LIMIT RESOURCES TO CHILD.
soft , hard = resource.getrlimit(resource.RLIMIT_STACK)
new_soft = 1024*1024*1024;												#LIMIT=1GB
resource.setrlimit(resource.RLIMIT_STACK,(new_soft,hard))

try:
	pass
except ValueError:
	ret_flag = 5
	print ret_flag
	quit()

while exit == 0:

	N = 18
	f = open("grid.txt","r+")
	xoboard = []
	for i in range(0,N):
		temp = [0 for j in range(0,N)] # A row of a 2D array
		xoboard.append(temp)	       # Putting temp(which is an array itself) inside an array, thus making an array of arrays
	# wboard	
	wboard = []
	for i in range(0,N):
		temp = [0 for j in range(0,N)]
		wboard.append(temp)
	#print xoboard[16][16]
	# Reading the file for the grid
	f.seek(0);
	s = f.read()
	f.close()
	# Splitting v into the array - values. We would extract the grid and sudoku boards from values
	# v is temporary, to avoid modifying s
	v = s
	
	values = v.split()

	# valuesIndex would run through the array values (There might be a more elegant way to put values into a 2D array from a single array)
	valuesIndex = 0 

	for i in range(0,N):
		for j in range(0,N):
			wboard[i][j] = int(values[valuesIndex])
			valuesIndex += 1

	string = values[valuesIndex]
	valuesIndex=0
	for i in range(0,N):
		for j in range(0,N):
			xoboard[i][j]=string[valuesIndex]
			valuesIndex += 1
			
			
	# The file has been read and put into xoboard and wboard, the judge can now make changes on the 2D array directly

	if (bot)==1:
		call(["g++",str(name1)]);
	elif (bot)==2:
		call(["g++",str(name2)])
	term=0

	#Timeopt function
	def timeout( p ):
		if p.poll() == None:
			try:
				p.kill()
				print ':TLE: Process taking too long to complete--terminating'
				chk=1;
				term=1
			except:
				pass

	def execute():
		#PIPING with executiable of Bot.c i.e a.out 
		proc = Popen("./a.out",	 stdin=PIPE,stdout=PIPE,stderr=PIPE ,shell= True);
		# Making the 2D 18x18 xoboard and wboard
		# Sending the grid to the bot

		t = threading.Timer( 2.0, timeout, [proc] )
		t.start();
		ret = proc.communicate(s)

		t.cancel();
		try:
			proc.kill();
		except OSError:
			pass

		return ret

	ret = execute()

	#ret=str(ret)
	move = ret[0]
	moves = move.split()
	x = int(moves[0])
	y = int(moves[1])
	# print x
	# print y
	chk=0

	#Check1: Output format and Storing in var x and y
	# if (len(ret)==11):
	# 	x=int(ret[2:3])
	# 	y=int(ret[4:5])
	# 	print x
	# 	print y
	# 	print "Valid1"
	# else:
	# 	print "Invalid"

	# 	chk=1


	#Check2: Coordinates inside grid
	temp=0
	if x<N and y<N and x>=0 and y>=0:
		#print 'Valid1'
		temp=1
	else:
		#print "Invalid1"
		chk=1
		if bot==1:
			bot1DQ=1
		elif bot==2:
			bot2DQ=1

	# if x in range(0,N):
	# 	x=x-1
	# 	print x
	# if y in range(0,N):
	# 	y=y-1
	# 	print y

	#Delete "a.out"
	os.remove("a.out")

	#Check3: No overlapping
	temp=0
	if x < N and y<N and x>=0 and y>=0:
		if xoboard[x][y] == 'X' or xoboard[x][y] == 'O':
			#print "Invalid2"
			chk=1
			if bot==1:
				bot1DQ=1
			elif bot==2:
				bot2DQ=1
	else:
		#print "Valid2"
		temp=1

	if chk == 0:
		print "Validation Successful"
		if (bot) == 1:
			xoboard[x][y]="X"
			log.write('X:'+str(x).zfill(2)+" "+str(y).zfill(2)+'\n')
			if x-1>=0 and y-1>=0 and xoboard[x-1][y-1] !='X' and xoboard[x-1][y-1]!='O': xoboard[x-1][y-1]="x" 
			if x-1>=0 and xoboard[x-1][y] !='X' and xoboard[x-1][y]!='O':  xoboard[x-1][y]="x"
			if x+1<N and y-1>=0 and xoboard[x+1][y-1] !='X' and xoboard[x+1][y-1]!='O': xoboard[x+1][y-1]="x"
			if x+1<N and xoboard[x+1][y] !='X' and xoboard[x+1][y]!='O': xoboard[x+1][y]="x"
			if x+1<N and y+1<N and xoboard[x+1][y+1] !='X' and xoboard[x+1][y+1]!='O': xoboard[x+1][y+1]="x"
			if y+1<N and xoboard[x][y+1] !='X' and xoboard[x][y+1]!='O': xoboard[x][y+1]="x"
			if x-1>=0 and y+1<N and xoboard[x-1][y+1] !='X' and xoboard[x-1][y+1]!='O': xoboard[x-1][y+1]="x"
			if y-1>=0 and xoboard[x][y-1] !='X' and xoboard[x][y-1]!='O': xoboard[x][y-1]="x"
			for i in range(0,N):	
				for j in range(0,N):
					if xoboard[i][j]=='o':
						xoboard[i][j]='O'


		elif (bot) == 2:
			xoboard[x][y]="O"
			log.write('O:'+str(x).zfill(2)+" "+str(y).zfill(2)+'\n')
			if x-1>=0 and y-1>=0 and xoboard[x-1][y-1] !='X' and xoboard[x-1][y-1]!='O': xoboard[x-1][y-1]="o" 
			if x-1>=0 and xoboard[x-1][y] !='X' and xoboard[x-1][y]!='O': xoboard[x-1][y]="o"
			if x+1<N and y-1>=0 and xoboard[x+1][y-1] !='X' and xoboard[x+1][y-1]!='O': xoboard[x+1][y-1]="o"
			if x+1<N and xoboard[x+1][y] !='X' and xoboard[x+1][y]!='O': xoboard[x+1][y]="o"
			if x+1<N and y+1<N and xoboard[x+1][y+1] !='X' and xoboard[x+1][y+1]!='O': xoboard[x+1][y+1]="o"
			if y+1<N and xoboard[x][y+1] !='X' and xoboard[x][y+1]!='O': xoboard[x][y+1]="o"
			if x-1>=0 and y+1<N and xoboard[x-1][y+1] !='X' and xoboard[x-1][y+1]!='O': xoboard[x-1][y+1]="o"
			if y-1>=0 and xoboard[x][y-1] !='X' and xoboard[x][y-1]!='O': xoboard[x][y-1]="o"
			for i in range(0,N):
				for j in range(0,N):
					if xoboard[i][j]=='x':
						xoboard[i][j]='X'
	elif chk==1:
		if bot==1 and bot1DQ==0:
			log.write('X:'+str(x).zfill(2)+" "+str(y).zfill(2)+'\n')
		elif bot==0 and bot2DQ==0:
			log.write('O:'+str(x).zfill(2)+" "+str(y).zfill(2)+'\n')

	#writing to grid.txt

	#f.seek(0);

	f = open("grid.txt","w+")
	temp=0
	for i in range(0,N):
		for j in range(0,N):
			f.write(str(wboard[i][j]))
			if i==17 and j==17:
				temp=1
			else:
				f.write(' ')
		f.write('\n')

	for i in range(0,N):
		for j in range(0,N):
			f.write(str(xoboard[i][j]))
		#f.write('\n')

	f.close()
	count= count + 1;
	if bot==1: bot=2
	else: bot=1

	#Check: Grid is complete or not
	f=0
	if  chk==1 or term==1:
		exit=1
	else:
		for i in range(0,N):
			for j in range(0,N):
				if xoboard[i][j]=='.' or xoboard[i][j]=='x' or xoboard[i][j]=='o':
					f=1
					break
			if f==1:
				break
		if f==0:
			exit=1
		else:
			exit=0
	
	#raw_input("Press Enter to continue")
	#time.sleep(2)


# Counting the amount of conquer
Xcount=0
Ocount=0
for i in range(0,N):
	for j in range(0,N):
		if xoboard[i][j]=='X':
			Xcount += wboard[i][j]

for i in range(0,N):
	for j in range(0,N):
		if xoboard[i][j]=='O':
			Ocount += wboard[i][j]

log.write("*Game Over");
if bot1DQ==1:
	Xcount=0
elif bot2DQ==1:
	Ocount=0
log.write('\nX:'+str(Xcount).zfill(4)+'\nO:'+str(Ocount).zfill(4))

#print " X conquered: ",Xcount
#print " O conquered: ",Ocount


f = open("grid.txt","r+")
f.seek(665);

for i in range(0,324):
	f.write(".");
