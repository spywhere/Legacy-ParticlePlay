#include "Testbed.hpp"

#include <sstream>
#include "GUI/Controls.hpp"

void ppTestBed::OnInit(){
	this->ptm = 1/30.0f;
	this->help = 0;
	this->cd = 0;
	this->fx = -1;
	this->fy = -1;
	this->tx = 0;
	this->ty = 0;
	this->px = 0;
	this->py = 0;
	this->physics = new ppPhysics(60, 0, 10);
	this->gui = new ppGUI();
}

void ppTestBed::RenderCircle(b2Vec2 center, float radius, ppColor* color){
	const float32 k_segments = 16.0f;
	const float32 k_increment = 2.0f * b2_pi / k_segments;
	float32 theta = 0.0f;
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(color->GetRf()*0.5f, color->GetGf()*0.5f, color->GetBf()*0.5f, 0.5f);
	glBegin(GL_TRIANGLE_FAN);
	for (int32 i = 0; i < k_segments; ++i)
	{
		b2Vec2 v = center + radius * b2Vec2(cosf(theta), sinf(theta));
		glVertex2f(v.x/this->ptm, v.y/this->ptm);
		theta += k_increment;
	}
	glEnd();
	glDisable(GL_BLEND);

	theta = 0.0f;
	glColor4f(color->GetRf(), color->GetGf(), color->GetBf(), 1.0f);
	glBegin(GL_LINE_LOOP);
	for (int32 i = 0; i < k_segments; ++i)
	{
		b2Vec2 v = center + radius * b2Vec2(cosf(theta), sinf(theta));
		glVertex2f(v.x/this->ptm, v.y/this->ptm);
		theta += k_increment;
	}
	glEnd();

	glBegin(GL_LINES);
	glVertex2f(center.x/this->ptm, center.y/this->ptm);
	glVertex2f((center.x + radius)/this->ptm, (center.y)/this->ptm);
	glEnd();
}


void ppTestBed::RenderEdge(b2Vec2 v1, b2Vec2 v2, ppColor* color){
	glColor4f(color->GetRf(), color->GetGf(), color->GetBf(), 1.0f);
	glBegin(GL_LINES);
		glVertex2f(v1.x/this->ptm, v1.y/this->ptm);
		glVertex2f(v2.x/this->ptm, v2.y/this->ptm);
	glEnd();
}

void ppTestBed::RenderPolygon(std::vector<b2Vec2> vertices, ppColor* color){
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(color->GetRf()*0.5f, color->GetGf()*0.5f, color->GetBf()*0.5f, 0.5f);
	glBegin(GL_TRIANGLE_FAN);
	for(auto vertex : vertices){
		glVertex2f(vertex.x/this->ptm, vertex.y/this->ptm);
	}
	glEnd();
	glDisable(GL_BLEND);

	glColor4f(color->GetRf(), color->GetGf(), color->GetBf(), 1.0f);
	glBegin(GL_LINE_LOOP);
	for(auto vertex : vertices){
		glVertex2f(vertex.x/this->ptm, vertex.y/this->ptm);
	}
	glEnd();
}

void ppTestBed::RenderChain(std::vector<b2Vec2> vertices, ppColor* color){
	glColor4f(color->GetRf(), color->GetGf(), color->GetBf(), 1.0f);
	glBegin(GL_LINE_STRIP);
	for(auto vertex : vertices){
		glVertex2f(vertex.x/this->ptm, vertex.y/this->ptm);
	}
	glEnd();
	for(auto vertex : vertices){
		this->RenderCircle(vertex, 3*this->ptm, color);
	}
}

void ppTestBed::OnRender(SDL_Renderer* renderer, int delta){
	glPushMatrix();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	std::stringstream ss;
	ss << "FPS: " << this->GetGame()->GetFPS() << " [" << this->GetGame()->GetAvgRenderTime() << "ms]\n";
	ss << "UPS: " << this->GetGame()->GetUPS() << " [" << this->GetGame()->GetAvgUpdateTime() << "ms]\n";
	ss << "Help: " << this->help << "\n";
	ss << "Cooldown: " << this->cd << "\n";
	ss << "Position: " << (this->px) << ", " << (this->py) << "\n";
	ss << "MTP: " << (1/this->ptm);
	if(this->gui->GetDefaultFont()){
		this->gui->GetDefaultFont()->Render(10, 10, ss.str().c_str(), renderer);
	}

	for(b2Body* bd=this->physics->GetWorld()->GetBodyList();bd!=NULL;bd=bd->GetNext()){
		b2Vec2 bdPos = bd->GetPosition();
		b2Transform bdTransform = bd->GetTransform();
		glPushMatrix();
		glTranslatef(bdTransform.p.x/this->ptm+this->px, bdTransform.p.y/this->ptm+this->py, 0);
		glRotatef(bdTransform.q.GetAngle()*180/b2_pi, 0, 0, 1);
		ppColor* color = new ppColor(0.9f, 0.7f, 0.7f);
		if(!bd->IsActive()){
			color = new ppColor(0.5f, 0.5f, 0.3f);
		}else if(bd->GetType()==b2_staticBody){
			color = new ppColor(0.5f, 0.9f, 0.3f);
		}else if(bd->GetType()==b2_kinematicBody){
			color = new ppColor(0.5f, 0.5f, 0.9f);
		}else if(!bd->IsAwake()){
			color = new ppColor(0.6f, 0.6f, 0.6f);
		}
		for(b2Fixture* ft=bd->GetFixtureList();ft!=NULL;ft=ft->GetNext()){
			switch(ft->GetType()){
				case b2Shape::e_circle:
				{
					b2CircleShape* circle = (b2CircleShape*)ft->GetShape();
					this->RenderCircle(circle->m_p, circle->m_radius, color);
				}
				break;
				case b2Shape::e_edge:
				{
					b2EdgeShape* edge = (b2EdgeShape*)ft->GetShape();
					this->RenderEdge(edge->m_vertex1, edge->m_vertex2, color);
				}
				break;
				case b2Shape::e_polygon:
				{
					b2PolygonShape* poly = (b2PolygonShape*)ft->GetShape();
					std::vector<b2Vec2> vertices;
					for(int i=0;i<poly->m_count;i++){
						vertices.push_back(poly->m_vertices[i]);
					}
					this->RenderPolygon(vertices, color);
				}
				break;
				case b2Shape::e_chain:
				{
					b2ChainShape* chain = (b2ChainShape*)ft->GetShape();
					std::vector<b2Vec2> vertices;
					for(int i=0;i<chain->m_count;i++){
						vertices.push_back(chain->m_vertices[i]);
					}
					this->RenderChain(vertices, color);
				}
				break;
				default: break;
			}
		}
		glPopMatrix();
	}

	this->gui->Render(renderer);
	glPopMatrix();
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
		myBodyDef->position.Set((input->GetMouseX()-this->px)*this->ptm, (input->GetMouseY()-this->py)*this->ptm);
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
		this->ptm = 1.0f/((1/this->ptm)+scrolly);
		if(1/this->ptm<1){
			this->ptm=1;
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
	this->physics->Update();
	this->gui->Update(input);
}
