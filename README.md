# SHA256CRACK
SHA256 cracking tool written in C++

Utilizes 2 attack modes - Brute Force and a Dictionary attack

**Features**
**Brute Force Attack:** 
Attempts to crack a password by trying every possible combination of characters from a specified charset


**Dictionary Attack:** 
Cracks the password by checking each word from a dictionary file (a list of potential passwords) against the hashed target password


**Multithreading:** 
Uses the available CPU cores to perform the brute force attack concurrently, speeding up the cracking process


**Customizable Charset & Max Length:** 
Allows the user to specify a custom charset and maximum password length for the brute force attack


**Default Charset:** 
Offers a default charset (abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()) and max length of 10 characters for simplicity

**Requirements**
C++11 or later.
OpenSSL library for SHA-256 hashing.

[![Main Skills](https://skillicons.dev/icons?i=cpp)](https://skillicons.dev)








```yaml
           ;               ,           
         ,;                 '.         
        ;:                   :;        
       ::                     ::       
       ::                     ::       
       ':                     :        
        :.                    :        
     ;' ::                   ::  '     
    .'  ';                   ;'  '.    
   ::    :;                 ;:    ::   
   ;      :;.             ,;:     ::   
   :;      :;:           ,;"      ::   
   ::.      ':;  ..,.;  ;:'     ,.;:   
    "'"...   '::,::::: ;:   .;.;""'    
        '"""....;:::::;,;.;"""         
    .:::.....'"':::::::'",...;::::;.   
   ;:' '""'"";.,;:::::;.'""""""  ':;   
  ::'         ;::;:::;::..         :;  
 ::         ,;:::::::::::;:..       :: 
 ;'     ,;;:;::::::::::::::;";..    ':.
::     ;:"  ::::::"""'::::::  ":     ::
 :.    ::   ::::::;  :::::::   :     ; 
  ;    ::   :::::::  :::::::   :    ;  
   '   ::   ::::::....:::::'  ,:   '   
    '  ::    :::::::::::::"   ::       
       ::     ':::::::::"'    ::       
       ':       """""""'      ::       
        ::                   ;:        
        ':;                 ;:"        
         ';              ,;'          
            "'           '"            
              '
```
