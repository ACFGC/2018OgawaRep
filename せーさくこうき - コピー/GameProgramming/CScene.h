#ifndef CSCENE_H
#define CSCENE_H

#include "CText.h"
#include "CModelX.h"

/*
シーンの基本クラス
*/
class CScene {
public:
	static CScene *spInstance;
	//シーンの識別値
	enum ESceneTag {
		EROOT,
		EGAME,	//ゲームシーン
		EWIN,	//勝利
		ELOSE	//敗北
	};
	//シーンの識別子
	ESceneTag mSceneTag;

	
	CText mText;

	CModelX mModelX;

	//仮想関数
	//デストラクタを仮想関数にしないと
	//子クラスのデストラクタが呼ばれない
	virtual ~CScene() {}
	virtual void Init();
	virtual void Update();
};

#endif
