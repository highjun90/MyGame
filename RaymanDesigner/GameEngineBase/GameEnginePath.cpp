#include "GameEnginePath.h"
#include "GameEngineDebug.h"

GameEnginePath::GameEnginePath()
{
}

GameEnginePath::GameEnginePath(const std::string& _path)
	: Path(_path)
{

}

GameEnginePath::~GameEnginePath()
{
}

std::string GameEnginePath::GetFileName()
{
	return Path.filename().string();
}

void GameEnginePath::GetCurrentPath()
{
	Path = std::filesystem::current_path();
}


void GameEnginePath::MoveParent()
{
	Path = Path.parent_path();
}

void GameEnginePath::MoveParentToExistsChild(const std::string& _ChildPath)
{
	while (true)
	{
		std::filesystem::path CheckPath = Path;

		CheckPath.append(_ChildPath);

		if (false == std::filesystem::exists(CheckPath))
		{
			MoveParent();
		}
		else
		{
			break;
		}

		if (Path == Path.root_path())
		{
			MsgBoxAssert("루트 경로까지 샅샅히 뒤졌지만" + _ChildPath + "파일이나 폴더를 하위로 가지고 있는 경로를 찾지 못했습니다");
		}
	}


}

void GameEnginePath::MoveChild(const std::string& _ChildPath)
{
	std::filesystem::path CheckPath = Path;

	CheckPath.append(_ChildPath);

	if (false == std::filesystem::exists(CheckPath))
	{
		MsgBoxAssert("존재하지 않는 경로로 이동하려고 했습니다." + CheckPath.string());
	}

	Path = CheckPath;
}







//============= 최종 삭제 주석 =============

//std::filesystem::path::filename() 함수 - path 클래스에서 저장된 경로의 마지막 파일이름을 반환. (정확히는 오른쪽부터 역슬래시 \ 한개를 만나기 전까지)
// 예시) 1. path(c:\Test0\FileA); cout << path.filename()       -> "FileA" 
//       2. path(C:); cout << path.filename()                   -> "C:"
//       3. path(c:\\Test0\\FileA\\); cout << path.filename()   -> ""
//       4. path(c:\Test0\FileA\); cout << path.filename()      -> ""
//       5. path(c:\\Test0\\FileA\..); cout << path.filename()  -> ".."
//       6. path(c:\\Test0\\FileA.bar); cout << path.filename() -> "FileA.bar"