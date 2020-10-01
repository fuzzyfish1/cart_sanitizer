# cart_sanitizer
	our objective is pretty much to create a carwash
	for shopping carts
## how to use
	list of steps to use this
	1. plug pump into sonoff
	2. plug sonoff into electrical wall socket
	3. wait until it connects to local wifi
	4. adjust sprayers as necessary
	5. find ip adress
		* check your routers arp tables
	6. remote control
		* enter ip into chrome browser
		* push on or off buttons to control
		* tap button to enter manual control/emergency shuttoff
	7. manual control
		1. wait for slow blink to finish
		2. tap once to toggle on/off
		3. to enter remote control
			* press and hold button for 3seconds
			* wait for fast blink to finish
	
## mechanical aspect
	we are using a fishtank pump to pump water through vinyl tube
	which goes through t splitter to 2 smaller tubes
	2 tubes go to 2 adjustable sprayers
## software aspect
	we are using an itead sonoff board for control
	it includes an esp8266, relay, and a green led	