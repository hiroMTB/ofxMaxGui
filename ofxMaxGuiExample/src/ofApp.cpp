#include "ofApp.h"

void ofApp::setup(){

	ofSetWindowPosition( 0, 0 );
	ofSetWindowShape( 500, 500 );
	
	bgColor.set(0.8);
	drawColor.set(0.1);
	timeStamp = ofGetTimestampString();
	guiName = "_gui_main.maxpat";
    int oscOutPort = 1234;
    int oscInPort = 4321;
    
	gui.setup( oscOutPort, oscInPort );
	
	bool bReGenerateGui = true;
	if( bReGenerateGui ){
		int x = 45;
		int y = 50;
		gui.addPatcher(500, 0, 500, 500);
		gui.addOscOut( x, 30 );
		gui.addOscIn( x, y+=30 );
		gui.addBang("myBang", x, y+=30, this, &ofApp::myBang);
		gui.addToggle("myToggle", x, y+=30, &myToggle);
		gui.addInt("myInt", x, y+=30, &myInt);
		gui.addFloat("myFloat", x, y+=30, &myFloat);
		gui.addColor("drawColor", x, y+=30, &drawColor);
		gui.addColor("bgColor", x, y+=70, &bgColor);
		gui.addComment(x, 500-60, 300, 20, "Generated                     " + timeStamp );
		gui.write( guiName );
	}
	

	gui.open( guiName );
}

void ofApp::update(){
	gui.update();
}

void ofApp::draw(){
	
	ofBackground( bgColor );
	ofSetColor( drawColor );
	ofDrawBitmapString("OSC Port       " + ofToString(gui.getPortOF()), 50, 45);
	
	ofSetColor(255, 0, 0);
	ofFill();
	ofCircle(173, 90, MAX(--csize, 3));
	
	ofSetColor( drawColor );
	stringstream ss;
	ss << "myBang\n\n";
	ss << "myToggle       " << myToggle << "\n\n";
	ss << "myInt          " << myInt << "\n\n";
	ss << "myFloat        " << myFloat << "\n\n";
	ss << "drawColor\n\n";

	ofDrawBitmapString( ss.str(), 50, 95 );
	
	ofSetColor( drawColor );
	ofRect(170, 195, 200, 60);
	
	ofDrawBitmapString("Compiled      " + timeStamp, 50, 500-45);

}

void ofApp::myBang(){
	cout << "bang" << endl;
	csize = 10;
}


void ofApp::exit(){
	gui.close( guiName );
}

void ofApp::keyPressed( int key ){
	
	switch ( key) {
		case ' ':
			gui.open( guiName );
			break;
			
		default:
			break;
	}
}
