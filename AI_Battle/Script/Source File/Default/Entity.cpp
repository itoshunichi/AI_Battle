#include"../../Header File/Default/entity.h"


Entity::Entity()
{
	radius = 1.0;
	edge.left = -1;
	edge.top = -1;
	edge.right = 1;
	edge.bottom = 1;
	mass = 1.0f;
	velocity.x = 0.0;
	velocity.y = 0.0;
	deltaV.x = 0.0;
	deltaV.y = 0.0;
	active = true; //エンティティはアクティブ
	rotatedBoxReady = false;
	collisionType = entityNS::CIRCLE;
	health = 100;
	gravity = entityNS::GRAVITY;
	center = vector2(0, 0);
}

////Entityを初期化
////実行前:*gamePtr = Gameオブジェクトへのポインタ
////width = Imageの幅(ピクセル単位)(0 = テクスチャ全体の幅を使用)
////heigth = Imageの高さ(ピクセル単位)(0 = テクスチャ全体の高さを使用)
////ncols = テクスチャ内の列数(1からnまで)(0は1と同じ)
////*textureM = TextureManagerオブジェクトへのポインタ
////実行後:成功した場合はtrue,失敗した場合はfalseを戻す
//bool Entity::initialize(Game *gamePtr, int width, int height, int ncols,
//	TextureManager *textureM)
//{
//	//input = gamePtr->getInput(); //入力システム
//	//audio = gamePtr->getAudio();
//	//return(Image::initialize(gamePtr->getGraphics(), width, height, ncols, textureM));
//}

//エンティティをアクティブ化
void Entity::activate()
{
	active = true;
}

//Update
//通常、フレームごとに１回呼び出す
//frameTimeは、移動とアニメーションの速さを制御するために使用
void Entity::update(float frameTime)
{
	currentImage.setX(position.x);
	currentImage.setY(position.y);
	currentImage.update(frameTime);
	velocity += deltaV;
	deltaV.x = 0;
	deltaV.y = 0;
	//Image::update(frameTime);
	rotatedBoxReady = false; //rotateBoxの衝突判定のため
}

//AI(人工知能)
//通常、フレームごとに１回呼び出す
//人工知能計算を実行,entは相互作用のために渡される
void Entity::ai(float frameTime, Entity &ent)
{}

//このエンティティともう一方のエンティティの衝突を判定
//各エンティティは必ず1種類の衝突を使用します
//衝突の種類を複数必要とする複雑は図形は、
//各部分を別個のエンティティとして扱うことにより処理できます
//通常、フレームごとに１回呼び出す
//衝突の種類:CIRCLE,BOX,またはROTATED_BOX
//実行後：衝突している場合はtrue,していない場合はfalseを戻す
//        衝突している場合は,collisionVectorを設定
bool Entity::collideWith(Entity &ent)
{
	//if (otherTag != ""&&ent.getTag() != otherTag)return false;

	//どちらかのエンティティがアクティブでない場合、衝突は起こらない
	if (!active || !ent.getActive())
		return false;
	//両方のエンティティがCIRCLR衝突である場合
	if (collisionType == entityNS::CIRCLE&&
		ent.getCollisionType() == entityNS::CIRCLE)
		return collideCircle(ent);

	//両方のエンティティがBOX衝突である場合
	if (collisionType == entityNS::BOX&&
		ent.getCollisionType() == entityNS::BOX)
		return collideBox(ent);
	//他のすべての組み合わせが使用する分離軸テスト
	//どちらのエンティティもCIRCLE衝突判定を使用しない場合
	if (collisionType != entityNS::CIRCLE&&
		ent.getCollisionType() != entityNS::CIRCLE)
		return collideRotatedBox(ent);
	else//どちらか一つのエンティティは円の場合
		//このエンティティがCIRCLE衝突を使用する場合
		if (collisionType == entityNS::CIRCLE)
			return ent.collideRotatedBoxCircle(*this);
		else//もう一方のエンティティがCIRCLE衝突を使用する場合
			return collideRotatedBoxCircle(ent);


}

//このエンティティが指定された短形の外側にあるか
//実行後：短形の外側にある場合はtrue,それ以外の場合はfalseを戻す
bool Entity::outsideRect(RECT rect)
{
	if (position.x + currentImage.getWidth()*currentImage.getScale()<rect.left ||
		position.x>rect.right ||
		position.y + currentImage.getHeight()*currentImage.getScale()<rect.top ||
		position.y>rect.bottom)
		return true;
	return false;
}

//Damage
//このエンティティが、武器によってダメージを受ける
//継承する側のクラスでのこの関数をオーバーライド
void Entity::damage(int weapon)
{

}

//円の衝突判定メソッド
//collision()によって呼び出される、デフォルトの衝突判定メソッド
//実行後：衝突している場合はtrue,していない場合はfalseを戻す
//衝突している場合は、collisionVectorを設定
bool Entity::collideCircle(Entity &ent)
{
	//中心と中心の間の差
	distSqured = getCenter() - ent.getCenter();
	distSqured.x = distSqured.x * distSqured.x;//差を２乗
	distSqured.y = distSqured.y  * distSqured.y;
	//半径の合計を計算(拡大縮小の倍率を調整)
	sumRadiiSquared = (radius*currentImage.getScale()) + (ent.radius*ent.getCurrentImage().getScale());
	sumRadiiSquared *= sumRadiiSquared;//2乗
	//エンティティが衝突している場合
	if (distSqured.x + distSqured.y <= sumRadiiSquared)
	{
		//衝突ベクトルを設定
		collisionVelocity = ent.getCenter() - getCenter();
		return true;
	}
	return false;
}

//軸平行境界ボックスの衝突判定メソッド
//collision()によって呼び出される
//実行後:衝突している場合はtrue,していない場合はfalseを戻す
//衝突している場合は、collisionVectorを設定
bool Entity::collideBox(Entity &ent)
{
	//どちらかのエンティティがアクティブでない場合、衝突は起こらない
	if (!active || !ent.getActive())
		return false;
	
	////軸平行境界ボックスを使って衝突をチェック
	//if ((currentImage.getCenterX() + edge.right*currentImage.getScale() >=
	//	ent.getCurrentImage().getCenterX() + ent.getEdge().left*ent.getCurrentImage().getScale()) &&
	//	(currentImage.getCenterX() + edge.left*currentImage.getScale() <=
	//	ent.getCurrentImage().getCenterX() + ent.getEdge().right*ent.getCurrentImage().getScale()) &&
	//	(currentImage.getCenterY() + edge.bottom*currentImage.getScale() >=
	//	ent.getCurrentImage().getCenterY() + ent.getEdge().top*ent.getCurrentImage().getScale()) &&
	//	(currentImage.getCenterY() + edge.top*getCurrentImage().getScale() <=
	//	ent.getCurrentImage().getCenterY() + ent.getEdge().bottom*ent.getCurrentImage().getScale()))
	if (Math::abs(position.x - ent.getPosition().x)<(currentImage.getWidth()*currentImage.getScale()) / 2 + (ent.getCurrentImage().getWidth()*ent.getCurrentImage().getScale())/2&&
		Math::abs(position.y - ent.getPosition().y)<(currentImage.getHeight()*currentImage.getScale()) / 2 + (ent.getCurrentImage().getHeight()*ent.getCurrentImage().getScale())/2)
	{
		//衝突ベクトルを設定
		collisionVelocity = ent.getCenter() - getCenter();
		//Vector2 test =ent.getCenter();
		return true;

	}

	return false;
}

//回転するボックスの衝突判定メソッド
//collision()によって呼び出される
//実行後:衝突している場合はtrue,していない場合はfalseを戻す
//       衝突している場合は、collisionVectorを設定
//分離軸テストを使用して衝突を判定
//分離軸テスト：
//2つのボックスは、特定の直線への投影が重なっていなければ衝突しない
bool  Entity::collideRotatedBox(Entity &ent)
{
	computeRotatedBox(); //回転するボックスを準備
	ent.computeRotatedBox();//回転するボックスを準備
	if (projectionsOverlap(ent) && ent.projectionsOverlap(*this))
	{
		//衝突ベクトルを設定
		collisionVelocity = ent.getCenter() - getCenter();
		return true;
	}

	return false;
}

//回転するボックスの頂点、投影線、投影の最小値と最大値を計算
//0---1頂点の番号
//|   |
//3---2
void Entity::computeRotatedBox()
{
	if (rotatedBoxReady)
		return;
	float projection;

	//xとyのベクトルを現在のエンティティの角度から作成する
	Vector2 rotatedX = vector2(cos(getCurrentImage().getRadians()), sin(getCurrentImage().getRadians()));
	Vector2 rotatedY = vector2(-sin(getCurrentImage().getRadians()), cos(getCurrentImage().getRadians()));

	//回転するボックスの頂点を計算する
	const Vector2 center = getCenter();
	corners[0] = center + rotatedX*((float)edge.left*getCurrentImage().getScale()) +
		rotatedY*((float)edge.top*getCurrentImage().getScale());

	corners[1] = center + rotatedX*((float)edge.right * getCurrentImage().getScale()) +
		rotatedY *((float)edge.top*getCurrentImage().getScale());

	corners[2] = center + rotatedX*((float)edge.right * getCurrentImage().getScale()) +
		rotatedY *((float)edge.bottom * getCurrentImage().getScale());

	corners[3] = center + rotatedX*((float)edge.left*getCurrentImage().getScale()) +
		rotatedY*((float)edge.top *getCurrentImage().getScale());

	//2つの投影線を作成
	//corners[0]を基点として使用
	//corners[0]に接する二辺を投影線として使用
	edge01 = vector2(corners[1].x - corners[0].x,
		corners[1].y - corners[0].y);
	normalize(edge01);
	//graphics->Vector2Normalize(&edge01);

	edge03 = vector2(corners[3].x - corners[0].x,
		corners[3].y - corners[0].y);
	normalize(edge03);

	//このエンティティを投影線上に投影したときの最小値と最大値
	projection = dot(edge01, corners[0]);
	edge01Min = projection;
	edge01Max = projection;
	//edge01への投影
	projection = dot(edge01, corners[1]);
	if (projection < edge01Min)
		edge01Max = projection;
	//edge03への投影
	projection = dot(edge03, corners[0]);
	edge03Min = projection;
	edge03Max = projection;
	projection = dot(edge03, corners[3]);
	if (projection < edge03Min)
		edge03Min = projection;
	else if (projection > edge03Max)
		edge03Max = projection;
	rotatedBoxReady = true;
}

//相手のボックスを、このエンティティのedge01およびedge03に投影
//collideRotatedBox()によって呼び出される
//実行後：投影が重なっている場合はtrue、それ以外の場合はfalseを戻す
bool Entity::projectionsOverlap(Entity &ent)
{
	float projection, min01, max01, min03, max03;
	//相手のボックスをedge01に投影
	projection = dot(edge01, *ent.getCorner(0));//
	//頂点０を投影
	min01 = projection;
	max01 = projection;
	//残りの頂点それぞれを処理
	for (int c = 1; c < 4; c++)
	{
		//頂点をedge01に投影
		projection = dot(edge01, *ent.getCorner(c));
		if (projection < min01)
			min01 = projection;
		else if (projection>max01)
			max01 = projection;
	}
	//投影が重ならない場合
	if (min01 > edge01Max || max01 < edge01Min)
		return false;//衝突の可能性無し
	//相手のボックスをedge03に投影
	projection = dot(edge03, *ent.getCorner(0));
	//頂点0を投影
	min03 = projection;
	max03 = projection;
	//残りの頂点それぞれを処理
	for (int c = 1; c < 4; c++)
	{
		//頂点をedge03に投影
		projection = dot(edge03, *ent.getCorner(c));
		if (projection < min03)
			min03 = projection;
		else if (projection > max03)
			max03 = projection;
	}
	//投影が重ならない場合
	if (min03>edge03Max || max03 < edge03Min)
		return false;//衝突の可能性無し
	return true;     //投影が重なっている場合
}

//回転するボックスと円の衝突判定メソッド
//collision()によって呼び出される
//ボックスの辺と円の半径で分離軸テストを使用
//円の中心が衝突ボックスの各辺を伸ばした直線の外側
//(ボロイノ領域と呼ばれる)にある場合、ボックスの最も近い頂点と
//衝突がないかを距離のチェックで判定します
//最も近い頂点は、重なりのテストから判断できます。
//
//Voronoi0 |   | Voronoi1
//      ---0---1---
//         |   |
//      ---3---2---
//Voronoi3 |   | Voronoi2
//
//実行前：このエンティティは必ずボックス、相手のエンティティ(ent)は必ず円
//実行後：衝突している場合はtrue、していない場合はfalseを戻す
//衝突している場合は,collisionVectorを設定
bool Entity::collideRotatedBoxCircle(Entity &ent)
{
	float min01, min03, max01, max03, center01, center03;

	computeRotatedBox(); //回転するボックスを準備

	//円の中心をedge01に投影
	center01 = dot(edge01, ent.getCenter());
	//最小値と最大値は中心からの半径
	min01 = center01 - ent.getCurrentImage().getRadians()*ent.getCurrentImage().getScale();
	max01 = center01 + ent.getCurrentImage().getRadians()*ent.getCurrentImage().getScale();
	if (min01 > edge01Max || max01 < edge01Min)//投影が重ならない場合
		return false;     //衝突の可能性なし

	//円の中心をedge03に投影
	center03 = dot(edge03, ent.getCenter());
	//最小値と最大値は中心あらの半径
	min03 = center03 - ent.getCurrentImage().getRadians()*ent.getCurrentImage().getScale();
	max03 = center03 + ent.getCurrentImage().getRadians()*ent.getCurrentImage().getScale();
	if (min03 > edge03Max || max03 < edge03Min)//投影が重ならない場合
		return false; //衝突の可能性なし

	//円の投影がボックスの投影に重なる場合
	//円が衝突ボックスのボロイノ領域にあるかどうかチェック

	//中心がVornoi0にある場合
	if (center01 < edge01Min&&center03 < edge03Min)
		return collideCornerCircle(corners[0], ent);

	//中心がVoronoi1にある場合
	if (center01>edge01Max&&center03 < edge03Min)
		return collideCornerCircle(corners[1], ent);

	//中心がVoronoi2にある場合
	if (center01>edge01Max&&center03>edge03Max)
		return collideCornerCircle(corners[2], ent);

	//中心がVoronoi3にある場合
	if (center01 > edge01Min&&center03 > edge03Max)
		return collideCornerCircle(corners[3], ent);

	//円がボロノイ領域にない場合、円はボックスの辺と衝突している
	//衝突ベクトルを設定、単純に、円の中心からボックスの中心までを使用
	collisionVelocity = ent.getCenter() - getCenter();

	return true;


}

//ボックスの頂点が円と衝突していないかを、距離のチェックを使用して判定
//collideRotatedBoxCircle()によって呼び出される
//実行後：衝突している場合はtrue、していない場合はfalseを戻す
//衝突している場合は,collisionVectorを設定
bool Entity::collideCornerCircle(Vector2 corner, Entity &ent)
{
	distSqured = corner -ent.getCenter(); //頂点-円
	distSqured.x = distSqured.x * distSqured.x;//差を２乗
	distSqured.y = distSqured.y*distSqured.y;
	//半径の合計を計算してから、それを２乗
	sumRadiiSquared = ent.getRadius()*ent.getCurrentImage().getScale(); //(0+円の半径)
	sumRadiiSquared *= sumRadiiSquared;//２乗する
	//頂点と円が衝突している場合
	if (distSqured.x + distSqured.y <= sumRadiiSquared)
	{
		//衝突ベクトルを設定
		collisionVelocity = ent.getCenter() - corner;
		return true;
	}
	return false;
}

//他のエンティティとの衝突後の跳ね返り
void Entity::bounce(Vector2 &collisionVector, Entity &ent)
{
	Vector2 Vdiff = ent.getVelocity() - velocity;
	Vector2 cUV = collisionVector; //衝突単位ベクトル
	normalize(cUV);
	float cUVdotVdiff = dot(cUV, Vdiff);
	float massRatio = 2.0f;
	if (getMass() != 0)
		massRatio *= (ent.getMass() / (getMass() + ent.getMass()));
	//エンティティが既に離れる方向に動いている場合は、bouceが
	//前にも呼び出されたものの、衝突がまだ続いている状態です。
	//エンティティを、collisionVectorに沿って離れる方向に移動
	if (cUVdotVdiff > 0)
	{
		position.x = (position.x - cUV.x*massRatio);
		position.y = (position.y - cUV.y*massRatio);
	}
	else
		deltaV += ((massRatio * cUVdotVdiff)*cUV);
}

//相手のエンティティからのこのエンティティへの重力
//重力をこのエンティティの速度ベクトルに加算
//Force = GRAVITY * m1 * m2 /r*r
//                2          2
//r*r = (Ax - Bx) + (Ay - By)
void Entity::gravityForce(Entity *ent, float frameTime)
{
	//どちらかのエンティティがアクティブでない場合、重力の影響はない
	if (!active || !ent->getActive())
		return;
	rr = pow((ent->getCurrentImage().getCenterX() - getCurrentImage().getCenterX()), 2) +
		pow((ent->getCurrentImage().getCenterY() - getCurrentImage().getCenterY()), 2);
	force = gravity * ent->getMass() * mass / rr;

	//---ベクトル計算を使って重力ベクトルを作成---
	//エンティティ間のベクトルを作成
	Vector2 gravityV = vector2(ent->getCurrentImage().getCenterX() - getCurrentImage().getCenterX(),
		ent->getCurrentImage().getCenterY() - getCurrentImage().getCenterY());

	//ベクトルを正規化
	normalize(gravityV);
	//重力で乗算して、重力ベクトルを作成
	gravityV *= force * frameTime;

	//重力ベクトルを、移動中の速度ベクトルに加算して、方向を変える
	velocity += gravityV;
}