# Alexander Vaughan, av1045643
# av1045643@swccd.edu

# caesar cipher encryption

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

# give me 100 of 0x0a
encryption_result: .byte 0x10:80
text_buffer: .byte 0x0e:100

msg : .asciiz "Hello World!" # hardcoded for example
prompt1: .asciiz "Enter 'e' or 'd' to select encrypt or decrypt:\t"
prompt2: .asciiz "Enter addition key:\t"
prompt3: .asciiz "Enter bit toggle key:\t"
prompt4: .asciiz "Enter text to encrypt:\t"
prompt5: .asciiz "Encrypted text:\t"
prompt6: .asciiz "Decrypted text:\t"
validation1: .asciiz "Invalid command input, please enter 'e' or 'd' to select encrypt or decrypt.\n"
newline: .asciiz "\n"
debug: .asciiz "DEBUG \n"
debug2: .asciiz "DEBUG2 \n"
debug3: .asciiz "DEBUG3 \n"

# SAVED REGISTERS
# s0	'e' or 'd'
# s1	Addition key
# s2	Toggle key
# s3	Addition increment count
# s4	Other increment count
############################################################
.text

main:
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
	
	# Invalid command input
	la $a0, validation1
	li $v0, 4
	syscall
	
	# request user input again
	j main
	
	#precautionary end program
	j END

ENCRYPT:

    	la $s5, text_buffer     #s0 text iterating through
    	la $t1, 0($s1)     	#s1 add value
    	li $t0, 0       	#t0 iterator count: 0
	
	# call function to encrypt each char
	jal encryptCharLoop
	
	# display result
	j RESULT
	
DECRYPT:

	sub $t1, $zero $s1	# subtract s1 add value
    	la $s5, text_buffer     #s0 text iterating through    	
    	li $t0, 0       	#t0 iterator count: 0
	
	# call function to encrypt each char
	jal dencryptCharLoop
	
	# display result
	j RESULT2

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

dencryptCharLoop:

   	add 	$s6, $s5, $t0		# $s6 = text_buffer[i]
    	lb 	$s7, 0($s6)     	# Loading char to shift into $s7
    	beq 	$s7, $zero, exitLoop2	# Breaking the loop if we've reached the end: http://stackoverflow.com/questions/12739463/how-to-iterate-a-string-in-mips-assembly
    	add 	$s7, $s7, $t1   	# Shift char by add value
    	
    	#APPLY_TOGGLE
    	# set bit toggle value from user input
	la	$t4, 0x01 		# HARDCODED 0x01: gives value of 0000 0001
	sllv	$t4, $t4, $s2 		# $s2 is toggle value to correct bit index
	xor	$s7, $s7, $t4 		# xor s7 against t4 bit value
    					
    	sb 	$s7, ($s6)       	# Changing the character in text_buffer to the shifted character
    	addi 	$t0, $t0, 1    		# increment iterator +1
    	j encryptCharLoop    		# continue loop
	
    	exitLoop2:
 	jr $ra				# jump to return address

#Display encrypted text result
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
	
#Display decrypted text result	
RESULT2:
	la $a0, prompt6
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
				
END:
#terminates program
li $v0, 10
syscall
		
				
# Trap handler
.ktext 0x80000180

	move $k0, $v0		# Save $v0 value
	move $k1, $a0		# Save $a0 value

	mfc0 $k0, $13		# get cause
	srl  $k0, $k0, 2	# determine cause

	# display trap message
	la $a0, TRAP		
	li $v0, 4		
	syscall

	move $v0, $k0		# Restore $v0
	move $a0, $k1		# Restore $a0
	mfc0 $k0, $14		# Coprocessor 0 register $14 takes address of trap
	addi $k0,$k0,4		# Add 4 to point to next instruction
	mfc0 $k0, $14		# Store new address back into $14
	eret			# Return error, set PC value to value in $14

.kdata

TRAP:
	.asciiz "Trap generated"


	
	
	
	
