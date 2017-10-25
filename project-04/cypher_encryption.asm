#cypher encryption

# ask user for string input
# ask for add value
# ask for toggle value
# print out result

#Hello world!
# 'H' = 0x48   0100 1000

# user enters 4 (add)
# " " a 3 
# RESTRICT THE ADD AND THE TOGGLE INPUTS, NOT THE STRING INPUT 

# 0100 1100 # is the encrypted result for 'H'


# 0100 1100
# 0000 1000 #XOR
# ---------------
# 0100 0100 #result, which was the original 



# ---------------------------------------------
.data

#use help syscall to get user input 



# give me 100 of 0x0a
buffer: .byte 0x0a:100
buffer1: .space 100


msg : .asciiz "Hello World!" # hardcoded for example
prompt1: .asciiz "Enter your string \n"

############################################################
.text

# Prompt the user for the string
#la $a0, prompt1
#li $v0, 4
#syscall


# Enter user input into memory called "buffer"
	# RECIEVE INPUT VIA CONSOLE SYSCALL
	# (Eventually place this in a function)

	# give address of input buffer
	#la $a0, buffer
	# set size of string length we will read(?) 
	#la $a1, 10
	# read input string
	#li $v0, 8 
	# executes the above call
	#syscall
	
	
# FOR HARDCODED msg
	la 	$t0, msg
	lb 	$t1, 0 ($t0) 	# load byte # will want in loop to load the next byte, +1 cause byte
	addi 	$t1, $t1, 4 	# this 4 is coming from user for 'add' so $v0 
	# add $t1, $t1, $v0
	
	# maybe create another space as to not overwrite msg?

# APPLY TOGGLE
# again will be from user input
	li	$s0, 0x01 	# gives value of 0000 0001
	li	$v0, 3 		# 3 is user input value, probably wont need this line at all, 
	sllv	$s0, $s0, $v0 	# instead of $v0, just use input 'toggle' value
	
	# exclusive OR for $t1 against $s0
	xor	$t4, $t1, $s0 	#only using $t4 instead of $t1 to see differences 
	
	#0100 1000 original
	#0100 1100 encrypted from add 4
	#0000 1000 XOR value
	#----------
	#0100 0100 XOR result (encrypted)
	
	
	# DECRYPT
	#la 	$t5, buffer
	#sb 	$t4, 0($t5)
	# Use toggle bit OXOR again
	# subtract 'add' value
	
			
	
	
	
	
	