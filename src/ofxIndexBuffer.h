/*
 *  ofxIndexBuffer.h
 *
 *  Created by Tobias Ebsen on 5/23/13.
 *
 */

#pragma once
#include "ofxBufferObject.h"

class ofxIndexBuffer : public ofxBufferObjectUint {
public:
	
	void allocate(int count, int usage);
	
	void draw(int mode, int count);
    void draw(int mode);
};