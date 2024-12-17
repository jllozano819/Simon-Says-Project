# Introduction
This project fulfills the final project requirements for the following course at California State University, Northridge (CSUN):
- ECE 425: Microprocessor Systems

Group Members:
- Wyatt Lopez Coggins
- Jose Lozano

Professor:
- Aaron Nanas

The final project we chose to perform for this course was to recreate the toy version of the “Simon Says” game by using the TM4C123GH6PM LaunchPad microcontroller and its peripherals. “Simon Says” is a fairly simple game that uses 4 buttons with each corresponding to a different color light and sound. The “Simon Says” device will generate a random sequence using the different color lights which the player will have to memorize in order to succeed. The player completes a level by correctly inputting the same sequence using the 4 buttons. When the level is completed the “Simon Says” game will replay the same sequence and generate random elements to add to the end of the sequence. This means that the sequence will remain the same for every level but will increase in length. The player will then have to memorize the longer sequence and use the buttons to input the sequence again. As the player completes more levels the sequence increases in length making it more difficult for the player to memorize. When a player fails they will then have to start over from the beginning with a new randomly generated sequence. Our project recreated the “Simon Says” game on the EduBase board with one minor difference. The main components of our project were the EduBase board 4 LEDs and their corresponding buttons, which were configured to be used in the same manner as the “Simon Says” game. The LEDs display the randomly generated sequence and the player uses the buttons in an attempt to match the displayed sequence. Unlike the original “Simon Says” game where the same sequence is used for every level, our “Simon Says” game is configured to generate a different sequence for every level. Each level has its own randomly generated sequence that will increase in length as the levels are passed. The player will have to pass 3 levels concurrently to win the game and if they fail a level they will restart from the beginning.

# Results and Video Demonstration
The following figures present the program running on the LaunchPad and EduBase Board.

<p align="center">
  <img src="https://github.com/user-attachments/assets/105da8b1-2147-4db8-b805-3f9827cd1c89"/>
</p>

- Figure 1 demonstrates the beginning of the program as the RGB LED on the Launchpad displays blue to indicate the game is active and while the seven segment indicates to the player that they are on level 1. The EduBase LED is also displaying part of the generated sequence for the level.

<p align="center">
  <img src="https://github.com/user-attachments/assets/3c5a8a18-2948-496a-a205-d167aafbb31f"/>
</p>

- Figure 2 shows how the game reacts when a player has successfully input a sequence. The LaunchPad RGB LED flashes a green color, while the Edubase LEDs flash the intended pattern (1001b) for the matched sequences.
  
<p align="center">
  <img src="https://github.com/user-attachments/assets/277bc484-932b-4e20-b83a-4d620679fc43"/>
</p>

- Figure 3 showcases the failed game state when a player’s sequence does not match the displayed sequence of the level. The RGB LED on the LaunchPad flashes a red color and while all four of the Edubase LEDs (1111b) flash at the same time with the LaunchPad LED to indicate to the player that they have failed level 1.
  
<p align="center">
  <img src="https://github.com/user-attachments/assets/2a1c1460-cf6f-411f-90c5-39a05f56c77e"/>
</p>

- Figure 4 depicts the program’s reaction to when a player has completed all 3 levels in succession. The seven segment display outputs a value of 0, while the LaunchPad LED displays green and the EduBase LEDs output the pattern (0110b) associated with a completed game.
  
**Video Demo:** [Link](https://youtu.be/1dyNteN_RUA)

# Background and Methodology
- The embedded concepts applied to this project include GPIO, timers, and interrupts. In order to smooth the development process of our project, we utilized drivers developed in the lab course, which include the GPIO, Buzzer, Seven Segment Display, and SysTick drivers. All the components used in the project use GPIO to function and the GPIO driver contains the necessary GPIO configuration for the LaunchPad RGB LED and EduBase Board LEDs and push buttons. The magnetic buzzer and Seven Segment Display GPIO configurations were contained within their own specific drivers, along with their other specific configurations. For timers, we utilized the SysTick driver for whenever we desired to have delays in our project’s game logic. Interrupt development was kept in the main source file of our project as it was viewed as part of our game logic and we wanted to keep all game logic related code in said source file. We configured interrupts for when players input their sequence where in response to a button press the button status of the EduBase board would be converted to a desired value and then stored in an array for the particular level they were on. Once the sequence was completely entered by the player, the player sequence array would then be compared to an array containing the values of the displayed sequence of that level.  
- The hardware components used for this project were all located on the EduBase board except for the RGB LED on the Launchpad. The RGB LED on the Launchpad is used to indicate the state of the game. If the LED is blue then the game is considered active and it will flash green to indicate if a level has been passed. It will also flash red when the player fails a level. The EduBase board LEDs, buttons, DMT-1206 magnetic buzzer, and seven segment display were all of the remaining components used for this project. The LEDs were configured to be paired with the switch button directly below them, such as how LED0 is paired with the SW5 button. The pair will also have a unique sound associated with them that is played from the magnetic buzzer whenever they are used. These LEDs and buttons were to be used to display and enter the sequences. The EduBase LEDs were also configured to display specific patterns whenever a level is passed or failed, as well as for when the game is beaten. The seven segment display was simply configured to display the level the player is on, as well as 0 for when the game is beaten. For sequence generation we utilized the rand function, which is included in the commonly used C library stdlib.h. 

# Block Diagram
<p align="center">
  <img src="https://github.com/user-attachments/assets/3faae931-d71e-4890-ac4a-40b3f58dc5c8"/>
</p>

# Pinout Used
TM4123G RGB LED | TM4C123G LaunchPad Pin
:-: | :-:
Red LED | PF1
Green LED | PF2
Blue LED | PF3
**EduBase Board LED** | 
LED 0 | PB0
LED 1 | PB1
LED 2 | PB2
LED 3 | PB3
**Magnetic Buzzer** | PC4
**Seven Segment Display** |
SSI2 CLK | PB4
SSI2 TX Data | PB7
SSI2 SS | PC7
# Components Used
Description | Quantity | Manufacturer
:-: | :-: | :-:
Tiva C Series TM4C123G LaunchPad | 1 | Texas Instruments
USB-A to Micro-USB Cable | 1 | N/A
EduBase Board | 1 | Trainer4Edu
