#pragma once

#include "ofxMaxGuiWriter.h"
#include "ofxOsc.h"

#include "ofMain.h"

class ofxMaxGui{

public:
	
	ofxMaxGui(){};
	~ofxMaxGui();

	void setup		( int portOF, int portMaxMsp );
	void update		( void );

	void addPatcher ( float win_x, float win_y, float win_w=500, float win_h=500 );
	void addOscOut	( float x, float y );
	void addOscIn	( float x, float y );

	template<class ListenerClass, typename ListenerMethod>
	void addBang	( string name, float x, float y, ListenerClass *listener, ListenerMethod method ){
		Json::Value obj = writer.create_bpatcher(x, y, def_w, def_h, "sBang.maxpat");
		obj["box"]["args"] = name;
		writer.addObject( obj );
		bangs.insert( pair<string, ofEvent<void> > (name, ofEvent<void>()) );
		ofAddListener( bangs[name], listener, method );
	}
	void addToggle	( string name, float x, float y, bool * toggle );
	void addInt		( string name, float x, float y, int * i );
	void addFloat	( string name, float x, float y, float * f );
	void addColor	( string name, float x, float y, ofFloatColor * color );
	void addComment ( float x, float y, float w, float h, string text );
	//void addMessage ( float x, float y, float w, float h, string text );
	
	void write		( string file_name );
	void open		( string file_name );
	void close		( string file_name );

	string getCode	( void );
	int	 getPortOF	( void );
	int	 getPortMax	( void );
private:

	static const int def_w = 350;
	static const int def_h = 20;
	static const int def_h_long = 60;
	int portMax;
	int portOF;

	string code;
	
	map<string, ofEvent<void> > bangs;
	map<string, bool*>			toggles;
	map<string, int*>			intValues;
	map<string, float*>			floatValues;
	map<string, ofFloatColor*>	colors;
	
	ofxMaxGuiWriter writer;
	ofxOscReceiver	oscr;
	ofxOscSender	oscs;
};
