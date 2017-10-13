#include "ofxMaxGuiWriter.h"

void ofxMaxGuiWriter::addObject(Json::Value &v){
	root["patcher"]["boxes"].append( v );
}

Json::Value ofxMaxGuiWriter::create_patcher(float x, float y, float w, float h){
	Json::Value patcher;
	patcher["fileversion"] = 1;
	patcher["appversion"]["major"] = 5;
	patcher["appversion"]["minor"] = 1;
	patcher["appversion"]["revision"] = 9;
	patcher["rect"] = rect( x, y, w, h );
	root["patcher"] = patcher;
	return patcher;
}

Json::Value ofxMaxGuiWriter::create_bpatcher( float x, float y, float w, float h, string fileName ){
	Json::Value bpatcher;
	bpatcher["box"]["maxclass"] = "bpatcher";
	bpatcher["box"]["presentation_rect"] = rect(x, y, w, h);
	bpatcher["box"]["patching_rect"] = rect(x, y, w, h);
	bpatcher["box"]["numinlets"] = 0;
	bpatcher["box"]["numoutlets"] = 0;
	bpatcher["box"]["presentation"] = 1;
	bpatcher["box"]["name"] = fileName;
	return bpatcher;
}

Json::Value ofxMaxGuiWriter::create_comment(float x, float y, float w, float h, string text ){
	Json::Value comment;
	comment["box"]["maxclass"] = "comment";
	comment["box"]["presentation_rect"] = rect(x, y, w, h);
	comment["box"]["patching_rect"] = rect(x, y, w, h);
	comment["box"]["numinlets"] = 1;
	comment["box"]["numoutlets"] = 0;
	comment["box"]["presentation"] = 1;
	comment["box"]["text"] =  text;
	comment["box"]["linecount"] = (int)ofSplitString(text, "\n").size();
	return comment;
}

Json::Value ofxMaxGuiWriter::create_message( float x, float y, float w, float h, string text ){
	Json::Value message;
	message["box"]["maxclass"] = "message";
	message["box"]["presentation_rect"] = rect(x, y, w, h);
	message["box"]["patching_rect"] = rect(x, y, w, h);
	message["box"]["numinlets"] = 2;
	message["box"]["numoutlets"] = 1;
	message["box"]["presentation"] = 1;
	message["box"]["text"] =  text;
	return message;
}


Json::Value ofxMaxGuiWriter::rect(float x, float y, float w, float h){
	Json::Value r;
	r[0] = x;
	r[1] = y;
	r[2] = w;
	r[3] = h;
	return r;
}

string ofxMaxGuiWriter::write(string file_name){
	
	// write Max Json file
	ofFile file;
	Json::StyledWriter writer;
	file.open( file_name, ofFile::WriteOnly );
	file << writer.write( root ) << endl;
	file.close();
	
	//	store result string
	ofFile reader( file_name );
	ofBuffer buf = reader.readToBuffer();
	string code = buf.getText();
	reader.close();
	
	return code;
}
