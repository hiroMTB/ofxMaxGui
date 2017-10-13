#pragma once

#include "ofMain.h"
#include "ofxJSON.h"

class ofxMaxGuiWriter{
    
public:
	string write( string file_name );
	void addObject( Json::Value &v );

	Json::Value create_patcher( float x, float y, float w, float h );
	Json::Value create_bpatcher( float x, float y, float w, float h, string fileName );
	Json::Value create_message( float x, float y, float w, float h, string text );
	Json::Value create_comment( float x, float y, float w, float h, string text );	
private:
	Json::Value rect( float x, float y, float w, float h );

	Json::Value root;

};