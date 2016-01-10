#include "Testbed.hpp"

#include <sstream>
#include <ParticlePlay/GUI/Controls.hpp>

void ppTestBed::OnInit(){
	this->help = 0;
	this->cd = 0;
	this->fx = -1;
	this->fy = -1;
	this->tx = 0;
	this->ty = 0;
	this->px = 0;
	this->py = 0;
	this->physics = new ppPhysics(0, 10);
	this->gui = new ppGUI();
}

void ppTestBed::RenderCircle(ppGraphics* graphics, b2Vec2 center, float radius, ppColor* color){
	graphics->SetColor(new ppColor(color->GetRf()*0.5f, color->GetGf()*0.5f, color->GetBf()*0.5f, 0.5f));
	graphics->FillOval(this->physics->WorldToPixel(center.x - radius), this->physics->WorldToPixel(center.y - radius), this->physics->WorldToPixel(radius * 2), this->physics->WorldToPixel(radius * 2));

	graphics->SetColor(new ppColor(color->GetRf(), color->GetGf(), color->GetBf()));
	graphics->DrawOval(this->physics->WorldToPixel(center.x - radius), this->physics->WorldToPixel(center.y - radius), this->physics->WorldToPixel(radius * 2), this->physics->WorldToPixel(radius * 2));

	graphics->DrawLine(this->physics->WorldToPixel(center.x), this->physics->WorldToPixel(center.y), this->physics->WorldToPixel(center.x + radius), this->physics->WorldToPixel(center.y));
}

void ppTestBed::RenderEdge(ppGraphics* graphics, b2Vec2 v1, b2Vec2 v2, ppColor* color){
	graphics->SetColor(new ppColor(color->GetRf(), color->GetGf(), color->GetBf()));
	graphics->DrawLine(this->physics->WorldToPixel(v1.x), this->physics->WorldToPixel(v1.y), this->physics->WorldToPixel(v2.x), this->physics->WorldToPixel(v2.y));
}

void ppTestBed::RenderPolygon(ppGraphics* graphics, std::vector<b2Vec2> vertices, ppColor* color){
	graphics->SetColor(new ppColor(color->GetRf()*0.5f, color->GetGf()*0.5f, color->GetBf()*0.5f, 0.5f));
	for(auto vertex : vertices){
		graphics->SetVertex(this->physics->WorldToPixel(vertex.x), this->physics->WorldToPixel(vertex.y));
	}
	graphics->FillPolygon();
	graphics->SetColor(new ppColor(color->GetRf(), color->GetGf(), color->GetBf()));
	graphics->DrawPolygon();
}

void ppTestBed::RenderChain(ppGraphics* graphics, std::vector<b2Vec2> vertices, ppColor* color){
	graphics->SetColor(new ppColor(color->GetRf(), color->GetGf(), color->GetBf()));
	for(auto vertex : vertices){
		graphics->SetVertex(this->physics->WorldToPixel(vertex.x), this->physics->WorldToPixel(vertex.y));
	}
	graphics->DrawStrip();
	for(auto vertex : vertices){
		this->RenderCircle(graphics, vertex, this->physics->PixelToWorld(3), color);
	}
}

void ppTestBed::RenderBody(ppGraphics* graphics, b2Body* body){
	b2Transform bdTransform = body->GetTransform();
	graphics->PushContext();
	graphics->Translate(this->physics->WorldToPixel(bdTransform.p.x)+this->px, this->physics->WorldToPixel(bdTransform.p.y)+this->py);
	graphics->Rotate(bdTransform.q.GetAngle());
	ppColor* color = new ppColor(0.9f, 0.7f, 0.7f);
	if(!body->IsActive()){
		color = new ppColor(0.5f, 0.5f, 0.3f);
	}else if(body->GetType()==b2_staticBody){
		color = new ppColor(0.5f, 0.9f, 0.3f);
	}else if(body->GetType()==b2_kinematicBody){
		color = new ppColor(0.5f, 0.5f, 0.9f);
	}else if(!body->IsAwake()){
		color = new ppColor(0.6f, 0.6f, 0.6f);
	}
	for(b2Fixture* ft=body->GetFixtureList();ft!=NULL;ft=ft->GetNext()){
		switch(ft->GetType()){
			case b2Shape::e_circle:
			{
				b2CircleShape* circle = (b2CircleShape*)ft->GetShape();
				this->RenderCircle(graphics, circle->m_p, circle->m_radius, color);
			}
			break;
			case b2Shape::e_edge:
			{
				b2EdgeShape* edge = (b2EdgeShape*)ft->GetShape();
				this->RenderEdge(graphics, edge->m_vertex1, edge->m_vertex2, color);
			}
			break;
			case b2Shape::e_polygon:
			{
				b2PolygonShape* poly = (b2PolygonShape*)ft->GetShape();
				std::vector<b2Vec2> vertices;
				for(int i=0;i<poly->m_count;i++){
					vertices.push_back(poly->m_vertices[i]);
				}
				this->RenderPolygon(graphics, vertices, color);
			}
			break;
			case b2Shape::e_chain:
			{
				b2ChainShape* chain = (b2ChainShape*)ft->GetShape();
				std::vector<b2Vec2> vertices;
				for(int i=0;i<chain->m_count;i++){
					vertices.push_back(chain->m_vertices[i]);
				}
				this->RenderChain(graphics, vertices, color);
			}
			break;
			default: break;
		}
	}
	graphics->PopContext();
}

void ppTestBed::OnRender(ppGraphics* graphics, int delta){
	graphics->PushContext();
	graphics->SetColor(new ppColor(1.0f, 1.0f, 1.0f));
	std::stringstream ss;
	ss << "FPS: " << this->GetGame()->GetFPS() << " [" << this->GetGame()->GetAvgRenderTime() << "ms]\n";
	ss << "UPS: " << this->GetGame()->GetUPS() << " [" << this->GetGame()->GetAvgUpdateTime() << "ms]\n";
	ss << "Help: " << this->help << "\n";
	ss << "Cooldown: " << this->cd << "\n";
	ss << "Position: " << (this->px) << ", " << (this->py) << "\n";
	ss << "PTM: " << this->physics->GetPTM();
	if(this->gui->GetDefaultFont()){
		this->gui->GetDefaultFont()->Render(10, 10, ss.str().c_str(), graphics);
	}

	for(b2Body* bd=this->physics->GetWorld()->GetBodyList();bd!=NULL;bd=bd->GetNext()){
		this->RenderBody(graphics, bd);
	}

	this->gui->Render(graphics);
	graphics->PopContext();
}

void ppTestBed::OnUpdate(ppInput* input, int delta){
	if(input->IsKeyDown(SDL_SCANCODE_H, 10)){
		this->help=(this->help+1) % 3;
	}else if(input->IsKeyDown(SDL_SCANCODE_R, 10)){
		this->SetNeedInit(true);
		this->GetGame()->EnterState(this);
	}
	if(input->IsMouseDown(SDL_BUTTON_LEFT, 30)){
		b2BodyDef* myBodyDef = new b2BodyDef();

		myBodyDef->type = b2_dynamicBody;
		myBodyDef->position.Set(this->physics->PixelToWorld(input->GetMouseX()-this->px), this->physics->PixelToWorld(input->GetMouseY()-this->py));
		b2Body* boxBody = this->physics->GetWorld()->CreateBody(myBodyDef);

		b2PolygonShape boxShape;
		boxShape.SetAsBox(1,1);

		b2FixtureDef boxFixtureDef;
		boxFixtureDef.shape = &boxShape;
		boxFixtureDef.density = 1;
		boxBody->CreateFixture(&boxFixtureDef);
	}
	int scrolly = input->GetScrollY();
	if(scrolly!=0){
		this->physics->SetPTM(this->physics->GetPTM()+scrolly);
		if(this->physics->GetPTM()<1){
			this->physics->SetPTM(1);
		}
	}
	if(input->IsMouseDown(SDL_BUTTON_RIGHT)){
		if(this->fx<0){
			this->fx = input->GetMouseX();
		}else{
			this->px = this->tx+input->GetMouseX()-fx;
		}
		if(this->fy<0){
			this->fy = input->GetMouseY();
		}else{
			this->py = this->ty+input->GetMouseY()-fy;
		}
	}else if(input->IsMouseDown(SDL_BUTTON_MIDDLE)){
		if(this->fx<0){
			this->fx = input->GetMouseX();
		}else{
			this->px -= (input->GetMouseX()-fx)/2;
		}
		if(this->fy<0){
			this->fy = input->GetMouseY();
		}else{
			this->py -= (input->GetMouseY()-fy)/2;
		}
	}else{
		this->tx = this->px;
		this->ty = this->py;
		this->fx = -1;
		this->fy = -1;
	}
	this->cd = input->GetKeyCooldown();
	this->physics->Update(delta);
	this->gui->Update(input);
}
