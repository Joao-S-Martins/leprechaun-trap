[Project website](https://joao-s-martins.github.io/leprechaun-trap/ "Leprechaun Trap website")

# Leprechaun Trap
This is the result of a kindergarten family project that was assigned to my oldest son.

## The Plan
My son wanted a trap where a leprechaun would be baited by a rainbow & gold coins to travel over a cage. Then my son planned to pull a rope & trap the leprechaun within the cage. I suggested that we make a cage automatically close & add lights to enhance the rainbow & coins. He loved my suggestions & we had our goal set.

## The Design
My wife pulled a plastic cauldron from our Halloween decorations for us to decorate as a pot of gold. I was inspired to give it a faux top covered in coins and a hole sized for a leprechaun. No leprechaun dimensions were given for this project, so the final hole size was about 2.25 inches.
She also found some stick-on foam sheets that were green & sparkley. They were 12 inches by 10 inches. The project dimension were based off of these sheets & the cauldron. I sat with my son, the sheets, the cauldron, & a ruler, & we decided that the full trap should be as wide two sheets connected at the long ends and that the rainbow should go from end to end, behind the centered cauldron, with the bottom of it rising just a couple inches taller than the cauldron.

## Prototyping
I used [circuits.io](https://circuits.io/circuits/4252213-leprechaun-trap, "This project prototyped at circuits.io") to experiment with the initial electronics. I referenced tutorials from [adafruit.com](https://learn.adafruit.com/category/learn-arduino, "Arduino tutorials by Adafruit") about programing an Arduino to [blink an LED](https://learn.adafruit.com/adafruit-arduino-lesson-1-blink, "LED blinking tutorial by Adafruit"), [button input](https://learn.adafruit.com/adafruit-arduino-lesson-6-digital-inputs, "Button input tutorial at atafruit.com"), and [manipulating a servo](https://learn.adafruit.com/adafruit-Arduino-lesson-14-servo-motors, "Servo motors tutorial by Adafruit"). I further read about blinking an LED [without using the `delay()`](https://learn.adafruit.com/multi-tasking-the-arduino-part-1/overview, "Arduino multi-tasking tutorial by Adafruit") function and making [use of `interrupts`](https://www.arduino.cc/en/Reference/attachInterrupt, "Interrupts reference from Arduino AG").

### The Trap Mechanism
The idea here was straight-forward; leprechaun falls in the hole and hits a button, then a servo moves to cover the hole. In the code, you'll notice that `tripped` is a boolean variable that is checked regularly during `loop()`. It is used for state, initialized as `false`, and set `true` in `caught()`. The `caught()` function is referenced by the line `attachInterrupt(digitalPinToInterrupt(triggerPin), caught, CHANGE);`. This line is the keystone of this script; it sets the trap trigger to throw interrupt events and `caught()` as their event handler. Also take note that the `triggerPin` is 2, as the pins that can throw an interrupt event are limited.
The `loop()` function was designed to cycle very often. With each cycle it checks the state of `tripped`. If it's been set `true`, then the servo angle is written to cover the tap hole. Frequently writing to servo within the loop like this keeps me from having to use a different function to update the servo angle as is commonly required.

### The Lighting
The lighting was intended to create a sparkle effect, like the reflection of light gleaming off of a pile of gold coins as you walk by. As such, I wanted to make sure the LEDs would be lit for short moments at a time. To obscure the pattern and create a semingly random sparkle effect, I programed three different pins to blink at different intervals, then wired different banks of LEDs in series to each pin. These appear in the code as `blink1`, `blink2`, and `blink3`, each one an instance of the `Flasher` object. This object is designed to have its `update()` method called frequently, with which it decides whether to change the LED state and does so. Once the trap has been triggered, the LEDs are are turned on and remain that way.

## The Build
This is an idea of how the final electronics played out.

Breadboard
<iframe frameborder='0' height='448' marginheight='0' marginwidth='0' scrolling='no' src='https://circuits.io/circuits/4252213-leprechaun-trap/embed#breadboard' width='650'></iframe>

Schematic
<iframe frameborder='0' height='448' marginheight='0' marginwidth='0' scrolling='no' src='https://circuits.io/circuits/4252213-leprechaun-trap/embed#schematic' width='650'></iframe>

### Woodworks
The base was make of scrap hardboard to the dimensions of the two foam sheets. Some scrap pieces of red oak were added underneath as feet, to allow space for wiring underneath. Some more scrap hardboard was glued along its ends and braced to become the rainbow. My son helped draw the curves of the rainbow and I cut it. Some strips of red oak were added to give the rainbow something to be screwed to the base. The rainbow was painted by my son, with glitter added, and would later be the last thing added to the base. I added holes to the base piece for the power switch and reset button. Another hole was added to the middle to run wires into the cauldron. The foam sheets, switch, button, cauldron, stickers, and gold coins were then added. 1/8 inch holes were drilled in between other decorations to install LEDs.

I created the faux top to the cauldron out of hardboard. The hole in the center was cut using a 2.25 inch hole saw and the cut-out was re-purposed as the trap cover. A hole was cut into the faux top for the servo and a scrap piece of plywood was attached underneath to eventually hold the trigger button, which was a large limit switch with a long arm that spans most of the width of the hole. Magnets were used to attach the faux lid to the cauldron, allowing easy access to the inner wiring and for removing any trapped leprechauns. I hot-glued round magnets under the lip of the cauldron. I then place the lid on top and let the magnetic force of the cauldron magnets guide my placement of the lid magnets. I used a forstner bit to partially drill sockets for the magnets on the lid and hot-glued them into place as well.

### Wiring
Most wiring was solid 22 gauge. I cut a few servo extension cables to be used with the servo and trigger button, allowing a quick disconnect. I put a small 2 channel patch inside the cauldron to help distribute 5V & ground from the Arduino. I glued an 8 channel patch underneath the base to help distribute the ground, reset, and LED signals. I really wanted to use a lit, shielded power switch that I had been storing for years. So I spliced it into a USB cable and used the USB cable & a 2200mah USB battery pack to power the Arduino.

Individual LEDs had their 200Ohm resistors soldered to them along with some lengths of wire. The LEDs were installed in the small holes in the base of the trap and wires cut to reach the patch panel. Some of my resistors turned out to be too fragile, even though I added shrink tubing to help reinforce them. Once everything was in place, including the Arduino Uno within the cauldron, I nervously tested the whole trap. It all worked! I immediately started applying hot-glue everywhere: LEDs, patch panels, Arduino pins, and some soldered connections just for good measure. Then I tested several more times, smiling successfully.

## The Result
The trap was a hit. The final result was a real attention getter. The blinking lights highlighted the many reflective bits that my son wanted to include. The rainbow made a fantastic background. Watching my son drop small toys into the hole and reset the trap to drop more toys was hugely rewarding.

## Lessons Learned
- Only certain Arduino pins can throw interrupts.
- After handling an interrupt, control is returned to the previously interrupted portion of `loop()`; `loop()` is not restarted.
- Running a `while true` loop within an interrupt handler works for some cases, but not all, as was the case with trying to change my servo angle. I recommend using interrupts to set state and have that state checked often within your main `loop()`.
- The power and ground cables inside of a USB cable are very, very thin.
- Test components often.
- Test soldered joints with a multimeter immediately after cooling.
- Don't get too fancy with special connectors and disconnects, because the add extra points of failure that can lead to diagnostic headaches.
