//
//  ofxBufferMesh.cpp
//
//  Created by Tobias Ebsen on 08/01/14.
//
//

#include "ofxBufferMesh.h"

ofxBufferMesh::ofxBufferMesh() {
    texCoords = NULL;
    indices = NULL;
    vertices = NULL;
    hasTex = NULL;
    tex = NULL;
    mode = GL_TRIANGLES;
}

void ofxBufferMesh::draw() {

    if (texCoords) {
        if (hasTex)
            texCoords->begin(*hasTex);
        else if (tex)
            texCoords->begin(*tex);
        else
            texCoords->begin();
    }
    
    if (vertices) vertices->bind();
    if (indices) indices->draw(mode);
    if (vertices) vertices->unbind();
    
    if (texCoords) {
        if (hasTex)
            texCoords->end(*hasTex);
        else if (tex)
            texCoords->end(*tex);
        else
            texCoords->end();
    }
}