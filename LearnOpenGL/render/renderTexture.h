//
//  renderTexture.hpp
//  LearnOpenGL
//
//  Created by www on 2019/11/10.
//  Copyright © 2019 woodlouse. All rights reserved.
//

#ifndef renderTexture_hpp
#define renderTexture_hpp

class renderTexture
{
public:
    renderTexture(const char *texPath, int format);
public:
    unsigned int textureId;
};

#endif /* renderTexture_hpp */
