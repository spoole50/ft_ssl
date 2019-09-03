# ft_ssl
## Encryption and Security

### Skills:
  1. Bit Memory Operations
  2. Function Dispatcher
  3. Endianness Concepts
  
### Objective:
  - Recode functionality of openssl, specifically MD5 and sha256 hashing algorithms.
  
#### Functional Overview:
Hashing Algorithms:
1. Preprocess Data (file or string in this case)
	- 1 bit appened to end of the data message
	- 0 bits appended until message is of proper length (algorithm dependant)
	- Message size (in bits) value is appended to the end of the padded message (64 or 128 bit depending on algorithm)
2. Apply Hashing algorithm to each block (512 or 1024 bit) of the padded message
	- Algorithm specific compression functions applied to data 
