#include "Testbed.h"

#include <sstream>
#include "GUI/Controls.h"

void ppTestBed::OnInit(){
	this->help = 0;
	this->cd = 0;
	this->physics = new ppPhysics(60, 0, 10);
	this->gui = new ppGUI();
	this->gui->AddControl("text", new ppLabel(10, 50));

	b2BodyDef *myBodyDef = new b2BodyDef();
	myBodyDef->type = b2_dynamicBody;
	myBodyDef->position.Set(0, 0);
	myBodyDef->angle = 0;
	b2Body* dynamicBody = this->physics->GetWorld()->CreateBody(myBodyDef);

	b2CircleShape circleShape;
	circleShape.m_radius = 1;

	dynamicBody->CreateFixture(&circleShape, 1.0f);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(1,1);

	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.density = 1;
	dynamicBody->CreateFixture(&boxFixtureDef);
}

void ppTestBed::RenderCircle(b2Vec2 center, int radius, ppColor* color){
	const float32 k_segments = 16.0f;
	const float32 k_increment = 2.0f * b2_pi / k_segments;
	float32 theta = 0.0f;
	glColor3f(color->GetRf(), color->GetGf(), color->GetBf());
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < k_segments; ++i){
		b2Vec2 v = center + radius * b2Vec2(cosf(theta), sinf(theta));
		glVertex2f(v.x, v.y);
		theta += k_increment;
	}
	glEnd();
}

void ppTestBed::RenderEdge(b2Vec2 v1, b2Vec2 v2, ppColor* color){

}

void ppTestBed::RenderPolygon(std::vector<b2Vec2> vertices, ppColor* color){

}

void ppTestBed::RenderChain(std::vector<b2Vec2> vertices, ppColor* color){

}

void ppTestBed::OnRender(SDL_Renderer* renderer, int delta){
	std::stringstream ss;
	ss << "FPS: " << this->GetGame()->GetFPS() << " [" << this->GetGame()->GetAvgRenderTime() << "ms]\n";
	ss << "UPS: " << this->GetGame()->GetUPS() << " [" << this->GetGame()->GetAvgUpdateTime() << "ms]\n";
	ss << "Help: " << this->help << "\n";
	ss << "Cooldown: " << this->cd;
	if(this->gui->GetDefaultFont()){
		this->gui->GetDefaultFont()->Render(10, 10, ss.str().c_str(), renderer);
	}

	for(b2Body* bd=this->physics->GetWorld()->GetBodyList();bd!=NULL;bd=bd->GetNext()){
		b2Vec2 bdPos = bd->GetPosition();
		b2Transform bdTransform = bd->GetTransform();
		ppColor* color = new ppColor(255, 0, 0);
		for(b2Fixture* ft=bd->GetFixtureList();ft!=NULL;ft=ft->GetNext()){
			switch(ft->GetType()){
				case b2Shape::e_circle:
				{
					b2CircleShape* circle = (b2CircleShape*)ft->GetShape();
					b2Vec2 center = b2Mul(bdTransform, circle->m_p);

					//Draw
					this->RenderCircle(bdPos+center, circle->m_radius, color);
				}
				break;
				case b2Shape::e_edge:
				{
					b2EdgeShape* edge = (b2EdgeShape*)ft->GetShape();

					//Draw
					//this->RenderEdge(edge->m_vertex1, edge->m_vertex2, color);
				}
				break;
				case b2Shape::e_polygon:
				{
					b2PolygonShape* poly = (b2PolygonShape*)ft->GetShape();
					std::vector<b2Vec2> vertices;
					for(int i=0;i<poly->m_count;i++){
						vertices.push_back(b2Mul(bdTransform, poly->m_vertices[i]));
					}

					//Draw
					//this->RenderPolygon(vertices, color);

					SDL_Rect* rect = new SDL_Rect();
					rect->x = (bdPos.x*30);
					rect->y = (bdPos.y*30);
					rect->w = 20;
					rect->h = 20;
					SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
					SDL_RenderFillRect(renderer, rect);
				}
				break;
				case b2Shape::e_chain:
				{
					b2ChainShape* chain = (b2ChainShape*)ft->GetShape();
					std::vector<b2Vec2> vertices;
					for(int i=0;i<chain->m_count;i++){
						vertices.push_back(b2Mul(bdTransform, chain->m_vertices[i]));
					}

					//Draw
					//this->RenderChain(vertices, color);
				}
				break;
				default: break;
			}
		}
	}

	this->gui->Render(renderer);
}

void ppTestBed::OnUpdate(ppInput* input, int delta){
	if(input->IsKeyDown(SDL_SCANCODE_H, 10)){
		this->help=(this->help+1) % 3;
	}
	this->cd = input->GetKeyCooldown();
	this->physics->Update();
	this->gui->Update(input);
}