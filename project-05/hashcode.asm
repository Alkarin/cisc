# Alexander Vaughan, av1045643
# av1045643@swccd.edu

# STRING TO HASCODE

# Prompt user to input a file name
# Read file
# Convert file into integer hash value with function
#

.data  
# give me 100 of 0x0a
encryption_result: .byte 0x10:80
text_buffer: .byte 0x0e:100


prompt1: .asciiz "Please enter a file name:\t"
input: 	 .asciiz "default.txt"      # filename for input
buffer:  .asciiz ""

.text

main:
#Prompt the user for the file name
	la $a0, prompt1
	li $v0, 4
	syscall
	
	# getting text from user
	la $a0, text_buffer
	la $a1, 20
	li $v0, 8 
	syscall
	
	#NOW DO FUNCTIONS
	
	#branch to appropriate function
	#j END
	
	#precautionary end program
	j END
	
HASH:
#do shit
	
OPENFILE:	
#open a file for writing
li   $v0, 13       # system call for open file
la   $a0, input    # board file name
li   $a1, 0        # Open for reading
li   $a2, 0
syscall            # open a file (file descriptor returned in $v0)
move $s6, $v0      # save the file descriptor 

READFILE:
#read from file
li   $v0, 14       # system call for read from file
move $a0, $s6      # file descriptor 
la   $a1, buffer   # address of buffer to which to read
li   $a2, 1024     # hardcoded buffer length
syscall            # read from file

CLOSEFILE:
# Close the file 
li   $v0, 16       # system call for close file
move $a0, $s6      # file descriptor to close
syscall            # close file



END:
#terminates program
li $v0, 10
syscall