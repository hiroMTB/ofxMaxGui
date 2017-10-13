#include "ofxMaxGui.h"
#include "ofxJSON.h"

void ofxMaxGui::setup( int _portOF, int _portMax ){
	portOF = _portOF;
	portMax = _portMax;
	oscr.setup( portOF );
	oscs.setup( "localhost", portMax );
    
    cout << "Osc Listening on " << portOF << " port" << endl;
    cout << "Osc Sending to " << portMax << " port" << endl;
}

void ofxMaxGui::addPatcher ( float win_x, float win_y, float win_w, float win_h){
	writer.create_patcher( win_x, win_y, win_w, win_h );
}

void ofxMaxGui::addOscOut( float x, float y ){
	Json::Value oscOut = writer.create_bpatcher(x, y, 150, def_h, "sOscOut.maxpat" );
	oscOut["box"]["args"] = portOF;
	writer.addObject( oscOut );
}

void ofxMaxGui::addOscIn( float x, float y ){
	Json::Value oscIn = writer.create_bpatcher(x, y, 150, def_h, "sOscIn.maxpat" );
	oscIn["box"]["args"] = portMax;
	writer.addObject( oscIn );
}

void ofxMaxGui::addToggle ( string name, float x, float y, bool * toggle ){
	Json::Value obj = writer.create_bpatcher(x, y, def_w, def_h, "sToggle.maxpat");
	obj["box"]["args"] = name;
	writer.addObject( obj );
	toggles.insert(pair<string, bool*>(name, toggle));
}

void ofxMaxGui::addInt ( string name, float x, float y, int * i ){
	Json::Value obj = writer.create_bpatcher(x, y, def_w, def_h, "sInt.maxpat");
	obj["box"]["args"] = name;
	writer.addObject( obj );
	intValues.insert(pair<string, int*>(name, i));
}

void ofxMaxGui::addFloat ( string name, float x, float y, float * f ){
	Json::Value obj = writer.create_bpatcher(x, y, def_w, def_h, "sFloat.maxpat");
	obj["box"]["args"] = name;
	writer.addObject( obj );
	floatValues.insert(pair<string, float*>(name, f));
}

void ofxMaxGui::addColor ( string name, float x, float y, ofFloatColor * color ){
	Json::Value obj = writer.create_bpatcher(x, y, def_w, def_h_long, "sColor.maxpat");
	obj["box"]["args"] = name;
	writer.addObject( obj );
	colors.insert(pair<string, ofFloatColor*>(name, color));
}

void ofxMaxGui::addComment(float x, float y, float w, float h, string text){
	Json::Value obj = writer.create_comment(x, y, w, h, text);
	writer.addObject(obj);
}

/*
//  This works collectly but don't send any Osc. Comment out to avoid confusing.
void ofxMaxGui::addMessage(float x, float y, float w, float h, string text){
	Json::Value obj = writer.create_message(x, y, w, h, text);
	writer.addObject(obj);
}
*/

void ofxMaxGui::write( string file_name ){
	code = writer.write(file_name);
}

void ofxMaxGui::update(){
	while ( oscr.hasWaitingMessages() ) {
		ofxOscMessage m;
		if( oscr.getNextMessage(&m) ){
			vector<string> adrs = ofSplitString(m.getAddress(), "/");

			/*
			 *	OSC address format (split)
			 *	adrs[0] = ""
			 *	adrs[1] = fromMax
			 *	adrs[2] = bang/toggle/int/float/color
			 *	adrs[3] = name
			 */
			string &top = adrs[1];

			if( top == "fromMax"){
				string &type = adrs[2];
				string &name = adrs[3];
				
				if( type == "bang" ){
					ofNotifyEvent( bangs[name] );
				}else if( type == "toggle" ){
					*toggles[name] = (bool)m.getArgAsInt32(0);
				}else if( type == "int" ){
					*intValues[name] = m.getArgAsInt32(0);
				}else if( type== "float" ){
					*floatValues[name] = m.getArgAsFloat(0);
				}else if( type == "color"){
					colors[name]->r = m.getArgAsFloat(0);
					colors[name]->g = m.getArgAsFloat(1);
					colors[name]->b = m.getArgAsFloat(2);
				}else{
					ofLogNotice("strange Osc msg type : " + type);
				}
			}else{
				ofLogNotice("strange Osc msg address : " + top);
			}
		}
	}
}

void ofxMaxGui::open( string file_name ){
	ofFile file;
	file.open( file_name, ofFile::ReadOnly );
	
	if( file.isFile() ){
		string command = "open " + ofToDataPath( file.getFileName(), true );
		system( command.c_str() );
	}
}

void ofxMaxGui::close( string file_name ){
//	ofFile file;
//	file.open( file_name, ofFile::ReadOnly );
//	
//	if( file.isFile() ){
//		string command = "close " + ofToDataPath( file.getFileName(), true );
//		system( command.c_str() );
//	}
}

string ofxMaxGui::getCode(){
	return code;
}

int ofxMaxGui::getPortOF(){
	return portOF;
}

ofxMaxGui::~ofxMaxGui(){

	map<string, ofEvent<void> >::iterator itr = bangs.begin();
	for(; itr!=bangs.end(); itr++){
		//ofRemoveListener( itr->second, ?, ?);
	}
}
