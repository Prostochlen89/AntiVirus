CAVBFile::CAVBFile() {
    this->RecordCount = 0;
}

//! �������� �����
void CAVBFile::close() {
    if (hFile.is_open()) {
        hFile.close();
    }
}

//! �������� ��������� �����
bool CAVBFile::is_open() {
    return hFile.is_open();
}

//! ��������� ����� �������
DWORD CAVBFile::getRecordCount() {
    return this->RecordCount;
}
