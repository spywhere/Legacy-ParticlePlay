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

    this->levelMask.push_back(b2Vec2(this->physics->PixelToWorld(-625), this->physics->PixelToWorld(20)));
    this->levelMask.push_back(b2Vec2(this->physics->PixelToWorld(225), this->physics->PixelToWorld(530)));

    this->levelMask.push_back(b2Vec2(this->physics->PixelToWorld(-400), this->physics->PixelToWorld(400)));
    this->levelMask.push_back(b2Vec2(this->physics->PixelToWorld(250), this->physics->PixelToWorld(100)));

    this->levelMask.push_back(b2Vec2(this->physics->PixelToWorld(-625), this->physics->PixelToWorld(500)));
    this->levelMask.push_back(b2Vec2(this->physics->PixelToWorld(1825), this->physics->PixelToWorld(400)));

    this->levelMask.push_back(b2Vec2(this->physics->PixelToWorld(300), this->physics->PixelToWorld(325)));
    this->levelMask.push_back(b2Vec2(this->physics->PixelToWorld(50), this->physics->PixelToWorld(80)));

    this->levelMask.push_back(b2Vec2(this->physics->PixelToWorld(150), this->physics->PixelToWorld(400)));
    this->levelMask.push_back(b2Vec2(this->physics->PixelToWorld(500), this->physics->PixelToWorld(500)));

    this->levelMask.push_back(b2Vec2(this->physics->PixelToWorld(650), this->physics->PixelToWorld(20)));
    this->levelMask.push_back(b2Vec2(this->physics->PixelToWorld(550), this->physics->PixelToWorld(880)));

    this->levelMask.push_back(b2Vec2(this->physics->PixelToWorld(300), this->physics->PixelToWorld(20)));
    this->levelMask.push_back(b2Vec2(this->physics->PixelToWorld(350), this->physics->PixelToWorld(230)));

    this->levelFog.push_back(b2Vec2(this->physics->PixelToWorld(-650), this->physics->PixelToWorld(20)));
    this->levelFog.push_back(b2Vec2(this->physics->PixelToWorld(975), this->physics->PixelToWorld(880)));

    this->waterMask.push_back(b2Vec2(this->physics->PixelToWorld(-150), 40.25f));
    this->waterMask.push_back(b2Vec2(this->physics->PixelToWorld(300), this->physics->PixelToWorld(500) - 40.25f));

	this->body->CreateFixture(chainShape, 1.0f);

    this->vine1 = new ppImage("tmpres/Kameleon/Assets/Image 1298.png");
    this->vine2 = new ppImage("tmpres/Kameleon/Assets/Image 1318.png");
    this->vine3 = new ppImage("tmpres/Kameleon/Assets/Image 1321.png");

    this->tree1 = new ppImage("tmpres/Kameleon/Assets/Image 1396.png");
    this->tree2 = new ppImage("tmpres/Kameleon/Assets/Image 1394.png");
}

void Level::Render(ppGraphics* graphics){
    this->vine1->Render(graphics, this->physics->WorldToPixel(45), this->physics->WorldToPixel(38));
    this->vine2->Render(graphics, this->physics->WorldToPixel(43), this->physics->WorldToPixel(25));
    this->vine2->Render(graphics, this->physics->WorldToPixel(49), this->physics->WorldToPixel(25));
    this->vine3->Render(graphics, this->physics->WorldToPixel(-35), this->physics->WorldToPixel(38));
    this->tree1->Render(graphics, this->physics->WorldToPixel(20), this->physics->WorldToPixel(30));
    this->tree2->Render(graphics, this->physics->WorldToPixel(-20), this->physics->WorldToPixel(30));

    graphics->SetColor(new ppColor(0.0f, 0.0f, 0.0f));
    b2Vec2 pos;
    bool gotPos = false;
    for(auto vec : this->levelMask){
        if(gotPos){
            graphics->FillRect(this->physics->WorldToPixel(pos.x), this->physics->WorldToPixel(pos.y), this->physics->WorldToPixel(vec.x), this->physics->WorldToPixel(vec.y));
        }else{
            pos = vec;
        }
        gotPos = !gotPos;
    }

    graphics->SetColor(new ppColor(0.5f, 0.5f, 1, 0.7f));
    for(auto vec : this->waterMask){
        if(gotPos){
            graphics->FillRect(this->physics->WorldToPixel(pos.x), this->physics->WorldToPixel(pos.y), this->physics->WorldToPixel(vec.x), this->physics->WorldToPixel(vec.y));
        }else{
            pos = vec;
        }
        gotPos = !gotPos;
    }

    if(this->reveal > 0){
        graphics->SetColor(new ppColor(0, 0, 0, this->reveal));
        for(auto vec : this->levelFog){
            if(gotPos){
                graphics->FillRect(this->physics->WorldToPixel(pos.x), this->physics->WorldToPixel(pos.y), this->physics->WorldToPixel(vec.x), this->physics->WorldToPixel(vec.y));
            }else{
                pos = vec;
            }
            gotPos = !gotPos;
        }
    }

    if(this->debugView){
        this->RenderBody(this->body);
    }
}

void Level::RenderMask(ppGraphics* graphics){
    if(this->reveal > 0){
        graphics->SetColor(new ppColor(0, 0, 0, this->reveal));
        b2Vec2 pos;
        bool gotPos = false;
        for(auto vec : this->levelFog){
            if(gotPos){
                graphics->FillRect(this->physics->WorldToPixel(pos.x), this->physics->WorldToPixel(pos.y), this->physics->WorldToPixel(vec.x), this->physics->WorldToPixel(vec.y));
            }else{
                pos = vec;
            }
            gotPos = !gotPos;
        }
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
