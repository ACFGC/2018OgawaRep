#include "CXCharacter.h"

/*
Init
����������
*/
void CXCharacter::Init(CModelX *model) {
	mpModel = model;
	//�ŏ��̃A�j���[�V�����ɂ���
	mAnimationIndex = 0;
	//�J��Ԃ��Đ�����
	mAnimationLoopFlg = true;
	//1�A�j���[�V����60�t���[��
	mAnimationFrameSize = 60.0f;
	//�A�j���[�V�����̃t���[�����ŏ��ɂ���
	mAnimationFrame = 0.0f;
	mpModel->mAnimationSet[mAnimationIndex]->mTime =
		mAnimationFrame;
	//�A�j���[�V�����̏d�݂�1.0�i100%)�ɂ���
	mpModel->mAnimationSet[mAnimationIndex]->mWeight = 1.0f;
}

/*
ChangeAnimation
�A�j���[�V������؂�ւ���
index:�A�j���[�V�����̔ԍ�
loop:true �J��Ԃ�
framesize�F�Ō�܂ōĐ�����̂Ɏg�p�����t���[����
*/
void CXCharacter::ChangeAnimation(int index, bool loop, float framesize) {
	//�����ꍇ�͐؂�ւ��Ȃ�
	if (mAnimationIndex == index) return;
	//���̃A�j���[�V�����̏d�݂�0.0�i0%)�ɂ���
	mpModel->mAnimationSet[mAnimationIndex]->mWeight = 0.0f;
	//�ԍ��A�J��Ԃ��A�t���[������ݒ�
	mAnimationIndex = index % mpModel->mAnimationSet.size();
	mAnimationLoopFlg = loop;
	mAnimationFrameSize = framesize;
	//�A�j���[�V�����̃t���[�����ŏ��ɂ���
	mAnimationFrame = 0.0f;
	mpModel->mAnimationSet[mAnimationIndex]->mTime =
		mAnimationFrame;
	//�A�j���[�V�����̏d�݂�1.0�i100%)�ɂ���
	mpModel->mAnimationSet[mAnimationIndex]->mWeight = 1.0f;
}

/*
Update
�X�V����
matrix�F�ړ��A��]�A�g��k���̍s��
*/
void CXCharacter::Update(CMatrix44 &matrix) {
	//�Ō�܂ōĐ����Ă��Ȃ�
	if (mAnimationFrame < mAnimationFrameSize) {
		//�A�j���[�V�����̎��Ԃ��v�Z
		mpModel->mAnimationSet[mAnimationIndex]->mTime =
			mpModel->mAnimationSet[mAnimationIndex]->mMaxTime *
			mAnimationFrame / mAnimationFrameSize;
		//�t���[����i�߂�
		mAnimationFrame++;
	}
	else {
		//�J��Ԃ��̏ꍇ�́A�t���[����0�ɖ߂�
		if (mAnimationLoopFlg) {
			//�A�j���[�V�����̃t���[�����ŏ��ɂ���
			mAnimationFrame = 0.0f;
			mpModel->mAnimationSet[mAnimationIndex]->mTime = mAnimationFrame;
		}
	}
	//�t���[���̕ϊ��s����A�j���[�V�����ōX�V����
	mpModel->AnimateFrame();
	//�t���[���̍����s����v�Z����
	mpModel->mFrame[0]->AnimateCombined(&matrix);
	//���_�ɃA�j���[�V������K�p����
	mpModel->AnimateVertex();
}

/*
�`�悷��
*/
void CXCharacter::Render() {
	mpModel->Render();
}

//�X�V����
void CXCharacter::Update() {
	CMatrix44 pos, rot;
	//�ʒu�̍s����擾
	pos.SetTranslate(mPosition);
	//?
	pos = pos.Transpose();
	//��]�iY���j�̍s����擾
	rot.SetRotationY(mRotation.y);
	//?
	rot = rot.Transpose();
	//�ʒu��]�s��v�Z
//?	mMatrix = pos * rot;
	mMatrix = rot * pos;
	//�A�j���[�V�������X�V����
	Update(mMatrix);
}
//�d�͏���
void CXCharacter::Gravity() {
	//���x���ړ�
	mPosition.y += mVelocityG;
	//���x������
	mVelocityG -= 0.01f;
}