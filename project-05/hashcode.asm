# Alexander Vaughan, av1045643
# av1045643@swccd.edu

# STRING TO HASCODE

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
	jal HASH
	
	# Display hashvalue
	jal HASHVALUE
	
	#precautionary end program
	j END
	
REMOVE_NEWLINE:

    	lb $a3,filename($s0)    	# Load character at index
    	addi $s0,$s0,1      		# Increment index
    	bnez $a3,REMOVE_NEWLINE     	# Loop until the end of string is reached
    	beq $a1,$s0,SKIP    		# Do not remove \n when string = maxlength
    	subiu $s0,$s0,2     		# If above not true, Backtrack index to '\n'
    	sb $0, filename($s0)    	# Add the terminating character in its place
    
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
	
	jr $ra

HASH:
	
	#display debug in console
	la $a0, debug
	li $v0, 4
	syscall
	j END

	#modulus value 104729
	#base value 31
	
	beq $s0, '\0', END

	li $t1, 4
	li $t2, 3
	mult $t1,$t2			#stored in Lo
	mflo $t0			#stores Lo in $t0
	
	li $t1, 24
	li $t2, 5
	div $t1, $t2			# store value in Lo and Remainder in Hi 
	
	jr $ra


END:
	
	#terminates program
	li $v0, 10
	syscall
