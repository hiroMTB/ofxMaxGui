#pragma once

#include "ofMain.h"
#include "ofxMaxGui.h"

class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();
	void exit();
	void keyPressed( int key );
	void myBang();

	bool myToggle;
	int	myInt;
	float myFloat;
	float csize;
	ofFloatColor drawColor;
	ofFloatColor bgColor;

	ofxMaxGui gui;
	string guiName;
	string timeStamp;
};
