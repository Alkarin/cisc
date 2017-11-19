# Alexander Vaughan, av1045643
# av1045643@swccd.edu

# STRING TO HASCODE
# TODO: Output resuilt
# More thorough testing
# Code cleanup
# Readability

# Prompt user to input a file name
# Read file
# Convert file into integer hash value with function
#

.data  

# give me 100 of 0x0a
#read: .byte 0x10:80
#text_buffer: .byte 0x00:100

read: .byte 0x00:100
filename: .byte 0x00:100		# filename for output
hashvalue: .byte 0x00:100

prompt1: .asciiz "Please enter a file name: "
prompt2: .asciiz "File content:\n"
prompt3: .asciiz "Hash value: "
newline: .asciiz "\n"
carriageReturn: .asciiz "\r"
debug: .asciiz "DEBUG \n"


.text

main:
#Prompt the user for the file name
	la $a0, prompt1
	li $v0, 4
	syscall
	
	# getting text(filename) from user
	la $a0, filename
	la $a1, 20
	li $v0, 8 
	syscall
	
#NOW DO FUNCTIONS
	# Remove newline from filename input
	li $s0,0        		# Set index to 0
	jal REMOVE_NEWLINE
	
	# Now open and read file
	jal OPENFILE
	
	# Display file content to user
	jal CONTENT

	# Hash file content
    	la $s0, read     		#s0 text iterating through    	
    	li $t0, 0       		#t0 iterator count: 0
    	add $t7, $zero, $zero		# initial hash int
	jal HASH
	
	# Display hashvalue
	jal HASHVALUE

	
	#precautionary end program
	j END
	
REMOVE_NEWLINE:

    	lb $a3,filename($s0)    	# Load character at index
    	addi $s0,$s0,1      		# Increment index
    	bnez $a3,REMOVE_NEWLINE		# Loop until the end of string is reached
    	beq $a1,$s0,SKIP    		# Do not remove \n when string = maxlength
    	subiu $s0,$s0,2     		# If above not true, Backtrack index to '\n'
    	sb $0, filename($s0)    	# Add the terminating character in its place
    	
    	jr $ra
    
SKIP:
	# Return to main
	jr $ra
	
OPENFILE:	
  	# Open a file
  	li   $v0, 13       		# system call for open file
  	la   $a0, filename    		# file name to read from
  	li   $a1, 0        		# Open for writing (flags are 0: read, 1: write)
  	li   $a2, 0        		# mode is ignored
  	syscall            		# open a file (file descriptor returned in $v0)
  	move $s6, $v0     		# save the file descriptor 
  
	# Read from file
	li   $v0, 14       		# system call for read from file
	move $a0, $s6      		# file descriptor 
	la   $a1, read   		# address of buffer to which to read
	li   $a2, 1024     		# hardcoded buffer length
	syscall            		# read from file

 	# Close the file 
  	li   $v0, 16       		# system call for close file
  	move $a0, $s6      		# file descriptor to close
  	syscall            		# close file
  	
  	jr $ra
  	
 
CONTENT:
	# Display file content
	la $a0, prompt2
	li $v0, 4
	syscall

	# Display file content
	li $v0, 4
	la $a0, read
	syscall
	
	#display newline in console
	la $a0, newline
	li $v0, 4
	syscall
	
	jr $ra

HASH:
	
	
	addi $t5, $zero, 104729		# modulus value
	addi $t6, $zero, 31		# base value
	
	add 	$s1, $s0, $t0		# $s1 = read[i]  			aka *v
    	lb 	$s2, 0($s1)     	# Loading char to hash into $s2		aka *v
	#############################

    	beq 	$s2, '\0', exitLoop	# Breaking the loop if we've reached the end
    	beq 	$s2, '\r', loopIterate	# skip carriageReturn
    	beq 	$s2, '\n', loopIterate	# skip newline

    	
    	mult $t6,$t7		# base * hash
    	add $t4, $zero, $zero	# set temp value
    	mflo $t4		# put mult product in $t4
    	add  $t4, $t4, $s2	#  the value to modulus against
    	
    	div $t4,$t5		# 106/104729
    	mflo $t3		# set $t4 to quotient of division
    	mult $t3,$t5		# subtract this from $t4
    	mflo $t2		# value from mult 
    	
    	sub $t4,$t4,$t2		# subtract modulo value from our value	# 106-0 =106
    	add $t7,$zero,$t4	# place result into hash
    	################
    	loopIterate:
    	addi 	$t0, $t0, 1    		# increment iterator +1
    	j HASH    		# continue loop
	
    	exitLoop:
 	jr $ra				# jump to return address

 	
HASHVALUE:

	# Display hashvalue
	la $a0, prompt3
	li $v0, 4
	syscall

	# Display hashvalue
	li $v0, 4
	la $a0, hashvalue
	syscall
	
	#display newline in console
	la $a0, newline
	li $v0, 4
	syscall
	
	#display debug in console
	la $a0, debug
	li $v0, 4
	syscall
	j END
	
	jr $ra
	
END:
	
	#terminates program
	li $v0, 10
	syscall
