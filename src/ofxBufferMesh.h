//
//  ofxBufferMesh.h
//
//  Created by Tobias Ebsen on 08/01/14.
//
//

#pragma once
#include "ofxVertexBuffer.h"
#include "ofxIndexBuffer.h"
#include "ofxTexCoordBuffer.h"

class ofxBufferMesh {
public:
    ofxBufferMesh();
    
    void setMode(int mode) { this->mode = mode; }
    int getMode() { return this->mode; }
    
    void setVertexBuffer(ofxVertexBufferFloat & vertices) { this->vertices = &vertices; }
    void setIndexBuffer(ofxIndexBuffer & indices) { this->indices = &indices; }
    void setTexCoodBuffer(ofxTexCoordBufferFloat & texCoords) { this->texCoords = &texCoords; }
    
    void setTexture(ofTexture & tex) { this->tex = &tex; }
    void setTextureSource(ofBaseHasTexture & hasTex) { this->hasTex = &hasTex; }

    void draw();
    
private:
    ofxVertexBufferFloat* vertices;
    ofxIndexBuffer* indices;
    ofxTexCoordBufferFloat* texCoords;
    
    ofTexture* tex;
    ofBaseHasTexture* hasTex;

    int mode;
};