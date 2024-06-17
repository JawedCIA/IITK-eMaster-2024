import pexpect

child = pexpect.spawn('/usr/bin/ssh student@172.27.26.181')
child.expect('student@172.27.26.181\'s password:')
child.sendline('***************************')
child.expect('Enter your group name: ', timeout=50) 
child.sendline("mjawed23")

child.expect('Enter password: ', timeout=50)
child.sendline("*******************************")

child.expect('\r\n\r\n\r\nYou have solved 3 levels so far.\r\nLevel you want to start at: ', timeout=50)
# Note: After clearing level 4 this needs to be changed to "solved 4 levels so far"
child.sendline("4")
child.expect('.*')
#child.sendline("read")
#child.expect('\r\nThe rumbling sound is very loud here. It is coming from \r\n your right side. A cold blast of air hits you sending \r\n shivers up your spine. You look in that direction. \r\n There is a large opening on the right from where the \r\n\tsound and the air is coming from. There is a fair amount\r\n\tof light also coming from that direction (you realize that\r\n\tyou have not lighted a matchstick and still you can see).\r\n\tThere is another door, with a panel nearby, to your left \r\n\twhich is closed. The chamber is rocky and cold. Another \r\n\tblast of air hits you from your right and you shiver again. \r\n\r\n> ', timeout=120)
child.sendline("read")


child.expect('.*')

f = open("plaintexts1-MD-20240606.txt", 'r')
f1= open("ciphertexts1-MD--20240606.txt",'w')

for line in f.readlines():
	child.sendline(line)
	print(child.before)
	f1.writelines(str(child.before)[48:64]+"\n")
	child.expect("Slowly, a new text starts*")
	child.sendline("c")
	child.expect('The text in the screen vanishes!')

data = child.read()
print(data)
child.close()
print(child.before, child.after)

f.close()
f1.close()


