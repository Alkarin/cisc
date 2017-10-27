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
#text_buffer: .byte 0x0a:80
encryption_result: .byte 0x10:80
text_buffer: .byte 0x0e:100

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

add_value: .word 0

# SAVED REGISTERS
# s0	'e' or 'd'
# s1	Addition key
# s2	Toggle key
# s3	Addition increment count
# s4	Other increment count
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
	
	#set s1 with user int input
	la $s1, 0($v0)
	
	#display newline in console
	la $a0, newline
	li $v0, 4
	syscall
	
#Prompt the user for the bit toggle key
	
	la $a0, prompt3
	li $v0, 4
	syscall
	
	# read input integer
	li $v0, 5 
	syscall
	
	#set s2 with user int input
	la $s2, 0($v0)
	
	#display newline in console
	la $a0, newline
	li $v0, 4
	syscall
		
#Prompt the user for the text to encrypt
	la $a0, prompt4
	li $v0, 4
	syscall
	
	# getting text from user
	la $a0, text_buffer
	la $a1, 20
	li $v0, 8 
	syscall
	
	#NOW DO FUNCTIONS
	
	#branch to appropriate function
	beq $s0, 'e', ENCRYPT
	beq $s0, 'd', DECRYPT
	
	#precautionary end program
	j END
	
#Display encrpyed text result
RESULT:
	la $a0, prompt5
	li $v0, 4
	syscall
	
	# display encryped
	li $v0, 4
	la $a0, text_buffer
	syscall
	
	#display newline in console
	la $a0, newline
	li $v0, 4
	syscall
	
	j END

ENCRYPT:

    	la $s5, text_buffer     #s0 text iterating through
    	la $t1, 0($s1)     	#s1 add value
    	li $t0, 0       	#t0 iterator count: 0
	
	# call function to encrypt each char
	jal encryptCharLoop
	
	# display result
	j RESULT

encryptCharLoop:

   	add 	$s6, $s5, $t0		# $s6 = text_buffer[i]
    	lb 	$s7, 0($s6)     	# Loading char to shift into $s7
    	beq 	$s7, $zero, exitLoop	# Breaking the loop if we've reached the end: http://stackoverflow.com/questions/12739463/how-to-iterate-a-string-in-mips-assembly
    	add 	$s7, $s7, $t1   	# Shift char by add value
    	
    	#APPLY_TOGGLE
    	# set bit toggle value from user input
	la	$t4, 0x01 		# HARDCODED 0x01: gives value of 0000 0001
	sllv	$t4, $t4, $s2 		# $s2 is toggle value to correct bit index
	xor	$s7, $s7, $t4 		# xor s7 against t4 bit value
    					
    	sb 	$s7, ($s6)       	# Changing the character in text_buffer to the shifted character
    	addi 	$t0, $t0, 1    		# increment iterator +1
    	j encryptCharLoop    		# continue loop
	
    	exitLoop:
 	jr $ra				# jump to return address


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
	#0000 1000 XOR value toggle of 3 (3+1 = index 4)
	#----------
	#0100 0100 XOR result (encrypted)
	
	
	# DECRYPT
	#la 	$t5, buffer
	#sb 	$t4, 0($t5)
	# Use toggle bit OXOR again
	# subtract 'add' value
	
			
	
	
	
	
	
