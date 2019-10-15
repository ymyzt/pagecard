#ifndef _CARD3D_H_
#define  _CARD3D_H_
#include "cocos2d.h"
//#include "Card3D_Sprite.h"
// struct V3_T2_IDX6_IDXT6
// {
// 	Vec3 _vertices;
// 	Vec2 _texCoordinates;
//	GLushort _indices[6];
// 	GLushort _indices2[6];
// 
// }; 



USING_NS_CC;
struct _Line {
	int type;
	float k;
	float b;
};
class Card3D :public Node
{
public:
	static Card3D *create(const std::string& pkbgpath, const std::string& pkpath, Size size = Size(2,2));
	bool init(const std::string& pkbgpath, const std::string& pkpath,Size &size);
	virtual void draw(Renderer *renderer, const Mat4& transform, uint32_t flags);
	void initSize();
	Card3D();
	~Card3D();
private:
	Sprite *_pk;
	Sprite *_pkbg;
	Size _gridSize;
	float _r;


	void onDraw(const Mat4 & transform);
	V3F_C4B_T2F getPoint(Vec2 pos);
	V3F_C4B_T2F setPoint(Vec2 pos, V3F_C4B_T2F value);
	V3F_C4B_T2F getPoint2(Vec2 pos);
	V3F_C4B_T2F setPoint2(Vec2 pos, V3F_C4B_T2F value);

	//Vec2 *_texCoordinates;
	//Vec3 *_vertices;
	//Vec3 *_gridVertices;
	//Color4B *_color4B;
	GLushort *_indices;
	GLushort *_indices2;
	V3F_C4B_T2F *_vctData;
	V3F_C4B_T2F *_vctData2;
	int _vctLength;
	int _idxLength;
	void setLine(Vec2 &v1, Vec2 &v2);
	void refData();

	Vec2  _beginPos;
	_Line _line;
	CustomCommand _customcommand;
};


#endif

