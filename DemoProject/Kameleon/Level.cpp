#include "Level.hpp"

Level::Level(ppPhysics* physics) : PhysicsObject(physics){
    this->reveal = 1;

	b2BodyDef* myBodyDef = new b2BodyDef();

	myBodyDef->type = b2_staticBody;
	myBodyDef->position.Set(this->physics->PixelToWorld(0), this->physics->PixelToWorld(0));
	this->body = this->physics->GetWorld()->CreateBody(myBodyDef);

	b2ChainShape* chainShape = new b2ChainShape();
	b2Vec2 vs[20];
	int index=0;
    vs[index++].Set(this->physics->PixelToWorld(650), this->physics->PixelToWorld(20));
    vs[index++].Set(this->physics->PixelToWorld(300), this->physics->PixelToWorld(20));
    vs[index++].Set(this->physics->PixelToWorld(300), this->physics->PixelToWorld(250));
    vs[index++].Set(this->physics->PixelToWorld(650), this->physics->PixelToWorld(250));
    vs[index++].Set(this->physics->PixelToWorld(650), this->physics->PixelToWorld(400));

    vs[index++].Set(this->physics->PixelToWorld(350), this->physics->PixelToWorld(400));
    vs[index++].Set(this->physics->PixelToWorld(350), this->physics->PixelToWorld(325));
    vs[index++].Set(this->physics->PixelToWorld(300), this->physics->PixelToWorld(325));
    vs[index++].Set(this->physics->PixelToWorld(300), this->physics->PixelToWorld(400));
    vs[index++].Set(this->physics->PixelToWorld(150), this->physics->PixelToWorld(400));
    vs[index++].Set(this->physics->PixelToWorld(150), this->physics->PixelToWorld(500));
    vs[index++].Set(this->physics->PixelToWorld(-150), this->physics->PixelToWorld(500));
    vs[index++].Set(this->physics->PixelToWorld(-150), this->physics->PixelToWorld(400));
    vs[index++].Set(this->physics->PixelToWorld(-400), this->physics->PixelToWorld(400));
    vs[index++].Set(this->physics->PixelToWorld(-400), this->physics->PixelToWorld(20));
    chainShape->CreateChain(vs, index);

    this->levelMask.push_back(b2Vec2(this->physics->PixelToWorld(-625), this->physics->PixelToWorld(550)));
    this->levelMask.push_back(b2Vec2(this->physics->PixelToWorld(-625), this->physics->PixelToWorld(20)));
    this->levelMask.push_back(b2Vec2(this->physics->PixelToWorld(-400), this->physics->PixelToWorld(20)));
    this->levelMask.push_back(b2Vec2(this->physics->PixelToWorld(-400), this->physics->PixelToWorld(550)));

    this->levelMask.push_back(b2Vec2(this->physics->PixelToWorld(-400), this->physics->PixelToWorld(400)));
    this->levelMask.push_back(b2Vec2(this->physics->PixelToWorld(-150), this->physics->PixelToWorld(400)));
    this->levelMask.push_back(b2Vec2(this->physics->PixelToWorld(-150), this->physics->PixelToWorld(500)));
    this->levelMask.push_back(b2Vec2(this->physics->PixelToWorld(-400), this->physics->PixelToWorld(500)));

    this->levelMask.push_back(b2Vec2(this->physics->PixelToWorld(-625), this->physics->PixelToWorld(500)));
    this->levelMask.push_back(b2Vec2(this->physics->PixelToWorld(-625), this->physics->PixelToWorld(700)));
    this->levelMask.push_back(b2Vec2(this->physics->PixelToWorld(900), this->physics->PixelToWorld(700)));
    this->levelMask.push_back(b2Vec2(this->physics->PixelToWorld(900), this->physics->PixelToWorld(500)));

    this->levelMask.push_back(b2Vec2(this->physics->PixelToWorld(300), this->physics->PixelToWorld(400)));
    this->levelMask.push_back(b2Vec2(this->physics->PixelToWorld(300), this->physics->PixelToWorld(325)));
    this->levelMask.push_back(b2Vec2(this->physics->PixelToWorld(350), this->physics->PixelToWorld(325)));
    this->levelMask.push_back(b2Vec2(this->physics->PixelToWorld(350), this->physics->PixelToWorld(400)));

    this->levelMask.push_back(b2Vec2(this->physics->PixelToWorld(150), this->physics->PixelToWorld(400)));
    this->levelMask.push_back(b2Vec2(this->physics->PixelToWorld(650), this->physics->PixelToWorld(400)));
    this->levelMask.push_back(b2Vec2(this->physics->PixelToWorld(650), this->physics->PixelToWorld(700)));
    this->levelMask.push_back(b2Vec2(this->physics->PixelToWorld(150), this->physics->PixelToWorld(700)));

    this->levelMask.push_back(b2Vec2(this->physics->PixelToWorld(650), this->physics->PixelToWorld(20)));
    this->levelMask.push_back(b2Vec2(this->physics->PixelToWorld(900), this->physics->PixelToWorld(20)));
    this->levelMask.push_back(b2Vec2(this->physics->PixelToWorld(900), this->physics->PixelToWorld(700)));
    this->levelMask.push_back(b2Vec2(this->physics->PixelToWorld(650), this->physics->PixelToWorld(700)));

    this->levelMask.push_back(b2Vec2(this->physics->PixelToWorld(300), this->physics->PixelToWorld(20)));
    this->levelMask.push_back(b2Vec2(this->physics->PixelToWorld(650), this->physics->PixelToWorld(20)));
    this->levelMask.push_back(b2Vec2(this->physics->PixelToWorld(650), this->physics->PixelToWorld(250)));
    this->levelMask.push_back(b2Vec2(this->physics->PixelToWorld(300), this->physics->PixelToWorld(250)));

    this->levelFog.push_back(b2Vec2(this->physics->PixelToWorld(-650), this->physics->PixelToWorld(700)));
    this->levelFog.push_back(b2Vec2(this->physics->PixelToWorld(325), this->physics->PixelToWorld(700)));
    this->levelFog.push_back(b2Vec2(this->physics->PixelToWorld(325), this->physics->PixelToWorld(20)));
    this->levelFog.push_back(b2Vec2(this->physics->PixelToWorld(-650), this->physics->PixelToWorld(20)));

    this->waterMask.push_back(b2Vec2(this->physics->PixelToWorld(-150), 40.25f));
    this->waterMask.push_back(b2Vec2(this->physics->PixelToWorld(150), 40.25f));
    this->waterMask.push_back(b2Vec2(this->physics->PixelToWorld(150), this->physics->PixelToWorld(500)));
    this->waterMask.push_back(b2Vec2(this->physics->PixelToWorld(-150), this->physics->PixelToWorld(500)));

	this->body->CreateFixture(chainShape, 1.0f);

    this->vine1 = new ppImage("tmpres/Kameleon/Assets/Image 1298.png");
    this->vine2 = new ppImage("tmpres/Kameleon/Assets/Image 1318.png");
    this->vine3 = new ppImage("tmpres/Kameleon/Assets/Image 1321.png");

    this->tree1 = new ppImage("tmpres/Kameleon/Assets/Image 1396.png");
    this->tree2 = new ppImage("tmpres/Kameleon/Assets/Image 1394.png");
}

void Level::Render(SDL_Renderer* renderer){
    this->vine1->Render(renderer, this->physics->WorldToPixel(45), this->physics->WorldToPixel(38));
    this->vine2->Render(renderer, this->physics->WorldToPixel(43), this->physics->WorldToPixel(25));
    this->vine2->Render(renderer, this->physics->WorldToPixel(49), this->physics->WorldToPixel(25));
    this->vine3->Render(renderer, this->physics->WorldToPixel(-35), this->physics->WorldToPixel(38));
    this->tree1->Render(renderer, this->physics->WorldToPixel(20), this->physics->WorldToPixel(30));
    this->tree2->Render(renderer, this->physics->WorldToPixel(-20), this->physics->WorldToPixel(30));

    glColor3f(0, 0, 0);
    glBegin(GL_QUADS);
        for(auto vec : this->levelMask){
            glVertex2f(this->physics->WorldToPixel(vec.x), this->physics->WorldToPixel(vec.y));
        }
    glEnd();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.5f, 0.5f, 1, 0.7f);
    glBegin(GL_QUADS);
        for(auto vec : this->waterMask){
            glVertex2f(this->physics->WorldToPixel(vec.x), this->physics->WorldToPixel(vec.y));
        }
    glEnd();
    glDisable(GL_BLEND);

    if(this->reveal > 0){
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(0, 0, 0, this->reveal);
        glBegin(GL_QUADS);
            for(auto vec : this->levelFog){
                glVertex2f(this->physics->WorldToPixel(vec.x), this->physics->WorldToPixel(vec.y));
            }
        glEnd();
        glDisable(GL_BLEND);
    }

    if(this->debugView){
        this->RenderBody(this->body);
    }
}

void Level::RenderMask(SDL_Renderer* renderer){
    if(this->reveal > 0){
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(0, 0, 0, this->reveal);
        glBegin(GL_QUADS);
            for(auto vec : this->levelFog){
                glVertex2f(this->physics->WorldToPixel(vec.x), this->physics->WorldToPixel(vec.y));
            }
        glEnd();
        glDisable(GL_BLEND);
    }
}

void Level::Update(ppInput* input){
}

void Level::Reveal(long revealTime){
    if(this->reveal == 0){
        return;
    }
    this->reveal = revealTime / 3000.0f;
}

float Level::GetReveal(){
    return this->reveal;
}
