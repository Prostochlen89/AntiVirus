//! �������� ������������� �����
bool isFileExist(PCSTR FileName){
	return GetFileAttributesA(FileName) != DWORD(-1);
};