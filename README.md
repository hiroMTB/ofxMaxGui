# ofxMaxGui
This is openFrameworks addon for generating GUI file.
It GUI file is only able to be opened and controled via Max (Cycling 74).


# Update
Dec, 2018 


# Developed / Tested on	
- OSX 10.12
- Windows 10
- openFrameworks 0.10.1
- Max 7 

# DEPENDENCY
- ofxOsc  : default openFrameworks addon
- ofxJson : https://github.com/jefftimesten/ofxJSON

# NOTICE

## Parameter sync limitation
  - Max patch can synclonize parameters with ofApp. But ofApp can not.
  - Number box object does not sync with slider object.
			

## Read only use
After you generate Max patch, you only need setup() and update() to communicate with Max.


## OSC address syntax
Do not use special characters for "name" parameter of GUI parts as as it is used for OSC address. Charactors of space, conmma, #, *, /, ?, [, ], {, } are not allowed.

	e.g.
		Bad
			addToggle("my toggle", 10, 10);

		Good
			addToggle("my_toggle", 10, 10);

## Duplicate Max patch/Osc message
Max patch remain open if you don’t close manually.
These remained, old max patch keep sending osc message to your new ofApp.
Don’t forget to close previous patch. close() function does not work now.


## Sub patch installation
ofxMaxGui load sub patches (sToggle.maxpat, sInt.maxpat, etc) for bpatcher objects of main GUI patch.
Recommend to move to Max search path directory.
Otherwise you must copy it every time when you start new projects.




# FUTURE DEVELOPMENT

## Message object
Nice to send string value to ofApp.
Store callback? or just string pointer?
We should handle user push event.
But if so, why no callback for another GUI parts(int/float/toggle/color).
This is not difficult but want to keep small addon.
Decide after I start using this addon.

## close() function
Does not work now.
Send close request to Max via OSC?



# MEMO

## ofEvent copy limitation
We can not copy Poco::priorityEvent (copy constructor and =operator are locked as private).
ofEvent inherit Poco::priorityEvent and not callbacked after ofEvent copy.
So first we insert/add ofEvent to container and then call ofAddListener.

	e.g.
		Bad
			ofEvent<void> event;
			ofAddListener( event, listener, method );
			myMap.insert( pair<string, ofEvent<void> > (name, event) );

		Good
			myMap.insert( pair<string, ofEvent<void> > (name, ofEvent(void)) );
			ofAddListener( myMap[name], listener, method );
