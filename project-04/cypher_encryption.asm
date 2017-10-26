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
#buffer: .byte 0x0a:100

#encrypt_decrypt: .byte 0x0b:4

toggle_key: .byte 0x0d:4
text_buffer: .byte 0x0a:80
encryption_result: .byte 0x0e:80

buffer1: .space 100


msg : .asciiz "Hello World!" # hardcoded for example
prompt1: .asciiz "Enter 'e' or 'd' to select encrypt or decrypt:\t"
prompt2: .asciiz "Enter addition key:\t"
prompt3: .asciiz "Enter bit toggle key:\t"
prompt4: .asciiz "Enter text to encrypt:\t"
prompt5: .asciiz "Encrypted text:\t"
newline: .asciiz "\n"
debug: .asciiz "DEBUG \n"
debug2: .asciiz "DEBUG2 \n"
debug3: .asciiz "DEBUG3 \n"

############################################################
.text

# Prompt the user for encryption or decryption
	la $a0, prompt1
	li $v0, 4
	syscall

	# read input character
	li $v0, 12			
	syscall
	
	#set s1 with user char input
	la $s0, 0($v0)
	
	#display newline in console
	la $a0, newline
	li $v0, 4
	syscall
	
#Prompt the user for addition key
	la $a0, prompt2
	li $v0, 4
	syscall
	
	# read input integer
	li $v0, 5 
	syscall
	
	#set s1 with user char input
	la $s1, 0($v0)
	
	#display newline in console
	la $a0, newline
	li $v0, 4
	syscall
	
	#DEBUG COMPARATOR
	la $t0, 4
	la $t1, 1
	beq $s1, $t0, ENCRYPT
	beq $s1, $t1, DECRYPT
	
#Prompt the user for the bit toggle key
	
	la $a0, prompt3
	li $v0, 4
	syscall
	
	la $a0, toggle_key 
	la $a1, 4
	li $v0, 8 
	syscall
	
	la $a0, newline
	li $v0, 4
	syscall
		
#Prompt the user for the text to encrypt
	la $a0, prompt4
	li $v0, 4
	syscall
	
	la $a0, text_buffer
	la $a1, 20
	li $v0, 8 
	syscall
	
	#NOW DO FUNCTIONS
	
	#branch to appropriate function
	beq $s0, 'e', ENCRYPT
	beq $s0, 'd', DECRYPT
	
	# debug output
	la $a0, debug3
	li $v0, 4
	syscall
	
	j END
	
#Display encrpyed text result
	la $a0, prompt5
	li $v0, 4
	syscall
	
	# do a call for the result
	#encryption_result


ENCRYPT:
	la $a0, debug
	li $v0, 4
	syscall
	j END

DECRYPT:
	la $a0, debug2
	li $v0, 4
	syscall
	
	j END
	
END:
#terminates program
li $v0, 10
syscall
	
##############################################################################################################################################################################
	
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
	
	
# APPLY ADDITION 
	#la 	$t0, msg	# HARDCODED msg: needs to be user input
	#lb 	$t1, 0 ($t0) 	# load byte # will want in loop to load the next byte, +1 cause byte
	#addi 	$t1, $t1, 4 	# this 4 is coming from user for 'add' so $v0 
	# add $t1, $t1, $v0
	
	# maybe create another space as to not overwrite msg?

# APPLY TOGGLE
# again will be from user input
	#li	$s0, 0x01 	# HARDCOED 0x01: gives value of 0000 0001
	#li	$v0, 3 		# 3 is user input value, probably wont need this line at all, 
	#sllv	$s0, $s0, $v0 	# instead of $v0, just use input 'toggle' value
	
	# exclusive OR for $t1 against $s0
	#xor	$t4, $t1, $s0 	#only using $t4 instead of $t1 to see differences 
	
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
	
			
	
	
	
	
	
