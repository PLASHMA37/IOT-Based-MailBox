Motivation:-
•	With the rise of e-commerce and frequent home deliveries, managing mail and package security has become more critical.
•	Many challenges persist, from missing deliveries to the rising concern of package theft.
•	The motivation behind this project is to create a seamless experience for managing mail and package deliveries while addressing growing concerns around convenience and security.

Implementation:-
The proposed smart mailbox works as follows:
• A digital locking mechanism with an LCD screen, keypad, and servo motor ensures secure access. Only authorized users can unlock the mailbox.
•	When the IR motion sensor detects the mailbox lid being opened, it signals the Arduino, which activates a servo-controlled barrier
  to prevent unauthorized access and sends a notification to the user's mobile device via the ESP32.
• A load cell paired with a weight amplifier measures the weight of delivered packages or letters. When a new delivery is detected, 
  the Arduino processes the data and sends notifications via the ESP32 to inform the user promptly.
  


