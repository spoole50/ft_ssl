# ft_ssl
## Encryption and Security

### Skills:
  1. Bit Memory Operations
  2. Function Dispatcher
  3. Endianness Concepts
  
### Objective:
- Recode functionality of openssl, specifically MD5 and sha256 hashing algorithms.
	
#### Flags:
	-h => Usage and Help with flag explanation
	-p => Echo STDIN to STDOUT and append checksum
	-q => Quiet mode, only prints checksum
	-r => Reverse format of output
	-s => Print the checksum of following argument treated as string
  
#### Bonus:
	- SHA1, SHA224, SHA384, SHA512, SHA512/224, SHA512/256 Hashing Algorithms
  
#### Functional Overview:
Hashing Algorithms:
1. Preprocess Data (file or string in this case)
	- 1 bit appened to end of the data message
	- 0 bits appended until message is of proper length (algorithm dependant)
	- Message size (in bits) value is appended to the end of the padded message (64 or 128 bit depending on algorithm)
2. Apply Hashing algorithm to each block (512 or 1024 bit) of the padded message
	- Initialize state variables, intialize register variables with current state.
	- Algorithm specific compression functions applied to message block and stored in registers.
	- State updated (+=) with register values and process continues for each block of message.
3. Calcualate Output Hash
	- Final state constitutes hash value, print in hexadecimal

#### Resources:
- https://fthb321.github.io/MD5-Hash/MD5OurVersion2.html
- https://medium.com/a-42-journey/implementing-the-sha256-and-md5-hash-functions-in-c-78c17e657794
- https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.180-4.pdf
- https://security.stackexchange.com/questions/11717/why-are-hash-functions-one-way-if-i-know-the-algorithm-why-cant-i-calculate-t/19658#19658

##### -DES
- https://academic.csuohio.edu/yuc/security/Chapter_06_Data_Encription_Standard.pdf
- https://csrc.nist.gov/csrc/media/publications/fips/46/3/archive/1999-10-25/documents/fips46-3.pdf
