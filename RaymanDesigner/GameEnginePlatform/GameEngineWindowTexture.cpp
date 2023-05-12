#include "GameEngineWindowTexture.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineDebug.h>
#include "GameEngineWindow.h"

#pragma comment(lib, "msimg32.lib")


GameEngineWindowTexture::GameEngineWindowTexture()
{
}

GameEngineWindowTexture::~GameEngineWindowTexture()
{
}

void GameEngineWindowTexture::ResLoad(const std::string& _Path)
{
	// 단순히 비트맵만 로드하는 함수가 아니라서 우리에게 그냥 HANDLE을 준다
	// 선생님 기억으로는 커서 아이콘등도 이녀석으로 로드할수 있었나? 하는데 그래서 

	// LoadBitmapA()

	// LPCSTR == const char*

	HANDLE ImageHandle = LoadImageA(nullptr, _Path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	if (nullptr == ImageHandle)
	{
		MsgBoxAssert("이미지 로드에 실패했습니다." + _Path);
		return;
	}

	// 이미지의 핸들일 뿐이고.
	BitMap = static_cast<HBITMAP>(ImageHandle);

	// 없던 권한을 새롭게 만들어야 한다.
	// Window에서 얻어온 DC
	ImageDC = CreateCompatibleDC(nullptr);
	// 이미지의 수정 권한을 만들어 내고

	// ImageDC 권한에
	// BitMap 2차원의 색깔 집합을 연결해라.
	// 사실 이미 만들어지자마자 내부에 1,1 이미지와 연결되어있고
	// 내가 로드한 이미지를 그 1,1짜리를 밀어내고 교체하는 작업을 하는데.
	// 이 함수의 리턴값이 기존에 연결되어있던 애를 리턴해주는것.
	OldBitMap = static_cast<HBITMAP>(SelectObject(ImageDC, BitMap));

	ScaleCheck();
}

void GameEngineWindowTexture::ResCreate(const float4& _Scale)
{
	// 그냥 비어있는 흰색 이미지를 하나 만드는 함수인거에요.
	HANDLE ImageHandle = CreateCompatibleBitmap(GameEngineWindow::MainWindow.GetHDC(), _Scale.iX(), _Scale.iY());

	if (nullptr == ImageHandle)
	{
		MsgBoxAssert("이미지 생성에 실패했습니다.");
		return;
	}

	// 이미지의 핸들일 뿐이고.
	BitMap = static_cast<HBITMAP>(ImageHandle);

	// 없던 권한을 새롭게 만들어야 한다.
	// Window에서 얻어온 DC
	ImageDC = CreateCompatibleDC(nullptr);
	// 이미지의 수정 권한을 만들어 내고

	// ImageDC 권한에
	// BitMap 2차원의 색깔 집합을 연결해라.
	// 사실 이미 만들어지자마자 내부에 1,1 이미지와 연결되어있고
	// 내가 로드한 이미지를 그 1,1짜리를 밀어내고 교체하는 작업을 하는데.
	// 이 함수의 리턴값이 기존에 연결되어있던 애를 리턴해주는것.
	OldBitMap = static_cast<HBITMAP>(SelectObject(ImageDC, BitMap));

	ScaleCheck();
}

void GameEngineWindowTexture::ScaleCheck()
{
	GetObject(BitMap, sizeof(BITMAP), &Info);

	BITMAP OldInfo;

	GetObject(OldBitMap, sizeof(BITMAP), &OldInfo);
}

float4 GameEngineWindowTexture::GetScale()
{

	return { static_cast<float>(Info.bmWidth), static_cast<float>(Info.bmHeight) };
}



void GameEngineWindowTexture::BitCopy(GameEngineWindowTexture* _CopyTexture, const float4& _Pos)
{
	BitCopy(_CopyTexture, _Pos, _CopyTexture->GetScale());
}

void GameEngineWindowTexture::BitCopy(
	GameEngineWindowTexture* _CopyTexture,
	const float4& _Pos,
	const float4& _Scale)
{
	HDC CopyImageDC = _CopyTexture->GetImageDC();

	//// 특정 DC에 연결된 색상을
	//// 특정 DC에 고속복사하는 함수입니다.
	BitBlt(ImageDC,
		_Pos.iX() - _Scale.ihX(),
		_Pos.iY() - _Scale.ihY(),
		_Scale.iX(),
		_Scale.iY(),
		CopyImageDC,
		0,
		0,
		SRCCOPY);

}

void GameEngineWindowTexture::TransCopy(GameEngineWindowTexture* _CopyTexture, const float4& _Pos, const float4& _Scale, const float4& _OtherPos, const float4& _OtherScale, int _TransColor/* = RGB(255, 0, 255)*/)
{
	HDC CopyImageDC = _CopyTexture->GetImageDC();

	//// 특정 DC에 연결된 색상을
	//// 특정 DC에 고속복사하는 함수입니다.
	TransparentBlt(ImageDC,
		_Pos.iX() - _Scale.ihX(),
		_Pos.iY() - _Scale.ihY(),
		_Scale.iX(),
		_Scale.iY(),
		CopyImageDC,
		_OtherPos.iX(), // 카피하려는 이미지의 왼쪽위 x
		_OtherPos.iY(), // 카피하려는 이미지의 왼쪽위 y
		_OtherScale.iX(), // 그부분부터 사이즈  x
		_OtherScale.iY(), // 그부분부터 사이즈  y
		_TransColor
	);

}
// ======= 최종 삭제 주석 ===========

//리마인드 - HANDLE 은 운영체제가 무엇인가 식별하기 위한 키값을 핸들이라고 한다. 핸들번호는 운영체제가 정하고 중복될 수 없음.

//HANDLE LoadImageA(                    //새로 로드된 이미지의 핸들을 반환해준다. 실패하면 null 반환
//	[in, optional] HINSTANCE hInst,   //로드할 이미지를 가질 응용프로그램
//	[in]           LPCSTR    name,    //로드할 이미지 파일경로
//	[in]           UINT      type,    //로드할 이미지 형식. IMAGE_BITMAP: 비트맵로드
//	[in]           int       cx,      //이미지 너비설정. 0이면 실제 리소스 너비.
//	[in]           int       cy,      //이미지 높이설정. 0이면 실제 리소스 높이.
//	[in]           UINT      fuLoad   //여러가지 옵션. LR_LOADFROMFILE: 지정된 파일에서 독립실행형 이미지를 로드.
//);

//HDC CreateCompatibleDC(        // DC의 특성을 대부분 다 갖고있지만 출력장치와는 연결이 안된 DC를 생성해야할때 사용. 성공하면 메모리 DC(CreateCompatibleDC로 만들어진 DC를 Memory DC라고함)의 핸들 반환, 실패는 null
//	[in] HDC hdc                 // 인자가 null이면 애플리케이션의 현재 화면에 호환되는 메모리 DC를 만듬
//);                             //https://blog.naver.com/tipsware/220995733415
  
//HBITMAP CreateCompatibleBitmap(  // 지정된 DC와 연결된 디바이스에 호환되는 비트맵을만듬. 함수성공시 호환되는 비트맵 핸들을 반환, 실패는 null
//	[in] HDC hdc,                  // DC의 핸들
//	[in] int cx,                   // 비트맵너비
//	[in] int cy                    // 비트맵높이
//);
//원래는 CreateBitmap() 함수가 있는데 이건인자가 5개임 그러나 이 함수는 DDB(장치종속적비트맵)이여서 DC에 영향을 많이 받음. 따라서 애초에 DC와 호환되게 비트맵을 만드는게 제일 편하고 안전하니 그게 CreateCompatibleBitmap. https://blog.naver.com/tipsware/220985029852

//HGDIOBJ SelectObject(          //DC에 저장된 Object를 변경할때 사용함. hdc가 가리키는 object를 h로 변경함.
//	[in] HDC     hdc,
//	[in] HGDIOBJ h
//);
//
//int GetObject(                //지정된 그래픽 개체에 대한 정보를 저장
//	[in]  HANDLE h,            //그래픽개체의 핸들.
//	[in]  int    c,            //버퍼에 쓸 정보의 바이트 수
//	[out] LPVOID pv            //그래픽개체의 정보를 저장할 버퍼의 포인터.
//);

//BOOL BitBlt(                 //이미지를 화면에 출력해주는 함수
//	[in] HDC   hdc,            //이미지가 출력될 위치의 핸들
//	[in] int   x,              // 이미지가 출력될 핸들화면의 왼쪽위 모서리 x좌표
//	[in] int   y,              //                                          y좌표
//	[in] int   cx,             // 출력될 이미지의 x너비
//	[in] int   cy,             //                 y 높이
//	[in] HDC   hdcSrc,         //이미지의 핸들
//	[in] int   x1,             //원본이미지에서 왼쪽위 x좌표. 
//	[in] int   y1,             //                      y                  
//	[in] DWORD rop             //이미지 출력방식. SRCCOPY: 원본이미지 출력
//);                          


//BOOL TransparentBlt(          //BitBlt은 이미지와 출력장소의 픽셀을 1:1로 대응해서 출력하는 기능만 있으므로, 이미지를 화면 비율에 맞춰 확대및 축소를 할 수 없다. 이미지 그대로 복사를 하는 경우엔 BltBlt을 사용해도 되지만 이미를 확대 축소하고 싶다면? 이 함수를 써서 이미지를 확대 축소할수 있다. (꿋꿋히 BitBlt을 사용하겠다면 이미지를 그에맞게 수정해서 가져오는 수밖에 없다.)
//	[in] HDC  hdcDest,        // 이미지가 출력될 핸들
//	[in] int  xoriginDest,    // 출력위치. 왼쪽위 모서리의 x좌표
//	[in] int  yoriginDest,    //                           y좌표
//	[in] int  wDest,          // 출력위치로부터 x 너비
//	[in] int  hDest,          //                y 너비
//	[in] HDC  hdcSrc,         // 원본이미지핸들
//	[in] int  xoriginSrc,     // 원본이미지의 왼쪽위 x좌표
//	[in] int  yoriginSrc,     //                     y좌표
//	[in] int  wSrc,           // 원본이미지의 왼쪽위 x좌표 부터의 너비
//	[in] int  hSrc,           //                     y
//	[in] UINT crTransparent   // 투명으로 처리할 원본 비트맵의 RGB 색. 보통(255,0,255) 마젠타로 지정함. 이 색이 눈아파서 게임 만들때 안쓰는 색이기때문. 즉, 이미지에 투명으로 처리하고 싶은부분은 마젠타로 색을 수정해놓으면 출력할때 투명하게 나옴
//);