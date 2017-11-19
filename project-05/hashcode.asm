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

prompt1: .asciiz "Please enter a file name: "
newline: .asciiz "\n"
debug: .asciiz "DEBUG \n"


.text

main:
#Prompt the user for the file name
	la $a0, prompt1
	li $v0, 4
	syscall
	
	# getting text from user
	la $a0, filename
	la $a1, 20
	li $v0, 8 
	syscall
	
	#NOW DO FUNCTIONS
	li $s0,0        # Set index to 0
	j REMOVE_NEWLINE
	
	#branch to appropriate function
	j OPENFILE
	
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
	#continue to open file
	j OPENFILE
	
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
  	
  	#
	
	#display debug in console
	la $a0, debug
	li $v0, 4
	syscall
	j END

HASH:

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


END:
	
	#terminates program
	li $v0, 10
	syscall
