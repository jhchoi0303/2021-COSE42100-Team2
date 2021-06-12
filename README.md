# Smart Gloves - Arduino, Android App

* #### COSE42100- EMBEDDED SYSTEMS, TEAM2 final project

<img src="https://github.com/jhchoi0303/2021-COSE42100-Team2/blob/main/SmartGloveApp/app/src/main/ic_launcher-playstore.png"  width="300" height="300">






## About

Our code consists of arduino codes and an android application that is user specific.

Smart Gloves is for disabled people (the blind, deaf), to help them and protect them from danger that lurks in their daily lives.


Just put on the Smart Gloves and make a bluetooth connection with the android application.



## Features

* ### Arduino code

    ### 1. Overall feature (main.ino, one glove)
    1. Senses high/low temporature 
    2. Senses close objects
    3. Prints out 3 types of emergency command on the LCD monitor
    4. Senses the heartbeat of the user
    5. Senses dark places
    6. Bluetooth connection
    
    ### 2. Sign Language feature (flexsenor_read_and_send.ino & process_sign_language_speech_recognize.ino , the other glove)
    1. Sign Language (Recognize sign language and print on LCD monitor)
    2. Voice recognition



* ### Android Application

    #### Submit user info to arduino using bluetooth (uses "age" info to decide the range of normal heartbeat)



    ### Screenshots

<img src="https://github.com/jhchoi0303/2021-COSE42100-Team2/blob/main/screenshot1.png" width="300" height="600" style="float:left; padding-right:10px"/><img src="https://github.com/jhchoi0303/2021-COSE42100-Team2/blob/main/screenshot2.png" width="300" height="600"/>

