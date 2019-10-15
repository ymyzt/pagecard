#include "Card3D.h"
//#include "Card3D_Grid.h"
//#include "cocostudio/CocoStudio.h"
//#include "ui/CocosGUI.h"
#define min(x,y) (((x) > (y)) ? (y) : (x))
#define max(x,y) (((x) > (y)) ? (x) : (y))
#define pi 3.1415926
Card3D::Card3D()
	:_beginPos(Vec2::ZERO),
	_line({0,0.0f,0.0f}),
	_r(20)
{
}
Card3D::~Card3D()
{
}
Card3D * Card3D::create(const std::string& pkbgpath, const std::string& pkpath,  Size size) {
	Card3D *card3d = new Card3D();
	if (card3d &&card3d->init(pkbgpath, pkpath,size)) {
		card3d->autorelease();
		return card3d;
	}
	delete card3d;
	card3d = nullptr;
	return nullptr;
}
bool Card3D::init(const std::string & pkbgpath, const std::string & pkpath,  Size & size) {
	_pk = Sprite::create(pkpath);
	_pkbg = Sprite::create(pkbgpath);
	if (!_pk || !_pkbg) {
		return false;
	}
	setAnchorPoint(Vec2(0.5, 0.5));
	setContentSize(_pkbg->getContentSize());
	_gridSize = size;
	_pk->retain();
	_pkbg->retain();

	auto listener1 = EventListenerTouchOneByOne::create();
	// trigger when you push down
	listener1->onTouchBegan = [=](Touch* touch, Event* event) {
		_beginPos = touch->getLocation();
		return true; // if you are consuming it
	};
	// trigger when moving touch
	listener1->onTouchMoved = [=](Touch* touch, Event* event) {
		// your code
		
		
		auto pos = touch->getLocation();
		Rect rect = getBoundingBox();
		bool isin = rect.containsPoint(pos);
		//if (isin) {
			setLine(pos, _beginPos);
			refData();
			//_beginPos = pos;
		//}
		//log("rect x:%f,y:%f,width:%f,height:%f", rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
		log("position x:%f,y:%f", pos.x, pos.y);
		log("isin :%d", isin?1:0);
		//CCLOG("onTouchMoved x:%f,y:%f", pos.x, pos.y);
	};
	// trigger when you let up
	listener1->onTouchEnded = [=](Touch* touch, Event* event) {
		// your code
		//auto pos = touch->getLocation();
		//beganPos = Vec2::ZERO;
		//CCLOG("onTouchEnded x:%f,y:%f", pos.x, pos.y);
		_beginPos = Vec2::ZERO;
		refData();
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);






	return true;
}
// _line.type 1,2,3,4 (左右) 上 下
void Card3D::setLine(Vec2 &dst, Vec2 &src) {
// 	_line.x = dst.x;
// 	_line.y = dst.y;
	if (dst.y == src.y) {
		_line.type = dst.x > src.x ? 1 : 2;
		_line.b = dst.x;
	}
	else {
		float k = (dst.y - src.y) / (dst.x - src.x);
			_line.type = dst.y > src.y ? 3 : 4;
			_line.k = -1 / k;
			_line.b =  dst.y - dst.x*_line.k;
	}
	log("beginx:%f,beginy:%f", _beginPos.x,_beginPos.y);
	log("type:%d k:%f,b:%f", _line.type, _line.k, _line.b);
}

void Card3D::initSize() {
	setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP));
	Rect _gridRect = this->getBoundingBox();
	Vec2 _step;
	_step.x = _gridRect.size.width / _gridSize.width;
	_step.y = _gridRect.size.height / _gridSize.height;
	int x, y, i;
	unsigned int numOfPoints = (_gridSize.width+1) * (_gridSize.height+1);
	_idxLength = _gridSize.width * _gridSize.height * 6;
	_vctData = new V3F_C4B_T2F[numOfPoints];
	_vctData2 = new V3F_C4B_T2F[numOfPoints];
	_indices = new GLushort[_idxLength];//(GLushort*)malloc(_gridSize.width * _gridSize.height * sizeof(GLushort) * 6);
	_indices2 = new GLushort[_idxLength];
	_vctLength = numOfPoints;
	
	for (y = 0; y < _gridSize.height; ++y)
	{
			for (x = 0; x < _gridSize.width; ++x)
		{
			int idx = (y * (_gridSize.width+1)) + x;
 			GLfloat x1 = x * _step.x + _gridRect.origin.x;
			GLfloat x2 = x1 + _step.x;
 			GLfloat y1 = y * _step.y + _gridRect.origin.y;
			GLfloat y2 = y1 + _step.y ;
			Vec3 v1(x1,y1,0);
			Vec3 v2(x2, y1, 0);
			Vec3 v3(x1, y2, 0);
			Vec3 v4(x2, y2, 0);
			Tex2F t1(x / (_gridSize.width), 1-y / (_gridSize.height));//纹理方向相反
			Tex2F t2((x+1) / (_gridSize.width), 1-y / (_gridSize.height));
			Tex2F t3(x / (_gridSize.width), 1-(y+1) / (_gridSize.height));
			Tex2F t4((x+1) / (_gridSize.width ),1-(y+1) / (_gridSize.height));
			V3F_C4B_T2F vct1 = { v1,Color4B::WHITE,t1};
			V3F_C4B_T2F vct2 = { v2,Color4B::WHITE,t2 };
			V3F_C4B_T2F vct3 = { v3,Color4B::WHITE,t3 };
			V3F_C4B_T2F vct4 = { v4,Color4B::WHITE,t4 };
			_vctData[idx] = vct1;
			if (x == _gridSize.width - 1) {
				_vctData[idx+1] = vct2;
			}
			if (y == _gridSize.height - 1) {
				int idx2 = idx + (_gridSize.width + 1);
				_vctData[idx2] = vct3;
				if (x == _gridSize.width - 1) {
					_vctData[idx2+1] = vct4;
				}
			}
			GLushort a1, a2, a3, a4;
			a1 = x+ y*(_gridSize.width + 1);
			a2 = x+1+y*(_gridSize.width + 1);;
			a3 = x + (y + 1)*(_gridSize.width + 1);
			a4 = x+1 + (y + 1)*(_gridSize.width + 1);
			GLushort idx1[] = { a1,a2,a3,a4,a3,a2 };
			GLushort idx2[] = { a1,a3,a2,a4,a2,a3 };
			int num = 6 * (y*_gridSize.width + x);
			for (i = 0;i<6;i++)
			{
				_indices[num + i] = idx1[i];
				_indices2[num + i] = idx2[i];
			}
		}
	}



	memcpy(_vctData2, _vctData, sizeof(V3F_C4B_T2F)*_vctLength);
}
V3F_C4B_T2F Card3D::getPoint(Vec2 pos) {
	int idx = (_gridSize.width+1)*pos.y + pos.x;
	return _vctData[idx];
}
V3F_C4B_T2F Card3D::setPoint(Vec2 pos, V3F_C4B_T2F value) {
	int idx = (_gridSize.width + 1)*pos.y + pos.x;
	V3F_C4B_T2F oldval = _vctData[idx];
	_vctData[idx] = value;
	return oldval;
}
V3F_C4B_T2F Card3D::getPoint2(Vec2 pos) {
	int idx = (_gridSize.width + 1)*pos.y + pos.x;
	return _vctData2[idx];
}
V3F_C4B_T2F Card3D::setPoint2(Vec2 pos, V3F_C4B_T2F value) {
	int idx = (_gridSize.width + 1)*pos.y + pos.x;
	V3F_C4B_T2F oldval = _vctData2[idx];
	_vctData2[idx] = value;
	return oldval;
}
void Card3D::draw(Renderer * renderer, const Mat4 & transform, uint32_t flags){
	_customcommand.init(_globalZOrder);
	_customcommand.func = CC_CALLBACK_0(Card3D::onDraw,this, transform);
	renderer->addCommand(&_customcommand);
}
void Card3D::onDraw(const Mat4 & transform)
{
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	
	GLuint _buffersVAO;
	GLuint _buffersVBO;
	GLuint _buffersEBO;
	//Bind VAO
	glGenVertexArrays(1, &_buffersVAO);
	glBindVertexArray(_buffersVAO);
	//Set VBO data
	glGenVertexArrays(1, &_buffersVBO);
	glBindBuffer(GL_ARRAY_BUFFER,_buffersVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(V3F_C4B_T2F)*_vctLength , _vctData, GL_STATIC_DRAW);

	CHECK_GL_ERROR_DEBUG();
	//glBufferData(GL_ARRAY_BUFFER, numOfPoints, _vertices, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_POSITION);
	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(V3F_C4B_T2F), (GLvoid *)offsetof(V3F_C4B_T2F, vertices));
	CHECK_GL_ERROR_DEBUG();
	//glBufferData(GL_ARRAY_BUFFER, numOfPoints, _color4B, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_COLOR);
	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(V3F_C4B_T2F), (GLvoid *)offsetof(V3F_C4B_T2F, colors));
	CHECK_GL_ERROR_DEBUG();
	// tex coords
	//glBufferData(GL_ARRAY_BUFFER, numOfPoints, _texCoordinates, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_TEX_COORD);
	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, sizeof(V3F_C4B_T2F), (GLvoid *)offsetof(V3F_C4B_T2F, texCoords));

	CHECK_GL_ERROR_DEBUG();
	//Set EBO data
	glGenVertexArrays(1, &_buffersEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffersEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort)*_idxLength, _indices, GL_STATIC_DRAW);
	


	


	CHECK_GL_ERROR_DEBUG();
	auto program =  getGLProgram();
	program->use();
	program->setUniformsForBuiltins();


	GL::bindTexture2D(_pkbg->getTexture()->getName());
	glDrawElements(GL_TRIANGLES, _idxLength, GL_UNSIGNED_SHORT, (GLvoid*)0);


	GL::bindTexture2D(_pk->getTexture()->getName());
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort)*_idxLength, _indices2, GL_STATIC_DRAW);
	glDrawElements(GL_TRIANGLES, _idxLength, GL_UNSIGNED_SHORT, (GLvoid*)0);

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void Card3D::refData()
{
	auto rect = _pkbg->getBoundingBox();
	for (int x = 0;x<_gridSize.width+1;x++)
	{
		for (int y = 0; y < _gridSize.height + 1; y++)
		{
			V3F_C4B_T2F p = getPoint2(Vec2(x, y));
			Mat4 trans = Mat4::IDENTITY;
			if (!_beginPos.equals(Vec2::ZERO)) {
				if (_line.type == 1 ) {
 					if (p.vertices.x < _line.b) {
						float l = _line.b - p.vertices.x;
						float x3 = 0;
						float z3 = 0;
						if (l > _r*pi) {
							x3 = 2 * l - _r * pi;
							z3 = 2 * _r;
						}
						else {
							x3 = l -  sin(pi * l / (_r*pi))*_r;
							z3 = _r - cos(pi * l / (_r*pi))*_r;
						}
						trans.translate(x3, 0, z3);
						//trans.translate((_line.b - p.vertices.x) * 2,  0, 0);
					}
				}
				else if (_line.type == 2) {
					if (p.vertices.x > _line.b) {
						float l =  p.vertices.x - _line.b;
						float x3 = 0;
						float z3 = 0;
						if (l > _r*pi) {
							x3 = -(2 * l - _r * pi);
							z3 = 2 * _r;
						}
						else {
							x3 = -(l - sin(pi * l / (_r*pi))*_r);
							z3 = _r - cos(pi * l / (_r*pi))*_r;
						}
						trans.translate(x3, 0, z3);
						//trans.translate((_line.b - p.vertices.x) * 2,  0, 0);
					}
				}
				else  {
					//float len = _beginPos.distance(Vec2(_line.x, _line.y));
					float k1 = _line.k;
					float b1 = _line.b;
					float x1 = p.vertices.x;//_beginPos.x;
					float y1 = p.vertices.y;//_beginPos.y;
					
					float x2 = (k1 * y1 + x1 - k1 * b1) / (k1*k1 + 1);
					float y2 = k1 * x2 + b1;

					Vec3 v2(x2, y2, 0);//垂足
					Vec3 v1(x1, y1, 0);//顶点

					float l = v1.distance(v2);
					float w = v2.x - v1.x;
					float h = v2.y - v1.y;


					float  x3 = 0, y3 = 0, z3 = 0,len = 0;
					if (l >= (pi*_r)) {
						len = 2 * l - pi * _r;
						x3 = len / (2 * l) * 2 * w;
						y3 = len / (2 * l) * 2 * h;
						z3 = 2 * _r;
					}
					else {
						len = _r * sin(l / (pi*_r) * pi);
						x3 = (l - len) / l * w;
						y3 = (l - len) / l * h;
						z3 = _r - _r * cos(l / (pi*_r) * pi);
					}
					if (_line.type == 3 && y1 < (x1 * _line.k + _line.b)) {
						trans.translate(x3, y3, z3);
						//trans.translate((x2 - p.vertices.x) * 2, (y2 - p.vertices.y) * 2, 0);
					}
					else if (_line.type == 4 && y1 > (x1 * _line.k + _line.b)) {
						trans.translate(x3, y3, z3);
						//trans.translate((x2 - p.vertices.x) * 2, (y2 - p.vertices.y) * 2, 0);
					}
				}
			}
			trans.transformPoint(&p.vertices);
			setPoint(Vec2(x,y), p);
		}
	}
}
