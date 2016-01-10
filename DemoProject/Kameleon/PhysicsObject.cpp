#include "PhysicsObject.hpp"

PhysicsObject::PhysicsObject(ppPhysics* physics){
	this->physics = physics;
	this->debugView = false;
}

void PhysicsObject::RenderCircle(ppGraphics* graphics, b2Vec2 center, float radius, ppColor* color){
	graphics->SetColor(new ppColor(color->GetRf()*0.5f, color->GetGf()*0.5f, color->GetBf()*0.5f, 0.5f));
	graphics->FillOval(this->physics->WorldToPixel(center.x - radius), this->physics->WorldToPixel(center.y - radius), this->physics->WorldToPixel(radius * 2), this->physics->WorldToPixel(radius * 2));

	graphics->SetColor(new ppColor(color->GetRf(), color->GetGf(), color->GetBf()));
	graphics->DrawOval(this->physics->WorldToPixel(center.x - radius), this->physics->WorldToPixel(center.y - radius), this->physics->WorldToPixel(radius * 2), this->physics->WorldToPixel(radius * 2));

	graphics->DrawLine(this->physics->WorldToPixel(center.x), this->physics->WorldToPixel(center.y), this->physics->WorldToPixel(center.x + radius), this->physics->WorldToPixel(center.y));
}

void PhysicsObject::RenderEdge(ppGraphics* graphics, b2Vec2 v1, b2Vec2 v2, ppColor* color){
	graphics->SetColor(new ppColor(color->GetRf(), color->GetGf(), color->GetBf()));
	graphics->DrawLine(this->physics->WorldToPixel(v1.x), this->physics->WorldToPixel(v1.y), this->physics->WorldToPixel(v2.x), this->physics->WorldToPixel(v2.y));
}

void PhysicsObject::RenderPolygon(ppGraphics* graphics, std::vector<b2Vec2> vertices, ppColor* color){
	graphics->SetColor(new ppColor(color->GetRf()*0.5f, color->GetGf()*0.5f, color->GetBf()*0.5f, 0.5f));
	for(auto vertex : vertices){
		graphics->SetVertex(this->physics->WorldToPixel(vertex.x), this->physics->WorldToPixel(vertex.y));
	}
	graphics->FillPolygon();
	graphics->SetColor(new ppColor(color->GetRf(), color->GetGf(), color->GetBf()));
	graphics->DrawPolygon();
}

void PhysicsObject::RenderChain(ppGraphics* graphics, std::vector<b2Vec2> vertices, ppColor* color){
	graphics->SetColor(new ppColor(color->GetRf(), color->GetGf(), color->GetBf()));
	for(auto vertex : vertices){
		graphics->SetVertex(this->physics->WorldToPixel(vertex.x), this->physics->WorldToPixel(vertex.y));
	}
	graphics->DrawStrip();
	for(auto vertex : vertices){
		this->RenderCircle(graphics, vertex, this->physics->PixelToWorld(3), color);
	}
}

void PhysicsObject::RenderBody(ppGraphics* graphics, b2Body* body){
	b2Transform bdTransform = body->GetTransform();
	graphics->PushContext();
	graphics->Translate(this->physics->WorldToPixel(bdTransform.p.x), this->physics->WorldToPixel(bdTransform.p.y));
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

void PhysicsObject::SetDebugView(bool debugView){
	this->debugView = debugView;
}
